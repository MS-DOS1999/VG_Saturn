#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64 
#define WIN32_LEAN_AND_MEAN  
#include <windows.h> 
#endif 


extern void Refresh_Window(int new_renderer);
extern void VG_Moveslist(int counter, int character, int index, int player);
extern void VG_Init_Story(int character);

extern void VG_Put_Temps_Into_Keys();
extern void VG_Put_Keys_Into_Temps();
extern void VG_Put_Keys_Into_Temps();
extern bool VG_Scan_for_Input();
extern bool VG_Check_Key_Available(int player);

bool Run_Frontend(int f_rate);

#define PLAY_YES_SFX  0
#define PLAY_NO_SFX  0


float vg_Y_align = 0.0f;
bool temp_fullscreen = false;
bool temp_backgrounds_random = false;
int temp_renderer = 0;
bool temp_lowres = false;

bool vg_key_taken = false;
int vg_key_taken_timer = 0;

int vg_key_check_player = 1;

void VG_reset_input()
{ 
	VG_1_PUNCH = VG_RESET;
	VG_1_PUNCH2 = VG_RESET;
	VG_1_KICK = VG_RESET; 
	VG_1_KICK2 = VG_RESET;
	VG_1_DX_A = false;
	VG_1_DX_B = false;
	VG_1_HUD_GO = false;
	VG_1_HUD_BACK = false;
	
}


void sta2_Scroll(int number, bool startup, int f_rate, int direction)
{
	float temp_speed=0.0f;
	 
/*	if(startup == true)
	{
		 if(direction == UP)
		 {
			new_counter[number].scroll = new_counter[number].y;
			new_counter[number].y -= new_counter[number].height*3;
		 }
		 if(direction == DOWN)
		 {
			new_counter[number].scroll = new_counter[number].y;
			new_counter[number].y += new_counter[number].height*3;
		 }
		 if(direction == LEFT)
		 {
			new_counter[number].scroll = new_counter[number].x;
			new_counter[number].x += new_counter[number].height*6;
		 }
		 if(direction == RIGHT)
		 {
			new_counter[number].scroll = new_counter[number].x;
			new_counter[number].x -= new_counter[number].height*6;
		 }

	}
	else
	{

		 if(direction == UP)  
		 {
			 temp_speed = 0.00036f*(float)f_rate;
			 new_counter[number].y += temp_speed;
		    if(new_counter[number].y > new_counter[number].scroll)
			   new_counter[number].y = new_counter[number].scroll;
		 }
		 if(direction == DOWN)
		 {
			 temp_speed = 0.00036f*(float)f_rate;
			 new_counter[number].y -= temp_speed;
		    if(new_counter[number].y < new_counter[number].scroll)
			   new_counter[number].y = new_counter[number].scroll;
		 }
		 if(direction == LEFT)
		 {
			 temp_speed = 0.00064f*(float)f_rate;
			 new_counter[number].x -= temp_speed;
		    if(new_counter[number].x < new_counter[number].scroll)
			   new_counter[number].x = new_counter[number].scroll;
		 }
		 if(direction == RIGHT)
		 {
			 temp_speed = 0.00064f*(float)f_rate;
			 new_counter[number].x += temp_speed;
		    if(new_counter[number].x > new_counter[number].scroll)
			   new_counter[number].x = new_counter[number].scroll;
		 }

	}*/

}
 
void SwipeCode(int f_rate) 
{


}

