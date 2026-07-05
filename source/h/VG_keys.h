#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64 
#define WIN32_LEAN_AND_MEAN   
#include <windows.h>
#endif    
 
extern void Run_Moves(int player, int f_rate); 
extern void VG_CombineDirections(int player);
extern void VG_CheckForSpecials(int player);
extern void VG_ATTACK_DOG(int player);
extern bool Change_Texture(sString sfilename, int loop);

extern void VG_CheckForSpecialsJoy(int player);

extern void VG_SlowMO(int duration, float strength);

extern void VG_Particles(float x, float y, float angle, int priority, int anim);

void VG_Upload_Score(int type);

void VG_SetMove(int player, int move) 
{

	int VG_countback = 0;  
	int tmp_VG_Moves_count = 0;
	int parse_value=0;

	bool done=false;  

	if(VG_finished_round == true)
		return;

	if(episode != 5)  
		return; 

	if(sprite[2].status == VG_SPECIAL1_FONT || sprite[2].status == VG_SPECIAL2_FONT )
	if(player == 1 && sprite[2].jumping == true) 
		return;

	if(sprite[3].status == VG_SPECIAL1_FONT || sprite[3].status == VG_SPECIAL2_FONT )
	if(player == 2 && sprite[3].jumping == true)
		return;

	if(player == 1)
	{

		if(move >= 10) // Don't process movement codes...
		if(VG_1_Firststrike == false)
		{
			VG_1_Firststrike_timestamp = (int)TimerGetTime() + 500;
			VG_1_Firststrike = true;
		}
		if(VG_1_Moves_count >= 0 && VG_1_Moves_count < MOVES_LIMIT)
		{
			VG_1_Moves[VG_1_Moves_count] = move;  
			VG_1_Moves_timestamp[VG_1_Moves_count] = (int)TimerGetTime();
		}

		VG_1_Moves_count++;

	}
	else 
	{

		if(move >= 10) // Don't process movement codes...
		if(VG_2_Firststrike == false)
		{
			VG_2_Firststrike_timestamp = (int)TimerGetTime() + 500;
			VG_2_Firststrike = true;
		}

		tmp_VG_Moves_count = VG_2_Moves_count;

		if(VG_2_Moves_count >= 0 && VG_2_Moves_count < MOVES_LIMIT)
		{
			VG_2_Moves[VG_2_Moves_count] = move;  
			VG_2_Moves_timestamp[VG_2_Moves_count] = (int)TimerGetTime();
		}

		VG_2_Moves_count++;

	}

	if(player == 1)
	if(VG_1_Moves_count >= 10) 
	{  
		for(int i = 0;i < 10;i++)  
		{
			VG_1_Moves[i] = VG_1_Moves[i+1];
			VG_1_Moves_timestamp[i] = VG_1_Moves_timestamp[i+1];
		}
		VG_1_Moves_count = 9;
	} 
	if(player == 2) 
	if(VG_2_Moves_count >= 10) 
	{  
		for(int i = 0;i < 10;i++)  
		{
			VG_2_Moves[i] = VG_2_Moves[i+1];
			VG_2_Moves_timestamp[i] = VG_2_Moves_timestamp[i+1];
		}
		VG_2_Moves_count = 9;   
	}   

	if(NO_SPECIALS == 0)
	{ 
		if(VG_1_EQUIPMENT != EQUIPMENT_BASIC)
		if(player == 1)
		{
			if(VG_P1_USING == VG_KEYBOARD)
				VG_CheckForSpecials(1); // Add special to queue...  
			else
				VG_CheckForSpecialsJoy(1); // Add special to queue...  
		}

		if(VG_AI_active == false)
		if(VG_2_EQUIPMENT != EQUIPMENT_BASIC)
		if(player == 2)
		{
			if(VG_P2_USING == VG_KEYBOARD)
				VG_CheckForSpecials(2); // Add special to queue...  
			else
				VG_CheckForSpecialsJoy(2); // Add special to queue...  
		}

	}

	if(player == 1)
		VG_1_MovesList_count = VG_1_Moves_count;
	else
		VG_2_MovesList_count = VG_2_Moves_count;
}
 
