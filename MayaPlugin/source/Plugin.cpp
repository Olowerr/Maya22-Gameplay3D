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
#if PRINT_EXTRA
	std::cout << "MESH ATTRI | ";
	PRINT_MSG(msg);
	printPlugPath(plug);
	printPlugPath(otherPlug);
#endif
	if (msg & MNodeMessage::AttributeMessage::kAttributeSet)
	{
		MFnMesh mesh(plug.node(), &status);
		if (M_FAIL2)
			return;

		std::string nodeName = mesh.name().asChar();
		std::string plugName = plug.name().asChar();
		
		if (plugName.find(".pnts[") != -1)
		{
#if PRINT_SENDS
			std::cout << nodeName << " | Updating mesh attribute\n";
#endif
			if (!sendUpdateMesh(plug.logicalIndex(), plug.node(), producerBuffer))
				std::cout << nodeName << " | Failed updating mesh attribute\n";
		}

	}
	/*else if (msg & MNodeMessage::AttributeMessage::kAttributeEval)
	{
		MFnMesh mesh(plug.node(), &status);
		if (M_FAIL2)
			return;

		std::string nodeName = mesh.name().asChar();
		std::string plugName = plug.name().asChar();

		if (plugName.find(".outMesh") != -1)
		{
			std::cout << "OUT MESH\n";
		}
	}*/

#if PRINT_EXTRA
	std::cout << "\n";
#endif
}

void meshTopoAttributeChanged(MNodeMessage::AttributeMessage msg, MPlug& plug, MPlug& otherPlug, void* clientData)
{
#if PRINT_EXTRA
	std::cout << "TOPO ATTRI | ";
	PRINT_MSG(msg);
	printPlugPath(plug);
	printPlugPath(otherPlug);
#endif

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
#if PRINT_SENDS
				std::cout << nodeName << " | Updating mesh topology...\n";
#endif
				if (!sendMesh(plug.node(), producerBuffer))
					std::cout << nodeName << " | Failed updating mesh topology...\n";
			}
		}
	}

#if PRINT_EXTRA
	std::cout << "\n";
#endif
}

void materialDirtyPlug(MObject& node, MPlug& plug, void* clientData)
{
	if (node.hasFn(MFn::kLambert))
	{
		MFnDependencyNode material(plug.node());
		std::cout << material.name() << std::endl;

		MFnLambertShader lambert(node, &status);
		if (M_OK2)
		{
			
		}
	}
}

void textureAttributeChanged(MNodeMessage::AttributeMessage msg, MPlug& plug, MPlug& otherPlug, void* clientData)
{
	if (msg & MNodeMessage::kAttributeSet)
	{
		MFnDependencyNode dgNode(plug.node(), &status);
		if (M_FAIL2)
			return;
		
		MPlug outColor = dgNode.findPlug("outColor", false, &status);
		if (M_FAIL2)
			return;

		MPlugArray connections;
		outColor.connectedTo(connections, false, true, &status);
		if (M_FAIL2)
			return;

		for (int i = 0; i < connections.length(); i++)
		{
			MFnDependencyNode material(connections[i].node(), &status);
			if (M_OK2)
			{
				SendMaterialData(material, producerBuffer);
			}
		}	
	}
}

