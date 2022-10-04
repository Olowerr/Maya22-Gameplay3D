#ifndef MayaViewer_H_
#define MayaViewer_H_

#include "gameplay.h"

#define BRO 1

#if BRO == 1
#endif
#include "../../Memory/Comlib.h"
//#include "../Comlib.h"

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

    /**
     * Draws the scene each frame.
     */
    bool drawScene(Node* node);


	Mesh* createCubeMesh(float size = 1.0f);
	Material* createMaterial();


    Scene* _scene;
    bool _wireframe;

#if BRO == 1
    Comlib* consumerBuffer;
    char* msg;
    SectionHeader* mainHeader;
#endif
};

#endif
