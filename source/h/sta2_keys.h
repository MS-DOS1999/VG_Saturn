#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64 
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#endif 

bool sta2_Keys();


bool sta2_Keys()
{ 
	bool success=true;
	int pack_id = -1;

	if(ply_id == -1)
		return(false);

	if(sprite[ply_id].value2 >= 0)
		pack_id = sta2_squad[sprite[ply_id].value2].wp;

	if(sta2_turn != TURN_COMPUTER) 
	if(sta2_displaying_help == false) 
	if(ply_id != -1)
	if(sprite[ply_id].score > 1) 
    if(sta2_1_pressed == true)  
	if(sta2_turn == TURN_PLAYER)  
	if(!mode && game_mode == WALK)  
	if((sta2_shots_pistol < 3 && sta2_pack[pack_id].type == STA2_SCOUT) 
	|| (sta2_shots_shotgun < STA2_SHOTGUN_LIMIT && sta2_pack[pack_id].type == STA2_HEAVY)
	|| (sta2_shots_pistol < 3 && sta2_pack[pack_id].type == STA2_SNIPER)
	|| (sta2_shots_pistol < 3 && sta2_pack[pack_id].type == STA2_MORTAR)
	) 
	if(sta2_shot_fired_gun == FIRED_NONE || sta2_shot_fired_gun == FIRED_PISTOL || sta2_shot_fired_gun == FIRED_SHOTGUN)
	if(ply_dead == false)  
	if(sta2_used_extra == false) 
	if(sta2_special_missed == false)   
	if(lock_player == false)    
	if(quit_active == false)        
	{  
				  
		sta2_1_pressed = false;   

		if(ply_id != -1)
		{
			has_grenade_equipped = false;
			has_pistol_equipped  = false;  
			has_rifle_equipped   = false;
			has_shotgun_equipped = false;
			has_machine_equipped = false;
			has_sniper_equipped = false;
			has_mortar_equipped = false;

			if(sta2_pack[pack_id].type == STA2_SCOUT)
				has_pistol_equipped = true;
			if(sta2_pack[pack_id].type == STA2_HEAVY)
				has_shotgun_equipped = true;
			if(sta2_pack[pack_id].type == STA2_SNIPER)
				has_pistol_equipped = true;
			if(sta2_pack[pack_id].type == STA2_MORTAR)
				has_pistol_equipped = true; 

			spark_sfx = true;

			ply_accel = 0.0f; 

			sprite[ply_id].moving  = false; 
			sprite[ply_id].turning = false; 

			ShotIdle(ply_id);  

			sprite[ply_id].status = AIMING; 
			sprite[ply_id].anim_state = WAIT; 
			Rank_Timer(ply_id, AIMING);

			sta2_current_extra = PACK_EXTRA_NONE;

			STA2_MODE = MODE_AIMING; 
		}
              
	}	

	if(sta2_turn != TURN_COMPUTER)  
	if(sta2_displaying_help == false) 
	if(ply_id != -1)
	if(sprite[ply_id].score > 1)
	if(sta2_2_pressed == true) 
	if(sta2_turn == TURN_PLAYER)
	if(!mode && game_mode == WALK)  
	if((sta2_shots_rifle < 1 && sta2_pack[pack_id].type == STA2_SCOUT) 
	|| (sta2_shots_machine < STA2_MACHINE_LIMIT && sta2_pack[pack_id].type == STA2_HEAVY)
	|| (sta2_shots_mortar < STA2_MORTAR_LIMIT && sta2_pack[pack_id].type == STA2_MORTAR)	
	|| (sta2_shots_sniper < STA2_SNIPER_LIMIT && sta2_pack[pack_id].type == STA2_SNIPER)	
	) 
	if(sta2_shot_fired_gun == FIRED_NONE || sta2_shot_fired_gun == FIRED_RIFLE || sta2_shot_fired_gun == FIRED_MACHINE || sta2_shot_fired_gun == FIRED_SNIPER || sta2_shot_fired_gun == FIRED_MORTAR)
	if(ply_dead == false) 
	if(sta2_used_extra == false) 
	if(sta2_special_missed == false)
	if(lock_player == false)
	if(quit_active == false)      
	{  
				  
		sta2_2_pressed = false;   

		if(ply_id != -1)
		{
			has_grenade_equipped = false;
			has_pistol_equipped  = false;
			has_shotgun_equipped = false;
			has_machine_equipped = false;  
			has_rifle_equipped   = false; 
			has_sniper_equipped = false;
			has_mortar_equipped = false;

			if(sta2_pack[pack_id].type == STA2_SCOUT)
				has_rifle_equipped = true;
			if(sta2_pack[pack_id].type == STA2_HEAVY)
				has_machine_equipped = true;
			if(sta2_pack[pack_id].type == STA2_SNIPER)
				has_sniper_equipped = true;
			if(sta2_pack[pack_id].type == STA2_MORTAR)
				has_mortar_equipped = true;

			spark_sfx = true;

			ply_accel = 0.0f;

			sprite[ply_id].moving  = false; 
			sprite[ply_id].turning = false;  

			ShotIdle(ply_id); 

			sprite[ply_id].status = AIMING; 
			sprite[ply_id].anim_state = WAIT; 
			Rank_Timer(ply_id, AIMING);

			sta2_current_extra = PACK_EXTRA_NONE;

			STA2_MODE = MODE_AIMING;


		}              
	}  

	if(sta2_turn != TURN_COMPUTER)
	if(sta2_displaying_help == false)
	if(ply_id != -1)	 
	if(sprite[ply_id].score > 1)
	if(sprite[ply_id].sector != UNIT_SNIPER && sprite[ply_id].sector != UNIT_MORTAR)
	if(sta2_3_pressed == true)  	 	  
	if(ply_id != -1)
	if(sta2_shot_fired_gun == FIRED_NONE)  
	if(sta2_used_extra == false)
	if(sta2_special_missed == false)  
	{  
		 
		has_grenade_equipped = false;
		has_pistol_equipped  = false;
		has_rifle_equipped   = false; 
		has_shotgun_equipped = false;
		has_machine_equipped = false;
		has_sniper_equipped = false;
		has_mortar_equipped = false;

		sta2_3_pressed = false;

		cash_up_sfx = true;

		sprite[ply_id].return_fire = true;

		sprite[ply_id].moving  = false; 
		sprite[ply_id].turning = false; 

		ShotIdle(ply_id);  
			 
		sprite[ply_id].status = CROUCHING; 
		sprite[ply_id].update = true;
		sprite[ply_id].anim_state = WAIT;

		sta2_current_extra = PACK_EXTRA_NONE;

		STA2_MODE = MODE_MOVING;
	}

	if(sta2_turn != TURN_COMPUTER)
	if(sta2_displaying_help == false)
	if(ply_id != -1)
	if(sprite[ply_id].score > 1)
	if(sta2_4_pressed == true) 
	if(ply_id != -1)
	if(sta2_turn == TURN_PLAYER)
	if(!mode && game_mode == WALK)
	if(sta2_used_extra == false)
	if(sta2_special_missed == false) 
	if(sta2_shot_fired_gun == FIRED_NONE)
	{  
		sta2_4_pressed = false;

		if(sprite[ply_id].value2 >= 0)
			pack_id = sta2_squad[sprite[ply_id].value2].wp;

		if(pack_id > -1)
		if(sta2_pack[pack_id].extra_charge > 0) 
		if(sta2_pack[pack_id].extra == PACK_EXTRA_MEDKIT)  
		{

			sta2_current_extra = PACK_EXTRA_MEDKIT;

			ply_accel = 0.0f; 

			sprite[ply_id].moving  = false; 
			sprite[ply_id].turning = false; 

			ShotIdle(ply_id); 

			sprite[ply_id].status = STA2_HEALING;
			sprite[ply_id].anim_state = WAIT;
			sprite[ply_id].update = true;

			STA2_MODE = MODE_TARGET;

		}

		if(pack_id > -1)
		if(sta2_pack[pack_id].extra_charge > 0) 
		if(sta2_pack[pack_id].extra == PACK_EXTRA_GRENADE)  
		{
			has_grenade_equipped = true;
			has_pistol_equipped  = false;
			has_shotgun_equipped = false;  
			has_machine_equipped = false; 
			has_rifle_equipped   = false;  
			has_sniper_equipped = false;
			has_mortar_equipped = false;

			spark_sfx = true;
			sta2_current_extra = PACK_EXTRA_GRENADE; 

			ply_accel = 0.0f; 

			sprite[ply_id].moving  = false; 
			sprite[ply_id].turning = false; 

			ShotIdle(ply_id); 

			sprite[ply_id].status = AIMING;  
			sprite[ply_id].anim_state = WAIT; 
			Rank_Timer(ply_id, AIMING);

			STA2_MODE = MODE_AIMING;

		}

	}

	if(sta2_turn != TURN_COMPUTER)
	if(sta2_displaying_help == false)
	if(ply_id != -1)
	if(sprite[ply_id].score > 1) 
	if(sta2_5_pressed == true)
	if(ply_id != -1)
	if(sta2_turn == TURN_PLAYER)
	if(!mode && game_mode == WALK) 
	if(STA2_MODE == MODE_MOVING) 
	if(sta2_used_extra == false)
	if(sta2_used_special == false) 
	if(sta2_shot_fired_gun == FIRED_NONE) 
	{ 
		sta2_5_pressed = false; 

		if(sprite[ply_id].value2 >= 0)
			pack_id = sta2_squad[sprite[ply_id].value2].wp;

		if(pack_id > -1) 
		if(sta2_pack[pack_id].special != PACK_SPECIAL_NONE) 
		{

			sta2_only_defend = false;
			sta2_only_pistol = false;
			sta2_only_grenade = false;

			sta2_used_special = true;       

			ply_accel = 0.0f;           

			sprite[ply_id].moving  = false;         
			sprite[ply_id].turning = false;      
			 
			ShotIdle(ply_id);      

			if(sta2_pack[pack_id].special == PACK_SPECIAL_GODEYE)
			if(rand()%3 == 0)  
			{
				DamageNumber( ply_id, -1, STA2_DAMAGE_MISS );  
				sta2_special_missed = true;
			}
			else  
			{
				sta2_pack[pack_id].special_charge++; // Sets effect to be active...

				if(sta2_pack[pack_id].special == PACK_SPECIAL_GODEYE)
			    DamageNumber( ply_id, -1, STA2_DAMAGE_EYE );

				healup_sfx = true;  
			}   
			 
			if(sta2_pack[pack_id].special == PACK_SPECIAL_MAGICNET)
			if(rand()%4 == 0) 
			{
				DamageNumber( ply_id, -1, STA2_DAMAGE_MISS );  
				sta2_special_missed = true;
			}
			else  
			{
				sta2_pack[pack_id].special_charge++; // Sets effect to be active...

				if(sta2_pack[pack_id].special == PACK_SPECIAL_MAGICNET)
			    DamageNumber( ply_id, -1, STA2_DAMAGE_NET );

				healup_sfx = true; 
			} 
			 
			// Do fx_score_slow acc+ or miss...    
			if(sta2_pack[pack_id].special != PACK_SPECIAL_GODEYE && sta2_pack[pack_id].special != PACK_SPECIAL_MAGICNET)
			if(rand()%5 == 0) 
			{
				DamageNumber( ply_id, -1, STA2_DAMAGE_MISS );  
				sta2_special_missed = true;
			}
			else  
			{  
				sta2_pack[pack_id].special_charge++; // Sets effect to be active...

				if(sta2_pack[pack_id].special == PACK_SPECIAL_SCOPE)
					DamageNumber( ply_id, -1, STA2_DAMAGE_ACC );  

				if(sta2_pack[pack_id].special == PACK_SPECIAL_SHIELD)
					DamageNumber( ply_id, -1, STA2_DAMAGE_SHD ); 

				if(sta2_pack[pack_id].special == PACK_SPECIAL_DUMDUM)
					DamageNumber( ply_id, -1, STA2_DAMAGE_DUM ); 

				if(sta2_pack[pack_id].special == PACK_SPECIAL_BOOTS) 
					DamageNumber( ply_id, -1, STA2_DAMAGE_BOOT ); 

				if(sta2_pack[pack_id].special == PACK_SPECIAL_VAMPIRE)
					DamageNumber( ply_id, -1, STA2_DAMAGE_VAMP ); 

				if(sta2_pack[pack_id].special == PACK_SPECIAL_MAGICHERB)
					DamageNumber( ply_id, -1, STA2_DAMAGE_HERB ); 

				if(sta2_pack[pack_id].special == PACK_SPECIAL_XPGAIN)
					DamageNumber( ply_id, -1, STA2_DAMAGE_EXP ); 

				if(sta2_pack[pack_id].special == PACK_SPECIAL_DEATHBLOW)
					DamageNumber( ply_id, -1, STA2_DAMAGE_BLOW ); 

				if(sta2_pack[pack_id].special == PACK_SPECIAL_LASTCHANCE)
					DamageNumber( ply_id, -1, STA2_DAMAGE_LAST ); 

				healup_sfx = true;  
			} 
			 
		} 
		 
	} 

	if(sta2_turn != TURN_COMPUTER)
	if(sta2_displaying_help == false) 
	if(ply_id != -1)	   
	if(sta2_machinegun_index == -1)
	if(sta2_6_pressed == true || sta2_tab_pressed == true) 
	if(sta2_turn == TURN_PLAYER)    
	if(!mode && game_mode == WALK)  
	if(ply_id != -1)
	if(sta2_battle_outcome == BATTLE_NONE) 
	if(STA2_MODE != MODE_AIMING && STA2_MODE != MODE_TARGET)
	{ 
		sta2_6_pressed = false;

		sta2_tab_pressed = false; 
		 
		sta2_menu = false;

		sta2_pressed_map = true;

		scene = 1;
		episode = 1;

		next_scene = true;

	/*	has_machine_equipped = false;
		has_shotgun_equipped = false;
		has_rifle_equipped = false;
		has_pistol_equipped = false; 
		has_sniper_equipped = false;
		has_mortar_equipped = false;

		ply_accel = 0.0f;

		sprite[ply_id].return_fire = false; // Defending...

		sprite[ply_id].moving  = false; 
		sprite[ply_id].turning = false; 

		ShotIdle(ply_id); 
			 
		STA2_MODE = MODE_MOVING;

		sta2_current_extra = PACK_EXTRA_NONE; */
		 
	}
	 
	if(sta2_turn != TURN_COMPUTER)
	if(sta2_displaying_help == false)
	if(ply_id != -1) 
	if(sta2_machinegun_index == -1)
	if(sta2_7_pressed == true)
	if(sta2_turn == TURN_PLAYER)     
	if(!mode && game_mode == WALK)  
	if(ply_id != -1) 
	{ 
		sta2_7_pressed = false;   

		sta2_menu = false;

		has_machine_equipped = false;
		has_shotgun_equipped = false;
		has_rifle_equipped = false;
		has_pistol_equipped = false;
		has_sniper_equipped = false;
		has_mortar_equipped = false; 

		stats_scene   = scene;
		stats_episode = episode;   

		if(sta2_battle_outcome == BATTLE_NONE) 
		{
			episode = 1; 
			scene   = 1;    
		} 
                         
		if(sta2_battle_outcome == BATTLE_DEFEAT || sta2_battle_outcome == BATTLE_VICTORY)
		{

			sta2_battle_load_outcome = sta2_battle_outcome;

			episode = 1;  
			scene   = 2; 

			if(sta2_battle_outcome == BATTLE_DEFEAT)
				sta2_next_event = EVENT_DEFEAT;

			if(sta2_battle_outcome == BATTLE_VICTORY)
				sta2_next_event = EVENT_VICTORY;

			sta2_battle_outcome = BATTLE_NONE;

		}

		next_scene = true;  

	}

	if(sta2_turn != TURN_COMPUTER)
	if(sta2_displaying_help == false) 
	if(ply_id != -1)	   
	if(sta2_machinegun_index == -1)
	if(sta2_space_pressed == true)
	if(sta2_turn == TURN_PLAYER)    
	if(!mode && game_mode == WALK) 
	if(ply_id != -1)
	if(STA2_MODE == MODE_AIMING || STA2_MODE == MODE_TARGET || sprite[ply_id].return_fire == true)
	{
		sta2_space_pressed = false;

		sta2_menu = false;

		has_machine_equipped = false;
		has_shotgun_equipped = false;
		has_rifle_equipped = false;
		has_pistol_equipped = false; 
		has_sniper_equipped = false;
		has_mortar_equipped = false;

		ply_accel = 0.0f;

		sprite[ply_id].return_fire = false; // Defending...

		sprite[ply_id].moving  = false; 
		sprite[ply_id].turning = false; 

		ShotIdle(ply_id); 
			 
		STA2_MODE = MODE_MOVING;

		sta2_current_extra = PACK_EXTRA_NONE; 
		 
	}


	return(success);

} 
 