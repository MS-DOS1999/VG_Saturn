
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN 

#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>			// Header File For Standard Input/Output
#include <gl\gl.h> 
#include "globals.h" 

#define RIFLE1_BASE_FP_RANDOM  15 
#define PISTOL1_BASE_FP_RANDOM 15   
#define ENEMY_BASE_FP_RANDOM   10
#define ENEMY_BASE_FP_RANDOM_HARD  15

#define BONUS_NONE          0
#define BONUS_FIREPOWER     1
#define BONUS_FIRERATE      2
#define BONUS_RELOAD        3 
#define BONUS_CAPACITY      4
#define BONUS_FIRE          5
#define BONUS_GAS           6

#define FARMERS_SHOTGUN   0
#define FARMERS_SHOTGUN_COST   550
#define FARMERS_SHOTGUN_ADD   10

#define ARMY_SHOTGUN        1
#define ARMY_SHOTGUN_COST    1500
#define ARMY_SHOTGUN_ADD    12

#define BLACK_GRENADE   0
#define BLACK_GRENADE_COST   10
#define BLACK_GRENADE_ADD   1

#define THOMPSOM_MACHINE   0
#define THOMPSOM_MACHINE_COST   550
#define THOMPSOM_MACHINE_ADD   10
  
#define FARMERS_RIFLE   0
#define HUNTER_RIFLE    1
#define ENFIELD_RIFLE   2
#define ENFIELDK_RIFLE  3
#define MAUSER_RIFLE    4
#define MAUSERK_RIFLE   5
#define CARBINE_RIFLE   6  
#define CARBINEK_RIFLE  7
#define GEWEHR_RIFLE    8
#define GEWEHRK_RIFLE   9
#define HEINRICH_RIFLE  10
#define HEINRICHK_RIFLE  11
#define WINCHESTER_RIFLE   12


#define TRAINING_PISTOL   0
#define WEBLEY_PISTOL     1
#define LUGER_PISTOL      2
#define LUGERK_PISTOL     3
#define WESTON_PISTOL     4
#define WESTONK_PISTOL    5
#define MAUSER_PISTOL     6
#define MAUSERK_PISTOL    7
#define COLT_PISTOL       8 
#define COLTK_PISTOL      9 
#define SAVAGE_PISTOL     10
#define SAVAGEK_PISTOL    11
#define NAVYCOLT_PISTOL    12

 
// Basic Machinegun
#define MACHINE1_BASE_FP    3 // 1.0   
#define MACHINE2_BASE_FP    0.7 // 1.0   
#define MACHINE3_BASE_FP    0.8 // 1.0   
#define MACHINE4_BASE_FP    0.9 // 1.0   
#define MACHINE5_BASE_FP    1.0 // 1.0   
#define MACHINE6_BASE_FP    1.2 // 1.0   

#define MACHINE1_BASE_FE    0.13 // 0.4
#define MACHINE2_BASE_FE    0.12 // 0.4
  
#define MACHINE1_BASE_RD    2.37// 2.0   
#define MACHINE2_BASE_RD    2.03 // 2.0  
#define MACHINE3_BASE_RD    1.57 // 2.0  

#define MACHINE1_BASE_CY   30   // 8
#define MACHINE2_BASE_CY   50   // 8   
#define MACHINE3_BASE_CY   70  // 8
#define MACHINE4_BASE_CY   90  // 8
#define MACHINE5_BASE_CY   120  // 8
#define MACHINE6_BASE_CY   150  // 8

#if INFINITE_PISTOL == 0


#define SNIPER1_BASE_FP    30  // 1.0    

// Basic Rifle 
#define RIFLE1_BASE_FP    20  // 1.0        
#define RIFLE2_BASE_FP    60  // 1.0    
#define RIFLE3_BASE_FP    80  // 1.0   
#define RIFLE4_BASE_FP    100 // 1.0     
#define RIFLE5_BASE_FP    120 // 1.0    
#define RIFLE6_BASE_FP    140 // 1.0     
#define RIFLE7_BASE_FP    160 // 1.0     
#define RIFLE8_BASE_FP    180 // 1.0    
#define RIFLE9_BASE_FP    200 // 1.0    
#define RIFLE10_BASE_FP   80 // 1.0       
#define RIFLE11_BASE_FP   85 // 1.0   
#define RIFLE12_BASE_FP   90 // 1.0      
#define RIFLE13_BASE_FP   95 // 1.0  
#endif

#if INFINITE_PISTOL == 1 
// Basic Rifle 
#define RIFLE1_BASE_FP    2.4 // 1.0        
#define RIFLE2_BASE_FP    2.7 // 1.0    
#define RIFLE3_BASE_FP    3.0 // 1.0    
#define RIFLE4_BASE_FP    3.4 // 1.0     
#define RIFLE5_BASE_FP    3.8 // 1.0    
#define RIFLE6_BASE_FP    4.2 // 1.0     
#define RIFLE7_BASE_FP    4.6 // 1.0     
#define RIFLE8_BASE_FP    4.8 // 1.0    
#define RIFLE9_BASE_FP    5.2 // 1.0    
#define RIFLE10_BASE_FP   5.5 // 1.0       
#define RIFLE11_BASE_FP   6.0 // 1.0   
#define RIFLE12_BASE_FP   7.0 // 1.0      
#define RIFLE13_BASE_FP  12.0 // 1.0  
#endif
    
