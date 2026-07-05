
#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h> 
#include <math.h>  
#include "globals.h"  
  
extern float Node_Distance(float x1, float y1, float x2, float y2);
extern float Node_Distance1(float x1, float y1, float x2, float y2);
extern int Is_Guy_In_Sight(float my_angle, float target_angle);
extern int Find_Path(int loop, float destX, float destY); 
extern bool Build_Man_Check(int loop, int x, int y, int build_type, bool row_check);
extern int Get_Nearest_Depot(int loop, bool check);
extern void ShotIdle(int loop);  
extern int Convert_Angle_To_Dir(float my_angle); 
extern bool Is_Guy_In_Range(int loop, int target, float range);
extern void Calculate_Buddy(bool turn_on, int slot, int index);
extern bool Shoot_Ray(int loop, float x1, float y1, float x2, float y2, bool grey_test, bool shooting, float precision);
extern void Shoot_Test(int loop, int f_rate);

void AI_Command(int f_rate);  
bool TestSpriteToPoint(float x1, float y1, float x2, float y2);
void AI_Check_For_Enemies(int loop);
void Refresh_Pnts();      
void Gunner_Command(int loop);
void Move_AI_Formation(int group, bool rallying);
void Group_Command();
void Reset_Build_Types(int loop); 
void Create_Defend_List();
void Alert_Enemies(int no_test, int loop);
bool Spawn_A_Guy(int number_of_dudes, int best_point, bool buddy, int trap, int sprite_point, int goto_point); 
void Raise_Alarm(); 
bool Is_Sprite_Onscreen(int index);
bool Get_Free_Point(int loop, int best_point, bool buddy);

 
void Reset_Build_Types(int loop)   
{

                     
}

void Group_Command()  
{
     
    bool group_ready = true;
  
     
}

void Move_AI_Formation(int group, bool rallying)
{
    
}   

void Gunner_Command(int loop)
{
 
}

  

// Sta2 A.I control... 

void AI_Command(int f_rate)
{  
	int loop = -1;

	int rnd=0;
	int gotoX=0;
	int gotoY=0;

	int index=0;

	int unit_count=0;
	int unit_list[100];

	int unit_dog_count=0;
	int unit_dog_list[100];

	bool player_is_cammoed=false;

	float distance=0.0f, closest=100000.0f;
	float mid_x=0.0f, mid_y=0.0f;
	float tar_x=0.0f, tar_y=0.0f;

	int sta2_p1_count = 0; 
	int sta2_p1_list[100]; 

	if(sta2_turn == TURN_COMPUTER)     
	{

		// Select a unit first... 
		if(emy_id == -1)   
		{ 
			#if WALK_BUG_TEST == 1 

			test_walk_count = 0;  

			// delete later...
			for(int y=0;y < MAP_HEIGHT;y++)     
			for(int x=0;x < MAP_WIDTH;x++)    
			if(test_walk_count < 200000)
			{
				index = (y * MAP_WIDTH)+x;

				if(map_col[index] == 0)
				{
					test_walkX[test_walk_count] = x;
					test_walkY[test_walk_count] = y;
					test_walk_count++;
				} 
			}

			#endif

			// Selecting an enemy unit to use...
			for(int i=0;i<player_counter;i++)  
			{  
				loop = player_list[i];      

				if(sprite[loop].type == UNT)
				if(sprite[loop].linked_sprite == player_type)
				if(sprite[loop].score > 1)
				if(sprite[loop].camo == true)
					player_is_cammoed = true;

				if(sprite[loop].type == UNT)
			//	if(sprite[loop].unit_moved == false || UNITS_CAN_MOVE_MORE_THAN_ONCE == 1)
				if(sprite[loop].linked_sprite != player_type)
				if(sprite[loop].score > 0)
				{
					if(sprite[loop].sector == UNIT_DOG)
					{
						unit_dog_list[unit_dog_count] = loop;
						unit_dog_count++;
					}

					unit_list[unit_count] = loop;
					unit_count++;
				}  

			}

			// Set emy_id...
			if(unit_count != 0)
			{

				if(player_is_cammoed == true && unit_dog_count > 0)
					loop = unit_dog_list[rand()%unit_dog_count];
				else
					loop = unit_list[rand()%unit_count];

				if(loop != -1)
				{
					emy_id = loop; 
					ShotIdle(loop);   
				}
			 
			}

			if(unit_count == 0)
			{
				sta2_enemy_mode = MOVE_END;
				sta2_timer = (int)TimerGetTime() + 2000;
			}

		} // emy_id == -1 
 
		//if(emy_id != -1)
		//	sprite[emy_id].unit_moved = true;
	   
		// Move an enemy towards a random target...
		if(sta2_enemy_mode == MOVE_WAIT)   
		if(emy_id != -1)  
		{  
			 
			mid_x = sprite[emy_id].w + sprite[emy_id].box_width/2; 
			mid_y = sprite[emy_id].z + sprite[emy_id].box_height/2; 

			// Selecting a player unit to target...
			if(the_target == -1) 
			{
				rnd = rand()%4;

				for(int i=0;i<player_counter;i++) 
				{  
					 
					loop = player_list[i];  
					  
					if(loop >= 0)
					{

						tar_x = sprite[loop].w + sprite[loop].box_width/2; 
						tar_y = sprite[loop].z + sprite[loop].box_height/2;  
			 
						if(sprite[loop].type == UNT)  
						if(sprite[loop].camo == false || sprite[emy_id].sector == UNIT_DOG)
						if(sprite[loop].linked_sprite == player_type)
						if(sprite[loop].score > 1)
						{

							distance = Node_Distance1(mid_x, mid_y, tar_x, tar_y);

							if(rnd != 0) 
							if(distance < closest)
							{
								the_target = loop;
								closest = distance;
							}
							if(rnd == 0)
							{
								sta2_p1_list[sta2_p1_count] = loop;
								sta2_p1_count++;
							}
						} 
					}
				} 
		
				// Set the target...
				if(sta2_p1_count != 0) 
				{
					the_target = sta2_p1_list[rand()%sta2_p1_count]; 
				}
			}
			 
			if(the_target == -1)
			{
				sta2_enemy_mode = MOVE_END;
				sta2_timer = (int)TimerGetTime() + 2000;
			}
			 
			// Move to the target...    
			if(the_target != -1 && emy_id != -1)         
			{     

				sprite[emy_id].col_timer = 0;    
				 
				ShotIdle(emy_id);  

				sprite[emy_id].mov_x = sprite[emy_id].w + sprite[emy_id].box_width/2;
				sprite[emy_id].mov_y = sprite[emy_id].z + sprite[emy_id].box_height/2;

				sprite[emy_id].end_x = sprite[emy_id].mov_x;
				sprite[emy_id].end_y = sprite[emy_id].mov_y;

				tar_x = sprite[the_target].w + sprite[the_target].box_width/2;
				tar_y = sprite[the_target].z + sprite[the_target].box_height/2;
				 
				#if WALK_BUG_TEST == 1  
					// Remove this...
					rnd = rand()%(test_walk_count);   

					gotoX = test_walkX[rnd];              
					gotoY = test_walkY[rnd];  

					tar_x = -map_startX + ( ((float)gotoX * 0.1f) + 0.05f ); // -5.0, 0.1
					tar_y = -map_startY + ( ((float)gotoY * 0.1f) + 0.05f ); // -5.0, 0.1
				#endif

				if(Find_Path(emy_id, tar_x, tar_y))
				{
					sta2_enemy_mode = MOVE_MOVE; 
					sta2_timer = 0; 
				}
				else 
				{
					sta2_enemy_mode = MOVE_END;
					sta2_timer = (int)TimerGetTime() + 2000;
				}   
			 
			}        
			        
		}   
    
	// Shoot at target if within range or has run out of moving...
	if(sta2_enemy_mode == MOVE_MOVE || sta2_enemy_mode == MOVE_AIM || sta2_enemy_mode == MOVE_FOCUS)  
	if((int)TimerGetTime() > sta2_timer)     
	if(emy_id != -1 && the_target != -1)   
	if(sprite[emy_id].score > 0)        
	{
		#if WALK_BUG_TEST == 0  
		Shoot_Test(emy_id, f_rate);   
		#endif
	} 
	 
	if(sta2_enemy_mode == MOVE_SHOOT)               
	if((int)TimerGetTime() > sta2_timer)
	if((int)TimerGetTime() > sta2_mg_timer)
	if((int)TimerGetTime() > sta2_chief_timer)
	{
		sta2_enemy_mode = MOVE_REFOCUS;
		sta2_timer = (int)TimerGetTime() + 750;
	}

	if(sta2_enemy_mode == MOVE_REFOCUS)          
	if((int)TimerGetTime() > sta2_timer)
	{
		sta2_enemy_mode = MOVE_END;
		sta2_timer = (int)TimerGetTime() + 750;
	}

	if(next_scene == false)  
	if(sta2_enemy_mode != MOVE_END)   
	if(emy_id != -1)
	if(sprite[emy_id].score <= 0) 
	{
		sta2_enemy_mode = MOVE_END;
		sta2_timer = (int)TimerGetTime() + 2000;

	}

	if(next_scene == false)  
	if(sta2_enemy_mode == MOVE_END)          
	if((int)TimerGetTime() > sta2_timer) 
	{ 
	  
		sta2_machinegun_index = -1;
		sta2_mg_timer = 0;
		sta2_mg_fired = 0;

		sta2_chief_index = -1;
		sta2_chief_timer = 0;
		sta2_chief_fired = 0;

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

		}                      
             
		next_scene = true;

	}


	} // sta2_turn == TURN_COMPUTER


                         
}

