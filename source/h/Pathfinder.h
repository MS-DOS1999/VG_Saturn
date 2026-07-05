#include <windows.h>
#include <math.h>
#include <stdio.h>    
#include "globals.h" 

#define MAX_PATHS 1500
#define ARRAY_LIMIT 1500

#define COL_LIMIT 500 
#define PLY_COL_LIMIT 10
 
 
//bool step=false;    
//bool step2=false;  
int limit_value = COL_LIMIT;  

bool Path_Found=false; // For FindPath
int best_list[1500]; 

struct sPath
{  
    int cost;  
    int start;
    int end;
    int index;
    bool backwards;
};

sPath path[MAX_PATHS];

extern void ShotIdle(int loop);
extern int Test_Collision_Vehicle(int loop, float deltax, float deltay);

int Path_finder(int loop, int last_node, int goal_node);
int Clean_Pathway(int count, int start_point, int loop);
int Sta2_Clean_Pathway(int count, int start_point, int loop);
void Next_node(int loop, bool increase_counter);
bool Shoot_Ray(int loop, float x1, float y1, float x2, float y2, bool grey_test, bool shooting, float precision); 
void Wall_Offset(int loop, int row_x, int row_y, int index, bool is_tank);

int Record_Pathway(bool direction, int last_node, int goal_node, bool is_player);
int Reorder_Pathway(int count, int last_node, int goal_node, bool testing);
bool Diagonal_Check(int on_node, int y, int x);
bool Stuck_Check(int on_node, int y, int x);
bool Stuck_To_Wall(int on_node, int y, int x);
void Calculate_Path(int path_id, int last_node, int goal_node);
int Get_Tile_Index(float x, float y);
bool Check_Col_Types(int temp_row, bool grey_test, bool shooting, bool test_water);



int Path_finder(int loop, int last_node, int goal_node)
{
 
  int count=0;
  int count1=0;
  int count2=0;
  int index=0;
  int old_last_node=0; 
  int old_goal_node=0; 
  int temp_row=0; 
  int row_x=0;
  int row_y=0;
  bool is_worker=false;  

  if(loop < 0 || last_node < 0 || goal_node < 0) 
  {
	return(0);
  }
   
  col_type = 0; // For water stuff
           
  // Switched last_node with goal_node
   
  //if(ARCADE)  
//	limit_value = 96;   
//  else 
	limit_value = COL_LIMIT; 
  
  if(ply_id != -1)
  if(loop == ply_id)   
      limit_value = PLY_COL_LIMIT;
   
  Path_Found = false; 
    
  debug_path_count = 0; 

  old_last_node = map_col[last_node];
  old_goal_node = map_col[goal_node]; 
    
  map_col[last_node] = 2;                         
  map_col[goal_node] = 3;        

	if( loop == ply_id) 
		count = Record_Pathway(false, last_node, goal_node, true);
	else                
		count = Record_Pathway(false, last_node, goal_node, false);
      
  count = Reorder_Pathway(count, last_node, goal_node, false);    
   
//  count = Clean_Pathway(count, last_node, loop);  

  count = Sta2_Clean_Pathway(count, last_node, loop); 

  map_col[last_node] = old_last_node;                           
  map_col[goal_node] = old_goal_node; 

  index = 0;  
    
  if(Path_Found == true)  
  for(int i=0;i<count;i++)     
  {     

      if(i<NODE_LIMIT)
      {
         sprite[loop].node_list[i] = recorded[i]; 
         index++; 
      }    
      
      if(debug_path_count >= 0 && debug_path_count < NODE_LIMIT)
      {       
                          
         temp_row = recorded[i];        

         if(MAP_HEIGHT != 0)
             row_y = temp_row/MAP_HEIGHT;                          

         row_x = temp_row-(row_y*MAP_HEIGHT);   
              
         debug_pathX[debug_path_count]= -map_startX + (( (float)row_x * 0.1f )+0.05f); // -5.0f, 0.1f
         debug_pathY[debug_path_count]= -map_startY + (( (float)row_y * 0.1f )+0.05f); // -5.0f, 0.1f        
         debug_path_count++;           

                 
      }   
      
  }     
     
  sprite[loop].node_count = index;  // last_node 6327
  sprite[loop].node_counter = 0;  
  
  if(Path_Found == false || sprite[loop].node_list[0] == -1)
  { 
      sprite[loop].node_list[0] = 0;
      sprite[loop].node_count = -1; 
  }  
  
  Next_node(loop, false);        

  return(Path_Found);
  
}