// Basic Pistol       
#define PISTOL1_BASE_FP    5  // 1.0   
#define PISTOL2_BASE_FP    20  // 1.0 
#define PISTOL3_BASE_FP    25  // 1.0   
#define PISTOL4_BASE_FP    30  // 1.0  
#define PISTOL5_BASE_FP    35  // 1.0    
#define PISTOL6_BASE_FP    40  // 1.0 
#define PISTOL7_BASE_FP    45  // 1.0  
#define PISTOL8_BASE_FP    50  // 1.0  
#define PISTOL9_BASE_FP    55  // 1.0   
#define PISTOL10_BASE_FP   60  // 1.0  
#define PISTOL11_BASE_FP   65  // 1.0 
#define PISTOL12_BASE_FP   70  // 1.0 
#define PISTOL13_BASE_FP   75  // 1.0  

// Basic Shotgun
#define SHOTGUN1_BASE_FP    24 // 1.0   
#define SHOTGUN2_BASE_FP    2.6 // 1.0    
#define SHOTGUN3_BASE_FP    2.8 // 1.0   
#define SHOTGUN4_BASE_FP    3.2 // 1.0    
#define SHOTGUN5_BASE_FP    3.4 // 1.0    
#define SHOTGUN6_BASE_FP    3.6 // 1.0   
#define SHOTGUN7_BASE_FP    4.0 // 1.0   
#define SHOTGUN8_BASE_FP    4.4 // 1.0    
#define SHOTGUN9_BASE_FP    4.6 // 1.0   
#define SHOTGUN10_BASE_FP   5.0 // 1.0   
#define SHOTGUN11_BASE_FP   5.2 // 1.0   
#define SHOTGUN12_BASE_FP   5.6 // 1.0   
#define SHOTGUN13_BASE_FP   9.0 // 1.0   



// Basic Pistol  
#define GRENADE1_BASE_FP   25.0 // 1.0      
#define GRENADE2_BASE_FP   50.0 // 1.0    
#define GRENADE3_BASE_FP   60.0 // 1.0 
#define GRENADE4_BASE_FP   24.0 // 1.0   
#define GRENADE5_BASE_FP   30.0 // 1.0   
#define GRENADE6_BASE_FP   35.0 // 1.0  
#define GRENADE7_BASE_FP   35.0 // 1.0  
#define GRENADE8_BASE_FP   35.0 // 1.0  
#define GRENADE9_BASE_FP   35.0 // 1.0  
#define GRENADE10_BASE_FP   35.0 // 1.0  
#define GRENADE11_BASE_FP   35.0 // 1.0  
#define GRENADE12_BASE_FP   35.0 // 1.0  


#define RIFLE1_BASE_FE    0.33  // 0.4
#define RIFLE2_BASE_FE    0.33  // 0.4
   
#define RIFLE1_BASE_RD    1.6  // 2.0  
#define RIFLE2_BASE_RD    1.6  // 2.0    
#define RIFLE3_BASE_RD    1.6  // 2.0  
 
#define RIFLE1_BASE_CY    8   // 8
#define RIFLE2_BASE_CY    8   // 8    
#define RIFLE3_BASE_CY    8   // 8  
#define RIFLE4_BASE_CY    8   // 8   
#define RIFLE5_BASE_CY    8   // 8
#define RIFLE6_BASE_CY    8   // 8

     
#define PISTOL1_BASE_RD    1.1  // 2.0    
#define PISTOL2_BASE_RD    1.1  // 2.0       
#define PISTOL3_BASE_RD    1.1  // 2.0     

#define PISTOL1_BASE_FE    0.25   // 0.4  
#define PISTOL2_BASE_FE    0.25   // 0.4
#define PISTOL3_BASE_FE    0.25   // 0.4

#define PISTOL1_BASE_CY    12   // 8   
#define PISTOL2_BASE_CY    12   // 8
#define PISTOL3_BASE_CY    12   // 8 
#define PISTOL4_BASE_CY    12   // 8
#define PISTOL5_BASE_CY    12   // 8
#define PISTOL6_BASE_CY    12   // 8

// Basic Rifle
#define HUNTER1_BASE_FP    1.2  // 1.0   
#define HUNTER2_BASE_FP    1.2  // 1.0   
#define HUNTER3_BASE_FP    1.2  // 1.0   
#define HUNTER4_BASE_FP    1.2  // 1.0   
#define HUNTER5_BASE_FP    1.2  // 1.0   
#define HUNTER6_BASE_FP    1.2  // 1.0   

#define HUNTER1_BASE_FE    0.4 // 0.4
#define HUNTER2_BASE_FE    0.4 // 0.4
  
#define HUNTER1_BASE_RD    1.6 // 2.0   
#define HUNTER2_BASE_RD    1.6 // 2.0  
#define HUNTER3_BASE_RD    1.6 // 2.0  

#define HUNTER1_BASE_CY   8   // 8 
#define HUNTER2_BASE_CY   8   // 8   
#define HUNTER3_BASE_CY   8   // 8
#define HUNTER4_BASE_CY   8   // 8      
#define HUNTER5_BASE_CY   8   // 8
#define HUNTER6_BASE_CY   8   // 8
 
 
#define SHOTGUN1_BASE_FE    0.53 // 0.4
#define SHOTGUN2_BASE_FE    0.53 // 0.4  
  
