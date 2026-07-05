
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN 

#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>			// Header File For Standard Input/Output
#include <gl\gl.h> 
#include "globals.h"  

#define WALK_LIMIT_ON  0
#define WALK_LIMIT 0.5 

extern int Find_Path(int loop, float destX, float destY);
extern int New_Sprite(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int sideways, int upways, int state, int linked_sprite, int tex_id, int a_global, float angle, int p_type, int goto_point);
extern void ShotIdle(int loop); 
extern bool Is_Guy_In_Range(int loop, int target, float range);  
extern void Message_Limits();  
extern bool Shoot_Ray(int loop, float x1, float y1, float x2, float y2, bool grey_test, bool shooting, float precision);  
extern void Calculate_Bullets();     
extern void Calculate_Lifebar();       
extern void Calculate_Mission(); 
extern void Calculate_Bullet_Flash();   
extern float Calculate_Emybar(int index);       
extern void Calculate_Inventory();
extern void Get_Mouse_Row(); 
extern void PickUp_Sfx(int type, int value); 
extern void Moving_Code(int loop, float x_pos, float y_pos, int f_rate);
extern int Get_Tile_Index(float x, float y);
extern bool TestSpriteToShootPly(int no_test, float x1, float y1, float x2, float y2, bool hulk, int target_id, int f_rate, bool shotgun_attack);
extern bool Get_Next_Tile(int k, float x2, float y2);

void Run_Keyboard(int f_rate1);
void Run_Mouse(int f_rate1);
void Do_Player_Accel(int f_rate);

