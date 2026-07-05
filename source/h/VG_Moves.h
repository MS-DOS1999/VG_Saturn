#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64  
#define WIN32_LEAN_AND_MEAN    
#include <windows.h>
#endif   

extern void Set_Vibration(int player, int left, int right, int time);
void VG_Play_Sound(int player, int sound);
void Run_Moves(int player, int f_rate);

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
extern void Run_Moves_SHO(int player, int f_rate);
extern void Run_Moves_TIA(int player, int f_rate);
extern void Run_Moves_SAIZO(int player, int f_rate);
extern void Run_Moves_KENNEDY(int player, int f_rate);

extern void VG_Reset_Player(int player);
extern void VG_SlowMO(int duration, float strength);

extern void VG_Particles(float x, float y, float angle, int priority, int anim);

void VG_Do_Shake(int length, float strength)
{

	if(SHAKE_CAM_WHEN_HIT == 1)
	{
		// Shake camera...
		VG_SHAKE_CAMERA_LENGTH = length;
		VG_SHAKE_CAMERA = true; 
		VG_SHAKE_UP = 0;
		VG_shake_timer = 0;
		VG_shake_length_timer = (int)TimerGetTime() + length; 
		VG_shake_strength = strength;
	}

}

void VG_Reset_sprite(int index)
{
	int anim=0;
	bool temp_VG_DOWN_pressed=false;

	if(index == 2)
	{
		temp_VG_DOWN_pressed = VG_1_DOWN_pressed; // VG_1_DOWN_pressed
	}
	else
	{
		temp_VG_DOWN_pressed = VG_2_DOWN_pressed; // VG_2_DOWN_pressed
	}

	if(index > 0 && index < TOTAL_NO_SPRITES)
	{
		sprite[index].anim_state = WAIT;    
		sprite[index].anim = 0;
		sprite[index].status = -1;      
		sprite[index].update = true;   
	}

}

void VG_Reset_all_anims()   
{ 
	int fx_id=0;
	int fx_anim=0;
	int fx_cur=0;
	int original_length=0;
	int original_frame_length=0;
	int cur_frame_length=0;
	int frame_length=0;
	int difference = 0;

	// Resets all current animations during slowmo ended...
	for(int i=0;i<no_sprites;i++)
	if(i < TOTAL_NO_SPRITES)
	{ 
		fx_id = sprite[i].fx_id;
		fx_anim = sprite[i].anim; 
		fx_cur = sprite[i].cur; 
		
#ifndef DREAMCAST
		if(fx_id >= 0 && fx_id < 75)   
		if(fx_anim >= 0 && fx_anim < 256)  
		if(fx_cur >= 0 && fx_cur < 256)
		if(VG_slowmof > 0.0f) 
		if((a_texture[fx_id].anims[fx_anim][fx_cur]) >= 0 && (a_texture[fx_id].anims[fx_anim][fx_cur]) < 256)
		{
		//	original_frame_length = sprite[i].cur_dest_time - sprite[i].cur_start_time; // 1200 - 1000 = 200...
		//	original_length = original_frame_length + sprite[i].cur_start_time; // 200 + 1000 = 1200...
			difference = sprite[i].cur_dest_time  - (int)TimerGetTime(); // 1200 - (t)1100 = 100ms...

			if(sprite[i].last_slowmo > 0.0f) 
				difference = difference / (int)sprite[i].last_slowmo;
		//		difference = (int)((float)difference / sprite[i].last_slowmo);

			// frame_length = (a_texture[sprite[i].fx_id].delay[ (a_texture[sprite[i].fx_id].anims[sprite[i].anim][sprite[i].cur]) ]) - difference; // 100ms - 75ms = 25ms..
			frame_length = difference * (int)VG_slowmof; // Resize the remaining length by slow motion... 100 * 2.0f = 200ms

			// This is like timergettime + 1000;
			sprite[i].cur_time = (int)TimerGetTime() + frame_length; // (t)1100ms + 200ms.. = 1300
			sprite[i].cur_dest_time = sprite[i].cur_time; // 1300
			sprite[i].last_slowmo = VG_slowmof; // 2.0f

		}
#else
		if(fx_id >= 0 && fx_id < 75)   
		if(fx_anim >= 0 && fx_anim < 256)  
		if(fx_cur >= 0 && fx_cur < 256)
		if(VG_slowmof > 0.0f) 
		if((a_texture_get_anims_secondlayer(fx_id, fx_anim, fx_cur)) >= 0 && (a_texture_get_anims_secondlayer(fx_id, fx_anim, fx_cur)) < 256)
		{
		//	original_frame_length = sprite[i].cur_dest_time - sprite[i].cur_start_time; // 1200 - 1000 = 200...
		//	original_length = original_frame_length + sprite[i].cur_start_time; // 200 + 1000 = 1200...
			//printf("SUCE MA BITE %d / %d\n", i, TOTAL_NO_SPRITES);
			difference = sprite[i].cur_dest_time  - (int)TimerGetTime(); // 1200 - (t)1100 = 100ms...

			if(sprite[i].last_slowmo > 0.0f) 
				difference = difference / (int)sprite[i].last_slowmo;
		//		difference = (int)((float)difference / sprite[i].last_slowmo);

			// frame_length = (a_texture[sprite[i].fx_id].delay[ (a_texture[sprite[i].fx_id].anims[sprite[i].anim][sprite[i].cur]) ]) - difference; // 100ms - 75ms = 25ms..
			frame_length = difference * (int)VG_slowmof; // Resize the remaining length by slow motion... 100 * 2.0f = 200ms

			// This is like timergettime + 1000;
			sprite[i].cur_time = (int)TimerGetTime() + frame_length; // (t)1100ms + 200ms.. = 1300
			sprite[i].cur_dest_time = sprite[i].cur_time; // 1300
			sprite[i].last_slowmo = VG_slowmof; // 2.0f

		}
#endif
	}
	
}

int VG_Get_anim_length(int id, int the_anim, bool run_slowmo)
{
	int length = 0;
	int index = 0;
	int anim_time=0; 
	int no_of_frames=0;

	if(id >= 0 && id < TOTAL_NO_SPRITES)
	if(sprite[id].fx_id >= 0 && sprite[id].fx_id < 75)
	if(the_anim >= 0 && the_anim < 256)
	if(sprite[id].cur >= 0 && sprite[id].cur < 256)
	if(VG_slowmof > 0.0f)
	{
		if(sprite[id].fx_id < 50 && the_anim < 256)
		{
			no_of_frames = a_texture[sprite[id].fx_id].anim_frames[the_anim];
#ifndef DREAMCAST
			for(int j=0;j<no_of_frames;j++) 
			if((a_texture[sprite[id].fx_id].anims[the_anim][j]) > 0 && (a_texture[sprite[id].fx_id].anims[the_anim][j]) < 256)
				length += (a_texture[sprite[id].fx_id].delay[ (a_texture[sprite[id].fx_id].anims[the_anim][j]) ]*(int)VG_slowmof);
#else
			for(int j=0;j<no_of_frames;j++) 
			if((a_texture_get_anims_secondlayer(sprite[id].fx_id, the_anim, j)) > 0 && (a_texture_get_anims_secondlayer(sprite[id].fx_id, the_anim, j)) < 256)
				length += (a_texture_get_delay(sprite[id].fx_id, (a_texture_get_anims_secondlayer(sprite[id].fx_id,the_anim,j)))*(int)VG_slowmof);
#endif
		}

	}
	    
//	length = (int)TimerGetTime() + 1000000;    

	return(length);  
} 