#define SHOTGUN1_BASE_RD    1.33 // 2.0  
#define SHOTGUN2_BASE_RD    1.33 // 2.0   
#define SHOTGUN3_BASE_RD    1.33 // 2.0  

#define SHOTGUN1_BASE_CY    8   // 8
#define SHOTGUN2_BASE_CY    8   // 8   
#define SHOTGUN3_BASE_CY    8   // 8
#define SHOTGUN4_BASE_CY    8   // 8
#define SHOTGUN5_BASE_CY    8  // 8
#define SHOTGUN6_BASE_CY    8  // 8

// Army Shotgun
#define ARMY1_BASE_FP    5.0 // 1.0   
#define ARMY2_BASE_FP    5.5 // 1.0   
#define ARMY3_BASE_FP    6.0 // 1.0   
#define ARMY4_BASE_FP    6.5 // 1.0   
#define ARMY5_BASE_FP    7.0 // 1.0   
#define ARMY6_BASE_FP    8.0 // 1.0    

#define ARMY1_BASE_FE    0.63 // 0.4 
#define ARMY2_BASE_FE    0.43 // 0.4 
  
#define ARMY1_BASE_RD    3.03 // 2.0  
#define ARMY2_BASE_RD    2.43 // 2.0  
#define ARMY3_BASE_RD    1.50 // 2.0  

#define ARMY1_BASE_CY    7   // 8
#define ARMY2_BASE_CY    9   // 8   
#define ARMY3_BASE_CY   11   // 8  
#define ARMY4_BASE_CY   13   // 8 
#define ARMY5_BASE_CY   15   // 8  
#define ARMY6_BASE_CY   20   // 8


    
// Basic Pistol       
#define LUGER1_BASE_FP    0.9  // 1.0 
#define LUGER2_BASE_FP    0.9  // 1.0 
#define LUGER3_BASE_FP    0.9  // 1.0  
#define LUGER4_BASE_FP    0.9  // 1.0  
#define LUGER5_BASE_FP    0.9  // 1.0 
#define LUGER6_BASE_FP    0.9  // 1.0 
    
#define LUGER1_BASE_RD    1.1 // 2.0    
#define LUGER2_BASE_RD    1.1 // 2.0    
#define LUGER3_BASE_RD    1.1 // 2.0    

#define LUGER1_BASE_FE    0.28  // 0.4 
#define LUGER2_BASE_FE    0.28  // 0.4
#define LUGER3_BASE_FE    0.28  // 0.4

#define LUGER1_BASE_CY    12   // 8 
#define LUGER2_BASE_CY    12   // 8 
#define LUGER3_BASE_CY    12   // 8
#define LUGER4_BASE_CY    12   // 8
#define LUGER5_BASE_CY    12   // 8
#define LUGER6_BASE_CY    12   // 8
    
// Colt Pistol       
#define COLT1_BASE_FP    1.6  // 1.0 
#define COLT2_BASE_FP    1.8  // 1.0 
#define COLT3_BASE_FP    2.0  // 1.0 
#define COLT4_BASE_FP    2.3  // 1.0 
#define COLT5_BASE_FP    2.7  // 1.0 
#define COLT6_BASE_FP    3.0  // 1.0 
    
#define COLT1_BASE_RD    1.70 // 2.0    
#define COLT2_BASE_RD    1.47 // 2.0    
#define COLT3_BASE_RD    0.83 // 2.0    

#define COLT1_BASE_FE    0.47  // 0.4
#define COLT2_BASE_FE    0.40  // 0.4
#define COLT3_BASE_FE    0.27  // 0.4

#define COLT1_BASE_CY    15   // 8 
#define COLT2_BASE_CY    18   // 8 
#define COLT3_BASE_CY    21   // 8
#define COLT4_BASE_CY    25   // 8
#define COLT5_BASE_CY    30   // 8
#define COLT6_BASE_CY    35   // 8
    
// Colt Pistol       
#define COLTK1_BASE_FP    0.9  // 1.0 
#define COLTK2_BASE_FP    1.1  // 1.0      
#define COLTK3_BASE_FP    1.3  // 1.0 
#define COLTK4_BASE_FP    1.5  // 1.0 
#define COLTK5_BASE_FP    1.7  // 1.0 
#define COLTK6_BASE_FP    1.9  // 1.0 
    
#define COLTK1_BASE_RD    1.70 // 2.0    
#define COLTK2_BASE_RD    1.47 // 2.0    
#define COLTK3_BASE_RD    0.83 // 2.0    

#define COLTK1_BASE_FE    0.47  // 0.4
#define COLTK2_BASE_FE    0.40  // 0.4
#define COLTK3_BASE_FE    0.33  // 0.4

#define COLTK1_BASE_CY    10   // 8 
#define COLTK2_BASE_CY    13   // 8  
#define COLTK3_BASE_CY    16   // 8
#define COLTK4_BASE_CY    20   // 8
#define COLTK5_BASE_CY    24   // 8
#define COLTK6_BASE_CY    28   // 8

