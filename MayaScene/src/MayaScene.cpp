#include "MayaScene.h"

// Declare our game instance
MayaViewer game;

static bool gKeys[256] = {};
int gDeltaX;
int gDeltaY;
bool gMousePressed;

MayaViewer::MayaViewer()
	: _scene(NULL), _wireframe(false)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

MayaViewer::~MayaViewer()
{
	delete consumerBuffer;
	SAFE_RELEASE(light);

	std::vector<Node*> nodes;
	_scene->findNodes("", nodes, true, false);

	for (Node* node : nodes)
	{
		node->setDrawable(nullptr);
		node->setCamera(nullptr);
		node->setLight(nullptr);
	}

	_scene->removeAllNodes();
}

void MayaViewer::initialize()
{
	consumerBuffer = new Comlib(L"Filemap", 150, ProcessType::Consumer);

	// Load game scene from file
	_scene = Scene::create();

	Camera* cam = Camera::createPerspective(45.0f, getAspectRatio(), 1.0, 100.0f);
	Node* cameraNode = _scene->addNode("camera");

	cameraNode->setCamera(cam);
	_scene->setActiveCamera(cam);
	SAFE_RELEASE(cam);

	cameraNode->translate(0, 0, 20);
	cameraNode->rotateX(MATH_DEG_TO_RAD(0.f));

	Node* lightNode = _scene->addNode("light");
	light = Light::createPoint(Vector3(1.f, 1.0f, 1.0f), 50);
	lightNode->setLight(light);
	lightNode->translate(Vector3(0, 1, 5));
}

void MayaViewer::finalize()
{
	SAFE_RELEASE(_scene);	
}

void MayaViewer::update(float elapsedTime)
{
	while (consumerBuffer->Recieve(msg, mainHeader))
	{
		switch (mainHeader->header)
		{
		default:
			break;

		case MESH_NEW:
		{
			MeshInfoHeader meshInfo;
			memcpy(&meshInfo, msg, sizeof(MeshInfoHeader));

			if (!_scene->findNode(mainHeader->name))
				createNode(meshInfo, msg + sizeof(MeshInfoHeader), mainHeader->name);
			else
				recreateMesh(meshInfo, msg + sizeof(MeshInfoHeader), mainHeader->name);

			break;
		}
		case MESH_UPDATE:
		{
			MeshInfoHeader meshInfo;
			memcpy(&meshInfo, msg, sizeof(MeshInfoHeader));

			if (_scene->findNode(mainHeader->name))
				updateMesh(msg + sizeof(MeshInfoHeader), meshInfo, mainHeader->name);
			else
				OutputDebugString(L"MESH_UPDATE | Could not find node...\n");

			break;
		}
		case TRANSFORM_DATA:
		{
			TransformDataHeader transHeader;
			memcpy(&transHeader, msg, sizeof(TransformDataHeader));

			if (_scene->findNode(mainHeader->name))
				setTransform(*transHeader.transMtrx, mainHeader->name);
			else
				OutputDebugString(L"TRANSFORM_DATA | Could not find node...\n");

			break;
		}
		case MESH_MATERIAL:
		{
			MeshMaterialHeader header;
			memcpy(&header, msg, sizeof(MeshMaterialHeader));
			Node* pNode = _scene->findNode(mainHeader->name);
			if (!pNode)
				break;

			Model* pModel = dynamic_cast<Model*>(pNode->getDrawable());
			if (!pModel)
				break;

			attachMaterial(mainHeader->name, header.materialName);

			break;
		}
		case MATERIAL_DATA:
		{
			MaterialDataHeader matHeader;
			memcpy(&matHeader, msg, sizeof(MaterialDataHeader));

			setMaterial(matHeader, mainHeader->name);

			break;
		}
		case COLOR_TEXTURE:
		{
			TextureDataHeader matHeader;
			memcpy(&matHeader, msg, sizeof(TextureDataHeader));

			setMaterial(matHeader, mainHeader->name, true);

			break;
		}
		case NORMAL_TEXTURE:
		{
			TextureDataHeader matHeader;
			memcpy(&matHeader, msg, sizeof(TextureDataHeader));

			setMaterial(matHeader, mainHeader->name, false);

			break;
		}
		case CAMERA_DATA:
		{
			CameraHeader camHeader;
			memcpy(&camHeader, msg, sizeof(CameraHeader));

			setCamera(camHeader, mainHeader->name);

			break;
		}
		case NODE_DELETE:
		{
			Node* pNode = _scene->findNode(mainHeader->name);
			if (pNode)
			{
				pNode->setDrawable(nullptr);
				pNode->setCamera(nullptr);
				pNode->setLight(nullptr);
				_scene->removeNode(pNode);
			}

			break;
		}
		case NAME_CHANGE:
		{
			Node* pNode = _scene->findNode(mainHeader->name);
			if (pNode)
			{
				NameChangeHeader name;
				memcpy(&name, msg, sizeof(NameChangeHeader));

				pNode->setId(name.newName);
			}
			break;
		}
		}

		if (msg)
		{
			delete[] msg;
			msg = nullptr;
		}
	}
}

