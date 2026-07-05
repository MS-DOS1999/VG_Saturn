#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
//#include "nl.h" 

#if defined WIN32 || defined WIN64 
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif 

float GetSFXPan(int index, float x, float y);
float GetSFXFactor(int index, float x, float y, int sound_type);
void Surround_Sound(int ping_type, int ping_value, int ping_value1, float x, float y);


void Surround_Sound(int sprite_index, int sound_type, float x, float y)
{

//	if(sprite_index < 0) 
//	    return;

	if(sound_type == SFX_PISTOL) 
    { 
    	death_sfx = true; 
        pistol_sfx_pan = GetSFXPan(sprite_index, x, y);
        pistol_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_PISTOL);
    }
	if(sound_type == SFX_RIFLE)  
    {  
    	sniperply_sfx = true;
        sniperply_sfx_pan = GetSFXPan(sprite_index, x, y);
        sniperply_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_RIFLE);
    }
	if(sound_type == SFX_CHOP)   
    { 
    	chop_sfx = true; 
        chop_sfx_pan = GetSFXPan(sprite_index, x, y);
        chop_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_CHOP);
    }
	if(sound_type == SFX_GRENADE)    
    {  
    	ready_sfx = true; 
        grenade_sfx_pan = GetSFXPan(sprite_index, x, y);
        grenade_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_GRENADE);
    }
	if(sound_type == SFX_BOMB)     
    { 
    	clank_sfx = true; 
        bomb_sfx_pan = GetSFXPan(sprite_index, x, y);
        bomb_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_BOMB);
    }
	if(sound_type == SFX_PAIN_GIRL)        
    { 
   		girl_hit_sfx = true;   
    //    pain_sfx_pan = GetSFXPan(sprite_index, x, y);
    //    pain_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_PAIN_GIRL);
    }
	if(sound_type == SFX_PAIN)      
    { 
   		wound_sfx = true;   
    //    pain_sfx_pan = GetSFXPan(sprite_index, x, y);
    //    pain_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_PAIN);
    }
	if(sound_type == SFX_SPLATTED)        
    { 
    	splatted_sfx = true; 
   //     splatted_sfx_pan = GetSFXPan(sprite_index, x, y);
    //    splatted_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_SPLATTED);
    }
	if(sound_type == SFX_DEATH)      
    { 
    	step_sfx = true;  
        step_sfx_pan = GetSFXPan(sprite_index, x, y);
        step_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_DEATH);
    }
	if(sound_type == SFX_DEATH_GIRL)       
    { 
    	girl_die_sfx = true;  
    //    step_sfx_pan = GetSFXPan(sprite_index, x, y);
    //    step_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_DEATH);
    }
	if(sound_type == SFX_GARGLE)      
    { 
    	gargle_sfx = true;  
        gargle_sfx_pan = GetSFXPan(sprite_index, x, y);
        gargle_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_GARGLE);
    }
	if(sound_type == SFX_DESTROY)      
    { 
    	destroy_sfx = true;  
        destroy_sfx_pan = GetSFXPan(sprite_index, x, y);
        destroy_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_DESTROY);
    } 
	if(sound_type == SFX_DROWN)      
    {  
    	drown_sfx = true;   
        drown_sfx_pan = GetSFXPan(sprite_index, x, y);
        drown_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_DROWN);
    } 
	if(sound_type == SFX_SMASH)      
    {  
    	smash1_sfx = true;   
        smash_sfx_pan = GetSFXPan(sprite_index, x, y);
        smash_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_SMASH);
    } 
	if(sound_type == SFX_EMYPAIN)      
    {   
    	emypain_sfx = true;   
        emypain_sfx_pan = GetSFXPan(sprite_index, x, y);
        emypain_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_EMYPAIN);
    } 
	if(sound_type == SFX_TADA)       
    {   
    	tada_sfx = true;   
        tada_sfx_pan = GetSFXPan(sprite_index, x, y);
        tada_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_TADA);
    } 
	if(sound_type == SFX_CROW)       
    {    
    	crow2_sfx = true;    
        crow_sfx_pan = GetSFXPan(sprite_index, x, y);
        crow_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_CROW);
    } 
	if(sound_type == SFX_MONKEY)        
    {   
    	monkey_sfx = true;    
        monkey_sfx_pan = GetSFXPan(sprite_index, x, y);
        monkey_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_MONKEY);
    } 
	if(sound_type == SFX_DOG)         
    {   
    	dogdie_sfx = true;    
        dog_sfx_pan = GetSFXPan(sprite_index, x, y);
        dog_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_DOG);
    } 
	if(sound_type == SFX_CROW1)       
    {    
    	crow1_sfx = true;    
        crow1_sfx_pan = GetSFXPan(sprite_index, x, y);
        crow1_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_CROW1);
    } 
	if(sound_type == SFX_COW)         
    {    
    	cow_sfx = true;    
        cow_sfx_pan = GetSFXPan(sprite_index, x, y);
        cow_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_COW);
    } 
	if(sound_type == SFX_MUDSTEP)       
    {    
    	mudstep_sfx = true;    
        mudstep_sfx_pan = GetSFXPan(sprite_index, x, y);
        mudstep_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_MUDSTEP);
    } 
	if(sound_type == SFX_SOFTSTEP)       
    {    
    	softstep_sfx = true;    
        softstep_sfx_pan = GetSFXPan(sprite_index, x, y);
        softstep_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_SOFTSTEP);
    } 
	if(sound_type == SFX_HARDSTEP)        
    {    
    	hardstep_sfx = true;    
        hardstep_sfx_pan = GetSFXPan(sprite_index, x, y);
        hardstep_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_HARDSTEP);
    }  
	if(sound_type == SFX_GRASSSTEP)        
    {    
    	grassstep_sfx = true;    
        grassstep_sfx_pan = GetSFXPan(sprite_index, x, y);
        grassstep_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_GRASSSTEP);
    } 
	if(sound_type == SFX_FOOTSTEP)         
    {    
    	footstep_sfx = true;    
        footstep_sfx_pan = GetSFXPan(sprite_index, x, y);
        footstep_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_FOOTSTEP);
    } 
	if(sound_type == SFX_SIGHT)         
    {    
    	sight_sfx = true;    
        sight_sfx_pan = GetSFXPan(sprite_index, x, y);
        sight_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_SIGHT);
    } 
	if(sound_type == SFX_MOUNT)            
    {    
    	mount_sfx = true;    
        mount_sfx_pan = GetSFXPan(sprite_index, x, y);
        mount_sfx_factor = GetSFXFactor(sprite_index, x, y, SFX_MOUNT);
    } 




}

