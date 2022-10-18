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
    // broh
    std::unordered_map<std::string, bool> colored;

    /**
     * Draws the scene each frame.
     */
    bool drawScene(Node* node);

    // Helpers
    Mesh* createMesh(const MeshInfoHeader& info, void* data);
	Mesh* createCubeMesh(float size = 1.0f);

	void setMaterial(const MaterialDataHeader& header, const char* materialName);
	void setMaterial(const TextureDataHeader& header, const char* materialName);
   // void setMaterial(const MaterialDataHeader& header, const char* nodeName);
   // void setMaterial(const TextureDataHeader& header, const char* nodeName);
    void setShadingParameters(Material* pModel);

    void setDefaultMat(Model* pModel);

    void createNode(const MeshInfoHeader& header, void* pMeshData, const char* nodeName);
    void recreateMesh(const MeshInfoHeader& header, void* pMeshData, const char* nodeName);
    void updateMesh(const MeshUpdateHeader& header, const char* nodeName);
    void setTransform(const float* matrix, const char* nodeName);
    void setCamera(const CameraHeader& camHeader, const char* nodeName);

    Camera* createCamera(const CameraHeader& cameraHeader);

    // temp
    Light* light;

    Technique* colour;
    Technique* texture;

    void foo();

};

#endif