Camera* MayaViewer::createCamera(const CameraHeader& cameraHeader)
{
	const float AspectRatio = cameraHeader.width / cameraHeader.height;
	return cameraHeader.perspective ?
		Camera::createPerspective(cameraHeader.fieldOfView, AspectRatio, 0.1f, 5000.f) :
		Camera::createOrthographic(cameraHeader.width, cameraHeader.height, AspectRatio, 0.1f, 5000.f);
}

void MayaViewer::render(float elapsedTime)
{
	// Clear the color and depth buffers
	clear(CLEAR_COLOR_DEPTH, Vector4(0.1f, 0.0f, 0.0f, 1.0f), 1.0f, 0);

	// Visit all the nodes in the scene for drawing
	_scene->visit(this, &MayaViewer::drawScene);
}

bool MayaViewer::drawScene(Node* node)
{
	// If the node visited contains a drawable object, draw it
	Drawable* drawable = node->getDrawable();
	if (drawable)
		drawable->draw(_wireframe);

	return true;
}

void MayaViewer::createTexturedMaterial(Model* pModel, bool hasNormal)
{
	Material* pMat;
	if (hasNormal)
	{
		pMat = pModel->setMaterial("res/shaders/normTex.vert", "res/shaders/normTex.frag", "POINT_LIGHT_COUNT 1");
	}
	else
	{
		pMat = pModel->setMaterial("res/shaders/textured.vert", "res/shaders/textured.frag", "POINT_LIGHT_COUNT 1");
	}

	pMat->setParameterAutoBinding("u_worldViewProjectionMatrix", "WORLD_VIEW_PROJECTION_MATRIX");
	pMat->setParameterAutoBinding("u_inverseTransposeWorldViewMatrix", "INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX");
	pMat->getParameter("u_ambientColor")->setValue(Vector3(0.1f, 0.1f, 0.1f));
	pMat->getParameter("u_pointLightColor[0]")->setValue(light->getColor());
	pMat->getParameter("u_pointLightPosition[0]")->bindValue(light->getNode(), &Node::getTranslationWorld);
	pMat->getParameter("u_pointLightRangeInverse[0]")->bindValue(light, &Light::getRangeInverse);
	pMat->getStateBlock()->setCullFace(true);
	pMat->getStateBlock()->setDepthTest(true);
	pMat->getStateBlock()->setDepthWrite(true);
}