// Basic Pistol       
#define TRAINING1_BASE_FP    2.0  // 1.0  
#define TRAINING2_BASE_FP    2.4  // 1.0 
#define TRAINING3_BASE_FP    2.6  // 1.0  
#define TRAINING4_BASE_FP    3.2  // 1.0  
#define TRAINING5_BASE_FP    3.6  // 1.0  
#define TRAINING6_BASE_FP    4.0  // 1.0 
    
#define TRAINING1_BASE_RD    2.03 // 2.0    
#define TRAINING2_BASE_RD    1.33 // 2.0     
#define TRAINING3_BASE_RD    0.87 // 2.0    

#define TRAINING1_BASE_FE    0.57  // 0.4  
#define TRAINING2_BASE_FE    0.43  // 0.4 
#define TRAINING3_BASE_FE    0.33  // 0.4

#define TRAINING1_BASE_CY    12    // 8 
#define TRAINING2_BASE_CY    16    // 8  
#define TRAINING3_BASE_CY    20    // 8
#define TRAINING4_BASE_CY    24    // 8
#define TRAINING5_BASE_CY    28    // 8
#define TRAINING6_BASE_CY    36    // 8

// Tin Hat
#define TINHAT1_BASE_DE    2.0 // 1.0    
#define TINHAT2_BASE_DE    4.0 // 1.0   
#define TINHAT3_BASE_DE    6.0 // 1.0   
#define TINHAT4_BASE_DE    8.0 // 1.0   
#define TINHAT5_BASE_DE   10.0 // 1.0   
#define TINHAT6_BASE_DE   15.0 // 1.0   

// Boxers
#define SHOES1_BASE_HP     5.0 // 1.0    
#define SHOES2_BASE_HP    10.0 // 1.0   
#define SHOES3_BASE_HP    15.0 // 1.0   
#define SHOES4_BASE_HP    20.0 // 1.0   
#define SHOES5_BASE_HP    25.0 // 1.0   
#define SHOES6_BASE_HP    30.0 // 1.0   



// todo - These need adding in, and shotgun, rifle, machine....

#define TRAINING_FP_LIMIT   5
#define TRAINING_FE_LIMIT   2
#define TRAINING_RD_LIMIT   2
#define TRAINING_CY_LIMIT   5
#define TRAINING_SP_LIMIT   1
#define TRAINING_SP2_LIMIT  1

#define ENFIELD_FP_LIMIT   5
#define ENFIELD_FE_LIMIT   1 
#define ENFIELD_RD_LIMIT   2  
#define ENFIELD_CY_LIMIT   5
#define ENFIELD_SP_LIMIT   1
#define ENFIELD_SP2_LIMIT  1


#define HUNTER_FP_LIMIT   5
#define HUNTER_FE_LIMIT   1 
#define HUNTER_RD_LIMIT   2  
#define HUNTER_CY_LIMIT   5
#define HUNTER_SP_LIMIT   1
#define HUNTER_SP2_LIMIT  1

#define MAUSER_FP_LIMIT   5
#define MAUSER_FE_LIMIT   1 
#define MAUSER_RD_LIMIT   2  
#define MAUSER_CY_LIMIT   5
#define MAUSER_SP_LIMIT   1
#define MAUSER_SP2_LIMIT  1

#define MAUSERK_FP_LIMIT   5
#define MAUSERK_FE_LIMIT   1 
#define MAUSERK_RD_LIMIT   2  
#define MAUSERK_CY_LIMIT   5
#define MAUSERK_SP_LIMIT   1
#define MAUSERK_SP2_LIMIT  1

#define MACHINE_FP_LIMIT   5
#define MACHINE_FE_LIMIT   1 
#define MACHINE_RD_LIMIT   2  
#define MACHINE_CY_LIMIT   5
#define MACHINE_SP_LIMIT   1
#define MACHINE_SP2_LIMIT  1

#define ARMY_FP_LIMIT   5
#define ARMY_FE_LIMIT   1 
#define ARMY_RD_LIMIT   2  
#define ARMY_CY_LIMIT   5
#define ARMY_SP_LIMIT   1
#define ARMY_SP2_LIMIT  1

#define FARMERS_FP_LIMIT   5
#define FARMERS_FE_LIMIT   1
#define FARMERS_RD_LIMIT   2  
#define FARMERS_CY_LIMIT   5
#define FARMERS_SP_LIMIT   1
#define FARMERS_SP2_LIMIT  1

#define COLT_FP_LIMIT   5 
#define COLT_FE_LIMIT   2
#define COLT_RD_LIMIT   2  
#define COLT_CY_LIMIT   5
#define COLT_SP_LIMIT   1
#define COLT_SP2_LIMIT  1

#define COLTK_FP_LIMIT   5
#define COLTK_FE_LIMIT   2 
#define COLTK_RD_LIMIT   2 
#define COLTK_CY_LIMIT   5
#define COLTK_SP_LIMIT   1
#define COLTK_SP2_LIMIT  2

#define LUGER_FP_LIMIT   5
#define LUGER_FE_LIMIT   2
#define LUGER_RD_LIMIT   2 
#define LUGER_CY_LIMIT   5
#define LUGER_SP_LIMIT   1
#define LUGER_SP2_LIMIT  1


