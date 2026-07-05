#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN 

#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>			// Header File For Standard Input/Output
#include <gl\gl.h> 
#include "globals.h"   
   
#define MANUAL_SKIP 300    
#define LOAD_SKIP 3000    
#define LOAD_SKIP_FAST 2500  
#define ACCOMPLISHED_TIME 4000            

#define DISABLE_MISSION_RESTART  1 

#define NO_FRONT_SNOWFLAKES  20
#define NO_SNOWFLAKES   100


extern void Generate_Object_Collision(int loop, bool col_test);
extern bool New_FX(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int i_value, int i_type, int state, int linked_sprite, int tex_id, int i_value1, int i_value2, int i_value3);
extern void Display_Message(int index, int message);
extern void Remove_Item(int item_type, int item_value, int item_value1, bool remove_all);
extern bool Calculate_Item(int item_value, int item_type, int the_item, int item_value1, int item_value2, int item_value3);
extern void Bit_Shift( int the_value1, int bit_to_shift, int bit_value);
extern int Get_Bit_Shift( int the_value1, int bit_to_shift);
extern int Convert_Angle_To_Dir(float my_angle);
extern bool Has_This_Item(int type, int value);
extern void Move_Vehicle(int loop, float x_pos, float y_pos, int f_rate);
extern void Remove_Temps(int type);
extern void Reset_Shop_Specials();
extern void Special_Attack(int type);
extern void Display_Front_Message(int type, int f_rate);
extern void Message_Fx();
extern int Convert_Dir_To_Angle(int loop, int direction);
extern void Set_Heading(int loop, float x1, float y1, bool hulk_ladder);
extern int Find_Path(int loop, float destX, float destY); 
extern void Set_Screen_Ratio();
extern void Remove_Item(int item_type, int item_value, int item_value1, bool remove_all);
extern void Save_Position();
extern void Load_Position(); 
extern void Run_Buttons();
extern void DamageNumber( int loop, int damage, int is_blue ); 
extern int Make_Trade();
extern void GetPage(int sta2_event);
extern void OptionHandler(int page_no, int option);
extern bool IsSquadAlive(); 
extern bool sta2GetName(char *filename, char *word);
extern bool sta2GetEmyNames(char *filename);
extern int TotalSquadScore(int loop);
extern bool STA2_SaveLevel( sString sfilename ); 
extern bool STA2_LoadLevel( sString sfilename );
extern void STA2_RemoveSave();
extern bool STA2_HasSave( char *filename ); 
extern int GetLongestLine(char *word);
extern void SwipeCode(int f_rate);
extern void sta2_Scroll(int number, bool startup, int f_rate, int direction);
extern void Run_Ach();

#if IS_FULL_STEAM == 1 

extern void Upload_Scores();

#endif

void Calculate_Gold();
void Make_Tunnel(int index);
void Fire_Shoot( int shooter, float x1, float y1, float angle, int f_rate);
void Check_Patrol(int loop, int point, int next_point);
void GraveStone();
int Get_Character_Scene();    
void Type_Key(int index, char a, char A);
float GetIncSpeed(float value);

    
// Scripts for Levels.. 

int cc=0;  
int stamp_timer=0;   
float start_stamp_Y=0.0;   
float start_stamp_X=0.0;
float start_X=0.0;
float start_Y=0.0; 
float start_Y1=0.0;
float start_Y2=0.0;
float spin_angle=0;
bool card_flash=false;
int card_flash_timer=0;       
int thud_timer=0;
int front_bomb_timer=0;
int front_bomb_count=0;
bool front_bomb_run=false;
bool speak_txt=false;
int speak_timer = 0;
int my_card_selected = 0;
int castle_sequence=0;
int no_mouse_change_timer = 0; // Stops question mark bug on mouse icon
int cowboy_timer=0;
int chicken_timer=0;
int sta2_snow_start_index=0;
int sta2_snow_timer = 0;
int sta2_snow_direction = 0;
float temp_snow_speed=0.0f;
float movement_limit=0;
int map_name_timer=0;

bool pigeon_direction = false;

int patroling1 = 0;
int patroling2 = 0;
int patroling3 = 0;

int target_pin=-1;

int no_wave = 0;
int wave_count = 0;

int sta2_layout_page = LAYOUT_ADA;
 
bool skidding=false;     
                 
void Run_Scripts(int f_rate)
{
	   float rad_width=0.0f;
	   float rad_height=0.0f; 
	   float rad_x=0.0f, rad_y=0.0f;

	   float tar_x=0.0f, tar_y=0.0f;
       float cam_x =0.0, cam_y =0.0; 
       float deltax =0.0,deltay =0.0;
       float testX=0.0, testY=0.0;
       float temp_speed = 0.0;
       float temp_speed1= 0.0;
       float angle = 0.0;     
       float x_pos=0.0, y_pos=0.0;
       float midX=0.0, midY=0.0;
       float dis_to_point=0.0;
       float diff_x=0.0, diff_y=0.0; 
       float total_distance=0.0; 
       float distance=0.0f;
       float mid_x=0.0f, mid_y=0.0f;
       float temp_expand=0.0f;
	   float sta2_increment=0.0f;

	   int slongest_line=0;
       int display_players_cards = 0;
       int display_dealers_cards = 0;
       int row_x=0, row_y=0;
       int Card_Time = 1250;
       int Card_Time1 = 3000;
       int quit_id = 0; 
       int deal_id = 0;
       int rnd=0; 
       int index=0;
       bool pass_on = false;  
       int anim_timer = 0;
       char string_value[1024]; 
       int secrets_found=0;
       int medals_found=0;
       int cards_found=0;
       float complete_rate=0;
       int length=0;
       int target_count=0;
       int test_button=0;
       int enemy_type=0;
	   int sta2_squad_temp_index=0;
	   int script_damage=0;
	   int rations_gain=0;
	   int total_enemy_health=0;
	   int total_player_health=0;
	   int hired_wp=0;
	   int sta2_equip_type = 0; 
	   int sta2_emy_pin_map = -1;

	   int pack_id=-1;

	   int unit_count_fifth=0;

	   bool sta2_pin_is_dead=false;

	   int option1=0;
	   int option2=0;
	   int option3=0;
	   int option4=0;

	   int targetA = 0;
	   int targetB = 0;
	   int targetC = 0;
	   int targetD = 0; 

       int cull_sizeX = 20; 
       int cull_sizeY = 20; 
       int temp =0;
       int temp1 =0, temp2 = 0;   
       
       bool disable_spy = false; 

	   bool disable_buffs = false;

	   bool has_no_connections = false;
	   bool blocked = false;

	   bool sta2_rising = false;

		if(f_rate <= 0)
	    	f_rate = 1;   

	
    // ******************************************************************************//
    //                            0-0  (RETRO ARMY SCREEN)                           //
    // ******************************************************************************//
				                 
       // Title Screen Stuff...
       if(!mode) 
       if(next_scene == false)  
       if(episode == 0 && scene == 0)   
       {    
                    
           if(title_sequence == 0)     
           { 

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
               
               activate_bicycle = false;
               
           }   
                                
           if(title_sequence == 1)       
           {   
             
             cos_scroll += ( (0.001f) ); 
             
             if(cos_scroll > 1.5f )    
                cos_scroll = 1.5f; 
                                     
             temp_speed = 0.00075f*(cos(cos_scroll));  
             
             sprite[1].y += temp_speed * (float)f_rate; 
                 
             if(start_stamp_Y < sprite[1].y)
             {   
                 sprite[1].y = start_stamp_Y;
                 title_sequence++;
             }                
                  
           } 
             
           if(title_sequence == 2)      
           {  
             
             Set_Sprite(1, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Stunned
             
             sprite[0].alpha = 1.0;
             
             stamp_sfx = true; 
                               
             red_swipe = true;
             swipe_color = COLOR_WHITE;
             red_timer = (int)TimerGetTime() + 50;
               
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
                                          
             title_timer = (int)TimerGetTime()+2000;                         
             title_sequence++;  
                                        
           }              
                                
           if( (int)TimerGetTime() > title_timer )
           if(title_sequence == 9) 
           {              
               title_sequence++; 
               next_scene = true;

               episode = 1; 
			   scene = 35;  

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
    //                            1-1  (BATTLE SCREEN)                               //
    // ******************************************************************************//
	    
       // Battle mode...               
       if(!mode)    
       if(next_scene == false)              
       if(episode == 1 && scene == 1)            
       {          

		    // Turn off cp stars....
		    for(int i = 2; i < 10; i++)
				sprite[i].alpha = 0.0f;
			 
		    if(sta2_turn == TURN_PLAYER)   
			if(sta2_pressed_map == false)
			if(sta2_player_moves <= 0 || sta2_ended_turn == true)
				run_swipe = true;

			if(sta2_turn == TURN_COMPUTER)        
			if(sta2_enemy_moves <= 0)  
				run_swipe = true;
			   
			if(sta2_change_turn == true)  
				run_swipe = true;

		//	if(sta2_pressed_map == false && sta2_turn != TURN_COMPUTER)
		//		run_swipe = true;

			if(run_swipe == true)
				SwipeCode(f_rate); 

		    // Enemy red circle firing range...
		    sprite[13].alpha = 0.0f; 
		    // Player movement circle range...
		    sprite[14].alpha = 0.0f; 

		    if(sta2_quit_active == true)  
			{
				if(sta2_playing_tutorial == true)
					Set_Sprite(3, 1, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Quit game?
				else
					Set_Sprite(3, 3, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Quit and save?
			}
			else
  				Set_Sprite(3, 2, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Point Arrow 

		//	if(sta2_has_officer == false) 
		//		sta2_power_bar = 0.0f;  
			 
			// For testing...
		//	sta2_power_bar = 100.0f;

			if(sta2_power_bar == 100.0f)
				Set_Sprite(11, 18, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Point Arrow
			else
				Set_Sprite(11, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Point Arrow
			
			// Calculate power bar... 
			sprite[11].width = (sprite[11].box_width/100.0f)*sta2_power_bar;

			sprite[10].alpha = 0.0f;  
			sprite[11].alpha = 0.0f;
			sprite[16].alpha = 0.0f; // Moves left...

			if(sta2_turn == TURN_COMPUTER)      
			{
				sprite[10].alpha = 0.0f;  
				sprite[11].alpha = 0.0f; 

				if(title_sequence == 1) 
				{
					sprite[16].alpha = 1.0f; // Moves left...
				}
			}
			if(sta2_turn == TURN_PLAYER) 
			{
				if(title_sequence == 2) 
				{
					sprite[10].alpha = 1.0f;
					sprite[11].alpha = 1.0f;
					sprite[16].alpha = 1.0f; // Moves left...
				}
			}
			      
			if(sta2_pressed_map == true)
			{
				sprite[10].alpha = 0.0f;  
				sprite[11].alpha = 0.0f;
				sprite[16].alpha = 0.0f; // Moves left...
			}

			if(sta2_yes_no_active == true)
			{ 

				hud[3].alpha = 1.0f;  

				if(sta2_quit_active == true)
				{
					new_counter[7].alpha = 1.0f; 
					new_counter[7].id = 0;
					sprintf(new_counter[7].word, "1 : YES"); 
					new_counter[7].x = hud[3].x + 0.08f;  
					new_counter[7].y =  hud[3].y + hud[3].height - 0.1f;
					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;
					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	
				 
					new_counter[8].alpha = 1.0f;
					new_counter[8].id = 0;
					sprintf(new_counter[8].word, "2 : NO"); 
					new_counter[8].x = hud[3].x + 0.08f;  
					new_counter[8].y = hud[3].y + hud[3].height - 0.1f - 0.04f;
					new_counter[8].w = new_counter[8].x - 0.026f;   
					new_counter[8].z = new_counter[8].y - 0.015f;
					new_counter[8].box_width = strlen(new_counter[8].word)   *  0.026f;
					new_counter[8].box_height = new_counter[8].height - 0.015f;	
				}
				if(sta2_quit_active == false)
				if(sta2_yes_no_endturn == 0)
				if(sta2_yes_no_page_map == 0) 
				{ 
					new_counter[11].alpha = 1.0f;      
					new_counter[11].id = 0;      

					if(sta2_is_first_level == true)
						sprintf(new_counter[11].word, "Click on a^pin to move^that unit."); 
					else
						sprintf(new_counter[11].word, "Some units^can use^grenades."); 

					new_counter[11].x = hud[3].x + 0.042f;  
					new_counter[11].y =  hud[3].y + hud[3].height - 0.1f;

					new_counter[7].alpha = 1.0f;  
					new_counter[7].id = 0;
					sprintf(new_counter[7].word, "1 : Next"); 
					new_counter[7].x = hud[3].x + 0.042f;  
					new_counter[7].y =  hud[3].y + hud[3].height - 0.1f - 0.20f;
					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;
					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	
				}
				if(sta2_quit_active == false)
				if(sta2_yes_no_endturn == 0)
				if(sta2_yes_no_page_map == 1) 
				{ 
					new_counter[11].alpha = 1.0f;    
					new_counter[11].id = 0;

					if(sta2_is_first_level == true)
						sprintf(new_counter[11].word, "You can move^any unit up^to 4 times."); // You can move^any unit up^to 4 times.
					else
						sprintf(new_counter[11].word, "Use grenades^to take out^small groups."); 

					new_counter[11].x = hud[3].x + 0.042f;  
					new_counter[11].y =  hud[3].y + hud[3].height - 0.1f;

					new_counter[7].alpha = 1.0f;  
					new_counter[7].id = 0;
					sprintf(new_counter[7].word, "1 : OKAY"); 
					new_counter[7].x = hud[3].x + 0.042f;  
					new_counter[7].y =  hud[3].y + hud[3].height - 0.1f - 0.20f;
					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;
					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	
				}
				if(sta2_quit_active == false)
				if(sta2_yes_no_endturn == 0)
				if(sta2_yes_no_page_map == 2)
				{  
					new_counter[11].alpha = 1.0f;     
					new_counter[11].id = 0;

					if(sta2_is_first_level == true)
						sprintf(new_counter[11].word, "Click an enemy^pin to see^that unit$s^firing range."); 
					else
						sprintf(new_counter[11].word, "Some units^can also use^Specials."); 

					new_counter[11].x = hud[3].x + 0.042f;  
					new_counter[11].y =  hud[3].y + hud[3].height - 0.1f;

					new_counter[7].alpha = 1.0f;  
					new_counter[7].id = 0;
					sprintf(new_counter[7].word, "1 : OKAY"); 
					new_counter[7].x = hud[3].x + 0.042f;  
					new_counter[7].y =  hud[3].y + hud[3].height - 0.1f - 0.20f;
					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;
					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	
				}
				if(sta2_quit_active == false)
				if(sta2_yes_no_endturn == 1) 
				{  
					new_counter[11].alpha = 1.0f;       
					new_counter[11].id = 0; 

					sprintf(new_counter[11].word, "You have %i^moves left...^Continue?", sta2_player_moves); 

					new_counter[11].x = hud[3].x + 0.042f;  
					new_counter[11].y =  hud[3].y + hud[3].height - 0.1f; 
					  
					new_counter[7].alpha = 1.0f;    
					new_counter[7].id = 0;
					sprintf(new_counter[7].word, "1 : END TURN"); 
					new_counter[7].x = hud[3].x + 0.042f;  
					new_counter[7].y =  hud[3].y + hud[3].height - 0.1f - 0.18f;
					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;
					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	
				 
					new_counter[8].alpha = 1.0f;   
					new_counter[8].id = 0;
					sprintf(new_counter[8].word, "2 : CANCEL"); 
					new_counter[8].x = hud[3].x + 0.042f;  
					new_counter[8].y = hud[3].y + hud[3].height - 0.1f - 0.23f;
					new_counter[8].w = new_counter[8].x - 0.026f;   
					new_counter[8].z = new_counter[8].y - 0.015f;
					new_counter[8].box_width = strlen(new_counter[8].word)   *  0.026f;
					new_counter[8].box_height = new_counter[8].height - 0.015f;	
				}



			}
			else
			{
				new_counter[7].alpha = 0.0f;
				new_counter[8].alpha = 0.0f;
				new_counter[11].alpha = 0.0f;
				hud[3].alpha = 0.0f; 
			}

           if(title_sequence == 0)           
           {   

			    if(screen_mode == SCREEN_1610_WIDESCREEN)
				{
					for(int i=2;i<10;i++)  
						sprite[i].x+=0.04f;

					sprite[10].x+=0.04f;
					sprite[11].x+=0.04f;   
					sprite[16].x+=0.04f;

				} 

			    sta2_flash_co_power = 0;

			    sta2_yes_no_active = false;  
	
			    sprintf( new_counter[0].word, "1 : CO POWER"); 

			    new_counter[0].alpha = 0.0f;        
			    new_counter[0].id = 0;
		     
			    new_counter[0].x = -0.60f;       
			    new_counter[0].y = -0.34f;   	      

				new_counter[0].w = new_counter[0].x - 0.026f;   
				new_counter[0].z = new_counter[0].y - 0.015f;

				new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
				new_counter[0].box_height = new_counter[0].height - 0.015f;	

			    new_counter[1].alpha = 0.0f;        
			    new_counter[1].id = 0; 
		       
			    new_counter[1].x = -0.12f;        
			    new_counter[1].y = -0.34f;  	      

				new_counter[1].w = new_counter[1].x - 0.026f;    
				new_counter[1].z = new_counter[1].y - 0.015f;    

				new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
				new_counter[1].box_height = new_counter[1].height - 0.015f;	

				if(sta2_pressed_map == true)
				{
					sprintf( new_counter[1].word, "PRESS SPACE TO CANCEL"); 
					new_counter[1].x = -0.22f;
				}
				else
				{
					sprintf( new_counter[1].word, "2 : END TURN"); 
					new_counter[1].x = -0.12f;
				}

			    sprintf( new_counter[3].word, "3 : QUIT"); 

			    new_counter[3].alpha = 0.0f;        
			    new_counter[3].id = 0;  
		      
			    new_counter[3].x = +0.42f;      
			    new_counter[3].y = -0.34f;  	       

				new_counter[3].w = new_counter[3].x - 0.026f;   
				new_counter[3].z = new_counter[3].y - 0.015f;

				new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
				new_counter[3].box_height = new_counter[3].height - 0.015f;	

			    sta2_battle_ready = false; 

				if(sta2_turn == TURN_PLAYER)  
				if(sta2_pressed_map == false)
				if(sta2_player_moves <= 0 || sta2_ended_turn == true)
					sta2_change_turn = true;  

				if(sta2_turn == TURN_COMPUTER)    
				if(sta2_enemy_moves <= 0)  
					sta2_change_turn = true;    

				sta2_ended_turn = false;
				 
			    pins_start = no_sprites;     
			    sprite[12].alpha = 0.0f; 

				if(sta2_pressed_map == false)
			    if(sta2_change_turn == true)  
				{  

					sta2_reset_movement = true;

					disable_buffs = false;

					sta2_no_of_turns++;

					switch(sta2_turn)      
					{  
						case TURN_NONE:		// left mouse button
							 sta2_turn = TURN_PLAYER;
							 STA2_MODE = MODE_MOVING; 
							 if(UNITS_CAN_MOVE_MORE_THAN_ONCE == 0)
								sta2_player_moves = sta2_player_count;
							 else
							 {
								if(sta2_is_epic_battle == true)
								    sta2_player_moves = STA2_MOVES_IN_EPIC_PLY; 
								else
									sta2_player_moves = STA2_MOVES_IN_QUICK_PLY;
							 }
							 sprite[12].alpha = 1.0f;
							 Set_Sprite(12, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
							 disable_buffs = true;
						break;
						case TURN_PLAYER:		// left mouse button
							 sta2_turn = TURN_COMPUTER;   
							 STA2_MODE = MODE_NONE; 
							 if(UNITS_CAN_MOVE_MORE_THAN_ONCE == 0)
								sta2_enemy_moves = sta2_enemy_count;
							 else 
							 {
								if(sta2_is_epic_battle == true)
								    sta2_enemy_moves = STA2_MOVES_IN_EPIC_EMY; 
								else
									sta2_enemy_moves = STA2_MOVES_IN_QUICK_EMY;
							 }
							 sprite[12].alpha = 1.0f;
							 Set_Sprite(12, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
						break;
						case TURN_COMPUTER:		// left mouse button
							 sta2_turn = TURN_PLAYER;
							 STA2_MODE = MODE_MOVING;
							 if(UNITS_CAN_MOVE_MORE_THAN_ONCE == 0)
								sta2_player_moves = sta2_player_count;
							 else
							 {
								if(sta2_is_epic_battle == true)
								    sta2_player_moves += STA2_MOVES_IN_EPIC_PLY; 
								else
									sta2_player_moves += STA2_MOVES_IN_QUICK_PLY;
							 }
							 sprite[12].alpha = 1.0f;
							 Set_Sprite(12, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
							 disable_buffs = true;
						break;
					}
					 
					if(sta2_turn == TURN_COMPUTER)
						title_timer = (int)TimerGetTime()+1500;
					else
						title_timer = (int)TimerGetTime()+2000;
					     
				} 

				// Remove any active buffs...
				if(disable_buffs == true)
				{ 

					for(int j = 0;j< STA2_PACKS_LIMIT;j++)     
						sta2_pack[j].special_charge = 0;

					disable_buffs = false;
				}

				total_enemy_health = 0;
				total_player_health = 0; 

				sta2_emy_pin_map = -1; 

			   // Create sprites...
			   for(int i = 0; i < no_of_map_pins;i++)       
			   {
				   // current_unit = PIN_UNIT5;
				   if(sta2_cpu_map_unit == i && sta2_pressed_map == false)
					   sprite[no_sprites].value1 = 1001;
				   else
					   sprite[no_sprites].value1 = -1;

				   if(sta2_pressed_map == true)
				   if(map_pins_type[i] == current_unit) 
					   sprite[no_sprites].value1 = 1001;

				   sprite[no_sprites].light = 1.0f; 

				   sprite[no_sprites].type = NON;  
				   sprite[no_sprites].priority = 2;    
            
				   sprite[no_sprites].width = 0.1f;   
				   sprite[no_sprites].height = 0.1f; 
				   sprite[no_sprites].box_width = 0.05f; 
				   sprite[no_sprites].box_height = 0.05f; 

				   rad_width  = sprite[0].box_width;          
				   rad_height = sprite[0].box_height;  
                   
				   rad_x = sprite[0].w - sprite[no_sprites].width/2;      
				   rad_y = sprite[0].z - sprite[no_sprites].height/2;                

				   rad_x += rad_width * map_pins_x[i]; 
				   rad_y += rad_height * map_pins_y[i];  

				   sprite[no_sprites].depth = 0.0f; 
				    
				   sprite[no_sprites].x = rad_x;  
				   sprite[no_sprites].y = rad_y;  

				   sprite[no_sprites].w = sprite[no_sprites].x + 0.025f; 
				   sprite[no_sprites].z = sprite[no_sprites].y + 0.025f; 

				   sprite[no_sprites].alpha = 1.0f;

				   sprite[no_sprites].priority = 3;

				   sprite[no_sprites].mouseover = false;
				    
				   sprite[no_sprites].turn_off = false;  

				   sprite[no_sprites].type = NON;

				   sprite[no_sprites].id = 9;   
				    
					sprite[no_sprites].fx_id = animation_fx[sprite[no_sprites].id];

					sprite[no_sprites].hit_by_bullet = map_pins_unit_moved[i];  

					sprite[no_sprites].movement = map_pins_movement[i];

					sprite[no_sprites].value3 = map_pins_type[i];  

					sprite[no_sprites].value2 = map_pins_roster[i];  

					sprite[no_sprites].return_fire = map_pins_defend[i]; 

					sprite[no_sprites].sector = map_pins_sector_type[i]; 
					 
					sprite[no_sprites].score = map_pins_score[i]; 

					sprite[no_sprites].angle = map_pins_angle[i];

					sprite[no_sprites].name = map_pins_names[i];
					 
					sprite[no_sprites].rank = map_pins_rank[i];  

					pack_id = -1;

					if(map_pins_type[i] != PIN_ENEMY)
					if(sprite[no_sprites].value2 >= 0)
						pack_id = sta2_squad[sprite[no_sprites].value2].wp;

				    // Joint...  
					if(map_pins_type[i] != PIN_ENEMY) 
				    if(pack_id > -1)   
				    if(sta2_pack[pack_id].special == PACK_SPECIAL_MAGICHERB)      
				    if(sta2_pack[pack_id].special_charge > 0)
				    {
					  map_pins_score[i] += (int)((float)Calculate_TotalScore(no_sprites) * 0.03f); 
					  if(map_pins_score[i] > Calculate_TotalScore(no_sprites))
						  map_pins_score[i] = Calculate_TotalScore(no_sprites);
					  DamageNumber( no_sprites, (int)((float)Calculate_TotalScore(no_sprites) * 0.03f), STA2_DAMAGE_HP );
					  sprite[no_sprites].score = map_pins_score[i];
				    }
					     
					if(map_pins_type[i] != PIN_ENEMY)              
					{  
						if(sprite[no_sprites].sector == UNIT_GUNNER)
							sprite[no_sprites].anim = 0;  // Yellow dot
						if(sprite[no_sprites].sector == UNIT_HEAVY)
							sprite[no_sprites].anim = 2;  // Yellow dot
						if(sprite[no_sprites].sector == UNIT_SNIPER)
							sprite[no_sprites].anim = 22;  // Yellow dot 
						if(sprite[no_sprites].sector == UNIT_MORTAR)
							sprite[no_sprites].anim = 24;  // Yellow dot

						if(pack_id > -1) 
						if(sta2_pack[pack_id].special != PACK_SPECIAL_NONE) 
   				        if(sta2_pack[pack_id].special_charge > 0)
						{
							if(sprite[no_sprites].sector == UNIT_GUNNER) 
								sprite[no_sprites].anim = 52;  // Yellow pulsating dot // 52
							if(sprite[no_sprites].sector == UNIT_HEAVY)
								sprite[no_sprites].anim = 56;  // Yellow pulsating dot
							if(sprite[no_sprites].sector == UNIT_SNIPER)
								sprite[no_sprites].anim = 60; // Yellow pulsating dot
							if(sprite[no_sprites].sector == UNIT_MORTAR)
								sprite[no_sprites].anim = 64; // Yellow pulsating dot
						}

						total_player_health += sprite[no_sprites].score;

					}  
					   
				    if(map_pins_type[i] == PIN_ENEMY)        
				    { 
						  
						// Remove enemy health...  
						if(map_pins_score[i] > 0)
						if(sta2_power_result == STA2_POWER_WIN)    
						{
							  
							script_damage = 1+rand()%(30 + (sta2_officer_rank*30)); // 1+rand()%15

							map_pins_score[i] -= script_damage;

							if(map_pins_score[i] < 1)  
								map_pins_score[i] = 1;

							sprite[no_sprites].score = map_pins_score[i];

							DamageNumber( no_sprites, script_damage, STA2_DAMAGE_NORM );
							 
						}

					   total_enemy_health += sprite[no_sprites].score;

						if(sprite[no_sprites].sector == UNIT_DOG)
							sprite[no_sprites].anim = 48;  // Yellow dot
						if(sprite[no_sprites].sector == UNIT_GUNNER)
							sprite[no_sprites].anim = 4;  // Yellow dot
						if(sprite[no_sprites].sector == UNIT_HEAVY)
							sprite[no_sprites].anim = 26;  // Yellow dot
						if(sprite[no_sprites].sector == UNIT_SNIPER)
							sprite[no_sprites].anim = 28;  // Yellow dot
						if(sprite[no_sprites].sector == UNIT_MORTAR)
							sprite[no_sprites].anim = 30;  // Yellow dot
						if(sprite[no_sprites].sector == UNIT_CHIEF)
							sprite[no_sprites].anim = 68;  // Yellow dot

					}     
					   
					// Low health
					if(sprite[no_sprites].score <= (Calculate_TotalScore(no_sprites)/4) ) 
					{
						if(map_pins_type[i] == PIN_ENEMY) 
						{
							if(sprite[no_sprites].sector == UNIT_DOG)
								sprite[no_sprites].anim = 50;  // Yellow dot
							if(sprite[no_sprites].sector == UNIT_GUNNER)
								sprite[no_sprites].anim = 32;  // Yellow dot
							if(sprite[no_sprites].sector == UNIT_HEAVY)
								sprite[no_sprites].anim = 34;  // Yellow dot
							if(sprite[no_sprites].sector == UNIT_SNIPER)
								sprite[no_sprites].anim = 36;  // Yellow dot
							if(sprite[no_sprites].sector == UNIT_MORTAR)
								sprite[no_sprites].anim = 38;  // Yellow dot
							if(sprite[no_sprites].sector == UNIT_CHIEF)
								sprite[no_sprites].anim = 70;  // Yellow dot
						}
						else    
						{
							if(sprite[no_sprites].sector == UNIT_GUNNER)
								sprite[no_sprites].anim = 40;  // Yellow dot
							if(sprite[no_sprites].sector == UNIT_HEAVY)
								sprite[no_sprites].anim = 42;  // Yellow dot
							if(sprite[no_sprites].sector == UNIT_SNIPER)
								sprite[no_sprites].anim = 44;  // Yellow dot
							if(sprite[no_sprites].sector == UNIT_MORTAR)
								sprite[no_sprites].anim = 46;  // Yellow dot

							if(pack_id > -1) 
							if(sta2_pack[pack_id].special != PACK_SPECIAL_NONE)  
							if(sta2_pack[pack_id].special_charge > 0)
							{
								if(sprite[no_sprites].sector == UNIT_GUNNER) 
									sprite[no_sprites].anim = 54;  // Yellow pulsating dot // 54
								if(sprite[no_sprites].sector == UNIT_HEAVY)
									sprite[no_sprites].anim = 58;  // Yellow pulsating dot
								if(sprite[no_sprites].sector == UNIT_SNIPER)
									sprite[no_sprites].anim = 62; // Yellow pulsating dot
								if(sprite[no_sprites].sector == UNIT_MORTAR)
									sprite[no_sprites].anim = 66; // Yellow pulsating dot
							}

						}
					}

					if(map_pins_type[i] != PIN_ENEMY)
					if(sprite[no_sprites].score <= 1)  
					{
						sprite[no_sprites].anim = 6;  // Black dot
						sprite[no_sprites].priority = 4;
					}

					if(map_pins_type[i] == PIN_ENEMY)
					if(sprite[no_sprites].score <= 0)
					{
						sprite[no_sprites].anim = 6; // Black dot  
						sprite[no_sprites].priority = 4;
					}

					sprite[no_sprites].cur = 0;     

					sprite[no_sprites].cur_time = 0;
                         
					sprite[no_sprites].anim_state = LOOP;
#ifndef DREAMCAST
					sprite[no_sprites].frame = a_texture[sprite[no_sprites].fx_id].anims[sprite[no_sprites].anim][sprite[no_sprites].cur];
#else
					sprite[no_sprites].frame = a_texture_get_anims_secondlayer(sprite[no_sprites].fx_id, sprite[no_sprites].anim, sprite[no_sprites].cur);
#endif
            
					sprite[no_sprites].base_anim = sprite[no_sprites].anim;

					Set_Sprite(no_sprites, sprite[no_sprites].anim, LOOP, ANIM_SPRITE, ANIM_WALKING);

					no_sprites++;      
					       
			    }   

				index = no_sprites; 

				// Create direction arrows for pins...
			    for(int i = 0; i < index;i++) 
				if(sprite[i].id == 9 && sprite[i].alpha == 1.0f)
			    {      

					sta2_pin_is_dead=false;

					if(sprite[i].value3 != PIN_ENEMY)
					if(sprite[i].score <= 1)  
					    sta2_pin_is_dead = true;

					if(sprite[i].value3 == PIN_ENEMY)
					if(sprite[i].score <= 0)  
					    sta2_pin_is_dead = true;

					sprite[no_sprites].id = 9; 

					sprite[no_sprites].light = 1.0f;

					sprite[no_sprites].priority = 1;

					if(sta2_pin_is_dead == true)  
					    sprite[no_sprites].priority = 4;

					sprite[no_sprites].fx_id = animation_fx[sprite[no_sprites].id];

				    sprite[no_sprites].depth = 0.0f;
				    
				    sprite[no_sprites].x = sprite[i].x;  
				    sprite[no_sprites].y = sprite[i].y;  

				    sprite[no_sprites].w = sprite[i].w; 
				    sprite[no_sprites].z = sprite[i].z; 

				    sprite[no_sprites].width = sprite[i].width; 
				    sprite[no_sprites].height = sprite[i].height; 
				    sprite[no_sprites].box_width = sprite[i].box_width; 
				    sprite[no_sprites].box_height = sprite[i].box_height; 

				    sprite[no_sprites].alpha = 1.0f; 

					sprite[no_sprites].type = NON;

				    sprite[no_sprites].mouseover = false;
				    
				    sprite[no_sprites].turn_off = false; 

					sprite[no_sprites].anim = 12 + Convert_Angle_To_Dir(sprite[i].angle);

					sprite[no_sprites].cur = 0;     

					sprite[no_sprites].cur_time = 0;
                         
					sprite[no_sprites].anim_state = LOOP;
                
#ifndef DREAMCAST
					sprite[no_sprites].frame = a_texture[sprite[no_sprites].fx_id].anims[sprite[no_sprites].anim][sprite[no_sprites].cur];
#else
					sprite[no_sprites].frame = a_texture_get_anims_secondlayer(sprite[no_sprites].fx_id, sprite[no_sprites].anim, sprite[no_sprites].cur);
#endif
            
					sprite[no_sprites].base_anim = sprite[no_sprites].anim;

					Set_Sprite(no_sprites, sprite[no_sprites].anim, LOOP, ANIM_SPRITE, ANIM_WALKING);
					 
					no_sprites++;        
					 
					// Create a defend pin...
					if(sprite[i].value3 != PIN_ENEMY) 
					if(sta2_pin_is_dead == false)  
					if(sprite[i].return_fire == true)
					{
						sprite[no_sprites].id = 9;

						sprite[no_sprites].light = 1.0f;

						sprite[no_sprites].priority = 1;

						sprite[no_sprites].fx_id = animation_fx[sprite[no_sprites].id];

						sprite[no_sprites].depth = 0.0f;
				    
						sprite[no_sprites].x = sprite[i].x;  
						sprite[no_sprites].y = sprite[i].y;  

						sprite[no_sprites].w = sprite[i].w; 
						sprite[no_sprites].z = sprite[i].z; 

						sprite[no_sprites].width = sprite[i].width; 
						sprite[no_sprites].height = sprite[i].height; 
						sprite[no_sprites].box_width = sprite[i].box_width; 
						sprite[no_sprites].box_height = sprite[i].box_height; 

						sprite[no_sprites].alpha = 1.0f;  

						sprite[no_sprites].type = NON;

						sprite[no_sprites].mouseover = false;
				    
						sprite[no_sprites].turn_off = false; 

						sprite[no_sprites].anim = 21;

						sprite[no_sprites].cur = 0;   

						sprite[no_sprites].cur_time = 0;   
                         
						sprite[no_sprites].anim_state = LOOP;
                
#ifndef DREAMCAST
						sprite[no_sprites].frame = a_texture[sprite[no_sprites].fx_id].anims[sprite[no_sprites].anim][sprite[no_sprites].cur];
#else
						sprite[no_sprites].frame = a_texture_get_anims_secondlayer(sprite[no_sprites].fx_id, sprite[no_sprites].anim, sprite[no_sprites].cur);
#endif
            
						sprite[no_sprites].base_anim = sprite[no_sprites].anim;

						Set_Sprite(no_sprites, sprite[no_sprites].anim, LOOP, ANIM_SPRITE, ANIM_WALKING);

						no_sprites++;   
   
					}   
					 
					// Overhead selection arrows...
					if(sta2_turn == TURN_COMPUTER || sta2_pressed_map == true)   
					if(sprite[i].value1 == 1001)  
					{
						sprite[no_sprites].id = 9;   

						sprite[no_sprites].light = 1.0f;

						sprite[no_sprites].priority = 1;

						sprite[no_sprites].fx_id = animation_fx[sprite[no_sprites].id];

						sprite[no_sprites].depth = 0.0f;
				    
						sprite[no_sprites].x = sprite[i].x;  
						sprite[no_sprites].y = sprite[i].y;  

						sprite[no_sprites].w = sprite[i].w; 
						sprite[no_sprites].z = sprite[i].z; 

						sprite[no_sprites].width = sprite[i].width; 
						sprite[no_sprites].height = sprite[i].height; 
						sprite[no_sprites].box_width = sprite[i].box_width; 
						sprite[no_sprites].box_height = sprite[i].box_height; 

						sprite[no_sprites].alpha = 1.0f;  

						sprite[no_sprites].type = NON;

						sprite[no_sprites].mouseover = false; 
				    
						sprite[no_sprites].turn_off = false; 

						sprite[no_sprites].anim = 12;

						sprite[no_sprites].cur = 0;    

						sprite[no_sprites].cur_time = 0;
                         
						sprite[no_sprites].anim_state = LOOP;
                
#ifndef DREAMCAST
						sprite[no_sprites].frame = a_texture[sprite[no_sprites].fx_id].anims[sprite[no_sprites].anim][sprite[no_sprites].cur];
#else
						sprite[no_sprites].frame = a_texture_get_anims_secondlayer(sprite[no_sprites].fx_id, sprite[no_sprites].anim, sprite[no_sprites].cur);
#endif
            
						sprite[no_sprites].base_anim = sprite[no_sprites].anim;

						Set_Sprite(no_sprites, sprite[no_sprites].anim, LOOP, ANIM_SPRITE, ANIM_WALKING);

						no_sprites++; 


					}


				}

				if(sta2_power_result == STA2_POWER_WIN)
					wound_sfx = true; 

				sta2_power_result = STA2_POWER_NONE; 

				if(sta2_turn == TURN_COMPUTER) 
					title_timer = (int)TimerGetTime()+1000;

                title_sequence++;    
				 
				// All enemies are dead...
				if(total_enemy_health == 0 || total_player_health == 0)
				{
					cheer_sfx = true;

					sta2_battle_load_outcome = BATTLE_VICTORY;

					sprite[12].alpha = 0.0f;  
					 
					if(total_enemy_health == 0)
						sta2_next_event = EVENT_VICTORY;
					if(total_player_health == 0)
						sta2_next_event = EVENT_DEFEAT;

					title_timer = (int)TimerGetTime()+2000;
					title_sequence = 3;

				}  

           }     

		   if(title_sequence == 3) 
		   if((int)TimerGetTime() > title_timer) 
		   {
				episode = 1;  
				scene   = 2; 

				next_scene = true;

			    title_sequence++;

		   } 

		   if(title_sequence == 1) 
		   if( (int)TimerGetTime() > title_timer) 
		   { 
			   sta2_esc_pressed = false;
			   sta2_1_pressed = false;
			   sta2_2_pressed = false;   
			   sta2_3_pressed = false; 
			   sta2_4_pressed = false;
			   sta2_5_pressed = false;
			   sta2_6_pressed = false;
			   sta2_7_pressed = false; 

			   if(sta2_playing_tutorial == true) 
			   if(sta2_yes_no_page_map == 0)
				   sta2_yes_no_active = true;

			   sta2_cp_stars_count = 0;
			   start_timer = (int)TimerGetTime() + STA2_CP_STARS_TIME;

			   title_sequence++;

		   } 

		   if(title_sequence == 2)
		   {  
			     
				testX = hud_mouseX - (-camX);                                                   
				testY = hud_mouseY - (-camY);    

				if(sta2_turn != TURN_COMPUTER)  
				{
					new_counter[0].alpha = 1.0f;
					new_counter[1].alpha = 1.0f;
					new_counter[3].alpha = 1.0f;
				}  

				if(sta2_pressed_map == true)
				{
					new_counter[0].alpha = 0.0f;
					new_counter[1].alpha = 1.0f;
					new_counter[3].alpha = 0.0f;
				}  

			//	new_counter[0].id = 0; // CO Power 
				new_counter[1].id = 0; // End turn
				new_counter[3].id = 0; // Quit

				if(sta2_yes_no_active == true)  
				{
					new_counter[0].id = 5; // CO Power
					new_counter[1].id = 5; // End turn
					new_counter[3].id = 5; // Quit
				}  

				if(sta2_player_moves < 1 || sta2_has_officer == false || sta2_power_bar < 100.0f)
					new_counter[0].id = 5; // CO Power
				else
			    {
				   if((int)TimerGetTime() > sta2_flash_co_power)
				   {
					   if(new_counter[0].id == 0)
						   new_counter[0].id = 5;
					   else
						   new_counter[0].id = 0;

					   sta2_flash_co_power = (int)TimerGetTime()+250;
				   }
			    }

				// YES...
				if(sta2_yes_no_active == true)
				if(sta2_turn != TURN_COMPUTER)
				if(new_counter[7].alpha == 1.0f)
				if(( testX < (new_counter[7].w + new_counter[7].box_width) )
				&&( testX > new_counter[7].w)                            
				&&( testY < (new_counter[7].z + new_counter[7].box_height) )
				&&( testY > new_counter[7].z) || sta2_1_pressed == true)   
				{ 
					new_counter[7].id = 4;      

					if(mouseleft == true || DX_SHOOT == true || sta2_1_pressed == true) 
					{  
						sta2_1_pressed = false; 
						sta2_2_pressed = false; 
						sta2_3_pressed = false; 
						mouseleft = false;       
						DX_SHOOT = false;      

						if(sta2_quit_active == true)
						{ 

							if(sta2_playing_tutorial == false)
							{
								sprintf( temp_string.string, "data/save/sta2");
								STA2_SaveLevel(temp_string);
							}

							episode = 0;
							scene = 1;

							next_scene = true;

							title_sequence++;						 
						}
						else 
						{
							if(sta2_yes_no_active == true && sta2_yes_no_endturn == 1) // Still have moves left...
							{

								sta2_yes_no_active = false;

								sta2_yes_no_endturn = 0;

								sta2_quit_active = false;
								sta2_reset_movement = true; 

								sta2_ended_turn = true;
								sta2_change_turn = true; 

								episode = 1;
								scene = 1;

								next_scene = true;

								title_sequence++;
							}
							else
							{
								sta2_yes_no_page_map++;
								if(sta2_yes_no_page_map == 3)
								{
									sta2_yes_no_active = false;
								}
							}

						}
					}
				}  

				// NO...
				if(sta2_yes_no_active == true)
				if(sta2_turn != TURN_COMPUTER)
				if(new_counter[8].alpha == 1.0f)
				if(( testX < (new_counter[8].w + new_counter[8].box_width) )
				&&( testX > new_counter[8].w)                            
				&&( testY < (new_counter[8].z + new_counter[8].box_height) )
				&&( testY > new_counter[8].z) || sta2_2_pressed == true)   
				{ 
					new_counter[8].id = 4;    

					if(mouseleft == true || DX_SHOOT == true || sta2_2_pressed == true) 
					{  
						sta2_1_pressed = false; 
						sta2_2_pressed = false; 
						sta2_3_pressed = false; 
						mouseleft = false;         
						DX_SHOOT = false;    

						sta2_quit_active = false;
						sta2_yes_no_active = false;

						sta2_yes_no_endturn = 0;

						hud[3].alpha = 0.0f; 
						 
					}
				}  

				// CO Power...
				if(sta2_yes_no_active == false) 
				if(sta2_turn != TURN_COMPUTER)
				if(sta2_player_moves >= 1 && sta2_has_officer == true && sta2_power_bar >= 100.0f)
				if(new_counter[0].alpha == 1.0f)
				if(( testX < (new_counter[0].w + new_counter[0].box_width) )
				&&( testX > new_counter[0].w)                            
				&&( testY < (new_counter[0].z + new_counter[0].box_height) )
				&&( testY > new_counter[0].z) || sta2_1_pressed == true)   
				{ 
					new_counter[0].id = 4;         

					if(mouseleft == true || DX_SHOOT == true || sta2_1_pressed == true) 
					{  

						mouseleft = false; 
						DX_SHOOT = false; 
						sta2_1_pressed = false; 
						sta2_2_pressed = false; 
						sta2_3_pressed = false; 

						sta2_power_result = STA2_POWER_WIN;

						sta2_player_moves--;          

						sta2_power_bar = 0.0f;

						scene = 15;
						episode = 1;  

						next_scene = true;
						 
					}
				}    
				 
				// End turn...
				if(sta2_yes_no_active == false)
				if(sta2_turn != TURN_COMPUTER) 
				if(new_counter[1].alpha == 1.0f)
				if(( testX < (new_counter[1].w + new_counter[1].box_width) )
				&&( testX > new_counter[1].w)                            
				&&( testY < (new_counter[1].z + new_counter[1].box_height) )
				&&( testY > new_counter[1].z) 
				|| (sta2_2_pressed == true && sta2_pressed_map == false) || (sta2_space_pressed == true && sta2_pressed_map == true) 
				|| (sta2_tab_pressed == true && sta2_pressed_map == true) )   
				{ 
					new_counter[1].id = 4;          

					if(mouseleft == true || DX_SHOOT == true 
					|| (sta2_2_pressed == true && sta2_pressed_map == false) 
					|| (sta2_space_pressed == true && sta2_pressed_map == true)
					|| (sta2_tab_pressed == true && sta2_pressed_map == true)) 
					{  
						 
						mouseleft = false;  
						DX_SHOOT = false;  
						sta2_1_pressed = false; 
						sta2_2_pressed = false; 
						sta2_3_pressed = false; 
						sta2_space_pressed = false; 
						sta2_tab_pressed = false;

						if(sta2_pressed_map == false)  
						{  
							   
							if(sta2_player_moves != 0)
							{
								sta2_yes_no_active = true;
								sta2_yes_no_endturn = 1;
							} 
							else
							{ 
								sta2_reset_movement = true; 

								sta2_ended_turn = true;
								sta2_change_turn = true; 

								episode = 1;
								scene = 1;

								next_scene = true;

								title_sequence++;
							}
						}

						if(sta2_pressed_map == true)
						{
							if(sta2_is_epic_battle == true)
							{
								episode = 4;   
								scene = 0;
							}
							else
							{ 
								episode = 2;   
								scene = 0; 
							}

							current_spawn = 0;  

							in_stats = true;
							next_scene = true;

							title_sequence++;
						}

						
 
					} 
				}   
				 
				// Quit game...
				if(sta2_yes_no_active == false)
				if(sta2_turn != TURN_COMPUTER)
				if(new_counter[3].alpha == 1.0f)
				if(( testX < (new_counter[3].w + new_counter[3].box_width) )
				&&( testX > new_counter[3].w)                            
				&&( testY < (new_counter[3].z + new_counter[3].box_height) )
				&&( testY > new_counter[3].z) || sta2_3_pressed == true || sta2_esc_pressed == true)   
				{ 
					new_counter[3].id = 4;         

					if(mouseleft == true || DX_SHOOT == true || sta2_3_pressed == true || sta2_esc_pressed == true) 
					{  
						   
						sta2_esc_pressed = false; 
						mouseleft = false; 
						DX_SHOOT = false;     
						sta2_1_pressed = false; 
						sta2_2_pressed = false; 
						sta2_3_pressed = false; 

						sta2_quit_active = true;
						sta2_yes_no_active = true; 
						 
					}  
				}   
				 
           //    if(title_timer != 0) 
			   if(sta2_change_turn == true) 
			   {     

				   sta2_change_turn = false; 
				   sprite[12].alpha = 0.0f;    // Player turn gfx..

				   if(sta2_turn == TURN_COMPUTER)  
				   {
						if(sta2_is_epic_battle == true)
						{
							episode = 4;   
							scene = 0;
						}
						else
						{
							episode = 2;   
							scene = 0;
						}
						 
						current_spawn = 0;     

						#if WALK_BUG_TEST == 0
						sta2_enemy_moves--; 
						#endif

						if(sta2_enemy_moves < 0) 
							sta2_enemy_moves = 0;

						in_stats = true;
						next_scene = true;

						title_sequence++;
				   }
			   } 
			   else
			   {
				   if(sta2_turn == TURN_COMPUTER)  
				   {
						if(sta2_is_epic_battle == true)
						{
							episode = 4;   
							scene = 0;
						}
						else
						{
							episode = 2;   
							scene = 0;
						}

						current_spawn = 0;    

						#if WALK_BUG_TEST == 0
							sta2_enemy_moves--; 
						#endif	

						if(sta2_enemy_moves < 0) 
							sta2_enemy_moves = 0;
						   
						in_stats = true;
						next_scene = true;

						title_sequence++;
				   }
			   }

		   } 

		   if( (int)TimerGetTime() > title_timer || run_swipe == false)
		   if(sta2_turn == TURN_PLAYER)    
		   { 
			   if(sta2_player_moves > 8)    
				   sta2_player_moves = 8;       
			    
			   if(run_swipe == false)
			   { 
				    for(int i = 0; i < sta2_player_moves;i++)
					{
						Set_Sprite(2+i, 0, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING);
						sprite[2+i].alpha = 1.0f;
					}
			   }
				
			   if(run_swipe == true)
			   {

				   if(sta2_cp_stars_count <= 7)
				   if(run_swipe == true)
				   if((int)TimerGetTime() > start_timer)   
				   {
					   Set_Sprite(2+sta2_cp_stars_count, 1, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING);

					   start_timer = (int)TimerGetTime() + STA2_CP_STARS_TIME;
					   sta2_cp_stars_count++;
				   }

				   if(sta2_cp_stars_count > sta2_player_moves)
					   sta2_cp_stars_count = sta2_player_moves;

				   for(int i = 0; i < sta2_cp_stars_count;i++)
					   sprite[2+i].alpha = 1.0f;

			   }
		   } 
		    
	//	   if( (int)TimerGetTime() > title_timer)
		   if(sta2_turn == TURN_COMPUTER)   
		   {  
			    
			   if(sta2_enemy_moves > 8)    
				   sta2_enemy_moves = 8;

			   if(run_swipe == false)
			   {
				    for(int i = 0; i < sta2_enemy_moves;i++)
					{
						Set_Sprite(2+i, 0, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING);
						sprite[2+i].alpha = 1.0f;
					}
			   }
				
			   if(run_swipe == true)
			   {

				   if(sta2_cp_stars_count <= 7)
				   if((int)TimerGetTime() > start_timer) 
				   {
					   Set_Sprite(2+sta2_cp_stars_count, 1, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING);

					   start_timer = (int)TimerGetTime() + STA2_CP_STARS_TIME;
					   sta2_cp_stars_count++;
				   }

				   if(sta2_cp_stars_count > sta2_enemy_moves)
					   sta2_cp_stars_count = sta2_enemy_moves;

				   for(int i = 0; i < sta2_cp_stars_count;i++)
					   sprite[2+i].alpha = 1.0f;
			   }
		   }

		   if(sta2_pressed_map == true)
		   {
			   for(int i = 2; i < 13;i++)
				   sprite[i].alpha = 0.0f;
		   }
		       
		   new_counter[4].alpha = 0.0f;     
		   new_counter[5].alpha = 0.0f;

		   index = -1; 

		    if(sta2_yes_no_active == false)
		    if(sta2_change_turn == false)
		    if(sprite[10].alpha == 1.0f)                   
		    if(( mouseX < (sprite[10].w + sprite[10].box_width) )
			&&( mouseX > sprite[10].w)                            
			&&( mouseY < (sprite[10].z + sprite[10].box_height) )
			&&( mouseY > sprite[10].z))  
			{    
				    
				new_counter[4].alpha = 1.0f;                
					    
				new_counter[4].x = mouseX + 0.13f;                     
				new_counter[4].y = mouseY;  

				new_counter[5].alpha = 1.0f;               
					   
				new_counter[5].x = mouseX + 0.1f;                 
				new_counter[5].y = mouseY;  

				sprintf( new_counter[5].word, "@");
    			sprintf( new_counter[4].word, "CO POWER:%i&", (int)sta2_power_bar);	 

			}
		    
           // Map pins...
		   if(sta2_yes_no_active == false)
		   for(int i = pins_start;i< pins_start+no_of_map_pins;i++)
		   {

			   Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

			   if(sta2_change_turn == false)
			   if(sprite[i].alpha == 1.0f)                   
			   if(( mouseX < (sprite[i].w + sprite[i].box_width) )
			   &&( mouseX > sprite[i].w)                            
			   &&( mouseY < (sprite[i].z + sprite[i].box_height) )
			   &&( mouseY > sprite[i].z))        
			   {     
				     
				    // Firing range...   
				    if(sta2_turn == TURN_PLAYER)
				    if(sprite[i].value3 == PIN_ENEMY) 
					if(sprite[i].sector != UNIT_DOG)
					if(sprite[i].sector != UNIT_SNIPER)
					if(sprite[i].sector != UNIT_MORTAR)
					if(sprite[i].score > 0) 
					{ 
						sprite[13].alpha = 1.0f;
						sprite[13].x = sprite[i].x + sprite[i].width/2;
						sprite[13].y = sprite[i].y + sprite[i].height/2;

						sprite[13].x -= sprite[13].width/2; 
						sprite[13].y -= sprite[13].height/2; 

						sprite[13].anim = (Convert_Angle_To_Dir(sprite[i].angle)) - 1;

						Set_Sprite(13, sprite[13].anim, LOOP, ANIM_SPRITE, ANIM_WALKING);

					}              
				            
				    // Movement range...         
				    if(sta2_turn == TURN_PLAYER)  
					if(sprite[i].score > 1 || sprite[i].value3 == PIN_ENEMY)
					if(sprite[i].score > 0)
					{   

						sprite[14].alpha = 1.0f;
						sprite[14].x = sprite[i].x + sprite[i].width/2;
						sprite[14].y = sprite[i].y + sprite[i].height/2;

						sprite[14].x -= sprite[14].width/2;  
						sprite[14].y -= sprite[14].height/2;   

						movement_limit = (float)sprite[i].movement / 40.0f;
						movement_limit *= 7.0f;

						sprite[14].anim = (int)movement_limit;

						Set_Sprite(14, sprite[14].anim, LOOP, ANIM_SPRITE, ANIM_WALKING);

					} 

					new_counter[4].alpha = 1.0f;               
					   
					new_counter[4].x = mouseX + 0.13f;                  
					new_counter[4].y = mouseY;     
					 
					new_counter[5].alpha = 1.0f;               
					    
					new_counter[5].x = mouseX + 0.1f;                      
					new_counter[5].y = mouseY;   
					 
					sprintf( new_counter[5].word, "@");    

					if(sprite[i].value2 >= 0)
						pack_id = sta2_squad[sprite[i].value2].wp;

					if(sprite[i].value3 == PIN_ENEMY)  
					{ 
						if(sprite[i].sector != UNIT_DOG && sprite[i].sector != UNIT_CHIEF)
    						sprintf( new_counter[4].word, "HP:%i/%i^%s LVL%i^", sprite[i].score, Calculate_TotalScore(i), sta2_emy_names[sprite[i].name].string, sprite[i].rank);	 
						if(sprite[i].sector == UNIT_DOG)
    						sprintf( new_counter[4].word, "HP:%i/%i^DOG LVL%i^", sprite[i].score, Calculate_TotalScore(i), sprite[i].rank);	 
						if(sprite[i].sector == UNIT_CHIEF)
    						sprintf( new_counter[4].word, "HP:%i/%i^HELMUTT LVL%i^", sprite[i].score, Calculate_TotalScore(i), sprite[i].rank);	 
					}
					else 
					{      
						if(sprite[i].value2 != -1)   
						{ 
							   
							if(sprite[i].score == 1)
							{
							    sprintf( new_counter[4].word, "WOUNDED..^%s LVL%i^", sta2_squad[sprite[i].value2].string, sprite[i].rank);
							}
							else                   
							{
								 
							//	sprintf( new_counter[4].word, "HP:%i/%i:XP/%i^", sprite[i].score, Calculate_TotalScore(i), sta2_squad[sprite[i].value2].xp);
								sprintf( new_counter[4].word, "HP:%i/%i^", sprite[i].score, Calculate_TotalScore(i));

								if(pack_id > -1) 
								if(sta2_pack[pack_id].extra == PACK_EXTRA_MEDKIT) 
								if(sta2_pack[pack_id].extra_charge > 0)
								{ 
									sprintf(string_value, "");
									sprintf(string_value, "£");
									strcat(new_counter[4].word, string_value);
								}  

								if(pack_id > -1) 
								if(sta2_pack[pack_id].extra == PACK_EXTRA_GRENADE) 
								if(sta2_pack[pack_id].extra_charge > 0)
								{
									sprintf(string_value, "");  
									sprintf(string_value, "¥");
									strcat(new_counter[4].word, string_value);
								} 

								if(pack_id > -1) 
								if(sta2_pack[pack_id].special != PACK_SPECIAL_NONE)
								{ 
									sprintf(string_value, ""); 

									if(sta2_pack[pack_id].special == PACK_SPECIAL_SCOPE) 
										sprintf(string_value, "¢");
									if(sta2_pack[pack_id].special == PACK_SPECIAL_SHIELD) 
										sprintf(string_value, "¤");
									if(sta2_pack[pack_id].special == PACK_SPECIAL_DUMDUM) 
										sprintf(string_value, "¦");
									if(sta2_pack[pack_id].special == PACK_SPECIAL_BOOTS) 
										sprintf(string_value, "§");
									if(sta2_pack[pack_id].special == PACK_SPECIAL_GODEYE) 
										sprintf(string_value, "¨");
									if(sta2_pack[pack_id].special == PACK_SPECIAL_MAGICNET) 
										sprintf(string_value, "©");
									if(sta2_pack[pack_id].special == PACK_SPECIAL_VAMPIRE) 
										sprintf(string_value, "ª");
									if(sta2_pack[pack_id].special == PACK_SPECIAL_MAGICHERB) 
										sprintf(string_value, "«");
									if(sta2_pack[pack_id].special == PACK_SPECIAL_XPGAIN) 
										sprintf(string_value, "¬");
									if(sta2_pack[pack_id].special == PACK_SPECIAL_DEATHBLOW) 
										sprintf(string_value, "®");
									if(sta2_pack[pack_id].special == PACK_SPECIAL_LASTCHANCE) 
										sprintf(string_value, "¯");

									strcat(new_counter[4].word, string_value);
								} 
								 
								sprintf(string_value, ""); 
//								sprintf(string_value, "%s LVL%i:WP/%i^", sta2_squad[sprite[i].value2].string, sprite[i].rank, sta2_pack[sta2_squad[sprite[i].value2].wp].rank);
								sprintf(string_value, "%s LVL%i^XP:%i WP:%i^", sta2_squad[sprite[i].value2].string, sprite[i].rank, sta2_squad[sprite[i].value2].xp, sta2_pack[sta2_squad[sprite[i].value2].wp].rank);
								strcat(new_counter[4].word, string_value);

								if(sprite[i].return_fire == true) // Defending... 
								{
									sprintf(string_value, "");
									sprintf(string_value, "DEFENDING..^");
									strcat(new_counter[4].word, string_value);
								}

							}

						}   
					}      
						 
					// For left-sided messages, get longest line...
					if( new_counter[4].x >= sta2_left_of_screen)  
					{ 
						slongest_line = GetLongestLine(new_counter[4].word); 
							   
						new_counter[5].x = mouseX - 0.03f;  
						new_counter[4].x = new_counter[5].x - (slongest_line*0.0245f);  

					} 

				    if(sta2_cpu_map_unit != i)    
					if(sprite[i].score > 1)  
					if(sprite[i].anim != 22)       
						index = i;   
					      
					if(sta2_turn == TURN_PLAYER)      
					if(sta2_player_moves > 0 || sta2_pressed_map == true)
					if(sprite[i].hit_by_bullet == false || UNITS_CAN_MOVE_MORE_THAN_ONCE == 1) 
					if(mouseleft == true || DX_SHOOT == true)   
					{  

						if(sta2_pressed_map == false || current_unit == sprite[i].value3 )
						if(sprite[i].value3 != PIN_ENEMY)
						if(sprite[i].score > 1)
						{        
							DX_SHOOT=false; 
							mouseleft = false; 
							  
							if(sta2_pressed_map == false)
							{
								if(sprite[i].value3 == PIN_UNIT1) 
									current_unit = PIN_UNIT1;
								if(sprite[i].value3 == PIN_UNIT2)
									current_unit = PIN_UNIT2;
								if(sprite[i].value3 == PIN_UNIT3)
									current_unit = PIN_UNIT3;
								if(sprite[i].value3 == PIN_UNIT4)
									current_unit = PIN_UNIT4; 
								if(sprite[i].value3 == PIN_UNIT5)
									current_unit = PIN_UNIT5;  
							}
							if(sta2_is_epic_battle == true)
							{
								episode = 4;   
								scene = 0;
							}
							else
							{
								episode = 2;   
								scene = 0;
							}

							current_spawn = 0;  

							if(sta2_pressed_map == false)
								sta2_player_moves--;

							if(sta2_player_moves < 0)
								sta2_player_moves = 0;

							in_stats = true;
							next_scene = true;
						}
					}         
          
			   }    
			   else          
			   {   
				   Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
			   }          
			      
		   } // for   

			if(index != -1) 
				Set_Sprite(index, sprite[index].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
		   
	/*	    if(sprite[1].alpha == 1.0f)                   
		    if(( mouseX < (sprite[1].w + sprite[1].box_width) )
		    &&( mouseX > sprite[1].w)                            
			&&( mouseY < (sprite[1].z + sprite[1].box_height) )
			&&( mouseY > sprite[1].z))   
			{ 
				if(title_sequence == 1)
				if(mouseleft == true || DX_SHOOT == true) 
				{ 
					 
					sta2_next_event = EVENT_VICTORY;

					episode = 1;    
					scene = 2;  

					next_scene = true;

				}
			}*/



       } // scene == 1  


    // ******************************************************************************//
    //                                 1-8  (RATIONS)                                //
    // ******************************************************************************//
             
       // Title Screen Stuff...       
       if(!mode)      
       if(next_scene == false)     
       if(episode == 1 && scene == 8)       
       {       
		   SwipeCode(f_rate);

	        if(title_sequence == 0)                       
            {  	  

			    sprintf( new_counter[0].word, "3. Back");   

			    new_counter[0].alpha = 1.0f;                  
			    new_counter[0].id = 0;    
		       
				if(screen_mode == SCREEN_1610_WIDESCREEN)
					new_counter[0].x = +0.46f;        
				else
					new_counter[0].x = +0.50f;   

			    new_counter[0].y = -0.34f;       	        
				     
				new_counter[0].w = new_counter[0].x - 0.026f;   
				new_counter[0].z = new_counter[0].y - 0.015f; 

				new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
				new_counter[0].box_height = new_counter[0].height - 0.015f;	

			    new_counter[1].alpha = 1.0f;          
			    new_counter[1].id = 0;     
		         
			    new_counter[1].x = -0.35f;         
			    new_counter[1].y = 0.085f; 	   

				title_sequence++;
			} 
			 
	        if(title_sequence == 1)                        
            {  
				for(int k = 1;k < 5;k++)
					Set_Sprite(k, sprite[k].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				if(sta2_food_rations == RATIONS_LOW)
					Set_Sprite(1, sprite[1].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				if(sta2_food_rations == RATIONS_MID)
					Set_Sprite(2, sprite[2].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				if(sta2_food_rations == RATIONS_HIGH)
					Set_Sprite(3, sprite[3].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				if(sta2_food_rations == RATIONS_MEGA)
					Set_Sprite(4, sprite[4].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				new_counter[0].id = 0; 
				 
				testX = hud_mouseX - (-camX);                                                    
				testY = hud_mouseY - (-camY);  

				// Back button..
				if(new_counter[0].alpha == 1.0f)
				if(( testX < (new_counter[0].w + new_counter[0].box_width) )
				&&( testX > new_counter[0].w)                            
				&&( testY < (new_counter[0].z + new_counter[0].box_height) )
				&&( testY > new_counter[0].z) || sta2_3_pressed == true)   
				{ 
					new_counter[0].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_3_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_3_pressed = false; 

						episode = 1;  
						scene = 5;

						next_scene = true;
						  
					} 
				}      

				test_button = 0;

				for(int i = 1;i < 5;i++)
				if(( mouseX < (sprite[i].w + sprite[i].box_width) )
				&&( mouseX > sprite[i].w)                            
				&&( mouseY < (sprite[i].z + sprite[i].box_height) )
				&&( mouseY > sprite[i].z)) 
				{

					test_button = i; 
					  
					if(mouseleft == true)     
					{
						if(test_button == 1)
							sta2_food_rations = RATIONS_LOW; 
						if(test_button == 2)
							sta2_food_rations = RATIONS_MID;
						if(test_button == 3)
							sta2_food_rations = RATIONS_HIGH;
						if(test_button == 4)
							sta2_food_rations = RATIONS_MEGA;

						mouseleft = false;       
					}
				}      
				     
				if(test_button == 0) 
					sprintf( new_counter[1].word, "Click on a ration icon^to change ration portions.^^Bigger rations means more^health regain per day!^If food runs out your^units lose health per day."); 
				if(test_button == 1)
					sprintf( new_counter[1].word, "MEAGER^Each unit uses %i food per^day. Non-wounded units gain^2& of health per day!", RATIONS_LOW_COST); 
				if(test_button == 2)
					sprintf( new_counter[1].word, "NORMAL^Each unit uses %i food per^day. Non-wounded units gain^5& of health per day!", RATIONS_MID_COST); 
				if(test_button == 3)
					sprintf( new_counter[1].word, "HIGH^Each unit uses %i food per^day. Non-wounded units gain^6& of health per day!", RATIONS_HIGH_COST); 
				if(test_button == 4)
					sprintf( new_counter[1].word, "MEGA^Each unit uses %i food per^day. Non-wounded units gain^10& of health per day!", RATIONS_MEGA_COST); 
			  


			}             

	   }

    // ******************************************************************************//
    //                                   1-7  (PACKS)                                //
    // ******************************************************************************//
             
       // Title Screen Stuff...       
       if(!mode)      
       if(next_scene == false)    
       if(episode == 1 && scene == 7)       
       {    

		    SwipeCode(f_rate);

	        if(title_sequence == 0)                  
            {  	     

				for(int j = 10;j < 16;j++)  
				{ 
					sprite[j].alpha = 0.0f;
				}

				sta2_packpage_index = 0;
				 
			    sprintf( new_counter[0].word, "3. Back");   

			    new_counter[0].alpha = 1.0f;                 
			    new_counter[0].id = 0;   
		      
				if(screen_mode == SCREEN_1610_WIDESCREEN)
					new_counter[0].x = +0.46f;        
				else
					new_counter[0].x = +0.50f;  

			    new_counter[0].y = -0.34f;       	        
				     
				new_counter[0].w = new_counter[0].x - 0.026f;   
				new_counter[0].z = new_counter[0].y - 0.015f; 

				new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
				new_counter[0].box_height = new_counter[0].height - 0.015f;	

			    new_counter[2].alpha = 1.0f;              
			    new_counter[2].id = 0;    
		       
			    new_counter[2].x = -0.35f;            
			    new_counter[2].y = +0.02f;   

				sta2_temp_pack_count = 0;    
				sta2_pack_order_count = 0;

				for(int i = 0;i<STA2_PACKS_LIMIT;i++)     
				{ 
					if(sta2_pack[i].type != STA2_VOID && sta2_pack[i].equipped == false)
					{
						sta2_pack_order_rank[sta2_pack_order_count] = sta2_pack[i].rank;
						sta2_pack_order[sta2_pack_order_count] = i;
						sta2_pack_order_count++; 
					} 
				}

				for(int j = 15;j>0;j--) 
				for(int i = 0;i<sta2_pack_order_count;i++)   
				{
					if(sta2_pack_order_rank[i] == j) 
					{
						sta2_pack_order_rank[i] = -1;
						sta2_temp_pack[sta2_temp_pack_count] = sta2_pack_order[i];
						sta2_temp_pack_count++;  
					} 
				}

				// Unit type pins...
			    for(int i = 1; i < 7;i++)  
			    {      

					sprite[i].value1 = no_sprites; 

					sprite[no_sprites].id = sprite[i].id; 

					sprite[no_sprites].light = 1.0f;
					 
					sprite[no_sprites].priority = 1;

					sprite[no_sprites].fx_id = animation_fx[sprite[no_sprites].id];

				    sprite[no_sprites].depth = 0.0f;
				    
				    sprite[no_sprites].x = sprite[i].x;  
				    sprite[no_sprites].y = sprite[i].y;  

				    sprite[no_sprites].w = sprite[i].w; 
				    sprite[no_sprites].z = sprite[i].z; 

				    sprite[no_sprites].width = sprite[i].width; 
				    sprite[no_sprites].height = sprite[i].height; 
				    sprite[no_sprites].box_width = sprite[i].box_width; 
				    sprite[no_sprites].box_height = sprite[i].box_height; 

				    sprite[no_sprites].alpha = 0.0f; 

					sprite[no_sprites].type = NON;

				    sprite[no_sprites].mouseover = false;
				    
				    sprite[no_sprites].turn_off = false; 

					sprite[no_sprites].anim = 32;

					sprite[no_sprites].cur = 0;   

					sprite[no_sprites].cur_time = 0;
                         
					sprite[no_sprites].anim_state = LOOP;
                
#ifndef DREAMCAST
					sprite[no_sprites].frame = a_texture[sprite[no_sprites].fx_id].anims[sprite[no_sprites].anim][sprite[no_sprites].cur];
#else
					sprite[no_sprites].frame = a_texture_get_anims_secondlayer(sprite[no_sprites].fx_id, sprite[no_sprites].anim, sprite[no_sprites].cur);
#endif
            
					sprite[no_sprites].base_anim = sprite[no_sprites].anim;

					Set_Sprite(no_sprites, sprite[no_sprites].anim, LOOP, ANIM_SPRITE, ANIM_WALKING);

					no_sprites++;    

					sprite[no_sprites].id = 12; 
					 
					sprite[no_sprites].light = 1.0f;
					 
					sprite[no_sprites].priority = 1;

					sprite[no_sprites].fx_id = animation_fx[sprite[no_sprites].id];

				    sprite[no_sprites].depth = 0.0f;
				    
				    sprite[no_sprites].x = sprite[i].x;  
				    sprite[no_sprites].y = sprite[i].y;  

				    sprite[no_sprites].w = sprite[i].w; 
				    sprite[no_sprites].z = sprite[i].z; 

				    sprite[no_sprites].width = sprite[i].width; 
				    sprite[no_sprites].height = sprite[i].height; 
				    sprite[no_sprites].box_width = sprite[i].box_width; 
				    sprite[no_sprites].box_height = sprite[i].box_height; 

				    sprite[no_sprites].alpha = 1.0f; 

					sprite[no_sprites].type = NON;

				    sprite[no_sprites].mouseover = false;
				    
				    sprite[no_sprites].turn_off = false; 

					sprite[no_sprites].anim = 16;  

					sprite[no_sprites].cur = 0;     

					sprite[no_sprites].cur_time = 0;
                         
					sprite[no_sprites].anim_state = LOOP;
                
#ifndef DREAMCAST
					sprite[no_sprites].frame = a_texture[sprite[no_sprites].fx_id].anims[sprite[no_sprites].anim][sprite[no_sprites].cur];
#else
					sprite[no_sprites].frame = a_texture_get_anims_secondlayer(sprite[no_sprites].fx_id, sprite[no_sprites].anim, sprite[no_sprites].cur);
#endif
            
					sprite[no_sprites].base_anim = sprite[no_sprites].anim;

					Set_Sprite(no_sprites, sprite[no_sprites].anim, LOOP, ANIM_SPRITE, ANIM_WALKING);
					 
					no_sprites++;  

				}

				title_sequence++;  
			}
	
			sta2_equip_type = sta2_squad[sta2_equip_this_unit].type;

			if(sta2_squad[sta2_equip_this_unit].type == STA2_CO)
			{
				if(sta2_co_type == STA2_CO_ADA)
					sta2_equip_type = STA2_SCOUT; 
				if(sta2_co_type == STA2_CO_MARIE)
					sta2_equip_type = STA2_HEAVY; 
				if(sta2_co_type == STA2_CO_ADELE)
					sta2_equip_type = STA2_SNIPER; 
				if(sta2_co_type == STA2_CO_BELLA)
					sta2_equip_type = STA2_MORTAR; 
			}

	        if(title_sequence == 1)                       
            {  	  
				
				 new_counter[2].id = 0; 

				 sprintf( new_counter[2].word, "Click on a weapon pack to^equip it to your unit."); 
				  
				// Packs...    
				for(int i = 1;i<7;i++)                                            
				{   
					 
					// Grenade / Medkit overlay...
					sprite[(i-1)+10].alpha = 0.0f; 
					 
					if(sprite[i].value1 > 0) 
						sprite[sprite[i].value1].alpha = 0.0f;

					sprite[sprite[i].value1+1].alpha = 0.0f; 

					sprite[i].base_anim = 12;    // Empty...            
					sprite[i].value2 = -1;
					Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

					if(sta2_packpage_index+(i-1) < sta2_temp_pack_count)
					if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].type != STA2_VOID && sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].equipped == false)
					{  
						sprite[i].value2 = sta2_temp_pack[sta2_packpage_index+(i-1)];       
						sprite[i].base_anim = 16;    
						 
						if(sprite[i].value1 > 0)  
						{
							sprite[sprite[i].value1].alpha = 1.0f;  
							
							if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].special != PACK_SPECIAL_NONE)
							{
								sprite[sprite[i].value1+1].alpha = 1.0f;
								// Lvl..
								sprite[sprite[i].value1+1].anim = 15 + sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].special;
								sprite[sprite[i].value1+1].base_anim = 15 + sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].special;
							}

							if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].type == STA2_SCOUT)
							{
								sprite[sprite[i].value1].anim = 32;
								sprite[sprite[i].value1].base_anim = 32;
							}  

							if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].type == STA2_HEAVY)
							{
								sprite[sprite[i].value1].anim = 33;
								sprite[sprite[i].value1].base_anim = 33;
							}

							if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].type == STA2_SNIPER)
							{
								sprite[sprite[i].value1].anim = 34;
								sprite[sprite[i].value1].base_anim = 34;
							}

							if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].type == STA2_MORTAR)
							{
								sprite[sprite[i].value1].anim = 35;
								sprite[sprite[i].value1].base_anim = 35; 
							}

							Set_Sprite(sprite[i].value1, sprite[sprite[i].value1].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
							Set_Sprite(sprite[i].value1+1, sprite[sprite[i].value1+1].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

						}


						if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].rank == 1)
							sprite[i].base_anim = 16;   
						if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].rank == 2)
							sprite[i].base_anim = 18;  
						if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].rank == 3)
							sprite[i].base_anim = 22;   
						if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].rank == 4)
							sprite[i].base_anim = 23;   
						if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].rank == 5)
							sprite[i].base_anim = 24;   
						if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].rank == 6)
							sprite[i].base_anim = 25;   
						if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].rank == 7)
							sprite[i].base_anim = 26;   
						if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].rank == 8)
							sprite[i].base_anim = 27;  
						if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].rank == 9)
							sprite[i].base_anim = 28;  

						if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].extra == PACK_EXTRA_MEDKIT)
						{
							sprite[(i-1)+10].alpha = 1.0f; 
							Set_Sprite((i-1)+10, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

							if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].special != PACK_SPECIAL_NONE)
								Set_Sprite((i-1)+10, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
							 
						}   
						 
						if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].extra == PACK_EXTRA_GRENADE)
						{
							sprite[(i-1)+10].alpha = 1.0f; 
							Set_Sprite((i-1)+10, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

							if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].special != PACK_SPECIAL_NONE)
								Set_Sprite((i-1)+10, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
						}

						if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].extra == PACK_EXTRA_NONE)
						if(sta2_pack[sta2_temp_pack[sta2_packpage_index+(i-1)]].special != PACK_SPECIAL_NONE)
						{
							sprite[(i-1)+10].alpha = 1.0f;
							Set_Sprite((i-1)+10, 4, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
						}

						Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
					}  

				}  

				new_counter[1].alpha = 0.0f; 
				new_counter[5].alpha = 0.0f;

				// Test against squad roster...     
				for(int i=1;i<7;i++)         
				{   
				 
					// Roster face...
					if(sprite[i].alpha == 1.0)                      
					if(sprite[i].value2 != -1)
					if(( mouseX < (sprite[i].w + sprite[i].box_width) )
					&&( mouseX > sprite[i].w)                            
					&&( mouseY < (sprite[i].z + sprite[i].box_height) )
					&&( mouseY > sprite[i].z)) 
					{      
					   
						new_counter[1].alpha = 1.0f;               
					   
						new_counter[1].x = mouseX + 0.13f;                   
						new_counter[1].y = mouseY;    

						new_counter[5].alpha = 1.0f;                
					    
						new_counter[5].x = mouseX + 0.1f;                    
						new_counter[5].y = mouseY;   
					 
						sprintf( new_counter[5].word, "@");  

						if(sprite[i].value2 != -1)   
    						sprintf( new_counter[1].word, "%s^LVL%i", sta2_pack[sprite[i].value2].string,  sta2_pack[sprite[i].value2].rank);	 

						// For left-sided messages, get longest line...
						if( new_counter[1].x >= sta2_left_of_screen)  
						{ 
							slongest_line = GetLongestLine(new_counter[1].word);  
							   
							new_counter[5].x = mouseX - 0.03f;  
							new_counter[1].x = new_counter[5].x - (slongest_line*0.0245f);  

						} 

						sprintf(string_value, "");
						sprintf(new_counter[2].word, "");

						if(sta2_squad[sta2_equip_this_unit].rank < sta2_pack[sprite[i].value2].rank)
						{
							new_counter[2].id = 3;
							sprintf(string_value, "(UNIT MUST BE ATLEAST LVL%i)^", sta2_pack[sprite[i].value2].rank);
							strcat(new_counter[2].word, string_value);
						}

						if(sta2_equip_type != sta2_pack[sprite[i].value2].type)
						{ 
							new_counter[2].id = 3;
							sprintf(string_value, "(UNIT IS WRONG CLASS^TYPE TO EQUIP)^");
							strcat(new_counter[2].word, string_value);
						} 

						if(sprite[i].value2 >= 0)
						if(sta2_pack[sprite[i].value2].type == STA2_SCOUT)
						{
							sprintf(string_value, "PISTOL DAMAGE %i-%i^", PISTOL1_BASE_FP + sta2_pack[sprite[i].value2].rank*10, PISTOL1_BASE_FP + PISTOL1_BASE_FP_RANDOM + sta2_pack[sprite[i].value2].rank*10);
							strcat(new_counter[2].word, string_value);

							sprintf(string_value, "RIFLE DAMAGE %i-%i^", RIFLE1_BASE_FP + sta2_pack[sprite[i].value2].rank*10, RIFLE1_BASE_FP + RIFLE1_BASE_FP_RANDOM + sta2_pack[sprite[i].value2].rank*20);
							strcat(new_counter[2].word, string_value);
						}    

						if(sprite[i].value2 >= 0)
						if(sta2_pack[sprite[i].value2].type == STA2_HEAVY)
						{
							sprintf(string_value, "SHOTGUN DAMAGE %i-%i^", (sta2_pack[sprite[i].value2].rank*20), 45 + (sta2_pack[sprite[i].value2].rank*20));
							strcat(new_counter[2].word, string_value);

							sprintf(string_value, "MACHINE DAMAGE %i-%i^", (sta2_pack[sprite[i].value2].rank*20), 20 + (sta2_pack[sprite[i].value2].rank*20));
							strcat(new_counter[2].word, string_value);
						}

						if(sprite[i].value2 >= 0)
						if(sta2_pack[sprite[i].value2].type == STA2_SNIPER)
						{
							sprintf(string_value, "PISTOL DAMAGE %i-%i^", PISTOL1_BASE_FP + sta2_pack[sprite[i].value2].rank*10, PISTOL1_BASE_FP + PISTOL1_BASE_FP_RANDOM + sta2_pack[sprite[i].value2].rank*10);
							strcat(new_counter[2].word, string_value);

							sprintf(string_value, "SNIPER DAMAGE %i-%i^", SNIPER1_BASE_FP + sta2_pack[sprite[i].value2].rank*20, SNIPER1_BASE_FP + RIFLE1_BASE_FP_RANDOM + (sta2_pack[sprite[i].value2].rank*20));
							strcat(new_counter[2].word, string_value);
						}
						if(sprite[i].value2 >= 0)
						if(sta2_pack[sprite[i].value2].type== STA2_MORTAR)
						{
							sprintf(string_value, "PISTOL DAMAGE %i-%i^", PISTOL1_BASE_FP + sta2_pack[sprite[i].value2].rank*10, PISTOL1_BASE_FP + PISTOL1_BASE_FP_RANDOM + sta2_pack[sprite[i].value2].rank*10);
							strcat(new_counter[2].word, string_value);

							sprintf(string_value, "MORTAR DAMAGE %i-%i^", 1, 60 + (sta2_pack[sprite[i].value2].rank*30));
							strcat(new_counter[2].word, string_value); 
						}

						if(sprite[i].value2 >= 0)
						if(sta2_pack[sprite[i].value2].extra == PACK_EXTRA_NONE)   
							sprintf(string_value, "EXTRA : NONE"); 

						if(sprite[i].value2 >= 0)
						if(sta2_pack[sprite[i].value2].extra == PACK_EXTRA_MEDKIT)
							sprintf(string_value, "EXTRA : MEDKIT %i-%i", 1, STA2_HEAL_AMOUNT + (sta2_pack[sprite[i].value2].rank*20));

						if(sprite[i].value2 >= 0)
						if(sta2_pack[sprite[i].value2].extra == PACK_EXTRA_GRENADE)
							sprintf(string_value, "EXTRA : GRENADE %i-%i", 1, STA2_GRENADE_AMOUNT + (sta2_pack[sprite[i].value2].rank*30));

						strcat(new_counter[2].word, string_value);

						if(sprite[i].value2 >= 0)
						{
						if(sta2_pack[sprite[i].value2].special == PACK_SPECIAL_NONE)   
							sprintf(string_value, "^SPECIAL : NONE");  
						if(sta2_pack[sprite[i].value2].special == PACK_SPECIAL_SCOPE)
							sprintf(string_value, "^SPECIAL : SCOPE");
						if(sta2_pack[sprite[i].value2].special == PACK_SPECIAL_SHIELD)
							sprintf(string_value, "^SPECIAL : SHIELD");
						if(sta2_pack[sprite[i].value2].special == PACK_SPECIAL_DUMDUM)
							sprintf(string_value, "^SPECIAL : RAGE");
						if(sta2_pack[sprite[i].value2].special == PACK_SPECIAL_BOOTS)
							sprintf(string_value, "^SPECIAL : DASH");
						if(sta2_pack[sprite[i].value2].special == PACK_SPECIAL_GODEYE)
							sprintf(string_value, "^SPECIAL : GOD-EYE");
						if(sta2_pack[sprite[i].value2].special == PACK_SPECIAL_MAGICNET)
							sprintf(string_value, "^SPECIAL : CLOAK");
						if(sta2_pack[sprite[i].value2].special == PACK_SPECIAL_VAMPIRE)
							sprintf(string_value, "^SPECIAL : VAMPIRE");
						if(sta2_pack[sprite[i].value2].special == PACK_SPECIAL_MAGICHERB)
							sprintf(string_value, "^SPECIAL : MARYJANE");
						if(sta2_pack[sprite[i].value2].special == PACK_SPECIAL_XPGAIN)
							sprintf(string_value, "^SPECIAL : WISDOM");
						if(sta2_pack[sprite[i].value2].special == PACK_SPECIAL_DEATHBLOW)
							sprintf(string_value, "^SPECIAL : FINAL");
						if(sta2_pack[sprite[i].value2].special == PACK_SPECIAL_LASTCHANCE)
							sprintf(string_value, "^SPECIAL : LAST");
						}

						strcat(new_counter[2].word, string_value);



						if(sprite[i].value2 >= 0)
						if(sta2_equip_type == sta2_pack[sprite[i].value2].type)
						if(sta2_squad[sta2_equip_this_unit].rank >= sta2_pack[sprite[i].value2].rank)
						if(mouseleft == true)
						{
							episode = 1;
							scene = 5;
							 
							next_scene = true; 

							spark_sfx = true;

							mouseleft = false;   

							sta2_pack[sprite[i].value2].equipped = true;
							sta2_pack[sta2_squad[sta2_equip_this_unit].wp].equipped = false;

							sta2_squad[sta2_equip_this_unit].wp = sprite[i].value2;

						}
					} 

				}  

				// Turn off arrows if roster is too small etc...
				if(sta2_temp_pack_count < 7)          
				{    
					sprite[9].base_anim = 3;  
					Set_Sprite(9, sprite[9].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}
				else
				{ 
					sprite[9].base_anim = 2;  
					Set_Sprite(9, sprite[9].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				} 
			 
				// Turn off arrows if roster is too small etc...
				if(sta2_packpage_index == 0)       
				{ 
					sprite[8].base_anim = 1;    
					Set_Sprite(8, sprite[8].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}
				else  
				{ 
					sprite[8].base_anim = 0;  
					Set_Sprite(8, sprite[8].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}

				// Arrow left 
				if(sprite[8].alpha == 1.0)    
				if(sprite[8].base_anim != 1)
				if(( mouseX < (sprite[8].w + sprite[8].box_width) )
				&&( mouseX > sprite[8].w)                            
				&&( mouseY < (sprite[8].z + sprite[8].box_height) )
				&&( mouseY > sprite[8].z)) 
				if(mouseleft == true)
				{ 
					mouseleft = false;    

					if(sta2_packpage_index >= 1)
						sta2_packpage_index--;
				}
			  
				// Arrow right
				if(sprite[9].alpha == 1.0)       
				if(sprite[9].base_anim != 3)
				if(( mouseX < (sprite[9].w + sprite[9].box_width) )
				&&( mouseX > sprite[9].w)                            
				&&( mouseY < (sprite[9].z + sprite[9].box_height) )
				&&( mouseY > sprite[9].z)) 
				if(mouseleft == true)
				{
					mouseleft = false;   

					if(sta2_packpage_index <= (94))
						sta2_packpage_index++;
				} 

				new_counter[0].id = 0;  
				 
				testX = hud_mouseX - (-camX);                                                    
				testY = hud_mouseY - (-camY);    

				// Back button..
				if(new_counter[0].alpha == 1.0f)
				if(( testX < (new_counter[0].w + new_counter[0].box_width) )
				&&( testX > new_counter[0].w)                            
				&&( testY < (new_counter[0].z + new_counter[0].box_height) )
				&&( testY > new_counter[0].z) || sta2_3_pressed == true)   
				{ 
					new_counter[0].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_3_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_3_pressed = false;

						episode = 1;  
						scene = 5;

						next_scene = true;
						  
					} 
				}   

			}


	   }


    // ******************************************************************************//
    //                                   1-6  (SHOP)                                 //
    // ******************************************************************************//
            
       // Title Screen Stuff...        
       if(!mode)    
       if(next_scene == false)    
       if(episode == 1 && scene == 6)    
       {       
		      
		//    SwipeCode(f_rate);

		    hud[62].alpha = 1.0f; // Gold / Food bar...

		    if(sta2_shop_tab != SHOP_PACKS) 
			for(int j = 14;j < 20;j++)  
			{
				sprite[j].alpha = 0.0f;
			}
			 
            if(title_sequence == 0)                     
            {   

				// Reset all shop items...
				for(int j = 14;j < 20;j++)  
				{
					sprite[j].alpha = 0.0f;
				}

				sta2_equip_this_unit = -1;

				sta2_shop.heal_cost=5; // +sta2_sector   
				 
				// Reset all shop items...
				for(int j = 0;j < SHOP_LIMIT_ITEMS;j++)  
				{
					sta2_shop.food_type[j] = SHOP_FOOD_NONE; 
					sta2_shop.food_amount[j] = 0;  
					sta2_shop.food_cost[j] = 0; 
					sta2_shop.hire_type[j] = STA2_VOID;   
					sta2_shop.hire_rank[j] = 0; 
					sta2_shop.hire_face[j] = 0;  
					sta2_shop.hire_cost[j] = 0;  
					sta2_shop.pack_type[j] = STA2_VOID; 
					sta2_shop.pack_rank[j] = 0; 
					sta2_shop.pack_extra[j] = PACK_EXTRA_NONE;
					sta2_shop.pack_special[j] = PACK_SPECIAL_NONE;  
					sta2_shop.pack_active1[j] = PACK_ACTIVE_NONE;     
					sta2_shop.pack_active2[j] = PACK_ACTIVE_NONE;
					sta2_shop.pack_active3[j] = PACK_ACTIVE_NONE;     
					sta2_shop.pack_active4[j] = PACK_ACTIVE_NONE;
					sta2_shop.pack_cost[j] = 0;
					sprintf( sta2_shop.hire_string[0], "NONE");
					sprintf( sta2_shop.pack_string[0], "NONE");
				} 
				 
				// Generate food items...
				for(int k = 0; k < 6;k++)   
				{ 
					index = rand()%8;   

					if(index == 0)
					{
						sta2_shop.food_type[k] = SHOP_FOOD_DEER; 
						sta2_shop.food_amount[k] = 65; 
						sta2_shop.food_cost[k] = 10;

						if(sta2_environment_type == AREA_SNOW)
						{
							sta2_shop.food_type[k] = SHOP_FOOD_YETI_BIG;
							sta2_shop.food_amount[k] = 65; 
							sta2_shop.food_cost[k] = 20;
						}

						if(sta2_environment_type == AREA_DESERT)
						{
							sta2_shop.food_type[k] = SHOP_FOOD_SNAKE_BIG;
							sta2_shop.food_amount[k] = 65; 
							sta2_shop.food_cost[k] = 20; 
						}

						if(sta2_environment_type == AREA_CITY || sta2_environment_type == AREA_TRENCH)
						{
							sta2_shop.food_type[k] = SHOP_FOOD_CROW_BIG;
							sta2_shop.food_amount[k] = 65; 
							sta2_shop.food_cost[k] = 20;
						}

					}  

					if(index == 1 || index == 2) 
					{

						sta2_shop.food_type[k] = SHOP_FOOD_RACOON; 
						sta2_shop.food_amount[k] = 30; 
						sta2_shop.food_cost[k] = 5;

						if(sta2_environment_type == AREA_SNOW)
						{
							sta2_shop.food_type[k] = SHOP_FOOD_YETI_SMALL;
							sta2_shop.food_amount[k] = 30; 
							sta2_shop.food_cost[k] = 10;
						}

						if(sta2_environment_type == AREA_DESERT)
						{
							sta2_shop.food_type[k] = SHOP_FOOD_SNAKE_SMALL;
							sta2_shop.food_amount[k] = 30; 
							sta2_shop.food_cost[k] = 10;
						}

						if(sta2_environment_type == AREA_CITY || sta2_environment_type == AREA_TRENCH)
						{
							sta2_shop.food_type[k] = SHOP_FOOD_CROW_SMALL;
							sta2_shop.food_amount[k] = 30; 
							sta2_shop.food_cost[k] = 10;
						}

					}

					if(index >= 3) 
					{
						sta2_shop.food_type[k] = SHOP_FOOD_RABBIT; 
						sta2_shop.food_amount[k] = 5; 
						sta2_shop.food_cost[k] = 1;

						if(sta2_environment_type == AREA_SNOW)
						{
							sta2_shop.food_type[k] = SHOP_FOOD_ICE;
							sta2_shop.food_amount[k] = 5; 
							sta2_shop.food_cost[k] = 2;
						}

						if(sta2_environment_type == AREA_DESERT)
						{
							sta2_shop.food_type[k] = SHOP_FOOD_SCORPION;
							sta2_shop.food_amount[k] = 5; 
							sta2_shop.food_cost[k] = 2;
						} 

						if(sta2_environment_type == AREA_CITY || sta2_environment_type == AREA_TRENCH)
						{
							sta2_shop.food_type[k] = SHOP_FOOD_RAT;
							sta2_shop.food_amount[k] = 5; 
							sta2_shop.food_cost[k] = 2;
						}

					}
				}  

				// Generate hire recruits...
				index = rand()%9;    

				for(int k = 0; k < index;k++)      
				{ 
					

					if(sta2_sector  < 3)
					{
						rnd = rand()%3;
						if(rand()%3==0) 
						{
							sta2_shop.hire_type[k] = STA2_HEAVY;  
							sta2_shop.hire_score[k] = 50 + sta2_sector*30;
						}
						else
						{
							sta2_shop.hire_type[k] = STA2_SCOUT;        
							sta2_shop.hire_score[k] = 30 + sta2_sector*30;
						}
					}
					if(sta2_sector  >= 3 && sta2_sector <= 4)
					{
						rnd = rand()%3;     
						if(rnd==0) 
						{
							sta2_shop.hire_type[k] = STA2_HEAVY;  
							sta2_shop.hire_score[k] = 50 + sta2_sector*30;
						}
						if(rnd==1)
						{
							sta2_shop.hire_type[k] = STA2_SCOUT;        
							sta2_shop.hire_score[k] = 30 + sta2_sector*30;
						}
						if(rnd==2)
						{
							sta2_shop.hire_type[k] = STA2_SNIPER;        
							sta2_shop.hire_score[k] = 30 + sta2_sector*30;
						}
					}
					if(sta2_sector  > 4)
					{
						rnd = rand()%4;  
						if(rnd==0) 
						{
							sta2_shop.hire_type[k] = STA2_HEAVY;  
							sta2_shop.hire_score[k] = 50 + sta2_sector*30;
						}
						if(rnd==1)
						{
							sta2_shop.hire_type[k] = STA2_SCOUT;        
							sta2_shop.hire_score[k] = 30 + sta2_sector*30;
						} 
						if(rnd==2)
						{
							sta2_shop.hire_type[k] = STA2_SNIPER;        
							sta2_shop.hire_score[k] = 20 + sta2_sector*30;
						}
						if(rnd==3)
						{
							sta2_shop.hire_type[k] = STA2_MORTAR;        
							sta2_shop.hire_score[k] = 40 + sta2_sector*30;
						}
					}

					sta2_shop.hire_rank[k] = sta2_sector;  

					if(sta2_shop.hire_type[k] == STA2_SCOUT)
						sta2_shop.hire_face[k] = 1+rand()%10;  
					if(sta2_shop.hire_type[k] == STA2_HEAVY)
						sta2_shop.hire_face[k] = 31;  
					if(sta2_shop.hire_type[k] == STA2_SNIPER)
						sta2_shop.hire_face[k] = 29;  
					if(sta2_shop.hire_type[k] == STA2_MORTAR)
						sta2_shop.hire_face[k] = 30;  

					sta2_shop.hire_cost[k] = (20+rand()%21) + (sta2_sector*20);
					sta2GetName("data/text/names/names.txt", sta2_shop.hire_string[k]);
				}
				 
				// Generate weapon packs...         
				index = rand()%11; 

				if(index >= 9)     
					index = 9;

				for(int k = 0; k < index;k++)       
				{     

					if(sta2_sector  < 3) 
					{ 
						rnd = rand()%3;
						if(rnd==0) 
							sta2_shop.pack_type[k] = STA2_HEAVY; 
						else 
						{
							if(sta2_co_type == STA2_CO_ADA)
								sta2_shop.pack_type[k] = STA2_SCOUT;

							if(sta2_co_type == STA2_CO_ADELE)
							if(rand()%2 == 0)
								sta2_shop.pack_type[k] = STA2_SCOUT;
							else
								sta2_shop.pack_type[k] = STA2_SNIPER;

							if(sta2_co_type == STA2_CO_BELLA)
							if(rand()%2 == 0)
								sta2_shop.pack_type[k] = STA2_SCOUT;
							else
								sta2_shop.pack_type[k] = STA2_MORTAR;

						}
					}
					if(sta2_sector  >= 3 && sta2_sector <= 4)
					{
						if(sta2_co_type != STA2_CO_BELLA)
						{
							rnd = rand()%3;
							if(rnd==0) 
								sta2_shop.pack_type[k] = STA2_SCOUT;
							if(rnd==1) 
								sta2_shop.pack_type[k] = STA2_HEAVY;
							if(rnd==2) 
								sta2_shop.pack_type[k] = STA2_SNIPER;
						}
						if(sta2_co_type == STA2_CO_BELLA)
						{
							rnd = rand()%4;
							if(rnd==0) 
								sta2_shop.pack_type[k] = STA2_SCOUT;
							if(rnd==1) 
								sta2_shop.pack_type[k] = STA2_HEAVY;
							if(rnd==2) 
								sta2_shop.pack_type[k] = STA2_SNIPER;
							if(rnd==3) 
								sta2_shop.pack_type[k] = STA2_MORTAR;
						}
					}    
					if(sta2_sector  > 4)
					{
						rnd = rand()%4;
						if(rnd==0) 
							sta2_shop.pack_type[k] = STA2_SCOUT;
						if(rnd==1) 
							sta2_shop.pack_type[k] = STA2_HEAVY;
						if(rnd==2) 
							sta2_shop.pack_type[k] = STA2_SNIPER;
						if(rnd==3) 
							sta2_shop.pack_type[k] = STA2_MORTAR;
					} 

					sta2_shop.pack_rank[k] = sta2_sector+rand()%2;     

					if(sta2_sector == 1)
						sta2_shop.pack_rank[k] = 2;

					sta2_shop.pack_cost[k] = (10+rand()%16) + (sta2_shop.pack_rank[k]*15);
						     

					sta2_shop.pack_special[k] = PACK_SPECIAL_NONE;  
					sta2_shop.pack_active1[k] = PACK_ACTIVE_NONE;     
					sta2_shop.pack_active2[k] = PACK_ACTIVE_NONE;
					sta2_shop.pack_active3[k] = PACK_ACTIVE_NONE;     
					sta2_shop.pack_active4[k] = PACK_ACTIVE_NONE;

					rnd  = rand()%3;      

					if(rnd == 0)   
					{
						sta2_shop.pack_special[k] = 1 + rand()%11;  
						sta2_shop.pack_cost[k] += 5;
					}

					if(sta2_shop.pack_type[k] == STA2_SCOUT)
						sprintf( sta2_shop.pack_string[k], "SCOUT PACK");
					if(sta2_shop.pack_type[k] == STA2_HEAVY)
						sprintf( sta2_shop.pack_string[k], "HEAVY PACK");
					if(sta2_shop.pack_type[k] == STA2_SNIPER)
						sprintf( sta2_shop.pack_string[k], "SNIPER PACK");
					if(sta2_shop.pack_type[k] == STA2_MORTAR)
						sprintf( sta2_shop.pack_string[k], "MORTAR PACK");

				/*	if(sta2_shop.pack_type[k] != PACK_SPECIAL_NONE) 
					{
						sprintf( string_value, "");
						sprintf( string_value, "+"); 
						strcat(sta2_shop.pack_string[k], string_value);
					}
					*/
					rnd  = rand()%3; 
					 
					sta2_shop.pack_extra[k] = PACK_EXTRA_NONE; 

					if(sta2_shop.pack_type[k] == STA2_SCOUT)
					{
						if(rnd == 0)
						{
							sta2_shop.pack_extra[k] = PACK_EXTRA_MEDKIT;  
							sta2_shop.pack_cost[k] += 5;
						}

						if(rnd == 1) 
						{
							sta2_shop.pack_extra[k] = PACK_EXTRA_GRENADE;  
							sta2_shop.pack_cost[k] += 5;
						}
					}

					 
				}

			    sprintf( new_counter[0].word, "3. Back");   

			    new_counter[0].alpha = 1.0f;                 
			    new_counter[0].id = 0;    
		      
				if(screen_mode == SCREEN_1610_WIDESCREEN)
					new_counter[0].x = +0.46f;        
				else
					new_counter[0].x = +0.50f;  

			    new_counter[0].y = -0.34f;      	        

				new_counter[0].w = new_counter[0].x - 0.026f;   
				new_counter[0].z = new_counter[0].y - 0.015f;

				new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
				new_counter[0].box_height = new_counter[0].height - 0.015f;	

			    new_counter[1].alpha = 1.0f;              
			    new_counter[1].id = 0;   
				 		         
			    new_counter[15].alpha = 1.0f;               
			    new_counter[15].id = 0;  

				if(screen_mode == SCREEN_1610_WIDESCREEN)
					new_counter[1].x = 0.22f;               
				else
					new_counter[1].x = 0.28f;    

			    new_counter[1].y = 0.37f;  
			    
			    if(screen_mode == SCREEN_1610_WIDESCREEN)
					new_counter[15].x = 0.46f;           
				else
					new_counter[15].x = 0.52f;   

			    new_counter[15].y = 0.37f;  

			    new_counter[2].alpha = 1.0f;          
			    new_counter[2].id = 0;    
		       
			    new_counter[2].x = -0.35f;           
			    new_counter[2].y = +0.01f; 	      

			    sprintf( new_counter[2].word, "Click on a unit to heal 15HP^for %iG.", sta2_shop.heal_cost); 

				// Create squad type pins for packs...
			    for(int i = 1; i < 7;i++)   
			    {      

					sprite[i].value1 = no_sprites;  

					sprite[no_sprites].id = 11;  

					sprite[no_sprites].light = 1.0f;
					 
					sprite[no_sprites].priority = 1;

					sprite[no_sprites].fx_id = animation_fx[sprite[no_sprites].id];

				    sprite[no_sprites].depth = 0.0f;
				    
				    sprite[no_sprites].x = sprite[i].x;  
				    sprite[no_sprites].y = sprite[i].y;  

				    sprite[no_sprites].w = sprite[i].w; 
				    sprite[no_sprites].z = sprite[i].z; 

				    sprite[no_sprites].width = sprite[i].width; 
				    sprite[no_sprites].height = sprite[i].height; 
				    sprite[no_sprites].box_width = sprite[i].box_width; 
				    sprite[no_sprites].box_height = sprite[i].box_height; 

				    sprite[no_sprites].alpha = 0.0f;  

					sprite[no_sprites].type = NON;

				    sprite[no_sprites].mouseover = false;
				    
				    sprite[no_sprites].turn_off = false; 

					sprite[no_sprites].anim = 9;

					sprite[no_sprites].cur = 0;     

					sprite[no_sprites].cur_time = 0;
                         
					sprite[no_sprites].anim_state = LOOP;
                
#ifndef DREAMCAST
					sprite[no_sprites].frame = a_texture[sprite[no_sprites].fx_id].anims[sprite[no_sprites].anim][sprite[no_sprites].cur];
#else
					sprite[no_sprites].frame = a_texture_get_anims_secondlayer(sprite[no_sprites].fx_id, sprite[no_sprites].anim, sprite[no_sprites].cur);
#endif
            
					sprite[no_sprites].base_anim = sprite[no_sprites].anim;

					Set_Sprite(no_sprites, sprite[no_sprites].anim, LOOP, ANIM_SPRITE, ANIM_WALKING);

					no_sprites++;   

					// Add rank number sprites for packs...

					sprite[no_sprites].id = 11;  

					sprite[no_sprites].light = 1.0f;
					 
					sprite[no_sprites].priority = 1;

					sprite[no_sprites].fx_id = animation_fx[sprite[no_sprites].id];

				    sprite[no_sprites].depth = 0.0f;
				    
				    sprite[no_sprites].x = sprite[i].x;  
				    sprite[no_sprites].y = sprite[i].y;  

				    sprite[no_sprites].w = sprite[i].w; 
				    sprite[no_sprites].z = sprite[i].z; 

				    sprite[no_sprites].width = sprite[i].width; 
				    sprite[no_sprites].height = sprite[i].height; 
				    sprite[no_sprites].box_width = sprite[i].box_width; 
				    sprite[no_sprites].box_height = sprite[i].box_height; 

				    sprite[no_sprites].alpha = 0.0f;  

					sprite[no_sprites].type = NON; 

				    sprite[no_sprites].mouseover = false;
				    
				    sprite[no_sprites].turn_off = false; 

					sprite[no_sprites].anim = 15;

					sprite[no_sprites].cur = 0;     

					sprite[no_sprites].cur_time = 0;
                         
					sprite[no_sprites].anim_state = LOOP;
                
#ifndef DREAMCAST
					sprite[no_sprites].frame = a_texture[sprite[no_sprites].fx_id].anims[sprite[no_sprites].anim][sprite[no_sprites].cur];
#else
					sprite[no_sprites].frame = a_texture_get_anims_secondlayer(sprite[no_sprites].fx_id, sprite[no_sprites].anim, sprite[no_sprites].cur);
#endif
            
					sprite[no_sprites].base_anim = sprite[no_sprites].anim;

					Set_Sprite(no_sprites, sprite[no_sprites].anim, LOOP, ANIM_SPRITE, ANIM_WALKING);

					no_sprites++;   
				} 

                title_sequence++;                               
            }  		

           if(title_sequence == 1)                 
           {   
			     
			    new_counter[0].id = 0; 


				sprintf( new_counter[1].word, ""); 

				if(sta2_gold < 10) 
					sprintf( string_value, "²    %iG", sta2_gold);  
				if(sta2_gold >= 10 && sta2_gold < 100)
					sprintf( string_value, "²   %iG", sta2_gold);  
				if(sta2_gold >= 100 && sta2_gold < 1000)
					sprintf( string_value, "²  %iG", sta2_gold);
				if(sta2_gold >= 1000)
					sprintf( string_value, "² %iG", sta2_gold);  
				strcat(new_counter[1].word, string_value);

				sprintf( new_counter[15].word, ""); 

				if(sta2_food < 10)   
					sprintf( string_value, "³    %iF", sta2_food);   
				if(sta2_food >= 10 && sta2_food < 100)
					sprintf( string_value, "³   %iF", sta2_food);  
				if(sta2_food >= 100 && sta2_food < 1000)
					sprintf( string_value, "³  %iF", sta2_food);
				if(sta2_food >= 1000)
					sprintf( string_value, "³ %iF", sta2_food);
				strcat(new_counter[15].word, string_value);

				testX = hud_mouseX - (-camX);                                                    
				testY = hud_mouseY - (-camY);   

				// Back button..
				if(new_counter[0].alpha == 1.0f)
				if(( testX < (new_counter[0].w + new_counter[0].box_width) )
				&&( testX > new_counter[0].w)                            
				&&( testY < (new_counter[0].z + new_counter[0].box_height) )
				&&( testY > new_counter[0].z) || sta2_3_pressed == true)   
				{ 
					new_counter[0].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_3_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_3_pressed = false; 
						sta2_investigate=false;
						 
						episode = 1;  
						scene = 0;

						next_scene = true;
						  
					} 
				}    
				   
				// Food button...  
				if(sprite[8].alpha == 1.0)    
				if(( mouseX < (sprite[8].w + sprite[8].box_width) )
				&&( mouseX > sprite[8].w)                            
				&&( mouseY < (sprite[8].z + sprite[8].box_height) )
				&&( mouseY > sprite[8].z)) 
				{
					Set_Sprite(8, sprite[8].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

					if(mouseleft == true)
						sta2_shop_tab = SHOP_FOOD;
				}
				else 
					Set_Sprite(8, sprite[8].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

			 
				// Medic button...  
				if(sprite[9].alpha == 1.0)     
				if(( mouseX < (sprite[9].w + sprite[9].box_width) )
				&&( mouseX > sprite[9].w)                            
				&&( mouseY < (sprite[9].z + sprite[9].box_height) )
				&&( mouseY > sprite[9].z)) 
				{
					Set_Sprite(9, sprite[9].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

					if(mouseleft == true)
						sta2_shop_tab = SHOP_MEDIC;
				}
				else
					Set_Sprite(9, sprite[9].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

			 
				// Hire button...  
				if(sprite[10].alpha == 1.0)     
				if(( mouseX < (sprite[10].w + sprite[10].box_width) )
				&&( mouseX > sprite[10].w)                            
				&&( mouseY < (sprite[10].z + sprite[10].box_height) )
				&&( mouseY > sprite[10].z)) 
				{
					Set_Sprite(10, sprite[10].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

					if(mouseleft == true)
						sta2_shop_tab = SHOP_HIRE;
				}
				else
					Set_Sprite(10, sprite[10].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				 
			  
				// Packs button...  
				if(sprite[13].alpha == 1.0)    
				if(( mouseX < (sprite[13].w + sprite[13].box_width) )
				&&( mouseX > sprite[13].w)                            
				&&( mouseY < (sprite[13].z + sprite[13].box_height) )
				&&( mouseY > sprite[13].z)) 
				{
					Set_Sprite(13, sprite[13].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

					if(mouseleft == true)
						sta2_shop_tab = SHOP_PACKS;
				} 
				else     
					Set_Sprite(13, sprite[13].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				// Turn off all unit type pins...
				for(int i = 1;i<7;i++)
				{
					if(sprite[i].value1 > 0) 
					{
						sprite[sprite[i].value1].alpha = 0.0f;
						sprite[sprite[i].value1+1].alpha = 0.0f;
					}
				}

				if(sta2_shop_tab == SHOP_FOOD) 
				{   
					sprintf( new_counter[2].word, "Click on a food pack to^purchase it.", sta2_gold); 

					for(int i = 1;i<7;i++)      
					{  
						sprite[i].base_anim = 12;      
						sprite[i].value2 = -1;
						Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

						if(sta2_shop.food_type[i-1] == SHOP_FOOD_DEER) 
							sprite[i].base_anim = 13;       

						if(sta2_shop.food_type[i-1] == SHOP_FOOD_RACOON) 
							sprite[i].base_anim = 14;       
						  
						if(sta2_shop.food_type[i-1] == SHOP_FOOD_RABBIT) 
							sprite[i].base_anim = 15;       

						if(sta2_shop.food_type[i-1] == SHOP_FOOD_YETI_BIG) 
							sprite[i].base_anim = 48;       

						if(sta2_shop.food_type[i-1] == SHOP_FOOD_YETI_SMALL) 
							sprite[i].base_anim = 49;       
						  
						if(sta2_shop.food_type[i-1] == SHOP_FOOD_ICE) 
							sprite[i].base_anim = 50;       

						if(sta2_shop.food_type[i-1] == SHOP_FOOD_SNAKE_BIG) 
							sprite[i].base_anim = 51;       

						if(sta2_shop.food_type[i-1] == SHOP_FOOD_SNAKE_SMALL) 
							sprite[i].base_anim = 52;       
						  
						if(sta2_shop.food_type[i-1] == SHOP_FOOD_SCORPION) 
							sprite[i].base_anim = 53;      

						if(sta2_shop.food_type[i-1] == SHOP_FOOD_CROW_BIG) 
							sprite[i].base_anim = 54;       

						if(sta2_shop.food_type[i-1] == SHOP_FOOD_CROW_SMALL) 
							sprite[i].base_anim = 55;       
						  
						if(sta2_shop.food_type[i-1] == SHOP_FOOD_RAT) 
							sprite[i].base_anim = 56;      


						if(sta2_shop.food_type[i-1] != SHOP_FOOD_NONE) 
						{
							sprite[i].value2 = (i-1);
							Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
						}
					}
				}
				if(sta2_shop_tab == SHOP_MEDIC)  
				{
					 
					sprintf( new_counter[2].word, "Click on a unit to heal 15HP^for %iG.", sta2_shop.heal_cost);

					// Squad roster...   
					for(int i = 1;i<7;i++)                         
					{   
						sprite[i].base_anim = 12;         
						sprite[i].value2 = -1;
						Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

						if(sta2_squad[sta2_squadpage_index+(i-1)].type != STA2_VOID) 
						if(sta2_squad[sta2_squadpage_index+(i-1)].health < TotalSquadScore(sta2_squadpage_index+(i-1)) )
						{
							sprite[i].value2 = sta2_squadpage_index+(i-1); 
							sprite[i].base_anim = sta2_squad[sta2_squadpage_index+(i-1)].face;   
							Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
						}

					}       
			
				} 
				if(sta2_shop_tab == SHOP_HIRE)     
				{

					sprintf( new_counter[2].word, "Click on a unit to recruit^that unit to your squad."); 

					for(int i = 1;i<7;i++)  
					{  
						sprite[i].base_anim = 12;      
						sprite[i].value2 = -1;
						Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
					}

					// Squad roster...   
					for(int i = 1;i<7;i++)                          
					{    
						sprite[i].base_anim = 12;           
						sprite[i].value2 = -1;
						Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

						if(sta2_shop.hire_type[(i-1)] != STA2_VOID)
						{  
							sprite[i].value2 = (i-1);     
							sprite[i].base_anim = sta2_shop.hire_face[(i-1)];   
							Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
						} 

					}          
				}
				if(sta2_shop_tab == SHOP_PACKS)     
				{ 
					sprintf( new_counter[2].word, "Click on a weapon pack to^purchase one.", sta2_gold); 

					// Packs...     
					for(int i = 1;i<7;i++)                                         
					{    
						sprite[i].base_anim = 12;               
						sprite[i].value2 = -1;
						Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

						if(sta2_shop.pack_type[(i-1)] != STA2_VOID) 
						{  
							if(sprite[i].value1 > 0)  
							{
								sprite[sprite[i].value1].alpha = 1.0f; 

								if(sta2_shop.pack_special[(i-1)] != PACK_SPECIAL_NONE)
								{
									sprite[sprite[i].value1+1].alpha = 1.0f;
									// Lvl..
								    sprite[sprite[i].value1+1].anim = 15 + sta2_shop.pack_special[(i-1)];
								    sprite[sprite[i].value1+1].base_anim = 15 + sta2_shop.pack_special[(i-1)];
								}

								if(sta2_shop.pack_type[(i-1)] == STA2_SCOUT)
								{
									sprite[sprite[i].value1].anim = 9;
									sprite[sprite[i].value1].base_anim = 9;
								}

								if(sta2_shop.pack_type[(i-1)] == STA2_HEAVY)
								{
									sprite[sprite[i].value1].anim = 10;
									sprite[sprite[i].value1].base_anim = 10;
								}

								if(sta2_shop.pack_type[(i-1)] == STA2_SNIPER) 
								{
									sprite[sprite[i].value1].anim = 11;
									sprite[sprite[i].value1].base_anim = 11;
								} 

								if(sta2_shop.pack_type[(i-1)] == STA2_MORTAR)
								{
									sprite[sprite[i].value1].anim = 12;
									sprite[sprite[i].value1].base_anim = 12; 
								}

								Set_Sprite(sprite[i].value1, sprite[sprite[i].value1].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
								Set_Sprite(sprite[i].value1+1, sprite[sprite[i].value1+1].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
								 
							} 

							sprite[i].value2 = (i-1);  

							if(sta2_shop.pack_rank[(i-1)] == 1)  
								sprite[i].base_anim = 16;   
							if(sta2_shop.pack_rank[(i-1)] == 2)
								sprite[i].base_anim = 18;    
							if(sta2_shop.pack_rank[(i-1)] == 3)
								sprite[i].base_anim = 22;   
							if(sta2_shop.pack_rank[(i-1)] == 4)
								sprite[i].base_anim = 23;   
							if(sta2_shop.pack_rank[(i-1)] == 5)
								sprite[i].base_anim = 24;   
							if(sta2_shop.pack_rank[(i-1)] == 6)
								sprite[i].base_anim = 25;   
							if(sta2_shop.pack_rank[(i-1)] == 7)
								sprite[i].base_anim = 26;   
							if(sta2_shop.pack_rank[(i-1)] == 8) 
								sprite[i].base_anim = 27;   
							if(sta2_shop.pack_rank[(i-1)] == 9) 
								sprite[i].base_anim = 28;    

							if(sta2_shop.pack_extra[(i-1)] == PACK_EXTRA_MEDKIT) 
							{
								sprite[(i-1)+14].id = 11;
								sprite[(i-1)+14].alpha = 1.0f;
								Set_Sprite((i-1)+14, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
							}
							 
							if(sta2_shop.pack_extra[(i-1)] == PACK_EXTRA_GRENADE) 
							{
								sprite[(i-1)+14].id = 11;
								sprite[(i-1)+14].alpha = 1.0f;
								Set_Sprite((i-1)+14, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
							} 

							Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
						}

					}  
				} 

				new_counter[3].alpha = 0.0f;  
				new_counter[5].alpha = 0.0f; 

				// Squad roster...  
				for(int i = 1;i<7;i++)                     
				{  
				  
					// Roster face... 
					if(sprite[i].alpha == 1.0)                      
					if(sprite[i].value2 != -1)
					if(( mouseX < (sprite[i].w + sprite[i].box_width) )
					&&( mouseX > sprite[i].w)                            
					&&( mouseY < (sprite[i].z + sprite[i].box_height) )
					&&( mouseY > sprite[i].z)) 
					{         

						new_counter[3].alpha = 1.0f;               
					   
						new_counter[3].x = mouseX + 0.13f;                  
						new_counter[3].y = mouseY;    

						new_counter[5].alpha = 1.0f;               
					    
						new_counter[5].x = mouseX + 0.1f;                  
						new_counter[5].y = mouseY;  
					 
						sprintf( new_counter[5].word, "@");

						if(sta2_shop_tab == SHOP_FOOD) 
						if(sprite[i].value2 != -1)      
						{
							if(sta2_shop.food_type[sprite[i].value2] == SHOP_FOOD_DEER)
    							sprintf( new_counter[3].word, "Delicious deer^meat %iF^only %iG!", sta2_shop.food_amount[sprite[i].value2], sta2_shop.food_cost[sprite[i].value2]);	 
							if(sta2_shop.food_type[sprite[i].value2] == SHOP_FOOD_RACOON)
    							sprintf( new_counter[3].word, "Quality dead^racoon %iF^only %iG!", sta2_shop.food_amount[sprite[i].value2], sta2_shop.food_cost[sprite[i].value2]);	 
							if(sta2_shop.food_type[sprite[i].value2] == SHOP_FOOD_RABBIT)
    							sprintf( new_counter[3].word, "Tasty tough^rabbit %iF^only %iG!", sta2_shop.food_amount[sprite[i].value2], sta2_shop.food_cost[sprite[i].value2]);	 
							if(sta2_shop.food_type[sprite[i].value2] == SHOP_FOOD_YETI_BIG)
    							sprintf( new_counter[3].word, "Delicious yeti^pie %iF^only %iG!", sta2_shop.food_amount[sprite[i].value2], sta2_shop.food_cost[sprite[i].value2]);	 
							if(sta2_shop.food_type[sprite[i].value2] == SHOP_FOOD_YETI_SMALL)
    							sprintf( new_counter[3].word, "Quality yeti^burgers %iF^only %iG!", sta2_shop.food_amount[sprite[i].value2], sta2_shop.food_cost[sprite[i].value2]);	 
							if(sta2_shop.food_type[sprite[i].value2] == SHOP_FOOD_ICE)
    							sprintf( new_counter[3].word, "Tasty snow^cakes %iF^only %iG!", sta2_shop.food_amount[sprite[i].value2], sta2_shop.food_cost[sprite[i].value2]);	 
							if(sta2_shop.food_type[sprite[i].value2] == SHOP_FOOD_SNAKE_BIG)
    							sprintf( new_counter[3].word, "Delicious snake^steaks %iF^only %iG!", sta2_shop.food_amount[sprite[i].value2], sta2_shop.food_cost[sprite[i].value2]);	 
							if(sta2_shop.food_type[sprite[i].value2] == SHOP_FOOD_SNAKE_SMALL)
    							sprintf( new_counter[3].word, "Quality dead^snake %iF^only %iG!", sta2_shop.food_amount[sprite[i].value2], sta2_shop.food_cost[sprite[i].value2]);	 
							if(sta2_shop.food_type[sprite[i].value2] == SHOP_FOOD_SCORPION)
    							sprintf( new_counter[3].word, "Tasty burnt^scorpion %iF^only %iG!", sta2_shop.food_amount[sprite[i].value2], sta2_shop.food_cost[sprite[i].value2]);	 
							if(sta2_shop.food_type[sprite[i].value2] == SHOP_FOOD_CROW_BIG)
    							sprintf( new_counter[3].word, "Delicious crow^pie %iF^only %iG!", sta2_shop.food_amount[sprite[i].value2], sta2_shop.food_cost[sprite[i].value2]);	 
							if(sta2_shop.food_type[sprite[i].value2] == SHOP_FOOD_CROW_SMALL)
    							sprintf( new_counter[3].word, "Quality crow^drumsticks %iF^only %iG!", sta2_shop.food_amount[sprite[i].value2], sta2_shop.food_cost[sprite[i].value2]);	 
							if(sta2_shop.food_type[sprite[i].value2] == SHOP_FOOD_RAT)
    							sprintf( new_counter[3].word, "Tasty dead^rat %iF^only %iG!", sta2_shop.food_amount[sprite[i].value2], sta2_shop.food_cost[sprite[i].value2]);	 
							 
						} 
						if(sta2_shop_tab == SHOP_MEDIC) 
						if(sprite[i].value2 != -1) 
    						sprintf( new_counter[3].word, "HP:%i/%i^%s LVL%i", sta2_squad[sprite[i].value2].health, TotalSquadScore(sprite[i].value2),  sta2_squad[sprite[i].value2].string, sta2_squad[sprite[i].value2].rank);	 

						if(sta2_shop_tab == SHOP_HIRE) 
						if(sprite[i].value2 != -1)  
    						sprintf( new_counter[3].word, "HP:%i/%i^%s LVL%i^COST:%iG", sta2_shop.hire_score[sprite[i].value2], sta2_shop.hire_score[sprite[i].value2],  sta2_shop.hire_string[sprite[i].value2], sta2_shop.hire_rank[sprite[i].value2], sta2_shop.hire_cost[sprite[i].value2]);	 
						 
						if(sta2_shop_tab == SHOP_PACKS)   
						if(sprite[i].value2 != -1)  
						{ 
							sprintf(string_value, ""); 
							sprintf(new_counter[2].word, "");

    						sprintf( new_counter[3].word, "%s^LVL%i^COST:%iG", sta2_shop.pack_string[sprite[i].value2], sta2_shop.pack_rank[sprite[i].value2], sta2_shop.pack_cost[sprite[i].value2]);	 
							 
						//	sprintf(string_value, "COST %iG^", sta2_shop.pack_cost[sprite[i].value2]);
						//	strcat(new_counter[2].word, string_value);

							if(sta2_shop.pack_type[sprite[i].value2] == STA2_SCOUT)
							{							
								sprintf(string_value, "PISTOL DAMAGE %i-%i^", PISTOL1_BASE_FP + sta2_shop.pack_rank[sprite[i].value2]*10, PISTOL1_BASE_FP + PISTOL1_BASE_FP_RANDOM + sta2_shop.pack_rank[sprite[i].value2]*10);
								strcat(new_counter[2].word, string_value);

								sprintf(string_value, "RIFLE DAMAGE %i-%i^", RIFLE1_BASE_FP + sta2_shop.pack_rank[sprite[i].value2]*20, RIFLE1_BASE_FP + RIFLE1_BASE_FP_RANDOM + sta2_shop.pack_rank[sprite[i].value2]*20);
								strcat(new_counter[2].word, string_value);
							}
							if(sta2_shop.pack_type[sprite[i].value2] == STA2_HEAVY)
							{
								sprintf(string_value, "SHOTGUN DAMAGE %i-%i^", (sta2_shop.pack_rank[sprite[i].value2]*20), 45 + (sta2_shop.pack_rank[sprite[i].value2]*20));
								strcat(new_counter[2].word, string_value);

								sprintf(string_value, "MACHINE DAMAGE %i-%i^", (sta2_shop.pack_rank[sprite[i].value2]*20), 20 + (sta2_shop.pack_rank[sprite[i].value2]*20));
								strcat(new_counter[2].word, string_value);
							}
							if(sta2_shop.pack_type[sprite[i].value2] == STA2_SNIPER)
							{
								sprintf(string_value, "PISTOL DAMAGE %i-%i^", PISTOL1_BASE_FP + sta2_shop.pack_rank[sprite[i].value2]*10, PISTOL1_BASE_FP + PISTOL1_BASE_FP_RANDOM + sta2_shop.pack_rank[sprite[i].value2]*10);
								strcat(new_counter[2].word, string_value);

								sprintf(string_value, "SNIPER DAMAGE %i-%i^", SNIPER1_BASE_FP + sta2_shop.pack_rank[sprite[i].value2]*20, SNIPER1_BASE_FP + RIFLE1_BASE_FP_RANDOM + (sta2_shop.pack_rank[sprite[i].value2]*20));
								strcat(new_counter[2].word, string_value);
							}
							if(sta2_shop.pack_type[sprite[i].value2] == STA2_MORTAR)
							{
								sprintf(string_value, "PISTOL DAMAGE %i-%i^", PISTOL1_BASE_FP + sta2_shop.pack_rank[sprite[i].value2]*10, PISTOL1_BASE_FP + PISTOL1_BASE_FP_RANDOM + sta2_shop.pack_rank[sprite[i].value2]*10);
								strcat(new_counter[2].word, string_value);

								sprintf(string_value, "MORTAR DAMAGE %i-%i^", 1, 60 + (sta2_shop.pack_rank[sprite[i].value2]*30));
								strcat(new_counter[2].word, string_value); 
							}

							if(sta2_shop.pack_extra[sprite[i].value2] == PACK_EXTRA_NONE) 
								sprintf(string_value, "EXTRA : NONE^"); 

							if(sta2_shop.pack_extra[sprite[i].value2] == PACK_EXTRA_MEDKIT)
								sprintf(string_value, "EXTRA : MEDKIT %i-%i^", 1, STA2_HEAL_AMOUNT + (sta2_shop.pack_rank[sprite[i].value2]*20));
							 
							if(sta2_shop.pack_extra[sprite[i].value2] == PACK_EXTRA_GRENADE)
								sprintf(string_value, "EXTRA : GRENADE %i-%i^", 1, STA2_GRENADE_AMOUNT + (sta2_shop.pack_rank[sprite[i].value2]*30) );

							strcat(new_counter[2].word, string_value); 

							if(sta2_shop.pack_special[sprite[i].value2] == PACK_SPECIAL_NONE) 
								sprintf(string_value, "SPECIAL : NONE"); 
							if(sta2_shop.pack_special[sprite[i].value2] == PACK_SPECIAL_SCOPE)
								sprintf(string_value, "SPECIAL : SCOPE");
							if(sta2_shop.pack_special[sprite[i].value2] == PACK_SPECIAL_SHIELD)
								sprintf(string_value, "SPECIAL : SHIELD");
							if(sta2_shop.pack_special[sprite[i].value2] == PACK_SPECIAL_DUMDUM)
								sprintf(string_value, "SPECIAL : RAGE");
							if(sta2_shop.pack_special[sprite[i].value2] == PACK_SPECIAL_BOOTS)
								sprintf(string_value, "SPECIAL : DASH");
							if(sta2_shop.pack_special[sprite[i].value2] == PACK_SPECIAL_GODEYE)
								sprintf(string_value, "SPECIAL : GOD-EYE"); 
							if(sta2_shop.pack_special[sprite[i].value2] == PACK_SPECIAL_MAGICNET)
								sprintf(string_value, "SPECIAL : CLOAK");
							if(sta2_shop.pack_special[sprite[i].value2] == PACK_SPECIAL_VAMPIRE)
								sprintf(string_value, "SPECIAL : VAMPIRE");
							if(sta2_shop.pack_special[sprite[i].value2] == PACK_SPECIAL_MAGICHERB)
								sprintf(string_value, "SPECIAL : MARYJANE");
							if(sta2_shop.pack_special[sprite[i].value2] == PACK_SPECIAL_XPGAIN)
								sprintf(string_value, "SPECIAL : WISDOM");
							if(sta2_shop.pack_special[sprite[i].value2] == PACK_SPECIAL_DEATHBLOW)
								sprintf(string_value, "SPECIAL : FINAL");
							if(sta2_shop.pack_special[sprite[i].value2] == PACK_SPECIAL_LASTCHANCE)
								sprintf(string_value, "SPECIAL : LAST");

							strcat(new_counter[2].word, string_value);

						}   
						 
						// For left-sided messages, get longest line...
						if( new_counter[3].x >= sta2_left_of_screen) 
						{ 
							slongest_line = GetLongestLine(new_counter[3].word);
							   
							new_counter[5].x = mouseX - 0.03f;  
							new_counter[3].x = new_counter[5].x - (slongest_line*0.0245f);  

						} 

						// Heal the unit 
						if(mouseleft == true)  
						{ 
							mouseleft = false; 

							if(sta2_shop_tab == SHOP_FOOD)
							if(sprite[i].value2 != -1) 
							if(sta2_gold >= sta2_shop.food_cost[sprite[i].value2])
							{ 

								// Remove food item from shop....
								sta2_shop.food_type[sprite[i].value2] = SHOP_FOOD_NONE; 

								cash_sfx = true;    

								sta2_gold -= sta2_shop.food_cost[sprite[i].value2]; 
								sta2_food += sta2_shop.food_amount[sprite[i].value2];
							}       

							if(sta2_shop_tab == SHOP_MEDIC)
							if(sta2_gold >= sta2_shop.heal_cost)  
							if(sta2_squad[sprite[i].value2].health < TotalSquadScore(sprite[i].value2))
							{   

								cash_sfx = true; 

								sta2_gold -= sta2_shop.heal_cost; 
								sta2_squad[sprite[i].value2].health += 15;

								if(sta2_squad[sprite[i].value2].health > TotalSquadScore(sprite[i].value2))
									sta2_squad[sprite[i].value2].health = TotalSquadScore(sprite[i].value2);
	
							}
							      
							if(sta2_shop_tab == SHOP_HIRE)
							if(sta2_gold >= sta2_shop.hire_cost[sprite[i].value2])  
							{   
								 
								cash_sfx = true;

								hired_wp = 0 ;

								// Add weapon pack for the hired unit....
								for(int k = 0;k < STA2_PACKS_LIMIT;k++) 
								{ 
									// Find an empty pack slot...  
									if(sta2_pack[k].type == STA2_VOID) 
									{
										sta2_pack[k].type = STA2_SCOUT;          
										sta2_pack[k].rank = sta2_sector-1;     
										sta2_pack[k].equipped = true; 
										sta2_pack[k].extra = PACK_EXTRA_NONE;      // PACK_EXTRA_MEDKIT
										sta2_pack[k].extra_charge = 0;
										sta2_pack[k].special = PACK_SPECIAL_NONE;  // PACK_EXTRA_MEDKIT
										sta2_pack[k].special_charge = 0;
										sprintf(sta2_pack[k].string, "SCOUT PACK");   

										if(sta2_sector == 1) 
											sta2_pack[k].rank = 1;

										if(sta2_shop.hire_type[sprite[i].value2] == STA2_HEAVY)
										{
											sta2_pack[k].type = STA2_HEAVY;  
											sprintf(sta2_pack[k].string, "HEAVY PACK"); 
										}

										if(sta2_shop.hire_type[sprite[i].value2] == STA2_SNIPER)
										{
											sta2_pack[k].type = STA2_SNIPER;  
											sprintf(sta2_pack[k].string, "SNIPER PACK"); 
										}
										  
										if(sta2_shop.hire_type[sprite[i].value2] == STA2_MORTAR)
										{
											sta2_pack[k].type = STA2_MORTAR;  
											sprintf(sta2_pack[k].string, "MORTAR PACK"); 
										}

										hired_wp = k; 
										
									}
									 
									if(hired_wp != 0)
										break;
								} 

								if(sprite[i].value2 >= 0)
								{
									sta2_gold -= sta2_shop.hire_cost[sprite[i].value2]; 
				  
									sta2_squad[sta2_squad_count].health = sta2_shop.hire_score[sprite[i].value2];  
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = sta2_shop.hire_face[sprite[i].value2];
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = sta2_shop.hire_rank[sprite[i].value2]; 
									sta2_squad[sta2_squad_count].type = sta2_shop.hire_type[sprite[i].value2]; 
									sta2_squad[sta2_squad_count].wp = hired_wp; 
									sprintf(sta2_squad[sta2_squad_count].string, "%s", sta2_shop.hire_string[sprite[i].value2]);
									sta2_squad_count++;  

									sta2_shop.hire_type[sprite[i].value2] = STA2_VOID;
								}
	
							} 

							if(sta2_shop_tab == SHOP_PACKS)
							if(sta2_gold >= sta2_shop.pack_cost[sprite[i].value2])  
							{    
								   
								cash_sfx = true; 

								sta2_gold -= sta2_shop.pack_cost[sprite[i].value2]; 

								  
								// Add weapon pack to players pack list....
								for(int k = 0;k < STA2_PACKS_LIMIT;k++) 
								{ 
									// Find an empty pack slot...  
									if(sta2_pack[k].type == STA2_VOID) 
									{
										sta2_pack[k].equipped = false;
										sta2_pack[k].type = sta2_shop.pack_type[sprite[i].value2];
										sta2_pack[k].rank = sta2_shop.pack_rank[sprite[i].value2];

										if(sta2_shop.pack_extra[sprite[i].value2] == PACK_EXTRA_MEDKIT)
										{
											sta2_pack[k].extra = PACK_EXTRA_MEDKIT;
											sta2_pack[k].extra_charge = 1; 
										}
										if(sta2_shop.pack_extra[sprite[i].value2] == PACK_EXTRA_GRENADE)
										{
											sta2_pack[k].extra = PACK_EXTRA_GRENADE;
											sta2_pack[k].extra_charge = 1; 
										}

										sta2_pack[k].special = sta2_shop.pack_special[sprite[i].value2];
										sta2_pack[k].active1 = sta2_shop.pack_active1[sprite[i].value2];
										sta2_pack[k].active2 = sta2_shop.pack_active2[sprite[i].value2];
										sta2_pack[k].active3 = sta2_shop.pack_active3[sprite[i].value2];
										sta2_pack[k].active4 = sta2_shop.pack_active4[sprite[i].value2];

										sta2_pack[k].special_charge = 0;

										sprintf(sta2_pack[k].string, "%s", sta2_shop.pack_string[sprite[i].value2]);

										sta2_shop.pack_type[sprite[i].value2] = STA2_VOID;

										sprite[sprite[i].value2 + 14].alpha = 0.0f;
										
									}
									 
									if(sta2_shop.pack_type[sprite[i].value2] == STA2_VOID)
										break;
								}

							}

						}

					} // sprite[i].alpha == 1.0
				} // int i = 1;i<7;i++

				// Turn off arrows if roster is too small etc...
				if(sta2_squad_count < 7)      
				{    
					sprite[12].base_anim = 3;  
					Set_Sprite(12, sprite[12].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}
				else
				{ 
					sprite[12].base_anim = 2;  
					Set_Sprite(12, sprite[12].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}
			 
				// Turn off arrows if roster is too small etc...
				if(sta2_squadpage_index == 0)      
				{ 
					sprite[11].base_anim = 1;   
					Set_Sprite(11, sprite[11].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}
				else 
				{
					sprite[11].base_anim = 0;  
					Set_Sprite(11, sprite[11].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}

				if(sta2_shop_tab != SHOP_MEDIC)
				{
					sprite[12].base_anim = 3;  
					Set_Sprite(12, sprite[12].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
					sprite[11].base_anim = 1;   
					Set_Sprite(11, sprite[11].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}
			 
				// Arrow left 
				if(sprite[11].alpha == 1.0)    
				if(sprite[11].base_anim != 1)
				if(( mouseX < (sprite[11].w + sprite[11].box_width) )
				&&( mouseX > sprite[11].w)                            
				&&( mouseY < (sprite[11].z + sprite[11].box_height) )
				&&( mouseY > sprite[11].z)) 
				if(mouseleft == true)
				{
					mouseleft = false;  

					if(sta2_squadpage_index >= 1)
						sta2_squadpage_index--;
				}
			 
				// Arrow right
				if(sprite[12].alpha == 1.0) 
				if(sprite[12].base_anim != 3)
				if(( mouseX < (sprite[12].w + sprite[12].box_width) )
				&&( mouseX > sprite[12].w)                            
				&&( mouseY < (sprite[12].z + sprite[12].box_height) )
				&&( mouseY > sprite[12].z)) 
				if(mouseleft == true)
				{
					mouseleft = false; 

					if(sta2_squadpage_index <= (24))
						sta2_squadpage_index++;
				}

		   } // title_sequence == 1


	   }
	    
	          
    // ******************************************************************************//
    //                              1-5  (SQUAD SCREEN)                              //
    // ******************************************************************************//
           
       // Title Screen Stuff...            
       if(!mode) 
       if(next_scene == false)  
       if(episode == 1 && scene == 5)    
       {       

		    if(sta2_battle_ready == false)
				SwipeCode(f_rate); 

            if(title_sequence == 0)               
            {       

				if(sta2_is_epic_battle == true)  
				if(sta2_battle_ready == true)  
				{
					sta2_increment = 0.125f;  
					 
					for(int i = 7; i < 12;i++)
					{
						sprite[i].x -= sta2_increment;
						sprite[i].w -= sta2_increment;
					}
					 
					for(int i = 13; i < 23;i++)
					{
						sprite[i].x -= sta2_increment;
						sprite[i].w -= sta2_increment;
					}

				} 

				if(sta2_is_epic_battle == false)
				{
					sprite[11].alpha = 0.0f;
					sprite[17].alpha = 0.0f;
					sprite[22].alpha = 0.0f;
				}
				 
				if(sta2_battle_ready == true)
				if(sta2_playing_tutorial == true)
				if(sta2_yes_no_page_squad == 0)
				{
					sta2_yes_no_active = true;
				}

				sta2_equip_this_unit = -1;
				 
				if(sta2_battle_ready == false) 
				{

					sprintf( new_counter[2].word, "3. Back");  

					new_counter[2].alpha = 1.0f;                 
					new_counter[2].id = 0;  
		      
					if(screen_mode == SCREEN_1610_WIDESCREEN)
						new_counter[2].x = +0.46f;        
					else
						new_counter[2].x = +0.50f;       

					new_counter[2].y = -0.34f;  	      

					new_counter[2].w = new_counter[2].x - 0.026f;   
					new_counter[2].z = new_counter[2].y - 0.015f;

					new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
					new_counter[2].box_height = new_counter[2].height - 0.015f;	
	
					sprintf( new_counter[3].word, "1. Rations");  

					new_counter[3].alpha = 1.0f;         
					new_counter[3].id = 0; 
		       
					new_counter[3].x = -0.60f;     
					new_counter[3].y = -0.34f;  	      

					new_counter[3].w = new_counter[3].x - 0.026f;   
					new_counter[3].z = new_counter[3].y - 0.015f;

					new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
					new_counter[3].box_height = new_counter[3].height - 0.015f;	

					sprintf( new_counter[4].word, "2. Tactics");  

					new_counter[4].alpha = 1.0f;        
					new_counter[4].id = 0; 
		       
					new_counter[4].x = -0.10f;     
					new_counter[4].y = -0.34f;  	      

					new_counter[4].w = new_counter[4].x - 0.026f;   
					new_counter[4].z = new_counter[4].y - 0.015f;

					new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
					new_counter[4].box_height = new_counter[4].height - 0.015f;	

				}
				else
				{
					new_counter[2].alpha = 0.0f;
					new_counter[4].alpha = 0.0f;

					sprintf( new_counter[3].word, "1. Fight!");  

					new_counter[3].alpha = 1.0f;        
					new_counter[3].id = 0; 
		       
					new_counter[3].x = -0.10f;     
					new_counter[3].y = -0.34f;  	      

					new_counter[3].w = new_counter[3].x - 0.026f;   
					new_counter[3].z = new_counter[3].y - 0.015f;

					new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
					new_counter[3].box_height = new_counter[3].height - 0.015f;	
	
				} 
				 
				// Create sprites for pack buffs... 
			    for(int i = 13; i < 18;i++)     
			    {      

					sprite[i].value1 = no_sprites;  

					sprite[no_sprites].id = 7;  

					sprite[no_sprites].light = 1.0f;
					 
					sprite[no_sprites].priority = 1;

					sprite[no_sprites].fx_id = animation_fx[sprite[no_sprites].id];

				    sprite[no_sprites].depth = 0.0f;
				    
				    sprite[no_sprites].x = sprite[i].x;  
				    sprite[no_sprites].y = sprite[i].y;  

				    sprite[no_sprites].w = sprite[i].w; 
				    sprite[no_sprites].z = sprite[i].z; 

				    sprite[no_sprites].width = sprite[i].width; 
				    sprite[no_sprites].height = sprite[i].height; 
				    sprite[no_sprites].box_width = sprite[i].box_width; 
				    sprite[no_sprites].box_height = sprite[i].box_height; 

				    sprite[no_sprites].alpha = 0.0f;   

					sprite[no_sprites].type = NON;
					 
				    sprite[no_sprites].mouseover = false;
				    
				    sprite[no_sprites].turn_off = false; 

					sprite[no_sprites].anim = 12; 

					sprite[no_sprites].cur = 0;    

					sprite[no_sprites].cur_time = 0;
                         
					sprite[no_sprites].anim_state = LOOP;
                
#ifndef DREAMCAST
					sprite[no_sprites].frame = a_texture[sprite[no_sprites].fx_id].anims[sprite[no_sprites].anim][sprite[no_sprites].cur];
#else
					sprite[no_sprites].frame = a_texture_get_anims_secondlayer(sprite[no_sprites].fx_id, sprite[no_sprites].anim, sprite[no_sprites].cur);
#endif
            
					sprite[no_sprites].base_anim = sprite[no_sprites].anim;

					Set_Sprite(no_sprites, sprite[no_sprites].anim, LOOP, ANIM_SPRITE, ANIM_WALKING);

					no_sprites++;   
					 
				} 

				sta2_wounded_start = no_sprites;

				if(sta2_is_epic_battle == false) 
					index = 11;
				else
					index = 12;

				// Create sprites for wounded... 
			    for(int i = 1; i < index;i++)     
			    {      

					sprite[no_sprites].id = 9;  

					sprite[no_sprites].light = 1.0f;
					 
					sprite[no_sprites].priority = 1;

					sprite[no_sprites].fx_id = animation_fx[sprite[no_sprites].id];

				    sprite[no_sprites].depth = 0.0f;
				    
				    sprite[no_sprites].x = sprite[i].x;  
				    sprite[no_sprites].y = sprite[i].y;  

				    sprite[no_sprites].w = sprite[i].w; 
				    sprite[no_sprites].z = sprite[i].z; 

				    sprite[no_sprites].width = sprite[i].width; 
				    sprite[no_sprites].height = sprite[i].height; 
				    sprite[no_sprites].box_width = sprite[i].box_width; 
				    sprite[no_sprites].box_height = sprite[i].box_height; 

				    sprite[no_sprites].alpha = 0.0f;    

					sprite[no_sprites].type = NON;
					 
				    sprite[no_sprites].mouseover = false;
				    
				    sprite[no_sprites].turn_off = false; 

					sprite[no_sprites].anim = 42; 

					sprite[no_sprites].cur = 0;    

					sprite[no_sprites].cur_time = 0;
                         
					sprite[no_sprites].anim_state = LOOP;
                
#ifndef DREAMCAST
					sprite[no_sprites].frame = a_texture[sprite[no_sprites].fx_id].anims[sprite[no_sprites].anim][sprite[no_sprites].cur];
#else
					sprite[no_sprites].frame = a_texture_get_anims_secondlayer(sprite[no_sprites].fx_id, sprite[no_sprites].anim, sprite[no_sprites].cur);
#endif
            
					sprite[no_sprites].base_anim = sprite[no_sprites].anim;

					Set_Sprite(no_sprites, sprite[no_sprites].anim, LOOP, ANIM_SPRITE, ANIM_WALKING);

					no_sprites++;   

				} 
				    
                title_sequence++;                               
            }     

			Set_Sprite(3, 2, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Point Arrow 

			hud[3].alpha = 0.0f; 

			new_counter[11].alpha = 0.0f; 
			new_counter[7].alpha  = 0.0f;
			 
			if(sta2_yes_no_active == true) 
			{ 

				hud[3].alpha = 1.0f;

				if(sta2_yes_no_page_squad == 0) 
				{
					new_counter[11].alpha = 1.0f;    
					new_counter[11].id = 0;
					sprintf(new_counter[11].word, "Click a unit^face to deploy^that unit to^fight."); 
					new_counter[11].x = hud[3].x + 0.042f;  
					new_counter[11].y =  hud[3].y + hud[3].height - 0.1f;

					new_counter[7].alpha = 1.0f;  
					new_counter[7].id = 0;
					sprintf(new_counter[7].word, "1. Next"); 
					new_counter[7].x = hud[3].x + 0.042f;  
					new_counter[7].y =  hud[3].y + hud[3].height - 0.1f - 0.20f;
					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;
					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	
				}
				 
				if(sta2_yes_no_page_squad == 1) 
				{
					new_counter[11].alpha = 1.0f;    
					new_counter[11].id = 0;
					sprintf(new_counter[11].word, "Click a gun^to change^that unit$s^equipment."); 
					new_counter[11].x = hud[3].x + 0.042f;  
					new_counter[11].y =  hud[3].y + hud[3].height - 0.1f;

					new_counter[7].alpha = 1.0f;  
					new_counter[7].id = 0;
					sprintf(new_counter[7].word, "1. Next"); 
					new_counter[7].x = hud[3].x + 0.042f;  
					new_counter[7].y =  hud[3].y + hud[3].height - 0.1f - 0.20f;
					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;
					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	
				}
				 
				if(sta2_yes_no_page_squad == 2) 
				{
					new_counter[11].alpha = 1.0f;    
					new_counter[11].id = 0;
					sprintf(new_counter[11].word, "It$s better^to deploy^atleast^three units."); 
					new_counter[11].x = hud[3].x + 0.042f;  
					new_counter[11].y =  hud[3].y + hud[3].height - 0.1f;

					new_counter[7].alpha = 1.0f;  
					new_counter[7].id = 0;
					sprintf(new_counter[7].word, "1. OKAY!"); 
					new_counter[7].x = hud[3].x + 0.042f;  
					new_counter[7].y =  hud[3].y + hud[3].height - 0.1f - 0.20f;
					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;
					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	
				}
			}

		    sta2_roster_count=0;     

			sta2_tactics = TACTIC_KEYS;

			for(int i=18; i < 23;i++)  
				sprite[i].alpha = 0.0f;  
			  
			// Reset the battle squad... 
			for(int i=0 ; i < 12;i++)    
				sta2_battle_squad[i] = -1;    

		    // Calculate Battle squad... 
			if(sta2_squad_count < STA2_SQUAD_LIMIT)
			for(int i=0 ; i < sta2_squad_count;i++)
			{
				if(sta2_squad[i].deployed == true)  
				{
					sta2_battle_squad[sta2_roster_count] = i; // Is roster unit 0
					sta2_roster_count++;
				}   
			}  
			 
			sta2_squad_temp_index = sta2_squadpage_index;  
			sta2_temp_roster_count = 0;  

			// Create a list of deployable units...
			if(sta2_squad_count < STA2_SQUAD_LIMIT)
			for(int j = 0; j < sta2_squad_count;j++)
			{
				if(sta2_squad[j].deployed == false)     
				{
					sta2_temp_roster[sta2_temp_roster_count] = j; 
					sta2_temp_roster_count++;    
				}
			}
			  
			// Squad roster...   
			for(int i = 1;i<7;i++)                        
			{  
				sprite[sta2_wounded_start+(i-1)].alpha = 0.0f; 

				sprite[i].base_anim = 12;         
				sprite[i].value2 = -1;
				Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				if(sta2_squad_temp_index < sta2_temp_roster_count)
				if(sta2_temp_roster[sta2_squad_temp_index] < STA2_SQUAD_LIMIT) 
				if(sta2_squad[sta2_temp_roster[sta2_squad_temp_index]].deployed == false) 
				{ 
					sprite[i].value2 = sta2_temp_roster[sta2_squad_temp_index];
					sprite[i].base_anim = sta2_squad[sta2_temp_roster[sta2_squad_temp_index]].face;   
					sprite[i].score = sta2_squad[sta2_temp_roster[sta2_squad_temp_index]].health; 
					Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				} 
 
				sta2_squad_temp_index++;

			}     

			// Turn off arrows if roster is too small etc...
			if(sta2_temp_roster_count < 7)     
			{    
				sprite[12].base_anim = 3;  
				Set_Sprite(12, sprite[12].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
			}
			else
			{ 
				sprite[12].base_anim = 2;  
				Set_Sprite(12, sprite[12].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
			}
			 
			// Turn off arrows if roster is too small etc...
			if(sta2_squadpage_index == 0)      
			{ 
				sprite[23].base_anim = 1;   
				Set_Sprite(23, sprite[23].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
			}
			else  
			{ 
				sprite[23].base_anim = 0;  
				Set_Sprite(23, sprite[23].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
			}

			// Battle squad...
			for(int i = 7;i<12;i++)                   
			{   
				sprite[sta2_wounded_start+(i-1)].alpha = 0.0f;

				sprite[i].base_anim = 12;        
				sprite[i].value2 = -1;
				Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				  
				if(sta2_battle_squad[i-7] != -1)
				if(sta2_squad[sta2_battle_squad[i-7]].type != STA2_VOID)   
				{ 
					sprite[i].value2 = sta2_battle_squad[i-7];  
					sprite[i].base_anim = sta2_squad[sta2_battle_squad[i-7]].face;  
					sprite[i].score = sta2_squad[sta2_battle_squad[i-7]].health; 
					Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}

			} 
			 
			// Packs... 
			for(int i = 13;i<18;i++)                       
			{    
				sprite[i].base_anim = 0;      
				sprite[i].value2 = -1; 
				Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				    
				sprite[i+5].alpha = 0.0f; 

				if(sprite[i].value1 >= 0)
					sprite[sprite[i].value1].alpha = 0.0f; 

				if(sta2_battle_squad[i-13] != -1)   
				if(sta2_squad[sta2_battle_squad[i-13]].type != STA2_VOID)  
				if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].type != STA2_VOID)
				{ 
					sprite[i].value2 = sta2_battle_squad[i-13];   

					sprite[i].base_anim = sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].rank;

					if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].extra == PACK_EXTRA_MEDKIT)
					{
						sprite[i+5].alpha = 1.0f;
						Set_Sprite(i+5, 10, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
					}
					 
					if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].extra == PACK_EXTRA_GRENADE)
					{
						sprite[i+5].alpha = 1.0f;
						Set_Sprite(i+5, 11, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
					}
					 
					if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].special != PACK_SPECIAL_NONE)
					{

						if(sprite[i].value1 >= 0)  
						{
							    
							sprite[sprite[i].value1].alpha = 1.0f;

							if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].special == PACK_SPECIAL_SCOPE)
								sprite[sprite[i].value1].anim = 12;
							if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].special == PACK_SPECIAL_SHIELD)
								sprite[sprite[i].value1].anim = 13;
							if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].special == PACK_SPECIAL_DUMDUM)
								sprite[sprite[i].value1].anim = 14;
							if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].special == PACK_SPECIAL_BOOTS)
								sprite[sprite[i].value1].anim = 15;
							if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].special == PACK_SPECIAL_GODEYE)
								sprite[sprite[i].value1].anim = 16;
							if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].special == PACK_SPECIAL_MAGICNET)
								sprite[sprite[i].value1].anim = 17;
							if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].special == PACK_SPECIAL_VAMPIRE)
								sprite[sprite[i].value1].anim = 18;
							if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].special == PACK_SPECIAL_MAGICHERB)
								sprite[sprite[i].value1].anim = 19;
							if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].special == PACK_SPECIAL_XPGAIN)
								sprite[sprite[i].value1].anim = 20;
							if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].special == PACK_SPECIAL_DEATHBLOW)
								sprite[sprite[i].value1].anim = 21;
							if(sta2_pack[sta2_squad[sta2_battle_squad[i-13]].wp].special == PACK_SPECIAL_LASTCHANCE)
								sprite[sprite[i].value1].anim = 22;

							Set_Sprite(sprite[i].value1, sprite[sprite[i].value1].anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
						}
					}

					Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}

			} 

           if(title_sequence == 1)           
           {    

				test_button = 0;  

				// Create a list of deployable units...
				if(sta2_squad_count < STA2_SQUAD_LIMIT)
				for(int j = 0; j < sta2_squad_count;j++) 
				{
					if(sta2_squad[j].deployed == true && sta2_squad[j].health > 1)     
					{
						test_button = 1;
						break;
					} 
				} 
				 
			    new_counter[2].id = 0; 
				new_counter[3].id = 0;
				new_counter[4].id = 0;
				new_counter[7].id = 0;

				if(sta2_battle_ready == true) 
				if(test_button == 0) 
					new_counter[3].id = 4;
				 
				testX = hud_mouseX - (-camX);                                                 
				testY = hud_mouseY - (-camY);   

				if(sta2_yes_no_active == true)
				if(new_counter[7].alpha == 1.0f)
				if(( testX < (new_counter[7].w + new_counter[7].box_width) )
				&&( testX > new_counter[7].w)                            
				&&( testY < (new_counter[7].z + new_counter[7].box_height) )
				&&( testY > new_counter[7].z) || sta2_1_pressed == true)   
				{ 
					new_counter[7].id = 2;    

					if(mouseleft == true || DX_SHOOT == true || sta2_1_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_1_pressed = false;

						sta2_yes_no_page_squad++;

						if(sta2_yes_no_page_squad == 3)
						{
							sta2_yes_no_active = false;
						}

						  
					}    
				}    

				if(new_counter[2].alpha == 1.0f)
				if(( testX < (new_counter[2].w + new_counter[2].box_width) )
				&&( testX > new_counter[2].w)                            
				&&( testY < (new_counter[2].z + new_counter[2].box_height) )
				&&( testY > new_counter[2].z) || sta2_3_pressed == true)   
				{ 
					new_counter[2].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_3_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_3_pressed = false;
					//	sta2_investigate=false;
						 
						episode = 1;  
						scene = 28;

						next_scene = true;
						  
					}    
				}    

				if(new_counter[3].alpha == 1.0f)
				if(new_counter[3].id != 4)
				if(( testX < (new_counter[3].w + new_counter[3].box_width) )
				&&( testX > new_counter[3].w)                            
				&&( testY < (new_counter[3].z + new_counter[3].box_height) )
				&&( testY > new_counter[3].z) || sta2_1_pressed == true)   
				{ 
					new_counter[3].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_1_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_1_pressed = false;
					//	sta2_investigate=false;
						 
						if(sta2_battle_ready == false)
						{
							episode = 1;  
							scene = 8;
						}
						else 
						{
							if(sta2_is_epic_battle == true)
							{
								episode = 4;   
								scene = 0;
							}
							else
							{
								episode = 2;   
								scene = 0;
							}

							sta2_loaded_level = false;
						}

						next_scene = true;
						  
					}
				}  

				if(new_counter[4].alpha == 1.0f)
				if(( testX < (new_counter[4].w + new_counter[4].box_width) )
				&&( testX > new_counter[4].w)                            
				&&( testY < (new_counter[4].z + new_counter[4].box_height) )
				&&( testY > new_counter[4].z) || sta2_2_pressed == true)   
				{ 
					new_counter[4].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_2_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_2_pressed = false;
						 
						episode = 1;  
						scene = 14;

						next_scene = true;
						  
					}    
				}    

			new_counter[0].alpha = 0.0f;
			new_counter[5].alpha = 0.0f; 

			// Test against squad roster...   
			if(sta2_yes_no_active == false)
			for(int i=1;i<7;i++)       
			{ 
				 
				sprite[sta2_wounded_start+(i-1)].alpha = 0.0f;

				if(sprite[i].alpha == 1.0)                       
				if(sprite[i].value2 != -1)
				if(sprite[i].score == 1)
					sprite[sta2_wounded_start+(i-1)].alpha = 1.0f;

				// Roster face...
				if(sprite[i].alpha == 1.0)                       
				if(sprite[i].value2 != -1)
				if(( mouseX < (sprite[i].w + sprite[i].box_width) )
				&&( mouseX > sprite[i].w)                            
				&&( mouseY < (sprite[i].z + sprite[i].box_height) )
				&&( mouseY > sprite[i].z)) 
				{   

					new_counter[0].alpha = 1.0f;               
					   
					new_counter[0].x = mouseX + 0.13f;                   
					new_counter[0].y = mouseY;    

					new_counter[5].alpha = 1.0f;               
					    
					new_counter[5].x = mouseX + 0.1f;                   
					new_counter[5].y = mouseY;   
					 
					sprintf( new_counter[5].word, "@");  

					if(sprite[i].value2 != -1)   
					if(sprite[i].score <= 1)
    					sprintf( new_counter[0].word, "WOUNDED..^%s LVL%i^Click to deploy^", sta2_squad[sprite[i].value2].string, sta2_squad[sprite[i].value2].rank);	 
					else
    					sprintf( new_counter[0].word, "HP:%i/%i^%s LVL%i^Click to deploy^", sta2_squad[sprite[i].value2].health, TotalSquadScore(sprite[i].value2),  sta2_squad[sprite[i].value2].string, sta2_squad[sprite[i].value2].rank);	 

					// For left-sided messages, get longest line...
					if( new_counter[0].x >= sta2_left_of_screen) 
					{ 
						slongest_line = GetLongestLine(new_counter[0].word);  
							   
						new_counter[5].x = mouseX - 0.03f;  
						new_counter[0].x = new_counter[5].x - (slongest_line*0.0245f);  

					}   

					if(sta2_is_epic_battle == true)
						index = 5;
					else
						index = 4; 

					if(mouseleft == true)
					if(sta2_roster_count < index)  
					{
						mouseleft = false;
						sta2_squad[sprite[i].value2].deployed = true;
					}
				}

			}
			// Test against squad roster...    
			if(sta2_yes_no_active == false)
			for(int i=7;i<12;i++)        
			{     
				  
				sprite[sta2_wounded_start+(i-1)].alpha = 0.0f;

				if(sprite[i].alpha == 1.0)                       
				if(sprite[i].value2 != -1)
				if(sprite[i].score == 1)
					sprite[sta2_wounded_start+(i-1)].alpha = 1.0f;

				// Roster face... 
				if(sprite[i].alpha == 1.0)                     
				if(sprite[i].value2 != -1)
				if(( mouseX < (sprite[i].w + sprite[i].box_width) )
				&&( mouseX > sprite[i].w)                            
				&&( mouseY < (sprite[i].z + sprite[i].box_height) )
				&&( mouseY > sprite[i].z)) 
				{
					   
					new_counter[0].alpha = 1.0f;               
					   
					new_counter[0].x = mouseX + 0.13f;                   
					new_counter[0].y = mouseY;    

					new_counter[5].alpha = 1.0f;               
					    
					new_counter[5].x = mouseX + 0.1f;                   
					new_counter[5].y = mouseY;   
					  
					sprintf( new_counter[5].word, "@");    
					 
					if(sprite[i].value2 != -1)   
					if(sprite[i].score <= 1)
    					sprintf( new_counter[0].word, "WOUNDED..^%s LVL%i^Click to swap^",  sta2_squad[sprite[i].value2].string, sta2_squad[sprite[i].value2].rank);	 
					else
    					sprintf( new_counter[0].word, "HP:%i/%i^%s LVL%i^Click to swap^", sta2_squad[sprite[i].value2].health, TotalSquadScore(sprite[i].value2),  sta2_squad[sprite[i].value2].string, sta2_squad[sprite[i].value2].rank);	 

					// For left-sided messages, get longest line...
					if( new_counter[0].x >= sta2_left_of_screen) 
					{ 
						slongest_line = GetLongestLine(new_counter[0].word);  
							   
						new_counter[5].x = mouseX - 0.03f;  
						new_counter[0].x = new_counter[5].x - (slongest_line*0.0245f);  

					}  

					if(mouseleft == true)
					{
						mouseleft = false;
						sta2_squad[sprite[i].value2].deployed = false;
					}
				}

			} 

			// Test against squad roster...   
			if(sta2_yes_no_active == false)
			for(int i=13;i<18;i++)         
			{      
				  
				// Roster face... 
				if(sprite[i].alpha == 1.0)                     
				if(sprite[i].value2 != -1)
				if(( mouseX < (sprite[i].w + sprite[i].box_width) )
				&&( mouseX > sprite[i].w)                            
				&&( mouseY < (sprite[i].z + sprite[i].box_height) )
				&&( mouseY > sprite[i].z)) 
				{  
					        
					new_counter[0].alpha = 1.0f;               
					   
					new_counter[0].x = mouseX + 0.13f;                   
					new_counter[0].y = mouseY;    

					new_counter[5].alpha = 1.0f;               
					    
					new_counter[5].x = mouseX + 0.1f;                   
					new_counter[5].y = mouseY;   
					   
					sprintf( new_counter[5].word, "@"); 
					 
					if(sprite[i].value2 != -1) 
    					sprintf( new_counter[0].word, "Weapon Pack^Click to change^", sta2_squad[sprite[i].value2].health, TotalSquadScore(sprite[i].value2),  sta2_squad[sprite[i].value2].string, sta2_squad[sprite[i].value2].rank);	 

					// For left-sided messages, get longest line...
					if( new_counter[0].x >= sta2_left_of_screen) 
					{ 
						slongest_line = GetLongestLine(new_counter[0].word);  
							   
						new_counter[5].x = mouseX - 0.03f;  
						new_counter[0].x = new_counter[5].x - (slongest_line*0.0245f);  

					}  

					if(mouseleft == true)
					{
						sta2_equip_this_unit = sprite[i].value2;

						episode = 1; 
						scene = 7;

						next_scene = true;

						mouseleft = false;
					}
				}
				 
			}

			  
			// Arrow left 
            if(sprite[23].alpha == 1.0)    
			if(sprite[23].base_anim != 1)
            if(( mouseX < (sprite[23].w + sprite[23].box_width) )
            &&( mouseX > sprite[23].w)                            
            &&( mouseY < (sprite[23].z + sprite[23].box_height) )
            &&( mouseY > sprite[23].z)) 
			if(mouseleft == true)
            {
				mouseleft = false;

				if(sta2_squadpage_index >= 1)
					sta2_squadpage_index--;
		    }
			 
			// Arrow right
            if(sprite[12].alpha == 1.0) 
			if(sprite[12].base_anim != 3)
            if(( mouseX < (sprite[12].w + sprite[12].box_width) )
            &&( mouseX > sprite[12].w)                            
            &&( mouseY < (sprite[12].z + sprite[12].box_height) )
            &&( mouseY > sprite[12].z)) 
			if(mouseleft == true)
            {
				mouseleft = false; 

				if(sta2_squadpage_index <= (24))
					sta2_squadpage_index++;
		    }


		   } // title_sequence == 1 

       }   
 	
    // ******************************************************************************//
    //                            1-3  (SECTOR MAP SCREEN)                           //
    // ******************************************************************************//

       // Sector Map...
       if(!mode)   
       if(next_scene == false)  
       if(episode == 1 && scene == 3)                
       {         

		    // C.O pins...  
		    if(sta2_co_type == STA2_CO_ADA)
				Set_Sprite(1, 70, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
		    if(sta2_co_type == STA2_CO_MARIE)
				Set_Sprite(1, 71, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
		    if(sta2_co_type == STA2_CO_ADELE)
				Set_Sprite(1, 72, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
		    if(sta2_co_type == STA2_CO_BELLA)
				Set_Sprite(1, 73, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 

            testX = hud_mouseX - (-camX);                                              
            testY = hud_mouseY - (-camY);   

           new_counter[2].alpha = 1.0f;     
		   new_counter[2].id = 0; 
		    
		   new_counter[2].x = 0.44f;  
		   new_counter[2].y = 0.36f; 	     

		   sprintf( new_counter[2].word, "");  

		   new_counter[2].x = testX + 0.1f; 
		   new_counter[2].y = testY;

           if(title_sequence == 0)             
           {    
			   
				// Remove any fifth units from squad...
				if(sta2_squad_count < STA2_SQUAD_LIMIT)
				for(int j = 0; j < sta2_squad_count;j++)
				{
					if(sta2_squad[j].deployed == true)     
					{
						unit_count_fifth++;

						if(unit_count_fifth >= 5)
							sta2_squad[j].deployed = false;
					}
				}

			    sta2_general_position = 0.0f;

			    map_pins_sector_count=0;

			    if(sta2_sector_create_pins == true) // Only run once...
				{ 
					for(int i = 0;i < no_sprites;i++)  
					{
						// Assign environment types to the areas...
						if(sprite[i].type >= FE_TYPE1 && sprite[i].type <= FE_TYPE8)
						{
							if(sprite[i].type == FE_TYPE1)
								sprite[i].value2 = sta2_first_area;
							if(sprite[i].type == FE_TYPE2)
							{  
								sprite[i].value2 = rand()%4;
							}
							if(sprite[i].type == FE_TYPE3)     
							{ 
								sprite[i].value2 = rand()%4;
							}
							if(sprite[i].type == FE_TYPE4) 
							{ 
								sprite[i].value2 = 4 + rand()%4;
							}
							if(sprite[i].type == FE_TYPE5)
							{  
								sprite[i].value2 = rand()%10;
							}
							if(sprite[i].type == FE_TYPE6)
							{ 
								sprite[i].value2 = 4 + rand()%4;
							}
							if(sprite[i].type == FE_TYPE7)
							{ 
								sprite[i].value2 = 8 + rand()%2;
							}
							if(sprite[i].type == FE_TYPE8)
								sprite[i].value2 = AREA_TRENCH;

							sprite[i].value1 = map_pins_sector_count;
							map_pins_sector[map_pins_sector_count] = sprite[i].value2;
							map_pins_sector_count++; 

						}

					} 

					sta2_sector_create_pins=false;

				} 
				else
				{
					for(int i = 0;i< no_sprites;i++)
					if(sprite[i].type >= FE_TYPE1 && sprite[i].type <= FE_TYPE8)
					{
						sprite[i].value1 = map_pins_sector_count;
						sprite[i].value2 = map_pins_sector[map_pins_sector_count];
						map_pins_sector_count++;
					}
				}

				// Set-up Pin colors...
				for(int i = 0;i< no_sprites;i++)
				if(sprite[i].type >= FE_TYPE1 && sprite[i].type <= FE_TYPE8)
				{
					if(sprite[i].value2 == -1)
					    sprite[i].base_anim = 10;  
					if(sprite[i].value2 == AREA_GRASSLANDS) 
					    sprite[i].base_anim = 4;  
					if(sprite[i].value2 == AREA_FOREST)
					    sprite[i].base_anim = 1; 
					if(sprite[i].value2 == AREA_SWAMP)
					    sprite[i].base_anim = 2;
					if(sprite[i].value2 == AREA_FARM) 
					    sprite[i].base_anim = 8;
					if(sprite[i].value2 == AREA_DESERT)
					    sprite[i].base_anim = 6; 
					if(sprite[i].value2 == AREA_SNOW)
					    sprite[i].base_anim = 7;  
					if(sprite[i].value2 == AREA_BEACH)
					    sprite[i].base_anim = 6; // Was 9..
					if(sprite[i].value2 == AREA_MOUNTAIN)
					    sprite[i].base_anim = 7; // Was 8..
					if(sprite[i].value2 == AREA_CITY)
					    sprite[i].base_anim = 3;
					if(sprite[i].value2 == AREA_TRENCH) 
					    sprite[i].base_anim = 5;
					if(sprite[i].value2 == AREA_CASTLE)
					    sprite[i].base_anim = 1; 
				}

				sprite[sta2_current_sector_pin].base_anim = 10;
				map_pins_sector[sprite[sta2_current_sector_pin].value1] = -1;

				// Get the current position, create an icon make 
				sprite[1].x = sprite[sta2_current_sector_pin].w; // Icon sprite  
				sprite[1].y = sprite[sta2_current_sector_pin].z; // Icon sprite  

				sprite[1].w = sprite[1].x; 
				sprite[1].z = sprite[1].y; 

				title_sequence++; 

		   }           

		   if(sta2_current_sector_pin > 0) 
		   {
		      targetA = sprite[sta2_current_sector_pin].sector; 
			  targetB = sprite[sta2_current_sector_pin].sector_action;
		   }

			new_counter[0].alpha = 0.0f;                
			new_counter[5].alpha = 0.0f;

		   // Selecting a target pin...
           if(title_sequence == 1)       
           {   
		       
			    
			   new_counter[0].alpha = 0.0f; 
			   new_counter[5].alpha = 0.0f;

			   for(int i = 0;i < no_sprites;i++)
			   { 

				   if(sprite[i].type >= FE_TYPE1 && sprite[i].type <= FE_TYPE8)
				   if(sprite[i].alpha == 1.0f)                   
				   if(( mouseX < (sprite[i].w + sprite[i].box_width) )
				   &&( mouseX > sprite[i].w)                            
				   &&( mouseY < (sprite[i].z + sprite[i].box_height) )
				   &&( mouseY > sprite[i].z))  
				   {   

						new_counter[0].alpha = 1.0f;                
					   
						new_counter[0].x = mouseX + 0.13f;                   
						new_counter[0].y = mouseY;    

						new_counter[5].alpha = 1.0f;               
					    
						new_counter[5].x = mouseX + 0.1f;                    
						new_counter[5].y = mouseY;   
					 
						sprintf( new_counter[5].word, "@");  

					    if(sprite[i].value2 == AREA_GRASSLANDS)
					        sprintf( new_counter[0].word, "GRASSLANDS^");
					    if(sprite[i].value2 == AREA_FOREST)
					        sprintf( new_counter[0].word, "FOREST^");
					    if(sprite[i].value2 == AREA_SWAMP) 
					        sprintf( new_counter[0].word, "SWAMP^");
					    if(sprite[i].value2 == AREA_FARM)
					        sprintf( new_counter[0].word, "FARM^"); 
					    if(sprite[i].value2 == AREA_DESERT)
					        sprintf( new_counter[0].word, "DESERT^"); 
					    if(sprite[i].value2 == AREA_SNOW)      
					        sprintf( new_counter[0].word, "SNOW^");
					    if(sprite[i].value2 == AREA_BEACH)
					        sprintf( new_counter[0].word, "DESERT^"); // Add Beach if I have time..
					    if(sprite[i].value2 == AREA_MOUNTAIN)    
					        sprintf( new_counter[0].word, "SNOW^");   // Add Mountain if I have time..
					    if(sprite[i].value2 == AREA_CITY)
					        sprintf( new_counter[0].word, "CITY^");
					    if(sprite[i].value2 == AREA_TRENCH) 
					        sprintf( new_counter[0].word, "TRENCH^");
					    if(sprite[i].value2 == AREA_CASTLE)
					        sprintf( new_counter[0].word, "CASTLE^");

						// For left-sided messages, get longest line...
						if( new_counter[0].x >= sta2_left_of_screen) 
						{ 
							slongest_line = GetLongestLine(new_counter[0].word);  
							   
							new_counter[5].x = mouseX - 0.03f;  
							new_counter[0].x = new_counter[5].x - (slongest_line*0.0245f);  

						}   

						Set_Sprite(i, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);				

						if(sta2_current_sector_pin != i) 
						if(mouseleft == true || DX_SHOOT == true)  
						{ 
							 
							if(i == targetA || i == targetB)
							{
								title_timer = (int)TimerGetTime() + 250;
								title_sequence++;

								target_pin = i;  
							}
							else
								stolen_sfx=true;

							DX_SHOOT=false;
							mouseleft = false;

						}

				   }
				   else
				   {
						Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);	
				   }

			   }

		   } // title_sequence == 1

		   // Moving towards the target pin...
           if(title_sequence == 2) 
		   if(target_pin != -1)
           {  
			    
			    if((int)TimerGetTime() > title_timer)
				{
					grassstep_sfx = true; 
					title_timer = (int)TimerGetTime() + 250;
				}

			    temp_speed = 0.00005f; 
			    
				mid_x = sprite[1].w+sprite[1].box_width/2; 
				mid_y = sprite[1].z+sprite[1].box_height/2; 
        
				tar_x = sprite[target_pin].w+sprite[target_pin].box_width/2; 
				tar_y = sprite[target_pin].z+sprite[target_pin].box_height/2;   
	
				angle = atan2(tar_y - mid_y, tar_x - mid_x);
     
				deltax = cos(angle); // Was 1.2    
				deltay = sin(angle); // Was 1.2 
        
				deltax *= temp_speed;           
				deltay *= temp_speed; 
     
				deltax *= (float)f_rate;       
				deltay *= (float)f_rate;     
				 
				sprite[1].x += deltax;      
				sprite[1].w += deltax; 
				 
				sprite[1].y += deltay;      
				sprite[1].z += deltay; 

				distance = Node_Distance1(mid_x, mid_y, tar_x, tar_y);

				if(distance <= 0.005f)        
				{
					sprite[1].x = sprite[target_pin].x; 
					sprite[1].y = sprite[target_pin].y;
					sprite[1].w = sprite[target_pin].w;  
					sprite[1].z = sprite[target_pin].z; 
					  
					sta2_current_sector_pin = target_pin;    
					sta2_environment_type = sprite[target_pin].value2;

					target_pin = -1;         
					title_sequence = 3;  
					title_timer = (int)TimerGetTime() + 500;

					sta2_next_event = EVENT_NEW_SECTOR; 
					 
				}      
				   
		   }   

		    // Go to investigate mode...
            if(title_sequence == 3)  
			if((int)TimerGetTime() > title_timer) 
            { 

				title_sequence = 1; 

				sta2_route_create_pins=true;
				sta2_sector++;

				episode = 1; 
				scene = 2;

				next_scene = true;
				 
		    }    
			 
	   }   
 	
    // ******************************************************************************//
    //                            1-0  (ROUTE MAP SCREEN)                            //
    // ******************************************************************************//	      

       // Route Map...   // 9 - Snow // 10 - Grasslands // 11 - Forest // 12 == Swamp // 13 == Farms // 21 == Castle
       if(!mode)  
       if(next_scene == false)  
       if(episode == 1 && (scene == 0 || scene == 9 || scene == 10 || scene == 11 
	   || scene == 12 || scene == 13 || scene == 21 || scene == 22 || scene == 23 || scene == 24)  )                     
       {       
		       
		//    SwipeCode(f_rate);  

		   if(sta2_scroll_route_map == false)
		   {
			   hud[62].alpha = 1.0f;  
			   hud[63].alpha = 1.0f;
			   hud[64].alpha = 1.0f;

			   Set_Sprite(64, 76+sta2_sector, PLAY, ANIM_HUD, ANIM_NOT_WALKING);
		   }
		   else
		   {
			   hud[62].alpha = 0.0f;
			   hud[63].alpha = 0.0f;
			   hud[64].alpha = 0.0f;
		   }

		    if(sta2_scroll_route_map == false)   
			if(sta2_playing_tutorial == true) 
			if(sta2_display_tutorial_text1 == false) 
			{
				sta2_yes_no_page = 1;
				sta2_yes_no_active = true;

				sta2_display_tutorial_text1 = true;  
			}

		    if(sta2_quit_active == true) 
			{
				if(sta2_playing_tutorial == true)
					Set_Sprite(3, 1, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Quit game?
				else
					Set_Sprite(3, 3, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Quit and save?
			}
			else
				Set_Sprite(3, 2, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Point Arrow 

			hud[3].alpha = 0.0f; 
			      
			if(sta2_yes_no_active == true)
			{ 

				hud[3].alpha = 1.0f;
				 
				sta2_tactics = TACTIC_KEYS;

				if(sta2_quit_active == true)
				{
					new_counter[7].alpha = 1.0f; 
					new_counter[7].id = 0;

					sprintf(new_counter[7].word, "1. YES"); 

					new_counter[7].x = hud[3].x + 0.08f;  
					new_counter[7].y =  hud[3].y + hud[3].height - 0.1f;
					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;
					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	
				 
					new_counter[8].alpha = 1.0f;
					new_counter[8].id = 0;

					sprintf(new_counter[8].word, "2. NO"); 

					new_counter[8].x = hud[3].x + 0.08f;  
					new_counter[8].y = hud[3].y + hud[3].height - 0.1f - 0.04f;
					new_counter[8].w = new_counter[8].x - 0.026f;   
					new_counter[8].z = new_counter[8].y - 0.015f;
					new_counter[8].box_width = strlen(new_counter[8].word)   *  0.026f;
					new_counter[8].box_height = new_counter[8].height - 0.015f;	
				}
				if(sta2_quit_active == false)
				if(sta2_yes_no_page == 1)   
				{
					new_counter[11].alpha = 1.0f;    
					new_counter[11].id = 0;
					sprintf(new_counter[11].word, "Click on a^pin to move^your squad^there."); 
					new_counter[11].x = hud[3].x + 0.042f;  
					new_counter[11].y =  hud[3].y + hud[3].height - 0.1f;

					new_counter[7].alpha = 1.0f;   
					new_counter[7].id = 0;
					sprintf(new_counter[7].word, "1. Next"); 
					new_counter[7].x = hud[3].x + 0.042f;  
					new_counter[7].y =  hud[3].y + hud[3].height - 0.1f - 0.20f;
					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;
					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	
				}
				if(sta2_quit_active == false)
				if(sta2_yes_no_page == 2) 
				{
					new_counter[11].alpha = 1.0f;   
					new_counter[11].id = 0;
					sprintf(new_counter[11].word, "Moving costs^food but also^regains squad^health!"); 
					new_counter[11].x = hud[3].x + 0.042f;  
					new_counter[11].y =  hud[3].y + hud[3].height - 0.1f;

					new_counter[7].alpha = 1.0f;  
					new_counter[7].id = 0;
					sprintf(new_counter[7].word, "1. OKAY!"); 
					new_counter[7].x = hud[3].x + 0.042f;  
					new_counter[7].y =  hud[3].y + hud[3].height - 0.1f - 0.20f;
					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;
					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	
				}
				if(sta2_quit_active == false)
				if(sta2_yes_no_page == 3) 
				{
					new_counter[11].alpha = 1.0f;   
					new_counter[11].id = 0;
					sprintf(new_counter[11].word, "Click on^investigate^to scout a^location."); 
					new_counter[11].x = hud[3].x + 0.042f;  
					new_counter[11].y =  hud[3].y + hud[3].height - 0.1f;

					new_counter[7].alpha = 1.0f;  
					new_counter[7].id = 0;
					sprintf(new_counter[7].word, "1. OKAY!"); 
					new_counter[7].x = hud[3].x + 0.042f;  
					new_counter[7].y =  hud[3].y + hud[3].height - 0.1f - 0.20f;
					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;
					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	
				}
				if(sta2_quit_active == false)  
				if(sta2_yes_no_page == 4)  
				{ 
					new_counter[11].alpha = 1.0f;   
					new_counter[11].id = 0;
					sprintf(new_counter[11].word, "Use shops to^heal or^revive your^squad!"); 
					new_counter[11].x = hud[3].x + 0.042f;  
					new_counter[11].y =  hud[3].y + hud[3].height - 0.1f;

					new_counter[7].alpha = 1.0f;  
					new_counter[7].id = 0;
					sprintf(new_counter[7].word, "1. Next"); 
					new_counter[7].x = hud[3].x + 0.042f;  
					new_counter[7].y =  hud[3].y + hud[3].height - 0.1f - 0.20f;
					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;
					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	
				}
				if(sta2_quit_active == false)  
				if(sta2_yes_no_page == 5) 
				{
					new_counter[11].alpha = 1.0f;   
					new_counter[11].id = 0;
					sprintf(new_counter[11].word, "Click on^investigate^to enter a^shop."); 
					new_counter[11].x = hud[3].x + 0.042f;  
					new_counter[11].y =  hud[3].y + hud[3].height - 0.1f;

					new_counter[7].alpha = 1.0f;  
					new_counter[7].id = 0;
					sprintf(new_counter[7].word, "1. OKAY!"); 
					new_counter[7].x = hud[3].x + 0.042f;  
					new_counter[7].y =  hud[3].y + hud[3].height - 0.1f - 0.20f;
					new_counter[7].w = new_counter[7].x - 0.026f;   
					new_counter[7].z = new_counter[7].y - 0.015f;
					new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
					new_counter[7].box_height = new_counter[7].height - 0.015f;	
				}

				 
			}
			else
			{
				new_counter[7].alpha = 0.0f;
				new_counter[8].alpha = 0.0f;
				new_counter[9].alpha = 0.0f;
				new_counter[11].alpha = 0.0f;
			}

		    sta2_battle_ready = false;     

		    sta2_shop.heal_cost = 0; 
			sta2_packpage_index=0;

			for(int j = 0;j< SHOP_LIMIT_ITEMS;j++) 
			{
				sta2_shop.food_type[j] = SHOP_FOOD_NONE; 
				sta2_shop.food_amount[j] = 0; 
				sta2_shop.food_cost[j] = 0; 
				sta2_shop.hire_type[j] = STA2_VOID;    
				sta2_shop.hire_rank[j] = 0; 
				sta2_shop.hire_face[j] = 0;  
				sta2_shop.hire_cost[j] = 0;
				sta2_shop.pack_type[j] = 0;         
				sta2_shop.pack_rank[j] = 0; 
				sta2_shop.pack_cost[j] = 0; 
				sprintf( sta2_shop.hire_string[0], "NONE"); 
			}  
			
			// Reset pack charges...
			for(int j = 0;j< STA2_PACKS_LIMIT;j++)   
			{ 
				if(sta2_pack[j].extra != PACK_EXTRA_NONE)
					sta2_pack[j].extra_charge = 1; 
				if(sta2_pack[j].special != PACK_SPECIAL_NONE)
					sta2_pack[j].special_charge = 0;
			}    

		   sta2_shop_tab = SHOP_FOOD; 

		   sta2_battle_outcome = BATTLE_NONE;  
		    
		   sta2_picked_up_gold=0; 
		   sta2_picked_up_food=0;    

		   if(sta2_playing_tutorial == false)
			   index = 24;
		   else
			   index = 13;
		    
		    // The 'level' name text...
			if(sta2_scroll_route_map == false) 
			{
				new_counter[2].alpha = 1.0f;
				sprite[index].alpha = 0.0f;
			}
			else 
			{ 
				new_counter[2].alpha = 0.0f;     
				sprite[index].alpha = 1.0f;

				if(sta2_environment_type == AREA_GRASSLANDS)
					Set_Sprite(index, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				if(sta2_environment_type == AREA_FOREST)
					Set_Sprite(index, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				if(sta2_environment_type == AREA_SWAMP)
					Set_Sprite(index, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				if(sta2_environment_type == AREA_FARM)
					Set_Sprite(index, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				if(sta2_environment_type == AREA_SNOW)
					Set_Sprite(index, 4, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);  
				if(sta2_environment_type == AREA_DESERT)
					Set_Sprite(index, 5, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				if(sta2_environment_type == AREA_BEACH)
					Set_Sprite(index, 6, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				if(sta2_environment_type == AREA_MOUNTAIN)
					Set_Sprite(index, 7, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				if(sta2_environment_type == AREA_CITY)
					Set_Sprite(index, 8, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				if(sta2_environment_type == AREA_TRENCH)
					Set_Sprite(index, 9, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				if(sta2_environment_type == AREA_CASTLE)
					Set_Sprite(index, 10, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);


			}
			
			sprintf( new_counter[2].word, ""); 

			if(sta2_gold < 10) 
				sprintf( string_value, "²    %iG", sta2_gold);  
			if(sta2_gold >= 10 && sta2_gold < 100)
				sprintf( string_value, "²   %iG", sta2_gold);  
			if(sta2_gold >= 100 && sta2_gold < 1000)
				sprintf( string_value, "²  %iG", sta2_gold);
			if(sta2_gold >= 1000)
				sprintf( string_value, "² %iG", sta2_gold);  
			strcat(new_counter[2].word, string_value);

			sprintf( new_counter[15].word, ""); 

			if(sta2_food < 10)   
				sprintf( string_value, "³    %iF", sta2_food);   
			if(sta2_food >= 10 && sta2_food < 100)
				sprintf( string_value, "³   %iF", sta2_food);  
			if(sta2_food >= 100 && sta2_food < 1000)
				sprintf( string_value, "³  %iF", sta2_food);
			if(sta2_food >= 1000)
				sprintf( string_value, "³ %iF", sta2_food);
			strcat(new_counter[15].word, string_value);

			if(sta2_scroll_route_map == false)  
				new_counter[15].alpha = 1.0f;                       
			else
				new_counter[15].alpha = 0.0f;  
 		    
			if(sta2_scroll_route_map == false) 
				new_counter[3].alpha = 1.0f;                   
			else 
				new_counter[3].alpha = 0.0f; 

		   new_counter[3].id = 0; 
		             
		   new_counter[3].x = -0.65f;      
		   new_counter[3].y = 0.36f; 	             

		   new_counter[3].alpha = 0.0f; // Hack  

		   sta2_squad_total_health = 0; 
	
		   sprintf( new_counter[4].word, "1. Squad");  

			if(sta2_scroll_route_map == false)
				new_counter[4].alpha = 1.0f;                 
			else
				new_counter[4].alpha = 0.0f; 

		   new_counter[4].id = 0; 
		      
		   new_counter[4].x = -0.60f;      
		   new_counter[4].y = -0.34f;  	      

			new_counter[4].w = new_counter[4].x - 0.026f;   
			new_counter[4].z = new_counter[4].y - 0.015f;

			new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
			new_counter[4].box_height = new_counter[4].height - 0.015f;	
	
		    sprintf( new_counter[5].word, "2. Investigate");   

			new_counter[5].alpha = 0.0f;  

		    new_counter[5].id = 0; 
		     
		    new_counter[5].x = -0.155f;      
		    new_counter[5].y = -0.34f;  	      

			new_counter[5].w = new_counter[5].x - 0.026f;   
			new_counter[5].z = new_counter[5].y - 0.015f;

			new_counter[5].box_width = strlen(new_counter[5].word)   *  0.026f;
			new_counter[5].box_height = new_counter[5].height - 0.015f;	

			
			sprintf( new_counter[6].word, "3. Quit");  

			if(sta2_scroll_route_map == false)
				new_counter[6].alpha = 1.0f;                 
			else
				new_counter[6].alpha = 0.0f;                 

			new_counter[6].id = 0;   
       
			if(screen_mode == SCREEN_1610_WIDESCREEN) 
				new_counter[6].x = +0.46f;         
			else
				new_counter[6].x = +0.50f;    

			new_counter[6].y = -0.34f;  	      

			new_counter[6].w = new_counter[6].x - 0.026f;   
			new_counter[6].z = new_counter[6].y - 0.015f;

			new_counter[6].box_width = strlen(new_counter[6].word)   *  0.026f;
			new_counter[6].box_height = new_counter[6].height - 0.015f;	

			if(sta2_yes_no_active == true)
			{
				new_counter[4].id = 4;
				new_counter[5].id = 4;
				new_counter[6].id = 4;
			}

		   sta2_squad_total_health = 0;
		    
		   for(int i = 0;i < sta2_squad_count; i++)
		   {
			   sta2_squad_total_health += TotalSquadScore(i);
		   }

		   sta2_squad_current_health = 0;     
		   sta2_squad_alive_count = 0; 

		   for(int i = 0;i < sta2_squad_count; i++)   
		   {
			   sta2_squad_current_health += sta2_squad[i].health;  
			   if(sta2_squad[i].health > 0)
				   sta2_squad_alive_count++; 
		   }  

		   sta2_squad_bar_width = hud[63].box_width * (float)( (float)sta2_squad_current_health / (float)sta2_squad_total_health);
			
		   if(sta2_scroll_route_map == false) 
		   if((int)TimerGetTime() > sta_hud63_timer) 
		   { 
			   if(hud[63].width > sta2_squad_bar_width)
			   {
				   hud[63].width -= 0.0001f*(float)f_rate;    // f_rate   
				   sta2_rising = false;
			   }
			   if(hud[63].width < sta2_squad_bar_width)  
			   {
				   hud[63].width += 0.0001f*(float)f_rate;    // f_rate
				   sta2_rising = true;
			   }
			   if(hud[63].width < sta2_squad_bar_width && sta2_rising == false)
			   {
				   hud[63].width = sta2_squad_bar_width; 
				   hud_63_old_width = sta2_squad_bar_width;
			   } 
			   if(hud[63].width > sta2_squad_bar_width && sta2_rising == true)
			   {
				   hud[63].width = sta2_squad_bar_width;
				   hud_63_old_width = sta2_squad_bar_width;
			   } 

			   if(hud_63_old_width == 0.0f)  
			       sta_hud63_timer = (int)TimerGetTime() + 2;
			   else
			       sta_hud63_timer = (int)TimerGetTime() + 10;

			   if(hud[63].width > hud[63].box_width) 
				   hud[63].width = hud[63].box_width;

			   	if(hud[63].width < 0.0f)  
				   hud[63].width = 0.0f; 
		   } 

           if(title_sequence == 0)                   
           {     

			    sta2_yes_no_page_map=0;
			    sta2_yes_no_page_battle = 0;

			    hud[63].width = hud_63_old_width;

			    sta2_pressed_map = false;  
			    sta2_fade_out_sequence = 0; 
				     
			    new_counter[2].id = 0;       
		         
				if(screen_mode == SCREEN_1610_WIDESCREEN)
					new_counter[2].x = 0.22f;               
				else
					new_counter[2].x = 0.28f;  

				new_counter[2].y = 0.37f; 
			    
			    if(screen_mode == SCREEN_1610_WIDESCREEN)
					new_counter[15].x = 0.46f;          
				else
					new_counter[15].x = 0.52f; 

			    new_counter[15].y = 0.37f;  
		    
			    sprintf( string_value, "²  %i", sta2_gold);   
				strcat(new_counter[2].word, string_value);

				sprintf( string_value, "³  %i", sta2_food); 
				strcat(new_counter[15].word, string_value);

			//    sta2_Scroll(2, true, f_rate, LEFT);

			    new_counter[3].id = 0; 
		              
			    new_counter[3].x = -0.66f;      
			    new_counter[3].y = 0.36f; 	             
				sprintf( new_counter[3].word, "");

		//	    sprintf( new_counter[3].word, "SQUAD : %i/%i^SECTOR : %i", sta2_squad_current_health, sta2_squad_total_health, sta2_sector); 
			//	sta2_Scroll(3, true, f_rate, RIGHT);

			    sta2_is_epic_battle = false;

  			    // XP gain stuff...  
			    for(int j=0;j<10;j++)
				   xp_damage_index[j] = -1; 

			    xp_damage_count = 0;
				sta2_danger_index = -1;

			    sta2_is_a_trader_event = false;
				sta2_trader_sequence = 0;

			    map_name_timer = (int)TimerGetTime() + 2000;

			    sta2_got_speed_bonus = false;
				sta2_got_epic_bonus = false;
				sta2_got_double_bonus = false;
				sta2_got_triple_bonus = false;

			    sta2_no_of_turns = 0;

			    sta2_power_bar = 0.0f;

				sprite[2].w += sprite[2].box_width/4;
				sprite[2].z += sprite[2].box_height/4;

				sprite[2].box_width = sprite[2].box_width/2;
				sprite[2].box_height = sprite[2].box_height/2;

				// Setup pins...  
				for(int i = 0;i < no_sprites;i++)       
				if(sprite[i].type >= FE_TYPE1 && sprite[i].type <= FE_TYPE8)
				{
					sprite[i].w += sprite[i].box_width/4;
					sprite[i].z += sprite[i].box_height/4;

					sprite[i].box_width = sprite[i].box_width/2;
					sprite[i].box_height = sprite[i].box_height/2;
				}

			    if(sta2_food_rations == RATIONS_LOW) // 2%
					rations_gain = 50;
			    if(sta2_food_rations == RATIONS_MID) // 5%
					rations_gain = 20;
			    if(sta2_food_rations == RATIONS_HIGH) // 6%
					rations_gain = 16;
			    if(sta2_food_rations == RATIONS_MEGA) // 10%
					rations_gain = 10;

			    script_damage = 0; 

			    // Health regain...
				if(sta2_has_moved == true)
				{

	   				for(int i = 0;i < sta2_squad_count; i++)       
					{
						if(sta2_squad[i].health > 1)      
						{
							if(sta2_food <= 0)     
							{ 

							}   
							else     
							{
								if(sta2_has_moved == true)
								{
									sta2_squad[i].health += (TotalSquadScore(i))/rations_gain;

									script_damage += (TotalSquadScore(i))/rations_gain;

									if(sta2_squad[i].health > (TotalSquadScore(i)) )
									{
										sta2_squad[i].health = (TotalSquadScore(i));
									}
								}
							}   
						} 
					} // End of for loop   
					 
					sta2_has_moved = false;

					sta2_squad_current_health = 0; 

					// Check to see if all of team starved..
				    for(int i = 0;i < sta2_squad_count; i++)    
				    {
						if(sta2_squad[i].health > 1) 
					        sta2_squad_current_health += sta2_squad[i].health;  
					    if(sta2_squad[i].health > 0)
						    sta2_squad_alive_count++; 
				    }

				    if(sta2_squad_current_health <= 0)
					{

						episode = 1; 
						scene = 2;

						next_scene = true; 

						title_sequence = 4;

						sta2_next_event = EVENT_STARVE;

					    sta2_team_starved = true;
					}

				}

			    Remove_Temps(TITLE_WIPE);   

				sta2_flash_food = 0;

				sta2_computer_co_down = false;
				sta2_player_co_down = false;

			    sta2_loaded_level = false;
				 
				sta2_shots_rifle = 0;  
				sta2_shots_pistol = 0; 
				sta2_shots_shotgun = 0;    
				sta2_shots_machine = 0;
				sta2_shots_sniper = 0;   
				sta2_shots_mortar = 0; 

				sta2_player_moves = STA2_MOVES_IN_QUICK_PLY;   // Was 3
				sta2_enemy_moves  = STA2_MOVES_IN_QUICK_EMY;   // Was 3

				sta2_enemy_mode = MOVE_WAIT; 

				STA2_MODE = MODE_MOVING;

				sta2_change_turn = true;

				sta2_turn = TURN_NONE;

				sta2_steps_taken = 0;

				emy_id = -1;

				ply_id = -1;

			   if(sta2_route_create_pins == true)  
			   {
				   sta2_current_pin = 3;
				   sta2_route_create_pins = false;   
				    
				   no_of_route_pins = 0;       
				    
				   // Setup pins... 
				   for(int i = 0;i < no_sprites;i++)       
				   {  

					   if(sprite[i].type >= FE_TYPE1 && sprite[i].type <= FE_TYPE8)
					   {    
   
						   rnd = rand()%100;                   

						   if(rnd >= 0 && rnd < 6)        
							   map_pins[3+no_of_route_pins] = EVENT_BRIBE;  
						   if(rnd >= 6 && rnd < 36)     
							   map_pins[3+no_of_route_pins] = EVENT_BATTLE; 
						   if(rnd >= 36 && rnd < 48)  
							   map_pins[3+no_of_route_pins] = EVENT_STORE;   
						   if(rnd >= 48 && rnd < 50)
							   map_pins[3+no_of_route_pins] = EVENT_CHANCE;
						   if(rnd >= 50 && rnd < 55) 
							   map_pins[3+no_of_route_pins] = EVENT_HUNT; 		 				    
						   if(rnd >= 55 && rnd < 60)   
							   map_pins[3+no_of_route_pins] = EVENT_GAMBLE;
						   if(rnd >= 60 && rnd < 65)  
							   map_pins[3+no_of_route_pins] = EVENT_EMPTY;
						   if(rnd >= 65 && rnd < 75)     
							   map_pins[3+no_of_route_pins] = EVENT_TRADE; 
						   if(rnd >= 75 && rnd < 78) 
							   map_pins[3+no_of_route_pins] = EVENT_OBSTACLE;
						   if(rnd >= 78 && rnd < 81)
							   map_pins[3+no_of_route_pins] = EVENT_WIZARD;
						   if(rnd >= 81 && rnd < 100)
							   map_pins[3+no_of_route_pins] = EVENT_CHANCE; 

						   if(sprite[i].type == FE_TYPE2)  
						   {
							   if(sta2_playing_tutorial == true)
								   map_pins[3+no_of_route_pins] = EVENT_SECTOR_GO;
							   else
								   map_pins[3+no_of_route_pins] = EVENT_BOSS;
						   }
						   if(sprite[i].type == FE_TYPE3)
							   map_pins[3+no_of_route_pins] = EVENT_EMPTY; 
						   if(sprite[i].type == FE_TYPE4)
							   map_pins[3+no_of_route_pins] = EVENT_CHANCE;
						   if(sprite[i].type == FE_TYPE5)
							   map_pins[3+no_of_route_pins] = EVENT_STORE;
						   if(sprite[i].type == FE_TYPE6) 
							   map_pins[3+no_of_route_pins] = EVENT_BATTLE; 
						   if(sprite[i].type == FE_TYPE7) 
							   map_pins[3+no_of_route_pins] = EVENT_BATTLE_TUTORIAL;
						   if(sprite[i].type == FE_TYPE8)
							   map_pins[3+no_of_route_pins] = EVENT_HUNT; 
							 
						   if(i == 3)   
							   map_pins[i] = EVENT_DONE;  

						   if(sta2_environment_type == AREA_CITY || sta2_environment_type == AREA_TRENCH)
						   if(map_pins[3+no_of_route_pins] == EVENT_HUNT)
							   map_pins[3+no_of_route_pins] = EVENT_GAMBLE;

						   sprite[i].value2 = map_pins[3+no_of_route_pins];

							no_of_route_pins++;
					   }

				   }          
				        
			   }          
			      
				// Setup pin anims...   
				for(int i = 0;i < no_of_route_pins;i++)      
				{ 
					sprite[3+i].base_anim = 5;  // grey  
					 
					if(map_pins[3+i] == EVENT_DONE)
						sprite[3+i].base_anim = 10; // black
					if(map_pins[3+i] == EVENT_BOSS || map_pins[3+i] == EVENT_SECTOR_GO)
						sprite[3+i].base_anim = 16;  // purple 
					if(map_pins[3+i] == EVENT_STORE)
						sprite[3+i].base_anim = 17;  // purple
				//	if(map_pins[3+i] == EVENT_HUNT)
				//		sprite[3+i].base_anim = 18;  // game
				//	if(map_pins[3+i] == EVENT_GAMBLE)
				//		sprite[3+i].base_anim = 18;  // game
					  
					sprite[3+i].value2 = map_pins[3+i];

					sprite[3+i].anim = sprite[3+i].base_anim;

					Set_Sprite(3+i, sprite[3+i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}

			   // Get the current position, create an icon make 
			   sprite[2].x = sprite[sta2_current_pin].x; // Icon sprite  
			   sprite[2].y = sprite[sta2_current_pin].y; // Icon sprite  

			   sprite[2].w = sprite[sta2_current_pin].w;    
			   sprite[2].z = sprite[sta2_current_pin].z;     
			    
			//   if(sta2_squad_current_health < sta2_squad_total_health)
			//   if(script_damage != 0)
			//       DamageNumber( 2, script_damage, STA2_DAMAGE_NORM );

               title_sequence++;   

			   if(sta2_scroll_route_map == true)
			   {
				   new_counter[2].alpha = 0.0f;
				   new_counter[3].alpha = 0.0f;
				   new_counter[4].alpha = 0.0f;
				   new_counter[5].alpha = 0.0f;
				   new_counter[6].alpha = 0.0f;

				   camX = -((sprite[0].x + sprite[0].width) - 0.785f);
				   title_sequence = 5;
				   title_timer = (int)TimerGetTime()+500;
			   } 
				// Create Lines data...  
				sta2_lines_count = 0;   

				for(int i  = 0;i< no_sprites;i++) 
				if(sprite[i].type >= FE_TYPE1 && sprite[i].type <= FE_TYPE8)
				{
					mid_x = sprite[i].x+sprite[i].width/2;    
					mid_y = sprite[i].y+sprite[i].height/2; 
		
					has_no_connections=true;

					for(int j  = 0;j< no_sprites;j++)  
					if(sprite[j].type >= FE_TYPE1 && sprite[j].type <= FE_TYPE8)
					if(i != j)
					{
						tar_x = sprite[j].x+sprite[j].width/2;  
						tar_y = sprite[j].y+sprite[j].height/2;  

						distance = Node_Distance1(mid_x, mid_y, tar_x, tar_y);
		 
						if(distance <= prox_distance)      
						{
					 
							has_no_connections=false;

							blocked = false; 

							for(int k=0;k<sta2_lines_count;k++)
							{
								if((Lines_MID[k] == i && Lines_TAR[k] == j) || (Lines_MID[k] == j && Lines_TAR[k] == i) )
								{
									blocked = true;
									break;
								}
							}
							if(blocked == false)
							{
								Lines_MID[sta2_lines_count] = i;
								Lines_TAR[sta2_lines_count] = j;
								sta2_lines_count++;
							}

						}
			 
					} // End j loop...

					if(has_no_connections == true)
					{
						 sprite[i].type = NON;
						 sprite[i].alpha = 0.0f;
					}

				}// End i loop...
          
           }       

		   if(sta2_food <= 30)
		   {
			   if((int)TimerGetTime() > sta2_flash_food)
			   {
				   if(new_counter[15].id == 0)
					   new_counter[15].id = 4;
				   else
					   new_counter[15].id = 0;

				   sta2_flash_food = (int)TimerGetTime()+250;
			   }
		   }
		   else
			   new_counter[15].id = 0;

		   if(sta2_scroll_route_map == false)
			   camX = -(sprite[2].x + sprite[2].width/2);
		    
		   if(-camX < sprite[0].x + 0.785f )
			   camX = -(sprite[0].x + 0.785f );  

		   if(-camX > (sprite[0].x + sprite[0].width) - 0.785f ) 
			   camX = -((sprite[0].x + sprite[0].width) - 0.785f);

		   if(sta2_current_pin > 0) 
		   { 
		      targetA = sprite[sta2_current_pin].sector; 
			  targetB = sprite[sta2_current_pin].sector_action;
		      targetC = sprite[sta2_current_pin].rank; 
			  targetD = sprite[sta2_current_pin].onCreate;
		   } 

		   new_counter[10].alpha = 0.0f; 

		   // Selecting a target pin...
           if(title_sequence == 1)         
           {  
			    
				testX = hud_mouseX - (-camX);                                                
				testY = hud_mouseY - (-camY);   

				// YES...
				if(sta2_yes_no_active == true)
				if(new_counter[7].alpha == 1.0f)
				if(( testX < (new_counter[7].w + new_counter[7].box_width) )
				&&( testX > new_counter[7].w)                            
				&&( testY < (new_counter[7].z + new_counter[7].box_height) )
				&&( testY > new_counter[7].z) || sta2_1_pressed == true)   
				{ 
					new_counter[7].id = 5;   

					if(mouseleft == true || DX_SHOOT == true || sta2_1_pressed == true) 
					{  
						sta2_1_pressed = false;
						sta2_2_pressed = false;
						sta2_3_pressed = false;
						sta2_4_pressed = false;
						sta2_esc_pressed = false; 

						mouseleft = false;       
						DX_SHOOT = false;     

						if(sta2_quit_active==true)
						{

							if(sta2_playing_tutorial == false)
							{
								sprintf( temp_string.string, "data/save/sta2");
								STA2_SaveLevel(temp_string);
							}

							episode = 0;  
							scene = 1; 
							 
							next_scene = true;
						}
						 
						if(sta2_yes_no_page==2)  
						{
							sta2_yes_no_active = false;
						}

						if(sta2_yes_no_page==3)
						{
							sta2_yes_no_active = false;
						}

						if(sta2_yes_no_page==5)
						{
							sta2_yes_no_active = false;
						}

						if(sta2_yes_no_page==4)
						{
							sta2_yes_no_page = 5;
						}

						if(sta2_yes_no_page==1)
						{
							sta2_yes_no_page = 2;
						}
						 
					} 
				}  

				// NO... 
				if(new_counter[8].id != 4)
				if(sta2_yes_no_active == true)
				if(new_counter[8].alpha == 1.0f)
				if(( testX < (new_counter[8].w + new_counter[8].box_width) )
				&&( testX > new_counter[8].w)                            
				&&( testY < (new_counter[8].z + new_counter[8].box_height) )
				&&( testY > new_counter[8].z) || sta2_2_pressed == true)   
				{ 
					new_counter[8].id = 5;    

					if(mouseleft == true || DX_SHOOT == true || sta2_2_pressed == true) 
					{  
						sta2_1_pressed = false;
						sta2_2_pressed = false;
						sta2_3_pressed = false;
						sta2_4_pressed = false;
						sta2_esc_pressed = false; 

						mouseleft = false;       
						DX_SHOOT = false;    

						if(sta2_quit_active==true)
							sta2_yes_no_active = false;

						sta2_quit_active = false;

						hud[3].alpha = 0.0f;
						 
					}
				}    
				 
				// Back... 
				if(new_counter[6].id != 4)
				if(sta2_yes_no_active == false) 
				if(new_counter[6].alpha == 1.0f)
				if(( testX < (new_counter[6].w + new_counter[6].box_width) )
				&&( testX > new_counter[6].w)                            
				&&( testY < (new_counter[6].z + new_counter[6].box_height) )
				&&( testY > new_counter[6].z) || sta2_3_pressed == true || sta2_esc_pressed == true)   
				{ 
					new_counter[6].id = 5;    

					if(mouseleft == true || DX_SHOOT == true || sta2_3_pressed == true || sta2_esc_pressed == true) 
					{  
						sta2_1_pressed = false;
						sta2_2_pressed = false;
						sta2_3_pressed = false;
						sta2_4_pressed = false;
						sta2_esc_pressed = false; 

						mouseleft = false;        
						DX_SHOOT = false;    

						sta2_quit_active = true;
						sta2_yes_no_active = true;
						 
					}
				}  
				  
				// Squad...
				if(new_counter[4].id != 4)
				if(sta2_yes_no_active == false)
				if(new_counter[4].alpha == 1.0f)
				if(( testX < (new_counter[4].w + new_counter[4].box_width) )
				&&( testX > new_counter[4].w)                            
				&&( testY < (new_counter[4].z + new_counter[4].box_height) )
				&&( testY > new_counter[4].z) || sta2_1_pressed == true)   
				{  
					new_counter[4].id = 5;   

					if(mouseleft == true || DX_SHOOT == true || sta2_1_pressed == true) 
					{  
						
						mouseleft = false;       
						DX_SHOOT = false;  

						sta2_1_pressed = false;
						sta2_2_pressed = false;
						sta2_3_pressed = false;
						sta2_4_pressed = false;
						sta2_esc_pressed = false; 

					//	sta2_investigate=false;
						 
						episode = 1; 
						scene = 5;
						 
						next_scene = true; 

					//    title_sequence = 3;
					//    title_timer = 0;
						 
					}
				}  
				 
			   if(sta2_investigate == true)        
			   {   

				    if(sta2_playing_tutorial == true)
				    if(sta2_yes_no_page == 2)
					{
						sta2_yes_no_active = true;
						sta2_yes_no_page = 3;
					}

                    new_counter[5].alpha = 1.0f;    
	 
					testX = hud_mouseX - (-camX);                                               
					testY = hud_mouseY - (-camY); 
				     
					// Investigate...
					if(sta2_yes_no_active == false)
					if(new_counter[5].alpha == 1.0f)
					if(( testX < (new_counter[5].w + new_counter[5].box_width) )
					&&( testX > new_counter[5].w)                            
					&&( testY < (new_counter[5].z + new_counter[5].box_height) )
					&&( testY > new_counter[5].z) || sta2_2_pressed == true)   
					{ 
						new_counter[5].id = 5;   

						if(mouseleft == true || DX_SHOOT == true || sta2_2_pressed == true) 
						{  
						
							mouseleft = false; 
							DX_SHOOT = false; 
							sta2_2_pressed = false;
							sta2_investigate=false;
							title_sequence = 3;
							title_timer = 0;
						 
						}
					}  

			    }

			   new_counter[9].alpha  = 0.0f;  
			   new_counter[10].alpha = 0.0f;  
			   sprintf( new_counter[9].word, "");
			   sprintf( new_counter[10].word, "");

			   for(int i = 0;i < no_sprites;i++)        
			   { 

				   if(sprite[i].type >= FE_TYPE1 && sprite[i].type <= FE_TYPE8)
				       Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				   if(sta2_yes_no_active == false)
				   if(sprite[i].type >= FE_TYPE1 && sprite[i].type <= FE_TYPE8)
				   if(sprite[i].alpha == 1.0f)                   
				   if(( mouseX < (sprite[i].w + sprite[i].box_width) )
				   &&( mouseX > sprite[i].w)                            
				   &&( mouseY < (sprite[i].z + sprite[i].box_height) )
				   &&( mouseY > sprite[i].z))   
				   {      
					    
						Set_Sprite(i, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);  				

						if(i != sta2_current_pin) 
							new_counter[10].alpha = 1.0f;    

					    testX = hud_mouseX - (-camX);                                                
					    testY = hud_mouseY - (-camY); 
						 
						new_counter[9].alpha = 1.0f;               
					   
						new_counter[9].x = testX + 0.13f;                  
						new_counter[9].y = testY;     
					  
						new_counter[10].alpha = 1.0f;                
					    
						new_counter[10].x = testX + 0.1f;                      
						new_counter[10].y = testY;      
						   
						if(i != sta2_current_pin)      
						{
							sprintf( new_counter[10].word, "@");

							mid_x = sprite[sta2_current_pin].x+sprite[sta2_current_pin].width/2; 
							mid_y = sprite[sta2_current_pin].y+sprite[sta2_current_pin].height/2; 
        
							tar_x = sprite[i].x+sprite[i].width/2;  
							tar_y = sprite[i].y+sprite[i].height/2;  

							distance = Node_Distance1(mid_x, mid_y, tar_x, tar_y);

							if(distance > prox_distance) 
								sprintf( new_counter[9].word, "OUT OF^RANGE^");
							else
								sprintf( new_counter[9].word, "CLICK TO^MOVE^"); 
						}
						  
						// For left-sided messages, get longest line...
						if( new_counter[9].x >= sta2_left_of_screen)    
						{ 
							slongest_line = GetLongestLine(new_counter[9].word); 
							   
							new_counter[10].x = testX - 0.03f;   
							new_counter[9].x = new_counter[10].x - (slongest_line*0.0245f);  

						} 

						if(i != sta2_current_pin) 
						if(mouseleft == true || DX_SHOOT == true)  
						{  
							if(distance <= prox_distance) 
							{
								if(target_pin != -1)
								if(map_pins[target_pin] != EVENT_BOSS && map_pins[target_pin] != EVENT_SECTOR_GO)
								{
									map_pins[target_pin] = EVENT_DONE; 
									sprite[target_pin].base_anim = 10;
									Set_Sprite(target_pin, sprite[target_pin].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
								} 

								title_timer = (int)TimerGetTime() + 250;
								title_sequence++;  

								target_pin = i;   

								sta2_squad_alive_count = 0;

								for(int i = 0;i < sta2_squad_count; i++)   
									if(sta2_squad[i].health >= 1)
										sta2_squad_alive_count++;

								if(sta2_food_rations == RATIONS_LOW) // 2%
									rations_gain = RATIONS_LOW_COST;
								if(sta2_food_rations == RATIONS_MID) // 5%
									rations_gain = RATIONS_MID_COST; 
								if(sta2_food_rations == RATIONS_HIGH) // 6%
									rations_gain = RATIONS_HIGH_COST;
								if(sta2_food_rations == RATIONS_MEGA) // 10% 
									rations_gain = RATIONS_MEGA_COST;
								 
								sta2_food -= sta2_squad_alive_count*rations_gain;

								if(sta2_food < 0) 
									sta2_food = 0;
							}
							else
								stolen_sfx=true;

							DX_SHOOT=false;
							mouseleft = false;
							 
						}

				   }
				   else
				   {
			//			Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);	
				   }

			   }

		   } 
		    
		   // Moving towards the target pin...
           if(title_sequence == 2)     
		   if(target_pin != -1)
           {  
			    sta2_investigate = false;

			    if((int)TimerGetTime() > title_timer)
				{
					grassstep_sfx = true; 
					title_timer = (int)TimerGetTime() + 250;
				}

			    temp_speed = 0.00015f; 
			    
				mid_x = sprite[2].w+sprite[2].box_width/2; 
				mid_y = sprite[2].z+sprite[2].box_height/2; 
        
				tar_x = sprite[target_pin].w+sprite[target_pin].box_width/2; 
				tar_y = sprite[target_pin].z+sprite[target_pin].box_height/2;   
	
				angle = atan2(tar_y - mid_y, tar_x - mid_x);
     
				deltax = cos(angle); // Was 1.2    
				deltay = sin(angle); // Was 1.2 
        
				deltax *= temp_speed;           
				deltay *= temp_speed; 
     
				deltax *= (float)f_rate;       
				deltay *= (float)f_rate;     
				  
				sprite[2].x += deltax;      
				sprite[2].w += deltax;  
				 
				sprite[2].y += deltay;       
				sprite[2].z += deltay; 

				distance = Node_Distance1(mid_x, mid_y, tar_x, tar_y);

				if(distance <= 0.005f)        
				{
					sprite[2].x = sprite[target_pin].x; 
					sprite[2].y = sprite[target_pin].y;
					sprite[2].w = sprite[target_pin].w; 
					sprite[2].z = sprite[target_pin].z;   
					   
					sta2_current_pin = target_pin;     

					sta2_next_event = map_pins[target_pin];   

				    if(sta2_playing_tutorial == true)
					if(sta2_next_event == EVENT_STORE)
				    if(sta2_yes_no_page == 3)
					{
						sta2_yes_no_active = true;
						sta2_yes_no_page = 4;
					}

					if(map_pins[target_pin] != EVENT_BOSS && map_pins[target_pin] != EVENT_SECTOR_GO)  
						map_pins[target_pin] = EVENT_DONE;

					// Check for starved...
					if(map_pins[target_pin] == EVENT_DONE)  
					{ 
						for(int i = 0;i < sta2_squad_count; i++)
						if(sta2_squad[i].health > 1)      
						{
							if(sta2_food <= 0)    
							{ 
								sta2_squad[i].health -= (TotalSquadScore(i)/5); 

								script_damage -= (TotalSquadScore(i)/5);

								if(sta2_squad[i].health < 1 ) 
								{
									sta2_squad[i].health = 1; 
								} 
							}   

						} 	

						sta2_squad_current_health = 0; 

						// Check to see if all of team starved..
						for(int i = 0;i < sta2_squad_count; i++)    
						{
							if(sta2_squad[i].health > 1) 
								sta2_squad_current_health += sta2_squad[i].health;  
							if(sta2_squad[i].health > 0)
								sta2_squad_alive_count++; 
						}

						if(sta2_squad_current_health <= 0)
						{

							episode = 1; 
							scene = 2;

							next_scene = true; 

							title_sequence = 4;

							sta2_next_event = EVENT_STARVE;

							sta2_team_starved = true;
						}
					}
					 
					if(sta2_next_event != EVENT_DONE)
					{
						if(map_pins[target_pin] != EVENT_BOSS && map_pins[target_pin] != EVENT_SECTOR_GO)
							sta2_has_moved = true;

						if(sta2_next_event == EVENT_BATTLE
						|| sta2_next_event == EVENT_BATTLE_TUTORIAL
						|| sta2_next_event == EVENT_BOSS 
						|| sta2_next_event == EVENT_SECTOR_GO
						|| sta2_next_event == EVENT_OBSTACLE
						|| sta2_next_event == EVENT_WIZARD
						|| sta2_next_event == EVENT_BRIBE
						)
						{
							title_sequence = 3; 
							title_timer = (int)TimerGetTime() + 1500; 
						}
						else 
						{
							sta2_investigate = true;
							title_sequence = 1;
						} 
					}
					else
					{
						title_sequence = 1; 
					//	title_timer = (int)TimerGetTime() + 1500; 
					}
					 
					if(sta2_next_event != EVENT_DONE)
					if(sta2_next_event == EVENT_BATTLE || sta2_next_event == EVENT_BATTLE_TUTORIAL || sta2_next_event == EVENT_BOSS || sta2_next_event == EVENT_SECTOR_GO || sta2_next_event == EVENT_OBSTACLE || sta2_next_event == EVENT_WIZARD || sta2_next_event == EVENT_BRIBE) 
					{
						New_FX(sprite[2].x, sprite[2].z+0.05f,  sprite[2].x, sprite[2].y-0.0001f, 24, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
						stolen_sfx = true;
					}
					else
					{ 
						cow_sfx = true;
						New_FX(sprite[2].x, sprite[2].z+0.05f,  sprite[2].x, sprite[2].y-0.0001f, 25, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
					}

				}     

		   } 

		    // Go to investigate mode...
            if(title_sequence == 3)  
			if((int)TimerGetTime() > title_timer) 
            { 
				
				episode = 1;  
				scene = 2;

				next_scene = true;	 			

		    }
			 
		    // Go to investigate mode... 
            if(title_sequence == 5)   
			if((int)TimerGetTime() > title_timer)    
            {  
				
				camX +=  0.00025f*(float)f_rate;  
				sprite[index].x -= 0.00025f*(float)f_rate;

				if((int)TimerGetTime() > map_name_timer)
					sprite[index].alpha = 0.0f;
				 
			    if(-camX < sprite[0].x + 0.785f || -camX < sprite[2].x+sprite[2].width/2 )
				{
					sprite[index].alpha = 0.0f;

					if(-camX < sprite[0].x + 0.785)
						camX = -(sprite[0].x + 0.785f );  
					 
					if(-camX < sprite[2].x+sprite[2].width/2)
						camX = -(sprite[2].x+sprite[2].width/2 );  


				    new_counter[2].alpha = 1.0f;
				    new_counter[3].alpha = 1.0f;
				    new_counter[4].alpha = 1.0f;
				 //   new_counter[5].alpha = 1.0f;
				    new_counter[6].alpha = 1.0f;

					sta2_scroll_route_map = false;

					sta2_esc_pressed = false;
					sta2_1_pressed = false;
					sta2_2_pressed = false;
					sta2_3_pressed = false;
					sta2_4_pressed = false;
					sta2_5_pressed = false;
					sta2_6_pressed = false;

					title_sequence = 1;
				}

		    }

		   pin_camX = -(sprite[2].x + sprite[2].width/2);
  
		   if(next_scene == true)
		       hud_63_old_width = hud[63].width;                         
       }           
 	
    // ******************************************************************************//
    //                            1-2  (INVESTIGATE SCREEN)                          //
    // ******************************************************************************//	      
	      
	   // Investigate Mode...   
       if(!mode)    
       if(next_scene == false)      
       if(episode == 1 && scene == 2)                          
       {                        

		/*    if(sta2_fade_out_sequence == 1)
			{
				Set_Sprite(3, 1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Messagebox

				new_counter[2].alpha = 0.0f; // Text
				new_counter[3].alpha = 0.0f; // Text
				new_counter[4].alpha = 0.0f; // Text
				new_counter[5].alpha = 0.0f; // Text
				new_counter[6].alpha = 0.0f; // Text

				sta2_fade_out_sequence = 2; 

				if(sta2_is_a_trader_event == false)
				{
					title_sequence = 2; 
					title_timer = (int)TimerGetTime() + 1000;
				}

			}

			if(title_sequence == 2)
			if((int)TimerGetTime() > title_timer)
			{
				episode = 1;
				scene = 0;

				next_scene = true;

				title_sequence++;

			}*/ 

		    // Scroll in trader sprite from left...
            if(sta2_trader_sequence == 1)   
            {            
				 
                 temp_speed = 0.0005f*(float)f_rate; 
				  
			     if(sprite[1].y < script_start_x1)
			     {
					 sprite[1].y += temp_speed; 
				 } 
				 else
					 sprite[1].y = script_start_x1; 
    
            } 
            if(sta2_trader_sequence == 2)        
            {
				Set_Sprite(1, 1, LOOP, ANIM_SPRITE, ANIM_WALKING); // Pistol

				script_start_x1 = sprite[1].y - sprite[1].height;

				sprite[3].alpha = 0.0f; // Msg box 

				new_counter[2].alpha = 0.0f; // Text
				new_counter[3].alpha = 0.0f; // Text
				new_counter[4].alpha = 0.0f; // Text
				new_counter[5].alpha = 0.0f; // Text
				new_counter[6].alpha = 0.0f; // Text

				sta2_trader_sequence++;
				 
				title_sequence = 101;
			}
            if(sta2_trader_sequence == 3)    
            {            
				 
                 temp_speed = 0.0005f*(float)f_rate;  
				  
			     if(sprite[1].y >= script_start_x1)
			     {
					 sprite[1].y -= temp_speed; 
				 }
				 else 
				 {
					 sprite[1].y = script_start_x1; 

					 episode = 1;
					 scene = 0;

					 next_scene = true;

					 sta2_trader_sequence++;

				 }  
     
            }   
            if(title_sequence == 0)                                              
            {      

				if(sta2_environment_type == AREA_CITY)
				{
					sprite[0].type = NON;
					sprite[4].type = NON;
				}
				if(sta2_environment_type == AREA_TRENCH)
				{
					sprite[0].type = NON;
					sprite[4].type = NON; 
				}
				if(sta2_environment_type == AREA_FARM)
				{
					sprite[4].priority = 4; // Stops road going over trader...
				}

				button_snd = false;
				button1_snd = false;
				button2_snd = false;

			//	Set_Sprite(3, 0, PLAY, ANIM_SPRITE, ANIM_WALKING); // Messagebox

				sprite[3].alpha = 0.0f; // Msg box

				if(sta2_next_event != EVENT_GENERAL) 
					sta2_move_general = true;

				sta2_is_a_trader_event = false;       
				  
				if(sta2_trader_sequence == 0)     
				{
					script_start_x1 = sprite[1].y; // x 
					sprite[1].y -= sprite[1].height/2;	// sprite[1].width/2		          
					sta2_trader_sequence = 1; 
				}      
				                            
				// Trader sprite...                                                    
				sprite[1].alpha = 0.0f;                                                                                             
				                 
			/*	if(DEBUG_MODE == 0)      
		   	    if(sta2_next_event != EVENT_INTRO && sta2_next_event != EVENT_STARVE 
				&& sta2_next_event != EVENT_BOSS && sta2_next_event != EVENT_NEW_SECTOR
				&& sta2_next_event != EVENT_VICTORY && sta2_next_event != EVENT_DEFEAT
				&& sta2_next_event != EVENT_HUNT_RESULT && sta2_next_event != EVENT_GAMBLE_RESULT && sta2_next_event != EVENT_BATTLE_TUTORIAL
				&& sta2_next_event != EVENT_SECTOR_GO && sta2_next_event != EVENT_STORE && sta2_next_event != EVENT_GENERAL)
					sta2_next_event = EVENT_BATTLE;      // For testing purposes.. 
		*/
				if(sta2_next_event == EVENT_TRADE)         
				{ 
					sta2_is_a_trader_event = true;  
				    sprite[1].alpha = 1.0f; 
					sprite[1].id = 8;    
				}       
		      
				if(sta2_next_event == EVENT_GAMBLE) 
				{
					sta2_is_a_trader_event = true; 
				    sprite[1].alpha = 1.0f;
					sprite[1].id = 9; 
				}
		      
				if(sta2_next_event == EVENT_WIZARD)  
				{
					sta2_is_a_trader_event = true; 
				    sprite[1].alpha = 1.0f;
					sprite[1].id = 10;
				}

				sta2_is_bandit_level = false;        
				sta2_is_first_level = false;  
	 	  
				if(sta2_next_event == EVENT_EMPTY)    
					GetPage(PAGE_EMPTY);            
				if(sta2_next_event == EVENT_TRADE)  
					GetPage(PAGE_TRADE);     
				if(sta2_next_event == EVENT_GENERAL)  
					GetPage(PAGE_GENERAL);  
				 
				if(sta2_next_event == EVENT_BRIBE)   
					GetPage(PAGE_BRIBE);       
				if(sta2_next_event == EVENT_BATTLE)  
					GetPage(PAGE_BATTLE); 
				if(sta2_next_event == EVENT_BATTLE_TUTORIAL)  
					GetPage(PAGE_BATTLE); 

				if(sta2_next_event == EVENT_OBSTACLE) 
					GetPage(PAGE_OBSTACLE_RIVER);        
				if(sta2_next_event == EVENT_WIZARD)  
					GetPage(PAGE_WIZARD);  
				if(sta2_next_event == EVENT_CHANCE)
					GetPage(PAGE_CHANCE);        

				if(sta2_next_event == EVENT_QUEST)    
					GetPage(PAGE_QUEST);        
				if(sta2_next_event == EVENT_GAMBLE) 
					GetPage(PAGE_GAMBLE);     
				if(sta2_next_event == EVENT_GAMBLE_RESULT)
					GetPage(PAGE_GAMBLE_RESULT);  

				if(sta2_next_event == EVENT_STORE)
					GetPage(PAGE_STORE);        
				if(sta2_next_event == EVENT_HUNT)
					GetPage(PAGE_HUNT);   
				if(sta2_next_event == EVENT_HUNT_RESULT)
					GetPage(PAGE_HUNT_RESULT);  

				if(sta2_next_event == EVENT_VICTORY)
					GetPage(PAGE_VICTORY);  
				if(sta2_next_event == EVENT_DEFEAT)
					GetPage(PAGE_DEFEAT);  
				 
				if(sta2_next_event == EVENT_BOSS) 
					GetPage(PAGE_BOSS);         
				if(sta2_next_event == EVENT_NEW_SECTOR) 
					GetPage(PAGE_NEW_SECTOR);   
				if(sta2_next_event == EVENT_SECTOR_GO) 
					GetPage(PAGE_SECTOR_GO);    

				if(sta2_next_event == EVENT_INTRO)  
					GetPage(PAGE_INTRO);  

				if(sta2_next_event == EVENT_STARVE)  
					GetPage(PAGE_STARVE);  

				if(sta2_next_event == EVENT_BRIBE)  
					sta2_is_bandit_level = true;
				if(sta2_next_event == EVENT_BATTLE_TUTORIAL) 
					sta2_is_first_level = true;      

				sta2_page = 0;     
				 
				new_counter[2].alpha = 0.0f; // Text 

				new_counter[2].id = 0;  
				  
				new_counter[2].x = -0.5f;    
				new_counter[2].y = 0.0f;	      

				new_counter[3].x = -0.5f; 
				new_counter[3].y = 0.0f - ((new_counter[3].height - 0.005f)*3);	 

				new_counter[3].w = new_counter[3].x - 0.026f;   
				new_counter[3].z = new_counter[3].y - 0.015f;
				       
				new_counter[3].box_width = 11 *  0.026f; 
				new_counter[3].box_height = new_counter[3].height - 0.015f;
				     
				new_counter[4].x = -0.5f;  
				new_counter[4].y = 0.0f - ((new_counter[4].height - 0.005f)*4);	 
				 
				new_counter[4].w = new_counter[4].x - 0.026f;    
				new_counter[4].z = new_counter[4].y - 0.015f; 

				new_counter[4].box_width = 11 *  0.026f;
				new_counter[4].box_height = new_counter[4].height - 0.015f;
				    
				new_counter[5].x = -0.5f; 
				new_counter[5].y = 0.0f - ((new_counter[5].height - 0.005f)*5);	 

				new_counter[5].w = new_counter[5].x - 0.026f;   
				new_counter[5].z = new_counter[5].y - 0.015f;

				new_counter[5].box_width = 11 *  0.026f;
				new_counter[5].box_height = new_counter[5].height - 0.015f;	

				if(sta2_next_event == EVENT_TRADE)
				{
					 
					hud[62].alpha = 0.0f; 
					  
					new_counter[6].alpha = 0.0f;              
					new_counter[6].id = 0;  
		     
					if(screen_mode == SCREEN_1610_WIDESCREEN)
						new_counter[6].x = 0.22f;               
					else 
						new_counter[6].x = 0.28f;  

					new_counter[6].y = 0.37f;   

					new_counter[15].alpha = 0.0f;              
					new_counter[15].id = 0;  

					if(screen_mode == SCREEN_1610_WIDESCREEN)
						new_counter[15].x = 0.46f;          
					else
						new_counter[15].x = 0.52f;   

					new_counter[15].y = 0.37f;

				}    

				title_sequence++;
				title_timer = (int)TimerGetTime() + 250;
				 
			}        
			           
            if(title_sequence >= 1)       
			if((int)TimerGetTime() > title_timer)   
            {     
				if(sta2_next_event == EVENT_TRADE)   
				{
					hud[62].alpha = 1.0f;
					new_counter[6].alpha = 1.0f;
					new_counter[15].alpha = 1.0f;
					 
					sprintf( new_counter[6].word, ""); 

					if(sta2_gold < 10) 
						sprintf( string_value, "²    %iG", sta2_gold);  
					if(sta2_gold >= 10 && sta2_gold < 100)
						sprintf( string_value, "²   %iG", sta2_gold);  
					if(sta2_gold >= 100 && sta2_gold < 1000)
						sprintf( string_value, "²  %iG", sta2_gold);
					if(sta2_gold >= 1000)
						sprintf( string_value, "² %iG", sta2_gold);  
					strcat(new_counter[6].word, string_value);

					sprintf( new_counter[15].word, ""); 

					if(sta2_food < 10)   
						sprintf( string_value, "³    %iF", sta2_food);   
					if(sta2_food >= 10 && sta2_food < 100)
						sprintf( string_value, "³   %iF", sta2_food);  
					if(sta2_food >= 100 && sta2_food < 1000)
						sprintf( string_value, "³  %iF", sta2_food);
					if(sta2_food >= 1000)
						sprintf( string_value, "³ %iF", sta2_food);
					strcat(new_counter[15].word, string_value);

					new_counter[6].id = 7;  // Option1
					new_counter[15].id = 7;  // Option1
				}	

				sprite[3].alpha = 1.0f; // Msg box
				 
				new_counter[3].id = 0;  // Option1 
				new_counter[4].id = 0;  // Option2  
				new_counter[5].id = 0;  // Option3 

				if(new_counter[3].greyed == true)  // Greyed out..
				    new_counter[3].id = 5;  // Option1 
				if(new_counter[4].greyed == true)  // Greyed out..
				    new_counter[4].id = 5;  // Option1 
				if(new_counter[5].greyed == true)  // Greyed out..
				    new_counter[5].id = 5;  // Option1  
				  
				new_counter[2].alpha = 1.0f; // Text 
				 
				if(page[sta2_page].option1 == OPTION_NONE)
					new_counter[3].alpha = 0.0f; // Option1  
				else
					new_counter[3].alpha = 1.0f; // Option1  

				if(page[sta2_page].option2 == OPTION_NONE) 
					new_counter[4].alpha = 0.0f; // Option2  
				else
					new_counter[4].alpha = 1.0f; // Option2  

				if(page[sta2_page].option3 == OPTION_NONE) 
					new_counter[5].alpha = 0.0f; // Option3  
				else
					new_counter[5].alpha = 1.0f; // Option3  

				new_counter[3].box_width = strlen(new_counter[3].word) *  0.026f;  // Option1
				new_counter[4].box_width = strlen(new_counter[4].word) *  0.026f;  // Option2
				new_counter[5].box_width = strlen(new_counter[5].word) *  0.026f;  // Option3

				sprintf( new_counter[2].word, page[sta2_page].word_text);  // Text 
				sprintf( new_counter[3].word, page[sta2_page].word_option1);  // Option1
				sprintf( new_counter[4].word, page[sta2_page].word_option2);  // Option2
				sprintf( new_counter[5].word, page[sta2_page].word_option3);  // Option3  
		  
				 
				if(sta2_trader_sequence >= 2) 
				{
					hud[62].alpha = 0.0f;
					new_counter[6].alpha = 0.0f;
					new_counter[15].alpha = 0.0f;
					sprite[3].alpha = 0.0f; // Msg box
				 
					new_counter[0].alpha = 0.0f;  // Option1
					new_counter[1].alpha = 0.0f;  // Option1
					new_counter[2].alpha = 0.0f;  // Option1
					new_counter[3].alpha = 0.0f;  // Option1 
					new_counter[4].alpha = 0.0f;  // Option2  
					new_counter[5].alpha = 0.0f;  // Option3 
				}


				// Option 1...
				 
				if(new_counter[3].alpha == 1.0f)                      
				if(( mouseX < (new_counter[3].w + new_counter[3].box_width) )
				&&( mouseX > new_counter[3].w)                            
				&&( mouseY < (new_counter[3].z + new_counter[3].box_height) )
				&&( mouseY > new_counter[3].z) || sta2_1_pressed == true)   
				{ 
					if(new_counter[3].greyed == false)
					    new_counter[3].id = 2;           
				    
					if(button_snd == false)
					{
						button_snd = true;
						radio_sfx = true;
					}

					if(mouseleft == true || DX_SHOOT == true || sta2_1_pressed == true) 
					{     
						mouseleft = false; 
						DX_SHOOT = false; 
						sta2_1_pressed = false; 
						sta2_2_pressed = false; 
						sta2_3_pressed = false;  
						sta2_4_pressed = false; 
						sta2_esc_pressed = false; 

						OptionHandler(sta2_page, 1);
					}  
				}  
				else 
					button_snd = false;

				// Option 2...
				
				if(new_counter[4].alpha == 1.0f && new_counter[4].id != 5)                     
				if(( mouseX < (new_counter[4].w + new_counter[4].box_width) )
				&&( mouseX > new_counter[4].w)                            
				&&( mouseY < (new_counter[4].z + new_counter[4].box_height) )
				&&( mouseY > new_counter[4].z) || sta2_2_pressed == true)   
				{ 
					if(new_counter[4].greyed == false) 
					    new_counter[4].id = 2; 
				    
					if(button1_snd == false)
					{
						button1_snd = true;
						radio_sfx = true;
					}

					if(mouseleft == true || DX_SHOOT == true || sta2_2_pressed == true) 
					{  

						mouseleft = false; 
						DX_SHOOT = false; 
						sta2_1_pressed = false; 
						sta2_2_pressed = false; 
						sta2_3_pressed = false; 
						sta2_4_pressed = false; 
						sta2_esc_pressed = false; 

						OptionHandler(sta2_page, 2);
					} 
				}  
				else
					button1_snd = false;

				// Option 3...
				
				if(new_counter[5].alpha == 1.0f && new_counter[5].id != 5)                     
				if(( mouseX < (new_counter[5].w + new_counter[5].box_width) )
				&&( mouseX > new_counter[5].w)                            
				&&( mouseY < (new_counter[5].z + new_counter[5].box_height) )
				&&( mouseY > new_counter[5].z) || sta2_3_pressed == true)   
				{ 
					if(new_counter[5].greyed == false) 
					    new_counter[5].id = 2;     
				    
					if(button2_snd == false)
					{
						button2_snd = true;
						radio_sfx = true;
					}

					if(mouseleft == true || DX_SHOOT == true || sta2_3_pressed == true) 
					{  
						
						mouseleft = false;  
						DX_SHOOT = false; 
						sta2_1_pressed = false; 
						sta2_2_pressed = false; 
						sta2_3_pressed = false; 
						sta2_4_pressed = false; 
						sta2_esc_pressed = false; 

						OptionHandler(sta2_page, 3);

						next_scene = true;
						 
					}  
				}  
				else
					button2_snd = false;

			} // title_sequence == 1



	   } // end of scene
 	
    // ******************************************************************************//
    //                            2-0  (INGAME BATTLE MODE)                          //
    // ******************************************************************************//	

       // Title Screen Stuff...
       if(game_mode == WALK && !mode)  
       if(next_scene == false)                 
       if(episode == 2 || episode == 4)  
       {     

	//	   SwipeCode(f_rate);   

		   if(start_sequence == 0) 
		   {  

			   sta2_entered_action = true;

			   start_sequence++; 

		   }

		   if(title_sequence == 0)                              
		   {          

			    if(sta2_turn != TURN_COMPUTER)    
				if(sta2_playing_tutorial == true)
				{

					if(sta2_yes_no_page_battle == 0) 
					{

						sta2_displaying_help = true;

						Set_Sprite(3, 2, LOOP, ANIM_HUD, ANIM_WALKING); // Pistol

						hud[3].alpha = 1.0f;  
	    
						new_counter[17].alpha = 1.0f;    
						new_counter[17].id = 0; 

						if(sta2_is_first_level == true)
							sprintf(new_counter[17].word, "Use the $WASD$^keys to move^your unit.");
						else
							sprintf(new_counter[17].word, "To use cover.^Stand near it^to take cover.");

						new_counter[17].x = hud[3].x + 0.042f;  
						new_counter[17].y =  hud[3].y + hud[3].height - 0.1f;

						new_counter[15].alpha = 1.0f;  
						new_counter[15].id = 0;
						sprintf(new_counter[15].word, "1 : Next"); 
						new_counter[15].x = hud[3].x + 0.042f;  
						new_counter[15].y =  hud[3].y + hud[3].height - 0.1f - 0.20f;
						new_counter[15].w = new_counter[15].x - 0.026f;   
						new_counter[15].z = new_counter[15].y - 0.015f;
						new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
						new_counter[15].box_height = new_counter[15].height - 0.015f;	
				
						title_sequence=1;
					}
					if(sta2_yes_no_page_battle == 1) 
					{
						sta2_displaying_help = true;

						Set_Sprite(3, 2, LOOP, ANIM_HUD, ANIM_WALKING); // Pistol

						hud[3].alpha = 1.0f;    
	   
						new_counter[17].alpha = 1.0f;   
						new_counter[17].id = 0;  

						if(sta2_is_first_level == true)
							sprintf(new_counter[17].word, "Click the^Right mouse^button for^actions."); 
						else
							sprintf(new_counter[17].word, "Cover reduces^damage taken^by 50&."); 

						new_counter[17].x = hud[3].x + 0.042f;  
						new_counter[17].y =  hud[3].y + hud[3].height - 0.1f;

						new_counter[15].alpha = 1.0f;  
						new_counter[15].id = 0;
						sprintf(new_counter[15].word, "1 : OKAY!"); 
						new_counter[15].x = hud[3].x + 0.042f;  
						new_counter[15].y =  hud[3].y + hud[3].height - 0.1f - 0.20f;
						new_counter[15].w = new_counter[15].x - 0.026f;   
						new_counter[15].z = new_counter[15].y - 0.015f;
						new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
						new_counter[15].box_height = new_counter[15].height - 0.015f;	
				
						title_sequence=1; 
					}
					if(sta2_is_first_level == false)
					if(sta2_yes_no_page_battle == 2) 
					{ 
						sta2_displaying_help = true;

						Set_Sprite(3, 2, LOOP, ANIM_HUD, ANIM_WALKING); // Pistol
						 
						hud[3].alpha = 1.0f;    
	   
						new_counter[17].alpha = 1.0f;    
						new_counter[17].id = 0;  

						sprintf(new_counter[17].word, "Using cover^is vital^for survival!"); 

						new_counter[17].x = hud[3].x + 0.042f;  
						new_counter[17].y =  hud[3].y + hud[3].height - 0.1f;

						new_counter[15].alpha = 1.0f;  
						new_counter[15].id = 0;
						sprintf(new_counter[15].word, "1 : OKAY!"); 
						new_counter[15].x = hud[3].x + 0.042f;  
						new_counter[15].y =  hud[3].y + hud[3].height - 0.1f - 0.20f;
						new_counter[15].w = new_counter[15].x - 0.026f;   
						new_counter[15].z = new_counter[15].y - 0.015f;
						new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
						new_counter[15].box_height = new_counter[15].height - 0.015f;	
				
						title_sequence=1; 
					}    
					 
				}
		   } 

		   if(title_sequence == 1)                        
		   {     
			    new_counter[15].id = 0;  

				testX = hud_mouseX - (-camX);                                                  
				testY = hud_mouseY - (-camY); 

				if(sta2_displaying_help == true)
				if(( testX < (new_counter[15].w + new_counter[15].box_width) )
				&&( testX > new_counter[15].w)                            
				&&( testY < (new_counter[15].z + new_counter[15].box_height) )
				&&( testY > new_counter[15].z) || sta2_1_pressed == true)   
				{   
					new_counter[15].id = 9;       

					if(mouseleft == true || DX_SHOOT == true || sta2_1_pressed == true) 
					{  

						mouseleft = false; 
						 
						new_counter[17].alpha = 0.0f; 
						new_counter[15].alpha = 0.0f; 
						  
						sta2_1_pressed = false;  
						  
						title_sequence = 0; 

						if(sta2_is_first_level == true) 
						if(sta2_yes_no_page_battle == 1)
						{ 
							sta2_displaying_help = false;        
							title_sequence = 0;  
						}
						if(sta2_is_first_level == false)
						if(sta2_yes_no_page_battle == 2)
						{
							sta2_displaying_help = false;  
							title_sequence = 0; 
						} 
			
						sta2_yes_no_page_battle++;
 
					} 
				}  
		   }


	   }
 	
    // ******************************************************************************//
    //                            0-1  (TITLE SCREEN)                                //
    // ******************************************************************************//	

       // Title Screen Stuff...
       if(game_mode == FRONT && !mode) 
       if(next_scene == false)             
       if(episode == 0 && scene == 1)      
       {          
		//    SwipeCode(f_rate); 
    
		    if(sta2_yes_no_page == 0)
				Set_Sprite(3, 1, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Point Arrow 
		    if(sta2_yes_no_page == 1)
				Set_Sprite(3, 0, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Point Arrow 

		/*    new_counter[15].id = 0;    
			 
		    new_counter[15].alpha = 1.0f;       
			  
		    new_counter[15].x = 0.42f;               
		    new_counter[15].y = 0.36f; 	      
		    
		    sprintf( new_counter[15].word, "(BETA)v0.42");  */

			new_counter[15].alpha = 0.0f;

			if(sta2_yes_no_active == true)     
			{ 
				 
				hud[3].alpha = 1.0f;  

				sta2_yes_no_active = true;  
				 
				if(sta2_yes_no_page == 3)
				{
					new_counter[15].alpha = 1.0f;
					new_counter[15].x = hud[3].x + 0.06f;  
					new_counter[15].y =  hud[3].y + hud[3].height - 0.1f;
					new_counter[15].w = new_counter[15].x - 0.026f;   
					new_counter[15].z = new_counter[15].y - 0.015f;
					new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
					new_counter[15].box_height = new_counter[15].height - 0.015f;	
					sprintf(new_counter[15].word, "Overwrite^existing^save file?"); 
				}

				new_counter[7].alpha = 1.0f;  

				if(new_counter[7].id != 4 || sta2_yes_no_page == 0)
					new_counter[7].id = 0; 

				if(sta2_yes_no_page == 2) 
					new_counter[7].id = 0; 

				if(sta2_yes_no_page == 0)
					sprintf(new_counter[7].word, "1. YES"); 
				if(sta2_yes_no_page == 1)
					sprintf(new_counter[7].word, "1. CONTINUE");  
				if(sta2_yes_no_page == 2)
					sprintf(new_counter[7].word, "1. TRAINING"); 
				if(sta2_yes_no_page == 3)
					sprintf(new_counter[7].word, "1. YES"); 

				new_counter[7].x = hud[3].x + 0.06f;  
				new_counter[7].y =  hud[3].y + hud[3].height - 0.1f;
				new_counter[7].w = new_counter[7].x - 0.026f;   
				new_counter[7].z = new_counter[7].y - 0.015f;
				new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
				new_counter[7].box_height = new_counter[7].height - 0.015f;	

				if(sta2_yes_no_page == 3)
				{
					new_counter[7].y = hud[3].y + hud[3].height - 0.2f - 0.04f;
					new_counter[7].z = new_counter[7].y - 0.015f;
				}

				new_counter[8].alpha = 1.0f; 

				new_counter[8].id = 0;

				if(sta2_yes_no_page == 2)
				if(sta2_has_beaten_training_game == false)
					new_counter[8].id = 4;
				 
				if(sta2_yes_no_page == 0)
					sprintf(new_counter[8].word, "2. NO"); 
				if(sta2_yes_no_page == 1)
					sprintf(new_counter[8].word, "2. NEW GAME"); 
				if(sta2_yes_no_page == 2)
					sprintf(new_counter[8].word, "2. NORMAL");  
				if(sta2_yes_no_page == 3)
					sprintf(new_counter[8].word, "2. NO"); 

				new_counter[8].x = hud[3].x + 0.06f;  
				new_counter[8].y = hud[3].y + hud[3].height - 0.1f - 0.04f;
				new_counter[8].w = new_counter[8].x - 0.026f;   
				new_counter[8].z = new_counter[8].y - 0.015f;
				new_counter[8].box_width = strlen(new_counter[8].word)   *  0.026f;
				new_counter[8].box_height = new_counter[8].height - 0.015f;	

				if(sta2_yes_no_page == 3)
				{
					new_counter[8].y = hud[3].y + hud[3].height - 0.24f - 0.04f;
					new_counter[8].z = new_counter[8].y - 0.015f;
				}

				new_counter[9].alpha = 0.0f; 
				new_counter[10].alpha = 0.0f;  
				new_counter[11].alpha = 0.0f; 

				if(sta2_yes_no_page == 1 || sta2_yes_no_page == 2)
				{
					new_counter[9].alpha = 1.0f;
					new_counter[9].id = 0;

					if(sta2_yes_no_page == 2)
					if(sta2_has_beaten_normal_game == false)
						new_counter[9].id = 4;

					if(sta2_yes_no_page == 1) 
						sprintf(new_counter[9].word, "3. TUTORIAL"); 
					if(sta2_yes_no_page == 2)
						sprintf(new_counter[9].word, "3. HARD"); 

					new_counter[9].x = hud[3].x + 0.06f;  
					new_counter[9].y = hud[3].y + hud[3].height - 0.1f - 0.08f;
					new_counter[9].w = new_counter[9].x - 0.026f;   
					new_counter[9].z = new_counter[9].y - 0.015f;
					new_counter[9].box_width = strlen(new_counter[9].word)   *  0.026f;
					new_counter[9].box_height = new_counter[9].height - 0.015f;	
				}
				if(sta2_yes_no_page == 1  || sta2_yes_no_page == 2) 
				{ 
					new_counter[10].alpha = 1.0f; 
					new_counter[10].id = 0;

					sprintf(new_counter[10].word, "4. SHOP"); 
					if(sta2_yes_no_page == 2)
						sprintf(new_counter[10].word, "4. BACK"); 

					new_counter[10].x = hud[3].x + 0.06f;  
					new_counter[10].y = hud[3].y + hud[3].height - 0.1f - 0.12f;
					new_counter[10].w = new_counter[10].x - 0.026f;   
					new_counter[10].z = new_counter[10].y - 0.015f;
					new_counter[10].box_width = strlen(new_counter[10].word)   *  0.026f;
					new_counter[10].box_height = new_counter[10].height - 0.015f;	

				}
				if(sta2_yes_no_page == 1)  
				{ 
					new_counter[11].alpha = 1.0f; 
					new_counter[11].id = 0;

					sprintf(new_counter[11].word, "5. BACK"); 

					new_counter[11].x = hud[3].x + 0.06f;  
					new_counter[11].y = hud[3].y + hud[3].height - 0.1f - 0.16f;
					new_counter[11].w = new_counter[11].x - 0.026f;   
					new_counter[11].z = new_counter[11].y - 0.015f;
					new_counter[11].box_width = strlen(new_counter[11].word)   *  0.026f;
					new_counter[11].box_height = new_counter[11].height - 0.015f;	

				}

			}
			else        
			{
				new_counter[7].alpha = 0.0f;
				new_counter[8].alpha = 0.0f;
				new_counter[9].alpha = 0.0f;
				new_counter[10].alpha = 0.0f;
				new_counter[11].alpha = 0.0f;
				hud[3].alpha = 0.0f; 
			} 
			   
		   if(title_sequence == 0)                                 
		   {               

			   #if IS_FULL_STEAM == 1

				   if (STEAM_ACTIVE == true)
					   g_SteamLeaderboards_finalscore->DownloadScores(); 

			   #endif

			   Run_Ach();

			   hud_63_old_width = 0.0f;

			   // Always enable the speed bonus....
			   sta2_globals[GLOBAL_TYPE_SPEED] = GLOBALS_ACTIVE;			    

			   sta2_only_defend = true;
			   sta2_only_pistol = true;
			   sta2_only_grenade = true;

			   hud_63_old_width = 0.0f;
			   sta2_squad_bar_width=0.0f;

			   sta2_pressed_map = false;
			   sta2_final_boss = false; 

			   sta2_is_general_fight = false;

			   sta2_general_position = 0.0f;

			   sta2_enemies_defeated = 0;
			   sta2_gold_collected = 0;
			   sta2_highest_level = 2;
			   sta2_final_score = 0;

			   sta2_co_type = STA2_CO_ADA;

			   sta2_is_epic_battle = false;

  			   // XP gain stuff... 
			   for(int j=0;j<10;j++)
				   xp_damage_index[j] = -1;

			   xp_damage_count = 0;

			   sta2_danger_index = -1;

			   sta2_is_a_trader_event = false;
				sta2_trader_sequence = 0;

			    sta2_snow_start_index = no_sprites;
				 
				sta2_snow_timer = 0;
				sta2_snow_direction = 0;

				sta2_reset_movement = false;
				sta2_entered_action = false;

				sta2_officer_rank = 0;

			    // Create snowflakes... 
			    for(int i=0;i<NO_SNOWFLAKES;i++)   
			    {       
					if(i >= NO_FRONT_SNOWFLAKES)
						sprite[no_sprites].id = 16;        
					else
						sprite[no_sprites].id = 15;  

					sprite[no_sprites].light = 1.0f; 
					 
					if(i >= NO_FRONT_SNOWFLAKES) 
						sprite[no_sprites].priority = 5; 
					else
						sprite[no_sprites].priority = 3;

					sprite[no_sprites].fx_id = animation_fx[sprite[no_sprites].id];

				    sprite[no_sprites].depth = 0.0f; 
				     
					// Randomise positions...   
					rnd = rand()%100;
				    sprite[no_sprites].x = sprite[1].x + ((sprite[1].width/100)*(float)rnd);  
					rnd = rand()%100;
				    sprite[no_sprites].y = sprite[1].y + ((sprite[1].height/100)*(float)rnd);  

				    sprite[no_sprites].w = sprite[no_sprites].x; 
				    sprite[no_sprites].z = sprite[no_sprites].y; 

				    sprite[no_sprites].width = 0.05f; 
				    sprite[no_sprites].height = 0.05f;  
				    sprite[no_sprites].box_width = 0.05f; 
				    sprite[no_sprites].box_height = 0.05f; 

					sprite[no_sprites].angle2 = 0.0f;

				    sprite[no_sprites].alpha = 1.0f;  
					 
					sprite[no_sprites].type = NON;

				    sprite[no_sprites].mouseover = false;
				    
				    sprite[no_sprites].turn_off = false; 

					if(rand()%5 == 0)
						sprite[no_sprites].anim = 0;
					else
						sprite[no_sprites].anim = 1;

					sprite[no_sprites].value1 = rand()%4;

					sprite[no_sprites].cur = 0;    

					sprite[no_sprites].cur_time = 0;
                         
					sprite[no_sprites].anim_state = LOOP;
                
#ifndef DREAMCAST
					sprite[no_sprites].frame = a_texture[sprite[no_sprites].fx_id].anims[sprite[no_sprites].anim][sprite[no_sprites].cur];
#else
					sprite[no_sprites].frame = a_texture_get_anims_secondlayer(sprite[no_sprites].fx_id, sprite[no_sprites].anim, sprite[no_sprites].cur);
#endif
            
					sprite[no_sprites].base_anim = sprite[no_sprites].anim;

					Set_Sprite(no_sprites, sprite[no_sprites].anim, LOOP, ANIM_SPRITE, ANIM_WALKING);

					no_sprites++;   

				}

			    sta2_got_speed_bonus = false; 
				sta2_got_triple_bonus = false;
				sta2_got_double_bonus = false;
				sta2_got_epic_bonus = false;

			    sta2_no_of_turns = 0;

			    sta2_yes_no_page_battle = 0;
			    sta2_yes_no_page_squad = 0; 
				sta2_yes_no_page=0;
				sta2_yes_no_page_map=0; 

			    sta2_display_tutorial_text1 = false;
				sta2_display_tutorial_text2 = false;
				sta2_display_tutorial_text3 = false;
				sta2_display_tutorial_text4 = false; 
				sta2_display_tutorial_text5 = false; 
				sta2_display_tutorial_text6 = false;

			    sta2_playing_tutorial = false; 

			    sta2_ended_turn = false;

			    sta2_power_result = STA2_POWER_NONE;

			    if(QUICK_PLAY == 1)
				{
					sta2_scroll_route_map = false;
					sta2_displaying_help = false;
				}
				else
				{
					sta2_scroll_route_map = true; 
				//	sta2_displaying_help = true;
				}

				sta2_displaying_help = false;

			    sta2_tactics = TACTIC_KEYS;
				 
			    sta2_yes_no_active = false;
				    
			    sta2_is_bandit_level = false;      
				      
			    sta2_team_starved = false;                 
				         
			    sta2_battle_ready = false;          
				 
			    sta2_food_rations = RATIONS_MID;    

			    sta2GetEmyNames("data/text/names/namesB.txt");  

			    sta2_environment_type = rand()%4; // AREA_GRASSLANDS
				sta2_first_area = sta2_environment_type;    

				// AREA_GRASSLANDS                 
				// AREA_FOREST             
				// AREA_SWAMP              
				// AREA_FARM                      
				                    
				// AREA_DESERT                                              
				// AREA_SNOW                                                
				                                               
				// AREA_BEACH                               
				// AREA_MOUNTAIN                             
				// AREA_CITY                              
				// AREA_TRENCH                
				       
				// AREA_CASTLE                 
				      
		//		sta2_environment_type = AREA_FOREST;  
				 
				sta2_sector = 1;    
				  
			    sta2_packpage_index=0;    
			    sta2_equip_this_unit = -1;     

				for(int j = 0;j< STA2_PACKS_LIMIT;j++)     
				{ 
					sta2_pack[j].type = STA2_VOID;     
					sta2_pack[j].rank = 0; 
					sta2_pack[j].equipped = false;
					sta2_pack[j].extra = PACK_EXTRA_NONE;
					sta2_pack[j].extra_charge = 0;
					sta2_pack[j].special = PACK_SPECIAL_NONE;
					sta2_pack[j].special_charge = 0;
					sta2_pack[j].active1 = PACK_ACTIVE_NONE;
					sta2_pack[j].active2 = PACK_ACTIVE_NONE;
					sta2_pack[j].active3 = PACK_ACTIVE_NONE;
					sta2_pack[j].active4 = PACK_ACTIVE_NONE;

					sprintf(sta2_pack[j].string, "NONE"); 
				}    
				 
			    sta2_shop.heal_cost = 0; 

				for(int j = 0;j< SHOP_LIMIT_ITEMS;j++)
				{
					sta2_shop.food_type[j] = SHOP_FOOD_NONE;
					sta2_shop.food_amount[j] = 0; 
					sta2_shop.food_cost[j] = 0;
					sta2_shop.hire_type[j] = STA2_VOID;   
					sta2_shop.hire_rank[j] = 0; 
					sta2_shop.hire_face[j] = 0; 
					sta2_shop.hire_cost[j] = 0;
					sta2_shop.pack_type[j] = STA2_VOID; 
					sta2_shop.pack_rank[j] = 0; 
					sta2_shop.pack_cost[j] = 0;
					sprintf( sta2_shop.hire_string[0], "NONE");
				} 

			    sta2_shop_tab = SHOP_FOOD;
				 
			    sta2_squadpage_index = 0;  

			    memset(map_pins, 0, sizeof(map_pins));

			    sta2_next_event = EVENT_INTRO;

			    sta2_battle_outcome = BATTLE_NONE;

			    sta2_sector_create_pins = true; 

				sta2_current_sector_pin = 3;  
				sta2_current_pin=3; 
 
			   	sta2_computer_co_down = false; 
				sta2_player_co_down = false; 

			    sta2_picked_up_gold=0;
			    sta2_picked_up_food=0;   

			    sta2_squad_count=0;    
				sta2_roster_count=0; 

				target_pin=-1;  
				 
				// Reset the squad...  
				for(int i =0;i<50;i++) 
				{ 
					sta2_squad[i].health = 0;       
					sta2_squad[i].xp = 0;   
					sta2_squad[i].rank = 0;   
					sta2_squad[i].type = STA2_VOID; 
					sta2_squad[i].wp = 0;    
					sprintf(sta2_squad[i].string, "EMPTY");         
				}   
				  
				sta2_pack[0].type = STA2_SCOUT;                
				sta2_pack[0].rank = 1;       
				sta2_pack[0].equipped = true;  
				sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
				sta2_pack[0].extra_charge = 0; 
				sta2_pack[0].special = PACK_SPECIAL_SCOPE;   // PACK_EXTRA_MEDKIT
				sta2_pack[0].special_charge = 0;
				sprintf(sta2_pack[0].string, "SCOUT PACK");   
				 
				sta2_pack[1].type = STA2_SCOUT;       
				sta2_pack[1].rank = 1;  
				sta2_pack[1].equipped = true; 
				sta2_pack[1].extra = PACK_EXTRA_GRENADE;   // PACK_EXTRA_GRENADE
				sta2_pack[1].extra_charge = 1;
				sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
				sta2_pack[1].special_charge = 0;
				sprintf(sta2_pack[1].string, "SCOUT PACK");   

				sta2_pack[2].type = STA2_SCOUT;      
				sta2_pack[2].rank = 1;     
				sta2_pack[2].equipped = true; 
				sta2_pack[2].extra = PACK_EXTRA_GRENADE;  
				sta2_pack[2].extra_charge = 1;
				sta2_pack[2].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
				sta2_pack[2].special_charge = 0;
				sprintf(sta2_pack[2].string, "SCOUT PACK"); 


		/*		sta2_pack[3].type = STA2_MORTAR;      
				sta2_pack[3].rank = 1;       
				sta2_pack[3].equipped = true; 
				sta2_pack[3].extra = PACK_EXTRA_NONE;  
				sta2_pack[3].extra_charge = 0;
				sta2_pack[3].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
				sta2_pack[3].special_charge = 0;
				sprintf(sta2_pack[3].string, "MORTAR PACK"); 

				sta2_pack[4].type = STA2_MORTAR;      
				sta2_pack[4].rank = 1;       
				sta2_pack[4].equipped = true; 
				sta2_pack[4].extra = PACK_EXTRA_NONE;  
				sta2_pack[4].extra_charge = 0;
				sta2_pack[4].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
				sta2_pack[4].special_charge = 0;
				sprintf(sta2_pack[4].string, "MORTAR PACK"); */

				// Add some units to the roster...   
				sta2_squad[sta2_squad_count].xp = 0; 
				sta2_squad[sta2_squad_count].face = 0; // 1+rand()%10
				sta2_squad[sta2_squad_count].deployed = false;  
				sta2_squad[sta2_squad_count].rank = 2;   
				sta2_squad[sta2_squad_count].type = STA2_CO;
				sta2_squad[sta2_squad_count].wp = 0; 
				sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
				sprintf(sta2_squad[sta2_squad_count].string, "ADA"); 
				sta2_squad_count++;   
				 
				sta2_squad[sta2_squad_count].xp = 0; 
				sta2_squad[sta2_squad_count].face = 1+rand()%10;    
				sta2_squad[sta2_squad_count].deployed = false; 
				sta2_squad[sta2_squad_count].rank = 1;   
				sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
				sta2_squad[sta2_squad_count].wp = 1; 
				sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
				sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
				sta2_squad_count++;   
				  
				sta2_squad[sta2_squad_count].xp = 0;  
				sta2_squad[sta2_squad_count].face = 1+rand()%10;
				sta2_squad[sta2_squad_count].deployed = false; 
				sta2_squad[sta2_squad_count].rank = 1; 
				sta2_squad[sta2_squad_count].type = STA2_SCOUT;
				sta2_squad[sta2_squad_count].wp = 2; 
				sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
				sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
				sta2_squad_count++;      
				      
		/*		sta2_squad[sta2_squad_count].xp = 0;  
				sta2_squad[sta2_squad_count].face = 30; 
				sta2_squad[sta2_squad_count].deployed = false; 
				sta2_squad[sta2_squad_count].rank = 1; 
				sta2_squad[sta2_squad_count].type = STA2_MORTAR;
				sta2_squad[sta2_squad_count].wp = 3; 
				sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
				sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
				sta2_squad_count++;    
				    
				sta2_squad[sta2_squad_count].xp = 0;   
				sta2_squad[sta2_squad_count].face = 30; 
				sta2_squad[sta2_squad_count].deployed = false; 
				sta2_squad[sta2_squad_count].rank = 1; 
				sta2_squad[sta2_squad_count].type = STA2_MORTAR;
				sta2_squad[sta2_squad_count].wp = 4; 
				sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
				sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
				sta2_squad_count++;  */

				sta2_squad_alive_count = sta2_squad_count; 
				 
				for(int i=0 ; i < 12;i++)
					sta2_battle_squad[i] = -1;

				// Create a dummy battle squad; Move to squad select screen at some point...
				for(int i=0 ; i < sta2_squad_count;i++)
				{
					if(sta2_squad[i].deployed == true) 
					{
						sta2_battle_squad[sta2_roster_count] = i; // Is roster unit 0
						sta2_roster_count++;
					} 
				}

			    sta2_route_create_pins=true; 

				pin_camX = 0.0f;

			    sta2_food = STA2_FOOD_START;
				sta2_gold = STA2_GOLD_START;

			    sta2_loaded_level = false;

				sta2_shots_rifle = 0;  
				sta2_shots_pistol = 0; 
				sta2_shots_shotgun = 0;  
				sta2_shots_machine = 0; 
				sta2_shots_sniper = 0;  
				sta2_shots_mortar = 0; 

				sta2_player_moves = 3;   // Was 3
				sta2_enemy_moves  = 3;   // Was 3

				sta2_enemy_mode = MOVE_WAIT; 

				STA2_MODE = MODE_MOVING;

				sta2_change_turn = true; 

				sta2_turn = TURN_NONE;
				  
				sta2_steps_taken = 0; 
				   
				emy_id = -1;  

				ply_id = -1;
	
			    sprintf( new_counter[0].word, "1. START GAME" ); // 1 : START GAME

			    new_counter[0].alpha = 1.0f;        
			    new_counter[0].id = 0;
		     
			    new_counter[0].x = -0.60f;      
			    new_counter[0].y = -0.34f;  	      

				new_counter[0].w = new_counter[0].x - 0.026f;   
				new_counter[0].z = new_counter[0].y - 0.015f;

				new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
				new_counter[0].box_height = new_counter[0].height - 0.015f;	

			    sprintf( new_counter[1].word, "2. OPTIONS"); 

			    new_counter[1].alpha = 1.0f;         
			    new_counter[1].id = 0; 
		      
			    new_counter[1].x = -0.10f;      
			    new_counter[1].y = -0.34f;  	      

				new_counter[1].w = new_counter[1].x - 0.026f;   
				new_counter[1].z = new_counter[1].y - 0.015f;

				new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
				new_counter[1].box_height = new_counter[1].height - 0.015f;	

			    sprintf( new_counter[2].word, "3. QUIT"); 

			    new_counter[2].alpha = 1.0f;         
			    new_counter[2].id = 0; 
		       
			    new_counter[2].x = +0.42f;              
			    new_counter[2].y = -0.34f;  	      
				 
				new_counter[2].w = new_counter[2].x - 0.026f;   
				new_counter[2].z = new_counter[2].y - 0.015f;

				new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
				new_counter[2].box_height = new_counter[2].height - 0.015f;	
				
				sta2_Scroll(0, true, f_rate, RIGHT);
				sta2_Scroll(1, true, f_rate, UP); 
				sta2_Scroll(2, true, f_rate, LEFT);

		/*	    sprintf( new_counter[13].word, "TOKENS:%i", sta2_tokens);  

				new_counter[13].alpha = 1.0f;                  
			    new_counter[13].id = 0;  
		          
			    new_counter[13].x = -0.64f;       
		        new_counter[13].y = 0.36f;  	       

			    new_counter[13].w = new_counter[13].x - 0.026f;   
			    new_counter[13].z = new_counter[13].y - 0.015f;

			    new_counter[13].box_width = strlen(new_counter[13].word)   *  0.026f;
			    new_counter[13].box_height = new_counter[13].height - 0.015f;	*/

				title_sequence++;
				 
			}    

			// Scroll in text...
			sta2_Scroll(0, false, f_rate, RIGHT);
			sta2_Scroll(1, false, f_rate, UP);
			sta2_Scroll(2, false, f_rate, LEFT);
			   
			// Make snow fall..  
			for(int i=sta2_snow_start_index;i<sta2_snow_start_index+NO_SNOWFLAKES;i++)
			{  
				 if(sprite[i].value1 == 0)  
					temp_speed = 0.00018f*(float)f_rate;     

				 if(sprite[i].value1 == 1)
					temp_speed = 0.0002f*(float)f_rate;   

				 if(sprite[i].value1 == 2)
					temp_speed = 0.00022f*(float)f_rate;   

				 if(sprite[i].value1 == 3) 
					temp_speed = 0.00025f*(float)f_rate; 

				 if(i >= sta2_snow_start_index+NO_FRONT_SNOWFLAKES)
					 temp_speed /= 4;

				 sprite[i].y -= temp_speed;   

				 if((int)TimerGetTime() > sta2_snow_timer)
				 {
					 sta2_snow_direction = rand()%3;
					  
					 if(sta2_snow_direction == 0)
						sta2_snow_timer = (int)TimerGetTime()+4000;  
					 else
						sta2_snow_timer = (int)TimerGetTime()+2000;  

				 }
				   
				 if(sta2_snow_direction == 0) 
				 { 
					 if(sprite[i].angle2 > 0.0f) 
						 sprite[i].angle2 -=  0.000001f*(float)f_rate; 

					 if(sprite[i].angle2 < 0.0f)  
						 sprite[i].angle2 +=  0.000001f*(float)f_rate; 

					 sprite[i].x += sprite[i].angle2; 
				 }

				 if(sta2_snow_direction == 1)   
				 {
					sprite[i].angle2 +=  0.000002f*(float)f_rate; 

					if(sprite[i].angle2 > temp_speed)
						sprite[i].angle2 = temp_speed;

					sprite[i].x += sprite[i].angle2;  
				 } 

				 if(sta2_snow_direction == 2)  
				 {
					sprite[i].angle2 -=  0.000002f*(float)f_rate; 

					if(sprite[i].angle2 < -temp_speed) 
						sprite[i].angle2 = -temp_speed;  

					sprite[i].x += sprite[i].angle2; 
				 }

				 if(sprite[i].y < sprite[1].y - sprite[i].height)
				 {
					 sprite[i].y = sprite[1].y + sprite[1].height*1.1f; 
					// Randomise positions...
					rnd = rand()%100;
				    sprite[i].x = sprite[1].x + ((sprite[1].width/100)*(float)rnd);  

					sprite[i].value1 = rand()%4;
				 } 
				  
				 if(i <= sta2_snow_start_index+NO_FRONT_SNOWFLAKES)
				 {
					 if(sprite[i].y < sprite[4].z)
					 if(sprite[i].x > sprite[4].w && sprite[i].x < sprite[4].w + sprite[4].width)
					 {
						 sprite[i].y = sprite[1].y + sprite[1].height*1.1f; 
						// Randomise positions...
						rnd = rand()%100;
						sprite[i].x = sprite[1].x + ((sprite[1].width/100)*(float)rnd);  
					 
						sprite[i].value1 = rand()%4;       
					 } 
					 if(sprite[i].y < sprite[5].z)  
					 if(sprite[i].x > sprite[5].w && sprite[i].x < sprite[5].w + sprite[5].width)
					 {
						 sprite[i].y = sprite[1].y + sprite[1].height*1.1f; 
						// Randomise positions...
						rnd = rand()%100;
						sprite[i].x = sprite[1].x + ((sprite[1].width/100)*(float)rnd);  

						sprite[i].value1 = rand()%4;
					 } 
					 if(sprite[i].y < sprite[2].z)  
					 if(sprite[i].x > sprite[2].w && sprite[i].x < sprite[2].w + sprite[2].width)
					 {
						 sprite[i].y = sprite[1].y + sprite[1].height*1.1f; 
						// Randomise positions...
						rnd = rand()%100;
						sprite[i].x = sprite[1].x + ((sprite[1].width/100)*(float)rnd);  

						sprite[i].value1 = rand()%4;
					 }
				 }

			}
			   
			if(title_sequence == 1) 
			{ 
       
                new_counter[0].alpha = 1.0f;  
				new_counter[0].id = 0;
				new_counter[1].id = 0;
				new_counter[2].id = 0;

				if(sta2_yes_no_active == true) 
				{
					new_counter[0].id = 4; 
					new_counter[1].id = 4;
					new_counter[2].id = 4;
				}

				testX = hud_mouseX - (-camX);                                                
				testY = hud_mouseY - (-camY);    

				// YES...
				if(sta2_yes_no_active == true) 
				if(new_counter[7].id != 4) // Greyed out...
				if(new_counter[7].alpha == 1.0f)
				if(( testX < (new_counter[7].w + new_counter[7].box_width) )
				&&( testX > new_counter[7].w)                            
				&&( testY < (new_counter[7].z + new_counter[7].box_height) )
				&&( testY > new_counter[7].z) || sta2_1_pressed == true)   
				{ 
					new_counter[7].id = 2;    

					if(mouseleft == true || DX_SHOOT == true || sta2_1_pressed == true) 
					{  
						sta2_1_pressed = false;
						mouseleft = false;       
						DX_SHOOT = false;     
						 
						if(sta2_yes_no_page == 0)
						{ 
							done = true;
							quitting=false;  
						}
						if(sta2_yes_no_page == 1) 
						{ 
							// Continue
							sta2_playing_tutorial = false;
	
							sprintf( temp_string.string, "data/save/sta2");

							STA2_LoadLevel(temp_string);

 						} 
						if(sta2_yes_no_page == 2)
						{

							sta2_food = STA2_FOOD_START_TRAINING;
							sta2_gold = STA2_GOLD_START_TRAINING; 

							sta2_difficulty = STA2_TRAINING_MODE;
							// New Game
							//sta2_playing_tutorial = false;
							//Start_Game();        
							scene = 27;
							episode = 1;

							for(int i=0;i<25;i++)
								new_counter[i].alpha = 0.0f;

							next_scene = true;

 						} 

						if(sta2_yes_no_page != 3)
							title_sequence++;	

						if(sta2_yes_no_page == 3)
						{
							sta2_yes_no_page = 2;
						}
					} 
				}  

				// NO...
				if(sta2_yes_no_active == true)
				if(new_counter[8].id != 4) // Greyed out...
				if(new_counter[8].alpha == 1.0f)
				if(( testX < (new_counter[8].w + new_counter[8].box_width) )
				&&( testX > new_counter[8].w)                            
				&&( testY < (new_counter[8].z + new_counter[8].box_height) )
				&&( testY > new_counter[8].z) || sta2_2_pressed == true)   
				{ 
					new_counter[8].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_2_pressed == true) 
					{  
						sta2_2_pressed = false;
						mouseleft = false;       
						DX_SHOOT = false;      

						switch(sta2_yes_no_page)
						{
							case 3:
								sta2_yes_no_page = 1;
							break;	 					 

							case 2: 
							 
								sta2_food = STA2_FOOD_START;
								sta2_gold = STA2_GOLD_START; 

								sta2_difficulty = STA2_NORMAL_MODE;
								// New Game
								//sta2_playing_tutorial = false;
								//Start_Game();          
								scene = 27;
								episode = 1; 

								for(int i=0;i<25;i++)
									new_counter[i].alpha = 0.0f;

								next_scene = true;

								sta2_yes_no_active = false;
								hud[3].alpha = 0.0f;

 							break;  

							case 0: 
								sta2_yes_no_active = false;
								sta2_yes_no_active = false;
								hud[3].alpha = 0.0f;
							break;

							case 1:
								// New Game
								// Check if this scene has a temp 
								sprintf( string, "data/save/sta2.sav");    

								if(STA2_HasSave( string ))
									sta2_yes_no_page = 3;       
								else
									sta2_yes_no_page = 2;       
 							break;

						} // End switch...
					}
				}  
	 
				// Option3...
				if(sta2_yes_no_active == true)
				if(new_counter[9].id != 4) // Greyed out...
				if(new_counter[9].alpha == 1.0f)
				if(( testX < (new_counter[9].w + new_counter[9].box_width) )
				&&( testX > new_counter[9].w)                            
				&&( testY < (new_counter[9].z + new_counter[9].box_height) )
				&&( testY > new_counter[9].z) || sta2_3_pressed == true)   
				{ 
					new_counter[9].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_3_pressed == true) 
					{  
						sta2_3_pressed = false; 
						mouseleft = false;       
						DX_SHOOT = false;      

						if(sta2_yes_no_page == 1)
						{
							sta2_playing_tutorial = true;
							Start_Game();        
							title_sequence++;

							for(int i=0;i<25;i++)
							    new_counter[i].alpha = 0.0f;

							sta2_yes_no_active = false;
							hud[3].alpha = 0.0f;
						}
						if(sta2_yes_no_page == 2) 
						{
							 
								sta2_food = STA2_FOOD_START;
								sta2_gold = STA2_GOLD_START; 

								sta2_difficulty = STA2_HARD_MODE;
								// New Game
								//sta2_playing_tutorial = false;
								//Start_Game();          
								scene = 27;
								episode = 1; 

								for(int i=0;i<25;i++)
									new_counter[i].alpha = 0.0f;

								next_scene = true;

								sta2_yes_no_active = false;
								hud[3].alpha = 0.0f;
						}

						 
					} 
				}  
				 

				// Option4...
				if(sta2_yes_no_active == true)
				if(new_counter[10].id != 4) // Greyed out...
				if(new_counter[10].alpha == 1.0f)
				if(( testX < (new_counter[10].w + new_counter[10].box_width) )
				&&( testX > new_counter[10].w)                            
				&&( testY < (new_counter[10].z + new_counter[10].box_height) )
				&&( testY > new_counter[10].z) || sta2_4_pressed == true)   
				{ 
					new_counter[10].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_4_pressed == true) 
					{  
						sta2_4_pressed = false;  
						mouseleft = false;        
						DX_SHOOT = false;       

						if(sta2_yes_no_page != 2)   
						{ 

							scene = 16;
							episode = 0; 

							next_scene = true;

							sta2_yes_no_active = false;
							hud[3].alpha = 0.0f;
						} 

						if(sta2_yes_no_page == 2)   
						{
							sta2_yes_no_page = 1;
						} 

					}
				}  
				// Option5...
				if(sta2_yes_no_active == true)
				if(new_counter[11].id != 4) // Greyed out...
				if(new_counter[11].alpha == 1.0f)
				if(( testX < (new_counter[11].w + new_counter[11].box_width) )
				&&( testX > new_counter[11].w)                            
				&&( testY < (new_counter[11].z + new_counter[11].box_height) )
				&&( testY > new_counter[11].z) || sta2_5_pressed == true)   
				{ 
					new_counter[11].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_5_pressed == true) 
					{  
						sta2_5_pressed = false; 
						mouseleft = false;       
						DX_SHOOT = false;    

						sta2_yes_no_active = false;
						hud[3].alpha = 0.0f;
						 
					}
				}  

				if(sta2_yes_no_active == false)
				if(( testX < (new_counter[0].w + new_counter[0].box_width) )
				&&( testX > new_counter[0].w)                            
				&&( testY < (new_counter[0].z + new_counter[0].box_height) )
				&&( testY > new_counter[0].z) || sta2_1_pressed == true)   
				{ 
					new_counter[0].id = 2;       

					if(mouseleft == true || DX_SHOOT == true || sta2_1_pressed == true) 
					{  
						
						mouseleft = false;      
						DX_SHOOT = false;   
						sta2_1_pressed = false;      

						if(sta2_finished_tutorial == false) 
						{
							sta2_playing_tutorial = true;
							Start_Game();        

							for(int i=0;i<25;i++)
							    new_counter[i].alpha = 0.0f;

							title_sequence++;
						}
						else 
						{
			    
							// Check if this scene has a temp 
							sprintf( string, "data/save/sta2.sav");    

							if(STA2_HasSave( string ))
								new_counter[7].id = 0; 
							else
								new_counter[7].id = 4;

							sta2_yes_no_active = true;
							sta2_yes_no_page = 1;
						}

						 
					} 
				}    

				if(sta2_yes_no_active == false)
				if(( testX < (new_counter[1].w + new_counter[1].box_width) )
				&&( testX > new_counter[1].w)                            
				&&( testY < (new_counter[1].z + new_counter[1].box_height) )
				&&( testY > new_counter[1].z) || sta2_2_pressed == true)   
				{ 
					new_counter[1].id = 2;        

					if(mouseleft == true || DX_SHOOT == true || sta2_2_pressed == true) 
					{  
						
						mouseleft = false;  
						DX_SHOOT = false; 
						sta2_2_pressed = false;

						for(int i=0;i<25;i++)
						    new_counter[i].alpha = 0.0f;

						scene = 2; 
						episode = 0;
						next_scene = true;

						title_sequence++;
						   
					}
				}    
	  
				// Quit game...
				if(sta2_yes_no_active == false)
				if(( testX < (new_counter[2].w + new_counter[2].box_width) )
				&&( testX > new_counter[2].w)                            
				&&( testY < (new_counter[2].z + new_counter[2].box_height) )
				&&( testY > new_counter[2].z) || sta2_3_pressed == true || sta2_esc_pressed == true)   
				{ 
					new_counter[2].id = 2;         

					if(mouseleft == true || DX_SHOOT == true || sta2_3_pressed == true || sta2_esc_pressed == true) 
					{  
						   
						sta2_esc_pressed = false;
						mouseleft = false; 
						DX_SHOOT = false; 
						sta2_3_pressed = false;

						sta2_yes_no_active = true; 

						sta2_yes_no_page = 0;
						 
					}
				}   

				if(sta2_yes_no_active == true)
				if(sta2_esc_pressed == true)
				{
					sta2_esc_pressed = false;
					sta2_yes_no_active = false;
				}


			}


	
       }// scene == 1

    // ******************************************************************************//
    //                           1-14  (TACTICS SCREEN)                              //
    // ******************************************************************************//
           
    // Title Screen Stuff...      
    if(!mode) 
    if(next_scene == false) 
    if(episode == 1 && scene == 14)    
    {      

		SwipeCode(f_rate); 

		if(title_sequence == 0)
		{ 
			// Reset the menu list...
			for(int i = 0;i<25;i++)
			{
				sta2_tactic_menu[i] = TACTIC_MENU_NONE;
			}

			sta2_tactics_index = 0;

			if(sta2_tactics == TACTIC_KEYS) 
			{ 
				sta2_tactic_menu[0] = TACTIC_MENU_MOVEMENT;
				sta2_tactic_menu[1] = TACTIC_MENU_PRIMARY;
				sta2_tactic_menu[2] = TACTIC_MENU_SECONDARY;
				sta2_tactic_menu[3] = TACTIC_MENU_DEFEND;
				sta2_tactic_menu[4] = TACTIC_MENU_EXTRA;
				sta2_tactic_menu[5] = TACTIC_MENU_SPECIAL;
				sta2_tactic_menu[6] = TACTIC_MENU_CANCEL;
				sta2_tactic_menu[7] = TACTIC_MENU_ENDTURN;
				sta2_tactics_count = 7;
			}

			if(sta2_tactics == TACTIC_BASIC)  
			{ 
				sta2_tactic_menu[0] = TACTIC_MENU_COVER;
				sta2_tactic_menu[1] = TACTIC_MENU_HEADSHOT;
				sta2_tactic_menu[2] = TACTIC_MENU_FOOTSHOT;
				sta2_tactic_menu[3] = TACTIC_MENU_LASTMAN;
				sta2_tactics_count = 4;
			}

			if(sta2_tactics == TACTIC_SPECIAL)  
			{ 
				sta2_tactic_menu[0] = TACTIC_MENU_SCOPE;
				sta2_tactic_menu[1] = TACTIC_MENU_SHIELD;
				sta2_tactic_menu[2] = TACTIC_MENU_RAGE;
				sta2_tactic_menu[3] = TACTIC_MENU_DASH;
				sta2_tactic_menu[4] = TACTIC_MENU_GODEYE;
				sta2_tactic_menu[5] = TACTIC_MENU_CLOAK; 
				sta2_tactic_menu[6] = TACTIC_MENU_VAMPIRE;
				sta2_tactic_menu[7] = TACTIC_MENU_MARYJANE;
				sta2_tactic_menu[8] = TACTIC_MENU_WISDOM;
				sta2_tactic_menu[9] = TACTIC_MENU_FINAL;
				sta2_tactic_menu[10] = TACTIC_MENU_LAST;

				sta2_tactics_count = 11;
			}

			sprintf( new_counter[2].word, "3. Back");  

			new_counter[2].alpha = 1.0f;                  
			new_counter[2].id = 0;  
		      
			if(screen_mode == SCREEN_1610_WIDESCREEN)
				new_counter[2].x = +0.46f;        
			else
				new_counter[2].x = +0.50f;    

			new_counter[2].y = -0.34f;  	      

			new_counter[2].w = new_counter[2].x - 0.026f;   
			new_counter[2].z = new_counter[2].y - 0.015f;

			new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
			new_counter[2].box_height = new_counter[2].height - 0.015f;

			new_counter[3].alpha = 1.0f;              
			new_counter[3].id = 0;     
		       
			new_counter[3].x = -0.35f;            
			new_counter[3].y = +0.01f;   

			sprintf( new_counter[3].word, "Select a tactic to display.");

			title_sequence++;
		}

		if(title_sequence == 1) 
		{ 

			for(int i = 1;i<7;i++)
			{ 
				Set_Sprite(i, sta2_tactic_menu[sta2_tactics_index+(i-1)], LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Point Arrow 
				sprite[i].value2 = sta2_tactic_menu[sta2_tactics_index+(i-1)];
			}

			new_counter[2].id = 0; 
				 
			testX = hud_mouseX - (-camX);                                                  
			testY = hud_mouseY - (-camY);   
				   
			// Keys button...  
			if(sprite[8].alpha == 1.0)    
			if(( mouseX < (sprite[8].w + sprite[8].box_width) )
			&&( mouseX > sprite[8].w)                            
			&&( mouseY < (sprite[8].z + sprite[8].box_height) )
			&&( mouseY > sprite[8].z)) 
			{
				Set_Sprite(8, sprite[8].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				if(mouseleft == true)
				{
					sta2_tactics = TACTIC_KEYS;
					title_sequence = 0;
				}
			}
			else 
				Set_Sprite(8, sprite[8].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				   
			// Basic button...  
			if(sprite[9].alpha == 1.0)    
			if(( mouseX < (sprite[9].w + sprite[9].box_width) )
			&&( mouseX > sprite[9].w)                            
			&&( mouseY < (sprite[9].z + sprite[9].box_height) )
			&&( mouseY > sprite[9].z)) 
			{
				Set_Sprite(9, sprite[9].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				if(mouseleft == true)
				{
					sta2_tactics = TACTIC_BASIC;
					title_sequence = 0;
				}
			}
			else 
				Set_Sprite(9, sprite[9].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				   
			// Basic button...  
			if(sprite[10].alpha == 1.0)    
			if(( mouseX < (sprite[10].w + sprite[10].box_width) )
			&&( mouseX > sprite[10].w)                            
			&&( mouseY < (sprite[10].z + sprite[10].box_height) )
			&&( mouseY > sprite[10].z)) 
			{
				Set_Sprite(10, sprite[10].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				if(mouseleft == true)
				{
					sta2_tactics = TACTIC_SPECIAL;
					title_sequence = 0;
				}
			}
			else 
				Set_Sprite(10, sprite[10].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

			// Back..
			if(new_counter[2].alpha == 1.0f)
			if(( testX < (new_counter[2].w + new_counter[2].box_width) )
			&&( testX > new_counter[2].w)                            
			&&( testY < (new_counter[2].z + new_counter[2].box_height) )
			&&( testY > new_counter[2].z) || sta2_3_pressed == true)   
			{ 
				new_counter[2].id = 2;   

				if(mouseleft == true || DX_SHOOT == true || sta2_3_pressed == true) 
				{  
						 
					mouseleft = false;        
					DX_SHOOT = false;   
					sta2_3_pressed = false;     
						 
					episode = 1;  
					scene = 5;

					next_scene = true;
						  
				}    
			}   

			new_counter[1].alpha = 0.0f;
			new_counter[5].alpha = 0.0f;

			sprintf( new_counter[3].word, "Select a tactic to display.");

			for(int i = 1;i<7;i++)
			if(sprite[i].alpha == 1.0)                      
			if(sprite[i].value2 > 0)
			if(( mouseX < (sprite[i].w + sprite[i].box_width) )
			&&( mouseX > sprite[i].w)                            
			&&( mouseY < (sprite[i].z + sprite[i].box_height) )
			&&( mouseY > sprite[i].z)) 
			{
					   
				new_counter[1].alpha = 1.0f;               
					   
				new_counter[1].x = mouseX + 0.13f;                   
				new_counter[1].y = mouseY;    

				new_counter[5].alpha = 1.0f;               
					    
				new_counter[5].x = mouseX + 0.1f;                   
				new_counter[5].y = mouseY;   
					 
				sprintf( new_counter[5].word, "@");      

				if(sprite[i].value2 == TACTIC_MENU_MOVEMENT)   
    				sprintf( new_counter[1].word, "$WASD$ MOVEMENT^");  

				if(sprite[i].value2 == TACTIC_MENU_PRIMARY)   
    				sprintf( new_counter[1].word, "$1$ PRIMARY^");  

				if(sprite[i].value2 == TACTIC_MENU_SECONDARY)   
    				sprintf( new_counter[1].word, "$2$ SECONDARY^");	         
						  
				if(sprite[i].value2 == TACTIC_MENU_DEFEND)          
    				sprintf( new_counter[1].word, "$3$ DEFEND^");     
						  
				if(sprite[i].value2 == TACTIC_MENU_EXTRA)       
    				sprintf( new_counter[1].word, "$4$ EXTRA^"); 
						  
				if(sprite[i].value2 == TACTIC_MENU_SPECIAL)   
    				sprintf( new_counter[1].word, "$5$ SPECIAL^");

				if(sprite[i].value2 == TACTIC_MENU_CANCEL)    
    				sprintf( new_counter[1].word, "$6$ VIEWMAP^"); 

				if(sprite[i].value2 == TACTIC_MENU_ENDTURN)    
    				sprintf( new_counter[1].word, "$7$ END TURN^");  
						  
				if(sprite[i].value2 == TACTIC_MENU_COVER)   
    				sprintf( new_counter[1].word, "TAKING COVER^");

				if(sprite[i].value2 == TACTIC_MENU_HEADSHOT)    
    				sprintf( new_counter[1].word, "HEADSHOTS^"); 

				if(sprite[i].value2 == TACTIC_MENU_FOOTSHOT)   
    				sprintf( new_counter[1].word, "FOOTSHOTS^"); 
				    
				if(sprite[i].value2 == TACTIC_MENU_LASTMAN)   
    				sprintf( new_counter[1].word, "LAST MAN^");   
				 
				if(sprite[i].value2 == TACTIC_MENU_SCOPE)   
    				sprintf( new_counter[1].word, "SCOPE^");  
				 
				if(sprite[i].value2 == TACTIC_MENU_SHIELD)   
    				sprintf( new_counter[1].word, "SHIELD^");  
				 
				if(sprite[i].value2 == TACTIC_MENU_RAGE)   
    				sprintf( new_counter[1].word, "RAGE^");  
				 
				if(sprite[i].value2 == TACTIC_MENU_DASH)   
    				sprintf( new_counter[1].word, "DASH^");  
				 
				if(sprite[i].value2 == TACTIC_MENU_GODEYE)   
    				sprintf( new_counter[1].word, "GOD-EYE^");  
				 
				if(sprite[i].value2 == TACTIC_MENU_CLOAK)   
    				sprintf( new_counter[1].word, "CLOAK^");  
				 
				if(sprite[i].value2 == TACTIC_MENU_VAMPIRE)   
    				sprintf( new_counter[1].word, "VAMPIRE^");  
				 
				if(sprite[i].value2 == TACTIC_MENU_MARYJANE)   
    				sprintf( new_counter[1].word, "MARYJANE^");  
				 
				if(sprite[i].value2 == TACTIC_MENU_WISDOM)   
    				sprintf( new_counter[1].word, "WISDOM^");  
				 
				if(sprite[i].value2 == TACTIC_MENU_FINAL)   
    				sprintf( new_counter[1].word, "FINAL^");  
				 
				if(sprite[i].value2 == TACTIC_MENU_LAST)   
    				sprintf( new_counter[1].word, "LAST^");  

				// For left-sided messages, get longest line...
				if( new_counter[1].x >= sta2_left_of_screen) 
				{ 
					slongest_line = GetLongestLine(new_counter[1].word);  
							   
					new_counter[5].x = mouseX - 0.03f;   
					new_counter[1].x = new_counter[5].x - (slongest_line*0.0245f);  

				} 

				if(sprite[i].value2 == TACTIC_MENU_MOVEMENT) 
					sprintf( new_counter[3].word, "Press the $WASD$ keys to^move your unit in^battle mode.");
				if(sprite[i].value2 == TACTIC_MENU_PRIMARY) 
					sprintf( new_counter[3].word, "Press the $1$ key to^use your primary weapon.^Primary weapons have^multiple shots but deal^low damage.");
				if(sprite[i].value2 == TACTIC_MENU_SECONDARY) 
					sprintf( new_counter[3].word, "Press the $2$ key to^use your secondary weapon.^Secondary weapons have a^single shot but deal^high damage.");
				if(sprite[i].value2 == TACTIC_MENU_DEFEND) 
					sprintf( new_counter[3].word, "Press the $3$ key to^make a unit defend.^A defending unit will^shoot any moving targets.^Within shooting range.");
				if(sprite[i].value2 == TACTIC_MENU_EXTRA) 
					sprintf( new_counter[3].word, "Press the $4$ key to^use an extra ability.^Some weapon packs give extra^abilities which can be used^once every battle.");
				if(sprite[i].value2 == TACTIC_MENU_SPECIAL) 
					sprintf( new_counter[3].word, "Press the $5$ key to^use a special ability.^Some weapon packs give^special abilities which can^be used at any time in^battle.");
				if(sprite[i].value2 == TACTIC_MENU_CANCEL) 
					sprintf( new_counter[3].word, "Press the $6$ key to^view the current^area battle map.^");
				if(sprite[i].value2 == TACTIC_MENU_ENDTURN) 
					sprintf( new_counter[3].word, "Press the $7$ or $ESC$ key^to end a units turn.");

				if(sprite[i].value2 == TACTIC_MENU_COVER) 
					sprintf( new_counter[3].word, "Stand a unit next to^cover to take cover.^Cover reduces damage taken^by 50&");
				if(sprite[i].value2 == TACTIC_MENU_HEADSHOT) 
					sprintf( new_counter[3].word, "Click on an enemies head to^headshot.^Headshots do 50& more^damage but have less^chance to hit.");
				if(sprite[i].value2 == TACTIC_MENU_FOOTSHOT) 
					sprintf( new_counter[3].word, "Click on an enemies foot to^footshot.^Footshots stun the target^and reduce that units^movement for the rest^of the battle.");
				if(sprite[i].value2 == TACTIC_MENU_LASTMAN) 
					sprintf( new_counter[3].word, "When you$re down to only^one unit. Use cover whilst^defending to take out^multiple targets!");

				if(sprite[i].value2 == TACTIC_MENU_SCOPE)  
					sprintf( new_counter[3].word, "Increases accuracy by^50& when active.^Has a 20& chance to^miss.^");  
				if(sprite[i].value2 == TACTIC_MENU_SHIELD)  
					sprintf( new_counter[3].word, "Reduces damage taken^by 40& when active.^Has a 20& chance to^miss.^"); 
				if(sprite[i].value2 == TACTIC_MENU_RAGE)  
					sprintf( new_counter[3].word, "Increases damage dealt^by 30& when active.^Has a 20& chance to^miss.^"); 
				if(sprite[i].value2 == TACTIC_MENU_DASH)  
					sprintf( new_counter[3].word, "Increases movement by^50& when active.^Has a 20& chance to^miss.^"); 
				if(sprite[i].value2 == TACTIC_MENU_GODEYE)  
					sprintf( new_counter[3].word, "Increases accuracy to^99& when active.^Has a 33& chance to^miss.^"); 
				if(sprite[i].value2 == TACTIC_MENU_CLOAK)  
					sprintf( new_counter[3].word, "Makes unit invisible^when active except dogs.^Has a 25& chance to^miss.^"); 
				if(sprite[i].value2 == TACTIC_MENU_VAMPIRE)  
					sprintf( new_counter[3].word, "Converts 18& of damage^dealt to HP when active.^Has a 20& chance to^miss.^"); 
				if(sprite[i].value2 == TACTIC_MENU_MARYJANE)  
					sprintf( new_counter[3].word, "Regains 4& of total^HP when active every move.^Has a 20& chance to^miss.^"); 
				if(sprite[i].value2 == TACTIC_MENU_WISDOM)  
					sprintf( new_counter[3].word, "Increase XP gained by^50& when active.^Has a 20& chance to^miss.^"); 
				if(sprite[i].value2 == TACTIC_MENU_FINAL)   
					sprintf( new_counter[3].word, "Increases damage by 50&^accuracy decreases by 50&^when active.^Has a 20& chance to^miss.^"); 
				if(sprite[i].value2 == TACTIC_MENU_LAST)  
					sprintf( new_counter[3].word, "Deals 999 or 1 damage^when active.^Has a 20& chance to^miss.^"); 

			}

			// Turn off arrows if roster is too small etc...
			if(sta2_tactics_count < 7)     
			{    
				sprite[12].base_anim = 3;  
				Set_Sprite(12, sprite[12].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
			}
			else
			{ 
				sprite[12].base_anim = 2;  
				Set_Sprite(12, sprite[12].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
			}
			 
			// Turn off arrows if roster is too small etc...
			if(sta2_tactics_index == 0)       
			{ 
				sprite[11].base_anim = 1;   
				Set_Sprite(11, sprite[11].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
			}
			else  
			{
				sprite[11].base_anim = 0;  
				Set_Sprite(11, sprite[11].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
			}

				// Arrow left 
				if(sprite[11].alpha == 1.0)    
				if(sprite[11].base_anim != 1)
				if(( mouseX < (sprite[11].w + sprite[11].box_width) )
				&&( mouseX > sprite[11].w)                            
				&&( mouseY < (sprite[11].z + sprite[11].box_height) )
				&&( mouseY > sprite[11].z)) 
				if(mouseleft == true)
				{
					mouseleft = false;    

					if(sta2_tactics_index >= 1)
						sta2_tactics_index--;
				}
			  
				// Arrow right
				if(sprite[12].alpha == 1.0)       
				if(sprite[12].base_anim != 3)
				if(( mouseX < (sprite[12].w + sprite[12].box_width) )
				&&( mouseX > sprite[12].w)                            
				&&( mouseY < (sprite[12].z + sprite[12].box_height) )
				&&( mouseY > sprite[12].z)) 
				if(mouseleft == true)
				{
					mouseleft = false;   

					if(sta2_tactics_index <= (24))
						sta2_tactics_index++;
				} 



		} 


	}
	
    // ******************************************************************************//
    //                           10-0  (LOADING SCREEN)                              //
    // ******************************************************************************//

   // Title Screen Stuff...
   if(next_scene == false)
   if(episode == 10 && scene == 0)  
   {  

       episode = 0;   
       scene   = 0;  

       next_scene = true; 
   }       
	
    // ******************************************************************************//
    //                           1-15  (ADA CO POWER1)                               //
    // ******************************************************************************//

   // Title Screen Stuff...
   if(!mode) 
   if(next_scene == false)
   if(episode == 1 && scene == 15)  
   {  
		if(title_sequence == 0)  
		{ 
			 title_timer = (int)TimerGetTime()+5000;

			 title_sequence++;
		}

		if(title_sequence == 1)  
		{
             temp_speed = 0.0003f*(float)f_rate;

             sprite[1].x += temp_speed; 

		} 

		if(title_sequence == 1) 
		if((int)TimerGetTime() > title_timer)
		{
			scene = 16;
			episode = 1;

			next_scene = true;

			title_sequence++;
		}

   }   
	
    // ******************************************************************************//
    //                           1-16  (ADA CO POWER1)                               //
    // ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode) 
   if(next_scene == false) 
   if(episode == 1 && scene == 16)  
   {    
		if(title_sequence == 0) 
		{ 
			 title_timer = (int)TimerGetTime()+3500;

			 title_sequence++;
		} 

		if(title_sequence == 1) 
		{
             temp_speed = 0.0003f*(float)f_rate;

             sprite[7].x -= temp_speed; 
			 sprite[8].x -= temp_speed; 

		} 

		if(title_sequence == 1) 
		if((int)TimerGetTime() > title_timer)
		{
			scene = 1;
			episode = 1;

			next_scene = true;

			title_sequence++;
		}
   }   
  	
    // ******************************************************************************//
    //                           1-17  (Intro - Castle)                              //
    // ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode)  
   if(next_scene == false)
   if(episode == 1 && scene == 17)  
   {  

	    if(sta2_esc_pressed == true)   
		{
			sta2_esc_pressed = false;
			scene = 2;
			episode = 1;
			next_scene = true;
		}

		if(title_sequence == 0) 
		{ 
		//	 title_timer = (int)TimerGetTime()+5000;
			 
			 title_sequence++;
		} 

		if(title_sequence == 1)   
		{

             temp_speed = 0.00005f*(float)f_rate;

             sprite[4].x -= temp_speed; 

			camX -=  0.00018f*(float)f_rate; 
				 
			if(-camX > ((sprite[0].x + sprite[0].width) - 0.785f ) )
			{
			    camX = -((sprite[0].x + sprite[0].width) - 0.785f );  
				title_sequence++;
			} 

			if(-camX > ((sprite[0].x + sprite[0].width) - 1.3f ) ) 
			if(sprite[5].anim != 1)
			{  
				Set_Sprite(5, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
				sta2_exp_sfx = true;
			}   

			if(-camX > ((sprite[0].x + sprite[0].width) - 1.2f ) )
			if(sprite[6].anim != 1)  
			{ 
				Set_Sprite(6, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
				sta2_exp_sfx = true;  
			}  
			 
			if(-camX > ((sprite[0].x + sprite[0].width) - 1.1f ) )
			if(sprite[7].anim != 1)
			{
				Set_Sprite(7, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
				sta2_exp_sfx = true;
			}

			if(-camX > ((sprite[0].x + sprite[0].width) - 1.0f ) )
			if(sprite[8].anim != 1)
			{
				Set_Sprite(8, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
				sta2_exp_sfx = true;
			}


		}  

		if(title_sequence == 2)   
		{ 
			scene = 18; 
			episode = 1;

			next_scene = true;

		}

   }   
    // ******************************************************************************//
    //                           1-18  (ADA steals plans)                            //
    // ******************************************************************************//

   // Title Screen Stuff...
   if(!mode) 
   if(next_scene == false)
   if(episode == 1 && scene == 18)  
   {  

	    if(sta2_esc_pressed == true)   
		{
			sta2_esc_pressed = false;
			scene = 2;
			episode = 1;
			next_scene = true;
		}

		if(title_sequence == 0)  
		{ 
			 title_timer = (int)TimerGetTime()+5000;

			 title_sequence++;
		}
		 
		if(title_sequence == 1)  
		{
             temp_speed = 0.00035f*(float)f_rate;

             sprite[1].x += temp_speed; 
			 sprite[10].x += temp_speed; 
			 sprite[11].x += temp_speed; 

		} 

		if(title_sequence == 1) 
		if((int)TimerGetTime() > title_timer)
		{
			scene = 19;
			episode = 1;

			next_scene = true;

			title_sequence++;
		}

   }   

    // ******************************************************************************//
    //                           1-19  (Helmutt chasing)                             //
    // ******************************************************************************//

   // Title Screen Stuff...
   if(!mode) 
   if(next_scene == false)
   if(episode == 1 && scene == 19)  
   {  

	    if(sta2_esc_pressed == true)   
		{
			sta2_esc_pressed = false;
			scene = 2;
			episode = 1;
			next_scene = true;

		}
		if(title_sequence == 0)  
		{ 
			 title_timer = (int)TimerGetTime()+5000;

			 title_sequence++;
		}
		 
		if(title_sequence == 1)  
		{
             temp_speed = 0.00035f*(float)f_rate;

             sprite[1].x -= temp_speed; 
			 sprite[10].x -= temp_speed; 
			 sprite[11].x -= temp_speed; 
			 sprite[12].x -= temp_speed; 

		}  

		if(title_sequence == 1) 
		if((int)TimerGetTime() > title_timer)
		{
			scene = 20;
			episode = 1;

			next_scene = true;

			title_sequence++;
		}

   }   

    // ******************************************************************************//
    //                       1-20  (Helmutt chasing reverse)                         //
    // ******************************************************************************//

   // Title Screen Stuff...
   if(!mode) 
   if(next_scene == false)
   if(episode == 1 && scene == 20)  
   {  

	    if(sta2_esc_pressed == true)   
		{
			sta2_esc_pressed = false;
			scene = 2;
			episode = 1;
			next_scene = true;
		}

		if(title_sequence == 0)  
		{ 
			 title_timer = (int)TimerGetTime()+5000;

			 title_sequence++;
		}
		 
		if(title_sequence == 1)  
		{
             temp_speed = 0.00035f*(float)f_rate;

             sprite[1].x += temp_speed; 
			 sprite[10].x += temp_speed; 
			 sprite[11].x += temp_speed; 
			 sprite[12].x += temp_speed; 

		} 

		if(title_sequence == 1) 
		if((int)TimerGetTime() > title_timer)
		{
			scene = 2;
			episode = 1; 

			next_scene = true;

			title_sequence++;
		}

   }   
    // ******************************************************************************//
    //                                 1-29  (SCORE)                                 //
    // ******************************************************************************//
             
       // Title Screen Stuff...        
       if(!mode)      
       if(next_scene == false)     
       if(episode == 1 && scene == 29)       
       {       

		    if(sta2_yes_no_page == 0)
				Set_Sprite(3, 2, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Point Arrow 

			new_counter[15].alpha = 0.0f;
			 
			if(sta2_yes_no_active == true)      
			{ 
				 
				hud[3].alpha = 1.0f;  

				sta2_yes_no_active = true;  
				 
				if(sta2_yes_no_page == 0) 
				{
					new_counter[15].alpha = 1.0f;
					new_counter[15].x = hud[3].x + 0.06f;  
					new_counter[15].y =  hud[3].y + hud[3].height - 0.1f;
					new_counter[15].w = new_counter[15].x - 0.026f;   
					new_counter[15].z = new_counter[15].y - 0.015f;
					new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
					new_counter[15].box_height = new_counter[15].height - 0.015f;	
					sprintf(new_counter[15].word, "New layout^unlocked!"); 
				}

				new_counter[7].alpha = 1.0f;   

				new_counter[7].id = 0;  

				if(sta2_yes_no_page == 0) 
					sprintf(new_counter[7].word, "1. CONTINUE");  

				new_counter[7].x = hud[3].x + 0.06f;  
				new_counter[7].y =  hud[3].y + hud[3].height - 0.1f;
				new_counter[7].w = new_counter[7].x - 0.026f;   
				new_counter[7].z = new_counter[7].y - 0.015f;
				new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
				new_counter[7].box_height = new_counter[7].height - 0.015f;	 

			}
			else        
			{
				new_counter[7].alpha = 0.0f;
				new_counter[15].alpha = 0.0f;
				hud[3].alpha = 0.0f; 
			} 

	        if(title_sequence == 0)                   
            {  	 
				  
				sprite[2].alpha = 0.0f;

			    sprintf( new_counter[0].word, "3 : Back");   

			    new_counter[0].alpha = 0.0f;                         
			    new_counter[0].id = 0;    
		         
				if(screen_mode == SCREEN_1610_WIDESCREEN)
					new_counter[0].x = +0.42f;           
				else
					new_counter[0].x = +0.50f;           

			    new_counter[0].y = -0.34f;       	        
				     
				new_counter[0].w = new_counter[0].x - 0.026f;    
				new_counter[0].z = new_counter[0].y - 0.015f; 

				new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
				new_counter[0].box_height = new_counter[0].height - 0.015f;	

				new_counter[1].alpha = 1.0f;              
				new_counter[1].id = 0;  
		                    
				new_counter[1].x = -0.40f;         
				new_counter[1].y = 0.20f;       

				new_counter[1].w = new_counter[1].x - 0.026f;         
				new_counter[1].z = new_counter[1].y - 0.015f; 
			  
				new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
				new_counter[1].box_height = new_counter[1].height - 0.015f;	
			 
				sprintf( new_counter[1].word, "");  

				new_counter[2].alpha = 1.0f;                              
				new_counter[2].id = 0;         
		                
				new_counter[2].x = 0.35f;           
				new_counter[2].y = 0.20f;      
				 
				new_counter[2].w = new_counter[2].x - 0.026f;      
				new_counter[2].z = new_counter[2].y - 0.015f; 
			  
				new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
				new_counter[2].box_height = new_counter[2].height - 0.015f;	

				sta2_sector_score = sta2_sector*1000; 

				sta2_final_score = (sta2_enemies_defeated*100)+(sta2_gold_collected)+(sta2_sector_score)+(sta2_highest_level*100);
				sta2_tokens_earned = sta2_final_score/100;

				sta2_temp_stars_earned = sta2_final_score/12;   

				// Reload current layouts...
				for(int i = 0; i<10;i++)
					sta2_layouts[LAYOUT_ADA][i] = LAYOUT_LOCKED;
				for(int i = 0; i<10;i++)
					sta2_layouts[LAYOUT_MARIE][i] = LAYOUT_LOCKED; 
				for(int i = 0; i<10;i++)
					sta2_layouts[LAYOUT_ADELE][i] = LAYOUT_LOCKED;
				for(int i = 0; i<10;i++)
					sta2_layouts[LAYOUT_BELLA][i] = LAYOUT_LOCKED;

				if(sta2_ada_exp >= ADA_LAYOUT1_COST)
					sta2_layouts[LAYOUT_ADA][0] = LAYOUT_OPEN;
				if(sta2_ada_exp >= ADA_LAYOUT2_COST)
					sta2_layouts[LAYOUT_ADA][1] = LAYOUT_OPEN;
				if(sta2_ada_exp >= ADA_LAYOUT3_COST)
					sta2_layouts[LAYOUT_ADA][2] = LAYOUT_OPEN;
				if(sta2_ada_exp >= ADA_LAYOUT4_COST)
					sta2_layouts[LAYOUT_ADA][3] = LAYOUT_OPEN;
				if(sta2_ada_exp >= ADA_LAYOUT5_COST)
					sta2_layouts[LAYOUT_ADA][4] = LAYOUT_OPEN;
				if(sta2_ada_exp >= ADA_LAYOUT6_COST)
					sta2_layouts[LAYOUT_ADA][5] = LAYOUT_OPEN;

				if(sta2_marie_exp >= MARIE_LAYOUT1_COST)
					sta2_layouts[LAYOUT_MARIE][0] = LAYOUT_OPEN;
				if(sta2_marie_exp >= MARIE_LAYOUT2_COST)
					sta2_layouts[LAYOUT_MARIE][1] = LAYOUT_OPEN;
				if(sta2_marie_exp >= MARIE_LAYOUT3_COST)
					sta2_layouts[LAYOUT_MARIE][2] = LAYOUT_OPEN;
				if(sta2_marie_exp >= MARIE_LAYOUT4_COST)
					sta2_layouts[LAYOUT_MARIE][3] = LAYOUT_OPEN;
				if(sta2_marie_exp >= MARIE_LAYOUT5_COST)
					sta2_layouts[LAYOUT_MARIE][4] = LAYOUT_OPEN;
				if(sta2_marie_exp >= MARIE_LAYOUT6_COST)
					sta2_layouts[LAYOUT_MARIE][5] = LAYOUT_OPEN;

				if(sta2_adele_exp >= ADELE_LAYOUT1_COST)
					sta2_layouts[LAYOUT_ADELE][0] = LAYOUT_OPEN;
				if(sta2_adele_exp >= ADELE_LAYOUT2_COST)
					sta2_layouts[LAYOUT_ADELE][1] = LAYOUT_OPEN;
				if(sta2_adele_exp >= ADELE_LAYOUT3_COST)
					sta2_layouts[LAYOUT_ADELE][2] = LAYOUT_OPEN;
				if(sta2_adele_exp >= ADELE_LAYOUT4_COST)
					sta2_layouts[LAYOUT_ADELE][3] = LAYOUT_OPEN;
				if(sta2_adele_exp >= ADELE_LAYOUT5_COST)
					sta2_layouts[LAYOUT_ADELE][4] = LAYOUT_OPEN;
				if(sta2_adele_exp >= ADELE_LAYOUT6_COST)
					sta2_layouts[LAYOUT_ADELE][5] = LAYOUT_OPEN;

				if(sta2_bella_exp >= BELLA_LAYOUT1_COST)
					sta2_layouts[LAYOUT_BELLA][0] = LAYOUT_OPEN;
				if(sta2_bella_exp >= BELLA_LAYOUT2_COST)
					sta2_layouts[LAYOUT_BELLA][1] = LAYOUT_OPEN;
				if(sta2_bella_exp >= BELLA_LAYOUT3_COST)
					sta2_layouts[LAYOUT_BELLA][2] = LAYOUT_OPEN;
				if(sta2_bella_exp >= BELLA_LAYOUT4_COST)
					sta2_layouts[LAYOUT_BELLA][3] = LAYOUT_OPEN;
				if(sta2_bella_exp >= BELLA_LAYOUT5_COST)
					sta2_layouts[LAYOUT_BELLA][4] = LAYOUT_OPEN;
				if(sta2_bella_exp >= BELLA_LAYOUT6_COST)
					sta2_layouts[LAYOUT_BELLA][5] = LAYOUT_OPEN;

				// Add new Xp gains...
				if(sta2_co_type == STA2_CO_ADA) 
					sta2_ada_exp += sta2_temp_stars_earned;
				if(sta2_co_type == STA2_CO_MARIE)
					sta2_marie_exp += sta2_temp_stars_earned;
				if(sta2_co_type == STA2_CO_ADELE)
					sta2_adele_exp += sta2_temp_stars_earned;
				if(sta2_co_type == STA2_CO_BELLA)
					sta2_bella_exp += sta2_temp_stars_earned;

				// Check to see if new layout is unlocked...
				sta2_got_new_ada_layout = false;
				sta2_got_new_marie_layout = false; 
				sta2_got_new_adele_layout = false; 
				sta2_got_new_bella_layout = false; 

				if(sta2_co_type == LAYOUT_ADA)   
				{
					if(sta2_ada_exp >= ADA_LAYOUT1_COST && sta2_layouts[LAYOUT_ADA][0] != LAYOUT_OPEN)
						sta2_got_new_ada_layout = true;
					if(sta2_ada_exp >= ADA_LAYOUT2_COST && sta2_layouts[LAYOUT_ADA][1] != LAYOUT_OPEN)
						sta2_got_new_ada_layout = true;
					if(sta2_ada_exp >= ADA_LAYOUT3_COST && sta2_layouts[LAYOUT_ADA][2] != LAYOUT_OPEN)
						sta2_got_new_ada_layout = true;
					if(sta2_ada_exp >= ADA_LAYOUT4_COST && sta2_layouts[LAYOUT_ADA][3] != LAYOUT_OPEN)
						sta2_got_new_ada_layout = true;
					if(sta2_ada_exp >= ADA_LAYOUT5_COST && sta2_layouts[LAYOUT_ADA][4] != LAYOUT_OPEN)
						sta2_got_new_ada_layout = true;
					if(sta2_ada_exp >= ADA_LAYOUT6_COST && sta2_layouts[LAYOUT_ADA][5] != LAYOUT_OPEN)
						sta2_got_new_ada_layout = true;
				} 
				 
				if(sta2_co_type == LAYOUT_MARIE)  
				{
					if(sta2_ada_exp >= MARIE_LAYOUT1_COST && sta2_layouts[LAYOUT_MARIE][0] != LAYOUT_OPEN)
						sta2_got_new_marie_layout = true;
					if(sta2_ada_exp >= MARIE_LAYOUT2_COST && sta2_layouts[LAYOUT_MARIE][1] != LAYOUT_OPEN)
						sta2_got_new_marie_layout = true;
					if(sta2_ada_exp >= MARIE_LAYOUT3_COST && sta2_layouts[LAYOUT_MARIE][2] != LAYOUT_OPEN)
						sta2_got_new_marie_layout = true;
					if(sta2_ada_exp >= MARIE_LAYOUT4_COST && sta2_layouts[LAYOUT_MARIE][3] != LAYOUT_OPEN)
						sta2_got_new_marie_layout = true;
					if(sta2_ada_exp >= MARIE_LAYOUT5_COST && sta2_layouts[LAYOUT_MARIE][4] != LAYOUT_OPEN)
						sta2_got_new_marie_layout = true;
					if(sta2_ada_exp >= MARIE_LAYOUT6_COST && sta2_layouts[LAYOUT_MARIE][5] != LAYOUT_OPEN)
						sta2_got_new_marie_layout = true;
				} 
				 
				if(sta2_co_type == LAYOUT_ADELE)  
				{
					if(sta2_ada_exp >= ADELE_LAYOUT1_COST && sta2_layouts[LAYOUT_ADELE][0] != LAYOUT_OPEN)
						sta2_got_new_adele_layout = true;
					if(sta2_ada_exp >= ADELE_LAYOUT2_COST && sta2_layouts[LAYOUT_ADELE][1] != LAYOUT_OPEN)
						sta2_got_new_adele_layout = true;
					if(sta2_ada_exp >= ADELE_LAYOUT3_COST && sta2_layouts[LAYOUT_ADELE][2] != LAYOUT_OPEN)
						sta2_got_new_adele_layout = true;
					if(sta2_ada_exp >= ADELE_LAYOUT4_COST && sta2_layouts[LAYOUT_ADELE][3] != LAYOUT_OPEN)
						sta2_got_new_adele_layout = true;
					if(sta2_ada_exp >= ADELE_LAYOUT5_COST && sta2_layouts[LAYOUT_ADELE][4] != LAYOUT_OPEN)
						sta2_got_new_adele_layout = true;
					if(sta2_ada_exp >= ADELE_LAYOUT6_COST && sta2_layouts[LAYOUT_ADELE][5] != LAYOUT_OPEN)
						sta2_got_new_adele_layout = true;
				} 
				 
				if(sta2_co_type == LAYOUT_BELLA)   
				{
					if(sta2_ada_exp >= BELLA_LAYOUT1_COST && sta2_layouts[LAYOUT_BELLA][0] != LAYOUT_OPEN)
						sta2_got_new_bella_layout = true;
					if(sta2_ada_exp >= BELLA_LAYOUT2_COST && sta2_layouts[LAYOUT_BELLA][1] != LAYOUT_OPEN)
						sta2_got_new_bella_layout = true;
					if(sta2_ada_exp >= BELLA_LAYOUT3_COST && sta2_layouts[LAYOUT_BELLA][2] != LAYOUT_OPEN)
						sta2_got_new_bella_layout = true;
					if(sta2_ada_exp >= BELLA_LAYOUT4_COST && sta2_layouts[LAYOUT_BELLA][3] != LAYOUT_OPEN)
						sta2_got_new_bella_layout = true;
					if(sta2_ada_exp >= BELLA_LAYOUT5_COST && sta2_layouts[LAYOUT_BELLA][4] != LAYOUT_OPEN)
						sta2_got_new_bella_layout = true;
					if(sta2_ada_exp >= BELLA_LAYOUT6_COST && sta2_layouts[LAYOUT_BELLA][5] != LAYOUT_OPEN)
						sta2_got_new_bella_layout = true;
				}  
				 
			    sprintf( new_counter[2].word, "");   

				sta2_tokens += sta2_tokens_earned;

				sta2_score_inc = 0.0f;
				sta2_old_score_inc = 0.0f;
				sta2_score_inc_timer=0;

				title_timer = (int)TimerGetTime() + 1000; 
			 
				title_sequence++;  
			}  
	        if(title_sequence == 1)                          
            {    
				
				// Start adding up scores etc...
				if((int)TimerGetTime() > title_timer)  
				{         
		
					if(start_sequence != 7)
					if((int)TimerGetTime() > sta2_score_inc_timer)
					if(sta2_score_inc != sta2_old_score_inc) 
					{
						sta2_score_inc_timer = (int)TimerGetTime() + 100;
						stop_sfx = true;
					}

					sta2_old_score_inc = sta2_score_inc; 

					if(start_sequence == 7) 
					{
						if(sta2_co_type == STA2_CO_ADA)
							sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^TOKENS EARNED^ADA STARS EARNED", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
						if(sta2_co_type == STA2_CO_MARIE)
							sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^TOKENS EARNED^MARIE STARS EARNED", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
						if(sta2_co_type == STA2_CO_ADELE)
							sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^TOKENS EARNED^ADELE STARS EARNED", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
						if(sta2_co_type == STA2_CO_BELLA)
							sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^TOKENS EARNED^BELLA STARS EARNED", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  

						if(sta2_score_inc == 0.0f)                   
							stamp_sfx = true;  
						  
						sta2_score_inc = 0.1f;            
						        
						sprite[2].alpha = 1.0f;      
						  
						Set_Sprite(2, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

						if(sta2_final_score >= 4000)
							Set_Sprite(2, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
						if(sta2_final_score >= 10000)
							Set_Sprite(2, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
						if(sta2_final_score >= 20000)
							Set_Sprite(2, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
						if(sta2_final_score >= 25000)
							Set_Sprite(2, 4, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
						if(sta2_final_score >= 33000)
							Set_Sprite(2, 5, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

						sprintf( new_counter[2].word, "%i^%i^%i^%i^^%i^º%i^¹%i", sta2_enemies_defeated*100, sta2_gold_collected, sta2_sector_score, sta2_highest_level*100, sta2_final_score, sta2_tokens_earned, sta2_temp_stars_earned);
						 
						new_counter[0].alpha = 1.0f; 

						#if IS_FULL_STEAM == 1  
	 
						if (STEAM_ACTIVE == true)  
						{
							Upload_Scores();
						}       

						#endif 


						start_sequence++;

					}
					if(start_sequence == 6)
					{
						if(sta2_co_type == STA2_CO_ADA)
							sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^TOKENS EARNED^ADA STARS EARNED", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
						if(sta2_co_type == STA2_CO_MARIE)
							sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^TOKENS EARNED^MARIE STARS EARNED", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
						if(sta2_co_type == STA2_CO_ADELE)
							sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^TOKENS EARNED^ADELE STARS EARNED", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
						if(sta2_co_type == STA2_CO_BELLA)
							sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^TOKENS EARNED^BELLA STARS EARNED", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  

						sprintf( new_counter[2].word, "%i^%i^%i^%i^^%i^º%i^¹%i", sta2_enemies_defeated*100, sta2_gold_collected, sta2_sector_score, sta2_highest_level*100, sta2_final_score, sta2_tokens_earned, (int)sta2_score_inc);
						  
						if(sta2_score_inc == 0.0f)        
							stamp_sfx = true;    
						 
						temp_speed = GetIncSpeed(sta2_score_inc);

						sta2_score_inc += temp_speed*(float)f_rate;
						  
						if((int)sta2_score_inc >= sta2_temp_stars_earned)        
						{
							cash_sfx = true;   
							if(sta2_temp_stars_earned == 0) 
								title_timer = (int)TimerGetTime() + 1000;
							else
								title_timer = (int)TimerGetTime() + 500;

							if(sta2_co_type == STA2_CO_ADA)
								sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^TOKENS EARNED^ADA STARS EARNED", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
							if(sta2_co_type == STA2_CO_MARIE)
								sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^TOKENS EARNED^MARIE STARS EARNED", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
							if(sta2_co_type == STA2_CO_ADELE)
								sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^TOKENS EARNED^ADELE STARS EARNED", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
							if(sta2_co_type == STA2_CO_BELLA)
								sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^TOKENS EARNED^BELLA STARS EARNED", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
  
							sprintf( new_counter[2].word, "%i^%i^%i^%i^^%i^º%i^¹%i", sta2_enemies_defeated*100, sta2_gold_collected, sta2_sector_score, sta2_highest_level*100, sta2_final_score, sta2_tokens_earned, sta2_temp_stars_earned);
					
							sta2_score_inc = 0.0f;
							start_sequence++; 
						}
					}   

					if(start_sequence == 5) 
					{
						sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^TOKENS EARNED", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
						sprintf( new_counter[2].word, "%i^%i^%i^%i^^%i^º%i", sta2_enemies_defeated*100, sta2_gold_collected, sta2_sector_score, sta2_highest_level*100, sta2_final_score, (int)sta2_score_inc);
						 
						if(sta2_score_inc == 0.0f)    
							stamp_sfx = true;  

						temp_speed = GetIncSpeed(sta2_score_inc);

						sta2_score_inc += temp_speed*(float)f_rate; 

						if((int)sta2_score_inc >= sta2_tokens_earned)  
						{
							cash_sfx = true;  
							if(sta2_tokens_earned == 0)
								title_timer = (int)TimerGetTime() + 1000;
							else
								title_timer = (int)TimerGetTime() + 500;

							sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^TOKENS EARNED", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
							sprintf( new_counter[2].word, "%i^%i^%i^%i^^%i^º%i", sta2_enemies_defeated*100, sta2_gold_collected, sta2_sector_score, sta2_highest_level*100, sta2_final_score, sta2_tokens_earned);
				
							sta2_score_inc = 0.0f;
							start_sequence++;
						}
					}
					if(start_sequence == 4)
					{
						sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
						sprintf( new_counter[2].word, "%i^%i^%i^%i^^%i", sta2_enemies_defeated*100, sta2_gold_collected, sta2_sector_score, sta2_highest_level*100, (int)sta2_score_inc);

						if(sta2_score_inc == 0.0f)
							stamp_sfx = true;
						 
						temp_speed = GetIncSpeed(sta2_score_inc);

						sta2_score_inc += temp_speed*(float)f_rate;  

						if((int)sta2_score_inc >= sta2_final_score)  
						{
							if(sta2_final_score == 0)
								title_timer = (int)TimerGetTime() + 1000;
							else
								title_timer = (int)TimerGetTime() + 500;

							sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^^FINAL SCORE^", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
							sprintf( new_counter[2].word, "%i^%i^%i^%i^^%i", sta2_enemies_defeated*100, sta2_gold_collected, sta2_sector_score, sta2_highest_level*100, sta2_final_score);

							sta2_score_inc = 0.0f;
							start_sequence++;
						} 
					}
					if(start_sequence == 3)
					{
						sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
						sprintf( new_counter[2].word, "%i^%i^%i^%i", sta2_enemies_defeated*100, sta2_gold_collected, sta2_sector_score, (int)sta2_score_inc);

						if(sta2_score_inc == 0.0f)
							stamp_sfx = true;

						temp_speed = GetIncSpeed(sta2_score_inc);

						sta2_score_inc += temp_speed*(float)f_rate; 

						if((int)sta2_score_inc >= sta2_highest_level*100)
						{
							if(sta2_highest_level == 0)
								title_timer = (int)TimerGetTime() + 1000;
							else
								title_timer = (int)TimerGetTime() + 500;

							sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^HIGHEST LEVEL x (%i)^", sta2_enemies_defeated, sta2_gold_collected, sta2_sector, sta2_highest_level);  
							sprintf( new_counter[2].word, "%i^%i^%i^%i", sta2_enemies_defeated*100, sta2_gold_collected, sta2_sector_score, sta2_highest_level*100);

							sta2_score_inc = 0.0f;
							start_sequence++;
						}
					}
					if(start_sequence == 2)
					{
						sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^", sta2_enemies_defeated, sta2_gold_collected, sta2_sector);  
						sprintf( new_counter[2].word, "%i^%i^%i", sta2_enemies_defeated*100, sta2_gold_collected, (int)sta2_score_inc);
						
						if(sta2_score_inc == 0.0f)
							stamp_sfx = true;

						temp_speed = GetIncSpeed(sta2_score_inc);

						sta2_score_inc += temp_speed*(float)f_rate; 

						if((int)sta2_score_inc >= sta2_sector*1000)
						{
							if(sta2_sector == 0)
								title_timer = (int)TimerGetTime() + 1000;
							else
								title_timer = (int)TimerGetTime() + 500;

							sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^HIGHEST SECTOR x (%i)^", sta2_enemies_defeated, sta2_gold_collected, sta2_sector);  
							sprintf( new_counter[2].word, "%i^%i^%i", sta2_enemies_defeated*100, sta2_gold_collected, sta2_sector_score);
					
							sta2_score_inc = 0.0f;
							start_sequence++;
						}
					} 
					if(start_sequence == 1)
					{
						sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^", sta2_enemies_defeated, sta2_gold_collected);  
						sprintf( new_counter[2].word, "%i^%i", sta2_enemies_defeated*100, (int)sta2_score_inc);

						if(sta2_score_inc == 0.0f) 
							stamp_sfx = true;

						temp_speed = GetIncSpeed(sta2_score_inc); 

						sta2_score_inc += temp_speed*(float)f_rate; 

						if((int)sta2_score_inc >= sta2_gold_collected)
						{
							if(sta2_gold_collected == 0)
								title_timer = (int)TimerGetTime() + 1000;
							else
								title_timer = (int)TimerGetTime() + 500;

							sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)^GOLD COLLECTED X (%i)^", sta2_enemies_defeated, sta2_gold_collected);  
							sprintf( new_counter[2].word, "%i^%i", sta2_enemies_defeated*100, sta2_gold_collected);

							sta2_score_inc = 0.0f;
							start_sequence++;
						}  
					} 
					if(start_sequence == 0)
					{
						sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)", sta2_enemies_defeated);  
						sprintf( new_counter[2].word, "%i", (int)sta2_score_inc);

						if(sta2_score_inc == 0.0f) 
							stamp_sfx = true;
						
						temp_speed = GetIncSpeed(sta2_score_inc);

						sta2_score_inc += temp_speed*(float)f_rate; 

						if((int)sta2_score_inc >= sta2_enemies_defeated*100)
						{
							if(sta2_enemies_defeated == 0)
								title_timer = (int)TimerGetTime() + 1000;
							else
								title_timer = (int)TimerGetTime() + 500;

							sprintf( new_counter[1].word, "ENEMIES DEFEATED X (%i)", sta2_enemies_defeated);  
							sprintf( new_counter[2].word, "%i", sta2_enemies_defeated*100);

							sta2_score_inc = 0.0f;
							start_sequence++;
						}
					}


				}


				new_counter[0].id = 0; 
				new_counter[7].id = 0;
				 
				testX = hud_mouseX - (-camX);                                                     
				testY = hud_mouseY - (-camY);    

				// YES...
				if(sta2_yes_no_active == true) 
				if(new_counter[7].id != 4) // Greyed out...
				if(new_counter[7].alpha == 1.0f)
				if(( testX < (new_counter[7].w + new_counter[7].box_width) )
				&&( testX > new_counter[7].w)                            
				&&( testY < (new_counter[7].z + new_counter[7].box_height) )
				&&( testY > new_counter[7].z) || sta2_1_pressed == true)   
				{ 
					new_counter[7].id = 2;     

					if(mouseleft == true || DX_SHOOT == true || sta2_1_pressed == true) 
					{  
						sta2_1_pressed = false;
						mouseleft = false;       
						DX_SHOOT = false;     
						 
						if(sta2_yes_no_page == 0)
						{ 
							sta2_yes_no_active = false;  
							sta2_yes_no_page = 0;
						}

					} 
				}  

				// Back button.. 
				if(new_counter[0].alpha == 1.0f)
				if(( testX < (new_counter[0].w + new_counter[0].box_width) )
				&&( testX > new_counter[0].w)                            
				&&( testY < (new_counter[0].z + new_counter[0].box_height) )
				&&( testY > new_counter[0].z) || sta2_3_pressed == true)   
				{ 
					new_counter[0].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_3_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_3_pressed = false;   

						if(sta2_got_new_ada_layout == true
						|| sta2_got_new_marie_layout == true
						|| sta2_got_new_adele_layout == true
						|| sta2_got_new_bella_layout == true
						|| sta2_got_normal_mode == true
						|| sta2_got_hard_mode == true
						|| sta2_got_bella == true)
						{
							episode = 1;  
							scene = 37;
						}
						else
						{
							episode = 0;  
							scene = 1;
						}

						next_scene = true;

						title_sequence++;

					} 
				}  

			}

	   }

    // ******************************************************************************//
    //                                 1-27  (LAYOUT)                                //
    // ******************************************************************************//
             
       // Title Screen Stuff...        
       if(!mode)      
       if(next_scene == false)     
       if(episode == 1 && scene == 27)         
       {   
	 
			if(sta2_layout_page == LAYOUT_ADA) 
				sprintf( new_counter[13].word, "ADA^¹ %i", sta2_ada_exp);
			if(sta2_layout_page == LAYOUT_MARIE)
				sprintf( new_counter[13].word, "MARIE^¹ %i", sta2_marie_exp);
			if(sta2_layout_page == LAYOUT_ADELE)
				sprintf( new_counter[13].word, "ADELE^¹ %i", sta2_adele_exp);
			if(sta2_layout_page == LAYOUT_BELLA)
				sprintf( new_counter[13].word, "BELLA^¹ %i", sta2_bella_exp);
				 
			for(int i = 0; i<10;i++)
				sta2_layouts[LAYOUT_ADA][i] = LAYOUT_LOCKED;
			for(int i = 0; i<10;i++)
				sta2_layouts[LAYOUT_MARIE][i] = LAYOUT_LOCKED;
			for(int i = 0; i<10;i++)
				sta2_layouts[LAYOUT_ADELE][i] = LAYOUT_LOCKED;
			for(int i = 0; i<10;i++)
				sta2_layouts[LAYOUT_BELLA][i] = LAYOUT_LOCKED;

			if(sta2_layout_page == LAYOUT_ADA)  
			{
				if(sta2_ada_exp >= ADA_LAYOUT1_COST)
					sta2_layouts[LAYOUT_ADA][0] = LAYOUT_OPEN;
				if(sta2_ada_exp >= ADA_LAYOUT2_COST)
					sta2_layouts[LAYOUT_ADA][1] = LAYOUT_OPEN;
				if(sta2_ada_exp >= ADA_LAYOUT3_COST)
					sta2_layouts[LAYOUT_ADA][2] = LAYOUT_OPEN;
				if(sta2_ada_exp >= ADA_LAYOUT4_COST)
					sta2_layouts[LAYOUT_ADA][3] = LAYOUT_OPEN;
				if(sta2_ada_exp >= ADA_LAYOUT5_COST)
					sta2_layouts[LAYOUT_ADA][4] = LAYOUT_OPEN;
				if(sta2_ada_exp >= ADA_LAYOUT6_COST)
					sta2_layouts[LAYOUT_ADA][5] = LAYOUT_OPEN;
			}

			if(sta2_layout_page == LAYOUT_MARIE) 
			{
				if(sta2_marie_exp >= MARIE_LAYOUT1_COST)
					sta2_layouts[LAYOUT_MARIE][0] = LAYOUT_OPEN;
				if(sta2_marie_exp >= MARIE_LAYOUT2_COST)
					sta2_layouts[LAYOUT_MARIE][1] = LAYOUT_OPEN;
				if(sta2_marie_exp >= MARIE_LAYOUT3_COST)
					sta2_layouts[LAYOUT_MARIE][2] = LAYOUT_OPEN;
				if(sta2_marie_exp >= MARIE_LAYOUT4_COST)
					sta2_layouts[LAYOUT_MARIE][3] = LAYOUT_OPEN;
				if(sta2_marie_exp >= MARIE_LAYOUT5_COST)
					sta2_layouts[LAYOUT_MARIE][4] = LAYOUT_OPEN;
				if(sta2_marie_exp >= MARIE_LAYOUT6_COST)
					sta2_layouts[LAYOUT_MARIE][5] = LAYOUT_OPEN;
			}

			if(sta2_layout_page == LAYOUT_ADELE) 
			{
				if(sta2_adele_exp >= ADELE_LAYOUT1_COST)
					sta2_layouts[LAYOUT_ADELE][0] = LAYOUT_OPEN;
				if(sta2_adele_exp >= ADELE_LAYOUT2_COST)
					sta2_layouts[LAYOUT_ADELE][1] = LAYOUT_OPEN;
				if(sta2_adele_exp >= ADELE_LAYOUT3_COST)
					sta2_layouts[LAYOUT_ADELE][2] = LAYOUT_OPEN;
				if(sta2_adele_exp >= ADELE_LAYOUT4_COST)
					sta2_layouts[LAYOUT_ADELE][3] = LAYOUT_OPEN;
				if(sta2_adele_exp >= ADELE_LAYOUT5_COST)
					sta2_layouts[LAYOUT_ADELE][4] = LAYOUT_OPEN;
				if(sta2_adele_exp >= ADELE_LAYOUT6_COST)
					sta2_layouts[LAYOUT_ADELE][5] = LAYOUT_OPEN;
			}

			if(sta2_layout_page == LAYOUT_BELLA)    
			{ 
				if(sta2_bella_exp >= BELLA_LAYOUT1_COST)
					sta2_layouts[LAYOUT_BELLA][0] = LAYOUT_OPEN;
				if(sta2_bella_exp >= BELLA_LAYOUT2_COST)
					sta2_layouts[LAYOUT_BELLA][1] = LAYOUT_OPEN;
				if(sta2_bella_exp >= BELLA_LAYOUT3_COST)
					sta2_layouts[LAYOUT_BELLA][2] = LAYOUT_OPEN;
				if(sta2_bella_exp >= BELLA_LAYOUT4_COST)
					sta2_layouts[LAYOUT_BELLA][3] = LAYOUT_OPEN;
				if(sta2_bella_exp >= BELLA_LAYOUT5_COST)
					sta2_layouts[LAYOUT_BELLA][4] = LAYOUT_OPEN;
				if(sta2_bella_exp >= BELLA_LAYOUT6_COST)
					sta2_layouts[LAYOUT_BELLA][5] = LAYOUT_OPEN;
			}

	        if(title_sequence == 0)                                 
            {  	              


				new_counter[13].alpha = 1.0f;                  
			    new_counter[13].id = 0;  
		          
				if(screen_mode == SCREEN_1610_WIDESCREEN)
					new_counter[13].x = -0.60f;        
				else  
					new_counter[13].x = -0.64f;         

		        new_counter[13].y = 0.36f;  	       

			    new_counter[13].w = new_counter[13].x - 0.026f;   
			    new_counter[13].z = new_counter[13].y - 0.015f;

			    new_counter[13].box_width = strlen(new_counter[13].word)   *  0.026f;
			    new_counter[13].box_height = new_counter[13].height - 0.015f;

				if(sta2_has_marie == 0)
				{
					sprite[9].base_anim = 8;
					Set_Sprite(9, sprite[9].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}
				else
				{     
					sprite[9].base_anim = 2;
					Set_Sprite(9, sprite[9].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}
				if(sta2_has_adele == 0)
				{
					sprite[10].base_anim = 8;
					Set_Sprite(10, sprite[10].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}
				else
				{
					sprite[10].base_anim = 4;
					Set_Sprite(10, sprite[10].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}
				if(sta2_has_bella == 0)
				{
					sprite[13].base_anim = 8;
					Set_Sprite(13, sprite[13].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}
				else
				{ 
					sprite[13].base_anim = 6;
					Set_Sprite(13, sprite[13].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				}


			    sta2_squad_count=0;     
				sta2_roster_count=0;  

				sta2_layout_page = LAYOUT_ADA; 

				for(int j = 0;j< STA2_PACKS_LIMIT;j++)     
				{  
					sta2_pack[j].type = STA2_VOID;     
					sta2_pack[j].rank = 0; 
					sta2_pack[j].equipped = false;
					sta2_pack[j].extra = PACK_EXTRA_NONE;
					sta2_pack[j].extra_charge = 0;
					sta2_pack[j].special = PACK_SPECIAL_NONE;
					sta2_pack[j].special_charge = 0;
					sta2_pack[j].active1 = PACK_ACTIVE_NONE;
					sta2_pack[j].active2 = PACK_ACTIVE_NONE;
					sta2_pack[j].active3 = PACK_ACTIVE_NONE;
					sta2_pack[j].active4 = PACK_ACTIVE_NONE;

					sprintf(sta2_pack[j].string, "NONE"); 
				}  
				 
				// Reset the squad...  
				for(int i =0;i<50;i++) 
				{ 
					sta2_squad[i].health = 0;      
					sta2_squad[i].xp = 0;   
					sta2_squad[i].rank = 0;   
					sta2_squad[i].type = STA2_VOID; 
					sta2_squad[i].wp = 0;    
					sprintf(sta2_squad[i].string, "");         
				}  

			    sprintf( new_counter[0].word, "3 : Back");    

			    new_counter[0].alpha = 1.0f;                         
			    new_counter[0].id = 0;      
		          
				if(screen_mode == SCREEN_1610_WIDESCREEN)  
					new_counter[0].x = +0.44f;           
				else
					new_counter[0].x = +0.50f;  

			    new_counter[0].y = -0.34f;       	        
				     
				new_counter[0].w = new_counter[0].x - 0.026f;   
				new_counter[0].z = new_counter[0].y - 0.015f; 

				new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
				new_counter[0].box_height = new_counter[0].height - 0.015f;	
 
			    new_counter[2].alpha = 1.0f;          
			    new_counter[2].id = 4;      
		        
			    new_counter[2].x = -0.35f;            
			    new_counter[2].y = +0.01f; 	       
				 
			    sprintf( new_counter[2].word, "Click on a squad layout^to start the game with."); 

				title_sequence++; 
			}   

			index = 0;  

			sta2_co_type = sta2_layout_page; 

			for(int i = 1;i<7;i++)  
			{
				if(sta2_layouts[sta2_layout_page][index] == LAYOUT_LOCKED)
					sprite[i].anim = 0;
				else 
				{ 
					if(sta2_layout_page == LAYOUT_ADA)
						sprite[i].anim = i;
					if(sta2_layout_page == LAYOUT_MARIE)
						sprite[i].anim = 6+i;
					if(sta2_layout_page == LAYOUT_ADELE) 
						sprite[i].anim = 12+i;
					if(sta2_layout_page == LAYOUT_BELLA)
						sprite[i].anim = 18+i;
				}

				index++;

			}

	        if(title_sequence == 1)                         
            {  
				 
				sprintf( new_counter[2].word, "Click on a squad layout^to start the game with.");

				new_counter[0].id = 0; 
				 
				testX = hud_mouseX - (-camX);                                                     
				testY = hud_mouseY - (-camY);   

				// Back button..
				if(new_counter[0].alpha == 1.0f)
				if(( testX < (new_counter[0].w + new_counter[0].box_width) )
				&&( testX > new_counter[0].w)                            
				&&( testY < (new_counter[0].z + new_counter[0].box_height) )
				&&( testY > new_counter[0].z) || sta2_3_pressed == true)   
				{ 
					new_counter[0].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_3_pressed == true) 
					{  
						 
						mouseleft = false;        
						DX_SHOOT = false;  
						sta2_3_pressed = false;       

						episode = 0;   
						scene = 1;

						next_scene = true;  
						   
					} 
				}      
				 
				new_counter[4].alpha = 0.0f;
				new_counter[5].alpha = 0.0f;

				sprintf( new_counter[4].word, ""); 
				sprintf( new_counter[5].word, "");

				for(int i = 1;i<7;i++)  
				{ 
 
					if(sprite[i].alpha == 1.0)    
					if(( mouseX < (sprite[i].w + sprite[i].box_width) )
					&&( mouseX > sprite[i].w)                            
					&&( mouseY < (sprite[i].z + sprite[i].box_height) )
					&&( mouseY > sprite[i].z)) 
					{   

						new_counter[4].alpha = 1.0f;                
					   
						new_counter[4].x = mouseX + 0.13f;                  
						new_counter[4].y = mouseY;     
					 
						new_counter[5].alpha = 1.0f;               
					    
						new_counter[5].x = mouseX + 0.1f;                       
						new_counter[5].y = mouseY;    

						sprintf( new_counter[5].word, "@");  

						if(sta2_layouts[sta2_layout_page][i-1] == LAYOUT_LOCKED)
						{
							sprintf( new_counter[2].word, "This layout is locked!");
							sprintf( new_counter[4].word, "LOCKED!^");  
							  
							if(sta2_layout_page == LAYOUT_ADA)       
							{
								if(i == 2){sprintf( new_counter[2].word, "This layout requires %i^ADA STARS to unlock!", ADA_LAYOUT2_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^ADA STARS^", ADA_LAYOUT2_COST);}
								if(i == 3){sprintf( new_counter[2].word, "This layout requires %i^ADA STARS to unlock!", ADA_LAYOUT3_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^ADA STARS^", ADA_LAYOUT3_COST);}
								if(i == 4){sprintf( new_counter[2].word, "This layout requires %i^ADA STARS to unlock!", ADA_LAYOUT4_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^ADA STARS^", ADA_LAYOUT4_COST);}
								if(i == 5){sprintf( new_counter[2].word, "This layout requires %i^ADA STARS to unlock!", ADA_LAYOUT5_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^ADA STARS^", ADA_LAYOUT5_COST);}
								if(i == 6){sprintf( new_counter[2].word, "This layout requires %i^ADA STARS to unlock!", ADA_LAYOUT6_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^ADA STARS^", ADA_LAYOUT6_COST);}
							} 
							if(sta2_layout_page == LAYOUT_MARIE) 
							{
								if(i == 2){sprintf( new_counter[2].word, "This layout requires %i^MARIE STARS to unlock!", MARIE_LAYOUT2_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^MARIE STARS^", MARIE_LAYOUT2_COST);}
								if(i == 3){sprintf( new_counter[2].word, "This layout requires %i^MARIE STARS to unlock!", MARIE_LAYOUT3_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^MARIE STARS^", MARIE_LAYOUT3_COST);}
								if(i == 4){sprintf( new_counter[2].word, "This layout requires %i^MARIE STARS to unlock!", MARIE_LAYOUT4_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^MARIE STARS^", MARIE_LAYOUT4_COST);}
								if(i == 5){sprintf( new_counter[2].word, "This layout requires %i^MARIE STARS to unlock!", MARIE_LAYOUT5_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^MARIE STARS^", MARIE_LAYOUT5_COST);}
								if(i == 6){sprintf( new_counter[2].word, "This layout requires %i^MARIE STARS to unlock!", MARIE_LAYOUT6_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^MARIE STARS^", MARIE_LAYOUT6_COST);}
							}
							if(sta2_layout_page == LAYOUT_ADELE) 
							{
								if(i == 2){sprintf( new_counter[2].word, "This layout requires %i^ADELE STARS to unlock!", ADELE_LAYOUT2_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^ADELE STARS^", ADELE_LAYOUT2_COST);}
								if(i == 3){sprintf( new_counter[2].word, "This layout requires %i^ADELE STARS to unlock!", ADELE_LAYOUT3_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^ADELE STARS^", ADELE_LAYOUT3_COST);}
								if(i == 4){sprintf( new_counter[2].word, "This layout requires %i^ADELE STARS to unlock!", ADELE_LAYOUT4_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^ADELE STARS^", ADELE_LAYOUT4_COST);}
								if(i == 5){sprintf( new_counter[2].word, "This layout requires %i^ADELE STARS to unlock!", ADELE_LAYOUT5_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^ADELE STARS^", ADELE_LAYOUT5_COST);}
								if(i == 6){sprintf( new_counter[2].word, "This layout requires %i^ADELE STARS to unlock!", ADELE_LAYOUT6_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^ADELE STARS^", ADELE_LAYOUT6_COST);}
							}
							if(sta2_layout_page == LAYOUT_BELLA) 
							{
								if(i == 2){sprintf( new_counter[2].word, "This layout requires %i^BELLA STARS to unlock!", BELLA_LAYOUT2_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^BELLA STARS^", BELLA_LAYOUT2_COST);}
								if(i == 3){sprintf( new_counter[2].word, "This layout requires %i^BELLA STARS to unlock!", BELLA_LAYOUT3_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^BELLA STARS^", BELLA_LAYOUT3_COST);}
								if(i == 4){sprintf( new_counter[2].word, "This layout requires %i^BELLA STARS to unlock!", BELLA_LAYOUT4_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^BELLA STARS^", BELLA_LAYOUT4_COST);}
								if(i == 5){sprintf( new_counter[2].word, "This layout requires %i^BELLA STARS to unlock!", BELLA_LAYOUT5_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^BELLA STARS^", BELLA_LAYOUT5_COST);}
								if(i == 6){sprintf( new_counter[2].word, "This layout requires %i^BELLA STARS to unlock!", BELLA_LAYOUT6_COST);sprintf( new_counter[4].word, "REQUIRES^¹ %i^BELLA STARS^", BELLA_LAYOUT6_COST);}
							}
						} 
						  
						if(i==1)  
						if(sta2_layouts[sta2_layout_page][i-1] == LAYOUT_OPEN)
						{
	
							if(sta2_layout_page == LAYOUT_ADA)  
							{
								sprintf( new_counter[4].word, "SELECT^ADA FROST^");

								sprintf( new_counter[2].word, "Scouts^Ada Lvl2^Scout Lvl1^Scout Lvl1^--------^Gold : 45^Food : 240^");

							}
							if(sta2_layout_page == LAYOUT_MARIE)  
							{
								  
								sprintf( new_counter[4].word, "SELECT^MARIE FLOCKHEART^"); 

								sprintf( new_counter[2].word, "Scout^Marie Lvl2^Scout Lvl1^Scout Lvl1^--------^Gold : 45^Food : 240^");

							}     
							if(sta2_layout_page == LAYOUT_ADELE)   
							{
								  
								sprintf( new_counter[4].word, "SELECT^ADELE LEVINE^");

								sprintf( new_counter[2].word, "Scout^Adele Lvl2^Scout Lvl1^Scout Lvl1^--------^Gold : 45^Food : 240^");

							}                
							if(sta2_layout_page == LAYOUT_BELLA)   
							{  
								  
								sprintf( new_counter[4].word, "SELECT^BELLA LARZ^");

								sprintf( new_counter[2].word, "Scout^Bella Lvl2^Scout Lvl1^Scout Lvl1^--------^Gold : 45^Food : 240^");
								 
							}    
							                
							if(mouseleft == true && sta2_layout_page == LAYOUT_ADA)  
							{      
								      
								sta2_gold = 45;  // 45  
								sta2_food = 240;  // 240

								// Add some units to the roster...   
								sta2_squad[sta2_squad_count].xp = 0; 
								sta2_squad[sta2_squad_count].face = 0; // 1+rand()%10
								sta2_squad[sta2_squad_count].deployed = false;   
								sta2_squad[sta2_squad_count].rank = 2;    // 2
								sta2_squad[sta2_squad_count].type = STA2_CO; 
								sta2_squad[sta2_squad_count].wp = 0; 
								sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
								sprintf(sta2_squad[sta2_squad_count].string, "Ada"); 
								sta2_squad_count++;    
				 
								sta2_squad[sta2_squad_count].xp = 0; 
								sta2_squad[sta2_squad_count].face = 1+rand()%10;    
								sta2_squad[sta2_squad_count].deployed = false; 
								sta2_squad[sta2_squad_count].rank = 1;   
								sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
								sta2_squad[sta2_squad_count].wp = 1; 
								sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
								sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
								sta2_squad_count++;   
				  
								sta2_squad[sta2_squad_count].xp = 0;   
								sta2_squad[sta2_squad_count].face = 1+rand()%10;
								sta2_squad[sta2_squad_count].deployed = false; 
								sta2_squad[sta2_squad_count].rank = 1;  
								sta2_squad[sta2_squad_count].type = STA2_SCOUT;
								sta2_squad[sta2_squad_count].wp = 2; 
								sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
								sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
								sta2_squad_count++;  
				   
								sta2_pack[0].type = STA2_SCOUT;                                  
								sta2_pack[0].rank = 1;         
								sta2_pack[0].equipped = true;  
								sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
								sta2_pack[0].extra_charge = 0; 
								sta2_pack[0].special = PACK_SPECIAL_SCOPE;   // PACK_EXTRA_MEDKIT
								sta2_pack[0].special_charge = 0;
								sprintf(sta2_pack[0].string, "SCOUT PACK");   
				  
								sta2_pack[1].type = STA2_SCOUT;         
								sta2_pack[1].rank = 1;  
								sta2_pack[1].equipped = true; 
								sta2_pack[1].extra = PACK_EXTRA_GRENADE;   // PACK_EXTRA_GRENADE
								sta2_pack[1].extra_charge = 1;
								sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
								sta2_pack[1].special_charge = 0;
								sprintf(sta2_pack[1].string, "SCOUT PACK");   

								sta2_pack[2].type = STA2_SCOUT;      
								sta2_pack[2].rank = 1;     
								sta2_pack[2].equipped = true; 
								sta2_pack[2].extra = PACK_EXTRA_GRENADE;  
								sta2_pack[2].extra_charge = 1;
								sta2_pack[2].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
								sta2_pack[2].special_charge = 0;
								sprintf(sta2_pack[2].string, "SCOUT PACK"); 

								title_sequence++;

							}// mouseleft == true && sta2_layout_page == LAYOUT_ADA  

							if(mouseleft == true && sta2_layout_page == LAYOUT_MARIE) 
							{  

								sta2_gold = 45;   
								sta2_food = 240; 

								// Add some units to the roster...   
								sta2_squad[sta2_squad_count].xp = 0; 
								sta2_squad[sta2_squad_count].face = 38; // 1+rand()%10
								sta2_squad[sta2_squad_count].deployed = false;  
								sta2_squad[sta2_squad_count].rank = 2;   
								sta2_squad[sta2_squad_count].type = STA2_CO;
								sta2_squad[sta2_squad_count].wp = 0; 
								sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
								sprintf(sta2_squad[sta2_squad_count].string, "Marie"); 
								sta2_squad_count++;   
				 
								sta2_squad[sta2_squad_count].xp = 0; 
								sta2_squad[sta2_squad_count].face = 1+rand()%10;    
								sta2_squad[sta2_squad_count].deployed = false; 
								sta2_squad[sta2_squad_count].rank = 1;   
								sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
								sta2_squad[sta2_squad_count].wp = 1; 
								sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
								sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
								sta2_squad_count++;   
				 
								sta2_squad[sta2_squad_count].xp = 0; 
								sta2_squad[sta2_squad_count].face = 1+rand()%10;    
								sta2_squad[sta2_squad_count].deployed = false; 
								sta2_squad[sta2_squad_count].rank = 1;   
								sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
								sta2_squad[sta2_squad_count].wp = 2; 
								sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
								sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
								sta2_squad_count++;   

								sta2_pack[0].type = STA2_HEAVY;                
								sta2_pack[0].rank = 1;       
								sta2_pack[0].equipped = true;  
								sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
								sta2_pack[0].extra_charge = 0;  
								sta2_pack[0].special = PACK_SPECIAL_SHIELD;   // PACK_EXTRA_MEDKIT
								sta2_pack[0].special_charge = 0;
								sprintf(sta2_pack[0].string, "HEAVY PACK");   
				 
								sta2_pack[1].type = STA2_SCOUT;       
								sta2_pack[1].rank = 1;  
								sta2_pack[1].equipped = true; 
								sta2_pack[1].extra = PACK_EXTRA_GRENADE;   // PACK_EXTRA_GRENADE
								sta2_pack[1].extra_charge = 1;
								sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
								sta2_pack[1].special_charge = 0;
								sprintf(sta2_pack[1].string, "SCOUT PACK");  
				 
								sta2_pack[2].type = STA2_SCOUT;       
								sta2_pack[2].rank = 1;  
								sta2_pack[2].equipped = true; 
								sta2_pack[2].extra = PACK_EXTRA_GRENADE;   // PACK_EXTRA_GRENADE
								sta2_pack[2].extra_charge = 1;
								sta2_pack[2].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
								sta2_pack[2].special_charge = 0;
								sprintf(sta2_pack[2].string, "SCOUT PACK");  

								title_sequence++;

							}// mouseleft == true && sta2_layout_page == LAYOUT_MARIE

							if(mouseleft == true && sta2_layout_page == LAYOUT_ADELE) 
							{  
								     
								sta2_gold = 45;   
								sta2_food = 240; 

								// Add some units to the roster...   
								sta2_squad[sta2_squad_count].xp = 0; 
								sta2_squad[sta2_squad_count].face = 43; // 1+rand()%10
								sta2_squad[sta2_squad_count].deployed = false;  
								sta2_squad[sta2_squad_count].rank = 2;   
								sta2_squad[sta2_squad_count].type = STA2_CO;
								sta2_squad[sta2_squad_count].wp = 0; 
								sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
								sprintf(sta2_squad[sta2_squad_count].string, "Adele"); 
								sta2_squad_count++;   
				 
								sta2_squad[sta2_squad_count].xp = 0; 
								sta2_squad[sta2_squad_count].face = 1+rand()%10;    
								sta2_squad[sta2_squad_count].deployed = false; 
								sta2_squad[sta2_squad_count].rank = 1;   
								sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
								sta2_squad[sta2_squad_count].wp = 1; 
								sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
								sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
								sta2_squad_count++;   
				 
								sta2_squad[sta2_squad_count].xp = 0; 
								sta2_squad[sta2_squad_count].face = 1+rand()%10;    
								sta2_squad[sta2_squad_count].deployed = false; 
								sta2_squad[sta2_squad_count].rank = 1;   
								sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
								sta2_squad[sta2_squad_count].wp = 2; 
								sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
								sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
								sta2_squad_count++;   

								sta2_pack[0].type = STA2_SNIPER;                
								sta2_pack[0].rank = 1;       
								sta2_pack[0].equipped = true;  
								sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
								sta2_pack[0].extra_charge = 0;  
								sta2_pack[0].special = PACK_SPECIAL_DUMDUM;   // PACK_EXTRA_MEDKIT
								sta2_pack[0].special_charge = 0;
								sprintf(sta2_pack[0].string, "SNIPER PACK");   
				 
								sta2_pack[1].type = STA2_SCOUT;       
								sta2_pack[1].rank = 1;  
								sta2_pack[1].equipped = true; 
								sta2_pack[1].extra = PACK_EXTRA_GRENADE;   // PACK_EXTRA_GRENADE
								sta2_pack[1].extra_charge = 1;
								sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
								sta2_pack[1].special_charge = 0;
								sprintf(sta2_pack[1].string, "SCOUT PACK");  
				 
								sta2_pack[2].type = STA2_SCOUT;       
								sta2_pack[2].rank = 1;  
								sta2_pack[2].equipped = true; 
								sta2_pack[2].extra = PACK_EXTRA_GRENADE;   // PACK_EXTRA_GRENADE
								sta2_pack[2].extra_charge = 1;
								sta2_pack[2].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
								sta2_pack[2].special_charge = 0;
								sprintf(sta2_pack[2].string, "SCOUT PACK");  

								title_sequence++;

							}// mouseleft == true && sta2_layout_page == LAYOUT_ADELE

							if(mouseleft == true && sta2_layout_page == LAYOUT_BELLA) 
							{   
								     
								sta2_gold = 45;        
								sta2_food = 240;    

								// Add some units to the roster...   
								sta2_squad[sta2_squad_count].xp = 0; 
								sta2_squad[sta2_squad_count].face = 44; // 1+rand()%10
								sta2_squad[sta2_squad_count].deployed = false;  
								sta2_squad[sta2_squad_count].rank = 2;   
								sta2_squad[sta2_squad_count].type = STA2_CO;
								sta2_squad[sta2_squad_count].wp = 0; 
								sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
								sprintf(sta2_squad[sta2_squad_count].string, "Bella"); 
								sta2_squad_count++;   
				 
								sta2_squad[sta2_squad_count].xp = 0; 
								sta2_squad[sta2_squad_count].face = 1+rand()%10;    
								sta2_squad[sta2_squad_count].deployed = false; 
								sta2_squad[sta2_squad_count].rank = 1;   
								sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
								sta2_squad[sta2_squad_count].wp = 1; 
								sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
								sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
								sta2_squad_count++;   
				 
								sta2_squad[sta2_squad_count].xp = 0;  
								sta2_squad[sta2_squad_count].face = 1+rand()%10;    
								sta2_squad[sta2_squad_count].deployed = false; 
								sta2_squad[sta2_squad_count].rank = 1;   
								sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
								sta2_squad[sta2_squad_count].wp = 1; 
								sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
								sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
								sta2_squad_count++;  

								sta2_pack[0].type = STA2_MORTAR;                   
								sta2_pack[0].rank = 1;       
								sta2_pack[0].equipped = true;  
								sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
								sta2_pack[0].extra_charge = 0;  
								sta2_pack[0].special = PACK_SPECIAL_VAMPIRE;   // PACK_EXTRA_MEDKIT
								sta2_pack[0].special_charge = 0;
								sprintf(sta2_pack[0].string, "MORTAR PACK");   
				  
								sta2_pack[1].type = STA2_SCOUT;             
								sta2_pack[1].rank = 1;   
								sta2_pack[1].equipped = true; 
								sta2_pack[1].extra = PACK_EXTRA_GRENADE;   // PACK_EXTRA_GRENADE
								sta2_pack[1].extra_charge = 1;
								sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
								sta2_pack[1].special_charge = 0;
								sprintf(sta2_pack[1].string, "SCOUT PACK");  
				 
								sta2_pack[2].type = STA2_SCOUT;          
								sta2_pack[2].rank = 1;   
								sta2_pack[2].equipped = true; 
								sta2_pack[2].extra = PACK_EXTRA_GRENADE;   // PACK_EXTRA_GRENADE
								sta2_pack[2].extra_charge = 1;
								sta2_pack[2].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
								sta2_pack[2].special_charge = 0;
								sprintf(sta2_pack[2].string, "SCOUT PACK"); 

								title_sequence++;                 

							}// mouseleft == true && sta2_layout_page == LAYOUT_BELLA

						} // sta2_layouts[sta2_layout_page][i-1] == LAYOUT_OPEN) 

						if(i==2) 
						if(sta2_layouts[sta2_layout_page][i-1] == LAYOUT_OPEN)
						{
	
							if(sta2_layout_page == LAYOUT_ADA)  
							{
								sprintf( new_counter[4].word, "SELECT^ADA FROST^");

								sprintf( new_counter[2].word, "Heavy^Ada Lvl2^Heavy Lvl1^--------^--------^Gold : 60^Food : 280^");
							}
							if(sta2_layout_page == LAYOUT_MARIE)  
							{
								  
								sprintf( new_counter[4].word, "SELECT^MARIE FLOCKHEART^");

								sprintf( new_counter[2].word, "Heavy^Marie Lvl2^Heavy Lvl1^--------^--------^Gold : 60^Food : 280^");

							}  
							if(sta2_layout_page == LAYOUT_ADELE)  
							{
								  
								sprintf( new_counter[4].word, "SELECT^ADELE LEVINE^");

								sprintf( new_counter[2].word, "Heavy^Adele Lvl2^Heavy Lvl1^--------^--------^Gold : 60^Food : 280^");

							}  
							if(sta2_layout_page == LAYOUT_BELLA)  
							{
								  
								sprintf( new_counter[4].word, "SELECT^BELLA LARZ^");

								sprintf( new_counter[2].word, "Heavy^Bella Lvl2^Heavy Lvl1^--------^--------^Gold : 60^Food : 280^");

							}  

							if(mouseleft == true) 
							{
								 
								sta2_gold = 60;
								sta2_food = 280;

								if(sta2_layout_page == LAYOUT_ADA)
								{								 
									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 0; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Ada"); 
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0;  
									sta2_squad[sta2_squad_count].face = 31;     
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_HEAVY; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				   
									sta2_pack[0].type = STA2_SCOUT;                 
									sta2_pack[0].rank = 1;        
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 0; 
									sta2_pack[0].special = PACK_SPECIAL_MAGICNET;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "SCOUT PACK");   
				 
									sta2_pack[1].type = STA2_HEAVY;       
									sta2_pack[1].rank = 1;  
									sta2_pack[1].equipped = true; 
									sta2_pack[1].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_GRENADE
									sta2_pack[1].extra_charge = 0;
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "HEAVY PACK");   
								}
								if(sta2_layout_page == LAYOUT_MARIE)
								{								 
									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 38; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Marie"); 
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0;  
									sta2_squad[sta2_squad_count].face = 31;     
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_HEAVY; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				   
									sta2_pack[0].type = STA2_HEAVY;                 
									sta2_pack[0].rank = 1;        
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 0; 
									sta2_pack[0].special = PACK_SPECIAL_SHIELD;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "HEAVY PACK");   
				 
									sta2_pack[1].type = STA2_HEAVY;       
									sta2_pack[1].rank = 1;  
									sta2_pack[1].equipped = true; 
									sta2_pack[1].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_GRENADE
									sta2_pack[1].extra_charge = 0;
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "HEAVY PACK");   
								}
								if(sta2_layout_page == LAYOUT_ADELE)
								{								  
									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 43; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Adele"); 
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0;  
									sta2_squad[sta2_squad_count].face = 31;     
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_HEAVY; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				   
									sta2_pack[0].type = STA2_SNIPER;                 
									sta2_pack[0].rank = 1;        
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 0; 
									sta2_pack[0].special = PACK_SPECIAL_DUMDUM;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "SNIPER PACK");   
				 
									sta2_pack[1].type = STA2_HEAVY;       
									sta2_pack[1].rank = 1;  
									sta2_pack[1].equipped = true; 
									sta2_pack[1].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_GRENADE
									sta2_pack[1].extra_charge = 0;
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "HEAVY PACK");   
								}
								if(sta2_layout_page == LAYOUT_BELLA)
								{								 
									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 44; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Bella"); 
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0;  
									sta2_squad[sta2_squad_count].face = 31;     
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_HEAVY; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				   
									sta2_pack[0].type = STA2_MORTAR;                 
									sta2_pack[0].rank = 1;         
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 0; 
									sta2_pack[0].special = PACK_SPECIAL_VAMPIRE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "MORTAR PACK");   
				 
									sta2_pack[1].type = STA2_HEAVY;        
									sta2_pack[1].rank = 1;  
									sta2_pack[1].equipped = true; 
									sta2_pack[1].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_GRENADE
									sta2_pack[1].extra_charge = 0;
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "HEAVY PACK");   
								}

								title_sequence++;  
							}
						} 
						if(i==3)  
						if(sta2_layouts[sta2_layout_page][i-1] == LAYOUT_OPEN)
						{ 
	 
							if(sta2_layout_page == LAYOUT_ADA)  
							{ 
								sprintf( new_counter[4].word, "SELECT^ADA FROST^");

								sprintf( new_counter[2].word, "Solo^Ada Lvl2^--------^--------^--------^Gold : 180^Food : 320^");

							}
							if(sta2_layout_page == LAYOUT_MARIE)  
							{
								  
								sprintf( new_counter[4].word, "SELECT^MARIE FLOCKHEART^");

								sprintf( new_counter[2].word, "Solo^Marie Lvl2^--------^--------^--------^Gold : 180^Food : 320^");

							}   
							if(sta2_layout_page == LAYOUT_ADELE)  
							{
								  
								sprintf( new_counter[4].word, "SELECT^ADELE LEVINE^");

								sprintf( new_counter[2].word, "Solo^Adele Lvl2^--------^--------^--------^Gold : 180^Food : 320^");

							}   
							if(sta2_layout_page == LAYOUT_BELLA)  
							{
								   
								sprintf( new_counter[4].word, "SELECT^BELLA LARZ^");

								sprintf( new_counter[2].word, "Solo^Bella Lvl2^--------^--------^--------^Gold : 180^Food : 320^");

							}   

							if(mouseleft == true) 
							{      
								 
								sta2_gold = 180; // 180
								sta2_food = 320;

								if(sta2_layout_page == LAYOUT_ADA)
								{

									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 0; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Ada"); 
									sta2_squad_count++;    
				  
									sta2_pack[0].type = STA2_SCOUT;                
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_MEDKIT;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 1; 
									sta2_pack[0].special = PACK_SPECIAL_SCOPE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "SCOUT PACK");  
									 

								}
								if(sta2_layout_page == LAYOUT_MARIE)
								{ 

									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 38; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Marie"); 
									sta2_squad_count++;    
				  
									sta2_pack[0].type = STA2_HEAVY;                   
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_MEDKIT;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 1; 
									sta2_pack[0].special = PACK_SPECIAL_SHIELD;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "HEAVY PACK");  


								}
								if(sta2_layout_page == LAYOUT_ADELE)
								{

									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 43; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Adele"); 
									sta2_squad_count++;    
				  
									sta2_pack[0].type = STA2_SNIPER;                
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_MEDKIT;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 1; 
									sta2_pack[0].special = PACK_SPECIAL_DUMDUM;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "SNIPER PACK");  

									 
								}
								if(sta2_layout_page == LAYOUT_BELLA)
								{

									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 44; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Bella"); 
									sta2_squad_count++;    
				  
									sta2_pack[0].type = STA2_MORTAR;                
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_MEDKIT;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 1; 
									sta2_pack[0].special = PACK_SPECIAL_VAMPIRE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "MORTAR PACK");  


								}



								title_sequence++;
							}
						} 
						if(i==4)   
						if(sta2_layouts[sta2_layout_page][i-1] == LAYOUT_OPEN)
						{
							if(sta2_layout_page == LAYOUT_ADA)  
							{
								sprintf( new_counter[4].word, "SELECT^ADA FROST^");

								sprintf( new_counter[2].word, "Fours^Ada Lvl2^Scout Lvl1^Scout Lvl1^Scout Lvl1^Gold : 10^Food : 240");

							}
							if(sta2_layout_page == LAYOUT_MARIE)  
							{ 
								sprintf( new_counter[4].word, "SELECT^MARIE FLOCKHEART^");

								sprintf( new_counter[2].word, "Fours^Marie Lvl2^Scout Lvl1^Scout Lvl1^Scout Lvl1^Gold : 10^Food : 240");

							}
							if(sta2_layout_page == LAYOUT_ADELE)  
							{
								sprintf( new_counter[4].word, "SELECT^ADELE LEVINE^");

								sprintf( new_counter[2].word, "Fours^Adele Lvl2^Scout Lvl1^Scout Lvl1^Scout Lvl1^Gold : 10^Food : 240");

							}
							if(sta2_layout_page == LAYOUT_BELLA)  
							{
								sprintf( new_counter[4].word, "SELECT^BELLA LARZ^");

								sprintf( new_counter[2].word, "Fours^Bella Lvl2^Scout Lvl1^Scout Lvl1^Scout Lvl1^Gold : 10^Food : 240");

							}

							if(mouseleft == true)   
							{ 

								sta2_gold = 10;  
								sta2_food = 240; 

								if(sta2_layout_page == LAYOUT_ADA)
								{

									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 0; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Ada"); 
									sta2_squad_count++;    
				 
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 1+rand()%10;    
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;         
				 
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 1+rand()%10;    
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
									sta2_squad[sta2_squad_count].wp = 2; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 1+rand()%10;    
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SCOUT;  
									sta2_squad[sta2_squad_count].wp = 3; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				 
									sta2_pack[0].type = STA2_SCOUT;                 
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 1; 
									sta2_pack[0].special = PACK_SPECIAL_SCOPE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "SCOUT PACK");   
				  
									sta2_pack[1].type = STA2_SCOUT;                 
									sta2_pack[1].rank = 1;       
									sta2_pack[1].equipped = true;  
									sta2_pack[1].extra = PACK_EXTRA_MEDKIT;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].extra_charge = 1; 
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "SCOUT PACK"); 
				  
									sta2_pack[2].type = STA2_SCOUT;                
									sta2_pack[2].rank = 1;       
									sta2_pack[2].equipped = true;  
									sta2_pack[2].extra = PACK_EXTRA_GRENADE;   // PACK_EXTRA_MEDKIT
									sta2_pack[2].extra_charge = 1; 
									sta2_pack[2].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[2].special_charge = 0;
									sprintf(sta2_pack[2].string, "SCOUT PACK"); 
				   
									sta2_pack[3].type = STA2_SCOUT;                
									sta2_pack[3].rank = 1;       
									sta2_pack[3].equipped = true;  
									sta2_pack[3].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[3].extra_charge = 1; 
									sta2_pack[3].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[3].special_charge = 0;
									sprintf(sta2_pack[3].string, "SCOUT PACK"); 

									 
								}

								if(sta2_layout_page == LAYOUT_MARIE)
								{

									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 38; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Marie"); 
									sta2_squad_count++;    
				 
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 1+rand()%10;    
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;         
				 
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 1+rand()%10;    
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
									sta2_squad[sta2_squad_count].wp = 2; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 1+rand()%10;    
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SCOUT;  
									sta2_squad[sta2_squad_count].wp = 3; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				 
									sta2_pack[0].type = STA2_HEAVY;                 
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 1; 
									sta2_pack[0].special = PACK_SPECIAL_SHIELD;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "HEAVY PACK");   
				  
									sta2_pack[1].type = STA2_SCOUT;                 
									sta2_pack[1].rank = 1;       
									sta2_pack[1].equipped = true;  
									sta2_pack[1].extra = PACK_EXTRA_MEDKIT;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].extra_charge = 1; 
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "SCOUT PACK"); 
				  
									sta2_pack[2].type = STA2_SCOUT;                
									sta2_pack[2].rank = 1;       
									sta2_pack[2].equipped = true;  
									sta2_pack[2].extra = PACK_EXTRA_GRENADE;   // PACK_EXTRA_MEDKIT
									sta2_pack[2].extra_charge = 1; 
									sta2_pack[2].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[2].special_charge = 0;
									sprintf(sta2_pack[2].string, "SCOUT PACK"); 
				   
									sta2_pack[3].type = STA2_SCOUT;                
									sta2_pack[3].rank = 1;       
									sta2_pack[3].equipped = true;  
									sta2_pack[3].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[3].extra_charge = 1; 
									sta2_pack[3].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[3].special_charge = 0;
									sprintf(sta2_pack[3].string, "SCOUT PACK"); 

									 
								}

								if(sta2_layout_page == LAYOUT_ADELE)
								{

									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 43; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Adele"); 
									sta2_squad_count++;    
				 
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 1+rand()%10;    
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;         
				 
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 1+rand()%10;    
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
									sta2_squad[sta2_squad_count].wp = 2; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 1+rand()%10;    
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SCOUT;  
									sta2_squad[sta2_squad_count].wp = 3; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				 
									sta2_pack[0].type = STA2_SNIPER;                 
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 1; 
									sta2_pack[0].special = PACK_SPECIAL_DUMDUM;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "SNIPER PACK");   
				  
									sta2_pack[1].type = STA2_SCOUT;                 
									sta2_pack[1].rank = 1;       
									sta2_pack[1].equipped = true;  
									sta2_pack[1].extra = PACK_EXTRA_MEDKIT;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].extra_charge = 1; 
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "SCOUT PACK"); 
				  
									sta2_pack[2].type = STA2_SCOUT;                
									sta2_pack[2].rank = 1;       
									sta2_pack[2].equipped = true;  
									sta2_pack[2].extra = PACK_EXTRA_GRENADE;   // PACK_EXTRA_MEDKIT
									sta2_pack[2].extra_charge = 1; 
									sta2_pack[2].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[2].special_charge = 0;
									sprintf(sta2_pack[2].string, "SCOUT PACK"); 
				   
									sta2_pack[3].type = STA2_SCOUT;                
									sta2_pack[3].rank = 1;       
									sta2_pack[3].equipped = true;  
									sta2_pack[3].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[3].extra_charge = 1; 
									sta2_pack[3].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[3].special_charge = 0;
									sprintf(sta2_pack[3].string, "SCOUT PACK"); 

									 
								}

								if(sta2_layout_page == LAYOUT_BELLA)
								{

									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 44; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Bella"); 
									sta2_squad_count++;    
				  
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 1+rand()%10;    
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;         
				  
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 1+rand()%10;    
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SCOUT; 
									sta2_squad[sta2_squad_count].wp = 2; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 1+rand()%10;    
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SCOUT;  
									sta2_squad[sta2_squad_count].wp = 3; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				 
									sta2_pack[0].type = STA2_MORTAR;                 
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 1; 
									sta2_pack[0].special = PACK_SPECIAL_VAMPIRE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "MORTAR PACK");   
				  
									sta2_pack[1].type = STA2_SCOUT;                 
									sta2_pack[1].rank = 1;       
									sta2_pack[1].equipped = true;  
									sta2_pack[1].extra = PACK_EXTRA_MEDKIT;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].extra_charge = 1; 
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "SCOUT PACK"); 
				  
									sta2_pack[2].type = STA2_SCOUT;                
									sta2_pack[2].rank = 1;       
									sta2_pack[2].equipped = true;  
									sta2_pack[2].extra = PACK_EXTRA_GRENADE;   // PACK_EXTRA_MEDKIT
									sta2_pack[2].extra_charge = 1; 
									sta2_pack[2].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[2].special_charge = 0;
									sprintf(sta2_pack[2].string, "SCOUT PACK"); 
				   
									sta2_pack[3].type = STA2_SCOUT;                
									sta2_pack[3].rank = 1;       
									sta2_pack[3].equipped = true;  
									sta2_pack[3].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[3].extra_charge = 1; 
									sta2_pack[3].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[3].special_charge = 0;
									sprintf(sta2_pack[3].string, "SCOUT PACK"); 

									 
								}

								title_sequence++;
								 
							}
						}
						if(i==5) 
						if(sta2_layouts[sta2_layout_page][i-1] == LAYOUT_OPEN)
						{
							if(sta2_layout_page == LAYOUT_ADA)  
							{
								sprintf( new_counter[4].word, "SELECT^ADA FROST^");

								sprintf( new_counter[2].word, "Sniper^Ada Lvl2^Sniper Lvl1^--------^--------^Gold : 60^Food : 320^");

							}
							if(sta2_layout_page == LAYOUT_MARIE)   
							{
								sprintf( new_counter[4].word, "SELECT^MARIE FLOCKHEART^");

								sprintf( new_counter[2].word, "Sniper^Marie Lvl2^Sniper Lvl1^--------^--------^Gold : 60^Food : 320^");

							}
							if(sta2_layout_page == LAYOUT_ADELE)  
							{
								sprintf( new_counter[4].word, "SELECT^ADELE LEVINE^");

								sprintf( new_counter[2].word, "Sniper^Adele Lvl2^Sniper Lvl1^--------^--------^Gold : 60^Food : 320^");

							}
							if(sta2_layout_page == LAYOUT_BELLA)  
							{
								sprintf( new_counter[4].word, "SELECT^Bella Larz^");

								sprintf( new_counter[2].word, "Sniper^Bella Lvl2^Sniper Lvl1^--------^--------^Gold : 60^Food : 320^");

							}

							if(mouseleft == true)
							{

								sta2_gold = 60;
								sta2_food = 280;

								if(sta2_layout_page == LAYOUT_ADA)
								{								 
									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 0; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Ada"); 
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0;  
									sta2_squad[sta2_squad_count].face = 29;     
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SNIPER; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				  
									sta2_pack[0].type = STA2_SCOUT;                
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 0; 
									sta2_pack[0].special = PACK_SPECIAL_SCOPE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "SCOUT PACK");   
				 
									sta2_pack[1].type = STA2_SNIPER;       
									sta2_pack[1].rank = 1;  
									sta2_pack[1].equipped = true; 
									sta2_pack[1].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_GRENADE
									sta2_pack[1].extra_charge = 0;
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "SNIPER PACK");   
								}

								if(sta2_layout_page == LAYOUT_MARIE)
								{								 
									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 38; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Marie"); 
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0;  
									sta2_squad[sta2_squad_count].face = 29;     
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SNIPER; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				  
									sta2_pack[0].type = STA2_HEAVY;                
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 0; 
									sta2_pack[0].special = PACK_SPECIAL_SHIELD;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "HEAVY PACK");   
				 
									sta2_pack[1].type = STA2_SNIPER;       
									sta2_pack[1].rank = 1;  
									sta2_pack[1].equipped = true; 
									sta2_pack[1].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_GRENADE
									sta2_pack[1].extra_charge = 0;
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "SNIPER PACK");   
								}

								if(sta2_layout_page == LAYOUT_ADELE)
								{								 
									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 43; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Adele"); 
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0;  
									sta2_squad[sta2_squad_count].face = 29;     
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SNIPER; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				  
									sta2_pack[0].type = STA2_SNIPER;                
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 0; 
									sta2_pack[0].special = PACK_SPECIAL_DUMDUM;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "SNIPER PACK");   
				 
									sta2_pack[1].type = STA2_SNIPER;       
									sta2_pack[1].rank = 1;  
									sta2_pack[1].equipped = true; 
									sta2_pack[1].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_GRENADE
									sta2_pack[1].extra_charge = 0;
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "SNIPER PACK");   
								}

								if(sta2_layout_page == LAYOUT_BELLA)
								{								 
									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 44; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Bella"); 
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0;  
									sta2_squad[sta2_squad_count].face = 29;     
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_SNIPER; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				  
									sta2_pack[0].type = STA2_MORTAR;                
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 0; 
									sta2_pack[0].special = PACK_SPECIAL_VAMPIRE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "MORTAR PACK");   
				 
									sta2_pack[1].type = STA2_SNIPER;       
									sta2_pack[1].rank = 1;  
									sta2_pack[1].equipped = true; 
									sta2_pack[1].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_GRENADE
									sta2_pack[1].extra_charge = 0;
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "SNIPER PACK");   
								}

								title_sequence++; 
							}
						}   
						if(i==6)
						if(sta2_layouts[sta2_layout_page][i-1] == LAYOUT_OPEN)
						{
							if(sta2_layout_page == LAYOUT_ADA)  
							{
								sprintf( new_counter[4].word, "SELECT^ADA FROST^");

								sprintf( new_counter[2].word, "Mortar^Ada Lvl2^Mortar Lvl1^--------^--------^Gold : 60^Food : 320^");

							}
							if(sta2_layout_page == LAYOUT_MARIE)   
							{
								sprintf( new_counter[4].word, "SELECT^MARIE FLOCKHEART^");

								sprintf( new_counter[2].word, "Mortar^Marie Lvl2^Mortar Lvl1^--------^--------^Gold : 60^Food : 320^");

							}
							if(sta2_layout_page == LAYOUT_ADELE)  
							{
								sprintf( new_counter[4].word, "SELECT^ADELE LEVINE^");

								sprintf( new_counter[2].word, "Mortar^Adele Lvl2^Mortar Lvl1^--------^--------^Gold : 60^Food : 320^");

							}
							if(sta2_layout_page == LAYOUT_BELLA)  
							{
								sprintf( new_counter[4].word, "SELECT^BELLA LARZ^");

								sprintf( new_counter[2].word, "Mortar^Bella Lvl2^Mortar Lvl1^--------^--------^Gold : 60^Food : 320^");

							}

							if(mouseleft == true)
							{ 

								sta2_gold = 60;
								sta2_food = 280;
								 
								if(sta2_layout_page == LAYOUT_ADA)
								{								 
									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 0; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Ada"); 
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0;  
									sta2_squad[sta2_squad_count].face = 30;     
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_MORTAR; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				  
									sta2_pack[0].type = STA2_SCOUT;                
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 0; 
									sta2_pack[0].special = PACK_SPECIAL_SCOPE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "SCOUT PACK");   
				 
									sta2_pack[1].type = STA2_MORTAR;       
									sta2_pack[1].rank = 1;  
									sta2_pack[1].equipped = true; 
									sta2_pack[1].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_GRENADE
									sta2_pack[1].extra_charge = 0;
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "MORTAR PACK");   
								}
								if(sta2_layout_page == LAYOUT_MARIE)
								{								 
									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 38; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Marie"); 
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0;  
									sta2_squad[sta2_squad_count].face = 30;     
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_MORTAR; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				  
									sta2_pack[0].type = STA2_HEAVY;                
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 0; 
									sta2_pack[0].special = PACK_SPECIAL_SHIELD;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "HEAVY PACK");   
				 
									sta2_pack[1].type = STA2_MORTAR;       
									sta2_pack[1].rank = 1;  
									sta2_pack[1].equipped = true; 
									sta2_pack[1].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_GRENADE
									sta2_pack[1].extra_charge = 0;
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "MORTAR PACK");   
								}
								if(sta2_layout_page == LAYOUT_ADELE)
								{								 
									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 43; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Adele"); 
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0;  
									sta2_squad[sta2_squad_count].face = 30;     
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_MORTAR; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				  
									sta2_pack[0].type = STA2_SNIPER;                
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 0; 
									sta2_pack[0].special = PACK_SPECIAL_DUMDUM;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "SNIPER PACK");   
				 
									sta2_pack[1].type = STA2_MORTAR;       
									sta2_pack[1].rank = 1;  
									sta2_pack[1].equipped = true; 
									sta2_pack[1].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_GRENADE
									sta2_pack[1].extra_charge = 0;
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "MORTAR PACK");   
								}
								if(sta2_layout_page == LAYOUT_BELLA)
								{								 
									// Add some units to the roster...   
									sta2_squad[sta2_squad_count].xp = 0; 
									sta2_squad[sta2_squad_count].face = 44; // 1+rand()%10
									sta2_squad[sta2_squad_count].deployed = false;  
									sta2_squad[sta2_squad_count].rank = 2;   
									sta2_squad[sta2_squad_count].type = STA2_CO;
									sta2_squad[sta2_squad_count].wp = 0; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sprintf(sta2_squad[sta2_squad_count].string, "Bella"); 
									sta2_squad_count++;   
				 
									sta2_squad[sta2_squad_count].xp = 0;  
									sta2_squad[sta2_squad_count].face = 30;     
									sta2_squad[sta2_squad_count].deployed = false; 
									sta2_squad[sta2_squad_count].rank = 1;   
									sta2_squad[sta2_squad_count].type = STA2_MORTAR; 
									sta2_squad[sta2_squad_count].wp = 1; 
									sta2_squad[sta2_squad_count].health = TotalSquadScore(sta2_squad_count);
									sta2GetName("data/text/names/names.txt", sta2_squad[sta2_squad_count].string);
									sta2_squad_count++;   
				  
									sta2_pack[0].type = STA2_MORTAR;                
									sta2_pack[0].rank = 1;       
									sta2_pack[0].equipped = true;  
									sta2_pack[0].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].extra_charge = 0; 
									sta2_pack[0].special = PACK_SPECIAL_VAMPIRE;   // PACK_EXTRA_MEDKIT
									sta2_pack[0].special_charge = 0;
									sprintf(sta2_pack[0].string, "VAMPIRE PACK");   
				 
									sta2_pack[1].type = STA2_MORTAR;       
									sta2_pack[1].rank = 1;  
									sta2_pack[1].equipped = true; 
									sta2_pack[1].extra = PACK_EXTRA_NONE;   // PACK_EXTRA_GRENADE
									sta2_pack[1].extra_charge = 0;
									sta2_pack[1].special = PACK_SPECIAL_NONE;   // PACK_EXTRA_MEDKIT
									sta2_pack[1].special_charge = 0;
									sprintf(sta2_pack[1].string, "MORTAR PACK");   
								}
								 
								title_sequence++;  
							} 

						} 
						   
						// For left-sided messages, get longest line...
						if( new_counter[4].x >= sta2_left_of_screen)  
						{ 
							slongest_line = GetLongestLine(new_counter[4].word); 
							   
							new_counter[5].x = mouseX - 0.03f;  
							new_counter[4].x = new_counter[5].x - (slongest_line*0.0245f);  

						} 	

						if(sta2_layouts[sta2_layout_page][i-1] == LAYOUT_OPEN)
						if(mouseleft == true)   
						{
							 
							sta2_squad_alive_count = sta2_squad_count;   
				 
							for(int i=0 ; i < 12;i++) 
								sta2_battle_squad[i] = -1;

							// Create a dummy battle squad; Move to squad select screen at some point...
							for(int i=0 ; i < sta2_squad_count;i++)
							{
								if(sta2_squad[i].deployed == true) 
								{
									sta2_battle_squad[sta2_roster_count] = i; // Is roster unit 0
									sta2_roster_count++;
								} 
							}

							mouseleft = false;
							// New Game
							sta2_playing_tutorial = false;
							Start_Game(); 

						}
					}


				}

				// Ada...  
				if(sprite[8].alpha == 1.0)    
				if(( mouseX < (sprite[8].w + sprite[8].box_width) )
				&&( mouseX > sprite[8].w)                            
				&&( mouseY < (sprite[8].z + sprite[8].box_height) )
				&&( mouseY > sprite[8].z)) 
				{
					new_counter[4].alpha = 1.0f;                
					   
					new_counter[4].x = mouseX + 0.13f;                   
					new_counter[4].y = mouseY;     
					 
					new_counter[5].alpha = 1.0f;               
					    
					new_counter[5].x = mouseX + 0.1f;                        
					new_counter[5].y = mouseY;    

					sprintf( new_counter[5].word, "@");   

    				sprintf( new_counter[4].word, "SELECT^ADA FROST^");	 

					Set_Sprite(8, sprite[8].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

					if(mouseleft == true)
					{
						sta2_layout_page = LAYOUT_ADA;
						mouseleft = false;
					}

				}
				else 
					Set_Sprite(8, sprite[8].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				   
				// Marie...   
				if(sprite[9].alpha == 1.0)    
				if(( mouseX < (sprite[9].w + sprite[9].box_width) ) 
				&&( mouseX > sprite[9].w)                            
				&&( mouseY < (sprite[9].z + sprite[9].box_height) )
				&&( mouseY > sprite[9].z)) 
				{ 

					new_counter[4].alpha = 1.0f;                
					   
					new_counter[4].x = mouseX + 0.13f;                  
					new_counter[4].y = mouseY;     
					 
					new_counter[5].alpha = 1.0f;               
					    
					new_counter[5].x = mouseX + 0.1f;                       
					new_counter[5].y = mouseY;    

					sprintf( new_counter[5].word, "@");   

    				sprintf( new_counter[4].word, "LOCKED!^BEAT TRAINING^MODE!^");	 

					Set_Sprite(9, sprite[9].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

					if(sta2_has_marie > 0)
					{
						sprintf( new_counter[4].word, "SELECT^MARIE FLOCKHEART^");

						if(mouseleft == true)
						{
							sta2_layout_page = LAYOUT_MARIE;
							mouseleft = false;
						}
					}
				}
				else 
					Set_Sprite(9, sprite[9].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				    
				// Adele...   
				if(sprite[10].alpha == 1.0)     
				if(( mouseX < (sprite[10].w + sprite[10].box_width) )
				&&( mouseX > sprite[10].w)                            
				&&( mouseY < (sprite[10].z + sprite[10].box_height) )
				&&( mouseY > sprite[10].z)) 
				{

					new_counter[4].alpha = 1.0f;                
					   
					new_counter[4].x = mouseX + 0.13f;                  
					new_counter[4].y = mouseY;     
					 
					new_counter[5].alpha = 1.0f;               
					    
					new_counter[5].x = mouseX + 0.1f;                       
					new_counter[5].y = mouseY;    

					sprintf( new_counter[5].word, "@");    

    				sprintf( new_counter[4].word, "LOCKED!^BEAT NORMAL^MODE!^");	

					Set_Sprite(10, sprite[10].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

					if(sta2_has_adele > 0)
					{
						sprintf( new_counter[4].word, "SELECT^ADELE LEVINE^");

						if(mouseleft == true)
						{
							sta2_layout_page = LAYOUT_ADELE;
							mouseleft = false;
						}
					}
				} 
				else   
					Set_Sprite(10, sprite[10].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
		     
				// Bella...   
				if(sprite[13].alpha == 1.0)    
				if(( mouseX < (sprite[13].w + sprite[13].box_width) )
				&&( mouseX > sprite[13].w)                            
				&&( mouseY < (sprite[13].z + sprite[13].box_height) )
				&&( mouseY > sprite[13].z)) 
				{

					new_counter[4].alpha = 1.0f;                
					   
					new_counter[4].x = mouseX + 0.13f;                  
					new_counter[4].y = mouseY;     
					 
					new_counter[5].alpha = 1.0f;               
					    
					new_counter[5].x = mouseX + 0.1f;                       
					new_counter[5].y = mouseY;    

					sprintf( new_counter[5].word, "@");   

    				sprintf( new_counter[4].word, "LOCKED!^BEAT HARD^MODE!^");

					Set_Sprite(13, sprite[13].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

					if(sta2_has_bella > 0)
					{
						sprintf( new_counter[4].word, "SELECT^BELLA LARZ^");

						if(mouseleft == true)
						{
							sta2_layout_page = LAYOUT_BELLA;
							mouseleft = false;
						}
					} 
						   
					// For left-sided messages, get longest line...
					if( new_counter[4].x >= sta2_left_of_screen)  
					{ 
						slongest_line = GetLongestLine(new_counter[4].word); 
							   
						new_counter[5].x = mouseX - 0.03f;  
						new_counter[4].x = new_counter[5].x - (slongest_line*0.0245f);  

					} 	

				}
				else 
					Set_Sprite(13, sprite[13].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);



			}

	   }

    // ******************************************************************************//
    //                                 1-30  (END SCREEN)                            //
    // ******************************************************************************//
             
       // Title Screen Stuff...         
       if(!mode)      
       if(next_scene == false)    
       if(episode == 1 && scene == 30)         
       {        
	        if(title_sequence == 0)                    
            {  	 

				sta2_got_new_ada_layout = false;
				sta2_got_new_marie_layout = false; 
				sta2_got_new_adele_layout = false; 
				sta2_got_new_bella_layout = false;

				sta2_got_marie = false;
				sta2_got_adele = false; 
				sta2_got_bella = false;

				sta2_got_normal_mode=false;
				sta2_got_hard_mode=false;  

				if(sta2_difficulty == STA2_TRAINING_MODE) 
				{ 
					if(sta2_has_marie == 0)
						sta2_got_marie = true;
					if(sta2_has_beaten_training_game == false) 
						sta2_got_normal_mode = true;

					sta2_has_marie = 1;
					sta2_has_beaten_training_game = true; 
				}

				if(sta2_difficulty == STA2_NORMAL_MODE) 
				{
					if(sta2_has_adele == 0)
						sta2_got_adele = true;
					if(sta2_has_beaten_normal_game == false)
						sta2_got_hard_mode = true;

					sta2_has_adele = 1;
					sta2_has_beaten_normal_game = true;
				}

				if(sta2_difficulty == STA2_HARD_MODE)
				{
					if(sta2_has_bella == 0)
						sta2_got_bella = true;

					sta2_has_bella = 1; 
				}

			    sprintf( new_counter[0].word, "3 : Back");   

			    new_counter[0].alpha = 0.0f;                       
			    new_counter[0].id = 0;    
		        
			    new_counter[0].x = +0.50f;                 
			    new_counter[0].y = -0.34f;       	        
				     
				new_counter[0].w = new_counter[0].x - 0.026f;    
				new_counter[0].z = new_counter[0].y - 0.015f; 

				new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
				new_counter[0].box_height = new_counter[0].height - 0.015f;	

				new_counter[1].alpha = 1.0f;             
				new_counter[1].id = 0;            
		                         
				new_counter[1].x = -0.36f;         
				new_counter[1].y = -0.50f; // Stop at 0.20f       
				 
				new_counter[1].w = new_counter[1].x - 0.026f;         
				new_counter[1].z = new_counter[1].y - 0.015f; 
			   
				new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;  
				new_counter[1].box_height = new_counter[1].height - 0.015f;	
			 
				sprintf( new_counter[1].word, "Hungry and tired the squad^crossed the border home..^^With the enemy plans the^Keiser$s invasion was averted^...for now.^^Is this the true end?");  

				start_timer = (int)TimerGetTime() + 16000;

				title_sequence++;   
			}  
	        if((int)TimerGetTime() > start_timer)                                
			{  
				episode = 1;
				scene = 31; 

				next_scene = true;  

				title_sequence++; 
			} 
	        if(title_sequence == 1)                             
            {     

				if(new_counter[1].y < 0.20f)
					new_counter[1].y += 0.00005f*(float)f_rate;
				else
					new_counter[1].y = 0.20f;

				new_counter[0].id = 0; 
				 
				testX = hud_mouseX - (-camX);                                                      
				testY = hud_mouseY - (-camY);   

				// Back button..
			//	if(new_counter[0].alpha == 1.0f)
				if(( testX < (new_counter[0].w + new_counter[0].box_width) )
				&&( testX > new_counter[0].w)                            
				&&( testY < (new_counter[0].z + new_counter[0].box_height) )
				&&( testY > new_counter[0].z) || sta2_esc_pressed == true)   
				{ 
					new_counter[0].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_esc_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_esc_pressed = false;  
						
						fade_out = 0;
						c_fade_out = 0; 

						episode = 1;   
						scene = 29;

						next_scene = true;

						title_sequence++;

					} 
				}  

			}

	   }

    // ******************************************************************************//
    //                                 1-31  (END SCREEN)                            //
    // ******************************************************************************//
             
       // Title Screen Stuff...         
       if(!mode)      
       if(next_scene == false)    
       if(episode == 1 && scene == 31)        
       {       
	        if(title_sequence == 0)                   
            {  	 
				 
				sta2_start_outroY = sprite[1].y;     
				 
				sprite[1].y -= sprite[1].height * 1.370f; 

			    sprintf( new_counter[0].word, "3 : Back");   
				 
			    new_counter[0].alpha = 0.0f;                       
			    new_counter[0].id = 0;    
		        
			    new_counter[0].x = +0.50f;                 
			    new_counter[0].y = -0.34f;       	        
				     
				new_counter[0].w = new_counter[0].x - 0.026f;    
				new_counter[0].z = new_counter[0].y - 0.015f; 

				new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
				new_counter[0].box_height = new_counter[0].height - 0.015f;	

				new_counter[1].alpha = 1.0f;             
				new_counter[1].id = 0;            
		                          
				new_counter[1].x = -0.0f;             
				new_counter[1].y = 0.64f; // Stop at 0.20f       

				new_counter[1].w = new_counter[1].x - 0.026f;           
				new_counter[1].z = new_counter[1].y - 0.015f; 
			   
				new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
				new_counter[1].box_height = new_counter[1].height - 0.015f;	
			 
				sprintf( new_counter[1].word, "     Made by^Paul Stephen-Davis");  

				start_timer = (int)TimerGetTime() + 6000;

				title_sequence++;    
			}  
	        if((int)TimerGetTime() > start_timer)                                
			{  
				episode = 1;
				scene = 32; 

				next_scene = true;  

				title_sequence++;
			}
	        if(title_sequence == 1)                                   
            {       
				    
				if(new_counter[1].y > 0.08f)
					new_counter[1].y -= 0.0001f*(float)f_rate;
				else 
					new_counter[1].y = 0.08f;    

				if(sprite[1].y < sta2_start_outroY)
					sprite[1].y += 0.0001f*(float)f_rate;
				else
					sprite[1].y = sta2_start_outroY;   

				new_counter[0].id = 0; 
				 
				testX = hud_mouseX - (-camX);                                                      
				testY = hud_mouseY - (-camY);   

				// Back button..
			//	if(new_counter[0].alpha == 1.0f)
				if(( testX < (new_counter[0].w + new_counter[0].box_width) )
				&&( testX > new_counter[0].w)                            
				&&( testY < (new_counter[0].z + new_counter[0].box_height) )
				&&( testY > new_counter[0].z) || sta2_esc_pressed == true)   
				{ 
					new_counter[0].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_esc_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_esc_pressed = false; 
						
						fade_out = 0;
						c_fade_out = 0; 

						episode = 1;   
						scene = 29;

						next_scene = true;

						title_sequence++;

					} 
				}  // Back button

			} // title_sequence == 1

	   } // if(episode == 1 && scene == 31)  
        

    // ******************************************************************************//
    //                                 1-32  (END SCREEN)                            //
    // ******************************************************************************//
             
       // Title Screen Stuff...         
       if(!mode)      
       if(next_scene == false)    
       if(episode == 1 && scene == 32)       
       {       
	        if(title_sequence == 0)                   
            {  	 
				 
				sta2_start_outroY = sprite[1].y;     
				 
				sprite[1].y += sprite[1].height * 1.370f; 

			    sprintf( new_counter[0].word, "3 : Back");   
				 
			    new_counter[0].alpha = 0.0f;                       
			    new_counter[0].id = 0;    
		        
			    new_counter[0].x = +0.50f;                   
			    new_counter[0].y = -0.34f;       	        
				     
				new_counter[0].w = new_counter[0].x - 0.026f;    
				new_counter[0].z = new_counter[0].y - 0.015f; 

				new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
				new_counter[0].box_height = new_counter[0].height - 0.015f;	
				  
				new_counter[1].alpha = 1.0f;                    
				new_counter[1].id = 0;             
		                              
				new_counter[1].x = -0.40f;              
				new_counter[1].y = -0.505f; // Stop at 0.20f       

				new_counter[1].w = new_counter[1].x - 0.026f;           
				new_counter[1].z = new_counter[1].y - 0.015f; 
			   
				new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
				new_counter[1].box_height = new_counter[1].height - 0.015f;	
			 
				sprintf( new_counter[1].word, "   Music by^Erik Sjostrand^ Robin Jensen^");  
				  
				start_timer = (int)TimerGetTime() + 6000;

				title_sequence++;      
			}  
	        if((int)TimerGetTime() > start_timer)                                
			{  
				episode = 1;
				scene = 33; 

				next_scene = true;  

				title_sequence++; 
			} 
	        if(title_sequence == 1)                                       
            {          
				   
				if(new_counter[1].y < 0.06f)
					new_counter[1].y += 0.0001f*(float)f_rate;
				else
					new_counter[1].y = 0.06f;      

				if(sprite[1].y > sta2_start_outroY) 
					sprite[1].y -= 0.0001f*(float)f_rate;
				else
					sprite[1].y = sta2_start_outroY;   

				new_counter[0].id = 0; 
				 
				testX = hud_mouseX - (-camX);                                                      
				testY = hud_mouseY - (-camY);   

				// Back button..
		//		if(new_counter[0].alpha == 1.0f)
				if(( testX < (new_counter[0].w + new_counter[0].box_width) )
				&&( testX > new_counter[0].w)                            
				&&( testY < (new_counter[0].z + new_counter[0].box_height) )
				&&( testY > new_counter[0].z) || sta2_esc_pressed == true)   
				{ 
					new_counter[0].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_esc_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_esc_pressed = false; 
						
						fade_out = 0;
						c_fade_out = 0; 

						episode = 1;   
						scene = 29;

						next_scene = true;

						title_sequence++;

					} 
				}  // Back button

			} // title_sequence == 1

	   } // if(episode == 1 && scene == 32)  

    // ******************************************************************************//
    //                                 1-33  (END SCREEN)                            //
    // ******************************************************************************//
             
       // Title Screen Stuff...         
       if(!mode)      
       if(next_scene == false)    
       if(episode == 1 && scene == 33)       
       {       
	        if(title_sequence == 0)                   
            {  	 
				 
				sta2_start_outroY = sprite[1].x;     
				 
				sprite[1].x -= sprite[1].width * 1.2f; 

			    sprintf( new_counter[0].word, "3 : Back");   
				 
			    new_counter[0].alpha = 0.0f;                       
			    new_counter[0].id = 0;    
		         
			    new_counter[0].x = +0.50f;                   
			    new_counter[0].y = -0.34f;       	        
				     
				new_counter[0].w = new_counter[0].x - 0.026f;    
				new_counter[0].z = new_counter[0].y - 0.015f; 

				new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
				new_counter[0].box_height = new_counter[0].height - 0.015f;	
				  
				new_counter[1].alpha = 1.0f;                    
				new_counter[1].id = 0;             
		                              
				new_counter[1].x = 0.58f;                
				new_counter[1].y = 0.05f; // Stop at 0.20f       

				new_counter[1].w = new_counter[1].x - 0.026f;            
				new_counter[1].z = new_counter[1].y - 0.015f; 
			   
				new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
				new_counter[1].box_height = new_counter[1].height - 0.015f;	
			  
				sprintf( new_counter[1].word, "Audio code by^   Audiere^");  
				  
				start_timer = (int)TimerGetTime() + 6000;

				title_sequence++;      
			}  
	        if((int)TimerGetTime() > start_timer)                                
			{  
				episode = 1;
				scene = 34; 

				next_scene = true;  

				title_sequence++; 
			} 
	        if(title_sequence == 1)                                       
            {          
				    
				if(new_counter[1].x > 0.1f)
					new_counter[1].x -= 0.0001f*(float)f_rate;
				else
					new_counter[1].x = 0.1f;       

				if(sprite[1].x < sta2_start_outroY) 
					sprite[1].x += 0.0001f*(float)f_rate;
				else
					sprite[1].x = sta2_start_outroY;   

				new_counter[0].id = 0; 
				 
				testX = hud_mouseX - (-camX);                                                      
				testY = hud_mouseY - (-camY);   

				// Back button..
		//		if(new_counter[0].alpha == 1.0f)
				if(( testX < (new_counter[0].w + new_counter[0].box_width) )
				&&( testX > new_counter[0].w)                            
				&&( testY < (new_counter[0].z + new_counter[0].box_height) )
				&&( testY > new_counter[0].z) || sta2_esc_pressed == true)   
				{ 
					new_counter[0].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_esc_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_esc_pressed = false; 

						episode = 1;   
						scene = 29;
						
						fade_out = 0;
						c_fade_out = 0; 

						next_scene = true;

						title_sequence++;

					} 
				}  // Back button

			} // title_sequence == 1

	   } // if(episode == 1 && scene == 33)  

    // ******************************************************************************//
    //                                 1-34  (END SCREEN)                            //
    // ******************************************************************************//
             
       // Title Screen Stuff...         
       if(!mode)      
       if(next_scene == false)    
       if(episode == 1 && scene == 34)        
       {       
	        if(title_sequence == 0)                   
            {  	 
				         
				sta2_start_outroY = sprite[1].y;     
				 
				sprite[1].y += sprite[1].height * 1.0f; 

			    sprintf( new_counter[0].word, "3 : Back");   
				 
			    new_counter[0].alpha = 0.0f;                       
			    new_counter[0].id = 0;    
		         
			    new_counter[0].x = +0.50f;                   
			    new_counter[0].y = -0.34f;       	        
				     
				new_counter[0].w = new_counter[0].x - 0.026f;    
				new_counter[0].z = new_counter[0].y - 0.015f; 

				new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
				new_counter[0].box_height = new_counter[0].height - 0.015f;	
				  
				new_counter[1].alpha = 1.0f;                     
				new_counter[1].id = 0;                  
		                                  
				new_counter[1].x = -0.2f;                    
				new_counter[1].y = -0.5f; // Stop at 0.20f       

				new_counter[1].w = new_counter[1].x - 0.026f;            
				new_counter[1].z = new_counter[1].y - 0.015f; 
			   
				new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
				new_counter[1].box_height = new_counter[1].height - 0.015f;	
			  
				sprintf( new_counter[1].word, "Thanks for playing!^");  
				  
				start_timer = (int)TimerGetTime() + 6000;

				title_sequence++;      
			}  
	        if((int)TimerGetTime() > start_timer)                                
			{   
				episode = 1;
				scene = 29;  

				next_scene = true;    

				title_sequence++; 
			} 
	        if(title_sequence == 1)                                       
            {          
				    
				if(new_counter[1].y < -0.1f)
					new_counter[1].y += 0.0001f*(float)f_rate;
				else
					new_counter[1].y = -0.1f;       

				if(sprite[1].y > sta2_start_outroY) 
					sprite[1].y -= 0.0001f*(float)f_rate;
				else
					sprite[1].y = sta2_start_outroY;   

				new_counter[0].id = 0; 
				 
				testX = hud_mouseX - (-camX);                                                      
				testY = hud_mouseY - (-camY);   

				// Back button..
		//		if(new_counter[0].alpha == 1.0f)
				if(( testX < (new_counter[0].w + new_counter[0].box_width) )
				&&( testX > new_counter[0].w)                            
				&&( testY < (new_counter[0].z + new_counter[0].box_height) )
				&&( testY > new_counter[0].z) || sta2_esc_pressed == true)   
				{ 
					new_counter[0].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_esc_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_esc_pressed = false; 

						episode = 1;   
						scene = 29;
						
						fade_out = 0;
						c_fade_out = 0; 

						next_scene = true;

						title_sequence++;

					} 
				}  // Back button

			} // title_sequence == 1

	   } // if(episode == 1 && scene == 34)  

    // ******************************************************************************//
    //                               1-35  (INTRO SCREEN)                            //
    // ******************************************************************************//
             
       // Title Screen Stuff...         
       if(!mode)      
       if(next_scene == false)     
       if(episode == 1 && scene == 35)              
       {       
	        if(title_sequence == 0)                     
            {  	 

			    sprintf( new_counter[0].word, "3 : Back");   

			    new_counter[0].alpha = 0.0f;                       
			    new_counter[0].id = 0;     
		        
			    new_counter[0].x = +0.50f;                 
			    new_counter[0].y = -0.34f;       	        
				     
				new_counter[0].w = new_counter[0].x - 0.026f;    
				new_counter[0].z = new_counter[0].y - 0.015f; 

				new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
				new_counter[0].box_height = new_counter[0].height - 0.015f;	

				new_counter[1].alpha = 1.0f;              
				new_counter[1].id = 0;            
		                          
				new_counter[1].x = -0.36f;         
				new_counter[1].y = -0.50f; // Stop at 0.20f       
				          
				new_counter[1].w = new_counter[1].x - 0.026f;         
				new_counter[1].z = new_counter[1].y - 0.015f;      
			     
				new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;    
				new_counter[1].box_height = new_counter[1].height - 0.015f;	
			 
				sprintf( new_counter[1].word, "Four years have passed since^the last war. A mysterious man^has crowned himself the new^Keiser.^^With dark intent he plots to^throw the world into darkness^yet again...^^However there are some within^the Black Army that oppose this^new Keiser, they call themselves^the fifth column...^^Elsewhere a group of Blue Army^scouts are lost in Black Army^territory.^^If they discover the Keiser$s^invasion plans the war could^be averted...");  

				start_timer = (int)TimerGetTime() + 48000; 

				title_sequence++;      
			}  
	        if((int)TimerGetTime() > start_timer)                                       
			{            
				episode = 0; 
				scene = 1;   
				         
				next_scene = true;     
				   
				title_sequence++;   
			}  
	   /*     if((int)TimerGetTime() > start_timer - 32000)                                  
			{   
				sprite[3].x += 0.0003f*(float)f_rate;
			} 
	        if((int)TimerGetTime() > start_timer - 24000)                                 
			{  
				sprite[4].x += 0.0003f*(float)f_rate;
				sprite[5].x += 0.0003f*(float)f_rate;
			} */
	        if(title_sequence == 1)                             
            {       
				 
			//	if(new_counter[1].y < 0.20f)
					new_counter[1].y += 0.00003f*(float)f_rate;
			//	else
			//		new_counter[1].y = 0.20f;

				new_counter[0].id = 0; 
				 
				testX = hud_mouseX - (-camX);                                                      
				testY = hud_mouseY - (-camY);    

				// Back button..
			//	if(new_counter[0].alpha == 1.0f)
				if(( testX < (new_counter[0].w + new_counter[0].box_width) )
				&&( testX > new_counter[0].w)                            
				&&( testY < (new_counter[0].z + new_counter[0].box_height) )
				&&( testY > new_counter[0].z) || sta2_esc_pressed == true)   
				{ 
					new_counter[0].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_esc_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_esc_pressed = false;       
						
						fade_out = 0;
						c_fade_out = 0; 

						episode = 0;   
						scene = 1;

						next_scene = true;

						title_sequence++;

					} 
				}  

			}

	   } // if(episode == 1 && scene == 35) 

    // ******************************************************************************//
    //                               1-36  (INTRO SCREEN)                            //
    // ******************************************************************************//
             
       // Title Screen Stuff...         
       if(!mode)      
       if(next_scene == false)    
       if(episode == 1 && scene == 36)       
       {       
	        if(title_sequence == 0)                     
            {  	 

			    sprintf( new_counter[0].word, "3 : Back");   

			    new_counter[0].alpha = 0.0f;                       
			    new_counter[0].id = 0;     
		        
			    new_counter[0].x = +0.50f;                 
			    new_counter[0].y = -0.34f;       	        
				     
				new_counter[0].w = new_counter[0].x - 0.026f;    
				new_counter[0].z = new_counter[0].y - 0.015f; 

				new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
				new_counter[0].box_height = new_counter[0].height - 0.015f;	

				new_counter[1].alpha = 1.0f;              
				new_counter[1].id = 0;            
		                          
				new_counter[1].x = -0.36f;         
				new_counter[1].y = -0.50f; // Stop at 0.20f       
				       
				new_counter[1].w = new_counter[1].x - 0.026f;         
				new_counter[1].z = new_counter[1].y - 0.015f;  
			   
				new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;    
				new_counter[1].box_height = new_counter[1].height - 0.015f;	
			 
				sprintf( new_counter[1].word, "However there are some within the^Black Army that oppose the new^Keiser, they call themselves^the fifth column...");  

				start_timer = (int)TimerGetTime() + 16000; 

				title_sequence++;    
			}  
	        if((int)TimerGetTime() > start_timer)                                
			{  
			//	episode = 1; 
			//	scene = 31; 

			//	next_scene = true;   

			//	title_sequence++; 
			} 
	        if(title_sequence == 1)                             
            {     

				if(new_counter[1].y < 0.20f)
					new_counter[1].y += 0.00005f*(float)f_rate;
				else
					new_counter[1].y = 0.20f;

				new_counter[0].id = 0; 
				 
				testX = hud_mouseX - (-camX);                                                      
				testY = hud_mouseY - (-camY);   

				// Back button..
			//	if(new_counter[0].alpha == 1.0f)
				if(( testX < (new_counter[0].w + new_counter[0].box_width) )
				&&( testX > new_counter[0].w)                            
				&&( testY < (new_counter[0].z + new_counter[0].box_height) )
				&&( testY > new_counter[0].z) || sta2_esc_pressed == true)   
				{ 
					new_counter[0].id = 2;   

					if(mouseleft == true || DX_SHOOT == true || sta2_esc_pressed == true) 
					{  
						 
						mouseleft = false;       
						DX_SHOOT = false;  
						sta2_esc_pressed = false;  
						
						fade_out = 0;
						c_fade_out = 0; 

						episode = 0;   
						scene = 1;

						next_scene = true;

						title_sequence++;

					} 
				}  

			}

	   } // if(episode == 1 && scene == 36) 
    // ******************************************************************************//
    //                              1-37  (UNLOCK SCREEN)                            //
    // ******************************************************************************//
             
	// Title Screen Stuff...             
	if(!mode)      
	if(next_scene == false)    
	if(episode == 1 && scene == 37)       
	{             

		if(sta2_yes_no_page == 0)
			Set_Sprite(3, 4, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Point Arrow 

		new_counter[15].alpha = 0.0f; 
		new_counter[15].alpha = 1.0f; 

		if(sta2_yes_no_active == true)      
		{  
				 
			hud[3].alpha = 1.0f;   
				   
			if(sta2_yes_no_page == 0) 
			{
				new_counter[15].alpha = 1.0f;
				new_counter[15].x = hud[3].x + 0.06f;  
				new_counter[15].y =  hud[3].y + hud[3].height - 0.1f;
				new_counter[15].w = new_counter[15].x - 0.026f;   
				new_counter[15].z = new_counter[15].y - 0.015f;
				new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
				new_counter[15].box_height = new_counter[15].height - 0.015f;	
				sprintf(new_counter[15].word, "Normal mode^is now^available!"); 

			}
			if(sta2_yes_no_page == 1) 
			{
				new_counter[15].alpha = 1.0f;
				new_counter[15].x = hud[3].x + 0.06f;  
				new_counter[15].y =  hud[3].y + hud[3].height - 0.1f;
				new_counter[15].w = new_counter[15].x - 0.026f;   
				new_counter[15].z = new_counter[15].y - 0.015f;
				new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
				new_counter[15].box_height = new_counter[15].height - 0.015f;	
				sprintf(new_counter[15].word, "C.O Marie^is now^available!"); 
			}
				   
			if(sta2_yes_no_page == 2) 
			{
				new_counter[15].alpha = 1.0f;
				new_counter[15].x = hud[3].x + 0.06f;  
				new_counter[15].y =  hud[3].y + hud[3].height - 0.1f;
				new_counter[15].w = new_counter[15].x - 0.026f;   
				new_counter[15].z = new_counter[15].y - 0.015f;
				new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
				new_counter[15].box_height = new_counter[15].height - 0.015f;	
				sprintf(new_counter[15].word, "Hard mode^is now^available!"); 
			}
			if(sta2_yes_no_page == 3) 
			{
				new_counter[15].alpha = 1.0f;
				new_counter[15].x = hud[3].x + 0.06f;  
				new_counter[15].y =  hud[3].y + hud[3].height - 0.1f;
				new_counter[15].w = new_counter[15].x - 0.026f;   
				new_counter[15].z = new_counter[15].y - 0.015f;
				new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
				new_counter[15].box_height = new_counter[15].height - 0.015f;	
				sprintf(new_counter[15].word, "C.O Adele^is now^available!"); 
			}
			if(sta2_yes_no_page == 4) 
			{
				new_counter[15].alpha = 1.0f;
				new_counter[15].x = hud[3].x + 0.06f;  
				new_counter[15].y =  hud[3].y + hud[3].height - 0.1f;
				new_counter[15].w = new_counter[15].x - 0.026f;   
				new_counter[15].z = new_counter[15].y - 0.015f;
				new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
				new_counter[15].box_height = new_counter[15].height - 0.015f;	
				sprintf(new_counter[15].word, "C.O Bella^is now^available!"); 
			}
			if(sta2_yes_no_page == 5) 
			{
				new_counter[15].alpha = 1.0f;
				new_counter[15].x = hud[3].x + 0.06f;  
				new_counter[15].y =  hud[3].y + hud[3].height - 0.1f;
				new_counter[15].w = new_counter[15].x - 0.026f;   
				new_counter[15].z = new_counter[15].y - 0.015f;
				new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
				new_counter[15].box_height = new_counter[15].height - 0.015f;	
				sprintf(new_counter[15].word, "New Ada^layout is^available!"); 
			}
			if(sta2_yes_no_page == 6) 
			{
				new_counter[15].alpha = 1.0f;
				new_counter[15].x = hud[3].x + 0.06f;  
				new_counter[15].y =  hud[3].y + hud[3].height - 0.1f;
				new_counter[15].w = new_counter[15].x - 0.026f;   
				new_counter[15].z = new_counter[15].y - 0.015f;
				new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
				new_counter[15].box_height = new_counter[15].height - 0.015f;	
				sprintf(new_counter[15].word, "New Marie^layout is^available!"); 
			}
			if(sta2_yes_no_page == 7) 
			{
				new_counter[15].alpha = 1.0f;
				new_counter[15].x = hud[3].x + 0.06f;  
				new_counter[15].y =  hud[3].y + hud[3].height - 0.1f;
				new_counter[15].w = new_counter[15].x - 0.026f;   
				new_counter[15].z = new_counter[15].y - 0.015f;
				new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
				new_counter[15].box_height = new_counter[15].height - 0.015f;	
				sprintf(new_counter[15].word, "New Adele^layout is^available!"); 
			}
			if(sta2_yes_no_page == 8) 
			{
				new_counter[15].alpha = 1.0f;
				new_counter[15].x = hud[3].x + 0.06f;  
				new_counter[15].y =  hud[3].y + hud[3].height - 0.1f;
				new_counter[15].w = new_counter[15].x - 0.026f;   
				new_counter[15].z = new_counter[15].y - 0.015f;
				new_counter[15].box_width = strlen(new_counter[15].word)   *  0.026f;
				new_counter[15].box_height = new_counter[15].height - 0.015f;	
				sprintf(new_counter[15].word, "New Bella^layout is^available!"); 
			}
			  
			new_counter[7].alpha = 1.0f;    

			new_counter[7].id = 0;    
			     
			if(sta2_yes_no_page == 0)   
				sprintf(new_counter[7].word, "1. NEXT");    
			if(sta2_yes_no_page == 1) 
				sprintf(new_counter[7].word, "1. CONTINUE");  
			if(sta2_yes_no_page == 2)   
				sprintf(new_counter[7].word, "1. NEXT");    
			if(sta2_yes_no_page == 3) 
				sprintf(new_counter[7].word, "1. CONTINUE"); 
			if(sta2_yes_no_page == 4) 
				sprintf(new_counter[7].word, "1. CONTINUE"); 
			if(sta2_yes_no_page == 5) 
				sprintf(new_counter[7].word, "1. CONTINUE"); 
			if(sta2_yes_no_page == 6) 
				sprintf(new_counter[7].word, "1. CONTINUE"); 
			if(sta2_yes_no_page == 7) 
				sprintf(new_counter[7].word, "1. CONTINUE"); 
			if(sta2_yes_no_page == 8) 
				sprintf(new_counter[7].word, "1. CONTINUE"); 

			new_counter[7].x = hud[3].x + 0.06f;  
			new_counter[7].y =  hud[3].y + hud[3].height - 0.26f;
			new_counter[7].w = new_counter[7].x - 0.026f;   
			new_counter[7].z = new_counter[7].y - 0.015f;
			new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
			new_counter[7].box_height = new_counter[7].height - 0.015f;	 

		}
		else        
		{
			new_counter[7].alpha = 0.0f;  
			new_counter[15].alpha = 0.0f;
			hud[3].alpha = 0.0f; 
		} 
		if(title_sequence == 0)                      
		{ 
			title_timer = (int)TimerGetTime() + 500;
			title_sequence++; 
		}

		if((int)TimerGetTime() > title_timer)   
		if(title_sequence == 1)                      
		{  	   
			sta2_yes_no_active = true;     

			if(sta2_got_new_ada_layout == true)
			{
			   	#if IS_FULL_STEAM == 1 

				if(sta2_ada_exp >= ADA_LAYOUT6_COST) 
				if(STEAM_ACTIVE == true)  
				if(IS_FULL_GAME == true)
				if (g_SteamAchievements)
				{
					g_SteamAchievements->SetAchievement("STA2_MEDAL_14"); // Unlock all Ada layouts...
					if(sta2_globals[GLOBAL_STA2_MEDAL_14] == GLOBALS_RESET)
					{
						sta2_globals[GLOBAL_STA2_MEDAL_14] = GLOBALS_ACTIVE;
						firework_sfx = true;

					}
				}

				#endif

				if(sta2_ada_exp >= ADA_LAYOUT6_COST) 
					sta2_globals[GLOBAL_STA2_MEDAL_14] = GLOBALS_ACTIVE;

				sta2_yes_no_page=5;
			}
			if(sta2_got_new_marie_layout == true)
			{
			   	#if IS_FULL_STEAM == 1 

				if(sta2_marie_exp >= MARIE_LAYOUT6_COST)
				if(STEAM_ACTIVE == true)  
				if(IS_FULL_GAME == true)
				if (g_SteamAchievements)
				{
					g_SteamAchievements->SetAchievement("STA2_MEDAL_15"); // Unlock all Marie layouts...
					if(sta2_globals[GLOBAL_STA2_MEDAL_15] == GLOBALS_RESET)
					{
						sta2_globals[GLOBAL_STA2_MEDAL_15] = GLOBALS_ACTIVE;
						firework_sfx = true;

					}
				}

				#endif

				if(sta2_marie_exp >= MARIE_LAYOUT6_COST)
					sta2_globals[GLOBAL_STA2_MEDAL_15] = GLOBALS_ACTIVE;

				sta2_yes_no_page=6;
			}
			if(sta2_got_new_adele_layout == true)
			{
			   	#if IS_FULL_STEAM == 1 

				if(sta2_adele_exp >= ADELE_LAYOUT6_COST)
				if(STEAM_ACTIVE == true)   
				if(IS_FULL_GAME == true)
				if (g_SteamAchievements)
				{
					g_SteamAchievements->SetAchievement("STA2_MEDAL_16"); // Unlock all Adele layouts...
					if(sta2_globals[GLOBAL_STA2_MEDAL_16] == GLOBALS_RESET)
					{
						sta2_globals[GLOBAL_STA2_MEDAL_16] = GLOBALS_ACTIVE;
						firework_sfx = true;

					}
				}

				#endif

				if(sta2_adele_exp >= ADELE_LAYOUT6_COST)
					sta2_globals[GLOBAL_STA2_MEDAL_16] = GLOBALS_ACTIVE;

				sta2_yes_no_page=7;
			}
			if(sta2_got_new_bella_layout == true)
			{
			   	#if IS_FULL_STEAM == 1 

				if(sta2_bella_exp >= BELLA_LAYOUT6_COST)
				if(STEAM_ACTIVE == true)  
				if(IS_FULL_GAME == true)
				if (g_SteamAchievements)
				{
					g_SteamAchievements->SetAchievement("STA2_MEDAL_17"); // Unlock all Bella layouts...
					if(sta2_globals[GLOBAL_STA2_MEDAL_17] == GLOBALS_RESET)
					{
						sta2_globals[GLOBAL_STA2_MEDAL_17] = GLOBALS_ACTIVE;
						firework_sfx = true;

					}
				}

				#endif

				if(sta2_bella_exp >= BELLA_LAYOUT6_COST)
					sta2_globals[GLOBAL_STA2_MEDAL_17] = GLOBALS_ACTIVE;

				sta2_yes_no_page=8; 
			}

			if(sta2_got_normal_mode == true) 
			{
				sta2_yes_no_page=0; 
	
				#if IS_FULL_STEAM == 1
				 
				if(STEAM_ACTIVE == true) 
				if(IS_FULL_GAME == true)
				if (g_SteamAchievements)
				{
					g_SteamAchievements->SetAchievement("STA2_MEDAL_4"); // Beat training mode...
					if(sta2_globals[GLOBAL_STA2_MEDAL_4] == GLOBALS_RESET)
					{
						sta2_globals[GLOBAL_STA2_MEDAL_4] = GLOBALS_ACTIVE;
						firework_sfx = true;

					}
				}

				#endif

				sta2_globals[GLOBAL_STA2_MEDAL_4] = GLOBALS_ACTIVE;
			}

			if(sta2_got_hard_mode == true) 
			{
				sta2_yes_no_page=2;
	
				#if IS_FULL_STEAM == 1

				if(STEAM_ACTIVE == true) 
				if(IS_FULL_GAME == true)
				if (g_SteamAchievements)
				{
					g_SteamAchievements->SetAchievement("STA2_MEDAL_5"); // Beat normal mode...
					if(sta2_globals[GLOBAL_STA2_MEDAL_5] == GLOBALS_RESET)
					{
						sta2_globals[GLOBAL_STA2_MEDAL_5] = GLOBALS_ACTIVE;
						firework_sfx = true;

					}
				}

				#endif

				sta2_globals[GLOBAL_STA2_MEDAL_5] = GLOBALS_ACTIVE;
			}

			if(sta2_got_bella == true)
			{
				sta2_yes_no_page=4;
	
				#if IS_FULL_STEAM == 1 

				if(STEAM_ACTIVE == true) 
				if(IS_FULL_GAME == true)
				if (g_SteamAchievements)
				{
					g_SteamAchievements->SetAchievement("STA2_MEDAL_6"); // Beat hard mode...
					if(sta2_globals[GLOBAL_STA2_MEDAL_6] == GLOBALS_RESET)
					{
						sta2_globals[GLOBAL_STA2_MEDAL_6] = GLOBALS_ACTIVE;
						firework_sfx = true;

					}
				}

				#endif

				sta2_globals[GLOBAL_STA2_MEDAL_6] = GLOBALS_ACTIVE;

			}
			 
			door_open_sfx = true;

			title_sequence++;

		}

		if(title_sequence == 2)
		{  	 
			new_counter[0].id = 0; 
			new_counter[7].id = 0;
				 
			testX = hud_mouseX - (-camX);                                                      
			testY = hud_mouseY - (-camY);     

			// YES...
			if(sta2_yes_no_active == true)  
			if(new_counter[7].id != 4) // Greyed out...
			if(new_counter[7].alpha == 1.0f)
			if(( testX < (new_counter[7].w + new_counter[7].box_width) )
			&&( testX > new_counter[7].w)                            
			&&( testY < (new_counter[7].z + new_counter[7].box_height) )
			&&( testY > new_counter[7].z) || sta2_1_pressed == true)   
			{ 
				new_counter[7].id = 2;     

				if(mouseleft == true || DX_SHOOT == true || sta2_1_pressed == true) 
				{  
					sta2_1_pressed = false;
					mouseleft = false;       
					DX_SHOOT = false;    

					switch(sta2_yes_no_page) 
					{

						case 0: 
							sta2_yes_no_page = 1;  
							door_open_sfx = true;
						break;

						case 1:
							sta2_yes_no_active = false;  
							sta2_yes_no_page = 0;

							title_sequence++;
						break;

						case 2: 
							sta2_yes_no_page = 3;  
							door_open_sfx = true;
						break;

						case 3:
							sta2_yes_no_active = false;  
							sta2_yes_no_page = 0;

							title_sequence++;
						break;
						  
						case 4:  
							sta2_yes_no_active = false;  
							sta2_yes_no_page = 0;

							title_sequence++;
						break;
						  
						case 5:  
							sta2_yes_no_active = false;  
							sta2_yes_no_page = 0;

							title_sequence++;
						break;
						  
						case 6:  
							sta2_yes_no_active = false;  
							sta2_yes_no_page = 0;

							title_sequence++;
						break;
						  
						case 7:  
							sta2_yes_no_active = false;  
							sta2_yes_no_page = 0;

							title_sequence++;
						break;
						  
						case 8:  
							sta2_yes_no_active = false;  
							sta2_yes_no_page = 0;

							title_sequence++; 
						break;

					}

				} 
			}  

		} // title_sequence == 1  

		if(title_sequence == 3)                     
		{  	
			episode = 0;
			scene = 1;

			next_scene = true;
		}


	} // episode == 1 && scene == 37







} 

// Removes gold from INV if is zero
void Calculate_Gold()
{

    if(current_gold != -1)
    {     
        if( player_inv_value[current_gold] <= 0)
        {
            player_inv_value[current_gold] = 0;
            player_inv[current_gold] = INV_NONE;
            player_inv_value1[current_gold] = 0;
            current_gold = -1;    
        } 
     
    } 
      
}
 
void Make_Tunnel(int index)
{
    if(index < 0)
		return;
 
    sprite[index].type = LAD;
    sprite[index].priority = 5;                              
    sprite[index].linked_sprite = MISSION_NONE;
    sprite[index].sector = LVL_TUNNEL;
    sprite[index].onCreate = 0;
    Generate_Object_Collision(index, REMOVE_COL);
    Set_Sprite(index, sprite[index].base_anim+2, ONCE, ANIM_SPRITE, ANIM_WALKING);
    
	if(trigger_counter >= 0)                    
	    trigger_list[trigger_counter] = index; 
    trigger_counter++;        
     
}

void Fire_Shoot( int shooter, float x1, float y1, float angle, int f_rate)
{
    
    float x=0.0f, y=0.0f;
    float deltax=0.0f, deltay=0.0f;
    float mid_x=0.0f, mid_y =0.0f;
    float mid_x1=0.0f, mid_y1 =0.0f;    
    float tar_x=0.0f, tar_y =0.0f; 
    float step=0.0f, distance=2.4f; 
    int iterations=0;
    bool test_success=false;

	if(f_rate <= 0)
	    f_rate = 1; 
    
    x = x1;  
    y = y1;
       
    deltax = cos(angle);     
    deltay = sin(angle);  
        
    deltax *= (float)LINE_OF_SIGHT;    
    deltay *= (float)LINE_OF_SIGHT;
        
    step = Node_Distance(x1, y1, x1+deltax, y1+deltay);
    
    if( step != 0)
        iterations = (int)(distance / step);
      
    if(iterations < 0)       
        iterations = 0;  

    for (int j = 0; j <= iterations; j++)
    {
        
    if(test_success == true) 
        break; 
                
    x += deltax; // Which is the mid_x
    y += deltay; // Which is the mid_y

    // Player...
    if(ply_id != -1) 
    {
        mid_x = sprite[ply_id].w+sprite[ply_id].box_width/2; 
        mid_y = sprite[ply_id].z+sprite[ply_id].box_height/2;    
    }
    
    if(ply_id != -1) 
    if(test_success == false)     
    if(sprite[ply_id].score > 0)                
    if(( x < mid_x + 0.05f )  
    &&( x > mid_x - 0.05f)                         
    &&( y < mid_y + 0.05f)  
    &&( y > mid_y - 0.05f) )        
    {
        Man_Shot(0, ply_id, shooter, BULLET_NONE, f_rate);
        test_success = true;
    }         

                
     
    } 
    
}

void Check_Patrol(int loop, int point, int next_point)
{
      float distance=0.0f;
      float mid_x=0.0f;    
      float mid_y=0.0f;
      float tar_x=0.0f;
      float tar_y=0.0f;
                
	  if(loop < 0 || point < 0 || next_point < 0)
		return;
               
      mid_x = sprite[loop].w+sprite[loop].box_width/2; 
      mid_y = sprite[loop].z+sprite[loop].box_height/2; 
        
      tar_x = points[point].x; 
      tar_y = points[point].y;   
                        
      distance = Node_Distance1(mid_x, mid_y, tar_x, tar_y);
       
      if(distance < 0.25f) 
      {   

          Find_Path(loop, points[next_point].x, points[next_point].y);  
          
          if(loop == 75)
              patroling1 = point;                           
          
          if(loop == 76)
              patroling2 = point; 
                           
      }        

}

void GraveStone()   
{
               
       ply_had_died = true;   
                        
       player_health = PLY_VITALITY;    
       
       old_health = player_health; 
                                              
       next_scene = true;  

	   ply_dead = false;  

       episode = 1;     
       scene = 25;  
       
       // Act2 cutscene...                          
       if(current_act != 1)
       if(global_objects[32] == GLOBAL_UNBEATEN)
       {
           episode = 1;
           scene   = 48;               
       }
       
       if(current_act == 3)
       if(global_objects[88] == GLOBAL_UNBEATEN)
       {
           episode = 1;
           scene   = 79;               
       } 
	   
       current_spawn = 0;      

}

int Get_Character_Scene()
{

	int success = 0; 

	if(current_char == CHAR_RIFLE)
       success = 4;
    if(current_char == CHAR_SHOTGUN)
   	   success = 34;

	return(success);

}
 

void Type_Key(int index, char A, char a)
{

           if(mouseleft == true || DX_SHOOT == true)
           if(sprite[index].alpha == 1.0)                    
           if(( mouseX < (sprite[index].w + sprite[index].box_width) )
           &&( mouseX > sprite[index].w)                            
           &&( mouseY < (sprite[index].z + sprite[index].box_height) )
           &&( mouseY > sprite[index].z))  
           {  
			   DX_SHOOT = false;
  
               mouseleft = false;   
                                         
			   if(shift_key == true) 
				   lvl_text[cur_letter]=A; 
			   else
				   lvl_text[cur_letter]=a;
           
			   if(capital_key > 0)
				   lvl_text[cur_letter]=A;
           
			   if(capital_key > 0 && shift_key == true)
				   lvl_text[cur_letter]=a;
                                         
			   if(cur_letter < input_cap)
			   {
				   cur_letter++;
				   type_sfx = true;
			   }
           }  

}

float GetIncSpeed(float value)
{ 
	float temp_speed=0.0f;
	 
	if((int)value >= 0) 
		temp_speed = 0.1f; 
	if((int)value >= 100)
		temp_speed = 0.2f; 
	if((int)value >= 250)
		temp_speed = 0.4f;  
	if((int)value >= 500)
		temp_speed = 0.6f; 
	if((int)value >= 750)
		temp_speed = 0.8f; 
	if((int)value >= 1000)
		temp_speed = 1.4f;  
	if((int)value >= 2000) 
		temp_speed = 3.0f; 
	if((int)value >= 3000)
		temp_speed = 4.5f; 
	if((int)value >= 4000)
		temp_speed = 5.0f;  
	if((int)value >= 5000) 
		temp_speed = 6.0f;  
	if((int)value >= 6000)  
		temp_speed = 7.0f; 
	if((int)value >= 7000)
		temp_speed = 8.0f; 
	if((int)value >= 8000)
		temp_speed = 9.0f;
	if((int)value >= 9000)
		temp_speed = 10.0f; 
	if((int)value >= 10000)
		temp_speed = 12.0f; 

	return(temp_speed);
}