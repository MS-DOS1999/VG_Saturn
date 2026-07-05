
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN 

#include <windows.h> 
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>			// Header File For Standard Input/Output
#include <gl\gl.h> 
#include "globals.h"    

extern void Generate_Object_Collision(int loop, bool col_test);
extern bool New_FX(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int i_value, int i_type, int state, int linked_sprite, int tex_id, int i_value1, int i_value2, int i_value3);
extern void Display_Message(int index, int message);
extern void Remove_Item(int item_type, int item_value, int item_value1);
extern bool Calculate_Item(int item_value, int item_type, int the_item, int item_value1, int item_value2, int item_value3);
extern void Bit_Shift( int the_value1, int bit_to_shift, int bit_value);
extern int  Get_Bit_Shift( int the_value1, int bit_to_shift);
extern int  Convert_Angle_To_Dir(float my_angle);
extern bool Has_This_Item(int type, int value);
extern void Move_Vehicle(int loop, float x_pos, float y_pos, int f_rate);
extern void Remove_Temps(int type);
extern void Reset_Shop_Specials();
extern void Special_Attack(int type);     
extern void Reposition_Unit(int loop);
extern int Convert_Dir_To_Angle(int loop, int direction);

void Boss_Shoot( int shooter, float x1, float y1, float angle, int f_rate);
void Check_Boss_Explode(int index);
void Check_Splat(int index);

// Scripts for Levels.. 
bool reverse=false;
int scripts_bullet_timer=0;
int bullet_count=0; 
bool silo_fired=false;
bool silo1_fired=false;
bool boss_front=true;
float boss_speed=0.0f;
float boss_accel=0.0f;

float boss_angle = 0.0;

int  boss_sequence = 0;
int  boss_sequence_timer=0;

int machinegun_timer=0;

int machinegun_index = 0;

int mauser_index = -1;

int  buddy_point=0;
                     
