#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64 
#define WIN32_LEAN_AND_MEAN   
#include <windows.h>
#endif    
 
extern void Run_Moves(int player, int f_rate);
void VG_Reset_Player(int player);


void VG_dust_effect(int character, int shadow, int direction)
{
	int anim = 12; // 46

	if(direction == -1) // For dust slide effects...
		anim = 46;

	if(shadow < 0 || shadow >= TOTAL_NO_SPRITES)
		return;

	if(character == VG_GYEONG)  
	{
		New_FX((sprite[shadow].x+sprite[shadow].width/2)+0.01f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)+0.01f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
		New_FX((sprite[shadow].x+sprite[shadow].width/2)-0.11f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)-0.11f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
	}
	if(character == VG_SIU)
	{
		New_FX((sprite[shadow].x+sprite[shadow].width/2)+0.05f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)+0.05f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
		New_FX((sprite[shadow].x+sprite[shadow].width/2)-0.15f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)-0.15f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
	}
	if (character == VG_SHO)
	{
		New_FX((sprite[shadow].x + sprite[shadow].width / 2) + 0.05f, sprite[shadow].y, (sprite[shadow].x + sprite[shadow].width / 2) + 0.05f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1);
		New_FX((sprite[shadow].x + sprite[shadow].width / 2) - 0.15f, sprite[shadow].y, (sprite[shadow].x + sprite[shadow].width / 2) - 0.15f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1);
	}
	if(character == VG_MINSO)
	{
		if(direction == RIGHT) 
		{
			New_FX((sprite[shadow].x+sprite[shadow].width/2)+0.05f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)+0.05f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
			New_FX((sprite[shadow].x+sprite[shadow].width/2)-0.11f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)-0.11f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
		}
		else 
		{
			New_FX((sprite[shadow].x+sprite[shadow].width/2)+0.03f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)+0.03f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
			New_FX((sprite[shadow].x+sprite[shadow].width/2)-0.13f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)-0.13f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
		} 
	} 
	if (character == VG_TIA)
	{
		if (direction == RIGHT)
		{
			New_FX((sprite[shadow].x + sprite[shadow].width / 2) + 0.05f, sprite[shadow].y, (sprite[shadow].x + sprite[shadow].width / 2) + 0.05f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1);
			New_FX((sprite[shadow].x + sprite[shadow].width / 2) - 0.11f, sprite[shadow].y, (sprite[shadow].x + sprite[shadow].width / 2) - 0.11f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1);
		}
		else
		{
			New_FX((sprite[shadow].x + sprite[shadow].width / 2) + 0.03f, sprite[shadow].y, (sprite[shadow].x + sprite[shadow].width / 2) + 0.03f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1);
			New_FX((sprite[shadow].x + sprite[shadow].width / 2) - 0.13f, sprite[shadow].y, (sprite[shadow].x + sprite[shadow].width / 2) - 0.13f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1);
		}
	}
	if(character == VG_SAIZO)
	{
		New_FX((sprite[shadow].x+sprite[shadow].width/2)+0.05f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)+0.05f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
		New_FX((sprite[shadow].x+sprite[shadow].width/2)-0.15f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)-0.15f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
	}
	if(character == VG_REESE)
	{  
		New_FX((sprite[shadow].x+sprite[shadow].width/2)+0.00f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)+0.00f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
		New_FX((sprite[shadow].x+sprite[shadow].width/2)-0.10f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)-0.10f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
	}
	if(character == VG_YOHAN)
	{ 
		New_FX((sprite[shadow].x+sprite[shadow].width/2)+0.03f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)+0.03f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
		New_FX((sprite[shadow].x+sprite[shadow].width/2)-0.13f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)-0.13f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
	}
	if(character == VG_JAE)
	{
		New_FX((sprite[shadow].x+sprite[shadow].width/2)+0.03f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)+0.03f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
		New_FX((sprite[shadow].x+sprite[shadow].width/2)-0.13f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)-0.13f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
	}
	if(character == VG_GUN)
	{
		New_FX((sprite[shadow].x+sprite[shadow].width/2)+0.05f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)+0.05f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
		New_FX((sprite[shadow].x+sprite[shadow].width/2)-0.15f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)-0.15f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
	}
	if(character == VG_HYUK)
	{
		New_FX((sprite[shadow].x+sprite[shadow].width/2)+0.05f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)+0.05f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
		New_FX((sprite[shadow].x+sprite[shadow].width/2)-0.15f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)-0.15f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
	}
	if(character == VG_SANG)
	{
		New_FX((sprite[shadow].x+sprite[shadow].width/2)+0.00f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)+0.00f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
		New_FX((sprite[shadow].x+sprite[shadow].width/2)-0.10f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)-0.10f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
	}
	if(character == VG_TRAINER)
	{
		New_FX((sprite[shadow].x+sprite[shadow].width/2)+0.03f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)+0.03f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
		New_FX((sprite[shadow].x+sprite[shadow].width/2)-0.13f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)-0.13f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
	}
	if(character == VG_KENNEDY)
	{
		New_FX((sprite[shadow].x+sprite[shadow].width/2)+0.05f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)+0.05f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
		New_FX((sprite[shadow].x+sprite[shadow].width/2)-0.15f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)-0.15f, sprite[shadow].y, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
	}

}

void VG_set_intro_dogs()
{
	VG_INTRO_DOG1 = 11; 
	VG_INTRO_DOG2 = 12;

	if(VG_BACKGROUND == VG_GYEONG)
		VG_INTRO_DOG1 = 11; 
	if(VG_BACKGROUND == VG_SIU) 
		VG_INTRO_DOG1 = 12;
	if(VG_BACKGROUND == VG_MINSO)
		VG_INTRO_DOG1 = 11; 
	if(VG_BACKGROUND == VG_REESE)
		VG_INTRO_DOG1 = 11; 
	if(VG_BACKGROUND == VG_YOHAN)
		VG_INTRO_DOG1 = 11; 
	if(VG_BACKGROUND == VG_JAE)
		VG_INTRO_DOG1 = 11; 
	if(VG_BACKGROUND == VG_GUN)
		VG_INTRO_DOG1 = 11; 
	if(VG_BACKGROUND == VG_HYUK)
		VG_INTRO_DOG1 = 11; 
	if(VG_BACKGROUND == VG_SANG)
		VG_INTRO_DOG1 = 11; 
	if(VG_BACKGROUND == VG_TRAINER)
		VG_INTRO_DOG1 = 11; 
	if(VG_BACKGROUND == VG_SHRINE)
		VG_INTRO_DOG1 = 11; 
	if (VG_BACKGROUND == VG_SHO)
		VG_INTRO_DOG1 = 11;
	if (VG_BACKGROUND == VG_TIA)
		VG_INTRO_DOG1 = 11;
	if(VG_BACKGROUND == VG_KENNEDY)
		VG_INTRO_DOG1 = 11; 

	if(VG_BACKGROUND == VG_GYEONG)
		VG_INTRO_DOG2 = 12;
	if(VG_BACKGROUND == VG_SIU)
		VG_INTRO_DOG2 = 13;
	if(VG_BACKGROUND == VG_MINSO)
		VG_INTRO_DOG2 = 12;
	if(VG_BACKGROUND == VG_REESE)
		VG_INTRO_DOG2 = 12;
	if(VG_BACKGROUND == VG_YOHAN)
		VG_INTRO_DOG2 = 12;
	if(VG_BACKGROUND == VG_JAE)
		VG_INTRO_DOG2 = 12;
	if(VG_BACKGROUND == VG_GUN)
		VG_INTRO_DOG2 = 12;
	if(VG_BACKGROUND == VG_HYUK)
		VG_INTRO_DOG2 = 12;
	if(VG_BACKGROUND == VG_SANG)
		VG_INTRO_DOG2 = 12;
	if(VG_BACKGROUND == VG_TRAINER) 
		VG_INTRO_DOG2 = 12;
	if(VG_BACKGROUND == VG_SHRINE)
		VG_INTRO_DOG2 = 12; 
	if (VG_BACKGROUND == VG_SHO)
		VG_INTRO_DOG2 = 12;
	if (VG_BACKGROUND == VG_TIA)
		VG_INTRO_DOG2 = 12;
	if(VG_BACKGROUND == VG_KENNEDY)
		VG_INTRO_DOG2 = 12;
}