void MayaViewer::createColoredMaterial(Model* pModel)
{
	Material* pMat = pModel->setMaterial("res/shaders/colored.vert", "res/shaders/colored.frag", "POINT_LIGHT_COUNT 1");
	pMat->setParameterAutoBinding("u_worldViewProjectionMatrix", "WORLD_VIEW_PROJECTION_MATRIX");
	pMat->setParameterAutoBinding("u_inverseTransposeWorldViewMatrix", "INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX");
	pMat->getParameter("u_ambientColor")->setValue(Vector3(0.1f, 0.1f, 0.1f));
	pMat->getParameter("u_diffuseColor")->setValue(Vector4(1.0f, 1.0f, 1.0f, 1.f));
	pMat->getParameter("u_pointLightColor[0]")->setValue(light->getColor());
	pMat->getParameter("u_pointLightPosition[0]")->bindValue(light->getNode(), &Node::getTranslationWorld);
	pMat->getParameter("u_pointLightRangeInverse[0]")->bindValue(light, &Light::getRangeInverse);
	pMat->getStateBlock()->setCullFace(true);
	pMat->getStateBlock()->setDepthTest(true);
	pMat->getStateBlock()->setDepthWrite(true);
}

void MayaViewer::createNode(const MeshInfoHeader& header, void* pMeshData, const char* nodeName)
{
	Mesh* pMesh = createMesh(header, pMeshData);
	if (!pMesh)
	{
		OutputDebugString(L"createNode | Failed to create mesh...\n");
		return;
	}

	Node* pNode = _scene->addNode(mainHeader->name.cStr);

	Model* pModel = Model::create(pMesh);
	SAFE_RELEASE(pMesh);

	if (!pModel)
	{
		OutputDebugString(L"createNode | Failed to create model...\n");
		return;
	}

	createColoredMaterial(pModel);

	pNode->setDrawable(pModel);
	SAFE_RELEASE(pModel);
}

void MayaViewer::recreateMesh(const MeshInfoHeader& header, void* pMeshData, const char* nodeName)
{
	Node* pNode = _scene->findNode(nodeName);
	if (!pNode)
	{
		OutputDebugString(L"recreateMesh | Couldn't find node...\n");
		return;
	}

	Mesh* pMesh = createMesh(header, pMeshData);
	if (!pMesh)
	{
		OutputDebugString(L"recreateMesh | Failed to create new mesh...\n");
		return;
	}

	Model* pOldModel = dynamic_cast<Model*>(pNode->getDrawable());
	if (!pOldModel)
	{
		OutputDebugString(L"recreateMesh | Failed to get old model...\n");
		return;
	}

	Material* pMaterial = pOldModel->getMaterial();
	if (!pMaterial)
	{
		OutputDebugString(L"recreateMesh | Failed to get material...\n");
		return;
	}

	Model* pModel = Model::create(pMesh);
	if (!pModel)
	{
		OutputDebugString(L"recreateMesh | Failed to create new model...\n");
		return;
	}

	pModel->setMaterial(pMaterial);
	pNode->setDrawable(pModel);

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pModel);
}

void MayaViewer::updateMesh(char* meshData, const MeshInfoHeader& meshInfo, const char* nodeName)
{
	Node* pNode = _scene->findNode(nodeName);
	if (!pNode)
	{
		OutputDebugString(L"updateMesh | Couldn't find node...\n");
		return;
	}

	Model* pModel = dynamic_cast<Model*>(pNode->getDrawable());
	if (!pModel)
	{
		OutputDebugString(L"updateMesh | Couldn't get drawble...\n");
		return;
	}

	Mesh* pMesh = pModel->getMesh();
	if (!pMesh)
	{
		OutputDebugString(L"updateMesh | Couldn't get mesh...\n");
		return;
	}
	
	const size_t vertexBytes = meshInfo.numVertex * sizeof(Vertex);

	void* pOldVertexData = pMesh->mapVertexBuffer();
	memcpy(pOldVertexData, meshData, vertexBytes);
	pMesh->unmapVertexBuffer();
	
	void* pOldIndexData = pMesh->getPart(0)->mapIndexBuffer();
	memcpy(pOldIndexData, meshData + vertexBytes, meshInfo.numIndex * sizeof(int));
	pMesh->getPart(0)->unmapIndexBuffer();
}