bool TestSpriteToPoint(float x1, float y1, float x2, float y2)
{      
    bool test_success=false;  
    
    float x=0.0f, y=0.0f;
    float angle=0.0f, deltax=0.0f, deltay=0.0f;
    float step=0, distance=0.0f;
    int iterations=0;
    int loop=0; 
    int rnd=0;
    int temp_r_x=0;
    int temp_r_y=0;
    int temp_row=0;
    
    x = x1;
    y = y1; 
    
    distance = Node_Distance(x1, y1, x2, y2);   
   
    angle = atan2(y2 - y1,x2 - x1);     
    
    deltax = cos(angle);    
    deltay = sin(angle); 
        
    deltax *= 0.05f;      
    deltay *= 0.05f;
        
    step = Node_Distance(x1, y1, x1+deltax, y1+deltay);
    
    if(step != 0)
    iterations = (int)(distance / step);
    
//    iterations -= 1;  
       
    if(iterations < 0) 
        iterations = 0; 
            
    if(distance < 4.0f)          
    for (int i = 0; i < iterations; i++)
    {   
         
        x += deltax; // Which is the mid_x 
        y += deltay; // Which is the mid_y
        
        temp_r_x = (int)((x + map_startX)*10);   
        temp_r_y = (int)((y + map_startY)*10);  
         
        temp_row = (temp_r_y*MAP_HEIGHT)+temp_r_x;   
                  
        if( temp_row >= 0 && temp_row < MAP_TILES)
        if(map_col[temp_row]==1)   
        {
            test_success = true; 
            break;
        }
    
    }      
    
//    if(distance >= 2.0)
//        test_success = true;
      
    return(test_success);       
     
}

