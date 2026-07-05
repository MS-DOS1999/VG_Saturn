
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN 

#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>			// Header File For Standard Input/Output
#include <gl\gl.h> 
#include "globals.h" 
 
extern bool New_FX(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int i_value, int i_type, int state, int linked_sprite, int tex_id, int i_value1, int i_value2, int i_value3);
extern bool Has_This_Item(int type, int value);
extern void Remove_Item(int item_type, int item_value, int item_value1, bool remove_all);
extern void Message_Limits();
extern void Create_Star_Effect(float x1, float y1, float size, int tex_id);

void Calculate_Tent_Lifebar();  

float tent_health_width = 0.0;
int tent_flash_timer=0;
int was_sleeping_timer=0;
int mouse_out_timer = 0;
bool mouse_out = false;

void Run_Tent(int f_rate)
{
	if(f_rate <= 0)
	    f_rate = 1; 
 
    if(tent_title_sequence == 0) 
    { 

	  				  
	  	stop_waves_sfx=true;
        stop_seagull_sfx = true;
        stop_wind_sfx=true;
        stop_woods_sfx=true;
        stop_exhaust_sfx=true;  
        stop_train_sfx=true;  
        stop_battlefield_sfx=true;
        stop_tank_boss_sfx=true;
        stop_airplane_sfx=true; 
		stop_tank_sfx=true;
		  			   
	    was_sleeping_timer = -1;  

	    mouse_out = false;   
		mouse_out_timer = (int)TimerGetTime() + 2000 + rand()%14000;
		sprite[39].alpha = 0.0;
 
        if(was_sleeping == true)  
        {
            Set_Sprite(10, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
            was_sleeping_timer = (int)TimerGetTime()+2000;
		}			  
        		              
        tent_health_width = sprite[11].width;  
                                                                  
        tent_flash_timer=0;
		 
		if(scene == 170) 
		{
            old_health = PLY_VITALITY; 
		}
        
        if(old_health != 0) 
        if(PLY_VITALITY/old_health > 3)
            Set_Sprite(10, 4, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);              
        
        if(old_health == 0) 
            Set_Sprite(10, 4, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);         
        
        Set_Sprite(1, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Dolly day anim
        
        sprite[35].alpha = 0.0;
         
        if(current_main > 0) 
        if(current_main != MISSION_TRAINING)
        if(main_mission[current_main] == IN_PROGRESS)
        if(activate_bicycle == true)
		{ 
            sprite[35].alpha = 1.0;

			if(global_objects[51] == GLOBAL_UNBEATEN)
			{
				sprite[35].flash_timer = (int)TimerGetTime() + 3000;
	            cash_sfx = true;
				global_objects[51] = GLOBAL_BEATEN;
			} 
		}

        sprite[1].alpha  = 0.0; // Dolly 
        sprite[3].alpha  = 0.0; // Lantern
        sprite[4].alpha  = 0.0; // Flies
        sprite[12].alpha = 0.0; // Socks              
        sprite[14].alpha = 0.0; // Books
        sprite[15].alpha = 0.0; // Dirty
        sprite[16].alpha = 0.0; // Ashtray
        sprite[17].alpha = 0.0; // Smoke
        sprite[18].alpha = 0.0; // Rug
        sprite[19].alpha = 0.0; // Chair
        sprite[20].alpha = 0.0; // Diary 
        sprite[21].alpha = 0.0; // Golf clubs
        sprite[22].alpha = 0.0; // Painting      
        sprite[24].alpha = 0.0; // Piggy Bank         
        sprite[27].alpha = 0.0; // Bible         
        sprite[26].alpha = 0.0; // Flag 
        sprite[28].alpha = 0.0; // Bedpan        
        sprite[29].alpha = 0.0; // Bog roll          
        sprite[30].alpha = 0.0; // Plate         
        sprite[31].alpha = 0.0; // Teacup 
        sprite[25].alpha = 0.0; // Hamlet         
        sprite[32].alpha = 0.0; // Snuffbox         
        sprite[23].alpha = 0.0; // Toy Plane         
        sprite[33].alpha = 0.0; // Poster            
        sprite[37].alpha = 0.0; // Poster 
        sprite[38].alpha = 0.0; // Closet
        
        if(COLLECTIBLE_CARDS == 0)
            sprite[36].alpha = 0.0; // Collectible Cards box...

        for(int i = 0; i < 36; i++)    
        if(Has_This_Item(INV_CARD, i) == true)
        {
            Remove_Item(INV_CARD, i, -1, true);                       
            global_cards[i] = CARD_FULL;
            sprite[36].flash_timer = (int)TimerGetTime() + 3000;
            cash_sfx = true;
        }       

        if(global_objects[99] == GLOBAL_BEATEN) // was 99 // was_sleeping == true
		if(tent_objects[22] != TENT_HAS)
		if(next_scene == false)
        {
            tent_objects[22] = TENT_AQUIRE; 
        }   
                                                   
        // Does player have sock in INV?
        if(Has_This_Item(INV_LETTERS, 8) == true) 
        {
            Remove_Item(INV_LETTERS, 8, -1, true);               
            tent_objects[0] = TENT_AQUIRE;
        } 
        
        if(tent_objects[0] == TENT_AQUIRE) 
        {
           sprite[4].flash_timer = (int)TimerGetTime() + 3000;
           sprite[12].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[0] = TENT_HAS;      
		   global_objects[15] = GLOBAL_BEATEN;  // 15 == Smelly Sock in Pebble Bay
        }
        
        if(tent_objects[0] == TENT_HAS)
        {
           sprite[4].alpha  = 1.0; // Flies
           sprite[12].alpha = 1.0; // Socks           
        }
        
        // Does player have Lantern in INV?
        if(Has_This_Item(INV_LETTERS, 9) == true)
//        if(tent_objects[1] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 9, -1, true);               
            tent_objects[1] = TENT_AQUIRE;
        }
         
        if(tent_objects[1] == TENT_AQUIRE) 
        {
           sprite[3].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[1] = TENT_HAS;   
		   global_objects[26] = GLOBAL_BEATEN;  // 26 == Lantern in Boatyard 
        }
        
        if(tent_objects[1] == TENT_HAS)
        {
           sprite[3].alpha  = 1.0; // Flies
        } 
         
        // Does player have Dolly in INV?
        if(Has_This_Item(INV_LETTERS, 10) == true)
 //       if(tent_objects[2] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 10, -1, true);               
            tent_objects[2] = TENT_AQUIRE;
        }
         
        if(tent_objects[2] == TENT_AQUIRE) 
        {
           sprite[1].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[2] = TENT_HAS;   
		   global_objects[23] = GLOBAL_BEATEN;  // 23 == Vodoo Doll in Bunker C
        }
        
        if(tent_objects[2] == TENT_HAS)
        {
           sprite[1].alpha  = 1.0; // Flies
        }
           
        // Does player have Books in INV? 
        if(Has_This_Item(INV_LETTERS, 11) == true)
//        if(tent_objects[3] == TENT_NONE) 
        {
            Remove_Item(INV_LETTERS, 11, -1, true);               
            tent_objects[3] = TENT_AQUIRE;
        } 
         
        if(tent_objects[3] == TENT_AQUIRE) 
        {
           sprite[14].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[3] = TENT_HAS;   
        }
        
        if(tent_objects[3] == TENT_HAS)
        {
           sprite[14].alpha  = 1.0; // Flies
        }        
        
        // Does player have Lantern in INV?
        if(Has_This_Item(INV_LETTERS, 4) == true)
//        if(tent_objects[4] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 4, -1, true);                
            tent_objects[4] = TENT_AQUIRE;
        } 
         
        if(tent_objects[4] == TENT_AQUIRE) 
        {
           sprite[15].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[4] = TENT_HAS;           
        }
        
        if(tent_objects[4] == TENT_HAS)
        {
           sprite[15].alpha  = 1.0; // Flies
        } 
         
        // Does player have Ashtray in INV?
        if(Has_This_Item(INV_LETTERS, 12) == true)
//        if(tent_objects[5] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 12, -1, true);                
            tent_objects[5] = TENT_AQUIRE;
        }
         
        if(tent_objects[5] == TENT_AQUIRE) 
        {
           sprite[16].flash_timer = (int)TimerGetTime() + 3000;
           sprite[17].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[5] = TENT_HAS;  
		   global_objects[22] = GLOBAL_BEATEN;  // 22 == Ashtray in bunker B
        }
        
        if(tent_objects[5] == TENT_HAS)
        {
           sprite[16].alpha  = 1.0; // Flies
           sprite[17].alpha  = 1.0; // Flies
        } 
         
        // Does player have Ashtray in INV?
        if(Has_This_Item(INV_LETTERS, 13) == true)
