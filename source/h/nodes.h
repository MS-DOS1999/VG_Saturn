
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN   
 
#include <windows.h> 
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>			// Header File For Standard Input/Output
#include <gl\gl.h>   
#include "globals.h" 
 
extern void Set_Heading(int loop, float x1, float y1, bool hulk_ladder);
extern void Rank_Timer(int index, int status);
extern void Set_Sprite(int id, int anim, int state, int hud_or_sprite, bool reset);
extern void Generate_Object_Collision(int loop, bool col_test);
extern void Reset_Build_Types(int loop);
extern void Animation_System(int loop, bool bullet_check, bool interrupt, bool pain_anim, bool fire);
extern void Calculate_Bullets();
extern void Calculate_Lifebar();
extern int  Generate_Item(int type, int rank);
extern bool New_FX(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int i_value, int i_type, int state, int linked_sprite, int tex_id, int i_value1, int i_value2, int i_value3);
extern void Spawn_Pickup(int index, int type);
extern void Calculate_Exp(int index, int experience);
extern bool Spawn_A_Guy(int number_of_dudes, int best_point, bool buddy, int trap, int sprite_point, int goto_point);
extern void Calculate_Buddy(bool turn_on, int slot, int index);
extern int Get_Tile_Index(float x, float y);
extern void Display_Message(int index, int message);
extern void Hud_Face_Unit(int loop, int slot); 
extern void Reload_Gun();
extern void Bit_Shift( int the_value1, int bit_to_shift, int bit_value);
extern int Get_Bit_Shift( int the_value1, int bit_to_shift);  
extern bool Has_This_Item(int type, int value);
extern void Turn_On_Lights();
extern void Create_Dust_Effect(float x, float y, bool is_shotgun, bool is_an_offset, int f_rate);
extern void Create_Crate_Effect(int guy_shot);
extern void Throw_Grenade(int index, int target); 
extern void Turn_Unit(int loop, int f_rate);    
extern void Create_Blood_Effect(int guy_shot); 
extern void Raise_Alarm();
extern void Create_Gibs_Effect(int index, bool bones, int type);
extern void Bomb_Run(float bomb_tar_x, float bomb_tar_y, int the_guy, int f_rate);
extern void Create_Fire_Point(float x, float y);
extern void Init_Player();
extern bool Remove_FX(int id, bool test); 
extern void Surround_Sound(int sprite_index, int sound_type, float x, float y);
extern void Create_Muzzle_Effect(int loop);
extern int GetAccuracy(int loop, int target);
extern void DamageNumber( int loop, int damage, int is_blue ); 

void New_Healthbar(int index, int quick_display);
bool TestSpriteToShoot(int no_test, float x1, float y1, float x2, float y2, bool hulk, int target_id, int f_rate);
bool TestSpriteToShootPly(int no_test, float x1, float y1, float x2, float y2, bool hulk, int target_id, int f_rate, bool shotgun_attack);
float Node_Distance(float x1, float y1, float x2, float y2);
bool Man_Shot(int guy_status, int guy_shot, int guy_shooting, int bullet_type, int f_rate);
int Is_Guy_In_Sight(float my_angle, float target_angle); 
void Test_sprite_to_trigger(int loop);
void Lay_Mine(float midX, float midY, int loop);
bool Mine_Check(int row_x, int row_y);
void Mine_Triggered(int guys_index, int mine_index, int loop);
int Convert_Angle_To_Dir(float my_angle);
int New_Sprite(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int sideways, int upways, int state, int linked_sprite, int tex_id, int a_global, float angle, int p_type, int goto_point);
bool Build_Man_Check(int loop, int x, int y, int build_type, bool row_check);
void ShotIdle(int loop);
bool Is_Guy_In_Range(int loop, int target, float range);
int Convert_Dir_To_Angle(int loop, int direction);
void Test_sprite_to_Obj(int loop, int target);
void Knock_Back(int guy_shooting, int guy_shot, int f_rate);
void Test_Sprite_to_Fx(int loop, int f_rate);
void Test_Fx_to_Fx(int loop, int f_rate);
void Remove_Item(int item_type, int item_value, int item_value1, bool remove_all);
bool Is_Grey_Area(float my_angle);
void Start_Game();
float Convert_Dir_To_Angle1(int direction);
int Get_Number_Of_Item(int item_type, int item_value, int item_value1, bool remove_all);
void Run_Gibs(int guy_shooting, int guy_shot, int f_rate);
void Turn_On_Torch(int index, bool on_off);
void Shot_Missed(int loop, int no_test, float x2, float y2);
void Calculate_Arcade_Score(int index, int guy_status, int torso_targeted);
 
void ShotIdle(int loop) 
{ 
    float mid_x=0.0,mid_y=0.0;
    float tar_x=0.0,tar_y=0.0;    
    int temp_row_x=0; 
    int temp_row_y=0;
    int temp_row_x1=0;
    int temp_row_y1=0;    
    int index=0;
    int value=0;      
    int rnd=0;   
	bool skip_this = false;   
 
	if(loop < 0) 
		return;     
	 
    // Needs sorting out...    
    value = REGEN_START;  

    if(lock_player == false || loop != ply_id)
    //if(sprite[loop].reached_node == -1) // Do we need this? 
    if((sprite[loop].score > 0 && sprite[loop].linked_sprite != player_type) || (sprite[loop].score > 1 && sprite[loop].linked_sprite == player_type)) 
    if(sprite[loop].status != SPECIAL || special_reacts == true) 
    if(sprite[loop].status != FALLING)    
    {
        sprite[loop].anim_state = WAIT;   
                   
        sprite[loop].status = IDLE;      
        sprite[loop].update = true; 
        sprite[loop].moving = false; // Hack?
        sprite[loop].ai_timer = (int)TimerGetTime() + 500;
        
    /*    if(loop != ply_id)   
        if(sprite[loop].group_id >= 0)
		if(sprite[sprite[loop].group_id].alpha != 0.0)
		if(sprite[sprite[loop].group_id].status != DEATH_READY)
        if(sprite[sprite[loop].group_id].score <= 0 
		|| sprite[sprite[loop].group_id].status == MERCY 
		|| sprite[sprite[loop].group_id].status == MERCY1)
        if(sprite[loop].on_ladder == false)   
        if(sprite[loop].ai_brain == BRAIN_HEALING)
        {
		 	sprite[loop].all_timer = (int)TimerGetTime() + 750;
			sprite[loop].ai_timer = (int)TimerGetTime() + 750;					 
		 	sprite[loop].idle_type = IDLE_HEAL; 
			        
		}*/
        
    }      
        
}


float Node_Distance(float x1, float y1, float x2, float y2)
{
        
      float length=0.0f;  
      float x_value=0.0;
      float y_value=0.0;
      
 /*     if( x1 > x2)
          x_value = x1 - x2; 
      else
          x_value = x2 - x1;
      
      if( y1 > y2) 
          y_value = y1 - y2;
      else
          y_value = y2 - y1;            

      length = sqrt( (x_value * x_value) + (y_value * y_value) );*/
            
      if( x1 > x2)
          x_value = x1 - x2;
      else
          x_value = x2 - x1;
       
      if( y1 > y2) 
          y_value = y1 - y2;
      else
          y_value = y2 - y1;           
      
      x_value += y_value; 
       
      length = x_value / 2; 
      
      // If you want the 3-d equation 
//      length *= 1.41421;      
       
      return length;  
           
}

bool TestSpriteToShootPly(int no_test, float x1, float y1, float x2, float y2, bool hulk, int target_id, int f_rate, bool shotgun_attack)
{ 
     
    // hulk is for knifing
     
    bool test_success=false;  
    
    float my_x=0.0f, my_y=0.0f;
    float angle=0.0f, deltax=0.0f, deltay=0.0f;
    float mid_x=0.0f, mid_y =0.0f;
    float tar_x=0.0f, tar_y =0.0f;
    float step=0.0f, distance=0.0f; 
    float off_set=0.05f;
	float box_offset=0.01f;
    int iterations=0;
    int loop=0; 
    int temp_row=0;
    int temp_r_x=0; 
    int temp_r_y=0;
    int row_x=0;
    int row_y=0;
    int the_row=0;
    bool a_switch=false;
    bool go_ahead=true;
    bool hit_cover=false;
    int rnd=0;
    int rnd1=0;
    int accuracy_test=0;  
    int enemy_to_hit_ratio=0;
    int stored_col=0;
    int alert_guy=0;
    bool object_attack_on = false;
    int the_count=0; 
    int torso_targeted=0;
    int tens=0;
    int zeros=0;
    int player_clip = 0; 
	int last_shot = -1;
    bool throwing_grenade=false;
	bool hit_something=false;
	int no_of_blocks_hit=0;
	bool shot_wheat=false;
	bool is_mortar = false;
	int pack_id = -1;

	if(f_rate <= 0)
	   f_rate = 1; 
    
    double_shot = false;      
     
    if(hulk == false) // Slash code.. 
    if(ply_id != -1)    
    if(no_test != -1) 
    if( (no_test == ply_id && player_type == p_server))
    {              
		 
        if(ply_id != -1) 
        {   
                    
            alert_enemies = true;
            noise_type = LOUD_NOISE;                  
                    
            noise_x = sprite[ply_id].w+sprite[ply_id].box_width/2;                        
            noise_y = sprite[ply_id].z+sprite[ply_id].box_height/2;   
        }
		 
    }   
    
    if(go_ahead == true)
	if(no_test != -1) 
    if(ply_id != -1)   
    {                                                 
        Set_Heading(ply_id, x2, y2, false);   
    
        sprite[ply_id].angle = sprite[ply_id].tar_angle;
        
        tar_x = sprite[no_test].x+sprite[no_test].width/2;  
        tar_y = sprite[no_test].y+sprite[no_test].height/2;

	//	Create_Muzzle_Effect(ply_id);

        if(hulk == false)  
        {
          if( has_rifle_equipped == true) // was has_shotgun_equipped
              New_FX(tar_x, tar_y,  sprite[no_test].w, sprite[no_test].z, 0, LOOP, 0.025f, 0.025f, 0.025f, 0.025f, 0, GFX, 1.0f, 0, 0, FX_SHELL, no_test, 8, 0, 0, -1); 
          else
              New_FX(tar_x, tar_y,  sprite[no_test].w, sprite[no_test].z, 0, LOOP, 0.025f, 0.025f, 0.025f, 0.025f, 0, GFX, 1.0f, 0, 0, FX_SHELL, no_test, 8, 0, 0, -1); 
        } 
            
    }                          
        
    if(go_ahead == true) 
	if(no_test != -1)    
    {
                 
        if(hulk == false)      
		{ 
			if(sta2_turn == TURN_PLAYER && sprite[no_test].linked_sprite == player_type)
				sprite[no_test].return_fire = false;

            sprite[no_test].status = OPEN_FIRE; 

			DX_SHOOT=false;

			if(has_pistol_equipped)
			{ 
				#if INCLDUE_360_CONTROLLER == 1
					VIBRATE_LEFT(12000, 150); 
					VIBRATE_RIGHT(12000, 150);
				#endif
			}
			if(has_rifle_equipped) 
			{
				#if INCLDUE_360_CONTROLLER == 1
					VIBRATE_LEFT(24000, 150); 
					VIBRATE_RIGHT(24000, 150);
				#endif
			}
		}
            
        if(hulk == true)   
            sprite[no_test].status = OPEN_CUT;

        sprite[no_test].anim_state = WAIT;
               
        sprite[no_test].update = true;  
		
		if(has_machine_equipped == false)
			mouseleft = false;

    }
    
   // Play firing SFX... 
   if(hulk == false)
   if(go_ahead == true)
   if(no_test != -1) 
   if(ply_id != -1)
   if(no_test == ply_id)
   { 
  
       shot_fired = SHOT_NONE;
                                                                          
           if(has_pistol_equipped)
           {
			   Surround_Sound(p1_id, SFX_PISTOL, x2, y2); 
			   sta2_shots_pistol++;
			   sta2_shot_fired_gun = FIRED_PISTOL; 
           }
                
           if(has_rifle_equipped)  
           {
			   sniper_sfx = true;
//			   Surround_Sound(p1_id, SFX_RIFLE, x2, y2); 	
			   sta2_shots_rifle++;
			   sta2_shot_fired_gun = FIRED_RIFLE;   
           }
                            
           if(has_shotgun_equipped)
           {
                 shotgun_sfx = true; 
				 sta2_shots_shotgun++;
				 sta2_shot_fired_gun = FIRED_SHOTGUN;   
           //    Surround_Sound(PING_SFX, SFX_SHOTGUN, -1, x2, y2);
           }                 
           if(has_machine_equipped)
           {
				 mount_sfx = true; 
				 sta2_shots_machine++;
				 sta2_shot_fired_gun = FIRED_MACHINE;  
            //   Surround_Sound(PING_SFX, SFX_MACHINE, -1, x2, y2);
           }

           if(has_sniper_equipped)  
           {
			   sniperply_sfx = true; 
			   sta2_shots_sniper++;
			   sta2_shot_fired_gun = FIRED_SNIPER; 
           }  
                
           if(has_mortar_equipped)  
           {
			   is_mortar = true;
			   splash_sfx = true; 	
			   sta2_shots_mortar++;
			   sta2_shot_fired_gun = FIRED_MORTAR;   
           }
                                      
           if(has_grenade_equipped)
           {
               death_sfx = true;   
           } 

   }
   
   if(hulk == true)
   if(go_ahead == true)       
   if(no_test != -1)  
   if(ply_id != -1) 
   if(no_test == ply_id)
   { 
       chop_sfx = true; 
   }
   
    if(go_ahead == true)           
    if(no_test != -1) 
    if(throwing_grenade == false)            
        Rank_Timer(no_test, sprite[no_test].status); 
    
    my_x = x1;
    my_y = y1;

    distance = Node_Distance1(x1, y1, x2, y2);
        
    angle = atan2(y2 - y1,x2 - x1);      
        
    if(hulk == true) // Knifing code
    {    
            
        deltax = cos(angle);     
        deltay = sin(angle);  
                
        deltax *= 0.075f;   
        deltay *= 0.075f; 
        
        x2 = x1 + deltax; 
        y2 = y1 + deltay;

        distance = Node_Distance1(x1, y1, x2, y2);
        
        off_set = 0.1f;   
                    
    }
    
    deltax = cos(angle);     
    deltay = sin(angle);  
         
    deltax *= (float)LINE_OF_SIGHT;    
    deltay *= (float)LINE_OF_SIGHT;
   
    step = Node_Distance1(x1, y1, x1+deltax, y1+deltay);
    
    if( step != 0)
        iterations = (int)(distance / step);
      
    if(iterations < 0)  
        iterations = 0;    

    my_x -= deltax; // Start at exact player/sprite co-ordinates...
    my_y -= deltay; // Start at exact player/sprite co-ordinates...

	if(is_mortar == true)
	if(no_test != -1)
	{ 
		pack_id = sta2_squad[sprite[no_test].value2].wp;
		Shell_Landed( x2, y2, no_test, f_rate, INV_MORTAR, sta2_pack[pack_id].rank);
		go_ahead = false;
	}

    if(go_ahead == true) 
    for(int j = 0; j <= iterations; j++) 
    { 
        
        my_x += deltax; // Which is the mid_x
        my_y += deltay; // Which is the mid_y
          
       row_x = (int)((my_x + map_startX)*10);    
       row_y = (int)((my_y + map_startY)*10);        
     
       the_row = (row_y*MAP_HEIGHT)+row_x;    

	   if(the_row < 0)
	       break;       
  
/*       if(tiles[the_row] == 0 && in_dungeon == true && !ARCADE) // For hitting the black darkness
       {
           mid_x = my_x;     
           mid_y = my_y;                
           
       //    New_FX(mid_x-0.070f, mid_y-0.06f,  sprite[ply_id].w, sprite[ply_id].z, 90, PLAY, 0.15f, 0.2f, 0.15f, 0.2f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);// Splat effect
           hit_cover = true; 
		   hit_something=true;	
           ric2_sfx = true;  
           break;     
       }   */

       if(map_col[the_row] == 1) // (|| map_col[the_row] == 7 && Level != LVL_SUB_PEN)
       {

			no_of_blocks_hit=0; 

			box_offset = 0.04f;  
          
       		row_x = (int)((my_x + box_offset + map_startX)*10);    
       		row_y = (int)((my_y + box_offset + map_startY)*10);        
       		the_row = (row_y*MAP_HEIGHT)+row_x;  
			if(the_row < 0)break;  
			if(map_col[the_row] == 1 ) //  || (map_col[the_row] == 7 && Level != LVL_SUB_PEN)
				no_of_blocks_hit++;
          
       		row_x = (int)((my_x - box_offset + map_startX)*10);    
       		row_y = (int)((my_y - box_offset + map_startY)*10);        
       		the_row = (row_y*MAP_HEIGHT)+row_x;  
			if(the_row < 0)break;  
			if(map_col[the_row] == 1 ) //  || (map_col[the_row] == 7 && Level != LVL_SUB_PEN)
				no_of_blocks_hit++;
           
       		row_x = (int)((my_x + box_offset + map_startX)*10);    
       		row_y = (int)((my_y - box_offset + map_startY)*10);        
       		the_row = (row_y*MAP_HEIGHT)+row_x;  
			if(the_row < 0)break;  
			if(map_col[the_row] == 1 )
				no_of_blocks_hit++; 
          
       		row_x = (int)((my_x - box_offset + map_startX)*10);     
       		row_y = (int)((my_y + box_offset + map_startY)*10);        
       		the_row = (row_y*MAP_HEIGHT)+row_x;  
			if(the_row < 0)break;  
			if(map_col[the_row] == 1 )
				no_of_blocks_hit++;

			if(ply_id != -1)
			if( no_of_blocks_hit >= 4)
			{ 
				 
				if(map_cover[the_row] != STA2_GRASS_COVER && map_cover[the_row] != STA2_ROCK_COVER)
				{
					map_cover[the_row] -= 25; 

					if(map_cover[the_row] <= 0)
						map_cover[the_row] = 10;
				}

            	mid_x = my_x;       
            	mid_y = my_y;        

				New_FX(mid_x-0.05f, mid_y-0.05f,  mid_x-0.05f,  mid_y-0.05f, 26, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 6, 0, 0, -1);// Spark effect
				ric2_sfx = true;  

            	hit_cover = true; 
				hit_something=true;
           
            	break;
			}


       }   

       // Object collision detection    
	   if(is_mortar == false)
       if(test_success == false)       
       for(int i=0;i<new_no_sprites;i++) 
       {        
                       
           loop = var5[i];     
   
           if(loop >= 0 && loop < TOTAL_NO_SPRITES)
           { 
                   
           mid_x = sprite[loop].w+sprite[loop].box_width/2; 
           mid_y = sprite[loop].z+sprite[loop].box_height/2;
			
		   if(shotgun_attack == true)
			   off_set=0.3f;

           if(no_test != -1)      
		   if(last_shot != loop)     
           if(sprite[loop].type == UNT || sprite[loop].type == BAG)     
           if( no_test != loop && test_success == false)
           if(sprite[loop].mouseover == false)
           if(sprite[loop].status != TIED)
           if(sprite[loop].grab_switch == true)
           if(sprite[loop].score > 0  ) // || (sprite[loop].type == UNT && stored_target != -1) // For splats 
           if(sprite[no_test].linked_sprite != sprite[loop].linked_sprite)
           if(sprite[loop].turn_off == false)
           if(sprite[loop].onDeath_action != TANK_TOP)
           if(( my_x < mid_x + off_set ) 
           &&( my_x > mid_x - off_set)                              
           &&( my_y < mid_y + off_set)  
           &&( my_y > mid_y - off_set) )            
           {      
               // Check accuracy to see if it hit... 

			    if(has_machine_equipped)
				{
			        sta2_machinegun_index = loop;
                    test_success = true;
					sta2_mg_timer = 0;
					sta2_mg_fired = 0;
			   	    break; 
			    } 
				 
           		rnd = rand()%100;         
				 
				accuracy_test = GetAccuracy(ply_id, loop);

			    if(rnd <= accuracy_test || (distance <= KNIFE_RANGE && sprite[no_test].sector != UNIT_DOG) )
			    { 

                	if(sprite[loop].score > 0) 
                	{    

                	 	 Man_Shot(sprite[no_test].status, loop, no_test, BULLET_NONE, f_rate); 

						 targeted = TARGET_TORSO;
                	}
              		else      
               	    {  
                    
                   	/*	if(loop != ply_id)      
                   		if(sprite[loop].sector != UNIT_MORTAR)
                   		if(sprite[loop].sector != UNIT_BOMBER || sprite[loop].onDeath_action != TURRET)
                       		Knock_Back(no_test, loop, f_rate);*/
                       
                   		Run_Gibs(no_test, loop, f_rate);
                   
                	}
				}
				else  
				{ 
			    	if(hit_cover == false)   
					{
				    	Create_Dust_Effect(x2, y2, true, false, f_rate); 
						DamageNumber(loop, -1, STA2_DAMAGE_MISS );
 					}
				} 

			   last_shot = loop;
               hit_something=true;

			   if(shotgun_attack == false)
               if(hulk == false && has_rifle_equipped == false) // Shots go through multiple units...
			   {
                   test_success = true;
			   	   break;
			   } 
                   
           }  
   
  
           
           } // if(loop < TOTAL_NO_SPRITES)  

     	} // new_no_sprites
       
    }  // ITERATIONS  
   
	if(is_mortar == false)
    if(hit_cover == false)
    if(shotgun_attack == true)   
    {
       
        Create_Dust_Effect(x2, y2, true, false, f_rate); 
        
        Create_Dust_Effect(x2, y2, true, false, f_rate); 
        
        if(no_test == ply_id) 
        if(st_gas >= 2)
            Create_Dust_Effect(x2, y2, true, false, f_rate);
            
        if(no_test == ply_id)    
        if(st_gas == 3)
            Create_Dust_Effect(x2, y2, true, false, f_rate);
      
    }    
    
	if(is_mortar == false)
    if(hit_cover == false)
    if(hulk == false)
    if(test_success == false)  
    if(ply_id != -1)
    {
		if(stored_target == -1)
			Create_Dust_Effect(x2, y2, false, true, f_rate);
    }    

     return 0;
}