void AI_Check_For_Enemies(int loop)
{
    
    float dis_to_point=0.0f;  
    float midX =0.0f, midY =0.0f; 
    float tarX =0.0f, tarY =0.0f; 
    int best_point=-1;
    float closest_point = 0.0f;
    float angle_to_target=0.0f; 
    int index=0;
    int alert_guy=0;

	if(loop >= 0)
	{

    midX = sprite[loop].w+sprite[loop].box_width/2;
    midY = sprite[loop].z+sprite[loop].box_height/2;
     
    closest_point = (float)ENEMY_ACT_RANGE;           
    
    if(sprite[loop].sector == UNIT_SKELETON)  
        closest_point = (float)SKELETON_ACT_RANGE;
            
    if(sprite[loop].sector == UNIT_DEAD_CHIEF)
        closest_point = (float)SKELETON_ACT_RANGE;
            
    if(sprite[loop].sector == UNIT_SHOTGUN)
        closest_point = (float)SHOTGUN_ACT_RANGE;
            
    if(sprite[loop].sector == UNIT_MORTAR1)
        closest_point = (float)MORTAR1_ACT_RANGE;
            
    if(sprite[loop].sector == UNIT_DOG)
        closest_point = (float)DOG_ACT_RANGE;
                                                  
    if(sprite[loop].status == STAMPING)
        closest_point = (float)STAMPING_RANGE;
        
    if(sprite[loop].status == CRYING)
        closest_point = (float)CRYING_RANGE; 
        
    if(sprite[loop].sector_action == AI_BUDDY)
        closest_point = (float)BUDDY_ACT_RANGE;   
        
	if(Level == LVL_SUB_PEN) 
    if(sprite[loop].sector_action == AI_BUDDY)
        closest_point = (float)BUDDY_BOSS_ACT_RANGE;  
         
    if(sprite[loop].sector == UNIT_BOMBER)  
        closest_point = (float)BOMBER_ACT_RANGE; 
         
    if(sprite[loop].sector_action == AI_HUNT)  
        closest_point = (float)HUNT_RANGE;     

//	if(in_dungeon == true) 
//		closest_point -= 0.1f;    
    
    for(int k=0;k<player_counter;k++)         
    {   
                      
      index = player_list[k];   
	  
	  // Check for dead or dieing guys..  
/*	  if(loop != index)  
	  if(index != p1_buddy)    
	  if(sprite[loop].sector != UNIT_BOMBER || index == ply_id)	
      if(sprite[index].status != FALLING && sprite[index].status != LEVELING)
      if(sprite[index].sector != UNIT_MONKEY) 
      if(sprite[index].sector != UNIT_DOG)
      if(sprite[index].status != GROUND_SPAWN)  
      {   
                
            tarX = sprite[index].w+sprite[index].box_width/2;
            tarY = sprite[index].z+sprite[index].box_height/2;  
             
            angle_to_target = atan2(tarY - midY,tarX - midX);     
                        
            dis_to_point = Node_Distance1(midX, midY, tarX, tarY);  
			   
			// Heal a dieing buddy...
			if(sprite[loop].sector != UNIT_SKELETON)   
            if(sprite[loop].sector != UNIT_MONKEY)   
            if(sprite[loop].sector != UNIT_SHOTGUN)   
            if(sprite[loop].sector != UNIT_SHIELD)        
            if(sprite[loop].sector != UNIT_DOG)   
            if(sprite[loop].sector != UNIT_DEAD_CHIEF)
			if(sprite[loop].sector != UNIT_MACHINE)	
			if(sprite[loop].sector != UNIT_GUARD)
			if(Level != LVL_UNDERGROUND)		 	
			if(sprite[loop].group_id == -1)   
			if(index != p1_id && index != p1_buddy)
			if(sprite[index].grenaded != DEATH_GRENADE)
			if(sprite[index].score <= 0 || sprite[index].status == MERCY || sprite[index].status == MERCY1)
			if(sprite[index].status != DEATH_READY && sprite[index].status != MAN_DOWN1)
			if(sprite[index].group_id != -2) // Has been revived once already..			
			if(sprite[loop].ai_brain != BRAIN_HEALING ) // && sprite[loop].ai_brain != BRAIN_HUNTER
			if(sprite[loop].linked_sprite == sprite[index].linked_sprite)
            if(dis_to_point < 0.4f)
            if(Shoot_Ray(-1, midX, midY, tarX, tarY, false, false, 0.001f) == false)    
            {   
			   if(Find_Path( loop, (sprite[index].w+sprite[index].box_width/2), (sprite[index].z+sprite[index].box_height/2) )==true)
			   {  
                   sprite[loop].ai_brain = BRAIN_HEALING;
				   sprite[loop].group_id = index;  // The dude I'm gonna go heal...
			   }
            }     
        }  */
         
	  if( loop != p1_buddy || sprite[index].spotted == true || sprite[index].sector == UNIT_BOSS)
	  if(sprite[index].sector != UNIT_BOMBER || sprite[index].grab_switch == true )  
	  if(sprite[loop].ai_brain != BRAIN_HEALING) 	                    
      if((sprite[index].type == UNT && (sprite[index].status != SPECIAL || special_reacts == true)  ) 
	  || ( sprite[index].type == BAG && sprite[index].sector == UNIT_BOSS && sprite[index].sector_action != AI_STAND)  )
      if(sprite[loop].linked_sprite != sprite[index].linked_sprite) 
      if(sprite[index].status != FALLING && sprite[index].status != LEVELING)
      if(sprite[index].grab_switch == true)       
      if(sprite[index].score > 0 && sprite[index].status != GROUND_SPAWN) 
      {   
                
            tarX = sprite[index].w+sprite[index].box_width/2;  
            tarY = sprite[index].z+sprite[index].box_height/2;  
             
            angle_to_target = atan2(tarY - midY,tarX - midX);    
                         
            dis_to_point = Node_Distance1(midX, midY, tarX, tarY);     

            if(dis_to_point < closest_point)      
            if(Shoot_Ray(loop, midX, midY, tarX, tarY, false, false, 0.01f) == false || sprite[loop].sector == UNIT_BOMBER)   
            {   
                 
               if( (Is_Guy_In_Sight(sprite[loop].angle, angle_to_target) > 0 || sprite[loop].sector == UNIT_BOMBER || loop == p1_buddy) 
               || sprite[loop].sector == UNIT_DOG
               || sprite[loop].sector == UNIT_SKELETON
               || sprite[loop].sector == UNIT_DEAD_CHIEF) // Bird doesn't need to see EMY
               { 

                   closest_point = dis_to_point;  
                   best_point = index;   
                       
               } 
                 
            }    
        } 
        
      }  // end of for loop   
  
      if(best_point != -1) // An enemy is within shooting range!
      {      
		     
          sprite[loop].fire_target = best_point;
          
       //   Find_Path(loop, sprite[best_point].w+sprite[best_point].box_width/2, sprite[best_point].z+sprite[best_point].box_height/2); 

       /*   if(ply_id != -1 && sprite[loop].sector_action != AI_BUDDY)   
          {    
                 
              alert_enemies = true;  
              noise_type = LOUD_NOISE;                 
              
              noise_x = sprite[best_point].w+sprite[best_point].box_width/2;                        
              noise_y = sprite[best_point].z+sprite[best_point].box_height/2; 
              
              alert_guy = best_point; 
              
          }*/
          
      }
   
	} // loop >= 0
                  
}
void Raise_Alarm()
{

       
}

 
void Alert_Enemies(int no_test, int loop)
{   
       float range = 0.0f;   
       float midX=0.0f, midY=0.0f;
       bool update_coords = false; 
       
/*	   if(loop != -1)
       {

       midX = sprite[loop].w + sprite[loop].box_width/2;
       midY = sprite[loop].z + sprite[loop].box_height/2; 
	   
                        
       if(noise_maker == LOUD_NOISE)
       {
           range = (float)LOUD_NOISE_RANGE;  
           
           if(screen_mode != SCREEN_NORMAL)
               range += 0.2f;
       } 
   
       if(noise_maker == SOFT_NOISE)           
           range = (float)SOFT_NOISE_RANGE;  
          
       if(noise_maker == MID_NOISE)           
           range = (float)MID_NOISE_RANGE;              
           
       if(sprite[loop].status == SPECIAL && special_reacts == false)    
           range = (float)MID_NOISE_RANGE;   
	   
	   // Spotted an enemy and chance to be BRAIN_HUNTER...	        
       if(loop != no_test) 
       if(loop != p1_buddy || p1_buddy == -1 || buddy_in_water == false)   
	   if(sprite[loop].ai_brain != BRAIN_HEALING)  
	   if(noise_maker != SOFT_NOISE || sprite[loop].status == IDLE)
       if(sprite[loop].type == UNT && sprite[loop].turn_off == false)
       if(sprite[loop].status != OPEN_FIRE && sprite[loop].status != OPEN_THROW 
	   && sprite[loop].status != STUNNED   && sprite[loop].status != FOOT_SHOT
	   && sprite[loop].status != FLATTENED)  
       if(sprite[loop].sector != UNIT_ARMOUR_TURRET)
       if(sprite[loop].score > 0 && loop != ply_id )
       if(Node_Distance1(midX, midY, noise_x, noise_y) <  LOUD_NOISE_RANGE)
       { 
            
          if(rand()%6 == 0) 
          if(sprite[loop].status != SPECIAL) 
          if(sprite[loop].ai_brain != BRAIN_HEALING)
          if(sprite[loop].sector != UNIT_SHOTGUN)
          if(sprite[loop].sector != UNIT_MACHINE)
          if(sprite[loop].sector != UNIT_GUARD) 
          if(sprite[loop].linked_sprite != p_server) 
          {
			  	 							 
              sprite[loop].ai_brain = BRAIN_HUNTER; 
			  
			  if(sprite[loop].sector != UNIT_MONKEY)
			  if(sprite[loop].sector != UNIT_DOG)
			  if(hud[2].alpha == 0.0f) // Fixes constant talking bug...
			  {

			  	  if(Level == LVL_HIGHWAY) 
  	                  Display_Message(loop, MSG_CHARGE_HIGHWAY); 

			  	  if(Level == LVL_FARMS) 
  	                  Display_Message(loop, MSG_CHARGE_FARMS); 
			   						 
			  	  if(Level == LVL_BUNKER_A 
			  	  || Level == LVL_BUNKER_B
			  	  || Level == LVL_BUNKER_C) 
  	                  Display_Message(loop, MSG_CHARGE_BUNKER); 

			  	  if(Level == LVL_CAVE  
			  	  || Level == LVL_SECRET_LAB
			  	  || Level == LVL_BOTTOM_LAB) 
  	                  Display_Message(loop, MSG_CHARGE_DUNGEON); 
			   						 
			  	  if(Level == LVL_WINDMILL) 
  	                  Display_Message(loop, MSG_CHARGE_WINDMILL); 
						             
				  if(Level == LVL_SUPPLIES
				  || Level == LVL_BAY
				  || Level == LVL_PLAINS 
				  || Level == LVL_TOWN
				  || Level == LVL_VILLAGE)
  	                  Display_Message(loop, MSG_CHARGE);  
  	                  
				  if(Level == LVL_TOWN)
  	                 Display_Message(loop, MSG_CHARGE_TOWN); 
  	                   
				  if(Level == LVL_CINEMA  
				  || Level == LVL_SCREENING)
  	                  Display_Message(loop, MSG_CHARGE_CINEMA); 
  	                  
				  if(Level == LVL_UNDERGROUND)
  	                  Display_Message(loop, MSG_CHARGE_STATION);   	                  
						  	                  
			  	  if(Level == LVL_HOUSE_TRAP
			  	  || Level == LVL_HOUSE_TRAP1  
			  	  || Level == LVL_HOUSE_TRAP2) 
  	                  Display_Message(loop, MSG_CHARGE_HOUSE); 	
 
              }  
              
			  if(sprite[loop].sector == UNIT_MONKEY)
			      Display_Message(loop, MSG_CHARGE_MONKEY); 
			      
			  if(sprite[loop].sector == UNIT_DOG)              
			      Display_Message(loop, MSG_CHARGE_DOG); 
			      
		  }  
		  
		  if(sprite[loop].sector == UNIT_GUARD)
		  if(Level == LVL_GASLAB || Level == LVL_GASLAB1)
		      Display_Message(loop, MSG_CHARGE_DUNGEON);
		  else
	  	      Display_Message(loop, MSG_CHARGE_GUARD);
              
          sprite[loop].spotted_timer = (int)TimerGetTime() + 12000;
          
          sprite[loop].spotted = true;    

       }                           
           
       // Alert any enemies within hearing range 
       if(loop != no_test) 
	   if(loop != p1_buddy)
       if(sprite[loop].ai_brain != BRAIN_HEALING)
       if(sprite[loop].bagging == false)
       if(sprite[loop].type == UNT && sprite[loop].turn_off == false)
       if(sprite[loop].score > 0 && loop != ply_id )
       if(sprite[loop].status != STUNNED && sprite[loop].status != FOOT_SHOT)
       if(sprite[loop].status != MERCY && sprite[loop].status != MERCY1 && sprite[loop].status != GROUND_SPAWN)
       if(sprite[loop].status != SALUTE && sprite[loop].emy_shooting == false)
       if(sprite[loop].status != AIMING) 
       if(sprite[loop].status != OPEN_FIRE) 
       if(sprite[loop].status != OPEN_CUT) 
       if(sprite[loop].status != AIM_CROUCH)   
       if(sprite[loop].status != MOVE_OUT)
       if(sprite[loop].status != STAMPING)
       if(Node_Distance1(midX, midY, noise_x, noise_y) <  range)       
       {         
          Find_Path(loop, noise_x, noise_y); 
       } 


	} // loop != -1
       */
}

