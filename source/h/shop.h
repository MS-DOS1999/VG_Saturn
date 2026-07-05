
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN 

#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>			// Header File For Standard Input/Output
#include <gl\gl.h> 
#include "globals.h"  

     
  
#define MAXIMUM_REACHED -101


#define SHOP_BUY  0 
#define SHOP_SELL 1
#define SHOP_TUNE 2  
#define SHOP_EXIT 3
 
#define GET_SHOP   0  
#define GET_COST   1

#define SHOP_AMOUNT_SHELLS       25  
#define SHOP_AMOUNT_HGUN_AMMO    40   
#define SHOP_AMOUNT_BULLETS      150
#define SHOP_AMOUNT_AMMO         30

#define SHOP_AMOUNT_BLACK_GRENADE 5
#define SHOP_AMOUNT_GREEN_GRENADE 5
#define SHOP_AMOUNT_MOLOTOV       5

#define SWITCH_TIME  10

#define COST_DIVISION  3 



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
extern int GetUpgradeSell( int the_gun);
extern int Tune_Gun(int the_index);
extern bool Has_This_Item(int type, int value);
extern void Calculate_Weapon_Text(int id, int index);
extern int GetUpgradesItems( int tune_up_page, int the_bit, int type);
extern void Calculate_Gold();
extern int Get_Cost(int id, int pickup);
extern int Generate_Item(int type, int rank);
extern int Get_Health_Amount(int my_amount);

void Calculate_Shop(int id);
bool Is_Available(int the_object, int the_weapon); 
void Set_Display_Picture(int i, int index);
void Calculate_Weapon_Buy(int index, int item);
void Calculate_Item_Buy(int index, int item);
void Calculate_Item_Txt(int index, int item);
float GetItemDefense(int item);

#define M_NOT_ENOUGH  0
#define M_PURCHASE    1
#define M_SELL        2
#define M_INVFULL   3

int shop_sequence=SHOP_BUY;
int shop_row = 0;
float base_height = 0.0;
int scroll_timer=0;
int the_item=0;
int the_index=0;
int message_type=M_NOT_ENOUGH;
int tune_up_page=0; 
int shop_switch_timer=0;
int bump_timer=-1;     

int upg_thompson =0; 
int upg_weston   =0;
int upg_enfield  =0;
int upg_farmers  =0;
int upg_luger    =0;
int upg_colt     =0;
int upg_coltk    =0;
int upg_hunter   =0;
int upg_army     =0;
int upg_training =0;

int iSHOP_AMOUNT_TINHAT=0;
int iSHOP_AMOUNT_SHOES=0;

int shop_skip_timer=0;
bool on_an_item=false;
             
