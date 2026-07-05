
#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>
#include <math.h>
#include "globals.h"        

extern void Set_Heading(int loop, float x1, float y1, bool hulk_ladder);
extern int New_Sprite(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int sideways, int upways, int state, int linked_sprite, int tex_id, int a_global, float angle, int p_type, int goto_point );
extern bool Build_Man_Check(int loop, int x, int y, int build_type, bool row_check);
extern bool Man_Shot(int guy_status, int guy_shot, int guy_shooting, int bullet_type, int f_rate);
extern bool Shoot_Ray(int loop, float x1, float y1, float x2, float y2, bool grey_test, bool shooting, float precision);
extern float TimerGetTime(); 

int Test_Collision(object collision, float x_inc, float y_inc, bool bullet, int no_test, bool quick_test); // SC - TC
void Generate_Object_Collision(int loop, bool col_test);
int Find_Path(int loop, float destX, float destY);  
int Path_finder(int loop, int last_node, int goal_node); 
void Reposition_Unit(int loop); 
int Get_Nearest_Depot(int loop, bool check);  
bool Build_Something(int loop);
int Get_Space(float x1, float y1, float x2, float y2);
void Squash_Test(int loop);
void Move_Vehicle(int loop, float x_pos, float y_pos, int f_rate);
void Vehicle_Anims(int loop);
int Test_Collision_Vehicle(int loop, float deltax, float deltay);


bool Build_Something(int loop)  
{ 
	return 0;
}
    
// SCC COL
int Test_Collision(object collision, float x_inc, float y_inc, bool bullet, int no_test, bool quick_test) // SC - TC
{        
     
        int test_success = ROUTE_GO;  
        float x1=0.0, y1=0.0;
        float x2=0.0, y2=0.0;
        float x3=0.0, y3=0.0; 
        int temp_row_x=0, temp_row_y=0;
        int edge_row_x=0, edge_row_y=0;
        int guys_row=0;  
        int on_row=0;
        int reduced_time=0;  
		float mid_x=0.0f, mid_y=0.0f;
		float tiles_center=0.0f;
		float distance=0.0f;
		float this_tilesX=0.0f, this_tilesY=0.0f;

		if(no_test != -1)   
		{
			mid_x = sprite[no_test].w + sprite[no_test].box_width/2;
			mid_y = sprite[no_test].z + sprite[no_test].box_height/2; 
		}  
          
        // Walk mode collision detection
        if(!mode && ( game_mode == WALK || game_mode == WORLD))
        {     
            x1 = collision.w + x_inc;                 
            y1 = collision.z + y_inc;      
                     
            x2 = x1 + (collision.box_width/2);  // Mid point...
            y2 = y1 + (collision.box_height/2); // Mid point...
                
            x3 = collision.w + (collision.box_width/2);  
            y3 = collision.z + (collision.box_height/2);
                 
            temp_row_x = (int)((x2 + map_startX)*10);              
            temp_row_y = (int)((y2 + map_startY)*10);       
      
            if(temp_row_x < 0 || temp_row_x >= MAP_WIDTH || temp_row_y < 0 || temp_row_y >= MAP_HEIGHT)  
                test_success = ROUTE_BLOCKED_EDGE; 
			
			if( x2 <= -map_startX) 
				test_success = ROUTE_BLOCKED_EDGE; 

			if( x2 >= (-map_startX + (MAP_WIDTH*TileSize) ) ) 
				test_success = ROUTE_BLOCKED_EDGE;           
			
			if( y2 <= -map_startY) 
				test_success = ROUTE_BLOCKED_EDGE; 

			if( y2 >= (-map_startY + (MAP_HEIGHT*TileSize) ) ) 
				test_success = ROUTE_BLOCKED_EDGE;  
             
            if(test_success != ROUTE_BLOCKED_EDGE)      
            { 
                            
              guys_row = (temp_row_y*MAP_HEIGHT)+temp_row_x;   

			  if(guys_row < 0)
				guys_row = 0;              

              // Crushable Tiles..
          /*    if(tiles[guys_row] == 502 
              || tiles[guys_row] == 504 
              || tiles[guys_row] == 506
              || tiles[guys_row] == 508  
              )
              {   
                   
                  if(dm_game != DM_NONE && ping_tile_count >= 0) 
                  {
                      ping_tile_changeX[ping_tile_count]=temp_row_x; 
                      ping_tile_changeY[ping_tile_count]=temp_row_y; 
                             
                      ping_tile_count++;  
                         
                      if(ping_tile_count >= 100)   
                          ping_tile_count=0;    
                  }      
          
                  if(tiles[guys_row] == 502 || tiles[guys_row] == 504)
                  {
                      glass_sfx = true;   

                      
                      if(Level == LVL_SUPPLIES)
                      if(tiles[guys_row] == 502 && map_set[guys_row] == 1)
                      if(temp_global_objects[19] == GLOBAL_UNBEATEN) // tent_objects[4] == TENT_NONE &&
                      {   
                                              
                         temp_global_objects[19] = GLOBAL_BEATEN;
                    
                         New_FX(mid_x, mid_y, mid_x, mid_y, 13, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 3, PKU, 1.0f, 4, INV_LETTERS, FX_STATIC, -1, 2, 0, 0, -1);
                     
                      } 
                          
                      if(Level == LVL_SUPPLIES)   
                          bottle_count++;
                       
                  }
                                                       
                  tiles[guys_row]++;    
                         
              }     */
                
              this_tilesX = -map_startX + (( (float)temp_row_x * TileSize )+TileSize/2);      
              this_tilesY = -map_startY + (( (float)temp_row_y * TileSize )+TileSize/2);
			  
			  distance = Node_Distance1(mid_x, mid_y, this_tilesX, this_tilesY);
			    
			//  if( distance <= (0.05 + collision.box_width/2) ) 	                
              if(map_col[guys_row]==1 || map_col[guys_row]==6 || map_col[guys_row]==7 || map_col[guys_row]==10) 
                  test_success = ROUTE_BLOCKED;  
			     
           /*   if(no_test != -1)       
              if( map_col[guys_row]==9
              && !(no_test == ply_id && has_water == true && has_crate_equipped == false)
              && !(no_test == p1_buddy && has_water == true)
              && sprite[no_test].sector != UNIT_SHARK
              ) 
                  test_success = ROUTE_BLOCKED;*/
                                                          
            } // if(test_success != ROUTE_BLOCKED_EDGE) 
    
    }  // Is game_mode WALK  

    return(test_success);            
    
}     
  