bool Spawn_A_Guy(int number_of_dudes, int best_point, bool buddy, int trap, int sprite_point, int goto_point)  
{ 
    
    float x1=0.0f;
    float y1=0.0f;
    int row_x[400];
    int row_y[400]; 
    int row_index=0;    
    int place_count=0;
    int temp_row_x=0;
    int temp_row_y=0;
    int testX=0, testY=0;
    int test_row_x=0;
    int test_row_y=0;
    int test_index=0;
    float closest_point=zoom_factor;  
	float DEAD_PNT_X=0.0f, DEAD_PNT_Y=0.0f;
    float mid_x=0.0f, mid_y=0.0f;
    float tarX=0.0f, tarY=0.0f;
    float dis_to_point=0.0f;  
    float temp_distance=0.0f;  
	float y_inc=0.0f;
    int rnd=0;
    int rnd1=0;
    int rnd2=0; 
    bool is_a_room=false;
    int radius=10; 
    bool is_a_general=false; 
    bool always_active = false;
    bool is_in_a_dead_zone=false;
    bool is_in_a_buddy_zone=false;
    bool graveyard=false;
    bool success=false;
    bool spawn_monkeys=false;
    bool is_in_a_special_zone=false;
    bool spawn_buddies = false;
    float spawn_in_range=(float)SPAWN_RANGE;
	bool spawned_chief=false;
    float angle_addition=0.0f;
    float lad_x=0.0f, lad_y=0.0f;
    int lad_index=0;
    bool on_a_ladder=false;
	bool spawn_supers=false;
	bool dont_spawn_specials=false;
	int super_count=4;
	int spawned_sprite=-1;     
	bool is_start_of_game=false;  
	float onscreenX1=0.0f, onscreenY1=0.0f;
	float cx1=0.0f, cx2=0.0f, cy1 =0.0f, cy2=0.0f; 

	cx1 = -camX - (zoom_factor); // Mid-Point X
	cx2 = -camX + (zoom_factor); // Half the width
	cy1 = -camY - ((zoom_factor*sc_ratio)); // Mid-Point Y                         
	cy2 = -camY + ((zoom_factor*sc_ratio)); // Half the height 

	if(main_mission[MISSION_RADIO] == IN_PROGRESS)
		is_start_of_game=true;	 
   
    angle_addition=0.0f;  
 
    spawn_in_range = (float)SPAWN_RANGE;  
     
    if(trap != TRAP_NONE)
        spawn_in_range = (float)TRAP_RANGE; 
    
    if(number_of_dudes == 101)
    {
        is_a_general = true;  
        number_of_dudes = 3;    
    }
     
    if(number_of_dudes == 102)   
    {
        number_of_dudes = rand()%1; 
        always_active = true;  
    }
    
    if(trap == TRAP_NONE)   
    if(number_of_dudes >= 3)
    {   
        if(rand()%2 == 0)    
        {                    
            spawn_monkeys = true;
            if(Level == LVL_SUPPLIES || Level == LVL_BAY || Level == LVL_PLAINS || Level == LVL_FARMS || Level == LVL_TOWN || Level == LVL_HIGHWAY || Level == LVL_VILLAGE)
                number_of_dudes += rand()%4; 
        }
    } 
    
    if(Level == LVL_VILLAGE || Level == LVL_HIGHWAY || Level == LVL_BOATYARD)
        spawn_monkeys = false; 
      
    memset(row_x, -1, sizeof(row_x));  
    memset(row_y, -1, sizeof(row_y));
 
    if(ply_id != -1)
    if(best_point == -1)  
    if(daytime == DAYTIME || daytime == NIGHTTIME || in_dungeon == true || ARCADE)
    { 
        x1 = (-camX) + (cos(sprite[ply_id].angle+angle_addition)*spawn_in_range);    
        y1 = (-camY) + (sin(sprite[ply_id].angle+angle_addition)*spawn_in_range);      
    } 
    
    if(x1 < -map_startX)
        x1 = -map_startX+0.1f;
    if(x1 > map_startX)
        x1 = map_startX-0.1f;
    if(y1 < -map_startY)
        y1 = -map_startY+0.1f; 
    if(y1 > map_startY)
        y1 = map_startY-0.1f;
    
    if(best_point == -1)
    if(in_dungeon != true)  // daytime != NIGHTTIME   
    for(int i=0;i<no_points;i++)
    {
        if(points[i].c1 == DEAD_PNT)   
        { 
                        
            temp_distance = Node_Distance1(x1, y1, points[i].x, points[i].y);
            
            if(temp_distance <= DEAD_SPAWN_RANGE)                         
                is_in_a_dead_zone = true;    
        }   
        if(points[i].c1 == SPECIAL_PNT)
        { 
                        
            temp_distance = Node_Distance1(x1, y1, points[i].x, points[i].y);
            
            if(temp_distance <= 2.0f)                        
                is_in_a_special_zone = true;    
        }        
          
    }    

	super_count = 4;

	if(ARCADE && arcade_kill_count <= 10)
		dont_spawn_specials=true;
	if(ARCADE && arcade_kill_count >= 40)
		 is_in_a_special_zone = true;
	if(ARCADE && arcade_kill_count >= 70)
		spawn_supers=true;
	if(ARCADE && arcade_kill_count >= 20)
		super_count=2;

    if(ply_id != -1)
    {
        mid_x = sprite[ply_id].w + sprite[ply_id].box_width/2;
        mid_y = sprite[ply_id].z + sprite[ply_id].box_height/2; 
    }
        
    if(best_point != -1)
    {    

        if(buddy == true)
            radius = 2;
        else     
            radius = 4;    
            
        closest_point=0.0f;
          
        x1 = points[best_point].x;     
        y1 = points[best_point].y;                
        
    }
	
	DEAD_PNT_X = x1;
	DEAD_PNT_Y = y1;
    
    temp_row_x = (int)((x1 + map_startX)*10);      
    temp_row_y = (int)((y1 + map_startY)*10);  
    
    if(is_in_a_dead_zone == false)           
    for(int testY=-radius;testY<=radius;testY++) 
    for(int testX=-radius;testX<=radius;testX++)
    {      
        
        test_row_x = temp_row_x + testX; 
        test_row_y = temp_row_y + testY;  

        if(test_row_x > 1 && test_row_x < MAP_WIDTH-1)     
        if(test_row_y > 2 && test_row_y < MAP_HEIGHT-1)   
        { 
                              
        if(is_a_room == false)
        {            
            tarX = -map_startX + (( (float)test_row_x * 0.1f) );
            tarY = -map_startY + (( (float)test_row_y * 0.1f) );  
                         
            dis_to_point = Node_Distance(mid_x, mid_y, tarX, tarY);              
        }         
        else 
            dis_to_point = 1.0f;  
                     
        if(!(testX == 0 && testY == 0))    
        if( dis_to_point > closest_point)  
        { 
            test_index = (test_row_y*MAP_HEIGHT)+test_row_x;
            
            if(Level != LVL_CONVOY) 
            {
                if(is_a_room == false && test_index > 0 && test_index < MAP_TILES)                              
                if( (tiles[test_index]>=416 && tiles[test_index]< 432 ) || buddy == true )
                if( (tiles[test_index] != 429 && tiles[test_index] != 430) || Level != LVL_HIGHWAY || buddy == true)
                if( (tiles[test_index] != 425 && tiles[test_index] != 426) || Level != LVL_TOWN || buddy == true)
                if( map_col[test_index] == 0 )    
                { 
                     
                    if(buddy == true) 
                    { 

                        on_a_ladder=false;
                        
                        for(int i=0;i< trigger_counter;i++) 
                        {
                                
                            lad_index = trigger_list[i];  
                                              
                            lad_x = -map_startX + (( (float)test_row_x * 0.1f)+0.05f );
                            lad_y = -map_startY + (( (float)test_row_y * 0.1f)+0.05f );
                                              
							if(lad_index >= 0)           
                            if(( lad_x < sprite[lad_index].w + sprite[lad_index].box_width )
                            &&( lad_x > sprite[lad_index].w)                        
                            &&( lad_y < sprite[lad_index].z + sprite[lad_index].box_height )
                            &&( lad_y > sprite[lad_index].z ))      
                            {
                                on_a_ladder=true;                             
                            }
                        
                        }
                        
                        if(on_a_ladder == false)
						if(row_index >= 0)  
                        {

							onscreenX1 = -map_startX + (( (float)test_row_x * 0.1f) + 0.05f );
							onscreenY1 = -map_startY + (( (float)test_row_y * 0.1f) + 0.05f );  
							
							// Is this point not onscreen...
							if(  !(( onscreenX1 < cx2 )
							&&( onscreenX1 > cx1 )                        
							&&( onscreenY1 < cy2 )
							&&( onscreenY1 > cy1)) )  
							{
								row_x[row_index]=test_row_x;
								row_y[row_index]=test_row_y; 
								if(row_index < 399)                   
									row_index++;                                             
							}

                        }                        
                                 
                    }
                    else
                    {  
						if(row_index >= 0)
						{

							onscreenX1 = -map_startX + (( (float)test_row_x * 0.1f) + 0.05f );
							onscreenY1 = -map_startY + (( (float)test_row_y * 0.1f) + 0.05f );  

							// Is this point not onscreen...
							if(  !(( onscreenX1 < cx2 )
							&&( onscreenX1 > cx1 )                        
							&&( onscreenY1 < cy2 )
							&&( onscreenY1 > cy1)) )
							{
                        		row_x[row_index]=test_row_x;
                        		row_y[row_index]=test_row_y;
                        		if(row_index < 399)                
                            		row_index++;  
							}

						}

                    }
                }    

            }
                                
       }
       
       }
       
       if(row_index >= 399)
           break;
                
    }       
    
    if(is_in_a_dead_zone == false && trap != TRAP_NONE)        
    if(row_index != 0 && number_of_dudes != 0)  
    { 
        for(int i=0;i<number_of_dudes;i++)
        {  
           
          if(row_index > 0)        
              test_index = rand()%row_index;          
                  
          temp_row_x = row_x[test_index];      
          temp_row_y = row_y[test_index];      
                    
          x1 = -map_startX + (( (float)temp_row_x * 0.1f) + 0.05f ); 
          y1 = -map_startY + (( (float)temp_row_y * 0.1f) + 0.05f );     
           
          if( trap == TRAP_GUNNER)
              spawned_sprite=New_Sprite(x1, y1, x1, y1, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_GUNNER, p_client1, 18, -1, -1, SPAWN_HUNT, goto_point);
          if( trap == TRAP_MONKEY)
              spawned_sprite=New_Sprite(x1, y1, x1, y1, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_MONKEY, p_client1, 20, -1, -1, SPAWN_HUNT, goto_point);
          if( trap == TRAP_SHOTGUN)
              spawned_sprite=New_Sprite(x1, y1, x1, y1, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_SHOTGUN, p_client1, 33, -1, -1, SPAWN_HUNT, goto_point);
          if( trap == TRAP_SHIELD)
              spawned_sprite=New_Sprite(x1, y1, x1, y1, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_SHIELD, p_client1, 26, -1, -1, SPAWN_HUNT, goto_point);
          if( trap == TRAP_CHIEF)
              spawned_sprite=New_Sprite(x1, y1, x1, y1, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_CHIEF, p_client1, 20, -1, -1, SPAWN_HUNT, goto_point); 
          if( trap == TRAP_MORTAR)
              spawned_sprite=New_Sprite(x1, y1, x1, y1, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_MORTAR1, p_client1, 28, -1, -1, SPAWN_HUNT, goto_point);
          if( trap == TRAP_MACHINE)
              spawned_sprite=New_Sprite(x1, y1, x1, y1, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_MACHINE, p_client1, 33, -1, -1, SPAWN_HUNT, goto_point);
                          
        }         
                 
    }   

    if(sprite_point != -1)  
    {    
 
 		row_index = 0;
          
        x1 = sprite[sprite_point].w + sprite[sprite_point].box_width/2;     
        y1 = sprite[sprite_point].z + sprite[sprite_point].box_height/2; 
 
    	temp_row_x = (int)((x1 + map_startX)*10);      
    	temp_row_y = (int)((y1 + map_startY)*10);  

		temp_row_y--;

		if(temp_row_y < 0)
			temp_row_y=0;

        row_x[row_index]=temp_row_x;
        row_y[row_index]=temp_row_y;

//		map_col[(temp_row_y*MAP_HEIGHT)+temp_row_x]=0;

		is_in_a_dead_zone = false; 

        row_index++;                
    }
 
    if(is_in_a_dead_zone == false && trap == TRAP_NONE )        
    if(row_index != 0 && number_of_dudes != 0)          
    {    

//		if(!ARCADE) 
        if(buddy == false)  
        if(in_dungeon == false) // daytime != NIGHTTIME 
        {                 
            points[no_points].c1 = DEAD_PNT;          
            points[no_points].x  = DEAD_PNT_X;     
            points[no_points].y  = DEAD_PNT_Y;   

			if(!ARCADE)
				points[no_points].score = (int)TimerGetTime() + 480000; // 8 minutes...
			else
				points[no_points].score = (int)TimerGetTime() + 8000; // 8 minutes...

            no_points++;
        }  
                     
        for(int i=0;i<number_of_dudes;i++)
        {  
           
          if(row_index > 0)        
              test_index = rand()%row_index;          
                 
          temp_row_x = row_x[test_index];     
          temp_row_y = row_y[test_index];      
                    
          x1 = -map_startX + (( (float)temp_row_x * 0.1f) + 0.05f );
          y1 = -map_startY + (( (float)temp_row_y * 0.1f) + 0.05f );


		  if( x1 <= -map_startX)  
		      x1 = -map_startX + 0.1f;

		  if( x1 >= map_startX ) 
  		      x1 = map_startX - 0.1f;

	      if( y1 <= -map_startY)        
		      y1 = -map_startY + 0.1f; 

		  if( y1 > map_startY) 
		      y1 = map_startY - 0.1f;
          
          rnd = rand()%30; 
            
          if(is_a_general == true)
              rnd = 1; 
          
          if( buddy == false)       
          {
                  
               if(daytime == DAYTIME || daytime == NIGHTTIME || in_dungeon == true || ARCADE)
               if( rnd != 1001) // Non-Event..  
               {
                      
                  if(is_a_general == false) 
                  {     
                       
                    if( (i != 2) && rnd != 30)
                    {   

                        {   
                         //   rnd1 = rand()%6;     

                            {  
                                if(in_open_world == false ) 
                                {
                                 
                                }
                                else     
                                {
                                    if(spawn_monkeys == false)   
                                    {       
                                        if(rand()%3 == 0 && (number_of_dudes > 2 || spawn_supers == true) && is_start_of_game == false && dont_spawn_specials == false)    
                                        {  
                                          if(is_in_a_special_zone==false)   
                                          {        
                                              if(rand()%super_count == 0  && !ARCADE && (Level == LVL_BAY || Level == LVL_SUPPLIES || Level == LVL_BOATYARD || Level == LVL_PLAINS || Level == LVL_FARMS || Level == LVL_TOWN || Level == LVL_HIGHWAY || Level == LVL_VILLAGE) )  
											  {	
												  if(Level == LVL_FARMS || Level == LVL_HIGHWAY)
	                                                  spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_MORTAR1, p_client1, 33, -1, -1, -1, -1);
												  if(Level == LVL_TOWN || Level == LVL_VILLAGE)
	                                                  spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_MACHINE, p_client1, 33, -1, -1, -1, -1);
												  if(Level != LVL_FARMS && Level != LVL_TOWN && Level != LVL_HIGHWAY && Level != LVL_VILLAGE)
	                                                  spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_SHOTGUN, p_client1, 33, -1, -1, -1, -1);

											  }
                                              else      
                                              {   
   	                                              spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_GUNNER, p_client1, 18, -1, -1, -1, -1);
                                              }
                                          } 
                                          else // is_in_a_special_zone
										  {
											  if(!ARCADE) 
	                                            spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_SHIELD, p_client1, 26, -1, -1, SPAWN_EXTRA_RANK, -1);
											  else
												spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_SHOTGUN, p_client1, 33, -1, -1, -1, -1);
										  }
                                        } 
                                        else      
                                        {
                                          if(is_in_a_special_zone==false)   
                                          {    
											  if(spawned_chief == false && number_of_dudes > 1)
											  {
												  spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_CHIEF, p_client1, 36, -1, -1, -1, -1); 
												  spawned_chief = true;
											  }	
											  else
											  {
												if(Level == LVL_FARMS || Level == LVL_TOWN || Level == LVL_HIGHWAY || Level == LVL_VILLAGE)	
	                                          	    spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_GUNNER, p_client1, 23, -1, -1, -1, -1);
												else
	                                          	    spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_SAILOR, p_client1, 23, -1, -1, -1, -1);
											  }
                                          }
                                          else
                                              spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_GUNNER, p_client1, 24, -1, -1, SPAWN_EXTRA_RANK, -1);
                                        }                                        
                                    }
                                    else
                                    {  
										if(Level == LVL_FARMS || Level == LVL_TOWN || Level == LVL_HIGHWAY || Level == LVL_VILLAGE)	
	                                        spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_DOG, p_client1, 20, -1, -1, -1, -1);    
										else
	                                        spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_MONKEY, p_client1, 20, -1, -1, -1, -1);    

                                    }                                      
                                 }
   
                              success = true;                                                                        
                            }
                                   
                        }
                            
                    }
                     
                    if(i == 2 && rnd != 30) 
                    { 

                        { 

                        
                              if(in_open_world == false)
                              {
                                
                              }
                              else 
                              {
                              if(spawn_monkeys == false)
                              {     
                                    if(rand()%3 == 0)
                                    {
                                        if(is_in_a_special_zone==false)        
                                            spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_GUNNER, p_client1, 18, -1, -1, -1, -1);
                                        else
										{
											if(!ARCADE)
												spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_SHIELD, p_client1, 26, -1, -1, SPAWN_EXTRA_RANK, -1);
											else
												spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_SHOTGUN, p_client1, 33, -1, -1, -1, -1);
										}
                                    }
                                    else     
                                    {
                                        if(is_in_a_special_zone==false)     
										{ 
											if(Level == LVL_FARMS || Level == LVL_TOWN || Level == LVL_HIGHWAY || Level == LVL_VILLAGE)		 
                                            	spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_GUNNER, p_client1, 23, -1, -1, -1, -1);
											else
                                            	spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_SAILOR, p_client1, 23, -1, -1, -1, -1);

										}
                                        else
										{
											if(Level == LVL_FARMS || Level == LVL_TOWN || Level == LVL_HIGHWAY || Level == LVL_VILLAGE)
	                                            spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_GUNNER , p_client1, 24, -1, -1, SPAWN_EXTRA_RANK, -1);
											else
	                                            spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_SAILOR, p_client1, 24, -1, -1, SPAWN_EXTRA_RANK, -1);

										} 
                                    }                                
                                    } 
                                    else
                                    {
										if(Level == LVL_FARMS || Level == LVL_TOWN || Level == LVL_HIGHWAY || Level == LVL_VILLAGE)
	                                        spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_DOG, p_client1, 20, -1, -1, -1, -1);    
										else
	                                        spawned_sprite=New_Sprite(x1, y1+y_inc, x1, y1+y_inc, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_MONKEY, p_client1, 20, -1, -1, -1, -1);    

                                    }
                              }    
                                                             
                              success = true;

                        }
                    }
                    
                  }
                  
               } 
               
          }          
           
          if( buddy == true) 
          {    
              spawned_sprite=New_Sprite(x1, y1, x1, y1, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, UNT, 1.0f, -1, 0, UNIT_GUNNER, p_server, 19, -1, -1, SPAWN_P1_BUDDY1, -1);
          }    
           
          // Remove test_index from list.
          if(row_index > 1 && test_index < row_index )
          for(int j=test_index;j<(row_index-1);j++)
          {          
              row_x[j] = row_x[j+1];              
              row_y[j] = row_y[j+1];            
          }
                           
          row_index--;        
          
          if(row_index <= 0)
              break;
          
        }
        
    } 
	
	if(sprite_point != -1)
	if(spawned_sprite != -1) 
	{
		Display_Message(spawned_sprite, MSG_SURPRISE);
		sprite[spawned_sprite].emy_shoot = ((int)TimerGetTime() + 1000);
	}

    
    return(success);
     
}
void Refresh_Pnts()
{

               
}

