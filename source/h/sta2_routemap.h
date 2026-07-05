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

extern int Proc_Get_Pixel_Grass(int pixel, int row_x, int row_y);
extern int Proc_Get_Pixel_Forest(int pixel, int row_x, int row_y);
extern int Proc_Get_Pixel_Swamp(int pixel, int row_x, int row_y);
extern int Proc_Get_Pixel_Farm(int pixel, int row_x, int row_y);
extern int Proc_Get_Pixel_Desert(int pixel, int row_x, int row_y);
extern int Proc_Get_Pixel_Snow(int pixel, int row_x, int row_y);
extern int Proc_Get_Pixel_Trench(int pixel, int row_x, int row_y);
extern int Proc_Get_Pixel_City(int pixel, int row_x, int row_y);
extern void sta2_Proc_Level_Grass();
extern void sta2_Proc_Level_Forest(); 
extern void sta2_Proc_Level_Swamp();
extern void sta2_Proc_Level_Farm();
extern void sta2_Proc_Level_Desert();
extern void sta2_Proc_Level_Snow();
extern void sta2_Proc_Level_Trench();
extern void sta2_Proc_Level_City();
extern void sta2_Scroll(int number, bool startup, int f_rate, int direction);
 
void CreateObject(float x, float y, float width, float height, int priority, int anim, int id, int type, int obj_type);
void CreatePin(float x, float y, int first, int second, int third, int fourth, int type, int node_type);
void sta2_Proc_Route();
void sta2_Proc_Level();
int Proc_Get_Pixel(int pixel, int row_x, int row_y);
int Count_Tiles(int x, int y);
void sta2_Reduce_Tileset(int index, int valueX, int valueY, int radius);

#define TEST_ROUTE_MAP  0

void sta2_Proc_Level()
{ 
 
	if(sta2_environment_type == AREA_GRASSLANDS)
		sta2_Proc_Level_Grass();
	if(sta2_environment_type == AREA_FOREST) 
		sta2_Proc_Level_Forest();
	if(sta2_environment_type == AREA_SWAMP)
		sta2_Proc_Level_Swamp();
	if(sta2_environment_type == AREA_FARM)
		sta2_Proc_Level_Farm();

	if(sta2_environment_type == AREA_DESERT)
		sta2_Proc_Level_Desert();
	if(sta2_environment_type == AREA_SNOW)
		sta2_Proc_Level_Snow();
	if(sta2_environment_type == AREA_BEACH)
		sta2_Proc_Level_Desert();
	if(sta2_environment_type == AREA_MOUNTAIN)
		sta2_Proc_Level_Snow();
	if(sta2_environment_type == AREA_CITY)
		sta2_Proc_Level_City();
	if(sta2_environment_type == AREA_TRENCH)
		sta2_Proc_Level_Trench();

	if(sta2_environment_type == AREA_CASTLE)
		sta2_Proc_Level_Forest();


}

