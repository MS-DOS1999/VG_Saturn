#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64  
#define WIN32_LEAN_AND_MEAN      
#include <windows.h>
#endif      


int Key_Handler(bool keys[256], object *display, int f_rate)
{ 
	int return_value = 0;

    
     if(f_rate <= 0)
         f_rate = 1;   

	// ******************************************************************************//
	//                                COPY/PASTE                                     //
	// ******************************************************************************//

   if(DEMO_MODE == 0)
    if( keys[VK_CONTROL] && keys['C'] )
	if(selection >= 0 && selection < TOTAL_NO_SPRITES)
    {
        
        keys['C']=false;
        
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		if(selection >= 0)
        {
                
        sprite_copy.x = sprite[selection].x;
        sprite_copy.y = sprite[selection].y;
        sprite_copy.width = sprite[selection].width;
        sprite_copy.height = sprite[selection].height;
                
        sprite_copy.w = sprite[selection].w;
        sprite_copy.z = sprite[selection].z;
        sprite_copy.box_width = sprite[selection].box_width;
        sprite_copy.box_height = sprite[selection].box_height;
                
        for(int j=0;j<4;j++)
        {
            sprite_copy.u[j] = sprite[selection].u[j];
            sprite_copy.v[j] = sprite[selection].v[j];
        }    
        sprite_copy.id = sprite[selection].id;
        sprite_copy.score = sprite[selection].score;
        sprite_copy.cur = sprite[selection].cur;
        sprite_copy.alpha = sprite[selection].alpha;
        sprite_copy.type = sprite[selection].type;
        sprite_copy.priority = sprite[selection].priority;
        sprite_copy.linked_sprite = sprite[selection].linked_sprite;
                
        sprite_copy.anim = sprite[selection].anim;
        sprite_copy.anim_state = sprite[selection].anim_state;
        sprite_copy.grab_switch = sprite[selection].grab_switch;
        sprite_copy.mouseover = sprite[selection].mouseover;
        sprite_copy.sector = sprite[selection].sector;
        sprite_copy.sector_action = sprite[selection].sector_action;
        sprite_copy.onCreate = sprite[selection].onCreate;
        sprite_copy.onCreate_action = sprite[selection].onCreate_action;
        sprite_copy.rank = sprite[selection].rank;
        sprite_copy.onDeath_action = sprite[selection].onDeath_action;                
        sprite_copy.light = sprite[selection].light; 
        
        vg_stamp_sfx=true;
        
        }
        
    }
    
    if(DEMO_MODE == 0) 
    if( keys[VK_CONTROL] && keys['V'] )
    {
        
        keys['V']=false;
        keys[VK_CONTROL]=false;
        
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		if(no_sprites >= 0 && no_sprites < TOTAL_NO_SPRITES-1)
        { 
            no_sprites++;
            original_no_sprites++; 
            
            sprite[no_sprites - 1].x = -(camX + sprite_copy.width/2);
            sprite[no_sprites - 1].y = -(camY + sprite_copy.height/2);
            sprite[no_sprites - 1].width = sprite_copy.width;
            sprite[no_sprites - 1].height = sprite_copy.height;
                
            sprite[no_sprites - 1].w = sprite_copy.w - (sprite_copy.x - sprite[no_sprites - 1].x);
            sprite[no_sprites - 1].z = sprite_copy.z - (sprite_copy.y - sprite[no_sprites - 1].y);
            sprite[no_sprites - 1].box_width = sprite_copy.box_width;
            sprite[no_sprites - 1].box_height = sprite_copy.box_height;
                
            for(int j=0;j<4;j++)
            {
                sprite[no_sprites - 1].u[j] = sprite_copy.u[j];
                sprite[no_sprites - 1].v[j] = sprite_copy.v[j];
            }    
            
            sprite[no_sprites - 1].id = sprite_copy.id;
            sprite[no_sprites - 1].score = sprite_copy.score;
            sprite[no_sprites - 1].cur = sprite_copy.cur; 
            sprite[no_sprites - 1].alpha = sprite_copy.alpha;
            sprite[no_sprites - 1].type = sprite_copy.type;
            sprite[no_sprites - 1].priority = sprite_copy.priority;
            sprite[no_sprites - 1].linked_sprite = sprite_copy.linked_sprite;
                
            sprite[no_sprites - 1].anim = sprite_copy.anim;
            sprite[no_sprites - 1].anim_state = sprite_copy.anim_state;
            sprite[no_sprites - 1].grab_switch = sprite_copy.grab_switch;
            sprite[no_sprites - 1].mouseover = sprite_copy.mouseover;
            sprite[no_sprites - 1].sector = sprite_copy.sector;
            sprite[no_sprites - 1].sector_action = sprite_copy.sector_action;
            sprite[no_sprites - 1].onCreate = sprite_copy.onCreate;
            sprite[no_sprites - 1].onCreate_action = sprite_copy.onCreate_action;
            sprite[no_sprites - 1].rank = sprite_copy.rank;
            sprite[no_sprites - 1].onDeath_action = sprite_copy.onDeath_action;                
            sprite[no_sprites - 1].light = sprite_copy.light; 
            
            sprite[no_sprites - 1].turn_off = sprite_copy.turn_off;
                   
            if( texture_fx[sprite[no_sprites - 1].id] == 2 || texture_fx[sprite[no_sprites - 1].id] == 3 || texture_fx[sprite[no_sprites - 1].id] == 4)
               sprite[no_sprites - 1].fx_id = animation_fx[sprite[no_sprites - 1].id];
                                                   	         
            selection = (no_sprites-1);
            
            vg_stamp_sfx=true;
            
        }         
        
    }
    
 
	// ******************************************************************************//
	//                                MUSIC/SELECT                                   //
	// ******************************************************************************//

    if(DEMO_MODE == 0)    
    if( keys[VK_CONTROL] && keys['S'] )
    {
        keys['S']=false;
        
        if(music_loop)
            music_loop--;
            
    }    
    
    if(DEMO_MODE == 0)    
    if( keys[VK_CONTROL] && keys['D'] )
    {
        keys['D']=false;
        
        music_loop++;
            
    }   
    
 
	// ******************************************************************************//
	//                                   DELETE                                      //
	// ******************************************************************************//

    if(DEMO_MODE == 0)    
	if(game_paused == false)           
    if( keys[VK_DELETE])
    {
        
        keys[VK_DELETE]=false;
        
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		if(selection >= 0)
        {   
                              
            for(int loop=selection;loop<no_sprites;loop++)
            {
                sprite[loop].x = sprite[loop+1].x;
                sprite[loop].y = sprite[loop+1].y;
                sprite[loop].width = sprite[loop+1].width;
                sprite[loop].height = sprite[loop+1].height;
                
                sprite[loop].w = sprite[loop+1].w;
                sprite[loop].z = sprite[loop+1].z;
                sprite[loop].box_width = sprite[loop+1].box_width;
                sprite[loop].box_height = sprite[loop+1].box_height;
                
                for(int j=0;j<4;j++)
                {
                    sprite[loop].u[j] = sprite[loop+1].u[j];
                    sprite[loop].v[j] = sprite[loop+1].v[j];
                }    
                sprite[loop].id = sprite[loop+1].id;
                sprite[loop].score = sprite[loop+1].score;
                sprite[loop].cur = sprite[loop+1].cur;
                sprite[loop].alpha = sprite[loop+1].alpha;
                sprite[loop].type = sprite[loop+1].type;
                sprite[loop].priority = sprite[loop+1].priority;
                sprite[loop].linked_sprite = sprite[loop+1].linked_sprite;
                
                sprite[loop].anim = sprite[loop+1].anim;
                sprite[loop].anim_state = sprite[loop+1].anim_state;
                sprite[loop].grab_switch = sprite[loop+1].grab_switch;
                sprite[loop].mouseover = sprite[loop+1].mouseover;
                sprite[loop].sector = sprite[loop+1].sector;
                sprite[loop].sector_action = sprite[loop+1].sector_action;
                sprite[loop].onCreate = sprite[loop+1].onCreate;
                sprite[loop].onCreate_action = sprite[loop+1].onCreate_action;
                sprite[loop].rank = sprite[loop+1].rank;
                sprite[loop].onDeath_action = sprite[loop+1].onDeath_action;                
                sprite[loop].light = sprite[loop+1].light;                
                sprite[loop].global_flag = sprite[loop+1].global_flag;
                   
                if( texture_fx[sprite[loop].id] == 2 || texture_fx[sprite[loop].id] == 3 || texture_fx[sprite[loop].id] == 4)
                   sprite[loop].fx_id = animation_fx[sprite[loop].id];
                     
                                
            }  

                           
            if(no_sprites>0)
                no_sprites--;
                
            if(!(selection == 0)) 
            selection--; 
            
       }     
        
       if(mode && mode == POINT_MODE)
       {
		   if(pt_selection >= 0) 
           for(int loop=pt_selection;loop<no_points;loop++)
           { 
              points[loop].x = points[loop+1].x;
              points[loop].y = points[loop+1].y; 
              
              points[loop].score = points[loop+1].score;  
              points[loop].active = points[loop+1].active;
              points[loop].speed  = points[loop+1].speed;  
              points[loop].c1 = points[loop+1].c1;
              points[loop].c2 = points[loop+1].c2; 
              points[loop].c3 = points[loop+1].c3;
              points[loop].c4 = points[loop+1].c4; 
                                                  
           }
           if(no_points>0)
               no_points--;
                
           if(!(pt_selection == 0)) 
               pt_selection--; 
       } 
       
       if(mode && mode == NODES)
       {
		      
       }        
    } 
    
 
	// ******************************************************************************//
	//                                POSITIONING                                    //
	// ******************************************************************************//

    shift_key = false;
 
	if(game_paused == false)      
    if( keys[VK_SHIFT]) 
    {  
        shift_key = true;    
    }
     
    if( keys[VK_SHIFT])
        precision = 0.045f;

	if( keys[VK_CONTROL])
        precision = 0.015f;

	if( keys[VK_SHIFT] && keys[VK_CONTROL])
        precision = 0.0005f;


   // VK_UP  
	if(game_paused == false) 
    if(DEMO_MODE == 0 && mode)   
	if (keys[VK_UP] && !keys[VK_DOWN] )
	{ 
       
       if(keys[VK_CONTROL] || keys[VK_SHIFT])    
       {
           if(mode==PLACEMENT)          
		   if(selection >= 0)
           {
    	       display[selection].y += precision;
    	       display[selection].z += precision;
           }    
           if(mode==TEXTURE)
		   if(selection >= 0)
           {
               display[selection].v[0] -= precision;
               display[selection].v[1] -= precision;
               display[selection].v[3] -= precision;
               display[selection].v[2] -= precision;
           }
           if(mode==COLLISION)
		   if(selection >= 0)
               display[selection].z += precision;
                      
           if(mode==POINT_MODE)          
		   if(pt_selection >= 0)
    	       points[pt_selection].y += precision;

       }
	   else   
       {  
          camY -= (float)SCROLL_SPEED*(float)f_rate;                     
          mouseY += (float)SCROLL_SPEED*(float)f_rate;           
       }   
	}
    
    // VK_DOWN
	if(game_paused == false)  
    if(DEMO_MODE == 0 && mode)
	if (keys[VK_DOWN] && !keys[VK_UP])
	{
       if(keys[VK_CONTROL] || keys[VK_SHIFT]) 
       {              
           if(mode==PLACEMENT)
		   if(selection >= 0)
           {               
    	       display[selection].y -= precision;
    	       display[selection].z -= precision;
           }
           if(mode==TEXTURE)
		   if(selection >= 0)
           {
               display[selection].v[0] += precision;
               display[selection].v[1] += precision;
               display[selection].v[3] += precision;
               display[selection].v[2] += precision;
           }
           if(mode==COLLISION)
		   if(selection >= 0)
               display[selection].z -= precision;
               
           if(mode==POINT_MODE)
		   if(pt_selection >= 0)
    	       points[pt_selection].y -= precision;

       }
       else
       {
            camY += (float)SCROLL_SPEED*(float)f_rate;        
            mouseY -= (float)SCROLL_SPEED*(float)f_rate; 
       }    
	}
	
	// VK_RIGHT
	if(game_paused == false) 
    if(DEMO_MODE == 0 && mode)	
	if (keys[VK_RIGHT] && !keys[VK_LEFT])
	{
       if(keys[VK_CONTROL] || keys[VK_SHIFT])  
       {               
           if(mode==PLACEMENT)                
		   if(selection >= 0)
           {
    	       display[selection].x += precision;
    	       display[selection].w += precision;
           }
           if(mode==TEXTURE)
		   if(selection >= 0)
           {
               display[selection].u[0] -= precision;
               display[selection].u[1] -= precision;
               display[selection].u[3] -= precision;
               display[selection].u[2] -= precision;
                
           }
           if(mode==COLLISION)
		   if(selection >= 0)
               display[selection].w += precision;
     
           if(mode==POINT_MODE)                
		   if(pt_selection >= 0)
    	       points[pt_selection].x += precision;

       }
       else
       {
            camX -= (float)SCROLL_SPEED*(float)f_rate;                   
            mouseX += (float)SCROLL_SPEED*(float)f_rate;      
       }  	       
	}
	
	// VK_LEFT
	if(game_paused == false) 
    if(DEMO_MODE == 0 && mode)	
	if (keys[VK_LEFT] && !keys[VK_RIGHT])
	{
       if(keys[VK_CONTROL] || keys[VK_SHIFT])  
       {               
           if(mode==PLACEMENT)                
		   if(selection >= 0)
           {
    	       display[selection].x -= precision;
    	       display[selection].w -= precision;
           }
           if(mode==TEXTURE)
		   if(selection >= 0)
           {
               display[selection].u[0] += precision;
               display[selection].u[1] += precision;
               display[selection].u[3] += precision;
               display[selection].u[2] += precision;
           }
           if(mode==COLLISION)
		   if(selection >= 0)
               display[selection].w -= precision;
               
           if(mode==POINT_MODE)                 
		   if(pt_selection >= 0)
    	       points[pt_selection].x -= precision;

       }
       else
       {
            camX += (float)SCROLL_SPEED*(float)f_rate;                                                            
            mouseX -= (float)SCROLL_SPEED*(float)f_rate;                 
       }              
	} 
    
 
	// ******************************************************************************//
	//                                ACTIVATE DEBUG                                 //
	// ******************************************************************************//

   if(game_paused == false)
   if(DEMO_MODE == 0) 
   if (keys[VK_SPACE]) 
   {

        KEY_SPACE = false;    
        
        if(space_is_held == false)
            KEY_SPACE = true; 

	if(game_paused == false)        
    if(DEMO_MODE == 0) 
    {  

       game_paused = false;          

       keys[VK_SPACE]=false; 
                     
       mouseX = -camX;
       mouseY = -camY; 
          
       if ( mode == STANDARD )
       {
           mode = PLACEMENT;
           zoom_factor = ZOOM_AMOUNT;
           
           if( ( game_mode == WALK || game_mode == WORLD) )
           {
               mode = CAMERA; 
               text[3].x = -0.35f;     
               sprintf( text[3].word, "Camera mode");       
           }
            
       }    
       else
       {
           mode = STANDARD;
           zoom_factor = ZOOM_AMOUNT;
       }
      
       if( mode == PLACEMENT )
       {
           text[3].x = -0.35f;     
           sprintf( text[3].word, "Placement mode");
       }
             
       LoadScene( episode, scene, true );
#ifdef SWITCH
       Zoom(zoom_factor);
#endif
       
       animating = false;           
         
       if(!mode)
       { 
		   sprintf( temp_string.string, "Data/verdict/font");                

           Change_Texture(temp_string, 0);  
       }
       else
       {
		   sprintf( temp_string.string, "Data/hud/font");                
           Change_Texture(temp_string, 0);  
       }
       
       } // demo_mode == 0
      
    } 
    else
    {
       KEY_SPACE = false;
       keys[VK_SPACE]=false;
       space_is_held=false; 
    }
    
 
	// ******************************************************************************//
	//                                SWITCH MODE                                    //
	// ******************************************************************************//

	if(game_paused == false)
    if (keys[VK_TAB])
	{
                     
       keys[VK_TAB]=false;					// If So Make Key FALSE

       if(DEMO_MODE == 0)
       if(mode)
       {    
           switch (mode)
           {  
               hud[47].alpha = 0.0;  
               case PLACEMENT:
           
                   mode = TEXTURE;       
                   text[3].x = -0.28f;
                   sprintf( text[3].word, "Texture mode");
                   hud[1].alpha = 1.0;
               break;          
               case TEXTURE:
                                
                   mode = COLLISION;  
                   text[3].x = -0.35f;     
                   sprintf( text[3].word, "Collision mode");
                   hud[1].alpha = 1.0;
               break;  
               case COLLISION:
               
                   mode = POINT_MODE;
                   text[3].x = -0.25f;    
                   sprintf( text[3].word, "Points mode");
                   hud[1].alpha = 1.0;     
               break;                 
               case POINT_MODE:  
                
                   mode = TILE_MODE;
                   text[3].x = -0.25f;    
                   sprintf( text[3].word, "Tiling mode"); 
                   hud[1].alpha = 0.0;  
                   hud[47].alpha = 1.0;   
               break;  
               case TILE_MODE: 
                 
                   mode = PLACEMENT;
                   text[3].x = -0.25f;     
                   sprintf( text[3].word, "Placement mode");
                   hud[1].alpha = 1.0;     
               break;                  
                          
           }
       } 

    }   
 
	// ******************************************************************************//
	//                                DUMP SCENE                                     //
	// ******************************************************************************//

	if (keys[VK_RETURN]) 
	{
                      
         keys[VK_RETURN]=false;					// If So Make Key FALSE      

         if(DEMO_MODE == 0)                
         if( mode )      
         if (dump_debug==false) 
         { 
          
           sprintf( string, "scene/episode%i/scene%i.tmp", episode, scene);
                                    
           remove(string); 
                                       
           sprintf( string, "scene/episode%i/scene%i.dat", episode, scene);
          
           DumpScene( string );
                                       
           sprintf( string, "scene/episode%i/scene%i.pt", episode, scene);
          
           DumpPoints( string );
           
           sprintf( string, "scene/episode%i/scene%i.nde", episode, scene);
           
           DumpNodes( string );   
           
           sprintf( string, "scene/episode%i/scene%i.bg", episode, scene);
           
           Dump_BG( string );    
           
           sprintf( string, "scene/episode%i/scene%i.col", episode, scene);
                                                       
           dump_debug=true; 
           
           vg_win_sfx = true; 
                                   
        }  

     }        
     else
	 { 
		if(DEMO_MODE == 0)
		if (dump_debug) 
			dump_debug=false;
	 }
 
	// ******************************************************************************//
	//                                ZOOM FUNCTIONS                                 //
	// ******************************************************************************//

     if(keys['Q']) // Zoom function
     {

       	keys['Q']=false;

		if(!(keys[VK_CONTROL]))
        {         
            zoom_factor +=0.1f;
#ifdef SWITCH
            Zoom(zoom_factor);
#endif
        }  

		if(keys[VK_CONTROL])
		{
			keys[VK_CONTROL] = false;
       
            quitting = true;
            quit_timer = (int)TimerGetTime() + 100; 

			vg_stamp_sfx = true;   

		} 

     }   

     if( keys['W']) // Zoom function
     {

         keys['W']=false;
     
         zoom_factor -=0.1f;
#ifdef SWITCH
         Zoom(zoom_factor);
#endif
                  
     } 
 
	// ******************************************************************************//
	//                                SIZE FUNCTIONS                                 //
	// ******************************************************************************//

	 if(game_paused == false)
     if( keys['1'] || DX_WEAPON1 == true)
     { 
         
         keys['1'] = false;   
		 DX_WEAPON1 = false;
                  
         if(DEMO_MODE == 0) 
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {
			 // 16x16 
			 if(keys[VK_CONTROL] && keys[VK_SHIFT])   
			 { 
				 display[selection].width  = 0.05f; 
				 display[selection].w  = display[selection].x;
				 display[selection].box_width  = 0.05f;
			 }   
			 // 32x32 
			 if(keys[VK_CONTROL] && !keys[VK_SHIFT])  
			 {
				 display[selection].width  = 0.1f; 
				 display[selection].w  = display[selection].x;
				 display[selection].box_width  = 0.1f;
			 }      
			 // 512x 
			 if(keys[VK_SHIFT] && !keys[VK_CONTROL])  
			 {
				 display[selection].width  = 1.6f; 
				 display[selection].w  = display[selection].x;
				 display[selection].box_width  = 1.6f;
			 }      

			 if(!keys[VK_CONTROL] && !keys[VK_SHIFT])
                 fade_in -= 1;   
         }    

     }


	 if(game_paused == false)
     if( keys['2'] || DX_WEAPON2 == true)
     {
         DX_WEAPON2 = false;
         keys['2'] = false;
                  
         if(DEMO_MODE == 0)         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {
			 // 64x64
			 if(keys[VK_CONTROL]) 
			 {
				 display[selection].width  = 0.2f;
				 display[selection].w  = display[selection].x;
				 display[selection].box_width  = 0.2f;
			 }
			 // 1024 
			 if(keys[VK_SHIFT])  
			 {
				 display[selection].width  = 3.2f; 
				 display[selection].w  = display[selection].x;
				 display[selection].box_width  = 3.2f;
			 }      
			 if(!keys[VK_CONTROL] && !keys[VK_SHIFT]) 
                 fade_in += 1;  
         }     
                      
     }

	 if(game_paused == false)
     if( keys['3'] || DX_WEAPON3 == true) 
     {
         DX_WEAPON3 = false;  
         keys['3'] = false;

         if(DEMO_MODE == 0)         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {
			  
			 // 128       
			 if(keys[VK_CONTROL]) 
			 {
				 display[selection].width  = 0.4f;
			//	 display[selection].height = 0.4f;
				 display[selection].w  = display[selection].x;
			//	 display[selection].z  = display[selection].y;
				 display[selection].box_width  = 0.4f;
			//	 display[selection].box_height = 0.4f;
			 }
			 // 2056 
			 if(keys[VK_SHIFT])  
			 {
				 display[selection].width  = 6.4f; 
				 display[selection].w  = display[selection].x;
				 display[selection].box_width  = 6.4f;
			 }   
			 if(!keys[VK_CONTROL] && !keys[VK_SHIFT]) 
                 fade_out -= 1; 
         }      
               
     }

	 if(game_paused == false)
     if( keys['4'] || DX_WEAPON4 == true)
     { 
         DX_WEAPON4 = false;   
         keys['4'] = false;

         if(DEMO_MODE == 0)         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {

			 // 256
			 if(keys[VK_CONTROL]) 
			 {
				 display[selection].width  = 0.8f;
			//	 display[selection].height = 0.8f;
				 display[selection].w  = display[selection].x;
			//	 display[selection].z  = display[selection].y;
				 display[selection].box_width  = 0.8f;
			//	 display[selection].box_height = 0.8f;
			 }
			 else
                 fade_out += 1; 
         }   
                          
     }   
 	 if(game_paused == false)
     if (keys['5'])
     { 
                    
         keys['5'] = false;

         if(DEMO_MODE == 0)         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {

			 // 16x16  
			 if(keys[VK_CONTROL] && keys[VK_SHIFT]) 
			 { 
				 display[selection].height = 0.05f;
				 display[selection].z  = display[selection].y;
				 display[selection].box_height = 0.05f;
			 }
			  
			 // 32x32 
			 if(keys[VK_CONTROL] && !keys[VK_SHIFT]) 
			 {
				 display[selection].height = 0.1f;
				 display[selection].z  = display[selection].y;
				 display[selection].box_height = 0.1f;
			 }
			 // 512x 
			 if(keys[VK_SHIFT] && !keys[VK_CONTROL])  
			 {
				 display[selection].height  = 1.6f; 
				 display[selection].z  = display[selection].y;
				 display[selection].box_height  = 1.6f; 
			 }      

         }    

                                                         
     }    
	 if(game_paused == false)              
     if (keys['6'])
     {
                   
         keys['6'] = false;

         if(DEMO_MODE == 0)         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {

			 //64x64 
			 if(keys[VK_CONTROL]) 
			 {
			//	 display[selection].width  = 0.2f;
				 display[selection].height = 0.2f;;
			//	 display[selection].w  = display[selection].x;
				 display[selection].z  = display[selection].y;
			//	 display[selection].box_width  = 0.2f;
				 display[selection].box_height = 0.2f;
			 }
			 // 1024x 
			 if(keys[VK_SHIFT])  
			 {
				 display[selection].height  = 3.2f; 
				 display[selection].z  = display[selection].y;
				 display[selection].box_height  = 3.2f; 
			 }    

         }   
                             
     }     
	 if(game_paused == false)      
     if (keys['7'])
     {
                   
         keys['7'] = false;

         if(DEMO_MODE == 0)         
         if(mode && mode != NODES && mode != TILE_MODE)
         {

			 // 128x128  
				 display[selection].width  = 0.4f;
				 display[selection].height = 0.4f;
			//	 display[selection].w  = display[selection].x;
				 display[selection].z  = display[selection].y;
			//	 display[selection].box_width  = 0.4f;
				 display[selection].box_height = 0.4f;


         }   
               
         
     }    

	 if(game_paused == false)           
     if (keys['8'])
     {
                   
         keys['8'] = false; 
  
         if(DEMO_MODE == 0)         
         if(mode && mode != NODES && mode != TILE_MODE)
         {
			   
			 // 256x256

			//	 display[selection].width  = 0.8f;
				 display[selection].height = 0.8f;
			//	 display[selection].w  = display[selection].x;
				 display[selection].z  = display[selection].y;
			//	 display[selection].box_width  = 0.8f;
				 display[selection].box_height = 0.8f;


         }   
                          
     } 

	// ******************************************************************************//
	//                                SET ANIM STATE                                 //
	// ******************************************************************************//

	 if(game_paused == false)          
     if (keys['9'])
     {
                   
         keys['9'] = false;
         
         if(DEMO_MODE == 0)
		 if(!keys[VK_CONTROL]) 
         if(mode) 
         {
             if(mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
			 if(selection >= 0)
             if(display[selection].anim_state)
                 display[selection].anim_state--;
                 
             if( mode == POINT_MODE)
			 if(pt_selection >= 0)
             if(points[pt_selection].anim_state)
                 points[pt_selection].anim_state--;
                             
         }     
             
     }    
	 if(game_paused == false)     
     if (keys['0'])
     { 
                        
         keys['0'] = false;
         
         if(DEMO_MODE == 0)         
         if(mode)
         {
                 
             if( mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
			 if(selection >= 0)
             {
                 
             if(display[selection].type != CUT && display[selection].type != BUT && display[selection].type != ALM)
             if(display[selection].anim_state < LOOP)
                 display[selection].anim_state++;
                
             }
             if( mode == POINT_MODE)
			 if(pt_selection >= 0)
             if(points[pt_selection].anim_state < ONCE)
                 points[pt_selection].anim_state++; 
                 
         }  

     } 
      // ANIM.STATE       
     if(DEMO_MODE == 0)
     if(keys[VK_F2])
     {
                   
         keys[VK_F2] = false; 

         if(mode)
         {
             if( mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
			 if(selection >= 0)
             if(display[selection].anim)
                 display[selection].anim--;
                 
             if(mode == POINT_MODE)
			 if(pt_selection >= 0)
                 points[pt_selection].anim--;
              
         } 
     
     }   

     if(DEMO_MODE == 0) 
     if(keys[VK_F3])
     {
                   
         keys[VK_F3] = false;
      
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		 if(selection >= 0)
         {
             if(display[selection].anim < a_texture[display[selection].fx_id].no_of_anims-1)
             display[selection].anim++;
             
         }
             
         if(mode == POINT_MODE)
		 if(pt_selection >= 0)
             points[pt_selection].anim++;
       
     }

	// ******************************************************************************//
	//                                SET GAME MODE                                  //
	// ******************************************************************************//

     if ( keys['M'])
     {
         keys['M'] =false;
         
        if(DEMO_MODE == 0 )         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {
                 
         game_mode ++; 
         
         if(game_mode > 5)
             game_mode =0;
         
         }  
                              
     }  

	// ******************************************************************************//
	//                                SET SPRITE TYPE                                //
	// ******************************************************************************//

     if (keys['V'])						// Is F1 Being Pressed?
     {
        keys['V']=false;					// If So Make Key FALSE
        
        if(DEMO_MODE == 0 )        
        if(mode  && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)        
        {
			if(selection >= 0)  
				display[selection].type++;            
        }

     } 

     if(keys['C'])						// Is F1 Being Pressed?
     {
        keys['C']=false;					// If So Make Key FALSE
        
        if(DEMO_MODE == 0 )        
        if(mode  && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
        {

			if(selection >= 0)  
            if(display[selection].type > 0)
                display[selection].type--; 
            
        }
 
            
     }    

	// ******************************************************************************//
	//                                SET PRIORITY                                   //
	// ******************************************************************************//

     if( keys['E'])
     {
	
         keys['E']=false;
         
        if(DEMO_MODE == 0 )         
		 if(selection >= 0)
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
             display[selection].priority--;
                 
         if( mode == POINT_MODE)
		 if(pt_selection >= 0)
         {
             points[pt_selection].c1--;
         }             

     }   
       
     if( keys['R'])
     {
         keys['R']=false;

        if(DEMO_MODE == 0 )    
		 if(selection >= 0)     
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
             display[selection].priority++;
                          
         if( mode == POINT_MODE)
		 if(pt_selection >= 0)
         {
             points[pt_selection].c1++; 
         }     

     }        

	// ******************************************************************************//
	//                                 DEBUG LINES                                   //
	// ******************************************************************************//

     if(DEMO_MODE == 0) 
     if(keys[VK_CONTROL] && keys[VK_F2])
     { 
         keys[VK_F2]=false;
         
         if(debug_active == true)
         {
             debug_active = false;                   
         }
         else
         {
             debug_active = true;
         }
         
     }    



	return(return_value);

}
