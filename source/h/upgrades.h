
#define WIN32_LEAN_AND_MEAN 
#define WIN32_EXTRA_LEAN 

#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>			// Header File For Standard Input/Output
#include <gl\gl.h> 
#include "globals.h" 

int Tune_Gun(int the_index); 
int GetUpgradesItems(int tune_up_page, int the_bit, int type);
int GetUpgradeSell( int the_gun);
bool Check_For_Super(int loop);

int GetUpgradeSell( int the_gun )
{  
   int the_price =0;  
   int limit_upgrade =0; 
    
	if(the_gun < 0)
		return(0);

    if(player_inv[the_gun] == INV_PISTOL_A)
    {   
        if(player_inv_value[the_gun] == WESTON_PISTOL) 
        {   
            limit_upgrade  = Get_Bit_Shift( the_gun, 1);
              
            if( limit_upgrade >= 1) 
                the_price += SHOP_WESTON_FIREPOWER_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_WESTON_FIREPOWER_UPG2_COST/2;
            if( limit_upgrade >= 3)
                the_price += SHOP_WESTON_FIREPOWER_UPG3_COST/2;
            if( limit_upgrade >= 4)
                the_price += SHOP_WESTON_FIREPOWER_UPG4_COST/2;
            if( limit_upgrade >= 5)
                the_price += SHOP_WESTON_FIREPOWER_UPG5_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 2);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_WESTON_FIRERATE_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_WESTON_FIRERATE_UPG2_COST/2;
                               
            limit_upgrade  = Get_Bit_Shift( the_gun, 3);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_WESTON_RELOAD_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_WESTON_RELOAD_UPG2_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 4);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_WESTON_CAPACITY_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_WESTON_CAPACITY_UPG2_COST/2;
            if( limit_upgrade >= 3)
                the_price += SHOP_WESTON_CAPACITY_UPG3_COST/2;
            if( limit_upgrade >= 4)  
                the_price += SHOP_WESTON_CAPACITY_UPG4_COST/2;
            if( limit_upgrade >= 5)
                the_price += SHOP_WESTON_CAPACITY_UPG5_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 5);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_WESTON_SPECIAL_UPG1_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 6); 
               
            if( limit_upgrade >= 1)
                the_price += SHOP_WESTON_SPECIAL2_UPG1_COST/2;
                                                                
        }    
        
        if(player_inv_value[the_gun] == LUGER_PISTOL) 
        {   
            limit_upgrade  = Get_Bit_Shift( the_gun, 1);
              
            if( limit_upgrade >= 1) 
                the_price += SHOP_LUGER_FIREPOWER_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_LUGER_FIREPOWER_UPG2_COST/2;
            if( limit_upgrade >= 3)
                the_price += SHOP_LUGER_FIREPOWER_UPG3_COST/2;
            if( limit_upgrade >= 4)
                the_price += SHOP_LUGER_FIREPOWER_UPG4_COST/2;
            if( limit_upgrade >= 5)
                the_price += SHOP_LUGER_FIREPOWER_UPG5_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 2);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_LUGER_FIRERATE_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_LUGER_FIRERATE_UPG2_COST/2;
                               
            limit_upgrade  = Get_Bit_Shift( the_gun, 3);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_LUGER_RELOAD_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_LUGER_RELOAD_UPG2_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 4);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_LUGER_CAPACITY_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_LUGER_CAPACITY_UPG2_COST/2;
            if( limit_upgrade >= 3) 
                the_price += SHOP_LUGER_CAPACITY_UPG3_COST/2;
            if( limit_upgrade >= 4)  
                the_price += SHOP_LUGER_CAPACITY_UPG4_COST/2;
            if( limit_upgrade >= 5)
                the_price += SHOP_LUGER_CAPACITY_UPG5_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 5);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_LUGER_SPECIAL_UPG1_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 6); 
               
            if( limit_upgrade >= 1)
                the_price += SHOP_LUGER_SPECIAL2_UPG1_COST/2;
                                                                
        }   
        
        if(player_inv_value[the_gun] == TRAINING_PISTOL) 
        {   
            limit_upgrade  = Get_Bit_Shift( the_gun, 1);
              
            if( limit_upgrade >= 1) 
                the_price += SHOP_TRAINING_FIREPOWER_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_TRAINING_FIREPOWER_UPG2_COST/2;
            if( limit_upgrade >= 3)
                the_price += SHOP_TRAINING_FIREPOWER_UPG3_COST/2;
            if( limit_upgrade >= 4)
                the_price += SHOP_TRAINING_FIREPOWER_UPG4_COST/2;
            if( limit_upgrade >= 5)
                the_price += SHOP_TRAINING_FIREPOWER_UPG5_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 2);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_TRAINING_FIRERATE_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_TRAINING_FIRERATE_UPG2_COST/2;
                               
            limit_upgrade  = Get_Bit_Shift( the_gun, 3);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_TRAINING_RELOAD_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_TRAINING_RELOAD_UPG2_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 4);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_TRAINING_CAPACITY_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_TRAINING_CAPACITY_UPG2_COST/2;
            if( limit_upgrade >= 3) 
                the_price += SHOP_TRAINING_CAPACITY_UPG3_COST/2;
            if( limit_upgrade >= 4)  
                the_price += SHOP_TRAINING_CAPACITY_UPG4_COST/2;
            if( limit_upgrade >= 5)
                the_price += SHOP_TRAINING_CAPACITY_UPG5_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 5);
                
            if( limit_upgrade >= 1)
                the_price += SHOP_TRAINING_SPECIAL_UPG1_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 6); 
               
            if( limit_upgrade >= 1)
                the_price += SHOP_TRAINING_SPECIAL2_UPG1_COST/2;
                                                                
        }                  
        
    }
    
    if(player_inv[the_gun] == INV_MACHINE_A)
    {   
        if(player_inv[the_gun] == INV_MACHINE_A) 
        {   
            limit_upgrade  = Get_Bit_Shift( the_gun, 1);
              
            if( limit_upgrade >= 1) 
                the_price += SHOP_MACHINE_FIREPOWER_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_MACHINE_FIREPOWER_UPG2_COST/2;
            if( limit_upgrade >= 3)
                the_price += SHOP_MACHINE_FIREPOWER_UPG3_COST/2;
            if( limit_upgrade >= 4)
                the_price += SHOP_MACHINE_FIREPOWER_UPG4_COST/2;
            if( limit_upgrade >= 5)
                the_price += SHOP_MACHINE_FIREPOWER_UPG5_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 2);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_MACHINE_FIRERATE_UPG1_COST/2;
                               
            limit_upgrade  = Get_Bit_Shift( the_gun, 3);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_MACHINE_RELOAD_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_MACHINE_RELOAD_UPG2_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 4);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_MACHINE_CAPACITY_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_MACHINE_CAPACITY_UPG2_COST/2;
            if( limit_upgrade >= 3) 
                the_price += SHOP_MACHINE_CAPACITY_UPG3_COST/2;
            if( limit_upgrade >= 4)  
                the_price += SHOP_MACHINE_CAPACITY_UPG4_COST/2;
            if( limit_upgrade >= 5)
                the_price += SHOP_MACHINE_CAPACITY_UPG5_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 5);
                
            if( limit_upgrade >= 1)
                the_price += SHOP_MACHINE_SPECIAL_UPG1_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 6); 
               
            if( limit_upgrade >= 1)
                the_price += SHOP_MACHINE_SPECIAL2_UPG1_COST/2;
                                                                
        }  
   }  
    
    if(player_inv[the_gun] == INV_SHOTGUN_A)
    {   
        if(player_inv_value[the_gun] == FARMERS_SHOTGUN) 
        {   
            limit_upgrade  = Get_Bit_Shift( the_gun, 1);
              
            if( limit_upgrade >= 1) 
                the_price += SHOP_FARMERS_FIREPOWER_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_FARMERS_FIREPOWER_UPG2_COST/2;
            if( limit_upgrade >= 3)
                the_price += SHOP_FARMERS_FIREPOWER_UPG3_COST/2;
            if( limit_upgrade >= 4)
                the_price += SHOP_FARMERS_FIREPOWER_UPG4_COST/2;
            if( limit_upgrade >= 5)
                the_price += SHOP_FARMERS_FIREPOWER_UPG5_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 2);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_FARMERS_FIRERATE_UPG1_COST/2;
                               
            limit_upgrade  = Get_Bit_Shift( the_gun, 3);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_FARMERS_RELOAD_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_FARMERS_RELOAD_UPG2_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 4);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_FARMERS_CAPACITY_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_FARMERS_CAPACITY_UPG2_COST/2;
            if( limit_upgrade >= 3) 
                the_price += SHOP_FARMERS_CAPACITY_UPG3_COST/2;
            if( limit_upgrade >= 4)  
                the_price += SHOP_FARMERS_CAPACITY_UPG4_COST/2;
            if( limit_upgrade >= 5)
                the_price += SHOP_FARMERS_CAPACITY_UPG5_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 5);
                
            if( limit_upgrade >= 1)
                the_price += SHOP_FARMERS_SPECIAL_UPG1_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 6); 
               
            if( limit_upgrade >= 1)
                the_price += SHOP_FARMERS_SPECIAL2_UPG1_COST/2;
                                                                
        }  
        if(player_inv_value[the_gun] == ARMY_SHOTGUN) 
        {   
            limit_upgrade  = Get_Bit_Shift( the_gun, 1);
              
            if( limit_upgrade >= 1) 
                the_price += SHOP_ARMY_FIREPOWER_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_ARMY_FIREPOWER_UPG2_COST/2;
            if( limit_upgrade >= 3)
                the_price += SHOP_ARMY_FIREPOWER_UPG3_COST/2;
            if( limit_upgrade >= 4)
                the_price += SHOP_ARMY_FIREPOWER_UPG4_COST/2;
            if( limit_upgrade >= 5)
                the_price += SHOP_ARMY_FIREPOWER_UPG5_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 2);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_ARMY_FIRERATE_UPG1_COST/2;
                               
            limit_upgrade  = Get_Bit_Shift( the_gun, 3);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_ARMY_RELOAD_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_ARMY_RELOAD_UPG2_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 4);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_ARMY_CAPACITY_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_ARMY_CAPACITY_UPG2_COST/2;
            if( limit_upgrade >= 3) 
                the_price += SHOP_ARMY_CAPACITY_UPG3_COST/2;
            if( limit_upgrade >= 4)  
                the_price += SHOP_ARMY_CAPACITY_UPG4_COST/2;
            if( limit_upgrade >= 5)
                the_price += SHOP_ARMY_CAPACITY_UPG5_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 5);
                
            if( limit_upgrade >= 1)
                the_price += SHOP_ARMY_SPECIAL_UPG1_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 6); 
               
            if( limit_upgrade >= 1)
                the_price += SHOP_ARMY_SPECIAL2_UPG1_COST/2;
                                                                
        }          
   }    
    
    if(player_inv[the_gun] == INV_RIFLE_A)
    {   
        if(player_inv_value[the_gun] == ENFIELD_RIFLE)  
        {   
            limit_upgrade  = Get_Bit_Shift( the_gun, 1);
              
            if( limit_upgrade >= 1)   
                the_price += SHOP_ENFIELD_FIREPOWER_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_ENFIELD_FIREPOWER_UPG2_COST/2;
            if( limit_upgrade >= 3)
                the_price += SHOP_ENFIELD_FIREPOWER_UPG3_COST/2;
            if( limit_upgrade >= 4)
                the_price += SHOP_ENFIELD_FIREPOWER_UPG4_COST/2;
            if( limit_upgrade >= 5)
                the_price += SHOP_ENFIELD_FIREPOWER_UPG5_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 2);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_ENFIELD_FIRERATE_UPG1_COST/2;
                               
            limit_upgrade  = Get_Bit_Shift( the_gun, 3);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_ENFIELD_RELOAD_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_ENFIELD_RELOAD_UPG2_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 4);
               
            if( limit_upgrade >= 1)
                the_price += SHOP_ENFIELD_CAPACITY_UPG1_COST/2;
            if( limit_upgrade >= 2)
                the_price += SHOP_ENFIELD_CAPACITY_UPG2_COST/2;
            if( limit_upgrade >= 3) 
                the_price += SHOP_ENFIELD_CAPACITY_UPG3_COST/2;
            if( limit_upgrade >= 4)  
                the_price += SHOP_ENFIELD_CAPACITY_UPG4_COST/2;
            if( limit_upgrade >= 5)
                the_price += SHOP_ENFIELD_CAPACITY_UPG5_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 5);
                
            if( limit_upgrade >= 1)
                the_price += SHOP_ENFIELD_SPECIAL_UPG1_COST/2;
                
            limit_upgrade  = Get_Bit_Shift( the_gun, 6); 
               
            if( limit_upgrade >= 1)
                the_price += SHOP_ENFIELD_SPECIAL2_UPG1_COST/2;
                                                                
        }  
   }      
   
    
   return(the_price);
    
}

    
int GetUpgrades( int tune_up_page, int the_bit, int type)
{ 
    int success = false;     
    int t_upgrade =0;  
    int limit_upgrade =0;  
    bool has_special=false;
    bool has_super=false;

	if(tune_up_page < 0)
		return(0);
                                                  
    t_upgrade  = Get_Bit_Shift( tune_up_page, the_bit);  // Firepower of this object; 
    
    if(the_bit == 6)      
        has_super = Check_For_Super(tune_up_page);
    
    has_special = true;
     
    if(player_inv[tune_up_page] == INV_MACHINE_A)          
        limit_upgrade  = Get_Bit_Shift_Int( upg_thompson, the_bit);
     
    if(player_inv[tune_up_page] == INV_PISTOL_A)
    {          
        if(player_inv_value[tune_up_page] == WESTON_PISTOL)       
            limit_upgrade  = Get_Bit_Shift_Int( upg_weston, the_bit);
        if(player_inv_value[tune_up_page] == LUGER_PISTOL)       
            limit_upgrade  = Get_Bit_Shift_Int( upg_luger, the_bit);
        if(player_inv_value[tune_up_page] == COLT_PISTOL)       
            limit_upgrade  = Get_Bit_Shift_Int( upg_colt, the_bit); 
        if(player_inv_value[tune_up_page] == COLTK_PISTOL)       
            limit_upgrade  = Get_Bit_Shift_Int( upg_coltk, the_bit); 
        if(player_inv_value[tune_up_page] == TRAINING_PISTOL)       
            limit_upgrade  = Get_Bit_Shift_Int( upg_training, the_bit);                                      
    } 
    if(player_inv[tune_up_page] == INV_RIFLE_A) 
    {   
        if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                  
            limit_upgrade  = Get_Bit_Shift_Int( upg_enfield, the_bit);
        if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                  
            limit_upgrade  = Get_Bit_Shift_Int( upg_hunter, the_bit);
    } 
    if(player_inv[tune_up_page] == INV_SHOTGUN_A) 
    {   
        if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)               
            limit_upgrade  = Get_Bit_Shift_Int( upg_farmers, the_bit);
        if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                  
            limit_upgrade  = Get_Bit_Shift_Int( upg_army, the_bit);
    }                   
          
    ishop = SHOP_NONE;  
    ishop_cost = MAXIMUM_REACHED; 
                          
    // --- FIREPOWER --- // 
    if(the_bit == 1) 
    { 
      
      if(t_upgrade == 0)  
      { 
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^îç-COMPLETE............");  
            strcat(counter[11].word, "^");                             
        }    
        if(t_upgrade < limit_upgrade)  
        {    
            
            strcat(counter[0].word, "^îç-Firepower"); 
            strcat(counter[11].word, "^LVL1");
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                
                ishop = SHOP_MACHINE_FIREPOWER_UPG1;
                ishop_cost= SHOP_MACHINE_FIREPOWER_UPG1_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {                 
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {
                    ishop = SHOP_WESTON_FIREPOWER_UPG1;
                    ishop_cost= SHOP_WESTON_FIREPOWER_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {
                    ishop = SHOP_LUGER_FIREPOWER_UPG1;
                    ishop_cost= SHOP_LUGER_FIREPOWER_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {
                    ishop = SHOP_COLT_FIREPOWER_UPG1; 
                    ishop_cost= SHOP_COLT_FIREPOWER_UPG1_COST;
                }  
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {
                    ishop = SHOP_COLTK_FIREPOWER_UPG1; 
                    ishop_cost= SHOP_COLTK_FIREPOWER_UPG1_COST;
                }    
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                                
                {
                    ishop = SHOP_TRAINING_FIREPOWER_UPG1; 
                    ishop_cost= SHOP_TRAINING_FIREPOWER_UPG1_COST;
                }                                              
           }
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_FIREPOWER_UPG1;
                    ishop_cost= SHOP_ENFIELD_FIREPOWER_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_FIREPOWER_UPG1;
                    ishop_cost= SHOP_HUNTER_FIREPOWER_UPG1_COST;
                }
            }   
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_FIREPOWER_UPG1;
                    ishop_cost= SHOP_FARMERS_FIREPOWER_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_FIREPOWER_UPG1;
                    ishop_cost= SHOP_ARMY_FIREPOWER_UPG1_COST;
                }                
            }                       
        }
      }        
      if(t_upgrade == 1)  
      { 
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^îç-COMPLETE............");  
            strcat(counter[11].word, "^"); 
        }                        
        if(t_upgrade < limit_upgrade) 
        {   
             
            strcat(counter[0].word, "^îç-Firepower");
            strcat(counter[11].word, "^LVL2");                               
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                               
                ishop = SHOP_MACHINE_FIREPOWER_UPG2;
                ishop_cost= SHOP_MACHINE_FIREPOWER_UPG2_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {                
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {
                    ishop = SHOP_WESTON_FIREPOWER_UPG2;
                    ishop_cost= SHOP_WESTON_FIREPOWER_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {
                    ishop = SHOP_LUGER_FIREPOWER_UPG2;
                    ishop_cost= SHOP_LUGER_FIREPOWER_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {
                    ishop = SHOP_COLT_FIREPOWER_UPG2;
                    ishop_cost= SHOP_COLT_FIREPOWER_UPG2_COST;
                }  
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {
                    ishop = SHOP_COLTK_FIREPOWER_UPG2;
                    ishop_cost= SHOP_COLTK_FIREPOWER_UPG2_COST;
                }  
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                                
                {
                    ishop = SHOP_TRAINING_FIREPOWER_UPG2;
                    ishop_cost= SHOP_TRAINING_FIREPOWER_UPG2_COST;
                }                                                     
            } 
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_FIREPOWER_UPG2;
                    ishop_cost= SHOP_ENFIELD_FIREPOWER_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_FIREPOWER_UPG2;
                    ishop_cost= SHOP_HUNTER_FIREPOWER_UPG2_COST;
                }
            }  
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_FIREPOWER_UPG2;
                    ishop_cost= SHOP_FARMERS_FIREPOWER_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_FIREPOWER_UPG2;
                    ishop_cost= SHOP_ARMY_FIREPOWER_UPG2_COST;
                }                
            }                                   
        }
      }  
      if(t_upgrade == 2)  
      {  
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^îç-COMPLETE............");                     
            strcat(counter[11].word, "^");
        }    
        if(t_upgrade < limit_upgrade) 
        {   
                
            strcat(counter[0].word, "^îç-Firepower"); 
            strcat(counter[11].word, "^LVL3");                              
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                                
                ishop = SHOP_MACHINE_FIREPOWER_UPG3;
                ishop_cost= SHOP_MACHINE_FIREPOWER_UPG3_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {                
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {
                    ishop = SHOP_WESTON_FIREPOWER_UPG3;
                    ishop_cost= SHOP_WESTON_FIREPOWER_UPG3_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {
                    ishop = SHOP_LUGER_FIREPOWER_UPG3;
                    ishop_cost= SHOP_LUGER_FIREPOWER_UPG3_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {
                    ishop = SHOP_COLT_FIREPOWER_UPG3;
                    ishop_cost= SHOP_COLT_FIREPOWER_UPG3_COST;
                }  
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {
                    ishop = SHOP_COLTK_FIREPOWER_UPG3;
                    ishop_cost= SHOP_COLTK_FIREPOWER_UPG3_COST;
                }   
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                                
                {
                    ishop = SHOP_TRAINING_FIREPOWER_UPG3;
                    ishop_cost= SHOP_TRAINING_FIREPOWER_UPG3_COST;
                }                                                 
            }  
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_FIREPOWER_UPG3;
                    ishop_cost= SHOP_ENFIELD_FIREPOWER_UPG3_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_FIREPOWER_UPG3;
                    ishop_cost= SHOP_HUNTER_FIREPOWER_UPG3_COST;
                }
            }               
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_FIREPOWER_UPG3;
                    ishop_cost= SHOP_FARMERS_FIREPOWER_UPG3_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_FIREPOWER_UPG3;
                    ishop_cost= SHOP_ARMY_FIREPOWER_UPG3_COST;
                }                
            }                        
        }
      }  
      if(t_upgrade == 3)  
      {  
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^îç-COMPLETE............");                      
            strcat(counter[11].word, "^");
        }
        if(t_upgrade < limit_upgrade) 
        {     
            strcat(counter[0].word, "^îç-Firepower");                               
            strcat(counter[11].word, "^LVL4");
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                             
                ishop = SHOP_MACHINE_FIREPOWER_UPG4;
                ishop_cost= SHOP_MACHINE_FIREPOWER_UPG4_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {                
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {
                    ishop = SHOP_WESTON_FIREPOWER_UPG4;
                    ishop_cost= SHOP_WESTON_FIREPOWER_UPG4_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {
                    ishop = SHOP_LUGER_FIREPOWER_UPG4;
                    ishop_cost= SHOP_LUGER_FIREPOWER_UPG4_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {
                    ishop = SHOP_COLT_FIREPOWER_UPG4;
                    ishop_cost= SHOP_COLT_FIREPOWER_UPG4_COST;
                }      
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {
                    ishop = SHOP_COLTK_FIREPOWER_UPG4;
                    ishop_cost= SHOP_COLTK_FIREPOWER_UPG4_COST;
                }   
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                                
                {
                    ishop = SHOP_TRAINING_FIREPOWER_UPG4;
                    ishop_cost= SHOP_TRAINING_FIREPOWER_UPG4_COST;
                }                                           
            }          
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_FIREPOWER_UPG4;
                    ishop_cost= SHOP_ENFIELD_FIREPOWER_UPG4_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_FIREPOWER_UPG4;
                    ishop_cost= SHOP_HUNTER_FIREPOWER_UPG4_COST;
                }
            }            
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_FIREPOWER_UPG4;
                    ishop_cost= SHOP_FARMERS_FIREPOWER_UPG4_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_FIREPOWER_UPG4;
                    ishop_cost= SHOP_ARMY_FIREPOWER_UPG4_COST;
                }                
            }                 
        }
      }  
      if(t_upgrade >= 4)  
      {  
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^îç-COMPLETE............");                     
            strcat(counter[11].word, "^");
        }    
        if(t_upgrade < limit_upgrade) 
        {     
            strcat(counter[0].word, "^îç-Firepower");                               
            strcat(counter[11].word, "^LVL5");
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                               
                ishop = SHOP_MACHINE_FIREPOWER_UPG5;
                ishop_cost= SHOP_MACHINE_FIREPOWER_UPG5_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {                
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {
                    ishop = SHOP_WESTON_FIREPOWER_UPG5;
                    ishop_cost= SHOP_WESTON_FIREPOWER_UPG5_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {
                    ishop = SHOP_LUGER_FIREPOWER_UPG5;
                    ishop_cost= SHOP_LUGER_FIREPOWER_UPG5_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {
                    ishop = SHOP_COLT_FIREPOWER_UPG5;
                    ishop_cost= SHOP_COLT_FIREPOWER_UPG5_COST;
                }    
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {
                    ishop = SHOP_COLTK_FIREPOWER_UPG5;
                    ishop_cost= SHOP_COLTK_FIREPOWER_UPG5_COST;
                }   
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                                
                {
                    ishop = SHOP_TRAINING_FIREPOWER_UPG5;
                    ishop_cost= SHOP_TRAINING_FIREPOWER_UPG5_COST;
                }                                               
            }           
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_FIREPOWER_UPG5;
                    ishop_cost= SHOP_ENFIELD_FIREPOWER_UPG5_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_FIREPOWER_UPG5;
                    ishop_cost= SHOP_HUNTER_FIREPOWER_UPG5_COST;
                }
            }               
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_FIREPOWER_UPG5;
                    ishop_cost= SHOP_FARMERS_FIREPOWER_UPG5_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_FIREPOWER_UPG5;
                    ishop_cost= SHOP_ARMY_FIREPOWER_UPG5_COST;
                }                
            }             
        }
      }  
    
    } // End of FIREPOWER 
    
    // --- FIRERATE --- // 
    if(the_bit == 2)
    {    
      if(t_upgrade == 0)  
      {  
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^ºÑ-COMPLETE............");
            strcat(counter[11].word, "^");                    
        }
        if(t_upgrade < limit_upgrade) 
        {                           
            strcat(counter[0].word, "^ºÑ-Firerate");  
            strcat(counter[11].word, "^LVL1");
                                         
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                               
                ishop = SHOP_MACHINE_FIRERATE_UPG1;
                ishop_cost= SHOP_MACHINE_FIRERATE_UPG1_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {        
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {                             
                    ishop = SHOP_WESTON_FIRERATE_UPG1;
                    ishop_cost = SHOP_WESTON_FIRERATE_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {                             
                    ishop = SHOP_LUGER_FIRERATE_UPG1;
                    ishop_cost= SHOP_LUGER_FIRERATE_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {                             
                    ishop = SHOP_COLT_FIRERATE_UPG1;
                    ishop_cost= SHOP_COLT_FIRERATE_UPG1_COST;
                }    
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {                             
                    ishop = SHOP_COLTK_FIRERATE_UPG1;
                    ishop_cost= SHOP_COLTK_FIRERATE_UPG1_COST;
                }       
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                                
                {
                    ishop = SHOP_TRAINING_FIRERATE_UPG1;
                    ishop_cost= SHOP_TRAINING_FIRERATE_UPG1_COST;
                }                                            
            }   
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_FIRERATE_UPG1;
                    ishop_cost= SHOP_ENFIELD_FIRERATE_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_FIRERATE_UPG1;
                    ishop_cost= SHOP_HUNTER_FIRERATE_UPG1_COST;
                }
            }      
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_FIRERATE_UPG1;
                    ishop_cost= SHOP_FARMERS_FIRERATE_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_FIRERATE_UPG1;
                    ishop_cost= SHOP_ARMY_FIRERATE_UPG1_COST;
                }                
            }                                  
        }
      }   
      if(t_upgrade == 1)  
      {  
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^ºÑ-COMPLETE............");
            strcat(counter[11].word, "^");                    
        }
        if(t_upgrade < limit_upgrade) 
        {       
            strcat(counter[0].word, "^ºÑ-Firerate");                               
            strcat(counter[11].word, "^LVL2");
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                            
                ishop = SHOP_MACHINE_FIRERATE_UPG1;
                ishop_cost= SHOP_MACHINE_FIRERATE_UPG1_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {        
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {                             
                    ishop = SHOP_WESTON_FIRERATE_UPG2;
                    ishop_cost= SHOP_WESTON_FIRERATE_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {                             
                    ishop = SHOP_LUGER_FIRERATE_UPG2;
                    ishop_cost= SHOP_LUGER_FIRERATE_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {                             
                    ishop = SHOP_COLT_FIRERATE_UPG2;
                    ishop_cost= SHOP_COLT_FIRERATE_UPG2_COST;
                }    
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {                             
                    ishop = SHOP_COLTK_FIRERATE_UPG2;
                    ishop_cost= SHOP_COLTK_FIRERATE_UPG2_COST;
                }           
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                                
                {
                    ishop = SHOP_TRAINING_FIRERATE_UPG2;
                    ishop_cost= SHOP_TRAINING_FIRERATE_UPG2_COST;
                }                                        
            } 
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_FIRERATE_UPG1;
                    ishop_cost= SHOP_ENFIELD_FIRERATE_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_FIRERATE_UPG1;
                    ishop_cost= SHOP_HUNTER_FIRERATE_UPG1_COST;
                }
            }   
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_FIRERATE_UPG1;
                    ishop_cost= SHOP_FARMERS_FIRERATE_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_FIRERATE_UPG1;
                    ishop_cost= SHOP_ARMY_FIRERATE_UPG1_COST;
                }                
            }                                     
        }
      }   
      if(t_upgrade >= 2)  
      {  
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^ºÑ-COMPLETE............");                      
            strcat(counter[11].word, "^");
        }
        if(t_upgrade < limit_upgrade) 
        {          
            strcat(counter[0].word, "^ºÑ-Firerate");                               
            strcat(counter[11].word, "^LVL3");
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                            
                ishop = SHOP_MACHINE_FIRERATE_UPG1;
                ishop_cost= SHOP_MACHINE_FIRERATE_UPG1_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {        
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {                             
                    ishop = SHOP_WESTON_FIRERATE_UPG2;
                    ishop_cost= SHOP_WESTON_FIRERATE_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {                             
                    ishop = SHOP_LUGER_FIRERATE_UPG2;
                    ishop_cost= SHOP_LUGER_FIRERATE_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {                             
                    ishop = SHOP_COLT_FIRERATE_UPG2;
                    ishop_cost= SHOP_COLT_FIRERATE_UPG2_COST;
                }   
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {                             
                    ishop = SHOP_COLTK_FIRERATE_UPG2;
                    ishop_cost= SHOP_COLTK_FIRERATE_UPG2_COST;
                }                      
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                                
                {
                    ishop = SHOP_TRAINING_FIRERATE_UPG2;
                    ishop_cost= SHOP_TRAINING_FIRERATE_UPG2_COST;
                }                             
            }  
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_FIRERATE_UPG1;
                    ishop_cost= SHOP_ENFIELD_FIRERATE_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_FIRERATE_UPG1;
                    ishop_cost= SHOP_HUNTER_FIRERATE_UPG1_COST;
                }
            }    
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_FIRERATE_UPG1;
                    ishop_cost= SHOP_FARMERS_FIRERATE_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_FIRERATE_UPG1;
                    ishop_cost= SHOP_ARMY_FIRERATE_UPG1_COST;
                }                
            }                                     
        }
      }   
    } // End of FIRERATE
    
    // --- RELOADTIME --- // 
    if(the_bit == 3)
    {    
      if(t_upgrade == 0)  
      {  
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^ÈÖ-COMPLETE............");                      
            strcat(counter[11].word, "^");
        }
                              
        if(t_upgrade < limit_upgrade) 
        {    
            strcat(counter[0].word, "^ÈÖ-Reloadtime"); 
            strcat(counter[11].word, "^LVL1");
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                                
                ishop = SHOP_MACHINE_RELOAD_UPG1;
                ishop_cost= SHOP_MACHINE_RELOAD_UPG1_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {        
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {                             
                    ishop = SHOP_WESTON_RELOAD_UPG1;
                    ishop_cost= SHOP_WESTON_RELOAD_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {                             
                    ishop = SHOP_LUGER_RELOAD_UPG1;
                    ishop_cost= SHOP_LUGER_RELOAD_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {                             
                    ishop = SHOP_COLT_RELOAD_UPG1;
                    ishop_cost= SHOP_COLT_RELOAD_UPG1_COST;
                }  
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {                             
                    ishop = SHOP_COLTK_RELOAD_UPG1;
                    ishop_cost= SHOP_COLTK_RELOAD_UPG1_COST;
                }                     
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                                
                {
                    ishop = SHOP_TRAINING_RELOAD_UPG1;
                    ishop_cost= SHOP_TRAINING_RELOAD_UPG1_COST;
                }                                 
            } 
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_RELOAD_UPG1;
                    ishop_cost= SHOP_ENFIELD_RELOAD_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_RELOAD_UPG1;
                    ishop_cost= SHOP_HUNTER_RELOAD_UPG1_COST;
                }
            }     
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_RELOAD_UPG1;
                    ishop_cost= SHOP_FARMERS_RELOAD_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_RELOAD_UPG1;
                    ishop_cost= SHOP_ARMY_RELOAD_UPG1_COST;
                }                
            }                                     
        }
      }     
      if(t_upgrade == 1)   
      {  
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^ÈÖ-COMPLETE............");                       
            strcat(counter[11].word, "^");
        }
        if(t_upgrade < limit_upgrade) 
        {       
            strcat(counter[0].word, "^ÈÖ-Reloadtime");                               
            strcat(counter[11].word, "^LVL2");
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                                
                ishop = SHOP_MACHINE_RELOAD_UPG2;
                ishop_cost= SHOP_MACHINE_RELOAD_UPG2_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {        
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {                             
                    ishop = SHOP_WESTON_RELOAD_UPG2;
                    ishop_cost= SHOP_WESTON_RELOAD_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {                             
                    ishop = SHOP_LUGER_RELOAD_UPG2;
                    ishop_cost= SHOP_LUGER_RELOAD_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {                             
                    ishop = SHOP_COLT_RELOAD_UPG2;
                    ishop_cost= SHOP_COLT_RELOAD_UPG2_COST;
                }   
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {                             
                    ishop = SHOP_COLTK_RELOAD_UPG2;
                    ishop_cost= SHOP_COLTK_RELOAD_UPG2_COST;
                }   
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                                
                {
                    ishop = SHOP_TRAINING_RELOAD_UPG2;
                    ishop_cost= SHOP_TRAINING_RELOAD_UPG2_COST;
                }                                              
            } 
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_RELOAD_UPG2;
                    ishop_cost= SHOP_ENFIELD_RELOAD_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_RELOAD_UPG2;
                    ishop_cost= SHOP_HUNTER_RELOAD_UPG2_COST;
                }
            }      
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_RELOAD_UPG2;
                    ishop_cost= SHOP_FARMERS_RELOAD_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_RELOAD_UPG2;
                    ishop_cost= SHOP_ARMY_RELOAD_UPG2_COST;
                }                
            }                                       
        }
      }          
      if(t_upgrade >= 2)  
      {  
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^ÈÖ-COMPLETE............");                     
            strcat(counter[11].word, "^");
        }
        if(t_upgrade < limit_upgrade) 
        {           
            strcat(counter[0].word, "^ÈÖ-Reloadtime");                               
            strcat(counter[11].word, "^LVL3");
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                                
                ishop = SHOP_MACHINE_RELOAD_UPG2;
                ishop_cost= SHOP_MACHINE_RELOAD_UPG2_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {        
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {                             
                    ishop = SHOP_WESTON_RELOAD_UPG2;
                    ishop_cost= SHOP_WESTON_RELOAD_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {                             
                    ishop = SHOP_LUGER_RELOAD_UPG2;
                    ishop_cost= SHOP_LUGER_RELOAD_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {                             
                    ishop = SHOP_COLT_RELOAD_UPG2;
                    ishop_cost= SHOP_COLT_RELOAD_UPG2_COST;
                }  
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {                             
                    ishop = SHOP_COLTK_RELOAD_UPG2;
                    ishop_cost= SHOP_COLTK_RELOAD_UPG2_COST;
                }                 
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                                
                {
                    ishop = SHOP_TRAINING_RELOAD_UPG2;
                    ishop_cost= SHOP_TRAINING_RELOAD_UPG2_COST;
                }                                   
            }              
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_RELOAD_UPG2;
                    ishop_cost= SHOP_ENFIELD_RELOAD_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_RELOAD_UPG2;
                    ishop_cost= SHOP_HUNTER_RELOAD_UPG2_COST;
                }
            }         
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_RELOAD_UPG2;
                    ishop_cost= SHOP_FARMERS_RELOAD_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_RELOAD_UPG2;
                    ishop_cost= SHOP_ARMY_RELOAD_UPG2_COST;
                }                
            }                      
        }
      }  
                
    } // End of RELOADTIME    
    
    // --- CAPACITY --- // 
    if(the_bit == 4)
    {    
      if(t_upgrade == 0)  
      {  
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^¿ú-COMPLETE............");                     
            strcat(counter[11].word, "^");
        }
        if(t_upgrade < limit_upgrade) 
        {      
            strcat(counter[0].word, "^¿ú-Capacity");                               
            strcat(counter[11].word, "^LVL1");
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                             
                ishop = SHOP_MACHINE_CAPACITY_UPG1;
                ishop_cost= SHOP_MACHINE_CAPACITY_UPG1_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {        
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {                             
                    ishop = SHOP_WESTON_CAPACITY_UPG1;
                    ishop_cost= SHOP_WESTON_CAPACITY_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {                             
                    ishop = SHOP_LUGER_CAPACITY_UPG1;
                    ishop_cost= SHOP_LUGER_CAPACITY_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {                             
                    ishop = SHOP_COLT_CAPACITY_UPG1;
                    ishop_cost= SHOP_COLT_CAPACITY_UPG1_COST;
                }      
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {                             
                    ishop = SHOP_COLTK_CAPACITY_UPG1;
                    ishop_cost= SHOP_COLTK_CAPACITY_UPG1_COST;
                }   
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                     
                {                             
                    ishop = SHOP_TRAINING_CAPACITY_UPG1;
                    ishop_cost= SHOP_TRAINING_CAPACITY_UPG1_COST;
                }                                           
            }   
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_CAPACITY_UPG1;
                    ishop_cost= SHOP_ENFIELD_CAPACITY_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_CAPACITY_UPG1;
                    ishop_cost= SHOP_HUNTER_CAPACITY_UPG1_COST;
                }
            }     
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_CAPACITY_UPG1;
                    ishop_cost= SHOP_FARMERS_CAPACITY_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_CAPACITY_UPG1;
                    ishop_cost= SHOP_ARMY_CAPACITY_UPG1_COST;
                }                
            }                                    
        }
      }    
      if(t_upgrade == 1)  
      {  
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^¿ú-COMPLETE............");                      
            strcat(counter[11].word, "^");
        }
        if(t_upgrade < limit_upgrade) 
        {           
            strcat(counter[0].word, "^¿ú-Capacity");                               
            strcat(counter[11].word, "^LVL2");
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                             
                ishop = SHOP_MACHINE_CAPACITY_UPG2;
                ishop_cost= SHOP_MACHINE_CAPACITY_UPG2_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {        
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {                             
                    ishop = SHOP_WESTON_CAPACITY_UPG2;
                    ishop_cost= SHOP_WESTON_CAPACITY_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {                             
                    ishop = SHOP_LUGER_CAPACITY_UPG2;
                    ishop_cost= SHOP_LUGER_CAPACITY_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {                             
                    ishop = SHOP_COLT_CAPACITY_UPG2;
                    ishop_cost= SHOP_COLT_CAPACITY_UPG2_COST;
                }   
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {                             
                    ishop = SHOP_COLTK_CAPACITY_UPG2;
                    ishop_cost= SHOP_COLTK_CAPACITY_UPG2_COST;
                }    
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                     
                {                             
                    ishop = SHOP_TRAINING_CAPACITY_UPG2;
                    ishop_cost= SHOP_TRAINING_CAPACITY_UPG2_COST;
                }                                                
            }       
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_CAPACITY_UPG2;
                    ishop_cost= SHOP_ENFIELD_CAPACITY_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_CAPACITY_UPG2;
                    ishop_cost= SHOP_HUNTER_CAPACITY_UPG2_COST;
                }
            }      
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_CAPACITY_UPG2;
                    ishop_cost= SHOP_FARMERS_CAPACITY_UPG2_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_CAPACITY_UPG2;
                    ishop_cost= SHOP_ARMY_CAPACITY_UPG2_COST;
                }                
            }                                 
        }
      }         
      if(t_upgrade == 2)  
      {  
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^¿ú-COMPLETE............");                     
            strcat(counter[11].word, "^");
        }
        if(t_upgrade < limit_upgrade) 
        {            
            strcat(counter[0].word, "^¿ú-Capacity");                               
            strcat(counter[11].word, "^LVL3");
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                             
                ishop = SHOP_MACHINE_CAPACITY_UPG3;
                ishop_cost= SHOP_MACHINE_CAPACITY_UPG3_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {        
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {                             
                    ishop = SHOP_WESTON_CAPACITY_UPG3;
                    ishop_cost= SHOP_WESTON_CAPACITY_UPG3_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {                             
                    ishop = SHOP_LUGER_CAPACITY_UPG3;
                    ishop_cost= SHOP_LUGER_CAPACITY_UPG3_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {                             
                    ishop = SHOP_COLT_CAPACITY_UPG3;
                    ishop_cost= SHOP_COLT_CAPACITY_UPG3_COST;
                } 
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {                             
                    ishop = SHOP_COLTK_CAPACITY_UPG3;
                    ishop_cost= SHOP_COLTK_CAPACITY_UPG3_COST;
                }         
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                     
                {                             
                    ishop = SHOP_TRAINING_CAPACITY_UPG3;
                    ishop_cost= SHOP_TRAINING_CAPACITY_UPG3_COST;
                }                                          
            }    
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_CAPACITY_UPG3;
                    ishop_cost= SHOP_ENFIELD_CAPACITY_UPG3_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_CAPACITY_UPG3;
                    ishop_cost= SHOP_HUNTER_CAPACITY_UPG3_COST;
                }
            }                   
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_CAPACITY_UPG3;
                    ishop_cost= SHOP_FARMERS_CAPACITY_UPG3_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_CAPACITY_UPG3;
                    ishop_cost= SHOP_ARMY_CAPACITY_UPG3_COST;
                }                
            }                            
        }
      }         
      if(t_upgrade == 3)  
      {  
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^¿ú-COMPLETE............");                      
            strcat(counter[11].word, "^");
        }
        if(t_upgrade < limit_upgrade) 
        {          
            strcat(counter[0].word, "^¿ú-Capacity");                               
            strcat(counter[11].word, "^LVL4");
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                             
                ishop = SHOP_MACHINE_CAPACITY_UPG4;
                ishop_cost= SHOP_MACHINE_CAPACITY_UPG4_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {        
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {                             
                    ishop = SHOP_WESTON_CAPACITY_UPG4;
                    ishop_cost= SHOP_WESTON_CAPACITY_UPG4_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {                             
                    ishop = SHOP_LUGER_CAPACITY_UPG4;
                    ishop_cost= SHOP_LUGER_CAPACITY_UPG4_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {                             
                    ishop = SHOP_COLT_CAPACITY_UPG4;
                    ishop_cost= SHOP_COLT_CAPACITY_UPG4_COST;
                }       
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {                             
                    ishop = SHOP_COLTK_CAPACITY_UPG4;
                    ishop_cost= SHOP_COLTK_CAPACITY_UPG4_COST;
                }                        
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                     
                {                             
                    ishop = SHOP_TRAINING_CAPACITY_UPG4;
                    ishop_cost= SHOP_TRAINING_CAPACITY_UPG4_COST;
                }                      
            }    
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_CAPACITY_UPG4;
                    ishop_cost= SHOP_ENFIELD_CAPACITY_UPG4_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_CAPACITY_UPG4;
                    ishop_cost= SHOP_HUNTER_CAPACITY_UPG4_COST;
                }
            }          
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_CAPACITY_UPG4;
                    ishop_cost= SHOP_FARMERS_CAPACITY_UPG4_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_CAPACITY_UPG4;
                    ishop_cost= SHOP_ARMY_CAPACITY_UPG4_COST;
                }                
            }                                     
        } 
      }         
      if(t_upgrade >= 4)  
      {  
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[0].word, "^¿ú-COMPLETE............");                      
            strcat(counter[11].word, "^");
        }
        if(t_upgrade < limit_upgrade) 
        {       
            strcat(counter[0].word, "^¿ú-Capacity");                               
            strcat(counter[11].word, "^LVL5");
            
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            {                             
                ishop = SHOP_MACHINE_CAPACITY_UPG5;
                ishop_cost= SHOP_MACHINE_CAPACITY_UPG5_COST;
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {        
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {                             
                    ishop = SHOP_WESTON_CAPACITY_UPG5;
                    ishop_cost= SHOP_WESTON_CAPACITY_UPG5_COST;
                }
                if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {                             
                    ishop = SHOP_LUGER_CAPACITY_UPG5;
                    ishop_cost= SHOP_LUGER_CAPACITY_UPG5_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {                             
                    ishop = SHOP_COLT_CAPACITY_UPG5;
                    ishop_cost= SHOP_COLT_CAPACITY_UPG5_COST;
                }     
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {                             
                    ishop = SHOP_COLTK_CAPACITY_UPG5;
                    ishop_cost= SHOP_COLTK_CAPACITY_UPG5_COST;
                }                       
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                     
                {                             
                    ishop = SHOP_TRAINING_CAPACITY_UPG5;
                    ishop_cost= SHOP_TRAINING_CAPACITY_UPG5_COST;
                }                        
            }     
            if(player_inv[tune_up_page] == INV_RIFLE_A)
            {                
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_CAPACITY_UPG5;
                    ishop_cost= SHOP_ENFIELD_CAPACITY_UPG5_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_CAPACITY_UPG5;
                    ishop_cost= SHOP_HUNTER_CAPACITY_UPG5_COST;
                }
            }                
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {   
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {                             
                    ishop = SHOP_FARMERS_CAPACITY_UPG5;
                    ishop_cost= SHOP_FARMERS_CAPACITY_UPG5_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {                             
                    ishop = SHOP_ARMY_CAPACITY_UPG5;
                    ishop_cost= SHOP_ARMY_CAPACITY_UPG5_COST;
                }                
            }                        
        }
      }   
             
    } // End of CAPACITY       
    
    // --- SPECIAL --- // 
    if(the_bit == 5 && has_special == true)
    {    
      if(t_upgrade == 0 ) 
      {   
                                   
        if(t_upgrade < limit_upgrade) 
        {      
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            { 
                     
                strcat(counter[0].word, "^ÚÓ-Stock...............");  
                
                if(player_inv_value[tune_up_page] == THOMPSOM_MACHINE)                                
                {                                                                                       
                    ishop = SHOP_MACHINE_SPECIAL_UPG1;
                    ishop_cost= SHOP_MACHINE_SPECIAL_UPG1_COST;
                }
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {   
                      
                strcat(counter[0].word, "^ÚÓ-Armour_Piercing.....");                       
                
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {                             
                    ishop = SHOP_WESTON_SPECIAL_UPG1; 
                    ishop_cost= SHOP_WESTON_SPECIAL_UPG1_COST;
                }
              if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {                             
                    ishop = SHOP_LUGER_SPECIAL_UPG1;
                    ishop_cost= SHOP_LUGER_SPECIAL_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {                             
                    ishop = SHOP_COLT_SPECIAL_UPG1;
                    ishop_cost= SHOP_COLT_SPECIAL_UPG1_COST;
                }      
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {                             
                    ishop = SHOP_COLTK_SPECIAL_UPG1;
                    ishop_cost= SHOP_COLTK_SPECIAL_UPG1_COST;
                }    
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                                
                {                             
                    ishop = SHOP_TRAINING_SPECIAL_UPG1;
                    ishop_cost= SHOP_TRAINING_SPECIAL_UPG1_COST;
                }                                     
            }   
          if(player_inv[tune_up_page] == INV_RIFLE_A)
          {              
                     
                strcat(counter[0].word, "^ÚÓ-????................");  
                                             
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_SPECIAL_UPG1;
                    ishop_cost= SHOP_ENFIELD_SPECIAL_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_SPECIAL_UPG1;
                    ishop_cost= SHOP_HUNTER_SPECIAL_UPG1_COST;
                }
            }     
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {    
                                
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {     
                    strcat(counter[0].word, "^ÚÓ-Wide_Shot...........");                                               
                    ishop = SHOP_FARMERS_SPECIAL_UPG1; 
                    ishop_cost= SHOP_FARMERS_SPECIAL_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {         
                    strcat(counter[0].word, "^ÚÓ-Wide_Shot...........");                                               
                    ishop = SHOP_ARMY_SPECIAL_UPG1;
                    ishop_cost= SHOP_ARMY_SPECIAL_UPG1_COST;
                }                
            }                                  
        }
      }    
      if(t_upgrade >= 1)  
      {  
        strcat(counter[0].word, "^ÚÓ-COMPLETE............"); 
          
      }      
            
    } // End of Special       
    
    // --- SPECIAL --- // 
    if(the_bit == 6 && has_super == true)
    {    
      if(t_upgrade == 0 ) 
      {   
                                      
        if(t_upgrade < limit_upgrade) 
        {      
            if(player_inv[tune_up_page] == INV_MACHINE_A)
            { 
                     
                strcat(counter[0].word, "^ÚÓ-Gun_Sight...........");  
                
                if(player_inv_value[tune_up_page] == THOMPSOM_MACHINE)                                
                {                                                                                       
                    ishop = SHOP_MACHINE_SPECIAL2_UPG1;
                    ishop_cost= SHOP_MACHINE_SPECIAL2_UPG1_COST;
                }
            }
            if(player_inv[tune_up_page] == INV_PISTOL_A)
            {   
                      
                strcat(counter[0].word, "^ÚÓ-Unlimited_Ammo......");                       
                
                if(player_inv_value[tune_up_page] == WESTON_PISTOL)                                
                {                             
                    ishop = SHOP_WESTON_SPECIAL2_UPG1; 
                    ishop_cost= SHOP_WESTON_SPECIAL2_UPG1_COST;
                }
              if(player_inv_value[tune_up_page] == LUGER_PISTOL)                                
                {                             
                    ishop = SHOP_LUGER_SPECIAL2_UPG1;
                    ishop_cost= SHOP_LUGER_SPECIAL2_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == COLT_PISTOL)                                
                {                             
                    ishop = SHOP_COLT_SPECIAL2_UPG1;
                    ishop_cost= SHOP_COLT_SPECIAL2_UPG1_COST;
                }      
                if(player_inv_value[tune_up_page] == COLTK_PISTOL)                                
                {                             
                    ishop = SHOP_COLTK_SPECIAL2_UPG1;
                    ishop_cost= SHOP_COLTK_SPECIAL2_UPG1_COST;
                }    
                if(player_inv_value[tune_up_page] == TRAINING_PISTOL)                                
                {                             
                    ishop = SHOP_TRAINING_SPECIAL2_UPG1;
                    ishop_cost= SHOP_TRAINING_SPECIAL2_UPG1_COST;
                }                                     
            }   
          if(player_inv[tune_up_page] == INV_RIFLE_A)
          {              
                     
                strcat(counter[0].word, "^ÚÓ-????................");  
                                             
                if(player_inv_value[tune_up_page] == ENFIELD_RIFLE)                                
                {
                    ishop = SHOP_ENFIELD_SPECIAL2_UPG1;
                    ishop_cost= SHOP_ENFIELD_SPECIAL2_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == HUNTER_RIFLE)                                
                {
                    ishop = SHOP_HUNTER_SPECIAL2_UPG1;
                    ishop_cost= SHOP_HUNTER_SPECIAL2_UPG1_COST;
                }
            }     
            if(player_inv[tune_up_page] == INV_SHOTGUN_A)
            {    
                                
                if(player_inv_value[tune_up_page] == FARMERS_SHOTGUN)                                
                {     
                    strcat(counter[0].word, "^ÚÓ-Double_Barrel.......");                                               
                    ishop = SHOP_FARMERS_SPECIAL2_UPG1; 
                    ishop_cost= SHOP_FARMERS_SPECIAL2_UPG1_COST;
                }
                if(player_inv_value[tune_up_page] == ARMY_SHOTGUN)                                
                {         
                    strcat(counter[0].word, "^ÚÓ-Wide_Shot...........");                                               
                    ishop = SHOP_ARMY_SPECIAL2_UPG1;
                    ishop_cost= SHOP_ARMY_SPECIAL2_UPG1_COST;
                }                
            }                                  
        }
      }    
      if(t_upgrade >= 1)  
      {  
        strcat(counter[0].word, "^ÚÓ-COMPLETE............"); 
          
      }      
            
    } // End of Special    
                    
    if(limit_upgrade != 0)
        success = true;
        
    if(the_bit == 5 && has_special == false)
        success = false;
        
    if(the_bit == 6 && has_super == false)
        success = false;
                        
    return(success);        
    
}

int Tune_Gun(int the_index)
{

	if(the_index < 0)
		return(0);

    // Tin Hat //
    if(shop[the_index] == SHOP_TINHAT_DEFENSE_UPG1)
        player_inv_value1[tune_up_page]=1;
    if(shop[the_index] == SHOP_TINHAT_DEFENSE_UPG2)
        player_inv_value1[tune_up_page]=2;
    if(shop[the_index] == SHOP_TINHAT_DEFENSE_UPG3)
        player_inv_value1[tune_up_page]=3;
    if(shop[the_index] == SHOP_TINHAT_DEFENSE_UPG4)
        player_inv_value1[tune_up_page]=4;
    if(shop[the_index] == SHOP_TINHAT_DEFENSE_UPG5)
        player_inv_value1[tune_up_page]=5;
    if(shop[the_index] == SHOP_TINHAT_DEFENSE_UPG6)
        player_inv_value1[tune_up_page]=6; 
                                           
    if(shop[the_index] == SHOP_TINHAT_SPECIAL_UPG1)
        player_inv_value2[tune_up_page]=1;
        
    // Tin Hat //
    if(shop[the_index] == SHOP_SHOES_HEALTH_UPG1)
        player_inv_value1[tune_up_page]=1;
    if(shop[the_index] == SHOP_SHOES_HEALTH_UPG2)
        player_inv_value1[tune_up_page]=2;
    if(shop[the_index] == SHOP_SHOES_HEALTH_UPG3)
        player_inv_value1[tune_up_page]=3;
    if(shop[the_index] == SHOP_SHOES_HEALTH_UPG4)
        player_inv_value1[tune_up_page]=4;
    if(shop[the_index] == SHOP_SHOES_HEALTH_UPG5)
        player_inv_value1[tune_up_page]=5;
    if(shop[the_index] == SHOP_SHOES_HEALTH_UPG6)
        player_inv_value1[tune_up_page]=6; 
                                           
    if(shop[the_index] == SHOP_SHOES_SPECIAL_UPG1)
        player_inv_value2[tune_up_page]=1; 
                                            
    // Thompson Machinegun //
    if(shop[the_index] == SHOP_MACHINE_FIREPOWER_UPG1)
    {Bit_Shift( tune_up_page, 1, 1);Bit_Shift( tune_up_page+1, 1, 1);}
                        
    if(shop[the_index] == SHOP_MACHINE_FIREPOWER_UPG2) 
    {Bit_Shift( tune_up_page, 1, 2);Bit_Shift( tune_up_page+1, 1, 2);}
                        
    if(shop[the_index] == SHOP_MACHINE_FIREPOWER_UPG3) 
    {Bit_Shift( tune_up_page, 1, 3);Bit_Shift( tune_up_page+1, 1, 3);}
                        
    if(shop[the_index] == SHOP_MACHINE_FIREPOWER_UPG4) 
    {Bit_Shift( tune_up_page, 1, 4);Bit_Shift( tune_up_page+1, 1, 4);}
                        
    if(shop[the_index] == SHOP_MACHINE_FIREPOWER_UPG5) 
    {Bit_Shift( tune_up_page, 1, 5);Bit_Shift( tune_up_page+1, 1, 5);}
    
    if(shop[the_index] == SHOP_MACHINE_FIRERATE_UPG1)  
    {Bit_Shift( tune_up_page, 2, 1);Bit_Shift( tune_up_page+1, 2, 1);}
                            
    if(shop[the_index] == SHOP_MACHINE_RELOAD_UPG1) 
    {Bit_Shift( tune_up_page, 3, 1);Bit_Shift( tune_up_page+1, 3, 1);}
                        
    if(shop[the_index] == SHOP_MACHINE_RELOAD_UPG2) 
    {Bit_Shift( tune_up_page, 3, 2);Bit_Shift( tune_up_page+1, 3, 2);} 
                        
    if(shop[the_index] == SHOP_MACHINE_CAPACITY_UPG1) 
    {Bit_Shift( tune_up_page, 4, 1); Bit_Shift( tune_up_page+1, 4, 1);} 
                        
    if(shop[the_index] == SHOP_MACHINE_CAPACITY_UPG2) 
    {Bit_Shift( tune_up_page, 4, 2);Bit_Shift( tune_up_page+1, 4, 2);} 
                        
    if(shop[the_index] == SHOP_MACHINE_CAPACITY_UPG3) 
    {Bit_Shift( tune_up_page, 4, 3);Bit_Shift( tune_up_page+1, 4, 3);}
     
    if(shop[the_index] == SHOP_MACHINE_CAPACITY_UPG4) 
    {Bit_Shift( tune_up_page, 4, 4);Bit_Shift( tune_up_page+1, 4, 4);} 
                        
    if(shop[the_index] == SHOP_MACHINE_CAPACITY_UPG5) 
    {Bit_Shift( tune_up_page, 4, 5);Bit_Shift( tune_up_page+1, 4, 5);} 
                            
    if(shop[the_index] == SHOP_MACHINE_SPECIAL_UPG1)
    {Bit_Shift( tune_up_page, 5, 1);Bit_Shift( tune_up_page+1, 5, 1);}                         
                            
    if(shop[the_index] == SHOP_MACHINE_SPECIAL2_UPG1)
    {Bit_Shift( tune_up_page, 6, 1);Bit_Shift( tune_up_page+1, 6, 1);}  
                                                    
     // Weston Pistol //
     if(shop[the_index] == SHOP_WESTON_FIREPOWER_UPG1)
         Bit_Shift( tune_up_page, 1, 1);                        

     if(shop[the_index] == SHOP_WESTON_FIREPOWER_UPG2)
         Bit_Shift( tune_up_page, 1, 2); 
                            
     if(shop[the_index] == SHOP_WESTON_FIREPOWER_UPG3)
         Bit_Shift( tune_up_page, 1, 3); 
                            
     if(shop[the_index] == SHOP_WESTON_FIREPOWER_UPG4)
         Bit_Shift( tune_up_page, 1, 4); 
                            
     if(shop[the_index] == SHOP_WESTON_FIREPOWER_UPG5)
         Bit_Shift( tune_up_page, 1, 5);
                             
     if(shop[the_index] == SHOP_WESTON_FIRERATE_UPG1)
         Bit_Shift( tune_up_page, 2, 1);                                                                                                                                           
                             
     if(shop[the_index] == SHOP_WESTON_FIRERATE_UPG2)
         Bit_Shift( tune_up_page, 2, 2);  
                             
     if(shop[the_index] == SHOP_WESTON_RELOAD_UPG1)
         Bit_Shift( tune_up_page, 3, 1);                                                                                                                                           
                             
     if(shop[the_index] == SHOP_WESTON_RELOAD_UPG2)
         Bit_Shift( tune_up_page, 3, 2);                                               
                                             
     if(shop[the_index] == SHOP_WESTON_CAPACITY_UPG1)
         Bit_Shift( tune_up_page, 4, 1);                        

     if(shop[the_index] == SHOP_WESTON_CAPACITY_UPG2)
         Bit_Shift( tune_up_page, 4, 2); 
                            
     if(shop[the_index] == SHOP_WESTON_CAPACITY_UPG3)
         Bit_Shift( tune_up_page, 4, 3); 
                            
     if(shop[the_index] == SHOP_WESTON_CAPACITY_UPG4)
         Bit_Shift( tune_up_page, 4, 4); 
                            
     if(shop[the_index] == SHOP_WESTON_CAPACITY_UPG5)
         Bit_Shift( tune_up_page, 4, 5);    
                            
     if(shop[the_index] == SHOP_WESTON_SPECIAL_UPG1)
         Bit_Shift( tune_up_page, 5, 1);                                                    
                             
     if(shop[the_index] == SHOP_WESTON_SPECIAL2_UPG1)
     {
         Bit_Shift( tune_up_page, 6, 1);   
         player_inv_value2[tune_up_page] = PISTOL6_BASE_CY;
     }
                                                         
     // Colt Pistol //
     if(shop[the_index] == SHOP_COLT_FIREPOWER_UPG1)
         Bit_Shift( tune_up_page, 1, 1);                        

     if(shop[the_index] == SHOP_COLT_FIREPOWER_UPG2)
         Bit_Shift( tune_up_page, 1, 2); 
                            
     if(shop[the_index] == SHOP_COLT_FIREPOWER_UPG3)
         Bit_Shift( tune_up_page, 1, 3); 
                            
     if(shop[the_index] == SHOP_COLT_FIREPOWER_UPG4)
         Bit_Shift( tune_up_page, 1, 4); 
                            
     if(shop[the_index] == SHOP_COLT_FIREPOWER_UPG5)
         Bit_Shift( tune_up_page, 1, 5);
                             
     if(shop[the_index] == SHOP_COLT_FIRERATE_UPG1)
         Bit_Shift( tune_up_page, 2, 1);                                                                                                                                           
                             
     if(shop[the_index] == SHOP_COLT_FIRERATE_UPG2)
         Bit_Shift( tune_up_page, 2, 2);  
                             
     if(shop[the_index] == SHOP_COLT_RELOAD_UPG1)
         Bit_Shift( tune_up_page, 3, 1);                                                                                                                                           
                             
     if(shop[the_index] == SHOP_COLT_RELOAD_UPG2)
         Bit_Shift( tune_up_page, 3, 2);                                               
                                             
     if(shop[the_index] == SHOP_COLT_CAPACITY_UPG1)
         Bit_Shift( tune_up_page, 4, 1);                        

     if(shop[the_index] == SHOP_COLT_CAPACITY_UPG2)
         Bit_Shift( tune_up_page, 4, 2); 
                            
     if(shop[the_index] == SHOP_COLT_CAPACITY_UPG3)
         Bit_Shift( tune_up_page, 4, 3); 
                            
     if(shop[the_index] == SHOP_COLT_CAPACITY_UPG4)
         Bit_Shift( tune_up_page, 4, 4);  
                            
     if(shop[the_index] == SHOP_COLT_CAPACITY_UPG5)
         Bit_Shift( tune_up_page, 4, 5);  
                            
     if(shop[the_index] == SHOP_COLT_SPECIAL_UPG1)
         Bit_Shift( tune_up_page, 5, 1);             
                            
     if(shop[the_index] == SHOP_COLT_SPECIAL2_UPG1)
         Bit_Shift( tune_up_page, 6, 1);   
                           
     // Colt-K Pistol //
     if(shop[the_index] == SHOP_COLTK_FIREPOWER_UPG1)
         Bit_Shift( tune_up_page, 1, 1);                        

     if(shop[the_index] == SHOP_COLTK_FIREPOWER_UPG2)
         Bit_Shift( tune_up_page, 1, 2); 
                            
     if(shop[the_index] == SHOP_COLTK_FIREPOWER_UPG3)
         Bit_Shift( tune_up_page, 1, 3); 
                            
     if(shop[the_index] == SHOP_COLTK_FIREPOWER_UPG4)
         Bit_Shift( tune_up_page, 1, 4); 
                            
     if(shop[the_index] == SHOP_COLTK_FIREPOWER_UPG5)
         Bit_Shift( tune_up_page, 1, 5);
                             
     if(shop[the_index] == SHOP_COLTK_FIRERATE_UPG1)
         Bit_Shift( tune_up_page, 2, 1);                                                                                                                                           
                             
     if(shop[the_index] == SHOP_COLTK_FIRERATE_UPG2)
         Bit_Shift( tune_up_page, 2, 2);  
                             
     if(shop[the_index] == SHOP_COLTK_RELOAD_UPG1)
         Bit_Shift( tune_up_page, 3, 1);                                                                                                                                           
                             
     if(shop[the_index] == SHOP_COLTK_RELOAD_UPG2)
         Bit_Shift( tune_up_page, 3, 2);                                               
                                             
     if(shop[the_index] == SHOP_COLTK_CAPACITY_UPG1)
         Bit_Shift( tune_up_page, 4, 1);                        

     if(shop[the_index] == SHOP_COLTK_CAPACITY_UPG2)
         Bit_Shift( tune_up_page, 4, 2);  
                            
     if(shop[the_index] == SHOP_COLTK_CAPACITY_UPG3)
         Bit_Shift( tune_up_page, 4, 3); 
                            
     if(shop[the_index] == SHOP_COLTK_CAPACITY_UPG4)
         Bit_Shift( tune_up_page, 4, 4);  
                            
     if(shop[the_index] == SHOP_COLTK_CAPACITY_UPG5)
         Bit_Shift( tune_up_page, 4, 5);  
                            
     if(shop[the_index] == SHOP_COLTK_SPECIAL_UPG1)
         Bit_Shift( tune_up_page, 5, 1);                      
                            
     if(shop[the_index] == SHOP_COLTK_SPECIAL2_UPG1)
         Bit_Shift( tune_up_page, 6, 1);   
                      
     // Luger Pistol //
     if(shop[the_index] == SHOP_LUGER_FIREPOWER_UPG1)
         Bit_Shift( tune_up_page, 1, 1);                        

     if(shop[the_index] == SHOP_LUGER_FIREPOWER_UPG2)
         Bit_Shift( tune_up_page, 1, 2); 
                            
     if(shop[the_index] == SHOP_LUGER_FIREPOWER_UPG3)
         Bit_Shift( tune_up_page, 1, 3); 
                            
     if(shop[the_index] == SHOP_LUGER_FIREPOWER_UPG4)
         Bit_Shift( tune_up_page, 1, 4); 
                            
     if(shop[the_index] == SHOP_LUGER_FIREPOWER_UPG5)
         Bit_Shift( tune_up_page, 1, 5);
                             
     if(shop[the_index] == SHOP_LUGER_FIRERATE_UPG1)
         Bit_Shift( tune_up_page, 2, 1);                                                                                                                                           
                             
     if(shop[the_index] == SHOP_LUGER_FIRERATE_UPG2)
         Bit_Shift( tune_up_page, 2, 2);  
                             
     if(shop[the_index] == SHOP_LUGER_RELOAD_UPG1)
         Bit_Shift( tune_up_page, 3, 1);                                                                                                                                           
                             
     if(shop[the_index] == SHOP_LUGER_RELOAD_UPG2)
         Bit_Shift( tune_up_page, 3, 2);                                               
                                             
     if(shop[the_index] == SHOP_LUGER_CAPACITY_UPG1)
         Bit_Shift( tune_up_page, 4, 1);                        

     if(shop[the_index] == SHOP_LUGER_CAPACITY_UPG2)
         Bit_Shift( tune_up_page, 4, 2); 
                            
     if(shop[the_index] == SHOP_LUGER_CAPACITY_UPG3)
         Bit_Shift( tune_up_page, 4, 3); 
                            
     if(shop[the_index] == SHOP_LUGER_CAPACITY_UPG4)
         Bit_Shift( tune_up_page, 4, 4);  
                            
     if(shop[the_index] == SHOP_LUGER_CAPACITY_UPG5)
         Bit_Shift( tune_up_page, 4, 5);   
                            
     if(shop[the_index] == SHOP_LUGER_SPECIAL_UPG1)
         Bit_Shift( tune_up_page, 5, 1);                
                            
     if(shop[the_index] == SHOP_LUGER_SPECIAL2_UPG1)
         Bit_Shift( tune_up_page, 6, 1); 
                                                         
     // Weston Pistol //
     if(shop[the_index] == SHOP_TRAINING_FIREPOWER_UPG1)
         Bit_Shift( tune_up_page, 1, 1);                        

     if(shop[the_index] == SHOP_TRAINING_FIREPOWER_UPG2)
         Bit_Shift( tune_up_page, 1, 2); 
                            
     if(shop[the_index] == SHOP_TRAINING_FIREPOWER_UPG3)
         Bit_Shift( tune_up_page, 1, 3); 
                            
     if(shop[the_index] == SHOP_TRAINING_FIREPOWER_UPG4)
         Bit_Shift( tune_up_page, 1, 4); 
                            
     if(shop[the_index] == SHOP_TRAINING_FIREPOWER_UPG5)
         Bit_Shift( tune_up_page, 1, 5);
                             
     if(shop[the_index] == SHOP_TRAINING_FIRERATE_UPG1)
         Bit_Shift( tune_up_page, 2, 1);                                                                                                                                           
                             
     if(shop[the_index] == SHOP_TRAINING_FIRERATE_UPG2)
         Bit_Shift( tune_up_page, 2, 2);  
                             
     if(shop[the_index] == SHOP_TRAINING_RELOAD_UPG1)
         Bit_Shift( tune_up_page, 3, 1);                                                                                                                                           
                             
     if(shop[the_index] == SHOP_TRAINING_RELOAD_UPG2)
         Bit_Shift( tune_up_page, 3, 2);                                               
                                             
     if(shop[the_index] == SHOP_TRAINING_CAPACITY_UPG1)
         Bit_Shift( tune_up_page, 4, 1);                        

     if(shop[the_index] == SHOP_TRAINING_CAPACITY_UPG2)
         Bit_Shift( tune_up_page, 4, 2); 
                            
     if(shop[the_index] == SHOP_TRAINING_CAPACITY_UPG3)
         Bit_Shift( tune_up_page, 4, 3); 
                            
     if(shop[the_index] == SHOP_TRAINING_CAPACITY_UPG4)
         Bit_Shift( tune_up_page, 4, 4); 
                            
     if(shop[the_index] == SHOP_TRAINING_CAPACITY_UPG5)
         Bit_Shift( tune_up_page, 4, 5);    
                            
     if(shop[the_index] == SHOP_TRAINING_SPECIAL_UPG1)
         Bit_Shift( tune_up_page, 5, 1); 
                            
     if(shop[the_index] == SHOP_TRAINING_SPECIAL2_UPG1)
         Bit_Shift( tune_up_page, 6, 1); 
                                                                                                                        
    // Enfield Rifle //
    if(shop[the_index] == SHOP_ENFIELD_FIREPOWER_UPG1)
    {Bit_Shift( tune_up_page, 1, 1);Bit_Shift( tune_up_page+1, 1, 1);}
                        
    if(shop[the_index] == SHOP_ENFIELD_FIREPOWER_UPG2) 
    {Bit_Shift( tune_up_page, 1, 2);Bit_Shift( tune_up_page+1, 1, 2);}
                        
    if(shop[the_index] == SHOP_ENFIELD_FIREPOWER_UPG3) 
    {Bit_Shift( tune_up_page, 1, 3);Bit_Shift( tune_up_page+1, 1, 3);}
                        
    if(shop[the_index] == SHOP_ENFIELD_FIREPOWER_UPG4) 
    {Bit_Shift( tune_up_page, 1, 4);Bit_Shift( tune_up_page+1, 1, 4);}
                        
    if(shop[the_index] == SHOP_ENFIELD_FIREPOWER_UPG5)  
    {Bit_Shift( tune_up_page, 1, 5);Bit_Shift( tune_up_page+1, 1, 5);}
    
    if(shop[the_index] == SHOP_ENFIELD_FIRERATE_UPG1) 
    {Bit_Shift( tune_up_page, 2, 1);Bit_Shift( tune_up_page+1, 2, 1);}
                            
    if(shop[the_index] == SHOP_ENFIELD_RELOAD_UPG1) 
    {Bit_Shift( tune_up_page, 3, 1);Bit_Shift( tune_up_page+1, 3, 1);}
                        
    if(shop[the_index] == SHOP_ENFIELD_RELOAD_UPG2) 
    {Bit_Shift( tune_up_page, 3, 2);Bit_Shift( tune_up_page+1, 3, 2);} 
                        
    if(shop[the_index] == SHOP_ENFIELD_CAPACITY_UPG1) 
    {Bit_Shift( tune_up_page, 4, 1); Bit_Shift( tune_up_page+1, 4, 1);} 
                        
    if(shop[the_index] == SHOP_ENFIELD_CAPACITY_UPG2) 
    {Bit_Shift( tune_up_page, 4, 2);Bit_Shift( tune_up_page+1, 4, 2);} 
                        
    if(shop[the_index] == SHOP_ENFIELD_CAPACITY_UPG3) 
    {Bit_Shift( tune_up_page, 4, 3);Bit_Shift( tune_up_page+1, 4, 3);}
     
    if(shop[the_index] == SHOP_ENFIELD_CAPACITY_UPG4) 
    {Bit_Shift( tune_up_page, 4, 4);Bit_Shift( tune_up_page+1, 4, 4);} 
                        
    if(shop[the_index] == SHOP_ENFIELD_CAPACITY_UPG5) 
    {Bit_Shift( tune_up_page, 4, 5);Bit_Shift( tune_up_page+1, 4, 5);} 
                            
    if(shop[the_index] == SHOP_ENFIELD_SPECIAL_UPG1)
    {Bit_Shift( tune_up_page, 5, 1);Bit_Shift( tune_up_page+1, 5, 1);}                    
                            
    if(shop[the_index] == SHOP_ENFIELD_SPECIAL2_UPG1)
    {Bit_Shift( tune_up_page, 6, 1);Bit_Shift( tune_up_page+1, 6, 1);}                   
                             
    // Hunter Rifle //
    if(shop[the_index] == SHOP_HUNTER_FIREPOWER_UPG1)
    {Bit_Shift( tune_up_page, 1, 1);Bit_Shift( tune_up_page+1, 1, 1);}
                        
    if(shop[the_index] == SHOP_HUNTER_FIREPOWER_UPG2) 
    {Bit_Shift( tune_up_page, 1, 2);Bit_Shift( tune_up_page+1, 1, 2);}
                        
    if(shop[the_index] == SHOP_HUNTER_FIREPOWER_UPG3) 
    {Bit_Shift( tune_up_page, 1, 3);Bit_Shift( tune_up_page+1, 1, 3);}
                        
    if(shop[the_index] == SHOP_HUNTER_FIREPOWER_UPG4) 
    {Bit_Shift( tune_up_page, 1, 4);Bit_Shift( tune_up_page+1, 1, 4);}
                        
    if(shop[the_index] == SHOP_HUNTER_FIREPOWER_UPG5)  
    {Bit_Shift( tune_up_page, 1, 5);Bit_Shift( tune_up_page+1, 1, 5);}
    
    if(shop[the_index] == SHOP_HUNTER_FIRERATE_UPG1) 
    {Bit_Shift( tune_up_page, 2, 1);Bit_Shift( tune_up_page+1, 2, 1);}
                            
    if(shop[the_index] == SHOP_HUNTER_RELOAD_UPG1) 
    {Bit_Shift( tune_up_page, 3, 1);Bit_Shift( tune_up_page+1, 3, 1);}
                        
    if(shop[the_index] == SHOP_HUNTER_RELOAD_UPG2) 
    {Bit_Shift( tune_up_page, 3, 2);Bit_Shift( tune_up_page+1, 3, 2);} 
                        
    if(shop[the_index] == SHOP_HUNTER_CAPACITY_UPG1) 
    {Bit_Shift( tune_up_page, 4, 1); Bit_Shift( tune_up_page+1, 4, 1);} 
                        
    if(shop[the_index] == SHOP_HUNTER_CAPACITY_UPG2) 
    {Bit_Shift( tune_up_page, 4, 2);Bit_Shift( tune_up_page+1, 4, 2);} 
                        
    if(shop[the_index] == SHOP_HUNTER_CAPACITY_UPG3) 
    {Bit_Shift( tune_up_page, 4, 3);Bit_Shift( tune_up_page+1, 4, 3);}
     
    if(shop[the_index] == SHOP_HUNTER_CAPACITY_UPG4) 
    {Bit_Shift( tune_up_page, 4, 4);Bit_Shift( tune_up_page+1, 4, 4);} 
                        
    if(shop[the_index] == SHOP_HUNTER_CAPACITY_UPG5) 
    {Bit_Shift( tune_up_page, 4, 5);Bit_Shift( tune_up_page+1, 4, 5);} 
                            
    if(shop[the_index] == SHOP_HUNTER_SPECIAL_UPG1)
    {Bit_Shift( tune_up_page, 5, 1);Bit_Shift( tune_up_page+1, 5, 1);}                                      
                            
    if(shop[the_index] == SHOP_HUNTER_SPECIAL2_UPG1)
    {Bit_Shift( tune_up_page, 6, 1);Bit_Shift( tune_up_page+1, 6, 1);}                                                                 
                                                           
    // Farmers Shotgun //
    if(shop[the_index] == SHOP_FARMERS_FIREPOWER_UPG1)
    {Bit_Shift( tune_up_page, 1, 1);Bit_Shift( tune_up_page+1, 1, 1);}
                        
    if(shop[the_index] == SHOP_FARMERS_FIREPOWER_UPG2) 
    {Bit_Shift( tune_up_page, 1, 2);Bit_Shift( tune_up_page+1, 1, 2);}
                        
    if(shop[the_index] == SHOP_FARMERS_FIREPOWER_UPG3) 
    {Bit_Shift( tune_up_page, 1, 3);Bit_Shift( tune_up_page+1, 1, 3);}
                        
    if(shop[the_index] == SHOP_FARMERS_FIREPOWER_UPG4) 
    {Bit_Shift( tune_up_page, 1, 4);Bit_Shift( tune_up_page+1, 1, 4);}
                        
    if(shop[the_index] == SHOP_FARMERS_FIREPOWER_UPG5)  
    {Bit_Shift( tune_up_page, 1, 5);Bit_Shift( tune_up_page+1, 1, 5);}
    
    if(shop[the_index] == SHOP_FARMERS_FIRERATE_UPG1) 
    {Bit_Shift( tune_up_page, 2, 1);Bit_Shift( tune_up_page+1, 2, 1);}
                            
    if(shop[the_index] == SHOP_FARMERS_RELOAD_UPG1) 
    {Bit_Shift( tune_up_page, 3, 1);Bit_Shift( tune_up_page+1, 3, 1);}
                        
    if(shop[the_index] == SHOP_FARMERS_RELOAD_UPG2) 
    {Bit_Shift( tune_up_page, 3, 2);Bit_Shift( tune_up_page+1, 3, 2);} 
                        
    if(shop[the_index] == SHOP_FARMERS_CAPACITY_UPG1) 
    {Bit_Shift( tune_up_page, 4, 1); Bit_Shift( tune_up_page+1, 4, 1);} 
                        
    if(shop[the_index] == SHOP_FARMERS_CAPACITY_UPG2)  
    {Bit_Shift( tune_up_page, 4, 2);Bit_Shift( tune_up_page+1, 4, 2);} 
                        
    if(shop[the_index] == SHOP_FARMERS_CAPACITY_UPG3) 
    {Bit_Shift( tune_up_page, 4, 3);Bit_Shift( tune_up_page+1, 4, 3);}
     
    if(shop[the_index] == SHOP_FARMERS_CAPACITY_UPG4) 
    {Bit_Shift( tune_up_page, 4, 4);Bit_Shift( tune_up_page+1, 4, 4);} 
                        
    if(shop[the_index] == SHOP_FARMERS_CAPACITY_UPG5) 
    {Bit_Shift( tune_up_page, 4, 5);Bit_Shift( tune_up_page+1, 4, 5);}                         
                            
    if(shop[the_index] == SHOP_FARMERS_SPECIAL_UPG1)
    {Bit_Shift( tune_up_page, 5, 1);Bit_Shift( tune_up_page+1, 5, 1);} 
                            
    if(shop[the_index] == SHOP_FARMERS_SPECIAL2_UPG1)
    {Bit_Shift( tune_up_page, 6, 1);Bit_Shift( tune_up_page+1, 6, 1);} 
                            
    // Army Shotgun //
    if(shop[the_index] == SHOP_ARMY_FIREPOWER_UPG1)
    {Bit_Shift( tune_up_page, 1, 1);Bit_Shift( tune_up_page+1, 1, 1);}
                        
    if(shop[the_index] == SHOP_ARMY_FIREPOWER_UPG2) 
    {Bit_Shift( tune_up_page, 1, 2);Bit_Shift( tune_up_page+1, 1, 2);}
                        
    if(shop[the_index] == SHOP_ARMY_FIREPOWER_UPG3) 
    {Bit_Shift( tune_up_page, 1, 3);Bit_Shift( tune_up_page+1, 1, 3);}
                        
    if(shop[the_index] == SHOP_ARMY_FIREPOWER_UPG4) 
    {Bit_Shift( tune_up_page, 1, 4);Bit_Shift( tune_up_page+1, 1, 4);}
                        
    if(shop[the_index] == SHOP_ARMY_FIREPOWER_UPG5)  
    {Bit_Shift( tune_up_page, 1, 5);Bit_Shift( tune_up_page+1, 1, 5);}
    
    if(shop[the_index] == SHOP_ARMY_FIRERATE_UPG1) 
    {Bit_Shift( tune_up_page, 2, 1);Bit_Shift( tune_up_page+1, 2, 1);}
                            
    if(shop[the_index] == SHOP_ARMY_RELOAD_UPG1) 
    {Bit_Shift( tune_up_page, 3, 1);Bit_Shift( tune_up_page+1, 3, 1);}
                        
    if(shop[the_index] == SHOP_ARMY_RELOAD_UPG2) 
    {Bit_Shift( tune_up_page, 3, 2);Bit_Shift( tune_up_page+1, 3, 2);} 
                        
    if(shop[the_index] == SHOP_ARMY_CAPACITY_UPG1)  
    {Bit_Shift( tune_up_page, 4, 1); Bit_Shift( tune_up_page+1, 4, 1);} 
                        
    if(shop[the_index] == SHOP_ARMY_CAPACITY_UPG2)  
    {Bit_Shift( tune_up_page, 4, 2);Bit_Shift( tune_up_page+1, 4, 2);} 
                        
    if(shop[the_index] == SHOP_ARMY_CAPACITY_UPG3) 
    {Bit_Shift( tune_up_page, 4, 3);Bit_Shift( tune_up_page+1, 4, 3);}
     
    if(shop[the_index] == SHOP_ARMY_CAPACITY_UPG4) 
    {Bit_Shift( tune_up_page, 4, 4);Bit_Shift( tune_up_page+1, 4, 4);} 
                        
    if(shop[the_index] == SHOP_ARMY_CAPACITY_UPG5) 
    {Bit_Shift( tune_up_page, 4, 5);Bit_Shift( tune_up_page+1, 4, 5);}                         
                            
    if(shop[the_index] == SHOP_ARMY_SPECIAL_UPG1)
    {Bit_Shift( tune_up_page, 5, 1);Bit_Shift( tune_up_page+1, 5, 1);} 
                            
    if(shop[the_index] == SHOP_ARMY_SPECIAL2_UPG1)
    {Bit_Shift( tune_up_page, 6, 1);Bit_Shift( tune_up_page+1, 6, 1);} 
      

	return(0);
}


int GetUpgradesItems( int tune_up_page, int the_bit, int type)
{ 
    int success = false;      
    int t_upgrade =0;  
    int limit_upgrade =0;  
    bool has_special=false;

	if(tune_up_page < 0)
		return(0);
    
    if(the_bit == 1) 
    if(player_inv[tune_up_page] == INV_HELMET_A || player_inv[tune_up_page] == INV_HELMET_E && the_bit == 1)
    {          
        limit_upgrade  = TINHAT_DE_LIMIT;
        t_upgrade = player_inv_value1[tune_up_page];
    }    
    
    if(the_bit == 2)
    if(player_inv[tune_up_page] == INV_HELMET_A || player_inv[tune_up_page] == INV_HELMET_E && the_bit == 2)          
    {
        limit_upgrade  = TINHAT_SP_LIMIT;
        t_upgrade = player_inv_value2[tune_up_page];
    }             
    
    if(the_bit == 1) 
    if(player_inv[tune_up_page] == INV_BOOT_A || player_inv[tune_up_page] == INV_BOOT_E && the_bit == 1)
    {          
        limit_upgrade  = SHOES_HP_LIMIT;
        t_upgrade = player_inv_value1[tune_up_page];
    }    
    
    if(the_bit == 2)
    if(player_inv[tune_up_page] == INV_BOOT_A || player_inv[tune_up_page] == INV_BOOT_E && the_bit == 2)          
    {
        limit_upgrade  = SHOES_SP_LIMIT;
        t_upgrade = player_inv_value2[tune_up_page];
    }    
        
    ishop = SHOP_NONE;  
    ishop_cost = MAXIMUM_REACHED; 
                          
    // --- DEFENSE --- // 
    if(the_bit == 1)
    { 
      
      if(t_upgrade == 0)  
      { 
                   
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[11].word, "^");         
            if(player_inv[tune_up_page] == INV_HELMET_A)         
                strcat(counter[0].word, "^Íó-COMPLETE............");  
            if(player_inv[tune_up_page] == INV_BOOT_A)         
                strcat(counter[0].word, "^áÉ-COMPLETE............");  
        }                     
          
        if(t_upgrade < limit_upgrade) 
        {     
            strcat(counter[11].word, "^LVL1");                   
            if(player_inv[tune_up_page] == INV_HELMET_A)
            {                            
                strcat(counter[0].word, "^Íó-Defense"); 
                                                                                                    
                ishop = SHOP_TINHAT_DEFENSE_UPG1; 
                ishop_cost= SHOP_TINHAT_DEFENSE_UPG1_COST;
            }
                              
            if(player_inv[tune_up_page] == INV_BOOT_A)
            {                            
                strcat(counter[0].word, "^áÉ-Health");                                                                                      
                ishop = SHOP_SHOES_HEALTH_UPG1; 
                ishop_cost= SHOP_SHOES_HEALTH_UPG1_COST;
            }            
        }  
      } // upgrade == 0  
      
      if(t_upgrade == 1)  
      { 
                   
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[11].word, "^");          
            if(player_inv[tune_up_page] == INV_HELMET_A)         
                strcat(counter[0].word, "^Íó-COMPLETE............");  
            if(player_inv[tune_up_page] == INV_BOOT_A)         
                strcat(counter[0].word, "^áÉ-COMPLETE............");  
        }   
                               
        if(t_upgrade < limit_upgrade) 
        {     
            strcat(counter[11].word, "^LVL2");                 
            if(player_inv[tune_up_page] == INV_HELMET_A)
            {       
                strcat(counter[0].word, "^Íó-Defense");                                               
                ishop = SHOP_TINHAT_DEFENSE_UPG2; 
                ishop_cost= SHOP_TINHAT_DEFENSE_UPG2_COST;
            }
                              
            if(player_inv[tune_up_page] == INV_BOOT_A)
            {                            
                strcat(counter[0].word, "^áÉ-Health");                                                                                      
                ishop = SHOP_SHOES_HEALTH_UPG2; 
                ishop_cost= SHOP_SHOES_HEALTH_UPG2_COST;
            }               
        }  
      } // upgrade == 1  
      
      if(t_upgrade == 2)  
      { 
                   
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[11].word, "^");          
            if(player_inv[tune_up_page] == INV_HELMET_A)         
                strcat(counter[0].word, "^Íó-COMPLETE............");  
            if(player_inv[tune_up_page] == INV_BOOT_A)         
                strcat(counter[0].word, "^áÉ-COMPLETE............");  
        }     
                               
        if(t_upgrade < limit_upgrade) 
        {     
            strcat(counter[11].word, "^LVL3");                  
            if(player_inv[tune_up_page] == INV_HELMET_A)
            {       
                strcat(counter[0].word, "^Íó-Defense");                                              
                ishop = SHOP_TINHAT_DEFENSE_UPG3; 
                ishop_cost= SHOP_TINHAT_DEFENSE_UPG3_COST;
            }
                              
            if(player_inv[tune_up_page] == INV_BOOT_A)
            {                            
                strcat(counter[0].word, "^áÉ-Health");                                                                                      
                ishop = SHOP_SHOES_HEALTH_UPG3; 
                ishop_cost= SHOP_SHOES_HEALTH_UPG3_COST;
            }               
        }  
      } // upgrade == 2  
      
      if(t_upgrade == 3)  
      { 
                   
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[11].word, "^");          
            if(player_inv[tune_up_page] == INV_HELMET_A)         
                strcat(counter[0].word, "^Íó-COMPLETE............");  
            if(player_inv[tune_up_page] == INV_BOOT_A)         
                strcat(counter[0].word, "^áÉ-COMPLETE............");  
        }   
                               
        if(t_upgrade < limit_upgrade) 
        {     
            strcat(counter[11].word, "^LVL4");                   
            if(player_inv[tune_up_page] == INV_HELMET_A)
            {    
                strcat(counter[0].word, "^Íó-Defense");                                             
                ishop = SHOP_TINHAT_DEFENSE_UPG4; 
                ishop_cost= SHOP_TINHAT_DEFENSE_UPG4_COST;
            }
                              
            if(player_inv[tune_up_page] == INV_BOOT_A)
            {                            
                strcat(counter[0].word, "^áÉ-Health");                                                                                      
                ishop = SHOP_SHOES_HEALTH_UPG4; 
                ishop_cost= SHOP_SHOES_HEALTH_UPG4_COST;
            }               
        }  
      } // upgrade == 3  
      
      if(t_upgrade == 4)  
      { 
                   
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[11].word, "^");          
            if(player_inv[tune_up_page] == INV_HELMET_A)         
                strcat(counter[0].word, "^Íó-COMPLETE............");  
            if(player_inv[tune_up_page] == INV_BOOT_A)         
                strcat(counter[0].word, "^áÉ-COMPLETE............");  
        }     
                               
        if(t_upgrade < limit_upgrade) 
        {     
            strcat(counter[11].word, "^LVL5");                  
            if(player_inv[tune_up_page] == INV_HELMET_A)
            {          
                strcat(counter[0].word, "^Íó-Defense");                                              
                ishop = SHOP_TINHAT_DEFENSE_UPG5; 
                ishop_cost= SHOP_TINHAT_DEFENSE_UPG5_COST;
            }
                              
            if(player_inv[tune_up_page] == INV_BOOT_A)
            {                            
                strcat(counter[0].word, "^áÉ-Health");                                                                                      
                ishop = SHOP_SHOES_HEALTH_UPG5; 
                ishop_cost= SHOP_SHOES_HEALTH_UPG5_COST;
            }               
        }  
      } // upgrade == 4  
      
      if(t_upgrade == 5)  
      { 
                   
        if(t_upgrade == limit_upgrade)
        {
            strcat(counter[11].word, "^");          
            if(player_inv[tune_up_page] == INV_HELMET_A)         
                strcat(counter[0].word, "^Íó-COMPLETE............");  
            if(player_inv[tune_up_page] == INV_BOOT_A)         
                strcat(counter[0].word, "^áÉ-COMPLETE............");  
        }   
                               
        if(t_upgrade < limit_upgrade) 
        {     
            strcat(counter[11].word, "^LVL6");                  
            if(player_inv[tune_up_page] == INV_HELMET_A)
            {     
                strcat(counter[0].word, "^Íó-Defense");                                              
                ishop = SHOP_TINHAT_DEFENSE_UPG6; 
                ishop_cost= SHOP_TINHAT_DEFENSE_UPG6_COST;
            }
                              
            if(player_inv[tune_up_page] == INV_BOOT_A)
            {                            
                strcat(counter[0].word, "^áÉ-Health");                                                                                      
                ishop = SHOP_SHOES_HEALTH_UPG6; 
                ishop_cost= SHOP_SHOES_HEALTH_UPG6_COST;
            }                
        }  
      } // upgrade == 5  
                                      
    }  // Defense 
                          
    // --- DEFENSE --- // 
    if(the_bit == 2)
    {  
      
      if(t_upgrade == 0)  
      { 
                    
        if(t_upgrade == limit_upgrade)
            strcat(counter[0].word, "^ÚÓ-COMPLETE............");  
                               
        if(t_upgrade < limit_upgrade)  
        {   
            if(player_inv[tune_up_page] == INV_HELMET_A)
            {
            if(player_inv_value[tune_up_page] == TINHAT_HEADWEAR)   
                strcat(counter[0].word, "^ÚÓ-Frag_Armour........");
            if(player_inv_value[tune_up_page] == TINHAT_G_HEADWEAR)   
                strcat(counter[0].word, "^ÚÓ-Extra_Gold.........");
            if(player_inv_value[tune_up_page] == TINHAT_R_HEADWEAR)   
                strcat(counter[0].word, "^ÚÓ-Barbed_Armour......");
            if(player_inv_value[tune_up_page] == TINHAT_L_HEADWEAR)   
                strcat(counter[0].word, "^ÚÓ-Life_Armour........");
            if(player_inv_value[tune_up_page] == TINHAT_S_HEADWEAR)   
                strcat(counter[0].word, "^ÚÓ-Super_Armour........");
            }   
            
            if(player_inv[tune_up_page] == INV_BOOT_A)
            { 
            if(player_inv_value[tune_up_page] == SHOES_FOOTWEAR)   
                strcat(counter[0].word, "^ÚÓ-Frag_Armour........");
            if(player_inv_value[tune_up_page] == SHOES_G_FOOTWEAR)   
                strcat(counter[0].word, "^ÚÓ-Extra_Gold.........");
            if(player_inv_value[tune_up_page] == SHOES_R_FOOTWEAR)   
                strcat(counter[0].word, "^ÚÓ-Barbed_Armour......");
            if(player_inv_value[tune_up_page] == SHOES_L_FOOTWEAR)   
                strcat(counter[0].word, "^ÚÓ-Life_Armour........");
            if(player_inv_value[tune_up_page] == SHOES_S_FOOTWEAR)   
                strcat(counter[0].word, "^ÚÓ-Super_Armour........");
            }              
            
                                                                                                        
            if(player_inv[tune_up_page] == INV_HELMET_A) 
            {                               
                ishop = SHOP_TINHAT_SPECIAL_UPG1; 
                ishop_cost= SHOP_TINHAT_SPECIAL_UPG1_COST;
            }     
                                                                                                        
            if(player_inv[tune_up_page] == INV_BOOT_A) 
            {                               
                ishop = SHOP_SHOES_SPECIAL_UPG1; 
                ishop_cost= SHOP_SHOES_SPECIAL_UPG1_COST;
            }  
                        
        }  
      } // upgrade == 0  
       
      if(t_upgrade == 1)  
      { 
                   
        if(t_upgrade == limit_upgrade)
            strcat(counter[0].word, "^ÚÓ-COMPLETE............");  

      } // upgrade == 1  
                                            
    }  // Special
                
    if(limit_upgrade != 0)
        success = true;
                
    return(success);        
       
                 
}