void sta2_Proc_Route()
{
	int tileX=2;
	int tileY=2;
	int temp_tileX=2;
	int temp_tileY=2;
	int tileIndex=0;
	int rnd=0;
	float this_map_startX=0.0f;  
	float this_map_startY=0.0f;
	int last=0;
	int next=0;
	int spine_node=0;
	int incoming_line = 0;
	int outgoing_line = 0;
	int line_length = 100; 
	int count_no_pins=0; 
	int last_count_no_pins=0;
	int index=0;
	int nodeX[100]; 
	int nodeY[100];
	int nodeN[100];
	int nodeL[100];
	int nodeT[100];
	bool blocked=false;
    float deltax=0.0f, deltay=0.0f;   
    float mid_x=0.0f, mid_y=0.0f;   
    float tar_x=0.0f, tar_y=0.0f;
	float angle=0.0f, distance = 0.0f; 
	float frnd=0.0f;
	int row_x=0, row_y=0;
	int step_inc=0;
	int testTileIndex=0;
//	int tilecol[10];
	bool has_no_connections=false;
//	int room[4][16];
	int rnd1=0, rnd2=0, rnd3=0;
	int bug_no_connections = 0;
	int connected_to=0;
	 
	if(sta2_route_create_pins == true)
	for(int i=0;i<256;i++)   
		sta2_tiles[i]=0;

	tileY = 1+rand()%7; 

    this_map_startX = (STA2_ROUTE_MAP_WIDTH*TileSize)/2;  // 1.6
    this_map_startY = (STA2_ROUTE_MAP_HEIGHT*TileSize)/2; // 0.4

	// Recreate pins and map from load file...
	if(sta2_route_create_pins == false)   
	{  
		sta2_route_start_pin = no_sprites;

		for(int i=0;i<no_of_route_pins;i++)  
		{ 
			CreatePin(map_pinsR_x[i],  map_pinsR_y[i], map_pinsR_link_1[i], map_pinsR_link_2[i], map_pinsR_link_3[i],map_pinsR_link_4[i], map_pinsR_type[i], map_pinsR_type2[i]);
		}

	}

	if(sta2_route_create_pins == true)   
	for(int j = 0; j<line_length;j++)   
	{

		// Create our first pin...   
		 
		rnd = rand()%5;

		if(tileY == 1)
			rnd = 2 + rand()%3; 
		if(tileY == 6)
			rnd = 0 + rand()%3;   

		if(rnd == 0)
			tileY -= 1;  
		if(rnd == 1)
			tileY -= 2;    
		if(rnd == 3)
			tileY += 1;   
		if(rnd == 4) 
			tileY += 2;      
		   
		if(tileY <= 1)  
			tileY = 1;
		if(tileY>=6) 
			tileY = 6; 

		tileIndex = (tileY*STA2_ROUTE_MAP_WIDTH)+tileX;

		if(tileIndex >= 0 && tileIndex < 256) 
			sta2_tiles[tileIndex] = 1;    
		 
		// Reset first pin... 
		if(j==0)      
			sta2_route_start_pin = no_sprites;  

		last = no_sprites-1;
		  
		next = no_sprites+1; 

		if(j == 0) 
			last = 0; 

		map_pinsR_x[count_no_pins] = -this_map_startX + (( (float)tileX*(0.1f)) );
		map_pinsR_y[count_no_pins] = -this_map_startY + (( (float)tileY*(0.1f)) );
		map_pinsR_link_1[count_no_pins] = next;
		map_pinsR_link_2[count_no_pins] = last;  
		map_pinsR_link_3[count_no_pins] = 0;  
		map_pinsR_link_4[count_no_pins] = 0;

		if(TEST_ROUTE_MAP == 0)
			map_pinsR_type[count_no_pins] = FE_TYPE1; 
		if(TEST_ROUTE_MAP == 1)
			map_pinsR_type[count_no_pins] = FE_TYPE3; 

		map_pinsR_type2[count_no_pins] = STA2_SPINE_NODE;

		nodeX[count_no_pins] = tileX;
		nodeY[count_no_pins] = tileY;  
		nodeN[count_no_pins] = next;
		nodeL[count_no_pins] = last;
		nodeT[count_no_pins] = no_sprites;

		CreatePin(map_pinsR_x[count_no_pins],  map_pinsR_y[count_no_pins], map_pinsR_link_1[count_no_pins], map_pinsR_link_2[count_no_pins], map_pinsR_link_3[count_no_pins],map_pinsR_link_4[count_no_pins], map_pinsR_type[count_no_pins], STA2_SPINE_NODE);


	//	rnd = rand()%20;          
		 
	//	if(rnd <= 18)      
			tileX+=2;   
	//	if(rnd == 19)    
	//		tileX+=1;
		  
		count_no_pins++;

		if(tileX > 28)   
		{
			map_pinsR_type[count_no_pins-1] = FE_TYPE2;
			sprite[no_sprites-1].type = FE_TYPE2;
			break;  
		}
		 
	}  

	// Create secondary routes... 
	if(sta2_route_create_pins == true)       
	{

		for(int k=0;k<11;k++)        
		{  
			 
		tileY = 1 + rand()%6;   
		tileX = 2 + rand()%27;    

		blocked = false; 

		// Make blank if any tiles nearby within 1 tile radius...
		for(int y = -1;y<2;y++)   
		for(int x = -1;x<2;x++) 
		{
			temp_tileX = tileX + x; 
			temp_tileY = tileY + y; 
			 
			if(temp_tileX < 0)temp_tileX=0;
			if(temp_tileX > 31)temp_tileX=31;
			if(temp_tileY < 0)temp_tileY=0;
			if(temp_tileY > 7)temp_tileY=7;

			tileIndex = (temp_tileY*STA2_ROUTE_MAP_WIDTH)+temp_tileX;

			if(tileIndex >= 0 && tileIndex < 256)
			if(sta2_tiles[tileIndex] != 0)
				blocked = true;
		}

		if(blocked == false)  
		{

			tileIndex = (tileY*STA2_ROUTE_MAP_WIDTH)+tileX; 

			if(tileIndex >= 0 && tileIndex < 256)       
				sta2_tiles[tileIndex] = 1;          

			map_pinsR_x[count_no_pins] = -this_map_startX + (( (float)tileX*(0.1f)) );
			map_pinsR_y[count_no_pins] = -this_map_startY + (( (float)tileY*(0.1f)) );
			map_pinsR_link_1[count_no_pins] = 0; 
			map_pinsR_link_2[count_no_pins] = 0;  
			map_pinsR_link_3[count_no_pins] = 0;  
			map_pinsR_link_4[count_no_pins] = 0;  

			if(TEST_ROUTE_MAP == 0)
				map_pinsR_type[count_no_pins] = FE_TYPE1; 
			if(TEST_ROUTE_MAP == 1)
				map_pinsR_type[count_no_pins] = FE_TYPE3; 

			map_pinsR_type2[count_no_pins] = STA2_SPINE_NODE; 

			nodeX[count_no_pins] = tileX; 
			nodeY[count_no_pins] = tileY; 
			nodeN[count_no_pins] = 0; 
			nodeL[count_no_pins] = 0;
			nodeT[count_no_pins] = 0;

			CreatePin(map_pinsR_x[count_no_pins],  map_pinsR_y[count_no_pins], map_pinsR_link_1[count_no_pins], map_pinsR_link_2[count_no_pins], map_pinsR_link_3[count_no_pins],map_pinsR_link_4[count_no_pins], map_pinsR_type[count_no_pins], STA2_SPINE_NODE);

			count_no_pins++; 
		}
		 
		} // End of K loop...   

	}// sta2_route_create_pins == true)         
	  
	bug_no_connections = 0;

	// Fix for bug where there are two nodes alone...
	for(int i  = sta2_route_start_pin;i<no_sprites;i++) 
	if(sprite[i].type != NON)
	{ 
		mid_x = sprite[i].x+sprite[i].width/2;     
		mid_y = sprite[i].y+sprite[i].height/2; 
		
		bug_no_connections=0; 

		for(int j  = sta2_route_start_pin;j<no_sprites;j++) 
		if(i != j)
		if(sprite[j].type != NON)
		{
			tar_x = sprite[j].x+sprite[j].width/2;  
			tar_y = sprite[j].y+sprite[j].height/2;  

			distance = Node_Distance1(mid_x, mid_y, tar_x, tar_y);
		 
			if(distance <= prox_distance)       
			{
				connected_to = j;
				bug_no_connections++;
			}

		}

		if(bug_no_connections == 1) 
		{
			bug_no_connections=0; 
			 
			mid_x = sprite[connected_to].x+sprite[connected_to].width/2;     
			mid_y = sprite[connected_to].y+sprite[connected_to].height/2; 

			for(int k  = sta2_route_start_pin;k<no_sprites;k++) 
			if(connected_to != k) 
			if(sprite[k].type != NON)
			{
				tar_x = sprite[k].x+sprite[k].width/2;  
				tar_y = sprite[k].y+sprite[k].height/2;  

				distance = Node_Distance1(mid_x, mid_y, tar_x, tar_y);
		 
				if(distance <= prox_distance)        
				{
					bug_no_connections++;       
				}

			}

			if(bug_no_connections == 1)
			{
				sprite[connected_to].type = NON;
				sprite[connected_to].alpha = 0.0f;
			}

		}


	}


	// Create Lines data... 
	sta2_lines_count = 0;   

	for(int i  = sta2_route_start_pin;i< no_sprites;i++) 
	if(sprite[i].type != NON)
	{ 
		mid_x = sprite[i].x+sprite[i].width/2;    
		mid_y = sprite[i].y+sprite[i].height/2; 
		
		has_no_connections=true;

		for(int j  = sta2_route_start_pin;j< no_sprites;j++) 
		if(i != j)
		if(sprite[j].type != NON)
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

	} // End i loop... 
	 
}