void Run_Boss(int f_rate)
{

       float cam_x =0.0, cam_y =0.0;
       float deltax =0.0,deltay =0.0;
       float testX=0.0, testY=0.0;
       float temp_speed = 0.0;
       float temp_speed1= 0.0;
       float angle = 0.0;     
       float x_pos=0.0, y_pos=0.0;
       float midX=0.0, midY=0.0;
       float dis_to_point=0.0;
       float dis_to_point1=0.0;
       float diff_x=0.0, diff_y=0.0;
       float total_distance=0.0;
       float distance=0.0f;
       float mid_x=0.0f, mid_y=0.0f;
       
       int display_players_cards = 0;
       int display_dealers_cards = 0;
       int Card_Time = 1250;
       int Card_Time1 = 3000;
       int quit_id = 0; 
       int deal_id = 0;
       int rnd=0; 
       int index=0;
       bool pass_on = false;
       int anim_timer = 0;
       int secrets_found=0;
       int medals_found=0;
       int cards_found=0;
       float complete_rate=0;

	if(f_rate <= 0)
	    f_rate = 1;  
       
   // Title Screen Stuff... 
   if(quit_active == false)
   if(game_mode == WALK && !mode)
   if(next_scene == false)       
   if(Level == LVL_TANK_BOSS)    
   {  
       
             
       if(title_sequence == 0) 
       {  
           boss_sequence = 0;
           boss_sequence_timer = (int)TimerGetTime() + 5000;
           
           bullet_count=0;
           
           scripts_bullet_timer = 0;  
           
           machinegun_index = 0;
           machinegun_timer = (int)TimerGetTime() + 20000; 
                         
           mid_x = points[1].x; 
           mid_y = points[1].y; 
           
           diff_x = points[2].x;  
           diff_y = points[2].y; 
                                    
           boss_angle = atan2(diff_y - mid_y,diff_x - mid_x);
           
           Generate_Object_Collision(4, REMOVE_COL);
           Generate_Object_Collision(5, REMOVE_COL);
           Generate_Object_Collision(40, REMOVE_COL);
           Generate_Object_Collision(41, REMOVE_COL); 
           Generate_Object_Collision(8, REMOVE_COL);
                
           buddy_point=3;  
           
           // Turn off buddy...  
           if(p1_buddy != -1) 
           {
               sprite[p1_buddy].grab_switch = false;
               sprite[p1_buddy].sector_action = AI_NONE; 
               Generate_Object_Collision(p1_buddy, REMOVE_COL);
               sprite[p1_buddy].mouseover = true; 
               sprite[p1_buddy].turn_off = true;
			   sprite[p1_buddy].score = BUDDY_VITALITY; 
           }
           else
           {
               sprite[54].alpha = 0.0;    
           }
           
           sprite[10].alpha = 0.0; 
           sprite[13].alpha = 0.0;
                                  
           sprite[6].grab_switch = false;
           sprite[7].grab_switch = false;
            
           mauser_index = -1;
           
           boss_success = false;
           
           tank_track_sfx = true;
           
           title_sequence++; 
       }         
              
       if(title_sequence == 1)
       {   
                          
           deltax = cos(boss_angle); // Was 1.2    
           deltay = sin(boss_angle); // Was 1.2 
           
           // Boss movement code   
           boss_speed = 0.00020f;    
           
           if( sprite[4].score <= 0)
               boss_speed -= 0.00003f;
           if( sprite[5].score <= 0) 
               boss_speed -= 0.00003f;
           if( sprite[40].score <= 0)   
               boss_speed -= 0.00003f;
           if( sprite[41].score <= 0)
               boss_speed -= 0.00003f;
           
           if( boss_speed < 0.00014f) 
               boss_speed = 0.00014f;
                                                        
           deltax *= boss_speed; 
           deltay *= boss_speed;
           
           deltax *= (float)f_rate;
           deltay *= (float)f_rate;
           
           sprite[4].x -= deltax;
           sprite[4].w -= deltax;
           sprite[4].y -= deltay;
           sprite[4].z -= deltay;
           
           sprite[5].x -= deltax;
           sprite[5].w -= deltax;
           sprite[5].y -= deltay;
           sprite[5].z -= deltay;           
            
           sprite[40].x -= deltax; 
           sprite[40].w -= deltax;
           sprite[40].y -= deltay;
           sprite[40].z -= deltay;   
                      
           sprite[41].x -= deltax;
           sprite[41].w -= deltax;
           sprite[41].y -= deltay;
           sprite[41].z -= deltay;                        
                       
           sprite[8].x -= deltax;
           sprite[8].w -= deltax;   
           sprite[8].y -= deltay;
           sprite[8].z -= deltay;            
                       
           sprite[54].x -= deltax;
           sprite[54].w -= deltax;   
           sprite[54].y -= deltay;
           sprite[54].z -= deltay; 
           
           // Machinegun pieces..
                                  
           sprite[6].x -= deltax;
           sprite[6].w -= deltax;   
           sprite[6].y -= deltay;
           sprite[6].z -= deltay;  
                                  
           sprite[7].x -= deltax;
           sprite[7].w -= deltax;    
           sprite[7].y -= deltay;
           sprite[7].z -= deltay;            
                                  
           sprite[13].x -= deltax;
           sprite[13].w -= deltax;   
           sprite[13].y -= deltay;
           sprite[13].z -= deltay;  
                                  
           sprite[10].x -= deltax;
           sprite[10].w -= deltax;   
           sprite[10].y -= deltay;
           sprite[10].z -= deltay;                        
           
            
                      
           Check_Boss_Explode(4); 
           Check_Boss_Explode(5); 
           Check_Boss_Explode(40); 
           Check_Boss_Explode(41); 
           Check_Boss_Explode(8);  
           Check_Boss_Explode(6);
           Check_Boss_Explode(7);
             
           Check_Splat(4); 
           Check_Splat(5); 
           Check_Splat(40);  
           Check_Splat(41);  
           Check_Splat(8);  
           
           if(sprite[8].grab_switch == true) 
           if(sprite[8].score != 0)
           if(sprite[8].priority != 3)         
           if(sprite[8].score < (BIG_BOSS_HEALTH/2) )
           {
                sprite[8].base_anim = 4;  
                
                if(boss_sequence == 0 && sprite[8].anim != sprite[8].base_anim)
                    Set_Sprite(8, sprite[8].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING);
           }
                      
           // Shoot Guns...  
           if((int)TimerGetTime() > machinegun_timer)        
           {      
                 
               if(machinegun_index == 2)
               if((int)TimerGetTime() > scripts_bullet_timer)
               { 
                   
                 if(sprite[6].score > 0)  
                 {
                     mid_x = sprite[6].w+sprite[6].box_width/2; 
                     mid_y = sprite[6].z+sprite[6].box_height/2; 
                     
                     Boss_Shoot(6, mid_x, mid_y, -2.6f, f_rate);
                     
                     Set_Sprite(6, 5, LOOP, ANIM_SPRITE, ANIM_WALKING);
                     sprite[10].alpha = 1.0f; 
                 }
                 
                 if(sprite[7].score > 0)  
                 {
                     mid_x = sprite[7].w+sprite[7].box_width/2; 
                     mid_y = sprite[7].z+sprite[7].box_height/2; 
                     
                     Boss_Shoot(7, mid_x, mid_y, -2.6f, f_rate);
                                  
                     Set_Sprite(7, 5, LOOP, ANIM_SPRITE, ANIM_WALKING);                
                     sprite[13].alpha = 1.0f;                  
                 }
                              
                 if(sprite[6].score > 0 || sprite[7].score > 0)  
                     mount_sfx = true; 
                   
                 scripts_bullet_timer = (int)TimerGetTime() + 100;
                 
                 bullet_count++;   
                 
               } 
                    
               if((int)TimerGetTime() > machinegun_timer)
               if(machinegun_index == 2)   
               if(bullet_count >= 50 || (sprite[6].score <= 0 && sprite[7].score <= 0) )
               {   
                           
                   machinegun_timer = (int)TimerGetTime() + 2000;   
                   machinegun_index = 1; 
                    
                   bullet_count=0;
                   
                   if(sprite[6].score > 0)
                       Set_Sprite(6, 4, LOOP, ANIM_SPRITE, ANIM_WALKING);
                   if(sprite[7].score > 0)
                       Set_Sprite(7, 4, LOOP, ANIM_SPRITE, ANIM_WALKING); 
                        
                   sprite[10].alpha = 0.0f; 
                   sprite[13].alpha = 0.0f;
                         
               } 
               
               if((int)TimerGetTime() > machinegun_timer) 
               if(machinegun_index == 1)
               { 
                   machinegun_timer = (int)TimerGetTime() + 1000;                
                   machinegun_index++; 
                    
                   if(sprite[6].score > 0 || sprite[7].score > 0)
                       evil_laugh_sfx = true;
                       
               }     
               
               if((int)TimerGetTime() > machinegun_timer) 
               if(machinegun_index == 0)
               {                
                   if(sprite[6].score > 0)
                       Set_Sprite(6, 4, PLAY, ANIM_SPRITE, ANIM_WALKING);
                   if(sprite[7].score > 0)
                       Set_Sprite(7, 4, PLAY, ANIM_SPRITE, ANIM_WALKING);                

                   if(sprite[6].score > 0 || sprite[7].score > 0)
                       hatch_sfx = true;  
                       
                   sprite[6].grab_switch = false;
                   sprite[7].grab_switch = false; 
                      
                   machinegun_timer = (int)TimerGetTime() + 1000;               
                   machinegun_index++;                         
                                          
               }        
                                                
                
           }  
       
           if(ply_id != -1)
           if(boss_sequence == 0) 
           if(boss_success == false)
           if((int)TimerGetTime() > boss_sequence_timer)
           if(sprite[8].score > 0) 
           {  
                               
               Set_Sprite(8, sprite[8].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING);           
               splash_sfx = true;
               
               silo_fired=true; 
               
               mid_x = sprite[ply_id].x+sprite[ply_id].width/2;
               mid_y = sprite[ply_id].y+sprite[ply_id].height/2; 
                                         
               New_FX(mid_x, mid_y, sprite[ply_id].w, sprite[ply_id].z, 11, LOOP, sprite[ply_id].width, sprite[ply_id].height, sprite[ply_id].box_width, sprite[ply_id].box_height, 4, GFX, 0.01f, 0, 0, FX_FALLING_BOMB, ply_id, 2, 0, 0, -1);      
               
               whistle_sfx = true;
                
               boss_sequence_timer = (int)TimerGetTime() + 250;
               boss_sequence++;
               
           }     
           
           if(ply_id != -1)
           if(boss_sequence == 1)  
           if((int)TimerGetTime() > boss_sequence_timer)
           if(sprite[8].score > 0) 
           {  
                              
               Set_Sprite(8, sprite[8].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING);           
               
               boss_sequence_timer = (int)TimerGetTime() + 6000;
               
               if( sprite[8].score < (BIG_BOSS_HEALTH / 2) )
                   boss_sequence_timer -= 1500;
                   
               if( sprite[8].score < (BIG_BOSS_HEALTH / 3) )
                   boss_sequence_timer -= 1500;
        
               boss_sequence=0;
                
           } 
           
          mid_x = points[1].x;   
          mid_y = points[1].y;  
           
          x_pos = sprite[8].w+sprite[8].box_width/2; 
          y_pos = sprite[8].z+sprite[8].box_height/2;             
         
          dis_to_point = Node_Distance1(mid_x, mid_y, x_pos, y_pos);
          
          if(ply_id != -1) 
          if(boss_success == false)  
          if(dis_to_point <= 0.25f)   
          { 
               sprite[ply_id].status = FLATTENED; 
               sprite[ply_id].update = true;
               sprite[ply_id].anim_state = WAIT;
               sprite[ply_id].all_timer = (int)TimerGetTime() + 2000; 

               drown_sfx = true;  

               boss_success = true;  

			   lock_player = true;
          } 
     
      }     
              
       if((int)TimerGetTime() > title_timer) 
       if(title_sequence == 2)
       {   
             
           mid_x = sprite[8].x+sprite[8].width/2; 
           mid_y = sprite[8].y+sprite[8].height/2;  
                              
           mauser_index = New_Sprite(mid_x, mid_y, mid_x, mid_y, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_SHOTGUN, p_client1, 33, -1, -1, SPAWN_MAUSER, -1);
           
           New_Sprite(mid_x+0.1f, mid_y, mid_x+0.1f, mid_y, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_CHIEF, p_client1, 28, -1, -1, SPAWN_HUNT, -1);
           
           if(mauser_index != -1)
               Display_Message(mauser_index, MSG_CHARGE_TANK);
           
           if(p1_buddy != -1)
           {
               sprite[p1_buddy].sector_action = AI_BUDDY;
               sprite[p1_buddy].grab_switch = true;
               sprite[p1_buddy].mouseover = false; 
               sprite[p1_buddy].turn_off = false; 
               sprite[p1_buddy].alpha = 1.0f; 
               
               sprite[p1_buddy].x = sprite[41].x; 
               sprite[p1_buddy].y = sprite[41].y;
               
               Reposition_Unit(p1_buddy); 
             
           }
           
           title_sequence++;
           
       }   
        
       if(title_sequence == 3)
       {
                         
           if(mauser_index != -1)
           {
               
               if(ply_id != -1)
               if(sprite[mauser_index].score <= 0) 
               {
			   								 
                   sprite[ply_id].status = LEVELING;                         
                   lock_player = true; 
                   sprite[ply_id].update = true;      
                   sprite[ply_id].anim_state = WAIT;
                   sprite[ply_id].moving = false;
                   sprite[ply_id].all_timer = (int)TimerGetTime() + 2000;  
                   
                   title_sequence++;
                                                                
               }
                
           }                       
                                         
       }
            
   }      
        
   // Title Screen Stuff...
   if(quit_active == false)
   if(game_mode == WALK && !mode)
   if(next_scene == false)       
   if(Level == LVL_SUB_PEN)    
   {   
       
       if(title_sequence == 0)
       {


		 // Remove collision...
		 Generate_Object_Collision(28, REMOVE_COL);
		 Generate_Object_Collision(30, REMOVE_COL);
		 Generate_Object_Collision(36, REMOVE_COL);
		 Generate_Object_Collision(31, REMOVE_COL); 
		 Generate_Object_Collision(33, REMOVE_COL);
		 Generate_Object_Collision(32, REMOVE_COL); 			 
		 Generate_Object_Collision(27, REMOVE_COL);
		 Generate_Object_Collision(29, REMOVE_COL); 

         sprite[33].alpha = 0.0f;
         sprite[33].grab_switch = false; 
         
         // Front door..
         sprite[36].alpha = 0.0f; 
         sprite[36].grab_switch = false;
         
         // Submarine body...
         sprite[31].grab_switch = false;
         
         // Tracers...
         sprite[37].alpha = 0.0f;  
         sprite[38].alpha = 0.0f; 
         sprite[39].alpha = 0.0f;  
                    
         bullet_count = 0;
         
         boss_speed = 0.0f;
         
         boss_accel = 0.0f;
         
         boss_front = true;
         
         reverse=true;
         
         // Tracers...
         sprite[34].alpha = 0.0f;
         sprite[35].alpha = 0.0f;
           
         title_timer = (int)TimerGetTime() + 2000;
           
         title_sequence++;         
         
       }       
       
       if((int)TimerGetTime() > title_timer)                         
       if(title_sequence == 1)    
       {
           if(sprite[29].score > 0)
               Set_Sprite(29, 0, PLAY, ANIM_SPRITE, ANIM_WALKING);
           if(sprite[30].score > 0)
               Set_Sprite(30, 0, PLAY, ANIM_SPRITE, ANIM_WALKING); 
           
           title_timer = (int)TimerGetTime() + 1000;
                     
           if(sprite[29].score <= 0 && sprite[30].score <= 0)
              title_timer = 0; 
                         
           title_sequence++; 
       }  
        
        
       // Ready Guns...  
       if((int)TimerGetTime() > title_timer)        
       if(title_sequence == 2)    
       {       

		   sprite[29].spotted = true;
		   sprite[30].spotted = true; 
		   sprite[27].spotted = true;
		   sprite[28].spotted = true;
	
           if(sprite[29].score > 0)
               Set_Sprite(29, 4, PLAY, ANIM_SPRITE, ANIM_WALKING);
           if(sprite[30].score > 0)
               Set_Sprite(30, 4, PLAY, ANIM_SPRITE, ANIM_WALKING);                
           
           title_timer = (int)TimerGetTime() + 1000;
           
           if(sprite[29].score > 0 || sprite[30].score > 0)
               hatch_sfx = true;                       
                     
           if(sprite[29].score <= 0 && sprite[30].score <= 0)
              title_timer = 0; 
              
           title_sequence++;         
       }  
       
       // Shoot Guns...  
       if((int)TimerGetTime() > title_timer)        
       if(title_sequence == 3)    
       {      
   
           if((int)TimerGetTime() > scripts_bullet_timer)
           {            
                                
             if(sprite[29].score > 0) 
             {
                 mid_x = sprite[29].w+sprite[29].box_width/2; 
                 mid_y = sprite[29].z+sprite[29].box_height/2; 
                 
                 Boss_Shoot(29, mid_x, mid_y, -2.6f, f_rate);
                 
                 Set_Sprite(29, 5, LOOP, ANIM_SPRITE, ANIM_WALKING);
                 sprite[34].alpha = 1.0f;
             }
             
             if(sprite[30].score > 0)  
             {
                 mid_x = sprite[30].w+sprite[30].box_width/2; 
                 mid_y = sprite[30].z+sprite[30].box_height/2; 
                 
                 Boss_Shoot(30, mid_x, mid_y, -2.6f, f_rate);
                              
                 Set_Sprite(30, 5, LOOP, ANIM_SPRITE, ANIM_WALKING);                
                 sprite[35].alpha = 1.0f;                  
             }
                          
             if(sprite[29].score > 0 || sprite[30].score > 0)  
                 mount_sfx = true; 
               
             scripts_bullet_timer = (int)TimerGetTime() + 100;
             
             bullet_count++;  
             
           }     
              
           if(bullet_count >= 50 || (sprite[29].score <= 0 && sprite[30].score <= 0) )
           {           
               title_sequence++;         
           } 
            
       }  
       
       // Withdraw Guns...
       if(title_sequence == 4)    
       {   
           // Turn off tracers...
           sprite[34].alpha = 0.0f;
           sprite[35].alpha = 0.0f;   
                  
           if(sprite[29].score > 0)
             Set_Sprite(29, 6, PLAY, ANIM_SPRITE, ANIM_WALKING);

           if(sprite[30].score > 0)
           {
             Set_Sprite(30, 6, PLAY, ANIM_SPRITE, ANIM_WALKING);  
           }
           
           if(sprite[29].score > 0 || sprite[30].score > 0)
               hatch_sfx = true;  
               
          bullet_count = 0;              
          
          title_timer = (int)TimerGetTime() + 1000;
          
          if(sprite[29].score <= 0 && sprite[30].score <= 0)
              title_timer = 0;
              
          title_sequence++;         
          
       }  
       
       // Fire First Silo...
       if((int)TimerGetTime() > title_timer)       
       if(title_sequence == 5)    
       {
	
           if(sprite[29].score > 0)
               Set_Sprite(29, 0, PLAY, ANIM_SPRITE, ANIM_WALKING);
               
           if(sprite[30].score > 0)
               Set_Sprite(30, 0, PLAY, ANIM_SPRITE, ANIM_WALKING); 
                      
           if(sprite[27].score > 0)
           {
               Set_Sprite(27, 4, PLAY, ANIM_SPRITE, ANIM_WALKING);           
               splash_sfx = true;
               
               silo_fired=true;
           } 
           
           title_timer = (int)TimerGetTime() + 150;
           title_sequence++; 
       }      
           
       // Close First Silo...
       if((int)TimerGetTime() > title_timer)       
       if(title_sequence == 6)    
       {

           if(sprite[27].score > 0)
               Set_Sprite(27, 0, LOOP, ANIM_SPRITE, ANIM_WALKING); 

           title_timer = (int)TimerGetTime() + 1000;
           title_sequence++; 
       }        
               
       // Fire Second Silo...
       if((int)TimerGetTime() > title_timer)        
       if(title_sequence == 7)    
       {
	
           if(sprite[28].score > 0)
           {
               Set_Sprite(28, 4, PLAY, ANIM_SPRITE, ANIM_WALKING);                  
               splash_sfx = true;
               
               silo1_fired=true;               
           }
           
           title_timer = (int)TimerGetTime() + 150;
           title_sequence++; 
       }             
           
       // Close Second Silo...
       if((int)TimerGetTime() > title_timer)       
       if(title_sequence == 8)    
       {

           if(sprite[28].score > 0)
               Set_Sprite(28, 0, LOOP, ANIM_SPRITE, ANIM_WALKING); 
       
           title_timer = (int)TimerGetTime() + 1000;
           title_sequence++; 
       }      
           
       // Drop first bomb...
       if((int)TimerGetTime() > title_timer)       
       if(title_sequence == 9)    
       { 
           
           if(silo_fired == true && ply_id != -1)
           { 
               
               mid_x = sprite[ply_id].x+sprite[ply_id].width/2;
               mid_y = sprite[ply_id].y+sprite[ply_id].height/2; 
                                        
               New_FX(mid_x, mid_y,  sprite[ply_id].w, sprite[ply_id].z, 11, LOOP, sprite[ply_id].width, sprite[ply_id].height, sprite[ply_id].box_width, sprite[ply_id].box_height, 4, GFX, 0.01f, 0, 0, FX_FALLING_BOMB, ply_id, 2, 0, 0, -1);      
               
               whistle_sfx = true;
               silo_fired=false;
           } 
           
           title_timer = (int)TimerGetTime() + 2000;
           title_sequence++; 
       }        
           
       // Drop second bomb...
       if((int)TimerGetTime() > title_timer)       
       if(title_sequence == 10)     
       {     
           
           if(silo1_fired == true && ply_id != -1) 
           {
                
               mid_x = sprite[ply_id].x+sprite[ply_id].width/2;
               mid_y = sprite[ply_id].y+sprite[ply_id].height/2; 
                                         
               New_FX(mid_x, mid_y, sprite[ply_id].w, sprite[ply_id].z, 11, LOOP, sprite[ply_id].width, sprite[ply_id].height, sprite[ply_id].box_width, sprite[ply_id].box_height, 4, GFX, 0.01f, 0, 0, FX_FALLING_BOMB, ply_id, 2, 0, 0, -1);      
               
               whistle_sfx = true;
               silo1_fired=false;
           } 
           
           title_timer = (int)TimerGetTime() + 2000;
           title_sequence++; 
       }    
                            
       // Close Silos...
       if((int)TimerGetTime() > title_timer)         
       if(title_sequence == 11)    
       {     

           title_sequence=1;      
       }              
      
       // Boss Second Form...
       if(title_sequence == 12) 
       {
           sprite[36].alpha = 1.0; 
           sprite[36].grab_switch = true;
           
           if(sprite[36].score > 0)
               hatch_sfx = true; 
                          
           title_timer = (int)TimerGetTime() + 1000; 
           title_sequence++;                
       } 
         
       // Pop-out guns...
       if((int)TimerGetTime() > title_timer)        
       if(title_sequence == 13) 
       {   
           if(sprite[36].score > 0)    
               Set_Sprite(36, 10, PLAY, ANIM_SPRITE, ANIM_WALKING); // Guns Out...

           sprite[36].spotted = true; 

           // Tracers...          
           sprite[37].alpha = 0.0;
           sprite[38].alpha = 0.0;
           sprite[39].alpha = 0.0;
                          
           bullet_count = 0; 
           scripts_bullet_timer=0;
                                    
           title_timer = (int)TimerGetTime() + 1500;
           title_sequence++;          
       }
       
       // Shoot Gun Straight...  
       if((int)TimerGetTime() > title_timer)        
       if(title_sequence == 14)    
       {      
   
           if((int)TimerGetTime() > scripts_bullet_timer)
           {             
                                
             if(sprite[36].score > 0) 
             {
                 if(boss_front == true)
                 {                 
                     mid_x = sprite[36].w+sprite[36].box_width/2; 
                     mid_y = sprite[36].z+sprite[36].box_height/2; 
                 
                     Boss_Shoot(36, mid_x, mid_y, -2.6f, f_rate);
                                                  
                     Set_Sprite(36, 11, LOOP, ANIM_SPRITE, ANIM_WALKING);
                     
                     sprite[37].alpha = 1.0f;
                 }
                 else   
                 {
                     mid_x = sprite[36].w+sprite[36].box_width/2; 
                     mid_y = sprite[36].z+sprite[36].box_height/2; 
                 
                     Boss_Shoot(36, mid_x, mid_y, 3.1f, f_rate);
                     
                     mid_x = sprite[36].w+sprite[36].box_width/2; 
                     mid_y = sprite[36].z+sprite[36].box_height/2; 
                 
                     Boss_Shoot(36, mid_x, mid_y, -1.4f, f_rate);
                     
                     sprite[38].alpha = 1.0f;
                     sprite[39].alpha = 1.0f;
                                                                                                                 
                     Set_Sprite(36, 12, LOOP, ANIM_SPRITE, ANIM_WALKING);
                 }
                 
             }
                          
             if(sprite[36].score > 0)  
                 mount_sfx = true; 
               
             scripts_bullet_timer = (int)TimerGetTime() + 100;
             
             bullet_count++;  
             
           }      
              
           if(bullet_count >= 50 || sprite[36].score <= 0 )
           {           
              if(boss_front == true)
                  boss_front = false;
              else
                  boss_front = true;         
                       
              title_sequence=13;         
           } 
            
       }  
        
       // Boss Third Form...
       if(title_sequence == 15) 
       {
           // Tracers...          
           sprite[37].alpha = 0.0f;
           sprite[38].alpha = 0.0f;
           sprite[39].alpha = 0.0f;

           sprite[31].spotted = true;                         
           sprite[31].grab_switch = true; 
             
           title_timer = (int)TimerGetTime() + 2000; 
           title_sequence++;                 
       }  
       
       // Fire First Silo...
       if((int)TimerGetTime() > title_timer)       
       if(title_sequence == 16)     
       {
           if(sprite[32].score > 0)
           {
               Set_Sprite(32, 7, PLAY, ANIM_SPRITE, ANIM_WALKING);           
               splash_sfx = true;
               
               silo_fired=true;
           } 
           
           title_timer = (int)TimerGetTime() + 150;
           title_sequence++; 
       }            
              
       // Close First Silo...
       if((int)TimerGetTime() > title_timer)       
       if(title_sequence == 17)    
       {
           
           if(sprite[32].score > 0)
               Set_Sprite(32, 5, LOOP, ANIM_SPRITE, ANIM_WALKING); 
           
           if(silo_fired == true && ply_id != -1)
           {
                
               mid_x = sprite[ply_id].x+sprite[ply_id].width/2;
               mid_y = sprite[ply_id].y+sprite[ply_id].height/2; 
                                         
               New_FX(mid_x, mid_y, sprite[ply_id].w, sprite[ply_id].z, 11, LOOP, sprite[ply_id].width, sprite[ply_id].height, sprite[ply_id].box_width, sprite[ply_id].box_height, 4, GFX, 0.01f, 0, 0, FX_FALLING_BOMB, ply_id, 2, 0, 0, -1);      
               
               whistle_sfx = true;
               silo_fired=false; 
           }    
              
           if(sprite[31].score > 0) 
               title_timer = (int)TimerGetTime() + 3000;
           else
               title_timer = (int)TimerGetTime() + 1000;
               
           title_sequence=16; 
       }    
                
       if(title_sequence == 18)  
	   if((int)TimerGetTime() > boss_blow_timer)
       {
           boss_speed = 0.0f;        
             
           if(boss_accel <= 0.00003f)
           {
               sprite[33].alpha = 0.0f; 
               sprite[36].alpha = 0.0f;
               sprite[29].alpha = 0.0f;
               sprite[30].alpha = 0.0f;  
               sprite[35].alpha = 0.0f;
               sprite[34].alpha = 0.0f;
               sprite[32].alpha = 0.0f;
                 
               sprite[27].id = 20;
               sprite[27].fx_id = animation_fx[sprite[27].id];
               sprite[28].id = 20; 
               sprite[28].fx_id = animation_fx[sprite[28].id];
               sprite[31].id = 20;
               sprite[31].fx_id = animation_fx[sprite[31].id];
               
               Set_Sprite(27, 0, PLAY, ANIM_SPRITE, ANIM_WALKING);
               Set_Sprite(28, 0, PLAY, ANIM_SPRITE, ANIM_WALKING);
               Set_Sprite(31, 1, PLAY, ANIM_SPRITE, ANIM_WALKING);
               
               boss_sfx = true;     
                                     
               title_timer = (int)TimerGetTime() + 1200;
               title_sequence++; 
                          
           }
                 
       }         
       
       // End Level... 
       if((int)TimerGetTime() > title_timer)                                                        
       if(title_sequence == 19) 
       if(ply_dead == false && ply_id != -1)          
       {
           sprite[27].alpha = 0.0f;
           sprite[28].alpha = 0.0f;   
           sprite[31].alpha = 0.0f; 
           sprite[32].alpha = 0.0f;  
           
           Display_Message(ply_id, MSG_SUCCESS); 
           sprite[ply_id].status = CELEBRATE;
		   Convert_Dir_To_Angle(ply_id, DOWN);	
             
           sprite[ply_id].update = true;   
           sprite[ply_id].anim_state = WAIT;
           sprite[ply_id].moving = false;
           sprite[ply_id].all_timer = (int)TimerGetTime() + 5000;   
                    
           lock_player = true; 
           
           title_timer = (int)TimerGetTime() + 4000;
           title_sequence++;
                                                     
       }                           
            
       // Change Scene... 
       if((int)TimerGetTime() > title_timer)                                                        
       if(title_sequence == 20)   
       if(ply_dead == false)           
       { 
           
           episode = 1;
           scene   = 44;  
           next_scene = true;       
            
       }                         
        
	   if( ply_id != -1 )
	   {	
	       cam_x = (sprite[ply_id].x + sprite[ply_id].width/2);
	       cam_y = sprite[ply_id].y;  
	   }
               
       deltax = cos(0.62f)* 0.25f; // Was 1.2    
       deltay = sin(0.62f)* 0.25f; // Was 1.2 
                             
       camX_OFFSET = -(deltax);    
       camY_OFFSET = -(deltay);  
       
       if(title_sequence < 18) // Boss is Dead...
       {             
           // Boss movement code     
           boss_speed = (0.00020f*(float)f_rate);      
         
           if(sprite[27].score <= 0 || sprite[28].score <= 0)
           {
               boss_speed = (0.00030f*(float)f_rate);      
               boss_accel = (0.00030f*(float)f_rate);
           } 
           if(sprite[27].score <= 0 && sprite[28].score <= 0)
           {
               boss_speed = (0.00038f*(float)f_rate);              
               boss_accel = (0.00038f*(float)f_rate); 
           }  
           if(sprite[31].score <= 0)   
           {  
               boss_speed = (0.00045f*(float)f_rate);    
               boss_accel = (0.00045f*(float)f_rate);
           }
            
       }        
	         
       if(title_sequence < 18)      
	   {
		    
		   if(sprite[27].score > 0 && sprite[28].score > 0 && sprite[31].score > 0)
			   boss_accel += (0.000001f*(float)f_rate);
		   
		   if(boss_accel > boss_speed)  
				boss_accel = boss_speed; 
	   } 

       if(title_sequence >= 18)         
	   {     
		//   if(boss_accel > 0.0f)
		//	   boss_accel -= (0.0000015f*(float)f_rate);
		//   else
		    boss_accel = 0.0f;
	   }

       if(reverse == false)   
           angle = -0.62f;    
       if(reverse == true)   
           angle = 2.52f;
       
       deltax = cos(angle); // Was 1.2    
       deltay = sin(angle); // Was 1.2       

       deltax *= boss_accel;     
       deltay *= boss_accel;     
    
	   if(boss_accel > 0.0f)
       for(int i = 27; i < 40; i++)
       {
           sprite[i].x += deltax; 
           sprite[i].y += deltay;
           sprite[i].w += deltax; 
           sprite[i].z += deltay;       
       } 
              
       mid_x = sprite[27].w+sprite[27].box_width/2; 
       mid_y = sprite[27].z+sprite[27].box_height/2; 
       
       distance = Node_Distance1(mid_x, mid_y, points[2].x, points[2].y);
       
       if(distance <= 0.4) 
           reverse = false;
       
       mid_x = sprite[28].w+sprite[28].box_width/2; 
       mid_y = sprite[28].z+sprite[28].box_height/2; 
              
       distance = Node_Distance1(mid_x, mid_y, points[3].x, points[3].y);
        
       if(distance <= 0.4)
           reverse = true;  
       
       // Check for second form...
       if(title_sequence < 12)
       if(sprite[27].score <= 0) // Ballast Tank
       if(sprite[28].score <= 0) // Ballast Tank
       if(sprite[29].score <= 0) // Ballast Tank
       if(sprite[30].score <= 0) // Ballast Tank       
           title_sequence = 12;
       
       if(title_sequence < 15)    
       if(sprite[36].score <= 0) // Front Gun
           title_sequence = 15;  
       

       if(sprite[33].score <= 0) 
       if(title_sequence < 18)  
       {    
           title_sequence = 18; 

		   boss_blow_timer = (int)TimerGetTime()+3000;

		//   boss_accel = 0.00020f*(float)f_rate;

           Set_Sprite(32, 6, PLAY, ANIM_SPRITE, ANIM_WALKING); 
       }      

       for(int i = 27; i < 37; i++)    
       {  

         // Explosion code...
         if(sprite[i].score <= 0 && sprite[i].alpha == 1.0) 
         if(title_sequence < 19)
         if((int)TimerGetTime() > sprite[i].all_timer)
         if( i == 27 || i == 28 || i == 31 || i == 32)
         {
            mid_x = sprite[i].w+sprite[i].box_width/2; 
            mid_y = sprite[i].z+sprite[i].box_height/2; 
            
            New_FX(mid_x-0.2f, mid_y-0.2f, mid_x, mid_y, 37, PLAY, 0.4f, 0.4f, 0.4f, 0.4f, 2, GFX, 1.0f, 0, 0, FX_EXPLOSION, -1, 2, 0, 0, -1);
            New_FX(mid_x-0.2f, mid_y-0.2f, mid_x, mid_y, 113, PLAY, 0.4f, 0.4f, 0.4f, 0.4f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);

			sprite[i].flash_target = true;
            sprite[i].flash_timer = (int)TimerGetTime() + 25;

            if(title_sequence < 17) 
            {
                sprite[i].all_timer = (int)TimerGetTime() + 3000;                                
            }  
            else       
            {   

				if((int)TimerGetTime() < boss_blow_timer - 1500)
					sprite[i].all_timer = (int)TimerGetTime() + 250;
				else 
					sprite[i].all_timer = (int)TimerGetTime() + 12500;

				#if INCLDUE_360_CONTROLLER  == 1
				if(CONTROLLER) 
				{
					VIBRATE_LEFT(48000, 150); 
					VIBRATE_RIGHT(48000, 150);
				}
				#endif

                Camera_Shake(THUD_SHAKE);    
                clank_sfx=true;                                  
            } 
         }  
         
         if(sprite[i].score <= 0 && sprite[i].grab_switch == true)
         {
            mid_x = sprite[i].w+sprite[i].box_width/2; 
            mid_y = sprite[i].z+sprite[i].box_height/2; 
              
            sprite[i].grab_switch = false;   
			sprite[i].flash_target = true;
            sprite[i].flash_timer = (int)TimerGetTime() + 25;

            Set_Sprite(i, sprite[i].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING);
            New_FX(mid_x-0.2f, mid_y-0.2f, mid_x, mid_y, 37, PLAY, 0.4f, 0.4f, 0.4f, 0.4f, 1, GFX, 1.0f, 0, 0, FX_EXPLOSION, -1, 2, 0, 0, -1);
            New_FX(mid_x-0.2f, mid_y-0.2f, mid_x, mid_y, 113, PLAY, 0.4f, 0.4f, 0.4f, 0.4f, 1, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);

            Camera_Shake(THUD_SHAKE);   

			#if INCLDUE_360_CONTROLLER  == 1
			if(CONTROLLER) 
			{
				VIBRATE_LEFT(48000, 150); 
				VIBRATE_RIGHT(48000, 150);
			}
			#endif

            clank_sfx=true;   
            
            if(i == 33) // Gear
		    { 
                sprite[32].score = 0;
				gargle_sfx = true;
			}
            
            if(i == 30) 
                sprite[35].alpha = 0.0f;
                
            if(i == 29)
                sprite[34].alpha = 0.0f;
             
            if(i == 28) 
            {
                sprite[30].grab_switch = false;
                sprite[30].mouseover = true;
                sprite[30].turn_off  = true;     
                sprite[30].score = 0;
                sprite[35].alpha = 0.0f;  // Tracers...  
            }
            if(i == 27)
            { 
                sprite[29].grab_switch = false;
                sprite[29].mouseover = true;
                sprite[29].turn_off  = true; 
                sprite[29].score = 0;  
                sprite[34].alpha = 0.0f; // Tracers...  
            }
            if(i == 31) // Submarine Body...
            {                     
				sprite[33].spotted = true;  
                sprite[33].grab_switch = true; 
                sprite[33].alpha = 1.0;
            }      
 
            
                    
         }      
       }
     

   }


   
             
} 