float GetSFXPan(int index, float x, float y)
{
    float pan_value = 0.0f;   
    float distance  = 0.0f;
    
    float my_x=0.0f;   
    float others_x=0.0f; 
   
    if(ply_id != -1)     
    {
        if(index != -1)
            others_x = sprite[index].w+sprite[index].box_width/2;     
        else
            others_x = x; 
            
        my_x = sprite[ply_id].w+sprite[ply_id].box_width/2; 
        
        distance = my_x - others_x;

        if( distance >= 0.4f)
            pan_value = 0.3f;
        if( distance >= 1.0f)
            pan_value = 0.5f;
        if( distance >= 1.8f)
            pan_value = 1.0f;
 
        if( distance <= -0.4f)  
            pan_value = -0.3f;
        if( distance <= -1.0f)
            pan_value = -0.5f;   
        if( distance <= -1.8f)
            pan_value = -1.0f;   

             
    }
      
    return(pan_value);      
}
float GetSFXFactor(int index, float x, float y, int sound_type)
{
    float volume_factor = 1.0f;   
    float distance  = 0.0f;
     
    float my_x=0.0f;  
    float my_y=0.0f;
    
    float others_x=0.0f, others_y=0.0f;
      
    if(ply_id != -1)     
    {  
        my_x = sprite[ply_id].w+sprite[ply_id].box_width/2;
        my_y = sprite[ply_id].z+sprite[ply_id].box_height/2;     
        
        if(index != -1) 
        {
            others_x = sprite[index].w+sprite[index].box_width/2; 
            others_y = sprite[index].z+sprite[index].box_height/2;    
        }
        else  
        { 
            others_x = x;  
            others_y = y;   
        }
        
        distance = Node_Distance1(my_x, my_y, others_x, others_y);  
 
        if( distance >= 1.0f) 
            volume_factor = 1.2f;            
        if( distance >= 1.2f)      
            volume_factor = 1.3f;
        if( distance >= 1.4f)
            volume_factor = 1.5f;             
        if( distance >= 1.8f)
            volume_factor = 1.7f;            
        if( distance >= 2.0f)
            volume_factor = 2.0f;                          
        if( distance >= 2.5f) 
            volume_factor = 3.0f; 
        if( distance >= 3.0f) 
            volume_factor = 4.0f; 
        if( distance >= 3.5f) 
            volume_factor = 5.0f;  
        if( distance >= 4.0f) 
            volume_factor = 6.0f; 

		// Do vibrate...
		#if INCLDUE_360_CONTROLLER  == 1
		if(CONTROLLER) 
		if(sound_type == SFX_GRENADE || sound_type == SFX_BOMB) 
		{
			if(distance <= 0.3)
			{ 
				VIBRATE_LEFT(48000, 150); 
				VIBRATE_RIGHT(48000, 150);
			}
			if(distance > 0.3 && distance <= 0.5)
			{
				VIBRATE_LEFT(36000, 150); 
				VIBRATE_RIGHT(36000, 150);
			}
			if(distance > 0.5 && distance <= 0.7)
			{
				VIBRATE_LEFT(24000, 150); 
				VIBRATE_RIGHT(24000, 150); 
			}
			if(distance > 0.7 && distance <= 1.0)
			{
				VIBRATE_LEFT(12000, 150); 
				VIBRATE_RIGHT(12000, 150);
			}
		}
		#endif

             
    }
      
    return(volume_factor);      
}