bool Check_For_Super(int loop)
{
    bool success=false;    
    int firepower = 0;
    int firerate = 0;
    int reload_speed = 0;
    int capacity = 0;
    int special  = 1;
    int special2 = 0;
    int value=0;  
      
	if(loop < 0)
		return(0);

    value = player_inv_value[loop];  
     
    firepower    = Get_Bit_Shift( loop, 1);  // Firepower of this object;  
    firerate     = Get_Bit_Shift( loop, 2);  // Firerate of this object;  
    reload_speed = Get_Bit_Shift( loop, 3);  // Reload of this object;  
    capacity     = Get_Bit_Shift( loop, 4);  // Capacity of this object;
    special      = Get_Bit_Shift( loop, 5);  // Capacity of this object;
    special2     = Get_Bit_Shift( loop, 6);  // Capacity of this object;
     
    if(player_inv[loop] == INV_SHOTGUN_A || player_inv[loop]  == INV_SHOTGUN_B || player_inv[loop]  == INV_SHOTGUN_E)     
    {   
        
    if(value == FARMERS_SHOTGUN)        
    if(firepower == FARMERS_FP_LIMIT
    && firerate  == FARMERS_FE_LIMIT
    && reload_speed == FARMERS_RD_LIMIT
    && capacity == FARMERS_CY_LIMIT
    && special == FARMERS_SP_LIMIT)
        success = true;

    if(value == ARMY_SHOTGUN)
    if(firepower == ARMY_FP_LIMIT
    && firerate  == ARMY_FE_LIMIT
    && reload_speed == ARMY_RD_LIMIT
    && capacity == ARMY_CY_LIMIT
    && special == ARMY_SP_LIMIT)
        success = true;    
    
    } // Shotguns...
                
    if(player_inv[loop] == INV_MACHINE_A || player_inv[loop]  == INV_MACHINE_B || player_inv[loop]  == INV_MACHINE_E)     
    {   
                    
    if(value == THOMPSOM_MACHINE)         
    if(firepower == MACHINE_FP_LIMIT
    && firerate  == MACHINE_FE_LIMIT
    && reload_speed == MACHINE_RD_LIMIT
    && capacity == MACHINE_CY_LIMIT
    && special == MACHINE_SP_LIMIT)
        success = true;          
        
    } // Machine-guns...          
    
    if(player_inv[loop] == INV_RIFLE_A || player_inv[loop]  == INV_RIFLE_B || player_inv[loop]  == INV_RIFLE_E)     
    {   
                    
    if(value == ENFIELD_RIFLE)
    if(firepower == ENFIELD_FP_LIMIT
    && firerate  == ENFIELD_FE_LIMIT
    && reload_speed == ENFIELD_RD_LIMIT
    && capacity == ENFIELD_CY_LIMIT
    && special == ENFIELD_SP_LIMIT)    
        success = true;   
            
    if(value == HUNTER_RIFLE)
    if(firepower == HUNTER_FP_LIMIT
    && firerate  == HUNTER_FE_LIMIT
    && reload_speed == HUNTER_RD_LIMIT
    && capacity == HUNTER_CY_LIMIT
    && special == HUNTER_SP_LIMIT)            
        success = true;               
            
    if(value == MAUSER_RIFLE)        
    if(firepower == MAUSER_FP_LIMIT
    && firerate  == MAUSER_FE_LIMIT
    && reload_speed == MAUSER_RD_LIMIT
    && capacity == MAUSER_CY_LIMIT
    && special == MAUSER_SP_LIMIT)            
        success = true;              
            
    if(value == MAUSERK_RIFLE)        
    if(firepower == MAUSERK_FP_LIMIT
    && firerate  == MAUSERK_FE_LIMIT
    && reload_speed == MAUSERK_RD_LIMIT
    && capacity == MAUSERK_CY_LIMIT
    && special == MAUSERK_SP_LIMIT)            
        success = true;     
        
    } // Rifles...
              
    if(player_inv[loop] == INV_PISTOL_A || player_inv[loop]  == INV_PISTOL_E) 
    {
                                  
    if(value == WESTON_PISTOL)        
    if(firepower == WESTON_FP_LIMIT
    && firerate  == WESTON_FE_LIMIT
    && reload_speed == WESTON_RD_LIMIT
    && capacity == WESTON_CY_LIMIT
    && special == WESTON_SP_LIMIT)            
        success = true;                
            
    if(value == LUGER_PISTOL)
    if(firepower == LUGER_FP_LIMIT
    && firerate  == LUGER_FE_LIMIT
    && reload_speed == LUGER_RD_LIMIT
    && capacity == LUGER_CY_LIMIT
    && special == LUGER_SP_LIMIT)    
        success = true;       
    
    if(value == COLT_PISTOL) 
    if(firepower == COLT_FP_LIMIT
    && firerate  == COLT_FE_LIMIT
    && reload_speed == COLT_RD_LIMIT
    && capacity == COLT_CY_LIMIT
    && special == COLT_SP_LIMIT)    
        success = true;       
    
    if(value == COLTK_PISTOL)
    if(firepower == COLTK_FP_LIMIT
    && firerate  == COLTK_FE_LIMIT
    && reload_speed == COLTK_RD_LIMIT
    && capacity == COLTK_CY_LIMIT
    && special == COLTK_SP_LIMIT)    
        success = true;  

    if(value == TRAINING_PISTOL)        
    if(firepower == TRAINING_FP_LIMIT
    && firerate  == TRAINING_FE_LIMIT
    && reload_speed == TRAINING_RD_LIMIT
    && capacity == TRAINING_CY_LIMIT
    && special == TRAINING_SP_LIMIT)
        success = true; 
    
    } // Pistols...
    
    
    return(success);
    
}
