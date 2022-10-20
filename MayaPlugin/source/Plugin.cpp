#include "maya_includes.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>

#include "Send.h"

Comlib* producerBuffer;
std::unordered_map<std::string, MCallbackId> callbacks;
MStatus status = MS::kSuccess;

#define PRINT_EXTRA 0
#define PRINT_SENDS 1

/*
	IF FILE-NODE EXISTS BEFORE HAND BUT NOT CONNECTED TO ANYTHING IT'LL NOT SET ANY CALLBACKS
	IF FILE-NODE EXISTS BEFORE HAND BUT NOT CONNECTED TO ANYTHING IT'LL NOT SET ANY CALLBACKS
	IF FILE-NODE EXISTS BEFORE HAND BUT NOT CONNECTED TO ANYTHING IT'LL NOT SET ANY CALLBACKS
	IF FILE-NODE EXISTS BEFORE HAND BUT NOT CONNECTED TO ANYTHING IT'LL NOT SET ANY CALLBACKS
	IF FILE-NODE EXISTS BEFORE HAND BUT NOT CONNECTED TO ANYTHING IT'LL NOT SET ANY CALLBACKS
*/

void addCallback(const std::string& name, MCallbackId id)
{
	static int i = 0;
	std::string tempName = name;

	if (callbacks.count(name))
		tempName += i++;

	callbacks[tempName] = id;
}
void addCallbackDelOld(const std::string& name, MCallbackId id)
{
	if (callbacks.count(name))
		MMessage::removeCallback(callbacks[name]);

	callbacks[name] = id;
}
void removeCallback(const std::string& name)
{
	if (callbacks.find(name) == callbacks.end())
		return;

	MNodeMessage::removeCallback(callbacks[name]);
	callbacks.erase(name);
}

/*


	Extrude initially works, but dragging while in extrude doesn't register.
	It sends attributeChanged with msg kAttributeSet.
	Currently meshAttribteChanged only checks kAttributeSet
	and meshTopoAttributeChanged only checks kAttributeEval,
	but removes the callback when outMesh is found

	kAttributeEval in meshAttributeChanged is triggered too much with a .outMesh check,
	atleast when a node is created (triggers twice).
	Otherwise it seems fine (?) but Patrik said to use only kAttributeSet in meshAttributeChanged .-.

	not removing the meshTopoAttributeChanged callback creates duplicates.

	maybe meshAttribteChanged-Eval can check if extrude is active ?

	------

	Dragging a vertex currently sends the whole mesh.. Need to send only the affected vertices

	------

	Recheck camera height

	------

	USE MItMeshFaceVertex FOR VERTEX BUFFER
	USE mesh.getTriangleOffsets FOR INDEX BUFFER
	WHEN DRAGGING VERT FIND AFFECTED VERTS BY LOOP THRO MIT AND SEARCH FOR vertId() == INDEX
	SAVE I WHEN FOUND AND UPDATE VERTEX BUFFER WITH SAVED INDICIES
	// COULD MAYBE JUST SEND THE NEW VERTEX DATA WHEN vertId() == PLUG INDEX RIGHT ?

*/

void meshAttributeChanged(MNodeMessage::AttributeMessage msg, MPlug& plug, MPlug& otherPlug, void* clientData)
{
	if (msg & MNodeMessage::AttributeMessage::kAttributeSet)
	{
		MFnMesh mesh(plug.node(), &status);
		if (M_FAIL2)
			return;

		std::string plugName = plug.name().asChar();

		if (plugName.find(".pnts[") != -1)
		{
			sendUpdateMesh(plug.node(), producerBuffer);
		}

	}
}

void meshTopoAttributeChanged(MNodeMessage::AttributeMessage msg, MPlug& plug, MPlug& otherPlug, void* clientData)
{
	if (msg & MNodeMessage::AttributeMessage::kAttributeEval)
	{
		MFnMesh mesh(plug.node(), &status);
		std::string nodeName = mesh.name().asChar();
		std::string plugName = plug.name().asChar();

		if (M_OK2)
		{
			if (plugName.find(".outMesh") != -1)
			{
				removeCallback(nodeName + "meshTopoAttriCB");
				sendMesh(plug.node(), producerBuffer);	
			}
		}
	}
}

