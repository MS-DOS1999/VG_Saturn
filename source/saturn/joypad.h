#ifndef VG_SATURN_JOYPAD_H
#define VG_SATURN_JOYPAD_H

#include <stdint.h>
#include <stdbool.h>

#define CONT_A 0x0400
#define CONT_B 0x0100
#define CONT_C 0x0200
#define CONT_X 0x0040
#define CONT_Y 0x0020
#define CONT_Z 0x0010
#define CONT_START 0x0800
#define CONT_DPAD_UP 0x1000
#define CONT_DPAD_DOWN 0x2000
#define CONT_DPAD_LEFT 0x4000
#define CONT_DPAD_RIGHT 0x8000
#define CONT_L 0x0008
#define CONT_R 0x0080

#define FORCE_UP 0
#define FORCE_DOWN 1
#define FORCE_LEFT 2
#define FORCE_RIGHT 3
#define FORCE_A 4
#define FORCE_B 5
#define FORCE_X 6
#define FORCE_Y 7

void ForceInput(int key, int value);
bool GetForced(int key);
void InitController(void);
int JoystickX(int i);
int JoystickY(int i);
int JoystickPressed(int i, int dir);
int JoystickPushed(int i, int dir);
int LTriggerPushed(int i);
int RTriggerPushed(int i);
int LTriggerPressed(int i);
int RTriggerPressed(int i);
void UpdateControllersStatus(void);
int ButtonPressed(int port, int button);
int ButtonPushed(int port, int button);
bool Mapple1Connected(void);
bool Mapple2Connected(void);

#endif
