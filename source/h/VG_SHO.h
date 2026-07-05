#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64 
#define WIN32_LEAN_AND_MEAN    
#include <windows.h> 
#endif    

extern void Set_Vibration(int player, int left, int right, int time);
extern void VG_Play_Sound(int player, int sound);
extern bool VG_ShootRay(int player);
extern void VG_SlowMO(int duration, float strength);

void Run_Moves_SHO(int player, int f_rate) 
{

	float testX=0.0f, testY=0.0f;
	float inc_x=0.0f;
	float inc_y=0.0f;
	float temp_speed=0.0f;
	float distance = 0.0f;
	float half_distance = 0.0f;
	float mid_x = 0.0f, mid_y=0.0f;
	float tar_x = 0.0f, tar_y=0.0f; 
	bool temp_VG_RIGHT_pressed=false; 
	bool temp_VG_LEFT_pressed=false;
	bool temp_VG_UP_pressed=false;
	bool temp_VG_DOWN_pressed=false;
	int index = 0;
	int other_index = 0;
	int point_index = 0; 
	int shadow = 0;
	int tmp_VG_MovesList[MOVES_LIMIT];
	int tmp_VG_Moves_count=0;
	int move_anim = 0;
	bool VG_MOVE_ACTIVE=false;
	int bullet_anim = 0; 
	bool VG_reload_gun=false;
	int VG_CURRENT_CHAR=0;
	bool VG_CORNERED=false;
	int VG_shadow_index=0;
	bool VG_HANDCUFFED=false;

	if(f_rate >= 50)
		f_rate = 50;

	if(f_rate <= 0)
		f_rate = 1;

	if(VG_slowmof == 0.0f)
		return;

	if(player == 1)
	{
		VG_HANDCUFFED = sprite[2].handcuffed;
		VG_shadow_index = 6;
		VG_CORNERED = VG_1_CORNERED;
		VG_CURRENT_CHAR = VG_1_CHARACTER;
		VG_1_OFFSET = 0.0f;
		tmp_VG_Moves_count = VG_1_MovesList_count;
		for(int i=0;i<VG_1_MovesList_count;i++)
		if(i >= 0 && i < MOVES_LIMIT)
			tmp_VG_MovesList[i] = VG_1_MovesList[i];
		index = 2;
		other_index = 3;
		point_index=0;
		temp_VG_DOWN_pressed = VG_1_DOWN_pressed;
		VG_MOVE_ACTIVE=VG_1_MOVE_ACTIVE;
		sprite[index].invulnerable = false;
		sprite[index].strafe = false;
		sprite[index].spin_strafe = false;
		VG_1_OFFSET = 0.0f;
	}
	if(player == 2) 
	{
		VG_HANDCUFFED = sprite[3].handcuffed;
		VG_shadow_index = 5;
		VG_CORNERED = VG_2_CORNERED;
		VG_CURRENT_CHAR = VG_2_CHARACTER;
		VG_2_OFFSET = 0.0f;
		tmp_VG_Moves_count = VG_2_MovesList_count;
		for(int i=0;i<VG_2_MovesList_count;i++)
		if(i >= 0 && i < MOVES_LIMIT)
			tmp_VG_MovesList[i] = VG_2_MovesList[i]; 
		index = 3;
		other_index = 2;
		point_index=1;
		temp_VG_DOWN_pressed = VG_2_DOWN_pressed;
		VG_MOVE_ACTIVE=VG_2_MOVE_ACTIVE;
		sprite[index].invulnerable = false;
		sprite[index].strafe = false;
		sprite[index].spin_strafe = false;
		VG_2_OFFSET = 0.0f;
	}

	// Get distance for converting to short punches...
	mid_x = sprite[2].x + sprite[2].width/2;    
	tar_x = sprite[3].x + sprite[3].width/2;  

	distance = Node_Distance1(mid_x, VG_START_Y, tar_x, VG_START_Y);

	if(sprite[index].x < sprite[other_index].x) 
		sprite[index].hit_direction = LEFT;      
	else
		sprite[index].hit_direction = RIGHT; 

	// Grab and execute the latest move... 
	if(VG_HANDCUFFED == false)
    if(VG_finished_round == false)
	if(VG_MOVE_ACTIVE == false)
	if(sprite[index].status == -1)  
	if((tmp_VG_Moves_count-1) >= 0 && (tmp_VG_Moves_count-1) < MOVES_LIMIT)
	if(tmp_VG_MovesList[(tmp_VG_Moves_count-1)] >= 0)
	{ 

		points[point_index].active = 0;

		// ******************************************************************************//
		//                                    LANDED                                     //
		// ******************************************************************************//
		if(sprite[index].jumping == false)
 		if(tmp_VG_MovesList[(tmp_VG_Moves_count-1)] == VG_LANDED_FONT)   
		{    
			// Need to add punch short here... 
			move_anim = 70;
			Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_PUNCH_LONG_FONT
			sprite[index].status = VG_LANDED_FONT;   
			 
			// Length of the move...    
			if(player == 1)    
			{  
				memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList)); 
				VG_1_MOVE_ACTIVE = true;
			} 
			if(player == 2)         
			{
				memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList)); 
				VG_2_MOVE_ACTIVE = true; 
			}   
			   
		} 
		if(sprite[index].jumping == false)
 		if(tmp_VG_MovesList[(tmp_VG_Moves_count-1)] == VG_GETUP_FONT)   
		{   
			// Need to add punch short here...
			move_anim = 71;
			Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_PUNCH_LONG_FONT
			sprite[index].status = VG_GETUP_FONT;  

			// Length of the move...  
			if(player == 1)   
			{
				memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList)); 
				VG_1_MOVE_ACTIVE = true;
			} 
			if(player == 2)         
			{
				memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList)); 
				VG_2_MOVE_ACTIVE = true; 
			}   

		} 

		// ******************************************************************************//
		//                                    THROWS                                     //
		// ******************************************************************************//
		if(sprite[index].jumping == false)
 		if(tmp_VG_MovesList[(tmp_VG_Moves_count-1)] == VG_KICK_AND_PUNCH_FONT)   
		{   
			// Need to add punch short here...
			move_anim = 46;
			Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_PUNCH_LONG_FONT
			sprite[index].status = VG_KICK_AND_PUNCH_FONT; 

			// Length of the move...     
			if(player == 1)   
			{
				memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList)); 
				VG_1_MOVE_ACTIVE = true; 
			} 
			if(player == 2)         
			{
				memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList)); 
				VG_2_MOVE_ACTIVE = true; 
			}    
			if(player == 1) 
			{
				if(VG_1_special1_sfx == 0)
				    VG_1_special1_sfx = 2;   
			}
			else  
			{
				if(VG_2_special1_sfx == 0)
				    VG_2_special1_sfx = 2;  
			}

		} 

		// ******************************************************************************//
		//                                    COMBOS                                     //
		// ******************************************************************************//

		// VG_COMBO1...  
		if(sprite[index].jumping == false)
 		if(tmp_VG_MovesList[(tmp_VG_Moves_count-1)] == VG_COMBO1 || tmp_VG_MovesList[(tmp_VG_Moves_count-1)] == VG_AI_COMBO_FONT)   
		{  

			// Need to add punch short here...
			move_anim = 38;
			Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_PUNCH_LONG_FONT
			sprite[index].status = VG_SECOND_STRIKE; 

			VG_yell_sfx = VG_CURRENT_CHAR;

			// Length of the move...  
			if(player == 1)   
			{
				memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList)); 
				VG_1_MOVE_ACTIVE = true;
			} 
			if(player == 2)         
			{
				memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList)); 
				VG_2_MOVE_ACTIVE = true; 
			}   

			if(player == 1)
				VG_1_STRIKE_TIMER = (int)TimerGetTime() + VG_STRIKE_DELAY;
			if(player == 2)
				VG_2_STRIKE_TIMER = (int)TimerGetTime() + VG_STRIKE_DELAY;

		}
		// VG_COMBO2...  
		if(sprite[index].jumping == false)
 		if(tmp_VG_MovesList[(tmp_VG_Moves_count-1)] == VG_COMBO2)   
		{  

			// Need to add punch short here... 
			move_anim = 68;
			Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_KICK_LONG_FONT
			sprite[index].status = VG_THIRD_STRIKE;

			// Length of the move...   
			if(player == 1)   
			{
				memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList)); 
				VG_1_MOVE_ACTIVE = true;
			} 
			if(player == 2)         
			{
				memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList)); 
				VG_2_MOVE_ACTIVE = true; 
			}   
			if(player == 1) 
			{
				if(VG_1_special1_sfx == 0)
				    VG_1_special1_sfx = 2;   
			}
			else  
			{
				if(VG_2_special1_sfx == 0)
				    VG_2_special1_sfx = 2;  
			}

		}   

		// ******************************************************************************//
		//                                  SPECIALS                                     //
		// ******************************************************************************//

		// VG_SPECIAL1_FONT...  
		if(sprite[index].jumping == false && sprite[index].status != VG_LANDED_FONT)
 		if(tmp_VG_MovesList[(tmp_VG_Moves_count-1)] == VG_SPECIAL1_FONT || tmp_VG_MovesList[(tmp_VG_Moves_count-1)] == VG_AI_SPECIAL1_FONT)   
		{  

			// Slide...
			if(sprite[index].jumping == false)
			if (sprite[index].special == 1)
			{
				move_anim = 75;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_SPECIAL1_FONT
				sprite[index].status = VG_SPECIAL1_FONT;
			}

			// FlameKick...
			if(sprite[index].jumping == false)
			if(sprite[index].special == 2)    
			{
				move_anim = 74;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_SPECIAL1_FONT
				sprite[index].status = VG_SPECIAL1_FONT;
			}

			// Fireball...
			if(sprite[index].jumping == false)
			if(sprite[index].special == 3)  
			{
				if(player == 1)
				{
					VG_1_Pistolsfx = 0;
					VG_1_BULLETS--;
					if(VG_1_BULLETS < 0)
					{
						VG_reload_gun = true;
						VG_1_BULLETS = 0;
					}
				}
				else
				{
					VG_2_Pistolsfx = 0;
					VG_2_BULLETS--;
					if(VG_2_BULLETS < 0)  
					{
						VG_reload_gun = true;
						VG_2_BULLETS = 0;
					}
				}
				move_anim = 27;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_SPECIAL2_FONT
				sprite[index].status = VG_SPECIAL2_FONT;

				if(VG_reload_gun == true)
				{
					sprite[index].special = 0;
					move_anim = 29;
					Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_SPECIAL2_FONT
					sprite[index].status = VG_RELOAD_FONT;
				}
			}

			if (sprite[index].jumping == false)
			{
				// Length of the move...   
				if (player == 1)
				{
					memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList));
					VG_1_MOVE_ACTIVE = true;
				}
				if (player == 2)
				{
					memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList));
					VG_2_MOVE_ACTIVE = true;
				}

				if (VG_reload_gun == false)
					if (sprite[index].special != 4 && sprite[index].special != 5) // Pistols...
						if (player == 1)
						{
							if (VG_1_special1_sfx == 0)
								VG_1_special1_sfx = 2;
						}
						else
						{
							if (VG_2_special1_sfx == 0)
								VG_2_special1_sfx = 2;
						}
			}


		} 

		// VG_PUNCH_FONT... // Slow punch 'K'
 		if(tmp_VG_MovesList[(tmp_VG_Moves_count-1)] == VG_PUNCH_FONT)   
		{   

			// Need to add punch short here...
			if(distance < VG_CLOSE_ATTACK_DISTANCE && sprite[other_index].jumping == false) 
			{
				move_anim = 72;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_PUNCH_MEDIUM_FONT
				sprite[index].status = VG_PUNCH_CLOSE_FONT;
			}
			else
			{
				move_anim = 11; // 12
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_PUNCH_MEDIUM_FONT
				sprite[index].status = VG_PUNCH_LONG_FONT;
			}

			// Crouching hit...
			if(temp_VG_DOWN_pressed == true)  
			{
				move_anim = 32;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_UPPERCUT_FONT
				sprite[index].status = VG_LOW_PUNCH2_FONT;
			} 

			// Jump punch...
			if(sprite[index].jumping == true)   
			{
				move_anim = 20;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_KICK_SHORT_FONT
				sprite[index].status = VG_JUMPING_PUNCH_FONT;
			}
			// Length of the move...  
			if(player == 1)   
			{
				memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList)); 
				VG_1_MOVE_ACTIVE = true;
			}
			if(player == 2)      
			{
				memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList)); 
				VG_2_MOVE_ACTIVE = true;
			} 

		//	chop_sfx = true;     
		}        
		// VG_PUNCH2_FONT...   // Fast punch 'L'
		if(tmp_VG_MovesList[(tmp_VG_Moves_count-1)] == VG_PUNCH2_FONT)   
		{   
			 
			// Need to add punch short here...
			if(distance < VG_CLOSE_ATTACK_DISTANCE && sprite[other_index].jumping == false) 
			{
				move_anim = 72;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_PUNCH_MEDIUM_FONT
				sprite[index].status = VG_PUNCH_CLOSE_FONT;
			}
			else
			{
				move_anim = 12; // 11
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_PUNCH_LONG_FONT
				sprite[index].status = VG_PUNCH_MEDIUM_FONT;
			}

			// Crouching hit...
			if(temp_VG_DOWN_pressed == true)
			{
				move_anim = 23;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_PUNCH_MEDIUM_FONT
				sprite[index].status = VG_LOW_PUNCH_FONT;
			}
			// Jump punch...
			if(sprite[index].jumping == true) 
			{
				move_anim = 20;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_KICK_SHORT_FONT
				sprite[index].status = VG_JUMPING_PUNCH_FONT;
			}
			// Length of the move...  
			if(player == 1)   
			{
				memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList)); 
				VG_1_MOVE_ACTIVE = true;
			}
			if(player == 2)  
			{
				memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList)); 
				VG_2_MOVE_ACTIVE = true;
			} 

		//	chop_sfx = true;      
		} 
		// VG_KICK_FONT...   Slow Kick 'm'
		if(tmp_VG_MovesList[(tmp_VG_Moves_count-1)] == VG_KICK_FONT)   
		{   

			// Need to add punch short here...  
			if(distance < VG_CLOSE_ATTACK_DISTANCE && sprite[other_index].jumping == false) 
			{
				move_anim = 73;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_PUNCH_MEDIUM_FONT
				sprite[index].status = VG_PUNCH_CLOSE_FONT;
			}
			else
			{
				move_anim = 14; // 15
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_KICK_LONG_FONT
				sprite[index].status = VG_KICK_KNEE_FONT;
			}

			// Crouching hit...
			if(temp_VG_DOWN_pressed == true)
			{
				move_anim = 25;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_PUNCH_MEDIUM_FONT
				sprite[index].status = VG_LOW_KICK_FONT;
			}
			// Jump kick...
			if(sprite[index].jumping == true)
			{
				move_anim = 66;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_KICK_SHORT_FONT
				sprite[index].status = VG_JUMPING_KICK_FONT;
			}
			// Length of the move...  
			if(player == 1)   
			{
				memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList)); 
				VG_1_MOVE_ACTIVE = true;
			}
			if(player == 2)  
			{
				memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList)); 
				VG_2_MOVE_ACTIVE = true;
			} 
			 
		//	chop_sfx = true;     
		} 
		// VG_KICK2_FONT...   Fast kick ','
		if(tmp_VG_MovesList[(tmp_VG_Moves_count-1)] == VG_KICK2_FONT)   
		{  

			// Need to add kick short here...
			if(distance < VG_CLOSE_ATTACK_DISTANCE && sprite[other_index].jumping == false) 
			{
				move_anim = 73;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_PUNCH_MEDIUM_FONT
				sprite[index].status = VG_PUNCH_CLOSE_FONT;
			}
			else
			{
				move_anim = 15; // 14
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_KICK_KNEE_FONT
				sprite[index].status = VG_KICK_LONG_FONT;
			}

			// Crouching hit...
			if(temp_VG_DOWN_pressed == true)
			{
				move_anim = 26;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_PUNCH_MEDIUM_FONT
				sprite[index].status = VG_LOW_KICK_SHORT_FONT;
			}  
			// Jump kick...
			if(sprite[index].jumping == true) 
			{
				move_anim = 66;
				Set_Sprite(index, move_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_KICK_SHORT_FONT
				sprite[index].status = VG_JUMPING_KICK_FONT;
			}

			// Length of the move...  
			if(player == 1)    
			{
				memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList)); 
				VG_1_MOVE_ACTIVE = true;
			} 
			if(player == 2)  
			{
				memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList)); 
				VG_2_MOVE_ACTIVE = true;
			} 
			 
		//	chop_sfx = true;     
		}

	} 

	if(player == 1) 
	{
		index = 2;
		point_index = 0;  

		mid_x = sprite[index].x + sprite[index].width/2;  
		tar_x = sprite[other_index].x + sprite[other_index].width/2;  

		distance = Node_Distance1(mid_x, VG_START_Y, tar_x, VG_START_Y);

	} 
	if(player == 2)  
	{
		index = 3;
		point_index = 1; 

		mid_x = sprite[index].x + sprite[index].width/2;  
		tar_x = sprite[other_index].x + sprite[other_index].width/2;  

		distance = Node_Distance1(mid_x, VG_START_Y, tar_x, VG_START_Y);
	} 

	// End of inputs...

	if(sprite[index].status == VG_KICK_AND_PUNCH_FONT)     
	{
		if(points[point_index].active != 2)	     
			points[point_index].active = 0;    

		if(sprite[index].cur == 1)         
		{    

			VG_Play_Sound(player, VG_SOUND_CHOP); 
			 
			if(points[point_index].active != 2) 
				points[point_index].active = 1;          
			   
			if(sprite[index].movement == RIGHT)
			{
				points[point_index].x = sprite[index].x + 0.40f;          
				points[point_index].y = sprite[index].y + 0.26f;
				points[point_index+2].x = sprite[index].x + 0.24f;             
				points[point_index+2].y = sprite[index].y + 0.26f;
			}   
			if(sprite[index].movement == LEFT)    
			{
				points[point_index].x = sprite[index].x + 0.00f;          
				points[point_index].y = sprite[index].y + 0.26f;
				points[point_index+2].x = sprite[index].x + 0.16f;            
				points[point_index+2].y = sprite[index].y + 0.26f;
			}   
			 
		}          

		if(sprite[index].movement == LEFT) 
		{
			if(player == 1)
				VG_1_OFFSET *= -1.0f;
			else
				VG_2_OFFSET *= -1.0f;
		}
	}  
	// Reloading gun...
	if(sprite[index].status == VG_RELOAD_FONT)       
	{
		sprite[index].strafe = true;

		sprite[index].special = 0;

		if(points[point_index].active != 2)	      
			points[point_index].active = 0;
		if(sprite[index].cur == 1)
		{
			if(VG_reloadsfx == 0)
			    VG_reloadsfx = 1;

			if(player == 1)
			{
				VG_1_BULLETS = 1; 
			}
			if(player == 2) 
			{
				VG_2_BULLETS = 1;
			}

		}
		if(sprite[index].cur == 2)  
		{
			if(VG_reloadedsfx == 0)
				VG_reloadedsfx = 1; 

			if(player == 1)
			{
				VG_1_BULLETS = 3;
			}
			if(player == 2)
			{
				VG_2_BULLETS = 3;
			}

		}
	}

	// Fireball...
	if(sprite[index].status == VG_SPECIAL2_FONT)       
	{
		if(sprite[index].special != 4) // Low pistol...
		    sprite[index].strafe = true;

		if(points[point_index].active != 2)	      
			points[point_index].active = 0;   
		   
		if(sprite[index].cur == 2)  
		{ 
			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(sprite[index].movement == RIGHT)    
			{  
				points[point_index].x = sprite[index].x + 0.29f;           
				points[point_index].y = sprite[index].y + 0.245f;
				points[point_index+2].x = sprite[index].x + 0.29f;           
				points[point_index+2].y = sprite[index].y + 0.245f;

				bullet_anim = 51;
			}
			else
			{
				points[point_index].x = sprite[index].x + 0.11f;          
				points[point_index].y = sprite[index].y + 0.245f;
				points[point_index+2].x = sprite[index].x + 0.11f;          
				points[point_index+2].y = sprite[index].y + 0.245f;
				bullet_anim = 52; 
			}   
		
			if(player == 1) 
			if(VG_1_Pistolsfx == 0)   
			{ 

				if(sprite[index].movement == LEFT)
					New_FX(points[point_index].x-0.05f, points[point_index].y-0.05f,  points[point_index].x-0.05f, points[point_index].y-0.05f, bullet_anim, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, index, FX_VG_FIREBALL, index, 12, 0, 0, LEFT); 
				else
					New_FX(points[point_index].x-0.05f, points[point_index].y-0.05f,  points[point_index].x-0.05f, points[point_index].y-0.05f, bullet_anim, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, index, FX_VG_FIREBALL, index, 12, 0, 0, RIGHT); 

				VG_1_Pistolsfx = 1;	  
			//	VG_SlowMO(500, 2.0f);  
			}
			if(player == 2)  
			if(VG_2_Pistolsfx == 0) 
			{
				if(sprite[index].movement == LEFT)
					New_FX(points[point_index].x-0.05f, points[point_index].y-0.05f,  points[point_index].x-0.05f, points[point_index].y-0.05f, bullet_anim, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, index, FX_VG_FIREBALL, index, 12, 0, 0, LEFT); 
				else
					New_FX(points[point_index].x-0.05f, points[point_index].y-0.05f,  points[point_index].x-0.05f, points[point_index].y-0.05f, bullet_anim, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, index, FX_VG_FIREBALL, index, 12, 0, 0, RIGHT); 

				VG_2_Pistolsfx = 1;	  
			//	VG_SlowMO(500, 2.0f);
			} 
			  
		}

		if(sprite[index].movement == LEFT)  
		{
			if(player == 1) 
				VG_1_OFFSET *= -1.0f;
			else
				VG_2_OFFSET *= -1.0f; 
		}  
		       

	}

	// FlameKick...
	if(sprite[index].special == 2) 
	if(sprite[index].status == VG_SPECIAL1_FONT)       
	{

		sprite[index].invulnerable = false;

		if(points[point_index].active != 2)	      
			points[point_index].active = 0;   

		if(sprite[index].cur == 1)          
			temp_speed = ((0.00035f/VG_slowmof)*(float)f_rate); 

		if(sprite[index].cur == 2)      
			temp_speed = ((0.00055f/VG_slowmof)*(float)f_rate); 

		if(sprite[index].cur == 3)      
			temp_speed = ((0.00035f/VG_slowmof)*(float)f_rate); 

		if(sprite[index].movement == RIGHT) 
		if(distance < screen_limit || sprite[index].x < sprite[other_index].x)
		{
			sprite[index].x += temp_speed;  
			sprite[index].w += temp_speed; 
		}
		if(sprite[index].movement == LEFT)
		if(distance < screen_limit || sprite[index].x > sprite[other_index].x)
		{
			sprite[index].x -= temp_speed;  
			sprite[index].w -= temp_speed; 
		}

		if (sprite[index].cur == 1)
		{
			sprite[index].invulnerable = true;

		}

		if (sprite[index].cur == 2)
		{
			sprite[index].invulnerable = true; 
			 
			VG_Play_Sound(player, VG_SOUND_CHOP);

			if (points[point_index].active != 2)
				points[point_index].active = 1;

			if (sprite[index].movement == RIGHT)
			{
				points[point_index].x = sprite[index].x + 0.44f;
				points[point_index].y = sprite[index].y + 0.28f;
				points[point_index + 2].x = sprite[index].x + 0.20f;
				points[point_index + 2].y = sprite[index].y + 0.28f;
			}
			if (sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x - 0.03f;
				points[point_index].y = sprite[index].y + 0.28f;
				points[point_index + 2].x = sprite[index].x + 0.16f;
				points[point_index + 2].y = sprite[index].y + 0.28f;
			}

		}

		if(sprite[index].cur == 1)
		{
			if (sprite[index].jumping == false)
			{
				sprite[index].jumping = true;
				sprite[index].on_ladder = true;

				sprite[index].action_timer = (int)TimerGetTime() + 90;
			}

		//	sprite[index].y += temp_speed;  
		//	sprite[index].z += temp_speed; 
		}


	}

	// Slide...
	if(sprite[index].special == 1)
	if(sprite[index].status == VG_SPECIAL1_FONT)       
	{

		sprite[index].invulnerable = false;

		if(points[point_index].active != 2)	      
			points[point_index].active = 0;    

		if(sprite[index].cur == 2)            
		{   
			sprite[index].invulnerable = true; 
			 
			// Shadow trails...  
			if(player == 1)
			if((int)TimerGetTime() > VG_1_trail_timer)
			{
				VG_1_trail_timer = (int)TimerGetTime() + 75;

				if(sprite[index].movement == RIGHT)
					New_FX(sprite[index].x, sprite[index].y, sprite[index].x, sprite[index].y, 69, PLAY, sprite[index].width,sprite[index].height, sprite[index].width,sprite[index].height, 3, GFX, 1.0f, 0, -1, FX_STATIC, index, sprite[index].id, 0, 0, index);
				else
					New_FX(sprite[index].x, sprite[index].y, sprite[index].x, sprite[index].y, 69, PLAY, sprite[index].width,sprite[index].height, sprite[index].width,sprite[index].height, 3, GFX, 1.0f, 0, -1, FX_FLIP, index, sprite[index].id, 0, 0, index);

			}
			// Shadow trails...   
			if(player == 2)
			if((int)TimerGetTime() > VG_2_trail_timer)
			{
				VG_2_trail_timer = (int)TimerGetTime() + 75;

				if(sprite[index].movement == RIGHT)
					New_FX(sprite[index].x, sprite[index].y, sprite[index].x, sprite[index].y, 69, PLAY, sprite[index].width,sprite[index].height, sprite[index].width,sprite[index].height, 3, GFX, 1.0f, 0, -1, FX_STATIC, index, sprite[index].id, 0, 0, index);
				else
					New_FX(sprite[index].x, sprite[index].y, sprite[index].x, sprite[index].y, 69, PLAY, sprite[index].width,sprite[index].height, sprite[index].width,sprite[index].height, 3, GFX, 1.0f, 0, -1, FX_FLIP, index, sprite[index].id, 0, 0, index);

			}

			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2)        
				points[point_index].active = 1;    
			 
			if(sprite[index].movement == RIGHT)    
			{
				points[point_index].x = sprite[index].x + 0.44f;           
				points[point_index].y = sprite[index].y + 0.28f;
				points[point_index+2].x = sprite[index].x + 0.20f;              
				points[point_index+2].y = sprite[index].y + 0.28f;
			} 
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x - 0.03f;           
				points[point_index].y = sprite[index].y + 0.28f;
				points[point_index+2].x = sprite[index].x + 0.16f;       
				points[point_index+2].y = sprite[index].y + 0.28f;
			}    

		}          

		if (sprite[index].cur == 5 || sprite[index].cur == 6 || sprite[index].cur == 7)
		{
			sprite[index].invulnerable = true;

			// Shadow trails...  
			if (player == 1)
				if ((int)TimerGetTime() > VG_1_trail_timer)
				{
					VG_1_trail_timer = (int)TimerGetTime() + 75;

					if (sprite[index].movement == RIGHT)
						New_FX(sprite[index].x, sprite[index].y, sprite[index].x, sprite[index].y, 69, PLAY, sprite[index].width, sprite[index].height, sprite[index].width, sprite[index].height, 3, GFX, 1.0f, 0, -1, FX_STATIC, index, sprite[index].id, 0, 0, index);
					else
						New_FX(sprite[index].x, sprite[index].y, sprite[index].x, sprite[index].y, 69, PLAY, sprite[index].width, sprite[index].height, sprite[index].width, sprite[index].height, 3, GFX, 1.0f, 0, -1, FX_FLIP, index, sprite[index].id, 0, 0, index);

				}
			// Shadow trails...   
			if (player == 2)
			if ((int)TimerGetTime() > VG_2_trail_timer)
			{
				VG_2_trail_timer = (int)TimerGetTime() + 75;

				if (sprite[index].movement == RIGHT)
					New_FX(sprite[index].x, sprite[index].y, sprite[index].x, sprite[index].y, 69, PLAY, sprite[index].width, sprite[index].height, sprite[index].width, sprite[index].height, 3, GFX, 1.0f, 0, -1, FX_STATIC, index, sprite[index].id, 0, 0, index);
				else
					New_FX(sprite[index].x, sprite[index].y, sprite[index].x, sprite[index].y, 69, PLAY, sprite[index].width, sprite[index].height, sprite[index].width, sprite[index].height, 3, GFX, 1.0f, 0, -1, FX_FLIP, index, sprite[index].id, 0, 0, index);

			}

			VG_Play_Sound(player, VG_SOUND_CHOP);

			if (points[point_index].active != 2)
				points[point_index].active = 1;

			if (sprite[index].movement == RIGHT)
			{
				points[point_index].x = sprite[index].x + 0.30f;
				points[point_index].y = sprite[index].y + 0.10f;
				points[point_index + 2].x = sprite[index].x + 0.20f;
				points[point_index + 2].y = sprite[index].y + 0.10f;
			}
			if (sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x + 0.06f;
				points[point_index].y = sprite[index].y + 0.10f;
				points[point_index + 2].x = sprite[index].x + 0.16f;
				points[point_index + 2].y = sprite[index].y + 0.10f;
			}

		}

		if(sprite[index].cur == 1)          
			temp_speed = ((0.00050f/VG_slowmof)*(float)f_rate); 

		if(sprite[index].cur == 2)      
			temp_speed = ((0.00100f/VG_slowmof)*(float)f_rate); 

		if(sprite[index].cur == 3)      
			temp_speed = ((0.00080f/VG_slowmof)*(float)f_rate); 

		if (sprite[index].cur == 4)
			temp_speed = ((0.00035f / VG_slowmof)*(float)f_rate);

		if (sprite[index].cur == 5)
			temp_speed = ((0.00050f / VG_slowmof)*(float)f_rate);

		if (sprite[index].cur == 6)
			temp_speed = ((0.00075f / VG_slowmof)*(float)f_rate);

		if (sprite[index].cur == 7)
			temp_speed = ((0.00050f / VG_slowmof)*(float)f_rate);

		if(sprite[index].movement == RIGHT) 
		if(distance < screen_limit || sprite[index].x < sprite[other_index].x)
		{
			sprite[index].x += temp_speed;  
			sprite[index].w += temp_speed; 
		}
		if(sprite[index].movement == LEFT)
		if(distance < screen_limit || sprite[index].x > sprite[other_index].x)
		{
			sprite[index].x -= temp_speed;  
			sprite[index].w -= temp_speed; 
		}


	}

	if(sprite[index].status == VG_PUNCH_CLOSE_FONT)     
	{
		if(points[point_index].active != 2)	      
			points[point_index].active = 0;    

		if(sprite[index].cur == 1)    
		{ 

			VG_Play_Sound(player, VG_SOUND_CHOP); 

			if(points[point_index].active != 2)
				points[point_index].active = 1;         
			  
			if(sprite[index].movement == RIGHT)
			{
				points[point_index].x = sprite[index].x + 0.41f;          
				points[point_index].y = sprite[index].y + 0.26f;
				points[point_index+2].x = sprite[index].x + 0.24f;             
				points[point_index+2].y = sprite[index].y + 0.26f;
			}   
			if(sprite[index].movement == LEFT)   
			{
				points[point_index].x = sprite[index].x - 0.01f;          
				points[point_index].y = sprite[index].y + 0.26f;
				points[point_index+2].x = sprite[index].x + 0.16f;            
				points[point_index+2].y = sprite[index].y + 0.26f;
			}   

		}
		 
	}  

	if(sprite[index].status == VG_KICK_CLOSE_FONT)     
	{
		if(points[point_index].active != 2)	      
			points[point_index].active = 0;    

		if(sprite[index].cur == 1)     
		{ 

			VG_Play_Sound(player, VG_SOUND_CHOP); 

			if(points[point_index].active != 2)
				points[point_index].active = 1;         
			  
			if(sprite[index].movement == RIGHT)
			{
				points[point_index].x = sprite[index].x + 0.41f;          
				points[point_index].y = sprite[index].y + 0.18f;
				points[point_index+2].x = sprite[index].x + 0.24f;             
				points[point_index+2].y = sprite[index].y + 0.18f;
			}   
			if(sprite[index].movement == LEFT)   
			{
				points[point_index].x = sprite[index].x - 0.01f;          
				points[point_index].y = sprite[index].y + 0.18f;
				points[point_index+2].x = sprite[index].x + 0.16f;            
				points[point_index+2].y = sprite[index].y + 0.18f;
			}   

		}

	}  
	if(sprite[index].status == VG_LOW_PUNCH_FONT)      
	{ 
		       
		if(points[point_index].active != 2) 
			points[point_index].active = 0;     
			    
		if(sprite[index].cur == 1)       
		{   
			VG_Play_Sound(player, VG_SOUND_CHOP);
			 
			if(points[point_index].active != 2)    
				points[point_index].active = 1;
			   
			if(sprite[index].movement == RIGHT)  
			{
				points[point_index].x = sprite[index].x + 0.39f;           
				points[point_index].y = sprite[index].y + 0.19f;
				points[point_index+2].x = sprite[index].x + 0.24f;            
				points[point_index+2].y = sprite[index].y + 0.19f;
			} 
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x + 0.01f;          
				points[point_index].y = sprite[index].y + 0.19f;
				points[point_index+2].x = sprite[index].x + 0.14f;       
				points[point_index+2].y = sprite[index].y + 0.19f;
			}   
			 
		}    

	} 
	if(sprite[index].status == VG_LOW_PUNCH2_FONT)     
	{
		      
		if(points[point_index].active != 2)  
			points[point_index].active = 0;     
			    
		if(sprite[index].cur == 1)       
		{   
			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2)    
				points[point_index].active = 1;
			     
			if(sprite[index].movement == RIGHT)  
			{
				points[point_index].x = sprite[index].x + 0.39f;           
				points[point_index].y = sprite[index].y + 0.21f;
				points[point_index+2].x = sprite[index].x + 0.24f;            
				points[point_index+2].y = sprite[index].y + 0.21f;
			} 
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x + 0.01f;          
				points[point_index].y = sprite[index].y + 0.21f;
				points[point_index+2].x = sprite[index].x + 0.14f;       
				points[point_index+2].y = sprite[index].y + 0.21f;
			}   

		}    

	} 
	if(sprite[index].status == VG_LOW_PUNCH_SHORT_FONT)     
	{
		      
		if(points[point_index].active != 2) 
			points[point_index].active = 0;     
			    
		if(sprite[index].cur == 1)       
		{   
			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2)     
				points[point_index].active = 1;
			   
			if(sprite[index].movement == RIGHT)  
			{
				points[point_index].x = sprite[index].x + 0.34f;           
				points[point_index].y = sprite[index].y + 0.17f; 
				points[point_index+2].x = sprite[index].x + 0.24f;            
				points[point_index+2].y = sprite[index].y + 0.17f;
			} 
			if(sprite[index].movement == LEFT)  
			{
				points[point_index].x = sprite[index].x + 0.06f;          
				points[point_index].y = sprite[index].y + 0.17f;
				points[point_index+2].x = sprite[index].x + 0.14f;       
				points[point_index+2].y = sprite[index].y + 0.17f;
			}   

		}    

	} 
	if(sprite[index].status == VG_LOW_KICK_FONT)     
	{
		      
		if(points[point_index].active != 2) 
			points[point_index].active = 0;    

		if(sprite[index].cur == 1)             
		{   
			if(player == 1)    
				VG_1_OFFSET = 0.060f;   
			else  
				VG_2_OFFSET = 0.060f;   

			VG_Play_Sound(player, VG_SOUND_CHOP);
			 
			if(points[point_index].active != 2)    
				points[point_index].active = 1; 
			  
			if(sprite[index].movement == RIGHT)    
			{
				points[point_index].x = sprite[index].x + 0.45f;           
				points[point_index].y = sprite[index].y + 0.05f;
				points[point_index+2].x = sprite[index].x + 0.24f;             
				points[point_index+2].y = sprite[index].y + 0.07f;
			} 
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x - 0.04f;          
				points[point_index].y = sprite[index].y + 0.05f;
				points[point_index+2].x = sprite[index].x + 0.14f;       
				points[point_index+2].y = sprite[index].y + 0.07f;
			}    

		}      

		if(sprite[index].movement == LEFT) 
		{
			if(player == 1)
				VG_1_OFFSET *= -1.0f;
			else
				VG_2_OFFSET *= -1.0f;
		}
	} 
 
	if(sprite[index].status == VG_LOW_KICK_SHORT_FONT)      
	{
		      
		if(points[point_index].active != 2) 
			points[point_index].active = 0;    

		if(sprite[index].cur == 1)              
		{   
			if(player == 1)     
				VG_1_OFFSET = 0.060f;      
			else   
				VG_2_OFFSET = 0.060f;    

			VG_Play_Sound(player, VG_SOUND_CHOP);
			 
			if(points[point_index].active != 2)    
				points[point_index].active = 1; 
			  
			if(sprite[index].movement == RIGHT)    
			{
				points[point_index].x = sprite[index].x + 0.48f;           
				points[point_index].y = sprite[index].y + 0.05f;
				points[point_index+2].x = sprite[index].x + 0.24f;              
				points[point_index+2].y = sprite[index].y + 0.07f;
			} 
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x - 0.07f;          
				points[point_index].y = sprite[index].y + 0.05f;
				points[point_index+2].x = sprite[index].x + 0.14f;       
				points[point_index+2].y = sprite[index].y + 0.07f;
			}    

		}      

		if(sprite[index].movement == LEFT) 
		{
			if(player == 1)
				VG_1_OFFSET *= -1.0f;
			else
				VG_2_OFFSET *= -1.0f;
		}
	} 
	if(sprite[index].status == VG_PUNCH_SHORT_FONT)     
	{
		      
		if(points[point_index].active != 2)
			points[point_index].active = 0;     
			    
		if(sprite[index].cur == 1)     
		{   
			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2)  
				points[point_index].active = 1;  
			  
			if(sprite[index].movement == RIGHT)   
			{
				points[point_index].x = sprite[index].x + 0.32f;           
				points[point_index].y = sprite[index].y + 0.32f;
				points[point_index+2].x = sprite[index].x + 0.24f;            
				points[point_index+2].y = sprite[index].y + 0.28f;
			} 
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x + 0.08f;          
				points[point_index].y = sprite[index].y + 0.32f;
				points[point_index+2].x = sprite[index].x + 0.14f;       
				points[point_index+2].y = sprite[index].y + 0.28f;
			}   

		}   

	} 
	if(sprite[index].status == VG_PUNCH_MEDIUM_FONT)       
	{
		if(points[point_index].active != 2)	     
			points[point_index].active = 0;    
		 
		if(sprite[index].cur == 0) 
		{ 
			if(player == 1)
				VG_1_OFFSET = 0.05f;
			else
				VG_2_OFFSET = 0.05f;
		} 

		if(sprite[index].cur == 1)         
		{      
			if(player == 1)
				VG_1_OFFSET = 0.1f;
			else
				VG_2_OFFSET = 0.1f; 

			VG_Play_Sound(player, VG_SOUND_CHOP);
			  
			if(points[point_index].active != 2)
				points[point_index].active = 1;     
			   
			if(sprite[index].movement == RIGHT)
			{
				points[point_index].x = sprite[index].x + 0.48f;          
				points[point_index].y = sprite[index].y + 0.32f;
				points[point_index+2].x = sprite[index].x + 0.34f;             
				points[point_index+2].y = sprite[index].y + 0.27f;
			}  
			if(sprite[index].movement == LEFT)  
			{
				points[point_index].x = sprite[index].x - 0.08f;          
				points[point_index].y = sprite[index].y + 0.32f;
				points[point_index+2].x = sprite[index].x + 0.06f;            
				points[point_index+2].y = sprite[index].y + 0.27f;
			}  

		}          

		if(sprite[index].cur == 2)  
		{
			if(player == 1)
				VG_1_OFFSET = 0.05f;
			else
				VG_2_OFFSET = 0.05f;      
		}

		if(sprite[index].movement == LEFT) 
		{
			if(player == 1)
				VG_1_OFFSET *= -1.0f;
			else
				VG_2_OFFSET *= -1.0f;
		}

	} 
	if(sprite[index].status == VG_PUNCH_LONG_FONT)     
	{
		if(points[point_index].active != 2)
			points[point_index].active = 0;    
			   
		if(sprite[index].cur == 1)      
		{   
			if(player == 1)  
				VG_1_OFFSET = 0.05f;
			else  
				VG_2_OFFSET = 0.05f;   

			VG_Play_Sound(player, VG_SOUND_CHOP); 

			if(points[point_index].active != 2)
				points[point_index].active = 1;  
			      
			if(sprite[index].movement == RIGHT) 
			{
				points[point_index].x = sprite[index].x + 0.44f;          
				points[point_index].y = sprite[index].y + 0.27f;
				points[point_index+2].x = sprite[index].x + 0.34f;             
				points[point_index+2].y = sprite[index].y + 0.27f;
			}  
			if(sprite[index].movement == LEFT)  
			{
				points[point_index].x = sprite[index].x - 0.04f;          
				points[point_index].y = sprite[index].y + 0.27f;
				points[point_index+2].x = sprite[index].x + 0.06f;            
				points[point_index+2].y = sprite[index].y + 0.27f;
			}  

		}   

		if(sprite[index].movement == LEFT) 
		{
			if(player == 1)
				VG_1_OFFSET *= -1.0f; 
			else
				VG_2_OFFSET *= -1.0f;
		}
	}  
	if(sprite[index].status == VG_UPPERCUT_FONT)     
	{
		      
		if(points[point_index].active != 2)
			points[point_index].active = 0;     
			    

		if(sprite[index].cur == 1)  
		{
			if(player == 1)
				VG_1_OFFSET = 0.06f;
			else
				VG_2_OFFSET = 0.06f;   
		}	
		if(sprite[index].cur == 2)     
		{    
			VG_Play_Sound(player, VG_SOUND_CHOP); 

			if(points[point_index].active != 2)   
				points[point_index].active = 1;  
			      
			if(sprite[index].movement == RIGHT)       
			{  
				points[point_index].x = sprite[index].x + 0.42f;           
				points[point_index].y = sprite[index].y + 0.36f;
				points[point_index+2].x = sprite[index].x + 0.32f;            
				points[point_index+2].y = sprite[index].y + 0.32f;
			} 
			if(sprite[index].movement == LEFT) 
			{ 
				points[point_index].x = sprite[index].x - 0.01f;          
				points[point_index].y = sprite[index].y + 0.36f;
				points[point_index+2].x = sprite[index].x + 0.09f;       
				points[point_index+2].y = sprite[index].y + 0.32f;
			}   

			if(player == 1)
				VG_1_OFFSET = 0.10f;
			else
				VG_2_OFFSET = 0.10f;  

		}

		if(sprite[index].cur == 3)
		{
			if(player == 1)
				VG_1_OFFSET = 0.06f;
			else
				VG_2_OFFSET = 0.06f;  
		}	

		if(sprite[index].movement == LEFT) 
		{
			if(player == 1)
				VG_1_OFFSET *= -1.0f;
			else
				VG_2_OFFSET *= -1.0f;
		} 

	} 
	if(sprite[index].status == VG_SECOND_STRIKE)     
	{
		sprite[index].spin_strafe = true; 

		if(points[point_index].active != 2)	     
			points[point_index].active = 0;    

		if(sprite[index].cur == 0)         
		{    
			if(player == 1)
				VG_1_OFFSET = 0.06f;
			else 
				VG_2_OFFSET = 0.06f;

			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2)   
				points[point_index].active = 1;   
			      
			if(sprite[index].movement == RIGHT)    
			{
				points[point_index].x = sprite[index].x + 0.50f;          
				points[point_index].y = sprite[index].y + 0.12f;
				points[point_index+2].x = sprite[index].x + 0.30f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}   
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x - 0.10f;          
				points[point_index].y = sprite[index].y + 0.12f;
				points[point_index+2].x = sprite[index].x + 0.10f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}  
			  
		}            

		if(sprite[index].movement == LEFT) 
		{
			if(player == 1)
				VG_1_OFFSET *= -1.0f;
			else
				VG_2_OFFSET *= -1.0f;
		}

	} 
	if(sprite[index].status == VG_THIRD_STRIKE)       
	{

		sprite[index].spin_strafe = true;

		if(points[point_index].active != 2)	     
			points[point_index].active = 0;    

		if(sprite[index].cur == 0) 
		{
			if(player == 1)
				VG_1_OFFSET = 0.06f;
			else 
				VG_2_OFFSET = 0.06f;

			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2)   
				points[point_index].active = 1;   
			      
			if(sprite[index].movement == RIGHT)    
			{
				points[point_index].x = sprite[index].x + 0.50f;          
				points[point_index].y = sprite[index].y + 0.12f;
				points[point_index+2].x = sprite[index].x + 0.30f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}   
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x - 0.10f;          
				points[point_index].y = sprite[index].y + 0.12f;
				points[point_index+2].x = sprite[index].x + 0.10f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}  
		}

		if(sprite[index].cur == 1)         
		{    
			if(player == 1)
				VG_1_OFFSET = 0.06f;
			else 
				VG_2_OFFSET = 0.06f;

			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2)  
				points[point_index].active = 1;   
			     
			if(sprite[index].movement == RIGHT)    
			{
				points[point_index].x = sprite[index].x + 0.50f;          
				points[point_index].y = sprite[index].y + 0.32f;
				points[point_index+2].x = sprite[index].x + 0.30f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}   
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x - 0.10f;          
				points[point_index].y = sprite[index].y + 0.32f;
				points[point_index+2].x = sprite[index].x + 0.10f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}  
			  
		}           

		if(sprite[index].cur == 2)    
		{
			if(player == 1)
				VG_1_OFFSET = 0.06f;
			else 
				VG_2_OFFSET = 0.06f;

			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2)   
				points[point_index].active = 1;   
			      
			if(sprite[index].movement == RIGHT)    
			{
				points[point_index].x = sprite[index].x + 0.50f;          
				points[point_index].y = sprite[index].y + 0.12f;
				points[point_index+2].x = sprite[index].x + 0.30f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}   
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x - 0.10f;          
				points[point_index].y = sprite[index].y + 0.12f;
				points[point_index+2].x = sprite[index].x + 0.10f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}         
		}

		if(sprite[index].cur == 3)          
		{    
			if(player == 1)
				VG_1_OFFSET = 0.06f;
			else 
				VG_2_OFFSET = 0.06f;
			 
			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2)  
				points[point_index].active = 1;   
			     
			if(sprite[index].movement == RIGHT)    
			{
				points[point_index].x = sprite[index].x + 0.50f;          
				points[point_index].y = sprite[index].y + 0.32f;
				points[point_index+2].x = sprite[index].x + 0.30f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}   
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x - 0.10f;          
				points[point_index].y = sprite[index].y + 0.32f;
				points[point_index+2].x = sprite[index].x + 0.10f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}  
			  
		}           

		if(sprite[index].cur == 4)    
		{
			if(player == 1)
				VG_1_OFFSET = 0.06f;
			else 
				VG_2_OFFSET = 0.06f;

			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2)   
				points[point_index].active = 1;   
			      
			if(sprite[index].movement == RIGHT)    
			{
				points[point_index].x = sprite[index].x + 0.50f;          
				points[point_index].y = sprite[index].y + 0.12f;
				points[point_index+2].x = sprite[index].x + 0.30f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}   
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x - 0.10f;          
				points[point_index].y = sprite[index].y + 0.12f;
				points[point_index+2].x = sprite[index].x + 0.10f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}         
		}
		if(sprite[index].movement == LEFT)  
		{
			if(player == 1)
				VG_1_OFFSET *= -1.0f;
			else
				VG_2_OFFSET *= -1.0f;
		}

	} 
	if(sprite[index].status == VG_KICK_KNEE_FONT)     
	{
		if(points[point_index].active != 2)	     
			points[point_index].active = 0;    

		if(sprite[index].cur == 0) 
		{
			if(player == 1)
				VG_1_OFFSET = 0.06f;
			else
				VG_2_OFFSET = 0.06f;
		}

		if(sprite[index].cur == 1)         
		{    
			if(player == 1)
				VG_1_OFFSET = 0.12f;
			else 
				VG_2_OFFSET = 0.12f;

			VG_Play_Sound(player, VG_SOUND_CHOP); 

			if(points[point_index].active != 2)   
				points[point_index].active = 1;   
			      
			if(sprite[index].movement == RIGHT)    
			{
				points[point_index].x = sprite[index].x + 0.50f;          
				points[point_index].y = sprite[index].y + 0.12f;
				points[point_index+2].x = sprite[index].x + 0.30f;          
				points[point_index+2].y = sprite[index].y + 0.22f;
			}   
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x - 0.10f;          
				points[point_index].y = sprite[index].y + 0.12f;
				points[point_index+2].x = sprite[index].x + 0.10f;          
				points[point_index+2].y = sprite[index].y + 0.22f;
			}  
			  
		}           

		if(sprite[index].cur == 2)    
		{
			if(player == 1)
				VG_1_OFFSET = 0.06f;
			else
				VG_2_OFFSET = 0.06f;      
		}

		if(sprite[index].movement == LEFT) 
		{
			if(player == 1)
				VG_1_OFFSET *= -1.0f;
			else
				VG_2_OFFSET *= -1.0f;
		}

	} 
	if(sprite[index].status == VG_KICK_SHORT_FONT)     
	{
		       
		if(points[point_index].active != 2) 
			points[point_index].active = 0;     
			    
		if(sprite[index].cur == 1)       
		{   
			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2)    
				points[point_index].active = 1;  
			  
			if(sprite[index].movement == RIGHT)  
			{
				points[point_index].x = sprite[index].x + 0.32f;           
				points[point_index].y = sprite[index].y + 0.24f;  
				points[point_index+2].x = sprite[index].x + 0.24f;           
				points[point_index+2].y = sprite[index].y + 0.22f;
			} 
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x + 0.08f;            
				points[point_index].y = sprite[index].y + 0.24f;
				points[point_index+2].x = sprite[index].x + 0.16f;          
				points[point_index+2].y = sprite[index].y + 0.22f;
			}   

		}    

	}  
	if(sprite[index].status == VG_KICK_LONG_FONT)       
	{
		if(points[point_index].active != 2)	     
			points[point_index].active = 0;    

		if(sprite[index].cur == 0) 
		{
			if(player == 1)
				VG_1_OFFSET = 0.06f;
			else
				VG_2_OFFSET = 0.06f;
		}

		if(sprite[index].cur == 1)         
		{    
			if(player == 1)
				VG_1_OFFSET = 0.12f;
			else 
				VG_2_OFFSET = 0.12f;

			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2)  
				points[point_index].active = 1;   
			     
			if(sprite[index].movement == RIGHT)    
			{
				points[point_index].x = sprite[index].x + 0.50f;          
				points[point_index].y = sprite[index].y + 0.32f;
				points[point_index+2].x = sprite[index].x + 0.30f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}   
			if(sprite[index].movement == LEFT)
			{
				points[point_index].x = sprite[index].x - 0.10f;          
				points[point_index].y = sprite[index].y + 0.32f;
				points[point_index+2].x = sprite[index].x + 0.10f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}  
			  
		}           

		if(sprite[index].cur == 2)    
		{
			if(player == 1)
				VG_1_OFFSET = 0.06f;
			else
				VG_2_OFFSET = 0.06f;      
		}

		if(sprite[index].movement == LEFT) 
		{
			if(player == 1)
				VG_1_OFFSET *= -1.0f;
			else
				VG_2_OFFSET *= -1.0f;
		}

	} 
	if(sprite[index].status == VG_JUMPING_KICK_FONT)      
	{
		if(points[point_index].active != 2)  
			points[point_index].active = 0;      
			     
		if(sprite[index].cur == 1)       
		{   
			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2) 
				points[point_index].active = 1;  
			   
			if(sprite[index].movement == RIGHT)     
			{ 
				points[point_index].x = sprite[index].x + 0.41f;          
				points[point_index].y = sprite[index].y + 0.10f;
				points[point_index+2].x = sprite[index].x + 0.20f;          
				points[point_index+2].y = sprite[index].y + 0.23f;
			}  
			if(sprite[index].movement == LEFT)  
			{
				points[point_index].x = sprite[index].x - 0.01f;           
				points[point_index].y = sprite[index].y + 0.10f;
				points[point_index+2].x = sprite[index].x + 0.20f;          
				points[point_index+2].y = sprite[index].y + 0.23f;

			}    
			  
			if(player == 1)
				VG_1_OFFSET = 0.04f;
			else
				VG_2_OFFSET = 0.04f;  			 
		}    

		if(sprite[index].movement == LEFT) 
		{
			if(player == 1)
				VG_1_OFFSET *= -1.0f;
			else
				VG_2_OFFSET *= -1.0f;
		}
	} 
	if(sprite[index].status == VG_JUMPING_KICK_SHORT_FONT)      
	{
		if(points[point_index].active != 2)  
			points[point_index].active = 0;      
			   
		if(sprite[index].cur == 0)      
		{   
			VG_Play_Sound(player, VG_SOUND_CHOP);
			 
			if(points[point_index].active != 2) 
				points[point_index].active = 1;      
			     
			if(sprite[index].movement == RIGHT)    
			{ 
				points[point_index].x = sprite[index].x + 0.30f;          
				points[point_index].y = sprite[index].y + 0.22f;
				points[point_index+2].x = sprite[index].x + 0.20f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}  
			if(sprite[index].movement == LEFT)
			{   
				points[point_index].x = sprite[index].x + 0.10f;          
				points[point_index].y = sprite[index].y + 0.22f;
				points[point_index+2].x = sprite[index].x + 0.20f;          
				points[point_index+2].y = sprite[index].y + 0.20f;
			}  
			 
		}   
	} 
	if(sprite[index].status == VG_JUMPING_PUNCH_FONT)       
	{
		if(points[point_index].active != 2)  
			points[point_index].active = 0;      
			   
		if(sprite[index].cur == 0)      
		{   
			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2)     
				points[point_index].active = 1;   
			    
			if(sprite[index].movement == RIGHT)     
			{ 
				points[point_index].x = sprite[index].x + 0.40f;          
				points[point_index].y = sprite[index].y + 0.32f;
				points[point_index+2].x = sprite[index].x + 0.30f;          
				points[point_index+2].y = sprite[index].y + 0.32f;
			}  
			if(sprite[index].movement == LEFT) 
			{
				points[point_index].x = sprite[index].x + 0.00f;            
				points[point_index].y = sprite[index].y + 0.32f;
				points[point_index+2].x = sprite[index].x + 0.12f;          
				points[point_index+2].y = sprite[index].y + 0.32f;
			}    
			 
		}   
	} 
	if(sprite[index].status == VG_JUMPING_PUNCH_SHORT_FONT)       
	{
		if(points[point_index].active != 2)  
			points[point_index].active = 0;       
			   
		if(sprite[index].cur == 0)      
		{   
			VG_Play_Sound(player, VG_SOUND_CHOP);

			if(points[point_index].active != 2)     
				points[point_index].active = 1;      
			  
			if(sprite[index].movement == RIGHT)      
			{ 
				points[point_index].x = sprite[index].x + 0.34f;          
				points[point_index].y = sprite[index].y + 0.24f;
				points[point_index+2].x = sprite[index].x + 0.30f;          
				points[point_index+2].y = sprite[index].y + 0.26f;
			}  
			if(sprite[index].movement == LEFT)
			{   
				points[point_index].x = sprite[index].x + 0.06f;          
				points[point_index].y = sprite[index].y + 0.24f;
				points[point_index+2].x = sprite[index].x + 0.10f;          
				points[point_index+2].y = sprite[index].y + 0.26f;
			}    
			 
		}   
	} 
	if(sprite[index].status == VG_KNOCKSLIDE_FONT)      
	{
		temp_speed = 0.0f;    

		if(player == 1)
			VG_SHAKE_1 = false;
		else
			VG_SHAKE_2 = false;

		if(sprite[index].cur == 0)      
			temp_speed = ((VG_KNOCKSLIDE_SPEED_HIGH/VG_slowmof)*(float)f_rate); 

		if(sprite[index].cur == 1)     
		{
			temp_speed = ((VG_KNOCKSLIDE_SPEED_SLOW/VG_slowmof)*(float)f_rate); 
		}
		 
		if(player == 1) 
		if((int)TimerGetTime() > VG_1_GLOBAL_DUST_TIMER) 
		{ 
			VG_dust_effect(VG_CURRENT_CHAR, index, sprite[index].movement);
			VG_1_GLOBAL_DUST_TIMER = (int)TimerGetTime() + VG_GLOBAL_DUST_LENGTH;
		}
		if(player == 2) 
		if((int)TimerGetTime() > VG_2_GLOBAL_DUST_TIMER) 
		{ 
			VG_dust_effect(VG_CURRENT_CHAR, index, sprite[index].movement);
			VG_2_GLOBAL_DUST_TIMER = (int)TimerGetTime() + VG_GLOBAL_DUST_LENGTH;
		}

		if(sprite[index].hit_direction == RIGHT) 
		if(distance < screen_limit || sprite[index].x < sprite[other_index].x)
		{
			sprite[index].x += temp_speed;  
			sprite[index].w += temp_speed; 
		}
		if(sprite[index].hit_direction == LEFT)
		if(distance < screen_limit || sprite[index].x > sprite[other_index].x)
		{
			sprite[index].x -= temp_speed;  
			sprite[index].w -= temp_speed; 
		}

	}
	if(sprite[index].status == VG_HIT_IN_FACE_FONT)      
	{
		temp_speed = 0.0f;  

		if(player == 1)
			VG_SHAKE_1 = false;
		else
			VG_SHAKE_2 = false; 

		if(sprite[index].cur == 0)       
		{  
			if(player == 1)
				VG_SHAKE_1 = true;
			else
				VG_SHAKE_2 = true; 
		}   
		      
		if(sprite[index].cur == 1)       
			temp_speed = ((0.00100f/VG_slowmof)*(float)f_rate); 

		if(sprite[index].cur == 2)     
			temp_speed = ((0.00060f/VG_slowmof)*(float)f_rate); 
		
		if(VG_CORNERED == true && VG_CORNER_SLIDEBACK == 1)
		{
			if(sprite[index].hit_by_bullet == false) 
			{
				if(sprite[index].hit_direction == LEFT && sprite[other_index].direction != RIGHT) 
				if(distance < screen_limit || sprite[index].x < sprite[other_index].x)
				{
					sprite[other_index].x += (temp_speed*0.8f);  
					sprite[other_index].w += (temp_speed*0.8f);  
				}
				if(sprite[index].hit_direction == RIGHT && sprite[other_index].direction != LEFT) 
				if(distance < screen_limit || sprite[index].x > sprite[other_index].x)
				{
					sprite[other_index].x -= (temp_speed*0.8f);  
					sprite[other_index].w -= (temp_speed*0.8f);  
				}
			}
		}
		else
		{
			if(sprite[index].hit_direction == RIGHT) 
			if(distance < screen_limit || sprite[index].x < sprite[other_index].x)
			{
				sprite[index].x += temp_speed;  
				sprite[index].w += temp_speed; 
			}
			if(sprite[index].hit_direction == LEFT)
			if(distance < screen_limit || sprite[index].x > sprite[other_index].x)
			{
				sprite[index].x -= temp_speed;  
				sprite[index].w -= temp_speed; 
			}
		}
	}
	if(sprite[index].status == VG_HIT_IN_BODY_FONT)      
	{
		temp_speed = 0.0f;  

		if(player == 1)
			VG_SHAKE_1 = false;
		else
			VG_SHAKE_2 = false;

		if(sprite[index].cur == 0)         
		{       
			if(player == 1) 
				VG_SHAKE_1 = true;
			else 
				VG_SHAKE_2 = true;
		}      
		 
		if(sprite[index].cur == 1)       
			temp_speed = ((0.00150f/VG_slowmof)*(float)f_rate); 

		if(sprite[index].cur == 2)     
			temp_speed = ((0.00075f/VG_slowmof)*(float)f_rate); 

		if(VG_CORNERED == true && VG_CORNER_SLIDEBACK == 1)
		{
			if(sprite[index].hit_by_bullet == false) 
			{
				if(sprite[index].hit_direction == LEFT && sprite[other_index].direction != RIGHT) 
				if(distance < screen_limit || sprite[index].x < sprite[other_index].x)
				{
					sprite[other_index].x += (temp_speed*0.8f);  
					sprite[other_index].w += (temp_speed*0.8f);  
				}
				if(sprite[index].hit_direction == RIGHT && sprite[other_index].direction != LEFT) 
				if(distance < screen_limit || sprite[index].x > sprite[other_index].x)
				{
					sprite[other_index].x -= (temp_speed*0.8f);  
					sprite[other_index].w -= (temp_speed*0.8f);  
				}
			}
		}
		else
		{
			if(sprite[index].hit_direction == RIGHT) 
			if(distance < screen_limit || sprite[index].x < sprite[other_index].x)
			{
				sprite[index].x += temp_speed;  
				sprite[index].w += temp_speed; 
			}
			if(sprite[index].hit_direction == LEFT)
			if(distance < screen_limit || sprite[index].x > sprite[other_index].x)
			{
				sprite[index].x -= temp_speed;  
				sprite[index].w -= temp_speed; 
			}
		}
	}
	if(sprite[index].status == VG_BLOCK_FONT || sprite[index].status == VG_BLOCKDOWN_FONT )       
	{
		temp_speed = 0.0f;     
	  
		// Slide back attacker 
		temp_speed = ((0.00050f/VG_slowmof)*(float)f_rate); 

		if(VG_CORNERED == true && VG_CORNER_SLIDEBACK == 1) 
		{  
			if(sprite[index].hit_by_bullet == false) 
			{
				if(sprite[index].hit_direction == LEFT && sprite[other_index].direction != RIGHT) 
				if(distance < screen_limit || sprite[index].x < sprite[other_index].x)
				{
					sprite[other_index].x += (temp_speed*0.8f);  
					sprite[other_index].w += (temp_speed*0.8f);  
				}
				if(sprite[index].hit_direction == RIGHT && sprite[other_index].direction != LEFT) 
				if(distance < screen_limit || sprite[index].x > sprite[other_index].x)
				{
					sprite[other_index].x -= (temp_speed*0.8f);  
					sprite[other_index].w -= (temp_speed*0.8f);  
				}
			}
		}
		else
		{
			if(sprite[index].hit_direction == RIGHT) 
			if(distance < screen_limit || sprite[index].x < sprite[other_index].x)
			{
				sprite[index].x += temp_speed;  
				sprite[index].w += temp_speed; 
			}
			if(sprite[index].hit_direction == LEFT)
			if(distance < screen_limit || sprite[index].x > sprite[other_index].x)
			{
				sprite[index].x -= temp_speed;  
				sprite[index].w -= temp_speed; 
			}
		}

	}

} 