void fileTextureAttributeChanged(MNodeMessage::AttributeMessage msg, MPlug& plug, MPlug& otherPlug, void* clientData)
{
	// Early out if a connection was changed and otherPlug.node() is the material
	if (msg & MNodeMessage::kConnectionBroken || msg & MNodeMessage::kConnectionMade)
	{
		if (otherPlug.node().hasFn(MFn::kLambert))
		{
			SendMaterialData(MFnDependencyNode(otherPlug.node()), producerBuffer);
			return;
		}
	}

	if (msg & MNodeMessage::kAttributeSet || msg & MNodeMessage::kConnectionMade)
	{
		MFnDependencyNode dgNode(plug.node(), &status);
		if (M_FAIL2)
			return;

		MPlug plug = dgNode.findPlug("outColor", false, &status);
		if (M_OK2)
		{
			MPlugArray connections;
			plug.connectedTo(connections, false, true, &status);

			if (M_OK2)
			{
				for (unsigned int i = 0; i < connections.length(); i++)
				{
					MObject curNode = connections[i].node();

					if (curNode.hasFn(MFn::kLambert))
					{
						SendMaterialData(MFnDependencyNode(curNode), producerBuffer);
					}
				}
			}
		}

		plug = dgNode.findPlug("outAlpha", false, &status);
		if (M_OK2)
		{
			MPlugArray connections;
			plug.connectedTo(connections, false, true, &status);

			if (M_OK2)
			{
				for (unsigned int i = 0; i < connections.length(); i++)
				{
					MObject curNodeI = connections[i].node();
					if (curNodeI.hasFn(MFn::kBump))
					{
						MFnDependencyNode dgBumpNode(curNodeI, &status);
						if (M_FAIL2)
							continue;

						plug = dgBumpNode.findPlug("outNormal", false, &status);
						if (M_FAIL2)
							continue;

						plug.connectedTo(connections, false, true, &status);
						if (M_FAIL2)
							continue;

						for (unsigned int j = 0; j < connections.length(); j++)
						{
							MObject curNodeJ = connections[j].node();
							if (curNodeJ.hasFn(MFn::kLambert))
							{
								SendMaterialData(MFnDependencyNode(curNodeJ), producerBuffer);
								continue;
							}
						}
					}
				}
			}
		}
	}

	if (msg & MNodeMessage::kConnectionBroken)
	{
		if (otherPlug.node().hasFn(MFn::kBump))
		{
			MFnDependencyNode bumpNode(otherPlug.node());

			MPlug plug = bumpNode.findPlug("outNormal", false, &status);
			if (M_FAIL2)
				return;

			MPlugArray connections;
			plug.connectedTo(connections, false, true, &status);
			if (M_FAIL2)
				return;

			for (unsigned int i = 0; i < connections.length(); i++)
			{
				if (connections[i].node().hasFn(MFn::kLambert))
				{
					MFnDependencyNode lambert(connections[i].node(), &status);
					if (M_OK2)
						SendMaterialData(lambert, producerBuffer);
				}
			}
		}
	}
}

void setFileCallbacks(MObject& materialNode)
{
	if (materialNode.hasFn(MFn::kLambert))
	{
		MFnLambertShader tempLamb(materialNode, &status);
		if (M_FAIL2)
			return;

		const char* matName = tempLamb.name().asChar();

		MPlugArray lambertCon;
		MPlug lambertPlug = tempLamb.findPlug("color", false);
		lambertPlug.connectedTo(lambertCon, true, false);
		bool hasTexture = false;

		if (lambertCon.length() > 0)
		{
			MObject obj(lambertCon[0].node());
			if (obj.hasFn(MFn::kFileTexture))
			{
				MCallbackId id = MNodeMessage::addAttributeChangedCallback(obj, fileTextureAttributeChanged, nullptr, &status);
				if (M_OK2)
				{
					std::string textureNodeName = MFnDependencyNode(obj).name().asChar();
					addCallbackDelOld(textureNodeName + "FileTextureChanged", id);
				}
			}
		}

		MPlug normPlug = tempLamb.findPlug("normalCamera", false);
		normPlug.connectedTo(lambertCon, true, false);

		if (lambertCon.length() > 0)
		{
			if (lambertCon[0].node().hasFn(MFn::kBump))
			{
				MFnDependencyNode bump(lambertCon[0].node());

				MPlug bumpPlug = bump.findPlug("bumpValue", false);
				bumpPlug.connectedTo(lambertCon, true, false);

				if (lambertCon.length() > 0)
				{
					MObject obj(lambertCon[0].node());
					if (obj.hasFn(MFn::kFileTexture))
					{
						MCallbackId id = MNodeMessage::addAttributeChangedCallback(obj, fileTextureAttributeChanged, nullptr, &status);
						if (M_OK2)
						{
							std::string textureNodeName = MFnDependencyNode(obj).name().asChar();
							addCallbackDelOld(textureNodeName + "FileTextureChanged", id);
						}
					}
				}
			}
		}
	}
}

