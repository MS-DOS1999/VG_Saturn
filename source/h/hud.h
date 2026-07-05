
#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <string.h> 
#include <gl\gl.h>       
#include <math.h>   
#include "globals.h"   

extern void Calculate_Inventory();
extern bool Calculate_Item(int item_value, int item_type, int the_item, int item_value1, int item_value2, int item_value3);
extern void Calculate_Health(int amount, bool share, int index, bool regen);
extern void Calculate_Lifebar(); 
extern void Calculate_Bullets();  
extern void Calculate_Stats(); 
extern void Calculate_Exp(int index, int experience);
extern bool SaveCFG();
extern void Quit_Code(bool quit_active);
extern void Calculate_Buddy(bool turn_on, int slot, int index);
extern void Remove_Item(int item_type, int item_value, int item_value1, bool remove_all);
extern float Get_Weapon_Stats(int the_value, int type);
extern void Remove_Temps(int type);
extern float Calculate_Offset(bool is_a_sprite);
extern void Calculate_Weapon_Buy(int index, int item);
extern float GetItemDefense(int item);
extern bool Check_For_Super(int loop);
extern void Message_Fx();
extern void New_Healthbar(int index, int quick_display);
extern int Get_Health_Amount(int my_amount);
extern void PickUp_Sfx(int type, int value); 

void Calculate_Weapon_Text(int id, int index);
void Reset_Hud_Stat();
void Message_Limits(); 
void Hud_Check();
int  Get_Cost(int id, int pickup);
void Help_Limits();  
void Display_Message(int index, int message);
void Reset_StatGfx();
void Display_Front_Message(int type, int f_rate);
bool Has_This_Item(int type, int value);
int  Grenade_Count();
void Bit_Shift( int the_value1, int bit_to_shift, int bit_value);
int Get_Bit_Shift( int the_value1, int bit_to_shift);
int Bit_Shift_Int( int the_integer, int bit_to_shift, int bit_value);
int Get_Bit_Shift_Int( int the_integer, int bit_to_shift);
bool Grab_Item(int id, bool switching);
bool Dump_Item(int id);

 
void Hud_Overlays() 
{
    float testX=0.0, testY=0.0;
    float tar_X=0.0, tar_Y=0.0; 
    int hud_start=11;   
    int id=0;
    bool level_up=false;
    int index=0;
    int item_cost=0;
//    char string_value[128];  
    bool on_the_inv=false; 
    bool AM = false;
    int new_hours=0;  
	int temp_inv=0; 

    on_hud_buttons=false;

    /*
	if(DX_INV_ACTIVE==false || game_mode != WALK)
	{
		testX = hud_mouseX - (-camX);                           
		testY = hud_mouseY - (-camY);    
	} 
	else 
	{
		#if INCLDUE_360_CONTROLLER == 1
			testX = hud[DXTSI[DX_ROW][DX_CURRENT_TITLE_BUTTON[DX_ROW]]].x + hud[DXTSI[DX_ROW][DX_CURRENT_TITLE_BUTTON[DX_ROW]]].width/2;                        
			testY = hud[DXTSI[DX_ROW][DX_CURRENT_TITLE_BUTTON[DX_ROW]]].y + hud[DXTSI[DX_ROW][DX_CURRENT_TITLE_BUTTON[DX_ROW]]].height/2;  

			DX_mouseX = testX;
			DX_mouseY = testY;
		#endif
	} */

    
           
    if(Level != LVL_SHOP)    
    if(hud[2].alpha == 1.0) 
    { 

        // Sfx Bar 
        if(hud[42].alpha == 1.0 && mouseleft == true || DX_SHOOT == true || DX_INV_LEFTCLICK == true)     
        if(( testX < hud[42].w + hud[42].box_width )   
        &&( testX > hud[42].w)                          
        &&( testY < hud[42].z + hud[42].box_height )
        &&( testY > hud[42].z))   
        {   
            click_sfx = true;
			DX_INV_LEFTCLICK=false;
			DX_SHOOT=false;
            hud[42].width = testX - hud[42].x;
            if(hud[42].box_width != 0.0)
                sfx_volume = hud[42].width / hud[42].box_width;
            
        } 
         
        // Music bar   
        if(hud[43].alpha == 1.0 && mouseleft == true || DX_SHOOT == true || DX_INV_LEFTCLICK == true)            
        if(( testX < hud[43].w + hud[43].box_width )   
        &&( testX > hud[43].w)                          
        &&( testY < hud[43].z + hud[43].box_height )
        &&( testY > hud[43].z))   
        {   
            click_sfx = true;
			DX_INV_LEFTCLICK=false;
			DX_SHOOT = false;
            hud[43].width = testX - hud[43].x;
            if(hud[43].box_width != 0.0)            
                music_volume = hud[43].width / hud[43].box_width;
            update_title = true;

        }                  
    
    }        
     
}