#define WESTON_FP_LIMIT   5
#define WESTON_FE_LIMIT   2 
#define WESTON_RD_LIMIT   2
#define WESTON_CY_LIMIT   5
#define WESTON_SP_LIMIT   1
#define WESTON_SP2_LIMIT  1

#define TINHAT_DE_LIMIT   3
#define TINHAT_SP_LIMIT   1
#define TINHAT_DE_BASE    2

#define SHOES_HP_LIMIT   3
#define SHOES_SP_LIMIT   1
#define SHOES_HP_BASE    5

#define SET_WEAPONS   0 
#define GET_FIREPOWER 1
#define GET_FIRERATE  2
#define GET_RELOAD    3
#define GET_CAPACITY  4
#define GET_SPECIAL   5 
#define GET_SPECIAL2  6

extern bool Calculate_Item(int item_value, int item_type, int the_item, int item_value1, int item_value2, int item_value3);
extern float Node_Distance1(float x1, float y1, float x2, float y2);
extern void Calculate_Inventory();
extern int Get_Cost(int id, int pickup);
extern void Set_Sprite(int id, int anim, int state, int hud_or_sprite, bool reset);
extern float TimerGetTime();
extern void ShotIdle(int loop);
extern void Display_Message(int index, int message);
extern void Calculate_Gold();
extern void Bit_Shift( int the_value1, int bit_to_shift, int bit_value);
extern int Get_Bit_Shift( int the_value1, int bit_to_shift);  
extern void ShotIdle(int loop);
extern void Calculate_Stats();
extern void Calculate_Health(int amount, bool share, int index, bool regen); 
extern void Calculate_Lifebar();  

float Get_Weapon_Stats(int the_value, int type);
bool Pickup_Check(int loop, int the_item, int type);
void Reload_Gun();

