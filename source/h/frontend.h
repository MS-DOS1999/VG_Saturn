#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64 
#define WIN32_LEAN_AND_MEAN  
#include <windows.h>
#endif 


extern void Refresh_Window();
extern void VG_Moveslist(int counter, int character, int index, int player);
extern void VG_Init_Story(int character);

bool Run_Frontend(int f_rate);

#define PLAY_YES_SFX  0
#define PLAY_NO_SFX  0


float vg_Y_align = 0.0f;

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

	if(!mode)  
	{ 
	//	if(sta2_played_swoosh == false)
	//		chop_sfx = true;

		if( hud[57].x <= (hud57_startX + hud[57].width/2) )
		{

			if(f_rate >= 80)            
				f_rate = 80; 
			 
			sta2_render_swipe = true;
			hud[57].alpha = 1.0f;

			temp_speed = 0.008f * (float)f_rate;       

			hud[57].x += temp_speed;

			sta2_played_swoosh = true;

		}
		else
		{
			hud[57].alpha = 0.0f;
			sta2_render_swipe = false;
		}
	}

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
	char punch;
	char punch2;
	char kick;
	char kick2;
	int vg_temp_score=0;
	int vg_index_display=0;
	int vg_index_char=0;
	int temp_mins=0;
	int temp_secs=0;
	int temp_perfects=0;
	int temp_arrests=0;
