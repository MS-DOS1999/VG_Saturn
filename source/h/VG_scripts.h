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
extern void Run_Verdict_AI(int f_rate); 
extern bool VG_ShootRay(int player);
extern void VG_Text(int character, int other_character, int final_text); 
extern void VG_Moveslist(int counter, int character, int index, int player);
extern void VG_set_intro_dogs();
extern void VG_dust_effect(int character, int shadow, int direction);
extern void VG_reset_input();
extern void VG_CheckForSpecials(int player);
extern void Run_Throws(int player, int f_rate);
extern void VG_Do_Shake(int length, float strength);
extern void VG_Upload_Score(int type);
extern void VG_Reset_Player(int player);
extern void VG_SlowMO(int duration, float strength);
extern void VG_Restrain_sprite(int index, int j);
extern void VG_SetMove(int player, int move);
extern int New_Sprite(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int sideways, int upways, int state, int linked_sprite, int tex_id, int a_global, float angle, int p_type, int goto_point);
extern void VG_Resize_Sprite(int index);
extern void VG_Particles(float x, float y, float angle, int priority, int anim);

#ifdef BREAKER_CHARACTER_BUILD
bool VG_ACTIVATE_BREAKERS = true;
#else
bool VG_ACTIVATE_BREAKERS = false;
#endif

int VG_BATTLE_TIMER = 0; 
float VG_distance_between_players = 0.0f;

float VG_start_stamp_Y=0.0;   
float VG_start_stamp_X=0.0;

int VG_intro_sequence = 0;
int VG_intro_timer = 0;
int VG_dog_timer = 0;
int VG_voice_delay=-1;
int nogo_timer = 0; 
int VG_DOG = 0; 

#define SCALE_FACE_AMOUNTX 1.0f
#define SCALE_FACE_AMOUNTY 0.66f

float stored_width;
float stored_height;

float stored_scale_Y;

float billboard_offsetX = 0.0f;

int story_help_timer = 0;

bool VG_displayed_story_help = false;

bool VG_HEALTH_LOADING = false;

bool vg_arrest_successful = false;
bool vg_waste_successful = false;

int  vg_lowtime_timer = 0;
bool vg_lowtime_flash = false;

int vg_van_trail_timer = 0;

int vg_switch_p2_text = 0;
bool vg_switch_is_p2 = false;

float vg_scalex = 0.0f, vg_scaley = 0.0f;

float VG_Get_Speed()
{
	int rnd_speed=0;
	float the_speed=0.0f;

	rnd_speed = rand()%6;
	if(rnd_speed == 0)
		the_speed = 0.00055f;
	if(rnd_speed == 1)
		the_speed = 0.00060f;
	if(rnd_speed == 2)
		the_speed = 0.00064f;
	if(rnd_speed == 3)
		the_speed = 0.00070f;
	if(rnd_speed == 4)
		the_speed = 0.00074f;
	if(rnd_speed == 5)
		the_speed = 0.00080f;

	return(the_speed);
}

void Run_Verdict(int f_rate)
{

	float testX=0.0f, testY=0.0f;
	float testX1=0.0f, testY1=0.0f;
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
	char string_value[1024]; 
	int tmp_VG_Moves_count=0;
	int tmp_VG_Moves[MOVES_LIMIT]; 
	int display_player = 0;
	bool VG_MOVE_ACTIVE = false; 
	int special_rnd=0;   
	int VG_bullet_type=0;     
	int k = 0;     
	bool skip_this = false;
    int next_list[15];
	int next_list_count=0;
	int VG_CURRENT_CHAR = 0;
	int VG_OTHER_CHAR = 0;
	int VG_WINNING_CHAR=0;
	bool VG_OTHER_CORNERED = false;
	int VG_HEALTH = 0;
	int count_rate=0; 
	int rnd=0; 
	float frnd=0;
	bool VG_skip_scene=false;
	float angle = 0.0f;
	float deltax=0.0f, deltay=0.0f; 
	float pushing_X = 0.0f;
	float diffX=0.0f;
	bool VG_BLOCKING = false;
	int VG_WAS_HIT_TIMES = 0;
	bool VG_THROWING = false;
	bool VG_HANDCUFFED = false;
	int vg_attack_type=0;
	bool vg_skip_this = false;
	char vg_temp_1_wins[5];
	char vg_temp_2_wins[5];
	char vg_temp_draws[5];
	int VG_USING = 0;
	float VG_XAXIS=0.0f;
	bool jump_sideways = false;
	bool was_knockslide = false;
	bool char_not_available = false;
	int temp_scroll_amount = 0;
	int floor_anim=0;
	bool VG_HAS_ALTER_CHAR_SELECT = false;
	float temp_VG_shake_strength=0.0f; 
	int temp_bottomrow_index;
	int bump_index=0;
	float tBomb_range = 0.0f;

	if(f_rate <= 0)                                                
	    f_rate = 1;        

	if(f_rate >= 50)
		f_rate = 50; 
	
	if(mode)    
		hud[1].alpha = 1.0f;  
	else 
		hud[1].alpha = 0.0f;

	// hud[10] ... Round
	// hud[14] ... Perfect

//	if(episode == 0 && scene != 1 && scene != 0)
//		hud[1].alpha = 1.0f;

    for(int i=0;i<new_no_sprites;i++) 
    {
		k = var5[i]; 
                
        // Disables white flash...                      
		if( k >= 0 && k < TOTAL_NO_SPRITES) 
        if(sprite[k].flash_target == true 
        && (int)TimerGetTime() > sprite[k].flash_timer)   
        {      
            sprite[k].flash_target = false;
            sprite[k].flash_timer  = 0;
        }    

	}
    for(int k=0;k<hud_no_sprites;k++)  
    {                
        // Disables white flash...  
		if( k >= 0 && k < TOTAL_NO_HUD) 
        if(hud[k].flash_target == true 
        && (int)TimerGetTime() > hud[k].flash_timer)    
        {      
            hud[k].flash_target = false;   
            hud[k].flash_timer  = 0; 
        }    
		if( k >= 0 && k < TOTAL_NO_HUD)     
        if(hud[k].type == FE_SCROLL )      
        {      
      
			temp_speed = hud[k].rank / 40000.0f;    

            hud[k].u[0] += (temp_speed*(float)f_rate); 
            hud[k].u[1] += (temp_speed*(float)f_rate);
            hud[k].u[3] += (temp_speed*(float)f_rate);
            hud[k].u[2] += (temp_speed*(float)f_rate);
            
        } 
	}

	
    // ******************************************************************************//
    //                                 5-0  (IN-GAME)                                //
    // ******************************************************************************//
				                 
       // Title Screen Stuff... 
       if(!mode)  
       if(next_scene == false)   
       if(episode == 5)     
       {         
			   
			// Pressed back key... 
			if(VG_HUD_ESC == true)   
			{
				VG_HUD_ESC = false;  
				vg_next_episode = 0; 
				vg_next_scene  = 1;

				next_scene = true;   
			}

			// Swipe transition... 
			if(hud[20].x > hud[20].w)
			{
				hud[20].alpha = 0.0f;
			}
			else
			{
				temp_speed = ((0.0025f/VG_slowmof)*(float)f_rate);

				hud[20].alpha = 1.0f;
				hud[20].x += temp_speed;
			}

		   if(VG_SURVIVAL == true)
		   if(VG_flash_survive_timer != 0)
		   if((int)TimerGetTime() > VG_flash_survive_local_timer)
		   {
			   VG_flash_survive_local_timer = (int)TimerGetTime() + 75;

			   VG_flash_survive ^= 1;

			   if(VG_flash_survive == true)
				   new_counter[3].alpha = 0.0f;
			   else
				   new_counter[3].alpha = 1.0f;

			   if((int)TimerGetTime() > VG_flash_survive_timer)
			   {
				   VG_flash_survive_timer = 0;
				   VG_flash_survive_local_timer = 0;
				   new_counter[3].alpha = 1.0f;
			   }

		   }
 
		   hud[0].alpha = 1.0f;
		   hud[1].alpha = 0.0f; // Mouse cursor...
		   hud[2].alpha = 1.0f;      
		   hud[3].alpha = 1.0f;  
		   hud[4].alpha = 1.0f;  
		   hud[6].alpha = 1.0f;    
		   hud[7].alpha = 1.0f; 
		   hud[8].alpha = 1.0f; // Bullets left  
		   hud[9].alpha = 1.0f; // Bullets right

		   hud[19].alpha = 1.0f; // Healthbar backing 
		
		   // Handcuffs...
		   if(VG_1_HAS_THROW == true)
		   {
   			   if(VG_1_CHARACTER == VG_GYEONG || VG_1_CHARACTER == VG_SIU || VG_1_CHARACTER == VG_MINSO || VG_1_CHARACTER == VG_REESE || VG_1_CHARACTER == VG_SANG || VG_1_CHARACTER == VG_TRAINER || VG_1_CHARACTER == VG_SHO || VG_1_CHARACTER == VG_TIA || VG_1_CHARACTER == VG_SAIZO)
				   Set_Sprite(17, 14, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets left...
			   else
				   Set_Sprite(17, 15, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets left...

			   hud[17].alpha = 1.0f; 
		   }
		   else  
			   hud[17].alpha = 0.0f;

		   if(VG_2_HAS_THROW == true)
		   {
   			   if(VG_2_CHARACTER == VG_GYEONG || VG_2_CHARACTER == VG_SIU || VG_2_CHARACTER == VG_MINSO || VG_2_CHARACTER == VG_REESE || VG_2_CHARACTER == VG_SANG || VG_2_CHARACTER == VG_TRAINER || VG_2_CHARACTER == VG_SHO || VG_2_CHARACTER == VG_TIA || VG_2_CHARACTER == VG_SAIZO)
				   Set_Sprite(18, 14, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets left...
			   else
				   Set_Sprite(18, 15, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets left...

			   hud[18].alpha = 1.0f;
		   }
		   else
			   hud[18].alpha = 0.0f;


		   // Make bullets on hud, show fireballs instead...
		   if (VG_1_CHARACTER == VG_SHO || VG_1_CHARACTER == VG_TIA || VG_1_CHARACTER == VG_SAIZO)
			   hud[8].id = 36;

		   if (VG_1_CHARACTER == VG_MINSO || VG_1_CHARACTER == VG_REESE)
			   hud[8].id = 37;

		   if(VG_1_BULLETS == 4) 
			   Set_Sprite(8, 0, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets left...
		   if(VG_1_BULLETS == 3) 
			   Set_Sprite(8, 1, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets left...
		   if(VG_1_BULLETS == 2) 
			   Set_Sprite(8, 2, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets left...
		   if(VG_1_BULLETS == 1) 
			   Set_Sprite(8, 3, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets left...
		   if(VG_1_BULLETS == 0)
			   Set_Sprite(8, 10, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets left...

		   if (VG_2_CHARACTER == VG_SHO || VG_2_CHARACTER == VG_TIA || VG_2_CHARACTER == VG_SAIZO)
			   hud[9].id = 36;
		   if (VG_2_CHARACTER == VG_MINSO || VG_2_CHARACTER == VG_REESE)
			   hud[9].id = 37;

		   if(VG_2_BULLETS == 4)
			   Set_Sprite(9, 5, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets right...
		   if(VG_2_BULLETS == 3)
			   Set_Sprite(9, 6, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets right...
		   if(VG_2_BULLETS == 2)
			   Set_Sprite(9, 7, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets right...
		   if(VG_2_BULLETS == 1)
			   Set_Sprite(9, 8, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets right...
		   if(VG_2_BULLETS == 0)
			   Set_Sprite(9, 11, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets right...

		   // Turn off reload if round end...
		   if(VG_finished_round == true) 
		   {  
			   if(VG_1_BULLETS == 0 && VG_1_CHARACTER != VG_GUN && VG_1_CHARACTER != VG_KENNEDY)
				   Set_Sprite(8, 4, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets left...
			   if(VG_2_BULLETS == 0 && VG_2_CHARACTER != VG_GUN && VG_2_CHARACTER != VG_KENNEDY)
				   Set_Sprite(9, 9, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets right...
		   }
		    
		   if(VG_1_CHARACTER == VG_GUN) 
			   Set_Sprite(8, 4, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets left...
		   if(VG_2_CHARACTER == VG_GUN)
			   Set_Sprite(9, 9, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets left...

		   if(VG_1_CHARACTER == VG_KENNEDY) 
			   Set_Sprite(8, 4, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets left...
		   if(VG_2_CHARACTER == VG_KENNEDY)
			   Set_Sprite(9, 9, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Bullets left...

		   if(VG_GAME_MODE == VG_STORY_MODE)  
		   if(VG_CURRENT_STORY_SCENE >= 0 && VG_CURRENT_STORY_SCENE < 20)
		   {  
			      
			   VG_has_no_explosive = false;  
			    
			   if(VG_1_CHARACTER == VG_HYUK && VG_CURRENT_STORY_SCENE < 6)
				   VG_has_no_explosive = true; 

			   if(VG_1_equipment[VG_CURRENT_STORY_SCENE] == EQUIPMENT_BASIC)
			   {
				   hud[8].alpha = 0.0f; // Bullets left  
				   hud[17].alpha = 0.0f; // Handcuffs left 
			   }
			   if(VG_2_equipment[VG_CURRENT_STORY_SCENE] == EQUIPMENT_BASIC)
			   {

				   hud[9].alpha = 0.0f; // Bullets right 
				   hud[18].alpha = 0.0f; // Handcuffs right 
			   }
		   }

		   // Blow leaves/trash...
		   if((int)TimerGetTime() > VG_WIND_TIMER)        
		   { 
			   switch(VG_WIND_BLOWING)
			   {
					case WIND_STOPPED:		// left mouse button
					   VG_WIND_BLOWING = WIND_FAST;
					   VG_WIND_TIMER = (int)TimerGetTime() + (1000 + (rand()%3000));
					break;

					case WIND_FAST:		// left mouse button
					   VG_WIND_BLOWING = WIND_SLOW;
					   VG_WIND_TIMER = (int)TimerGetTime() + 500;
					break;
        
					case WIND_SLOW:		// left mouse button
					   VG_WIND_BLOWING = WIND_STOPPED;
					   VG_WIND_TIMER = (int)TimerGetTime() + (3000 + (rand()%3000));
					break;

			   }  

		   }

		   if(title_sequence == 0)              
		   {   

			   // Get clock offset for attaching to background...
			   if(scene == VG_MINSO)
			   {
			       VG_clock_offset = sprite[14].x - sprite[1].x;
				   VG_clock2_offset = sprite[15].x - sprite[1].x;
			   }
			   if(scene == VG_SIU)
			   {
			       VG_clock_offset = sprite[15].x - sprite[1].x;
			   }
			   if(scene == VG_SHO)
			   {
			       VG_clock_offset = sprite[15].x - sprite[1].x;
				   VG_suitcase_offset = sprite[15].y;
			   }
			   if(scene == VG_GYEONG) 
			   {
			       VG_clock_offset = sprite[14].x - sprite[1].x; 
			   } 

			   VG_suitcase_timer = 0;
			   VG_suitcase_resetting = false;

			   VG_1_LEGS = 0;  
			   VG_2_LEGS = 0;  
			      
			   if(VG_1_CHARACTER == VG_GYEONG)
			       VG_1_LEGS = New_Sprite(sprite[2].x, sprite[2].y, sprite[2].x, sprite[2].y, 75, LOOP, sprite[2].width, sprite[2].height, sprite[2].width, sprite[2].height, 3, NON, 1.0f, 0, -1, 0, 0, sprite[2].id, 0, 0, 0, -1);
			   if(VG_2_CHARACTER == VG_GYEONG)
			       VG_2_LEGS = New_Sprite(sprite[3].x, sprite[3].y, sprite[3].x, sprite[3].y, 75, LOOP, sprite[3].width, sprite[3].height, sprite[3].width, sprite[3].height, 3, NON, 1.0f, 0, -1, 0, 0, sprite[3].id, 0, 0, 0, -1);

			   if(VG_1_CHARACTER == VG_SIU)
			       VG_1_LEGS = New_Sprite(sprite[2].x, sprite[2].y, sprite[2].x, sprite[2].y, 74, LOOP, sprite[2].width, sprite[2].height, sprite[2].width, sprite[2].height, 3, NON, 1.0f, 0, -1, 0, 0, sprite[2].id, 0, 0, 0, -1);
			   if(VG_2_CHARACTER == VG_SIU)
			       VG_2_LEGS = New_Sprite(sprite[3].x, sprite[3].y, sprite[3].x, sprite[3].y, 74, LOOP, sprite[3].width, sprite[3].height, sprite[3].width, sprite[3].height, 3, NON, 1.0f, 0, -1, 0, 0, sprite[3].id, 0, 0, 0, -1);
			     				     	
			   if(VG_1_CHARACTER == VG_MINSO)
			       VG_1_LEGS = New_Sprite(sprite[2].x, sprite[2].y, sprite[2].x, sprite[2].y, 75, LOOP, sprite[2].width, sprite[2].height, sprite[2].width, sprite[2].height, 3, NON, 1.0f, 0, -1, 0, 0, sprite[2].id, 0, 0, 0, -1);
			   if(VG_2_CHARACTER == VG_MINSO)
			       VG_2_LEGS = New_Sprite(sprite[3].x, sprite[3].y, sprite[3].x, sprite[3].y, 75, LOOP, sprite[3].width, sprite[3].height, sprite[3].width, sprite[3].height, 3, NON, 1.0f, 0, -1, 0, 0, sprite[3].id, 0, 0, 0, -1);

			   if(VG_1_CHARACTER == VG_JAE)
			       VG_1_LEGS = New_Sprite(sprite[2].x, sprite[2].y, sprite[2].x, sprite[2].y, 74, LOOP, sprite[2].width, sprite[2].height, sprite[2].width, sprite[2].height, 3, NON, 1.0f, 0, -1, 0, 0, sprite[2].id, 0, 0, 0, -1);
			   if(VG_2_CHARACTER == VG_JAE)
			       VG_2_LEGS = New_Sprite(sprite[3].x, sprite[3].y, sprite[3].x, sprite[3].y, 74, LOOP, sprite[3].width, sprite[3].height, sprite[3].width, sprite[3].height, 3, NON, 1.0f, 0, -1, 0, 0, sprite[3].id, 0, 0, 0, -1);

			   if(VG_1_CHARACTER == VG_HYUK)
			       VG_1_LEGS = New_Sprite(sprite[2].x, sprite[2].y, sprite[2].x, sprite[2].y, 74, LOOP, sprite[2].width, sprite[2].height, sprite[2].width, sprite[2].height, 3, NON, 1.0f, 0, -1, 0, 0, sprite[2].id, 0, 0, 0, -1);
			   if(VG_2_CHARACTER == VG_HYUK)
			       VG_2_LEGS = New_Sprite(sprite[3].x, sprite[3].y, sprite[3].x, sprite[3].y, 74, LOOP, sprite[3].width, sprite[3].height, sprite[3].width, sprite[3].height, 3, NON, 1.0f, 0, -1, 0, 0, sprite[3].id, 0, 0, 0, -1);
			     				   			     				     	
			   if(VG_1_LEGS > 0 && VG_1_LEGS < TOTAL_NO_SPRITES)
				   sprite[VG_1_LEGS].alpha = 0.0f;
			   if(VG_2_LEGS != 0 && VG_2_LEGS < TOTAL_NO_SPRITES)
				   sprite[VG_2_LEGS].alpha = 0.0f;

			    // Create scrolling floor... 
				testY = 0.0f;
				          
				VG_SCROLL_INDEX = no_sprites;  
				   
				VG_GROUND_INDEX = VG_SCROLL_INDEX + 8;     

				for(int i = 0 ;i < 16;i++)   
				{
				//	if(i == 0 || i == 1) 
				//		floor_anim = 16;
				//	else
						floor_anim = 16-i;

					New_Sprite(sprite[1].x, (sprite[1].y - 0.0250f) + testY, sprite[1].x, (sprite[1].y - 0.0250f) + testY, floor_anim, LOOP, sprite[1].width, 0.0125f, sprite[1].width, 0.0125f, 5, NON, 1.0f, 0, -1, 0, 0, 33, 0, 0, 0, -1);
					testY = (float)i * 0.0125f;
				}

				VG_SABU_JUDGE_INDEX = -1;

				// Create Judge Sabu for duelling...
			   if(VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_DUELLING)
			   {
				   VG_JUDGE_AI_TIMER = 0;
				   VG_JUDGE_AI = VG_JUDGE_IDLE;
				   VG_SABU_JUDGE_INDEX = New_Sprite(sprite[1].x + (sprite[1].width/2 - 0.2f), VG_PLAYERS_STARTY + 0.015f, sprite[1].x + (sprite[1].width/2 - 0.2f), VG_PLAYERS_STARTY + 0.015f, 0, LOOP, 0.4f, 0.4f, 0.4f, 0.4f, 3, NON, 1.0f, 0, -1, 0, 0, 34, 0, 0, 0, -1);
			   }

			   if(VG_BACKGROUND == VG_KENNEDY)
			   {
				   VG_JUDGE_AI_TIMER = 0;
				   VG_JUDGE_AI = VG_JUDGE_IDLE;
				   VG_SABU_JUDGE_INDEX = New_Sprite(sprite[1].x + (sprite[1].width/2 - 0.2f), VG_PLAYERS_STARTY + 0.015f, sprite[1].x + (sprite[1].width/2 - 0.2f), VG_PLAYERS_STARTY + 0.015f, 0, LOOP, 0.4f, 0.4f, 0.4f, 0.4f, 3, NON, 1.0f, 0, -1, 0, 0, 34, 0, 0, 0, -1);
			   }

			   if(VG_GAME_MODE == VG_TRAINING_MODE)
			   {
				   VG_Display_moves = true;
			   }

			   VG_flash_survive_timer = 0;
			   VG_flash_survive_local_timer = 0;
			   VG_flash_survive = false;

			   vg_lowtime_timer = 0;
			   vg_lowtime_flash = false;

			   // Turn off other characters...specific to story mode...
			   if(episode == 5 && scene == 4) // Apartment
			   {
				   sprite[10].alpha = 0.0f; // Kyung

				   if(VG_GAME_MODE == VG_STORY_MODE)
				   if(VG_1_CHARACTER == VG_MINSO)
				   if(VG_CURRENT_STORY_SCENE == 9)
					   sprite[10].alpha = 1.0f; // Kyung
			   }

			   vg_arrest_successful = false;
			   vg_waste_successful = false;

			   VG_displayed_story_help = false;
			   story_help_timer = (int)TimerGetTime() + 500;

			   VG_HEALTH_LOADING = true;

			   VG_1_CORNERED = false;
			   VG_2_CORNERED = false;

			   VG_1_THROWING_SEQUENCE = 0;
			   VG_2_THROWING_SEQUENCE = 0;

			   VG_1_THROWING = false;
			   VG_2_THROWING = false; 

			   if(VG_has_no_explosive == false)
				   VG_1_HAS_THROW = true;
			   else
				   VG_1_HAS_THROW = false;

			   VG_2_HAS_THROW = true;

			   VG_1_HANDCUFFED = 0;
			   VG_2_HANDCUFFED = 0;

			   VG_voice_delay=-1; 

			   if( VG_BACKGROUND == VG_GUN)
				   vg_amb_prison_sfx = true;

			   if( VG_BACKGROUND == VG_KENNEDY)
				   vg_amb_prison_sfx = true;

			   if( VG_BACKGROUND == VG_SANG)
				   vg_amb_prison_sfx = true;

			   if( VG_BACKGROUND == VG_MINSO)
				   vg_amb_traffic_sfx = true; 

			   if( VG_BACKGROUND == VG_SHRINE)
				   vg_amb_duel_sfx = true;

			   if( VG_BACKGROUND == VG_REESE )  
			   {

				    for(int i = 0; i < 20; i++)   
					{      
						frnd = (float)(rand()%100);
						frnd /= 100.0f;

						mid_x = sprite[1].width * frnd;  
						mid_x += sprite[1].x;
						 
						frnd = (float)(rand()%100);
						frnd /= 100.0f;

						mid_y = (sprite[1].height/8) * frnd;
						mid_y += sprite[1].y;

						if(mid_y >= sprite[2].y)
			   			    New_FX(mid_x, mid_y,  mid_x, mid_y, 15, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 4, GFX, 1.0f, 0, 5, FX_LEAF1, 5, 12, 0, 0, 1); 
						else
			   			    New_FX(mid_x, mid_y,  mid_x, mid_y, 13, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 5, FX_LEAF, 5, 12, 0, 0, 1); 
					}
			   } 
			    
			   if( VG_BACKGROUND == VG_SIU )  
			   {

				    for(int i = 0; i < 10; i++)   
					{       
						frnd = (float)(rand()%100); 
						frnd /= 100.0f;

						mid_x = sprite[1].width * frnd;  
						mid_x += sprite[1].x;

						frnd = (float)(rand()%100);
						frnd /= 100.0f;

						mid_y = (sprite[1].height/8) * frnd; 
						mid_y += sprite[1].y;

						if(mid_y >= sprite[2].y)
			   			    New_FX(mid_x, mid_y,  mid_x, mid_y, 19, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 4, GFX, 1.0f, 0, 5, FX_RUBBISH1, 5, 12, 0, 0, 1); 
						else
			   			    New_FX(mid_x, mid_y,  mid_x, mid_y, 17, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 5, FX_RUBBISH, 5, 12, 0, 0, 1); 
					}
			   } 

			   if(scene == 1)   
			   { 
				   	train_startX = sprite[10].x;  
					train_start1X = sprite[11].x;  

					vg_train_timer = (int)TimerGetTime();
			   }

			   if(scene == VG_MINSO)
			   {
				    billboard_offsetX = sprite[13].x - sprite[0].x;

					BILLBOARD_STATE = BILL_WAITING;
					BILLBOARD_TIMER = (int)TimerGetTime() + BILLBOARD_WAIT_LENGTH;
					BILLBOARD_DIRECTION = BILL_RIGHT;

					sprite[13].y -= 0.001f;

					sprite[13].u[0] = 0.5f;
					sprite[13].u[1] = 0.0f;
					sprite[13].u[2] = 0.0f;
					sprite[13].u[3] = 0.5f;

					sprite[15].y -= 0.001f;

					sprite[15].u[0] = 0.5f;
					sprite[15].u[1] = 0.0f;
					sprite[15].u[2] = 0.0f;
					sprite[15].u[3] = 0.5f;
			   }

			   // Select character faces...
			   for(int i = 0;i<10;i++)   
			   if(VG_1_CHARACTER == i)  
			   {
				   if(VG_IS_AN_ALTER_P1 == true)
				       Set_Sprite(3, i+8, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...
				   else
				       Set_Sprite(3, i, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...
			   }
			   for(int i = 0;i<10;i++)
			   if(VG_2_CHARACTER == i) 
			   {
				   if((VG_IS_AN_ALTER == true)) // VG_1_CHARACTER == VG_2_CHARACTER || 
				       Set_Sprite(4, i+8, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...
				   else
				       Set_Sprite(4, i, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...

				   if(VG_GAME_MODE == VG_VERSUS_MODE)
				   if(VG_1_CHARACTER == VG_2_CHARACTER && VG_IS_AN_ALTER == false)
				       Set_Sprite(4, i+16, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...

			   }

			   if(VG_1_CHARACTER == VG_SANG)  
				    Set_Sprite(3, 24, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...
			   if(VG_1_CHARACTER == VG_TRAINER) 
				    Set_Sprite(3, 25, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...
			   if(VG_2_CHARACTER == VG_SANG) 
				    Set_Sprite(4, 24, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...
			   if(VG_2_CHARACTER == VG_TRAINER) 
				    Set_Sprite(4, 25, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...

			   if (VG_1_CHARACTER == VG_SHO)
				   Set_Sprite(3, 26, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...
			   if (VG_1_CHARACTER == VG_TIA)
				   Set_Sprite(3, 27, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...
			   if (VG_1_CHARACTER == VG_SAIZO)
				   Set_Sprite(3, 29, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...
			   if (VG_1_CHARACTER == VG_KENNEDY)
				   Set_Sprite(3, 31, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...

			   if (VG_2_CHARACTER == VG_SHO)
				   Set_Sprite(4, 26, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...
			   if (VG_2_CHARACTER == VG_TIA)
				   Set_Sprite(4, 27, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...
			   if (VG_2_CHARACTER == VG_SAIZO)
				   Set_Sprite(4, 29, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...
			   if (VG_2_CHARACTER == VG_KENNEDY)
				   Set_Sprite(4, 31, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Left face...

				if(VG_GAME_MODE == VG_VERSUS_MODE)
				if(VG_2_CHARACTER == VG_SHO)
				if(VG_1_CHARACTER == VG_2_CHARACTER && VG_IS_AN_ALTER == false)
				    Set_Sprite(4, 28, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Sho in blue face...

				if(VG_GAME_MODE == VG_VERSUS_MODE)
				if(VG_2_CHARACTER == VG_SAIZO)
				if(VG_1_CHARACTER == VG_2_CHARACTER && VG_IS_AN_ALTER == false)
				    Set_Sprite(4, 30, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Saizo in red face...

			   // ---------------------------- // 
			    
			   VG_1_Moves_count = 0;  
			   VG_2_Moves_count = 0;
			   VG_1_MovesList_count = 0; 
			   VG_2_MovesList_count = 0;

			   memset(VG_1_Moves, 0, sizeof(VG_1_Moves));
			   memset(VG_2_Moves, 0, sizeof(VG_2_Moves));
			   memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList));
			   memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList));

			   hud[14].flash_target = false;
			   hud[14].alpha = 0.0f; // Win/lose...

			   VG_1_BULLETS = 3; 
			   VG_2_BULLETS = 3;  
			       
			   if(VG_1_CHARACTER == VG_JAE)
				   VG_1_BULLETS = 2;
			   if(VG_2_CHARACTER == VG_JAE) 
				   VG_2_BULLETS = 2; 
			     
			   if(VG_1_CHARACTER == VG_SIU)
				   VG_1_BULLETS = 3;
			   if(VG_2_CHARACTER == VG_SIU)
				   VG_2_BULLETS = 3;
			     
			   if(VG_1_CHARACTER == VG_GYEONG)
				   VG_1_BULLETS = 2;
			   if(VG_2_CHARACTER == VG_GYEONG)
				   VG_2_BULLETS = 2;

			   if(VG_1_CHARACTER == VG_HYUK)
				   VG_1_BULLETS = 1;
			   if(VG_2_CHARACTER == VG_HYUK) 
				   VG_2_BULLETS = 1;

			   if(VG_1_CHARACTER == VG_GUN) 
				   VG_1_BULLETS = 0;
			   if(VG_2_CHARACTER == VG_GUN)
				   VG_2_BULLETS = 0;

			   if(VG_1_CHARACTER == VG_SANG)
				   VG_1_BULLETS = 2;
			   if(VG_2_CHARACTER == VG_SANG) 
				   VG_2_BULLETS = 2;

			   if(VG_1_CHARACTER == VG_REESE)
				   VG_1_BULLETS = 2;
			   if(VG_2_CHARACTER == VG_REESE) 
				   VG_2_BULLETS = 2;

			   if (VG_1_CHARACTER == VG_SHO)
				   VG_1_BULLETS = 3;
			   if (VG_2_CHARACTER == VG_SHO)
				   VG_2_BULLETS = 3;

			   if (VG_1_CHARACTER == VG_TIA)
				   VG_1_BULLETS = 3;
			   if (VG_2_CHARACTER == VG_TIA)
				   VG_2_BULLETS = 3;

			   if (VG_1_CHARACTER == VG_SAIZO)
				   VG_1_BULLETS = 3;
			   if (VG_2_CHARACTER == VG_SAIZO)
				   VG_2_BULLETS = 3;

			   if(VG_1_CHARACTER == VG_KENNEDY) 
				   VG_1_BULLETS = 0;
			   if(VG_2_CHARACTER == VG_KENNEDY)
				   VG_2_BULLETS = 0;

			   VG_1_BOXHEIGHT = sprite[2].box_height;
			   VG_2_BOXHEIGHT = sprite[3].box_height;

			   VG_1_Moves_count = 0;  
			   VG_2_Moves_count = 0;

			   VG_BATTLE_TIMER = (int)TimerGetTime() + 1000;

			   VG_JUMP_HEIGHT = 0.25f;     
			    
			   sprite[2].y = VG_PLAYERS_STARTY;

			   VG_START_Y = sprite[2].y;
			   VG_LAYER1_X = sprite[0].x;

			   VG_SCREEN_X = sprite[13].x;

			   sprite[3].y = VG_START_Y;

			   sprite[6].y = VG_START_Y;  
			   sprite[5].y = VG_START_Y;

			   sprite[2].pain = false;
			   sprite[3].pain = false;

			   sprite[2].knockdown = false;
			   sprite[3].knockdown = false;

			   sprite[2].jumping = false;
			   sprite[3].jumping = false;

			   sprite[2].electrocute = false;
			   sprite[3].electrocute = false;

			   sprite[2].status = -1;  
			   sprite[3].status = -1;

			   sprite[2].special = 0;  
			   sprite[3].special = 0;
			     
			   sprite[2].action_timer = 0; 
			   sprite[3].action_timer = 0;

			//   sprite[2].anim_state = NO_ANIM;
			//   sprite[3].anim_state = NO_ANIM;

			   sprite[2].hit_opponent = false;
			   sprite[3].hit_opponent = false;

			   sprite[2].movement = RIGHT;
			   sprite[3].movement = LEFT;

			   sprite[2].direction = RESET; 
			   sprite[3].direction = RESET;

			   sprite[2].handcuffed = false; 
			   sprite[3].handcuffed = false;

			   sprite[2].dizzy = false; 
			   sprite[3].dizzy = false;

			   sprite[2].sticky = false; 
			   sprite[3].sticky = false; 

			   sprite[2].walking_backwards = false; 
			   sprite[3].walking_backwards = false;

			   sprite[2].jumping = false;
			   sprite[3].jumping = false;

			   sprite[2].status = -1; 
			   sprite[3].status = -1;  
			    
			   sprite[2].special = 0; 
			   sprite[3].special = 0;

			   VG_1_DEFEATED_BY_BOMB = false; 
			   VG_2_DEFEATED_BY_BOMB = false;

			   if(VG_ROUND_CONDITIONS == CONDITION_TIMED_BASIC || VG_ROUND_CONDITIONS == CONDITION_TIMED)
			   {
				   if(VG_ROUND == 1)
					   VG_TIME = 39;   
				   else
					   VG_TIME = 29;   
			   }  
			   else     
			       VG_TIME = 99;      

			   if(VG_ROUND_CONDITIONS == CONDITION_SURVIVE)
				   VG_TIME = 39;   

			   if(VG_GAME_MODE == VG_VERSUS_MODE)
			   if(VG_VS_TIME == 1) 
				   VG_TIME = 59; 

			   if(VG_GAME_MODE == VG_ARCADE_MODE)
			   if(VG_ARCADE_TYPE == VG_ARCADE_DUELLING)
				   VG_TIME = 9; 

			   // Testing round timer..
			//      VG_TIME = 4; 

			   // Timer...  
			   new_counter[0].alpha = 1.0f;   
			   new_counter[0].id = 0; 
			   new_counter[0].x = -0.015f;          
			   new_counter[0].y = 0.333f;
			   new_counter[0].type = 0;  // Large Font...
			   new_counter[0].right = false; 

			   sprintf( new_counter[0].word, "");  

			   sprintf( new_counter[0].word, "KO^%i", VG_TIME);

			   // Player 1 name...
			   new_counter[1].alpha = 1.0f;   
			   new_counter[1].id = 0;     
			   new_counter[1].x = -0.54f;       
			   new_counter[1].y = 0.285f;
			   new_counter[1].type = 0;  // Large Font...
			   new_counter[1].right = false; 

			   sprintf( new_counter[1].word, "");   

			   if(VG_1_CHARACTER == VG_GYEONG) 
			       sprintf( VG_1_NAME, "GYEONG");   
			   if(VG_1_CHARACTER == VG_SIU)
			       sprintf( VG_1_NAME, "SI$U");   
			   if(VG_1_CHARACTER == VG_MINSO) 
			       sprintf( VG_1_NAME, "MINSO");   
			   if(VG_1_CHARACTER == VG_REESE)
			       sprintf( VG_1_NAME, "REESE");   
			   if(VG_1_CHARACTER == VG_YOHAN)
			       sprintf( VG_1_NAME, "YOHAN");   
			   if(VG_1_CHARACTER == VG_JAE)
			       sprintf( VG_1_NAME, "JAE");   
			   if(VG_1_CHARACTER == VG_GUN)
			       sprintf( VG_1_NAME, "GUN");   
			   if(VG_1_CHARACTER == VG_HYUK)
			       sprintf( VG_1_NAME, "HYUK");   
			   if(VG_1_CHARACTER == VG_SANG)
			       sprintf( VG_1_NAME, "SANG");    
			   if(VG_1_CHARACTER == VG_TRAINER) 
			       sprintf( VG_1_NAME, "SABU");  
			   if (VG_1_CHARACTER == VG_SHO)
				   sprintf(VG_1_NAME, "SHO");
			   if (VG_1_CHARACTER == VG_TIA)
				   sprintf(VG_1_NAME, "TIA");
			   if (VG_1_CHARACTER == VG_SAIZO)
				   sprintf(VG_1_NAME, "SAIZO");
			   if(VG_1_CHARACTER == VG_KENNEDY)
			       sprintf( VG_1_NAME, "K.ANDERSON");   

			   if(VG_1_CHARACTER == VG_GYEONG && VG_IS_AN_ALTER_P1 == true) 
			       sprintf( VG_1_NAME, "TOYUN");   
			   if(VG_1_CHARACTER == VG_SIU && VG_IS_AN_ALTER_P1 == true)
			       sprintf( VG_1_NAME, "DAE-SU");   
			   if(VG_1_CHARACTER == VG_MINSO && VG_IS_AN_ALTER_P1 == true) 
			       sprintf( VG_1_NAME, "MIA");   
			   if(VG_1_CHARACTER == VG_REESE && VG_IS_AN_ALTER_P1 == true)
			       sprintf( VG_1_NAME, "BOB");   
			   if(VG_1_CHARACTER == VG_YOHAN && VG_IS_AN_ALTER_P1 == true)
			       sprintf( VG_1_NAME, "SUNG-KI");   
			   if(VG_1_CHARACTER == VG_JAE && VG_IS_AN_ALTER_P1 == true)
			       sprintf( VG_1_NAME, "SAPPORO");   
			   if(VG_1_CHARACTER == VG_GUN && VG_IS_AN_ALTER_P1 == true)
			       sprintf( VG_1_NAME, "KONU");   
			   if(VG_1_CHARACTER == VG_HYUK && VG_IS_AN_ALTER_P1 == true)
			       sprintf( VG_1_NAME, "YE-JUN"); 

			   // Player 2 name...
			   new_counter[2].alpha = 1.0f;     
			   new_counter[2].id = 0;       
			   new_counter[2].x = 0.540f;               
			   new_counter[2].y = 0.285f;
			   new_counter[2].type = 0;  // Large Font...
			   new_counter[2].right = true; 

			   sprintf( new_counter[2].word, ""); 
			    
			   if(VG_2_CHARACTER == VG_GYEONG)
			       sprintf( VG_2_NAME, "GYEONG");   
			   if(VG_2_CHARACTER == VG_SIU)
			       sprintf( VG_2_NAME, "SI$U");   
			   if(VG_2_CHARACTER == VG_MINSO)
			       sprintf( VG_2_NAME, "MINSO");   
			   if(VG_2_CHARACTER == VG_REESE)  
			       sprintf( VG_2_NAME, "REESE");      
			   if(VG_2_CHARACTER == VG_YOHAN) 
			       sprintf( VG_2_NAME, "YOHAN");    
			   if(VG_2_CHARACTER == VG_JAE) 
			       sprintf( VG_2_NAME, "JAE");   
			   if(VG_2_CHARACTER == VG_GUN)
			       sprintf( VG_2_NAME, "GUN");    
			   if(VG_2_CHARACTER == VG_HYUK)    
			       sprintf( VG_2_NAME, "HYUK");   
			   if(VG_2_CHARACTER == VG_SANG)     
			       sprintf( VG_2_NAME, "SANG");   
			   if(VG_2_CHARACTER == VG_TRAINER)  
			       sprintf( VG_2_NAME, "SABU");  
			   if (VG_2_CHARACTER == VG_SHO)
				   sprintf(VG_2_NAME, "SHO");
			   if (VG_2_CHARACTER == VG_TIA)
				   sprintf(VG_2_NAME, "TIA");
			   if (VG_2_CHARACTER == VG_SAIZO)
				   sprintf(VG_2_NAME, "SAIZO");
			   if(VG_2_CHARACTER == VG_KENNEDY)
			       sprintf( VG_2_NAME, "K.ANDERSON");  

				if(VG_2_CHARACTER == VG_GYEONG && VG_IS_AN_ALTER == true)
					sprintf( VG_2_NAME, "TOYUN");
				if(VG_2_CHARACTER == VG_SIU && VG_IS_AN_ALTER == true)
					sprintf( VG_2_NAME, "DAE-SU");
				if(VG_2_CHARACTER == VG_MINSO && VG_IS_AN_ALTER == true)
					sprintf( VG_2_NAME, "MIA");
				if(VG_2_CHARACTER == VG_REESE && VG_IS_AN_ALTER == true)
					sprintf( VG_2_NAME, "BOB");
				if(VG_2_CHARACTER == VG_GUN && VG_IS_AN_ALTER == true)
					sprintf( VG_2_NAME, "KONU");
				if(VG_2_CHARACTER == VG_YOHAN && VG_IS_AN_ALTER == true)
					sprintf( VG_2_NAME, "SUNG-KI");
				if(VG_2_CHARACTER == VG_JAE && VG_IS_AN_ALTER == true)
					sprintf( VG_2_NAME, "SAPPORO");			    
				if(VG_2_CHARACTER == VG_HYUK && VG_IS_AN_ALTER == true)
					sprintf( VG_2_NAME, "YE-JUN");	

			   // Rounds won p1...
		//	   new_counter[5].alpha = 1.0f;     
			   new_counter[5].id = 0;        
			   new_counter[5].x = -0.065f;                 
			   new_counter[5].y = 0.285f; 
			   new_counter[5].type = 0;  // Large Font... 
			   new_counter[5].right = true; 

			   sprintf( new_counter[5].word, ""); 

			   // Rounds won p2... 
		//	   new_counter[6].alpha = 1.0f;     
			   new_counter[6].id = 0;            
			   new_counter[6].x = 0.065f;                 
			   new_counter[6].y = 0.285f; 
			   new_counter[6].type = 0;  // Large Font...
			   new_counter[6].right = false; 

			   sprintf( new_counter[6].word, ""); 

			   // Player 1 score...
			   new_counter[3].alpha = 1.0f;    
			   new_counter[3].id = 2;          
			   new_counter[3].x = -0.54f;             
			   new_counter[3].y = 0.375f;
			   new_counter[3].type = 1;  // Large Font... 
			   new_counter[3].right = false; 

			   sprintf( new_counter[3].word, ""); 

			   if(VG_GAME_MODE == VG_STORY_MODE)
				   sprintf( new_counter[3].word, "FREE PLAY"); 
			   else
			   {
				   if(VG_GAME_MODE == VG_VERSUS_MODE)
					   sprintf( new_counter[3].word, "INSERT COIN"); 
				   else
				   { 
					   sprintf( new_counter[3].word, "CREDITS 0%i", (VG_1_CREDITS-1));

					   if(VG_SURVIVAL == true)
					   {
						   if(VG_SURVIVAL_WINS <= 9)
							   sprintf( new_counter[3].word, "WINS 0%i", VG_SURVIVAL_WINS);
						   else
							   sprintf( new_counter[3].word, "WINS %i", VG_SURVIVAL_WINS);
					   }
				   }
			   }

			   // Player 2 score...
			   new_counter[4].alpha = 1.0f;     
			   new_counter[4].id = 2;      
			   new_counter[4].x = 0.545f;             
			   new_counter[4].y = 0.375f;
			   new_counter[4].type = 1;  // Large Font...
			   new_counter[4].right = true; 

			   sprintf( new_counter[4].word, ""); 

			   if(VG_GAME_MODE == VG_STORY_MODE)
				   sprintf( new_counter[4].word, "FREE PLAY"); 
			   else
				   sprintf( new_counter[4].word, "INSERT COIN");  

			   // Ratios...   
			   if (screen_mode == SCREEN_NORMAL)
			   {
				   Set_Sprite(2, 1, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Healthbar...
				   new_counter[1].x = -0.44f; // P1 name...
				   new_counter[3].x = -0.40f; // P1 score...

				   new_counter[2].x = 0.44f; // P2 name...
				   new_counter[4].x = 0.40f; // P2 score...

				   VG_SCREEN_EDGE = 0.60f;   // 0.65f
				   screen_limit = 0.9f; // limit between characters...

				   hud[15].x += 0.15f; // Combo hits...
				   hud[16].x -= 0.15f; // Combo hits... 

				   hud[3].x += 0.15f;
				   hud[8].x += 0.17f;  // P1 bullets 
				   hud[17].x += 0.17f; // P1 Handcuffs..

				   hud[4].x -= 0.15f;
				   hud[9].x -= 0.17f;  // P2 bullets   
				   hud[18].x -= 0.17f; // P2 Handcuffs..

				   hud[7].width = hud[7].width - 0.15f;
				   hud[7].x += 0.15f;
				   hud[7].w += 0.15f;

				   hud[6].width = hud[6].width - 0.15f;

				   hud[7].box_width = hud[7].width;
				   hud[6].box_width = hud[6].width;

			   }
			   // Ratios...   
			   if(screen_mode == SCREEN_1610_WIDESCREEN) 
			   {
				   Set_Sprite(2, 1, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Healthbar...
				   new_counter[1].x = -0.48f; // P1 name...
				   new_counter[3].x = -0.48f; // P1 score...
				    
				   new_counter[2].x = 0.48f; // P2 name...
				   new_counter[4].x = 0.48f; // P2 score...

				   VG_SCREEN_EDGE = 0.70f;   // 0.65f
				   screen_limit = 1.1f;	

				   hud[15].x += 0.06f; // Combo hits...
				   hud[16].x -= 0.06f; // Combo hits... 

				   hud[3].x += 0.06f;   
				   hud[8].x += 0.06f;  // P1 bullets
				   hud[17].x += 0.06f; // P1 Handcuffs..
				    
				   hud[4].x -= 0.06f;  
				   hud[9].x -= 0.06f;  // P2 bullets   
				   hud[18].x -= 0.06f; // P2 Handcuffs..

				   hud[7].width = hud[7].width - 0.06f;
				   hud[7].x += 0.06f; 
				   hud[7].w += 0.06f;

				   hud[6].width = hud[6].width - 0.06f;

				   hud[7].box_width = hud[7].width;
				   hud[6].box_width = hud[6].width;  

			   }
			   if(screen_mode == SCREEN_169_WIDESCREEN)  
			   {
				   Set_Sprite(2, 0, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Healthbar...
				   VG_SCREEN_EDGE = 0.80f; // 0.75f     
				   screen_limit = 1.2f;    
			   }  

			   hud[15].alpha = 0.0f;  
			   hud[16].alpha = 0.0f;  

			   hud[15].mov_x = hud[15].x;
			   hud[16].mov_x = hud[16].x;

			   sprite[2].flash_target = true; 
			   sprite[2].flash_timer = (int)TimerGetTime() + 15;

			   sprite[3].flash_target = true; 
			   sprite[3].flash_timer = (int)TimerGetTime() + 15;

			   VG_1_HEALTH = STARTING_HEALTH;   
			   VG_2_HEALTH = STARTING_HEALTH;   
			         
			   VG_1_TOTALHEALTH = STARTING_HEALTH;       
			   VG_2_TOTALHEALTH = STARTING_HEALTH;  

			   VG_ROUND_LIMIT = 2; 

			   if(VG_GAME_MODE == VG_ARCADE_MODE)
			   if(VG_ARCADE_TYPE == VG_ARCADE_DUELLING)
			   {
				   VG_ROUND_LIMIT = 2;

				   VG_1_HEALTH = 49;    
				   VG_2_HEALTH = 49;   
			        
				   VG_1_TOTALHEALTH = 50;       
				   VG_2_TOTALHEALTH = 50;  
			   }

			   if(VG_SURVIVAL == true)
			   {
				   VG_1_TOTALHEALTH = 2000;       
				   VG_2_TOTALHEALTH = 2000;  

				   VG_1_HEALTH = VG_1_SURVIVAL_HEALTH;
				   VG_2_HEALTH = 2000;

				   if(VG_SURVIVAL_ROUND == 1)
					   VG_1_HEALTH += 250;

				   if(VG_SURVIVAL_ROUND == 2)
					   VG_1_HEALTH += 150;

				   if(VG_SURVIVAL_ROUND >= 3)
					   VG_1_HEALTH += 100;

				   if(VG_1_HEALTH > VG_1_TOTALHEALTH)
					   VG_1_HEALTH = VG_1_TOTALHEALTH;

			   }
			    
			   if(VG_GAME_MODE == VG_VERSUS_MODE)
			   if(VG_VS_HEALTH == 1)       
			   {
				   VG_1_HEALTH = VG_VS_HIGH_HEALTH;   
				   VG_2_HEALTH = VG_VS_HIGH_HEALTH;   
			        
				   VG_1_TOTALHEALTH = VG_VS_HIGH_HEALTH;       
				   VG_2_TOTALHEALTH = VG_VS_HIGH_HEALTH;  
			   }

			   if(VG_ROUND_CONDITIONS == CONDITION_LOW_HEALTH)
			   {
				   VG_1_HEALTH = 750;
			   }
			   if(VG_ROUND_CONDITIONS == CONDITION_MID_HEALTH)
			   {
				   VG_1_HEALTH = 750;
			   }

			   VG_1_NEWHEALTH = 0.0f;   
			   VG_2_NEWHEALTH = 0.0f;

			   if(scene == 0)
			   {
				   sprite[8].mov_x = VG_Get_Speed();				
				   sprite[9].mov_x = VG_Get_Speed(); 
				   sprite[10].mov_x = VG_Get_Speed(); 
			   }

			   VG_finished_round = true; 
			     
			   hud[10].mov_x = hud[10].x;         
			   hud[11].mov_x = hud[11].x;     
			    
		//	   hud[12].mov_y = hud[12].y - 0.085f;         
		//	   hud[13].mov_y = hud[13].y + 0.085f;

			   hud[12].action_timer = (int)TimerGetTime() + 250;
			    
			   hud[10].x -= 1.00f;     
			   hud[11].x += 1.00f;        

			   hud[10].alpha = 1.0f; 
			   hud[11].alpha = 1.0f;

			//   hud[12].alpha = 0.0f;  
			//   hud[13].alpha = 0.0f;     

               hud[10].flash_target = false; 
               hud[10].flash_timer  = 0;

               hud[11].flash_target = false;  
               hud[11].flash_timer  = 0;

			   if(VG_ROUND > 0 && VG_ROUND <= 8)
				   Set_Sprite(10, (VG_ROUND-1), LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Healthbar...

			   VG_health_move_timer = 0;

			   title_timer = (int)TimerGetTime() + 200;   
			     
			   title_sequence++;      
			     
			   if(QUICK_PLAY == 1 || VG_SKIP_INTRO == true)
			   { 
				   VG_finished_round = false; 
				   title_sequence = 101;   
			   }     
			     
			   VG_intro_sequence = 2;

			   if(VG_INTRO_DOG1 > 0 && VG_INTRO_DOG1 < TOTAL_NO_SPRITES)
			   if(VG_INTRO_DOG2 > 0 && VG_INTRO_DOG2 < TOTAL_NO_SPRITES)
			   {
 	   			   sprite[VG_INTRO_DOG1].grab_switch = false; 
				   sprite[VG_INTRO_DOG1].moving = false; 
 	   			   sprite[VG_INTRO_DOG2].grab_switch = false; 
				   sprite[VG_INTRO_DOG2].moving = false; 
			   }

			   if(VG_SKIP_INTRO == false) 
			   if(VG_INTRO_DOG1 > 0 && VG_INTRO_DOG1 < TOTAL_NO_SPRITES)
			   if(VG_INTRO_DOG2 > 0 && VG_INTRO_DOG2 < TOTAL_NO_SPRITES)
			   { 
				   VG_intro_sequence = 0; 
				   VG_intro_timer = (int)TimerGetTime() + 1000;  
				   VG_dog_timer = (int)TimerGetTime() + 1500; 

				   Set_Sprite(2, 40, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Intro anim...
				   Set_Sprite(3, 40, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Intro anim...

				   if(VG_1_CHARACTER == VG_MINSO)   
				   {
					   if(VG_1_EQUIPMENT == EQUIPMENT_ALL || VG_ROUND_CONDITIONS == CONDITION_BASIC_BOTH)
					   {
						   Set_Sprite(VG_INTRO_DOG1, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Intro anim...
						   sprite[VG_INTRO_DOG1].x = sprite[2].x - sprite[2].width/3;
						   sprite[VG_INTRO_DOG1].type = FE_NON;
					   }
					   else
						   Set_Sprite(2, 33, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Looking for Charlie anim...
				   }
				   if(VG_2_CHARACTER == VG_MINSO)
				   {
					   Set_Sprite(VG_INTRO_DOG2, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Intro anim...
					   sprite[VG_INTRO_DOG2].x = sprite[3].x + sprite[3].width/3;
					   sprite[VG_INTRO_DOG2].type = FE_FLIP;
				   }
			   } 

			   // RESIZE PLAYER SPRITES... 
			    
			   VG_Resize_Sprite(2);
			   VG_Resize_Sprite(3);



		   }  // title_sequence == 0  
    
		   if(VG_SURVIVAL == true) 
		       VG_1_SURVIVAL_HEALTH = VG_1_HEALTH;   
		     
			mid_x = sprite[2].x + sprite[2].width/2;    
			tar_x = sprite[3].x + sprite[3].width/2;  

			distance = Node_Distance1(mid_x, VG_START_Y, tar_x, VG_START_Y);

			org_zoom_scroll_amount = -0.65f + distance;  
			  
			if(RENDERER == RENDER_OPENGL)         
			    org_zoom_scroll_amount /= 13;          
			if(RENDERER == RENDER_DIRECTX)          
			    org_zoom_scroll_amount /= 13;     
			    
			if(org_zoom_scroll_amount > 0.0f)    
			{   
				if(screen_mode == SCREEN_169_WIDESCREEN)
			        sprite[4].y = sprite[1].y - 0.005f - (org_zoom_scroll_amount/1.35f);
				if(screen_mode == SCREEN_1610_WIDESCREEN)
			        sprite[4].y = sprite[1].y - 0.005f - (org_zoom_scroll_amount/1.35f);
			}
			else
				sprite[4].y = sprite[1].y - 0.005f; 
			  
			   
		   // Update player1 debug timer...
		//   sprintf( new_counter[3].word, "VG_P2_AI_THROW_KEY %i", VG_P2_AI_THROW_KEY);
		    
		   // Intro anims... 
		   if(VG_SKIP_INTRO == false)
		   if(VG_intro_sequence == 0)  
		   if((int)TimerGetTime() > VG_intro_timer) 
		   {

			   Set_Sprite(2, 41, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Intro anim...
			   Set_Sprite(3, 41, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Intro anim...

			   if(VG_1_CHARACTER == VG_MINSO)
			   if(VG_1_EQUIPMENT != EQUIPMENT_ALL && VG_ROUND_CONDITIONS != CONDITION_BASIC_BOTH)
				   Set_Sprite(2, 33, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Intro anim...

			   VG_intro_timer = (int)TimerGetTime() + 1000;
			   VG_intro_sequence++; 
		   }   

		   // Intro..
		   // Make dogs run off screen... 
		   if(VG_SKIP_INTRO == false)
		   if(VG_intro_sequence <= 1)  
		   if((int)TimerGetTime() > VG_dog_timer) 
		   if(VG_INTRO_DOG1 > 0 && VG_INTRO_DOG1 < TOTAL_NO_SPRITES)
		   if(VG_INTRO_DOG2 > 0 && VG_INTRO_DOG2 < TOTAL_NO_SPRITES)
		   if(VG_slowmof != 0.0f)
		   {
			   if(VG_1_CHARACTER == VG_MINSO)
			   {
				    sprite[VG_INTRO_DOG1].type = FE_FLIP;
					Set_Sprite(VG_INTRO_DOG1, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Intro anim...

					if(VG_slowmof > 0.0f)
						temp_speed = ((0.00150f/VG_slowmof)*(float)f_rate); // 00400f

					sprite[VG_INTRO_DOG1].x -= temp_speed;
					sprite[VG_INTRO_DOG1].w -= temp_speed; 
			   }
			   if(VG_2_CHARACTER == VG_MINSO)
			   {
				    sprite[VG_INTRO_DOG2].type = FE_NON;
					Set_Sprite(VG_INTRO_DOG2, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Intro anim...

					if(VG_slowmof > 0.0f)
						temp_speed = ((0.00150f/VG_slowmof)*(float)f_rate); // 00400f

					sprite[VG_INTRO_DOG2].x += temp_speed;
					sprite[VG_INTRO_DOG2].w += temp_speed; 
			   }
			   
		   } 
		   // Intro anims... 
		   if(VG_SKIP_INTRO == false)
		   if(VG_intro_sequence == 1) 
		   if((int)TimerGetTime() > VG_intro_timer) 
		   {

			   // If intro anim finished go to intro anim...
			   if(sprite[2].anim_state == WAIT)
				  Set_Sprite(2, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Intro anim...
			   if(sprite[3].anim_state == WAIT)
			      Set_Sprite(3, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Intro anim...

			   if(sprite[2].anim == 0 && sprite[3].anim == 0)
			   VG_intro_sequence++;
		   }

		   // Calculate combos...
		   if(VG_1_hits_timer != 0)
		   if((int)TimerGetTime() > VG_1_hits_timer) 
		   {
			   if(VG_1_hits >= 2) 
			   {
				   VG_1_hits_total = VG_1_hits; 

				   VG_1_hits_timer = 0;   
				   VG_1_display_hit = true;

				   if(VG_1_hits >= 17)      
					   VG_1_hits = 17;

				   if((VG_1_hits-2) >= 0)
					   Set_Sprite(15, (VG_1_hits-2), LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Fight...

				   #if IS_FULL_STEAM == 1 
				   if(STEAM_ACTIVE == true)
				   if(VG_GAME_MODE == VG_ARCADE_MODE)
				   if(VG_STEAM_DEMO == 0)
				   if(VG_1_hits >= 4)
				   {
					   platform_unlock_achievement(8); // Beat training mode...
				   }
				   #endif

				   VG_1_hits = 0;
			   } 
			   else
			       VG_1_hits = 0;
		   }
		   if(VG_2_hits_timer != 0)
		   if((int)TimerGetTime() > VG_2_hits_timer) 
		   {
			   if(VG_2_hits >= 2)
			   {
				   VG_2_hits_total = VG_2_hits;

				   VG_2_hits_timer = 0;
				   VG_2_display_hit = true;

				   if(VG_2_hits >= 17)
					   VG_2_hits = 17;

				   if((VG_2_hits-2) >= 0)
					   Set_Sprite(16, (VG_2_hits-2), LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Fight...

				   VG_2_hits = 0;
			   }
			   else
			       VG_2_hits = 0;
		   }

		   // Combo hits...
		   if(VG_1_display_hit == false)
		   if((int)TimerGetTime() > VG_1_display_hit_timer)
		   {
			   hud[15].alpha = 0.0f;
			   hud[15].x = hud[15].mov_x;
		   }
		   // Combo hits...
		   if(VG_1_display_hit == true)      
		   {       
			    hud[15].alpha = 1.0f;    
				   
				temp_speed = (0.0010f)*(float)f_rate;

				if(hud[15].x < hud[15].mov_x + (hud[15].width*0.75f))
					temp_speed = (0.0020f)*(float)f_rate;  

				hud[15].x += temp_speed;  

				if(hud[15].x >= hud[15].mov_x + (hud[15].width*1.5f))
				{

					if(VG_1_hits_total == 2) 
					{
						rnd = rand()%3;
						if(rnd == 0)
							VG_alright_sfx = true;
						if(rnd == 1)
							VG_nice_sfx = true;
						if(rnd == 2)
							VG_okay_sfx = true;
					}
					if(VG_1_hits_total == 3)  
						VG_good_sfx = true;   
					if(VG_1_hits_total == 4) 
						VG_great_sfx = true;
					if(VG_1_hits_total == 5) 
						VG_excellent_sfx = true; 
					if(VG_1_hits_total == 6) 
						VG_excellent_sfx = true; 
					if(VG_1_hits_total >= 7) 
						vg_perfect_sfx = true;

					hud[15].x = hud[15].mov_x + (hud[15].width*1.5f);
					VG_1_display_hit = false;
					VG_1_display_hit_timer = (int)TimerGetTime() + 1000;
				}

		   } 

		   // Combo hits...
		   if(VG_2_display_hit == false)
		   if((int)TimerGetTime() > VG_2_display_hit_timer)
		   {
			   hud[16].alpha = 0.0f;
			   hud[16].x = hud[16].mov_x;
		   }
		   // Combo hits...   
		   if(VG_2_display_hit == true)      
		   {          
			    hud[16].alpha = 1.0f;   
				   
				temp_speed = (0.0010f)*(float)f_rate;

				if(hud[16].x > hud[16].mov_x - (hud[16].width*0.75f))
					temp_speed = (0.0020f)*(float)f_rate;   
				 
				hud[16].x -= temp_speed;  

				if(hud[16].x <= hud[16].mov_x - (hud[16].width*1.5f))
				{
					if(VG_AI_active == false)
					{ 
						if(VG_2_hits_total == 2) 
						{
							rnd = rand()%3;
							if(rnd == 0)
								VG_alright_sfx = true;
							if(rnd == 1)
								VG_nice_sfx = true;
							if(rnd == 2)
								VG_okay_sfx = true;
						}
						if(VG_2_hits_total == 3) 
							VG_good_sfx = true;
						if(VG_2_hits_total == 4) 
							VG_great_sfx = true;
						if(VG_2_hits_total == 5) 
							VG_excellent_sfx = true;
						if(VG_2_hits_total == 6) 
							VG_excellent_sfx = true; 
						if(VG_2_hits_total >= 7) 
							vg_perfect_sfx = true;
					}

					hud[16].x = hud[16].mov_x - (hud[16].width*1.5f);
					VG_2_display_hit = false;
					VG_2_display_hit_timer = (int)TimerGetTime() + 1000;
				}  
				 
		   }  

		   if(VG_GAME_MODE == VG_STORY_MODE)
		   if(VG_ROUND == 1)
		   if(VG_displayed_story_help == false)
		   if((int)TimerGetTime() > story_help_timer)
		   {
				VG_STORY_PAUSE = true;
				VG_displayed_story_help = true;
		   }

		   if(title_sequence == 1)     
		   if((int)TimerGetTime() > title_timer)  
		   {
			   if(VG_slowmof > 0.0f)
				   temp_speed = (0.0018f/VG_slowmof)*(float)f_rate;
			     
			   hud[10].x += temp_speed;  
			   hud[11].x -= temp_speed;     

			   if(hud[10].x >= hud[10].mov_x)   
			   {    
				   hud[10].x = hud[10].mov_x;
				   hud[11].x = hud[11].mov_x;  

				   hud[10].flash_target = true; 
				   hud[10].flash_timer = (int)TimerGetTime() + 15;
				   hud[11].flash_target = true; 
				   hud[11].flash_timer = (int)TimerGetTime() + 15;

				   hud[10].bump_this = true; 
				   hud[10].bump_this_timer = (int)TimerGetTime() + 35; 
				   hud[11].bump_this = true; 
				   hud[11].bump_this_timer = (int)TimerGetTime() + 35; 

				   vg_round_sfx = true;

				   title_timer = (int)TimerGetTime() + 750;
				   title_sequence++;
			   }
			    
		   }
		   if(title_sequence == 2)        
		   if((int)TimerGetTime() > title_timer)   
		   {  
				hud[10].flash_target = true; 
				hud[10].flash_timer = (int)TimerGetTime() + 15;
				hud[11].flash_target = true; 
				hud[11].flash_timer = (int)TimerGetTime() + 15;

				hud[10].bump_this = true; 
				hud[10].bump_this_timer = (int)TimerGetTime() + 35; 
				hud[11].bump_this = true; 
				hud[11].bump_this_timer = (int)TimerGetTime() + 35; 

			   	title_timer = (int)TimerGetTime() + 750;
			    title_sequence++;    
		   }	   
		   if(title_sequence == 3)         
		   if((int)TimerGetTime() > title_timer)   
		   {  
			    VG_AI_SPECIALS_TIMER = (int)TimerGetTime() + 2000;

			    VG_1_Moves_count = 0; 
			    VG_2_Moves_count = 0; 
			    VG_1_MovesList_count = 0;  
			    VG_2_MovesList_count = 0;

			    vg_fight_sfx = true;
			    Set_Sprite(10, 8, PLAY, ANIM_HUD, ANIM_NOT_WALKING); // Fight...

				hud[10].width += 0.26f;
				hud[10].height += 0.20f;

				hud[10].x -= 0.13f;
				hud[10].y -= 0.10f;

				hud[10].bump_this = true; 
				hud[10].bump_this_timer = (int)TimerGetTime() + 35; 

				hud[11].alpha = 0.0f;
			   	title_timer = (int)TimerGetTime() + 1000;
			    title_sequence++;   


		   }	 
		   if(title_sequence >= 5)      
		   { 
			   Set_Sprite(10, 9, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Fight...

			   if(hud[10].width > 0.0001f)   
			   {
				   temp_speed = (0.003f/VG_slowmof)*(float)f_rate;

				   hud[10].width -= temp_speed;
				   hud[10].x += temp_speed/2; 

				   temp_speed = (0.0015f/VG_slowmof)*(float)f_rate;

				   hud[10].height -= temp_speed;
				   hud[10].y += temp_speed/2;
			   }
			   else
				   hud[10].alpha = 0.0f;



		  /* 	   temp_speed = (0.002f/VG_slowmof)*(float)f_rate;

			   hud[12].y += temp_speed;    
			   hud[13].y -= temp_speed; */
		   }   

		   if(title_sequence == 4)      
		   if((int)TimerGetTime() > title_timer)
		   {  
			//    hud[10].alpha = 0.0f;
				hud[11].alpha = 0.0f;

				if(VG_INTRO_DOG1 > 0 && VG_INTRO_DOG1 < TOTAL_NO_SPRITES)
				if(VG_INTRO_DOG2 > 0 && VG_INTRO_DOG2 < TOTAL_NO_SPRITES)
				{
					diffX = sprite[VG_INTRO_DOG1].w - sprite[VG_INTRO_DOG1].x;
				    sprite[VG_INTRO_DOG1].x = sprite[VG_SCROLL_INDEX+7].x - (sprite[VG_INTRO_DOG1].width);
					sprite[VG_INTRO_DOG1].w = sprite[VG_INTRO_DOG1].x + diffX;

					diffX = sprite[VG_INTRO_DOG2].w - sprite[VG_INTRO_DOG2].x;
					sprite[VG_INTRO_DOG2].x = sprite[VG_SCROLL_INDEX+7].x + (sprite[VG_SCROLL_INDEX+7].width);
					sprite[VG_INTRO_DOG2].w = sprite[VG_INTRO_DOG2].x + diffX;
				}

				VG_HEALTH_LOADING = false; 

				VG_1_NEWHEALTH = (float)VG_1_HEALTH;
				VG_2_NEWHEALTH = (float)VG_2_HEALTH;

			    VG_finished_round = false;

			   if(VG_ROUND_CONDITIONS == CONDITION_MUST_ARREST && VG_1_WINS >= 1)
					New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 2, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // FX_VG_ATTACH
			   if(VG_ROUND_CONDITIONS == CONDITION_MUST_WASTE && VG_1_WINS >= 1)
					New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 4, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // FX_VG_ATTACH

			   if(VG_ROUND_CONDITIONS == CONDITION_THROWS_ONLY)
			   if(VG_1_CHARACTER == VG_GYEONG || VG_1_CHARACTER == VG_SIU || VG_1_CHARACTER == VG_MINSO || VG_1_CHARACTER == VG_REESE || VG_1_CHARACTER == VG_SANG || VG_1_CHARACTER == VG_TRAINER)
					New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 2, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // FX_VG_ATTACH
			   else
					New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 4, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // FX_VG_ATTACH

			   if(VG_ROUND_CONDITIONS == CONDITION_SURVIVE)
					New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 5, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // AVOID

			   if(VG_ROUND_CONDITIONS == CONDITION_SPECIAL1_ONLY)   
			   { 
				   if(VG_1_CHARACTER == VG_MINSO)
				       New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 6, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // TAZER
				   if(VG_1_CHARACTER == VG_GYEONG)
				       New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 10, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // DASH
				   if(VG_1_CHARACTER == VG_REESE)
				       New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 13, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // STRETCH
				   if(VG_1_CHARACTER == VG_GUN)
				       New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 10, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // DASH
				   if(VG_1_CHARACTER == VG_KENNEDY)
				       New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 10, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // DASH
			   }

			   if(VG_ROUND_CONDITIONS == CONDITION_SPECIAL2_ONLY) 
			   {
				   if(VG_1_CHARACTER == VG_GYEONG)
				       New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 7, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // SHOOT
				   if(VG_1_CHARACTER == VG_YOHAN)
				       New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 14, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // ACID
				   if(VG_1_CHARACTER == VG_JAE)
				       New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 7, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // SHOOT
				   if(VG_1_CHARACTER == VG_HYUK)
				       New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 7, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // SHOOT

			   }

			   if(VG_ROUND_CONDITIONS == CONDITION_COMBO_ONLY)
					New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 8, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // COMBO

			   if(VG_ROUND_CONDITIONS == CONDITION_PIGEON_ONLY)
					New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 11, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // PIGEON

			   if(VG_ROUND_CONDITIONS == CONDITION_PISTOL_ONLY)
					New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 7, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // SHOOT

			   if(VG_ROUND_CONDITIONS == CONDITION_ELECTRIC_ONLY)
					New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 12, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // ELECTRIC

			   if(VG_ROUND_CONDITIONS == CONDITION_MINE_ONLY)
					New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 15, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // MINE

			   if(VG_ROUND_CONDITIONS == CONDITION_BREAKDANCE_ONLY)
					New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 16, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // MINE

			   if(VG_ROUND_CONDITIONS == CONDITION_CLOTHESLINE_ONLY)
					New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 16, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // MINE

			   if(VG_ROUND_CONDITIONS == CONDITION_GRENADES_ONLY)
					New_FX(sprite[3].x+0.1f, sprite[3].y+0.3f, sprite[3].x+0.1f, sprite[3].y+0.3f, 17, LOOP, sprite[3].width/2,sprite[3].height/2, sprite[3].width/2,sprite[3].height/2, 2, GFX, 1.0f, 0, -1, FX_VG_ATTACH_HANDCUFFS, 3, 28, 0, 0, 3); // MINE

			    
			   	title_timer = (int)TimerGetTime() + 4000;
			    title_sequence++;   
		   }	 
		   if(title_sequence == 10)            
		   {  
			   	title_timer = (int)TimerGetTime() + 2500;
			    title_sequence++;   
		   }
		   if(title_sequence == 11)    
		   if((int)TimerGetTime() > title_timer)  
		   {     
				      
				VG_displaying_win = true;    

				// Need to turn off arm sprite here...
				for(int i=0;i<no_fx;i++) 
				{ 
					if(Fx[i].sector == FX_ARM || Fx[i].sector == FX_FLAME)
					{
						Fx[i].turn_off = true;
					}
				}

				// Time out...  
				if(VG_ROUND_CONDITIONS != CONDITION_TIMED_BASIC 
				&& VG_ROUND_CONDITIONS != CONDITION_TIMED
				&& VG_ROUND_CONDITIONS != CONDITION_SURVIVE)
				if(VG_TIME == 0) 
				{
					 
					if(VG_1_HEALTH < VG_2_HEALTH)  
					{
						if(sprite[3].jumping == false && sprite[3].knockdown == false && sprite[3].status != VG_KNOCKSLIDE_FONT && sprite[3].status != VG_RELOAD_FONT)
						{
						//	VG_Reset_Player(3);
							Set_Sprite(3, 42, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P2 Winning anim...
							sprite[3].strafe = false;
							sprite[3].spin_strafe = false;
						}
						if(sprite[2].jumping == false && sprite[2].knockdown == false && sprite[2].status != VG_KNOCKSLIDE_FONT && sprite[2].status != VG_RELOAD_FONT)
						{
						//	VG_Reset_Player(2);
							Set_Sprite(2, 65, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P1 fail anim...
							sprite[2].strafe = false;
							sprite[2].spin_strafe = false;
						}
						 
						VG_1_DEFEATED = true; 
						VG_2_DEFEATED = false; 
					}

					if(VG_1_HEALTH > VG_2_HEALTH)
					{
						if(sprite[2].jumping == false && sprite[2].knockdown == false && sprite[2].status != VG_KNOCKSLIDE_FONT && sprite[2].status != VG_RELOAD_FONT)
						{
						//	VG_Reset_Player(2);
							Set_Sprite(2, 42, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P1 Winning anim...
							sprite[2].strafe = false;
							sprite[2].spin_strafe = false;
						}
						if(sprite[3].jumping == false && sprite[3].knockdown == false && sprite[3].status != VG_KNOCKSLIDE_FONT && sprite[3].status != VG_RELOAD_FONT)
						{
						//	VG_Reset_Player(3);
							Set_Sprite(3, 65, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P2 Fail anim...
							sprite[3].strafe = false;
							sprite[3].spin_strafe = false;
						}

						VG_1_DEFEATED = false;
						VG_2_DEFEATED = true;
					}

					if(VG_1_HEALTH == VG_2_HEALTH)
					{
						if(sprite[2].jumping == false && sprite[2].knockdown == false && sprite[2].status != VG_KNOCKSLIDE_FONT && sprite[2].status != VG_RELOAD_FONT)
						{
						//	VG_Reset_Player(2);
							Set_Sprite(2, 65, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P1 Fail anim...
							sprite[2].strafe = false;
							sprite[2].spin_strafe = false;
						}
						if(sprite[3].jumping == false && sprite[3].knockdown == false && sprite[3].status != VG_KNOCKSLIDE_FONT && sprite[3].status != VG_RELOAD_FONT)
						{
						//	VG_Reset_Player(3);
							Set_Sprite(3, 65, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P2 Fail anim...
							sprite[3].strafe = false;
							sprite[3].spin_strafe = false;
						}

						VG_1_DEFEATED = false;
						VG_2_DEFEATED = false;
					} 

					// If time runs out on an arrest condition, last round...
					if((VG_ROUND_CONDITIONS == CONDITION_MUST_ARREST || VG_ROUND_CONDITIONS == CONDITION_MUST_WASTE)  
					&& VG_1_WINS == 1) 
					{
						if(sprite[3].handcuffed == true || sprite[3].dizzy == true)
						{
							if(sprite[2].jumping == false && sprite[2].knockdown == false && sprite[2].status != VG_KNOCKSLIDE_FONT && sprite[2].status != VG_RELOAD_FONT)
							{
							//	VG_Reset_Player(2);
								Set_Sprite(2, 42, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P1 Winning anim...
								sprite[2].strafe = false;
								sprite[2].spin_strafe = false;
							}
						}
						else
						{
							if(sprite[2].jumping == false && sprite[2].knockdown == false && sprite[2].status != VG_KNOCKSLIDE_FONT && sprite[2].status != VG_RELOAD_FONT)
							{
							//	VG_Reset_Player(2);
								Set_Sprite(2, 65, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P1 Fail anim...
								sprite[2].strafe = false;
								sprite[2].spin_strafe = false;
							}
						}
					}  
					 
				}

				if(title_sequence == 11) 
				if(VG_ROUND_CONDITIONS == CONDITION_TIMED_BASIC || VG_ROUND_CONDITIONS == CONDITION_TIMED)
				if(VG_TIME == 0)
				{
					VG_1_DEFEATED = true;
					VG_ROUND = 3; 
					VG_2_WINS = 1;

					if(sprite[2].jumping == false && sprite[2].knockdown == false && sprite[2].status != VG_KNOCKSLIDE_FONT && sprite[2].status != VG_RELOAD_FONT)
					{
					//	VG_Reset_Player(2);
						Set_Sprite(2, 65, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P1 fail anim...
						sprite[2].strafe = false;
						sprite[2].spin_strafe = false;
					}
					if(sprite[3].jumping == false && sprite[3].knockdown == false && sprite[3].status != VG_KNOCKSLIDE_FONT && sprite[3].status != VG_RELOAD_FONT)
					{
					//	VG_Reset_Player(3);
						Set_Sprite(3, 42, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P2 Winning anim...
						sprite[3].strafe = false;
						sprite[3].spin_strafe = false;
					}
				}

				if(title_sequence == 11) 
				if(VG_ROUND_CONDITIONS == CONDITION_SURVIVE)
				if(VG_TIME == 0)
				{
					VG_1_DEFEATED = false;
					VG_2_DEFEATED = true;
					VG_ROUND = 3; 
					VG_1_WINS = 1;

					if(sprite[3].jumping == false && sprite[3].knockdown == false && sprite[3].status != VG_KNOCKSLIDE_FONT && sprite[3].status != VG_RELOAD_FONT)
					{
					//	VG_Reset_Player(3);
						Set_Sprite(3, 65, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P2 fail anim...
						sprite[3].strafe = false;
						sprite[3].spin_strafe = false;
					}
					if(sprite[2].jumping == false && sprite[2].knockdown == false && sprite[2].status != VG_KNOCKSLIDE_FONT && sprite[2].status != VG_RELOAD_FONT)
					{
					//	VG_Reset_Player(2);
						Set_Sprite(2, 42, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P1 Winning anim...
						sprite[2].strafe = false;
						sprite[2].spin_strafe = false;
					}
				}
				else
				{
					VG_1_DEFEATED = true;
					VG_2_DEFEATED = false;
					VG_ROUND = 3;
					VG_2_WINS = 1;

					if(sprite[3].jumping == false && sprite[3].knockdown == false && sprite[3].status != VG_KNOCKSLIDE_FONT && sprite[3].status != VG_RELOAD_FONT)
					{
					//	VG_Reset_Player(3);
						Set_Sprite(3, 42, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P2 Winning anim...
						sprite[3].strafe = false;
						sprite[3].spin_strafe = false;
					}
				}

				if(title_sequence == 11) 
				if(VG_TIME != 0)
				if(VG_1_DEFEATED == true)
				{

					if(sprite[3].jumping == false && sprite[3].knockdown == false && sprite[3].status != VG_KNOCKSLIDE_FONT && sprite[3].status != VG_RELOAD_FONT)
					{
					//	VG_Reset_Player(3);
						Set_Sprite(3, 42, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Winning anim...
						sprite[3].strafe = false;
						sprite[3].spin_strafe = false;
					}
				} 

				if(title_sequence == 11) 
				if(VG_TIME != 0)
				if(VG_2_DEFEATED == true)   
				{ 

					if((VG_ROUND_CONDITIONS == CONDITION_MUST_ARREST || VG_ROUND_CONDITIONS == CONDITION_MUST_WASTE)  
					&& VG_1_WINS == 1)   
					{
						if(sprite[3].handcuffed == true || sprite[3].dizzy == true)
						{
							if(sprite[2].jumping == false && sprite[2].knockdown == false && sprite[2].status != VG_KNOCKSLIDE_FONT && sprite[2].status != VG_RELOAD_FONT)
							{
							//	VG_Reset_Player(2);
								Set_Sprite(2, 42, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P1 Winning anim...
								sprite[2].strafe = false;
								sprite[2].spin_strafe = false;
							}
						}
						else
						{
							if(sprite[2].jumping == false && sprite[2].knockdown == false && sprite[2].status != VG_KNOCKSLIDE_FONT && sprite[2].status != VG_RELOAD_FONT)
							{
							//	VG_Reset_Player(2);
								Set_Sprite(2, 65, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P1 Fail anim...
								sprite[2].strafe = false;
								sprite[2].spin_strafe = false;
							}
						}
					}
					else
					{
						if(sprite[2].jumping == false && sprite[2].knockdown == false && sprite[2].status != VG_KNOCKSLIDE_FONT && sprite[2].status != VG_RELOAD_FONT)
						{
						//	VG_Reset_Player(2);
							Set_Sprite(2, 42, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // P1 Winning anim...
							sprite[2].strafe = false;
							sprite[2].spin_strafe = false;
						}
					}
				}  

				// Both players died... 
				if(title_sequence == 11)
				if(VG_1_HEALTH <= 0 && VG_2_HEALTH <= 0) 
				if(sprite[2].anim_state == WAIT && sprite[3].anim_state == WAIT)
				{

					VG_voice_delay = (int)TimerGetTime() + 700;

			   		title_timer = (int)TimerGetTime() + 300;
					title_sequence++;   
				} 
				 
				if(title_sequence == 11)
				if(sprite[2].jumping == false && sprite[2].knockdown == false && sprite[2].status != VG_KNOCKSLIDE_FONT && sprite[2].status != VG_RELOAD_FONT)
				if(sprite[3].jumping == false && sprite[3].knockdown == false && sprite[3].status != VG_KNOCKSLIDE_FONT && sprite[3].status != VG_RELOAD_FONT)
			//	if(sprite[2].status == -1 && sprite[3].status == -1)
				if( (sprite[3].anim == 42 || sprite[3].anim == 65)
				|| (sprite[2].anim == 42 || sprite[2].anim == 65))
				{

				/*	sprite[2].strafe = false;
					sprite[2].spin_strafe = false;
					sprite[3].strafe = false;
					sprite[3].spin_strafe = false;*/

					if(VG_TRAINING == false)
					if(VG_1_DEFEATED == false && VG_2_DEFEATED == true)
					{
						   #if IS_FULL_STEAM == 1 
						   if(STEAM_ACTIVE == true)
						   if(VG_GAME_MODE == VG_ARCADE_MODE)
						   if(VG_STEAM_DEMO == 0)
						   if(VG_TIME >= 90)
						   {
							   platform_unlock_achievement(9); // 10 seconds...
						   }
						   #endif
					}

					VG_voice_delay = (int)TimerGetTime() + 700;

			   		title_timer = (int)TimerGetTime() + 300;
					title_sequence++;    
				} 

		   } 
		   if(VG_voice_delay != -1)
		   if((int)TimerGetTime() > VG_voice_delay)
		   {
			    if(!(VG_1_DEFEATED == false && VG_2_DEFEATED == false))
				if(VG_1_DEFEATED == true)
				{
					if(!(VG_2_CHARACTER == VG_MINSO && VG_IS_AN_ALTER == true))  
					    VG_victory_sfx = VG_2_CHARACTER;
				}
				else
				{ 
					if(!(VG_1_CHARACTER == VG_MINSO && VG_IS_AN_ALTER_P1 == true)) // I'm Mia...
					    VG_victory_sfx = VG_1_CHARACTER;
				}

				VG_voice_delay = -1;
		   }
		   if(title_sequence == 12)  
		   if((int)TimerGetTime() > title_timer) 
		   {     

			    hud[14].alpha = 1.0f; // Win/lose... 
				hud[14].flash_target = false;

				hud[14].bump_this = true; 
				hud[14].bump_this_timer = (int)TimerGetTime() + 35; 

				VG_SLOWMO = false;   
				VG_slowmof = 1.0f; 
				VG_Reset_all_anims();

			//	VG_SlowMO(6000, 0.8f);

				if(VG_2_DEFEATED == true) // VG_1_HEALTH > VG_2_HEALTH
				{
					VG_1_WINS++; 
					VG_PLAYER1_WON = true;   

					VG_flash_win_player = 1;   
					VG_flash_win_timer = 0;
					VG_flash_win_timer_total = (int)TimerGetTime() + 600;

					VG_1_perfect_count++; 
					VG_1_arrests_count++; 

					vg_win_sfx = true;
					Set_Sprite(14, 0, PLAY, ANIM_HUD, ANIM_NOT_WALKING); // Win...

					if(VG_SURVIVAL == true)
					if(VG_1_WINS == 1)
					{  
						VG_SURVIVAL_WINS++;

						#if IS_FULL_STEAM == 1 
						if(STEAM_ACTIVE == true)
						if(VG_SURVIVAL_WINS == 4)
						if(VG_STEAM_DEMO == 0)
						{
							platform_unlock_achievement(11);
						}
						#endif

						vg_titleselect_sfx = true;

						VG_flash_survive_timer = (int)TimerGetTime() + 1000;
						VG_flash_survive_local_timer = 0;
						VG_flash_survive = false;

						if(VG_SURVIVAL_WINS <= 9)
							sprintf( new_counter[3].word, "WINS 0%i", VG_SURVIVAL_WINS);
						else
							sprintf( new_counter[3].word, "WINS %i", VG_SURVIVAL_WINS);
					}

				}
				if(VG_1_DEFEATED == true) // VG_1_HEALTH < VG_2_HEALTH  
				{
					VG_2_WINS++; 
					VG_PLAYER1_WON = false;

					VG_flash_win_player = 2;
					VG_flash_win_timer = 0;
					VG_flash_win_timer_total = (int)TimerGetTime() + 600;

					VG_2_perfect_count++;
					VG_2_arrests_count++; 

					if(VG_SURVIVAL == true)
						VG_2_WINS = 2;

					vg_lose_sfx = true; 
					Set_Sprite(14, 1, PLAY, ANIM_HUD, ANIM_NOT_WALKING); // Lose...
				}
				if(VG_1_DEFEATED == false && VG_2_DEFEATED == false) // VG_1_HEALTH == VG_2_HEALTH
				{
					Set_Sprite(14, 2, PLAY, ANIM_HUD, ANIM_NOT_WALKING); // Draw...
				}

				if(VG_1_HEALTH == VG_1_TOTALHEALTH || VG_2_HEALTH == VG_2_TOTALHEALTH)
			   		title_timer = (int)TimerGetTime() + 1500;
				else  
			   		title_timer = (int)TimerGetTime() + 1500; 
				  
			    title_sequence++;    
				 
		   }   
		   if(title_sequence == 13)            
		   if((int)TimerGetTime() > title_timer)      
		   {    

				if((VG_1_HEALTH == VG_1_TOTALHEALTH || VG_2_HEALTH == VG_2_TOTALHEALTH) && VG_TIME != 0)
				{
					VG_SLOWMO = false; 
					VG_slowmof = 1.0f;
					VG_Reset_all_anims();
					hud[14].alpha = 1.0f; // Perfect...

					hud[14].bump_this = true; 
					hud[14].bump_this_timer = (int)TimerGetTime() + 35; 

					hud[14].flash_target = true; 
					hud[14].flash_timer = (int)TimerGetTime() + 15;

					title_sequence=15;   
					title_timer = 0;   
				} 
				else 
				{ 
					VG_SLOWMO = false; 
					VG_slowmof = 1.0f;
					VG_Reset_all_anims();
					hud[14].alpha = 0.0f; // Win/lose... 

					hud[14].bump_this = true; 
					hud[14].bump_this_timer = (int)TimerGetTime() + 35; 

					hud[14].flash_target = true; 
					hud[14].flash_timer = (int)TimerGetTime() + 15;

			   		title_timer = (int)TimerGetTime() + 1000;
					title_sequence++;    
				}
				// Do arrested-wasted code.. 
				if(VG_1_WINS == 2) 
				if(!(VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_DUELLING))
				if(sprite[3].handcuffed == true 
				|| sprite[3].dizzy == true
				|| sprite[3].sticky == true
				|| VG_2_DEFEATED_BY_BOMB == true
				)
				{

					if(VG_1_WINS == 2)
					{
						VG_1_Temp_arrests++;
						if(VG_1_arrests_count >= 0 && VG_1_arrests_count < 10)
							VG_1_arrests[VG_1_arrests_count] = 1; 
					}
					if(VG_2_WINS == 2)
					{ 
						VG_2_Temp_arrests++;
						if(VG_2_arrests_count >= 0 && VG_2_arrests_count < 10)
							VG_2_arrests[VG_2_arrests_count] = 1; 
					}

					VG_SLOWMO = false; 
					VG_slowmof = 1.0f;

					VG_Reset_all_anims();

					hud[14].alpha = 1.0f; 

					hud[14].bump_this = true; 
					hud[14].bump_this_timer = (int)TimerGetTime() + 35; 

					hud[14].flash_target = true; 
					hud[14].flash_timer = (int)TimerGetTime() + 15;

					title_sequence=17;  
					title_timer = 0; 
				}				  
				// Do arrested-wasted code..
				if(VG_2_WINS == 2) 
				if(!(VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_DUELLING))
				if(sprite[2].handcuffed == true 
				|| sprite[2].dizzy == true
				|| sprite[2].sticky == true 
				|| VG_1_DEFEATED_BY_BOMB == true
				)
				{

					VG_SLOWMO = false; 
					VG_slowmof = 1.0f;
					hud[14].alpha = 1.0f; 
					
					hud[14].flash_target = true; 
					hud[14].flash_timer = (int)TimerGetTime() + 15;

					hud[14].bump_this = true; 
					hud[14].bump_this_timer = (int)TimerGetTime() + 35; 

					title_sequence=17;  
					title_timer = 0; 
				}
				   
		   }	   

		   // End scene... 
		   if(title_sequence == 14)     
		   if((int)TimerGetTime() > title_timer)  
		   {       
			    VG_ROUND++;

				if(VG_GAME_MODE == VG_VERSUS_MODE)
				if(VG_ROUND == 4 || VG_1_WINS == 2 || VG_2_WINS == 2)
				{
					if(VG_1_WINS > VG_2_WINS)
					if(VG_1_Vs_wins < 100)
						VG_1_Vs_wins++;
					if(VG_2_WINS > VG_1_WINS)
					if(VG_2_Vs_wins < 100)
						VG_2_Vs_wins++;
					if(VG_1_WINS == VG_2_WINS)
					if(VG_Vs_draws < 100)
						VG_Vs_draws++;
				} 

				if(VG_TRAINING == false)
				if(VG_1_WINS == VG_ROUND_LIMIT || VG_2_WINS == VG_ROUND_LIMIT || VG_ROUND == 7 
				|| (VG_GAME_MODE == VG_VERSUS_MODE && VG_ROUND == 4) 
				|| (VG_1_WINS == 1 && VG_SURVIVAL == true))
				{

					VG_IS_VERSUS_SCREEN = false; 
					vg_next_episode = 6;     
					vg_next_scene    = 0;  

					// Survival mode beat Sang...
					if(VG_1_WINS == 1 && VG_SURVIVAL == true)
					{
						VG_PLAYER1_WON = true;

						// Go to arcade endings...
						if(VG_2_CHARACTER == VG_SANG)
						{
							vg_next_episode = 6;    
							vg_next_scene   = 2; 
						}
					}

					if(VG_GAME_MODE == VG_ARCADE_MODE)
					if(VG_1_WINS == VG_ROUND_LIMIT)
					{
						if(VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE != VG_ARCADE_DUELLING)
						{
							VG_1_TOTAL_perfects += VG_1_Temp_perfects;
							VG_1_TOTAL_arrests += VG_1_Temp_arrests;

							VG_2_TOTAL_perfects += VG_2_Temp_perfects; 
							VG_2_TOTAL_arrests += VG_2_Temp_arrests;
						}

						// Go to arcade endings...
						if(VG_2_CHARACTER == VG_SANG)
						{
							vg_next_episode = 6;    
							vg_next_scene   = 2; 
						}
					}

					VG_1_Temp_perfects = 0;
					VG_2_Temp_perfects = 0;

					VG_1_Temp_arrests = 0;
					VG_2_Temp_arrests = 0;

				}

				if(VG_TRAINING == true)
				{ 
					if(VG_2_WINS == 1)
					{
						VG_PLAYER1_WON = false;
						VG_IS_VERSUS_SCREEN = false;
						vg_next_episode = 6;    
						vg_next_scene    = 0;  
					}
					if(VG_1_WINS == 2)
					{ 
						VG_PLAYER1_WON = true;
						VG_IS_VERSUS_SCREEN = false;
						vg_next_episode = 6;    
						vg_next_scene    = 0;     
					}
				} 
				 
				if(VG_GAME_MODE == VG_STORY_MODE)
				if(VG_1_WINS == 2 
				|| (VG_1_WINS == 1 && (VG_ROUND_CONDITIONS == CONDITION_THROWS_ONLY || VG_ROUND_CONDITIONS == CONDITION_BASIC_ONLY) ))
				{

					// Need to go to cutscene mode here...
					vg_next_episode = 6;    
					vg_next_scene    = 2;    
					
					VG_STORY_SETUP = VG_STORY_SCENE_WON;

					if(VG_ROUND_CONDITIONS == CONDITION_MUST_ARREST)
					if(vg_arrest_successful == false)
					{
						VG_STORY_SETUP = VG_STORY_SCENE_LOST;
						VG_PLAYER1_WON = false;
						VG_IS_VERSUS_SCREEN = false;
						vg_next_episode = 6;    
						vg_next_scene    = 0;
					}

					if(VG_ROUND_CONDITIONS == CONDITION_MUST_WASTE)
					if(vg_waste_successful == false)
					{
						VG_STORY_SETUP = VG_STORY_SCENE_LOST;
						VG_PLAYER1_WON = false;
						VG_IS_VERSUS_SCREEN = false;
						vg_next_episode = 6;    
						vg_next_scene    = 0;
					}

				}

			   	next_scene = true;
		   }
		   // Perfect...      
		   if(title_sequence == 15)          
		   if((int)TimerGetTime() > title_timer)   
		   {   
				if(VG_1_HEALTH == VG_1_TOTALHEALTH)
				{
					if(VG_1_perfect_count >= 0 && VG_1_perfect_count < 10)
					    VG_1_perfects[VG_1_perfect_count] = 1; 

					if(VG_GAME_MODE == VG_ARCADE_MODE)
						vg_titleselect_sfx = true;

					VG_1_Temp_perfects++;
				}

				if(VG_2_HEALTH == VG_2_TOTALHEALTH)
				{
					if(VG_2_perfect_count >= 0 && VG_2_perfect_count < 10)
					    VG_2_perfects[VG_2_perfect_count] = 1;

					VG_2_Temp_perfects++;
				}

			    hud[14].alpha = 1.0f; // Perfect...

				hud[14].bump_this = true; 
				hud[14].bump_this_timer = (int)TimerGetTime() + 35; 

			    vg_perfect_sfx = true; // Perfect sfx...
				hud[14].flash_target = true; 
				hud[14].flash_timer = (int)TimerGetTime() + 15;
			    Set_Sprite(14, 3, PLAY, ANIM_HUD, ANIM_NOT_WALKING); // Perfect...
			    title_timer = (int)TimerGetTime() + 1000;
			    title_sequence=16; 
		   } 
		   // Perfect... 
		   if(title_sequence == 16)           
		   if((int)TimerGetTime() > title_timer)    
		   {    
			    VG_SLOWMO = false;   
				VG_slowmof = 1.0f; 
				VG_Reset_all_anims();
			    hud[14].alpha = 0.0f; // Win/lose... 
			   	title_timer = (int)TimerGetTime() + 1000;
			    title_sequence=14;    
		   }	 
		   // Arrested-Wasted...        
		   if(title_sequence == 17)             
		   if((int)TimerGetTime() > title_timer)      
		   {     
			    hud[14].alpha = 1.0f; // Win/lose... 

				if(VG_1_WINS == 2)
				{
					
					if(VG_GAME_MODE == VG_ARCADE_MODE)
						vg_titleselect_sfx = true;

					vg_arrest_successful = true;
					vg_waste_successful = true; 
				}

				if(sprite[2].handcuffed == true || sprite[3].handcuffed == true)
				{
					if(VG_1_WINS == 2) 
						VG_2_WAS_ARRESTED = true;
					if(VG_2_WINS == 2)
						VG_1_WAS_ARRESTED = true;

					Set_Sprite(14, 4, PLAY, ANIM_HUD, ANIM_NOT_WALKING); // Arrested...
					VG_arrested_sfx = true;
				}
				else
				{
					Set_Sprite(14, 5, PLAY, ANIM_HUD, ANIM_NOT_WALKING); // Wasted...
					VG_wasted_sfx = true;
				}

				hud[14].flash_target = true; 
				hud[14].flash_timer = (int)TimerGetTime() + 15;

				hud[14].bump_this = true; 
				hud[14].bump_this_timer = (int)TimerGetTime() + 35; 
			    
			    title_timer = (int)TimerGetTime() + 1500;
			    title_sequence=18; 
		   } 
		   // Arrested-Wasted...     
		   if(title_sequence == 18)           
		   if((int)TimerGetTime() > title_timer)    
		   {    
			    VG_SLOWMO = false; 
				VG_slowmof = 1.0f;
				VG_Reset_all_anims();
			    hud[14].alpha = 0.0f; // Win/lose... 

				// Perfect...
				if((VG_1_HEALTH == VG_1_TOTALHEALTH || VG_2_HEALTH == VG_2_TOTALHEALTH) && VG_TIME != 0)
				{
			   		title_timer = (int)TimerGetTime() + 500;
					title_timer = 0;
					title_sequence=15; // Perfect display... 
				} 
				else
				{
			   		title_timer = (int)TimerGetTime() + 1000;
					title_sequence=14; // End scene...  
				}
		   }	

		   if(VG_BACKGROUND == VG_SHRINE || VG_BACKGROUND == VG_SAIZO)
		   if((int)TimerGetTime() > VG_RAIN_TIMER)
		   {
			    VG_RAIN_TIMER = (int)TimerGetTime() + VG_RAIN_LENGTH;

				if(VG_RAIN_SEGMENT == 0)
				{
					tar_x = sprite[1].width / 3;

					rnd = rand()%100;

					tar_x = (tar_x / 100.0f) * (float)rnd;

					mid_x = sprite[1].x + tar_x; 
					mid_y = sprite[1].y + sprite[1].height;  
				}
				if(VG_RAIN_SEGMENT == 1)
				{
					tar_x = sprite[1].width / 3;

					rnd = rand()%100;

					tar_x = (tar_x / 100.0f) * (float)rnd;

					mid_x = sprite[1].x + (sprite[1].width / 3) + tar_x; 
					mid_y = sprite[1].y + sprite[1].height;  
				}
				if(VG_RAIN_SEGMENT == 2) 
				{
					tar_x = sprite[1].width / 3;

					rnd = rand()%100; 

					tar_x = (tar_x / 100.0f) * (float)rnd;

					mid_x = sprite[1].x + ((sprite[1].width / 3)*2) + tar_x; 
					mid_y = sprite[1].y + sprite[1].height;  
				}
				 
				rnd = rand()%5;  
				 
				// Frags...
				if(rnd == 0 || rnd == 1)
					New_FX(mid_x, mid_y,  mid_x, mid_y, 0, LOOP, 0.025f, 0.025f, 0.025f, 0.025f, 1, GFX, 1.0f, 0, 1, FX_VG_RAINDROP, -1, 18, 0, 0, rnd); 
				if(rnd == 2)
					New_FX(mid_x, mid_y,  mid_x, mid_y, 0, LOOP, 0.025f, 0.025f, 0.025f, 0.025f, 3, GFX, 1.0f, 0, 1, FX_VG_RAINDROP, -1, 18, 0, 0, rnd); 
				if(rnd == 3)
					New_FX(mid_x, mid_y,  mid_x, mid_y, 0, LOOP, 0.025f, 0.025f, 0.025f, 0.025f, 3, GFX, 1.0f, 0, 1, FX_VG_RAINDROP, -1, 18, 0, 0, rnd); 
				if(rnd == 4)
					New_FX(mid_x, mid_y,  mid_x, mid_y, 0, LOOP, 0.025f, 0.025f, 0.025f, 0.025f, 5, GFX, 1.0f, 0, 1, FX_VG_RAINDROP, -1, 18, 0, 0, rnd); 


				VG_RAIN_SEGMENT++;

				if(VG_RAIN_SEGMENT >= 3)
					VG_RAIN_SEGMENT = 0;

		   }

		   if(scene == VG_MINSO)  
		   {  
		   		// Get clock offset for attaching to background...
			//	sprite[14].x = sprite[1].x + VG_clock_offset;
		   } 
		   if(scene == VG_SIU)  
		   {  
		   		// Get clock offset for attaching to background...
				sprite[15].x = sprite[1].x + VG_clock_offset;
		   } 
		   if(scene == VG_SHO)  
		   {  
		   		// Get clock offset for attaching to background...
				sprite[15].x = sprite[1].x + VG_clock_offset;
		   } 

		   // Falling suitcases.
			if(scene == VG_SHO) 
			{

				if (VG_suitcase_resetting == false)
				{
					temp_speed = ((0.0001f / VG_slowmof)*(float)f_rate);

					sprite[15].y -= temp_speed;
				}

				if (VG_suitcase_resetting == false)
				if (sprite[15].y < (sprite[1].y + sprite[1].height/10))
				{
					VG_suitcase_timer = (int)TimerGetTime() + 3000;
					VG_suitcase_resetting = true;
				}

				if(VG_suitcase_resetting == true)
				if((int)TimerGetTime() > VG_suitcase_timer)
				{
					VG_rnd =  rand()%4;
					
 				    Set_Sprite(15, VG_rnd, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Low health red bar...

					sprite[15].y = VG_suitcase_offset;
					VG_suitcase_resetting = false;
					VG_suitcase_timer = 0;
				}

			}

		   // Scroll BG cars...
		   if(scene == VG_GYEONG)  
		   {  

			   sprite[14].x = sprite[1].x + VG_clock_offset;

			   sprite[10].type = FE_FLIP;  

			   if(VG_CAR[0] == false)
			   if(sprite[8].x >= sprite[0].x + (sprite[0].width/3))
			   {
				   VG_CAR[0] = true;
				   vg_amb_car1_sfx = true;  
			   }

			   if(VG_CAR[1] == false)
			   if(sprite[9].x >= sprite[0].x + (sprite[0].width/3))
			   {
				   VG_CAR[1] = true;
				   vg_amb_car1_sfx = true;
			   }

			   if(VG_CAR[2] == false)
			   if(sprite[10].x <= sprite[0].x + (sprite[0].width - sprite[0].width/3))
			   {
				   VG_CAR[2] = true;
				   vg_amb_car2_sfx = true; 
			   }

			   if(VG_slowmof > 0.0f)
				   temp_speed = ((sprite[8].mov_x/VG_slowmof)*(float)f_rate);
			   sprite[8].x += temp_speed;

			   if(VG_slowmof > 0.0f)
			       temp_speed = ((sprite[9].mov_x/VG_slowmof)*(float)f_rate);
			   sprite[9].x += temp_speed;

			   if(sprite[8].x >= sprite[1].x + sprite[1].width)  
			   {      
				   sprite[8].x = sprite[1].x - sprite[8].width; 
				   sprite[8].mov_x = VG_Get_Speed();	
				   VG_CAR[0] = false;
			   }
			    
			   if(sprite[9].x >= sprite[1].x + sprite[1].width)
			   {
				   sprite[9].x = sprite[1].x - sprite[9].width;
				   sprite[9].mov_x = VG_Get_Speed();	
				   VG_CAR[1] = false;
			   }		     

			   if(VG_slowmof > 0.0f)
			       temp_speed = ((sprite[10].mov_x/VG_slowmof)*(float)f_rate);
			   sprite[10].x -= temp_speed; 

			   if(sprite[10].x <= sprite[1].x) 
			   {
				   sprite[10].x = sprite[1].x + sprite[1].width;
				   sprite[10].mov_x = VG_Get_Speed();
				   VG_CAR[2] = false;
			   }	
		   }

		   // Move cat on alleyway bg... 
		   if(scene == VG_GYEONG)
		   {

			   if((int)TimerGetTime() > VG_cat_AI_timer)
			   {
				   VG_cat_AI_timer = (int)TimerGetTime() + (1000 + rand()%3000);
				   VG_cat_AI = rand()%4;
			   }
			    
			   if(VG_slowmof > 0.0f)
			       temp_speed = ((0.0001f/VG_slowmof)*(float)f_rate);

			   if(VG_cat_AI == VG_CAT_IDLE || VG_cat_AI == VG_CAT_IDLE2)
				   Set_Sprite(13, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Low health red bar...

			   if(VG_cat_AI == VG_CAT_LEFT)
			   {
				   Set_Sprite(13, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Low health red bar...
				   sprite[13].x -= temp_speed;
				   if(sprite[13].x < sprite[1].x)
					   VG_cat_AI = VG_CAT_RIGHT;
			   }
			   if(VG_cat_AI == VG_CAT_RIGHT)
			   {
				   Set_Sprite(13, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Low health red bar...
				   sprite[13].x += temp_speed;
				   if(sprite[13].x > (sprite[1].x + sprite[1].width/4))
					   VG_cat_AI = VG_CAT_LEFT;
			   }

		   }

		   // Move rat on apartment bg...  
		   if(scene == VG_YOHAN)
		   {

			   if((int)TimerGetTime() > VG_cat_AI_timer)
			   {
				   VG_cat_AI_timer = (int)TimerGetTime() + (1000 + rand()%3000);
				   VG_cat_AI = rand()%4;
			   }
			    
			   if(VG_slowmof > 0.0f)
			       temp_speed = ((0.0001f/VG_slowmof)*(float)f_rate);

			   if(VG_cat_AI == VG_CAT_IDLE || VG_cat_AI == VG_CAT_IDLE2)
				   Set_Sprite(13, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Low health red bar...

			   if(VG_cat_AI == VG_CAT_LEFT)
			   {
				   Set_Sprite(13, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Low health red bar...
				   sprite[13].x -= temp_speed;
				   if(sprite[13].x < points[4].x)
					   VG_cat_AI = VG_CAT_RIGHT;
			   }
			   if(VG_cat_AI == VG_CAT_RIGHT)
			   {
				   Set_Sprite(13, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Low health red bar...
				   sprite[13].x += temp_speed;
				   if(sprite[13].x > points[5].x)
					   VG_cat_AI = VG_CAT_LEFT;
			   } 
			    
		   } 
		   if(scene == VG_MINSO)
		   {
			   if((int)TimerGetTime() > BILLBOARD_TIMER)
			   if(BILLBOARD_STATE == BILL_WAITING) 
			   {
				   BILLBOARD_STATE = BILL_MOVING;
			   } 

			   if(BILLBOARD_STATE == BILL_MOVING)   
			   { 
				   if(BILLBOARD_DIRECTION == BILL_RIGHT) 
				   {
						sprite[13].u[0] += 0.0001f * (float)f_rate; 
						sprite[13].u[1] += 0.0001f * (float)f_rate; 
						sprite[13].u[2] += 0.0001f * (float)f_rate;
						sprite[13].u[3] += 0.0001f * (float)f_rate;

						sprite[15].u[0] += 0.0002f * (float)f_rate;
						sprite[15].u[1] += 0.0002f * (float)f_rate; 
						sprite[15].u[2] += 0.0002f * (float)f_rate;
						sprite[15].u[3] += 0.0002f * (float)f_rate;

						if(sprite[13].u[0] >= 1.0f)
						{ 
							sprite[13].u[0] = 1.0f;
							sprite[13].u[1] = 0.5f; 
							sprite[13].u[2] = 0.5f;
							sprite[13].u[3] = 1.0f;

							BILLBOARD_STATE = BILL_WAITING;
							BILLBOARD_TIMER = (int)TimerGetTime() + BILLBOARD_WAIT_LENGTH;
							BILLBOARD_DIRECTION = BILL_LEFT;
						}

						if(sprite[15].u[0] >= 1.0f)
						{ 
							sprite[15].u[0] = 1.0f;
							sprite[15].u[1] = 0.5f; 
							sprite[15].u[2] = 0.5f;
							sprite[15].u[3] = 1.0f;

							BILLBOARD2_STATE = BILL_WAITING;
							BILLBOARD2_TIMER = (int)TimerGetTime() + BILLBOARD_WAIT_LENGTH;
							BILLBOARD2_DIRECTION = BILL_LEFT;
						}
				   }
				   else
				   { 
						sprite[13].u[0] -= 0.0001f * (float)f_rate;
						sprite[13].u[1] -= 0.0001f * (float)f_rate; 
						sprite[13].u[2] -= 0.0001f * (float)f_rate;
						sprite[13].u[3] -= 0.0001f * (float)f_rate;

						sprite[15].u[0] -= 0.0002f * (float)f_rate;
						sprite[15].u[1] -= 0.0002f * (float)f_rate; 
						sprite[15].u[2] -= 0.0002f * (float)f_rate;
						sprite[15].u[3] -= 0.0002f * (float)f_rate;

						if(sprite[13].u[0] <= 0.5f)
						{
							sprite[13].u[0] = 0.5f; 
							sprite[13].u[1] = 0.0f; 
							sprite[13].u[2] = 0.0f; 
							sprite[13].u[3] = 0.5f;

							BILLBOARD_STATE = BILL_WAITING;
							BILLBOARD_TIMER = (int)TimerGetTime() + BILLBOARD_WAIT_LENGTH;
							BILLBOARD_DIRECTION = BILL_RIGHT;
						}

						if(sprite[15].u[0] <= 0.5f)
						{
							sprite[15].u[0] = 0.5f; 
							sprite[15].u[1] = 0.0f; 
							sprite[15].u[2] = 0.0f;
							sprite[15].u[3] = 0.5f;

							BILLBOARD2_STATE = BILL_WAITING;
							BILLBOARD2_TIMER = (int)TimerGetTime() + BILLBOARD_WAIT_LENGTH;
							BILLBOARD2_DIRECTION = BILL_RIGHT;
						}
				   }

			   } // BILLBOARD_STATE == BILL_MOVING

		   } // scene == VG_MINSO

		   // Scroll BG train cars... 
		   if(scene == VG_SIU)
		   {
				sprite[16].u[0] += 0.0002f * (float)f_rate;
				sprite[16].u[1] += 0.0002f * (float)f_rate; 
				sprite[16].u[2] += 0.0002f * (float)f_rate;
				sprite[16].u[3] += 0.0002f * (float)f_rate;

				sprite[17].u[0] += 0.0002f * (float)f_rate;
				sprite[17].u[1] += 0.0002f * (float)f_rate; 
				sprite[17].u[2] += 0.0002f * (float)f_rate;
				sprite[17].u[3] += 0.0002f * (float)f_rate;

			   if((int)TimerGetTime() > vg_train_timer) 		 	 
			   {  


				   if(sprite[10].x == train_startX)
					   vg_amb_subway_sfx = true;

				   if(VG_slowmof > 0.0f)
					   temp_speed = ((0.001f/VG_slowmof)*(float)f_rate);

				   sprite[10].x -= temp_speed; 
				   sprite[11].x -= temp_speed; 

				   if((sprite[11].x + (sprite[11].width*3)) <= sprite[1].x) 
				   {
						sprite[10].x = train_startX; 
						sprite[11].x = train_start1X;
						vg_train_timer = (int)TimerGetTime() + (4000 + rand()%4000);
				   }	

				   // Animate platform flag/sign...
					if( (sprite[10].x <= sprite[1].x + sprite[1].width/2) && ((sprite[11].x+(sprite[11].width/4)) >= sprite[1].x) )
						Set_Sprite(14, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Low health red bar...
					else
						Set_Sprite(14, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Low health red bar...

			   }
		   }

		   // Healthbar code...

		   if(VG_1_HEALTH < 0)
			   VG_1_HEALTH = 0;  
		   if(VG_2_HEALTH < 0)  
			   VG_2_HEALTH = 0; 

			   if(VG_HEALTH_LOADING == true) 
			   if(VG_1_NEWHEALTH < (float)VG_1_HEALTH)   
			   {
			       VG_1_NEWHEALTH += (0.15f*f_rate);
				   if(((float)VG_1_HEALTH-VG_1_NEWHEALTH) > 100)
				       VG_1_NEWHEALTH += (0.18f*f_rate);
				   if(((float)VG_1_HEALTH-VG_1_NEWHEALTH) > 150)
				       VG_1_NEWHEALTH += (0.20f*f_rate);
				   if(((float)VG_1_HEALTH-VG_1_NEWHEALTH) > 200)
				       VG_1_NEWHEALTH += (0.20f*f_rate);
				   if(((float)VG_1_HEALTH-VG_1_NEWHEALTH) > 250)
				       VG_1_NEWHEALTH += (0.20f*f_rate);
			   }
			   else 
				   VG_1_NEWHEALTH = (float)VG_1_HEALTH; 

			   if(VG_HEALTH_LOADING == false) 
			   if(VG_1_NEWHEALTH > (float)VG_1_HEALTH)   
			   {
				   VG_1_NEWHEALTH -= (0.15f*f_rate); 

				   if((VG_1_NEWHEALTH-(float)VG_1_HEALTH) > 100)
				       VG_1_NEWHEALTH -= (0.25f*f_rate);
				   if((VG_1_NEWHEALTH-(float)VG_1_HEALTH) > 300)
				       VG_1_NEWHEALTH -= (0.35f*f_rate);
				         
			   }
			   else
				   VG_1_NEWHEALTH = (float)VG_1_HEALTH;
			    
			   if(VG_HEALTH_LOADING == true)   
			   if(VG_2_NEWHEALTH < (float)VG_2_HEALTH)  
			   {
			       VG_2_NEWHEALTH += (0.15f*f_rate);
				   if(((float)VG_2_HEALTH-VG_2_NEWHEALTH) > 100)
				       VG_2_NEWHEALTH += (0.18f*f_rate);
				   if(((float)VG_2_HEALTH-VG_2_NEWHEALTH) > 150)
				       VG_2_NEWHEALTH += (0.20f*f_rate);
				   if(((float)VG_2_HEALTH-VG_2_NEWHEALTH) > 200)
				       VG_2_NEWHEALTH += (0.20f*f_rate);
				   if(((float)VG_2_HEALTH-VG_2_NEWHEALTH) > 250)
				       VG_2_NEWHEALTH += (0.20f*f_rate);
			   }
			   else
				   VG_2_NEWHEALTH = (float)VG_2_HEALTH;

			   if(VG_HEALTH_LOADING == false)   
			   if(VG_2_NEWHEALTH > (float)VG_2_HEALTH)   
			   {
				   VG_2_NEWHEALTH -= (0.15f*f_rate);  

				   if((VG_2_NEWHEALTH-(float)VG_2_HEALTH) > 100)
				       VG_2_NEWHEALTH -= (0.25f*f_rate);
				   if((VG_2_NEWHEALTH-(float)VG_2_HEALTH) > 300)
				       VG_2_NEWHEALTH -= (0.35f*f_rate);
			   }
			   else
				   VG_2_NEWHEALTH = (float)VG_2_HEALTH;

		   // Healthbars... 
		   if(VG_1_TOTALHEALTH > 0) 
		   {
			   if(VG_1_TOTALHEALTH > 0)
			   {
				   hud[7].width = (hud[7].box_width / (float)VG_1_TOTALHEALTH) * VG_1_NEWHEALTH; 
				   if(hud[7].width < (hud[7].box_width / 30))
					   hud[7].width = (hud[7].box_width / 30);
			   }

			   if(VG_1_HEALTH <= 0)
				   hud[7].width = 0.0f;

		       hud[7].x = hud[7].w + ((hud[7].box_width - hud[7].width));

			   if(VG_1_NEWHEALTH < (float)(VG_1_TOTALHEALTH/4))
			   {
				   Set_Sprite(7, 1, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Low health red bar...
			   }
			   else
				   Set_Sprite(7, 0, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Low health red bar...
			    
		   } 

		   // Healthbars...  
		   if(VG_2_TOTALHEALTH > 0)
		   {
			   if(VG_2_TOTALHEALTH > 0)
			   {
			       hud[6].width = (hud[6].box_width /(float)VG_2_TOTALHEALTH) * VG_2_NEWHEALTH;
				   if(hud[6].width < (hud[6].box_width / 30))
					   hud[6].width = (hud[6].box_width / 30);
			   }

			   if(VG_2_HEALTH <= 0)
				   hud[6].width = 0.0f;

			   if(VG_2_NEWHEALTH < (float)(VG_2_TOTALHEALTH/4))
			   {
				   Set_Sprite(6, 1, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Low health red bar...
			   }
			   else
				   Set_Sprite(6, 0, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Low health red bar...
		   }

		   // Flip shake... 
		   if((int)TimerGetTime() > VG_SHAKE_timer)   
		   { 
			   VG_SHAKE_LEFT ^= 1;
			   VG_SHAKE_timer = (int)TimerGetTime()+25;
		   } 

		   // Debug moves inputted...       

		   sprintf( new_counter[5].word, " "); 

		   for(int i = 1;i<=VG_1_WINS;i++) 
		   {
			   sprintf(string_value, "ö"); // ö - Normal symbol

			   if(VG_1_arrests[i] == 1)
				   sprintf(string_value, "ã"); // ¿ - Arrest symbol 

			   if(VG_1_perfects[i] == 1)
				   sprintf(string_value, "¿"); // ¿ - Perfect symbol 

			   strcat(new_counter[5].word, string_value);
		   }
		    
		   // Debug moves inputted...       
		   sprintf( new_counter[6].word, "");  

		   for(int i = VG_2_WINS;i>=1;i--)
		   {
			   sprintf(string_value, "ö"); // ö - Normal symbol 

			   if(VG_2_arrests[i] == 1)
				   sprintf(string_value, "ã"); // ¿ - Arrest symbol 

			   if(VG_2_perfects[i] == 1)
				   sprintf(string_value, "¿"); // ¿ - Perfect symbol 

			   strcat(new_counter[6].word, string_value);
		   }

		   if(VG_flash_win_player == 0)
		   {
			   new_counter[5].alpha = 1.0f;
			   new_counter[6].alpha = 1.0f;
		   }  
		   if(VG_flash_win_player == 1)  
		   { 
			   if((int)TimerGetTime() < VG_flash_win_timer_total )
			   {
				   if((int)TimerGetTime() > VG_flash_win_timer)
				   {
					   if(new_counter[5].alpha == 1.0f)
						   new_counter[5].alpha = 0.0f; 
					   else
						   new_counter[5].alpha = 1.0f;
				     
					   VG_flash_win_timer = (int)TimerGetTime() + 75;
				   }
			   } 
			   else
				   VG_flash_win_player = 0;    
		   }
		   if(VG_flash_win_player == 2)
		   {
			   if((int)TimerGetTime() < VG_flash_win_timer_total )
			   {
				   if((int)TimerGetTime() > VG_flash_win_timer)
				   {
					   if(new_counter[6].alpha == 1.0f)
						   new_counter[6].alpha = 0.0f;
					   else
						   new_counter[6].alpha = 1.0f;

					   VG_flash_win_timer = (int)TimerGetTime() + 75;
				   }
			   } 
			   else 
				   VG_flash_win_player = 0;      
		   }
		       
		   // Debug moves inputted...        
			   sprintf( new_counter[1].word, "%s^", VG_1_NAME);    
		      
		   // Debug moves inputted...       
			   sprintf( new_counter[2].word, "%s", VG_2_NAME);     
			    
		//   sprintf( new_counter[1].word, "sprite[2].deflect:%i^sprite[3].deflect:%i", sprite[2].deflect, sprite[3].deflect);

		   if(VG_Display_moves == true)   //  || VG_TRAINING == true
		   {

		   sprintf(string_value, ""); 
    
		   display_player = 1;      
		        
		   if(display_player == 1)   
		   {
			   tmp_VG_Moves_count = VG_1_Moves_count;   

				for(int i=0;i<tmp_VG_Moves_count;i++)
				if(i < MOVES_LIMIT)
				if(VG_1_Moves[i] >= 0)
					tmp_VG_Moves[i] = VG_1_Moves[i];
		   }
		   if(display_player == 2)
		   {
			   tmp_VG_Moves_count = VG_2_Moves_count;

				for(int i=0;i<tmp_VG_Moves_count;i++)
				if(i < MOVES_LIMIT)
				if(VG_2_Moves[i] >= 0)
					tmp_VG_Moves[i] = VG_2_Moves[i];
		   }

		   if(tmp_VG_Moves_count <= 10)
		   for(int i=0;i<tmp_VG_Moves_count;i++)
		   if(i < MOVES_LIMIT)
		   if(tmp_VG_Moves[i] >= 0)
		   {
			   if(tmp_VG_Moves[i] == VG_LEFT_FONT_H)  
		   		   sprintf(string_value, "¨,"); 
			   if(tmp_VG_Moves[i] == VG_RIGHT_FONT_H)  
		   		   sprintf(string_value, "©,"); 
			   if(tmp_VG_Moves[i] == VG_UP_FONT_H)  
		   		   sprintf(string_value, "ª,"); 
			   if(tmp_VG_Moves[i] == VG_DOWN_FONT_H)  
		   		   sprintf(string_value, "«,"); 
			   if(tmp_VG_Moves[i] == VG_PUNCH_FONT_H)  
		   		   sprintf(string_value, "¬,"); 
			   if(tmp_VG_Moves[i] == VG_KICK_FONT_H)  
		   		   sprintf(string_value, "®,"); 

			   if(tmp_VG_Moves[i] == VG_LEFT_FONT)   
		   		   sprintf(string_value, "¢,"); 
			   if(tmp_VG_Moves[i] == VG_RIGHT_FONT)
		   		   sprintf(string_value, "¤,");
			   if(tmp_VG_Moves[i] == VG_UP_FONT)
		   		   sprintf(string_value, "¦,");
			   if(tmp_VG_Moves[i] == VG_DOWN_FONT)
		   		   sprintf(string_value, "§,");

			   if(tmp_VG_Moves[i] == VG_DOWNLEFT_FONT)  
		   		   sprintf(string_value, "¯,"); 
			   if(tmp_VG_Moves[i] == VG_DOWNRIGHT_FONT)
		   		   sprintf(string_value, "²,");
			   if(tmp_VG_Moves[i] == VG_UPLEFT_FONT)
		   		   sprintf(string_value, "³,");
			   if(tmp_VG_Moves[i] == VG_UPRIGHT_FONT)
		   		   sprintf(string_value, "¹,");

			   if(tmp_VG_Moves[i] == VG_PUNCH_FONT)   
		   		   sprintf(string_value, "ù,");
			   if(tmp_VG_Moves[i] == VG_KICK_FONT)
		   		   sprintf(string_value, "÷,"); 
			   if(tmp_VG_Moves[i] == VG_PUNCH2_FONT)   
		   		   sprintf(string_value, "ú,");
			   if(tmp_VG_Moves[i] == VG_KICK2_FONT)
		   		   sprintf(string_value, "ø,");
			   if(tmp_VG_Moves[i] == VG_PUNCH2_FONT_H)   
		   		   sprintf(string_value, "Â,");
			   if(tmp_VG_Moves[i] == VG_KICK2_FONT_H)
		   		   sprintf(string_value, "Ã,");

			   if(tmp_VG_Moves[i] == VG_SPECIAL1_FONT) 
		   		   sprintf(string_value, "Ê,"); 
			   if(tmp_VG_Moves[i] == VG_SPECIAL2_FONT)
		   		   sprintf(string_value, "Ê,");
			   if(tmp_VG_Moves[i] == VG_SPECIAL3_FONT) 
		   		   sprintf(string_value, "Ê,");
			   if(tmp_VG_Moves[i] == VG_SPECIAL4_FONT)
		   		   sprintf(string_value, "Ê,");
			   if(tmp_VG_Moves[i] == VG_SPECIAL5_FONT || tmp_VG_Moves[i] == VG_COMBO1)
		   		   sprintf(string_value, "Ê,");
			   if(tmp_VG_Moves[i] == VG_SPECIAL6_FONT || tmp_VG_Moves[i] == VG_COMBO2)
		   		   sprintf(string_value, "Ê,");

			   if(tmp_VG_Moves[i] == VG_KICK_AND_PUNCH_FONT)
		   		   sprintf(string_value, "»,");
			     
			   if(tmp_VG_Moves[i] == VG_THROW_FONT) 
		   		   sprintf(string_value, "»,");

			   if(tmp_VG_Moves[i] == VG_LANDED_FONT)
		   		   sprintf(string_value, "»,");

		/*	   if(tmp_VG_Moves[i] == VG_RIGHT_AND_KICK_FONT) 
		   		   sprintf(string_value, "©+¥,");
			   if(tmp_VG_Moves[i] == VG_LEFT_AND_PUNCH_FONT) 
		   		   sprintf(string_value, "¨+£,");
			   if(tmp_VG_Moves[i] == VG_RIGHT_AND_PUNCH_FONT)
		   		   sprintf(string_value, "©+£,");

			   if(tmp_VG_Moves[i] == VG_DOWN_AND_KICK_FONT)
		   		   sprintf(string_value, "«+¥,");
			   if(tmp_VG_Moves[i] == VG_UP_AND_KICK_FONT)
		   		   sprintf(string_value, "ª+¥,");
			   if(tmp_VG_Moves[i] == VG_DOWN_AND_PUNCH_FONT)
		   		   sprintf(string_value, "«+£,");
			   if(tmp_VG_Moves[i] == VG_UP_AND_PUNCH_FONT)
		   		   sprintf(string_value, "ª+£,");

			   if(tmp_VG_Moves[i] == VG_DOWNLEFT_AND_KICK_FONT)
		   		   sprintf(string_value, "¯+¥,");
			   if(tmp_VG_Moves[i] == VG_DOWNRIGHT_AND_KICK_FONT)
		   		   sprintf(string_value, "²+¥,");
			   if(tmp_VG_Moves[i] == VG_DOWNLEFT_AND_PUNCH_FONT)
		   		   sprintf(string_value, "¯+£,");
			   if(tmp_VG_Moves[i] == VG_DOWNRIGHT_AND_PUNCH_FONT)
		   		   sprintf(string_value, "²+£,");

			   if(tmp_VG_Moves[i] == VG_LEFT_AND_PUNCH_AND_KICK_FONT)
		   		   sprintf(string_value, "¢+£+¥,");
			   if(tmp_VG_Moves[i] == VG_RIGHT_AND_PUNCH_AND_KICK_FONT)
		   		   sprintf(string_value, "¤+£+¥,");

			   if(tmp_VG_Moves[i] == VG_DOWNRIGHT_AND_PUNCH_FONT)
		   		   sprintf(string_value, "²+£,");
			   if(tmp_VG_Moves[i] == VG_DOWNLEFT_AND_PUNCH_FONT)
		   		   sprintf(string_value, "¯+£,");

			   if(tmp_VG_Moves[i] == VG_DOWNRIGHT_AND_KICK_FONT)
		   		   sprintf(string_value, "²+¥,");
			   if(tmp_VG_Moves[i] == VG_DOWNLEFT_AND_KICK_FONT)
		   		   sprintf(string_value, "¯+¥,");

			   if(tmp_VG_Moves[i] == VG_UPRIGHT_AND_PUNCH_FONT)
		   		   sprintf(string_value, "¹+£,");
			   if(tmp_VG_Moves[i] == VG_UPLEFT_AND_PUNCH_FONT)
		   		   sprintf(string_value, "³+£,");

			   if(tmp_VG_Moves[i] == VG_UPRIGHT_AND_KICK_FONT)
		   		   sprintf(string_value, "¹+¥,");
			   if(tmp_VG_Moves[i] == VG_UPLEFT_AND_KICK_FONT)
		   		   sprintf(string_value, "³+¥,"); */
    
			   strcat(new_counter[1].word, string_value); 
		   } 
		   }
		    
		   if(VG_SLOWMO == true)        
		   { 
			     
			   // Slowmo for last hit has two speeds...  
			   if(VG_finished_round == true)           
			   { 
				   if((int)TimerGetTime() > VG_slowmo_timer - 3000)  
				   {
					   VG_slowmof = 6.0f;    
					   VG_Reset_all_anims();   
				   }

			   }

			   if((int)TimerGetTime() > VG_slowmo_timer) 
			   {   
				    VG_INVERT_TOTAL_TIMER = 0;
					VG_SLOWMO = false;    
					VG_slowmof = 1.0f; 

					VG_Reset_all_anims(); 
			   }
		   }
	
		   if((int)TimerGetTime() > VG_INVERT_TOTAL_TIMER) 
		   {
			   VG_INVERT = false;
		   }
		   else
		   {
			   if((int)TimerGetTime() > VG_INVERT_TIMER)
			   {
				   VG_INVERT_TIMER = (int)TimerGetTime() + VG_INVERT_LENGTH;

				   VG_INVERT ^= 1;
			   }
		   }


		   if(VG_finished_round == false)
		   if(VG_Display_moves == false)
		   if((int)TimerGetTime() > VG_BATTLE_TIMER)
		   {
			   VG_BATTLE_TIMER = (int)TimerGetTime() + 1000;
			    
			   if(VG_TIME > 0)
			   {
				  VG_TIME--; 
				  
				//  sprite[index].bump_this = true; 
				//  sprite[index].bump_this_timer = (int)TimerGetTime() + 35; 

				  if(VG_AI_active == true) 
				  {
					  VG_1_TOTAL_SECS++; 

					  if(VG_1_TOTAL_SECS>=60)
					  {
						  VG_1_TOTAL_SECS-=60;
						  VG_1_TOTAL_MINS++;
					  }
				  }
			   }
			   else
			   {
				   new_counter[0].alpha = 1.0f;
				   VG_TIME = 0;

				   title_timer = (int)TimerGetTime() + 500; // 500
				   title_sequence = 11;

				   VG_finished_round = true;
			   }
		   } 
		       
		   if(VG_TIME >= 10)   
		   {
			   sprintf( new_counter[0].word, "KO^%i", VG_TIME); 
		   }
		   else
		   { 
			    if(title_sequence < 12)
				{
					if((int)TimerGetTime() > vg_lowtime_timer)
					{
						vg_lowtime_timer = (int)TimerGetTime() + 500;

						if(vg_lowtime_flash == false)
						{
							vg_lowtime_flash = true;
							sprintf(new_counter[0].word, "KO");
						}
						else
						{
							vg_lowtime_flash = false;
							sprintf(new_counter[0].word, "KO^0%i", VG_TIME);
						}
					}
				}
				else
					sprintf(new_counter[0].word, "KO^0%i", VG_TIME);
		   }

		   if(VG_ESC_pressed == true)  
		   {

			   VG_ESC_pressed = false; 

				vg_next_episode = 0; 
				vg_next_scene = 1; 
				  
				next_scene = true;       
				   
		   }     
			// Disable Explosions after running one frame...   
			for(int k=0;k<no_fx;k++)
			if(k >= 0 && k < TOTAL_NO_FX_SPRITES)
			if(Fx[k].sector == FX_VG_EXPLOSION || Fx[k].sector == FX_VG_EXPLOSIONB || Fx[k].sector == FX_VG_EXPLOSIONG || Fx[k].sector == FX_VG_EXPLOSIONS || Fx[k].sector == FX_VG_EXPLOSIONSAIZO)   
			if(Fx[k].fire_target == 101) 
			{ 
				Fx[k].sector = FX_STATIC; 
				Fx[k].grab_switch = true;   
			}   
			 
			if(VG_JUDGE_DECISION == true)
			if((int)TimerGetTime() > VG_JUDGE_DECISION_TIMER) 
			{ 
				VG_JUDGE_DECISION = false;
				vg_judge_sfx = true;  
			} 

			if(VG_JUDGE_AI != VG_JUDGE_FLAG) 
			if((int)TimerGetTime() > VG_JUDGE_AI_TIMER)
			if((VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_DUELLING) || VG_BACKGROUND == VG_KENNEDY)
			if(VG_SABU_JUDGE_INDEX >= 0 && VG_SABU_JUDGE_INDEX < TOTAL_NO_SPRITES)
			{
				mid_x = sprite[VG_SABU_JUDGE_INDEX].x + sprite[VG_SABU_JUDGE_INDEX].width/2;

				if((sprite[2].x + sprite[2].width/2) > (sprite[3].x + sprite[3].width/2))
					tar_x = (sprite[3].x + sprite[3].width/2) + (((sprite[2].x + sprite[2].width/2) - (sprite[3].x + sprite[3].width/2))/2);
				else
					tar_x = (sprite[2].x + sprite[2].width/2) + (((sprite[3].x + sprite[3].width/2) - (sprite[2].x + sprite[2].width/2))/2);

				if(VG_slowmof > 0.0f)
					temp_speed = ((0.00050f/VG_slowmof)*(float)f_rate); // 00400f

				VG_JUDGE_AI = VG_JUDGE_IDLE;   

				if(mid_x < tar_x - (sprite[VG_SABU_JUDGE_INDEX].width/6))  
				{
					Set_Sprite(VG_SABU_JUDGE_INDEX, 4, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Low health red bar...
					sprite[VG_SABU_JUDGE_INDEX].x += temp_speed;
					VG_JUDGE_AI = VG_JUDGE_MOVING; 
				}
				if(mid_x > tar_x + (sprite[VG_SABU_JUDGE_INDEX].width/6))
				{
					Set_Sprite(VG_SABU_JUDGE_INDEX, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Low health red bar...
					sprite[VG_SABU_JUDGE_INDEX].x -= temp_speed;
					VG_JUDGE_AI = VG_JUDGE_MOVING;
				}

				if(VG_JUDGE_AI == VG_JUDGE_IDLE)
				{
					Set_Sprite(VG_SABU_JUDGE_INDEX, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Low health red bar...
					VG_JUDGE_AI_TIMER = (int)TimerGetTime() + 250;
				}

			}


			// Finish round if one of the players is dead...
			if(VG_finished_round == false)
			if(VG_1_HEALTH <= 0 || VG_2_HEALTH <= 0) 
			{

				if((VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_DUELLING) || VG_BACKGROUND == VG_KENNEDY)
				if(VG_SABU_JUDGE_INDEX >= 0 && VG_SABU_JUDGE_INDEX < TOTAL_NO_SPRITES)
				{
					if(VG_1_HEALTH <= 0 && VG_2_HEALTH > 0)
						Set_Sprite(VG_SABU_JUDGE_INDEX, 1, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // Low health red bar...
					if(VG_2_HEALTH <= 0 && VG_1_HEALTH > 0)
						Set_Sprite(VG_SABU_JUDGE_INDEX, 2, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // Low health red bar...

					VG_JUDGE_AI = VG_JUDGE_FLAG;

					VG_JUDGE_DECISION = true;
					VG_JUDGE_DECISION_TIMER = (int)TimerGetTime() + 3500;

				//	vg_pause_sfx = true;
				}


				if(VG_1_HEALTH <= 0)
					VG_1_DEFEATED = true;
				if(VG_2_HEALTH <= 0)
					VG_2_DEFEATED = true;
				 
				if(VG_1_HEALTH <= 0 && VG_2_HEALTH <= 0)
				{
					VG_1_DEFEATED = false;
					VG_2_DEFEATED = false;  
				}
				 
				VG_finished_round = true;  

				VG_SlowMO(6000, 16.0f);  

				title_sequence = 10;   
			}
			     
		   // Attach shadows to players... 
		   sprite[6].x = sprite[2].x; 
		   sprite[5].x = sprite[3].x;  

		   for(int j = 0;j<2;j++)  
		   {  
			     
			   if(VG_1_THROWING == true || VG_2_THROWING == true)
				   VG_THROWING = true;
			   else
				   VG_THROWING = false; 
			    
			   if(VG_finished_round == false)
			   {
				   // Handcuff code..  
				   if(sprite[2].handcuffed == true)
				   if(sprite[2].knockdown == false && sprite[2].status != VG_KNOCKSLIDE_FONT && sprite[2].status != VG_GETUP_FONT)
				   if((int)TimerGetTime() > VG_1_HANDCUFFED_TIMER)
				   {
					   sprite[2].handcuffed = false;

					   VG_2_HAS_THROW = true;

					   if(sprite[2].movement == RIGHT)
						   testX = sprite[2].x + sprite[2].width/3;
					   else
						   testX = (sprite[2].x + sprite[2].width) - sprite[2].width/3;

					   testY = sprite[2].y + (sprite[2].height/2);

					   if(sprite[2].movement == RIGHT)
					   {
						   New_FX(testX, testY,  testX, testY, 44, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 3); 
						   New_FX(testX, testY,  testX, testY, 45, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 4); 
					   }
					   else
					   {
						   New_FX(testX, testY,  testX, testY, 44, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 1); 
						   New_FX(testX, testY,  testX, testY, 45, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 2); 
					   }

					   VG_handcuffs_sfx = true;
				   }

				   if(sprite[3].handcuffed == true)
				   if(sprite[3].knockdown == false && sprite[3].status != VG_KNOCKSLIDE_FONT && sprite[3].status != VG_GETUP_FONT)
				   if((int)TimerGetTime() > VG_2_HANDCUFFED_TIMER)
				   {
					   sprite[3].handcuffed = false;

					   VG_1_HAS_THROW = true;
					    
					   if(sprite[3].movement == RIGHT)
						   testX = sprite[3].x + sprite[3].width/3;
					   else
						   testX = (sprite[3].x + sprite[3].width) - sprite[3].width/3;

					   testY = sprite[3].y + (sprite[3].height/2);

					   if(sprite[3].movement == RIGHT)
					   {
						   New_FX(testX, testY,  testX, testY, 44, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 3); 
						   New_FX(testX, testY,  testX, testY, 45, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 3, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 4); 
					   }
					   else
					   {
						   New_FX(testX, testY,  testX, testY, 44, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 1); 
						   New_FX(testX, testY,  testX, testY, 45, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 3, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 2); 
					   }

					   VG_handcuffs_sfx = true;
				   }
				   // Dizzy code.. 
				   if(sprite[2].dizzy == true)
				   if((int)TimerGetTime() > VG_1_DIZZY_TIMER)
				   {
					   VG_2_HAS_THROW = true;

					   sprite[2].dizzy = false;
					   VG_handcuffs_sfx = true;
				   }

				   if(sprite[3].dizzy == true)
				   if((int)TimerGetTime() > VG_2_DIZZY_TIMER)
				   {
					   VG_1_HAS_THROW = true;

					   sprite[3].dizzy = false;
					   VG_handcuffs_sfx = true;
				   }
				   // Dizzy code.. 
				   if(sprite[2].acid == true)
				   if((int)TimerGetTime() > VG_1_ACID_TIMER)
				   {
					   sprite[2].acid = false;
				   }

				   if(sprite[3].acid == true)
				   if((int)TimerGetTime() > VG_2_ACID_TIMER)
				   {
					   sprite[3].acid = false;
				   }

			   } 

			   if(j == 0) 
			   {   
				   VG_USING = VG_P1_USING;
				   VG_XAXIS = VG_1_XAXIS;

				   VG_DOG = 0; 

				   if(VG_INTRO_DOG1 > 0)
					   VG_DOG = VG_INTRO_DOG1;

				   VG_OTHER_CORNERED = VG_2_CORNERED;

				   VG_CURRENT_CHAR = VG_1_CHARACTER;
				   VG_OTHER_CHAR = VG_2_CHARACTER;

				   VG_BLOCKING = VG_1_BLOCKING;

				   VG_WAS_HIT_TIMES = VG_2_hits; 

				   VG_HEALTH = VG_1_HEALTH;

				   VG_HANDCUFFED = sprite[2].handcuffed;

				   index = 2;
				   index_point = 0;
				   other_index = 3;
				   player = 1;
				   other_player = 2;
				   shadow = 6;   
				    
				   temp_VG_LEFT_pressed = VG_1_LEFT_pressed; 
				   temp_VG_RIGHT_pressed = VG_1_RIGHT_pressed; 
				   temp_VG_UP_pressed = VG_1_UP_pressed;
				   temp_VG_DOWN_pressed = VG_1_DOWN_pressed;
				   temp_VG_DEFEATED = VG_1_DEFEATED; 
				    
				   if(sprite[2].dizzy == true || sprite[2].acid == true)
				   {
					   temp_VG_LEFT_pressed = VG_1_RIGHT_pressed; 
					   temp_VG_RIGHT_pressed = VG_1_LEFT_pressed; 
					   temp_VG_UP_pressed = VG_1_DOWN_pressed;
					   temp_VG_DOWN_pressed = VG_1_UP_pressed;
				   }

				   points[2].active = points[0].active; 

					// A move ended...   
					if(VG_1_MOVE_ACTIVE == true)   
					if(index >= 0 && index < TOTAL_NO_SPRITES)
					if(sprite[index].anim_state == NO_ANIM)  
					{
					   // Do a landed/get up move...
					   if(VG_HEALTH > 0 && sprite[index].was_knocked_down == true)
					   {
						   VG_Reset_Player(1);

						   sprite[index].was_knocked_down = false;

						   if(sprite[index].handcuffed == false)
						   {
							   sprite[index].status = -1; 
							   sprite[index].anim_state = NO_ANIM;
							   VG_MOVE_ACTIVE = false; 
							   VG_1_MOVE_ACTIVE = false;
							   VG_SetMove(player, VG_GETUP_FONT);
						   }
					   }
					   else
					       VG_Reset_Player(1); 

					}	

                   // Turn offf Jae's bullet deflect...
				   if(VG_CURRENT_CHAR == VG_JAE)
				   if((int)TimerGetTime() > VG_1_JAE_DEFLECT_TIMER)
					   sprite[index].deflect = false;

				   VG_MOVE_ACTIVE = VG_1_MOVE_ACTIVE; 

				   if(index >= 0 && index < TOTAL_NO_SPRITES)
				   if(VG_1_MOVE_ACTIVE == false)
				   {
				       sprite[index].box_height = VG_1_BOXHEIGHT;
					   sprite[index].box_height += sprite[index].box_height * VG_RESIZE_Y;
				   }


			   }
			      
			   if(j == 1) 
			   {   
				   VG_USING = VG_P2_USING;
				   VG_XAXIS = VG_2_XAXIS;

				   VG_DOG = 0;

				   if(VG_INTRO_DOG2 > 0)
				       VG_DOG = VG_INTRO_DOG2;

				   VG_OTHER_CORNERED = VG_1_CORNERED;

				   VG_CURRENT_CHAR = VG_2_CHARACTER;
				   VG_OTHER_CHAR = VG_1_CHARACTER;

				   VG_BLOCKING = VG_2_BLOCKING;

				   VG_WAS_HIT_TIMES = VG_1_hits;

				   VG_HEALTH = VG_2_HEALTH;

				   VG_HANDCUFFED = sprite[3].handcuffed;

				   index = 3;
				   index_point = 1;    
				   other_index = 2;  
				   player = 2;
				   other_player = 1;  
				   shadow = 5;

				   temp_VG_LEFT_pressed = VG_2_LEFT_pressed; 
				   temp_VG_RIGHT_pressed = VG_2_RIGHT_pressed; 
				   temp_VG_UP_pressed = VG_2_UP_pressed;
				   temp_VG_DOWN_pressed = VG_2_DOWN_pressed;
				   temp_VG_DEFEATED = VG_2_DEFEATED; 
				     
				   if(sprite[3].dizzy == true || sprite[3].acid == true) 
				   {
					   temp_VG_LEFT_pressed = VG_2_RIGHT_pressed; 
					   temp_VG_RIGHT_pressed = VG_2_LEFT_pressed; 
					   temp_VG_UP_pressed = VG_2_DOWN_pressed;
					   temp_VG_DOWN_pressed = VG_2_UP_pressed;
				   }

				   points[3].active = points[1].active; 

				   // A move ended...
				   if(VG_2_MOVE_ACTIVE == true)  
				   if(index >= 0 && index < TOTAL_NO_SPRITES)
				   if(sprite[index].anim_state == NO_ANIM)
				   {  
					   // Do a landed/get up move...
					   if(VG_HEALTH > 0 && sprite[index].was_knocked_down == true)
					   {
						   VG_Reset_Player(2);

						   sprite[index].was_knocked_down = false;

						   if(sprite[index].handcuffed == false)
						   {
							   sprite[index].status = -1; 
							   sprite[index].anim_state = NO_ANIM;
							   VG_MOVE_ACTIVE = false;
							   VG_2_MOVE_ACTIVE = false;
							   VG_SetMove(player, VG_GETUP_FONT);
						   }
					   }
					   else
					       VG_Reset_Player(2); 
				   }

                   // Turn offf Jae's bullet deflect...
				   if(VG_CURRENT_CHAR == VG_JAE)
				   if((int)TimerGetTime() > VG_2_JAE_DEFLECT_TIMER)
					   sprite[index].deflect = false;

				   VG_MOVE_ACTIVE = VG_2_MOVE_ACTIVE;  

				   if(index >= 0 && index < TOTAL_NO_SPRITES)
				   if(VG_2_MOVE_ACTIVE == false)
				   {
					   sprite[index].box_height = VG_2_BOXHEIGHT;
					   sprite[index].box_height += sprite[index].box_height * VG_RESIZE_Y;
				   }
				     
			   }  // j == 1
			     
			   // Run LEGS... 
			   if(j==0) 
			   if(VG_1_LEGS > 0 && VG_1_LEGS < TOTAL_NO_SPRITES)
			   {
				   sprite[VG_1_LEGS].x = sprite[2].x; 
				   sprite[VG_1_LEGS].type = sprite[2].type;
				   sprite[VG_1_LEGS].walking_backwards = sprite[2].walking_backwards;

				   if(sprite[2].strafe == false)
					   sprite[VG_1_LEGS].alpha = 0.0f; 
				   else 
					   sprite[VG_1_LEGS].alpha = 1.0f; 

				   if(VG_1_LEGS > 0 && VG_1_LEGS < TOTAL_NO_SPRITES)
				   if(sprite[2].moving == true)
			            Set_Sprite(VG_1_LEGS, sprite[VG_1_LEGS].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Walk...
				   else
			            Set_Sprite(VG_1_LEGS, sprite[VG_1_LEGS].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Walk...


			   }
			   if(j==1)
			   if(VG_2_LEGS > 0 && VG_2_LEGS < TOTAL_NO_SPRITES)
			   {
				   sprite[VG_2_LEGS].x = sprite[3].x;
				   sprite[VG_2_LEGS].type = sprite[3].type;
				   sprite[VG_2_LEGS].walking_backwards = sprite[3].walking_backwards;

				   if(sprite[3].strafe == false)
					   sprite[VG_2_LEGS].alpha = 0.0f;
				   else
					   sprite[VG_2_LEGS].alpha = 1.0f;

				   if(VG_2_LEGS > 0 && VG_2_LEGS < TOTAL_NO_SPRITES)
				   if(sprite[3].moving == true)
			            Set_Sprite(VG_2_LEGS, sprite[VG_2_LEGS].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Walk...
				   else
			            Set_Sprite(VG_2_LEGS, sprite[VG_2_LEGS].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Walk...
			   }

			   if(VG_HEALTH < VG_1_TOTALHEALTH/4)
			   {
				   if(CHANGE_SONG_SPEED != 2)
				       CHANGE_SONG_SPEED = 1;
			   }

			   // A.I code...
			   if(j == 1 && title_sequence >= 4) //  && VG_THROWING == false
				   Run_Verdict_AI(f_rate); 

			   if(VG_finished_round == true)
			   {
				   temp_VG_LEFT_pressed = false; 
				   temp_VG_RIGHT_pressed = false;  
				   temp_VG_UP_pressed = false;
				   temp_VG_DOWN_pressed = false;
			   }   
			     
			   VG_DONT_MOVE_CAMERA = false;

			   //
			   // Execute any moves in the queue....
			   // 

			   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if(VG_THROWING == false)  
			   { 
				   if(j == 0)    
				   if(sprite[index].anim != 42 && sprite[3].anim != 65) // Win/fail anim...
				   { 
					   Run_Moves(1, f_rate);  
					   VG_MOVE_ACTIVE = VG_1_MOVE_ACTIVE; 
				   }  
				   else
					   VG_1_OFFSET = 0.0f;

				   if(j == 1)     
				   if(sprite[index].anim != 42 && sprite[3].anim != 65) // Win/fail anim...
				   {
					   Run_Moves(2, f_rate);  
					   VG_MOVE_ACTIVE = VG_2_MOVE_ACTIVE; 
				   }
				   else
					   VG_2_OFFSET = 0.0f;
			   }
			   else
			   {
				   Run_Throws(1, f_rate); 
			   }

			   // Jumping collision...
			   if(index >= 0 && index < TOTAL_NO_SPRITES)	
			   if(sprite[index].jumping == true)    
			   {  
				   if(j == 0)  
				   {
					   if(VG_1_JUMPBOX == 0)
						   sprite[2].z = sprite[2].z + VG_1_BOXHEIGHT/4;
					   VG_1_JUMPBOX = 1;
				       sprite[2].box_height = VG_1_BOXHEIGHT/1.3f;
					   sprite[2].box_height += sprite[2].box_height * VG_RESIZE_Y;

				   }
				   if(j == 1)
				   {
					   if(VG_2_JUMPBOX == 0)
						   sprite[3].z = sprite[3].z + VG_1_BOXHEIGHT/4;
					   VG_2_JUMPBOX = 1;
				       sprite[3].box_height = VG_2_BOXHEIGHT/1.3f;
					   sprite[3].box_height += sprite[3].box_height * VG_RESIZE_Y; 
				   }
			   }  
			   else 
			   {     
				   if(j == 0)
				   {
					   if(VG_1_JUMPBOX == 1)
						   sprite[2].z = sprite[2].z - VG_1_BOXHEIGHT/4;
					   VG_1_JUMPBOX = 0;
				   }
				   if(j == 1)
				   {
					   if(VG_2_JUMPBOX == 1)
						   sprite[3].z = sprite[3].z - VG_1_BOXHEIGHT/4;
					   VG_2_JUMPBOX = 0;
				   }   
				        
			   }       

			   // Deflect flash effects...
			   if((int)TimerGetTime() > VG_DEFLECT_TOTAL_TIMER)
			   {
				   VG_DEFLECT_FLASH_ACTIVE = true;
				   VG_DEFLECT_TIMER = (int)TimerGetTime() + 150;
				   VG_DEFLECT_TOTAL_TIMER = (int)TimerGetTime() + 1000;
			   }
			   if((int)TimerGetTime() > VG_DEFLECT_TIMER)
			   {
				   VG_DEFLECT_FLASH_ACTIVE = false;
			   }

			   // Ducking collision...    
			   if(VG_THROWING == false)
			   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT )
			   if(sprite[index].status != VG_RELOAD_FONT)
			   if(sprite[index].jumping == false) 
			   if(temp_VG_DOWN_pressed == true || temp_VG_DOWNED == true)    
			   {
				   if(j == 0)
				   {
					   if(VG_CURRENT_CHAR == VG_KENNEDY)
						   sprite[2].box_height = VG_1_BOXHEIGHT*0.8f; 
					   else
						   sprite[2].box_height = VG_1_BOXHEIGHT*0.6f; 

					   sprite[2].box_height += sprite[2].box_height * VG_RESIZE_Y; 
				   }
				   if(j == 1)
				   {
					   if(VG_CURRENT_CHAR == VG_KENNEDY)
						   sprite[3].box_height = VG_2_BOXHEIGHT*0.8f; 
					   else
						   sprite[3].box_height = VG_2_BOXHEIGHT*0.6f; 
 
					   sprite[3].box_height += sprite[3].box_height * VG_RESIZE_Y; 
				   }
			   }

			   // Landed... 
			   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if(sprite[index].status == VG_LANDED_FONT || sprite[index].status == VG_GETUP_FONT )
			   if(sprite[index].jumping == false) 
			   {
				   if(j == 0)
				   {
				       sprite[2].box_height = VG_1_BOXHEIGHT*0.6f; 
					   sprite[2].box_height += sprite[2].box_height * VG_RESIZE_Y;
				   }
				   if(j == 1)
				   {
				       sprite[3].box_height = VG_2_BOXHEIGHT*0.6f;    
					   sprite[3].box_height += sprite[3].box_height * VG_RESIZE_Y;
				   }
			   }
			   

			   // Ducking for slide... 
			   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if(VG_CURRENT_CHAR == VG_SIU )
			   if(sprite[index].status == VG_SPECIAL1_FONT )
			   if(sprite[index].special == 1 ) 
			   if(sprite[index].jumping == false) 
			   {
				   if(j == 0)
				   {
					   sprite[2].box_height = VG_1_BOXHEIGHT*0.6f; 
					   sprite[2].box_height += sprite[2].box_height * VG_RESIZE_Y;
				   }
				   if(j == 1)
				   {
				       sprite[3].box_height = VG_2_BOXHEIGHT*0.6f;    
					   sprite[3].box_height += sprite[3].box_height * VG_RESIZE_Y;
				   }
			   }

			   // Suicide... 
			   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if(VG_CURRENT_CHAR == VG_YOHAN )
			   if(sprite[index].status == VG_SPECIAL1_FONT )
			   if(sprite[index].special == 4 ) 
			   if(sprite[index].jumping == false) 
			   {
				   if(j == 0)
				   {
				       sprite[2].box_height = VG_1_BOXHEIGHT*0.6f; 
					   sprite[2].box_height += sprite[2].box_height * VG_RESIZE_Y;
				   }
				   if(j == 1)
				   {
				       sprite[3].box_height = VG_2_BOXHEIGHT*0.6f;    
					   sprite[3].box_height += sprite[3].box_height * VG_RESIZE_Y;
				   }  
			   }

			   // Ducking for low pistol... 
			   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if(VG_CURRENT_CHAR == VG_GYEONG || VG_CURRENT_CHAR == VG_SIU || VG_CURRENT_CHAR == VG_HYUK || VG_CURRENT_CHAR == VG_SANG )
			   if(sprite[index].status == VG_SPECIAL2_FONT )
			   if(sprite[index].special == 4 ) 
			   if(sprite[index].jumping == false) 
			   {
				   if(j == 0)
				   {
				       sprite[2].box_height = VG_1_BOXHEIGHT*0.6f; 
					   sprite[2].box_height += sprite[2].box_height * VG_RESIZE_Y;
				   }
				   if(j == 1)
				   {
				       sprite[3].box_height = VG_2_BOXHEIGHT*0.6f;    
					   sprite[3].box_height += sprite[3].box_height * VG_RESIZE_Y;
				   }  
			   }

			   // Ducking collision for cannonball...  
			   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if(VG_CURRENT_CHAR == VG_GUN || VG_CURRENT_CHAR == VG_KENNEDY) 
			   if(sprite[index].status == VG_SPECIAL1_FONT)
			   if(sprite[index].special == 2)
			   if(sprite[index].jumping == false) 
			   {
				   if(j == 0)
				   {
				       sprite[2].box_height = VG_1_BOXHEIGHT*0.6f; 
					   sprite[2].box_height += sprite[2].box_height * VG_RESIZE_Y;
				   }
				   if(j == 1)
				   {
				       sprite[3].box_height = VG_2_BOXHEIGHT*0.6f;    
					   sprite[3].box_height += sprite[3].box_height * VG_RESIZE_Y;
				   }  
			   }
			   // Ducking collision for arm stretch low...    
			   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if(VG_CURRENT_CHAR == VG_REESE)
			   if(sprite[index].status == VG_SPECIAL1_FONT)
			   if(sprite[index].special == 2) 
			   if(sprite[index].jumping == false) 
			   {
				   if(j == 0)
				   {
				       sprite[2].box_height = VG_1_BOXHEIGHT*0.6f; 
					   sprite[2].box_height += sprite[2].box_height * VG_RESIZE_Y;
				   }
				   if(j == 1)
				   {
				       sprite[3].box_height = VG_2_BOXHEIGHT*0.6f;    
					   sprite[3].box_height += sprite[3].box_height * VG_RESIZE_Y;
				   }   
			   }
			   // Ducking collision for Yohan low vial...    
			   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if(VG_CURRENT_CHAR == VG_YOHAN) 
			   if(sprite[index].status == VG_SPECIAL2_FONT)
			   if(sprite[index].special == 2) 
			   if(sprite[index].jumping == false) 
			   {
				   if(j == 0)
				   {
				       sprite[2].box_height = VG_1_BOXHEIGHT*0.6f; 
					   sprite[2].box_height += sprite[2].box_height * VG_RESIZE_Y;
				   }
				   if(j == 1)
				   {
				       sprite[3].box_height = VG_2_BOXHEIGHT*0.6f;    
					   sprite[3].box_height += sprite[3].box_height * VG_RESIZE_Y;
				   }    
			   }
			   // Ducking collision for Hyuk grenade...    
			   if(index >= 0 && index < TOTAL_NO_SPRITES) 
			   if(VG_CURRENT_CHAR == VG_HYUK) 
			   if(sprite[index].status == VG_SPECIAL1_FONT) 
			   if(sprite[index].special == 2) 
			   if(sprite[index].jumping == false) 
			   {
				   if(j == 0)
				   {
				       sprite[2].box_height = VG_1_BOXHEIGHT*0.6f; 
					   sprite[2].box_height += sprite[2].box_height * VG_RESIZE_Y;
				   }
				   if(j == 1)
				   {
				       sprite[3].box_height = VG_2_BOXHEIGHT*0.6f;    
					   sprite[3].box_height += sprite[3].box_height * VG_RESIZE_Y;
				   }  
			   }
			   // Ducking collision for Jae reload...   
			/*   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if(VG_CURRENT_CHAR == VG_JAE || VG_CURRENT_CHAR == VG_YOHAN)
			   if(sprite[index].status == VG_RELOAD_FONT) 
			   {
				   if(j == 0)
				   {
				       sprite[2].box_height = VG_1_BOXHEIGHT*0.6f; 
					   sprite[2].box_height += sprite[2].box_height * VG_RESIZE_Y;
				   }
				   if(j == 1)
				   {
				       sprite[3].box_height = VG_2_BOXHEIGHT*0.6f;    
					   sprite[3].box_height += sprite[3].box_height * VG_RESIZE_Y;
				   }
			   }*/
			   // Ducking collision for Tazer low...   
			   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if(VG_CURRENT_CHAR == VG_MINSO)
			   if(sprite[index].status == VG_SPECIAL1_FONT)
			   if(sprite[index].special == 2) 
			   if(sprite[index].jumping == false) 
			   {
				   if(j == 0)
				   {
				       sprite[2].box_height = VG_1_BOXHEIGHT*0.6f; 
					   sprite[2].box_height += sprite[2].box_height * VG_RESIZE_Y;
				   }
				   if(j == 1)
				   {
				       sprite[3].box_height = VG_2_BOXHEIGHT*0.6f;    
					   sprite[3].box_height += sprite[3].box_height * VG_RESIZE_Y;
				   }  
			   }

			   // Ducking collision for Sho Slider...   
			   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if(VG_CURRENT_CHAR == VG_SHO)
			   if(sprite[index].status == VG_SPECIAL1_FONT)
			   if(sprite[index].special == 1) 
			   if(sprite[index].cur >= 4 && sprite[index].cur <= 7)
			   if(sprite[index].jumping == false) 
			   {
				   if(j == 0)
				   {
				       sprite[2].box_height = VG_1_BOXHEIGHT*0.6f; 
					   sprite[2].box_height += sprite[2].box_height * VG_RESIZE_Y;
				   }
				   if(j == 1)
				   {
				       sprite[3].box_height = VG_2_BOXHEIGHT*0.6f;    
					   sprite[3].box_height += sprite[3].box_height * VG_RESIZE_Y;
				   }  
			   }

			   if (sprite[index].special == 2 && VG_CURRENT_CHAR == VG_SHO) // Sho's FlameKick...
			   {
				   temp_VG_LEFT_pressed = false;  
				   temp_VG_RIGHT_pressed = false;
			   }

			   if (sprite[index].special == 2 && VG_CURRENT_CHAR == VG_TIA) // Sho's FlameKick...
			   {
				   temp_VG_LEFT_pressed = false;  
				   temp_VG_RIGHT_pressed = false;
			   }

			   // Handle flash code... 
			   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if((int)TimerGetTime() > sprite[index].flash_timer) 
			       sprite[index].flash_target = false;  

			    // Setup directions first...   
			   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if(VG_THROWING == false)  
			   if(VG_finished_round == false)
			   if(sprite[index].status != VG_KNOCKSLIDE_FONT && sprite[index].status != VG_GETUP_FONT) // New  
			   if(sprite[index].jumping == false && sprite[index].knockdown == false)     
			   if(sprite[index].status == -1 || sprite[index].status == VG_KICK_CLOSE_FONT || sprite[index].status == VG_PUNCH_CLOSE_FONT)
			   { 
				   sprite[index].movement = RIGHT;

				   if(sprite[index].x < sprite[other_index].x) 
					   sprite[index].movement = RIGHT;   
				   else
					   sprite[index].movement = LEFT; 
				     
				   if( sprite[index].movement == LEFT)
					   sprite[index].type = FE_FLIP;
				   else  
					   sprite[index].type = FE_NON;   
			   }  
			     
			   sprite[index].block_type = VG_BLOCK_NONE;  
			     
			   //Setup blocking code... 
			   if(index >= 0 && index < TOTAL_NO_SPRITES)
			   if(VG_HANDCUFFED == false)
			   if(VG_THROWING == false)
			   if((j == 0 && sprite[2].pain == false) || (j == 1 && sprite[3].pain == false) || VG_WAS_HIT_TIMES >= 3)
			   if(sprite[index].status != VG_SPECIAL1_FONT && sprite[index].status != VG_SPECIAL2_FONT ) 
			   if( sprite[index].movement != sprite[other_index].movement || VG_WAS_HIT_TIMES >= 3)
			   if( sprite[index].jumping == false && sprite[index].status != VG_KNOCKSLIDE_FONT && sprite[index].status != VG_GETUP_FONT)
			   if( sprite[index].knockdown == false && sprite[index].electrocute == false)
			   if((temp_VG_LEFT_pressed == true && sprite[index].movement == RIGHT) || (temp_VG_RIGHT_pressed == true && sprite[index].movement == LEFT)
			   || VG_BLOCKING == true)
			   {
				   if(temp_VG_DOWN_pressed == true)
					   sprite[index].block_type = VG_BLOCK_LOW;
				   else
					   sprite[index].block_type = VG_BLOCK_MID;

			   }

			    if(j == 0)
				{
					VG_AI_BITE_MID = false;
					VG_AI_BITE_LOW = false;
				}

				// Stop AI from spamming dog atacks if onscreen...
				VG_AI_DOG_ONSCREEN = false;

				if(j == 1)
			    if(VG_DOG > 0 && VG_DOG < TOTAL_NO_SPRITES)   
				if(sprite[VG_DOG].moving == true) 
					VG_AI_DOG_ONSCREEN = true;

			    // Attack dog code...
				if(index >= 0 && index < TOTAL_NO_SPRITES)
			    if(VG_THROWING == false)  
			    if(VG_DOG > 0 && VG_DOG < TOTAL_NO_SPRITES)      
				if((j == 0 && VG_DOG == VG_INTRO_DOG1) || (j == 1 && VG_DOG == VG_INTRO_DOG2) )
				if(sprite[VG_DOG].moving == true)   
				{ 
					  
					if(j == 0)
					{
						mid_x = sprite[VG_DOG].x + sprite[VG_DOG].width/2;   
						tar_x = sprite[3].x + sprite[3].width/2;  

						distance = Node_Distance1(mid_x, VG_START_Y, tar_x, VG_START_Y);

						if(distance < 0.5f) 
						if((sprite[3].movement == RIGHT && mid_x > tar_x) || (sprite[3].movement == LEFT && mid_x < tar_x))
						if(VG_1_CHARACTER == VG_SIU)
							VG_AI_BITE_MID = true;
						else
							VG_AI_BITE_LOW = true;

					}

					if(j == 0)
					if(sprite[VG_DOG].cur == 0 || sprite[VG_DOG].cur == 2)
					if((int)TimerGetTime() > VG_DOG1_trail_timer)
					{ 
						VG_DOG1_trail_timer = (int)TimerGetTime() + 75;

						if(sprite[VG_DOG].movement == RIGHT)
							New_FX(sprite[VG_DOG].x, sprite[VG_DOG].y, sprite[VG_DOG].x, sprite[VG_DOG].y, 2, PLAY, sprite[VG_DOG].width,sprite[VG_DOG].height, sprite[VG_DOG].width, sprite[VG_DOG].height, 3, GFX, 1.0f, 0, -1, FX_STATIC, -1, sprite[VG_DOG].id, 0, 0, -1);
						else
							New_FX(sprite[VG_DOG].x, sprite[VG_DOG].y, sprite[VG_DOG].x, sprite[VG_DOG].y, 3, PLAY, sprite[VG_DOG].width,sprite[VG_DOG].height, sprite[VG_DOG].width, sprite[VG_DOG].height, 3, GFX, 1.0f, 0, -1, FX_FLIP, -1, sprite[VG_DOG].id, 0, 0, -1);
					}
					if(j == 1)
					if(sprite[VG_DOG].cur == 0 || sprite[VG_DOG].cur == 2)
					if((int)TimerGetTime() > VG_DOG2_trail_timer)
					{
						VG_DOG2_trail_timer = (int)TimerGetTime() + 75;

						if(sprite[VG_DOG].movement == RIGHT)
							New_FX(sprite[VG_DOG].x, sprite[VG_DOG].y, sprite[VG_DOG].x, sprite[VG_DOG].y, 2, PLAY, sprite[VG_DOG].width, sprite[VG_DOG].height, sprite[VG_DOG].width, sprite[VG_DOG].height, 3, GFX, 1.0f, 0, -1, FX_STATIC, -1, sprite[VG_DOG].id, 0, 0, -1);
						else
							New_FX(sprite[VG_DOG].x, sprite[VG_DOG].y, sprite[VG_DOG].x, sprite[VG_DOG].y, 3, PLAY, sprite[VG_DOG].width, sprite[VG_DOG].height, sprite[VG_DOG].width, sprite[VG_DOG].height, 3, GFX, 1.0f, 0, -1, FX_FLIP, -1, sprite[VG_DOG].id, 0, 0, -1);
					}

					Set_Sprite(VG_DOG, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Running anim...

					if(VG_slowmof > 0.0f)
						temp_speed = ((0.00150f/VG_slowmof)*(float)f_rate); // 00400f

					if(sprite[VG_DOG].movement == LEFT) 
					{ 
						sprite[VG_DOG].x -= temp_speed;
						sprite[VG_DOG].w -= temp_speed;   
						sprite[VG_DOG].type = FE_FLIP;
					}
					else		 	 		
					{ 
						sprite[VG_DOG].x += temp_speed;  
						sprite[VG_DOG].w += temp_speed; 
						sprite[VG_DOG].type = FE_NON;
					}
					    
					// Reset dog if outside playfield...
					if(sprite[VG_DOG].movement == LEFT) 
					if((sprite[VG_DOG].x + sprite[VG_DOG].width) <= sprite[VG_SCROLL_INDEX+7].x)
						sprite[VG_DOG].moving = false;

					if(sprite[VG_DOG].movement == RIGHT)
					if(sprite[VG_DOG].x >= (sprite[VG_SCROLL_INDEX+7].x + sprite[VG_SCROLL_INDEX+7].width))
						sprite[VG_DOG].moving = false; 

					testX = sprite[VG_DOG].w + sprite[VG_DOG].box_width;    

					if( sprite[VG_DOG].is_a_pigeon == false )
					{
						testY = sprite[VG_DOG].z + sprite[VG_DOG].box_height/2;
						vg_attack_type = VG_DOG_ATTACK;
					}

					if( sprite[VG_DOG].is_a_pigeon == true )
					{
						testY = sprite[VG_DOG].y + (sprite[VG_DOG].height*0.8f);
						vg_attack_type = VG_PIGEON_ATTACK;
					} 
					 
					if(VG_finished_round == false) 
					if(sprite[VG_DOG].grab_switch == true) 
					if(sprite[other_index].invulnerable == false)
					if(( testX < (sprite[other_index].w + sprite[other_index].box_width) )
					&&( testX > sprite[other_index].w)                             
					&&( testY < (sprite[other_index].z + sprite[other_index].box_height) )   
					&&( testY > sprite[other_index].z) )  
					{  

						if(VG_Hit_player(other_player, vg_attack_type, f_rate)) // Returns was blocked...
							New_FX(testX-0.05f, testY-0.05f,  testX-0.05f, testY-0.05f, 1, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 12, 0, 0, -1); // Blocked effect
						else
							New_FX(testX-0.1f, testY-0.1f,  testX-0.1f, testY-0.1f, 3, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 28, 0, 0, -1); // Large spark effect

						sprite[VG_DOG].grab_switch = false;
					} 
					 
				}
				// Test Explosions...   
				if(index >= 0 && index < TOTAL_NO_SPRITES)
				if(VG_THROWING == false)
				if(VG_finished_round == false) 
				for(int k=0;k<no_fx;k++)
				if(k >= 0 && k < TOTAL_NO_FX_SPRITES)
				if(Fx[k].sector == FX_VG_EXPLOSION || Fx[k].sector == FX_VG_EXPLOSIONB || Fx[k].sector == FX_VG_EXPLOSIONG || Fx[k].sector == FX_VG_EXPLOSIONS || Fx[k].sector == FX_VG_EXPLOSIONSAIZO)   
				if(Fx[k].grab_switch == false && Fx[k].turn_off == false)
				{

					testX = Fx[k].x + Fx[k].width/2;                
					testY = Fx[k].y + Fx[k].height/2;  

					mid_x = sprite[index].w + sprite[index].box_width/2;  
					mid_y = sprite[index].z + sprite[index].box_height/2; 

					distance = Node_Distance1(testX, testY, mid_x, mid_y);

					tBomb_range = 0.26f;

					if(Fx[k].sector == FX_VG_EXPLOSIONSAIZO)
						tBomb_range = 0.14f;

					if(Fx[k].grab_switch == false && Fx[k].turn_off == false)
					if(distance < tBomb_range )   
					{  
						  
						if(Fx[k].sector == FX_VG_EXPLOSION)
							VG_bullet_type = VG_EXPLOSION;    

						if(Fx[k].sector == FX_VG_EXPLOSIONB) 
							VG_bullet_type = VG_STICKY_BOMB;  

						if(Fx[k].sector == FX_VG_EXPLOSIONG)
							VG_bullet_type = VG_STICKY_GRENADE; 

						if(Fx[k].sector == FX_VG_EXPLOSIONS)
							VG_bullet_type = VG_STICKY_SUICIDE;

						if(Fx[k].sector == FX_VG_EXPLOSIONSAIZO)
							VG_bullet_type = VG_EXPLOSIONSAIZO;    

						if(VG_Hit_player(player, VG_bullet_type, f_rate))
							New_FX(testX-0.05f, testY-0.05f,  testX-0.05f, testY-0.05f, 1, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 12, 0, 0, -1); 
						else
							New_FX(testX-0.1f, testY-0.1f,  testX-0.1f, testY-0.1f, 3, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 28, 0, 0, -1); // Large spark effect 
						 
						Fx[k].fire_target = 101;

					}  
				} 

				// Test vials...   
				if(index >= 0 && index < TOTAL_NO_SPRITES)
				if(VG_THROWING == false)
				if(VG_finished_round == false) 
				for(int k=0;k<no_fx;k++)
				if(k >= 0 && k < TOTAL_NO_FX_SPRITES)
				if(Fx[k].sector == FX_VG_VIAL || Fx[k].sector == FX_VG_VIAL_LOW || Fx[k].sector == FX_VG_KNIFE)   
				if(Fx[k].grab_switch == false && Fx[k].turn_off == false)
				{

					testX = Fx[k].x + Fx[k].width/2;             
					testY = Fx[k].y + Fx[k].height/2;
	
					if(Fx[k].grab_switch == false && Fx[k].turn_off == false)
					if(sprite[index].invulnerable == false)
					if(( testX < (sprite[index].w + sprite[index].box_width) )
					&&( testX > sprite[index].w)                             
					&&( testY < (sprite[index].z + sprite[index].box_height) )
					&&( testY > sprite[index].z) ) 
					{ 
						if(Fx[k].sector == FX_VG_VIAL) 
							VG_bullet_type = VG_VIAL_MID;
						if(Fx[k].sector == FX_VG_VIAL_LOW)
							VG_bullet_type = VG_VIAL_LOW;
						if(Fx[k].sector == FX_VG_KNIFE)
							VG_bullet_type = VG_KNIFE;

						if(VG_Hit_player(player, VG_bullet_type, f_rate))
							New_FX(testX-0.05f, testY-0.05f,  testX-0.05f, testY-0.05f, 1, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 12, 0, 0, -1); 
						else
							New_FX(testX-0.1f, testY-0.1f,  testX-0.1f, testY-0.1f, 3, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 28, 0, 0, -1); // Large spark effect 
						 
						if(Fx[k].sector == FX_VG_VIAL || Fx[k].sector == FX_VG_VIAL_LOW)
						{ 
							vg_glass_sfx = true;
							// Shards...
							New_FX(Fx[k].x, Fx[k].y,  Fx[k].x, Fx[k].y, 10, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 1); 
							New_FX(Fx[k].x, Fx[k].y,  Fx[k].x, Fx[k].y, 11, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 2); 
							New_FX(Fx[k].x, Fx[k].y,  Fx[k].x, Fx[k].y, 10, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 3); 
							New_FX(Fx[k].x, Fx[k].y,  Fx[k].x, Fx[k].y, 11, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 4); 
						}

						Fx[k].turn_off = true;
						Fx[k].grab_switch = true;

					}  
				} 

				// Test bullets... 
				if(index >= 0 && index < TOTAL_NO_SPRITES)
				if(VG_THROWING == false)
				if(VG_finished_round == false) 
				for(int k=0;k<no_fx;k++)
				if(k >= 0 && k < TOTAL_NO_FX_SPRITES)
				if(Fx[k].sector == FX_VG_BULLET || Fx[k].sector == FX_VG_BULLET_LOW || Fx[k].sector == FX_VG_ORB || Fx[k].sector == FX_VG_FIREBALL || Fx[k].sector == FX_VG_KUNAI)   
				if(Fx[k].grab_switch == false && Fx[k].turn_off == false)
				{

					testX = Fx[k].x + Fx[k].width/2;             
					testY = Fx[k].y + Fx[k].height/2; 

					// Test against other bullets...  
					for(int t=0;t<no_fx;t++)  
					if(t != k) 
					if(t >= 0 && t < TOTAL_NO_FX_SPRITES)
					if(Fx[t].sector == FX_VG_BULLET || Fx[t].sector == FX_VG_BULLET_LOW 
					|| Fx[t].sector == FX_VG_VIAL || Fx[t].sector == FX_VG_VIAL_LOW
					|| Fx[t].sector == FX_VG_ORB || Fx[t].sector == FX_VG_FIREBALL || Fx[t].sector == FX_VG_KUNAI) 
					if(Fx[t].linked_sprite != Fx[k].linked_sprite)
					if(Fx[t].grab_switch == false && Fx[t].turn_off == false)
					{
						  
						if(( testX < (Fx[t].x + Fx[t].width) )
						&&( testX > Fx[t].x)                              
						&&( testY < (Fx[t].y + Fx[t].height) ) 
						&&( testY > Fx[t].y) ) 
						{
							if(Fx[k].sector == FX_VG_ORB || Fx[t].sector == FX_VG_ORB || Fx[k].sector == FX_VG_FIREBALL || Fx[t].sector == FX_VG_FIREBALL ) 
							    vg_vacuum_sfx = true;
							else
							    vg_ric_sfx = true; 
							 
						//	if(Fx[k].sector == FX_VG_ORB || Fx[k].sector == FX_VG_FIREBALL)
						//	if (Fx[t].sector == FX_VG_ORB || Fx[t].sector == FX_VG_FIREBALL)
						//	{
								Fx[t].turn_off = true;
								Fx[k].turn_off = true;
						//	}

							/*if(Fx[t].sector != FX_VG_ORB && Fx[t].sector != FX_VG_FIREBALL)
							    Fx[t].turn_off = true;

							if (Fx[t].sector == FX_VG_ORB && (Fx[k].sector == FX_VG_ORB || Fx[k].sector == FX_VG_FIREBALL))
							{
								Fx[k].turn_off = true;
							}

							if(Fx[t].sector == FX_VG_FIREBALL && (Fx[k].sector == FX_VG_ORB || Fx[k].sector == FX_VG_FIREBALL))
							    Fx[k].turn_off = true;*/

						//	Fx[k].turn_off = true;
							New_FX(testX-0.1f, testY-0.1f,  testX-0.1f, testY-0.1f, 3, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 28, 0, 0, -1); // Large spark effect 
						}

					}

					if(k >= 0 && k < TOTAL_NO_FX_SPRITES)
					if(Fx[k].linked_sprite >= 0 && Fx[k].linked_sprite < TOTAL_NO_SPRITES)
					if(Fx[k].linked_sprite != index)
					if(Fx[k].grab_switch == false && Fx[k].turn_off == false) 
					if(( testX < (sprite[index].w + sprite[index].box_width) )
					&&( testX > sprite[index].w)                             
					&&( testY < (sprite[index].z + sprite[index].box_height) ) 
					&&( testY > sprite[index].z) ) 
					{    
						// Reese's bullet deflect code...
						if(sprite[index].deflect == true && Fx[k].sector != FX_VG_ORB && Fx[k].sector != FX_VG_FIREBALL) //  || (sprite[index].invulnerable == true && VG_OTHER_CHAR != VG_MINSO) 
						{
							if(Fx[k].anim == 2 && testX < (sprite[index].w + sprite[index].box_width/2) ) // RIGHT 
							{
								vg_ric_sfx = true;
								New_FX(testX-0.05f, testY-0.05f,  testX-0.05f, testY-0.05f, 48, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 12, 0, 0, -1);
								Set_Sprite(k, 3, LOOP, ANIM_FX, ANIM_NOT_WALKING);
								Fx[k].linked_sprite = index;
							}
							if(Fx[k].anim == 3 && testX > (sprite[index].w + sprite[index].box_width/2) ) // LEFT  
							{
								vg_ric_sfx = true;
								New_FX(testX-0.05f, testY-0.05f,  testX-0.05f, testY-0.05f, 48, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 12, 0, 0, -1);
								Set_Sprite(k, 2, LOOP, ANIM_FX, ANIM_NOT_WALKING);
								Fx[k].linked_sprite = index;
							}
						}
						else 
						{
							if(Fx[k].sector == FX_VG_BULLET)
								VG_bullet_type = VG_BULLET_MID;
							else
								VG_bullet_type = VG_BULLET_LOW;

							if(Fx[k].sector == FX_VG_ORB)
								VG_bullet_type = VG_BULLET_ORB;

							if(Fx[k].sector == FX_VG_FIREBALL)
								VG_bullet_type = VG_BULLET_MID;

							if(Fx[k].sector == FX_VG_KUNAI)
								VG_bullet_type = VG_BULLET_MID;

							if(VG_Hit_player(player, VG_bullet_type, f_rate))
								New_FX(testX-0.05f, testY-0.05f,  testX-0.05f, testY-0.05f, 1, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 12, 0, 0, -1); 
							else
								New_FX(testX-0.1f, testY-0.1f,  testX-0.1f, testY-0.1f, 3, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 28, 0, 0, -1); // Large spark effect 

							Fx[k].turn_off = true;
							Fx[k].grab_switch = true;
						}

					}  
				} 
				
				// Run normal hits...
				if(VG_THROWING == false)
				if(VG_finished_round == false)  
				if(index_point >= 0 && index_point < TOTAL_NO_POINTS)
				if(points[index_point].active == 1)      
				if(VG_ShootRay(player)) 
				{    
					if(VG_OTHER_CHAR == VG_REESE && sprite[other_index].special == 3 && sprite[other_index].status == VG_SPECIAL2_FONT) // Reese's electrocute...
					{
						if(VG_Hit_player(player, -1, f_rate))
							New_FX(VG_HIT_X-0.05f, VG_HIT_Y-0.05f,  VG_HIT_X-0.05f, VG_HIT_Y-0.05f, 1, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 12, 0, 0, -1); 
					} 
					else 
					{   
						if(sprite[other_index].invulnerable == false  
						|| (sprite[index].invulnerable == true && sprite[other_index].invulnerable == true)
						|| (VG_CURRENT_CHAR == VG_REESE && (sprite[other_index].status == VG_SPECIAL1_FONT || sprite[other_index].status == VG_SPECIAL2_FONT) ))
						if((sprite[other_index].on_ladder == false && sprite[other_index].status != VG_KNOCKSLIDE_FONT && sprite[other_index].status != VG_GETUP_FONT) || VG_OTHER_CORNERED == false) // Stop infinite combos on cornered character...
						if (VG_Hit_player(other_player, -1, f_rate))
						{
							New_FX(VG_HIT_X - 0.05f, VG_HIT_Y - 0.05f, VG_HIT_X - 0.05f, VG_HIT_Y - 0.05f, 1, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 12, 0, 0, -1);
						}
						else
						{
							if((player == 1 && VG_2_HEALTH > 0) || (player == 2 && VG_1_HEALTH > 0))
								New_FX(VG_HIT_X-0.05f, VG_HIT_Y-0.05f,  VG_HIT_X-0.05f, VG_HIT_Y-0.05f, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 12, 0, 0, -1); 
							else
								New_FX(VG_HIT_X-0.1f, VG_HIT_Y-0.1f,  VG_HIT_X-0.1f, VG_HIT_Y-0.1f, 3, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 0, GFX, 1.0f, 0, index, FX_PUNCH_POINT, -1, 28, 0, 0, -1); // Large spark effect
						}
					}

					points[index_point].active = 2; // Hit a guy so stop moving...
				}   

				// Need to turn off arm sprite here...
				if(VG_CURRENT_CHAR == VG_REESE || VG_CURRENT_CHAR == VG_SANG) 
				if(sprite[index].status != VG_SPECIAL1_FONT)
				{
					for(int i=0;i<no_fx;i++) 
					if(i >= 0 && i < TOTAL_NO_FX_SPRITES)
					{ 
						if(Fx[i].sector == FX_ARM || Fx[i].sector == FX_FLAME)
						if(Fx[i].value3 == index)
						{
							Fx[i].turn_off = true;
						}
					}
					if(player == 1)
						VG_1_ARM_LENGTH = false;
					else
						VG_2_ARM_LENGTH = false;
				}

			   // Disable moving controls when one character is sliding...
			   if((j == 0 && sprite[2].pain == true) || (j == 1 && sprite[3].pain == true) || VG_THROWING == true
			   || sprite[index].status == VG_KNOCKSLIDE_FONT || sprite[index].status == VG_GETUP_FONT)
				   VG_MOVE_ACTIVE = true; 
				  
			   // Disable down if jumping... 
			   if(sprite[index].jumping == true || sprite[index].knockdown == true || VG_THROWING == true) 
			   if(temp_VG_DOWN_pressed == true) 
				   temp_VG_DOWN_pressed = false; 
			    
			   // Can't press left & right at the same time...
			   if(temp_VG_LEFT_pressed == true && temp_VG_RIGHT_pressed == true || VG_BLOCKING == true)
			   {
				   temp_VG_LEFT_pressed = false;
				   temp_VG_RIGHT_pressed = false; 
			   }

			   // Setup directions... 
			   if(VG_THROWING == false)    
               if(sprite[index].status != VG_KNOCKSLIDE_FONT && sprite[index].status != VG_GETUP_FONT 
			   && sprite[index].jumping == false && sprite[index].knockdown == false)  
			   {
				   if(temp_VG_LEFT_pressed == false && temp_VG_RIGHT_pressed == false)
					   sprite[index].direction = RESET;
				   if(temp_VG_LEFT_pressed == true)  
					   sprite[index].direction = LEFT; 
				   if(temp_VG_RIGHT_pressed == true)
					   sprite[index].direction = RIGHT;
			   }  

			   // Moving Left/Right... 
			    
			   mid_x = sprite[index].x + sprite[index].width/2;  
			   tar_x = sprite[other_index].x + sprite[other_index].width/2;  

			   distance = Node_Distance1(mid_x, VG_START_Y, tar_x, VG_START_Y);

			   sprite[index].moving = false;

			   // Walk left...
			   if(VG_THROWING == false)
			   if(VG_finished_round == false)  
			   if(VG_MOVE_ACTIVE == false || sprite[index].strafe == true || sprite[index].spin_strafe == true)  
			   if(temp_VG_DOWN_pressed == false)
			   if(sprite[index].status != VG_KNOCKSLIDE_FONT && sprite[index].status != VG_GETUP_FONT) // New
			   if(sprite[index].hit_opponent == false || sprite[index].spin_strafe == true)
			   if(sprite[index].jumping == false && sprite[index].knockdown == false)  
			   if(distance < screen_limit || sprite[index].x > sprite[other_index].x)
			   if(temp_VG_LEFT_pressed == true)    
			   { 

				   // Walking backwards... 
				   if(sprite[index].movement == RIGHT) 
				   {
					   VG_SPEED = 0.00044f;  // 44 
					     
					   if(VG_CURRENT_CHAR == VG_GUN)      
						   VG_SPEED = 0.00024f;  
					   if(VG_CURRENT_CHAR == VG_YOHAN)     
						   VG_SPEED = 0.00033f; 
					   if(VG_CURRENT_CHAR == VG_TRAINER)       
						   VG_SPEED = 0.00033f;  
					   if(VG_CURRENT_CHAR == VG_KENNEDY)      
						   VG_SPEED = 0.00024f;  
					     
					   if(VG_USING == VG_CONTROLLER) 
					   if(VG_XAXIS != 0.0f)  
						   VG_SPEED /= VG_XAXIS;  
					    
						if(VG_ARCADE_TYPE == VG_ARCADE_TURBO)
							VG_SPEED += 0.00025f; 
						else   
							VG_SPEED += 0.00005f;

					   if(sprite[index].strafe == true)
						   VG_SPEED = 0.00028f; 
					   if(sprite[index].spin_strafe == true)
						   VG_SPEED = 0.00026f;  

					   if(VG_slowmof > 0.0f)
						   temp_speed = (VG_SPEED/VG_slowmof)*(float)f_rate;  

					   sprite[index].moving = true;
					    
				   } 
				   else  
				   {  
					   VG_SPEED = 0.00080f;  // 80   
					    
					   if(VG_CURRENT_CHAR == VG_GUN)      
						   VG_SPEED = 0.00050f; // 40
					   if(VG_CURRENT_CHAR == VG_YOHAN)      
						   VG_SPEED = 0.00060f; // 55
					   if(VG_CURRENT_CHAR == VG_TRAINER)      
						   VG_SPEED = 0.00060f; // 55
					   if(VG_CURRENT_CHAR == VG_KENNEDY)      
						   VG_SPEED = 0.00050f; // 40

					   if(VG_USING == VG_CONTROLLER)
					   if(VG_XAXIS != 0.0f)
						   VG_SPEED /= VG_XAXIS;
					   
						if(VG_ARCADE_TYPE == VG_ARCADE_TURBO)
							VG_SPEED += 0.00025f;
						else
							VG_SPEED += 0.00005f;

					   if(sprite[index].strafe == true)
						   VG_SPEED = 0.00030f; 
					   if(sprite[index].spin_strafe == true)
						   VG_SPEED = 0.00028f; 

					   if(VG_slowmof > 0.0f)
					       temp_speed = (VG_SPEED/VG_slowmof)*(float)f_rate;

					   sprite[index].moving = true;
				   }
			          
				   pushing_X = sprite[index].w - temp_speed;

				   if( (pushing_X < sprite[other_index].w + sprite[other_index].box_width) && sprite[index].movement == LEFT)
				   {
					   temp_speed *= 0.4f;

				       sprite[index].x -= temp_speed;    
				       sprite[index].w -= temp_speed;

					   sprite[other_index].x -= temp_speed;  
					   sprite[other_index].w -= temp_speed; 
				   }
				   else
				   {
				       sprite[index].x -= temp_speed;    
				       sprite[index].w -= temp_speed;
				   }

			   }            
			     
			   // Walk right...  
			   if(VG_THROWING == false)
			   if(VG_finished_round == false) 
			   if(VG_MOVE_ACTIVE == false || sprite[index].strafe == true || sprite[index].spin_strafe == true)
			   if(temp_VG_DOWN_pressed == false)
			   if(sprite[index].status != VG_KNOCKSLIDE_FONT && sprite[index].status != VG_GETUP_FONT) // New
			   if(sprite[index].hit_opponent == false || sprite[index].spin_strafe == true)
			   if(sprite[index].jumping == false && sprite[index].knockdown == false)  
			   if(distance < screen_limit || sprite[index].x < sprite[other_index].x)
			   if(temp_VG_RIGHT_pressed == true) 
			   {  

				   // Walking backwards... 
				   if(sprite[index].movement == LEFT)
				   {
					   VG_SPEED = 0.00044f;  // 44

					   if(VG_CURRENT_CHAR == VG_GUN)      
						   VG_SPEED = 0.00024f; 
					   if(VG_CURRENT_CHAR == VG_YOHAN)      
						   VG_SPEED = 0.00033f; 
					   if(VG_CURRENT_CHAR == VG_TRAINER)      
						   VG_SPEED = 0.00033f; 
					   if(VG_CURRENT_CHAR == VG_KENNEDY)      
						   VG_SPEED = 0.00024f; 

					   if(VG_USING == VG_CONTROLLER)
					   if(VG_XAXIS != 0.0f) 
						   VG_SPEED /= VG_XAXIS;
					   
						if(VG_ARCADE_TYPE == VG_ARCADE_TURBO)
							VG_SPEED += 0.00025f;
						else
							VG_SPEED += 0.00005f;

					   if(sprite[index].strafe == true)
						   VG_SPEED = 0.00028f; 
					   if(sprite[index].spin_strafe == true)
						   VG_SPEED = 0.00026f; 

					   if(VG_slowmof > 0.0f)
					       temp_speed = (VG_SPEED/VG_slowmof)*(float)f_rate; 

					   sprite[index].moving = true;
				   }
				   else         
				   { 
					   VG_SPEED = 0.00080f;  // 80
					     
					   if(VG_CURRENT_CHAR == VG_GUN)       
						   VG_SPEED = 0.00050f; // 40
					   if(VG_CURRENT_CHAR == VG_YOHAN)      
						   VG_SPEED = 0.00060f; // 55
					   if(VG_CURRENT_CHAR == VG_TRAINER)       
						   VG_SPEED = 0.00060f; // 55
					   if(VG_CURRENT_CHAR == VG_KENNEDY)       
						   VG_SPEED = 0.00050f; // 40

					   if(VG_USING == VG_CONTROLLER) 
					   if(VG_XAXIS != 0.0f)
						   VG_SPEED /= VG_XAXIS;
					   
						if(VG_ARCADE_TYPE == VG_ARCADE_TURBO)
							VG_SPEED += 0.00025f;
						else
							VG_SPEED += 0.00005f;

					   if(sprite[index].strafe == true)
						   VG_SPEED = 0.00030f; 
					   if(sprite[index].spin_strafe == true)
						   VG_SPEED = 0.00028f; 

					   if(VG_slowmof > 0.0f)
					       temp_speed = (VG_SPEED/VG_slowmof)*(float)f_rate;   

					   sprite[index].moving = true;
				   }

				   pushing_X = sprite[index].w + sprite[index].box_width + temp_speed;

				   if( (pushing_X > sprite[other_index].w) && sprite[index].movement == RIGHT)
				   {
					   temp_speed *= 0.4f;

					   sprite[index].x += temp_speed;    
					   sprite[index].w += temp_speed;

					   sprite[other_index].x += temp_speed;  
					   sprite[other_index].w += temp_speed; 
				   }
				   else
				   {
					   sprite[index].x += temp_speed;    
					   sprite[index].w += temp_speed;
				   }
				    
			   }   
			  
			   // Large shadows for floored sprites...  
			   if(sprite[index].status == VG_KNOCKSLIDE_FONT  || (temp_VG_DEFEATED == true && VG_TIME > 0) )
				   Set_Sprite(shadow, 4, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Shadow...
			   else
				   Set_Sprite(shadow, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Shadow...
			    
			   // Jumping code...   
			   if(VG_THROWING == false)
			   if(VG_MOVE_ACTIVE == false)  
			   if(sprite[index].jumping == false && sprite[index].knockdown == false)      
			   if(temp_VG_UP_pressed == true)    
			   {   
				   sprite[index].action_timer = (int)TimerGetTime() + 90;

				   if(sprite[index].handcuffed == false)
					   Set_Sprite(index, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
				   else
					   Set_Sprite(index, 52, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump handcuffed...

				   sprite[index].jumping = true; 
				   sprite[index].on_ladder = true;
			   }

			   inc_y = sprite[index].z - sprite[index].y;  
		     
			   if((int)TimerGetTime() > sprite[index].action_timer)
			   if(sprite[index].jumping == true)    
			   {         
				      
				   VG_JUMP_HEIGHT = 0.28f; //  0.25f  
				     
				   if(VG_CURRENT_CHAR == VG_MINSO)       
					   VG_JUMP_HEIGHT = 0.28f; //  0.265f
				   if(VG_CURRENT_CHAR == VG_GUN)        
					   VG_JUMP_HEIGHT = 0.16f;  //  0.16f
				   if(VG_CURRENT_CHAR == VG_YOHAN)      
					   VG_JUMP_HEIGHT = 0.18f;  //  0.18f
				   if(VG_CURRENT_CHAR == VG_TRAINER)
					   VG_JUMP_HEIGHT = 0.18f;  //  0.18f  
				   if(VG_CURRENT_CHAR == VG_KENNEDY)        
					   VG_JUMP_HEIGHT = 0.16f;  //  0.16f
				      
				   // Jump left-Right...     
				   if(sprite[index].direction == LEFT || sprite[index].direction == RIGHT)
				   {
					   jump_sideways = true; 

					   if(distance < screen_limit || sprite[index].x > sprite[other_index].x)
					   if(sprite[index].direction == LEFT)
					   {   
						   if(sprite[index].movement == LEFT)            
						   {  
							   if(VG_JUMP_HEIGHT > 0.21f) 
							       VG_JUMP_HEIGHT = 0.21f; 
							   if(VG_slowmof > 0.0f)
							       temp_speed = -((0.00100f/VG_slowmof)*(float)f_rate); // 0.0.00075f
						   }
						   else  
						   {
							   if(VG_JUMP_HEIGHT > 0.25f)
							       VG_JUMP_HEIGHT = 0.25f;
							   if(VG_slowmof > 0.0f)
							       temp_speed = -((0.00090f/VG_slowmof)*(float)f_rate); // 0.0.00075f  
						   }
						      
						   sprite[index].x += temp_speed;   
						   sprite[index].w += temp_speed;
					   }
					   if(distance < screen_limit || sprite[index].x < sprite[other_index].x)
					   if(sprite[index].direction == RIGHT)
					   { 
						   if(sprite[index].movement == RIGHT)    
						   {
							   if(VG_JUMP_HEIGHT > 0.21f)
							       VG_JUMP_HEIGHT = 0.21f;
							   if(VG_slowmof > 0.0f)
							       temp_speed = (0.00100f/VG_slowmof)*(float)f_rate; // // 0.0.00075f 
						   }
						   else 
						   {
							   if(VG_JUMP_HEIGHT > 0.25f)
							       VG_JUMP_HEIGHT = 0.25f;
							   if(VG_slowmof > 0.0f)
							       temp_speed = (0.00090f/VG_slowmof)*(float)f_rate; // // 0.0.00075f
						   }

						   sprite[index].x += temp_speed;   
						   sprite[index].w += temp_speed;
					   }
					    
				   }

				   temp_speed = 0.00160f*(float)f_rate;          

				   if(sprite[index].y < VG_START_Y + (VG_JUMP_HEIGHT*0.90f))
				   {
					   if(sprite[index].status == -1)
					   {
						   if(sprite[index].handcuffed == false)
							   Set_Sprite(index, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
						   else
							   Set_Sprite(index, 52, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump handcuffed...
					   } 

					   Set_Sprite(shadow, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Shadow...

					   if(sprite[index].y > VG_START_Y + (VG_JUMP_HEIGHT*0.25f)) 
					   {
						   if(sprite[index].status == -1) 
						   {
							   if(sprite[index].handcuffed == false)
								   Set_Sprite(index, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
							   else
								   Set_Sprite(index, 53, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump handcuffed...
						   }

							Set_Sprite(shadow, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Shadow...
					   }
					   if(sprite[index].y > VG_START_Y + (VG_JUMP_HEIGHT*0.50f)) 
					   {
						   if(VG_slowmof > 0.0f)
						       temp_speed = (0.00100f/VG_slowmof)*(float)f_rate;

						   if(sprite[index].status == -1)
						   {
							   if(sprite[index].handcuffed == false)
								   Set_Sprite(index, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
							   else
								   Set_Sprite(index, 53, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump handcuffed...
						   }
						   Set_Sprite(shadow, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Shadow...
					   }
					   if(sprite[index].y > VG_START_Y + (VG_JUMP_HEIGHT*0.75f))
					   {
						   if(VG_slowmof > 0.0f)
						       temp_speed = (0.00060f/VG_slowmof)*(float)f_rate;  // 75

						    if(sprite[index].status == -1)
							if(sprite[index].direction == LEFT && sprite[index].movement == RIGHT 
							|| sprite[index].direction == RIGHT && sprite[index].movement == LEFT)
							{
								if(sprite[index].handcuffed == false)
								    Set_Sprite(index, 35, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
								else
								    Set_Sprite(index, 55, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
							}
							else
							{
								if(sprite[index].handcuffed == false)
									Set_Sprite(index, 4, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
								else
									Set_Sprite(index, 54, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
							}
							 
						   Set_Sprite(shadow, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Shadow...
					   }
					   if(sprite[index].y > VG_START_Y + (VG_JUMP_HEIGHT*0.80f))   
					   {   
						   if(VG_slowmof > 0.0f)
						       temp_speed = (0.00035f/VG_slowmof)*(float)f_rate; // 50
						    
						   if(sprite[index].status == -1)
							if(sprite[index].direction == LEFT && sprite[index].movement == RIGHT 
							|| sprite[index].direction == RIGHT && sprite[index].movement == LEFT)
							{
								if(sprite[index].handcuffed == false)
								    Set_Sprite(index, 35, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
								else
								    Set_Sprite(index, 55, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
							}
							else
							{
								if(sprite[index].handcuffed == false)
									Set_Sprite(index, 4, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
								else
									Set_Sprite(index, 54, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
							}

						   Set_Sprite(shadow, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Shadow...
					   }
					    
					   if(jump_sideways == false) 
					   if(VG_slowmof > 0.0f)
						   temp_speed += (0.00020f/VG_slowmof)*(float)f_rate;
				   }  
				   else       
				   {
					   if(VG_slowmof > 0.0f)
					   if(sprite[index].y > VG_START_Y + (VG_JUMP_HEIGHT*0.90f))
						   temp_speed = (0.00020f/VG_slowmof)*(float)f_rate;

					   if(VG_slowmof > 0.0f)
					   if(sprite[index].y > VG_START_Y + (VG_JUMP_HEIGHT*0.95f))
						   temp_speed = (0.00018f/VG_slowmof)*(float)f_rate;

						if(sprite[index].status == -1)
						if(sprite[index].direction == LEFT && sprite[index].movement == RIGHT 
						|| sprite[index].direction == RIGHT && sprite[index].movement == LEFT)
						{
							if(sprite[index].handcuffed == false)
								Set_Sprite(index, 36, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
							else
								Set_Sprite(index, 57, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
						}
						else
						{
							if(sprite[index].handcuffed == false)
								Set_Sprite(index, 5, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
							else
								Set_Sprite(index, 56, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
						}

					   Set_Sprite(shadow, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Shadow...

				   }   

				   if(sprite[index].on_ladder == false)
					   temp_speed *= -1; 
			     
				   sprite[index].y += temp_speed;     
				   sprite[index].z += temp_speed;  

				   if(sprite[index].y > VG_START_Y + VG_JUMP_HEIGHT)
				   {
					   sprite[index].on_ladder = false;
					   sprite[index].y = VG_START_Y + VG_JUMP_HEIGHT;
					   sprite[index].z = sprite[index].y + inc_y; 
				   } 
				    
				   if(sprite[index].y < VG_START_Y)    
				   { 
					   VG_dust_effect(VG_CURRENT_CHAR, shadow, sprite[index].movement);
					   VG_land_sfx = true; 
					   sprite[index].jumping = false;
					   sprite[index].y = VG_START_Y;
					   sprite[index].z = sprite[index].y + inc_y;   

					   // Test for fixing odd crouched jumping bug...
					   temp_VG_DOWN_pressed = false;

					/*   if(VG_1_HEALTH <= 0 || VG_2_HEALTH <= 0)
					   {
						   sprite[index].status = -1; 
						   sprite[index].anim_state = NO_ANIM; 

						   if(j == 0)
							   VG_1_MOVE_ACTIVE = false;
						   if(j == 1)
							   VG_2_MOVE_ACTIVE = false;

						   VG_MOVE_ACTIVE = false;
						   VG_SetMove(player, VG_LANDED_FONT);
					   }*/

				   }

			   }  // if(sprite[index].jumping == true)    

			   inc_y = sprite[index].z - sprite[index].y; 

			   // Knockdown code... 
			   if(sprite[index].knockdown == true)     
			   {         

				    VG_JUMP_HEIGHT = 0.075f;   

					if(j == 0 && VG_1_CORNERED == true && sprite[index].electrocute == false)
						VG_JUMP_HEIGHT = 0.025f;
			       	if(j == 1 && VG_2_CORNERED == true && sprite[index].electrocute == false)
						VG_JUMP_HEIGHT = 0.025f;
				 
				   // Jump left-Right...   
					if(distance < screen_limit) 
					if(sprite[index].x >= sprite[other_index].x)
					{
						if(VG_slowmof > 0.0f)
						    temp_speed = ((0.00140f/VG_slowmof)*(float)f_rate);        

						sprite[index].x += temp_speed;   
						sprite[index].w += temp_speed; 
					}
					if(distance < screen_limit)
					if(sprite[index].x < sprite[other_index].x)
					{
						if(VG_slowmof > 0.0f)
						    temp_speed = -(0.00140f/VG_slowmof)*(float)f_rate;

						sprite[index].x += temp_speed;   
						sprite[index].w += temp_speed;
					} 

				   if(VG_slowmof > 0.0f)
				       temp_speed = 0.00120f*(float)f_rate;                 

				   if(sprite[index].y < sprite[index].knockdown_Y + (VG_JUMP_HEIGHT*0.90f))
				   {
					   Set_Sprite(shadow, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Shadow...

					   if(sprite[index].y > sprite[index].knockdown_Y + (VG_JUMP_HEIGHT*0.25f)) 
					   {
							Set_Sprite(shadow, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Shadow...
					   }
					   if(sprite[index].y > sprite[index].knockdown_Y + (VG_JUMP_HEIGHT*0.50f)) 
					   {
						   if(VG_slowmof > 0.0f)
						       temp_speed = (0.00090f/VG_slowmof)*(float)f_rate;
						   Set_Sprite(shadow, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Shadow...
					   }
					   if(sprite[index].y > sprite[index].knockdown_Y + (VG_JUMP_HEIGHT*0.75f))
					   {
						   if(VG_slowmof > 0.0f)
						       temp_speed = (0.00055f/VG_slowmof)*(float)f_rate;
						   Set_Sprite(shadow, 2, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Shadow...
					   }
					   if(sprite[index].y > sprite[index].knockdown_Y + (VG_JUMP_HEIGHT*0.80f))   
					   {  
						   if(VG_slowmof > 0.0f)
						       temp_speed = (0.00040f/VG_slowmof)*(float)f_rate;
						   Set_Sprite(shadow, 2, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Shadow...
					   } 
					     
				   }         
				   else         
				   {
					   if(VG_slowmof > 0.0f)
					   if(sprite[index].y > sprite[index].knockdown_Y + (VG_JUMP_HEIGHT*0.90f))
						   temp_speed = (0.00030f/VG_slowmof)*(float)f_rate;

					   if(VG_slowmof > 0.0f)
					   if(sprite[index].y > sprite[index].knockdown_Y + (VG_JUMP_HEIGHT*0.95f))
						   temp_speed = (0.00028f/VG_slowmof)*(float)f_rate;

					   Set_Sprite(shadow, 3, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Shadow...
					    
				   }        

				   if(sprite[index].on_ladder == false)         
				   {   

					    // Falling down... 

					   temp_speed *= -1;            
					     
					   if(sprite[index].electrocute == true)
					   {
						   if(sprite[index].handcuffed == false)
							   Set_Sprite(index, 37, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
						   else
							   Set_Sprite(index, 67, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
					   }
					   else 
					   {
						   if(sprite[index].handcuffed == false)
							   Set_Sprite(index, 17, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
						   else
							   Set_Sprite(index, 60, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
					   }
				   }
				   else    
				   {
					   // Falling up...

					   if(sprite[index].electrocute == true)
					   {
						   if(sprite[index].handcuffed == false)
							   Set_Sprite(index, 37, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
						   else
							   Set_Sprite(index, 67, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
					   }
					   else
					   {
						   if(sprite[index].handcuffed == false)
							   Set_Sprite(index, 16, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
						   else
							   Set_Sprite(index, 59, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Prepared to jump...
					   }  
				   }

				   sprite[index].y += temp_speed;       
				   sprite[index].z += temp_speed;      

				   if(sprite[index].y > sprite[index].knockdown_Y + VG_JUMP_HEIGHT)
				   {
					   sprite[index].on_ladder = false;
					   sprite[index].y = sprite[index].knockdown_Y + VG_JUMP_HEIGHT;
					   sprite[index].z = sprite[index].y + inc_y;
				   }

				   if(shadow >= 0 && shadow < TOTAL_NO_SPRITES)
				   if(sprite[index].y < VG_START_Y)
				   {  

					   New_FX((sprite[shadow].x+sprite[shadow].width/2)+0.00f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)+0.00f, sprite[shadow].y, 12, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
					   New_FX((sprite[shadow].x+sprite[shadow].width/2)-0.10f, sprite[shadow].y,  (sprite[shadow].x+sprite[shadow].width/2)-0.10f, sprite[shadow].y, 12, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_STATIC, 5, 12, 0, 0, 1); 
					    
					   VG_knockslide_sfx = true;  
					      
					   // Shake camera...  
					   VG_Do_Shake(500, 0.0115f);  

					    if(sprite[index].handcuffed == false) 
							Set_Sprite(index, 18, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_LEFT_AND_PUNCH_FONT    
						else
							Set_Sprite(index, 61, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // VG_LEFT_AND_PUNCH_FONT 
						 
						sprite[index].status = VG_KNOCKSLIDE_FONT;
						
						sprite[index].was_knocked_down = true;
						 
						if(j == 0)     
						{
							memset(VG_1_MovesList, 0, sizeof(VG_1_MovesList)); 
							VG_1_MOVE_ACTIVE = true;
						} 
						if(j == 1)  
						{ 
							memset(VG_2_MovesList, 0, sizeof(VG_2_MovesList)); 
							VG_2_MOVE_ACTIVE = true;
						}

					   if(VG_finished_round == false)
						   VG_slowmo_timer = 0;
					        
					   sprite[index].on_ladder = false;
					   sprite[index].pain = false; 
					   sprite[index].knockdown = false;
					   sprite[index].electrocute = false;

					   sprite[index].y = VG_START_Y;
					   sprite[index].z = sprite[index].y + inc_y;
				   } 
			   }           
			     
			   sprite[index].walking_backwards = false; 
	               
			   // Basic Animation system.... 
			   if(VG_finished_round == false || (index == 2 && VG_1_HEALTH > 0 ) || (index == 3 && VG_2_HEALTH > 0 ) )
			   if(VG_THROWING == false)
			   if(VG_displaying_win == false) 
			   if(VG_intro_sequence >= 2)   
		       if(VG_MOVE_ACTIVE == false)    
			   if(temp_VG_DEFEATED == false)  
			   if(sprite[index].anim_state != ONCE && sprite[index].anim_state != NO_ANIM)
			   {
				   if(temp_VG_DOWN_pressed == false)      
				   if(sprite[index].jumping == false)    
				   if(sprite[index].knockdown == false)
				   if(temp_VG_RIGHT_pressed == true || temp_VG_LEFT_pressed == true)
				   {
					   if(temp_VG_LEFT_pressed == true && sprite[index].movement == LEFT)
						   sprite[index].walking_backwards = false;
					   if(temp_VG_LEFT_pressed == true && sprite[index].movement == RIGHT)
						   sprite[index].walking_backwards = true;

					   if(temp_VG_RIGHT_pressed == true && sprite[index].movement == LEFT)
						   sprite[index].walking_backwards = true;
					   if(temp_VG_RIGHT_pressed == true && sprite[index].movement == RIGHT)
						   sprite[index].walking_backwards = false;

					   if(sprite[index].handcuffed == false)
						   Set_Sprite(index, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Walk...
					   else
						   Set_Sprite(index, 6, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Handcuffed walk...
				   } 
				   else   
				   { 
					   if(VG_BLOCKING == false)  
					   {
						  if(sprite[index].handcuffed == false)
						      Set_Sprite(index, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Idle...
						  else
						      Set_Sprite(index, 51, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Handcuffed Idle...
					   }
					   else
						  Set_Sprite(index, 21, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Standing block...
				   }
				    
				   if(temp_VG_DOWN_pressed == true)   
				   if(sprite[index].status != VG_BLOCK_FONT && sprite[index].status != VG_BLOCKDOWN_FONT)
				   {
					   if(VG_BLOCKING == false) 
					   {
						  if(sprite[index].handcuffed == false)
						      Set_Sprite(index, 45, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Crouch...
						  else
						      Set_Sprite(index, 58, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Crouch...
					   }
					   else
						  Set_Sprite(index, 22, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Crouch/block...
				   }
				     
			   } 

				// Restrain sprites against eachother...    
			    if(VG_THROWING == false)
			    if(VG_finished_round == false)
			    if((sprite[index].jumping == false && sprite[other_index].jumping == false)  
			    || (sprite[index].jumping == true && sprite[other_index].jumping == true) ) 
				{
					inc_x = sprite[index].w - sprite[index].x;     

					if(sprite[index].movement == RIGHT)
						mid_x = sprite[index].w + sprite[index].box_width;
					else
						mid_x = sprite[index].w; 

					if(mid_x >= sprite[other_index].w && (mid_x < sprite[other_index].w + sprite[other_index].box_width))
					{
						if(sprite[index].movement == RIGHT)  
							sprite[index].w = sprite[other_index].w - sprite[index].box_width; 
						else
							sprite[index].w = sprite[other_index].w + sprite[other_index].box_width;

						sprite[index].x = sprite[index].w - inc_x;
					}
				}

				// Restrain sprites against screen edges...
				VG_Restrain_sprite(index, j);

			   // Restrain the camera...
				 
			   mid_x = sprite[index].x + sprite[index].width/2;  
			   tar_x = sprite[other_index].x + sprite[other_index].width/2;  

			   distance = Node_Distance1(mid_x, VG_START_Y, tar_x, VG_START_Y);

			   half_distance = distance / 2.0f;     
			    
  		       if(VG_DONT_MOVE_CAMERA == false)  
			   if(distance < screen_limit)        
			   if(mid_x < tar_x) 
				   camX = -(sprite[index].x + sprite[index].width/2 + half_distance);
			   else  
				   camX = -(sprite[other_index].x + sprite[other_index].width/2 + half_distance);
		     
			   camY = 0.0f - ((sprite[index].y - VG_START_Y)/10.0f);  

			   if(VG_SHAKE_CAMERA == true)  
			   {

				   temp_VG_shake_strength = VG_shake_strength;

				   if((int)TimerGetTime() > VG_shake_length_timer-(VG_SHAKE_CAMERA_LENGTH/2))
				   {
					   temp_VG_shake_strength = VG_shake_strength * 0.50f;    
				   }

				   if(VG_SHAKE_UP == 1)  
					   camY += (temp_VG_shake_strength/2);  
				   if(VG_SHAKE_UP == 2)   
					   camY += temp_VG_shake_strength;   
				   if(VG_SHAKE_UP == 3)   
					   camY +=(temp_VG_shake_strength/2);  

				   if((int)TimerGetTime() > VG_shake_timer)
				   {

					   VG_shake_strength *= 0.90f;    

					   VG_SHAKE_UP++;
					    
					   if(VG_SHAKE_UP >= 4) 
						   VG_SHAKE_UP = 0;

					   if(VG_SLOWMO == true)
						   VG_shake_timer = (int)TimerGetTime() + 50;
					   else
						   VG_shake_timer = (int)TimerGetTime() + 35;
				   }

				   if((int)TimerGetTime() > VG_shake_length_timer)
					   VG_SHAKE_CAMERA = false;
			   }
		       
			   if(-camX < sprite[VG_GROUND_INDEX].x + VG_SCREEN_EDGE)    
				   camX = -(sprite[VG_GROUND_INDEX].x + VG_SCREEN_EDGE); 

			   if(-camX > sprite[VG_GROUND_INDEX].x + sprite[1].width - VG_SCREEN_EDGE)
				   camX = -(sprite[VG_GROUND_INDEX].x + sprite[1].width - VG_SCREEN_EDGE); 

			   sprite[4].x = VG_LAYER1_X - (camX/6); // Fg... 

			   sprite[VG_SCROLL_INDEX].x = VG_LAYER1_X - (camX/8);  // 2 + (0-14)...
			   sprite[VG_SCROLL_INDEX+1].x = VG_LAYER1_X - (camX/12);  // 2 + (0-14)... 
			   sprite[VG_SCROLL_INDEX+2].x = VG_LAYER1_X - (camX/16);  // 2 + (0-14)...
			   sprite[VG_SCROLL_INDEX+3].x = VG_LAYER1_X - (camX/20);  // 2 + (0-14)...
			   sprite[VG_SCROLL_INDEX+4].x = VG_LAYER1_X - (camX/30);  // 2 + (0-14)...
			   sprite[VG_SCROLL_INDEX+5].x = VG_LAYER1_X - (camX/40);  // 2 + (0-14)...
			   sprite[VG_SCROLL_INDEX+6].x = VG_LAYER1_X - (camX/50);  // 2 + (0-14)...
			
			   sprite[VG_SCROLL_INDEX+7].x = VG_LAYER1_X;  // 2 + (0-14)... 

			   sprite[VG_SCROLL_INDEX+8].x = VG_LAYER1_X + (camX/50);  // 2 + (0-14)...
			   sprite[VG_SCROLL_INDEX+9].x = VG_LAYER1_X + (camX/45);  // 2 + (0-14)...
			   sprite[VG_SCROLL_INDEX+10].x = VG_LAYER1_X + (camX/40);  // 2 + (0-14)...
			   sprite[VG_SCROLL_INDEX+11].x = VG_LAYER1_X + (camX/30);  // 2 + (0-14)...
			   sprite[VG_SCROLL_INDEX+12].x = VG_LAYER1_X + (camX/25);  // 2 + (0-14)...
			   sprite[VG_SCROLL_INDEX+13].x = VG_LAYER1_X + (camX/20);  // 2 + (0-14)...

			    
			   sprite[1].x = VG_LAYER1_X + (camX/20); // Bg...  
			   sprite[7].x = sprite[1].x; // Top section of Bg...

			   if(scene == VG_MINSO)  
			   {
					sprite[14].x = VG_LAYER1_X + VG_clock_offset + (camX/15); // Ticket...
					sprite[15].x = VG_LAYER1_X + VG_clock2_offset + (camX/15); // Ticket...
			   }
			   sprite[0].x = VG_LAYER1_X + (camX/7); // Far Bg...


			/*	   temp_scroll_amount = 4;    

				   for(int i = VG_SCROLL_INDEX ;i < VG_SCROLL_INDEX + 14;i++) 
				   {
				       sprite[i].x = VG_LAYER1_X - (camX / (temp_scroll_amount+2));  // 2 + (0-14)...
					   temp_scroll_amount++; 

				   }*/

			   if(scene == VG_MINSO)  
				   sprite[13].x = sprite[0].x + billboard_offsetX;    

			   if(VG_BACKGROUND == VG_REESE || VG_BACKGROUND == VG_SHRINE) 
				   sprite[13].x = VG_LAYER1_X + (camX/15); 
			    
			   if(scene == 5)
				   sprite[13].x = VG_SCREEN_X + (camX/10);
		    
		   } // End of J loop... 
		    

	   }
		
    // ******************************************************************************//
    //                            6-1  (CHARACTER SELECT)                            //
    // ******************************************************************************//
				                 
       // Title Screen Stuff...  
       if(!mode)      
       if(episode == 6 && scene == 1)          
       {           

		   if(next_scene == false)
		   if((int)TimerGetTime() > VG_HUD_1_BACK_TIMER)
		   if(VG_AI_active == false || vg_selected_character == false)
		   if(VG_1_HUD_BACK == true)      
		   {     
			     
			   if(VG_GAME_MODE == VG_VERSUS_MODE && VG_PLAYER1_SELECTED == true)
			   {
			       VG_PLAYER1_SELECTED = false;
				   VG_1_HUD_BACK = false; 
				   VG_1_HUD_GO = false;	
				   VG_HUD_1_BACK_TIMER = (int)TimerGetTime() + 250; 
				   vg_selected_character = false;

				   temp_bottomrow_index = VG_1_SELECTED + 2;

				   if (VG_1_SELECTED == VG_SHO)
					   temp_bottomrow_index = 26;
				   if (VG_1_SELECTED == VG_TIA)
					   temp_bottomrow_index = 27;
				   if (VG_1_SELECTED == VG_SAIZO)
					   temp_bottomrow_index = 28;

				   if(REPLACE_SANG_WITH_KENNEDY == 0)
				   if (VG_1_SELECTED == VG_SANG)
					   temp_bottomrow_index = 29;
				   if(REPLACE_SANG_WITH_KENNEDY == 1)
				   if (VG_1_SELECTED == VG_KENNEDY)
					   temp_bottomrow_index = 29;


				   if(temp_bottomrow_index >= 0 && temp_bottomrow_index < TOTAL_NO_SPRITES)
				   if((VG_1_SELECTED != VG_2_SELECTED) || VG_PLAYER2_SELECTED == false)
				   {
					   Set_Sprite(temp_bottomrow_index, sprite[temp_bottomrow_index].base_anim, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
				   }

			   }
			   else 
			   { 
				   VG_HUD_1_BACK_TIMER = (int)TimerGetTime() + 250;

				   VG_1_HUD_BACK = false;

				   VG_reset_input();     
			     
				   vg_next_episode = 0;    
				   vg_next_scene    = 1;  

				   if(VG_GAME_MODE != VG_VERSUS_MODE)
					   VG_BACK_TO_SELECTION = true;

				   next_scene = true;  
			   }
				  
		   }	   
		    
		   if (next_scene == false)
			if (VG_2_HUD_BACK == true) 
			{
				if (VG_GAME_MODE == VG_VERSUS_MODE && VG_PLAYER2_SELECTED == true)
				{
					VG_PLAYER2_SELECTED = false;
					VG_2_HUD_BACK = false;
					vg_selected_character = false;

					temp_bottomrow_index = VG_2_SELECTED + 2;

					if (VG_2_SELECTED == VG_SHO)
						temp_bottomrow_index = 26;
					if (VG_2_SELECTED == VG_TIA)
						temp_bottomrow_index = 27;
					if (VG_2_SELECTED == VG_SAIZO)
						temp_bottomrow_index = 28;

					if(REPLACE_SANG_WITH_KENNEDY == 0)
					if (VG_2_SELECTED == VG_SANG)
						temp_bottomrow_index = 29;
					if(REPLACE_SANG_WITH_KENNEDY == 1)
					if (VG_2_SELECTED == VG_SANG)
						temp_bottomrow_index = 29;

					if (temp_bottomrow_index >= 0 && temp_bottomrow_index < TOTAL_NO_SPRITES)
					if ((VG_1_SELECTED != VG_2_SELECTED) || VG_PLAYER1_SELECTED == false)
					{
						Set_Sprite(temp_bottomrow_index, sprite[temp_bottomrow_index].base_anim, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
					}

				}
			}


		   if(VG_GAME_MODE != VG_STORY_MODE) 
		   {

			   if(VG_PLAYER1_SELECTED == false)  
				   VG_IS_AN_ALTER_P1 = false;
			   if(VG_PLAYER2_SELECTED == false) 
				   VG_IS_AN_ALTER_P2 = false;

			   VG_HAS_ALTER_CHAR_SELECT = false;

			   if(VG_CHARACTER_LOCKS[VG_1_SELECTED] == 1)
				   VG_HAS_ALTER_CHAR_SELECT = true;

			   if(VG_PLAYER1_SELECTED == false) 
			   if(VG_CHARACTER_LOCKS[VG_1_SELECTED] == 1)
			   if(VG_1_BLOCKING == true || VG_1_THROW != VG_RESET)
				   VG_IS_AN_ALTER_P1 = true;
			   else
				   VG_IS_AN_ALTER_P1 = false;

			   if(VG_PLAYER2_SELECTED == false)  
			   if(VG_CHARACTER_LOCKS[VG_2_SELECTED] == 1)
			   if(VG_2_BLOCKING == true || VG_2_THROW != VG_RESET)
				   VG_IS_AN_ALTER_P2 = true;
			   else
				   VG_IS_AN_ALTER_P2 = false;
		   }

		   // Setup correct faces...
		   if(VG_IS_AN_ALTER_P1 == false)
			   sprite[1].id = 11;
		   if(VG_IS_AN_ALTER_P2 == false)
			   sprite[12].id = 11;

		   if(VG_1_SELECTED == VG_2_SELECTED)
			   sprite[12].id = 12; 

		   // Setup alter faces...
		   if(VG_IS_AN_ALTER_P1 == true)
			   sprite[1].id = 13; 

		   if(VG_IS_AN_ALTER_P2 == true)
			   sprite[12].id = 13; 


		   // SHO & TIA are on seperate spritesheet...
		   if(VG_1_SELECTED == VG_SHO)
			   sprite[1].id = 14;
		   if (VG_2_SELECTED == VG_SHO)
			   sprite[12].id = 14;

		   if (VG_1_SELECTED == VG_TIA)
			   sprite[1].id = 14;
		   if (VG_2_SELECTED == VG_TIA)
			   sprite[12].id = 14;

		   if(VG_1_SELECTED == VG_SAIZO)
			   sprite[1].id = 14;
		   if (VG_2_SELECTED == VG_SAIZO)
			   sprite[12].id = 14;

		   if(REPLACE_SANG_WITH_KENNEDY == 1)
		   if(VG_1_SELECTED == VG_KENNEDY)
			   sprite[1].id = 14;
		   if (VG_2_SELECTED == VG_KENNEDY)
			   sprite[12].id = 14;

		   if (VG_2_SELECTED == VG_TIA || VG_2_SELECTED == VG_SHO || VG_2_SELECTED == VG_SAIZO || VG_2_SELECTED == VG_KENNEDY)
		   if(VG_1_SELECTED == VG_2_SELECTED)
			   sprite[12].id = 15;

		   if(title_sequence == 0)      
		   {
			    stored_width = sprite[1].width;
				stored_height = sprite[1].height;

				stored_scale_Y = sprite[1].y;

			    sprite[4].x = sprite[3].x; // Align moving grid to box...
			    
			    // Fix offset so both line up correctly...
			    sprite[1].y = sprite[12].y;

			    vg_van_trail_timer = 0;

			    memset(VG_1_arrests, 0, sizeof(VG_1_arrests) );
			    memset(VG_2_arrests, 0, sizeof(VG_2_arrests) );

				VG_1_arrests_count = 0;
				VG_2_arrests_count = 0;

			    memset(VG_1_perfects, 0, sizeof(VG_1_perfects) );
			    memset(VG_2_perfects, 0, sizeof(VG_2_perfects) );

				VG_1_perfect_count = 0;
				VG_2_perfect_count = 0;

			    VG_voice_delay = (int)TimerGetTime() + 500;

			    sprite[1].mov_x = sprite[1].x;
				sprite[12].mov_x = sprite[12].x; 

			    VG_1_WINS = 0;
			    VG_2_WINS = 0;
				        
			    VG_ROUND = 1; 

				sprite[24].alpha = 0.0f; // Cop Car/Bike...

				if(VG_AI_active == true && vg_selected_character == true) 
				{

					if(VG_1_CHARACTER == VG_YOHAN || VG_1_CHARACTER == VG_JAE
					|| VG_1_CHARACTER == VG_GUN || VG_1_CHARACTER == VG_HYUK
					|| VG_1_CHARACTER == VG_SANG || VG_1_CHARACTER == VG_KENNEDY)
					{
						sprite[24].base_anim = 6; // car...
						vg_shout_sfx = true;
					}
					else
					{
						sprite[24].base_anim = 4; // car...
						vg_siren_sfx = true;
					}

				}
				     
				// Player 1 name...
				new_counter[1].alpha = 1.0f;            
				new_counter[1].id = 0;           
				new_counter[1].x = -0.16f;              
				new_counter[1].y = 0.36f; 
				new_counter[1].type = 0;  // Large Font...
				new_counter[1].right = false; 
			         
				sprintf( new_counter[1].word, "");  

				if(VG_GAME_MODE == VG_VERSUS_MODE)
					sprintf( new_counter[1].word, "VERSUS BATTLE^");   
				else
					sprintf( new_counter[1].word, "PLAYER SELECT^");   

			    if(VG_GAME_MODE == VG_VERSUS_MODE)
				{

					if(VG_1_Vs_wins < 10)
						sprintf( vg_temp_1_wins, "0%i", VG_1_Vs_wins);
					else
						sprintf( vg_temp_1_wins, "%i", VG_1_Vs_wins);

					if(VG_2_Vs_wins < 10)
						sprintf( vg_temp_2_wins, "0%i", VG_2_Vs_wins);
					else
						sprintf( vg_temp_2_wins, "%i", VG_2_Vs_wins);

					if(VG_Vs_draws < 10)
						sprintf( vg_temp_draws, "0%i", VG_Vs_draws);
					else
						sprintf( vg_temp_draws, "%i", VG_Vs_draws);

					sprintf( new_counter[2].word, "WIN  LOSE  DRAW"); 
			  
					new_counter[2].alpha = 1.0f;                     
					new_counter[2].id = 2;     
		       
					new_counter[2].type = 0;  // Large Font...  
					new_counter[2].right = false;   
			     
					if (screen_mode == SCREEN_NORMAL) // 4:3
						new_counter[2].x = -0.45f;              
					else
						new_counter[2].x = -0.55f;


					new_counter[2].y = 0.26f;    	          

					new_counter[2].w = new_counter[2].x - 0.026f;   
					new_counter[2].z = new_counter[2].y - 0.015f;
			     
					new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
					new_counter[2].box_height = new_counter[2].height - 0.015f;	

					sprintf( new_counter[3].word, " %s   %s    %s", vg_temp_1_wins, vg_temp_2_wins, vg_temp_draws); 
			  
					new_counter[3].alpha = 1.0f;                     
					new_counter[3].id = 2;     
		       
					new_counter[3].type = 0;  // Large Font...  
					new_counter[3].right = false;   
			     
					if (screen_mode == SCREEN_NORMAL) // 4:3
						new_counter[3].x = -0.45f;              
					else
						new_counter[3].x = -0.55f;

					new_counter[3].y = new_counter[2].y - 0.06f;    	          

					new_counter[3].w = new_counter[3].x - 0.026f;   
					new_counter[3].z = new_counter[3].y - 0.015f;
			     
					new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
					new_counter[3].box_height = new_counter[3].height - 0.015f;	

					sprintf( new_counter[4].word, "WIN  LOSE  DRAW"); 
			   
					new_counter[4].alpha = 1.0f;                     
					new_counter[4].id = 2;     
		       
					new_counter[4].type = 0;  // Large Font...  
					new_counter[4].right = false;   
			     
					if (screen_mode == SCREEN_NORMAL) // 4:3
						new_counter[4].x = 0.08f;              
					else
						new_counter[4].x = 0.15f;

					new_counter[4].y = 0.26f;

					new_counter[4].w = new_counter[4].x - 0.026f;   
					new_counter[4].z = new_counter[4].y - 0.015f;
			     
					new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
					new_counter[4].box_height = new_counter[4].height - 0.015f;	

					sprintf( new_counter[5].word, " %s   %s    %s", vg_temp_2_wins, vg_temp_1_wins, vg_temp_draws); 
			  
					new_counter[5].alpha = 1.0f;                     
					new_counter[5].id = 2;     
		       
					new_counter[5].type = 0;  // Large Font...  
					new_counter[5].right = false;   
			     
					if (screen_mode == SCREEN_NORMAL) // 4:3
						new_counter[5].x = 0.08f;
					else
						new_counter[5].x = 0.15f;

					new_counter[5].y = new_counter[4].y - 0.06f;    	             

					new_counter[5].w = new_counter[5].x - 0.026f;   
					new_counter[5].z = new_counter[5].y - 0.015f;
			     
					new_counter[5].box_width = strlen(new_counter[5].word)   *  0.026f;
					new_counter[5].box_height = new_counter[5].height - 0.015f;	

				}
			 
				sprintf( new_counter[7].word, "^¦-§ MOVE  Z: SELECT ESC: BACK"); 

				new_counter[7].alpha = 1.0f;                  
				new_counter[7].id = 2;        
				   
				new_counter[7].type = 1;  // Small Font...
				new_counter[7].right = false;
				      
				new_counter[7].x = -0.31f;                        
				new_counter[7].y = -0.33f;           

				new_counter[7].w = new_counter[7].x - 0.026f;   
				new_counter[7].z = new_counter[7].y - 0.015f;

				new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
				new_counter[7].box_height = new_counter[7].height - 0.015f;	

				if(VG_AI_active == true && vg_selected_character == true) 
				{
					new_counter[7].alpha = 0.0f;
					new_counter[1].alpha = 0.0f; 
				} 

				if(TURN_OFF_INGAME_HELP == 1)
					new_counter[7].alpha = 0.0f;

				VG_1_WAS_ARRESTED = false;
				VG_2_WAS_ARRESTED = false;

				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false; 

				VG_1_HUDUP = false;
				VG_2_HUDUP = false;

				VG_1_HUDLEFT = false;
				VG_2_HUDLEFT = false; 

				VG_1_HUDRIGHT = false;
				VG_2_HUDRIGHT = false;

				VG_1_PUNCH = 0;
				VG_1_PUNCH2 = 0;
				VG_1_KICK = 0;
				VG_1_KICK2 = 0;

				VG_2_PUNCH = 0;
				VG_2_PUNCH2 = 0;
				VG_2_KICK = 0;
				VG_2_KICK2 = 0;

			   distance = 0.08f;       

			   if (VG_GAME_MODE == VG_STORY_MODE)
			   {
				   sprite[26].alpha = 0.0f;
				   sprite[27].alpha = 0.0f;
				   sprite[28].alpha = 0.0f;
				   sprite[29].alpha = 0.0f;

				   sprite[2].y -= sprite[2].height/2;
				   sprite[6].y -= sprite[6].height/2;

			   }
			   else
			   {
				   if (VG_ACTIVATE_BREAKERS == false)
				   {
					   sprite[2].y = sprite[6].y;
					   sprite[6].y = sprite[26].y;

					   object emptySprite = { 0 };
					   sprite[26] = emptySprite;
					   sprite[27] = sprite[26];
					   sprite[28] = sprite[26];
					   sprite[29] = sprite[26];
				   }
			   }
			   
#ifdef SWITCH
			   //printf("VGGAMEMODE = %d\n", VG_VERSUS_MODE);
				if (VG_GAME_MODE == VG_VERSUS_MODE)
				{
					IControlSetup(1, 2);
					while (IControlConnected(CDEV_PAD_1) == ICTRL_NONE && IControlConnected(CDEV_PAD_2) == ICTRL_NONE)
					{
						//printf("While before loop\n");
						IControlSetup(1, 2);
						IControlUpdate();
					}
				}
#endif

			   sprite[3].y = sprite[2].y; 
			   sprite[4].y = sprite[2].y;   
			   sprite[5].y = sprite[2].y;

			   sprite[3].x = sprite[2].x + sprite[2].width - distance;
			   sprite[4].x = sprite[3].x + sprite[3].width - distance;
			   sprite[5].x = sprite[4].x + sprite[4].width - distance;

			   sprite[7].y = sprite[6].y;
			   sprite[8].y = sprite[6].y;
			   sprite[9].y = sprite[6].y;

			   sprite[6].x = sprite[2].x;
			   sprite[7].x = sprite[6].x + sprite[6].width - distance;
			   sprite[8].x = sprite[7].x + sprite[7].width - distance;
			   sprite[9].x = sprite[8].x + sprite[8].width - distance;

			   sprite[27].y = sprite[26].y;
			   sprite[28].y = sprite[26].y;
			   sprite[29].y = sprite[26].y;

			   sprite[26].x = sprite[2].x; 
			   sprite[27].x = sprite[26].x + sprite[26].width - distance;
			   sprite[28].x = sprite[27].x + sprite[27].width - distance;
			   sprite[29].x = sprite[28].x + sprite[28].width - distance;


			   if(REPLACE_SANG_WITH_KENNEDY)
				   sprite[33].alpha = 0.0f;

			   // Turn off Trainer pin by default...
			   sprite[23].alpha = 0.0f;
			    
			   // Turn off Sang pin by default...
			   sprite[22].alpha = 0.0f;

			   if (VG_GAME_MODE == VG_VERSUS_MODE)
			   {
				   sprite[30].alpha = 0.0f;
				   sprite[31].alpha = 0.0f;
				   sprite[32].alpha = 0.0f;
				   sprite[33].alpha = 0.0f;
			   }

			   if (vg_selected_character == false)
			   {
				   VG_1_SELECTED = 0;

				   VG_2_SELECTED = 3;
			   }

			   VG_PLAYER1_SELECTED = false;   

			   sprite[25].alpha = 0.0f; // Shrine...

			   if(VG_AI_active == true)
			   {
				   sprite[12].alpha = 0.0f;
				   VG_PLAYER2_SELECTED = true;

				   if(vg_selected_character == true) 
				   {
				       VG_PLAYER1_SELECTED = true;
					   title_timer = (int)TimerGetTime() + 4000;
				   }

				   if(VG_GAME_MODE == VG_ARCADE_MODE)
				   if(vg_continued_arcade == false)
				   {
					   // Useful for testing arcade mode...
					/*   if (vg_selected_character == false)
					   {
						   VG_DEFEATED_GUYS[0] = VG_SIU;
						   VG_DEFEATED_GUYS[1] = VG_GUN;
						   VG_DEFEATED_GUYS[2] = VG_HYUK;
						   VG_DEFEATED_GUYS[3] = VG_GYEONG;
						   VG_DEFEATED_GUYS[4] = VG_REESE;
						   VG_DEFEATED_GUYS[5] = VG_MINSO;
						   VG_DEFEATED_GUYS[6] = VG_YOHAN;
						//   VG_DEFEATED_GUYS[7] = VG_JAE;

						   vg_defeat_count = 7;
					   }*/

						next_list_count=0;  
					    
						// Find a new fighter...
						for(int j = 0;j < 8;j++) 
						{ 
							skip_this = false;

							for(int i = 0;i < 8;i++)
							{
								if(j == VG_DEFEATED_GUYS[i])
									skip_this = true;
							}
							if(skip_this == false)
							if(next_list_count >= 0 && next_list_count < 15)
							{
								next_list[next_list_count] = j;
								next_list_count++;
							} 

						}      

						// For testing against Sang... 
					//	next_list_count = 0;
						// testing only...

						if(next_list_count == 0)  
						{ 
							if(VG_SUBBOSS == 0)
								VG_NEXT_FIGHTER = VG_SHO;      
							if(VG_SUBBOSS == 1)
								VG_NEXT_FIGHTER = VG_TIA;      
							if(VG_SUBBOSS == 2)
								VG_NEXT_FIGHTER = VG_SAIZO;  

							if(REPLACE_SANG_WITH_KENNEDY == 0)
							if (VG_SUBBOSS == 3 )
							{
								VG_NEXT_FIGHTER = VG_SANG;
								sprite[22].alpha = 1.0f;
							}
							
							if (REPLACE_SANG_WITH_KENNEDY == 1)
							{
								if (VG_SUBBOSS == 3)
								{
									VG_NEXT_FIGHTER = VG_KENNEDY;
									sprite[33].alpha = 1.0f;
								}
								if (VG_SUBBOSS == 4)
								{
									VG_NEXT_FIGHTER = VG_SANG;
									sprite[22].alpha = 1.0f;
								}
							}


							VG_SUBBOSS++;
						} 
						else 
						{
							if(next_list_count >= 0 && next_list_count < 15)
								VG_NEXT_FIGHTER = next_list[rand()%next_list_count];

							sprite[22].alpha = 0.0f;
						}

						VG_map_next_point = (VG_NEXT_FIGHTER+14);

						if (VG_NEXT_FIGHTER == VG_SANG)
							VG_map_next_point = 22;
						if (VG_NEXT_FIGHTER == VG_SHO)
							VG_map_next_point = 30;
						if (VG_NEXT_FIGHTER == VG_SAIZO)
							VG_map_next_point = 31;
						if (VG_NEXT_FIGHTER == VG_TIA)
							VG_map_next_point = 32;
						if (VG_NEXT_FIGHTER == VG_KENNEDY)
							VG_map_next_point = 33;
				    
						if(VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_DUELLING)
						{
							VG_map_next_point = 25;
							sprite[25].alpha = 1.0f; // Shrine pin...
							sprite[22].alpha = 0.0f; // Sang's pin...
						} 

				    }
				    
					if(VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_DUELLING)
						sprite[25].alpha = 1.0f;
				    
				    vg_continued_arcade = false;

					if(VG_GAME_MODE == VG_STORY_MODE)
					if(VG_CURRENT_STORY_SCENE >= 0 && VG_CURRENT_STORY_SCENE < 20)
					{
						// VG_GYEONG   0  - 14               
						// VG_SIU      1  - 15                    
						// VG_MINSO    2  - 16
						// VG_REESE    3  - 17              
						// VG_YOHAN    4  - 18                 
						// VG_JAE      5  - 19      
						// VG_GUN      6  - 20
						// VG_HYUK     7  - 21 
						// VG_SHO      8  - 22 - SANG...
						// VG_TIA      9  - 23 - Dojo?
						// VG_SAIZO    10 - 24
						// VG_KENNEDY  11 - 25
						// VG_SANG     12 - 26
						// VG_TRAINER  13 - 27

						VG_NEXT_FIGHTER = VG_story_characters[VG_CURRENT_STORY_SCENE];
						VG_map_next_point = (VG_story_background[VG_CURRENT_STORY_SCENE] + 14); // 14 - 26...

						sprite[23].alpha = 1.0f; // Sabu pin...

						sprite[30].alpha = 0.0f; // Sho pin...
						sprite[31].alpha = 0.0f; // Saizo pin...
						sprite[32].alpha = 0.0f; // Tia pin...
						sprite[33].alpha = 0.0f; // Kennedy pin...

						if (VG_story_background[VG_CURRENT_STORY_SCENE] == VG_TRAINER)
							VG_map_next_point = 23;
						if (VG_story_background[VG_CURRENT_STORY_SCENE] == VG_SANG)
							VG_map_next_point = 22;

						// Turn on/off Sang's pin...
						if(VG_story_background[VG_CURRENT_STORY_SCENE] == VG_SANG)    
							sprite[22].alpha = 1.0f;
						else
							sprite[22].alpha = 0.0f;

					}
		  
			   }    
			   else
			   {
				   VG_PLAYER1_SELECTED = false; 
				   VG_PLAYER2_SELECTED = false;
			   }

			   // For demo turn off characters, except minso, hyuk...
			   if(!(VG_GAME_MODE == VG_ARCADE_MODE && vg_selected_character == true))
			   if(VG_STEAM_DEMO == 1)
			   {
				   // Gyeong
					Set_Sprite(2, 16, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
					Set_Sprite(14, sprite[14].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

					// Siu
					Set_Sprite(3, 17, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);  
					Set_Sprite(15, sprite[15].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

					// Minso
			//		Set_Sprite(4, 18, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
					Set_Sprite(16, sprite[16].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

					// Reese
					Set_Sprite(5, 19, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
					Set_Sprite(17, sprite[17].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

					// Yohan
					Set_Sprite(6, 20, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
					Set_Sprite(18, sprite[18].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

					// Jae
					Set_Sprite(7, 21, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
					Set_Sprite(19, sprite[19].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

					// Gun
					Set_Sprite(8, 22, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
					Set_Sprite(20, sprite[20].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
					 
					// Hyuk
			//		Set_Sprite(9, 23, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
					Set_Sprite(21, sprite[21].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

					// Sang
					Set_Sprite(22, sprite[22].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

					// Sabu
					Set_Sprite(23, sprite[23].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

			   }

			   if(VG_AI_active == true && vg_selected_character == true)
			   {
				   sprite[10].alpha = 0.0f; 
				   sprite[11].alpha = 0.0f; 

				   // Make all pins grey for story mode...
				   if(VG_GAME_MODE == VG_STORY_MODE)
				   for(int i = 14;i < 24;i++) 
				   {
					   Set_Sprite(i, sprite[i].base_anim, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
				   }

				   Set_Sprite(30, sprite[30].base_anim, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
			       Set_Sprite(31, sprite[31].base_anim, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
				   Set_Sprite(32, sprite[32].base_anim, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
				   Set_Sprite(33, sprite[33].base_anim, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

				   // Grey out defeated opponents...
				   if(VG_GAME_MODE == VG_ARCADE_MODE)
				   for(int i = 0;i < 8;i++)
				   {
						if(VG_DEFEATED_GUYS[i]==VG_GYEONG)
						{
							Set_Sprite(2, sprite[2].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
							Set_Sprite(14, sprite[14].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Pin
							New_Sprite(sprite[2].x, sprite[2].y, sprite[2].x, sprite[2].y, 16, LOOP, sprite[2].width, sprite[2].height, sprite[2].width, sprite[2].height, 2, NON, 1.0f, 0, -1, 0, 0, sprite[2].id, 0, 0, 0, -1);
						}
						if(VG_DEFEATED_GUYS[i]==VG_SIU)
						{ 
							Set_Sprite(3, sprite[3].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
							Set_Sprite(15, sprite[15].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Pin
							New_Sprite(sprite[3].x, sprite[3].y, sprite[3].x, sprite[3].y, 16, LOOP, sprite[3].width, sprite[3].height, sprite[3].width, sprite[3].height, 2, NON, 1.0f, 0, -1, 0, 0, sprite[3].id, 0, 0, 0, -1);
						}
						if(VG_DEFEATED_GUYS[i]==VG_MINSO)
						{
							Set_Sprite(4, sprite[4].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
							Set_Sprite(16, sprite[16].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Pin
							New_Sprite(sprite[4].x, sprite[4].y, sprite[4].x, sprite[4].y, 16, LOOP, sprite[4].width, sprite[4].height, sprite[4].width, sprite[4].height, 2, NON, 1.0f, 0, -1, 0, 0, sprite[4].id, 0, 0, 0, -1);
						}
						if(VG_DEFEATED_GUYS[i]==VG_REESE)
						{
							Set_Sprite(5, sprite[5].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
							Set_Sprite(17, sprite[17].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Pin
							New_Sprite(sprite[5].x, sprite[5].y, sprite[5].x, sprite[5].y, 16, LOOP, sprite[5].width, sprite[5].height, sprite[5].width, sprite[5].height, 2, NON, 1.0f, 0, -1, 0, 0, sprite[5].id, 0, 0, 0, -1);
						}
						if(VG_DEFEATED_GUYS[i]==VG_YOHAN)
						{
							Set_Sprite(6, sprite[6].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
							Set_Sprite(18, sprite[18].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Pin
							New_Sprite(sprite[6].x, sprite[6].y, sprite[6].x, sprite[6].y, 16, LOOP, sprite[6].width, sprite[6].height, sprite[6].width, sprite[6].height, 2, NON, 1.0f, 0, -1, 0, 0, sprite[6].id, 0, 0, 0, -1);
						}
						if(VG_DEFEATED_GUYS[i]==VG_JAE)
						{
							Set_Sprite(7, sprite[7].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
							Set_Sprite(19, sprite[19].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Pin
							New_Sprite(sprite[7].x, sprite[7].y, sprite[7].x, sprite[7].y, 16, LOOP, sprite[7].width, sprite[7].height, sprite[7].width, sprite[7].height, 2, NON, 1.0f, 0, -1, 0, 0, sprite[7].id, 0, 0, 0, -1);
						}
						if(VG_DEFEATED_GUYS[i]==VG_GUN)
						{
							Set_Sprite(8, sprite[8].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
							Set_Sprite(20, sprite[20].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Pin
							New_Sprite(sprite[8].x, sprite[8].y, sprite[8].x, sprite[8].y, 16, LOOP, sprite[8].width, sprite[8].height, sprite[8].width, sprite[8].height, 2, NON, 1.0f, 0, -1, 0, 0, sprite[8].id, 0, 0, 0, -1);
						}
						if(VG_DEFEATED_GUYS[i]==VG_HYUK)
						{
							Set_Sprite(9, sprite[9].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
							Set_Sprite(21, sprite[21].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Pin
							New_Sprite(sprite[9].x, sprite[9].y, sprite[9].x, sprite[9].y, 16, LOOP, sprite[9].width, sprite[9].height, sprite[9].width, sprite[9].height, 2, NON, 1.0f, 0, -1, 0, 0, sprite[9].id, 0, 0, 0, -1);
						}

						if(VG_SUBBOSS > 1) // VG_SHO
						{
							Set_Sprite(26, sprite[26].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
							Set_Sprite(30, sprite[30].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Pin
							New_Sprite(sprite[26].x, sprite[26].y, sprite[26].x, sprite[26].y, 16, LOOP, sprite[26].width, sprite[26].height, sprite[26].width, sprite[26].height, 2, NON, 1.0f, 0, -1, 0, 0, sprite[26].id, 0, 0, 0, -1);

						}
						if(VG_SUBBOSS > 2) // VG_TIA
						{
							Set_Sprite(27, sprite[27].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
							Set_Sprite(32, sprite[32].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Pin
							New_Sprite(sprite[27].x, sprite[27].y, sprite[27].x, sprite[27].y, 16, LOOP, sprite[27].width, sprite[27].height, sprite[27].width, sprite[27].height, 2, NON, 1.0f, 0, -1, 0, 0, sprite[27].id, 0, 0, 0, -1);

						}
						if(VG_SUBBOSS > 3) // VG_SAIZO
						{
							Set_Sprite(28, sprite[28].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
							Set_Sprite(31, sprite[31].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Pin
							New_Sprite(sprite[28].x, sprite[28].y, sprite[28].x, sprite[28].y, 16, LOOP, sprite[28].width, sprite[28].height, sprite[28].width, sprite[28].height, 2, NON, 1.0f, 0, -1, 0, 0, sprite[28].id, 0, 0, 0, -1);

						} 
						if(VG_SUBBOSS > 4) // VG_KENNEDY
						{
							Set_Sprite(29, sprite[29].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
							Set_Sprite(33, sprite[33].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Pin
							New_Sprite(sprite[29].x, sprite[29].y, sprite[29].x, sprite[29].y, 16, LOOP, sprite[29].width, sprite[29].height, sprite[29].width, sprite[29].height, 2, NON, 1.0f, 0, -1, 0, 0, sprite[29].id, 0, 0, 0, -1);

						}

				   }

				/*   if (VG_GAME_MODE == VG_ARCADE_MODE)
				   for (int i = 26; i < 30; i++)
				   {

				   }*/


			   }  

			   title_sequence++;  
			      
			   vg_switch_p2_text = (int)TimerGetTime() + 2000;  
			   vg_switch_is_p2 = false;

			   if(VG_AI_active == false)   
			   {
				   sprite[22].alpha = 0.0f; // Sang pin...
				   title_sequence = 5;
			   }

			   if(VG_map_next_point >= 0 && VG_map_next_point < TOTAL_NO_SPRITES)
			   if(VG_AI_active == true && vg_selected_character == true)
			   {
				   sprite[24].x = sprite[VG_map_last_point].x; // Equals the car...
				   sprite[24].y = sprite[VG_map_last_point].y; // Equals the car...
				   sprite[24].alpha = 1.0f; // Equals the car...
				   
					mid_x = sprite[24].x+sprite[24].width/2; 
					mid_y = sprite[24].y+sprite[24].height/2; 

					tar_x = sprite[VG_map_next_point].x+sprite[VG_map_next_point].width/2; 
					tar_y = sprite[VG_map_next_point].y+sprite[VG_map_next_point].height/2; 

					angle = atan2(tar_y - mid_y, tar_x - mid_x);

					angle = (angle*180)/3.14f; 
             
					if(angle < 0)                       
						angle += 360;  

					sprite[24].angle = angle;

					Set_Sprite(24, sprite[24].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				   vg_amb_van_sfx = true;

				   title_timer = (int)TimerGetTime() + 500;
				   title_sequence = 2;  
			   }    
		   } // title_sequence == 0       
		    

			if(vg_switch_is_p2 == false) 
			if(VG_P1_USING == VG_KEYBOARD) 
			{ 
				if(VG_HAS_ALTER_CHAR_SELECT == false)
				{
					new_counter[7].x = -0.31f;
					sprintf( new_counter[7].word, "^%c-%c MOVE  %c: SELECT %c: BACK", VG_P1_UP_KEY_DSY, VG_P1_DOWN_KEY_DSY, VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
				}
				else
				{
					new_counter[7].x = -0.40f;
					sprintf( new_counter[7].word, "^%c-%c MOVE  %c: ALTER  %c: SELECT %c: BACK", VG_P1_UP_KEY_DSY, VG_P1_DOWN_KEY_DSY, VG_P1_THROW_KEY_DSY, VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
				}
			}
			else
			{ 
				if(VG_HAS_ALTER_CHAR_SELECT == false)
				{
					new_counter[7].x = -0.31f;
					sprintf( new_counter[7].word, "^¦-§ MOVE  ÷: SELECT ø: BACK");
				}
				else
				{
					new_counter[7].x = -0.40f;
					sprintf( new_counter[7].word, "^¦-§ MOVE  »: ALTER  ÷: SELECT ø: BACK");
				}

			}

		   if(VG_GAME_MODE == VG_ARCADE_MODE)
		   if(VG_AI_active == true && vg_selected_character == true)
		   if(VG_BATTLE_ROUND > 1)
		   {
			    if(VG_1_TOTAL_MINS <= 9)
				{
					if(VG_1_TOTAL_SECS <= 9)
						sprintf( new_counter[7].word, "^      $0%i-0%i$ ¿:%i  ã:%i", VG_1_TOTAL_MINS, VG_1_TOTAL_SECS, VG_1_TOTAL_perfects, VG_1_TOTAL_arrests);
					else
						sprintf( new_counter[7].word, "^      $0%i-%i$ ¿:%i  ã:%i", VG_1_TOTAL_MINS, VG_1_TOTAL_SECS, VG_1_TOTAL_perfects, VG_1_TOTAL_arrests);
				}
				else
				{
					if(VG_1_TOTAL_SECS <= 9)
						sprintf( new_counter[7].word, "^      $%i-0%i$ ¿:%i  ã:%i", VG_1_TOTAL_MINS, VG_1_TOTAL_SECS, VG_1_TOTAL_perfects, VG_1_TOTAL_arrests);
					else
						sprintf( new_counter[7].word, "^      $%i-%i$ ¿:%i  ã:%i", VG_1_TOTAL_MINS, VG_1_TOTAL_SECS, VG_1_TOTAL_perfects, VG_1_TOTAL_arrests);
				}

				new_counter[7].alpha = 1.0f;
		   }

		   if(VG_AI_active == false || vg_selected_character == false)
		   if(VG_voice_delay != -1)
		   if((int)TimerGetTime() > VG_voice_delay)
		   {
			   VG_destiny_sfx = true; 
			   VG_voice_delay = -1;
		   }

		   for(int i=0;i<2;i++) 
		   { 

			   if(i == 0) 
			   { 
				   if(VG_1_SELECTED+2 >= 0 && VG_1_SELECTED+2 < TOTAL_NO_SPRITES)
				   {
					   sprite[10].x = sprite[VG_1_SELECTED+2].x;
					   sprite[10].y = sprite[VG_1_SELECTED+2].y;
				   }
			   }
			        
			   if(VG_AI_active == false)       
			   if(i == 1) 
			   {
				   if(VG_2_SELECTED+2 >= 0 && VG_2_SELECTED+2 < TOTAL_NO_SPRITES)
				   {
					   sprite[11].x = sprite[VG_2_SELECTED+2].x;
					   sprite[11].y = sprite[VG_2_SELECTED+2].y;
				   }
			   }
		   } 

		   if (VG_1_SELECTED == VG_SHO)
		   {
			   sprite[10].x = sprite[26].x;
			   sprite[10].y = sprite[26].y;
		   }
		   if (VG_2_SELECTED == VG_SHO)
		   {
			   sprite[11].x = sprite[26].x;
			   sprite[11].y = sprite[26].y; 
		   } 

		   if (VG_1_SELECTED == VG_TIA)
		   {
			   sprite[10].x = sprite[27].x;
			   sprite[10].y = sprite[27].y;
		   }
		   if (VG_2_SELECTED == VG_TIA)
		   {
			   sprite[11].x = sprite[27].x;
			   sprite[11].y = sprite[27].y;
		   }

		   if (VG_1_SELECTED == VG_SAIZO)
		   {
			   sprite[10].x = sprite[28].x;
			   sprite[10].y = sprite[28].y;
		   }
		   if (VG_2_SELECTED == VG_SAIZO)
		   {
			   sprite[11].x = sprite[28].x;
			   sprite[11].y = sprite[28].y; 
		   } 

		   if (VG_1_SELECTED == VG_SANG)
		   {
			   sprite[10].x = sprite[29].x;
			   sprite[10].y = sprite[29].y;
		   }
		   if (VG_2_SELECTED == VG_SANG)
		   {
			   sprite[11].x = sprite[29].x;
			   sprite[11].y = sprite[29].y; 
		   } 

		   if (VG_1_SELECTED == VG_KENNEDY)
		   {
			   sprite[10].x = sprite[29].x;
			   sprite[10].y = sprite[29].y;
		   }
		   if (VG_2_SELECTED == VG_KENNEDY)
		   {
			   sprite[11].x = sprite[29].x;
			   sprite[11].y = sprite[29].y; 
		   } 

		   // Setup faces...
			Set_Sprite(1, (VG_1_SELECTED), PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
			Set_Sprite(12, (VG_2_SELECTED), PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

		   // SHO & TIA are on seperate sheet...
		   if (VG_1_SELECTED == VG_SHO)
			   Set_Sprite(1, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
		   if (VG_2_SELECTED == VG_SHO)
			   Set_Sprite(12, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

		   if (VG_1_SELECTED == VG_TIA)
			   Set_Sprite(1, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
		   if (VG_2_SELECTED == VG_TIA)
			   Set_Sprite(12, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

		   if (VG_1_SELECTED == VG_SAIZO)
			   Set_Sprite(1, 2, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
		   if (VG_2_SELECTED == VG_SAIZO)
			   Set_Sprite(12, 2, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

		   if(VG_1_SELECTED == VG_SANG)
			   Set_Sprite(1, 24, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
		   if(VG_2_SELECTED == VG_SANG)
			   Set_Sprite(12, 24, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
		   
		   if (REPLACE_SANG_WITH_KENNEDY == 0)
		   {
			   if (VG_1_SELECTED == VG_KENNEDY)
				   Set_Sprite(1, 24, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
			   if (VG_2_SELECTED == VG_KENNEDY)
				   Set_Sprite(12, 24, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
		   }
		   if (REPLACE_SANG_WITH_KENNEDY == 1)
		   {
			   if (VG_1_SELECTED == VG_KENNEDY)
				   Set_Sprite(1, 3, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
			   if (VG_2_SELECTED == VG_KENNEDY)
				   Set_Sprite(12, 3, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
		   }

		   // Selection boxes...
		   if(VG_PLAYER1_SELECTED == false)
		   { 
			   if(VG_1_SELECTED == VG_2_SELECTED && VG_GAME_MODE == VG_VERSUS_MODE)
			       Set_Sprite(10, 4, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Not Selected on single face...
			   else
			       Set_Sprite(10, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Not Selected and both on same face...
		   }
		   else
		   {
			   if(VG_1_SELECTED == VG_2_SELECTED && VG_GAME_MODE == VG_VERSUS_MODE)
			       Set_Sprite(10, 6, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Selected on single face...
			   else
			       Set_Sprite(10, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Selected and both on same face...
		   }
		    
		   if(VG_PLAYER2_SELECTED == false)
		   { 
			   if(VG_1_SELECTED == VG_2_SELECTED && VG_GAME_MODE == VG_VERSUS_MODE)
			       Set_Sprite(11, 5, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Not Selected on single face...
			   else
			       Set_Sprite(11, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Not Selected and both on same face...
		   } 
		   else 
		   {
			   if(VG_1_SELECTED == VG_2_SELECTED && VG_GAME_MODE == VG_VERSUS_MODE)
			       Set_Sprite(11, 7, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Selected on single face...
			   else
			       Set_Sprite(11, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Selected and both on same face...
		   }

		   // Turn off map and pins for vs mode...
		   if(VG_GAME_MODE == VG_VERSUS_MODE)
		   {
			   sprite[13].alpha = 0.0f;
			   sprite[14].alpha = 0.0f;
			   sprite[15].alpha = 0.0f;
			   sprite[16].alpha = 0.0f;
			   sprite[17].alpha = 0.0f;
			   sprite[18].alpha = 0.0f;
			   sprite[19].alpha = 0.0f;
			   sprite[20].alpha = 0.0f;
			   sprite[21].alpha = 0.0f;
			   sprite[22].alpha = 0.0f;
			   sprite[23].alpha = 0.0f;
		   }

		   // Player one selection...
			if(VG_PLAYER1_SELECTED == false) 
			if(VG_1_HUDDOWN == VG_PRESSED) 
			{
				if(VG_1_SELECTED <= 3 || ((VG_1_SELECTED == 4 || VG_1_SELECTED == 5 || VG_1_SELECTED == 6 || VG_1_SELECTED == 7) && VG_GAME_MODE != VG_STORY_MODE && VG_ACTIVATE_BREAKERS != false))
				{
					vg_title_move_sfx = true;
					VG_1_SELECTED+=4;
					sprite[1].x = sprite[1].mov_x - sprite[1].width;
					sprite[1].width = stored_width*SCALE_FACE_AMOUNTX;
					sprite[1].height = stored_height*SCALE_FACE_AMOUNTY;
					sprite[1].y = stored_scale_Y + ((stored_height * SCALE_FACE_AMOUNTY)/4);

					bump_index = VG_1_SELECTED + 2;

					if (VG_1_SELECTED == 8) // VG_SHO...
						bump_index = 26;
					if (VG_1_SELECTED == 9) // VG_TIA...
						bump_index = 27;
					if (VG_1_SELECTED == 10) // VG_SAIZO...
						bump_index = 28;
					if (VG_1_SELECTED == 11) // VG_KENNEDY...
						bump_index = 29;
					if (VG_1_SELECTED == 12) // VG_SANG...
						bump_index = 29;

					sprite[bump_index].bump_this = true;
					sprite[bump_index].bump_this_timer = (int)TimerGetTime() + 150;

					sprite[10].bump_this = true;
					sprite[10].bump_this_timer = (int)TimerGetTime() + 150;

				} 
				VG_1_HUDDOWN = false;
			} 
			if(VG_PLAYER1_SELECTED == false)
			if(VG_1_HUDUP == VG_PRESSED)  
			{
				if(VG_1_SELECTED > 3)  
				{
					vg_title_move_sfx = true;
					VG_1_SELECTED-=4;
					sprite[1].x = sprite[1].mov_x - sprite[1].width;
					sprite[1].width = stored_width*SCALE_FACE_AMOUNTX;
					sprite[1].height = stored_height*SCALE_FACE_AMOUNTY;
					sprite[1].y = stored_scale_Y + ((stored_height * SCALE_FACE_AMOUNTY)/4);

					bump_index = VG_1_SELECTED + 2;

					if (VG_1_SELECTED == 8) // VG_SHO...
						bump_index = 26;
					if (VG_1_SELECTED == 9) // VG_TIA...
						bump_index = 27;
					if (VG_1_SELECTED == 10) // VG_SAIZO...
						bump_index = 28;
					if (VG_1_SELECTED == 11) // VG_KENNEDY...
						bump_index = 29;
					if (VG_1_SELECTED == 12) // VG_SANG...
						bump_index = 29;

					sprite[bump_index].bump_this = true;
					sprite[bump_index].bump_this_timer = (int)TimerGetTime() + 150;

					sprite[10].bump_this = true;
					sprite[10].bump_this_timer = (int)TimerGetTime() + 150;
				}
				VG_1_HUDUP = false;
			} 
			if(VG_PLAYER1_SELECTED == false)
			if(VG_1_HUDLEFT == VG_PRESSED)
			{
				if(VG_1_SELECTED > 0 && VG_1_SELECTED != 4 && VG_1_SELECTED != 8)
				{ 
					vg_title_move_sfx = true; 
					VG_1_SELECTED--;
					sprite[1].x = sprite[1].mov_x - sprite[1].width;
					sprite[1].width = stored_width*SCALE_FACE_AMOUNTX;
					sprite[1].height = stored_height*SCALE_FACE_AMOUNTY;
					sprite[1].y = stored_scale_Y + ((stored_height * SCALE_FACE_AMOUNTY)/4);

					bump_index = VG_1_SELECTED + 2;

					if (VG_1_SELECTED == 8) // VG_SHO...
						bump_index = 26;
					if (VG_1_SELECTED == 9) // VG_TIA...
						bump_index = 27;
					if (VG_1_SELECTED == 10) // VG_SAIZO...
						bump_index = 28;
					if (VG_1_SELECTED == 11) // VG_KENNEDY...
						bump_index = 29;
					if (VG_1_SELECTED == 12) // VG_SANG...
						bump_index = 29;

					sprite[bump_index].bump_this = true;
					sprite[bump_index].bump_this_timer = (int)TimerGetTime() + 150;

					sprite[10].bump_this = true;
					sprite[10].bump_this_timer = (int)TimerGetTime() + 150;
				} 
				VG_1_HUDLEFT = false;
			} 
			if(VG_PLAYER1_SELECTED == false)
			if(VG_1_HUDRIGHT == VG_PRESSED)   
			{  
				if(VG_1_SELECTED != 3 && VG_1_SELECTED != 7 && VG_1_SELECTED != 11)
				{
					vg_title_move_sfx = true;
					VG_1_SELECTED++;
				    sprite[1].x = sprite[1].mov_x - sprite[1].width;
					sprite[1].width = stored_width*SCALE_FACE_AMOUNTX;
					sprite[1].height = stored_height*SCALE_FACE_AMOUNTY;
					sprite[1].y = stored_scale_Y + ((stored_height * SCALE_FACE_AMOUNTY)/4);

					bump_index = VG_1_SELECTED + 2;

					if (VG_1_SELECTED == 8) // VG_SHO...
						bump_index = 26;
					if (VG_1_SELECTED == 9) // VG_TIA...
						bump_index = 27;
					if (VG_1_SELECTED == 10) // VG_SAIZO...
						bump_index = 28;
					if (VG_1_SELECTED == 11) // VG_KENNEDY...
						bump_index = 29;
					if (VG_1_SELECTED == 12) // VG_SANG...
						bump_index = 29;

					sprite[bump_index].bump_this = true;
					sprite[bump_index].bump_this_timer = (int)TimerGetTime() + 150;

					sprite[10].bump_this = true;
					sprite[10].bump_this_timer = (int)TimerGetTime() + 150;
				}
				VG_1_HUDRIGHT = false;
			} 

			// Player two selection...
			if(VG_PLAYER2_SELECTED == false)
			if(VG_2_HUDDOWN == VG_PRESSED)
			{
				if(VG_2_SELECTED <= 3 || ((VG_2_SELECTED == 4 || VG_2_SELECTED == 5 || VG_2_SELECTED == 6 || VG_2_SELECTED == 7) && VG_ACTIVATE_BREAKERS != false))
				{
					vg_title_move_sfx = true;
					VG_2_SELECTED+=4;
					sprite[12].x = sprite[12].mov_x + sprite[12].width;
					sprite[12].width = stored_width*SCALE_FACE_AMOUNTX;
					sprite[12].height = stored_height*SCALE_FACE_AMOUNTY;
					sprite[12].y = stored_scale_Y  + ((stored_height * SCALE_FACE_AMOUNTY)/4);

					bump_index = VG_2_SELECTED + 2;

					if (VG_2_SELECTED == 8) // VG_SHO...
						bump_index = 26;
					if (VG_2_SELECTED == 9) // VG_TIA...
						bump_index = 27;
					if (VG_2_SELECTED == 10) // VG_SAIZO...
						bump_index = 28;
					if (VG_2_SELECTED == 11) // VG_KENNEDY...
						bump_index = 29;
					if (VG_2_SELECTED == 12) // VG_SANG...
						bump_index = 29;

					sprite[bump_index].bump_this = true;
					sprite[bump_index].bump_this_timer = (int)TimerGetTime() + 150;
					sprite[11].bump_this = true;
					sprite[11].bump_this_timer = (int)TimerGetTime() + 150;
				} 
				VG_2_HUDDOWN = false;
			} 
			if(VG_PLAYER2_SELECTED == false)
			if(VG_2_HUDUP == VG_PRESSED) 
			{
				if(VG_2_SELECTED > 3)
				{
					vg_title_move_sfx = true;
					VG_2_SELECTED-=4;
					sprite[12].x = sprite[12].mov_x + sprite[12].width;
					sprite[12].width = stored_width*SCALE_FACE_AMOUNTX;
					sprite[12].height = stored_height*SCALE_FACE_AMOUNTY;
					sprite[12].y = stored_scale_Y  + ((stored_height * SCALE_FACE_AMOUNTY)/4);

					bump_index = VG_2_SELECTED + 2;

					if (VG_2_SELECTED == 8) // VG_SHO...
						bump_index = 26;
					if (VG_2_SELECTED == 9) // VG_TIA...
						bump_index = 27;
					if (VG_2_SELECTED == 10) // VG_SAIZO...
						bump_index = 28;
					if (VG_2_SELECTED == 11) // VG_KENNEDY...
						bump_index = 29;
					if (VG_2_SELECTED == 12) // VG_SANG...
						bump_index = 29;

					sprite[bump_index].bump_this = true;
					sprite[bump_index].bump_this_timer = (int)TimerGetTime() + 150;
					sprite[11].bump_this = true;
					sprite[11].bump_this_timer = (int)TimerGetTime() + 150;
				} 
				VG_2_HUDUP = false;
			} 
			if(VG_PLAYER2_SELECTED == false)  
			if(VG_2_HUDLEFT == VG_PRESSED)
			{
				if(VG_2_SELECTED > 0  && VG_2_SELECTED != 4 && VG_2_SELECTED != 8)
				{  
					vg_title_move_sfx = true; 
					VG_2_SELECTED--;
					sprite[12].x = sprite[12].mov_x + sprite[12].width;
					sprite[12].width = stored_width*SCALE_FACE_AMOUNTX;
					sprite[12].height = stored_height*SCALE_FACE_AMOUNTY;
					sprite[12].y = stored_scale_Y  + ((stored_height * SCALE_FACE_AMOUNTY)/4);

					bump_index = VG_2_SELECTED + 2;

					if (VG_2_SELECTED == 8) // VG_SHO...
						bump_index = 26;
					if (VG_2_SELECTED == 9) // VG_TIA...
						bump_index = 27;
					if (VG_2_SELECTED == 10) // VG_SAIZO...
						bump_index = 28;
					if (VG_2_SELECTED == 11) // VG_KENNEDY...
						bump_index = 29;
					if (VG_2_SELECTED == 12) // VG_SANG...
						bump_index = 29;

					sprite[bump_index].bump_this = true;
					sprite[bump_index].bump_this_timer = (int)TimerGetTime() + 150;
					sprite[11].bump_this = true;
					sprite[11].bump_this_timer = (int)TimerGetTime() + 150;
				}  
				VG_2_HUDLEFT = false;     
			} 
			if(VG_PLAYER2_SELECTED == false)
			if(VG_2_HUDRIGHT == VG_PRESSED)    
			{   
				if(VG_2_SELECTED != 3 && VG_2_SELECTED != 7 && VG_2_SELECTED != 11)
				{ 
					vg_title_move_sfx = true;
					VG_2_SELECTED++;
					sprite[12].x = sprite[12].mov_x + sprite[12].width; 
					sprite[12].width = stored_width*SCALE_FACE_AMOUNTX;
					sprite[12].height = stored_height*SCALE_FACE_AMOUNTY;
					sprite[12].y = stored_scale_Y  + ((stored_height * SCALE_FACE_AMOUNTY)/4);

					bump_index = VG_2_SELECTED + 2; 

					if (VG_2_SELECTED == 8) // VG_SHO...
						bump_index = 26;
					if (VG_2_SELECTED == 9) // VG_TIA...
						bump_index = 27;
					if (VG_2_SELECTED == 10) // VG_SAIZO...
						bump_index = 28;
					if (VG_2_SELECTED == 11) // VG_KENNEDY...
						bump_index = 29;
					if (VG_2_SELECTED == 12) // VG_SANG...
						bump_index = 29;

					sprite[bump_index].bump_this = true;
					sprite[bump_index].bump_this_timer = (int)TimerGetTime() + 150;
					sprite[11].bump_this = true;
					sprite[11].bump_this_timer = (int)TimerGetTime() + 150;
				} 
				VG_2_HUDRIGHT = false; 
			} 
			    
			if((int)TimerGetTime() > title_timer)     
			if(title_sequence == 2)    
			{ 
				if(VG_1_PUNCH == VG_PRESSED || VG_1_PUNCH2 == VG_PRESSED || VG_1_KICK == VG_PRESSED || VG_1_KICK2 == VG_PRESSED
				|| VG_1_PUNCH == VG_HELD  || VG_1_PUNCH2 == VG_HELD || VG_1_KICK == VG_HELD || VG_1_KICK2 == VG_HELD)
				{
					temp_speed = (0.00060f*(float)f_rate);  
				}
				else
					temp_speed = (0.00015f*(float)f_rate);  

				mid_x = sprite[24].x+sprite[24].width/2; // *SCALE_FACE_AMOUNTX
				mid_y = sprite[24].y+sprite[24].height/2; // *SCALE_FACE_AMOUNTY

				if(VG_map_next_point >= 0 && VG_map_next_point < TOTAL_NO_SPRITES)
				{
					tar_x = sprite[VG_map_next_point].x+sprite[VG_map_next_point].width/2; 
					tar_y = sprite[VG_map_next_point].y+sprite[VG_map_next_point].height/2; 
				}

				angle = atan2(tar_y - mid_y, tar_x - mid_x);

				deltax = cos(angle); // Was 1.2      
				deltay = sin(angle); // Was 1.2 
        
				deltax *= temp_speed;           
				deltay *= temp_speed;    
				
				angle = (angle*180)/3.14f;
             
				if(angle < 0)                      
					angle += 360;  

				distance = Node_Distance1(mid_x, mid_y, tar_x, tar_y);

				if(distance <= 0.005f)         
				{
					if(VG_map_next_point >= 0 && VG_map_next_point < TOTAL_NO_SPRITES)
					{
						sprite[24].x = sprite[VG_map_next_point].x; 
						sprite[24].y = sprite[VG_map_next_point].y;
						sprite[24].w = sprite[VG_map_next_point].w; 
						sprite[24].z = sprite[VG_map_next_point].z; 
					}

					stop_vg_amb_van_sfx = true;

					Set_Sprite(24, sprite[24].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

					sprite[24].anim_state = WAIT; // Cop Car/Bike...

					title_timer = (int)TimerGetTime() + 1000;
					title_sequence = 5;
				}  
				else 
				{
				  
					sprite[24].x += deltax;      
					sprite[24].w += deltax;  
				    
					sprite[24].y += deltay;            
					sprite[24].z += deltay;  

					if((int)TimerGetTime() > vg_van_trail_timer)
					{
						vg_van_trail_timer = (int)TimerGetTime() + 75;

						if(sprite[24].base_anim == 6) // van
							New_FX(sprite[24].x, sprite[24].y, sprite[24].x, sprite[24].y, 11, PLAY, sprite[24].width, sprite[24].height, sprite[24].width,sprite[24].height, 4, GFX, 1.0f, 0, -1, FX_VG_TRAIL_SPRITE, 24, sprite[24].id, 0, 0, 24);
						else
							New_FX(sprite[24].x, sprite[24].y, sprite[24].x, sprite[24].y, 10, PLAY, sprite[24].width, sprite[24].height, sprite[24].width,sprite[24].height, 4, GFX, 1.0f, 0, -1, FX_VG_TRAIL_SPRITE, 24, sprite[24].id, 0, 0, 24);
					}

				}
			}
			   
			if(VG_slowmof > 0.0f)
			{
				temp_speed = (0.00100f/VG_slowmof)*(float)f_rate;

				if(sprite[1].x < sprite[1].mov_x - sprite[1].width/2) 
					temp_speed = (0.0075f/VG_slowmof)*(float)f_rate;
				if(sprite[1].x < sprite[1].mov_x - sprite[1].width/4) 
					temp_speed = (0.0050f/VG_slowmof)*(float)f_rate;
				if(sprite[1].x < sprite[1].mov_x - sprite[1].width/6)
					temp_speed = (0.0025f/VG_slowmof)*(float)f_rate;

				if(VG_PLAYER1_SELECTED == true)
					temp_speed = (0.00100f/VG_slowmof)*(float)f_rate;

				if (sprite[1].height < stored_height)
				{
					sprite[1].height += (0.00100f / VG_slowmof)*(float)f_rate;
					sprite[1].y -= (0.00050f / VG_slowmof)*(float)f_rate;
				}
				else 
				{
					sprite[1].height = stored_height;
					sprite[1].y = stored_scale_Y;
				}

				if (sprite[1].width < stored_width)
					sprite[1].width += (0.00100f / VG_slowmof)*(float)f_rate;
				else
					sprite[1].width = stored_width;

				sprite[1].x += temp_speed;       

				temp_speed = (0.00100f/VG_slowmof)*(float)f_rate;

				if(sprite[12].x > sprite[12].mov_x + sprite[12].width/2)
					temp_speed = (0.0075f/VG_slowmof)*(float)f_rate;
				if(sprite[12].x > sprite[12].mov_x + sprite[12].width/4)
					temp_speed = (0.0050f/VG_slowmof)*(float)f_rate;
				if(sprite[12].x > sprite[12].mov_x + sprite[12].width/6)
					temp_speed = (0.0025f/VG_slowmof)*(float)f_rate;

				if (sprite[12].height < stored_height)
				{
					sprite[12].height += (0.00100f / VG_slowmof)*(float)f_rate;
					sprite[12].y -= (0.00050f / VG_slowmof)*(float)f_rate;
				}
				else 
				{
					sprite[12].height = stored_height;
					sprite[12].y = stored_scale_Y;
				}

				if (sprite[12].width < stored_width)
					sprite[12].width += (0.00100f / VG_slowmof)*(float)f_rate;
				else
					sprite[12].width = stored_width;

				if(VG_PLAYER2_SELECTED == true)
					temp_speed = (0.00100f/VG_slowmof)*(float)f_rate;
			}

			sprite[12].x -= temp_speed;  

			if(sprite[1].x >= sprite[1].mov_x )   
			{      
				sprite[1].x = sprite[1].mov_x;
			} 
			if(sprite[12].x <= sprite[12].mov_x )   
			{      
				sprite[12].x = sprite[12].mov_x;
			} 

			// Pressed back key...
		/*	if(VG_AI_active == false || vg_selected_character == false)
			if(VG_1_HUD_BACK == true)
			{
				VG_reset_input();
				vg_next_episode = 0;
				vg_next_scene  = 1;

				if(VG_GAME_MODE != VG_VERSUS_MODE)
					VG_BACK_TO_SELECTION = true;

				next_scene = true;
			}*/

			char_not_available = false;

			if(next_scene == false)    
			if(VG_PLAYER1_SELECTED == false)
			if((int)TimerGetTime() > VG_1_DX_A_timer)
			if(VG_1_HUD_GO == true) 
			{  

				VG_1_HUD_GO = false; 

				VG_1_DX_A_timer = (int)TimerGetTime() + 250;

				VG_reset_input();

				if(VG_STEAM_DEMO == 1)
				if(VG_1_SELECTED != 2 && VG_1_SELECTED != 7)
					char_not_available = true;

				if(char_not_available == false) 
				{
				         
					VG_1_CHARACTER = VG_1_SELECTED;    

					if(REPLACE_SANG_WITH_KENNEDY == 0)
					if (VG_1_SELECTED == 11) // VG_KENNEDY...
						VG_1_CHARACTER = VG_SANG;

					VG_map_last_point = (VG_1_CHARACTER+14);

					if (VG_1_CHARACTER == VG_SANG)
						VG_map_last_point = 30; // Was 22..
					if (VG_1_CHARACTER == VG_SHO)
						VG_map_last_point = 30;
					if (VG_1_CHARACTER == VG_SAIZO)
						VG_map_last_point = 31;
					if (VG_1_CHARACTER == VG_TIA)
						VG_map_last_point = 32;
					if (VG_1_CHARACTER == VG_KENNEDY)
						VG_map_last_point = 33;

					if(vg_selected_character == true)
					if(VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_DUELLING)
					    VG_map_last_point = 25;

					if(VG_AI_active == true)     
					{ 
						if(VG_map_last_point >= 0 && VG_map_last_point < TOTAL_NO_SPRITES)
						{
							sprite[24].x = sprite[VG_map_last_point].x;
							sprite[24].y = sprite[VG_map_last_point].y;
						}

						sprite[24].alpha = 1.0f;
						title_timer = 0;  

						title_timer = (int)TimerGetTime() + 500;
						title_sequence = 2;

						if(vg_selected_character == false)
						{
							sprite[24].alpha = 0.0f;

							vg_next_episode = 0;
							vg_next_scene  = 9;  
				  
							next_scene = true; 

							title_sequence = 101; 

						} 
					} 

					vg_selected_character = true; 

					VG_PLAYER1_SELECTED = true;                

					temp_bottomrow_index = VG_1_CHARACTER + 2;

					if (VG_1_CHARACTER == VG_SHO)
						temp_bottomrow_index = 26;
					if (VG_1_CHARACTER == VG_TIA)
						temp_bottomrow_index = 27;
					if (VG_1_CHARACTER == VG_SAIZO)
						temp_bottomrow_index = 28;
					if (VG_1_CHARACTER == VG_KENNEDY)
						temp_bottomrow_index = 29;
					if (VG_1_CHARACTER == VG_SANG)
						temp_bottomrow_index = 29;

					if(temp_bottomrow_index >= 0 && temp_bottomrow_index < TOTAL_NO_SPRITES)
					{

						sprite[temp_bottomrow_index].flash_target = true;
						sprite[temp_bottomrow_index].flash_timer = (int)TimerGetTime() + 25;

						Set_Sprite(temp_bottomrow_index, sprite[temp_bottomrow_index].base_anim + 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

					}

					Set_Sprite(10, 2, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

					title_timer = (int)TimerGetTime() + 500;
					vg_pause_sfx = true;

				}
				else
					vg_hitsound_sfx = true;

			}  
			 
			if(char_not_available == false)
			if(next_scene == false)
			if(VG_GAME_MODE == VG_VERSUS_MODE)
			if(VG_PLAYER2_SELECTED == false) 
			if((int)TimerGetTime() > VG_2_DX_A_timer)
			if(VG_2_HUD_GO == true)
			{
				VG_2_HUD_GO = false;

				VG_2_DX_A_timer = (int)TimerGetTime() + 250;

				VG_reset_input(); 

				if(VG_STEAM_DEMO == 1)
				if(VG_2_SELECTED != 2 && VG_2_SELECTED != 7)
					char_not_available = true;

				if(char_not_available == false) 
				{

					VG_PLAYER2_SELECTED = true;  

					VG_2_CHARACTER = VG_2_SELECTED;

					VG_BACKGROUND = VG_2_CHARACTER;

					temp_bottomrow_index = VG_2_SELECTED + 2;

					if (VG_2_SELECTED == VG_SHO)
						temp_bottomrow_index = 26;
					if (VG_2_SELECTED == VG_TIA)
						temp_bottomrow_index = 27;
					if (VG_2_SELECTED == VG_SAIZO)
						temp_bottomrow_index = 28;
					if (VG_2_SELECTED == VG_SANG)
						temp_bottomrow_index = 29;
					if (VG_2_SELECTED == VG_KENNEDY)
						temp_bottomrow_index = 29;

					if (temp_bottomrow_index >= 0 && temp_bottomrow_index < TOTAL_NO_SPRITES)
					{

						sprite[temp_bottomrow_index].flash_target = true;
						sprite[temp_bottomrow_index].flash_timer = (int)TimerGetTime() + 25;

						Set_Sprite(temp_bottomrow_index, sprite[temp_bottomrow_index].base_anim + 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

					} 

					Set_Sprite(11, 3, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

					title_timer = (int)TimerGetTime() + 500;
					vg_pause_sfx = true;  

				}
				else
					vg_hitsound_sfx = true;

			}  
			if(next_scene == false)
			if(VG_PLAYER1_SELECTED == true && VG_PLAYER2_SELECTED == true)
			if(title_sequence == 5)
			if((int)TimerGetTime() > title_timer) 
			{
				VG_IS_VERSUS_SCREEN = true;   
				vg_next_episode = 6;       
				vg_next_scene    = 0;    
				next_scene = true; 

				if(VG_GAME_MODE == VG_VERSUS_MODE)
			    if(VG_VS_BG == 1) 
					VG_BACKGROUND = rand()%13;

				if(REPLACE_SANG_WITH_KENNEDY == 0)
				if (VG_1_SELECTED == 11) // VG_KENNEDY...
					VG_1_CHARACTER = VG_SANG;

				if(VG_GAME_MODE == VG_VERSUS_MODE)
				if(REPLACE_SANG_WITH_KENNEDY == 0)
				if (VG_2_SELECTED == 11) // VG_KENNEDY...
					VG_2_CHARACTER = VG_SANG;


			   if(VG_AI_active == true && vg_selected_character == true)
			   { 
				    VG_map_last_point = (VG_NEXT_FIGHTER+14);
					VG_2_CHARACTER = VG_NEXT_FIGHTER;
					VG_BACKGROUND = VG_2_CHARACTER; 

					if (VG_NEXT_FIGHTER == VG_SANG)
						VG_map_last_point = 30; // Was 22..
					if (VG_NEXT_FIGHTER == VG_SHO)
						VG_map_last_point = 30;
					if (VG_NEXT_FIGHTER == VG_SAIZO)
						VG_map_last_point = 31;
					if (VG_NEXT_FIGHTER == VG_TIA)
						VG_map_last_point = 32;
					if (VG_NEXT_FIGHTER == VG_KENNEDY)
						VG_map_last_point = 33;

					if(vg_selected_character == true)
					if(VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_DUELLING)
					    VG_map_last_point = 25;
					   
					if(VG_CURRENT_STORY_SCENE >= 0 && VG_CURRENT_STORY_SCENE < 20)
					if(VG_GAME_MODE == VG_STORY_MODE)       
					{        
						        
						// For testing only...       
					//	VG_CURRENT_STORY_SCENE = 3;     

						VG_STORY_SETUP = VG_STORY_SCENE_SETUP; 

						VG_map_last_point = (VG_story_background[VG_CURRENT_STORY_SCENE]+14);

						if (VG_story_background[VG_CURRENT_STORY_SCENE] == VG_TRAINER)
							VG_map_last_point = 23;
						if (VG_story_background[VG_CURRENT_STORY_SCENE] == VG_SANG)
							VG_map_last_point = 22;

						VG_2_CHARACTER = VG_story_characters[VG_CURRENT_STORY_SCENE];
						VG_BACKGROUND = VG_story_background[VG_CURRENT_STORY_SCENE];
						VG_ROUND_CONDITIONS = VG_story_conditions[VG_CURRENT_STORY_SCENE];
						VG_AI_LEVEL = VG_story_ai_level[VG_CURRENT_STORY_SCENE];
						VG_IS_AN_ALTER = VG_is_an_alter_story[VG_CURRENT_STORY_SCENE];

						VG_1_EQUIPMENT = VG_1_equipment[VG_CURRENT_STORY_SCENE];
						VG_2_EQUIPMENT = VG_2_equipment[VG_CURRENT_STORY_SCENE];

						// Need to go to cutscene mode here...
						vg_next_episode = 6;    
						vg_next_scene    = 2;    
						next_scene = true; 
					}
			   }

			} 
			 
	   } 

    // ******************************************************************************//
    //                              6-0  (VS SCREEN)                                 //
    // ******************************************************************************//
				                 
       // Title Screen Stuff...  
       if(!mode)    
       if(episode == 6 && scene == 0)       
       {          

		   if(VG_HUD_ESC == true)        
		   {
			    
			   VG_HUD_ESC = false;    

			   vg_next_episode = 0;    
			   vg_next_scene    = 1;   
				 
			   next_scene = true;       
				  
		   } 	

			// Boxes for move display...
			if(VG_IS_VERSUS_SCREEN == true && VG_GAME_MODE != VG_STORY_MODE)
			{
				if(new_counter[7].alpha == 1.0f)
					sprite[9].alpha = 1.0f;
				else
					sprite[9].alpha = 0.0f;

				if(new_counter[8].alpha == 1.0f)
					sprite[10].alpha = 1.0f;
				else
					sprite[10].alpha = 0.0f;
			}
			else
			{
				sprite[9].alpha = 0.0f; 
				sprite[10].alpha = 0.0f; 
			}

		   if(VG_IS_VERSUS_SCREEN == true) 
		   {
			   new_counter[7].y = -0.23f;  
			   new_counter[8].y = -0.23f;

			   sprite[7].u[0] += 0.0001f * (float)f_rate;
			   sprite[7].u[1] += 0.0001f * (float)f_rate; 
			   sprite[7].u[2] += 0.0001f * (float)f_rate;
			   sprite[7].u[3] += 0.0001f * (float)f_rate;

			   sprite[8].u[0] -= 0.0001f * (float)f_rate;
			   sprite[8].u[1] -= 0.0001f * (float)f_rate;
			   sprite[8].u[2] -= 0.0001f * (float)f_rate;
			   sprite[8].u[3] -= 0.0001f * (float)f_rate;
		   }
		   else
		   {
			   sprite[7].alpha = 0.0f;
			   sprite[8].alpha = 0.0f;
		   }


		   // Bars...
		   if(VG_IS_VERSUS_SCREEN == false)
		   {
		   
			   sprite[6].x = sprite[2].x;
			   sprite[6].y = sprite[2].y;

			   sprite[5].x = sprite[3].x;
			   sprite[5].y = sprite[3].y;

			   if(VG_1_WAS_ARRESTED == true)
				   sprite[6].alpha = 1.0f;
			   else
				   sprite[6].alpha = 0.0f; // Bars...

			   if(VG_2_WAS_ARRESTED == true)
				   sprite[5].alpha = 1.0f;
			   else   
				   sprite[5].alpha = 0.0f; // Bars...

			   // Remove bars if continuing...
			   if(title_sequence == 5)
			   {
				   sprite[6].alpha = 0.0f;
				   sprite[5].alpha = 0.0f; 
			   }
		   } 

			if(VG_P1_USING == VG_KEYBOARD)
				sprintf( new_counter[9].word, "^       %c: YES  %C: NO^", VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY); 
			else
				sprintf( new_counter[9].word, "^       ÷: YES  ø: NO^"); 

		   if(title_sequence == 0)       
		   { 

			   // Set Sho to other sheet...
			   if (VG_1_CHARACTER == VG_SHO)
				   sprite[2].id = 13;
			   if (VG_2_CHARACTER == VG_SHO)
				   sprite[3].id = 13;
			   if (VG_1_CHARACTER == VG_TIA)
				   sprite[2].id = 13;
			   if (VG_2_CHARACTER == VG_TIA)
				   sprite[3].id = 13;
			   if (VG_1_CHARACTER == VG_SAIZO)
				   sprite[2].id = 13;
			   if (VG_2_CHARACTER == VG_SAIZO)
				   sprite[3].id = 13;
			   if (VG_1_CHARACTER == VG_KENNEDY)
				   sprite[2].id = 13;
			   if (VG_2_CHARACTER == VG_KENNEDY)
				   sprite[3].id = 13;
			   
			   if(VG_1_CHARACTER == VG_2_CHARACTER)
			   if (VG_2_CHARACTER == VG_TIA || VG_2_CHARACTER == VG_SHO || VG_2_CHARACTER == VG_SAIZO || VG_2_CHARACTER == VG_KENNEDY)
				   sprite[3].id = 14;

			   VG_CPU_THROWN_COUNT = 0;

			   sprite[7].mov_y = sprite[7].y; 
			   sprite[8].mov_y = sprite[8].y;

			   sprite[7].y += sprite[7].height *3; 
			   sprite[8].y -= sprite[8].height *3; 

			   vg_skip_this = false;   

			   // Upload current score...
			   if(VG_STEAM_DEMO == 0)
			   if(VG_IS_VERSUS_SCREEN == false)
			   if(VG_GAME_MODE == VG_ARCADE_MODE) 
			   {
				   if(VG_SURVIVAL == true)
					   VG_Upload_Score(1);
				   else
					   VG_Upload_Score(0);
			   }
			    
			   if(VG_IS_VERSUS_SCREEN == false)
				   VG_start_timer = (int)TimerGetTime() + 500;
			   else
				   VG_start_timer = (int)TimerGetTime() + 2000;

			   sprite[2].mov_x = sprite[2].x;
			   sprite[3].mov_x = sprite[3].x; 
			      
			   sprite[4].alpha = 0.0f;
			    
			   // Setup faces...
			   sprite[2].base_anim = VG_1_CHARACTER;  
			   sprite[3].base_anim = VG_2_CHARACTER;

			   if (VG_1_CHARACTER == VG_SHO)
				   sprite[2].base_anim = 0; 
			   if (VG_2_CHARACTER == VG_SHO)
				   sprite[3].base_anim = 0;
			   if (VG_1_CHARACTER == VG_TIA)
				   sprite[2].base_anim = 1;
			   if (VG_2_CHARACTER == VG_TIA)
				   sprite[3].base_anim = 1;
			   if (VG_1_CHARACTER == VG_SAIZO)
				   sprite[2].base_anim = 2; 
			   if (VG_2_CHARACTER == VG_SAIZO)
				   sprite[3].base_anim = 2;
			   if (VG_1_CHARACTER == VG_KENNEDY)
				   sprite[2].base_anim = 3; 
			   if (VG_2_CHARACTER == VG_KENNEDY)
				   sprite[3].base_anim = 3;

			   if(VG_1_CHARACTER == VG_SANG)
				   sprite[2].base_anim = 24;   
			   if(VG_2_CHARACTER == VG_SANG)
				   sprite[3].base_anim = 24;

			   if(VG_1_CHARACTER == VG_TRAINER)
				   sprite[2].base_anim = 27;   
			   if(VG_2_CHARACTER == VG_TRAINER)
				   sprite[3].base_anim = 27; 

			   Set_Sprite(2, sprite[2].base_anim, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned
			   Set_Sprite(3, sprite[3].base_anim, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned

			   VG_1_WINS = 0;
			   VG_2_WINS = 0;

			   VG_ROUND = 1; 
			  
				new_counter[9].alpha = 0.0f;                     
				new_counter[9].id = 2;        
				  
				new_counter[9].type = 1;  // Small Font...
				new_counter[9].right = false;

				new_counter[9].x = -0.28f;                     
				new_counter[9].y = -0.33f;          

				new_counter[9].w = new_counter[9].x - 0.026f;   
				new_counter[9].z = new_counter[9].y - 0.015f; 

				new_counter[9].box_width = strlen(new_counter[9].word)   *  0.026f;
				new_counter[9].box_height = new_counter[9].height - 0.015f;	

			   if(VG_IS_VERSUS_SCREEN == true)
			   {

				   VG_MOVES_VS = true; 

				   // Player 1 name...
				   new_counter[1].alpha = 0.0f;        
				   new_counter[1].id = 0;      
				   new_counter[1].x = -0.46f;        
				   new_counter[1].y = sprite[3].y - 0.004f;
				   new_counter[1].type = 0;  // Large Font...
				   new_counter[1].right = false; 
			        
				   sprintf( new_counter[1].word, "");  

				   if(VG_1_CHARACTER == VG_GYEONG)
					   sprintf( new_counter[1].word, "GYEONG^");   
				   if(VG_1_CHARACTER == VG_SIU)
					   sprintf( new_counter[1].word, "  SI$U^");   
				   if(VG_1_CHARACTER == VG_MINSO)
					   sprintf( new_counter[1].word, " MINSO^");   
				   if(VG_1_CHARACTER == VG_REESE)
					   sprintf( new_counter[1].word, " REESE^");   
				   if(VG_1_CHARACTER == VG_YOHAN)
					   sprintf( new_counter[1].word, " YOHAN^");   
				   if(VG_1_CHARACTER == VG_JAE)
					   sprintf( new_counter[1].word, "  JAE^");   
				   if(VG_1_CHARACTER == VG_GUN)
					   sprintf( new_counter[1].word, "  GUN^");   
				   if(VG_1_CHARACTER == VG_HYUK)
					   sprintf( new_counter[1].word, "  HYUK^");    
				   if(VG_1_CHARACTER == VG_SANG)
					   sprintf( new_counter[1].word, "  SANG^");  
				   if(VG_1_CHARACTER == VG_TRAINER)
					   sprintf( new_counter[2].word, "  SABU^"); 
				   if (VG_1_CHARACTER == VG_SHO)
					   sprintf(new_counter[1].word,  "  SHO^");
				   if (VG_1_CHARACTER == VG_TIA)
					   sprintf(new_counter[1].word,  "  TIA^");
				   if(VG_1_CHARACTER == VG_SAIZO)
					   sprintf( new_counter[1].word, " SAIZO^");   
				   if(VG_1_CHARACTER == VG_KENNEDY)
					   sprintf( new_counter[1].word, "KEN ANDERSON^");   

				   if(VG_1_CHARACTER == VG_GYEONG && VG_IS_AN_ALTER_P1 == true)
					   sprintf( new_counter[1].word, " TOYUN^");   
				   if(VG_1_CHARACTER == VG_SIU && VG_IS_AN_ALTER_P1 == true)
					   sprintf( new_counter[1].word, "DAE-SU^");   
				   if(VG_1_CHARACTER == VG_MINSO && VG_IS_AN_ALTER_P1 == true)
					   sprintf( new_counter[1].word, "   MIA^");   
				   if(VG_1_CHARACTER == VG_REESE && VG_IS_AN_ALTER_P1 == true)
					   sprintf( new_counter[1].word, "   BOB^");   
				   if(VG_1_CHARACTER == VG_YOHAN && VG_IS_AN_ALTER_P1 == true)
					   sprintf( new_counter[1].word, "SUNG-KI^");   
				   if(VG_1_CHARACTER == VG_JAE && VG_IS_AN_ALTER_P1 == true)
					   sprintf( new_counter[1].word, "SAPPORO^");   
				   if(VG_1_CHARACTER == VG_GUN && VG_IS_AN_ALTER_P1 == true)
					   sprintf( new_counter[1].word, " KONU^");   
				   if(VG_1_CHARACTER == VG_HYUK && VG_IS_AN_ALTER_P1 == true)
					   sprintf( new_counter[1].word, "YE-JUN^");  
		    
				   // Player 2 name...
				   new_counter[2].alpha = 0.0f;       
				   new_counter[2].id = 0;         
				   new_counter[2].x = 0.48f;               
				   new_counter[2].y = sprite[3].y - 0.004f;
				   new_counter[2].type = 0;  // Large Font...
				   new_counter[2].right = true; 
				     
				   sprintf( new_counter[2].word, "");  

				   if(VG_2_CHARACTER == VG_GYEONG)  
					   sprintf( new_counter[2].word, "GYEONG");     
				   if(VG_2_CHARACTER == VG_SIU)
					   sprintf( new_counter[2].word, "SI$U  ");   
				   if(VG_2_CHARACTER == VG_MINSO)
					   sprintf( new_counter[2].word, "MINSO ");   
				   if(VG_2_CHARACTER == VG_REESE)
					   sprintf( new_counter[2].word, "REESE ");   
				   if(VG_2_CHARACTER == VG_YOHAN)
					   sprintf( new_counter[2].word, "YOHAN ");   
				   if(VG_2_CHARACTER == VG_JAE)
					   sprintf( new_counter[2].word, "JAE  ");   
				   if(VG_2_CHARACTER == VG_GUN)  
					   sprintf( new_counter[2].word, "GUN  ");   
				   if(VG_2_CHARACTER == VG_HYUK) 
					   sprintf( new_counter[2].word, "HYUK  "); 
				   if(VG_2_CHARACTER == VG_SANG)
					   sprintf( new_counter[2].word, "SANG  "); 
				   if(VG_2_CHARACTER == VG_TRAINER)
					   sprintf( new_counter[2].word, "SABU  ");  
				   if (VG_2_CHARACTER == VG_SHO)
					   sprintf(new_counter[2].word,  "SHO   ");
				   if (VG_2_CHARACTER == VG_TIA)
					   sprintf(new_counter[2].word,  "TIA   "); 
				   if(VG_2_CHARACTER == VG_SAIZO)
					   sprintf( new_counter[2].word, "SAIZO "); 
				   if(VG_2_CHARACTER == VG_KENNEDY)  
					   sprintf( new_counter[2].word, "KEN ANDERSON");   

					if(VG_2_CHARACTER == VG_GYEONG && VG_IS_AN_ALTER == true)
						sprintf( new_counter[2].word, "TOYUN");
					if(VG_2_CHARACTER == VG_SIU && VG_IS_AN_ALTER == true)
						sprintf( new_counter[2].word, "DAE-SU");
					if(VG_2_CHARACTER == VG_MINSO && VG_IS_AN_ALTER == true)
						sprintf( new_counter[2].word, "MIA  ");
					if(VG_2_CHARACTER == VG_REESE && VG_IS_AN_ALTER == true)
						sprintf( new_counter[2].word, "BOB  ");
					if(VG_2_CHARACTER == VG_GUN && VG_IS_AN_ALTER == true)
						sprintf( new_counter[2].word, "KONU ");
					if(VG_2_CHARACTER == VG_YOHAN && VG_IS_AN_ALTER == true)
						sprintf( new_counter[2].word, "SUNG-KI");
					if(VG_2_CHARACTER == VG_JAE && VG_IS_AN_ALTER == true)
						sprintf( new_counter[2].word, "SAPPORO");			    
					if(VG_2_CHARACTER == VG_HYUK && VG_IS_AN_ALTER == true)
						sprintf( new_counter[2].word, "YE-JUN");	

				   VG_Moveslist(7, VG_1_CHARACTER, -1, 1); 
			 
					new_counter[7].alpha = 0.0f;	                
					new_counter[7].id = 2;         
				  
					new_counter[7].type = 1;  // Small Font...
					new_counter[7].right = false;
					 
					if (screen_mode == SCREEN_NORMAL) // 4:3
						new_counter[7].x = -0.45f;                      
					else
						new_counter[7].x = -0.60f;

					new_counter[7].y = -0.33f;           

					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;

					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	

				    VG_Moveslist(8, VG_2_CHARACTER, -1, 2);
			  
					new_counter[8].alpha = 0.0f;	                
					new_counter[8].id = 2;         
				  
					new_counter[8].type = 1;  // Small Font...
					new_counter[8].right = false;

					if (screen_mode == SCREEN_NORMAL) // 4:3
						new_counter[8].x = 0.22f;                        
					else
						new_counter[8].x = 0.34f;

					new_counter[8].y = -0.33f;          

					new_counter[8].w = new_counter[8].x - 0.026f;   
					new_counter[8].z = new_counter[8].y - 0.015f;

					new_counter[8].box_width = strlen(new_counter[8].word)   *  0.026f;
					new_counter[8].box_height = new_counter[8].height - 0.015f;	

			   } 
			   else      
			   {  

				   #if IS_FULL_STEAM == 1 
				   if(STEAM_ACTIVE == true)
				   if(VG_PLAYER1_WON == true)
				   if(VG_TRAINING == true)
				   if(VG_STEAM_DEMO == 0)
				   {
					   //g_SteamAchievements->SetAchievement("VG_11"); // Beat training mode...
				   }
				   #endif

				   if(VG_PLAYER1_WON == false)
				   if(VG_GAME_MODE == VG_STORY_MODE)
				   {
					   if(VG_ROUND_CONDITIONS == CONDITION_MUST_ARREST || VG_ROUND_CONDITIONS == CONDITION_MUST_WASTE)
						   vg_skip_this = true;
					   if(VG_ROUND_CONDITIONS == CONDITION_TIMED || VG_ROUND_CONDITIONS == CONDITION_TIMED_BASIC)
						   vg_skip_this = true;
				   }

				   if(vg_skip_this == false)
				   if(VG_PLAYER1_WON == false) 
				   {
					   if(VG_GAME_MODE == VG_ARCADE_MODE)
					       VG_1_CREDITS--;

					   if(VG_1_CREDITS < 0)
						   VG_1_CREDITS = 0;

					   Set_Sprite(2, sprite[2].base_anim+8, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned
						
					   if(VG_1_CHARACTER == VG_SANG)
						   Set_Sprite(2, sprite[2].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned
					   if(VG_1_CHARACTER == VG_TRAINER)
						   Set_Sprite(2, sprite[2].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned
				   }
				   else
				   {

					   VG_BATTLE_ROUND++;

					   Set_Sprite(3, sprite[3].base_anim+8, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned

					   if(VG_2_CHARACTER == VG_SANG)
						   Set_Sprite(3, sprite[3].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned
					   if(VG_2_CHARACTER == VG_TRAINER)
						   Set_Sprite(3, sprite[3].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned

					   if(VG_GAME_MODE == VG_ARCADE_MODE)
					   {
						   if(vg_defeat_count >= 0 && vg_defeat_count < 15)
							   VG_DEFEATED_GUYS[vg_defeat_count] = VG_2_CHARACTER;
					    
						   vg_defeat_count++;

						   if(vg_defeat_count >= 9) 
							   vg_defeat_count = 9;
					   }
				   }

				   sprite[1].alpha = 0.0f; 

				   if(VG_PLAYER1_WON == true)
					   VG_WINNING_CHAR = VG_1_CHARACTER;
				   else
					   VG_WINNING_CHAR = VG_2_CHARACTER;

				   // Player 1 name... 
				   new_counter[1].alpha = 1.0f;                 
				   new_counter[1].id = 0;       
				   new_counter[1].x = -0.32f;         
				   new_counter[1].y = sprite[3].y - 0.04f;
				   new_counter[1].type = 2;  // Large Font...  
				   new_counter[1].right = false; 
			         
				   sprintf( new_counter[1].word, "");

				   if(vg_defeat_count == 14 && VG_PLAYER1_WON == true && VG_GAME_MODE == VG_ARCADE_MODE) // Display endings coming soon..
					   VG_Text(VG_WINNING_CHAR, VG_2_CHARACTER, 1); 
				   else
				   {
					   if(VG_PLAYER1_WON == true)
					       VG_Text(VG_1_CHARACTER, VG_2_CHARACTER, -1); 
					   else
					       VG_Text(VG_2_CHARACTER, VG_1_CHARACTER, -1); 
				   }
				    
			   }

			   if(VG_IS_VERSUS_SCREEN == true)  
			   {
				   sprite[2].mov_x = sprite[2].x; 
				   sprite[3].mov_x = sprite[3].x;    

				   sprite[2].x = sprite[0].x + sprite[0].width;
				   sprite[3].x = sprite[0].x - sprite[3].width;

				   sprite[1].alpha = 0.0f;

				   title_timer = (int)TimerGetTime() + 1500;
				   title_sequence++; 

			   }
			   else
			   {
				   title_timer = (int)TimerGetTime() + 5000;
				   title_sequence++;
			   }

		   }

		   // Move tape..
		      
		   if(next_scene == false)
		   {
			   if( sprite[7].y > sprite[7].mov_y)			   
				   sprite[7].y -= 0.00015f * (float)f_rate;
			   else
				   sprite[7].y = sprite[7].mov_y; 

			   if( sprite[8].y < sprite[8].mov_y)			   
				   sprite[8].y += 0.00015f * (float)f_rate;
			   else
				   sprite[8].y = sprite[8].mov_y;
		   }
		   else 
		   {
			   sprite[7].y += 0.00015f * (float)f_rate;
			   sprite[8].y -= 0.00015f * (float)f_rate;
		   }


		   if(VG_IS_VERSUS_SCREEN == false)  
		   {

			   if((int)TimerGetTime() > VG_start_timer)
			   if(title_sequence == 1)
			   if(VG_1_PUNCH == VG_PRESSED || VG_1_PUNCH2 == VG_PRESSED || VG_1_KICK == VG_PRESSED || VG_1_KICK2 == VG_PRESSED)
			   {
				   VG_reset_input(); 
				   VG_skip_scene = true;  
				   title_sequence = 1; 
			   } 

			   // Game over... 
			   if(VG_TRAINING == false) 
			   if(VG_PLAYER1_WON == false && VG_GAME_MODE != VG_VERSUS_MODE)
			   if((int)TimerGetTime() > title_timer || VG_skip_scene == true)
			   if(title_sequence == 1)
			   {
				   VG_reset_input(); 
				   sprite[3].alpha = 0.0f;
				   new_counter[1].alpha = 0.0f; 
				   title_timer = (int)TimerGetTime() + 3000;
				   title_sequence = 2;
			   }

			   // Game over...   
			   if(VG_TRAINING == false)  
			   if(title_sequence == 2) 
			   {   

				   VG_reset_input(); 

				   temp_speed = (0.00025f/VG_slowmof)*(float)f_rate;

				   sprite[2].x += temp_speed; 

				   if(sprite[2].x > sprite[2].mov_x + (sprite[2].width*0.85f))
				   { 
					   if(VG_GAME_MODE == VG_STORY_MODE)
					   {
						   VG_KOED_CHARACTER = VG_1_CHARACTER;
						   VG_KO_sfx = true; 

						   Set_Sprite(2, sprite[2].base_anim+16, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned

						   title_timer = (int)TimerGetTime() + 750;
						   title_sequence = 3;
					   }
					   else
					   {
						   VG_KOED_CHARACTER = VG_1_CHARACTER;
						   VG_KO_sfx = true; 

						   Set_Sprite(2, sprite[2].base_anim+16, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned

						   if(VG_1_CHARACTER == VG_SANG)
							   Set_Sprite(2, sprite[2].base_anim+2, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned
						   if(VG_1_CHARACTER == VG_TRAINER)
							   Set_Sprite(2, sprite[2].base_anim+2, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned

						   title_timer = (int)TimerGetTime() + 750;
						   title_sequence = 3;
					   } 
				   }
			   } 
			    
			   if((int)TimerGetTime() > title_timer)
			   if(title_sequence < 3)
				   VG_reset_input(); 
			    
			   // Game over...
			   if(VG_TRAINING == false) 
			   if((int)TimerGetTime() > title_timer)  
			   if(title_sequence == 3) 
			   {
					if(VG_GAME_MODE == VG_STORY_MODE || ( VG_GAME_MODE == VG_ARCADE_MODE && VG_1_CREDITS != 0))
					{
						sprite[4].alpha = 1.0f;
						Set_Sprite(4, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned
						new_counter[9].alpha = 1.0f;
					//	place_sfx = true;

						if(VG_1_HUD_GO == true)   
						{ 
							VG_reset_input();   

							if(VG_1_special1_sfx == 0)
								VG_1_special1_sfx = 2;   

							Set_Sprite(2, sprite[2].base_anim, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned

						//	sprite[4].alpha = 0.0f;
							new_counter[9].alpha = 0.0f;

							title_timer = (int)TimerGetTime() + 2000;
							title_sequence = 5;
						}

						if(VG_1_HUD_BACK == true)
						{
							VG_reset_input(); 
							vg_gameover_sfx = true;

						    VG_KOED_CHARACTER = VG_1_CHARACTER;
						    VG_KO_sfx = true; 

							new_counter[9].alpha = 0.0f;

							Set_Sprite(4, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned

							title_timer = (int)TimerGetTime() + 3000;
							title_sequence = 4;
						}

					}
					else
					{
						sprite[4].alpha = 1.0f;
						vg_gameover_sfx = true;

						title_timer = (int)TimerGetTime() + 3000;
						title_sequence = 4;
					}
			   }
			   // Game over...
			   if(VG_TRAINING == false)  
			   if((int)TimerGetTime() > title_timer)  
			   if(title_sequence == 4)
			   { 
					vg_next_episode = 0;   
					vg_next_scene    = 11; // Score sheet

					next_scene = true; 
			   }
			   // Continue playing... 
			   if(VG_TRAINING == false)  
			   if((int)TimerGetTime() > title_timer)  
			   if(title_sequence == 5)
			   { 
					vg_next_episode = 6;   
					vg_next_scene    = 1;

					if(VG_GAME_MODE == VG_ARCADE_MODE)
					{
						vg_continued_arcade = true;
						VG_AI_active = true;
						vg_selected_character = true;
					}

					next_scene = true; 
			   }

			   if((!(VG_PLAYER1_WON == false && VG_GAME_MODE != VG_VERSUS_MODE)) || VG_TRAINING == true)
			   if((int)TimerGetTime() > title_timer || VG_skip_scene == true)
			   if(title_sequence == 1)
			   { 

				   // Beat game...
				   if(VG_2_CHARACTER != VG_SANG)
				   {
					   vg_next_episode = 6;   
					   vg_next_scene    = 1;   
				   }
				   else
				   {
					   vg_next_episode = 0;   
					   vg_next_scene    = 11;   
				   }

				   // Game over screen...
				   if(VG_AI_active == true)
				   if(VG_PLAYER1_WON == false)   
				   {
					   vg_next_episode = 0;   
					   vg_next_scene    = 11;   
				   }

				   if(VG_TRAINING == true)  
				   {

					    vg_defeat_count = 0;

						VG_BATTLE_ROUND = 1;

						vg_selected_character = false;
						vg_defeat_count = 0;
				
						VG_map_last_point = 0;
						VG_map_next_point = 0; 

						for(int i =0;i<15;i++) 
							VG_DEFEATED_GUYS[i] = -1;

						VG_1_CHARACTER = VG_GYEONG;
						VG_2_CHARACTER = VG_GYEONG;

						VG_SKIP_INTRO = false; 

						VG_1_WINS = 0;
						VG_2_WINS = 0;

						vg_next_episode = 6;    
						vg_next_scene    = 1;  
 
				   }

				   next_scene = true;   

			   }
		   }
		   if(VG_IS_VERSUS_SCREEN == true)      
		   {

			   if(VG_skip_scene == false)
			   if((int)TimerGetTime() > VG_start_timer)
			   if(VG_1_PUNCH == VG_PRESSED || VG_1_PUNCH2 == VG_PRESSED || VG_1_KICK == VG_PRESSED || VG_1_KICK2 == VG_PRESSED)
			   {
				   VG_1_PUNCH = VG_RESET;
				   VG_1_PUNCH2 = VG_RESET;
				   VG_1_KICK = VG_RESET;
				   VG_1_KICK2 = VG_RESET;

				   VG_skip_scene = true;
				   title_sequence = 2; 
			   }

			   if((int)TimerGetTime() > title_timer)
			   if(title_sequence == 1)   
			   {   
				   if(VG_AI_active == false) 
				   {
					   new_counter[8].alpha = 1.0f;
					   new_counter[7].alpha = 1.0f; 
				   }

				   if(DISPLAY_1_MOVES_DURING_VS == 1)
					   new_counter[7].alpha = 1.0f;

				   Set_Sprite(1, 0, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned
				    
				   vg_scalex = sprite[1].width;
				   vg_scaley = sprite[1].height;

				   sprite[1].mov_x = sprite[1].x;
				   sprite[1].mov_y = sprite[1].y;

				   sprite[1].width  *= 3.0f; 
				   sprite[1].height *= 3.0f;  
				     
				   sprite[1].x -= sprite[1].width/3.0f;
				   sprite[1].y -= sprite[1].height/3.0f;

				   sprite[1].alpha = 1.0f;
				   sprite[1].flash_target = true; 
				   sprite[1].flash_timer = (int)TimerGetTime() + 15;

				   VG_ZOOM_VS = 0;

				   title_timer = (int)TimerGetTime() + 3500;
				   title_sequence++;  
			         
			   }          

			   if(VG_ZOOM_VS == 0)
			   if(title_sequence == 2)      
			   {    
				    
				   if(VG_slowmof > 0.0f) 
					   temp_speed = (0.00100f/VG_slowmof)*(float)f_rate;

				   if(sprite[1].width > vg_scalex)
				   {
					   sprite[1].width -= temp_speed;
					   sprite[1].x += temp_speed/2;

					   if(sprite[1].width <= vg_scalex)
						   sprite[1].width = vg_scalex;
				   }
				   else
				   {
					   sprite[1].width = vg_scalex;
					   sprite[1].x = sprite[1].mov_x;
					   sprite[1].height = vg_scaley; 
					   sprite[1].y = sprite[1].mov_y;

					   VG_ZOOM_VS = 1;
				   }

				   if(sprite[1].height > vg_scaley)
				   {
					   sprite[1].height -= temp_speed;
					   sprite[1].y += temp_speed/2;

					   if(sprite[1].height <= vg_scaley)
						   sprite[1].height = vg_scaley;
				   }
				   else
				   {
					   sprite[1].width = vg_scalex;
					   sprite[1].x = sprite[1].mov_x;
					   sprite[1].height = vg_scaley; 
					   sprite[1].y = sprite[1].mov_y;

					   VG_ZOOM_VS = 1;
				   }

			   }  
			      
			    if(start_sequence == 1)  
				if(title_sequence == 2)  
				if( ((int)TimerGetTime() > (title_timer - 1000)) ) // || VG_skip_scene == true
				{
			       temp_speed = (0.00025f/VG_slowmof)*(float)f_rate;

				   Set_Sprite(0, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned

				   Set_Sprite(1, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned

				   sprite[2].x -= temp_speed; 
				   sprite[3].x += temp_speed; 

				   new_counter[1].alpha = 0.0f; // P1 name...
				   new_counter[2].alpha = 0.0f; // P2 name...
    
				   if(VG_slowmof > 0.0f) 
					   temp_speed = (0.00050f/VG_slowmof)*(float)f_rate;
				     
				   if(sprite[1].width > 0.0001f)
				   {
				       sprite[1].width -= temp_speed; 
					   sprite[1].x += temp_speed/2;
					    
					   sprite[1].height -= temp_speed;
					   sprite[1].y += temp_speed/2;
				   }
				   else  
					   sprite[1].alpha = 0.0f; 
				    
				}        
				  
			   if((int)TimerGetTime() > title_timer)     
			   if(title_sequence == 2)  
			   {      
					// testing...    
				    
				  //  VG_1_CHARACTER = VG_KENNEDY; // test...
				//	VG_2_CHARACTER = VG_SHO; // test...
				//    VG_BACKGROUND = VG_SANG;
				//	VG_BACKGROUND = VG_SHRINE;
				//	VG_BATTLE_ROUND = 8; 

				//   VG_IS_AN_ALTER = true;

				   if(VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_DUELLING)
					   VG_BACKGROUND = VG_SHRINE;

				   vg_next_episode = 5;    
				   vg_next_scene  = VG_BACKGROUND;   
			 
				   next_scene = true;  
				    
			   }

			   if(start_sequence == 0)        
			   { 
				   if(VG_slowmof > 0.0f)
					   temp_speed = (0.00140f/VG_slowmof)*(float)f_rate;
			     
				   sprite[2].x -= temp_speed;   
				   sprite[3].x += temp_speed;     
			     
				   if(sprite[2].x <= sprite[2].mov_x || sprite[3].x > sprite[3].mov_x)   
				   {      
					   sprite[2].x = sprite[2].mov_x; 
					   sprite[3].x = sprite[3].mov_x;   

					   sprite[2].flash_target = true; 
					   sprite[2].flash_timer = (int)TimerGetTime() + 15;
					   sprite[3].flash_target = true; 
					   sprite[3].flash_timer = (int)TimerGetTime() + 15;

					   new_counter[1].alpha = 1.0f;
					   new_counter[2].alpha = 1.0f;

					   start_sequence++;
				   }

			   }

		   } // VG_IS_VERSUS_SCREEN == true...
	   }


    // ******************************************************************************//
    //                            0-0  (RETRO ARMY SCREEN)                           //
    // ******************************************************************************//
				                 
       // Title Screen Stuff...
       if(!mode)   
       if(episode == 0 && scene == 0)     
       {    
                    
           if(title_sequence == 0)     
           { 

			   VG_ROUND = 1;

			   hud[1].alpha=0.0f;
			    
               title_sequence++; 
			       
               sprite[0].alpha = 0.0;
			   sprite[8].alpha = 0.0; 

               VG_start_stamp_Y = sprite[1].y;
               VG_start_stamp_X = sprite[1].x;

               sprite[1].y -= sprite[1].height/2;
               
               sprite[3].alpha = 0.0; 
               sprite[4].alpha = 0.0; 
               sprite[5].alpha = 0.0;
               sprite[6].alpha = 0.0; 
               
               cos_scroll = 0.0f;

			   sprite[2].flash_target = true; 
			   sprite[2].flash_timer = (int)TimerGetTime() + 15;
               
           }   

			// Handle flash code...
			if((int)TimerGetTime() > sprite[2].flash_timer)
			    sprite[2].flash_target = false;

           if(title_sequence == 1)       
           {   
             
             cos_scroll += ( (0.001f) ); 
             
             if(cos_scroll > 1.5f )    
                cos_scroll = 1.5f; 
                                     
             temp_speed = 0.00075f*(cos(cos_scroll));  
             
             sprite[1].y += temp_speed * (float)f_rate; 
                 
             if(VG_start_stamp_Y < sprite[1].y)
             {    
                 sprite[1].y = VG_start_stamp_Y;
                 title_sequence++;
             }                
                  
           } 
             
           if(title_sequence == 2)      
           {  
             
             Set_Sprite(1, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned
             
             sprite[0].alpha = 1.0;
             
             vg_stamp_sfx = true; 
                               
         //    red_swipe = true;
         //    swipe_color = COLOR_WHITE;
         //    red_timer = (int)TimerGetTime() + 50;
               
             title_timer = (int)TimerGetTime()+500;
             
             title_sequence++;
             
           } 
           
           if(title_sequence == 3)
           if( (int)TimerGetTime() > title_timer )
           {                              
             temp_speed = 0.00100f*(float)f_rate;

             sprite[2].x += temp_speed; 
 
             if(sprite[2].x > sprite[0].x)
             {   
                 sprite[2].x = sprite[0].x;
             //    title_timer = (int)TimerGetTime()+1000;
                 title_sequence++;
             }   
           }  
            
           if( (int)TimerGetTime() > title_timer )
           if(title_sequence == 4) 
           { 
                
       //      title_timer = (int)TimerGetTime()+1000;                         
             title_sequence++;
           }              
           
           if( (int)TimerGetTime() > title_timer )
           if(title_sequence == 5) 
           { 
             Set_Sprite(3, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned
             sprite[3].alpha = 1.0;
             
             sprite[2].alpha = 0.0;
             
          //   sparkle_sfx = true;
             
             title_timer = (int)TimerGetTime()+300;                         
             title_sequence++;    
           }             
           if( (int)TimerGetTime() > title_timer )
           if(title_sequence == 6) 
           { 
             
             Set_Sprite(4, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned
             sprite[4].alpha = 1.0;
             
          //   sparkle_sfx = true;
                                                       
             title_timer = (int)TimerGetTime()+300;                         
             title_sequence++;                             
           }      
           if( (int)TimerGetTime() > title_timer ) 
           if(title_sequence == 7) 
           {  
                                  
             Set_Sprite(5, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned 
             sprite[5].alpha = 1.0;
                
           //  sparkle_sfx = true; 
                                                      
             title_timer = (int)TimerGetTime()+300;                          
             title_sequence++;                             
           } 
           if( (int)TimerGetTime() > title_timer )    
           if(title_sequence == 8) 
           {  
                                  
           //  Set_Sprite(0, 1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned 

             sprite[8].alpha = 1.0;  
 
         //    teddy_roar_sfx = true; 
                                          
             title_timer = (int)TimerGetTime()+500;                         
             title_sequence++;  
                                        
           }              
                                
           if( (int)TimerGetTime() > title_timer )
           if(title_sequence == 9) 
           {              
               title_sequence++;  
               next_scene = true;

               vg_next_episode = 1; 
			   vg_next_scene  = 0;  

           }    
            
           if(title_sequence >= 3)   
           {          
                              
             temp_speed = 0.00075f*(float)f_rate; 
              
             sprite[1].x += temp_speed;    
                               
             cos_scroll += ( (0.001f) );  
             
             if(cos_scroll > 1.5f )    
                cos_scroll = 1.5f; 
                                     
             temp_speed = 0.00075f*(cos(cos_scroll)); 
             
             sprite[1].y -= temp_speed * (float)f_rate; 
                                     
           }  
                                            
       }    
	    
	    
    // ******************************************************************************//
    //                           10-0  (LOADING SCREEN)                              //
    // ******************************************************************************//

   // Title Screen Stuff... 
   if(next_scene == false)
   if(episode == 10 && scene == 0)  
   {  

       vg_next_episode = 0;   
       vg_next_scene    = 0;  
	       
       next_scene = true;     

   }         

    // ******************************************************************************//
    //                              0-1  (TITLE SCREEN)                              //
    // ******************************************************************************//
				                 
       // Title Screen Stuff...  
       if(!mode) 
//       if(next_scene == false)  
       if(episode == 0 && scene == 1)      
       {        
		   VG_SUBBOSS = 0;

		   if((int)TimerGetTime() > GRID_TIMER)
		   {
			   GRID_TIMER = (int)TimerGetTime() + 3000;

			   GRID_LEFT_RIGHT = rand()%2; 
			   GRID_UP_DOWN = rand()%2;
		   }
/*#ifdef XB1
			// Scroll sheet box grid...
			if(GRID_LEFT_RIGHT == 0)
			{
				sprite[1].x += VG_TITLE_SCROLL_SPEED * (float)f_rate;
			}
			else
			{ 
				sprite[1].x -= VG_TITLE_SCROLL_SPEED * (float)f_rate;
			} 
			if(GRID_UP_DOWN == 0)
			{
				sprite[1].y -= VG_TITLE_SCROLL_SPEED * (float)f_rate;
			}
			else
			{
				sprite[1].y += VG_TITLE_SCROLL_SPEED * (float)f_rate;
			}
#elif defined PS4 || defined SWITCH*/
		   // Scroll sheet box grid...
		   if (GRID_LEFT_RIGHT == 0)
		   {
			   sprite[1].u[0] += VG_TITLE_SCROLL_SPEED * (float)f_rate;
			   sprite[1].u[1] += VG_TITLE_SCROLL_SPEED * (float)f_rate;
			   sprite[1].u[2] += VG_TITLE_SCROLL_SPEED * (float)f_rate;
			   sprite[1].u[3] += VG_TITLE_SCROLL_SPEED * (float)f_rate;
		   }
		   else
		   {
			   sprite[1].u[0] -= VG_TITLE_SCROLL_SPEED * (float)f_rate;
			   sprite[1].u[1] -= VG_TITLE_SCROLL_SPEED * (float)f_rate;
			   sprite[1].u[2] -= VG_TITLE_SCROLL_SPEED * (float)f_rate;
			   sprite[1].u[3] -= VG_TITLE_SCROLL_SPEED * (float)f_rate;
		   }
		   if (GRID_UP_DOWN == 0)
		   {
			   sprite[1].v[0] -= VG_TITLE_SCROLL_SPEED * (float)f_rate;
			   sprite[1].v[1] -= VG_TITLE_SCROLL_SPEED * (float)f_rate;
			   sprite[1].v[2] -= VG_TITLE_SCROLL_SPEED * (float)f_rate;
			   sprite[1].v[3] -= VG_TITLE_SCROLL_SPEED * (float)f_rate;
		   }
		   else
		   {
			   sprite[1].v[0] += VG_TITLE_SCROLL_SPEED * (float)f_rate;
			   sprite[1].v[1] += VG_TITLE_SCROLL_SPEED * (float)f_rate;
			   sprite[1].v[2] += VG_TITLE_SCROLL_SPEED * (float)f_rate;
			   sprite[1].v[3] += VG_TITLE_SCROLL_SPEED * (float)f_rate;
		   }
//#endif


		    if(QUICK_PLAY == 1)   
			{ 
				VG_AI_active = false;
				vg_next_episode = 5;     
				vg_next_scene  = VG_BACKGROUND;   
				next_scene = true; 
			}
			 
			if(title_sequence != 2) 
			{
				if(VG_page_no == 0)
				{
					VG_IS_AN_ALTER = false;

					VG_IS_AN_ALTER_P1 = false;
					VG_IS_AN_ALTER_P2 = false;

					VG_TRAINING = false;

					sprintf( new_counter[1].word, "NORMAL MODE"); 

					new_counter[1].alpha = 1.0f;          
					new_counter[1].id = 0;  

					new_counter[1].type = 0;  // Large Font...
					new_counter[1].right = false;

					new_counter[1].x = -0.13f;                
					new_counter[1].y = -0.03f;    	       

					new_counter[1].w = new_counter[1].x - 0.026f;   
					new_counter[1].z = new_counter[1].y - 0.015f;
			     
					new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
					new_counter[1].box_height = new_counter[1].height - 0.015f;	

					sprintf( new_counter[2].word, "VERSUS MODE"); 

					new_counter[2].alpha = 1.0f;           
					new_counter[2].id = 0; 

					new_counter[2].type = 0;  // Large Font...
					new_counter[2].right = false;


					new_counter[2].x = -0.13f;             
					new_counter[2].y = new_counter[1].y - 0.06f;   	      

					new_counter[2].w = new_counter[2].x - 0.026f;   
					new_counter[2].z = new_counter[2].y - 0.015f;

					new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
					new_counter[2].box_height = new_counter[2].height - 0.015f;	

					sprintf( new_counter[3].word, "OPTION MODE"); 

					new_counter[3].alpha = 1.0f;           
					new_counter[3].id = 0; 

					new_counter[3].type = 0;  // Large Font...
					new_counter[3].right = false;
				     
					new_counter[3].x = -0.13f;             
					new_counter[3].y = new_counter[2].y - 0.06f;   	      

					new_counter[3].w = new_counter[3].x - 0.026f;   
					new_counter[3].z = new_counter[3].y - 0.015f;

					new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
					new_counter[3].box_height = new_counter[3].height - 0.015f;	

					sprintf( new_counter[4].word, " EXIT GAME"); 

					new_counter[4].alpha = 0.0f;                
					new_counter[4].id = 0;  
				    
					new_counter[4].type = 0;  // Large Font...
					new_counter[4].right = false;
				            
					new_counter[4].x = -0.13f;             
					new_counter[4].y = new_counter[3].y - 0.06f;       	      
				 
					new_counter[4].w = new_counter[4].x - 0.026f;    
					new_counter[4].z = new_counter[4].y - 0.015f;

					new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
					new_counter[4].box_height = new_counter[4].height - 0.015f;	

				}
				if(VG_page_no == 1)
				{
					sprintf( new_counter[1].word, "ARCADE MODE"); 

					new_counter[1].alpha = 1.0f;          
					new_counter[1].id = 0;  

					new_counter[1].type = 0;  // Large Font...
					new_counter[1].right = false;

					new_counter[1].x = -0.13f;                
					new_counter[1].y = -0.03f;    	       

					new_counter[1].w = new_counter[1].x - 0.026f;   
					new_counter[1].z = new_counter[1].y - 0.015f;
			     
					new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
					new_counter[1].box_height = new_counter[1].height - 0.015f;	

					sprintf( new_counter[2].word, "STORY  MODE"); 

					new_counter[2].alpha = 1.0f;           
					new_counter[2].id = 4; 
				     
					new_counter[2].type = 0;  // Large Font...
					new_counter[2].right = false;

				  
					new_counter[2].x = -0.13f;              
					new_counter[2].y = new_counter[1].y - 0.06f;   	      

					new_counter[2].w = new_counter[2].x - 0.026f;   
					new_counter[2].z = new_counter[2].y - 0.015f;

					new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
					new_counter[2].box_height = new_counter[2].height - 0.015f;	

					sprintf( new_counter[3].word, " SURVIVAL"); 

					new_counter[3].alpha = 1.0f;            
					new_counter[3].id = 0; 

					new_counter[3].type = 0;  // Large Font...
					new_counter[3].right = false;
				     
					new_counter[3].x = -0.13f;             
					new_counter[3].y = new_counter[2].y - 0.06f;   	      

					new_counter[3].w = new_counter[3].x - 0.026f;   
					new_counter[3].z = new_counter[3].y - 0.015f;

					new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
					new_counter[3].box_height = new_counter[3].height - 0.015f;	

					sprintf( new_counter[4].word, " TRAINING");

					new_counter[4].alpha = 1.0f;                 
					new_counter[4].id = 0;  
				     
					new_counter[4].type = 0;  // Large Font...
					new_counter[4].right = false; 
				           
					new_counter[4].x = -0.13f;             
					new_counter[4].y = new_counter[3].y - 0.06f;       	      
				 
					new_counter[4].w = new_counter[4].x - 0.026f;    
					new_counter[4].z = new_counter[4].y - 0.015f;

					new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
					new_counter[4].box_height = new_counter[4].height - 0.015f;	

				}  
				if(VG_page_no == 2)
				{
					sprintf( new_counter[1].word, " STANDARD"); 

					new_counter[1].alpha = 1.0f;          
					new_counter[1].id = 0;  

					new_counter[1].type = 0;  // Large Font...
					new_counter[1].right = false;
					 
					new_counter[1].x = -0.13f;                 
					new_counter[1].y = -0.03f;    	       

					new_counter[1].w = new_counter[1].x - 0.026f;   
					new_counter[1].z = new_counter[1].y - 0.015f;
			     
					new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
					new_counter[1].box_height = new_counter[1].height - 0.015f;	

					if(VG_DUELLISTS_UNLOCKED == 0)
						sprintf( new_counter[2].word, "  ??????"); 
					else
						sprintf( new_counter[2].word, " DUELLING"); 

					new_counter[2].alpha = 1.0f;            
					new_counter[2].id = 4;   
				     
					new_counter[2].type = 0;  // Large Font...
					new_counter[2].right = false;

				  
					new_counter[2].x = -0.13f; // was -0.13f               
					new_counter[2].y = new_counter[1].y - 0.06f;   	      

					new_counter[2].w = new_counter[2].x - 0.026f;   
					new_counter[2].z = new_counter[2].y - 0.015f;

					new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
					new_counter[2].box_height = new_counter[2].height - 0.015f;	

					new_counter[3].alpha = 0.0f; 
					new_counter[4].alpha = 0.0f;  

					 
					new_counter[3].x = -0.13f;  

					if(VG_TURBO_UNLOCKED == 0)
						sprintf( new_counter[3].word, "  ??????"); // HARD  FIGHT
					else 
					{ 
						new_counter[3].x = -0.12f; // was -0.13f
						sprintf( new_counter[3].word, "  TURBO"); // HARD  FIGHT
					}
					 
					new_counter[3].alpha = 1.0f;            
					new_counter[3].id = 0; 

					new_counter[3].type = 0;  // Large Font... 
					new_counter[3].right = false;
				             
					new_counter[3].y = new_counter[2].y - 0.06f;   	       

					new_counter[3].w = new_counter[3].x - 0.026f;   
					new_counter[3].z = new_counter[3].y - 0.015f;

					new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
					new_counter[3].box_height = new_counter[3].height - 0.015f;	

					if(VG_MASTER_UNLOCKED == 0)
						sprintf( new_counter[4].word, "  ??????"); // SUPER FIGHT
					else
					{ 
						sprintf( new_counter[4].word, "  MASTER"); // SUPER FIGHT
					}

					new_counter[4].alpha = 1.0f;                 
					new_counter[4].id = 0;  
				     
					new_counter[4].type = 0;  // Large Font...
					new_counter[4].right = false; 
				           
					new_counter[4].x = -0.13f;             
					new_counter[4].y = new_counter[3].y - 0.06f;       	      
				 
					new_counter[4].w = new_counter[4].x - 0.026f;    
					new_counter[4].z = new_counter[4].y - 0.015f;

					new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
					new_counter[4].box_height = new_counter[4].height - 0.015f;	

				}  				  
			} 
			  
			if(VG_P1_USING == VG_KEYBOARD)
				sprintf( new_counter[6].word, "%c-%c MOVE  %c: SELECT %c: BACK^&RETRO ARMY LTD. 2015-2019", VG_P1_UP_KEY_DSY, VG_P1_DOWN_KEY_DSY, VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY);
			else
				sprintf( new_counter[6].word, "¦-§ MOVE  ÷: SELECT ø: BACK^&RETRO ARMY LTD. 2015-2019");

		    if(title_sequence == 0)    
		    { 
				VG_ARCADE_TYPE = VG_ARCADE_STANDARD;

				VG_Display_moves = false;

				VG_SURVIVAL_ROUND = 1;

				VG_1_SURVIVAL_HEALTH = 2000;
				VG_SURVIVAL = false;
				VG_SURVIVAL_WINS = 0;

			//	VG_1_Vs_wins = 0;
			//	VG_2_Vs_wins = 0;
			//	VG_Vs_draws = 0;

			    memset(VG_1_arrests, 0, sizeof(VG_1_arrests) );
			    memset(VG_2_arrests, 0, sizeof(VG_2_arrests) );

				VG_1_arrests_count = 0; 
				VG_2_arrests_count = 0;

			    memset(VG_1_perfects, 0, sizeof(VG_1_perfects) );
			    memset(VG_2_perfects, 0, sizeof(VG_2_perfects) );

				VG_1_perfect_count = 0;
				VG_2_perfect_count = 0;

				VG_1_Temp_perfects = 0;
				VG_2_Temp_perfects = 0;

				VG_1_Temp_arrests = 0;
				VG_2_Temp_arrests = 0;

				VG_1_CREDITS = 4;
				VG_2_CREDITS = 4;

				VG_AI_LEVEL = 1;
				 
				VG_1_EQUIPMENT = EQUIPMENT_ALL;
				VG_2_EQUIPMENT = EQUIPMENT_ALL;

				VG_ROUND_CONDITIONS = CONDITION_NONE;

				VG_GAME_MODE = VG_ARCADE_MODE;

				#if IS_FULL_STEAM == 1  

					if (STEAM_ACTIVE == true)
					{
						//g_SteamLeaderboards_finalscore->VG_DownloadScores(); 
						//g_SteamLeaderboards_survivalscore->VG_DownloadScores(); 
					}

				#endif

				VG_1_TOTAL_MINS = 0;
				VG_1_TOTAL_SECS = 0; 

				VG_1_TOTAL_perfects = 0;   
				VG_2_TOTAL_perfects = 0;

				VG_1_TOTAL_arrests = 0;
				VG_2_TOTAL_arrests = 0;

				memset(VG_1_perfects, 0, sizeof(VG_1_perfects));
				memset(VG_2_perfects, 0, sizeof(VG_2_perfects));	

				VG_TRAINING = false;

				nogo_timer = 0;

			    VG_voice_delay = (int)TimerGetTime() + 500;

				stop_vg_amb_prison_sfx = true;
				stop_vg_amb_traffic_sfx = true;
				stop_vg_amb_van_sfx = true;		
				stop_vg_amb_subway_sfx = true;
				stop_vg_amb_duel_sfx = true;

				VG_BATTLE_ROUND = 1;

				vg_selected_character = false;
				vg_defeat_count = 0;
				
				VG_map_last_point = 0;
				VG_map_next_point = 0;

				for(int i =0;i<15;i++) 
					VG_DEFEATED_GUYS[i] = -1;

				VG_1_CHARACTER = VG_GYEONG;
				VG_2_CHARACTER = VG_GYEONG;

				VG_SKIP_INTRO = false;

				VG_1_WINS = 0;
				VG_2_WINS = 0;

				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false;  

				VG_1_HUDUP = false;
				VG_2_HUDUP = false;

			    VG_ROUND = 1;
				 
				new_counter[6].alpha = 1.0f;                    
				new_counter[6].id = 2;        
				  
				new_counter[6].type = 1;  // Small Font...
				new_counter[6].right = false;
				 
				new_counter[6].x = -0.28f;              
				new_counter[6].y = new_counter[4].y - VG_BOTTOM_TEXT_OFFSET;  	      

				new_counter[6].w = new_counter[6].x - 0.026f;   
				new_counter[6].z = new_counter[6].y - 0.015f;

				new_counter[6].box_width = strlen(new_counter[6].word)   *  0.026f;
				new_counter[6].box_height = new_counter[6].height - 0.015f;	

				VG_SELECTED = 0;
				 
				title_sequence++;   

				start_sequence = 0;

				if(VG_played_title == -1) 
				{ 
					sprite[2].alpha = 0.0f;
					start_timer = (int)TimerGetTime() + 250;
					start_sequence = 1;
				}  
				else
					Set_Sprite(2, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Tm stuff...

				if(VG_BACK_TO_SELECTION == true)
				{
					VG_SELECTED = VG_BACK_SELECTED;
					VG_page_no = 1;
					title_sequence = 1;
					sprite[2].alpha = 1.0f; 
					start_sequence = 0;
					Set_Sprite(2, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Tm stuff...
					VG_played_title = 1;
				}

				VG_BACK_TO_SELECTION = false;
			}

			// Logo intro...
			if(start_sequence == 1)
			if((int)TimerGetTime() > start_timer)
			{
				VG_played_title = 1;  
				sprite[2].alpha = 1.0f; 
				sprite[2].flash_target = true; 
				sprite[2].flash_timer = (int)TimerGetTime() + 25;
				Set_Sprite(2, 0, PLAY, ANIM_SPRITE, ANIM_WALKING); // Chains...
				start_timer = (int)TimerGetTime() + 500;
				start_sequence = 2; 
			}

			// Logo intro...
			if(start_sequence == 2)
			if((int)TimerGetTime() > start_timer) 
			{
				VG_verdict_sfx = true;
				VG_titlevoice_sfx = true;

				sprite[2].flash_target = true; 
				sprite[2].flash_timer = (int)TimerGetTime() + 25;
				Set_Sprite(2, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Verdict...
				start_timer = (int)TimerGetTime() + 500;
				start_sequence = 3;
			}   
			 
			// Logo intro...  
			if(start_sequence == 3) 
			if((int)TimerGetTime() > start_timer)      
			{
				VG_guilty_sfx = true;
				sprite[2].flash_target = true; 
				sprite[2].flash_timer = (int)TimerGetTime() + 25;
				Set_Sprite(2, 2, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Guilty...

				sprite[2].bump_this = true;
				sprite[2].bump_this_timer = (int)TimerGetTime() + 75;

				start_timer = (int)TimerGetTime() + 250;
				start_sequence = 4;
			}

			// Logo intro...			 
			if(start_sequence == 4) 
			if((int)TimerGetTime() > title_timer)  
			{
				Set_Sprite(2, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Tm stuff...
				start_sequence = 0;
			}

			VG_BACK_SELECTED = VG_SELECTED;

		    if(VG_1_HUD_BACK == true)       
		    {
				if(VG_page_no == 1)   
				{ 
					VG_page_no = 0;
					title_sequence = 1; 
					VG_SELECTED = 0; 
				}
				if(VG_page_no == 2)
				{
					VG_page_no = 1;
					title_sequence = 1; 
					VG_SELECTED = 0; 
				}

				VG_1_HUD_BACK = false;

		    }    		      
		    if(title_sequence == 1)
		    {
				 
			new_counter[1].id = 3; // NORMAL

			if(VG_page_no == 1)
				new_counter[2].id = 3; //  VERSUS
			else
				new_counter[2].id = 3;

			if(VG_page_no == 1)
				new_counter[3].id = 3; // OPTION
			else
				new_counter[3].id = 3;

			new_counter[4].id = 3; // EXIT

			testX = hud_mouseX - (-camX);                                                 
			testY = hud_mouseY - (-camY); 

			if(VG_1_HUDDOWN == VG_PRESSED)
			{
				vg_titlemove_sfx = true;
				VG_SELECTED++;

				if(VG_page_no == 0)
				if(VG_SELECTED > 2)  
					VG_SELECTED = 0;

				if(VG_page_no != 0)
				if(VG_SELECTED > 3)  
					VG_SELECTED = 0;

				VG_1_HUDDOWN = false;
				VG_2_HUDDOWN = false;
			} 

			if(VG_1_HUDUP == VG_PRESSED)
			{ 
				vg_titlemove_sfx = true;
				VG_SELECTED--;

				if(VG_page_no == 0)
				if(VG_SELECTED < 0)
					VG_SELECTED = 2; 

				if(VG_page_no != 0)
				if(VG_SELECTED < 0)
					VG_SELECTED = 3; 

				VG_1_HUDUP = false; 
				VG_2_HUDUP = false; 
			}

			if(VG_SELECTED == 0) // NORMAL MODE / ARCADE MODE / STANDARD
			{   
				new_counter[1].id = 0;
				 
				if(VG_1_HUD_GO == true)
				{
					VG_1_PUNCH = VG_RESET; 
					VG_1_PUNCH2 = VG_RESET; 
					VG_1_KICK = VG_RESET; 
					VG_1_KICK2 = VG_RESET;
					VG_1_DX_A = false;
					VG_1_DX_B = false;
					VG_1_HUD_GO = false;

					VG_Flicker_HUD_Button_timer = 0;

					VG_1_DX_A_timer = (int)TimerGetTime() + 250;

					title_sequence++;
					title_timer = (int)TimerGetTime() + 500;
					vg_titleselect_sfx = true;
				} 
			}   
			if(VG_SELECTED == 1) // VERSUS MODE / STORY MODE / DUELLISTS
			{ 
				new_counter[2].id = 0; 
				
				if(VG_1_HUD_GO == true)  // VG_DUELLISTS_UNLOCKED
				{
					VG_1_PUNCH = VG_RESET;
					VG_1_PUNCH2 = VG_RESET;
					VG_1_KICK = VG_RESET;  
					VG_1_KICK2 = VG_RESET;
					VG_1_DX_A = false;
					VG_1_DX_B = false; 
					VG_1_HUD_GO = false;
					VG_1_HUD_BACK = false;

					VG_1_DX_A_timer = (int)TimerGetTime() + 250;

					// Go to next page...
					if(VG_page_no == 0 || VG_page_no == 1 || (VG_page_no == 2 && VG_DUELLISTS_UNLOCKED == 1)) 
					{
						VG_Flicker_HUD_Button_timer = 0;

						title_sequence++;
						title_timer = (int)TimerGetTime() + 500;
						vg_titleselect_sfx = true;
					}
				}

			} 
			if(VG_SELECTED == 2) // OPTIONS / TRAINING / TURBO
			{ 
				new_counter[3].id = 0;

				if(VG_1_HUD_GO == true)
				{
					VG_1_PUNCH = VG_RESET;
					VG_1_PUNCH2 = VG_RESET;
					VG_1_KICK = VG_RESET; 
					VG_1_KICK2 = VG_RESET;
					VG_1_DX_A = false;
					VG_1_DX_B = false;
					VG_1_HUD_GO = false;

					VG_1_DX_A_timer = (int)TimerGetTime() + 250;

					// Go to next page...
					if(VG_page_no == 0 || VG_page_no == 1 || (VG_page_no == 2 && VG_TURBO_UNLOCKED == 1))
					{
						VG_Flicker_HUD_Button_timer = 0;

						title_sequence++; 
						title_timer = (int)TimerGetTime() + 500;
						vg_titleselect_sfx = true;
					}
				}     

			} 
			if(VG_SELECTED == 3) // QUIT / BACK / MASTER
			{
				new_counter[4].id = 0;

				if(VG_1_HUD_GO == true)  
				{
					VG_1_PUNCH = VG_RESET;
					VG_1_PUNCH2 = VG_RESET;
					VG_1_KICK = VG_RESET; 
					VG_1_KICK2 = VG_RESET;
					VG_1_DX_A = false;
					VG_1_DX_B = false;
					VG_1_HUD_GO = false;

					VG_1_DX_A_timer = (int)TimerGetTime() + 250;

					// Go to next page...
					if(VG_page_no == 0 || VG_page_no == 1 || (VG_page_no == 2 && VG_MASTER_UNLOCKED == 1))
					{
						VG_Flicker_HUD_Button_timer = 0;

						title_sequence++;
						title_timer = (int)TimerGetTime() + 500;
						vg_titleselect_sfx = true;
					}
				}
			}

			} // title_sequence == 1
		      
		    if(title_sequence == 2)   
		    {

				if((int)TimerGetTime() > VG_Flicker_HUD_Button_timer)
				{
					VG_Flicker_HUD_Button_timer = (int)TimerGetTime() + 25;

					if(VG_SELECTED == 0) // NORMAL MODE / ARCADE MODE
					{
						if(new_counter[1].id == 0)
							new_counter[1].id = 3;
						else
							new_counter[1].id = 0;
					} 
					if(VG_SELECTED == 1) // VERSUS MODE / STORY MODE
					{
						
						if(new_counter[2].id == 0)
							new_counter[2].id = 3;
						else
							new_counter[2].id = 0;
					}   
					if(VG_SELECTED == 2) // OPTIONS / SURVIVAL
					{
						if(new_counter[3].id == 0)  
							new_counter[3].id = 3; 
						else 
							new_counter[3].id = 0;
					}
					if(VG_SELECTED == 3) // QUIT / BACK
					{
						if(new_counter[4].id == 0)
							new_counter[4].id = 3;
						else
							new_counter[4].id = 0;
					} 
				}  

				if((int)TimerGetTime() > title_timer)
				{
					if(VG_SELECTED == 0)  // NORMAL MODE / ARCADE MODE    
					{
						if(VG_page_no == 2) // STANDARD FIGHT
						{
							VG_ARCADE_TYPE = VG_ARCADE_STANDARD;
							VG_GAME_MODE = VG_ARCADE_MODE;
							VG_AI_active = true;
							VG_IS_VERSUS_SCREEN = true;
							vg_next_episode = 6;    
							vg_next_scene    = 1;  
							next_scene = true; 
						}
						if(VG_page_no == 1) 
						{
							VG_page_no = 2;
							title_sequence = 1;
						}

						if(VG_page_no == 0)
						{
							VG_page_no = 1;
							title_sequence = 1;
						}

					}  
					if(VG_SELECTED == 1) // VERSUS MODE / STORY MODE      
					{
						if(VG_page_no == 2 && VG_DUELLISTS_UNLOCKED == 1) // DUELLING
						{
							VG_1_CREDITS = 6;
							VG_2_CREDITS = 6;
							VG_ARCADE_TYPE = VG_ARCADE_DUELLING;
							VG_GAME_MODE = VG_ARCADE_MODE;
							VG_AI_active = true;
							VG_IS_VERSUS_SCREEN = true;
							vg_next_episode = 6;    
							vg_next_scene    = 1;  
							next_scene = true; 
						}
						if(VG_page_no == 1)
						{
							VG_GAME_MODE = VG_STORY_MODE;
							VG_AI_active = true;
							VG_IS_VERSUS_SCREEN = true;
							vg_next_episode = 6;     
							vg_next_scene    = 1;    
							next_scene = true;   
						}       
						if(VG_page_no == 0)
						{
							VG_GAME_MODE = VG_VERSUS_MODE;
							VG_AI_active = false;
							VG_IS_VERSUS_SCREEN = true;   
							vg_next_episode = 6;         
							vg_next_scene    = 1;       
							next_scene = true;         
						}  
					}          
					if(VG_SELECTED == 2) // OPTIONS / SURVIVAL                       
					{     
						if(VG_page_no == 2 && VG_TURBO_UNLOCKED == 1) // STANDARD FIGHT
						{
							VG_SURVIVAL = false;
							VG_ARCADE_TYPE = VG_ARCADE_TURBO;
							VG_GAME_MODE = VG_ARCADE_MODE;
							VG_AI_active = true;
							VG_IS_VERSUS_SCREEN = true;
							vg_next_episode = 6;    
							vg_next_scene    = 1;  
							next_scene = true; 
						}
						if(VG_page_no == 1)
						{
							VG_1_CREDITS = 0;
							VG_SURVIVAL = true;
							VG_ARCADE_TYPE = VG_ARCADE_STANDARD;
							VG_GAME_MODE = VG_ARCADE_MODE;
							VG_AI_active = true;
							VG_IS_VERSUS_SCREEN = true;
							vg_next_episode = 6;    
							vg_next_scene    = 1;  
							next_scene = true;    
						}       
						if(VG_page_no == 0)                                 
						{                                                     
							// For testing...                                   
						/*    VG_SKIP_INTRO = false;                                                                                                     
							VG_AI_active = true;        
							VG_TRAINING = false;         
							 
							VG_1_EQUIPMENT = EQUIPMENT_ALL; 
							VG_2_EQUIPMENT = EQUIPMENT_ALL;       
							       
							vg_next_episode = 5;                                                                   
 						               
							VG_BATTLE_ROUND = 8;

							VG_1_CHARACTER = VG_KENNEDY;                  
							VG_2_CHARACTER = VG_SANG;      

							VG_ROUND_CONDITIONS = CONDITION_NONE;  

							VG_GAME_MODE = VG_ARCADE_MODE;  
						  
							VG_BACKGROUND = VG_SANG;   
						    
							vg_next_scene = VG_BACKGROUND;

							next_scene = true;     */
							  
						/*	VG_GAME_MODE = VG_STORY_MODE;

							VG_SURVIVAL = false;

							VG_STORY_SETUP = VG_STORY_SCENE_WON;

							VG_CURRENT_STORY_SCENE = 0;

							VG_IS_VERSUS_SCREEN = false;
							  
							VG_PLAYER1_WON = true;      
							      
							VG_AI_active = true;   
							 
							VG_1_CHARACTER = VG_GYEONG;                 
							VG_2_CHARACTER = VG_GYEONG;  
							 
							vg_next_episode = 6;         
							vg_next_scene    = 2; // should be 2 

							next_scene = true;     */ 
							 
							vg_next_episode = 0;        
							vg_next_scene    = 2; // should be 2 

							next_scene = true; 

						}  
					} 
					if(VG_SELECTED == 3)  // QUIT / TRAINING
					{
						if(VG_page_no == 2 && VG_MASTER_UNLOCKED == 1) // STANDARD FIGHT
						{
							VG_ARCADE_TYPE = VG_ARCADE_MASTER;
							VG_GAME_MODE = VG_ARCADE_MODE;
							VG_AI_active = true;
							VG_IS_VERSUS_SCREEN = true;
							vg_next_episode = 6;    
							vg_next_scene    = 1;  
							next_scene = true; 
						}
						if(VG_page_no == 1)
						{
							VG_ARCADE_TYPE = VG_ARCADE_STANDARD;
							VG_GAME_MODE = VG_TRAINING_MODE;
							VG_AI_active = true;
							VG_TRAINING = true; 
							vg_next_episode = 6;     
							vg_next_scene    = 1;    
							next_scene = true;     
						}  
						if(VG_page_no == 0) 
						{
							done = true;
							quitting=false; 
						}
					}

				}

			}

	   } // if(episode == 0 && scene == 1)  


}

