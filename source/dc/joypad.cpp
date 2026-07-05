#include "joypad.h"
maple_device_t *__dev0;
maple_device_t *__dev1;

cont_state_t *__st0;
cont_state_t *__st1;


uint8 pushedA[2];
uint8 pushedB[2];
uint8 pushedX[2];
uint8 pushedY[2];

uint8 pushedLT[2];
uint8 pushedRT[2];

uint8 pushedStart[2];

uint8 pushedPadUP[2];
uint8 pushedPadDOWN[2];
uint8 pushedPadRIGHT[2];
uint8 pushedPadLEFT[2];

uint8 joypadUp[2];
uint8 joypadDown[2];
uint8 joypadLeft[2];
uint8 joypadRight[2];

int forcedInput[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void ForceInput(int key, int value)
{
	forcedInput[key] = value;
}

bool GetForced(int key)
{
	/*if(g_iCtrlStatus == 1)
	{
		if(forcedInput[key] > 0)
		{
			return true;
		}
	}*/

	return false;
}

void InitController()
{
	pushedA[0] = 0;
	pushedB[0] = 0;
	pushedX[0] = 0;
	pushedY[0] = 0;

	pushedStart[0] = 0;

	pushedPadUP[0] = 0;
	pushedPadDOWN[0] = 0;
	pushedPadRIGHT[0] = 0;
	pushedPadLEFT[0] = 0;

	joypadUp[0] = 0;
	joypadDown[0] = 0;
	joypadLeft[0] = 0;
	joypadRight[0] = 0;

	pushedA[1] = 0;
	pushedB[1] = 0;
	pushedX[1] = 0;
	pushedY[1] = 0;

	pushedStart[1] = 0;

	pushedPadUP[1] = 0;
	pushedPadDOWN[1] = 0;
	pushedPadRIGHT[1] = 0;
	pushedPadLEFT[1] = 0;

	joypadUp[1] = 0;
	joypadDown[1] = 0;
	joypadLeft[1] = 0;
	joypadRight[1] = 0;

	__dev0 = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);
	__dev1 = maple_enum_type(1, MAPLE_FUNC_CONTROLLER);

}

int JoystickX(int i)
{
	if(i == 0)
	{
		return __st0->joyx;
	}
	else
	{
		return __st1->joyx;
	}
}

int JoystickY(int i)
{
	if(i == 0)
	{
		return __st0->joyy;
	}
	else
	{
		return __st1->joyy;
	}
	
}

int JoystickPressed(int i, int dir)
{
	if(dir == 0 && JoystickY(i) < -50 && joypadUp[i] == 0)
	{
		joypadUp[i] = 1;
		return 1;
	}
	if(dir == 2 && JoystickY(i) > 50 && joypadDown[i] == 0)
	{
		joypadDown[i] = 1;
		return 1;
	}

	if(dir == 1 && JoystickX(i) > 50 && joypadRight[i] == 0)
	{
		joypadRight[i] = 1;
		return 1;
	}
	if(dir == 3 && JoystickX(i) < -50 && joypadLeft[i] == 0)
	{
		joypadLeft[i] = 1;
		return 1;
	}

	return 0;
}

int JoystickPushed(int i, int dir)
{
	if(dir == 0 && JoystickY(i) < -50)
	{
		return 1;
	}
	if(dir == 2 && JoystickY(i) > 50)
	{
		return 1;
	}

	if(dir == 1 && JoystickX(i) > 50)
	{
		return 1;
	}
	if(dir == 3 && JoystickX(i) < -50)
	{
		return 1;
	}

	return 0;
}

int LTriggerPushed(int i)
{
	if(i == 0)
	{
		return __st0->ltrig;
	}
	else
	{
		return __st1->ltrig;
	}
}

int RTriggerPushed(int i)
{
	if(i == 0)
	{
		return __st0->rtrig;
	}
	else
	{
		return __st1->rtrig;
	}
}