void MayaViewer::setTransform(const float* matrix, const char* nodeName)
{
	Node* pNode = _scene->findNode(mainHeader->name);
	if (!pNode)
	{
		OutputDebugString(L"setTransform | Could not find node...\n");
		return;
	}

	Matrix mtrx = Matrix(matrix);
	Vector3* translate = new Vector3;
	Vector3* scale = new Vector3;
	Quaternion* rotation = new Quaternion;
	mtrx.decompose(scale, rotation, translate);

	Matrix* rotMtrx = new Matrix;
	Matrix::createRotation(*rotation, rotMtrx);

	pNode->setTranslation(*translate);
	pNode->setScale(*scale);
	pNode->setRotation(*rotMtrx);

	delete translate;
	delete scale;
	delete rotation;
	delete rotMtrx;
}

void MayaViewer::setCamera(const CameraHeader& camHeader, const char* nodeName)
{
	const float AspectRatio = camHeader.width / camHeader.height;

	Node* pNode = _scene->findNode(mainHeader->name);
	if (!pNode)
		pNode = _scene->addNode(mainHeader->name);

	setTransform(*camHeader.viewMatrix, mainHeader->name);

	Camera* pCamera = pNode->getCamera();
	if (!pCamera)
	{
		pCamera = createCamera(camHeader);
		pNode->setCamera(pCamera);
		pCamera->release();
	}
	else
	{
		pCamera = pNode->getCamera();
		pCamera->setAspectRatio(AspectRatio);

		if (camHeader.perspective)
			pCamera->setFieldOfView(camHeader.fieldOfView);
		else
		{
			pCamera->setZoomX(camHeader.width);
			pCamera->setZoomY(camHeader.height);
		}
	}

	if (_scene->getActiveCamera() != pCamera) // maybe if-statement is unnecessary...
		_scene->setActiveCamera(pNode->getCamera());
}

void MayaViewer::keyEvent(Keyboard::KeyEvent evt, int key)
{
	if (key >= 256)
		return;

	if (evt == Keyboard::KEY_PRESS)
	{
		gKeys[key] = true;
		switch (key)
		{
		case Keyboard::KEY_ESCAPE:
			exit();
			break;
		};
	}
	else if (evt == Keyboard::KEY_RELEASE)
	{
		gKeys[key] = false;
	}
}

bool MayaViewer::mouseEvent(Mouse::MouseEvent evt, int x, int y, int wheelDelta)
{
	static int lastX = 0;
	static int lastY = 0;
	gDeltaX = lastX - x;
	gDeltaY = lastY - y;
	lastX = x;
	lastY = y;
	gMousePressed =
		(evt == Mouse::MouseEvent::MOUSE_PRESS_LEFT_BUTTON) ? true :
		(evt == Mouse::MouseEvent::MOUSE_RELEASE_LEFT_BUTTON) ? false : gMousePressed;

	return true;
}

void MayaViewer::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
	switch (evt)
	{
	case Touch::TOUCH_PRESS:
		_wireframe = !_wireframe;
		break;
	case Touch::TOUCH_RELEASE:
		break;
	case Touch::TOUCH_MOVE:
		break;
	};
}

void MayaViewer::attachMaterial(const char* nodeName, const char* materialName)
{
	auto mat = materials.find(materialName);
	if (mat == materials.end())
		return;

	Node* pNode = _scene->findNode(nodeName);
	if (!pNode)
		return;

	Model* pModel = dynamic_cast<Model*>(pNode->getDrawable());
	if (!pModel)
		return;


	// Materials with no diffuse but normal map, will be seen as colored, and wont try applying the normal map
	if (mat->second.colored)
	{
		createColoredMaterial(pModel);
		pModel->getMaterial()->getParameter("u_diffuseColor")->setValue(mat->second.color);

#if weHadColoredNormalMapShader
		Texture::Sampler* pSampler = pModel->getMaterial()->getParameter("u_normalmapTexture")->setValue(mat->second.normal.c_str(), true);
		pSampler->setFilterMode(Texture::LINEAR_MIPMAP_LINEAR, Texture::LINEAR);
#endif

	}
	else
	{
		bool hasNormal = mat->second.normal != "";
		createTexturedMaterial(pModel, hasNormal);

		if (mat->second.diffuse != "")
		{
			Texture::Sampler* pSampler = pModel->getMaterial()->getParameter("u_diffuseTexture")->setValue(mat->second.diffuse.c_str(), true);
			pSampler->setFilterMode(Texture::LINEAR_MIPMAP_LINEAR, Texture::LINEAR);
		}
		if (mat->second.normal != "")
		{
			Texture::Sampler* pSampler = pModel->getMaterial()->getParameter("u_normalmapTexture")->setValue(mat->second.normal.c_str(), true);
			pSampler->setFilterMode(Texture::LINEAR_MIPMAP_LINEAR, Texture::LINEAR);
		}
	}


	nodes[nodeName] = materialName;
}

