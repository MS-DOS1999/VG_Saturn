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
extern void SwipeCode(int f_rate);
extern int Convert_Angle_To_Dir(float my_angle);
extern void CreateObject(float x, float y, float width, float height, int priority, int anim, int id, int type, int obj_type);
extern void sta2_Reduce_Tileset(int index, int valueX, int valueY, int radius);

int Count_Tiles_City(int x, int y);
int Proc_Get_Pixel_City(int pixel, int row_x, int row_y);
void sta2_Proc_Level_City(); 
 
#define TEST_ROUTE_MAP  0

#define CY_ROOM_EMPTY        0
#define CY_ROOM_ROAD_RIGHT   1
#define CY_ROOM_ROAD_UP      2
#define CY_ROOM_ROAD_RIGHT1  3
#define CY_ROOM_ROAD_RIGHT2  4
#define CY_ROOM_ROAD_CROSS   5
#define CY_ROOM_ROAD_CROSSU   6
#define CY_ROOM_ROAD_CROSSD   7
#define CY_ROOM_ROAD_CROSSL   8
#define CY_ROOM_ROAD_CROSSR   9

#define CY_ROOM_TREE         10

#define CY_ROOM_HUT1     12
#define CY_ROOM_HUT2     13
#define CY_ROOM_HUT3     14
#define CY_ROOM_HUT4     15
#define CY_ROOM_HUT5     16
#define CY_ROOM_HUT6     17

#define CY_ROOM_ROCK1        18
#define CY_ROOM_ROCK2        19
#define CY_ROOM_ROCK3        20
#define CY_ROOM_ROCK4        21

#define CY_ROOM_CRATER1        22
#define CY_ROOM_CRATER2        23
#define CY_ROOM_CRATER3        24
#define CY_ROOM_CRATER4        25