void Create_Defend_List()  
{  

     
}

bool Is_Sprite_Onscreen(int index)
{
     bool success = false;    
     bool keep_in = false;   
     float x1=0.0f, y1=0.0f; 
     float x2=0.0f, y2=0.0f;
     float x3=0.0f, y3=0.0f;  
     float x4=0.0f, y4=0.0f;    
     float cx1=0.0f, cy1=0.0f;        
     float cx2=0.0f, cy2=0.0f;  
     float off_set = 0.25f;  
     float off_set1 = 0.25f;  
     
     cx1 = -camX - (zoom_factor); // Mid-Point X
     cx2 = -camX + (zoom_factor); // Half the width
     cy1 = -camY - ((zoom_factor)*sc_ratio); // Mid-Point Y                         
     cy2 = -camY + ((zoom_factor)*sc_ratio); // Half the height 
     
     if(zoom_factor != 1.0f)
         off_set = 0.35f;
      
     cx1 += off_set; 
     cx2 -= off_set;
     cy1 += off_set1;
     cy2 -= off_set1;
              
     if(index != -1 )
     {
         x1 = (sprite[index].x); 
         x2 = (sprite[index].x + sprite[index].width);
         y1 = (sprite[index].y);
         y2 = (sprite[index].y + sprite[index].height);
         x3 = (sprite[index].x + (sprite[index].width/2));
         y3 = (sprite[index].y + (sprite[index].height/2));
                          
     }  
              
     if(( x1 < cx2 )
     &&( x1 > cx1 )                        
     &&( y2 < cy2 )
     &&( y2 > cy1))
     {
         keep_in = true;
     } 
     
     if(keep_in == false)                               
     if(( x1 < cx2 )
     &&( x1 > cx1 )                        
     &&( y1 < cy2 )
     &&( y1 > cy1))
     {
         keep_in = true;    
     }
     
     if(keep_in == false)                              
     if(( x2 < cx2 )
     &&( x2 > cx1 )                        
     &&( y1 < cy2 )
     &&( y1 > cy1))
     {
         keep_in = true;    
     }                                             

     if(keep_in == false)                              
     if(( x2 < cx2 )
     &&( x2 > cx1 )                        
     &&( y2 < cy2 )
     &&( y2 > cy1))
     {
         keep_in = true;    
     }         

     if(keep_in == false)                              
     if(( x2 < cx2 )
     &&( x2 > cx1 )                        
     &&( y3 < cy2 )
     &&( y3 > cy1))
     {
         keep_in = true;    
     }         

     if(keep_in == false)                              
     if(( x1 < cx2 )
     &&( x1 > cx1 )                        
     &&( y3 < cy2 )
     &&( y3 > cy1))
     {
         keep_in = true;     
     }     

     if(keep_in == false)                           
     if(( x3 < cx2 )
     &&( x3 > cx1 )                        
     &&( y1 < cy2 )
     &&( y1 > cy1))
     {
         keep_in = true;    
     }         

     if(keep_in == false)                              
     if(( x3 < cx2 )
     &&( x3 > cx1 )                        
     &&( y2 < cy2 )
     &&( y2 > cy1))
     { 
         keep_in = true;      
     }           
         
         if(keep_in == true)
             success = true;
                
    return(success);
     
}