void MayaViewer::setMaterial(const MaterialDataHeader& header, const char* materialName)
{
	Vector4 color = header.color;

	bool found = false;

	for (auto& material : materials)
	{
		if (material.first == materialName)
			found = true;
	}

	materials[materialName].color = color;
	materials[materialName].colored = true;
	
	for (auto& node : nodes)
	{
		if (node.second == materialName)
		{
			Node* pNode = _scene->findNode(node.first.c_str());
			if (!pNode)
				continue;

			Model* pModel = dynamic_cast<Model*>(pNode->getDrawable());
			if (!pModel)
				continue;

			createColoredMaterial(pModel);

			pModel->getMaterial()->getParameter("u_diffuseColor")->setValue(color);
		}
	}

}

void MayaViewer::setMaterial(const TextureDataHeader& header, const char* materialName, bool diffuse)
{
	bool found = false;
	if (materials.find(materialName) == materials.end())
	{
		materials[materialName].colored = false;
	}

	if (diffuse)
		materials[materialName].diffuse = header.path.cStr;
	else
		materials[materialName].normal = header.path.cStr;


	// Materials with no diffuse but normal map will be seen as colored, and not try to apply the textures
	auto& mat = materials.find(materialName);
	for (auto& node : nodes)
	{
		if (node.second == materialName)
		{
			Node* pNode = _scene->findNode(node.first.c_str());
			if (!pNode)
				continue;

			Model* pModel = dynamic_cast<Model*>(pNode->getDrawable());
			if (!pModel)
				continue;

			bool hasNormal = mat->second.normal != "";
			createTexturedMaterial(pModel, hasNormal);

			if (mat->second.diffuse != "")
			{
				Texture::Sampler* pSampler = pModel->getMaterial()->getParameter("u_diffuseTexture")->setValue(mat->second.diffuse.c_str(), true);
				pSampler->setFilterMode(Texture::LINEAR_MIPMAP_LINEAR, Texture::LINEAR);
			}

			if (mat->second.normal != "")
			{
				Texture::Sampler* pSampler = pModel->getMaterial()->getParameter("u_normalmapTexture")->setValue(mat->second.normal.c_str(), true);
				pSampler->setFilterMode(Texture::LINEAR_MIPMAP_LINEAR, Texture::LINEAR);
			}
		}
	}

	materials[materialName].colored = false;
}

Mesh* MayaViewer::createMesh(const MeshInfoHeader& info, void* data)
{
	VertexFormat::Element elements[] =
	{
		VertexFormat::Element(VertexFormat::POSITION, 3),
		VertexFormat::Element(VertexFormat::TEXCOORD0, 2),
		VertexFormat::Element(VertexFormat::NORMAL, 3),
		VertexFormat::Element(VertexFormat::TANGENT, 3),
		VertexFormat::Element(VertexFormat::BINORMAL, 3),
	};

	Mesh* mesh = Mesh::createMesh(VertexFormat(elements, 5), info.numVertex, true);
	if (mesh == NULL)
	{
		GP_ERROR("createMesh | Failed to create mesh.");
		return NULL;
	}

	mesh->setVertexData(data, 0, info.numVertex);
	MeshPart* meshPart = mesh->addPart(Mesh::TRIANGLES, Mesh::IndexFormat::INDEX32, info.numIndex, true);
	meshPart->setIndexData((char*)data + sizeof(Vertex) * info.numVertex, 0, info.numIndex);
	return mesh;
}