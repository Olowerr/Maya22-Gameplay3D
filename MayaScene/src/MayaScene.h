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

    /**
     * Draws the scene each frame.
     */
    bool drawScene(Node* node);

    // Helpers
    Mesh* createMesh(const MeshInfoHeader& info, void* data);
	Mesh* createCubeMesh(float size = 1.0f);
	Material* createMaterial();

    void setMatDefaults(Model* pModel);
    void createNode(const MeshInfoHeader& header, void* pMeshData, const char* nodeName);
    void updateMesh(const MeshInfoHeader& header, void* pMeshData, const char* nodeName);



    // temp
    Light* light;

};

#endif