void Run_Shop(int f_rate, int type)
{
     
       float cam_x =0.0, cam_y =0.0;
       float deltax =0.0,deltay =0.0;
       float testX=0.0, testY=0.0;
       float temp_speed = 0.0;
       float angle = 0.0;    
       int cost=0;
       int shop_cost[32];
//       int shop_value[32];
       int shop_sell_id[32];
       int length = 0;
       bool success=false;
       int t_firepower  =0;
       int t_firerate   =0;
       int t_reloadtime =0;
       int t_capacity   =0;
       int limit_firepower  =0;
       int limit_firerate   =0;
       int limit_reloadtime =0;
       int limit_capacity   =0;
       int rnd=0;
       int index=0;
       bool has_special = false;
       int item_value=0;
	   int temp_value=0;
	   int discount=0;

	   return;

	if(f_rate <= 0)
	    f_rate = 1;       
         
    // ******************************************************************************//
    //                                 MAIN_SHOP                                     //
    // ******************************************************************************//
   
   // Title Screen Stuff...
   if(game_mode == FRONT && !mode) 
   if(next_scene == false)
   {   
     
       if(title_sequence == 0)  
       {     
           

		   shop_skip_timer = (int)TimerGetTime() + 500;
	
           for(int i =7; i < 15;i++)
               Set_Sprite(i, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Blank
           
           base_height = sprite[18].y;  
           shop_sequence = SHOP_BUY; 
           
           if(type == SHOP_DEFAULT)  
		   {	
               shop_sequence = SHOP_BUY; 
			   shop_id = 0;	
		   }
             
           if(type == SHOP_UPGRADE) 
           {
 			   shop_sequence = SHOP_BUY;
			   shop_id = 1;	
			   type = SHOP_DEFAULT;	 
           }
             
           if(type == SHOP_PASSIVE)   
           {
 			   shop_sequence = SHOP_BUY;
			   shop_id = 2;	
			   type = SHOP_DEFAULT;	 
           }
		                
           if(type == SHOP_TRAPPER)  
           {      
 			   shop_sequence = SHOP_BUY;
			   shop_id = 3;	
			   type = SHOP_DEFAULT;	 
           } 

			#if INCLDUE_360_CONTROLLER == 1      
			if(CONTROLLER)
			{
				 
				MAKE_BUTTON(ROW_MIDDLE-2, 7, BOX_WIDE); 
				MAKE_BUTTON(ROW_MIDDLE-2, 8, BOX_WIDE);  
				MAKE_BUTTON(ROW_MIDDLE-2, 9, BOX_WIDE);  
				MAKE_BUTTON(ROW_MIDDLE-2, 10, BOX_WIDE); 
				MAKE_BUTTON(ROW_MIDDLE-2, 11, BOX_WIDE); 
				MAKE_BUTTON(ROW_MIDDLE-2, 12, BOX_WIDE); 
				MAKE_BUTTON(ROW_MIDDLE-2, 13, BOX_WIDE);  
				MAKE_BUTTON(ROW_MIDDLE-2, 14, BOX_WIDE);

				MAKE_BUTTON(ROW_MIDDLE-1, 16, BOX_SMALL);  
				MAKE_BUTTON(ROW_MIDDLE-1, 15, BOX_SMALL);

				DX_ROW=ROW_MIDDLE-2;
				DX_CURRENT_TITLE_BUTTON[DX_ROW]=0; 

			}
		   #endif

      // sprite[23].alpha = 0.0; 
      // sprite[24].alpha = 0.0;
             
           tune_up_page=-1;
           title_sequence++;
           shop_row=0; 
           scroll_timer=0;
           the_item=0;
           the_index=0;
           message_type=M_NOT_ENOUGH;
           bump_timer=-1;
             
           Calculate_Shop(shop_id);
 
       }  

	   if(st_passive_discount == 0 || shop_sequence != SHOP_BUY)
	       sprite[23].alpha = 0.0;
	   else
	   {
	       sprite[23].alpha = 1.0; 

		   if(st_passive_discount == 1) 
		       Set_Sprite(23, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Top text
		   if(st_passive_discount == 2)
		       Set_Sprite(23, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Top text
		   if(st_passive_discount == 3)
		       Set_Sprite(23, 2, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Top text
		   if(st_passive_discount == 4)
		       Set_Sprite(23, 3, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Top text
		   if(st_passive_discount == 5)
		       Set_Sprite(23, 4, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Top text
		   if(st_passive_discount == 6)
		       Set_Sprite(23, 5, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Top text

	   }

       type = SHOP_DEFAULT;

       sprintf( counter[0].word, ""); 
       sprintf( counter[1].word, "");
       sprintf( counter[11].word, "");
       sprintf( counter[5].word, "");
                          
       if(current_gold == -1)
           temp_gold = 0;
       else
           temp_gold = player_inv_value[current_gold]; 
            
       Calculate_Gold();
                
       if(shop_sequence == SHOP_SELL) 
       {
           Set_Sprite(6, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Top text
       }
       if(shop_sequence == SHOP_TUNE)
       {
           Set_Sprite(6, 2, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Top text
       }       
       if(shop_sequence == SHOP_BUY)   
       {
           Set_Sprite(6, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Top text
       } 
 
       // Discount Button 
       if(sprite[23].alpha == 1.0)       
       if(( mouseX < (sprite[23].w + sprite[23].box_width) )
       &&( mouseX > sprite[23].w)                            
       &&( mouseY < (sprite[23].z + sprite[23].box_height) )
       &&( mouseY > sprite[23].z)) 
       { 
    
		   if(st_passive_discount == 1)
	           sprintf( counter[5].word, "Prices^reduced^by %i¡!", DISCOUNT_BOOST1);
		   if(st_passive_discount == 2)
	           sprintf( counter[5].word, "Prices^reduced^by %i¡!", DISCOUNT_BOOST2);
		   if(st_passive_discount == 3)
	           sprintf( counter[5].word, "Prices^reduced^by %i¡!", DISCOUNT_BOOST3);
		   if(st_passive_discount == 4)
	           sprintf( counter[5].word, "Prices^reduced^by %i¡!", DISCOUNT_BOOST4);
		   if(st_passive_discount == 5)
	           sprintf( counter[5].word, "Prices^reduced^by %i¡!", DISCOUNT_BOOST5);
		   if(st_passive_discount == 6)
	           sprintf( counter[5].word, "Prices^reduced^by %i¡!", DISCOUNT_BOOST6);
                        
           counter[5].length = 2; 
            
           msg_left=true;  
               
           if( button10_snd == false)
           {
               radio_sfx = true;
               button10_snd = true; 
           }  
	   }
	   else
       {
           button10_snd = false;           
       }

       // Buttons - BUY 
       if(hud[2].alpha == 0.0) 
       if( ( ( mouseX < (sprite[0].w + sprite[0].box_width) )
       &&( mouseX > sprite[0].w)                            
       &&( mouseY < (sprite[0].z + sprite[0].box_height) )
       &&( mouseY > sprite[0].z))  || DX_LEFTSHLDR == true)
       {
    
           sprintf( counter[5].word, "Buy_Item");
                        
           counter[5].length = 0; 
            
           msg_left=true;  
                
           if( button_snd == false)
           {
               radio_sfx = true;
               button_snd = true;
           }                          
           Set_Sprite(0, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
           
           if(mouseleft == true || DX_SHOOT == true || DX_LEFTSHLDR == true)
           {
			   DX_SHOOT = false;
			   DX_LEFTSHLDR = false;
               shop_sequence = SHOP_BUY;
               mouseleft = false; 
               pick_up_sfx = true;
               shop_row=0;               
               tune_up_page = -1;  

       	       for(int i=0;i<32;i++)
       	       {
                   shop[i] = SHOP_NONE;
           	       shop_s[i] = SHOP_NONE;
		 		   shop_value[i] = 0;
				   shop_value1[i] = 0;
           	       shop_cost[i] = 0; 
       	       }           

			   Calculate_Shop(shop_id);

           }   
           
           
                      
       }
       else
       {
           Set_Sprite(0, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // BUY SIGN   
           button_snd = false;           
       }
           
       // Exit Button - EXIT
       if(hud[2].alpha == 0.0)       
       if( ( ( mouseX < (sprite[2].w + sprite[2].box_width) )
       &&( mouseX > sprite[2].w)                            
       &&( mouseY < (sprite[2].z + sprite[2].box_height) )
       &&( mouseY > sprite[2].z)) || DX_BACK == true) 
       {
    
           sprintf( counter[5].word, "Return^to_camp");
                        
           counter[5].length = 1; 
             
           msg_left=false;  
                
           if( button1_snd == false)
           {
               radio_sfx = true;
               button1_snd = true; 
           }                           
           Set_Sprite(2, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
           
		   if((int)TimerGetTime() > shop_skip_timer)	
           if(mouseleft == true || DX_SHOOT == true || DX_BACK == true)  
           { 
			   DX_SHOOT = false;
               DX_BACK = false;

               shop_intro_type=SHOP_EXIT_TYPE;
               
               if( type == SHOP_DEFAULT)  
               {

				   if(shop_id == 0)
				   {	
                       episode = 1; 
                   	   scene = 27;  
				   }

				   if(shop_id == 1)
				   {	
                       episode = 1;  
                   	   scene = 29;   
				   }
 
				   if(shop_id == 2)
				   {	
                       episode = 1;  
                   	   scene = 17;   
				   }
				     
				   if(shop_id == 3)
				   {	
                       episode = 1;  
                   	   scene = 184;   
				   }
				     
                   if((skip_level_shop0 == true && shop_id == 0)
				   || (skip_level_shop1 == true && shop_id == 1))	
				   {         
                   
	                   episode = 2; 
	                   scene = 0;  	

	                   if(shop_id == 0)                                                             
		                   current_spawn = 12;  

	                   if(shop_id == 1)                                                             
		                   current_spawn = 9;  
                   
				   }
				                      
                   next_scene = true;
               }         

               mouseleft = false; 
               switch_n_sfx = true;
               shop_row=0;               
                                         
           }   
                     
       }   
       else
       {
           Set_Sprite(2, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // EXIT SIGN 
           button1_snd = false;       
       }
              
       // Buttons - SELL 
       if(hud[2].alpha == 0.0)       
       if(( ( mouseX < (sprite[3].w + sprite[3].box_width) )
       &&( mouseX > sprite[3].w)                            
       &&( mouseY < (sprite[3].z + sprite[3].box_height) )
       &&( mouseY > sprite[3].z)) || DX_RIGHTSHLDR == true)
       { 
    
           sprintf( counter[5].word, "Sell_Item");
                        
           counter[5].length = 0; 
             
           msg_left=true;       
               
           if( button2_snd == false)
           {
               radio_sfx = true; 
               button2_snd = true;
           }                    
           Set_Sprite(3, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
            
           if(mouseleft == true || DX_SHOOT == true || DX_RIGHTSHLDR == true) 
           {
			   DX_SHOOT = false;
			   DX_RIGHTSHLDR = false;
               shop_sequence = SHOP_SELL;
               pick_up_sfx = true; 
               mouseleft = false;
               shop_row=0;               
               tune_up_page = -1;   
           }    
           
       }   
       else
       {
           Set_Sprite(3, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // SELL SIGN 
           button2_snd = false;      
       }
       
       if(tune_up_page == -1)
           sprite[19].alpha = 0.0; // Back button
       else
           sprite[19].alpha = 1.0; // Back button
           
       // Buttons - Back Button
       if(hud[2].alpha == 0.0)       
       if(sprite[19].alpha == 1.0)                   
       if(( mouseX < (sprite[19].w + sprite[19].box_width) )
       &&( mouseX > sprite[19].w)                            
       &&( mouseY < (sprite[19].z + sprite[19].box_height) )
       &&( mouseY > sprite[19].z)) 
       {
           
           if(mouseleft == true || DX_SHOOT == true) 
           {
			   DX_SHOOT = false;
               tune_up_page = -1;
               pick_up_sfx = true; 
               mouseleft = false; 
           }    
           
       }  
                       
       // Buttons - TUNE-UP
       if(hud[2].alpha == 0.0)       
       if(sprite[4].grab_switch == true)                   
       if(( mouseX < (sprite[4].w + sprite[4].box_width) )
       &&( mouseX > sprite[4].w)                            
       &&( mouseY < (sprite[4].z + sprite[4].box_height) )
       &&( mouseY > sprite[4].z)) 
       {
    
           sprintf( counter[5].word, "Upgrade^Item");
                        
           counter[5].length = 1; 
            
           msg_left=true;   
                
           if( button3_snd == false)
           {
               radio_sfx = true;
               button3_snd = true;
           }   
                                
           Set_Sprite(4, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
           
           if(mouseleft == true || DX_SHOOT == true) 
           {
			   DX_SHOOT = false;
               shop_sequence = SHOP_TUNE;
               shop_row=0;
               sprite[0].grab_switch = true; 
               sprite[2].grab_switch = true;
               sprite[3].grab_switch = true;
               sprite[4].grab_switch = false; 
               pick_up_sfx = true; 
               mouseleft = false;
               tune_up_page = -1; 
           }    
           
       }  
       else
           button3_snd = true;
                          
       // Buttons - Up Arrow
       if(hud[2].alpha == 0.0)       
       if(sprite[16].grab_switch == true)                   
       if( (( mouseX < (sprite[16].w + sprite[16].box_width) )
       &&( mouseX > sprite[16].w)                            
       &&( mouseY < (sprite[16].z + sprite[16].box_height) )
       &&( mouseY > sprite[16].z)) 
       || mousewheel == UP
       )
       {
           if(mouseleft == true  || DX_SHOOT == true || mousewheel == UP)
           if(shop_sequence != SHOP_TUNE || tune_up_page == -1)           
           if((int)TimerGetTime() > scroll_timer)           
           {           
			   DX_SHOOT = false;
               shop_row--;
               if(shop_row < 0)
                   shop_row = 0;
               if(mousewheel == RESET)
                   pick_up_sfx = true; 
               scroll_timer = (int)TimerGetTime()+125;
           }
                
           if( button4_snd == false)
           {
               radio_sfx = true;
               button4_snd = true;
           }            
       }    
       else
           button4_snd = false;
           
       // Buttons - Down Arrow
       if(hud[2].alpha == 0.0)       
       if(sprite[15].grab_switch == true)                   
       if((( mouseX < (sprite[15].w + sprite[15].box_width) )
       &&( mouseX > sprite[15].w)                            
       &&( mouseY < (sprite[15].z + sprite[15].box_height) )
       &&( mouseY > sprite[15].z))
       || mousewheel == DOWN
       ) 
       { 
           if(mouseleft == true  || DX_SHOOT == true || mousewheel == DOWN)
           if(shop_sequence != SHOP_TUNE || tune_up_page == -1)
           if((int)TimerGetTime() > scroll_timer)
           {
			   DX_SHOOT = false;
               shop_row++;
               if(shop_row > 24)
                   shop_row = 24;
               if(mousewheel == RESET)
                   pick_up_sfx = true; 
               scroll_timer = (int)TimerGetTime()+125;
           }
                
           if( button5_snd == false)
           {
               radio_sfx = true;
               button5_snd = true;
           }               
       }  
       else
           button5_snd = false;
                   
       // Calculate Tab on scrollbar 
       
       sprite[18].y = base_height - ( ((base_height - sprite[17].y)/24) * shop_row);

	   if(shop_sequence == SHOP_SELL)            
       for(int i=0;i<32;i++)
       {
           shop[i] = SHOP_NONE;
           shop_s[i] = SHOP_NONE;
           shop_cost[i] = 0; 
       }    
                                       
       if(shop_sequence == SHOP_BUY)
       {
                        
		   if(st_passive_discount == 0)
		       discount = 0; 		   
		   if(st_passive_discount == 1)
		       discount = DISCOUNT_BOOST1;    	
		   if(st_passive_discount == 2)
		       discount = DISCOUNT_BOOST2; 
		   if(st_passive_discount == 3)
		       discount = DISCOUNT_BOOST3; 
		   if(st_passive_discount == 4)
		       discount = DISCOUNT_BOOST4; 
		   if(st_passive_discount == 5)
		       discount = DISCOUNT_BOOST5; 
		   if(st_passive_discount == 6)
		       discount = DISCOUNT_BOOST6; 
	           
           for(int i=0;i<shop_count;i++) 
           { 

		   // Rifles..
           if(shop[i] == SHOP_FARMERS_RIFLE) 
             shop_cost[i]= SHOP_FARMERS_RIFLE_COST;
             
           if(shop[i] == SHOP_HUNTER_RIFLE)
             shop_cost[i]= SHOP_HUNTER_RIFLE_COST;

           if(shop[i] == SHOP_ENFIELD_RIFLE) 
             shop_cost[i]= SHOP_ENFIELD_RIFLE_COST;
             
           if(shop[i] == SHOP_ENFIELDK_RIFLE)
             shop_cost[i]= SHOP_ENFIELDK_RIFLE_COST;
                   
           if(shop[i] == SHOP_MAUSER_RIFLE) 
             shop_cost[i]= SHOP_MAUSER_RIFLE_COST;
             
           if(shop[i] == SHOP_MAUSERK_RIFLE)
             shop_cost[i]= SHOP_MAUSERK_RIFLE_COST;

           if(shop[i] == SHOP_CARBINE_RIFLE) 
             shop_cost[i]= SHOP_CARBINE_RIFLE_COST;
             
           if(shop[i] == SHOP_CARBINEK_RIFLE)
             shop_cost[i]= SHOP_CARBINEK_RIFLE_COST;
                   
           if(shop[i] == SHOP_GEWEHR_RIFLE) 
             shop_cost[i]= SHOP_GEWEHR_RIFLE_COST;
             
           if(shop[i] == SHOP_GEWEHRK_RIFLE) 
             shop_cost[i]= SHOP_GEWEHRK_RIFLE_COST;

           if(shop[i] == SHOP_HEINRICH_RIFLE) 
             shop_cost[i]= SHOP_HEINRICH_RIFLE_COST;
             
           if(shop[i] == SHOP_HEINRICHK_RIFLE)
             shop_cost[i]= SHOP_HEINRICHK_RIFLE_COST;
             
           if(shop[i] == SHOP_WINCHESTER_RIFLE)
             shop_cost[i]= SHOP_WINCHESTER_RIFLE_COST;                  

		   // Shotguns..	
           if(shop[i] == SHOP_FARMERS_SHOTGUN)
               shop_cost[i]= SHOP_FARMERS_SHOTGUN_COST;      
                        
           if(shop[i] == SHOP_ARMY_SHOTGUN)
               shop_cost[i]= SHOP_ARMY_SHOTGUN_COST;
                          
           if(shop[i] == SHOP_THOMPSOM_MACHINE)
              shop_cost[i]= SHOP_THOMPSOM_MACHINE_COST;          

		   // Pistols..           
           if(shop[i] == SHOP_TRAINING_PISTOL)
               shop_cost[i]= SHOP_TRAINING_PISTOL_COST;        
           
           if(shop[i] == SHOP_WEBLEY_PISTOL)
               shop_cost[i]= SHOP_WEBLEY_PISTOL_COST;
                          
           if(shop[i] == SHOP_LUGER_PISTOL)
               shop_cost[i]= SHOP_LUGER_PISTOL_COST;
           
           if(shop[i] == SHOP_LUGERK_PISTOL)
               shop_cost[i]= SHOP_LUGERK_PISTOL_COST;
           
           if(shop[i] == SHOP_WESTON_PISTOL)
               shop_cost[i]= SHOP_WESTON_PISTOL_COST;
           
           if(shop[i] == SHOP_WESTONK_PISTOL)
               shop_cost[i]= SHOP_WESTONK_PISTOL_COST;
                          
           if(shop[i] == SHOP_MAUSER_PISTOL)
               shop_cost[i]= SHOP_MAUSER_PISTOL_COST;
           
           if(shop[i] == SHOP_MAUSERK_PISTOL)
               shop_cost[i]= SHOP_MAUSERK_PISTOL_COST;
           
           if(shop[i] == SHOP_COLT_PISTOL)
               shop_cost[i]= SHOP_COLT_PISTOL_COST;
           
           if(shop[i] == SHOP_COLTK_PISTOL)
               shop_cost[i]= SHOP_COLTK_PISTOL_COST;  
                          
           if(shop[i] == SHOP_SAVAGE_PISTOL)
               shop_cost[i]= SHOP_SAVAGE_PISTOL_COST;
           
           if(shop[i] == SHOP_SAVAGEK_PISTOL)
               shop_cost[i]= SHOP_SAVAGEK_PISTOL_COST;
           
           if(shop[i] == SHOP_NAVYCOLT_PISTOL)
               shop_cost[i]= SHOP_NAVYCOLT_PISTOL_COST;


		   // Grenades..                                                          
           if(shop[i] == SHOP_BLACK_GRENADE) 
               shop_cost[i]= SHOP_BLACK_GRENADE_COST * SHOP_AMOUNT_BLACK_GRENADE;
                                                        
           if(shop[i] == SHOP_GREEN_GRENADE)
               shop_cost[i]= SHOP_GREEN_GRENADE_COST * SHOP_AMOUNT_GREEN_GRENADE;

           if(shop[i] == SHOP_MOLOTOV_GRENADE)
               shop_cost[i]= SHOP_MOLOTOV_GRENADE_COST * SHOP_AMOUNT_MOLOTOV;
           
           if(shop[i] == SHOP_AMPUOLE)
               shop_cost[i]= SHOP_AMPUOLE_COST;

           if(shop[i] == SHOP_SILVER_WATCH) 
             shop_cost[i]= SHOP_SILVER_WATCH_COST;

           if(shop[i] == SHOP_TRAP_MINE) 
             shop_cost[i]= SHOP_TRAP_MINE_COST;

           if(shop[i] == SHOP_TRAP_DECOY) 
             shop_cost[i]= SHOP_TRAP_DECOY_COST;

           if(shop[i] == SHOP_SCOPE)
               shop_cost[i]= SHOP_SCOPE_COST;

           if(shop[i] == SHOP_SCOPE2) 
               shop_cost[i]= SHOP_SCOPE2_COST;

           if(shop[i] == SHOP_SCOPE3) 
               shop_cost[i]= SHOP_SCOPE3_COST;

           if(shop[i] == SHOP_SCOPE4) 
               shop_cost[i]= SHOP_SCOPE4_COST; 

           if(shop[i] == SHOP_SCOPE5) 
               shop_cost[i]= SHOP_SCOPE5_COST; 

           if(shop[i] == SHOP_SCOPE6)  
               shop_cost[i]= SHOP_SCOPE6_COST; 

           if(shop[i] == SHOP_DISCOUNT)
               shop_cost[i]= SHOP_DISCOUNT_COST;

           if(shop[i] == SHOP_DISCOUNT1)
               shop_cost[i]= SHOP_DISCOUNT1_COST;

           if(shop[i] == SHOP_DISCOUNT2) 
               shop_cost[i]= SHOP_DISCOUNT2_COST;

           if(shop[i] == SHOP_DISCOUNT3) 
               shop_cost[i]= SHOP_DISCOUNT3_COST;

           if(shop[i] == SHOP_DISCOUNT4) 
               shop_cost[i]= SHOP_DISCOUNT4_COST; 

           if(shop[i] == SHOP_DISCOUNT5) 
               shop_cost[i]= SHOP_DISCOUNT5_COST; 

           if(shop[i] == SHOP_FLAK)
               shop_cost[i]= SHOP_FLAK_COST;

           if(shop[i] == SHOP_FLAK2)
               shop_cost[i]= SHOP_FLAK2_COST;

           if(shop[i] == SHOP_FLAK3)
               shop_cost[i]= SHOP_FLAK3_COST;

           if(shop[i] == SHOP_FLAK4) 
               shop_cost[i]= SHOP_FLAK4_COST;

           if(shop[i] == SHOP_FLAK5) 
               shop_cost[i]= SHOP_FLAK5_COST;

           if(shop[i] == SHOP_FLAK6) 
               shop_cost[i]= SHOP_FLAK6_COST;

           if(shop[i] == SHOP_BAYONET)
               shop_cost[i]= SHOP_BAYONET_COST;

           if(shop[i] == SHOP_BAYONET2)
               shop_cost[i]= SHOP_BAYONET2_COST;

           if(shop[i] == SHOP_BAYONET3)
               shop_cost[i]= SHOP_BAYONET3_COST;

           if(shop[i] == SHOP_BAYONET4) 
               shop_cost[i]= SHOP_BAYONET4_COST;

           if(shop[i] == SHOP_BAYONET5)  
               shop_cost[i]= SHOP_BAYONET5_COST;

           if(shop[i] == SHOP_BAYONET6)  
               shop_cost[i]= SHOP_BAYONET6_COST;

           if(shop[i] == SHOP_MEDICAL)
               shop_cost[i]= SHOP_MEDICAL_COST;

           if(shop[i] == SHOP_MEDICAL2)
               shop_cost[i]= SHOP_MEDICAL2_COST;

           if(shop[i] == SHOP_MEDICAL3)
               shop_cost[i]= SHOP_MEDICAL3_COST;

           if(shop[i] == SHOP_MEDICAL4) 
               shop_cost[i]= SHOP_MEDICAL4_COST;

           if(shop[i] == SHOP_MEDICAL5) 
               shop_cost[i]= SHOP_MEDICAL5_COST;

           if(shop[i] == SHOP_MEDICAL6) 
               shop_cost[i]= SHOP_MEDICAL6_COST;
           
           if(shop[i] == SHOP_MEDAL)  
		   { 
  
        			if(shop_value[i] > 0)                   
           				shop_cost[i] = shop_value[i] * 50;   
       				if(shop_value[i] >= 5)                   
           				shop_cost[i] = shop_value[i] * 100; 
       				if(shop_value[i] >= 10)                   
           				shop_cost[i] = shop_value[i] * 150; 
       				if(shop_value[i] >= 15)                   
           				shop_cost[i] = shop_value[i] * 200;  
       				if(shop_value[i] >= 20)                   
           				shop_cost[i] = shop_value[i] * 275; 
       				if(shop_value[i] >= 25)                    
           				shop_cost[i] = shop_value[i] * 300;  
       				if(shop_value[i] >= 30)                   
           				shop_cost[i] = shop_value[i] * 350;    
           } 
           if(shop[i] == SHOP_TINHAT) 
		   {
   			    shop_cost[i] = shop_value[i] * 75;   
           }
           if(shop[i] == SHOP_SHOES) 
		   { 
   			    shop_cost[i] = shop_value[i] * 75; 
           }
                                                                                                                      
           if(shop[i] == SHOP_HEALTH)
               shop_cost[i]= SHOP_HEALTH_COST;
                                                                                                                      
           if(shop[i] == SHOP_AMPUOLE)
               shop_cost[i]= SHOP_AMPUOLE_COST;
           
           if(shop[i] == SHOP_HGUN_AMMO)   
               shop_cost[i]= SHOP_HGUN_AMMO_COST * SHOP_AMOUNT_HGUN_AMMO;
               
           if(shop[i] == SHOP_BULLETS)
               shop_cost[i]= SHOP_BULLETS_COST * SHOP_AMOUNT_BULLETS;                        
               
           if(shop[i] == SHOP_SHELLS)
               shop_cost[i]= SHOP_SHELLS_COST * SHOP_AMOUNT_SHELLS;                        
               
           if(shop[i] == SHOP_AMMO) 
               shop_cost[i]= SHOP_AMMO_COST * SHOP_AMOUNT_AMMO;
               
           if(shop[i] == SHOP_BUY_GOLFCLUBS) 
               shop_cost[i]= SHOP_BUY_GOLFCLUBS_COST;
               
           if(shop[i] == SHOP_BUY_PIGGYBANK) 
               shop_cost[i]= SHOP_BUY_PIGGYBANK_COST;
               
           if(shop[i] == SHOP_BUY_FLAG) 
               shop_cost[i]= SHOP_BUY_FLAG_COST;
               
           if(shop[i] == SHOP_BUY_FIREVEST) 
               shop_cost[i]= SHOP_BUY_FIREVEST_COST;                                            
               
           if(shop[i] == SHOP_BUY_GASMASK) 
               shop_cost[i]= SHOP_BUY_GASMASK_COST; 

		   if(discount != 0)  
		   {
			   if(shop_cost[i] < 100)
			   {
			       shop_cost[i]*=10; 
				   shop_cost[i] -= ((shop_cost[i]/100) * discount);
			       shop_cost[i]/=10;
			   }	
			   else	
			       shop_cost[i] -= ((shop_cost[i]/100) * discount);		
		   }	
                                             
           }   
                              
       }  
       
       // Calculate Upgrades available for weapon
       if(shop_sequence == SHOP_TUNE && tune_up_page != -1)
       {
                        
           index = 0; 
           
           if(player_inv[tune_up_page] == INV_HELMET 
           || player_inv[tune_up_page]  == INV_HELMET_A 
           || player_inv[tune_up_page]  == INV_HELMET_E
           || player_inv[tune_up_page]  == INV_BOOT 
           || player_inv[tune_up_page]  == INV_BOOT_E
           || player_inv[tune_up_page]  == INV_BOOT_A 
           )      
           {
                                        
           if(GetUpgradesItems( tune_up_page, 1, GET_SHOP) > 0)
           {   
               shop[index]      = ishop;  
               shop_cost[index] = ishop_cost;
                             
               shop_sell_id[index] = tune_up_page;
               index++;  
           }
               
           if(GetUpgradesItems( tune_up_page, 2, GET_SHOP) > 0)   
           {   
               shop[index]      = ishop;
               shop_cost[index] = ishop_cost;
                             
               shop_sell_id[index] = tune_up_page;
               index++;  
           }                                         
                                       
           }
           else
           {
               
           if(GetUpgrades( tune_up_page, 1, GET_SHOP) > 0)
           {   
               shop[index]      = ishop;
               shop_cost[index] = ishop_cost;
                             
               shop_sell_id[index] = tune_up_page;
               index++;  
           }
               
           if(GetUpgrades( tune_up_page, 2, GET_SHOP) > 0)   
           {   
               shop[index]      = ishop;
               shop_cost[index] = ishop_cost;
                             
               shop_sell_id[index] = tune_up_page;
               index++;  
           }                             
           if(GetUpgrades( tune_up_page, 3, GET_SHOP) > 0)   
           {   
               shop[index]      = ishop;
               shop_cost[index] = ishop_cost;
                             
               shop_sell_id[index] = tune_up_page;
               index++;  
           }                             
           if(GetUpgrades( tune_up_page, 4, GET_SHOP) > 0)   
           {   
               shop[index]      = ishop;
               shop_cost[index] = ishop_cost;
                             
               shop_sell_id[index] = tune_up_page;
               index++;  
           }                           
           if(GetUpgrades( tune_up_page, 5, GET_SHOP) > 0)   
           {   
               shop[index]      = ishop;
               shop_cost[index] = ishop_cost;
                             
               shop_sell_id[index] = tune_up_page;
               index++;  
           }
           if(GetUpgrades( tune_up_page, 6, GET_SHOP) > 0)   
           {   
               shop[index]      = ishop;
               shop_cost[index] = ishop_cost;
                             
               shop_sell_id[index] = tune_up_page;
               index++;  
           }
                       
           }
           
       }
       
       if(shop_sequence == SHOP_SELL || (shop_sequence == SHOP_TUNE && tune_up_page == -1) )        
       { 
                        
           index = 0;
           
           memset(shop_s, SHOP_NONE, sizeof(shop_s));
           
           // Weapons...  
           for(int i=0;i<16;i++)                         
           {
                  
               if(player_inv[i] == INV_RIFLE_A) // Tune-UP
               {
                   shop_s[index] = SHOP_SPECIAL;
                                
                   if(player_inv_value[i] == FARMERS_RIFLE)
                   {                                   
                       shop[index] = SHOP_FARMERS_RIFLE;
                       shop_cost[index]= SHOP_FARMERS_RIFLE_COST/COST_DIVISION;
                   }
                   if(player_inv_value[i] == HUNTER_RIFLE)
                   {                                   
                       shop[index] = SHOP_HUNTER_RIFLE;
                       shop_cost[index]= SHOP_HUNTER_RIFLE_COST/COST_DIVISION;
                   }
                   if(player_inv_value[i] == ENFIELD_RIFLE)
                   {                                   
                       shop[index] = SHOP_ENFIELD_RIFLE;
                       shop_cost[index]= SHOP_ENFIELD_RIFLE_COST/COST_DIVISION;
                   }
                   if(player_inv_value[i] == ENFIELDK_RIFLE)
                   {                                   
                       shop[index] = SHOP_ENFIELDK_RIFLE;
                       shop_cost[index]= SHOP_ENFIELDK_RIFLE_COST/COST_DIVISION;
                   }
                                
                   if(player_inv_value[i] == MAUSER_RIFLE)
                   {                                   
                       shop[index] = SHOP_MAUSER_RIFLE;
                       shop_cost[index]= SHOP_MAUSER_RIFLE_COST/COST_DIVISION;
                   }
                   if(player_inv_value[i] == MAUSERK_RIFLE)
                   {                                   
                       shop[index] = SHOP_MAUSERK_RIFLE;
                       shop_cost[index]= SHOP_MAUSERK_RIFLE_COST/COST_DIVISION;
                   }
                   if(player_inv_value[i] == CARBINE_RIFLE)
                   {                                   
                       shop[index] = SHOP_CARBINE_RIFLE;
                       shop_cost[index]= SHOP_CARBINE_RIFLE_COST/COST_DIVISION;
                   }
                   if(player_inv_value[i] == CARBINEK_RIFLE)
                   {                                   
                       shop[index] = SHOP_CARBINEK_RIFLE;
                       shop_cost[index]= SHOP_CARBINEK_RIFLE_COST/COST_DIVISION;
                   }
                                
                   if(player_inv_value[i] == GEWEHR_RIFLE)
                   {                                   
                       shop[index] = SHOP_GEWEHR_RIFLE;
                       shop_cost[index]= SHOP_GEWEHR_RIFLE_COST/COST_DIVISION;
                   }
                   if(player_inv_value[i] == GEWEHRK_RIFLE)
                   {                                   
                       shop[index] = SHOP_GEWEHRK_RIFLE;
                       shop_cost[index]= SHOP_GEWEHRK_RIFLE_COST/COST_DIVISION;
                   }
                   if(player_inv_value[i] == HEINRICH_RIFLE)
                   {                                   
                       shop[index] = SHOP_HEINRICH_RIFLE;
                       shop_cost[index]= SHOP_HEINRICH_RIFLE_COST/COST_DIVISION;
                   }
                   if(player_inv_value[i] == HEINRICHK_RIFLE)
                   {                                   
                       shop[index] = SHOP_HEINRICHK_RIFLE;
                       shop_cost[index]= SHOP_HEINRICHK_RIFLE_COST/COST_DIVISION;
                   }
                   if(player_inv_value[i] == WINCHESTER_RIFLE)
                   {                                   
                       shop[index] = SHOP_WINCHESTER_RIFLE;
                       shop_cost[index]= SHOP_WINCHESTER_RIFLE_COST/COST_DIVISION;
                   }

                   
                   shop_sell_id[index] = i;
                   index++;
               } 
		   }	
           for(int i=0;i<16;i++)                         
           {
               if(player_inv[i] == INV_PISTOL_A) // Tune-UP
               {
                   shop_s[index] = SHOP_SPECIAL;
                                                       
                   if(player_inv_value[i] == TRAINING_PISTOL)
                   {             
                       shop[index] = SHOP_TRAINING_PISTOL; 
                       shop_cost[index]= SHOP_TRAINING_PISTOL_COST/COST_DIVISION;   
                   }
                   if(player_inv_value[i] == WEBLEY_PISTOL)
                   {             
                       shop[index] = SHOP_WEBLEY_PISTOL;
                       shop_cost[index]= SHOP_WEBLEY_PISTOL_COST/COST_DIVISION; 
                   }                   
                   if(player_inv_value[i] == LUGER_PISTOL)
                   {             
                       shop[index] = SHOP_LUGER_PISTOL;
                       shop_cost[index]= SHOP_LUGER_PISTOL_COST/COST_DIVISION;    
                   }
                   if(player_inv_value[i] == LUGERK_PISTOL)
                   {             
                       shop[index] = SHOP_LUGERK_PISTOL;
                       shop_cost[index]= SHOP_LUGERK_PISTOL_COST/COST_DIVISION;    
                   }  
                   if(player_inv_value[i] == WESTON_PISTOL)
                   {             
                       shop[index] = SHOP_WESTON_PISTOL; 
                       shop_cost[index]= SHOP_WESTON_PISTOL_COST/COST_DIVISION;   
                   }
                   if(player_inv_value[i] == WESTONK_PISTOL)
                   {             
                       shop[index] = SHOP_WESTONK_PISTOL;
                       shop_cost[index]= SHOP_WESTONK_PISTOL_COST/COST_DIVISION; 
                   }                   
                   if(player_inv_value[i] == MAUSER_PISTOL)
                   {             
                       shop[index] = SHOP_MAUSER_PISTOL;
                       shop_cost[index]= SHOP_MAUSER_PISTOL_COST/COST_DIVISION;    
                   }
                   if(player_inv_value[i] == MAUSERK_PISTOL)
                   {             
                       shop[index] = SHOP_MAUSERK_PISTOL;
                       shop_cost[index]= SHOP_MAUSERK_PISTOL_COST/COST_DIVISION;    
                   }  
                   if(player_inv_value[i] == COLT_PISTOL)
                   {             
                       shop[index] = SHOP_COLT_PISTOL; 
                       shop_cost[index]= SHOP_COLT_PISTOL_COST/COST_DIVISION;   
                   }
                   if(player_inv_value[i] == COLTK_PISTOL)
                   {             
                       shop[index] = SHOP_COLTK_PISTOL;
                       shop_cost[index]= SHOP_COLTK_PISTOL_COST/COST_DIVISION; 
                   }                   
                   if(player_inv_value[i] == SAVAGE_PISTOL)
                   {             
                       shop[index] = SHOP_SAVAGE_PISTOL;
                       shop_cost[index]= SHOP_SAVAGE_PISTOL_COST/COST_DIVISION;    
                   }
                   if(player_inv_value[i] == SAVAGEK_PISTOL)
                   {             
                       shop[index] = SHOP_SAVAGEK_PISTOL;
                       shop_cost[index]= SHOP_SAVAGEK_PISTOL_COST/COST_DIVISION;    
                   }  
                   if(player_inv_value[i] == NAVYCOLT_PISTOL)
                   {             
                       shop[index] = SHOP_NAVYCOLT_PISTOL;
                       shop_cost[index]= SHOP_NAVYCOLT_PISTOL_COST/COST_DIVISION;    
                   }  
   
                   shop_sell_id[index] = i;
                   index++;                              
               }
               if(player_inv[i] == INV_SHOTGUN_A) // Tune-UP
               {
                   shop_s[index] = SHOP_SPECIAL;
                                                       
                   if(player_inv_value[i] == FARMERS_SHOTGUN)
                   {                                  
                       shop[index] = SHOP_FARMERS_SHOTGUN;
                       shop_cost[index]= SHOP_FARMERS_SHOTGUN_COST/COST_DIVISION;    
                       
                       shop_cost[index] += GetUpgradeSell(i);                       
                   }
                   if(player_inv_value[i] == ARMY_SHOTGUN)
                   {                                  
                       shop[index] = SHOP_ARMY_SHOTGUN;
                       shop_cost[index]= SHOP_ARMY_SHOTGUN_COST/COST_DIVISION;    
                       
                       shop_cost[index] += GetUpgradeSell(i);                       
                   }
                   shop_sell_id[index] = i;
                   index++;                              
               }               
               if(player_inv[i] == INV_MACHINE_A) // Tune-UP
               {
                   shop_s[index] = SHOP_SPECIAL;
                                                       
                   shop[index] = SHOP_THOMPSOM_MACHINE;
                   shop_cost[index]= SHOP_THOMPSOM_MACHINE_COST/COST_DIVISION;
                       
                   shop_cost[index] += GetUpgradeSell(i);                   
                   
                   shop_sell_id[index] = i;
                   index++;  
               }  
               
           }

		   // Medals...                   
           for(int i=0;i<16;i++)  
           {

	     
               if(player_inv[i] == INV_MEDAL || player_inv[i] == INV_MEDAL_A || player_inv[i] == INV_MEDAL_E)
               {
                   
                    shop[index] = SHOP_MEDAL;          
 
        			if(player_inv_value[i] > 0)                    
           				shop_cost[index] = player_inv_value[i] * 50;   
       				if(player_inv_value[i] >= 5)                   
           				shop_cost[index] = player_inv_value[i] * 100; 
       				if(player_inv_value[i] >= 10)                   
           				shop_cost[index] = player_inv_value[i] * 150; 
       				if(player_inv_value[i] >= 15)                   
           				shop_cost[index] = player_inv_value[i] * 200;  
       				if(player_inv_value[i] >= 20)                   
           				shop_cost[index] = player_inv_value[i] * 275; 
       				if(player_inv_value[i] >= 25)                    
           				shop_cost[index] = player_inv_value[i] * 300;  
       				if(player_inv_value[i] >= 30)                   
           				shop_cost[index] = player_inv_value[i] * 350;  

				   if( COST_DIVISION > 0)
	                   shop_cost[index] /= COST_DIVISION;

				   if(shop_sequence == SHOP_SELL)
				   {
				       shop_value[index] = player_inv_value[i];	 
                       shop_value1[index] = player_inv_value1[i]; 
				   }  
                                                       
                   shop_sell_id[index] = i;
                   index++;                    
               }                  
           }    

           // Helmets...                   
           for(int i=0;i<16;i++)  
           {
                                  
               if(player_inv[i] == INV_HELMET || player_inv[i] == INV_HELMET_A || player_inv[i] == INV_HELMET_E)
               {

                    shop[index] = SHOP_TINHAT;
 
			        if(player_inv_value[i] >= 0)             
          				shop_cost[index] = player_inv_value[i] * 50;                      
			        if(player_inv_value[i] >= 10)             
			            shop_cost[index] = player_inv_value[i]  * 75; 
			        if(player_inv_value[i] >= 20)             
				        shop_cost[index] = player_inv_value[i]  * 100;            
			        if(player_inv_value[i] >= 30)             
				        shop_cost[index] = player_inv_value[i]  * 150; 

				   if( COST_DIVISION > 0)
	                   shop_cost[index] /= COST_DIVISION;

				   if(shop_sequence == SHOP_SELL)
				   {
				       shop_value[index] = player_inv_value[i];	 
                       shop_value1[index] = player_inv_value1[i]; 
				   }
                                                         
                   shop_sell_id[index] = i;
                   index++;                   
               }      
		}
           // Boots...                   
           for(int i=0;i<16;i++)  
           {
                 
               if(player_inv[i] == INV_BOOT || player_inv[i] == INV_BOOT_A || player_inv[i] == INV_BOOT_E)
               {
                   
                    shop[index] = SHOP_SHOES; 

			        if(player_inv_value[i] >= 0)             
          				shop_cost[index] = player_inv_value[i] * 50;                      
			        if(player_inv_value[i] >= 10)             
			            shop_cost[index] = player_inv_value[i]  * 75; 
			        if(player_inv_value[i] >= 20)             
				        shop_cost[index] = player_inv_value[i]  * 100;            
			        if(player_inv_value[i] >= 30)             
				        shop_cost[index] = player_inv_value[i]  * 150; 

					if( COST_DIVISION > 0)
	                   shop_cost[index] /= COST_DIVISION;

				   if(shop_sequence == SHOP_SELL)
				   {
				       shop_value[index] = player_inv_value[i];	 
                       shop_value1[index] = player_inv_value1[i]; 
				   }
                                                                              
                   shop_sell_id[index] = i;
                   index++;                   
               }   
			}
 
           // Grenades...                   
           for(int i=0;i<16;i++) 
           {
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_GRENADE_A || player_inv[i] == INV_GRENADE_E)
               {
                   shop_s[index] = SHOP_SPECIAL;
                   
				   if(player_inv_value[i] == BLACK_GRENADE)
				   {
	                   shop[index] = SHOP_BLACK_GRENADE;    
					   shop_cost[index]= (player_inv_value2[i]*SHOP_BLACK_GRENADE_COST)/2;
	                   //shop_cost[index]= (SHOP_BLACK_GRENADE_COST)/COST_DIVISION; // *player_inv_value[i]
				   }
                   
				   if(player_inv_value[i] == GREEN_GRENADE)
				   { 
	                   shop[index] = SHOP_GREEN_GRENADE;   
					   shop_cost[index]= (player_inv_value2[i]*SHOP_GREEN_GRENADE_COST)/2;
	                   //shop_cost[index]= (SHOP_GREEN_GRENADE_COST)/COST_DIVISION; // *player_inv_value[i]
				   }
                   
				   if(player_inv_value[i] == MOLOTOV_GRENADE)
				   {
	                   shop[index] = SHOP_MOLOTOV_GRENADE;   
					   shop_cost[index]= (player_inv_value2[i]*SHOP_MOLOTOV_GRENADE_COST)/2;
	                   //shop_cost[index]= (SHOP_MOLOTOV_GRENADE_COST)/COST_DIVISION; // *player_inv_value[i]
				   }

                   shop_sell_id[index] = i;
                   index++;                                    
               } 
           }           
		   // Traps...
           for(int i=0;i<16;i++) 
               if(player_inv[i] == INV_TRAP || player_inv[i] == INV_TRAP_A || player_inv[i] == INV_TRAP_E)
               {
                   
				    if(player_inv_value[i] == TRAP_TYPE_DECOY)
					{
	                    shop[index] = SHOP_TRAP_DECOY;          
						shop_cost[index] = SHOP_TRAP_DECOY_COST;  
					}
					                   
				    if(player_inv_value[i] == TRAP_TYPE_MINE)
					{
	                    shop[index] = SHOP_TRAP_MINE;          
						shop_cost[index] = SHOP_TRAP_MINE_COST;  
					}

				   if( COST_DIVISION > 0) 
	                   shop_cost[index] /= COST_DIVISION;

				   if(shop_sequence == SHOP_SELL) 
				   {
				       shop_value[index] = player_inv_value[i];	 
                       shop_value1[index] = player_inv_value3[i];  
				   }   
                                                       
                   shop_sell_id[index] = i;
                   index++;    
               }     
           // Ammo...                  
           for(int i=0;i<16;i++) 
           {
                                                   
               if(shop_sequence == SHOP_SELL)               
               if(player_inv[i] == INV_AMMO)
               {
                   shop[index] = SHOP_AMMO; 
                   shop_cost[index]= (player_inv_value[i]*SHOP_AMMO_COST)/2; 
                   shop_sell_id[index] = i;
                   index++;                  
               }
               if(shop_sequence == SHOP_SELL)                 
               if(player_inv[i] == INV_HGUN_AMMO)
               {
                   shop[index] = SHOP_HGUN_AMMO; 
                   shop_cost[index]= (player_inv_value[i]*SHOP_HGUN_AMMO_COST)/2; 
                   shop_sell_id[index] = i;
                   index++;                  
               } 
               if(shop_sequence == SHOP_SELL)               
               if(player_inv[i] == INV_SHELLS)
               {
                   shop[index] = SHOP_SHELLS; 
                   shop_cost[index]= (player_inv_value[i]*SHOP_SHELLS_COST)/2; 
                   shop_sell_id[index] = i;
                   index++;                  
               }
               if(shop_sequence == SHOP_SELL)               
               if(player_inv[i] == INV_BULLETS) 
               {
                   shop[index] = SHOP_BULLETS; 
                   shop_cost[index]= (player_inv_value[i]*SHOP_BULLETS_COST)/2; 
                   shop_sell_id[index] = i;
                   index++;                  
               }                
           }      

           // Gems...                           
           for(int i=0;i<16;i++) 
           {           
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 5)
               {
                   shop[index] = SHOP_BAR;   
                   shop_cost[index]= SHOP_BAR_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }   
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 6)
               {
                   shop[index] = SHOP_PIPE;   
                   shop_cost[index]= SHOP_PIPE_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }   
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 7)
               {
                   shop[index] = SHOP_PORTRAIT;   
                   shop_cost[index]= SHOP_PORTRAIT_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                     
               }  
           }  
             
           // Cards...                           
           for(int i=0;i<16;i++) 
           {    
               if(shop_sequence == SHOP_SELL)                
               if(player_inv[i] == INV_CARD)  
               {
                   shop[index] = SHOP_CARD; 

                   shop_cost[index]= SHOP_CARD_COST/COST_DIVISION; 
                       
                   shop_value[index] = player_inv_value[i];
                   
                   shop_sell_id[index] = i;
                   index++;                  
               }  
           }                 
           // Others...                   
           for(int i=0;i<16;i++) 
           {
                                  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_WATCH && player_inv_value[i] == 0)
               {
                   shop[index] = SHOP_BRASS_WATCH;   
                   shop_cost[index]= SHOP_BRASS_WATCH_COST/COST_DIVISION; 
                   shop_sell_id[index] = i;
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_WATCH && player_inv_value[i] == 1)
               {
                   shop[index] = SHOP_SILVER_WATCH;   
                   shop_cost[index]= SHOP_SILVER_WATCH_COST/COST_DIVISION; 
                   shop_sell_id[index] = i;
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_WATCH && player_inv_value[i] == 2)
               {
                   shop[index] = SHOP_GOLD_WATCH;   
                   shop_cost[index]= SHOP_GOLD_WATCH_COST/COST_DIVISION; 
                   shop_sell_id[index] = i;
                   index++;                                    
               }                                
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 3)
               {
                   shop[index] = SHOP_CROWN;   
                   shop_cost[index]= SHOP_CROWN_COST; // /COST_DIVISION
                   shop_sell_id[index] = i;
                   index++;                                    
               }   
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 4)
               {
                   shop[index] = SHOP_DIRTY;   
                   shop_cost[index]= SHOP_DIRTY_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }        
 
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 8)
               {
                   shop[index] = SHOP_SOCK;   
                   shop_cost[index]= SHOP_SOCK_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }   
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 9)
               {
                   shop[index] = SHOP_LANTERN;   
                   shop_cost[index]=SHOP_LANTERN_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 10)
               {
                   shop[index] = SHOP_TEDDY;   
                   shop_cost[index]= SHOP_TEDDY_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }     
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 11)
               {
                   shop[index] = SHOP_BOOKS;    
                   shop_cost[index]= SHOP_BOOKS_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }   
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 12)
               {
                   shop[index] = SHOP_ASHTRAY;   
                   shop_cost[index]= SHOP_ASHTRAY_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }   
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 13)
               {
                   shop[index] = SHOP_RUG;   
                   shop_cost[index]= SHOP_RUG_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 14)
               {
                   shop[index] = SHOP_CHAIR;   
                   shop_cost[index]= SHOP_CHAIR_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                      
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 15)
               {
                   shop[index] = SHOP_DIARY;   
                   shop_cost[index]= SHOP_DIARY_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }    
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 16)
               {
                   shop[index] = SHOP_GOLFCLUBS;   
                   shop_cost[index]= SHOP_GOLFCLUBS_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 17)
               {
                   shop[index] = SHOP_PAINTING;   
                   shop_cost[index]= SHOP_PAINTING_COST; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 18)
               {
                   shop[index] = SHOP_PIGGYBANK;   
                   shop_cost[index]= SHOP_PIGGYBANK_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 19)
               {
                   shop[index] = SHOP_BIBLE;   
                   shop_cost[index]= SHOP_BIBLE_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 20)
               {
                   shop[index] = SHOP_FLAG;   
                   shop_cost[index]= SHOP_FLAG_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 21)
               {
                   shop[index] = SHOP_BEDPAN;   
                   shop_cost[index]= SHOP_BEDPAN_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 22)
               {
                   shop[index] = SHOP_BOGROLL;   
                   shop_cost[index]= SHOP_BOGROLL_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 23)
               {
                   shop[index] = SHOP_PLATE;   
                   shop_cost[index]= SHOP_PLATE_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 24)
               {
                   shop[index] = SHOP_TEACUP;   
                   shop_cost[index]= SHOP_TEACUP_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 25)
               {
                   shop[index] = SHOP_HAMLET;   
                   shop_cost[index]= SHOP_HAMLET_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 26)
               {
                   shop[index] = SHOP_SNUFFBOX;   
                   shop_cost[index]= SHOP_SNUFFBOX_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 27)
               {
                   shop[index] = SHOP_TOYPLANE;   
                   shop_cost[index]= SHOP_TOYPLANE_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 28)
               {
                   shop[index] = SHOP_POSTER;   
                   shop_cost[index]= SHOP_POSTER_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }                  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 29)
               {
                   shop[index] = SHOP_FIREVEST;   
                   shop_cost[index]= SHOP_FIREVEST_COST/COST_DIVISION; 
                   shop_sell_id[index] = i; 
                   index++;                                    
               }                  
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_LETTERS && player_inv_value[i] == 30)
               {
                   shop[index] = SHOP_GASMASK;   
                   shop_cost[index]= SHOP_GASMASK_COST/COST_DIVISION; 
                   shop_sell_id[index] = i;  
                   index++;                                    
               }                                
                                                                                                                                                                                                                                                                                                       
               if(shop_sequence == SHOP_SELL)
               if(player_inv[i] == INV_APPLE) 
               {
                   shop[index] = SHOP_APPLE;   
                   shop_cost[index]= SHOP_APPLE_COST/COST_DIVISION; 
                   shop_sell_id[index] = i;
                   index++;                                    
               }         

               if(shop_sequence == SHOP_SELL)                 
               if(player_inv[i] == INV_HEALTH)
               {
                   shop[index] = SHOP_HEALTH; 
                   shop_cost[index]= SHOP_HEALTH_COST/COST_DIVISION; 
                   shop_sell_id[index] = i;
                   index++;                  
               }   
               if(shop_sequence == SHOP_SELL)                
               if(player_inv[i] == INV_AMPUOLE)
               {
                   shop[index] = SHOP_AMPUOLE; 
                   shop_cost[index]= SHOP_AMPUOLE_COST/COST_DIVISION; 
                   shop_sell_id[index] = i;
                   index++;                  
               }       

                                                                                                                                                
               if(index >= 32) 
                   break;
           
           }
       }    
       if(bump_timer==-1)
       {                               
          counter[3].x = 0.60f;    
          counter[3].y =  0.63f;  
          counter[3].width = 0.016f;
          counter[3].height = 0.048f;
       }
       else
       {                               
          counter[3].x = 0.60f;    
          counter[3].y =  0.63f;  
          counter[3].width = 0.018f;
          counter[3].height = 0.052f;
       }
       
       if((int)TimerGetTime() > bump_timer)
           bump_timer = -1;
       
       if(current_gold == -1)
           sprintf( counter[3].word, "%iG", 0); 
       else
           sprintf( counter[3].word, "%iG", player_inv_value[current_gold] ); 
       
       counter[3].alpha = 1.0f; 

       counter[0].x = -0.15f;    
       counter[0].y =  0.55f;  
       counter[0].width = 0.016f; 
       counter[0].height = 0.048f;

       counter[11].x =  0.50f;     
       counter[11].y =  0.55f;  
       counter[11].width = 0.016f; 
       counter[11].height = 0.048f;
        
       counter[11].alpha = 1.0f;
              
       if(shop_sequence != SHOP_TUNE || tune_up_page == -1) 
       {     
           sprintf( counter[0].word, "");
           sprintf( counter[11].word, "");
       }
           
  /*   if( shop_sequence == SHOP_TUNE)
       {
           sprite[21].alpha = 0.0f;
           sprite[22].alpha = 0.0f;
       }
       
      sprite[23].alpha = 0.0f; 
       sprite[24].alpha = 0.0f; 
       
       sprite[22].frame = sprite[21].frame;
       sprite[23].frame = sprite[21].frame; 
       sprite[24].frame = sprite[21].frame;
       
       sprite[22].cur = sprite[21].cur; 
       sprite[23].cur = sprite[21].cur;
       sprite[24].cur = sprite[21].cur;
                         
       if(shop_sequence == SHOP_TUNE && tune_up_page != -1)
       {
           if(shop_cost[0] != MAXIMUM_REACHED)             
               sprite[21].alpha = 1.0f;
               
           if(player_inv[tune_up_page] != INV_HELMET_A
           && player_inv[tune_up_page] != INV_BOOT_A)    
           if(shop_cost[1] != MAXIMUM_REACHED)             
              sprite[22].alpha = 1.0f;
              
           if(player_inv[tune_up_page] != INV_HELMET_A
           && player_inv[tune_up_page] != INV_BOOT_A)               
           if(shop_cost[2] != MAXIMUM_REACHED)             
               sprite[23].alpha = 1.0f;
               
           if(player_inv[tune_up_page] != INV_HELMET_A
           && player_inv[tune_up_page] != INV_BOOT_A)                
           if(shop_cost[3] != MAXIMUM_REACHED)             
               sprite[24].alpha = 1.0f; 
       }*/
       
       if(shop_sequence != SHOP_TUNE || tune_up_page == -1) 
       for(int i=shop_row;i<shop_row+8;i++)   // Works for Buy & Sell
	   if(i >= 0) 
       { 
               
           if(shop[i] == SHOP_FARMERS_RIFLE) 
               strcat(counter[0].word, "^(G)Farmers Rifle.........");
           if(shop[i] == SHOP_HUNTER_RIFLE) 
               strcat(counter[0].word, "^(G)Hunter Rifle..........");
           if(shop[i] == SHOP_ENFIELD_RIFLE) 
               strcat(counter[0].word, "^(G)Enfield Rifle.........");
           if(shop[i] == SHOP_ENFIELDK_RIFLE) 
               strcat(counter[0].word, "^(G)Enfield-K Rifle.......");
           if(shop[i] == SHOP_MAUSER_RIFLE) 
               strcat(counter[0].word, "^(G)Mauser Rifle..........");
           if(shop[i] == SHOP_MAUSERK_RIFLE) 
               strcat(counter[0].word, "^(G)Mauser-K Rifle........");
           if(shop[i] == SHOP_CARBINE_RIFLE) 
               strcat(counter[0].word, "^(G)Carbine Rifle.........");
           if(shop[i] == SHOP_CARBINEK_RIFLE) 
               strcat(counter[0].word, "^(G)Carbine-K Rifle.......");
           if(shop[i] == SHOP_GEWEHR_RIFLE) 
               strcat(counter[0].word, "^(G)Gewehr Rifle.........."); 
           if(shop[i] == SHOP_GEWEHRK_RIFLE) 
               strcat(counter[0].word, "^(G)Gewehr-K Rifle........");
           if(shop[i] == SHOP_HEINRICH_RIFLE) 
               strcat(counter[0].word, "^(G)Heinrich Rifle........");
           if(shop[i] == SHOP_HEINRICHK_RIFLE) 
               strcat(counter[0].word, "^(G)Heinrich-K Rifle......");
           if(shop[i] == SHOP_WINCHESTER_RIFLE) 
               strcat(counter[0].word, "^(G)Winchester Rifle......");


           if(shop[i] == SHOP_FARMERS_SHOTGUN)
           {        
               if(shop_sequence != SHOP_TUNE)
               {           
                           
                   if(shop_s[i] == SHOP_NONE || disable_s_text == true)             
                       strcat(counter[0].word, "^(G)Farmers Shotgun......");
                   if(shop_s[i] == SHOP_SPECIAL && disable_s_text == false)             
                       strcat(counter[0].word, "^(S)-Farmers Shotgun.....");
               
               }
               else
               {
                   if(shop_s[i] == SHOP_NONE || disable_s_text == true)             
                       strcat(counter[0].word, "^Upgrade - Farmers Shotgun");
                   if(shop_s[i] == SHOP_SPECIAL && disable_s_text == false)             
                       strcat(counter[0].word, "^Upgrade - (S)-Farmers Shotgun");                      
                   
                   if(Is_Available(shop_sell_id[i], i)==false)
                   { 
                   //    shop[i] = SHOP_MAXIMUM; 
                       shop_cost[i] = MAXIMUM_REACHED;
                   }
               }                   
           }     
           if(shop[i] == SHOP_ARMY_SHOTGUN)
           {        
               if(shop_sequence != SHOP_TUNE)        
               {             
                           
                   if(shop_s[i] == SHOP_NONE || disable_s_text == true)             
                       strcat(counter[0].word, "^(G)Combat Shotgun......");
                   if(shop_s[i] == SHOP_SPECIAL && disable_s_text == false)             
                       strcat(counter[0].word, "^(S)-Combat Shotgun.....");                             
                
               }                   
               else
               {

                   if(shop_s[i] == SHOP_NONE || disable_s_text == true)             
                       strcat(counter[0].word, "^Upgrade - Combat Shotgun");
                   if(shop_s[i] == SHOP_SPECIAL && disable_s_text == false)             
                       strcat(counter[0].word, "^Upgrade - (S)-Combat Shotgun");  
                                          
                   if(Is_Available(shop_sell_id[i], i)==false)
                   { 
                   //    shop[i] = SHOP_MAXIMUM; 
                       shop_cost[i] = MAXIMUM_REACHED;
                   }
               }                   
           }                         
           if(shop[i] == SHOP_THOMPSOM_MACHINE)  
           {        
               if(shop_sequence != SHOP_TUNE) 
               {                   

                   if(shop_s[i] == SHOP_NONE || disable_s_text == true)             
                       strcat(counter[0].word, "^(G)Vickers Machinegun...");
                   if(shop_s[i] == SHOP_SPECIAL && disable_s_text == false)             
                       strcat(counter[0].word, "^(S)-Vickers Machinegun..");  

                   
               } 
               else
               {

                   if(shop_s[i] == SHOP_NONE || disable_s_text == true)             
                       strcat(counter[0].word, "^Upgrade - Vickers Machinegun");
                   if(shop_s[i] == SHOP_SPECIAL && disable_s_text == false)             
                       strcat(counter[0].word, "^Upgrade - (S)-Vickers Machinegun");  
                                          
                   if(Is_Available(shop_sell_id[i], i)==false)
                   { 
                   //    shop[i] = SHOP_MAXIMUM; 
                       shop_cost[i] = MAXIMUM_REACHED;
                   }
               }
           }               
               
           if(shop[i] == SHOP_TRAINING_PISTOL) 
               strcat(counter[0].word, "^(G)Training Pistol.......");
           if(shop[i] == SHOP_WEBLEY_PISTOL) 
               strcat(counter[0].word, "^(G)Webley Pistol.........");
           if(shop[i] == SHOP_LUGER_PISTOL) 
               strcat(counter[0].word, "^(G)Luger Pistol..........");
           if(shop[i] == SHOP_LUGERK_PISTOL) 
               strcat(counter[0].word, "^(G)Luger-K Pistol........");
           if(shop[i] == SHOP_WESTON_PISTOL) 
               strcat(counter[0].word, "^(G)Weston Pistol.........");
           if(shop[i] == SHOP_WESTONK_PISTOL) 
               strcat(counter[0].word, "^(G)Weston-K Pistol.......");
           if(shop[i] == SHOP_MAUSER_PISTOL) 
               strcat(counter[0].word, "^(G)Mauser Pistol.........");
           if(shop[i] == SHOP_MAUSERK_PISTOL) 
               strcat(counter[0].word, "^(G)Mauser-K Pistol.......");
           if(shop[i] == SHOP_COLT_PISTOL)  
               strcat(counter[0].word, "^(G)Colt Pistol..........."); 
           if(shop[i] == SHOP_COLTK_PISTOL) 
               strcat(counter[0].word, "^(G)Colt-K Pistol.........");
           if(shop[i] == SHOP_SAVAGE_PISTOL) 
               strcat(counter[0].word, "^(G)Savage Pistol.........");
           if(shop[i] == SHOP_SAVAGEK_PISTOL) 
               strcat(counter[0].word, "^(G)Savage-K Pistol.......");
           if(shop[i] == SHOP_NAVYCOLT_PISTOL) 
               strcat(counter[0].word, "^(G)Navy Colt Pistol......");  
           
                                                            
           if(shop[i] == SHOP_BLACK_GRENADE)        
               strcat(counter[0].word, "^(S)Stick Grenades........");
           if(shop[i] == SHOP_GREEN_GRENADE)        
               strcat(counter[0].word, "^(S)Hand Grenades.........");
           if(shop[i] == SHOP_MOLOTOV_GRENADE)        
               strcat(counter[0].word, "^(S)Molotovs..............");
           if(shop[i] == SHOP_AMMO)        
               strcat(counter[0].word, "^(A)Rifle Ammo...........");               
           if(shop[i] == SHOP_HGUN_AMMO)        
               strcat(counter[0].word, "^(A)Handgun Ammo.........");               
           if(shop[i] == SHOP_SHELLS)        
               strcat(counter[0].word, "^(A)Shotgun Shells.......");      
           if(shop[i] == SHOP_AMPUOLE)        
               strcat(counter[0].word, "^(H)Ampuole..............");  
           if(shop[i] == SHOP_HEALTH)        
               strcat(counter[0].word, "^(H)First Aid............");                                        
           if(shop[i] == SHOP_BULLETS)        
               strcat(counter[0].word, "^(A)Machinegun Ammo......");  
           if(shop[i] == SHOP_TRAP_DECOY)
               strcat(counter[0].word, "^(X)Decoy Trap..........."); 
           if(shop[i] == SHOP_TRAP_MINE)
               strcat(counter[0].word, "^(X)Mine Trap............");  
           if(shop[i] == SHOP_BRASS_WATCH)
               strcat(counter[0].word, "^(X)Brass Watch.........."); 
           if(shop[i] == SHOP_SILVER_WATCH)
               strcat(counter[0].word, "^(X)Silver Watch........."); 
           if(shop[i] == SHOP_GOLD_WATCH)
               strcat(counter[0].word, "^(X)Gold Watch...........");                
           if(shop[i] == SHOP_CROWN)        
               strcat(counter[0].word, "^(X)Gold Crown...........");       
           if(shop[i] == SHOP_DIRTY)        
               strcat(counter[0].word, "^(X)Dirty Magazines......"); 
           if(shop[i] == SHOP_BAR)        
               strcat(counter[0].word, "^(X)Emerald..............");    
           if(shop[i] == SHOP_PIPE)        
               strcat(counter[0].word, "^(X)Ruby.................");    
           if(shop[i] == SHOP_PORTRAIT)        
               strcat(counter[0].word, "^(X)Diamond..............");    
           if(shop[i] == SHOP_SOCK)        
               strcat(counter[0].word, "^(F)Smelly Sock..........");  
           if(shop[i] == SHOP_LANTERN)        
               strcat(counter[0].word, "^(F)Lantern..............");
           if(shop[i] == SHOP_TEDDY)        
               strcat(counter[0].word, "^(F)Vodoo Doll...........");  
           if(shop[i] == SHOP_BOOKS)    
               strcat(counter[0].word, "^(F)Children Books......."); 
           if(shop[i] == SHOP_ASHTRAY)      
               strcat(counter[0].word, "^(F)Ashtray.............."); 
           if(shop[i] == SHOP_RUG)        
               strcat(counter[0].word, "^(F)Rug..................");
           if(shop[i] == SHOP_CHAIR)        
               strcat(counter[0].word, "^(F)Chair................");
           if(shop[i] == SHOP_DIARY)        
               strcat(counter[0].word, "^(F)Diary................");
           if(shop[i] == SHOP_GOLFCLUBS)        
               strcat(counter[0].word, "^(F)Golf Clubs...........");
           if(shop[i] == SHOP_PAINTING)        
               strcat(counter[0].word, "^(F)Painting.............");
           if(shop[i] == SHOP_PIGGYBANK)        
               strcat(counter[0].word, "^(F)Piggy Bank...........");
           if(shop[i] == SHOP_BIBLE)        
               strcat(counter[0].word, "^(F)Bible................");               
           if(shop[i] == SHOP_FLAG)        
               strcat(counter[0].word, "^(F)Flag.................");
           if(shop[i] == SHOP_BEDPAN)        
               strcat(counter[0].word, "^(X)Keisers Key..........");                 
           if(shop[i] == SHOP_BOGROLL)        
               strcat(counter[0].word, "^(F)Bog Roll.............");
           if(shop[i] == SHOP_PLATE)        
               strcat(counter[0].word, "^(F)Plate................");  
           if(shop[i] == SHOP_TEACUP)                       
		       strcat(counter[0].word, "^(F)Tea Cup..............");
           if(shop[i] == SHOP_HAMLET)        
               strcat(counter[0].word, "^(F)Hamlet...............");                
           if(shop[i] == SHOP_SNUFFBOX)        
               strcat(counter[0].word, "^(F)Snuff Box............");
           if(shop[i] == SHOP_TOYPLANE)        
               strcat(counter[0].word, "^(F)Toy Plane............");                 
           if(shop[i] == SHOP_POSTER)        
               strcat(counter[0].word, "^(F)Poster...............");
           if(shop[i] == SHOP_FIREVEST)        
               strcat(counter[0].word, "^(X)Fire Vest............");                
           if(shop[i] == SHOP_GASMASK)        
               strcat(counter[0].word, "^(X)Gas Mask.............");  
           if(shop[i] == SHOP_SCOPE)        
               strcat(counter[0].word, "^(U)Farmers scope........"); 
		   if(shop[i] == SHOP_SCOPE2)        
               strcat(counter[0].word, "^(U)Weston scope........."); 
           if(shop[i] == SHOP_SCOPE3)        
               strcat(counter[0].word, "^(U)Webley scope........."); 
           if(shop[i] == SHOP_SCOPE4)        
               strcat(counter[0].word, "^(U)Mauser scope........."); 
           if(shop[i] == SHOP_SCOPE5)        
               strcat(counter[0].word, "^(U)Heinrich scope......."); 
           if(shop[i] == SHOP_SCOPE6)        
               strcat(counter[0].word, "^(U)Super scope..........");  
           if(shop[i] == SHOP_DISCOUNT)    
               strcat(counter[0].word, "^(U)Discount Card........");  
           if(shop[i] == SHOP_DISCOUNT1)        
               strcat(counter[0].word, "^(U)Savers Card..........");  
           if(shop[i] == SHOP_DISCOUNT2)        
               strcat(counter[0].word, "^(U)Pensioners Card......"); 
           if(shop[i] == SHOP_DISCOUNT3)        
               strcat(counter[0].word, "^(U)Supersaver Card......"); 
           if(shop[i] == SHOP_DISCOUNT4)        
               strcat(counter[0].word, "^(U)Loyalty Card........."); 
           if(shop[i] == SHOP_DISCOUNT5)        
               strcat(counter[0].word, "^(U)Royalty Card........."); 
           if(shop[i] == SHOP_FLAK)        
               strcat(counter[0].word, "^(U)Flak Vest............"); 
           if(shop[i] == SHOP_FLAK2)        
               strcat(counter[0].word, "^(U)Flak Shirt..........."); 
           if(shop[i] == SHOP_FLAK3)        
               strcat(counter[0].word, "^(U)Old Flak Jacket......"); 
           if(shop[i] == SHOP_FLAK4)        
               strcat(counter[0].word, "^(U)Flak Jacket.........."); 
           if(shop[i] == SHOP_FLAK5)        
               strcat(counter[0].word, "^(U)New Flak Jacket......"); 
           if(shop[i] == SHOP_FLAK6)        
               strcat(counter[0].word, "^(U)Uber Flak Jacket.....");   
           if(shop[i] == SHOP_BAYONET)        
               strcat(counter[0].word, "^(U)Dagger..............."); 
           if(shop[i] == SHOP_BAYONET2)        
               strcat(counter[0].word, "^(U)Trench Knife........."); 
           if(shop[i] == SHOP_BAYONET3)        
               strcat(counter[0].word, "^(U)Bayonet.............."); 
           if(shop[i] == SHOP_BAYONET4)        
               strcat(counter[0].word, "^(U)Rifle Bayonet........"); 
           if(shop[i] == SHOP_BAYONET5)        
               strcat(counter[0].word, "^(U)Machette............."); 
           if(shop[i] == SHOP_BAYONET6)        
               strcat(counter[0].word, "^(U)Razor Bayonet........");  
           if(shop[i] == SHOP_MEDICAL)        
               strcat(counter[0].word, "^(U)Plasters............."); 
           if(shop[i] == SHOP_MEDICAL2)        
               strcat(counter[0].word, "^(U)Bandages............."); 
           if(shop[i] == SHOP_MEDICAL3)        
               strcat(counter[0].word, "^(U)Ointment............."); 
           if(shop[i] == SHOP_MEDICAL4)        
               strcat(counter[0].word, "^(U)Morphine............."); 
           if(shop[i] == SHOP_MEDICAL5)        
               strcat(counter[0].word, "^(U)Suchures............."); 
           if(shop[i] == SHOP_MEDICAL6)        
               strcat(counter[0].word, "^(U)Double Dosage........"); 
                               
           if(shop[i] == SHOP_BUY_GOLFCLUBS)        
               strcat(counter[0].word, "^(F)Golf Clubs...........");
           if(shop[i] == SHOP_BUY_PIGGYBANK)        
               strcat(counter[0].word, "^(F)Piggy Bank...........");               
           if(shop[i] == SHOP_BUY_FLAG)        
               strcat(counter[0].word, "^(F)Flag.................");
           if(shop[i] == SHOP_BUY_FIREVEST)        
               strcat(counter[0].word, "^(X)Fire Vest............");               
           if(shop[i] == SHOP_BUY_GASMASK)        
               strcat(counter[0].word, "^(X)Gas Mask............."); 
   
           if(shop[i] == SHOP_TINHAT)         
               strcat(counter[0].word, "^(D)Tin Helmet...........");  
           if(shop[i] == SHOP_SHOES)        
               strcat(counter[0].word, "^(D)Boots................");  
           if(shop[i] == SHOP_MEDAL)        
               strcat(counter[0].word, "^(X)Medal................");             
                                                                                                                                                                                                                                           
           if(shop[i] == SHOP_APPLE)        
               strcat(counter[0].word, "^(H)Red Apple............");  
 
                      
           if(shop[i] == SHOP_CARD)
           {  

               if(shop_value[i]== 0)
                  strcat(counter[0].word, "^Card-Lucille..........."); 
               if(shop_value[i]== 1)
                  strcat(counter[0].word, "^Card-Mona.............."); 
               if(shop_value[i]== 2)
                  strcat(counter[0].word, "^Card-Audrie............"); 
               if(shop_value[i]== 3)
                  strcat(counter[0].word, "^Card-Betsy............."); 
                  
               if(shop_value[i]== 4)
                  strcat(counter[0].word, "^Card-Amanda............"); 
               if(shop_value[i]== 5)
                  strcat(counter[0].word, "^Card-Kelly............."); 
               if(shop_value[i]== 6)
                  strcat(counter[0].word, "^Card-Linda............."); 
               if(shop_value[i]== 7)
                  strcat(counter[0].word, "^Card-Lisa.............."); 
                  
               if(shop_value[i]== 8)
                  strcat(counter[0].word, "^Card-Hilda.............");  
               if(shop_value[i]== 9)
                  strcat(counter[0].word, "^Card-Chloe............."); 
               if(shop_value[i]== 10)
                  strcat(counter[0].word, "^Card-Hepburn..........."); 
               if(shop_value[i]== 11)
                  strcat(counter[0].word, "^Card-Fiona............."); 

               if(shop_value[i]== 12)
                  strcat(counter[0].word, "^Card-Celine............"); 
               if(shop_value[i]== 13)
                  strcat(counter[0].word, "^Card-Carla............."); 
               if(shop_value[i]== 14)
                  strcat(counter[0].word, "^Card-Hitomi............"); 
               if(shop_value[i]== 15)
                  strcat(counter[0].word, "^Card-Helena............"); 
                  
               if(shop_value[i]== 16)
                  strcat(counter[0].word, "^Card-Claudia...........");  
               if(shop_value[i]== 17)
                  strcat(counter[0].word, "^Card-Lucy.............."); 
               if(shop_value[i]== 18)
                  strcat(counter[0].word, "^Card-Amy..............."); 
               if(shop_value[i]== 19)
                  strcat(counter[0].word, "^Card-Glenda............"); 
                  
               if(shop_value[i]== 20) 
                  strcat(counter[0].word, "^Card-Laura.............");  
               if(shop_value[i]== 21)
                  strcat(counter[0].word, "^Card-Mandy.............");  
               if(shop_value[i]== 22)
                  strcat(counter[0].word, "^Card-Isabelle.........."); 
               if(shop_value[i]== 23)
                  strcat(counter[0].word, "^Card-Lilly............."); 

               if(shop_value[i]== 24) 
                  strcat(counter[0].word, "^Card-Emma..............");  
               if(shop_value[i]== 25)
                  strcat(counter[0].word, "^Card-Allison..........."); 
               if(shop_value[i]== 26)
                  strcat(counter[0].word, "^Card-Scarlet...........");  
               if(shop_value[i]== 27)
                  strcat(counter[0].word, "^Card-Faith............."); 
                  
               if(shop_value[i]== 28)
                  strcat(counter[0].word, "^Card-Penny.............");  
               if(shop_value[i]== 29)
                  strcat(counter[0].word, "^Card-Hailey............"); 
               if(shop_value[i]== 30)
                  strcat(counter[0].word, "^Card-Layla.............");  
               if(shop_value[i]== 31)
                  strcat(counter[0].word, "^Card-Jasmine..........."); 
                  
               if(shop_value[i]== 32) 
                  strcat(counter[0].word, "^Card-Stella............");  
               if(shop_value[i]== 33)
                  strcat(counter[0].word, "^Card-Bella............."); 
               if(shop_value[i]== 34)
                  strcat(counter[0].word, "^Card-Brooke............"); 
               if(shop_value[i]== 35)
                  strcat(counter[0].word, "^Card-Sarah............."); 
                                                                                                                                                                  
           }                   
                                             
           if(shop[i] == SHOP_NONE && shop_cost[i] != MAXIMUM_REACHED)        
               strcat(counter[0].word, "^");                 
       } 
                                                 
       counter[0].alpha = 1.0f;

       counter[1].x = 0.65f;    
       counter[1].y =  0.55f; 
       counter[1].width = 0.016f;
       counter[1].height = 0.048f; 
             
       sprintf( counter[1].word, "");
                                             
       counter[2].alpha = 1.0f;
       counter[2].x = -0.83f;       
       counter[2].y =  0.03f; 
       counter[2].width = 0.018f; 
       counter[2].height = 0.036f;
        
       counter[2].alpha = 1.0f;  
       
       if(hud[2].alpha == 0.0)      
           sprintf( counter[2].word, "");               
               
                      
       if(shop_sequence != SHOP_TUNE || tune_up_page != -1)              
       for(int i=shop_row;i<shop_row+8;i++)   // Works for Buy & Sell 
	   if(i >= 0) 
       {    
            
           if(shop[i] != SHOP_NONE)  
           {
               sprintf(temp_string.string, "%i", shop_cost[i]);       
               length = strlen(temp_string.string); 
               
               if(tune_up_page != -1)
               {
               if(length == 5)  
                   sprintf(temp_string.string, "^%iG", shop_cost[i]);
               if(length == 4)
                   sprintf(temp_string.string, "^_%iG", shop_cost[i]);
               if(length == 3)
                   sprintf(temp_string.string, "^__%iG", shop_cost[i]);
               if(length == 2)
                   sprintf(temp_string.string, "^___%iG", shop_cost[i]);
               if(length == 1)
                   sprintf(temp_string.string, "^____%iG", shop_cost[i]); 
               }
               else 
               {
               if(length == 5)
                   sprintf(temp_string.string, "^%iG", shop_cost[i]);
               if(length == 4)
                   sprintf(temp_string.string, "^_%iG", shop_cost[i]);
               if(length == 3)
                   sprintf(temp_string.string, "^__%iG", shop_cost[i]);
               if(length == 2)
                   sprintf(temp_string.string, "^___%iG", shop_cost[i]);
               if(length == 1)
                   sprintf(temp_string.string, "^____%iG", shop_cost[i]); 
               }
                              
               strcat(counter[1].word, temp_string.string);
           }                      
           else
           {        
               strcat(counter[1].word, "^");   
           }          

       }  

       counter[1].alpha = 1.0;
       
       if(hud[2].alpha == 0.0) 
       if(tune_up_page == -1 && on_an_item == false) 
           Set_Sprite(20, 0, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display
       
       if(hud[2].alpha == 0.0 && tune_up_page == -1 && on_an_item == false)
       {     
         if(shop_sequence == SHOP_BUY)  
         {           
           sprintf(counter[2].word, "^Hmmm_...What^should_I_buy?");
               Set_Sprite(20, 22, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display
         }
         if(shop_sequence == SHOP_SELL)
         {
           sprintf(counter[2].word, "^Hmmm_...What^should_I_sell?");
               Set_Sprite(20, 23, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display
         }
         if(shop_sequence == SHOP_TUNE)  
         {
           sprintf(counter[2].word, "^Select_a_weapon^or_item_to^upgrade.");
               Set_Sprite(20, 24, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display
         }
       }
        
       if(hud[2].alpha == 0.0)
       if(tune_up_page != -1 )
       {
           if(player_inv[tune_up_page] == INV_HELMET_A 
           || player_inv[tune_up_page] == INV_HELMET_E
           || player_inv[tune_up_page] == INV_BOOT_E
           || player_inv[tune_up_page] == INV_BOOT_E
           )            
               Calculate_Item_Txt(tune_up_page, 2);
           else
               Calculate_Weapon_Text(tune_up_page, 2);
       }

       on_an_item = false;   
  
       if(hud[2].alpha == 0.0)        
       for(int i = 7; i < 15;i++)   
       {      
                     
           index = (i+shop_row) - 7;  // 7  

		   if(index < 0)
			  break;
 
		   if(shop_id < 0) 
			  break;

           Set_Sprite(i, 2, LOOP, ANIM_SPRITE, ANIM_WALKING); // Blank
                       
           if(( mouseX < (sprite[i].w + sprite[i].box_width) )
           &&( mouseX > sprite[i].w)                            
           &&( mouseY < (sprite[i].z + sprite[i].box_height) )
           &&( mouseY > sprite[i].z))   
           {       

               if(shop[index] != SHOP_NONE && hud[2].alpha == 0.0)
               { 

               if(hud[2].alpha == 0.0 && (i-7) < 20)               
               if( array_button_snd[i-7] == false)
               {
                   radio_sfx = true;
                   array_button_snd[i-7] = true;
               } 

               on_an_item = true;
               
               if(shop_sold[shop_id][index] == UNSOLD || shop_sequence != SHOP_BUY)       
                   Set_Sprite(i, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
               else
                   Set_Sprite(i, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
               
               if(shop_cost[index] == MAXIMUM_REACHED && shop_sequence == SHOP_TUNE)
                   Set_Sprite(i, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

               if(shop[index] != SHOP_NONE)                    
                   Set_Display_Picture(shop_sell_id[index], index);
               
               if((mouseleft == true  || DX_SHOOT == true) && (shop_sold[shop_id][index] == UNSOLD || shop_sequence != SHOP_BUY) )  
               {
				   DX_SHOOT = false;
                            
                   cost = shop_cost[index];
                       
                   if(shop_sequence == SHOP_BUY)    
                   if(cost <= temp_gold)
                   { 
                           
                       hud[2].alpha = 1.0; 
                       Set_Sprite(2, 0, LOOP, ANIM_HUD, ANIM_NOT_WALKING);
                       
                       the_item  = i; 
                       the_index = index;
                       
                       message_type = M_PURCHASE;
                     
                   }
                   else
                   {
                       hud[2].alpha = 1.0; 
                       Set_Sprite(2, 8, LOOP, ANIM_HUD, ANIM_NOT_WALKING);
                       message_type = M_NOT_ENOUGH;                      
                   }
                                       
                   if(shop_sequence == SHOP_SELL)     
                   {
                           
                       hud[2].alpha = 1.0; 
                       Set_Sprite(2, 6, LOOP, ANIM_HUD, ANIM_NOT_WALKING);
                       
                       the_item  = i; 
                       the_index = index;
                       
                       message_type = M_SELL;
                        
                   }    
                   
                   if(shop_sequence == SHOP_TUNE && tune_up_page != -1)
                   {     
                     if(cost <= temp_gold)
                     { 
                           
                       hud[2].alpha = 1.0; 
                       Set_Sprite(2, 0, LOOP, ANIM_HUD, ANIM_NOT_WALKING);
                       
                       the_item  = i; 
                       the_index = index; 
                       
                       message_type = M_PURCHASE;
                     
                     }
                     else 
                     {
                       hud[2].alpha = 1.0; 
                       Set_Sprite(2, 8, LOOP, ANIM_HUD, ANIM_NOT_WALKING);
                       message_type = M_NOT_ENOUGH;                      
                     }
                   }
                   
                   if(shop_sequence == SHOP_TUNE && tune_up_page == -1)     
                   {
                       tune_up_page = shop_sell_id[index]; 
                       shop_row=0;   
                   }
                                                                                                         
                   mouseleft = false; 
                    
               } // mouseleft
               } // SHOP_INDEX != SHOP_NONE
      
                
           } // clicked on a row
		   else
		   {
				array_button_snd[i-7] = false;
		   }

      //     else
      //         Set_Sprite(i, 2, LOOP, ANIM_SPRITE, ANIM_WALKING); // Blank           
                                                        
           if(shop_sold[shop_id][index] == SOLD && shop_sequence == SHOP_BUY && shop[index] != SHOP_NONE)  
               Set_Sprite(i, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);  // Red line              
                                             
           if(shop_cost[index] == MAXIMUM_REACHED && shop_sequence == SHOP_TUNE)  
               Set_Sprite(i, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);  // Red line                 
        
       } // end of for loop

        // Yes Button
        if(hud[2].alpha == 1.0)
        {
    
        testX = hud_mouseX - (-camX);                           
        testY = hud_mouseY - (-camY);  
        
        hud[40].alpha = 1.0;
        hud[41].alpha = 1.0; 
        
        // Yes Button                                               
        if(( testX < hud[40].w + hud[40].box_width )   
        &&( testX > hud[40].w)                          
        &&( testY < hud[40].z + hud[40].box_height )
        &&( testY > hud[40].z))  
        {   
            
                if(hud[40].anim == HUD_YES_ANIM)
                    radio_sfx = true;
                                        
                Set_Sprite(40, HUD_YES_ANIM+1, PLAY, ANIM_HUD, ANIM_NOT_WALKING);
                
                if(mouseleft == true || DX_SHOOT == true)
                {     
					DX_SHOOT = false;
                    click_sfx = true;
                    hud[2].alpha = 0.0; 
                    hud[40].alpha = 0.0;   
                    hud[41].alpha = 0.0;
                //    click_sfx = true;
                    if(message_type == M_PURCHASE)
                    { 
						if(the_item >= 0)
                        sprite[the_item].grab_switch = false;
                        
                        if(shop_sequence == SHOP_BUY)
                            success = false;
                        else
                            success = true;
                            
					    if(the_index >= 0)
						{

                        Tune_Gun(the_index);
                         
                        item_value=0; 
                        
                        // Rifles //                                                                                                                                                                                                                
                        if(shop[the_index] == SHOP_FARMERS_RIFLE)  
                        {  
                             success = Calculate_Item(FARMERS_RIFLE, INV_RIFLE, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(24, INV_AMMO, -1, 24, -1, -1);
                        }                
                        if(shop[the_index] == SHOP_HUNTER_RIFLE)  
                        {  
                             success = Calculate_Item(HUNTER_RIFLE, INV_RIFLE, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(24, INV_AMMO, -1, 24, -1, -1);
                        }                
                        if(shop[the_index] == SHOP_ENFIELD_RIFLE)  
                        {  
                             success = Calculate_Item(ENFIELD_RIFLE, INV_RIFLE, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(24, INV_AMMO, -1, 24, -1, -1);
                        }                
                        if(shop[the_index] == SHOP_ENFIELDK_RIFLE)  
                        {  
                             success = Calculate_Item(ENFIELDK_RIFLE, INV_RIFLE, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(24, INV_AMMO, -1, 24, -1, -1);
                        }                
                        if(shop[the_index] == SHOP_MAUSER_RIFLE)  
                        {  
                             success = Calculate_Item(MAUSER_RIFLE, INV_RIFLE, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(24, INV_AMMO, -1, 24, -1, -1);
                        }    
                        if(shop[the_index] == SHOP_MAUSERK_RIFLE)  
                        {  
                             success = Calculate_Item(MAUSERK_RIFLE, INV_RIFLE, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(24, INV_AMMO, -1, 24, -1, -1);
                        }                
                        if(shop[the_index] == SHOP_CARBINE_RIFLE)  
                        {  
                             success = Calculate_Item(CARBINE_RIFLE, INV_RIFLE, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(24, INV_AMMO, -1, 24, -1, -1);
                        }                
                        if(shop[the_index] == SHOP_CARBINEK_RIFLE)  
                        {  
                             success = Calculate_Item(CARBINEK_RIFLE, INV_RIFLE, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(24, INV_AMMO, -1, 24, -1, -1);
                        }                
                        if(shop[the_index] == SHOP_GEWEHR_RIFLE)  
                        {  
                             success = Calculate_Item(GEWEHR_RIFLE, INV_RIFLE, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(24, INV_AMMO, -1, 24, -1, -1);
                        }  
                        if(shop[the_index] == SHOP_GEWEHRK_RIFLE)  
                        {  
                             success = Calculate_Item(GEWEHRK_RIFLE, INV_RIFLE, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(24, INV_AMMO, -1, 24, -1, -1);
                        }                
                        if(shop[the_index] == SHOP_HEINRICH_RIFLE)  
                        {  
                             success = Calculate_Item(HEINRICH_RIFLE, INV_RIFLE, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(24, INV_AMMO, -1, 24, -1, -1);
                        }                
                        if(shop[the_index] == SHOP_HEINRICHK_RIFLE)  
                        {  
                             success = Calculate_Item(HEINRICHK_RIFLE, INV_RIFLE, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(24, INV_AMMO, -1, 24, -1, -1);
                        }                
                        if(shop[the_index] == SHOP_WINCHESTER_RIFLE)   
                        {  
                             success = Calculate_Item(WINCHESTER_RIFLE, INV_RIFLE, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(24, INV_AMMO, -1, 24, -1, -1);
                        }              

                        // Shotguns //                                                           
                        if(shop[the_index] == SHOP_FARMERS_SHOTGUN) 
                        {  

                                 item_value = 0;   
                                                           
                             success = Calculate_Item(0, INV_SHOTGUN, -1, item_value, -1, -1);
                             Calculate_Item(24, INV_SHELLS, -1, 24, -1, -1);
                        }     
                        if(shop[the_index] == SHOP_ARMY_SHOTGUN) 
                        {  

                                 item_value = 0;   
                                                           
                             success = Calculate_Item(1, INV_SHOTGUN, -1, item_value, -1, -1);
                             Calculate_Item(24, INV_SHELLS, -1, 24, -1, -1);
                        }                             
                        // Machineguns //
                        if(shop[the_index] == SHOP_THOMPSOM_MACHINE) 
                        {  
                             success = Calculate_Item(0, INV_MACHINE, -1, item_value, -1, -1);
                             Calculate_Item(150, INV_BULLETS, -1, 150, -1, -1);
                        }   


                        // Pistols //                         
                        if(shop[the_index] == SHOP_TRAINING_PISTOL) 
                        {  
                             success = Calculate_Item(TRAINING_PISTOL, INV_PISTOL, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(50, INV_HGUN_AMMO, -1, 24, -1, -1);
                        }     
                        if(shop[the_index] == SHOP_WEBLEY_PISTOL) 
                        {  
                             success = Calculate_Item(WEBLEY_PISTOL, INV_PISTOL, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(50, INV_HGUN_AMMO, -1, 24, -1, -1);
                        }  
                        if(shop[the_index] == SHOP_LUGER_PISTOL) 
                        {  
                             success = Calculate_Item(LUGER_PISTOL, INV_PISTOL, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(50, INV_HGUN_AMMO, -1, 24, -1, -1);
                        }  
                        if(shop[the_index] == SHOP_LUGERK_PISTOL) 
                        {  
                             success = Calculate_Item(LUGERK_PISTOL, INV_PISTOL, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(50, INV_HGUN_AMMO, -1, 24, -1, -1);
                        }  
                        if(shop[the_index] == SHOP_WESTON_PISTOL) 
                        {  
                             success = Calculate_Item(WESTON_PISTOL, INV_PISTOL, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(50, INV_HGUN_AMMO, -1, 24, -1, -1);
                        }  
                        if(shop[the_index] == SHOP_WESTONK_PISTOL) 
                        {  
                             success = Calculate_Item(WESTONK_PISTOL, INV_PISTOL, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(50, INV_HGUN_AMMO, -1, 24, -1, -1);
                        }  
                        if(shop[the_index] == SHOP_MAUSER_PISTOL) 
                        {  
                             success = Calculate_Item(MAUSER_PISTOL, INV_PISTOL, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(50, INV_HGUN_AMMO, -1, 24, -1, -1);
                        }  
                        if(shop[the_index] == SHOP_MAUSERK_PISTOL) 
                        {  
                             success = Calculate_Item(MAUSERK_PISTOL, INV_PISTOL, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(50, INV_HGUN_AMMO, -1, 24, -1, -1);
                        }  
                        if(shop[the_index] == SHOP_COLT_PISTOL) 
                        {  
                             success = Calculate_Item(COLT_PISTOL, INV_PISTOL, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(50, INV_HGUN_AMMO, -1, 24, -1, -1);
                        }  
                        if(shop[the_index] == SHOP_COLTK_PISTOL) 
                        {  
                             success = Calculate_Item(COLTK_PISTOL, INV_PISTOL, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(50, INV_HGUN_AMMO, -1, 24, -1, -1);
                        }  
                        if(shop[the_index] == SHOP_SAVAGE_PISTOL) 
                        {  
                             success = Calculate_Item(SAVAGE_PISTOL, INV_PISTOL, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(50, INV_HGUN_AMMO, -1, 24, -1, -1);
                        }  
                        if(shop[the_index] == SHOP_SAVAGEK_PISTOL) 
                        {  
                             success = Calculate_Item(SAVAGEK_PISTOL, INV_PISTOL, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(50, INV_HGUN_AMMO, -1, 24, -1, -1);
                        }  
                        if(shop[the_index] == SHOP_NAVYCOLT_PISTOL) 
                        {  
                             success = Calculate_Item(NAVYCOLT_PISTOL, INV_PISTOL, -1, shop_value[the_index], -1, shop_value1[the_index]);
                             Calculate_Item(50, INV_HGUN_AMMO, -1, 24, -1, -1);
                        }  
						 
                        // Others //   
                        if(shop[the_index] == SHOP_BLACK_GRENADE) 
                             success = Calculate_Item(BLACK_GRENADE, INV_GRENADE, -1, 1, SHOP_AMOUNT_BLACK_GRENADE, -1);                               
                        // Others //  
                        if(shop[the_index] == SHOP_GREEN_GRENADE) 
                             success = Calculate_Item(GREEN_GRENADE, INV_GRENADE, -1, 1, SHOP_AMOUNT_GREEN_GRENADE, -1); 
                        // Others //  
                        if(shop[the_index] == SHOP_MOLOTOV_GRENADE) 
                             success = Calculate_Item(MOLOTOV_GRENADE, INV_GRENADE, -1, 1, SHOP_AMOUNT_MOLOTOV, -1); 

                        // Others //  
                        if(shop[the_index] == SHOP_SCOPE) 
						{
                             st_passive_scope=1;  
							 success = true;
						} 
						// Others //  
                        if(shop[the_index] == SHOP_SCOPE2) 
						{
                             st_passive_scope=2;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_SCOPE3) 
						{
                             st_passive_scope=3;   
							 success = true;
						} 
                        // Others //  
                        if(shop[the_index] == SHOP_SCOPE4) 
						{
                             st_passive_scope=4;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_SCOPE5) 
						{
                             st_passive_scope=5;   
							 success = true;
						} 
                        // Others //  
                        if(shop[the_index] == SHOP_SCOPE6) 
						{
                             st_passive_scope=6;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_DISCOUNT) 
						{
                             st_passive_discount=1;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_DISCOUNT1) 
						{
                             st_passive_discount=2;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_DISCOUNT2) 
						{
                             st_passive_discount=3;   
							 success = true;
						} 
                        // Others //  
                        if(shop[the_index] == SHOP_DISCOUNT3) 
						{
                             st_passive_discount=4;   
							 success = true;
						} 
                        // Others //  
                        if(shop[the_index] == SHOP_DISCOUNT4) 
						{
                             st_passive_discount=5;   
							 success = true;
						} 
                        // Others //  
                        if(shop[the_index] == SHOP_DISCOUNT5) 
						{
                             st_passive_discount=6;   
							 success = true;
						} 
                        // Others //  
                        if(shop[the_index] == SHOP_FLAK) 
						{
                             st_passive_flak=1;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_FLAK2) 
						{
                             st_passive_flak=2;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_FLAK3) 
						{
                             st_passive_flak=3;   
							 success = true;
						} 
                        // Others //  
                        if(shop[the_index] == SHOP_FLAK4) 
						{
                             st_passive_flak=4;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_FLAK5) 
						{
                             st_passive_flak=5;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_FLAK6) 
						{
                             st_passive_flak=6;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_BAYONET) 
						{
                             st_passive_knife=1;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_BAYONET2) 
						{
                             st_passive_knife=2;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_BAYONET3) 
						{
                             st_passive_knife=3;   
							 success = true;
						} 
                        // Others //  
                        if(shop[the_index] == SHOP_BAYONET4) 
						{
                             st_passive_knife=4;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_BAYONET5) 
						{
                             st_passive_knife=5;   
							 success = true;
						}
                        // Others //   
                        if(shop[the_index] == SHOP_BAYONET6) 
						{
                             st_passive_knife=6;   
							 success = true;
						}

                        // Others //  
                        if(shop[the_index] == SHOP_MEDICAL) 
						{
                             st_passive_medikit=1;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_MEDICAL2) 
						{
                             st_passive_medikit=2;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_MEDICAL3) 
						{
                             st_passive_medikit=3;   
							 success = true;
						} 
                        // Others //  
                        if(shop[the_index] == SHOP_MEDICAL4) 
						{
                             st_passive_medikit=4;   
							 success = true;
						}
                        // Others //  
                        if(shop[the_index] == SHOP_MEDICAL5) 
						{
                             st_passive_medikit=5;   
							 success = true;
						} 
                        // Others //  
                        if(shop[the_index] == SHOP_MEDICAL6) 
						{
                             st_passive_medikit=6;   
							 success = true;
						}
                        
                        if(shop[the_index] == SHOP_AMPUOLE)  
                             success = Calculate_Item(0, INV_AMPUOLE, -1, 0, 1, -1);  
                         
                        if(shop[the_index] == SHOP_HEALTH)   
                             success = Calculate_Item(0, INV_HEALTH, -1, 0, 1, -1);  
                           
                        if(shop[the_index] == SHOP_MEDAL)        
                             success = Calculate_Item(shop_value[the_index], INV_MEDAL, -1, shop_value1[the_index], -1, -1); 
                         
                        if(shop[the_index] == SHOP_TINHAT)   
                             success = Calculate_Item(shop_value[the_index], INV_HELMET, -1, 0, 0, -1); 
                         
                        if(shop[the_index] == SHOP_SHOES) 
                             success = Calculate_Item(shop_value[the_index], INV_BOOT, -1, 0, 0, -1); 
                                                                                      
                        if(shop[the_index] == SHOP_HGUN_AMMO)
                             success = Calculate_Item(SHOP_AMOUNT_HGUN_AMMO, INV_HGUN_AMMO, -1, 0, 1, -1);  
                        
                        if(shop[the_index] == SHOP_BULLETS) 
                             success = Calculate_Item(SHOP_AMOUNT_BULLETS, INV_BULLETS, -1, 0, 1, -1);  
                        
                        if(shop[the_index] == SHOP_TRAP_DECOY)
                             success = Calculate_Item(TRAP_TYPE_DECOY, INV_TRAP, -1, 0, 1, DECOY_HEALTH);  
                        
                        if(shop[the_index] == SHOP_TRAP_MINE)
                             success = Calculate_Item(TRAP_TYPE_MINE, INV_TRAP, -1, 0, 1, DECOY_HEALTH);   

                        if(shop[the_index] == SHOP_SHELLS)
                             success = Calculate_Item(SHOP_AMOUNT_SHELLS, INV_SHELLS, -1, 0, 1, -1);  
                        
                        if(shop[the_index] == SHOP_AMMO) 
                             success = Calculate_Item(SHOP_AMOUNT_AMMO, INV_AMMO, -1, 0, 1, -1);  
                        
                        if(shop[the_index] == SHOP_SILVER_WATCH)  
                             success = Calculate_Item(1, INV_WATCH, -1, 0, 1, -1);  
                        
                        if(shop[the_index] == SHOP_BUY_GOLFCLUBS)  
                        {
                             success = Calculate_Item(16, INV_LETTERS, -1, 0, 1, -1);
                             
                             if(success == true)  
                                 purchased = PURCHASE_GOLFCLUBS;   
                        } 
                        
                        if(shop[the_index] == SHOP_BUY_PIGGYBANK)  
                        {
                             success = Calculate_Item(18, INV_LETTERS, -1, 0, 1, -1);  
                             
                             if(success == true)
                                 purchased = PURCHASE_PIGGYBANK;
                                 
                        } 
                         
                        if(shop[the_index] == SHOP_BUY_FLAG)  
                        {
                             success = Calculate_Item(20, INV_LETTERS, -1, 0, 1, -1);  
                             
                             if(success == true)
                                 purchased = PURCHASE_FLAG;
                                  
                        } 
                         
                        if(shop[the_index] == SHOP_BUY_FIREVEST)  
                        {
                             success = Calculate_Item(29, INV_LETTERS, -1, 0, 1, -1);  
                             
                             if(success == true)
                                 purchased = PURCHASE_FIREVEST;
                                  
                        }                        
                         
                        if(shop[the_index] == SHOP_BUY_GASMASK)  
                        {
                             success = Calculate_Item(30, INV_LETTERS, -1, 0, 1, -1);  
                             
                             if(success == true)
                                 purchased = PURCHASE_GASMASK;
                                  
                        }
                                                                                                                                                                                                                                                                                                                                                                                                                                  
                        if(success == true)  
                        { 
 
							// Display manual...
                            if(shop[the_index] == SHOP_TRAP_DECOY)
							    display_trap_manual=true;
                            if(shop[the_index] == SHOP_TRAP_MINE)
							    display_trap_manual=true; 
                                                                                                                                        
                            if(shop_sequence == SHOP_BUY)        
							if(shop[the_index] != SHOP_AMMO)
							if(shop[the_index] != SHOP_HGUN_AMMO)
							if(shop[the_index] != SHOP_BLACK_GRENADE)
							if(shop[the_index] != SHOP_GREEN_GRENADE)
							if(shop[the_index] != SHOP_MOLOTOV_GRENADE)
                                shop_sold[shop_id][the_index] = SOLD;
                                
                            cash_sfx = true;  
                                                   
                            bump_timer = (int)TimerGetTime() + 200;

                            if(shop_sequence == SHOP_BUY)
                            {  
                                if(current_gold != -1)
                                {             
                                    player_inv_value[current_gold] -= shop_cost[the_index]; 
                                }
                            }
                            else
                            {  
                                if(current_gold != -1)
                                {             
                                    player_inv_value[current_gold] -= shop_cost[the_index]; 
                                }
                            }
                        } 
                        else 
                        {
                            message_type = M_INVFULL;   
                            Set_Sprite(2, 7, LOOP, ANIM_HUD, ANIM_NOT_WALKING);
                            hud[2].alpha = 1.0; 
                            hud[40].alpha = 1.0;   
                            hud[41].alpha = 1.0;                            
                        }
						
						} // the_index >= 0
                         
                    }
                    
                    if(message_type == M_SELL)
                    {   

     				   if(the_index >= 0)
     				   if(shop_sell_id[the_index] >= 0)
					   {
         
                       
                       if(current_helmet == shop_sell_id[the_index])
                           current_helmet = -1;  
                       
                       if(current_medal == shop_sell_id[the_index])
                           current_medal = -1;    
                       
                       if(current_trap == shop_sell_id[the_index])
                           current_trap = -1;  
                       
                       if(current_boot == shop_sell_id[the_index])
                           current_boot = -1; 
                       
                       if(current_special == shop_sell_id[the_index])
                           current_special = -1;       

                       if(last_current_rifle == shop_sell_id[the_index])
                           last_current_rifle = -1;  

                       if(last_current_pistol == shop_sell_id[the_index])
                           last_current_pistol = -1;  
                                                                             
                       if(player_inv[shop_sell_id[the_index]] == INV_RIFLE_A
                       || player_inv[shop_sell_id[the_index]] == INV_SHOTGUN_A
                       || player_inv[shop_sell_id[the_index]] == INV_MACHINE_A
                       )
                       {
                                                           
                               
                           player_inv[shop_sell_id[the_index]+1] = INV_NONE;
               
                           player_inv_value[shop_sell_id[the_index]+1]  = 0;
                           player_inv_value1[shop_sell_id[the_index]+1] = 0;
                           player_inv_value2[shop_sell_id[the_index]+1] = 0;  
                       }
                                                           
                       player_inv[shop_sell_id[the_index]] = INV_NONE;
               
                       player_inv_value[shop_sell_id[the_index]]  = 0;
                       player_inv_value1[shop_sell_id[the_index]] = 0;
                       player_inv_value2[shop_sell_id[the_index]] = 0;                 
                        
                       cash_sfx = true;   
                         
                       Calculate_Item(shop_cost[the_index], INV_GOLD, -1, 0, -1, -1);                                          
                       
                       bump_timer = (int)TimerGetTime() + 200;
                           
                    } // the_index >= 0
   
					} 
                                             
                    mouseleft = false;
                    
                }
                            
        }
        else
            Set_Sprite(40, HUD_YES_ANIM, PLAY, ANIM_HUD, ANIM_NOT_WALKING);
            
        // No Button                                               
        if(( testX < hud[41].w + hud[41].box_width )   
        &&( testX > hud[41].w)                          
        &&( testY < hud[41].z + hud[41].box_height )
        &&( testY > hud[41].z))  
        {   
            
            if(hud[41].anim == HUD_NO_ANIM)
                radio_sfx = true;
                        
            Set_Sprite(41, HUD_NO_ANIM+1, PLAY, ANIM_HUD, ANIM_NOT_WALKING);
            
            if(mouseleft == true || DX_SHOOT == true)
            {    
				DX_SHOOT = false;
                hud[2].alpha = 0.0;
                hud[40].alpha = 0.0;
                hud[41].alpha = 0.0;
                click_sfx = true;
                mouseleft = false;
            }
            
        }
        else
            Set_Sprite(41, HUD_NO_ANIM, PLAY, ANIM_HUD, ANIM_NOT_WALKING);
                
        }   // end of hud[2] 
                 
                            
   }    // episode 1 - scene 7
 
}
void Calculate_Shop(int id)  
{ 
    int shop_stage = 0;
	int rnd=0;
	int rnd1=0;
	int rank=0;
	int rifle_rank=1;
    int the_weapon = INV_GRENADE;

    shop_count = 0;
     
    memset(shop, SHOP_NONE, sizeof(shop)); 
     
    memset(shop_s, SHOP_NONE, sizeof(shop_s)); 
    
    // WESTON_PISTOL      

    shop_stage = 0; 

	memset(shop_value, 0, sizeof(shop_value));
	memset(shop_value1, 0, sizeof(shop_value1));
	
	if(shop_items_set_timer == 0) 
	{
		shop_items_set[0] = false;
		shop_items_set[1] = false; 
		shop_items_set[2] = false;
	
		memset( shop_sold, UNSOLD, sizeof(shop_sold)); 
	}
 	
	if(shop_id >= 0)
	if(shop_items_set[shop_id] == true)        
	{ 
		for(int i=0;i<32;i++)    
		{
			shop[i] = stored_shop[shop_id][i];
			shop_s[i] = stored_shop_s[shop_id][i];
			shop_value[i] = stored_shop_value[shop_id][i];
			shop_value1[i] = stored_shop_value1[shop_id][i];
		}
		shop_count = stored_shop_count[shop_id]; 
	} 

    if(shop_id == 0)          
        if(shop_items_set[shop_id] == false)     
        {      
  
     		shop_items_set[shop_id] = true; 
 			shop_items_set_timer = 1;  
 
			if(player_rank > 1)  
			{
         	   shop[shop_count] = SHOP_MEDAL;   
         	   shop_s[shop_count] = SHOP_SPECIAL;  
			   shop_value[shop_count] = ((player_rank-1)*4) + 1 + rand()%4;
			   shop_value1[shop_count] = rand()%10; 	

               if(shop_value1[shop_count] == 7)
			       shop_value1[shop_count] = 0;	 
				
				
         	   shop_count++;  
			}
			if(player_rank > 3)  
			{	 
          	   shop[shop_count] = SHOP_MEDAL; 
         	   shop_s[shop_count] = SHOP_SPECIAL;  
			   shop_value[shop_count] = ((player_rank-1)*4) + 1 + rand()%4;
			   shop_value1[shop_count] = rand()%10; 

               if(shop_value1[shop_count] == 7)
			       shop_value1[shop_count] = 0;	 

         	   shop_count++; 
			}

            shop[shop_count] = SHOP_TINHAT;  
            shop_s[shop_count] = SHOP_SPECIAL;
			shop_value[shop_count] = (1+((player_rank-1)*3)) + rand()%(player_rank*3);
            shop_count++; 
                 
            shop[shop_count] = SHOP_SHOES; 
            shop_s[shop_count] = SHOP_SPECIAL;
			shop_value[shop_count] = (1+((player_rank-1)*3)) + rand()%(player_rank*3);
            shop_count++;

            shop[shop_count] = SHOP_AMPUOLE; 
            shop_s[shop_count] = SHOP_SPECIAL;
            shop_count++;  
   
	        shop[shop_count] = SHOP_HEALTH;
	        shop_s[shop_count] = SHOP_SPECIAL;
	        shop_count++;   
 
 			for(int i=0;i<32;i++)  
			{ 
				stored_shop[shop_id][i] = shop[i];
				stored_shop_s[shop_id][i] = shop_s[i];
				stored_shop_value[shop_id][i] = shop_value[i];
				stored_shop_value1[shop_id][i] = shop_value1[i];
			} 

			stored_shop_count[shop_id] = shop_count;
                       
        }

    if(shop_id == 1)        
        if(shop_items_set[shop_id] == false)   
        {     
  
     		shop_items_set[shop_id] = true;
 			shop_items_set_timer = 1;  

				if(player_rank > 12 )  
            		shop[shop_count] = SHOP_WINCHESTER_RIFLE;
				if(player_rank == 12 )  
            		shop[shop_count] = SHOP_HEINRICHK_RIFLE;
				if(player_rank == 11  )
            		shop[shop_count] = SHOP_HEINRICHK_RIFLE;
				if(player_rank == 10  )
            		shop[shop_count] = SHOP_HEINRICH_RIFLE;
				if(player_rank == 9  )
            		shop[shop_count] = SHOP_GEWEHRK_RIFLE;

				if(player_rank == 8  )
            		shop[shop_count] = SHOP_GEWEHR_RIFLE;
				if(player_rank == 7  )
            		shop[shop_count] = SHOP_CARBINEK_RIFLE;
				if(player_rank == 6  )
            		shop[shop_count] = SHOP_CARBINE_RIFLE;
				if(player_rank == 5  )
            		shop[shop_count] = SHOP_MAUSERK_RIFLE;

				if(player_rank == 4 )
            		shop[shop_count] = SHOP_MAUSER_RIFLE;
				if(player_rank == 3 )
            		shop[shop_count] = SHOP_ENFIELDK_RIFLE;
				if(player_rank == 2 )
            		shop[shop_count] = SHOP_ENFIELD_RIFLE;
				if(player_rank == 1  )
            		shop[shop_count] = SHOP_HUNTER_RIFLE;

           		shop_s[shop_count] = SHOP_SPECIAL;
           		shop_count++;  

				if(player_rank > 12 )    
            		shop[shop_count] = SHOP_NAVYCOLT_PISTOL;
				if(player_rank == 12 )   
            		shop[shop_count] = SHOP_SAVAGEK_PISTOL;
				if(player_rank == 11  )
            		shop[shop_count] = SHOP_SAVAGEK_PISTOL;
				if(player_rank == 10  ) 
            		shop[shop_count] = SHOP_SAVAGE_PISTOL;
				if(player_rank == 9  )
            		shop[shop_count] = SHOP_COLTK_PISTOL;

				if(player_rank == 8  )
            		shop[shop_count] = SHOP_COLT_PISTOL;
				if(player_rank == 7  )
            		shop[shop_count] = SHOP_MAUSERK_PISTOL;
				if(player_rank == 6  )
            		shop[shop_count] = SHOP_MAUSER_PISTOL;
				if(player_rank == 5  )
            		shop[shop_count] = SHOP_WESTONK_PISTOL;

				if(player_rank == 4  )
            		shop[shop_count] = SHOP_WESTON_PISTOL;
				if(player_rank == 3 )
            		shop[shop_count] = SHOP_LUGERK_PISTOL;
				if(player_rank == 2  )
            		shop[shop_count] = SHOP_LUGER_PISTOL;
				if(player_rank == 1  )
            		shop[shop_count] = SHOP_WEBLEY_PISTOL;

           		shop_s[shop_count] = SHOP_SPECIAL;
           		shop_count++; 

		//	if(INFINITE_PISTOL == 0)
		//	for(int i=0;i<2;i++) 
		//	{
		//		rnd = rand()%2;  


		//	if(rnd == 0)
		//	{              
            	shop[shop_count] = SHOP_AMMO; 
            	shop_s[shop_count] = SHOP_SPECIAL;
				shop_value[shop_count] = SHOP_AMOUNT_AMMO;
            	shop_count++;      
         //   }
		//	if(rnd == 1)   
		//	{  
            	shop[shop_count] = SHOP_HGUN_AMMO; 
            	shop_s[shop_count] = SHOP_SPECIAL;
				shop_value[shop_count] = SHOP_AMOUNT_HGUN_AMMO;
            	shop_count++;   
		//	}

		//	} 

			#if INFINITE_PISTOL == 1

            	shop[shop_count] = SHOP_AMMO; 
            	shop_s[shop_count] = SHOP_SPECIAL;
				shop_value[shop_count] = 20;
            	shop_count++;    
				 
            	shop[shop_count] = SHOP_AMMO; 
            	shop_s[shop_count] = SHOP_SPECIAL;
				shop_value[shop_count] = 20;
            	shop_count++;   

			#endif

			if(current_act == 1)
			{
				if(player_rank > 1) 
				{
		            shop[shop_count] = SHOP_GREEN_GRENADE; 
		            shop_s[shop_count] = SHOP_SPECIAL;
	    	        shop_count++;  
				}
				
				if(player_rank > 3) 
				{
		            shop[shop_count] = SHOP_BLACK_GRENADE; 
		            shop_s[shop_count] = SHOP_SPECIAL;
		            shop_count++;  
				}
			} 

			if(current_act != 1)   
			{

	            shop[shop_count] = SHOP_BLACK_GRENADE; 
	            shop_s[shop_count] = SHOP_SPECIAL;
	            shop_count++;  

	            shop[shop_count] = SHOP_MOLOTOV_GRENADE; 
	            shop_s[shop_count] = SHOP_SPECIAL;
    	        shop_count++;  
			}

 			for(int i=0;i<32;i++)  
			{
				stored_shop[shop_id][i] = shop[i];
				stored_shop_s[shop_id][i] = shop_s[i];
				stored_shop_value[shop_id][i] = shop_value[i];
				stored_shop_value1[shop_id][i] = shop_value1[i];
			} 

			stored_shop_count[shop_id] = shop_count;
                       
        }


    if(shop_id == 2)          
        if(shop_items_set[shop_id] == false)    
        {      
  
     		shop_items_set[shop_id] = true;
 			shop_items_set_timer = 1;  

            shop[shop_count] = SHOP_SILVER_WATCH;     
            shop_s[shop_count] = SHOP_SPECIAL;   
			shop_value[shop_count] = 1;
			shop_value1[shop_count] = 1;  	 
            shop_count++;    
			 
			if(current_act != 1 || main_mission[MISSION_SPY] == FINISHED)
			{
	            shop[shop_count] = SHOP_BUY_FIREVEST;    
	            shop_s[shop_count] = SHOP_SPECIAL;   
				shop_value[shop_count] = 1;
				shop_value1[shop_count] = 1;  	
	            shop_count++;  
			}    
 			 
			if(st_passive_knife == 0)
	            shop[shop_count] = SHOP_BAYONET;    
			if(st_passive_knife == 1)
	            shop[shop_count] = SHOP_BAYONET2;              
			if(st_passive_knife == 2)
	            shop[shop_count] = SHOP_BAYONET3;    
			if(st_passive_knife == 3)
	            shop[shop_count] = SHOP_BAYONET4;      
			if(st_passive_knife == 4)
	            shop[shop_count] = SHOP_BAYONET5;   
			if(st_passive_knife == 5)
	            shop[shop_count] = SHOP_BAYONET6;  

			if(st_passive_knife < 6) 
			{
	            shop_s[shop_count] = SHOP_SPECIAL;   
				shop_value[shop_count] = 1; 
				shop_value1[shop_count] = 1; 	
	            shop_count++;  
			}
 
			if(player_rank >= 1) 
			{			 
			if(st_passive_medikit == 0)
	            shop[shop_count] = SHOP_MEDICAL;    
			if(st_passive_medikit == 1)
	            shop[shop_count] = SHOP_MEDICAL2;    
			if(st_passive_medikit == 2)
	            shop[shop_count] = SHOP_MEDICAL3;    
			if(st_passive_medikit == 3)
	            shop[shop_count] = SHOP_MEDICAL4;      
			if(st_passive_medikit == 4)
	            shop[shop_count] = SHOP_MEDICAL5;   
			if(st_passive_medikit == 5)
	            shop[shop_count] = SHOP_MEDICAL6;  

			if(st_passive_medikit < 6) 
			{
	            shop_s[shop_count] = SHOP_SPECIAL;   
				shop_value[shop_count] = 1; 
				shop_value1[shop_count] = 1; 	
	            shop_count++;  
			}
			}
 
/*			if(player_rank >= 1) 
			{
						 
			if(st_passive_scope == 0)
	            shop[shop_count] = SHOP_SCOPE;    
			if(st_passive_scope == 1)
	            shop[shop_count] = SHOP_SCOPE2;    
			if(st_passive_scope == 2)
	            shop[shop_count] = SHOP_SCOPE3;     
			if(st_passive_scope == 3)
	            shop[shop_count] = SHOP_SCOPE4;      
			if(st_passive_scope == 4)
	            shop[shop_count] = SHOP_SCOPE5;   
			if(st_passive_scope == 5) 
	            shop[shop_count] = SHOP_SCOPE6;  

			if(st_passive_scope < 6) 
			{
	            shop_s[shop_count] = SHOP_SPECIAL;   
				shop_value[shop_count] = 1; 
				shop_value1[shop_count] = 1; 	
	            shop_count++;  
			}

			}*/

			if(player_rank > 3) 
			{
 
			if(st_passive_flak == 0)
	            shop[shop_count] = SHOP_FLAK;    
			if(st_passive_flak == 1)
	            shop[shop_count] = SHOP_FLAK2;    
			if(st_passive_flak == 2)
	            shop[shop_count] = SHOP_FLAK3;    
			if(st_passive_flak == 3)
	            shop[shop_count] = SHOP_FLAK4;      
			if(st_passive_flak == 4)
	            shop[shop_count] = SHOP_FLAK5;   
			if(st_passive_flak == 5)
	            shop[shop_count] = SHOP_FLAK6;  
			
			if(st_passive_flak < 6)
			{
	            shop_s[shop_count] = SHOP_SPECIAL;   
				shop_value[shop_count] = 1; 
				shop_value1[shop_count] = 1; 	
	            shop_count++;  
			}
 
			if(st_passive_discount == 0)
	            shop[shop_count] = SHOP_DISCOUNT;    
			if(st_passive_discount == 1)
	            shop[shop_count] = SHOP_DISCOUNT1;   
			if(st_passive_discount == 2)
	            shop[shop_count] = SHOP_DISCOUNT2;   
			if(st_passive_discount == 3)
	            shop[shop_count] = SHOP_DISCOUNT3;   
			if(st_passive_discount == 4)
	            shop[shop_count] = SHOP_DISCOUNT4;   
			if(st_passive_discount == 5)
	            shop[shop_count] = SHOP_DISCOUNT5;  
	
			if(st_passive_discount < 6 )  
			{
	            shop_s[shop_count] = SHOP_SPECIAL;   
				shop_value[shop_count] = 1; 
				shop_value1[shop_count] = 1; 	
	            shop_count++;  
			}

			}

 			for(int i=0;i<32;i++)  
			{
				stored_shop[shop_id][i] = shop[i];
				stored_shop_s[shop_id][i] = shop_s[i];
				stored_shop_value[shop_id][i] = shop_value[i];
				stored_shop_value1[shop_id][i] = shop_value1[i];
			} 

			stored_shop_count[shop_id] = shop_count;

		}
		
    if(shop_id == 3)          
        if(shop_items_set[shop_id] == false)    
        {      

            shop[shop_count] = SHOP_TRAP_DECOY;     
            shop_s[shop_count] = SHOP_SPECIAL;   
			shop_value[shop_count] = 1; 
			shop_value1[shop_count] = 1;  	
            shop_count++;  

            shop[shop_count] = SHOP_TRAP_DECOY;      
            shop_s[shop_count] = SHOP_SPECIAL;   
			shop_value[shop_count] = 1;  
			shop_value1[shop_count] = 1;  	
            shop_count++;  

            shop[shop_count] = SHOP_TRAP_MINE;     
            shop_s[shop_count] = SHOP_SPECIAL;   
			shop_value[shop_count] = 1; 
			shop_value1[shop_count] = 1;  	
            shop_count++;  

            shop[shop_count] = SHOP_TRAP_MINE;     
            shop_s[shop_count] = SHOP_SPECIAL;   
			shop_value[shop_count] = 1; 
			shop_value1[shop_count] = 1;  	
            shop_count++;  

 			for(int i=0;i<32;i++)  
			{
				stored_shop[shop_id][i] = shop[i];
				stored_shop_s[shop_id][i] = shop_s[i];
				stored_shop_value[shop_id][i] = shop_value[i];
				stored_shop_value1[shop_id][i] = shop_value1[i];
			} 

			stored_shop_count[shop_id] = shop_count;

		}


 

      
}

bool Is_Available(int the_object, int the_weapon)
{
     int t_firepower  =0;
     int t_firerate   =0;
     int t_reloadtime =0;
     int t_capacity   =0;
     int t_special    =0;
     int t_special2    =0;   
     int t_defense     =0;   
       
     int limit_firepower  =0;
     int limit_firerate   =0; 
     int limit_reloadtime =0;
     int limit_capacity   =0;
     int limit_special    =0;
     int limit_special2   =0;     
     int limit_defense    =0;
     
     bool non_weapon=false;
     bool has_a_special = false;
     bool success=false; 
     bool has_super = false;

	 if(the_weapon < 0)
	    return(0);
     
     if(shop[the_weapon] == SHOP_TINHAT
     || shop[the_weapon] == SHOP_TINHAT_G
     || shop[the_weapon] == SHOP_TINHAT_R
     || shop[the_weapon] == SHOP_TINHAT_L
     || shop[the_weapon] == SHOP_TINHAT_S)
         non_weapon = true;
         
     if(shop[the_weapon] == SHOP_SHOES
     || shop[the_weapon] == SHOP_SHOES_G
     || shop[the_weapon] == SHOP_SHOES_R
     || shop[the_weapon] == SHOP_SHOES_L
     || shop[the_weapon] == SHOP_SHOES_S)
         non_weapon = true;
      
     if(non_weapon == false)
     {
 	 	if(the_object < 0)     
			return(0);

     t_firepower   = Get_Bit_Shift( the_object, 1);  // Firepower of this object;  
     t_firerate    = Get_Bit_Shift( the_object, 2);  // Firerate of this object;  
     t_reloadtime  = Get_Bit_Shift( the_object, 3);  // Reload of this object;  
     t_capacity    = Get_Bit_Shift( the_object, 4);  // Capacity of this object;
     t_special     = Get_Bit_Shift( the_object, 5);  // Capacity of this object;
     t_special2    = Get_Bit_Shift( the_object, 6);  // Capacity of this object;

     has_a_special = true;
     
     has_super = Check_For_Super(the_object);
             
     if(shop[the_weapon] == SHOP_THOMPSOM_MACHINE)
     {           
         limit_firepower  = Get_Bit_Shift_Int( upg_thompson, 1);
         limit_firerate   = Get_Bit_Shift_Int( upg_thompson, 2);
         limit_reloadtime = Get_Bit_Shift_Int( upg_thompson, 3);
         limit_capacity   = Get_Bit_Shift_Int( upg_thompson, 4);   
         limit_special    = Get_Bit_Shift_Int( upg_thompson, 5); 
         limit_special2   = Get_Bit_Shift_Int( upg_thompson, 6);                      
     }
       
     if(shop[the_weapon] == SHOP_WESTON_PISTOL) 
     {           
         limit_firepower  = Get_Bit_Shift_Int( upg_weston, 1);
         limit_firerate   = Get_Bit_Shift_Int( upg_weston, 2);
         limit_reloadtime = Get_Bit_Shift_Int( upg_weston, 3);
         limit_capacity   = Get_Bit_Shift_Int( upg_weston, 4);  
         limit_special    = Get_Bit_Shift_Int( upg_weston, 5);  
         limit_special2   = Get_Bit_Shift_Int( upg_weston, 6);                     
     }
       
     if(shop[the_weapon] == SHOP_TRAINING_PISTOL) 
     {           
         limit_firepower  = Get_Bit_Shift_Int( upg_training, 1);
         limit_firerate   = Get_Bit_Shift_Int( upg_training, 2);
         limit_reloadtime = Get_Bit_Shift_Int( upg_training, 3);
         limit_capacity   = Get_Bit_Shift_Int( upg_training, 4);  
         limit_special    = Get_Bit_Shift_Int( upg_training, 5); 
         limit_special2   = Get_Bit_Shift_Int( upg_training, 6);                      
     } 
            
     if(shop[the_weapon] == SHOP_LUGER_PISTOL) 
     {           
         limit_firepower  = Get_Bit_Shift_Int( upg_luger, 1);
         limit_firerate   = Get_Bit_Shift_Int( upg_luger, 2);
         limit_reloadtime = Get_Bit_Shift_Int( upg_luger, 3);
         limit_capacity   = Get_Bit_Shift_Int( upg_luger, 4);    
         limit_special    = Get_Bit_Shift_Int( upg_luger, 5);  
         limit_special2   = Get_Bit_Shift_Int( upg_luger, 6);                   
     }
       
     if(shop[the_weapon] == SHOP_COLT_PISTOL)   
     {           
         limit_firepower  = Get_Bit_Shift_Int( upg_colt, 1);
         limit_firerate   = Get_Bit_Shift_Int( upg_colt, 2);
         limit_reloadtime = Get_Bit_Shift_Int( upg_colt, 3);
         limit_capacity   = Get_Bit_Shift_Int( upg_colt, 4);  
         limit_special    = Get_Bit_Shift_Int( upg_colt, 5);      
         limit_special2   = Get_Bit_Shift_Int( upg_colt, 6);                 
     }
       
     if(shop[the_weapon] == SHOP_COLTK_PISTOL)  
     {           
         limit_firepower  = Get_Bit_Shift_Int( upg_coltk, 1);
         limit_firerate   = Get_Bit_Shift_Int( upg_coltk, 2);
         limit_reloadtime = Get_Bit_Shift_Int( upg_coltk, 3);
         limit_capacity   = Get_Bit_Shift_Int( upg_coltk, 4);    
         limit_special    = Get_Bit_Shift_Int( upg_coltk, 5);  
         limit_special2   = Get_Bit_Shift_Int( upg_coltk, 6);                   
     }
                      
     if(shop[the_weapon] == SHOP_ENFIELD_RIFLE) 
     {           
         limit_firepower  = Get_Bit_Shift_Int( upg_enfield, 1);
         limit_firerate   = Get_Bit_Shift_Int( upg_enfield, 2);
         limit_reloadtime = Get_Bit_Shift_Int( upg_enfield, 3);
         limit_capacity   = Get_Bit_Shift_Int( upg_enfield, 4);  
         limit_special    = Get_Bit_Shift_Int( upg_enfield, 5);  
         limit_special2   = Get_Bit_Shift_Int( upg_enfield, 6);                     
     }
                 
     if(shop[the_weapon] == SHOP_HUNTER_RIFLE) 
     {           
         limit_firepower  = Get_Bit_Shift_Int( upg_hunter, 1);
         limit_firerate   = Get_Bit_Shift_Int( upg_hunter, 2);
         limit_reloadtime = Get_Bit_Shift_Int( upg_hunter, 3);
         limit_capacity   = Get_Bit_Shift_Int( upg_hunter, 4); 
         limit_special    = Get_Bit_Shift_Int( upg_hunter, 5);
         limit_special2   = Get_Bit_Shift_Int( upg_hunter, 6);                        
     }
            
     if(shop[the_weapon] == SHOP_FARMERS_SHOTGUN)  
     {           
         limit_firepower  = Get_Bit_Shift_Int( upg_farmers, 1);
         limit_firerate   = Get_Bit_Shift_Int( upg_farmers, 2);
         limit_reloadtime = Get_Bit_Shift_Int( upg_farmers, 3);
         limit_capacity   = Get_Bit_Shift_Int( upg_farmers, 4);
         limit_special    = Get_Bit_Shift_Int( upg_farmers, 5);  
         limit_special2   = Get_Bit_Shift_Int( upg_farmers, 6);                       
     }
     if(shop[the_weapon] == SHOP_ARMY_SHOTGUN)  
     {           
         limit_firepower  = Get_Bit_Shift_Int( upg_army, 1);
         limit_firerate   = Get_Bit_Shift_Int( upg_army, 2);
         limit_reloadtime = Get_Bit_Shift_Int( upg_army, 3);
         limit_capacity   = Get_Bit_Shift_Int( upg_army, 4);
         limit_special    = Get_Bit_Shift_Int( upg_army, 5);  
         limit_special2   = Get_Bit_Shift_Int( upg_army, 6);                       
     }                    
     
     if(t_firepower < limit_firepower)
         success = true;
     if(t_firerate < limit_firerate)
         success = true;
     if(t_reloadtime < limit_reloadtime) 
         success = true;
     if(t_capacity < limit_capacity) 
         success = true;
     if(t_special < limit_special)
         success = true;
     if(t_special2 < limit_special2 && has_super == true)
         success = true;         
     }         
     
     if(shop[the_weapon] == SHOP_TINHAT
     || shop[the_weapon] == SHOP_TINHAT_G
     || shop[the_weapon] == SHOP_TINHAT_R
     || shop[the_weapon] == SHOP_TINHAT_L
     || shop[the_weapon] == SHOP_TINHAT_S
     )
     { 
                         
            t_defense   = player_inv_value1[the_object];
            t_special   = player_inv_value2[the_object]; 

            limit_defense = TINHAT_DE_LIMIT;  
 
            limit_special = TINHAT_SP_LIMIT; 
            
         if(t_defense < limit_defense) 
             success = true; 
                               
         if(t_special < limit_special && limit_special != 0)
             success = true;          
          
     }
     
     if(shop[the_weapon] == SHOP_SHOES
     || shop[the_weapon] == SHOP_SHOES_G
     || shop[the_weapon] == SHOP_SHOES_R
     || shop[the_weapon] == SHOP_SHOES_L
     || shop[the_weapon] == SHOP_SHOES_S
     )
     {  
                         
            t_defense   = player_inv_value1[the_object];
            t_special   = player_inv_value2[the_object]; 

            limit_defense = SHOES_HP_LIMIT;  
 
            limit_special = SHOES_SP_LIMIT; 
             
         if(t_defense < limit_defense) 
             success = true; 
                               
         if(t_special < limit_special && limit_special != 0)
             success = true;          
          
     }     
          
     return(success);

     
} 


void Set_Display_Picture(int i, int index)
{ 
   
    char string_value[128]; 
	int temp_firepower = 0; 
  
 	if(index < 0)     
		return; 
          
    memset(string_value, 0, sizeof(string_value));
    
    sprintf(counter[2].word, "");   
    sprintf(string_value, ""); 
              
     if(shop[index] == SHOP_TRAINING_PISTOL || shop[index] == SHOP_WEBLEY_PISTOL 
	 || shop[index] == SHOP_LUGER_PISTOL || shop[index] == SHOP_LUGERK_PISTOL 
	 || shop[index] == SHOP_WESTON_PISTOL || shop[index] == SHOP_WESTONK_PISTOL 
	 || shop[index] == SHOP_MAUSER_PISTOL || shop[index] == SHOP_MAUSERK_PISTOL 
	 || shop[index] == SHOP_COLT_PISTOL || shop[index] == SHOP_COLTK_PISTOL 
	 || shop[index] == SHOP_SAVAGE_PISTOL || shop[index] == SHOP_SAVAGEK_PISTOL 
	 || shop[index] == SHOP_NAVYCOLT_PISTOL  
	 )   
     {
         Set_Sprite(20, 1, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME; 

         if(shop[index] == SHOP_TRAINING_PISTOL)
            sprintf(string_value,"^A_basic^training pistol.^"); 
         if(shop[index] == SHOP_WEBLEY_PISTOL)
            sprintf(string_value,"^An_army_issue^webley pistol.^");            
         if(shop[index] == SHOP_LUGER_PISTOL)
            sprintf(string_value,"^An_enemy_luger^pistol.^");  
         if(shop[index] == SHOP_LUGERK_PISTOL)
            sprintf(string_value,"^An_enemy_luger-k^pistol.^");  
         if(shop[index] == SHOP_WESTON_PISTOL)
            sprintf(string_value,"^A_deadly_weston^pistol.^"); 
         if(shop[index] == SHOP_WESTONK_PISTOL)
            sprintf(string_value,"^A_deadly_weston-k^pistol.^");            
         if(shop[index] == SHOP_MAUSER_PISTOL)
            sprintf(string_value,"^An_enemy_mauser^pistol.^");  
         if(shop[index] == SHOP_MAUSERK_PISTOL)
            sprintf(string_value,"^A_enemy_mauser-k^pistol.^");  
         if(shop[index] == SHOP_COLT_PISTOL)
            sprintf(string_value,"^A_foreign_colt^pistol.^"); 
         if(shop[index] == SHOP_COLTK_PISTOL)
            sprintf(string_value,"^A_foreign_colt-k^pistol.^");            
         if(shop[index] == SHOP_SAVAGE_PISTOL)
            sprintf(string_value,"^The_lethal_savage^pistol.^");   
         if(shop[index] == SHOP_SAVAGEK_PISTOL)
            sprintf(string_value,"^The_lethal_savage-k^pistol.^");  
         if(shop[index] == SHOP_NAVYCOLT_PISTOL)
            sprintf(string_value,"^The ultimate navy^colt pistol!^");  
 
		 if(shop[index] == SHOP_NAVYCOLT_PISTOL)
		     Set_Sprite(20, 25, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 


         strcat(counter[2].word, string_value);     	
		 sprintf(string_value, "");
		 
		 if(shop_sequence == SHOP_BUY) 
	     {
			 if(shop[index] == SHOP_TRAINING_PISTOL)
		         temp_firepower =  (int)(PISTOL1_BASE_FP * 10);
			 if(shop[index] == SHOP_WEBLEY_PISTOL)
		         temp_firepower =  (int)(PISTOL2_BASE_FP * 10);
			 if(shop[index] == SHOP_LUGER_PISTOL)
		         temp_firepower =  (int)(PISTOL3_BASE_FP * 10);
			 if(shop[index] == SHOP_LUGERK_PISTOL)
		         temp_firepower =  (int)(PISTOL4_BASE_FP * 10);
			 if(shop[index] == SHOP_WESTON_PISTOL)
		         temp_firepower =  (int)(PISTOL5_BASE_FP * 10);
			 if(shop[index] == SHOP_WESTONK_PISTOL)
		         temp_firepower =  (int)(PISTOL6_BASE_FP * 10);
			 if(shop[index] == SHOP_MAUSER_PISTOL)
		         temp_firepower =  (int)(PISTOL7_BASE_FP * 10);
			 if(shop[index] == SHOP_MAUSERK_PISTOL)
		         temp_firepower =  (int)(PISTOL8_BASE_FP * 10);
			 if(shop[index] == SHOP_COLT_PISTOL)
		         temp_firepower =  (int)(PISTOL9_BASE_FP * 10);
			 if(shop[index] == SHOP_COLTK_PISTOL)
		         temp_firepower =  (int)(PISTOL10_BASE_FP * 10);
			 if(shop[index] == SHOP_SAVAGE_PISTOL)
		         temp_firepower =  (int)(PISTOL11_BASE_FP * 10);
			 if(shop[index] == SHOP_SAVAGEK_PISTOL)
		         temp_firepower =  (int)(PISTOL12_BASE_FP * 10);
			 if(shop[index] == SHOP_NAVYCOLT_PISTOL)
		         temp_firepower =  (int)(PISTOL13_BASE_FP * 10);

		 }
		 else
		 {
			 if(i >=0 )
				 temp_firepower = (int)Get_Weapon_Stats(i, GET_FIREPOWER);
		 }

		 if(shop_sequence == SHOP_BUY) 	
		 {
 		 if(shop_value[index] == BONUS_NONE) 
	         sprintf(string_value, "ÓÁ:%i", temp_firepower);
         if(shop_value[index] == BONUS_FIREPOWER)  
	         sprintf(string_value, "ÓÁ+%i:ÓÁ+%i", temp_firepower, shop_value1[index]);
         if(shop_value[index] == BONUS_FIRERATE)  
	         sprintf(string_value, "ÓÁ+%i:∏≥+%i", (int)(PISTOL1_BASE_FP * 10), shop_value1[index]);
         if(shop_value[index] == BONUS_RELOAD)   
	         sprintf(string_value, "ÓÁ+%i:’¨+%i", (int)(PISTOL1_BASE_FP * 10), shop_value1[index]);
         if(shop_value[index] == BONUS_CAPACITY)  
	         sprintf(string_value, "ÓÁ+%i:´œ+%i", (int)(PISTOL1_BASE_FP * 10), shop_value1[index]);
		 }
		 else
		 { 
		 if(i >= 0)
		 {
 		 if(player_inv_value1[i] == BONUS_NONE) 
		 	sprintf(string_value, "ÓÁ:%i", temp_firepower); 
         if(player_inv_value1[i] == BONUS_FIREPOWER)  
	         sprintf(string_value, "ÓÁ+%i:ÓÁ+%i", temp_firepower, player_inv_value3[i]);
         if(player_inv_value1[i] == BONUS_FIRERATE)  
	         sprintf(string_value, "ÓÁ+%i:∏≥+%i", temp_firepower, player_inv_value3[i]);
         if(player_inv_value1[i] == BONUS_RELOAD)   
	         sprintf(string_value, "ÓÁ+%i:’¨+%i", temp_firepower, player_inv_value3[i]);
         if(player_inv_value1[i] == BONUS_CAPACITY)  
	         sprintf(string_value, "ÓÁ+%i:´œ+%i", temp_firepower, player_inv_value3[i]);
		 }
		 }
 
         strcat(counter[2].word, string_value);    

     } 
     if(shop[index] == SHOP_FARMERS_SHOTGUN)
     {
         Set_Sprite(20, 2, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;              
         sprintf(counter[2].word, "^A_lethal_farmers^shotgun.^ÓÁ+%i", (int)(SHOTGUN1_BASE_FP * 10));                        
     }    
     if(shop[index] == SHOP_ARMY_SHOTGUN)
     {
         Set_Sprite(20, 29, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;              
         sprintf(counter[2].word, "^A_lethal_farmers^shotgun.^ÓÁ+%i", (int)(PISTOL1_BASE_FP * 10));                        
     }        
     if(shop[index] == SHOP_THOMPSOM_MACHINE)   
     {
         Set_Sprite(20, 3, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_Vickers^machine-gun.^ÓÁ+%i", (int)(MACHINE1_BASE_FP * 10));                        
     }               
     if(shop[index] == SHOP_FARMERS_RIFLE || shop[index] == SHOP_HUNTER_RIFLE 
	 || shop[index] == SHOP_ENFIELD_RIFLE || shop[index] == SHOP_ENFIELDK_RIFLE
	 || shop[index] == SHOP_MAUSER_RIFLE || shop[index] == SHOP_MAUSERK_RIFLE
	 || shop[index] == SHOP_CARBINE_RIFLE || shop[index] == SHOP_CARBINEK_RIFLE
	 || shop[index] == SHOP_GEWEHR_RIFLE || shop[index] == SHOP_GEWEHRK_RIFLE
	 || shop[index] == SHOP_HEINRICH_RIFLE || shop[index] == SHOP_HEINRICHK_RIFLE
	 || shop[index] == SHOP_WINCHESTER_RIFLE 
	 ) 
     {
         Set_Sprite(20, 5, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         

         if(shop[index] == SHOP_FARMERS_RIFLE)
            sprintf(string_value,"^An_old_farmers^rifle.^");  
         if(shop[index] == SHOP_HUNTER_RIFLE)
            sprintf(string_value,"^A_working_hunter^rifle.^");             
         if(shop[index] == SHOP_ENFIELD_RIFLE)
            sprintf(string_value,"^An army issue^enfield rifle.^");  
         if(shop[index] == SHOP_ENFIELDK_RIFLE)
            sprintf(string_value,"^An army issue^enfield-k rifle.^");  
         if(shop[index] == SHOP_MAUSER_RIFLE)
            sprintf(string_value,"^An enemy mauser^rifle.^");  
         if(shop[index] == SHOP_MAUSERK_RIFLE)
            sprintf(string_value,"^An enemy mauser-k^rifle.^");             
         if(shop[index] == SHOP_CARBINE_RIFLE)
            sprintf(string_value,"^A_powerful^carbine rifle.^");  
         if(shop[index] == SHOP_CARBINEK_RIFLE)
            sprintf(string_value,"^A_powerful^carbine-k rifle.^");  
         if(shop[index] == SHOP_GEWEHR_RIFLE)
            sprintf(string_value,"^An enemy gewher^rifle.^");  
         if(shop[index] == SHOP_GEWEHRK_RIFLE)
            sprintf(string_value,"^An enemy gewher-k^rifle.^");             
         if(shop[index] == SHOP_HEINRICH_RIFLE)
            sprintf(string_value,"^A_lethal_heinrich^rifle.^");  
         if(shop[index] == SHOP_HEINRICHK_RIFLE) 
            sprintf(string_value,"^A_lethal_heinrich-k^rifle.^");  
         if(shop[index] == SHOP_WINCHESTER_RIFLE)
            sprintf(string_value,"^The gun that^won the west!^");  
 
		 if(shop[index] == SHOP_WINCHESTER_RIFLE) 
		     Set_Sprite(20, 4, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 

         strcat(counter[2].word, string_value);     	
		 sprintf(string_value, "");
		 
		 if(shop_sequence == SHOP_BUY)  
	     {
			 if(shop[index] == SHOP_FARMERS_RIFLE)
		         temp_firepower =  (int)(RIFLE1_BASE_FP * 10);
			 if(shop[index] == SHOP_HUNTER_RIFLE)
		         temp_firepower =  (int)(RIFLE2_BASE_FP * 10);
			 if(shop[index] == SHOP_ENFIELD_RIFLE)
		         temp_firepower =  (int)(RIFLE3_BASE_FP * 10);
			 if(shop[index] == SHOP_ENFIELDK_RIFLE)
		         temp_firepower =  (int)(RIFLE4_BASE_FP * 10);
			 if(shop[index] == SHOP_MAUSER_RIFLE)
		         temp_firepower =  (int)(RIFLE5_BASE_FP * 10);
			 if(shop[index] == SHOP_MAUSERK_RIFLE)
		         temp_firepower =  (int)(RIFLE6_BASE_FP * 10);
			 if(shop[index] == SHOP_CARBINE_RIFLE)
		         temp_firepower =  (int)(RIFLE7_BASE_FP * 10);
			 if(shop[index] == SHOP_CARBINEK_RIFLE)
		         temp_firepower =  (int)(RIFLE8_BASE_FP * 10);
			 if(shop[index] == SHOP_GEWEHR_RIFLE)
		         temp_firepower =  (int)(RIFLE9_BASE_FP * 10);
			 if(shop[index] == SHOP_GEWEHRK_RIFLE)
		         temp_firepower =  (int)(RIFLE10_BASE_FP * 10);
			 if(shop[index] == SHOP_HEINRICH_RIFLE)
		         temp_firepower =  (int)(RIFLE11_BASE_FP * 10);
			 if(shop[index] == SHOP_HEINRICHK_RIFLE)
		         temp_firepower =  (int)(RIFLE12_BASE_FP * 10);
			 if(shop[index] == SHOP_WINCHESTER_RIFLE)
		         temp_firepower =  (int)(RIFLE13_BASE_FP * 10);
		 }
		 else
		 {
			 if(i >=0 )
				 temp_firepower = (int)Get_Weapon_Stats(i, GET_FIREPOWER);
		 }

 
			 if(shop_sequence == SHOP_BUY) 	
			 { 
 				 if(shop_value[index] == BONUS_NONE)
					 sprintf(string_value, "ÓÁ:%i", temp_firepower);
				 if(shop_value[index] == BONUS_FIREPOWER) 
					 sprintf(string_value, "ÓÁ+%i:ÓÁ+%i", temp_firepower, shop_value1[index]);
				 if(shop_value[index] == BONUS_FIRERATE)  
					 sprintf(string_value, "ÓÁ+%i:∏≥+%i", temp_firepower, shop_value1[index]);
				 if(shop_value[index] == BONUS_RELOAD)   
					 sprintf(string_value, "ÓÁ+%i:’¨+%i", temp_firepower, shop_value1[index]);
				 if(shop_value[index] == BONUS_CAPACITY)  
					 sprintf(string_value, "ÓÁ+%i:´œ+%i", temp_firepower, shop_value1[index]);
			 }
			 else  
			 {  
				 if(i>=0)
				 {
 				 if(player_inv_value1[i] == BONUS_NONE)  
		 			sprintf(string_value, "ÓÁ:%i", temp_firepower); 
				 if(player_inv_value1[i] == BONUS_FIREPOWER)  
					 sprintf(string_value, "ÓÁ+%i:ÓÁ+%i", temp_firepower, player_inv_value3[i]);
				 if(player_inv_value1[i] == BONUS_FIRERATE)  
					 sprintf(string_value, "ÓÁ+%i:∏≥+%i", temp_firepower, player_inv_value3[i]);
				 if(player_inv_value1[i] == BONUS_RELOAD)   
					 sprintf(string_value, "ÓÁ+%i:’¨+%i", temp_firepower, player_inv_value3[i]);
				 if(player_inv_value1[i] == BONUS_CAPACITY)  
					 sprintf(string_value, "ÓÁ+%i:´œ+%i", temp_firepower, player_inv_value3[i]);
				 }
			 } 

		strcat(counter[2].word, string_value);    
                       
     }    
     if(shop[index] == SHOP_TRAP_DECOY)    
     {
         Set_Sprite(20, 29, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;                   
		 if(shop_sequence == SHOP_BUY)
	         sprintf(counter[2].word, "^A re-usable^decoy trap!^È˚:%i", DECOY_HEALTH);
		 else
	         sprintf(counter[2].word, "^A re-usable^decoy trap!^È˚:%i±%i", shop_value1[index], DECOY_HEALTH);

     }   
	 if(shop[index] == SHOP_TRAP_MINE)        
     {
         Set_Sprite(20, 32, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;                   
		 if(shop_sequence == SHOP_BUY)
	         sprintf(counter[2].word, "^A wide radius^damage mine trap!", DECOY_HEALTH, DECOY_HEALTH);
		 else
	         sprintf(counter[2].word, "^A wide radius^damage mine trap!", shop_value1[index], DECOY_HEALTH);

     }   
     if(shop[index] == SHOP_SILVER_WATCH) 
     {
         Set_Sprite(20, 6, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;                   
         sprintf(counter[2].word, "^A_silver_watch.^That_actually_works!");
     }         
     if(shop[index] == SHOP_BRASS_WATCH)
     {
         Set_Sprite(20, 7, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_lovely_brass^watch_still_ticking.");
     }                   
     if(shop[index] == SHOP_GOLD_WATCH)
     {
         Set_Sprite(20, 8, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_lovely_gold^watch_still_ticking.");
     }                   
     if(shop[index] == SHOP_CARD)  
     {
         Set_Sprite(20, 9, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;                             
         sprintf(counter[2].word, "^A_cigarette_card^not_worth_much^here.");
     }                    
     if(shop[index] == SHOP_SHELLS) 
     {
         Set_Sprite(20, 10, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;          
         if(shop_sequence == SHOP_BUY)
             sprintf(counter[2].word, "^Shotgun^rounds.^Ë‡:%i", shop_value[index]);
         else
		 {
			 if(i >= 0)
	             sprintf(counter[2].word, "^Shotgun^rounds.^Ë‡:%i", player_inv_value[i]);
		 }
         
     }                 
     if(shop[index] == SHOP_BULLETS) 
     {
         Set_Sprite(20, 11, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;          
         if(shop_sequence == SHOP_BUY)         
             sprintf(counter[2].word, "^Machine-gun^rounds.^Ë‡:%i", shop_value[index]);
         else
		 {
			 if(i >= 0)
             	sprintf(counter[2].word, "^Machine-gun^Ë‡:%i", player_inv_value[i]);
		 }          
     }               
     if(shop[index] == SHOP_HGUN_AMMO)     
     {      
         Set_Sprite(20, 12, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         if(shop_sequence == SHOP_BUY)          
             sprintf(counter[2].word, "^Pistol^rounds.^Ë‡:+%i^(Ë‡:%i)", shop_value[index], INV_PISTOL_COUNT);
         else 
		 {
			 if(i >= 0) 
             	sprintf(counter[2].word, "^Pistol^rounds.^Ë‡:%i", player_inv_value[i]);
		 }            
     }                      
     if(shop[index] == SHOP_AMMO)  
     {  
         Set_Sprite(20, 13, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;                              
         if(shop_sequence == SHOP_BUY)           
             sprintf(counter[2].word, "^Rifle^rounds.^Ë‡:+%i^(Ë‡:%i)", shop_value[index], INV_RIFLE_COUNT); 
         else
		 {
			 if(i >= 0)
             	sprintf(counter[2].word, "^Rifle^rounds.^Ë‡:%i", player_inv_value[i]);
		 }           
     }      
     if(shop[index] == SHOP_HEALTH)       
     { 
         Set_Sprite(20, 21, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;                              
         if(shop_sequence == SHOP_BUY)           
             sprintf(counter[2].word, "^Portable First_aid^kit.^·…+%i.", Get_Health_Amount(AMOUNT_HEALTH) );
         else
             sprintf(counter[2].word, "^Portable First_aid^kit.^·…+%i.", Get_Health_Amount(AMOUNT_HEALTH) );
     }       
     if(shop[index] == SHOP_AMPUOLE)       
     { 
         Set_Sprite(20, 8, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;                              
         if(shop_sequence == SHOP_BUY)           
             sprintf(counter[2].word, "^Portable First_aid^Ampuole.^·…+%i.", Get_Health_Amount(AMOUNT_AMPUOLE) );
         else
             sprintf(counter[2].word, "^Portable First_aid^Ampuole.^·…+%i.", Get_Health_Amount(AMOUNT_AMPUOLE) );
     }        
     if(shop[index] == SHOP_BLACK_GRENADE)   
     {
     /*    Set_Sprite(20, 14, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;   
         sprintf(counter[2].word, "^Unlimited supply^of stick_grenades!^ÓÁ:%i", (int)GRENADE2_BASE_FP);*/

         Set_Sprite(20, 14, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;                              
         if(shop_sequence == SHOP_BUY)           
             sprintf(counter[2].word, "^Stick^grenades.^ÓÁ:%i^Ë‡:+%i^(Ë‡:%i)", (int)GRENADE2_BASE_FP, SHOP_AMOUNT_BLACK_GRENADE, INV_BLACK_GRENADE_COUNT); 
         else
		 { 
			 if(i >= 0) 
             	sprintf(counter[2].word, "^Stick^grenades.^ÓÁ:%i^Ë‡:%i", (int)GRENADE2_BASE_FP, player_inv_value2[i]);
		 }   

     }    
     if(shop[index] == SHOP_GREEN_GRENADE)  
     {
     /*    Set_Sprite(20, 17, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;   
         sprintf(counter[2].word, "^Unlimited supply^of hand_grenades!^ÓÁ:%i", (int)GRENADE1_BASE_FP);*/

         Set_Sprite(20, 17, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;                              
         if(shop_sequence == SHOP_BUY)           
             sprintf(counter[2].word, "^Hand^grenades.^ÓÁ:%i^Ë‡:+%i^(Ë‡:%i)", (int)GRENADE1_BASE_FP, SHOP_AMOUNT_GREEN_GRENADE, INV_GREEN_GRENADE_COUNT); 
         else
		 {
			 if(i >= 0)
             	sprintf(counter[2].word, "^Hand^grenades.^ÓÁ:%i^Ë‡:%i", (int)GRENADE1_BASE_FP, player_inv_value2[i]);
		 }   

     }    
     if(shop[index] == SHOP_MOLOTOV_GRENADE)   
     { 
     /*    Set_Sprite(20, 31, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;   
         sprintf(counter[2].word, "^Unlimited supply^of molotovs!^ÓÁ:%i", (int)GRENADE3_BASE_FP);*/
		  
         Set_Sprite(20, 31, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;                              
         if(shop_sequence == SHOP_BUY)           
             sprintf(counter[2].word, "^Molotov^grenades.^ÓÁ:%i^Ë‡:+%i^(Ë‡:%i)", (int)GRENADE3_BASE_FP, SHOP_AMOUNT_MOLOTOV, INV_MOLOTOV_GRENADE_COUNT); 
         else
		 {
			 if(i >= 0) 
             	sprintf(counter[2].word, "^Molotov^grenades.^ÓÁ:%i^Ë‡:%i", (int)GRENADE3_BASE_FP, player_inv_value2[i]);
		 }   

     }    
     if(shop[index] == SHOP_SCOPE)        
     {
         Set_Sprite(20, 33, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;     
         sprintf(counter[2].word, "^Increases headshot^damage by %i¡!", 5); 
     }      
	 if(shop[index] == SHOP_SCOPE2)         
     {  
         Set_Sprite(20, 33, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Increases headshot^damage by %i¡!", 10);
     }   
     if(shop[index] == SHOP_SCOPE3)       
     {  
         Set_Sprite(20, 33, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Increases headshot^damage by %i¡!", 15);
     }   
     if(shop[index] == SHOP_SCOPE4)       
     {  
         Set_Sprite(20, 33, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Increases headshot^damage by %i¡!", 20);
     }    
     if(shop[index] == SHOP_SCOPE5)        
     {   
         Set_Sprite(20, 33, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Increases headshot^damage by %i¡!", 25);
     }    
     if(shop[index] == SHOP_SCOPE6)         
     {  
         Set_Sprite(20, 33, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Increases headshot^damage by %i¡!", 30);
     }  
     if(shop[index] == SHOP_DISCOUNT)       
     {  
         Set_Sprite(20, 18, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^All shop prices^are reduced^by %i¡!", DISCOUNT_BOOST1);
     }       
     if(shop[index] == SHOP_DISCOUNT1)         
     {  
         Set_Sprite(20, 18, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^All shop prices^are reduced^by %i¡!", DISCOUNT_BOOST2);
     }   
     if(shop[index] == SHOP_DISCOUNT2)         
     {  
         Set_Sprite(20, 18, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^All shop prices^are reduced^by %i¡!", DISCOUNT_BOOST3);
     } 
     if(shop[index] == SHOP_DISCOUNT3)         
     {  
         Set_Sprite(20, 18, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^All shop prices^are reduced^by %i¡!", DISCOUNT_BOOST4);
     } 
     if(shop[index] == SHOP_DISCOUNT4)         
     {  
         Set_Sprite(20, 18, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^All shop prices^are reduced^by %i¡!", DISCOUNT_BOOST5);
     } 
     if(shop[index] == SHOP_DISCOUNT5)         
     {  
         Set_Sprite(20, 18, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^All shop prices^are reduced^by %i¡!", DISCOUNT_BOOST6);
     } 
     if(shop[index] == SHOP_FLAK)       
     {  
         Set_Sprite(20, 19, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Explosive^damage reduced^by 5¡!", 5);
     }      
     if(shop[index] == SHOP_FLAK2)         
     {  
         Set_Sprite(20, 19, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Explosive^damage reduced^by 10¡!", 5);
     }   
     if(shop[index] == SHOP_FLAK3)       
     {  
         Set_Sprite(20, 19, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Explosive^damage reduced^by 15¡!", 5);
     }   
     if(shop[index] == SHOP_FLAK4)       
     {  
         Set_Sprite(20, 19, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Explosive^damage reduced^by 20¡!", 5);
     }   
     if(shop[index] == SHOP_FLAK5)       
     {  
         Set_Sprite(20, 19, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Explosive^damage reduced^by 25¡!", 5);
     }   
     if(shop[index] == SHOP_FLAK6)        
     {  
         Set_Sprite(20, 19, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Explosive^damage reduced^by 33¡!", 5);
     }   
     if(shop[index] == SHOP_BAYONET)       
     {  
         Set_Sprite(20, 20, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Increases knife^damage by 50¡!", 5);
     }      
     if(shop[index] == SHOP_BAYONET2)        
     {  
         Set_Sprite(20, 20, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Increases knife^damage by 100¡!", 5);
     }      
     if(shop[index] == SHOP_BAYONET3)        
     {  
         Set_Sprite(20, 20, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Increases knife^damage by 200¡!", 5);
     }       
     if(shop[index] == SHOP_BAYONET4)        
     {  
         Set_Sprite(20, 20, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Increases knife^damage by 300¡!", 5);
     }        
     if(shop[index] == SHOP_BAYONET5)         
     {  
         Set_Sprite(20, 20, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Increases knife^damage by 400¡!", 5);
     }        
     if(shop[index] == SHOP_BAYONET6)         
     {  
         Set_Sprite(20, 20, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Increases knife^damage by 500¡!", 5);
     }   
     if(shop[index] == SHOP_MEDICAL)        
     {  
         Set_Sprite(20, 9, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display   
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Health item^amount increased^by %i¡!", MEDICAL_BOOST1*10);
     }      
     if(shop[index] == SHOP_MEDICAL2)         
     {  
         Set_Sprite(20, 9, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Health item^amount increased^by %i¡!", MEDICAL_BOOST2*10);
     }   
     if(shop[index] == SHOP_MEDICAL3)         
     {   
         Set_Sprite(20, 9, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Health item^amount increased^by %i¡!", MEDICAL_BOOST3*10);
     }       
     if(shop[index] == SHOP_MEDICAL4)        
     {   
         Set_Sprite(20, 9, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Health item^amount increased^by %i¡!", MEDICAL_BOOST4*10);
     }   
     if(shop[index] == SHOP_MEDICAL5)       
     {  
         Set_Sprite(20, 9, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Health item^amount increased^by %i¡!", MEDICAL_BOOST5*10);
     }   
     if(shop[index] == SHOP_MEDICAL6)            
     {  
         Set_Sprite(20, 9, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;    
         sprintf(counter[2].word, "^Health item^amount increased^by %i¡!", MEDICAL_BOOST6*10);
     }  
    
     if(shop[index] == SHOP_SOCK)     
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_smelly_sock^Good_for^decorating_a^tent!");
     }   
     if(shop[index] == SHOP_LANTERN)   
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_lantern^Good_for^decorating_a^tent!");
     }     
     if(shop[index] == SHOP_TEDDY)  
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_voodoo_doll^Good_for^decorating_a^tent!");
     }    
     if(shop[index] == SHOP_BOOKS)   
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^Children_books^Good_for^decorating_a^tent!");
     }   
     if(shop[index] == SHOP_ASHTRAY)  
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^An_ashtray^Good_for^decorating_a^tent!");
     }  
     if(shop[index] == SHOP_RUG)   
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_rug^Good_for^decorating_a^tent!");
     }  
     if(shop[index] == SHOP_CHAIR)
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_chair^Good_for^decorating_a^tent!");
     }  
     if(shop[index] == SHOP_DIARY) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_diary^Good_for^decorating_a^tent!");
     }      
     if(shop[index] == SHOP_GOLFCLUBS) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^Golf_Clubs^Good_for^decorating_a^tent!");
     }      
     if(shop[index] == SHOP_PAINTING) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_painting^Good_for^decorating_a^tent!");
     }      
     if(shop[index] == SHOP_PIGGYBANK) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_Piggy_bank^Good_for^decorating_a^tent!");
     }      
     if(shop[index] == SHOP_BIBLE) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_Bible^Good_for^decorating_a^tent!");
     }     
     if(shop[index] == SHOP_FLAG) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_Flag^Good_for^decorating_a^tent!");
     }      
     if(shop[index] == SHOP_BEDPAN)  
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^Keisers_Key^Good_for^opening_a^door.");
     }    
     if(shop[index] == SHOP_BOGROLL) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^Some_bog_roll^Good_for^decorating_a^tent!");
     }      
     if(shop[index] == SHOP_PLATE) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_china_plate^Good_for^decorating_a^tent!");
     } 
     if(shop[index] == SHOP_TEACUP) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_tea_cup^Good_for^decorating_a^tent!");
     }      
     if(shop[index] == SHOP_HAMLET) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^Hamlet&s_skull^Good_for^decorating_a^tent!");
     }      
     if(shop[index] == SHOP_SNUFFBOX) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_snuff_box^Good_for^decorating_a^tent!");
     }      
     if(shop[index] == SHOP_TOYPLANE) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_toy_plane^Good_for^decorating_a^tent!");
     }             
     if(shop[index] == SHOP_POSTER) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_poster^Good_for^decorating_a^tent!");
     }   
     if(shop[index] == SHOP_FIREVEST)   
     {
         Set_Sprite(20, 30, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^Makes_the_wearer^Immune_against^fire!");
     }  
     if(shop[index] == SHOP_GASMASK)  
     {
         Set_Sprite(20, 28, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^Makes_the_wearer^Immune_against^gas!");
     }               
         
     if(shop[index] == SHOP_BUY_GOLFCLUBS) 
     { 
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^Golf_Clubs^Good_for^decorating_a^tent!");
     }            
     if(shop[index] == SHOP_BUY_PIGGYBANK) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;          
         sprintf(counter[2].word, "^A_Piggy_bank^Good_for^decorating_a^tent!");
     }       
     if(shop[index] == SHOP_BUY_FLAG) 
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A_Flag^Good_for^decorating_a^tent!");
     }   
     if(shop[index] == SHOP_BUY_FIREVEST)  
     { 
         Set_Sprite(20, 30, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^Makes_the_wearer^Immune_against^fire!");
     }              
     if(shop[index] == SHOP_BUY_GASMASK) 
     { 
         Set_Sprite(20, 28, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^Makes_the_wearer^Immune_against^gas!");
     }    

     if(shop[index] == SHOP_TINHAT) 
     { 
         Set_Sprite(20, 26, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A regular tin^helmet.^ÕÛ+%i", shop_value[index]);
     }  

     if(shop[index] == SHOP_SHOES) 
     {  
         Set_Sprite(20, 27, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;         
         sprintf(counter[2].word, "^A regular army^boots.^ÕÛ+%i", shop_value[index]);
     }        

     if(shop[index] == SHOP_MEDAL)  
     { 
         Set_Sprite(20, 7, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display                      
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;           
    
              if(shop_value1[index] == 0)   
                  sprintf( counter[2].word, "^A lovely shiny^medal.^ÕÛ+%i", shop_value[index]); // Defense
              if(shop_value1[index] == 1)  
                  sprintf( counter[2].word, "^A lovely shiny^medal.^·…+%i", shop_value[index]); // Life
              if(shop_value1[index] == 2)  
                  sprintf( counter[2].word, "^A lovely shiny^medal.^⁄”+%i", shop_value[index]); // Accuracy
              if(shop_value1[index] == 3)  
                  sprintf( counter[2].word, "^A lovely shiny^medal.^∫—+%i", shop_value[index]); // Pistol
              if(shop_value1[index] == 4)  
                  sprintf( counter[2].word, "^A lovely shiny^medal.^»÷+%i", shop_value[index]); // Rifle  
              if(shop_value1[index] == 5)  
                  sprintf( counter[2].word, "^A lovely shiny^medal.^´œ+%i¡", shop_value[index]*3); // Ammo Plus 
              if(shop_value1[index] == 6)  
                  sprintf( counter[2].word, "^A lovely shiny^medal.^Ù‚+%i¡", shop_value[index]); // Gold
              if(shop_value1[index] == 7)  
                  sprintf( counter[2].word, "^A lovely shiny^medal.^/«+%i", shop_value[index]); // Stamina
              if(shop_value1[index] == 8)  
                  sprintf( counter[2].word, "^A lovely shiny^medal.^˘°+%i", shop_value[index]); // Regen 
              if(shop_value1[index] == 9)  
                  sprintf( counter[2].word, "^A lovely shiny^medal.^$é+%i¡", shop_value[index]); // XP  
     }    
              
     if(shop[index] == SHOP_CROWN) 
     {
         Set_Sprite(20, 16, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;                              
         sprintf(counter[2].word, "^A_golden_crown^fit_for_a_king!");
     }     
     if(shop[index] == SHOP_BAR) 
     {
         Set_Sprite(20, 17, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;                     
         sprintf(counter[2].word, "^A_precious^Emerald^worth_quite_alot.");
     }      
     if(shop[index] == SHOP_PIPE) 
     {
         Set_Sprite(20, 18, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display  
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;                             
         sprintf(counter[2].word, "^A_precious^Ruby^worth_quite_alot.");
     }        
     if(shop[index] == SHOP_PORTRAIT) 
     {
         Set_Sprite(20, 19, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display   
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;                            
         sprintf(counter[2].word, "^A_precious^Diamond^worth_quite_alot.");
     }     
     if(shop[index] == SHOP_DIRTY)  
     {
         Set_Sprite(20, 15, PLAY, ANIM_SPRITE, ANIM_NOT_WALKING); // Picture Display 
         shop_switch_timer = (int)TimerGetTime() + SWITCH_TIME;           
         sprintf(counter[2].word, "^Dirty_magazines^Good_for^decorating_a^tent!");
     }    
     // Tin Hat
     if(shop[index] == SHOP_TINHAT_DEFENSE_UPG1)
     {
       sprintf(string_value,"^Increase_Defense^_%0.1f_to_%0.1f", TINHAT1_BASE_DE, TINHAT2_BASE_DE);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_TINHAT_DEFENSE_UPG2)
     {
       sprintf(string_value,"^Increase_Defense^_%0.1f_to_%0.1f", TINHAT2_BASE_DE, TINHAT3_BASE_DE);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_TINHAT_DEFENSE_UPG3) 
     {
       sprintf(string_value,"^Increase_Defense^_%0.1f_to_%0.1f", TINHAT3_BASE_DE, TINHAT4_BASE_DE);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_TINHAT_DEFENSE_UPG4)
     {
       sprintf(string_value,"^Increase_Defense^_%0.1f_to_%0.1f", TINHAT4_BASE_DE, TINHAT5_BASE_DE);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_TINHAT_DEFENSE_UPG5)
     {
       sprintf(string_value,"^Increase_Defense^_%0.1f_to_%0.1f", TINHAT5_BASE_DE, TINHAT6_BASE_DE);
       strcat(counter[2].word, string_value);                    
     }          
     if(shop[index] == SHOP_TINHAT_SPECIAL_UPG1)
	 if(i >= 0)      
     {
       if(player_inv_value[i] == TINHAT_HEADWEAR) 
           sprintf(string_value,"^Frag_Armour^Reduce_Explosive^Damage_by_25¿");
       if(player_inv_value[i] == TINHAT_G_HEADWEAR)
           sprintf(string_value,"^Extra_Gold^Enemies_drop^10¿_extra_gold");
       if(player_inv_value[i] == TINHAT_R_HEADWEAR)
           sprintf(string_value,"^Barbed_Armour^Enemies_take^Damage_when_attacking^at_close_range");
       if(player_inv_value[i] == TINHAT_L_HEADWEAR)
           sprintf(string_value,"^Life_Armour^Increase_Life^by_15¿");
       if(player_inv_value[i] == TINHAT_S_HEADWEAR)
           sprintf(string_value,"^Super_Armour^Increase_Defense^by_4.0");
           
       strcat(counter[2].word, string_value);                    
     }      
     
     // Shoes
     if(shop[index] == SHOP_SHOES_HEALTH_UPG1)
     {
       sprintf(string_value,"^Increase_Health^_%0.1f_to_%0.1f", SHOES1_BASE_HP, SHOES2_BASE_HP);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_SHOES_HEALTH_UPG2)
     {
       sprintf(string_value,"^Increase_Health^_%0.1f_to_%0.1f", SHOES2_BASE_HP, SHOES3_BASE_HP);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_SHOES_HEALTH_UPG3) 
     {
       sprintf(string_value,"^Increase_Health^_%0.1f_to_%0.1f", SHOES3_BASE_HP, SHOES4_BASE_HP);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_SHOES_HEALTH_UPG4)
     {
       sprintf(string_value,"^Increase_Health^_%0.1f_to_%0.1f", SHOES4_BASE_HP, SHOES5_BASE_HP);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_SHOES_HEALTH_UPG5)
     {
       sprintf(string_value,"^Increase_Health^_%0.1f_to_%0.1f", SHOES5_BASE_HP, SHOES6_BASE_HP);
       strcat(counter[2].word, string_value);                    
     }          
     if(shop[index] == SHOP_SHOES_SPECIAL_UPG1)
	 if( i >= 0)     
     {
       if(player_inv_value[i] == SHOES_FOOTWEAR) 
           sprintf(string_value,"^Frag_Armour^Reduce_Explosive^Damage_by_25¿");
       if(player_inv_value[i] == SHOES_G_FOOTWEAR)
           sprintf(string_value,"^Extra_Gold^Enemies_drop^10¿_extra_gold");
       if(player_inv_value[i] == SHOES_R_FOOTWEAR)
           sprintf(string_value,"^Barbed_Armour^Enemies_take^Damage_when_attacking^at_close_range");
       if(player_inv_value[i] == SHOES_L_FOOTWEAR)
           sprintf(string_value,"^Life_Armour^Increase_Life^by_15¿");
       if(player_inv_value[i] == SHOES_S_FOOTWEAR)
           sprintf(string_value,"^Super_Armour^Increase_Defense^by_4.0");
            
       strcat(counter[2].word, string_value);                    
     }              
               
     // Training Pistol
     if(shop[index] == SHOP_TRAINING_FIREPOWER_UPG1)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", TRAINING1_BASE_FP, TRAINING2_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_TRAINING_FIREPOWER_UPG2)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", TRAINING2_BASE_FP, TRAINING3_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }     
     if(shop[index] == SHOP_TRAINING_FIREPOWER_UPG3)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", TRAINING3_BASE_FP, TRAINING4_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_TRAINING_FIREPOWER_UPG4)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", TRAINING4_BASE_FP, TRAINING5_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }    
     if(shop[index] == SHOP_TRAINING_FIREPOWER_UPG5)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", TRAINING5_BASE_FP, TRAINING6_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }                      
     if(shop[index] == SHOP_TRAINING_FIRERATE_UPG1)
     {
       sprintf(string_value,"^Increase_Fire_Rate^_%0.2f_to_%0.2f", TRAINING1_BASE_FE, TRAINING2_BASE_FE);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_TRAINING_FIRERATE_UPG2)
     {
       sprintf(string_value,"^Increase_Fire_Rate^_%0.2f_to_%0.2f", TRAINING2_BASE_FE, TRAINING3_BASE_FE);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_TRAINING_RELOAD_UPG1)
     {
       sprintf(string_value,"^Decrease_Reload^_%0.2f_to_%0.2f", TRAINING1_BASE_RD, TRAINING2_BASE_RD);
       strcat(counter[2].word, string_value);                    
     }  
     if(shop[index] == SHOP_TRAINING_RELOAD_UPG2)
     {
       sprintf(string_value,"^Increase_Reload^_%0.2f_to_%0.2f", TRAINING2_BASE_RD, TRAINING3_BASE_RD);
       strcat(counter[2].word, string_value);                    
     }       
     if(shop[index] == SHOP_TRAINING_CAPACITY_UPG1)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", TRAINING1_BASE_CY, TRAINING2_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_TRAINING_CAPACITY_UPG2)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", TRAINING2_BASE_CY, TRAINING3_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_TRAINING_CAPACITY_UPG3)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", TRAINING3_BASE_CY, TRAINING4_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_TRAINING_CAPACITY_UPG4)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", TRAINING4_BASE_CY, TRAINING5_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_TRAINING_CAPACITY_UPG5)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", TRAINING5_BASE_CY, TRAINING6_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }                
     if(shop[index] == SHOP_TRAINING_SPECIAL_UPG1)
     {
       sprintf(string_value,"^Armour_Piercing^Bullets_go_through^armour.");
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_TRAINING_SPECIAL2_UPG1) 
     {
       sprintf(string_value,"^Unlimited_Ammo^Never_need^ammunition^again!");
       strcat(counter[2].word, string_value);                    
     }      
     // Weston Pistol
     if(shop[index] == SHOP_WESTON_FIREPOWER_UPG1)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", PISTOL1_BASE_FP, PISTOL2_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_WESTON_FIREPOWER_UPG2)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", PISTOL2_BASE_FP, PISTOL3_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }     
     if(shop[index] == SHOP_WESTON_FIREPOWER_UPG3)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", PISTOL3_BASE_FP, PISTOL4_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_WESTON_FIREPOWER_UPG4)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", PISTOL4_BASE_FP, PISTOL5_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }    
     if(shop[index] == SHOP_WESTON_FIREPOWER_UPG5)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", PISTOL5_BASE_FP, PISTOL6_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }                      
     if(shop[index] == SHOP_WESTON_FIRERATE_UPG1)
     {
       sprintf(string_value,"^Increase_Fire_Rate^_%0.2f_to_%0.2f", PISTOL1_BASE_FE, PISTOL2_BASE_FE);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_WESTON_FIRERATE_UPG2)
     {
       sprintf(string_value,"^Increase_Fire_Rate^_%0.2f_to_%0.2f", PISTOL2_BASE_FE, PISTOL3_BASE_FE);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_WESTON_RELOAD_UPG1)
     {
       sprintf(string_value,"^Decrease_Reload^_%0.2f_to_%0.2f", PISTOL1_BASE_RD, PISTOL2_BASE_RD);
       strcat(counter[2].word, string_value);                    
     }  
     if(shop[index] == SHOP_WESTON_RELOAD_UPG2)
     {
       sprintf(string_value,"^Increase_Reload^_%0.2f_to_%0.2f", PISTOL2_BASE_RD, PISTOL3_BASE_RD);
       strcat(counter[2].word, string_value);                    
     }       
     if(shop[index] == SHOP_WESTON_CAPACITY_UPG1)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", PISTOL1_BASE_CY, PISTOL2_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_WESTON_CAPACITY_UPG2)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", PISTOL2_BASE_CY, PISTOL3_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_WESTON_CAPACITY_UPG3)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", PISTOL3_BASE_CY, PISTOL4_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_WESTON_CAPACITY_UPG4)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", PISTOL4_BASE_CY, PISTOL5_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_WESTON_CAPACITY_UPG5)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", PISTOL5_BASE_CY, PISTOL6_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }                
     if(shop[index] == SHOP_WESTON_SPECIAL_UPG1)
     {
       sprintf(string_value,"^Armour_Piercing^Bullets_go_through^armour.");
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_WESTON_SPECIAL2_UPG1)
     {
       sprintf(string_value,"^Unlimited_Ammo^Never_need^ammunition^again!");
       strcat(counter[2].word, string_value);                    
     }                     
     // Enfield Rifle
     if(shop[index] == SHOP_ENFIELD_FIREPOWER_UPG1)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", RIFLE1_BASE_FP, RIFLE2_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_ENFIELD_FIREPOWER_UPG2)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", RIFLE2_BASE_FP, RIFLE3_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_ENFIELD_FIREPOWER_UPG3)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", RIFLE3_BASE_FP, RIFLE4_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_ENFIELD_FIREPOWER_UPG4)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", RIFLE4_BASE_FP, RIFLE5_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_ENFIELD_FIREPOWER_UPG5)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", RIFLE5_BASE_FP, RIFLE6_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_ENFIELD_FIRERATE_UPG1)
     {
       sprintf(string_value,"^Increase_Fire_Rate^_%0.2f_to_%0.2f", RIFLE1_BASE_FE, RIFLE2_BASE_FE);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_ENFIELD_RELOAD_UPG1)
     {
       sprintf(string_value,"^Decrease_Reload^_%0.2f_to_%0.2f", RIFLE1_BASE_RD, RIFLE2_BASE_RD);
       strcat(counter[2].word, string_value);                    
     }                    
     if(shop[index] == SHOP_ENFIELD_RELOAD_UPG2)
     {
       sprintf(string_value,"^Decrease_Reload^_%0.2f_to_%0.2f", RIFLE2_BASE_RD, RIFLE3_BASE_RD);
       strcat(counter[2].word, string_value);                    
     }   
     if(shop[index] == SHOP_ENFIELD_CAPACITY_UPG1)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", RIFLE1_BASE_CY, RIFLE2_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_ENFIELD_CAPACITY_UPG2)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", RIFLE2_BASE_CY, RIFLE3_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_ENFIELD_CAPACITY_UPG3)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", RIFLE3_BASE_CY, RIFLE4_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_ENFIELD_CAPACITY_UPG4)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", RIFLE4_BASE_CY, RIFLE5_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_ENFIELD_CAPACITY_UPG5)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", RIFLE5_BASE_CY, RIFLE6_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
                         
     // Farmers Shotgun
     if(shop[index] == SHOP_FARMERS_FIREPOWER_UPG1)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", SHOTGUN1_BASE_FP, SHOTGUN2_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_FARMERS_FIREPOWER_UPG2)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", SHOTGUN2_BASE_FP, SHOTGUN3_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_FARMERS_FIREPOWER_UPG3)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", SHOTGUN3_BASE_FP, SHOTGUN4_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_FARMERS_FIREPOWER_UPG4)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", SHOTGUN4_BASE_FP, SHOTGUN5_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_FARMERS_FIREPOWER_UPG5)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", SHOTGUN5_BASE_FP, SHOTGUN6_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_FARMERS_FIRERATE_UPG1)
     {
       sprintf(string_value,"^Increase_Fire_Rate^_%0.2f_to_%0.2f", SHOTGUN1_BASE_FE, SHOTGUN2_BASE_FE);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_FARMERS_RELOAD_UPG1)
     {
       sprintf(string_value,"^Decrease_Reload^_%0.2f_to_%0.2f", SHOTGUN1_BASE_RD, SHOTGUN2_BASE_RD);
       strcat(counter[2].word, string_value);                    
     }                           
     if(shop[index] == SHOP_FARMERS_RELOAD_UPG2)
     {
       sprintf(string_value,"^Decrease_Reload^_%0.2f_to_%0.2f", SHOTGUN2_BASE_RD, SHOTGUN3_BASE_RD);
       strcat(counter[2].word, string_value);                    
     }     
     if(shop[index] == SHOP_FARMERS_CAPACITY_UPG1)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", SHOTGUN1_BASE_CY, SHOTGUN2_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_FARMERS_CAPACITY_UPG2)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", SHOTGUN2_BASE_CY, SHOTGUN3_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }   
     if(shop[index] == SHOP_FARMERS_CAPACITY_UPG3)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", SHOTGUN3_BASE_CY, SHOTGUN4_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }   
     if(shop[index] == SHOP_FARMERS_CAPACITY_UPG4)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", SHOTGUN4_BASE_CY, SHOTGUN5_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }   
     if(shop[index] == SHOP_FARMERS_CAPACITY_UPG5)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", SHOTGUN5_BASE_CY, SHOTGUN6_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }                       
     if(shop[index] == SHOP_FARMERS_SPECIAL_UPG1)  
     {
       sprintf(string_value,"^Wide_Shot^Increase_spread^of_pellets_by^25¿!");                    
       strcat(counter[2].word, string_value);                    
     }    
     if(shop[index] == SHOP_FARMERS_SPECIAL2_UPG1) 
     {
       sprintf(string_value,"^Double_Barrel^Fires_two_rounds^instead_of_one.");
       strcat(counter[2].word, string_value);                    
     }   
                         
     // Army Shotgun
     if(shop[index] == SHOP_ARMY_FIREPOWER_UPG1)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", SHOTGUN1_BASE_FP, SHOTGUN2_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_ARMY_FIREPOWER_UPG2)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", SHOTGUN2_BASE_FP, SHOTGUN3_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_ARMY_FIREPOWER_UPG3)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", SHOTGUN3_BASE_FP, SHOTGUN4_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_ARMY_FIREPOWER_UPG4)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", SHOTGUN4_BASE_FP, SHOTGUN5_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_ARMY_FIREPOWER_UPG5)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", SHOTGUN5_BASE_FP, SHOTGUN6_BASE_FP);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_ARMY_FIRERATE_UPG1)
     {
       sprintf(string_value,"^Increase_Fire_Rate^_%0.2f_to_%0.2f", SHOTGUN1_BASE_FE, SHOTGUN2_BASE_FE);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_ARMY_RELOAD_UPG1)
     {
       sprintf(string_value,"^Decrease_Reload^_%0.2f_to_%0.2f", SHOTGUN1_BASE_RD, SHOTGUN2_BASE_RD);
       strcat(counter[2].word, string_value);                    
     }                           
     if(shop[index] == SHOP_ARMY_RELOAD_UPG2)
     {
       sprintf(string_value,"^Decrease_Reload^_%0.2f_to_%0.2f", SHOTGUN2_BASE_RD, SHOTGUN3_BASE_RD);
       strcat(counter[2].word, string_value);                    
     }     
     if(shop[index] == SHOP_ARMY_CAPACITY_UPG1)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", SHOTGUN1_BASE_CY, SHOTGUN2_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_ARMY_CAPACITY_UPG2)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", SHOTGUN2_BASE_CY, SHOTGUN3_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }   
     if(shop[index] == SHOP_ARMY_CAPACITY_UPG3)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", SHOTGUN3_BASE_CY, SHOTGUN4_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }   
     if(shop[index] == SHOP_ARMY_CAPACITY_UPG4)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", SHOTGUN4_BASE_CY, SHOTGUN5_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }   
     if(shop[index] == SHOP_ARMY_CAPACITY_UPG5)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", SHOTGUN5_BASE_CY, SHOTGUN6_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }                        
     if(shop[index] == SHOP_ARMY_SPECIAL_UPG1)  
     {
       sprintf(string_value,"^Wide_Shot^Increase_spread^of_pellets_by^25¿!");                    
       strcat(counter[2].word, string_value);                    
     }    
     if(shop[index] == SHOP_ARMY_SPECIAL2_UPG1) 
     {
       sprintf(string_value,"^Double_Barrel^Fires_two_rounds^instead_of_one.");
       strcat(counter[2].word, string_value);                    
     }        
     
           
     // Luger Pistol
     if(shop[index] == SHOP_LUGER_FIREPOWER_UPG1)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", LUGER1_BASE_FP, LUGER2_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_LUGER_FIREPOWER_UPG2)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", LUGER2_BASE_FP, LUGER3_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }   
     if(shop[index] == SHOP_LUGER_FIREPOWER_UPG3)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", LUGER3_BASE_FP, LUGER4_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }   
     if(shop[index] == SHOP_LUGER_FIREPOWER_UPG4)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", LUGER4_BASE_FP, LUGER5_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }   
     if(shop[index] == SHOP_LUGER_FIREPOWER_UPG5)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", LUGER5_BASE_FP, LUGER6_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }                       
     if(shop[index] == SHOP_LUGER_FIRERATE_UPG1)
     {
       sprintf(string_value,"^Increase_Fire_Rate^_%0.2f_to_%0.2f", LUGER1_BASE_FE, LUGER2_BASE_FE);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_LUGER_FIRERATE_UPG2)
     {
       sprintf(string_value,"^Increase_Fire_Rate^_%0.2f_to_%0.2f", LUGER2_BASE_FE, LUGER3_BASE_FE);
       strcat(counter[2].word, string_value);                    
     }        
     if(shop[index] == SHOP_LUGER_RELOAD_UPG1)
     {
       sprintf(string_value,"^Decrease_Reload^_%0.2f_to_%0.2f", LUGER1_BASE_RD, LUGER2_BASE_RD);
       strcat(counter[2].word, string_value);                    
     }       
     if(shop[index] == SHOP_LUGER_RELOAD_UPG2)
     {
       sprintf(string_value,"^Decrease_Reload^_%0.2f_to_%0.2f", LUGER2_BASE_RD, LUGER3_BASE_RD);
       strcat(counter[2].word, string_value);                    
     }     
     if(shop[index] == SHOP_LUGER_CAPACITY_UPG1)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", LUGER1_BASE_CY, LUGER2_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }  
     if(shop[index] == SHOP_LUGER_CAPACITY_UPG2)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", LUGER2_BASE_CY, LUGER3_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }  
     if(shop[index] == SHOP_LUGER_CAPACITY_UPG3)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", LUGER3_BASE_CY, LUGER4_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }  
     if(shop[index] == SHOP_LUGER_CAPACITY_UPG4)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", LUGER4_BASE_CY, LUGER5_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }  
     if(shop[index] == SHOP_LUGER_CAPACITY_UPG5)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", LUGER5_BASE_CY, LUGER6_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }             
                   
     // Thompson Machinegun
     if(shop[index] == SHOP_MACHINE_FIREPOWER_UPG1)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", MACHINE1_BASE_FP, MACHINE2_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }       
     if(shop[index] == SHOP_MACHINE_FIREPOWER_UPG2)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", MACHINE2_BASE_FP, MACHINE3_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }  
     if(shop[index] == SHOP_MACHINE_FIREPOWER_UPG3)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", MACHINE3_BASE_FP, MACHINE4_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }  
     if(shop[index] == SHOP_MACHINE_FIREPOWER_UPG4)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", MACHINE4_BASE_FP, MACHINE5_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }  
     if(shop[index] == SHOP_MACHINE_FIREPOWER_UPG5)
     {
       sprintf(string_value,"^Increase_Fire_Power^_%0.1f_to_%0.1f", MACHINE5_BASE_FP, MACHINE6_BASE_FP);
       strcat(counter[2].word, string_value);                    
     }  
     if(shop[index] == SHOP_MACHINE_FIRERATE_UPG1)
     {
       sprintf(string_value,"^Increase_Fire_Rate^_%0.2f_to_%0.2f", MACHINE1_BASE_FE, MACHINE2_BASE_FE);
       strcat(counter[2].word, string_value);                    
     }       
     if(shop[index] == SHOP_MACHINE_RELOAD_UPG1)
     {
       sprintf(string_value,"^Decrease_Reload^_%0.2f_to_%0.2f", MACHINE1_BASE_RD, MACHINE2_BASE_RD);
       strcat(counter[2].word, string_value);                    
     }      
     if(shop[index] == SHOP_MACHINE_RELOAD_UPG2)
     {
       sprintf(string_value,"^Decrease_Reload^_%0.2f_to_%0.2f", MACHINE2_BASE_RD, MACHINE3_BASE_RD);
       strcat(counter[2].word, string_value);                    
     }           
     if(shop[index] == SHOP_MACHINE_CAPACITY_UPG1)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", MACHINE1_BASE_CY, MACHINE2_BASE_CY);
       strcat(counter[2].word, string_value);                    
     }       
     if(shop[index] == SHOP_MACHINE_CAPACITY_UPG2)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", MACHINE2_BASE_CY, MACHINE3_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_MACHINE_CAPACITY_UPG3)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", MACHINE3_BASE_CY, MACHINE4_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_MACHINE_CAPACITY_UPG4)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", MACHINE4_BASE_CY, MACHINE5_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_MACHINE_CAPACITY_UPG5)
     {
       sprintf(string_value,"^Increase_Capacity^_%i_to_%i", MACHINE5_BASE_CY, MACHINE6_BASE_CY);
       strcat(counter[2].word, string_value);                    
     } 
     if(shop[index] == SHOP_MACHINE_SPECIAL_UPG1)
     {
       sprintf(string_value,"^Stock^Increases_accuracy^_75¿_to_95¿");
       strcat(counter[2].word, string_value);                    
     }                                              
     if(shop[index] == SHOP_MACHINE_SPECIAL2_UPG1)
     {
       sprintf(string_value,"^Gun_Sight^Enables_headshots^and_footshots!");
       strcat(counter[2].word, string_value);                    
     }        
 
                              
}

void Calculate_Weapon_Buy(int index, int item)
{
    int value=0; 
    float check=0.0f; 
    int check1=0;     
    char string_value[128];    
    float firepower = 0.0f;
    float firerate = 0.0f;
    float reload_speed = 0.0f;
    float capacity = 0.0f;
    float special  = 0.0f;
    int v_firepower = 0;
    int v_firerate = 0;
    int v_reload_speed = 0;
    int v_capacity = 0; 
    int v_special = 0;

	if(index < 0)
		return;
          
    memset(string_value, 0, sizeof(string_value));
            
    if(shop[index] == SHOP_FARMERS_SHOTGUN) 
    {
        firepower =    (float)SHOTGUN1_BASE_FP;
        firerate =     (float)SHOTGUN1_BASE_FE;
        reload_speed = (float)SHOTGUN1_BASE_RD;
        capacity =     (float)SHOTGUN1_BASE_CY;
        v_firepower = FARMERS_FP_LIMIT;
        v_firerate  = FARMERS_FE_LIMIT; 
        v_reload_speed = FARMERS_RD_LIMIT;
        v_capacity     = FARMERS_CY_LIMIT;
        if(shop_s[index] == SHOP_SPECIAL) 
            v_special = FARMERS_SP_LIMIT; 
    }  
            
    if(shop[index] == SHOP_ARMY_SHOTGUN) 
    {
        firepower =    (float)ARMY1_BASE_FP;
        firerate =     (float)ARMY1_BASE_FE;
        reload_speed = (float)ARMY1_BASE_RD;
        capacity =     (float)ARMY1_BASE_CY;
        v_firepower = ARMY_FP_LIMIT; 
        v_firerate  = ARMY_FE_LIMIT; 
        v_reload_speed = ARMY_RD_LIMIT;
        v_capacity     = ARMY_CY_LIMIT;
        if(shop_s[index] == SHOP_SPECIAL) 
            v_special = ARMY_SP_LIMIT; 
    }  
                    
    if(shop[index] == SHOP_WESTON_PISTOL)  
    {
        firepower =    (float)PISTOL1_BASE_FP;
        firerate =     (float)PISTOL1_BASE_FE;
        reload_speed = (float)PISTOL1_BASE_RD;
        capacity =     (float)PISTOL1_BASE_CY;
        v_firepower = WESTON_FP_LIMIT;
        v_firerate  = WESTON_FE_LIMIT; 
        v_reload_speed = WESTON_RD_LIMIT;
        v_capacity     = WESTON_CY_LIMIT;  
        if(shop_s[index] == SHOP_SPECIAL) 
            v_special = WESTON_SP_LIMIT;     
    }     
                
    if(shop[index] == SHOP_TRAINING_PISTOL) 
    {
        firepower =    (float)TRAINING1_BASE_FP;
        firerate =     (float)TRAINING1_BASE_FE;
        reload_speed = (float)TRAINING1_BASE_RD; 
        capacity =     (float)TRAINING1_BASE_CY;
        v_firepower = TRAINING_FP_LIMIT; 
        v_firerate  = TRAINING_FE_LIMIT;
        v_reload_speed = TRAINING_RD_LIMIT;
        v_capacity     = TRAINING_CY_LIMIT;  
        if(shop_s[index] == SHOP_SPECIAL) 
            v_special = 1;     
    }     
                    
    if(shop[index] == SHOP_THOMPSOM_MACHINE) 
    {
        firepower =    (float)MACHINE1_BASE_FP;
        firerate =     (float)MACHINE1_BASE_FE;
        reload_speed = (float)MACHINE1_BASE_RD;
        capacity =     (float)MACHINE1_BASE_CY; 
        v_firepower = MACHINE_FP_LIMIT;
        v_firerate  = MACHINE_FE_LIMIT;
        v_reload_speed = MACHINE_RD_LIMIT;
        v_capacity     = MACHINE_CY_LIMIT;   
        if(shop_s[index] == SHOP_SPECIAL) 
            v_special = MACHINE_SP_LIMIT;     
    }    
                
    if(shop[index] == SHOP_LUGER_PISTOL) 
    {
        firepower =    (float)LUGER1_BASE_FP;
        firerate =     (float)LUGER1_BASE_FE;
        reload_speed = (float)LUGER1_BASE_RD; 
        capacity =     (float)LUGER1_BASE_CY;
        v_firepower = LUGER_FP_LIMIT;
        v_firerate  = LUGER_FE_LIMIT;
        v_reload_speed = LUGER_RD_LIMIT;
        v_capacity     = LUGER_CY_LIMIT; 
        if(shop_s[index] == SHOP_SPECIAL) 
            v_special = LUGER_SP_LIMIT;      
    }    
                
    if(shop[index] == SHOP_ENFIELD_RIFLE) 
    {
        firepower =    (float)RIFLE1_BASE_FP;
        firerate =     (float)RIFLE1_BASE_FE;
        reload_speed = (float)RIFLE1_BASE_RD;
        capacity =     (float)RIFLE1_BASE_CY;
        v_firepower = ENFIELD_FP_LIMIT;
        v_firerate  = ENFIELD_FE_LIMIT;
        v_reload_speed = ENFIELD_RD_LIMIT;
        v_capacity     = ENFIELD_CY_LIMIT;   
        if(shop_s[index] == SHOP_SPECIAL) 
            v_special = ENFIELD_SP_LIMIT;     
    }    
                  
    counter[2].length = 4;  
    
    // FirePower
      
    sprintf(temp_string.string, "^ÓÁ:");
    strcat(string_value, temp_string.string);
    
    if(v_firepower == 5)
        sprintf(temp_string.string, "ÒÒÒÒÒ");
    if(v_firepower == 4) 
        sprintf(temp_string.string, "ÒÒÒÒ¡");          
    if(v_firepower == 3) 
        sprintf(temp_string.string, "ÒÒÒ¡¡");          
    if(v_firepower == 2) 
        sprintf(temp_string.string, "ÒÒ¡¡¡");    
    if(v_firepower == 1)
        sprintf(temp_string.string, "Ò¡¡¡¡"); 
        
    strcat(string_value, temp_string.string);
    
    sprintf(temp_string.string, "_+%0.1f^∫—:", firepower);
    strcat(string_value, temp_string.string);    
    
    // FireRate
    
    if(v_firerate == 5)
        sprintf(temp_string.string, "ÒÒÒÒÒ");
    if(v_firerate == 4) 
        sprintf(temp_string.string, "ÒÒÒÒ¡"); 
    if(v_firerate == 3) 
        sprintf(temp_string.string, "ÒÒÒ¡¡");                 
    if(v_firerate == 2) 
        sprintf(temp_string.string, "ÒÒ¡¡¡");    
    if(v_firerate == 1)
        sprintf(temp_string.string, "Ò¡¡¡¡");  
        
    strcat(string_value, temp_string.string);    
    
    sprintf(temp_string.string, "_+%0.2f", firerate);
    strcat(string_value, temp_string.string);   
        
    // ReloadSpeed
      
    sprintf(temp_string.string, "^»÷:");
    strcat(string_value, temp_string.string);
    
    if(v_reload_speed == 5)
        sprintf(temp_string.string, "ÒÒÒÒÒ");
    if(v_reload_speed == 4) 
        sprintf(temp_string.string, "ÒÒÒÒ¡"); 
    if(v_reload_speed == 3) 
        sprintf(temp_string.string, "ÒÒÒ¡¡");                 
    if(v_reload_speed == 2)  
        sprintf(temp_string.string, "ÒÒ¡¡¡");    
    if(v_reload_speed == 1)
        sprintf(temp_string.string, "Ò¡¡¡¡"); 
        
    strcat(string_value, temp_string.string);
    
    sprintf(temp_string.string, "_+%0.2f^ø˙:", reload_speed);
    strcat(string_value, temp_string.string);    
     
    // Capacity
      
    if(v_capacity == 5)
        sprintf(temp_string.string, "ÒÒÒÒÒ");
    if(v_capacity == 4) 
        sprintf(temp_string.string, "ÒÒÒÒ¡"); 
    if(v_capacity == 3) 
        sprintf(temp_string.string, "ÒÒÒ¡¡");                 
    if(v_capacity == 2) 
        sprintf(temp_string.string, "ÒÒ¡¡¡");    
    if(v_capacity == 1)
        sprintf(temp_string.string, "Ò¡¡¡¡");  
        
    strcat(string_value, temp_string.string);    
    
    sprintf(temp_string.string, "_+%0.0f", capacity);
    strcat(string_value, temp_string.string);       
     
    // Special
    if( v_special != 0)
    { 
        
    sprintf(temp_string.string, "^⁄”:");
    strcat(string_value, temp_string.string);
          
    if(v_special == 5) 
        sprintf(temp_string.string, "ÒÒÒÒÒ");
    if(v_special == 4) 
        sprintf(temp_string.string, "ÒÒÒÒ¡"); 
    if(v_special == 3) 
        sprintf(temp_string.string, "ÒÒÒ¡¡");                 
    if(v_special == 2) 
        sprintf(temp_string.string, "ÒÒ¡¡¡");    
    if(v_special == 1)
        sprintf(temp_string.string, "Ò¡¡¡¡");  
        
    strcat(string_value, temp_string.string);    
    
    sprintf(temp_string.string, "_+%0.0f", special);
    strcat(string_value, temp_string.string);       
    
    }            

    strcat(counter[2].word, string_value);      
     
}

void Calculate_Item_Buy(int index1, int item)
{
    int value=0; 
    float check=0.0f; 
    int check1=0;     
    char string_value[128];    
    float defense = 0.0f;
    float defense_base = 0.0f;
    float defense_txt = 0.0f;
    float special  = 0.0f; 
    int v_defense = 0;
    int v_special = 0;

	if(index1 < 0)
		return;
          
    memset(string_value, 0, sizeof(string_value));
            
    if(shop[index1] == SHOP_TINHAT
    || shop[index1] == SHOP_TINHAT_G
    || shop[index1] == SHOP_TINHAT_R
    || shop[index1] == SHOP_TINHAT_L
    || shop[index1] == SHOP_TINHAT_S
    ) 
    { 
        v_defense =    TINHAT_DE_LIMIT; 
        defense   = 0.0f;
        defense_base = TINHAT_DE_BASE;
        if(shop_s[index1] == SHOP_SPECIAL)  
            v_special = TINHAT_SP_LIMIT; 
        
        defense_txt = TINHAT1_BASE_DE; 
            
    }  
            
    if(shop[index1] == SHOP_SHOES
    || shop[index1] == SHOP_SHOES_G
    || shop[index1] == SHOP_SHOES_R
    || shop[index1] == SHOP_SHOES_L
    || shop[index1] == SHOP_SHOES_S
    ) 
    { 
        v_defense =    SHOES_HP_LIMIT; 
        defense   = 0.0f;
        defense_base = SHOES_HP_BASE;
        if(shop_s[index1] == SHOP_SPECIAL)  
            v_special = SHOES_SP_LIMIT; 
        
        defense_txt = SHOES1_BASE_HP; 
            
    } 
    
    counter[2].length = 2;  
    
    // Defense
    if(shop[index1] == SHOP_TINHAT
    || shop[index1] == SHOP_TINHAT_G
    || shop[index1] == SHOP_TINHAT_R
    || shop[index1] == SHOP_TINHAT_L
    || shop[index1] == SHOP_TINHAT_S)       
        sprintf(temp_string.string, "^ÕÛ:");
    
    if(shop[index1] == SHOP_SHOES
    || shop[index1] == SHOP_SHOES_G 
    || shop[index1] == SHOP_SHOES_R
    || shop[index1] == SHOP_SHOES_L
    || shop[index1] == SHOP_SHOES_S)     
        sprintf(temp_string.string, "^·…:");
            
    strcat(string_value, temp_string.string);
    
    if(v_defense == 5)
        sprintf(temp_string.string, "ÒÒÒÒÒ");
    if(v_defense == 4) 
        sprintf(temp_string.string, "ÒÒÒÒ¡");          
    if(v_defense == 3) 
        sprintf(temp_string.string, "ÒÒÒ¡¡");          
    if(v_defense == 2) 
        sprintf(temp_string.string, "ÒÒ¡¡¡");    
    if(v_defense == 1)
        sprintf(temp_string.string, "Ò¡¡¡¡"); 
        
    strcat(string_value, temp_string.string);  
    
    sprintf(temp_string.string, "_+%0.1f", defense_txt);
    strcat(string_value, temp_string.string);    

    // Special
    if( v_special != 0)
    { 
        
    sprintf(temp_string.string, "^⁄”:"); 
    strcat(string_value, temp_string.string);
          
    if(v_special == 5) 
        sprintf(temp_string.string, "ÒÒÒÒÒ");
    if(v_special == 4) 
        sprintf(temp_string.string, "ÒÒÒÒ¡"); 
    if(v_special == 3) 
        sprintf(temp_string.string, "ÒÒÒ¡¡");                 
    if(v_special == 2) 
        sprintf(temp_string.string, "ÒÒ¡¡¡");    
    if(v_special == 1)
        sprintf(temp_string.string, "Ò¡¡¡¡");  
         
    strcat(string_value, temp_string.string);    
    
    sprintf(temp_string.string, "_+%0.0f", special);
    strcat(string_value, temp_string.string);       
    
    }            

    strcat(counter[2].word, string_value);      
     
}

void Calculate_Item_Txt(int index, int item)
{
    int value=0; 
    float check=0.0; 
    int check1=0;     
    char string_value[128];    
    int defense = 0;
    int defense_base = 0;
    float defense_txt = 0;
    int special  = 0;
    int v_defense = 0;
    int v_special = 0;
    int the_modulus = 0;

	if(index < 0) 
		return;
              
    memset(string_value, 0, sizeof(string_value));
     
    value = player_inv[index];  
                
    if(value == INV_HELMET_A || value == INV_HELMET || value == INV_HELMET_E) 
    {
        if(player_inv_value[index] == TINHAT_HEADWEAR 
        || player_inv_value[index] == TINHAT_G_HEADWEAR
        || player_inv_value[index] == TINHAT_R_HEADWEAR
        || player_inv_value[index] == TINHAT_L_HEADWEAR
        || player_inv_value[index] == TINHAT_S_HEADWEAR
        ) 
        {
            defense   = player_inv_value1[index];
            special   = player_inv_value2[index]; 

            defense_txt = GetItemDefense(index);  
                                                                            
            defense_base = TINHAT_DE_BASE;
        
            v_defense = TINHAT_DE_LIMIT;  
 
            v_special = TINHAT_SP_LIMIT; 
        } 
    }  
                
    if(value == INV_BOOT_A || value == INV_BOOT || value == INV_BOOT_E) 
    {
        if(player_inv_value[index] == SHOES_FOOTWEAR 
        || player_inv_value[index] == SHOES_G_FOOTWEAR
        || player_inv_value[index] == SHOES_R_FOOTWEAR
        || player_inv_value[index] == SHOES_L_FOOTWEAR
        || player_inv_value[index] == SHOES_S_FOOTWEAR
        ) 
        {
            defense   = player_inv_value1[index];
            special   = player_inv_value2[index]; 

            defense_txt = GetItemDefense(index);  
                                                                            
            defense_base = SHOES_HP_BASE;
        
            v_defense = SHOES_HP_LIMIT;  
 
            v_special = SHOES_SP_LIMIT; 
        }  
    }  
    
    counter[2].length = 2;  
    
    // Defense
    if(value == INV_HELMET_A || value == INV_HELMET || value == INV_HELMET_E) 
        sprintf(temp_string.string, "^ÕÛ:");
        
    if(value == INV_BOOT_A || value == INV_BOOT || value == INV_BOOT_E) 
        sprintf(temp_string.string, "^·…:");
        
        
    strcat(string_value, temp_string.string);
    
    if(defense == 0)
        sprintf(temp_string.string, "");    
    if(defense == 1)
        sprintf(temp_string.string, "Ì");
    if(defense == 2)
        sprintf(temp_string.string, "ÌÌ");
    if(defense == 3)
        sprintf(temp_string.string, "ÌÌÌ");
    if(defense == 4) 
        sprintf(temp_string.string, "ÌÌÌÌ");                         
    if(defense == 5)
        sprintf(temp_string.string, "ÌÌÌÌÌ"); 
          
    strcat(string_value, temp_string.string);
    v_defense -= defense;
                            
    if(v_defense == 5) 
        sprintf(temp_string.string, "ÒÒÒÒÒ");
    if(v_defense == 4) 
        sprintf(temp_string.string, "ÒÒÒÒ");          
    if(v_defense == 3) 
        sprintf(temp_string.string, "ÒÒÒ");          
    if(v_defense == 2) 
        sprintf(temp_string.string, "ÒÒ");    
    if(v_defense == 1)
        sprintf(temp_string.string, "Ò"); 
    if(v_defense == 0)
        sprintf(temp_string.string, ""); 
                        
    strcat(string_value, temp_string.string);   
    the_modulus = 5 - (v_defense + defense); 
                                 
    if(the_modulus == 5) 
        sprintf(temp_string.string, "¡¡¡¡¡");
    if(the_modulus == 4) 
        sprintf(temp_string.string, "¡¡¡¡");          
    if(the_modulus == 3) 
        sprintf(temp_string.string, "¡¡¡");          
    if(the_modulus == 2) 
        sprintf(temp_string.string, "¡¡");    
    if(the_modulus == 1)
        sprintf(temp_string.string, "¡"); 
    if(the_modulus == 0)
        sprintf(temp_string.string, ""); 
                        
    strcat(string_value, temp_string.string);  
    
    sprintf(temp_string.string, "_+%0.1f", defense_txt );
    strcat(string_value, temp_string.string);    

    // Special
    if( v_special != 0)
    { 
        
    sprintf(temp_string.string, "^⁄”:"); 
    strcat(string_value, temp_string.string);
    
    if(special == 0)
        sprintf(temp_string.string, "");    
    if(special == 1)
        sprintf(temp_string.string, "Ì");
    if(special == 2)
        sprintf(temp_string.string, "ÌÌ");
    if(special == 3)
        sprintf(temp_string.string, "ÌÌÌ");
    if(special == 4) 
        sprintf(temp_string.string, "ÌÌÌÌ");                         
    if(special == 5)
        sprintf(temp_string.string, "ÌÌÌÌÌ"); 
          
    strcat(string_value, temp_string.string);
    v_special -= special;
                            
    if(v_special == 5) 
        sprintf(temp_string.string, "ÒÒÒÒÒ");
    if(v_special == 4) 
        sprintf(temp_string.string, "ÒÒÒÒ");          
    if(v_special == 3) 
        sprintf(temp_string.string, "ÒÒÒ");          
    if(v_special == 2) 
        sprintf(temp_string.string, "ÒÒ");    
    if(v_special == 1)
        sprintf(temp_string.string, "Ò"); 
    if(v_special == 0)
        sprintf(temp_string.string, ""); 
                        
    strcat(string_value, temp_string.string);   
    the_modulus = 5 - (v_special + special); 
                                 
    if(the_modulus == 5) 
        sprintf(temp_string.string, "¡¡¡¡¡");
    if(the_modulus == 4) 
        sprintf(temp_string.string, "¡¡¡¡");          
    if(the_modulus == 3) 
        sprintf(temp_string.string, "¡¡¡");          
    if(the_modulus == 2) 
        sprintf(temp_string.string, "¡¡");    
    if(the_modulus == 1)
        sprintf(temp_string.string, "¡"); 
    if(the_modulus == 0)
        sprintf(temp_string.string, ""); 
                        
    strcat(string_value, temp_string.string);   
    
    sprintf(temp_string.string, "_+%i", special);
    strcat(string_value, temp_string.string);  
    
    }            

    strcat(counter[2].word, string_value);      
     
}

float GetItemDefense(int item)
{
    float success = 0.0;
    int defense = 0;

	if(item < 0)
		return(0);
     
    if(player_inv[item] == INV_HELMET_A || player_inv[item] == INV_HELMET || player_inv[item] == INV_HELMET_E) 
    {
        if(player_inv_value[item] == TINHAT_HEADWEAR
        || player_inv_value[item] == TINHAT_G_HEADWEAR
        || player_inv_value[item] == TINHAT_R_HEADWEAR
        || player_inv_value[item] == TINHAT_L_HEADWEAR
        || player_inv_value[item] == TINHAT_S_HEADWEAR
        )
        {
            defense   = player_inv_value1[item]; 
                            
            if(defense == 0) 
                success = TINHAT1_BASE_DE;   
            if(defense == 1)
                success = TINHAT2_BASE_DE;  
            if(defense == 2)
                success = TINHAT3_BASE_DE;  
            if(defense == 3)
                success = TINHAT4_BASE_DE;  
            if(defense == 4)
                success = TINHAT5_BASE_DE;  
                      
        }
    }
     
    if(player_inv[item] == INV_BOOT_A || player_inv[item] == INV_BOOT || player_inv[item] == INV_BOOT_E) 
    {
        if(player_inv_value[item] == SHOES_FOOTWEAR
        || player_inv_value[item] == SHOES_G_FOOTWEAR
        || player_inv_value[item] == SHOES_R_FOOTWEAR
        || player_inv_value[item] == SHOES_L_FOOTWEAR
        || player_inv_value[item] == SHOES_S_FOOTWEAR
        ) 
        {
            defense   = player_inv_value1[item]; 
                            
            if(defense == 0) 
                success = SHOES1_BASE_HP;   
            if(defense == 1)
                success = SHOES2_BASE_HP;  
            if(defense == 2)
                success = SHOES3_BASE_HP;  
            if(defense == 3)
                success = SHOES4_BASE_HP;  
            if(defense == 4)
                success = SHOES5_BASE_HP;  
                      
        }
    }
       
    return(success);
          
}