int LTriggerPressed(int i)
{
	if(i == 0)
	{
		if(__st0->ltrig > 120 && pushedLT[i] == 0)
		{
			pushedLT[i] = 1;
			return true;
		}
	}
	else
	{
		if(__st1->ltrig > 120 && pushedLT[i] == 0)
		{
			pushedLT[i] = 1;
			return true;
		}
	}

	return false;
}

int RTriggerPressed(int i)
{
	if(i == 0)
	{
		if(__st0->rtrig > 120 && pushedRT[i] == 0)
		{
			pushedRT[i] = 1;
			return true;
		}
	}
	else
	{
		if(__st1->rtrig > 120 && pushedRT[i] == 0)
		{
			pushedRT[i] = 1;
			return true;
		}
	}

	return false;
}

bool Mapple1Connected()
{
	if(__dev0 != NULL)
		return true;

	return false;
}

bool Mapple2Connected()
{
	if(__dev1 != NULL)
		return true;

	return false;
}

void UpdateControllersStatus()
{
	
	__dev0 = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);
	__dev1 = maple_enum_type(1, MAPLE_FUNC_CONTROLLER);

	__st0 = (cont_state_t*)maple_dev_status(__dev0);
				if(__st0->ltrig < 120)
				{
					pushedLT[0] = 0;
				}
				if(__st0->rtrig < 120)
				{
					pushedRT[0] = 0;
				}
				if((__st0->joyx < 50))
				{
					joypadRight[0] = 0;
				}
				if((__st0->joyx > -50))
				{
					joypadLeft[0] = 0;
				}
				if((__st0->joyy > -50))
				{
					joypadUp[0] = 0;
				}
				if((__st0->joyy < 50))
				{
					joypadDown[0] = 0;
				}
				if((__st0->buttons & CONT_A) == 0)
				{
					pushedA[0] = 0;
				}
				if((__st0->buttons & CONT_B) == 0)
				{
					pushedB[0] = 0;
				}
				if((__st0->buttons & CONT_X) == 0)
				{
					pushedX[0] = 0;
				}
				if((__st0->buttons & CONT_Y) == 0)
				{
					pushedY[0] = 0;
				}
				if((__st0->buttons & CONT_START) == 0)
				{
					pushedStart[0] = 0;
				}
				if((__st0->buttons & CONT_DPAD_UP) == 0)
				{
					pushedPadUP[0] = 0;
				}
				if((__st0->buttons & CONT_DPAD_DOWN) == 0)
				{
					pushedPadDOWN[0] = 0;
				}
				if((__st0->buttons & CONT_DPAD_RIGHT) == 0)
				{
					pushedPadRIGHT[0] = 0;
				}
				if((__st0->buttons & CONT_DPAD_LEFT) == 0)
				{
					pushedPadLEFT[0] = 0;
				}

	
	__st1 = (cont_state_t*)maple_dev_status(__dev1);

				if(__st1->ltrig < 120)
				{
					pushedLT[1] = 0;
				}
				if(__st1->rtrig < 120)
				{
					pushedRT[1] = 0;
				}
				if((__st1->joyx < 50))
				{
					joypadRight[1] = 0;
				}
				if((__st1->joyx > -50))
				{
					joypadLeft[1] = 0;
				}
				if((__st1->joyy > -50))
				{
					joypadUp[1] = 0;
				}
				if((__st1->joyy < 50))
				{
					joypadDown[1] = 0;
				}

				if((__st1->buttons & CONT_A) == 0)
				{
					pushedA[1] = 0;
				}
				if((__st1->buttons & CONT_B) == 0)
				{
					pushedB[1] = 0;
				}
				if((__st1->buttons & CONT_X) == 0)
				{
					pushedX[1] = 0;
				}
				if((__st1->buttons & CONT_Y) == 0)
				{
					pushedY[1] = 0;
				}
				if((__st1->buttons & CONT_START) == 0)
				{
					pushedStart[1] = 0;
				}
				if((__st1->buttons & CONT_DPAD_UP) == 0)
				{
					pushedPadUP[1] = 0;
				}
				if((__st1->buttons & CONT_DPAD_DOWN) == 0)
				{
					pushedPadDOWN[1] = 0;
				}
				if((__st1->buttons & CONT_DPAD_RIGHT) == 0)
				{
					pushedPadRIGHT[1] = 0;
				}
				if((__st1->buttons & CONT_DPAD_LEFT) == 0)
				{
					pushedPadLEFT[1] = 0;
				}
}