void materialAttributeChanged(MNodeMessage::AttributeMessage msg, MPlug& plug, MPlug& otherPlug, void* x)
{
	if (msg & MNodeMessage::kConnectionMade)
	{
		MObject node = plug.node();
		MObject otherNode = otherPlug.node();
		MFnDependencyNode material(node);

		if (otherNode.hasFn(MFn::kShadingEngine))
		{
			MFnDependencyNode material(otherPlug.node());
			
			SendMaterialData(material, producerBuffer);

			/*MFnMesh mesh(plug.node(), &status);
			MFnDagNode dag(mesh.parent(0), &status);
			std::string nodeName = dag.name(&status).asChar();

			MCallbackId id = MNodeMessage::addNodeDirtyPlugCallback(connection, materialDirtyPlug, nullptr, &status);
			if (M_OK2)
				addCallback(nodeName + "DirtyMaterialPlug", id);*/
		}

		if (otherNode.hasFn(MFn::kFileTexture))
		{
			MCallbackId id = MNodeMessage::addAttributeChangedCallback(otherNode, textureAttributeChanged, nullptr, &status);
			if (M_OK2)
			{
				std::string textureNodeName = MFnDependencyNode(otherPlug.node()).name().asChar();
				addCallback(textureNodeName + "FileTextureChanged", id);
			}
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
	//if (msg & MNodeMessage::kAttributeSet)
	//{
	//	cout << "hej" << endl;
	//	if (otherPlug.node().hasFn(MFn::kLambert))
	//	{
	//		cout << "hej" << endl;
	//		MFnDependencyNode material(otherPlug.node());
	//		std::cout << material.name() << std::endl;

	//		MPlugArray connections;
	//		MPlug shaderPlug = material.findPlug("surfaceShader", false);
	//		shaderPlug.connectedTo(connections, true, false);

	//		for (size_t i = 0; i < connections.length(); i++)
	//		{
	//			MObject connection(connections[i].node());
	//			if (connection.hasFn(MFn::kLambert))
	//			{
	//				MFnLambertShader tempLamb(connection);
	//				std::cout << "Lambert material name: " << tempLamb.name() << std::endl;
	//				tempLamb.hasAttribute("Color", &status);
	//				if (M_OK2)
	//				{
	//					SendMaterialData(tempLamb, producerBuffer, plug.node());
	//				}
	//			}
	//		}
	//	}
	//}
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
			std::cout << "hello?\n";
			printPlugPath(plug);

			MObject materialNode = getMaterial(plug);
			if (!materialNode.hasFn(MFn::kLambert))
				return;

			MFnDependencyNode dgNode(materialNode, &status);
			if (M_FAIL2)
				return;

			const char* materialName = dgNode.name().asChar();
			const char* nodeName = MFnDependencyNode(plug.node()).name().asChar();
			std::cout << "Mattt: " << materialName << "\n";

			sendAttachedMaterial(materialName, nodeName, producerBuffer);

			std::cout << "SENDING\n";
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
#if PRINT_EXTRA
	std::cout << "MESH DIRTY | ";
	printPlugPath(plug);
#endif
	
	MFnMesh mesh(node, &status);
	if (M_OK2)
	{
		std::string nodeName = mesh.name().asChar();

		if (std::string(plug.name().asChar()).find(".inMesh") != -1)
		{
			removeCallback(nodeName + "DirtyPlug");
#if PRINT_SENDS
			std::cout << nodeName << " | Sending mesh\n";
#endif

			if (!sendMesh(node, producerBuffer))
				std::cout << nodeName << " | Failed creating mesh...\n";


			MCallbackId id = MNodeMessage::addAttributeChangedCallback(node, meshSetMaterial, nullptr, &status);
			if (M_OK2)
				addCallback(nodeName + "MeshMatAttriChanged", id);


			// Send which material to use
			/*printPlugPath(plug);

			std::cout << "0" << "\n";
			MObject materialNode = getMaterial(node);
			if (!materialNode.hasFn(MFn::kLambert))
				return;

			std::cout << "1" << "\n";
			MFnDependencyNode dgNode(materialNode, &status);
			if (M_FAIL2)
				return;

			const char* materialName = dgNode.name().asChar();
			const char* nodeName = MFnDependencyNode(plug.node()).name().asChar();
			std::cout << "Matt: " << materialName << "\n";

			sendAttachedMaterial(materialName, nodeName, producerBuffer);

			std::cout << "SENDING\n";*/

			/*MItMeshVertex it(node, &status);
			if (M_FAIL2)
				return;

			MVector normal;
			float2 uv;

			std::cout <<"Num: "<< it.count() << "\n";
			for (; !it.isDone(); it.next())
			{
				std::cout << it.index() << ":\n";

				it.getNormal(normal);
				it.getUV(uv);

				printVector(it.position());
				printVector(normal);
				printVector(uv);
				std::cout << "---\n";
			}*/

			/*MItMeshFaceVertex it2(node, &status);
			if (M_FAIL2)
				return;

			MVector normal;
			float2 uv;
			int c = 0;
			for (; !it2.isDone(); it2.next(), c++)
			{
				std::cout << it2.vertId() << ", " << it2.faceId() << ":\n";

				it2.getNormal(normal);
				it2.getUV(uv);

				printVector(it2.position());
				printVector(normal);
				printVector(uv);
				std::cout << "---\n";
			}
			std::cout << "num: " << c << "\n";*/
		}
	}

#if PRINT_EXTRA
	std::cout << "\n";
#endif
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
		// Could just create a CharString...

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
			else
				std::cout << name << " | Failed creating material...\n";

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

			id = MNodeMessage::addAttributeChangedCallback(node, materialAttributeChanged, NULL, &status);
			if (M_OK2)
				addCallback(name + "MaterialChanged", id);

			id = MNodeMessage::addNodeDirtyPlugCallback(node, materialDirtyPlug, nullptr, &status);
			if (M_OK2)
				addCallback(name + "DirtyMaterialPlug", id);


			if (!sendMesh(node, producerBuffer))
				std::cout << name << " | Failed creating mesh...\n";
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

				if (!SendTransformData(node, producerBuffer))
					std::cout << name << " | Failed sending transform...\n";
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
			//id = MNodeMessage::addNodeDirtyPlugCallback(node, materialDirtyPlug, nullptr, &status);
			//if (M_OK2)
			//	addCallback(name + "DirtyMaterialPlug", id);

			id = MNodeMessage::addAttributeChangedCallback(node, materialAttributeChanged, NULL, &status);
			if (M_OK2)
				addCallback(name + "MaterialChanged", id);

			SendMaterialData(dgNode, producerBuffer);
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
		callbacks.insert({ "cameraPanel1", callbackId});

	callbackId = MUiMessage::add3dViewPreRenderMsgCallback("modelPanel2", cameraMoved);
	if (M_OK2)
		callbacks.insert({ "cameraPanel2", callbackId});

	callbackId = MUiMessage::add3dViewPreRenderMsgCallback("modelPanel3", cameraMoved);
	if (M_OK2)
		callbacks.insert({ "cameraPanel3", callbackId});

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
		std::cout << "Unloading \"" << id.first << "\" with ID: " << id.second << std::endl;
		MMessage::removeCallback(id.second);
	}

	delete producerBuffer;

	std::cout << "Plugin unloaded\n"
		"=======================================================" << std::endl;

	return MS::kSuccess;
}
