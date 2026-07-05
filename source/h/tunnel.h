
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN 

#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>			// Header File For Standard Input/Output
#include <gl\gl.h> 
#include "globals.h" 

extern void Message_Limits();
 
int drip_timer=0;  
 
void Run_Tunnel(int f_rate)
{
	if(f_rate <= 0)
	    f_rate = 1; 
               
     if(tunnel_sequence == 0)  
     {    
     
         // Open up certain tunnels...
        
     /*    global_objects[14] = GLOBAL_BEATEN; // "Pebble^Beach"
         global_objects[40] = GLOBAL_BEATEN; // "Church"
         global_objects[47] = GLOBAL_BEATEN; // "Vineyard"
        
         global_objects[13] = GLOBAL_BEATEN; // "Light^House"
         global_objects[41] = GLOBAL_BEATEN; // "Grave^Yard"
         global_objects[46] = GLOBAL_BEATEN; // "River^Bank"  */
                
         sprite[15].alpha = 0.0;
         sprite[16].alpha = 0.0;
         sprite[17].alpha = 0.0;

		 if(current_main >= 0)           
         if(main_mission[current_main] == IN_PROGRESS) 
         { 
           if(tunnel_page == 1)
           if(current_main == MISSION_SPY)
           if(global_objects[14] == GLOBAL_BEATEN) 
               sprite[15].alpha = 1.0;  
               
           if(tunnel_page == 1)    
           if(current_main == MISSION_HIGHLANDERS) 
           if(global_objects[13] == GLOBAL_BEATEN)
               sprite[16].alpha = 1.0;   
                
           if(current_main == MISSION_CONVOY) 
           if(global_objects[13] == GLOBAL_BEATEN)
               sprite[16].alpha = 1.0;  
                
           if(tunnel_page == 2)    
           if(current_main == MISSION_REVENGE) 
           if(global_objects[41] == GLOBAL_BEATEN || global_objects[40] == GLOBAL_BEATEN)
           {
               if(global_objects[40] == GLOBAL_BEATEN)
               {                  
                   sprite[15].alpha = 1.0;  
               }                                 
               if(global_objects[41] == GLOBAL_BEATEN)
               {                  
                   sprite[16].alpha = 1.0; 
                   sprite[15].alpha = 0.0; 
               }
           }    
           
           if(tunnel_page == 2)    
           if(current_main == MISSION_CINEMA) 
           if(global_objects[40] == GLOBAL_BEATEN)
           {
               if(global_objects[40] == GLOBAL_BEATEN)
               {                  
                   sprite[15].alpha = 1.0;  
               }                                  
           }                             
           
           if(tunnel_page == 2)    
           if(current_main == MISSION_TRENCH) 
           if(global_objects[41] == GLOBAL_BEATEN || global_objects[40] == GLOBAL_BEATEN)
           {
               if(global_objects[40] == GLOBAL_BEATEN)
               {                  
                   sprite[15].alpha = 1.0;  
               }                                 
               if(global_objects[41] == GLOBAL_BEATEN)
               {                  
                   sprite[16].alpha = 1.0; 
                   sprite[15].alpha = 0.0; 
               }
           } 
                                
           if(tunnel_page == 2)     
           if(current_main == MISSION_FORTRESS) 
           if(global_objects[41] == GLOBAL_BEATEN || global_objects[40] == GLOBAL_BEATEN)
           {
               if(global_objects[40] == GLOBAL_BEATEN)
               {                  
                   sprite[15].alpha = 1.0;  
               }                                 
               if(global_objects[41] == GLOBAL_BEATEN)
               {                  
                   sprite[16].alpha = 1.0; 
                   sprite[15].alpha = 0.0; 
               }
           }  
                               
           if(tunnel_page == 2)     
           if(current_main == MISSION_RAILWAY) 
           if(global_objects[40] == GLOBAL_BEATEN || global_objects[40] == GLOBAL_BEATEN)
           {
               if(global_objects[41] == GLOBAL_BEATEN)
               {                  
                   sprite[16].alpha = 1.0;  
               }                                 
               if(global_objects[40] == GLOBAL_BEATEN)
               {                  
                   sprite[15].alpha = 1.0; 
                   sprite[16].alpha = 0.0; 
               } 
           }                
               
           if(tunnel_page == 1)
           if(current_main == MISSION_FISH) 
               sprite[17].alpha = 1.0;                                                                                                                        
         }          
         
         if(current_act == 2)
         {
             sprite[11].id+=2; // Stunned   
         }
         if(current_act == 3)
         {
             sprite[11].id+=2; // Stunned 
         //    sprite[12].id+=3; // Stunned  
         }
         
         stop_waves_sfx=true;
                  
         tunnel_sequence++;
         
     }          
     
     if(tunnel_sequence == 1)   
     {   
         sprite[3].alpha = 0.0; 
         
         sprite[4].alpha = 0.0; // Back Wall
          
         if(tunnel_page == 1)
         {
             if(global_objects[14] == GLOBAL_BEATEN)
                 Set_Sprite(5, sprite[5].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned
                 
             if(global_objects[13] == GLOBAL_BEATEN)
                 Set_Sprite(6,  sprite[6].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned         
                 
             if(global_objects[3] == GLOBAL_BEATEN)
                 Set_Sprite(7,  sprite[7].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned         
                 
             if(global_objects[16] == GLOBAL_BEATEN)
                 Set_Sprite(8,  sprite[8].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned         
         }
         
         if(tunnel_page == 2)  
         {
             if(global_objects[40] == GLOBAL_BEATEN)
                 Set_Sprite(5, sprite[5].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned
                 
             if(global_objects[41] == GLOBAL_BEATEN)
                 Set_Sprite(6,  sprite[6].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned         
                 
             if(global_objects[42] == GLOBAL_BEATEN)
                 Set_Sprite(7,  sprite[7].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned         
                 
             if(global_objects[43] == GLOBAL_BEATEN)
                 Set_Sprite(8,  sprite[8].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned         
         }        
         
         if(tunnel_page == 3)    
         {
             if(global_objects[47] == GLOBAL_BEATEN)
                 Set_Sprite(5, sprite[5].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned
                 
             if(global_objects[46] == GLOBAL_BEATEN)
                 Set_Sprite(6,  sprite[6].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned         
                 
             if(global_objects[48] == GLOBAL_BEATEN)
                 Set_Sprite(7,  sprite[7].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned         
                 
             if(global_objects[49] == GLOBAL_BEATEN)
                 Set_Sprite(8,  sprite[8].base_anim+1, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned         
         }            
         
         tunnel_sequence_timer = (int)TimerGetTime() + 4000;
         tunnel_sequence++;                   
     }
     if(tunnel_sequence == 2)
     if((int)TimerGetTime() > tunnel_sequence_timer)
     {
         sprite[3].alpha = 1.0;
         
         Set_Sprite(3, 0, PLAY, ANIM_SPRITE, ANIM_WALKING); // Stunned                      
         tunnel_sequence_timer = (int)TimerGetTime() + 200;
         
         drip_sfx = true;
         
         tunnel_sequence++;                                
     }
     if(tunnel_sequence == 3)
     if((int)TimerGetTime() > tunnel_sequence_timer)
     {
         tunnel_sequence = 1;                       
     }
      
     if(!mode && next_scene == false && fade != 0.5)
     {
              
         sprintf( counter[5].word, "");          
                                         
       // Exit Button - EXIT 
       if(( mouseX < (sprite[4].w + sprite[4].box_width) )
       &&( mouseX > sprite[4].w)                            
       &&( mouseY < (sprite[4].z + sprite[4].box_height) )
       &&( mouseY > sprite[4].z)) 
       { 

           sprintf( counter[5].word, "Summer_Camp");
           
           counter[5].length = 0;    
           msg_left=true;   
                 
           if(mouseleft == true)   
           {
               episode = 2;    

               scene = 0;  
                                     
               current_spawn = 2;

               if(current_act != 1)
               if(global_objects[32] == GLOBAL_UNBEATEN) // Act II cutscene
               {
                   episode = 1;
                   scene   = 48;               
               } 
               
               if(current_act == 3)
               if(global_objects[88] == GLOBAL_UNBEATEN) // Act III cutscene
               {
                   episode = 1;
                   scene   = 79;               
               }               
                
               switch_n_sfx = true; 
               next_scene = true;
               mouseleft = false; 
           }   
                     
       }                    
                                         
       // Exit Button - EXIT 
       if(( mouseX < (sprite[5].w + sprite[5].box_width) )
       &&( mouseX > sprite[5].w)                            
       &&( mouseY < (sprite[5].z + sprite[5].box_height) )
       &&( mouseY > sprite[5].z)) 
       {  
  
           sprintf( counter[5].word, "Closed");
           
           counter[5].length = 0;     
           msg_left=true;   
            
           if(tunnel_page == 1)
           {           
               if(global_objects[14] == GLOBAL_BEATEN)
               {               
                   sprintf( counter[5].word, "Pebble^Beach");
                   counter[5].length = 1;    
               }
               
               if(global_objects[14] == GLOBAL_BEATEN)      
               if(mouseleft == true)  
               { 
                   episode = 3;     
                   scene = 3;     
                      
                   current_spawn = 17;
                   
                   switch_n_sfx = true; 
                   next_scene = true;
                   mouseleft = false; 
               }   
           }            
            
           if(tunnel_page == 2)  
           {
               if(global_objects[40] == GLOBAL_BEATEN)
               {               
                   sprintf( counter[5].word, "Cinema");
                   counter[5].length = 0;    
               }
                
               if(global_objects[40] == GLOBAL_BEATEN)
               if(mouseleft == true)  
               {
                   episode = 2;     
                   scene = 13;       
                      
                   current_spawn = 24;
                   
                   switch_n_sfx = true; 
                   next_scene = true;
                   mouseleft = false; 
               }   
           }      

            
           if(tunnel_page == 3) 
           {

               if(global_objects[47] == GLOBAL_BEATEN)
               {               
                   sprintf( counter[5].word, "Vineyard");
                   counter[5].length = 0;    
               }    
                
               if(global_objects[47] == GLOBAL_BEATEN)
               if(mouseleft == true)  
               {
                   episode = 2;    
                   scene = 9;       
                      
                   current_spawn = 7;
                   
                   switch_n_sfx = true; 
                   next_scene = true;
                   mouseleft = false; 
               }                            

           }           
                                
       }                    
                                         
       // Exit Button - EXIT 
       if(( mouseX < (sprite[6].w + sprite[6].box_width) )
       &&( mouseX > sprite[6].w)                            
       &&( mouseY < (sprite[6].z + sprite[6].box_height) )
       &&( mouseY > sprite[6].z)) 
       {  

           sprintf( counter[5].word, "Closed");
           
           counter[5].length = 0;    
           msg_left=true;   
            
           if(tunnel_page == 1)
           {
               if(global_objects[13] == GLOBAL_BEATEN)
               {               
                   sprintf( counter[5].word, "Light^House");
                   counter[5].length = 1;    
               }
               
               if(global_objects[13] == GLOBAL_BEATEN)
               if(mouseleft == true)  
               {
                   episode = 3;    
                   scene = 3;      
                      
                   current_spawn = 2;
                   
                   switch_n_sfx = true; 
                   next_scene = true;
                   mouseleft = false; 
               }    
           }
           
           if(tunnel_page == 2) 
           {           
               if(global_objects[41] == GLOBAL_BEATEN)
               {               
                   sprintf( counter[5].word, "Train^Yard");
                   counter[5].length = 1;    
               }
               
               if(global_objects[41] == GLOBAL_BEATEN)      
               if(mouseleft == true)  
               { 
                   episode = 2;      
                   scene = 13;       
                      
                   current_spawn = 25;
                   
                   switch_n_sfx = true; 
                   next_scene = true;
                   mouseleft = false; 
               }   
           }      
                    
           if(tunnel_page == 3) 
           {
               if(global_objects[46] == GLOBAL_BEATEN)
               {               
                   sprintf( counter[5].word, "River^Bank");
                   counter[5].length = 1;    
               } 
               if(global_objects[46] == GLOBAL_BEATEN)
               if(mouseleft == true)  
               {
                   episode = 2;    
                   scene = 9;       
                      
                   current_spawn = 8;
                   
                   switch_n_sfx = true; 
                   next_scene = true;
                   mouseleft = false; 
               }    
           }             
                             
       }   
                                         
       // Exit Button - EXIT 
       if(( mouseX < (sprite[7].w + sprite[7].box_width) )
       &&( mouseX > sprite[7].w)                            
       &&( mouseY < (sprite[7].z + sprite[7].box_height) )
       &&( mouseY > sprite[7].z)) 
       { 

           sprintf( counter[5].word, "Closed");
           
           counter[5].length = 0;    
           msg_left=false;   
            
           if(tunnel_page == 1)
           {                  
               if(global_objects[3] == GLOBAL_BEATEN)
               {               
                   sprintf( counter[5].word, "Pebble^Bay");
                   counter[5].length = 1;    
               } 
               
               if(global_objects[3] == GLOBAL_BEATEN)      
               if(mouseleft == true)  
               { 
                   episode = 3;      
                   scene = 16;    
                      
                   current_spawn = 0;
                   
                   switch_n_sfx = true; 
                   next_scene = true;
                   mouseleft = false; 
               }   
           }    
            
           if(tunnel_page == 2)
           {                  
               if(global_objects[42] == GLOBAL_BEATEN)
               {               
                   sprintf( counter[5].word, "Palace");
                   counter[5].length = 0;    
               }  
               
               if(global_objects[42] == GLOBAL_BEATEN)      
               if(mouseleft == true)  
               { 
                   episode = 2;      
                   scene = 8;     
                      
                   current_spawn = 1;
                   
                   switch_n_sfx = true; 
                   next_scene = true;
                   mouseleft = false; 
               }   
           } 
            
           if(tunnel_page == 3) 
           {
               if(global_objects[48] == GLOBAL_BEATEN)
               {               
                   sprintf( counter[5].word, "Missile^Silo");
                   counter[5].length = 1;    
               } 
               if(global_objects[48] == GLOBAL_BEATEN)
               if(mouseleft == true)  
               {
                   episode = 2;    
                   scene = 1;        
                      
                   current_spawn = 11;
                   
                   switch_n_sfx = true; 
                   next_scene = true;
                   mouseleft = false; 
               }    
           }            
                            
       }    
                                           
       // Exit Button - EXIT 
       if(( mouseX < (sprite[8].w + sprite[8].box_width) )
       &&( mouseX > sprite[8].w)                            
       &&( mouseY < (sprite[8].z + sprite[8].box_height) )
       &&( mouseY > sprite[8].z)) 
       { 
 
           sprintf( counter[5].word, "Closed");
           
           counter[5].length = 0;    
           msg_left=true;   
           
           if(tunnel_page == 1) 
           {                      
               if(global_objects[16] == GLOBAL_BEATEN)
               {               
                   sprintf( counter[5].word, "Pirate^Ship");
                   counter[5].length = 1;    
               } 
               
               if(global_objects[16] == GLOBAL_BEATEN)      
               if(mouseleft == true)  
               { 
                   episode = 3;    
                   scene = 16;      
                      
                   current_spawn = 8;
                   
                   switch_n_sfx = true; 
                   next_scene = true;
                   mouseleft = false; 
               } 
           }  
           if(tunnel_page == 2)  
           { 
               if(global_objects[43] == GLOBAL_BEATEN)
               {               
                   sprintf( counter[5].word, "Coastal^Town");
                   counter[5].length = 1;    
               } 
               if(global_objects[43] == GLOBAL_BEATEN)
               if(mouseleft == true)  
               {  
                   episode = 2;      
                   scene = 5;         
                      
                   current_spawn = 0;
                   
                   switch_n_sfx = true; 
                   next_scene = true;
                   mouseleft = false; 
               }    
           }               
           if(tunnel_page == 3)  
           {
               if(global_objects[49] == GLOBAL_BEATEN)
               {               
                   sprintf( counter[5].word, "Trench");
                   counter[5].length = 0;    
               } 
               if(global_objects[49] == GLOBAL_BEATEN)
               if(mouseleft == true)  
               { 
                   episode = 3;     
                   scene = 24;         
                      
                   current_spawn = 0;
                   
                   switch_n_sfx = true; 
                   next_scene = true;
                   mouseleft = false; 
               }    
           }              
           
                                
       }   
                
       // Page 1 
       if(sprite[10].grab_switch == true)                 
       if(( mouseX < (sprite[10].w + sprite[10].box_width) )
       &&( mouseX > sprite[10].w)                            
       &&( mouseY < (sprite[10].z + sprite[10].box_height) )
       &&( mouseY > sprite[10].z)) 
       { 
            
           Set_Sprite(10, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                  
           sprintf( counter[5].word, "Beach^Tunnels");
   
           counter[5].length = 1;     
           msg_left=true;   
           
           if(mouseleft == true)
           {
                        
               tunnel_page = 1; 
                       
               next_scene = true;
               
               click_sfx = true;         
               mouseleft = false;
           }                       
       }  
       else
           Set_Sprite(10, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);  
                
       // Page 1 
       if(sprite[11].grab_switch == true)                 
       if(( mouseX < (sprite[11].w + sprite[11].box_width) )
       &&( mouseX > sprite[11].w)                            
       &&( mouseY < (sprite[11].z + sprite[11].box_height) )
       &&( mouseY > sprite[11].z)) 
       {  

           Set_Sprite(11, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
           
           if(current_act == 1)      
           {  
               sprintf( counter[5].word, "Locked");
               counter[5].length = 0;
           }
           else
           {
               sprintf( counter[5].word, "Village^Tunnels");
               counter[5].length = 1;
           }
    
           msg_left=true;    
           
           if(mouseleft == true)
           {
               if(current_act > 1) 
               {   
                   tunnel_page = 2;
                   next_scene = true;
               }
                                       
               click_sfx = true;         
               mouseleft = false;
           }                       
       } 
       else
           Set_Sprite(11, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);             
                
       // Page 1 
       if(sprite[12].grab_switch == true)                 
       if(( mouseX < (sprite[12].w + sprite[12].box_width) )
       &&( mouseX > sprite[12].w)                            
       &&( mouseY < (sprite[12].z + sprite[12].box_height) )
       &&( mouseY > sprite[12].z)) 
       { 
            
           Set_Sprite(12, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
           
           if(current_act != 3 && current_act != 4)      
           {  
               sprintf( counter[5].word, "Locked");
               counter[5].length = 0;
           }
           else
           {
               sprintf( counter[5].word, "Farmland^Tunnels");
               counter[5].length = 1;
           }
    
           msg_left=true;     
           
           if(mouseleft == true)
           {
               if(current_act == 3 || current_act == 4) 
               {   
                   tunnel_page = 3;
                   next_scene = true;
               }
                                       
               click_sfx = true;          
               mouseleft = false;
           }                       
       } 
       else
           Set_Sprite(12, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);             
                    
                                                    
       Message_Limits();        
            
              
     }
 
           // Lantern     
           if(fade == 0.5 || fade == 1.0)   
           if(( mouseX < (sprite[2].w + sprite[2].box_width) )
           &&( mouseX > sprite[2].w)                            
           &&( mouseY < (sprite[2].z + sprite[2].box_height) )
           &&( mouseY > sprite[2].z))  
           { 
               Set_Sprite(1, 4, LOOP, ANIM_HUD, ANIM_NOT_WALKING);
                    
               if(mouseleft == true) 
               {
                   mouseleft = false;
                   lightswitch_sfx = true;
                   if(sprite[2].grab_switch == false)
                   {
                       sprite[2].grab_switch = true;
                       
                       Set_Sprite(2, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                       
                       fade = 0.5;       
                   }             
                   else
                   {
                       sprite[2].grab_switch = false;
                       Set_Sprite(2, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                       fade = 1.0;
                   }
                            
               }
                
           }                  
           else
               Set_Sprite(1, 0, LOOP, ANIM_HUD, ANIM_NOT_WALKING);        
 
}
