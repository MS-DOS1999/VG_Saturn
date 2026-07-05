
//#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#ifdef SWITCH
//#include <gl\gl.h>
#endif
#include <math.h>
#include "texture.h"											// Header File Containing Our Texture Structure ( NEW )
#include "globals.h"
//#include "audiere.h"

extern bool New_FX(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int i_value, int i_type, int state, int linked_sprite, int tex_id, int i_value1, int i_value2, int i_value3);
 
void Animation_System(int loop, bool bullet_check, bool interrupt, bool pain_anim, bool fire);
void Animate(int loop, int type);
void Set_Sprite(int id, int anim, int state, int hud_or_sprite, bool reset);
 
void Set_Sprite(int id, int anim, int state, int hud_or_sprite, bool reset)
{        

	 if(anim < 0)
		 return;

	 if(game_paused == false)   
	 if(id >= 0)
	 {
	  	      
     if(hud_or_sprite==ANIM_HUD)  
	 if(id >= 0 && id < TOTAL_NO_HUD)
	 if(hud[id].fx_id >= 0 && hud[id].fx_id < 75)
	 if(hud[id].anim >= 0 && hud[id].anim < 256)
	 if(hud[id].cur >= 0 && hud[id].cur < 256)
     {   
         if(hud[id].anim != anim || reset == ANIM_WALKING)
         {     
             hud[id].anim = anim;  
             hud[id].cur = 0;  
             hud[id].cur_time = 0; 
             hud[id].anim_state = state; 
         }  
#ifndef DREAMCAST
	     hud[id].frame = a_texture[hud[id].fx_id].anims[hud[id].anim][hud[id].cur];
#else
         hud[id].frame = a_texture_get_anims_secondlayer(hud[id].fx_id, hud[id].anim, hud[id].cur);
#endif

         hud[id].anim_state = state;         
		  
     }   

     if(hud_or_sprite == ANIM_SPRITE)             
	 if(id >= 0 && id < TOTAL_NO_SPRITES)
	 if(sprite[id].fx_id >= 0 && sprite[id].fx_id < 75)
	 if(sprite[id].anim >= 0 && sprite[id].anim < 256)
	 if(sprite[id].cur >= 0 && sprite[id].cur < 256)
     {      
	 	 
         if(sprite[id].anim != anim || reset == ANIM_WALKING) 
         {  

           sprite[id].anim = anim;  
            
           if(state == ONCE ) 
           { 
               sprite[id].cur = 0;
#ifndef DREAMCAST
               sprite[id].cur_time = ((int)TimerGetTime() + (a_texture[sprite[id].fx_id].delay[ (a_texture[sprite[id].fx_id].anims[sprite[id].anim][sprite[id].cur]) ]*(int)VG_slowmof));
#else
               sprite[id].cur_time = ((int)TimerGetTime() + (a_texture_get_delay(sprite[id].fx_id, a_texture_get_anims_secondlayer(sprite[id].fx_id, sprite[id].anim, sprite[id].cur))*(int)VG_slowmof));
#endif
           }     

#ifndef DREAMCAST          
           if(reset == ANIM_WALKING )
           if(sprite[id].cur > (a_texture[sprite[id].fx_id].anim_frames[sprite[id].anim])-1 )
#else
           if(reset == ANIM_WALKING )
           if(sprite[id].cur > (a_texture_get_animsframes(sprite[id].fx_id, sprite[id].anim))-1 )
#endif
           {     

             sprite[id].cur = 0; 
#ifndef DREAMCAST
               sprite[id].cur_time = ((int)TimerGetTime() + (a_texture[sprite[id].fx_id].delay[ (a_texture[sprite[id].fx_id].anims[sprite[id].anim][sprite[id].cur]) ]*(int)VG_slowmof));
#else
               sprite[id].cur_time = ((int)TimerGetTime() + (a_texture_get_delay(sprite[id].fx_id, a_texture_get_anims_secondlayer(sprite[id].fx_id, sprite[id].anim, sprite[id].cur))*(int)VG_slowmof));
#endif
           }     
              
           if(reset == ANIM_NOT_WALKING) 
           { 
                    
             if(game_mode != WALK)                
                 sprite[id].cur = 0;

#ifndef DREAMCAST
               sprite[id].cur_time = ((int)TimerGetTime() + (a_texture[sprite[id].fx_id].delay[ (a_texture[sprite[id].fx_id].anims[sprite[id].anim][sprite[id].cur]) ]*(int)VG_slowmof));
#else
               sprite[id].cur_time = ((int)TimerGetTime() + (a_texture_get_delay(sprite[id].fx_id, a_texture_get_anims_secondlayer(sprite[id].fx_id, sprite[id].anim, sprite[id].cur))*(int)VG_slowmof));
#endif
           }    

		   sprite[id].last_slowmo = VG_slowmof;
		   sprite[id].cur_start_time = (int)TimerGetTime();
#ifndef DREAMCAST
            sprite[id].cur_time = ((int)TimerGetTime() + (a_texture[sprite[id].fx_id].delay[ (a_texture[sprite[id].fx_id].anims[sprite[id].anim][sprite[id].cur]) ]*(int)VG_slowmof));
#else
            sprite[id].cur_time = ((int)TimerGetTime() + (a_texture_get_delay(sprite[id].fx_id, a_texture_get_anims_secondlayer(sprite[id].fx_id, sprite[id].anim, sprite[id].cur))*(int)VG_slowmof));
#endif
		   sprite[id].cur_dest_time = sprite[id].cur_time;
#ifndef DREAMCAST
           sprite[id].frame = a_texture[sprite[id].fx_id].anims[sprite[id].anim][sprite[id].cur];
#else
           sprite[id].frame = a_texture_get_anims_secondlayer(sprite[id].fx_id, sprite[id].anim, sprite[id].cur);
#endif
           sprite[id].anim_state = state;
         
         }
         
     }  

     if(hud_or_sprite == ANIM_FX)       
	 if(id >= 0 && id < TOTAL_NO_FX_SPRITES)
	 if(Fx[id].fx_id >= 0 && Fx[id].fx_id < 75)
	 if(Fx[id].anim >= 0 && Fx[id].anim < 256)
	 if(Fx[id].cur >= 0 && Fx[id].cur < 256)
     {     
         
         if(Fx[id].anim != anim || reset == ANIM_WALKING)  
         { 
            
           Fx[id].anim = anim;  
#ifndef DREAMCAST
           if(reset == ANIM_WALKING )
           if(Fx[id].cur >= (a_texture[Fx[id].fx_id].anim_frames[Fx[id].anim])-1 )
#else
           if(reset == ANIM_WALKING )
           if(Fx[id].cur >= (a_texture_get_animsframes(Fx[id].fx_id, Fx[id].anim))-1 )
#endif
           {
             Fx[id].cur = 0;
#ifndef DREAMCAST
             Fx[id].cur_time = ((int)TimerGetTime() + (a_texture[Fx[id].fx_id].delay[ (a_texture[Fx[id].fx_id].anims[Fx[id].anim][Fx[id].cur]) ]));
#else
             Fx[id].cur_time = ((int)TimerGetTime() + (a_texture_get_delay(Fx[id].fx_id, a_texture_get_anims_secondlayer(Fx[id].fx_id, Fx[id].anim, Fx[id].cur))));
#endif
           }     
              
           if(reset == ANIM_NOT_WALKING)
           { 
             Fx[id].cur = 0; 
             Fx[id].cur_time=0;    
#ifndef DREAMCAST
             Fx[id].cur_time = ((int)TimerGetTime() + (a_texture[Fx[id].fx_id].delay[ (a_texture[Fx[id].fx_id].anims[Fx[id].anim][Fx[id].cur]) ]));
#else
             Fx[id].cur_time = ((int)TimerGetTime() + (a_texture_get_delay(Fx[id].fx_id, a_texture_get_anims_secondlayer(Fx[id].fx_id, Fx[id].anim, Fx[id].cur))));
#endif
           }   
             
#ifndef DREAMCAST
           Fx[id].frame = a_texture[Fx[id].fx_id].anims[Fx[id].anim][Fx[id].cur];
#else
           Fx[id].frame = a_texture_get_anims_secondlayer(Fx[id].fx_id, Fx[id].anim, Fx[id].cur);
#endif
           Fx[id].anim_state = state;
         
         }
               
     } 
	       
	 }   // id != -1
	 
	 
}   
  