void Generate_Object_Collision(int loop, bool col_test)
{
     
    float mid_x=0.0f, mid_y=0.0f;
    float mid_x1=0.0f, mid_y1=0.0f;
    int index=0;
    int temp_row_x=0, temp_row_y=0;
    int temp_row_x1=0, temp_row_y1=0;
    int corner1=0, corner2=0, corner3=0, corner4=0;
    int col_type = 6;
    
	if(loop >= 0)
	{

    if(sprite[loop].type == OBJ 
    && sprite[loop].sector_action == OBJ_NONE 
    || sprite[loop].sector_action == -1)
        col_type = 1;
               
    mid_x  = sprite[loop].w;   
    mid_y  = sprite[loop].z;   
    mid_x1 = sprite[loop].w+sprite[loop].box_width; 
    mid_y1 = sprite[loop].z+sprite[loop].box_height; 
                            
    temp_row_x = (int)((mid_x + map_startX)*10);        
    temp_row_y = (int)((mid_y + map_startY)*10); 
    
    temp_row_x1 = (int)((mid_x1 + map_startX)*10);        
    temp_row_y1 = (int)((mid_y1 + map_startY)*10); 
    
    for(int j=temp_row_y;j<=temp_row_y1;j++)
    for(int i=temp_row_x;i<=temp_row_x1;i++)
    {
        index = (j*MAP_HEIGHT)+i;    
         
        if(index >= 0 && index < MAP_TILES) 
        {       
               
            if(col_test == CREATE_COL)  
            {  
                if(sprite[loop].type == OBJ)
                {        
                  if(sprite[loop].onCreate == DUCKABLE)
                    map_col[index]=1;   
                  else        
                    map_col[index]=col_type;  
                    
                  if(sprite[loop].onCreate == SHOOTTHRU)    
                    map_col[index]=7;   
                }
                else 
                {            
 
				  map_col[index]=10;    

             //     if(sprite[loop].type == BAG && sprite[loop].sector == UNIT_COW)
             //       map_col[index]=10;  
                  if(sprite[loop].type == BAG && sprite[loop].sector == UNIT_ARMOUR_TANK) 
                    map_col[index]=6;  
                  if(sprite[loop].type == BAG && sprite[loop].sector == UNIT_SEAGULL)
                    map_col[index]=6;  
                  if(sprite[loop].type == BAG && sprite[loop].sector == UNIT_SEAGULL2)
                    map_col[index]=6; 
                  if(sprite[loop].type == BAG && sprite[loop].sector == UNIT_ARMOUR_TURRET && sprite[loop].rank != 0) // Mauser's small tanks
                    map_col[index]=1;   
            //      if(sprite[loop].type == BAG && sprite[loop].sector == UNIT_ARMOUR_TURRET)
             //       map_col[index]=10;    
 
                }
                     
                      
            } 
            
            if(col_test == REMOVE_COL)  
                map_col[index]=0;   
        }
    }

	} // loop >= 0

} 