void Boss_Shoot( int shooter, float x1, float y1, float angle, int f_rate)
{
    
    float x=0.0f, y=0.0f;
    float deltax=0.0f, deltay=0.0f;
    float mid_x=0.0f, mid_y =0.0f;
    float mid_x1=0.0f, mid_y1 =0.0f;    
    float tar_x=0.0f, tar_y =0.0f; 
    float step=0.0f, distance=2.4f; 
    int iterations=0; 
	float distance_check = 0.0f;
    bool test_success=false;

	if(f_rate <= 0)
	    f_rate = 1;   
    
    x = x1;  
    y = y1;
       
    deltax = cos(angle);     
    deltay = sin(angle);  
         
    deltax *= (float)LINE_OF_SIGHT;      
    deltay *= (float)LINE_OF_SIGHT;    
        
    step = Node_Distance1(x1, y1, x1+deltax, y1+deltay);

	if(ply_id != -1)
	{
		mid_x = sprite[ply_id].w+sprite[ply_id].box_width/2; 
		mid_y = sprite[ply_id].z+sprite[ply_id].box_height/2;
	}
	 
	tar_x = sprite[shooter].w;
	tar_y = sprite[shooter].z; 

	distance_check = Node_Distance1(mid_x, mid_y, tar_x, tar_y);

    if( step != 0) 
        iterations = (int)(distance / step);
      
    if(iterations < 0)       
        iterations = 0;  
	
	if(distance_check < 1.6)
    for (int j = 0; j <= iterations; j++)
    {
        
    if(test_success == true) 
        break; 
                
    x += deltax; // Which is the mid_x
    y += deltay; // Which is the mid_y

    // Fish...
    mid_x = sprite[48].w+sprite[48].box_width/2; 
    mid_y = sprite[48].z+sprite[48].box_height/2;
    
    if(test_success == false)   
    if(sprite[48].priority != 3)         
    if(sprite[48].score > 0)               
    if(( x < mid_x + 0.05 )  
    &&( x > mid_x - 0.05)                         
    &&( y < mid_y + 0.05)  
    &&( y > mid_y - 0.05) )        
    {
        sprite[48].flash_target = true;
        sprite[48].flash_timer = (int)TimerGetTime() + 30;
        
        sprite[48].score--;
         
        if(sprite[48].score <= 0)
        {
            Set_Sprite(48, sprite[48].base_anim+1, ONCE, ANIM_SPRITE, ANIM_WALKING);
            Generate_Object_Collision(48, REMOVE_COL);
            sprite[48].priority = 3;                
            drown_sfx = true; 
        }
        
        test_success = true;
    } 

    // Fish...
    mid_x = sprite[49].w+sprite[49].box_width/2; 
    mid_y = sprite[49].z+sprite[49].box_height/2;
    
    if(test_success == false)   
    if(sprite[49].priority != 3)         
    if(sprite[49].score > 0)               
    if(( x < mid_x + 0.05 )   
    &&( x > mid_x - 0.05)                         
    &&( y < mid_y + 0.05)  
    &&( y > mid_y - 0.05) )        
    {
        sprite[49].flash_target = true;
        sprite[49].flash_timer = (int)TimerGetTime() + 30;
        
        sprite[49].score--; 
         
        if(sprite[49].score <= 0)
        {
            Set_Sprite(49, sprite[49].base_anim+1, ONCE, ANIM_SPRITE, ANIM_WALKING);
            Generate_Object_Collision(49, REMOVE_COL);
            sprite[49].priority = 3;                
            drown_sfx = true; 
        }
        
        test_success = true;
    } 
    
    
    



    // Pillar...
    mid_x = sprite[41].w+sprite[41].box_width/2; 
    mid_y = sprite[41].z+sprite[41].box_height/2;
    
    if(test_success == false)   
    if(sprite[41].priority != 3)         
    if(sprite[41].score > 0)               
    if(( x < mid_x + 0.05 )  
    &&( x > mid_x - 0.05)                         
    &&( y < mid_y + 0.05)  
    &&( y > mid_y - 0.05) )        
    {
        sprite[41].flash_target = true;
        sprite[41].flash_timer = (int)TimerGetTime() + 30;
        
        sprite[41].score--;
         
        if(sprite[41].score <= 0)
        {
            Set_Sprite(41, sprite[41].base_anim+1, ONCE, ANIM_SPRITE, ANIM_WALKING);
            Generate_Object_Collision(41, REMOVE_COL);
            sprite[41].priority = 3;                
            destroy_sfx = true;
        }
        
        test_success = true;
    } 
    
    // Pillar...
    mid_x = sprite[43].w+sprite[43].box_width/2; 
    mid_y = sprite[43].z+sprite[43].box_height/2;
    
    if(test_success == false) 
    if(sprite[43].priority != 3)     
    if(sprite[43].score > 0)               
    if(( x < mid_x + 0.05 )  
    &&( x > mid_x - 0.05)                         
    &&( y < mid_y + 0.05)  
    &&( y > mid_y - 0.05) )        
    {
        sprite[43].flash_target = true;
        sprite[43].flash_timer = (int)TimerGetTime() + 30;
        
        sprite[43].score--;
         
        if(sprite[43].score <= 0)
        {
            Set_Sprite(43, sprite[43].base_anim+1, ONCE, ANIM_SPRITE, ANIM_WALKING);
            Generate_Object_Collision(43, REMOVE_COL);
            sprite[43].priority = 3;                
            destroy_sfx = true;
        }
                
        test_success = true;
    } 
    
    // Cover Box...
    mid_x = sprite[46].w; 
    mid_y = sprite[46].z;
    mid_x1 = sprite[46].w+sprite[46].box_width;
    mid_y1 = sprite[46].z+sprite[46].box_height;
        
    if(test_success == false)
    if(sprite[46].priority != 3)             
    if(sprite[46].score > 0)               
    if(( x < mid_x1 )  
    &&( x > mid_x)                          
    &&( y < mid_y1)  
    &&( y > mid_y) )        
    {
        sprite[46].flash_target = true;
        sprite[46].flash_timer = (int)TimerGetTime() + 30;
        
        sprite[46].score--;
         
        if(sprite[46].score <= 0)
        {
            Set_Sprite(46, sprite[46].base_anim+1, ONCE, ANIM_SPRITE, ANIM_WALKING);
            Generate_Object_Collision(46, REMOVE_COL);
            sprite[46].priority = 3;                
            destroy_sfx = true;
            Spawn_Pickup(46, BOSS_DROP);
        }
                
        test_success = true;
    } 
    
    // Back Box...
    mid_x = sprite[11].w; 
    mid_y = sprite[11].z;
    mid_x1 = sprite[11].w+sprite[11].box_width;
    mid_y1 = sprite[11].z+sprite[11].box_height;
        
    if(test_success == false)
    if(sprite[11].priority != 3)             
    if(sprite[11].score > 0)               
    if(( x < mid_x1 )   
    &&( x > mid_x)                          
    &&( y < mid_y1)  
    &&( y > mid_y) )          
    {
        sprite[11].flash_target = true;
        sprite[11].flash_timer = (int)TimerGetTime() + 30;
        
        sprite[11].score--;
         
        if(sprite[11].score <= 0)
        {
            Set_Sprite(11, sprite[11].base_anim+1, ONCE, ANIM_SPRITE, ANIM_WALKING);
            Generate_Object_Collision(11, REMOVE_COL);
            sprite[11].priority = 3;                
            destroy_sfx = true;
            Spawn_Pickup(11, BOSS_DROP);            
        }
                
        test_success = true;
    }  
     
    // Player...
    if(ply_id != -1)
    {    
        mid_x = sprite[ply_id].w+sprite[ply_id].box_width/2; 
        mid_y = sprite[ply_id].z+sprite[ply_id].box_height/2;    
    
        if(test_success == false)        
        if(sprite[ply_id].score > 0)                
        if(( x < mid_x + 0.05 )  
        &&( x > mid_x - 0.05)                         
        &&( y < mid_y + 0.05)   
        &&( y > mid_y - 0.05) )        
        {
            Man_Shot(0, ply_id, shooter, BULLET_NONE, f_rate);
            test_success = true;
        }         
    } 
    
    // Buddy...
    if(p1_buddy != -1)  
    {    
        mid_x = sprite[p1_buddy].w+sprite[p1_buddy].box_width/2; 
        mid_y = sprite[p1_buddy].z+sprite[p1_buddy].box_height/2;  
            
    
        if(test_success == false)        
        if(sprite[p1_buddy].score > 0)                
        if(( x < mid_x + 0.05 )  
        &&( x > mid_x - 0.05)                         
        &&( y < mid_y + 0.05)  
        &&( y > mid_y - 0.05) )        
        {
            Man_Shot(0, p1_buddy, shooter, BULLET_NONE, f_rate);
            test_success = true;
        }   
    }
                
     
    } 
     
     
     
}


