
#if INCLDUE_360_CONTROLLER == 1

#ifdef XB1
#include <windows.h>
#endif
#ifdef SWITCH
#include "IControl.h"
#endif
//#include <stdio.h>			// Header File For Standard Input/Output
//#include "texture.h"											// Header File Containing Our Texture Structure ( NEW )
#include "VG_globals.h"
#include "globals.h"
//#include "audiere.h"
#ifdef XB1
//extern Sample* global_sample;
//#include <d3d9.h>     
//#include <d3dx9.h>     
//#include <Xinput.h>
#endif

#ifdef DREAMCAST
#include "joypad.h"
#endif

//using namespace audiere;    


#ifdef SWITCH
extern float TimerGetTime();
#elif defined PS4 || defined XB1 || defined DREAMCAST
extern double TimerGetTime();
#endif

float VG_VERT_DEADZONE = 9000.0f; 
float VG_HORZ_DEADZONE = 13000.0f;

#if defined (SWITCH) || defined (PS4) || defined(DREAMCAST)
void GetDXLeftThumbStick(XINPUT_STATE my_state);
void GetDXRightThumbStick(XINPUT_STATE my_state);
#elif XB1
void GetDXLeftThumbStick(XINPUT_STATE_CUSTOM my_state);
void GetDXRightThumbStick(XINPUT_STATE_CUSTOM my_state);
#endif

#if defined (SWITCH) || defined (PS4) || defined(DREAMCAST)
void GetDXLeftThumbStick(XINPUT_STATE my_state) 
#elif XB1

bool isByte8SetTo0xFF(uint32_t number, int byteIndex) {
	byteIndex -= 1;
	uint32_t mask = 0xFF << (byteIndex * 8);
	uint32_t result = number & mask;
	return result == mask;
}


int C_Gamepad_GetButton(int controller, int button);
float C_Gamepad_GetTrigger(int controller, int trigger);
unsigned int C_Gamepad_GetStick(int controller, int stick);
int C_Gamepad_IsConnected(int controller);
int C_Button_A();
int C_Button_B();
int C_Button_X();
int C_Button_Y();
int C_Button_Up();
int C_Button_Down();
int C_Button_Left();
int C_Button_Right();
int C_Button_LShoulder();
int C_Button_RShoulder();
int C_Button_LThumb();
int C_Button_RThumb();
int C_Button_Start();
int C_Button_Back();
int C_Trigger_Left();
int C_Trigger_Right();
int C_Stick_Left();
int C_Stick_Right();
void GetDXLeftThumbStick(XINPUT_STATE_CUSTOM my_state)
#endif
{ 
	DX_WALK_LX = 0.0f;
	DX_SOFT_LX = 0.0f;
	DX_SOFT_LY = 0.0f; 
	DX_LX = 0.0f; 
	DX_LY = 0.0f;
		
	////////////////////////////////////////////////////////
	// Run soft left/right movements, not for specials... //
	////////////////////////////////////////////////////////

	VG_VERT_DEADZONE = 10500.0f;   
	VG_HORZ_DEADZONE = 10500.0f;  

	DX_WALK_LX = (float)my_state.Gamepad.sThumbLX;
	DX_SOFT_LX = (float)my_state.Gamepad.sThumbLX;
	DX_SOFT_LY = (float)my_state.Gamepad.sThumbLY; 

	if(DX_WALK_LX > -VG_HORZ_DEADZONE && DX_WALK_LX < VG_HORZ_DEADZONE) // Is in the deadzone...
		DX_WALK_LX = 0.0f;  
	if(DX_SOFT_LX > -VG_HORZ_DEADZONE && DX_SOFT_LX < VG_HORZ_DEADZONE) // Is in the deadzone...
		DX_SOFT_LX = 0.0f;  
	if(DX_SOFT_LY > -VG_VERT_DEADZONE && DX_SOFT_LY < VG_VERT_DEADZONE) // Is in the deadzone...
		DX_SOFT_LY = 0.0f;  

	if(DX_WALK_LX < 0.0f)
		DX_WALK_LX *= -1;

	////////////////////////////////////////////////////////
	// Run hard left/right movements, for specials...     //
	////////////////////////////////////////////////////////

	VG_VERT_DEADZONE = 12000.0f;        
	VG_HORZ_DEADZONE = 24000.0f;    
	  
	DX_LY = (float)my_state.Gamepad.sThumbLY; 

	if(DX_LY > -VG_VERT_DEADZONE && DX_LY < VG_VERT_DEADZONE) // Is in the deadzone...
		DX_LY = 0.0f;  
	else
		VG_HORZ_DEADZONE = 12000.0f;
	 
	DX_LX = (float)my_state.Gamepad.sThumbLX;

	if(DX_LX > -VG_HORZ_DEADZONE && DX_LX < VG_HORZ_DEADZONE) // Is in the deadzone...
		DX_LX = 0.0f;
	
	// When just started a new scene..
	if((int)TimerGetTime() < DX_DELAY_ANALOG ) 
	{
		DX_LX = 0.0f; 
		DX_LY = 0.0f;
	}
	 
}