int Find_Path(int loop, float destX, float destY)
{
     
    bool test_water=false; 
    bool test_success=false; 
    int success=0;

    float x1=0.0f, y1=0.0f; 
    float x2=0.0f, y2=0.0f;
    float angle=0.0f, deltax=0.0f, deltay=0.0f;
    float step=0, distance=0.0f;
    int iterations=0;
    int temp_row=0;
    int go_to_row=0;  
    int temp_r_x=0;  
    int temp_r_y=0;
    float closest_point = 10000.0f;
    float dis_to_point=0.0f;
    int best_row_x=0;  
    int best_row_y=0;
    int last_node=0;  
    int goal_node=0;  
    int stored_col=0;   
	int player_stored_col=0;    
    int index=0;   
    int row_x=0;    
    int row_y=0;    
    bool run_new_code = false; 

    if(destX != -1 && destY != -1) 
    {
		run_new_code = true;  
  
		// Convert destination to tile co-ordinates... // New change
		row_x = (int)((destX + map_startX)*10);      
		row_y = (int)((destY + map_startY)*10);
	              
	    destX = -map_startX + (( (float)row_x * 0.1f )+0.05f); // -5.0f, 0.1f
	    destY = -map_startY + (( (float)row_y * 0.1f )+0.05f); // -5.0f, 0.1f  	
			
    }
    else
    {
		if(loop >= 0) 
		{
	        destX = sprite[loop].end_x;     
	        destY = sprite[loop].end_y;	  
		}
    } 

	// Check co-ords are on the map...
	if( destX < -map_startX || destX >  map_startX  ) 
	{
		if(loop >= 0)	
	    if(ply_id != -1)  
	    if(loop != ply_id)                            
		{
	        sprite[loop].col_timer = (int)TimerGetTime() + 100 + rand()%50; 
			ShotIdle(loop);
		}
		return(false); 
	}
	if( destY < -map_startY || destY > map_startY )
	{
		if(loop >= 0)	
	    if(ply_id != -1)  
	    if(loop != ply_id)                            
		{
	        sprite[loop].col_timer = (int)TimerGetTime() + 100 + rand()%50; 
			ShotIdle(loop);
		}
		return(false); 
	}
	  
	if(loop >= 0)
//	if(sprite[loop].ai_brain != BRAIN_HEALING )    
//	if(sprite[loop].bagging == false)
//	if((int)TimerGetTime() > sprite[loop].col_timer || loop == ply_id) 
	{ 
	    
	    if(ply_id != -1)  
	    if(loop != ply_id)                            
	        sprite[loop].col_timer = (int)TimerGetTime() + 100;  
	
	    x2 = destX;      
	    y2 = destY;
	
	    temp_r_x = (int)((x2 + map_startX)*10);               
	    temp_r_y = (int)((y2 + map_startY)*10);  
	
	    goal_node = (temp_r_y*MAP_HEIGHT)+temp_r_x; 

		if(	goal_node < 0)
			goal_node = 0;	

	    stored_col = map_col[goal_node];    
	    map_col[goal_node]=0;
	    
	    // Reset the Node_List
	    for(int i=0;i<NODE_LIMIT;i++) 
	    {
	        sprite[loop].node_list[i] = -1;    
	        sprite[loop].node_counter = 0;
	        sprite[loop].node_count   = -1;
	    } 
	 
	                  
	    x1 = sprite[loop].w+sprite[loop].box_width/2;
	    y1 = sprite[loop].z+sprite[loop].box_height/2;
	
	    temp_r_x = (int)((x1 + map_startX)*10);              
	    temp_r_y = (int)((y1 + map_startY)*10);  
	    
	    index = (temp_r_y*MAP_HEIGHT)+temp_r_x; 

		if(	index < 0) 
			index = 0;	
	         
		player_stored_col = map_col[index];   
    
	    map_col[index] = 0;    
	    
	    test_success = Shoot_Ray(loop, x1, y1, x2, y2, true, false, 0.02f);
	            
	    map_col[index]=player_stored_col; 
	             
	    if(test_success == false)  
	    {
			if(destX != -1 && destY != -1)  
			{
		        sprite[loop].mov_x = destX; 
		        sprite[loop].mov_y = destY; 
   	
				if( sprite[loop].mov_x  < -map_startX || sprite[loop].mov_x  >  map_startX  || sprite[loop].mov_y < -map_startY || sprite[loop].mov_y >  map_startY  )
				{
					sprite[loop].mov_x = (sprite[loop].w + sprite[loop].box_width/2);
					sprite[loop].mov_y = (sprite[loop].z + sprite[loop].box_height/2); 
				}

				sprite[loop].end_x = destX; 
		        sprite[loop].end_y = destY;

			}
	        
	        if(ply_id != -1)
	        if(loop == ply_id)
	            sprite[loop].col_timer = 0;
	        
	        success=1; 
	                        
	    }   
    
	    // Need to find a path etc 
	    if(test_success == true ) 
	    { 
	                            
	       x1 = sprite[loop].w+sprite[loop].box_width/2;
	       y1 = sprite[loop].z+sprite[loop].box_height/2;
	     
	       x2 = destX;      
	       y2 = destY;        
	            
	       temp_r_x = (int)((x1 + map_startX)*10);           
	       temp_r_y = (int)((y1 + map_startY)*10);    
	    
	       last_node = (temp_r_y*MAP_HEIGHT)+temp_r_x; 
	         
	       temp_r_x = (int)((x2 + map_startX)*10);         
	       temp_r_y = (int)((y2 + map_startY)*10);   
	    
	       goal_node = (temp_r_y*MAP_HEIGHT)+temp_r_x;  

		   if( goal_node < 0) 
		       goal_node = 0;
	        
	       if(map_col[goal_node] == 1 || map_col[goal_node] == 6 || map_col[goal_node] == 7) 
	           goal_node = Get_Space(x2, y2, x1, y1);   
	       
	       gobal_goal_node = goal_node;
	        
	       if(goal_node != -1)  
	           success = Path_finder(loop, last_node, goal_node);  // Sets up mov_x & mov_y automatically...  

	       sprite[loop].col_timer = (int)TimerGetTime() + 800;  // Don't process them all on the same frame...
	 
	   }   
       
       map_col[goal_node]= stored_col;  
    
	   if(run_new_code == true) 
	   { 
		   if(success == 1)  
		   { 
			   if(destX != -1 && destY != -1)
			   {		
			       sprite[loop].end_x = destX;     
			       sprite[loop].end_y = destY;	  
			   }

		       sprite[loop].anim_state = WAIT;   
		           
		       sprite[loop].special = 0;  
			        
		       sprite[loop].update = true;  
		                         
		       sprite[loop].moving = true;
		            
		       sprite[loop].turning = false; 
		          
		       sprite[loop].all_timer = (int)TimerGetTime() + 250;				   
		               
		       sprite[loop].status = MOVE_OUT; 
		       
		  //     sprite[loop].idle_type = IDLE_NONE;
			     
		  }
		  else  
		  {
			if(loop != ply_id)
		      ShotIdle(loop);
		  }
				              
        } 

    
    } // col_timer && loop >= 0
    
    return(success); 
    
}

