#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   
 
#if defined WIN32 || defined WIN64 
#define WIN32_LEAN_AND_MEAN   
#include <windows.h>  
#endif     

extern void Run_Moves(int player, int f_rate);
extern bool VG_Hit_player(int player, int type, int f_rate);
extern bool New_FX(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int i_value, int i_type, int state, int linked_sprite, int tex_id, int i_value1, int i_value2, int i_value3);
extern void VG_Slow_Mo();
extern void VG_Reset_all_anims();
extern float Node_Distance1(float x1, float y1, float x2, float y2);
extern bool LoadKeys();
extern bool SaveKeys(); 

int AI_DECISION_AVOID = -1;
int AI_DOG_CHARGE_TIMER = 0;
 
void Run_Verdict_AI(int f_rate)
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
	bool temp_VG_DOWNED=false;
	bool temp_VG_DEFEATED=false;
	int index = 0;
	int index_point = 0;
	int other_index = 0;   
	int other_player = 0;
	int player = 0;
	int shadow = 0;
	int tmp_VG_Moves_count=0;
	int display_player = 0;
	bool VG_MOVE_ACTIVE = false;  
	int special_rnd=1;
	int VG_CURRENT_CHAR=VG_2_CHARACTER;
	int rnd=0;
	int VG_CURRENT_AI_LEVEL = 1;
	bool VG_DANGER_ARMS_MID = false;
	bool VG_DANGER_ARMS_LOW = false;
	bool VG_BLOCK_A_PROJECTILE = true;

	int VG_TRAINER_HEALTHMID = VG_TRAINER_HEALTH/2; 

	if(VG_GAME_MODE != VG_STORY_MODE) 
	{
		VG_CURRENT_AI_LEVEL = VG_BATTLE_ROUND;

		if(VG_CURRENT_CHAR == VG_SANG)
			VG_CURRENT_AI_LEVEL = 8;
	}
	if(VG_GAME_MODE == VG_ARCADE_MODE)
	{
		if(VG_ARCADE_TYPE == VG_ARCADE_DUELLING) 
		{
			if(VG_CURRENT_AI_LEVEL < 3)
				VG_CURRENT_AI_LEVEL = 3;
		}
		if(VG_ARCADE_TYPE == VG_ARCADE_MASTER) 
			VG_CURRENT_AI_LEVEL = 8;
	}

	if(VG_GAME_MODE == VG_STORY_MODE)
		VG_CURRENT_AI_LEVEL = VG_AI_LEVEL; 

	// Block Reese's stretch arms...
	if(VG_1_CHARACTER == VG_REESE)
	if(sprite[2].status == VG_SPECIAL1_FONT)
	{
		if(sprite[2].special == 1)
			VG_DANGER_ARMS_MID = true;
		if(sprite[2].special == 2)
			VG_DANGER_ARMS_LOW = true;
	} 

	// Dodge projectiles...
	if(VG_finished_round == false)
	if(VG_AI_active == true) 
	if(sprite[3].status != VG_SPECIAL1_FONT && sprite[3].status != VG_SPECIAL2_FONT)
	if(sprite[3].knockdown == false && sprite[3].status != VG_KNOCKSLIDE_FONT && sprite[3].status != VG_GETUP_FONT)
	if((int)TimerGetTime() > VG_AI_AVOID_timer)
	if(VG_INTRO_DOG1 > 0 && VG_INTRO_DOG1 < TOTAL_NO_SPRITES) 
	{  
		if(rand()%3 != 0 || VG_AI_OWN_BOMB == true) 
		{
			VG_BLOCK_A_PROJECTILE = false;
			VG_AI_AVOID_timer = (int)TimerGetTime() + rand()%500;
		}

		if(VG_BLOCK_A_PROJECTILE == true)
		if(AI_DECISION_AVOID == -1)
		if(VG_AI_BITE_MID == true || VG_AI_BITE_LOW == true 
		|| VG_AI_DANGER_MID == true || VG_AI_DANGER_LOW == true
		|| VG_DANGER_ARMS_MID == true || VG_DANGER_ARMS_LOW == true
		|| VG_AI_OWN_BOMB == true) 
		{

			VG_Current_AI = -1;  

			VG_P2_AI_DOWN_KEY = false;
			VG_P2_AI_LEFT_KEY = false;            
			VG_P2_AI_RIGHT_KEY = false; 
			VG_P2_AI_UP_KEY = false;    
			VG_P2_AI_BLOCK_KEY = false;
			VG_P2_AI_THROW_KEY = false;

			if(VG_AI_DANGER_LOW == true || VG_AI_BITE_LOW == true || VG_DANGER_ARMS_LOW == true)
			if(rand()%4 == 0) 
			{  
				if(VG_CURRENT_CHAR == VG_JAE)  
				{
					sprite[3].special = 1 + rand()%2;
					VK_KEY_AI_SPECIAL1 = true;
				}
				else
				{ 
					VG_P2_AI_UP_KEY = true;    
					VG_P2_AI_BLOCK_KEY = false; 
				}

				AI_DECISION_AVOID = 1;
			}   
			else 
			{
				VG_P2_AI_BLOCK_KEY = true;    
				VG_P2_AI_DOWN_KEY = true;  
				AI_DECISION_AVOID = 0;
			} 

			if(VG_AI_DANGER_MID == true || VG_AI_BITE_MID == true || VG_DANGER_ARMS_MID == true) 
			if(rand()%4 == 0) 
			{ 
				if(VG_CURRENT_CHAR == VG_JAE)  
				{
					sprite[3].special = 1 + rand()%2;
					VK_KEY_AI_SPECIAL1 = true;
				}
				else
					VG_P2_AI_BLOCK_KEY = false;

				AI_DECISION_AVOID = 1;
			}
			else 
			{
				if(rand()%2 == 0)
					VG_P2_AI_BLOCK_KEY = true;
				 
				VG_P2_AI_DOWN_KEY = true;
				AI_DECISION_AVOID = 0; 
			} 

			if(VG_DANGER_ARMS_MID == true || VG_DANGER_ARMS_LOW == true) 
			{
				VG_AI_AVOID_timer = (int)TimerGetTime() + rand()%500;
				VG_AI_MOVE_timer = (int)TimerGetTime() + rand()%500;
				VG_AI_timer = (int)TimerGetTime() + rand()%175;
			}

		}

		if(VG_BLOCK_A_PROJECTILE == true)
		if(VG_AI_BITE_MID == false && VG_AI_BITE_LOW == false && VG_AI_DANGER_MID == false && VG_AI_DANGER_LOW == false && VG_AI_OWN_BOMB == false)
		{
			if(AI_DECISION_AVOID != -1)
			{
				VG_P2_AI_DOWN_KEY = false;
				VG_P2_AI_LEFT_KEY = false;            
				VG_P2_AI_RIGHT_KEY = false; 
				VG_P2_AI_UP_KEY = false;    
				VG_P2_AI_BLOCK_KEY = false;
				VG_P2_AI_THROW_KEY = false;
				AI_DECISION_AVOID = -1;
			}
		}

	}

	// Basic AI for testing... 
