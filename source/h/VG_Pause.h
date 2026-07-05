#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64  
#define WIN32_LEAN_AND_MEAN    
#include <windows.h> 
#endif    

extern void VG_Moveslist(int counter, int character, int index, int player);
extern void Animate(int loop, int type);
extern void VG_Help_Story_Minso(int scene, int index);
extern void VG_Help_Story_Gyeong(int scene, int index);
extern void VG_Help_Story_Hyuk(int scene, int index); 
extern void VG_Help_Story_Jae(int scene, int index);

extern void VG_Help_Story_Reese(int scene, int index);
extern void VG_Help_Story_Siu(int scene, int index);
extern void VG_Help_Story_Yohan(int scene, int index);
extern void VG_Help_Story_Gun(int scene, int index);

int flash_pause_timer = 0;

void VG_Pause()
{
	float X_align = 0.0f;
	float Y_align = 0.0f;

	if(episode == 5)    
	{    
		X_align = -0.17f;    
		
		sprintf( new_counter[10].word, "GAME PAUSED"); 

		if(VG_GAME_MODE == VG_STORY_MODE)
			sprintf( new_counter[10].word, "OBJECTIVES"); 
         
		new_counter[10].id = 2;  
		       
		new_counter[10].type = 0;  // Large Font...
		new_counter[10].right = false; 
		 
		new_counter[10].x = X_align+0.03f;       
		new_counter[10].y = +0.24f;  	      

		new_counter[10].w = new_counter[10].x - 0.026f;   
		new_counter[10].z = new_counter[10].y - 0.015f;

		new_counter[10].box_width = strlen(new_counter[10].word)   *  0.026f;
		new_counter[10].box_height = new_counter[10].height - 0.015f;
         
		new_counter[11].id = 2;     
		       
		new_counter[11].type = 1;  // Large Font...  
		new_counter[11].right = false;   

		new_counter[11].x = -0.30f;             
		new_counter[11].y = +0.17f;     	       

		new_counter[11].w = new_counter[11].x - 0.026f;   
		new_counter[11].z = new_counter[11].y - 0.015f;
			     
		new_counter[11].box_width = strlen(new_counter[11].word)   *  0.026f;
		new_counter[11].box_height = new_counter[11].height - 0.015f;	

		if(VG_PLAYER_1_PAUSED == true)
			VG_Moveslist(11, VG_1_CHARACTER, 0, 1);
		else
			VG_Moveslist(11, VG_2_CHARACTER, 0, 2);
         
		if(VG_GAME_MODE == VG_STORY_MODE)
		{
			if(VG_1_CHARACTER == VG_MINSO)
				VG_Help_Story_Minso(VG_CURRENT_STORY_SCENE, 11);
			if(VG_1_CHARACTER == VG_GYEONG)
				VG_Help_Story_Gyeong(VG_CURRENT_STORY_SCENE, 11);
			if(VG_1_CHARACTER == VG_HYUK)
				VG_Help_Story_Hyuk(VG_CURRENT_STORY_SCENE, 11);
			if(VG_1_CHARACTER == VG_JAE)
				VG_Help_Story_Jae(VG_CURRENT_STORY_SCENE, 11);

			if(VG_1_CHARACTER == VG_REESE)
				VG_Help_Story_Reese(VG_CURRENT_STORY_SCENE, 11);
			if(VG_1_CHARACTER == VG_SIU)
				VG_Help_Story_Siu(VG_CURRENT_STORY_SCENE, 11);
			if(VG_1_CHARACTER == VG_YOHAN)
				VG_Help_Story_Yohan(VG_CURRENT_STORY_SCENE, 11);
			if(VG_1_CHARACTER == VG_GUN)
				VG_Help_Story_Gun(VG_CURRENT_STORY_SCENE, 11);
		}

		new_counter[12].id = 2;     
		       
		new_counter[12].type = 1;  // Large Font...  
		new_counter[12].right = false;   

		new_counter[12].x = -0.30f;             
		new_counter[12].y = +0.07f;     	        

		new_counter[12].w = new_counter[12].x - 0.026f;   
		new_counter[12].z = new_counter[12].y - 0.015f;
			     
		new_counter[12].box_width = strlen(new_counter[12].word)   *  0.026f;
		new_counter[12].box_height = new_counter[12].height - 0.015f;	

		if(VG_PLAYER_1_PAUSED == true)
			VG_Moveslist(12, VG_1_CHARACTER, 1, 1);
		else
			VG_Moveslist(12, VG_2_CHARACTER, 1, 2);

		new_counter[13].id = 2;     
		       
		new_counter[13].type = 1;  // Large Font...  
		new_counter[13].right = false;   

		new_counter[13].x = -0.30f;              
		new_counter[13].y = -0.03f;     	         

		new_counter[13].w = new_counter[13].x - 0.026f;   
		new_counter[13].z = new_counter[13].y - 0.015f;
			     
		new_counter[13].box_width = strlen(new_counter[13].word)   *  0.026f;
		new_counter[13].box_height = new_counter[13].height - 0.015f;	

		if(VG_PLAYER_1_PAUSED == true)
			VG_Moveslist(13, VG_1_CHARACTER, 2, 1);
		else
			VG_Moveslist(13, VG_2_CHARACTER, 2, 2);

		new_counter[17].id = 2;     
		new_counter[17].alpha = 0.0f; 
		        
		new_counter[17].type = 1;  // Large Font...  
		new_counter[17].right = false;   

		new_counter[17].x = -0.30f;              
		new_counter[17].y = -0.13f;     	         

		new_counter[17].w = new_counter[17].x - 0.026f;   
		new_counter[17].z = new_counter[17].y - 0.015f;
			     
		new_counter[17].box_width = strlen(new_counter[17].word)   *  0.026f;
		new_counter[17].box_height = new_counter[17].height - 0.015f;	

		if(VG_PLAYER_1_PAUSED == true && (VG_1_CHARACTER == VG_YOHAN || VG_1_CHARACTER == VG_REESE) )
		{
			VG_Moveslist(17, VG_1_CHARACTER, 6, 1);
			new_counter[17].alpha = 1.0f;
		}
		if(VG_PLAYER_1_PAUSED == false && (VG_2_CHARACTER == VG_YOHAN || VG_2_CHARACTER == VG_REESE) )
		{
			VG_Moveslist(17, VG_2_CHARACTER, 6, 2);
			new_counter[17].alpha = 1.0f;
		}
         
         
		new_counter[14].id = 2;       
		       
		new_counter[14].type = 1;  // Large Font...  
		new_counter[14].right = false;   

		new_counter[14].x = +0.10f;           
		new_counter[14].y = +0.17f;      	        

		new_counter[14].w = new_counter[14].x - 0.026f;   
		new_counter[14].z = new_counter[14].y - 0.015f;
			     
		new_counter[14].box_width = strlen(new_counter[14].word)   *  0.026f;
		new_counter[14].box_height = new_counter[14].height - 0.015f;	

		// Combo...
		if(VG_PLAYER_1_PAUSED == true)
			VG_Moveslist(14, VG_1_CHARACTER, 3, 1);
		else
			VG_Moveslist(14, VG_2_CHARACTER, 3, 2);
          
		new_counter[15].id = 2;      
		       
		new_counter[15].type = 1;  // Large Font...  
		new_counter[15].right = false;   

		new_counter[15].x = +0.10f;             
		new_counter[15].y = +0.07f;      	        

		new_counter[15].w = new_counter[15].x - 0.026f;   
		new_counter[15].z = new_counter[15].y - 0.015f;
			     
		new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
		new_counter[15].box_height = new_counter[15].height - 0.015f;	

		// Handcuffs...
		if(VG_PLAYER_1_PAUSED == true)
			VG_Moveslist(15, VG_1_CHARACTER, 4, 1);
		else
			VG_Moveslist(15, VG_2_CHARACTER, 4, 2);
          
		new_counter[16].id = 2;      
		       
		new_counter[16].type = 1;  // Large Font...  
		new_counter[16].right = false;   
		 
		new_counter[16].x = +0.10f;              
		new_counter[16].y = -0.03f;   	        

		new_counter[16].w = new_counter[16].x - 0.026f;   
		new_counter[16].z = new_counter[16].y - 0.015f;
			     
		new_counter[16].box_width = strlen(new_counter[16].word)   *  0.026f;
		new_counter[16].box_height = new_counter[16].height - 0.015f;	

		// New special...
		if(VG_PLAYER_1_PAUSED == true)
			VG_Moveslist(16, VG_1_CHARACTER, 5, 1);
		else
			VG_Moveslist(16, VG_2_CHARACTER, 5, 2);

		new_counter[20].id = 2;     
		       
		new_counter[20].type = 1;  // Large Font...  
		new_counter[20].right = false;   
		     
		new_counter[20].x = -0.27f;               
		new_counter[20].y = -0.26f;      	        

		new_counter[20].w = new_counter[20].x - 0.026f;   
		new_counter[20].z = new_counter[20].y - 0.015f;
			     
		new_counter[20].box_width = strlen(new_counter[20].word)   *  0.026f;
		new_counter[20].box_height = new_counter[20].height - 0.015f;

		if(VG_PLAYER_1_PAUSED == true)
		if(VG_P1_USING == VG_CONTROLLER) 
		{   
			new_counter[20].x = -0.34f;
#ifdef SWITCH
			sprintf( new_counter[20].word, "QUIT : Ý BACK  RESUME : Ž START");
#elif PS4
			sprintf( new_counter[20].word, "QUIT : ø  RESUME : OPTIONS");
#elif XB1
			sprintf( new_counter[20].word, "QUIT : ø  RESUME : MENU");
#elif DREAMCAST
			sprintf( new_counter[20].word, "QUIT : ø  RESUME : START");
#endif  
		}
		else
		{
			new_counter[20].x = -0.27f;
			sprintf( new_counter[20].word, "QUIT : ESC  RESUME : ENTER");
		}
		if(VG_PLAYER_1_PAUSED == false)
		if(VG_P2_USING == VG_CONTROLLER) 
		{   
			new_counter[20].x = -0.34f;
#ifdef SWITCH
			sprintf( new_counter[20].word, "QUIT : Ý BACK  RESUME : Ž START");
#elif PS4
			sprintf( new_counter[20].word, "QUIT : ø  RESUME : OPTIONS");
#elif XB1
			sprintf( new_counter[20].word, "QUIT : ø  RESUME : MENU");
#elif DREAMCAST
			sprintf( new_counter[20].word, "QUIT : ø  RESUME : START");
#endif
		}
		else
		{
			new_counter[20].x = -0.27f;
			sprintf( new_counter[20].word, "QUIT : ESC  RESUME : ENTER");
		}

		if(VG_GAME_MODE == VG_STORY_MODE)  
		if(VG_STORY_PAUSE == true) 
		{ 
			if(VG_P1_USING == VG_CONTROLLER) 
			{   
				new_counter[20].x = -0.27f; // was -0.34f
			//	sprintf( new_counter[20].word, "     ÷: NEXT ø: BACK^");  
				sprintf( new_counter[20].word, "        ÷: CONTINUE^"); 
			}
			else
			{
				new_counter[20].x = -0.27f;
				sprintf( new_counter[20].word, "     %c: NEXT %c: BACK^", VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
			}
		}


		if(VG_play_pause_menu == true) 
		{ 
			flash_pause_timer = (int)TimerGetTime();  
			new_counter[10].alpha = 0.0f; 

			VG_play_pause_menu = false;
			Set_Sprite(13, 0, ONCE, ANIM_HUD, ANIM_NOT_WALKING); // VG_KICK_SHORT_FONT
		}

		if(hud[13].anim_state == NO_ANIM)
			Set_Sprite(13, 1, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // VG_KICK_SHORT_FONT

		Animate(13, ANIM_HUD);

		if(game_paused == false)  
		{  
			new_counter[10].alpha = 0.0f;
			new_counter[11].alpha = 0.0f;  
			new_counter[12].alpha = 0.0f; 
			new_counter[13].alpha = 0.0f;   
			new_counter[14].alpha = 0.0f;  
			new_counter[15].alpha = 0.0f;
			new_counter[16].alpha = 0.0f;
			new_counter[20].alpha = 0.0f;

			new_counter[17].alpha = 0.0f;
			  
			hud[13].alpha = 0.0f;    
		}   
		else        
		{
			if(hud[13].anim_state == LOOP)
			{
				new_counter[11].alpha = 1.0f; 
				new_counter[20].alpha = 1.0f;

				if(VG_GAME_MODE != VG_STORY_MODE)
				{
					new_counter[12].alpha = 1.0f;
					new_counter[13].alpha = 1.0f;
					new_counter[14].alpha = 1.0f;
					new_counter[15].alpha = 1.0f;
					new_counter[16].alpha = 1.0f;

					if(VG_PLAYER_1_PAUSED == true && (VG_1_CHARACTER == VG_YOHAN || VG_1_CHARACTER == VG_REESE) )
						new_counter[17].alpha = 1.0f;
					if(VG_PLAYER_1_PAUSED == false && (VG_2_CHARACTER == VG_YOHAN || VG_2_CHARACTER == VG_REESE) )
						new_counter[17].alpha = 1.0f;
				}

				if(VG_PLAYER_1_PAUSED == true)
				if(VG_STORY_PAUSE == false)
				if(keys[VK_ESCAPE] == true || VG_1_DX_BACK == true)
				{  
					game_paused = false;
					VG_1_DX_BACK = false;
					keys[VK_ESCAPE] = false;

					VG_HUD_ESC = false;
					vg_next_episode = 0;
					vg_next_scene  = 1;

					if(VG_GAME_MODE == VG_TRAINING_MODE || VG_GAME_MODE == VG_VERSUS_MODE)
					{
						vg_next_episode = 6;
						vg_next_scene  = 1;

						vg_selected_character = false;
					}  
				 
					next_scene = true;  
				}

				if(VG_PLAYER_1_PAUSED == false)
				if(VG_2_DX_BACK == true) 
				{  
					game_paused = false;
					VG_2_DX_BACK = false;
					keys[VK_ESCAPE] = false;

					VG_HUD_ESC = false;
					vg_next_episode = 0;
					vg_next_scene  = 1;

					if(VG_GAME_MODE == VG_TRAINING_MODE || VG_GAME_MODE == VG_VERSUS_MODE)
					{
						vg_next_episode = 6;
						vg_next_scene  = 1;

						vg_selected_character = false;
					}
				 
					next_scene = true; 
				}

				if((int)TimerGetTime() > flash_pause_timer) 
				{
					if(new_counter[10].alpha == 0.0f)
					{
						flash_pause_timer = (int)TimerGetTime() + 500;
						new_counter[10].alpha = 1.0f;
					}
					else
					{
						flash_pause_timer = (int)TimerGetTime() + 500;
						new_counter[10].alpha = 0.0f;
					}
				}

				hud[13].alpha = 1.0f;    

			} // hud[13].anim_state == LOOP
		}
	}
}
