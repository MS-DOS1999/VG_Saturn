#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64  
#define WIN32_LEAN_AND_MEAN    
#include <windows.h>
#endif     
  
#define HANDCUFF_COP_TIME 3250 
#define HANDCUFF_TIME 5000

extern void Set_Vibration(int player, int left, int right, int time);
void VG_Play_Sound(int player, int sound);
extern void VG_SlowMO(int duration, float strength);
extern void VG_Restrain_sprite(int index, int j);

extern void Animate(int loop, int type);
extern void Run_Moves_GYEONG(int player, int f_rate);
extern void Run_Moves_GUN(int player, int f_rate);  
extern void Run_Moves_JAE(int player, int f_rate);
extern void Run_Moves_MINSO(int player, int f_rate);
extern void Run_Moves_HYUK(int player, int f_rate);
extern void Run_Moves_SIU(int player, int f_rate);
extern void Run_Moves_REESE(int player, int f_rate);
extern void Run_Moves_YOHAN(int player, int f_rate);
extern void Run_Moves_SANG(int player, int f_rate);
extern void Run_Moves_TRAINER(int player, int f_rate);

void Run_Throws(int player, int f_rate)
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
	int move_anim = 0;
	bool VG_MOVE_ACTIVE=false;
	int bullet_anim = 0; 
	bool VG_reload_gun=false;
	int VG_CURRENT_CHAR=0; 
	float diff_x = 0.0f;
	int VG_THROWING_SEQUENCE = 0;
	bool VG_THROWING = false;
	bool VG_OTHER_CORNERED = false;
	int other_player = 0;
	int VG_DAMAGE = 0;
	int VG_CHARACTER=0;
	int j = 0;
                   
	if(f_rate <= 0)                                                
	    f_rate = 1;        

	if(f_rate >= 50)
		f_rate = 50; 

	if(VG_1_THROWING == true) 
	{
		VG_CHARACTER = VG_1_CHARACTER;
		other_player = 2;
		VG_THROWING = VG_1_THROWING;
		index = 2;
		other_index = 3;
		VG_THROWING_SEQUENCE = VG_1_THROWING_SEQUENCE;
		VG_OTHER_CORNERED = VG_2_CORNERED;
	}
	if(VG_2_THROWING == true) 
	{
		VG_CHARACTER = VG_2_CHARACTER;
		other_player = 1; 
		VG_THROWING = VG_2_THROWING;
		index = 3;
		other_index = 2;
		VG_THROWING_SEQUENCE = VG_2_THROWING_SEQUENCE;
		VG_OTHER_CORNERED = VG_1_CORNERED;
	}
	 
	if(VG_THROWING == true)   
	{  
		  
		VG_slowmo_timer = 0;
		VG_slowmof = 1.0f;   

		VG_Reset_all_anims();
		VG_SLOWMO = false;  
		 
		// Make sure both characters are standing on the floor...
		if(VG_THROWING_SEQUENCE == 0)
		{
			inc_y = sprite[2].z - sprite[2].y;
			sprite[2].y = VG_START_Y; 
			sprite[2].z = sprite[2].y + inc_y;

			inc_y = sprite[3].z - sprite[3].y;
			sprite[3].y = VG_START_Y;
			sprite[3].z = sprite[3].y + inc_y;
			 
			if(VG_1_THROWING == true)  
			if(VG_1_HAS_THROW == true) 
			{
		        if(VG_1_CHARACTER == VG_GYEONG || VG_1_CHARACTER == VG_SIU || VG_1_CHARACTER == VG_MINSO || VG_1_CHARACTER == VG_REESE || VG_1_CHARACTER == VG_SANG || VG_1_CHARACTER == VG_TRAINER || VG_1_CHARACTER == VG_SHO || VG_1_CHARACTER == VG_TIA || VG_1_CHARACTER == VG_SAIZO)
				{
					sprite[3].handcuffed = true;
					VG_2_HANDCUFFED_TIMER = (int)TimerGetTime() + HANDCUFF_COP_TIME;
				}
				else
				{
					if(VG_CHARACTER == VG_JAE || VG_CHARACTER == VG_GUN || VG_CHARACTER == VG_KENNEDY)
					{
						sprite[3].dizzy = true;
						VG_2_DIZZY_TIMER = (int)TimerGetTime() + HANDCUFF_TIME;
					}
					if(VG_CHARACTER == VG_YOHAN || VG_CHARACTER == VG_HYUK)
					{
						sprite[3].dizzy = true;
						VG_2_STICKY_TIMER = (int)TimerGetTime() + HANDCUFF_TIME;
					}
				}


			}

			if(VG_2_THROWING == true)
			if(VG_2_HAS_THROW == true)
			{
		        if(VG_2_CHARACTER == VG_GYEONG || VG_2_CHARACTER == VG_SIU || VG_2_CHARACTER == VG_MINSO || VG_2_CHARACTER == VG_REESE || VG_2_CHARACTER == VG_SANG || VG_2_CHARACTER == VG_TRAINER || VG_2_CHARACTER == VG_SHO || VG_2_CHARACTER == VG_TIA || VG_2_CHARACTER == VG_SAIZO)
				{
					sprite[2].handcuffed = true;
					VG_1_HANDCUFFED_TIMER = (int)TimerGetTime() + HANDCUFF_COP_TIME;
				}
				else
				{
					if(VG_CHARACTER == VG_JAE || VG_CHARACTER == VG_GUN || VG_CHARACTER == VG_KENNEDY)
					{
						sprite[2].dizzy = true;
						VG_1_DIZZY_TIMER = (int)TimerGetTime() + HANDCUFF_TIME;
					}
					if(VG_CHARACTER == VG_YOHAN || VG_CHARACTER == VG_HYUK)
					{
						sprite[2].dizzy = true;
						VG_1_STICKY_TIMER = (int)TimerGetTime() + HANDCUFF_TIME;
					}
				}
			}
		}

		VG_1_MOVE_ACTIVE = false;
		VG_2_MOVE_ACTIVE = false;

		if(VG_THROWING_SEQUENCE == 0) 
		if(VG_1_THROWING == true)
		{ 
			Set_Sprite(index, 47, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Moving around...
			Set_Sprite(other_index, 49, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Held down...
		}
		else
		{
			Set_Sprite(index, 48, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Moving around...
			Set_Sprite(other_index, 49, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Held down...
		}

		temp_speed = ((0.00050f/VG_slowmof)*(float)f_rate); 

		// Get distance for converting to short punches...
		mid_x = sprite[index].x + sprite[index].width/2;     
		tar_x = sprite[other_index].x + sprite[other_index].width/2;  

		distance = Node_Distance1(mid_x, VG_START_Y, tar_x, VG_START_Y);

		diff_x = sprite[index].w - sprite[index].x;

		// Moving into position...
		if(VG_THROWING_SEQUENCE == 0)
		if(sprite[index].movement == RIGHT)      
		if(sprite[index].w < sprite[other_index].w + sprite[other_index].box_width ) // distance < screen_limit && 
		{
			sprite[index].x += temp_speed;   
			sprite[index].w += temp_speed; 
			sprite[other_index].x -= temp_speed;   
			sprite[other_index].w -= temp_speed; 
		} 
		else
		{
			if(VG_1_THROWING == true)
				VG_1_THROWING_SEQUENCE = 1;
			else 
				VG_2_THROWING_SEQUENCE = 1;
			 
			sprite[index].movement = LEFT;
			sprite[index].direction = LEFT;

			sprite[other_index].movement = LEFT;
			sprite[other_index].direction = LEFT;

			sprite[index].w = sprite[other_index].w + sprite[other_index].box_width;   
			sprite[index].x = sprite[index].w - diff_x; 

		//	sprite[other_index].w = sprite[index].w - sprite[index].box_width;   
		//	sprite[other_index].x = sprite[other_index].w - diff_x; 

		} 

		// Moving into position...
		if(VG_THROWING_SEQUENCE == 0)
		if(sprite[index].movement == LEFT)
		if(sprite[index].w + sprite[index].box_width > sprite[other_index].w) // distance < screen_limit && 
		{
			sprite[index].x -= temp_speed;  
			sprite[index].w -= temp_speed;  
			sprite[other_index].x += temp_speed;   
			sprite[other_index].w += temp_speed;

		}
		else
		{
			if(VG_1_THROWING == true) 
				VG_1_THROWING_SEQUENCE = 1; 
			else 
				VG_2_THROWING_SEQUENCE = 1; 

			sprite[index].movement = RIGHT; 
			sprite[index].direction = RIGHT; 

			sprite[other_index].movement = RIGHT;
			sprite[other_index].direction = RIGHT;

			sprite[index].w = sprite[other_index].w - sprite[index].box_width;   
			sprite[index].x = sprite[index].w - diff_x; 

		//	sprite[other_index].w = sprite[index].w + sprite[index].box_width;   
		//	sprite[other_index].x = sprite[other_index].w - diff_x; 
		}

		VG_Restrain_sprite(2, 0);
		VG_Restrain_sprite(3, 1);
				     
		// Executing throw...
		if(VG_THROWING_SEQUENCE == 1)     
		{          
			if(VG_1_THROWING == true)     
			{  
				if(VG_1_HAS_THROW == true)
					Set_Sprite(index, 50, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // Handcuff anim...
				else
					Set_Sprite(index, 64, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // Normal Throw anim...

				VG_1_THROWING_SEQUENCE = 2;

				if(VG_1_HAS_THROW == true)
				{
					if(VG_CHARACTER == VG_JAE || VG_CHARACTER == VG_GUN || VG_CHARACTER == VG_KENNEDY)
					{
						VG_handcuffs_sfx = true;
						VG_2_DIZZY_TIMER = (int)TimerGetTime() + HANDCUFF_TIME;

						if(VG_2_CHARACTER == VG_KENNEDY)
							VG_2_DIZZY_TIMER = (int)TimerGetTime() + 1000;
					}
					if(VG_CHARACTER == VG_YOHAN || VG_CHARACTER == VG_HYUK)
					{
						VG_handcuffs_sfx = true;
						VG_2_STICKY_TIMER = (int)TimerGetTime() + HANDCUFF_TIME;
					}
					if(VG_CHARACTER == VG_GYEONG || VG_CHARACTER == VG_SIU || VG_CHARACTER == VG_MINSO || VG_CHARACTER == VG_REESE || VG_CHARACTER == VG_SANG || VG_CHARACTER == VG_TRAINER || VG_CHARACTER == VG_SHO || VG_CHARACTER == VG_TIA || VG_CHARACTER == VG_SAIZO)
					{
						VG_handcuffs_sfx = true;
						VG_2_HANDCUFFED_TIMER = (int)TimerGetTime() + HANDCUFF_COP_TIME;

						if(VG_2_CHARACTER == VG_KENNEDY)
							VG_2_HANDCUFFED_TIMER = (int)TimerGetTime() + 1000;
					}
				}
			} 
			else
			{
				if(VG_2_HAS_THROW == true)
					Set_Sprite(index, 50, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // Handcuff anim...
				else
					Set_Sprite(index, 64, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // Normal Throw anim...

				VG_2_THROWING_SEQUENCE = 2;

				if(VG_2_HAS_THROW == true)
				{
					if(VG_CHARACTER == VG_JAE || VG_CHARACTER == VG_GUN || VG_CHARACTER == VG_KENNEDY)
					{
						VG_handcuffs_sfx = true;
						VG_1_DIZZY_TIMER = (int)TimerGetTime() + HANDCUFF_TIME;

						if(VG_1_CHARACTER == VG_KENNEDY)
							VG_1_DIZZY_TIMER = (int)TimerGetTime() + 1000;
					}
					if(VG_CHARACTER == VG_YOHAN || VG_CHARACTER == VG_HYUK)
					{
						VG_handcuffs_sfx = true;
						VG_1_STICKY_TIMER = (int)TimerGetTime() + HANDCUFF_TIME;
					}
					if(VG_CHARACTER == VG_GYEONG || VG_CHARACTER == VG_SIU || VG_CHARACTER == VG_MINSO || VG_CHARACTER == VG_REESE || VG_CHARACTER == VG_SANG || VG_CHARACTER == VG_TRAINER || VG_CHARACTER == VG_SHO || VG_CHARACTER == VG_TIA || VG_CHARACTER == VG_SAIZO)
					{
						VG_handcuffs_sfx = true;
						VG_1_HANDCUFFED_TIMER = (int)TimerGetTime() + HANDCUFF_COP_TIME;

						if(VG_1_CHARACTER == VG_KENNEDY)
							VG_1_HANDCUFFED_TIMER = (int)TimerGetTime() + 1000;

					}
				}
			} 

			if(VG_CHARACTER == VG_JAE || VG_CHARACTER == VG_GUN  || VG_CHARACTER == VG_KENNEDY)
			{ 
				if(VG_1_THROWING == true)     
				{ 
					if(VG_1_HAS_THROW == true)  
					{
						sprite[other_index].dizzy = true;
					}
				}
				if(VG_2_THROWING == true)
				{
					if(VG_2_HAS_THROW == true)
					{
						sprite[other_index].dizzy = true;
					}
				}
				 
			}
			if(VG_CHARACTER == VG_YOHAN || VG_CHARACTER == VG_HYUK)
			{ 
				if(VG_1_THROWING == true)     
				{ 
					if(VG_1_HAS_THROW == true)  
					{
						sprite[other_index].sticky = true;
					}
				}
				if(VG_2_THROWING == true)
				{
					if(VG_2_HAS_THROW == true)
					{
						sprite[other_index].sticky = true;
					}
				}
				  
			}
			if(VG_CHARACTER == VG_GYEONG || VG_CHARACTER == VG_SIU || VG_CHARACTER == VG_MINSO || VG_CHARACTER == VG_REESE || VG_CHARACTER == VG_SANG || VG_CHARACTER == VG_TRAINER || VG_CHARACTER == VG_SHO || VG_CHARACTER == VG_TIA || VG_CHARACTER == VG_SAIZO)
			{
				if(VG_1_THROWING == true)
				{
					if(VG_1_HAS_THROW == true)
						sprite[other_index].handcuffed = true;
				}
				if(VG_2_THROWING == true)
				{
					if(VG_2_HAS_THROW == true)
						sprite[other_index].handcuffed = true;
				}
				 
			}
			 
		} 
		if(VG_1_THROWING_SEQUENCE == 2 || VG_2_THROWING_SEQUENCE == 2)  
		{        
			if(sprite[index].anim_state == NO_ANIM)
			{  
				 
				if(VG_CHARACTER == VG_JAE || VG_CHARACTER == VG_GUN || VG_CHARACTER == VG_KENNEDY)
				{
					if(VG_1_THROWING == true && VG_1_HAS_THROW == true)
						New_FX(sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, 1, LOOP, sprite[other_index].width/2,sprite[other_index].height/2, sprite[other_index].width/2,sprite[other_index].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH, other_index, 28, 0, 0, other_index); // FX_VG_ATTACH
					if(VG_2_THROWING == true && VG_2_HAS_THROW == true)
						New_FX(sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, 1, LOOP, sprite[other_index].width/2,sprite[other_index].height/2, sprite[other_index].width/2,sprite[other_index].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH, other_index, 28, 0, 0, other_index); // FX_VG_ATTACH
				}
				if(VG_CHARACTER == VG_YOHAN || VG_CHARACTER == VG_HYUK)
				{ 
					if(VG_1_THROWING == true && VG_1_HAS_THROW == true)
					{  
						if(VG_CHARACTER == VG_YOHAN) 
							New_FX(sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, 24, LOOP, sprite[other_index].width/4,sprite[other_index].height/4, sprite[other_index].width/4,sprite[other_index].height/4, 2, GFX, 1.0f, 0, -1, FX_VG_STICKYB, other_index, 12, 14, 0, other_index); // FX_VG_ATTACH
						if(VG_CHARACTER == VG_HYUK)
							New_FX(sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, 24, LOOP, sprite[other_index].width/4,sprite[other_index].height/4, sprite[other_index].width/4,sprite[other_index].height/4, 2, GFX, 1.0f, 0, -1, FX_VG_STICKYG, other_index, 12,  9, 0, other_index); // FX_VG_ATTACH
					}
					if(VG_2_THROWING == true && VG_2_HAS_THROW == true)
					{
						if(VG_CHARACTER == VG_YOHAN)
							New_FX(sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, 24, LOOP, sprite[other_index].width/4,sprite[other_index].height/4, sprite[other_index].width/4,sprite[other_index].height/4, 2, GFX, 1.0f, 0, -1, FX_VG_STICKYB, other_index, 12, 14, 0, other_index); // FX_VG_ATTACH
						if(VG_CHARACTER == VG_HYUK)
							New_FX(sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, 24, LOOP, sprite[other_index].width/4,sprite[other_index].height/4, sprite[other_index].width/4,sprite[other_index].height/4, 2, GFX, 1.0f, 0, -1, FX_VG_STICKYG, other_index, 12,  9, 0, other_index); // FX_VG_ATTACH
					}
				}
			/*	if(VG_CHARACTER == VG_GYEONG || VG_CHARACTER == VG_SIU || VG_CHARACTER == VG_MINSO || VG_CHARACTER == VG_REESE || VG_CHARACTER == VG_SANG)
				{
					if(VG_1_THROWING == true && VG_1_HAS_THROW == true)
						New_FX(sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, 2, LOOP, sprite[other_index].width/2,sprite[other_index].height/2, sprite[other_index].width/2,sprite[other_index].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, other_index, 28, 0, 0, other_index); // FX_VG_ATTACH
					if(VG_2_THROWING == true && VG_2_HAS_THROW == true)
						New_FX(sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, sprite[other_index].x+0.1f, sprite[other_index].y+0.2f, 2, LOOP, sprite[other_index].width/2,sprite[other_index].height/2, sprite[other_index].width/2,sprite[other_index].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, other_index, 28, 0, 0, other_index); // FX_VG_ATTACH
				}
			*/
				// Reset index sprite...  
				sprite[index].status = -1; 
				sprite[index].hit_opponent = false;  

				sprite[index].special = 0;

				sprite[index].pain = false;    
				sprite[index].status = -1;  
				sprite[index].anim_state = WAIT;

				VG_1_MOVE_ACTIVE = false; 
				VG_2_MOVE_ACTIVE = false; 
				 
				if(VG_1_THROWING == true) 
				{
					if(VG_1_special1_sfx == 0)
						VG_1_special1_sfx = 2;  
					VG_1_THROW_TIMER = (int)TimerGetTime() + 750;
					VG_1_THROW_COOLDOWN = (int)TimerGetTime() + THROW_COOLDOWN_LENGTH;
				}
				if(VG_2_THROWING == true)
				{
					if(VG_2_special1_sfx == 0)
						VG_2_special1_sfx = 2; 
					VG_2_THROW_TIMER = (int)TimerGetTime() + 750;
					VG_2_THROW_COOLDOWN = (int)TimerGetTime() + THROW_COOLDOWN_LENGTH;
				} 
				 
				if(VG_CHARACTER == VG_GYEONG || VG_CHARACTER == VG_SIU || VG_CHARACTER == VG_MINSO || VG_CHARACTER == VG_REESE || VG_CHARACTER == VG_SANG || VG_CHARACTER == VG_TRAINER || VG_CHARACTER == VG_SHO || VG_CHARACTER == VG_TIA || VG_CHARACTER == VG_SAIZO)
					VG_DAMAGE = (VG_COP_THROW_DAMAGE);
				else
					VG_DAMAGE = (VG_CRIME_THROW_DAMAGE);    

				if(VG_CHARACTER == VG_KENNEDY)
					VG_DAMAGE = (VG_KENNEDY_THROW_DAMAGE);

				if(VG_CHARACTER == VG_YOHAN || VG_CHARACTER == VG_HYUK)
					VG_DAMAGE = (VG_WEAK_THROW_DAMAGE);

				if(VG_1_HAS_THROW == false && VG_1_THROWING == true) 
					VG_DAMAGE = (VG_WEAK_THROW_DAMAGE);

				if(VG_2_HAS_THROW == false && VG_2_THROWING == true)
					VG_DAMAGE = (VG_WEAK_THROW_DAMAGE);

				if(VG_ROUND_CONDITIONS == CONDITION_THROWS_ONLY)
				if(other_player == 2)
					VG_DAMAGE = (VG_STORY_THROW_DAMAGE);

				if(VG_ROUND_CONDITIONS == CONDITION_SPECIAL1_ONLY)
				if(other_player == 2) 
					VG_DAMAGE = 0;

				if(VG_ROUND_CONDITIONS == CONDITION_COMBO_ONLY)
				if(other_player == 2) 
					VG_DAMAGE = 0;

				if(VG_ROUND_CONDITIONS == CONDITION_SPECIAL2_ONLY)
				if(other_player == 2) 
					VG_DAMAGE = 0;

				if(VG_ROUND_CONDITIONS == CONDITION_ELECTRIC_ONLY)
				if(other_player == 2) 
					VG_DAMAGE = 0;

				if(VG_ROUND_CONDITIONS == CONDITION_CLOTHESLINE_ONLY)
				if(other_player == 2) 
					VG_DAMAGE = 0;

				if(VG_ROUND_CONDITIONS == CONDITION_PIGEON_ONLY)
				if(other_player == 2) 
					VG_DAMAGE = 0;

				if(VG_ROUND_CONDITIONS == CONDITION_PISTOL_ONLY)
				if(other_player == 2) 
					VG_DAMAGE = 0;

				if(VG_ROUND_CONDITIONS == CONDITION_MINE_ONLY)
				if(other_player == 2) 
					VG_DAMAGE = 0;

				if(VG_ROUND_CONDITIONS == CONDITION_BREAKDANCE_ONLY)
				if(other_player == 2) 
					VG_DAMAGE = 0;

				if(VG_ROUND_CONDITIONS == CONDITION_SURVIVE)
				if(other_player == 2) 
					VG_DAMAGE = 0;

				if(VG_1_THROWING == true)
					VG_1_HAS_THROW = false;       
				if(VG_2_THROWING == true) 
					VG_2_HAS_THROW = false;

				VG_1_THROWING = false; 
				VG_2_THROWING = false; 
				 
				VG_1_THROWING_SEQUENCE = 0;
				VG_2_THROWING_SEQUENCE = 0;   

				if(VG_Display_moves == false)
				{ 
					if(other_player == 1)      
					{  
						VG_1_HEALTH -= VG_DAMAGE;
						if(VG_1_HEALTH <= 0)
						{
							VG_INVERT = true;

							VG_INVERT_TOTAL_TIMER = (int)TimerGetTime() + VG_INVERT_TOTAL_LENGTH;
							VG_INVERT_TIMER = (int)TimerGetTime() + VG_INVERT_LENGTH;

							VG_finished_round = true;
							VG_1_HEALTH = 0;
							VG_1_DEFEATED = true; 
						}
					}
					if(other_player == 2)      
					{
						VG_2_HEALTH -= VG_DAMAGE; 
						if(VG_2_HEALTH <= 0)
						{
							VG_INVERT = true;

							VG_INVERT_TOTAL_TIMER = (int)TimerGetTime() + VG_INVERT_TOTAL_LENGTH;
							VG_INVERT_TIMER = (int)TimerGetTime() + VG_INVERT_LENGTH;

							VG_finished_round = true;
							VG_2_HEALTH = 0;
							VG_2_DEFEATED = true; 
						} 
					} 
				}

				if(VG_finished_round == true) 
				{
					if(other_player == 1) 
						VG_KOED_CHARACTER = VG_1_CHARACTER;
					if(other_player == 2) 
						VG_KOED_CHARACTER = VG_2_CHARACTER;

					VG_KO_sfx = true;

					vg_ko_smash_sfx = true; 
					title_sequence = 10;   
				}

				if(other_player == 1)
					VG_SHAKE_1 = false;
				else
					VG_SHAKE_2 = false;

				memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList)); 
				memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList)); 

				memset(VG_1_Moves, 0, sizeof(VG_1_Moves)); 
				memset(VG_2_Moves, 0, sizeof(VG_2_Moves)); 

				VG_1_Moves_count = 0;
				VG_2_Moves_count = 0;

				sprite[other_index].action_timer = 0;   
				sprite[other_index].on_ladder = true;
		  
				sprite[other_index].jumping = false; 

				sprite[other_index].special = 0; 

				sprite[other_index].pain = true;     
				sprite[other_index].knockdown = true; 
				sprite[other_index].knockdown_Y = sprite[other_index].y;

				sprite[other_index].flash_target = true; 
				sprite[other_index].flash_timer = (int)TimerGetTime() + 35;
			 
				sprite[other_index].electrocute = false;

				if(VG_finished_round == true) 
				{
					VG_SlowMO(6000, 6.0f); 
				}
				else 
				{ 
					VG_SlowMO(4000, 3.0f);
				}

				vg_hitsound_sfx = true;   
				 
			} 
			 
		}

		// Flip sprites when they've changed directions... 
		if( sprite[index].movement == LEFT)
			sprite[index].type = FE_FLIP;
		else  
			sprite[index].type = FE_NON; 

		if( sprite[other_index].movement == LEFT)
			sprite[other_index].type = FE_FLIP;
		else  
			sprite[other_index].type = FE_NON; 
	  

		Animate(2, ANIM_SPRITE); 
		Animate(3, ANIM_SPRITE);


	} // RUN_THROWS


}
