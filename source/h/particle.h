
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
extern void Remove_Item(int item_type, int item_value, int item_value1, bool remove_all);
extern bool Calculate_Item(int item_value, int item_type, int the_item, int item_value1, int item_value2, int item_value3);
extern void Bit_Shift( int the_value1, int bit_to_shift, int bit_value);
extern int Get_Bit_Shift( int the_value1, int bit_to_shift);
extern int Bit_Shift_Int( int the_integer, int bit_to_shift, int bit_value);
extern int Get_Bit_Shift_Int( int the_integer, int bit_to_shift);
extern int GetUpgrades( int tune_up_page, int the_bit, int type);
extern int Tune_Gun(int the_index);
extern bool Has_This_Item(int type, int value);
extern void Shell_Landed( float x, float y, int shooter, int f_rate, int type, int value);

void Create_Dust_Effect(float x, float y, bool is_shotgun, bool is_an_offset, int f_rate); 
void Create_Crate_Effect(int guy_shot);
void Create_Frag_Effect(float x1, float y1);
void Create_Blood_Effect(int guy_shot);
void Create_Star_Effect(float x1, float y1, float size, int tex_id);
void Create_Explosion(int guy_shot);
void Create_Gibs_Effect(int index, bool bones, int type);
void Create_Fire_Point(float x, float y);
void DamageNumber( int loop, int damage, int is_blue );