void Check_Boss_Explode(int index)  
{
            
       if(sprite[index].score <= 0 && sprite[index].grab_switch == true)
       {
           exploding_id = index;
           exploding_timer = (int)TimerGetTime() + 100;
           exploding_count=3; 
           sprite[index].grab_switch = false;
           Set_Sprite(index, sprite[index].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING);
           
           if(index == 8) 
           { 
               Set_Sprite(8, 7, LOOP, ANIM_SPRITE, ANIM_WALKING);
               Set_Sprite(4, 6, LOOP, ANIM_SPRITE, ANIM_WALKING);
               Set_Sprite(5, 6, LOOP, ANIM_SPRITE, ANIM_WALKING);
               Set_Sprite(40, 6, LOOP, ANIM_SPRITE, ANIM_WALKING);
               Set_Sprite(41, 6, LOOP, ANIM_SPRITE, ANIM_WALKING); 
               
               sprite[8].priority = 3; 
               sprite[4].priority = 3;
               sprite[5].priority = 3;
               sprite[40].priority = 3;
               sprite[41].priority = 3;  
               sprite[54].priority = 3;   
               
               sprite[6].alpha = 0.0;   
               sprite[7].alpha = 0.0; 
               sprite[10].alpha = 0.0;   
               sprite[13].alpha = 0.0; 
                
               sprite[8].score = 0;  
               sprite[4].score = 0;
               sprite[5].score = 0; 
               sprite[40].score = 0; 
               sprite[41].score = 0; 
               sprite[54].score = 0;    
               sprite[6].score = 0; 
               sprite[7].score = 0;  
               
               sprite[8].grab_switch = false;
               sprite[4].grab_switch = false;
               sprite[5].grab_switch = false;
               sprite[40].grab_switch = false;
               sprite[41].grab_switch = false;                             
               sprite[54].grab_switch = false;
               sprite[6].grab_switch = false;                             
               sprite[7].grab_switch = false;
               
               sprite[54].alpha = 0.0;
               
               exploding_count=10;   
               
               stop_tank_boss_sfx = true;  
               stop_tank_track_sfx = true;
         
               title_sequence=2; 
                
               title_timer = (int)TimerGetTime()+1000;     
           }
           
       }
           
}

