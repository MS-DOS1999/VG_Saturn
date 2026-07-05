
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN 

#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>			// Header File For Standard Input/Output
#include <gl\gl.h> 
#include "globals.h"  
 
#define GUY_DOWN_LEFT      0
#define GUY_DOWN_MIDLEFT   1
#define GUY_DOWN_MIDDLE    2 
#define GUY_DOWN_MIDRIGHT  3 
#define GUY_DOWN_RIGHT     4

#define GUY_MIDDLE_LEFT      5 
#define GUY_MIDDLE_MIDLEFT   6
#define GUY_MIDDLE_MIDDLE    7  
#define GUY_MIDDLE_MIDRIGHT  8
#define GUY_MIDDLE_RIGHT     9

#define GUY_UP_LEFT      10
#define GUY_UP_MIDLEFT   11 
#define GUY_UP_MIDDLE    12    
#define GUY_UP_MIDRIGHT  13
#define GUY_UP_RIGHT     14

#define targets_spd            0.00020
#define targets_fast_spd       0.00030

#define HEALTHKIT_AMOUNT  40

#define TARGET_ENEMY   0
#define PAIN_RUMBLE  250

#define START_ANIM  0
#define IDLE_ANIM   1 
#define DIE_ANIM    2
#define STUN_ANIM   3
#define FIRE_ANIM   4    
#define COVER_ANIM  5 
  
#define S_START_ANIM  0
#define S_STUN_ANIM   1    
#define S_DIE_ANIM    2 
#define S_FIRE_ANIM   3  
 
   
#define GALLERY_CLIP_AMOUNT  6 
#define GALLERY_RELOAD_TIME 600 
#define GALLERY_RELOAD_TIMEC 600 

#define GALLERY_ENEMY_SHOOT_EASY   600 
#define GALLERY_ENEMY_SHOOT_NORMALC 900 
#define GALLERY_ENEMY_SHOOT_NORMAL  600 
 
#define GALLERY_GENERAL_SHOOT_EASY   1500
#define GALLERY_GENERAL_SHOOT_NORMAL 900   
#define GALLERY_GENERAL_SHOOT_HARD   750 

#define GALLERY_MAUSER_SHOOT_EASY    800    
#define GALLERY_MAUSER_SHOOT_NORMAL  1000  
#define GALLERY_MAUSER_SHOOT_HARD    800 


#define CORE_HEALTH_EASY   600  
#define CORE_HEALTH_NORMAL 600      
#define CORE_HEALTH_HARD   600

#define GALLERY_DAMAGE_EASY   5 
#define GALLERY_DAMAGE_NORMAL 6 
#define GALLERY_DAMAGE_HARD   8


#define TARGET_GUNNER   0 
#define TARGET_CHIEF    1
#define TARGET_SAILOR   2
#define TARGET_BOSS     3
#define TARGET_BUDDY    4


extern bool New_FX(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int i_value, int i_type, int state, int linked_sprite, int tex_id, int i_value1, int i_value2, int i_value3);
extern bool Has_This_Item(int type, int value);
extern void Remove_Item(int item_type, int item_value, int item_value1, bool remove_all);
extern void Message_Limits();
extern void Calculate_Gold();
extern void Create_Star_Effect(float x1, float y1, float size, int tex_id);
    
void Init_Gallery(int index);
void Run_Cards(int f_rate);
void Run_Medals(int f_rate);
void Set_Card(int index, int value);
void Calculate_Gallery_Bullets();
void Calculate_Gallery_Lifebar();
int Get_Number_Of_Item(int item_type, int item_value, int item_value1, bool remove_all);
void Hud_Face_Unit_Gallery(); 
 
int player_heal_timer=0;

#define GALLERY_LIMIT  75

int gallery_sequence[GALLERY_LIMIT];
int gallery_sequence_times[GALLERY_LIMIT];
int gallery_innocent[GALLERY_LIMIT];
int gallery_id[GALLERY_LIMIT];
int gallery_direction[GALLERY_LIMIT];
int gallery_pause[GALLERY_LIMIT];

int cards_popup[16];
int cards_popup_count=0;

int gallery_pause_count = 0;
int gallery_count = 0;
int gallery_index =0;  
int gallery_timer = 0;
int gallery_scene = 1;
int total_targets = 0;
int targets_killed = 0;

int prize_sequence = 0;
int prize_timer    = 0;
bool displaying_prize = false;
int card_start = 0;
int the_sprite=4;

int the_prize = 0;

int card_flash_timer1 = 0;

int pigeon_timer = 0;
bool pigeon_launched = false;
bool pigeon_mode = false;

int my_flash_timer = 0;

int gallery_clip=GALLERY_CLIP_AMOUNT;

bool flashing = false;

bool gallery_reloading = false;
int gallery_reload_timer = 0;
int gallery_reload_count = 0;
float gallery_health_width = 0.0;

float boss_health_width = 0.0;
int boss_total_score = 0;
int boss_gallery_health = 0;
int cannon_timer = 0;

int gallery_player_damage=10; 

int Gallery_Level = ENTRY_NONE;

bool gallery_finished = false;

bool gallery_paused = false;

float deck_angle=0.0f;

float start_33_x = 0.0;
float start_33_y = 0.0;

float start_34_x = 0.0;
float start_34_y = 0.0;

float start_35_x = 0.0;
float start_35_y = 0.0;

float Xspeed1 = 0.0;
float Xspeed2 = 0.0;
float Xspeed3 = 0.0;