void Create_Dust_Effect(float x, float y, bool is_shotgun, bool is_an_offset, int f_rate)
{
    
    int rnd=0;
    float tar_x=0.0, tar_y=0.0;
    int temp_r_x=0, temp_r_y=0;
    int temp_row=0;
	bool hit_something=false;
	bool hit_wheat=false;
    
    rnd = rand()%40;  
    
    tar_x = (float)(rnd-20);
    
    if(tar_x == 0)
        tar_x = 1;
        
    tar_x /= 100; 
    
    rnd = rand()%40; 
      
    tar_y = (float)(rnd-20); 
    
    if(tar_y == 0)
        tar_y = 1;    
    
    tar_y /= 100;  
               
    tar_x = x-tar_x;   
    tar_y = y-tar_y;  

	if(is_an_offset == true)
	{
	    tar_x = x;
		tar_y = y;    
	}      
   
    temp_r_x = (int)((tar_x + map_startX)*10);        
    temp_r_y = (int)((tar_y + map_startY)*10);       

    temp_row = (temp_r_y*MAP_HEIGHT)+temp_r_x;              
    
    if(ply_id != -1)            
    if(temp_row >= 0 && temp_row < SET_MAP_TILES)  
    { 
		  
        // Hit Wheat...    
	    if(sta2_environment_type == AREA_GRASSLANDS) 
	    if( (tiles[temp_row] >= 0 && tiles[temp_row] <= 3) || (tiles[temp_row] >= 16 && tiles[temp_row] <= 19) )
	    {
	         New_FX(tar_x-0.05f, tar_y-0.05f,  sprite[ply_id].w, sprite[ply_id].z, 75, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 6, 0, 0, -1);
    	    watersmll_sfx=true;  
			hit_something=true; 
			hit_wheat=true;
	    } 

		// Hit Wall...
		if(hit_wheat == false)
        if(map_col[temp_row] == 1 || map_col[temp_row] == 7) 
		{
				 
			if(map_cover[temp_row] != STA2_GRASS_COVER && map_cover[temp_row] != STA2_ROCK_COVER) 
			{
				map_cover[temp_row] -= 25; 

				if(map_cover[temp_row] <= 0)
					map_cover[temp_row] = 10;
			}

		//	New_FX(tar_x-0.070f, tar_y-0.06f,  sprite[ply_id].w, sprite[ply_id].z, 90, PLAY, 0.05f, 0.05f, 0.05f, 0.05f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);// Splat effect
			New_FX(tar_x-0.05f, tar_y-0.05f,  tar_x-0.05f,  tar_y-0.05f, 26, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 6, 0, 0, -1);// Spark effect
		    ric2_sfx = true;     
			hit_something=true;       	
		}

		// Hit Glass...
		if(tiles[temp_row] == 502 || tiles[temp_row] == 504)
        {
			glass_sfx = true; 

			if(Level == LVL_SUPPLIES)  
                bottle_count++;

			tiles[temp_row]++; 
			hit_something=true;   
		}

		// Hit Grass...
		if(tiles[temp_row] == 506 || tiles[temp_row] == 508)
        { 
			tiles[temp_row]++;  
		}

		// Hit Mud...
	/*	if(tiles[temp_row]==16 || tiles[temp_row] == 29 || tiles[temp_row] == 30 || tiles[temp_row] == 31)
		{
   	        New_FX(tar_x-0.070f, tar_y-0.06f,  sprite[ply_id].w, sprite[ply_id].z, 100, PLAY, 0.05f, 0.05f, 0.05f, 0.05f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);
			mudstep_sfx = true;
			hit_something=true; 
		}   */
 
		// Hit Swamp water...  
		if(sta2_environment_type == AREA_SWAMP) 
        if( (tiles[temp_row] >= 448 && tiles[temp_row] <= 455) ||  (tiles[temp_row] >= 432 && tiles[temp_row] <= 437)  ) 
        {    
          New_FX(tar_x-0.05f, tar_y-0.05f,  sprite[ply_id].w, sprite[ply_id].z, 39, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 6, 0, 0, -1);
		  hit_something=true;   
          watersmll_sfx=true; 
        }  

		// Hit Water...  
  /*      if(tiles[temp_row]>=480 && tiles[temp_row] < 484  )  
        {    
          New_FX(tar_x-0.070f, tar_y-0.06f,  sprite[ply_id].w, sprite[ply_id].z, WATER_SPLASH_ANIM, PLAY, 0.05f, 0.05f, 0.05f, 0.05f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);
		  hit_something=true;   
          watersmll_sfx=true; 
        }  */

		// Hit Mine...
   /*     if(tiles[temp_row] == 14) 
        {    
		  hit_something=true;    
                        
	      if(tiles[temp_row] == 14)                   
          	tiles[temp_row] = 15;                                   

	      Shell_Landed(tar_x, tar_y, -1, f_rate, INV_BARREL_BOMB, -1);

        }*/
        
		// Hit ground...
		if(hit_something==false)
        {
          if(is_shotgun == true) 
          {   
                        
               if(st_gas == 0) 
               {
                  New_FX(tar_x-0.070f, tar_y-0.06f,  sprite[ply_id].w, sprite[ply_id].z, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 6, 0, 0, -1);
                  New_FX(tar_x-0.070f, tar_y-0.06f,  sprite[ply_id].w, sprite[ply_id].z, 5, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 0.8f, 0, 0, FX_DECAL, -1, 6, 0, 0, -1);
               }         
               if(st_gas == 1) 
                   New_FX(tar_x-0.10f, tar_y-0.11f,  tar_x-0.10f, tar_y-0.11f, 89, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 2, GFX, 0.6f, 0, 0, FX_GAS, -1, 2, 0, 0, -1);
               if(st_gas == 2)
                   New_FX(tar_x-0.10f, tar_y-0.11f,  tar_x-0.10f, tar_y-0.11f, 89, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 2, GFX, 0.6f, 0, 0, FX_GAS, -1, 2, 0, 0, -1);
               if(st_gas == 3)
                   New_FX(tar_x-0.10f, tar_y-0.11f,  tar_x-0.10f, tar_y-0.11f, 89, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 2, GFX, 0.6f, 0, 0, FX_GAS, -1, 2, 0, 0, -1);
          }            
          else
          {   
              New_FX(tar_x-0.070f, tar_y-0.06f,  sprite[ply_id].w, sprite[ply_id].z, 0, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 6, 0, 0, -1);
              New_FX(tar_x-0.070f, tar_y-0.06f,  sprite[ply_id].w, sprite[ply_id].z, 5, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 0.8f, 0, 0, FX_DECAL, -1, 6, 0, 0, -1);
          }
           
        } // if(tiles[temp_row]>=480 && tiles[temp_row] < 484 )

    } // if(temp_row >= 0 && temp_row < SET_MAP_TILES)                           
     
}

void Create_Crate_Effect(int guy_shot)
{
    float width=0.0f, height = 0.0f; 
    float x1 =0.0f, y1 =0.0f;

	if(guy_shot < 0)
		return;
    
    width = sprite[guy_shot].width;
    height = sprite[guy_shot].height;
    
    x1 = sprite[guy_shot].x; 
    y1 = sprite[guy_shot].y;   
         
    New_FX(x1, y1, x1, y1, 54, PLAY, width, height, width, height, 1, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);

} 