bool VG_Hit_player(int player_hit, int type, int f_rate)
{
	int index = 0;
	int punching_guy=0;
	int anim_time=0; 
	int no_of_anims=0;
	int pain_anim=0; 
	int VG_DAMAGE=0;
	int VG_BLOCK_REDUCE = 1;
	bool was_blocked=false;
	bool block_worked=true;
	int VG_status=0;
	int other_player=0;
	int VG_CURRENT_CHAR = 0;
	int VG_OTHER_CHAR = 0;
	bool VG_CORNERED = false;
	bool temp_VG_DOWN_pressed = false; 
	bool electrocuted = false;
	bool bullet_attack = false;
	bool VG_ARM_LENGTH = false;
	bool is_power_move=false;
	bool throw_move=false;
	bool no_slowmo = false;
	int VG_hits=0;
	bool vial_attack = false;
	bool handcuff_corner_bug=false;
          
	if(f_rate <= 0)                                                
	    f_rate = 1;        

	if(f_rate >= 50)
		f_rate = 50; 

	// Shake camera...
//	VG_Do_Shake(250, 0.0020f);

	// Player here is the guy that was hit...
	if(player_hit == 1)
	{
		VG_CORNERED = VG_1_CORNERED;
		VG_hits = VG_2_hits;
		VG_ARM_LENGTH = VG_1_ARM_LENGTH;
		other_player = 2; 
		index = 2;
		sprite[2].deflect = false;
		VG_CURRENT_CHAR = VG_1_CHARACTER; 
		VG_OTHER_CHAR = VG_2_CHARACTER; 
		punching_guy = 3;
		VG_Reset_sprite(2);
		points[0].active = 0;
		points[2].active = 0;
		VG_status = sprite[punching_guy].status;
		temp_VG_DOWN_pressed = VG_1_DOWN_pressed;
	} 
	else
	{
		VG_CORNERED = VG_2_CORNERED;
		VG_hits = VG_1_hits;
		VG_ARM_LENGTH = VG_2_ARM_LENGTH;
		other_player = 1;
		index = 3;   
		sprite[3].deflect = false;
		VG_CURRENT_CHAR = VG_2_CHARACTER;
		VG_OTHER_CHAR = VG_1_CHARACTER;
		punching_guy = 2;      
		VG_Reset_sprite(3);
		points[1].active = 0; 
		points[3].active = 0;
		VG_status = sprite[punching_guy].status;
		temp_VG_DOWN_pressed = VG_2_DOWN_pressed; 
	} 
	  
	  
	if(VG_CORNERED == true)
	if(sprite[index].status == VG_KNOCKSLIDE_FONT)
	if(sprite[index].handcuffed == true&& VG_hits >= 2)
		handcuff_corner_bug = true; 

	// Need to turn off arm sprite here...
//	if(VG_CURRENT_CHAR == VG_REESE)
	if(VG_ARM_LENGTH == true) 
	{
		for(int i=0;i<no_fx;i++) 
		{
			if(Fx[i].sector == FX_ARM)
			if(Fx[i].value3 == index)
			{
				Fx[i].turn_off = true;
			}
		}
		if(player_hit == 1)
			VG_1_ARM_LENGTH = false;
		else
			VG_2_ARM_LENGTH = false;
	}
	// Need to turn off flame sprite here...
	if(VG_CURRENT_CHAR == VG_SANG)
	if(VG_ARM_LENGTH == true) 
	{
		for(int i=0;i<no_fx;i++) 
		{
			if(Fx[i].sector == FX_FLAME)
			if(Fx[i].value3 == index)
			{
				Fx[i].turn_off = true;
			}
		}
		if(player_hit == 1)
			VG_1_ARM_LENGTH = false;
		else
			VG_2_ARM_LENGTH = false;
	}

	if(type == VG_DOG_ATTACK) 
	{ 
		VG_status = VG_DOG_ATTACK; 
		type = -1;
		bullet_attack = true;
		no_slowmo = true;
	}
	if(type == VG_PIGEON_ATTACK)
	{ 
		VG_status = VG_PIGEON_ATTACK; 
		type = -1;
		bullet_attack = true;
		no_slowmo = true;
	}
	if(type == VG_BULLET_MID)
	{
		VG_status = VG_BULLET_MID; 
		type = -1;
		bullet_attack = true;
		no_slowmo = true;
	}
	if(type == VG_BULLET_ORB)
	{
		VG_status = VG_BULLET_ORB; 
		type = -1;
		bullet_attack = true;
		no_slowmo = true;
	}
	if(type == VG_BULLET_LOW)
	{
		VG_status = VG_BULLET_LOW;
		type = -1; 
		bullet_attack = true;
		no_slowmo = true;
	}
	if(type == VG_VIAL_MID)
	{
		VG_status = VG_VIAL_MID; 
		type = -1;
		bullet_attack = true;
		no_slowmo = true; 
		vial_attack = true;
	}
	if(type == VG_VIAL_LOW)
	{
		VG_status = VG_VIAL_LOW;
		type = -1;
		bullet_attack = true;
		no_slowmo = true;
		vial_attack = true;
	}
	if(type == VG_KNIFE)
	{
		VG_status = VG_KNIFE; 
		type = -1;
		bullet_attack = true;
	}
	if(type == VG_EXPLOSION)
	{
		VG_status = VG_EXPLOSION;
		type = -1;
		bullet_attack = true;
		no_slowmo = true;
	}
	if(type == VG_EXPLOSIONSAIZO)
	{
		VG_status = VG_EXPLOSIONSAIZO;
		type = -1;
		bullet_attack = true;
		no_slowmo = true;
	}
	if(type == VG_STICKY_BOMB) 
	{
		VG_status = VG_STICKY_BOMB;
		type = -1;
		bullet_attack = true;
	}
	if(type == VG_STICKY_GRENADE)
	{
		VG_status = VG_STICKY_GRENADE;
		type = -1;
		bullet_attack = true;
	}
	if(type == VG_STICKY_SUICIDE)
	{
		VG_status = VG_STICKY_SUICIDE;
		type = -1;
		bullet_attack = true;
	}

	// Don't slide back the atttacker...
	if(bullet_attack == true) 
	{
		sprite[index].hit_by_bullet = true; // For cornered code, stops attacker getting pushback...
		sprite[punching_guy].hit_opponent = false; // Stops attacker from being able to walk left/right
	}
	else
	{
		sprite[index].hit_by_bullet = false; // For cornered code, stops attacker getting pushback...
		sprite[punching_guy].hit_opponent = true; // Stops attacker from being able to walk left/right
	} 

	if(type == -1)
	if(VG_status == VG_KICK_AND_PUNCH_FONT) 
	{
		type = VG_KICK_AND_PUNCH_FONT; 
		VG_status = -1; 

		type = -2;

		VG_1_THROWING_SEQUENCE = 0;
		VG_2_THROWING_SEQUENCE = 0; 

		if(player_hit == 1)
		{
			VG_Reset_Player(1);
			VG_1_MOVE_ACTIVE = false;

			VG_1_Moves_count = 0;
			memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList));

			sprite[2].knockdown = false;
			sprite[2].jumping = false;

			VG_2_THROWING = true;
			VG_1_THROWING = false;
		}

		if(player_hit == 2)   
		{ 
			VG_Reset_Player(2);
			VG_2_MOVE_ACTIVE = false;

			VG_2_Moves_count = 0;
			memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList));

			sprite[3].knockdown = false; 
			sprite[3].jumping = false;

			VG_1_THROWING = true; 
			VG_2_THROWING = false;
		}

	}

	// Minso's panty shot...
	if(type != -2) // Reset
	if(bullet_attack == false)
	if(VG_OTHER_CHAR == VG_MINSO)
	if(sprite[punching_guy].status == VG_SPECIAL2_FONT)
	if(sprite[punching_guy].special == 4)
	{
		VG_status = VG_PANTY_SHOT;
	}

	// Check for blocking...
	if(type != -2) // Reset
	if(index >= 0 && index < TOTAL_NO_SPRITES)
	if(sprite[index].block_type != VG_BLOCK_NONE)   
	{ 
		if(sprite[index].block_type == VG_BLOCK_LOW) 
		if(VG_status == VG_JUMPING_KICK_FONT   
		|| VG_status == VG_JUMPING_PUNCH_FONT 
		|| VG_status == VG_PANTY_SHOT 
		|| VG_status == VG_KICK_SHORT_FONT  
		|| VG_status == VG_LOW_KICK_SHORT_FONT   
		|| VG_status == VG_VIAL_MID  
		|| VG_status == VG_KICK_CLOSE_FONT
		|| VG_status == VG_BULLET_ORB
		) 
		    block_worked = false;   
		 
		if(sprite[index].block_type == VG_BLOCK_MID) 
		if(VG_status == VG_LOW_KICK_FONT 
		|| VG_status == VG_LOW_PUNCH_FONT
		|| VG_status == VG_LOW_PUNCH2_FONT 
		|| VG_status == VG_LOW_PUNCH_SHORT_FONT
		|| VG_status == VG_BULLET_LOW
		|| VG_status == VG_BULLET_ORB
		|| VG_status == VG_DOG_ATTACK
		|| (VG_OTHER_CHAR == VG_GUN && sprite[punching_guy].special == 2 && sprite[punching_guy].status == VG_SPECIAL1_FONT)
		|| (VG_OTHER_CHAR == VG_KENNEDY && sprite[punching_guy].special == 2 && sprite[punching_guy].status == VG_SPECIAL1_FONT)
		|| VG_status == VG_VIAL_LOW
		)
		    block_worked = false;  

	} 
	else  
		block_worked = false;     

	if(sprite[index].jumping == true || sprite[index].knockdown == true || sprite[index].status == VG_KNOCKSLIDE_FONT 
	|| sprite[index].status == VG_RELOAD_FONT || sprite[index].handcuffed == true) 
		block_worked = false;
	if(VG_status == VG_STICKY_BOMB || VG_status == VG_STICKY_GRENADE || VG_status == VG_STICKY_SUICIDE)
		block_worked = false;

	// Minso's tazer...
	if(type != -2) // Reset
	if(bullet_attack == false)
	if(VG_OTHER_CHAR == VG_MINSO)
	if(sprite[punching_guy].status == VG_SPECIAL1_FONT)
	if(sprite[punching_guy].special == 1 || sprite[punching_guy].special == 2)
	{
		electrocuted = true;
		block_worked = false; 
	}
	 
	// Reese's Force Field...
	if(type != -2) // Reset
	if(bullet_attack == false)
	if(VG_OTHER_CHAR == VG_REESE)
	if(sprite[punching_guy].status == VG_SPECIAL2_FONT)
	if(sprite[punching_guy].special == 3)
	{
		VG_status = VG_FORCEFIELD;  
		electrocuted = true;
		block_worked = false;     
	}  
	 
	// Check for blocking... 
	if(type != -2) // Reset 
	if(block_worked == true)
	if(sprite[index].block_type != VG_BLOCK_NONE)
	{
		vial_attack = false;
		VG_BLOCK_REDUCE = 4; 
	} 
	 
	if(block_worked == false)
	if(sprite[index].block_type == VG_BLOCK_NONE)
	{
		sprite[index].bump_this = true; 
		sprite[index].bump_this_timer = (int)TimerGetTime() + 35; 
	}
	 
	if(type == -1) 
	{
		 
		if(VG_BLOCK_REDUCE <= 0)
			VG_BLOCK_REDUCE = 1;

		if(VG_status == VG_BULLET_ORB)   
		{
			electrocuted = true;
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_ORB_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(VG_status == VG_FORCEFIELD)   
		{
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_ELECTRIC_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(VG_status == VG_EXPLOSION)   
		{
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_GRENADE_DAMAGE/VG_BLOCK_REDUCE);

			if(VG_CURRENT_STORY_SCENE == 6 && VG_1_CHARACTER == VG_HYUK)
				VG_DAMAGE = (VG_STORY_GRENADE_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(VG_status == VG_EXPLOSIONSAIZO)   
		{
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_EXPLOSIONSAIZO_DAMAGE/VG_BLOCK_REDUCE);

			if(VG_CURRENT_STORY_SCENE == 6 && VG_1_CHARACTER == VG_HYUK)
				VG_DAMAGE = (VG_STORY_GRENADE_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(VG_status == VG_STICKY_GRENADE)   
		{
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_GRENADE_DAMAGE);
		} 
		if(VG_status == VG_STICKY_SUICIDE)   
		{
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_STICKYSUICIDE_DAMAGE);
		}
		if(VG_status == VG_STICKY_BOMB)   
		{
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_STICKYBOMB_DAMAGE); 

			if(VG_ROUND_CONDITIONS == CONDITION_THROWS_ONLY)
			if(player_hit == 2)
			{
				VG_DAMAGE = (VG_STORY_STICKYBOMB_DAMAGE);
			}
		} 
		if(VG_status == VG_VIAL_MID)   
		{
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_VIAL_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(VG_status == VG_VIAL_LOW)    
		{
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_VIAL_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(VG_status == VG_KNIFE)   
		{  
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_KNIFE_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(VG_status == VG_SPECIAL2_FONT && (VG_OTHER_CHAR == VG_JAE || VG_OTHER_CHAR == VG_GUN || VG_OTHER_CHAR == VG_KENNEDY) )   
		{
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_DANCE_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(VG_status == VG_BULLET_MID)    
		{ 
			type = VG_KNOCKDOWN_FONT;
			if (VG_OTHER_CHAR == VG_JAE || VG_OTHER_CHAR == VG_HYUK)
			{
				VG_DAMAGE = (VG_MGUN_DAMAGE / VG_BLOCK_REDUCE);
			}
			else
			{
				if(VG_OTHER_CHAR == VG_GYEONG)
					VG_DAMAGE = (VG_MAGNUM_DAMAGE/VG_BLOCK_REDUCE);
				else
				{
					if(VG_OTHER_CHAR == VG_SANG)
					    VG_DAMAGE = (VG_SANG_MGUN_DAMAGE/VG_BLOCK_REDUCE);
					else
					    VG_DAMAGE = (VG_PISTOL1_DAMAGE/VG_BLOCK_REDUCE);
				}
				if(VG_OTHER_CHAR == VG_SHO || VG_OTHER_CHAR == VG_TIA || VG_OTHER_CHAR == VG_SAIZO)
					VG_DAMAGE = (VG_FIREBALL_DAMAGE/VG_BLOCK_REDUCE);
				if(VG_OTHER_CHAR == VG_SAIZO)
					VG_DAMAGE = (VG_KUNAI_DAMAGE/VG_BLOCK_REDUCE);
			}
		} 
		if(VG_status == VG_BULLET_LOW)  
		{
			type = VG_KNOCKDOWN_FONT;
			if(VG_OTHER_CHAR == VG_JAE || VG_OTHER_CHAR == VG_HYUK)
				VG_DAMAGE = (VG_MGUN_DAMAGE/VG_BLOCK_REDUCE);
			else
			{
				if(VG_OTHER_CHAR == VG_GYEONG)
					VG_DAMAGE = (VG_MAGNUM_DAMAGE/VG_BLOCK_REDUCE);
				else
				{
					if(VG_OTHER_CHAR == VG_SANG)
					    VG_DAMAGE = (VG_SANG_MGUN_DAMAGE/VG_BLOCK_REDUCE);
					else
					    VG_DAMAGE = (VG_PISTOL1_DAMAGE/VG_BLOCK_REDUCE);
				}
			}
		} 
		if(VG_status == VG_DOG_ATTACK)  
		{
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_DOG_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(VG_status == VG_PIGEON_ATTACK)  
		{
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_DOG_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(VG_status == VG_UPPERCUT_FONT)   
		{ 
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_UPPERCUT_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(VG_status == VG_SPECIAL1_FONT)   
		{
			type = VG_KNOCKDOWN_FONT; 
			if(VG_BLOCK_REDUCE > 0)
			{
				VG_DAMAGE = (VG_SPECIAL1_DAMAGE/VG_BLOCK_REDUCE);

				if(VG_OTHER_CHAR == VG_REESE)
					VG_DAMAGE = (VG_STRECTCH_ARMS_DAMAGE/VG_BLOCK_REDUCE);
			}
		} 

		if(VG_status == VG_PUNCH_CLOSE_FONT)
		{
			type = VG_HIT_IN_BODY_FONT;
			VG_DAMAGE = (VG_PUNCH_CLOSE_DAMAGE/VG_BLOCK_REDUCE);
		}

		if(VG_status == VG_KICK_CLOSE_FONT)
		{
			type = VG_HIT_IN_BODY_FONT;
			VG_DAMAGE = (VG_KICK_CLOSE_DAMAGE/VG_BLOCK_REDUCE);
		}

		if(VG_status == VG_LOW_PUNCH_SHORT_FONT)  
		{
			type = VG_HIT_IN_BODY_FONT;
			VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(VG_status == VG_LOW_KICK_SHORT_FONT)  
		{
			type = VG_HIT_IN_BODY_FONT;
			if(VG_BLOCK_REDUCE > 0)
			VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);
		}
		if(VG_status == VG_SECOND_STRIKE)   
		{
			type = VG_HIT_IN_BODY_FONT;

			VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);

			if(VG_CURRENT_CHAR == VG_SIU || VG_CURRENT_CHAR == VG_GUN || VG_CURRENT_CHAR == VG_KENNEDY)
				VG_DAMAGE = (VG_PUNCH_CLOSE_DAMAGE/VG_BLOCK_REDUCE);

		} 
		if(VG_status == VG_THIRD_STRIKE)  
		{ 
			type = VG_KNOCKDOWN_FONT;
			if(VG_BLOCK_REDUCE > 0)
				VG_DAMAGE = (VG_UPPERCUT_DAMAGE/VG_BLOCK_REDUCE);

			if(VG_CURRENT_CHAR == VG_SIU || VG_CURRENT_CHAR == VG_GUN || VG_CURRENT_CHAR == VG_KENNEDY)
				VG_DAMAGE = (VG_PUNCH_CLOSE_DAMAGE/VG_BLOCK_REDUCE);

		}
		if(VG_status == VG_KICK_KNEE_FONT)  
		{
			type = VG_HIT_IN_BODY_FONT;
			VG_DAMAGE = (VG_KNEE_DAMAGE/VG_BLOCK_REDUCE);
		}
		if(VG_status == VG_LOW_KICK_FONT)  
		{
			type = VG_HIT_IN_BODY_FONT;
			if(VG_BLOCK_REDUCE > 0)
			VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(VG_status == VG_LOW_PUNCH_FONT)  
		{
			type = VG_HIT_IN_BODY_FONT;
			VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);  
		}
		if(VG_status == VG_LOW_PUNCH2_FONT)  
		{
			type = VG_HIT_IN_BODY_FONT;
			VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);
		}
		if(VG_status == VG_PUNCH_SHORT_FONT)
		{
			type = VG_HIT_IN_BODY_FONT; 
			VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);
		}
		if(VG_status == VG_PUNCH_MEDIUM_FONT)  
		{
			type = VG_HIT_IN_FACE_FONT;
			VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);
		}
		if(VG_status == VG_PUNCH_LONG_FONT)
		{
			type = VG_HIT_IN_BODY_FONT;
			VG_DAMAGE = (VG_KNEE_DAMAGE/VG_BLOCK_REDUCE);
		}
		if(VG_status == VG_KICK_SHORT_FONT) 
		{
			type = VG_HIT_IN_BODY_FONT; 
			VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);
		}
		if(VG_status == VG_KICK_MEDIUM_FONT)  
		{
			type = VG_HIT_IN_FACE_FONT;
			VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);
		}
		if(VG_status == VG_KICK_LONG_FONT)
		{
			if(VG_OTHER_CHAR == VG_JAE)  
			{
				type = VG_KNOCKDOWN_FONT;
				VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);
			}
			else
			{
				type = VG_HIT_IN_FACE_FONT;
				VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);
			}
		} 
		if(VG_status == VG_KICK_POWER_FONT)
		{
			type = VG_KNOCKDOWN_FONT;
			VG_DAMAGE = (VG_POWER_DAMAGE/VG_BLOCK_REDUCE);
			is_power_move = true;
		} 	
		if(VG_status == VG_PANTY_SHOT) 
		{ 
			type = VG_KNOCKDOWN_FONT; 
			VG_DAMAGE = (VG_PANTYSHOT_DAMAGE/VG_BLOCK_REDUCE);
		}
		if(VG_status == VG_JUMPING_KICK_FONT)
		{
			type = VG_HIT_IN_FACE_FONT; 
			VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);
		}
		if(VG_status == VG_JUMPING_KICK_SHORT_FONT)
		{
			type = VG_HIT_IN_FACE_FONT; 
			VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);
		}
		if(VG_status == VG_JUMPING_PUNCH_FONT)
		{
			type = VG_HIT_IN_FACE_FONT;
			VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(VG_status == VG_JUMPING_PUNCH_SHORT_FONT)
		{
			type = VG_HIT_IN_FACE_FONT;
			VG_DAMAGE = (VG_PUNCH_DAMAGE/VG_BLOCK_REDUCE);
		} 
		if(sprite[index].jumping == true)  
		{ 
		    type = VG_KNOCKDOWN_FONT;
		}

		if(VG_ROUND_CONDITIONS == CONDITION_COMBO_ONLY)
		if(player_hit == 2)
		if(VG_status != VG_SECOND_STRIKE && VG_status != VG_THIRD_STRIKE)
		{
			was_blocked = true;
			block_worked = true;
			VG_DAMAGE = 0;
		}
		else
		{
			if(VG_status == VG_SECOND_STRIKE)
				VG_DAMAGE = (VG_STORY_COMBO_DAMAGE/VG_BLOCK_REDUCE);
			if(VG_status == VG_THIRD_STRIKE)
				VG_DAMAGE = (VG_STORY_COMBOX_DAMAGE/VG_BLOCK_REDUCE);
			if(VG_OTHER_CHAR == VG_SIU)
				VG_DAMAGE = (VG_STORY_COMBO_SIU_DAMAGE/VG_BLOCK_REDUCE);
			if(VG_OTHER_CHAR == VG_GUN)
				VG_DAMAGE = (VG_STORY_COMBO_SIU_DAMAGE/VG_BLOCK_REDUCE);
			if(VG_OTHER_CHAR == VG_REESE)
				VG_DAMAGE = (VG_STORY_COMBO_REESE_DAMAGE/VG_BLOCK_REDUCE);
			if(VG_OTHER_CHAR == VG_YOHAN)
				VG_DAMAGE = (VG_STORY_COMBO_YOHAN_DAMAGE/VG_BLOCK_REDUCE);
		}

		// Minso's tazer condition...
		if(VG_ROUND_CONDITIONS == CONDITION_SPECIAL1_ONLY)
		if(player_hit == 2)
		if(VG_status != VG_SPECIAL1_FONT)
		{
			was_blocked = true;
			block_worked = true;
			VG_DAMAGE = 0;
		}
		else
		{
			VG_DAMAGE = (VG_STORY_SPECIAL1_DAMAGE/VG_BLOCK_REDUCE);

			if(VG_1_CHARACTER == VG_GUN)
			if(sprite[punching_guy].special == 3)
			{
				was_blocked = true;
				block_worked = true;
				VG_DAMAGE = 0;
			}
		}

		if(VG_ROUND_CONDITIONS == CONDITION_CLOTHESLINE_ONLY)
		if(player_hit == 2)
		if(VG_status != VG_SPECIAL2_FONT)
		{
			was_blocked = true;
			block_worked = true;
			VG_DAMAGE = 0;
		} 
		else
		{
			VG_DAMAGE = (VG_STORY_CLOTHESLINE_DAMAGE/VG_BLOCK_REDUCE);
		}

		if(VG_ROUND_CONDITIONS == CONDITION_PIGEON_ONLY)
		if(player_hit == 2)
		if(VG_status != VG_PIGEON_ATTACK)
		{
			was_blocked = true;
			block_worked = true;
			VG_DAMAGE = 0;
		}
		else
		{
			VG_DAMAGE = (VG_STORY_PIGEON_DAMAGE/VG_BLOCK_REDUCE);
		}

		if(VG_ROUND_CONDITIONS == CONDITION_MINE_ONLY)
		if(player_hit == 2)
		if(VG_status != VG_EXPLOSION && VG_status != VG_EXPLOSIONSAIZO)
		{
			was_blocked = true;
			block_worked = true;
			VG_DAMAGE = 0;
		}
		else
		{
			VG_DAMAGE = (VG_STORY_MINE_DAMAGE/VG_BLOCK_REDUCE);
		}

		if(VG_ROUND_CONDITIONS == CONDITION_SPECIAL2_ONLY)
		if(player_hit == 2) 
		{  
			if(VG_1_CHARACTER == VG_GYEONG)
			if(VG_status != VG_BULLET_LOW && VG_status != VG_BULLET_MID)
			{
				was_blocked = true;
				block_worked = true;
				VG_DAMAGE = 0;
			}
			else
				VG_DAMAGE = (VG_STORY_PISTOL_DAMAGE/VG_BLOCK_REDUCE);

			if(VG_1_CHARACTER == VG_HYUK)
			if(VG_status != VG_BULLET_LOW && VG_status != VG_BULLET_MID)
			{
				was_blocked = true;
				block_worked = true;
				VG_DAMAGE = 0;
			}
			else
				VG_DAMAGE = (VG_STORY_MGUN_DAMAGE/VG_BLOCK_REDUCE);

			if(VG_1_CHARACTER == VG_JAE)
			if(VG_status != VG_BULLET_LOW && VG_status != VG_BULLET_MID)
			{
				was_blocked = true;
				block_worked = true;
				VG_DAMAGE = 0;
			}
			else
				VG_DAMAGE = (VG_STORY_UZI_DAMAGE/VG_BLOCK_REDUCE);

			if(VG_1_CHARACTER == VG_SIU)
			if(VG_status != VG_BULLET_LOW && VG_status != VG_BULLET_MID)
			{
				was_blocked = true;
				block_worked = true;
				VG_DAMAGE = 0;
			}
			else
				VG_DAMAGE = (VG_STORY_PISTOL_SIU_DAMAGE/VG_BLOCK_REDUCE);

			if(VG_1_CHARACTER == VG_YOHAN)
			if(VG_status != VG_VIAL_LOW && VG_status != VG_VIAL_MID)
			{
				was_blocked = true;
				block_worked = true;
				VG_DAMAGE = 0;
			}
			else
				VG_DAMAGE = (VG_STORY_VIAL_DAMAGE/VG_BLOCK_REDUCE);

		}
		if(VG_ROUND_CONDITIONS == CONDITION_PISTOL_ONLY)
		if(player_hit == 2) 
		{ 
			if(VG_1_CHARACTER == VG_SIU)
			if(VG_status != VG_BULLET_LOW && VG_status != VG_BULLET_MID)
			{
				was_blocked = true;
				block_worked = true;
				VG_DAMAGE = 0; 
			}
			else
				VG_DAMAGE = (VG_STORY_PISTOL_SIU_DAMAGE/VG_BLOCK_REDUCE);
		}
		if(VG_ROUND_CONDITIONS == CONDITION_ELECTRIC_ONLY)
		if(player_hit == 2) 
		{ 
			if(VG_1_CHARACTER == VG_REESE)
			if(!(VG_status == VG_FORCEFIELD || VG_status == VG_BULLET_ORB))
			{
				was_blocked = true;
				block_worked = true;
				VG_DAMAGE = 0;
			}
			else
				VG_DAMAGE = (VG_STORY_ELECTRIC_DAMAGE/VG_BLOCK_REDUCE);
		}
		if(VG_ROUND_CONDITIONS == CONDITION_BREAKDANCE_ONLY)
		if(player_hit == 2)
		{
			if(VG_1_CHARACTER == VG_JAE)
			if(VG_status != VG_SPECIAL2_FONT)	
			{
				was_blocked = true;
				block_worked = true;
				VG_DAMAGE = 0;
			}
			else
				VG_DAMAGE = (VG_STORY_DANCE_DAMAGE/VG_BLOCK_REDUCE);
		}

		if(VG_ROUND_CONDITIONS == CONDITION_THROWS_ONLY)
		if(player_hit == 2)
		if(sprite[index].handcuffed == false && sprite[index].dizzy == false)
		{
			if(VG_status != VG_STICKY_BOMB && VG_status != VG_STICKY_SUICIDE) 
			{
				was_blocked = true;
				block_worked = true;
			    VG_DAMAGE = 0;
			}
		}

		if(VG_ROUND_CONDITIONS == CONDITION_SURVIVE)
		if(player_hit == 2)
		{
			was_blocked = true;
			block_worked = true;
			VG_DAMAGE = 0; 
		}
		   
		if(VG_ROUND_CONDITIONS == CONDITION_GRENADES_ONLY)
		if(player_hit == 2)
		if(VG_status != VG_STICKY_GRENADE && VG_status != VG_EXPLOSION && VG_status != VG_EXPLOSIONSAIZO) //  && VG_status != VG_STICKY_SUICIDE
		{
			was_blocked = true;
			block_worked = true; 
			VG_DAMAGE = 0;		 
		}

		if(block_worked == false)
		{  
			if(player_hit == 2) 
			{
				VG_1_hits_timer = (int)TimerGetTime() + COMBO_TIME;
				VG_1_hits++;
				VG_hits++;
			}
			if(player_hit == 1)
			{
				VG_2_hits_timer = (int)TimerGetTime() + COMBO_TIME;
				VG_2_hits++;
				VG_hits++;
			}
		} 

		// Stop infinite combos on handcuffed character...
	//	if(VG_DAMAGE != 0)
	/*	if((sprite[index].handcuffed == true || VG_CORNERED == true) && VG_hits >= 2) // VG_CORNERED
		{
			type = VG_KNOCKDOWN_FONT; 
		} */
		 
		if(handcuff_corner_bug == true)      
		{
		//	type = VG_BLOCKDOWN_FONT;
			type = VG_HIT_IN_FACE_FONT;

		//	was_blocked=true; 
		}

		if(VG_Display_moves == false)   
		{
			if(player_hit == 1)       
			{ 

				VG_1_HEALTH -= VG_DAMAGE; 

				if(!vial_attack && !bullet_attack)
				if(block_worked == false)
				    VG_Particles(VG_SWEAT_X, VG_SWEAT_Y, VG_ANGLE_OF_ATTACK, 1, 49);
					 
				if(vial_attack == true)
				{
					sprite[2].acid = true;
					VG_1_ACID_TIMER = (int)TimerGetTime() + 3000;
					New_FX(sprite[2].x+0.1f, sprite[2].y+0.2f, sprite[2].x+0.1f, sprite[2].y+0.2f, 1, LOOP, sprite[2].width/2,sprite[2].height/2, sprite[2].width/2,sprite[2].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_ACID, 2, 28, 0, 0, 2); // FX_VG_ATTACH

				}

				if(VG_1_HEALTH <= 0)   
				{
					VG_1_MovesList_count = 0; 
					VG_2_MovesList_count = 0; 

					VG_INVERT = true;
					VG_INVERT_TOTAL_TIMER = (int)TimerGetTime() + VG_INVERT_TOTAL_LENGTH;
					VG_INVERT_TIMER = (int)TimerGetTime() + VG_INVERT_LENGTH;

				//	VG_finished_round = true;
					VG_1_HEALTH = 0;
				//	VG_1_DEFEATED = true;

					if(VG_status == VG_STICKY_BOMB || VG_status == VG_STICKY_GRENADE)
						VG_1_DEFEATED_BY_BOMB = true;

					VG_KOED_CHARACTER = VG_1_CHARACTER;

					block_worked = false;

					VG_KO_sfx = true;

					vg_ko_smash_sfx = true;
					type = VG_KNOCKDOWN_FONT; 

				}
			}
			if(player_hit == 2)      
			{ 

				VG_2_HEALTH -= VG_DAMAGE;  

				if(!vial_attack && !bullet_attack)
				if(block_worked == false)
				    VG_Particles(VG_SWEAT_X, VG_SWEAT_Y, VG_ANGLE_OF_ATTACK, 1, 49);

				if(vial_attack == true)
				{
					sprite[3].acid = true;
					VG_2_ACID_TIMER = (int)TimerGetTime() + 3000;
					New_FX(sprite[3].x+0.1f, sprite[3].y+0.2f, sprite[3].x+0.1f, sprite[3].y+0.2f, 1, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_ACID, 3, 28, 0, 0, 3); // FX_VG_ATTACH

				}

				if(VG_2_HEALTH <= 0)
				{
					VG_1_MovesList_count = 0; 
					VG_2_MovesList_count = 0; 

					VG_INVERT = true;
					VG_INVERT_TOTAL_TIMER = (int)TimerGetTime() + VG_INVERT_TOTAL_LENGTH;
					VG_INVERT_TIMER = (int)TimerGetTime() + VG_INVERT_LENGTH;

				//	VG_finished_round = true;
					VG_2_HEALTH = 0;
				//	VG_2_DEFEATED = true;

					if(VG_status == VG_STICKY_BOMB || VG_status == VG_STICKY_GRENADE)
						VG_2_DEFEATED_BY_BOMB = true;

					VG_KOED_CHARACTER = VG_2_CHARACTER;

					block_worked = false;

					VG_KO_sfx = true;

					vg_ko_smash_sfx = true;
					type = VG_KNOCKDOWN_FONT; 

				}
			} 
		}

	/*	if(VG_finished_round == true)  
		{
			if(player_hit == 1) 
			    VG_KOED_CHARACTER = VG_1_CHARACTER;
			if(player_hit == 2) 
			    VG_KOED_CHARACTER = VG_2_CHARACTER;

			VG_KO_sfx = true;

			vg_ko_smash_sfx = true;
			type = VG_KNOCKDOWN_FONT;  
			title_sequence = 10;   
		}*/

		// Turn off jumping if the character was hit... 
		sprite[index].jumping = false; 

		if((sprite[index].w + sprite[index].box_width/2) < (sprite[punching_guy].w + sprite[punching_guy].box_width/2) )
		{
			//Set_Vibration(other_player, 10000, 6000, 250);
		    //Set_Vibration(player_hit, 12000, 24000, 250);
		} 
		else 
		{
		    //Set_Vibration(other_player, 6000, 10000, 250);
		    //Set_Vibration(player_hit, 24000, 12000, 250);
		}

	}  

	// Check for blocking...
	if(type != -2) // Reset
	if(block_worked == true)
	if(VG_finished_round == false)
	if(sprite[index].block_type != VG_BLOCK_NONE)
	{
		if(sprite[index].block_type == VG_BLOCK_LOW)
			type = VG_BLOCKDOWN_FONT;
		if(sprite[index].block_type == VG_BLOCK_MID)
			type = VG_BLOCK_FONT;

		was_blocked=true; 
	}

	if(type == VG_KNOCKDOWN_FONT)      
	{   

		if(player_hit == 1)
		{
			VG_SHAKE_1 = false;
			VG_1_DOWN_pressed = false;
		}
		else
		{
			VG_SHAKE_2 = false;
			VG_2_DOWN_pressed = false;
		}

		// Stop playing special voice sound...
		if(player_hit == 1)
		{
			if(VG_1_special1_sfx == 0)
				VG_1_special1_sfx = 1;
		}
		else 
		{
			if(VG_2_special1_sfx == 0)
			    VG_2_special1_sfx = 1;
		}

		// Length of the move...     
		if(player_hit == 1)       
		{
			memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList)); 
			VG_1_MOVE_ACTIVE = true;
		} 
		if(player_hit == 2)  
		{ 
			memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList)); 
			VG_2_MOVE_ACTIVE = true;
		} 

		sprite[index].action_timer = 0;   
		sprite[index].on_ladder = true;
		  
		sprite[index].jumping = false;
		 
		sprite[index].special = 0; 

		sprite[index].pain = true;     
		sprite[index].knockdown = true;  
		sprite[index].knockdown_Y = sprite[index].y;

        sprite[index].flash_target = true; 
        sprite[index].flash_timer = (int)TimerGetTime() + VG_FLASH_HIT_LENGTH;

		// Added these two lines 03-26-17 to try and fix stuck crouch bug...
		Set_Sprite(index, 17, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_LEFT_AND_PUNCH_FONT
		sprite[index].status = type;

		// Added to try and fix sliding reversing direction on ground...
		if(sprite[index].movement == LEFT)
			sprite[index].hit_direction = RIGHT;        
		else 
			sprite[index].hit_direction = LEFT;

		if(VG_finished_round == false)  
		{ 
			if(sprite[punching_guy].status == VG_SPECIAL1_FONT) 
			{
				VG_SlowMO(4000, 4.0f);

				sprite[index].flash_target = true; 
				sprite[index].flash_timer = (int)TimerGetTime() + VG_FLASH_HIT_LENGTH;
			}
			else
				VG_SlowMO(4000, 3.0f);
		}

		if(electrocuted == false)
		{
			if(block_worked == true)
				vg_blocked_sfx = true; 
			else
				vg_hitsound_sfx = true;  
			 
			sprite[index].electrocute = false;
		}
		else 
		{
			vg_shock_sfx = true;
			sprite[index].electrocute = true;
		}

		if(is_power_move == true)
		{
			VG_SlowMO(4000, 4.0f);
			sprite[index].flash_target = true; 
			sprite[index].flash_timer = (int)TimerGetTime() + VG_FLASH_HIT_LENGTH;

			VG_power_sfx = true;
		}
	}    

	if(type != -2)
	if(sprite[index].jumping == false) // Need to replace with body bounce...
	if(type == VG_HIT_IN_FACE_FONT || type == VG_HIT_IN_BODY_FONT || type == VG_BLOCK_FONT
	|| type == VG_BLOCKDOWN_FONT || type == VG_HIT_IN_CLOSE_FONT)     
	{
		// Stop playing special voice sound...
		if(player_hit == 1)
			VG_1_special1_sfx = 1; 
		else
			VG_2_special1_sfx = 1;

		if(type == VG_HIT_IN_FACE_FONT || type == VG_HIT_IN_BODY_FONT || type == VG_HIT_IN_CLOSE_FONT)
		if(temp_VG_DOWN_pressed==true)
		{
			if(sprite[index].handcuffed == false) 
				pain_anim = 34; // Crouch hit...
			else
				pain_anim = 62; // Crouch hit handcuffed...
		}
		else
		{
			if(sprite[index].handcuffed == false)
				pain_anim = 10; // Standing hit...
			else
				pain_anim = 63; // Standing hit handcuffed...
		}

		if(type == VG_BLOCK_FONT)pain_anim = 21;
		if(type == VG_BLOCKDOWN_FONT)pain_anim = 22;
		 
		// Length of the move...  
/*		if(player_hit == 1)
			VG_slowmo_timer = (int)TimerGetTime() + VG_Get_anim_length(2, pain_anim, true);  
		else
			VG_slowmo_timer = (int)TimerGetTime() + VG_Get_anim_length(3, pain_anim, true); */
		
		if(player_hit == 1)     
		{
			memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList)); 
			VG_1_MOVE_ACTIVE = true;
		} 
		if(player_hit == 2)  
		{ 
			memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList)); 
			VG_2_MOVE_ACTIVE = true;
		}

		if(sprite[index].movement == LEFT)
			sprite[index].hit_direction = RIGHT;        
		else 
			sprite[index].hit_direction = LEFT;

		Set_Sprite(index, pain_anim, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_LEFT_AND_PUNCH_FONT
		sprite[index].status = type;

		sprite[index].invulnerable = false; 
		sprite[index].special = 0;

		if(block_worked == false)   //  && VG_hits <= 1
			sprite[index].pain = true;

		if(no_slowmo == false)      
		if(block_worked == true)   
			VG_SlowMO(400, 4.0f); // 400, 4.0f 
		else 
			VG_SlowMO(200, 2.0f); // 200, 2.0f 

		if(block_worked == true)
			vg_blocked_sfx = true; 
		else
			vg_hitsound_sfx = true;   


		if(type != VG_BLOCK_FONT && type != VG_BLOCKDOWN_FONT)  
		{
			sprite[index].flash_target = true; 
			sprite[index].flash_timer = (int)TimerGetTime() + 35;
		}  
		 
	}

	return(was_blocked);

}