void materialAttributeChanged(MNodeMessage::AttributeMessage msg, MPlug& plug, MPlug& otherPlug, void* x)
{
	if (msg & MNodeMessage::kConnectionMade || msg & MNodeMessage::kConnectionBroken)
	{
		MObject node = plug.node();
		MObject otherNode = otherPlug.node();
		MFnDependencyNode material(node);

		if (otherNode.hasFn(MFn::kShadingEngine))
		{
			SendMaterialData(material, producerBuffer); 
		}

		if (otherNode.hasFn(MFn::kBump))
		{
			SendMaterialData(material, producerBuffer);

			/*MFnDependencyNode bumpNode(otherNode, &status);
			if (M_OK2)
			{
				MPlugArray plugArr;
				MPlug bumpPlug = bumpNode.findPlug("bumpValue", false);
				bumpPlug.connectedTo(plugArr, true, false);

				for (unsigned int i = 0; i < plugArr.length(); i++)
				{
					MObject obj(plugArr[i].node());
					if (obj.hasFn(MFn::kFileTexture))
					{
						MCallbackId id = MNodeMessage::addAttributeChangedCallback(obj, fileTextureAttributeChanged, nullptr, &status);
						if (M_OK2)
						{
							std::string textureNodeName = MFnDependencyNode(obj).name().asChar();
							addCallbackDelOld(textureNodeName + "FileTextureChanged", id);
						}
						break;

					}
				}
			}*/
		}


	}
	else if (msg & MNodeMessage::kAttributeSet)
	{
		if (plug.node().hasFn(MFn::kLambert))
		{
			MFnDependencyNode material(plug.node());
			SendMaterialData(material, producerBuffer);
		}
	}
}

void meshSetMaterial(MNodeMessage::AttributeMessage msg, MPlug& plug, MPlug& otherPlug, void* x)
{
	if (msg & MNodeMessage::kConnectionMade)
	{
		MObject otherNode = otherPlug.node(&status);
		if (M_FAIL2)
			return;

		if (otherNode.hasFn(MFn::kShadingEngine) && std::string(plug.name().asChar()).find(".instObjGroups[0]") != -1)
		{
			sendAttachedMaterial(plug.node(), producerBuffer);
		}
	}
}

void meshTopoChanged(MObject& node, void* clientData)
{
	MCallbackId callbackId = MNodeMessage::addAttributeChangedCallback(node, meshTopoAttributeChanged, nullptr, &status);
	std::string name = MFnDependencyNode(node).name().asChar();
	if (M_OK2)
		addCallback(name + "meshTopoAttriCB", callbackId);
}

void meshDirtyPlug(MObject& node, MPlug& plug, void* clientData)
{
	MFnMesh mesh(node, &status);
	if (M_OK2)
	{
		std::string nodeName = mesh.name().asChar();

		if (std::string(plug.name().asChar()).find(".inMesh") != -1)
		{
			removeCallback(nodeName + "DirtyPlug");

			sendMesh(node, producerBuffer);

			MCallbackId id = MNodeMessage::addAttributeChangedCallback(node, meshSetMaterial, nullptr, &status);
			if (M_OK2)
				addCallback(nodeName + "MeshMatAttriChanged", id);

			sendAttachedMaterial(node, producerBuffer);
		}
	}
}

void transformAttributeChanged(MNodeMessage::AttributeMessage msg, MPlug& plug, MPlug& otherPlug, void* x)
{
	if (msg & MNodeMessage::AttributeMessage::kAttributeSet)
	{
		MObject obj(plug.node());
		if (obj.hasFn(MFn::kTransform))
		{
			SendTransformData(obj, producerBuffer);
		}
	}
}

void cameraMoved(const MString& str, void* clientData)
{
	MString activePanel = MGlobal::executeCommandStringResult("getPanel -wf");

	if (strcmp(str.asChar(), activePanel.asChar()) == 0)
		sendCamera(M3dView::active3dView(), producerBuffer);
}