void Create_Blood_Effect(int guy_shot)
{
    float width=0.0f, height = 0.0f;
    float x1 =0.0f, y1 =0.0f;

	if(guy_shot < 0)
		return;
    
    width = sprite[guy_shot].width;
    height = sprite[guy_shot].height;
    
    x1 = sprite[guy_shot].x; 
    y1 = sprite[guy_shot].y;
    
    if(sprite[guy_shot].grenaded != DEATH_GRENADE)      
        New_FX(x1, y1, x1, y1, 63, PLAY, width, height, width, height, 1, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);
    if(sprite[guy_shot].grenaded == DEATH_GRENADE)      
        New_FX(x1, y1, x1, y1, 64, PLAY, width, height, width, height, 1, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);

} 

void Create_Frag_Effect(float x1, float y1)
{
    float tar_x=0.0f, tar_y=0.0f; 
    int guy_shot=-1;
    int rnd = 0;
    
    if(ply_id != -1)
    	guy_shot = ply_id;

	if(guy_shot == -1)
		return;
                 
    tar_x = x1;   
    tar_y = y1; 
    
    rnd = rand()%2;
    
    if(rnd == 0) 
    {
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 4, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG, -1, 5, 0, UP_RIGHT, -1);
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 6, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG_SHADOW, -1, 5, 0, UP_RIGHT, -1);
    }  
    if(rnd == 1)
    {
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 4, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG, -1, 5, 0, RIGHT, -1);
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 6, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG_SHADOW, -1, 5, 0, RIGHT, -1);
    }       
    
    rnd = rand()%2; 
    
    if(rnd == 0)
    {                                
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 4, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG, -1, 5, 0, DOWN_LEFT, -1);
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 6, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG_SHADOW, -1, 5, 0, DOWN_LEFT, -1);
    }                           
    if(rnd == 1)
    {
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 4, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG, -1, 5, 0, LEFT, -1);
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 6, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG_SHADOW, -1, 5, 0, LEFT, -1);
    }      
    
    rnd = rand()%2;
    
    if(rnd == 0)
    {                                
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 4, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG, -1, 5, 0, DOWN, -1);
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 6, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG_SHADOW, -1, 5, 0, DOWN, -1);
    }                           
    if(rnd == 1)
    {
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 4, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG, -1, 5, 0, DOWN_RIGHT, -1);
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 6, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG_SHADOW, -1, 5, 0, DOWN_RIGHT, -1);
    }  
    
     
}   
 