float Get_Weapon_Stats(int the_value, int type)
{
    float test_value = 0.0;
    float temp_value = 0.0;  

	player_inv[16];        // INV_PISTOL      -
	player_inv_value[16];  // WESTON_PISTOL   -
	player_inv_value1[16]; // SPECIAL TYPE    -
	player_inv_value2[16]; // CAPACITY        - 
    player_inv_value3[16]; // SPECIAL VALUE   - 

	if(the_value >= 0)
	{

    if(player_inv[the_value] == INV_GRENADE_A || player_inv[the_value] == INV_GRENADE_E)     
    {    

                   
    }       
                 
    if(player_inv[the_value] == INV_MACHINE_A || player_inv[the_value] == INV_MACHINE_B || player_inv[the_value] == INV_MACHINE_E)     
    {    
        if(player_inv_value[the_value] == THOMPSOM_MACHINE) 
        {   
            
            if(Get_Bit_Shift( the_value, 1) == 0)
                temp_value = (int)(MACHINE1_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 1)
                temp_value = (int)(MACHINE2_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 2)
                temp_value = (int)(MACHINE3_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 3)
                temp_value = (int)(MACHINE4_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 4)
                temp_value = (int)(MACHINE5_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 5)
                temp_value = (int)(MACHINE6_BASE_FP * 10);              
                     
            if(type == SET_WEAPONS)
                GUN_FIREPOWER = (int)temp_value;
            if(type == GET_FIREPOWER) 
                test_value = temp_value;               
                      
                                                                                               
            if(Get_Bit_Shift( the_value, 2) == 0) 
                temp_value = (int)(MACHINE1_BASE_FE * 1000);
            if(Get_Bit_Shift( the_value, 2) == 1) 
                temp_value = (int)(MACHINE2_BASE_FE * 1000);
                                                 
            if(type == SET_WEAPONS)
                GUN_FIRERATE = (int)temp_value;
            if(type == GET_FIRERATE) 
                test_value = temp_value;             
            
                
            if(Get_Bit_Shift( the_value, 3) == 0) 
                temp_value = (int)(MACHINE1_BASE_RD * 1000);
            if(Get_Bit_Shift( the_value, 3) == 1) 
                temp_value = (int)(MACHINE2_BASE_RD * 1000);
            if(Get_Bit_Shift( the_value, 3) == 2) 
                temp_value = (int)(MACHINE3_BASE_RD * 1000);
                                             
            if(type == SET_WEAPONS)
                GUN_RELOAD = (int)temp_value;
            if(type == GET_RELOAD) 
                test_value = temp_value;   
                
                
            if(Get_Bit_Shift( the_value, 4) == 0) 
                temp_value = MACHINE1_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 1) 
                temp_value = MACHINE2_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 2) 
                temp_value = MACHINE3_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 3) 
                temp_value = MACHINE4_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 4) 
                temp_value = MACHINE5_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 5) 
                temp_value = MACHINE6_BASE_CY;
                                             
            if(type == SET_WEAPONS)
                GUN_CAPACITY = (int)temp_value;
            if(type == GET_CAPACITY) 
                test_value = temp_value;                   
                
                
            temp_value = (float)Get_Bit_Shift( the_value, 5);
                                             
            if(type == SET_WEAPONS)
                GUN_SPECIAL = (int)temp_value; 
            if(type == GET_SPECIAL) 
                test_value = temp_value;  
                
            temp_value = (float)Get_Bit_Shift( the_value, 6);
                                             
            if(type == SET_WEAPONS)
                GUN_SPECIAL2 = (int)temp_value;
            if(type == GET_SPECIAL2) 
                test_value = temp_value;                                             
        }      
    }      
                     
    if(player_inv[the_value] == INV_SHOTGUN_A || player_inv[the_value] == INV_SHOTGUN_B || player_inv[the_value] == INV_SHOTGUN_E)     
    {    
        if(player_inv_value[the_value] == FARMERS_SHOTGUN) 
        {   
            
            if(Get_Bit_Shift( the_value, 1) == 0)
                temp_value = (int)(SHOTGUN1_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 1)
                temp_value = (int)(SHOTGUN2_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 2)
                temp_value = (int)(SHOTGUN3_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 3)
                temp_value = (int)(SHOTGUN4_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 4)
                temp_value = (int)(SHOTGUN5_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 5)
                temp_value = (int)(SHOTGUN6_BASE_FP * 10);              
                     
            if(type == SET_WEAPONS)
                GUN_FIREPOWER = (int)temp_value;
            if(type == GET_FIREPOWER) 
                test_value = temp_value;               
                      
                                                                                                
            if(Get_Bit_Shift( the_value, 2) == 0) 
                temp_value = (int)(SHOTGUN1_BASE_FE * 1000);
            if(Get_Bit_Shift( the_value, 2) == 1) 
                temp_value = (int)(SHOTGUN2_BASE_FE * 1000);
                                                 
            if(type == SET_WEAPONS)
                GUN_FIRERATE = (int)temp_value;
            if(type == GET_FIRERATE) 
                test_value = temp_value;             
            
                
            if(Get_Bit_Shift( the_value, 3) == 0) 
                temp_value = (int)(SHOTGUN1_BASE_RD * 1000);
            if(Get_Bit_Shift( the_value, 3) == 1) 
                temp_value = (int)(SHOTGUN2_BASE_RD * 1000);
            if(Get_Bit_Shift( the_value, 3) == 2) 
                temp_value = (int)(SHOTGUN3_BASE_RD * 1000);
                                             
            if(type == SET_WEAPONS)
                GUN_RELOAD = (int)temp_value;
            if(type == GET_RELOAD) 
                test_value = temp_value;   
                
                
            if(Get_Bit_Shift( the_value, 4) == 0) 
                temp_value = SHOTGUN1_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 1) 
                temp_value = SHOTGUN2_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 2) 
                temp_value = SHOTGUN3_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 3) 
                temp_value = SHOTGUN4_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 4) 
                temp_value = SHOTGUN5_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 5) 
                temp_value = SHOTGUN6_BASE_CY;
                                             
            if(type == SET_WEAPONS)
                GUN_CAPACITY = (int)temp_value;
            if(type == GET_CAPACITY) 
                test_value = temp_value;                  
                
                
            temp_value = (float)Get_Bit_Shift( the_value, 5);
                                             
            if(type == SET_WEAPONS)
                GUN_SPECIAL = (int)temp_value;
            if(type == GET_SPECIAL) 
                test_value = temp_value;  
                
            temp_value = (float)Get_Bit_Shift( the_value, 6);
                                             
            if(type == SET_WEAPONS)
                GUN_SPECIAL2 = (int)temp_value;
            if(type == GET_SPECIAL2) 
                test_value = temp_value;                                             
        }   
        if(player_inv_value[the_value] == ARMY_SHOTGUN) 
        {   
            
            if(Get_Bit_Shift( the_value, 1) == 0)
                temp_value = (int)(ARMY1_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 1)
                temp_value = (int)(ARMY2_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 2)
                temp_value = (int)(ARMY3_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 3)
                temp_value = (int)(ARMY4_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 4)
                temp_value = (int)(ARMY5_BASE_FP * 10);              
            if(Get_Bit_Shift( the_value, 1) == 5)
                temp_value = (int)(ARMY6_BASE_FP * 10);              
                     
            if(type == SET_WEAPONS)
                GUN_FIREPOWER = (int)temp_value;
            if(type == GET_FIREPOWER) 
                test_value = temp_value;               
                      
                                                                                               
            if(Get_Bit_Shift( the_value, 2) == 0) 
                temp_value = (int)(ARMY1_BASE_FE * 1000);
            if(Get_Bit_Shift( the_value, 2) == 1) 
                temp_value = (int)(ARMY2_BASE_FE * 1000);
                                                 
            if(type == SET_WEAPONS)
                GUN_FIRERATE = (int)temp_value;
            if(type == GET_FIRERATE) 
                test_value = temp_value;             
            
                
            if(Get_Bit_Shift( the_value, 3) == 0) 
                temp_value = (int)(ARMY1_BASE_RD * 1000);
            if(Get_Bit_Shift( the_value, 3) == 1) 
                temp_value = (int)(ARMY2_BASE_RD * 1000);
            if(Get_Bit_Shift( the_value, 3) == 2) 
                temp_value = (int)(ARMY3_BASE_RD * 1000);
                                             
            if(type == SET_WEAPONS)
                GUN_RELOAD = (int)temp_value;
            if(type == GET_RELOAD) 
                test_value = temp_value;   
                 
                
            if(Get_Bit_Shift( the_value, 4) == 0) 
                temp_value = ARMY1_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 1) 
                temp_value = ARMY2_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 2) 
                temp_value = ARMY3_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 3) 
                temp_value = ARMY4_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 4) 
                temp_value = ARMY5_BASE_CY;
            if(Get_Bit_Shift( the_value, 4) == 5) 
                temp_value = ARMY6_BASE_CY;
                                             
            if(type == SET_WEAPONS)
                GUN_CAPACITY = (int)temp_value;
            if(type == GET_CAPACITY) 
                test_value = temp_value;                  
                
                
            temp_value = (float)Get_Bit_Shift( the_value, 5);
                                             
            if(type == SET_WEAPONS) 
                GUN_SPECIAL = (int)temp_value;
            if(type == GET_SPECIAL) 
                test_value = temp_value;    
                
            temp_value = (float)Get_Bit_Shift( the_value, 6);
                                             
            if(type == SET_WEAPONS)
                GUN_SPECIAL2 = (int)temp_value;
            if(type == GET_SPECIAL2) 
                test_value = temp_value;                                           
        }               
    }      
    
        
    if(player_inv[the_value] == INV_RIFLE_A || player_inv[the_value] == INV_RIFLE_B || player_inv[the_value] == INV_RIFLE_E)     
    {    
			// FIREPOWER
			if(player_inv_value[the_value] == FARMERS_RIFLE)
				temp_value = (int)(RIFLE1_BASE_FP * 10);  // 10

			// FIREPOWER 
			if(player_inv_value[the_value] == HUNTER_RIFLE) 
				temp_value = (int)(RIFLE2_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == ENFIELD_RIFLE)  
				temp_value = (int)(RIFLE3_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == ENFIELDK_RIFLE)  
				temp_value = (int)(RIFLE4_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == MAUSER_RIFLE)  
				temp_value = (int)(RIFLE5_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == MAUSERK_RIFLE)  
				temp_value = (int)(RIFLE6_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == CARBINE_RIFLE)  
				temp_value = (int)(RIFLE7_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == CARBINEK_RIFLE)  
				temp_value = (int)(RIFLE8_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == GEWEHR_RIFLE)  
				temp_value = (int)(RIFLE9_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == GEWEHRK_RIFLE)  
				temp_value = (int)(RIFLE10_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == HEINRICH_RIFLE)  
				temp_value = (int)(RIFLE11_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == HEINRICHK_RIFLE)   
				temp_value = (int)(RIFLE12_BASE_FP * 10);  // 10

			// FIREPOWER 
			if(player_inv_value[the_value] == WINCHESTER_RIFLE)   
				temp_value = (int)(RIFLE13_BASE_FP * 10);  // 10 

			
			if(type == SET_WEAPONS)	
			if(player_inv_value1[the_value] == BONUS_FIREPOWER)
				temp_value += player_inv_value3[the_value];

            if(type == SET_WEAPONS)
                GUN_FIREPOWER = (int)temp_value;
            if(type == GET_FIREPOWER)    
                test_value = temp_value; 
			
			// FIRERATE
            temp_value = (int)(RIFLE1_BASE_FE * 1000); // 400

			if(player_inv_value1[the_value] == BONUS_FIRERATE)
				temp_value -= player_inv_value3[the_value]*10;
                                                 
            if(type == SET_WEAPONS) 
                GUN_FIRERATE = (int)temp_value;
            if(type == GET_FIRERATE) 
                test_value = temp_value;   
			
			// RELOAD
            temp_value = (int)(RIFLE1_BASE_RD * 1000);  

			if(player_inv_value1[the_value] == BONUS_RELOAD) 
				temp_value -= player_inv_value3[the_value]*50;
                                             
            if(type == SET_WEAPONS)
                GUN_RELOAD = (int)temp_value;
            if(type == GET_RELOAD) 
                test_value = temp_value;   
			
			// CAPACITY
            temp_value = RIFLE1_BASE_CY; 

			if(player_inv_value1[the_value] == BONUS_CAPACITY)   
				temp_value += player_inv_value3[the_value]*1; 
                                             
            if(type == SET_WEAPONS)
                GUN_CAPACITY = (int)temp_value;
            if(type == GET_CAPACITY) 
                test_value = temp_value;  
             
    }        
    
    if(player_inv[the_value] == INV_PISTOL_A || player_inv[the_value] == INV_PISTOL_E)     
    {    

			// FIREPOWER
			if(player_inv_value[the_value] == TRAINING_PISTOL)
				temp_value = (int)(PISTOL1_BASE_FP * 10);  // 7

			// FIREPOWER 
			if(player_inv_value[the_value] == WEBLEY_PISTOL) 
				temp_value = (int)(PISTOL2_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == LUGER_PISTOL)  
				temp_value = (int)(PISTOL3_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == LUGERK_PISTOL)  
				temp_value = (int)(PISTOL4_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == WESTON_PISTOL)
				temp_value = (int)(PISTOL5_BASE_FP * 10);  // 7

			// FIREPOWER 
			if(player_inv_value[the_value] == WESTONK_PISTOL) 
				temp_value = (int)(PISTOL6_BASE_FP * 10);  // 10
			 
			// FIREPOWER
			if(player_inv_value[the_value] == MAUSER_PISTOL)  
				temp_value = (int)(PISTOL7_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == MAUSERK_PISTOL)  
				temp_value = (int)(PISTOL8_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == COLT_PISTOL)
				temp_value = (int)(PISTOL9_BASE_FP * 10);  // 7

			// FIREPOWER 
			if(player_inv_value[the_value] == COLTK_PISTOL) 
				temp_value = (int)(PISTOL10_BASE_FP * 10);  // 10

			// FIREPOWER 
			if(player_inv_value[the_value] == SAVAGE_PISTOL)  
				temp_value = (int)(PISTOL11_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == SAVAGEK_PISTOL)  
				temp_value = (int)(PISTOL12_BASE_FP * 10);  // 10

			// FIREPOWER
			if(player_inv_value[the_value] == NAVYCOLT_PISTOL)  
				temp_value = (int)(PISTOL13_BASE_FP * 10);  // 10



			if(type == SET_WEAPONS)
			if(player_inv_value1[the_value] == BONUS_FIREPOWER)
				temp_value += player_inv_value3[the_value];

            if(type == SET_WEAPONS)
                GUN_FIREPOWER = (int)temp_value;
            if(type == GET_FIREPOWER)    
                test_value = temp_value; 
			
			// FIRERATE
            temp_value = (int)(PISTOL1_BASE_FE * 1000); // 310

			if(player_inv_value1[the_value] == BONUS_FIRERATE)
				temp_value -= player_inv_value3[the_value]*5;
                                                 
            if(type == SET_WEAPONS) 
                GUN_FIRERATE = (int)temp_value;
            if(type == GET_FIRERATE) 
                test_value = temp_value;   
			 
			// RELOAD
            temp_value = (int)(PISTOL1_BASE_RD * 1000);  // 1100

			if(player_inv_value1[the_value] == BONUS_RELOAD)  
				temp_value -= player_inv_value3[the_value]*50;
                                             
            if(type == SET_WEAPONS)
                GUN_RELOAD = (int)temp_value;
            if(type == GET_RELOAD) 
                test_value = temp_value;   
			
			// CAPACITY 
            temp_value =PISTOL1_BASE_CY;  

			if(player_inv_value1[the_value] == BONUS_CAPACITY)   
				temp_value += player_inv_value3[the_value]*1; 
                                             
            if(type == SET_WEAPONS)
                GUN_CAPACITY = (int)temp_value;
            if(type == GET_CAPACITY) 
                test_value = temp_value;            
                             
    }     

	} // the_value >= 0  

    return(test_value);
        
}

