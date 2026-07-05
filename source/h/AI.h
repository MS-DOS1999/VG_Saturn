
#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>
#include <math.h>    
#include "globals.h"           

extern void Animation_System(int loop, bool bullet_check, bool interrupt, bool pain_anim, bool fire);
extern void OnCreate(int sprite_id);
extern bool TestSpriteToShoot(int no_test, float x1, float y1, float x2, float y2, bool hulk, int target_id, int f_rate);
extern void GalleryScore(int the_score);
extern void Gravity(int f_rate1);  
extern float Node_Distance(float x1, float y1, float x2, float y2);
extern void Start_Game();  
extern bool Man_Shot(int guy_status, int guy_shot, int guy_shooting, int bullet_type, int f_rate);
extern void AI_Command(int f_rate);
extern int Is_Guy_In_Sight(float my_angle, float target_angle);
extern void Test_sprite_to_trigger(int loop);
extern int Find_Path(int loop, float destX, float destY); 
extern void Next_node(int loop, bool increase_counter);
extern void AI_Check_For_Enemies(int loop);
extern void Lay_Mine(float midX, float midY, int loop);
extern void Mine_Triggered(int guys_index, int mine_index, int loop);
extern void Remove_Bush(int row_x, int row_y); 
extern int Convert_Angle_To_Dir(float my_angle);
extern void Reposition_Unit(int loop);
extern int Get_Nearest_Depot(int loop, bool check);
extern int  New_Sprite(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int sideways, int upways, int state, int linked_sprite, int tex_id, int a_global, float angle, int p_type, int goto_point);
extern void Set_Sprite(int id, int anim, int state, int hud_or_sprite, bool reset);
extern bool New_FX(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int i_value, int i_type, int state, int linked_sprite, int tex_id, int i_value1, int i_value2, int i_value3);
extern bool Build_Man_Check(int loop, float x, float y, int build_type);
extern void Turn_Unit(int loop, int f_rate);
extern void Refresh_Pnts();  
extern bool Build_Something(int loop);
extern void Gunner_Command(int loop); 
extern void Group_Command();
extern void Reset_Build_Types(int loop);
extern void ShotIdle(int loop);
extern bool Is_Guy_In_Range(int loop, int target, float range);
extern void Squash_Test(int loop);
extern void Create_Defend_List();  
extern void Calculate_Bullets();
extern void Calculate_Lifebar();
extern int Calculate_TotalScore(int loop);
extern bool Calculate_Item(int item_value, int item_type, int the_item, int item_value1, int item_value2, int item_value3);
extern bool Spawn_A_Guy(int number_of_dudes, int best_point, bool buddy, int trap, int sprite_point, int goto_point);
extern bool Shoot_Ray(int loop, float x1, float y1, float x2, float y2, bool grey_test, bool shooting, float precision);
extern bool Pickup_Check(int loop, int the_item, int type);   
extern void Test_sprite_to_Obj(int loop, int target);
extern void Move_Sprite(int loop, int f_rate, bool direction);
extern void Test_Sprite_to_Fx(int loop, int f_rate); 
extern void Test_Fx_to_Fx(int loop, int f_rate); 
extern void Move_Vehicle(int loop, float x_pos, float y_pos, int f_rate);
extern void Vehicle_Anims(int loop);
extern int Test_Collision_Vehicle(int loop, float deltax, float deltay);
extern void Check_Crouch(int loop, bool loading); 
extern void Check_Ladder(int loop);
extern void Draw_Light(bool render_all); 
extern void Medal_Awarded(int type); 
extern void Create_Dust_Effect(float x, float y, bool is_shotgun, bool is_an_offset, int f_rate);      
extern void Create_Crate_Effect(int guy_shot);
extern bool Is_Grey_Area(float my_angle);
extern void Set_Heading(int loop, float x1, float y1, bool hulk_ladder);
extern void Create_Explosion(int guy_shot);
extern void Raise_Alarm();
extern void Knock_Back(int guy_shooting, int guy_shot, int f_rate);
extern void Mission_Accomplished(bool active);
extern float TimerGetTime();
extern bool Get_Next_Tile(int k, float x2, float y2);
extern void Do_Player_Accel(int f_rate);
extern void Check_For_Grenade();
extern void Sleep_Sprites(int j, bool load); 
extern int Calculate_TotalScore(int loop);
extern void Run_Hats();
extern void Surround_Sound(int sprite_index, int sound_type, float x, float y);
extern bool sta2_Keys();
extern int GetAccuracy(int loop, int target);

void Get_Target(int loop); 
void Hud_Signal(float value);
int Navigate_Point(int loop, bool hunting);
int Get_Closest_Node(int loop);
void Alert_Buddies(int loop, float range); 
int Search_area(int guy, int target, bool on_mesh);
void Check_EMY_State(int loop);
void Moving_Code(int loop, float x_pos, float y_pos, int f_rate);
void Shoot_Test(int loop, int f_rate);
void Reduce_Fog(float mid_x, float mid_y, int unit);
bool Test_Visible(float mid_x, float mid_y);
void Bomb_Run(float bomb_tar_x, float bomb_tar_y, int the_guy, int f_rate);
void Dig_Hole(int loop, float x, float y); 
bool Dig_Check(float x, float y, int man_to_check);
bool Slash_Check(float x, float y, int man_to_check);
bool Check_hole(int loop, int index);
void Rank_Timer(int index, int status);
void Shell_Landed( float x, float y, int shooter, int f_rate, int type, int value);
void Play_Footstep(int loop);
void Medal_Check();
void Remove_From_List(int index);
void Throw_Grenade(int index, int target);
void Special_Attack(int type);
void Run_Mud_Check(int j, int f_rate);
void Run_Legs_Check(int index, int the_player_id);
void Run_Legs();
void Respawn_Enemy(int index);
void Set_Camera(int f_rate, bool startup);