//        if(tent_objects[6] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 13, -1, true);                
            tent_objects[6] = TENT_AQUIRE;
        }
         
        if(tent_objects[6] == TENT_AQUIRE) 
        {
           sprite[18].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[6] = TENT_HAS; 
		   global_objects[74] = GLOBAL_BEATEN;  // 74 == Rug at Village
        }
         
        if(tent_objects[6] == TENT_HAS)
        {
           sprite[18].alpha  = 1.0; // Flies
        }         
         
        // Does player have Chair in INV?
        if(Has_This_Item(INV_LETTERS, 14) == true)
 //       if(tent_objects[7] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 14, -1, true);                
            tent_objects[7] = TENT_AQUIRE;
        } 
         
        if(tent_objects[7] == TENT_AQUIRE) 
        {
           sprite[19].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[7] = TENT_HAS;   
		   global_objects[21] = GLOBAL_BEATEN;  // 21 == Chair in bunker A
        } 
          
        if(tent_objects[7] == TENT_HAS)
        {
           sprite[19].alpha  = 1.0; // Flies
        }  
         
        // Does player have Diary in INV? 
        if(Has_This_Item(INV_LETTERS, 15) == true)
//        if(tent_objects[8] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 15, -1, true);                
            tent_objects[8] = TENT_AQUIRE;
        }
         
        if(tent_objects[8] == TENT_AQUIRE) 
        {
           sprite[20].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[8] = TENT_HAS;           
        }
         
        if(tent_objects[8] == TENT_HAS)
        {
           sprite[20].alpha  = 1.0; // Flies
        }  
         
        // Does player have Golf Clubs in INV? 
        if(Has_This_Item(INV_LETTERS, 16) == true)
 //       if(tent_objects[9] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 16, -1, true);                
            tent_objects[9] = TENT_AQUIRE;
        }
         
        if(tent_objects[9] == TENT_AQUIRE) 
        {
           sprite[21].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[9] = TENT_HAS;  
		   global_objects[6] = GLOBAL_BEATEN;  // 6 == Chest at grassy plains
        }
         
        if(tent_objects[9] == TENT_HAS)
        {
           sprite[21].alpha  = 1.0; // Flies
        }  
         
        // Does player have Painting in INV? 
        if(Has_This_Item(INV_LETTERS, 17) == true)