void Check_Splat(int index) 
{
    float mid_x=0.0, mid_y=0.0;
    float x_pos=0.0, y_pos=0.0;
    float dis_to_point = -1; 
         
	  if(index >= 0)
      if(ply_id != -1)  
      if(sprite[ply_id].score > 0)   
      if(sprite[ply_id].grab_switch == true)
      if(sprite[index].priority != 3)
      { 
                                 
          mid_x = sprite[ply_id].w+sprite[ply_id].box_width/2; 
          mid_y = sprite[ply_id].z+sprite[ply_id].box_height/2; 
           
          x_pos = sprite[index].w+sprite[index].box_width/2; 
          y_pos = sprite[index].z+sprite[index].box_height/2;             
         
          dis_to_point = Node_Distance1(mid_x, mid_y, x_pos, y_pos);
          
          if(ply_id != -1) 
          if(sprite[ply_id].status != FLATTENED)
          if(dis_to_point <= 0.25)   
          {        
               sprite[ply_id].status = FLATTENED;
               sprite[ply_id].update = true;
               sprite[ply_id].anim_state = WAIT;
               sprite[ply_id].all_timer = (int)TimerGetTime() + 3000;         
               drown_sfx = true;          
          }
           
      }
        
      if(p1_buddy != -1) 
      if(sprite[p1_buddy].score > 0)  
      if(sprite[p1_buddy].grab_switch == true)
      if(sprite[index].priority != 3)
      { 
                                 
          mid_x = sprite[p1_buddy].w+sprite[p1_buddy].box_width/2; 
          mid_y = sprite[p1_buddy].z+sprite[p1_buddy].box_height/2; 
           
          x_pos = sprite[index].w+sprite[index].box_width/2; 
          y_pos = sprite[index].z+sprite[index].box_height/2;             
         
          dis_to_point = Node_Distance1(mid_x, mid_y, x_pos, y_pos);
          
          if(ply_id != -1)  
          if(boss_success == false)
          if(sprite[p1_buddy].status != FLATTENED)
          if(dis_to_point <= 0.25)   
          {        
               sprite[p1_buddy].status = FLATTENED;
               sprite[p1_buddy].update = true;
               sprite[p1_buddy].anim_state = WAIT;
               sprite[p1_buddy].all_timer = (int)TimerGetTime() + 3000;         
               drown_sfx = true;  
          }
           
      }      
      
}
