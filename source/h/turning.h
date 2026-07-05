
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN 

#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>			// Header File For Standard Input/Output
#include <gl\gl.h> 
#include "globals.h" 

void Set_Heading(int loop, float x1, float y1, bool hulk_ladder);
void Turn_Unit(int loop, int f_rate);

void Set_Heading(int loop, float x1, float y1, bool hulk_ladder)
{ 
    float old_angle  = 0.0;  
    float midX=0.0f, midY=0.0f;  
    float new_angle=0.0f;    
    float angle_diff=0.0f;
    int old_direction=0; 
    int new_direction=0;      
    bool skip_this = false;

	if(loop < 0)
		return;
      
	if(STA2_MODE == MODE_AIMING) //  || STA2_MODE == MODE_TARGET
    if(loop == ply_id && ply_id != -1)
    {
        x1 = mouseX;  
        y1 = mouseY;    
    }
    
    old_angle = (float)Convert_Angle_To_Dir(sprite[loop].angle);
    
    old_direction = Convert_Angle_To_Dir(sprite[loop].angle);
    
    midX = sprite[loop].w+sprite[loop].box_width/2;
    midY = sprite[loop].z+sprite[loop].box_height/2;
   
    if( Node_Distance1(midX, midY, x1, y1) > 0.015f )  // Stop spinning when reached target
    {
          
		new_angle = atan2(y1 - midY,x1 - midX);    
       
		new_direction = Convert_Angle_To_Dir(new_angle);
    
		if(loop == ply_id)
			ply_direction = new_direction;
    
		angle_diff = new_angle - old_angle;
    
		if(angle_diff < 0) 
			angle_diff *= -1;
          
		if(ply_id != -1) 
		if(loop == ply_id)    
		{
			if(Is_Grey_Area(new_angle)==true)
				skip_this = true;
      
			if(mouseheld == false )    
				skip_this = false;  

		}
    
		if(loop != -1) 
		if(sprite[loop].on_ladder == true)
			skip_this = true; 
    
		if(skip_this == false)
		if(new_direction != old_direction && skip_this == false || loop == ply_id)         
		{ 
        
			sprite[loop].tar_angle = new_angle;   
           
		}
		else 
		{ 
			sprite[loop].angle = new_angle;
			sprite[loop].tar_angle = sprite[loop].angle;
		}
        
    } 
    
} 

void Turn_Unit(int loop, int f_rate)
{
    int old_direction=0;    
    int new_direction=0;  
    int quadrant=0; 
    int quadrant1=0;   
    bool skip_this=false; 
    float turn_spd=0.2f;
    int original_direction = 0;
    float mid_x=0.0f, mid_y=0.0f;

	if(loop < 0)
		return;

	if(f_rate <= 0)
	    f_rate = 1; 
    
    original_direction = Convert_Angle_To_Dir(sprite[loop].angle);
    
    if(sprite[loop].sector == UNIT_MORTAR1)  
        turn_spd = (float)mortar1_trn;     
    if(sprite[loop].sector == UNIT_GUNNER)  
        turn_spd = (float)gunner_trn; 
    if(sprite[loop].sector == UNIT_SHOTGUN)  
        turn_spd = (float)shotgun_trn;         
    if(sprite[loop].sector == UNIT_MONKEY)  
        turn_spd = (float)monkey_trn;   
    if(sprite[loop].sector == UNIT_DOG)  
        turn_spd = (float)dog_trn;     
    if(sprite[loop].sector == UNIT_BOX)  
        turn_spd = (float)dog_trn;                   
    if(sprite[loop].sector == UNIT_SHIELD)  
        turn_spd = (float)shield_trn;         
    if(sprite[loop].sector == UNIT_DUCK)  
        turn_spd = (float)gunner_trn;         
    if(sprite[loop].sector == UNIT_BOMBER) 
    { 
        if(sprite[loop].onDeath_action != TANK_TOP)                   
            turn_spd = (float)bomber_trn;    
        else
            turn_spd = (float)tank_trn;    
    }
    if(sprite[loop].sector == UNIT_CHIEF)
        turn_spd = (float)chief_trn;
    if(sprite[loop].sector == UNIT_SAILOR)
        turn_spd = (float)sailor_trn;
    if(sprite[loop].sector == UNIT_GRUNT)
        turn_spd = (float)grunt_trn;       
    if(sprite[loop].sector == UNIT_MACHINE)
        turn_spd = (float)machine_trn; 
    if(sprite[loop].sector == UNIT_GUARD)
        turn_spd = (float)machine_trn;                  
    if(sprite[loop].sector == UNIT_WORKER)
        turn_spd = (float)worker_trn;
    if(sprite[loop].sector == UNIT_RESCUE)
        turn_spd = (float)rescue_trn;      
    if(sprite[loop].sector == UNIT_MOUNTED)
        turn_spd = (float)mounted_trn;
    if(sprite[loop].sector == UNIT_MORTAR)
        turn_spd = (float)mortar_trn;        
    if(sprite[loop].sector == UNIT_SNIPER)
        turn_spd = (float)sniper_trn;
    if(sprite[loop].sector == UNIT_TANK)  
        turn_spd = (float)tank_trn; 
    if(sprite[loop].sector == UNIT_BIRD)  
        turn_spd = (float)plane_trn;
    if(sprite[loop].sector == UNIT_SKELETON)  
        turn_spd = (float)skeleton_trn;  
    if(sprite[loop].sector == UNIT_DEAD_CHIEF)
        turn_spd = (float)dead_chief_trn;  
    if(sprite[loop].sector == UNIT_SHARK)  
        turn_spd = (float)shark_trn; 

    if(ply_id != -1)                 
    if(loop == ply_id)  
    {  
        if(sprite[loop].fire_target != -1 || throw_grenade == true)
            turn_spd = (float)player_trn*1.5f;          
        else    
            turn_spd = (float)player_trn;          
    }                                           
    
    if(sprite[loop].on_mud == true) 
        turn_spd -= 0.001f;     
        
    turn_spd *= (float)f_rate;
     
    for(float i=0.0;i<turn_spd;i+=turn_spd/8) 
    {                 
    if(sprite[loop].angle > 1.5f && sprite[loop].angle < 3.14f && sprite[loop].tar_angle < -1.5f)
    {
        sprite[loop].angle += i; 
        
        skip_this=true; 
        
        if(sprite[loop].angle > 3.14f)
            sprite[loop].angle = -3.14f - ( 3.14f - sprite[loop].angle);
    }
    if(sprite[loop].tar_angle > 1.5f && sprite[loop].tar_angle < 3.14f && sprite[loop].angle < -1.5f)
    {
        sprite[loop].angle -= i;
        
        skip_this=true; 
        
        if(sprite[loop].angle < -3.14f)
            sprite[loop].angle = 3.14f + ( 3.14f + sprite[loop].angle);
    }

    if( skip_this==false)  
    {  
      if(sprite[loop].angle < sprite[loop].tar_angle)
        sprite[loop].angle += i;
        
      if(sprite[loop].angle > sprite[loop].tar_angle)
        sprite[loop].angle -= i; 
    }    
    
    old_direction = Convert_Angle_To_Dir(sprite[loop].angle);
       
    new_direction = Convert_Angle_To_Dir(sprite[loop].tar_angle);
    
    if(old_direction == new_direction)   
    {
        sprite[loop].angle = sprite[loop].tar_angle;
        break; 
    } 
  
    }
    
    if(sprite[loop].status != GROUND_SPAWN)
    if(original_direction != old_direction)  
    {
        sprite[loop].update = true;     
        sprite[loop].anim_state = WAIT;  
              
    }
         
}