bool Pickup_Check(int loop, int the_item, int type)
{
    float midX=0.0, midY=0.0;
    float tarX=0.0, tarY=0.0;
    float dis_to_point=0;
    int cost=0;
    bool success=false; 
    bool no_gold = false;
    float range = 0.0; 
	bool is_gold_bar=false;

	if(the_item >= 0 && loop >= 0)
	{

	if(Fx[the_item].item_type == INV_GOLD)
	if(Fx[the_item].value == SMALL_GOLDBAR || Fx[the_item].value == LARGE_GOLDBAR)
	   is_gold_bar=true;	
      
    if(type == RUN_AND_COLLECT)
       range = (float)RUN_COLLECT_RANGE;
    else
       range = (float)COLLECT_RANGE;
    
    midX = sprite[loop].w+sprite[loop].box_width/2; 
    midY = sprite[loop].z+sprite[loop].box_height/2;
                       
    tarX = Fx[the_item].x + 0.05f;  
    tarY = Fx[the_item].y + 0.05f; 
                         
    dis_to_point = Node_Distance1(midX, midY, tarX, tarY);  
    
    if(Fx[the_item].turn_off == false && the_item != -1)
    if(dis_to_point <= range) 
    {

        if(the_item != -1) 
        { 

			if(Fx[the_item].item_type != INV_AMPUOLE)
				success = Calculate_Item(Fx[the_item].value, Fx[the_item].item_type, the_item, Fx[the_item].value1, Fx[the_item].value2, Fx[the_item].value3);
			else 
			{
				if(ply_id != -1)
				{
					Calculate_Health(Fx[the_item].value, false, ply_id, false);
					Fx[the_item].turn_off = true;
					DXPick_Up=-1; 
					DX_USECOLLECT=false;
					chute_sfx = true;
					Calculate_Lifebar();
				}
			}
			 
			if(success == true)
			{
				mouseleft=false;  

				DXPick_Up=-1;

				Fx[the_item].turn_off = true;

				if(displaying_message_type == MSG_NOWEAPON || displaying_message_type == MSG_TOOFAR)
				{
				   dialog_timer = (int)TimerGetTime();
				   hud[2].alpha = 0.0f; 
				   sprintf( counter[4].word, "");
				   dialog_active = -1; 
				   displaying_message_type = -1;
				}
			}

            if(ply_pickup_target == -1)
            if(flash_on == the_item + TOTAL_NO_SPRITES)
                flash_on = -1;
                           
        }                            
        if(ply_id != -1)       
        if(ply_pickup_target == -1) 
        {
                           
            bump_player_timer  = (int)TimerGetTime() + BUMP_TIME;
            bump_player = true; 
            
        }           
 
		if(Fx[the_item].item_type != INV_GOLD || (AUTO_PICKUP_GOLD == GOLD_AUTO_OFF) )
        	mouseleft = false;        

    }

	} // the_item >= 

	return(success);

}

void Reload_Gun()
{

}