void Create_Gibs_Effect(int index, bool bones, int type)
{ 
    float tar_x=0.0f, tar_y=0.0f;   
    int guy_shot=0;   
    int rnd = 0;
    int anim_gib = 12;    
    int anim_gib1 = 12; 
    int anim_gib2 = 12; 
	int gib_active = -1;
	sString itemp_string;

	if(index < 0)
		return;
	
	if(type == -1)
	{
    if(sprite[index].rank == 1 && sprite[index].sector != UNIT_MONKEY)
	{
        anim_gib = 13;  
        anim_gib1 = 13; 
        anim_gib2 = 13;       
	}
   
    if(sprite[index].type == BAG || sprite[index].sector == UNIT_BOX || sprite[index].sector == UNIT_DECOY)
	{
        anim_gib = 15;  
        anim_gib1 = 15; 
        anim_gib2 = 15;       
	}   
         
    if(sprite[index].type == DOR)
	{
        anim_gib = 16;  
        anim_gib1 = 16; 
        anim_gib2 = 16;       
	}   
           
    if(bones == true)
	{
        anim_gib = 11;   
        anim_gib1 = 11; 
        anim_gib2 = 11;       
	}  
 
	}  
	if(type == TARGET_HEAD)
	if( sprite[index].id >= 0) 
	{  
        anim_gib = 17;   // Skull    
        anim_gib1 = 11;  // Bones      
		anim_gib2 = 11;  // Bones 

        sprintf(itemp_string.string, "Data/chars/black_sailor.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 22;  // White sailors cap	
        sprintf(itemp_string.string, "Data/chars/black_sailorG.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 22;  // White sailors cap	
        sprintf(itemp_string.string, "Data/chars/black_admiral.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 22;  // White sailors cap	
        sprintf(itemp_string.string, "Data/chars/black_shield.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 22;  // White sailors cap
        sprintf(itemp_string.string, "Data/chars/black_shotgun.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 22;  // White sailors cap 

        sprintf(itemp_string.string, "Data/chars/black_sailorF.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 23;  // Black sailors cap
        sprintf(itemp_string.string, "Data/chars/black_sailorG1.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 23;  // Black sailors cap
        sprintf(itemp_string.string, "Data/chars/black_sailorG2.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 23;  // Black sailors cap
        sprintf(itemp_string.string, "Data/chars/black_shield1.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 23;  // Black sailors cap
        sprintf(itemp_string.string, "Data/chars/black_shotgunG.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 23;  // Black sailors cap

 
        sprintf(itemp_string.string, "Data/chars/black_pirate.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 24;  // Red pirate cap 
        sprintf(itemp_string.string, "Data/chars/black_pirateG.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 25;  // Captain pirates hat
        sprintf(itemp_string.string, "Data/chars/black_pirateS.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 25;  // Red pirate cap 

        sprintf(itemp_string.string, "Data/chars/black_art.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 26;  // Gunners cap 
        sprintf(itemp_string.string, "Data/chars/black_mortar.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 26;  // Gunners cap 
        sprintf(itemp_string.string, "Data/chars/black_scout.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 26;  // Gunners cap 
 
        sprintf(itemp_string.string, "Data/chars/black_chief.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 27;  // Chief cap 

        sprintf(itemp_string.string, "Data/chars/black_gunner.tga");     
        if( strcmp( material[sprite[index].id].string, itemp_string.string ) == 0)
			anim_gib2 = 28;  // Helmet  

//		gib_active = rand()%4;   
	}                    
            
    if(ply_id != -1) 
    	guy_shot = ply_id;
                 
    tar_x = sprite[index].w+sprite[index].box_width/2;   
    tar_y = sprite[index].z+sprite[index].box_height/2;

	if(type == TARGET_HEAD) 
	{    
	    tar_y = sprite[index].y+sprite[index].height/1.4f;
	}
	
	// First Gib....
	if(gib_active == 0 || gib_active == -1)
	if(guy_shot >= 0)
	{
    rnd = rand()%2;
     
    if(bones == true)        
        anim_gib = 17;   
        
    if(rnd == 0)
    {
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, anim_gib, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG, -1, 5, 0, UP_RIGHT, -1);
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 10, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG_SHADOW, -1, 5, 0, UP_RIGHT, -1);
    }  
    if(rnd == 1)
    {
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, anim_gib, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG, -1, 5, 0, RIGHT, -1);
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 10, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG_SHADOW, -1, 5, 0, RIGHT, -1);
    }   

	}
	
	// Second Gib....
	if(type != TARGET_HEAD)
	if(gib_active == 1 || gib_active == -1)
	if(guy_shot >= 0)
	{        

    if(bones == true)
        anim_gib = 11;  
        
    rnd = rand()%2;
    
    if(rnd == 0)
    {                                
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, anim_gib1, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG, -1, 5, 0, DOWN_LEFT, -1);
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 10, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG_SHADOW, -1, 5, 0, DOWN_LEFT, -1);
    }                           
    if(rnd == 1)
    {
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, anim_gib1, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG, -1, 5, 0, LEFT, -1);
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 10, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG_SHADOW, -1, 5, 0, LEFT, -1);
    }     

	} 
	
	// Third Gib....
	if(type != TARGET_HEAD)
	if(gib_active == 2 || gib_active == -1)
	if(guy_shot >= 0)
	{       
    rnd = rand()%2;
    
    if(rnd == 0)
    {                                
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, anim_gib1, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG, -1, 5, 0, DOWN, -1);
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 10, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG_SHADOW, -1, 5, 0, DOWN, -1);
    }                           
    if(rnd == 1)
    {
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, anim_gib1, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG, -1, 5, 0, DOWN_RIGHT, -1);
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 10, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG_SHADOW, -1, 5, 0, DOWN_RIGHT, -1);
    } 
	}
	// Fourth Gib....
	if(gib_active == 3 || gib_active == -1) 
	if(guy_shot >= 0)
	{       
    rnd = rand()%2; 
    
    if(rnd == 0) 
    {                                
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, anim_gib2, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG, -1, 5, 0, UP_LEFT, -1);
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 10, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG_SHADOW, -1, 5, 0, UP_LEFT, -1);
    }                           
    if(rnd == 1)
    {
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, anim_gib2, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG, -1, 5, 0, UP, -1);
        New_FX(tar_x, tar_y,  sprite[guy_shot].w, sprite[guy_shot].z, 10, LOOP, 0.05f, 0.05f, 0.05f, 0.05f, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_FRAG_SHADOW, -1, 5, 0, UP, -1);
    }  
	}   
    
    
} 

void Create_Star_Effect(float x1, float y1, float size, int tex_id) 
{
 
    int rnd = 0; 
  
    rnd = rand()%2;
 
	if(tex_id >= 0)
	    New_FX(x1, y1, x1, y1, 8, LOOP, size, size, size, size, 0, GFX, 1.0f, -1, BULLET_KNIFE_PLY, FX_STAR, -1, tex_id, 0, UP_RIGHT, -1);
    
} 

void Create_Muzzle_Effect(int loop) 
{
 
    int direction = 0;  
	float x=0.0f, y=0.0f;
	float size = 0.05f;
	
     
	if(loop < 0)
		return;

	direction = Convert_Angle_To_Dir(sprite[loop].angle);

    if(direction == UP)  
	{
		x = sprite[loop].x + sprite[loop].width/2;
		y = sprite[loop].y + sprite[loop].height;
	}   
                    
	New_FX(x-size/2, y-size/2, sprite[loop].w, sprite[loop].z-0.01f, 29, PLAY, size, size, size, size, 2, GFX, 1.0f, 0, 0, FX_MUZZLE, loop, 27, 0, UP, -1); 

}  

void Create_Explosion(int guy_shot)
{
    float mid_x=0.0f;
    float mid_y=0.0f;
    
    int rnd=0;     
    int anim=0;
     
	if(guy_shot < 0)
		return;

    if(exploding_type == EXPLOSION_FIRE)
        anim=37;        
    
    if(exploding_type == EXPLOSION_ROCK)
        anim=85;        
     
    rnd = rand()%6; 
    
    mid_x = sprite[guy_shot].x; 
    mid_y = sprite[guy_shot].y; 
    
    if(rnd == 0)
        New_FX(mid_x, mid_y-0.2f, mid_x, mid_y, anim, PLAY, 0.4f, 0.4f, 0.4f, 0.4f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);
    if(rnd == 1)
        New_FX(mid_x+0.05f, mid_y+0.1f, mid_x, mid_y, anim, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);
    if(rnd == 2)
        New_FX(mid_x-0.2f, mid_y-0.1f, mid_x, mid_y, anim, PLAY, 0.4f, 0.4f, 0.4f, 0.4f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);
    if(rnd == 3)
        New_FX(mid_x, mid_y+0.05f, mid_x, mid_y, anim, PLAY, 0.5f, 0.5f, 0.5f, 0.5f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);
    if(rnd == 4)
        New_FX(mid_x-0.20f, mid_y+0.10f, mid_x, mid_y, anim, PLAY, 0.5f, 0.5f, 0.5f, 0.5f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);
    if(rnd == 5)
        New_FX(mid_x, mid_y, mid_x, mid_y, anim, PLAY, 0.5f, 0.5f, 0.5f, 0.5f, 2, GFX, 1.0f, 0, 0, FX_STATIC, -1, 2, 0, 0, -1);

    Camera_Shake(THUD_SHAKE);  

	#if INCLDUE_360_CONTROLLER == 1
		if(CONTROLLER) 
		{
			VIBRATE_LEFT(36000, 150); 
			VIBRATE_RIGHT(36000, 150);		
		}
	#endif
    
    if(exploding_type == EXPLOSION_ROCK)  
        destroy_sfx = true;      
    
    if(exploding_type == EXPLOSION_FIRE)  
        clank_sfx=true;      
    
   
}  
 

void Create_Fire_Point( float x, float y )
{
    if(daytime == NIGHTTIME || (in_dungeon == true && !ARCADE)) 
    {  
        points[no_points].x = x;  
        points[no_points].y = y; 
        points[no_points].c1 = LIGHT_PNT;
        points[no_points].score = (int)TimerGetTime() + 1500;
        points[no_points].c4 = LIGHT_FIRE_ROUND;
        no_points++;     
    }
     
}

void DamageNumber( int loop, int damage, int is_blue )
{
	float mid_x=0.0f, mid_y=0.0f;
	int anim=7; // number 0
	int anim1=7; // number 0
	int anim2=7; // number 0
	int number_of_letters=1;

	int first_digit = damage;   
	int second_digit = damage;  
	int third_digit = damage; 

	int hp_xp_anim=54;
	 
	if(loop < 0)
		return; 

	if(is_blue == STA2_DAMAGE_HP || is_blue == STA2_DAMAGE_XP || is_blue == STA2_DAMAGE_FOOD)  
	{
		anim=40; // number 0
		anim1=40; // number 0
		anim2=40; // number 0
	}

	if(is_blue == STA2_DAMAGE_HP)
		hp_xp_anim=55;
	if(is_blue == STA2_DAMAGE_XP)
		hp_xp_anim=54; 
	if(is_blue == STA2_DAMAGE_FOOD)
		hp_xp_anim=76;

	mid_x = sprite[loop].x+sprite[loop].width/2;
	mid_y = sprite[loop].y+sprite[loop].height/2;

	if(damage != -1) // miss
	{ 
		 
		first_digit = damage%10;  
		second_digit = ((damage%100 - damage%10) / 10);
		third_digit = (third_digit - damage%100) / 100;

		anim += first_digit;
		anim1 += second_digit;
		anim2 += third_digit;

		if(damage < 1000)
			number_of_letters = 3;   
	  
		if(damage < 100)     
			number_of_letters = 2;  

		if(damage < 10) 
			number_of_letters = 1;   

		if(number_of_letters == 1)
		{
			if(is_blue == STA2_DAMAGE_XP || is_blue == STA2_DAMAGE_HP || is_blue == STA2_DAMAGE_FOOD)
			{
				New_FX(mid_x-0.062f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
				New_FX(mid_x-0.034f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, hp_xp_anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
			}
			else
			{
				New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
			}

		}

		if(number_of_letters == 2)
		{
			if(is_blue == STA2_DAMAGE_XP || is_blue == STA2_DAMAGE_HP || is_blue == STA2_DAMAGE_FOOD)
			{
				New_FX(mid_x-0.08f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, anim1, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
				New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
				New_FX(mid_x-0.02f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, hp_xp_anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
			}
			else
			{
				New_FX(mid_x-0.062f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, anim1, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
				New_FX(mid_x-0.034f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
			}
		}

		if(number_of_letters == 3) 
		{ 
			if(is_blue == STA2_DAMAGE_XP || is_blue == STA2_DAMAGE_HP || is_blue == STA2_DAMAGE_FOOD)
			{
				New_FX(mid_x-0.08f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, anim2, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
				New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, anim1, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
				New_FX(mid_x-0.02f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
				New_FX(mid_x+0.01f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, hp_xp_anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
			}
			else
			{
				New_FX(mid_x-0.08f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, anim2, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
				New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, anim1, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
				New_FX(mid_x-0.02f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, anim, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE, -1, 6, 0, 0, -1);
			}
		}

	}
	else   
	{

		if(is_blue == STA2_DAMAGE_MISS)
			New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, 6, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE_SLOW, -1, 6, 0, 0, -1);

		if(is_blue == STA2_DAMAGE_ACC)
			New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, 59, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE_SLOW, -1, 6, 0, 0, -1); 

		if(is_blue == STA2_DAMAGE_SHD)
			New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, 60, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE_SLOW, -1, 6, 0, 0, -1); 

		if(is_blue == STA2_DAMAGE_DUM)
			New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, 61, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE_SLOW, -1, 6, 0, 0, -1); 

		if(is_blue == STA2_DAMAGE_BOOT)
			New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, 62, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE_SLOW, -1, 6, 0, 0, -1); 

		if(is_blue == STA2_DAMAGE_EYE)
			New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, 63, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE_SLOW, -1, 6, 0, 0, -1); 

		if(is_blue == STA2_DAMAGE_NET)
			New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, 64, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE_SLOW, -1, 6, 0, 0, -1); 

		if(is_blue == STA2_DAMAGE_VAMP)
			New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, 65, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE_SLOW, -1, 6, 0, 0, -1); 

		if(is_blue == STA2_DAMAGE_HERB)
			New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, 66, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE_SLOW, -1, 6, 0, 0, -1); 

		if(is_blue == STA2_DAMAGE_EXP)
			New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, 67, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE_SLOW, -1, 6, 0, 0, -1); 

		if(is_blue == STA2_DAMAGE_BLOW)
			New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, 68, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE_SLOW, -1, 6, 0, 0, -1); 

		if(is_blue == STA2_DAMAGE_LAST)
			New_FX(mid_x-0.05f, mid_y+0.05f,  sprite[loop].w, sprite[loop].y-0.0001f, 69, PLAY, 0.1f, 0.1f, 0.1f, 0.1f, 2, GFX, 1.0f, 0, 0, FX_SCORE_SLOW, -1, 6, 0, 0, -1); 



	}
	     
	
}