//	char name1[1024];
//	char name2[1024];


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

			sprintf( new_counter[2].word, "DISPLAY OPTIONS"); 

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

			sprintf( new_counter[3].word, "VIDEO OPTIONS"); 

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

			sprintf( new_counter[4].word, "GAME OPTIONS"); 

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

			sprintf( new_counter[5].word, "CREDITS"); 

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

			sprintf( new_counter[6].word, "CONTROLS"); 

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

			sprintf( new_counter[7].word, "SCOREBOARDS"); 

			new_counter[7].alpha = 1.0f;              
			new_counter[7].id = 0; 
		      
			new_counter[7].type = 0;  // Large Font...
			new_counter[7].right = false;
			 
			new_counter[7].x = X_align;             
			new_counter[7].y = new_counter[6].y-0.06f;          	      

			new_counter[7].w = new_counter[7].x - 0.026f;   
			new_counter[7].z = new_counter[7].y - 0.015f;

			new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
			new_counter[7].box_height = new_counter[7].height - 0.015f;	

			sprintf( new_counter[8].word, "BACK"); 

			new_counter[8].alpha = 1.0f;                
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
			new_counter[9].y = -0.33f;          

			new_counter[9].w = new_counter[9].x - 0.026f;   
			new_counter[9].z = new_counter[9].y - 0.015f;

			new_counter[9].box_width = strlen(new_counter[9].word)   *  0.026f;
			new_counter[9].box_height = new_counter[9].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[9].word, "¦-§ MOVE  Z: SELECT X: BACK^&RETRO ARMY LTD. 2015, 2016");
		else
			sprintf( new_counter[9].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015, 2016");

		if(title_sequence == 1) 
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == VG_PRESSED)
			{
				VG_reset_input();
				sta2_next_episode = 0;
				sta2_next_scene = 1;

				next_scene = true;
			}

			if(VG_1_HUDDOWN == VG_PRESSED)
			{
				click_off_sfx = true;
				VG_SELECTED++;
				if(VG_SELECTED > 7)   
					VG_SELECTED = 0;
				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false;
			} 

			if(VG_1_HUDUP == VG_PRESSED)
			{
				click_off_sfx = true; 
				VG_SELECTED--;
				if(VG_SELECTED < 0)
					VG_SELECTED = 7; 
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
					monkey_sfx = true;
				}
			}
			if(VG_SELECTED == 1) // DISPLAY OPTIONS
			{   
				new_counter[2].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					monkey_sfx = true;
				}
			}
			if(VG_SELECTED == 2) // VIDEO OPTIONS
			{   
				new_counter[3].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					monkey_sfx = true;
				}
			}
			if(VG_SELECTED == 3) // GAME OPTIONS
			{   
				new_counter[4].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					monkey_sfx = true;
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
					monkey_sfx = true;
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
					monkey_sfx = true;
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
					monkey_sfx = true;
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
					monkey_sfx = true;
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
				if(VG_SELECTED == 3) // GAME OPTIONS
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
					sta2_3_pressed = false; 
						  
					sta2_next_episode = 0;        
					sta2_next_scene = 4;

					if(PLAY_NO_SFX == 1)
						pw_no_sfx = true;

					next_scene = true;
				}
				if(VG_SELECTED == 1) // DISPLAY OPTIONS
				{ 
						 
					mouseleft = false;        
					DX_SHOOT = false;  
					sta2_3_pressed = false; 
						 
					sta2_next_episode = 0;       
					sta2_next_scene = 5;

					if(PLAY_NO_SFX == 1)
						pw_no_sfx = true;

					next_scene = true;
				}
				if(VG_SELECTED == 2) // VIDEO OPTIONS
				{ 
						 
					mouseleft = false;        
					DX_SHOOT = false;  
					sta2_3_pressed = false; 
						 
					sta2_next_episode = 0;     
					sta2_next_scene = 7;

					if(PLAY_NO_SFX == 1)
						pw_no_sfx = true;

					next_scene = true;
				}
				if(VG_SELECTED == 3) // GAME OPTIONS
				{ 
						 
					mouseleft = false;        
					DX_SHOOT = false;  
					sta2_3_pressed = false; 
						 
					sta2_next_episode = 0;     
					sta2_next_scene = 12;

					if(PLAY_NO_SFX == 1)
						pw_no_sfx = true;

					next_scene = true;
				}
				if(VG_SELECTED == 4) // CREDITS 
				{ 
						 
					mouseleft = false;        
					DX_SHOOT = false;  
					sta2_3_pressed = false;
						 
					sta2_next_episode = 0;   
					sta2_next_scene = 6;

					if(PLAY_NO_SFX == 1)
						pw_no_sfx = true;

					next_scene = true;
				}
				if(VG_SELECTED == 5) // CONTROLS 
				{ 
						 
					mouseleft = false;        
					DX_SHOOT = false;  
					sta2_3_pressed = false; 
						 
					sta2_next_episode = 0;   
					sta2_next_scene = 8;

					if(PLAY_NO_SFX == 1)
						pw_no_sfx = true;

					next_scene = true;
				}
				if(VG_SELECTED == 6) // SCOREBOARDS 
				{ 
						 
					mouseleft = false;        
					DX_SHOOT = false;  
					sta2_3_pressed = false;  
						 
					sta2_next_episode = 0;   
					sta2_next_scene = 11;

					if(PLAY_NO_SFX == 1)
						pw_no_sfx = true;

					next_scene = true;
				}
				if(VG_SELECTED == 7) // BACK
				{
						 
					mouseleft = false;        
					DX_SHOOT = false;  
					sta2_3_pressed = false;
						 
					sta2_next_episode = 0;   
					sta2_next_scene = 1;

					if(PLAY_NO_SFX == 1)
						pw_no_sfx = true;

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

			sprintf( new_counter[7].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015, 2016");
			 
			new_counter[7].alpha = 1.0f;                 
			new_counter[7].id = 3;        
				  
			new_counter[7].type = 1;  // Small Font...
			new_counter[7].right = false;

			new_counter[7].x = -0.28f;                    
			new_counter[7].y = -0.33f;          

			new_counter[7].w = new_counter[7].x - 0.026f;   
			new_counter[7].z = new_counter[7].y - 0.015f;

			new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
			new_counter[7].box_height = new_counter[7].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[7].word, "¦-§ MOVE  Z: SELECT X: BACK^&RETRO ARMY LTD. 2015, 2016");
		else
			sprintf( new_counter[7].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015, 2016");

		if(title_sequence == 1) 
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == VG_PRESSED)
			{
				VG_reset_input();
				sta2_next_episode = 0;
				sta2_next_scene = 2;

				next_scene = true;
			}

			if(VG_1_HUDDOWN == VG_PRESSED)
			{
				click_off_sfx = true;
				VG_SELECTED++;
				if(VG_SELECTED > 2)   
					VG_SELECTED = 0; 
				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false;
			} 

			if(VG_1_HUDUP == VG_PRESSED)
			{
				click_off_sfx = true;
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

				sprintf( new_counter[1].word, "MUSIC VOLUME ¢-¤");

				if(VG_1_HUDLEFT == VG_PRESSED) 
				{
					VG_1_HUDLEFT = false;
					sprite[3].width -= 0.02f;
                    
					if(sprite[3].box_width != 0.0)
						music_volume = sprite[3].width / sprite[3].box_width;
                        
					if(sprite[3].width < sprite[3].box_width/25)
					{
						sprite[3].width = 0.0f;
						music_volume = 0.0f;					   
					}                            

					click_off_sfx = true; 
    
					update_title = true;      
					create_option = true;  

				}
				if(VG_1_HUDRIGHT == VG_PRESSED)
				{      
					VG_1_HUDRIGHT = false;
					sprite[3].width += 0.02f;
                    
					if(sprite[3].width > sprite[3].box_width)
						sprite[3].width = sprite[3].box_width;

					if(sprite[3].box_width != 0.0)
						music_volume = sprite[3].width / sprite[3].box_width;

					click_off_sfx = true;

					update_title = true;      
					create_option = true; 

				}
			} 
			if(VG_SELECTED == 1) // SOUND VOLUME
			{    
				new_counter[2].id = 2;

				sprintf( new_counter[2].word, "SOUND VOLUME ¢-¤");

				if(VG_1_HUDLEFT == VG_PRESSED) 
				{  
					VG_1_HUDLEFT = false;
					sprite[4].width -= 0.02f;
                    
					if(sprite[4].box_width != 0.0)
						sfx_volume = sprite[4].width / sprite[4].box_width;
                        
					if(sprite[4].width < sprite[4].box_width/25)
					{
						sprite[4].width = 0.0f;
						sfx_volume = 0.0f;					   
					}                            

					click_off_sfx = true;
					 
					update_title = true;        
					create_option = true;  

				}
				if(VG_1_HUDRIGHT == VG_PRESSED)
				{ 
					VG_1_HUDRIGHT = false;
					sprite[4].width += 0.02f;
                    
					if(sprite[4].width > sprite[4].box_width)
						sprite[4].width = sprite[4].box_width;

					if(sprite[4].box_width != 0.0)
						sfx_volume = sprite[4].width / sprite[4].box_width;

					click_off_sfx = true;

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
					monkey_sfx = true;
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
					sta2_3_pressed = false;
						 
					sta2_next_episode = 0;   
					sta2_next_scene = 2;

					if(PLAY_NO_SFX == 1)
						pw_no_sfx = true;

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

                sprintf(string_value,"%i x %i^", RES_Width[i], RES_Height[i]);
                strcat(new_counter[i].word, string_value);  

				new_counter[i].alpha = 1.0f;        
				new_counter[i].id = 0; 

				new_counter[i].type = 0;  // Large Font...
				new_counter[i].right = false;

				if(i >= 9) 
					new_counter[i].x = 0.12f;                       
				else
					new_counter[i].x = -0.35f;

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


			sprintf( new_counter[20].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015, 2016");
			 
			new_counter[20].alpha = 1.0f;                 
			new_counter[20].id = 3;        
				  
			new_counter[20].type = 1;  // Small Font...
			new_counter[20].right = false;

			new_counter[20].x = -0.28f;                    
			new_counter[20].y = -0.33f;          

			new_counter[20].w = new_counter[20].x - 0.026f;   
			new_counter[20].z = new_counter[20].y - 0.015f;

			new_counter[20].box_width = strlen(new_counter[20].word)   *  0.026f;
			new_counter[20].box_height = new_counter[20].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[20].word, "¦-§ MOVE  Z: SELECT X: BACK^&RETRO ARMY LTD. 2015, 2016");
		else
			sprintf( new_counter[20].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015, 2016");

		if(title_sequence == 1)  
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == true)
			{
				VG_reset_input();
				sta2_next_episode = 0;
				sta2_next_scene = 2;

				next_scene = true;
			}

			if(VG_1_HUDDOWN == VG_PRESSED)
			{
				click_off_sfx = true;
				VG_SELECTED++;
				if(VG_SELECTED > 18)    
					VG_SELECTED = 0;
				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false;
			} 

			if(VG_1_HUDUP == VG_PRESSED)
			{
				click_off_sfx = true;
				VG_SELECTED--;
				if(VG_SELECTED < 0)
					VG_SELECTED = 18; 
				VG_1_HUDUP = false;
				VG_2_HUDUP = false;
			}
			 
			for(int i=0;i<19;i++)   
			{ 
				  
				new_counter[i].id = 0;    
				 
				if((RES_Width[i] > MAX_horizontal || RES_Height[i] > MAX_vertical))
					new_counter[i].id = 4;

				if(VG_SELECTED == i) // SOUND OPTIONS
				{   

					if(new_counter[i].id != 4)
					if(VG_1_HUD_GO == true)
					{
						VG_reset_input();
						title_sequence++;
						title_timer = (int)TimerGetTime() + 500;
						monkey_sfx = true;
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
					if(!(RES_Width[i] > MAX_horizontal || RES_Height[i] > MAX_vertical))
				//	if(!(new_sc_width == RES_Width[i] && new_sc_height == RES_Height[i]))
					{
						new_sc_width = RES_Width[i]; 
						new_sc_height = RES_Height[i];  

						changed_video = true; 
						create_option = true; 

						Refresh_Window();

					}  
				}

				if(VG_SELECTED == 18) // BACK
				{
						 
					mouseleft = false;        
					DX_SHOOT = false;  
					sta2_3_pressed = false;
						 
					sta2_next_episode = 0;   
					sta2_next_scene = 2;

					if(PLAY_NO_SFX == 1)
						pw_no_sfx = true;

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
			Y_align = +0.20f;    

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

			sprintf( new_counter[3].word, "       MUSIC BY^      BOSSFIGHT^   TRUONG-SON NGUYEN"); 
			 
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



			sprintf( new_counter[7].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015, 2016"); 
			 
			new_counter[7].alpha = 1.0f;                 
			new_counter[7].id = 3;        
				  
			new_counter[7].type = 1;  // Small Font...
			new_counter[7].right = false;

			new_counter[7].x = -0.28f;                    
			new_counter[7].y = -0.33f;          

			new_counter[7].w = new_counter[7].x - 0.026f;   
			new_counter[7].z = new_counter[7].y - 0.015f;

			new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
			new_counter[7].box_height = new_counter[7].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[7].word, "¦-§ MOVE  Z: SELECT X: BACK^&RETRO ARMY LTD. 2015, 2016");
		else
			sprintf( new_counter[7].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015, 2016");

		if(title_sequence == 1) 
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == true)
			{
				VG_reset_input();
				sta2_next_episode = 0;
				sta2_next_scene = 2;

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
					monkey_sfx = true;
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
					sta2_3_pressed = false;
						 
					sta2_next_episode = 0;   
					sta2_next_scene = 2;

					if(PLAY_NO_SFX == 1)
						pw_no_sfx = true;

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

			sprintf( new_counter[1].word, "WINDOWED"); 

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

			sprintf( new_counter[2].word, "FULLSCREEN"); 

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

			sprintf( new_counter[3].word, "BACK");  
			 
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

			sprintf( new_counter[7].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015, 2016"); 
			 
			new_counter[7].alpha = 1.0f;                 
			new_counter[7].id = 3;        
				  
			new_counter[7].type = 1;  // Small Font...
			new_counter[7].right = false;

			new_counter[7].x = -0.28f;                    
			new_counter[7].y = -0.33f;          

			new_counter[7].w = new_counter[7].x - 0.026f;   
			new_counter[7].z = new_counter[7].y - 0.015f;

			new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
			new_counter[7].box_height = new_counter[7].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[7].word, "¦-§ MOVE  Z: SELECT X: BACK^&RETRO ARMY LTD. 2015, 2016");
		else
			sprintf( new_counter[7].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015, 2016");

		if(title_sequence == 1) 
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == true)
			{
				VG_reset_input();
				sta2_next_episode = 0;
				sta2_next_scene = 2;

				next_scene = true;
			}

			if(VG_1_HUDDOWN == VG_PRESSED)
			{
				click_off_sfx = true;
				VG_SELECTED++;
				if(VG_SELECTED > 2)    
					VG_SELECTED = 0;
				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false;
			} 

			if(VG_1_HUDUP == VG_PRESSED)
			{
				click_off_sfx = true;
				VG_SELECTED--;
				if(VG_SELECTED < 0)
					VG_SELECTED = 2; 
				VG_1_HUDUP = false;
				VG_2_HUDUP = false;
			}

			new_counter[1].id = 0;
			new_counter[2].id = 0; 
			new_counter[3].id = 0;

			if(VG_SELECTED == 0) // WINDOWED
			{
				new_counter[1].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					monkey_sfx = true;
				}   
			} 
			if(VG_SELECTED == 1) // FULLSCREEN
			{
				new_counter[2].id = 2;
				if(VG_1_HUD_GO == true)
				{
					VG_reset_input();
					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					monkey_sfx = true;
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
					monkey_sfx = true;
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
				if(VG_SELECTED == 2) // BACK
				{
					if(new_counter[3].id == 0) 
						new_counter[3].id = 2;
					else
						new_counter[3].id = 0;
				} 

			}
			   
			if((int)TimerGetTime() > title_timer) 
			{

				if(VG_SELECTED == 0) // WINDOWED
				{					  
					mouseleft = false;               
					DX_SHOOT = false;   

                    fullscreen = false;
                    stamp_sfx = true;
                    changed_video = true;  
                    create_option = true;    

					Refresh_Window();
				}
				if(VG_SELECTED == 1) // FULLSCREEN
				{					  
					mouseleft = false;                
					DX_SHOOT = false;    
					      
                    fullscreen = true;
                    stamp_sfx = true;
                    changed_video = true;
                    create_option = true;        

					Refresh_Window();
				}
				if(VG_SELECTED == 2) // BACK
				{
						 
					mouseleft = false;        
					DX_SHOOT = false;  
					sta2_3_pressed = false;
						 
					sta2_next_episode = 0;   
					sta2_next_scene = 2;

					if(PLAY_NO_SFX == 1)
						pw_no_sfx = true;

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

			sprintf( new_counter[1].word, "P1^¦-§-¢-¤^Arrow keys^^"); 
			 
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
			sprintf( new_counter[2].word, "^£  ¥  À  Á"); 

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
			 
			sprintf( new_counter[3].word, "^ Z  X  C  V^ ÷  ø  ù  ú"); 

			new_counter[3].alpha = 1.0f;             
			new_counter[3].id = 3;  
		      
			new_counter[3].type = 1;  // Large Font... 
			new_counter[3].right = false;
			  
			new_counter[3].x = X_align;              
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


			sprintf( new_counter[5].word, "P2^¦-§-¢-¤^ W  A  S  D^^"); 
			 
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
			sprintf( new_counter[6].word, "^£  ¥  À  Á"); 

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
			 
			sprintf( new_counter[7].word, "^ J  K  N  M^ ÷  ø  ù  ú"); 

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

			sprintf( new_counter[9].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015, 2016"); 
			 
			new_counter[9].alpha = 1.0f;                 
			new_counter[9].id = 3;        
				  
			new_counter[9].type = 1;  // Small Font...
			new_counter[9].right = false;
			 
			new_counter[9].x = -0.28f;                    
			new_counter[9].y = -0.33f;          

			new_counter[9].w = new_counter[9].x - 0.026f;   
			new_counter[9].z = new_counter[9].y - 0.015f;

			new_counter[9].box_width = strlen(new_counter[9].word)   *  0.026f;
			new_counter[9].box_height = new_counter[9].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[9].word, "¦-§ MOVE  Z: SELECT X: BACK^&RETRO ARMY LTD. 2015, 2016");
		else
			sprintf( new_counter[9].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015, 2016");

		if(title_sequence == 1) 
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == true)
			{
				VG_reset_input();
				sta2_next_episode = 0;
				sta2_next_scene = 2;

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
					monkey_sfx = true;
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
					sta2_3_pressed = false;
						 
					sta2_next_episode = 0;   
					sta2_next_scene = 2;

					if(PLAY_NO_SFX == 1)
						pw_no_sfx = true;

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
		if(VG_P1_USING == VG_KEYBOARD)
		{
			punch  = 'Z';
			punch2 = 'X';
			kick   = 'C';
			kick2  = 'V';
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
				sprintf( new_counter[1].word, "AGE: 28^JOB: DETECTIVE^LIKES: SOJU^^¦-§-¢-¤^Arrow keys^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_SIU)
				sprintf( new_counter[1].word, "AGE: 22^JOB: SUBWAY COP^LIKES: TRAINS^^¦-§-¢-¤^Arrow keys^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_MINSO)
				sprintf( new_counter[1].word, "AGE: 26^JOB: TRAFFIC COP^LIKES: KIMCHI^^¦-§-¢-¤^Arrow keys^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_REESE)
				sprintf( new_counter[1].word, "AGE: ??^JOB: SECRET AGENT^LIKES: ALIENS^^¦-§-¢-¤^Arrow keys^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_YOHAN)
				sprintf( new_counter[1].word, "AGE: 17^JOB: TERRORIST^LIKES: BOMBS^^¦-§-¢-¤^Arrow keys^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_JAE)
				sprintf( new_counter[1].word, "AGE: 32^JOB: YAKUZA^LIKES: DANCING^^¦-§-¢-¤^Arrow keys^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_GUN)
				sprintf( new_counter[1].word, "AGE: 46^JOB: CONVICT^LIKES: MAHJONG^^¦-§-¢-¤^Arrow keys^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
			if(VG_1_CHARACTER == VG_HYUK)
				sprintf( new_counter[1].word, "AGE: 22^JOB: BANK ROBBER^LIKES: MONEY^^¦-§-¢-¤^Arrow keys^£  ¥  À  Á^ %c  %c  %c  %c", punch, punch2, kick, kick2); 
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
#endif
		}

		VG_Moveslist(2, VG_1_CHARACTER, 0, 1);
		VG_Moveslist(3, VG_1_CHARACTER, 1, 1);
		VG_Moveslist(4, VG_1_CHARACTER, 2, 1);

		if(title_sequence == 0) 
		{ 

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
				new_counter[7].y = -0.33f;          

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
			sprintf( new_counter[7].word, "^     Z: NEXT X: BACK^"); 
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

				sta2_next_episode = 6;
				sta2_next_scene = 1;  
				  
				next_scene = true; 
			}
			if(VG_1_HUD_GO == true
			) // Go to map screen...   // || (int)TimerGetTime() > title_timer
			{ 
				VG_reset_input(); 

				mouseleft = false;        
				DX_SHOOT = false;  
				sta2_3_pressed = false; 

				if(VG_TRAINING == true)
				{
					VG_IS_VERSUS_SCREEN = true; 
      
					VG_2_CHARACTER = VG_TRAINER;    
						  
					VG_BACKGROUND = VG_TRAINER; 

					sta2_next_episode = 0;         
					sta2_next_scene = 10;
				}
				else 
				{
					if(VG_GAME_MODE == VG_STORY_MODE)
					{
						sta2_next_episode = 6;        
						sta2_next_scene = 1; 

						VG_Init_Story(VG_1_CHARACTER);
					}
					else
					{
						sta2_next_episode = 0;        
						sta2_next_scene = 10; 
					}
				}

				if(PLAY_NO_SFX == 1)
					pw_no_sfx = true;

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
		if(VG_P1_USING == VG_KEYBOARD)
		{
			punch  = 'Z';
			punch2 = 'X';
			kick   = 'C';
			kick2  = 'V';
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
				sprintf( new_counter[1].word, "HANDCUFFS^TO HANDCUFF AN OPPONENT^PRESS THE %c + %c KEYS^^TO ARREST AN OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", punch, punch2);
			if(VG_1_CHARACTER == VG_SIU)
				sprintf( new_counter[1].word, "HANDCUFFS^TO HANDCUFF AN OPPONENT^PRESS THE %c + %c KEYS^^TO ARREST AN OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", punch, punch2);
			if(VG_1_CHARACTER == VG_MINSO)
				sprintf( new_counter[1].word, "HANDCUFFS^TO HANDCUFF AN OPPONENT^PRESS THE %c + %c KEYS^^TO ARREST AN OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", punch, punch2);
			if(VG_1_CHARACTER == VG_REESE)
				sprintf( new_counter[1].word, "HANDCUFFS^TO HANDCUFF AN OPPONENT^PRESS THE %c + %c KEYS^^TO ARREST AN OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", punch, punch2);
			if(VG_1_CHARACTER == VG_YOHAN)
				sprintf( new_counter[1].word, "STICKY BOMB^TO BOMB AN OPPONENT^PRESS THE %c + %c KEYS^TO ATTACH A BOMB^^DEFEAT THEM WITH^THE BOMB^TO WASTE THEM!", punch, punch2);
			if(VG_1_CHARACTER == VG_JAE)
				sprintf( new_counter[1].word, "BACK-STAB^TO KNIFE AN OPPONENT^PRESS THE %c + %c KEYS^^DEFEAT THEM WHILST^THEY$RE DIZZY^TO WASTE THEM!", punch, punch2);  
			if(VG_1_CHARACTER == VG_GUN)
				sprintf( new_counter[1].word, "BACK-STAB^TO KNIFE AN OPPONENT^PRESS THE %c + %c KEYS^^DEFEAT THEM WHILST^THEY$RE DIZZY^TO WASTE THEM!", punch, punch2); 
			if(VG_1_CHARACTER == VG_HYUK)
				sprintf( new_counter[1].word, "STICKY GRENADE^TO BOMB AN OPPONENT^PRESS THE %c + %c KEYS^TO ATTACH A GRENADE^^DEFEAT THEM WITH^THE GRENADE^TO WASTE THEM!", punch, punch2);
		}  
		else 
		{ 
			if(VG_1_CHARACTER == VG_GYEONG)    
				sprintf( new_counter[1].word, "HANDCUFFS^TO HANDCUFF AN OPPONENT^PRESS THE %c + %c BUTTONS^^TO ARREST AN OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", punch, punch2);
			if(VG_1_CHARACTER == VG_SIU)
				sprintf( new_counter[1].word, "HANDCUFFS^TO HANDCUFF AN OPPONENT^PRESS THE %c + %c BUTTONS^^TO ARREST AN OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", punch, punch2);
			if(VG_1_CHARACTER == VG_MINSO)
				sprintf( new_counter[1].word, "HANDCUFFS^TO HANDCUFF AN OPPONENT^PRESS THE %c + %c BUTTONS^^TO ARREST AN OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", punch, punch2);
			if(VG_1_CHARACTER == VG_REESE)
				sprintf( new_counter[1].word, "HANDCUFFS^TO HANDCUFF AN OPPONENT^PRESS THE %c + %c BUTTONS^^TO ARREST AN OPPONENT^DEFEAT THEM WHILST^THEY$RE HANDCUFFED!", punch, punch2);
			if(VG_1_CHARACTER == VG_YOHAN)
				sprintf( new_counter[1].word, "STICKY BOMB^TO BOMB AN OPPONENT^PRESS THE %c + %c BUTTONS^TO ATTACH A BOMB^^DEFEAT THEM WITH^THE BOMB^TO WASTE THEM!", punch, punch2);
			if(VG_1_CHARACTER == VG_JAE)
				sprintf( new_counter[1].word, "BACK-STAB^TO KNIFE AN OPPONENT^PRESS THE %c + %c BUTTONS^^DEFEAT THEM WHILST^THEY$RE DIZZY^TO WASTE THEM!", punch, punch2);
			if(VG_1_CHARACTER == VG_GUN)
				sprintf( new_counter[1].word, "BACK-STAB^TO KNIFE AN OPPONENT^PRESS THE %c + %c BUTTONS^^DEFEAT THEM WHILST^THEY$RE DIZZY^TO WASTE THEM!", punch, punch2);
			if(VG_1_CHARACTER == VG_HYUK)
				sprintf( new_counter[1].word, "STICKY GRENADE^TO BOMB AN OPPONENT^PRESS THE %c + %c BUTTONS^TO ATTACH A GRENADE^^DEFEAT THEM WITH^THE GRENADE^TO WASTE THEM!", punch, punch2);

		} 

		VG_Moveslist(2, VG_1_CHARACTER, 0, 1);
		VG_Moveslist(3, VG_1_CHARACTER, 1, 1);
		VG_Moveslist(4, VG_1_CHARACTER, 2, 1);

		if(title_sequence == 0) 
		{ 

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
				new_counter[7].y = -0.33f;          

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
			sprintf( new_counter[7].word, "^     Z: NEXT X: BACK^"); 
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

				sta2_next_episode = 6;
				sta2_next_scene = 1;    
				  
				next_scene = true; 
			}
			if(VG_1_HUD_GO == true
			) // Go to map screen...  // || (int)TimerGetTime() > title_timer
			{ 
				VG_reset_input(); 

				mouseleft = false;        
				DX_SHOOT = false;  
				sta2_3_pressed = false; 

				if(VG_TRAINING == true)
				{
					VG_IS_VERSUS_SCREEN = true;
      
					VG_2_CHARACTER = VG_TRAINER;    
						  
					VG_BACKGROUND = VG_TRAINER; 

					sta2_next_episode = 6;        
					sta2_next_scene = 0;
				}
				else
				{
					sta2_next_episode = 6;        
					sta2_next_scene = 1; 
				}

				if(PLAY_NO_SFX == 1)
					pw_no_sfx = true;

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

		if(title_sequence == 0)  
		{  

			#if IS_FULL_STEAM == 1 
			 
				if (STEAM_ACTIVE == true) 
				{
					for(int i = 0;i< 100;i++)
						g_SteamLeaderboards_finalscore->m_leaderboardEntries[i].m_nScore = 0;

					g_SteamLeaderboards_finalscore->DownloadScores(); 

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
			 
			sprintf( new_counter[1].word, "RANK  NAME               RND  ¿+ö    TIME"); 
			  
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
				new_counter[2].y = -0.33f;          

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
			vg_Y_align -= 0.00020f*(float)f_rate; // +0.24f  
		}
		else   
		{ 
			if(vg_Y_align < 1.00f) 
			{
				vg_Y_align -= 0.00030f*(float)f_rate; // +0.24f  
			}
			else
			{ 
				if(vg_Y_align < 2.00f)
				{
					vg_Y_align -= 0.00040f*(float)f_rate; // +0.24f  
				}
				else
					vg_Y_align -= 0.0006f*(float)f_rate; // +0.24f  
			}

		} 

		if(vg_Y_align < 0.24f)  
			vg_Y_align = 0.24f;    

		vg_index_display = 3;  

		temp_Y_align = vg_Y_align;

		for(int i = 1;i<100;i++)     
		{
			    
			if((i-1) >= 0)   
			{
				sprintf( new_counter[vg_index_display].word, "%iÐ    %.18s^", i, "EMPTY" ); 

				#if IS_FULL_STEAM == 1 
				if(STEAM_ACTIVE == true)
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
			{
				   
			if(vg_temp_score > 0)             
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

/*		#if IS_FULL_STEAM == 1  
		if(STEAM_ACTIVE == true)  
		if( (i-1) >= 0)
 		if((int)TimerGetTime() > flash1_helptext_timer)   
		{
			flash1_helptext_timer = (int)TimerGetTime() + 50; 

			sprintf( name1, "%.18s^", SteamFriends()->GetPersonaName()); 
			sprintf( name2, "%.18s^", SteamFriends()->GetFriendPersonaName(g_SteamLeaderboards_finalscore->m_leaderboardEntries[i-1].m_steamIDUser));

			if( strcmp( name1, name2 ) == 0) 
			{ 

				if(new_counter[vg_index_display].alpha == 0.0f)
				{
					new_counter[vg_index_display].alpha = 1.0f; 
					new_counter[vg_index_display-1].alpha = 1.0f;
				}
				else
				{
					new_counter[vg_index_display].alpha = 0.0f;
					new_counter[vg_index_display-1].alpha = 0.0f;
				}
			}
		}
		#endif*/

 		if((int)TimerGetTime() > flash_helptext_timer)   
		{
			if(new_counter[2].alpha == 0.0f)
			{
				flash_helptext_timer = (int)TimerGetTime() + 500;
				new_counter[2].alpha = 1.0f;

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
				new_counter[2].alpha = 0.0f;

				if(STEAM_ACTIVE == false)
				{
					new_counter[0].x = -0.12f;
					new_counter[0].id = 2;
					sprintf( new_counter[0].word, "TOP PLAYERS^");
				}
			}
		}

		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[2].word, "^     Z: NEXT X: BACK^"); 
		else
			sprintf( new_counter[2].word, "^     ÷: NEXT ø: BACK^");

		if(title_sequence == 1)    
		{ 
			// Pressed back key...
			if(VG_1_HUD_BACK == true) 
			{ 
				VG_reset_input();

				sta2_next_episode = 0;
				sta2_next_scene = 1;    
				  
				next_scene = true; 
			}
			if(VG_1_HUD_GO == true
			) // Go to map screen...  // || (int)TimerGetTime() > title_timer
			{ 
				VG_reset_input(); 

				mouseleft = false;        
				DX_SHOOT = false;  

				sta2_next_episode = 0;        
				sta2_next_scene = 1; 

				if(PLAY_NO_SFX == 1)
					pw_no_sfx = true;

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
			    
			X_align = -0.26f;      
			Y_align = +0.20f;    

			sprintf( new_counter[0].word, "  GAME OPTIONS"); 

			new_counter[0].alpha = 1.0f;        
			new_counter[0].id = 2; 
		      
			new_counter[0].type = 0;  // Large Font...
			new_counter[0].right = false; 

			new_counter[0].x = -0.20f;   
			new_counter[0].y = +0.29f;  	      

			new_counter[0].w = new_counter[0].x - 0.026f;   
			new_counter[0].z = new_counter[0].y - 0.015f;

			new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
			new_counter[0].box_height = new_counter[0].height - 0.015f;	

			sprintf( new_counter[1].word, "");  
			 
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


			sprintf( new_counter[2].word, "");  
			 
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

			sprintf( new_counter[9].word, "¦-§ MOVE  Z: SELECT ESC: BACK^&RETRO ARMY LTD. 2015, 2016"); 
			 
			new_counter[9].alpha = 1.0f;                 
			new_counter[9].id = 3;        
				  
			new_counter[9].type = 1;  // Small Font...
			new_counter[9].right = false;
			 
			new_counter[9].x = -0.28f;                    
			new_counter[9].y = -0.33f;          

			new_counter[9].w = new_counter[9].x - 0.026f;   
			new_counter[9].z = new_counter[9].y - 0.015f;

			new_counter[9].box_width = strlen(new_counter[9].word)   *  0.026f;
			new_counter[9].box_height = new_counter[9].height - 0.015f;	

			 title_sequence++;
		} 
			 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[9].word, "¦-§ MOVE  Z: SELECT X: BACK^&RETRO ARMY LTD. 2015, 2016");
		else
			sprintf( new_counter[9].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015, 2016");

		if(title_sequence == 1) 
		{ 
			   
			// Pressed back key...
			if(VG_1_HUD_BACK == true)
			{
				VG_reset_input();
				sta2_next_episode = 0;
				sta2_next_scene = 2;

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
					monkey_sfx = true;
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
					sta2_3_pressed = false;
						 
					sta2_next_episode = 0;   
					sta2_next_scene = 2;

					if(PLAY_NO_SFX == 1)
						pw_no_sfx = true;

					next_scene = true;
				}

			}



		}

   }     






	return(success);

} 