int ButtonPressed(int port, int button)
{
	if(port == 0)
	{
		switch(button)
		{
			case CONT_A:
			{
				if((__st0->buttons & button) && pushedA[0] == 0)
				{
					pushedA[0] = 1;
					return 1;
				}

				return 0;
			}
			break;

			case CONT_B:
			{
				if((__st0->buttons & button) && pushedB[0] == 0)
				{
					pushedB[0] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			case CONT_X:
			{
				if((__st0->buttons & button) && pushedX[0] == 0)
				{
					pushedX[0] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			case CONT_Y:
			{
				if((__st0->buttons & button) && pushedY[0] == 0)
				{
					pushedY[0] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			case CONT_START:
			{
				if((__st0->buttons & button) && pushedStart[0] == 0)
				{
					pushedStart[0] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			case CONT_DPAD_UP:
			{
				if((__st0->buttons & button) && pushedPadUP[0] == 0)
				{
					pushedPadUP[0] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			case CONT_DPAD_DOWN:
			{
				if((__st0->buttons & button) && pushedPadDOWN[0] == 0)
				{
					pushedPadDOWN[0] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			case CONT_DPAD_RIGHT:
			{
				if((__st0->buttons & button) && pushedPadRIGHT[0] == 0)
				{
					pushedPadRIGHT[0] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			case CONT_DPAD_LEFT:
			{
				if((__st0->buttons & button) && pushedPadLEFT[0] == 0)
				{
					pushedPadLEFT[0] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			default:
			return 0;
			break;
		}
	}
	else if(port == 1)
	{
		switch(button)
		{
			case CONT_A:
			{
				if((__st1->buttons & button) && pushedA[1] == 0)
				{
					pushedA[1] = 1;
					return 1;
				}

				return 0;
			}
			break;

			case CONT_B:
			{
				if((__st1->buttons & button) && pushedB[1] == 0)
				{
					pushedB[1] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			case CONT_X:
			{
				if((__st1->buttons & button) && pushedX[1] == 0)
				{
					pushedX[1] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			case CONT_Y:
			{
				if((__st1->buttons & button) && pushedY[1] == 0)
				{
					pushedY[1] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			case CONT_START:
			{
				if((__st1->buttons & button) && pushedStart[1] == 0)
				{
					pushedStart[1] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			case CONT_DPAD_UP:
			{
				if((__st1->buttons & button) && pushedPadUP[1] == 0)
				{
					pushedPadUP[1] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			case CONT_DPAD_DOWN:
			{
				if((__st1->buttons & button) && pushedPadDOWN[1] == 0)
				{
					pushedPadDOWN[1] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			case CONT_DPAD_RIGHT:
			{
				if((__st1->buttons & button) && pushedPadRIGHT[1] == 0)
				{
					pushedPadRIGHT[1] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			case CONT_DPAD_LEFT:
			{
				if((__st1->buttons & button) && pushedPadLEFT[1] == 0)
				{
					pushedPadLEFT[1] = 1;
					return 1;
				}
				
				return 0;
			}
			break;

			default:
			return 0;
			break;
		}
	}

	return 0;
}

int ButtonPushed(int port, int button)
{
	if(port == 0)
	{
		if(__st0->buttons & button)
		{
			return 1;
		}

		return 0;
	}
	else if(port == 1)
	{
		if(__st1->buttons & button)
		{
			return 1;
		}

		return 0;
	}

	return 0;
}