float Yspeed1 = 0.0;
float Yspeed2 = 0.0;
float Yspeed3 = 0.0;

        
void Run_Gallery(int f_rate)
{
    bool on_the_belt = false;     
    int play_anim=0; 
    int base_anim=TARGET_ENEMY;
    float diff_x=0.0f, diff_y=0.0f;
    float x1=0.0f, y1=0.0f;
    float the_speed=0.0f;
    float deltax =0.0f,deltay =0.0f;
    bool shot_a_target = false; 
    int the_index=0;
    int rnd1 = 0;  
    float frnd = 0.0f;
    bool on_a_target=false;
	bool go_ahead=false;
    
    float temp_speed = 0.0f; 
    float temp_expand = 0.0f; 

	float gas_hit_width=0.0f;

	bool shot_vibrating=false;
 
	if(f_rate <= 0)
	    f_rate = 1;      

    if(gallery_title_sequence == 0)   
    {   
        if(!mode)
        if(screen_mode == SCREEN_WIDESCREEN || screen_mode == SCREEN_1610_WIDESCREEN)
        {
            sprite[17].x -= 0.2f;   
            sprite[17].w -= 0.2f;  
            sprite[18].x -= 0.2f; 
            sprite[18].w -= 0.2f;  
            
            sprite[1].x += 0.2f; 
            sprite[1].w += 0.2f;  
            sprite[21].x += 0.2f;  
            sprite[21].w += 0.2f;  
            sprite[20].x += 0.2f;  
            sprite[20].w += 0.2f;  
            sprite[19].x += 0.2f;  
            sprite[19].w += 0.2f;     

			if(scene == 23) 
			{ 
				sprite[28].y -= 0.02f;
				sprite[29].y -= 0.02f;  
			}

			if(scene == 73) 
			{ 
				sprite[31].y -= 0.02f;
				sprite[32].y -= 0.02f;
			} 
			 
			if(scene == 98)    
			{  
				sprite[30].y -= 0.018f;
				sprite[31].y -= 0.018f;
			}

        } 
        if(!mode)
        if(screen_mode == SCREEN_169_WIDESCREEN)
        {
            sprite[17].x -= 0.3f; 
            sprite[17].w -= 0.3f; 
            sprite[18].x -= 0.3f; 
            sprite[18].w -= 0.3f; 
            
            sprite[1].x += 0.3f;  
            sprite[1].w += 0.3f; 
            sprite[21].x += 0.3f; 
            sprite[21].w += 0.3f; 
            sprite[20].x += 0.3f;  
            sprite[20].w += 0.3f; 
            sprite[19].x += 0.3f; 
            sprite[19].w += 0.3f; 

			if(scene == 23)
			{ 
				sprite[28].y -= 0.02f;
				sprite[29].y -= 0.02f;  
			}

			if(scene == 73) 
			{ 
				sprite[31].y -= 0.02f;
				sprite[32].y -= 0.02f;
			} 
			 
			if(scene == 98)    
			{  
				sprite[30].y -= 0.018f;
				sprite[31].y -= 0.018f;
			}



        }
        
        memset(global_triggers, GLOBAL_UNBEATEN, sizeof(global_triggers) );
        
        sprite[20].status = IDLE;         
        Set_Sprite(20, 1, PLAY, ANIM_SPRITE, ANIM_WALKING);
      
        pigeon_mode = false;
                      
        Gallery_Level = ENTRY_NONE;
                      
        camY = 0.0f; 
         
        deck_angle=0;
                      
        memset( gallery_pause, 1000, sizeof(gallery_pause));              
        gallery_scene = 0;
      
        if(episode == 1 && scene == 8)
        {
            gallery_scene = 0;
            Gallery_Level = ENTRY_BATTLESHIP;
            stop_waves_sfx = true;
        }    
        if(episode == 1 && scene == 21) 
        {
            gallery_scene = 1; 
            Gallery_Level = ENTRY_BATTLESHIP;
        }               
        if(episode == 1 && scene == 22) 
        { 
            gallery_scene = 2;  
            Gallery_Level = ENTRY_BATTLESHIP;
        }               
        if(episode == 1 && scene == 23)
        {
            gallery_scene = 3;  
            Gallery_Level = ENTRY_BATTLESHIP;
        }   
                
        if(episode == 1 && scene == 69)
        {
            gallery_scene = 4;
            train_sfx=true;
            Gallery_Level = ENTRY_GARDENS;
        }               
        
        if(episode == 1 && scene == 70)
        {
            gallery_scene = 5;   
            Gallery_Level = ENTRY_GARDENS;
        }               
        
        if(episode == 1 && scene == 71)
        {
            gallery_scene = 6;
            Gallery_Level = ENTRY_GARDENS;
        }               
        
        if(episode == 1 && scene == 73)
        {
            gallery_scene = 7; 
            train_sfx=true;
            Gallery_Level = ENTRY_GARDENS;
        }               
         
        if(episode == 1 && scene == 95)  
        {
            exhaust_sfx = true;        
            gallery_scene = 8;    
            Gallery_Level = ENTRY_MISSILE; 
        }                 
        
        if(episode == 1 && scene == 96)
        {
            exhaust_sfx = true;       
            gallery_scene = 9;      
			sprite[15].spin = 0.785f;
			sprite[28].spin = 2.785f; 
			sprite[29].spin = -1.0f;               
            Gallery_Level = ENTRY_MISSILE;
        }                 
        
        if(episode == 1 && scene == 97)
        {
            exhaust_sfx = true;
			sprite[15].spin = 0.785f; 
			sprite[11].spin = -2.1f;          
            gallery_scene = 10;  
            Gallery_Level = ENTRY_MISSILE;
        }                 
        
        if(episode == 1 && scene == 98)   
        {
            exhaust_sfx = true;         
            gallery_scene = 11; 
			sprite[9].spin = -2.785f; 
			sprite[11].spin = 1.0f;   
			sprite[15].spin = -0.785f; 
			sprite[10].spin = 1.7f;  
			sprite[16].spin = -0.4f;     
            Gallery_Level = ENTRY_MISSILE;
            
            Set_Sprite(32, 5, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
            
            hatch_sfx = true;
            
            if(current_difficulty == EASY_MODE)
                sprite[32].score = CORE_HEALTH_NORMAL;
            if(current_difficulty == NORMAL_MODE)
                sprite[32].score = CORE_HEALTH_NORMAL;
            if(current_difficulty == HARD_MODE)
                sprite[32].score = CORE_HEALTH_HARD; 

                
        }     
                
        if(episode == 1 && scene == 112)  
        {
            pigeon_mode = true;
            Gallery_Level = ENTRY_PIGEON; 
            gallery_scene = 12;
            woods_sfx = true;  
        }
         
        if(episode == 1 && scene == 113)
        { 
            pigeon_mode = true;
            Gallery_Level = ENTRY_PIGEON;
            gallery_scene = 13;  
        }
        
        if(episode == 1 && scene == 114)
        {
            pigeon_mode = true;
            Gallery_Level = ENTRY_PIGEON;
            gallery_scene = 14;   
        }
        
        if(episode == 1 && scene == 115)
        {
            pigeon_mode = true; 
            Gallery_Level = ENTRY_PIGEON;
            gallery_scene = 15;  
            pigeon_round++;
        }
        if(episode == 1 && scene == 146)
        {
            gallery_scene = 16;
            Gallery_Level = ENTRY_BUNKER;
            stop_waves_sfx = true; 
        }      

        if(episode == 1 && scene == 179)
        {
            gallery_scene = 17;  
            Gallery_Level = ENTRY_UNDERGROUND;
            stop_waves_sfx = true;
        }          
                                                                                                                                             
        gallery_prize = NO_PRIZE;
        gallery_index = 0; 
        
        gallery_pause_count = 0;  
        
        gallery_health_width = sprite[21].width;
        
        if(gallery_scene == 3)
            boss_health_width = sprite[29].width;
        
        if(gallery_scene == 11)
        {
            boss_health_width = sprite[31].width;
            
            sprite[22].alpha = 0.0f; 
            sprite[23].alpha = 0.0f;
            sprite[24].alpha = 0.0f;
            
            start_33_x = sprite[22].x;  
            start_33_y = sprite[22].y;
                        
            start_34_x = sprite[23].x; 
            start_34_y = sprite[23].y;
            
            start_35_x = sprite[24].x; 
            start_35_y = sprite[24].y;            
        }
                    
        if(gallery_scene == 7) 
        {
            boss_health_width = sprite[32].width;
            
            sprite[33].alpha = 0.0f; 
            sprite[34].alpha = 0.0f;
            sprite[35].alpha = 0.0f;
            
            start_33_x = sprite[33].x;  
            start_33_y = sprite[33].y;
                        
            start_34_x = sprite[34].x; 
            start_34_y = sprite[34].y;
            
            start_35_x = sprite[35].x; 
            start_35_y = sprite[35].y;
            
            cannon_timer = (int)TimerGetTime() + 6000;
            
        } 

		gallery_clip=GALLERY_CLIP_AMOUNT;

//        gallery_clip = 6;
        gallery_player_damage = 10;  
        
        if(st_gallery == 0)
        {
            gallery_clip = 5;
            gallery_player_damage = 10; 
        }
        if(st_gallery == 1) 
        {
            gallery_clip = 6;
            gallery_player_damage = 15;
        } 
        if(st_gallery == 2)
        {
            gallery_clip = 6;
            gallery_player_damage = 10;
        }
        if(st_gallery == 3)
        {
            gallery_clip = 8;
            gallery_player_damage = 30;
        }
                   
        if(pigeon_mode == true) 
        {
           sprite[28].alpha = 1.0f; 
           sprite[32].alpha = 1.0f;
           sprite[33].alpha = 1.0f;       
           sprite[28].angle = 0;   
           sprite[32].angle = 0;
           sprite[33].angle = 0;    
           sprite[28].grab_switch = true;
           sprite[32].grab_switch = true;
           sprite[33].grab_switch = true;
           
           Set_Sprite(28, 0, LOOP, ANIM_SPRITE, ANIM_WALKING);  
           Set_Sprite(32, 0, LOOP, ANIM_SPRITE, ANIM_WALKING);
           Set_Sprite(33, 0, LOOP, ANIM_SPRITE, ANIM_WALKING);
                 
           pigeon_launched = false;
           pigeon_timer = (int)TimerGetTime() + 3000;   
                               
           gallery_clip = 3;
           
        } 
        
        gallery_reloading = false;
//        gallery_sfx  = true;
        
        gallery_paused = false;
        
        gallery_timer = 0;
        
        gallery_finished = false;
                        
        total_targets = 0;
        targets_killed = 0;
        the_sprite = 4;
                    
        Init_Gallery(gallery_scene); 
        
        for(int i = 0;i < no_sprites;i++)
        {  
          if(sprite[i].type == FE_TARGET)
          {

           sprite[i].grab_switch = false;
           sprite[i].mov_x = sprite[i].x;
           sprite[i].end_x = sprite[i].w;
           sprite[i].sector = RESET;
           sprite[i].alpha = 0.0f; 
           sprite[i].status = MAN_DOWN;
           
          } 
          if(sprite[i].type == FE_SHOOTABLE && gallery_scene != 11)
          {
              sprite[i].score = 3;
          }
        }
         
        gallery_timer = (int)TimerGetTime() + 3000; 
        
        if(f_rate > 100)
            f_rate = 100;
                                
        gallery_title_sequence++;       
        
    }      
        
    // Start the Gallery
    if(gallery_title_sequence == 1)
    {     
            
        // Start the Gallery
        if((int)TimerGetTime() > gallery_title_timer)
        if(next_scene == false)
        if(gallery_finished == true)
        {   
            
            episode = 1;   
            
            if(gallery_scene == 0) 
                scene = 21; 
            if(gallery_scene == 1)
                scene = 22;  
            if(gallery_scene == 2) 
            {
            //    scene = 23;    
                        
                episode = 1;      
                scene = 40;    
                
                next_scene = true;
                                                
            } 
            if(gallery_scene == 3)    
            {
                             
                global_objects[17] = GLOBAL_BEATEN; 
                        
                episode = 1;      
                scene = 41;  
               
                next_scene = true;
                mouseleft = false; 
                sprite[1].grab_switch = false;                
            }  
            if(gallery_scene == 4) 
            {
       
                episode = 1;      
                scene = 72;   
                                                
            }             
            if(gallery_scene == 5)  
                scene = 71;  
            if(gallery_scene == 6) 
            { 
        
                episode = 1;      
                scene = 72;    
                
                next_scene = true; 
                                                
            } 
            if(gallery_scene == 7) 
            { 
         
                episode = 1;       
                scene = 74;    // was 74
                
                next_scene = true; 
                                                
            }   
            if(gallery_scene == 8) 
            { 
        
                episode = 1;        
                scene = 96;    
                    
                next_scene = true; 
                                                
            }     
            if(gallery_scene == 9) 
            {  
        
                episode = 1;         
                scene = 97;    
                
                next_scene = true; 
                                                 
            }    
            if(gallery_scene == 10) 
            {  
        
                episode = 1;         
                scene = 123;    
                
                next_scene = true; 
                                                
            }   
            if(gallery_scene == 11) 
            {  
        
                episode = 1;         
                scene = 99;    
                
                next_scene = true; 
                                                 
            }    
            if(gallery_scene == 16)    
            {

                episode = 1;      
                scene = 145;   
               
                next_scene = true;
                           
            }     
            if(gallery_scene == 17) 
            {  
        
                episode = 3;         
                scene = 16;     
                
                current_spawn = 1;
                
                next_scene = true; 
                                                
            }                                                                 
            if(pigeon_mode == true) 
            {  
        
                episode = 3;         
                scene = 29;    
                
                current_spawn = 3;
                
                next_scene = true; 
                                                
            }      
                                     
            deck_angle=0;
            
            next_scene = true;       
            
        } 
             
        Calculate_Gallery_Bullets();
        Calculate_Gallery_Lifebar();
        
        if(pigeon_mode == true)  
        {
                                                                  
           counter[1].x = -0.92f;        
           counter[1].y =  0.66f;  
           counter[1].width = 0.016f; 
           counter[1].height = 0.048f;
           counter[1].alpha = 1.0f;  
           
           if( targets_shot < 10)
               sprintf( counter[1].word, "TARGETS^_%i-24", targets_shot);             
           else
               sprintf( counter[1].word, "TARGETS^%i-24", targets_shot);             
                        
        }
        
                               
        // 9 - 8 - 7 - 2 
        if(pigeon_mode == false)
		if(gallery_index >= 0 && gallery_index < GALLERY_LIMIT)
        if(gallery_index < gallery_count)
        if(gallery_finished == false && gallery_paused == false)
        if((int)TimerGetTime() >  gallery_timer)
        {
                                          
            the_sprite = gallery_sequence[gallery_index];
            
            if(gallery_scene == 11) 
            { 
                rnd1 = rand()%7; 
                
                if(rnd1 == 0)the_sprite = 5;
                if(rnd1 == 1)the_sprite = 4;
                if(rnd1 == 2)the_sprite = 7;
                if(rnd1 == 3)the_sprite = 6;
                if(rnd1 == 4)the_sprite = 8;
                if(rnd1 == 5)the_sprite = 2;
                if(rnd1 == 6)the_sprite = 13; 
            }
                 
            if(gallery_index < gallery_count) 
            if(the_sprite >= 0 && the_sprite != 0)     
            {
                sprite[the_sprite].grab_switch = true;
                sprite[the_sprite].sector = gallery_direction[gallery_index];
                
                if(gallery_innocent[gallery_index] == TARGET_SAILOR)
                {
                    sprite[the_sprite].x = sprite[the_sprite].mov_x;  
                    sprite[the_sprite].w = sprite[the_sprite].end_x;
                } 
                 
                sprite[the_sprite].alpha = 1.0f;
                sprite[the_sprite].flash_timer = 0;
                
                sprite[the_sprite].status = GROUND_SPAWN; 
                 
                sprite[the_sprite].rank = 0;
                sprite[the_sprite].all_timer = (int)TimerGetTime() + 500;
                
                if(gallery_id[gallery_index] != -1)
                    sprite[the_sprite].id = gallery_id[gallery_index];
                
                if(gallery_innocent[gallery_index] == TARGET_BUDDY)                
                     sprite[the_sprite].sector_action = UNIT_BUDDY;
                                     
                if(gallery_innocent[gallery_index] == TARGET_GUNNER)                
                     sprite[the_sprite].sector_action = UNIT_GUNNER;
                
                if(gallery_innocent[gallery_index] == TARGET_CHIEF)                
                     sprite[the_sprite].sector_action = UNIT_CHIEF;
                
                if(gallery_innocent[gallery_index] == TARGET_BOSS)                
                     sprite[the_sprite].sector_action = UNIT_GENERAL;
                                     
                if(gallery_innocent[gallery_index] == TARGET_SAILOR)                
                     sprite[the_sprite].sector_action = UNIT_SAILOR;
                                                          
                if(sprite[the_sprite].sector_action == UNIT_GENERAL)
                    sprite[the_sprite].bomb_timer = (int)TimerGetTime() + 2000;
                                                          
                if(sprite[the_sprite].sector_action == UNIT_CHIEF)
                    sprite[the_sprite].bomb_timer = (int)TimerGetTime() + 1500;
                                    
                if(sprite[the_sprite].sector_action == UNIT_GUNNER)
                    sprite[the_sprite].bomb_timer = (int)TimerGetTime() + 3000;
                
                if(sprite[the_sprite].sector_action == UNIT_SAILOR)
                    sprite[the_sprite].bomb_timer = (int)TimerGetTime() + 6000;
                
                if(sprite[the_sprite].sector_action == UNIT_BUDDY)   
                    sprite[the_sprite].bomb_timer = (int)TimerGetTime() + 3000;                    
                     
                if(sprite[the_sprite].sector_action == UNIT_SAILOR) 
                {
                    Set_Sprite(the_sprite, S_START_ANIM, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                    sprite[the_sprite].score = 50;                       
                }   
                else    
                {
                    Set_Sprite(the_sprite, START_ANIM, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); 
                    sprite[the_sprite].score = 10;                    
                }  
                
                if(sprite[the_sprite].sector_action == UNIT_GENERAL)
                {
                    sprite[the_sprite].score = 30; 
                           
                //    if(gallery_scene == 3)
                    laugh_sfx = true;
                        
                }            
                if(gallery_scene == 11)                                              
                if(sprite[the_sprite].sector_action == UNIT_GENERAL)
                    sprite[the_sprite].score = 10;   
                     
                                        
            }         
                                                              
            gallery_index++;  
                
            gallery_timer = (int)TimerGetTime() + gallery_sequence_times[gallery_index];

                                         
        }  
                      
    } 
     
    if( gallery_finished == false)
    if(targets_killed == gallery_count)  
    { 
        if(gallery_scene != 11) 
        {              
            gallery_finished = true;
            gallery_title_timer = (int)TimerGetTime() + 10;
        }
        else    
        {
            gallery_index = 0;  
            targets_killed = 0;  
            gallery_pause_count = 0;
            gallery_paused = false;
        //    gallery_timer = (int)TimerGetTime() + gallery_sequence_times[gallery_index];  
            gallery_timer = 0;
           
        }
    }
     
    if(gallery_scene == 11)        
    if(boss_gallery_health <= 0) 
    {             
        gallery_finished = true;
        gallery_title_timer = (int)TimerGetTime() + 10;
        
        episode = 1;         
        scene = 99;    
                
        next_scene = true; 
    }
    
    if(gallery_scene == 11)
    {
                      
        if(gallery_index == 6)  
        {
            if(sprite[32].grab_switch == false) 
            if(sprite[32].anim != 4)
            {
                hatch_sfx = true; 
                sprite[32].grab_switch = true;               
                Set_Sprite(32, 4, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Opening...            
            }
        }             
        else 
        {
            sprite[32].grab_switch = false;
            if(sprite[32].anim != 5)
            { 
                hatch_sfx = true;                
                Set_Sprite(32, 5, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Closing...
            }
        } 
  
        if(sprite[32].anim != 4 || sprite[32].cur == 3) 
        if(sprite[32].grab_switch == true) 
        {    
    
            if(sprite[32].score == boss_total_score && sprite[32].anim != 0) 
                Set_Sprite(32, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);                           
            if(sprite[32].score >= boss_total_score/2 && sprite[32].score < boss_total_score && sprite[32].anim != 1)
                Set_Sprite(32, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);               
            if(sprite[32].score >= boss_total_score/4 && sprite[32].score < boss_total_score/2 && sprite[32].anim != 2)
                Set_Sprite(32, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);               
            if(sprite[32].score < boss_total_score/4 && sprite[32].anim != 3) 
                Set_Sprite(32, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);  
        }
    }
    
    if(Gallery_Level == ENTRY_BATTLESHIP)
    { 
        temp_speed  = 0.00003f*(float)f_rate;
         
        deck_angle += 0.001f*(float)f_rate; 
        
        if(deck_angle >= 6.28f)  
            deck_angle = 0; 
                                        
        deltay = sin(deck_angle-3.14f); // Was 1.2f         
                      
        deltay *= temp_speed;                                     
    } 
    
    if(Gallery_Level == ENTRY_GARDENS)
    { 
        temp_speed  = 0.00001f*(float)f_rate;
         
        deck_angle+=0.003f*(float)f_rate;
          
        if(deck_angle >= 6.28f)  
            deck_angle = 0; 
                                        
        deltay = sin(deck_angle-3.14f); // Was 1.2f         
                      
        deltay *= temp_speed;    
        
        temp_speed  = 0.00007f*(float)f_rate;                                 
    }     
	 
	// Zero gravity...
		for(int i =0 ;i< no_sprites;i++)
		if( i < TOTAL_NO_SPRITES)
		if(sprite[i].type == FE_CARD)
		{

		go_ahead=true; 

		if(sprite[i].status == STUNNED)
			sprite[i].angle -= 0.08f*(float)f_rate;
		else
			sprite[i].angle -= 0.02f*(float)f_rate; 
 
		if(sprite[i].status == STUNNED)  
			temp_speed  = 0.0015f*(float)f_rate;  
		else
			temp_speed  = 0.0005f*(float)f_rate;  
                   
     	deltax = cos(sprite[i].spin); // Was 1.2f          
	    deltay = sin(sprite[i].spin); // Was 1.2f                            
                
	    deltax *= temp_speed;                                       
	    deltay *= temp_speed;                           

		x1 = sprite[i].w + deltax;  
		y1 = sprite[i].z + deltay;
		
		if(y1 >= sprite[14].z + sprite[14].box_height)
		{
			if(deltax > 0)
			    sprite[i].spin -= 1.57f;
			else
			    sprite[i].spin += 1.57f; 
		
			go_ahead=false;	
		}
		
		if(y1 <= sprite[14].z)
		{
			if(deltax > 0)
			    sprite[i].spin += 1.57f;
			else
			    sprite[i].spin -= 1.57f;
			go_ahead=false;	 
		}
		
		if(x1 >= sprite[14].w + sprite[14].box_width)
		{
			if(deltay > 0)
			    sprite[i].spin += 1.57f; 
			else
			    sprite[i].spin -= 1.57f; 

			go_ahead=false;	
		}
		
		if(x1 <= sprite[14].w)
		{
			if(deltay > 0)
			    sprite[i].spin -= 1.57f; 
			else
			    sprite[i].spin += 1.57f; 

			go_ahead=false;	
		}

		if( sprite[i].spin <= -3.14f)
		    sprite[i].spin += 6.28f;

		if(go_ahead==true) 
		{ 
			sprite[i].x += deltax;  
			sprite[i].y += deltay;
			sprite[i].w += deltax;  
			sprite[i].z += deltay;
		}		

        // Shot a target... 
        if(gallery_clip > 0)           
        if(on_the_belt == false) 
        if(mouseleft == true || DX_SHOOT == true)   
        if(gallery_reloading == false) 
        if(sprite[i].type == FE_CARD)
        if(( mouseX < (sprite[i].w + sprite[i].box_width) )
        &&( mouseX > sprite[i].w)                            
        &&( mouseY < (sprite[i].z + sprite[i].box_height) )
        &&( mouseY > sprite[i].z)) 
        {    
			DX_SHOOT=false;
			sprite[i].status = STUNNED;  
            sprite[i].all_timer = (int)TimerGetTime() + 3000;
			ric2_sfx=true;
			mouseleft=false;
		}
			
		if(sprite[i].type == FE_CARD)
		if(sprite[i].status == STUNNED)
		if((int)TimerGetTime() > sprite[i].all_timer)
		{
			sprite[i].status = IDLE;   
            sprite[i].all_timer = 0;
		}

		}
           
    if(Gallery_Level == ENTRY_BATTLESHIP || Gallery_Level == ENTRY_GARDENS) 
    for(int i =0 ;i< no_sprites;i++)
	if( i < TOTAL_NO_SPRITES)
    if( i != 17 && i != 18 && i != 0 && i != 20 && i != 19 && i != 21 && i != 1)
    if( (i != 28 && i != 29) || gallery_scene != 3)
    if( (i != 31 && i != 32) || gallery_scene != 7)
    {
        sprite[i].y += deltay;      
        sprite[i].z += deltay;       
    }    
        
    if(fade > 0.7) 
    if(Gallery_Level == ENTRY_GARDENS && gallery_scene != 7)   
    for(int i =0 ;i< no_sprites;i++)
	if( i < TOTAL_NO_SPRITES)
    if( i != 17 && i != 18 && i != 0 && i != 20 && i != 19 && i != 21 && i != 1 && i != 31 && i != 3 && i != 49)
    if( (i != 28 && i != 29) || gallery_scene != 3)
    {

        sprite[i].x -= temp_speed;       
        sprite[i].w -= temp_speed;

		if(sprite[55].w < sprite[3].w) 
			gallery_finished = true;
        
    }     

    if(Gallery_Level == ENTRY_MISSILE)   
	if((int)TimerGetTime() > my_flash_timer)
    for(int i=0 ;i<original_no_sprites;i++)
	if( i < TOTAL_NO_SPRITES)
    {

        deltay = 0.005f;        
		 
		vibrate ^= 1; 

		if( i != 17 && i != 18 && i != 0 && i != 20 && i != 19 && i != 21 && i != 1)
		if( (i != 28 && i != 29) || gallery_scene != 3)
		if( (i != 30 && i != 31) || gallery_scene != 11)
        if(vibrate == true)  
        {
            sprite[i].y += deltay;     
            sprite[i].z += deltay;
        }
        else 
        {
            sprite[i].y -= deltay;    
            sprite[i].z -= deltay;
        }        

    } 
         
    if((int)TimerGetTime() > my_flash_timer)
    {    
          if(flashing == false)
             flashing = true;
          else
             flashing = false;

          my_flash_timer = (int)TimerGetTime() + 50;
                            
    } 
 
	if( gallery_pause_count >= 0 && gallery_pause_count < GALLERY_LIMIT)
    if(targets_killed == gallery_pause[gallery_pause_count])
        gallery_pause_count++;
    
	if( gallery_pause_count >= 0 && gallery_pause_count < GALLERY_LIMIT)
    if(gallery_index == gallery_pause[gallery_pause_count])
        gallery_paused = true;      
    else
        gallery_paused = false;          
           
    shot_a_target = false;   
    
    if(pigeon_mode == true)
    if((int)TimerGetTime() > pigeon_timer && pigeon_launched == true)
    {
        if(gallery_scene == 12)
        {
            episode = 1;         
            scene = 113;    
            
            next_scene = true;             
        }
        if(gallery_scene == 13)
        {
            episode = 1;         
            scene = 114;    
            
            next_scene = true;            
        }
        if(gallery_scene == 14)
        {
            episode = 1;         
            scene = 115;     
            
            next_scene = true;            
        }
        if(gallery_scene == 15)
        {
            episode = 1;           
            scene = 112;    
            
            next_scene = true;            
        } 
        
        if(pigeon_round == 2)
        {
    
            episode = 3;         
            scene = 29;    
            
            current_spawn = 3;
            
            next_scene = true; 
                                    
        }
        
    }
    
    // Run Clay pigeon code...
    if(pigeon_mode == true)
    if((int)TimerGetTime() > pigeon_timer || pigeon_launched == true)
    { 
          
        if(pigeon_launched == false)
        {             
            pigeon_launched = true;           
            splash_sfx = true;
            pigeon_timer = (int)TimerGetTime() +4500;
            
           
           if(gallery_scene == 13)
           {                
               frnd = (float)(rand()%16);
               if(frnd != 0)  
                  frnd /= 10000;  
                    
               Xspeed1 = 0.0006f+frnd;

               frnd = (float)(rand()%16); 
               if(frnd != 0)
                   frnd /= 10000; 
                                       
               Xspeed2 = 0.0004f+frnd;  
               
               frnd = (float)(rand()%16); 
               
               if(frnd != 0)
                   frnd /= 10000;   
               Xspeed3 = 0.0002f+frnd; 

               frnd = (float)(rand()%10); 
               if(frnd != 0) 
                   frnd /= 10000;    
                                                                         
               Yspeed1 = 0.0002f+frnd;                
 
               frnd = (float)(rand()%10); 
               if(frnd != 0) 
                   frnd /= 10000;   
                                                                         
               Yspeed2 = 0.0002f+frnd;

               frnd = (float)(rand()%10); 
               if(frnd != 0) 
                   frnd /= 10000;    
                                                                         
               Yspeed3 = 0.0002f+frnd;                             
           }    
            if(gallery_scene == 14)
           {                
               frnd = (float)(rand()%16);
               if(frnd != 0)  
                  frnd /= 10000;  
                    
               Xspeed1 = 0.0006f+frnd;

               frnd = (float)(rand()%16); 
               if(frnd != 0)
                   frnd /= 10000; 
                                       
               Xspeed2 = 0.0004f+frnd;  
               
               frnd = (float)(rand()%16); 
               
               if(frnd != 0)
                   frnd /= 10000;   
               Xspeed3 = 0.0002f+frnd; 

               frnd = (float)(rand()%10); 
               if(frnd != 0) 
                   frnd /= 10000;    
                                                                         
               Yspeed1 = 0.0002f+frnd;                
 
               frnd = (float)(rand()%10); 
               if(frnd != 0) 
                   frnd /= 10000;   
                                                                         
               Yspeed2 = 0.0002f+frnd;

               frnd = (float)(rand()%10); 
               if(frnd != 0) 
                   frnd /= 10000;    
                                                                         
               Yspeed3 = 0.0002f+frnd;                             
           }     
           if(gallery_scene == 15)
           {                
               frnd = (float)(rand()%16);
               if(frnd != 0)  
                  frnd /= 10000;  
                    
               Xspeed1 = 0.0006f+frnd;

               frnd = (float)(rand()%16); 
               if(frnd != 0)
                   frnd /= 10000;  
                                       
               Xspeed2 = 0.0006f+frnd;  
               
               frnd = (float)(rand()%16); 
               
               if(frnd != 0)
                   frnd /= 10000;   
               Xspeed3 = 0.0002f+frnd; 

               frnd = (float)(rand()%10); 
               if(frnd != 0) 
                   frnd /= 10000;    
                                                                         
               Yspeed1 = 0.0002f+frnd;                
 
               frnd = (float)(rand()%10); 
               if(frnd != 0) 
                   frnd /= 10000;   
                                                                         
               Yspeed2 = 0.0002f+frnd;

               frnd = (float)(rand()%10); 
               if(frnd != 0) 
                   frnd /= 10000;    
                                                                         
               Yspeed3 = 0.0002f+frnd;                             
           }     
                               
        }
                     
        for(int i = 0;i<=no_sprites;i++)
		if( i < TOTAL_NO_SPRITES)
        if(i == 28 || i == 32 || i == 33)
        if(sprite[i].alpha == 1.0)    
        {   
           
           if(gallery_scene == 12)
           {                           
               if(i == 33) 
                   sprite[i].x += 0.0001f*(float)f_rate;
               if(i == 28)
                   sprite[i].x -= 0.0001f*(float)f_rate; 
                                
               temp_speed = 0.001f*(float)f_rate; 
                
               if(i == 32)
                   temp_speed = 0.0013f*(float)f_rate; 
                   
               temp_expand = 0.00002f*(float)f_rate;
           }
           
           if(gallery_scene == 13)
           {                
                                         
               if(i == 33)    
               {
                   sprite[i].x += Xspeed1*(float)f_rate;
                   temp_speed = Yspeed1*(float)f_rate;
               } 
               if(i == 28)
               {
                   sprite[i].x += Xspeed2*(float)f_rate; 
                   temp_speed = Yspeed2*(float)f_rate;
                   
               }
               if(i == 32) 
               {               
                   sprite[i].x += Xspeed3*(float)f_rate;
                   temp_speed = Yspeed3*(float)f_rate; 
               }   

               temp_expand = 0.00004f*(float)f_rate;
           }    
            
           if(gallery_scene == 14)
           {                 
                                         
               if(i == 33)  
               {
                   sprite[i].x -= Xspeed1*(float)f_rate;
                   temp_speed = Yspeed1*(float)f_rate;
               }
               if(i == 28)
               {
                   sprite[i].x -= Xspeed2*(float)f_rate; 
                   temp_speed = Yspeed2*(float)f_rate;
               }
               if(i == 32) 
               {
                   sprite[i].x -= Xspeed3*(float)f_rate;
                   temp_speed = Yspeed3*(float)f_rate; 
               }                    
                               
               temp_expand = 0.000045f*(float)f_rate;
               
           }   
           
           if(gallery_scene == 15)
           {                 
                                         
               if(i == 33)  
               {
                   sprite[i].x -= Xspeed1*(float)f_rate;
                   temp_speed = Yspeed1*(float)f_rate;
               }
               if(i == 28) 
               {
                   sprite[i].x += Xspeed2*(float)f_rate; 
                   temp_speed = Yspeed2*(float)f_rate;
               }
               if(i == 32) 
               {
               //    sprite[i].x -= Xspeed3*(float)f_rate;
                   temp_speed = Yspeed3*(float)f_rate; 
               }                    
                               
               temp_expand = 0.000045f*(float)f_rate;
               
           }  
                                       
           sprite[i].y += cos(sprite[i].angle )*(temp_speed);
                 
           sprite[i].angle += 0.001f*(float)f_rate; 
                           
           if(sprite[i].angle > 3.14f)         
               sprite[i].angle = 3.14f;   
            
           sprite[i].x += temp_expand/2; 
           sprite[i].width -= temp_expand;
            
           sprite[i].y += temp_expand/2;  
           sprite[i].height -= temp_expand;  
           
           sprite[i].w = sprite[i].x;
           sprite[i].z = sprite[i].y;
           
           sprite[i].box_width = sprite[i].width;
           sprite[i].box_height = sprite[i].height;
           
        }                      
                     
                     
                     
    }                
          
    // Run Gas Attack...
    if(gallery_scene == 11 && sprite[32].score < boss_total_score/2 && gallery_index == 6)    
    {
                       
        if((int)TimerGetTime() > cannon_timer)
        {
            rnd1 = rand()%2; 
            
            the_index = 22;
                               
            if(rnd1 == 0)
                the_index = 22;
            if(rnd1 == 1) 
                the_index = 23; 
            if(rnd1 == 2)
                the_index = 24;
                 
            if(sprite[the_index].alpha == 0.0f)
            {         
                                
                sprite[the_index].alpha = 1.0f; 
                
                sprite[the_index].width = sprite[24].width;
                sprite[the_index].height = sprite[24].height;
                
                sprite[the_index].angle = 0;  
                
                if(the_index == 22) 
                {
                    sprite[the_index].x = start_33_x;    
                    sprite[the_index].y = start_33_y; 
                    Set_Sprite(29, 1, PLAY, ANIM_SPRITE, ANIM_WALKING);
                }                 
                if(the_index == 23)
                {
                    sprite[the_index].x = start_34_x;  
                    sprite[the_index].y = start_34_y; 
                    Set_Sprite(28, 1, PLAY, ANIM_SPRITE, ANIM_WALKING);
                } 
                 
                if(the_index == 24)
                {
                    sprite[the_index].x = start_35_x;  
                    sprite[the_index].y = start_35_y; 
                    Set_Sprite(30, 1, PLAY, ANIM_SPRITE, ANIM_WALKING);
                }           
                      
                sprite[the_index].w = sprite[the_index].x + (sprite[24].w - sprite[24].x);   
                sprite[the_index].z = sprite[the_index].y + (sprite[24].z - sprite[24].y); 
                  
                sprite[the_index].box_width = sprite[24].width;
                sprite[the_index].box_height = sprite[24].height;  
                         
                sprite[the_index].grab_switch = true;             
                 
                splash_sfx = true;
             
            } 
            
            cannon_timer = (int)TimerGetTime()+5000;   
            
            if(boss_gallery_health < boss_total_score / 2)
                cannon_timer =  (int)TimerGetTime()+3000;  
            
            if(boss_gallery_health < boss_total_score / 3)
                cannon_timer =  (int)TimerGetTime()+2000; 
                            
            if(boss_gallery_health < boss_total_score / 4) 
                cannon_timer =  (int)TimerGetTime()+1500;  
             
        } // if((int)TimerGetTime() > cannon_timer)

	}

    // Run Gas Attack...
    if(gallery_scene == 11 && sprite[32].score < boss_total_score/2)    
    {         
        for(int i = 22;i<=23;i++)
        { 
        
        if(sprite[i].alpha == 1.0f)  
        {    
            
           if(i == 22)  
               sprite[i].x += 0.00005f*(float)f_rate;
           if(i == 23)
               sprite[i].x -= 0.00005f*(float)f_rate; 
           
		   if(!CONTROLLER)
		   {
			   temp_speed = 0.001f;
			   temp_expand = 0.0004f;  
		   }
		   else
		   {
			   temp_speed = 0.0005f;
			   temp_expand = 0.0003f;  
		   }

           
           if(i == 24)   
               sprite[i].y += 0.00005f*(float)f_rate;
                 
           sprite[i].angle += 0.001f*(float)f_rate; 
                           
           if(sprite[i].angle > 3.14f)         
               sprite[i].angle = 3.14f; 
             
           if(i == 22)     
           {
               sprite[i].x += cos(sprite[i].angle)*temp_speed*(float)f_rate;  
               sprite[i].y += sin(sprite[i].angle)*temp_speed*(float)f_rate; 
           }
           else 
           {
               sprite[i].x -= cos(sprite[i].angle)*temp_speed*(float)f_rate;  
               sprite[i].y -= sin(sprite[i].angle)*temp_speed*(float)f_rate; 
           }           
           
           sprite[i].x -= temp_expand/2; 
           sprite[i].width += temp_expand; 
            
           sprite[i].y -= temp_expand/2; 
           sprite[i].height += temp_expand;  
           
           sprite[i].w = sprite[i].x;
           sprite[i].z = sprite[i].y;
           
           sprite[i].box_width = sprite[i].width;
           sprite[i].box_height = sprite[i].height;
          
             
        }    
		  
        if(sprite[i].alpha == 1.0)    
        if( ( (sprite[i].y+sprite[i].height/2) >= sprite[14].y+sprite[14].height ) || ((sprite[i].y+sprite[i].height/2) < sprite[14].y)  )
        { 

			reset_player_heal_timer = (int)TimerGetTime() + REGEN_RESET_TIME;

            if(current_difficulty == EASY_MODE)
                old_health -= GALLERY_DAMAGE_EASY;
            if(current_difficulty == NORMAL_MODE)
                old_health -= GALLERY_DAMAGE_NORMAL;
            if(current_difficulty == HARD_MODE)
                old_health -= GALLERY_DAMAGE_HARD;
                                            
            sprite[20].status = STUNNED; 
            sprite[20].all_timer = (int)TimerGetTime() + 250;
                   
            red_swipe = true; 
            swipe_color = COLOR_RED; 
            red_timer = (int)TimerGetTime() + 100;

			#if INCLDUE_360_CONTROLLER  == 1
				VIBRATE_LEFT(52000, PAIN_RUMBLE);  
				VIBRATE_RIGHT(52000, PAIN_RUMBLE);
			#endif

			shot_vibrating = true;

                                  
            New_FX(sprite[i].x, sprite[i].y,  sprite[i].x, sprite[i].y, 0, PLAY, sprite[i].width, sprite[i].height, sprite[i].width, sprite[i].height, 0, GFX, 1.0, 0, 0, FX_STATIC, i, 22, 0, 0, -1);
            sprite[i].grab_switch = false;
            sprite[i].alpha = 0.0f;    
        //    boss_sfx = true;      
            cough_sfx = true;        
        //    sight_sfx = true;  
                                    
        }
          
        }   // for(int i = 22;i<=23;i++)     
                     
    }
             
    // Run cannonball code...
    if(gallery_scene == 7)
    {
                      
        if((int)TimerGetTime() > cannon_timer)
        {
            rnd1 = rand()%3;
           
            the_index = 33;
                               
            if(rnd1 == 0)
                the_index = 33;
            if(rnd1 == 1)
                the_index = 34;
            if(rnd1 == 2)
                the_index = 35;
            
			if(the_index >= 0)     
            if(sprite[the_index].alpha == 0.0)
            {         
                                
                sprite[the_index].alpha = 1.0f; 
                
                sprite[the_index].width = sprite[36].width;
                sprite[the_index].height = sprite[36].height;
                
                sprite[the_index].angle = 0; 
                
                if(the_index == 33) 
                {
                    sprite[the_index].x = start_33_x;     
                    sprite[the_index].y = start_33_y; 
                    Set_Sprite(29, 1, PLAY, ANIM_SPRITE, ANIM_WALKING);
					sprite[29].cur = 0;
                }                 
                if(the_index == 34)
                {
                    sprite[the_index].x = start_34_x;  
                    sprite[the_index].y = start_34_y; 
                    Set_Sprite(28, 1, PLAY, ANIM_SPRITE, ANIM_WALKING);
					sprite[28].cur = 0;
                } 
                 
                if(the_index == 35)  
                { 
                    sprite[the_index].x = start_35_x;  
                    sprite[the_index].y = start_35_y; 
                    Set_Sprite(30, 1, PLAY, ANIM_SPRITE, ANIM_WALKING);
					sprite[30].cur = 0;
                }           
                      
                sprite[the_index].w = sprite[the_index].x+ (sprite[36].w - sprite[36].x);   
                sprite[the_index].z = sprite[the_index].y + (sprite[36].z - sprite[36].y);;  
                 
                sprite[the_index].box_width = sprite[36].width;
                sprite[the_index].box_height = sprite[36].height;  
                         
                sprite[the_index].grab_switch = true;             
                 
                splash_sfx = true;
             
            } 
            
            cannon_timer = (int)TimerGetTime()+5000;   
            
            if(boss_gallery_health < boss_total_score / 2)
                cannon_timer =  (int)TimerGetTime()+3000;  
            
            if(boss_gallery_health < boss_total_score / 3)
                cannon_timer =  (int)TimerGetTime()+2000; 
                            
            if(boss_gallery_health < boss_total_score / 4) 
                cannon_timer =  (int)TimerGetTime()+1500;  
             
        }
        
        for(int i = 33;i<=35;i++)
        {
              
        if(sprite[i].alpha == 1.0)    
        {   

           if(i == 34)
               sprite[i].x += 0.0001f*(float)f_rate;
           if(i == 35)
               sprite[i].x -= 0.0001f*(float)f_rate; 
                            
           temp_speed = 0.001f*(float)f_rate;
           
           temp_expand = 0.0003f*(float)f_rate; 
             
           sprite[i].y += cos(sprite[i].angle )*(temp_speed);
               
		   if(CONTROLLER) 
			   sprite[i].angle += 0.0015f*(float)f_rate; 
		   else
			   sprite[i].angle += 0.001f*(float)f_rate; 
                           
           if(sprite[i].angle > 3.14f)       
               sprite[i].angle = 3.14f;  
           
           sprite[i].x -= temp_expand/2; 
           sprite[i].width += temp_expand;
            
           sprite[i].y -= temp_expand/2; 
           sprite[i].height += temp_expand;  
           
           sprite[i].w = sprite[i].x;
           sprite[i].z = sprite[i].y;
           
           sprite[i].box_width = sprite[i].width;
           sprite[i].box_height = sprite[i].height;
          
             
        }   
        
        if(sprite[i].alpha == 1.0) 
        if(sprite[i].z <= sprite[27].z)
        { 
			reset_player_heal_timer = (int)TimerGetTime() + REGEN_RESET_TIME;

            if(current_difficulty == EASY_MODE)
                old_health -= GALLERY_DAMAGE_EASY;
            if(current_difficulty == NORMAL_MODE)
                old_health -= GALLERY_DAMAGE_NORMAL;
            if(current_difficulty == HARD_MODE)
                old_health -= GALLERY_DAMAGE_HARD;
                                            
            sprite[20].status = STUNNED; 
            sprite[20].all_timer = (int)TimerGetTime() + 250;
                   
            red_swipe = true;
            swipe_color = COLOR_RED;
            red_timer = (int)TimerGetTime() + 100;

			#if INCLDUE_360_CONTROLLER  == 1
				VIBRATE_LEFT(52000, PAIN_RUMBLE);  
				VIBRATE_RIGHT(52000, PAIN_RUMBLE);
			#endif

			shot_vibrating = true;

                                  
            New_FX(sprite[i].x, sprite[i].y,  sprite[i].x, sprite[i].y, 0, PLAY, sprite[i].width, sprite[i].height, sprite[i].width, sprite[i].height, 0, GFX, 1.0, 0, 0, FX_STATIC, i, 21, 0, 0, -1);
            sprite[i].grab_switch = false;
            sprite[i].alpha = 0.0f;    
            boss_sfx = true;      
                    
            sight_sfx = true; 
                                    
        }
          
        }        
                     
    }
    
        Hud_Face_Unit_Gallery();
             
       if(( mouseX < (sprite[0].w + sprite[0].box_width) )
       &&( mouseX > sprite[0].w)                            
       &&( mouseY < (sprite[0].z + sprite[0].box_height) )
       &&( mouseY > sprite[0].z)) 
       {               
            on_the_belt = true; 
       }        
            
           if(ply_dead == false)       
           if(old_health <= 0) 
           { 
               red_swipe = false;          
               ply_dead = true; 
               
               if(current_main > 0)  
               if(main_mission[current_main] == IN_PROGRESS)
               {
                  cycle_episode = episode; 
                  cycle_scene   = scene;
                  cycle_spawn   = last_spawn;
                
                  activate_bicycle = true;
               }                           
               
               sprite[20].status = DIEING;  
               sprite[20].all_timer = (int)TimerGetTime() + 5000;
            
               episode = 0;           
               scene = 8;  
 
               if(Gallery_Level == ENTRY_UNDERGROUND)
                   scene = 14;               
               if(Gallery_Level == ENTRY_BATTLESHIP)
                   scene = 14;
               if(Gallery_Level == ENTRY_GARDENS)
                   scene = 15;
               if(Gallery_Level == ENTRY_BUNKER)
                   scene = 14;                   
                                                 
               next_scene = true;
           }
        
	   aim_assist=false;
	   shot_vibrating=false;

       for(int i = 0;i< no_sprites;i++)
	   if(i < TOTAL_NO_SPRITES)
	   if(i != 20) 
       { 
	   	 	   
 	   	    if(sprite[i].sector_action != UNIT_GENERAL) 	   
            if(flashing == false) 
               if(sprite[i].status == DIEING)
                   sprite[i].alpha = 0.0f;
                   
            if(sprite[i].sector_action != UNIT_GENERAL)        
            if(flashing == true)
              if(sprite[i].status == DIEING) 
                  sprite[i].alpha = 1.0f;
                  
           if(sprite[i].sector_action != UNIT_GENERAL) 
		   if(sprite[i].status == DIEING)
		   if(sprite[i].flash_timer != 0)
		   if((int)TimerGetTime() > sprite[i].flash_timer)     
		       sprite[i].alpha = 1.0f;

           // Disables white flash...                    
           if(sprite[i].flash_target == true 
           && (int)TimerGetTime() > sprite[i].flash_timer)   
           {      
               sprite[i].flash_target = false;
               sprite[i].flash_timer  = 0;
           }      
                       
           // Make targets take cover...    
           if((int)TimerGetTime() > sprite[i].bomb_timer)    
           if(sprite[i].type == FE_TARGET) 
           if(sprite[i].sector_action != UNIT_DUMMY)           
           if(sprite[i].score > 0)            
           if(sprite[i].status != CORNERED)   
           if(sprite[i].grab_switch == true)                  
           {
                 
                sprite[i].grab_switch = false;
                sprite[i].status = CORNERED;
                                     
                if(sprite[i].sector_action != UNIT_SAILOR) 
                {
                    play_anim = COVER_ANIM;
                
                    Set_Sprite(i, play_anim, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
                } 
                else
                {
                    sprite[i].x = sprite[i].mov_x;  
                    sprite[i].w = sprite[i].end_x;                    
                } 
                
                sprite[i].all_timer = (int)TimerGetTime() + 3000;
                                                    
           }   
           
           // Pop targets out again if in cover...
           if((int)TimerGetTime() > sprite[i].all_timer) 
           if(sprite[i].score > 0)     
           if(sprite[i].sector_action != UNIT_DUMMY)                     
           if(sprite[i].type == FE_TARGET)     
           if(sprite[i].status == CORNERED)                   
           { 
                             
                sprite[i].grab_switch = true;           
                sprite[i].status = GROUND_SPAWN; 
                                     
                if(sprite[i].sector_action == UNIT_CHIEF)
                    sprite[i].bomb_timer = (int)TimerGetTime() + 1500;
                 
                if(sprite[i].sector_action == UNIT_GUNNER)
                    sprite[i].bomb_timer = (int)TimerGetTime() + 3000;
                
                if(sprite[i].sector_action == UNIT_SAILOR)
                    sprite[i].bomb_timer = (int)TimerGetTime() + 6000;
                
                if(sprite[i].sector_action == UNIT_GENERAL)
                    sprite[i].bomb_timer = (int)TimerGetTime() + 2000;
                                         
                if(sprite[i].sector_action != UNIT_SAILOR) 
                    Set_Sprite(i, START_ANIM, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); 
                    
                if(sprite[i].sector_action == UNIT_SAILOR) 
                    Set_Sprite(i, S_START_ANIM, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
                  
                sprite[i].all_timer = (int)TimerGetTime() + 500; 
                
                if(sprite[i].sector_action == UNIT_BUDDY || (Gallery_Level == ENTRY_GARDENS && gallery_scene != 7) )
                {
                    sprite[i].alpha = 0.0f;            
                    sprite[i].grab_switch = false;
                    sprite[i].status = MAN_DOWN;  
                    sprite[i].score = 0;  
                    targets_killed++;
                }
                                                    
           }    
           
           if(sprite[i].sector_action != UNIT_DUMMY)                                                                        
           if(sprite[i].sector == RIGHT)   
           if(sprite[i].type == FE_TARGET)    
           if(sprite[i].grab_switch == true)                  
           {   
               if(gallery_scene != 1)
               {  
                   the_speed = (float)targets_spd*(float)f_rate; 
               }
               if(gallery_scene == 1)
               {  
                   the_speed = (float)targets_fast_spd*(float)f_rate;                                 
               } 
               
               if(sprite[i].status == DIEING)
                   the_speed /= 2;
               
               sprite[i].x += the_speed;         
               sprite[i].w += the_speed;  
                             
           }   
           
           if(sprite[i].sector_action != UNIT_DUMMY)            
           if(sprite[i].sector == LEFT)    
           if(sprite[i].type == FE_TARGET)    
           if(sprite[i].grab_switch == true)                  
           {        
               if(gallery_scene != 1)
               {  
                   the_speed = (float)targets_spd*(float)f_rate; 
               }
               if(gallery_scene == 1)
               {  
                   the_speed = (float)targets_fast_spd*(float)f_rate;                                 
               } 
               
               if(sprite[i].status == DIEING)
                   the_speed /= 2;
               
               sprite[i].x -= the_speed;         
               sprite[i].w -= the_speed;  
                                 
           }    
            
           // Make target go IDLE...    
           if((int)TimerGetTime() > sprite[i].all_timer) 
           if(sprite[i].score > 0)
           if(sprite[i].type == FE_TARGET) 
           if(sprite[i].sector_action != UNIT_DUMMY)              
           if(sprite[i].status == STUNNED 
           || sprite[i].status == GROUND_SPAWN
           || sprite[i].status == OPEN_FIRE)
           if(sprite[i].alpha == 1.0)                  
           { 
 
                play_anim = IDLE_ANIM; 
                
                sprite[i].status = IDLE; 
                 
                if(sprite[i].sector_action != UNIT_GENERAL)
                {
                    if(current_difficulty == EASY_MODE)                       
                        sprite[i].all_timer = (int)TimerGetTime() + GALLERY_ENEMY_SHOOT_EASY;

                    if(current_difficulty == NORMAL_MODE)            
					if(CONTROLLER)
                        sprite[i].all_timer = (int)TimerGetTime() + GALLERY_ENEMY_SHOOT_NORMALC;
					else
                        sprite[i].all_timer = (int)TimerGetTime() + GALLERY_ENEMY_SHOOT_NORMAL;

                    if(current_difficulty == HARD_MODE)                       
					if(CONTROLLER)
                        sprite[i].all_timer = (int)TimerGetTime() + GALLERY_ENEMY_SHOOT_NORMALC;
					else
                        sprite[i].all_timer = (int)TimerGetTime() + GALLERY_ENEMY_SHOOT_NORMAL;                                               
                }
                else 
                {
                    if(gallery_scene == 7) 
                    {
                        if(current_difficulty == EASY_MODE)                       
                            sprite[i].all_timer = (int)TimerGetTime() + GALLERY_MAUSER_SHOOT_EASY;
                        if(current_difficulty == NORMAL_MODE)                       
                            sprite[i].all_timer = (int)TimerGetTime() + GALLERY_MAUSER_SHOOT_NORMAL;
                        if(current_difficulty == HARD_MODE)                       
                            sprite[i].all_timer = (int)TimerGetTime() + GALLERY_MAUSER_SHOOT_NORMAL;                                      
                    }
                    else  
                    {
                        if(current_difficulty == EASY_MODE)                        
                            sprite[i].all_timer = (int)TimerGetTime() + GALLERY_GENERAL_SHOOT_EASY;
                        if(current_difficulty == NORMAL_MODE)                       
                            sprite[i].all_timer = (int)TimerGetTime() + GALLERY_GENERAL_SHOOT_NORMAL;
                        if(current_difficulty == HARD_MODE)                       
                            sprite[i].all_timer = (int)TimerGetTime() + GALLERY_GENERAL_SHOOT_NORMAL; 
                        
                        if(boss_gallery_health < boss_total_score / 3)  
                        {  
                            if(current_difficulty == EASY_MODE)                           
                                sprite[i].all_timer = (int)TimerGetTime() + (GALLERY_GENERAL_SHOOT_EASY/2);

							if(!CONTROLLER)
							{
								if(current_difficulty == NORMAL_MODE)                       
									sprite[i].all_timer = (int)TimerGetTime() + (GALLERY_GENERAL_SHOOT_NORMAL/2);
								if(current_difficulty == HARD_MODE)                       
									sprite[i].all_timer = (int)TimerGetTime() + (GALLERY_GENERAL_SHOOT_NORMAL/2);                         
							} 
							else  
							{
								if(current_difficulty == NORMAL_MODE)                       
									sprite[i].all_timer = (int)TimerGetTime() + (GALLERY_GENERAL_SHOOT_NORMAL-200);
								if(current_difficulty == HARD_MODE)                       
									sprite[i].all_timer = (int)TimerGetTime() + (GALLERY_GENERAL_SHOOT_NORMAL-300);                         
							} 
							 
                        }    
                        if(current_difficulty != EASY_MODE)    
                        if(boss_gallery_health < boss_total_score / 4)      
                        {  
                            if(current_difficulty == EASY_MODE)                       
                                sprite[i].all_timer = (int)TimerGetTime() + (GALLERY_GENERAL_SHOOT_EASY/4);

							if(!CONTROLLER)
							{
								if(current_difficulty == NORMAL_MODE)                       
									sprite[i].all_timer = (int)TimerGetTime() + (GALLERY_GENERAL_SHOOT_NORMAL/4);
								if(current_difficulty == HARD_MODE)                       
									sprite[i].all_timer = (int)TimerGetTime() + (GALLERY_GENERAL_SHOOT_NORMAL/4);                         
							}
							else 
							{ 
								if(current_difficulty == NORMAL_MODE)                        
									sprite[i].all_timer = (int)TimerGetTime() + (GALLERY_GENERAL_SHOOT_NORMAL-350);
								if(current_difficulty == HARD_MODE)                       
									sprite[i].all_timer = (int)TimerGetTime() + (GALLERY_GENERAL_SHOOT_NORMAL-350);                         
							}

                        }    
                                                      
                    }
                }
                                    
                
                if(sprite[i].sector_action != UNIT_SAILOR)                
                    Set_Sprite(i, play_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                if(sprite[i].sector_action == UNIT_SAILOR)                
                    Set_Sprite(i, S_START_ANIM, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                    
                                                   
           }  
               
           // Make targets shoot...    
           if((int)TimerGetTime() > sprite[i].all_timer)   
           if(sprite[i].score > 0)               
           if(sprite[i].type == FE_TARGET) 
           if(sprite[i].sector_action != UNIT_DUMMY)  
           if(sprite[i].sector_action != UNIT_BUDDY)             
           if(sprite[i].status == IDLE)
           if(sprite[i].alpha == 1.0)                  
           { 

                play_anim = FIRE_ANIM;   
                 
                sprite[i].status = OPEN_FIRE; 
                
				reset_player_heal_timer = (int)TimerGetTime() + REGEN_RESET_TIME;
    
                if(current_difficulty == EASY_MODE)
                    old_health -= GALLERY_DAMAGE_EASY*2;
                if(current_difficulty == NORMAL_MODE)
                    old_health -= GALLERY_DAMAGE_NORMAL*2;
                if(current_difficulty == HARD_MODE)
                    old_health -= GALLERY_DAMAGE_HARD*2;
                
                sprite[20].status = STUNNED;  
                sprite[20].all_timer = (int)TimerGetTime() + 250;
               
          //      Camera_Shake(THUD_SHAKE);
          
                red_swipe = true;
                swipe_color = COLOR_RED;

				#if INCLDUE_360_CONTROLLER  == 1
					VIBRATE_LEFT(52000, PAIN_RUMBLE);  
					VIBRATE_RIGHT(52000, PAIN_RUMBLE);
				#endif

				shot_vibrating = true;

                red_timer = (int)TimerGetTime() + 100;
                
                sight_sfx = true;
                
                sprite[i].all_timer = (int)TimerGetTime() + 250;
                
                if(sprite[i].sector_action != UNIT_SAILOR)
                    Set_Sprite(i, play_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                if(sprite[i].sector_action == UNIT_SAILOR)
                    Set_Sprite(i, S_FIRE_ANIM, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                                         
           }    
           
           // Target is dieing...     
           if((int)TimerGetTime() > sprite[i].all_timer)
           if(sprite[i].sector_action != UNIT_DUMMY)    
           if(sprite[i].type == FE_TARGET)    
           if(sprite[i].status == DIEING)
           if(sprite[i].alpha == 1.0)                   
           {
                if(sprite[i].sector_action != UNIT_SAILOR)                              
                    sprite[i].alpha = 0.0f;
                    
                sprite[i].grab_switch = false;
                    
                sprite[i].status = MAN_DOWN; 
                targets_killed++;  
                         
                if(current_act != 2 && gallery_scene != 5 ) 
                if( i == 9)
				if(gallery_scene != 2) 
                if(sprite[i].sector_action != UNIT_GENERAL)     
                {
                    sprite[11].grab_switch = true;
                    sprite[11].alpha = 1.0f; 
                    sprite[11].priority = 3;
                    
                    sprite[11].sector_action = UNIT_DUMMY;
                    sprite[11].rank = 1;
                    sprite[11].score = 10;  
                    
                    sprite[11].x = sprite[9].x;
                    sprite[11].w = sprite[9].x;
                    
                    sprite[11].y = sprite[9].y-sprite[11].height/3;
                    sprite[11].z = sprite[9].y-sprite[11].height/3;
                     
                    Set_Sprite(11, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
                    
                    coins_sfx = true;  
                }
                if(current_act != 2 && gallery_scene != 5 ) 
                if( i == 12)  
                if(sprite[i].sector_action != UNIT_GENERAL)                            
                {  
                    sprite[10].grab_switch = true;
                    sprite[10].alpha = 1.0f; 
                    sprite[10].priority = 3;
                    
                    sprite[10].sector_action = UNIT_DUMMY;
                    sprite[10].rank = 0;
                    sprite[10].score = 10;   
                    
                    sprite[10].x = sprite[12].x+sprite[12].width/2;
                    sprite[10].w = sprite[12].x+sprite[12].width/2; 
                    
                    sprite[10].y = sprite[12].y-sprite[10].height/3; 
                    sprite[10].z = sprite[12].y-sprite[10].height/3;
                    
                    Set_Sprite(10, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
                    
                    mgun_sfx = true;
                }                 
                
           }  
           
           // Shot a target...
           if(on_the_belt == false) 
           if(gallery_reloading == false) 
           if(sprite[i].type == FE_TARGET || sprite[i].type == FE_CARD) // Card is floating debris...
           if(sprite[i].score > 0)  
           if(sprite[i].grab_switch == true)  
           if(( mouseX < (sprite[i].w + sprite[i].box_width) )
           &&( mouseX > sprite[i].w)                            
           &&( mouseY < (sprite[i].z + sprite[i].box_height) )
           &&( mouseY > sprite[i].z)) 
		   {
               on_a_target = true;
			   aim_assist=true;
		   }

                                                       
           // Shot a target... 
           if(gallery_clip > 0)           
           if(on_the_belt == false) 
           if(mouseleft == true || DX_SHOOT == true)   
           if(gallery_reloading == false) 
           if(sprite[i].type == FE_TARGET)
           if(sprite[i].score > 0)  
           if(sprite[i].grab_switch == true)  
           if(( mouseX < (sprite[i].w + sprite[i].box_width) )
           &&( mouseX > sprite[i].w)                            
           &&( mouseY < (sprite[i].z + sprite[i].box_height) )
           &&( mouseY > sprite[i].z)) 
           {     

                if(sprite[i].sector_action == UNIT_BUDDY)
                {

					reset_player_heal_timer = (int)TimerGetTime() + REGEN_RESET_TIME;                

                    if(current_difficulty == EASY_MODE)
                        old_health -= GALLERY_DAMAGE_EASY;
                    if(current_difficulty == NORMAL_MODE)
                        old_health -= GALLERY_DAMAGE_NORMAL;
                    if(current_difficulty == HARD_MODE)
                        old_health -= GALLERY_DAMAGE_HARD;
                    
                    sprite[20].status = STUNNED;  
                    sprite[20].all_timer = (int)TimerGetTime() + 250;

                    red_swipe = true; 
                    swipe_color = COLOR_RED;

                    red_timer = (int)TimerGetTime() + 100;

					#if INCLDUE_360_CONTROLLER  == 1
						VIBRATE_LEFT(52000, PAIN_RUMBLE);  
						VIBRATE_RIGHT(52000, PAIN_RUMBLE);
					#endif

					shot_vibrating = true;

                    stolen_sfx = true;
                                                           
                }  
                 
                sprite[i].score -= gallery_player_damage; 
                                     
                shot_a_target = true;
                   
                if(sprite[i].sector_action == UNIT_DUMMY)  
                {
          
                   sprite[i].alpha = 0.0f;
                   sprite[i].grab_switch = false;
                   
                   if(sprite[i].rank == 0) 
                   { 
                      chute_sfx = true; 
                      old_health += HEALTHKIT_AMOUNT;
                      
                      if(old_health > PLY_VITALITY)
                          old_health = PLY_VITALITY;                        
                   }
                   if(sprite[i].rank == 1) 
                   {
                   //    current_gold += 50;
                       
                       Calculate_Item(50, INV_GOLD, -1, 0, -1, -1);
                       
                       switch_sfx = true; // whoosh.wav         
                   }                    
                   
                }          
                      
                if(sprite[i].sector_action != UNIT_DUMMY) 
                {       
                        
                if(sprite[i].score <= 0)
                {   
                    if(sprite[i].sector_action != UNIT_SAILOR)                                  
                        Set_Sprite(i, DIE_ANIM, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
                    if(sprite[i].sector_action == UNIT_SAILOR)                                  
                        Set_Sprite(i, S_DIE_ANIM, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
                    
                    if(sprite[i].sector_action == UNIT_GENERAL)                            
                        sprite[i].all_timer = (int)TimerGetTime() + 1000;
                    else
                        sprite[i].all_timer = (int)TimerGetTime() + 2000;
                                    
                    if(sprite[i].sector_action == UNIT_GENERAL) 
                            boss_ohh_sfx = true;
 
                    if(gallery_scene == 3 && sprite[i].sector_action == UNIT_GENERAL) 
                        boss_gallery_health -= 30; 
                        
                    if(gallery_scene == 7 && sprite[i].sector_action == UNIT_GENERAL) 
                        boss_gallery_health -= 30;  
                                
                    sprite[i].status = DIEING; 
                    
                    if(sprite[i].sector_action != UNIT_GENERAL) 
                        sprite[i].flash_timer = (int)TimerGetTime()+250;
                    
                    if(sprite[i].sector_action != UNIT_BUDDY)                    
                    {
                        if(sprite[i].sector_action != UNIT_GENERAL || (gallery_index == 22 && gallery_scene == 3) )
                            step_sfx = true; 
                        else 
                            emypain_sfx = true;
                    }
                } 
                else 
                {
                    if(sprite[i].sector_action != UNIT_SAILOR)                     
                        Set_Sprite(i, STUN_ANIM, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
                    if(sprite[i].sector_action == UNIT_SAILOR)                     
                        Set_Sprite(i, S_STUN_ANIM, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
                    
                    sprite[i].all_timer = (int)TimerGetTime() + 250;
                    sprite[i].status = STUNNED;
                     
                    sprite[i].flash_target = true; 
                    sprite[i].flash_timer = (int)TimerGetTime() + 50;
                    
                //    wound_sfx = true;
                }   
                }                   

           } 
                       
           // Shot a target...
           if(on_the_belt == false) 
           if(sprite[i].type == FE_SHOOTABLE) 
           if(sprite[i].rank == 5)   
           if(sprite[i].grab_switch == true)                   
           if(( mouseX < (sprite[i].w + sprite[i].box_width) )
           &&( mouseX > sprite[i].w)                            
           &&( mouseY < (sprite[i].z + sprite[i].box_height) )
           &&( mouseY > sprite[i].z)) 
               on_a_target = true;
                           
           // Shot a target... 
           if(on_the_belt == false) 
           if(mouseleft == true || DX_SHOOT == true)  
           if(gallery_clip > 0 && gallery_reloading == false)
           if(sprite[i].type == FE_SHOOTABLE)    
           if(sprite[i].grab_switch == true)                   
           if(( mouseX < (sprite[i].w + sprite[i].box_width) )
           &&( mouseX > sprite[i].w)                            
           &&( mouseY < (sprite[i].z + sprite[i].box_height) )
           &&( mouseY > sprite[i].z)) 
           {    
			   DX_SHOOT=false;
  
                // Crate    
                if(sprite[i].rank == 0)   
                {
                    New_FX(mouseX, mouseY,  mouseX, mouseY, 1, LOOP, sprite[i].width/4, sprite[i].height/4, sprite[i].width/4, sprite[i].height/4, 0, GFX, 1.0, 0, 0, FX_CHIP, i, 2, 0, 0, -1);
                    
                    sprite[i].score--;   
                    if(st_gallery == 2)
                        sprite[i].score--;   
                    if(st_gallery == 3)
                        sprite[i].score--;   
                    
                    sprite[i].flash_target = true;
                    sprite[i].flash_timer = (int)TimerGetTime() + 50;
                    
                    if(sprite[i].score > 0)
                    {
                        if(gallery_index != 5)               
                            Set_Sprite(i, sprite[i].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);   
                        else
                            Set_Sprite(i, sprite[i].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);   
                        
                    }
                     
                    if(sprite[i].score <= 0) 
                    { 
                        if(gallery_index != 5)                                        
                            Set_Sprite(i, sprite[i].base_anim+2, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); 
                        else
                            Set_Sprite(i, sprite[i].base_anim+2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
                           
                        sprite[i].score = 0;
                        sprite[i].grab_switch = false;
                        destroy_sfx = true;
                        Create_Crate_Effect(i);                        
                    }                   
                }
                
                // Glass window    
                if(sprite[i].rank == 1)
                {
                    Set_Sprite(i, sprite[i].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);    
                    glass_sfx = true; 
                    sprite[i].grab_switch = false;
                }     
                
                // Lantern
                if(sprite[i].rank == 2)
                {
                    Set_Sprite(i, sprite[i].base_anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);    
                    glass_sfx = true; 
                    sprite[i].grab_switch = false;
                    fade = 0.6f;
                }     
                
                // Lantern 
                if(sprite[i].rank == 3)
                {
                    New_FX(mouseX, mouseY,  mouseX, mouseY, 1, LOOP, sprite[i].width/4, sprite[i].height/4, sprite[i].width/4, sprite[i].height/4, 0, GFX, 1.0, 0, 0, FX_CHIP, i, 2, 0, 0, -1);
                    
                    sprite[i].score--;    
                    
                    sprite[i].flash_target = true;
                    sprite[i].flash_timer = (int)TimerGetTime() + 50;
                    
                    if(sprite[i].score > 0)
                        Set_Sprite(i, sprite[i].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);   
     
                    if(sprite[i].score <= 0) 
                    { 
                        Set_Sprite(i, sprite[i].base_anim+2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
                           
                        sprite[i].score = 0;
                        sprite[i].grab_switch = false;
                        destroy_sfx = true;
                        Create_Crate_Effect(i);  
                                                      
                        if(gallery_scene == 5 ) 
                        if( i == 29)         
                        {  
                            sprite[10].grab_switch = true;
                            sprite[10].alpha = 1.0; 
                            sprite[10].priority = 2; 
                            
                            sprite[10].sector_action = UNIT_DUMMY;
                            sprite[10].rank = 0;
                            sprite[10].score = 10;   
                            
                            sprite[10].x = sprite[29].x+sprite[29].width/2;
                            sprite[10].w = sprite[29].x+sprite[29].width/2; 
                            
                            sprite[10].y = sprite[29].y-sprite[29].height/4; 
                            sprite[10].z = sprite[29].y-sprite[29].height/4;
                            
                            Set_Sprite(10, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);
                            
                            mgun_sfx = true;
                        }  
                                          
                    }   
                }  
                  
                // Glass window    
                if(sprite[i].rank == 4)
                { 
                    if(gallery_scene != 11) 
                    {             
                        New_FX(sprite[i].x, sprite[i].y,  sprite[i].x, sprite[i].y, 0, PLAY, sprite[i].width, sprite[i].height, sprite[i].width, sprite[i].height, 0, GFX, 1.0, 0, 0, FX_STATIC, i, 21, 0, 0, -1);
                        boss_sfx = true;
                    }
                    else
                        New_FX(sprite[i].x, sprite[i].y,  sprite[i].x, sprite[i].y, 0, PLAY, sprite[i].width, sprite[i].height, sprite[i].width, sprite[i].height, 0, GFX, 1.0, 0, 0, FX_STATIC, i, 22, 0, 0, -1);
                                            
                    sprite[i].grab_switch = false;
                    sprite[i].alpha = 0.0f;    
                         
                }                      
                   
                // Clay Pigeon    
                if(sprite[i].rank == 5)
                {  
                                  
                    New_FX(sprite[i].x-sprite[i].width/2, sprite[i].y-sprite[i].height/2,  sprite[i].x, sprite[i].y, 0, PLAY, sprite[i].width*2, sprite[i].height*2, sprite[i].width*2, sprite[i].height*2, 0, GFX, 0.5, 0, 0, FX_STATIC, i, 21, 0, 0, -1);
                    sprite[i].grab_switch = false;
                    Set_Sprite(i, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);   
                    smash1_sfx = true; 
                    targets_shot++;  
                     
                    if(targets_shot >= 24)
                        pigeon_finished = true;
                    
                }   
                
                // Glass window    
                if(sprite[i].rank == 6)     
                {    
                    glass_sfx = true;      

                    boss_gallery_health -= 10;   
 
                    sprite[i].score -= 10;    
                    
                    sprite[i].flash_target = true;
                    sprite[i].flash_timer = (int)TimerGetTime() + 50;
                                        
                    if(sprite[i].score < 0)
                    {  
                        sprite[i].score = 0;
                        boss_gallery_health = 0;  
                    }
      
                   
                }   
                 
                // Cow  
                if(sprite[i].rank == 7) 
                {
                    Set_Sprite(i, sprite[i].base_anim+1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);    
                    cow_sfx = true;  
                    sprite[i].grab_switch = false;
                }      
                             
                shot_a_target = true;  
                                           
                gallery_clip--;   
                
                if(gallery_clip >= 0) 
                {
                    sprite[20].status = OPEN_FIRE; 
                    sprite[20].all_timer = (int)TimerGetTime() + 250;            
                    death_sfx = true;
                }    
                
           //     smash1_sfx = true;   
                mouseleft = false;     
           }   
                            
       }  // for no_of_sprites           
               
       sprintf( counter[5].word, "");
       
       // Exit Button - EXIT  
       if(fade >= 0.7)
       if(sprite[1].grab_switch == true)                   
       if(( ( mouseX < (sprite[1].w + sprite[1].box_width) )
       &&( mouseX > sprite[1].w)                            
       &&( mouseY < (sprite[1].z + sprite[1].box_height) )
       &&( mouseY > sprite[1].z)) || DX_BACK == true)
       {
           if(sprite[1].anim != 1)
               Set_Sprite(1, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
               
           sprintf( counter[5].word, "Back"); 
                         
           counter[5].length = 0;  
             
           msg_left=false;   
                          
           if(mouseleft == true || DX_BACK == true) 
           {
			   DX_BACK=false;

               if(Gallery_Level == ENTRY_BATTLESHIP)
               {         
                   episode = 3;      
                   scene = 3;  
                   
                   current_spawn = 21;
               }
               if(Gallery_Level == ENTRY_UNDERGROUND)
               {         
                   episode = 3;      
                   scene = 16;   
                   
                   current_spawn = 2; 
               }
               if(Gallery_Level == ENTRY_GARDENS)
               {          
                   episode = 2;       
                   scene = 13;    
                   
                   current_spawn = 23;
               } 
               
               if(Gallery_Level == ENTRY_PIGEON)
               {         
                   episode = 3;         
                   scene = 29;    
                   
                   current_spawn = 3;

               }      
               
               if(Gallery_Level == ENTRY_BUNKER)
               {         
                   episode = 3;          
                   scene = 5;     
                   
                   current_spawn = 2;

               }                 
                                       
               map_stat = false; 
               
               switch_n_sfx = true;  
               
               if(Gallery_Level != ENTRY_MISSILE)
               {
                   next_scene = true;
                   sprite[1].grab_switch = false;
               }    
               
               mouseleft = false; 
               
           }   
                     
       }  
       else
       {
          if(sprite[1].anim != 0) 
              Set_Sprite(1, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
       }  
       
                         
       if(on_the_belt == false && mouseleft == true || DX_SHOOT == true)
       {
			DX_SHOOT=false; 

			if(shot_vibrating == false)
			{ 
				#if INCLDUE_360_CONTROLLER  == 1
					VIBRATE_LEFT(24000, 150); 
					VIBRATE_RIGHT(24000, 150);
				#endif
			}

           if(gallery_clip == 0 && gallery_reloading == false && pigeon_mode == false)
           {
               mouseright = true; 
               click_sfx = true; 
           }    
           
           if(gallery_reloading == false && mouseright == false)
           {     
               gallery_clip--;     

               
               if(gallery_clip >= 0)  
               { 
                
                   sprite[20].status = OPEN_FIRE; 
                   sprite[20].all_timer = (int)TimerGetTime() + 250;
                                                        
                   death_sfx = true;   
                   
                   if(shot_a_target == false)        
                       New_FX(mouseX-0.1f, mouseY-0.1f,  mouseX-0.1f, mouseY-0.1f, 0, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 0, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);
                       
               }
               else
                   click_sfx = true;
           }               
           
           mouseleft = false;                    
       }     
       
       // Reloading gun...
       if(pigeon_mode == false)
       if(mouseright == true || DX_RELOAD == true && gallery_reloading == false)
       {
           gallery_reloading = true;

		   if(CONTROLLER)
 			   gallery_reload_timer = (int)TimerGetTime() + GALLERY_RELOAD_TIMEC;          
		   else
 			   gallery_reload_timer = (int)TimerGetTime() + GALLERY_RELOAD_TIME;          

           mouseright = false; 
		   DX_RELOAD=false;
           potion_up_sfx = true; 
                       
       }    
          
       if( gallery_reloading == true)  
            Set_Sprite(1, 8, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Attack Arrow 
            
       if( gallery_reloading == false && on_the_belt == false)
            Set_Sprite(1, 9, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Attack Arrow 
      
      
       if(gallery_reloading == true) 
       {
                              
           
       if((int)TimerGetTime() > gallery_reload_count)
       {
           gallery_reload_count = (int)TimerGetTime() + 500;
//           potion_up_sfx = true;
       }
                                         
       if((int)TimerGetTime() > gallery_reload_timer)
       { 

		   gallery_clip = GALLERY_CLIP_AMOUNT; 
                       
           if(st_gallery == 0)
               gallery_clip = 5; 
           if(st_gallery == 1)
               gallery_clip = 6; 
           if(st_gallery == 2)
               gallery_clip = 6;
           if(st_gallery == 3)
               gallery_clip = 8;
               
           cash_up_sfx = true;                       
           gallery_reloading = false;  
           sprite[20].status = IDLE;                     
       }
        
       }  
       
       if(gallery_reloading == false)  
       {
           if(on_a_target == true) 
           {
               if(hud[1].anim != 2)           
                   Set_Sprite(1, 2, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Normal Arrow        
           }   
           else
           {
               if(hud[1].anim != 7)
                   Set_Sprite(1, 7, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Normal Arrow
           }
       }    
       
       if(gallery_reloading == true)
       {
           if(hud[1].anim != 8)                 
               Set_Sprite(1, 8, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Normal Arrow
       }    
       
       if(( mouseX < (sprite[0].w + sprite[0].box_width) )
       &&( mouseX > sprite[0].w)                            
       &&( mouseY < (sprite[0].z + sprite[0].box_height) )
       &&( mouseY > sprite[0].z))  
       {    
            if(hud[1].anim != 0) 
                Set_Sprite(1, 0, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Normal Arrow                      
       }          
       
       if(gallery_reloading == false)
       if((int)TimerGetTime() > sprite[20].all_timer )
           sprite[20].status = IDLE; 
     
}
     
void Init_Gallery(int index) 
{
             
    gallery_index =0;
/* For Copy&Paste
#define GUY_DOWN_LEFT      0
#define GUY_DOWN_MIDLEFT   1
#define GUY_DOWN_MIDDLE    2 
#define GUY_DOWN_MIDRIGHT  3
#define GUY_DOWN_RIGHT     4

#define GUY_MIDDLE_LEFT      5
#define GUY_MIDDLE_MIDLEFT   6
#define GUY_MIDDLE_MIDDLE    7 
#define GUY_MIDDLE_MIDRIGHT  8
#define GUY_MIDDLE_RIGHT     9

#define GUY_UP_LEFT      10
#define GUY_UP_MIDLEFT   11
#define GUY_UP_MIDDLE    12 
#define GUY_UP_MIDRIGHT  13
#define GUY_UP_RIGHT     14
*/

    memset(gallery_direction, RESET, sizeof(gallery_direction) );
    memset(gallery_id, -1, sizeof(gallery_id));
    
    if(index == 0) 
    { 
              
        gallery_sequence[0]       = 2;
        gallery_sequence_times[0] = 2000;
        gallery_innocent[0] = TARGET_CHIEF;
        
        gallery_sequence[1]       = 6;
        gallery_sequence_times[1] = 3000; 
        gallery_innocent[1] = TARGET_GUNNER;         

        gallery_sequence[2]       = 8;
        gallery_sequence_times[2] = 1000; 
        gallery_innocent[2] = TARGET_CHIEF;        
       
        gallery_sequence[3]       = 7; 
        gallery_sequence_times[3] = 2000;
        gallery_innocent[3] = TARGET_CHIEF;    
       
        gallery_sequence[4]       = 4; 
        gallery_sequence_times[4] = 500; 
        gallery_innocent[4] = TARGET_BUDDY; 
        
        gallery_sequence[5]       = 6;
        gallery_sequence_times[5] = 4000; 
        gallery_innocent[5] = TARGET_GUNNER;
        
        gallery_sequence[6]       = 13;
        gallery_sequence_times[6] = 1000;
        gallery_innocent[6] = TARGET_CHIEF;        

               
        gallery_count = 7; 
        
        gallery_pause[0] = 3;
        gallery_pause[1] = 6;          
  
  
        
    }     

    if(index == 1)  
    {   

        gallery_sequence[0]       = 7;
        gallery_sequence_times[0] = 2000;
        gallery_innocent[0] = TARGET_CHIEF;

        gallery_sequence[1]       = 6; 
        gallery_sequence_times[1] = 500;
        gallery_innocent[1] = TARGET_GUNNER;        

        gallery_sequence[2]       = 4;
        gallery_sequence_times[2] = 2000; 
        gallery_innocent[2] = TARGET_GUNNER;        
        
        gallery_sequence[3]       = 13;  
        gallery_sequence_times[3] = 1000;
        gallery_innocent[3] = TARGET_CHIEF;    
        
        gallery_sequence[4]       = 12; 
        gallery_sequence_times[4] = 1000; 
        gallery_innocent[4] = TARGET_SAILOR;          
        gallery_direction[4] = RIGHT;    
                
        gallery_sequence[5]       = 5;  
        gallery_sequence_times[5] = 6000; 
        gallery_innocent[5] = TARGET_GUNNER;  
        gallery_id[5] = 17;  
        
        gallery_sequence[6]       = 8;
        gallery_sequence_times[6] = 3000; 
        gallery_innocent[6] = TARGET_CHIEF;
        
        gallery_sequence[7]       = 5;   
        gallery_sequence_times[7] = 400;
        gallery_innocent[7] = TARGET_BUDDY; 
        gallery_id[7] = 25;         
         
        gallery_sequence[8]       = 6;
        gallery_sequence_times[8] = 2000;
        gallery_innocent[8] = TARGET_GUNNER;        
        
        gallery_sequence[9]       = 4;  
        gallery_sequence_times[9] = 2000; 
        gallery_innocent[9] = TARGET_GUNNER;         
                
        gallery_sequence[10]       = 9; 
        gallery_sequence_times[10] = 2000; 
        gallery_innocent[10] = TARGET_SAILOR;        
        gallery_direction[10] = LEFT;  
                     
        gallery_sequence[11]       = 4;
        gallery_sequence_times[11] = 6000;
        gallery_innocent[11] = TARGET_GUNNER; 
        
        gallery_sequence[12]       = 6;
        gallery_sequence_times[12] = 100;
        gallery_innocent[12] = TARGET_GUNNER;

               
        gallery_count = 13;
        
        gallery_pause[0] = 3; 
        gallery_pause[1] = 6;         
        gallery_pause[2] = 10;           
        gallery_pause[3] = 11;   

          
    }

    if(index == 2)  
    {   
              
        gallery_sequence[0]       = 6;
        gallery_sequence_times[0] = 2000; // Pop me up in 2 seconds...
        gallery_innocent[0] = TARGET_GUNNER;
        
        gallery_sequence[1]       = 2; 
        gallery_sequence_times[1] = 1000;
        gallery_innocent[1] = TARGET_CHIEF;        
        
        gallery_sequence[2]       = 4; 
        gallery_sequence_times[2] = 1000;
        gallery_innocent[2] = TARGET_GUNNER;
         
        gallery_sequence[3]       = 8; 
        gallery_sequence_times[3] = 2000;
        gallery_innocent[3] = TARGET_CHIEF;
                 
        gallery_sequence[4]       = 9; 
        gallery_sequence_times[4] = 4000; 
        gallery_innocent[4] = TARGET_SAILOR;        
        gallery_direction[4] = LEFT;  
        
        gallery_sequence[5]       = 4; 
        gallery_sequence_times[5] = 6000;
        gallery_innocent[5] = TARGET_GUNNER;
           
        gallery_sequence[6]       = 7;      
        gallery_sequence_times[6] = 1000;
        gallery_innocent[6] = TARGET_BUDDY;
        gallery_id[6] = 25; 
        
        gallery_sequence[7]       = 12; 
        gallery_sequence_times[7] = 2000; 
        gallery_innocent[7] = TARGET_SAILOR;         
        gallery_direction[7] = RIGHT;           
        
        gallery_sequence[8]       = 9; 
        gallery_sequence_times[8] = 4000; 
        gallery_innocent[8] = TARGET_SAILOR;        
        gallery_direction[8] = LEFT;  
         
/*        gallery_sequence[10]       = 6; 
        gallery_sequence_times[10] = 3000; 
        gallery_innocent[10] = TARGET_GUNNER;
         
        gallery_sequence[11]       = 8;  
        gallery_sequence_times[11] = 500;
        gallery_innocent[11] = TARGET_CHIEF;         
        
        gallery_sequence[12]       = 2;  
        gallery_sequence_times[12] = 100;
        gallery_innocent[12] = TARGET_CHIEF; */ 
                                                                       
        gallery_count = 9;
        
        gallery_pause[0] = 3;   
        gallery_pause[1] = 5;          
        gallery_pause[2] = 8;
   //     gallery_pause[3] = 10;        
        gallery_pause[3] = 8;        

        //gallery_pause[4] = 12;         

                         
    }

    if(index == 3)   
    {   
          
        boss_total_score = 0;
               
        gallery_sequence[0]       = 6;
        gallery_sequence_times[0] = 2000; // Pop me up in 2 seconds...
        gallery_innocent[0] = TARGET_BOSS;
        boss_total_score += 30;
        
        gallery_sequence[1]       = 2; 
        gallery_sequence_times[1] = 2000;
        gallery_innocent[1] = TARGET_BOSS;        
        boss_total_score += 30;
                
        gallery_sequence[2]       = 4; 
        gallery_sequence_times[2] = 2000;
        gallery_innocent[2] = TARGET_BOSS;                  
        boss_total_score += 30;
                
        gallery_sequence[3]       = 9; 
        gallery_sequence_times[3] = 2000;
        gallery_innocent[3] = TARGET_BOSS; 
        boss_total_score += 30;
                
        gallery_sequence[4]       = 8; 
        gallery_sequence_times[4] = 2000;
        gallery_innocent[4] = TARGET_BOSS;         
        boss_total_score += 30;
                
        gallery_sequence[5]       = 7; 
        gallery_sequence_times[5] = 2000;
        gallery_innocent[5] = TARGET_BOSS;           
        boss_total_score += 30;
                
        gallery_sequence[6]       = 4; 
        gallery_sequence_times[6] = 2000;
        gallery_innocent[6] = TARGET_BOSS; 
        boss_total_score += 30;       
        
        
        gallery_sequence[7]       = 8; 
        gallery_sequence_times[7] = 6000;
        gallery_innocent[7] = TARGET_BOSS; 
        boss_total_score += 30;
        
        gallery_sequence[8]       = 13;
        gallery_sequence_times[8] = 1000;
        gallery_innocent[8] = TARGET_BOSS; 
        boss_total_score += 30;
         
        gallery_sequence[9]       = 5; 
        gallery_sequence_times[9] = 1000;
        gallery_innocent[9] = TARGET_BOSS; 
        boss_total_score += 30;
        
        gallery_sequence[10]       = 9; 
        gallery_sequence_times[10] = 1000;
        gallery_innocent[10] = TARGET_BOSS; 
        boss_total_score += 30;
        
        gallery_sequence[11]       = 12;
        gallery_sequence_times[11] = 1000;
        gallery_innocent[11] = TARGET_BOSS; 
        boss_total_score += 30;
        
        gallery_sequence[12]       = 6; 
        gallery_sequence_times[12] = 1000;
        gallery_innocent[12] = TARGET_BOSS; 
        boss_total_score += 30;
        
        
        gallery_sequence[13]       = 5; 
        gallery_sequence_times[13] = 6000;
        gallery_innocent[13] = TARGET_BOSS; 
        boss_total_score += 30;
        
        gallery_sequence[14]       = 12;  
        gallery_sequence_times[14] = 10;
        gallery_innocent[14] = TARGET_BOSS;                                                                 
        boss_total_score += 30;
        
        gallery_sequence[15]       = 4;  
        gallery_sequence_times[15] = 10;
        gallery_innocent[15] = TARGET_BOSS; 
        boss_total_score += 30;
                
        gallery_sequence[16]       = 13;  
        gallery_sequence_times[16] = 10;
        gallery_innocent[16] = TARGET_BOSS; 
        boss_total_score += 30;
                
        gallery_sequence[17]       = 2;  
        gallery_sequence_times[17] = 10;
        gallery_innocent[17] = TARGET_BOSS; 
        boss_total_score += 30;
                
        gallery_sequence[18]       = 6;  
        gallery_sequence_times[18] = 10;
        gallery_innocent[18] = TARGET_BOSS; 
        boss_total_score += 30;
                
        gallery_sequence[19]       = 9;  
        gallery_sequence_times[19] = 10;
        gallery_innocent[19] = TARGET_BOSS;  
        boss_total_score += 30;
                
        gallery_sequence[20]       = 7;  
        gallery_sequence_times[20] = 10;
        gallery_innocent[20] = TARGET_BOSS; 
        boss_total_score += 30;
                
        gallery_sequence[21]       = 4;   
        gallery_sequence_times[21] = 10;
        gallery_innocent[21] = TARGET_BOSS; 
        boss_total_score += 30;
        
        boss_gallery_health = boss_total_score;                                                                          
        
        gallery_count = 22;  
         
        gallery_pause[0] = 1;   
        gallery_pause[1] = 2;
        gallery_pause[2] = 3; 
        gallery_pause[3] = 4;   
        gallery_pause[4] = 5;
        gallery_pause[5] = 6; 
        gallery_pause[6] = 7;    
        gallery_pause[7] = 8;
        gallery_pause[8] = 9; 
        gallery_pause[9] = 10;   
        gallery_pause[10] = 11;
        gallery_pause[11] = 12;                         
        gallery_pause[12] = 13;
        gallery_pause[13] = 14;                         
        gallery_pause[14] = 15; 
        gallery_pause[15] = 16;   
        gallery_pause[16] = 17;
        gallery_pause[17] = 18;                         
        gallery_pause[18] = 19;
        gallery_pause[19] = 20;           
        gallery_pause[20] = 21;          
          
    }   

    if(index == 4) 
    { 
              
        gallery_count = 0;
              
        gallery_sequence[gallery_count]       = 7; 
        gallery_sequence_times[gallery_count] = 5000;
        gallery_innocent[gallery_count] = TARGET_CHIEF;
        gallery_count++;
        
        gallery_sequence[gallery_count]       = 6; 
        gallery_sequence_times[gallery_count] = 3000;
        gallery_innocent[gallery_count] = TARGET_GUNNER;         
        gallery_count++;
 
        gallery_sequence[gallery_count]       = 8;
        gallery_sequence_times[gallery_count] = 1000; 
        gallery_innocent[gallery_count] = TARGET_CHIEF;        
        gallery_count++;  
       
        gallery_sequence[gallery_count]       = 2; 
        gallery_sequence_times[gallery_count] = 2000;
        gallery_innocent[gallery_count] = TARGET_CHIEF;    
        gallery_count++;
       
        gallery_sequence[gallery_count]       = 5;
        gallery_sequence_times[gallery_count] = 3000; 
        gallery_innocent[gallery_count] = TARGET_GUNNER;        
        gallery_count++;  // 5
        
        gallery_sequence[gallery_count]       = 6; 
        gallery_sequence_times[gallery_count] = 1500;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;
        gallery_count++;
        
        gallery_sequence[gallery_count]       = 13; 
        gallery_sequence_times[gallery_count] = 3000;
        gallery_innocent[gallery_count] = TARGET_CHIEF;        
        gallery_count++; 
 
        gallery_sequence[gallery_count]       = 8; 
        gallery_sequence_times[gallery_count] = 3000; 
        gallery_innocent[gallery_count] = TARGET_GUNNER; 
        gallery_count++;
          
        gallery_sequence[gallery_count]       = 13;
        gallery_sequence_times[gallery_count] = 1000;  
        gallery_innocent[gallery_count] = TARGET_GUNNER; 
        gallery_count++;
        
        gallery_sequence[gallery_count]       = 34;
        gallery_sequence_times[gallery_count] = 1000;  
        gallery_innocent[gallery_count] = TARGET_CHIEF;          
        gallery_count++;
         
        gallery_sequence[gallery_count]       = 35;
        gallery_sequence_times[gallery_count] = 4000; 
        gallery_innocent[gallery_count] = TARGET_GUNNER;          
        gallery_count++;
        
        gallery_sequence[gallery_count]       = 36; 
        gallery_sequence_times[gallery_count] = 1000; 
        gallery_innocent[gallery_count] = TARGET_BUDDY;
        gallery_count++; // 15
        
        gallery_sequence[gallery_count]       = 46;
        gallery_sequence_times[gallery_count] = 3000;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++;
        
        gallery_sequence[gallery_count]       = 34;
        gallery_sequence_times[gallery_count] = 4000; 
        gallery_innocent[gallery_count] = TARGET_CHIEF;                 
        gallery_count++;
          
        gallery_sequence[gallery_count]       = 38;
        gallery_sequence_times[gallery_count] = 2000;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++;  // 20      
        
        gallery_sequence[gallery_count]       = 47;
        gallery_sequence_times[gallery_count] = 1500;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++;    
        
        gallery_sequence[gallery_count]       = 48;
        gallery_sequence_times[gallery_count] = 1500;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++;  // 23    
        
        gallery_sequence[gallery_count]       = 46;
        gallery_sequence_times[gallery_count] = 1500;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++;   
         
        gallery_sequence[gallery_count]       = 47; 
        gallery_sequence_times[gallery_count] = 1000;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++;    

        gallery_sequence[gallery_count]       = 37; 
        gallery_sequence_times[gallery_count] = 3000;  
        gallery_innocent[gallery_count] = TARGET_CHIEF;                
        gallery_count++;   
                
        gallery_sequence[gallery_count]       = 48;
        gallery_sequence_times[gallery_count] = 2000;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++; // 26   
                
        gallery_sequence[gallery_count]       = 58;
        gallery_sequence_times[gallery_count] = 2000;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++; // 26   
                
        gallery_sequence[gallery_count]       = 44;
        gallery_sequence_times[gallery_count] = 1000;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++; // 26   
                
        gallery_sequence[gallery_count]       = 51; 
        gallery_sequence_times[gallery_count] = 3000;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++; // 26      
                
        gallery_sequence[gallery_count]       = 58;   
        gallery_sequence_times[gallery_count] = 2000;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++; // 26           
                
        gallery_sequence[gallery_count]       = 60; 
        gallery_sequence_times[gallery_count] = 2000;   
        gallery_innocent[gallery_count] = TARGET_BUDDY;                 
        gallery_count++; // 26           
                
        gallery_sequence[gallery_count]       = 59; 
        gallery_sequence_times[gallery_count] = 200;   
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++; // 26           
                 
        gallery_sequence[gallery_count]       = 50; 
        gallery_sequence_times[gallery_count] = 3000;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++; // 26           
                
        gallery_sequence[gallery_count]       = 51; 
        gallery_sequence_times[gallery_count] = 2000;   
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++; // 26    
                
        gallery_sequence[gallery_count]       = 61; 
        gallery_sequence_times[gallery_count] = 100;   
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++; // 26     
                 
        gallery_sequence[gallery_count]       = 53; 
        gallery_sequence_times[gallery_count] = 100;   
        gallery_innocent[gallery_count] = TARGET_BUDDY;                
        gallery_count++; // 26                             
                 
        gallery_sequence[gallery_count]       = 50; 
        gallery_sequence_times[gallery_count] = 2000;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++; // 26        
                  
        gallery_sequence[gallery_count]       = 59; 
        gallery_sequence_times[gallery_count] = 2000;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++; // 26                   
                 
        gallery_sequence[gallery_count]       = 50; 
        gallery_sequence_times[gallery_count] = 2000;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++; // 26  
                  
        gallery_sequence[gallery_count]       = 52; 
        gallery_sequence_times[gallery_count] = 1000;  
        gallery_innocent[gallery_count] = TARGET_GUNNER;                
        gallery_count++; // 26     
        
        gallery_pause[0] = gallery_count-1;                 
           
    }        

    if(index == 5)  
    {   
              
        gallery_sequence[0]       = 7;
        gallery_sequence_times[0] = 2000;
        gallery_innocent[0] = TARGET_CHIEF;
        
        gallery_sequence[1]       = 6; 
        gallery_sequence_times[1] = 2000;
        gallery_innocent[1] = TARGET_GUNNER;        

        gallery_sequence[2]       = 4;
        gallery_sequence_times[2] = 2000; 
        gallery_innocent[2] = TARGET_GUNNER;        
        
        gallery_sequence[3]       = 13;  
        gallery_sequence_times[3] = 1000;
        gallery_innocent[3] = TARGET_CHIEF;    
        
        gallery_sequence[4]       = 12; 
        gallery_sequence_times[4] = 1000; 
        gallery_innocent[4] = TARGET_SAILOR;         
        gallery_direction[4] = RIGHT;   
                
        gallery_sequence[5]       = 5;  
        gallery_sequence_times[5] = 6000; 
        gallery_innocent[5] = TARGET_GUNNER;    
        
        gallery_sequence[6]       = 8;
        gallery_sequence_times[6] = 3000; 
        gallery_innocent[6] = TARGET_CHIEF;
        
        gallery_sequence[7]       = 5;  
        gallery_sequence_times[7] = 400;
        gallery_innocent[7] = TARGET_GUNNER;        
        
        gallery_sequence[8]       = 6;
        gallery_sequence_times[8] = 2000;
        gallery_innocent[8] = TARGET_GUNNER;        
        
        gallery_sequence[9]       = 4;  
        gallery_sequence_times[9] = 2000; 
        gallery_innocent[9] = TARGET_GUNNER;         
                
        gallery_sequence[10]       = 9; 
        gallery_sequence_times[10] = 2000; 
        gallery_innocent[10] = TARGET_SAILOR;        
        gallery_direction[10] = LEFT;  
                     
        gallery_sequence[11]       = 4;
        gallery_sequence_times[11] = 6000;
        gallery_innocent[11] = TARGET_GUNNER; 
        
        gallery_sequence[12]       = 6;
        gallery_sequence_times[12] = 100;
        gallery_innocent[12] = TARGET_GUNNER;

               
        gallery_count = 13;
        
        gallery_pause[0] = 1;
        gallery_pause[1] = 3;  
        gallery_pause[2] = 6;  
        gallery_pause[3] = 7;       
        gallery_pause[4] = 10;           
        gallery_pause[5] = 11;   
 
          
    }

    if(index == 6)  
    {   
              
        gallery_sequence[0]       = 6;
        gallery_sequence_times[0] = 2000; // Pop me up in 2 seconds...
        gallery_innocent[0] = TARGET_GUNNER;
        
        gallery_sequence[1]       = 2; 
        gallery_sequence_times[1] = 1000;
        gallery_innocent[1] = TARGET_CHIEF;        
        
        gallery_sequence[2]       = 4; 
        gallery_sequence_times[2] = 1000;
        gallery_innocent[2] = TARGET_GUNNER;
         
        gallery_sequence[3]       = 8; 
        gallery_sequence_times[3] = 2000;
        gallery_innocent[3] = TARGET_CHIEF;
                 
        gallery_sequence[4]       = 4;  
        gallery_sequence_times[4] = 3000; 
        gallery_innocent[4] = TARGET_GUNNER;        
        
        gallery_sequence[5]       = 13;  
        gallery_sequence_times[5] = 2000;
        gallery_innocent[5] = TARGET_CHIEF;
         
        gallery_sequence[6]       = 7; 
        gallery_sequence_times[6] = 1000;
        gallery_innocent[6] = TARGET_CHIEF;
        
        gallery_sequence[7]       = 5; 
        gallery_sequence_times[7] = 2000; 
        gallery_innocent[7] = TARGET_GUNNER;         

        gallery_sequence[8]       = 2; 
        gallery_sequence_times[8] = 1000;
        gallery_innocent[8] = TARGET_CHIEF;  
        
        gallery_sequence[9]       = 13; 
        gallery_sequence_times[9] = 500;
        gallery_innocent[9] = TARGET_CHIEF;  
          
        gallery_sequence[10]       = 6; 
        gallery_sequence_times[10] = 3000; 
        gallery_innocent[10] = TARGET_GUNNER;
         
        gallery_sequence[11]       = 8;  
        gallery_sequence_times[11] = 500;
        gallery_innocent[11] = TARGET_CHIEF;        
        
        gallery_sequence[12]       = 2;  
        gallery_sequence_times[12] = 100;
        gallery_innocent[12] = TARGET_CHIEF;  
                                                                       
        gallery_count = 13;
        
        gallery_pause[0] = 3;  
        gallery_pause[1] = 5;          
        gallery_pause[2] = 8;
        gallery_pause[3] = 10;        
        gallery_pause[4] = 12;         
                         
    } 


    if(index == 7)   
    {     
          
        boss_total_score = 0;
               
        gallery_sequence[0]       = 6;
        gallery_sequence_times[0] = 2000; // Pop me up in 2 seconds...
        gallery_innocent[0] = TARGET_BOSS;
        boss_total_score += 30;
        
        gallery_sequence[1]       = 8; 
        gallery_sequence_times[1] = 2000;
        gallery_innocent[1] = TARGET_BOSS;        
        boss_total_score += 30;
        
        gallery_sequence[2]       = 4; 
        gallery_sequence_times[2] = 2000;
        gallery_innocent[2] = TARGET_BOSS;                  
        boss_total_score += 30;
        
        gallery_sequence[3]       = 4; 
        gallery_sequence_times[3] = 2000;
        gallery_innocent[3] = TARGET_BOSS; 
        boss_total_score += 30;
        
        gallery_sequence[4]       = 8; 
        gallery_sequence_times[4] = 2000;
        gallery_innocent[4] = TARGET_BOSS;         
        boss_total_score += 30;
        
        gallery_sequence[5]       = 6; 
        gallery_sequence_times[5] = 2000;
        gallery_innocent[5] = TARGET_BOSS;           
        boss_total_score += 30;
        
        gallery_sequence[6]       = 41; 
        gallery_sequence_times[6] = 2000;
        gallery_innocent[6] = TARGET_BOSS; 
        boss_total_score += 30;
        
        gallery_sequence[7]       = 8; 
        gallery_sequence_times[7] = 6000;
        gallery_innocent[7] = TARGET_BOSS; 
        boss_total_score += 30;
        
        gallery_sequence[8]       = 4;
        gallery_sequence_times[8] = 1000;
        gallery_innocent[8] = TARGET_BOSS; 
        boss_total_score += 30;
         
        gallery_sequence[9]       = 6; 
        gallery_sequence_times[9] = 1000;
        gallery_innocent[9] = TARGET_BOSS; 
        boss_total_score += 30;
        
        gallery_sequence[10]       = 4; 
        gallery_sequence_times[10] = 1000;
        gallery_innocent[10] = TARGET_BOSS; 
        boss_total_score += 30;
        
        gallery_sequence[11]       = 8;
        gallery_sequence_times[11] = 1000;
        gallery_innocent[11] = TARGET_BOSS; 
        boss_total_score += 30;
        
        gallery_sequence[12]       = 6; 
        gallery_sequence_times[12] = 1000;
        gallery_innocent[12] = TARGET_BOSS; 
        boss_total_score += 30;
        
        
        gallery_sequence[13]       = 6; 
        gallery_sequence_times[13] = 6000;
        gallery_innocent[13] = TARGET_BOSS; 
        boss_total_score += 30;
        
        gallery_sequence[14]       = 43;  
        gallery_sequence_times[14] = 10;
        gallery_innocent[14] = TARGET_BUDDY;                                                                 
    //    boss_total_score += 30;
        
        gallery_sequence[15]       = 4;  
        gallery_sequence_times[15] = 10;
        gallery_innocent[15] = TARGET_BOSS; 
        boss_total_score += 30;
                
        gallery_sequence[16]       = 8;  
        gallery_sequence_times[16] = 10;
        gallery_innocent[16] = TARGET_BOSS; 
        boss_total_score += 30;
                
        gallery_sequence[17]       = 4;  
        gallery_sequence_times[17] = 10;
        gallery_innocent[17] = TARGET_BOSS; 
        boss_total_score += 30;
                
        gallery_sequence[18]       = 6;  
        gallery_sequence_times[18] = 10;
        gallery_innocent[18] = TARGET_BOSS;   
        boss_total_score += 30;
                
        gallery_sequence[19]       = 42;  
        gallery_sequence_times[19] = 10;
        gallery_innocent[19] = TARGET_BUDDY; 
                
        gallery_sequence[20]       = 8;  
        gallery_sequence_times[20] = 10;
        gallery_innocent[20] = TARGET_BOSS;  
        boss_total_score += 30; 
                
        gallery_sequence[21]       = 4;   
        gallery_sequence_times[21] = 10;
        gallery_innocent[21] = TARGET_BOSS;  
        boss_total_score += 30;
        
        boss_gallery_health = boss_total_score;  
                                                                                           
        gallery_count = 22;  
         
        gallery_pause[0] = 1;   
        gallery_pause[1] = 2;
        gallery_pause[2] = 3; 
        gallery_pause[3] = 4;    
        gallery_pause[4] = 5; 
        gallery_pause[5] = 6; 
        gallery_pause[6] = 7;    
        gallery_pause[7] = 8;
        gallery_pause[8] = 9; 
        gallery_pause[9] = 10;   
        gallery_pause[10] = 11;
        gallery_pause[11] = 12;                         
        gallery_pause[12] = 13;
        gallery_pause[13] = 14;                         
        gallery_pause[14] = 15; 
        gallery_pause[15] = 16;   
        gallery_pause[16] = 17;
        gallery_pause[17] = 18;                          
        gallery_pause[18] = 19;
        gallery_pause[19] = 20;           
        gallery_pause[20] = 21;           

    }   
    if(index == 8)    
    {     
               
        gallery_sequence[0]       = 6;
        gallery_sequence_times[0] = 2000; // Pop me up in 2 seconds...
        gallery_innocent[0] = TARGET_BOSS;
        
        gallery_sequence[1]       = 8; 
        gallery_sequence_times[1] = 2000;
        gallery_innocent[1] = TARGET_BOSS;        
        
        gallery_sequence[2]       = 4; 
        gallery_sequence_times[2] = 2000;
        gallery_innocent[2] = TARGET_BOSS;                  
        
        gallery_sequence[3]       = 4; 
        gallery_sequence_times[3] = 2000;
        gallery_innocent[3] = TARGET_BOSS; 
        
        gallery_sequence[4]       = 8; 
        gallery_sequence_times[4] = 2000;
        gallery_innocent[4] = TARGET_BOSS;         
        
        gallery_sequence[5]       = 6; 
        gallery_sequence_times[5] = 2000;
        gallery_innocent[5] = TARGET_BOSS;           
        
        gallery_sequence[6]       = 8; 
        gallery_sequence_times[6] = 2000;
        gallery_innocent[6] = TARGET_BOSS; 
                                                                      
        gallery_count = 7;  
         
        gallery_pause[0] = 1;   
        gallery_pause[1] = 2;
        gallery_pause[2] = 3; 
        gallery_pause[3] = 4;   
        gallery_pause[4] = 5;
        gallery_pause[5] = 6; 
        gallery_pause[6] = 7;    
          
    }   
    if(index == 9)     
    {     
               
        gallery_sequence[0]       = 6;
        gallery_sequence_times[0] = 2000; // Pop me up in 2 seconds...
        gallery_innocent[0] = TARGET_BOSS;
        
        gallery_sequence[1]       = 8; 
        gallery_sequence_times[1] = 2000;
        gallery_innocent[1] = TARGET_BOSS;        
        
        gallery_sequence[2]       = 5; 
        gallery_sequence_times[2] = 2000;
        gallery_innocent[2] = TARGET_BOSS;                  
        
        gallery_sequence[3]       = 4; 
        gallery_sequence_times[3] = 2000;
        gallery_innocent[3] = TARGET_BOSS; 
        
        gallery_sequence[4]       = 2;  
        gallery_sequence_times[4] = 2000;
        gallery_innocent[4] = TARGET_BOSS;         
        
        gallery_sequence[5]       = 6; 
        gallery_sequence_times[5] = 2000;
        gallery_innocent[5] = TARGET_BOSS;           
        
        gallery_sequence[6]       = 8; 
        gallery_sequence_times[6] = 2000;
        gallery_innocent[6] = TARGET_BOSS; 
                                                                      
        gallery_count = 7;  
         
        gallery_pause[0] = 1;   
        gallery_pause[1] = 2;
        gallery_pause[2] = 3; 
        gallery_pause[3] = 4;   
        gallery_pause[4] = 5;
        gallery_pause[5] = 6; 
        gallery_pause[6] = 7;    
          
    }    
    if(index == 10)     
    {     
               
        gallery_sequence[0]       = 6;
        gallery_sequence_times[0] = 2000; // Pop me up in 2 seconds...
        gallery_innocent[0] = TARGET_BOSS;
        
        gallery_sequence[1]       = 8; 
        gallery_sequence_times[1] = 2000;
        gallery_innocent[1] = TARGET_BOSS;        
        
        gallery_sequence[2]       = 4; 
        gallery_sequence_times[2] = 2000;
        gallery_innocent[2] = TARGET_BOSS;                  
        
        gallery_sequence[3]       = 4; 
        gallery_sequence_times[3] = 2000;
        gallery_innocent[3] = TARGET_BOSS; 
        
        gallery_sequence[4]       = 8; 
        gallery_sequence_times[4] = 2000;
        gallery_innocent[4] = TARGET_BOSS;         
        
        gallery_sequence[5]       = 6; 
        gallery_sequence_times[5] = 2000;
        gallery_innocent[5] = TARGET_BOSS;           
        
        gallery_sequence[6]       = 8; 
        gallery_sequence_times[6] = 2000;
        gallery_innocent[6] = TARGET_BOSS; 
                                                                      
        gallery_count = 7;  
         
        gallery_pause[0] = 1;   
        gallery_pause[1] = 2;
        gallery_pause[2] = 3; 
        gallery_pause[3] = 4;   
        gallery_pause[4] = 5;
        gallery_pause[5] = 6; 
        gallery_pause[6] = 7;    
           
    }       
    if(index == 11)      
    {        
                    
        if(current_difficulty == EASY_MODE)
            boss_total_score = CORE_HEALTH_EASY;
        if(current_difficulty == NORMAL_MODE)
            boss_total_score = CORE_HEALTH_NORMAL;
        if(current_difficulty == HARD_MODE)
            boss_total_score = CORE_HEALTH_HARD;    

        boss_gallery_health = boss_total_score; 
               
        gallery_sequence[0]       = 6;
        gallery_sequence_times[0] = 1000; // Pop me up in 2 seconds...
        gallery_innocent[0] = TARGET_BOSS; 
        
        gallery_sequence[1]       = 8; 
        gallery_sequence_times[1] = 1000;  
        gallery_innocent[1] = TARGET_BOSS;        
        
        gallery_sequence[2]       = 4;  
        gallery_sequence_times[2] = 1000; 
        gallery_innocent[2] = TARGET_BOSS;                  
         
        gallery_sequence[3]       = 4; 
        gallery_sequence_times[3] = 1000; 
        gallery_innocent[3] = TARGET_BOSS; 
         
        gallery_sequence[4]       = 8; 
        gallery_sequence_times[4] = 1000;  
        gallery_innocent[4] = TARGET_BOSS;         
        
        gallery_sequence[5]       = 6; 
        gallery_sequence_times[5] = 1000;  
        gallery_innocent[5] = TARGET_BOSS;           
         
        gallery_sequence[6]       = 8; 
        gallery_sequence_times[6] = 8000;
        gallery_innocent[6] = TARGET_BOSS; 
                                                                      
        gallery_count = 7;   

        gallery_pause[0] = 1;   
        gallery_pause[1] = 2;
        gallery_pause[2] = 3; 
        gallery_pause[3] = 4;   
        gallery_pause[4] = 5;
        gallery_pause[5] = 6; 
        gallery_pause[6] = 7;    
          
    }    
    if(index == 16) 
    { 
              
        gallery_sequence[0]       = 2;
        gallery_sequence_times[0] = 2000;
        gallery_innocent[0] = TARGET_CHIEF;
        
        gallery_sequence[1]       = 6;
        gallery_sequence_times[1] = 3000;
        gallery_innocent[1] = TARGET_GUNNER;        

        gallery_sequence[2]       = 8;
        gallery_sequence_times[2] = 1000; 
        gallery_innocent[2] = TARGET_CHIEF;        
       
        gallery_sequence[3]       = 7; 
        gallery_sequence_times[3] = 2000;
        gallery_innocent[3] = TARGET_CHIEF;    
       
        gallery_sequence[4]       = 5;
        gallery_sequence_times[4] = 500; 
        gallery_innocent[4] = TARGET_GUNNER;        
        
        gallery_sequence[5]       = 6;
        gallery_sequence_times[5] = 4000; 
        gallery_innocent[5] = TARGET_GUNNER;
        
        gallery_sequence[6]       = 13;
        gallery_sequence_times[6] = 1000;
        gallery_innocent[6] = TARGET_CHIEF;        
               
        gallery_count = 7; 
        
        gallery_pause[0] = 3;
        gallery_pause[1] = 4;              
        gallery_pause[2] = 6;          

        
    }     
         
    if(index == 17)  
    {   

        gallery_sequence[0]       = 7;
        gallery_sequence_times[0] = 2000;
        gallery_innocent[0] = TARGET_CHIEF;

        gallery_sequence[1]       = 6; 
        gallery_sequence_times[1] = 500;
        gallery_innocent[1] = TARGET_GUNNER;        

        gallery_sequence[2]       = 4;
        gallery_sequence_times[2] = 2000; 
        gallery_innocent[2] = TARGET_GUNNER;        
        
        gallery_sequence[3]       = 13;  
        gallery_sequence_times[3] = 1000;
        gallery_innocent[3] = TARGET_CHIEF;    
        
        gallery_sequence[4]       = 12; 
        gallery_sequence_times[4] = 1000; 
        gallery_innocent[4] = TARGET_SAILOR;          
        gallery_direction[4] = RIGHT;    
                
        gallery_sequence[5]       = 5;  
        gallery_sequence_times[5] = 6000; 
        gallery_innocent[5] = TARGET_GUNNER;  
        gallery_id[5] = 17;  
        
        gallery_sequence[6]       = 8;
        gallery_sequence_times[6] = 3000; 
        gallery_innocent[6] = TARGET_CHIEF;
        
        gallery_sequence[7]       = 5;   
        gallery_sequence_times[7] = 400;
        gallery_innocent[7] = TARGET_BUDDY; 
        gallery_id[7] = 25;         
         
        gallery_sequence[8]       = 6;
        gallery_sequence_times[8] = 2000;
        gallery_innocent[8] = TARGET_GUNNER;        
        
        gallery_sequence[9]       = 4;  
        gallery_sequence_times[9] = 2000; 
        gallery_innocent[9] = TARGET_GUNNER;         
                
        gallery_sequence[10]       = 9; 
        gallery_sequence_times[10] = 2000; 
        gallery_innocent[10] = TARGET_SAILOR;        
        gallery_direction[10] = LEFT;  
                     
        gallery_sequence[11]       = 4;
        gallery_sequence_times[11] = 6000;
        gallery_innocent[11] = TARGET_GUNNER;  
        
        gallery_sequence[12]       = 6;
        gallery_sequence_times[12] = 100;
        gallery_innocent[12] = TARGET_GUNNER;

               
        gallery_count = 13;
        
        gallery_pause[0] = 3;  
        gallery_pause[1] = 6;         
        gallery_pause[2] = 10;           
        gallery_pause[3] = 11;   

          
    }  
        
         
}


void Run_Cards(int f_rate)
{ 
    int card_index = 0;
    bool has_page1 = false;
    bool has_page2 = false;
    bool has_page3 = false;
    bool has_page4 = false; 

	if(f_rate <= 0)
	    f_rate = 1; 
    
    if(card_page == 1)
        card_index = 0; 
    if(card_page == 2)
        card_index = 12;
    if(card_page == 3)
        card_index = 24;  
                                                                                             
    for(int i = 0; i < 36; i++)    
    if(Has_This_Item(INV_CARD, i) == true)
    {
        if(i<12) 
            has_page1 = true;
        if(i>=12 && i < 24)
            has_page2 = true; 
        if(i>=24 && i < 36)
            has_page3 = true;
    //    if(i>=36 && i < 48)
    //        has_page4 = true;
    }      
     
    sprite[6].id  = 7+card_page;
    sprite[3].id  = 7+card_page;
    sprite[9].id  = 7+card_page;
    sprite[10].id = 7+card_page;

    sprite[7].id  = 7+card_page;
    sprite[4].id  = 7+card_page;
    sprite[11].id = 7+card_page;
    sprite[12].id = 7+card_page;

    sprite[8].id  = 7+card_page;
    sprite[5].id  = 7+card_page;
    sprite[13].id = 7+card_page;
    sprite[14].id = 7+card_page;
                          
    if(gallery_title_sequence == 0) 
    { 
    
        if(has_page3 == true)
            card_page = 3;
        if(has_page2 == true)
            card_page = 2;
        if(has_page1 == true)
            card_page = 1; 
        
        if(card_page == 1)
            card_index = 0; 
        if(card_page == 2)
            card_index = 12;
        if(card_page == 3)
            card_index = 24;  
                      
        for(int i=0;i<no_sprites;i++) 
        {
            sprite[i].flash_timer = 0;
        }          
        
        if(current_act == 2) 
        {
            sprite[17].id+=2; // Stunned   
        }
         
        if(current_act == 3) 
        {
            sprite[17].id+=2; // Stunned  
        //    sprite[18].id+=3; // Stunned  
        }
                                  
        sprite[15].alpha = 0.0f;              
        prize_timer = 0;
        cards_popup_count = 0;
        card_start=0;
        card_flash_timer1=0;
        displaying_prize=false; 

        sprite[6].id  = 7+card_page;
        sprite[3].id  = 7+card_page;
        sprite[9].id  = 7+card_page;
        sprite[10].id = 7+card_page;

        sprite[7].id  = 7+card_page;
        sprite[4].id  = 7+card_page;
        sprite[11].id = 7+card_page;
        sprite[12].id = 7+card_page;

        sprite[8].id  = 7+card_page;
        sprite[5].id  = 7+card_page;
        sprite[13].id = 7+card_page;
        sprite[14].id = 7+card_page;

           
        if(global_cards[card_index] != CARD_BLANK) 
            Set_Sprite(6, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(global_cards[card_index+1] != CARD_BLANK)
            Set_Sprite(3, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(global_cards[card_index+2] != CARD_BLANK)
            Set_Sprite(9, 4, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(global_cards[card_index+3] != CARD_BLANK)
            Set_Sprite(10, 5, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
             
        if(global_cards[card_index+4] != CARD_BLANK)
            Set_Sprite(7, 6, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(global_cards[card_index+5] != CARD_BLANK)
            Set_Sprite(4, 7, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(global_cards[card_index+6] != CARD_BLANK) 
            Set_Sprite(11, 8, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(global_cards[card_index+7] != CARD_BLANK)
            Set_Sprite(12, 9, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
              
        if(global_cards[card_index+8] != CARD_BLANK)
            Set_Sprite(8, 10, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(global_cards[card_index+9] != CARD_BLANK)
            Set_Sprite(5, 11, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(global_cards[card_index+10] != CARD_BLANK)
            Set_Sprite(13, 12, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(global_cards[card_index+11] != CARD_BLANK) 
            Set_Sprite(14, 13, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                                  
   /*     for(int i = card_index; i < card_index+12; i++)    
        if(Has_This_Item(INV_CARD, i) == true)
        { 
            cards_popup_value[cards_popup_count] = Get_Number_Of_Item(INV_CARD, i, -1, false);                       
            Remove_Item(INV_CARD, i, -1, true);                           
            cards_popup[cards_popup_count] = i;
            cards_popup_count++; 
            displaying_prize = true;
        }    */
        
        if(cards_popup_count > 0)
        {
            prize_sequence = 1;
            prize_timer = (int)TimerGetTime() + 500;
        }
                     
        gallery_title_sequence++;                  
    }       
     
    if(gallery_title_sequence == 1)  
    { 
                        
       sprintf( counter[5].word, "");   
       sprintf( counter[0].word, ""); 
          
       counter[0].alpha = 0.0f; 
       sprite[1].alpha = 0.0f; 
       sprite[16].alpha = 0.0f;
       sprite[17].alpha = 0.0f;
       sprite[18].alpha = 0.0f;
       sprite[19].alpha = 0.0f;
   //    sprite[20].alpha = 0.0f;
        
       if(prize_sequence != 2)
       if((int)TimerGetTime() > prize_timer)
       if(card_start == cards_popup_count) 
       {
           displaying_prize = false;
           prize_sequence = 3;
           sprite[1].alpha = 1.0f; 
           sprite[16].alpha = 1.0f;
           sprite[17].alpha = 1.0f;
           sprite[18].alpha = 1.0f;
           sprite[19].alpha = 1.0f;
       //    sprite[20].alpha = 1.0f; 
                  
           if(has_page3 == true && card_page != 3)
           {
               card_page = 3;
               next_scene = true;
           }    
                             
           if(has_page2 == true && card_page != 2)
           {
               card_page = 2;
               next_scene = true;
           }
           
       }
      
       for(int i=0;i<no_sprites;i++)
       {
       
         if(sprite[i].flash_timer != 0)
         if((int)TimerGetTime() > card_flash_timer1 )
         {
 
           if(sprite[i].alpha == 0.0)         
              sprite[i].alpha = 1.0f;
           else  
              sprite[i].alpha = 0.0f;  
              
           // Create a star effect...
           if(rand()%2 == 0)
               Create_Star_Effect( (sprite[i].x+sprite[i].width/2), (sprite[i].y+sprite[i].height/2), 0.1f, 22);
           else
               Create_Star_Effect( (sprite[i].x+sprite[i].width/2), (sprite[i].y+sprite[i].height/2), 0.15f, 22);
           
   
         } 
         if(sprite[i].flash_timer != 0)
         if((int)TimerGetTime() > sprite[i].flash_timer )
         {
             sprite[i].alpha = 1.0f;
             sprite[i].flash_timer = 0;
         } 
       
       }   
     
       if((int)TimerGetTime() > card_flash_timer1 )
         card_flash_timer1 = (int)TimerGetTime() + 150; 

       if(prize_sequence == 1)
       if(card_start != cards_popup_count)   
       if((int)TimerGetTime() > prize_timer) 
       for(int i=card_start;i<cards_popup_count;i++)
       { 
  
               Set_Card(cards_popup[i], cards_popup_value[i]); 
               prize_timer = (int)TimerGetTime() + 1500;
               cash_sfx = true;
               card_start++;    
                
               if(cards_popup[i] == card_index)
                   sprite[6].flash_timer = (int)TimerGetTime() + 1500;
               if(cards_popup[i] == card_index+1)
                   sprite[3].flash_timer = (int)TimerGetTime() + 1500;
               if(cards_popup[i] == card_index+2)
                   sprite[9].flash_timer = (int)TimerGetTime() + 1500;
               if(cards_popup[i] == card_index+3)
                   sprite[10].flash_timer = (int)TimerGetTime() + 1500;
                
               if(cards_popup[i] == card_index+4)
                   sprite[7].flash_timer = (int)TimerGetTime() + 1500;
               if(cards_popup[i] == card_index+5)
                   sprite[4].flash_timer = (int)TimerGetTime() + 1500;
               if(cards_popup[i] == card_index+6)
                   sprite[11].flash_timer = (int)TimerGetTime() + 1500;
               if(cards_popup[i] == card_index+7)
                   sprite[12].flash_timer = (int)TimerGetTime() + 1500;                   
                
               if(cards_popup[i] == card_index+8)
                   sprite[8].flash_timer = (int)TimerGetTime() + 1500;
               if(cards_popup[i] == card_index+9)
                   sprite[5].flash_timer = (int)TimerGetTime() + 1500;
               if(cards_popup[i] == card_index+10)
                   sprite[13].flash_timer = (int)TimerGetTime() + 1500;
               if(cards_popup[i] == card_index+11)
                   sprite[14].flash_timer = (int)TimerGetTime() + 1500;                   
                   
   

                                                                                     
               i=cards_popup_count;

       } 
        
       if(prize_sequence == 2)  
       {   
 
                                                            
           counter[0].alpha = 1.0f;
           counter[0].x = -0.18f;     
           counter[0].y =  0.30f; 
           counter[0].width = 0.016f; 
           counter[0].height = 0.048f;
           
           if((int)TimerGetTime() > prize_timer || mouseleft == true)
           {
               prize_sequence = 1;
               mouseleft = false;
               prize_timer = 0;
           }
       }
       
       if(counter[0].alpha == 1.0)
       {
           sprite[15].alpha = 1.0f;
       }
       else
       {
           sprite[15].alpha = 0.0f;
       }

           
       if(displaying_prize == false)            
       for(int i = 3; i < 15; i++) 
       if(( mouseX < (sprite[i].w + sprite[i].box_width) )
       &&( mouseX > sprite[i].w)                            
       &&( mouseY < (sprite[i].z + sprite[i].box_height) )
       &&( mouseY > sprite[i].z))  
       { 
            
           if(mouseleft == true)
           {
               episode = 1;
               scene = 54; 
               next_scene = true;
           }
           
           card_selected = card_index;
                       
           if(i == 6) 
           {
              if( global_cards[card_index] == 10)
              {
                  if(card_page == 1)
                      sprintf( counter[5].word, "CARD^LUCILLE^(PERFECT)");
                  if(card_page == 2)
                      sprintf( counter[5].word, "CARD^CELINE^(PERFECT)");
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^EMMA^(PERFECT)");                      
                  counter[5].length = 2;  
              }
              else 
              { 
                  if(card_page == 1)
                      sprintf( counter[5].word, "CARD^LUCILLE_(%i)", global_cards[card_index]); 
                  if(card_page == 2)
                      sprintf( counter[5].word, "CARD^CELINE_(%i)", global_cards[card_index]); 
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^EMMA_(%i)", global_cards[card_index]);                       
                  counter[5].length = 1;  
              }                       
              card_selected = card_index+1;
           }
          if(i == 3) 
           {
              if( global_cards[card_index+1] == 10) 
              {
                  if(card_page == 1)
                      sprintf( counter[5].word, "CARD^MONA^(PERFECT)");
                  if(card_page == 2)
                      sprintf( counter[5].word, "CARD^CARLA^(PERFECT)");
                  counter[5].length = 2;  
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^ALLISON^(PERFECT)");                   
              }
              else
              {
                  if(card_page == 1)                  
                       sprintf( counter[5].word, "CARD^MONA_(%i)", global_cards[card_index+1]);
                  if(card_page == 2)                  
                       sprintf( counter[5].word, "CARD^CARLA_(%i)", global_cards[card_index+1]);  
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^ALLISON_(%i)", global_cards[card_index+1]);                                             
                  counter[5].length = 1;  
              }                   
              card_selected = card_index+2;
           }              
           if(i == 9)  
           { 
              if( global_cards[card_index+2] == 10)  
              {
                  if(card_page == 1)
                       sprintf( counter[5].word, "CARD^AUDRIE^(PERFECT)");
                  if(card_page == 2)
                       sprintf( counter[5].word, "CARD^HITOMI^(PERFECT)");                       
                  counter[5].length = 2;  
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^SCARLET^(PERFECT)");                   
              }
              else
              {
                  if(card_page == 1)
                      sprintf( counter[5].word, "CARD^AUDRIE_(%i)", global_cards[card_index+2]);
                  if(card_page == 2)
                      sprintf( counter[5].word, "CARD^HITOMI_(%i)", global_cards[card_index+2]); 
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^SCARLET_(%i)", global_cards[card_index+2]);                                            
                  counter[5].length = 1;  
              }                   
              card_selected = card_index+3;
           }              
           if(i == 10)
           {
              if( global_cards[card_index+3] == 10)
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^BETSY^(PERFECT)");    
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^HELENA^(PERFECT)");                             
                  counter[5].length = 2;  
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^FAITH^(PERFECT)");                   
              }
              else 
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^BETSY_(%i)", global_cards[card_index+3]);
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^HELENA_(%i)", global_cards[card_index+3]);  
                  if(card_page == 3)
                  sprintf( counter[5].word, "CARD^FAITH_(%i)", global_cards[card_index+3]);                                   
                  counter[5].length = 1;  
              }                   
              card_selected = card_index+4;
           }              


           if(i == 7)
           {
              if( global_cards[card_index+4] == 10)
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^AMANDA^(PERFECT)");   
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^CLAUDIA^(PERFECT)");                               
                  counter[5].length = 2;  
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^PENNY^(PERFECT)");                   
              }
              else 
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^AMANDA_(%i)", global_cards[card_index+4]);
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^CLAUDIA_(%i)", global_cards[card_index+4]);   
                  if(card_page == 3)
                  sprintf( counter[5].word, "CARD^PENNY_(%i)", global_cards[card_index+4]);                                  
                  counter[5].length = 1;  
              }                       
              card_selected = card_index+5;
           }              
           if(i == 4)
           {
              if( global_cards[card_index+5] == 10)
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^KELLY^(PERFECT)");   
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^LUCY^(PERFECT)");                               
                  counter[5].length = 2;  
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^HAILEY^(PERFECT)");                   
              }
              else
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^KELLY_(%i)", global_cards[card_index+5]);
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^LUCY_(%i)", global_cards[card_index+5]);   
                  if(card_page == 3)
                  sprintf( counter[5].word, "CARD^HAILEY_(%i)", global_cards[card_index+5]);                                  
                  counter[5].length = 1;  
              }                       
              card_selected = card_index+6;
           }              
           if(i == 11)
           {
              if( global_cards[card_index+6] == 10)
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^LINDA^(PERFECT)"); 
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^AMY^(PERFECT)");                                
                  counter[5].length = 2;  
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^LAYLA^(PERFECT)");                   
              }
              else
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^LINDA_(%i)", global_cards[card_index+6]);
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^AMY_(%i)", global_cards[card_index+6]);  
                  if(card_page == 3)
                  sprintf( counter[5].word, "CARD^LAYLA_(%i)", global_cards[card_index+6]);                                   
                  counter[5].length = 1;  
              }                       
              card_selected = card_index+7;
           }              
           if(i == 12)
           {
              if( global_cards[card_index+7] == 10)
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^LISA^(PERFECT)");  
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^GLENDA^(PERFECT)");                                
                  counter[5].length = 2;  
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^JASMINE^(PERFECT)");                   
              }
              else
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^LISA_(%i)", global_cards[card_index+7]);
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^GLENDA_(%i)", global_cards[card_index+7]);   
                  if(card_page == 3)
                  sprintf( counter[5].word, "CARD^JASMINE_(%i)", global_cards[card_index+7]);                                  
                  counter[5].length = 1;  
              }                       
              card_selected = card_index+8;
           }              
              
              
              
           if(i == 8)                     
           {
              if( global_cards[card_index+8] == 10)
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^HILDA^(PERFECT)");
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^LAURA^(PERFECT)");                                    
                  counter[5].length = 2;  
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^STELLA^(PERFECT)");                   
              }
              else
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^HILDA_(%i)", global_cards[card_index+8]); 
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^LAURA_(%i)", global_cards[card_index+8]);  
                  if(card_page == 3)
                  sprintf( counter[5].word, "CARD^STELLA_(%i)", global_cards[card_index+8]);                                    
                  counter[5].length = 1;  
              }                       
              card_selected = card_index+9;
           }              
           if(i == 5)                    
           {
              if( global_cards[card_index+9] == 10)
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^CHLOE^(PERFECT)");
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^MANDY^(PERFECT)");                                 
                  counter[5].length = 2;  
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^BELLA^(PERFECT)");                   
              }
              else
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^CHLOE_(%i)", global_cards[card_index+9]);
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^MANDY_(%i)", global_cards[card_index+9]); 
                  if(card_page == 3)
                  sprintf( counter[5].word, "CARD^BELLA_(%i)", global_cards[card_index+9]);                                       
                  counter[5].length = 1;  
              }                       
              card_selected = card_index+10;
           }              
           if(i == 13)                    
           {
              if( global_cards[card_index+10] == 10)
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^HEPBURN^(PERFECT)");
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^ISABELLE^(PERFECT)");                                  
                  counter[5].length = 2;  
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^BROOKE^(PERFECT)");                   
              }
              else
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^HEPBURN_(%i)", global_cards[card_index+10]);
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^ISABELLE_(%i)", global_cards[card_index+10]);    
                  if(card_page == 3)
                  sprintf( counter[5].word, "CARD^BROOKE_(%i)", global_cards[card_index+10]);                                  
                  counter[5].length = 1;  
              }                       
              card_selected = card_index+11;
           }              
           if(i == 14)                       
           {
              if( global_cards[card_index+11] == 10)
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^FIONA^PERFECT)");
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^LILLY^PERFECT)");                                 
                  counter[5].length = 2;  
                  if(card_page == 3)
                      sprintf( counter[5].word, "CARD^SARAH^(PERFECT)");                   
              }
              else 
              {
                  if(card_page == 1)
                  sprintf( counter[5].word, "CARD^FIONA_(%i)", global_cards[card_index+11]);
                  if(card_page == 2)
                  sprintf( counter[5].word, "CARD^LILLY_(%i)", global_cards[card_index+11]);   
                  if(card_page == 3)
                  sprintf( counter[5].word, "CARD^SARAH_(%i)", global_cards[card_index+11]);                                  
                  counter[5].length = 1;  
              }                       
              card_selected = card_index+12;
           }              
                 
           msg_left=true;                                                                           
           
           if(sprite[i].selected == false)        
           {
               radio_sfx = true;  
               sprite[i].selected = true;
           }       
                  
           Message_Limits();                     
            
       }   
       else 
           sprite[i].selected = false; 
             
//       sprintf( counter[5].word, "");
                    
       // Exit Button - EXIT 
       if(displaying_prize == false) 
       if(( mouseX < (sprite[1].w + sprite[1].box_width) )
       &&( mouseX > sprite[1].w)                            
       &&( mouseY < (sprite[1].z + sprite[1].box_height) )
       &&( mouseY > sprite[1].z)) 
       {
           
           Set_Sprite(1, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
           
           if(current_act != 4)
               sprintf( counter[5].word, "Return^to_Tent");
           else
               sprintf( counter[5].word, "Return^to_House");
                        
           counter[5].length = 1; 
             
           msg_left=false;  
               
           if(mouseleft == true)  
           {

               if(current_act != 4)
               {
			       episode = 1;    
                   scene   = 25;
			   } 
			   else
               {
			       episode = 1;    
                   scene   = 170;
			   } 
               
               shop_intro_type=SHOP_EXIT_TYPE;
               
               switch_n_sfx = true;
               next_scene = true;
               mouseleft = false;  
           }   
                     
       }      
       else
           Set_Sprite(1, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);         
                
       // Page 1 
       if(displaying_prize == false)                 
       if(( mouseX < (sprite[16].w + sprite[16].box_width) )
       &&( mouseX > sprite[16].w)                            
       &&( mouseY < (sprite[16].z + sprite[16].box_height) )
       &&( mouseY > sprite[16].z)) 
       { 
            
           Set_Sprite(16, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                  
           sprintf( counter[5].word, "Swimsuit^Album");
   
           counter[5].length = 1;     
           msg_left=true;   
           
           if(mouseleft == true)
           {
               card_page  = 1;
               next_scene = true;         
               click_sfx = true;         
               mouseleft = false;
           }                       
       } 
       else
           Set_Sprite(16, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);  
                
       // Page 2
       if(displaying_prize == false)                  
       if(( mouseX < (sprite[17].w + sprite[17].box_width) )
       &&( mouseX > sprite[17].w)                            
       &&( mouseY < (sprite[17].z + sprite[17].box_height) )
       &&( mouseY > sprite[17].z)) 
       { 
            
           Set_Sprite(17, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
           
           if(current_act > 1)  
           {         
               sprintf( counter[5].word, "Costume^Album");
               counter[5].length = 1;
           }
           else
           {         
               sprintf( counter[5].word, "Locked");
               counter[5].length = 0;
           }
           
                
           msg_left=true;   
           
           if(mouseleft == true)
           {
               if(current_act > 1)
               {         
                   card_page  = 2;
                   next_scene = true;                         
               }
               
               click_sfx = true;         
               mouseleft = false;
           }                       
       } 
       else
           Set_Sprite(17, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
                
       // Page 3
       if(displaying_prize == false)                  
       if(( mouseX < (sprite[18].w + sprite[18].box_width) )
       &&( mouseX > sprite[18].w)                            
       &&( mouseY < (sprite[18].z + sprite[18].box_height) )
       &&( mouseY > sprite[18].z)) 
       { 
            
           Set_Sprite(18, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
           
           if(current_act == 3 || current_act == 4)  
           {         
               sprintf( counter[5].word, "Underwear^Album");
               counter[5].length = 1;
           }
           else
           {         
               sprintf( counter[5].word, "Locked");
               counter[5].length = 0;
           }
           
                
           msg_left=true;   
           
           if(mouseleft == true)
           {
               if(current_act == 3 || current_act == 4)
               {         
                   card_page  = 3;
                   next_scene = true;                         
               }
               
               click_sfx = true;         
               mouseleft = false;
           }                         
       } 
       else
           Set_Sprite(18, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
 
       
    } // gallery_title_sequence == 1
    
    
}
 
void Set_Card(int index, int value) 
{ 
 
	if(index >= 0)
	{
	
    global_cards[index]+=value;       
        
    if(global_cards[index] > 10)  
        global_cards[index]=10;      
    
    if(index >= 12 && index < 24)
        index -= 12;  
    if(index >= 24 && index < 36)
        index -= 24;  
                                   
        if(index == 0)   
            Set_Sprite(6, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(index == 1)
            Set_Sprite(3, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(index == 2)
            Set_Sprite(9, 4, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(index == 3)
            Set_Sprite(10, 5, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
             
        if(index == 4)
            Set_Sprite(7, 6, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(index == 5)
            Set_Sprite(4, 7, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(index == 6) 
            Set_Sprite(11, 8, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(index == 7) 
            Set_Sprite(12, 9, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
             
        if(index == 8)
            Set_Sprite(8, 10, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(index == 9)
            Set_Sprite(5, 11, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(index == 10)
            Set_Sprite(13, 12, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        if(index == 11)
            Set_Sprite(14, 13, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);      
  
 	} // index >= 0
    
}
 
void Calculate_Gallery_Bullets()       
{                      
      
   int addition=0;  
 
   addition = 0;    

   if(gallery_clip < 5)
       sprite[18].alpha = 0.0f;
   else
       sprite[18].alpha = 1.0f;
       
   if(gallery_clip <= 0)                     
       sprite[17].alpha = 0.0f;  
   else
       sprite[17].alpha = 1.0f;          
 
   if(gallery_clip ==  8)     
       Set_Sprite(18, 0+addition, LOOP, ANIM_SPRITE, ANIM_WALKING); // Move Arrow 
   if(gallery_clip ==  7)
       Set_Sprite(18, 1+addition, LOOP, ANIM_SPRITE, ANIM_WALKING); // Move Arrow 
   if(gallery_clip ==  6)
       Set_Sprite(18, 2+addition, LOOP, ANIM_SPRITE, ANIM_WALKING); // Move Arrow 
   if(gallery_clip ==  5)
       Set_Sprite(18, 3+addition, LOOP, ANIM_SPRITE, ANIM_WALKING); // Move Arrow 

   if(gallery_clip ==  4)
       Set_Sprite(17, 0+addition, LOOP, ANIM_SPRITE, ANIM_WALKING); // Move Arrow 
   if(gallery_clip ==  3)
       Set_Sprite(17, 1+addition, LOOP, ANIM_SPRITE, ANIM_WALKING); // Move Arrow 
   if(gallery_clip ==  2)
       Set_Sprite(17, 2+addition, LOOP, ANIM_SPRITE, ANIM_WALKING); // Move Arrow 
   if(gallery_clip ==  1)
       Set_Sprite(17, 3+addition, LOOP, ANIM_SPRITE, ANIM_WALKING); // Move Arrow 
   
   if(gallery_clip >= 5)                           
   {
       Set_Sprite(17, 0+addition, LOOP, ANIM_SPRITE, ANIM_WALKING);
   }            
     
}
                   
void Calculate_Gallery_Lifebar()   
{      
                      
     float testX = 0.0f;              
 
     // Regeneration...     
     if(PLY_REGENERATE != 0)     
	 if(old_health < PLY_VITALITY) 
	 if((int)TimerGetTime() > reset_player_heal_timer)	
     if((int)TimerGetTime() > player_heal_timer)  
     {
          player_heal_timer = (int)TimerGetTime() + (4000 - PLY_REGENERATE*150);

	  	  if(player_heal_timer < (int)TimerGetTime() + MAX_REGEN_RATE) 
		      player_heal_timer = (int)TimerGetTime() + MAX_REGEN_RATE;

          old_health++;        
     }  
     
     if(PLY_VITALITY != 0)
         testX = gallery_health_width / (float)PLY_VITALITY;     
   
     sprite[21].width = (float)old_health * testX;
         
     if( old_health > 0) 
     {       
         if( PLY_VITALITY/old_health > 3)
            Set_Sprite(21, 15, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
         else
            Set_Sprite(21, 14, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
     }    
          
     if(old_health <= 0)
         sprite[21].alpha = 0.0f;               
     
     if(gallery_scene == 3)
     {
           
         if(boss_total_score != 0) 
             testX = boss_health_width / (float)boss_total_score;     
              
         sprite[29].width = (float)boss_gallery_health * testX;
                           
     }
     
     if(gallery_scene == 11) 
     {
           
         if(boss_total_score != 0) 
             testX = boss_health_width / (float)boss_total_score;     
              
         sprite[31].width = (float)boss_gallery_health * testX;
                           
     }
           
     if(gallery_scene == 7)  
     {
           
         if(boss_total_score != 0) 
             testX = boss_health_width / (float)boss_total_score;     
              
         sprite[32].width = (float)boss_gallery_health * testX;
                           
     }     
     
     
}

void Run_Medals(int f_rate)
{ 

    int medal_index=0;

	if(f_rate <= 0)
	    f_rate = 1; 
         
	if(medal_page == 3) 
	    medal_page = 2;
			       
    if(medal_page == 1)
        medal_index=0;
    
    if(medal_page == 2)
        medal_index=12;
    
    if(medal_page == 3)
        medal_index=24;
                         
    if(gallery_title_sequence == 0) 
    { 
		#if INCLDUE_360_CONTROLLER  == 1  
		if(CONTROLLER)   
		{ 
			     
			MAKE_BUTTON(ROW_MIDDLE-3, 15, BOX_SMALL);
			     
			MAKE_BUTTON(ROW_MIDDLE-2, 16, BOX_SMALL);

			MAKE_BUTTON(ROW_MIDDLE-1, 6, BOX_SMALL);
			MAKE_BUTTON(ROW_MIDDLE-1, 7, BOX_SMALL); 
			MAKE_BUTTON(ROW_MIDDLE-1, 8, BOX_SMALL);
			
			MAKE_BUTTON(ROW_MIDDLE, 3, BOX_SMALL);
			MAKE_BUTTON(ROW_MIDDLE, 4, BOX_SMALL);
			MAKE_BUTTON(ROW_MIDDLE, 5, BOX_SMALL);
			 
			MAKE_BUTTON(ROW_MIDDLE+1, 9, BOX_SMALL);
			MAKE_BUTTON(ROW_MIDDLE+1, 11, BOX_SMALL); 
			MAKE_BUTTON(ROW_MIDDLE+1, 13, BOX_SMALL);

			MAKE_BUTTON(ROW_MIDDLE+2, 10, BOX_SMALL);
			MAKE_BUTTON(ROW_MIDDLE+2, 12, BOX_SMALL); 
			MAKE_BUTTON(ROW_MIDDLE+2, 14, BOX_SMALL);

			MAKE_BUTTON(ROW_MIDDLE+3, 1, BOX_SMALL);
			 
			DX_ROW = ROW_MIDDLE-1;
			DX_CURRENT_TITLE_BUTTON[DX_ROW]=0;
			 
			sprintf( string, "scene/episode%i/scene%i.dx", episode, scene);
			LoadDXTemp( string ); 

		}	
		#endif

         if(current_act == 2)
         {
             sprite[16].id+=2; // Stunned   
         }
        
         if(current_act == 3 || current_act == 4)
         {
             sprite[16].id+=2; // Stunned 
         }
                  
        if( medal_page == 1) 
        {  

             if(global_medals[0] == MEDAL_BLANK) 
                Set_Sprite(6, sprite[6].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[1] == MEDAL_BLANK)
                Set_Sprite(3, sprite[3].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[2] == MEDAL_BLANK)
                Set_Sprite(9, sprite[9].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[3] == MEDAL_BLANK)
                Set_Sprite(10, sprite[10].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); 
                
            if(global_medals[4] == MEDAL_BLANK)
                Set_Sprite(7, sprite[7].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[5] == MEDAL_BLANK)
                Set_Sprite(4, sprite[4].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[6] == MEDAL_BLANK)   
                Set_Sprite(11, sprite[11].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[7] == MEDAL_BLANK)
                Set_Sprite(12, sprite[12].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); 
                
            if(global_medals[8] == MEDAL_BLANK)
                Set_Sprite(8, sprite[8].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[9] == MEDAL_BLANK)
                Set_Sprite(5, sprite[5].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[10] == MEDAL_BLANK)
                Set_Sprite(13, sprite[13].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[11] == MEDAL_BLANK)
                Set_Sprite(14, sprite[14].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); 
			 

            if(global_medals[0] != MEDAL_BLANK) 
                Set_Sprite(6, sprite[6].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[1] != MEDAL_BLANK)
                Set_Sprite(3, sprite[3].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[2] != MEDAL_BLANK)
                Set_Sprite(9, sprite[9].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[3] != MEDAL_BLANK)
                Set_Sprite(10, sprite[10].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); 
                
            if(global_medals[4] != MEDAL_BLANK)
                Set_Sprite(7, sprite[7].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[5] != MEDAL_BLANK)
                Set_Sprite(4, sprite[4].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[6] != MEDAL_BLANK)   
                Set_Sprite(11, sprite[11].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[7] != MEDAL_BLANK)
                Set_Sprite(12, sprite[12].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); 
                
            if(global_medals[8] != MEDAL_BLANK)
                Set_Sprite(8, sprite[8].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[9] != MEDAL_BLANK)
                Set_Sprite(5, sprite[5].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[10] != MEDAL_BLANK)
                Set_Sprite(13, sprite[13].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[11] != MEDAL_BLANK)
                Set_Sprite(14, sprite[14].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); 
                                                                                
        }                 
         
        if( medal_page == 2)
        { 
            
            if(global_medals[12] == MEDAL_BLANK) 
                Set_Sprite(6, sprite[6].base_anim+24, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[13] == MEDAL_BLANK)
                Set_Sprite(3, sprite[3].base_anim+24, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[14] == MEDAL_BLANK)
                Set_Sprite(9, sprite[9].base_anim+24, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[15] == MEDAL_BLANK)
                Set_Sprite(10, sprite[10].base_anim+24, LOOP, ANIM_SPRITE, ANIM_WALKING); 
                
            if(global_medals[16] == MEDAL_BLANK)
                Set_Sprite(7, sprite[7].base_anim+24, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[17] == MEDAL_BLANK)
                Set_Sprite(4, sprite[4].base_anim+24, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[18] == MEDAL_BLANK)   
                Set_Sprite(11, sprite[11].base_anim+24, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[19] == MEDAL_BLANK)
                Set_Sprite(12, sprite[12].base_anim+24, LOOP, ANIM_SPRITE, ANIM_WALKING); 
                
            if(global_medals[20] == MEDAL_BLANK)
                Set_Sprite(8, sprite[8].base_anim+24, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[21] == MEDAL_BLANK)
                Set_Sprite(5, sprite[5].base_anim+24, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[22] == MEDAL_BLANK)
                Set_Sprite(13, sprite[13].base_anim+24, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[23] == MEDAL_BLANK)
                Set_Sprite(14, sprite[14].base_anim+24, LOOP, ANIM_SPRITE, ANIM_WALKING); 

            if(global_medals[12] != MEDAL_BLANK) 
                Set_Sprite(6, sprite[6].base_anim+25, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[13] != MEDAL_BLANK)
                Set_Sprite(3, sprite[3].base_anim+25, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[14] != MEDAL_BLANK)
                Set_Sprite(9, sprite[9].base_anim+25, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[15] != MEDAL_BLANK)
                Set_Sprite(10, sprite[10].base_anim+25, LOOP, ANIM_SPRITE, ANIM_WALKING); 
                
            if(global_medals[16] != MEDAL_BLANK)
                Set_Sprite(7, sprite[7].base_anim+25, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[17] != MEDAL_BLANK)
                Set_Sprite(4, sprite[4].base_anim+25, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[18] != MEDAL_BLANK)   
                Set_Sprite(11, sprite[11].base_anim+25, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[19] != MEDAL_BLANK)
                Set_Sprite(12, sprite[12].base_anim+25, LOOP, ANIM_SPRITE, ANIM_WALKING); 
                
            if(global_medals[20] != MEDAL_BLANK)
                Set_Sprite(8, sprite[8].base_anim+25, LOOP, ANIM_SPRITE, ANIM_WALKING);  
            if(global_medals[21] != MEDAL_BLANK)
                Set_Sprite(5, sprite[5].base_anim+25, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[22] != MEDAL_BLANK)
                Set_Sprite(13, sprite[13].base_anim+25, LOOP, ANIM_SPRITE, ANIM_WALKING); 
            if(global_medals[23] != MEDAL_BLANK)
                Set_Sprite(14, sprite[14].base_anim+25, LOOP, ANIM_SPRITE, ANIM_WALKING); 
                                                                                  
        }            
        
        gallery_title_sequence++;                   
    }      
    
    if(gallery_title_sequence == 1)  
    { 
                      
       sprintf( counter[5].word, "");   
       sprintf( counter[0].word, "");   
       counter[0].alpha = 0.0f;
       
       // 7, 4, 11, 12
       // 8, 5, 13, 14
          
       for(int i = 3; i < 15; i++) 
       if(( mouseX < (sprite[i].w + sprite[i].box_width) )
       &&( mouseX > sprite[i].w)                            
       &&( mouseY < (sprite[i].z + sprite[i].box_height) )
       &&( mouseY > sprite[i].z))  
       { 
           counter[5].length = 2; 
            
           if(i == 6)   
           { 
              if(global_medals[medal_index] == MEDAL_BLANK)
              {  
                  if(medal_page == 1)                          
                      sprintf( counter[5].word, "-NO_BADGE-^Survive^Boot_Camp!");
                  if(medal_page == 2)
                      sprintf( counter[5].word, "-NO_BADGE-^Destroy^the enemy^Tanks!");
                  if(medal_page == 3)
                      sprintf( counter[5].word, "-NO_BADGE-^Kill_atleast^250^farmlands^scouts!");
                  counter[5].length = 4; 
              }
              if(global_medals[medal_index] != MEDAL_BLANK) 
              {  
				  if(medal_page == 1)                          
					sprintf( counter[5].word, "BOOT^BADGE");
                  if(medal_page == 2)
					sprintf( counter[5].word, "TANK^BADGE");

                  counter[5].length = 1; 

              }                    
           }     
           if(i == 3)    
           {
              if(global_medals[medal_index+1] == MEDAL_BLANK) 
              {   
                  if(medal_page == 1)                            
                      sprintf( counter[5].word, "-NO_BADGE-^Destroy^all_the^antennas!");
                  if(medal_page == 2)                             
                      sprintf( counter[5].word, "-NO_BADGE-^Take out^the enemy^division!");
                  if(medal_page == 3)                            
                      sprintf( counter[5].word, "-NO_BADGE-^Kill_atleast^50^farmlands^colonels!");
                      
                  counter[5].length = 4; 
              }
              if(global_medals[medal_index+1] != MEDAL_BLANK)
              {  
				  if(medal_page == 1)                          
					sprintf( counter[5].word, "SEAGULL^BADGE");
                  if(medal_page == 2)
					sprintf( counter[5].word, "CAPTAIN^BADGE");
                  counter[5].length = 1; 

              }                      
           }  
           if(i == 9)   
           { 
              if(global_medals[medal_index+2] == MEDAL_BLANK) 
              {   
                  if(medal_page == 1)                            
                      sprintf( counter[5].word, "-NO_BADGE-^Clear^all_the^bunkers!");
                  if(medal_page == 2)
                      sprintf( counter[5].word, "-NO_BADGE-^Find_Agent^Biggs!");
                  if(medal_page == 3)                  
                      sprintf( counter[5].word, "-NO_BADGE-^Kill_atleast^50^dogs!");
                  counter[5].length = 4; 
              } 
              if(global_medals[medal_index+2] != MEDAL_BLANK)
              {   
				  if(medal_page == 1)                          
					sprintf( counter[5].word, "RAT^BADGE");
                  if(medal_page == 2)
					sprintf( counter[5].word, "MAUSER^BADGE");
                  counter[5].length = 1; 

              }                   
           }  
           if(i == 10)     
           {
              if(global_medals[medal_index+3] == MEDAL_BLANK)   
              {    
                  if(medal_page == 1)                            
                      sprintf( counter[5].word, "-NO_BADGE-^Collect^the^Battleship^documents!");
                  if(medal_page == 2)
                      sprintf( counter[5].word, "-NO_BADGE-^Destroy_the^Black_Mole!");
                  if(medal_page == 3)                  
                      sprintf( counter[5].word, "-NO_BADGE-^Kill_atleast^1000^zombies!");
                  counter[5].length = 4;  
              }
              if(global_medals[medal_index+3] != MEDAL_BLANK)
              {  
				  if(medal_page == 1)                          
					sprintf( counter[5].word, "BIGGS^BADGE");
                  if(medal_page == 2)
					sprintf( counter[5].word, "MOLE^BADGE");
                  counter[5].length = 1; 

              }                
           }             
           if(i == 7)    
           {
              if(global_medals[medal_index+4] == MEDAL_BLANK) 
              {    
                  if(medal_page == 1)
                      sprintf( counter[5].word, "-NO_BADGE-^Destroy_the^battleship!");
                  if(medal_page == 2)
                      sprintf( counter[5].word, "-NO_BADGE-^Stop_the^Train!");
                  if(medal_page == 3)
                      sprintf( counter[5].word, "-NO_BADGE-^Contact^agent^Biggs!");                      
                   
                  counter[5].length = 4; 
              }
              if(global_medals[medal_index+4] != MEDAL_BLANK) 
              {  
				  if(medal_page == 1)                          
					sprintf( counter[5].word, "BATTLESHIP^BADGE");
                  if(medal_page == 2)
					sprintf( counter[5].word, "KEISER^BADGE");
                  counter[5].length = 1; 

              }                   
           }                          
           if(i == 4)   
           {
              if(global_medals[medal_index+5] == MEDAL_BLANK) 
              {  
                  if(medal_page == 1) 
                      sprintf( counter[5].word, "-NO_BADGE-^Rescue_the^Professor!");
                  if(medal_page == 2)
                      sprintf( counter[5].word, "-NO_BADGE-^Confront^the_Keiser!"); 
                  if(medal_page == 3)
                      sprintf( counter[5].word, "-NO_BADGE-^Destroy_the^enemies_air^defense!");                                          
                  counter[5].length = 4; 
              }
              if(global_medals[medal_index+5] != MEDAL_BLANK)
              {  
				  if(medal_page == 1)                          
					sprintf( counter[5].word, "PROFESSOR^BADGE");
                  if(medal_page == 2)
					sprintf( counter[5].word, "TRAIN^BADGE");
                  counter[5].length = 1; 

              }                
           }                       
           if(i == 11)    
           { 
              if(global_medals[medal_index+6] == MEDAL_BLANK)  
              {    
                  if(medal_page == 1)                             
                      sprintf( counter[5].word, "-NO_BADGE-^Destroy_the^Sea^Monkey!");
                  if(medal_page == 2)
                      sprintf( counter[5].word, "-NO_BADGE-^Stop_the^Professor!"); 
                  if(medal_page == 3)
                      sprintf( counter[5].word, "-NO_BADGE-^Destroy_the^enemy^missiles!");                                             
                  counter[5].length = 4; 
              }
              if(global_medals[medal_index+6] != MEDAL_BLANK) 
              {  
				  if(medal_page == 1)                          
					sprintf( counter[5].word, "SEAMONKEY^BADGE");
                  if(medal_page == 2)
					sprintf( counter[5].word, "ZOMBIE^BADGE");
                  counter[5].length = 1; 

              }                   
           }                        
           if(i == 12)    
           {
              if(global_medals[medal_index+7] == MEDAL_BLANK) 
              {   
                  if(medal_page == 1)                             
                      sprintf( counter[5].word, "-NO_BADGE-^Defeat_the^Admiral!");
                  if(medal_page == 2)
                      sprintf( counter[5].word, "-NO_BADGE-^Beat_the^game!");  
                  if(medal_page == 3)                             
                      sprintf( counter[5].word, "-NO_BADGE-^Defeat_the^Professor!");                                          
                  counter[5].length = 4; 
              }
              if(global_medals[medal_index+7] != MEDAL_BLANK)
              {  
				  if(medal_page == 1)                          
					sprintf( counter[5].word, "ADMIRAL^BADGE");
                  if(medal_page == 2)
					sprintf( counter[5].word, "COMPLETE^BADGE");
                  counter[5].length = 1; 

              }                  
           }                        
                        
           if(i == 8)           
           {
              if(global_medals[medal_index+8] == MEDAL_BLANK)
              {    
                  if(medal_page == 1)  
                      sprintf( counter[5].word, "-NO_BADGE-^Knife^atleast^fifty^enemies!");
                  if(medal_page == 2)
                      sprintf( counter[5].word, "-NO_BADGE-^Kill_all^the_crows^at_the^farmlands!");
                  if(medal_page == 3)
                      sprintf( counter[5].word, "-NO_BADGE-^Kill_all^the_cows^at_the^farmlands!");
                  counter[5].length = 4; 
              } 
              if(global_medals[medal_index+8] != MEDAL_BLANK)
              {  
				  if(medal_page == 1)                          
					sprintf( counter[5].word, "KNIFE^BADGE");
                  if(medal_page == 2)
					sprintf( counter[5].word, "CROW^BADGE");
                  counter[5].length = 1; 

              }                 
           }                        
           if(i == 5)   
           {
              if(global_medals[medal_index+9] == MEDAL_BLANK)  
              {  
                  if(medal_page == 1)                            
                      sprintf( counter[5].word, "-NO_BADGE-^Clear^the_hidden^bunker!");
                  if(medal_page == 2)                            
                      sprintf( counter[5].word, "-NO_BADGE-^Clear^the_cellar^at_the^village!");
                  if(medal_page == 3)                            
                      sprintf( counter[5].word, "-NO_BADGE-^Smash_all^the_gates^at_the^farmlands!");
                      
                  counter[5].length = 4; 
              }
              if(global_medals[medal_index+9] != MEDAL_BLANK)
              {  
				  if(medal_page == 1)                          
					sprintf( counter[5].word, "SAILOR^BADGE");
                  if(medal_page == 2)
					sprintf( counter[5].word, "HELMET^BADGE");
                  counter[5].length = 1; 

              }                   
           }                     
           if(i == 13)       
           {
              if(global_medals[medal_index+10] == MEDAL_BLANK)   
              {   
                  if(medal_page == 1)  
                      sprintf( counter[5].word, "-NO_BADGE-^Light_all^the_torches^on_pebble^beach!");
                  if(medal_page == 2) 
                      sprintf( counter[5].word, "-NO_BADGE-^Win^2500G^overall_at^the_casino!");
                  if(medal_page == 3) 
                      sprintf( counter[5].word, "-NO_BADGE-^Shoot_all^the_crows^at_the^farmlands!");
                  
                  counter[5].length = 4; 
              }
              if(global_medals[medal_index+10] != MEDAL_BLANK)
              {  
				  if(medal_page == 1)                          
					sprintf( counter[5].word, "LIGHTER^BADGE");
                  if(medal_page == 2)
					sprintf( counter[5].word, "CASINO^BADGE");
                  counter[5].length = 1; 

              }                
           }                        
           if(i == 14)   
           {
              if(global_medals[medal_index+11] == MEDAL_BLANK) 
              {   
                  if(medal_page == 1)                              
                      sprintf( counter[5].word, "-NO_BADGE-^Smash_all^the_bottles^at_pebble^beach!");
                  if(medal_page == 2)                             
                      sprintf( counter[5].word, "-NO_BADGE-^Collect^all_the^tent^furniture!");
                  if(medal_page == 3)                             
                      sprintf( counter[5].word, "-NO_BADGE-^Collect^every^cigarette^card!");
                       
                  counter[5].length = 4;   
              }
              if(global_medals[medal_index+11] != MEDAL_BLANK)
              {  
				  if(medal_page == 1)                          
					sprintf( counter[5].word, "BOTTLE^BADGE");
                  if(medal_page == 2)
					sprintf( counter[5].word, "TEDDYBEAR^BADGE");
                  counter[5].length = 1; 

              }
           }                       
     
                       
           msg_left=true;                                                                           

           if(sprite[i].selected == false)        
           {
               radio_sfx = true;  
               sprite[i].selected = true;
           }    
                  
           Message_Limits();                     
           
       }   
       else 
           sprite[i].selected = false;   
                     
       // Exit Button - EXIT 
       if(sprite[1].grab_switch == true)                   
       if( (( mouseX < (sprite[1].w + sprite[1].box_width) )
       &&( mouseX > sprite[1].w)                            
       &&( mouseY < (sprite[1].z + sprite[1].box_height) )
       &&( mouseY > sprite[1].z)) || DX_BACK == true)
       { 
            
           Set_Sprite(1, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
        
		   if(!CONTROLLER)
		   {
			   if(current_act != 4)
				   sprintf( counter[5].word, "Return^to_Tent");
			   else
				   sprintf( counter[5].word, "Return^to_House");   
		   }
               
           counter[5].length = 1;     
           msg_left=false;   
               
           if( button_snd == false)
           {
               radio_sfx = true;
               button_snd = true;
           }                              
           if(mouseleft == true || DX_SHOOT == true || DX_BACK == true)  
           {  

			   DX_SHOOT = false;
			   DX_BACK = false;

               if(current_act != 4)
               {
			       episode = 1;    
                   scene   = 25;
			   } 
			   else
               {
			       episode = 1;    
                   scene   = 170;
			   } 
                
			   
               switch_n_sfx = true; 
               next_scene = true;
               mouseleft = false; 
               sprite[1].grab_switch = false; 
           }   
                     
       } 
       else
       {
           Set_Sprite(1, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
           button_snd = false;
       }
                
       // Page 1 
       if(sprite[15].grab_switch == true)                 
       if( ( ( mouseX < (sprite[15].w + sprite[15].box_width) )
       &&( mouseX > sprite[15].w)                            
       &&( mouseY < (sprite[15].z + sprite[15].box_height) )
       &&( mouseY > sprite[15].z)) || DX_LEFTSHLDR == true)
       { 
            
           Set_Sprite(15, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                  
           sprintf( counter[5].word, "Layer^One");
   
           counter[5].length = 1;     
           msg_left=true;   
               
           if( button1_snd == false)
           {
               radio_sfx = true;
               button1_snd = true;
           }                
           if(mouseleft == true || DX_SHOOT == true || DX_LEFTSHLDR == true)
           {
               DX_SHOOT=false;  
			   DX_LEFTSHLDR=false;
               medal_page = 1;   
               next_scene = true;
                     
               click_sfx = true;         
               mouseleft = false;
               
           }                       
       } 
       else
       {
           Set_Sprite(15, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);  
           button1_snd = false;
       } 
                
       // Page 2
       if(sprite[16].grab_switch == true)                  
       if(( ( mouseX < (sprite[16].w + sprite[16].box_width) )
       &&( mouseX > sprite[16].w)                            
       &&( mouseY < (sprite[16].z + sprite[16].box_height) )
       &&( mouseY > sprite[16].z)) || DX_RIGHTSHLDR == true)
       { 
            
           Set_Sprite(16, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
           
           if(current_act == 1)      
           {                    
               sprintf( counter[5].word, "Locked");
               counter[5].length = 0;
           }
           else
           {
               sprintf( counter[5].word, "Layer^Two");
               counter[5].length = 1;                 
           } 
           
           msg_left=true;   
               
           if( button2_snd == false)
           {
               radio_sfx = true;
               button2_snd = true;
           }              
           if(mouseleft == true || DX_SHOOT == true || DX_RIGHTSHLDR == true)
           {
               DX_SHOOT=false;   
			   DX_RIGHTSHLDR=false;
               if(current_act > 1) 
               {   
                   medal_page = 2;
                   next_scene = true;
               }     
                   
               click_sfx = true;         
               mouseleft = false;
               
           }             
                      
       } 
       else 
       {
           Set_Sprite(16, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
           button2_snd = false;
       }
                 
       // Page 3
       if(sprite[17].grab_switch == true)                  
       if(( mouseX < (sprite[17].w + sprite[17].box_width) )
       &&( mouseX > sprite[17].w)                            
       &&( mouseY < (sprite[17].z + sprite[17].box_height) )
       &&( mouseY > sprite[17].z)) 
       { 
            
           Set_Sprite(17, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
           
           if(current_act != 3 && current_act != 4)      
           {                    
               sprintf( counter[5].word, "Locked");
               counter[5].length = 0;
           }
           else
           {
               sprintf( counter[5].word, "Layer^Three");
               counter[5].length = 1;                 
           } 
           
           msg_left=true;   
               
           if( button3_snd == false)
           {
               radio_sfx = true;
               button3_snd = true;
           }               
           if(mouseleft == true)
           {
                        
               if(current_act == 3 || current_act == 4)  
               {    
                   medal_page = 3;
                   next_scene = true;
               }     
                   
               click_sfx = true;         
               mouseleft = false; 
               
           }                        
       } 
       else
       {
           Set_Sprite(17, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
           button3_snd = false;                                        
       }
           
                  
    } // gallery_title_sequence == 1
    
    
}

void Hud_Face_Unit_Gallery()                                                                        
{             
        
    int hud_id=0;       
    int addition=0;  
      
    hud_id = 20;   
             
    if(PLY_VITALITY != 0)   
    if( old_health <= 30)
        addition = 6;
              
    if(PLY_VITALITY != 0)   
    if( old_health <= 20)
        addition = 6;
     
    if(ply_id != -1) 
    if( old_health <= 0)       
        addition = 6;   
          
    if(gallery_reloading == false)               
    if(sprite[hud_id].status == IDLE)  
	if(sprite[hud_id].anim != 1+addition)   
    {  
        Set_Sprite(hud_id, 1+addition, PLAY, ANIM_SPRITE, ANIM_WALKING);   
    }                                            
         
    if(sprite[hud_id].status == STUNNED)     
    {
                      
            Set_Sprite(hud_id, 2+addition, ONCE, ANIM_SPRITE, ANIM_WALKING);   
  
    }          
    
    if(sprite[hud_id].status == FALLING)     
    {
                        
            Set_Sprite(hud_id, 3+addition, ONCE, ANIM_SPRITE, ANIM_WALKING);   

    }            
                                             
    if(sprite[hud_id].status == OPEN_FIRE)    
    {  
                         
            Set_Sprite(hud_id, 3+addition, ONCE, ANIM_SPRITE, ANIM_WALKING);   

    }            
                                      
    if(sprite[hud_id].status == OPEN_CUT) 
    {  
                       
            Set_Sprite(hud_id, 3+addition, ONCE, ANIM_SPRITE, ANIM_WALKING);   
  
    }        
                                         
    if(sprite[hud_id].status == DIEING)                                     
    {  
                         
            Set_Sprite(hud_id, 5+addition, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING);   
 
    }          
      
    if(sprite[hud_id].status == MERCY || sprite[hud_id].status == MERCY1)                       
    {  
                                   
            Set_Sprite(hud_id, 5+addition, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING);   
 
    }      
       
    if(gallery_reloading == true)     
    {  
                          
            Set_Sprite(hud_id, 4+addition, LOOP,  ANIM_SPRITE, ANIM_NOT_WALKING);   
 
    }      
                                                    
                                                 
}   