int Record_Pathway(bool direction, int last_node, int goal_node, bool is_player)
{
     
  int temp_node=0;
  float closest=100000.0f;
  float distance=0; 
  float distance1=0; 
  int row_x=0,row_y=0;    
  float g_x=0,g_y=0;
  float x1=0.0,y1=0.0;
  int best=0;
  int count=0; 
  bool swi_goal=true; 
  int last_best;
  int goal_best;
  int highest=-1;    
  bool is_diagonal=false;    
  float midX=0.0;
  float midY=0.0;
  float tarX=0.0;
  float tarY=0.0;
  bool stuck_to_wall_on=false;      
  int entry_point[MAX_PATHS];
  int ep_id=0;
  bool first_stuck=false;
  bool finished=false;
  int viewX_Limit=0;  
  int viewX1_Limit=0;
  int viewY_Limit=0;
  int viewY1_Limit=0; 
  int number_of_points_found=0;
  int best_count=0; 
  int no_path_found=0;
  int on_node=0; 
   
  row_y = last_node / MAP_HEIGHT;       
  row_x = last_node - (row_y*MAP_HEIGHT); 
          
  viewX_Limit  = row_x - limit_value;  
  viewX1_Limit = row_x + limit_value; 
  viewY_Limit  = row_y - limit_value;
  viewY1_Limit = row_y + limit_value;
  
  if(viewX_Limit < 0)
      viewX_Limit = 0;
  if(viewX1_Limit >= MAP_WIDTH)
      viewX1_Limit = MAP_WIDTH-1;
  if(viewY_Limit < 0) 
      viewY_Limit = 0;
  if(viewY1_Limit >= MAP_HEIGHT)
      viewY1_Limit = MAP_HEIGHT-1;
          
  temp_node = last_node;       
  goal_best = goal_node;    
  last_best = last_node;
                      
  for(int back=0;back<limit_value*limit_value;back++)  
  {  
      
    for(int i=-1;i<=1;i++)  // Y        
    for(int j=-1;j<=1;j++)  // X        
    { 
  
      on_node = last_best;               
      
      // Stick him to the wall if node I'm on is near a wall.. 
      if(first_stuck == false && ep_id >= 0)
      if(stuck_to_wall_on == false)       
      if(Stuck_To_Wall(on_node, i, j)==true)
      {
          stuck_to_wall_on = true; 
          entry_point[ep_id] = last_best;    
      } 
      
      row_y = on_node/MAP_WIDTH;
      row_x = on_node - (row_y*MAP_WIDTH);
      
      row_y += i; 
      row_x += j; 
         
      on_node = (row_y*MAP_WIDTH) + row_x;  
		       
      if(row_x >= viewX_Limit && row_x <= viewX1_Limit)             
      if(row_y >= viewY_Limit && row_y <= viewY1_Limit)                    
      if(i == 0 || j == 0)         // No Diagonals
      if(on_node != last_best)     // Pick a new tile
      if(on_node >= 0 && on_node < MAP_TILES)    
      if( map_col[on_node] == 0 || map_col[on_node] == 3 || map_col[on_node] == col_type) 
      {     
              
        if(Stuck_Check(on_node, i, j) == false || map_col[on_node] == 3)  
        if(Diagonal_Check(on_node, i, j)==false) 
        { 
                 
             midX = (float)row_x;                          
             midY = (float)row_y;    

             if(MAP_WIDTH != 0)
                 g_y = (float)(goal_best/MAP_WIDTH);           

             g_x = goal_best - (g_y*MAP_WIDTH);     
                           
             tarX = g_x;                 
             tarY = g_y;                 
                                   
             distance = Node_Distance1(midX, midY, tarX, tarY);

             if(stuck_to_wall_on == true)
             if(Stuck_To_Wall(on_node, i, j)==false) // Is this tile near a wall check..
             {  
                 distance = -1;    
             }   
                 
             if(stuck_to_wall_on == true)
             if(distance != -1 && best_count >= 0)
             {        
                 best_list[best_count]=on_node;        
                 best_count++; 
             }      

             if(distance != -1)
             if(distance < closest)         
             {
                 
                 best = on_node;   
                 closest = distance;            
                     
             }

         }                           
                  
      } 
              
    }       
    
    if(best_count > 1)  
    {
        // Choose the node that is on my wall..
        ep_id++;      
        if(ep_id >= MAX_PATHS)ep_id=MAX_PATHS-1;   
		if(ep_id >= 0)      
	        entry_point[ep_id] = last_best; 
    }  
    
    closest = 10000.0f;                        
    
    if(best == goal_node)
    {  
        Path_Found=true;    
        last_best = best;        
    } 
    
    // Couldn't find a new point  
    if(last_best == best)    
    { 
		if(ep_id >= 0)
        if(last_best == entry_point[ep_id])
        {
                     
            no_path_found++;    
            if(no_path_found >= 1)
            {  
                ep_id--;  
                    
                if(ep_id < 0)            
                {
                //    Path_Found=false;    
                    break; 
                }
            } 
            
            // Ready to detach from the wall..         
            for(int k=0;k<count;k++)
            {
                on_node = recorded[k];
                
                if(MAP_WIDTH != 0)
                    row_y = on_node/MAP_WIDTH;
                row_x = on_node - (row_y*MAP_WIDTH);                 
                
                midX = (float)row_x;                             
                midY = (float)row_y;    
                 
                if(MAP_WIDTH != 0)
                    g_y = (float)(goal_best/MAP_WIDTH);             

                g_x = goal_best - (g_y*MAP_WIDTH);     
                           
                tarX = g_x;                  
                tarY = g_y;                 
                                   
                distance = Node_Distance1(midX, midY, tarX, tarY);
                
                if(MAP_WIDTH != 0)
                    g_y = (float)(last_node/MAP_WIDTH);             

                g_x = last_node - (g_y*MAP_WIDTH);     
                           
                tarX = g_x;                
                tarY = g_y;    
                
                distance += (Node_Distance1(midX, midY, tarX, tarY)/2);                 
                
                if(distance < closest)       
                {
                   best = on_node; 
                   closest = distance;            
                }                        
                    
            }            
                
            last_best = best;
            stuck_to_wall_on = false; 
            first_stuck = true;    
            
        } 
        else 
        {   
      		if(ep_id >= 0)
			{
	            last_best = entry_point[ep_id];
	            best = entry_point[ep_id];		
			}			
                             
            first_stuck = false; 
        }
    }  
    else        
    {
        first_stuck = false;  
                      
        last_best = best;    
        
        no_path_found=0;
       
        if(best >= MAP_TILES)
			best=MAP_TILES-1;
	
		if(best >= 0)
	        map_col[best] = 4;      
        
		if(count >= 0) 
	        recorded[count] = best;  
                  
        count++;          
        
        if(count >= MAX_RECORDS)
			count=MAX_RECORDS-1;
               
    }          
                
    best_count = 0;
                  
  }
      
  return(count);      

}