void VG_ATTACK_DOG(int player) 
{ 
	int VG_TEMP_DOG=0;
	int VG_CURRENT_CHAR=0;  
	float diff_x=0.0f;
	bool is_pigeon = false;
	int index = 0;
	int other_index = 0;

	VG_TEMP_DOG = 11; 

	if(player == 1) 
	{ 
		if(VG_1_CHARACTER == VG_SIU || VG_1_CHARACTER == VG_SAIZO)
			is_pigeon = true;

		VG_TEMP_DOG = VG_INTRO_DOG1;

		index = 2;
		other_index = 3;
		 
		VG_CURRENT_CHAR = 2;
	}
	else 
	{ 
		if(VG_2_CHARACTER == VG_SIU || VG_2_CHARACTER == VG_SAIZO)
			is_pigeon = true;

		VG_TEMP_DOG = VG_INTRO_DOG2;

		index = 3;
		other_index = 2;

		VG_CURRENT_CHAR = 3;
	} 

	if(sprite[VG_TEMP_DOG].x < sprite[VG_SCROLL_INDEX+7].x || sprite[VG_TEMP_DOG].x >= sprite[VG_SCROLL_INDEX+7].x + sprite[VG_SCROLL_INDEX+7].width)
	if(sprite[VG_TEMP_DOG].moving == false)
	{ 

		diff_x = sprite[VG_TEMP_DOG].w - sprite[VG_TEMP_DOG].x;   

		if( (sprite[index].x + sprite[index].width/2) < (sprite[other_index].x + sprite[other_index].width/2) )
			sprite[VG_TEMP_DOG].movement = RIGHT;
		else
			sprite[VG_TEMP_DOG].movement = LEFT;

		sprite[VG_TEMP_DOG].grab_switch = true; 

		sprite[VG_TEMP_DOG].moving = true;   
		    
		sprite[VG_TEMP_DOG].type = FE_NON;  
		  
		if(is_pigeon == false)
		{
			sprite[VG_TEMP_DOG].x = -camX - 0.85f;     
			sprite[VG_TEMP_DOG].is_a_pigeon = false;
		}
		else 
		{
			sprite[VG_TEMP_DOG].x = -camX - 0.95f;    
			sprite[VG_TEMP_DOG].is_a_pigeon = true;
		}

		sprite[VG_TEMP_DOG].w = (sprite[VG_TEMP_DOG].x + sprite[VG_TEMP_DOG].width) - sprite[VG_TEMP_DOG].box_width;

		if(sprite[VG_TEMP_DOG].movement == LEFT) 
		{

			if(is_pigeon == false)
				sprite[VG_TEMP_DOG].x = -camX + 0.8f;
			else
				sprite[VG_TEMP_DOG].x = -camX + 0.8f;

			sprite[VG_TEMP_DOG].type = FE_FLIP;

			sprite[VG_TEMP_DOG].w  = sprite[VG_TEMP_DOG].x;

		}



	}

}

bool VG_CheckMove(int move1, int move2, int move3, int move4, int move5)  
{
	bool success = true;
	  
	if(VG_1st != move1 && move1 != -1)
		success = false;
	if(VG_2nd != move2 && move2 != -1)
		success = false; 
	if(VG_3rd != move3 && move3 != -1)
		success = false; 
	if(VG_4th != move4 && move4 != -1)
		success = false;  
	if(VG_5th != move5 && move5 != -1)
		success = false;  

	return(success);
}
bool VG_CheckMoveALL(int move1, int move2, int move3, int move4)   
{
	bool success = true; 
	  
	if(VG_1st != move1 && VG_1st != move2 && VG_1st != move3 && VG_1st != move4 && move1 != -1)
		success = false;
	if(VG_2nd != move1 && VG_2nd != move2 && VG_2nd != move3 && VG_2nd != move4 && move2 != -1)
		success = false; 
	if(VG_3rd != move1 && VG_3rd != move2 && VG_3rd != move3 && VG_3rd != move4 && move3 != -1)
		success = false; 
	if(VG_4th != move1 && VG_4th != move2 && VG_4th != move3 && VG_4th != move4 && move4 != -1)
		success = false;  

	return(success);
}

void VG_CombineDirections(int player)  
{




}