int VG_Key_Handler(bool keys[256], object *display, int f_rate)
{  
                   
	float mid_x=0.0f, mid_y=0.0f;

	if(f_rate <= 0)                                                
	    f_rate = 1;        

	if(f_rate >= 50) 
		f_rate = 50;  
	 
	 if(episode == 5)
	 { 
		 if((int)TimerGetTime() > VG_1_Firststrike_timestamp)
			 VG_1_Firststrike = false;
		 if((int)TimerGetTime() > VG_2_Firststrike_timestamp)
			 VG_2_Firststrike = false;

		 if(VG_finished_round == false)    
		 if(VG_1_MOVE_ACTIVE == false)
	//	 if((int)TimerGetTime() > VG_1_WaitForKeys || VG_P1_USING != VG_KEYBOARD) 
		 if(VG_1_MovesList_count > 0 && VG_1_MovesList_count < MOVES_LIMIT)
		 for(int i=0;i<VG_1_MovesList_count;i++) 
		 if(i < MOVES_LIMIT)
		 {
			 VG_1_MovesList[i] = VG_1_Moves[i];
			 VG_1_MovesList_timestamp[i] = VG_1_Moves_timestamp[i];
		 }
		 if(VG_finished_round == false)   
		 if(VG_2_MOVE_ACTIVE == false)
	//	 if((int)TimerGetTime() > VG_2_WaitForKeys || VG_P2_USING != VG_KEYBOARD || VG_AI_active == true) 
		 if(VG_2_MovesList_count > 0 && VG_2_MovesList_count < MOVES_LIMIT)
		 for(int i=0;i<VG_2_MovesList_count;i++)
		 if(i < MOVES_LIMIT)
		 {
			 VG_2_MovesList[i] = VG_2_Moves[i];
			 VG_2_MovesList_timestamp[i] = VG_2_Moves_timestamp[i];
		 }
	 }

	 // A.I special moves...
   	 if(game_paused == false)       
     if(!mode)  
     {

		if(VK_KEY_AI_SPECIAL1 == true && VK_KEY_AI_COMBO == false) 
			VG_SetMove(2, VG_AI_SPECIAL1_FONT);

		VK_KEY_AI_SPECIAL1 = false;

		if(VK_KEY_AI_COMBO == true)
			VG_SetMove(2, VG_AI_COMBO_FONT);

		VK_KEY_AI_COMBO = false;

	 } 

   	 if(game_paused == false)    
	 if(VG_1_BLOCKING == false)
     if(!mode)  
     {
	     if(keys[VG_P1_UP_KEY] || VG_1_DX_UP)      
		 { 
			 if(keys[VG_P1_UP_KEY])
				 VG_P1_USING = VG_KEYBOARD;
			  
			 VG_1_UP_pressed = true; // Temp...

			 if(VG_1_UP == VG_RESET) 
				 VG_1_UP_timer = (int)TimerGetTime() + VG_HELD_LENGTH;

			if(VG_1_UP == VG_RESET)
			{
				VG_1_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;
				VG_1_HUDUP = true;
				VG_1_UP = VG_PRESSED;
				VG_SetMove(1, VG_UP_FONT);
			}

		/*	 if(VG_1_UP_timer != -1)
			 if((int)TimerGetTime() > VG_1_UP_timer) 
			 {
				VG_1_UP = VG_HELD; 
				VG_SetMove(1, VG_UP_FONT_H); 
				VG_1_UP_timer = -1;
			 }*/

		 } 
		  
	     if(!keys[VG_P1_UP_KEY] && !VG_1_DX_UP)   
		 {
			 VG_1_HUDUP = false;

			 VG_1_UP_pressed = false; // Temp...
			 VG_1_UP = VG_RESET; 

			 VG_1_DX_UP = false;
		 }  
	 } 
	 if(game_paused == false)    
	 if(VG_2_BLOCKING == false)
     if(!mode)  
     {
	     if(keys[VG_P2_UP_KEY] || VG_2_DX_UP || VG_P2_AI_UP_KEY)       
		 { 
			 if(keys[VG_P2_UP_KEY])
				 VG_P2_USING = VG_KEYBOARD;

			 VG_2_UP_pressed = true; // Temp...
			 if(VG_2_UP == VG_RESET)
				 VG_2_UP_timer = (int)TimerGetTime() + VG_HELD_LENGTH;

			if(VG_2_UP == VG_RESET)
			{
				VG_2_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;
				VG_2_HUDUP = true;
				VG_2_UP = VG_PRESSED;
				VG_SetMove(2, VG_UP_FONT);
			}

		/*	 if(VG_2_UP_timer != -1)
			 if((int)TimerGetTime() > VG_2_UP_timer) 
			 {
				VG_2_UP = VG_HELD; 
				VG_SetMove(2, VG_UP_FONT_H);
				VG_2_UP_timer = -1;
			 }*/

		 } 
		  
	     if(!keys[VG_P2_UP_KEY] && !VG_2_DX_UP && !VG_P2_AI_UP_KEY)   
		 {
			 VG_2_HUDUP = false;

			 VG_2_UP_pressed = false; // Temp...
			 VG_2_UP = VG_RESET; 
			 VG_2_DX_UP = false;

			 VG_P2_AI_UP_KEY = false;
		 }  

	 } 
   	 if(game_paused == false)      
     if(!mode)  
     {
	     if(keys[VG_P1_DOWN_KEY] || VG_1_DX_DOWN)           
		 { 
			 if(keys[VG_P1_DOWN_KEY])
				 VG_P1_USING = VG_KEYBOARD;

			 VG_1_DOWN_pressed = true; // Temp... 

			 if(VG_1_DOWN == VG_RESET)
				 VG_1_DOWN_timer = (int)TimerGetTime() + VG_HELD_LENGTH;

			if(VG_1_DOWN == VG_RESET)
			{
				VG_1_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;
				VG_1_HUDDOWN = true;
				VG_1_DOWN = VG_PRESSED;
				VG_SetMove(1, VG_DOWN_FONT);
			}

		/*	 if(VG_1_DOWN_timer != -1) 
			 if((int)TimerGetTime() > VG_1_DOWN_timer)    
			 { 
				VG_1_DOWN = VG_HELD; 
				VG_SetMove(1, VG_DOWN_FONT_H);
				VG_1_DOWN_timer = -1;
			 }*/

		 }

	     if(!keys[VG_P1_DOWN_KEY] && !VG_1_DX_DOWN)   
		 {
			VG_1_HUDDOWN = false;

			VG_1_DOWN_pressed = false; // Temp...
			VG_1_DOWN = VG_RESET; 

			VG_1_DX_DOWN = false;
		 } 
	 } 
	 if(game_paused == false)      
     if(!mode)  
     {
	     if(keys[VG_P2_DOWN_KEY] || VG_2_DX_DOWN || VG_P2_AI_DOWN_KEY)                   
		 { 
			 if(keys[VG_P2_DOWN_KEY])
				 VG_P2_USING = VG_KEYBOARD;	
			  
			 VG_2_DOWN_pressed = true; // Temp... 
			 if(VG_2_DOWN == VG_RESET)
				 VG_2_DOWN_timer = (int)TimerGetTime() + VG_HELD_LENGTH;

			if(VG_2_DOWN == VG_RESET)
			{ 
				VG_2_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;
				VG_SetMove(2, VG_DOWN_FONT);
				VG_2_HUDDOWN = true;
				VG_2_DOWN = VG_PRESSED;
			}
				
		/*	 if(VG_2_DOWN_timer != -1) 
			 if((int)TimerGetTime() > VG_2_DOWN_timer)    
			 { 
				VG_2_DOWN = VG_HELD; 
				VG_SetMove(2, VG_DOWN_FONT_H); 
				VG_2_DOWN_timer = -1;
			 }*/

		 }

	     if(!keys[VG_P2_DOWN_KEY] && !VG_2_DX_DOWN && !VG_P2_AI_DOWN_KEY)          
		 {

			VG_2_HUDDOWN = false;

			VG_2_DOWN_pressed = false; // Temp...
			VG_2_DOWN = VG_RESET; 
			VG_2_DX_DOWN = false;

			VG_P2_AI_DOWN_KEY = false;
		 } 

	 } 
   	 if(game_paused == false)       
     if(!mode)  
     {
	//	 if(VG_P1_USING == VG_CONTROLLER) 
		 if(VG_1_SOFT_DX_LEFT) // Walking left/right...
		 {
			 VG_1_LEFT_pressed = true; // Temp...
		 }
		 else
			 VG_1_LEFT_pressed = false; // Temp...

	     if(keys[VG_P1_LEFT_KEY] || VG_1_DX_LEFT)       
		 { 
			 if(VG_P1_USING != VG_CONTROLLER) 
				VG_1_LEFT_pressed = true; // Temp...

			 if(keys[VG_P1_LEFT_KEY])
				 VG_P1_USING = VG_KEYBOARD;

			 if(VG_1_LEFT == VG_RESET)
				 VG_1_LEFT_timer = (int)TimerGetTime() + VG_HELD_LENGTH;

			 if(VG_1_LEFT == VG_RESET) 
			 {
				VG_1_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;

				VG_1_HUDLEFT = true;
				VG_SetMove(1, VG_LEFT_FONT);
				VG_1_LEFT = VG_PRESSED; 
			 }

		/*	 if(VG_1_LEFT_timer != -1)
			 if((int)TimerGetTime() > VG_1_LEFT_timer) 
			 {
				VG_1_LEFT = VG_HELD; 
				VG_SetMove(1, VG_LEFT_FONT_H);  
				VG_1_LEFT_timer = -1;  
			 }*/
		 }
		   
	     if(!keys[VG_P1_LEFT_KEY] && !VG_1_DX_LEFT)   
		 {
			 if(VG_P1_USING != VG_CONTROLLER) 
				VG_1_LEFT_pressed = false; // Temp...

			 VG_1_HUDLEFT = false;

			 VG_1_LEFT = VG_RESET; 

		  //   VG_1_LEFT_pressed = false; // Temp...

			 VG_1_DX_LEFT = false;
		 } 
	 } 
	 if(game_paused == false)      
     if(!mode)  
     { 
		 if(VG_P2_USING == VG_CONTROLLER) 
		 if(VG_2_SOFT_DX_LEFT) // Walking left/right...
			 VG_2_LEFT_pressed = true; // Temp...
		 else 
			 VG_2_LEFT_pressed = false; // Temp...

	     if(keys[VG_P2_LEFT_KEY] || VG_2_DX_LEFT || VG_P2_AI_LEFT_KEY)                 
		 { 
			 if(VG_P2_USING != VG_CONTROLLER) 
				VG_2_LEFT_pressed = true; // Temp...

			 if(keys[VG_P2_LEFT_KEY])
				 VG_P2_USING = VG_KEYBOARD;

			 if(VG_2_LEFT == VG_RESET)
				 VG_2_LEFT_timer = (int)TimerGetTime() + VG_HELD_LENGTH;

			 if(VG_2_LEFT == VG_RESET) 
			 {
				VG_2_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;

				VG_2_HUDLEFT = true;
				VG_SetMove(2, VG_LEFT_FONT);
				VG_2_LEFT = VG_PRESSED; 
			 }

		/*	 if(VG_2_LEFT_timer != -1)
			 if((int)TimerGetTime() > VG_2_LEFT_timer) 
			 {
				VG_2_LEFT = VG_HELD; 
				VG_SetMove(2, VG_LEFT_FONT_H);  
				VG_2_LEFT_timer = -1; 
			 }*/
		 }
		  
	     if(!keys[VG_P2_LEFT_KEY] && !VG_2_DX_LEFT && !VG_P2_AI_LEFT_KEY)   
		 {
			 if(VG_P2_USING != VG_CONTROLLER) 
				VG_2_LEFT_pressed = false; // Temp...

			 VG_2_HUDLEFT = false;

			 VG_2_LEFT = VG_RESET; 

		  //   VG_1_LEFT_pressed = false; // Temp...

			 VG_2_DX_LEFT = false;
			 VG_P2_AI_LEFT_KEY = false; 
		 } 

	 } 
   	 if(game_paused == false)       
     if(!mode)   
     { 
		 if(VG_P1_USING == VG_CONTROLLER) 
		 if(VG_1_SOFT_DX_RIGHT) // Walking left/right...
			 VG_1_RIGHT_pressed = true; // Temp...
		 else
			 VG_1_RIGHT_pressed = false; // Temp...

		 if(keys[VG_P1_RIGHT_KEY] || VG_1_DX_RIGHT)       
		 { 

			 if(VG_P1_USING != VG_CONTROLLER) 
				VG_1_RIGHT_pressed = true; // Temp...

			 if(keys[VG_P1_RIGHT_KEY])
				 VG_P1_USING = VG_KEYBOARD;

			 if(VG_1_RIGHT == VG_RESET)
				 VG_1_RIGHT_timer = (int)TimerGetTime() + VG_HELD_LENGTH;

			// VG_1_RIGHT_pressed = true; // Temp...
			  
			 if(VG_1_RIGHT == VG_RESET)
			 {
				VG_1_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;

				VG_1_HUDRIGHT = true; 
				VG_SetMove(1, VG_RIGHT_FONT); 
				VG_1_RIGHT = VG_PRESSED; 
			 }

		/*	 if(VG_1_RIGHT_timer != -1)
			 if((int)TimerGetTime() > VG_1_RIGHT_timer) 
			 {
				VG_1_RIGHT = VG_HELD; 
				VG_SetMove(1, VG_RIGHT_FONT_H); 
				VG_1_RIGHT_timer = -1;
			 }*/

		 }
		    
	     if(!keys[VG_P1_RIGHT_KEY] && !VG_1_DX_RIGHT)     
		 { 

			 if(VG_P1_USING != VG_CONTROLLER) 
				VG_1_RIGHT_pressed = false; // Temp...

			 VG_1_HUDRIGHT = false;

			 VG_1_RIGHT = VG_RESET; 
		//	 VG_1_RIGHT_pressed = false; // Temp...

			 VG_1_DX_RIGHT = false;
		 } 
	 } 
	 if(game_paused == false)      
     if(!mode)  
     {
		 if(VG_P2_USING == VG_CONTROLLER)  
		 if(VG_2_SOFT_DX_RIGHT) // Walking left/right...
			 VG_2_RIGHT_pressed = true; // Temp...
		 else
			 VG_2_RIGHT_pressed = false; // Temp...

	     if(keys[VG_P2_RIGHT_KEY] || VG_2_DX_RIGHT || VG_P2_AI_RIGHT_KEY)                    
		 { 

			 if(VG_P2_USING != VG_CONTROLLER) 
				VG_2_RIGHT_pressed = true; // Temp...

			 if(keys[VG_P2_RIGHT_KEY])
				 VG_P2_USING = VG_KEYBOARD;

			 if(VG_2_RIGHT == VG_RESET)
				 VG_2_RIGHT_timer = (int)TimerGetTime() + VG_HELD_LENGTH;

			// VG_2_RIGHT_pressed = true; // Temp...
			  
			 if(VG_2_RIGHT == VG_RESET)
			 {
				VG_2_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;

				VG_2_HUDRIGHT = true;
				VG_SetMove(2, VG_RIGHT_FONT);
				VG_2_RIGHT = VG_PRESSED; 
			 }

		/*	 if(VG_2_RIGHT_timer != -1)
			 if((int)TimerGetTime() > VG_2_RIGHT_timer) 
			 {
				VG_2_RIGHT = VG_HELD; 
				VG_SetMove(2, VG_RIGHT_FONT_H); 
				VG_2_RIGHT_timer = -1; 
			 }*/
		 }
		    
	     if(!keys[VG_P2_RIGHT_KEY] && !VG_2_DX_RIGHT && !VG_P2_AI_RIGHT_KEY)     
		 {  

			 if(VG_P2_USING != VG_CONTROLLER) 
				VG_2_RIGHT_pressed = false; // Temp...

			 VG_2_HUDRIGHT = false;

			 VG_2_RIGHT = VG_RESET; 
		//	 VG_2_RIGHT_pressed = false; // Temp...

			 VG_P2_AI_RIGHT_KEY = false;
		 } 
   
	 } 
    if(game_paused == false)
    if(!mode)   
    { 
	     if(keys[VG_P1_PUNCH1_KEY] || VG_1_DX_X)  // 'Z'
		 {
			 if(keys[VG_P1_PUNCH1_KEY]) 
				 VG_P1_USING = VG_KEYBOARD; 

			 if(VG_1_PUNCH == VG_RESET)
				 VG_1_PUNCH_timer = (int)TimerGetTime() + VG_HELD_SUPER_LENGTH;

			 if(VG_1_PUNCH_timer != -1)  
			 if((int)TimerGetTime() > VG_1_PUNCH_timer)
			 {
				VG_1_PUNCH = VG_HELD;  
			 }

			 if(VG_1_PUNCH == VG_RESET)  
			 {
				 VG_1_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;
				 VG_1_PUNCH = VG_PRESSED;
				 VG_SetMove(1, VG_PUNCH_FONT);
			 }

		 }
		  
	     if(!keys[VG_P1_PUNCH1_KEY] && !VG_1_DX_X)          
		 {

			 if(VG_1_PUNCH == VG_HELD) 
			 {
				 VG_SetMove(1, VG_PUNCH_FONT_H);
			 }

			 VG_1_PUNCH_timer = -1;
			 VG_1_PUNCH = VG_RESET;

			 VG_1_DX_X = false;
		 }  
         
    }     
    if(game_paused == false)   
    if(!mode)    
    {    
	     if( keys[VG_P1_PUNCH2_KEY] || VG_1_DX_Y) // 'X'     
		 { 
			 if(keys[VG_P1_PUNCH2_KEY])
				 VG_P1_USING = VG_KEYBOARD;

			 if(VG_1_PUNCH2 == VG_RESET)
				 VG_1_PUNCH2_timer = (int)TimerGetTime() + VG_HELD_SUPER_LENGTH;

			 if(VG_1_PUNCH2_timer != -1)
			 if((int)TimerGetTime() > VG_1_PUNCH2_timer) 
			 {
				VG_1_PUNCH2 = VG_HELD; 
			 } 

			 if(VG_1_PUNCH2 == VG_RESET)  
			 {
				 VG_1_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;
				 VG_1_PUNCH2 = VG_PRESSED;
				 VG_SetMove(1, VG_PUNCH2_FONT);
			 }


		 }
		   
	     if(!keys[VG_P1_PUNCH2_KEY] && !VG_1_DX_Y)    
		 {

			 if(VG_1_PUNCH2 == VG_HELD)
			 {
				 VG_SetMove(1, VG_PUNCH2_FONT_H);
			 }

			 VG_1_PUNCH2_timer = -1;
			 VG_1_PUNCH2 = VG_RESET; 

			 VG_1_DX_Y = false;
		 }  
         
    }   
    if(game_paused == false)   
    if(!mode)    
    {    
	     if( keys[VG_P1_KICK1_KEY] || VG_1_DX_A)  // 'C'      
		 { 
			 if(keys[VG_P1_KICK1_KEY])
				 VG_P1_USING = VG_KEYBOARD;

			 if(VG_1_KICK == VG_RESET)
				 VG_1_KICK_timer = (int)TimerGetTime() + VG_HELD_SUPER_LENGTH;

			 if(VG_1_KICK_timer != -1)
			 if((int)TimerGetTime() > VG_1_KICK_timer) 
			 {
				VG_1_KICK = VG_HELD; 
			 } 

			 if(VG_1_KICK == VG_RESET)  
			 {
				 VG_1_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;
				 VG_1_KICK = VG_PRESSED;

				 VG_SetMove(1, VG_KICK_FONT);

				 if((int)TimerGetTime() > VG_1_DX_A_timer)
					VG_1_HUD_GO = true;
			 }

		 }
		   
	     if(!keys[VG_P1_KICK1_KEY] && !VG_1_DX_A)    
		 {

			 if(VG_1_KICK == VG_HELD) 
			 {
				 VG_SetMove(1, VG_KICK_FONT_H);
			 }

			 VG_1_KICK_timer = -1;
			 VG_1_KICK = VG_RESET; 

			 VG_1_DX_A = false;
		 }  
         
    }   
    if(game_paused == false)   
    if(!mode)    
    {    
	     if( keys[VG_P1_KICK2_KEY] || VG_1_DX_B)  // 'V'         
		 { 
			 if(keys[VG_P1_KICK2_KEY])
				 VG_P1_USING = VG_KEYBOARD;

			 if(VG_1_KICK2 == VG_RESET)
				 VG_1_KICK2_timer = (int)TimerGetTime() + VG_HELD_SUPER_LENGTH;

			 if(VG_1_KICK2_timer != -1)
			 if((int)TimerGetTime() > VG_1_KICK2_timer) 
			 {
				VG_1_KICK2 = VG_HELD; 
			 } 
			   
			 if(VG_1_KICK2 == VG_RESET)   
			 {
				 VG_1_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;
				 VG_1_KICK2 = VG_PRESSED;
				 VG_SetMove(1, VG_KICK2_FONT);
				 VG_1_HUD_BACK = true;
			 }

		 }
		   
	     if(!keys[VG_P1_KICK2_KEY] && !VG_1_DX_B)     
		 {

			 if(VG_1_KICK2 == VG_HELD)
			 {
				 VG_SetMove(1, VG_KICK2_FONT_H);
			 }

			 VG_1_KICK2_timer = -1;
			 VG_1_KICK2 = VG_RESET; 

			 VG_1_DX_B = false;
		 }  
         
    } 

    if(game_paused == false) 
    if(!mode)  
    { 
	     if(keys[VG_P2_PUNCH1_KEY] || VG_2_DX_X || VG_P2_AI_PUNCH1_KEY)                 
		 {
			 if(keys[VG_P2_PUNCH1_KEY])
				 VG_P2_USING = VG_KEYBOARD;

			 if(VG_2_PUNCH == VG_RESET)
				 VG_2_PUNCH_timer = (int)TimerGetTime() + VG_HELD_SUPER_LENGTH;

			 if(VG_2_PUNCH_timer != -1)
			 if((int)TimerGetTime() > VG_2_PUNCH_timer)
			 {
				VG_2_PUNCH = VG_HELD; 
			 }

			 if(VG_2_PUNCH == VG_RESET)  
			 {
				 VG_2_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;
				 VG_2_PUNCH = VG_PRESSED;
				 VG_SetMove(2, VG_PUNCH_FONT);
			 }

		 }
		  
	     if(!keys[VG_P2_PUNCH1_KEY]  && !VG_2_DX_X && !VG_P2_AI_PUNCH1_KEY)            
		 {

			 if(VG_2_PUNCH == VG_HELD) 
			 {
				 VG_SetMove(2, VG_PUNCH_FONT_H);
			 }

			 VG_2_PUNCH_timer = -1;
			 VG_2_PUNCH = VG_RESET;
			 VG_2_DX_X = false;

			 VG_P2_AI_PUNCH1_KEY = false;
		 }  
        
    }     
    if(game_paused == false)   
    if(!mode)    
    {    
	     if( keys[VG_P2_PUNCH2_KEY] || VG_2_DX_Y || VG_P2_AI_PUNCH2_KEY)              
		 { 
			 if(keys[VG_P2_PUNCH2_KEY])
				 VG_P2_USING = VG_KEYBOARD;

			 if(VG_2_PUNCH2 == VG_RESET)
				 VG_2_PUNCH2_timer = (int)TimerGetTime() + VG_HELD_SUPER_LENGTH;

			 if(VG_2_PUNCH2_timer != -1)
			 if((int)TimerGetTime() > VG_2_PUNCH2_timer) 
			 {
				VG_2_PUNCH2 = VG_HELD; 
			 } 

			 if(VG_2_PUNCH2 == VG_RESET)  
			 {
				 VG_2_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;
				 VG_2_PUNCH2 = VG_PRESSED;
				 VG_SetMove(2, VG_PUNCH2_FONT);
			 }
		 }
		    
	     if(!keys[VG_P2_PUNCH2_KEY] && !VG_2_DX_Y && !VG_P2_AI_PUNCH2_KEY)            
		 {

			 if(VG_2_PUNCH2 == VG_HELD) 
			 {
				 VG_SetMove(2, VG_PUNCH2_FONT_H);
			 }

			 VG_2_PUNCH2_timer = -1;
			 VG_2_PUNCH2 = VG_RESET;
			 VG_2_DX_Y = false;

			 VG_P2_AI_PUNCH2_KEY = false;
		 }  
          
    }   
    if(game_paused == false)
    if(!mode)  
    { 
	     if(keys[VG_P2_KICK1_KEY] || VG_2_DX_A || VG_P2_AI_KICK1_KEY)                
		 { 
			 if(keys[VG_P2_KICK1_KEY])
				 VG_P2_USING = VG_KEYBOARD;

			 if(VG_2_KICK == VG_RESET)
				 VG_2_KICK_timer = (int)TimerGetTime() + VG_HELD_SUPER_LENGTH;

			 if(VG_2_KICK_timer != -1)
			 if((int)TimerGetTime() > VG_2_KICK_timer)
			 {
				VG_2_KICK = VG_HELD; 
			 }

			 if(VG_2_KICK == VG_RESET)  
			 {  
				 VG_2_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;
				 VG_2_KICK = VG_PRESSED;

				 VG_SetMove(2, VG_KICK_FONT);

				 if((int)TimerGetTime() > VG_2_DX_A_timer)
					VG_2_HUD_GO = true;
			 }
		 }
		  
	     if(!keys[VG_P2_KICK1_KEY] && !VG_2_DX_A && !VG_P2_AI_KICK1_KEY)              
		 {

			 if(VG_2_KICK == VG_HELD) 
			 {
				 VG_SetMove(2, VG_KICK_FONT_H);
			 }

			 VG_2_KICK_timer = -1;
			 VG_2_KICK = VG_RESET;
			 VG_2_DX_A = false;

			 VG_P2_AI_KICK1_KEY = false;
		 }  
        
    }     
    if(game_paused == false)   
    if(!mode)    
    {    
	     if(keys[VG_P2_KICK2_KEY] || VG_2_DX_B || VG_P2_AI_KICK2_KEY)                     
		 { 
			 if(keys[VG_P2_KICK2_KEY])
				 VG_P2_USING = VG_KEYBOARD;

			 if(VG_2_KICK2 == VG_RESET)
				 VG_2_KICK2_timer = (int)TimerGetTime() + VG_HELD_SUPER_LENGTH;

			 if(VG_2_KICK2_timer != -1)
			 if((int)TimerGetTime() > VG_2_KICK2_timer) 
			 {
				VG_2_KICK2 = VG_HELD; 
			 } 

			 if(VG_2_KICK2 == VG_RESET)  
			 {
				 VG_2_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;
				 VG_2_KICK2 = VG_PRESSED;
				 VG_SetMove(2, VG_KICK2_FONT); 
				 VG_2_HUD_BACK = true;
			 }
		 }
		   
	     if(!keys[VG_P2_KICK2_KEY] && !VG_2_DX_B && !VG_P2_AI_KICK2_KEY)            
		 {

			 if(VG_2_KICK2 == VG_HELD)
			 {
				 VG_SetMove(2, VG_KICK2_FONT_H);
				 VG_2_HUD_BACK = true;
			 }

			 VG_2_KICK2_timer = -1;
			 VG_2_KICK2 = VG_RESET;  
			 VG_2_DX_B = false;

			 VG_P2_AI_KICK2_KEY = false;
		 }  
          
    }   

    if(game_paused == false)   
	if((int)TimerGetTime() > VG_1_THROW_COOLDOWN)
    if(!mode)    
    {    
	//	 if(VG_1_EQUIPMENT != EQUIPMENT_BASIC && VG_1_EQUIPMENT != EQUIPMENT_JUST_COMBO)
	     if(VG_1_DX_RS || keys[VG_P1_THROW_KEY])    
		 { 
			 if(keys[VG_P1_THROW_KEY]) 
				VG_P1_USING = VG_KEYBOARD; 

			 if(VG_1_THROW == VG_RESET) 
			 {
				 VG_1_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;
				 VG_SetMove(1, VG_KICK_AND_PUNCH_FONT);
				 VG_1_THROW = VG_PRESSED;
			 }

		 }
		 
	//	 if(VG_2_EQUIPMENT != EQUIPMENT_BASIC && VG_2_EQUIPMENT != EQUIPMENT_JUST_COMBO)
	     if(!VG_1_DX_RS && !keys[VG_P1_THROW_KEY])    
		 {
			 VG_1_THROW_timer = -1;
			 VG_1_THROW = VG_RESET;  

			 VG_1_DX_RS = false;

		 }  
            
    }  

    if(game_paused == false)    
	if((int)TimerGetTime() > VG_2_THROW_COOLDOWN)
    if(!mode)    
    {     

	     if(VG_2_DX_RS || keys[VG_P2_THROW_KEY] || VG_P2_AI_THROW_KEY)              
		 { 
			 if(keys[VG_P2_THROW_KEY])
				VG_P2_USING = VG_KEYBOARD; 

			 if(VG_2_THROW == VG_RESET)
			 {
				 VG_2_WaitForKeys = (int)TimerGetTime() + VG_WAIT_FOR_ACTION_LENGTH;
				 VG_SetMove(2, VG_KICK_AND_PUNCH_FONT); 
				 VG_2_THROW = VG_PRESSED; 
			 }

		 }
		   
	     if(!VG_2_DX_RS && !keys[VG_P2_THROW_KEY] && !VG_P2_AI_THROW_KEY)            
		 {
			 VG_2_THROW_timer = -1;
			 VG_2_THROW = VG_RESET;  

			 VG_2_DX_RS = false;
		 }  

          
    }  
 
	 if(episode != 5)
	 if(game_paused == false) 
	 if(!mode)
     if(keys[VK_ESCAPE])  
     { 
        VG_1_HUD_BACK = true;     
		VG_HUD_ESC = true;

	//	VG_ESC_pressed = true;

	 }

	 if(DEBUG_MODE == 0)
	// if(episode != 0 && scene != 15) 
	 if(game_paused == false) 
	 if(!mode)
     if(keys['1']) 
     {
                          
		keys['1'] = false; 

		episode = 6;

		scene = 0;

		next_scene = true;

		VG_1_pressed = true;

	 }  
	 if(DEBUG_MODE == 0)
	 if(episode != 0 && scene != 15)
	 if(game_paused == false) 
	 if(!mode)
     if(keys['2']) 
     {
                            
		keys['2'] = false;  

		mid_x = sprite[2].x + (sprite[2].width / 1.8f); 
		mid_y = sprite[2].y + (sprite[2].height * 0.8f);

		VG_Particles(mid_x, mid_y, 2.8f, 1, 49);

		VG_2_pressed = true;

	 }
	 if(DEBUG_MODE == 0) 
	 if(episode != 0 && scene != 15)
	 if(game_paused == false) 
	 if(!mode)
     if(keys['3']) 
     { 
                          
		keys['3'] = false;  

		VG_Display_moves ^= 1; 

		VG_3_pressed = true;

	 }
	 if(DEBUG_MODE == 0)
	 if(episode != 0 && scene != 15) 
	 if(game_paused == false) 
	 if(!mode)
     if(keys['4']) 
     {
                          
		keys['4'] = false;  

		VG_AI_active ^= 1; 
		VG_BATTLE_ROUND = 2;

		VG_AI_LEVEL = 5;

		VG_2_EQUIPMENT = EQUIPMENT_ALL;

		keys[VK_DOWN] = false;
		keys[VK_LEFT] = false;       
		keys[VK_RIGHT] = false;
		keys[VK_UP] = false;

		keys['Z'] = false;  
		keys['C'] = false;  
		keys['V'] = false; 
		keys['X'] = false; 
	 }
	 if(DEBUG_MODE == 0)
	 if(episode != 0 && scene != 15) 
	 if(game_paused == false) 
	 if(!mode)
     if(keys['5']) 
     {
                          
		keys['5'] = false;   

		TEST_POINTS ^= 1;  

	 }
	 if(DEBUG_MODE == 0) 
	 if(episode != 0 && scene != 15)
	 if(game_paused == false)    
	 if(!mode)   
     if(keys['6']) 
     {
                               
		keys['6'] = false;    

		VG_SlowMO(12000, 2.0f);


	 }
	 if(DEBUG_MODE == 0)
	 if(episode != 0 && scene != 15)
	 if(game_paused == false) 
	 if(!mode)
     if(keys['7']) 
     {                    
                              
		keys['7'] = false;    
/*  
		sprite[3].electrocute = true; 

		sprite[3].status = VG_KNOCKDOWN_FONT;
		sprite[3].knockdown = true;

		VG_1_MovesList[0] = VG_KNOCKDOWN_FONT;
		VG_1_MovesList_count = 3;
		VG_1_MOVE_ACTIVE = false;

		// Over-ride any current move...
		Run_Moves(1, 1);*/


//		sprite[3].special = 4;
//		VK_KEY_AI_SPECIAL1 = true;


		#if IS_FULL_STEAM == 1   
				 
        if(STEAM_ACTIVE == true)    
		{
			//SteamUserStats()->ResetAllStats(true);
			VG_okay_sfx = true;
		}
				 
		#endif 

	 }

	 if(game_paused == false) 
	 if(!mode)
     if(keys[VK_CONTROL] && keys['Q']) // Zoom function
     {

         keys['Q']=false;  
		 keys[VK_CONTROL] = false;
         
		if(DEBUG_MODE == 0)     
		{

             end_sfx=NO_ANIM;          
             quitting = true;
             quit_timer = (int)TimerGetTime() + 100; 
 

		} 
		 
	 }

    if(DEMO_MODE == 0)    
    if(game_paused == false)
    if(keys[VK_SHIFT] && keys['J'] )   
    {
         keys['J']=false;  
		 keys[VK_SHIFT] = false;
                        
         if(!(scene)==0)
            scene --;

                                     
         LoadScene( episode, scene, true );
        
         if(game_mode != WALK && mode && game_mode != WORLD)
         {
            camX = 0.0f;
            camY = 0.0f;
            zoom_factor = 1.2f;
         }
        
         selection = 0;   

    }

    if(DEMO_MODE == 0)    
    if(game_paused == false)
    if( keys[VK_SHIFT] && keys['K'] )
    { 
         keys['K']=false;
		 keys[VK_SHIFT] = false;

         scene++;
   

         LoadScene( episode, scene, true );
                 
         if(game_mode != WALK && mode && game_mode != WORLD)
         {
            camX = 0.0f;
            camY = 0.0f;
            zoom_factor = 1.2f;
         }
        
         selection = 0;  
        
    }  
     
    if(game_paused == false)  
	if(!mode)
	{ 
		 
	     if(VG_1_DX_LS || keys[VG_P1_BLOCK_KEY])              
		 {  
			 if(sprite[2].handcuffed == false && sprite[2].knockdown == false && sprite[2].jumping == false
			 && sprite[2].status != VG_KNOCKSLIDE_FONT && sprite[2].status != VG_RELOAD_FONT)
			 {
				VG_1_BLOCKING = true;
			//	VG_1_UP_pressed = false; // Temp...
				VG_1_UP = VG_RESET; 
				keys[VG_P1_UP_KEY] = false;
				VG_1_DX_UP = false;
			 }
		 }
		     
	     if(!VG_1_DX_LS && !keys[VG_P1_BLOCK_KEY])              
		 {  

			 VG_1_BLOCKING = false;
			 VG_1_DX_LS = false;

		 }   
		 if(VG_2_DX_LS|| keys[VG_P2_BLOCK_KEY] || VG_P2_AI_BLOCK_KEY) 
		 {
			 if(sprite[3].handcuffed == false && sprite[3].knockdown == false && sprite[3].jumping == false
			 && sprite[3].status != VG_KNOCKSLIDE_FONT && sprite[3].status != VG_RELOAD_FONT)
			 {
			//	VG_P2_AI_BLOCK_KEY = false;
				VG_2_BLOCKING = true;
			//	VG_2_UP_pressed = false; // Temp...
				VG_2_UP = VG_RESET; 
				keys[VG_P2_UP_KEY] = false;
				VG_2_DX_UP = false;
			 }
		 }
		   
	     if(!VG_2_DX_LS && !keys[VG_P2_BLOCK_KEY] && !VG_P2_AI_BLOCK_KEY)             
		 {  
		//	 VG_P2_AI_BLOCK_KEY = false;
			 VG_2_BLOCKING = false;
			 VG_2_DX_LS = false;
		 }  


	}

    if(game_paused == false) 
	if (keys[VK_F5]) 
	{

		keys[VK_F5] = false;

		if(game_paused == false)        
		if(DEMO_MODE == 0) 
		{    

			mode = PLACEMENT;
			LoadScene( episode, scene, true );

		   if(!mode)
		   { 
			   sprintf( temp_string.string, "Data/verdict/font");                

			   Change_Texture(temp_string, 0);  
		   }
		   else
		   {
			   sprintf( temp_string.string, "Data/hud/font");                
			   Change_Texture(temp_string, 0);  
		   }

		}

	}

	 //if(game_paused == false)      
     //if(DEMO_MODE == 0) 
     /*if(keys[VK_F2])
     { 
         keys[VK_F2]=false;
         
         if(debug_active == true)
         {
             debug_active = false;                   
         }
         else
         {
             debug_active = true;
         }
          
     }   */
	   
	if(episode == 5)
	if(VG_STORY_PAUSE == false)
	if((int)TimerGetTime() > VG_pause_button_timer && fade == 1.0) 
	if(game_paused == false && (keys[VK_RETURN] || VG_1_DX_START == true || VG_2_DX_START == true || (keys[VK_ESCAPE] == true && game_paused == false) )
	|| game_paused == true && (keys[VK_RETURN] || VG_1_DX_START == true && VG_PLAYER_1_PAUSED == true) 
	|| game_paused == true && (VG_2_DX_START == true && VG_PLAYER_1_PAUSED == false)
	) 
	{

		 if(keys[VK_RETURN] || VG_1_DX_START == true || (keys[VK_ESCAPE] == true && game_paused == false) || VG_STORY_PAUSE == true)
			VG_PLAYER_1_PAUSED = true;
		 else
			VG_PLAYER_1_PAUSED = false;

         keys[VK_RETURN]=false;					// If So Make Key FALSE
		 keys[VK_ESCAPE]=false;
		 VG_1_DX_START = false;
		 VG_2_DX_START = false;

		 VG_1_DX_A = false;
		 VG_1_DX_B = false;

         if(!mode) 
         { 

			 if(next_scene == false) //  
			 if(episode == 5) 
			 {
				game_paused ^= 1;

				vg_pause_sfx = true;

				if(game_paused == false)   
				{

					pause_music=true; 

					timer_addition += TimerGetTime() - pause_timer_start; 

					AI_Time = (int)TimerGetTime();
					Animate_Time = (int)TimerGetTime();  //8
					Swap_Time = (int)TimerGetTime() + SWAP_RATE;
					Steam_Time = (int)TimerGetTime() + STEAM_RATE;

					Key_Start = (int)TimerGetTime();
					Main_Start = (int)TimerGetTime(); 
					Code_Start = (int)TimerGetTime();
					Code_Time = (int)TimerGetTime();
					Main_Time = (int)TimerGetTime();

					Main_cycle = (int)TimerGetTime();
					Draw_cycle = (int)TimerGetTime(); 
					Ai_cycle = (int)TimerGetTime();
					Swap_cycle = (int)TimerGetTime();
					Key_Time = (int)TimerGetTime(); 
					Real_Time = (int)TimerGetTime();
					time_diff = (int)TimerGetTime(); 

					VG_pause_button_timer = (int)TimerGetTime() + 500;

					view_cone_timer = (int)TimerGetTime(); 
					render_bg = TimerGetTime();

					double_main_code = 0;
					render_sequence=0; 

				} 
				else 
				{ 

					VG_play_pause_menu = true;

				   pause_music=true;

	               pause_timer_start = TimerGetTime();

					AI_Time = (int)TimerGetTime();
					Animate_Time = (int)TimerGetTime();  //8
					Swap_Time = (int)TimerGetTime() + SWAP_RATE;
					Steam_Time = (int)TimerGetTime() + STEAM_RATE;

					Key_Start = (int)TimerGetTime();
					Main_Start = (int)TimerGetTime();
					Code_Start = (int)TimerGetTime();
					Code_Time = (int)TimerGetTime();
					Main_Time = (int)TimerGetTime();

					Main_cycle = (int)TimerGetTime();
					Draw_cycle = (int)TimerGetTime();
					Ai_cycle = (int)TimerGetTime();
					Swap_cycle = (int)TimerGetTime();
					Key_Time = (int)TimerGetTime(); 
					Real_Time = (int)TimerGetTime();
					time_diff = (int)TimerGetTime(); 

					VG_pause_button_timer = (int)TimerGetTime() + 500;

					view_cone_timer = (int)TimerGetTime(); 
					render_bg = TimerGetTime();

					double_main_code = 0;
					render_sequence=0;
				}

             } // episode == 5

         } // !mode

	} // keys[VK_RETURN] 

	// Story mode start-up help text...
	if(episode == 5)
	if(VG_GAME_MODE == VG_STORY_MODE) 
	if(VG_STORY_PAUSE == true)
	if((int)TimerGetTime() > VG_pause_button_timer && fade == 1.0) 
	if(game_paused == false || (game_paused == true && (keys[VG_P1_KICK1_KEY] || VG_1_DX_A || keys[VG_P1_KICK2_KEY] || VG_1_DX_B ) )
	) 
	{

		 VG_PLAYER_1_PAUSED = true;

         keys[VK_RETURN]=false;					// If So Make Key FALSE
		 keys[VK_ESCAPE]=false;
		 VG_1_DX_START = false;
		 VG_2_DX_START = false;

		 VG_1_DX_A = false;
		 VG_1_DX_B = false;

         if(!mode) 
         { 

			 if(next_scene == false) //  && fade == 1.0
			 if(episode == 5) 
			 {
				game_paused ^= 1;

				vg_pause_sfx = true;

				if(game_paused == false)   
				{
					VG_STORY_PAUSE = false;

					pause_music=true; 

					timer_addition += TimerGetTime() - pause_timer_start; 

					AI_Time = (int)TimerGetTime();
					Animate_Time = (int)TimerGetTime();  //8
					Swap_Time = (int)TimerGetTime() + SWAP_RATE;
					Steam_Time = (int)TimerGetTime() + STEAM_RATE;

					Key_Start = (int)TimerGetTime();
					Main_Start = (int)TimerGetTime(); 
					Code_Start = (int)TimerGetTime();
					Code_Time = (int)TimerGetTime();
					Main_Time = (int)TimerGetTime();

					Main_cycle = (int)TimerGetTime();
					Draw_cycle = (int)TimerGetTime(); 
					Ai_cycle = (int)TimerGetTime();
					Swap_cycle = (int)TimerGetTime();
					Key_Time = (int)TimerGetTime(); 
					Real_Time = (int)TimerGetTime();
					time_diff = (int)TimerGetTime(); 

					VG_pause_button_timer = (int)TimerGetTime() + 500;

					view_cone_timer = (int)TimerGetTime(); 
					render_bg = TimerGetTime();

					double_main_code = 0;
					render_sequence=0; 

				} 
				else 
				{ 

					VG_play_pause_menu = true;

				    pause_music=true;

	                pause_timer_start = TimerGetTime();

					AI_Time = (int)TimerGetTime();
					Animate_Time = (int)TimerGetTime();  //8
					Swap_Time = (int)TimerGetTime() + SWAP_RATE;
					Steam_Time = (int)TimerGetTime() + STEAM_RATE;

					Key_Start = (int)TimerGetTime();
					Main_Start = (int)TimerGetTime();
					Code_Start = (int)TimerGetTime();
					Code_Time = (int)TimerGetTime();
					Main_Time = (int)TimerGetTime();

					Main_cycle = (int)TimerGetTime();
					Draw_cycle = (int)TimerGetTime();
					Ai_cycle = (int)TimerGetTime();
					Swap_cycle = (int)TimerGetTime();
					Key_Time = (int)TimerGetTime(); 
					Real_Time = (int)TimerGetTime();
					time_diff = (int)TimerGetTime(); 

					VG_pause_button_timer = (int)TimerGetTime() + 500;

					view_cone_timer = (int)TimerGetTime(); 
					render_bg = TimerGetTime();

					double_main_code = 0;
					render_sequence=0;
				}

             } // episode == 5

         } // !mode

	} // keys[VK_RETURN] 

	 return true;   

}

