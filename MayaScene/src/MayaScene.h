#ifndef MayaViewer_H_
#define MayaViewer_H_

#include "gameplay.h"
#include "../../Memory/Comlib.h"

using namespace gameplay;

/**
 * Main game class.
 */
class MayaViewer: public Game
{
public:

    /**
     * Constructor.
     */
    MayaViewer();

    /**
     * Deconstructor.
     */
    ~MayaViewer();

    /**
     * @see Game::keyEvent
     */
	void keyEvent(Keyboard::KeyEvent evt, int key);
	
    /**
     * @see Game::touchEvent
     */
    void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

	// mouse events
	bool mouseEvent(Mouse::MouseEvent evt, int x, int y, int wheelDelta);


protected:

    /**
     * @see Game::initialize
     */
    void initialize();

    /**
     * @see Game::finalize
     */
    void finalize();

    /**
     * @see Game::update
     */
    void update(float elapsedTime);

    /**
     * @see Game::render
     */
    void render(float elapsedTime);

private:
    
    Scene* _scene;
    bool _wireframe;

    // Message handling
    Comlib* consumerBuffer;
    char* msg;
    SectionHeader* mainHeader;

    std::unordered_map<std::string, Material*> materials;

    /**
     * Draws the scene each frame.
     */
    bool drawScene(Node* node);

    // Helpers
    Mesh* createMesh(const MeshInfoHeader& info, void* data);
	Mesh* createCubeMesh(float size = 1.0f);
	Material* createMaterial(const MaterialDataHeader& header, void* pMatdata, const char* nodeName);


    void setMatDefaults(Model* pModel);
    void setMaterial(const MaterialDataHeader& header, void* pMatdata, const char* nodeName);
    void createNode(const MeshInfoHeader& header, void* pMeshData, const char* nodeName);
    void recreateMesh(const MeshInfoHeader& header, void* pMeshData, const char* nodeName);
    void updateMesh(const MeshUpdateHeader& header, const char* nodeName);
    void setTransform(const TransformDataHeader& matrix, const char* nodeName);

    Camera* createCamera(const CameraHeader& cameraHeader);

    // temp
    Light* light;

};

#endif