bool Get_Free_Point(int loop, int best_point, bool buddy)
{
    float x1=0.0f;
    float y1=0.0f;
    int row_x[400];
    int row_y[400];
    int row_index=0;    
    int place_count=0;
    int temp_row_x=0; 
    int temp_row_y=0;
    int testX=0, testY=0;
    int test_row_x=0;
    int test_row_y=0;
    int test_index=0;
    float closest_point=zoom_factor;  
    float mid_x=0.0f, mid_y=0.0f;
    float tarX=0.0f, tarY=0.0f;
    float dis_to_point=0.0f;  
    float temp_distance=0.0f;  
    int rnd=0;
    int rnd1=0;
    int rnd2=0; 
    bool is_a_room=false;
    int radius=10; 
    bool is_a_general=false; 
    bool always_active = false;
    bool is_in_a_dead_zone=false;
    bool is_in_a_buddy_zone=false;
    bool graveyard=false;
    bool spawn_monkeys=false;
    bool is_in_a_special_zone=false;
    bool spawn_buddies = false;
    float spawn_in_range=(float)SPAWN_RANGE;
	bool spawned_chief=false;
    float angle_addition=0.0f;
    float lad_x=0.0f, lad_y=0.0f;
    int lad_index=0;
    bool on_a_ladder=false;
	int spawned_sprite=-1; 
	bool success=false; 


	radius = 2;

    if(loop >= 0) 
    {
        mid_x = sprite[loop].w + sprite[loop].box_width/2;
        mid_y = sprite[loop].z + sprite[loop].box_height/2; 
    }
            
	if(best_point >= 0)
	{
	    x1 = points[best_point].x;     
	    y1 = points[best_point].y;  
	}
    
    temp_row_x = (int)((x1 + map_startX)*10);      
    temp_row_y = (int)((y1 + map_startY)*10);  
         
    for(int testY=-radius;testY<=radius;testY++) 
    for(int testX=-radius;testX<=radius;testX++)
    {      
        
        test_row_x = temp_row_x + testX; 
        test_row_y = temp_row_y + testY;  

        if(test_row_x > 1 && test_row_x < MAP_WIDTH-1 )    
        if(test_row_y > 2 && test_row_y < MAP_HEIGHT-1 )  
        { 
                     
        if(!(testX == 0 && testY == 0))    
        { 
            test_index = (test_row_y*MAP_HEIGHT)+test_row_x;
            
			if(test_index != best_point)
            {
                if( test_index > 0 && test_index < MAP_TILES)                              
                if( map_col[test_index] == 0 )    
                { 
                     
                    if(buddy == true)
                    { 

                        on_a_ladder=false;
                        
                        for(int i=0;i< trigger_counter;i++)
                        {
                                
                            lad_index = trigger_list[i];  
                                              
                            lad_x = -map_startX + (( (float)test_row_x * 0.1f)+0.05f );
                            lad_y = -map_startY + (( (float)test_row_y * 0.1f)+0.05f );

                            if(lad_index >= 0)                             
                            if(( lad_x < sprite[lad_index].w + sprite[lad_index].box_width )
                            &&( lad_x > sprite[lad_index].w)                        
                            &&( lad_y < sprite[lad_index].z + sprite[lad_index].box_height )
                            &&( lad_y > sprite[lad_index].z ))      
                            {
                                on_a_ladder=true;                             
                            }
                        
                        }
                        
                        if(on_a_ladder == false)
						if(row_index >= 0)
                        {
                            row_x[row_index]=test_row_x;
                            row_y[row_index]=test_row_y;
                            if(row_index < 399)                
                                row_index++;                                             
                        }                        
                                 
                    }
                    else
                    {
						if(row_index >= 0)
						{
	                        row_x[row_index]=test_row_x;
	                        row_y[row_index]=test_row_y;
	                        if(row_index < 399)                
	                            row_index++;    
						}
                    }
                }    

            }
                                
       }
        
       }
       
       if(row_index >= 399)
           break;
                
    }        
     
    if(row_index != 0)     
	{
    	if(row_index > 0)        
        	test_index = rand()%row_index;          
                 
        temp_row_x = row_x[test_index];       
        temp_row_y = row_y[test_index];        
                    
        buddy_startX = -map_startX + (( (float)temp_row_x * 0.1f) + 0.05f );
        buddy_startY = -map_startY + (( (float)temp_row_y * 0.1f) + 0.05f ); 

		success = true;
	}

	return(success);

}