void Run_Moves(int player, int f_rate)
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
               
	if(f_rate <= 0)                                                
	    f_rate = 1;        

	if(f_rate >= 50)
		f_rate = 50; 

	if(player == 1)   
	{
		index = 2;
		VG_CURRENT_CHAR = VG_1_CHARACTER;      
		Animate(2, ANIM_SPRITE);     
	}
	if(player == 2) 
	{
		index = 3;
		VG_CURRENT_CHAR = VG_2_CHARACTER;
		Animate(3, ANIM_SPRITE);
	}

	if(VG_CURRENT_CHAR == VG_GYEONG)
		Run_Moves_GYEONG(player, f_rate);  
	if(VG_CURRENT_CHAR == VG_GUN)
		Run_Moves_GUN(player, f_rate);
	if(VG_CURRENT_CHAR == VG_JAE)
		Run_Moves_JAE(player, f_rate);
	if(VG_CURRENT_CHAR == VG_MINSO)  
		Run_Moves_MINSO(player, f_rate); 
	if(VG_CURRENT_CHAR == VG_HYUK)
		Run_Moves_HYUK(player, f_rate);
	if(VG_CURRENT_CHAR == VG_SIU)
		Run_Moves_SIU(player, f_rate); 
	if(VG_CURRENT_CHAR == VG_REESE)
		Run_Moves_REESE(player, f_rate);
	if(VG_CURRENT_CHAR == VG_YOHAN)
		Run_Moves_YOHAN(player, f_rate);
	if(VG_CURRENT_CHAR == VG_SANG)
		Run_Moves_SANG(player, f_rate);
	if(VG_CURRENT_CHAR == VG_TRAINER)
		Run_Moves_TRAINER(player, f_rate);
	if (VG_CURRENT_CHAR == VG_SHO)
		Run_Moves_SHO(player, f_rate);
	if (VG_CURRENT_CHAR == VG_TIA)
		Run_Moves_TIA(player, f_rate);
	if (VG_CURRENT_CHAR == VG_SAIZO)
		Run_Moves_SAIZO(player, f_rate);
	if(VG_CURRENT_CHAR == VG_KENNEDY)
		Run_Moves_KENNEDY(player, f_rate);


	if(player == 1)  
	{
		VG_CURRENT_CHAR = VG_1_CHARACTER;     
		Animate(2, ANIM_SPRITE);     
	}
	if(player == 2) 
	{
		VG_CURRENT_CHAR = VG_2_CHARACTER;
		Animate(3, ANIM_SPRITE);
	}
	 
} 

