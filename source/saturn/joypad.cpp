#include "joypad.h"

#include "saturn_platform.h"

static bool g_forced[8];

void ForceInput(int key, int value)
{
    if ((key >= 0) && (key < 8)) {
        g_forced[key] = value != 0;
    }
}

bool GetForced(int key)
{
    if ((key >= 0) && (key < 8)) {
        return g_forced[key];
    }
    return false;
}

void InitController(void)
{
    vg_saturn_input_update();
}

void UpdateControllersStatus(void)
{
    vg_saturn_input_update();
}

static int analog_axis_from_buttons(int port, bool x_axis)
{
    const uint16_t held = vg_saturn_input_held(port);
    if (x_axis) {
        if ((held & CONT_DPAD_LEFT) != 0) return -127;
        if ((held & CONT_DPAD_RIGHT) != 0) return 127;
    } else {
        if ((held & CONT_DPAD_UP) != 0) return 127;
        if ((held & CONT_DPAD_DOWN) != 0) return -127;
    }
    return 0;
}

int JoystickX(int i) { return analog_axis_from_buttons(i, true); }
int JoystickY(int i) { return analog_axis_from_buttons(i, false); }

int JoystickPressed(int i, int dir)
{
    return ButtonPressed(i, dir);
}

int JoystickPushed(int i, int dir)
{
    return ButtonPushed(i, dir);
}

int LTriggerPushed(int i)
{
    return ButtonPushed(i, CONT_L);
}

int RTriggerPushed(int i)
{
    return ButtonPushed(i, CONT_R);
}

int LTriggerPressed(int i)
{
    return ButtonPressed(i, CONT_L);
}

int RTriggerPressed(int i)
{
    return ButtonPressed(i, CONT_R);
}

int ButtonPressed(int port, int button)
{
    return (vg_saturn_input_held(port) & button) != 0;
}

int ButtonPushed(int port, int button)
{
    return (vg_saturn_input_pressed(port) & button) != 0;
}

bool Mapple1Connected(void) { return true; }
bool Mapple2Connected(void) { return true; }