void nodeNameChange(MObject& node, const MString& prevName, void* clientData)
{
	MFnTransform traNode(node, &status);
	if (M_OK2)
	{
		NameChangeHeader nameChange;
		nameChange.newName = traNode.name(&status).asChar();
		if (M_FAIL2)
			return;

		SectionHeader secHeader;
		secHeader.header = NAME_CHANGE;
		secHeader.name = prevName.asChar();
		secHeader.messageLength = sizeof(NameChangeHeader);

		producerBuffer->Send((char*)&nameChange, &secHeader);
	}
}

void iterateScene()
{
	MCallbackId id;

	// FILE TEXTURE
	MItDependencyNodes fileIterator(MFn::kFileTexture, &status);
	if (M_OK2)
	{
		for (; !fileIterator.isDone(); fileIterator.next())
		{
			MFnDependencyNode dgNode(fileIterator.thisNode(), &status);
			if (M_FAIL2)
				continue;

			MObject node = fileIterator.thisNode();

			MCallbackId id = MNodeMessage::addAttributeChangedCallback(node, fileTextureAttributeChanged, nullptr, &status);
			if (M_OK2)
			{
				std::string textureNodeName = dgNode.name().asChar();
				addCallbackDelOld(textureNodeName + "FileTextureChanged", id);
			}
		}
	}

	// MATERIALS
	MItDependencyNodes matIterator(MFn::kLambert, &status);
	if (M_OK2)
	{
		for (; !matIterator.isDone(); matIterator.next())
		{
			MFnDependencyNode dgNode(matIterator.thisNode());
			std::string name = dgNode.name().asChar();
			MObject node = matIterator.thisNode();

			id = MNodeMessage::addAttributeChangedCallback(node, materialAttributeChanged, NULL, &status);
			if (M_OK2)
				addCallback(name + "MaterialChanged", id);

			//setFileCallbacks(node);

			SendMaterialData(dgNode, producerBuffer);
		}
	}

	// MESHES
	MItDag meshIterator(MItDag::kBreadthFirst, MFn::kMesh, &status);
	for (; !meshIterator.isDone(); meshIterator.next())
	{
		MFnDependencyNode dgNode(meshIterator.currentItem(), &status);
		std::string name = dgNode.name().asChar();

		MObject node(meshIterator.currentItem());

		if (node.hasFn(MFn::kMesh))
		{
			id = MPolyMessage::addPolyTopologyChangedCallback(node, meshTopoChanged, nullptr, &status);
			if (M_OK2)
				addCallback(name + "TopoChanged", id);

			id = MNodeMessage::addAttributeChangedCallback(node, meshAttributeChanged, nullptr, &status);
			if (M_OK2)
				addCallback(name + "AttriChanged", id);

			MCallbackId id = MNodeMessage::addAttributeChangedCallback(node, meshSetMaterial, nullptr, &status);
			if (M_OK2)
				addCallback(name + "MeshMatAttriChanged", id);

			sendMesh(node, producerBuffer);
			sendAttachedMaterial(node, producerBuffer);
		}
	}

	// TRANSFORMS
	MItDag transIterator(MItDag::kBreadthFirst, MFn::kTransform, &status);
	for (; !transIterator.isDone(); transIterator.next())
	{
		MFnDependencyNode dgNode(transIterator.currentItem(), &status);
		std::string name = dgNode.name().asChar();
		MObject node(transIterator.currentItem());


		MFnTransform tra(node, &status);
		if (M_OK2)
		{
			if (!tra.child(0).hasFn(MFn::kCamera))
			{
				id = MNodeMessage::addAttributeChangedCallback(node, transformAttributeChanged, NULL, &status);
				if (M_OK2)
					addCallback(name + "TranformChanged", id);

				SendTransformData(node, producerBuffer);
			}
		}
	}

	M3dView view = M3dView::active3dView();
	sendCamera(view, producerBuffer);

	MDagPath camPath;
	view.getCamera(camPath);
	MFnCamera camera(camPath, &status);
	if (M_OK2)
		SendTransformData(camera.parent(0), producerBuffer);
}

void nodeRemoved(MObject& node, void* clientData)
{
	// Nodes created in Gameplay3D are based on the MFnTransform name
	MFnTransform traNode(node, &status);
	if (M_OK2)
	{
		SectionHeader secHeader;
		secHeader.name = traNode.name(&status).asChar();
		if (M_FAIL2)
			return;

		secHeader.header = NODE_DELETE;
		secHeader.messageLength = 0;

		producerBuffer->Send(nullptr, &secHeader);
	}

}