bool Run_Frontend(int f_rate) 
{   
	bool success=true;
	char string_value[1024];
	float testX=0.0f, testY=0.0f;
	float incY=0.0f;
	int rnd = 0;
	int index = 0; 
	int slongest_line=0;
	int temp_id=0;
	float X_align=0.0f;
	float Y_align=0.0f;
	float temp_Y_align=0.0f;
	float temp_speed=0.0f;
	char punch;
	char punch2;
	char kick;
	char kick2;
	char up;
	char down;
	char left;
	char right;
	char block;
	char throw_key;
	int vg_temp_score=0;
	int vg_index_display=0;
	int vg_index_char=0;
	int temp_mins=0;
	int temp_secs=0;
	int temp_perfects=0;
	int temp_arrests=0;

//	char name1[1024];
//	char name2[1024];
                   
	if(f_rate <= 0)                                                
	    f_rate = 1;        
	                    
	if(f_rate > 100)         
		f_rate = 100;  

    // ******************************************************************************//
    //                           0-2  (FRONTEND OPTIONS)                             //
    // ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode) 
   if(next_scene == false)
   if(episode == 0 && scene == 2)        
   {       
		 
		if(title_sequence == 0) 
		{ 
			VG_SELECTED = 0;

			X_align = -0.17f;  
			Y_align = +0.20f;    

			sprintf( new_counter[0].word, "OPTION MODE"); 

			new_counter[0].alpha = 1.0f;        
			new_counter[0].id = 2; 
		      
			new_counter[0].type = 0;  // Large Font...
			new_counter[0].right = false; 

			new_counter[0].x = X_align+0.05f;      
			new_counter[0].y = +0.29f;  	      

			new_counter[0].w = new_counter[0].x - 0.026f;   
			new_counter[0].z = new_counter[0].y - 0.015f;

			new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
			new_counter[0].box_height = new_counter[0].height - 0.015f;	

			sprintf( new_counter[1].word, "SOUND OPTIONS"); 

			new_counter[1].alpha = 1.0f;          
			new_counter[1].id = 0;  
		      
			new_counter[1].type = 0;  // Large Font...
			new_counter[1].right = false; 

			new_counter[1].x = X_align;               
			new_counter[1].y = Y_align;    	      

			new_counter[1].w = new_counter[1].x - 0.026f;   
			new_counter[1].z = new_counter[1].y - 0.015f;
			     
			new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
			new_counter[1].box_height = new_counter[1].height - 0.015f;	

			sprintf( new_counter[2].word, "VERSUS OPTIONS"); 

			new_counter[2].alpha = 1.0f;           
			new_counter[2].id = 0;  
		      
			new_counter[2].type = 0;  // Large Font...
			new_counter[2].right = false;

			new_counter[2].x = X_align;             
			new_counter[2].y = new_counter[1].y-0.06f;       	      

			new_counter[2].w = new_counter[2].x - 0.026f;   
			new_counter[2].z = new_counter[2].y - 0.015f;

			new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
			new_counter[2].box_height = new_counter[2].height - 0.015f;	

			sprintf( new_counter[3].word, "CREDITS"); 

			new_counter[3].alpha = 1.0f;           
			new_counter[3].id = 0; 
		      
			new_counter[3].type = 0;  // Large Font...
			new_counter[3].right = false;

			new_counter[3].x = X_align;             
			new_counter[3].y = new_counter[2].y-0.06f;        	      

			new_counter[3].w = new_counter[3].x - 0.026f;   
			new_counter[3].z = new_counter[3].y - 0.015f;

			new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
			new_counter[3].box_height = new_counter[3].height - 0.015f;	

			sprintf( new_counter[4].word, "BACK"); 

			new_counter[4].alpha = 1.0f;           
			new_counter[4].id = 0; 
		      
			new_counter[4].type = 0;  // Large Font...
			new_counter[4].right = false;

			new_counter[4].x = X_align;             
			new_counter[4].y = new_counter[3].y-0.06f;          	      

			new_counter[4].w = new_counter[4].x - 0.026f;   
			new_counter[4].z = new_counter[4].y - 0.015f;

			new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
			new_counter[4].box_height = new_counter[4].height - 0.015f;	

			sprintf( new_counter[5].word, "UNUSED"); 

			new_counter[5].alpha = 0.0f;           
			new_counter[5].id = 0; 
		      
			new_counter[5].type = 0;  // Large Font...
			new_counter[5].right = false;

			new_counter[5].x = X_align;             
			new_counter[5].y = new_counter[4].y-0.06f;          	      

			new_counter[5].w = new_counter[5].x - 0.026f;   
			new_counter[5].z = new_counter[5].y - 0.015f;

			new_counter[5].box_width = strlen(new_counter[5].word)   *  0.026f;
			new_counter[5].box_height = new_counter[5].height - 0.015f;	

			sprintf( new_counter[6].word, "UNUSED"); 

			new_counter[6].alpha = 0.0f;               
			new_counter[6].id = 0; 
		      
			new_counter[6].type = 0;  // Large Font...
			new_counter[6].right = false;
			 
			new_counter[6].x = X_align;             
			new_counter[6].y = new_counter[5].y-0.06f;          	      

			new_counter[6].w = new_counter[6].x - 0.026f;   
			new_counter[6].z = new_counter[6].y - 0.015f;

			new_counter[6].box_width = strlen(new_counter[6].word)   *  0.026f;
			new_counter[6].box_height = new_counter[6].height - 0.015f;	

			sprintf( new_counter[7].word, "UNUSED"); 

			new_counter[7].alpha = 0.0f;              
			new_counter[7].id = 0; 
		      
			new_counter[7].type = 0;  // Large Font...
			new_counter[7].right = false;
			 
			new_counter[7].x = X_align;             
			new_counter[7].y = new_counter[6].y-0.06f;          	      

			new_counter[7].w = new_counter[7].x - 0.026f;   
			new_counter[7].z = new_counter[7].y - 0.015f;

			new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
			new_counter[7].box_height = new_counter[7].height - 0.015f;	

			sprintf( new_counter[8].word, "UNUSED"); 

			new_counter[8].alpha = 0.0f;                
			new_counter[8].id = 0;  
		      
			new_counter[8].type = 0;  // Large Font...
			new_counter[8].right = false;

			new_counter[8].x = X_align;                
			new_counter[8].y = new_counter[7].y-0.06f;          	      

			new_counter[8].w = new_counter[7].x - 0.026f;   
			new_counter[8].z = new_counter[7].y - 0.015f;

			new_counter[8].box_width = strlen(new_counter[8].word)   *  0.026f;
			new_counter[8].box_height = new_counter[8].height - 0.015f;	
			 
			new_counter[9].alpha = 1.0f;                 
			new_counter[9].id = 3;        
				   
			new_counter[9].type = 1;  // Small Font...
			new_counter[9].right = false;

			new_counter[9].x = -0.28f;                     
			new_counter[9].y = VG_BOTTOM_OPTIONS_OFFSET;          
			 
			new_counter[9].w = new_counter[9].x - 0.026f;   
			new_counter[9].z = new_counter[9].y - 0.015f;

			new_counter[9].box_width = strlen(new_counter[9].word)   *  0.026f;
			new_counter[9].box_height = new_counter[9].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[9].word, "%c-%c MOVE  %c: SELECT %c: BACK^&RETRO ARMY LTD. 2015-2019", VG_P1_UP_KEY_DSY, VG_P1_DOWN_KEY_DSY, VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
		else
			sprintf( new_counter[9].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015-2019");

		if(title_sequence == 1) 
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == VG_PRESSED)
			{
				VG_reset_input();
				vg_next_episode = 0;
				vg_next_scene  = 1;

				next_scene = true;
			}

			if(VG_1_HUDDOWN == VG_PRESSED)
			{
				vg_titlemove_sfx = true;
				VG_SELECTED++;
				if(VG_SELECTED > 3)   
					VG_SELECTED = 0;
				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false;
			} 

			if(VG_1_HUDUP == VG_PRESSED)
			{
				vg_titlemove_sfx = true; 
				VG_SELECTED--;
				if(VG_SELECTED < 0)
					VG_SELECTED = 3; 
				VG_1_HUDUP = false;
				VG_2_HUDUP = false;
			}

			new_counter[1].id = 0;
			new_counter[2].id = 0;
			new_counter[3].id = 0;
			new_counter[4].id = 0;
			new_counter[5].id = 0;
			new_counter[6].id = 0;
			new_counter[7].id = 0;
			new_counter[8].id = 0;

			if(VG_SELECTED == 0) // SOUND OPTIONS
			{   
				new_counter[1].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				}
			}
			if(VG_SELECTED == 1) // VERSUS OPTIONS
			{   
				new_counter[2].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				}
			}
			if(VG_SELECTED == 2) // CREDITS
			{   
				new_counter[3].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				}
			}
			if(VG_SELECTED == 3) // BACK
			{   
				new_counter[4].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				}
			}
			if(VG_SELECTED == 4) // CREDITS 
			{   
				new_counter[5].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				}
			}
			if(VG_SELECTED == 5) // CONTROLS  
			{   
				new_counter[6].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				}
			}
			if(VG_SELECTED == 6) // SCOREBOARDS  
			{   
				new_counter[7].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				}
			}
			if(VG_SELECTED == 7) // BACK
			{   
				new_counter[8].id = 2; 

				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				}
			} 

		} // title_sequence == 1

		if(title_sequence == 2)   
		{
			if((int)TimerGetTime() > VG_Flicker_HUD_Button_timer)
			{
				VG_Flicker_HUD_Button_timer = (int)TimerGetTime() + 25;
				 
				if(VG_SELECTED == 0) // SOUND OPTIONS
				{
					if(new_counter[1].id == 0)
						new_counter[1].id = 2;
					else
						new_counter[1].id = 0;
				} 
				if(VG_SELECTED == 1) // DISPLAY OPTIONS
				{
					if(new_counter[2].id == 0)
						new_counter[2].id = 2;
					else
						new_counter[2].id = 0;
				}   
				if(VG_SELECTED == 2) // VIDEO OPTIONS 
				{
					if(new_counter[3].id == 0)  
						new_counter[3].id = 2; 
					else 
						new_counter[3].id = 0;
				} 
				if(VG_SELECTED == 3) // VERSUS OPTIONS
				{
					if(new_counter[4].id == 0)
						new_counter[4].id = 2;
					else
						new_counter[4].id = 0;
				}
				if(VG_SELECTED == 4) // CREDITS
				{
					if(new_counter[5].id == 0)
						new_counter[5].id = 2;
					else
						new_counter[5].id = 0;
				}
				if(VG_SELECTED == 5) // CONTROLS  
				{
					if(new_counter[6].id == 0)
						new_counter[6].id = 2;
					else
						new_counter[6].id = 0;
				}
				if(VG_SELECTED == 6) // SCOREBOARDS  
				{
					if(new_counter[7].id == 0)
						new_counter[7].id = 2;
					else
						new_counter[7].id = 0;
				}
				if(VG_SELECTED == 7) // BACK  
				{
					if(new_counter[8].id == 0)
						new_counter[8].id = 2;
					else
						new_counter[8].id = 0;
				}
			} 
			   
			if((int)TimerGetTime() > title_timer)
			{
				if(VG_SELECTED == 0) // SOUND OPTIONS
				{ 
						 
					mouseleft = false;        
					DX_SHOOT = false;  
						  
					vg_next_episode = 0;        
					vg_next_scene  = 4;


					next_scene = true;
				}
				if(VG_SELECTED == 1) // VERSUS OPTIONS
				{ 
						 
					mouseleft = false;        
					DX_SHOOT = false;  
						 
					vg_next_episode = 0;       
					vg_next_scene  = 12;


					next_scene = true;
				}
				if(VG_SELECTED == 2) // CREDITS
				{ 
						 
					mouseleft = false;        
					DX_SHOOT = false;  
						 
					vg_next_episode = 0;     
					vg_next_scene  = 6;


					next_scene = true;
				}
				if(VG_SELECTED == 3) // BACK
				{ 
						 
					mouseleft = false;        
					DX_SHOOT = false;  
						 
					vg_next_episode = 0;   
					vg_next_scene  = 1;


					next_scene = true;
				}
				if(VG_SELECTED == 4) // CREDITS 
				{ 
						 
					mouseleft = false;        
					DX_SHOOT = false;  
						 
					vg_next_episode = 0;   
					vg_next_scene  = 6;


					next_scene = true;
				}
				if(VG_SELECTED == 5) // CONTROLS 
				{ 
						 
					mouseleft = false;        
					DX_SHOOT = false;  
						 
					vg_next_episode = 0;   
					vg_next_scene  = 14;


					next_scene = true;
				}
				if(VG_SELECTED == 6) // SCOREBOARDS 
				{ 
						 
					mouseleft = false;        
					DX_SHOOT = false;  

					vg_next_episode = 0;   
					vg_next_scene  = 13;


					next_scene = true;
				}
				if(VG_SELECTED == 7) // BACK
				{
						 
					mouseleft = false;        
					DX_SHOOT = false;  
						 
					vg_next_episode = 0;   
					vg_next_scene  = 1;


					next_scene = true;
				}

			}



		}

   }   

   // ******************************************************************************//
   //                              0-4  (SOUND OPTIONS)                             //
   // ******************************************************************************//

  // Title Screen Stuff... 
   if(!mode) 
   if(next_scene == false) 
   if(episode == 0 && scene == 4)         
   {       
		 
		if(title_sequence == 0) 
		{ 

			sprite[3].width = sprite[3].box_width * music_volume; // Music volume
			sprite[4].width = sprite[4].box_width * sfx_volume; // Sound volume

			VG_SELECTED = 0;
			 
			X_align = -0.21f;    
			Y_align = +0.20f;    

			sprintf( new_counter[0].word, "SOUND OPTIONS"); 

			new_counter[0].alpha = 1.0f;        
			new_counter[0].id = 2; 
		      
			new_counter[0].type = 0;  // Large Font...
			new_counter[0].right = false; 

			new_counter[0].x = X_align+0.07f;      
			new_counter[0].y = +0.29f;  	      

			new_counter[0].w = new_counter[0].x - 0.026f;   
			new_counter[0].z = new_counter[0].y - 0.015f;

			new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
			new_counter[0].box_height = new_counter[0].height - 0.015f;	

			sprintf( new_counter[1].word, "MUSIC VOLUME"); 

			new_counter[1].alpha = 1.0f;            
			new_counter[1].id = 3;    
		      
			new_counter[1].type = 0;  // Large Font...
			new_counter[1].right = false; 
			 
			new_counter[1].x = X_align;               
			new_counter[1].y = Y_align;    	      

			new_counter[1].w = new_counter[1].x - 0.026f;   
			new_counter[1].z = new_counter[1].y - 0.015f;
			     
			new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
			new_counter[1].box_height = new_counter[1].height - 0.015f;	

			sprintf( new_counter[2].word, "SOUND VOLUME"); 

			new_counter[2].alpha = 1.0f;            
			new_counter[2].id = 3;  
		      
			new_counter[2].type = 0;  // Large Font...
			new_counter[2].right = false;
			  
			new_counter[2].x = X_align;             
			new_counter[2].y = new_counter[1].y-0.12f;        	      

			new_counter[2].w = new_counter[2].x - 0.026f;   
			new_counter[2].z = new_counter[2].y - 0.015f;

			new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
			new_counter[2].box_height = new_counter[2].height - 0.015f;	

			sprintf( new_counter[3].word, "BACK");  
			 
			new_counter[3].alpha = 1.0f;              
			new_counter[3].id = 0;  
		      
			new_counter[3].type = 0;  // Large Font...
			new_counter[3].right = false;

			new_counter[3].x = X_align;             
			new_counter[3].y = new_counter[2].y-0.12f;            	      

			new_counter[3].w = new_counter[3].x - 0.026f;   
			new_counter[3].z = new_counter[3].y - 0.015f;

			new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
			new_counter[3].box_height = new_counter[3].height - 0.015f;	

			sprintf( new_counter[7].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015-2019");
			 
			new_counter[7].alpha = 1.0f;                 
			new_counter[7].id = 3;        
				  
			new_counter[7].type = 1;  // Small Font...
			new_counter[7].right = false;

			new_counter[7].x = -0.28f;                    
			new_counter[7].y = VG_BOTTOM_OPTIONS_OFFSET;           

			new_counter[7].w = new_counter[7].x - 0.026f;   
			new_counter[7].z = new_counter[7].y - 0.015f;

			new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
			new_counter[7].box_height = new_counter[7].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[7].word, "%c-%c MOVE  %c: SELECT %c: BACK^&RETRO ARMY LTD. 2015-2019", VG_P1_UP_KEY_DSY, VG_P1_DOWN_KEY_DSY, VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
		else
			sprintf( new_counter[7].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015-2019");

		if(title_sequence == 1) 
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == VG_PRESSED)
			{
				VG_reset_input();
				vg_next_episode = 0;
				vg_next_scene  = 2;

				next_scene = true;
			}

			if(VG_1_HUDDOWN == VG_PRESSED)
			{
				vg_titlemove_sfx = true;
				VG_SELECTED++;
				if(VG_SELECTED > 2)   
					VG_SELECTED = 0; 
				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false;
			} 

			if(VG_1_HUDUP == VG_PRESSED)
			{
				vg_titlemove_sfx = true;
				VG_SELECTED--;
				if(VG_SELECTED < 0)
					VG_SELECTED = 2; 
				VG_1_HUDUP = false;
				VG_2_HUDUP = false;
			}

			new_counter[1].id = 0;
			new_counter[2].id = 0;
			new_counter[3].id = 0;

			sprintf( new_counter[1].word, "MUSIC VOLUME");
			sprintf( new_counter[2].word, "SOUND VOLUME");

			if(VG_SELECTED == 0) // MUSIC VOLUME 
			{   
				new_counter[1].id = 2;

				sprintf( new_counter[1].word, "MUSIC VOLUME %c-%c", VG_P1_LEFT_KEY_DSY, VG_P1_RIGHT_KEY_DSY);

				if(VG_1_HUD_GO == true)
					VG_reset_input();

				if(VG_1_HUDLEFT == VG_PRESSED) 
				{
					VG_1_HUDLEFT = false;
					VG_reset_input();
					sprite[3].width -= 0.02f;
                    
					if(sprite[3].box_width != 0.0)
						music_volume = sprite[3].width / sprite[3].box_width;
                        
					if(sprite[3].width < sprite[3].box_width/25)
					{
						sprite[3].width = 0.0f;
						music_volume = 0.0f;					   
					}                            

					vg_titlemove_sfx = true; 
    
					update_title = true;      
					create_option = true;  

				}
				if(VG_1_HUDRIGHT == VG_PRESSED)
				{      
					VG_1_HUDRIGHT = false;
					VG_reset_input();
					sprite[3].width += 0.02f;
                    
					if(sprite[3].width > sprite[3].box_width)
						sprite[3].width = sprite[3].box_width;

					if(sprite[3].box_width != 0.0)
						music_volume = sprite[3].width / sprite[3].box_width;

					vg_titlemove_sfx = true;

					update_title = true;      
					create_option = true; 

				}
			} 
			if(VG_SELECTED == 1) // SOUND VOLUME
			{    
				new_counter[2].id = 2;

				sprintf( new_counter[2].word, "SOUND VOLUME %c-%c", VG_P1_LEFT_KEY_DSY, VG_P1_RIGHT_KEY_DSY);

				if(VG_1_HUD_GO == true)
					VG_reset_input();

				if(VG_1_HUDLEFT == VG_PRESSED) 
				{  
					VG_1_HUDLEFT = false;
					VG_reset_input();
					sprite[4].width -= 0.02f;
                    
					if(sprite[4].box_width != 0.0)
						sfx_volume = sprite[4].width / sprite[4].box_width;
                        
					if(sprite[4].width < sprite[4].box_width/25)
					{
						sprite[4].width = 0.0f;
						sfx_volume = 0.0f;					   
					}                            

					vg_titlemove_sfx = true;
					 
					update_title = true;        
					create_option = true;  

				}
				if(VG_1_HUDRIGHT == VG_PRESSED)
				{ 
					VG_1_HUDRIGHT = false;
					VG_reset_input();
					sprite[4].width += 0.02f;
                    
					if(sprite[4].width > sprite[4].box_width)
						sprite[4].width = sprite[4].box_width;

					if(sprite[4].box_width != 0.0)
						sfx_volume = sprite[4].width / sprite[4].box_width;

					vg_titlemove_sfx = true;

					update_title = true;      
					create_option = true; 

				} 
			}
			if(VG_SELECTED == 2) // BACK  
			{     
				new_counter[3].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				}
			}

		} // title_sequence == 1

		if(title_sequence == 2)   
		{
			if((int)TimerGetTime() > VG_Flicker_HUD_Button_timer)
			{
				VG_Flicker_HUD_Button_timer = (int)TimerGetTime() + 25;
				 
				if(VG_SELECTED == 0)
				{
					if(new_counter[1].id == 0)
						new_counter[1].id = 2;
					else
						new_counter[1].id = 0;
				} 
				if(VG_SELECTED == 1)
				{
					if(new_counter[2].id == 0)
						new_counter[2].id = 2;
					else
						new_counter[2].id = 0;
				}   
				if(VG_SELECTED == 2)
				{
					if(new_counter[3].id == 0)  
						new_counter[3].id = 2; 
					else 
						new_counter[3].id = 0;
				} 

			} 
			   
			if((int)TimerGetTime() > title_timer)
			{
				if(VG_SELECTED == 0) // SOUND OPTIONS
				{ 

				}
				if(VG_SELECTED == 1) // DISPLAY OPTIONS
				{ 

				} 
				if(VG_SELECTED == 2) // BACK
				{ 
						 
					mouseleft = false;        
					DX_SHOOT = false;   
						 
					vg_next_episode = 0;   
					vg_next_scene  = 2;

					next_scene = true;
				}


			}



		}

   }   

    // ******************************************************************************//
    //                              0-5  (DISPLAY OPTIONS)                           //
    // ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode) 
   if(next_scene == false)
   if(episode == 0 && scene == 5)        
   {       
		 
		if(title_sequence == 0) 
		{  
      //    new_sc_width = sc_width;
      //    new_sc_height = sc_height;       

		  // 1280	×	720	16:9
		  // 1366	×	768 16:9
		  // 1600	×	900	16:9
		  // 1920	×	1080	16:9

		  // 2048	×	1152	16:9 
		  // 2560	×	1440	16:9
		  // 3200	×	1800	16:9
		  // 3840	×	2160	16:9

		  // 4096	×	2304	16:9

		  RES_Width[0]  = 1280; 
		  RES_Height[0] = 720;	

		  RES_Width[1]  = 1366;
		  RES_Height[1] = 768;

		  RES_Width[2]  = 1600;
		  RES_Height[2] = 900;

		  RES_Width[3]  = 1920;
		  RES_Height[3] = 1080;

		  RES_Width[4]  = 2048;
		  RES_Height[4] = 1152;  

		  RES_Width[5]  = 2560;
		  RES_Height[5] = 1440;
 
		  RES_Width[6]  = 3200;
		  RES_Height[6] = 1800;

		  RES_Width[7]  = 3840;
		  RES_Height[7] = 2160;

		  RES_Width[8]  = 4096;
		  RES_Height[8] = 2304;

		  RES_Width[9]  = 1280;
		  RES_Height[9] = 800;	

		  RES_Width[10]  = 1440;
		  RES_Height[10] = 900;

		  RES_Width[11]  = 1680;
		  RES_Height[11] = 1050;

		  RES_Width[12]  = 1920;
		  RES_Height[12] = 1200;

		  RES_Width[13]  = 2048;
		  RES_Height[13] = 1280; 

		  RES_Width[14]  = 2560; 
		  RES_Height[14] = 1600;
 
		  RES_Width[15]  = 2880;
		  RES_Height[15] = 1800;

		  RES_Width[16]  = 3840;
		  RES_Height[16] = 2400;

		  RES_Width[17]  = 5120;
		  RES_Height[17] = 3200;


			VG_SELECTED = 0;  

			X_align = -0.17f;  
			Y_align = +0.20f;    

			sprintf( new_counter[21].word, "DISPLAY OPTIONS"); 

			new_counter[21].alpha = 1.0f;         
			new_counter[21].id = 2; 
		      
			new_counter[21].type = 0;  // Large Font...
			new_counter[21].right = false; 

			new_counter[21].x = X_align;      
			new_counter[21].y = +0.29f;  	      

			new_counter[21].w = new_counter[21].x - 0.026f;   
			new_counter[21].z = new_counter[21].y - 0.015f;

			new_counter[21].box_width = strlen(new_counter[21].word)   *  0.026f;
			new_counter[21].box_height = new_counter[21].height - 0.015f;	

			incY = 0.05f; 
              
            for(int i=0;i<18;i++)       
            { 
				if(i == 9)    
					incY = 0.05f;     
				 
				incY += 0.05f;   

				sprintf( new_counter[i].word, "");

				if(sc_width == RES_Width[i] && sc_height == RES_Height[i])
					sprintf(string_value," Ë%i x %i^", RES_Width[i], RES_Height[i]);
				else
					sprintf(string_value," %i x %i^", RES_Width[i], RES_Height[i]);

                strcat(new_counter[i].word, string_value);  
				 
				new_counter[i].alpha = 1.0f;        
				new_counter[i].id = 0; 

				new_counter[i].type = 0;  // Large Font...
				new_counter[i].right = false;

				if(i >= 9) 
					new_counter[i].x = 0.07f;                       
				else
					new_counter[i].x = -0.40f;

				new_counter[i].y = 0.33f - incY;     	      

				new_counter[i].w = new_counter[i].x - 0.026f;   
				new_counter[i].z = new_counter[i].y - 0.015f;
			     
				new_counter[i].box_width = strlen(new_counter[i].word)   *  0.026f;
				new_counter[i].box_height = new_counter[i].height - 0.015f;	

            }     
			 
			sprintf( new_counter[18].word, "     BACK"); 

			new_counter[18].alpha = 1.0f;                
			new_counter[18].id = 0;  
		      
			new_counter[18].type = 0;  // Large Font... 
			new_counter[18].right = false;

			new_counter[18].x = X_align;              
			new_counter[18].y = new_counter[17].y-0.06f;          	      

			new_counter[18].w = new_counter[18].x - 0.026f;   
			new_counter[18].z = new_counter[18].y - 0.015f;

			new_counter[18].box_width = strlen(new_counter[18].word)   *  0.026f;
			new_counter[18].box_height = new_counter[18].height - 0.015f;	


			sprintf( new_counter[20].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015-2019");
			 
			new_counter[20].alpha = 1.0f;                 
			new_counter[20].id = 3;        
				  
			new_counter[20].type = 1;  // Small Font...
			new_counter[20].right = false;

			new_counter[20].x = -0.28f;                    
			new_counter[20].y = VG_BOTTOM_OPTIONS_OFFSET;            

			new_counter[20].w = new_counter[20].x - 0.026f;   
			new_counter[20].z = new_counter[20].y - 0.015f;

			new_counter[20].box_width = strlen(new_counter[20].word)   *  0.026f;
			new_counter[20].box_height = new_counter[20].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[20].word, "%c-%c MOVE  %c: SELECT %c: BACK^&RETRO ARMY LTD. 2015-2019", VG_P1_UP_KEY_DSY, VG_P1_DOWN_KEY_DSY, VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
		else
			sprintf( new_counter[20].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015-2019");

		if(title_sequence == 1)  
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == true)
			{
				VG_reset_input();
				vg_next_episode = 0;
				vg_next_scene  = 2;

				next_scene = true;
			}
			 
			if(VG_1_HUDDOWN == VG_PRESSED)
			{
				vg_titlemove_sfx = true;
				VG_SELECTED++;
				if(VG_SELECTED > 18)    
					VG_SELECTED = 0;
				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false;
				VG_1_HUDLEFT = false;
				VG_1_HUDRIGHT = false;
			} 

			if(VG_1_HUDUP == VG_PRESSED)
			{
				vg_titlemove_sfx = true;
				VG_SELECTED--;
				if(VG_SELECTED < 0)
					VG_SELECTED = 18; 
				VG_1_HUDUP = false;
				VG_2_HUDUP = false;
				VG_1_HUDLEFT = false;
				VG_1_HUDRIGHT = false;
			}
			if(VG_1_HUDLEFT == VG_PRESSED)
			{

				if(VG_SELECTED != 18) // Back button...
				if(VG_SELECTED >= 9)    
				{
					vg_titlemove_sfx = true;
					VG_SELECTED -= 9;
				}

				VG_1_HUDDOWN = false; 
				VG_2_HUDDOWN = false;
				VG_1_HUDUP = false;
				VG_2_HUDUP = false;
				VG_1_HUDLEFT = false;
				VG_1_HUDRIGHT = false;
			} 

			if(VG_1_HUDRIGHT == VG_PRESSED)
			{ 

				if(VG_SELECTED != 18) // Back button...
				if(VG_SELECTED >= 0 && VG_SELECTED < 9)  
				{
					vg_titlemove_sfx = true;
					VG_SELECTED += 9;
				}

				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false;
				VG_1_HUDUP = false;
				VG_2_HUDUP = false;
				VG_1_HUDLEFT = false;
				VG_1_HUDRIGHT = false;
			}

			if(VG_SELECTED < 0)
				VG_SELECTED = 0;

			if(VG_SELECTED > 18)
				VG_SELECTED = 18; 

			for(int i=0;i<19;i++)   
			{ 
				  
				new_counter[i].id = 0;    
				 
				if(i != 18)
				if(RES_Available[i] == false)
					new_counter[i].id = 4;

			//	if((RES_Width[i] > MAX_horizontal || RES_Height[i] > MAX_vertical))
			//		new_counter[i].id = 4;

				if(VG_SELECTED == i) // SOUND OPTIONS
				{   

					
					if(VG_1_HUD_GO == true)
					{
						VG_reset_input();

						if(new_counter[i].id != 4)
						{
							title_sequence++;
							title_timer = (int)TimerGetTime() + 500;
							vg_titleselect_sfx = true;
						}
					}

					new_counter[i].id = 2;

				}
			}

		} // title_sequence == 1
		  
		if(title_sequence == 2)   
		{
			if((int)TimerGetTime() > VG_Flicker_HUD_Button_timer)
			{
				VG_Flicker_HUD_Button_timer = (int)TimerGetTime() + 25;
				  
				for(int i=0;i<19;i++)
				if(VG_SELECTED == i) 
				{
					if(new_counter[i].id == 0)
						new_counter[i].id = 2;
					else 
						new_counter[i].id = 0;
				} 
			} 
			   
			if((int)TimerGetTime() > title_timer)
			{

				for(int i=0;i<18;i++)      
				if(VG_SELECTED == i)
				{
				//	if(!(RES_Width[i] > MAX_horizontal || RES_Height[i] > MAX_vertical))
				//	{
						new_sc_width = RES_Width[i]; 
						new_sc_height = RES_Height[i];  

						changed_video = true; 
						create_option = true; 

						Refresh_Window(RENDERER);

				//	}  
				}

				if(VG_SELECTED == 18) // BACK
				{
						 
					mouseleft = false;        
					DX_SHOOT = false;  
						 
					vg_next_episode = 0;   
					vg_next_scene  = 2;


					next_scene = true;
				}

			}



		}

   }   

	// ******************************************************************************//
	//                                  0-6  (CREDITS)                               //
	// ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode) 
   if(next_scene == false)
   if(episode == 0 && scene == 6)        
   {       
		 
		if(title_sequence == 0) 
		{ 
			VG_SELECTED = 0;
			 
			X_align = -0.21f;    
			Y_align = +0.24f;    

			sprintf( new_counter[0].word, "GAME CREDITS"); 

			new_counter[0].alpha = 1.0f;        
			new_counter[0].id = 2; 
		      
			new_counter[0].type = 0;  // Large Font...
			new_counter[0].right = false; 

			new_counter[0].x = X_align+0.07f;      
			new_counter[0].y = +0.29f;  	      

			new_counter[0].w = new_counter[0].x - 0.026f;   
			new_counter[0].z = new_counter[0].y - 0.015f;

			new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
			new_counter[0].box_height = new_counter[0].height - 0.015f;	

			sprintf( new_counter[1].word, "       MADE BY^  PAUL STEPHEN-DAVIS"); 

			new_counter[1].alpha = 1.0f;             
			new_counter[1].id = 3;    
		      
			new_counter[1].type = 1;  // Large Font...
			new_counter[1].right = false; 

			new_counter[1].x = X_align;               
			new_counter[1].y = Y_align;    	      

			new_counter[1].w = new_counter[1].x - 0.026f;   
			new_counter[1].z = new_counter[1].y - 0.015f;
			     
			new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
			new_counter[1].box_height = new_counter[1].height - 0.015f;	

			sprintf( new_counter[2].word, "   ANNOUNCER VOICE^  ELAINE MCCULLOUGH"); 

			new_counter[2].alpha = 1.0f;            
			new_counter[2].id = 3;  
		      
			new_counter[2].type = 1;  // Large Font...
			new_counter[2].right = false;
			    
			new_counter[2].x = X_align;             
			new_counter[2].y = new_counter[1].y-0.12f;        	      

			new_counter[2].w = new_counter[2].x - 0.026f;   
			new_counter[2].z = new_counter[2].y - 0.015f;

			new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
			new_counter[2].box_height = new_counter[2].height - 0.015f;	

			sprintf( new_counter[3].word, "       MUSIC BY^      BOSSFIGHT^   TRUONG-SON NGUYEN^     LACHLAN COHEN"); 
			 
			new_counter[3].alpha = 1.0f;            
			new_counter[3].id = 3; 
		       
			new_counter[3].type = 1;  // Large Font...
			new_counter[3].right = false;
			 
			new_counter[3].x = X_align;                
			new_counter[3].y = new_counter[2].y-0.12f;       	      

			new_counter[3].w = new_counter[3].x - 0.026f;   
			new_counter[3].z = new_counter[3].y - 0.015f;

			new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
			new_counter[3].box_height = new_counter[3].height - 0.015f;	

			sprintf( new_counter[4].word, "      BACK"); 
			 
			new_counter[4].alpha = 1.0f;            
			new_counter[4].id = 0; 
		      
			new_counter[4].type = 0;  // Large Font...
			new_counter[4].right = false;

			new_counter[4].x = X_align;             
			new_counter[4].y = new_counter[3].y-0.18f;           	      

			new_counter[4].w = new_counter[4].x - 0.026f;   
			new_counter[4].z = new_counter[4].y - 0.015f;

			new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
			new_counter[4].box_height = new_counter[4].height - 0.015f;	

		/*	sprintf( new_counter[5].word, "CONTROLS"); 

			new_counter[5].alpha = 1.0f;              
			new_counter[5].id = 0; 
		      
			new_counter[5].type = 0;  // Large Font...
			new_counter[5].right = false;
			 
			new_counter[5].x = X_align;             
			new_counter[5].y = new_counter[4].y-0.06f;          	      

			new_counter[5].w = new_counter[5].x - 0.026f;   
			new_counter[5].z = new_counter[5].y - 0.015f;

			new_counter[5].box_width = strlen(new_counter[5].word)   *  0.026f;
			new_counter[5].box_height = new_counter[5].height - 0.015f;	*/



			sprintf( new_counter[7].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015-2019"); 
			 
			new_counter[7].alpha = 1.0f;                 
			new_counter[7].id = 3;        
				  
			new_counter[7].type = 1;  // Small Font...
			new_counter[7].right = false;

			new_counter[7].x = -0.28f;                    
			new_counter[7].y = VG_BOTTOM_OPTIONS_OFFSET;            

			new_counter[7].w = new_counter[7].x - 0.026f;   
			new_counter[7].z = new_counter[7].y - 0.015f;

			new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
			new_counter[7].box_height = new_counter[7].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[7].word, "%c-%c MOVE  %c: SELECT %c: BACK^&RETRO ARMY LTD. 2015-2019", VG_P1_UP_KEY_DSY, VG_P1_DOWN_KEY_DSY, VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
		else
			sprintf( new_counter[7].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015-2019");

		if(title_sequence == 1) 
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == true)
			{
				VG_reset_input();
				vg_next_episode = 0;
				vg_next_scene  = 2;

				next_scene = true;
			}

			if(VG_SELECTED == 0) // SOUND OPTIONS
			{   
				new_counter[4].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
			}


		} // title_sequence == 1

		if(title_sequence == 2)   
		{
			if((int)TimerGetTime() > VG_Flicker_HUD_Button_timer)
			{
				VG_Flicker_HUD_Button_timer = (int)TimerGetTime() + 25;

				if(VG_SELECTED == 0)
				{
					if(new_counter[4].id == 0)
						new_counter[4].id = 2;
					else
						new_counter[4].id = 0;
				} 

			}
			   
			if((int)TimerGetTime() > title_timer)
			{
				if(VG_SELECTED == 0) // BACK
				{
						 
					mouseleft = false;        
					DX_SHOOT = false;  
						 
					vg_next_episode = 0;   
					vg_next_scene  = 2;


					next_scene = true;
				}

			}



		}

   }     

    // ******************************************************************************//
    //                              0-7  (VIDEO OPTIONS)                             //
    // ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode)  
   if(next_scene == false)
   if(episode == 0 && scene == 7)        
   {       
		 
		if(title_sequence == 0) 
		{ 

			temp_fullscreen = fullscreen;
			temp_renderer = RENDERER;

		//	temp_lowres = VG_HIRES_BACKGROUNDS;

			VG_SELECTED = 0;
			 
			X_align = -0.21f;    
			Y_align = +0.20f;    

			sprintf( new_counter[0].word, "VIDEO OPTIONS"); 

			new_counter[0].alpha = 1.0f;        
			new_counter[0].id = 2; 
		      
			new_counter[0].type = 0;  // Large Font...
			new_counter[0].right = false; 

			new_counter[0].x = X_align+0.07f;      
			new_counter[0].y = +0.29f;  	      

			new_counter[0].w = new_counter[0].x - 0.026f;   
			new_counter[0].z = new_counter[0].y - 0.015f;

			new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
			new_counter[0].box_height = new_counter[0].height - 0.015f;	

			sprintf( new_counter[1].word, "SCREEN OPTIONS"); 

			new_counter[1].alpha = 1.0f;            
			new_counter[1].id = 3;    
		      
			new_counter[1].type = 0;  // Large Font...
			new_counter[1].right = false; 
			 
			new_counter[1].x = X_align;               
			new_counter[1].y = Y_align;    	      

			new_counter[1].w = new_counter[1].x - 0.026f;   
			new_counter[1].z = new_counter[1].y - 0.015f;
			     
			new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
			new_counter[1].box_height = new_counter[1].height - 0.015f;	

			sprintf( new_counter[5].word, " WINDOWED"); 

			new_counter[5].alpha = 1.0f;            
			new_counter[5].id = 0;     
		      
			new_counter[5].type = 0;  // Large Font...
			new_counter[5].right = false; 
			 
			new_counter[5].x = X_align;               
			new_counter[5].y = new_counter[1].y-0.06f;      

			new_counter[5].w = new_counter[5].x - 0.026f;   
			new_counter[5].z = new_counter[5].y - 0.015f;
			     
			new_counter[5].box_width = strlen(new_counter[5].word)   *  0.026f;
			new_counter[5].box_height = new_counter[5].height - 0.015f;	

			sprintf( new_counter[6].word, " FULLSCREEN"); 

			new_counter[6].alpha = 1.0f;            
			new_counter[6].id = 0;    
		       
			new_counter[6].type = 0;  // Large Font...
			new_counter[6].right = false; 
			 
			new_counter[6].x = 0.08f;               
			new_counter[6].y = new_counter[1].y-0.06f;      

			new_counter[6].w = new_counter[6].x - 0.026f;   
			new_counter[6].z = new_counter[6].y - 0.015f;
			     
			new_counter[6].box_width = strlen(new_counter[6].word)   *  0.026f;
			new_counter[6].box_height = new_counter[6].height - 0.015f;	

			sprintf( new_counter[2].word, "RENDERER OPTIONS"); 

			new_counter[2].alpha = 1.0f;            
			new_counter[2].id = 3;  
		      
			new_counter[2].type = 0;  // Large Font...
			new_counter[2].right = false;
			  
			new_counter[2].x = X_align;             
			new_counter[2].y = new_counter[5].y-0.06f;        	      

			new_counter[2].w = new_counter[2].x - 0.026f;   
			new_counter[2].z = new_counter[2].y - 0.015f;

			new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
			new_counter[2].box_height = new_counter[2].height - 0.015f;	

			sprintf( new_counter[7].word, " DIRECTX"); 

			new_counter[7].alpha = 1.0f;            
			new_counter[7].id = 0;    
		      
			new_counter[7].type = 0;  // Large Font...
			new_counter[7].right = false; 
			 
			new_counter[7].x = X_align;               
			new_counter[7].y = new_counter[2].y-0.06f;      

			new_counter[7].w = new_counter[7].x - 0.026f;   
			new_counter[7].z = new_counter[7].y - 0.015f;
			     
			new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
			new_counter[7].box_height = new_counter[7].height - 0.015f;	

			sprintf( new_counter[8].word, " OPENGL"); 

			new_counter[8].alpha = 1.0f;            
			new_counter[8].id = 0;    
		      
			new_counter[8].type = 0;  // Large Font...
			new_counter[8].right = false; 
			 
			new_counter[8].x = 0.08f;            
			new_counter[8].y = new_counter[2].y-0.06f;      

			new_counter[8].w = new_counter[8].x - 0.026f;   
			new_counter[8].z = new_counter[8].y - 0.015f;
			     
			new_counter[8].box_width = strlen(new_counter[8].word)   *  0.026f;
			new_counter[8].box_height = new_counter[8].height - 0.015f;	

			sprintf( new_counter[9].word, "LOW-RES BACKGROUNDS"); 

			new_counter[9].alpha = 1.0f;            
			new_counter[9].id = 3;  
		      
			new_counter[9].type = 0;  // Large Font...
			new_counter[9].right = false;
			  
			new_counter[9].x = X_align;             
			new_counter[9].y = new_counter[8].y-0.06f;        	      

			new_counter[9].w = new_counter[9].x - 0.026f;   
			new_counter[9].z = new_counter[9].y - 0.015f;

			new_counter[9].box_width = strlen(new_counter[9].word)   *  0.026f;
			new_counter[9].box_height = new_counter[9].height - 0.015f;	

			sprintf( new_counter[10].word, " ON"); 

			new_counter[10].alpha = 1.0f;            
			new_counter[10].id = 0;    
		      
			new_counter[10].type = 0;  // Large Font...
			new_counter[10].right = false; 
			 
			new_counter[10].x = X_align;               
			new_counter[10].y = new_counter[9].y-0.06f;      

			new_counter[10].w = new_counter[10].x - 0.026f;   
			new_counter[10].z = new_counter[10].y - 0.015f;
			     
			new_counter[10].box_width = strlen(new_counter[10].word)   *  0.026f;
			new_counter[10].box_height = new_counter[10].height - 0.015f;	

			sprintf( new_counter[11].word, " OFF"); 

			new_counter[11].alpha = 1.0f;            
			new_counter[11].id = 0;    
		      
			new_counter[11].type = 0;  // Large Font...
			new_counter[11].right = false; 
			 
			new_counter[11].x = 0.08f;            
			new_counter[11].y = new_counter[9].y-0.06f;      

			new_counter[11].w = new_counter[11].x - 0.026f;   
			new_counter[11].z = new_counter[11].y - 0.015f;
			     
			new_counter[11].box_width = strlen(new_counter[11].word)   *  0.026f;
			new_counter[11].box_height = new_counter[11].height - 0.015f;	





			sprintf( new_counter[3].word, "MAKE CHANGES"); 

			new_counter[3].alpha = 1.0f;            
			new_counter[3].id = 3;  
		      
			new_counter[3].type = 0;  // Large Font...
			new_counter[3].right = false;
			  
			new_counter[3].x = X_align;             
			new_counter[3].y = new_counter[11].y-0.12f;        	      

			new_counter[3].w = new_counter[3].x - 0.026f;   
			new_counter[3].z = new_counter[3].y - 0.015f;

			new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
			new_counter[3].box_height = new_counter[3].height - 0.015f;	

			sprintf( new_counter[4].word, "BACK");  
			 
			new_counter[4].alpha = 1.0f;              
			new_counter[4].id = 0; 
		      
			new_counter[4].type = 0;  // Large Font...
			new_counter[4].right = false;

			new_counter[4].x = X_align;             
			new_counter[4].y = new_counter[3].y-0.06f;           	      

			new_counter[4].w = new_counter[4].x - 0.026f;   
			new_counter[4].z = new_counter[4].y - 0.015f;

			new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
			new_counter[4].box_height = new_counter[4].height - 0.015f;	

			sprintf( new_counter[12].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015-2019"); 
			 
			new_counter[12].alpha = 1.0f;                 
			new_counter[12].id = 3;        
				  
			new_counter[12].type = 1;  // Small Font...
			new_counter[12].right = false;

			new_counter[12].x = -0.28f;                    
			new_counter[12].y = VG_BOTTOM_OPTIONS_OFFSET;            

			new_counter[12].w = new_counter[12].x - 0.026f;   
			new_counter[12].z = new_counter[12].y - 0.015f;

			new_counter[12].box_width = strlen(new_counter[12].word)   *  0.026f;
			new_counter[12].box_height = new_counter[12].height - 0.015f;	

			 title_sequence++;
		} 
			  
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[12].word, "%c-%c MOVE  %c: SELECT %c: BACK^&RETRO ARMY LTD. 2015-2019", VG_P1_UP_KEY_DSY, VG_P1_DOWN_KEY_DSY, VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
		else
			sprintf( new_counter[12].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015-2019");

		sprintf( new_counter[1].word, "SCREEN OPTIONS");
		sprintf( new_counter[2].word, "RENDERER OPTIONS");
		sprintf( new_counter[9].word, "LOW-RES BACKGROUNDS"); 

		if(temp_fullscreen == true)
		{
			sprintf( new_counter[5].word, " WINDOWED");
			sprintf( new_counter[6].word, "ËFULLSCREEN");
		}
		else
		{
			sprintf( new_counter[5].word, "ËWINDOWED");
			sprintf( new_counter[6].word, " FULLSCREEN");
		}
		if(temp_renderer == RENDER_DIRECTX)
		{
			sprintf( new_counter[7].word, "ËDIRECTX"); 
			sprintf( new_counter[8].word, " OPENGL");
		}
		if(temp_renderer == RENDER_OPENGL)
		{
			sprintf( new_counter[7].word, " DIRECTX"); 
			sprintf( new_counter[8].word, "ËOPENGL");
		}
		if(VG_HIRES_BACKGROUNDS == false)
		{
			sprintf( new_counter[10].word, "ËON");  
			sprintf( new_counter[11].word, " OFF"); 
		}
		if(VG_HIRES_BACKGROUNDS == true)
		{
			sprintf( new_counter[10].word, " ON");  
			sprintf( new_counter[11].word, "ËOFF"); 
		}

		if(title_sequence == 1) 
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == true)
			{
				VG_reset_input();
				vg_next_episode = 0;
				vg_next_scene  = 2;

				next_scene = true; 
			}

			if(VG_1_HUDDOWN == VG_PRESSED)
			{
				vg_titlemove_sfx = true;
				VG_SELECTED++;
				if(VG_SELECTED > 4)    
					VG_SELECTED = 0;
				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false;
				VG_reset_input();
			} 

			if(VG_1_HUDUP == VG_PRESSED)
			{
				vg_titlemove_sfx = true;
				VG_SELECTED--;
				if(VG_SELECTED < 0)
					VG_SELECTED = 4; 
				VG_1_HUDUP = false;
				VG_2_HUDUP = false;
				VG_reset_input();
			}

			new_counter[1].id = 0;
			new_counter[2].id = 0; 
			new_counter[3].id = 0;
			new_counter[4].id = 0;

			new_counter[9].id = 0; // Lowres

			new_counter[5].id = 4; 
			new_counter[6].id = 4;
			new_counter[7].id = 4;
			new_counter[8].id = 4;

			new_counter[10].id = 4; // ON
			new_counter[11].id = 4; // OFF

			if(VG_SELECTED == 0) // WINDOW OPTIONS
			{
				new_counter[1].id = 2; 
				 
				if(temp_fullscreen == false)
					new_counter[5].id = 3; // Windowed...
				if(temp_fullscreen == true)
					new_counter[6].id = 3; // Fullscreen..

				sprintf( new_counter[1].word, "SCREEN OPTIONS %c-%c", VG_P1_LEFT_KEY_DSY, VG_P1_RIGHT_KEY_DSY); 

				if(VG_1_HUD_GO == true)
					VG_reset_input();

				if(VG_1_HUDRIGHT == VG_PRESSED)
				{
					VG_reset_input();
					if(temp_fullscreen == false)
					{
						temp_fullscreen = true;
						vg_titlemove_sfx = true;
					}
					VG_1_HUDRIGHT = false;
				}

				if(VG_1_HUDLEFT == VG_PRESSED)
				{
					VG_reset_input();
					if(temp_fullscreen == true)
					{
						temp_fullscreen = false;
						vg_titlemove_sfx = true;
					}
					VG_1_HUDLEFT = false;
				}
			} 
			if(VG_SELECTED == 1) // RENDERER OPTIONS
			{
				new_counter[2].id = 2;

				if(temp_renderer == RENDER_DIRECTX)
					new_counter[7].id = 3; // DirectX...
				if(temp_renderer == RENDER_OPENGL)
					new_counter[8].id = 3; // OpenGl...

				sprintf( new_counter[2].word, "RENDERER OPTIONS %c-%c", VG_P1_LEFT_KEY_DSY, VG_P1_RIGHT_KEY_DSY);

				if(VG_1_HUD_GO == true)
					VG_reset_input();

				if(VG_1_HUDRIGHT == VG_PRESSED)
				{
					VG_reset_input();
					if(temp_renderer == RENDER_DIRECTX)
					{
						temp_renderer = RENDER_OPENGL;
						vg_titlemove_sfx = true;
					}
					VG_1_HUDRIGHT = false;
				}

				if(VG_1_HUDLEFT == VG_PRESSED)
				{
					VG_reset_input();
					if(temp_renderer == RENDER_OPENGL)
					{
						temp_renderer = RENDER_DIRECTX;
						vg_titlemove_sfx = true;
					}
					VG_1_HUDLEFT = false;
				}
			}   
			if(VG_SELECTED == 2) // LOW-RES
			{
				new_counter[9].id = 2;

				if(VG_HIRES_BACKGROUNDS == false)
					new_counter[10].id = 3; // ON
				if(VG_HIRES_BACKGROUNDS == true)
					new_counter[11].id = 3; // OFF

				sprintf( new_counter[9].word, "LOW-RES BACKGROUNDS %c-%c", VG_P1_LEFT_KEY_DSY, VG_P1_RIGHT_KEY_DSY); 

				if(VG_1_HUD_GO == true)
					VG_reset_input();

				if(VG_1_HUDRIGHT == VG_PRESSED)
				{
					VG_reset_input();
					if(VG_HIRES_BACKGROUNDS == false)
					{
						VG_HIRES_BACKGROUNDS = true;
						vg_titlemove_sfx = true;
					}
					VG_1_HUDRIGHT = false;
				}

				if(VG_1_HUDLEFT == VG_PRESSED)
				{
					VG_reset_input();
					if(VG_HIRES_BACKGROUNDS == true)
					{
						VG_HIRES_BACKGROUNDS = false;
						vg_titlemove_sfx = true;
					}
					VG_1_HUDLEFT = false;
				}
			}   
			if(VG_SELECTED == 3) // MAKE CHANGES
			{   
				new_counter[3].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
			}
			if(VG_SELECTED == 4) // BACK
			{   
				new_counter[4].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
			}

		} // title_sequence == 1 

		if(title_sequence == 2)    
		{ 
			if((int)TimerGetTime() > VG_Flicker_HUD_Button_timer) 
			{
				VG_Flicker_HUD_Button_timer = (int)TimerGetTime() + 25; 

				if(VG_SELECTED == 0) // WINDOWED
				{
					if(new_counter[1].id == 0) 
						new_counter[1].id = 2;
					else
						new_counter[1].id = 0;
				} 

				if(VG_SELECTED == 1) // FULLSCREEN
				{
					if(new_counter[2].id == 0) 
						new_counter[2].id = 2;
					else
						new_counter[2].id = 0;
				} 
				if(VG_SELECTED == 2) // LOW-RES
				{
					if(new_counter[9].id == 0) 
						new_counter[9].id = 2;
					else
						new_counter[9].id = 0;
				} 
				if(VG_SELECTED == 3) // MAKE CHANGES
				{
					if(new_counter[3].id == 0) 
						new_counter[3].id = 2;
					else
						new_counter[3].id = 0;
				} 
				if(VG_SELECTED == 4) // BACK
				{
					if(new_counter[4].id == 0) 
						new_counter[4].id = 2;
					else
						new_counter[4].id = 0;
				} 

			}
			   
			if((int)TimerGetTime() > title_timer) 
			{

				if(VG_SELECTED == 0) // WINDOWED
				{					  
					mouseleft = false;               
					DX_SHOOT = false;   
				}
				if(VG_SELECTED == 1) // FULLSCREEN
				{					  
					mouseleft = false;                
					DX_SHOOT = false;    
				}
				if(VG_SELECTED == 2) // LOW-RES
				{					  
					mouseleft = false;                
					DX_SHOOT = false;    
				}
				if(VG_SELECTED == 3) // MAKE CHANGES
				{
					mouseleft = false;                
					DX_SHOOT = false;    
					      
                    fullscreen = temp_fullscreen;

                    vg_stamp_sfx = true;
                    changed_video = true;
                    create_option = true;        

					Refresh_Window(temp_renderer);
				}
				if(VG_SELECTED == 4) // BACK
				{
						 
					mouseleft = false;         
					DX_SHOOT = false;  
						 
					vg_next_episode = 0;   
					vg_next_scene  = 2;
					
					next_scene = true;
				}

			}



		}

   }   

	// ******************************************************************************//
	//                                 0-8  (CONTROLS)                               //
	// ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode) 
   if(next_scene == false)
   if(episode == 0 && scene == 8)        
   {        
		 
		if(title_sequence == 0) 
		{ 
			VG_SELECTED = 0;
			 
			X_align = -0.26f;      
			Y_align = +0.20f;    

			sprintf( new_counter[0].word, "   CONTROLS"); 

			new_counter[0].alpha = 1.0f;        
			new_counter[0].id = 2; 
		      
			new_counter[0].type = 0;  // Large Font...
			new_counter[0].right = false; 

			new_counter[0].x = -0.18f;   
			new_counter[0].y = +0.29f;  	      

			new_counter[0].w = new_counter[0].x - 0.026f;   
			new_counter[0].z = new_counter[0].y - 0.015f;

			new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
			new_counter[0].box_height = new_counter[0].height - 0.015f;	

			up = VG_P1_UP_KEY_DSY;
			down = VG_P1_DOWN_KEY_DSY;
			left = VG_P1_LEFT_KEY_DSY;
			right = VG_P1_RIGHT_KEY_DSY;

			punch  = VG_P1_PUNCH1_KEY_DSY;
			punch2 = VG_P1_PUNCH2_KEY_DSY;
			kick   = VG_P1_KICK1_KEY_DSY;
			kick2  = VG_P1_KICK2_KEY_DSY;

			block = VG_P1_BLOCK_KEY_DSY;
			throw_key = VG_P1_THROW_KEY_DSY;

			sprintf( new_counter[1].word, "P1^¦-§-¢-¤^ %c  %c  %c  %c^^", up, down, left, right); 
			 
			new_counter[1].alpha = 1.0f;             
			new_counter[1].id = 3;    
		       
			new_counter[1].type = 1;  // Large Font...
			new_counter[1].right = false;  

			new_counter[1].x = X_align;               
			new_counter[1].y = Y_align;    	      

			new_counter[1].w = new_counter[1].x - 0.026f;   
			new_counter[1].z = new_counter[1].y - 0.015f;
			     
			new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
			new_counter[1].box_height = new_counter[1].height - 0.015f;	

			//sprintf( new_counter[2].word, "£^'Z'^¥^'X'^À^'C'^Á^'V'"); 
			sprintf( new_counter[2].word, "^£  ¥  À  Á  ¼  ½"); 

			new_counter[2].alpha = 1.0f;             
			new_counter[2].id = 3;  
		        
			new_counter[2].type = 1;  // Large Font... 
			new_counter[2].right = false; 
			   
			new_counter[2].x = X_align-0.08f;             
			new_counter[2].y = new_counter[1].y-0.12f;         	      
			 
			new_counter[2].w = new_counter[2].x - 0.026f;   
			new_counter[2].z = new_counter[2].y - 0.015f;

			new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
			new_counter[2].box_height = new_counter[2].height - 0.015f;	
			 
			sprintf( new_counter[3].word, "^ %c  %c  %c  %c  %c  %c^ ÷  ø  ù  ú  ¾  »", punch, punch2, kick, kick2, block, throw_key); 

			new_counter[3].alpha = 1.0f;             
			new_counter[3].id = 3;  
		      
			new_counter[3].type = 1;  // Large Font... 
			new_counter[3].right = false; 
			   
			new_counter[3].x = X_align-0.08f;              
			new_counter[3].y = new_counter[2].y-0.04f;        	      
			 
			new_counter[3].w = new_counter[3].x - 0.026f;   
			new_counter[3].z = new_counter[3].y - 0.015f;

			new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
			new_counter[3].box_height = new_counter[3].height - 0.015f;	

			sprintf( new_counter[4].word, "       BACK"); 
			 
			new_counter[4].alpha = 1.0f;            
			new_counter[4].id = 0; 
		       
			new_counter[4].type = 0;  // Large Font...
			new_counter[4].right = false;

			new_counter[4].x = -0.24f;             
			new_counter[4].y = new_counter[2].y-0.36f;           	      

			new_counter[4].w = new_counter[4].x - 0.026f;   
			new_counter[4].z = new_counter[4].y - 0.015f;

			new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
			new_counter[4].box_height = new_counter[4].height - 0.015f;	

			up = VG_P2_UP_KEY_DSY;
			down = VG_P2_DOWN_KEY_DSY;
			left = VG_P2_LEFT_KEY_DSY;
			right = VG_P2_RIGHT_KEY_DSY;
			punch  = VG_P2_PUNCH1_KEY_DSY;
			punch2 = VG_P2_PUNCH2_KEY_DSY;
			kick   = VG_P2_KICK1_KEY_DSY; 
			kick2  = VG_P2_KICK2_KEY_DSY;

			block = VG_P2_BLOCK_KEY_DSY;
			throw_key = VG_P2_THROW_KEY_DSY;

			sprintf( new_counter[5].word, "P2^¦-§-¢-¤^ %c  %c  %c  %c^^", up, down, left, right); 
			 
			new_counter[5].alpha = 1.0f;             
			new_counter[5].id = 3;    
		      
			new_counter[5].type = 1;  // Large Font...
			new_counter[5].right = false;  

			new_counter[5].x = X_align+0.4f;               
			new_counter[5].y = Y_align;    	       

			new_counter[5].w = new_counter[5].x - 0.026f;   
			new_counter[5].z = new_counter[5].y - 0.015f;
			     
			new_counter[5].box_width = strlen(new_counter[5].word)   *  0.026f;
			new_counter[5].box_height = new_counter[5].height - 0.015f;	

			//sprintf( new_counter[2].word, "£^'Z'^¥^'X'^À^'C'^Á^'V'"); 
			sprintf( new_counter[6].word, "^£  ¥  À  Á  ¼  ½"); 

			new_counter[6].alpha = 1.0f;             
			new_counter[6].id = 3;  
		       
			new_counter[6].type = 1;  // Large Font... 
			new_counter[6].right = false; 
			   
			new_counter[6].x = X_align+0.4f;              
			new_counter[6].y = new_counter[5].y-0.12f;         	      
			 
			new_counter[6].w = new_counter[6].x - 0.026f;   
			new_counter[6].z = new_counter[6].y - 0.015f;

			new_counter[6].box_width = strlen(new_counter[6].word)   *  0.026f;
			new_counter[6].box_height = new_counter[6].height - 0.015f;	
			 
			sprintf( new_counter[7].word, "^ %c  %c  %c  %c  %c  %c^ ÷  ø  ù  ú  ¾  »", punch, punch2, kick, kick2, block, throw_key);

			new_counter[7].alpha = 1.0f;              
			new_counter[7].id = 3;    
		      
			new_counter[7].type = 1;  // Large Font... 
			new_counter[7].right = false;
			  
			new_counter[7].x = X_align+0.4f;            
			new_counter[7].y = new_counter[6].y-0.04f;        	      
			 
			new_counter[7].w = new_counter[7].x - 0.026f;   
			new_counter[7].z = new_counter[7].y - 0.015f;

			new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
			new_counter[7].box_height = new_counter[7].height - 0.015f;	

			sprintf( new_counter[9].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015-2019"); 
			 
			new_counter[9].alpha = 1.0f;                 
			new_counter[9].id = 3;        
				  
			new_counter[9].type = 1;  // Small Font...
			new_counter[9].right = false;
			 
			new_counter[9].x = -0.28f;                    
			new_counter[9].y = VG_BOTTOM_OPTIONS_OFFSET;            

			new_counter[9].w = new_counter[9].x - 0.026f;   
			new_counter[9].z = new_counter[9].y - 0.015f;

			new_counter[9].box_width = strlen(new_counter[9].word)   *  0.026f;
			new_counter[9].box_height = new_counter[9].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[9].word, "%c-%c MOVE  %c: SELECT %c: BACK^&RETRO ARMY LTD. 2015-2019", VG_P1_UP_KEY_DSY, VG_P1_DOWN_KEY_DSY, VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
		else
			sprintf( new_counter[9].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015-2019");

		if(title_sequence == 1) 
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == true)
			{
				VG_reset_input();
				vg_next_episode = 0;
				vg_next_scene  = 14;

				next_scene = true;
			}

			if(VG_SELECTED == 0) // SOUND OPTIONS
			{   
				new_counter[4].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
			}


		} // title_sequence == 1

		if(title_sequence == 2)   
		{
			if((int)TimerGetTime() > VG_Flicker_HUD_Button_timer)
			{
				VG_Flicker_HUD_Button_timer = (int)TimerGetTime() + 25;

				if(VG_SELECTED == 0)
				{
					if(new_counter[4].id == 0)
						new_counter[4].id = 2;
					else
						new_counter[4].id = 0;
				} 

			}
			   
			if((int)TimerGetTime() > title_timer)
			{
				if(VG_SELECTED == 0) // BACK
				{
						 
					mouseleft = false;        
					DX_SHOOT = false;  

						 
					vg_next_episode = 0;   
					vg_next_scene  = 14;


					next_scene = true;
				}

			}



		}

   }     

    // ******************************************************************************//
    //                            0-9  (CHARACTER SHEET)                             //
    // ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode) 
   if(next_scene == false)
   if(episode == 0 && scene == 9)        
   {       
	    
	   if((int)TimerGetTime() > GRID_TIMER)
	   {
		   GRID_TIMER = (int)TimerGetTime() + 3000;

		   GRID_LEFT_RIGHT = rand()%2; 
		   GRID_UP_DOWN = rand()%2;
	   }

	    // Scroll sheet box grid...
	    if(GRID_LEFT_RIGHT == 0)
		{
			sprite[4].u[0] += VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].u[1] += VG_SHEET_SCROLL_SPEED * (float)f_rate; 
			sprite[4].u[2] += VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].u[3] += VG_SHEET_SCROLL_SPEED * (float)f_rate;
		}
		else
		{
			sprite[4].u[0] -= VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].u[1] -= VG_SHEET_SCROLL_SPEED * (float)f_rate; 
			sprite[4].u[2] -= VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].u[3] -= VG_SHEET_SCROLL_SPEED * (float)f_rate;
		}
	    if(GRID_UP_DOWN == 0)
		{
			sprite[4].v[0] -= VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].v[1] -= VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].v[2] -= VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].v[3] -= VG_SHEET_SCROLL_SPEED * (float)f_rate;
		}
		else
		{
			sprite[4].v[0] += VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].v[1] += VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].v[2] += VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].v[3] += VG_SHEET_SCROLL_SPEED * (float)f_rate;
		}



		if(VG_P1_USING == VG_KEYBOARD)
		{
			up = VG_P1_UP_KEY_DSY;
			down = VG_P1_DOWN_KEY_DSY;
			left = VG_P1_LEFT_KEY_DSY;
			right = VG_P1_RIGHT_KEY_DSY;
			punch  = VG_P1_PUNCH1_KEY_DSY;
			punch2 = VG_P1_PUNCH2_KEY_DSY;
			kick   = VG_P1_KICK1_KEY_DSY;
			kick2  = VG_P1_KICK2_KEY_DSY;
		}
		if(VG_P1_USING == VG_CONTROLLER)
		{
			punch  = '÷';
			punch2 = 'ø';
			kick   = 'ù';
			kick2  = 'ú'; 
		}

		if(VG_P1_USING == VG_KEYBOARD)  
		{ 
			if(VG_1_CHARACTER == VG_GYEONG)  
				sprintf( new_counter[1].word, "AGE: 28^JOB: DETECTIVE^LIKES: SOJU^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_SIU)
				sprintf( new_counter[1].word, "AGE: 22^JOB: SUBWAY COP^LIKES: TRAINS^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_MINSO)
				sprintf( new_counter[1].word, "AGE: 26^JOB: TRAFFIC COP^LIKES: KIMCHI^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_REESE)
				sprintf( new_counter[1].word, "AGE: ??^JOB: SECRET AGENT^LIKES: ALIENS^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_YOHAN)
				sprintf( new_counter[1].word, "AGE: 17^JOB: TERRORIST^LIKES: BOMBS^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_JAE)
				sprintf( new_counter[1].word, "AGE: 32^JOB: YAKUZA^LIKES: DANCING^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_GUN)
				sprintf( new_counter[1].word, "AGE: 46^JOB: CONVICT^LIKES: MAHJONG^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_HYUK)
				sprintf( new_counter[1].word, "AGE: 22^JOB: BANK ROBBER^LIKES: MONEY^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if (VG_1_CHARACTER == VG_SHO)
				sprintf(new_counter[1].word, "AGE: 22^JOB: KARATE EXPERT^LIKES: STRENGTH^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2);
			if (VG_1_CHARACTER == VG_TIA)
				sprintf(new_counter[1].word, "AGE: 19^JOB: KICKBOXER^LIKES: HER BROTHER^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2);
			if (VG_1_CHARACTER == VG_SAIZO)
				sprintf(new_counter[1].word, "AGE: 28^JOB: NINJA^LIKES: ANIMALS^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2);
			if (VG_1_CHARACTER == VG_SANG)
				sprintf(new_counter[1].word, "AGE: 42^JOB: POLITICIAN^LIKES: CRIME^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2);
			if(VG_1_CHARACTER == VG_KENNEDY)
				sprintf( new_counter[1].word, "AGE: 42^JOB: WRESTLER^LIKES: ATHLETICS^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 

			if(VG_1_CHARACTER == VG_GYEONG && VG_IS_AN_ALTER_P1 == true)  
				sprintf( new_counter[1].word, "AGE: 26^JOB: DETECTIVE^LIKES: KARAOKE^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_SIU && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 43^JOB: SUBWAY COP^LIKES: PIGEONS^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_MINSO && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 26^JOB: TRAFFIC COP^LIKES: BOWLING^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_REESE && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: ??^JOB: SECRET AGENT^LIKES: WHISKEY^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_YOHAN && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 52^JOB: TERRORIST^LIKES: RELIGION^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_JAE && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 34^JOB: YAKUZA^LIKES: GUNS^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_GUN && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 28^JOB: CONVICT^LIKES: CHESS^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_HYUK && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 19^JOB: BANK ROBBER^LIKES: DRIVING^^¦-§-¢-¤^ %c  %c  %c  %c^£  ¥  À  Á^ %c  %c  %c  %c", up, down, left, right, punch, punch2, kick, kick2); 
	
		}
		else   
		{
#ifdef SWITCH
			if(VG_1_CHARACTER == VG_GYEONG)  
				sprintf( new_counter[1].word, "AGE: 28^JOB: DETECTIVE^LIKES: SOJU^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_SIU)
				sprintf( new_counter[1].word, "AGE: 22^JOB: SUBWAY COP^LIKES: TRAINS^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_MINSO)
				sprintf( new_counter[1].word, "AGE: 26^JOB: TRAFFIC COP^LIKES: KIMCHI^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_REESE)
				sprintf( new_counter[1].word, "AGE: ??^JOB: SECRET AGENT^LIKES: ALIENS^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_YOHAN)
				sprintf( new_counter[1].word, "AGE: 17^JOB: TERRORIST^LIKES: BOMBS^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_JAE)
				sprintf( new_counter[1].word, "AGE: 32^JOB: YAKUZA^LIKES: DANCING^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_GUN)
				sprintf( new_counter[1].word, "AGE: 46^JOB: CONVICT^LIKES: MAHJONG^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_HYUK)
				sprintf( new_counter[1].word, "AGE: 22^JOB: BANK ROBBER^LIKES: MONEY^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if (VG_1_CHARACTER == VG_SHO)
				sprintf(new_counter[1].word, "AGE: 22^JOB: SUBWAY COP^LIKES: TRAINS^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2);
			if (VG_1_CHARACTER == VG_TIA)
				sprintf(new_counter[1].word, "AGE: 19^JOB: KICKBOXER^LIKES: HER BROTHER^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2);
			if (VG_1_CHARACTER == VG_SAIZO)
				sprintf(new_counter[1].word, "AGE: 28^JOB: NINJA^LIKES: ANIMALS^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2);
			if (VG_1_CHARACTER == VG_SANG)
				sprintf(new_counter[1].word, "AGE: 42^JOB: POLITICIAN^LIKES: CRIME^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2);
			if(VG_1_CHARACTER == VG_KENNEDY)
				sprintf( new_counter[1].word, "AGE: 42^JOB: WRESTLER^LIKES: ATHLETICS^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
					
			if(VG_1_CHARACTER == VG_GYEONG && VG_IS_AN_ALTER_P1 == true)  
				sprintf( new_counter[1].word, "AGE: 26^JOB: DETECTIVE^LIKES: KARAOKE^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_SIU && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 43^JOB: SUBWAY COP^LIKES: PIGEONS^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_MINSO && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 26^JOB: TRAFFIC COP^LIKES: BOWLING^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_REESE && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: ??^JOB: SECRET AGENT^LIKES: WHISKEY^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_YOHAN && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 52^JOB: TERRORIST^LIKES: RELIGION^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_JAE && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 34^JOB: YAKUZA^LIKES: GUNS^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_GUN && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 28^JOB: CONVICT^LIKES: CHESS^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_HYUK && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 19^JOB: BANK ROBBER^LIKES: DRIVING^^¦-§-¢-¤^+Control Pad^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
#elif defined PS4 || defined XB1 || defined DREAMCAST
			if(VG_1_CHARACTER == VG_GYEONG)  
				sprintf( new_counter[1].word, "AGE: 28^JOB: DETECTIVE^LIKES: SOJU^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_SIU)
				sprintf( new_counter[1].word, "AGE: 22^JOB: SUBWAY COP^LIKES: TRAINS^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_MINSO)
				sprintf( new_counter[1].word, "AGE: 26^JOB: TRAFFIC COP^LIKES: KIMCHI^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_REESE)
				sprintf( new_counter[1].word, "AGE: ??^JOB: SECRET AGENT^LIKES: ALIENS^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_YOHAN)
				sprintf( new_counter[1].word, "AGE: 17^JOB: TERRORIST^LIKES: BOMBS^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_JAE)
				sprintf( new_counter[1].word, "AGE: 32^JOB: YAKUZA^LIKES: DANCING^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_GUN)
				sprintf( new_counter[1].word, "AGE: 46^JOB: CONVICT^LIKES: MAHJONG^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_HYUK)
				sprintf( new_counter[1].word, "AGE: 22^JOB: BANK ROBBER^LIKES: MONEY^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if (VG_1_CHARACTER == VG_SHO)
				sprintf(new_counter[1].word, "AGE: 22^JOB: SUBWAY COP^LIKES: TRAINS^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2);
			if (VG_1_CHARACTER == VG_TIA)
				sprintf(new_counter[1].word, "AGE: 19^JOB: KICKBOXER^LIKES: HER BROTHER^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2);
			if (VG_1_CHARACTER == VG_SAIZO)
				sprintf(new_counter[1].word, "AGE: 28^JOB: NINJA^LIKES: ANIMALS^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2);
			if (VG_1_CHARACTER == VG_SANG)
				sprintf(new_counter[1].word, "AGE: 42^JOB: POLITICIAN^LIKES: CRIME^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2);
			if(VG_1_CHARACTER == VG_KENNEDY)
				sprintf( new_counter[1].word, "AGE: 42^JOB: WRESTLER^LIKES: ATHLETICS^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
					
			if(VG_1_CHARACTER == VG_GYEONG && VG_IS_AN_ALTER_P1 == true)  
				sprintf( new_counter[1].word, "AGE: 26^JOB: DETECTIVE^LIKES: KARAOKE^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_SIU && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 43^JOB: SUBWAY COP^LIKES: PIGEONS^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_MINSO && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 26^JOB: TRAFFIC COP^LIKES: BOWLING^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_REESE && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: ??^JOB: SECRET AGENT^LIKES: WHISKEY^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_YOHAN && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 52^JOB: TERRORIST^LIKES: RELIGION^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_JAE && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 34^JOB: YAKUZA^LIKES: GUNS^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_GUN && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 28^JOB: CONVICT^LIKES: CHESS^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_HYUK && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[1].word, "AGE: 19^JOB: BANK ROBBER^LIKES: DRIVING^^¦-§-¢-¤^LEFT STICK^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
#endif

		}

		VG_Moveslist(2, VG_1_CHARACTER, 0, 1);
		VG_Moveslist(3, VG_1_CHARACTER, 1, 1);
		VG_Moveslist(4, VG_1_CHARACTER, 2, 1);

		if(title_sequence == 0) 
		{ 
			GRID_TIMER = (int)TimerGetTime() + 3000;

			VG_arcade_sequence = 0;

			VG_SHEET_ANIM = 0;

			VG_SELECTED = 0;

			X_align = 0.05f;     
			Y_align = +0.24f;    

			if(VG_1_CHARACTER == VG_GYEONG)
				sprintf( new_counter[0].word, "GYEONG^");   
			if(VG_1_CHARACTER == VG_SIU)
				sprintf( new_counter[0].word, "  SI$U^");   
			if(VG_1_CHARACTER == VG_MINSO)
				sprintf( new_counter[0].word, " MINSO^");   
			if(VG_1_CHARACTER == VG_REESE)
				sprintf( new_counter[0].word, " REESE^");   
			if(VG_1_CHARACTER == VG_YOHAN)
				sprintf( new_counter[0].word, " YOHAN^");   
			if(VG_1_CHARACTER == VG_JAE)
				sprintf( new_counter[0].word, "  JAE^");   
			if(VG_1_CHARACTER == VG_GUN)
				sprintf( new_counter[0].word, "  GUN^");   
			if(VG_1_CHARACTER == VG_HYUK)
				sprintf( new_counter[0].word, "  HYUK^");  
			if (VG_1_CHARACTER == VG_SHO)
				sprintf(new_counter[0].word, "  SHO^"); 
			if (VG_1_CHARACTER == VG_TIA)
				sprintf(new_counter[0].word, "  TIA^");
			if (VG_1_CHARACTER == VG_SAIZO)
				sprintf(new_counter[0].word, " SAIZO^");   
			if(VG_1_CHARACTER == VG_SANG)
				sprintf( new_counter[0].word, "  SANG^");  
			if(VG_1_CHARACTER == VG_KENNEDY)
				sprintf( new_counter[0].word, "KEN ANDERSON^");  


			if(VG_1_CHARACTER == VG_GYEONG && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, "TOYUN^");   
			if(VG_1_CHARACTER == VG_SIU && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, "DAE-SU^");   
			if(VG_1_CHARACTER == VG_MINSO && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, "   MIA^");   
			if(VG_1_CHARACTER == VG_REESE && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, "   BOB^");   
			if(VG_1_CHARACTER == VG_YOHAN && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, "SUNG-KI^");   
			if(VG_1_CHARACTER == VG_JAE && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, "SAPPORO^");   
			if(VG_1_CHARACTER == VG_GUN && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, "  KONU^");   
			if(VG_1_CHARACTER == VG_HYUK && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, " YE-JUN^"); 

			new_counter[0].alpha = 1.0f;         
			new_counter[0].id = 2;  
		      
			new_counter[0].type = 0;  // Large Font...
			new_counter[0].right = false; 
			 
			new_counter[0].x = -0.05f;   
			new_counter[0].y = +0.32f;  	        

			new_counter[0].w = new_counter[0].x - 0.026f;   
			new_counter[0].z = new_counter[0].y - 0.015f;

			new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
			new_counter[0].box_height = new_counter[0].height - 0.015f;	

			scroll_index = 0;
			scroll_length = strlen(new_counter[1].word);
			scroll_txt_active = true; 
			new_counter[1].scroll_this = true;


			new_counter[1].alpha = 1.0f;            
			new_counter[1].id = 3;     
		       
			new_counter[1].type = 1;  // Large Font...  
			new_counter[1].right = false;   

			new_counter[1].x = 0.10f;             
			new_counter[1].y = Y_align;    	       

			new_counter[1].w = new_counter[1].x - 0.026f;   
			new_counter[1].z = new_counter[1].y - 0.015f;
			     
			new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
			new_counter[1].box_height = new_counter[1].height - 0.015f;	

			VG_Moveslist(2, VG_1_CHARACTER, 0, 1);

			new_counter[2].alpha = 1.0f;            
			new_counter[2].id = 3;   
		       
			new_counter[2].type = 1;  // Large Font...  
			new_counter[2].right = false;   
			 
			if (screen_mode == SCREEN_NORMAL) // 4:3
				new_counter[2].x = -0.45f;              
			else
				new_counter[2].x = -0.57f;

			new_counter[2].y = -0.24f;     

			new_counter[2].w = new_counter[2].x - 0.026f;   
			new_counter[2].z = new_counter[2].y - 0.015f;
			     
			new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
			new_counter[2].box_height = new_counter[2].height - 0.015f;	
			 
			VG_Moveslist(3, VG_1_CHARACTER, 1, 1);

			new_counter[3].alpha = 1.0f;            
			new_counter[3].id = 3;   
		       
			new_counter[3].type = 1;  // Large Font...  
			new_counter[3].right = false;    

			if (screen_mode == SCREEN_NORMAL) // 4:3
				new_counter[3].x = -0.13f;                    
			else
				new_counter[3].x = -0.13f;

			new_counter[3].y = -0.24f;     

			new_counter[3].w = new_counter[3].x - 0.026f;   
			new_counter[3].z = new_counter[3].y - 0.015f;
			     
			new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
			new_counter[3].box_height = new_counter[3].height - 0.015f;	

			VG_Moveslist(4, VG_1_CHARACTER, 2, 1);
			 
			new_counter[4].alpha = 1.0f;              
			new_counter[4].id = 3;   
		        
			new_counter[4].type = 1;  // Large Font...  
			new_counter[4].right = false;   
			 
			if (screen_mode == SCREEN_NORMAL) // 4:3
				new_counter[4].x = 0.23f;                  
			else
				new_counter[4].x = 0.30f;

			new_counter[4].y = -0.24f;      

			new_counter[4].w = new_counter[4].x - 0.026f;   
			new_counter[4].z = new_counter[4].y - 0.015f; 
			     
			new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
			new_counter[4].box_height = new_counter[4].height - 0.015f;	

			if(TURN_OFF_INGAME_HELP == 0) 
			{
				sprintf( new_counter[7].word, "^     Z: NEXT ESC: BACK^"); 
			  
				new_counter[7].alpha = 1.0f;                     
				new_counter[7].id = 3;        
				  
				new_counter[7].type = 1;  // Small Font...
				new_counter[7].right = false;

				new_counter[7].x = -0.26f;                    
				new_counter[7].y = VG_BOTTOM_OPTIONS_OFFSET;            

				new_counter[7].w = new_counter[7].x - 0.026f;   
				new_counter[7].z = new_counter[7].y - 0.015f;

				new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
				new_counter[7].box_height = new_counter[7].height - 0.015f;	
			}
			title_timer = (int)TimerGetTime() + 12000;
			title_sequence++; 
		} // title_sequence == 0
  
 		if((int)TimerGetTime() > flash_helptext_timer) 
		{
			if(new_counter[7].alpha == 0.0f)
			{
				flash_helptext_timer = (int)TimerGetTime() + 500;
				new_counter[7].alpha = 1.0f;
			}
			else
			{
				flash_helptext_timer = (int)TimerGetTime() + 500;
				new_counter[7].alpha = 0.0f;
			}
		}

		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[7].word, "^     %c: NEXT %c: BACK^", VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY); 
		else
			sprintf( new_counter[7].word, "^     ÷: NEXT ø: BACK^");

		if(title_sequence == 1)    
		{ 
			// Pressed back key...
			if(VG_1_HUD_BACK == true) 
			{ 
				VG_reset_input();

			    VG_1_WINS = 0;  
			    VG_2_WINS = 0; 

			    VG_ROUND = 1;

				vg_selected_character = false;

				vg_next_episode = 6;
				vg_next_scene  = 1;  
				  
				next_scene = true; 
			}
			if(VG_1_HUD_GO == true
			) // Go to map screen...   // || (int)TimerGetTime() > title_timer
			{ 
				VG_reset_input(); 

				mouseleft = false;        
				DX_SHOOT = false;  

				if(VG_TRAINING == true)
				{
					VG_IS_VERSUS_SCREEN = true; 
      
					VG_2_CHARACTER = VG_TRAINER;    
						  
					VG_BACKGROUND = VG_TRAINER; 

					vg_next_episode = 0;         
					vg_next_scene  = 10;
				}
				else 
				{
					if(VG_GAME_MODE == VG_STORY_MODE)
					{
						vg_next_episode = 6;        
						vg_next_scene  = 1; 

						VG_Init_Story(VG_1_CHARACTER);
					}
					else
					{
						vg_next_episode = 0;        
						vg_next_scene  = 10; 
					}
				}


				next_scene = true;

			}

		} // title_sequence == 1 


   }   // scene == 9

    // ******************************************************************************//
    //                            0-10  (THROWS SHEET)                               //
    // ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode) 
   if(next_scene == false)
   if(episode == 0 && scene == 10)        
   {   

	   if((int)TimerGetTime() > GRID_TIMER)
	   {
		   GRID_TIMER = (int)TimerGetTime() + 3000;

		   GRID_LEFT_RIGHT = rand()%2; 
		   GRID_UP_DOWN = rand()%2;
	   }

	    // Scroll sheet box grid...
	    if(GRID_LEFT_RIGHT == 0)
		{
			sprite[4].u[0] += VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].u[1] += VG_SHEET_SCROLL_SPEED * (float)f_rate; 
			sprite[4].u[2] += VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].u[3] += VG_SHEET_SCROLL_SPEED * (float)f_rate;
		}
		else
		{
			sprite[4].u[0] -= VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].u[1] -= VG_SHEET_SCROLL_SPEED * (float)f_rate; 
			sprite[4].u[2] -= VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].u[3] -= VG_SHEET_SCROLL_SPEED * (float)f_rate;
		}
	    if(GRID_UP_DOWN == 0)
		{
			sprite[4].v[0] -= VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].v[1] -= VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].v[2] -= VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].v[3] -= VG_SHEET_SCROLL_SPEED * (float)f_rate;
		}
		else
		{
			sprite[4].v[0] += VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].v[1] += VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].v[2] += VG_SHEET_SCROLL_SPEED * (float)f_rate;
			sprite[4].v[3] += VG_SHEET_SCROLL_SPEED * (float)f_rate;
		}

		if(VG_P1_USING == VG_KEYBOARD)
		{
			up = VG_P1_UP_KEY_DSY;
			down = VG_P1_DOWN_KEY_DSY;
			left = VG_P1_LEFT_KEY_DSY;
			right = VG_P1_RIGHT_KEY_DSY;
			punch  = VG_P1_PUNCH1_KEY_DSY;
			punch2 = VG_P1_PUNCH2_KEY_DSY;
			kick   = VG_P1_KICK1_KEY_DSY;
			kick2  = VG_P1_KICK2_KEY_DSY;

			throw_key = VG_P1_THROW_KEY_DSY;
		}
		if(VG_P1_USING == VG_CONTROLLER)
		{
			punch  = 'ù'; // ÷ - A
			punch2 = 'ú'; // ø - B
			kick   = '÷'; // ù - X 
			kick2  = 'ø'; // ú - Y

			throw_key = '»';
		}

		if(VG_P1_USING == VG_KEYBOARD) 
		{  
			if(VG_1_CHARACTER == VG_GYEONG)    
				sprintf( new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c KEY^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if(VG_1_CHARACTER == VG_SIU)
				sprintf( new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c KEY^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if(VG_1_CHARACTER == VG_MINSO)
				sprintf( new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c KEY^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if(VG_1_CHARACTER == VG_REESE)
				sprintf( new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c KEY^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if(VG_1_CHARACTER == VG_YOHAN)
				sprintf( new_counter[1].word, "IMPORTANT!^TO THROW AN^OPPONENT^PRESS THE %c KEY^TO ATTACH A^BOMB^^DEFEAT THEM WITH^THE BOMB^TO WASTE THEM!", throw_key);
			if(VG_1_CHARACTER == VG_JAE)
				sprintf( new_counter[1].word, "IMPORTANT!^TO THROW AN^OPPONENT^PRESS THE %c KEY^^DEFEAT THEM WHILST^THEY$RE DIZZY^TO WASTE THEM!", throw_key);
			if(VG_1_CHARACTER == VG_GUN)
				sprintf( new_counter[1].word, "IMPORTANT!^TO THROW AN^OPPONENT^PRESS THE %c KEY^^DEFEAT THEM WHILST^THEY$RE DIZZY^TO WASTE THEM!", throw_key);
			if(VG_1_CHARACTER == VG_HYUK)
				sprintf( new_counter[1].word, "IMPORTANT!^TO THROW AN^OPPONENT^PRESS THE %c KEY^TO ATTACH A^GRENADE^^DEFEAT THEM WITH^THE GRENADE^TO WASTE THEM!", throw_key);
			if (VG_1_CHARACTER == VG_SHO)
				sprintf(new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c KEY^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if (VG_1_CHARACTER == VG_TIA)
				sprintf(new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c KEY^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if (VG_1_CHARACTER == VG_SAIZO)
				sprintf(new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c KEY^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if (VG_1_CHARACTER == VG_SANG)
				sprintf(new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c KEY^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if(VG_1_CHARACTER == VG_KENNEDY)
				sprintf( new_counter[1].word, "IMPORTANT!^TO THROW AN^OPPONENT^PRESS THE %c KEY^^DEFEAT THEM WHILST^THEY$RE DIZZY^TO WASTE THEM!", throw_key);

		}
		else  
		{ 
			if(VG_1_CHARACTER == VG_GYEONG)    
				sprintf( new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c BUTTON^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if(VG_1_CHARACTER == VG_SIU)
				sprintf( new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c BUTTON^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if(VG_1_CHARACTER == VG_MINSO)
				sprintf( new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c BUTTON^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if(VG_1_CHARACTER == VG_REESE)
				sprintf( new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c BUTTON^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if(VG_1_CHARACTER == VG_YOHAN)
				sprintf( new_counter[1].word, "IMPORTANT!^TO THROW AN^OPPONENT^PRESS THE %c BUTTON^TO ATTACH A^BOMB^^DEFEAT THEM WITH^THE BOMB^TO WASTE THEM!", throw_key);
			if(VG_1_CHARACTER == VG_JAE)
				sprintf( new_counter[1].word, "IMPORTANT!^TO THROW AN^OPPONENT^PRESS THE %c BUTTON^^DEFEAT THEM WHILST^THEY$RE DIZZY^TO WASTE THEM!", throw_key);
			if(VG_1_CHARACTER == VG_GUN)
				sprintf( new_counter[1].word, "IMPORTANT!^TO THROW AN^OPPONENT^PRESS THE %c BUTTON^^DEFEAT THEM WHILST^THEY$RE DIZZY^TO WASTE THEM!", throw_key);
			if(VG_1_CHARACTER == VG_HYUK)
				sprintf( new_counter[1].word, "IMPORTANT!^TO THROW AN^OPPONENT^PRESS THE %c BUTTON^TO ATTACH A^GRENADE^^DEFEAT THEM WITH^THE GRENADE^TO WASTE THEM!", throw_key);
			if (VG_1_CHARACTER == VG_SHO)
				sprintf(new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c BUTTON^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if (VG_1_CHARACTER == VG_TIA)
				sprintf(new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c BUTTON^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if (VG_1_CHARACTER == VG_SAIZO)
				sprintf(new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c BUTTON^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if (VG_1_CHARACTER == VG_SANG)
				sprintf(new_counter[1].word, "IMPORTANT!^TO HANDCUFF AN^OPPONENT^PRESS THE %c BUTTON^^TO ARREST AN^OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", throw_key);
			if(VG_1_CHARACTER == VG_KENNEDY)
				sprintf( new_counter[1].word, "IMPORTANT!^TO THROW AN^OPPONENT^PRESS THE %c BUTTON^^DEFEAT THEM WHILST^THEY$RE DIZZY^TO WASTE THEM!", throw_key);

		} 

		VG_Moveslist(2, VG_1_CHARACTER, 3, 1);
		VG_Moveslist(3, VG_1_CHARACTER, 4, 1);
		VG_Moveslist(4, VG_1_CHARACTER, 5, 1); 

		if(title_sequence == 0) 
		{ 
			GRID_TIMER = (int)TimerGetTime() + 3000;

		    GRID_LEFT_RIGHT = rand()%2; 
		    GRID_UP_DOWN = rand()%2;

			VG_arcade_sequence = 0;

			VG_SHEET_ANIM = 0;

			VG_SELECTED = 0; 

			X_align = 0.05f;     
			Y_align = +0.24f;    

			if(VG_1_CHARACTER == VG_GYEONG)
				sprintf( new_counter[0].word, "GYEONG^");   
			if(VG_1_CHARACTER == VG_SIU)
				sprintf( new_counter[0].word, "  SI$U^");   
			if(VG_1_CHARACTER == VG_MINSO) 
				sprintf( new_counter[0].word, " MINSO^");   
			if(VG_1_CHARACTER == VG_REESE) 
				sprintf( new_counter[0].word, " REESE^");   
			if(VG_1_CHARACTER == VG_YOHAN)
				sprintf( new_counter[0].word, " YOHAN^");   
			if(VG_1_CHARACTER == VG_JAE)
				sprintf( new_counter[0].word, "  JAE^");   
			if(VG_1_CHARACTER == VG_GUN)
				sprintf( new_counter[0].word, "  GUN^");   
			if(VG_1_CHARACTER == VG_HYUK)
				sprintf( new_counter[0].word, "  HYUK^");  
			if (VG_1_CHARACTER == VG_SHO)
				sprintf(new_counter[0].word,  "  SHO^");
			if (VG_1_CHARACTER == VG_TIA)
				sprintf(new_counter[0].word,  "  TIA^");
			if (VG_1_CHARACTER == VG_SAIZO)
				sprintf(new_counter[0].word,  " SAIZO^");
			if(VG_1_CHARACTER == VG_KENNEDY)
				sprintf( new_counter[0].word, "KEN ANDERSON^");  

			if(VG_1_CHARACTER == VG_GYEONG && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, "TOYUN^");   
			if(VG_1_CHARACTER == VG_SIU && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, "DAE-SU^");   
			if(VG_1_CHARACTER == VG_MINSO && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, "   MIA^");   
			if(VG_1_CHARACTER == VG_REESE && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, "   BOB^");   
			if(VG_1_CHARACTER == VG_YOHAN && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, "SUNG-KI^");   
			if(VG_1_CHARACTER == VG_JAE && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, "SAPPORO^");   
			if(VG_1_CHARACTER == VG_GUN && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, "  KONU^");   
			if(VG_1_CHARACTER == VG_HYUK && VG_IS_AN_ALTER_P1 == true)
				sprintf( new_counter[0].word, " YE-JUN^"); 

			new_counter[0].alpha = 1.0f;         
			new_counter[0].id = 2;  
		      
			new_counter[0].type = 0;  // Large Font...
			new_counter[0].right = false; 
			 
			new_counter[0].x = -0.05f;   
			new_counter[0].y = +0.32f;  	        

			new_counter[0].w = new_counter[0].x - 0.026f;   
			new_counter[0].z = new_counter[0].y - 0.015f;

			new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
			new_counter[0].box_height = new_counter[0].height - 0.015f;	

			scroll_index = 0;
			scroll_length = strlen(new_counter[1].word);
			scroll_txt_active = true; 
			new_counter[1].scroll_this = true;

			new_counter[1].alpha = 1.0f;             
			new_counter[1].id = 3;     
		       
			new_counter[1].type = 1;  // Large Font...  
			new_counter[1].right = false;   

			new_counter[1].x = 0.10f;             
			new_counter[1].y = Y_align;    	       

			new_counter[1].w = new_counter[1].x - 0.026f;   
			new_counter[1].z = new_counter[1].y - 0.015f;
			     
			new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
			new_counter[1].box_height = new_counter[1].height - 0.015f;	

			VG_Moveslist(2, VG_1_CHARACTER, 0, 1);

			new_counter[2].alpha = 1.0f;            
			new_counter[2].id = 3;   
		       
			new_counter[2].type = 1;  // Large Font...  
			new_counter[2].right = false;   
			 
			if (screen_mode == SCREEN_NORMAL) // 4:3
				new_counter[2].x = -0.45f;
			else
				new_counter[2].x = -0.57f;
			new_counter[2].y = -0.24f;     

			new_counter[2].w = new_counter[2].x - 0.026f;   
			new_counter[2].z = new_counter[2].y - 0.015f;
			     
			new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
			new_counter[2].box_height = new_counter[2].height - 0.015f;	
			 
			VG_Moveslist(3, VG_1_CHARACTER, 1, 1);

			new_counter[3].alpha = 1.0f;            
			new_counter[3].id = 3;   
		       
			new_counter[3].type = 1;  // Large Font...  
			new_counter[3].right = false;    

			if (screen_mode == SCREEN_NORMAL) // 4:3
				new_counter[3].x = -0.13f;
			else
				new_counter[3].x = -0.13f;
			new_counter[3].y = -0.24f;     

			new_counter[3].w = new_counter[3].x - 0.026f;   
			new_counter[3].z = new_counter[3].y - 0.015f;
			     
			new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
			new_counter[3].box_height = new_counter[3].height - 0.015f;	

			VG_Moveslist(4, VG_1_CHARACTER, 2, 1);
			 
			new_counter[4].alpha = 1.0f;              
			new_counter[4].id = 3;   
		        
			new_counter[4].type = 1;  // Large Font...  
			new_counter[4].right = false;   
			 
			if (screen_mode == SCREEN_NORMAL) // 4:3
				new_counter[4].x = 0.23f;
			else
				new_counter[4].x = 0.30f;

			new_counter[4].y = -0.24f;      

			new_counter[4].w = new_counter[4].x - 0.026f;   
			new_counter[4].z = new_counter[4].y - 0.015f; 
			     
			new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
			new_counter[4].box_height = new_counter[4].height - 0.015f;	

			if(TURN_OFF_INGAME_HELP == 0)
			{
				sprintf( new_counter[7].word, "^     Z: NEXT ESC: BACK^"); 
			  
				new_counter[7].alpha = 1.0f;                     
				new_counter[7].id = 3;        
				  
				new_counter[7].type = 1;  // Small Font...
				new_counter[7].right = false;

				new_counter[7].x = -0.26f;                    
				new_counter[7].y = VG_BOTTOM_OPTIONS_OFFSET;       

				new_counter[7].w = new_counter[7].x - 0.026f;   
				new_counter[7].z = new_counter[7].y - 0.015f;

				new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
				new_counter[7].box_height = new_counter[7].height - 0.015f;	
			}
			title_timer = (int)TimerGetTime() + 12000;
			title_sequence++; 
		} // title_sequence == 0

 		if((int)TimerGetTime() > flash_helptext_timer)   
		{
			if(new_counter[7].alpha == 0.0f)
			{
				flash_helptext_timer = (int)TimerGetTime() + 500;
				new_counter[7].alpha = 1.0f;
			}
			else
			{
				flash_helptext_timer = (int)TimerGetTime() + 500;
				new_counter[7].alpha = 0.0f;
			}
		}

		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[7].word, "^     %c: NEXT %c: BACK^", VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
		else
			sprintf( new_counter[7].word, "^     ÷: NEXT ø: BACK^");

		if(title_sequence == 1)    
		{ 
			// Pressed back key...
			if(VG_1_HUD_BACK == true) 
			{ 
				VG_reset_input();

			    VG_1_WINS = 0; 
			    VG_2_WINS = 0; 

			    VG_ROUND = 1;

				vg_selected_character = false;

				vg_next_episode = 6;
				vg_next_scene  = 1;    
				  
				next_scene = true; 
			}
			if(VG_1_HUD_GO == true
			) // Go to map screen...  // || (int)TimerGetTime() > title_timer
			{ 
				VG_reset_input(); 

				mouseleft = false;        
				DX_SHOOT = false;  


				if(VG_TRAINING == true)
				{
					VG_IS_VERSUS_SCREEN = true;
      
					VG_2_CHARACTER = VG_TRAINER;    
						  
					VG_BACKGROUND = VG_TRAINER; 

					vg_next_episode = 6;        
					vg_next_scene  = 0;
				}
				else
				{
					vg_next_episode = 6;        
					vg_next_scene  = 1; 
				}

				next_scene = true;

			}

		} // title_sequence == 1 


   }  // scene == 10

   // ******************************************************************************//
   //                             0-11  (SCORE SHEET)                               //
   // ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode) 
   if(next_scene == false)
   if(episode == 0 && scene == 11)        
   {      
#if 0
		if(title_sequence == 0)  
		{  
			 
			#if IS_FULL_STEAM == 1 
			 
				if (STEAM_ACTIVE == true) 
				{
					if(VG_SURVIVAL == true)
					{
						for(int i = 0;i< 100;i++)
							g_SteamLeaderboards_survivalscore->m_leaderboardEntries[i].m_nScore = 0;
						g_SteamLeaderboards_survivalscore->VG_DownloadScores(); 
					}
					else
					{
						if(VG_ARCADE_TYPE == VG_ARCADE_STANDARD)
						{
							for(int i = 0;i< 100;i++)
								g_SteamLeaderboards_finalscore->m_leaderboardEntries[i].m_nScore = 0;
							g_SteamLeaderboards_finalscore->VG_DownloadScores(); 
						}
						if(VG_ARCADE_TYPE == VG_ARCADE_DUELLING)
						{
							for(int i = 0;i< 100;i++)
								g_SteamLeaderboards_duellingscore->m_leaderboardEntries[i].m_nScore = 0;
							g_SteamLeaderboards_duellingscore->VG_DownloadScores(); 
						}
						if(VG_ARCADE_TYPE == VG_ARCADE_TURBO)
						{
							for(int i = 0;i< 100;i++)
								g_SteamLeaderboards_turboscore->m_leaderboardEntries[i].m_nScore = 0;
							g_SteamLeaderboards_turboscore->VG_DownloadScores(); 
						}
						if(VG_ARCADE_TYPE == VG_ARCADE_MASTER)
						{
							for(int i = 0;i< 100;i++)
								g_SteamLeaderboards_masterscore->m_leaderboardEntries[i].m_nScore = 0;
							g_SteamLeaderboards_masterscore->VG_DownloadScores(); 
						}

					}

				}

			#endif

			VG_SELECTED = 0;

			X_align = 0.05f;     
			Y_align = +0.24f;    

			sprintf( new_counter[0].word, "TOP PLAYERS^"); 

			new_counter[0].alpha = 1.0f;         
			new_counter[0].id = 2;  
		      
			new_counter[0].type = 0;  // Large Font...
			new_counter[0].right = false;         
			 
			new_counter[0].x = -0.12f;          
			new_counter[0].y = +0.32f;   	         
			 
			new_counter[0].w = new_counter[0].x - 0.026f;    
			new_counter[0].z = new_counter[0].y - 0.015f; 

			new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
			new_counter[0].box_height = new_counter[0].height - 0.015f;	
			 
			if(VG_SURVIVAL == true)
				sprintf( new_counter[1].word, "RANK  NAME               WINS   TIME"); 

			if(VG_SURVIVAL == false)
				sprintf( new_counter[1].word, "RANK  NAME               RND  ¿+ã    TIME"); 
			  
			new_counter[1].alpha = 1.0f;                     
			new_counter[1].id = 3;     
		       
			new_counter[1].type = 1;  // Large Font...  
			new_counter[1].right = false;   
			     
			new_counter[1].x = -0.45f;              
			new_counter[1].y = Y_align;    	          

			new_counter[1].w = new_counter[1].x - 0.026f;   
			new_counter[1].z = new_counter[1].y - 0.015f;
			     
			new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
			new_counter[1].box_height = new_counter[1].height - 0.015f;	

			if(TURN_OFF_INGAME_HELP == 0)
			{
				sprintf( new_counter[2].word, "^     Z: NEXT ESC: BACK^"); 
			  
				new_counter[2].alpha = 1.0f;                     
				new_counter[2].id = 3;        
				  
				new_counter[2].type = 1;  // Small Font...
				new_counter[2].right = false;

				new_counter[2].x = -0.24f;                    
				new_counter[2].y = VG_BOTTOM_OPTIONS_OFFSET;            

				new_counter[2].w = new_counter[2].x - 0.026f;   
				new_counter[2].z = new_counter[2].y - 0.015f; 

				new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
				new_counter[2].box_height = new_counter[2].height - 0.015f;	
			}

			vg_Y_align = 5.7f; // +0.24f  

			title_timer = (int)TimerGetTime() + 12000;
			title_sequence++; 

		} // title_sequence == 0      
		    
		if(vg_Y_align < 0.50f)   
		{
			vg_Y_align -= 0.00035f*(float)f_rate; // +0.24f  
		}
		else   
		{ 
			if(vg_Y_align < 1.00f) 
			{
				vg_Y_align -= 0.00045f*(float)f_rate; // +0.24f  
			}
			else
			{ 
				if(vg_Y_align < 2.00f)
				{
					vg_Y_align -= 0.00055f*(float)f_rate; // +0.24f  
				}
				else
					vg_Y_align -= 0.0020f*(float)f_rate; // +0.24f  
			}

		} 
		 
		if(vg_Y_align < 0.24f)  
			vg_Y_align = 0.24f;    

		vg_index_display = 3;  

		temp_Y_align = vg_Y_align;

		for(int i = 1;i<10;i++)  
		if(vg_index_display >= 0 && vg_index_display < 300)
		{
			    
			if((i-1) >= 0)   
			{
				if(vg_index_display >= 0 && vg_index_display < 300)
					sprintf( new_counter[vg_index_display].word, "%iÐ    %.18s^", i, "EMPTY" ); 

				#if IS_FULL_STEAM == 1 
				if(STEAM_ACTIVE == true)
				{
					if(VG_SURVIVAL == true)
					{

						vg_temp_score = g_SteamLeaderboards_survivalscore->m_leaderboardEntries[i-1].m_nScore;

						if(vg_temp_score > 0)
						{

						vg_index_char = vg_temp_score%10;
				     
						vg_temp_score -= vg_index_char;

						sprintf( new_counter[vg_index_display].word, "%iÐ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_survivalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 

						if(vg_index_char == VG_GYEONG)
							sprintf( new_counter[vg_index_display].word, "%i{    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_survivalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
						if(vg_index_char == VG_SIU)
							sprintf( new_counter[vg_index_display].word, "%i}    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_survivalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
						if(vg_index_char == VG_MINSO)
							sprintf( new_counter[vg_index_display].word, "%i~    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_survivalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
						if(vg_index_char == VG_REESE)
							sprintf( new_counter[vg_index_display].word, "%i¡    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_survivalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 

						if(vg_index_char == VG_YOHAN)
							sprintf( new_counter[vg_index_display].word, "%iÌ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_survivalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
						if(vg_index_char == VG_JAE)
							sprintf( new_counter[vg_index_display].word, "%iÍ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_survivalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
						if(vg_index_char == VG_GUN)
							sprintf( new_counter[vg_index_display].word, "%iÎ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_survivalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
						if(vg_index_char == VG_HYUK)
							sprintf( new_counter[vg_index_display].word, "%iÏ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_survivalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
						}
						else
							sprintf( new_counter[vg_index_display].word, "%iÐ    %.18s^", i, "EMPTY" ); 

					}
					if(VG_SURVIVAL == false)
					{

						if(VG_ARCADE_TYPE == VG_ARCADE_STANDARD)
						{
							vg_temp_score = g_SteamLeaderboards_finalscore->m_leaderboardEntries[i-1].m_nScore;

							if(vg_temp_score > 0)
							{

								vg_index_char = vg_temp_score%10;
				     
								vg_temp_score -= vg_index_char;

								sprintf( new_counter[vg_index_display].word, "%iÐ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_finalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 

								if(vg_index_char == VG_GYEONG)
									sprintf( new_counter[vg_index_display].word, "%i{    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_finalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_SIU)
									sprintf( new_counter[vg_index_display].word, "%i}    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_finalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_MINSO)
									sprintf( new_counter[vg_index_display].word, "%i~    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_finalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_REESE)
									sprintf( new_counter[vg_index_display].word, "%i¡    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_finalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 

								if(vg_index_char == VG_YOHAN)
									sprintf( new_counter[vg_index_display].word, "%iÌ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_finalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_JAE)
									sprintf( new_counter[vg_index_display].word, "%iÍ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_finalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_GUN)
									sprintf( new_counter[vg_index_display].word, "%iÎ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_finalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_HYUK)
									sprintf( new_counter[vg_index_display].word, "%iÏ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_finalscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
							}
							else
								sprintf( new_counter[vg_index_display].word, "%iÐ    %.18s^", i, "EMPTY" ); 
						}
						  
						if(VG_ARCADE_TYPE == VG_ARCADE_DUELLING)
						{
							vg_temp_score = g_SteamLeaderboards_duellingscore->m_leaderboardEntries[i-1].m_nScore;

							if(vg_temp_score > 0)
							{

								vg_index_char = vg_temp_score%10;
				     
								vg_temp_score -= vg_index_char; 

								sprintf( new_counter[vg_index_display].word, "%iÐ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_duellingscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 

								if(vg_index_char == VG_GYEONG)
									sprintf( new_counter[vg_index_display].word, "%i{    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_duellingscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_SIU)
									sprintf( new_counter[vg_index_display].word, "%i}    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_duellingscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_MINSO)
									sprintf( new_counter[vg_index_display].word, "%i~    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_duellingscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_REESE)
									sprintf( new_counter[vg_index_display].word, "%i¡    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_duellingscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 

								if(vg_index_char == VG_YOHAN)
									sprintf( new_counter[vg_index_display].word, "%iÌ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_duellingscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_JAE)
									sprintf( new_counter[vg_index_display].word, "%iÍ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_duellingscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_GUN)
									sprintf( new_counter[vg_index_display].word, "%iÎ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_duellingscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_HYUK)
									sprintf( new_counter[vg_index_display].word, "%iÏ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_duellingscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
							}
							else
								sprintf( new_counter[vg_index_display].word, "%iÐ    %.18s^", i, "EMPTY" ); 
						}

						if(VG_ARCADE_TYPE == VG_ARCADE_TURBO)
						{
							vg_temp_score = g_SteamLeaderboards_turboscore->m_leaderboardEntries[i-1].m_nScore;

							if(vg_temp_score > 0)
							{

								vg_index_char = vg_temp_score%10;
				     
								vg_temp_score -= vg_index_char; 

								sprintf( new_counter[vg_index_display].word, "%iÐ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_turboscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 

								if(vg_index_char == VG_GYEONG)
									sprintf( new_counter[vg_index_display].word, "%i{    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_turboscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_SIU)
									sprintf( new_counter[vg_index_display].word, "%i}    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_turboscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_MINSO)
									sprintf( new_counter[vg_index_display].word, "%i~    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_turboscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_REESE)
									sprintf( new_counter[vg_index_display].word, "%i¡    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_turboscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 

								if(vg_index_char == VG_YOHAN)
									sprintf( new_counter[vg_index_display].word, "%iÌ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_turboscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_JAE)
									sprintf( new_counter[vg_index_display].word, "%iÍ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_turboscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_GUN)
									sprintf( new_counter[vg_index_display].word, "%iÎ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_turboscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_HYUK)
									sprintf( new_counter[vg_index_display].word, "%iÏ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_turboscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
							}
							else
								sprintf( new_counter[vg_index_display].word, "%iÐ    %.18s^", i, "EMPTY" ); 
						}

						if(VG_ARCADE_TYPE == VG_ARCADE_MASTER)
						{
							vg_temp_score = g_SteamLeaderboards_masterscore->m_leaderboardEntries[i-1].m_nScore;

							if(vg_temp_score > 0)
							{

								vg_index_char = vg_temp_score%10;
				     
								vg_temp_score -= vg_index_char; 

								sprintf( new_counter[vg_index_display].word, "%iÐ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_masterscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 

								if(vg_index_char == VG_GYEONG)
									sprintf( new_counter[vg_index_display].word, "%i{    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_masterscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_SIU)
									sprintf( new_counter[vg_index_display].word, "%i}    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_masterscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_MINSO)
									sprintf( new_counter[vg_index_display].word, "%i~    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_masterscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_REESE)
									sprintf( new_counter[vg_index_display].word, "%i¡    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_masterscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 

								if(vg_index_char == VG_YOHAN)
									sprintf( new_counter[vg_index_display].word, "%iÌ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_masterscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_JAE)
									sprintf( new_counter[vg_index_display].word, "%iÍ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_masterscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_GUN)
									sprintf( new_counter[vg_index_display].word, "%iÎ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_masterscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
								if(vg_index_char == VG_HYUK)
									sprintf( new_counter[vg_index_display].word, "%iÏ    %.18s^", i, SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_masterscore->m_leaderboardEntries[i-1].m_steamIDUser) ); 
							}
							else
								sprintf( new_counter[vg_index_display].word, "%iÐ    %.18s^", i, "EMPTY" ); 
						}

					}
		 
				} // STEAM_ACTIVE == true
				#endif

			} // (i-1) >= 0
			 
			temp_Y_align -= 0.06f;   

			new_counter[vg_index_display].alpha = 1.0f;              

			if(temp_Y_align > 0.20f)
				new_counter[vg_index_display].alpha = 0.0f;

			if(temp_Y_align < -0.33f)
				new_counter[vg_index_display].alpha = 0.0f;

			new_counter[vg_index_display].id = 3;     
		       
			new_counter[vg_index_display].type = 1;  // Large Font...  
			new_counter[vg_index_display].right = false;   
			 
			if(i >= 10)
				new_counter[vg_index_display].x = -0.473f;             
			else
				new_counter[vg_index_display].x = -0.45f;                  

			new_counter[vg_index_display].y = temp_Y_align;    	       

			new_counter[vg_index_display].w = new_counter[vg_index_display].x - 0.026f;   
			new_counter[vg_index_display].z = new_counter[vg_index_display].y - 0.015f;
			     
			new_counter[vg_index_display].box_width = strlen(new_counter[vg_index_display].word)   *  0.026f;
			new_counter[vg_index_display].box_height = new_counter[vg_index_display].height - 0.015f;	
			 
			vg_index_display++;   
			    
			sprintf( new_counter[vg_index_display].word, ""); 
			 
			#if IS_FULL_STEAM == 1 
			if(STEAM_ACTIVE == true)
			if(vg_index_display >= 0 && vg_index_display < 300)
			{
				   
			if(vg_temp_score > 0)             
			{   
				if(VG_SURVIVAL == false)
				{
					temp_secs = (vg_temp_score / 10)%10;  
					temp_secs += (((vg_temp_score / 100)%10)*10); 

					temp_mins = (vg_temp_score / 1000)%10;  
					temp_mins += (((vg_temp_score / 10000)%10)*10); 

					temp_mins = 99 - temp_mins;
					temp_secs = 99 - temp_secs;

					temp_perfects =  (vg_temp_score / 100000) - ((vg_temp_score/10000000)*100);   

					if(temp_mins <= 9) 
					{
						if(temp_secs <= 9)
						{
							if(temp_perfects <= 9)
								sprintf( new_counter[vg_index_display].word, "0%i   0%i   $0%i-0%i$^", vg_temp_score/10000000, temp_perfects, temp_mins, temp_secs);  
							else
								sprintf( new_counter[vg_index_display].word, "0%i   %i   $0%i-0%i$^", vg_temp_score/10000000, temp_perfects, temp_mins, temp_secs);  
						}
						else
						{
							if(temp_perfects <= 9)
								sprintf( new_counter[vg_index_display].word, "0%i   0%i   $0%i-%i$^", vg_temp_score/10000000, temp_perfects, temp_mins, temp_secs);  
							else
								sprintf( new_counter[vg_index_display].word, "0%i   %i   $0%i-%i$^", vg_temp_score/10000000, temp_perfects, temp_mins, temp_secs);  
						}
					}
					else 
					{
						if(temp_secs <= 9) 
						{
							if(temp_perfects <= 9)
								sprintf( new_counter[vg_index_display].word, "0%i   0%i   $%i-0%i$^", vg_temp_score/10000000, temp_perfects, temp_mins, temp_secs);  
							else
								sprintf( new_counter[vg_index_display].word, "0%i   %i   $%i-0%i$^", vg_temp_score/10000000, temp_perfects, temp_mins, temp_secs);  
						}
						else
						{
							if(temp_perfects <= 9)
								sprintf( new_counter[vg_index_display].word, "0%i   0%i   $%i-%i$^", vg_temp_score/10000000, temp_perfects, temp_mins, temp_secs);   
							else
								sprintf( new_counter[vg_index_display].word, "0%i   %i   $%i-%i$^", vg_temp_score/10000000, temp_perfects, temp_mins, temp_secs);   
						}
					}
				} // VG_SURVIVAL == true

				if(VG_SURVIVAL == true)
				if(vg_index_display >= 0 && vg_index_display < 300)
				{
					temp_secs = (vg_temp_score / 10)%10;  
					temp_secs += (((vg_temp_score / 100)%10)*10); 

					temp_mins = (vg_temp_score / 1000)%10;  
					temp_mins += (((vg_temp_score / 10000)%10)*10); 

					temp_mins = 99 - temp_mins;
					temp_secs = 99 - temp_secs;

					temp_perfects =  (vg_temp_score / 100000) - ((vg_temp_score/10000000)*100);   

					if(temp_mins <= 9) 
					{
						if(temp_secs <= 9)
						{
							if(temp_perfects <= 9)
								sprintf( new_counter[vg_index_display].word, "0%i   $0%i-0%i$^", temp_perfects, temp_mins, temp_secs);  
							else
								sprintf( new_counter[vg_index_display].word, "%i   $0%i-0%i$^", temp_perfects, temp_mins, temp_secs);  
						}
						else
						{
							if(temp_perfects <= 9)
								sprintf( new_counter[vg_index_display].word, "0%i   $0%i-%i$^", temp_perfects, temp_mins, temp_secs);  
							else
								sprintf( new_counter[vg_index_display].word, "%i   $0%i-%i$^", temp_perfects, temp_mins, temp_secs);  
						}
					}
					else 
					{
						if(temp_secs <= 9) 
						{
							if(temp_perfects <= 9)
								sprintf( new_counter[vg_index_display].word, "0%i   $%i-0%i$^", temp_perfects, temp_mins, temp_secs);  
							else
								sprintf( new_counter[vg_index_display].word, "%i   $%i-0%i$^", temp_perfects, temp_mins, temp_secs);  
						}
						else
						{
							if(temp_perfects <= 9)
								sprintf( new_counter[vg_index_display].word, "0%i   $%i-%i$^", temp_perfects, temp_mins, temp_secs);   
							else
								sprintf( new_counter[vg_index_display].word, "%i   $%i-%i$^", temp_perfects, temp_mins, temp_secs);   
						}
					}
				} // VG_SURVIVAL == false

			} // vg_temp_score > 0

			}
			#endif 

			new_counter[vg_index_display].alpha = 1.0f;     
			 
			if(temp_Y_align > 0.20f)
				new_counter[vg_index_display].alpha = 0.0f;

			if(temp_Y_align < -0.33f)
				new_counter[vg_index_display].alpha = 0.0f;
			 
			new_counter[vg_index_display].id = 3;     
		        
			new_counter[vg_index_display].type = 1;  // Large Font...  
			new_counter[vg_index_display].right = false;    

			new_counter[vg_index_display].x = +0.14f;             
			new_counter[vg_index_display].y = temp_Y_align;    	       

			new_counter[vg_index_display].w = new_counter[vg_index_display].x - 0.026f;   
			new_counter[vg_index_display].z = new_counter[vg_index_display].y - 0.015f;
			     
			new_counter[vg_index_display].box_width = strlen(new_counter[vg_index_display].word)   *  0.026f;
			new_counter[vg_index_display].box_height = new_counter[vg_index_display].height - 0.015f;	

			vg_index_display++;

		} // End of i loop...

 		if((int)TimerGetTime() > flash_helptext_timer)   
		{
			if(new_counter[0].alpha == 0.0f)
			{
				flash_helptext_timer = (int)TimerGetTime() + 500;
				new_counter[0].alpha = 1.0f;

				if(STEAM_ACTIVE == false)  
				{ 
					new_counter[0].x = -0.14f; 
					new_counter[0].id = 4;
					sprintf( new_counter[0].word, "NO CONNECTION^");
				}
			}
			else
			{
				flash_helptext_timer = (int)TimerGetTime() + 500; 
				new_counter[0].alpha = 0.0f;

				if(STEAM_ACTIVE == false)
				{
					new_counter[0].x = -0.12f;
					new_counter[0].id = 2;
					sprintf( new_counter[0].word, "TOP PLAYERS^");
				}
			}
		}

		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[2].word, "^     %c: NEXT %c: BACK^", VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
		else
			sprintf( new_counter[2].word, "^     ÷: NEXT ø: BACK^");

#endif


		title_sequence = 1;
		VG_1_HUD_BACK = true;

		if(title_sequence == 1)    
		{ 
			// Pressed back key...
			if(VG_1_HUD_BACK == true) 
			{ 
				VG_reset_input();

				vg_next_episode = 0; 
				vg_next_scene  = 13;    

				if(VG_BEAT_THE_GAME == true)
				{
					vg_next_episode = 0; 
					vg_next_scene  = 1; 

					VG_BEAT_THE_GAME = false;
				}
				  
				next_scene = true; 
			}
			if(VG_1_HUD_GO == true
			) // Go to map screen...  // || (int)TimerGetTime() > title_timer
			{ 
				VG_reset_input(); 

				mouseleft = false;        
				DX_SHOOT = false;  

				vg_next_episode = 0;        
				vg_next_scene  = 13; 

				if(VG_BEAT_THE_GAME == true)
				{
					vg_next_episode = 0; 
					vg_next_scene  = 1; 

					VG_BEAT_THE_GAME = false;
				}

				next_scene = true;

			}

		} // title_sequence == 1 


   }  // scene == 11

	// ******************************************************************************//
	//                            0-12  (GAME OPTIONS)                               //
	// ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode)  
   if(next_scene == false)
   if(episode == 0 && scene == 12)        
   {       
		 
		if(title_sequence == 0) 
		{ 

			VG_SELECTED = 0;
			 
			X_align = -0.21f;    
			Y_align = +0.20f;    

			sprintf( new_counter[0].word, "VERSUS OPTIONS"); 

			new_counter[0].alpha = 1.0f;        
			new_counter[0].id = 2; 
		      
			new_counter[0].type = 0;  // Large Font...
			new_counter[0].right = false; 

			new_counter[0].x = X_align+0.07f;      
			new_counter[0].y = +0.29f;  	      

			new_counter[0].w = new_counter[0].x - 0.026f;   
			new_counter[0].z = new_counter[0].y - 0.015f;

			new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
			new_counter[0].box_height = new_counter[0].height - 0.015f;	

			sprintf( new_counter[1].word, "ROUND TIME"); 

			new_counter[1].alpha = 1.0f;            
			new_counter[1].id = 3;    
		      
			new_counter[1].type = 0;  // Large Font...
			new_counter[1].right = false; 
			 
			new_counter[1].x = X_align;               
			new_counter[1].y = Y_align;    	      

			new_counter[1].w = new_counter[1].x - 0.026f;   
			new_counter[1].z = new_counter[1].y - 0.015f;
			     
			new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
			new_counter[1].box_height = new_counter[1].height - 0.015f;	

			sprintf( new_counter[5].word, " 60"); 

			new_counter[5].alpha = 1.0f;            
			new_counter[5].id = 0;     
		      
			new_counter[5].type = 0;  // Large Font...
			new_counter[5].right = false; 
			 
			new_counter[5].x = X_align;               
			new_counter[5].y = new_counter[1].y-0.06f;      

			new_counter[5].w = new_counter[5].x - 0.026f;   
			new_counter[5].z = new_counter[5].y - 0.015f;
			     
			new_counter[5].box_width = strlen(new_counter[5].word)   *  0.026f;
			new_counter[5].box_height = new_counter[5].height - 0.015f;	

			sprintf( new_counter[6].word, " 100"); 

			new_counter[6].alpha = 1.0f;            
			new_counter[6].id = 0;    
		       
			new_counter[6].type = 0;  // Large Font...
			new_counter[6].right = false; 
			 
			new_counter[6].x = 0.08f;               
			new_counter[6].y = new_counter[1].y-0.06f;      

			new_counter[6].w = new_counter[6].x - 0.026f;   
			new_counter[6].z = new_counter[6].y - 0.015f;
			     
			new_counter[6].box_width = strlen(new_counter[6].word)   *  0.026f;
			new_counter[6].box_height = new_counter[6].height - 0.015f;	

			sprintf( new_counter[2].word, "HEALTH"); 

			new_counter[2].alpha = 1.0f;            
			new_counter[2].id = 3;  
		      
			new_counter[2].type = 0;  // Large Font...
			new_counter[2].right = false;
			  
			new_counter[2].x = X_align;             
			new_counter[2].y = new_counter[5].y-0.06f;        	      

			new_counter[2].w = new_counter[2].x - 0.026f;   
			new_counter[2].z = new_counter[2].y - 0.015f;

			new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
			new_counter[2].box_height = new_counter[2].height - 0.015f;	

			sprintf( new_counter[7].word, " 100"); 

			new_counter[7].alpha = 1.0f;            
			new_counter[7].id = 0;    
		      
			new_counter[7].type = 0;  // Large Font...
			new_counter[7].right = false; 
			 
			new_counter[7].x = X_align;               
			new_counter[7].y = new_counter[2].y-0.06f;      

			new_counter[7].w = new_counter[7].x - 0.026f;   
			new_counter[7].z = new_counter[7].y - 0.015f;
			     
			new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
			new_counter[7].box_height = new_counter[7].height - 0.015f;	

			sprintf( new_counter[8].word, " 200"); 

			new_counter[8].alpha = 1.0f;            
			new_counter[8].id = 0;    
		      
			new_counter[8].type = 0;  // Large Font...
			new_counter[8].right = false; 
			 
			new_counter[8].x = 0.08f;            
			new_counter[8].y = new_counter[2].y-0.06f;      

			new_counter[8].w = new_counter[8].x - 0.026f;   
			new_counter[8].z = new_counter[8].y - 0.015f;
			     
			new_counter[8].box_width = strlen(new_counter[8].word)   *  0.026f;
			new_counter[8].box_height = new_counter[8].height - 0.015f;	

			sprintf( new_counter[3].word, "BACKGROUNDS"); 

			new_counter[3].alpha = 1.0f;            
			new_counter[3].id = 3;  
		      
			new_counter[3].type = 0;  // Large Font...
			new_counter[3].right = false;
			  
			new_counter[3].x = X_align;             
			new_counter[3].y = new_counter[7].y-0.06f;        	      

			new_counter[3].w = new_counter[3].x - 0.026f;   
			new_counter[3].z = new_counter[3].y - 0.015f;

			new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
			new_counter[3].box_height = new_counter[3].height - 0.015f;	

			sprintf( new_counter[9].word, " RANDOM"); 

			new_counter[9].alpha = 1.0f;            
			new_counter[9].id = 0;    
		      
			new_counter[9].type = 0;  // Large Font...
			new_counter[9].right = false; 
			 
			new_counter[9].x = X_align;               
			new_counter[9].y = new_counter[3].y-0.06f;      

			new_counter[9].w = new_counter[9].x - 0.026f;   
			new_counter[9].z = new_counter[9].y - 0.015f;
			     
			new_counter[9].box_width = strlen(new_counter[9].word)   *  0.026f;
			new_counter[9].box_height = new_counter[9].height - 0.015f;	

			sprintf( new_counter[10].word, " CHAR"); 

			new_counter[10].alpha = 1.0f;            
			new_counter[10].id = 0;    
		      
			new_counter[10].type = 0;  // Large Font...
			new_counter[10].right = false; 
			 
			new_counter[10].x = 0.08f;            
			new_counter[10].y = new_counter[3].y-0.06f;      

			new_counter[10].w = new_counter[10].x - 0.026f;   
			new_counter[10].z = new_counter[10].y - 0.015f;
			     
			new_counter[10].box_width = strlen(new_counter[10].word)   *  0.026f;
			new_counter[10].box_height = new_counter[10].height - 0.015f;	

			sprintf( new_counter[4].word, "BACK");  
			 
			new_counter[4].alpha = 1.0f;              
			new_counter[4].id = 0; 
		      
			new_counter[4].type = 0;  // Large Font...
			new_counter[4].right = false;

			new_counter[4].x = X_align;             
			new_counter[4].y = new_counter[10].y-0.06f;           	      

			new_counter[4].w = new_counter[4].x - 0.026f;   
			new_counter[4].z = new_counter[4].y - 0.015f;

			new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
			new_counter[4].box_height = new_counter[4].height - 0.015f;	

			sprintf( new_counter[12].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015-2019"); 
			 
			new_counter[12].alpha = 1.0f;                 
			new_counter[12].id = 3;        
				  
			new_counter[12].type = 1;  // Small Font...
			new_counter[12].right = false;

			new_counter[12].x = -0.28f;                    
			new_counter[12].y = VG_BOTTOM_OPTIONS_OFFSET;          

			new_counter[12].w = new_counter[12].x - 0.026f;   
			new_counter[12].z = new_counter[12].y - 0.015f;

			new_counter[12].box_width = strlen(new_counter[12].word)   *  0.026f;
			new_counter[12].box_height = new_counter[12].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[12].word, "%c-%c MOVE  %c: SELECT %c: BACK^&RETRO ARMY LTD. 2015-2019", VG_P1_UP_KEY_DSY, VG_P1_DOWN_KEY_DSY, VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
		else
			sprintf( new_counter[12].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015-2019");

		sprintf( new_counter[1].word, "ROUND TIME");
		sprintf( new_counter[2].word, "HEALTH");
		sprintf( new_counter[3].word, "BACKGROUNDS");

		if(VG_VS_TIME == 0)
		{
			sprintf( new_counter[5].word, "Ë100s");
			sprintf( new_counter[6].word, " 60s");
		}
		if(VG_VS_TIME == 1)
		{
			sprintf( new_counter[5].word, " 100s");
			sprintf( new_counter[6].word, "Ë60s");
		}
		if(VG_VS_HEALTH == 0)
		{
			sprintf( new_counter[7].word, "Ë1000"); 
			sprintf( new_counter[8].word, " 2000");
		}
		if(VG_VS_HEALTH == 1)
		{
			sprintf( new_counter[7].word, " 1000"); 
			sprintf( new_counter[8].word, "Ë2000");
		}
		if(VG_VS_BG == 0)
		{
			sprintf( new_counter[9].word,  "ËCHAR"); 
			sprintf( new_counter[10].word, " RANDOM");
		}
		if(VG_VS_BG == 1)
		{
			sprintf( new_counter[9].word,  " CHAR"); 
			sprintf( new_counter[10].word, "ËRANDOM");
		}
		if(title_sequence == 1) 
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == true)
			{
				VG_reset_input();
				vg_next_episode = 0;
				vg_next_scene  = 2;

				next_scene = true;
			}

			if(VG_1_HUDDOWN == VG_PRESSED)
			{
				vg_titlemove_sfx = true;
				VG_SELECTED++;
				if(VG_SELECTED > 3)    
					VG_SELECTED = 0;
				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false;
				VG_reset_input();
			} 

			if(VG_1_HUDUP == VG_PRESSED)
			{
				vg_titlemove_sfx = true;
				VG_SELECTED--; 
				if(VG_SELECTED < 0)
					VG_SELECTED = 3; 
				VG_1_HUDUP = false;
				VG_2_HUDUP = false;
				VG_reset_input();
			}

			new_counter[1].id = 0;
			new_counter[2].id = 0; 
			new_counter[3].id = 0;
			new_counter[4].id = 0;

			new_counter[5].id = 4; 
			new_counter[6].id = 4;
			new_counter[7].id = 4;
			new_counter[8].id = 4;
			new_counter[9].id = 4;
			new_counter[10].id = 4;

			if(VG_SELECTED == 0) // WINDOW OPTIONS
			{
				new_counter[1].id = 2; 
				 
				if(VG_VS_TIME == 0)
					new_counter[5].id = 3; // Windowed...
				if(VG_VS_TIME == 1)
					new_counter[6].id = 3; // Fullscreen..

				sprintf( new_counter[1].word, "ROUND TIME ¢-¤"); 

				if(VG_1_HUDRIGHT == VG_PRESSED)
				{
					VG_reset_input();
					if(VG_VS_TIME == 0)
					{
						VG_VS_TIME = 1;
						vg_titlemove_sfx = true;
					}
					VG_1_HUDRIGHT = false;
				}

				if(VG_1_HUDLEFT == VG_PRESSED)
				{
					VG_reset_input();
					if(VG_VS_TIME == 1)
					{
						VG_VS_TIME = 0;
						vg_titlemove_sfx = true;
					}
					VG_1_HUDLEFT = false;
				}
			} 
			if(VG_SELECTED == 1) // RENDERER OPTIONS
			{
				new_counter[2].id = 2; 

				if(VG_VS_HEALTH == 0)
					new_counter[7].id = 3; // DirectX...
				if(VG_VS_HEALTH == 1)
					new_counter[8].id = 3; // OpenGl...

				sprintf( new_counter[2].word, "HEALTH ¢-¤");

				if(VG_1_HUDRIGHT == VG_PRESSED)
				{
					VG_reset_input();
					if(VG_VS_HEALTH == 0)
					{
						VG_VS_HEALTH = 1;
						vg_titlemove_sfx = true;
					}
					VG_1_HUDRIGHT = false;
				}

				if(VG_1_HUDLEFT == VG_PRESSED)
				{
					VG_reset_input();
					if(VG_VS_HEALTH == 1)
					{
						VG_VS_HEALTH = 0;
						vg_titlemove_sfx = true;
					}
					VG_1_HUDLEFT = false;
				}
			}   
			if(VG_SELECTED == 2) // BACKGROUNDS 
			{   
				new_counter[3].id = 2;

				if(VG_VS_BG == 0)
					new_counter[9].id = 3; // Windowed...
				if(VG_VS_BG == 1)
					new_counter[10].id = 3; // Fullscreen..

				sprintf( new_counter[3].word, "BACKGROUNDS ¢-¤");

				if(VG_1_HUDRIGHT == VG_PRESSED)
				{
					VG_reset_input();
					if(VG_VS_BG == 0)
					{
						VG_VS_BG = 1;
						vg_titlemove_sfx = true;
					}
					VG_1_HUDRIGHT = false;
				}

				if(VG_1_HUDLEFT == VG_PRESSED)
				{
					VG_reset_input();
					if(VG_VS_BG == 1)
					{
						VG_VS_BG = 0;
						vg_titlemove_sfx = true;
					}
					VG_1_HUDLEFT = false;
				}
			}
			if(VG_SELECTED == 3) // BACK
			{   
				new_counter[4].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
			}

		} // title_sequence == 1 

		if(title_sequence == 2)    
		{ 
			if((int)TimerGetTime() > VG_Flicker_HUD_Button_timer) 
			{
				VG_Flicker_HUD_Button_timer = (int)TimerGetTime() + 25; 

				if(VG_SELECTED == 0) // WINDOWED
				{
					if(new_counter[1].id == 0) 
						new_counter[1].id = 2;
					else
						new_counter[1].id = 0;
				} 

				if(VG_SELECTED == 1) // FULLSCREEN
				{
					if(new_counter[2].id == 0) 
						new_counter[2].id = 2;
					else
						new_counter[2].id = 0;
				} 
				if(VG_SELECTED == 2) // MAKE CHANGES
				{
					if(new_counter[3].id == 0) 
						new_counter[3].id = 2;
					else
						new_counter[3].id = 0;
				} 
				if(VG_SELECTED == 3) // BACK
				{
					if(new_counter[4].id == 0) 
						new_counter[4].id = 2;
					else
						new_counter[4].id = 0;
				} 

			}
			   
			if((int)TimerGetTime() > title_timer) 
			{

				if(VG_SELECTED == 0) // WINDOWED
				{					  
					mouseleft = false;               
					DX_SHOOT = false;   
				}
				if(VG_SELECTED == 1) // FULLSCREEN
				{					  
					mouseleft = false;                
					DX_SHOOT = false;    
				}
				if(VG_SELECTED == 2) // MAKE CHANGES
				{
					mouseleft = false;                
					DX_SHOOT = false;  
				}
				if(VG_SELECTED == 3) // BACK
				{
						 
					mouseleft = false;        
					DX_SHOOT = false;  

						 
					vg_next_episode = 0;   
					vg_next_scene  = 2;


					next_scene = true;
				}

			}



		}

   }   // 0 - 12

   
	// ******************************************************************************//
	//                             0-13  (SCOREBOARDS)                               //
	// ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode)  
   if(next_scene == false)
   if(episode == 0 && scene == 13)         
   {       
#if 0
		if(title_sequence == 0) 
		{ 

			#if IS_FULL_STEAM == 1 
			  
				if (STEAM_ACTIVE == true) 
				{

					for(int i = 0;i< 100;i++)
						g_SteamLeaderboards_survivalscore->m_leaderboardEntries[i].m_nScore = 0;

					g_SteamLeaderboards_survivalscore->VG_DownloadScores(); 

					for(int i = 0;i< 100;i++)
						g_SteamLeaderboards_finalscore->m_leaderboardEntries[i].m_nScore = 0;

					g_SteamLeaderboards_finalscore->VG_DownloadScores(); 

					for(int i = 0;i< 100;i++)
						g_SteamLeaderboards_duellingscore->m_leaderboardEntries[i].m_nScore = 0;

					g_SteamLeaderboards_duellingscore->VG_DownloadScores(); 

					for(int i = 0;i< 100;i++)
						g_SteamLeaderboards_turboscore->m_leaderboardEntries[i].m_nScore = 0;

					g_SteamLeaderboards_turboscore->VG_DownloadScores(); 

					for(int i = 0;i< 100;i++)
						g_SteamLeaderboards_masterscore->m_leaderboardEntries[i].m_nScore = 0;

					g_SteamLeaderboards_masterscore->VG_DownloadScores(); 

				}

			#endif

			VG_SELECTED = 0;
			 
			X_align = -0.21f;    
			Y_align = +0.20f;    

			sprintf( new_counter[0].word, " SCOREBOARDS"); 

			new_counter[0].alpha = 1.0f;        
			new_counter[0].id = 2; 
		      
			new_counter[0].type = 0;  // Large Font...
			new_counter[0].right = false; 

			new_counter[0].x = X_align+0.07f;      
			new_counter[0].y = +0.29f;  	      

			new_counter[0].w = new_counter[0].x - 0.026f;   
			new_counter[0].z = new_counter[0].y - 0.015f;

			new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
			new_counter[0].box_height = new_counter[0].height - 0.015f;	

			sprintf( new_counter[1].word, "ARCADE SCORES"); 

			new_counter[1].alpha = 1.0f;            
			new_counter[1].id = 3;    
		      
			new_counter[1].type = 0;  // Large Font...
			new_counter[1].right = false; 
			 
			new_counter[1].x = X_align;               
			new_counter[1].y = Y_align;    	      

			new_counter[1].w = new_counter[1].x - 0.026f;   
			new_counter[1].z = new_counter[1].y - 0.015f;
			     
			new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
			new_counter[1].box_height = new_counter[1].height - 0.015f;	

			sprintf( new_counter[2].word, "SURVIVAL SCORES"); 

			new_counter[2].alpha = 1.0f;            
			new_counter[2].id = 3;  
		      
			new_counter[2].type = 0;  // Large Font...
			new_counter[2].right = false;
			  
			new_counter[2].x = X_align;             
			new_counter[2].y = new_counter[1].y-0.06f;        	      

			new_counter[2].w = new_counter[2].x - 0.026f;   
			new_counter[2].z = new_counter[2].y - 0.015f;

			new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
			new_counter[2].box_height = new_counter[2].height - 0.015f;	

			if(VG_DUELLISTS_UNLOCKED == 0)
				sprintf( new_counter[3].word, "?????? SCORES");  
			else
				sprintf( new_counter[3].word, "DUELLING SCORES");  
			 
			new_counter[3].alpha = 1.0f;              
			new_counter[3].id = 0; 
		      
			new_counter[3].type = 0;  // Large Font...
			new_counter[3].right = false;

			new_counter[3].x = X_align;             
			new_counter[3].y = new_counter[2].y-0.06f;           	      

			new_counter[3].w = new_counter[3].x - 0.026f;   
			new_counter[3].z = new_counter[3].y - 0.015f;

			new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
			new_counter[3].box_height = new_counter[3].height - 0.015f;	

			if(VG_TURBO_UNLOCKED == 0)
				sprintf( new_counter[4].word, "?????? SCORES");  
			else
				sprintf( new_counter[4].word, "TURBO SCORES");  
			 
			new_counter[4].alpha = 1.0f;              
			new_counter[4].id = 0; 
		      
			new_counter[4].type = 0;  // Large Font...
			new_counter[4].right = false;

			new_counter[4].x = X_align;             
			new_counter[4].y = new_counter[3].y-0.06f;           	      

			new_counter[4].w = new_counter[4].x - 0.026f;   
			new_counter[4].z = new_counter[4].y - 0.015f;

			new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
			new_counter[4].box_height = new_counter[4].height - 0.015f;	

			if(VG_MASTER_UNLOCKED == 0)
				sprintf( new_counter[5].word, "?????? SCORES");  
			else
				sprintf( new_counter[5].word, "MASTER SCORES");  
			 
			new_counter[5].alpha = 1.0f;              
			new_counter[5].id = 0; 
		      
			new_counter[5].type = 0;  // Large Font...
			new_counter[5].right = false;

			new_counter[5].x = X_align;             
			new_counter[5].y = new_counter[4].y-0.06f;           	      

			new_counter[5].w = new_counter[5].x - 0.026f;   
			new_counter[5].z = new_counter[5].y - 0.015f;

			new_counter[5].box_width = strlen(new_counter[5].word)   *  0.026f;
			new_counter[5].box_height = new_counter[5].height - 0.015f;	

			sprintf( new_counter[6].word, "BACK");  
			 
			new_counter[6].alpha = 1.0f;              
			new_counter[6].id = 0; 
		      
			new_counter[6].type = 0;  // Large Font...
			new_counter[6].right = false;

			new_counter[6].x = X_align;             
			new_counter[6].y = new_counter[5].y-0.06f;           	      

			new_counter[6].w = new_counter[6].x - 0.026f;   
			new_counter[6].z = new_counter[6].y - 0.015f;

			new_counter[6].box_width = strlen(new_counter[6].word)   *  0.026f;
			new_counter[6].box_height = new_counter[6].height - 0.015f;	

			sprintf( new_counter[12].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015-2019"); 
			 
			new_counter[12].alpha = 1.0f;                 
			new_counter[12].id = 3;        
				  
			new_counter[12].type = 1;  // Small Font...
			new_counter[12].right = false; 

			new_counter[12].x = -0.28f;                    
			new_counter[12].y = VG_BOTTOM_OPTIONS_OFFSET;         

			new_counter[12].w = new_counter[12].x - 0.026f;   
			new_counter[12].z = new_counter[12].y - 0.015f;

			new_counter[12].box_width = strlen(new_counter[12].word)   *  0.026f;
			new_counter[12].box_height = new_counter[12].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[12].word, "%c-%c MOVE  %c: SELECT %c: BACK^&RETRO ARMY LTD. 2015-2019", VG_P1_UP_KEY_DSY, VG_P1_DOWN_KEY_DSY, VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
		else
			sprintf( new_counter[12].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015-2019");
#endif
		title_sequence = 1;
		VG_1_HUD_BACK = 1;
		if(title_sequence == 1) 
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == true)
			{
				VG_reset_input();
				vg_next_episode = 0;
			//	vg_next_scene  = 2;
				//fix scoreboard
				vg_next_scene = 1;

				next_scene = true;
			}

			if(VG_1_HUDDOWN == VG_PRESSED)
			{
				vg_titlemove_sfx = true;
				VG_SELECTED++;
				if(VG_SELECTED > 5)    
					VG_SELECTED = 0;
				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false;
				VG_reset_input();
			} 

			if(VG_1_HUDUP == VG_PRESSED)
			{ 
				vg_titlemove_sfx = true;
				VG_SELECTED--; 
				if(VG_SELECTED < 0)
					VG_SELECTED = 5; 
				VG_1_HUDUP = false;
				VG_2_HUDUP = false;
				VG_reset_input();
			}

			new_counter[1].id = 0;
			new_counter[2].id = 0; 
			new_counter[3].id = 0;
			new_counter[4].id = 0;
			new_counter[5].id = 0;
			new_counter[6].id = 0;

			if(VG_SELECTED == 0) // ARCADE SCORES
			{
				new_counter[1].id = 2; 
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
				 
			} 
			if(VG_SELECTED == 1) // SURVIVAL SCORES
			{
				new_counter[2].id = 2; 
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
			}   
			if(VG_SELECTED == 2) // DUELLING SCORES
			{
				new_counter[3].id = 2; 
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
			}   
			if(VG_SELECTED == 3) // TURBO SCORES
			{
				new_counter[4].id = 2; 
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
			}   
			if(VG_SELECTED == 4) // MASTER SCORES
			{
				new_counter[5].id = 2; 
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
			}   
			if(VG_SELECTED == 5) // BACK
			{   
				new_counter[6].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
			}

		} // title_sequence == 1 

		if(title_sequence == 2)    
		{ 
			if((int)TimerGetTime() > VG_Flicker_HUD_Button_timer) 
			{
				VG_Flicker_HUD_Button_timer = (int)TimerGetTime() + 25; 

				if(VG_SELECTED == 0) // ARCADE SCORES
				{
					if(new_counter[1].id == 0) 
						new_counter[1].id = 2;
					else
						new_counter[1].id = 0;
				} 

				if(VG_SELECTED == 1) // SURVIVAL SCORES
				{
					if(new_counter[2].id == 0) 
						new_counter[2].id = 2;
					else
						new_counter[2].id = 0;
				} 
				if(VG_SELECTED == 2) // BACK
				{
					if(new_counter[3].id == 0) 
						new_counter[3].id = 2;
					else
						new_counter[3].id = 0;
				} 
				if(VG_SELECTED == 3) // BACK
				{
					if(new_counter[4].id == 0) 
						new_counter[4].id = 2;
					else
						new_counter[4].id = 0;
				} 
				if(VG_SELECTED == 4) // BACK
				{
					if(new_counter[5].id == 0) 
						new_counter[5].id = 2;
					else
						new_counter[5].id = 0;
				} 
				if(VG_SELECTED == 5) // BACK
				{
					if(new_counter[6].id == 0) 
						new_counter[6].id = 2;
					else
						new_counter[6].id = 0;
				} 

			}
			   
			if((int)TimerGetTime() > title_timer) 
			{

				if(VG_SELECTED == 0) // ARCADE SCORES
				{					  
					VG_ARCADE_TYPE = VG_ARCADE_STANDARD;

					mouseleft = false;               
					DX_SHOOT = false; 

					VG_SURVIVAL = false;

					vg_next_episode = 0;   
					vg_next_scene  = 11;

					next_scene = true;
				}
				if(VG_SELECTED == 1) // SURVIVAL SCORES
				{					  
					VG_ARCADE_TYPE = VG_ARCADE_STANDARD;

					mouseleft = false;                
					DX_SHOOT = false; 

					VG_SURVIVAL = true;

					vg_next_episode = 0;   
					vg_next_scene  = 11;

					next_scene = true;
				}
				if(VG_SELECTED == 2) // DUELLING SCORES
				{					  
					VG_ARCADE_TYPE = VG_ARCADE_DUELLING;

					mouseleft = false;                
					DX_SHOOT = false; 

					VG_SURVIVAL = false;

					vg_next_episode = 0;   
					vg_next_scene  = 11;

					next_scene = true;
				}
				if(VG_SELECTED == 3) // TURBO SCORES
				{					  
					VG_ARCADE_TYPE = VG_ARCADE_TURBO;

					mouseleft = false;                
					DX_SHOOT = false; 

					VG_SURVIVAL = false;

					vg_next_episode = 0;   
					vg_next_scene  = 11;

					next_scene = true;
				}
				if(VG_SELECTED == 4) // MASTER SCORES
				{					  
					VG_ARCADE_TYPE = VG_ARCADE_MASTER;

					mouseleft = false;                
					DX_SHOOT = false; 

					VG_SURVIVAL = false;

					vg_next_episode = 0;   
					vg_next_scene  = 11;
					 
					next_scene = true;
				}
				if(VG_SELECTED == 5) // BACK
				{
						 
					mouseleft = false;        
					DX_SHOOT = false;  
				 
					vg_next_episode = 0;   
					vg_next_scene  = 2;

					next_scene = true;
				}

			}



		}

   }   // 0 - 13

	// ******************************************************************************//
	//                             0-14  (CONTROLS)                                  //
	// ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode)  
   if(next_scene == false)
   if(episode == 0 && scene == 14)        
   {       
		 
		if(title_sequence == 0) 
		{ 
			VG_define_P1_keys = false;
			VG_SELECTED = 0;
			 
			X_align = -0.21f;    
			Y_align = +0.20f;    

			sprintf( new_counter[0].word, " CONTROLS"); 

			new_counter[0].alpha = 1.0f;        
			new_counter[0].id = 2; 
		      
			new_counter[0].type = 0;  // Large Font...
			new_counter[0].right = false; 

			new_counter[0].x = X_align+0.07f;      
			new_counter[0].y = +0.29f;  	      

			new_counter[0].w = new_counter[0].x - 0.026f;   
			new_counter[0].z = new_counter[0].y - 0.015f;

			new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
			new_counter[0].box_height = new_counter[0].height - 0.015f;	

			sprintf( new_counter[1].word, "VIEW CONTROLS"); 

			new_counter[1].alpha = 1.0f;            
			new_counter[1].id = 3;    
		      
			new_counter[1].type = 0;  // Large Font...
			new_counter[1].right = false; 
			 
			new_counter[1].x = X_align;               
			new_counter[1].y = Y_align;    	      

			new_counter[1].w = new_counter[1].x - 0.026f;   
			new_counter[1].z = new_counter[1].y - 0.015f;
			     
			new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
			new_counter[1].box_height = new_counter[1].height - 0.015f;	

			sprintf( new_counter[2].word, "REDEFINE P1 KEYS"); 

			new_counter[2].alpha = 1.0f;            
			new_counter[2].id = 3;    
		      
			new_counter[2].type = 0;  // Large Font...
			new_counter[2].right = false; 
			 
			new_counter[2].x = X_align;               
			new_counter[2].y = new_counter[1].y-0.06f;   

			new_counter[2].w = new_counter[2].x - 0.026f;   
			new_counter[2].z = new_counter[2].y - 0.015f;
			     
			new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
			new_counter[2].box_height = new_counter[2].height - 0.015f;	

			sprintf( new_counter[3].word, "REDEFINE P2 KEYS"); 

			new_counter[3].alpha = 1.0f;            
			new_counter[3].id = 3;    
		      
			new_counter[3].type = 0;  // Large Font...
			new_counter[3].right = false; 
			 
			new_counter[3].x = X_align;               
			new_counter[3].y = new_counter[2].y-0.06f;   

			new_counter[3].w = new_counter[3].x - 0.026f;   
			new_counter[3].z = new_counter[3].y - 0.015f;
			     
			new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
			new_counter[3].box_height = new_counter[3].height - 0.015f;	

			sprintf( new_counter[4].word, "BACK");  
			 
			new_counter[4].alpha = 1.0f;              
			new_counter[4].id = 0; 
		      
			new_counter[4].type = 0;  // Large Font...
			new_counter[4].right = false;

			new_counter[4].x = X_align;             
			new_counter[4].y = new_counter[3].y-0.06f;           	      

			new_counter[4].w = new_counter[4].x - 0.026f;   
			new_counter[4].z = new_counter[4].y - 0.015f;

			new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
			new_counter[4].box_height = new_counter[4].height - 0.015f;	

			sprintf( new_counter[12].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015-2019"); 
			 
			new_counter[12].alpha = 1.0f;                 
			new_counter[12].id = 3;        
				  
			new_counter[12].type = 1;  // Small Font...
			new_counter[12].right = false;

			new_counter[12].x = -0.28f;                    
			new_counter[12].y = VG_BOTTOM_OPTIONS_OFFSET;           

			new_counter[12].w = new_counter[12].x - 0.026f;   
			new_counter[12].z = new_counter[12].y - 0.015f;

			new_counter[12].box_width = strlen(new_counter[12].word)   *  0.026f;
			new_counter[12].box_height = new_counter[12].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[12].word, "%c-%c MOVE  %c: SELECT %c: BACK^&RETRO ARMY LTD. 2015-2019", VG_P1_UP_KEY_DSY, VG_P1_DOWN_KEY_DSY, VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
		else
			sprintf( new_counter[12].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015-2019");

		if(title_sequence == 1) 
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == true)
			{
				VG_reset_input();
				vg_next_episode = 0;
				vg_next_scene  = 2;

				next_scene = true;
			}

			if(VG_1_HUDDOWN == VG_PRESSED)
			{
				vg_titlemove_sfx = true;
				VG_SELECTED++;
				if(VG_SELECTED > 3)    
					VG_SELECTED = 0;
				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false;
				VG_reset_input();
			} 

			if(VG_1_HUDUP == VG_PRESSED)
			{
				vg_titlemove_sfx = true;
				VG_SELECTED--; 
				if(VG_SELECTED < 0)
					VG_SELECTED = 3; 
				VG_1_HUDUP = false;
				VG_2_HUDUP = false;
				VG_reset_input();
			}

			new_counter[1].id = 0;
			new_counter[2].id = 0; 
			new_counter[3].id = 0;
			new_counter[4].id = 0;

			if(VG_SELECTED == 0) // VIEW CONTROLS
			{
				new_counter[1].id = 2; 
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 

			} 
			if(VG_SELECTED == 1) // REDEFINE P1 KEYS
			{
				new_counter[2].id = 2; 
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
			}   
			if(VG_SELECTED == 2) // REDEFINE P2 KEYS
			{   
				new_counter[3].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
			}
			if(VG_SELECTED == 3) // BACK
			{   
				new_counter[4].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
			}
		} // title_sequence == 1 

		if(title_sequence == 2)    
		{ 
			if((int)TimerGetTime() > VG_Flicker_HUD_Button_timer) 
			{
				VG_Flicker_HUD_Button_timer = (int)TimerGetTime() + 25; 

				if(VG_SELECTED == 0) // VIEW CONTROLS
				{
					if(new_counter[1].id == 0) 
						new_counter[1].id = 2;
					else
						new_counter[1].id = 0;
				} 

				if(VG_SELECTED == 1) // REDEFINE P1 KEYS
				{
					if(new_counter[2].id == 0) 
						new_counter[2].id = 2;
					else
						new_counter[2].id = 0;
				} 
				if(VG_SELECTED == 2) // REDEFINE P2 KEYS
				{
					if(new_counter[3].id == 0) 
						new_counter[3].id = 2;
					else
						new_counter[3].id = 0;
				} 
				if(VG_SELECTED == 3) // BACK
				{
					if(new_counter[4].id == 0) 
						new_counter[4].id = 2;
					else
						new_counter[4].id = 0;
				} 
			}
			   
			if((int)TimerGetTime() > title_timer) 
			{

				if(VG_SELECTED == 0) // VIEW CONTROLS
				{					  
					mouseleft = false;               
					DX_SHOOT = false; 

					vg_next_episode = 0;   
					vg_next_scene  = 8;

					next_scene = true;
				}
				if(VG_SELECTED == 1) // REDEFINE P1 KEYS
				{					  
					mouseleft = false;                
					DX_SHOOT = false; 

					VG_define_P1_keys = true;

					vg_next_episode = 0;   
					vg_next_scene  = 15;

					next_scene = true;
				}
				if(VG_SELECTED == 2) // REDEFINE P2 KEYS
				{
						 
					mouseleft = false;        
					DX_SHOOT = false;  

					VG_define_P1_keys = false;

					vg_next_episode = 0;   
					vg_next_scene  = 15;

					next_scene = true;
				}
				if(VG_SELECTED == 3) // BACK
				{
						 
					mouseleft = false;        
					DX_SHOOT = false;  
				 
					vg_next_episode = 0;   
					vg_next_scene  = 2;

					next_scene = true;
				}

			}



		}






   }   // 0 - 14

	// ******************************************************************************//
	//                             0-15  (REDEFINE P1)                               //
	// ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode)  
   if(next_scene == false)
   if(episode == 0 && scene == 15)        
   {       
		 
		if(title_sequence == 0) 
		{ 
			VG_Flicker_HUD_Button_timer = 0;

			VG_SELECTED = 0;
			 
			X_align = -0.21f;    
			Y_align = +0.20f;  

			if(VG_define_P1_keys == true)
			{
				vg_key_check_player = 1;

				VG_P1_UP_KEY_DSY='?';
				VG_P1_DOWN_KEY_DSY='?';

				VG_P1_LEFT_KEY_DSY='?'; 
				VG_P1_RIGHT_KEY_DSY='?';   

				VG_P1_PUNCH1_KEY_DSY='?'; 
				VG_P1_PUNCH2_KEY_DSY='?'; 
				VG_P1_KICK1_KEY_DSY='?';
				VG_P1_KICK2_KEY_DSY='?'; 

				tVG_P1_UP_KEY=VG_KEY_BLANK;
				tVG_P1_DOWN_KEY=VG_KEY_BLANK;

				tVG_P1_LEFT_KEY=VG_KEY_BLANK;
				tVG_P1_RIGHT_KEY=VG_KEY_BLANK;

				tVG_P1_PUNCH1_KEY=VG_KEY_BLANK;
				tVG_P1_PUNCH2_KEY=VG_KEY_BLANK;
				tVG_P1_KICK1_KEY=VG_KEY_BLANK;
				tVG_P1_KICK2_KEY=VG_KEY_BLANK;

				tVG_P1_BLOCK_KEY=VG_KEY_BLANK;
				tVG_P1_THROW_KEY=VG_KEY_BLANK;
			}
			else
			{
				vg_key_check_player = 2;

				VG_P2_UP_KEY_DSY='?';
				VG_P2_DOWN_KEY_DSY='?';

				VG_P2_LEFT_KEY_DSY='?'; 
				VG_P2_RIGHT_KEY_DSY='?';   

				VG_P2_PUNCH1_KEY_DSY='?'; 
				VG_P2_PUNCH2_KEY_DSY='?'; 
				VG_P2_KICK1_KEY_DSY='?';
				VG_P2_KICK2_KEY_DSY='?'; 

				tVG_P2_UP_KEY=VG_KEY_BLANK;
				tVG_P2_DOWN_KEY=VG_KEY_BLANK;

				tVG_P2_LEFT_KEY=VG_KEY_BLANK;
				tVG_P2_RIGHT_KEY=VG_KEY_BLANK;

				tVG_P2_PUNCH1_KEY=VG_KEY_BLANK;
				tVG_P2_PUNCH2_KEY=VG_KEY_BLANK;
				tVG_P2_KICK1_KEY=VG_KEY_BLANK;
				tVG_P2_KICK2_KEY=VG_KEY_BLANK;

				tVG_P2_BLOCK_KEY=VG_KEY_BLANK;
				tVG_P2_THROW_KEY=VG_KEY_BLANK;
			}
			

			if(VG_define_P1_keys == true)
				sprintf( new_counter[0].word, "SET P1 KEYS"); 
			else
				sprintf( new_counter[0].word, "SET P2 KEYS"); 

			new_counter[0].alpha = 1.0f;        
			new_counter[0].id = 2; 
		      
			new_counter[0].type = 0;  // Large Font...
			new_counter[0].right = false; 

			new_counter[0].x = X_align+0.07f;      
			new_counter[0].y = +0.29f;  	      

			new_counter[0].w = new_counter[0].x - 0.026f;   
			new_counter[0].z = new_counter[0].y - 0.015f;

			new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
			new_counter[0].box_height = new_counter[0].height - 0.015f;	

			sprintf( new_counter[1].word, "  DEFINE UP KEY"); 

			new_counter[1].alpha = 1.0f;            
			new_counter[1].id = 3;    
		      
			new_counter[1].type = 0;  // Large Font...
			new_counter[1].right = false; 
			 
			new_counter[1].x = -0.22f;           
			new_counter[1].y = Y_align;    	      

			new_counter[1].w = new_counter[1].x - 0.026f;   
			new_counter[1].z = new_counter[1].y - 0.015f;
			     
			new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
			new_counter[1].box_height = new_counter[1].height - 0.015f;	

			sprintf( new_counter[2].word, "  (PRESS ANY KEY..)"); 

			new_counter[2].alpha = 1.0f;            
			new_counter[2].id = 3;    
		      
			new_counter[2].type = 0;  // Large Font...
			new_counter[2].right = false; 
			 
			new_counter[2].x = -0.28f;         
			new_counter[2].y = new_counter[1].y - 0.06f;

			new_counter[2].w = new_counter[2].x - 0.026f;   
			new_counter[2].z = new_counter[2].y - 0.015f;
			     
			new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
			new_counter[2].box_height = new_counter[2].height - 0.015f;	

			sprintf( new_counter[12].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015-2019"); 
			 
			new_counter[12].alpha = 1.0f;                 
			new_counter[12].id = 3;        
				  
			new_counter[12].type = 1;  // Small Font...
			new_counter[12].right = false;

			new_counter[12].x = -0.28f;                     
			new_counter[12].y = VG_BOTTOM_OPTIONS_OFFSET;            

			new_counter[12].w = new_counter[12].x - 0.026f;   
			new_counter[12].z = new_counter[12].y - 0.015f;

			new_counter[12].box_width = strlen(new_counter[12].word)   *  0.026f;
			new_counter[12].box_height = new_counter[12].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[12].word, "%c-%c MOVE  %c: SELECT %c: BACK^&RETRO ARMY LTD. 2015-2019", VG_P1_UP_KEY_DSY, VG_P1_DOWN_KEY_DSY, VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
		else
			sprintf( new_counter[12].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015-2019");

		if(vg_key_taken == true)
		{
			sprintf( new_counter[2].word, "(KEY ALREADY IN USE..)"); 

			if((int)TimerGetTime() > VG_Flicker_HUD_Button_timer)
			{
				VG_Flicker_HUD_Button_timer = (int)TimerGetTime() + 150;

				if(new_counter[2].id == 3) 
					new_counter[2].id = 4;
				else
					new_counter[2].id = 3;
			}
			if((int)TimerGetTime() > vg_key_taken_timer)
			{
				vg_key_taken = false;
				vg_key_taken_timer = 0;
			}
		}
		else
		{
			new_counter[2].id = 3;
			sprintf( new_counter[2].word, "  (PRESS ANY KEY..)"); 
		}

		// Define Up key...
		if(vg_key_taken == false)
		{ 

		if(title_sequence == 1) 
		{ 
			sprintf( new_counter[1].word, "  DEFINE UP KEY"); 

			VG_global_temp_key = 0;  

			/*if(VG_Scan_for_Input() == true) 
			{
				if(VG_Check_Key_Available(vg_key_check_player) == true)
				{
					if(VG_define_P1_keys == true)
						tVG_P1_UP_KEY = VG_global_temp_key;
					else
						tVG_P2_UP_KEY = VG_global_temp_key;

					vg_titlemove_sfx = true;

					VG_Put_Temps_Into_Keys();

					title_sequence++;
				}
				else
				{
					vg_key_taken = true;
					vg_key_taken_timer = (int)TimerGetTime() + 2000;
				}
			}*/

		} // title_sequence == 1 

		// Define Down key...
		if(title_sequence == 2) 
		{ 
			sprintf( new_counter[1].word, " DEFINE DOWN KEY"); 

			VG_global_temp_key = 0;

			/*if(VG_Scan_for_Input() == true)
			{
				if(VG_Check_Key_Available(vg_key_check_player) == true)
				{
					if(VG_define_P1_keys == true)
						tVG_P1_DOWN_KEY = VG_global_temp_key;
					else
						tVG_P2_DOWN_KEY = VG_global_temp_key;

					vg_titlemove_sfx = true;

					VG_Put_Temps_Into_Keys();
				
					title_sequence++;
				}
				else
				{
					vg_key_taken = true;
					vg_key_taken_timer = (int)TimerGetTime() + 2000;
				}
			}*/

		} // title_sequence == 2 

		// Define LEFT key...
		if(title_sequence == 3) 
		{ 
			sprintf( new_counter[1].word, " DEFINE LEFT KEY"); 

			VG_global_temp_key = 0;

			/*if(VG_Scan_for_Input() == true)
			{
				if(VG_Check_Key_Available(vg_key_check_player) == true)
				{
					if(VG_define_P1_keys == true)
						tVG_P1_LEFT_KEY = VG_global_temp_key;
					else
						tVG_P2_LEFT_KEY = VG_global_temp_key;

					vg_titlemove_sfx = true;

					VG_Put_Temps_Into_Keys();
				
					title_sequence++;
				}
				else
				{
					vg_key_taken = true;
					vg_key_taken_timer = (int)TimerGetTime() + 2000;
				}
			}*/

		} // title_sequence == 3 

		// Define RIGHT key...
		if(title_sequence == 4) 
		{ 
			sprintf( new_counter[1].word, "DEFINE RIGHT KEY"); 

			VG_global_temp_key = 0;

			/*if(VG_Scan_for_Input() == true)
			{
				if(VG_Check_Key_Available(vg_key_check_player) == true)
				{
					if(VG_define_P1_keys == true)
						tVG_P1_RIGHT_KEY = VG_global_temp_key;
					else
						tVG_P2_RIGHT_KEY = VG_global_temp_key;

					vg_titlemove_sfx = true;

					VG_Put_Temps_Into_Keys();
				
					title_sequence++;
				}
				else
				{
					vg_key_taken = true;
					vg_key_taken_timer = (int)TimerGetTime() + 2000;
				}
			}*/

		} // title_sequence == 4 

		// Define PUNCH1 key...
		if(title_sequence == 5) 
		{ 
			sprintf( new_counter[1].word, "DEFINE PUNCH1 KEY"); 

			VG_global_temp_key = 0;

			/*if(VG_Scan_for_Input() == true)
			{
				if(VG_Check_Key_Available(vg_key_check_player) == true)
				{
					if(VG_define_P1_keys == true)
						tVG_P1_PUNCH1_KEY = VG_global_temp_key;
					else
						tVG_P2_PUNCH1_KEY = VG_global_temp_key;

					vg_titlemove_sfx = true;

					VG_Put_Temps_Into_Keys();
				
					title_sequence++;
				}
				else
				{
					vg_key_taken = true;
					vg_key_taken_timer = (int)TimerGetTime() + 2000;
				}
			}*/ 

		} // title_sequence == 5 

		// Define PUNCH2 key...
		if(title_sequence == 6) 
		{ 
			sprintf( new_counter[1].word, "DEFINE PUNCH2 KEY"); 

			VG_global_temp_key = 0;

			/*if(VG_Scan_for_Input() == true)
			{
				if(VG_Check_Key_Available(vg_key_check_player) == true)
				{
					if(VG_define_P1_keys == true)
						tVG_P1_PUNCH2_KEY = VG_global_temp_key;
					else
						tVG_P2_PUNCH2_KEY = VG_global_temp_key;

					vg_titlemove_sfx = true;

					VG_Put_Temps_Into_Keys();
				
					title_sequence++;
				}
				else
				{
					vg_key_taken = true;
					vg_key_taken_timer = (int)TimerGetTime() + 2000;
				}
			}*/

		} // title_sequence == 6 

		// Define KICK1 key...
		if(title_sequence == 7) 
		{ 
			sprintf( new_counter[1].word, "DEFINE KICK1 KEY"); 

			VG_global_temp_key = 0;

			/*if(VG_Scan_for_Input() == true)
			{
				if(VG_Check_Key_Available(vg_key_check_player) == true)
				{
					if(VG_define_P1_keys == true)
						tVG_P1_KICK1_KEY = VG_global_temp_key;
					else
						tVG_P2_KICK1_KEY = VG_global_temp_key;

					vg_titlemove_sfx = true; 

					VG_Put_Temps_Into_Keys();
				 
					title_sequence++;
				}
				else
				{
					vg_key_taken = true;
					vg_key_taken_timer = (int)TimerGetTime() + 2000;
				}
			}*/

		} // title_sequence == 7 

		// Define KICK2 key...
		if(title_sequence == 8) 
		{ 
			sprintf( new_counter[1].word, "DEFINE KICK2 KEY"); 

			VG_global_temp_key = 0;

			/*if(VG_Scan_for_Input() == true)
			{
				if(VG_Check_Key_Available(vg_key_check_player) == true)
				{
					if(VG_define_P1_keys == true)
						tVG_P1_KICK2_KEY = VG_global_temp_key;
					else
						tVG_P2_KICK2_KEY = VG_global_temp_key; 

					vg_titlemove_sfx = true;

					VG_Put_Temps_Into_Keys();

					title_sequence++;
				}
				else
				{
					vg_key_taken = true;
					vg_key_taken_timer = (int)TimerGetTime() + 2000;
				}

			}*/

		} // title_sequence == 8 

		// Define BLOCK key...
		if(title_sequence == 9) 
		{ 
			sprintf( new_counter[1].word, "DEFINE BLOCK KEY"); 

			VG_global_temp_key = 0;

			/*if(VG_Scan_for_Input() == true)
			{
				if(VG_Check_Key_Available(vg_key_check_player) == true)
				{
					if(VG_define_P1_keys == true)
						tVG_P1_BLOCK_KEY = VG_global_temp_key;
					else
						tVG_P2_BLOCK_KEY = VG_global_temp_key; 

					vg_titlemove_sfx = true;

					VG_Put_Temps_Into_Keys(); 

					title_sequence++;
				}
				else
				{
					vg_key_taken = true;
					vg_key_taken_timer = (int)TimerGetTime() + 2000;
				}

			}*/

		} // title_sequence == 9

		// Define THROW key...
		if(title_sequence == 10) 
		{ 
			sprintf( new_counter[1].word, "DEFINE THROW KEY"); 

			VG_global_temp_key = 0;

			/*if(VG_Scan_for_Input() == true)
			{
				if(VG_Check_Key_Available(vg_key_check_player) == true)
				{
					if(VG_define_P1_keys == true)
						tVG_P1_THROW_KEY = VG_global_temp_key;
					else
						tVG_P2_THROW_KEY = VG_global_temp_key; 

					vg_titlemove_sfx = true;

					VG_Put_Temps_Into_Keys();
				 
					vg_next_episode = 0;   
					vg_next_scene  = 8;

					next_scene = true;

					title_sequence++;
				}
				else
				{
					vg_key_taken = true;
					vg_key_taken_timer = (int)TimerGetTime() + 2000;
				}

			}*/

		} // title_sequence == 10


		} // vg_key_taken = false


   }   // 0 - 15




    // ******************************************************************************//
    //                            1-0  (INTRO-COPS)                                  //
    // ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode) 
   if(next_scene == false)
   if(episode == 1 && scene == 0)        
   {        
		 
		// Pressed back key...
		if(VG_1_HUD_BACK == VG_PRESSED || VG_1_HUD_GO == VG_PRESSED)
		{
			VG_reset_input();
			vg_next_episode = 0; 
			vg_next_scene  = 1;

			fade_out = 20;
			c_fade_out = fade_out;

			next_scene = true;
		}

		if(title_sequence == 0) 
		{ 
			sprite[1].mov_x = sprite[1].x; 
			sprite[2].mov_y = sprite[2].y;
			sprite[3].mov_y = sprite[3].y;
			sprite[4].mov_x = sprite[4].x;

			sprite[1].x = sprite[0].x + sprite[0].width;
			sprite[4].x = sprite[0].x - sprite[4].width;

			sprite[2].y = sprite[0].y - sprite[2].height;
			sprite[3].y = sprite[0].y + sprite[0].height;

			title_timer = (int)TimerGetTime() + 2000;
			title_sequence++; 
		}
		if(title_sequence == 1) 
		{ 
			if(VG_slowmof != 0.0f)
				temp_speed = (0.00150f/VG_slowmof)*(float)f_rate;

			sprite[1].x -= temp_speed; 

			if(sprite[1].x < sprite[1].mov_x)
				sprite[1].x = sprite[1].mov_x;

			sprite[4].x += temp_speed; 

			if(sprite[4].x > sprite[4].mov_x)
				sprite[4].x = sprite[4].mov_x;

			if(VG_slowmof != 0.0f)
				temp_speed = (0.00075f/VG_slowmof)*(float)f_rate;

			sprite[2].y += temp_speed; 

			if(sprite[2].y > sprite[2].mov_y)
				sprite[2].y = sprite[2].mov_y;

			sprite[3].y -= temp_speed; 

			if(sprite[3].y < sprite[3].mov_y)
				sprite[3].y = sprite[3].mov_y;

		}

		if((int)TimerGetTime() > title_timer)
		{
			vg_next_episode = 1;   
			vg_next_scene    = 1; // Score sheet

			next_scene = true; 

		}


   }


    // ******************************************************************************//
    //                         1-1  (INTRO_ROBBERS)                                  //
    // ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode) 
   if(next_scene == false)
   if(episode == 1 && scene == 1)        
   {       
		 
		// Pressed back key...
		if(VG_1_HUD_BACK == VG_PRESSED || VG_1_HUD_GO == VG_PRESSED)
		{
			VG_reset_input();
			vg_next_episode = 0; 
			vg_next_scene  = 1;

			fade_out = 20;
			c_fade_out = fade_out;

			next_scene = true;
		}

		if(title_sequence == 0) 
		{ 
			sprite[1].mov_x = sprite[1].x; 
			sprite[2].mov_y = sprite[2].y;
			sprite[3].mov_y = sprite[3].y;
			sprite[4].mov_x = sprite[4].x;

			sprite[1].x = sprite[0].x + sprite[0].width;
			sprite[4].x = sprite[0].x - sprite[4].width;

			sprite[3].y = sprite[0].y - sprite[3].height;
			sprite[2].y = sprite[0].y + sprite[0].height;

			title_timer = (int)TimerGetTime() + 2000;
			title_sequence++; 
		}
		if(title_sequence == 1) 
		{ 
			if(VG_slowmof != 0.0f)
				temp_speed = (0.00150f/VG_slowmof)*(float)f_rate;

			sprite[1].x -= temp_speed; 

			if(sprite[1].x < sprite[1].mov_x)
				sprite[1].x = sprite[1].mov_x;

			sprite[4].x += temp_speed;  

			if(sprite[4].x > sprite[4].mov_x)
				sprite[4].x = sprite[4].mov_x;

			if(VG_slowmof != 0.0f)
				temp_speed = (0.00075f/VG_slowmof)*(float)f_rate;

			sprite[3].y += temp_speed; 

			if(sprite[3].y > sprite[3].mov_y)
				sprite[3].y = sprite[3].mov_y;

			sprite[2].y -= temp_speed; 
			 
			if(sprite[2].y < sprite[2].mov_y)
				sprite[2].y = sprite[2].mov_y;

		}

		if((int)TimerGetTime() > title_timer)
		{
			vg_next_episode = 1;   
			vg_next_scene    = 5; 

			next_scene = true; 

		}


   }

    // ******************************************************************************//
    //                             1-5  (INTRO-CITY)                                 //
    // ******************************************************************************//
    
   // Title Screen Stuff...    
   if(!mode)   
   if(next_scene == false)
   if(episode == 1 && scene == 5)         
   {        
		 
		// Pressed back key...
		if(VG_1_HUD_BACK == VG_PRESSED || VG_1_HUD_GO == VG_PRESSED)
		{
			VG_reset_input();
			vg_next_episode = 0; 
			vg_next_scene  = 1;

			fade_out = 20;
			c_fade_out = fade_out;

			next_scene = true;
		}

		if(title_sequence == 0) 
		{  
			
			title_timer = (int)TimerGetTime() + 1500;
			title_sequence++; 

			sprite[2].mov_x = sprite[2].x; 
			sprite[2].x -= sprite[2].width;

			start_timer = (int)TimerGetTime() + 400;
			start_sequence = 0;
		}
		      
		if(title_sequence == 1)   
		{   
			if(VG_slowmof != 0.0f)
				temp_speed = (0.00060f/VG_slowmof)*(float)f_rate;
			 
			sprite[1].y += temp_speed; 
			 
			if(sprite[1].y > sprite[0].y)
				sprite[1].y = sprite[0].y;

			if(sprite[1].y > (sprite[0].y - sprite[1].width/2) )
			{
				if(VG_slowmof != 0.0f)
					temp_speed = (0.00080f/VG_slowmof)*(float)f_rate;

				sprite[2].x += temp_speed; 

				if(sprite[2].x > sprite[2].mov_x)
					sprite[2].x = sprite[2].mov_x;
			}
			
		//	title_sequence++;  
		}

		if((int)TimerGetTime() > title_timer)
		{  
			    
			vg_next_episode = 1;     
			vg_next_scene   = 2;     
			   
			next_scene = true;  

		}
		 
		if((int)TimerGetTime() > start_timer)
		if(start_sequence == 0)
		{
			vg_siren_sfx = true;

		//	Set_Sprite(1, 1, ONCE, ANIM_SPRITE, ANIM_WALKING);

			start_sequence++;
		}


   }

 
   
    // ******************************************************************************//
    //                            1-2  (INTRO-EYES)                                  //
    // ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode) 
//   if(next_scene == false)
   if(episode == 1 && scene == 2)         
   {          
		 
		// Pressed back key...
		if(VG_1_HUD_BACK == VG_PRESSED || VG_1_HUD_GO == VG_PRESSED)
		{
			VG_reset_input();
			vg_next_episode = 0; 
			vg_next_scene  = 1;

			fade_out = 20;
			c_fade_out = fade_out;

			next_scene = true;
		}

		if(title_sequence == 0) 
		{  

			sprite[1].x = sprite[0].x - sprite[1].width;
			sprite[2].x = sprite[0].x + sprite[0].width; 

			title_timer = (int)TimerGetTime() + 3000;
			title_sequence++; 
		} 
		if(title_sequence == 1) 
		{ 
			if(VG_slowmof != 0.0f)
				temp_speed = (0.00060f/VG_slowmof)*(float)f_rate;

			sprite[1].x += temp_speed; 
			sprite[2].x -= temp_speed; 

		}

		if((int)TimerGetTime() > title_timer)
		{
			vg_next_episode = 1;   
			vg_next_scene    = 3; // Score sheet

			next_scene = true; 

		}


   }

     
    // ******************************************************************************//
    //                            1-3  (INTRO-LOAD)                                  //
    // ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode) 
   if(next_scene == false)
   if(episode == 1 && scene == 3)        
   {       
		 
		// Pressed back key...
		if(VG_1_HUD_BACK == VG_PRESSED || VG_1_HUD_GO == VG_PRESSED)
		{
			VG_reset_input();
			vg_next_episode = 0; 
			vg_next_scene  = 1;

			fade_out = 20;
			c_fade_out = fade_out;

			next_scene = true;
		}

		if(title_sequence == 0) 
		{ 

			title_timer = (int)TimerGetTime() + 800;
			title_sequence++; 

			start_timer = (int)TimerGetTime() + 400;
			start_sequence = 0; 
		} 
		if(title_sequence == 1) 
		{   
			 

		}

		if((int)TimerGetTime() > title_timer) 
		{
			vg_next_episode = 1;   
			vg_next_scene    = 4; // Score sheet

			next_scene = true;   
			 
		}   
		 
		if((int)TimerGetTime() > start_timer)
		if(start_sequence == 0)
		{

			Set_Sprite(1, 1, ONCE, ANIM_SPRITE, ANIM_WALKING);

			VG_handcuffs_sfx = true;

			start_sequence++;
		}

   }

    // ******************************************************************************//
    //                             1-4  (INTRO-SHOT)                                 //
    // ******************************************************************************//
    
   // Title Screen Stuff...    
   if(!mode)   
   if(next_scene == false)
   if(episode == 1 && scene == 4)         
   {        
		 
		// Pressed back key...
		if(VG_1_HUD_BACK == VG_PRESSED || VG_1_HUD_GO == VG_PRESSED)
		{
			VG_reset_input();
			vg_next_episode = 0; 
			vg_next_scene  = 1;

			fade_out = 20;
			c_fade_out = fade_out;

			next_scene = true;
		}

		if(title_sequence == 0) 
		{  
			
			title_timer = (int)TimerGetTime() + 800;
			title_sequence++; 

			sprite[2].type = FE_SCROLL; 

			start_timer = (int)TimerGetTime() + 400; 
			start_sequence = 0;  
		}  

		if(title_sequence == 1) 
		{ 
			temp_speed = 2.0f / 40000.0f;    

            sprite[2].u[0] += (temp_speed*(float)f_rate); 
            sprite[2].u[1] += (temp_speed*(float)f_rate);
            sprite[2].u[3] += (temp_speed*(float)f_rate);
            sprite[2].u[2] += (temp_speed*(float)f_rate);
		}

		if((int)TimerGetTime() > title_timer)
		{  
			    
			vg_next_episode = 0;     
			vg_next_scene   = 1;     
			   
			next_scene = true;  

		}
		 
		if((int)TimerGetTime() > start_timer)
		if(start_sequence == 0)
		{
			VG_pow_sfx = true;

			Set_Sprite(1, 1, ONCE, ANIM_SPRITE, ANIM_WALKING);

			start_sequence++;
		}


   }




	return(success);

} 