int Reorder_Pathway(int count, int last_node, int goal_node, bool testing)
{ 
     
  if( count < 0) 
  {
	return(0);
  }

  int* temp_record = new int[count];
  int* temp_record1 = new int[count];

  //int temp_record[count];
  //int temp_record1[count];  
  int temp_node=0;
  float closest=100000.0f;
  float distance=0; 
  int row_x=0,row_y=0;
  float g_x=0,g_y=0;
  float x1=0.0,y1=0.0;
  int best=0;
  bool swi_goal=true;
  int temp_goal;
  int last_best;
  int highest=-1;    
  bool is_diagonal=false;    
  float midX=0.0;
  float midY=0.0;
  float tarX=0.0;
  float tarY=0.0;      
  int  new_count=0;       
  int entry_point=0; 
  int last_junction=-1;
  int best_count=0;  
  int junction_list[MAX_PATHS];
  int j_id=0;
  int cost=0;  
  int path_id=0; 
  int free_id=0;
  bool on_junction=false;
  bool skip_this=false;  
  bool recording=true; 
  int temp_start=0;
  int temp_end=0;
  int temp=0;
  int on_node=0;
  bool reverse=false;
  int viewX_Limit=0;  
  int viewX1_Limit=0;
  int viewY_Limit=0;
  int viewY1_Limit=0;    
  int last_bests[4];
  int last_bests_count=0;
  
  // Start at the goal work your way to the home node using map_col[4]'s...
  
  for(int k=0;k<MAX_PATHS;k++)
  {
      path[k].cost  = 0;
      path[k].start = -1;
      path[k].end   = -1;
  } 
      
  last_best = goal_node;  
  temp_goal = last_node;    
  
  if(MAP_HEIGHT != 0)
      row_y = last_best/MAP_HEIGHT;       
  row_x = last_best - (row_y*MAP_HEIGHT); 
          
  viewX_Limit  = row_x - limit_value;  
  viewX1_Limit = row_x + limit_value; 
  viewY_Limit  = row_y - limit_value;
  viewY1_Limit = row_y + limit_value;
  
  if(viewX_Limit < 0)
      viewX_Limit = 0;
  if(viewX1_Limit > MAP_WIDTH)  
      viewX1_Limit = MAP_WIDTH-1;
  if(viewY_Limit < 0) 
      viewY_Limit = 0;
  if(viewY1_Limit > MAP_HEIGHT)
      viewY1_Limit = MAP_HEIGHT-1;
      
  junction_list[0]   = goal_node; 
  path[0].start = goal_node;
  path[0].index = 0;  
  path[0].cost=0;      

  if(Path_Found == true)    
  for(int back=0;back<limit_value*limit_value;back++)    
  {   
                             
    for(int i=-1;i<=1;i++)  // Y        
    for(int j=-1;j<=1;j++)  // X        
    {     
  
      on_node = last_best;   
              
      if(MAP_WIDTH != 0)      
          row_y = on_node/MAP_WIDTH;
      row_x = on_node - (row_y*MAP_WIDTH);
      
      row_y += i;      
      row_x += j; 
       
      if(row_y < 0) 
          row_y = 0;
      if(row_y > MAP_HEIGHT)    
          row_y = MAP_HEIGHT-1;  
      if(row_x < 0)
          row_x = 0;        
      if(row_x > MAP_WIDTH)  
          row_x = MAP_WIDTH;         
           
      on_node = (row_y*MAP_WIDTH) + row_x;           
      
      if(row_x >= viewX_Limit && row_x <= viewX1_Limit)             
      if(row_y >= viewY_Limit && row_y <= viewY1_Limit)         
      if(i == 0 || j == 0)         // No Diagonals   
      if(on_node != last_best)     // Pick a new tile
      if(on_node >= 0 && on_node < MAP_TILES)   
      if( map_col[on_node] == 4 || map_col[on_node] == 2 )    
      {                           
                
             if(Diagonal_Check(on_node, i, j)==false)      
             {    
                  
                 midX = (float)row_x;                
                 midY = (float)row_y; 

                 if(MAP_WIDTH !=0)
                 g_y = (float)(temp_goal/MAP_WIDTH);           
                 g_x = (float)(temp_goal - (g_y*MAP_WIDTH));     
                           
                 tarX = g_x;                 
                 tarY = g_y; 
                                 
                 distance = Node_Distance1(midX, midY, tarX, tarY);
      
                 best_count++; 
      
                 if(distance < closest)         
                 {
                     best = on_node;  
                     closest = distance;            
                 }
                 
             }
                           
      }

                    
    }
          
      closest = 10000;     
      
      if(best != temp_goal) 
      if(best_count > 1 )          
      {   
              
          skip_this = false;
          for(int k=0;k<=j_id;k++)
          if(junction_list[k] == last_best)
              skip_this = true; 
              
          if(skip_this == false)
          {
			  if(path_id >= 0)
	              path[path_id].end = last_best;         

              j_id++; 

              if(j_id >= MAX_PATHS)
				 j_id=MAX_PATHS-1;                                      

			  if(j_id >= 0)
              junction_list[j_id] = last_best;

              recording = false;
          }   
      }               
                  
      best_count = 0;                         

      // Couldn't find a new point 
      if(best != temp_goal)          
      {  
        if(last_best == best)           
        {    
             
            recording = false;
            
            // If on a junction go back to an earlier one.
            // If on a dead-end go back to last junction
            skip_this = false;
            for(int k=0;k<=j_id;k++)
            if(junction_list[k] == last_best)
                skip_this = true; 
                
            if(skip_this == false) // Dead-End
            {     
                if(path_id >= 0)            
                path[path_id].end = -1;  
                             
                // Am I going backwards  
                if(MAP_HEIGHT != 0 && MAP_WIDTH != 0)
                for(int k=0;k<=j_id;k++)  
                if((junction_list[k] == last_best+MAP_WIDTH && last_junction != last_best+MAP_WIDTH && last_best/MAP_HEIGHT == (last_best+MAP_WIDTH)/MAP_HEIGHT)
                || (junction_list[k] == last_best-MAP_WIDTH && last_junction != last_best-MAP_WIDTH && last_best/MAP_HEIGHT == (last_best-MAP_WIDTH)/MAP_HEIGHT)
                || (junction_list[k] == last_best-1 && last_junction != last_best-1 && last_best/MAP_WIDTH == (last_best-1)/MAP_WIDTH)  
                || (junction_list[k] == last_best+1 && last_junction != last_best+1 && last_best/MAP_WIDTH == (last_best+1)/MAP_WIDTH) )
                {
					if(path_id >= 0)
                    path[path_id].end = junction_list[k]; 
                }    

                if(j_id >= 0)                
	                last_best = junction_list[j_id]; 
                
            }               
              
            if(skip_this == true) // On a Junction
            {    
                j_id--;   
                
                if(j_id < 0)
                    break;

                if(j_id >= 0)    
                	last_best = junction_list[j_id];
            }
            
            best = last_best;  
                
        }        
        else                           
        {     
           
          // Create a new path.. 
          if(recording == false) 
          {  
              path_id++; 

			  if(path_id >= 0)	
	              path[path_id].cost=0;

              if(path_id >= MAX_PATHS)
				path_id=MAX_PATHS-1;    
           
			  if(path_id >= 0)
	              path[path_id].start = last_best;

              last_junction = last_best; 

		      if(path_id >= 0)		
	              path[path_id].index = new_count;
          }     
  
          if(best >= MAP_TILES)
			best=MAP_TILES-1; 

          if(new_count >= 0)          
	          temp_record[new_count] = best;  
          
          new_count++;   
              
          if(new_count > count)
			new_count=count-1;
 
          if(path_id >= 0)              
          	path[path_id].cost++;      
                                                           
          recording = true;  
   
          if(best >= 0)       
              map_col[best] = 5;     
           
          for(int k=0;k<=j_id;k++)
		  if( junction_list[k] >= 0)
          if( map_col[junction_list[k]] != 2)
              map_col[junction_list[k]] = 8;
          
          last_best = best;         

        }          
      }       
      
      // Reached the goal  
      if(best == temp_goal)                  
      {    
          // Go back to last junction point
		  if(path_id >= 0)
          	path[path_id].end = -2; 

          recording = false;

		  if(j_id >= 0)
            last_best = junction_list[j_id];

          best = last_best;
   
      }         
              
    }          

                       
      for(int i = 0;i<count;i++)
	  if( recorded[i] >= 0)
      {
              
        map_col[recorded[i]] = 0;
        
   //     if(tiles[recorded[i]]>=480 && tiles[recorded[i]] < 484 )
   //         map_col[recorded[i]] = 9;            
             
        recorded[i] = -1; 
      } 
                  
      // Get path; 
      if(Path_Found == true)       
      if(path_id != 0)      
          Calculate_Path(path_id, last_node, goal_node);  

      new_count=0;         
      
      // Record the pathways that aren't -1;  
      if(Path_Found == true)        
      if(path_id < MAX_PATHS)  
      if(path_id != 0)          
      for(int j=0;j<=path_id;j++)   
      for(int i=0;i<path[j].cost;i++)
      {
   
          on_node = path[j].index;         
                    
          if(path[j].end != -1 && path[j].start != -1)
		  if(on_node+i >= 0 && new_count >= 0)   
          { 
                        
              if( temp_record[on_node+i] < MAP_TILES)            
                  temp_record1[new_count] = temp_record[on_node+i];
              new_count++;     
              if(new_count > count)new_count=count; 
          }
          else
              break;           
      }         
      
      if(Path_Found == true)              
      if(path_id == 0)      
      for(int i=0;i<path[0].cost;i++)
      {
          on_node = path[0].index;         
                    
          if(path[0].end != -1 && path[0].start != -1)  
          {

              if(on_node+i >= 0 && new_count >= 0)                         
              if( temp_record[on_node+i] < MAP_TILES)            
                  temp_record1[new_count] = temp_record[on_node+i];

              new_count++;

              if(new_count > count)new_count=count;
                   
          }        
      }     
      
	  if(last_node >= 0 && goal_node >= 0)
	  {  
	      map_col[last_node] = 2;                                     
	      map_col[goal_node] = 3;  
	  }
      
      temp = temp_record1[0]; 
        
      // Fix any holes in the path..
      // Start at beginning and go towards the end
      on_node = last_node;
      last_best = -1;
      
      best_count = 0;  
      
      memset(last_bests, -1, sizeof(last_bests));
                 
      if(Path_Found == true)  
      for(int j=0;j<new_count*2;j++)  
      { 
               
        skip_this = false;     
              
        for(int i=0;i<new_count;i++)  
        {
        
           if(temp_record1[i] !=  last_bests[0] && temp_record1[i] !=  last_bests[1] 
           && temp_record1[i] !=  last_bests[2] && temp_record1[i] !=  last_bests[3]) 
           if((temp_record1[i] == on_node+MAP_WIDTH) 
           || (temp_record1[i] == on_node-MAP_WIDTH)
           || (temp_record1[i] == on_node-1 && on_node/MAP_WIDTH == (on_node-1)/MAP_WIDTH)
           || (temp_record1[i] == on_node+1 && on_node/MAP_WIDTH == (on_node+1)/MAP_WIDTH) )  
           { 
                               
               on_node = temp_record1[i];    
                   
               last_bests_count++;   

               if(last_bests_count >= 4)
				  last_bests_count = 0;
                                                                          
               if(last_bests_count >= 0)
            	   last_bests[last_bests_count] = temp_record1[i];

               if(best_count >= 0)                            
            	   recorded[best_count] = temp_record1[i];

			   if(best_count < MAX_RECORDS)
				   best_count++;  
               
               skip_this = true;
               break;     
           }  
        }
          
        // There is a hole...
        if(skip_this == false) 
        { 
                                        
             for(int i=0;i<new_count;i++)  
             if(temp_record[i] !=  last_bests[0] && temp_record[i] !=  last_bests[1] 
             && temp_record[i] !=  last_bests[2] && temp_record[i] !=  last_bests[3]) 
             if((temp_record[i] == on_node+MAP_WIDTH) 
             || (temp_record[i] == on_node-MAP_WIDTH)
             || (temp_record[i] == on_node-1 && on_node/MAP_WIDTH == (on_node-1)/MAP_WIDTH)
             || (temp_record[i] == on_node+1 && on_node/MAP_WIDTH == (on_node+1)/MAP_WIDTH) )  
             {  
                             
               on_node = temp_record[i];    
               
               last_bests_count++; 

               if(last_bests_count >= 4)
			  	  last_bests_count = 0;

               if(last_bests_count >= 0)                                              
               	   last_bests[last_bests_count] = temp_record[i];

               if(best_count >= 0)
                   recorded[best_count] = temp_record[i];

               best_count++; 
    
               break;              
               
             }        

        }
        
        
      }
     
     // For testing 
/*            
      for(int i = 0;i<count;i++)
      {
        recorded[i] = temp_record1[i];  
      } 
      best_count = count;
*/

    delete [] temp_record; 
	delete [] temp_record1; 

    return(best_count);    
 
}