#define CY_ROOM_FULL        40
#define CY_ROOM_BUSH_UP     41
#define CY_ROOM_BUSH_DOWN   42
#define CY_ROOM_BUSH_LEFT   43
#define CY_ROOM_BUSH_RIGHT  44
#define CY_ROOM_BUSH_UPLEFT    45
#define CY_ROOM_BUSH_UPRIGHT   46
#define CY_ROOM_BUSH_DOWNLEFT   47
#define CY_ROOM_BUSH_DOWNRIGHT  48
#define CY_ROOM_BUSH_LEFTRIGHT  49
#define CY_ROOM_BUSH_ENDLEFT    50
#define CY_ROOM_BUSH_ENDRIGHT   51
#define CY_ROOM_BUSH_ENDUP      52
#define CY_ROOM_BUSH_ENDDOWN    53
#define CY_ROOM_BUSH_UPDOWN     54

 
void sta2_Proc_Level_City()   
{
	 
	int tileIndex=0; 
	int tile_textureID = 0;
	int x=0,y=0;
	int startTile=0;
	int strX=0, strY=0;
	int endX=0, endY=0;
	int gotoX=0, gotoY=0;
	int count=0;
	int length = 0;
	int endTile=0;   
	int temp_row_x=0, temp_row_y=0;  
	int rnd=0;
	int no_of_player_units=0;
	int tilecol[10];
	float midX=0.0f, midY=0.0f;
	bool continue_on = false;
	int index=0, index1=0;

	if(sta2_battle_squad[0] != -1)
		no_of_player_units = 1;
	if(sta2_battle_squad[1] != -1)
		no_of_player_units = 2;
	if(sta2_battle_squad[2] != -1)
		no_of_player_units = 3;
	if(sta2_battle_squad[3] != -1)
		no_of_player_units = 4;
	if(sta2_battle_squad[4] != -1) 
		no_of_player_units = 5; 

	float angle=0.0f;
	 
    memset( tiles, 0, sizeof(tiles) );        
    memset( map_col, 0, sizeof(map_col) );
	memset( map_cover, 0, sizeof(map_cover) );  
    memset( map_set, 0, sizeof(map_set) );  

	for(int y=0;y<(MAP_HEIGHT/2);y++)  
	for(int x=0;x<(MAP_WIDTH/2);x++)    
	{
		room[y][x] = CY_ROOM_EMPTY; 
		room_col[y][x] = false;
	}

	// Setup player start positions... 
	if(sta2_is_epic_battle == true)
		index = 5;
	else
		index = 4;

	no_points = 0;
	   
	spawn_tile_count = 0;

	// Generate players...
	for(int y=2;y < ((MAP_HEIGHT-4));y++)         
	for(int x=2;x < (MAP_WIDTH-4);x++)   
	if(spawn_tile_count < 10000)
	{
		spawn_tileX[spawn_tile_count] = x;
		spawn_tileY[spawn_tile_count] = y;
		spawn_tile_count++;
	}

	// Generate players... 
	for(int i=0;i<index;i++)              
	{    

		if(rand()%4 == 0 && sta2_is_first_level == false) 
			rnd = rand()%(spawn_tile_count);  
		else
			rnd = rand()%(spawn_tile_count/2);  

		gotoX = spawn_tileX[rnd];             
		gotoY = spawn_tileY[rnd];  

		sta2_Reduce_Tileset(rnd, 0, 0, 0);

		points[i].x = -map_startX + ( ((float)gotoX * 0.1f) + 0.05f ); // -5.0, 0.1
		points[i].y = -map_startY + ( ((float)gotoY * 0.1f) + 0.05f ); // -5.0, 0.1 

		points[i].c1 = CAM_SPAWN;  
		angle = atan2(0.0f - points[i].y, 0.0f - points[i].x);

		points[i].c2 = Convert_Angle_To_Dir(angle); 
		no_points++;

		
	}  
	 
	if(sta2_is_epic_battle == true) 
		index1 = index + 14; 
	else
		index1 = index + 6;

	// Generate enemies...
	for(int i=index;i<index1;i++)    
	{ 
		rnd = rand()%(spawn_tile_count);  

		gotoX = spawn_tileX[rnd];             
		gotoY = spawn_tileY[rnd];  

		sta2_Reduce_Tileset(rnd, 0, 0, 0);

		points[i].x = -map_startX + ( ((float)gotoX * 0.1f) + 0.05f ); // -5.0, 0.1
		points[i].y = -map_startY + ( ((float)gotoY * 0.1f) + 0.05f ); // -5.0, 0.1

		// Set a direction for the enemy  to face a player unit...
		if(no_of_player_units > 0) 
			rnd = rand()%no_of_player_units;
		else
			no_of_player_units = 0;

		angle = atan2(points[rnd].y - points[i].y, points[rnd].x - points[i].x);

		points[i].c1 = NPC_PNT;

		points[i].c2 = Convert_Angle_To_Dir(angle);
		no_points++;

	}

	if(sta2_is_epic_battle == true)
		index = 12;
	else
		index = 6;
	      
	for(int i = 0;i < index;i++)  
	{
		// Draw a bush...
		gotoX = 0;   
		gotoY = rand()%(MAP_HEIGHT/2);   

		length = 4+rand()%(MAP_WIDTH-4); 

		for(int x=0;x<length;x++)  
		{ 

			if(gotoX >= 0 && gotoX < (MAP_WIDTH/2) && gotoY >= 0 && gotoY < (MAP_HEIGHT/2))
				room[gotoY][gotoX] = CY_ROOM_FULL;
			if(gotoX >= 0 && gotoX < (MAP_WIDTH/2) && (gotoY-1) >= 0 && (gotoY-1) < (MAP_HEIGHT/2))
				room[gotoY-1][gotoX] = CY_ROOM_FULL;

			gotoX++; 

			if(rand()%3 == 0)
				gotoY--;

		}

	}

	if(sta2_is_epic_battle == true)
		index = 12;
	else
		index = 6;

	for(int i = 0;i < index;i++)    
	{
		// Draw a bush...     
		gotoX = (MAP_WIDTH/2)-1;   
		gotoY = rand()%(MAP_HEIGHT/2);  

		length = 4+rand()%(MAP_WIDTH-4); 

		for(int x=0;x<length;x++)  
		{ 

			if(gotoX >= 0 && gotoX < (MAP_WIDTH/2) && gotoY >= 0 && gotoY < (MAP_HEIGHT/2))
				room[gotoY][gotoX] = CY_ROOM_FULL;
			if(gotoX >= 0 && gotoX < (MAP_WIDTH/2) && (gotoY-1) >= 0 && (gotoY-1) < (MAP_HEIGHT/2))
				room[gotoY-1][gotoX] = CY_ROOM_FULL;

			gotoX--; 
			 
			if(rand()%3 == 0)
				gotoY++;

		}

	}

//	if(rand()%3 != 0)
	for(int i = 0;i < 1;i++)    
	{
		// Draw a road across...
		gotoX = 0;   
		gotoY = rand()%(MAP_HEIGHT/2); 

		length = (MAP_WIDTH/2);  
		  
		for(int x=0;x<length;x++)       
		{ 

			if(gotoX >= 0 && gotoX < (MAP_WIDTH/2) && gotoY >= 0 && gotoY < (MAP_HEIGHT/2))
				room[gotoY][gotoX] = CY_ROOM_ROAD_RIGHT; 

			gotoX++;    
			  
			if(rand()%3 == 0) 
			{
				if(gotoX >= 0 && gotoX < (MAP_WIDTH/2) && gotoY >= 0 && gotoY < (MAP_HEIGHT/2))
					room[gotoY][gotoX] = CY_ROOM_ROAD_RIGHT;

					gotoY--;
				if(gotoY < 0) 
					break;
			}     
			  
		}

	}

//	if(rand()%3 != 0)
	for(int i = 0;i < 1;i++)   
	{
		// Draw a road up...
		gotoX = rand()%(MAP_WIDTH/2);   
		gotoY = 0;        
		 
		length = (MAP_WIDTH/2);    
		 
		for(int x=0;x<length;x++)       
		{  

			if(gotoX >= 0 && gotoX < (MAP_WIDTH/2) && gotoY >= 0 && gotoY < (MAP_HEIGHT/2))
				room[gotoY][gotoX] = CY_ROOM_ROAD_RIGHT; 

			gotoY++;      
			   
			if(rand()%3 == 0)
			{
				if(gotoX >= 0 && gotoX < (MAP_WIDTH/2) && gotoY >= 0 && gotoY < (MAP_HEIGHT/2))
					room[gotoY][gotoX] = CY_ROOM_ROAD_RIGHT;
				
				gotoX--;

				if(gotoX < 0) 
					break;
			}     
			  
		}

	}

	// Fix up roads...
	for(int y=0;y<(MAP_HEIGHT/2);y++)   
	for(int x=0;x<(MAP_WIDTH/2) ;x++)    
	{ 		 

		for(int i=0;i<10;i++)  
			tilecol[i] = 0;  

		// Bush edges...
		if(room[y][x] >= CY_ROOM_ROAD_RIGHT && room[y][x] <= CY_ROOM_ROAD_CROSSR)
		{

			gotoX = x;	gotoY = y+1;
			if(gotoX >= 0 && gotoY >= 0 && gotoX < (MAP_WIDTH/2) && gotoY < (MAP_HEIGHT/2))
			if(room[gotoY][gotoX] >= CY_ROOM_ROAD_RIGHT && room[gotoY][gotoX] <= CY_ROOM_ROAD_CROSSR)
				tilecol[UP] = 1; 
			if(gotoX < 0 || gotoY < 0 || gotoX >= (MAP_WIDTH/2) || gotoY >= (MAP_HEIGHT/2))
				tilecol[UP] = 1;  

			gotoX = x;	gotoY = y-1;
			if(gotoX >= 0 && gotoY >= 0 && gotoX < (MAP_WIDTH/2) && gotoY < (MAP_HEIGHT/2))
			if(room[gotoY][gotoX] >= CY_ROOM_ROAD_RIGHT && room[gotoY][gotoX] <= CY_ROOM_ROAD_CROSSR)
				tilecol[DOWN] = 1; 
			if(gotoX < 0 || gotoY < 0 || gotoX >= (MAP_WIDTH/2) || gotoY >= (MAP_HEIGHT/2))
				tilecol[DOWN] = 1;  
			 
			gotoX = x-1; gotoY = y;
			if(gotoX >= 0 && gotoY >= 0 && gotoX < (MAP_WIDTH/2) && gotoY < (MAP_HEIGHT/2))
			if(room[gotoY][gotoX] >= CY_ROOM_ROAD_RIGHT && room[gotoY][gotoX] <= CY_ROOM_ROAD_CROSSR)
				tilecol[LEFT] = 1;  
			if(gotoX < 0 || gotoY < 0 || gotoX >= (MAP_WIDTH/2) || gotoY >= (MAP_HEIGHT/2))
				tilecol[LEFT] = 1;  
			 
			gotoX = x+1; gotoY = y;
			if(gotoX >= 0 && gotoY >= 0 && gotoX < (MAP_WIDTH/2) && gotoY < (MAP_HEIGHT/2))
			if(room[gotoY][gotoX] >= CY_ROOM_ROAD_RIGHT && room[gotoY][gotoX] <= CY_ROOM_ROAD_CROSSR)
				tilecol[RIGHT] = 1; 
			if(gotoX < 0 || gotoY < 0 || gotoX >= (MAP_WIDTH/2) || gotoY >= (MAP_HEIGHT/2))
				tilecol[RIGHT] = 1;  
			 
			if(tilecol[RIGHT] == 1 && tilecol[UP] == 1)
				room[y][x] = CY_ROOM_ROAD_RIGHT1;   
			if(tilecol[LEFT] == 1 && tilecol[DOWN] == 1)
				room[y][x] = CY_ROOM_ROAD_RIGHT2;

			if(tilecol[LEFT] == 1 && tilecol[UP] == 0 && tilecol[DOWN] == 0)
				room[y][x] = CY_ROOM_ROAD_RIGHT;
			if(tilecol[RIGHT] == 1 && tilecol[UP] == 0 && tilecol[DOWN] == 0)
				room[y][x] = CY_ROOM_ROAD_RIGHT;
			if(tilecol[LEFT] == 0 && tilecol[RIGHT] == 0  && (tilecol[UP] == 1 || tilecol[DOWN] == 1) ) 
				room[y][x] = CY_ROOM_ROAD_UP; 
			

			if(tilecol[LEFT] == 1 && tilecol[RIGHT] == 1  && tilecol[UP] == 0 && tilecol[DOWN] == 1)  
				room[y][x] = CY_ROOM_ROAD_CROSSU; 
			if(tilecol[LEFT] == 1 && tilecol[RIGHT] == 1  && tilecol[UP] == 1 && tilecol[DOWN] == 0)  
				room[y][x] = CY_ROOM_ROAD_CROSSD; 
			if(tilecol[LEFT] == 1 && tilecol[RIGHT] == 0  && tilecol[UP] == 1 && tilecol[DOWN] == 1)  
				room[y][x] = CY_ROOM_ROAD_CROSSL; 
			if(tilecol[LEFT] == 0 && tilecol[RIGHT] == 1  && tilecol[UP] == 1 && tilecol[DOWN] == 1)  
				room[y][x] = CY_ROOM_ROAD_CROSSR; 


			if(tilecol[LEFT] == 1 && tilecol[RIGHT] == 1  && tilecol[UP] == 1 && tilecol[DOWN] == 1)  
				room[y][x] = CY_ROOM_ROAD_CROSS; 

		}

	}

	// Draw some trees...
/*	for(int i = 0;i < 35;i++)     
	{
		x = rand()%(MAP_WIDTH/2);  
		y = rand()%(MAP_HEIGHT/2);   

		continue_on = true;
		  
		if(x >= 0 && x < (MAP_WIDTH/2) && y >= 0 && y < (MAP_HEIGHT/2))
		if(room[y][x] == CY_ROOM_EMPTY) 
		{
			for(int k=-2;k<3;k++)
			for(int j=-2;j<3;j++) 
			{
				gotoX=x+j;
				gotoY=y+k;

				if(gotoX >= 0 && gotoX < (MAP_WIDTH/2) && gotoY >= 0 && gotoY < (MAP_HEIGHT/2))
				if(room[gotoY][gotoX] != CY_ROOM_EMPTY)
					continue_on = false;
			}

			if(continue_on == true)
				room[y][x] = CY_ROOM_TREE;
		}

	}*/

	// Generate Rocks...
	for(int y=0;y<(MAP_HEIGHT/2);y++)       
	for(int x=0;x<(MAP_WIDTH/2);x++)     
	{ 

		if(room[y][x] == CY_ROOM_EMPTY) 
		{
			if(rand()%4 == 0)
			{ 
				rnd = rand()%4;

				if(rnd == 0)
					room[y][x] = CY_ROOM_ROCK1;
				if(rnd == 1)
					room[y][x] = CY_ROOM_ROCK2;
				if(rnd == 2)
					room[y][x] = CY_ROOM_ROCK3;
				if(rnd == 3)
					room[y][x] = CY_ROOM_ROCK4;

			}
		}

	}


	// Connect all points so there is always a route...
	for(int p=0;p<1;p++)       
	{     
		
		gotoX = rand()%MAP_WIDTH;  
		gotoY = rand()%MAP_HEIGHT;   
		  
		for(int l=0;l<no_points;l++)  
		{ 

			strX = (int)((points[l].x + map_startX)*10);              
			strY = (int)((points[l].y + map_startY)*10); 

			temp_row_x = strX/2;
			temp_row_y = strY/2;

			room_col[temp_row_y][temp_row_x] = true;

			for(int k=0;k<150;k++)  
			{  
				 
				temp_row_x = strX/2;
				temp_row_y = strY/2;
				if(temp_row_x >= 0 && temp_row_x < (MAP_WIDTH/2) && temp_row_y >= 0 && temp_row_y < (MAP_HEIGHT/2))
				if(room[temp_row_y][temp_row_x] == CY_ROOM_FULL || room[temp_row_y][temp_row_x] == CY_ROOM_TREE || (room[temp_row_y][temp_row_x] >= CY_ROOM_ROCK1 && room[temp_row_y][temp_row_x] <= CY_ROOM_ROCK4 ))
					room[temp_row_y][temp_row_x] = CY_ROOM_EMPTY;

				temp_row_x = (strX+1)/2;
				temp_row_y = strY/2;
				if(temp_row_x >= 0 && temp_row_x < (MAP_WIDTH/2) && temp_row_y >= 0 && temp_row_y < (MAP_HEIGHT/2))
				if(room[temp_row_y][temp_row_x] == CY_ROOM_FULL || room[temp_row_y][temp_row_x] == CY_ROOM_TREE || (room[temp_row_y][temp_row_x] >= CY_ROOM_ROCK1 && room[temp_row_y][temp_row_x] <= CY_ROOM_ROCK4 ))
					room[temp_row_y][temp_row_x] = CY_ROOM_EMPTY;

				if(strX > gotoX) 
					strX--;
				else if (strX < gotoX)
					strX++;
				if(strY > gotoY)
					strY--; 
				else if (strY < gotoY)
					strY++;

				if(strX == endX && strY == endY)
					break;
				 
			}
		}
	}

	// Remove all loose rooms... 
	for(int y=0;y<(MAP_HEIGHT/2);y++)      
	for(int x=0;x<(MAP_WIDTH/2);x++)  
	{ 

		if(x != 0 && y != 0 && x != ((MAP_WIDTH/2)-1) && y != ((MAP_HEIGHT/2)-1) ) 
		{
			if(room[y][x] == CY_ROOM_FULL)
			if(Count_Tiles_City(x, y) == 0)
				room[y][x] = CY_ROOM_EMPTY; 

			if(room[y][x] == CY_ROOM_EMPTY)  
			if(Count_Tiles_City(x, y) >= 4) 
				room[y][x] = CY_ROOM_FULL;
		}
	}

	// Generate craters...
	for(int y=0;y<(MAP_HEIGHT/2);y++)      
	for(int x=0;x<(MAP_WIDTH/2);x++)     
	{ 

		continue_on = true;

		if(x+2 < (MAP_WIDTH/2) && y+2 < (MAP_HEIGHT/2))  
		if(room[y][x] == CY_ROOM_EMPTY) 
		{ 

			if(room[y][x] != CY_ROOM_EMPTY || room_col[y][x]==true)  
				continue_on = false;
			if(room[y][x+1] != CY_ROOM_EMPTY || room_col[y][x+1]==true)  
				continue_on = false;
			 
			if(room[y+1][x] != CY_ROOM_EMPTY || room_col[y+1][x]==true) 
				continue_on = false;
			if(room[y+1][x+1] != CY_ROOM_EMPTY || room_col[y+1][x+1]==true)  
				continue_on = false;

			if(rand()%12 == 0)  
			if(continue_on == true)
			{
				room[y+1][x] = CY_ROOM_CRATER1;
				room[y+1][x+1] = CY_ROOM_CRATER2;
				room[y][x] = CY_ROOM_CRATER3;
				room[y][x+1] = CY_ROOM_CRATER4;

			}


		}

	}

	// Generate bush edges...
	for(int y=0;y<(MAP_HEIGHT/2);y++)      
	for(int x=0;x<(MAP_WIDTH/2);x++)     
	{ 

		for(int i=0;i<10;i++)  
			tilecol[i] = 0;  

		// Bush edges...
		if(room[y][x] == CY_ROOM_FULL) 
		{
			 
			gotoX = x;	gotoY = y;
			if(gotoX >= 0 && gotoY >= 0 && gotoX < (MAP_WIDTH/2) && gotoY < (MAP_HEIGHT/2))
			if(room[gotoY][gotoX] >= CY_ROOM_FULL && room[gotoY][gotoX] <= CY_ROOM_BUSH_UPDOWN)
					tilecol[RESET] = 1;  
			if(gotoX < 0 || gotoY < 0 || gotoX >= (MAP_WIDTH/2) || gotoY >= (MAP_HEIGHT/2))
				tilecol[RESET] = 1;  

			gotoX = x;	gotoY = y+1;
			if(gotoX >= 0 && gotoY >= 0 && gotoX < (MAP_WIDTH/2) && gotoY < (MAP_HEIGHT/2))
			if(room[gotoY][gotoX] >= CY_ROOM_FULL && room[gotoY][gotoX] <= CY_ROOM_BUSH_UPDOWN)
				tilecol[UP] = 1; 
			if(gotoX < 0 || gotoY < 0 || gotoX >= (MAP_WIDTH/2) || gotoY >= (MAP_HEIGHT/2))
				tilecol[UP] = 1;  

			gotoX = x;	gotoY = y-1;
			if(gotoX >= 0 && gotoY >= 0 && gotoX < (MAP_WIDTH/2) && gotoY < (MAP_HEIGHT/2))
			if(room[gotoY][gotoX] >= CY_ROOM_FULL && room[gotoY][gotoX] <= CY_ROOM_BUSH_UPDOWN)
				tilecol[DOWN] = 1; 
			if(gotoX < 0 || gotoY < 0 || gotoX >= (MAP_WIDTH/2) || gotoY >= (MAP_HEIGHT/2))
				tilecol[DOWN] = 1;  
			 
			gotoX = x-1; gotoY = y;
			if(gotoX >= 0 && gotoY >= 0 && gotoX < (MAP_WIDTH/2) && gotoY < (MAP_HEIGHT/2))
			if(room[gotoY][gotoX] >= CY_ROOM_FULL && room[gotoY][gotoX] <= CY_ROOM_BUSH_UPDOWN)
				tilecol[LEFT] = 1;  
			if(gotoX < 0 || gotoY < 0 || gotoX >= (MAP_WIDTH/2) || gotoY >= (MAP_HEIGHT/2))
				tilecol[LEFT] = 1;  
			 
			gotoX = x+1; gotoY = y;
			if(gotoX >= 0 && gotoY >= 0 && gotoX < (MAP_WIDTH/2) && gotoY < (MAP_HEIGHT/2))
			if(room[gotoY][gotoX] >= CY_ROOM_FULL && room[gotoY][gotoX] <= CY_ROOM_BUSH_UPDOWN)
				tilecol[RIGHT] = 1; 
			if(gotoX < 0 || gotoY < 0 || gotoX >= (MAP_WIDTH/2) || gotoY >= (MAP_HEIGHT/2))
				tilecol[RIGHT] = 1;  

			if(tilecol[LEFT] == 1)
				room[y][x] = CY_ROOM_BUSH_RIGHT;
			if(tilecol[RIGHT] == 1)
				room[y][x] = CY_ROOM_BUSH_LEFT;
			if(tilecol[UP] == 1)   
				room[y][x] = CY_ROOM_BUSH_DOWN; 
			if(tilecol[DOWN] == 1)   
				room[y][x] = CY_ROOM_BUSH_UP;

			     
			// Ends...
			if(tilecol[LEFT] == 1 && tilecol[RIGHT] == 0 && tilecol[UP] == 0 && tilecol[DOWN] == 0)
				room[y][x] = CY_ROOM_BUSH_ENDRIGHT;

			if(tilecol[LEFT] == 0 && tilecol[RIGHT] == 1 && tilecol[UP] == 0 && tilecol[DOWN] == 0)
				room[y][x] = CY_ROOM_BUSH_ENDLEFT;

			if(tilecol[LEFT] == 0 && tilecol[RIGHT] == 0 && tilecol[UP] == 1 && tilecol[DOWN] == 0)
				room[y][x] = CY_ROOM_BUSH_ENDDOWN;

			if(tilecol[LEFT] == 0 && tilecol[RIGHT] == 0 && tilecol[UP] == 0 && tilecol[DOWN] == 1)
				room[y][x] = CY_ROOM_BUSH_ENDUP;

			 
			if(tilecol[LEFT] == 1 && tilecol[RIGHT] == 1 && tilecol[UP] == 0 && tilecol[DOWN] == 0)
				room[y][x] = CY_ROOM_BUSH_LEFTRIGHT; 

			if(tilecol[UP] == 1 && tilecol[DOWN] == 1 && tilecol[LEFT] == 0 && tilecol[RIGHT] == 0)
				room[y][x] = CY_ROOM_BUSH_UPDOWN;


			if(tilecol[UP] == 1 && tilecol[LEFT] == 1)
				room[y][x] = CY_ROOM_BUSH_DOWNRIGHT;
			if(tilecol[UP] == 1 && tilecol[RIGHT] == 1) 
				room[y][x] = CY_ROOM_BUSH_DOWNLEFT;

			if(tilecol[DOWN] == 1 && tilecol[LEFT] == 1)   
				room[y][x] = CY_ROOM_BUSH_UPRIGHT;
			if(tilecol[DOWN] == 1 && tilecol[RIGHT] == 1)
				room[y][x] = CY_ROOM_BUSH_UPLEFT;

			if(tilecol[UP] == 1 && tilecol[LEFT] == 1 && tilecol[RIGHT] == 1)
				room[y][x] = CY_ROOM_BUSH_DOWN;

			if(tilecol[DOWN] == 1 && tilecol[LEFT] == 1 && tilecol[RIGHT] == 1)
				room[y][x] = CY_ROOM_BUSH_UP;

			if(tilecol[UP] == 1 && tilecol[DOWN] == 1 && tilecol[RIGHT] == 1)
				room[y][x] = CY_ROOM_BUSH_LEFT;

			if(tilecol[UP] == 1 && tilecol[DOWN] == 1 && tilecol[LEFT] == 1)
				room[y][x] = CY_ROOM_BUSH_RIGHT;

			if(tilecol[UP] == 1 && tilecol[DOWN] == 1 && tilecol[LEFT] == 1 && tilecol[RIGHT] == 1)
				room[y][x] = CY_ROOM_FULL;
		 
		} // room[y][x] == CY_ROOM_FULL)

	}

	// Paint 2x2 room tiles onto map...
	for(int i=0;i<MAP_HEIGHT;i+=2)     
	for(int j=0;j<MAP_WIDTH;j+=2)    
	{  

		y = i/2;  
		x = j/2; 

		if(room[y][x] == CY_ROOM_EMPTY) 
		{   
			rnd = rand()%8; 
			if(rnd == 0)
				tile_textureID = 0; 
			if(rnd == 1)
				tile_textureID = 2; 
			if(rnd == 2)
				tile_textureID = 4;
			if(rnd == 3)
				tile_textureID = 6;
			if(rnd == 4)
				tile_textureID = 8; 
			if(rnd == 5)
				tile_textureID = 10;
			if(rnd == 6)
				tile_textureID = 12;
			if(rnd == 7)
				tile_textureID = 14;
		}
		if(room[y][x] == CY_ROOM_ROAD_RIGHT)     
			tile_textureID = 96;
		if(room[y][x] == CY_ROOM_ROAD_UP)   
			tile_textureID = 98; 
		if(room[y][x] == CY_ROOM_ROAD_RIGHT1)
			tile_textureID = 100;    
		if(room[y][x] == CY_ROOM_ROAD_RIGHT2) 
			tile_textureID = 102;
		if(room[y][x] == CY_ROOM_ROAD_CROSS) 
			tile_textureID = 104;      
		if(room[y][x] == CY_ROOM_ROAD_CROSSU) 
			tile_textureID = 106; 
		if(room[y][x] == CY_ROOM_ROAD_CROSSD) 
			tile_textureID = 108;
		if(room[y][x] == CY_ROOM_ROAD_CROSSL) 
			tile_textureID = 110;
		if(room[y][x] == CY_ROOM_ROAD_CROSSR) 
			tile_textureID = 128;

		if(room[y][x] == CY_ROOM_CRATER1)      
			tile_textureID = 166;
		if(room[y][x] == CY_ROOM_CRATER2)     
			tile_textureID = 168;
		if(room[y][x] == CY_ROOM_CRATER3)     
			tile_textureID = 170;
		if(room[y][x] == CY_ROOM_CRATER4)     
			tile_textureID = 172;

		if(room[y][x] == CY_ROOM_HUT1) 
			tile_textureID = 130;  
		if(room[y][x] == CY_ROOM_HUT2)  
			tile_textureID = 132;
		if(room[y][x] == CY_ROOM_HUT3) 
			tile_textureID = 134;
		if(room[y][x] == CY_ROOM_HUT4) 
			tile_textureID = 136;
		if(room[y][x] == CY_ROOM_HUT5) 
			tile_textureID = 138;
		if(room[y][x] == CY_ROOM_HUT6)  
			tile_textureID = 140;

		if(room[y][x] == CY_ROOM_ROCK1)  
			tile_textureID = 142; 
		if(room[y][x] == CY_ROOM_ROCK2) 
			tile_textureID = 160; 
		if(room[y][x] == CY_ROOM_ROCK3) 
			tile_textureID = 162; 
		if(room[y][x] == CY_ROOM_ROCK4) 
			tile_textureID = 164; 

		
		if(room[y][x] == CY_ROOM_FULL)
			tile_textureID = 32;
		if(room[y][x] == CY_ROOM_BUSH_UP)    
			tile_textureID = 34;
		if(room[y][x] == CY_ROOM_BUSH_DOWN)      
			tile_textureID = 36;
		if(room[y][x] == CY_ROOM_BUSH_LEFT) 
			tile_textureID = 38;
		if(room[y][x] == CY_ROOM_BUSH_RIGHT)
			tile_textureID = 40;
		if(room[y][x] == CY_ROOM_BUSH_UPLEFT)   
			tile_textureID = 42;
		if(room[y][x] == CY_ROOM_BUSH_UPRIGHT)
			tile_textureID = 44;
		if(room[y][x] == CY_ROOM_BUSH_DOWNLEFT)
			tile_textureID = 46;
		if(room[y][x] == CY_ROOM_BUSH_DOWNRIGHT) 
			tile_textureID = 64;
		if(room[y][x] == CY_ROOM_BUSH_LEFTRIGHT)
			tile_textureID = 66;
		if(room[y][x] == CY_ROOM_BUSH_ENDLEFT)
			tile_textureID = 68;
		if(room[y][x] == CY_ROOM_BUSH_ENDRIGHT)
			tile_textureID = 70;
		if(room[y][x] == CY_ROOM_BUSH_ENDUP)
			tile_textureID = 72;
		if(room[y][x] == CY_ROOM_BUSH_ENDDOWN)
			tile_textureID = 74;
		if(room[y][x] == CY_ROOM_BUSH_UPDOWN)
			tile_textureID = 76;
		if(room[y][x] == CY_ROOM_TREE)
			tile_textureID = 78; 

		tileIndex = (i * MAP_WIDTH)+j;
		         
		if(tileIndex >= 0 && tileIndex < MAP_TILES) 
		{
			// Tile..  
			if(tileIndex >= 0 && tileIndex < MAP_TILES)
			{
				tiles[tileIndex] = tile_textureID; 
				map_cover[tileIndex] = 0;

				if(room[y][x] >= CY_ROOM_FULL || room[y][x] == CY_ROOM_TREE 
				|| room[y][x] == CY_ROOM_HUT5 || room[y][x] == CY_ROOM_ROCK3 || room[y][x] == CY_ROOM_ROCK4)
				if(room[y][x] != CY_ROOM_BUSH_DOWNLEFT) 
				if(room[y][x] != CY_ROOM_BUSH_ENDDOWN)  
				if(room[y][x] != CY_ROOM_TREE)
				{ 
					map_col[tileIndex] = 7;
					map_cover[tileIndex] = STA2_GRASS_COVER; 
					if(room[y][x] >= CY_ROOM_ROCK1 && room[y][x] <= CY_ROOM_ROCK4) 
						map_cover[tileIndex] = STA2_ROCK_COVER;
				}
				if(room[y][x] >= CY_ROOM_ROAD_RIGHT && room[y][x] <= CY_ROOM_ROAD_CROSSR 
				|| room[y][x] == CY_ROOM_HUT2 || room[y][x] == CY_ROOM_HUT3 || room[y][x] == CY_ROOM_HUT6)
					map_cover[tileIndex] = 1;

			}
			// Tile right..
			if( (tileIndex+1) >= 0 && (tileIndex+1) < MAP_TILES)
			{
				tiles[tileIndex+1] = tile_textureID+1; 
				map_cover[tileIndex+1] = 0; 

				if(room[y][x] >= CY_ROOM_FULL || room[y][x] == CY_ROOM_TREE 
				|| room[y][x] == CY_ROOM_HUT1 || room[y][x] == CY_ROOM_HUT3
				|| room[y][x] == CY_ROOM_ROCK3 || room[y][x] == CY_ROOM_ROCK4)
				if(room[y][x] != CY_ROOM_BUSH_DOWNRIGHT)    
				if(room[y][x] != CY_ROOM_BUSH_ENDDOWN)
				if(room[y][x] != CY_ROOM_TREE)       
				{
					map_col[tileIndex+1] = 7;  
					map_cover[tileIndex+1] = STA2_GRASS_COVER;
					if(room[y][x] >= CY_ROOM_ROCK1 && room[y][x] <= CY_ROOM_ROCK4) 
						map_cover[tileIndex+1] = STA2_ROCK_COVER;
				}
				if(room[y][x] >= CY_ROOM_ROAD_RIGHT && room[y][x] <= CY_ROOM_ROAD_CROSSR || room[y][x] == CY_ROOM_HUT2 || room[y][x] == CY_ROOM_HUT5)
					map_cover[tileIndex+1] = 1;
			}
			// Tile above... 
			if( (tileIndex+MAP_WIDTH) >= 0 && (tileIndex+MAP_WIDTH) < MAP_TILES)
			{
				tiles[tileIndex+MAP_WIDTH] = tile_textureID+16;
				map_cover[tileIndex+MAP_WIDTH] = 0;

				if(room[y][x] >= CY_ROOM_FULL || room[y][x] == CY_ROOM_TREE || room[y][x] == CY_ROOM_HUT4 
				|| room[y][x] == CY_ROOM_ROCK1 || room[y][x] == CY_ROOM_ROCK2)
				if(room[y][x] != CY_ROOM_BUSH_UPLEFT) 
				if(room[y][x] != CY_ROOM_BUSH_ENDUP)
				{
					map_col[tileIndex+MAP_WIDTH] = 7;   
					if(room[y][x] != CY_ROOM_TREE)
						map_cover[tileIndex+MAP_WIDTH] = STA2_GRASS_COVER; 
					if(room[y][x] == CY_ROOM_TREE) 
						map_cover[tileIndex+MAP_WIDTH] = STA2_TREE_COVER;
					if(room[y][x] >= CY_ROOM_ROCK1 && room[y][x] <= CY_ROOM_ROCK4) 
						map_cover[tileIndex+MAP_WIDTH] = STA2_ROCK_COVER;
				}
				if(room[y][x] >= CY_ROOM_ROAD_RIGHT && room[y][x] <= CY_ROOM_ROAD_CROSSR || room[y][x] == CY_ROOM_HUT5 || room[y][x] == CY_ROOM_HUT6)
					map_cover[tileIndex+MAP_WIDTH] = 1;
			}
			// Tile above right...
			if((tileIndex+MAP_WIDTH+1) >= 0 && (tileIndex+MAP_WIDTH+1) < MAP_TILES)
			{
				tiles[tileIndex+MAP_WIDTH+1] = tile_textureID+17;
				map_cover[tileIndex+MAP_WIDTH+1] = 0;

				if(room[y][x] >= CY_ROOM_FULL || room[y][x] == CY_ROOM_TREE || room[y][x] == CY_ROOM_HUT1 
				|| room[y][x] == CY_ROOM_ROCK1 || room[y][x] == CY_ROOM_ROCK2)
				if(room[y][x] != CY_ROOM_BUSH_UPRIGHT)  
				if(room[y][x] != CY_ROOM_BUSH_ENDUP)  
				{
					map_col[tileIndex+MAP_WIDTH+1] = 7;
					if(room[y][x] != CY_ROOM_TREE)
						map_cover[tileIndex+MAP_WIDTH+1] = STA2_GRASS_COVER;
					if(room[y][x] == CY_ROOM_TREE)
						map_cover[tileIndex+MAP_WIDTH+1] = STA2_TREE_COVER;
					if(room[y][x] >= CY_ROOM_ROCK1 && room[y][x] <= CY_ROOM_ROCK4) 
						map_cover[tileIndex+MAP_WIDTH+1] = STA2_ROCK_COVER;
				}
				if(room[y][x] >= CY_ROOM_ROAD_RIGHT && room[y][x] <= CY_ROOM_ROAD_CROSSR || room[y][x] == CY_ROOM_HUT4 || room[y][x] == CY_ROOM_HUT5)
					map_cover[tileIndex+MAP_WIDTH+1] = 1;
			}
		}
		 
	} // End for loop...

	// Paint in any missing tiles...      
	for(int i=0;i<MAP_HEIGHT;i++)     
	for(int j=0;j<MAP_WIDTH;j++)         
	{       

		tileIndex = (i * MAP_WIDTH)+j; 

		if(tileIndex >= 0 && tileIndex < MAP_TILES)   
		{  

			// Debris.. 
			if(tiles[tileIndex] >= 0 && tiles[tileIndex] < 16) 
			if(rand()%32 == 0)
			{ 
				midX = -map_startX + ( ((float)j * 0.1f) ); // -5.0, 0.1
				midY = -map_startY + ( ((float)i * 0.1f) ); // -5.0, 0.1 
				CreateObject(midX, midY, 0.1f, 0.2f, 4, 4+rand()%4, 13, OBJ, OBJ_NONE);
			}				    
			// Tree...     
			if(tiles[tileIndex] == 79)      
			{ 
				midX = -map_startX + ( ((float)j * 0.1f) - 0.4f ); // -5.0, 0.1
				midY = -map_startY + ( ((float)i * 0.1f) + 0.07f ); // -5.0, 0.1 
				CreateObject(midX, midY, 0.8f, 0.8f, 2, rand()%2, 12, OBJ, OBJ_NONE);
			} 
			   
			if(tiles[tileIndex] == 90)          
			if( (tileIndex+MAP_WIDTH) >= 0 && (tileIndex+MAP_WIDTH) < MAP_TILES)
			if(tiles[tileIndex+MAP_WIDTH] != 72 && tiles[tileIndex+MAP_WIDTH] != 73)
			if(map_col[(tileIndex+MAP_WIDTH)-1] != 0)
				tiles[tileIndex+MAP_WIDTH] = 416; 
			 
			if(tiles[tileIndex] == 91)
			if( (tileIndex+MAP_WIDTH) >= 0 && (tileIndex+MAP_WIDTH) < MAP_TILES)
			if(tiles[tileIndex+MAP_WIDTH] != 72 && tiles[tileIndex+MAP_WIDTH] != 73)
			if(map_col[tileIndex+MAP_WIDTH+1] != 0)
				tiles[tileIndex+MAP_WIDTH] = 417;			     
		 
			if(tiles[tileIndex] == 81) 
			if( (tileIndex+MAP_WIDTH+1) >= 0 && (tileIndex+MAP_WIDTH+1) < MAP_TILES)
			if(map_col[tileIndex+MAP_WIDTH+1] != 0)
				tiles[tileIndex+MAP_WIDTH] = 417; 
			        
			if(tiles[tileIndex] == 62) 
			if( ((tileIndex+MAP_WIDTH)-1) >= 0 && ((tileIndex+MAP_WIDTH)-1) < MAP_TILES)
			if(map_col[(tileIndex+MAP_WIDTH)-1] != 0) 
				tiles[tileIndex+MAP_WIDTH] = 416;    
			              
			if(tiles[tileIndex] == 57 || tiles[tileIndex] == 93)     // Top left/right tiles...
			if( ((tileIndex+MAP_WIDTH)+1) >= 0 && ((tileIndex+MAP_WIDTH)+1) < MAP_TILES)
			if(tiles[(tileIndex+MAP_WIDTH)+1] == 36 || tiles[(tileIndex+MAP_WIDTH)+1] == 64 || tiles[(tileIndex+MAP_WIDTH)+1] == 70 || tiles[(tileIndex+MAP_WIDTH)+1] == 66)
				tiles[tileIndex+MAP_WIDTH] = 419; 
			     
			if(tiles[tileIndex] == 54 || tiles[tileIndex] == 92)     // Top left/right tiles...
			if( ((tileIndex+MAP_WIDTH)-1) >= 0 && ((tileIndex+MAP_WIDTH)-1) < MAP_TILES)
			if(tiles[(tileIndex+MAP_WIDTH)-1] == 37 || tiles[(tileIndex+MAP_WIDTH)-1] == 47 || tiles[(tileIndex+MAP_WIDTH)-1] == 69 || tiles[(tileIndex+MAP_WIDTH)-1] == 67) 
				tiles[tileIndex+MAP_WIDTH] = 418;
			 
			if(tiles[tileIndex] == 50 || tiles[tileIndex] == 82 || tiles[tileIndex] == 86 || tiles[tileIndex] == 60)  // top edge of top tiles...           
			if( ((tileIndex+MAP_WIDTH)-1) >= 0 && ((tileIndex+MAP_WIDTH)-1) < MAP_TILES)
			if(tiles[(tileIndex+MAP_WIDTH)-1] == 41 || tiles[(tileIndex+MAP_WIDTH)-1] == 45 || tiles[(tileIndex+MAP_WIDTH)-1] == 77 || tiles[(tileIndex+MAP_WIDTH)-1] == 73) 
			{
				tiles[tileIndex-1] = 420;       

				if( (tileIndex-2) >= 0 && (tileIndex-2) < MAP_TILES)
				if(tiles[tileIndex-2] == 62)
					tiles[tileIndex-1] = 422;   
			}
			         
			if(tiles[tileIndex] == 51 || tiles[tileIndex] == 83 || tiles[tileIndex] == 85 || tiles[tileIndex] == 59)  // top edge of top tiles...       
			if( ((tileIndex+MAP_WIDTH)+1) >= 0 && ((tileIndex+MAP_WIDTH)+1) < MAP_TILES)
			if(tiles[(tileIndex+MAP_WIDTH)+1] == 38 || tiles[(tileIndex+MAP_WIDTH)+1] == 42 || tiles[(tileIndex+MAP_WIDTH)+1] == 76 || tiles[(tileIndex+MAP_WIDTH)+1] == 72) 
			{
				tiles[tileIndex+1] = 421;    
				  
				if( (tileIndex+2) >= 0 && (tileIndex+2) < MAP_TILES)
				if(tiles[tileIndex+2] == 81) 
					tiles[tileIndex+1] = 423;
			} 

		}  
		 
	} 
	 
	// Create some butterflies...
	if(sta2_is_epic_battle == true)
		index = 40;
	else
		index = 20;

	for(int i = 0;i <index;i++)      
	{   
		x = rand()%MAP_WIDTH;    
		y = rand()%MAP_HEIGHT;   

		midX = -map_startX + ( ((float)x * 0.1f)); // -5.0, 0.1
		midY = -map_startY + ( ((float)y * 0.1f)); // -5.0, 0.1 
		CreateObject(midX, midY, 0.1f, 0.2f, 2, rand()%4, 13, OBJ, OBJ_BUTTERFLY);

	}


} 