void Run_Keyboard(int f_rate1)
{
     
    bool on_collision=false;  
    bool test=false;          
    float midX=0.0, midY=0.0;
    float tarX=0.0, tarY=0.0;
    float tarX1=0.0, tarY1=0.0;    
    float diffX=0.0, diffY=0.0;    
    float deltax=0.0, deltay=0.0;
    float angle=0.0;     
    float distance = 0.0;   
    int temp_row_x=0, temp_row_y=0;
    int index = 0;  
	int pack_id = 0;
	int same_trap_value=0; 
    bool skip_this=false;

	if(f_rate1 <= 0) 
	    f_rate1 = 1; 
   
	if(CONTROLLER == true) 
	{
		KEY_FORWARD   = false;
		KEY_BACKWARD  = false; 
		KEY_LEFTWARD  = false; 
		KEY_RIGHTWARD = false;
	} 

            // Move the Unit Out  
			if(sta2_displaying_help == false)
			if(sta2_turn == TURN_PLAYER)
            if(lock_player != true)
            if(ply_dead == false)   
            if(ply_id != -1)   
			if(STA2_MODE == MODE_MOVING && sprite[ply_id].movement > 0)
			if(sprite[ply_id].score > 1)
			if(sprite[ply_id].status != FALLING && sprite[ply_id].status != LEVELING) 
            if( test == false && DX_INV_ACTIVE == false && disable_scrolling == false) 
            if(!mode && ( (KEY_FORWARD == true || KEY_BACKWARD == true) || (KEY_LEFTWARD == true || KEY_RIGHTWARD == true) && !CONTROLLER )
			|| (CONTROLLER == true && DX_LX != 0.0 || DX_LY != 0.0)) 
            if(sprite[ply_id].status != OPEN_STAMP 
            && sprite[ply_id].status != FOOT_SHOT 
            && sprite[ply_id].status != FLATTENED
			&& sprite[ply_id].status != MERCY
			&& sprite[ply_id].status != STUNNED
            )        
            { 
                
                    // Check against player... 
                    if( sprite[ply_id].type == UNT )       
                    if( sprite[ply_id].score > 0                    
                    || sprite[ply_id].status == DIEING
                    || sprite[ply_id].status == MAN_DOWN)     
                    {     

						   float control_speed = 0.2f * f_rate1; 

                           on_collision=false;         
          
                           sprite[ply_id].update = true;       
                               
                           midX = sprite[ply_id].w+sprite[ply_id].box_width/2;      
                           midY = sprite[ply_id].z+sprite[ply_id].box_height/2; 
							 
						   if(CONTROLLER)    
						   {    
								keys_diffX = (DX_LX / (32767*2) ) / 1.6f;
								keys_diffY = (DX_LY / (32767*2) ) / 1.6f;
						   }     
						     
						   if(!CONTROLLER)	 
						   {
							   if(KEY_FORWARD == false && KEY_BACKWARD == false)
							   {
   				  				   if(midY + keys_diffY >= midY)   
   				  					   keys_diffY -= (0.0012f * f_rate1);
   				  				   if(midY + keys_diffY < midY)
   				  					   keys_diffY += (0.0012f * f_rate1);    

								   if( keys_diffY >= -(0.0012f * f_rate1) && keys_diffY <= (0.0012f * f_rate1) )
									   keys_diffY = 0.0;
							   } 
							   if(KEY_LEFTWARD == false && KEY_RIGHTWARD == false)
							   {
   				  				   if(midX + keys_diffX >= midX) 
   				  					   keys_diffX -= (0.0012f * f_rate1); 
   				  				   if(midX + keys_diffX < midX) 
   				  					   keys_diffX += (0.0012f * f_rate1);

								   if( keys_diffX >= -(0.0012f * f_rate1) && keys_diffX <= (0.0012f * f_rate1) )
									   keys_diffX = 0.0;
							   }

							   // Sepert...
							   if(KEY_FORWARD == true && KEY_BACKWARD == false)
							   {
								   keys_diffY += control_speed;  
								   if(keys_diffY >= 0.3f)
									   keys_diffY = 0.3f;
                               
							   }
						    
							   if(KEY_BACKWARD == true && KEY_FORWARD == false)
							   {
								   keys_diffY -= control_speed;  
								   if(keys_diffY <= -0.3f) 
									   keys_diffY = -0.3f;                           
                               
							   }
						    
							   if(KEY_LEFTWARD == true && KEY_RIGHTWARD == false)
							   {
								   keys_diffX -= control_speed; 
								   if(keys_diffX <= -0.3f)
									   keys_diffX = -0.3f;  							    
                               
							   }
						      
							   if(KEY_RIGHTWARD == true && KEY_LEFTWARD == false)
							   {
								   keys_diffX += control_speed; 
								   if(keys_diffX >= 0.3f)
									   keys_diffX = 0.3f;   							     
                               
							   } 

						   }// CONTROLLER = false;
                                                   
                           sprite[ply_id].mov_x = midX + keys_diffX;
                           sprite[ply_id].mov_y = midY + keys_diffY;

						   if( sprite[ply_id].mov_x <= -map_startX) 
						       sprite[ply_id].mov_x = -map_startX;

						   if( sprite[ply_id].mov_x >= (-map_startX + (MAP_WIDTH*0.1f) ) ) 
						       sprite[ply_id].mov_x = (-map_startX + (MAP_WIDTH*0.1f) );
	   
						   if( sprite[ply_id].mov_y <= -map_startY)   
						       sprite[ply_id].mov_y = -map_startY; 

						   if( sprite[ply_id].mov_y > (-map_startY + MAP_HEIGHT*0.1f)) 
						       sprite[ply_id].mov_y = (-map_startY + MAP_HEIGHT*0.1f);
                               
                           sprite[ply_id].end_x = sprite[ply_id].mov_x;          
                           sprite[ply_id].end_y = sprite[ply_id].mov_y;  

                           if(on_collision == false)   
                           {  
                                               
                                   //  Not walking into a tile...
                                   if(Get_Next_Tile(ply_id, sprite[ply_id].mov_x, sprite[ply_id].mov_y) == true)
                                   {   
   
                                       // Stops walking anim bug...
                                       if(sprite[ply_id].status != MOVE_OUT && sprite[ply_id].status != OPEN_FIRE)
									   { 
                                           sprite[ply_id].anim_state = WAIT; 
									   }
                                           
                                       if(sprite[ply_id].status != OPEN_FIRE && sprite[ply_id].status != OPEN_CUT && sprite[ply_id].status != OPEN_THROW && sprite[ply_id].status != AIMING)
                                           sprite[ply_id].status = MOVE_OUT; 
                                                                                
                                       sprite[ply_id].moving = true;   
 
                                   }     
                                   else // Walked into a tile..      
                                   {
                                       if(Find_Path(ply_id, -1, -1) > 0 && Node_Distance1(midX, midY, sprite[ply_id].end_x, sprite[ply_id].end_y) > 0.15)
                                       {       
                                           // Stops walking anim bug
                                           if(sprite[ply_id].status != MOVE_OUT && sprite[ply_id].status != OPEN_FIRE  )
									   	   { 
                                               sprite[ply_id].anim_state = WAIT; 
									       }
                                               
										   if(sprite[ply_id].status != OPEN_FIRE && sprite[ply_id].status != OPEN_CUT && sprite[ply_id].status != OPEN_THROW && sprite[ply_id].status != AIMING)
                                               sprite[ply_id].status = MOVE_OUT; 
                                                                                    
                                           sprite[ply_id].moving = true; 
                                       }
                                       else 
                                       {
									   	  if(sprite[ply_id].status != OPEN_FIRE && sprite[ply_id].status != OPEN_CUT && sprite[ply_id].status != OPEN_THROW && sprite[ply_id].status != AIMING) 
                                              ShotIdle(ply_id); 
									   }
                                   }
                           
                           } // on_collision == false  
                             
                           dpointX = sprite[ply_id].w+sprite[ply_id].box_width/2;     
                           dpointY = sprite[ply_id].z+sprite[ply_id].box_height/2;
                           
                           dpointX1 = sprite[ply_id].mov_x;
                           dpointY1 = sprite[ply_id].mov_y;                                                            
                                                                                              
                        } // sprite[ply_id].type == UNT

                     
            }          
      
            // Slashing code..    
			if(sta2_displaying_help == false)
			if(sta2_turn == TURN_PLAYER)
            if(lock_player != true) 
            if(ply_dead == false) 
            if(ply_id != -1)  
			if(sprite[ply_id].score > 1)
			if(sprite[ply_id].status != FALLING)             
            if(sprite[ply_id].on_ladder == false)  
			if(DX_INV_ACTIVE == false)
            if( test == false && mouse_grabbed == false)     
            if(!mode && (KEY_SPACE == true || mousemiddle == true || DX_GRENADE_KEY == true || DX_TRAP_KEY == true || DX_KNIFE == true) )
            if( sprite[ply_id].status != OPEN_CUT  
            && sprite[ply_id].status != OPEN_STAMP   
			&& sprite[ply_id].status != OPEN_THROW 
            && sprite[ply_id].status != STUNNED
            && sprite[ply_id].status != FOOT_SHOT
			&& sprite[ply_id].status != MERCY
            && sprite[ply_id].status != FLATTENED)   
            {
                    // Check against player...
                    if( sprite[ply_id].type == UNT )      
                    if( sprite[ply_id].score > 0                  
                    || sprite[ply_id].status == DIEING
                    || sprite[ply_id].status == MAN_DOWN)      
                    {
                                            
                           if(lock_player != true)                 
                           if(ply_dead == false) 
                           if(sprite[ply_id].status != FALLING)             
                           if(sprite[ply_id].status != STUNNED) 
                           if( (int)TimerGetTime() > sprite[ply_id].reload_timer )
                           if(sprite[ply_id].score > 0 && ply_dead == false && hud_corner == true) 
                           {   
						   	   if(KEY_SPACE == true)  
	                               space_is_held=true;   
                                
                               reloading = false;   

						/*	   if(mousemiddle == true || DX_GRENADE_KEY == true) 
							   if(current_special != -1)
							   if(has_black_grenade_equipped == true || has_green_grenade_equipped == true || has_molotov_grenade_equipped == true)
							   {	
							       sprite[ply_id].anim_state = WAIT;
								   sprite[ply_id].update = true;
								   sprite[ply_id].fire_target = -1;
								   DX_GRENADE_KEY=false;
		                           throw_grenade = true;
								   if(has_green_grenade_equipped == true)	
									   throw_grenade_type = THROW_GREEN_GRENADE;	
								   if(has_black_grenade_equipped == true)	
									   throw_grenade_type = THROW_BLACK_GRENADE;	
								   if(has_molotov_grenade_equipped == true)	
									   throw_grenade_type = THROW_MOLOTOV;	
							   } */

						//	   if(DX_TRAP_KEY == true) 
						//	   if(current_trap == -1)		    
                        //           Display_Message(ply_id, MSG_NOTRAP);
  
						/*	   if(DX_TRAP_KEY == true)
							   if(current_trap != -1)   
							   {	
							       sprite[ply_id].anim_state = WAIT; 
								   sprite[ply_id].update = true;
								   sprite[ply_id].fire_target = -1;

								   DX_TRAP_KEY=false;

		                           throw_grenade = true;
									
								   if( player_inv_value[current_trap] == TRAP_TYPE_DECOY)
									   throw_grenade_type = THROW_DECOY;
									
								   if( player_inv_value[current_trap] == TRAP_TYPE_MINE)
									   throw_grenade_type = THROW_MINE;

								   throw_grenade_amount = player_inv_value3[current_trap];

                                   same_trap_value = player_inv_value[current_trap]; 

                       			   player_inv[current_trap] = INV_NONE;
               
                       			   player_inv_value[current_trap]  = 0; 
                       			   player_inv_value1[current_trap] = 0;
                       			   player_inv_value2[current_trap] = 0;   			

								   current_trap=-1;

								   // Find next trap of same type to equip...
								   for(int i=0;i<16;i++)
								   if(player_inv[i] == INV_TRAP || player_inv[i] == INV_TRAP_A)
								   if(player_inv_value[i] == same_trap_value)
								   {
 									   current_trap = i; 
									   break;
								   }

								   // Find any trap to equip...
								   if(current_trap==-1)
								   for(int i=0;i<16;i++)
								   if(player_inv[i] == INV_TRAP || player_inv[i] == INV_TRAP_A)
								   {
 									   current_trap = i; 
									   break;
								   } 

							   }   */

							   if(DX_GRENADE_KEY == true)
								   DX_GRENADE_KEY = false;

							   if(DX_TRAP_KEY == true)
								   DX_TRAP_KEY = false;

							   if(DX_KNIFE == true)
								   DX_KNIFE = false; 

                           }
                     
                                               
                    }                 
                    
            }       
                                                                                         
            // Shooting code..  
			if(sta2_displaying_help == false)
			if(sta2_turn == TURN_PLAYER)   
            if(lock_player != true) 
            if(ply_dead == false)  
            if(ply_id != -1)  
			if(sprite[ply_id].score > 1)
			if(STA2_MODE == MODE_AIMING)       
			if(has_pistol_equipped == true 
			|| has_rifle_equipped == true 
			|| has_machine_equipped == true 
			|| has_shotgun_equipped == true 
			|| has_sniper_equipped == true
			|| has_mortar_equipped == true
			|| has_grenade_equipped == true)
            if(test == false)  
            if(!mode && (mouseleft == true || DX_SHOOT == true) )
            if( sprite[ply_id].status != OPEN_CUT  
            && sprite[ply_id].status != OPEN_STAMP 
			&& sprite[ply_id].status != OPEN_THROW
            && sprite[ply_id].status != STUNNED 
            && sprite[ply_id].status != FOOT_SHOT
			&& sprite[ply_id].status != MERCY
            && sprite[ply_id].status != FLATTENED
            && sprite[ply_id].status != LEVELING)       
            {                                
               
                    // Check against player...
                    if(sprite[ply_id].type == UNT)           
                    if(sprite[ply_id].score > 1                  
                    || sprite[ply_id].status == DIEING
                    || sprite[ply_id].status == MAN_DOWN)      
                    {      
 
						  if( ply_id != -1)                     
                          {    

							if(sprite[ply_id].value2 != -1)
								pack_id = sta2_squad[sprite[ply_id].value2].wp;

							if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
							if(sta2_pack[pack_id].extra_charge > 0)
							if(has_grenade_equipped == true && sta2_out_of_range == false)
							{
								 sta2_pack[pack_id].extra_charge--;

								 if(sta2_pack[pack_id].extra_charge <= 0)
									 sta2_pack[pack_id].extra_charge = 0;

							     throw_grenade_type = sta2_pack[pack_id].rank; // THROW_BLACK_GRENADE
								 throw_grenade = true; 
								 
								 sta2_only_defend = false;
								 sta2_only_pistol = false;

							}
						   else
                               throw_grenade = false;  
                           
                           on_collision=false; 
                           
						   if(has_grenade_equipped == false)
						   if(throw_grenade == false)
						   if(debug_active == false) 
                           if(lock_player != true)  
                           if(ply_dead == false) 
                           if(on_pickup == false)
                           if(player_in_water == false)
                           if(sprite[ply_id].status != FALLING)            
                           if(sprite[ply_id].status != STUNNED) 
                           if( (int)TimerGetTime() > sprite[ply_id].reload_timer )
                           if(sprite[ply_id].score > 0 && ply_dead == false) 
                           {  
                                
                               tarX = mouseX;       
                               tarY = mouseY;  
							         
                               if(stored_target != -1)
                               {
                                   tarX = sprite[stored_target].w + sprite[stored_target].box_width/2;    
                                   tarY = sprite[stored_target].z + sprite[stored_target].box_height/2; 
                               } 
                      
                               midX = sprite[ply_id].w + sprite[ply_id].box_width/2;
                               midY = sprite[ply_id].z + sprite[ply_id].box_height/2;
                               
							   if(stored_target != -1) 
							   if(has_grenade_equipped == false)  
							   if(has_rifle_equipped == false || sta2_shots_rifle < 1)
							   if(has_pistol_equipped == false || sta2_shots_pistol < 3)
							   if(has_shotgun_equipped == false || sta2_shots_shotgun < STA2_SHOTGUN_LIMIT)
							   if(has_machine_equipped == false || sta2_shots_machine < STA2_MACHINE_LIMIT)
							   if(has_sniper_equipped == false || sta2_shots_sniper < STA2_SNIPER_LIMIT)
							   if(has_mortar_equipped == false || sta2_shots_mortar < STA2_MORTAR_LIMIT)
                               {  

									if(has_rifle_equipped == true || has_machine_equipped == true 
									|| has_shotgun_equipped == true || has_sniper_equipped == true)
									{ 
										sta2_only_grenade = false; 
									}
									if(has_rifle_equipped == true || has_machine_equipped == true 
									|| has_shotgun_equipped == true || has_sniper_equipped == true || has_mortar_equipped == true)
									{ 
										sta2_only_defend = false;
										sta2_only_pistol = false;
									}
									if(has_pistol_equipped == true) 
									{
										sta2_only_defend = false;
										sta2_only_grenade = false;
									}


                                 if(has_shotgun_equipped)    
                                      TestSpriteToShootPly(ply_id, midX, midY, tarX, tarY, false, stored_target, f_rate1, true); 
                                 else
                                      TestSpriteToShootPly(ply_id, midX, midY, tarX, tarY, false, stored_target, f_rate1, false);   
                               }

                           }                            
           
                           sprite[ply_id].update = true;                                     
 
                           if(ply_id != -1)                                                                    
                           if( ( on_selected_man == BAD_MAN || on_selected_man == KICK_OBJ || on_selected_man == TALK_MAN)
                           && (int)TimerGetTime() > sprite[ply_id].reload_timer ) 
                           {                                                          

                            if(sprite[ply_id].fire_target != stored_target) 
                             if((int)TimerGetTime() > target_flash_timer)
                             {    
                               if(flash_on != -1)                     
                               {                 
                                   if(flash_on < TOTAL_NO_SPRITES)              
                                       sprite[flash_on].alpha = 1.0; 
                                   else
								   {
									   if( flash_on-TOTAL_NO_SPRITES >= 0)	
	                                       Fx[flash_on-TOTAL_NO_SPRITES].alpha = 1.0; 
								   }	
                                    
                               }       

                               // Flash the BAD_MAN   
                               if(stored_target != -1)  
                               {       
								   if(!CONTROLLER)
									flash_on = stored_target;    

                                   sprite[ply_id].fire_target = stored_target;
                               }

                               target_flash_timer = (int)TimerGetTime() + 25;
                               target_flash_mtimer = (int)TimerGetTime() + FLASH_OBJECT_TIME;
                                                            
                             }    
                                                         
                           near_sell = false;        
                           
                           
                           } // Move_the_guy == true 

                          } // Not VK_CONTROL  
                                                     
                        } // != sector != UNIT_B_COMMAND)
                        else 
						{
							if(ply_id != -1)
	                            sprite[ply_id].selected = false;
						}
                                                 
                stored_target = -1;      
                                    
              }                  
     
 
     
     
}
 