void Calculate_Path(int path_id, int last_node, int goal_node)
{
     int j_list[MAX_PATHS];
     int pathway[MAX_PATHS];
     int route[MAX_PATHS];
     int pathway_id=0;
     int route_id=0;
     int route_cost=0;
     int best_cost=0;
     int j_id=0;  
     int prior_node=0; 
     int testing=0;
     int closed_list[MAX_PATHS];  
     int closed_list_id=0;
     int closed_choice[4];    
     int choice_id=0; 
     int choice=0;
     int looking_for_choice=1;
     int choice_taken=0;
     int total_choice=0; 
     
     bool found_a_route=false;   
     bool bad_junction=false;
     bool finished=false;
     bool keep_in=false;
     bool restart=false;
     bool is_start=false;
     bool running_a_choice=false;
     
     memset(route, -1, sizeof(route));
     memset(j_list, -1, sizeof(j_list));
     memset(pathway, -1, sizeof(pathway));
     memset(closed_list, -1, sizeof(closed_list));
               
     j_list[0]   = goal_node;      
     j_id++;
           
     pathway_id=0;        
     
     route_id = 0;         
                              
     prior_node = -1; 
     
     route_cost = 0;  
                          
     best_cost = 10000;   
           
     // Get a path that starts or ends at j_list[1];
     for(int j=0;j<=path_id*path_id;j++) 
     { 
               
         found_a_route=false;                        
         choice=0;           
         running_a_choice=false; 

                  
     for(int i=0;i<=path_id;i++) 
     if( i != prior_node)  
	 if(j_id-1 >= 0)      
     if( path[i].start == j_list[j_id-1] || path[i].end == j_list[j_id-1] )  
     if( path[i].start != -1 && path[i].end != -1 ) 
         choice++;     
         
     if(choice > 4)
         choice = 4;
  
     for(int i=0;i<=path_id;i++) 
     if( i != prior_node)    
	 if(j_id-1 >= 0)        
     if( path[i].start == j_list[j_id-1] || path[i].end == j_list[j_id-1] )  
     if( path[i].start != -1 && path[i].end != -1 ) 
     {            
              
             bad_junction=false;             
                
             for(int k=0;k<closed_list_id;k++) 
             if(i == closed_list[k])             
                 bad_junction=true;

             if(path[i].start == j_list[j_id-1])
                 is_start = true; 
             else      
                 is_start = false;   
               
             for(int y=0;y<choice_id;y++)
             if( i == closed_choice[y] )
                 bad_junction = true;      
                                
             if(is_start == true)              
               for(int k=0;k<j_id;k++)      
               if(path[i].end == j_list[k])
			   if(closed_list_id >= 0)
               {
                 closed_list[closed_list_id]= i;
                 closed_list_id++; 
                 if(closed_list_id >= MAX_PATHS)closed_list_id=MAX_PATHS-1; 
                           
                 bad_junction=true;    
               }                  
                  
             if(is_start == false)             
               for(int k=0;k<j_id;k++)      
               if(path[i].start == j_list[k])
			   if(closed_list_id >= 0)
               {   
                       
                 closed_list[closed_list_id]= i;
                 closed_list_id++;  
                 if(closed_list_id >= MAX_PATHS)closed_list_id=MAX_PATHS-1;                                                 

                 bad_junction=true;           
               }    
 
             if(found_a_route == false)    
             if(bad_junction==false)     
             {   
                 if( path[i].end == -2 || path[i].start == -2) // A goal node
                 {  

					 if(pathway_id >= 0)
	                     pathway[pathway_id] = i; 

                     prior_node = i; 
                     choice_taken = i;  

                     if(closed_list_id >= 0)                     
	                     closed_list[closed_list_id]= i;

                     closed_list_id++;
                     if(closed_list_id >= MAX_PATHS)closed_list_id=MAX_PATHS-1;
                    
                     pathway_id++;   
                     
                     if(pathway_id >= MAX_PATHS)pathway_id=MAX_PATHS-1;                          
                     
                     // Start Recording the route if it's the shortest yet.
                     route_cost = 0;      
                     for(int x=0;x < pathway_id;x++)
					 if(pathway[x] >= 0)
                     {
                         route_cost += path[pathway[x]].cost;    
                     } 
                     
                     if(route_cost < best_cost)
                     {     
                         route_id = 0;  
                                 
                         for(int x=0;x < pathway_id;x++)    
                         {
                             route[x] = pathway[x]; 
                              
                             route_id = pathway_id;     

                         } 
                         
                         best_cost = route_cost; 
                
                     } 
                      
                     pathway_id--; 
                     
                     // End of record route    
                     running_a_choice=true;   
                 
                     found_a_route=true;
                         
                     break;
                           
                 }      
                 else                 
                 {                      
					 
 					 if(j_id >= 0)
					 {
                     if(is_start == true)           
                         j_list[j_id]   = path[i].end;  
                     else
                         j_list[j_id]   = path[i].start;  
					 }
                         
                     j_id++;          
                     
                     if(j_id >= MAX_PATHS)j_id=MAX_PATHS-1;

                     if(pathway_id >= 0)                             
	                     pathway[pathway_id] = i; 

                     prior_node = i; 
                     choice_taken = i;
                                         
                     pathway_id++; 
                     if(pathway_id >= MAX_PATHS)pathway_id=MAX_PATHS-1;
                                          
                     running_a_choice=true;
                     found_a_route=true; 
                     
                     break;   
                 }        
             }     
              
     } // For path_id      
       
     
     // We have a choice start point
     if(choice > 1 && looking_for_choice == 1)
     { 
               
         if( choice_id < 4 && choice_id >= 0)    
             closed_choice[choice_id] = choice_taken;      

         looking_for_choice = 0;        
             
         choice_id++;     
         total_choice = choice; 
         
         if(choice_id > total_choice)
         {  
                    
             break;   
         }    
         
     } 
  
     // Stuck at a dead-end.. 
     if(found_a_route==false)       
     {  
         // Start a new route...
                  
         j_id--;

         pathway_id--;     
         
         if(j_id <= 0)                           
         {     
             
             looking_for_choice = 1;
             
             j_list[0]   = path[0].start;      
             j_id=1;  
          
             pathway_id = 0;      
                                          
             closed_list_id=0;                              
             
             prior_node = -1;               
         }
     }
          
     }   
     
     // Any paths that aren't on pathway end and starts == -1
     if(path_id < MAX_PATHS) 
     for(int j=0;j<MAX_PATHS;j++)
     {        
              
         keep_in = false;    
         
         if(route_id < MAX_PATHS)    
         for(int i=0;i<route_id;i++)
         if( j == route[i] )  
         {
             keep_in = true;  

         }  
               
         if(keep_in == false)
         {    
             path[j].end     = -1;
             path[j].start   = -1;
         }   
     
     }    
     
} 


