#include "MayaScene.h"

// Declare our game instance
MayaViewer game;

constexpr int gModelCount = 10;
static bool gKeys[256] = {};
int gDeltaX;
int gDeltaY;
bool gMousePressed;

MayaViewer::MayaViewer()
    : _scene(NULL), _wireframe(false)
{
}

MayaViewer::~MayaViewer()
{
	delete consumerBuffer;
}

void MayaViewer::initialize()
{
	consumerBuffer = new Comlib(L"Filemap",150, ProcessType::Consumer);

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

	Mesh* mesh1 = createCubeMesh(5.0);

	Model* models[gModelCount];
	Material* mats[gModelCount];
	Texture::Sampler* samplers[gModelCount];

	char nodeName[10] = {};
	for (int i = 0; i < gModelCount; i++)
	{
		models[i] = Model::create(mesh1);
		mats[i] = models[i]->setMaterial( "res/shaders/colored.vert", "res/shaders/colored.frag", "POINT_LIGHT_COUNT 1");
		mats[i]->setParameterAutoBinding("u_worldViewProjectionMatrix", "WORLD_VIEW_PROJECTION_MATRIX");
		mats[i]->setParameterAutoBinding("u_inverseTransposeWorldViewMatrix", "INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX");
		mats[i]->getParameter("u_ambientColor")->setValue(Vector3(0.4f, 0.1f, 1.f));
		mats[i]->getParameter("u_diffuseColor")->setValue(Vector4(0.1f, 1.f, 1.f, 1.f));
		mats[i]->getParameter("u_pointLightColor[0]")->setValue(lightNode->getLight()->getColor());
		mats[i]->getParameter("u_pointLightPosition[0]")->bindValue(lightNode, &Node::getTranslationWorld);
		mats[i]->getParameter("u_pointLightRangeInverse[0]")->bindValue(lightNode->getLight(), &Light::getRangeInverse);
		//samplers[i] = mats[i]->getParameter("u_diffuseTexture")->setValue("res/png/crate.png", true);
		//samplers[i]->setFilterMode(Texture::LINEAR_MIPMAP_LINEAR, Texture::LINEAR);
		mats[i]->getStateBlock()->setCullFace(true);
		mats[i]->getStateBlock()->setDepthTest(true);
		mats[i]->getStateBlock()->setDepthWrite(true);
		sprintf(nodeName, "cube%d", i);
		Node* node = _scene->addNode(nodeName);
		node->setDrawable(models[i]);
		SAFE_RELEASE(models[i]);
	}
}

void MayaViewer::finalize()
{
    SAFE_RELEASE(_scene);
}