#if defined (SWITCH) || defined (PS4) || defined (DREAMCAST)
void GetDXRightThumbStick(XINPUT_STATE my_state) 
#elif XB1
void GetDXRightThumbStick(XINPUT_STATE_CUSTOM my_state)
#endif
{  

	DX_RX = my_state.Gamepad.sThumbRX;
	DX_RY = my_state.Gamepad.sThumbRY;  

	if(DX_RY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE  && DX_RY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE )
		DX_RY = 0.0; 

	if(DX_RX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE  && DX_RX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE )
		DX_RX = 0.0; 
	
	// When just started a new scene..
	if((int)TimerGetTime() < DX_DELAY_ANALOG )
	{
		DX_RX = 0.0;   
		DX_RY = 0.0;
	}

} 

#if defined (SWITCH) || defined (PS4) || defined (DREAMCAST)
static void InputGetState(int i, XINPUT_STATE *st)
#elif XB1
static void InputGetState(int i, XINPUT_STATE_CUSTOM *st)
#endif
{
	st->Gamepad.wButtons = 0;
	st->Gamepad.sThumbLX = 0;
	st->Gamepad.sThumbLY = 0;
	st->Gamepad.sThumbRX = 0;
	st->Gamepad.sThumbRY = 0;
	st->Gamepad.bLeftTrigger = 0;
	st->Gamepad.bRightTrigger = 0;

#ifdef SWITCH

	if (i == 0)
	{
		if (IControlValue(CDEV_PAD_0, CPAD_SELECT) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_SELECT) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_BACK;

		if (IControlValue(CDEV_PAD_0, CPAD_START) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_START) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_START;

		if (IControlValue(CDEV_PAD_0, CPAD_A) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_A) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_A;

		if (IControlValue(CDEV_PAD_0, CPAD_B) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_B) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_B;

		if (IControlValue(CDEV_PAD_0, CPAD_X) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_X) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_X;

		if (IControlValue(CDEV_PAD_0, CPAD_Y) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_Y) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_Y;

		if (IControlValue(CDEV_PAD_0, CPAD_LEFT) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_LEFT) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;

		if (IControlValue(CDEV_PAD_0, CPAD_RIGHT) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_RIGHT) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;

		if (IControlValue(CDEV_PAD_0, CPAD_UP) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_UP) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_UP;

		if (IControlValue(CDEV_PAD_0, CPAD_DOWN) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_DOWN) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;

		if (IControlValue(CDEV_PAD_0, CPAD_L1) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_L1) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_LEFT_SHOULDER;

		if (IControlValue(CDEV_PAD_0, CPAD_R1) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_R1) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_SHOULDER;

		float LX_SWITCH_0 = 0;
		LX_SWITCH_0 += IControlValue(CDEV_PAD_0, CPAD_ASL_LEFT) * -32767.0f;
		LX_SWITCH_0 += IControlValue(CDEV_PAD_0, CPAD_ASL_RIGHT) * 32767.0f;

		float LY_SWITCH_0 = 0;
		LY_SWITCH_0 += IControlValue(CDEV_PAD_0, CPAD_ASL_UP) * 32767.0f;
		LY_SWITCH_0 += IControlValue(CDEV_PAD_0, CPAD_ASL_DOWN) * -32767.0f;

		float RX_SWITCH_0 = 0;
		RX_SWITCH_0 += IControlValue(CDEV_PAD_0, CPAD_ASR_LEFT) * -32767.0f;
		RX_SWITCH_0 += IControlValue(CDEV_PAD_0, CPAD_ASR_RIGHT) * 32767.0f;

		float RY_SWITCH_0 = 0;
		RY_SWITCH_0 += IControlValue(CDEV_PAD_0, CPAD_ASR_UP) * 32767.0f;
		RY_SWITCH_0 += IControlValue(CDEV_PAD_0, CPAD_ASR_DOWN) * -32767.0f;

		float LX_SWITCH_1 = 0;
		LX_SWITCH_1 += IControlValue(CDEV_PAD_1, CPAD_ASL_LEFT) * -32767.0f;
		LX_SWITCH_1 += IControlValue(CDEV_PAD_1, CPAD_ASL_RIGHT) * 32767.0f;

		float LY_SWITCH_1 = 0;
		LY_SWITCH_1 += IControlValue(CDEV_PAD_1, CPAD_ASL_UP) * 32767.0f;
		LY_SWITCH_1 += IControlValue(CDEV_PAD_1, CPAD_ASL_DOWN) * -32767.0f;

		float RX_SWITCH_1 = 0;
		RX_SWITCH_1 += IControlValue(CDEV_PAD_1, CPAD_ASR_LEFT) * -32767.0f;
		RX_SWITCH_1 += IControlValue(CDEV_PAD_1, CPAD_ASR_RIGHT) * 32767.0f;

		float RY_SWITCH_1 = 0;
		RY_SWITCH_1 += IControlValue(CDEV_PAD_1, CPAD_ASR_UP) * 32767.0f;
		RY_SWITCH_1 += IControlValue(CDEV_PAD_1, CPAD_ASR_DOWN) * -32767.0f;

		float L1_SWITCH_0 = 0;
		L1_SWITCH_0 += IControlValue(CDEV_PAD_0, CPAD_L2) * 255.0f;

		float R1_SWITCH_0 = 0;
		R1_SWITCH_0 += IControlValue(CDEV_PAD_0, CPAD_R2) * 255.0f;

		float L1_SWITCH_1 = 0;
		L1_SWITCH_1 += IControlValue(CDEV_PAD_1, CPAD_L2) * 255.0f;

		float R1_SWITCH_1 = 0;
		R1_SWITCH_1 += IControlValue(CDEV_PAD_1, CPAD_R2) * 255.0f;

		if (LX_SWITCH_1 == 0.0)
			st->Gamepad.sThumbLX = LX_SWITCH_0;
		else
			st->Gamepad.sThumbLX = LX_SWITCH_1;

		if (LY_SWITCH_1 == 0.0)
			st->Gamepad.sThumbLY = LY_SWITCH_0;
		else
			st->Gamepad.sThumbLY = LY_SWITCH_1;

		if (RX_SWITCH_1 == 0.0)
			st->Gamepad.sThumbRX = RX_SWITCH_0;
		else
			st->Gamepad.sThumbRX = RX_SWITCH_1;

		if (RY_SWITCH_1 == 0.0)
			st->Gamepad.sThumbRY = RY_SWITCH_0;
		else
			st->Gamepad.sThumbRY = RY_SWITCH_1;

		if (L1_SWITCH_0 >= L1_SWITCH_1)
			st->Gamepad.bLeftTrigger = L1_SWITCH_0;
		else
			st->Gamepad.bLeftTrigger = L1_SWITCH_1;

		if (R1_SWITCH_0 >= R1_SWITCH_1)
			st->Gamepad.bRightTrigger = R1_SWITCH_0;
		else
			st->Gamepad.bRightTrigger = R1_SWITCH_1;

		/*st->Gamepad.sThumbLX += IControlValue(CDEV_PAD_0, CPAD_ASL_LEFT) * -32767.0f;
		st->Gamepad.sThumbLX += IControlValue(CDEV_PAD_0, CPAD_ASL_RIGHT) * 32767.0f;

		st->Gamepad.sThumbLY += IControlValue(CDEV_PAD_0, CPAD_ASL_UP) * 32767.0f;
		st->Gamepad.sThumbLY += IControlValue(CDEV_PAD_0, CPAD_ASL_DOWN) * -32767.0f;

		st->Gamepad.sThumbRX += IControlValue(CDEV_PAD_0, CPAD_ASR_LEFT) * -32767.0f;
		st->Gamepad.sThumbRX += IControlValue(CDEV_PAD_0, CPAD_ASR_RIGHT) * 32767.0f;

		st->Gamepad.sThumbRY += IControlValue(CDEV_PAD_0, CPAD_ASR_UP) * 32767.0f;
		st->Gamepad.sThumbRY += IControlValue(CDEV_PAD_0, CPAD_ASR_DOWN) * -32767.0f;

		st->Gamepad.bLeftTrigger += IControlValue(CDEV_PAD_0, CPAD_L2) * 255.0f;
		st->Gamepad.bRightTrigger += IControlValue(CDEV_PAD_0, CPAD_R2) * 255.0f;*/
	}
	else
	{
		i += 1;

		if (IControlValue(CDEV_PAD_0 + i, CPAD_SELECT) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_BACK;

		if (IControlValue(CDEV_PAD_0 + i, CPAD_START) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_START;

		if (IControlValue(CDEV_PAD_0 + i, CPAD_A) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_A;

		if (IControlValue(CDEV_PAD_0 + i, CPAD_B) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_B;

		if (IControlValue(CDEV_PAD_0 + i, CPAD_X) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_X;

		if (IControlValue(CDEV_PAD_0 + i, CPAD_Y) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_Y;

		if (IControlValue(CDEV_PAD_0 + i, CPAD_LEFT) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;

		if (IControlValue(CDEV_PAD_0 + i, CPAD_RIGHT) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;

		if (IControlValue(CDEV_PAD_0 + i, CPAD_UP) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_UP;

		if (IControlValue(CDEV_PAD_0 + i, CPAD_DOWN) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;

		if (IControlValue(CDEV_PAD_0 + i, CPAD_L1) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_LEFT_SHOULDER;

		if (IControlValue(CDEV_PAD_0 + i, CPAD_R1) != 0.0f)
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_SHOULDER;

		st->Gamepad.sThumbLX += IControlValue(CDEV_PAD_0 + i, CPAD_ASL_LEFT) * -32767.0f;
		st->Gamepad.sThumbLX += IControlValue(CDEV_PAD_0 + i, CPAD_ASL_RIGHT) * 32767.0f;

		st->Gamepad.sThumbLY += IControlValue(CDEV_PAD_0 + i, CPAD_ASL_UP) * 32767.0f;
		st->Gamepad.sThumbLY += IControlValue(CDEV_PAD_0 + i, CPAD_ASL_DOWN) * -32767.0f;

		st->Gamepad.sThumbRX += IControlValue(CDEV_PAD_0 + i, CPAD_ASR_LEFT) * -32767.0f;
		st->Gamepad.sThumbRX += IControlValue(CDEV_PAD_0 + i, CPAD_ASR_RIGHT) * 32767.0f;

		st->Gamepad.sThumbRY += IControlValue(CDEV_PAD_0 + i, CPAD_ASR_UP) * 32767.0f;
		st->Gamepad.sThumbRY += IControlValue(CDEV_PAD_0 + i, CPAD_ASR_DOWN) * -32767.0f;

		st->Gamepad.bLeftTrigger += IControlValue(CDEV_PAD_0 + i, CPAD_L2) * 255.0f;
		st->Gamepad.bRightTrigger += IControlValue(CDEV_PAD_0 + i, CPAD_R2) * 255.0f;
	}
#elif PS4
	if (i == 0)
	{
		if (_Application._MainPadContext != nullptr)
		{
			//printf("Enter GamePAD 0\n");
			//if (IControlValue(CDEV_PAD_0, CPAD_SELECT) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_SELECT) != 0.0f)
				//st->Gamepad.wButtons |= XINPUT_GAMEPAD_BACK;

			if (_Application._MainPadContext->isButtonDown(sce::SampleUtil::Input::kButtonOptions))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_START;

			if (_Application._MainPadContext->isButtonDown(_Application.isMainButtonCircle ? sce::SampleUtil::Input::kButtonCircle : sce::SampleUtil::Input::kButtonCross))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_A;

			if (_Application._MainPadContext->isButtonDown(_Application.isMainButtonCircle ? sce::SampleUtil::Input::kButtonCross : sce::SampleUtil::Input::kButtonCircle))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_B;

			if (_Application._MainPadContext->isButtonDown(sce::SampleUtil::Input::kButtonSquare))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_X;

			if (_Application._MainPadContext->isButtonDown(sce::SampleUtil::Input::kButtonTriangle))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_Y;

			if (_Application._MainPadContext->isButtonDown(sce::SampleUtil::Input::kButtonLeft))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;

			if (_Application._MainPadContext->isButtonDown(sce::SampleUtil::Input::kButtonRight))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;

			if (_Application._MainPadContext->isButtonDown(sce::SampleUtil::Input::kButtonUp))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_UP;

			if (_Application._MainPadContext->isButtonDown(sce::SampleUtil::Input::kButtonDown))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;

			if (_Application._MainPadContext->isButtonDown(sce::SampleUtil::Input::kButtonL1))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_LEFT_SHOULDER;

			if (_Application._MainPadContext->isButtonDown(sce::SampleUtil::Input::kButtonR1))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_SHOULDER;


			st->Gamepad.sThumbLX += _Application._MainPadContext->getLeftStick().getX() * 32767.0f;

			st->Gamepad.sThumbLY += _Application._MainPadContext->getLeftStick().getY() * -32767.0f;
			//st->Gamepad.sThumbLY += IControlValue(CDEV_PAD_0, CPAD_ASL_DOWN) * 32767.0f;

			//st->Gamepad.sThumbRX += IControlValue(CDEV_PAD_0, CPAD_ASR_LEFT) * -32767.0f;
			//st->Gamepad.sThumbRX += IControlValue(CDEV_PAD_0, CPAD_ASR_RIGHT) * 32767.0f;

			//st->Gamepad.sThumbRY += IControlValue(CDEV_PAD_0, CPAD_ASR_UP) * 32767.0f;
			//st->Gamepad.sThumbRY += IControlValue(CDEV_PAD_0, CPAD_ASR_DOWN) * -32767.0f;

			//st->Gamepad.bLeftTrigger += IControlValue(CDEV_PAD_0, CPAD_L2) * 255.0f;
			//st->Gamepad.bRightTrigger += IControlValue(CDEV_PAD_0, CPAD_R2) * 255.0f;
		}
	}
	else
	{

		
		if (_Application._SecondPadContext != nullptr)
		{

			//printf("Enter GamePAD 1\n");
			//if (IControlValue(CDEV_PAD_0, CPAD_SELECT) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_SELECT) != 0.0f)
			//st->Gamepad.wButtons |= XINPUT_GAMEPAD_BACK;

			if (_Application._SecondPadContext->isButtonDown(sce::SampleUtil::Input::kButtonOptions))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_START;

			if (_Application._SecondPadContext->isButtonDown(_Application.isMainButtonCircle ? sce::SampleUtil::Input::kButtonCircle : sce::SampleUtil::Input::kButtonCross))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_A;

			if (_Application._SecondPadContext->isButtonDown(_Application.isMainButtonCircle ? sce::SampleUtil::Input::kButtonCross : sce::SampleUtil::Input::kButtonCircle))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_B;

			if (_Application._SecondPadContext->isButtonDown(sce::SampleUtil::Input::kButtonSquare))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_X;

			if (_Application._SecondPadContext->isButtonDown(sce::SampleUtil::Input::kButtonTriangle))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_Y;

			if (_Application._SecondPadContext->isButtonDown(sce::SampleUtil::Input::kButtonLeft))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;

			if (_Application._SecondPadContext->isButtonDown(sce::SampleUtil::Input::kButtonRight))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;

			if (_Application._SecondPadContext->isButtonDown(sce::SampleUtil::Input::kButtonUp))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_UP;

			if (_Application._SecondPadContext->isButtonDown(sce::SampleUtil::Input::kButtonDown))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;

			if (_Application._SecondPadContext->isButtonDown(sce::SampleUtil::Input::kButtonL1))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_LEFT_SHOULDER;

			if (_Application._SecondPadContext->isButtonDown(sce::SampleUtil::Input::kButtonR1))
				st->Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_SHOULDER;


			st->Gamepad.sThumbLX += _Application._SecondPadContext->getLeftStick().getX() * 32767.0f;

			st->Gamepad.sThumbLY += _Application._SecondPadContext->getLeftStick().getY() * -32767.0f;
			//st->Gamepad.sThumbLY += IControlValue(CDEV_PAD_0, CPAD_ASL_DOWN) * 32767.0f;

			//st->Gamepad.sThumbRX += IControlValue(CDEV_PAD_0, CPAD_ASR_LEFT) * -32767.0f;
			//st->Gamepad.sThumbRX += IControlValue(CDEV_PAD_0, CPAD_ASR_RIGHT) * 32767.0f;

			//st->Gamepad.sThumbRY += IControlValue(CDEV_PAD_0, CPAD_ASR_UP) * 32767.0f;
			//st->Gamepad.sThumbRY += IControlValue(CDEV_PAD_0, CPAD_ASR_DOWN) * -32767.0f;

			//st->Gamepad.bLeftTrigger += IControlValue(CDEV_PAD_0, CPAD_L2) * 255.0f;
			//st->Gamepad.bRightTrigger += IControlValue(CDEV_PAD_0, CPAD_R2) * 255.0f;
		}
	}
#elif XB1
	if (C_Gamepad_IsConnected(i))
	{
		//printf("Enter GamePAD 0\n");
		//if (IControlValue(CDEV_PAD_0, CPAD_SELECT) != 0.0f || IControlValue(CDEV_PAD_1, CPAD_SELECT) != 0.0f)
		//st->Gamepad.wButtons |= XINPUT_GAMEPAD_BACK;

		if (C_Gamepad_GetButton(i, C_Button_Start()))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_START;

		if (C_Gamepad_GetButton(i, C_Button_A()))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_A;

		if (C_Gamepad_GetButton(i, C_Button_B()))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_B;

		if (C_Gamepad_GetButton(i, C_Button_X()))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_X;

		if (C_Gamepad_GetButton(i, C_Button_Y()))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_Y;

		if ((C_Gamepad_GetButton(i, C_Button_Left()) == 1 || isByte8SetTo0xFF(C_Gamepad_GetStick(i, C_Stick_Left()), 1) == true))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;

		if ((C_Gamepad_GetButton(i, C_Button_Right()) == 1 || isByte8SetTo0xFF(C_Gamepad_GetStick(i, C_Stick_Left()), 2) == true))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;

		if ((C_Gamepad_GetButton(i, C_Button_Up()) == 1 || isByte8SetTo0xFF(C_Gamepad_GetStick(i, C_Stick_Left()), 3) == true))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_UP;

		if ((C_Gamepad_GetButton(i, C_Button_Down()) == 1 || isByte8SetTo0xFF(C_Gamepad_GetStick(i, C_Stick_Left()), 4) == true))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;

		if (C_Gamepad_GetButton(i, C_Button_LShoulder()))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_LEFT_SHOULDER;

		if (C_Gamepad_GetButton(i, C_Button_RShoulder()))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_SHOULDER;


		//st->Gamepad.sThumbLX += pad1.thumbSticks.leftX * 32767.0f;

		//st->Gamepad.sThumbLY += pad1.thumbSticks.leftY * -32767.0f;
	}
#elif DREAMCAST

	if((i == 0 && Mapple1Connected() == true) || (i == 1 && Mapple2Connected() == true))
	{
		if (ButtonPushed(i, CONT_START))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_START;

		if (ButtonPushed(i, CONT_A))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_A;

		if (ButtonPushed(i, CONT_B))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_B;

		if (ButtonPushed(i, CONT_X))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_X;

		if (ButtonPushed(i, CONT_Y))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_Y;

		if (ButtonPushed(i, CONT_DPAD_LEFT))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;

		if (ButtonPushed(i, CONT_DPAD_RIGHT))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;

		if (ButtonPushed(i, CONT_DPAD_UP))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_UP;

		if (ButtonPushed(i, CONT_DPAD_DOWN))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;

		if (LTriggerPushed(i))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_LEFT_SHOULDER;

		if (RTriggerPushed(i))
			st->Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_SHOULDER;


		st->Gamepad.sThumbLX += ((float)JoystickX(i))/127.0f * 32767.0f;

		st->Gamepad.sThumbLY += ((float)JoystickY(i))/127.0f * -32767.0f;
	}
#endif



	return;
}

 
bool Check_Controller()
{
	bool success=false;

#ifdef XB1
	DWORD dwResult; 
#endif		    
	DXPacketNumber = state.dwPacketNumber;  

#ifdef XB1
	ZeroMemory( &state, sizeof(XINPUT_STATE_CUSTOM) );
#elif SWITCH
	memset(&state, 0, sizeof(XINPUT_STATE));
#elif DREAMCAST
	memset(&state, 0, sizeof(XINPUT_STATE));
#elif PS4
	memset(&state, 0, sizeof(XINPUT_STATE));
#endif

	if ((int)TimerGetTime() > VG_1_vibrate_time)
	{
#ifdef XB1
		ZeroMemory(&DX_1_vibration, sizeof(XINPUT_VIBRATION_CUSTOM));
#elif SWITCH
		memset(&DX_1_vibration, 0, sizeof(XINPUT_VIBRATION));
#elif DREAMCAST
		memset(&DX_1_vibration, 0, sizeof(XINPUT_VIBRATION));
#elif PS4
		memset(&DX_1_vibration, 0, sizeof(XINPUT_VIBRATION));
#endif
	}

	// Simply get the state of the controller from XInput.
#ifdef XB1
	InputGetState(0, &state);
#elif SWITCH
	InputGetState(0, &state);
#elif PS4
	InputGetState(0, &state);
#elif DREAMCAST
	InputGetState(0, &state);
#endif
	{  
		success = true;
	}

	return(success);
}

void Run_Joypad()
{

#ifdef XB1
	DWORD dwResult; 
#endif

	DXPacketNumber = state.dwPacketNumber; 

#ifdef XB1
	ZeroMemory( &state, sizeof(XINPUT_STATE_CUSTOM) );
#elif SWITCH
	memset(&state, 0, sizeof(XINPUT_STATE));
#elif DREAMCAST
	memset(&state, 0, sizeof(XINPUT_STATE));
#elif PS4
	memset(&state, 0, sizeof(XINPUT_STATE));
#endif

	for(int i=0;i<2;i++)  
	{ 
		 
		if(i==0)
		if((int)TimerGetTime() > VG_1_vibrate_time)
#ifdef XB1
			ZeroMemory( &DX_1_vibration, sizeof(XINPUT_VIBRATION_CUSTOM) );
#elif SWITCH
			memset(&DX_1_vibration, 0, sizeof(XINPUT_VIBRATION));
#elif DREAMCAST
			memset(&DX_1_vibration, 0, sizeof(XINPUT_VIBRATION));
#elif PS4
			memset(&DX_1_vibration, 0, sizeof(XINPUT_VIBRATION));
#endif
		if(i==1)
		if((int)TimerGetTime() > VG_2_vibrate_time)
#ifdef XB1
			ZeroMemory( &DX_2_vibration, sizeof(XINPUT_VIBRATION_CUSTOM) );
#elif SWITCH
			memset(&DX_2_vibration, 0, sizeof(XINPUT_VIBRATION));
#elif DREAMCAST
			memset(&DX_2_vibration, 0, sizeof(XINPUT_VIBRATION));
#elif PS4
			memset(&DX_2_vibration, 0, sizeof(XINPUT_VIBRATION));
#endif

		// Simply get the state of the controller from XInput.
#ifdef XB1
		InputGetState(i, &state);
#elif SWITCH
		InputGetState(i, &state);
#elif DREAMCAST
		InputGetState(i, &state);
#elif PS4
		InputGetState(i, &state);
#endif
		{  
						
			if(i==0)
			{
				 
				VG_1_XAXIS = 0.0f;

				VG_1_DX_UP = false;
				VG_1_DX_DOWN = false;
				VG_1_DX_LEFT = false;
				VG_1_DX_RIGHT = false; 

				VG_1_SOFT_DX_LEFT=false;
				VG_1_SOFT_DX_RIGHT=false;

				VG_1_DX_A = false;
				VG_1_DX_B = false;
				VG_1_DX_X = false;
				VG_1_DX_Y = false;

				VG_1_DX_LS = false;
				VG_1_DX_RS = false;

				VG_1_DX_LT = false;
				VG_1_DX_RT = false;

				VG_1_DX_START = false;
				VG_1_DX_BACK = false;
			}
			if(i==1)
			{
				 
				VG_2_XAXIS = 0.0f;

				VG_2_DX_UP = false;
				VG_2_DX_DOWN = false;
				VG_2_DX_LEFT = false;
				VG_2_DX_RIGHT = false;

				VG_2_SOFT_DX_LEFT=false;
				VG_2_SOFT_DX_RIGHT=false;

				VG_2_DX_A = false;
				VG_2_DX_B = false;
				VG_2_DX_X = false;
				VG_2_DX_Y = false;

				VG_2_DX_LS = false;
				VG_2_DX_RS = false;

				VG_2_DX_LT = false;
				VG_2_DX_RT = false;

				VG_2_DX_START = false;
				VG_2_DX_BACK = false;
			} 

			GetDXLeftThumbStick(state);   
			GetDXRightThumbStick(state);
			 
			if(i == 0)
			{
				if((int)TimerGetTime() > VG_1_DX_A_timer)

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) // VG_P1_KICK1_KEY
					VG_1_DX_A = true;
#ifdef SWITCH
				
							
				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_B) // VG_P1_KICK2_KEY
					VG_1_DX_B = true;

#elif defined PS4 || defined XB1 || defined DREAMCAST
				if (!game_paused)
				{

					if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) // VG_P1_KICK2_KEY
						VG_1_DX_B = true;
				}
#endif
								
				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_X) // VG_P1_PUNCH1_KEY
					VG_1_DX_X = true;

				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) // VG_P1_PUNCH2_KEY
					VG_1_DX_Y = true;   
								
				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
					VG_1_DX_LS = true;

				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
					VG_1_DX_RS = true;   

				if(state.Gamepad.bLeftTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD ) // XINPUT_GAMEPAD_TRIGGER_THRESHOLD
					VG_1_DX_LS = true;

				if(state.Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD ) // XINPUT_GAMEPAD_TRIGGER_THRESHOLD
					VG_1_DX_RS = true;   

				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
					VG_1_DX_UP = true;
								
				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
					VG_1_DX_DOWN = true;
								
				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				{
					VG_1_DX_LEFT = true;
					VG_1_SOFT_DX_LEFT = true;
				}

				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
				{
					VG_1_DX_RIGHT = true;  
					VG_1_SOFT_DX_RIGHT = true;
				}
			
				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
					VG_1_DX_START = true;

				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
					VG_1_DX_BACK = true;

#if defined PS4 || defined XB1 || defined DREAMCAST
				if (game_paused)
				{
					if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) // VG_P1_KICK2_KEY
						VG_1_DX_BACK = true;
				}
#endif

				// Left analog stick for menus
				if(DX_LY != 0.0f)
				if(DX_LY < 0.0f )    
					VG_1_DX_DOWN = true;

				if(DX_LY != 0.0f)
				if(DX_LY > 0.0f )   
					VG_1_DX_UP = true;   

				// Left analog stick for menus 
				if(DX_LX != 0.0f) 
				if(DX_LX < 0.0f )  
					VG_1_DX_LEFT = true;    

				if(DX_LX != 0.0f)
				if(DX_LX > 0.0f )   
					VG_1_DX_RIGHT = true;   

				// Left analog stick for menus 
				if(DX_SOFT_LX != 0.0f)
				if(DX_SOFT_LX < 0.0f )  
					VG_1_SOFT_DX_LEFT = true;    
				 
				if(DX_SOFT_LX != 0.0f)
				if(DX_SOFT_LX > 0.0f )   
					VG_1_SOFT_DX_RIGHT = true;   

				if(DX_WALK_LX != 0.0f)
					VG_1_XAXIS = 30000.0f / DX_WALK_LX;

			}

			if(i == 1)
			{
				if((int)TimerGetTime() > VG_2_DX_A_timer)

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) // VG_P1_KICK1_KEY
					VG_2_DX_A = true;
#ifdef SWITCH
				
							
				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_B) // VG_P1_KICK2_KEY
					VG_2_DX_B = true;
#elif defined PS4 || defined XB1 || defined DREAMCAST
				if (!game_paused)
				{

					if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) // VG_P1_KICK2_KEY
						VG_2_DX_B = true;
				}
#endif
								
				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_X) // VG_P1_PUNCH1_KEY
					VG_2_DX_X = true;
				 
				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) // VG_P1_PUNCH2_KEY
					VG_2_DX_Y = true;   
								
				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
					VG_2_DX_LS = true; 

				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
					VG_2_DX_RS = true;   

				if(state.Gamepad.bLeftTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD ) // XINPUT_GAMEPAD_TRIGGER_THRESHOLD
					VG_2_DX_LS = true;

				if(state.Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD ) // XINPUT_GAMEPAD_TRIGGER_THRESHOLD
					VG_2_DX_RS = true;   

				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
					VG_2_DX_UP = true;
								
				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
					VG_2_DX_DOWN = true;
								
				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				{
					VG_2_DX_LEFT = true;
					VG_2_SOFT_DX_LEFT = true; 
				}

				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
				{
					VG_2_DX_RIGHT = true;  
					VG_2_SOFT_DX_RIGHT = true;
				}
			

				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
					VG_2_DX_START = true; 

				if(state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
					VG_2_DX_BACK = true;

#if defined PS4 || defined XB1 || defined DREAMCAST
				if (game_paused)
				{
					if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) // VG_P1_KICK2_KEY
						VG_2_DX_BACK = true;
				}
#endif

				// Left analog stick for menus
				if(DX_LY != 0.0f)
				if(DX_LY < 0.0f )     
					VG_2_DX_DOWN = true;

				if(DX_LY != 0.0f)
				if(DX_LY > 0.0f )     
					VG_2_DX_UP = true;   

				// Left analog stick for menus 
				if(DX_LX != 0.0f)
				if(DX_LX < 0.0f )  
					VG_2_DX_LEFT = true;    
				 
				if(DX_LX != 0.0f)
				if(DX_LX > 0.0f )   
					VG_2_DX_RIGHT = true;    

				// Left analog stick for menus 
				if(DX_SOFT_LX != 0.0f)
				if(DX_SOFT_LX < 0.0f )  
					VG_2_SOFT_DX_LEFT = true;    

				if(DX_SOFT_LX != 0.0f)
				if(DX_SOFT_LX > 0.0f )    
					VG_2_SOFT_DX_RIGHT = true;   

				if(DX_WALK_LX != 0.0f)
					VG_2_XAXIS = 32676.0f / DX_WALK_LX;
			}	

		} // if(game_paused == false && ply_dead == false && lock_player == false)


		if(VG_1_DX_A == true || VG_1_DX_B == true
		|| VG_1_DX_X == true || VG_1_DX_Y == true
		|| VG_1_DX_LS == true || VG_1_DX_RS == true
		|| VG_1_DX_UP == true || VG_1_DX_DOWN == true
		|| VG_1_DX_LEFT == true || VG_1_DX_RIGHT == true
		|| VG_1_DX_START == true || VG_1_DX_BACK == true)
			VG_P1_USING = VG_CONTROLLER;

		if(VG_2_DX_A == true || VG_2_DX_B == true
		|| VG_2_DX_X == true || VG_2_DX_Y == true
		|| VG_2_DX_LS == true || VG_2_DX_RS == true
		|| VG_2_DX_UP == true || VG_2_DX_DOWN == true
		|| VG_2_DX_LEFT == true || VG_2_DX_RIGHT == true
		|| VG_2_DX_START == true|| VG_2_DX_BACK == true)
			VG_P2_USING = VG_CONTROLLER; 

	} // end of for loop... 

}

void Set_Vibration(int player, int left, int right, int time)
{

}

#endif