//        if(tent_objects[10] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 17, -1, true);                
            tent_objects[10] = TENT_AQUIRE;
        } 
         
        if(tent_objects[10] == TENT_AQUIRE) 
        {
           sprite[22].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[10] = TENT_HAS;   
		   global_objects[7] = GLOBAL_BEATEN;  // 7 == Painting at wine cellar
        }
         
        if(tent_objects[10] == TENT_HAS)
        {
           sprite[22].alpha  = 1.0; // Flies
        }          
         
        // Does player have Piggy Bank in INV? 
        if(Has_This_Item(INV_LETTERS, 18) == true)
//        if(tent_objects[11] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 18, -1, true);                
            tent_objects[11] = TENT_AQUIRE; 
        } 
         
        if(tent_objects[11] == TENT_AQUIRE) 
        {
           sprite[24].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[11] = TENT_HAS;   
		   global_objects[39] = GLOBAL_BEATEN;  // 39 == Piggy bank at tank bunker
        }
         
        if(tent_objects[11] == TENT_HAS)
        {
           sprite[24].alpha  = 1.0; // Flies
        }   
         
        // Does player have Bible in INV? 
        if(Has_This_Item(INV_LETTERS, 19) == true)
//        if(tent_objects[12] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 19, -1, true);                
            tent_objects[12] = TENT_AQUIRE; 
        } 
         
        if(tent_objects[12] == TENT_AQUIRE) 
        {
           sprite[27].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[12] = TENT_HAS; 
		   global_objects[76] = GLOBAL_BEATEN;  // 76 == Bible at Church
        }
         
        if(tent_objects[12] == TENT_HAS)
        {
           sprite[27].alpha  = 1.0; // Flies
        }   
         
        // Does player have Flag in INV? 
        if(Has_This_Item(INV_LETTERS, 20) == true)
 //       if(tent_objects[13] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 20, -1, true);                
            tent_objects[13] = TENT_AQUIRE; 
        } 
         
        if(tent_objects[13] == TENT_AQUIRE) 
        {
           sprite[26].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true;  
           tent_objects[13] = TENT_HAS;   
		   global_objects[10] = GLOBAL_BEATEN;  // 10 == Flag at Grannies cellar
        }
         
        if(tent_objects[13] == TENT_HAS)     
        {
           sprite[26].alpha  = 1.0; // Flies
        }  
         
        // Does player have Bedpan in INV? 
        if(Has_This_Item(INV_LETTERS, 21) == true)
        if(tent_objects[14] == TENT_NONE) 
        {
            Remove_Item(INV_LETTERS, 21, -1, false);                
            tent_objects[14] = TENT_AQUIRE; 
        } 
         
        if(tent_objects[14] == TENT_AQUIRE) 
        {
           sprite[28].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[14] = TENT_HAS; 
		   global_objects[37] = GLOBAL_BEATEN; // 37 == Chest at Keiser bunker
        }
         
        if(tent_objects[14] == TENT_HAS)
        {
           sprite[28].alpha  = 1.0; // Flies
        }          
         
        // Does player have Bog roll in INV? 
        if(Has_This_Item(INV_LETTERS, 22) == true)