void CreatePin(float x, float y, int first, int second, int third, int fourth, int type, int node_type)
{

	    sprite[no_sprites].status = node_type;

		sprite[no_sprites].id = 11;   

		sprite[no_sprites].light = 1.0f; 
					  
		sprite[no_sprites].priority = 2;

		sprite[no_sprites].fx_id = animation_fx[sprite[no_sprites].id];

		sprite[no_sprites].depth = 0.0f; 

		sprite[no_sprites].sector = first;
		sprite[no_sprites].sector_action = second;
		sprite[no_sprites].rank = third;
		sprite[no_sprites].onCreate = fourth;
				    
		sprite[no_sprites].x = x;   
		sprite[no_sprites].y = y;    
		sprite[no_sprites].w = x;  
		sprite[no_sprites].z = y;  

		sprite[no_sprites].width = 0.1f;  
		sprite[no_sprites].height = 0.1f; 
		sprite[no_sprites].box_width = 0.1f;  
		sprite[no_sprites].box_height = 0.1f;   

		sprite[no_sprites].alpha = 1.0f;  
		 
		sprite[no_sprites].type = type;

		sprite[no_sprites].mouseover = false;   
				    
		sprite[no_sprites].turn_off = false;    
		 
		sprite[no_sprites].anim = 5;   

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


bool Run_Routemap(int f_rate)
{  
	bool success=true;
	float testX=0.0f, testY=0.0f;  
	float midX=0.0f, midY=0.0f;
	float incY=0.0f;
	int rnd=0;
	int index=0;
	float tar_x=0.0f, tar_y=0.0f;
    float cam_x =0.0, cam_y =0.0;
    float deltax =0.0,deltay =0.0; 
    float distance=0.0f;
    float mid_x=0.0f, mid_y=0.0f;
	int rations_gain=0;
	int targetA = 0;
	int targetB = 0;
	int targetC = 0;
	int targetD = 0; 
	int script_damage=0; 
    float angle = 0.0;       
	char string_value[1024]; 
	int slongest_line=0;

	bool sta2_rising = false;


    // ******************************************************************************//
    //                            1-0  (ROUTE MAP SCREEN)                            //
    // ******************************************************************************//	      

       // Route Map...   // 9 - Snow // 10 - Grasslands // 11 - Forest // 12 == Swamp // 13 == Farms // 21 == Castle
       if(!mode)  
       if(next_scene == false)  
       if(episode == 1 && scene == 28)                       
       {       
		    
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

		//    SwipeCode(f_rate); 

		    // C.O pins...  
		    if(sta2_co_type == STA2_CO_ADA)
				Set_Sprite(2, 70, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
		    if(sta2_co_type == STA2_CO_MARIE)
				Set_Sprite(2, 71, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
		    if(sta2_co_type == STA2_CO_ADELE)
				Set_Sprite(2, 72, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
		    if(sta2_co_type == STA2_CO_BELLA)
				Set_Sprite(2, 73, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 

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
			   index = 3;
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

		   sprintf( new_counter[3].word, "HP %i/%i SECTOR %i^%f", sta2_squad_current_health, sta2_squad_total_health, sta2_sector); 

		   new_counter[3].alpha = 0.0f; // Hack  

		   sta2_squad_total_health = 0; 
	
		   sprintf( new_counter[4].word, "1. Squad");  

			if(sta2_scroll_route_map == false)
				new_counter[4].alpha = 1.0f;                 
			else
				new_counter[4].alpha = 0.0f; 

		   new_counter[4].id = 0; 

		    sprintf( new_counter[5].word, "2. Investigate");

			new_counter[5].alpha = 0.0f;  

		    new_counter[5].id = 0;
			
			sprintf( new_counter[6].word, "3. Quit");  

			if(sta2_scroll_route_map == false)
				new_counter[6].alpha = 1.0f;                 
			else
				new_counter[6].alpha = 0.0f;                 
			 
			new_counter[6].id = 0;  

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
			   if(sta2_squad[i].health > 0)
				   sta2_squad_current_health += sta2_squad[i].health;   
			   if(sta2_squad[i].health > 0) 
				   sta2_squad_alive_count++;        
		   }   

		   sta2_squad_bar_width = hud[63].box_width * (float)( (float)sta2_squad_current_health / (float)sta2_squad_total_health);
			
		   if(title_sequence != 0) 
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

				sta2_only_defend = true;
				sta2_only_pistol = true;
				sta2_only_grenade = true;

			    if(sta2_squad_count >= 9)
			    {
			   		#if IS_FULL_STEAM == 1 

					if(STEAM_ACTIVE == true)  
					if(IS_FULL_GAME == true)
					if (g_SteamAchievements)
					{
						g_SteamAchievements->SetAchievement("STA2_MEDAL_12"); // Have nine team members on your squad...
						if(sta2_globals[GLOBAL_STA2_MEDAL_12] == GLOBALS_RESET)
						{
							sta2_globals[GLOBAL_STA2_MEDAL_12] = GLOBALS_ACTIVE;
							firework_sfx = true;

						}
					}

					#endif
			    }
			    if(sta2_food >= 1500)
			    {
			   		#if IS_FULL_STEAM == 1  

					if(STEAM_ACTIVE == true)  
					if(IS_FULL_GAME == true)
					if (g_SteamAchievements)
					{
						g_SteamAchievements->SetAchievement("STA2_MEDAL_18"); // Have over 1500Food at one time...
						if(sta2_globals[GLOBAL_STA2_MEDAL_18] == GLOBALS_RESET)
						{
							sta2_globals[GLOBAL_STA2_MEDAL_18] = GLOBALS_ACTIVE;
							firework_sfx = true;

						}
					}


					#endif
			    }
			    if(sta2_gold >= 1500)
			    {
			   		#if IS_FULL_STEAM == 1 

					if(STEAM_ACTIVE == true)  
					if(IS_FULL_GAME == true)
					if (g_SteamAchievements)
					{
						g_SteamAchievements->SetAchievement("STA2_MEDAL_19"); // Have over 1500Gold at one time...
						if(sta2_globals[GLOBAL_STA2_MEDAL_19] == GLOBALS_RESET)
						{
							sta2_globals[GLOBAL_STA2_MEDAL_19] = GLOBALS_ACTIVE;
							firework_sfx = true;

						}
					}

					#endif
			    }

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

			    sprintf( new_counter[3].word, "SQUAD : %i/%i^SECTOR : %i", sta2_squad_current_health, sta2_squad_total_health, sta2_sector); 
			//	sta2_Scroll(3, true, f_rate, RIGHT);

			    new_counter[4].id = 0; 
		      
			    new_counter[4].x = -0.60f;      
			    new_counter[4].y = -0.34f;  	       

				new_counter[4].w = new_counter[4].x - 0.026f;   
				new_counter[4].z = new_counter[4].y - 0.015f;

				new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
				new_counter[4].box_height = new_counter[4].height - 0.015f;	

				sprintf( new_counter[4].word, "1. Squad");
				sta2_Scroll(4, true, f_rate, RIGHT);

				new_counter[5].id = 0;   
		     
				new_counter[5].x = -0.155f;       
				new_counter[5].y = -0.34f;  	      

				new_counter[5].w = new_counter[5].x - 0.026f;   
				new_counter[5].z = new_counter[5].y - 0.015f;

				new_counter[5].box_width = strlen(new_counter[5].word)   *  0.026f;
				new_counter[5].box_height = new_counter[5].height - 0.015f;	

				sprintf( new_counter[5].word, "2. Investigate"); 
				sta2_Scroll(5, true, f_rate, UP);

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

				sprintf( new_counter[6].word, "3. Quit");
				sta2_Scroll(6, true, f_rate, LEFT);

			    sta2_is_general_fight = false;  

				if(sta2_move_general == true)  
				if(sta2_sector != 7 && sta2_sector != 8)
					sta2_general_position += sprite[4].width / 20; 

				sprite[4].x = (sprite[4].x - sprite[4].width - (sprite[4].width / 20)) + sta2_general_position;

				sta2_move_general = false;   

				sta2_Proc_Route();

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

						hud_63_old_width = hud[63].width;

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
				   sta2_current_pin = sta2_route_start_pin;
				   sta2_route_create_pins = false;  
				    
				   no_of_route_pins = 0;        
				    
				   // Setup pins... 
				   for(int i = 0;i < no_sprites;i++)       
				   {  

					   if(sprite[i].type >= FE_TYPE1 && sprite[i].type <= FE_TYPE8)
					   {    
   
						   rnd = rand()%100;                   

						   if(rnd >= 0 && rnd < 6)         
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_BRIBE;  
						   if(rnd >= 6 && rnd < 36)     
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_BATTLE; 
						   if(rnd >= 36 && rnd < 48)  
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_STORE;   
						   if(rnd >= 48 && rnd < 50)
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_CHANCE;
						   if(rnd >= 50 && rnd < 55) 
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_HUNT; 		 				    
						   if(rnd >= 55 && rnd < 60)   
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_GAMBLE;
						   if(rnd >= 60 && rnd < 65)  
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_EMPTY;
						   if(rnd >= 65 && rnd < 75)     
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_TRADE; 
						   if(rnd >= 75 && rnd < 78) 
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_OBSTACLE;
						   if(rnd >= 78 && rnd < 81)
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_WIZARD;
						   if(rnd >= 81 && rnd < 100)
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_CHANCE; 

						   if(sprite[i].type == FE_TYPE2)  
						   {
							   if(sta2_playing_tutorial == true)
								   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_SECTOR_GO;
							   else
								   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_BOSS;
						   }
						   if(sprite[i].type == FE_TYPE3)
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_EMPTY;
						   if(sprite[i].type == FE_TYPE4)
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_CHANCE;
						   if(sprite[i].type == FE_TYPE5)
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_STORE;
						   if(sprite[i].type == FE_TYPE6)
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_BATTLE;
						   if(sprite[i].type == FE_TYPE7)
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_BATTLE_TUTORIAL;
						   if(sprite[i].type == FE_TYPE8)
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_HUNT; 
							 
						   if(i == sta2_route_start_pin)    
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_DONE;  

						   if(sta2_environment_type == AREA_CITY || sta2_environment_type == AREA_TRENCH)
						   if(map_pins[sta2_route_start_pin+no_of_route_pins] == EVENT_HUNT)
							   map_pins[sta2_route_start_pin+no_of_route_pins] = EVENT_GAMBLE;

						   sprite[i].value2 = map_pins[sta2_route_start_pin+no_of_route_pins];
						   sprite[i].value3 = sta2_route_start_pin+no_of_route_pins;

							no_of_route_pins++;
					   } 

				   }           
				        
			   } // sta2_route_create_pins == true)         

			   // Calculate value3 for pins...  
			   no_of_route_pins = 0;      

			   for(int i = 0;i < no_sprites;i++)       
			   if(sprite[i].type >= FE_TYPE1 && sprite[i].type <= FE_TYPE8)
			   {    

					sprite[i].value3 = sta2_route_start_pin+no_of_route_pins;
					    
					no_of_route_pins++;
			   } 
			    
			   // Create general pins... 
			   for(int i = 0;i < no_sprites;i++)            
			   {  
					if(sprite[i].type >= FE_TYPE1 && sprite[i].type <= FE_TYPE8)
					if(sprite[i].x <= ((sprite[4].x + (sprite[4].width*0.98) )))
					if(map_pins[sprite[i].value3] != EVENT_BOSS && map_pins[sprite[i].value3] != EVENT_SECTOR_GO) 
					{    
						map_pins[sprite[i].value3] = EVENT_GENERAL; 
					}
			    }
			       
				// Setup pin anims...   
				for(int i = 0;i < no_of_route_pins;i++)      
				{ 
					sprite[sta2_route_start_pin+i].base_anim = 5;  // grey  
					 
					if(map_pins[sta2_route_start_pin+i] == EVENT_DONE)
						sprite[sta2_route_start_pin+i].base_anim = 10; // black
					if(map_pins[sta2_route_start_pin+i] == EVENT_BOSS || map_pins[sta2_route_start_pin+i] == EVENT_SECTOR_GO)
						sprite[sta2_route_start_pin+i].base_anim = 16;  // purple 
					if(map_pins[sta2_route_start_pin+i] == EVENT_STORE)
						sprite[sta2_route_start_pin+i].base_anim = 17;  // purple
					if(map_pins[sta2_route_start_pin+i] == EVENT_GENERAL)
						sprite[sta2_route_start_pin+i].base_anim = 19;  // purple
				//	if(map_pins[3+i] == EVENT_HUNT)
				//		sprite[3+i].base_anim = 18;  // game
				//	if(map_pins[3+i] == EVENT_GAMBLE)
				//		sprite[3+i].base_anim = 18;  // game  
					  
					sprite[sta2_route_start_pin+i].value2 = map_pins[sta2_route_start_pin+i];

					sprite[sta2_route_start_pin+i].anim = sprite[sta2_route_start_pin+i].base_anim;

					Set_Sprite(sta2_route_start_pin+i, sprite[sta2_route_start_pin+i].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING);
					 
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
			    
			   Animate(-1, -1); 

			   // Save the level after everything has been setup...
				if(sta2_playing_tutorial == false)  
				{
					sprintf( temp_string.string, "data/save/sta2");
					STA2_SaveLevel(temp_string);
				}	 
          
           }    // title_sequence == 0   

		//   sta2_Scroll(2, false, f_rate, LEFT);  // GOLD
		//   sta2_Scroll(3, false, f_rate, RIGHT);  // SQUAD
		   sta2_Scroll(4, false, f_rate, RIGHT); // SQUAD
		   sta2_Scroll(5, false, f_rate, UP);  // INVEST
		   sta2_Scroll(6, false, f_rate, LEFT);  // QUIT

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

							hud_63_old_width = hud[63].width;

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

						hud_63_old_width = hud[63].width;

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

			   sta2_route_selected_pin = -1;

			   new_counter[9].alpha  = 0.0f;  
			   new_counter[10].alpha = 0.0f;  
			   sprintf( new_counter[9].word, "");
			   sprintf( new_counter[10].word, "");

			   for(int i = 0;i < no_sprites;i++)           
			   { 

				   if(sprite[i].type >= FE_TYPE1 && sprite[i].type <= FE_TYPE8)
				       Set_Sprite(i, sprite[i].base_anim, LOOP, ANIM_SPRITE, ANIM_WALKING);

				   if(sta2_yes_no_active == false)
				   if(sprite[i].type >= FE_TYPE1 && sprite[i].type <= FE_TYPE8)
				   if(sprite[i].alpha == 1.0f)                   
				   if(( mouseX < (sprite[i].w + sprite[i].box_width) )
				   &&( mouseX > sprite[i].w)                            
				   &&( mouseY < (sprite[i].z + sprite[i].box_height) )
				   &&( mouseY > sprite[i].z))   
				   {      

					    sta2_route_selected_pin = i; 

						Set_Sprite(i, 0, LOOP, ANIM_SPRITE, ANIM_WALKING);  				

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

								IsSquadAlive(); // Get no of guys left alive...Stores in sta2_squad_alive_count

								if(sta2_food_rations == RATIONS_LOW) // 2%
									rations_gain = 4;
								if(sta2_food_rations == RATIONS_MID) // 5%
									rations_gain = 5; 
								if(sta2_food_rations == RATIONS_HIGH) // 6%
									rations_gain = 7;
								if(sta2_food_rations == RATIONS_MEGA) // 10% 
									rations_gain = 15;
								 
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

							hud_63_old_width = hud[63].width;

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
						|| sta2_next_event == EVENT_GENERAL
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
					if(sta2_next_event == EVENT_BATTLE || sta2_next_event == EVENT_BATTLE_TUTORIAL || sta2_next_event == EVENT_BOSS || sta2_next_event == EVENT_SECTOR_GO || sta2_next_event == EVENT_OBSTACLE || sta2_next_event == EVENT_WIZARD || sta2_next_event == EVENT_BRIBE || sta2_next_event == EVENT_GENERAL) 
					{
						if(sta2_next_event == EVENT_OBSTACLE) 
							New_FX(sprite[2].x, sprite[2].z+0.05f,  sprite[2].x, sprite[2].y-0.0001f, 85, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
						else
							New_FX(sprite[2].x, sprite[2].z+0.05f,  sprite[2].x, sprite[2].y-0.0001f, 56, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);

						stolen_sfx = true;
					}
					else
					{
						if(TEST_ROUTE_MAP == 0)
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

				hud_63_old_width = hud[63].width; 

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

       }  // episode == 1 && scene == 28...

	     
	return(success);
}


void CreateObject(float x, float y, float width, float height, int priority, int anim, int id, int type, int obj_type)
{

	    sprite[no_sprites].status = 0;  

		sprite[no_sprites].sector_action = obj_type; 

		sprite[no_sprites].id = id;   

		sprite[no_sprites].light = 1.0f; 
					  
		sprite[no_sprites].priority = priority;

		sprite[no_sprites].fx_id = animation_fx[sprite[no_sprites].id];

		sprite[no_sprites].depth = 0.0f; 
				    
		sprite[no_sprites].x = x;   
		sprite[no_sprites].y = y;    
		sprite[no_sprites].w = x;  
		sprite[no_sprites].z = y;  

		sprite[no_sprites].width = width;  
		sprite[no_sprites].height = height; 
		sprite[no_sprites].box_width = width;  
		sprite[no_sprites].box_height = height;   

		sprite[no_sprites].alpha = 1.0f;  
		 
		sprite[no_sprites].type = type;

		sprite[no_sprites].mouseover = false;   
				    
		sprite[no_sprites].turn_off = false;    
		 
		sprite[no_sprites].anim = anim;   

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

int Proc_Get_Pixel(int pixel, int row_x, int row_y)
{ 
	int return_color=0;  

	if(sta2_environment_type == AREA_GRASSLANDS)
		return_color = Proc_Get_Pixel_Grass(pixel, row_x, row_y);
	if(sta2_environment_type == AREA_FOREST) 
		return_color = Proc_Get_Pixel_Forest(pixel, row_x, row_y);
	if(sta2_environment_type == AREA_SWAMP)
		return_color = Proc_Get_Pixel_Swamp(pixel, row_x, row_y);
	if(sta2_environment_type == AREA_FARM)
		return_color = Proc_Get_Pixel_Farm(pixel, row_x, row_y);

	if(sta2_environment_type == AREA_DESERT)
		return_color = Proc_Get_Pixel_Desert(pixel, row_x, row_y);
	if(sta2_environment_type == AREA_SNOW)
		return_color = Proc_Get_Pixel_Snow(pixel, row_x, row_y);
	if(sta2_environment_type == AREA_BEACH)
		return_color = Proc_Get_Pixel_Desert(pixel, row_x, row_y);
	if(sta2_environment_type == AREA_MOUNTAIN)
		return_color = Proc_Get_Pixel_Snow(pixel, row_x, row_y);
	if(sta2_environment_type == AREA_CITY)
		return_color = Proc_Get_Pixel_City(pixel, row_x, row_y);
	if(sta2_environment_type == AREA_TRENCH)
		return_color = Proc_Get_Pixel_Trench(pixel, row_x, row_y);

	if(sta2_environment_type == AREA_CASTLE)
		return_color = Proc_Get_Pixel_Forest(pixel, row_x, row_y);


	return(return_color);
	 
}

int Count_Tiles(int x, int y)
{ 
    int count = 0;
	int testX=0, testY=0;

	testY = y-1;
	testX = x;

	if(testY >= 0 && testX >= 0 && testX < (MAP_WIDTH/2) && testY < (MAP_HEIGHT/2))
	if(room[testY][testX] == GR_ROOM_FULL)
		count++;

	testY = y+1;
	testX = x;

	if(testY >= 0 && testX >= 0 && testX < (MAP_WIDTH/2) && testY < (MAP_HEIGHT/2))
	if(room[testY][testX] == GR_ROOM_FULL)
		count++;

	testY = y;
	testX = x+1;

	if(testY >= 0 && testX >= 0 && testX < (MAP_WIDTH/2) && testY < (MAP_HEIGHT/2))
	if(room[testY][testX] == GR_ROOM_FULL)
		count++;

	testY = y;
	testX = x-1;

	if(testY >= 0 && testX >= 0 && testX < (MAP_WIDTH/2) && testY < (MAP_HEIGHT/2))
	if(room[testY][testX] == GR_ROOM_FULL)
		count++;

	return(count);
     
} 

void sta2_Reduce_Tileset(int index, int valueX, int valueY, int radius)
{

	for(int i=index;i < spawn_tile_count;i++)  
	{
		spawn_tileX[i] = spawn_tileX[i+1];
		spawn_tileY[i] = spawn_tileY[i+1];
	} 

	spawn_tile_count--;

}
