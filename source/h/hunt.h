#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64 
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#endif 

extern void Refresh_Window();
extern bool New_FX(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int i_value, int i_type, int state, int linked_sprite, int tex_id, int i_value1, int i_value2, int i_value3);
extern void DrawPoint( float x, float y, float size);

#define HUNT_NONE 0
#define HUNT_FLY  1
#define HUNT_FALL 2
#define HUNT_WAIT 3
#define HUNT_GATOR_MOVE 4
#define HUNT_GATOR_FALL 5
#define HUNT_GATOR_WAIT 6
#define HUNT_CROW_FLY  7
#define HUNT_CROW_FALL 8
#define HUNT_CROW_WAIT 9
#define HUNT_YETI_MOVE 10 
#define HUNT_YETI_FALL 11
#define HUNT_YETI_WAIT 12
#define HUNT_YETI_UP   13 


bool Run_Hunt(int f_rate);

int sta2_hunt_reload_timer=0;
int sta2_collision_hunt_timer=0;

int sta2_hunt_timer = 0;
int sta2_shake_timer = 0;

int sta2_ducks_killed = 0;

bool Run_Hunt(int f_rate)
{  
	bool success=true;
	float testX=0.0f, testY=0.0f;  
	float midX=0.0f, midY=0.0f;
	float incY=0.0f;
	int rnd=0;
	int sta2_food_addition=0;

    // ******************************************************************************//
    //                               3-0  (HUNT GRASS)                               //
    // ******************************************************************************//

   // Title Screen Stuff...
//   if(next_scene == false)
   if(!mode)     
   if(episode == 3)      
   {        
	    
	    Set_Sprite(1, 1, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // CrossHair

		if(title_sequence == 0)       
		{      
			sprite[1].alpha = 0.0f;             
			sprite[2].alpha = 0.0f;	   
			  
			 hud[34].alpha = 1.0f; // Left arrow
			 hud[31].alpha = 1.0f; // Right arrow 

			 sta2_ducks_killed = 0;

			 sta2_picked_up_food = 0; 

			 sta2_hunt_reload_timer = 0;  
			 sta2_collision_hunt_timer=0;   

			 for(int j=0;j<no_sprites;j++)  
			 {
				    
				 if(sprite[j].type == FE_NEW) 
				 { 
					sprite[j].moving = false; 

					sprite[j].all_timer = 0;

					sprite[j].value3 = HUNT_WAIT;

					if(scene == 1)
						sprite[j].value3 = HUNT_GATOR_WAIT;

					if(scene == 3)
						sprite[j].value3 = HUNT_CROW_WAIT;

					if(scene == 4)
						sprite[j].value3 = HUNT_GATOR_WAIT;

					if(scene == 5)
						sprite[j].value3 = HUNT_YETI_WAIT;

					sprite[j].all_timer = 2000 + ((int)TimerGetTime() + rand()%1000);
				 } 

			 } 

			 sta2_hunt_timer = (int)TimerGetTime()+47000;
			         
			 title_sequence++;   
		}     
		       
		if(title_sequence == 1)     
		{  

			for(int j=0;j<no_sprites;j++) 
			{  
								 
				// Shake a tree...
				if(sprite[j].type == FE_NON || sprite[j].type == FE_OPT) 
				if(sprite[j].spotted == true)  
				{
					if((int)TimerGetTime() > sta2_shake_timer )
					{
						sprite[j].end_y += 1.0f; 
						sprite[j].x += (cos(sprite[j].end_y)/400);
   
						if(sprite[j].end_y >= 3.14f) 
							sprite[j].end_y = -3.14f;

						sta2_shake_timer = (int)TimerGetTime() + 10;
              
					} 

					if((int)TimerGetTime() > sprite[j].spotted_timer)
					{
						Set_Sprite(j, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // CrossHair
						sprite[j].x = sprite[j].end_x;
						sprite[j].spotted = false;
					}
				}

				// Duck hunt..
				if(sprite[j].type == FE_NEW || sprite[j].type == FE_FLIP)
				if(sprite[j].value3 == HUNT_WAIT)
				if((int)TimerGetTime() < sta2_hunt_timer - 3000)
				if((int)TimerGetTime() > sprite[j].all_timer) 
				{
					rnd = 10+rand()%80;
					incY = (sprite[0].width / 100.0f)*(float)rnd;

					testY = sprite[j].w - sprite[j].x;

					sprite[j].x = sprite[0].x + incY; 
					sprite[j].w = sprite[j].x + testY;

					// Direction left or right...
					if(rand()%2 == 0)
					{
						sprite[j].moving = false;
						sprite[j].type = FE_FLIP;
					}
					else
					{
						sprite[j].moving = true;
						sprite[j].type = FE_NEW;
					}

					// Altitude angle...
					if(rand()%2 == 0) 
						sprite[j].selected = false;
					else
						sprite[j].selected = true;

					sprite[j].alpha = 1.0f;

					sprite[j].value3 = HUNT_FLY;
					Set_Sprite(j, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // CrossHair
				}
				 
				if(sprite[j].type == FE_NEW || sprite[j].type == FE_FLIP) 
				if(sprite[j].value3 == HUNT_FALL)  
				{   
					   if((int)TimerGetTime() > target_flash_timer )
					   {
 
						 if(sprite[j].alpha == 0.0)         
							sprite[j].alpha = 1.0;     
						 else
							sprite[j].alpha = 0.0; 
   
						 target_flash_timer = (int)TimerGetTime() + 50;
              
					   }

					 temp_speed = 0.00100f*(float)f_rate;  

					 sprite[j].y -= temp_speed;   
					 sprite[j].z -= temp_speed;

					 if(sprite[j].y < (sprite[0].y - sprite[j].height*2))
					 {
						sprite[j].value3 = HUNT_WAIT;
						sprite[j].all_timer = (int)TimerGetTime() + rand()%1000;
					 }
					   
				}   
				 
				if(sprite[j].type == FE_NEW || sprite[j].type == FE_FLIP)  
				if(sprite[j].value3 == HUNT_FLY)  
				{
					 if(sprite[j].y < (sprite[0].y + sprite[0].height/3))
						 temp_speed = 0.00025f*(float)f_rate; 
					 else
						 temp_speed = 0.00040f*(float)f_rate; 
					  
					 if(sprite[j].value3 == HUNT_FLY)
					 {
						 sprite[j].z += temp_speed;
						 sprite[j].y += temp_speed;  
					 }
	  
					 if(sprite[j].selected == false)
						 temp_speed = 0.00040f*(float)f_rate;
					 else
						 temp_speed = 0.00080f*(float)f_rate; 

					 if(sprite[j].moving == false)  
						temp_speed *= -1;

					 sprite[j].x += temp_speed/2; 
					 sprite[j].w += temp_speed/2; 
					  
					 if(sprite[j].y > ((sprite[0].y + sprite[0].height) + sprite[j].height))
					 {

						testY = sprite[j].z - sprite[j].y;
						sprite[j].y = sprite[0].y - sprite[j].height;

						sprite[j].z = sprite[j].y + testY;

						sprite[j].value3 = HUNT_WAIT;
						sprite[j].all_timer = (int)TimerGetTime() + rand()%1000;

					 }   
					  
				}

				// End duck hunt.. 
 
				// Gator hunt..
				if(sprite[j].type == FE_NEW || sprite[j].type == FE_FLIP)
				if(sprite[j].value3 == HUNT_GATOR_WAIT)
				if((int)TimerGetTime() < sta2_hunt_timer - 3000)
				if((int)TimerGetTime() > sprite[j].all_timer) 
				{ 

					rnd=rand()%no_points; 

					testY = sprite[j].w - sprite[j].x;

					sprite[j].x = points[rnd].x;  
					sprite[j].w = sprite[j].x + testY; 

					testY = sprite[j].z - sprite[j].y;

					sprite[j].y = points[rnd].y; 
					sprite[j].z = sprite[j].y + testY;

					// Direction left or right...
					if(points[rnd].c2 == LEFT)
					{
						sprite[j].moving = false; 
						sprite[j].type = FE_FLIP;  
					} 
					else 
					{
						sprite[j].moving = true; 
						sprite[j].type = FE_NEW; 
					} 

					// Altitude angle...
					if(rand()%2 == 0) 
						sprite[j].selected = false;
					else     
						sprite[j].selected = true;

					sprite[j].tar_angle = points[points[rnd].score].x;

					sprite[j].alpha = 1.0;

					New_FX(sprite[j].x+sprite[j].width/2, sprite[j].y,  sprite[j].x-0.1f, sprite[j].y-0.05f, 39, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 3, GFX, 1.0f, 0, 0, FX_STATIC, -1, 6, 0, 0, -1);
		  				
					sprite[j].value3 = HUNT_GATOR_MOVE; 
					Set_Sprite(j, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // CrossHair

				}
				 
				if(sprite[j].type == FE_NEW || sprite[j].type == FE_FLIP)  
				if(sprite[j].value3 == HUNT_GATOR_MOVE) 
				{
					  
					if(scene == 4) // AREA_DESERT 
					{ 
					 if(sprite[j].selected == false)   
						temp_speed = 0.00085f*(float)f_rate; 
					 else
						temp_speed = 0.00065f*(float)f_rate; 
					}
					else
					{
					 if(sprite[j].selected == false) 
						temp_speed = 0.00055f*(float)f_rate; 
					 else
						temp_speed = 0.00045f*(float)f_rate; 
					}

					 if(sprite[j].moving == false)  
						temp_speed *= -1;

					 sprite[j].x += temp_speed/2;  
					 sprite[j].w += temp_speed/2; 
					  
					 if((sprite[j].x < sprite[j].tar_angle && sprite[j].moving == false) 
					 || (sprite[j].x > sprite[j].tar_angle && sprite[j].moving == true))
					 {

						testY = sprite[j].z - sprite[j].y; 
						sprite[j].y = sprite[0].y - sprite[j].height; 
						 
						sprite[j].z = sprite[j].y + testY;

						New_FX(sprite[j].x+sprite[j].width/2, sprite[j].y,  sprite[j].x-0.1f, sprite[j].y-0.05f, 39, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 3, GFX, 1.0f, 0, 0, FX_STATIC, -1, 6, 0, 0, -1);
		  				
						sprite[j].value3 = HUNT_GATOR_WAIT;
						sprite[j].all_timer = (int)TimerGetTime() + rand()%2000;

					 }  
					  
				}
				 
				if(sprite[j].type == FE_NEW || sprite[j].type == FE_FLIP) 
				if(sprite[j].value3 == HUNT_GATOR_FALL)  
				{
					if((int)TimerGetTime() > target_flash_timer )
					{
 
						 if(sprite[j].alpha == 0.0)         
							sprite[j].alpha = 1.0;     
						 else
							sprite[j].alpha = 0.0; 
   
						 target_flash_timer = (int)TimerGetTime() + 50;
              
					}
					if((int)TimerGetTime() > sprite[j].all_timer)
					{   

						sprite[j].value3 = HUNT_GATOR_WAIT;
						sprite[j].all_timer = (int)TimerGetTime() + rand()%2000;
					  
					}
				}

				// End of gator hunt...

				 
				// Crow hunt..
				if(sprite[j].type == FE_NEW || sprite[j].type == FE_FLIP)
				if(sprite[j].value3 == HUNT_CROW_WAIT)
				if((int)TimerGetTime() < sta2_hunt_timer - 3000)
				if((int)TimerGetTime() > sprite[j].all_timer) 
				{
					rnd = 10+rand()%80;
					incY = (sprite[0].width / 100.0f)*(float)rnd;

					testY = sprite[j].w - sprite[j].x;

					sprite[j].x = sprite[0].x + incY; 
					sprite[j].w = sprite[j].x + testY;

					testY = sprite[j].z - sprite[j].y;

					sprite[j].y = sprite[0].y + sprite[0].height + sprite[j].height; 
					sprite[j].z = sprite[j].y + testY;


					// Direction left or right...
					if(rand()%2 == 0)
					{
						sprite[j].moving = false;
						sprite[j].type = FE_FLIP;
					}
					else
					{
						sprite[j].moving = true;
						sprite[j].type = FE_NEW;
					}

					// Altitude angle...
					if(rand()%2 == 0) 
						sprite[j].selected = false;
					else
						sprite[j].selected = true;

					sprite[j].alpha = 1.0f;

					sprite[j].value3 = HUNT_CROW_FLY;
					Set_Sprite(j, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // CrossHair
				}
				 
				if(sprite[j].type == FE_NEW || sprite[j].type == FE_FLIP) 
				if(sprite[j].value3 == HUNT_CROW_FALL)  
				{   
					 temp_speed = 0.00100f*(float)f_rate;  

					 sprite[j].y -= temp_speed;   
					 sprite[j].z -= temp_speed;

					 if((int)TimerGetTime() > target_flash_timer )
					 {
 
						 if(sprite[j].alpha == 0.0)         
							sprite[j].alpha = 1.0;     
						 else
							sprite[j].alpha = 0.0; 
   
						 target_flash_timer = (int)TimerGetTime() + 50;
              
					 }
					 if(sprite[j].y < (sprite[0].y - sprite[j].height*2))
					 {
						sprite[j].value3 = HUNT_CROW_WAIT;
						sprite[j].all_timer = (int)TimerGetTime() + rand()%1000;
					 }
					  
				}
				 
				if(sprite[j].type == FE_NEW || sprite[j].type == FE_FLIP)  
				if(sprite[j].value3 == HUNT_CROW_FLY) 
				{
					  
					 if(sprite[j].y > ((sprite[0].y + sprite[0].height)-(sprite[0].height/3))   )
						 temp_speed = 0.00025f*(float)f_rate; 
					 else
						 temp_speed = 0.00040f*(float)f_rate;  

					 sprite[j].z -= temp_speed;
					 sprite[j].y -= temp_speed;  
	  
					 if(sprite[j].selected == false)
						 temp_speed = 0.00040f*(float)f_rate;
					 else
						 temp_speed = 0.00080f*(float)f_rate; 

					 if(sprite[j].moving == false)  
						temp_speed *= -1;

					 sprite[j].x += temp_speed/2;  
					 sprite[j].w += temp_speed/2; 
					  
					 if(sprite[j].y < (sprite[0].y - sprite[j].height*2)) 
					 {
						sprite[j].value3 = HUNT_CROW_WAIT;
						sprite[j].all_timer = (int)TimerGetTime() + rand()%1000;
					 } 

				}  

				// End crow hunt.. 

				// YETI hunt..
				if(sprite[j].type == FE_NEW || sprite[j].type == FE_FLIP)
				if(sprite[j].value3 == HUNT_YETI_WAIT)
				if((int)TimerGetTime() < sta2_hunt_timer - 3000)
				if((int)TimerGetTime() > sprite[j].all_timer) 
				{

					rnd=rand()%no_points;  

					testY = sprite[j].w - sprite[j].x; 

					sprite[j].x = points[rnd].x;   
					sprite[j].w = sprite[j].x + testY;  

					testY = sprite[j].z - sprite[j].y;

					sprite[j].y = points[rnd].y; 
					sprite[j].z = sprite[j].y + testY;    

					sprite[j].all_timer = (int)TimerGetTime() + 150;

					sprite[j].alpha = 1.0f;

					sprite[j].value3 = HUNT_YETI_UP;
					Set_Sprite(j, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // CrossHair
				} 
				 
				if(sprite[j].type == FE_NEW || sprite[j].type == FE_FLIP)  
				if(sprite[j].value3 == HUNT_YETI_UP) 
				if((int)TimerGetTime() > sprite[j].all_timer) 
				{
					Set_Sprite(j, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // CrossHair
					sprite[j].value3 = HUNT_YETI_MOVE;
					       
					// Altitude angle...
					if(rand()%2 == 0) 
						sprite[j].all_timer = (int)TimerGetTime() + 1500;  
					else
						sprite[j].all_timer = (int)TimerGetTime() + 1250;

					sprite[j].grab_switch = true;
				}

				if(sprite[j].type == FE_NEW || sprite[j].type == FE_FLIP)  
				if(sprite[j].value3 == HUNT_YETI_MOVE) 
				if((int)TimerGetTime() > sprite[j].all_timer) 
				{
					Set_Sprite(j, 2, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // CrossHair
					sprite[j].value3 = HUNT_YETI_WAIT;
					sprite[j].all_timer = (int)TimerGetTime() + rand()%1000;
					sprite[j].grab_switch = false;
				} 
				 
				if(sprite[j].type == FE_NEW || sprite[j].type == FE_FLIP) 
				if(sprite[j].value3 == HUNT_YETI_FALL)  
				{   
					if((int)TimerGetTime() > target_flash_timer ) 
					{
 
						 if(sprite[j].alpha == 0.0)         
							sprite[j].alpha = 1.0;     
						 else
							sprite[j].alpha = 0.0; 
   
						 target_flash_timer = (int)TimerGetTime() + 50;
              
					}
					if((int)TimerGetTime() > sprite[j].all_timer) 
					{
						sprite[j].grab_switch = false;
						sprite[j].value3 = HUNT_YETI_WAIT;
						sprite[j].all_timer = (int)TimerGetTime() + rand()%1000;
					}
					    
				}


				// End yeti hunt... 
 
				// Run collision checks...
				if((int)TimerGetTime() > sta2_collision_hunt_timer)
				{

					for(int i=0;i<no_fx;i++)     
					{ 

						midX = Fx[i].x + Fx[i].width/2;
						midY = Fx[i].y + Fx[i].height/2; 
					 
						// Check to see if hit anything...  
						if(Fx[i].turn_off == false)
						if(Fx[i].sector == FX_HUNT_BULLET)     
						{         
							 
							for(int j=0;j<no_sprites;j++)
							if(sprite[j].grab_switch == true)   
							{ 

								if(sprite[j].value3  == HUNT_FLY || sprite[j].value3  == HUNT_GATOR_MOVE
								|| sprite[j].value3  == HUNT_CROW_FLY || sprite[j].value3  == HUNT_YETI_MOVE
								|| sprite[j].type == FE_OPT || sprite[j].type == NON)
								if(( midX < (sprite[j].w + sprite[j].box_width) )
								&&( midX > sprite[j].w)                            
								&&( midY < (sprite[j].z + sprite[j].box_height) )
								&&( midY > sprite[j].z))   
								{   
									 
								//	d_pointX = Fx[i].w-0.05f;   
								//	d_pointY = Fx[i].z;

									if(sprite[j].alpha == 1.0f)
									if(sprite[j].type == FE_NEW || sprite[j].type == FE_FLIP) 
									{ 
										 
										if(( (Fx[i].w-0.05f) < (sprite[j].w + sprite[j].box_width) )
										&&( (Fx[i].w-0.05f) > sprite[j].w)                            
										&&( Fx[i].z < (sprite[j].z + sprite[j].box_height) )
										&&( Fx[i].z > sprite[j].z))  
										{        
											     
											Set_Sprite(j, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // CrossHair

											if(scene == 3) // AREA_FARM
												crow1_sfx = true; 

											if(scene == 0 || scene == 2) // AREA_GRASS - AREA_FOREST
											{
												sta2_ducks_killed++;

												if(sta2_ducks_killed==10)
												{
													#if IS_FULL_STEAM == 1 

													if(STEAM_ACTIVE == true)  
													if(IS_FULL_GAME == true)
													if (g_SteamAchievements)
													{
														g_SteamAchievements->SetAchievement("STA2_MEDAL_7"); // Kill 10 ducks...

														if(sta2_globals[GLOBAL_STA2_MEDAL_7] == GLOBALS_RESET)
														{
															sta2_globals[GLOBAL_STA2_MEDAL_7] = GLOBALS_ACTIVE;
															firework_sfx = true;

														}
													}

													#endif
												}

												crow1_sfx = true; 
											}
											 
											if(scene == 5) // AREA_SNOW
												crow1_sfx = true; 
											  
											if(scene == 0) // AREA_GRASS 
												sta2_food_addition += 8+rand()%6;   
											if(scene == 1) // AREA_SWAMP
												sta2_food_addition += 5+rand()%5;
											if(scene == 2) // AREA_FOREST
												sta2_food_addition += 8+rand()%6;  
											if(scene == 3) // AREA_FARM
												sta2_food_addition += 5+rand()%7;  
											if(scene == 4) // AREA_DESERT
												sta2_food_addition += 5+rand()%5;
											if(scene == 5) // AREA_SNOW
												sta2_food_addition += 5+rand()%5;

											sta2_picked_up_food += sta2_food_addition;

											DamageNumber( j, sta2_food_addition, STA2_DAMAGE_FOOD );
											
											sprite[j].value3 = HUNT_FALL;

											if(scene == 3) 
												sprite[j].value3 = HUNT_CROW_FALL;

											if(scene == 1)   
											{ 
												sprite[j].value3 = HUNT_GATOR_FALL;
												sprite[j].all_timer = (int)TimerGetTime() + 1000;
											}
											if(scene == 4)  
											{
												sprite[j].value3 = HUNT_GATOR_FALL; 
												sprite[j].all_timer = (int)TimerGetTime() + 1000;
											}
											if(scene == 5)  
											{
												Set_Sprite(j, 2, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // CrossHair
												sprite[j].value3 = HUNT_YETI_FALL;
												sprite[j].all_timer = (int)TimerGetTime() + 1000;
											}

											Fx[i].turn_off = true;
										}
										 
									}
									else 
									{
										ric_sfx = true;  
										Fx[i].turn_off = true;

										New_FX(midX-0.05f, midY-0.05f,  mouseX, mouseY, 26, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, Fx[i].priority, GFX, 1.0f, 0, 0, FX_STATIC, -1, 6, 0, 0, -1); 

										// Add a shake effect...
										sprite[j].end_y = 0.0f;
										sprite[j].end_x = sprite[j].x;
										sprite[j].spotted = true;
										sprite[j].spotted_timer = (int)TimerGetTime() + 500;

										if(sprite[j].type == FE_OPT)
											Set_Sprite(j, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // CrossHair

									}

									break;
								}
							}
						}  
						 
					} // no_fx

					sta2_collision_hunt_timer = (int)TimerGetTime()+2;

				} // Run collision checks...

			} // no_sprites 

			if(sprite[3].anim_state == WAIT)
			{
				Set_Sprite(3, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // CrossHair
			}
			 
			sprite[3].x = mouseX - 0.2f;  
			sprite[3].y = sprite[0].y - (((sprite[0].y+sprite[0].height)-mouseY)/3);

			if(next_scene == false)
			if((int)TimerGetTime() > sta2_hunt_reload_timer) 
			if(mouseleft == true)  
			{  

				Set_Sprite(3, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // CrossHair

				sta2_hunt_reload_timer = (int)TimerGetTime() + 1000;
				sniper_sfx = true; 
				mouseleft = false;   
				 
				midX = mouseX - 0.1f;   
				midY = sprite[0].y - 0.1f; 

				New_FX(midX, midY,  mouseX, mouseY, 0, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 1, GFX, 1.0f, 0, 0, FX_HUNT_BULLET, -1, 7, 0, 0, -1); 

			}	

			if(fade > 0.7)
			if( (mouseX > (-camX) + 0.4f) || (mouseX < (-camX) - 0.4f) ) 
			{
			 
				sprite[1].alpha = 0.0f; 
				sprite[2].alpha = 0.0f;

				hud[31].alpha = 1.0f;
				hud[34].alpha = 1.0f;


				sta2_globalX = -(camX) - mouseX; // -0.7 - 0.7

				sta2_globalX /= -0.8f;         
		 
				if(sta2_globalX > 1.0f)     
					sta2_globalX = 1.0f;    
		 
				if(sta2_globalX < -1.0f) 
					sta2_globalX = -1.0f;
				 
				camX -= (0.0018f*sta2_globalX)*(float)f_rate;

				if((-camX > sprite[0].x + 0.785f ) && (-camX < (sprite[0].x + sprite[0].width) - 0.785f ))
				{
					mouseX += (0.0018f*sta2_globalX)*(float)f_rate;
					sprite[1].x += (0.0018f*sta2_globalX)*(float)f_rate; 
					sprite[2].x += (0.0018f*sta2_globalX)*(float)f_rate;
				}       

			}    

		    if(-camX < sprite[0].x + 0.785f )
			{ 
			   camX = -(sprite[0].x + 0.785f );  
			   sprite[1].alpha = 0.0f; 
			   hud[34].alpha = 0.0f;
			}

		    if(-camX > (sprite[0].x + sprite[0].width) - 0.785f ) 
			{
			   camX = -((sprite[0].x + sprite[0].width) - 0.785f);
			   sprite[2].alpha = 0.0f;
			   hud[31].alpha = 0.0f;
			} 
			 
			// End hunt after time limit...
			if((int)TimerGetTime() > sta2_hunt_timer)
			{
				sta2_next_episode = 1;   
				sta2_next_scene   = 2; 
				
				next_scene = true; 

				sta2_next_event = EVENT_HUNT_RESULT;

			}         

		} 

   }   


	return(success);

} 