void nodeAdded(MObject& node, void* clientData)
{
	// Switch to MFnDagNode ? hmmmm	
	MFnDagNode dagNode(node, &status);
	if (M_OK2)
	{
		MCallbackId id;
		std::string name = dagNode.name().asChar();

		id = MNodeMessage::addNameChangedCallback(node, nodeNameChange, nullptr, &status);
		if (M_OK2)
			addCallback(name + "NameChanged", id);

		if (node.hasFn(MFn::kMesh))
		{
			id = MNodeMessage::addNodeDirtyPlugCallback(node, meshDirtyPlug, nullptr, &status);
			if (M_OK2)
				addCallback(name + "DirtyPlug", id);

			id = MPolyMessage::addPolyTopologyChangedCallback(node, meshTopoChanged, nullptr, &status);
			if (M_OK2)
				addCallback(name + "TopoChanged", id);

			id = MNodeMessage::addAttributeChangedCallback(node, meshAttributeChanged, nullptr, &status);
			if (M_OK2)
				addCallback(name + "AttriChanged", id);

			MCallbackId id = MNodeMessage::addAttributeChangedCallback(node, meshSetMaterial, nullptr, &status);
			if (M_OK2)
				addCallback(name + "MeshMatAttriChanged", id);
		}

		if (node.hasFn(MFn::kTransform))
		{
			id = MNodeMessage::addAttributeChangedCallback(node, transformAttributeChanged, NULL, &status);
			if (M_OK2)
				addCallback(name + "TranformChanged", id);
		}

	}

	MFnDependencyNode dgNode(node, &status);
	if (M_OK2)
	{
		MCallbackId id;
		std::string name = dgNode.name().asChar();

		if (node.hasFn(MFn::kLambert))
		{
			//setFileCallbacks(node);
			id = MNodeMessage::addAttributeChangedCallback(node, materialAttributeChanged, NULL, &status);
			if (M_OK2)
				addCallback(name + "MaterialChanged", id);

			//SendMaterialData(material, producerBuffer);
		}

		if (node.hasFn(MFn::kFileTexture))
		{
			id = MNodeMessage::addAttributeChangedCallback(node, fileTextureAttributeChanged, nullptr, &status);
			if (M_OK2)
				addCallbackDelOld(name + "FileTextureChanged", id);
			
		}

	}

}


EXPORT MStatus initializePlugin(MObject obj) {

	MStatus res = MS::kSuccess;

	MFnPlugin myPlugin(obj, "level editor", "1.0", "Any", &res);

	if (MFAIL(res)) {
		CHECK_MSTATUS(res);
		return res;
	}

	std::cout.set_rdbuf(MStreamUtils::stdOutStream().rdbuf());
	std::cerr.set_rdbuf(MStreamUtils::stdErrorStream().rdbuf());
	std::cout << "\n\n\n\nPlugin successfully loaded\n"
		"=======================================================\n\n\n\n";

	producerBuffer = new Comlib(L"Filemap", 150, ProcessType::Producer);


	iterateScene();

	// register callbacks here for
	MCallbackId callbackId;

	callbackId = MDGMessage::addNodeAddedCallback(nodeAdded, "dependNode", NULL, &status);
	if (M_OK2)
		callbacks.insert({ "nodeCreationCB", callbackId });

	callbackId = MDGMessage::addNodeRemovedCallback(nodeRemoved, "dependNode", nullptr, &status);
	if (M_OK2)
		callbacks.insert({ "nodeRemovedCB", callbackId });

	// Cameras
	callbackId = MUiMessage::add3dViewPreRenderMsgCallback("modelPanel1", cameraMoved);
	if (M_OK2)
		callbacks.insert({ "cameraPanel1", callbackId });

	callbackId = MUiMessage::add3dViewPreRenderMsgCallback("modelPanel2", cameraMoved);
	if (M_OK2)
		callbacks.insert({ "cameraPanel2", callbackId });

	callbackId = MUiMessage::add3dViewPreRenderMsgCallback("modelPanel3", cameraMoved);
	if (M_OK2)
		callbacks.insert({ "cameraPanel3", callbackId });

	callbackId = MUiMessage::add3dViewPreRenderMsgCallback("modelPanel4", cameraMoved);
	if (M_OK2)
		callbacks.insert({ "cameraPanel4", callbackId });


	return res;
}

EXPORT MStatus uninitializePlugin(MObject obj)
{
	MFnPlugin plugin(obj);

	for (auto& id : callbacks)
	{
		MMessage::removeCallback(id.second);
	}

	delete producerBuffer;

	std::cout << "Plugin unloaded\n"
		"=======================================================" << std::endl;

	return MS::kSuccess;
}