void Run_Mouse(int f_rate1)     
{

}

void Do_Player_Accel(int f_rate) 
{
	if(f_rate <= 0)
		f_rate = 1; 
      
	 if(ply_id != -1)    
	 if(sprite[ply_id].score > 1)
     {                    
         if( (KEY_FORWARD == true || KEY_BACKWARD == true || KEY_LEFTWARD == true  || KEY_RIGHTWARD == true && CONTROLLER == false) 
		 || (CONTROLLER == true && DX_LX != 0.0 || DX_LY != 0.0) )
         {                  
                               
             ply_accel+=0.000004f*(float)f_rate; // was 10
                          
             if(ply_accel > 1.5f)          
                 ply_accel = 1.5f;       
         }          
         else    
         {  

             ply_accel-=0.0000019f*(float)f_rate;
                   
             if(ply_accel < 0.0) 
             {  

			   	 keys_diffY=0.0f;
				 keys_diffX=0.0f;  
				 		  
                 ply_accel = 0.0f;

                 if(ply_id != -1)
				 {
	                 sprite[ply_id].moving  = false; 
	                 sprite[ply_id].turning = false; 
				 }
                 
                 if(reloading == false)
				 if(ply_id != -1)
                 if(sprite[ply_id].status != OPEN_FIRE && sprite[ply_id].status != OPEN_CUT && sprite[ply_id].status != OPEN_THROW && sprite[ply_id].status != AIMING)
                     ShotIdle(ply_id); 
					             
             }
         }  
     }   
	 else
		 ply_accel = 0.0f;

 	 
}