//        if(tent_objects[15] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 22, -1, true);                
            tent_objects[15] = TENT_AQUIRE; 
        } 
         
        if(tent_objects[15] == TENT_AQUIRE)  
        {
           sprite[29].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[15] = TENT_HAS;
		   global_objects[78] = GLOBAL_BEATEN; // 78 == Bogroll at farmlands 
        }
         
        if(tent_objects[15] == TENT_HAS)
        {
           sprite[29].alpha  = 1.0; // Flies
        }  
         
        // Does player have Plate in INV? 
        if(Has_This_Item(INV_LETTERS, 23) == true)
 //       if(tent_objects[16] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 23, -1, true);                
            tent_objects[16] = TENT_AQUIRE; 
        } 
         
        if(tent_objects[16] == TENT_AQUIRE) 
        {
           sprite[30].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[16] = TENT_HAS; 
		   global_objects[77] = GLOBAL_BEATEN; // 77 == Plate at Cave
        }
         
        if(tent_objects[16] == TENT_HAS)
        {
           sprite[30].alpha  = 1.0; // Flies
        }          
         
        // Does player have Teacup in INV? 
        if(Has_This_Item(INV_LETTERS, 24) == true)
//        if(tent_objects[17] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 24, -1, true);                
            tent_objects[17] = TENT_AQUIRE; 
        } 
         
        if(tent_objects[17] == TENT_AQUIRE)  
        {
           sprite[31].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[17] = TENT_HAS; 
		   global_objects[25] = GLOBAL_BEATEN; // 25 == teacup at house at village 
        }
         
        if(tent_objects[17] == TENT_HAS)
        {
           sprite[31].alpha  = 1.0; // Flies
        }           
         
        // Does player have Hamlet in INV? 
        if(Has_This_Item(INV_LETTERS, 25) == true) 
//        if(tent_objects[18] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 25, -1, true);                
            tent_objects[18] = TENT_AQUIRE; 
        } 
         
        if(tent_objects[18] == TENT_AQUIRE) 
        {
           sprite[25].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[18] = TENT_HAS;  
		   global_objects[24] = GLOBAL_BEATEN; // 24 == Hamlet in Secret Lab A
        }
         
        if(tent_objects[18] == TENT_HAS)
        {
           sprite[25].alpha  = 1.0; // Flies
        }            
         
        // Does player have Snuff box in INV? 
        if(Has_This_Item(INV_LETTERS, 26) == true)
//        if(tent_objects[19] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 26, -1, true);                
            tent_objects[19] = TENT_AQUIRE; 
        } 
         
        if(tent_objects[19] == TENT_AQUIRE) 
        {
           sprite[32].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[19] = TENT_HAS;   
		   global_objects[38] = GLOBAL_BEATEN; // 38 == Snuff-box at house at village
        }
         
        if(tent_objects[19] == TENT_HAS)
        {
           sprite[32].alpha  = 1.0; // Flies
        }   
         
        // Does player have Toy Plane in INV? 
        if(Has_This_Item(INV_LETTERS, 27) == true)
//        if(tent_objects[20] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 27, -1, true);                
            tent_objects[20] = TENT_AQUIRE; 
        } 
          
        if(tent_objects[20] == TENT_AQUIRE) 
        {
           sprite[23].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[20] = TENT_HAS;   
		   global_objects[79] = GLOBAL_BEATEN; // 79 == toyplane at airfield

        }
         
        if(tent_objects[20] == TENT_HAS)
        {
           sprite[23].alpha  = 1.0; // Flies
        }    
         
        // Does player have Poster in INV? 
        if(Has_This_Item(INV_LETTERS, 28) == true)