void Reposition_Unit(int loop)
{ 
     
   int temp_row_x=0;  
   int temp_row_y=0;  
   int temp_row=0; 
   int index=0;  
   float mid_x=0.0f, mid_y=0.0f;
   float center_x=0.0f, center_y=0.0f; 
   float off_x=0.0f, off_y=0.0f;  
    
   
   if(loop >= 0)
   {

   if(sprite[loop].onDeath_action != TANK_TOP)	 
   { 
	                              
	   sprite[loop].width  = 0.2f; // 2.3f  
	   sprite[loop].height = 0.2f; // 2.6f  
	    
	   sprite[loop].box_width  = 0.03f;   
	   sprite[loop].box_height = 0.03f; 
	        
	   sprite[loop].w = sprite[loop].x+(sprite[loop].width/2-0.015f);
	   sprite[loop].z = sprite[loop].y+(sprite[loop].height/7);
	            
	   center_x = sprite[loop].w+sprite[loop].box_width/2; 
	   center_y = sprite[loop].z+sprite[loop].box_height/2; 
         
   }


   if(sprite[loop].sector != UNIT_DECOY)
   if(sprite[loop].onDeath_action != TANK_TOP)
   if(sprite[loop].file_full == false)
   {
       off_x = center_x - sprite[loop].x;
       off_y = center_y - sprite[loop].y;
       
       sprite[loop].x -= off_x;
       sprite[loop].y -= off_y;
       sprite[loop].w -= off_x;
       sprite[loop].z -= off_y;
   }
   
   // Set tile collision on...
    
   mid_x = sprite[loop].w+sprite[loop].box_width/2;  
   mid_y = sprite[loop].z+sprite[loop].box_height/2;     
               
   temp_row_x = (int)((mid_x + map_startX)*10);        
   temp_row_y = (int)((mid_y + map_startY)*10);  
     
   index = (temp_row_y*MAP_HEIGHT)+temp_row_x;    

   if(index < 0)
	  index = 0;   
  
   if(sprite[loop].onDeath_action != TANK_TOP)
   if(loop != p1_id && loop != p2_id && loop != p3_id && loop != p4_id && loop != p1_buddy)  
   if(map_col[index] == 0)
       map_col[index] = 6;  


	} // loop >= 0
        
}