bool TestSpriteToShoot(int no_test, float x1, float y1, float x2, float y2, bool hulk, int target_id, int f_rate)
{ 
     
    bool test_success=false;  
    
    float x=0.0f, y=0.0f;
    float angle=0.0f, deltax=0.0f, deltay=0.0f;
    float mid_x=0.0f, mid_y =0.0f;
    float tar_x=0.0f, tar_y =0.0f;
    float step=0, distance=0.0f; 
    int iterations=0;
    int loop=0; 
    int temp_row=0;
    int temp_r_x=0; 
    int temp_r_y=0;
    int row_x=0;
    int row_y=0;
    int the_row=0;
    bool a_switch=false;
    bool go_ahead=true;
    bool hit_cover=false;
    int rnd=0;
    int rnd1=0;
    int accuracy_test=0;  
    int enemy_to_hit_ratio=0;
    int stored_col=0;
    int alert_guy=0;
    bool object_attack_on = false;
    int the_count=0; 
    int torso_targeted=0;
    int tens=0;
    int zeros=0;
    int player_clip = 0;  
    bool throwing_grenade=false;
	float my_x=0.0f, my_y=0.0f;
	bool is_mortar=false;

	 if(f_rate <= 0)
	     f_rate = 1;  

	 if(no_test < 0)
		 return(false);
    
    double_shot = false;
     
    x = x1;
    y = y1;

	if(no_test >= 0)
	{
	    my_x = sprite[no_test].w+sprite[no_test].box_width/2; 
	    my_y = sprite[no_test].z+sprite[no_test].box_height/2;

		if(sprite[no_test].sector == UNIT_MORTAR)
			is_mortar = true;
	} 
    
    // Turn off dudes collision
            
    row_x = (int)((mid_x + map_startX)*10);    
    row_y = (int)((mid_y + map_startY)*10);   
    
    the_row = (row_y*MAP_HEIGHT)+row_x;
 
    distance = Node_Distance1(x1, y1, x2, y2);   

    if(object_attack_on == false)
        the_count = player_counter;
    else
        the_count = door_counter; 
              
    angle = atan2(y2 - y1,x2 - x1);     
    
    deltax = cos(angle);    
    deltay = sin(angle);  
        
    deltax *= (float)LINE_OF_SIGHT;    
    deltay *= (float)LINE_OF_SIGHT; 
        
    step = Node_Distance1(x1, y1, x1+deltax, y1+deltay); // Was Node_Distance
    
    if( step != 0)
        iterations = (int)(distance / step);
    
//    iterations -= 1;
      
    if(iterations < 0)   
        iterations = 0; 
    
    x = x1;
    y = y1;

	if(is_mortar == true)
	if(no_test != -1)
	{ 
		Shell_Landed( x2, y2, no_test, f_rate, INV_MORTAR, sprite[no_test].rank);
		go_ahead = false;
	}

    if(hit_cover == false)                              
    if(go_ahead == true)
    {
  
       x = x2;
       y = y2;

    // Object collision detection             
       if(test_success == false) 
       for(int i=0;i<the_count;i++) 
       { 
       
	   srand(i+(int)TimerGetTime()); 	
        
       if(object_attack_on == false)           
           loop = player_list[i];            
       else 
           loop = door_list[i];   

	   if(loop < 0)
	       break;

       mid_x = sprite[loop].w+sprite[loop].box_width/2; 
       mid_y = sprite[loop].z+sprite[loop].box_height/2;
      
       row_x = (int)((x + map_startX)*10);    
       row_y = (int)((y + map_startY)*10);   
    
       the_row = (row_y*MAP_HEIGHT)+row_x;
            
       if(no_test != -1)        
       if(sprite[loop].type == DOR || sprite[loop].type == UNT || sprite[loop].type == BAG)     
       if(no_test != loop && test_success == false)
       if(sprite[loop].mouseover == false)
       if(sprite[loop].grab_switch == true)
       if(sprite[loop].score > 0 ) //  || loop == sprite[no_test].fire_target
       if(sprite[no_test].linked_sprite != sprite[loop].linked_sprite)
       if(sprite[loop].turn_off == false)
       if(( x < mid_x + 0.05f )  
       &&( x > mid_x - 0.05f)                          
       &&( y < mid_y + 0.05f)  
       &&( y > mid_y - 0.05f) )            
       {          
             
       /*    if(sprite[no_test].sector == UNIT_SAILOR     
           || sprite[no_test].sector == UNIT_GUNNER 
           || sprite[no_test].sector == UNIT_GRUNT         
           || sprite[no_test].sector == UNIT_SHIELD  
           )
		   if( (int)TimerGetTime() > sprite[no_test].heal_timer)
           if(sprite[no_test].linked_sprite != player_type && loop != p1_buddy && no_test != p1_buddy) 
           {
			    
			   if(sprite[no_test].sector != UNIT_BOMBER)   	 
			   if(Level != LVL_SCREENING && Level != LVL_CINEMA)  
			   if(sprite[loop].sector != UNIT_DECOY)
               if(rand()%8 == 4 || (reloading == true && rand()%3 == 0) ) 
			   if(player_rank != 1 || (main_mission[MISSION_RADIO] == COMPLETED || main_mission[MISSION_RADIO] == FINISHED) || arcade_kill_count >= 25)
			   if(Node_Distance1(mid_x, mid_y, my_x, my_y) <= 0.8f)       	
			   {	                           
                   throwing_grenade = true; 
				   sprite[no_test].heal_timer = (int)TimerGetTime() + 4000;	
			   }	
           } */
		    
           if(throwing_grenade == false)
           { 

				if(sta2_turn == TURN_PLAYER && sprite[no_test].linked_sprite == player_type)
					sprite[no_test].return_fire = false;	

               sprite[no_test].status = OPEN_FIRE;
                   
               sprite[no_test].anim_state = WAIT;
               
               sprite[no_test].update = true;
               
               Rank_Timer(no_test, sprite[no_test].status);
               
           } 
           

           if(sprite[no_test].sector != UNIT_SKELETON)
           if(sprite[no_test].sector != UNIT_MONKEY)
           if(sprite[no_test].sector != UNIT_DOG)
           if(sprite[no_test].sector != UNIT_BOX)
           if(sprite[no_test].sector != UNIT_SHARK)             
           if(distance > KNIFE_RANGE)     
           {       
                   
               tar_x = sprite[no_test].x+sprite[no_test].width/2;  
               tar_y = sprite[no_test].y+sprite[no_test].height/2; 
               
               if(throwing_grenade == false)
               { 
                                                  
               if(sprite[no_test].sector != UNIT_DEAD_CHIEF)
               if(sprite[no_test].sector != UNIT_SKELETON)
               if(sprite[no_test].sector != UNIT_MONKEY)
               if(sprite[no_test].sector != UNIT_DOG)  
               if(sprite[no_test].sector != UNIT_BOX)              
               if(sprite[no_test].sector != UNIT_BOMBER)
               if(sprite[no_test].sector != UNIT_SHARK)
               if(sprite[loop].type != DOR)
               {
                   if(no_test != ply_id)                 
                       New_FX(tar_x, tar_y,  sprite[no_test].w, sprite[no_test].z, 0, LOOP, 0.025f, 0.025f, 0.025f, 0.025f, 0, GFX, 1.0f, 0, 0, FX_SHELL, no_test, 8, 0, 0, -1); 
                   else
                   {
                       if( sprite[no_test].sector == UNIT_SHOTGUN ) 
                       { 
                           New_FX(tar_x, tar_y,  sprite[no_test].w, sprite[no_test].z, 0, LOOP, 0.025f, 0.025f, 0.025f, 0.025f, 0, GFX, 1.0f, 0, 0, FX_SHELL, no_test, 8, 0, 0, -1); 
                       } 
                       else
                           New_FX(tar_x, tar_y,  sprite[no_test].w, sprite[no_test].z, 0, LOOP, 0.025f, 0.025f, 0.025f, 0.025f, 0, GFX, 1.0f, 0, 0, FX_SHELL, no_test, 8, 0, 0, -1); 
                   }
                   
               }   

                
               }      

           }  
   
           if(no_test != -1) 
           if(throwing_grenade == false)            
               Rank_Timer(no_test, sprite[no_test].status);   
               
           if(no_test != -1)     
           if(throwing_grenade == false)     
           { 
                          
             if(sprite[no_test].sector == UNIT_GUNNER)
				 sniper_sfx = true;
//               Surround_Sound(no_test, SFX_RIFLE,  -1, -1);   
               
             if(sprite[no_test].sector == UNIT_MORTAR1)                           
               splash_sfx = true;  
                              
             if(sprite[no_test].sector == UNIT_SHOTGUN)
               shotgun1_sfx = true; 
                                 
             if(sprite[no_test].sector == UNIT_MONKEY)
               splat_sfx = true;    
                                
             if(sprite[no_test].sector == UNIT_SNIPER)
               sniperply_sfx = true;   

             if(sprite[no_test].sector == UNIT_BOX) 
               Surround_Sound(no_test, SFX_SIGHT,  -1, -1);
                                               
             if(sprite[no_test].sector == UNIT_DOG)
               dogdie_sfx = true;
                                             
             if(sprite[no_test].sector == UNIT_SHIELD)
               Surround_Sound(no_test, SFX_SIGHT,  -1, -1); 
                                           
             if(sprite[no_test].sector == UNIT_DUCK) 
               Surround_Sound(no_test, SFX_SIGHT,  -1, -1);   
                              
         //    if(sprite[no_test].sector == UNIT_SNIPER)
         //      sniper_sfx = true;                 
               
             if(sprite[no_test].sector == UNIT_CHIEF) 
               Surround_Sound(no_test, SFX_PISTOL,  -1, -1);                        
               
             if(sprite[no_test].sector == UNIT_SAILOR) 
               Surround_Sound(no_test, SFX_PISTOL,  -1, -1);  
               
             if(sprite[no_test].sector == UNIT_GRUNT) 
               Surround_Sound(no_test, SFX_PISTOL,  -1, -1);   
               
             if(sprite[no_test].sector == UNIT_HEAVY)  
               heavy_sfx = true;  
               
             if(sprite[no_test].sector == UNIT_GUARD) 
               Surround_Sound(no_test, SFX_MOUNT,  -1, -1);                 
                                                            
             if(sprite[no_test].sector == UNIT_WORKER) 
               Surround_Sound(no_test, SFX_CHOP,  -1, -1);                         
               
             if(sprite[no_test].sector == UNIT_MOUNTED)                           
               Surround_Sound(no_test, SFX_MOUNT,  -1, -1);  
               
             if(sprite[no_test].sector == UNIT_MORTAR)                           
               Surround_Sound(no_test, SFX_MOUNT,  -1, -1);       
               
             if(sprite[no_test].sector == UNIT_BOMBER)                           
               splash_sfx = true;  
               
             if(sprite[no_test].sector == UNIT_SKELETON)
               splat_sfx = true;                  
             
             if(sprite[no_test].sector == UNIT_DEAD_CHIEF)
               Surround_Sound(no_test, SFX_CHOP,  -1, -1); 
               
             if(sprite[no_test].sector == UNIT_SHARK)
               Surround_Sound(no_test, SFX_CHOP, -1, -1); 
                            
           } // no_test != -1 
           
           // Check accuracy to see if it hit... 
            
           rnd = rand()%100;      
           
		   // TestSpriteToShoot  
           if(no_test != -1 && loop >= 0)                 
		   {	   
			   has_rifle_equipped=true;
			   targeted = TARGET_TORSO;
		       accuracy_test = GetAccuracy(no_test, loop);
		   }  
          
           if(throwing_grenade == true) 
           {
               Throw_Grenade(no_test, loop);
               accuracy_test = -1; 
           }  

		    if(no_test != -1) 
			if(sta2_machinegun_index == -1)
			if(sta2_turn == TURN_COMPUTER && no_test == emy_id)
			if(sprite[no_test].sector == UNIT_HEAVY) 
			{
				mount_sfx = true;
				sta2_machinegun_index = loop; 
				sta2_mg_timer = 0;
				sta2_mg_fired = 0;
			} 

		    if(no_test != -1) 
			if(sta2_chief_index == -1)
			if(sta2_turn == TURN_COMPUTER && no_test == emy_id)
			if(sprite[no_test].sector == UNIT_CHIEF) 
			{
				mount_sfx = true;
				sta2_chief_index = loop;  
				sta2_chief_timer = 0;
				sta2_chief_fired = 0;
			} 

		   if(sta2_machinegun_index == -1 && sta2_chief_index == -1) 
           if(no_test != -1 && loop >= 0)  
           if(rnd <= accuracy_test)  
           {    
               if(next_scene == false)
               if(sprite[loop].score > 0)
                  Man_Shot(sprite[no_test].status, loop, no_test, BULLET_NONE, f_rate);
           }    
           else 
           {   
               
			    if(hit_cover == false)  
				{
					if(sprite[no_test].sector != UNIT_DOG)
						Create_Dust_Effect(x2, y2, false, false, f_rate); 

					if(no_test != -1 && loop >= 0)
						DamageNumber(loop, -1, STA2_DAMAGE_MISS );  

                    if(sprite[no_test].sector == UNIT_SHOTGUN)  
                    {                         
                        Create_Dust_Effect(x2, y2, true, false, f_rate);
                        Create_Dust_Effect(x2, y2, true, false, f_rate); 
                        Create_Dust_Effect(x2, y2, true, false, f_rate); 
                    }
  
				} 
           }   
           
           if(no_test != -1) 
               sprite[no_test].emy_shooting = true;
           
           test_success = true; 

       }  
                              
    } 
         
  } 
    
  return(test_success);     
     
}   