void Calculate_Weapon_Text(int id, int index)
{

     
}

void Reset_Hud_Stat() 
{

                    
}

void Message_Limits()
{

                 
}

void Hud_Check()
{
  
    float widthX  =0.0f, widthX1 =0.0f;
    float heightY =0.0f, heightY1=0.0f; 
    float midX=0.0f, midY=0.0f;   
    int firepower=0;
    int item_cost=0;
    int new_hours=0;
    bool AM=false; 
    
    if(sta2_menu == true)
		return;

    for(int id=0;id<no_fx;id++) 
    if(Fx[id].type == PKU || Fx[id].item_type == INV_MINE) 
	if(DX_INV_ACTIVE==false)
    {  
                    
      fx_offset = Calculate_Offset(false);                         
                  
      midX = Fx[id].width/4;    
      midY = Fx[id].height/4;  
                  
      widthX  = (Fx[id].x + midX) - (fx_offset);          
      heightY = (Fx[id].y + midY) - (fx_offset);  
                                   
      widthX1  = (Fx[id].x + Fx[id].width  - midX) + (fx_offset);    
      heightY1 = (Fx[id].y + Fx[id].height - midY) + (fx_offset);                        
      
	  if(new_counter[2].alpha == 0.0f && new_counter[0].alpha == 0.0f)
      if(( mouseX < widthX1 )                 
      &&( mouseX > widthX)                                            
      &&( mouseY < heightY1 )  
      &&( mouseY > heightY))    
      {          
                 
          counter[5].length = 1;        
       
          if(Fx[id].item_type == INV_GOLD)       
		  {
			  new_counter[2].x = (hud_mouseX - (-camX)) + 0.1f; 
			  new_counter[2].y = (hud_mouseY - (-camY));
              sprintf( new_counter[2].word, "@GOLD :%iG", Fx[id].value); 
			  new_counter[2].alpha = 1.0f; // Ground item text.
		  } 
          if(Fx[id].item_type == INV_AMPUOLE)   
		  {
			  new_counter[2].x = (hud_mouseX - (-camX)) + 0.1f; 
			  new_counter[2].y = (hud_mouseY - (-camY));
              sprintf( new_counter[2].word, "@AMPUOLE +%iHP", Get_Health_Amount(Fx[id].value)); 
			  new_counter[2].alpha = 1.0f; // Ground item text.
		  }
                             
      }
      
    } 
    
    Message_Limits();
    
}

int Get_Cost(int id, int pickup)
{
    int item_cost=0;

    return(item_cost);
}
 
void Help_Limits()
{

}

void Display_Message(int index, int message)
{   
   
     
}

void Reset_StatGfx()
{

}

// ******************************************************************************//
//                                                                               //  
//                                                                               //  
//                           Display_Front_Message                               //
//                                                                               //  
//                                                                               // 
// ******************************************************************************//

void Display_Front_Message(int type, int f_rate)
{

                   
}
 
bool Has_This_Item(int type, int value)
{ 
    
    bool success = false;  
    
    for(int j=0;j<16;j++)          
    if(player_inv[j] == type)
    if(player_inv_value[j] == value || value == -1)    
        success = true;

    return(success);   
   
}