int Get_Nearest_Depot(int loop, bool check) 
{

	return 0;    
}

int Get_Space(float x1, float y1, float x2, float y2)
{      
    int test_success=-1;  
    
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
      
    for (int i = 0; i < iterations; i++)
    {    
         
        x += deltax; // Which is the mid_x 
        y += deltay; // Which is the mid_y
        
        temp_r_x = (int)((x + map_startX)*10);   
        temp_r_y = (int)((y + map_startY)*10); 
         
        temp_row = (temp_r_y*MAP_HEIGHT)+temp_r_x;   

        if(temp_row < 0)
			temp_row = 0;
          
        if( temp_row >= 0 && temp_row < MAP_TILES)
        if(map_col[temp_row]==0) 
        {
            test_success = temp_row; 
            break;
        }
    
    }            
    
    return(test_success);       
     
} 

void Squash_Test(int loop)
{
    float dis_to_point=0.0f;
    float midX =0.0f, midY =0.0f;
    float tarX =0.0f, tarY =0.0f;
    int best_point = -1;
    int index=0;    
	float distance = 0.0f;   
          
	if(loop >= 0)
	{ 
	    midX = sprite[loop].w+sprite[loop].box_width/2;
	    midY = sprite[loop].z+sprite[loop].box_height/2;
	}
                    
    for(int tx=0;tx<player_counter;tx++)             
    {  
                 
      index = player_list[tx];     
      
	  if(index >= 0 && loop >= 0)   
      if(sprite[index].linked_sprite != sprite[loop].linked_sprite)
      if(sprite[index].building == false && sprite[index].sector != UNIT_TANK)        
      if(sprite[index].score > 0 && sprite[index].turn_off == false)
      {                
  
            tarX = sprite[index].w + sprite[index].box_width/2;
            tarY = sprite[index].z + sprite[index].box_height/2; 
                                     
            dis_to_point = Node_Distance(midX, midY, tarX, tarY);  

            if( dis_to_point < squash_rng)                
            {         
                                        
               if(lan_game == true && ping_squash_count >= 0)         
               {
                   ping_squasher[ping_squash_count]=loop;
                   ping_squashed[ping_squash_count]=index; 
                     
                   ping_squash_count++;              
               
                   if(ping_squash_count >= 40) 
                       ping_squash_count=0;                  
                }      
                
                if(lan_game == false)               
                    Man_Shot(UNIT_SQUASHED, index, loop, BULLET_NONE, 1);                   
  
            }
             
     }

     }
     
}