void Next_node(int loop, bool increase_counter) 
{
    int the_node=0; 
    int on_node=0;
    int list_index=-1;   
    int temp_row_x=0;
    int temp_row_y=0;  
    int temp_index=0;   
	int temp_node=0;
    float x1=0.0,y1=0.0;  
	float testX=0.0f, testY=0.0f;
    bool is_tank = false;
	bool check=false;
	int increased_node_counter_by = 0;
	int inc_amount = 0;
       
	if(loop < 0)
    {
		return; 
	}

    col_type = 0; // For water stuff
    
    limit_value = COL_LIMIT; 
    
//    if(loop == ply_id && has_water == true && has_crate_equipped == false)
//        col_type = 9;

    x1 = sprite[loop].w+sprite[loop].box_width/2;
    y1 = sprite[loop].z+sprite[loop].box_height/2;   
         
    // Check to see if I can't see the end_x, end_y...
    if(Shoot_Ray(loop, x1, y1, sprite[loop].end_x, sprite[loop].end_y, true, false, 0.02f)==true)
    {  
        
        if(increase_counter == true)      
            sprite[loop].node_counter++;   
        
        the_node = sprite[loop].node_counter;     
		temp_node = the_node; 
		 
		if(the_node >= 0 && the_node < NODE_LIMIT) 
            list_index = sprite[loop].node_list[the_node]; 
    
		if(list_index >= 0 && list_index < 10000)
        if(list_index != 0 && (map_col[list_index] == 0 || map_col[list_index] == col_type) )       
        {         
            temp_row_y = list_index/MAP_HEIGHT;          
            temp_row_x = list_index - (temp_row_y*MAP_HEIGHT);     
        
            // Calculate offsets for mov_x if near wall
            if( loop == ply_id ) 
                Wall_Offset(loop, temp_row_x, temp_row_y, list_index, false);
            else
                Wall_Offset(loop, temp_row_x, temp_row_y, list_index, true);
            

        }         
    
        // If my x,y is the next node then quit
        temp_row_x = (int)((x1 + map_startX)*10);              
        temp_row_y = (int)((y1 + map_startY)*10);    
    
        on_node = (temp_row_y*MAP_HEIGHT)+temp_row_x;     
        
        on_node = -1;
        
		check = false;

		if( list_index >= 0 && list_index < 10000)
		if(map_col[list_index] != 0 && map_col[list_index] != col_type)	
			check = true;

        if( list_index == 0  
        || on_node == list_index  
        || check == true 
        )
        {
            sprite[loop].moving = false;  
			  
        	if(loop != ply_id)
                ShotIdle(loop);     
        } 
        
    } 
    else   
    { 
        sprite[loop].mov_x = sprite[loop].end_x; 
        sprite[loop].mov_y = sprite[loop].end_y;
   	
		if( sprite[loop].mov_x  < -map_startX || sprite[loop].mov_x  >  map_startX  || sprite[loop].mov_y < -map_startY || sprite[loop].mov_y >  map_startY  )
		{
		  sprite[loop].mov_x = (sprite[loop].w + sprite[loop].box_width/2);
		  sprite[loop].mov_y = (sprite[loop].z + sprite[loop].box_height/2); 
 		}
    }
    
    
}
bool Shoot_Ray_Ply(int loop, float x1, float y1, float x2, float y2)
{ 
   
	bool success=false;

    float my_x=0.0f, my_y=0.0f;
    float angle=0.0f, deltax=0.0f, deltay=0.0f;
    float mid_x=0.0f, mid_y =0.0f;
    float tar_x=0.0f, tar_y =0.0f;
    float step=0, distance=0.0f; 
    int row_x=0;
    int row_y=0;
    int the_row=0;    
	float off_set=0.05f;
	float box_offset=0.01f; 
    int iterations=0;
	int no_of_blocks_hit=0;

    my_x = x1;
    my_y = y1;

    distance = Node_Distance1(x1, y1, x2, y2);
        
    angle = atan2(y2 - y1,x2 - x1);      
   
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

    for(int j = 0; j <= iterations; j++) 
    { 
        
        my_x += deltax; // Which is the mid_x
        my_y += deltay; // Which is the mid_y
          
       row_x = (int)((my_x + map_startX)*10);    
       row_y = (int)((my_y + map_startY)*10);        
     
       the_row = (row_y*MAP_HEIGHT)+row_x;    

	   if(the_row < 0)
	       break;       
  
/*       if(tiles[the_row] == 0 && (in_dungeon == true && !ARCADE)) // For hitting the black darkness
       {
           success=true; 
           break;     
       }   */
          
       if(map_col[the_row] == 1)
       {

			no_of_blocks_hit=0; 

			box_offset = 0.04f;  
          
       		row_x = (int)((my_x + box_offset + map_startX)*10);    
       		row_y = (int)((my_y + box_offset + map_startY)*10);        
       		the_row = (row_y*MAP_HEIGHT)+row_x;  
			if(the_row < 0)break;  
			if(map_col[the_row] == 1 )
				no_of_blocks_hit++;
          
       		row_x = (int)((my_x - box_offset + map_startX)*10);    
       		row_y = (int)((my_y - box_offset + map_startY)*10);        
       		the_row = (row_y*MAP_HEIGHT)+row_x;  
			if(the_row < 0)break;  
			if(map_col[the_row] == 1 )
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
            	success=true; 
            	break;   
			} 

       }  

	}

	return(success);


}