void Bit_Shift( int the_value1, int bit_to_shift, int bit_value)
{
    bool success=false;
    int reset_value=0;
    
	if( the_value1 >= 0)
	{
	
    reset_value = Get_Bit_Shift( the_value1, bit_to_shift);
    
    if(bit_to_shift == 1)
        bit_to_shift = 1;
    if(bit_to_shift == 2)
        bit_to_shift = 10;
    if(bit_to_shift == 3)
        bit_to_shift = 100;
    if(bit_to_shift == 4)
        bit_to_shift = 1000;
    if(bit_to_shift == 5)
        bit_to_shift = 10000;  
    if(bit_to_shift == 6)
        bit_to_shift = 100000;        
 
    player_inv_value1[the_value1] -= reset_value * (bit_to_shift);
     
    if(bit_to_shift == 1)
        bit_to_shift = 1;
    if(bit_to_shift == 2)
        bit_to_shift = 10;
    if(bit_to_shift == 3)
        bit_to_shift = 100;
    if(bit_to_shift == 4)
        bit_to_shift = 1000;
    if(bit_to_shift == 5)
        bit_to_shift = 10000; 
    if(bit_to_shift == 6)
        bit_to_shift = 100000;        
 
    player_inv_value1[the_value1] += bit_value * (bit_to_shift);

	} // the_value1 >= 0
  
}

int Get_Bit_Shift( int the_value1, int bit_to_shift)
{
    int success=false;
    
    if(bit_to_shift == 1)
        bit_to_shift = 1;
    if(bit_to_shift == 2)
        bit_to_shift = 10;
    if(bit_to_shift == 3)
        bit_to_shift = 100;
    if(bit_to_shift == 4)
        bit_to_shift = 1000;
    if(bit_to_shift == 5)
        bit_to_shift = 10000; 
    if(bit_to_shift == 6)
        bit_to_shift = 100000;
    
	if( the_value1 >= 0 && bit_to_shift > 0)                
        success = (player_inv_value1[the_value1] / bit_to_shift ) % 10;
    
    return(success);
     
}
int Bit_Shift_Int( int the_integer, int bit_to_shift, int bit_value)
{
    bool success=false;
    int reset_value=0;
    
    reset_value = Get_Bit_Shift_Int( the_integer, bit_to_shift);
    
    if(bit_to_shift == 1)
        bit_to_shift = 1;
    if(bit_to_shift == 2) 
        bit_to_shift = 10;
    if(bit_to_shift == 3)
        bit_to_shift = 100;
    if(bit_to_shift == 4)
        bit_to_shift = 1000; 
    if(bit_to_shift == 5)
        bit_to_shift = 10000;  
    if(bit_to_shift == 6)
        bit_to_shift = 100000;        
 
    the_integer -= reset_value * (bit_to_shift);
     
    if(bit_to_shift == 1)
        bit_to_shift = 1;
    if(bit_to_shift == 2)
        bit_to_shift = 10;
    if(bit_to_shift == 3)
        bit_to_shift = 100;
    if(bit_to_shift == 4)
        bit_to_shift = 1000;
    if(bit_to_shift == 5)
        bit_to_shift = 10000; 
    if(bit_to_shift == 6)
        bit_to_shift = 100000;        
    
    the_integer += bit_value * (bit_to_shift);
    
    return(the_integer);
  
}

int Get_Bit_Shift_Int( int the_integer, int bit_to_shift)
{
    int success=false;
    
    if(bit_to_shift == 1)
        bit_to_shift = 1;
    if(bit_to_shift == 2)
        bit_to_shift = 10;
    if(bit_to_shift == 3)
        bit_to_shift = 100;
    if(bit_to_shift == 4)
        bit_to_shift = 1000;
    if(bit_to_shift == 5)
        bit_to_shift = 10000; 
    if(bit_to_shift == 6)
        bit_to_shift = 100000;
                    
	if( bit_to_shift > 0)
    success = (the_integer / bit_to_shift ) % 10;
    
    return(success);
    
}

bool Grab_Item(int id, bool switching)
{

	return 0;

}
bool Dump_Item(int id)
{

	
	return 0;
}