void VG_CheckForSpecials(int player)      
{ 
	int index=0;
	int VG_1st_time = 0;
	int VG_2nd_time = 0;
	int VG_3rd_time = 0;
	int VG_4th_time = 0;
	int VG_5th_time = 0;
	int direction=0;
	int opp_direction=0;
	int direction_H=0;
	int opp_direction_H=0;
	int VG_Moves_count=0;
	int VG_Moves[MOVES_LIMIT];
	int VG_Moves_timestamp[MOVES_LIMIT];
	int VG_CURRENT_CHAR = 0;
	bool temp_VG_DOWN_pressed=false;
	bool VG_MOVE_ACTIVE = false;
	int VG_STRIKE_TIMER=0;
	int VG_THROW_TIMER = 0;
	bool VG_THROWING = false;
	int VG_EQUIPMENT = EQUIPMENT_BASIC;
	bool VG_HAS_THIRD = true;

	VG_1st = 0;
	VG_2nd = 0;
	VG_3rd = 0; 
	VG_4th = 0;  

	if(VG_1_THROWING == true || VG_2_THROWING == true)
		VG_THROWING = true;
	else
		VG_THROWING = false;

	if(player == 1)
	{
		if(VG_GAME_MODE == VG_STORY_MODE)
			VG_HAS_THIRD = VG_has_third_special[VG_CURRENT_STORY_SCENE];
		else
			VG_HAS_THIRD = true;

		VG_EQUIPMENT = VG_1_EQUIPMENT;
		VG_STRIKE_TIMER = VG_1_STRIKE_TIMER;
		VG_THROW_TIMER = VG_1_THROW_TIMER;
		temp_VG_DOWN_pressed =  VG_1_DOWN_pressed;
		index = 2;
		VG_CURRENT_CHAR = VG_1_CHARACTER;
		VG_Moves_count = VG_1_Moves_count;
		 
		if(VG_1_Moves_count < MOVES_LIMIT)
		for(int i=0;i<VG_1_Moves_count;i++)
		{
			VG_Moves[i] = VG_1_Moves[i];
			VG_Moves_timestamp[i] = VG_1_Moves_timestamp[i];
		}
	}
	if(player == 2)
	{
		VG_EQUIPMENT = VG_2_EQUIPMENT;
		VG_STRIKE_TIMER = VG_2_STRIKE_TIMER;
		VG_THROW_TIMER = VG_2_THROW_TIMER;

		if(VG_GAME_MODE == VG_STORY_MODE)
		if(VG_EQUIPMENT != EQUIPMENT_BASIC)
			VG_HAS_THIRD = false;
		else
			VG_HAS_THIRD = true;

		temp_VG_DOWN_pressed =  VG_2_DOWN_pressed;   
		index = 3;
		VG_CURRENT_CHAR = VG_2_CHARACTER; 
		VG_Moves_count = VG_2_Moves_count;

		if(VG_2_Moves_count < MOVES_LIMIT)  
		for(int i=0;i<VG_2_Moves_count;i++)  
		{
			VG_Moves[i] = VG_2_Moves[i];
			VG_Moves_timestamp[i] = VG_2_Moves_timestamp[i]; 
		} 
	}     

	if(VG_finished_round == false) 
	if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)  // Throw...   
	if(sprite[index].pain == false) 
	if(sprite[index].knockdown == false)
	if(sprite[index].status != VG_RELOAD_FONT) 
	if(sprite[index].status != VG_KNOCKSLIDE_FONT)
	if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT)    
	{
		    
		if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT)
		{ 
			VG_1st =  VG_Moves[(VG_Moves_count-1)]; 
			VG_1st_time = VG_Moves_timestamp[(VG_Moves_count-1)]; 

			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT)
			{
				VG_2nd =  VG_Moves[(VG_Moves_count-2)];  
				VG_2nd_time = VG_Moves_timestamp[(VG_Moves_count-2)];
			}

			if((VG_Moves_count-3) >= 0 && (VG_Moves_count-3) <= MOVES_LIMIT)
			{
			    VG_3rd =  VG_Moves[(VG_Moves_count-3)]; 
				VG_3rd_time = VG_Moves_timestamp[(VG_Moves_count-3)];
			}
			if((VG_Moves_count-4) >= 0 && (VG_Moves_count-4) <= MOVES_LIMIT)
			{
			    VG_4th =  VG_Moves[(VG_Moves_count-4)]; 
				VG_4th_time = VG_Moves_timestamp[(VG_Moves_count-4)];
			}
			if((VG_Moves_count-5) >= 0 && (VG_Moves_count-5) <= MOVES_LIMIT)
			{
			    VG_5th =  VG_Moves[(VG_Moves_count-5)]; 
				VG_5th_time = VG_Moves_timestamp[(VG_Moves_count-5)];
			}

			if(sprite[index].movement == RIGHT) 
			{
				direction = VG_RIGHT_FONT;
				opp_direction = VG_LEFT_FONT;
				direction_H = VG_RIGHT_FONT_H; 
				opp_direction_H = VG_LEFT_FONT_H;

				if(player == 1 && (sprite[index].dizzy == true || sprite[index].acid == true))
				{
					direction = VG_LEFT_FONT;   
					opp_direction = VG_RIGHT_FONT;  
					direction_H = VG_LEFT_FONT_H; 
					opp_direction_H = VG_RIGHT_FONT_H;
				}
			}
			else
			{
				direction = VG_LEFT_FONT;   
				opp_direction = VG_RIGHT_FONT;  
				direction_H = VG_LEFT_FONT_H; 
				opp_direction_H = VG_RIGHT_FONT_H;

				if(player == 1 && (sprite[index].dizzy == true || sprite[index].acid == true))
				{
					direction = VG_RIGHT_FONT; 
					opp_direction = VG_LEFT_FONT;
					direction_H = VG_RIGHT_FONT_H;  
					opp_direction_H = VG_LEFT_FONT_H;
				}
			}

		// ******************************************************************************//
		//                                    THROWS                                     //
		// ******************************************************************************//

		// Throws...(A, A)  // Slow punch 'K'   
		if(VG_EQUIPMENT != EQUIPMENT_BASIC && VG_EQUIPMENT != EQUIPMENT_JUST_COMBO)
		if((int)TimerGetTime() > VG_THROW_TIMER)  
		if((int)TimerGetTime() > VG_STRIKE_TIMER)
		if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
		if(sprite[index].handcuffed == false)  
		if(sprite[index].jumping == false)   
		if(sprite[index].pain == false)   
		if(sprite[index].knockdown == false)  
		if(sprite[index].electrocute == false)    
		if(sprite[index].status != VG_KNOCKSLIDE_FONT)  
		if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
		if(VG_THROWING == false)  
		if(sprite[index].status != VG_SECOND_STRIKE && sprite[index].status != VG_THIRD_STRIKE )
		if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT ) // direction
		if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH_THROW)
		if( VG_CheckMove(VG_KICK_AND_PUNCH_FONT, -1, -1, -1, -1)) //  || VG_CheckMove(-1, VG_KICK_AND_PUNCH_FONT, -1, -1, -1)
	//	if( VG_CheckMove(VG_PUNCH_FONT, VG_KICK_FONT, -1, -1, -1) || VG_CheckMove(VG_KICK_FONT, VG_PUNCH_FONT, -1, -1, -1)
	//	|| VG_CheckMove(VG_PUNCH_FONT_H, VG_KICK_FONT_H, -1, -1, -1) || VG_CheckMove(VG_KICK_FONT_H, VG_PUNCH_FONT_H, -1, -1, -1))
		{   
							  
			sprite[index].special = 0; 
			sprite[index].status = -1;       
			  
			if(player == 1) 
			{
				VG_1_Moves[(VG_1_Moves_count-1)] = VG_KICK_AND_PUNCH_FONT;
			//	VG_1_Moves_count-=1; 
				VG_1_MOVE_ACTIVE = false;
				// Over-ride any current move...
				Run_Moves(1, 1);
			}
			else
			{
				VG_2_Moves[(VG_2_Moves_count-1)] = VG_KICK_AND_PUNCH_FONT;
			//	VG_2_Moves_count-=1; 
				VG_2_MOVE_ACTIVE = false;
				// Over-ride any current move...
				Run_Moves(2, 1); 
			}

		}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)
		

		// ******************************************************************************//
		//                                    COMBOS                                     //
		// ******************************************************************************//
			// VG_SANG - Combo 1 - Second strike...(A, A)  // Slow punch 'K' 
		/*	if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) )
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_SANG)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_LENGTH)
			if(VG_CheckMove(VG_PUNCH_FONT, VG_PUNCH_FONT, -1, -1, -1))
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1;  

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO1;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO1;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}  

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_SANG - Combo 2 - Third strike...(K, COMBO1)  // Slow punch 'K' 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) )
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_SANG) 
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )  
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, VG_COMBO1, -1, -1, -1) || VG_CheckMove(VG_PUNCH2_FONT, -1, VG_COMBO1, -1, -1))
			if(!(VG_CheckMove(VG_COMBO1, VG_COMBO1, -1, -1, -1)))
			if(!(VG_CheckMove(VG_COMBO2, -1, -1, -1, -1)) && !(VG_CheckMove(-1, VG_COMBO2, -1, -1, -1)))
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1; 
				  
				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO2;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO2;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) */

			// VG_MINSO - Combo 1 - Second strike...(A, A)  // Slow punch 'K' 
			if((int)TimerGetTime() > VG_STRIKE_TIMER) 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false)  
			if(VG_CURRENT_CHAR == VG_MINSO)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_LENGTH)
			if(VG_CheckMove(VG_PUNCH_FONT, VG_PUNCH_FONT, -1, -1, -1))
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1;  

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO1;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO1;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1); 
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_MINSO - Combo 2 - Third strike...(K, COMBO1)  // Slow punch 'K' 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false)
			if(VG_CURRENT_CHAR == VG_MINSO) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_KICK_FONT, VG_COMBO1, -1, -1, -1) || VG_CheckMove(VG_KICK_FONT, -1, VG_COMBO1, -1, -1))
			if(!(VG_CheckMove(-1, VG_COMBO2, -1, -1, -1))) //  && !(VG_CheckMove(-1, -1, VG_COMBO2, -1)) 
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1; 
				  
				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO2;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO2;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_GYEONG - Combo 1 - Second strike...(A, A)  // Slow punch 'K'
			if((int)TimerGetTime() > VG_STRIKE_TIMER)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_GYEONG)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_LENGTH)
			if(VG_CheckMove(VG_PUNCH_FONT, VG_PUNCH_FONT, -1, -1, -1))
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1;  

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO1;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO1;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}   
				 
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_GYEONG - Combo 2 - Third strike...(K, COMBO1)  // Slow punch 'K' 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_GYEONG) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )  
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, VG_COMBO1, -1, -1, -1) || VG_CheckMove(VG_PUNCH2_FONT, -1, VG_COMBO1, -1, -1))
			if(!(VG_CheckMove(-1, VG_COMBO2, -1, -1, -1)) && !(VG_CheckMove(-1, -1, VG_COMBO2, -1, -1)) )
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1; 
				  
				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO2;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO2;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_SIU - Combo 1 - Second strike...(A, A)  // Slow punch 'K' 
			if((int)TimerGetTime() > VG_STRIKE_TIMER)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_SIU) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_LENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_KICK2_FONT, VG_KICK2_FONT, VG_KICK2_FONT, -1, -1))
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1;  

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO1;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else 
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO1;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);   
				}  

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_SIU - Combo 2 - Third strike...(K, COMBO1)  // Slow punch 'K' 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false)   
			if(VG_CURRENT_CHAR == VG_SIU)  
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT ) 
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_TOTALLENGTH) 
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_KICK2_FONT, VG_COMBO1, -1, -1, -1) || VG_CheckMove(VG_KICK2_FONT, -1, VG_COMBO1, -1, -1)) 
			if(!(VG_CheckMove(-1, VG_COMBO2, -1, -1, -1)) && !(VG_CheckMove(-1, -1, VG_COMBO2, -1, -1)) )
			{   
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1; 
				  
				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO2;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO2;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move... 
					Run_Moves(2, 1);
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_REESE - Combo 1 - Second strike...(A, A)  // Slow punch 'K' 
			if((int)TimerGetTime() > VG_STRIKE_TIMER)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_REESE) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_LENGTH)
			if(VG_CheckMove(VG_KICK2_FONT, VG_KICK2_FONT, -1, -1, -1))
			{   
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1;  

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO1;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO1;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}  
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_REESE - Combo 2 - Third strike...(K, COMBO1)  // Slow punch 'K' 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false)  
			if(VG_CURRENT_CHAR == VG_REESE) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )  
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, VG_COMBO1, -1, -1, -1) || VG_CheckMove(VG_PUNCH2_FONT, -1, VG_COMBO1, -1, -1))
			if(!(VG_CheckMove(-1, VG_COMBO2, -1, -1, -1)) && !(VG_CheckMove(-1, -1, VG_COMBO2, -1, -1)) )
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1; 
				  
				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO2;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO2;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)
			// VG_YOHAN - Combo 1 - Second strike...(A, A)  // Slow punch 'K' 
			if((int)TimerGetTime() > VG_STRIKE_TIMER)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_YOHAN)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_LENGTH)
			if(VG_CheckMove(VG_PUNCH_FONT, VG_PUNCH_FONT, -1, -1, -1))
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1;  

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO1;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO1;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}  

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_YOHAN - Combo 2 - Third strike...(K, COMBO1)  // Slow punch 'K' 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_YOHAN) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT ) 
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, VG_COMBO1, -1, -1, -1) || VG_CheckMove(VG_PUNCH2_FONT, -1, VG_COMBO1, -1, -1))
			if(!(VG_CheckMove(-1, VG_COMBO2, -1, -1, -1)) && !(VG_CheckMove(-1, -1, VG_COMBO2, -1, -1)) )
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1; 
				  
				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO2;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO2;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1); 
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_JAE - Combo 1 - Second strike...(A, A)  // Slow punch 'K' 
			if((int)TimerGetTime() > VG_STRIKE_TIMER)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_JAE)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_LENGTH)
			if(VG_CheckMove(VG_PUNCH_FONT, VG_PUNCH_FONT, -1, -1, -1))
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1;  

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO1;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO1;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_JAE - Combo 2 - Third strike...(K, COMBO1)  // Slow punch 'K' 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_JAE) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_KICK_FONT, VG_COMBO1, -1, -1, -1) || VG_CheckMove(VG_KICK_FONT, -1, VG_COMBO1, -1, -1))
			if(!(VG_CheckMove(-1, VG_COMBO2, -1, -1, -1)) && !(VG_CheckMove(-1, -1, VG_COMBO2, -1, -1)) )
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1; 
				  
				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO2;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO2;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_GUN - Combo 1 - Second strike...(A, A)  // Slow punch 'K' 
			if((int)TimerGetTime() > VG_STRIKE_TIMER)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_GUN) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_LENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, VG_PUNCH2_FONT, VG_PUNCH2_FONT, -1, -1))
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1;  

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO1;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO1;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}   

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_GUN - Combo 2 - Third strike...(K, COMBO1)  // Slow punch 'K' 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_GUN) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )  
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, VG_COMBO1, -1, -1, -1) || VG_CheckMove(VG_PUNCH2_FONT, -1, VG_COMBO1, -1, -1))
			if(!(VG_CheckMove(-1, VG_COMBO2, -1, -1, -1)) && !(VG_CheckMove(-1, -1, VG_COMBO2, -1, -1)) )
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1; 
				  
				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO2;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}  
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO2;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_KENNEDY - Combo 1 - Second strike...(A, A)  // Slow punch 'K' 
			if((int)TimerGetTime() > VG_STRIKE_TIMER)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false)  
			if(VG_CURRENT_CHAR == VG_KENNEDY) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_LENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, VG_PUNCH2_FONT, VG_PUNCH2_FONT, -1, -1))
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1;  

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO1;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO1;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}   

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_KENNEDY - Combo 2 - Third strike...(K, COMBO1)  // Slow punch 'K' 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_KENNEDY) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )  
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, VG_COMBO1, -1, -1, -1) || VG_CheckMove(VG_PUNCH2_FONT, -1, VG_COMBO1, -1, -1))
			if(!(VG_CheckMove(-1, VG_COMBO2, -1, -1, -1)) && !(VG_CheckMove(-1, -1, VG_COMBO2, -1, -1)) )
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1; 
				  
				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO2;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}  
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO2;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_HYUK - Combo 1 - Second strike...(A, A)  // Slow punch 'K' 
			if((int)TimerGetTime() > VG_STRIKE_TIMER)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false)  
			if(VG_CURRENT_CHAR == VG_HYUK) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_LENGTH)
			if(VG_CheckMove(VG_KICK_FONT, VG_KICK_FONT, -1, -1, -1))
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1;  

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO1;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}  
				else 
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO1;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}  

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_HYUK - Combo 2 - Third strike...(K, COMBO1)  // Slow punch 'K' 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false)   
			if(VG_CURRENT_CHAR == VG_HYUK)   
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )  
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_LENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_KICK2_FONT, VG_COMBO1, -1, -1, -1)  || VG_CheckMove(VG_KICK2_FONT, -1, VG_COMBO1, -1, -1))  
			if(!(VG_CheckMove(-1, VG_COMBO2, -1, -1, -1)) && !(VG_CheckMove(-1, -1, VG_COMBO2, -1, -1)) )
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1;  
				  
				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO2;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO2;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_SHO - Combo 1 - Second strike...(A, A)  // Slow punch 'K' 
			if((int)TimerGetTime() > VG_STRIKE_TIMER)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_SHO) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_LENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_PUNCH_FONT, VG_PUNCH_FONT, -1, -1, -1))
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1;  

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO1;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO1;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}   

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_SHO - Combo 2 - Third strike...(K, COMBO1)  // Slow punch 'K' 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_SHO) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )  
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, VG_COMBO1, -1, -1, -1) || VG_CheckMove(VG_PUNCH2_FONT, -1, VG_COMBO1, -1, -1))
			if(!(VG_CheckMove(-1, VG_COMBO2, -1, -1, -1)) && !(VG_CheckMove(-1, -1, VG_COMBO2, -1, -1)) )
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1; 
				  
				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO2;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}  
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO2;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_TIA - Combo 1 - Second strike...(A, A)  // Slow punch 'K' 
			if((int)TimerGetTime() > VG_STRIKE_TIMER) 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false)  
			if(VG_CURRENT_CHAR == VG_TIA)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_LENGTH)
			if(VG_CheckMove(VG_PUNCH_FONT, VG_PUNCH_FONT, -1, -1, -1))
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1;  

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO1;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO1;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1); 
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_TIA - Combo 2 - Third strike...(K, COMBO1)  // Slow punch 'K' 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false)
			if(VG_CURRENT_CHAR == VG_TIA) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_KICK_FONT, VG_COMBO1, -1, -1, -1) || VG_CheckMove(VG_KICK_FONT, -1, VG_COMBO1, -1, -1))
			if(!(VG_CheckMove(-1, VG_COMBO2, -1, -1, -1))) //  && !(VG_CheckMove(-1, -1, VG_COMBO2, -1)) 
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1; 
				  
				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO2;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO2;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_SAIZO - Combo 1 - Second strike...(A, A)  // Slow punch 'K'
			if((int)TimerGetTime() > VG_STRIKE_TIMER)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_SAIZO)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_LENGTH)
			if(VG_CheckMove(VG_PUNCH_FONT, VG_PUNCH_FONT, -1, -1, -1))
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1;  

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO1;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO1;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}   
				 
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_SAIZO - Combo 2 - Third strike...(K, COMBO1)  // Slow punch 'K' 
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(temp_VG_DOWN_pressed == false) 
			if(VG_CURRENT_CHAR == VG_SAIZO) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )  
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if((VG_2nd_time - VG_3rd_time) <= VG_COMBINE_COMBO_TOTALLENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, VG_COMBO1, -1, -1, -1) || VG_CheckMove(VG_PUNCH2_FONT, -1, VG_COMBO1, -1, -1))
			if(!(VG_CheckMove(-1, VG_COMBO2, -1, -1, -1)) && !(VG_CheckMove(-1, -1, VG_COMBO2, -1, -1)) )
			{  
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
				sprite[index].status = -1; 
				  
				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_COMBO2;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_COMBO2;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

		// ******************************************************************************//
		//                                  SPECIALS                                     //
		// ******************************************************************************//

			/////////////////////////////
			//      Reese Specials...  //
			/////////////////////////////

			// VG_REESE - Special 1 - Stretch arm mid...(->, ->, A or C)  // Slow punch 'K' 
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_REESE) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_PUNCH2_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																														
					sprite[index].status = -1; 
					sprite[index].special = 1;  

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}

					 
				}   

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_REESE - Special 2 - Stretch arm mid...(->, ->, A or C)  // Slow punch 'K' 
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_REESE) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_PUNCH_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_PUNCH_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																														
					sprite[index].status = -1; 
					sprite[index].special = 2; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}

				}  

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_REESE - Special 3 - Electric field...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_REESE) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL2_FONT ) // sprite[index].status != VG_SPECIAL1_FONT && 
			if(VG_1st == VG_KICK_FONT_H || VG_2nd == VG_KICK_FONT_H) 
			{  
				 
				sprite[index].status = -1;        
				sprite[index].special = 3;      
				      
				if(player == 1)   
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}  
				 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 

			// VG_REESE - Special 3 - Deflect field...(<-, ->, A or C)  
			if(VG_HAS_THIRD == true)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_REESE) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL2_FONT ) // sprite[index].status != VG_SPECIAL1_FONT && 
			if(VG_1st == VG_KICK2_FONT_H || VG_2nd == VG_KICK2_FONT_H) 
			{  
				 
				sprite[index].status = -1;        
				sprite[index].special = 4;      
				      
				if(player == 1)   
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				} 
				 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 

			// VG_SIU - Special 5 - Pistol shot...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_REESE)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, direction, -1, -1, -1) || VG_CheckMove(direction, VG_PUNCH2_FONT, -1, -1, -1))
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, opp_direction, -1, -1))
				{

				sprite[index].status = -1;  
				sprite[index].special = 5;   

				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false; 
					// Over-ride any current move... 
					Run_Moves(2, 1); 
				} 
				 
				}	 			 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 

			/////////////////////////////
			//      Yohan Specials...  //
			/////////////////////////////

			// VG_YOHAN - Special 1 - Vial mid...(->, ->, A or C)  // Slow punch 'K' 
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_YOHAN)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_PUNCH2_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																														
					sprite[index].status = -1; 
					sprite[index].special = 1; 
					 
					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				} 

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_YOHAN - Special 1 - Vial mid...(->, ->, A or C)  // Slow punch 'K'
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_YOHAN)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_PUNCH_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_PUNCH_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																														
					sprite[index].status = -1; 
					sprite[index].special = 2; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				}   

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)
			// VG_YOHAN - Special 3 - Bomb drop...(<-, <-, C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT)  
			if(VG_CURRENT_CHAR == VG_YOHAN)  
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT) //   
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_KICK2_FONT, opp_direction, -1, -1, -1)
			|| VG_CheckMove(opp_direction, VG_KICK2_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{ 

				sprite[index].status = -1;  
				sprite[index].special = 3;     
				  
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}   
		  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_YOHAN - Special 4 - Slide...(->, ->, A or C)  
			if(VG_HAS_THIRD == true)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_YOHAN)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_KICK_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_KICK_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{  
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 

					sprite[index].status = -1;  
					sprite[index].special = 4; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_YOHAN - Special 5 - Suicide...(<-, <-, C)  
			if(VG_HAS_THIRD == true)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT)  
			if(VG_CURRENT_CHAR == VG_YOHAN)  
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT) //   
			if(VG_1st == VG_PUNCH2_FONT_H || VG_2nd == VG_PUNCH2_FONT_H) 
			{ 

				sprite[index].status = -1;  
				sprite[index].special = 5;     
				  
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				} 

				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			///////////////////////////// 
			//      Minso Specials...  // 
			///////////////////////////// 

			// VG_MINSO - Special 1 - Tazer mid...(->, ->, A or C)  // Slow punch 'K' 
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_MINSO)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_PUNCH2_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{  
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																														
					sprite[index].status = -1; 
					sprite[index].special = 1; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}

				}  

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_MINSO - Special 2 - Tazer low...(->, ->, A or C)  //  Slow Kick 'm'
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT)  
			if(VG_CURRENT_CHAR == VG_MINSO)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_PUNCH_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_PUNCH_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																														
					sprite[index].status = -1; 
					sprite[index].special = 2; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}  
	 
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_MINSO - Special 3 - Dog attack...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT)  
			if(VG_CURRENT_CHAR == VG_MINSO)  
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL2_FONT ) // sprite[index].status != VG_SPECIAL1_FONT && 
			if(VG_1st == VG_PUNCH_FONT_H || VG_2nd == VG_PUNCH_FONT_H) 
			{ 

				sprite[index].status = -1;  
				sprite[index].special = 3;     
				  
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				} 
				 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)
			 
			// VG_MINSO - Special 3 - Panty shot...(<-, ->, A or C)  
			if(VG_HAS_THIRD == true)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT)  
			if(VG_CURRENT_CHAR == VG_MINSO) 
			if(sprite[index].jumping == true)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL2_FONT ) // sprite[index].status != VG_SPECIAL1_FONT && 
			if(VG_1st == VG_KICK2_FONT_H || VG_2nd == VG_KICK2_FONT_H) 
			{  

				sprite[index].status = -1;  
				sprite[index].special = 4;     
				  
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				} 
		 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			/////////////////////////////
			//     Trainer Specials... //
			/////////////////////////////

			// VG_TRAINER - Special 3 - Dog attack...(<-, ->, A or C) 
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_TRAINER)  
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
		//	if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if(VG_1st == VG_KICK_FONT_H || VG_2nd == VG_KICK_FONT_H) 
			{ 

				sprite[index].status = -1;   
				sprite[index].special = 3;     
				  
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				} 
			  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 

			// VG_TRAINER - Special 2 - Shotgun...(<-, ->, A or C) 
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_TRAINER)  
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
		//	if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if(VG_1st == VG_PUNCH_FONT_H || VG_2nd == VG_PUNCH_FONT_H) 
			{ 

				sprite[index].status = -1;  
				sprite[index].special = 2;     
				  
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				} 
				 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 

			/////////////////////////////
			//      Jae Specials...    //
			/////////////////////////////

			// VG_JAE - Special 1 - Dash forwards...(->, ->)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_JAE) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_DASH_LENGTH)
			if(VG_1st == direction)
			if(VG_2nd == direction)      
			{ 

				sprite[index].status = -1;      
				sprite[index].special = 1;   

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_2_Moves_count-=1;  
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);     
				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_JAE - Special 2 - Dash backwards...(<-, <-)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_JAE) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT ) 
			if((VG_1st_time - VG_2nd_time) <= VG_DASH_LENGTH)
			if(VG_1st == opp_direction)
			if(VG_2nd == opp_direction)      
			{ 

				sprite[index].status = -1;      
				sprite[index].special = 2;  

				if(player == 1) 
				{
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else
				{ 
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1); 
				} 
					  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_JAE - Special 3 - Uzi shot...(<-, ->, A or C)   
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_JAE)   
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
		//	if(sprite[index].status != VG_SPECIAL2_FONT ) // sprite[index].status != VG_SPECIAL1_FONT &&  
			if(VG_1st == VG_PUNCH_FONT_H || VG_2nd == VG_PUNCH_FONT_H) 
			{ 

				sprite[index].status = -1;  
				sprite[index].special = 3;     
				  
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{   
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1); 
				}   
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 
			// VG_JAE - Special 4 -  Breakdance......(<-, ->, A or C)   
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_JAE)   
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(!(sprite[index].special == 4))
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_KICK_FONT, opp_direction, -1, -1, -1)
			|| VG_CheckMove(opp_direction, VG_KICK_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			) 
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 

					sprite[index].status = -1;   
					sprite[index].special = 4;     
				  
					if(player == 1)  
					{
						VG_1_Pistolsfx = 0;
						VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
					//	VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					} 
					else 
					{  
						VG_2_Pistolsfx = 0;
						VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
					//	VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}   

				}
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 

			// VG_JAE - Special 5 - Mad dash...(->, ->, A or C)  
			if(VG_HAS_THIRD == true)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_JAE)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_KICK2_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_KICK2_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			) 
			{    
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
				if(VG_CheckMove(-1, -1, opp_direction, -1, -1))
				{ 

					sprite[index].status = -1;  
					sprite[index].special = 5; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			/////////////////////////////
			//     Hyuk Specials...    //
			/////////////////////////////

			// VG_HYUK - Special 1 - Grenade...(->, ->, A or C)  // Slow punch 'K' 
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_HYUK)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)
			if(VG_CheckMove(VG_KICK2_FONT, direction, -1, -1, -1) || VG_CheckMove(direction, VG_KICK2_FONT, -1, -1, -1))
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, opp_direction, -1, -1))
				{ 

					sprite[index].status = -1;   
					sprite[index].special = 2; 
					 
					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_HYUK - Special 2 - Uzi shot...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_HYUK)  
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
		//	if(sprite[index].status != VG_SPECIAL1_FONT ) //  && sprite[index].status != VG_SPECIAL2_FONT
			if(VG_1st == VG_PUNCH2_FONT_H || VG_2nd == VG_PUNCH2_FONT_H) 
			{ 

				sprite[index].status = -1;   
				sprite[index].special = 3;     
				  
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move... 
					Run_Moves(2, 1);
				} 
				 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 

			// VG_HYUK - Special 2 - Uzi shot...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_HYUK)  
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
	//		if(sprite[index].status != VG_SPECIAL1_FONT ) //  && sprite[index].status != VG_SPECIAL2_FONT
			if(VG_1st == VG_PUNCH_FONT_H || VG_2nd == VG_PUNCH_FONT_H) 
			{ 

				sprite[index].status = -1;  
				sprite[index].special = 4;     
				  
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}  
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}  
				 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 

			// VG_HYUK - Special 1 - Golf club...(->, ->, A or C)  // Slow punch 'K' 
			if(VG_HAS_THIRD == true)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_HYUK)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT) //   
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_KICK_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_KICK_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH) 
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 

					sprite[index].status = -1; 
					sprite[index].special = 1; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				} 

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			/////////////////////////////
			//        Gun Specials...  //
			/////////////////////////////

			// VG_GUN - Special 1 - Torpedo punch...(->, ->, A or C)  // Slow punch 'K' 
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_GUN)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT) //   
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_PUNCH2_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 

					sprite[index].status = -1; 
					sprite[index].special = 1; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_GUN - Special 1 - Torpedo punch...(->, ->, A or C)  // Slow punch 'K' 
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_GUN)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT) //   
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_PUNCH_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_PUNCH_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 

					sprite[index].status = -1; 
					sprite[index].special = 2; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				} 

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)
			     
			// VG_GUN - Special 3 - Clothesline...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_GUN)  
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL2_FONT ) 
			if(VG_1st == VG_KICK2_FONT_H || VG_2nd == VG_KICK2_FONT_H)
			{ 

				sprite[index].status = -1;  
				sprite[index].special = 3;     
				    
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				} 
				 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_GUN - Special 1 - Whiplash...(->, ->, A or C)  // Slow punch 'K' 
			if(VG_HAS_THIRD == true)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_GUN)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT) //   
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_KICK2_FONT, opp_direction, -1, -1, -1)
			|| VG_CheckMove(opp_direction, VG_KICK2_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, opp_direction, -1, -1))
				{ 

					sprite[index].status = -1; 
					sprite[index].special = 4; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				} 

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			/////////////////////////////
			//        Kennedy Specials...  //
			/////////////////////////////

			// VG_KENNEDY - Special 1 - Torpedo punch...(->, ->, A or C)  // Slow punch 'K' 
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_KENNEDY)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT) //   
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_PUNCH2_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 

					sprite[index].status = -1; 
					sprite[index].special = 1; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_KENNEDY - Special 1 - Torpedo punch...(->, ->, A or C)  // Slow punch 'K' 
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_KENNEDY)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT) //   
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_PUNCH_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_PUNCH_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 

					sprite[index].status = -1; 
					sprite[index].special = 2; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				} 

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)
			     
			// VG_KENNEDY - Special 3 - Clothesline...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_KENNEDY)  
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL2_FONT ) 
			if(VG_1st == VG_KICK2_FONT_H || VG_2nd == VG_KICK2_FONT_H)
			{ 

				sprite[index].status = -1;  
				sprite[index].special = 3;     
				    
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				} 
				 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_KENNEDY - Special 1 - Whiplash...(->, ->, A or C)  // Slow punch 'K' 
			if(VG_HAS_THIRD == true)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_KENNEDY)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT) //   
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_KICK2_FONT, opp_direction, -1, -1, -1)
			|| VG_CheckMove(opp_direction, VG_KICK2_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, opp_direction, -1, -1))
				{ 

					sprite[index].status = -1; 
					sprite[index].special = 4; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				} 

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			/////////////////////////////
			//       Sang Specials...  //
			/////////////////////////////

			// VG_SANG - Special 2 - Flamethrower...(->, ->, A or C)  // Slow punch 'K' 
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_SANG) 
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)
			if(VG_CheckMove(VG_KICK_FONT, direction, -1, -1, -1) || VG_CheckMove(direction, VG_KICK_FONT, -1, -1, -1))
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, opp_direction, -1, -1))
				{ 

					sprite[index].status = -1; 
					sprite[index].special = 2; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}

				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_SANG - Special 2 - Uzi shot...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_SANG)  
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
		//	if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if(VG_1st == VG_PUNCH_FONT_H || VG_2nd == VG_PUNCH_FONT_H) 
			{ 

				sprite[index].status = -1;  
				sprite[index].special = 3;     
				  
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else  
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				} 
				 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 

			// VG_SANG - Special 2 - Uzi shot...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_SANG)  
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
	//		if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if(VG_1st == VG_PUNCH2_FONT_H || VG_2nd == VG_PUNCH2_FONT_H) 
			{ 

				sprite[index].status = -1;  
				sprite[index].special = 4;     
				  
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				} 
				 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 

			/////////////////////////////
			//     Gyeong Specials...  //
			/////////////////////////////

			// Gyeong - Special 1 - Torpedo punch...(->, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_GYEONG)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_KICK_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_KICK_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{  
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 

					sprite[index].status = -1;  
					sprite[index].special = 1; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// Gyeong - Special 1 - Torpedo punch...(->, ->, A or C) 
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_GYEONG)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT ) // VG_KICK2_FONT
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_KICK2_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_KICK2_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{  
					  
					sprite[index].status = -1; 
					sprite[index].special = 2; 

					if(player == 1)  
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				}   

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// Gyeong - Special 1 - Uppercut...(->, ->, A or C)
			if(VG_HAS_THIRD == true)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_GYEONG)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_KICK2_FONT, opp_direction, -1, -1, -1)
			|| VG_CheckMove(opp_direction, VG_KICK2_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			) 
			{  
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
				if(VG_CheckMove(-1, -1, opp_direction, -1, -1))
				{ 

					sprite[index].status = -1;  
					sprite[index].special = 5;  

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// Gyeong - Special 2 - Pistol shot...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT)   
			if(VG_CURRENT_CHAR == VG_GYEONG)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if( VG_CheckMove(VG_PUNCH2_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_PUNCH2_FONT, opp_direction, -1, -1) 
			)   
			{  
				// -> 
				if((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH) // 
				if(VG_CheckMove(-1, -1, opp_direction, -1, -1)) // opp_direction
				{
					 
				sprite[index].status = -1;  
				sprite[index].special = 3;   

				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else  
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}  

				}    
				    
				   
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 

			// Gyeong - Special 2 - Pistol shot...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT)   
			if(VG_CURRENT_CHAR == VG_GYEONG)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT ) 
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH) 
			if( VG_CheckMove(VG_PUNCH_FONT, direction, -1, -1, -1) 
			|| VG_CheckMove(direction, VG_PUNCH_FONT, opp_direction, -1, -1)   
			)
			{  
				// -> 
				if((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
				if(VG_CheckMove(-1, -1, opp_direction, -1, -1)) // opp_direction
				{

				sprite[index].status = -1;         
				sprite[index].special = 4;  

				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}

				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			/////////////////////////////
			//        Siu Specials...  //
			/////////////////////////////

			// VG_SIU - Special 3 - Pistol shot...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_SIU)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, direction, -1, -1, -1) || VG_CheckMove(direction, VG_PUNCH2_FONT, -1, -1, -1))
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, opp_direction, -1, -1))
				{

				sprite[index].status = -1;  
				sprite[index].special = 3;   

				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false; 
					// Over-ride any current move... 
					Run_Moves(2, 1); 
				} 
				 
				}	 			 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 

			// VG_SIU - Special 4 - Pistol shot...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_SIU)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )  
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 
			if(VG_CheckMove(VG_PUNCH_FONT, direction, -1, -1, -1) || VG_CheckMove(direction, VG_PUNCH_FONT, -1, -1, -1))
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, opp_direction, -1, -1))
				{

				sprite[index].status = -1;       
				sprite[index].special = 4;  

				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				}
				else
				{
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				}

				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_SIU - Special 2 - Pigeon attack...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT)  
			if(VG_CURRENT_CHAR == VG_SIU)  
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT ) // sprite[index].status != VG_SPECIAL1_FONT && 
			if(VG_1st == VG_KICK2_FONT_H || VG_2nd == VG_KICK2_FONT_H) 
			{ 

				sprite[index].status = -1;  
				sprite[index].special = 2;     
				  
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);  
				}  
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				} 
				 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_SIU - Special 1 - Slide...(->, ->, A or C)  
			if(VG_HAS_THIRD == true)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_SIU)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if(VG_CheckMove(VG_KICK_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_KICK_FONT, -1, -1, -1) &&  (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{  
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{ 

					sprite[index].status = -1;  
					sprite[index].special = 1; 

					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}


				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			////////////
			// VG_SHO //
			////////////

			 // VG_SHO - Special 1 - Slide...(->, ->, A or C)  
			if (VG_HAS_THIRD == true)
			if ((VG_Moves_count - 2) >= 0 && (VG_Moves_count - 2) <= MOVES_LIMIT)
			if (VG_CURRENT_CHAR == VG_SHO)
			if (sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if (sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT)
			if ((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if (VG_CheckMove(VG_KICK_FONT, direction, -1, -1, -1)
			|| VG_CheckMove(direction, VG_KICK_FONT, -1, -1, -1) && (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{
				// ->
				if ((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
					if (VG_CheckMove(-1, -1, direction, -1, -1))
					{

						sprite[index].status = -1;
						sprite[index].special = 1;

						if (player == 1)
						{
							VG_1_Moves[(VG_1_Moves_count - 2)] = VG_SPECIAL1_FONT;
							VG_1_Moves_count -= 1;
							VG_1_MOVE_ACTIVE = false;
							// Over-ride any current move...
							Run_Moves(1, 1);
						}
						else
						{
							VG_2_Moves[(VG_2_Moves_count - 2)] = VG_SPECIAL1_FONT;
							VG_2_Moves_count -= 1;
							VG_2_MOVE_ACTIVE = false;
							// Over-ride any current move...
							Run_Moves(2, 1);
						}


					}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_SHO - Special 2 - FlameKick...(<-, <-, A or C)  
			if (VG_HAS_THIRD == true)
			if ((VG_Moves_count - 2) >= 0 && (VG_Moves_count - 2) <= MOVES_LIMIT)
			if (VG_CURRENT_CHAR == VG_SHO)
			if (sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if (sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT)
			if ((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if (VG_CheckMove(VG_KICK_FONT, opp_direction, -1, -1, -1)
			|| VG_CheckMove(opp_direction, VG_KICK_FONT, -1, -1, -1) && (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{
				// ->
				if ((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
					if (VG_CheckMove(-1, -1, opp_direction, -1, -1))
					{

						sprite[index].status = -1;
						sprite[index].special = 2;

						if (player == 1)
						{
							VG_1_Moves[(VG_1_Moves_count - 2)] = VG_SPECIAL1_FONT;
							VG_1_Moves_count -= 1;
							VG_1_MOVE_ACTIVE = false;
							// Over-ride any current move...
							Run_Moves(1, 1);
						}
						else
						{
							VG_2_Moves[(VG_2_Moves_count - 2)] = VG_SPECIAL1_FONT;
							VG_2_Moves_count -= 1;
							VG_2_MOVE_ACTIVE = false;
							// Over-ride any current move...
							Run_Moves(2, 1);
						}


					}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_SHO - Special 3 - Fireball...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_SHO)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, direction, -1, -1, -1) || VG_CheckMove(direction, VG_PUNCH2_FONT, -1, -1, -1))
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, direction, -1, -1))
				{

				sprite[index].status = -1;  
				sprite[index].special = 3;   

				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false; 
					// Over-ride any current move... 
					Run_Moves(2, 1); 
				} 
				 
				}	 			 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 


			////////////
			// VG_TIA //
			////////////
			
			// VG_TIA - Special 3 - Fireball...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_TIA)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, direction, -1, -1, -1) || VG_CheckMove(direction, VG_PUNCH2_FONT, -1, -1, -1))
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, opp_direction, -1, -1))
				{

				sprite[index].status = -1;  
				sprite[index].special = 1;   

				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false; 
					// Over-ride any current move... 
					Run_Moves(2, 1); 
				} 
				 
				}	 			 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 

			// VG_TIA - Special 2 - Uppercut...(<-, <-, A or C)  
			if (VG_HAS_THIRD == true)
			if ((VG_Moves_count - 2) >= 0 && (VG_Moves_count - 2) <= MOVES_LIMIT)
			if (VG_CURRENT_CHAR == VG_TIA)
			if (sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if (sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT)
			if ((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if (VG_CheckMove(VG_PUNCH2_FONT, opp_direction, -1, -1, -1)
			|| VG_CheckMove(opp_direction, VG_PUNCH2_FONT, -1, -1, -1) && (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{
				// ->
				if ((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
					if (VG_CheckMove(-1, -1, opp_direction, -1, -1))
					{

						sprite[index].status = -1;
						sprite[index].special = 2;

						if (player == 1)
						{
							VG_1_Moves[(VG_1_Moves_count - 2)] = VG_SPECIAL1_FONT;
							VG_1_Moves_count -= 1;
							VG_1_MOVE_ACTIVE = false;
							// Over-ride any current move...
							Run_Moves(1, 1);
						}
						else
						{
							VG_2_Moves[(VG_2_Moves_count - 2)] = VG_SPECIAL1_FONT;
							VG_2_Moves_count -= 1;
							VG_2_MOVE_ACTIVE = false;
							// Over-ride any current move...
							Run_Moves(2, 1);
						}


					}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			 // VG_TIA - Special 3 - Slide...(->, ->, A or C)  
			if (VG_HAS_THIRD == true)
			if ((VG_Moves_count - 2) >= 0 && (VG_Moves_count - 2) <= MOVES_LIMIT)
			if (VG_CURRENT_CHAR == VG_TIA)
			if (sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if (sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT)
			if ((VG_1st_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
			if (VG_CheckMove(VG_KICK_FONT, opp_direction, -1, -1, -1)
			|| VG_CheckMove(opp_direction, VG_KICK_FONT, -1, -1, -1) && (VG_1st_time - VG_2nd_time <= VG_SPECIAL_BOTH_LENGTH)
			)
			{
				// ->
				if ((VG_3rd_time - VG_2nd_time) <= VG_SPECIAL_WAIT_LENGTH)
					if (VG_CheckMove(-1, -1, opp_direction, -1, -1))
					{

						sprite[index].status = -1;
						sprite[index].special = 3;

						if (player == 1)
						{
							VG_1_Moves[(VG_1_Moves_count - 2)] = VG_SPECIAL1_FONT;
							VG_1_Moves_count -= 1;
							VG_1_MOVE_ACTIVE = false;
							// Over-ride any current move...
							Run_Moves(1, 1);
						}
						else
						{
							VG_2_Moves[(VG_2_Moves_count - 2)] = VG_SPECIAL1_FONT;
							VG_2_Moves_count -= 1;
							VG_2_MOVE_ACTIVE = false;
							// Over-ride any current move...
							Run_Moves(2, 1);
						}


					}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)


			//////////////
			// VG_SAIZO //
			//////////////

			// VG_SAIZO - Special 1 - Bomb...(->, ->, A or C)  // Slow punch 'K' 
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_SAIZO)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)
			if(VG_CheckMove(VG_KICK2_FONT, direction, -1, -1, -1) || VG_CheckMove(direction, VG_KICK2_FONT, -1, -1, -1))
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, opp_direction, -1, -1))
				{ 

					sprite[index].status = -1;   
					sprite[index].special = 1; 
					 
					if(player == 1) 
					{
						VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_1_Moves_count-=1; 
						VG_1_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(1, 1);
					}
					else
					{
						VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
						VG_2_Moves_count-=1; 
						VG_2_MOVE_ACTIVE = false;
						// Over-ride any current move...
						Run_Moves(2, 1);
					}

				}

			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)


			// VG_SAIZO - Special 2 - Eagle attack...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP1)
			if((VG_Moves_count-1) >= 0 && (VG_Moves_count-1) <= MOVES_LIMIT)  
			if(VG_CURRENT_CHAR == VG_SAIZO)  
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT ) // sprite[index].status != VG_SPECIAL1_FONT && 
			if(VG_1st == VG_PUNCH2_FONT_H || VG_2nd == VG_PUNCH2_FONT_H) 
			{ 

				sprite[index].status = -1;  
				sprite[index].special = 2;     
				  
				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);  
				}  
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-1)] = VG_SPECIAL1_FONT;
				//	VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(2, 1);
				} 
				 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)

			// VG_SAIZO - Special 3 - Kunai...(<-, ->, A or C)  
			if(VG_EQUIPMENT == EQUIPMENT_ALL || VG_EQUIPMENT == EQUIPMENT_JUST_SP2)
			if((VG_Moves_count-2) >= 0 && (VG_Moves_count-2) <= MOVES_LIMIT) 
			if(VG_CURRENT_CHAR == VG_SAIZO)
			if(sprite[index].status != VG_KICK_AND_PUNCH_FONT)
			if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH)
			if(VG_CheckMove(VG_PUNCH2_FONT, direction, -1, -1, -1) || VG_CheckMove(direction, VG_PUNCH2_FONT, -1, -1, -1))
			{ 
				// ->
				if((VG_3rd_time - VG_2nd_time) <= VG_COMBINE_LONG_LENGTH)
				if(VG_CheckMove(-1, -1, opp_direction, -1, -1))
				{

				sprite[index].status = -1;  
				sprite[index].special = 3;   

				if(player == 1)  
				{
					VG_1_Pistolsfx = 0;
					VG_1_Moves[(VG_1_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_1_Moves_count-=1; 
					VG_1_MOVE_ACTIVE = false;
					// Over-ride any current move...
					Run_Moves(1, 1);
				} 
				else 
				{  
					VG_2_Pistolsfx = 0;
					VG_2_Moves[(VG_2_Moves_count-2)] = VG_SPECIAL1_FONT;
					VG_2_Moves_count-=1; 
					VG_2_MOVE_ACTIVE = false; 
					// Over-ride any current move... 
					Run_Moves(2, 1); 
				} 
				 
				}	 			 
				  
			}// if((VG_1st_time - VG_2nd_time) <= VG_COMBINE_LENGTH) 



		// END OF LIST //

		} // (VG_Moves_count-2) >= 0

	} // (VG_Moves_count-1) >= 0)   

}


void VG_Reset_Player(int player) 
{
	if(player == 1)
	{
		VG_SHAKE_1 = false;
		VG_1_ARM_LENGTH = false;
		VG_1_MOVE_ACTIVE = false;
		points[0].active = 0;  
		points[2].active = 0;
		VG_1_MovesList_count = 0; 
		sprite[2].status = -1;
		sprite[2].special = 0;
		sprite[2].invulnerable = false;
		sprite[2].electrocute = false; 

		VG_1_Pistolsfx = 0;
		VG_1_Mgunsfx = 0; 
		VG_reloadsfx = 0;
		VG_reloadedsfx = 0; 
		VG_1_chop_sfx = 0;
		VG_1_special1_sfx = 0;
		VG_1_Vialsfx = 0;
		VG_1_Grenadesfx = 0;
		VG_1_Knifesfx = 0;  
		VG_1_Pfpsfx = 0;   

		VG_1_cur = 0;  


		sprite[2].anim_state = WAIT;
		sprite[2].hit_opponent = false;

		sprite[2].pain = false;  
		sprite[2].status = -1;  

		sprite[2].strafe = false;

		if(VG_1_DOWN_pressed == true)
			sprite[2].ducking = 3;

	}	

	if(player == 2)
	{
		VG_SHAKE_2 = false;
		VG_2_ARM_LENGTH = false;
		VG_2_MOVE_ACTIVE = false;  

		points[1].active = 0;    
		points[3].active = 0; 
		VG_2_MovesList_count = 0;
		sprite[3].status = -1;  
		sprite[3].special = 0;
		sprite[3].invulnerable = false; 
		sprite[3].electrocute = false;

		VG_2_Pistolsfx = 0;
		VG_2_Mgunsfx = 0;
		VG_reloadsfx = 0; 
		VG_reloadedsfx = 0;  
		VG_2_chop_sfx = 0; 
		VG_2_special1_sfx = 0;
		VG_2_Vialsfx = 0;
		VG_2_Grenadesfx = 0; 
		VG_2_Knifesfx = 0; 
		VG_2_Pfpsfx = 0; 
					     
		VG_2_cur = 0;
 

		sprite[3].anim_state = WAIT;
		sprite[3].hit_opponent = false;

		sprite[3].pain = false; 
		sprite[3].status = -1;  

		sprite[3].strafe = false;

		if(VG_2_DOWN_pressed == true)
			sprite[3].ducking = 3;
	}


}