void VG_Play_Sound(int player, int sound)
{ 

	if(player == 1)
	{
		if(sound == VG_SOUND_CHOP)
		if(VG_1_chop_sfx == 0)
			VG_1_chop_sfx = 1;

	}
	else
	{
		if(sound == VG_SOUND_CHOP)
		if(VG_2_chop_sfx == 0)
			VG_2_chop_sfx = 1;

	}


}
 
bool VG_ShootRay(int player)
{
	bool success=false;
	float x1=0.0f;
	float y1=0.0f; 
	float x2=0.0f; 
	float y2=0.0f;
	float other_x1=0.0f;
	float other_y1=0.0f; 
	float other_x2=0.0f; 
	float other_y2=0.0f;
    float x=0.0f, y=0.0f;
    float x_line=0.0f, y_line=0.0f;
    float angle=0.0f, deltax=0.0f, deltay=0.0f;
    float other_angle=0.0f, other_deltax=0.0f, other_deltay=0.0f;
    float step=0, distance=0.0f, distance_line=0.0f;
    int iterations=0, iterations_line=0;
    int temp_row=0; 
    int temp_r_x=0;  
    int temp_r_y=0; 
	int other_index=0;
	bool other_active = false;
	bool break_loop = false;
	float attackers_angle=0.0f;

	if(player == 1)
	{
		x1 = points[2].x; 
		y1 = points[2].y;
		x2 = points[0].x;
		y2 = points[0].y; 

		other_x1 = points[3].x;  
		other_y1 = points[3].y;
		other_x2 = points[1].x;   
		other_y2 = points[1].y;

		attackers_angle = atan2(y2 - y1,x2 - x1); 

		VG_ANGLE_OF_ATTACK = attackers_angle;

		if(points[1].active != 0) 
			other_active = true;

		other_index = 3;  
	}

	if(player == 2)
	{
		x1 = points[3].x;
		y1 = points[3].y; 
		x2 = points[1].x;  
		y2 = points[1].y;

		other_x1 = points[2].x;
		other_y1 = points[2].y;
		other_x2 = points[0].x; 
		other_y2 = points[0].y;

		attackers_angle = atan2(y2 - y1,x2 - x1); 

		VG_ANGLE_OF_ATTACK = attackers_angle;

		if(points[0].active != 0)
			other_active = true;

		other_index = 2;
	}
 
    x = x1;  
    y = y1;    
    
    distance = Node_Distance1(x1, y1, x2, y2);   
   
    angle = atan2(y2 - y1,x2 - x1);     
    
    deltax = cos(angle); // *1.2f   
    deltay = sin(angle); // *1.2f
        
    deltax *= (float)LINE_OF_SIGHT;          
    deltay *= (float)LINE_OF_SIGHT;
        
    step = Node_Distance1(x1, y1, x1+deltax, y1+deltay);
    
    if(step > 0.0f)
        iterations = (int)(distance / step);   

    if(iterations < 0)    
        iterations = 0;  
    
	x -= deltax; // Start at exact player/sprite co-ordinates...
	y -= deltay; // Start at exact player/sprite co-ordinates...

    for (int i = 0; i <= iterations; i++)      
    {  
	        
	   // Test against opponents collision box...
       x += deltax; // Which is the mid_x
       y += deltay; // Which is the mid_y
         
	   if(other_index >= 0)
	   if(( x < (sprite[other_index].w + sprite[other_index].box_width) )
	   &&( x > sprite[other_index].w)                             
	   &&( y < (sprite[other_index].z + sprite[other_index].box_height) )
	   &&( y > sprite[other_index].z) )
	   {
		   VG_HIT_X = x;
		   VG_HIT_Y = y;

		   VG_SWEAT_X = x;
		   VG_SWEAT_Y = y;

		//   VG_Particles(x, y, attackers_angle, 1, 49);

	       success = true;
		   break;
	   }

	   // Test against line...
	   if(other_active == true)
	   {
		    
		x_line = other_x1;  
		y_line = other_y1;    
    
		distance = Node_Distance1(other_x1, other_y1, other_x2, other_y2);   
   
		angle = atan2(other_y2 - other_y1,other_x2 - other_x1);     
    
		other_deltax = cos(angle); // *1.2f   
		other_deltay = sin(angle); // *1.2f
        
		other_deltax *= 0.01f;           
		other_deltay *= 0.01f;     
        
		step = Node_Distance1(other_x1, other_y1, other_x1+deltax, other_y1+deltay);
    
		if(step > 0.0f)
			iterations_line = (int)(distance / step);   

		if(iterations_line < 0)      
			iterations_line = 0;   

		x_line -= other_deltax; // Start at exact player/sprite co-ordinates...
		y_line -= other_deltay; // Start at exact player/sprite co-ordinates...

		for (int j = 0; j <= iterations_line; j++)        
		{  
        
		   x_line += other_deltax; // Which is the mid_x
		   y_line += other_deltay; // Which is the mid_y

		   distance = Node_Distance1(x, y, x_line, y_line);   
		    
		   if(distance <= 0.020f)    
		   { 
			   VG_HIT_X = x; 
			   VG_HIT_Y = y;
			   success = true;

			   break_loop = true;
		   } 

		   if(break_loop == true)
		       break;

		}  

	   } // other_active == true

	   if(break_loop == true)
			break;

	} //  for (int i = 0; i <= iterations; i++)      

	return(success);

}