//	if(1 == 2) 
	if(VG_finished_round == false)
	if(VG_AI_active == true)   
	{
		// Moving Left/Right... 

		mid_x = sprite[2].x + sprite[2].width/2;    
		tar_x = sprite[3].x + sprite[3].width/2;  

		VG_distance_between_players = Node_Distance1(mid_x, VG_START_Y, tar_x, VG_START_Y);

		VG_Current_AI = -1;

		VG_P2_AI_THROW_KEY = false;

		if((int)TimerGetTime() > VG_AI_MOVE_timer)  
		{  
			VG_P2_AI_DOWN_KEY = false;
			VG_P2_AI_LEFT_KEY = false;           
			VG_P2_AI_RIGHT_KEY = false;   
			VG_P2_AI_UP_KEY = false;    
			VG_P2_AI_BLOCK_KEY = false;
			   
			if(VG_distance_between_players < 0.8f)  
				VG_Current_AI_MOVE = rand()%11;    
			else
				VG_Current_AI_MOVE = rand()%4;       

			VG_AI_MOVE_timer = (int)TimerGetTime() + rand()%200;  

			if(VG_Current_AI_MOVE <= 3) // VG_LEFT_FONT - VG_RIGHT_FONT - VG_DOWN_FONT - VG_UP_FONT
  				VG_AI_MOVE_timer = (int)TimerGetTime() + rand()%2000;

			// Make A.I more aggressive on 2nd round...
			if(AI_DECISION_AVOID == -1)
			//if(VG_2_CHARACTER != VG_YOHAN) 
			if(rand()%5 != 0)
			if((VG_2_CHARACTER == VG_GUN || VG_distance_between_players >= 0.6f) || (VG_2_CHARACTER == VG_KENNEDY || VG_distance_between_players >= 0.6f))  // VG_1_WINS == 1 && 
			if((VG_1_CHARACTER != VG_REESE && VG_1_CHARACTER != VG_GUN  && VG_1_CHARACTER != VG_KENNEDY)) // Don't advance against these characters...
		//	if(VG_2_CORNERED == false) 
			{
				if(mid_x >= tar_x) 
				{
					VG_Current_AI_MOVE = 3; // RIGHT
					if(rand()%3 == 0)
						VG_Current_AI_MOVE = 8; // UP-RIGHT
				}
				else
				{
					VG_Current_AI_MOVE = 2; // LEFT
					if(rand()%3 == 0)
						VG_Current_AI_MOVE = 5; // UP-LEFT
				}

			}
				   
		}

		if(VG_distance_between_players < 0.5f)   
		if(VG_MOVE_ACTIVE == false)
		if((int)TimerGetTime() > VG_AI_timer)     
		{  
			VG_P2_AI_PUNCH1_KEY = false;  
			VG_P2_AI_KICK1_KEY = false;           
			VG_P2_AI_KICK2_KEY = false;      
			VG_P2_AI_PUNCH2_KEY = false;          

			VG_AI_timer = (int)TimerGetTime() + rand()%175;

			if(VG_CURRENT_AI_LEVEL == 1)
				VG_AI_timer = (int)TimerGetTime() + rand()%800;
			if(VG_CURRENT_AI_LEVEL == 2)
				VG_AI_timer = (int)TimerGetTime() + rand()%650;
			if(VG_CURRENT_AI_LEVEL == 3)
				VG_AI_timer = (int)TimerGetTime() + rand()%550; 
			if(VG_CURRENT_AI_LEVEL == 4) 
				VG_AI_timer = (int)TimerGetTime() + rand()%500;
			if(VG_CURRENT_AI_LEVEL == 5)
				VG_AI_timer = (int)TimerGetTime() + rand()%450;
			if(VG_CURRENT_AI_LEVEL == 6)
				VG_AI_timer = (int)TimerGetTime() + rand()%400;
			if(VG_CURRENT_AI_LEVEL == 7) 
				VG_AI_timer = (int)TimerGetTime() + rand()%350;
			if(VG_CURRENT_AI_LEVEL >= 8) 
				VG_AI_timer = (int)TimerGetTime() + rand()%300; 

			if(VG_CURRENT_CHAR == VG_TRAINER && VG_GAME_MODE == VG_TRAINING_MODE) 
			{
				if(VG_ROUND > 1 || VG_2_HEALTH <= VG_TRAINER_HEALTHMID)
					VG_AI_timer = (int)TimerGetTime() + rand()%250;
				if(VG_ROUND > 1 && VG_2_HEALTH <= VG_TRAINER_HEALTHMID)
					VG_AI_timer = (int)TimerGetTime() + rand()%200;
				if(VG_ROUND == 2)
					VG_AI_timer = (int)TimerGetTime() + rand()%200;
			}
			 
			if(VG_CURRENT_AI_LEVEL >= 3)  
			if(rand()%4 == 0) 
			if(VG_2_CHARACTER != VG_SANG && VG_2_CHARACTER != VG_TRAINER)
			    VK_KEY_AI_COMBO = true;

			if(VG_2_CORNERED == true)     
				VG_AI_timer -= 100;   
			 
			VG_Current_AI = 1;   
			 
			if(VG_CURRENT_AI_LEVEL == 2)  
			if(VG_distance_between_players <= 0.23f)   
				VG_Current_AI = rand()%4;
			if(VG_CURRENT_AI_LEVEL == 3)  
			if(VG_distance_between_players <= 0.23f)   
				VG_Current_AI = rand()%3;
			if(VG_CURRENT_AI_LEVEL == 4)
			if(VG_distance_between_players <= 0.23f)  
				VG_Current_AI = rand()%3;
			if(VG_CURRENT_AI_LEVEL == 5)
			if(VG_distance_between_players <= 0.23f)      
				VG_Current_AI = rand()%2; 
			if(VG_CURRENT_AI_LEVEL >= 6)
			if(VG_distance_between_players <= 0.23f)  
				VG_Current_AI = 1 + rand()%1;
			 
		//	if(VG_ROUND_CONDITIONS == CONDITION_BASIC_BOTH)
		//		VG_Current_AI = 1;

			// Make sure character is facing opponent...
		//	if(VG_distance_between_players <= 0.20f)  
			if(VG_Current_AI == 2)
			if((int)TimerGetTime() > VG_2_THROW_TIMER)  
			if(sprite[3].jumping == true || sprite[2].handcuffed == true || sprite[2].dizzy == true || sprite[2].sticky == true)
			    VG_Current_AI = 1; // Punch or reset... // rand()%2
			 
			// Don't try to throw jumping opponent...
		/*	if(sprite[2].jumping == true)  
			if(VG_Current_AI == 2)
				VG_Current_AI = rand()%2; // Punch or reset...*/

			// Do a special move... 
			if(VG_Current_AI != 2) // If doing a throw don't do a special...
			if(VG_2_EQUIPMENT != EQUIPMENT_BASIC)
			if((int)TimerGetTime() > VG_AI_SPECIALS_TIMER)
			if((sprite[3].jumping == false || VG_CURRENT_CHAR == VG_MINSO) && sprite[3].pain == false && sprite[3].knockdown == false)
			{
				special_rnd = 13;   
				  
				if(VG_2_HEALTH <= 600)    
					special_rnd = 10;
				if(VG_2_HEALTH <= 200)       
					special_rnd = 7;
				if(VG_BATTLE_ROUND >= 2)  
					special_rnd = 9;
				if(VG_BATTLE_ROUND >= 4) 
					special_rnd = 6;
				if(VG_BATTLE_ROUND >= 6) 
					special_rnd = 4;
				if(VG_BATTLE_ROUND == 8)
					special_rnd = 3; 

				if(VG_2_CORNERED == true)
					special_rnd = 4;

				if(NO_SPECIALS == 0)
				if(VG_CURRENT_AI_LEVEL > 1)
				if((VG_CURRENT_CHAR != VG_TRAINER || (VG_ROUND >= 2 && VG_2_HEALTH <= VG_TRAINER_HEALTHMID ) || VG_GAME_MODE != VG_TRAINING_MODE)   )
				if(sprite[3].status != VG_SPECIAL1_FONT && sprite[3].status != VG_SPECIAL2_FONT ) 
				if(rand()%special_rnd == 0)    
				{ 
					if(VG_CURRENT_CHAR == VG_TRAINER) 
					{
						if(VG_AI_DOG_ONSCREEN == true)
							sprite[3].special = 2;
						else
							sprite[3].special = 2 + rand()%2;
					}
					if(VG_CURRENT_CHAR == VG_REESE)
						sprite[3].special = 1 + rand()%5;
					if(VG_CURRENT_CHAR == VG_YOHAN)  
					{
						if(VG_2_CORNERED == false)
							sprite[3].special = 1 + rand()%4;
						else
						{
							sprite[3].special = 1 + rand()%4;

							if(sprite[3].special == 3) // Bomb drop
								sprite[3].special = 4;
						}

						// Only do vials for fight 4...
						if(VG_GAME_MODE == VG_STORY_MODE)
						if(VG_1_CHARACTER == VG_GYEONG)
						if(VG_CURRENT_STORY_SCENE == 4)
							sprite[3].special = 1 + rand()%2;
					}

					if(VG_CURRENT_CHAR == VG_SIU) 
						sprite[3].special = 1 + rand()%4;

					if (VG_CURRENT_CHAR == VG_SHO)
						sprite[3].special = 1 + rand() % 3;

					if (VG_CURRENT_CHAR == VG_SAIZO)
						sprite[3].special = 1 + rand() % 3;

					if (VG_CURRENT_CHAR == VG_TIA)
						sprite[3].special = 1 + rand() % 3;

					if(VG_CURRENT_CHAR == VG_GUN)  
					{
						if(sprite[2].jumping == true)
							sprite[3].special = 4;
						else
							sprite[3].special = 1 + rand()%4;
					}
					if(VG_CURRENT_CHAR == VG_KENNEDY)  
					{
						if(sprite[2].jumping == true)
							sprite[3].special = 4;
						else
							sprite[3].special = 1 + rand()%4;
					}
					if(VG_CURRENT_CHAR == VG_JAE)
						sprite[3].special = 1 + rand()%5;
					if(VG_CURRENT_CHAR == VG_GYEONG) 
						sprite[3].special = 1 + rand()%5;
					if(VG_CURRENT_CHAR == VG_MINSO)
					if(sprite[3].jumping == false)
					{
						if(VG_AI_DOG_ONSCREEN == true)
						    sprite[3].special = 1 + rand()%2;
						else
						    sprite[3].special = 1 + rand()%3;
					}
					else
						sprite[3].special = 4; // Panty shot...

					if(VG_CURRENT_CHAR == VG_HYUK)
						sprite[3].special = 1 + rand()%4;
					if(VG_CURRENT_CHAR == VG_SANG)
						sprite[3].special = 2; 

					VK_KEY_AI_SPECIAL1 = true;
				}
			}
			 
		}     

		// Do a special pistol move...
	//	if((int)TimerGetTime() > VG_AI_SPECIALS_TIMER)
		if(VG_Current_AI != 2) 
		if(VG_2_EQUIPMENT != EQUIPMENT_BASIC)
	//	if(VG_2_CHARACTER != VG_REESE)
		if(sprite[3].status != VG_SPECIAL1_FONT && sprite[3].status != VG_SPECIAL2_FONT )
		if(VG_distance_between_players >= 0.5f) 
		if(VG_MOVE_ACTIVE == false)
		if(sprite[3].jumping == false && sprite[3].pain == false && sprite[3].knockdown == false)
		if((int)TimerGetTime() > VG_AI_timer)
		{   
			VG_P2_AI_PUNCH1_KEY = false; 
			VG_P2_AI_KICK1_KEY = false;     
			VG_P2_AI_KICK2_KEY = false;       
			VG_P2_AI_PUNCH2_KEY = false;   

			VG_AI_timer = (int)TimerGetTime() + rand()%250;  

			if(VG_CURRENT_AI_LEVEL == 1)
				VG_AI_timer = (int)TimerGetTime() + rand()%650;
			if(VG_CURRENT_AI_LEVEL == 2)
				VG_AI_timer = (int)TimerGetTime() + rand()%500;
			if(VG_CURRENT_AI_LEVEL == 3)
				VG_AI_timer = (int)TimerGetTime() + rand()%450; 
			if(VG_CURRENT_AI_LEVEL == 4)
				VG_AI_timer = (int)TimerGetTime() + rand()%400;
			if(VG_CURRENT_AI_LEVEL == 5)
				VG_AI_timer = (int)TimerGetTime() + rand()%350;
			if(VG_CURRENT_AI_LEVEL == 6)
				VG_AI_timer = (int)TimerGetTime() + rand()%250;
			if(VG_CURRENT_AI_LEVEL == 7) 
				VG_AI_timer = (int)TimerGetTime() + rand()%150;

			if(VG_CURRENT_AI_LEVEL == 8)
				VG_AI_timer = (int)TimerGetTime() + rand()%100;

			if(VG_CURRENT_CHAR == VG_TRAINER && VG_GAME_MODE == VG_TRAINING_MODE)
			{
				if(VG_ROUND > 1 || VG_2_HEALTH <= VG_TRAINER_HEALTHMID)
					VG_AI_timer = (int)TimerGetTime() + rand()%250;
				if(VG_ROUND > 1 && VG_2_HEALTH <= VG_TRAINER_HEALTHMID)
					VG_AI_timer = (int)TimerGetTime() + rand()%200;
				if(VG_ROUND == 2)
					VG_AI_timer = (int)TimerGetTime() + rand()%200;
			}

			special_rnd = 9;    
			 
			if(VG_2_HEALTH <= 600) 
				special_rnd = 8;   
			  
			if(VG_2_HEALTH <= 200)  
				special_rnd = 5;
	
			if(VG_CURRENT_CHAR == VG_YOHAN)
				special_rnd -= 2;   

			if(NO_SPECIALS == 0)
			if(VG_CURRENT_AI_LEVEL > 1)
			if(VG_CURRENT_CHAR != VG_TRAINER || (VG_ROUND >= 2 && VG_2_HEALTH <= VG_TRAINER_HEALTHMID ) || VG_GAME_MODE != VG_TRAINING_MODE)
			if(rand()%special_rnd == 0) 
			{  
				if(VG_CURRENT_CHAR == VG_TRAINER) 
					{
						if(VG_AI_DOG_ONSCREEN == true)
							sprite[3].special = 2;
						else
							sprite[3].special = 2 + rand()%2;
					}
				if(VG_CURRENT_CHAR == VG_REESE)  
				{
					sprite[3].special = 1 + rand()%6; 

					// Power Orb...
					if(sprite[3].special >= 3)
						sprite[3].special = 5;
				}
				if(VG_CURRENT_CHAR == VG_YOHAN)  
				{ 
					if(VG_2_CORNERED == false)
						sprite[3].special = 1 + rand()%4;
					else
					{
						sprite[3].special = 1 + rand()%4;

						if(sprite[3].special == 3) // Bomb drop
							sprite[3].special = 4;
					}

					// Only do vials for fight 4...
					if(VG_GAME_MODE == VG_STORY_MODE)
					if(VG_1_CHARACTER == VG_GYEONG)
					if(VG_CURRENT_STORY_SCENE == 4)
						sprite[3].special = 1 + rand()%2;
				}
				if(VG_CURRENT_CHAR == VG_SIU) 
					sprite[3].special = 2 + rand()%3;

				if (VG_CURRENT_CHAR == VG_SHO)
					sprite[3].special = 3;

				if (VG_CURRENT_CHAR == VG_SAIZO)
					sprite[3].special = 2 + rand() % 1;

				if (VG_CURRENT_CHAR == VG_TIA)
					sprite[3].special = 1;

				if(VG_CURRENT_CHAR == VG_GUN) 
					sprite[3].special = 1 + rand()%2;
				if(VG_CURRENT_CHAR == VG_KENNEDY) 
					sprite[3].special = 1 + rand()%2;
				if(VG_CURRENT_CHAR == VG_JAE)  
					sprite[3].special = 1 + rand()%3;
				if(VG_CURRENT_CHAR == VG_MINSO)
				if(sprite[3].jumping == false)
				{
					if(VG_AI_DOG_ONSCREEN == true)
						sprite[3].special = 1 + rand()%2;
					else
						sprite[3].special = 1 + rand()%3;
				}
				else
					sprite[3].special = 4; // Panty shot...

				if(VG_CURRENT_CHAR == VG_HYUK)
					sprite[3].special = 2 + rand()%3;
				if(VG_CURRENT_CHAR == VG_GYEONG)
				{
					if(rand()%2 == 0)
						sprite[3].special = 3; 
					else
						sprite[3].special = 4; 
				}
				if(VG_CURRENT_CHAR == VG_SANG)
				{
					if(rand()%2 == 0)
						sprite[3].special = 3; 
					else
						sprite[3].special = 4; 
				}

				VK_KEY_AI_SPECIAL1 = true;
			}
		}
		  
		if(VG_Current_AI_MOVE == 1)
		{
			VG_P2_AI_DOWN_KEY = true;  
		}
				    
		if(VG_Current_AI_MOVE == 2 )
		if(sprite[3].movement == RIGHT && VG_2_CORNERED == true)
		{
			VG_P2_AI_LEFT_KEY = false; 
			VG_P2_AI_BLOCK_KEY = true;
		}
		else  
			VG_P2_AI_LEFT_KEY = true; 

		if(VG_Current_AI_MOVE == 3 )
		if(sprite[3].movement == LEFT && VG_2_CORNERED == true)
		{
			VG_P2_AI_RIGHT_KEY = false;
			VG_P2_AI_BLOCK_KEY = true;
		}
		else
			VG_P2_AI_RIGHT_KEY = true;

		if(VG_Current_AI_MOVE == 4) 
			VG_P2_AI_UP_KEY = true;

		if(VG_Current_AI_MOVE == 5 || VG_Current_AI_MOVE == 6 || VG_Current_AI_MOVE == 7)
		{
			VG_P2_AI_UP_KEY = true;
			VG_P2_AI_LEFT_KEY = true;
		}
		if(VG_Current_AI_MOVE == 8 || VG_Current_AI_MOVE == 9 || VG_Current_AI_MOVE == 10)
		{
			VG_P2_AI_UP_KEY = true;
			VG_P2_AI_RIGHT_KEY = true; 
		}

		// Do a throw...  
		if(VK_KEY_AI_SPECIAL1 == false)  
		if(VG_Current_AI == 2)  
		{ 
			VG_P2_AI_THROW_KEY = true;
		}

		if(VK_KEY_AI_SPECIAL1 == false)
		if(VG_Current_AI == 1)   
		{ 
			rnd = rand()%4; 

			if(rnd == 0)
				VG_P2_AI_PUNCH1_KEY = true;
			if(rnd == 1)
				VG_P2_AI_PUNCH2_KEY = true;
			if(rnd == 2)
				VG_P2_AI_KICK2_KEY = true; 
			if(rnd == 3)
				VG_P2_AI_KICK1_KEY = true;

		}

		// P2 is being pounded on...
		if(sprite[3].pain == true)  
		{
			// If hit low, duck...
			if(sprite[2].status == VG_LOW_PUNCH_FONT || sprite[2].status == VG_LOW_KICK_FONT || sprite[2].status == VG_LOW_PUNCH2_FONT
			|| sprite[2].status == VG_LOW_PUNCH_SHORT_FONT || sprite[2].status == VG_KICK_KNEE_FONT || sprite[2].status == VG_SECOND_STRIKE
			|| sprite[2].status == VG_LOW_KICK_SHORT_FONT || sprite[2].status == VG_UPPERCUT_FONT || sprite[2].status == VG_THIRD_STRIKE
			|| VG_2_CORNERED == true)
			{
				VG_P2_AI_DOWN_KEY = true; 
				VG_P2_AI_UP_KEY = false;
			}
			 
			VG_P2_AI_BLOCK_KEY = true;

		}   
		  
		// P1 is handcuffed or P2 has bomb attached... 
		if(sprite[2].handcuffed == true 
		|| sprite[2].acid == true
		|| (sprite[3].sticky == true && VG_2_HEALTH < (VG_2_TOTALHEALTH/3) ) 
		|| VG_ROUND_CONDITIONS == CONDITION_BASIC_ONLY
		|| VG_ROUND_CONDITIONS == CONDITION_SURVIVE
		|| VG_ROUND_CONDITIONS == CONDITION_ELECTRIC_ONLY
		|| VG_ROUND_CONDITIONS == CONDITION_CLOTHESLINE_ONLY
		|| VG_ROUND_CONDITIONS == CONDITION_MINE_ONLY
		|| VG_ROUND_CONDITIONS == CONDITION_PISTOL_ONLY
		|| VG_ROUND_CONDITIONS == CONDITION_COMBO_ONLY
		|| VG_ROUND_CONDITIONS == CONDITION_PIGEON_ONLY
		|| (VG_CURRENT_STORY_SCENE == 1 && VG_1_CHARACTER == VG_GYEONG)
		|| (VG_CURRENT_STORY_SCENE == 8 && VG_1_CHARACTER == VG_YOHAN)
		|| (VG_CURRENT_STORY_SCENE == 4 && VG_1_CHARACTER == VG_HYUK)
		)  
		{
			// Retreat backwards... 
			if(sprite[3].movement == RIGHT) 
			{
				VG_P2_AI_LEFT_KEY = false;   
				VG_P2_AI_RIGHT_KEY = true; 
			} 
			else
			{
				VG_P2_AI_LEFT_KEY = true; 
				VG_P2_AI_RIGHT_KEY = false; 
			}
			 
		} 

		if(VG_CURRENT_CHAR == VG_TRAINER && VG_GAME_MODE == VG_TRAINING_MODE)
		if(VG_ROUND == 1 && VG_2_HEALTH > VG_TRAINER_HEALTHMID)  
		{  
			  
			// Make Sensei block...   
		/*	if(VG_1_MOVE_ACTIVE == true) 
			{
				if(sprite[2].direction == LEFT)
					VG_P2_AI_LEFT_KEY = true;           
				if(sprite[2].direction == RIGHT)
					VG_P2_AI_RIGHT_KEY = true;  
			} */
			 
			VG_P2_AI_PUNCH2_KEY = false; 
			VG_P2_AI_PUNCH1_KEY = false;
			VG_P2_AI_KICK2_KEY  = false;
			VG_P2_AI_KICK1_KEY  = false;

		//	VG_P2_AI_LEFT_KEY = false; 
		//	VG_P2_AI_RIGHT_KEY = false;

			VG_P2_AI_UP_KEY = false;
		//	VG_P2_AI_DOWN_KEY = false;

		}

		// Is dizzy from back-stab move...
		if(sprite[3].dizzy == true || sprite[3].acid == true)   
		{
			if(VG_P2_AI_LEFT_KEY == true) 
			{
				VG_P2_AI_RIGHT_KEY = true;
				VG_P2_AI_LEFT_KEY = false;
			}
			else if(VG_P2_AI_RIGHT_KEY == true)
			{
				VG_P2_AI_RIGHT_KEY = false;
				VG_P2_AI_LEFT_KEY = true;
			}
			if(VG_P2_AI_DOWN_KEY == true)
			{
				VG_P2_AI_UP_KEY = true;
				VG_P2_AI_DOWN_KEY = false;
			}
			else if(VG_P2_AI_UP_KEY == true)
			{
				VG_P2_AI_UP_KEY = false;
				VG_P2_AI_DOWN_KEY = true;
			}

		}
	}

}