void Move_Vehicle(int loop, float x_pos, float y_pos, int f_rate)
{
    float deltax=0.0f, deltay=0.0f;
    float angle=0.0f; 
    float mid_x=0.0f;    
    float mid_y=0.0f;
    float ratio=0.0f;
    float distance_from_target=0.20f;
    int temp_row_x=0; 
    int temp_row_y=0;   
    int index=0; 
    int temp_row_x1=0; 
    int temp_row_y1=0;    
    int index1=0;     
    float temp_speed = (float)vehicle_spd;
    int collision_returned=ROUTE_GO;   
    int collision_returned1=ROUTE_GO;       
    int test_wood=0, test_food=0;
    int old_index=0;  
   
	if(f_rate <= 0)
	    f_rate = 1; 
 
	if(loop >= 0)
	{
 
	if(sprite[loop].score == 1)
	    temp_speed = (float)vehicle_spd*3.0f;	

    angle = atan2(y_pos - (sprite[loop].z+sprite[loop].box_height/2),x_pos - (sprite[loop].w+sprite[loop].box_width/2));
     
    deltax = cos(angle); // Was 1.2f    
    deltay = sin(angle); // Was 1.2f
       
    deltax *= temp_speed;             
    deltay *= temp_speed; // *sc_ratio
    
    deltax *= (float)f_rate;  
    deltay *= (float)f_rate;   

    if(sprite[loop].grab_switch == true) 
        Generate_Object_Collision(loop, REMOVE_COL); 
       
    if(collision_returned == ROUTE_GO && collision_returned1 == ROUTE_GO)   
    {
                          
        sprite[loop].y += deltay; 
        sprite[loop].z += deltay; 
        sprite[loop].x += deltax;           
        sprite[loop].w += deltax; 
        
        sprite[loop].moving = true;
         
    }  
    else 
    {
        sprite[loop].moving = false;
    } 
    
    if(sprite[loop].grab_switch == true)     
        Generate_Object_Collision(loop, CREATE_COL);      
    
	} // loop > = 0
     
}   

void Vehicle_Anims(int loop)
{
    
	if(loop >= 0)
	{
    if(sprite[loop].score > 0)
    {
      if( sprite[loop].moving == true)
        Set_Sprite(loop, 0, LOOP, ANIM_SPRITE, ANIM_WALKING); 
        
      if( sprite[loop].moving == false)
        Set_Sprite(loop, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
    }
    else
    {
        Set_Sprite(loop, 3, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); 
    }
	}
    
         
}

// SCC COL
int Test_Collision_Vehicle(int loop, float deltax, float deltay)
{        
      
    float mid_x=0.0f, mid_y=0.0f;
    float mid_x1=0.0f, mid_y1=0.0f;
    int index=0; 
    int temp_row_x=0, temp_row_y=0;
    int temp_row_x1=0, temp_row_y1=0;
    int corner1=0, corner2=0, corner3=0, corner4=0;
    int test_success=ROUTE_GO;
    float inc_buffer = 0.01f;
    

	if(loop >= 0)
	{
           
    mid_x  = sprite[loop].w + deltax;  
    mid_y  = sprite[loop].z + deltay;   
    mid_x1 = mid_x + sprite[loop].box_width; 
    mid_y1 = mid_y + sprite[loop].box_height; 
    
    
    mid_x -= inc_buffer;
    mid_y -= inc_buffer;
    mid_x1 += inc_buffer;
    mid_y1 += inc_buffer; 
                            
    temp_row_x = (int)((mid_x + map_startX)*10);        
    temp_row_y = (int)((mid_y + map_startY)*10); 
    
    temp_row_x1 = (int)((mid_x1 + map_startX)*10);        
    temp_row_y1 = (int)((mid_y1 + map_startY)*10); 
    
    for(int j=temp_row_y;j<=temp_row_y1;j++)
    for(int i=temp_row_x;i<=temp_row_x1;i++)
    {
            
        index = (j*MAP_HEIGHT)+i;     

        if(temp_row_x < 0 || temp_row_x >= MAP_WIDTH || temp_row_y < 0 || temp_row_y >= MAP_HEIGHT)  
            test_success = ROUTE_BLOCKED_EDGE; 
                         
        if(index >= 0 && index < MAP_TILES) 
        if(test_success != ROUTE_BLOCKED_EDGE)    
        {  

              if(map_col[index]==1 || map_col[index]==6 || map_col[index]==7) 
                  test_success = ROUTE_BLOCKED;   
 
        }
    }

	} // loop >= 0

    return(test_success);            
    
}   