void MayaViewer::update(float elapsedTime)
{
	static float totalTime = 0;
	totalTime += elapsedTime;
	float step = 360.0 / float(gModelCount);
	char name[10] = {};

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
			MeshUpdateHeader header;
			memcpy(&header, msg, sizeof(MeshUpdateHeader));

			if (_scene->findNode(mainHeader->name))
				updateMesh(header, mainHeader->name);
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

			/*size_t sizeTrans = strlen(mainHeader->name) + 1;
			wchar_t* transStr = new wchar_t[sizeTrans] {};
			mbstowcs(transStr, mainHeader->name, sizeTrans);

			std::wstring printThis =
				L" - Translate: " +
				std::to_wstring(translate->x) + L", " +
				std::to_wstring(translate->y) + L", " +
				std::to_wstring(translate->z) + L"\n";

			std::wstring printMe =
				L" - Scale: " +
				std::to_wstring(scale->x) + L", " +
				std::to_wstring(scale->y) + L", " +
				std::to_wstring(scale->z) + L"\n";

			std::wstring printDat =
				L" - Rotate: " +
				std::to_wstring(rotation->x) + L", " +
				std::to_wstring(rotation->y) + L", " +
				std::to_wstring(rotation->z) + L"\n";

			OutputDebugStringW(transStr);
			OutputDebugStringW(printThis.c_str());
			OutputDebugStringW(printMe.c_str());
			OutputDebugStringW(printDat.c_str());

			delete[]transStr;*/
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

			materials[header.materialName.cStr]->addRef();
			pModel->setMaterial(materials[header.materialName.cStr]);

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
			memcpy(&matHeader, msg, sizeof(MaterialDataHeader));

			setMaterial(matHeader, mainHeader->name);

			break;
		}
		case NORMAL_TEXTURE:
		{
			// temp
			break;

			TextureDataHeader matHeader;
			memcpy(&matHeader, msg, sizeof(MaterialDataHeader));

			setMaterial(matHeader, mainHeader->name);

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
				_scene->removeNode(pNode);

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

	for (int i = 0; i < gModelCount; i++)
	{
		sprintf(name, "cube%d", i);
		Node* node = _scene->findNode(name);
		if (node) {
			node->setScale(0.3f);
			node->setTranslation(
				cosf(MATH_DEG_TO_RAD(((int)totalTime / 10) % 360 + i * step))*5.0, 
				sinf(MATH_DEG_TO_RAD(((int)totalTime / 10) % 360 + i * step))*5.0,
				0.0);
		}
		if (i%2)
			node->rotateX(elapsedTime / 1000.f);
	}	

	Node* camnode = _scene->getActiveCamera()->getNode();
	if (gKeys[Keyboard::KEY_W])
		camnode->translateForward(0.5);
	if (gKeys[Keyboard::KEY_S])
		camnode->translateForward(-0.5);
	if (gKeys[Keyboard::KEY_A])
		camnode->translateLeft(0.5);
	if (gKeys[Keyboard::KEY_D])
		camnode->translateLeft(-0.5);

	if (gMousePressed) {
		camnode->rotate(camnode->getRightVectorWorld(), MATH_DEG_TO_RAD(gDeltaY / 10.0));
		camnode->rotate(camnode->getUpVectorWorld(), MATH_DEG_TO_RAD(gDeltaX / 5.0));
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
    clear(CLEAR_COLOR_DEPTH, Vector4(0.1f,0.0f,0.0f,1.0f), 1.0f, 0);

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

void MayaViewer::setShadingParameters(Material* pMaterial)
{
	pMaterial->setParameterAutoBinding("u_worldViewProjectionMatrix", "WORLD_VIEW_PROJECTION_MATRIX");
	pMaterial->setParameterAutoBinding("u_inverseTransposeWorldViewMatrix", "INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX");
	pMaterial->getParameter("u_ambientColor")->setValue(Vector3(0.2f, 0.2f, 0.2f));
	pMaterial->getParameter("u_pointLightColor[0]")->setValue(light->getColor());
	pMaterial->getParameter("u_pointLightPosition[0]")->bindValue(light->getNode(), &Node::getTranslationWorld);
	pMaterial->getParameter("u_pointLightRangeInverse[0]")->bindValue(light, &Light::getRangeInverse);
	pMaterial->getStateBlock()->setCullFace(true);
	pMaterial->getStateBlock()->setDepthTest(true);
	pMaterial->getStateBlock()->setDepthWrite(true);
}

void MayaViewer::setDefaultMat(Model* pModel)
{

	Material* pMat = pModel->setMaterial("res/shaders/colored.vert", "res/shaders/colored.frag", "POINT_LIGHT_COUNT 1");
	pMat->setParameterAutoBinding("u_worldViewProjectionMatrix", "WORLD_VIEW_PROJECTION_MATRIX");
	pMat->setParameterAutoBinding("u_inverseTransposeWorldViewMatrix", "INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX");
	pMat->getParameter("u_ambientColor")->setValue(Vector3(0.4f, 0.1f, 1.f));
	pMat->getParameter("u_diffuseColor")->setValue(Vector4(0.1f, 1.f, 1.f, 1.f));
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
	if (!pModel)
	{
		OutputDebugString(L"createNode | Failed to create model...\n");
		return;
	}

	//setDefaultMat(pModel);
	pModel->setMaterial(materials["lambert1"]);
	
	pNode->setDrawable(pModel);
	SAFE_RELEASE(pMesh);
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

	//setMatDefaults(pModel);
	pModel->setMaterial(pMaterial);
	pNode->setDrawable(pModel);

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pModel);
}

void MayaViewer::updateMesh(const MeshUpdateHeader& header, const char* nodeName)
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

	Vertex* pData = (Vertex*)pMesh->mapVertexBuffer();
	pData[header.vertexIndex] = header.newVertex;
	pMesh->unmapVertexBuffer();
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
		pNode->setCamera(createCamera(camHeader));
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

Mesh* MayaViewer::createCubeMesh(float size)
{
	float a = size * 0.5f;
	float vertices[] =
	{
		-a, -a,  a,    0.0,  0.0,  1.0,   0.0, 0.0,
		a, -a,  a,    0.0,  0.0,  1.0,   1.0, 0.0,
		-a,  a,  a,    0.0,  0.0,  1.0,   0.0, 1.0,
		a,  a,  a,    0.0,  0.0,  1.0,   1.0, 1.0,
		-a,  a,  a,    0.0,  1.0,  0.0,   0.0, 0.0,
		a,  a,  a,    0.0,  1.0,  0.0,   1.0, 0.0,
		-a,  a, -a,    0.0,  1.0,  0.0,   0.0, 1.0,
		a,  a, -a,    0.0,  1.0,  0.0,   1.0, 1.0,
		-a,  a, -a,    0.0,  0.0, -1.0,   0.0, 0.0,
		a,  a, -a,    0.0,  0.0, -1.0,   1.0, 0.0,
		-a, -a, -a,    0.0,  0.0, -1.0,   0.0, 1.0,
		a, -a, -a,    0.0,  0.0, -1.0,   1.0, 1.0,
		-a, -a, -a,    0.0, -1.0,  0.0,   0.0, 0.0,
		a, -a, -a,    0.0, -1.0,  0.0,   1.0, 0.0,
		-a, -a,  a,    0.0, -1.0,  0.0,   0.0, 1.0,
		a, -a,  a,    0.0, -1.0,  0.0,   1.0, 1.0,
		a, -a,  a,    1.0,  0.0,  0.0,   0.0, 0.0,
		a, -a, -a,    1.0,  0.0,  0.0,   1.0, 0.0,
		a,  a,  a,    1.0,  0.0,  0.0,   0.0, 1.0,
		a,  a, -a,    1.0,  0.0,  0.0,   1.0, 1.0,
		-a, -a, -a,   -1.0,  0.0,  0.0,   0.0, 0.0,
		-a, -a,  a,   -1.0,  0.0,  0.0,   1.0, 0.0,
		-a,  a, -a,   -1.0,  0.0,  0.0,   0.0, 1.0,
		-a,  a,  a,   -1.0,  0.0,  0.0,   1.0, 1.0
	};
	short indices[] =
	{
		0, 1, 2, 2, 1, 3, 4, 5, 6, 6, 5, 7, 8, 9, 10, 10, 9, 11, 12, 13, 14, 14, 13, 15, 16, 17, 18, 18, 17, 19, 20, 21, 22, 22, 21, 23
	};
	unsigned int vertexCount = 24;
	unsigned int indexCount = 36;
	VertexFormat::Element elements[] =
	{
		VertexFormat::Element(VertexFormat::POSITION, 3),
		VertexFormat::Element(VertexFormat::NORMAL, 3),
		VertexFormat::Element(VertexFormat::TEXCOORD0, 2)
	};
	Mesh* mesh = Mesh::createMesh(VertexFormat(elements, 3), vertexCount, false);
	if (mesh == NULL)
	{
		GP_ERROR("Failed to create mesh.");
		return NULL;
	}
	mesh->setVertexData(vertices, 0, vertexCount);
	MeshPart* meshPart = mesh->addPart(Mesh::TRIANGLES, Mesh::INDEX16, indexCount, false);
	meshPart->setIndexData(indices, 0, indexCount);
	return mesh;
}

void MayaViewer::setMaterial(const MaterialDataHeader& header, const char* materialName)
{
	Vector4 color = header.color;

	if (!materials.count(materialName))
	{
		materials[materialName] = Material::create("res/shaders/colored.vert", "res/shaders/colored.frag", "POINT_LIGHT_COUNT 1");
		colored[materialName] = true;
	}
	else
	{
		if (!colored[materialName])
		{
			Material* pOldMat = materials[materialName];
			pOldMat->release();

			materials[materialName] = Material::create("res/shaders/colored.vert", "res/shaders/colored.frag", "POINT_LIGHT_COUNT 1");
			colored[materialName] = true;

			std::vector<Node*> nodes;
			_scene->findNodes("", nodes, true, false);

			for (Node* pNode : nodes)
			{
				if (Model* pModel = (Model*)pNode->getDrawable())
				{
					if (pModel->getMaterial() == pOldMat)
						pModel->setMaterial(materials[materialName]);
				}
			}

		}
	}

	setShadingParameters(materials[materialName]);
	materials[materialName]->getParameter("u_diffuseColor")->setValue(color);
}

void MayaViewer::setMaterial(const TextureDataHeader& header, const char* materialName)
{
	if (!materials.count(materialName))
	{
		materials[materialName] = Material::create("res/shaders/textured.vert", "res/shaders/textured.frag", "POINT_LIGHT_COUNT 1");
		colored[materialName] = false;
	}
	else
	{
		if (colored[materialName])
		{
			Material* pOldMat = materials[materialName];
			pOldMat->release();

			materials[materialName] = Material::create("res/shaders/textured.vert", "res/shaders/textured.frag", "POINT_LIGHT_COUNT 1");
			colored[materialName] = false;

			std::vector<Node*> nodes;
			_scene->findNodes("", nodes, true, false);

			for (Node* pNode : nodes)
			{
				if (Model* pModel = dynamic_cast<Model*>(pNode->getDrawable()))
				{
					if (pModel->getMaterial() == pOldMat)
						pModel->setMaterial(materials[materialName]);
				}
			}

		}
	}

	setShadingParameters(materials[materialName]);

	Texture::Sampler* pSampler = materials[materialName]->getParameter("u_diffuseTexture")->setValue(header.path.cStr, true);
	pSampler->setFilterMode(Texture::LINEAR_MIPMAP_LINEAR, Texture::LINEAR);
}

Mesh* MayaViewer::createMesh(const MeshInfoHeader& info, void* data)
{
	std::vector<Vertex> verts(info.numVertex);
	std::vector<int> inds(info.numIndex);

	memcpy(verts.data(), data, sizeof(Vertex) * verts.size());
	memcpy(inds.data(), (char*)data + sizeof(Vertex) * verts.size(), sizeof(int) * inds.size());

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