void AI(int f_rate)   
{

     float temp_distance=0.0f;
     bool door_test=false;
     bool changed_weapon=false;
     bool skip_this=false; 
     bool bud_continue=false;
     float deltax=0.0, deltay=0.0;
     float temp_music_volume=0.0;
     float angle=0.0;
     float mid_x=0.0;
     float mid_y=0.0;
     float tar_x=0.0, tar_y=0.0;  
     float cam_x =0.0;
     float cam_y = 0.0;
     float distance = 0.0;
     int rnd=0;
     int rnd1=0;
     int itemp=0;
     bool enemy_has_a_man=false;
     bool player_has_a_man=false; 
     int temp_row_x=0;
     int temp_row_y=0;
     bool gnd_check=false;
     bool special_go=false;
     float cam_factor=0.0;
     int  loop = 0;
     int  j = 0;
     int gun_amount=0;
     int gun_amount_gained=0;
     bool test_tech_artillery=false;
     bool test_tech_chief=false;
     bool test_tech_sniper=false;     
     bool test_cpu_tech_artillery=false;
     bool test_cpu_tech_chief=false;
     bool test_cpu_tech_sniper=false;
     bool test_cpu_tech_mech=false;
     bool test_tech_barracks=false;
     bool test_tech_mech=false;
     float frnd=0.0;
     int lowest_clip=10000;
     int clip_index=0;
     int index=0;
     int old_direction=0;
     int new_direction=0;
	 int smoke_direction=0;
     int tens = 0;
     int zeros = 0;   
     int player_clip = 0; 
     int temp_f_rate=0;
     float time_left_percent = 0;
     int time_taken=0;
	 float stop_range = 0.0f;
	 float return_range = 0.0f;
	 int closest_talk=0;
	 float closest_point=0.0f; 
	 float closest_alert=0.0f;
	 float dis_to_point=0.0f;
	 int found_the_gun=-1;
	 int pack_id=-1;
	 int accuracy_test = 0;
	 int the_guy = -1;

            
     int count_start=0;
     int count_end=0;
     
     float spawn_in_range = 0.0;
     
     float temp_factor = 0.0;
     
     if(f_rate <= 0)
         f_rate = 1; 

     if(f_rate > 100) 
         f_rate = 100; 

     guys_mine_count  = 0;  
     cpu_wood_workers = 0; 
     cpu_can_workers  = 0; 
     cpu_gunners      = 0;     
     cpu_bombers      = 0;  
     cpu_command      = -1; 
     cpu_command_count=0;  
     cpu_no_mortars=0; 
     cpu_no_buildings=0;  
                                                          
     if(!mode)                   
     {      
		  
	 	  if(game_mode == WALK)               
	 	  {  

			  the_guy = -1;

			  if(ply_id != -1)
			  if(sta2_turn == TURN_PLAYER) 
				  the_guy = ply_id;

			  if(emy_id != -1)
			  if(sta2_turn == TURN_COMPUTER)
				  the_guy = emy_id;

			  sta2_current_special = PACK_SPECIAL_NONE;

			  //Set current pack...
			  if(the_guy != -1)
			  if(sta2_turn == TURN_PLAYER)
			  {
				  if(sprite[the_guy].value2 != -1)
					   pack_id = sta2_squad[sprite[the_guy].value2].wp;

				  if(pack_id > -1) 
				  if(sta2_pack[pack_id].special != PACK_SPECIAL_NONE) 
				  if(sta2_pack[pack_id].special_charge > 0)
				  {
				      sta2_current_special = sta2_pack[pack_id].special; 
				  }
				   
			  } 

			  if(sta2_turn == TURN_PLAYER)   
			  if(sta2_killed_in_one_shot >= 2)
			  {
				if(sta2_globals[GLOBAL_TYPE_TRIPLE] == GLOBALS_ACTIVE)
				if(sta2_killed_in_one_shot >= 3)  
				{  
					sta2_levelup_display = true;  
					sta2_levelup_display_timer = (int)TimerGetTime()+3000;
					
				    sta2_got_triple_bonus = true; 

					Set_Sprite(32, 4, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Triple bonus
					sta2_killed_in_one_shot = 0;
					 
					#if IS_FULL_STEAM == 1 

					if(STEAM_ACTIVE == true)  
					if(IS_FULL_GAME == true)
					if (g_SteamAchievements)
					{
						g_SteamAchievements->SetAchievement("STA2_MEDAL_1"); // Perform a triple kill...

						if(sta2_globals[GLOBAL_STA2_MEDAL_1] == GLOBALS_RESET)
						{
							sta2_globals[GLOBAL_STA2_MEDAL_1] = GLOBALS_ACTIVE;
							firework_sfx = true;

						}
					}

					#endif

					firework_sfx = true; 
				}
				if(sta2_killed_in_one_shot >= 2)
				if(sta2_globals[GLOBAL_TYPE_DOUBLE] == GLOBALS_ACTIVE)
				if(sta2_killed_in_one_shot >= 2)     
				{
					sta2_levelup_display = true;  
					sta2_levelup_display_timer = (int)TimerGetTime()+3000;
					
				    sta2_got_double_bonus = true; 

					Set_Sprite(32, 3, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Double bonus
					sta2_killed_in_one_shot = 0;
					 
					#if IS_FULL_STEAM == 1 

					if(STEAM_ACTIVE == true) 
					if(IS_FULL_GAME == true)
					if (g_SteamAchievements)
					{
						g_SteamAchievements->SetAchievement("STA2_MEDAL_0"); // Perform a double kill...

						if(sta2_globals[GLOBAL_STA2_MEDAL_0] == GLOBALS_RESET)
						{
							sta2_globals[GLOBAL_STA2_MEDAL_0] = GLOBALS_ACTIVE;
							firework_sfx = true;

						}
					}

					#endif

					firework_sfx = true;
				} 

			  }

			  sta2_killed_in_one_shot = 0;

			  if(sta2_reset_movement == true) 
			  {
				  for(int i = 0;i< no_sprites; i++) 
				  if(sprite[i].type == UNT)
				  {
					 // Setup initial movement ranges...
					 if(sprite[i].sector == UNIT_DOG)
						sprite[i].movement = STA2_DOG_STEPS;
					 if(sprite[i].sector == UNIT_GUNNER)
						sprite[i].movement = STA2_SCOUT_STEPS;
					 if(sprite[i].sector == UNIT_HEAVY)
						sprite[i].movement = STA2_HEAVY_STEPS;
					 if(sprite[i].sector == UNIT_SNIPER)
						sprite[i].movement = STA2_SNIPER_STEPS;
					 if(sprite[i].sector == UNIT_MORTAR)
						sprite[i].movement = STA2_MORTAR_STEPS;
					 if(sprite[i].sector == UNIT_CHIEF)
						sprite[i].movement = STA2_CHIEF_STEPS;

				  }

				  sta2_reset_movement = false; 
			  }
			   
			  // XP gain stuff...  
			  for(int j=0;j<10;j++)
			  if(xp_damage_index[j] != -1)  
			  if((int)TimerGetTime() > xp_damage_timer[j]) 
			  {
				   DamageNumber( xp_damage_index[j], xp_damage_gain[j], STA2_DAMAGE_XP );
				   xp_damage_index[j] = -1;
			  }

			  // Add some movement speed to the active unit...
			  if(the_guy != -1) 
			  if(sta2_entered_action == true)   
			  {  
				  if(sta2_pressed_map == false)
				  {
					 // Setup initial movement ranges...
					 if(sprite[the_guy].sector == UNIT_DOG)
						sprite[the_guy].movement += STA2_DOG_STEPS/4;
					 if(sprite[the_guy].sector == UNIT_GUNNER)
						sprite[the_guy].movement += STA2_SCOUT_STEPS/4;
					 if(sprite[the_guy].sector == UNIT_HEAVY)
						sprite[the_guy].movement += STA2_HEAVY_STEPS/4;
					 if(sprite[the_guy].sector == UNIT_SNIPER)
						sprite[the_guy].movement += STA2_SNIPER_STEPS/4;
					 if(sprite[the_guy].sector == UNIT_MORTAR)
						sprite[the_guy].movement += STA2_MORTAR_STEPS/4;
					 if(sprite[the_guy].sector == UNIT_CHIEF)
						sprite[the_guy].movement += STA2_CHIEF_STEPS/4;

					 // Setup initial movement ranges...
					 if(sprite[the_guy].sector == UNIT_DOG)
					 if(sprite[the_guy].movement > STA2_DOG_STEPS)
						sprite[the_guy].movement = STA2_DOG_STEPS;
					 if(sprite[the_guy].sector == UNIT_GUNNER)
					 if(sprite[the_guy].movement > STA2_SCOUT_STEPS)
						sprite[the_guy].movement = STA2_SCOUT_STEPS;
					 if(sprite[the_guy].sector == UNIT_HEAVY)
					 if(sprite[the_guy].movement > STA2_HEAVY_STEPS)
						sprite[the_guy].movement = STA2_HEAVY_STEPS;
					 if(sprite[the_guy].sector == UNIT_SNIPER)
					 if(sprite[the_guy].movement > STA2_SNIPER_STEPS)
						sprite[the_guy].movement = STA2_SNIPER_STEPS;
					 if(sprite[the_guy].sector == UNIT_MORTAR)
					 if(sprite[the_guy].movement > STA2_MORTAR_STEPS)
						sprite[the_guy].movement = STA2_MORTAR_STEPS;
					 if(sprite[the_guy].sector == UNIT_CHIEF)
					 if(sprite[the_guy].movement > STA2_CHIEF_STEPS)
						sprite[the_guy].movement = STA2_CHIEF_STEPS;
				  }

				  sta2_pressed_map = false;

				  sta2_entered_action = false; 
			  }

			  // Machine gun...
			  if(the_guy != -1)
			  if(sta2_machinegun_index != -1) 
			  if((int)TimerGetTime() > sta2_mg_timer) 
			  if(sta2_mg_fired < 5) 
			  {  

				   sta2_mg_fired++;                    
				       
           		   rnd = rand()%100;               
				 
				   sprite[the_guy].status = OPEN_FIRE;
                   
				   sprite[the_guy].anim_state = WAIT;
               
				   sprite[the_guy].update = true;
               
				   Rank_Timer(the_guy, sprite[the_guy].status); 

				   tar_x = sprite[the_guy].x+sprite[the_guy].width/2;  
				   tar_y = sprite[the_guy].y+sprite[the_guy].height/2; 

				   New_FX(tar_x, tar_y,  sprite[the_guy].w, sprite[the_guy].z, 0, LOOP, 0.025f, 0.025f, 0.025f, 0.025f, 0, GFX, 1.0f, 0, 0, FX_SHELL, the_guy, 8, 0, 0, -1); 

				   accuracy_test = GetAccuracy(the_guy, sta2_machinegun_index);

				   mid_x = sprite[sta2_machinegun_index].w+sprite[sta2_machinegun_index].box_width/2; 
				   mid_y = sprite[sta2_machinegun_index].z+sprite[sta2_machinegun_index].box_height/2;

				  if( (rnd <= accuracy_test) && sprite[sta2_machinegun_index].score > 0) 
					  Man_Shot(sprite[the_guy].status, sta2_machinegun_index, the_guy, BULLET_NONE, f_rate);
				  else
				  {
				 	 Create_Dust_Effect(mid_x, mid_y, true, false, f_rate); 
					 DamageNumber(sta2_machinegun_index, -1, STA2_DAMAGE_MISS ); 
				  }

				  sta2_mg_timer = (int)TimerGetTime() + 200; 

				  if(sta2_mg_fired >= 5)
				  {
					 sta2_machinegun_index = -1;
					 sta2_mg_timer = 0;
					 sta2_mg_fired = 0;
				  }

			  }

			  // Pistol
			  if(the_guy != -1) 
			  if(sta2_chief_index != -1) 
			  if((int)TimerGetTime() > sta2_chief_timer) 
			  if(sta2_chief_fired < 3) 
			  {  

				   sta2_chief_fired++;                    
				       
           		   rnd = rand()%100;                

				//   death_sfx = true;

				   sprite[the_guy].status = OPEN_FIRE;
                   
				   sprite[the_guy].anim_state = WAIT;
               
				   sprite[the_guy].update = true;
                     
				   Rank_Timer(the_guy, sprite[the_guy].status); 

				   tar_x = sprite[the_guy].x+sprite[the_guy].width/2;  
				   tar_y = sprite[the_guy].y+sprite[the_guy].height/2; 

				   New_FX(tar_x, tar_y,  sprite[the_guy].w, sprite[the_guy].z, 0, LOOP, 0.025f, 0.025f, 0.025f, 0.025f, 0, GFX, 1.0f, 0, 0, FX_SHELL, the_guy, 8, 0, 0, -1); 

				   accuracy_test = GetAccuracy(the_guy, sta2_chief_index);

				   mid_x = sprite[sta2_chief_index].w+sprite[sta2_chief_index].box_width/2; 
				   mid_y = sprite[sta2_chief_index].z+sprite[sta2_chief_index].box_height/2;

				  if( (rnd <= accuracy_test) && sprite[sta2_chief_index].score > 0) 
					  Man_Shot(sprite[the_guy].status, sta2_chief_index, the_guy, BULLET_NONE, f_rate);
				  else
				  {
				 	 Create_Dust_Effect(mid_x, mid_y, true, false, f_rate); 
					 DamageNumber(sta2_chief_index, -1, STA2_DAMAGE_MISS ); 
				  }

				  sta2_chief_timer = (int)TimerGetTime() + 400;    

				  if(sta2_chief_fired >= 5)
				  {
					 sta2_chief_index = -1;
					 sta2_chief_timer = 0;
					 sta2_chief_fired = 0;
				  }

			  }

			  sta2_Keys(); 
			   
			  if(!mode)  
			  { 

				  the_guy = -1;

				  if(sta2_turn == TURN_PLAYER)  
					  the_guy = ply_id;

				  if(sta2_turn == TURN_COMPUTER)   
					  the_guy = emy_id;
					
				  if(the_guy != -1) 
				  {

					  distance = 0.1f; 

					  if(sta2_turn == TURN_PLAYER)
					  if(sta2_current_special == PACK_SPECIAL_BOOTS)
						  distance = 0.14f;

				    if(sta2_distance_traveled >= distance) 
					{
						sta2_distance_traveled = 0.0f; 

						if(INFINITE_RUN == 0)
							sprite[the_guy].movement--; 
					 
						if(sprite[the_guy].movement <= 0) 
						{
							sprite[the_guy].movement = 0; 
							ShotIdle(the_guy);

							if(sta2_turn == TURN_COMPUTER) 
							if(sta2_enemy_mode == MOVE_MOVE)
							{
								sta2_enemy_mode = MOVE_END; 
								sta2_timer = 0;
							}
						}   
					}
				  }

				  if(sta2_levelup_display==true)
				  if((int)TimerGetTime() > sta2_levelup_display_timer)
					  sta2_levelup_display=false;

				  if(sta2_levelup_display==true)
					  hud[32].alpha = 1.0f;
				  else 
					  hud[32].alpha = 0.0f;

				  AI_Command(f_rate); // Run A.I...

			  }

			  if(ARCADE)
			  if( (int)TimerGetTime() > arcade_bonus_timer)
				  arcade_bonus = 0;

			  if(CONTROLLER)
				  map_stat = false;

		//	if(main_mission[current_main] != IN_PROGRESS)
		//		save_position= SAVE_NONE;	
			
      	    if((int)TimerGetTime() > animate_tiles_timer)    
	  	    { 
				flip_tiles ^= 1;  
		    	animate_tiles_timer = (int)TimerGetTime()+250; // 125
	  	    }   

		  } 
		  
		  if(game_mode == WALK)      
		  if(ply_legs_id != -1 && ply_id != -1) 
	 	  {      
	  		 tar_x = sprite[ply_id].end_x;  
    		 tar_y = sprite[ply_id].end_y; 
    		 
  	         mid_x = sprite[ply_id].w+sprite[ply_id].box_width/2;
			 mid_y = sprite[ply_id].z+sprite[ply_id].box_height/2;	 

			 angle = atan2(tar_y - mid_y,tar_x - mid_x);     
       
       		 if(Is_Guy_In_Sight(sprite[ply_id].angle, angle) == false )
       		     MOVING_BACKWARDS = true;
   		     else
   		         MOVING_BACKWARDS = false;
				 
		  }

		 if(PLAYER_INVULNERABLE == 1) 
		 if(ply_id != -1)
		 { 
		 	sprite[ply_id].score = PLY_VITALITY;
		 }
       
         // Health Kits... 
         if(!mode && game_mode == WALK)
         {
     
              
             if(alarm_raised == true)
             if((int)TimerGetTime() > alarm_raised_timer)
             {
                 Raise_Alarm();     
                 alarm_raised=false;
             }
             
                  
             hud[52].alpha = 0.0;
         //    hud[53].alpha = 0.0;
             
        //     Set_Sprite(53, 7, PLAY, ANIM_HUD, ANIM_NOT_WALKING);
             Set_Sprite(52, 7, PLAY, ANIM_HUD, ANIM_NOT_WALKING);  
                              
             if(party_power == true)
             {
                 Set_Sprite(53, 9, PLAY, ANIM_HUD, ANIM_NOT_WALKING);
                 Set_Sprite(52, 9, PLAY, ANIM_HUD, ANIM_NOT_WALKING);                 
             }
                              
             if(ply_id != -1)
             if(party_power == false)
             {
                 if((int)TimerGetTime() > bump_player_timer)        
                     bump_player=false;
             }         
                         
         } 

         if(lock_player == false)  
         if(ply_dead == false)  
         if(ply_id != -1)
         if(!mode && game_mode == WALK)  
         { 

             if(sprite[ply_id].status != IDLE || sprite[ply_id].score <= 0 || reloading == true)
             {
                 start_healing = false;
                 remove_healthkit = false;
             }         
             
         }
         
         
         if(ply_dead == false) 
		 if(!mode)
         if(game_mode == WALK && (int)TimerGetTime() > fade_timer) // fade_timer == 10       
             Medal_Check();  
         
         if(ply_dead == false)
         if(game_mode == WALK)
         if(ply_special_attack != -1)
             Special_Attack(ply_special_attack);   
         
         
         if((int)TimerGetTime() > tunnel_timer)
         if(tunnel_timer != -1)  
         {
             tunnel_timer = -1;  
             
             if(LAD_next_scene != -1 && LAD_next_episode != -1)
             {
                 scene = LAD_next_scene;
                 episode = LAD_next_episode;           
             }
             
             next_scene = true;
         }
             
         no_lights_on = 0;    
                       
         rnd=Get_Closest_Node(0); 
         
         if(rnd!=-1)
             ply_node=rnd; 
          
         if(ply_potion==POTION_HULK) 
             called_in_node = ply_node;
        
         if(lock_player != true)
		 if(ply_id != -1)
         if(success_condition >= total_success_condition)
         { 
                                            
             if(Level == LVL_TRAINING) 
             if(current_main == MISSION_TRAINING)
             if(main_mission[MISSION_TRAINING] != COMPLETED)
             if(mission_accomplished_active == false)
             {   
             
                 sprite[ply_id].status = LEVELING;   
                    
                 Convert_Dir_To_Angle(ply_id, DOWN);

                 sprite[ply_id].update = true;      
                 sprite[ply_id].anim_state = WAIT; 
                 sprite[ply_id].moving = false;
                 sprite[ply_id].all_timer = (int)TimerGetTime() + 1500; 
                 
                 success_condition = 0;

             }         
             
         }   
          
         if(lock_player != true)
         if(fail_condition >= total_fail_condition) 
         {
             mission_objective = MISSION_FAILED;
         } 
          
         // Throw a grenade     
         if(lock_player != true && ply_dead == false)
         if(next_scene == false)
         if(ply_id != -1)
         if(sprite[ply_id].score > 1)
         if( sprite[ply_id].status != OPEN_CUT  
         && sprite[ply_id].status != OPEN_STAMP && sprite[ply_id].status != OPEN_THROW
         && (int)TimerGetTime() > sprite[ply_id].reload_timer )            
         if(throw_grenade == true)  
         {   
				  
                  tar_x = sprite[ply_id].x+sprite[ply_id].width/2;  
                  tar_y = sprite[ply_id].y+sprite[ply_id].height/2;   
                   
				  Surround_Sound(p1_id, SFX_CHOP, tar_x, tar_y);     

//				  if(throw_grenade_type == THROW_BLACK_GRENADE)  
				  //{	                               
            	      New_FX(tar_x, tar_y,  sprite[ply_id].w, sprite[ply_id].z, 31, LOOP, 0.05f, 0.05f, 0.2f, 0.2f, 4, GFX, 1.0, -1, BULLET_KNIFE_PLY, FX_GRENADE_SHADOW, ply_id, 5, 0, 0, -1);
	                  New_FX(tar_x, tar_y,  sprite[ply_id].w, sprite[ply_id].z, 0, LOOP, 0.05f, 0.05f, 0.2f, 0.2f, 2, GFX, 1.0, -1, BULLET_KNIFE_PLY, FX_GRENADE, ply_id, 5, BLACK_GRENADE, 0, throw_grenade_type);
				  //}
			/*	  if(throw_grenade_type == THROW_GREEN_GRENADE)
				  {
        	          New_FX(tar_x, tar_y,  sprite[ply_id].w, sprite[ply_id].z, 30, LOOP, sprite[ply_id].box_width, sprite[ply_id].box_height, sprite[ply_id].width, sprite[ply_id].height, 0, GFX, 1.0, -1, BULLET_KNIFE_PLY, FX_GRENADE_SHADOW, ply_id, 5, 0, 0, -1);
	                  New_FX(tar_x, tar_y,  sprite[ply_id].w, sprite[ply_id].z, 18, LOOP, sprite[ply_id].box_width, sprite[ply_id].box_height, sprite[ply_id].width, sprite[ply_id].height, 0, GFX, 1.0, -1, BULLET_KNIFE_PLY, FX_GRENADE, ply_id, 5, GREEN_GRENADE, 0, -1);
				  }
				  if(throw_grenade_type == THROW_MOLOTOV)
				  {
    	              New_FX(tar_x, tar_y,  sprite[ply_id].w, sprite[ply_id].z, 32, LOOP, sprite[ply_id].box_width, sprite[ply_id].box_height, sprite[ply_id].width, sprite[ply_id].height, 0, GFX, 1.0, -1, BULLET_KNIFE_PLY, FX_GRENADE_SHADOW, ply_id, 5, 0, 0, -1);
	                  New_FX(tar_x, tar_y,  sprite[ply_id].w, sprite[ply_id].z, 20, LOOP, sprite[ply_id].box_width, sprite[ply_id].box_height, sprite[ply_id].width, sprite[ply_id].height, 0, GFX, 1.0, -1, BULLET_KNIFE_PLY, FX_GRENADE, ply_id, 5, MOLOTOV_GRENADE, 0, -1);
				  }
				  if(throw_grenade_type == THROW_DECOY) 
				  {
    	              New_FX(tar_x, tar_y,  sprite[ply_id].w, sprite[ply_id].z, 35, LOOP, sprite[ply_id].box_width, sprite[ply_id].box_height, sprite[ply_id].width, sprite[ply_id].height, 0, GFX, 1.0, -1, BULLET_KNIFE_PLY, FX_GRENADE_SHADOW, ply_id, 5, 0, 0, throw_grenade_amount);
	                  New_FX(tar_x, tar_y,  sprite[ply_id].w, sprite[ply_id].z, 34, LOOP, sprite[ply_id].box_width, sprite[ply_id].box_height, sprite[ply_id].width, sprite[ply_id].height, 0, GFX, 1.0, -1, BULLET_KNIFE_PLY, FX_GRENADE, ply_id, 5, DECOY_GRENADE, 0, throw_grenade_amount);
				  } 
				  if(throw_grenade_type == THROW_MINE)  
				  {
    	              New_FX(tar_x, tar_y,  sprite[ply_id].w, sprite[ply_id].z, 37, LOOP, sprite[ply_id].box_width, sprite[ply_id].box_height, sprite[ply_id].width, sprite[ply_id].height, 0, GFX, 1.0, -1, BULLET_KNIFE_PLY, FX_GRENADE_SHADOW, ply_id, 5, 0, 0, throw_grenade_amount);
	                  New_FX(tar_x, tar_y,  sprite[ply_id].w, sprite[ply_id].z, 36, LOOP, sprite[ply_id].box_width, sprite[ply_id].box_height, sprite[ply_id].width, sprite[ply_id].height, 0, GFX, 1.0, -1, BULLET_KNIFE_PLY, FX_GRENADE, ply_id, 5, DECOY_MINE, 0, throw_grenade_amount);
				  } */
                   
                  sprite[ply_id].status = OPEN_THROW;  
                  sprite[ply_id].anim_state = WAIT;   
                  sprite[ply_id].update = true;    

                  sta2_used_extra = true;

                  Rank_Timer(ply_id, sprite[ply_id].status); 
                                                      
                  throw_grenade = false;                                    
                                    
        //     }
          
         }

         run_angle_check = false;  
                   
         // Turning code    
         if((int)TimerGetTime() > angle_timer) 
         {
                                
              angle_timer = (int)TimerGetTime() + 15;
              
              run_angle_check = true; 
              
              if(lan_game == false)              
                  Group_Command(); 
                  
         }     
                   
         // Exploding effects for antenna's etc...
         if(game_mode == WALK)   
         if(exploding_id != -1)
         if((int)TimerGetTime() > exploding_timer) 
         { 
                                
              exploding_timer = (int)TimerGetTime() + 500;
              exploding_count++; 
              
              Create_Explosion(exploding_id);
              
              if(exploding_count >= 4)
                  exploding_timer = (int)TimerGetTime() + 200;
                  
              if(exploding_count > 16)   
              {
                  exploding_id = -1;               
                  exploding_count = 0;  
                 
                  if(ply_id != -1)
                  if(current_main == MISSION_RADIO)
                  if(global_objects[18] == GLOBAL_BEATEN)
                  if(global_objects[19] == GLOBAL_BEATEN)
                      Display_Message(ply_id, MSG_SUCCESS1);    
                                
              }
                                
         }
         
                  
         // Makes Dudes semi-visible in dungeon
         if(game_mode == WALK)
         if((int)TimerGetTime() > range_timer) 
         {   
                            
              for(int k=0;k<no_fx;k++)  
              {   
   
              if(Fx[k].type == PKU 
              || Fx[k].sector == FX_BULLET  
              || Fx[k].sector == FX_SHELL  
              || Fx[k].sector == FX_BULLET_SHADOW)  
              {
                              
                  if(ply_id != -1)
                  if(player_type == p_server)  
                  {                     
                      mid_x = sprite[ply_id].w+sprite[ply_id].box_width/2; 
                      mid_y = sprite[ply_id].z+sprite[ply_id].box_height/2; 
                  }
                   
                  tar_x = Fx[k].x+Fx[k].width/2;   
                  tar_y = Fx[k].y+Fx[k].height/2; 
                  
                  temp_distance = Node_Distance1(mid_x, mid_y, tar_x, tar_y);     
                       
                  if(Fx[k].sector == FX_BULLET 
                  || Fx[k].sector == FX_SHELL 
                  || Fx[k].sector == FX_BULLET_SHADOW) 
                  if( temp_distance >= REMOVE_FX_RANGE)
                      Fx[k].turn_off = true;
                      
                      
              }
              
              } // For no_fx
       
         } // range timer    
             
         // Step SFX 
         if(game_mode == WALK && !mode)
         {
                      
             if(player_in_water == true)                      
             if(step_traveled >= 200)
             { 
                 step_traveled = 0;
                 
             }
                      
             if(player_in_water == false)                      
             if(step_traveled >= 140)
             { 
                 step_traveled = 0;

                 player_walked++;
                 if(player_walked > 3280)
                 {
                     player_walked=0;             
                     player_miles++;
                 }
             } 
                       
         }          
		  
	     spawn_in_range = 1.0;  // 1.4    

         // Spawn some dudes code... 
/*		 if(ARCADE)   
	     if(arcade_enemy_count < 16)
         if(dm_game == DM_NONE) 
         if(in_dungeon == false)  
         if(spawn_level_number != 0) 
         if((int)TimerGetTime() >= WAVE_timer)    
         {     
                
             if(spawn_group == spawn_level_number)      
             {  
				   
                 if(Level == LVL_SUPPLIES || Level == LVL_BAY 
				 || Level == LVL_TOWN || Level == LVL_PLAINS 
				 || Level == LVL_FARMS || Level == LVL_HIGHWAY
				 || Level == LVL_VILLAGE) 
				 if(has_buddy != BUDDY_WAIT || Level == LVL_HIGHWAY)            
                     rnd = 3+rand()%4;  // was 4+rand()%5; 
				 else   
				 {
                     rnd = 3+rand()%3;  
					 if(main_mission[MISSION_RADIO] == IN_PROGRESS)
					     rnd = 3;
				 }	
                     
			  	 if(Level == LVL_HIGHWAY)	     		
                     rnd = 3+rand()%3;  
                     
			  	 if(Level == LVL_BOATYARD)	    		
                     rnd = 2+rand()%2;                      
				        
  			     
             }    
             else          
                rnd = rand()%2;                
             
			 if(DISABLE_ALL_ENEMIES == 0)       
             if(Level != LVL_TRAINING 
             && Level != LVL_BASE 
             && Level != LVL_TEST   
             && Level != LVL_ROADWAY 
             && Level != LVL_ORCHARD 
             && Level != LVL_BOOT_ROAD 
             && Level != LVL_BEACH_ROAD  
             && Level != LVL_AIRFIELD
             && Level != LVL_CASTLEROOF) 
             {  

                 if(Spawn_A_Guy(rnd, -1, false, TRAP_NONE, -1, -1)==true)
                     spawned_a_group=true;   
                                      
                 if(spawned_a_group == true) 
                 {

					 if(spawn_group == spawn_level_number) 
						WAVE_timer=(int)TimerGetTime()+12000;
					 else
						WAVE_timer=(int)TimerGetTime()+3000;

                     spawned_a_group=false;              
                     spawn_group++;     

                     if(spawn_group > spawn_level_number+1)
                         spawn_group = 0;
                 }                                         
            }
            
                       
         }     */
        
         // Spawn some dudes code... 
//		 if(!ARCADE)
         if(dm_game == DM_NONE) 
         if(in_dungeon == false)  
         if(spawn_level_number != 0) 
         if(distance_traveled >= spawn_in_range)    
         {     
                
             if(spawn_group == spawn_level_number)      
             {  
				   
                 if(Level == LVL_SUPPLIES || Level == LVL_BAY 
				 || Level == LVL_TOWN || Level == LVL_PLAINS 
				 || Level == LVL_FARMS || Level == LVL_HIGHWAY
				 || Level == LVL_VILLAGE) 
				 if(has_buddy != BUDDY_WAIT || Level == LVL_HIGHWAY)            
                     rnd = 3+rand()%4;  // was 4+rand()%5; 
				 else   
				 {
                     rnd = 3+rand()%3;  
					 if(main_mission[MISSION_RADIO] == IN_PROGRESS)
					     rnd = 3;
				 }	
                     
			  	 if(Level == LVL_HIGHWAY)	     		
                     rnd = 3+rand()%3;  
                     
			  	 if(Level == LVL_BOATYARD)	    		
                     rnd = 2+rand()%2;                      
				        
  			     
             }    
             else          
                rnd = rand()%2;                
             
			 if(DISABLE_ALL_ENEMIES == 0)       
             if(Level != LVL_TRAINING 
             && Level != LVL_BASE 
             && Level != LVL_TEST  
             && Level != LVL_ROADWAY 
             && Level != LVL_ORCHARD
             && Level != LVL_BOOT_ROAD 
             && Level != LVL_BEACH_ROAD  
             && Level != LVL_AIRFIELD
             && Level != LVL_CASTLEROOF) 
             {  

                 if(Spawn_A_Guy(rnd, -1, false, TRAP_NONE, -1, -1)==true)
                     spawned_a_group=true;  
                                      
                 if(spawned_a_group == true)
                 {
                     spawned_a_group=false;             
                     spawn_group++;     
                                       
                     distance_traveled=0.0;
                     
                     if(spawn_group > spawn_level_number+1)
                         spawn_group = 0;
                 }                                         
            }
            
                       
         }      
                  
         // Follow node...     
         if(distance_traveled >= 0.03)    
         { 
             follow_x = -1;
             follow_y = -1; 
                              
             if(ply_id != -1)                 
             if(player_type == p_server) 
             {
                 mid_x = sprite[ply_id].w+sprite[ply_id].box_width/2; 
                 mid_y = sprite[ply_id].z+sprite[ply_id].box_height/2;
                 
                 follow_x = mid_x;     
                 follow_y = mid_y;                              
                 
             }   
                         
         }    
                  
         if((int)TimerGetTime() > defend_timer) 
         {   
             defend_timer = (int)TimerGetTime() + 500;
         }   
     
       // Get rid of old Light pnt's  
       if((int)TimerGetTime() > points_timer)
       {
                                   
           for(int i=0;i<no_points;i++)   
           { 
               if( (points[i].c1 == LIGHT_PNT || (points[i].c1 == DEAD_PNT && ARCADE) ) && ((int)TimerGetTime() >= points[i].score && points[i].c4 != LIGHT_GENERAL  )) //  || points[i].c1 == DEAD_PNT
			   if(  points[i].score != -1)
               {
                   for(int loop=i;loop<no_points;loop++) 
                   { 
                      points[loop].x = points[loop+1].x;
                      points[loop].y = points[loop+1].y; 
                      
                      points[loop].score = points[loop+1].score;  
                      points[loop].active = points[loop+1].active;
                      points[loop].speed  = points[loop+1].speed;  
                      points[loop].c1 = points[loop+1].c1;
                      points[loop].c2 = points[loop+1].c2; 
                      points[loop].c3 = points[loop+1].c3;
                      points[loop].c4 = points[loop+1].c4; 
                                                          
                   } 
                   if(no_points>0) 
                       no_points--;    
               }
           } 
           
           points_timer = (int)TimerGetTime()+100; // Was 200...
       
       }
          
       music_danger_volume = 0.0;
       
       light_count = 0;
              
       if((int)TimerGetTime() > check_timer)
       if(alert_enemies == true)
       {
           alert_enemies = false;             
           noise_maker   = LOUD_NOISE;
           alert_guy = -1;
       } 
       
       draw_light_count = 0; 
        
   // ******************************************************************************//
   //                                                                               //
   //                                                                               //
   //                                Main Loop                                      //
   //                                                                               //
   //                                                                               //
   // ******************************************************************************//    
        
	   if(game_mode == WALK)
		   sta2_lines_count = 0;

	   if(game_mode == WALK)
	   if(sta2_turn == TURN_PLAYER) 
	   if(STA2_MODE == MODE_MOVING) 
	   if(sta2_alert_index != -1)
	   if(ply_id != -1)
	   if(sprite[ply_id].score > 1)
	   {
		   sta2_lines_count = 1; 
		   Lines_MID[0] = ply_id;
		   Lines_TAR[0] = sta2_alert_index;

	   }

	   sta2_player_in_danger = false;      
	   closest_alert = (float)gunner_rng*3.0f;  

	   sta2_alert_index = -1; 

       for(int i=0;i<player_counter;i++)   
       {   
	   	   
          srand(i+(int)TimerGetTime());        
		     
          loop = player_list[i];      
				   
		  // Add alert fx for player when in enemy firing range...
		  if(game_mode == WALK)   
		  if(sta2_turn == TURN_PLAYER) 
		  if(STA2_MODE == MODE_MOVING)  
		  if(ply_id != -1)
		  if(sprite[ply_id].score > 1)
		  if(loop >= 0)     
		  if(sprite[loop].type == UNT)   
		  if(sprite[loop].score > 0)
		  if(sprite[loop].linked_sprite != player_type)  
		  {	 

				mid_x = sprite[ply_id].w+sprite[ply_id].box_width/2;
				mid_y = sprite[ply_id].z+sprite[ply_id].box_height/2;

				tar_x = sprite[loop].w + sprite[loop].box_width/2;    
				tar_y = sprite[loop].z + sprite[loop].box_height/2;    
             
				angle = atan2(mid_y - tar_y,mid_x - tar_x);     
                          
				dis_to_point = Node_Distance1(mid_x, mid_y, tar_x, tar_y);  

			   if(sta2_turn == TURN_PLAYER)   
			   if(dis_to_point < closest_alert)           
			   if(Is_Guy_In_Sight(sprite[loop].angle, angle) > 0) 
               {        
				    closest_alert = dis_to_point;   

					sta2_alert_index = loop;  
	
               }  

			   if(sta2_turn == TURN_PLAYER)
			   if(sprite[loop].sector != UNIT_DOG && sprite[loop].sector != UNIT_SNIPER && sprite[loop].sector != UNIT_MORTAR) 
			   if(dis_to_point < (float)gunner_rng*2.1f)           
			   if(Is_Guy_In_Sight(sprite[loop].angle, angle) > 0) 
               {        

					sta2_player_in_danger = true;   
					   
					if(sta2_danger_index == -1)  
						New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[ply_id].w, sprite[ply_id].y-0.0001f, 56, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_ALERT, ply_id, 6, 0, 0, -1);
					
               } 
	      }

		  if(game_mode == WALK)       	 
		  if(loop >= 0)     
		  if(sprite[loop].type == UNT)  
		  if(sprite[loop].score > 0)
		  if(sprite[loop].linked_sprite != player_type)
		  {
		//	  if(sta2_turn == TURN_PLAYER) 
		//		sprite[loop].unit_moved = false;   
		  } 

		  if(game_mode == WALK)        	 
		  if(loop >= 0)    
		  if(sprite[loop].type == UNT)  
		  if(sprite[loop].score > 1) 
		  if(sprite[loop].linked_sprite == player_type)
		  { 
		//	  if(sta2_turn == TURN_COMPUTER) 
		//		sprite[loop].unit_moved = false;
		  }

		  if(!mode && game_mode == WALK)   
		  if(loop >= 0)  
		  if(sprite[loop].type == UNT) 
		  if(sprite[loop].score > 1)
		  {
	 		  Check_Crouch(loop, false); 
		  } 

		  if(game_mode == WALK)      	 
		  if(loop >= 0)  
		  if(sprite[loop].type == UNT)
		  if(sprite[loop].sector == UNIT_SAILOR)// Civilian clothes
		  if(sprite[loop].status == IDLE)
		  if(sprite[loop].moving == false)
		  if(sprite[loop].spotted == false)
		  if(sprite[loop].on_screen == true)  	
		  if((int)TimerGetTime() > smoking_timer) 	
		  { 
 
			  smoke_direction = Convert_Angle_To_Dir(sprite[loop].angle);  
			   
              if(smoke_direction == DOWN)
	              New_FX( ((sprite[loop].x+sprite[loop].width/2)-0.03f), sprite[loop].y+sprite[loop].height/1.3f, sprite[loop].w, sprite[loop].y-0.001f, 19, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 2, GFX, 1.0, 0, 0, FX_HEADSHOT, loop, 27, 0, 0, -1);    
			  if(smoke_direction == UP)
	              New_FX( ((sprite[loop].x+sprite[loop].width/2)-0.03f), sprite[loop].y+sprite[loop].height/1.3f, sprite[loop].w, sprite[loop].y+0.001f, 19, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 2, GFX, 1.0, 0, 0, FX_HEADSHOT, loop, 27, 0, 0, -1);    
              if(smoke_direction == DOWN_LEFT || smoke_direction == LEFT)
	              New_FX( ((sprite[loop].x+sprite[loop].width/2)-0.06f), sprite[loop].y+sprite[loop].height/1.3f, sprite[loop].w, sprite[loop].y-0.001f, 19, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 2, GFX, 1.0, 0, 0, FX_HEADSHOT, loop, 27, 0, 0, -1);    
			  if(smoke_direction == RIGHT || smoke_direction == DOWN_RIGHT)
	              New_FX( ((sprite[loop].x+sprite[loop].width/2)+0.01f), sprite[loop].y+sprite[loop].height/1.3f, sprite[loop].w, sprite[loop].y-0.001f, 19, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 2, GFX, 1.0, 0, 0, FX_HEADSHOT, loop, 27, 0, 0, -1);    
              if(smoke_direction == UP_LEFT)
	              New_FX( ((sprite[loop].x+sprite[loop].width/2)-0.06f), sprite[loop].y+sprite[loop].height/1.3f, sprite[loop].w, sprite[loop].y+0.001f, 19, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 2, GFX, 1.0, 0, 0, FX_HEADSHOT, loop, 27, 0, 0, -1);    
			  if(smoke_direction == UP_RIGHT)
	              New_FX( ((sprite[loop].x+sprite[loop].width/2)+0.01f), sprite[loop].y+sprite[loop].height/1.3f, sprite[loop].w, sprite[loop].y+0.001f, 19, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 2, GFX, 1.0, 0, 0, FX_HEADSHOT, loop, 27, 0, 0, -1);    

			  smoking_timer = (int)TimerGetTime() + 300; 
		  } 
         
		 if(game_mode == WALK)
		 if(loop >= 0)  	
         if((int)TimerGetTime() > crouch_timer)                
         {
			 if(sprite[loop].type == UNT)
	             Run_Mud_Check(loop, f_rate);   
         } 
		  
		 if(loop >= 0)   
		     Sleep_Sprites(loop, false);    
		     

         if(game_mode == WALK) 
		 if(loop >= 0)  
         if(sprite[loop].type == OBJ 
         && sprite[loop].sector_action == OBJ_BUTTERFLY)         
		 { 
			
			sprite[loop].x += cos(sprite[loop].angle )*(0.0002f*(float)f_rate);        
			sprite[loop].y -= sin(sprite[loop].angle )*(0.0002f*(float)f_rate);

			if(sprite[loop].x <= -map_startX)
				sprite[loop].x = -map_startX;
			if(sprite[loop].x > (-map_startX + (MAP_WIDTH*0.1f) ) )
				sprite[loop].x = (-map_startX + (MAP_WIDTH*0.1f) );

			if(sprite[loop].y <= -map_startY)
				sprite[loop].y = -map_startY;
			if(sprite[loop].y > (-map_startY + MAP_HEIGHT*0.1f))
				sprite[loop].y = (-map_startY + MAP_HEIGHT*0.1f);

            if(rand()%3 == 0)
				sprite[loop].angle += 1*(float)f_rate;
			else
				sprite[loop].angle -= 1*(float)f_rate;

		 }
                               
         if(game_mode == WALK)
		 if(loop >= 0)  
         if(sprite[loop].type == OBJ 
         && sprite[loop].sector_action == OBJ_LIGHT1 
         && sprite[loop].linked_sprite == LIGHT_ON)         
             no_lights_on++;
                          
         if(game_mode == WALK)
		 if(loop >= 0)  
         if( (sprite[loop].type == OBJ && sprite[loop].sector_action == OBJ_LIGHT)
         ||  (sprite[loop].type == UNT && sprite[loop].status == OPEN_FIRE
         && (int)TimerGetTime() < sprite[loop].all_timer )
         || (sprite[loop].type == OBJ && sprite[loop].sector_action == OBJ_LIGHT1 )
         ) 
         {    
             light_list[light_count] = loop; 
             light_count++;  
 
             mid_x = sprite[loop].w + sprite[loop].box_width/2;
             mid_y = sprite[loop].z + sprite[loop].box_height/2;
             
             tar_x = (-camX);   
             tar_y = (-camY);  
             
             distance = Node_Distance1(mid_x, mid_y, tar_x, tar_y);
             
             if( (sprite[loop].type == OBJ && sprite[loop].sector_action == OBJ_LIGHT && sprite[loop].linked_sprite == LIGHT_ON)
             || (sprite[loop].type == OBJ && sprite[loop].sector_action == OBJ_LIGHT1 && sprite[loop].linked_sprite == LIGHT_ON )
             ||  (sprite[loop].type == UNT && sprite[loop].status == OPEN_FIRE && (int)TimerGetTime() < sprite[loop].all_timer )
             )
             if( distance < 2.9f) // was 2.5   
             if(draw_light_count >= 0 && draw_light_count < 50) 
             { 
                 draw_light_list[draw_light_count] = loop; 
                 draw_light_count++;  
             }               
     
         }              
          
//             if(Level == LVL_BASE) 
             if(ply_id != -1)
			 if(loop >= 0)      
             if(sprite[loop].type == BOX)  
             {
                 music_danger_distance = Node_Distance(sprite[loop].x, sprite[loop].y, sprite[ply_id].x, sprite[ply_id].y);
                 temp_music_volume = 1.4f - music_danger_distance;                 
             
                 if(temp_music_volume > music_danger_volume)                
                     music_danger_volume = temp_music_volume; 
                           
                 if(music_danger_volume < 0.0f)   
                     music_danger_volume = 0.0f;  
                                         
                 if(music_danger_volume > music_volume) 
                     music_danger_volume = music_volume; 
                        
             }

                                           
             if(game_mode == WALK)     
             if((int)TimerGetTime() > dancing_timer)
                 start_dancing = DANCE_PLAYING;
             
             if(game_mode == WALK)
			 if(loop >= 0)  
             if(sprite[loop].type == BAG  
             && (sprite[loop].sector == UNIT_SEAGULL ||sprite[loop].sector == UNIT_SEAGULL2) ) 
             if((int)TimerGetTime() > sprite[loop].all_timer)
             if(ply_id != -1)
             if(sprite[loop].score > 0)
             if(sprite[loop].status != NOISE_MAKING ) 
             if(Is_Guy_In_Range(loop, ply_id, (float)ENEMY_ACT_RANGE) == true)
             {
                                       
                 Set_Sprite(loop, sprite[loop].base_anim+2, LOOP, ANIM_SPRITE, ANIM_WALKING); // Stunned                           
                 
                 if(sprite[loop].sector == UNIT_SEAGULL) 
                 {   
                     sprite[loop].all_timer = (int)TimerGetTime() + 1000; 
                     
                     if(Level != LVL_HIGHWAY && Level != LVL_FARMS 
					 && Level != LVL_ROADWAY && Level != LVL_VILLAGE 
					 && Level != LVL_TOWN && Level != LVL_CASTLEROOF
					 && Level != LVL_MULTI3 && Level != LVL_MULTI5)              
                         seagull_sfx = true;                          
                     else  
                         crow1_sfx = true; 
                 } 
                 
                 if(sprite[loop].sector == UNIT_SEAGULL2)
                 {   
                     
                     if(Level != LVL_HIGHWAY && Level != LVL_FARMS && Level != LVL_ROADWAY && Level != LVL_VILLAGE && Level != LVL_TOWN && Level != LVL_CASTLEROOF)              
                         seagull2_sfx = true;                          
                     else
                         crow1_sfx = true;

                     sprite[loop].all_timer = (int)TimerGetTime() + 5000;
                 }   
                 
                 sprite[loop].status = NOISE_MAKING;  
                                                                       
             }
             
             if(game_mode == WALK)   
			 if(loop >= 0)  
             if(sprite[loop].type == BAG  
             && (sprite[loop].sector == UNIT_SEAGULL ||sprite[loop].sector == UNIT_SEAGULL2) ) 
             if((int)TimerGetTime() > sprite[loop].all_timer) 
             if(sprite[loop].score > 0)
             if(sprite[loop].status == NOISE_MAKING )
             {
                 Set_Sprite(loop, sprite[loop].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); // Stunned                           
                 sprite[loop].all_timer = (int)TimerGetTime() + (3000+rand()%12000);
                 sprite[loop].status = IDLE;
             }       
                                                                                         
             if(game_mode == WALK)
			 if(loop >= 0)  
             if(sprite[loop].type == OBJ  
             && (sprite[loop].sector_action == OBJ_SEAGULL ||sprite[loop].sector_action == OBJ_SEAGULL2) ) 
             if((int)TimerGetTime() > sprite[loop].all_timer)
             if(ply_id != -1)
             if(sprite[loop].status != NOISE_MAKING ) 
             if(Is_Guy_In_Range(loop, ply_id, (float)ENEMY_ACT_RANGE) == true)
             {
                 if( sprite[loop].linked_sprite != LINKED_BUOY && sprite[loop].linked_sprite != LINKED_DRIP && sprite[loop].linked_sprite != LINKED_SNIPER)                      
                     Set_Sprite(loop, sprite[loop].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); // Stunned                           
                 if(sprite[loop].linked_sprite == LINKED_DRIP || sprite[loop].linked_sprite == LINKED_SNIPER)
                     Set_Sprite(loop, sprite[loop].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned                           
                 
                 if(sprite[loop].sector_action == OBJ_SEAGULL)
                 {    
                     
                     sprite[loop].all_timer = (int)TimerGetTime() + 1000;
                                               
                     if( sprite[loop].linked_sprite == LINKED_SEAGULL)                                               
                         seagull_sfx = true;
                          
                     if( sprite[loop].linked_sprite == LINKED_DOG)                                               
                         bark_sfx = true; 
                          
                     if( sprite[loop].linked_sprite == LINKED_BUOY)                                               
                         buoy_sfx = true;  
                          
                     if( sprite[loop].linked_sprite == LINKED_DRIP)                                               
                         drip_sfx = true;  
                                               
                     if( sprite[loop].linked_sprite == LINKED_SNIPER)  
                     {                                             
                         sniperply_sfx = true; 
                     }
                                                                           
                     
                 }
                 
                 if(sprite[loop].sector_action == OBJ_SEAGULL2)
                 { 
                     seagull2_sfx = true;  
                     sprite[loop].all_timer = (int)TimerGetTime() + 5000;
                 } 
                 
                 sprite[loop].status = NOISE_MAKING; 
             }   
             
             if(game_mode == WALK)   
			 if(loop >= 0)  
             if(sprite[loop].type == OBJ  
             && (sprite[loop].sector_action == OBJ_SEAGULL ||sprite[loop].sector_action == OBJ_SEAGULL2) ) 
             if((int)TimerGetTime() > sprite[loop].all_timer) 
             if(sprite[loop].status == NOISE_MAKING )
             {
                 Set_Sprite(loop, sprite[loop].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); // Stunned                           
                 sprite[loop].all_timer = (int)TimerGetTime() + (3000+rand()%12000);
                 sprite[loop].status = IDLE;
             }              
 
             // Bullet Testing  
             if(game_mode == WALK)  
			 if(loop >= 0)  
             if(sprite[loop].type == UNT && (sprite[loop].score > 0 || sprite[loop].status == DIEING)
             || sprite[loop].type == BAG && sprite[loop].score > 0
             || sprite[loop].type == DOR && sprite[loop].score > 0) 
			 if(sprite[loop].sector != UNIT_DECOY) 	
			 if((int)TimerGetTime() > sprite_to_fx_timer) 
             {
				 if( (loop == ply_id && ply_id != -1) || !CONTROLLER)
				 {
					DXPick_Up=-1; 
					DXTalk_Man=-1;
					DXJustCollected=false;
				 }
				  
 				 if(ply_dead == false && lock_player == false)
                     Test_Sprite_to_Fx(loop, f_rate);   // Needs optimizing... 

             } 
             
			 if(loop >= 0)  
             if(sprite[loop].type == UNT) 
             if(sprite[loop].status != SPECIAL)
             if(sprite[loop].sector != UNIT_SHARK)
             if(sprite[loop].sector != UNIT_MORTAR)             
             if(sprite[loop].sector != UNIT_BOMBER) 
			 if(sprite[loop].sector != UNIT_DECOY) 	  
             if(sprite[loop].onDeath_action != -1)
             {
                if(sprite[loop].sector == UNIT_GUNNER)                  
                    sprite[loop].id = 18;               
                if(sprite[loop].sector == UNIT_SHIELD)                   
                    sprite[loop].id = 26;                      
                if(sprite[loop].sector == UNIT_CHIEF)                  
                    sprite[loop].id = 20;  
                if(sprite[loop].sector == UNIT_MONKEY)                  
                    sprite[loop].id = 20;   
                if(sprite[loop].sector == UNIT_DOG)                   
                    sprite[loop].id = 32;   
                if(sprite[loop].sector == UNIT_BOX)                  
                    sprite[loop].id = 25;                                                                        
                if(sprite[loop].sector == UNIT_BOMBER)                   
                    sprite[loop].id = 28;  
                if(sprite[loop].sector == UNIT_MORTAR1)                  
                    sprite[loop].id = 33;                      
                if(sprite[loop].sector == UNIT_SHARK)                  
                    sprite[loop].id = 31; 
                if(sprite[loop].sector == UNIT_SAILOR)                  
                    sprite[loop].id = 23; 
                if(sprite[loop].sector == UNIT_GRUNT)                  
                    sprite[loop].id = 23;                     
                if(sprite[loop].sector == UNIT_SHOTGUN)                   
                    sprite[loop].id = 33;  
                if(sprite[loop].sector == UNIT_MACHINE)                   
                    sprite[loop].id = 33;   
                if(sprite[loop].sector == UNIT_GUARD)                   
                    sprite[loop].id = 33;                                                                                  
                                                
                sprite[loop].fx_id = animation_fx[sprite[loop].id];
                
                sprite[loop].onDeath_action = -1;
                
             }      
                                                            
             // Turn code  
             if(sprite[loop].type == UNT)
			 if(sprite[loop].sector != UNIT_DECOY) 	
             if(loop >= 0)  
             if(lan_game == false || sprite[loop].linked_sprite  == player_type)
             if( (loop != p1_id && loop != p2_id && loop != p3_id && loop != p4_id) || loop == ply_id || dm_game == DM_NONE )
             if(sprite[loop].sector != UNIT_VEHICLE)
             if(run_angle_check == true && sprite[loop].score > 0)
             if(sprite[loop].on_ladder == false)
             if(sprite[loop].status != SPECIAL) 
             if(sprite[loop].status != OPEN_FIRE 
             && sprite[loop].status != OPEN_CUT 
             && sprite[loop].status != OPEN_STAMP
             && sprite[loop].status != OPEN_THROW )
             if(sprite[loop].status != MERCY && sprite[loop].status != MERCY1 && sprite[loop].status != GROUND_SPAWN)
             if(sprite[loop].angle != sprite[loop].tar_angle)
             { 
                  Turn_Unit(loop, f_rate);   
             }
                                   
             // Scrolling Texture code 
			 if(loop >= 0)  
             if(sprite[loop].type == SCR || (sprite[loop].type == FE_SCROLL && game_mode == FRONT) )
			 if( texture_fx[sprite[loop].id] == 0 || texture_fx[sprite[loop].id] == 1)
             { 
   
                 temp_distance = (float)sprite[loop].score / 200000.0f; 
                 
                 if(sprite[loop].onCreate == 0)
                 {
                     sprite[loop].u[0] += (temp_distance*(float)f_rate); // 0.01 - 0.002
                     sprite[loop].u[1] += (temp_distance*(float)f_rate);
                     sprite[loop].u[3] += (temp_distance*(float)f_rate);
                     sprite[loop].u[2] += (temp_distance*(float)f_rate);
                 }
                 else 
                 {
                     sprite[loop].v[0] -= (temp_distance*(float)f_rate)*2; // 0.01f - 0.002f
                     sprite[loop].v[1] -= (temp_distance*(float)f_rate)*2;
                     sprite[loop].v[3] -= (temp_distance*(float)f_rate)*2;
                     sprite[loop].v[2] -= (temp_distance*(float)f_rate)*2;
                 }
             
             } 
        
        // Talk man anims    
		if(loop >= 0)  
        if( sprite[loop].type == OBJ && (int)TimerGetTime() > sprite[loop].all_timer && sprite[loop].selected == true)
        if(sprite[loop].sector_action != OBJ_SHOTGUN)
        if(sprite[loop].sector_action != OBJ_PISTOL)
        if(sprite[loop].sector_action != OBJ_MACHINE) 
        if(sprite[loop].sector_action != OBJ_RIFLE)                  
        if(sprite[loop].sector_action != OBJ_HEALTH)   
        if(sprite[loop].sector_action != OBJ_GRENADE) 		              
        { 
            
            sprite[loop].selected = false; 
             
            if(sprite[loop].sector_action != OBJ_SWITCH && sprite[loop].sector_action != OBJ_NONE) 
                Set_Sprite(loop, sprite[loop].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING);
                
        }   

        if(loop >= 0)  
        if( sprite[loop].all_timer != -1)
        if( sprite[loop].mouseover == true)
        if( sprite[loop].type == OBJ && (int)TimerGetTime() > sprite[loop].all_timer)
        if(sprite[loop].sector_action == OBJ_SHOTGUN || sprite[loop].sector_action == OBJ_PISTOL 
		|| sprite[loop].sector_action == OBJ_MACHINE || sprite[loop].sector_action == OBJ_RIFLE 
		|| sprite[loop].sector_action == OBJ_HEALTH  || sprite[loop].sector_action == OBJ_GRENADE)
        {  
            sprite[loop].mouseover = false;   

        }          
		  
        if(loop >= 0)    
		if(sprite[loop].type == OBJ) 
		if(sprite[loop].alpha != 0.0f) 
		if(sprite[loop].sector_action == OBJ_TIMEPLUS_SMLL 
		|| sprite[loop].sector_action == OBJ_TIMEPLUS_MID  
		|| sprite[loop].sector_action == OBJ_TIMEPLUS_BIG
		|| sprite[loop].sector_action == OBJ_BONUS1  
		|| sprite[loop].sector_action == OBJ_BONUS2
		|| sprite[loop].sector_action == OBJ_BONUS3 
		|| sprite[loop].sector_action == OBJ_PISTOL_UP  
		|| sprite[loop].sector_action == OBJ_RIFLE_UP
		|| sprite[loop].sector_action == OBJ_LIFE_UP  
		|| sprite[loop].sector_action == OBJ_BONUS4)
        {  
            sprite[loop].angle += 0.1f*(float)f_rate;  
        }       

						
                
        // Buddy follow code... 
		if(loop >= 0)    
        if(game_mode == WALK && !mode)     
        if(sprite[loop].sector_action == AI_BUDDY )
        if(sprite[loop].type == UNT && sprite[loop].score > 0) 
        if(sprite[loop].status != STUNNED
        && sprite[loop].status != FOOT_SHOT
        && sprite[loop].status != FLATTENED
        && sprite[loop].status != OPEN_FIRE
        && sprite[loop].status != DIEING) 
        if(sprite[loop].linked_sprite == p_server) 
        if(ply_id != -1)   
        if(follow_x != -1 && follow_y != -1)    
        if((int)TimerGetTime() > follow_timer)        
        {     
  		  
		  if(Level == LVL_SUB_PEN) 
		      stop_range = (float)BUDDY_CRATE_STOP_RANGE;			
		  else
		      stop_range = (float)BUDDY_STOP_RANGE; 			
  		   
		  if(Level == LVL_SUB_PEN)
		      return_range = (float)BUDDY_CRATE_RETURN_RANGE;			
		  else
		      return_range = (float)BUDDY_RETURN_RANGE;

          if(Is_Guy_In_Range(loop, ply_id, stop_range) == false && Is_Guy_In_Range(loop, ply_id, return_range) == false)
          {      
                  
            follow_timer = (int)TimerGetTime()+150;  

            sprite[loop].fire_target = -1;

            sprite[loop].emy_shoot = ((int)TimerGetTime() + 500);  
 
			if(Level != LVL_SUB_PEN)   
            	sprite[loop].fire_target = -1; 
                            
            Find_Path(loop, follow_x, follow_y);
                                
          }    
                
        }  
        
        // Buddy follow code...   
 /*       if(game_mode == WALK && !mode)    
        if(sprite[loop].sector_action == AI_BUDDY )
        if(sprite[loop].type == UNT && sprite[loop].score > 0) 
        if(sprite[loop].moving == true)
        if(sprite[loop].linked_sprite == p_server) 
		if(loop >= 0)  
        if(ply_id != -1)   
        {   
  		  
		  if(main_mission[MISSION_NUN] == IN_PROGRESS)
		      stop_range = (float)BUDDY_CRATE_STOP_RANGE;			
		  else
		      stop_range = (float)BUDDY_STOP_RANGE;			

          if(Is_Guy_In_Range(loop, ply_id, stop_range) == true)
          {
              ShotIdle(loop);
              sprite[loop].col_timer = (int)TimerGetTime() + 100;
  		  }
  		  
        }*/
 
        // Turn off guy alarm mode...
        if(game_mode == WALK && !mode) 
        if(sprite[loop].type == UNT && sprite[loop].score > 0)
        if(sprite[loop].spotted == true)  
        if(sprite[loop].sector_action == AI_DEFEND || sprite[loop].sector_action == AI_BUDDY )  
		if(loop >= 0)          
        if(loop != ply_id) 
        if((int)TimerGetTime() > sprite[loop].spotted_timer)          
        { 
            sprite[loop].spotted_timer = 0;     
            sprite[loop].spotted = false;  
        }
 
        if(game_mode == WALK && !mode) 
        if(sprite[loop].type == UNT && sprite[loop].score > 0)
        if(sprite[loop].sector == UNIT_BOMBER)    
		if(loop >= 0)       
        if(loop != ply_id) 
		{		
			if(ply_id != -1)  
			{
	           	sprite[loop].mov_x = (sprite[ply_id].w + sprite[ply_id].box_width/2);    
	           	sprite[loop].mov_y = sprite[ply_id].z;  
			}  

		}	
                                 
        if(game_mode == WALK && !mode)   
		if(loop >= 0)  
        if(loop != ply_id) 
        if(sprite[loop].sector_action == AI_DEFEND || sprite[loop].sector_action == AI_BUDDY || sprite[loop].sector_action == AI_STAND || sprite[loop].sector_action == AI_HUNT)           
        if(sprite[loop].type == UNT && sprite[loop].score > 0 
        && sprite[loop].status == IDLE   
        && sprite[loop].moving == false )    
        if(sprite[loop].status != SPECIAL) 
        if((int)TimerGetTime() > sprite[loop].ai_timer)          
        {   
	         
	        if(loop != ply_id) 
	        if(loop != p1_buddy)
	        if(sprite[loop].group_id != -1) 
	        if(sprite[loop].on_ladder == false)   
	        if(sprite[loop].ai_brain == BRAIN_HEALING)
	        {
			 						 
			 	chute_sfx = true;
				 					 
	            Respawn_Enemy(sprite[loop].group_id); 
	            
	            sprite[loop].idle_type = IDLE_NONE; 
	            sprite[loop].ai_brain = BRAIN_HUNTER; 
	            sprite[loop].group_id = -1; 	            
			}
			 
			if(sprite[loop].sector_action != AI_HUNT)
			if(sprite[loop].sector != UNIT_BOMBER)  
			{     

			/*	if(STA2_MODE == MODE_MOVING)
				{
					frnd = (float)((rand()%6)-3);        
  
					sprite[loop].mov_x = (sprite[loop].w + sprite[loop].box_width/2) + (cos(frnd)*0.016f);    
					sprite[loop].mov_y = (sprite[loop].z + sprite[loop].box_height/2) + (sin(frnd)*0.016f); 
   	
					if( sprite[loop].mov_x  < -map_startX || sprite[loop].mov_x  >  map_startX  || sprite[loop].mov_y < -map_startY || sprite[loop].mov_y >  map_startY  )
					{
						sprite[loop].mov_x = (sprite[loop].w + sprite[loop].box_width/2);
						sprite[loop].mov_y = (sprite[loop].z + sprite[loop].box_height/2);  
					} 
				}*/

	         //   ShotIdle(loop);
			} 
			   
			if(ARCADE)   
			if(ply_id != -1)
			if(sprite[loop].sector_action == AI_HUNT) 
			{      

	            sprite[loop].mov_x = sprite[ply_id].w + sprite[ply_id].box_width/2;    
	            sprite[loop].mov_y = sprite[ply_id].z + sprite[ply_id].box_height/2; 

	            sprite[loop].end_x = sprite[ply_id].w + sprite[ply_id].box_width/2;    
	            sprite[loop].end_y = sprite[ply_id].z + sprite[ply_id].box_height/2; 

			//	sprite[loop].col_timer = 0;
				sprite[loop].bagging = false;
				 
				sprite[loop].moving = true;
				sprite[loop].status = MOVE_OUT;

				Find_Path(loop, sprite[loop].end_x, sprite[loop].end_y); 

			} 
                         
            // Turn the guy 
            if(sprite[loop].spotted == false)     
                sprite[loop].ai_timer = (int)TimerGetTime() + 4000;
            else
                sprite[loop].ai_timer = (int)TimerGetTime() + 1000;
                                        
            rnd = rand()%3;
             
        }     
          
        // Stop trying to heal a guy if he's already been healed...
		if(loop >= 0)  
        if(sprite[loop].group_id >= 0)
	    if(sprite[loop].sector != UNIT_DECOY) 	
		if(sprite[loop].ai_brain == BRAIN_HEALING) 
		if( (sprite[sprite[loop].group_id].score > 0 && ( sprite[sprite[loop].group_id].status != MERCY))
		|| sprite[sprite[loop].group_id].status == DEATH_READY
		|| sprite[sprite[loop].group_id].status == MAN_DOWN1)
		{
            sprite[loop].idle_type = IDLE_NONE; 
            sprite[loop].ai_brain = BRAIN_DEFAULT;       
            sprite[loop].group_id = -1;
           
			ShotIdle(loop); 		 									   
        }
		
		                     
        if(game_mode == WALK && !mode)  
		if(loop >= 0)    
        if(sprite[loop].type == UNT) 
        if(lan_game == false || player_type == sprite[loop].linked_sprite)          
        {           
           
            // Circular triggers
            if(lock_player != true)  
			if(ply_dead == false)
            if(sprite[loop].type == UNT)
		    if(sprite[loop].sector != UNIT_DECOY) 
            if(sprite[loop].turn_off == false)  
                Test_sprite_to_trigger(loop);  
                 
            // Obj triggers 
			if(!CONTROLLER)
            if(lock_player != true)   
			if(ply_dead == false)
			if(loop >= 0)           
            if(sprite[loop].type == UNT) 
		    if(sprite[loop].sector != UNIT_DECOY) 
            if(ply_id != -1)  
            if(loop == ply_id && sprite[loop].fire_target >= 0)
            if(sprite[sprite[loop].fire_target].type == OBJ 
            || sprite[sprite[loop].fire_target].status == TIED)
            if(sprite[sprite[loop].fire_target].mouseover == false)
                Test_sprite_to_Obj(loop, sprite[loop].fire_target);
			 
            // Obj triggers  
			if(CONTROLLER)
			if(loop >= 0)           
            if(sprite[loop].type == UNT) 
		    if(sprite[loop].sector != UNIT_DECOY) 
            if(ply_id != -1) 
			if(DXPick_Up==-1) 
            if(loop == ply_id)  
			if((int)TimerGetTime() > sprite_to_fx_timer) 
			{       

				DXTalk_Man=-1; 

				closest_talk=-1; 
				 
				closest_point=10000.0f;        

				if(ply_dead == false && lock_player == false) 
				for(int m=0;m<player_counter;m++)     
				{
					if( (sprite[player_list[m]].type == OBJ || sprite[player_list[m]].status == TIED)  
					|| (sprite[player_list[m]].type == UNT && sprite[player_list[m]].sector == UNIT_DECOY && sprite[player_list[m]].score > 0))
					if(sprite[player_list[m]].sector_action != OBJ_LIGHT)
					if( sprite[player_list[m]].sector_action != -1)
					if(sprite[player_list[m]].sector_action != OBJ_NONE || sprite[player_list[m]].sector == UNIT_DECOY)
					if(sprite[player_list[m]].alpha != 0.0f) 
					if(sprite[player_list[m]].mouseover == false)  
					{
						mid_x = sprite[loop].w+sprite[loop].box_width/2;
						mid_y = sprite[loop].z+sprite[loop].box_height/2;     
                 
						tar_x = sprite[player_list[m]].w + sprite[player_list[m]].box_width/2;
						tar_y = sprite[player_list[m]].z + sprite[player_list[m]].box_height/2; 

						dis_to_point=Node_Distance(mid_x, mid_y, tar_x, tar_y);

						if(closest_point > dis_to_point) 
						{
							closest_point=dis_to_point;
							closest_talk=player_list[m];
						}
					} 

				} 

				if(closest_talk != -1)  
				{
					Test_sprite_to_Obj(loop, closest_talk);
				}

			}

            // Bombers shell lands
			if(loop >= 0)  
            if(sprite[loop].jumping == true)
            if((int)TimerGetTime() > sprite[loop].bomb_timer)
            {    
                sprite[loop].jumping = false;          
                Bomb_Run(sprite[loop].shell_x, sprite[loop].shell_y, loop, 1);
            }    
                         
            // Reset my fire target if he's dead  
			if(loop >= 0)  
            if(sprite[loop].type == UNT)
		    if(sprite[loop].sector != UNIT_DECOY) 
            if(ply_id != -1)
            if(sprite[loop].score > 0 && sprite[loop].status != GROUND_SPAWN)
            if(sprite[loop].fire_target != -1)         
            {      
                
                if(sprite[sprite[loop].fire_target].score <= 0 || sprite[sprite[loop].fire_target].status == FALLING || sprite[sprite[loop].fire_target].status == LEVELING)
                if(sprite[sprite[loop].fire_target].status != DIEING || loop != ply_id)
                {
                    sprite[loop].fire_target = -1; 
                    sprite[loop].turning     = false;    
                }   
               
            }       
                                      
            // If it's against the computer or it's one of my men
			if(loop >= 0)  
            if( lan_game == false || player_type == sprite[loop].linked_sprite)
            {     
                     
            if( (sprite[loop].status == IDLE || sprite[loop].status == SHOT_IDLE) && (int)TimerGetTime() > sprite[loop].all_timer) 
            {   
                sprite[loop].emy_shooting = false; 
            }  
            
            if(loop >= 0)     
            if(loop != p1_id && loop != p2_id && loop != p3_id && loop != p4_id)     
            if(sprite[loop].status == FALLING && (int)TimerGetTime() > sprite[loop].all_timer)
            { 
                sprite[loop].status = DEATH_READY; 
                sprite[loop].update = true;    
                sprite[loop].turn_off = true;            
            }

            if(loop >= 0)  
            if(sprite[loop].status == DIEING && (int)TimerGetTime() > sprite[loop].all_timer)
            { 
                 
                sprite[loop].score = 0;   
                    
                sprite[loop].status = MAN_DOWN; 
                
                sprite[loop].fire_target = -1; 
                                
                sprite[loop].death_flash = false;  
                
                sprite[loop].alpha = 1.0;
                
                if(sprite[loop].onDeath_action != TANK_TOP)
                    sprite[loop].priority = 3; 
                  
                if(sprite[loop].on_mud == true)   
                    sprite[loop].depth = 0.0f;    
                
                sprite[loop].update = true;  
                sprite[loop].anim_state = WAIT;
                   
                if(sprite[loop].sector != UNIT_SKELETON 
                && sprite[loop].sector != UNIT_DEAD_CHIEF) 
                    sprite[loop].all_timer = (int)TimerGetTime() + 12000; // 6000
                     
                if(sprite[loop].sector == UNIT_SKELETON
                || sprite[loop].sector == UNIT_DEAD_CHIEF) 
                    sprite[loop].all_timer = (int)TimerGetTime() + 1500;
                    
                if(sprite[loop].sector == UNIT_BOX) 
                    sprite[loop].all_timer = (int)TimerGetTime() + 2000;                    
          
            }  
      
            if(loop >= 0)  
            if(sprite[loop].status == MERCY && (int)TimerGetTime() > sprite[loop].all_timer)
            { 
             
            } 
   
            if(loop >= 0)              
            if(sprite[loop].status == MAN_DOWN && (int)TimerGetTime() > sprite[loop].all_timer)
            { 
                                
           /*     if(p1_buddy != -1 && ply_buddy_dead == false)      
                if(loop == p1_buddy ) 
                {
                    ply_buddy_dead = true;  
					sprite[p1_buddy].alpha = 0.0f; // Hack                  
                }                      
                 
                sprite[loop].fire_target = -1;   
                                   
                sprite[loop].status = MAN_DOWN1;    
                sprite[loop].update = true;      
                sprite[loop].anim_state = WAIT;  
                  
                if(sprite[loop].sector != UNIT_SKELETON    
                && sprite[loop].sector != UNIT_DEAD_CHIEF)  
                    sprite[loop].all_timer = (int)TimerGetTime() + 2000; // 8000 - 470000
                    
                if(sprite[loop].sector == UNIT_SKELETON 
                || sprite[loop].sector == UNIT_DEAD_CHIEF) 
                    sprite[loop].all_timer = (int)TimerGetTime() + 2000; */
                
          /*      if(sprite[loop].sector == UNIT_BOX)
                {
                                       
                    mid_x = sprite[loop].w+sprite[loop].box_width/2; 
                    mid_y = sprite[loop].z+sprite[loop].box_height/2;  
                                     
                    Shell_Landed(mid_x, mid_y, loop, f_rate, INV_GRENADE, -1);
                    Create_Frag_Effect( mid_x, mid_y); 
                                                           
                }*/
                  
            }         
            if(loop >= 0)  
            if( (loop != p1_id && loop != p2_id && loop != p3_id && loop != p4_id) || dm_game == DM_NONE )
            if(sprite[loop].sector != UNIT_SKELETON && sprite[loop].sector != UNIT_DEAD_CHIEF)                 
            if(sprite[loop].status == MAN_DOWN1 && (int)TimerGetTime() > sprite[loop].all_timer)
            {             
            /*    sprite[loop].status = DEATH_READY;  
                sprite[loop].update = true;    
                sprite[loop].turn_off = true; */
   
            //    Remove_From_List(loop); 
            }     
   
            if(loop >= 0)  
            if(ply_id != -1 && next_scene == false) 
            if(sprite[loop].status == LEVELING) 
				Convert_Dir_To_Angle(ply_id, DOWN);

            if(loop >= 0)  
            if(ply_id != -1 && next_scene == false) 
            if(sprite[loop].status == LEVELING)
            if((int)TimerGetTime() > sprite[loop].all_timer)
            { 
                lock_player = false; 
                ShotIdle(ply_id); 
                
                if(global_objects[98] == GLOBAL_UNBEATEN) // Training M-Accomplished scene   
                if(current_main == MISSION_TRAINING) 
                if(mission_training_is_done == false)                   
                if(mission_accomplished_active == false) 
                {
                    mission_accomplished_active = true;    
                    Mission_Accomplished(true);  // Displays Victory screen
                    global_objects[98] = GLOBAL_BEATEN;
                }    
                
                if(current_main == MISSION_RADIO)                   
                if(mission_accomplished_active == false)
                {
                    mission_accomplished_active = true;    
                    Mission_Accomplished(true);   
                }  
                
                if(current_main == MISSION_SUPPLIES)                   
                if(mission_accomplished_active == false)
                {
                    mission_accomplished_active = true;    
                    Mission_Accomplished(true);   
                } 
                
                if(current_main == MISSION_FORTRESS)                   
                if(mission_accomplished_active == false)
                {
                    mission_accomplished_active = true;     
                    Mission_Accomplished(true);    
                }     
                
                if(current_main == MISSION_RADAR)                     
                if(mission_accomplished_active == false)
                {
                    mission_accomplished_active = true;    
                    Mission_Accomplished(true);   
                }      
                
                if(current_main == MISSION_NUN)                     
                if(mission_accomplished_active == false) 
                {
                    mission_accomplished_active = true;    
                    Mission_Accomplished(true);   
                }     
                
                if(current_main == MISSION_CELLARS)                     
                if(mission_accomplished_active == false) 
                { 
                    mission_accomplished_active = true;    
                    Mission_Accomplished(true);   
                }    
                
                if(current_main == MISSION_REVENGE)                   
                if(mission_accomplished_active == false)
                {
                    mission_accomplished_active = true;    
                    Mission_Accomplished(true);   
                }  
                
                if(current_main == MISSION_TRENCH)  
                if(main_mission[MISSION_TRENCH] == IN_PROGRESS)                 
                {
                    episode = 1;
                    scene = 134;
                    
                    next_scene = true;
                       
                }                                                                                           
                                                
//                Display_Message(ply_id, MSG_SUCCESS1);
                
            }    
            if(loop >= 0)  
            if(ply_id != -1) 
            if(sprite[loop].status == LEVELING)
            {
                lock_player = true;                       
            }
            if(loop >= 0)                      
            if(ply_id != -1)            
            if(sprite[loop].status == CELEBRATE || sprite[loop].status == DEFEATED)
            if((int)TimerGetTime() > sprite[loop].all_timer)
            { 


                if(sprite[loop].status == CELEBRATE)
                {
                    
                    if(mission == MISSION_HIGHLANDERS)                   
                    {                 
                        episode = 2;
                        scene   = 1; 
                        current_spawn = 7;  
                        next_scene = true; 
						Convert_Dir_To_Angle(ply_id, DOWN);
                        sprite[loop].status = CELEBRATE;
                        sprite[loop].all_timer = (int)TimerGetTime() + 6000; 
                    } 
                    
                    if(mission == MISSION_CONVOY)                   
                    {
                        episode = 2;
                        scene   = 0; 
                        current_spawn = 14;  
                        next_scene = true; 
						Convert_Dir_To_Angle(ply_id, DOWN);
                        sprite[loop].status = CELEBRATE;
                        sprite[loop].all_timer = (int)TimerGetTime() + 6000; 
                    }
                    
                    if(mission == MISSION_SUPPLIES)                    
                    {
                        episode = 2;
                        scene   = 0; 
                        current_spawn = 14;  
                        next_scene = true; 
						Convert_Dir_To_Angle(ply_id, DOWN);
                        sprite[loop].status = CELEBRATE;
                        sprite[loop].all_timer = (int)TimerGetTime() + 6000; 
                    } 
                                        
                    if(mission == MISSION_TRAINING)                    
                    {
                        Display_Message(ply_id, MSG_SUCCESS1);
                        lock_player = false;    
                        mission_objective = MISSION_PASSED;
                        Convert_Dir_To_Angle(ply_id, DOWN);
                        ShotIdle(ply_id); 
                        sprite[loop].all_timer = (int)TimerGetTime() + 500; 
                    }
                                  
                    mission = MISSION_NONE;
                                    
                }                    
                
                if(sprite[loop].status == DEFEATED)
                {
                    
                    if(mission == MISSION_HIGHLANDERS)                   
                    {                  
                        episode = 2;
                        scene   = 1; 
                        current_spawn = 7;  
                        next_scene = true; 
                        sprite[loop].status = DEFEATED;
                        sprite[loop].all_timer = (int)TimerGetTime() + 6000; 
                    }
                    if(mission == MISSION_CONVOY)                   
                    {                   
                        episode = 2;  
                        scene   = 0; 
                        current_spawn = 14;  
                        next_scene = true; 
                        sprite[loop].status = DEFEATED;
                        sprite[loop].all_timer = (int)TimerGetTime() + 6000; 
                    }   
                    if(mission == MISSION_SUPPLIES)                   
                    {                  
                        episode = 2; 
                        scene   = 0; 
                        current_spawn = 14;  
                        next_scene = true; 
                        sprite[loop].status = DEFEATED;
                        sprite[loop].all_timer = (int)TimerGetTime() + 6000; 
                    }                                         
                    if(mission == MISSION_TRAINING)                   
                    {
                        Display_Message(ply_id, MSG_FAILED1);
                        lock_player = false;   
                        mission_objective = MISSION_OFF;
                        Convert_Dir_To_Angle(ply_id, DOWN);
                        ShotIdle(ply_id);
                        sprite[loop].all_timer = (int)TimerGetTime() + 500;                                                 
                        
                    }
                    
                    mission = MISSION_NONE;
                                        
                }                      

            }        

            if(loop >= 0)  
            if(sprite[loop].type == UNT)
            if(lock_player != true || loop != ply_id)
            if(sprite[loop].status != FALLING)    
            if(sprite[loop].status != MERCY)                              
            if(sprite[loop].score > 0)             
            if((sprite[loop].status == STUNNED || sprite[loop].status == FOOT_SHOT))
            if((int)TimerGetTime() > sprite[loop].all_timer)
            { 
             
				 if(sprite[loop].status == STUNNED)
                 if(sprite[loop].moving == true)
                 {
                    sprite[loop].status = MOVE_OUT; 
                    sprite[loop].turning = false;
                    sprite[loop].anim_state = WAIT; 
                    sprite[loop].update = true;                       
                 } 
                 else          
                 {
                    ShotIdle(loop); 
                 }         
                
            }  

			if(loop == ply_id)     
            if(sprite[loop].type == UNT)  
            if(next_scene == false)  
            if(boss_success == true && Level == LVL_TANK_BOSS)
            if(sprite[loop].status == FLATTENED && (int)TimerGetTime() > sprite[loop].all_timer)
            {  
                ply_dead = true; 

				next_scene = true;

				reloading = false; 

				Calculate_Lifebar();

				if(current_main > 0) 
				if(main_mission[current_main] == IN_PROGRESS)
				{
					cycle_episode = episode; 
					cycle_scene   = scene;
					cycle_spawn   = last_spawn; 
                    
					activate_bicycle = true;
				} 
			}

            if(loop >= 0)    
            if(sprite[loop].type == UNT)  
            if(next_scene == false)  
            if(lock_player != true || loop != ply_id)
            if(sprite[loop].score > 0)              
            if(sprite[loop].status == FLATTENED && (int)TimerGetTime() > sprite[loop].all_timer)
            {  

                ShotIdle(loop);
                     
                if(is_a_stealth_mission == true)
                {
                    scene = 76;
                    episode = 1;
                    next_scene = true;  
                    failed_stealth = true;
                }
                
            }    
             
            // Shot has been taken 
			if(loop >= 0)   
            if(lock_player == false)  
            if(sprite[loop].type == UNT)      
            if(sprite[loop].score > 0)               
            if((int)TimerGetTime() > sprite[loop].all_timer)
            if(sprite[loop].status == OPEN_FIRE)
            {         
				sprite[loop].status = AIMING; 
				sprite[loop].anim_state = WAIT; 
				Rank_Timer(loop, AIMING);
            }
                        
            // Shot has been taken   
			if(loop >= 0)  	
            if(lock_player != true || loop != ply_id)   
            if(ply_id != -1) 
            if(sprite[loop].type == UNT) 
            if(sprite[loop].score > 0)               
            if((int)TimerGetTime() > sprite[loop].all_timer)
			if(STA2_MODE == MODE_MOVING)
            if(sprite[loop].status == AIMING
            || sprite[loop].status == OPEN_CUT  
            || sprite[loop].status == OPEN_STAMP
            || sprite[loop].status == AIM_CROUCH)  
            {   
                  ShotIdle(loop);
            }     
                         
            // Shot has been taken   
			if(loop >= 0)  	
            if(lock_player != true || loop != ply_id)   
            if(ply_id != -1) 
            if(sprite[loop].type == UNT) 
            if(sprite[loop].score > 0)               
            if((int)TimerGetTime() > sprite[loop].all_timer)
            if(sprite[loop].status == OPEN_THROW)  
            {   
                  ShotIdle(loop);
            }     
            
            // Shot has been taken  
			if(loop >= 0)  
            if(lock_player != true) 
            if(ply_id != -1)  
            if(loop == ply_id)           
            if(sprite[loop].score > 0)               
            if((int)TimerGetTime() > sprite[loop].all_timer)
            if(sprite[loop].status == OPEN_STAMP) // || sprite[loop].status == OPEN_THROW
            {  
                    
                    if(sprite[loop].moving == true)   
                    {    

                        sprite[loop].emy_shooting = false;   
						
                    } 
                    else          
                    {
                        ShotIdle(loop);  
                    }         
              
            }    
 
            if(loop >= 0)              
            if(lock_player != true || loop != ply_id)  
		    if(sprite[loop].sector != UNIT_DECOY)                          
            if(sprite[loop].status == MOVE_OUT && (int)TimerGetTime() > sprite[loop].all_timer)
            {
                sprite[loop].emy_shooting = false;                           
            } 
     
    /*        if(loop >= 0)         
            if(lock_player != true || loop != ply_id)  
            if(ply_id != -1)
            if(loop != ply_id)
            if(sprite[loop].status != MERCY)
		    if(sprite[loop].sector != UNIT_DECOY) 
            if(sprite[loop].score > 0 && sprite[loop].type == UNT)
            if(sprite[loop].status == AIMING || sprite[loop].status == AIM_CROUCH) 
            if(sprite[loop].bagging == false)
            if(sprite[loop].fire_target >= 0)  
            {
                sprite[loop].mov_x = sprite[sprite[loop].fire_target].w+sprite[sprite[loop].fire_target].box_width/2; 
                sprite[loop].mov_y = sprite[sprite[loop].fire_target].z+sprite[sprite[loop].fire_target].box_height/2; 
   	
				if( sprite[loop].mov_x  < -map_startX || sprite[loop].mov_x  >  map_startX  || sprite[loop].mov_y < -map_startY || sprite[loop].mov_y >  map_startY  )
				{
					sprite[loop].mov_x = (sprite[loop].w + sprite[loop].box_width/2);
					sprite[loop].mov_y = (sprite[loop].z + sprite[loop].box_height/2); 
				} 
					  
                sprite[loop].spotted_timer = (int)TimerGetTime() + 12000; // was 8000
                sprite[loop].spotted = true;
                 
                // If target runs away break aiming to go after him... 
                if(sprite[loop].status != AIM_CROUCH)
                if(Is_Guy_In_Range(loop, sprite[loop].fire_target, (float)ENEMY_ACT_RANGE) == false)
                {
                    if(sprite[loop].moving == true) // && sprite[loop].linked_sprite == player_type
                    {     

                        sprite[loop].emy_shooting = false;  
                                                                     
                        sprite[loop].all_timer = (int)TimerGetTime() + 2000;
                        sprite[loop].status = MOVE_OUT;  
                       
                        sprite[loop].turning = false; 
                        sprite[loop].anim_state = WAIT;  
                        sprite[loop].update = true;
                    } 
                    else           
                    {
                        ShotIdle(loop);   
                    }                                            
                }              
            }   */   
            
            if(loop >= 0)        
            if(f_rate < 100)         
            if(sprite[loop].status != FALLING)        
            if(sprite[loop].score > 0 && sprite[loop].type == UNT) 
            if(sprite[loop].turning == false && sprite[loop].status != GROUND_SPAWN)
            if(sprite[loop].status != FALLING) 
            if(sprite[loop].status != MERCY)
            if(sprite[loop].status == MOVE_OUT)  
            if(sprite[loop].moving == true)
            if(sprite[loop].bagging == false)
		    if(sprite[loop].sector != UNIT_DECOY)
			if(sprite[loop].linked_sprite == player_type || (sta2_enemy_mode == MOVE_MOVE && loop == emy_id)  ) 
                Moving_Code(loop, sprite[loop].mov_x, sprite[loop].mov_y, f_rate);
            
            // Regeneration...    
			if(loop >= 0)   
			if(p1_id != -1)
			if(ply_dead == false) 
            if(loop == p1_id || loop == p2_id)    
            if(PLY_REGENERATE != 0) 
			if(sprite[loop].score < PLY_VITALITY) 
			if((int)TimerGetTime() > reset_player_heal_timer)
            if((int)TimerGetTime() > sprite[loop].heal_timer)  
            {
                sprite[loop].heal_timer = (int)TimerGetTime() + (4000 - PLY_REGENERATE*150);

				if(sprite[loop].heal_timer < (int)TimerGetTime() + MAX_REGEN_RATE) 
				    sprite[loop].heal_timer = (int)TimerGetTime() + MAX_REGEN_RATE;
	
				bump_player_timer  = (int)TimerGetTime() + BUMP_TIME;
	            bump_player = true; 

                Calculate_Health(1, false, ply_id, true);        
            }  

            // Has buff activated...     
			if(loop >= 0)     
			if(sprite[loop].value2 >= 0)
			if(sta2_squad[sprite[loop].value2].wp >= 0)
			if(sta2_pack[sta2_squad[sprite[loop].value2].wp].special != PACK_SPECIAL_NONE) 
   			if(sta2_pack[sta2_squad[sprite[loop].value2].wp].special_charge > 0)
			if(sprite[loop].score > 1)
			if(sprite[loop].linked_sprite == player_type)
			{

				if(sta2_pack[sta2_squad[sprite[loop].value2].wp].special == PACK_SPECIAL_MAGICNET)
					sprite[loop].camo = true;
				else
					sprite[loop].camo = false; 

				if((int)TimerGetTime() > sprite[loop].heal_timer)  
				{


				}  
			}

            if(loop >= 0)    
            if(f_rate < 100)      
            if(sprite[loop].score <= 0 && sprite[loop].type == UNT)
            if(sprite[loop].on_ladder == true)
            {  
                                         
                deltay = 0.001f * (float)f_rate;  
                                      
                sprite[loop].y -= deltay;    
                sprite[loop].z -= deltay;
                 
            } 
                   
            if(loop >= 0)  
            if((loop != p1_id && loop != p2_id && loop != p3_id && loop != p4_id) || loop == ply_id) 
            if(lock_player != true || loop != ply_id)  
            if(sprite[loop].score > 0 && sprite[loop].type == UNT)
            if(sprite[loop].turning == false)
		    if(sprite[loop].sector != UNIT_DECOY) 
            if(sprite[loop].status != FALLING)   
            if(sprite[loop].status != SPECIAL) 
            if(sprite[loop].status != OPEN_FIRE && sprite[loop].status != OPEN_CUT 
			&& sprite[loop].status != OPEN_STAMP && sprite[loop].status != OPEN_THROW )
            if(sprite[loop].status != MERCY && sprite[loop].status != MERCY1 && sprite[loop].status != GROUND_SPAWN)
            if(sprite[loop].mov_x != 10001)  
            { 
                Set_Heading(loop, sprite[loop].mov_x, sprite[loop].mov_y, false); 
            }
                  
            // Shooting Test only used for defending units... 
			if(DISABLE_ALL_ENEMIES == 0)             
			if(loop >= 0)     
			if(loop != emy_id || sta2_turn == TURN_PLAYER)   
			if(loop != ply_id || sta2_turn == TURN_COMPUTER) 
            if(lock_player == false)           
            if(sprite[loop].sector_action != AI_NONE)     
            if(sprite[loop].type == UNT)  
		    if(sprite[loop].sector != UNIT_DECOY) 
            if(sprite[loop].status != STUNNED && sprite[loop].status != FOOT_SHOT)
            if(sprite[loop].status != OPEN_FIRE)    
            if(sprite[loop].status != DIEING) 
            if(sprite[loop].status != FLATTENED)    
			if(sprite[loop].ai_brain != BRAIN_HEALING) 
			if(sprite[loop].return_fire == true)
            if(sprite[loop].turn_off == false)
            if(sprite[loop].status != FALLING && sprite[loop].status != DEATH_READY)
            if((int)TimerGetTime() > sprite[loop].emy_shoot)  
            if(sprite[loop].score > 0 && sprite[loop].status != GROUND_SPAWN)
			if(sprite[loop].score > 1 || sprite[loop].linked_sprite != player_type)
            if(sprite[loop].status != MERCY && sprite[loop].status != MERCY1) 
            {                  
                sprite[loop].emy_shoot = ((int)TimerGetTime() + 100);     

                if((int)TimerGetTime() > sprite[loop].reload_timer)     
                    Shoot_Test(loop, f_rate);                       
            }              

       /*     if(DISABLE_ALL_ENEMIES == 0) 
			if(loop >= 0)        
            if(noise_maker != NO_NOISE) 
            if(ply_dead == false)      
            if(ply_id != -1)    
            if(loop != ply_id ) // && loop != p1_buddy
            if(sprite[loop].sector_action != AI_NONE)
            if(sprite[loop].status != MERCY)
            if(sprite[loop].bagging == false)
            if(sprite[loop].on_ladder == false || sprite[loop].moving == false)
            if(sprite[loop].type == UNT && sprite[loop].turn_off == false)
            if(sprite[loop].score > 0)
		    if(sprite[loop].sector != UNIT_DECOY) 
               Alert_Enemies(alert_guy, loop);  */
            
            } // lan_game == false or is one of my units 

        } // lan_game == false or is one of my units        
                                 
     }  // For loop 
     }  // !mode   
                            
     // Sinking in mud                
     if((int)TimerGetTime() > sinking_timer )     
     {
         sinking_timer = ((int)TimerGetTime() + 75);  
     }
                  
     // Tank squash check..
     if((int)TimerGetTime() > squash_timer)  
     {
                 
         squash_timer = (int)TimerGetTime() + 150;

     }                    
     
     enemy_has_a_man=false; 
     player_has_a_man=false;     
     
     no_of_enemies = 0;   
    
     update_counter=0;       
     
     test_tech_artillery = false;
     test_tech_mech      = false;
     test_tech_chief = false; 
     test_tech_barracks = false;
     test_tech_sniper = false;
     
     test_cpu_tech_artillery = false;
     test_cpu_tech_mech = false;
     test_cpu_tech_chief = false;
     test_cpu_tech_sniper = false;     
     cpu_tech_barracks = false;

     tech_artillery = test_tech_artillery;
     tech_mech = test_tech_mech;
     tech_chief = test_tech_chief;  
     tech_barracks = test_tech_barracks; 
     tech_sniper = test_tech_sniper; 
                  
     if(lan_game == false)  
     {
         cpu_tech_artillery = test_cpu_tech_artillery;
         cpu_tech_mech      = test_cpu_tech_mech;
         cpu_tech_chief     = test_cpu_tech_chief;
         cpu_tech_sniper    = test_cpu_tech_sniper;         
     }     

     if(!mode && game_mode == WALK)     
     {   
	 	 
	 if(game_over == false) 
     if((game_condition == G_VICTORY || game_condition == G_DEFEAT) && (int)TimerGetTime() > reset_map_timer )
     {
              
         game_condition = G_RESET;      

		 sta2_battle_load_outcome = sta2_battle_outcome;
                                                       
		if(sta2_battle_outcome == BATTLE_NONE) 
		{
			episode = 1;    
			scene   = 1;  
		}
                          
		if(sta2_battle_outcome == BATTLE_DEFEAT || sta2_battle_outcome == BATTLE_VICTORY)
		{
			episode = 1;  
			scene   = 2; 

			if(sta2_battle_outcome == BATTLE_DEFEAT) 
				sta2_next_event = EVENT_DEFEAT;

			if(sta2_battle_outcome == BATTLE_VICTORY)
				sta2_next_event = EVENT_VICTORY;

		}   

 	    sta2_battle_outcome = BATTLE_NONE; 

		next_scene = true;
                                 
     }     
     
     // Reduce fog timer     
     if((int)TimerGetTime() > reduce_fog_timer )      
     {
         reduce_fog_timer = ((int)TimerGetTime() + 50);  
     } 
  
     // Flash the fire_target 
     if(flash_on != -1)
     if(flash_on < TOTAL_NO_SPRITES)
     if(sprite[flash_on].flash_target == false) 
     if(sprite[flash_on].dflash_timer == 0)
     {       
       if((int)TimerGetTime() > target_flash_timer )
       {
 
         if(sprite[flash_on].alpha == 0.0)         
            sprite[flash_on].alpha = 1.0;
         else
            sprite[flash_on].alpha = 0.0;
   
         target_flash_timer = (int)TimerGetTime() + 50;
              
       }
       if((int)TimerGetTime() > target_flash_mtimer )
       {
         
         sprite[flash_on].alpha = 1.0;
       
         flash_on = -1;
              
       } 
     } 
       
     if(flash_on != -1)  
     if(flash_on >= TOTAL_NO_SPRITES)
     if((flash_on-TOTAL_NO_SPRITES) >= 0 && (flash_on-TOTAL_NO_SPRITES) < TOTAL_NO_FX_SPRITES) 
     {      
       if((int)TimerGetTime() > target_flash_timer ) 
       { 

         if(Fx[flash_on-TOTAL_NO_SPRITES].alpha == 1.0f)         
            Fx[flash_on-TOTAL_NO_SPRITES].alpha = 0.01f;
         else
            Fx[flash_on-TOTAL_NO_SPRITES].alpha = 1.0f;
   
         target_flash_timer = (int)TimerGetTime() + 50;
              
       } 
       if((int)TimerGetTime() > target_flash_mtimer )
       {
         
         Fx[flash_on-TOTAL_NO_SPRITES].alpha = 1.0;
       
         flash_on = -1;
              
       } 
     }        
     
            
     }  
       
     if(game_mode == WALK)  
     if((int)TimerGetTime() > crouch_timer) 
         crouch_timer = (int)TimerGetTime() + 50;  
                
     if(game_mode == WALK)
     if((int)TimerGetTime() > range_timer) 
         range_timer = (int)TimerGetTime() + 250; 
         
     if((int)TimerGetTime() > follow_timer)         
         follow_timer = (int)TimerGetTime()+750;   
      
     if((int)TimerGetTime() > sprite_to_fx_timer)
	 {
         sprite_to_fx_timer = (int)TimerGetTime()+75;  
	 }
         
     if(game_mode == WALK)       
     if((int)TimerGetTime() > check_timer) 
     { 
         check_timer = (int)TimerGetTime() + 500;
              
         if(alert_enemies == false)  
         {     
             noise_maker = NO_NOISE;          
             alert_guy = -1;
         }
     }                        
     
}                      

void Get_Target(int loop) 
{
}
void Hud_Signal(float value)
{
}

int Navigate_Point(int loop, bool hunting)
{
	return 0;
}

int Get_Closest_Node(int loop)
{
	return 0;
}

void Alert_Buddies(int loop, float range)
{
} 

int Search_area(int guy, int target, bool on_mesh)
{
	return 0;
}

// ******************************************************************************//
//                              Enemy AI                                         //                     
// ******************************************************************************//
void Check_EMY_State(int loop)
{ 
}

void Moving_Code(int loop, float x_pos, float y_pos, int f_rate)
{
    float deltax=0.0f, deltay=0.0f;
    float angle=0.0f; 
    float mid_x=0.0f;    
    float mid_y=0.0f;
    float tar_x=0.0f;
    float tar_y=0.0f;
    float ratio=0.0f;
    float distance=0.0f;
    float distance_from_target=0.20f;
    int temp_row_x=0; 
    int temp_row_y=0;   
    int index=0; 
    int temp_row_x1=0;  
    int temp_row_y1=0;        
    int index1=0;     
    float temp_speed = (float)gunner_spd;   
    int collision_returned=0;   
    int test_wood=0, test_food=0;
    int old_index=0;     
    bool add_distance = false;  
    bool skip_this = false;
    bool guy_on_ladder=false;     
    int total_score=1;
	int stored_col=0;       

	if(f_rate <= 0)     
	    f_rate = 1; 

	if(f_rate > 100)
	    f_rate = 100; 
    
	if(loop >= 0)
	{ 

	if(sprite[loop].linked_sprite == player_type)
		sprite[loop].return_fire = false;
	 
    if(sprite[loop].sector == UNIT_DOG) 
        temp_speed = (float)dog_spd;
    if(sprite[loop].sector == UNIT_GUNNER) 
        temp_speed = (float)gunner_spd; 
    if(sprite[loop].sector == UNIT_CHIEF) 
        temp_speed = (float)gunner_spd; 
    if(sprite[loop].sector == UNIT_HEAVY)
        temp_speed = (float)gunner_spd;
    if(sprite[loop].sector == UNIT_SNIPER)
        temp_speed = (float)gunner_spd;
    if(sprite[loop].sector == UNIT_MORTAR)
        temp_speed = (float)gunner_spd;
                      
    if(ply_id != -1)            
    if(loop == ply_id) 
	if(player_in_water == false) 
        temp_speed = (float)gunner_spd;
	else
	{     
		temp_speed = (float)gunner_spd;
	} 
                
    sprite[loop].update = true;     

    mid_x = sprite[loop].w+sprite[loop].box_width/2; 
    mid_y = sprite[loop].z+sprite[loop].box_height/2; 
        
    tar_x = sprite[loop].end_x; 
    tar_y = sprite[loop].end_y;  
     
//    if(loop == ply_id)  
//   { 
             
        distance = Node_Distance1(mid_x, mid_y, tar_x, tar_y);
		 
        if(distance > 0.9f)        
            sprite[loop].factor = 0.50f;            
        if(distance > 0.8f)        
            sprite[loop].factor = 0.55f;        
        if(distance > 0.7f)        
            sprite[loop].factor = 0.58f;          
        if(distance > 0.6f && distance <= 0.7f)   
            sprite[loop].factor = 0.60f;   
        if(distance > 0.5f && distance <= 0.6f)
            sprite[loop].factor = 0.62f;                      
        if(distance > 0.4f && distance <= 0.5f)  
            sprite[loop].factor = 0.65f; 
        if(distance > 0.3f && distance <= 0.4f) 
            sprite[loop].factor = 0.68f;               
        if(distance > 0.2f && distance <= 0.3f)
            sprite[loop].factor = 0.70f;            
        if(distance > 0.15f && distance <= 0.2f)
            sprite[loop].factor = 0.75f;            
        if(distance > 0.1f && distance <= 0.15f)
            sprite[loop].factor = 0.9f; 
        if(distance > 0.05f && distance <= 0.1f)
            sprite[loop].factor = 1.00f;
        if(distance <= 0.05f)  
            sprite[loop].factor = 1.10f; 
     
        if(ply_id != -1)            
        if(loop == ply_id)
            total_score = 20;    
        else  
            total_score = 20;
     
		if(sta2_environment_type != AREA_GRASSLANDS && sta2_environment_type != AREA_SWAMP)
        if(sprite[loop].on_mud == true)
            sprite[loop].factor += 0.40f; 
		 
		if(sta2_environment_type == AREA_SWAMP )
        if(sprite[loop].on_mud == true)
            sprite[loop].factor += 0.15f; 
                    
        if(sprite[loop].factor < 0.02f) 
            sprite[loop].factor = 0.02f;    
            
        if(sprite[loop].factor > 1.4f)
            sprite[loop].factor = 1.4f;    
                        
        if(sprite[loop].factor > 0.0f)
            temp_speed /= sprite[loop].factor;
                          
        if(temp_speed > 0.00075f)  
            temp_speed = 0.00075f;  
                     
        if(temp_speed < 0.0001f)       
            temp_speed = 0.0001f;   
 
        if(loop == ply_id)
        {      
            if(ply_accel > temp_speed)
                ply_accel = temp_speed;
                
            temp_speed = ply_accel; 
              
            if(temp_speed < 0.00020f)
                sprite[loop].factor = 0.9f; 
                
            if(temp_speed < 0.00010f)                
                sprite[loop].factor = 1.10f;
        }      
                          
                                     
    temp_row_x = (int)((mid_x + map_startX)*10);        
    temp_row_y = (int)((mid_y + map_startY)*10);  
     
    index = (temp_row_y*MAP_HEIGHT)+temp_row_x;         
	
	if(index < 0)
		index = 0;

    map_col[index] = 0;     
    
    old_index = index;   
	 
    angle = atan2(y_pos - (sprite[loop].z+sprite[loop].box_height/2),x_pos - (sprite[loop].w+sprite[loop].box_width/2));
     
    deltax = cos(angle); // Was 1.2    
    deltay = sin(angle); // Was 1.2
        
    deltax *= temp_speed;      
       
    if(ply_id != -1)   
    if(loop == ply_id && sta2_turn == TURN_PLAYER)  
	{
		if(screen_mode == SCREEN_169_WIDESCREEN)   // 16:9
			deltay *= temp_speed*0.73f;   
		if(screen_mode == SCREEN_1610_WIDESCREEN) // 16:10
			deltay *= temp_speed*0.74f;    
		if(screen_mode == SCREEN_WIDESCREEN)       // 5:3
			deltay *= temp_speed*0.73f;   
		if(screen_mode == SCREEN_NORMAL)           // 4:3
			deltay *= temp_speed*0.73f;   
	}
    else 
        deltay *= temp_speed;  
    
    deltax *= (float)f_rate; 
    deltay *= (float)f_rate;    

    collision_returned = Test_Collision(sprite[loop], deltax, 0.0f, false, loop, false );
        
    if(guy_on_ladder == false)                  
    if(collision_returned == ROUTE_GO)           
    {
           
        sprite[loop].x += deltax;      
        sprite[loop].w += deltax;   

		if(loop == ply_id || loop == emy_id)        
		if(deltax < 0)
			sta2_distance_traveled -= deltax;
		else
			sta2_distance_traveled += deltax; 
                 
    } 
	    
    if(guy_on_ladder == false)    
    if(collision_returned == ROUTE_BLOCKED)       
    {
		     
		ShotIdle(loop);

		if(sta2_turn == TURN_COMPUTER) 
		if(emy_id != -1)  
		if(loop == emy_id)
		if(!(Find_Path(loop, sprite[loop].end_x, sprite[loop].end_y)))
		{
			sta2_enemy_mode = MOVE_END;
			sta2_timer = (int)TimerGetTime() + 2000;
		}    
			  
    }       

    collision_returned = Test_Collision(sprite[loop], 0.0f, deltay, false, loop, false );
         
    if(collision_returned == ROUTE_GO)   
    {  
              
        sprite[loop].y += deltay;      
        sprite[loop].z += deltay;  
 
		if(loop == ply_id || loop == emy_id)   
		if(deltay < 0)
			sta2_distance_traveled -= deltay;
		else
			sta2_distance_traveled += deltay; 

    }   
 
    if(collision_returned == ROUTE_BLOCKED)   
    {  
		ShotIdle(loop); 

		if(sta2_turn == TURN_COMPUTER) 
		if(emy_id != -1) 
		if(loop == emy_id)
		if(!(Find_Path(loop, sprite[loop].end_x, sprite[loop].end_y)))
		{
			sta2_enemy_mode = MOVE_END;
			sta2_timer = (int)TimerGetTime() + 2000;
		}         
			 
    }
     
    distance_from_target = 0.01f;  // was 0.0030f
    
    mid_x = sprite[loop].w+sprite[loop].box_width/2; 
    mid_y = sprite[loop].z+sprite[loop].box_height/2;        
    
    if( mid_x < (sprite[loop].end_x + distance_from_target)
    && mid_x > (sprite[loop].end_x - distance_from_target)     
    && mid_y < (sprite[loop].end_y + distance_from_target)     
    && mid_y > (sprite[loop].end_y - distance_from_target)) 
    {  
                                            
        sprite[loop].moving = false;            

		if(sta2_turn == TURN_COMPUTER) 
		if(emy_id != -1) 
		if(loop == emy_id)
		{
			sta2_enemy_mode = MOVE_END;
			sta2_timer = (int)TimerGetTime() + 2000;
		}
		  
        ShotIdle(loop);  
 
    }      
      
    if(sprite[loop].moving == true)               
    if( mid_x < (sprite[loop].mov_x + 0.01f) // was 0.010f
    && mid_x > (sprite[loop].mov_x - 0.01f)  // was 0.010f       
    && mid_y < (sprite[loop].mov_y + 0.01f)  // was 0.010f   
    && mid_y > (sprite[loop].mov_y - 0.01f)) // was 0.010f 
    {     
        
        if(sprite[loop].node_count != -1)    
        { 
			 
          if(sprite[loop].node_counter >= sprite[loop].node_count-1)
          {
		   	  ShotIdle(loop); 		   

              if(!(Find_Path(loop, sprite[loop].end_x, sprite[loop].end_y)))
			  if(sta2_turn == TURN_COMPUTER) 
			  if(emy_id != -1)  
			  if(loop == emy_id)
			  {
			  	  sta2_enemy_mode = MOVE_END;
				  sta2_timer = (int)TimerGetTime() + 2000;
			  }
          } 
          else      
          { 
              Next_node(loop, true);       
          } 
           
        }       
		else 
		{
		    ShotIdle(loop);	       

			if(sta2_turn == TURN_COMPUTER) 
			if(emy_id != -1)  
			if(loop == emy_id)
			{
			  	sta2_enemy_mode = MOVE_END;
				sta2_timer = (int)TimerGetTime() + 2000;
			}
		}
    }                
    
    mid_x = sprite[loop].w+sprite[loop].box_width/2; 
    mid_y = sprite[loop].z+sprite[loop].box_height/2;     
               
    temp_row_x = (int)((mid_x + map_startX)*10);        
    temp_row_y = (int)((mid_y + map_startY)*10);  
     
    index = (temp_row_y*MAP_HEIGHT)+temp_row_x;      
    
    // Run a pickup check if player is heading for one..
    if(ply_id != -1)
    if(ply_pickup_target != -1 && loop == ply_id) 
    if(Fx[ply_pickup_target].turn_off == false)
	if(mouseleft == true)
    {
        Pickup_Check(ply_id, ply_pickup_target, RUN_AND_COLLECT);
    }    

	if(old_index >= 0)
		map_col[old_index] = 0; 
      
    if(old_index >= 0)             
    if(tiles[old_index]>=480 && tiles[old_index] < 484 ) // Water...
        map_col[old_index] = 9;   
 
    if(index >= 0)
    if( loop != p1_buddy )         
        map_col[index] = 6;     
	 
	if(ply_id != -1)
	if(loop == ply_id)
	if(STA2_MODE == MODE_MOVING)   
	{
		Set_Camera( f_rate, false );       
	}

	} // loop >= 0
	  
                                                  
}
void Shoot_Test(int loop, int f_rate)   
{
    
    float dis_to_point=0.0f; 
    float midX =0.0f, midY =0.0f;
    float tarX =0.0f, tarY =0.0f;
    int best_point = -1;
    float closest_point = 0.0f;
    float angle_to_move=0.0f;
    float angle_to_target=0.0f;  
    float angle1=0.0,angle2=0.0f;
    float deltax=0.0, deltay = 0.0f;  
    int old_direction=0;   
    int new_direction=0;  
    bool skip_this=false;
    int the_count=0;
    bool object_attack_on = false;
    int player_clip = 0; 
    int addition=0; 
    int tens = 0;
    int zeros = 0;  
	int temp_target=0;
    bool rnd_sniper=false;
	bool animal_attack = false; 
	bool throwing_grenade = false;   

		if(f_rate <= 0)         
			f_rate = 1;     
              
		if(loop < 0)    
			return;

		if(sprite[loop].linked_sprite == player_type) // I'm a player unit...     
		{

			if(sta2_turn == TURN_COMPUTER && sta2_enemy_mode != MOVE_MOVE) // Don't shoot guy when he's taking a shot...
				return; 
			 
			if(emy_id != -1)
				temp_target = emy_id;    
			else 
				return; 
		}
		if(sprite[loop].linked_sprite != player_type) // I'm an enemy unit... 
		{

			if(sta2_turn == TURN_PLAYER && STA2_MODE == MODE_AIMING || STA2_MODE == MODE_TARGET) // Don't shoot guy when he's taking a shot...
				return; 

			if(sta2_turn == TURN_PLAYER && (sprite[loop].sector == UNIT_MORTAR || sprite[loop].sector == UNIT_SNIPER) ) // Mortars and snipers have no defend...
				return; 

			if(sta2_turn == TURN_COMPUTER && loop != emy_id)
				return;
			  
			if(ply_id != -1) 
			if(sta2_turn == TURN_PLAYER)
			if(sprite[ply_id].moving == true)
				temp_target = ply_id; 
			else
				return;

		}   

		if(emy_id != -1 && the_target != -1)
		if(sprite[loop].linked_sprite != player_type) // I'm an enemy unit... 
		if(loop == emy_id && sta2_turn == TURN_COMPUTER) // I'm the currently active unit...
			temp_target = the_target;  

		if(loop >= 0)    
		{     
			 
			midX = sprite[loop].w+sprite[loop].box_width/2;
			midY = sprite[loop].z+sprite[loop].box_height/2;

			if(loop == emy_id && sta2_turn == TURN_COMPUTER)
			{
				if(sprite[loop].sector == UNIT_SNIPER || sprite[loop].sector == UNIT_MORTAR)
					closest_point = (float)2.6f;                     
				else
					closest_point = (float)gunner_rng*2.0f;  

				if(sprite[loop].sector == UNIT_DOG)
					closest_point = (float)0.2f; 
			}
			else 
			{ 
				if(sta2_turn == TURN_COMPUTER)
					closest_point = (float)gunner_rng*2.6f;                    
				else
					closest_point = (float)gunner_rng*1.45f; 

				if(sprite[loop].sector == UNIT_DOG)
					closest_point = (float)0.2f; 
			}
         
		}       

        if(loop != -1)     
		if(temp_target != -1)   
        if(sprite[temp_target].type == UNT)   
        if(sprite[temp_target].linked_sprite != sprite[loop].linked_sprite )  
        if(sprite[temp_target].score > 1 || sprite[temp_target].linked_sprite != player_type) 
		if(sprite[temp_target].camo == false || sprite[loop].sector == UNIT_DOG)
        if(sprite[temp_target].turn_off == false)    
        {                  
       
            tarX = sprite[temp_target].w + sprite[temp_target].box_width/2; 
            tarY = sprite[temp_target].z + sprite[temp_target].box_height/2;    
			 
         /*   throwing_grenade = false; 
 
            if(sprite[loop].sector == UNIT_GUNNER) 
		    if( (int)TimerGetTime() > sprite[loop].heal_timer) 
            if(sprite[loop].linked_sprite != player_type) 
            {  
			
               if(rand()%30 == 4)  
			   if(Node_Distance1(midX, midY, tarX, tarY) <= 0.8f)       	
			   {	                           
                //   Throw_Grenade(loop, index);  
				//   throwing_grenade = true;
				//   sprite[loop].heal_timer = (int)TimerGetTime() + 4000;	
			   }	       
            }       */ 
             
            angle_to_target = atan2(tarY - midY,tarX - midX);   
                          
            dis_to_point = Node_Distance1(midX, midY, tarX, tarY);      
            
			// Getting a target
			if(throwing_grenade == false)
            if( dis_to_point < closest_point)          
            if(Shoot_Ray(loop, midX, midY, tarX, tarY, false, true, 0.01f) == false
            ||  dis_to_point < KNIFE_RANGE )           
            {      

               if(Is_Guy_In_Sight(sprite[loop].angle, angle_to_target) > 0) 
               {        
					closest_point = dis_to_point;  
					best_point = temp_target;        
               }
                  
            }      
                 
      //      } 
  
      sprite[loop].turning = false; 
                                  
      if(best_point != -1) // An enemy is within shooting range!
      {    

            tarX = sprite[best_point].w+sprite[best_point].box_width/2;   
            tarY = sprite[best_point].z+sprite[best_point].box_height/2;

			ShotIdle(loop);      

            sprite[loop].turning = true;                         
                                                   
            Set_Heading(loop, tarX, tarY, false);   

			if(emy_id != -1)
			if(sta2_turn == TURN_COMPUTER) 
			if(loop == emy_id)
			{  
				switch(sta2_enemy_mode) 
				{ 
					case MOVE_MOVE: 
						 
						spark_sfx = true;
						sta2_enemy_mode = MOVE_AIM;  
						sta2_timer = (int)TimerGetTime() + 500;

						sprite[emy_id].status = AIMING;
						sprite[emy_id].anim_state = WAIT; 
						sprite[emy_id].update = true;

						sprite[emy_id].all_timer = (int)TimerGetTime() + 8000;
						 
					break;
					  
					case MOVE_AIM:  

						sta2_enemy_mode = MOVE_FOCUS;
						sta2_timer = (int)TimerGetTime() + 750;

					break;    
					 
					case MOVE_FOCUS:  

						sta2_enemy_mode = MOVE_SHOOT;
						sta2_timer = (int)TimerGetTime() + 750;

						sprite[loop].angle = sprite[loop].tar_angle;
						  
					break;    
					 
				}  
			      
			}    
                  
            old_direction = Convert_Angle_To_Dir(sprite[loop].angle); 
                       
            new_direction = Convert_Angle_To_Dir(sprite[loop].tar_angle);       

			if( (sta2_enemy_mode != MOVE_MOVE && sta2_enemy_mode != MOVE_AIM && sta2_enemy_mode != MOVE_FOCUS) || best_point == emy_id)
            if(old_direction == new_direction)   
            {   
				if(sprite[loop].linked_sprite == player_type)  
				{
					sta2_only_pistol = false;
					sta2_only_grenade = false;
				}

                TestSpriteToShoot(loop, midX, midY, tarX, tarY, false, best_point, f_rate); 

                sprite[loop].turning = false;   
              
            }         

      }    


	} // sprite[index].type == UNT
  
}                                       

void Reduce_Fog(float mid_x, float mid_y, int unit)
{
     
    int row_x=0;  
    int row_y=0;  
    int the_row=0;
    float vision=0;
    int temp=0;      
    float dis_to_point=0.0f;
    float tarX=0.0f, tarY=0.0f; 
    int width = 0;
    int player_id=0;
    float ply_x=0.0f, ply_y=0.0f;
    int stored_col=0;
    int stored_col1=0;
    
    memset( blackness, SOLID, sizeof(blackness) );
           
    row_x = (int)((mid_x + map_startX)*10);    
    row_y = (int)((mid_y + map_startY)*10);   
    
    the_row = (row_y*MAP_HEIGHT)+row_x;
    
//    stored_col1 = map_col[the_row];
    
//    map_col[the_row] = 0; 
    
    vision = PLAYER_VISION; 
    
    width = (int)(vision*12);           
    
    if(ply_id != -1 && player_type == p_server) 
        player_id = ply_id;
            
    for(int j=row_y-width;j<=row_y+width;j++)
    for(int i=row_x-width;i<=row_x+width;i++)
    { 
            
        temp = (j*MAP_HEIGHT)+i;                         
        
        mid_x = -map_startX + (( (float)row_x*(0.1f)+0.05f) );
        mid_y = -map_startY + (( (float)row_y*(0.1f)+0.05f) ); 
                         
        tarX = -map_startX + (( (float)i*(0.1f)+0.05f) );
        tarY = -map_startY + (( (float)j*(0.1f)+0.05f) ); 
                           
        dis_to_point = Node_Distance(mid_x, mid_y, tarX, tarY); 
          
  //      if(dis_to_point < (vision/1.5) )      
  //      if( temp >= 0 && temp < MAP_TILES)       
  //      { 
            if(temp >= 0)
	            blackness[temp]=BLANK;
                   
  //      } 
            
    }
     
//    map_col[the_row] = stored_col1;

}

bool Test_Visible(float mid_x, float mid_y)
{ 
      
    bool success=false; 
    
    // Disabled the fog so don't need for now
    int fog_row_x=0;    
    int fog_row_y=0;
    int index=0;    
             
    fog_row_x = (int)((mid_x + map_startX)*10);     
    fog_row_y = (int)((mid_y + map_startY)*10);  
    
    index = (fog_row_y*MAP_HEIGHT)+fog_row_x; 
    
    if(index >= 0 && index < MAP_TILES)      
    if(blackness[index]==BLANK) 
        success=true; 
        
//    success = true;
    
    return(success);      
}
 
void Bomb_Run(float bomb_tar_x, float bomb_tar_y, int the_guy, int f_rate)  
{
    float bomb_x =0.0f, bomb_y=0.0f; 
 
	if(f_rate <= 0)
	    f_rate = 1; 
    
    // Ground bomb or air bomb?
//    New_FX(bomb_tar_x-0.2f, bomb_tar_y-0.2f, bomb_tar_x, bomb_tar_y, 0, PLAY, 0.1f, 0.1f, 0.4f, 0.6f, 1, GFX, 1.0f, 0, 0, FX_STATIC, -1, 7, 0, 0);
    
    Shell_Landed(bomb_tar_x, bomb_tar_y, the_guy, f_rate, -1, -1);
    
      
} 

void Shell_Landed( float x, float y, int shooter, int f_rate, int type, int my_value) // A shell hit one of my men
{
    
                    
    int loop = 0; 
    bool hit_a_building = false; 
    float range=SHELL_RANGE;
    float tar_range=0.0f; 
    float test_range=0.0f;
    float mid_x = 0.0f, mid_y=0.0f;  
    float tar_x = 0.0f, tar_y=0.0f;
    float deltax=0.0f, deltay=0.0f;
    int rnd=0;

	if(f_rate <= 0) 
	    f_rate = 1; 
        
    if(type == INV_BOSS_SHELL)   
        range = (float)BOSS_SHELL_RANGE;
        
    if(type == INV_BARREL_BOMB)    
        range = (float)BARREL_BOMB_RANGE; 
             
    if(type == INV_BOSS_BOMB)     
        range = (float)BOSS_BOMB_RANGE;
    
    if(type == INV_ARTILLERY) 
        range = (float)ARTILLERY_BOMB_RANGE;
        
    if(type == INV_GRENADE)       
        range = (float)GRENADES_RANGE;
        
    if(type == INV_MORTAR)       
        range = (float)GRENADES_RANGE;
                     
    if(type != INV_GRENADE && type != INV_BOSS_BOMB && type != INV_MORTAR)
    {        
		Surround_Sound(-1, SFX_BOMB, x, y); 
    }
    else
    {
		Surround_Sound(-1, SFX_GRENADE, x, y); // Grenade sfx
    }
    
    alert_enemies = true;  
    noise_type = LOUD_NOISE;                 
  
    noise_x = x;                        
    noise_y = y;   
	
	if(shooter != -1)
	    alert_guy = shooter;
               
    if(shooter != -1)  
    if(type == INV_SHOTGUN) 
    {
             
        mid_x = sprite[shooter].w+sprite[shooter].box_width/2; 
        mid_y = sprite[shooter].z+sprite[shooter].box_height/2; 
        
        range = Node_Distance(x, y, mid_x, mid_y)/3.5f;   
              
        if(ply_id != -1) 
        if(shooter == ply_id)  
        if( has_shotgun_equipped == true)
        if( has_wideshot == true )
            range = Node_Distance(x, y, mid_x, mid_y)/2.5f;         
    
    }
	
	// Blow-up any grenades...
	if(CHAIN_GRENADES == 1)
    for(int i=0;i<no_fx;i++)      
    {    
 
        if(Fx[i].sector == FX_GRENADE) 
		if(Fx[i].grab_switch == true)                                                                                                   
        if(Fx[i].turn_off == false)
		{
              
     	    mid_x = Fx[i].w+Fx[i].box_width/2; 
     	    mid_y = Fx[i].z+Fx[i].box_height/2; 

			range = Node_Distance(x, y, mid_x, mid_y);
			
			if(range <= 0.35f)
			{
			    Fx[i].action_timer = 0;
			}

		}

	}
   
    for(int i=0;i<player_counter;i++)      
    {   
        
        loop = player_list[i];  

        test_range = range; 

		if(loop >= 0)
        if(sprite[loop].type == UNT) 
        if(type == INV_GRENADE || type == INV_MORTAR)
        if(sprite[loop].score > 0)
        if(sprite[loop].status != MAN_DOWN && sprite[loop].status != MAN_DOWN1)
        if(sprite[loop].status != DEATH_READY) 
        if(sprite[loop].status != FALLING && sprite[loop].status != LEVELING)
        if(sprite[loop].grab_switch == true) 
        if( ( x < (sprite[loop].w + sprite[loop].box_width/2) + test_range)
        &&( x > (sprite[loop].w + sprite[loop].box_width/2) - test_range)                              
        &&( y < (sprite[loop].z + sprite[loop].box_height/2) + test_range) 
        &&( y > (sprite[loop].z + sprite[loop].box_height/2) - test_range))
        {   
            
            tar_x = sprite[loop].w+sprite[loop].box_width/2; 
            tar_y = sprite[loop].z+sprite[loop].box_height/2;   
        
            tar_range = Node_Distance(tar_x, tar_y, mid_x, mid_y);  

            if(type == INV_GRENADE)   
            {   
				Man_Shot(UNIT_GRENADE, loop, shooter, my_value, f_rate);
            }    

            if(type == INV_MORTAR)   
            {   
	            Man_Shot(UNIT_MORTAR, loop, shooter, my_value, f_rate);
            }               
          
            if(type == INV_SHOTGUN)   
            {
                if(tar_range <= 0.35f)                 
                    Man_Shot(-1, loop, shooter, BULLET_SHOTGUN, f_rate); 
                else
                    Man_Shot(-1, loop, shooter, BULLET_SHOTGUN_LONG, f_rate);
                                           
            }  

        }
         
    }              
    
    if(type != INV_SHOTGUN)     
    { 
		   
        if(type == INV_ARTILLERY) 
		{
            New_FX(x-0.11f, y-0.03f, x, y, 8, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 2, GFX, 1.0f, 0, 0, FX_EXPLOSION, -1, 2, 0, 0, -1); // Explosion
        //    New_FX(x-0.2f, y-0.05f, x, y, 113, PLAY, 0.1f, 0.1f, 0.4f, 0.6f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1); // Explosion
		}
        else    
		{
            New_FX(x-0.11f, y-0.03f, x, y, 8, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 2, GFX, 1.0f, 0, 0, FX_EXPLOSION, -1, 2, 0, 0, -1); // Explosion
        //    New_FX(x-0.2f, y-0.05f, x, y, 113, PLAY, 0.1f, 0.1f, 0.4f, 0.6f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1); // Explosion
		}
            
  //      New_FX(x-0.2f, y-0.2f, x, y, 86, PLAY, 0.1f, 0.1f, 0.4f, 0.6f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1); // POW
        
		if(no_points >= 0)
		{
	        points[no_points].x = x;  
	        points[no_points].y = y;   
	        points[no_points].c1 = LIGHT_PNT;
	        points[no_points].score = (int)TimerGetTime() + 250;
	        points[no_points].c4 = LIGHT_OPEN_FIRE; 
	        no_points++;
		}
        
        if( x > -(camX + 1.0f) && x < -(camX - 1.0f))
        if( y > -(camY + 1.0f) && y < -(camY - 1.0f))
            Camera_Shake(THUD_SHAKE);
    }
    
}
bool Dig_Check(float x, float y, int man_to_check) 
{
      bool cant_dig_here=false;
      int row_x=0; 
      int row_y=0; 
      int the_row=0;  
      
      // Level Editor stuff                          
      row_x = (int)((x + map_startX)*10);
      row_y = (int)((y + map_startY)*10); 
      
      the_row = (row_y*MAP_HEIGHT) + row_x;
            
      cant_dig_here = false; 
             
      // Check you can dig here first
      for(int j=-1;j<2;j++)                         
      for(int i=-1;i<2;i++) 
      {
        if(((row_y+j)*MAP_HEIGHT)+(row_x+i) >= 0 && ((row_y+j)*MAP_HEIGHT)+(row_x+i) < MAP_TILES)       
        if(tiles[ ((row_y+j)*MAP_HEIGHT)+(row_x+i)] >= 16)
          cant_dig_here = true;        
      }
      
      // Check for men in the hole
      if(Check_hole(man_to_check, the_row)==true)
          cant_dig_here = true;   
      
      return(cant_dig_here);
     
}
bool Slash_Check(float x, float y, int man_to_check)
{
      bool cant_dig_here=true;
      int row_x=0; 
      int row_y=0; 
      int the_row=0;  
      
      // Level Editor stuff                          
      row_x = (int)((x + map_startX)*10);
      row_y = (int)((y + map_startY)*10); 
      
      the_row = (row_y*MAP_HEIGHT) + row_x;

      if( the_row >= 0 && the_row < MAP_TILES)
      {       
        if(tiles[ the_row] >= 48 && tiles[the_row] < 64)
          cant_dig_here = false;       
        if(tiles[ the_row] >= 192 && tiles[the_row] < 208)
          cant_dig_here = false;   
      }
      return(cant_dig_here);     
     
}
void Dig_Hole(int loop, float x, float y)
{
      bool cant_dig_here=false;
      int row_x=0; 
      int row_y=0;   
      
      // Level Editor stuff                          
      row_x = (int)((x + map_startX)*10);
      row_y = (int)((y + map_startY)*10);  
              
      cant_dig_here = false;
             
      // Check you can dig here first
      for(int j=-1;j<2;j++)                         
      for(int i=-1;i<2;i++)
      if(((row_y+j)*MAP_HEIGHT)+(row_x+i) >= 0 && ((row_y+j)*MAP_HEIGHT)+(row_x+i) < MAP_TILES)        
      if(tiles[ ((row_y+j)*MAP_HEIGHT)+(row_x+i)] >= 16)
          cant_dig_here = true;  
                     
      if(cant_dig_here == false)   
      {   
           if( (row_y*MAP_HEIGHT)+row_x >= 0 && (row_y*MAP_HEIGHT)+row_x < MAP_TILES)  
               tiles[(row_y*MAP_HEIGHT)+row_x]=32;   
               
           for(int j=-1;j<2;j++)                          
           for(int i=-1;i<2;i++)
             Calculate_Edges( ((row_y+j)*MAP_HEIGHT)+(row_x+i), 32); 
             
     /*      if( lan_game == true)
           {  
               ping_hole_x[ping_hole_count]=row_x;
               ping_hole_y[ping_hole_count]=row_y;
                     
               ping_hole_count++;      
               
               if(ping_hole_count >= 40)
                   ping_hole_count=0;
                   
           } */
             
      }   
     
}

bool Check_hole(int loop, int index)  
{
	 
     return 0; 
}  

void Rank_Timer(int index, int status)            
{
	 
	if(index >= 0)           
	{ 
  
    if(status == OPEN_FIRE) // sprite[index].sector == UNIT_GUNNER && 
    {    
         
         sprite[index].all_timer = (int)TimerGetTime() + 150;                      
             
         sprite[index].reload_timer = (int)TimerGetTime() + 1200; // 1000                                             
         sprite[index].all_timer += 170;  
              
		 if(index == ply_id && sta2_turn == TURN_PLAYER) 
			sprite[index].reload_timer = (int)TimerGetTime() + 200; // 1000 
		 else
		 {
			 if(sprite[index].sector == UNIT_HEAVY)
				sprite[index].reload_timer = (int)TimerGetTime() + 300; // 1000 
		 }

    }     
    
/*    if(ply_id != -1)     
    if(index == ply_id && sta2_turn == TURN_PLAYER)               
    if(status == OPEN_FIRE)         
    {         
    //     sprite[index].all_timer = (int)TimerGetTime() + 2000;    
         sprite[index].all_timer = (int)TimerGetTime() + 150; 
     
         sprite[index].reload_timer = (int)TimerGetTime() + GUN_FIRERATE;  
         
         start_healing = false;                                             
    }     */
     
    if(ply_id != -1)     
    if(index == ply_id)       
    if(status == OPEN_CUT)    
    {         
         sprite[index].all_timer = (int)TimerGetTime() + 200;  
         sprite[index].reload_timer = (int)TimerGetTime() + 250; 
         start_healing = false;                                              
    }          
    if(ply_id != -1)    
    if(index == ply_id)       
    if(status == OPEN_STAMP || status == OPEN_THROW)      
    {          
         sprite[index].all_timer = (int)TimerGetTime() + 200;   

		 if(has_green_grenade_equipped == true)  
	         sprite[index].reload_timer = (int)TimerGetTime() + 500; 
		 if(has_black_grenade_equipped == true)
	         sprite[index].reload_timer = (int)TimerGetTime() + 500; 
		 if(has_molotov_grenade_equipped == true)
	         sprite[index].reload_timer = (int)TimerGetTime() + 500; 
 
         start_healing = false;                                              
    }      
    if(ply_id != -1)
    if(index != ply_id)        
    if(status == OPEN_THROW)     
    {         
         sprite[index].all_timer = (int)TimerGetTime() + 100;  
         sprite[index].reload_timer = (int)TimerGetTime() + 500;                                               
    }   

    if(ply_id != -1)   
    if(index == ply_id) 
    if(status == STUNNED)   
    {  
        sprite[index].all_timer = (int)TimerGetTime() + 400; 
        start_healing = false;                   
    }     
        
    if(index != ply_id)        
    if(status == STUNNED)   
    {    
        sprite[index].all_timer = (int)TimerGetTime() + 600;                    
    }     
        
    if(index != ply_id)       
    if(status == FOOT_SHOT)      
    {  
        sprite[index].all_timer = (int)TimerGetTime() + 2750;                    
    }  
    
    if(index != ply_id)        
    if(status == FOOT_SHOT)  
	if(Level == LVL_TANK_BOSS)     
    {  
        sprite[index].all_timer = (int)TimerGetTime() + 1000;                    
    }      
      
    if(index == ply_id)    
    if(status == FOOT_SHOT)      
    {  
        sprite[index].all_timer = (int)TimerGetTime() + 1000;                    
    }   
            
    if(index != ply_id)         
    if(status == AIMING)        
    {
        if(sprite[index].sector != UNIT_SHOTGUN      
        && sprite[index].sector != UNIT_BOMBER 
        && sprite[index].sector != UNIT_MACHINE    
        && sprite[index].sector != UNIT_GUARD 
        && sprite[index].sector != UNIT_MORTAR1)
            sprite[index].all_timer = (int)TimerGetTime() + 300; // 1000                    
        
        if(sprite[index].sector == UNIT_SHOTGUN) 
            sprite[index].all_timer = (int)TimerGetTime() + 1000; // 2000
        
        if(sprite[index].sector == UNIT_BOMBER) 
            sprite[index].all_timer = (int)TimerGetTime() + 1500;  
              
        if(sprite[index].sector == UNIT_MORTAR1)
            sprite[index].all_timer = (int)TimerGetTime() + 4000;    
             
        if(sprite[index].sector_action == AI_BUDDY )                              
            sprite[index].all_timer = (int)TimerGetTime() + 750;
        
        if(sprite[index].sector == UNIT_MACHINE)
            sprite[index].all_timer = (int)TimerGetTime() + 25;   
        
        if(sprite[index].sector == UNIT_GUARD)
            sprite[index].all_timer = (int)TimerGetTime() + 25;                        
                  
    }    
       
    if(index == ply_id)      
    if(status == AIM_CROUCH || status == AIMING) 
    {    
		  
		if(CONTROLLER) 
		{
			if(CONTROLLER && on_selected_man != BAD_MAN)
		        sprite[index].all_timer = (int)TimerGetTime() + 150; // 1500                    
			else
		        sprite[index].all_timer = (int)TimerGetTime() + 1000; // 1500                    
		}
		else
	        sprite[index].all_timer = (int)TimerGetTime() + 1500; // 1500                    

    }    

	} // index >= 0
                 
}

void Play_Footstep(int loop)
{

    float mid_x=0.0f;
    float mid_y=0.0f;
    int temp_row_x=0;
    int temp_row_y=0;
    int index=0;
    bool played=false;
    bool guy_in_water=false;
	bool guy_on_mud=false;
  
	if(loop >= 0)
	{

    mid_x = sprite[loop].w+sprite[loop].box_width/2; 
    mid_y = sprite[loop].z+sprite[loop].box_height/2;     
               
    temp_row_x = (int)((mid_x + map_startX)*10);        
    temp_row_y = (int)((mid_y + map_startY)*10);  
     
    index = (temp_row_y*MAP_HEIGHT)+temp_row_x;  

	if(index < 0)
		index = 0;
    
    if(ply_id != -1) 
    if(loop == ply_id)
    if(player_in_water == true)
        guy_in_water = true;
         
    if(p1_buddy != -1)    
    if(loop == p1_buddy) 
    if(buddy_in_water == true)
        guy_in_water = true;

 /*   if(tiles[index]==16 || tiles[index] == 29 || tiles[index] == 30 || tiles[index] == 31)   
	{
		Surround_Sound(loop, SFX_MUDSTEP, -1, -1);	
        played=true;
    	guy_on_mud=true;
	}*/
	if(sta2_environment_type == AREA_GRASSLANDS || sta2_environment_type == AREA_SNOW || sta2_environment_type == AREA_MOUNTAIN)
	{
        Surround_Sound(loop, SFX_GRASSSTEP, -1, -1);
        played=true;
	}
	if(sta2_environment_type == AREA_SWAMP) 
	{
		if(sprite[loop].on_mud == true)
			Surround_Sound(loop, SFX_MUDSTEP, -1, -1);
		else
			Surround_Sound(loop, SFX_GRASSSTEP, -1, -1);

        played=true;
	}

	if(played == false)
    if(guy_in_water == false)    
    if(guy_on_mud == false)
    {
        if(tiles[index]==416 || tiles[index]==417
        || tiles[index]==418 || tiles[index]==8 
        || tiles[index]==419 || tiles[index]==420
        || tiles[index]==9 || tiles[index] < 7)   
        { 
            Surround_Sound(loop, SFX_HARDSTEP, -1, -1);
            played=true;
        }    
        else 
        { 
            Surround_Sound(loop, SFX_GRASSSTEP, -1, -1);
            played=true;
        }                         
    } 

    if(guy_in_water == true)  
    {
        swim_sfx = true;
        played=true;
    } 
       
    if(played == false)
        Surround_Sound(loop, SFX_FOOTSTEP, -1, -1); 
     

	} // loop >= 0

}

void Medal_Check()
{

           
}

void Remove_From_List(int index)
{

	if(index >= 0)
	{

    sprite[index].flash_target = false;
    sprite[index].flash_timer  = 0;
    sprite[index].dflash_timer  = 0;
                                  
    for(int loop=index;loop<player_counter;loop++)
    {
        if( (loop+1) < 400)     
            player_list[loop] = player_list[loop+1];
    }   
                           
    if(player_counter > 0) 
        player_counter--;     

	}

} 

void Throw_Grenade(int index, int target) 
{
     
    float tar_x=0.0f, tar_y=0.0f;
    float x1=0.0f, y1=0.0f;
    float new_angle=0.0f;
    
	if(target >= 0)
	{
	    x1 = sprite[target].x+sprite[target].width/2;  
	    y1 = sprite[target].y+sprite[target].height/2; 
    }                   
	
	if(index >= 0)
	{	

    tar_x = sprite[index].x+sprite[index].width/2;  
    tar_y = sprite[index].y+sprite[index].height/2; 
    
    new_angle = atan2(y1 - tar_y,x1 - tar_x);   
       
    sprite[index].angle = new_angle; 
    sprite[index].tar_angle = new_angle;   
    
	if( Level != LVL_FARMS || ENEMIES_HAVE_MOLOTOVS == 0) 
	{                          
    	New_FX(tar_x, tar_y,  sprite[index].w, sprite[index].z, 31, LOOP, sprite[index].box_width, sprite[index].box_height, sprite[index].width, sprite[index].height, 0, GFX, 1.f, -1, BULLET_KNIFE_PLY, FX_GRENADE_SHADOW, index, 5, BLACK_GRENADE, 0, -1);
    	New_FX(tar_x, tar_y,  sprite[index].w, sprite[index].z, 0, LOOP, sprite[index].box_width, sprite[index].box_height, sprite[index].width, sprite[index].height, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_GRENADE, index, 5, BLACK_GRENADE, 0, -1);
	}
	if( Level == LVL_FARMS && ENEMIES_HAVE_MOLOTOVS == 1)
	{                          
    	New_FX(tar_x, tar_y,  sprite[index].w, sprite[index].z, 32, LOOP, sprite[index].box_width, sprite[index].box_height, sprite[index].width, sprite[index].height, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_GRENADE_SHADOW, index, 5, MOLOTOV_GRENADE, 0, -1);
    	New_FX(tar_x, tar_y,  sprite[index].w, sprite[index].z, 20, LOOP, sprite[index].box_width, sprite[index].box_height, sprite[index].width, sprite[index].height, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_GRENADE, index, 5, MOLOTOV_GRENADE, 0, -1);
	} 
                  
    chop_sfx = true; 
                   
    sprite[index].status = OPEN_THROW; 
    sprite[index].anim_state = WAIT;  
    sprite[index].update = true;    
                  
    Rank_Timer(index, sprite[index].status);

	}// index >= 0
     
}
     
void Special_Attack(int type)
{
    float tar_x=0.0f;
    float tar_y=0.0f;
    float offset_x=0.0f;
    float offset_y=0.0f;
    
    if(ply_id != -1)
    {
        tar_x = sprite[ply_id].x+sprite[ply_id].width/2;
        tar_y = sprite[ply_id].y+sprite[ply_id].height/2; 
    }
    
    // SPL_ARTILLERY_1
    if(type == SPL_ARTILLERY_1) 
    {
    
        if( (int)TimerGetTime() > special_attack_timer)
        {
            if(special_count == 0)
            {
                special_attack_timer = (int)TimerGetTime() + 500; 
                if(ply_id != -1)
                    Display_Message(ply_id, MSG_INCOMING);
                whistle_sfx = true;
            }
            else
            {
                special_attack_timer = (int)TimerGetTime() + 100; 
            }
            if(ply_id != -1)                        
            if(special_count >= 1)                                                                                                
                New_FX(tar_x, tar_y,  sprite[ply_id].w, sprite[ply_id].z, 37, LOOP, sprite[ply_id].width, sprite[ply_id].height, sprite[ply_id].box_width, sprite[ply_id].box_height, 4, GFX, 0.01f, 0, 0, FX_FALLING_BOMB, ply_id, 8, 0, 0, -1);      
             
            special_count++;
                       
        }
        
        if(special_count == 2)
        {
            ply_special_attack = -1;
            special_count = 0;
            special_attack_timer = 0;
        }
        
    } // SPL_ARTILLERY_1
    
    
    
}

void Run_Mud_Check(int j, int f_rate)
{
     bool gnd_check=false;
     float mid_x = 0.0f, mid_y = 0.0f;
     int temp_row_x=0, temp_row_y=0;
     int index = 0;   
 
	 if(f_rate <= 0)
	    f_rate = 1; 
 		
	 if(j >= 0)
	 {

       if(sprite[j].type == UNT)  
	   if(sprite[j].sector != UNIT_DECOY)     
       if( sprite[j].anim_state == WAIT)        
       {        
               
            if( sprite[j].status == GROUND_SPAWN)
            {
                sprite[j].status = IDLE;  
                ShotIdle(j);   
               
            } 
            
            // Stop Waking anim from looping...
            if( sprite[j].status == WAKING) 
            { 
                    
                lock_player = false;
                                
                ShotIdle(j);   
                    
            }       
             
       }   

       if(lan_game == false)                
           sprite[j].update = false;       
           
       if(sprite[j].type == UNT)
       {  
                          
           sprite[j].on_screen = false; 
                         
		   if(Is_Guy_In_Range(-1, j, (float)VISUAL_RANGE) == true)
		      sprite[j].on_screen = true;
         
		   if(sprite[j].type == UNT)
		   if(sprite[j].onDeath_action != TANK_TOP)  
		   if(sprite[j].status == MAN_DOWN)   
		       sprite[j].priority = 3;      
	   }  
                             
       // Is the UNIT walking into a hole          
       if(sprite[j].type == UNT) //  && sprite[j].score > 0
       { 
                          
           gnd_check = false;           
           
           mid_x = sprite[j].w+sprite[j].box_width/2;  
           mid_y = sprite[j].z+sprite[j].box_height/2;   
                        
           temp_row_x = (int)((mid_x + map_startX)*10);     
           temp_row_y = (int)((mid_y + map_startY)*10);   
     
           index = (temp_row_y*MAP_HEIGHT)+temp_row_x;   
           
           // Mine check    
       /*    if(index >= 0 && index < MAP_TILES)                
           if(tiles[index] == 14) //  || tiles[index] == 78    
           {    
                                
               if(tiles[index] == 14)                  
                   tiles[index] = 15;                                  
                             
                    
               Shell_Landed(mid_x, mid_y, -1, f_rate, INV_BARREL_BOMB, -1);

               if(dm_game != DM_NONE && ping_tile_count >= 0) 
               { 
                   ping_tile_changeX[ping_tile_count] = temp_row_x; 
                   ping_tile_changeY[ping_tile_count] = temp_row_y;  
                             
                   ping_tile_count++;  
                         
                   if(ping_tile_count >= 100) 
                       ping_tile_count=0;    
               }        
                               
           } */      
            
		   // Grass check...
		   if(sta2_environment_type == AREA_GRASSLANDS) 
           if(sprite[j].type == UNT) 
           if(index >= 0 && index < MAP_TILES)               
		   if( map_cover[index] == 0 )
		   {

             gnd_check=true;   
            
            if(sprite[j].depth != 0.4f)                     
                sprite[j].update = true; 

			 sprite[j].depth = 0.4f;
			  
             if(sprite[j].on_mud == false)     
             { 
                sprite[j].on_mud = true;  
                 
                if( sprite[j].mouseover == false ) 
                { 
                   // Mud Splash 
				   New_FX(sprite[j].x, sprite[j].y,  sprite[j].w, sprite[j].z, 10, PLAY, sprite[j].width, sprite[j].height, sprite[j].width, sprite[j].height, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1); 
                   // Mud ring
                   New_FX(sprite[j].x, sprite[j].y,  sprite[j].w, sprite[j].z, 9, LOOP, sprite[j].width, sprite[j].height, sprite[j].width, sprite[j].height, 4, GFX, 1.0f, 0, 0, FX_MUD, j, 2, 0, 0, -1); 
                }
             }   
		   }

		   // Grass check...
		   if(sta2_environment_type == AREA_SWAMP) 
           if(sprite[j].type == UNT)
           if(index >= 0 && index < MAP_TILES)             
           if( map_cover[index] == 0 )
		   { 

             gnd_check=true;  
			   
             if(sprite[j].on_mud == false)    
             { 
                sprite[j].on_mud = true;  
           
                if(sprite[j].depth != 0.2f)                     
                   sprite[j].update = true; 
               
                sprite[j].depth = 0.2f; 
                 
                if( sprite[j].mouseover == false ) 
                { 
                   // Mud Splash 
				   New_FX(sprite[j].x, sprite[j].y,  sprite[j].w, sprite[j].z, 12, PLAY, sprite[j].width, sprite[j].height, sprite[j].width, sprite[j].height, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1); 
                   // Mud ring
                   New_FX(sprite[j].x, sprite[j].y,  sprite[j].w, sprite[j].z, 11, LOOP, sprite[j].width, sprite[j].height, sprite[j].width, sprite[j].height, 4, GFX, 1.0f, 0, 0, FX_MUD, j, 2, 0, 0, -1); 
                }
             }   
		   }   

           // Mud check 
      /*     if(sprite[j].type == UNT)
           if(index >= 0 && index < MAP_TILES)             
           if(tiles[index]==16 || tiles[index] == 29 || tiles[index] == 30 || tiles[index] == 31)      
           {  

             gnd_check=true;

             if(sprite[j].on_mud == false)   
             {
                sprite[j].on_mud = true;
           
                if(sprite[j].depth != 0.3f)                   
                   sprite[j].update = true; 
               
                sprite[j].depth = 0.3f; 
                 
                if( sprite[j].mouseover == false ) 
                { 
                   // Mud Splash 
                   New_FX(sprite[j].x+sprite[j].width/6, sprite[j].y,  sprite[j].w, sprite[j].z, 3, PLAY, sprite[j].box_width, sprite[j].box_height, sprite[j].width/1.5f, sprite[j].height/2, 2, GFX, 1.0f, 0, 0, FX_STATIC, j, 2, 0, 0, -1);
                   // Mud ring
                   New_FX(sprite[j].x, sprite[j].y,  sprite[j].w, sprite[j].z, 2, LOOP, sprite[j].box_width, sprite[j].box_height, sprite[j].width/1.5f, sprite[j].height/3, 4, GFX, 1.0f, 0, 0, FX_MUD, j, 2, 0, 0, -1); 
                }
             }    
           }  */

       } // sprite[j].type == UNT
                                   
           // Mud Check
     /*      if(sprite[j].type == UNT)           
           if(index >= 0 && index < MAP_TILES)  
           if(tiles[index]>=17 && tiles[index]<29)          
           {
               
               gnd_check=true; 

               if(sprite[j].depth != -1.2f)                   
                   sprite[j].update = true;
                             
               sprite[j].depth = -1.2f;   
               
               if(sprite[j].on_mud == true)
               {   
                   sprite[j].on_mud = false;
                   // Mud Splash
                   New_FX(sprite[j].x+sprite[j].width/6, sprite[j].y,  sprite[j].w, sprite[j].z, 3, PLAY, sprite[j].box_width, sprite[j].box_height, sprite[j].width/1.5f, sprite[j].height/2, 2, GFX, 1.0f, 0, 0, FX_STATIC, j, 2, 0, 0, -1);
                   
               } 
                   
           }  */   
                                      
           // Hard Ground Check   
           if(sprite[j].type == UNT)             
           if(index >= 0 && index < MAP_TILES)  
           if( map_cover[index] == 1 ) 
           if(gnd_check == false )            
           { 
      
               if(sprite[j].depth != 0.0f)                    
                   sprite[j].update = true; 

               sprite[j].depth = 0.0f;  
			    
               if(sprite[j].on_mud == true && sprite[j].mouseover == false)
			   {
                   // Mud Splash 
				   if(sta2_environment_type == AREA_SWAMP)
					   New_FX(sprite[j].x, sprite[j].y,  sprite[j].w, sprite[j].z, 12, PLAY, sprite[j].width, sprite[j].height, sprite[j].width, sprite[j].height, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1); 
                   if(sta2_environment_type == AREA_GRASSLANDS)
					   New_FX(sprite[j].x, sprite[j].y,  sprite[j].w, sprite[j].z, 10, PLAY, sprite[j].width, sprite[j].height, sprite[j].width, sprite[j].height, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1); 
				   if(sta2_environment_type != AREA_SWAMP && sta2_environment_type != AREA_GRASSLANDS)
					   New_FX(sprite[j].x, sprite[j].y,  sprite[j].w, sprite[j].z, 10, PLAY, sprite[j].width, sprite[j].height, sprite[j].width, sprite[j].height, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);
			   }
                  
               sprite[j].on_mud = false;
                                                 
           }       
     
     } // j >= 0
     
     
}

void Run_Legs_Check(int index, int the_player_id)
{  
 	
	float x1 = 0.0f, y1 = 0.0f; 
	int temp_row_x=0, temp_row_y=0;
	int row_index=0;  

	if(index >= 0 && the_player_id >= 0)
	{   
	
		sprite[index].alpha = 0.0f;

/*
    sprite[index].alpha = 1.0f;	 
 	  
	if(sprite[index].status == MAN_DOWN 
	|| sprite[index].status == MAN_DOWN1  
	|| sprite[index].status == MAN_DOWN2)   
	    sprite[index].alpha = 0.0f;   
	
	if(index != ply_hat_id)
	if(ply_id != -1)
	if(the_player_id == ply_id)       
 	if(sprite[ply_id].on_ladder == true) //  || sprite[the_player_id].on_ladder == true
	    sprite[index].alpha = 0.0f;  

 	if(the_player_id == ply_id)      
 	if(player_in_water == true) //  || sprite[the_player_id].on_ladder == true
	    sprite[index].alpha = 0.0f;  
      
	if(index != ply_hat_id)
	if(sprite[index].status == FLATTENED 
	|| sprite[index].status == FALLING)       
	    sprite[index].alpha = 0.0f;  */
/*  
	if(index == ply_hat_id)
	if(sprite[index].status == DIEING 
	|| sprite[index].status == MAN_DOWN
	|| sprite[index].status == MAN_DOWN1
	|| sprite[index].status == MAN_DOWN2)
	    sprite[index].alpha = 0.0; 
    
	// Check if a player is swimming...
	 
    x1 = sprite[the_player_id].w+sprite[the_player_id].box_width/2; 
    y1 = sprite[the_player_id].z+sprite[the_player_id].box_height/2;     
                
    temp_row_x = (int)((x1 + map_startX)*10);         
    temp_row_y = (int)((y1 + map_startY)*10);  
     
    row_index = (temp_row_y*MAP_HEIGHT)+temp_row_x; 					    
	
	if(the_player_id != ply_id)
    if(tiles[row_index]>=480 && tiles[row_index] < 484 )
	    sprite[index].alpha = 0.0f;
   */

	} // index >= 0 && the_player_id >= 0
 	 
} 
void Run_Hats()
{
	int old_current_headwear=WEARING_NONE;

	 if(p1_id != -1)   
     if(ply_hat_id != -1)   
	 {

	     if(current_helmet == -1)
		 {
			 
			 old_current_headwear = current_headwear;

		     sprite[ply_hat_id].alpha = 0.0f;
			 sprite[ply_hat_id].turn_off = true;
			 sprite[ply_hat_id].mouseover = true;
			 current_headwear = WEARING_NONE; 

			 // Update textures if headwear has changed...	
			 if(old_current_headwear != current_headwear)
			 { 

        		if(current_char == CHAR_RIFLE)	
        	    if(current_headwear == WEARING_NONE)   
        	    {        
            	    sprintf( temp_string.string, "Data/hud/faces_non");                
            	    Change_Texture(temp_string, 4);   
                    sprintf(temp_string.string, "Data/chars/green_gunnerW_non");                           
            	    Change_Texture(temp_string, 30);    
        	    } 

        		if(current_char == CHAR_SHOTGUN)	
        	    if(current_headwear == WEARING_NONE)   
        	    {        
            	    sprintf( temp_string.string, "Data/hud/faces_shotgun_non");                
            	    Change_Texture(temp_string, 4);                              
        	    } 


			 }   
		 }
		 else 
		 {
			 
			 old_current_headwear = current_headwear;

		     sprite[ply_hat_id].alpha = 1.0f;
			 sprite[ply_hat_id].turn_off = false;  
			 sprite[ply_hat_id].mouseover = false;
	
			 // Get type of hat being worn...
			 if(current_helmet != -1)
			 {

			 if(player_inv_value1[current_helmet] == TYPE_TINHAT)
			     current_headwear = WEARING_TINHAT;
			 if(player_inv_value1[current_helmet] == TYPE_BUTLERS)
			     current_headwear = WEARING_BUTLERS;
			 if(player_inv_value1[current_helmet] == TYPE_CAP)
			     current_headwear = WEARING_CAP;
			 if(player_inv_value1[current_helmet] == TYPE_OFFICER)
			     current_headwear = WEARING_OFFICER;
			 if(player_inv_value1[current_helmet] == TYPE_COWBOY) 
			     current_headwear = WEARING_COWBOY;
			 if(player_inv_value1[current_helmet] == TYPE_CAMMO) 
			     current_headwear = WEARING_CAMMO;
			 }

			 // Update textures if headwear has changed...	
			 if(old_current_headwear != current_headwear)
			 {

       			if(current_char == CHAR_RIFLE)
//        	    if(current_headwear == WEARING_TINHAT)  
        	    {        
            	    sprintf( temp_string.string, "Data/hud/faces");                
            	    Change_Texture(temp_string, 4);  
            	    sprintf( temp_string.string, "Data/chars/green_hat1");                 
            	    Change_Texture(temp_string, 31);  
                    sprintf(temp_string.string, "Data/chars/green_gunnerW");                           
            	    Change_Texture(temp_string, 30);                               
        	    } 

       			if(current_char == CHAR_SHOTGUN)  
//        	    if(current_headwear == WEARING_TINHAT)  
        	    {        
            	    sprintf( temp_string.string, "Data/hud/faces_shotgun");                
            	    Change_Texture(temp_string, 4);  
            	    sprintf( temp_string.string, "Data/chars/green_hat5");                
            	    Change_Texture(temp_string, 31);                              
        	    } 
       
 /*       	    if(current_headwear == WEARING_CAP)    
        	    {        
            	    sprintf( temp_string.string, "Data/hud/faces_cap");                
            	    Change_Texture(temp_string, 4);  
            	    sprintf( temp_string.string, "Data/chars/green_hat3");                
            	    Change_Texture(temp_string, 31);                              
        	    } 
       
        	    if(current_headwear == WEARING_BUTLERS)     
        	    {        
            	    sprintf( temp_string.string, "Data/hud/faces_but");                
            	    Change_Texture(temp_string, 4);  
            	    sprintf( temp_string.string, "Data/chars/green_hat2");                
            	    Change_Texture(temp_string, 31);                              
        	    }  
       
        	    if(current_headwear == WEARING_OFFICER)      
        	    {        
            	    sprintf( temp_string.string, "Data/hud/faces_off");                
            	    Change_Texture(temp_string, 4);  
            	    sprintf( temp_string.string, "Data/chars/green_hat4");                
            	    Change_Texture(temp_string, 31);                              
        	    } 
       
        	    if(current_headwear == WEARING_COWBOY)     
        	    {        
            	    sprintf( temp_string.string, "Data/hud/faces_cow");                
            	    Change_Texture(temp_string, 4);  
            	    sprintf( temp_string.string, "Data/chars/green_hat5");                
            	    Change_Texture(temp_string, 31);                              
        	    } 
        
        	    if(current_headwear == WEARING_CAMMO)      
        	    {        
            	    sprintf( temp_string.string, "Data/hud/faces_cam");                
            	    Change_Texture(temp_string, 4);  
            	    sprintf( temp_string.string, "Data/chars/green_hat6");                
            	    Change_Texture(temp_string, 31);                              
        	    } */

			 }

		 }	

	 }

}
void Run_Legs()
{
 /*	 
	 if(p1_id != -1)   
     if(p1_legs_id != -1)   
	 {

	     sprite[p1_legs_id].x = sprite[p1_id].x;   
	     sprite[p1_legs_id].y = sprite[p1_id].y;
	     
	     sprite[p1_legs_id].w = sprite[p1_id].w; 
	     sprite[p1_legs_id].z = sprite[p1_id].z;
	     
	     sprite[p1_legs_id].box_width = sprite[p1_id].box_width; 
	     sprite[p1_legs_id].box_height = sprite[p1_id].box_height;	 		 	     
	     
	     sprite[p1_legs_id].mov_x = sprite[p1_id].mov_x;
	     sprite[p1_legs_id].mov_y = sprite[p1_id].mov_y;
	      
	     sprite[p1_legs_id].end_x = sprite[p1_id].end_x; 
	     sprite[p1_legs_id].end_y = sprite[p1_id].end_y; 
	     
	     sprite[p1_legs_id].angle = sprite[p1_id].angle;
	     sprite[p1_legs_id].tar_angle = sprite[p1_id].tar_angle;
	     
	     sprite[p1_legs_id].moving = sprite[p1_id].moving;
	     
	     sprite[p1_legs_id].status = sprite[p1_id].status;  
	     
		 sprite[p1_legs_id].depth = sprite[p1_id].depth;
		 
		 sprite[p1_legs_id].flash_target = sprite[p1_id].flash_target;
		 		 		     
		 sprite[p1_legs_id].flash_timer = sprite[p1_id].flash_timer;		 
		 
	     sprite[p1_legs_id].factor = sprite[p1_id].factor;

		 Run_Legs_Check(p1_legs_id, p1_id);
		 
	 } 

	 if(p1_id != -1)   
     if(ply_hat_id != -1)   
	 {
	     sprite[ply_hat_id].x = sprite[p1_id].x; 
	     sprite[ply_hat_id].y = sprite[p1_id].y;
	     
	     sprite[ply_hat_id].w = sprite[p1_id].w; 
	     sprite[ply_hat_id].z = sprite[p1_id].z;
	     
	     sprite[ply_hat_id].box_width = sprite[p1_id].box_width; 
	     sprite[ply_hat_id].box_height = sprite[p1_id].box_height;	 		 	     
	     
	     sprite[ply_hat_id].mov_x = sprite[p1_id].mov_x;
	     sprite[ply_hat_id].mov_y = sprite[p1_id].mov_y;
	     
	     sprite[ply_hat_id].end_x = sprite[p1_id].end_x;
	     sprite[ply_hat_id].end_y = sprite[p1_id].end_y;
	     
	     sprite[ply_hat_id].angle = sprite[p1_id].angle;
	     sprite[ply_hat_id].tar_angle = sprite[p1_id].tar_angle;
	     
	     sprite[ply_hat_id].moving = sprite[p1_id].moving;
	     
	     sprite[ply_hat_id].on_ladder = sprite[p1_id].on_ladder;
	     
	     sprite[ply_hat_id].status = sprite[p1_id].status;  
	     
		 sprite[ply_hat_id].depth = sprite[p1_id].depth;
		 
		 sprite[ply_hat_id].flash_target = sprite[p1_id].flash_target;
		 		 		     
		 sprite[ply_hat_id].flash_timer = sprite[p1_id].flash_timer;		 
		 
	     sprite[ply_hat_id].factor = sprite[p1_id].factor;	

		 sprite[ply_hat_id].anim_state = sprite[p1_id].anim_state;	
		 sprite[ply_hat_id].cur = sprite[p1_id].cur;	
		 sprite[ply_hat_id].cur_time = sprite[p1_id].cur_time;	 
		 sprite[ply_hat_id].frame = sprite[p1_id].frame;			     
		 
		 Run_Legs_Check(ply_hat_id, p1_id); 
		 
	 } 
  	 	      
	 if(p2_id != -1)   
     if(p2_legs_id != -1)  
	 { 
	     sprite[p2_legs_id].x = sprite[p2_id].x; 
	     sprite[p2_legs_id].y = sprite[p2_id].y + 0.01f;
	     
	     sprite[p2_legs_id].w = sprite[p2_id].w; 
	     sprite[p2_legs_id].z = sprite[p2_id].z;
	     
	     sprite[p2_legs_id].box_width = sprite[p2_id].box_width; 
	     sprite[p2_legs_id].box_height = sprite[p2_id].box_height;	 	     
	     
	     sprite[p2_legs_id].mov_x = sprite[p2_id].mov_x;
	     sprite[p2_legs_id].mov_y = sprite[p2_id].mov_y;
	      
	     sprite[p2_legs_id].end_x = sprite[p2_id].end_x;
	     sprite[p2_legs_id].end_y = sprite[p2_id].end_y;
	     
	     sprite[p2_legs_id].angle = sprite[p2_id].angle;
	     sprite[p2_legs_id].tar_angle = sprite[p2_id].tar_angle;
	     
	     sprite[p2_legs_id].moving = sprite[p2_id].moving;
	     
	     sprite[p2_legs_id].status = sprite[p2_id].status;
	     
		 sprite[p2_legs_id].depth = sprite[p2_id].depth;
		 
		 sprite[p2_legs_id].flash_target = sprite[p2_id].flash_target;	
		 		 		     
		 sprite[p2_legs_id].flash_timer = sprite[p2_id].flash_timer;		 	 			     

	     sprite[p2_legs_id].factor = sprite[p2_id].factor;				     
		 
		 Run_Legs_Check(p2_legs_id, p2_id);
		 
	 }
  	 	     
	 if(p3_id != -1)   
     if(p3_legs_id != -1) 
	 { 
	     sprite[p3_legs_id].x = sprite[p3_id].x; 
	     sprite[p3_legs_id].y = sprite[p3_id].y + 0.01f; 
	     
	     sprite[p3_legs_id].w = sprite[p3_id].w; 
	     sprite[p3_legs_id].z = sprite[p3_id].z;
	     
	     sprite[p3_legs_id].box_width = sprite[p3_id].box_width; 
	     sprite[p3_legs_id].box_height = sprite[p3_id].box_height;	 	     
	     
	     sprite[p3_legs_id].mov_x = sprite[p3_id].mov_x;
	     sprite[p3_legs_id].mov_y = sprite[p3_id].mov_y;
	     
	     sprite[p3_legs_id].end_x = sprite[p3_id].end_x;
	     sprite[p3_legs_id].end_y = sprite[p3_id].end_y;
	     
	     sprite[p3_legs_id].angle = sprite[p3_id].angle;
	     sprite[p3_legs_id].tar_angle = sprite[p3_id].tar_angle;
	      
	     sprite[p3_legs_id].moving = sprite[p3_id].moving;
	     
	     sprite[p3_legs_id].status = sprite[p3_id].status;
	     
		 sprite[p3_legs_id].depth = sprite[p3_id].depth;	
		 
		 sprite[p3_legs_id].flash_target = sprite[p3_id].flash_target;	
		 		 		     
		 sprite[p3_legs_id].flash_timer = sprite[p3_id].flash_timer;		 	 		     

	     sprite[p3_legs_id].factor = sprite[p3_id].factor;				     
		 
		 Run_Legs_Check(p3_legs_id, p3_id);
		 
	 }
  	 	     
	 if(p4_id != -1)   
     if(p4_legs_id != -1) 
	 { 
	     sprite[p4_legs_id].x = sprite[p4_id].x; 
	     sprite[p4_legs_id].y = sprite[p4_id].y + 0.01f;
	     
	     sprite[p4_legs_id].w = sprite[p4_id].w; 
	     sprite[p4_legs_id].z = sprite[p4_id].z;
	     
	     sprite[p4_legs_id].box_width = sprite[p4_id].box_width; 
	     sprite[p4_legs_id].box_height = sprite[p4_id].box_height;	 	     
	     
	     sprite[p4_legs_id].mov_x = sprite[p4_id].mov_x;
	     sprite[p4_legs_id].mov_y = sprite[p4_id].mov_y;
	     
	     sprite[p4_legs_id].end_x = sprite[p4_id].end_x;
	     sprite[p4_legs_id].end_y = sprite[p4_id].end_y;
	     
	     sprite[p4_legs_id].angle = sprite[p4_id].angle;
	     sprite[p4_legs_id].tar_angle = sprite[p4_id].tar_angle;
	     
	     sprite[p4_legs_id].moving = sprite[p4_id].moving;
	     
	     sprite[p4_legs_id].status = sprite[p4_id].status;
	     
		 sprite[p4_legs_id].depth = sprite[p4_id].depth;	
		 
		 sprite[p4_legs_id].flash_target = sprite[p4_id].flash_target;
		 		 		     
		 sprite[p4_legs_id].flash_timer = sprite[p4_id].flash_timer;
		 
	     sprite[p4_legs_id].factor = sprite[p4_id].factor;				     
		 
		 Run_Legs_Check(p4_legs_id, p4_id);
		 
	 }	 	 
 	 
 	 */
 	 
 	 
}

void Respawn_Enemy(int index)   
{ 

	if(index >= 0)
	{

    // Heal the sprite stored in group_id...
    if(sprite[index].status != DEATH_READY)
    if(sprite[index].status != MAN_DOWN1)
    if(sprite[index].score <= 0 || sprite[index].status == MERCY)
    {
		
		if(sprite[index].status != MERCY) 
		if(sprite[index].linked_sprite != player_type)
		    enemy_count++;
				 					   
        sprite[index].alpha    = 1.0f;   
        sprite[index].priority = 2; 
        sprite[index].update = true;   
        sprite[index].status = IDLE; 
		sprite[index].reached_node = -1; 
        sprite[index].anim_state = WAIT;  
		sprite[index].turn_off = false;
        sprite[index].score = Calculate_TotalScore(index);
        sprite[index].mercy = false; 
        
  		sprite[index].spotted_timer = (int)TimerGetTime() + 12000;
  		sprite[index].spotted = true; 
  		
		sprite[index].ai_brain = BRAIN_HUNTER; 
		
		sprite[index].fire_target = -1;
		
		sprite[index].reload_timer = 0;
		sprite[index].emy_shoot = 0;
		
		sprite[index].group_id = -2; // Can't be revived again..
		                
        ShotIdle(index);  	 		
		   
	}
 	  

	} // index >= 0

}
 
void Set_Camera(int f_rate, bool startup) 
{
     float angle=0.0f;
     float tar_x=0.0f, tar_y=0.0f;  
     float ply_x =0.0f;
     float ply_y = 0.0f;
     float deltax=0.0f, deltay=0.0f;
	 float temp_factor = 0.0f;
	 int id=-1;

	if(f_rate <= 0)
	    f_rate = 1;  
	 
	if(sta2_turn == TURN_PLAYER) 
	if(ply_id != -1)
		id = ply_id; 
	 
	if(sta2_turn == TURN_COMPUTER)  
	if(emy_id != -1)
	{ 
		id = emy_id;  

		if(the_target != -1) 
		if(sta2_enemy_mode == MOVE_FOCUS || sta2_enemy_mode == MOVE_SHOOT || sta2_enemy_mode == MOVE_REFOCUS)
			id = the_target;
	}

	// This code starts at player, then always moves towards the camX_OFFSET, camY_OFFSET...
	if(game_mode == WALK)
	if(id != -1)  
	{ 
                       
        temp_factor = sprite[id].factor;      

		ply_x = -( (sprite[id].x + (sprite[id].width/2)));
		ply_y = -(sprite[id].y + (sprite[id].height/2) - (sprite[id].box_height));  

		if(startup == true)         
		{
			camX = ply_x;     
			camY = ply_y;  

			mouseX = -camX;
			mouseY = -camY;

			camX_OFFSET=0.0f; 
			camY_OFFSET=0.0f;
		}

        mouseX -= -camX;                          
        mouseY -= -camY;               
                                            
        hud_mouseX -= -camX;                       
        hud_mouseY -= -camY;          

		if(STA2_MODE == MODE_AIMING || STA2_MODE == MODE_TARGET)
		{  

		}  

		if(STA2_MODE == MODE_MOVING)  
		{
			 
			if(sta2_turn == TURN_COMPUTER) 
			{ 
				camX =  -((sprite[id].x + (sprite[id].width/2)));
				camY = -(sprite[id].y + (sprite[id].height/2) - (sprite[id].box_height));  
			}
			 
			if(sta2_turn == TURN_PLAYER)  
			if(sta2_menu == false && sta2_displaying_help == false) 
			{ 

				tar_x = ply_x + camX_OFFSET;      
				tar_y = ply_y + camY_OFFSET;   
                           
				angle = atan2(camY - tar_y, camX - tar_x);
             
				camDistance = Node_Distance1(camX, camY, tar_x, tar_y);
				 
				if(camDistance > 0.018f)          
				{ 
					    
					if(sprite[id].moving == true)
						temp_speed = camDistance/500; // 450    
					else
						temp_speed = camDistance/350; // 500   

					deltax = cos(angle);             
					deltay = sin(angle);   
    
					deltax *= temp_speed*(float)f_rate;
					deltay *= temp_speed*(float)f_rate; 

					camY -= deltay;    
					camX -= deltax;   

				}

				if(NEW_CAMERA_TEST == 0)
				{
					camX =  -((sprite[id].x + (sprite[id].width/2)));
					camY = -(sprite[id].y + (sprite[id].height/2) - (sprite[id].box_height));  
				}

			}
		} 
		 
        if( camX > ( map_startX-zoom_factor) )       
        { 
            camX = map_startX-zoom_factor;      
        }    

        if( camX < -(MAP_WIDTH*0.05f) + zoom_factor)
        {
            camX = -(MAP_WIDTH*0.05f) + zoom_factor;    
        }         
               
        // Offset for Hud at bottom of map                      
        if(camY > map_startY-((zoom_factor*sc_ratio)) ) // -((zoom_factor*sc_ratio)/4)  
        {     
            camY = map_startY-((zoom_factor*sc_ratio)); // -((zoom_factor*sc_ratio)/4)   
        } 
        if( camY < -(MAP_HEIGHT*0.05f) + (zoom_factor*sc_ratio))
        {
            camY = -(MAP_HEIGHT*0.05f) + (zoom_factor*sc_ratio);    
        }              
                                                                                              
        mouseX += -camX;                               
        mouseY += -camY;  
                 
        hud_mouseX += -camX;           
        hud_mouseY += -camY; 
              
        Get_Mouse_Row();  

	} // ply_id != -1


}

