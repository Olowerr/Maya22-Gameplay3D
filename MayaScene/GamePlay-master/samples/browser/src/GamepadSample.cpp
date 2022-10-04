#include "GamepadSample.h"

#if defined(ADD_SAMPLE)
    ADD_SAMPLE("Input", "Gamepads", GamepadSample, 3);
#endif

GamepadSample::GamepadSample() : _gamepad(NULL), _font(NULL)
{
}

void GamepadSample::initialize()
{
    setMultiTouch(true);

    _gamepad = getGamepad(0);
    // This is needed because the virtual gamepad is shared between all samples.
    // SamplesGame always ensures the virtual gamepad is disabled when a sample is exited.
    if (_gamepad && _gamepad->isVirtual())
        _gamepad->getForm()->setEnabled(true);

    _font = Font::create("res/ui/arial.gpb");
    _status = "Looking for gamepads...";
}

void GamepadSample::finalize()
{
    SAFE_RELEASE(_font);
}

void GamepadSample::updateGamepad(float elapsedTime, Gamepad* gamepad, unsigned int player)
{
    char s[128];
    sprintf(s, "Player: %d - %s\nButtons: ", player, gamepad->getName());
    _status += s;
    for (int i = 0; i < 20; ++i)
    {
        if (gamepad->isButtonDown((Gamepad::ButtonMapping)i))
        {
            sprintf(s, "%s ", getStringFromButtonMapping((Gamepad::ButtonMapping)i));
            _status += s;
        }
    }
    _status += "\n";
    for (unsigned int j = 0; j < gamepad->getJoystickCount(); ++j)
    {
        Vector2 joystick;
        gamepad->getJoystickValues(j, &joystick);
        sprintf(s, "Joystick %d: (%f, %f)\n", j, joystick.x, joystick.y);
        _status += s;
    }
    for (unsigned int k = 0; k < gamepad->getTriggerCount(); ++k)
    {
        sprintf(s, "Trigger %d: %f\n", k, gamepad->getTriggerValue(k));
        _status += s;
    }
    _status += "\n";
}

void GamepadSample::update(float elapsedTime)
{
    _status = "";
    if (_gamepad)
        updateGamepad(elapsedTime, _gamepad, 1);
}

void GamepadSample::render(float elapsedTime)
{
    clear(CLEAR_COLOR_DEPTH, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0);

    drawFrameRate(_font, Vector4(0, 0.5f, 1, 1), 5, 1, getFrameRate());

    _font->start();
    _font->drawText(_status.c_str(), 7, 27, Vector4::one(), 22);
    _font->finish();


    _gamepad->draw();
}

void GamepadSample::gamepadEvent(Gamepad::GamepadEvent evt, Gamepad* gamepad)
{
    switch(evt)
    {
        case Gamepad::CONNECTED_EVENT:
        case Gamepad::DISCONNECTED_EVENT:
            _gamepad = getGamepad(0);
            // This is needed because the virtual gamepad is shared between all samples.
            // SamplesGame always ensures the virtual gamepad is disabled when a sample is exited.
            if (_gamepad && _gamepad->isVirtual())
                _gamepad->getForm()->setEnabled(true);
            break;
    }
}

const char* GamepadSample::getStringFromButtonMapping(Gamepad::ButtonMapping mapping)
{
    switch (mapping)
    {
        case Gamepad::BUTTON_A:
            return "A";
        case Gamepad::BUTTON_B:
            return "B";
        case Gamepad::BUTTON_X:
            return "X";
        case Gamepad::BUTTON_Y:
            return "Y";
        case Gamepad::BUTTON_L1:
            return "L1";
        case Gamepad::BUTTON_L2:
            return "L2";
        case Gamepad::BUTTON_L3:
            return "L3";
        case Gamepad::BUTTON_R1:
            return "R1";
        case Gamepad::BUTTON_R2:
            return "R2";
        case Gamepad::BUTTON_R3:
            return "R3";
        case Gamepad::BUTTON_UP:
            return "UP";
        case Gamepad::BUTTON_DOWN:
            return "DOWN";
        case Gamepad::BUTTON_LEFT:
            return "LEFT";
        case Gamepad::BUTTON_RIGHT:
            return "RIGHT";
        case Gamepad::BUTTON_MENU1:
            return "MENU1";
        case Gamepad::BUTTON_MENU2:
            return "MENU2";
        case Gamepad::BUTTON_MENU3:
            return "MENU3";
        default:
            return "";
    }
}