void VG_Upload_Score(int type)
{

	int temp_mins = 5;
	int temp_secs = 45;
	int temp_round = 7;
	int temp_character = 1;
	int temp_perfects = 6;
	int temp_arrests = 7;
	int temp_score = 0;
	int temp_perfects_arrests=13;
	int temp_survival_wins=0;
		    
	if(VG_SURVIVAL == false)
	{
		temp_secs = VG_1_TOTAL_SECS;   
		temp_mins = VG_1_TOTAL_MINS;
		 
		temp_round = VG_BATTLE_ROUND;      
		temp_character = VG_1_CHARACTER;  
		temp_perfects = VG_1_TOTAL_perfects;        
		temp_arrests = VG_1_TOTAL_arrests;   
		 
		temp_perfects_arrests = VG_1_TOTAL_perfects + VG_1_TOTAL_arrests; 

		temp_secs = 99 - temp_secs;
		temp_mins = 99 - temp_mins;

		VG_FINAL_SCORE = 0;
		VG_FINAL_SCORE += temp_character;
		VG_FINAL_SCORE += temp_secs*10;
		VG_FINAL_SCORE += temp_mins*1000;
		VG_FINAL_SCORE += temp_perfects_arrests*100000;
		VG_FINAL_SCORE += (temp_round*10000000);
	}
	if(VG_SURVIVAL == true)
	{
		temp_secs = VG_1_TOTAL_SECS;   
		temp_mins = VG_1_TOTAL_MINS;
 
		temp_character = VG_1_CHARACTER;  
		temp_survival_wins = VG_SURVIVAL_WINS; 

		temp_secs = 99 - temp_secs;
		temp_mins = 99 - temp_mins;

		VG_FINAL_SCORE = 0;
		VG_FINAL_SCORE += temp_character;
		VG_FINAL_SCORE += temp_secs*10;
		VG_FINAL_SCORE += temp_mins*1000;
		VG_FINAL_SCORE += temp_survival_wins*100000;
	}


	#if IS_FULL_STEAM == 1  
	 
	/*if(STEAM_ACTIVE == true)  
	{
		if(VG_STEAM_DEMO == 0)
		{
			if(VG_SURVIVAL == true)
				Upload_Scores(1);
			else
			{
				if(VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_STANDARD)
					Upload_Scores(0);
				if(VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_DUELLING)
					Upload_Scores(2);
				if(VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_TURBO)
					Upload_Scores(3);
				if(VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_MASTER)
					Upload_Scores(4);

			}
		}
	}       */

	#endif 








}