void Animate(int loop, int type) 
{ 
     int index=0; 
     bool player_moving_back=false;
     float temp_cur_time=0.0f; 
     int new_no_spritesT = 0;
     int hud_no_spritesT = 0;

	 new_no_spritesT = new_no_sprites;
	 hud_no_spritesT = hud_no_sprites; 

	 if(type == ANIM_SPRITE)  
	 {
	     new_no_spritesT = 1;
	 }
	 	 
	 if(type == ANIM_HUD)   
     if(loop != -1)
	 {  
	     hud_no_spritesT = 1;
	 }
     
        // ******************************************************************************//
        //                              Animation System                                 //                     
        // ******************************************************************************//
  		    if(game_paused == false)
  		    if(type != ANIM_SPRITE)
            for(int i=0;i<hud_no_spritesT;i++) 
            {   

            index = i;

            if(loop != -1)
                index = loop;

			if(index >= 0 && index < TOTAL_NO_HUD)
			if(hud[index].id >= 0 && hud[index].id < 200)   
			if(hud[index].fx_id >= 0 && hud[index].fx_id < 75)
			if(hud[index].anim >= 0 && hud[index].anim < 256)
			if(hud[index].cur >= 0 && hud[index].cur < 256)
            if ( texture_fx[hud[index].id] == 2 || texture_fx[hud[index].id] == 3 || texture_fx[hud[index].id] == 4)
            if ( hud[index].anim_state != WAIT && (int)TimerGetTime() > hud[index].cur_time )
            {   
#ifndef DREAMCAST
                hud[index].frame = a_texture[hud[index].fx_id].anims[hud[index].anim][hud[index].cur];
#else
                hud[index].frame = a_texture_get_anims_secondlayer(hud[index].fx_id, hud[index].anim, hud[index].cur);
#endif
                if(a_texture[hud[index].fx_id].rythm == 0) 
				{
					hud[index].cur_start_time = (int)TimerGetTime();
#ifndef DREAMCAST
                    hud[index].cur_time = ((int)TimerGetTime() + (a_texture[hud[index].fx_id].delay[(a_texture[hud[index].fx_id].anims[hud[index].anim][hud[i].cur])]*(int)VG_slowmof) );
#else
                    hud[index].cur_time = ((int)TimerGetTime() + (a_texture_get_delay(hud[index].fx_id, a_texture_get_anims_secondlayer(hud[index].fx_id, hud[index].anim, hud[i].cur))*(int)VG_slowmof) );
#endif
				}
                     
#ifndef DREAMCAST   
                if(hud[index].cur < ((a_texture[hud[index].fx_id].anim_frames[hud[index].anim])-1) )
#else
                if(hud[index].cur < ((a_texture_get_animsframes(hud[index].fx_id, hud[index].anim))-1) )
#endif
                {
                    hud[index].cur++;  
                }
                else  
                {
                    if(hud[index].anim_state==PLAY)
                    {
                        hud[index].anim_state=WAIT;
                    }
                    if(hud[index].anim_state==LOOP)
                        hud[index].cur=0;
                }
                
              } 
              
            }  

            if(game_paused == false)
            if(animate_sprites == true && (quit_active == false || game_mode == FRONT) )
            for(int i=0;i<new_no_spritesT;i++) 
            {  
         
            index = var5[i];  
            
            if(var5[i] >= TOTAL_NO_SPRITES)   
            {
                index = var5[i] - TOTAL_NO_SPRITES;            
            }  
            
            if(loop != -1) 
                index = loop;
#ifndef DREAMCAST
			if(index >= 0 && index < TOTAL_NO_SPRITES)
			if(sprite[index].id >= 0 && sprite[index].id < 200)   
			if(sprite[index].fx_id >= 0 && sprite[index].fx_id < 75)
			if(sprite[index].anim >= 0 && sprite[index].anim < 256)
			if(sprite[index].cur >= 0 && sprite[index].cur < 256)
	            sprite[index].frame = a_texture[sprite[index].fx_id].anims[sprite[index].anim][sprite[index].cur];
#else
            if(index >= 0 && index < TOTAL_NO_SPRITES)
            if(sprite[index].id >= 0 && sprite[index].id < 200)   
            if(sprite[index].fx_id >= 0 && sprite[index].fx_id < 75)
            if(sprite[index].anim >= 0 && sprite[index].anim < 256)
            if(sprite[index].cur >= 0 && sprite[index].cur < 256)
                sprite[index].frame = a_texture_get_anims_secondlayer(sprite[index].fx_id, sprite[index].anim, sprite[index].cur);
#endif
      
			if(index >= 0 && index < TOTAL_NO_SPRITES)
			if(sprite[index].id >= 0 && sprite[index].id < 200)   
			if(sprite[index].fx_id >= 0 && sprite[index].fx_id < 75)
			if(sprite[index].anim >= 0 && sprite[index].anim < 256)
			if(sprite[index].cur >= 0 && sprite[index].cur < 256)
			if( texture_fx[sprite[index].id] == 2 || texture_fx[sprite[index].id] == 3 || texture_fx[sprite[index].id] == 4)
            if( (int)TimerGetTime() > sprite[index].cur_time )
            if( sprite[index].anim_state != WAIT && sprite[index].anim_state != NO_ANIM) 
            {                                          
                
                if(sprite[index].walking_backwards == false)
                {
#ifndef DREAMCAST
                    if(sprite[index].cur < (a_texture[sprite[index].fx_id].anim_frames[sprite[index].anim])-1 )
#else
                    if(sprite[index].cur < (a_texture_get_animsframes(sprite[index].fx_id, sprite[index].anim))-1 )
#endif
                    {   
                        sprite[index].cur++; 
                    } 
                    else        
                    {  
                        if(sprite[index].anim_state==PLAY)   
                        {
                            sprite[index].anim_state=WAIT; 
                        } 
                        if(sprite[index].anim_state==LOOP)  
                        {
                            sprite[index].cur=0; 
                        }
                        if(sprite[index].anim_state==ONCE)
                        {
                            sprite[index].anim_state = NO_ANIM;                   
                        } 

                    } 
                }
                     
                if(sprite[index].walking_backwards == true)
                { 
                    if(sprite[index].cur > 0 )
                    {    
                        sprite[index].cur--;
                    } 
                    else      
                    { 
                        if(sprite[index].anim_state==PLAY)
                        {
                            sprite[index].anim_state=WAIT;
                        } 
                        if(sprite[index].anim_state==LOOP)
                        {
#ifndef DREAMCAST
                            sprite[index].cur=(a_texture[sprite[index].fx_id].anim_frames[sprite[index].anim])-1;
#else
                            sprite[index].cur=(a_texture_get_animsframes(sprite[index].fx_id, sprite[index].anim))-1;
#endif
                        }
                        if(sprite[index].anim_state==ONCE)
                        {
                            sprite[index].anim_state = NO_ANIM;                   
                        } 
                    }
                }     

				sprite[index].last_slowmo = VG_slowmof;
				sprite[index].cur_start_time = (int)TimerGetTime();
#ifndef DREAMCAST
                sprite[index].cur_time = ((int)TimerGetTime() + (a_texture[sprite[index].fx_id].delay[ (a_texture[sprite[index].fx_id].anims[sprite[index].anim][sprite[index].cur]) ]*(int)VG_slowmof) );
#else
                sprite[index].cur_time = ((int)TimerGetTime() + (a_texture_get_delay(sprite[index].fx_id, a_texture_get_anims_secondlayer(sprite[index].fx_id, sprite[index].anim, sprite[index].cur))*(int)VG_slowmof) );
#endif
				sprite[index].cur_dest_time = sprite[index].cur_time;

#ifndef DREAMCAST
                sprite[index].frame = a_texture[sprite[index].fx_id].anims[sprite[index].anim][sprite[index].cur];
#else
                sprite[index].frame = a_texture_get_anims_secondlayer(sprite[index].fx_id, sprite[index].anim, sprite[index].cur);
#endif
                
            } 
          
         }          

		    if(game_paused == false)
            if(type != ANIM_SPRITE)
            if(animate_sprites == true && quit_active == false)
            for(int i=0;i<no_fx;i++) // was no_sprites
            {     
                     
            index = i; 
#ifndef DREAMCAST
			if(index >= 0 && index < TOTAL_NO_FX_SPRITES)
			if(Fx[index].id >= 0 && Fx[index].id < 200)   
			if(Fx[index].fx_id >= 0 && Fx[index].fx_id < 75)
			if(Fx[index].anim >= 0 && Fx[index].anim < 256)
			if(Fx[index].cur >= 0 && Fx[index].cur < 256)          
            	Fx[index].frame = a_texture[Fx[index].fx_id].anims[Fx[index].anim][Fx[index].cur];
#else
            if(index >= 0 && index < TOTAL_NO_FX_SPRITES)
            if(Fx[index].id >= 0 && Fx[index].id < 200)   
            if(Fx[index].fx_id >= 0 && Fx[index].fx_id < 75)
            if(Fx[index].anim >= 0 && Fx[index].anim < 256)
            if(Fx[index].cur >= 0 && Fx[index].cur < 256)          
                Fx[index].frame = a_texture_get_anims_secondlayer(Fx[index].fx_id, Fx[index].anim, Fx[index].cur);
#endif

			if(index >= 0 && index < TOTAL_NO_FX_SPRITES)
			if(Fx[index].id >= 0 && Fx[index].id < 200)   
			if(Fx[index].fx_id >= 0 && Fx[index].fx_id < 75)
			if(Fx[index].anim >= 0 && Fx[index].anim < 256)
			if(Fx[index].cur >= 0 && Fx[index].cur < 256)      
            if ( texture_fx[Fx[index].id] == 2 || texture_fx[Fx[index].id] == 3 || texture_fx[Fx[index].id] == 4)
            if ( (int)TimerGetTime() > Fx[index].cur_time )
            if( Fx[index].anim_state != WAIT && Fx[index].anim_state != NO_ANIM)
            {                                       
#ifndef DREAMCAST
                Fx[index].cur_time = ((int)TimerGetTime() + (a_texture[Fx[index].fx_id].delay[ (a_texture[Fx[index].fx_id].anims[Fx[index].anim][Fx[index].cur]) ]) ); // *(int)VG_slowmof
                if(Fx[index].cur < (a_texture[Fx[index].fx_id].anim_frames[Fx[index].anim])-1 )
#else
                Fx[index].cur_time = ((int)TimerGetTime() + (a_texture_get_delay(Fx[index].fx_id, a_texture_get_anims_secondlayer(Fx[index].fx_id, Fx[index].anim, Fx[index].cur))) );
                if(Fx[index].cur < (a_texture_get_animsframes(Fx[index].fx_id, Fx[index].anim))-1 )
#endif
                {
                    Fx[index].cur++;
                } 
                else      
                {  
                    if(Fx[index].anim_state==PLAY)
                    {
                        Fx[index].anim_state=WAIT;
                    } 
                    if(Fx[index].anim_state==LOOP)
                    {
                        Fx[index].cur=0; 
                    }
                    if(Fx[index].anim_state==ONCE)
                        Fx[index].anim_state = NO_ANIM;                   
                }
             
            }       
                
       }   
 
} 

// ******************************************************************************//
//                                Animation System                               //
// ******************************************************************************//
     	
void Animation_System(int loop, bool bullet_check, bool interrupt, bool pain_anim, bool fire) 
{ 

}  