bool Shoot_Ray(int loop, float x1, float y1, float x2, float y2, bool grey_test, bool shooting, float precision)
{ 
     
    bool test_success=false; 
    bool test_water=false; 
    
    float x=0.0, y=0.0;
    float angle=0.0, deltax=0.0, deltay=0.0;
    float step=0, distance=0.0;
    int iterations=0;
    int temp_row=0; 
    int temp_r_x=0;  
    int temp_r_y=0; 

    float increment=precision; 
    
	// x1 == sprite's x
	// y1 == sprite's y 

	// x2 == target x
	// y2 == target y

    if(shooting == true) 
    {
        increment = 0.0025f;
        test_water = true;  
    }
 
	increment = (float)LINE_OF_SIGHT; 

    if(ply_id != -1 && loop >= 0) 
    if(loop == ply_id && has_water == true)
        test_water = true;
        
    if(p1_buddy != -1 && loop >= 0)
    if(loop == p1_buddy && has_water == true)
        test_water = true;        
    
    x = x1; 
    y = y1;  
    
    distance = Node_Distance1(x1, y1, x2, y2);   
   
    angle = atan2(y2 - y1,x2 - x1);     
    
    deltax = cos(angle); // *1.2f   
    deltay = sin(angle); // *1.2f
        
    deltax *= (float)LINE_OF_SIGHT;          
    deltay *= (float)LINE_OF_SIGHT;
        
    step = Node_Distance1(x1, y1, x1+deltax, y1+deltay);
    
    if(step != 0)
        iterations = (int)(distance / step);   
       
    iterations--;       
        
    if(iterations < 0)  
        iterations = 0; 
    
	x -= deltax; // Start at exact player/sprite co-ordinates...
	y -= deltay; // Start at exact player/sprite co-ordinates...
        
    for (int i = 0; i <= iterations; i++)  
    { 
        
       x += deltax; // Which is the mid_x
       y += deltay; // Which is the mid_y

       // Upper right corner       
       temp_r_x = (int)((x+increment + map_startX)*10);   
       temp_r_y = (int)((y+increment + map_startY)*10); 
         
       temp_row = (temp_r_y*MAP_HEIGHT)+temp_r_x;     
                   
       if( temp_row >= 0 && temp_row < MAP_TILES)
       {
         if(grey_test == true)
         if( map_col[temp_row]==6 || map_col[temp_row]==10 ||(map_col[temp_row] == 7 && Level != LVL_SUB_PEN) ) 
         {
           test_success = true;  
           break;               
         }  
		 if(shooting == true)  
		 if(loop != -1)
         if( (map_col[temp_row]==10 && sprite[loop].sector != UNIT_BOMBER)) //   || (map_col[temp_row] == 7 && Level != LVL_SUB_PEN)    
         {
           test_success = true;  
           break;  
         }
         if(map_col[temp_row]==1 )     
         {
           test_success = true;  
           break;  
         }
         if(test_water == false)
         if(tiles[temp_row]>=480 && tiles[temp_row] < 484 )    
         {
           test_success = true;  
           break;  
         }          
       }
       // Upper left corner       
       temp_r_x = (int)((x-increment + map_startX)*10);   
       temp_r_y = (int)((y+increment + map_startY)*10); 
         
       temp_row = (temp_r_y*MAP_HEIGHT)+temp_r_x;     
                  
       if( temp_row >= 0 && temp_row < MAP_TILES)
       {
         if(grey_test == true) 
         if( map_col[temp_row] == 6 || map_col[temp_row]==10 || (map_col[temp_row] == 7 && Level != LVL_SUB_PEN) ) 
         {
           test_success = true;  
           break;               
         }
		 if(shooting == true) 
		 if(loop != -1)
         if( (map_col[temp_row]==10 && sprite[loop].sector != UNIT_BOMBER) )  //  || (map_col[temp_row] == 7 && Level != LVL_SUB_PEN)   
         {
           test_success = true;  
           break;  
         }
         if(map_col[temp_row] == 1 )      
         {
           test_success = true;  
           break;  
         }
         if(test_water == false)
         if(tiles[temp_row]>=480 && tiles[temp_row] < 484 )    
         {
           test_success = true;  
           break;  
         }          
       }
       // Lower right corner       
       temp_r_x = (int)((x+increment + map_startX)*10);   
       temp_r_y = (int)((y-increment + map_startY)*10); 
         
       temp_row = (temp_r_y*MAP_HEIGHT)+temp_r_x;     
                  
       if( temp_row >= 0 && temp_row < MAP_TILES)
       {
         if(grey_test == true)
         if( map_col[temp_row]==6 || map_col[temp_row]==10 || (map_col[temp_row] == 7 && Level != LVL_SUB_PEN)) 
         {
           test_success = true;  
           break;               
         }
		 if(shooting == true)
		 if(loop != -1)
         if( (map_col[temp_row]==10 && sprite[loop].sector != UNIT_BOMBER)) //   || (map_col[temp_row] == 7 && Level != LVL_SUB_PEN)    
         {
           test_success = true;  
           break;  
         }
         if(map_col[temp_row]==1 )   
         {
           test_success = true;  
           break;  
         }
         if(test_water == false)
         if(tiles[temp_row]>=480 && tiles[temp_row] < 484 )    
         {
           test_success = true;  
           break;  
         }          
       }
       // Lower left corner       
       temp_r_x = (int)((x-increment + map_startX)*10);   
       temp_r_y = (int)((y-increment + map_startY)*10); 
         
       temp_row = (temp_r_y*MAP_HEIGHT)+temp_r_x;     
                  
       if( temp_row >= 0 && temp_row < MAP_TILES)    
       {
         if(grey_test == true)  
         if( map_col[temp_row] == 6 || map_col[temp_row]==10 || (map_col[temp_row] == 7 && Level != LVL_SUB_PEN)) 
         {
           test_success = true;   
           break;               
         } 
		 if(shooting == true)
		 if(loop != -1)
         if( (map_col[temp_row]==10 && sprite[loop].sector != UNIT_BOMBER))  //   || (map_col[temp_row] == 7 && Level != LVL_SUB_PEN)   
         {
           test_success = true;  
           break;  
         }
         if(map_col[temp_row]==1 )    
         {
           test_success = true;  
           break;  
         }
         if(test_water == false)
         if(tiles[temp_row]>=480 && tiles[temp_row] < 484 )     
         {
           test_success = true;  
           break;  
         }          
       }
       
                               
    } 
 
  return(test_success);     
     
}   
int Sta2_Clean_Pathway(int count, int start_point, int loop) 
{
	int new_path[MAX_RECORDS];
    int count1=0;
    int temp_row_x=0; 
    int temp_row_y=0;   
	int furthest_node = -1;
	int furthest_count = -1;
    float start_X, start_Y;  
    float end_X, end_Y;
	bool found_a_path = false;

	if(count < 0)
		return(0);

	if(MAP_HEIGHT != 0)       
	{
		temp_row_y = start_point / MAP_HEIGHT;          
		temp_row_x = start_point - (temp_row_y*MAP_HEIGHT);      
	}
     
    start_X = ( (-map_startX + ( (float)temp_row_x * 0.1f )) + 0.05f ); 
    start_Y = ( (-map_startY + ( (float)temp_row_y * 0.1f )) + 0.05f );  

	// Find furthest node that I can see...

	for(int j=0;j<count;j++) 
	{   

		for(int i=0;i<count;i++)    
		{ 
          
			if(i != furthest_count)
			if(i >= 0 && i < MAX_RECORDS)    
			{      
				if(MAP_HEIGHT != 0)  
				{
					temp_row_y = recorded[i]/MAP_HEIGHT;        
					temp_row_x = recorded[i] - (temp_row_y*MAP_HEIGHT);    
				}

				end_X = ( (-map_startX + ( (float)temp_row_x * 0.1f )) + 0.05f ); 
				end_Y = ( (-map_startY + ( (float)temp_row_y * 0.1f )) + 0.05f );  
          
				if(Shoot_Ray(loop, start_X, start_Y, end_X, end_Y, true, false, 0.02f)==false)
				{
					furthest_node = recorded[i];
					furthest_count = i;
				}

			} 
			    
		}
		  
		if(furthest_node != -1) 
		{
			found_a_path = true;
			new_path[count1] = furthest_node;
			count1++;
		}
		if(furthest_node == -1)
			break;

		if(furthest_count == (count-1)) 
			break;

		furthest_node = -1; 
	
		if(MAP_HEIGHT != 0)       
		{
			temp_row_y = recorded[furthest_count] / MAP_HEIGHT;          
			temp_row_x = recorded[furthest_count] - (temp_row_y*MAP_HEIGHT);      
		}
     
		start_X = ( (-map_startX + ( (float)temp_row_x * 0.1f )) + 0.05f ); 
		start_Y = ( (-map_startY + ( (float)temp_row_y * 0.1f )) + 0.05f ); 

	}
	 
    if(found_a_path == true)       
    if(count1 < MAX_RECORDS) 
    for(int i=0;i<count1;i++)    
    { 
        recorded[i] = new_path[i]; 
    } 

    return(count1);  

}