int Proc_Get_Pixel_City(int pixel, int row_x, int row_y)
{ 
	int color=0;  
	int i=0, j=0; 
	int tile_y=0;
	int black_color = 12;    
	float division=0.0f;  
	int roomX=0, roomY=0;   
	int index = 0;  
	float tempX = 0.0f;
	int my_row_x=0, my_row_y=0;  
	int frameX = 0, frameY = 0;

	if(row_x >= 50 && row_x <= 460 && row_y >= 36) // Here row_x is the X pixel, and y the y pixel... 
	{ 
		 
		my_row_x = row_x;    
		my_row_y = row_y;     

		my_row_x -= 50; // 0 - 410       
		my_row_y -= 36; // 0 - 220      

		// one tile is 410 / 50 = 8.2, 220 / 50 = 4.4...  
		        
		division = (((float)MAP_HEIGHT/2.0f) / 220.0f);         
		my_row_y = (int)((float)my_row_y * (float)division);  
		   
		division = (((float)MAP_WIDTH/2.0f) / 410.0f);             
		my_row_x = (int)((float)my_row_x * (float)division);  

		sta2_colorR = 100;sta2_colorG = 100;sta2_colorB = 100;

		if(my_row_x != sta2_old_roomX)               
		{   
			sta2_pixelX = 0; 
		}   

		if(room[my_row_y][my_row_x] >= CY_ROOM_FULL)        
		{           
			frameX = 0;
			frameY = 1; 
			 
			if(room[my_row_y][my_row_x] == CY_ROOM_FULL){frameX = 0;frameY = 1;}
			if(room[my_row_y][my_row_x] == CY_ROOM_BUSH_UP){frameX = 1;frameY = 1;}
			if(room[my_row_y][my_row_x] == CY_ROOM_BUSH_DOWN){frameX = 2;frameY = 1;}
			if(room[my_row_y][my_row_x] == CY_ROOM_BUSH_LEFT){frameX = 3;frameY = 1;}
			if(room[my_row_y][my_row_x] == CY_ROOM_BUSH_RIGHT){frameX = 4;frameY = 1;}
			if(room[my_row_y][my_row_x] == CY_ROOM_BUSH_UPLEFT){frameX = 5;frameY = 1;}
			if(room[my_row_y][my_row_x] == CY_ROOM_BUSH_UPRIGHT){frameX = 6;frameY = 1;}
			if(room[my_row_y][my_row_x] == CY_ROOM_BUSH_DOWNLEFT){frameX = 7;frameY = 1;}
			if(room[my_row_y][my_row_x] == CY_ROOM_BUSH_DOWNRIGHT){frameX = 0;frameY = 2;}
			if(room[my_row_y][my_row_x] == CY_ROOM_BUSH_LEFTRIGHT){frameX = 1;frameY = 2;}
			if(room[my_row_y][my_row_x] == CY_ROOM_BUSH_ENDLEFT){frameX = 2;frameY = 2;}
			if(room[my_row_y][my_row_x] == CY_ROOM_BUSH_ENDRIGHT){frameX = 3;frameY = 2;}
			if(room[my_row_y][my_row_x] == CY_ROOM_BUSH_ENDUP){frameX = 4;frameY = 2;}
			if(room[my_row_y][my_row_x] == CY_ROOM_BUSH_ENDDOWN){frameX = 5;frameY = 2;}
			if(room[my_row_y][my_row_x] == CY_ROOM_BUSH_UPDOWN){frameX = 6;frameY = 2;}

			index = (sta2_pixelX+(18*frameX) + (144 * (sta2_pixelY+(frameY*10))) );  

			if( index < 32000) 
				sta2_colorR = sta2_detail[index][0];sta2_colorG = sta2_detail[index][1];sta2_colorB = sta2_detail[index][2];
		}
		if(room[my_row_y][my_row_x] >= CY_ROOM_ROAD_RIGHT && room[my_row_y][my_row_x] <= CY_ROOM_ROAD_CROSSR)
		{
			if(room[my_row_y][my_row_x] == CY_ROOM_ROAD_RIGHT){frameX = 0;frameY = 3;}
			if(room[my_row_y][my_row_x] == CY_ROOM_ROAD_UP){frameX = 1;frameY = 3;}
			if(room[my_row_y][my_row_x] == CY_ROOM_ROAD_RIGHT1){frameX = 2;frameY = 3;}
			if(room[my_row_y][my_row_x] == CY_ROOM_ROAD_RIGHT2){frameX = 3;frameY = 3;} 
			if(room[my_row_y][my_row_x] == CY_ROOM_ROAD_CROSS){frameX = 4;frameY = 3;}
			if(room[my_row_y][my_row_x] == CY_ROOM_ROAD_CROSSU){frameX = 5;frameY = 3;}
			if(room[my_row_y][my_row_x] == CY_ROOM_ROAD_CROSSD){frameX = 6;frameY = 3;}
			if(room[my_row_y][my_row_x] == CY_ROOM_ROAD_CROSSL){frameX = 7;frameY = 3;}
			if(room[my_row_y][my_row_x] == CY_ROOM_ROAD_CROSSR){frameX = 0;frameY = 4;}

			index = (sta2_pixelX+(18*frameX) + (144 * (sta2_pixelY+(frameY*10))) );  
			 
			if( index < 32000)
				sta2_colorR = sta2_detail[index][0];sta2_colorG = sta2_detail[index][1];sta2_colorB = sta2_detail[index][2];
		}
		if(room[my_row_y][my_row_x] >= CY_ROOM_HUT1 && room[my_row_y][my_row_x] <= CY_ROOM_HUT6)
		{
			if(room[my_row_y][my_row_x] == CY_ROOM_HUT1){frameX = 1;frameY = 4;} 
			if(room[my_row_y][my_row_x] == CY_ROOM_HUT2){frameX = 2;frameY = 4;}
			if(room[my_row_y][my_row_x] == CY_ROOM_HUT3){frameX = 3;frameY = 4;}
			if(room[my_row_y][my_row_x] == CY_ROOM_HUT4){frameX = 4;frameY = 4;}
			if(room[my_row_y][my_row_x] == CY_ROOM_HUT5){frameX = 5;frameY = 4;}
			if(room[my_row_y][my_row_x] == CY_ROOM_HUT6){frameX = 6;frameY = 4;}

			index = (sta2_pixelX+(18*frameX) + (144 * (sta2_pixelY+(frameY*10))) );  

			if( index < 32000)
				sta2_colorR = sta2_detail[index][0];sta2_colorG = sta2_detail[index][1];sta2_colorB = sta2_detail[index][2];
		}
		if(room[my_row_y][my_row_x] >= CY_ROOM_ROCK1 && room[my_row_y][my_row_x] <= CY_ROOM_ROCK4)
		{
			if(room[my_row_y][my_row_x] == CY_ROOM_ROCK1){frameX = 7;frameY = 4;} 
			if(room[my_row_y][my_row_x] == CY_ROOM_ROCK2){frameX = 7;frameY = 4;}
			if(room[my_row_y][my_row_x] == CY_ROOM_ROCK3){frameX = 7;frameY = 4;} 
			if(room[my_row_y][my_row_x] == CY_ROOM_ROCK4){frameX = 7;frameY = 4;}

			index = (sta2_pixelX+(18*frameX) + (144 * (sta2_pixelY+(frameY*10))) );  
			  
			if( index < 32000)
				sta2_colorR = sta2_detail[index][0];sta2_colorG = sta2_detail[index][1];sta2_colorB = sta2_detail[index][2];
		}  
		if(room[my_row_y][my_row_x] >= CY_ROOM_CRATER1 && room[my_row_y][my_row_x] <= CY_ROOM_CRATER4)
		{
			if(room[my_row_y][my_row_x] == CY_ROOM_CRATER1){frameX = 3;frameY = 5;} 
			if(room[my_row_y][my_row_x] == CY_ROOM_CRATER2){frameX = 4;frameY = 5;}
			if(room[my_row_y][my_row_x] == CY_ROOM_CRATER3){frameX = 5;frameY = 5;}
			if(room[my_row_y][my_row_x] == CY_ROOM_CRATER4){frameX = 6;frameY = 5;}

			index = (sta2_pixelX+(18*frameX) + (144 * (sta2_pixelY+(frameY*10))) );  

			if( index < 32000)
				sta2_colorR = sta2_detail[index][0];sta2_colorG = sta2_detail[index][1];sta2_colorB = sta2_detail[index][2];
		} 
		if(room[my_row_y][my_row_x] == CY_ROOM_TREE)
		{
			if(room[my_row_y][my_row_x] == CY_ROOM_TREE){frameX = 7;frameY = 2;} 

			index = (sta2_pixelX+(18*frameX) + (144 * (sta2_pixelY+(frameY*10))) );  

			if( index < 32000)
				sta2_colorR = sta2_detail[index][0];sta2_colorG = sta2_detail[index][1];sta2_colorB = sta2_detail[index][2];
		}
		if(room[my_row_y][my_row_x] == CY_ROOM_EMPTY)      
		{ 
			frameX = room_empty[my_row_y][my_row_x];
			frameY = 0; 

			index = (sta2_pixelX+(18*frameX) + (144 * (sta2_pixelY+(frameY*10))) );  

			if( index < 32000)
				sta2_colorR = sta2_detail[index][0];sta2_colorG = sta2_detail[index][1];sta2_colorB = sta2_detail[index][2];
		}
		if(row_x == 460)
		{
			sta2_pixelY++;
		}
		if(my_row_y != sta2_old_roomY) 
		{
			sta2_pixelY = 0;
		} 

		sta2_pixelX++;

		sta2_old_roomX = my_row_x;
		sta2_old_roomY = my_row_y;

	}
	else
		color = -1; 


	return(color);
	 
}

int Count_Tiles_City(int x, int y)
{ 
    int count = 0;
	int testX=0, testY=0;

	testY = y-1;
	testX = x;

	if(testY >= 0 && testX >= 0 && testX < (MAP_WIDTH/2) && testY < (MAP_HEIGHT/2))
	if(room[testY][testX] == CY_ROOM_FULL)
		count++;

	testY = y+1;
	testX = x;

	if(testY >= 0 && testX >= 0 && testX < (MAP_WIDTH/2) && testY < (MAP_HEIGHT/2))
	if(room[testY][testX] == CY_ROOM_FULL)
		count++;

	testY = y;
	testX = x+1;

	if(testY >= 0 && testX >= 0 && testX < (MAP_WIDTH/2) && testY < (MAP_HEIGHT/2))
	if(room[testY][testX] == CY_ROOM_FULL)
		count++;

	testY = y;
	testX = x-1;

	if(testY >= 0 && testX >= 0 && testX < (MAP_WIDTH/2) && testY < (MAP_HEIGHT/2))
	if(room[testY][testX] == CY_ROOM_FULL)
		count++;

	return(count);
     
} 