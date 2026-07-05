
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN 

#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>			// Header File For Standard Input/Output
#include <gl\gl.h> 
#include "globals.h" 
     

void Run_Map(int f_rate, int type)
{ 
  
	if(f_rate <= 0)
	    f_rate = 1; 
 
       sprintf( counter[5].word, "");
    
       sprite[13].alpha = 0.0;
       sprite[14].alpha = 0.0;
       sprite[15].alpha = 0.0;
       
       if(map_type == MAP_BETSY)
           sprite[13].alpha = 1.0; 
        
       if(map_type == MAP_BOATYARD)
           sprite[14].alpha = 1.0;
                   
       if(map_type == MAP_CLIFFS)
           sprite[15].alpha = 1.0;
/*           
       // Cliff tunnel activated...    
       if(global_objects[13] == GLOBAL_BEATEN)
           Set_Sprite(12, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
       
       // Boatyard activated...    
       if(global_objects[14] == GLOBAL_BEATEN)
           Set_Sprite(11, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                  
       // Bay area activated...
       if(main_mission[MISSION_SPY] == FINISHED) 
           Set_Sprite(9, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
       
       // Beach area activated...
       if(main_mission[MISSION_SUPPLIES] == FINISHED) 
           Set_Sprite(7, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);       
*/
      
       counter[3].x = -0.85f;    
       counter[3].y =  0.60f;  
       counter[3].width = 0.015f;
       counter[3].height = 0.030f;
                 
       sprintf( counter[3].word, "YOUR_MISSION!^^The_damned_Black_Army^has_invaded_our^coastline._It&s^up_to_a_few_brave^soldiers_to_hold_them_off.^^We&re_counting_on^you_men.^^General_Baker.");
       
       // Buttons - EXIT
       if(( mouseX < (sprite[2].w + sprite[2].box_width) )
       &&( mouseX > sprite[2].w)                             
       &&( mouseY < (sprite[2].z + sprite[2].box_height) )
       &&( mouseY > sprite[2].z)) 
       {
           
           Set_Sprite(2, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
           
           if(mouseleft == true)
           {
               episode = 2;          
               scene   = 0; 

                    scene = 0; 
                           
               current_spawn = 27; 
                                       
               next_scene = true;
               
               mouseleft = false;            
           }
           
                      
       }
       else
           Set_Sprite(2, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // BUY SIGN   


       // Buttons - EXIT
       if(sprite[10].grab_switch == true)
       if(( mouseX < (sprite[10].w + sprite[10].box_width) )
       &&( mouseX > sprite[10].w)                            
       &&( mouseY < (sprite[10].z + sprite[10].box_height) )
       &&( mouseY > sprite[10].z)) 
       {
           sprintf( counter[5].word, "Summer^Camp");
           counter[5].length = 1; 
           msg_left=true;  
       }
 
       // Buttons - EXIT
       if(sprite[7].grab_switch == true)
       if(( mouseX < (sprite[7].w + sprite[7].box_width) )
       &&( mouseX > sprite[7].w)                            
       &&( mouseY < (sprite[7].z + sprite[7].box_height) )
       &&( mouseY > sprite[7].z)) 
       {
           sprintf( counter[5].word, "Pebble^Beach");
           counter[5].length = 1; 
           msg_left=true;  
       }
 
       // Buttons - EXIT
       if(sprite[12].grab_switch == true)
       if(( mouseX < (sprite[12].w + sprite[12].box_width) )
       &&( mouseX > sprite[12].w)                            
       &&( mouseY < (sprite[12].z + sprite[12].box_height) )
       &&( mouseY > sprite[12].z)) 
       {
           sprintf( counter[5].word, "Cliffs");
           counter[5].length = 0; 
           msg_left=true;  
       }
 
       // Buttons - EXIT
       if(sprite[9].grab_switch == true)
       if(( mouseX < (sprite[9].w + sprite[9].box_width) )
       &&( mouseX > sprite[9].w)                            
       &&( mouseY < (sprite[9].z + sprite[9].box_height) )
       &&( mouseY > sprite[9].z)) 
       {
           sprintf( counter[5].word, "Pebble_Bay");
           counter[5].length = 0; 
           msg_left=true;  
       }       
 
       // Buttons - EXIT 
       if(sprite[11].grab_switch == true)
       if(( mouseX < (sprite[11].w + sprite[11].box_width) )
       &&( mouseX > sprite[11].w)                            
       &&( mouseY < (sprite[11].z + sprite[11].box_height) )
       &&( mouseY > sprite[11].z)) 
       {
           sprintf( counter[5].word, "Boatyard");
           counter[5].length = 0; 
           msg_left=true;  
       }   
 
       // Buttons - EXIT
       if(sprite[8].grab_switch == true)
       if(( mouseX < (sprite[8].w + sprite[8].box_width) )
       &&( mouseX > sprite[8].w)                            
       &&( mouseY < (sprite[8].z + sprite[8].box_height) )
       &&( mouseY > sprite[8].z)) 
       {
           sprintf( counter[5].word, "Pebble_Dam");
           counter[5].length = 0; 
           msg_left=true;  
       }          
       
              
       

}