bool Man_Shot(int guy_status, int guy_shot, int guy_shooting, int bullet_type, int f_rate)
{ 
     
    float exp_x=0.0f, exp_y=0.0f; 
    float kill_count=0; 
    float mid_x=0.0f, mid_y=0.0f;
	float widthX1=0.0f, heightY1=0.0f;
    int row_x=0, row_y=0;
    bool hit_a_building=false;
    int rnd=0;     
    int item_value=0;
    int item_type = INV_NONE;
    float closest_point = 2.0f;    
    int best_point=-1;
    float dis_to_point=0.0f;
    float tar_x=0.0f, tar_y=0.0f;

    int enemy_damage=0; 
    int enemy_strength=0;
	int vampire=0;
    int exp_gain=0;
    int torso_targeted=TARGET_TORSO;    
    float angle=0.0f, deltax=0.0f, deltay=0.0f; 
    bool collision_returned=false;   
    int temp_row_x=0, temp_row_y=0;
    int index=0, old_index=0;
    int rnd1 = -1;
    hit_man = guy_shot; 
    bool no_damage = false;  
    bool double_damage = false;  
    bool shot_hit_armour=false;   
    int damage_factor = 1;
    bool buddy_special = false;
    bool skip_stunned=false;
    int PLAYERS_GUN_FIREPOWER=1;
	int original_score=0;
	float hitX=0, hitY=0;
	int temp_ply_id=-1; 
	float damage_percent = 0.0f;
	int xp_value=0;

	bool player_is_shooting = false;
	bool player_is_shot = false;
	bool skip_shot_a_player = false;  
	
	bool area_damage=false;

	int DAMAGE_REDUCTION = 1; 

	int FLAK_REDUCTION = 100; 
	int KNIFE_MULITPLIER=0;

	int pack_id=-1;
	int pack_id_guy_shot = -1;

	if(sta2_turn == TURN_COMPUTER)
		temp_ply_id = -1;
	else
		temp_ply_id = ply_id;

	if(guy_shooting < 0) 
		return(0);

	if(guy_shot < 0)
		return(0);

	if(guy_shooting != -1)
	if(guy_shooting == temp_ply_id)
	{
		#if INCLDUE_360_CONTROLLER == 1
			VIBRATE_LEFT(52000, 150);  
			VIBRATE_RIGHT(52000, 150);
		#endif
	}

	if(guy_shooting != -1)
	if(sprite[guy_shooting].linked_sprite == player_type)
	if(sprite[guy_shooting].value2 >= 0)
	{
		pack_id = sta2_squad[sprite[guy_shooting].value2].wp;
	}

	if(guy_shot != -1)
	if(sprite[guy_shot].linked_sprite == player_type)
	if(sprite[guy_shot].value2 >= 0)
	{
		pack_id_guy_shot = sta2_squad[sprite[guy_shot].value2].wp;
	}


	if(f_rate <= 0)
	    f_rate = 1; 
    
	if(guy_shot != -1)
		original_score = sprite[guy_shot].score; 

    PLAYERS_GUN_FIREPOWER = PLY_FIREPOWER;

    if(bullet_type != BULLET_NONE) 
    {
        targeted = TARGET_TORSO;     
    } 
	  
	// Enemy shooting...  
	if(guy_status != UNIT_MORTAR && guy_status != UNIT_GRENADE)
	if(guy_shot != -1 && guy_shooting != -1)  
    if(guy_status != OPEN_CUT && guy_status != OPEN_STAMP && guy_status != OPEN_THROW)        
    {
           
      if(sprite[guy_shot].linked_sprite == player_type)             
      {   
	          
			// Disable any cammo...
			if(pack_id_guy_shot > -1)   
			if(sta2_pack[pack_id_guy_shot].special == PACK_SPECIAL_MAGICNET)    
			if(sta2_pack[pack_id_guy_shot].special_charge > 0)
			{
				sta2_pack[pack_id_guy_shot].special_charge = 0;
				sprite[guy_shot].camo = false;
			}

		  if(sprite[guy_shooting].sector == UNIT_GUNNER)      
		  if(sta2_difficulty == STA2_HARD_MODE) 
			enemy_damage = (20 + sprite[guy_shooting].rank*17) + rand()%ENEMY_BASE_FP_RANDOM_HARD; // 35-45
		  else
			enemy_damage = (20 + sprite[guy_shooting].rank*15) + rand()%ENEMY_BASE_FP_RANDOM; // 35-45

		  if(sprite[guy_shooting].sector == UNIT_DOG) 
		  if(sta2_difficulty == STA2_HARD_MODE)
			enemy_damage = (20 + sprite[guy_shooting].rank*17) + rand()%ENEMY_BASE_FP_RANDOM_HARD; // 35-45
		  else
			enemy_damage = (20 + sprite[guy_shooting].rank*15) + rand()%ENEMY_BASE_FP_RANDOM; // 35-45

		  if(sprite[guy_shooting].sector == UNIT_HEAVY)  
		  if(sta2_difficulty == STA2_HARD_MODE)
			enemy_damage = 10 + rand()%(sprite[guy_shooting].rank*17); // 10-25 
		  else
			enemy_damage = 10 + rand()%(sprite[guy_shooting].rank*15); // 10-25 

		  if(sprite[guy_shooting].sector == UNIT_CHIEF)  
		  if(sta2_difficulty == STA2_HARD_MODE)
			enemy_damage = 10 + rand()%(sprite[guy_shooting].rank*17); // 10-25
		  else
			enemy_damage = 10 + rand()%(sprite[guy_shooting].rank*15); // 10-25

		  if(sprite[guy_shooting].sector == UNIT_SNIPER)  
		  if(sta2_difficulty == STA2_HARD_MODE)
			enemy_damage = (30 + sprite[guy_shooting].rank*17) + rand()%ENEMY_BASE_FP_RANDOM_HARD; // 45-55
		  else
			enemy_damage = (30 + sprite[guy_shooting].rank*15) + rand()%ENEMY_BASE_FP_RANDOM; // 45-55
           

		  if(pack_id_guy_shot > -1)  
		  if(sta2_pack[pack_id_guy_shot].special == PACK_SPECIAL_SHIELD)   
		  if(sta2_pack[pack_id_guy_shot].special_charge > 0)
		  {
			  enemy_damage -= (int)((float)enemy_damage * 0.40f);
		  }
		   
		  if(enemy_damage <= 0)  
			  enemy_damage = 1;  
	   
		  sprite[guy_shot].score -= enemy_damage;  // / DAMAGE_REDUCTION
		    
		  DamageNumber( guy_shot, enemy_damage, STA2_DAMAGE_NORM ); 
   		  
		  if(enemy_damage > Calculate_TotalScore(guy_shot))
			  enemy_damage = Calculate_TotalScore(guy_shot);
		   
		  if(enemy_damage != 0)
			damage_percent = (float)( Calculate_TotalScore(guy_shot) / enemy_damage);

		  if(damage_percent != 0)  
		  { 
			  if(sta2_is_epic_battle == true)
			      sta2_power_bar += ((100.0f / damage_percent) / 1.5f);
			  else
			      sta2_power_bar += ((100.0f / damage_percent) / 1.2f);
		  }

		  if(sta2_power_bar >= 100.0f)
		     sta2_power_bar = 100.0f;

      }   // sprite[guy_shot].linked_sprite == player_type  
	   
	  //  Player unit shot an enemy... 
	  if(guy_status != UNIT_MORTAR && guy_status != UNIT_GRENADE) 
      if(guy_shot != -1 && guy_shooting != -1)    
	  if(pack_id != -1) 
      if( sprite[guy_shot].linked_sprite != player_type && guy_shooting != temp_ply_id  || area_damage == true)  
      { 
          
		  // Disable any cammo...
		  if(pack_id > -1)   
		  if(sta2_pack[pack_id].special == PACK_SPECIAL_MAGICNET)    
		  if(sta2_pack[pack_id].special_charge > 0)
		  {
			  sta2_pack[pack_id].special_charge = 0;
			  sprite[guy_shooting].camo = false; 
		  }

		  if(sprite[guy_shooting].sector == UNIT_GUNNER)
			  PLAYERS_GUN_FIREPOWER = (RIFLE1_BASE_FP + rand()%RIFLE1_BASE_FP_RANDOM) + (sta2_pack[pack_id].rank*20);

		  if(sprite[guy_shooting].sector == UNIT_DOG)
			  PLAYERS_GUN_FIREPOWER = (RIFLE1_BASE_FP + rand()%RIFLE1_BASE_FP_RANDOM) + (sta2_squad[sprite[guy_shooting].value2].rank*20);

		  if(sprite[guy_shooting].sector == UNIT_HEAVY)
			  PLAYERS_GUN_FIREPOWER = 20 + (rand()%(sta2_pack[pack_id].rank*20));

		  enemy_damage = PLAYERS_GUN_FIREPOWER;   

		  // Rage...
		  if(pack_id > -1)   
		  if(sta2_pack[pack_id].special == PACK_SPECIAL_DUMDUM)     
		  if(sta2_pack[pack_id].special_charge > 0)
		  {
			  enemy_damage += (int)((float)enemy_damage * 0.30f);
		  } 

		  // Deathblow...
		  if(pack_id > -1)   
		  if(sta2_pack[pack_id].special == PACK_SPECIAL_DEATHBLOW)    
		  if(sta2_pack[pack_id].special_charge > 0)
		  {
			  enemy_damage *= 2;
		  } 

		  // Vampire... 
		  if(pack_id > -1)    
		  if(sta2_pack[pack_id].special == PACK_SPECIAL_VAMPIRE)    
		  if(sta2_pack[pack_id].special_charge > 0)
		  {
			  vampire = (int)((float)enemy_damage * 0.18f); 
			  if(vampire <= 0)
				  vampire = 1;
			  DamageNumber( guy_shooting, vampire, STA2_DAMAGE_HP );
			  sprite[guy_shooting].score += vampire;
			  if(sprite[guy_shooting].score > Calculate_TotalScore(guy_shooting))
				  sprite[guy_shooting].score = Calculate_TotalScore(guy_shooting);
		  }
		   
		  // Final...  
		  if(pack_id > -1)   
		  if(sta2_pack[pack_id].special == PACK_SPECIAL_LASTCHANCE)    
		  if(sta2_pack[pack_id].special_charge > 0)
		  {
			  if(sprite[guy_shooting].sector == UNIT_HEAVY)
			  {
				  if(rand()%40 == 0)  
					  enemy_damage = 999;
				  else
					  enemy_damage = 1;
			  }
			  else
			  {
				  if(rand()%8 == 0)
					  enemy_damage = 999;
				  else 
					  enemy_damage = 1;
			  }
		  } 


		    
		  if(enemy_damage <= 0)   
			  enemy_damage = 1;

          sprite[guy_shot].score -= enemy_damage; 
		   
		  DamageNumber( guy_shot, enemy_damage, STA2_DAMAGE_NORM );  

		  if(enemy_damage > Calculate_TotalScore(guy_shot)) 
			  enemy_damage = Calculate_TotalScore(guy_shot);

		  if(enemy_damage != 0)
			damage_percent = (float)(Calculate_TotalScore(guy_shot) / enemy_damage);

		  if(damage_percent != 0)
		  { 
			  if(sta2_is_epic_battle == true)
			      sta2_power_bar += ((100.0f / damage_percent) / 20);
			  else
			      sta2_power_bar += ((100.0f / damage_percent) / 10);
		  }

		  if(sta2_power_bar >= 100.0f)
		     sta2_power_bar = 100.0f;
   
      }   // sprite[guy_shot].linked_sprite == player_type  
                
	  if(guy_status != UNIT_MORTAR && guy_status != UNIT_GRENADE)
      if(ply_id != -1 && guy_shot != -1)   
	  if(pack_id != -1) 
      if(guy_shooting == temp_ply_id)         
      {    
          
		  // Disable any cammo...
		  if(pack_id > -1)   
		  if(sta2_pack[pack_id].special == PACK_SPECIAL_MAGICNET)    
		  if(sta2_pack[pack_id].special_charge > 0)
		  {
			  sta2_pack[pack_id].special_charge = 0;
			  sprite[guy_shooting].camo = false;
		  }

		  // Rifle increase by +20 damage per extra lvl for weapon pack. Pistol increases by +7.
		   
		  if(has_pistol_equipped == true)      
		  {
		      PLAYERS_GUN_FIREPOWER = (PISTOL1_BASE_FP + rand()%PISTOL1_BASE_FP_RANDOM) + (sta2_pack[pack_id].rank*10);
		  }

		  if(has_rifle_equipped == true)    
		  {
		      PLAYERS_GUN_FIREPOWER = (RIFLE1_BASE_FP + rand()%RIFLE1_BASE_FP_RANDOM) + (sta2_pack[pack_id].rank*20);
		  }

		  if(has_sniper_equipped == true)        
		  {
		      PLAYERS_GUN_FIREPOWER = (SNIPER1_BASE_FP + rand()%RIFLE1_BASE_FP_RANDOM) + (sta2_pack[pack_id].rank*20);
		  }

		  if(has_shotgun_equipped == true)    
		  {
		      PLAYERS_GUN_FIREPOWER = (rand()%45) + (sta2_pack[pack_id].rank*20);
		  }
		   
		  if(has_machine_equipped == true)    
		  {
		      PLAYERS_GUN_FIREPOWER = 20 + (rand()%(sta2_pack[pack_id].rank*20));
		  }
                       
          torso_targeted = targeted;    

		  if(has_rifle_equipped == false && has_pistol_equipped == false && has_sniper_equipped == false)
			  torso_targeted = TARGET_TORSO;

		  if(torso_targeted == TARGET_HEAD) 
			enemy_damage = (int)(PLAYERS_GUN_FIREPOWER*1.5);
		  if(torso_targeted == TARGET_TORSO) 
			enemy_damage = PLAYERS_GUN_FIREPOWER;
		  if(torso_targeted == TARGET_LEGS) 
			enemy_damage = (int)(PLAYERS_GUN_FIREPOWER/4); 

		  // Rage...
		  if(pack_id > -1)   
		  if(sta2_pack[pack_id].special == PACK_SPECIAL_DUMDUM)    
		  if(sta2_pack[pack_id].special_charge > 0)
		  {
			  enemy_damage += (int)((float)enemy_damage * 0.30f);
		  }

		  // Deathblow... 
		  if(pack_id > -1)   
		  if(sta2_pack[pack_id].special == PACK_SPECIAL_DEATHBLOW)    
		  if(sta2_pack[pack_id].special_charge > 0)
		  {
			  enemy_damage *= 2;
		  } 

		  // Vampire... 
		  if(pack_id > -1)   
		  if(sta2_pack[pack_id].special == PACK_SPECIAL_VAMPIRE)    
		  if(sta2_pack[pack_id].special_charge > 0)
		  {
			  vampire = (int)((float)enemy_damage * 0.18f);
			  if(vampire <= 0)
				  vampire = 1;
			  DamageNumber( guy_shooting, vampire, STA2_DAMAGE_HP );
			  sprite[guy_shooting].score += vampire;
			  if(sprite[guy_shooting].score > Calculate_TotalScore(guy_shooting))
				  sprite[guy_shooting].score = Calculate_TotalScore(guy_shooting);
		  } 

		  // Final... 
		  if(pack_id > -1)   
		  if(sta2_pack[pack_id].special == PACK_SPECIAL_LASTCHANCE)    
		  if(sta2_pack[pack_id].special_charge > 0)
		  {
			  if(has_machine_equipped == true) 
			  {
				  if(rand()%35 == 0)
					  enemy_damage = 999;
				  else
					  enemy_damage = 1; 
			  }
			  if(has_rifle_equipped == true) 
			  {
				  if(rand()%3 == 0)
					  enemy_damage = 999;
				  else
					  enemy_damage = 1;  
			  }
			  if(has_machine_equipped == false && has_rifle_equipped == false)
			  {
				  if(rand()%7 == 0)
					  enemy_damage = 999;
				  else
					  enemy_damage = 1;
			  }

		  } 
         
		     
		  if(enemy_damage <= 0) 
			  enemy_damage = 1; 

          sprite[guy_shot].score -= enemy_damage;

		  DamageNumber( guy_shot, enemy_damage, STA2_DAMAGE_NORM );

		  if(enemy_damage > Calculate_TotalScore(guy_shot))
			  enemy_damage = Calculate_TotalScore(guy_shot);

		  if(enemy_damage != 0)
			damage_percent = (float)(Calculate_TotalScore(guy_shot) / enemy_damage);

		  if(damage_percent != 0)
		  { 
			  if(sta2_is_epic_battle == true)
			      sta2_power_bar += ((100.0f / damage_percent) / 20);
			  else
			      sta2_power_bar += ((100.0f / damage_percent) / 10);
		  }

		  if(sta2_power_bar >= 100.0f)
			  sta2_power_bar = 100.0f;
            
		}  // Not UNIT_SHELL

	}
	    
    if(guy_shot != -1)         
    if(guy_status == UNIT_MORTAR && lock_player == false)   
    {   
          
		// Disable any cammo...
		if(pack_id_guy_shot > -1)   
		if(sta2_pack[pack_id_guy_shot].special == PACK_SPECIAL_MAGICNET)    
		if(sta2_pack[pack_id_guy_shot].special_charge > 0)
		{
			sta2_pack[pack_id_guy_shot].special_charge = 0;
			sprite[guy_shot].camo = false;
		}

		enemy_damage = 1 + rand()%(60 + (bullet_type*30) );


		if(pack_id_guy_shot > -1)  
		if(sta2_pack[pack_id_guy_shot].special == PACK_SPECIAL_SHIELD) 
		if(sta2_pack[pack_id_guy_shot].special_charge > 0)
		{
			enemy_damage -= (int)((float)enemy_damage * 0.40f);
		}

		if(enemy_damage < 0)
			enemy_damage = 0;

		// Vampire... 
		if(pack_id > -1)    
		if(sta2_pack[pack_id].special == PACK_SPECIAL_VAMPIRE)    
		if(sta2_pack[pack_id].special_charge > 0)
		{
			vampire = (int)((float)enemy_damage * 0.18f); 
			if(vampire <= 0)
				vampire = 1;
			DamageNumber( guy_shooting, vampire, STA2_DAMAGE_HP );
			sprite[guy_shooting].score += vampire;
			if(sprite[guy_shooting].score > Calculate_TotalScore(guy_shooting))
				sprite[guy_shooting].score = Calculate_TotalScore(guy_shooting);
		}

		sprite[guy_shot].score -= enemy_damage; 

		DamageNumber( guy_shot, enemy_damage, STA2_DAMAGE_NORM ); 

		if(enemy_damage > Calculate_TotalScore(guy_shot))
			enemy_damage = Calculate_TotalScore(guy_shot);

		if(enemy_damage != 0)
			damage_percent = (float)(Calculate_TotalScore(guy_shot) / enemy_damage);

		if(damage_percent != 0)
		{ 
			if(sta2_is_epic_battle == true)
			    sta2_power_bar += ((100.0f / damage_percent) / 20);
			else
			    sta2_power_bar += ((100.0f / damage_percent) / 10);
		}

		if(sta2_power_bar >= 100.0f)
		   sta2_power_bar = 100.0f;
    }   
	      
    if(guy_shot != -1)         
    if(guy_status == UNIT_GRENADE && lock_player == false)  
    {   
		  
		enemy_damage = 1 + rand()%(STA2_GRENADE_AMOUNT + (bullet_type*30) );
   

		// Vampire... 
		if(pack_id > -1)    
		if(sta2_pack[pack_id].special == PACK_SPECIAL_VAMPIRE)    
		if(sta2_pack[pack_id].special_charge > 0)
		{
			vampire = (int)((float)enemy_damage * 0.18f); 
			if(vampire <= 0)
				vampire = 1;
			DamageNumber( guy_shooting, vampire, STA2_DAMAGE_HP );
			sprite[guy_shooting].score += vampire;
			if(sprite[guy_shooting].score > Calculate_TotalScore(guy_shooting))
				sprite[guy_shooting].score = Calculate_TotalScore(guy_shooting);
		}

		sprite[guy_shot].score -= enemy_damage;
		 
		DamageNumber( guy_shot, enemy_damage, STA2_DAMAGE_NORM );  

		if(enemy_damage > Calculate_TotalScore(guy_shot))
			enemy_damage = Calculate_TotalScore(guy_shot);

		if(enemy_damage != 0)
			damage_percent = (float)(Calculate_TotalScore(guy_shot) / enemy_damage);

		if(damage_percent != 0)
		{ 
			if(sta2_is_epic_battle == true)
			    sta2_power_bar += ((100.0f / damage_percent) / 20);
			else
			    sta2_power_bar += ((100.0f / damage_percent) / 10);
		}

		if(sta2_power_bar >= 100.0f)
		   sta2_power_bar = 100.0f;
    }   	  
    
	// Knifed a guy...
    if(skip_shot_a_player == false && guy_shot != -1)    
    if( (guy_status == OPEN_CUT || guy_status == OPEN_STAMP)) 
    {
        sprite[guy_shot].score -= KNIFE_FIREPOWER;          
    }   
      
    // Stop guy from flashing...  
	if(guy_shot != -1)
    if(sprite[guy_shot].score > 0 || sprite[guy_shot].type != UNT)
	if(overshot == false)
    {
           
         if(shot_hit_armour==false)
         {
                                                       
             sprite[guy_shot].flash_target = true; 

             sprite[guy_shot].flash_timer = (int)TimerGetTime() + 50;
          
         } 
         
         if(ply_id != -1)
         if(guy_shot == ply_id)
         {
             start_healing = false;
             start_healing_timer = 0;
         }    
         
         if(guy_shot == flash_on && flash_on >= 0) 
         {   
             sprite[flash_on].alpha = 1.0f;

             flash_on = -1;
         } 
            
    }  
    
    if(guy_shot != -1)
    if(sprite[guy_shot].score < 0)
        sprite[guy_shot].score = 0;

	// Fix up if player unit goes down to 1hp... 
    if(guy_shot != -1)
	if(sprite[guy_shot].linked_sprite == player_type)
    if(sprite[guy_shot].score == 1)
        sprite[guy_shot].score = 0;
     
    if(guy_shot != -1 && guy_shooting != -1)  
    if(lock_player == false) 
    if(sprite[guy_shot].sector != UNIT_BOSS)
    if(sprite[guy_shot].sector != UNIT_MORTAR || targeted != TARGET_LEGS) 
    if(sprite[guy_shot].score <= 0)     
    if(sprite[guy_shot].status != DIEING  
    && sprite[guy_shot].status != MAN_DOWN
    && sprite[guy_shot].status != MAN_DOWN1     
    && sprite[guy_shot].status != MAN_DOWN2
    && sprite[guy_shot].status != FLATTENED) 
    {
		
        if(sprite[guy_shot].building == false)           
        {   
	        
            if(sprite[guy_shot].type == UNT)  
            {                

				// Reduce CP points by 1 if unit was a C.O

				if(sprite[guy_shot].linked_sprite == player_type) 
				if(sprite[guy_shot].value2 != -1) 
				if(sta2_squad[sprite[guy_shot].value2].type == STA2_CO)
					sta2_player_co_down = true;

				if(sprite[guy_shot].linked_sprite != player_type)
				if(sprite[guy_shot].rank != sta2_sector)
					sta2_computer_co_down = true;

       //     rnd = rand()%2;     // Enable for enemies having chance for mercy

			rnd = 1;    

			if(ply_id != -1)   
            if(sprite[guy_shot].linked_sprite == player_type) 
			if(sta2_squad_alive_count >= 2 && sta2_squad[sprite[guy_shot].value2].type != STA2_CO) 
			{
				rnd = 0; // Unit's can't die for now..
			}
			else  
                rnd = 0;      
			 
			if(sprite[guy_shot].linked_sprite != player_type) 
			{
				sta2_enemy_count--; 
				sta2_enemies_defeated++;
				sta2_killed_in_one_shot++;
			}

			// Isn't dead already...
			if(sprite[guy_shot].mercy == false)
			if(sprite[guy_shot].linked_sprite == player_type) 
				sta2_player_count--;
			 
			if(sta2_enemy_count <= 0)            
			{ 
				sta2_enemy_count = 0;

				cheer_sfx = true;  
				sta2_battle_outcome = BATTLE_VICTORY;      

				if(sta2_turn == TURN_COMPUTER)  
				{
					game_condition = G_VICTORY;
					reset_map_timer = (int)TimerGetTime()+3000;
				} 
				 
				if(sta2_no_of_turns <= 1)   
				if(sta2_globals[GLOBAL_TYPE_SPEED] == GLOBALS_ACTIVE || sta2_globals[GLOBAL_TYPE_EPIC] == GLOBALS_ACTIVE)
				{
					sta2_levelup_display = true;  
					sta2_levelup_display_timer = (int)TimerGetTime()+3000;

					if(sta2_globals[GLOBAL_TYPE_SPEED] == GLOBALS_ACTIVE)
					{
					    sta2_got_speed_bonus = true; 

						Set_Sprite(32, 1, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Speed bonus

						firework_sfx = true;
					} 
					 
					if(sta2_is_epic_battle == true)  
					if(sta2_globals[GLOBAL_TYPE_EPIC] == GLOBALS_ACTIVE)
					{
						sta2_got_epic_bonus = true;

						Set_Sprite(32, 2, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Epic bonus

						firework_sfx = true; 
						     
					#if IS_FULL_STEAM == 1 

					if(STEAM_ACTIVE == true) 
					if(IS_FULL_GAME == true) 
					if (g_SteamAchievements)
					{
						g_SteamAchievements->SetAchievement("STA2_MEDAL_2"); // Get an epic bonus

						if(sta2_globals[GLOBAL_STA2_MEDAL_2] == GLOBALS_RESET)
						{
							sta2_globals[GLOBAL_STA2_MEDAL_2] = GLOBALS_ACTIVE;
							firework_sfx = true;

						}
					}
						 
					#endif

					}

				}

				   
			}        

			if(sprite[guy_shot].linked_sprite == player_type)
			if(sta2_player_count <= 0)      
			{   
				sta2_player_count = 0;      

				defeat_sfx = true;
				sta2_battle_outcome = BATTLE_DEFEAT;  

				game_condition = G_DEFEAT;

				reset_map_timer = (int)TimerGetTime()+3000;

			}

            // Mercy code...                 
            if( rnd == 0 )      
            {   
 
                mid_x = sprite[guy_shot].w+sprite[guy_shot].box_width/2; 
                mid_y = sprite[guy_shot].z+sprite[guy_shot].box_height/2;  
                  
                row_x = (int)((mid_x + map_startX)*10);         
                row_y = (int)((mid_y + map_startY)*10);   

				if( (row_y*MAP_HEIGHT)+row_x >= 0)
				{

		            map_col[(row_y*MAP_HEIGHT)+row_x] = 0;  
                      
		            if(tiles[(row_y*MAP_HEIGHT)+row_x]>=480 && tiles[(row_y*MAP_HEIGHT)+row_x] < 484 ) // Water?
		                map_col[(row_y*MAP_HEIGHT)+row_x] = 8;   

				}      
                // Flash when they die...
                sprite[guy_shot].dflash_timer = 1;
                
                flash_no_count=0;
                
                sprite[guy_shot].death_flash  = true;

				ShotIdle(guy_shot);   

                sprite[guy_shot].status = MERCY; 

				sprite[guy_shot].anim_state = WAIT;
  
                sprite[guy_shot].all_timer = (int)TimerGetTime() + 6000;

				sprite[guy_shot].update = true; 
                    
                sprite[guy_shot].score = 1;    

                sprite[guy_shot].mercy = true;     
                  
				sprite[guy_shot].thrown_effect = 0;

                if(sprite[guy_shot].sector != UNIT_SKELETON  
                && sprite[guy_shot].sector != UNIT_BIRD 
                && sprite[guy_shot].sector != UNIT_SHARK  
                && sprite[guy_shot].sector != UNIT_MONKEY 
                && sprite[guy_shot].sector != UNIT_DOG  
                && sprite[guy_shot].sector != UNIT_BOX
				&& sprite[guy_shot].sector != UNIT_DECOY
                && sprite[guy_shot].sector != UNIT_DEAD_CHIEF
				&& (sprite[guy_shot].sector != UNIT_BOSS || sprite[guy_shot].sector_action == AI_ADMIRAL)) 
                {          
					if(sprite[guy_shot].linked_sprite != player_type)  
						Surround_Sound(guy_shot, SFX_DEATH, -1, -1);  
					else 
					{ 
						if(sprite[guy_shot].value2 != -1)
						if(sta2_squad[sprite[guy_shot].value2].type == STA2_CO)
							Surround_Sound(guy_shot, SFX_DEATH_GIRL, -1, -1);
						else
							Surround_Sound(guy_shot, SFX_PAIN, -1, -1);
					} 
                }
                         
            }      
            else                                                         
            {                

				if(guy_shooting != -1)
				if(sprite[guy_shooting].linked_sprite == player_type)  
				{ 
					// Give Xp gain to unit..    
					exp_gain = 5 + sprite[guy_shot].rank*5;

					if(sprite[guy_shot].sector == UNIT_HEAVY || sprite[guy_shot].sector == UNIT_MORTAR)
						exp_gain += 5;

					if(sprite[guy_shot].sector == UNIT_DOG)
						exp_gain /= 2;    
		      
					// Wisdom...  
					if(pack_id > -1)     
					if(sta2_pack[pack_id].special == PACK_SPECIAL_XPGAIN)    
					if(sta2_pack[pack_id].special_charge > 0)  
					  exp_gain += (int)((float)exp_gain * 0.5f); 

					if(sprite[guy_shooting].value2 >= 0)
						sta2_squad[sprite[guy_shooting].value2].xp += exp_gain;
					
					xp_damage_index[xp_damage_count] = guy_shot;
					xp_damage_timer[xp_damage_count] = (int)TimerGetTime() + 500;
					xp_damage_gain[xp_damage_count] = exp_gain;

					xp_damage_count++;   

					if(xp_damage_count >= 10) 
						xp_damage_count = 0; 

					if(sta2_difficulty == STA2_TRAINING_MODE)
						xp_value = (10 + sta2_squad[sprite[guy_shooting].value2].rank*20);
					else
						xp_value = (10 + sta2_squad[sprite[guy_shooting].value2].rank*30);

					if(sprite[guy_shooting].value2 >= 0)
					if(sta2_squad[sprite[guy_shooting].value2].xp >= xp_value )
					{
						sta2_squad[sprite[guy_shooting].value2].rank++; 
						sprite[guy_shooting].rank++;  

						if(sprite[guy_shooting].rank > sta2_highest_level)
							sta2_highest_level = sprite[guy_shooting].rank;

						sta2_squad[sprite[guy_shooting].value2].xp -= xp_value; 
						 
						// Restore units health... 
					//	sta2_squad[sprite[guy_shooting].value2].health = TotalSquadScore(sprite[guy_shooting].value2);
					//	sprite[guy_shooting].score = sta2_squad[sprite[guy_shooting].value2].health;

						Set_Sprite(32, 0, LOOP, ANIM_HUD, ANIM_NOT_WALKING);

						sta2_levelup_display = true;  
						sta2_levelup_display_timer = (int)TimerGetTime()+3000;

						if(sprite[guy_shooting].rank >= 13)
						{
							#if IS_FULL_STEAM == 1 

							if(STEAM_ACTIVE == true) 
							if(IS_FULL_GAME == true)
							if (g_SteamAchievements)
							{
								g_SteamAchievements->SetAchievement("STA2_MEDAL_13"); // Get a team member to lvl 13...
								if(sta2_globals[GLOBAL_STA2_MEDAL_13] == GLOBALS_RESET)
								{
									sta2_globals[GLOBAL_STA2_MEDAL_13] = GLOBALS_ACTIVE;
									firework_sfx = true;

								}
							}

							#endif
						}
						firework_sfx = true;

					} 

				} 

				sprite[guy_shot].thrown_effect = 0;

                sprite[guy_shot].grenaded = DEATH_NORMAL; 
                        
                if(ply_id != -1)  
				if(guy_shooting != -1)
                if(guy_shooting == ply_id )             
                if(torso_targeted == TARGET_HEAD)  
                if(sprite[guy_shot].sector != UNIT_MORTAR1)  
				if(sprite[guy_shot].sector != UNIT_SHOTGUN) 
				{    
	                sprite[guy_shot].grenaded = DEATH_HEADSHOT; // was DEATH_NORMAL
					Create_Gibs_Effect(guy_shot, false, TARGET_HEAD); 	
				}

                if(sprite[guy_shot].sector == UNIT_MONKEY)   
                    sprite[guy_shot].grenaded = DEATH_NORMAL; 
                         
                if(sprite[guy_shot].sector == UNIT_DOG)   
                    sprite[guy_shot].grenaded = DEATH_NORMAL;
                         
                if(sprite[guy_shot].sector == UNIT_BOX)   
                    sprite[guy_shot].grenaded = DEATH_NORMAL;
                                                                                     
                if(guy_status == UNIT_SHELL)  
                    sprite[guy_shot].grenaded = DEATH_GRENADE;
                  
                if(ply_id != -1)  
				if(guy_shooting != -1)
                if(guy_shooting == ply_id ) 
                if(sprite[guy_shot].sector == UNIT_MORTAR1)
                    sprite[guy_shot].grenaded = DEATH_GRENADE;
                   
                if(bullet_type == BULLET_FIRE || bullet_type == BULLET_FIRE1 || bullet_type == BULLET_FIRE2 || bullet_type == BULLET_FIRE3)
                    sprite[guy_shot].grenaded = DEATH_GRENADE;

                sprite[guy_shot].status = DIEING; 

                if(guy_status != OPEN_CUT)    
				{                 
	                alert_enemies = true; 
	                noise_type = MID_NOISE;                  
	                 
	                noise_x = sprite[guy_shot].w+sprite[guy_shot].box_width/2;                        
	                noise_y = sprite[guy_shot].z+sprite[guy_shot].box_height/2;  
					
				}
                 
                if(guy_shooting != -1 && guy_shot != -1) 
                if(sprite[guy_shot].sector != UNIT_MORTAR)
                if(sprite[guy_shot].sector != UNIT_BOMBER || sprite[guy_shot].onDeath_action != TURRET)                
                    Knock_Back(guy_shooting, guy_shot, f_rate);  
                             
                if(p1_buddy != -1 && ply_buddy_dead == false)     
                if((guy_shot == p1_buddy && player_type == p_server) )
                {
                    Calculate_Lifebar();
                    ply_buddy_dead = true;                      
                }   
                
                // Flash when they die...
                sprite[guy_shot].dflash_timer = 1;
                
                flash_no_count=0;
                
                sprite[guy_shot].death_flash  = true;
                
                if(guy_shooting != -1)
                if(guy_status == OPEN_CUT) 
                { 
                         
                   Create_Gibs_Effect(guy_shot, false, -1); 

 				   Surround_Sound(guy_shot, SFX_SPLATTED, -1, -1);

                   if(NICE_EFFECT)
                       New_FX(sprite[guy_shot].x, sprite[guy_shot].y-0.0001f, sprite[guy_shot].x, sprite[guy_shot].y, 59, PLAY, sprite[guy_shot].width, sprite[guy_shot].height, sprite[guy_shot].width, sprite[guy_shot].height, 2, GFX, 1.0f, 0, 0, FX_SPLAT, guy_shot, 2, 0, 0, -1);
                   
                   if(guy_shot != ply_id)
				   if(guy_shooting != -1)
                   if(sprite[guy_shot].sector != UNIT_MORTAR)
                   if(sprite[guy_shot].sector != UNIT_BOMBER || sprite[guy_shot].onDeath_action != TURRET)                    
                       Knock_Back(guy_shooting, guy_shot, f_rate);
    
                   sprite[guy_shot].splatted = true;
                   
               }                              
                  
                if(in_dungeon == true && !ARCADE)
                if(sprite[guy_shot].linked_sprite != player_type)
                {
                                                  
                    enemy_count--;  
                    
                    if(Level == LVL_CELLAR) 
                        cellar_kill_count++;
                    
                }  
                
                if(sprite[guy_shot].sector != UNIT_SKELETON 
                && sprite[guy_shot].sector != UNIT_DEAD_CHIEF 
                )
                    sprite[guy_shot].all_timer = (int)TimerGetTime() + 1000; // 1000
                else
                    sprite[guy_shot].all_timer = (int)TimerGetTime() + 1000;  // 1500
                
                mid_x = sprite[guy_shot].w+sprite[guy_shot].box_width/2; 
                mid_y = sprite[guy_shot].z+sprite[guy_shot].box_height/2;  
                  
                row_x = (int)((mid_x + map_startX)*10);         
                row_y = (int)((mid_y + map_startY)*10);   

				if( (row_y*MAP_HEIGHT)+row_x >= 0) 
				{

		            map_col[(row_y*MAP_HEIGHT)+row_x] = 0; 
                      
		            if(tiles[(row_y*MAP_HEIGHT)+row_x]>=480 && tiles[(row_y*MAP_HEIGHT)+row_x] < 484 ) // Water?
		                map_col[(row_y*MAP_HEIGHT)+row_x] = 8;   

				}                 
     
                if(guy_shot != ply_id && guy_shot != p1_buddy && guy_shooting != p1_buddy) 
			    if(guy_shooting != -1 && guy_shot != -1)
                if(sprite[guy_shot].sector != UNIT_MORTAR)
                if(sprite[guy_shot].sector != UNIT_BOMBER || sprite[guy_shot].onDeath_action == MOVABLE)
                    Knock_Back(guy_shooting, guy_shot, f_rate);
                  
                
                if(ply_id != -1 && guy_shooting != -1)
				if(guy_shooting != -1)
                if(guy_shooting == ply_id && player_type == p_server)
                { 


                    if(st_kill != 0) 
                    {
                        Calculate_Health(st_kill, false, ply_id, false);
                        Calculate_Lifebar();
                        bump_player_timer  = (int)TimerGetTime() + BUMP_TIME;
                        bump_player = true; 
                    }
					 
                }   
                               
                // Spawn a pick-up  
                if(sprite[guy_shot].on_ladder == false) 
                if(guy_shot != p1_id && guy_shot != p2_id && guy_shot != p3_id && guy_shot != p4_id)
                {  
                             
					if(sprite[guy_shot].linked_sprite != player_type)
                    if(sprite[guy_shot].sector_action != AI_HUNT || ARCADE)        
                    if(sprite[guy_shot].sector != UNIT_SHOTGUN 
                    && sprite[guy_shot].sector != UNIT_MACHINE  
                    && sprite[guy_shot].sector != UNIT_GUARD 
                    && sprite[guy_shot].sector != UNIT_CHIEF     
                    && sprite[guy_shot].sector != UNIT_MONKEY 
					&& sprite[guy_shot].sector != UNIT_DECOY
                    && sprite[guy_shot].sector != UNIT_DOG)
                        Spawn_Pickup(guy_shot, ENEMY_DROP);  
                       
                } 
              
                if(sprite[guy_shot].type = UNT)
                { 
                
                if(guy_status != OPEN_CUT)              
                if(sprite[guy_shot].sector != UNIT_SKELETON 
                && sprite[guy_shot].sector != UNIT_BIRD
                && sprite[guy_shot].sector != UNIT_SHARK
                && sprite[guy_shot].sector != UNIT_DEAD_CHIEF
                && sprite[guy_shot].sector != UNIT_BOMBER
                && sprite[guy_shot].sector != UNIT_MONKEY
                && sprite[guy_shot].sector != UNIT_DOG
				&& sprite[guy_shot].sector != UNIT_DECOY
                && sprite[guy_shot].sector != UNIT_BOSS
                )           
                {  
                    if(guy_status != OPEN_CUT)    
                    {       
					    // Dieing sound effect
						if(sprite[guy_shot].grenaded == DEATH_HEADSHOT)
    	          	        Surround_Sound(guy_shot, SFX_SPLATTED, -1, -1);  
						else
						{
							if(sprite[guy_shot].linked_sprite != player_type)
								Surround_Sound(guy_shot, SFX_DEATH, -1, -1);  
							else
							{
								if(sta2_squad[sprite[guy_shot].value2].type == STA2_CO)
									Surround_Sound(guy_shot, SFX_DEATH_GIRL, -1, -1);
								else
									Surround_Sound(guy_shot, SFX_DEATH, -1, -1);
							}
						}

                    } 
                    else
						Surround_Sound(guy_shot, SFX_GARGLE, -1, -1);
                }  
                         
                if(guy_status != OPEN_CUT)
                if(sprite[guy_shot].sector == UNIT_BOMBER 
                && (sprite[guy_shot].onDeath_action == MOVABLE || sprite[guy_shot].onDeath_action == UNMOVABLE) )
                {
                    if(guy_status != OPEN_CUT)       
                    {        
					    	// Dieing sound effect
							if(sprite[guy_shot].grenaded == DEATH_HEADSHOT)
    	          	            Surround_Sound(guy_shot, SFX_SPLATTED, -1, -1);  
							else
	                            Surround_Sound(guy_shot, SFX_DEATH, -1, -1);
                    }
                    else
                        Surround_Sound(guy_shot, SFX_GARGLE, -1, -1);
                }            
                            
                if(sprite[guy_shot].sector == UNIT_BIRD) 
                    Surround_Sound(guy_shot, SFX_CROW1, -1, -1);

                if(sprite[guy_shot].sector == UNIT_SHARK)           
                    Surround_Sound(guy_shot, SFX_DESTROY, -1, -1);
                    
                if(guy_status != OPEN_CUT)    
                if(sprite[guy_shot].sector == UNIT_MONKEY) 
                    Surround_Sound(guy_shot, SFX_MONKEY, -1, -1);
                    
                if(guy_status != OPEN_CUT)    
                if(sprite[guy_shot].sector == UNIT_DOG) 
                    Surround_Sound(guy_shot, SFX_DOG, -1, -1); 
                
                if(sprite[guy_shot].sector == UNIT_SKELETON)           
                    Surround_Sound(guy_shot, SFX_DESTROY, -1, -1);

                if(sprite[guy_shot].sector == UNIT_DEAD_CHIEF)
                    Surround_Sound(guy_shot, SFX_DESTROY, -1, -1);               

                if(sprite[guy_shot].sector == UNIT_DECOY)   
				{        
                    Surround_Sound(guy_shot, SFX_DESTROY, -1, -1);
					Create_Gibs_Effect(guy_shot, false, -1); 
				}
                
                         
                if(sprite[guy_shot].sector == UNIT_MORTAR)
                { 
                //    New_FX(sprite[guy_shot].x-0.1f, sprite[guy_shot].y-0.1f, sprite[guy_shot].x, sprite[guy_shot].y, 37, PLAY, 0.1f, 0.1f, 0.4f, 0.6f, 1, GFX, 1.0f, 0, 0, FX_EXPLOSION, -1, 2, 0, 0, -1);
                //    New_FX(sprite[guy_shot].x-0.1f, sprite[guy_shot].y-0.1f, sprite[guy_shot].x, sprite[guy_shot].y, 113, PLAY, 0.1f, 0.1f, 0.4f, 0.6f, 1, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);
                    Surround_Sound(guy_shot, SFX_DESTROY, -1, -1);
                }
                if(sprite[guy_shot].sector == UNIT_BOMBER && (sprite[guy_shot].onDeath_action == TURRET || sprite[guy_shot].onDeath_action == TANK_TOP) ) 
                {
                //    New_FX(sprite[guy_shot].x-0.1f, sprite[guy_shot].y-0.1f, sprite[guy_shot].x, sprite[guy_shot].y, 37, PLAY, 0.1f, 0.1f, 0.4f, 0.6f, 1, GFX, 1.0f, 0, 0, FX_EXPLOSION, -1, 2, 0, 0, -1);
                //    New_FX(sprite[guy_shot].x-0.1f, sprite[guy_shot].y-0.1f, sprite[guy_shot].x, sprite[guy_shot].y, 113, PLAY, 0.1f, 0.1f, 0.4f, 0.6f, 1, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);
                    Surround_Sound(guy_shot, SFX_DESTROY, -1, -1);
                }
                    
                     
                }
                                                   
            }  
            
            sprite[guy_shot].moving = false; 
                                  
            Reset_Build_Types(guy_shot);     

            kill_count = 1;  
                        
            }  // == UNT    
            
            if(guy_status == UNIT_SQUASHED)                                                                
                Surround_Sound(guy_shot, SFX_DROWN, -1, -1);        
                   
            // Shot a Bag     
			if(guy_shot != -1)
            if(sprite[guy_shot].type == BAG)
            if(sprite[guy_shot].sector != UNIT_BOSS)
            if(sprite[guy_shot].grab_switch == true)  
            if(sprite[guy_shot].priority != 3)                
            {  
                                    
            //    sprite[guy_shot].anim_state = WAIT;
                sprite[guy_shot].update = true;          
                sprite[guy_shot].reload_timer = (int)TimerGetTime() + 100; 
                                     
				if(sprite[guy_shot].sector == UNIT_ARMOUR_TANK)
			    if(sprite[guy_shot].rank != 0 && sprite[guy_shot].rank > 0)  
				{
		             sprite[sprite[guy_shot].rank].flash_target = true;
		             sprite[sprite[guy_shot].rank].flash_timer = (int)TimerGetTime() + 30;
				}
 
                if(ply_id != -1)
				if(guy_shooting != -1)
                if(guy_shooting == ply_id || dm_game == DM_NONE)
                if(sprite[guy_shot].sector != UNIT_SIGNPOST)
                if(sprite[guy_shot].sector != UNIT_SEAGULL 
                && sprite[guy_shot].sector != UNIT_SEAGULL2)
                {
					if(HEALTHBARS == HEALTHBARS_ON)
						New_Healthbar(guy_shot, -1);
                }  
                 
                torso_targeted = targeted;  
                    
                if(ply_id != -1) 
                if(noise_type != LOUD_NOISE) 
                {

                    alert_enemies = true;
                    noise_type = SOFT_NOISE;  
                                    
                    noise_x = sprite[guy_shot].w+sprite[guy_shot].box_width/2;                        
                    noise_y = sprite[guy_shot].z+sprite[guy_shot].box_height/2;   
                }
                                    
                if(sprite[guy_shot].score <= 0)   
                {    
                                         
                //    exp_gain = 2;                       
                        
                    if(ply_id != -1)
					if(guy_shooting != -1)
                    if(guy_shooting == ply_id && player_type == p_server)
                    { 
                    //    Calculate_Exp(ply_id, exp_gain);  
                    } 
                    
                    if(ply_id != -1)                    
                    if(Level == LVL_TRAINING)
                    if(sprite[guy_shot].sector != UNIT_SIGNPOST)
                    { 
                             
                        success_condition++; 
                                               
                    }  
                     
					if(sprite[guy_shot].type == BAG && sprite[guy_shot].sector == UNIT_ARMOUR_TANK)
					{
					   exploding_id = guy_shot; 
                       exploding_timer = (int)TimerGetTime() + 100;
                       exploding_count=0;   
  
					   if(sprite[guy_shot].rank != 0 && sprite[guy_shot].rank > 0)  
					   {
							sprite[sprite[guy_shot].rank].alpha = 0.0; 
							sprite[sprite[guy_shot].rank].grab_switch = false;
							sprite[sprite[guy_shot].rank].mouseover = true;
							sprite[sprite[guy_shot].rank].score = 0;
					   }	

					}

                    if(Level == LVL_TRENCH_A || Level == LVL_TRENCH_B)
                        sprite[guy_shot].priority = 3; 
                    
                    if(sprite[guy_shot].sector == UNIT_SIGNPOST && sprite[guy_shot].sector_action == AI_DOOR)
					if(sprite[guy_shot].sector != UNIT_ARMOUR_TANK)
                        sprite[guy_shot].priority = 3;
                                        
                    mid_x = sprite[guy_shot].w+sprite[guy_shot].box_width/2; 
                    mid_y = sprite[guy_shot].z+sprite[guy_shot].box_height/2;  
                    
                    if(sprite[guy_shot].sector != UNIT_ARMOUR_TANK)
                    if(sprite[guy_shot].sector != UNIT_SEAGULL 
                    && sprite[guy_shot].sector != UNIT_SEAGULL2
					&& sprite[guy_shot].sector != UNIT_ARMOUR_TURRET) 
                        Generate_Object_Collision(guy_shot, REMOVE_COL);

                    // Mauser's small tanks 
                    if(sprite[guy_shot].sector == UNIT_ARMOUR_TURRET 
					&& sprite[guy_shot].rank == 0) 
                        Generate_Object_Collision(guy_shot, REMOVE_COL);
                                    

                    sprite[guy_shot].score = 0;  
                    sprite[guy_shot].grab_switch = false;   
                    
	                // Flash when they die...
	                sprite[guy_shot].dflash_timer = 1;
	                
	                sprite[guy_shot].flash_no_count=0;   
	                
	                sprite[guy_shot].death_flash  = true;                  
                    
                    if(sprite[guy_shot].sector == UNIT_ARMOUR_TURRET || sprite[guy_shot].sector == UNIT_ARMOUR_TANK ) 
                    {  
                        New_FX(mid_x-0.2f, mid_y-0.2f, mid_x, mid_y, 37, PLAY, 0.4f, 0.4f, 0.4f, 0.4f, 1, GFX, 1.0f, 0, 0, FX_EXPLOSION, -1, 2, 0, 0, -1);
                        New_FX(mid_x-0.2f, mid_y-0.2f, mid_x, mid_y, 113, PLAY, 0.4f, 0.4f, 0.4f, 0.4f, 1, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);

                        Set_Sprite(guy_shot, sprite[guy_shot].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING);
                        
                        if(sprite[guy_shot].sector != UNIT_ARMOUR_TANK) 
                            sprite[guy_shot].priority = 3;
                        else 
                        { 
                            Shell_Landed( sprite[guy_shot].x+sprite[guy_shot].width/2, sprite[guy_shot].y+sprite[guy_shot].height/2, sprite[guy_shot].linked_sprite, f_rate, -1, -1);
                            Shell_Landed( sprite[guy_shot].x+sprite[guy_shot].width/2, sprite[guy_shot].y+sprite[guy_shot].height/2, sprite[guy_shot].linked_sprite, f_rate, -1, -1);
                        }
                                                
                    } 
                    else
                    {
                        if(sprite[guy_shot].sector != UNIT_SEAGULL 
                        && sprite[guy_shot].sector != UNIT_SEAGULL2
                        && (sprite[guy_shot].sector != UNIT_SIGNPOST || sprite[guy_shot].sector_action != AI_DOOR)) 
                            Set_Sprite(guy_shot, sprite[guy_shot].base_anim+2, ONCE, ANIM_SPRITE, ANIM_WALKING);
                        else 
                            Set_Sprite(guy_shot, sprite[guy_shot].base_anim+1, ONCE, ANIM_SPRITE, ANIM_WALKING);
                    }
                    
                    if(sprite[guy_shot].sector != UNIT_BARREL)
                    {
                                                
                        if(sprite[guy_shot].rank ==4) // Mushroom
                            Surround_Sound(guy_shot, SFX_SPLATTED, -1, -1);                       
                                               
                        if(sprite[guy_shot].sector != UNIT_SEAGULL 
                        && sprite[guy_shot].sector != UNIT_SEAGULL2
                        && sprite[guy_shot].sector != UNIT_COW)
                        { 
                            if(sprite[guy_shot].rank !=4)                       
                                Surround_Sound(guy_shot, SFX_DESTROY, -1, -1); 
                            Create_Crate_Effect(guy_shot);
                        
                            Create_Gibs_Effect(guy_shot, false, -1);                             
                            
                        } 
                         
                        if(sprite[guy_shot].sector == UNIT_SEAGULL 
                        || sprite[guy_shot].sector == UNIT_SEAGULL2)
                        {
 
                            crow_kill_count++; 
                                                                                       
                            Surround_Sound(guy_shot, SFX_CROW, -1, -1);
                            
                        }    
                        if( sprite[guy_shot].sector == UNIT_COW)
                        {
                            Surround_Sound(guy_shot, SFX_COW, -1, -1);

                            Set_Sprite(guy_shot, sprite[guy_shot].base_anim+2, LOOP, ANIM_SPRITE, ANIM_WALKING);

                            if(Level == LVL_FARMS)
                                cow_kill_count++;
                                
                        }
                    }
                    else    
                    {   
                         
                        if(sprite[guy_shot].onDeath_action == BOSS_SHELL)  
                            Shell_Landed( sprite[guy_shot].x+sprite[guy_shot].width/2, sprite[guy_shot].y+sprite[guy_shot].height/4, sprite[guy_shot].linked_sprite, f_rate, INV_BOSS_SHELL, -1);
                        if(sprite[guy_shot].onDeath_action == BARREL_BOMB)  
                            Shell_Landed( sprite[guy_shot].x+sprite[guy_shot].width/2, sprite[guy_shot].y+sprite[guy_shot].height/4, sprite[guy_shot].linked_sprite, f_rate, INV_BARREL_BOMB, -1);
                        if(sprite[guy_shot].onDeath_action != BOSS_SHELL && sprite[guy_shot].onDeath_action != BARREL_BOMB)  
                            Shell_Landed( sprite[guy_shot].x+sprite[guy_shot].width/2, sprite[guy_shot].y+sprite[guy_shot].height/4, sprite[guy_shot].linked_sprite, f_rate, -1, -1);
                        
                        if(sprite[guy_shot].onDeath_action != TANK_TOP)
                            sprite[guy_shot].priority = 3;
                              
                    }  
                    
                }
                else 
                {
                    if(sprite[guy_shot].sector != UNIT_ARMOUR_TURRET)
                    if(sprite[guy_shot].sector != UNIT_ARMOUR_TANK)
                    { 
                        if(sprite[guy_shot].sector != UNIT_ARMOUR_HEAD
                        && sprite[guy_shot].sector != UNIT_ARMOUR_FULL
                        && sprite[guy_shot].sector != UNIT_COW
                        )
                            Set_Sprite(guy_shot, sprite[guy_shot].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING);
                            
                        if(sprite[guy_shot].sector == UNIT_ARMOUR_HEAD)
                        if(torso_targeted == TARGET_HEAD || torso_targeted == TARGET_LEGS || guy_status == OPEN_CUT)
                            Set_Sprite(guy_shot, sprite[guy_shot].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING);
                            
                        if(sprite[guy_shot].sector == UNIT_ARMOUR_FULL)
                        if(guy_status == OPEN_CUT)
                            Set_Sprite(guy_shot, sprite[guy_shot].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING);
                            
                        if(sprite[guy_shot].sector == UNIT_COW)
                        {
                            Surround_Sound(guy_shot, SFX_COW, -1, -1); 
                            Set_Sprite(guy_shot, sprite[guy_shot].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING);                            
                        }
                        
                    }
                                         
                }
                
            }        
                              
            if(sprite[guy_shot].type == DOR)
            if(sprite[guy_shot].grab_switch == true)
            if(sprite[guy_shot].priority != 3)
            {  
  			                         
                // Flash when they die...
                sprite[guy_shot].dflash_timer = 1;
                
                sprite[guy_shot].flash_no_count=0;   
                
                sprite[guy_shot].death_flash  = true;   
	                
                if(sprite[guy_shot].sector_action != TYPE_TREE
                && sprite[guy_shot].sector_action != TYPE_GOLDTREE)                     
                {
                                                   
                Set_Sprite(guy_shot, sprite[guy_shot].anim+1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING);

                mid_x = sprite[guy_shot].w+sprite[guy_shot].box_width/2; 
                mid_y = sprite[guy_shot].z+sprite[guy_shot].box_height/2;  
                 
                row_x = (int)((mid_x + map_startX)*10);      
                row_y = (int)((mid_y + map_startY)*10);   
               
                map_col[(row_y*MAP_HEIGHT)+row_x] = 0;    
             
                // Double Doors
                if(sprite[guy_shot].type == DOR && sprite[guy_shot].sector_action == TYPE_DOUBLE)
                    map_col[((row_y+1)*MAP_HEIGHT)+(row_x+1)] = 0;
                if(sprite[guy_shot].type == DOR && sprite[guy_shot].sector_action == TYPE_DOUBLE_BACK)
                    map_col[((row_y+1)*MAP_HEIGHT)+(row_x-1)] = 0;
 
                sprite[guy_shot].score = 0; 
                sprite[guy_shot].priority = 3;
                sprite[guy_shot].grab_switch = false;  
                
                Surround_Sound(guy_shot, SFX_SMASH, -1, -1);   
                                                   
                exp_gain = 2;                        
                 
                if(ply_id != -1)
				if(guy_shooting != -1)
                if(guy_shooting == ply_id && player_type == p_server)
                { 
                    Calculate_Exp(ply_id, exp_gain);  
                } 
                // KRAK effect
                New_FX(sprite[guy_shot].x, sprite[guy_shot].y, sprite[guy_shot].x, sprite[guy_shot].y, 87, PLAY, sprite[guy_shot].width, sprite[guy_shot].height, sprite[guy_shot].width, sprite[guy_shot].height, 1, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);
                
                Create_Gibs_Effect(guy_shot, false, -1);
                
                }                 
                else
                    sprite[guy_shot].score = 1;
                    
                if(sprite[guy_shot].sector_action == TYPE_TREE)
                {
                    Spawn_Pickup(guy_shot, TREE_DROP); 
                    mouseleft = false;
                    mouseheld = false;
             //       Set_Sprite(guy_shot, sprite[guy_shot].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                    
                } 
                 
                if(sprite[guy_shot].sector_action == TYPE_DOUBLE
                || sprite[guy_shot].sector_action == TYPE_DOUBLE_BACK
                || sprite[guy_shot].sector_action == TYPE_SINGLE_DOOR)
                {
                    Create_Crate_Effect(guy_shot);  
                                                
                    if(Level == LVL_VILLAGE)
                        doors_kill_count++;
                         
                }
                
                if(Level == LVL_FARMS)                
                if(sprite[guy_shot].sector_action == TYPE_DOUBLE_BACK)
                    gate_kill_count++;
                       
                if(sprite[guy_shot].sector_action == TYPE_TREE)
                {
                    Spawn_Pickup(guy_shot, TREE_DROP); 
                    mouseleft = false;
                    mouseheld = false;
             //       Set_Sprite(guy_shot, sprite[guy_shot].base_anim, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                    
                }  
                    
                if(sprite[guy_shot].sector_action == TYPE_GOLDTREE && sprite[guy_shot].anim == sprite[guy_shot].base_anim)
                {
                    Spawn_Pickup(guy_shot, GOLDTREE_DROP); 
                    mouseleft = false;
                    mouseheld = false;
                    Set_Sprite(guy_shot, sprite[guy_shot].base_anim-2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                }       
 
                if(sprite[guy_shot].sector_action == TYPE_CHEST)
                {
                    sprite[guy_shot].priority = 3;    
                    Spawn_Pickup(guy_shot, CHEST_DROP); 

					if(Level == LVL_PIRATE)  
	                    global_objects[0] = GLOBAL_BEATEN; 

					if(Level == LVL_PIRATE1)  
	                    global_objects[2] = GLOBAL_BEATEN;  

                    player_crate_count++;
                    Create_Crate_Effect(guy_shot);
                }  
                if(sprite[guy_shot].sector_action == TYPE_APPLE)
                {
                    sprite[guy_shot].priority = 3;  
                                                           
                    player_crate_count++; 
                    Create_Crate_Effect(guy_shot);
                }                  
                if(sprite[guy_shot].sector_action == TYPE_AMMO)
                {
                    sprite[guy_shot].priority = 3;   
                    Spawn_Pickup(guy_shot, AMMO_DROP);   
                    player_crate_count++; 
                    Create_Crate_Effect(guy_shot);                    
                } 
                if(sprite[guy_shot].sector_action == TYPE_GRENADE)
                {
                    sprite[guy_shot].priority = 3;   
                    Spawn_Pickup(guy_shot, GRENADE_DROP);   
                    player_crate_count++;
                    Create_Crate_Effect(guy_shot);                    
                }     
                if(sprite[guy_shot].sector_action == TYPE_SUBMARINE)
                { 
                    sprite[guy_shot].priority = 3;   
                    Spawn_Pickup(guy_shot, SUBMARINE_DROP);   
                    player_crate_count++;
                    Create_Crate_Effect(guy_shot);                    
                }       
                if(sprite[guy_shot].sector_action == TYPE_BAD_POETRY)
                { 
                    sprite[guy_shot].priority = 3;    

                    if(ply_id != -1)
						Display_Message(ply_id, MSG_POETRY);  

                    player_crate_count++;
                    Create_Crate_Effect(guy_shot);                    
                }      

				// Arcade stuff...
                if(sprite[guy_shot].sector_action == TYPE_MAIN_DROP)
                { 
					Spawn_Pickup(guy_shot, ARCADE_MAIN_DROP);
				}
                if(sprite[guy_shot].sector_action == TYPE_SECOND_DROP)
                {
					Spawn_Pickup(guy_shot, ARCADE_SECOND_DROP);
				}

                if(sprite[guy_shot].sector_action == TYPE_AMMO_RIFLE 
                || sprite[guy_shot].sector_action == TYPE_BARREL)
                { 
                    sprite[guy_shot].priority = 3;    
                    player_crate_count++;    

					if(sprite[guy_shot].sector_action == TYPE_AMMO_RIFLE)
					{
                        if(player_crate_count%15 == 0)
                            Spawn_Pickup(guy_shot, SUPER_CRATE_DROP);  
                        else
                            Spawn_Pickup(guy_shot, AMMO_DROP_RIFLE);  
					}
					else    
					{ 
						if(rand()%7 == 0 && Level != LVL_AIRFIELD)
							Spawn_A_Guy(1, -1, false, false, guy_shot, -1);
						else
						    Spawn_Pickup(guy_shot, AMMO_DROP_RIFLE);
					}
                        
                    Create_Crate_Effect(guy_shot);                    
                }                                 
                if(sprite[guy_shot].sector_action == TYPE_DOCK)
                {
                    sprite[guy_shot].priority = 3;   
                    Spawn_Pickup(guy_shot, DOCK_DROP);  
                    player_crate_count++;
                    Create_Crate_Effect(guy_shot);                    
                }                 
                if(sprite[guy_shot].sector_action == TYPE_HEALTH)
                { 
                    sprite[guy_shot].priority = 3;   
                    Spawn_Pickup(guy_shot, HEALTH_DROP);  
                    player_crate_count++;
                    Create_Crate_Effect(guy_shot);                    
                }   
                if(sprite[guy_shot].sector_action == TYPE_SPARE_A)
                {
                    sprite[guy_shot].priority = 3;   
                    player_crate_count++;
                    if(Has_This_Item(INV_LETTERS, 0)==false)
                    { 
                        Spawn_Pickup(guy_shot, SPARE_DROP_A); 
                        if(ply_id != -1)
                        Display_Message(ply_id, MSG_DELIVER);     
                    } 
                    if(ply_id != -1)
                    Display_Message(ply_id, MSG_DELIVER);      
                    Create_Crate_Effect(guy_shot);    
                }   
                if(sprite[guy_shot].sector_action == TYPE_SPARE_B)
                {
                    sprite[guy_shot].priority = 3;    
                    player_crate_count++;
                    if(Has_This_Item(INV_LETTERS, 1)==false)
                    { 
                        Spawn_Pickup(guy_shot, SPARE_DROP_B); 
                        if(ply_id != -1)
                        Display_Message(ply_id, MSG_DELIVER);     
                    }
                    Create_Crate_Effect(guy_shot);                     
                }    
                if(sprite[guy_shot].sector_action == TYPE_SPARE_C)
                {
                    sprite[guy_shot].priority = 3;   
                    player_crate_count++;
                    if(Has_This_Item(INV_LETTERS, 2)==false)
                    { 
                        Spawn_Pickup(guy_shot, SPARE_DROP_C); 
                        if(ply_id != -1)
                        Display_Message(ply_id, MSG_DELIVER);     
                    } 
                    Create_Crate_Effect(guy_shot);                    
                }   
                                                                                                             
                // Get the nearest ROOM_PNT 
                if(sprite[guy_shot].sector_action != TYPE_BARREL && sprite[guy_shot].sector_action != TYPE_CHEST
                && sprite[guy_shot].rank == 0 && sprite[guy_shot].sector_action != TYPE_DOCK)
                for(int i=0;i<no_points;i++) 
                if(points[i].c1 == ROOM_PNT || points[i].c1 == ROOM1_PNT
                || points[i].c1 == GENERAL_PNT) 
                {    
                                     
                    tar_x = points[i].x; 
                    tar_y = points[i].y;   
                    
                    dis_to_point = Node_Distance(mid_x, mid_y, tar_x, tar_y); 
                    
                    if( dis_to_point < closest_point)
                    {
                        best_point = i;
                        closest_point = dis_to_point;    
                    } 
                
                }  
                
                if(sprite[guy_shot].sector_action != TYPE_BARREL && sprite[guy_shot].sector_action != TYPE_CHEST
                && sprite[guy_shot].rank == 0 && sprite[guy_shot].sector_action != TYPE_DOCK)                
                if(best_point != -1)
                if(points[best_point].active == 1)
                {
                  
                  points[best_point].active = 0;
                      
                  rnd = rand()%4;    
                  
                  if(points[best_point].c1 == GENERAL_PNT)
                      rnd = 101; 
                      
                  if(rnd != 0) 
                      Spawn_A_Guy(rnd, best_point, false, false, -1, -1);                 
                    
                }   
                 
            }
 
            sprite[guy_shot].selected = false;   
            
        }
   } 
   
   if(lock_player == false || guy_shot != ply_id)  
   if(no_damage == false && guy_shot != -1)
   if(sprite[guy_shot].type == UNT) 
   if(sprite[guy_shot].sector != UNIT_MORTAR || targeted != TARGET_LEGS)
   if(sprite[guy_shot].score > 0 )
   if(sprite[guy_shot].status != MERCY && sprite[guy_shot].status != MERCY1)           
   {   
  
        if(sprite[guy_shot].building == false)     
        {   
            
             if(ply_id != -1)
			 if(guy_shooting != -1)
             if(guy_shooting == ply_id && targeted == TARGET_LEGS)
             if(has_pistol_equipped == true) 
             {   
                 
                 mid_x = sprite[guy_shot].w+sprite[guy_shot].box_width/2; 
                 mid_y = sprite[guy_shot].z+sprite[guy_shot].box_height/2;
  
             }
             
             if(guy_shot != -1)
			 if(guy_shooting != -1)
             if(sprite[guy_shooting].sector == UNIT_HEAVY && sta2_turn == TURN_COMPUTER)
                 skip_stunned=true;   

            if(guy_shot != -1)
			if(sprite[guy_shot].sector == UNIT_DECOY)
                 skip_stunned=true; 	 			
                
            if(ply_id != -1) 
            if(shot_hit_armour == false) // For shield guys
            if(sprite[guy_shot].status != STUNNED)  
            {  
                if(skip_stunned == false)                       
	            if(sprite[guy_shot].sector != UNIT_SHOTGUN && sprite[guy_shot].sector != UNIT_MACHINE && sprite[guy_shot].sector != UNIT_GUARD)  
                if(bullet_type != BULLET_FIRE  && bullet_type != BULLET_FIRE1
				&& bullet_type != BULLET_FIRE2 && bullet_type != BULLET_FIRE3 
				&& bullet_type != BULLET_GAS)                        
                    Rank_Timer(guy_shot, STUNNED);  
				if(HEALTHBARS == HEALTHBARS_ON)
				    New_Healthbar(guy_shot, -1); 

            }
                
            if(sprite[guy_shot].sector == UNIT_SHOTGUN || sprite[guy_shot].sector == UNIT_MACHINE || sprite[guy_shot].sector == UNIT_GUARD)
            if(bullet_type != BULLET_FIRE  && bullet_type != BULLET_FIRE1
			&& bullet_type != BULLET_FIRE2 && bullet_type != BULLET_FIRE3 
			&& bullet_type != BULLET_GAS)  
            if(guy_shot != ply_id)  
            { 
				if(HEALTHBARS == HEALTHBARS_ON)
					New_Healthbar(guy_shot, -1);
            }       

            if(bullet_type != BULLET_FIRE  && bullet_type != BULLET_FIRE1
			&& bullet_type != BULLET_FIRE2 && bullet_type != BULLET_FIRE3 
			&& bullet_type != BULLET_GAS)  
            if(sprite[guy_shot].sector != UNIT_SHOTGUN && sprite[guy_shot].sector != UNIT_MACHINE && sprite[guy_shot].sector != UNIT_GUARD)
			if(sprite[guy_shot].sector != UNIT_DECOY)
            if(shot_hit_armour == false) 
            if(skip_stunned == false)
            if(sprite[guy_shot].status != RELOADING_GUN)
                sprite[guy_shot].status = STUNNED; 
			    
            if(ply_id != -1)    
            if((guy_shot == ply_id && player_type == p_server) )
            {
                Calculate_Lifebar();                      
            }       
      
            if(bullet_type != BULLET_FIRE  && bullet_type != BULLET_FIRE1
			&& bullet_type != BULLET_FIRE2 && bullet_type != BULLET_FIRE3 
			&& bullet_type != BULLET_GAS)  
            if(ply_id != -1 && guy_shot != -1)
			if(sprite[guy_shot].sector != UNIT_DECOY)
            if(skip_stunned == false)
            if(shot_hit_armour == false) // For shield guys 
            {      
                               
                if(torso_targeted == TARGET_LEGS 
				&& (sprite[guy_shot].sector != UNIT_MONKEY && sprite[guy_shot].sector != UNIT_DOG && sprite[guy_shot].sector != UNIT_BOX) 
				&& guy_shot != ply_id 
				&& (guy_shot != p1_buddy || buddy_in_water == false) )  
                {
          
                    sprite[guy_shot].status = FOOT_SHOT;   
                    Rank_Timer(guy_shot, FOOT_SHOT); 

					New_FX(sprite[guy_shot].x, sprite[guy_shot].y,  sprite[guy_shot].x, sprite[guy_shot].y, 6, LOOP, sprite[guy_shot].width, sprite[guy_shot].height, sprite[guy_shot].width, sprite[guy_shot].height, 2, GFX, 1.0f, 0, 0, FX_STUNNED, guy_shot, 2, 0, 0, 0);

                    
                    if(bullet_type == BULLET_SHOTGUN_LONG) 
                        sprite[guy_shot].all_timer = (int)TimerGetTime() + 500;   
                 
                }      
                if(torso_targeted == TARGET_LEGS && guy_shot == ply_id)
                { 
                    sprite[guy_shot].status = STUNNED;
                    Rank_Timer(guy_shot, STUNNED);                 
                } 
                if(torso_targeted == TARGET_LEGS && sprite[guy_shot].sector == UNIT_MONKEY)
                { 
                    sprite[guy_shot].status = STUNNED;
                    Rank_Timer(guy_shot, STUNNED);                 
                } 
                if(torso_targeted == TARGET_LEGS && sprite[guy_shot].sector == UNIT_DOG)
                { 
                    sprite[guy_shot].status = STUNNED;
                    Rank_Timer(guy_shot, STUNNED);                 
                }                 
                if(torso_targeted == TARGET_LEGS && sprite[guy_shot].sector == UNIT_BOX)
                { 
                    sprite[guy_shot].status = STUNNED;
                    Rank_Timer(guy_shot, STUNNED);                 
                }                                    
            } 
            
            if(sprite[guy_shot].sector == UNIT_BIRD)  
                Surround_Sound(guy_shot, SFX_CROW, -1, -1); 
            
            if(sprite[guy_shot].sector == UNIT_MONKEY)
                Surround_Sound(guy_shot, SFX_MONKEY, -1, -1);
            
            if(sprite[guy_shot].sector == UNIT_DOG)
                Surround_Sound(guy_shot, SFX_DOG, -1, -1);
          
            if(sprite[guy_shot].sector != UNIT_BIRD 
            && sprite[guy_shot].sector != UNIT_SKELETON
            && sprite[guy_shot].sector != UNIT_SHARK
            && sprite[guy_shot].sector != UNIT_MORTAR  
            && sprite[guy_shot].sector != UNIT_MONKEY 
            && sprite[guy_shot].sector != UNIT_DOG          
            && sprite[guy_shot].sector != UNIT_DEAD_CHIEF
            )
            { 
			/*    if(bullet_type == BULLET_GAS)
			        cough_sfx = true; 
			 //   else 
                if(bullet_type != BULLET_FIRE  && bullet_type != BULLET_FIRE1
				&& bullet_type != BULLET_FIRE2 && bullet_type != BULLET_FIRE3 
				&& bullet_type != BULLET_GAS)  
				if(rand()%4 == 0) 
                    Surround_Sound(guy_shot, SFX_TADA, -1, -1); 
				else  
                    Surround_Sound(guy_shot, SFX_EMYPAIN, -1, -1); */    

					if(sprite[guy_shot].linked_sprite != player_type)
						Surround_Sound(guy_shot, SFX_PAIN, -1, -1);  
					else
					{
						if(sprite[guy_shot].value2 != -1)
						if(sta2_squad[sprite[guy_shot].value2].type == STA2_CO)
							Surround_Sound(guy_shot, SFX_PAIN_GIRL, -1, -1);
						else
							Surround_Sound(guy_shot, SFX_PAIN, -1, -1);
					} 
		    }
               
            // Turn to face attacker, etc    
			if(sprite[guy_shot].moving == false) 
            if(bullet_type != BULLET_FIRE  && bullet_type != BULLET_FIRE1
			&& bullet_type != BULLET_FIRE2 && bullet_type != BULLET_FIRE3 
			&& bullet_type != BULLET_GAS && bullet_type != BULLET_BARREL_BOMB)  
        /*    if(bullet_type != BULLET_GRENADE && bullet_type != BULLET_ARTILLERY
			&& bullet_type != BULLET_GREEN_GRENADE && bullet_type != BULLET_BLACK_GRENADE
			&& bullet_type != MOLOTOV_GRENADE) */
            if(guy_shot != guy_shooting && guy_shooting >= 0 && guy_shot >= 0) // guy_shot != ply_id && 
            {
                sprite[guy_shot].mov_x = sprite[guy_shooting].w+sprite[guy_shooting].box_width/2;
                sprite[guy_shot].mov_y = sprite[guy_shooting].z+sprite[guy_shooting].box_height/2;
                
                sprite[guy_shot].end_x = sprite[guy_shot].mov_x;
                sprite[guy_shot].end_y = sprite[guy_shot].mov_y;
                
                sprite[guy_shot].turning = false;
                
                sprite[guy_shot].fire_target = guy_shooting;
                     
            } 
             
        }     
        
    }     

    if(skip_stunned == false) 
    if(lock_player == false || guy_shot != ply_id)
    { 
        sprite[guy_shot].update = true;
     
        if(sprite[guy_shot].type != BAG && sprite[guy_shot].type != DOR)
		if(sprite[guy_shot].sector != UNIT_DECOY || sprite[guy_shot].score <= 0)           
            sprite[guy_shot].anim_state = WAIT; 
    } 

    overshot = false;

    return(hit_a_building);
     
}

int Convert_Dir_To_Angle(int loop, int direction)
{

	if(loop < 0)
		return(0);

	if(loop >= 0) 
	{

		if(direction == DOWN)
			sprite[loop].angle = -1.5f; 
		if(direction == UP)
			sprite[loop].angle = 1.5f;
		if(direction == LEFT)
			sprite[loop].angle = -3.0f;
		if(direction == RIGHT)
			sprite[loop].angle = 0.0f;  
		if(direction == UP_RIGHT)
			sprite[loop].angle = 0.75f;
		if(direction == UP_LEFT)
			sprite[loop].angle = 2.25f;
		if(direction == DOWN_RIGHT)
			sprite[loop].angle = -0.75f;
		if(direction == DOWN_LEFT)
			sprite[loop].angle = -2.25f; 
        
		sprite[loop].tar_angle = sprite[loop].angle;
        
		sprite[loop].mov_x = (sprite[loop].w + sprite[loop].box_width/2) + (cos(sprite[loop].angle)*2.0f);    
		sprite[loop].mov_y = sprite[loop].y + (sin(sprite[loop].angle)*2.0f);
   	
		if( sprite[loop].mov_x  < -map_startX || sprite[loop].mov_x  >  map_startX  || sprite[loop].mov_y < -map_startY || sprite[loop].mov_y >  map_startY  )
		{
			sprite[loop].mov_x = (sprite[loop].w + sprite[loop].box_width/2);
			sprite[loop].mov_y = (sprite[loop].z + sprite[loop].box_height/2); 
		}

	//	if(game_mode == WALK)
	//		Animation_System(loop, BULLET_CHECK_OFF, INTERRUPT_OFF, PAIN_ANIM_OFF, FIRE_OFF);

	} 

	return 0;
              
}

int Is_Guy_In_Sight(float my_angle, float target_angle)
{
    int success=false;
    int i_my_angle=0;
    int i_target_angle=0; 
    
    if(my_angle >= -1.875f && my_angle <= -1.125f) // DOWN
    {    
        i_my_angle = DOWN;     
    }
    if(my_angle <= 1.875f && my_angle >= 1.125f) // UP
    {
        i_my_angle = UP;     
    }        
    if(my_angle >= 2.625f || my_angle <= -2.625f) // RIGHT
    {   
        i_my_angle = LEFT;     
    }
    if(my_angle <= 0.375f && my_angle >= -0.375f) // LEFT
    { 
        i_my_angle = RIGHT;      
    }  
    if(my_angle >= -2.625f && my_angle <= -1.875f) 
    {
        i_my_angle = DOWN_LEFT;     
    }
    if(my_angle >= -1.125f && my_angle <= -0.375f)  // DOWN LEFT/RIGHT
    {
        i_my_angle = DOWN_RIGHT;     
    }
    if(my_angle >= 1.875f && my_angle <= 2.625f)
    {
        i_my_angle = UP_LEFT;                            
    }
    if(my_angle <= 1.125f && my_angle >= 0.375f) // UP LEFT/RIGHT
    {      
        i_my_angle = UP_RIGHT;                            
    }
    
    
    if(target_angle >= -1.875f && target_angle <= -1.125f) // DOWN
    {    
        i_target_angle = DOWN;     
    }
    if(target_angle <= 1.875f && target_angle >= 1.125f) // UP
    {
        i_target_angle = UP;     
    }        
    if(target_angle >= 2.625f || target_angle <= -2.625f) // RIGHT
    {   
        i_target_angle = LEFT;     
    }
    if(target_angle <= 0.375f && target_angle >= -0.375f) // LEFT
    { 
        i_target_angle = RIGHT;      
    }  
    if(target_angle >= -2.625f && target_angle <= -1.875f) 
    {
        i_target_angle = DOWN_LEFT;     
    }
    if(target_angle >= -1.125f && target_angle <= -0.375f)  // DOWN LEFT/RIGHT
    {
        i_target_angle = DOWN_RIGHT;     
    }
    if(target_angle >= 1.875f && target_angle <= 2.625f)
    {
        i_target_angle = UP_LEFT;                            
    }
    if(target_angle <= 1.125f && target_angle >= 0.375f) // UP LEFT/RIGHT
    {      
        i_target_angle = UP_RIGHT;                            
    }     
   
/*    if(i_my_angle == UP && (i_target_angle == DOWN || i_target_angle == DOWN_LEFT || i_target_angle == DOWN_RIGHT) )
        success = false;
    if(i_my_angle == DOWN && (i_target_angle == UP || i_target_angle == UP_LEFT || i_target_angle == UP_RIGHT) )
        success = false;
    if(i_my_angle == LEFT && (i_target_angle == RIGHT || i_target_angle == DOWN_RIGHT || i_target_angle == UP_RIGHT) )
        success = false;
    if(i_my_angle == RIGHT && (i_target_angle == LEFT || i_target_angle == DOWN_LEFT || i_target_angle == UP_LEFT) )
        success = false; 
 
    if(i_my_angle == DOWN_LEFT && (i_target_angle == UP_RIGHT || i_target_angle == UP || i_target_angle == RIGHT) )
        success = false;
    if(i_my_angle == DOWN_RIGHT && (i_target_angle == UP_LEFT || i_target_angle == UP || i_target_angle == LEFT) )
        success = false;
    if(i_my_angle == UP_LEFT && (i_target_angle == DOWN_RIGHT || i_target_angle == DOWN || i_target_angle == RIGHT) )
        success = false;
    if(i_my_angle == UP_RIGHT && (i_target_angle == DOWN_LEFT || i_target_angle == DOWN || i_target_angle == LEFT) )
        success = false;    */
        
    if(i_my_angle == UP && (i_target_angle == UP || i_target_angle == UP_LEFT || i_target_angle == UP_RIGHT || i_target_angle == RIGHT || i_target_angle == LEFT) )
        success = 2;
    if(i_my_angle == DOWN && (i_target_angle == DOWN || i_target_angle == DOWN_LEFT || i_target_angle == DOWN_RIGHT || i_target_angle == RIGHT || i_target_angle == LEFT) ) 
        success = 2;
    if(i_my_angle == LEFT && (i_target_angle == LEFT || i_target_angle == DOWN_LEFT || i_target_angle == UP_LEFT || i_target_angle == UP || i_target_angle == DOWN) )
        success = 2;
    if(i_my_angle == RIGHT && (i_target_angle == RIGHT || i_target_angle == DOWN_RIGHT || i_target_angle == UP_RIGHT || i_target_angle == UP || i_target_angle == DOWN) )
        success = 2;  
        
    if(i_my_angle == DOWN_LEFT && (i_target_angle == DOWN_LEFT || i_target_angle == DOWN || i_target_angle == LEFT || i_target_angle == DOWN_RIGHT || i_target_angle == UP_LEFT) )
        success = 2;
    if(i_my_angle == DOWN_RIGHT && (i_target_angle == DOWN_RIGHT || i_target_angle == DOWN || i_target_angle == RIGHT || i_target_angle == DOWN_LEFT || i_target_angle == UP_RIGHT) )
        success = 2;
    if(i_my_angle == UP_LEFT && (i_target_angle == UP_LEFT || i_target_angle == UP || i_target_angle == LEFT || i_target_angle == DOWN_LEFT || i_target_angle == UP_RIGHT) )
        success = 2;
    if(i_my_angle == UP_RIGHT && (i_target_angle == UP_RIGHT || i_target_angle == UP || i_target_angle == RIGHT || i_target_angle == DOWN_RIGHT || i_target_angle == UP_LEFT) )
        success = 2; 
                                                                                       
    return(success); 
     
}
void Test_Fx_to_Fx(int loop, int f_rate)
{
     
    float midX =0.0f, midY =0.0f;
    float tarX =0.0f, tarY =0.0f;
    bool test_success=false;
    float closest_point = 0.0f; 
    float dis_to_point = 0.0f;
    int index=0; 

	if(loop < 0)
		return;

	if(f_rate <= 0)
	    f_rate = 1; 
        
    midX = Fx[loop].w+Fx[loop].box_width/2;
    midY = Fx[loop].z+Fx[loop].box_height/2;     
    
    for(int k=0;k<no_fx;k++)  
    {
        if(Fx[k].turn_off == false)       
        if(Fx[k].sector == FX_GAS) 
        {
            tarX = Fx[k].w + Fx[k].box_width/2;
            tarY = Fx[k].z + Fx[k].box_height/2; 
        
            closest_point = 0.2f;
        
            dis_to_point = Node_Distance(midX, midY, tarX, tarY);         
         
            if( dis_to_point < closest_point)                          
            {
                Fx[k].turn_off = true;
                Fx[loop].turn_off = true;
                Shell_Landed( Fx[k].x, Fx[k].y, Fx[k].linked_sprite, f_rate, -1, -1);    
            }   
                     
        }            
    }

            
}

void Test_Sprite_to_Fx(int loop, int f_rate)
{
     
    float midX =0.0f, midY =0.0f;
    float tarX =0.0f, tarY =0.0f;
    bool test_success=false;
    float closest_point = 0.0f; 
    float dis_to_point = 0.0f;
	float closest_DXpoint = 10000.0f; 
    int index=0; 
	float range=0.0f;

	if(loop < 0)
		return;

	if(f_rate <= 0) 
	    f_rate = 1; 
        
    midX = sprite[loop].w+sprite[loop].box_width/2;
    midY = sprite[loop].z+sprite[loop].box_height/2;   
	 
	if(CONTROLLER)
	if(loop == ply_id && ply_id != -1)
	for(int k=0;k<no_fx;k++)    
	{
	    range = (float)COLLECT_RANGE; 
                        
		tarX = Fx[k].x + 0.05f;  
		tarY = Fx[k].y + 0.05f;    
                         
		dis_to_point = Node_Distance1(midX, midY, tarX, tarY);  
		
		if(Fx[k].alpha != 0.0f)
		if(Fx[k].turn_off == false && k != -1)  
		if(Fx[k].type == PKU || Fx[k].item_type == INV_MINE) 
		if(Fx[k].item_type != INV_GOLD || AUTO_PICKUP_GOLD == GOLD_AUTO_OFF)
		if(dis_to_point <= range && dis_to_point < closest_DXpoint) 
		{
			closest_DXpoint = dis_to_point;     
			 
			DXPick_Up=k; 
		}

	}


    for(int k=0;k<no_fx;k++)     
    { 

	if(AUTO_PICKUP_GOLD == GOLD_AUTO_ON) 
    if(ply_id != -1)
	if(loop == ply_id)  
	if(Fx[k].type == PKU)   
	if(Fx[k].turn_off == false) 
	if(Fx[k].item_type == INV_GOLD)  
	if(Pickup_Check(ply_id, k, STAND_AND_COLLECT))	
	{
        DXPick_Up=-1;  
		DXJustCollected=true;
	}

	if(CONTROLLER)
    if(ply_id != -1) 
	if(loop == ply_id)   
	if(Fx[k].type == PKU || Fx[k].item_type == INV_MINE)  
	if(Fx[k].turn_off == false)  
	if(DX_USECOLLECT == true)
	if(DXPick_Up == -1 || k == DXPick_Up)
	{
        if(Pickup_Check(ply_id, k, STAND_AND_COLLECT))
		{
			DX_USECOLLECT=false;
			DXPick_Up=-1; 
			DXJustCollected=true;
		}
	}

       
    if(ply_id != -1)
    if(sprite[loop].type != OBJ) 
    if(!(sprite[loop].sector == UNIT_DEAD_CHIEF && sprite[loop].type == UNT))
    if(!(sprite[loop].sector == UNIT_SKELETON && sprite[loop].type == UNT))
    if(!(sprite[loop].sector == UNIT_BOSS && sprite[loop].type == UNT))
    if(Fx[k].turn_off == false)   
    if(sprite[loop].grab_switch == true)    
    if(Fx[k].sector == FX_FIRE || Fx[k].sector == FX_FIRE1 || Fx[k].sector == FX_GAS)  
    if((int)TimerGetTime() > Fx[k].action_timer || Fx[k].action_timer == 101)
    {
        tarX = Fx[k].w + Fx[k].box_width/2;
        tarY = Fx[k].z + Fx[k].box_height/2; 
    
        closest_point = Fx[k].box_width/2 + sprite[loop].box_width/2;
    
        dis_to_point = Node_Distance(midX, midY, tarX, tarY);          
        
	    if(ply_id != -1)   
        if( dis_to_point < closest_point)     
        if(sprite[loop].score > 0)       
        {  
            if(Fx[k].sector == FX_FIRE)     
            {    
                if(loop != ply_id)              
                    Man_Shot(-1, loop, -1, BULLET_FIRE, f_rate);  
                if(loop == ply_id)
                {
                    if(has_firevest_equipped == false )
                        Man_Shot(-1, loop, -1, BULLET_FIRE, f_rate);
                }
				// Move buddy somewhere else.. 
				if(loop == p1_buddy) 
			//	if(sprite[loop].moving == false)
				{
					sprite[loop].mov_x = (sprite[loop].w+sprite[loop].box_width/2); 
					sprite[loop].mov_y -= (sprite[loop].z+sprite[loop].box_height/2)-0.12f; 
					  
					sprite[loop].end_x = sprite[loop].mov_x;
					sprite[loop].end_y = sprite[loop].mov_y; 

					Find_Path(loop, sprite[loop].end_x, sprite[loop].end_y);

				}

            }
            if(Fx[k].sector == FX_FIRE1 )                      
            { 

                if(loop != ply_id)  
				{
					if( Fx[k].value3 == 1)            
	                    Man_Shot(-1, loop, Fx[k].linked_sprite, BULLET_FIRE1, f_rate);  
					if( Fx[k].value3 == 2)            
	                    Man_Shot(-1, loop, Fx[k].linked_sprite, BULLET_FIRE2, f_rate);  
					if( Fx[k].value3 == 3)            
	                    Man_Shot(-1, loop, Fx[k].linked_sprite, BULLET_FIRE3, f_rate);  

				} 
                if(loop == ply_id)
				if(has_firevest_equipped == false)  
                {
					if( Fx[k].value3 == 1)            
	                    Man_Shot(-1, loop, Fx[k].linked_sprite, BULLET_FIRE1, f_rate);  
					if( Fx[k].value3 == 2)            
	                    Man_Shot(-1, loop, Fx[k].linked_sprite, BULLET_FIRE2, f_rate);  
					if( Fx[k].value3 == 3)            
	                    Man_Shot(-1, loop, Fx[k].linked_sprite, BULLET_FIRE3, f_rate);  
                } 
				// Move buddy somewhere else.. 
				if(loop == p1_buddy) 
		//		if(sprite[loop].moving == false)
				{
					sprite[loop].mov_x = (sprite[loop].w+sprite[loop].box_width/2); 
					sprite[loop].mov_y -= (sprite[loop].z+sprite[loop].box_height/2)-0.12f; 
					  
					sprite[loop].end_x = sprite[loop].mov_x;
					sprite[loop].end_y = sprite[loop].mov_y; 

					Find_Path(loop, sprite[loop].end_x, sprite[loop].end_y);

				}
            }   
            if(Fx[k].sector == FX_GAS)        
            {  
                if(loop != ply_id)
                {              
                    if(loop != p1_buddy || p1_buddy == -1)  
					if(sprite[loop].linked_sprite != p_server)  // Gas-Mask buddies...
                        Man_Shot(-1, loop, -1, BULLET_GAS, f_rate); 					 
					
                } 
                if(loop == ply_id) 
                {
                    if(has_gasmask_equipped == false)
                        Man_Shot(-1, loop, -1, BULLET_GAS, f_rate);
                } 
            }                           
                
            Fx[k].action_timer = 101; 
        }
    }         
    
	if(sprite[loop].type == UNT) 
	if(sprite[loop].score > 0) 
    if(sprite[loop].grab_switch == true) 
    if(sprite[loop].turn_off == false) 
    if(Fx[k].item_type == INV_MINE) 
	if(Fx[k].value == TRAP_TYPE_MINE) 
    if(sprite[loop].linked_sprite != player_type)
    {   
                            
    tarX = Fx[k].w + Fx[k].box_width/2;  
    tarY = Fx[k].z + Fx[k].box_height/2;   
    
    closest_point = 0.15f;
    
    dis_to_point = Node_Distance(midX, midY, tarX, tarY);          
     
    if( dis_to_point < closest_point)     
    {
        
		if(sprite[loop].type == UNT)     	 
		if(sprite[loop].status == MOVE_OUT)
        if(sprite[loop].score > 0)
        {  
			 
			exploding_id = loop;
            exploding_timer = (int)TimerGetTime() + 100;
            exploding_count=10;  
    
            Shell_Landed( Fx[k].w+Fx[k].box_width/2, Fx[k].z+Fx[k].box_height/2, -1, f_rate, INV_BOSS_SHELL, -1); 
			Fx[k].turn_off = true;   
 
        } // sprite[loop].type == UNT

    } // dis_to_point < closest_point 
    
    } // Fx[k].item_type == INV_TRAP

    
    if(Fx[k].sector == FX_BULLET || Fx[k].sector == FX_BULLET_SHADOW)
    if(Fx[k].linked_sprite != loop)
    if(Fx[k].linked_sprite > 0 && Fx[k].linked_sprite < TOTAL_NO_SPRITES)
    if(sprite[Fx[k].linked_sprite].linked_sprite != sprite[loop].linked_sprite)
    {   
                            
    tarX = Fx[k].w + Fx[k].box_width/2;  
    tarY = Fx[k].z + Fx[k].box_height/2;   
    
    closest_point = Fx[k].box_width/2 + sprite[loop].box_width/2;
    
    dis_to_point = Node_Distance(midX, midY, tarX, tarY);          
     
    if( dis_to_point < closest_point)     
    {
       
		if(sprite[loop].type == UNT)     	 
        if(sprite[loop].score > 0)
		if(sprite[loop].linked_sprite == p_server)
        if(Fx[k].sector == FX_BULLET)      
        { 

            if(Fx[k].sector_action != BOMB_EMY)  
            {       
                                      
              if(lan_game == false && next_scene == false)
              {
                    
                 if(loop != ply_id && sprite[loop].type != BAG)  
                 if(sprite[loop].sector != UNIT_MORTAR)
                 if(sprite[loop].sector != UNIT_BOMBER || sprite[loop].onDeath_action != TURRET)
                     Knock_Back(Fx[k].linked_sprite, loop, f_rate); 
                                              
                 Man_Shot(sprite[Fx[k].linked_sprite].status, loop, Fx[k].linked_sprite, Fx[loop].sector_action, f_rate);
                     
              }

              New_FX(Fx[k].x, Fx[k].y,  Fx[k].w, Fx[k].z, 36, PLAY, Fx[k].box_width, Fx[k].box_height, Fx[k].width, Fx[k].height, 2, GFX, 1.0f, loop, 0, FX_BLOOD, loop, 2, 0, 0, -1);
              Fx[k].turn_off = true;  
            }     
 
            if(Fx[k].sector_action == BOMB_EMY)    
			if(loop != p1_id || player_in_water == false) 
			if(loop != p1_buddy || buddy_in_water == false)
			{         
                Shell_Landed( Fx[k].w+Fx[k].box_width/2, Fx[k].z+Fx[k].box_height/2, -1, f_rate, -1, -1); 
				Fx[k].turn_off = true;   
			}
            
        } // is UNT is FX_BULLET
        

    } // dis_to_point < closest_point
    
    } // Fx[k].sector == FX_BULLET || Fx[k].sector == FX_BULLET_SHADOW


    
    } // End for loop
    
    
}
 

void Test_sprite_to_Obj(int loop, int target)
{
     
    float midX =0.0f, midY =0.0f;
    float mid_x =0.0f, mid_y =0.0f;    
    float tarX =0.0f, tarY =0.0f;
    bool test_success=false;
    float closest_point = 0.0f; 
    float dis_to_point = 0.0f;
    int index=0;
    bool is_special_event = false;
    bool has_this_gun = false;
	int temp_row_x=0, temp_row_y=0;

	if(loop < 0 || target < 0)
		return;
           
    midX = sprite[loop].w+sprite[loop].box_width/2;
    midY = sprite[loop].z+sprite[loop].box_height/2;     
                 
    tarX = sprite[target].w + sprite[target].box_width/2;
    tarY = sprite[target].z + sprite[target].box_height/2; 
    
    closest_point = (float)talk_rng;  
    
	if(sprite[target].sector_action == OBJ_INFO 
    || sprite[target].sector_action == OBJ_DANCER  
    || sprite[target].sector_action == OBJ_DANCER1)  
		closest_point = (float)widetalk_rng;
    
	if(sprite[target].sector_action == OBJ_TIMEPLUS_SMLL 
    || sprite[target].sector_action == OBJ_TIMEPLUS_MID  
    || sprite[target].sector_action == OBJ_TIMEPLUS_BIG
    || sprite[target].sector_action == OBJ_PISTOL_UP  
    || sprite[target].sector_action == OBJ_RIFLE_UP
    || sprite[target].sector_action == OBJ_LIFE_UP  
    || sprite[target].sector_action == OBJ_BONUS1  
    || sprite[target].sector_action == OBJ_BONUS2
    || sprite[target].sector_action == OBJ_BONUS3  
    || sprite[target].sector_action == OBJ_BONUS4
	)
		closest_point = (float)arcade_rng;

    dis_to_point = Node_Distance(midX, midY, tarX, tarY);     
    
    near_sell = false;   
	  
	if(CONTROLLER)   
	if(dis_to_point < closest_point)  
	if(sprite[target].type == OBJ || (sprite[target].type == UNT && sprite[target].sector == UNIT_DECOY && sprite[target].score > 0))
	if( sprite[target].sector_action != OBJ_OBSTACLE)
	if( sprite[target].sector_action != OBJ_SEAGULL) 
	if( sprite[target].sector_action != OBJ_SEAGULL2)
	if( sprite[target].sector_action != -1)
	if( sprite[target].sector_action != OBJ_NONE || sprite[target].sector == UNIT_DECOY)  
	if( sprite[target].alpha != 0.0f)
	if(DXPick_Up==-1 && DXJustCollected==false)
		DXTalk_Man = target; 
     
	if(mouseleft == true || DX_USECOLLECT == true) 
	if( sprite[target].sector_action != OBJ_OBSTACLE)
    if(dis_to_point < closest_point)     
    {  

		if(sprite[target].type == UNT && sprite[target].sector == UNIT_DECOY && sprite[target].score > 0)
		if(Calculate_Item(TRAP_TYPE_DECOY, INV_TRAP, -1, 0, 1, sprite[target].score))
		{

			tarX = sprite[target].w + sprite[target].box_width/2;  
            tarY = sprite[target].z + sprite[target].box_height/2;
			 
            temp_row_x = (int)((tarX + map_startX)*10);       
            temp_row_y = (int)((tarY + map_startY)*10);   

           	if( (temp_row_y*MAP_HEIGHT)+temp_row_x > 0 && (temp_row_y*MAP_HEIGHT)+temp_row_x < MAP_TILES)
			if( map_col[(temp_row_y*MAP_HEIGHT)+temp_row_x] == 6)
	            map_col[(temp_row_y*MAP_HEIGHT)+temp_row_x] = 0; 
 
 			sprite[target].status = MAN_DOWN1;    
			sprite[target].all_timer = 0;   
			sprite[target].score = 0; 

			mgun_sfx = true;
		}


		DX_USECOLLECT=false;
        mouseleft = false;   

		if(displaying_message_type == MSG_NOWEAPON || displaying_message_type == MSG_TOOFAR)
		{
		   dialog_timer = (int)TimerGetTime();
		   hud[2].alpha = 0.0f; 
		   sprintf( counter[4].word, "");
		   displaying_message_type = -1;
		   dialog_active = -1; 
		}

        sprite[loop].moving = false;    
        ShotIdle(loop);                                
        sprite[loop].anim_state = WAIT;  
        sprite[loop].update = true;                      
        sprite[loop].fire_target = -1;          
        
        if(target >= 0) 
        if(sprite[target].type == OBJ)  
        {
        
			if(sprite[target].sector_action == OBJ_TIMEPLUS_SMLL 
			|| sprite[target].sector_action == OBJ_TIMEPLUS_MID  
			|| sprite[target].sector_action == OBJ_TIMEPLUS_BIG
			|| sprite[target].sector_action == OBJ_PISTOL_UP  
			|| sprite[target].sector_action == OBJ_RIFLE_UP
			|| sprite[target].sector_action == OBJ_LIFE_UP  
			|| sprite[target].sector_action == OBJ_BONUS1  
			|| sprite[target].sector_action == OBJ_BONUS2
			|| sprite[target].sector_action == OBJ_BONUS3  
			|| sprite[target].sector_action == OBJ_BONUS4
			)
			{
				

				if(sprite[target].sector_action == OBJ_TIMEPLUS_SMLL)
				{
					arcade_time+=15;
					ok_sfx=true; 
				}

				if(sprite[target].sector_action == OBJ_TIMEPLUS_MID)
				{
					arcade_time+=30; 
					ok_sfx=true;
				}

				if(sprite[target].sector_action == OBJ_TIMEPLUS_BIG)
				{
					arcade_time+=60;
					ok_sfx=true;
				}

				if(sprite[target].sector_action == OBJ_BONUS1)
				{
					arcade_bonus_timer = (int)TimerGetTime() + 15000;
					arcade_bonus=1;
					ok_sfx=true;
				}

				if(sprite[target].sector_action == OBJ_BONUS2)
				{
					arcade_bonus_timer = (int)TimerGetTime() + 15000;
					arcade_bonus=2;
					ok_sfx=true;
				}
				 
				if(sprite[target].sector_action == OBJ_BONUS3)
				{
					arcade_bonus_timer = (int)TimerGetTime() + 15000;
					arcade_bonus=3;
					ok_sfx=true; 
				}
				 
				if(sprite[target].sector_action == OBJ_BONUS4)
				{
					arcade_bonus_timer = (int)TimerGetTime() + 15000;
					arcade_bonus=4;
					ok_sfx=true;
				}
				 
				if(sprite[target].sector_action == OBJ_LIFE_UP)
				{
					stat_vitality+=5;
					cash_up_sfx = true; 
				}

				if(sprite[target].sector_action == OBJ_PISTOL_UP)
				{
					stat_pistol_skill+=5; 
					cash_up_sfx = true;
				}

				if(sprite[target].sector_action == OBJ_RIFLE_UP)
				{
					stat_rifle_skill+=5; 
					cash_up_sfx = true;
				}

				Calculate_Stats();

				sprite[target].alpha = 0.0f;
				sprite[target].sector_action = OBJ_NONE;
			}



        if( sprite[target].sector_action != OBJ_SHOTGUN) 
        if( sprite[target].sector_action != OBJ_PISTOL)
        if( sprite[target].sector_action != OBJ_MACHINE)
        if( sprite[target].sector_action != OBJ_RIFLE) 
        if( sprite[target].sector_action != OBJ_HEALTH)
        if( sprite[target].sector_action != OBJ_GRENADE)
            sprite[target].all_timer = (int)TimerGetTime() + 1500; 
        
        if(ply_id != -1)
        if(sprite[target].score > 0)
        if(sprite[target].sector_action == OBJ_SWITCH1)
        {
            sprite[target].moving = true; 
        }                                
                                                 
        if(ply_id != -1) 
        if(sprite[target].score > 0)
        if(sprite[target].sector_action == OBJ_SWITCH)
        { 
            sprite[target].score = 0; 
            Display_Message(ply_id, MSG_TRIGGER);  
            click_sfx = true;    
            mouseleft=false;   

        }  
        
        if(ply_id != -1)
        if(sprite[target].sector_action == OBJ_INFO 
        || sprite[target].sector_action == OBJ_DANCER 
        || sprite[target].sector_action == OBJ_DANCER1
        )
        { 
            if(sprite[target].score == MSG_MERCY_BIRD 
            || sprite[target].score == MSG_MERCY_MONKEY
            || sprite[target].score == MSG_STATUE   
            || sprite[target].score == MSG_HUMAN1
            || sprite[target].score == MSG_HUMAN
            || sprite[target].score == MSG_RESUPPLY
            || sprite[target].score == MSG_LOCKED 
            || sprite[target].score == MSG_BATHTUB
			|| sprite[target].score == MSG_OLDRECRUIT) 
            {    
                  
                if(sprite[target].score == MSG_LOCKED) 
                if(Has_This_Item(INV_LETTERS, 21) == true)
                    global_objective[3] = GLOBAL_BEATEN; 
                 
                if(sprite[target].score != MSG_BATHTUB)     
                if(sprite[target].score != MSG_LOCKED || global_objective[3] == GLOBAL_UNBEATEN)                            
                    Display_Message(ply_id, sprite[target].score);
                
                if(ply_id != -1)     
                if(sprite[target].score == MSG_BATHTUB)  
                { 
                    sprite[ply_id].status = FLATTENED; 
                    sprite[ply_id].all_timer = (int)TimerGetTime() + 2000; 
                        
                    sprite[ply_id].update = true;
                    sprite[ply_id].anim_state = WAIT;
             
                    stolen_sfx = true;   
                    mouseleft = false;
                }
                 
            }
            else
                Display_Message(target, sprite[target].score); 
            
            if(sprite[target].score == MSG_MERCY_MONKEY)
                monkey_sfx = true;  
             
            if(sprite[target].score == MSG_EMBARASS)
			{
				sprite[target].sector_action = OBJ_NONE;

				if(Level == LVL_SUPPLIES) 
				    temp_global_objects[14] = GLOBAL_BEATEN;
				if(Level == LVL_FARMS)
				    temp_global_objects[15] = GLOBAL_BEATEN;

                click_off_sfx = true;   
			}
                
            if(sprite[target].score == MSG_STATUE)
               stolen_sfx = true;     

            mouseleft=false;
        } 
        
        if(ply_id != -1)
        if(sprite[target].sector_action == OBJ_TALK1)
        {
                          
            Display_Message(ply_id, sprite[target].score); 
                
            mouseleft=false;
            
        }    
                  
        if(sprite[target].sector_action == OBJ_LETTERS)
        {

        }  
        
        if(sprite[target].sector_action == OBJ_LETTERS1)
        {

        }
        
        if(sprite[target].sector_action == OBJ_LIGHT1)
        {
                                        
            if(sprite[target].linked_sprite == LIGHT_OFF) 
                sprite[target].linked_sprite = LIGHT_ON; 
            else
                sprite[target].linked_sprite = LIGHT_OFF;
                
            if(sprite[target].linked_sprite == LIGHT_OFF)
                Set_Sprite( target, sprite[target].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); // Stunned
            if(sprite[target].linked_sprite == LIGHT_ON)
                Set_Sprite( target, sprite[target].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); // Stunned
                
            if(sprite[target].onCreate_action == LIGHT_TORCH)
                torch_sfx = true; 
                
            if(sprite[target].onCreate_action == LIGHT_ELECTRIC)
                lightswitch_sfx = true; 
                            
            mouseleft = false;
            mouseheld = false; 
             
      /*      if(dm_game != DM_NONE)   
            {    
  
                ping_torch_id[ping_torch_count] = target;  
                
                if(sprite[target].linked_sprite == LIGHT_OFF)
                    ping_torch_status[ping_torch_count] = false;  
                else
                    ping_torch_status[ping_torch_count] = true;  
                                             
                ping_torch_count++;      
                               
                if(ping_torch_count >= 40) 
                    ping_torch_count=0;                  

            }    */ 
            
        }   
                          
        if(sprite[target].sector_action == OBJ_RESCUE)
        {
            episode = 1;
            scene = 78;  
            next_scene = true;  
        }
                          
        if(sprite[target].sector_action == OBJ_BUDDY) 
        {

            episode = 1;
            scene = 146;   
             
            next_scene = true;    
        }      
        if(sprite[target].sector_action == OBJ_SAW)
        {

            episode = 1; 
            scene = 161;

			main_mission[MISSION_CINEMA] = COMPLETED;   
             
            next_scene = true; 
        }                                      
        if(sprite[target].sector_action == OBJ_MONKEY)
        {

            episode = 1;
            scene = 148;   
                        
            next_scene = true; 
        }      
        if(sprite[target].sector_action == OBJ_ISLAND)
        {

            episode = 1;
            scene = 174;   
                        
            next_scene = true; 
        }    
        if(sprite[target].sector_action == OBJ_FOOTSHOT)
        {
			 
            episode = 1;
            scene = 188;   
                        
            next_scene = true; 
        }   
        if(sprite[target].sector_action == OBJ_DUMMY)
        {

            episode = 1; 
            scene = 154;  
                        
            next_scene = true; 
        }           
        if(sprite[target].sector_action == OBJ_RAILCAR)
        {
            episode = 1;    
            scene = 110; 
            gun_entry = ENTRY_GARDENS;
            next_scene = true; 
        }                
        if(sprite[target].sector_action == OBJ_BETSY)
        {
            episode = 1;
            scene = 0;  
            
            if(BETA_MODE == 0 && main_mission[MISSION_SPY] == FINISHED)
            {
                episode = 1;
                scene   = 50;
            }
            
            next_scene = true; 
            
        }
                                
        if(sprite[target].sector_action == OBJ_BETSY4)
        {
            episode = 1; 
            scene = 122; 
            next_scene = true; 
        }
                                        
        if(sprite[target].sector_action == OBJ_SCARECROW)
        {
            episode = 1; 
            scene = 86; 
            next_scene = true; 
        }         
                                
        if(sprite[target].sector_action == OBJ_COMMAND)
        {
            episode = 1;  
            scene = 92;  
            next_scene = true; 
        }    
                                       
        if(sprite[target].sector_action == OBJ_AIRPLANE)
        {
            episode = 1; 
            scene = 90;  
            current_spawn = 0; 
            next_scene = true; 
        }
        
        if(sprite[target].sector_action == OBJ_CLAY)
        { 
            episode = 1;   
            scene = 110; 
            gun_entry = ENTRY_PIGEON;
            next_scene = true; 
        }
         
        if(sprite[target].sector_action == OBJ_KNIFE)
        { 
            episode = 1;

            next_scene = true; 
        }        
                                         
        if(sprite[target].sector_action == OBJ_AIRPLANE1)
        {
            episode = 3;
            scene = 29; 
            current_spawn = 2;
            next_scene = true; 
        }                              
         
        if(sprite[target].sector_action == OBJ_SUB_INTRO)
        {
            episode = 1; 
            scene = 34; 
            next_scene = true; 
        } 
        if(sprite[target].sector_action == OBJ_NUN)
        {
            episode = 1; 
            scene = 68;    
            next_scene = true; 
        }      
        if(sprite[target].sector_action == OBJ_NUN1)
        {
            episode = 1; 
            scene = 91;  
            next_scene = true; 
        }         
        if(sprite[target].sector_action == OBJ_CHEF)
        {
            episode = 1; 
            scene = 76;  
            next_scene = true; 
        }              
        if(sprite[target].sector_action == OBJ_SPY_CAMP)
        {
            episode = 1; 
            scene = 37; 
            next_scene = true; 
        }    
        if(sprite[target].sector_action == OBJ_MADMAN)
        {
            episode = 1;  
            scene = 38;    
            next_scene = true; 
        } 
                        
        if(sprite[target].sector_action == OBJ_TELESCOPE)
        {
            episode = 1; 
            scene = 45; 
            next_scene = true; 
        }          
		                        
        if(sprite[target].sector_action == OBJ_TELESCOPE1)
        {
            episode = 1;  
            scene = 183; 
            next_scene = true; 
        }   
        if(sprite[target].sector_action == OBJ_MAP)
        { 
       
            if(episode == 3 && scene == 21)
                map_type = MAP_CLIFFS; 
                                        
            if(episode == 3 && scene == 18)
                map_type = MAP_BOATYARD; 
                                                
            episode = 1;  
            scene = 62; 
            
            next_scene = true; 
            
        }
                                        
        if(sprite[target].sector_action == OBJ_DODGYDAN)
        {
            episode = 1;
            scene = 27; 
            shop_intro_type=SHOP_ENTRY_TYPE;
            next_scene = true; 
        }
                        
        if(sprite[target].sector_action == OBJ_BOATGIRL)
        {
            episode = 1;
            scene = 32; 
            next_scene = true; 
        }
                        
        if(sprite[target].sector_action == OBJ_BATTLESHIP)
        {
            episode = 1;
            scene = 33; 
            next_scene = true; 
        }
                                        
        if(sprite[target].sector_action == OBJ_UPGRADE)
        {
            episode = 1; 
            scene = 29; 
            shop_intro_type=SHOP_ENTRY_TYPE;
            next_scene = true; 
        }
                                        
        if(sprite[target].sector_action == OBJ_MEDALBOX)
        {
            episode = 1;
            scene = 24; 
            next_scene = true; 
        }
                                
        if(sprite[target].sector_action == OBJ_PATCHES)
        {
            episode = 1;
            scene = 19; 
            next_scene = true; 
        }     
                        
        if(sprite[target].sector_action == OBJ_DOGMATE)
        {
            episode = 1;
            scene = 20; 
            next_scene = true; 
        }                            
        if(sprite[target].sector_action == OBJ_BETSY_TIED)
        {
            episode = 1;
            scene = 16; 
            next_scene = true; 
        }
                        
        if(sprite[target].sector_action == OBJ_CARD_START)
        {
            episode = 1;
            scene = 17; 
            shop_intro_type=SHOP_ENTRY_TYPE;
            next_scene = true; 
        }
                                        
        if(sprite[target].sector_action == OBJ_ARTY)
        { 
            episode = 1;
            scene = 13;  
            next_scene = true; 
        }
                        
        if(sprite[target].sector_action == OBJ_FATMAN)
        { 
            episode = 1;
            scene = 14;   
            next_scene = true; 
        }
                        
        if(sprite[target].sector_action == OBJ_GENERAL)
        { 
            episode = 1; 
            scene = 15;  
            next_scene = true; 
        }
                                                
        if(sprite[target].sector_action == OBJ_CAMP_BUSTED)
        {
            episode = 1;
            scene = 11; 
            next_scene = true; 
        }
                
        if(sprite[target].sector_action == OBJ_DRILL)
        {
            episode = 1;
            scene = 1; 
            next_scene = true;   
        }
        
        if(sprite[target].sector_action == OBJ_SPY)
        {
            episode = 1;
            scene = 28; 
            next_scene = true;  
        }
                
        if(sprite[target].sector_action == OBJ_WAGES)
        {
            episode = 1;
            scene = 2; 
            next_scene = true; 
        }
        
        if(sprite[target].sector_action == OBJ_STARTUP)
        {
            episode = 1; 
            scene = 5; 
            next_scene = true; 
        }
                
        if(sprite[target].sector_action == OBJ_CASINO)
        {
            episode = 1;
            scene = 3; 
            next_scene = true; 
        }
                
        if(sprite[target].sector_action == OBJ_GALLERY)
        {
            episode = 1;
            scene = 8; 
            next_scene = true; 
        }
                
        if(sprite[target].sector_action == OBJ_GALLERY_START)
        {
            episode = 1; 
            scene = 10;  
            next_scene = true;      
        }
                
        if(sprite[target].sector_action == OBJ_EVENT)
        {
            if(sprite[target].anim == sprite[target].base_anim)
            {                             
            //  if(rand()%100 == 55)
            //      is_special_event = true;  
                                            
              if(is_special_event == false)                             
                  stolen_sfx = true;  
                  
              if(is_special_event == false) // rand()%6 == 0 && 
                  Display_Message(target, MSG_SHITTER1); 
                   
            }    
            
            mouseleft = false;
        } 
        
        if(ply_id != -1)         
        if(sprite[target].sector_action == OBJ_SCARE)
        {   
                      
            sprite[ply_id].status = FLATTENED; 
            sprite[ply_id].all_timer = (int)TimerGetTime() + 2000; 
                
            sprite[ply_id].update = true;
            sprite[ply_id].anim_state = WAIT;
     
            stolen_sfx = true;   
            mouseleft = false;
        }
                 
        if(sprite[target].sector_action == OBJ_MUSICBOX)
        {   
            if(sprite[target].moving == false)
            {
                music_off = true; 
                sprite[target].moving = true;
                Set_Sprite(target, sprite[target].base_anim, PLAY, ANIM_SPRITE, ANIM_WALKING);
            }
            else
            {
                music_off = false;
                sprite[target].moving = false;
                Set_Sprite(target, sprite[target].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING);                
            }
             
            chute_sfx = true;    
            mouseleft = false;
        } 
    
        if(sprite[target].sector != UNIT_RESCUE) 
        if(sprite[target].sector_action != OBJ_SELL)
        if(sprite[target].sector_action != OBJ_SHOTGUN)
        if(sprite[target].sector_action != OBJ_PISTOL)
        if(sprite[target].sector_action != OBJ_MACHINE)
        if(sprite[target].sector_action != OBJ_RIFLE)
        if(sprite[target].sector_action != OBJ_HEALTH)
        if(sprite[target].sector_action != OBJ_GRENADE)
        if(sprite[target].sector_action != OBJ_LIGHT1)
        if(sprite[target].sector_action != OBJ_MUSICBOX)
        if(sprite[target].sector_action != OBJ_DANCER)
        if(sprite[target].sector_action != OBJ_SWITCH1)
        if(sprite[target].sector_action != OBJ_DANCER1)  
        if(sprite[target].score != MSG_RESUPPLY)              
        if(sprite[target].selected == false)
        {
            
            sprite[target].selected = true;   
             
            if(sprite[target].score != MSG_MERCY_BIRD) 
            if(sprite[target].sector_action != OBJ_TALK1)
                Set_Sprite(target, sprite[target].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING);
            
            // Spawn rare item for OBJ_EVENT...    
            if(sprite[target].sector_action == OBJ_EVENT)
            if(sprite[target].anim != sprite[target].base_anim+2)
            if(is_special_event == true) 
            { 
                     
                mid_x = sprite[target].w+sprite[target].box_width/2;  
                mid_y = sprite[target].z+sprite[target].box_height/2; 
                   
                Set_Sprite(target, sprite[target].base_anim+2, LOOP, ANIM_SPRITE, ANIM_WALKING);
                
                fall_sfx = true;
                                    
            }        
        } 
        
        if(sprite[target].sector_action == OBJ_MEDIC)
        {
            Display_Message(target, MSG_MEDIC);                             
            sprite[loop].score = PLY_VITALITY; 
            Calculate_Lifebar(); 
            player_health = sprite[loop].score; 
            
            if(p1_buddy != -1) 
            {
                sprite[p1_buddy].score = BUDDY_VITALITY; 
                buddy_health = BUDDY_VITALITY;                
            }
                
            chute_sfx = true;
            mouseleft = false;
        }            
        } // == OBJ
    }
    
} 

void Test_sprite_to_trigger(int loop)
{
    float dis_to_point=0.0;   
    float midX=0.0f, midY=0.0f;
    float tarX=0.0f, tarY=0.0f; 
    int index=0;
    float tar_X=0.0f, tar_Y=0.0f;
    float midX1=0.0f, midY1=0.0f;
    int temp_row_x=0, temp_row_y=0;
    int index1=0;
    int linked_index=0;
    bool buddy_skip = false;
    

	if(loop < 0)
		return;

    if(p1_buddy != -1)
    if(loop == p1_buddy)
       buddy_skip = true;

    
    midX = sprite[loop].w+sprite[loop].box_width/2;
    midY = sprite[loop].z+sprite[loop].box_height/2;
    
    if( buddy_skip == false)
    if(next_scene == false)
    for(int i=0;i< trigger_counter;i++)
    {   
     
      index = trigger_list[i];

	  if(index < 0)
	      break;
       
      tar_X = sprite[index].w+sprite[index].box_width/2;
      tar_Y = sprite[index].z+sprite[index].box_height/2;
      
      linked_index = sprite[index].linked_sprite;
      
      if( linked_index < 0)      
          linked_index = 24;

      if(sprite[loop].type == UNT && sprite[loop].sector != UNIT_SNIPER)       
      if(sprite[index].onCreate != -1) 
      if(sprite[index].moving == false)
      if(sprite[loop].status != FALLING && sprite[loop].turn_off == false)
      if(sprite[index].sector != LVL_CLOSED) 
      if( main_mission[linked_index] != UNBEATEN 
      || sprite[index].linked_sprite == MISSION_NONE 
      || sprite[index].linked_sprite == MISSION_T_COMPLETE
      || sprite[index].linked_sprite == MISSION_T_START
      )
      
      
      if( sprite[index].sector != LVL_DEMO && sprite[loop].grab_switch == true)       
      if( (sprite[index].type == TRI || sprite[index].type == LAD || sprite[index].type == SWI) )
      {       
        
        if(( midX < sprite[index].w + sprite[index].box_width )
        &&( midX > sprite[index].w)                        
        &&( midY < sprite[index].z + sprite[index].box_height )
        &&( midY > sprite[index].z ))      
        {     
            if(ply_id != -1)
            if(sprite[index].type == SWI)
            if(sprite[index].grab_switch == true)
            if( (sprite[index].sector == HIT_PLAYER && loop == ply_id) 
            || (sprite[index].sector == HIT_VEHICLE && sprite[loop].sector == UNIT_VEHICLE)             
            )
            {
                trigger_hit = index;            
            //    sprite[index].grab_switch = false;                      

            }
                        
            if(sprite[index].type == LAD) 
            {    
    
                midX1 = sprite[loop].w+sprite[loop].box_width/2; 
                midY1 = sprite[loop].z+sprite[loop].box_height/2;     
                
                temp_row_x = (int)((midX1 + map_startX)*10);        
                temp_row_y = (int)((midY1 + map_startY)*10);  
     
                index1 = (temp_row_y*MAP_HEIGHT)+temp_row_x;        
    			
				if( index1 < 0)
					break;

                map_col[index1] = 0;   
                
                sprite[loop].all_timer = (int)TimerGetTime() + 1500;                  
                
                if(sprite[loop].sector != UNIT_RESCUE && loop != ply_id)                      
                    sprite[loop].all_timer = (int)TimerGetTime() + 500;                  
                    
                sprite[loop].status = FALLING;   
                sprite[loop].update = true;
                sprite[loop].moving = false;
                sprite[loop].grab_switch = false;
                sprite[loop].anim_state = WAIT; 
                
                if(ply_id != -1) 
                if(loop == ply_id)      
                {
                //    falling_in_hole = true; 
                
                    mouseleft = false;     
                }
                 
                if(loop != ply_id && sprite[loop].sector != UNIT_SNIPER && loop != p1_buddy)
                    sprite[loop].score = 0; 
                
                sprite[loop].x = tar_X - sprite[loop].width/2;
                sprite[loop].y = tar_Y - sprite[loop].height/2;
                
                if(sprite[loop].sector != UNIT_MONKEY)
                if(sprite[loop].sector != UNIT_DOG)
                if(sprite[loop].sector != UNIT_BOX)
                    fall_sfx = true;       

                
            }     
            if(ply_id != -1) 
            if(loop == ply_id)
            if(sprite[index].type == LAD 
            || sprite[index].type == TRI)
            { 
            
            stop_music = true;
             
            if(Level != LVL_BASE) 
            if( sprite[index].mouseover == IS_A_PORTAL)                       
            if(sprite[index].type == LAD)
            if(sprite[index].onCreate != -1)
            { 
                current_ladder_sector = Level; 
                current_ladder_spawn  = sprite[index].onCreate; 
            } 
            
            current_spawn = sprite[index].score;
              
            if(sprite[index].sector == LVL_BASE)
            { 
               
             //   if(current_act == 1)  
                    LAD_next_scene = 0; 
            /*    if(current_act == 2)
                    LAD_next_scene = 3; 
                if(current_act == 3) 
                    LAD_next_scene = 10;  
                if(current_act == 4) 
                    LAD_next_scene = 11;  */                    
                                                             
                LAD_next_episode = 2;  

                if(current_act != 1)
                if(global_objects[32] == GLOBAL_UNBEATEN)
                {
                    LAD_next_episode = 1;
                    LAD_next_scene   = 48;               
                } 

                if(current_act == 3)
                if(global_objects[88] == GLOBAL_UNBEATEN)
                {
                    LAD_next_episode = 1;
                    LAD_next_scene   = 79;               
                }                
                 
            }
            if(sprite[index].sector == LVL_FARMS)
            {
                LAD_next_scene = 9;  
                LAD_next_episode = 2; 
            }     
            if(sprite[index].sector == LVL_CONTROL)
            {
                LAD_next_scene = 30;    
                LAD_next_episode = 3; 
            }     
            if(sprite[index].sector == LVL_CONTROLROOM)
            {
                LAD_next_scene = 31;   
                LAD_next_episode = 3;  
            }                        
            if(sprite[index].sector == LVL_FARMS1)
            {
                LAD_next_scene = 4;  
                LAD_next_episode = 2; 
            }                   
            if(sprite[index].sector == LVL_TENT)
            {
                LAD_next_scene = 25;  
                LAD_next_episode = 1;
            }                     
            if(sprite[index].sector == LVL_HIGHWAY)
            {
                LAD_next_scene = 1;  
                LAD_next_episode = 2; 
            }
            if(sprite[index].sector == LVL_CELLAR)
            {
                LAD_next_scene = 13;  
                LAD_next_episode = 3;
            }     
            if(sprite[index].sector == LVL_PIRATE) 
            {
                LAD_next_scene = 14;  
                LAD_next_episode = 3; 
            }       
            if(sprite[index].sector == LVL_ISLAND) 
            {
                LAD_next_scene = 62;  
                LAD_next_episode = 3;
            }         
            if(sprite[index].sector == LVL_PIRATE1)
            {
                LAD_next_scene = 61;   
                LAD_next_episode = 3;
            }       
            if(sprite[index].sector == LVL_BAY)
            {
                LAD_next_scene = 16;  
                LAD_next_episode = 3;
            }      
            if(sprite[index].sector == LVL_PLAINS)
            {
                LAD_next_scene = 63;  
                LAD_next_episode = 3;
            }                        
            if(sprite[index].sector == LVL_ACT2)
            {
                LAD_next_scene = 11;  
                LAD_next_episode = 0;
            }     
            if(sprite[index].sector == LVL_ACT3)
            {
                LAD_next_scene = 12;   
                LAD_next_episode = 0;
            }                      
            if(sprite[index].sector == LVL_ROADWAY)
            {
                LAD_next_scene = 4;  
                LAD_next_episode = 2;
            }            
            if(sprite[index].sector == LVL_VILLAGE)
            {
                LAD_next_scene = 2; 
                LAD_next_episode = 2; 
            }
            if(sprite[index].sector == LVL_WINDMILL)  
            {
                LAD_next_scene = 64;  
                LAD_next_episode = 3; 

				if(global_objects[84] == GLOBAL_UNBEATEN) // Mauser tank-love cutscene...
				{
	                LAD_next_scene = 158;   
	                LAD_next_episode = 1; 	
					global_objects[84] = GLOBAL_BEATEN; 
				}
	
            }
            if(sprite[index].sector == LVL_CASINO)
            {
                LAD_next_scene = 2; 
                LAD_next_episode = 3;  
            } 
            if(sprite[index].sector == LVL_TRENCH_A)
            {
                LAD_next_scene = 24;  
                LAD_next_episode = 3; 
            }                   
            if(sprite[index].sector == LVL_TRENCH_B)
            {
                LAD_next_scene = 25;  
                LAD_next_episode = 3;
            }     
            if(sprite[index].sector == LVL_TOWN)
            {
                
            }    
            if(sprite[index].sector == LVL_STAIRWELL)
            {
                LAD_next_scene = 19;   
                LAD_next_episode = 3;
            }     
            if(sprite[index].sector == LVL_ALLEY1)
            { 
                LAD_next_scene = 38;    
                LAD_next_episode = 3;
            }                                                 
            if(sprite[index].sector == LVL_ALLEY2)
            {
                LAD_next_scene = 39;   
                LAD_next_episode = 3;
            }     
            if(sprite[index].sector == LVL_ALLEY3)
            {
                LAD_next_scene = 40;   
                LAD_next_episode = 3; 
            }  
            if(sprite[index].sector == LVL_ALLEY4)
            {
                LAD_next_scene = 41;   
                LAD_next_episode = 3;  
            }    
            if(sprite[index].sector == LVL_HOUSE_TRAP1)
            {
                LAD_next_scene = 46;    
                LAD_next_episode = 3;  
            }   
            if(sprite[index].sector == LVL_HOUSE_TRAP) // Now railway station
            {
                LAD_next_scene = 42;    
                LAD_next_episode = 3;  
            }  
            if(sprite[index].sector == LVL_CINEMA)
            {
                LAD_next_scene = 54;    
                LAD_next_episode = 3; 
            }  
            if(sprite[index].sector == LVL_SCREENING)
            {
                if(global_objects[1] == GLOBAL_UNBEATEN)
                {
                    LAD_next_scene = 162;     
                    LAD_next_episode = 1; 
                }
                else
                {
                    LAD_next_scene = 55;     
                    LAD_next_episode = 3; 
                }
                
            }                          
            if(sprite[index].sector == LVL_HOUSE_TRAP2)
            {
                LAD_next_scene = 47;    
                LAD_next_episode = 3;   
            }    
            if(sprite[index].sector == LVL_CASTLEROOF)
            {
                LAD_next_scene = 14;     
                LAD_next_episode = 2;   
            }                                                         
            if(sprite[index].sector == LVL_STATION)
            {
                LAD_next_scene = 158;     
                LAD_next_episode = 1; 
            }  
            if(sprite[index].sector == LVL_ALLEY5)
            {
                LAD_next_scene = 44;   
                LAD_next_episode = 3;   
            }     
            if(sprite[index].sector == LVL_ALLEY6)
            {
                LAD_next_scene = 45;   
                LAD_next_episode = 3; 
            }                                                                                                      
            if(sprite[index].sector == LVL_SUPPLIES) 
            {

                
            }  
            if(sprite[index].sector == LVL_TRANS_BEACH)
            {
                LAD_next_scene = 55;  
                LAD_next_episode = 1;
            }     
            if(sprite[index].sector == LVL_TRANS_FORK)
            {
                LAD_next_scene = 84;  
                LAD_next_episode = 1;
            }     
            if(sprite[index].sector == LVL_TRANS_FORK1)
            {
                LAD_next_scene = 85;  
                LAD_next_episode = 1;
            }       
            if(sprite[index].sector == LVL_TRANS_FORK2)
            {
                LAD_next_scene = 87;  
                LAD_next_episode = 1;
            }   
            if(sprite[index].sector == LVL_TRANS_FORK3)
            {
                LAD_next_scene = 88;  
                LAD_next_episode = 1; 
            }        
            if(sprite[index].sector == LVL_TRANS_VILLAGE)
            {
                LAD_next_scene = 89;  
                LAD_next_episode = 1; 
            }                                                           
            if(sprite[index].sector == LVL_TRANS_FRONT)
            {
                LAD_next_scene = 66; 
                LAD_next_episode = 1;  
            }    
            if(sprite[index].sector == LVL_TRANS_BOOT)
            {
                LAD_next_scene = 59; 
                LAD_next_episode = 1; 
            }                           
            if(sprite[index].sector == LVL_TRANS_CAMP)
            {
                LAD_next_scene = 56;   
                LAD_next_episode = 1;
                
                if(current_act != 1)
                if(global_objects[32] == GLOBAL_UNBEATEN)
                {
                    LAD_next_episode = 1;
                    LAD_next_scene   = 48;               
                }   
                 
                if(current_act == 3)
                if(global_objects[88] == GLOBAL_UNBEATEN)
                {
                    LAD_next_episode = 1;
                    LAD_next_scene   = 79;               
                }                                 
                
            }  
            if(sprite[index].sector == LVL_TRANS_CAMP1)
            {
                LAD_next_scene = 58;  
                LAD_next_episode = 1; 
            }     
            if(sprite[index].sector == LVL_TRANS_CAMP2)
            {
                LAD_next_scene = 67;  
                LAD_next_episode = 1;
            }                                                     
            if(sprite[index].sector == LVL_CONVOY)
            {
                LAD_next_scene = 4; 
                LAD_next_episode = 3;
            }   
            if(sprite[index].sector == LVL_BUNKER_A)
            {
                LAD_next_scene = 5; 
                LAD_next_episode = 3;
            }                                             
            if(sprite[index].sector == LVL_BUNKER_B)
            {
                LAD_next_scene = 6;  
                LAD_next_episode = 3;
            }                                             
            if(sprite[index].sector == LVL_BUNKER_C)
            {
                LAD_next_scene = 7; 
                LAD_next_episode = 3;
            }                                             
            if(sprite[index].sector == LVL_CAVE)
            {
                LAD_next_scene = 9; 
                LAD_next_episode = 3;
            }    
            if(sprite[index].sector == LVL_ORCHARD)
            {
                LAD_next_scene = 15; 
                LAD_next_episode = 3;
            }                            
            if(sprite[index].sector == LVL_TRAINING)
            {
                LAD_next_scene = 1;  
                LAD_next_episode = 3;
            }
            if(sprite[index].sector == LVL_BOOT_ROAD)
            {
                LAD_next_scene = 6;  
                LAD_next_episode = 2; 
            }              
            if(sprite[index].sector == LVL_BEACH_ROAD)
            {
                LAD_next_scene = 7;   
                LAD_next_episode = 2;
            }              
            if(sprite[index].sector == LVL_BASEMENT_A)
            {
                LAD_next_scene = 10;  
                LAD_next_episode = 3; 
            }                                             
            if(sprite[index].sector == LVL_BASEMENT_B)
            {
                LAD_next_scene = 11;  
                LAD_next_episode = 3;
            }                                             
            if(sprite[index].sector == LVL_BASEMENT_C)
            {
                LAD_next_scene = 12;  
                LAD_next_episode = 3;
            }   
            if(sprite[index].sector == LVL_GALLERY)
            {
                LAD_next_scene = 8;  
                LAD_next_episode = 1;
            }  
            if(sprite[index].sector == LVL_SH00T_TRENCH)
            {
                 if(main_mission[MISSION_TRENCH] == IN_PROGRESS)
                 {                   
                     LAD_next_scene = 110;     
                     LAD_next_episode = 1;
                     gun_entry = ENTRY_GARDENS;
                 }
                 else 
                 {
                     LAD_next_scene = 111;     
                     LAD_next_episode = 1;
                 }
            }   
            if(sprite[index].sector == LVL_BAY_SHOOT)   
            {
                 if(temp_global_objects[1] == GLOBAL_UNBEATEN && main_mission[MISSION_FISH] == IN_PROGRESS)
                 {                   
                     LAD_next_scene = 110;     
                     LAD_next_episode = 1; 
                     gun_entry = ENTRY_UNDERGROUND;
                 }
                 else 
                 {
				     LAD_next_scene = 16;  
                     LAD_next_episode = 3;
                 }
            }  
            if(sprite[index].sector == LVL_MISSILEL)
            {
                 LAD_next_scene = 93;   // Was 93    
                 LAD_next_episode = 1;
            }                         
            if(sprite[index].sector == LVL_BOATYARD)
            { 
                LAD_next_scene = 18;    
                LAD_next_episode = 3; 
            }              
            if(sprite[index].sector == LVL_BATTLESHIP)
            {
                 LAD_next_scene = 110; 
                 LAD_next_episode = 1;
                 gun_entry = ENTRY_BATTLESHIP;
            }    
            if(sprite[index].sector == LVL_SUB_PEN)
            {  
                LAD_next_scene = 43;  
                LAD_next_episode = 1; 
            }   
            if(sprite[index].sector == LVL_TANK_BOSS)
            { 
                LAD_next_scene = 43;   
                LAD_next_episode = 3; 
            }      
            if(sprite[index].sector == LVL_TRANS_TANK)
            { 
                LAD_next_scene = 153;    
                LAD_next_episode = 1; 
            }                       
            if(sprite[index].sector == LVL_CLIFFS)
            { 
                LAD_next_scene = 21;  
                LAD_next_episode = 3;
            }   
            if(sprite[index].sector == LVL_SECRET_LAB)
            { 
                LAD_next_scene = 22;   
                LAD_next_episode = 3;
            }   
            if(sprite[index].sector == LVL_BOTTOM_LAB)
            { 
                LAD_next_scene = 23;     
                LAD_next_episode = 3;  
            }  
            if(sprite[index].sector == LVL_AIRFIELD)
            { 
                LAD_next_scene = 29;      
                LAD_next_episode = 3;   
            }        
            if(sprite[index].sector == LVL_SILO1)
            { 
                LAD_next_scene = 32;      
                LAD_next_episode = 3;  
            }     
            if(sprite[index].sector == LVL_SILO2)
            { 
                LAD_next_scene = 33;       
                LAD_next_episode = 3;   
            }     
            if(sprite[index].sector == LVL_SILO3)
            { 
                LAD_next_scene = 34;       
                LAD_next_episode = 3;  
            }       
            if(sprite[index].sector == LVL_SILO4)
            { 
                LAD_next_scene = 35;       
                LAD_next_episode = 3;  
            }   
            if(sprite[index].sector == LVL_SUPER)
            { 
                LAD_next_scene = 36;              
                LAD_next_episode = 3;   
            }  
            if(sprite[index].sector == LVL_BUDDY)
            {  
                 LAD_next_scene = 110; 
                 LAD_next_episode = 1; 
                 gun_entry = ENTRY_BUNKER; 
            }             
            if(sprite[index].sector == LVL_SUPER1)
            { 
                LAD_next_scene = 37;        
                LAD_next_episode = 3;  
            }                                                                               
            if(sprite[index].sector == LVL_BETSY)
            {
               
                LAD_next_episode = 1;
                LAD_next_scene = 0;     

                if(BETA_MODE == 0 && main_mission[MISSION_SPY] == FINISHED)
                {
                    LAD_next_episode = 1;
                    LAD_next_scene   = 50;
                }        
                                                      
            }    
            if(sprite[index].sector == LVL_SARGE)
            {
                LAD_next_episode = 1; 
                LAD_next_scene = 1;   
            }             
            if(sprite[index].sector == LVL_GLASSES)
            {
                LAD_next_episode = 1;
                LAD_next_scene = 17;   
                shop_intro_type=SHOP_ENTRY_TYPE;
            } 
            if(sprite[index].sector == LVL_TUNE)
            {
                LAD_next_episode = 1;  
                LAD_next_scene = 29; 
                shop_intro_type=SHOP_ENTRY_TYPE;
                  
                if(skip_level_shop1==true)
                {
				    LAD_next_episode = 1;  
                    LAD_next_scene = 30;  						 
				}
                
            }      
            if(sprite[index].sector == LVL_JACK)
            {
                LAD_next_episode = 1; 
                LAD_next_scene = 3; 
            }            
            if(sprite[index].sector == LVL_SHOP)
            {
                LAD_next_episode = 1; 
                LAD_next_scene = 27; 
                shop_intro_type=SHOP_ENTRY_TYPE;
                
                if(skip_level_shop0==true)
                {
				    LAD_next_episode = 1;   
                    LAD_next_scene = 7;  						 
				}                
            }            
            if(sprite[index].sector == LVL_DOGMAN)
            {
                LAD_next_episode = 1; 
                LAD_next_scene = 3;  
            }   
			if(sprite[index].sector == LVL_TRAPSHOP)
            {
                LAD_next_episode = 1;  
                LAD_next_scene = 184; 
                shop_intro_type=SHOP_ENTRY_TYPE;
                
                if(skip_level_shop0==true)
                {
				    LAD_next_episode = 1;   
                    LAD_next_scene = 7;  						 
				}   
            } 
            if(sprite[index].sector == LVL_FORTRESS)
            {
                LAD_next_episode = 2; 
                LAD_next_scene = 8; 
            }    
            if(sprite[index].sector == LVL_COASTAL)
            {
                LAD_next_episode = 2;
                LAD_next_scene = 5; 
            }  
            if(sprite[index].sector == LVL_CHEF)
            {
                LAD_next_episode = 3;
                LAD_next_scene = 2; 
            }    
            if(sprite[index].sector == LVL_LIBRARY)
            {
                LAD_next_episode = 3; 
                LAD_next_scene = 26; 
            }        
            if(sprite[index].sector == LVL_GRAND)
            {
                LAD_next_episode = 3;
                LAD_next_scene = 48; 
            }   
            if(sprite[index].sector == LVL_ORGAN)
            {
                LAD_next_episode = 3;
                LAD_next_scene = 49; 
            }                               
            if(sprite[index].sector == LVL_GASLAB)
            {
                LAD_next_episode = 3; 
                LAD_next_scene = 50; 
            }   
            if(sprite[index].sector == LVL_GASLAB1)
            {
                LAD_next_episode = 3;
                LAD_next_scene = 51; 
            }                           
            if(sprite[index].sector == LVL_VAULTS)
            {
                LAD_next_episode = 3;
                LAD_next_scene = 27; 
            } 
            if(sprite[index].sector == LVL_DUNGEON)
            {
                LAD_next_episode = 3; 
                LAD_next_scene = 28;   
            }    
            if(sprite[index].sector == LVL_BETSY4)
            {
                LAD_next_episode = 1;
                LAD_next_scene = 122;  
            }                           
            if(sprite[index].sector == LVL_TUNNELS)
            {
//                LAD_next_episode = 1;
//                LAD_next_scene = 31; 
   
                LAD_next_episode = 1;
                LAD_next_scene = 172;    

                entered_from_tunnel=true;

                tunnel_page = current_act;
                
                if(current_act >=2)
                    tunnel_page = 2;
                 
                if(Level == LVL_SUPPLIES)
                    tunnel_page = 1;
                
                if(Level == LVL_HIGHWAY || Level == LVL_BEACH_ROAD)
                    tunnel_page = 2;  
                                    
            }              
                                                                    
            // Uses next_scene so don't copy...                                                                                                
            if(sprite[index].sector == LVL_TUNNEL)
            {
            /*    LAD_next_scene = 31;    
                LAD_next_episode = 1; 
                
                next_scene1 = 31;     
                next_episode1 = 1;  */
   
                LAD_next_episode = 1;
                LAD_next_scene = 172; 
 
			    next_scene1 = 172;     
                next_episode1 = 1;   

                entered_from_tunnel=true;
               
                tunnel_page = current_act; 
                
                if(current_act >= 2)
                    tunnel_page = 2;
                                     
                if(Level == LVL_SUPPLIES)
                    tunnel_page = 1;
                
                if(Level == LVL_HIGHWAY || Level == LVL_BEACH_ROAD)
                    tunnel_page = 2;   
                
            } 
            
			if( trigger_list[i] >= 0)                
	            sprite[trigger_list[i]].grab_switch = false;
            
            if(sprite[index].type == LAD) 
            {
                tunnel_timer = (int)TimerGetTime() + 1000;
            } 
            else
            {
			 	scene = LAD_next_scene;
			 	episode = LAD_next_episode;
                next_scene = true;
			}    
            
            }     // == ply_id           
            
        }            
            
      }
      
    } 
     
} 

void Lay_Mine(float midX, float midY, int loop)
{
    
/*    int row_x=0, row_y=0;
    int index=0;    

	if(loop < 0)
		return;
    
    row_x = (int)((midX + map_startX)*10);
    row_y = (int)((midY + map_startY)*10); 
    
    index = (row_y*MAP_HEIGHT)+row_x;
    
	if(index < 0)
		return;
               
    if(tiles[index] < 16 && tiles[index] != 14 && tiles[index] != 13)
	    tiles[index] = 13;    
    if(tiles[index] == 64 || tiles[index] == 79) 
	    tiles[index] = 77;              
     
    sprite[loop].guys_mine = index; */
     
}

void Mine_Triggered(int guys_index, int mine_index, int loop)
{
       
	if(mine_index < 0)
		return;
        
    if(guys_index != mine_index)  
    {
        if(tiles[mine_index] == 13)
        { 
            tiles[mine_index] = 14;

        }
        if(tiles[mine_index] == 77) 
        {
            tiles[mine_index] = 78;
        }
        
   /*     if( lan_game == true && (tiles[mine_index] == 78 || tiles[mine_index] == 14) )   
        { 
        
            ping_mine_index[ping_mine_count] = mine_index; // center of target 
            ping_mine_type[ping_mine_count] = tiles[mine_index];
            ping_mine_count++;          
        
            if(ping_mine_count >= 40)  
                ping_mine_count = 0; 
            
        } */ 
        
        door_close_sfx = true;
       
    }  
     
}

bool Mine_Check(int row_x, int row_y)
{
    bool test_success=false; 
    int index=0; 
    
    index = (row_y*MAP_HEIGHT)+row_x;
     
	if(index < 0)
		return(0);

    if(tiles[index] < 16 && tiles[index] != 13 && tiles[index] != 14)
    {
        test_success = true; 
    } 
    if(tiles[index] == 64 )
    {
        test_success = true; 
    }
    
    return(test_success); 
     
}

int New_Sprite(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int sideways, int upways, int state, int linked_sprite, int tex_id, int a_global, float angle, int p_type, int goto_point)
{ 
  
    int end_id=-1;   
    int loop=0;
    bool new_sprite=true; 
    bool go_ahead=true;
    int temp_row_x=0;
    int temp_row_y=0;  
    int temp_index=0;
    float mid_x=0.0f, mid_y=0.0f;
	int rnd=0;
      
    // Check if this tile is available...  
    temp_index = Get_Tile_Index(x,y);
    
    if(p_type != SPAWN_DECOY && p_type != SPAWN_PLAYER_UNIT) 
	if(temp_index >= 0 && temp_index < MAP_TILES)
    if(map_col[temp_index] != 0) 
        go_ahead = false;   
   
    
    // Replace a dead body sprite...
    if(go_ahead==true) 
    for(int i=0;i<player_counter;i++)   
    {           
         loop = player_list[i];  
    }
    
    if(go_ahead==true)    
    if(end_id == -1) 
    { 
        end_id = no_sprites;
        no_sprites++; 
        
        if(type != NON && player_counter >= 0)
        {
            player_list[player_counter] = end_id; 
            player_counter++;  
		}
		
    }
    
    if(go_ahead==true)   
    if(end_id != -1 )    
    {          
                                       
        sprite[end_id].id = tex_id; 

		if(type != NON) 
        if(p_type == SPAWN_PLAYER_UNIT)       
	    {
			 
			if(current_unit == a_global)   
			{
				p1_id = end_id;      
				ply_id = end_id;   
			} 

			if(goto_point != -1)  
			{
				sprite[end_id].value2 = goto_point;

				// Setup CO unit type...
				if(sta2_squad[goto_point].type == STA2_CO)
				{
					if(sta2_co_type == STA2_CO_ADA) 
						sprite[end_id].sector = UNIT_GUNNER;
					if(sta2_co_type == STA2_CO_MARIE) 
						sprite[end_id].sector = UNIT_HEAVY;
					if(sta2_co_type == STA2_CO_ADELE) 
						sprite[end_id].sector = UNIT_SNIPER;
					if(sta2_co_type == STA2_CO_BELLA) 
						sprite[end_id].sector = UNIT_MORTAR;
				}

				if(sta2_squad[goto_point].type == STA2_CO) 
					sprite[end_id].id = 15;

				if(sta2_squad[goto_point].type == STA2_SCOUT)
					sprite[end_id].id = 16;

				if(sta2_squad[goto_point].type == STA2_HEAVY)
					sprite[end_id].id = 17;

				if(sta2_squad[goto_point].type == STA2_SNIPER)
					sprite[end_id].id = 18;
				 
				if(sta2_squad[goto_point].type == STA2_MORTAR)
					sprite[end_id].id = 19;

			}

			if(a_global != -1) 
				sprite[end_id].value3 = a_global;

			unit_id[unit_id_count] = end_id;
			unit_id_count++;

		}
                                                                           
        sprite[end_id].x = x;      
        sprite[end_id].y = y; 
        
        sprite[end_id].w = w + box_width/4; 
        sprite[end_id].z = z;   
          
        sprite[end_id].width = width;
        sprite[end_id].height = height;       
                        
        sprite[end_id].box_width = box_width/2;
        sprite[end_id].box_height = box_height;
 

		if(p_type != SPAWN_PLAYER_UNIT) 
		{
			sprite[end_id].value3 = -1; 
			sprite[end_id].value2 = -1;
		}
                     
        if(anim_state != NO_ANIM)      
        {
            sprite[end_id].fx_id = animation_fx[sprite[end_id].id];

            sprite[end_id].anim = anim; 
            sprite[end_id].cur = 0;     
                         
            sprite[end_id].anim_state = anim_state;
#ifndef DREAMCAST
            sprite[end_id].frame = a_texture[sprite[end_id].fx_id].anims[sprite[end_id].anim][sprite[end_id].cur];
#else
            sprite[end_id].frame = a_texture_get_anims_secondlayer(sprite[end_id].fx_id, sprite[end_id].anim, sprite[end_id].cur);
#endif
            
            sprite[end_id].base_anim = sprite[end_id].anim;
                    
            Set_Sprite(end_id, anim, anim_state, ANIM_SPRITE, ANIM_WALKING);
            
        }    
           
        sprite[end_id].alpha = alpha;  

        sprite[end_id].priority = priority;
            
        sprite[end_id].type = type;      
        
        sprite[end_id].mouseover = false;
        
        sprite[end_id].score = 0;   

        sprite[end_id].linked_sprite = linked_sprite;
        
        if(angle != -1)   
            sprite[end_id].angle = angle; 
        
        sprite[end_id].sector_action = AI_NONE;
         
        sprite[end_id].hit_opponent = false;      
        sprite[end_id].sector = state; 
		
        sprite[end_id].grab_switch = true;
         
        sprite[end_id].light = 1.0f; 
        
        sprite[end_id].file_full = false;
        
        sprite[end_id].on_ladder = false;

        if(type == UNT || type == NON)                
        {
            sprite[end_id].score = 60; 
            sprite[end_id].sector_action = AI_NONE;   
            sprite[end_id].cur=0; 
            sprite[end_id].flash_target = false; 
            sprite[end_id].moving = false;  
            sprite[end_id].flash_timer  = 0;
            sprite[end_id].dflash_timer = 0;  
            sprite[end_id].death_flash  = false;          
            sprite[end_id].fire_target = -1;
            sprite[end_id].emy_shooting = false;
            sprite[end_id].jumping = false;  
            sprite[end_id].all_timer=0;
            sprite[end_id].reached_node = -1;
            sprite[end_id].node_counter = 0; 
            sprite[end_id].kills = 0; 
		    sprite[end_id].flash_no_count = 0;   
            sprite[end_id].node_counter=0;  
            sprite[end_id].depth = 0.0;     
            sprite[end_id].anim = 0;    
            sprite[end_id].movement = 0; 
            sprite[end_id].on_mud = false;   
            sprite[end_id].rank = 0; 
            sprite[end_id].group_id = -1;
            sprite[end_id].spotted_timer = 0;
            sprite[end_id].ai_brain_timer = 0;
			sprite[end_id].thrown_effect = 0;
			sprite[end_id].camo = false;

            sprite[end_id].ai_brain = BRAIN_DEFAULT;
			            
            sprite[end_id].spotted = false; 
            sprite[end_id].col_timer = 0;  
            sprite[end_id].return_fire = false;
			sprite[end_id].idle_type = IDLE_NONE; 
			     
            sprite[end_id].reload_timer = 0; 
            sprite[end_id].mercy = false;
             
            if(angle != -1)
                sprite[end_id].tar_angle = angle; 
            if(angle == -1)
                sprite[end_id].tar_angle = 0.0f;
                
            sprite[end_id].bomb_timer = 0;
            sprite[end_id].bagging = false; 
            sprite[end_id].splatted = false;
            sprite[end_id].on_ladder = false;
                
            sprite[end_id].turn_off = false;
            sprite[end_id].anim_state = WAIT; 
            sprite[end_id].status = IDLE; 
            
            if(angle == -1)
                sprite[end_id].angle = -1.5;
            
            sprite[end_id].turning = false;   
             
            sprite[end_id].selected = false; 
            sprite[end_id].update = true;   
            sprite[end_id].hit_by_bullet = false;    
            sprite[end_id].special = 0;
           
            sprite[end_id].death_by_mud = 0;  
        
            sprite[end_id].onDeath_action = -1; 
                        
            sprite[end_id].grenaded = DEATH_NORMAL; 

			// Setup initial movement ranges...
			if(sprite[end_id].sector == UNIT_DOG)
				sprite[end_id].movement = STA2_DOG_STEPS;
			if(sprite[end_id].sector == UNIT_GUNNER)
				sprite[end_id].movement = STA2_SCOUT_STEPS;
			if(sprite[end_id].sector == UNIT_HEAVY)
				sprite[end_id].movement = STA2_HEAVY_STEPS;
			if(sprite[end_id].sector == UNIT_SNIPER)
				sprite[end_id].movement = STA2_SNIPER_STEPS;
			if(sprite[end_id].sector == UNIT_MORTAR)
				sprite[end_id].movement = STA2_MORTAR_STEPS;
			if(sprite[end_id].sector == UNIT_CHIEF)
				sprite[end_id].movement = STA2_CHIEF_STEPS;
            
        }        
         
        if(sprite[end_id].type == UNT)     
        { 
            sprite[end_id].score = Calculate_TotalScore(end_id);   
        }                  

        if(sprite[end_id].type != OBJ)    
	       	Reposition_Unit(end_id);              
        
        if(angle == -1)      
        {   
                 
            sprite[end_id].mov_x = sprite[end_id].w+sprite[end_id].box_width/2;
            sprite[end_id].mov_y = sprite[end_id].z+sprite[end_id].box_height/2 - 0.016f;
   	
			if( sprite[end_id].mov_x  < -map_startX || sprite[end_id].mov_x  >  map_startX  || sprite[end_id].mov_y < -map_startY || sprite[end_id].mov_y >  map_startY  )
			{
				sprite[end_id].mov_x = (sprite[end_id].w + sprite[end_id].box_width/2);
				sprite[end_id].mov_y = (sprite[end_id].z + sprite[end_id].box_height/2); 
			}

	        sprite[end_id].end_x = sprite[end_id].mov_x;  // *** NEW ***
	        sprite[end_id].end_y = sprite[end_id].mov_y;  // *** NEW *** 
            
            Set_Heading(end_id, sprite[end_id].mov_x, sprite[end_id].mov_y, false);
            
        }    
        else   
        { 
            sprite[end_id].mov_x = (sprite[end_id].w + sprite[end_id].box_width/2) + (cos(sprite[end_id].angle)*0.016f);    
            sprite[end_id].mov_y = sprite[end_id].y + (sin(sprite[end_id].angle)*0.016f); 
   	
			if( sprite[end_id].mov_x  < -map_startX || sprite[end_id].mov_x  >  map_startX  || sprite[end_id].mov_y < -map_startY || sprite[end_id].mov_y >  map_startY  )
			{
				sprite[end_id].mov_x = (sprite[end_id].w + sprite[end_id].box_width/2);
				sprite[end_id].mov_y = (sprite[end_id].z + sprite[end_id].box_height/2); 
			}

	        sprite[end_id].end_x = sprite[end_id].mov_x;  // *** NEW ***
	        sprite[end_id].end_y = sprite[end_id].mov_y;  // *** NEW *** 
			 
        }

   		if(type != NON && type != OBJ) 
   		{   
		 				  
        if(p_type == SPAWN_PLAYER_UNIT)     
		{
			if(sprite[end_id].value2 != -1) 
			{
				sprite[end_id].rank  = sta2_squad[sprite[end_id].value2].rank;
				sprite[end_id].score = sta2_squad[sprite[end_id].value2].health; 
			}

			sprite[end_id].linked_sprite = p_server;  
            sprite[end_id].sector_action = AI_DEFEND; 

			if(sta2_squad[goto_point].type == STA2_CO)
			{
				if(sta2_co_type == STA2_CO_ADA) 
					sprite[end_id].sector = UNIT_GUNNER;
				if(sta2_co_type == STA2_CO_MARIE) 
					sprite[end_id].sector = UNIT_HEAVY;
				if(sta2_co_type == STA2_CO_ADELE) 
					sprite[end_id].sector = UNIT_SNIPER;
				if(sta2_co_type == STA2_CO_BELLA) 
					sprite[end_id].sector = UNIT_MORTAR;
			}
			if(sta2_squad[goto_point].type == STA2_HEAVY)
				sprite[end_id].sector = UNIT_HEAVY;
			if(sta2_squad[goto_point].type == STA2_SNIPER)
				sprite[end_id].sector = UNIT_SNIPER;
			if(sta2_squad[goto_point].type == STA2_MORTAR)
				sprite[end_id].sector = UNIT_MORTAR;

			if(sprite[end_id].score <= 1)   
			{
				sprite[end_id].status = MAN_DOWN1; 
				sprite[end_id].anim_state = WAIT;  
				sprite[end_id].update = true;
			}
		} 

        if(sprite[end_id].type == UNT)    
        if(p_type != SPAWN_PLAYER_UNIT)    
        {  

			sprite[end_id].name = rand()%sta2_no_enemy_names;

			sprite[end_id].return_fire = true;

            sprite[end_id].sector_action = AI_DEFEND;   

            sprite[end_id].rank = sta2_sector;       

			if(sta2_is_general_fight == true)
				sprite[end_id].rank = STA2_GENERAL_ARMY_LEVEL;
			 
			if(sta2_final_boss == true)     
				sprite[end_id].rank = STA2_FINAL_AREA_LEVEL;
                 
            if(p_type == SPAWN_EXTRA_RANK) 
                sprite[end_id].rank++;

            if(p_type == SPAWN_FINAL_BOSS)   
			{
                sprite[end_id].rank = STA2_FINAL_AREA_LEVEL+5;
				sprite[end_id].name = rand()%sta2_no_enemy_names;
			}
             
            sprite[end_id].score = Calculate_TotalScore(end_id);
              
            sprite[end_id].moving = false;
            sprite[end_id].anim_state = WAIT;
            sprite[end_id].update = true; 
   
            if(p_type == SPAWN_DECOY)   
            {   
                 sprite[end_id].rank = 1;   
 
				 if(a_global > 0)
	                 sprite[end_id].score = a_global;  
				 else
	                 sprite[end_id].score = DECOY_HEALTH;  

				 sprite[end_id].sector_action = AI_NONE; 
				 sprite[end_id].onDeath_action = -1;
				 sprite[end_id].anim = sprite[end_id].base_anim;
				 sprite[end_id].anim_state = LOOP;
            }  
                       
            if(ply_id != -1)    
            if(p_type == SPAWN_HUNT || p_type == SPAWN_MAUSER) 
            {
                       
                enemy_count++;
                WAVE_enemy_count++;

                mid_x = sprite[ply_id].w + sprite[ply_id].box_width/2;
                mid_y = sprite[ply_id].z + sprite[ply_id].box_height/2;
                
                sprite[end_id].mov_x = mid_x; 
                sprite[end_id].mov_y = mid_y;  
   	
				if( sprite[end_id].mov_x  < -map_startX || sprite[end_id].mov_x  >  map_startX  || sprite[end_id].mov_y < -map_startY || sprite[end_id].mov_y >  map_startY  )
				{
					sprite[end_id].mov_x = (sprite[end_id].w + sprite[end_id].box_width/2);
					sprite[end_id].mov_y = (sprite[end_id].z + sprite[end_id].box_height/2); 
				}
               
			/*	if(goto_point != -1)
				{
					sprite[end_id].end_x = points[goto_point].x;  
					sprite[end_id].end_y = points[goto_point].y;
				}
				else
				{*/
					sprite[end_id].end_x = sprite[end_id].mov_x;  
					sprite[end_id].end_y = sprite[end_id].mov_y;
			//	}

				 
				sprite[end_id].col_timer = 0; 
				sprite[end_id].bagging = false;   

                if(sprite[end_id].bagging == false)
                {    
                   
                    sprite[end_id].status = MOVE_OUT;       
                             
                    sprite[end_id].moving = true;
                               
                    Find_Path(end_id, sprite[end_id].end_x, sprite[end_id].end_y);     
              
                }  
                
                sprite[end_id].sector_action = AI_HUNT;
                
                sprite[end_id].update = true;                            
              
                sprite[end_id].anim_state = WAIT;              
               
                sprite[end_id].turning = false;
              
                sprite[end_id].all_timer = (int)TimerGetTime() + 200;                  
                          
            } 
            
			} // linked_sprite != UNIT_LEGS
                                
//            if(p_type == SPAWN_ALWAYS_ACTIVE)
 //               sprite[end_id].file_full = true;
                        
        } 

            
    }  
     
    return(end_id); 
}

bool Build_Man_Check(int loop, int x, int y, int build_type, bool row_check)
{
     
    bool test_success=true;   
    int index=0; 
    int guy_index=0;   
    int width_x=0; 
    int width_x1=0;
    int width_y=0; 
    int guy=0;
    float mid_x=0.0f, mid_y=0.0f;
    int temp_row_x=0;   
    int temp_row_y=0;
    int row_x=0, row_y=0; 

	if( loop < 0)
		return(0);     
     
    if(row_check == true)  
    {
        row_x = x;         
        row_y = y; 
        
    } 
    else
    {
    
        mid_x = sprite[loop].w+sprite[loop].box_width/2; 
        mid_y = sprite[loop].z+sprite[loop].box_height/2;    
        
        row_x = (int)((mid_x + map_startX)*10);       
        row_y = (int)((mid_y + map_startY)*10);      
    
    }
    
    if(build_type == UNIT_B_BARRACKS 
    || build_type == UNIT_B_COMMAND
    || build_type == UNIT_B_AIRFIELD
    || build_type == UNIT_B_FACTORY)  
    {
        width_x  = 3;  
        width_x1 = 2;   
        width_y = 2;
    }
    else
    {
        width_x  = 2;  
        width_x1 = 2;   
        width_y = 2;
    }
    
    if(build_type == UNIT_MOUNTED)  
    {
        width_x = 1;
        width_x1 = 1;   
        width_y = 1;
    }
    if(build_type == UNIT_MORTAR)
    {
        width_x = 1; 
        width_x1 = 1;    
        width_y = 1;
    } 
                            
    if(row_x > 2 && row_x < MAP_HEIGHT-3) 
    if(row_y > 2 && row_y < MAP_WIDTH-3)    
    for(int j=row_y-width_y;j<=row_y+width_y;j++)
    for(int i=row_x-width_x;i<=row_x+width_x1;i++)
    { 
 
        index = (j*MAP_HEIGHT)+i;               

        if(index >= 0 && index < MAP_TILES)
        { 
                 
          if(map_col[index]==1 || map_col[index]==6)          
            test_success = false; 
         
          if(tiles[index]!=223 && !(tiles[index] >= 80 && tiles[index] < 96) )               
          if( tiles[index] > 16 || tiles[index] == 13 || tiles[index] == 14)
            test_success = false;  
         
        }                

    }
    
    // Turn off loop's collision
    if(loop != -1)
    {
       mid_x = sprite[loop].w+sprite[loop].box_width/2; 
       mid_y = sprite[loop].z+sprite[loop].box_height/2;    
        
       temp_row_x = (int)((mid_x + map_startX)*10);       
       temp_row_y = (int)((mid_y + map_startY)*10);   
    
       map_col[(temp_row_y*MAP_HEIGHT)+temp_row_x]=0;
         
    // Run check against any men in the area
    for(int i=0;i<player_counter;i++)
    { 
            
      guy = player_list[i];     
       
	  if(guy >= 0)
      if(guy != loop && sprite[guy].score > 0)
      {
             
      mid_x = sprite[guy].w+sprite[guy].box_width/2; 
      mid_y = sprite[guy].z+sprite[guy].box_height/2;
      
      temp_row_x = (int)((mid_x + map_startX)*10);      
      temp_row_y = (int)((mid_y + map_startY)*10);  

      guy_index = (temp_row_y*MAP_HEIGHT)+temp_row_x;  

      for(int j=row_y-width_y;j<=row_y+width_y;j++)
      for(int i=row_x-width_x;i<=row_x+width_x1;i++)
      {
        index = (j*MAP_HEIGHT)+i;              
         
        if(index >= 0 && index < MAP_TILES)  
        if(index == guy_index)  
            test_success = false;     
      }
      
      }
       
      }   
    
    }
    
    return(test_success); 
    
}     

bool Is_Guy_In_Range(int loop, int target, float range)
{
    float midX =0.0f, midY =0.0f;
    float tarX =0.0f, tarY =0.0f;
    bool test_success=false;
    float closest_point = 0.0f; 
    float dis_to_point = 0.0f;
    
    if(loop == -1)
    {
        midX = -camX;
        midY = -camY;
    } 
    else 
    {    
        midX = sprite[loop].w+sprite[loop].box_width/2;
        midY = sprite[loop].z+sprite[loop].box_height/2;     
    }   
    
	if(target != -1)
	{          
	    tarX = sprite[target].w + sprite[target].box_width/2;
	    tarY = sprite[target].z + sprite[target].box_height/2; 
	}
    
    if(range == -1)
    { 
    closest_point = (float)gunner_rng;                  
    
	if(loop != -1)
	{
               
    if(sprite[loop].sector == UNIT_MORTAR1)
        closest_point = (float)mortar1_rng;                   
    if(sprite[loop].sector == UNIT_GUNNER)
        closest_point = (float)gunner_rng;
    if(sprite[loop].sector == UNIT_SHOTGUN)
        closest_point = (float)shotgun_rng;        
    if(sprite[loop].sector == UNIT_SHIELD)
        closest_point = (float)shield_rng;        
    if(sprite[loop].sector == UNIT_DUCK)
        closest_point = (float)gunner_rng;  
    if(sprite[loop].sector == UNIT_MONKEY)
        closest_point = (float)monkey_rng;    
    if(sprite[loop].sector == UNIT_DOG)
        closest_point = (float)dog_rng;    
    if(sprite[loop].sector == UNIT_BOX)
        closest_point = (float)monkey_rng;                                                          
    if(sprite[loop].sector == UNIT_BOMBER)
    {
        if(sprite[loop].onDeath_action != TANK_TOP)
            closest_point = (float)bomber_rng; 
        else
            closest_point = (float)tank_rng; 
    }
    if(sprite[loop].sector == UNIT_CHIEF) 
        closest_point = (float)chief_rng;  
    if(sprite[loop].sector == UNIT_SAILOR)   
        closest_point = (float)sailor_rng; 
    if(sprite[loop].sector == UNIT_GRUNT)   
        closest_point = (float)machine_rng;  
    if(sprite[loop].sector == UNIT_MACHINE)   
        closest_point = (float)grunt_rng; 
    if(sprite[loop].sector == UNIT_GUARD)   
        closest_point = (float)grunt_rng;                                                                       
    if(sprite[loop].sector == UNIT_MOUNTED)
        closest_point = (float)mounted_rng;   
    if(sprite[loop].sector == UNIT_MORTAR) 
        closest_point = (float)mortar_rng;         
    if(sprite[loop].sector == UNIT_RESCUE)
        closest_point = (float)rescue_rng; 
    if(sprite[loop].sector == UNIT_WORKER)
        closest_point = (float)worker_rng;   
    if(sprite[loop].sector == UNIT_SNIPER) 
        closest_point = (float)sniper_rng;         
    if(sprite[loop].sector == UNIT_TANK) 
        closest_point = (float)tank_rng; 
    if(sprite[loop].sector == UNIT_BIRD) 
        closest_point = (float)gunner_rng;
    if(sprite[loop].sector == UNIT_SKELETON) 
        closest_point = (float)skeleton_rng;        
    if(sprite[loop].sector == UNIT_DEAD_CHIEF)
        closest_point = (float)skeleton_rng;  
    if(sprite[loop].sector == UNIT_SHARK)
        closest_point = (float)shark_rng;  

    } // loop != -1
    
    if(ply_id != -1 && loop != -1)                          
    if(loop == ply_id)
        closest_point = p1_range; 
        
    	if(sprite[loop].sector_action == AI_BUDDY)
		if(Level != LVL_SUB_PEN)
	         closest_point = (float)BUDDY_SHOOT_RANGE; 
		else
	         closest_point = 2.0f; 
    }                                      
    else 
    {
        closest_point = range;    
    }
        
    dis_to_point = Node_Distance1(midX, midY, tarX, tarY);     
    
    if( dis_to_point < closest_point)
        test_success = true;
    else
        test_success = false;
     
    return(test_success); 
    
      
}
void Knock_Back(int guy_shooting, int guy_shot, int f_rate)
{
     float tar_x=0.0f, tar_y=0.0f;
     float mid_x=0.0f, mid_y=0.0f;
     int index=0;
     float angle=0.0f;
     int temp_row_x=0, temp_row_y=0;
     float deltax=0.0f, deltay=0.0f;      
     int collision_returned=0; 

	if(f_rate <= 0)
	    f_rate = 1; 
     
     if(guy_shooting != -1 && guy_shot != -1)
     {
                // KNOCKBACK FROM GETTING SHOT... 
            mid_x = sprite[guy_shooting].w+sprite[guy_shooting].box_width/2; 
            mid_y = sprite[guy_shooting].z+sprite[guy_shooting].box_height/2;  

            tar_x = sprite[guy_shot].w+sprite[guy_shot].box_width/2; 
            tar_y = sprite[guy_shot].z+sprite[guy_shot].box_height/2;  
            
            temp_row_x = (int)((tar_x + map_startX)*10);        
            temp_row_y = (int)((tar_y + map_startY)*10);  

            index = (temp_row_y*MAP_HEIGHT)+temp_row_x;        
            
        //    if(sprite[guy_shot].score > 0)
                map_col[index] = 0;                                                  
            
            angle = atan2(tar_y - mid_y,tar_x - mid_x);     

            deltax = cos(angle);    
            deltay = sin(angle);  
        
            deltax *= (float)KNOCKBACK;             
            deltay *= (float)KNOCKBACK*sc_ratio;

      //      deltax *= (float)f_rate;
      //      deltay *= (float)f_rate;    

            collision_returned = Test_Collision(sprite[guy_shot], deltax, 0.0f, false, guy_shot, false );

            if(collision_returned == ROUTE_GO)   
            {
                sprite[guy_shot].x += deltax;
                sprite[guy_shot].w += deltax;
            } 
            
            collision_returned = Test_Collision(sprite[guy_shot], 0.0f, deltay, false, guy_shot, false );

            if(collision_returned == ROUTE_GO)   
            {
                sprite[guy_shot].y += deltay; 
                sprite[guy_shot].z += deltay; 
            }
            
            tar_x = sprite[guy_shot].w+sprite[guy_shot].box_width/2; 
            tar_y = sprite[guy_shot].z+sprite[guy_shot].box_height/2;  
            
            temp_row_x = (int)((tar_x + map_startX)*10);        
            temp_row_y = (int)((tar_y + map_startY)*10);  

            index = (temp_row_y*MAP_HEIGHT)+temp_row_x; 

			if(index < 0)	
				return;
             
            if(sprite[guy_shot].score > 0) 
                map_col[index] = 6;
            else 
                map_col[index] = 0;    

            if(tiles[index]>=480 && tiles[index] < 484 )
                map_col[index] = 8;
                        
    }                 
    
}

void Remove_Item(int item_type, int item_value, int item_value1, bool remove_all)
{
                
    for(int i=0;i<16;i++)           
    {   
                         
        if(player_inv[i] == item_type)
        if(player_inv_value[i] == item_value || item_value == -1)
        if(player_inv_value1[i] == item_value1 || item_value1 == -1)
        {
                      
              player_inv[i] = INV_NONE; 
              
              player_inv_value[i]  = 0;
              player_inv_value1[i] = 0;
              player_inv_value2[i] = 0;   
              player_inv_value3[i] = 0;

              if(remove_all == false)   
                  break;           
                 
        }
                                           
    }       
    
    if(game_mode == WALK)          
        Calculate_Inventory();       
  
     
}

int Get_Number_Of_Item(int item_type, int item_value, int item_value1, bool remove_all)
{
    
    int success = 0;
                
    for(int i=0;i<16;i++)           
    {   
                         
        if(player_inv[i] == item_type)
        if(player_inv_value[i] == item_value || item_value == -1)
        if(player_inv_value1[i] == item_value1 || item_value1 == -1)
        {
              success++;           
        }
                                            
    }       
    
    return(success);      
     
}



bool Is_Grey_Area(float my_angle)
{
    bool success=true;
   
   
    if( my_angle >= 2.725f || my_angle <= -2.725f ) // RIGHT
    {   
        success=false;     
    }
    if( my_angle <= 0.275f && my_angle >= -0.275f ) // LEFT
    { 
        success=false;       
    }     
    if( my_angle <= -1.225f && my_angle >= -1.775f ) // DOWN
    {    
        success=false;     
    }
    if( my_angle >= 1.225f && my_angle <= 1.775f ) // UP
    {
        success=false;   
    }  
       
    if( my_angle <= -1.975f && my_angle >= -2.525f ) 
    {
        success=false;     
    }
    if( my_angle <= -0.475f && my_angle >= -1.025f )  // DOWN LEFT/RIGHT
    {
        success=false;     
    }
    if( my_angle >= 1.975f && my_angle <= 2.525f)
    {
        success=false;                            
    }
    if( my_angle >= 0.475f && my_angle <= 1.025f ) // UP LEFT/RIGHT
    {      
        success=false;                            
    }
   
 /*  
    if(my_angle >= -1.875f && my_angle <= -1.125f) // DOWN
    {    
        i_my_angle = DOWN;     
    }
    if(my_angle <= 1.875f && my_angle >= 1.125f) // UP
    {
        i_my_angle = UP;     
    }        
    if(my_angle >= 2.625f || my_angle <= -2.625f) // RIGHT
    {   
        i_my_angle = LEFT;     
    }
    if(my_angle <= 0.375f && my_angle >= -0.375f) // LEFT
    { 
        i_my_angle = RIGHT;      
    }  
    if(my_angle >= -2.625f && my_angle <= -1.875f) 
    {
        i_my_angle = DOWN_LEFT;     
    }
    if(my_angle >= -1.125f && my_angle <= -0.375f)  // DOWN LEFT/RIGHT
    {
        i_my_angle = DOWN_RIGHT;     
    }
    if(my_angle >= 1.875f && my_angle <= 2.625f)
    {
        i_my_angle = UP_LEFT;                            
    }
    if(my_angle <= 1.125f && my_angle >= 0.375f) // UP LEFT/RIGHT
    {      
        i_my_angle = UP_RIGHT;                            
    }*/
                                                                                           
    return(success);     
} 

void STA2_reset_old_vars()
{

	sta2_displaying_help = false;

	player_type = p_server;

	text_select = false;
	quit_active = false;

	NET_PLAYER = PLY1;

	lock_player = false;

	ply_dead = false;

	memset(player_inv, INV_NONE, sizeof(player_inv));
	memset(player_inv_value, 0, sizeof(player_inv_value));
	memset(player_inv_value1, 0, sizeof(player_inv_value1));
	memset(player_inv_value2, 0, sizeof(player_inv_value2));
	memset(player_inv_value3, 0, sizeof(player_inv_value3));
      
	memset(global_objective, GLOBAL_UNBEATEN, sizeof(global_objective));
	memset(global_side_objective, GLOBAL_UNBEATEN, sizeof(global_side_objective));  
           
	memset(global_objects, GLOBAL_UNBEATEN, sizeof(global_objects)); 
	memset(temp_global_objects, GLOBAL_UNBEATEN, sizeof(temp_global_objects));
	memset(tent_objects, TENT_NONE, sizeof(tent_objects));       
	memset(global_cards, CARD_BLANK, sizeof(global_cards)); 
	memset(global_medals, MEDAL_BLANK, sizeof(global_medals));
  
	memset(main_mission, UNBEATEN, sizeof(main_mission));     
     
	memset(shop_sold, UNSOLD, sizeof(shop_sold));             
    
	memset(main_mission, UNBEATEN, sizeof(main_mission));

	current_new_game = false;

	dm_game = DM_NONE;

	hours   = 8;                                    
	minutes = 0;     

	daytime = DAYTIME;  

	has_buddy = BUDDY_WAIT;

	Reset_Specials(); 

	player_rank = 1; 

	current_act = 1;

	current_char = CHAR_RIFLE;

	current_healthkit = 0;

	current_difficulty = 0;

	current_spawn = 0;
    
	stat_rifle_skill  = 14; // = 6                             
	stat_pistol_skill = 10; // = 5                     
	stat_firepower    = 10;                  
	stat_accuracy     = 10; // = 5                                   
	stat_vitality     = 30; // = 5          
	stat_agility      = 18;                                             
	stat_defense_base = 15;                         
	stat_max_life     = 60;  
                                                                    
	current_helmet  = -1;                                                
	current_boot    = -1;                              
	current_grenade = -1;                                                                                                                      
	current_medal   = -1; 
	current_trap    = -1;     
	current_special  = -1;                                                                 
	last_current_rifle=-1; 
	last_current_pistol=-1;
                             
	current_gold    = -1; 
	current_scrap   = 0;      
	current_act = 1;                       
	current_spawn   = -1;                             
	current_ladder_sector=-1;                      
	current_ladder_spawn=-1;                                                                    
	mission = MISSION_NONE;                 
	mission_objective=MISSION_OFF;                      
	lock_player = false;                                
	on_a_mission = false;                                                                                     
	no_lights_on = 0;                                           
	total_no_bottles = 0;                                      
                                     
	has_all_cards = false;                                    
	has_all_furniture = false;                
	pigeon_finished = false; 

	current_trousers=WEARING_TROUSERS;  
	current_headwear=WEARING_NONE;
                        
	player_experience = 0;     
	player_exp_level = EXP_FIRST_LEVEL;        
     
	PLY_VITALITY  = ((stat_vitality)* VITALTY_INC)  + VITALITY_BASE;
     
	player_health = PLY_VITALITY; 
	old_health    = PLY_VITALITY;    

	mission = MISSION_NONE;  

	Calculate_Item(999, INV_HGUN_AMMO, -1, 0, 1, -1);
	Calculate_Item(999, INV_AMMO, -1, 0, 1, -1);
	Calculate_Item(TRAINING_PISTOL, INV_PISTOL, -1, 0, -1, -1);
	Calculate_Item(FARMERS_RIFLE, INV_RIFLE, -1, 0, -1, -1); 
	Calculate_Item(1, INV_HELMET, -1, 0, 1, -1);

	Calculate_Stats(); 
		  
	current_file = -1;  
		 
	new_game = true;  

}
  
void Start_Game()  
{
	   
	STA2_reset_old_vars(); 

	if(sta2_playing_tutorial == true) 
	{
		sta2_displaying_help = true;
		sta2_environment_type = AREA_CASTLE;
		sta2_first_area = AREA_CASTLE;
		scene = 17;
		episode = 1;
	}
	else
	{
		scene = 2;
		episode = 1;
	}


	next_scene = true;
}   

float Convert_Dir_To_Angle1(int direction)
{
    float success = 0.0f;
    
    if(direction == DOWN)
        success = -1.5f;
    if(direction == UP)
        success = 1.5f; 
    if(direction == LEFT)
        success = -3.0f;
    if(direction == RIGHT)
        success = 0.0f;  
    if(direction == UP_RIGHT)
        success = 0.75f;
    if(direction == UP_LEFT)
        success = 2.25f;
    if(direction == DOWN_RIGHT)
        success = -0.75f;
    if(direction == DOWN_LEFT)
        success = -2.25f; 
        
    return(success);
              
}
 
void Run_Gibs(int guy_shooting, int guy_shot, int f_rate)
{
 /*   if(sprite[guy_shot].score <= 0)
    if(sprite[guy_shot].type == UNT)       
    if(sprite[guy_shot].onDeath_action != TURRET)  
    {   

           if(guy_shot != ply_id && sprite[guy_shot].on_mud == false && sprite[guy_shot].grenaded != DEATH_GRENADE ) // && sprite[guy_shot].grenaded != DEATH_HEADSHOT
           {
                     
               Create_Gibs_Effect(guy_shot, false, -1);   
               
               splatted_sfx=true; 
               
               New_FX(sprite[guy_shot].x, sprite[guy_shot].y-0.0001f, sprite[guy_shot].x, sprite[guy_shot].y, 59, PLAY, sprite[guy_shot].width, sprite[guy_shot].height, sprite[guy_shot].width, sprite[guy_shot].height, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);
               
               if(guy_shot != ply_id)
                   Knock_Back(guy_shooting, guy_shot, f_rate);

               sprite[guy_shot].splatted = true;
                               
               if(sprite[guy_shot].splatted == false && sprite[guy_shot].status != MAN_DOWN && sprite[guy_shot].status != MAN_DOWN1)
               {
                   sprite[guy_shot].status = DIEING;
                   sprite[guy_shot].anim_state = WAIT;  
                   sprite[guy_shot].update = true;    
                   
                   sprite[guy_shot].dflash_timer = 1;
                   sprite[guy_shot].death_flash  = true;
                                   
                   Rank_Timer(guy_shot, sprite[guy_shot].status);                            
               }   

               
           }
    }    */ 
     
     
}

void Turn_On_Torch(int index, bool on_off)   
{

		if(index >= 0)        
        if(sprite[index].sector_action == OBJ_LIGHT1)
        {
                                         
            if(on_off == true)
                sprite[index].linked_sprite = LIGHT_ON; 
            else
                sprite[index].linked_sprite = LIGHT_OFF;
                
            if(sprite[index].linked_sprite == LIGHT_OFF)
                Set_Sprite( index, sprite[index].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING); // Stunned
            if(sprite[index].linked_sprite == LIGHT_ON)
                Set_Sprite( index, sprite[index].base_anim+1, LOOP, ANIM_SPRITE, ANIM_WALKING); // Stunned
                
            if(sprite[index].onCreate_action == LIGHT_TORCH)
                torch_sfx = true; 
                
            if(sprite[index].onCreate_action == LIGHT_ELECTRIC)
                lightswitch_sfx = true;  
            
        }   
        
}

void Shot_Missed(int loop, int no_test, float x2, float y2)
{

}

void New_Healthbar(int index, int quick_display)  
{

	float widthX1=0.0f, heightY1=0.0f; 
 	bool already_exists=false;

	 
	if(index < 0)
		return; 

	if(sprite[index].sector == UNIT_BOSS)
		return;

		  // Delete any older health 
		  if(index != -1) 
    	  for(int i=0;i<no_fx;i++)             
          {              
              if(Fx[i].sector == FX_HEALTHBOX)           				
              if(Fx[i].linked_sprite == index)
			  if(Fx[i].turn_off == false)
			  {          				
			  	if( quick_display == 1)  
		    		Fx[i].sparkle_timer = (int)TimerGetTime()+150;   
				else 
		    		Fx[i].sparkle_timer = (int)TimerGetTime()+1500; 

				already_exists=true;				

				break;      

			  }  
		  }    
		 
		  if( already_exists == false)    
		  {

			  New_FX(sprite[index].x, sprite[index].y,  sprite[index].w, sprite[index].z, 4, LOOP, sprite[index].box_width, sprite[index].box_height, sprite[index].width, sprite[index].height, 2, GFX, 1.0f, index, 0, FX_HEALTHBOX, index, 2, 0, 0, quick_display);
			   
	  	      widthX1 = sprite[index].width/10;  
	  	      heightY1 = (sprite[index].height/6)/5;
	
  		  	  if( sprite[index].score <= Calculate_TotalScore(index)/3 || sprite[index].linked_sprite != player_type ) 
			      New_FX(sprite[index].x + widthX1, (sprite[index].y+sprite[index].height)+heightY1,  sprite[index].w, sprite[index].z-0.0001f, 2, LOOP, sprite[index].box_width, sprite[index].box_height, (sprite[index].width - (widthX1*2)), 0.0125f, 2, GFX, 1.0f, index, 0, FX_HEALTHBAR, index, 2, 0, 0, quick_display);
		  	  else
			  	  New_FX(sprite[index].x + widthX1, (sprite[index].y+sprite[index].height)+heightY1,  sprite[index].w, sprite[index].z-0.0001f, 1, LOOP, sprite[index].box_width, sprite[index].box_height, (sprite[index].width - (widthX1*2)), 0.0125f, 2, GFX, 1.0f, index, 0, FX_HEALTHBAR, index, 2, 0, 0, quick_display);

		  }
		   
}

void Calculate_Arcade_Score(int index, int guy_status, int torso_targeted)
{

	float mid_x=0.0f, mid_y=0.0f;

	int temp_arcade_score = 1000;
	int letter1=0;
	int letter2=0;
	int letter3=0;
	int letter4=0;
	int letter5=0;
	int letter_length=0;
	float letter_width=0.0f;
	float letter_total_width=0.0f;
	int letters[20];

	if(sprite[index].sector == UNIT_MONKEY)  
		temp_arcade_score=750; 

	if(sprite[index].sector == UNIT_SHOTGUN) 
		temp_arcade_score=6000;    

	if(sprite[index].sector == UNIT_SHIELD) 
		temp_arcade_score=2000; 
	 
	if(sprite[index].rank == 2)  
		temp_arcade_score *= 3;

	if(torso_targeted == TARGET_HEAD)
		temp_arcade_score += temp_arcade_score/4; 
	if(guy_status == OPEN_CUT)
		temp_arcade_score += temp_arcade_score/2;

	if(arcade_bonus == 1)
		temp_arcade_score*= 2; 

	arcade_score += temp_arcade_score;
	arcade_score += temp_arcade_score; 

	if(temp_arcade_score < 100000)
		letter_length=6;
	if(temp_arcade_score < 10000)
		letter_length=5;
	if(temp_arcade_score < 1000)
		letter_length=4; 
	if(temp_arcade_score < 100)
		letter_length=3;
	if(temp_arcade_score < 10)  
		letter_length=2;  
	
	for(int i=0;i<letter_length;i++)
	{
		letters[1] = temp_arcade_score%10;
		letters[2] = (temp_arcade_score/10)%10; 
		letters[3] = (temp_arcade_score/100)%10;
		letters[4] = (temp_arcade_score/1000)%10; 
		letters[5] = (temp_arcade_score/10000)%10;
		letters[6] = (temp_arcade_score/100000)%10;
	}
	 
	letter_width = 0.025f;  
	letter_total_width = letter_width*(float)letter_length;  

	mid_x = (sprite[index].x + sprite[index].width/2)-(letter_total_width/2);
	mid_y = sprite[index].y + (sprite[index].height*1.25f);

	for(int i=0;i<letter_length;i++)  
	{
		if(i==0) 
			New_FX(mid_x, mid_y, mid_x, mid_y, 10, LOOP, letter_width, 0.05f, letter_width, 0.05f, 3, GFX, 1.0f, -1, -1, FX_SCORE, -1, 39, -1, -1, -1);
		else
		{
			New_FX(mid_x+(0.025f*i), mid_y, mid_x+(0.025f*i), mid_y, letters[letter_length-i], LOOP, letter_width, 0.05f, letter_width, 0.05f, 3, GFX, 1.0f, -1, -1, FX_SCORE, -1, 39, -1, -1, -1);
		}
	}
 
}