int Clean_Pathway(int count, int start_point, int loop) 
{
     
	int* new_path = new int[count];
    bool test_success=false; 
    int temp_row=0;
    int temp_row_x=0; 
    int temp_row_y=0;   
    int last_good_one=0; 
    bool finished = false;  
    int last_node=0;
    int count1=0;
    float start_X, start_Y;  
    float end_X, end_Y;     
    int wset_row=0;  
    int wset_rowX=0;
    int wset_rowY=0;

	if(count < 0)
		return(0);
    
    if(MAP_HEIGHT != 0)       
	{
		temp_row_y = start_point / MAP_HEIGHT;          
		temp_row_x = start_point - (temp_row_y*MAP_HEIGHT);      
	}
     
    start_X = ( (-map_startX + ( (float)temp_row_x * 0.1f )) + 0.05f ); 
    start_Y = ( (-map_startY + ( (float)temp_row_y * 0.1f )) + 0.05f );    
    
    // Use line of sight to jump corners etc, in theory anyway
    if(Path_Found == true) 
    for(int j=0;j<count*count;j++)      
    { 
      
      if(finished == true)
          break;
                            
      for(int i=last_node;i<count;i++)  
	  if(i >= 0)   
      {   
        
        if(i-1 >= 0)
        {      
            last_good_one = recorded[i-1];   
            last_node = i-1;             
        } 
        else 
        {
            last_good_one = recorded[i];
            last_node = i; 
        }     
        
        if(i == count-1)  
        {    
            finished = true;      
        }  
         
        if(i >= 0 && i < MAX_RECORDS)
        {   
            if(MAP_HEIGHT != 0)                           
            temp_row_y = recorded[i]/MAP_HEIGHT;        
            temp_row_x = recorded[i] - (temp_row_y*MAP_HEIGHT);    
        } 
        
        end_X = ( (-map_startX + ( (float)temp_row_x * 0.1f )) + 0.05f ); 
        end_Y = ( (-map_startY + ( (float)temp_row_y * 0.1f )) + 0.05f );  
          
        if(Shoot_Ray(loop, start_X, start_Y, end_X, end_Y, true, false, 0.02f)==true)
            break;    
                                                
      }          
               
      temp_row_y = last_good_one/MAP_HEIGHT;         
      temp_row_x = last_good_one - (temp_row_y*MAP_HEIGHT);    
     
      start_X = ( (-map_startX + ( (float)temp_row_x * 0.1f )) + 0.05f );
      start_Y = ( (-map_startY + ( (float)temp_row_y * 0.1f )) + 0.05f );  

      if(count1 >= 0)
	      new_path[count1] = last_good_one;   
        
      count1++;         
           
      if(count1 > count)count1 = count;
             
      if(count1 >= count)         
        finished = true;  
     
  }        
  
    if(Path_Found == true)    
    if(count1 < MAX_RECORDS)
    for(int i=0;i<count1;i++) 
    { 
        if(i < count)    
            recorded[i] = new_path[i]; 
    } 
    
	delete [] new_path;

    return(count1);   
      
}  

void Wall_Offset(int loop, int row_x, int row_y, int index, bool is_tank)
{
    bool g_direct[8];
    float INCREMENT = 0.00f; 
        
    memset(g_direct, false, sizeof(g_direct) );  
    
    if(index >= 0 && index < MAP_TILES)    
    {   
		if( index+1 >= 0 && index+1 < MAP_TILES)
        if(map_col[index+1] != 0 && map_col[index+1] != col_type ) // RIGHT 
           g_direct[7] = true; 
		
		if( index-1 >= 0 && index-1 < MAP_TILES)
        if(map_col[index-1] != 0 && map_col[index-1] != col_type ) // LEFT
           g_direct[3] = true;

		if( index+MAP_WIDTH >= 0 && index+MAP_WIDTH < MAP_TILES)
        if(map_col[index+MAP_WIDTH] != 0 && map_col[index+MAP_WIDTH] != col_type ) // UP
           g_direct[5] = true;

		if( index-MAP_WIDTH >= 0 && index-MAP_WIDTH < MAP_TILES)
        if(map_col[index-MAP_WIDTH] != 0 && map_col[index-MAP_WIDTH] != col_type ) // DOWN
           g_direct[1] = true;  
 
		if( index+(MAP_WIDTH+1) >= 0 && index+(MAP_WIDTH+1) < MAP_TILES)
        if(map_col[index+(MAP_WIDTH+1)] != 0 && map_col[index+(MAP_WIDTH+1)] != col_type ) // UP-RIGHT
           g_direct[6] = true;

		if( index+(MAP_WIDTH-1) >= 0 && index+(MAP_WIDTH-1) < MAP_TILES)
        if(map_col[index+(MAP_WIDTH-1)] != 0 && map_col[index+(MAP_WIDTH-1)] != col_type ) // UP-LEFT
           g_direct[4] = true;

		if( index-(MAP_WIDTH+1) >= 0 && index-(MAP_WIDTH+1) < MAP_TILES) 
        if(map_col[index-(MAP_WIDTH+1)] != 0 && map_col[index-(MAP_WIDTH+1)] != col_type ) // DOWN-RIGHT
           g_direct[0] = true;

		if( index-(MAP_WIDTH-1) >= 0 && index-(MAP_WIDTH-1) < MAP_TILES)
        if(map_col[index-(MAP_WIDTH-1)] != 0 && map_col[index-(MAP_WIDTH-1)] != col_type ) // DOWN-LEFT
           g_direct[2] = true;    

        if(g_direct[7] == true) // RIGHT  
           wall_offset_X-=INCREMENT; 
        if(g_direct[3] == true) // LEFT  
           wall_offset_X+=INCREMENT; 
        if(g_direct[5] == true) // UP
           wall_offset_Y-=INCREMENT; 
        if(g_direct[1] == true) // DOWN
           wall_offset_Y+=INCREMENT; 
           
        if(g_direct[7] == true && g_direct[5] == true) // UP-RIGHT
        {
           wall_offset_X-=INCREMENT;
           wall_offset_Y-=INCREMENT;                                                               
        }
        if(g_direct[3] == true && g_direct[5] == true) // UP-LEFT
        {
           wall_offset_X+=INCREMENT; 
           wall_offset_Y-=INCREMENT;                                                               
        }                                                 
        if(g_direct[7] == true && g_direct[1] == true) // DOWN-RIGHT
        {
           wall_offset_X-=INCREMENT;
           wall_offset_Y+=INCREMENT;                                                                 
        }                           
        if(g_direct[3] == true && g_direct[1] == true) // DOWN-LEFT
        {
           wall_offset_X+=INCREMENT;
           wall_offset_Y+=INCREMENT;                                                              
        }  
                                             
    }                        
     
    if( loop != -1)
    {
        sprite[loop].mov_x = -map_startX + (( (float)row_x * 0.1f )+0.05f);
        sprite[loop].mov_y = -map_startY + (( (float)row_y * 0.1f )+0.05f); 
   	
		if( sprite[loop].mov_x  < -map_startX || sprite[loop].mov_x  >  map_startX  || sprite[loop].mov_y < -map_startY || sprite[loop].mov_y >  map_startY  )
		{
		  sprite[loop].mov_x = (sprite[loop].w + sprite[loop].box_width/2);
		  sprite[loop].mov_y = (sprite[loop].z + sprite[loop].box_height/2); 
 		}
   
    }
     
    if(wall_offset_X > INCREMENT)  
        wall_offset_X = INCREMENT; 
    if(wall_offset_X < -INCREMENT)
        wall_offset_X = -INCREMENT;  
    if(wall_offset_Y > INCREMENT)
        wall_offset_Y = INCREMENT; 
    if(wall_offset_Y < -INCREMENT)
        wall_offset_Y = -INCREMENT;
        
    if(loop != -1)
    {
        sprite[loop].mov_x += wall_offset_X; 
        sprite[loop].mov_y += wall_offset_Y;
    }
     
}

