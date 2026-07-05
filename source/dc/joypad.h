#ifndef JOYPAD_H
#define JOYPAD_H

#include <kos.h>

extern maple_device_t *__dev;

extern cont_state_t *__st0;
extern cont_state_t *__st1;

extern uint8 pushedA[2];
extern uint8 pushedB[2];
extern uint8 pushedX[2];
extern uint8 pushedY[2];

extern uint8 pushedStart[2];

extern uint8 pushedPadUP[2];
extern uint8 pushedPadDOWN[2];
extern uint8 pushedPadRIGHT[2];
extern uint8 pushedPadLEFT[2];

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
void InitController();
int JoystickX(int i);
int JoystickY(int i);
int JoystickPressed(int i, int dir);
int JoystickPushed(int i, int dir);
int LTriggerPushed(int i);
int RTriggerPushed(int i);
int LTriggerPressed(int i);
int RTriggerPressed(int i);
void UpdateControllersStatus();
int ButtonPressed(int port, int button);
int ButtonPushed(int port, int button);
bool Mapple1Connected();
bool Mapple2Connected();

#endif