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

			if (!_scene->findNode(mainHeader->nodeName))
				createNode(meshInfo, msg + sizeof(MeshInfoHeader), mainHeader->nodeName);
			else
				recreateMesh(meshInfo, msg + sizeof(MeshInfoHeader), mainHeader->nodeName);

			break;
		}
		case MESH_UPDATE:
		{
			MeshUpdateHeader header;
			memcpy(&header, msg, sizeof(MeshUpdateHeader));

			if (_scene->findNode(mainHeader->nodeName))
				updateMesh(header, mainHeader->nodeName);
			else
				OutputDebugString(L"Could not find node...\n");

			break;
		}
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

void MayaViewer::setMatDefaults(Model* pModel)
{
	Material* pMat = pModel->setMaterial( "res/shaders/textured.vert", "res/shaders/textured.frag", "POINT_LIGHT_COUNT 1");
	pMat->setParameterAutoBinding("u_worldViewProjectionMatrix", "WORLD_VIEW_PROJECTION_MATRIX");
	pMat->setParameterAutoBinding("u_inverseTransposeWorldViewMatrix", "INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX");
	pMat->getParameter("u_ambientColor")->setValue(Vector3(0.2f, 0.2f, 0.2f));
	pMat->getParameter("u_pointLightColor[0]")->setValue(light->getColor());
	pMat->getParameter("u_pointLightPosition[0]")->bindValue(light->getNode(), &Node::getTranslationWorld);
	pMat->getParameter("u_pointLightRangeInverse[0]")->bindValue(light, &Light::getRangeInverse);
	pMat->getStateBlock()->setCullFace(true);
	pMat->getStateBlock()->setDepthTest(true);
	pMat->getStateBlock()->setDepthWrite(true);

    Texture::Sampler* pSampler = pMat->getParameter("u_diffuseTexture")->setValue("res/png/crate.png", true);
    pSampler->setFilterMode(Texture::LINEAR_MIPMAP_LINEAR, Texture::LINEAR);
}

void MayaViewer::createNode(const MeshInfoHeader& header, void* pMeshData, const char* nodeName)
{
	Mesh* pMesh = createMesh(header, msg + sizeof(MeshInfoHeader));
	delete[] msg;
	
	if (!pMesh)
	{
		OutputDebugString(L"Failed to create mesh...\n");
		return;
	}
	
	Node* pNode = _scene->addNode(mainHeader->nodeName.cStr);

	Model* pModel = Model::create(pMesh);
	if (!pModel)
	{
		OutputDebugString(L"Failed to create model...\n");
		return;
	}

	setMatDefaults(pModel);
	
	pNode->setDrawable(pModel);
	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pModel);
}

void MayaViewer::recreateMesh(const MeshInfoHeader& header, void* pMeshData, const char* nodeName)
{
	Node* pNode = _scene->findNode(nodeName);
	if (!pNode)
	{
		OutputDebugString(L"Couldn't find node...\n");
		return;
	}

	Model* pModel = dynamic_cast<Model*>(pNode->getDrawable());
	if (!pModel)
	{
		OutputDebugString(L"Couldn't get drawble...\n");
		return;
	}

	Mesh* pMesh = pModel->getMesh();
	if (!pMesh)
	{
		OutputDebugString(L"Couldn't get mesh...\n");
		return;
	}

	pMesh = createMesh(header, pMeshData);
	if (!pMesh)
	{
		OutputDebugString(L"Failed to update mesh...\n");
		return;
	}

	pModel = Model::create(pMesh);
	if (!pModel)
	{
		OutputDebugString(L"Failed to create model...\n");
		return;
	}

	setMatDefaults(pModel);
	pNode->setDrawable(pModel);

	//pMesh->mapVertexBuffer();
	//pMesh->unmapVertexBuffer();
}

void MayaViewer::updateMesh(const MeshUpdateHeader& header, const char* nodeName)
{
	Node* pNode = _scene->findNode(nodeName);
	if (!pNode)
	{
		OutputDebugString(L"Couldn't find node...\n");
		return;
	}

	Model* pModel = dynamic_cast<Model*>(pNode->getDrawable());
	if (!pModel)
	{
		OutputDebugString(L"Couldn't get drawble...\n");
		return;
	}

	Mesh* pMesh = pModel->getMesh();
	if (!pMesh)
	{
		OutputDebugString(L"Couldn't get mesh...\n");
		return;
	}

	Vertex* pData = (Vertex*)pMesh->mapVertexBuffer();
	pData[header.vertexIndex] = header.newVertex;
	pMesh->unmapVertexBuffer();
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

Mesh* MayaViewer::createMesh(const MeshInfoHeader& info, void* data)
{
	VertexFormat::Element elements[] =
	{
		VertexFormat::Element(VertexFormat::POSITION, 3),
		VertexFormat::Element(VertexFormat::TEXCOORD0, 2),
		VertexFormat::Element(VertexFormat::NORMAL, 3)
	};
	Mesh* mesh = Mesh::createMesh(VertexFormat(elements, 3), info.numVertex, true);
	if (mesh == NULL)
	{
		GP_ERROR("Failed to create mesh.");
		return NULL;
	}
	mesh->setVertexData(data, 0, info.numVertex);
	//MeshPart* meshPart = mesh->addPart(Mesh::TRIANGLES, Mesh::, indexCount, true);
	//meshPart->setIndexData(indices, 0, indexCount);
	return mesh;
}