bool Diagonal_Check(int on_node, int y, int x)
{
    bool test_success = false;
    int test_row1=0;
    int test_row2=0;  

    if(y == -1 && x == -1) // DOWN-LEFT 
    {
        test_row1 = on_node+1; 
        test_row2 = on_node+MAP_WIDTH;
        
        if(test_row1 >= 0 && test_row1 <= MAP_TILES)
        if(test_row2 >= 0 && test_row2 <= MAP_TILES)
        if((map_col[test_row1] == 1 || map_col[test_row1] == 6 || map_col[test_row1] == 7 || map_col[test_row1] == 10)
        && (map_col[test_row2] == 1 || map_col[test_row2] == 6 || map_col[test_row2] == 7 || map_col[test_row2] == 10) )
            test_success = true; 
    }
    if(y == 1 && x == -1) // UP-LEFT
    {
        test_row1 = on_node+1;
        test_row2 = on_node-MAP_WIDTH;
        
        if(test_row1 >= 0 && test_row1 < MAP_TILES)
        if(test_row2 >= 0 && test_row2 < MAP_TILES)
        if((map_col[test_row1] == 1 || map_col[test_row1] == 6 || map_col[test_row1] == 7 || map_col[test_row1] == 10)
        && (map_col[test_row2] == 1 || map_col[test_row2] == 6 || map_col[test_row2] == 7 || map_col[test_row2] == 10) )
            test_success = true; 
    }     
    if(y == -1 && x == 1) // DOWN-RIGHT 
    {
        test_row1 = on_node-1;
        test_row2 = on_node+MAP_WIDTH;
        
        if(test_row1 >= 0 && test_row1 < MAP_TILES)
        if(test_row2 >= 0 && test_row2 < MAP_TILES)
        if((map_col[test_row1] == 1 || map_col[test_row1] == 6 || map_col[test_row1] == 7 || map_col[test_row1] == 10)
        && (map_col[test_row2] == 1 || map_col[test_row2] == 6 || map_col[test_row2] == 7 || map_col[test_row2] == 10) )
            test_success = true;  
    }
    if(y == 1 && x == 1) // UP_RIGHT       
    {   
        test_row1 = on_node-1; 
        test_row2 = on_node-MAP_WIDTH;
        
        if(test_row1 >= 0 && test_row1 < MAP_TILES)
        if(test_row2 >= 0 && test_row2 < MAP_TILES)
        if((map_col[test_row1] == 1 || map_col[test_row1] == 6 || map_col[test_row1] == 7 || map_col[test_row1] == 10)
        && (map_col[test_row2] == 1 || map_col[test_row2] == 6 || map_col[test_row2] == 7 || map_col[test_row2] == 10) )
            test_success = true; 
    }
     
    return(test_success);    
     
}


bool Stuck_Check(int on_node, int y, int x)
{  
     
    bool success=false;         
    int near_collision=0; 
    int test_row=0;
    
    test_row = on_node-1; 
        
    if(test_row >= 0 && test_row <= MAP_TILES)
    if( (map_col[test_row] == 1 || map_col[test_row] == 6 || map_col[test_row] == 7 || map_col[test_row] == 10) )
        near_collision++; 
          
    test_row = on_node+1;  
        
    if(test_row >= 0 && test_row <= MAP_TILES)
    if( (map_col[test_row] == 1 || map_col[test_row] == 6 || map_col[test_row] == 7 || map_col[test_row] == 10) )
        near_collision++;  

    test_row = on_node-MAP_WIDTH; 
            
    if(test_row >= 0 && test_row <= MAP_TILES)
    if( (map_col[test_row] == 1 || map_col[test_row] == 6 || map_col[test_row] == 7 || map_col[test_row] == 10) )
        near_collision++; 
    
    test_row = on_node+MAP_WIDTH; 
            
    if(test_row >= 0 && test_row <= MAP_TILES)
    if( (map_col[test_row] == 1 || map_col[test_row] == 6 || map_col[test_row] == 7 || map_col[test_row] == 10) )
        near_collision++; 
    
    test_row = on_node+MAP_WIDTH-1; 
    
    if(near_collision >= 3)  
        success = true;
    
    return(success);  
     
}

bool Stuck_To_Wall(int on_node, int y, int x)
{  
     
    bool success=false;         
    int near_collision=0;  
    int test_row=0;
    int row_x=0;   
    int row_y=0;
    
    row_y = on_node/MAP_WIDTH;
    row_x = on_node - (row_y*MAP_WIDTH);
          
    test_row = on_node-1; 
    
    if(row_x != 0)    
    if(test_row >= 0 && test_row <= MAP_TILES)
    if( (map_col[test_row] == 1 || map_col[test_row] == 6 || map_col[test_row] == 7 || map_col[test_row] == 10) )
        near_collision++; 
           
    test_row = on_node+1;      
    
    if(row_x != MAP_WIDTH-1)         
    if(test_row >= 0 && test_row <= MAP_TILES)
    if( (map_col[test_row] == 1 || map_col[test_row] == 6 || map_col[test_row] == 7 || map_col[test_row] == 10) )
        near_collision++;  

    test_row = on_node-MAP_WIDTH; 
    
    if(row_y != 0)              
    if(test_row >= 0 && test_row <= MAP_TILES)
    if( (map_col[test_row] == 1 || map_col[test_row] == 6 || map_col[test_row] == 7 || map_col[test_row] == 10) )
        near_collision++; 
    
    test_row = on_node+MAP_WIDTH; 
    
    if(row_y != MAP_HEIGHT-1)                
    if(test_row >= 0 && test_row <= MAP_TILES)
    if( (map_col[test_row] == 1 || map_col[test_row] == 6 || map_col[test_row] == 7 || map_col[test_row] == 10) )
        near_collision++; 
    
    test_row = on_node+MAP_WIDTH-1; 
        
    if(row_y != MAP_HEIGHT-1 && row_x != 0)                 
    if(test_row >= 0 && test_row <= MAP_TILES)
    if( (map_col[test_row] == 1 || map_col[test_row] == 6 || map_col[test_row] == 7 || map_col[test_row] == 10) )
        near_collision++; 
    
    test_row = on_node+MAP_WIDTH+1; 
    
    if(row_y != MAP_HEIGHT-1 && row_x != MAP_WIDTH-1)             
    if(test_row >= 0 && test_row <= MAP_TILES)
    if( (map_col[test_row] == 1 || map_col[test_row] == 6 || map_col[test_row] == 7 || map_col[test_row] == 10) )
        near_collision++; 
    
    test_row = on_node-MAP_WIDTH-1;         
    
    if(row_y != 0 && row_x != 0)             
    if(test_row >= 0 && test_row <= MAP_TILES)
    if( (map_col[test_row] == 1 || map_col[test_row] == 6 || map_col[test_row] == 7 || map_col[test_row] == 10) )
        near_collision++; 
    
    test_row = on_node-MAP_WIDTH+1;     
    
    if(row_y != 0 && row_x != MAP_WIDTH-1)              
    if(test_row >= 0 && test_row <= MAP_TILES)
    if( (map_col[test_row] == 1 || map_col[test_row] == 6 || map_col[test_row] == 7 || map_col[test_row] == 10) )
        near_collision++;        
    
    if(near_collision >= 1)
        success = true;
    
    return(success);
     
}

int Get_Tile_Index(float x, float y)
{
     
    int temp_row_x=0;
    int temp_row_y=0;
    int temp_index=0;
    
    // Check if this tile is available...  
             
    temp_row_x = (int)((x + map_startX)*10);      
    temp_row_y = (int)((y + map_startY)*10);      
    
    temp_index = (temp_row_y*MAP_HEIGHT)+temp_row_x;        
    
    if(temp_index < 0 || temp_index >= MAP_TILES)
        temp_index = 0;
    
    return(temp_index);
    
}


bool Check_Col_Types(int temp_row, bool grey_test, bool shooting, bool test_water)	
{		

	return 0;
}