//        if(tent_objects[21] == TENT_NONE)
        {
            Remove_Item(INV_LETTERS, 28, -1, true);                
            tent_objects[21] = TENT_AQUIRE; 
        }  
         
        if(tent_objects[21] == TENT_AQUIRE) 
        {
           sprite[33].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[21] = TENT_HAS;    
		   global_objects[52] = GLOBAL_BEATEN; // 52 == Poster at coastal town
        }
         
        if(tent_objects[21] == TENT_HAS)
        {
           sprite[33].alpha  = 1.0; // Flies 
        }            
                         
        if(tent_objects[22] == TENT_AQUIRE) 
        {
           sprite[38].flash_timer = (int)TimerGetTime() + 3000;
           cash_sfx = true; 
           tent_objects[22] = TENT_HAS;           
        }  
        
        if(tent_objects[22] == TENT_HAS)
        {
           sprite[38].alpha  = 1.0; // Closet
        }         
    		
        was_sleeping = false;        

		#if INCLDUE_360_CONTROLLER  == 1 
		if(CONTROLLER) 
		{       

			if(sprite[35].alpha == 0.0)
			{
				MAKE_BUTTON(ROW_MIDDLE+2, 13, BOX_SMALL); // Exit

				MAKE_BUTTON(ROW_MIDDLE+1, 7, BOX_SMALL); // Player stats
				MAKE_BUTTON(ROW_MIDDLE, 5, BOX_SMALL); // Badge box  

				if(sprite[38].alpha == 1.0)      
					MAKE_BUTTON(ROW_MIDDLE-1, 38, BOX_SMALL); // Clothes

				MAKE_BUTTON(ROW_MIDDLE-1, 6, BOX_SMALL);   // Bed

				DX_ROW = ROW_MIDDLE-1;
				DX_CURRENT_TITLE_BUTTON[DX_ROW] = 0;
			 
				sprintf( string, "scene/episode%i/scene%i.dx", episode, scene);
				LoadDXTemp( string ); 

			}
			if(sprite[35].alpha == 1.0)
			{
				MAKE_BUTTON(ROW_MIDDLE+2, 13, BOX_SMALL); // Exit
			
				MAKE_BUTTON(ROW_MIDDLE+1, 35, BOX_SMALL);  // Retry

				MAKE_BUTTON(ROW_MIDDLE, 7, BOX_SMALL); // Player stats
				MAKE_BUTTON(ROW_MIDDLE, 5, BOX_SMALL); // Badge box

				if(sprite[38].alpha == 1.0)      
					MAKE_BUTTON(ROW_MIDDLE-1, 38, BOX_SMALL); // Clothes

				MAKE_BUTTON(ROW_MIDDLE-1, 6, BOX_SMALL);   // Bed

				DX_ROW = ROW_MIDDLE+1;
				DX_CURRENT_TITLE_BUTTON[DX_ROW] = 0;
			}


		}
		#endif

        tent_title_sequence++; 
                         
    }      

	if((int)TimerGetTime() > mouse_out_timer)
	{
		
		if(mouse_out == false) 
		{ 
			mouse_out = true;
			sprite[39].alpha = 1.0; 
			mouse_out_timer	= (int)TimerGetTime()+2000;
		}
		else 
		{
			mouse_out = false; 
			sprite[39].alpha = 0.0;
	    	mouse_out_timer	= (int)TimerGetTime()+16000+rand()%24000;
		}

	}

    if(tent_title_sequence == 1)        
    { 
                        
       if(hours >= 23 || hours < 6 )            
         daytime = NIGHTTIME;                  
       if(hours >= 6 && hours < 23 )  
         daytime = DAYTIME;  
         
       if(hours >= 22 && hours < 23) // Decrease Light     
       if(minutes >= 15) 
       {
         daytime = NIGHTTIME;             
       }             
                     
       if(hours >= 5 && hours < 6)            
       if(minutes >= 15)  
       {                                    
         daytime = DAYTIME;                  
       }
                            
       sprintf( counter[5].word, "");   
       sprintf( counter[0].word, "");   
       counter[0].alpha = 0.0;
       
       Calculate_Tent_Lifebar(); 

       if(was_sleeping_timer != -1) 
       if((int)TimerGetTime() > was_sleeping_timer)
       {
           Set_Sprite(10, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
           was_sleeping_timer = -1;
	   }	
		
       if(daytime == NIGHTTIME )             
           Set_Sprite(8, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
                   
       if(daytime == DAYTIME )
           Set_Sprite(8, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
           
       // Exit Button - EXIT 
       if(sprite[13].grab_switch == true)                   
       if( (( mouseX < (sprite[13].w + sprite[13].box_width) )
       &&( mouseX > sprite[13].w)                            
       &&( mouseY < (sprite[13].z + sprite[13].box_height) )
       &&( mouseY > sprite[13].z))  || DX_BACK == true)
       { 
           
           Set_Sprite(13, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
            
		   if(!CONTROLLER)
		   if(scene != 170)               
		   {
               sprintf( counter[5].word, "Leave_Tent");
               counter[5].length = 0; 
		   }
           else
           { 
               sprintf( counter[5].word, "Back_to^Title");
               counter[5].length = 1; 
		   }               
           
              
           msg_left=false;   
               
           if( button_snd == false) 
           {         
               radio_sfx = true;
               button_snd = true;
           }                 
           if( (mouseleft == true || DX_SHOOT == true || DX_BACK == true) && scene != 170)   
           {
			   DX_SHOOT=false;
			   DX_BACK=false;

               if(global_objects[60] == GLOBAL_DELIVERED)
               { 
				   if(!CONTROLLER)
				   {
					   episode = 1;    
					   scene = 186;  
				   }
				   else
				   { 

					    episode = 2;    
 
					    scene = 0;  
                                                    
					    current_spawn = 0;

						global_objects[60] = GLOBAL_BEATEN;

						new_mission = TALK_TENT_DAY; 

				   }

               }
			   else
			   {

				   episode = 2;    
 
				   scene = 0;  
                                                    
				   current_spawn = 0;

			   }

               next_scene = true; 
               mouseleft = false; 
               sprite[8].grab_switch = false;
               
               if(global_objects[60] == GLOBAL_FINISHED)
               {
                   global_objects[60] = GLOBAL_BEATEN;
               	   new_mission = TALK_TENT_DAY; 
               }                 
           } 
           if(mouseleft == true || DX_SHOOT == true && scene == 170)   
           {
			   DX_SHOOT=false;
		       episode = 0;	 
			   scene = 0;
			   
			   fade_out = 5; 
			   c_fade_out = 5;

    		   if(dm_game == DM_NONE)             
		       if(current_file != -1)                    
		       if(current_new_game == true)                   
		       {              
	               sprintf( temp_string.string, "data/save/fragfile%i", current_file);
		           SaveLevel( temp_string);                                    
	           } 
			   
			   next_scene = true;					     
		   }          
       }   
       else 
       {
           Set_Sprite(13, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);   
           button_snd = false;
       }
        
      // Bed
       if(sprite[35].alpha == 1.0)
       if(( mouseX < (sprite[35].w + sprite[35].box_width) )
       &&( mouseX > sprite[35].w)                            
       &&( mouseY < (sprite[35].z + sprite[35].box_height) )
       &&( mouseY > sprite[35].z)) 
       {  
           
           if(sprite[35].grab_switch == true)
           {
               sprite[35].grab_switch = false;                     
               radio_sfx = true;   
           }   
                 
           sprintf( counter[5].word, "Cycle_to^Last_mission");
           
           counter[5].length = 1;    
           msg_left=false;   
                
           if(mouseleft == true|| DX_SHOOT == true)
           if(cycle_episode != -1)
           if(cycle_scene != -1) 
           { 
                        
			   DX_SHOOT=false;
               episode = cycle_episode;    
               scene   = cycle_scene;
               
               if(episode == 1) 
               if( scene == 95 
               || scene == 96)
               {
                   episode = 1;     
                   scene   = 93;                        
               }               
               if(scene == 97
               || scene == 98) 
               { 
                   episode = 1;     
                   scene   = 97;                        
               }
               
               current_spawn = cycle_spawn;
               
               next_scene = true; 
			   
  			   if(has_buddy != BUDDY_WAIT)  	 	
			   if(ply_buddy_dead == false)
			   {
			       buddy_cur_health = BUDDY_VITALITY;
				   buddy_health = BUDDY_VITALITY;	
			   }
               
               Calculate_Stats();    
               
               pick_up_sfx = true; 
               tent_title_sequence = 2;
               sprintf( counter[5].word, "");
           }
                
        }
        else 
        {
           sprite[35].grab_switch = true;
        }    

      // Bed
       if(sprite[38].alpha == 1.0)
       if(( mouseX < (sprite[38].w + sprite[38].box_width) )
       &&( mouseX > sprite[38].w)                            
       &&( mouseY < (sprite[38].z + sprite[38].box_height) )
       &&( mouseY > sprite[38].z)) 
       {  
           
           if(sprite[38].grab_switch == true)
           {
               sprite[38].grab_switch = false;                     
               radio_sfx = true;   
           }   
                 
           sprintf( counter[5].word, "Change^Clothes");

           Set_Sprite(38, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
           
           counter[5].length = 1;    
           msg_left=true;   
                
           if(mouseleft == true || DX_SHOOT == true)
           { 
			   DX_SHOOT=false;

     		   episode = 1; 
			   scene = 176;
	
               next_scene = true; 

               pick_up_sfx = true; 
               sprintf( counter[5].word, "");
           }
                
        }
        else 
        {
           Set_Sprite(38, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
        }    
        
        
//     Medal_box   
       if(sprite[37].alpha != 0.0)                 
       if(( mouseX < (sprite[37].w + sprite[37].box_width) )
       &&( mouseX > sprite[37].w)                            
       &&( mouseY < (sprite[37].z + sprite[37].box_height) )
       &&( mouseY > sprite[37].z)) 
       {

           Set_Sprite(5, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

           sprintf( counter[5].word, "New_Cards!");
           
           counter[5].length = 0;   
           msg_left=true;  
     
        }
                            
//     Medal_box                   
       if(( mouseX < (sprite[5].w + sprite[5].box_width) )
       &&( mouseX > sprite[5].w)                            
       &&( mouseY < (sprite[5].z + sprite[5].box_height) )
       &&( mouseY > sprite[5].z)) 
       {
           
           if(sprite[5].anim == 0)
               radio_sfx = true;   
            
           Set_Sprite(5, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

           sprintf( counter[5].word, "Badge_Box");
           
           counter[5].length = 0;   
           msg_left=true;  
                          
           if(mouseleft == true || DX_SHOOT == true)
           {
			   DX_SHOOT=false;
               episode = 1;
               scene   = 24;
               pick_up_sfx = true; 
               next_scene = true;
               tent_title_sequence = 2;
           }
     
        }
        else
           Set_Sprite(5, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
       
       if(sprite[36].alpha == 1.0)      
       if(( mouseX < (sprite[36].w + sprite[36].box_width) )
       &&( mouseX > sprite[36].w)                            
       &&( mouseY < (sprite[36].z + sprite[36].box_height) )
       &&( mouseY > sprite[36].z)) 
       {
           
           if(sprite[36].anim == 0)
               radio_sfx = true;   
            
           Set_Sprite(36, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

           sprintf( counter[5].word, "Collectible^Cards");
           
           counter[5].length = 1;    
           msg_left=true;  
                          
           if(mouseleft == true || DX_SHOOT == true)
           { 
			   DX_SHOOT=false;
               episode = 1;
               scene   = 18;
               pick_up_sfx = true; 
               next_scene = true;
               tent_title_sequence = 2;
           }
     
        }
        else
           Set_Sprite(36, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);    
                           
       
       // Bed
       if( fade > 0.7)
       if(( mouseX < (sprite[6].w + sprite[6].box_width) )
       &&( mouseX > sprite[6].w)                            
       &&( mouseY < (sprite[6].z + sprite[6].box_height) )
       &&( mouseY > sprite[6].z)) 
       {  
           
           if(sprite[6].grab_switch == true)
           {
               sprite[6].grab_switch = false;                     
               radio_sfx = true;   
           }
               
           sprintf( counter[5].word, "Go_to_sleep");
           
           counter[5].length = 0;    
           msg_left=true;    
             
           if(mouseleft == true || DX_SHOOT == true)  
           {       
			   DX_SHOOT=false;
               episode = 1;   
               scene   = 25;  
               next_scene = true;      
               pick_up_sfx = true; 
	   		
			   shop_items_set_timer = 0;

               snore_sfx = true;  
               c_fade_out = 3;
               fade_out   = 3;
               was_sleeping = true;
               tent_title_sequence = 2; 
               sprintf( counter[5].word, "");
               Set_Sprite(6, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
               Set_Sprite(1, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Dolly day anim
                            
               Calculate_Stats();    

               old_health = PLY_VITALITY;   
			   player_health = old_health;	

				if(ply_buddy_dead == false)
					buddy_cur_health = BUDDY_VITALITY;
  
               sprite[10].alpha = 0.0; 
               
			   if(daytime == NIGHTTIME)                                      
			   {
	               hours=6;  
				   minutes=1;  
			   }
               
			   if(daytime == DAYTIME)                                       
			   {
	               hours=23;  
				   minutes=1;
			   } 
   
               if(global_objects[60] == GLOBAL_DELIVER)
               {
                   global_objects[60] = GLOBAL_DELIVERED;
                     
                   hours = 5; 
                   minutes = 15; 
                   
                   daytime = DAYTIME;
                   
               }
                               
           }
     
        } 
        else
        {
           Set_Sprite(6, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);        
           sprite[6].grab_switch = true;
        }
        
      // Bed
       if(( mouseX < (sprite[7].w + sprite[7].box_width) )
       &&( mouseX > sprite[7].w)                            
       &&( mouseY < (sprite[7].z + sprite[7].box_height) )
       &&( mouseY > sprite[7].z)) 
       {  
           
           if(sprite[7].grab_switch == true)
           { 
               sprite[7].grab_switch = false;                     
               radio_sfx = true;    
           }   
                 
           sprintf( counter[5].word, "%0.9s&s^Stats", player_name); 
           
           counter[5].length = 1;    
           msg_left=false;   
           
           if(mouseleft == true || DX_SHOOT == true)
           { 
			   DX_SHOOT=false;
               episode = 1;   
               scene   = 26;
               next_scene = true;
               
               pick_up_sfx = true; 
               tent_title_sequence = 2;
               sprintf( counter[5].word, "");
           }
                
        }
        else 
        {
           sprite[7].grab_switch = true;
        }    
       
                          
        Message_Limits();              
  
              
    } // tent_title_sequence == 1 
     
     for(int i=0;i<no_sprites;i++)
     {
       
       if(sprite[i].flash_timer != 0)
       if((int)TimerGetTime() > tent_flash_timer )
       {
 
         if(sprite[i].alpha == 0.0)          
            sprite[i].alpha = 1.0;
         else 
            sprite[i].alpha = 0.0;
              
           // Create a star effect...
           if(rand()%2 == 0)
               Create_Star_Effect( (sprite[i].x+sprite[i].width/2), (sprite[i].y+sprite[i].height/2), 0.1f, 39);
           else
               Create_Star_Effect( (sprite[i].x+sprite[i].width/2), (sprite[i].y+sprite[i].height/2), 0.15f, 39);
            
       } 
       if(sprite[i].flash_timer != 0)
       if((int)TimerGetTime() > sprite[i].flash_timer )
       {
           sprite[i].alpha = 1.0;
           sprite[i].flash_timer = 0;
       } 
     } 
     
     if((int)TimerGetTime() > tent_flash_timer )
         tent_flash_timer = (int)TimerGetTime() + 150;
     
           // Lantern     
           if(sprite[3].alpha == 1.0)
           {
           
           if(fade == 0.5 || fade == 1.0)  
           if(( mouseX < (sprite[3].w + sprite[3].box_width) )
           &&( mouseX > sprite[3].w)                            
           &&( mouseY < (sprite[3].z + sprite[3].box_height) )
           &&( mouseY > sprite[3].z))  
           { 
           //    Set_Sprite(1, 4, LOOP, ANIM_HUD, ANIM_NOT_WALKING);
               
               if(mouseleft == true || DX_SHOOT == true)  
               {
				   DX_SHOOT=false;
                   mouseleft = false;
                   lightswitch_sfx = true;
                   if(sprite[3].grab_switch == false)
                   {
                       sprite[3].grab_switch = true;
                       
                       Set_Sprite(3, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                               
                       Set_Sprite(1, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Dolly Night anim
                       
                       if(tent_objects[0] == TENT_HAS)
                           sprite[4].alpha = 0.0; // Flies
                       
                       fade = 0.5;       
                                   
                       tent_title_sequence = 6;
                   }             
                   else
                   {
                       sprite[3].grab_switch = false;
                       
                       Set_Sprite(3, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
                               
                       Set_Sprite(1, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Dolly Day anim
                       
                       if(tent_objects[0] == TENT_HAS)
                           sprite[4].alpha = 1.0; // Flies
                       
                       fade = 1.0;
                       tent_title_sequence=1;
                   }
                            
               }
                
           }                  
       //    else
       //        Set_Sprite(1, 0, LOOP, ANIM_HUD, ANIM_NOT_WALKING);       
           
           } // alpha == 1.0 
 
 
}
void Calculate_Tent_Lifebar() 
{       
                      
     float testX = 0.0;           
     
     if(PLY_VITALITY != 0)     
         testX = tent_health_width / (float)PLY_VITALITY;     
          
     sprite[11].width = (float)old_health * testX;
         
     if( old_health > 0)  
     {       
         if( PLY_VITALITY/old_health > 3)
            Set_Sprite(11, 15, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
         else
            Set_Sprite(11, 14, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
     }    
         
     if(old_health <= 0)
         sprite[11].alpha = 0.0;              

     
}
