#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN 
 
#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>			// Header File For Standard Input/Output
#include <gl\gl.h> 
#include "globals.h"  

extern int Find_Path(int loop, float destX, float destY);
extern int New_Sprite(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int sideways, int upways, int state, int linked_sprite, int tex_id, int a_global, float angle, int p_type, int goto_point);
extern void ShotIdle(int loop); 
extern bool Is_Guy_In_Range(int loop, int target, float range);  
extern void Message_Limits();  
extern bool Shoot_Ray(int loop, float x1, float y1, float x2, float y2, bool grey_test, bool shooting, float precision);  
extern void Calculate_Bullets();     
extern void Calculate_Lifebar();       
extern void Calculate_Mission(); 
extern void Calculate_Bullet_Flash(); 
extern float Calculate_Emybar(int index);        
extern void Calculate_Inventory();
extern void Get_Mouse_Row(); 
extern void PickUp_Sfx(int type, int value); 
extern void Moving_Code(int loop, float x_pos, float y_pos, int f_rate);
extern int Get_Tile_Index(float x, float y);
extern bool TestSpriteToShootPly(int no_test, float x1, float y1, float x2, float y2, bool hulk, int target_id, int f_rate, bool shotgun_attack);
extern void Run_Keyboard(int f_rate1);
extern bool Shoot_Ray_Ply(int loop, float x1, float y1, float x2, float y2);

bool Get_Next_Tile(int k, float x2, float y2);
float Calculate_Offset(bool is_a_sprite); 
void  Run_Mouse_Limits(int f_rate);
void Run_Fx(int f_rate); 
int GetAccuracy(int loop, int target);

int target_all=-1;

bool was_on_pickup = false;

void Mouse_Code(int f_rate1)
{
    int old_direction = 0;  
    int new_direction = 0;
    int test_player=0;
    int brush_id=0;       
    int temp_index=0;
    int temp_row_x=0;       
    int temp_row_y=0; 
    int row_x1=0;     
    int row_y1=0;
    int sell_gold=0;
    int m_check=-1; 
    bool knifing=false;  
    bool has_ammo=false;
    int time_diff=0;
    float mid_x=0.0f,mid_y=0.0f; 
    float tar_x=0.0f,tar_y=0.0f; 
    float testX=0.0f,testY=0.0f; 
    float testX1=0.0f, testY1=0.0f;
    float widthX=0.0f, heightY = 0.0f;
    float widthX1=0.0f, heightY1 = 0.0f;
    float midX=0.0f, midY=0.0f;
    float tarX=0.0f, tarY=0.0f;
    float diffX=0.0f, diffY=0.0f;
    float deltax=0.0f, deltay=0.0f;
    float angle=0.0f;     
    float distance = 0.0f;  
    float percentage=0.0f;  
    float old_diff=0.0f;
	float head_offset = 0.05f;
	float closest_point = 0.0f;
	float dis_to_point = 0.0f;

	int found_a_target = -1;
	int slongest_line=0;
	char string_value[1024];
    bool test=false;
    bool go_aheadX=true;
    bool go_aheadY=true;
    int k=0; 
	int current_guy=-1;
    bool move_the_guy=false;
    bool building_selected=false; 
    bool on_collision=false;
    int the_tile=0;
    bool machine_skip=false;
    bool shootable_object=false;
    bool segTest = true;
    int tall_trigger = -1; 
	bool FX_TOOFAR = false;
	bool TALKMAN_TOOFAR = false;
	bool SPRITE_NOWEAPON=false;
	int heal_amount=0;
	int pack_id=-1;
	bool has_bullets=true;

	float mouse_DX_Offset = 0.05f;    

    on_a_trigger=false;       

    if(f_rate1 <= 0)      
        f_rate1 = 1; 
	  
          Get_Mouse_Row();                                                     
                                                                              
        // ******************************************************************************//
        //                                 Mouse-Scrolling                               //                     
        // ******************************************************************************//

        if((mode || game_mode == WALK )) // || game_mode == FRONT   
        {     

			if(game_mode == WALK && !mode)
			{
				if(sta2_turn == TURN_PLAYER)  
					current_guy = ply_id;
				if(sta2_turn == TURN_COMPUTER)
					current_guy = emy_id; 
			}
				 
			testX = hud_mouseX - (-camX);                                                   
			testY = hud_mouseY - (-camY);  

            DX_ON_TARGET = false;    
                          
            on_selected_man = NO_MAN;    
			 
            on_pickup = false;  
			
			if(stored_target != -1) 
				last_target = stored_target;  
                          
            testX = hud_mouseX - (-camX);                                                
            testY = hud_mouseY - (-camY);                    
        
			new_counter[0].alpha = 0.0f; // To Hit
			new_counter[1].alpha = 0.0f; // Lvl Hp text 
			new_counter[2].alpha = 0.0f; // Ground item text.

			new_counter[3].alpha = 0.0f; // Menu text.
			new_counter[4].alpha = 0.0f; // Menu text.
			new_counter[5].alpha = 0.0f; // Menu text.  
			new_counter[6].alpha = 0.0f; // Menu text.
			new_counter[7].alpha = 0.0f; // Menu text.
			new_counter[8].alpha = 0.0f; // Menu text.
			new_counter[9].alpha = 0.0f; // Menu text.

			new_counter[12].alpha = 0.0f;  // @ Symbol.

			new_counter[0].id = 0; // Mouse over text.
			new_counter[12].id = 0;  // @ Symbol.

			hud[58].alpha = 0.0f;
			     
			if(sta2_turn == TURN_PLAYER)
			if(sta2_displaying_help == false)
			if(game_mode == WALK && !mode)
			if(STA2_MODE == MODE_AIMING || STA2_MODE == MODE_TARGET) 
			{      
				 
				hud[58].alpha = 0.0f;
				hud[34].alpha = 1.0f; // edge arrows..
				hud[35].alpha = 1.0f; // edge arrows.. 
				hud[31].alpha = 1.0f; // edge arrows..
				hud[37].alpha = 1.0f; // edge arrows..

				hud[36].alpha = 0.0f;
				       
				new_counter[10].alpha = 1.0f;         
				new_counter[10].id = 0; 
		       
				new_counter[10].x = -0.25f;      
				new_counter[10].y = -0.36f;   // 0.36f 	       

				new_counter[10].w = new_counter[10].x - 0.026f;   
				new_counter[10].z = new_counter[10].y - 0.015f;

				new_counter[10].box_width = strlen(new_counter[10].word)   *  0.026f;
				new_counter[10].box_height = new_counter[10].height - 0.015f;	

				sprintf( new_counter[10].word, "Press space to cancel");  
				       
				new_counter[11].alpha = 1.0f;         
				new_counter[11].id = 0;  
		        

				if(screen_mode == SCREEN_1610_WIDESCREEN)
					new_counter[11].x = -0.60f;        
				else
					new_counter[11].x = -0.64f;        

				new_counter[11].y = 0.36f; // 0.36f      
				 
				new_counter[11].w = new_counter[11].x - 0.026f;    
				new_counter[11].z = new_counter[11].y - 0.015f;

				new_counter[11].box_width = strlen(new_counter[11].word)   *  0.026f;
				new_counter[11].box_height = new_counter[11].height - 0.015f;	

				if(current_guy != -1)
				if(sprite[current_guy].value2 >= 0)
					pack_id = sta2_squad[sprite[current_guy].value2].wp;  

				if(has_sniper_equipped)  
				if(sta2_shots_sniper >= 1)
				{
					sprintf( new_counter[11].word, "OUT OF SHOTS!" );
					has_bullets = false;
				}
				else
					sprintf( new_counter[11].word, "SHOTS LEFT : %i", STA2_SNIPER_LIMIT-sta2_shots_sniper); 

				if(has_mortar_equipped)    
				if(sta2_shots_mortar >= 1)
				{
					sprintf( new_counter[11].word, "OUT OF SHOTS!" );
					has_bullets = false;
				}
				else
					sprintf( new_counter[11].word, "SHOTS LEFT : %i", STA2_MORTAR_LIMIT-sta2_shots_mortar);  

				if(has_rifle_equipped)  
				if(sta2_shots_rifle >= 1)
				{
					sprintf( new_counter[11].word, "OUT OF SHOTS!" );
					has_bullets = false;
				}
				else
					sprintf( new_counter[11].word, "SHOTS LEFT : %i", 1-sta2_shots_rifle);  

				if(has_pistol_equipped)   
				if(sta2_shots_pistol >= 3)
				{
					sprintf( new_counter[11].word, "OUT OF SHOTS!" );
					has_bullets = false;
				}
				else
					sprintf( new_counter[11].word, "SHOTS LEFT : %i", 3-sta2_shots_pistol);  

				if(has_shotgun_equipped)  
				if(sta2_shots_shotgun >= STA2_SHOTGUN_LIMIT)
				{
					sprintf( new_counter[11].word, "OUT OF SHOTS!" ); 
					has_bullets = false;
				}
				else
					sprintf( new_counter[11].word, "SHOTS LEFT : %i", STA2_SHOTGUN_LIMIT-sta2_shots_shotgun);  

				if(has_machine_equipped)   
				if(sta2_shots_machine >= STA2_MACHINE_LIMIT)
				{
					sprintf( new_counter[11].word, "OUT OF SHOTS!" );
					has_bullets = false;
				}
				else
					sprintf( new_counter[11].word, "SHOTS LEFT : %i", STA2_MACHINE_LIMIT-sta2_shots_machine);  

				if(has_grenade_equipped) 
				if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
				if(sta2_pack[pack_id].extra_charge <= 0)
				{
					sprintf( new_counter[11].word, "OUT OF SHOTS!" ); 
					has_bullets = false;
				}
				else
					sprintf( new_counter[11].word, "SHOTS LEFT : %i", sta2_pack[pack_id].extra_charge);  

				// Debug text... 
			/*	sprintf( string_value, "^sta2_globalX%f",  sta2_globalX );
				strcat(new_counter[11].word, string_value);
				sprintf( string_value, "^sta2_globalY%f",  sta2_globalY );
				strcat(new_counter[11].word, string_value);*/
				 
			} 
			else
			{
				hud[34].alpha = 0.0f; // edge arrows..
				hud[35].alpha = 0.0f; // edge arrows..
				hud[31].alpha = 0.0f; // edge arrows..
				hud[37].alpha = 0.0f; // edge arrows..

				hud[36].alpha = 1.0f;
				new_counter[10].alpha = 0.0f;
				new_counter[11].alpha = 0.0f;
			}

			if(sta2_displaying_help == false)
			if(!mode && game_mode == WALK)
			if(sta2_turn == TURN_PLAYER) 
			if(STA2_MODE == MODE_MOVING)
			if(mouseright == true)  
			{
				mouseright = false;  

				switch(sta2_menu)    
				{         
					   
					case 0: 
						 
						sta2_menu_x = hud_mouseX - (-camX) - 0.1f; 
						sta2_menu_y = hud_mouseY - (-camY); 

						if(screen_mode == SCREEN_1610_WIDESCREEN)
						{ 
							if(real_mouseX < -0.55f)       
								sta2_menu_x = -0.67f;        
							if(real_mouseX > 0.23f)    
								sta2_menu_x = 0.23f;    
							if(real_mouseY < -0.13f)    
								sta2_menu_y = -0.13f;  
							if(real_mouseY > 0.32f)    
								sta2_menu_y = 0.32f;  
						}  

						if(screen_mode == SCREEN_169_WIDESCREEN)
						{
							if(real_mouseX < -0.62f)       
								sta2_menu_x = -0.74f;  
							if(real_mouseX > 0.33f)    
								sta2_menu_x = 0.33f;     
							if(real_mouseY < -0.1f)  
								sta2_menu_y = -0.1f;    
							if(real_mouseY > 0.30f)    
								sta2_menu_y = 0.30f;
						}

						sta2_menu = true; 
						sta2_space_pressed = false;
					break; 

					case 1:
						sta2_menu = false;
						sta2_space_pressed = false;
					break;						
				}   
				 
			}  

			// Turn off action menu if space pressed..
			if(hud[3].alpha == 1.0)
			if(sta2_displaying_help == false)
			if(sta2_menu == true)
			if(sta2_space_pressed == true || STA2_MODE != MODE_MOVING)  
			{
				mouseright = false; 
				sta2_menu = false;
				sta2_space_pressed = false; 
			}

			// Turn off action menu if not mouseover..
			if(hud[3].alpha == 1.0)
			if(sta2_displaying_help == false)
			if(sta2_menu == true)
			if(( testX < (hud[3].x + hud[3].width) )
			&&( testX > hud[3].x)                            
			&&( testY < (hud[3].y + hud[3].height) )
			&&( testY > hud[3].y))  
				sta2_menu = sta2_menu; 
			else
			{
				sta2_menu = false;
				mouseright = false;
				sta2_space_pressed = false;
			}

			if(sta2_displaying_help == false)
			    Set_Sprite(3, 0, LOOP, ANIM_HUD, ANIM_WALKING); // Hud textbox

			if(sta2_turn == TURN_PLAYER)  
			if(sta2_displaying_help == false) 
			if(current_guy != -1 && !mode)
			if(sta2_menu == true)  
			{  
				  
				hud[3].alpha = 1.0f;            

				hud[3].x = sta2_menu_x + 0.02f; 
				hud[3].y = sta2_menu_y - 0.30f;

				if(sprite[current_guy].value2 >= 0)
					pack_id = sta2_squad[sprite[current_guy].value2].wp;

				new_counter[3].alpha = 1.0f;

				sprintf(new_counter[3].word, "1 : PISTOL"); 
				 
				if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
				if(sta2_pack[pack_id].type == STA2_HEAVY)
					sprintf(new_counter[3].word, "1 : SHOTGUN");  

				new_counter[3].x = hud[3].x + 0.06f;  
				new_counter[3].y = sta2_menu_y;
				new_counter[3].w = new_counter[3].x - 0.026f;   
				new_counter[3].z = new_counter[3].y - 0.015f;
				new_counter[3].box_width = strlen(new_counter[3].word)   *  0.026f;
				new_counter[3].box_height = new_counter[3].height - 0.015f;	
				 
				new_counter[4].alpha = 1.0f;
				sprintf(new_counter[4].word, "2 : RIFLE"); 

				if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
				if(sta2_pack[pack_id].type == STA2_HEAVY)
					sprintf(new_counter[4].word, "2 : MACHINE");

				if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
				if(sta2_pack[pack_id].type == STA2_SNIPER)
					sprintf(new_counter[4].word, "2 : SNIPER");

				if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
				if(sta2_pack[pack_id].type == STA2_MORTAR)
					sprintf(new_counter[4].word, "2 : MORTAR");

				new_counter[4].x = hud[3].x + 0.06f;  
				new_counter[4].y = sta2_menu_y - 0.04f;
				new_counter[4].w = new_counter[4].x - 0.026f;   
				new_counter[4].z = new_counter[4].y - 0.015f;
				new_counter[4].box_width = strlen(new_counter[4].word)   *  0.026f;
				new_counter[4].box_height = new_counter[4].height - 0.015f;	

				new_counter[5].alpha = 1.0f;
				sprintf(new_counter[5].word, "3 : DEFEND"); 
				new_counter[5].x = hud[3].x + 0.06f; 
				new_counter[5].y = sta2_menu_y - 0.08f;
				new_counter[5].w = new_counter[5].x - 0.026f;   
				new_counter[5].z = new_counter[5].y - 0.015f;
				new_counter[5].box_width = strlen(new_counter[5].word)   *  0.026f;
				new_counter[5].box_height = new_counter[5].height - 0.015f;	

				new_counter[6].alpha = 1.0f;

				if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
				if(sta2_pack[pack_id].extra == PACK_EXTRA_MEDKIT) 
					sprintf(new_counter[6].word, "4 : MEDKIT"); 
				if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
				if(sta2_pack[pack_id].extra == PACK_EXTRA_GRENADE) 
					sprintf(new_counter[6].word, "4 : GRENADE"); 
				if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
				if(sta2_pack[pack_id].extra == PACK_EXTRA_NONE)
					sprintf(new_counter[6].word, "4 : ------");     

				new_counter[6].x = hud[3].x + 0.06f;  
				new_counter[6].y = sta2_menu_y - 0.12f;
				new_counter[6].w = new_counter[6].x - 0.026f;   
				new_counter[6].z = new_counter[6].y - 0.015f;
				new_counter[6].box_width = strlen(new_counter[6].word)   *  0.026f;
				new_counter[6].box_height = new_counter[6].height - 0.015f;	

				new_counter[7].alpha = 1.0f;  
				if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
				{
				if(sta2_pack[pack_id].special == PACK_SPECIAL_NONE)
					sprintf(new_counter[7].word, "5 : ------");
				if(sta2_pack[pack_id].special == PACK_SPECIAL_SCOPE)  
					sprintf(new_counter[7].word, "5 : SCOPE"); 
				if(sta2_pack[pack_id].special == PACK_SPECIAL_SHIELD) 
					sprintf(new_counter[7].word, "5 : SHIELD");
				if(sta2_pack[pack_id].special == PACK_SPECIAL_DUMDUM) 
					sprintf(new_counter[7].word, "5 : RAGE");
				if(sta2_pack[pack_id].special == PACK_SPECIAL_BOOTS) 
					sprintf(new_counter[7].word, "5 : DASH");
				if(sta2_pack[pack_id].special == PACK_SPECIAL_GODEYE) 
					sprintf(new_counter[7].word, "5 : GOD-EYE"); 
				if(sta2_pack[pack_id].special == PACK_SPECIAL_MAGICNET) 
					sprintf(new_counter[7].word, "5 : CLOAK");
				if(sta2_pack[pack_id].special == PACK_SPECIAL_VAMPIRE) 
					sprintf(new_counter[7].word, "5 : VAMPIRE");
				if(sta2_pack[pack_id].special == PACK_SPECIAL_MAGICHERB) 
					sprintf(new_counter[7].word, "5 : MARYJANE"); 
				if(sta2_pack[pack_id].special == PACK_SPECIAL_XPGAIN) 
					sprintf(new_counter[7].word, "5 : WISDOM");
				if(sta2_pack[pack_id].special == PACK_SPECIAL_DEATHBLOW) 
					sprintf(new_counter[7].word, "5 : FINAL");
				if(sta2_pack[pack_id].special == PACK_SPECIAL_LASTCHANCE) 
					sprintf(new_counter[7].word, "5 : LAST");
				}
				new_counter[7].x = hud[3].x + 0.06f;  
				new_counter[7].y = sta2_menu_y - 0.16f;
				new_counter[7].w = new_counter[7].x - 0.026f;   
				new_counter[7].z = new_counter[7].y - 0.015f;
				new_counter[7].box_width = strlen(new_counter[7].word)   *  0.026f;
				new_counter[7].box_height = new_counter[7].height - 0.015f;	

				new_counter[8].alpha = 1.0f; 
				sprintf(new_counter[8].word, "6 : VIEWMAP"); 
				new_counter[8].x = hud[3].x + 0.06f; 
				new_counter[8].y = sta2_menu_y - 0.20f;
				new_counter[8].w = new_counter[8].x - 0.026f;   
				new_counter[8].z = new_counter[8].y - 0.015f;
				new_counter[8].box_width = strlen(new_counter[8].word)   *  0.026f;
				new_counter[8].box_height = new_counter[8].height - 0.015f;	
				 
				new_counter[9].alpha = 1.0f;
				sprintf(new_counter[9].word, "7 : ENDMOVE");  
				new_counter[9].x = hud[3].x + 0.06f; 
				new_counter[9].y = sta2_menu_y - 0.24f;
				new_counter[9].w = new_counter[9].x - 0.026f;   
				new_counter[9].z = new_counter[9].y - 0.015f;
				new_counter[9].box_width = strlen(new_counter[9].word)   *  0.026f;
				new_counter[9].box_height = new_counter[9].height - 0.015f;	

			}
			else
				hud[3].alpha = 0.0f;    

			if(game_mode == WALK && !mode)   
			if(current_guy != -1)   
			{       

				if(sprite[current_guy].value2 >= 0)
					pack_id = sta2_squad[sprite[current_guy].value2].wp;

				new_counter[3].id = 0;  // Pistol  
				new_counter[4].id = 0;  // Rifle 
				new_counter[5].id = 0;  // Defend
				new_counter[6].id = 0;  // Extra 
				new_counter[7].id = 0;  // Special 
				new_counter[8].id = 0;  // Cancel  
				new_counter[9].id = 0;  // End turn  
				 
				// Disable options from menu...
				if(sta2_turn == TURN_PLAYER)
				if(sta2_shots_pistol >= 3 || sta2_shots_rifle >= 1 
				|| sta2_shots_shotgun >= STA2_SHOTGUN_LIMIT || sta2_shots_machine >= STA2_MACHINE_LIMIT 
				|| sta2_shots_sniper >= STA2_SNIPER_LIMIT || sta2_shots_mortar >= STA2_MORTAR_LIMIT
				|| sta2_used_extra == true || sta2_special_missed == true || sta2_shot_fired_gun == FIRED_RIFLE || sta2_shot_fired_gun == FIRED_MACHINE || sta2_shot_fired_gun == FIRED_SNIPER || sta2_shot_fired_gun == FIRED_MORTAR || sprite[current_guy].score <= 1)
					new_counter[3].id = 7; // Pistol / Shotgun

				if(sta2_turn == TURN_PLAYER)
				if(sta2_shots_pistol >= 3 || sta2_shots_rifle >= 1 
				|| sta2_shots_shotgun >= STA2_SHOTGUN_LIMIT || sta2_shots_machine >= STA2_MACHINE_LIMIT 
				|| sta2_shots_sniper >= STA2_SNIPER_LIMIT || sta2_shots_mortar >= STA2_MORTAR_LIMIT
				|| sta2_used_extra == true || sta2_special_missed == true || sta2_shot_fired_gun == FIRED_PISTOL || sta2_shot_fired_gun == FIRED_SHOTGUN || sprite[current_guy].score <= 1)
					new_counter[4].id = 7; // Rifle / Machine / Sniper / Mortar

				if(sta2_turn == TURN_PLAYER)
				if(sta2_shot_fired_gun != FIRED_NONE || sta2_used_extra == true || sta2_special_missed == true || sprite[current_guy].score <= 1)
					new_counter[5].id = 7; // Defend

				if(sta2_turn == TURN_PLAYER)
				if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
				if(sta2_pack[pack_id].type == STA2_SNIPER || sta2_pack[pack_id].type == STA2_MORTAR)
					new_counter[5].id = 7; // Defend

				if(sta2_turn == TURN_PLAYER)
				if(sta2_shot_fired_gun != FIRED_NONE || sta2_used_extra == true || sta2_special_missed == true || sprite[current_guy].score <= 1)
					new_counter[6].id = 7; // Extra 
				 
				if(sta2_turn == TURN_PLAYER)
				if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
				if(sta2_pack[pack_id].extra == PACK_EXTRA_NONE || sta2_pack[pack_id].extra_charge == 0 || sprite[current_guy].score <= 1)
					new_counter[6].id = 7; // Extra 
				 
				if(sta2_turn == TURN_PLAYER)
				if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
				if(sta2_pack[pack_id].special == PACK_SPECIAL_NONE || sta2_used_special == true || sta2_used_extra == true || sta2_shot_fired_gun != FIRED_NONE || sprite[current_guy].score <= 1)
					new_counter[7].id = 7; // Special

				if(sta2_turn == TURN_PLAYER)  
				if(sta2_battle_outcome != BATTLE_NONE) 
			//	if(STA2_MODE == MODE_MOVING && sprite[current_guy].return_fire == false || sprite[current_guy].score <= 1)
					new_counter[8].id = 7; // Cancel

				if(sta2_turn == TURN_PLAYER)
				if(sta2_menu == true) 
				for(int i = 3; i < 10;i++)
				if(new_counter[i].alpha == 1.0f)
				if(new_counter[i].id == 0)
				if(( testX < (new_counter[i].w + new_counter[i].box_width) )
				&&( testX > new_counter[i].w)                            
				&&( testY < (new_counter[i].z + new_counter[i].box_height) )
				&&( testY > new_counter[i].z))   
				{ 
					new_counter[i].id = 9;           

					if(mouseleft == true || DX_SHOOT == true) 
					{   
						mouseleft = false;  
						DX_SHOOT = false; 

						sta2_menu = false; 

						if(i == 3)
							sta2_1_pressed = true; 
						if(i == 4)
							sta2_2_pressed = true; 
						if(i == 5)
							sta2_3_pressed = true; 
						if(i == 6)
							sta2_4_pressed = true; 
						if(i == 7)
							sta2_5_pressed = true; 
						if(i == 8)
							sta2_6_pressed = true; 
						if(i == 9)
							sta2_7_pressed = true; 

					}     
				}    

				if(STA2_MODE != MODE_AIMING && STA2_MODE != MODE_TARGET)
				if(current_guy != -1)
				{
					 
				new_counter[1].alpha = 1.0f;      

				sprintf(new_counter[1].word, "");     
				 
				if(sprite[current_guy].score == 1 && sprite[current_guy].linked_sprite == player_type)
					sprintf(string_value, "WOUNDED..^", sprite[current_guy].score, Calculate_TotalScore(current_guy));  
				else 
					sprintf(string_value, "HP:%i/%i^", sprite[current_guy].score, Calculate_TotalScore(current_guy));  

				strcat(new_counter[1].word, string_value);       

				if(sta2_turn == TURN_COMPUTER)        
				{  
					if(sprite[current_guy].sector != UNIT_DOG && sprite[current_guy].sector != UNIT_CHIEF) 
						sprintf(string_value, "%s LVL%i^", sta2_emy_names[sprite[current_guy].name].string, sprite[current_guy].rank); 
					if(sprite[current_guy].sector == UNIT_DOG)
						sprintf(string_value, "DOG LVL%i^", sprite[current_guy].rank);
					if(sprite[current_guy].sector == UNIT_CHIEF)
						sprintf(string_value, "HELMUTT LVL%i^", sprite[current_guy].rank);


					strcat(new_counter[1].word, string_value);  
				}
				if(sta2_turn == TURN_PLAYER)    
				{   
					if(sprite[current_guy].value2 != -1)
					{
						if(sprite[current_guy].sector != UNIT_DOG)
							sprintf(string_value, "%s LVL%i:XP/%i^", sta2_squad[sprite[current_guy].value2].string, sta2_squad[sprite[current_guy].value2].rank, sta2_squad[sprite[current_guy].value2].xp );
						else
							sprintf(string_value, "DOG LVL%i:XP/%i^", sta2_squad[sprite[current_guy].value2].rank, sta2_squad[sprite[current_guy].value2].xp );
					}
					strcat(new_counter[1].word, string_value);  
				}  
				 
				} // not aiming...
				 
				if(STA2_MODE == MODE_MOVING || STA2_MODE == MODE_TARGET)
				if(current_guy != -1)
				{ 
					if(sta2_turn == TURN_COMPUTER)
					{
						if(sta2_enemy_mode == MOVE_MOVE) 
							sprintf( string_value, "MOVING.." );
						else
							sprintf( string_value, "AIMING.." );

						strcat(new_counter[1].word, string_value);
					}
					else  
					{ 
						if(sprite[current_guy].return_fire == false)
						{
						}
						else
							sprintf( string_value, "DEFENDING.." );

						if(STA2_MODE == MODE_TARGET)      
						{
							if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
							if(sta2_current_extra == PACK_EXTRA_MEDKIT)
								sprintf( string_value, "HEAL TARGET..^%i/1", sta2_pack[pack_id].extra_charge);
						}

						strcat(new_counter[1].word, string_value);
					}  
					 
				}      
				 
				// Debug text... 
			/*	if(current_guy != -1)   
				{
					sprintf( string_value, "^sta2_enemy_mode%i",  sta2_enemy_mode );
					strcat(new_counter[1].word, string_value);
					sprintf( string_value, "^node_count%i",  sprite[current_guy].node_count );
					strcat(new_counter[1].word, string_value);
					sprintf( string_value, "^on node%i",  sprite[current_guy].node_counter );
					strcat(new_counter[1].word, string_value);
				}*/

				if(new_counter[1].alpha != 0.0f)  
				{ 
					new_counter[1].x = hud[36].x + hud[36].width + 0.03f; 
					new_counter[1].y = hud[36].y + hud[36].height - 0.03f; 
				}  

				// Cover...   
				if(sta2_menu == false)
				if(sta2_displaying_help == false)
				if(sta2_turn == TURN_PLAYER)        
				if(STA2_MODE == MODE_MOVING)  
				{ 
				    testX = hud_mouseX - (-camX);                                                 
		            testY = hud_mouseY - (-camY);  

					row_x1 = (int)((mouseX + map_startX)*10);      
					row_y1 = (int)((mouseY + map_startY)*10);      
				  
					the_tile = (row_y1*MAP_HEIGHT)+row_x1;    

					if(new_counter[0].alpha == 0.0f)
					if(the_tile >= 0 && the_tile < MAP_TILES)   
					if(map_col[the_tile] != 0 && map_col[the_tile] != 6)     
					{ 
						new_counter[12].alpha = 1.0f;               
					    
						new_counter[12].x = testX + 0.1f;                    
						new_counter[12].y = testY;  

						sprintf( new_counter[12].word, "@");
						sprintf( new_counter[0].word, "Cover^%i&^", map_cover[the_tile]); 
					 
						new_counter[0].alpha = 1.0f;   
						 
						new_counter[0].x = testX + 0.13f;     
						new_counter[0].y = testY;   
						 
						// For left-sided messages, get longest line...
						if( new_counter[0].x >= sta2_left_of_screen) 
						{ 
							slongest_line = GetLongestLine(new_counter[0].word); 
							   
							new_counter[12].x = testX - 0.03f;   
							new_counter[0].x = new_counter[12].x - (slongest_line*0.0245f);  

						} 


					}
				   
				}

				// Chance to hit... 
				if(sta2_menu == false)
				if(sta2_is_scrolling == false)
				if(sta2_turn == TURN_PLAYER)   
				if(STA2_MODE == MODE_TARGET && sta2_used_extra == false)   
				if(current_guy != -1 && !mode) 
				{
					distance = 100.0f; 
					 
					if(target_all != -1)
					{
						mid_x = sprite[current_guy].w+sprite[current_guy].box_width/2; 
						mid_y = sprite[current_guy].z+sprite[current_guy].box_height/2; 

						tar_x = sprite[target_all].w+sprite[target_all].box_width/2; 
						tar_y = sprite[target_all].z+sprite[target_all].box_height/2;  

						distance = Node_Distance(mid_x, mid_y, tar_x, tar_y);
					}

					if(sprite[current_guy].value2 >= 0)
						pack_id = sta2_squad[sprite[current_guy].value2].wp;

					new_counter[0].alpha = 1.0f;  
					new_counter[12].alpha = 1.0f;  

					if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
					if(target_all != -1)     
					if(player_type == sprite[target_all].linked_sprite) 
					{  
						if(distance <= 0.3f)
							sprintf( new_counter[0].word, "TO HEAL^AMOUNT %i-%iHP^", 1, STA2_HEAL_AMOUNT + (sta2_pack[pack_id].rank * 20) );
						else
						{
							sprintf( new_counter[0].word, "OUT OF^RANGE!^"); 
							new_counter[0].id = 7;
						} 
					}

					if(target_all == -1)    
						sprintf( new_counter[0].word, "SELECT^TARGET^");

					if(new_counter[0].alpha != 0.0f)          
					{

						testX = hud_mouseX - (-camX);                                                    
						testY = hud_mouseY - (-camY);  

						sprintf( new_counter[12].word, "@", 50);  

						new_counter[0].x = testX + 0.13f;     
						new_counter[0].y = testY + 0.05f;    

						new_counter[12].x = testX + 0.1f;                    
						new_counter[12].y = testY + 0.05f;   
						 
						// For left-sided messages, get longest line...
						if( new_counter[0].x >= sta2_left_of_screen) 
						{ 
							slongest_line = GetLongestLine(new_counter[0].word); 
							   
							new_counter[12].x = testX - 0.03f;   
							new_counter[0].x = new_counter[12].x - (slongest_line*0.0245f);  

						} 
					} 
					  
					if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
					if(target_all != -1) 
					if(distance <= 0.3f)
					if(mouseleft == true)
					if(sta2_pack[pack_id].extra_charge > 0) 
					{
						
						sta2_only_defend = false;
						sta2_only_pistol = false;
						sta2_only_grenade = false;

						mouseleft = false; 
						sta2_used_extra = true;

						if(rand()%100 <= 100)   
						{

							sta2_pack[pack_id].extra_charge--; 

							healup_sfx = true;   

							heal_amount = 1 + rand()%(STA2_HEAL_AMOUNT + (sta2_pack[pack_id].rank * 20));

							if(HEALTHBARS == HEALTHBARS_ON)   
								New_Healthbar(target_all, heal_amount); 

							sprite[target_all].score += heal_amount;    

							DamageNumber(target_all, heal_amount, STA2_DAMAGE_HP); 
						}
						else  
						{
							DamageNumber(target_all, -1, STA2_DAMAGE_MISS); // Miss 
						}
                       
						if(sprite[target_all].score > Calculate_TotalScore(target_all))     
							sprite[target_all].score = Calculate_TotalScore(target_all);     

					}

				}

				// Chance to hit...
				if(sta2_menu == false)
				if(sta2_is_scrolling == false)
				if(sta2_turn == TURN_PLAYER)   
				if(STA2_MODE == MODE_AIMING) 
				if(current_guy != -1 && !mode)   
				{

					testX = hud_mouseX - (-camX);                                                     
					testY = hud_mouseY - (-camY);  

					new_counter[0].x = testX + 0.13f;     
					new_counter[0].y = testY + 0.05f;      

					new_counter[12].x = testX + 0.1f;                    
					new_counter[12].y = testY + 0.05f;  

					new_counter[0].alpha = 0.0f; 
					new_counter[12].alpha = 0.0f;

					if(sprite[current_guy].value2 >= 0)
						pack_id = sta2_squad[sprite[current_guy].value2].wp;

					if(has_grenade_equipped == false && has_mortar_equipped == false)
					if(stored_target != -1) 
					{
						new_counter[0].alpha = 1.0f; 
						new_counter[12].alpha = 1.0f;

						sprintf( new_counter[12].word, "@", 50); 

						if(targeted == TARGET_HEAD)
							sprintf( new_counter[0].word, "HEADSHOT^%i&", GetAccuracy(current_guy, stored_target) );

						if(targeted == TARGET_TORSO)
							sprintf( new_counter[0].word, "TO HIT^%i&", GetAccuracy(current_guy, stored_target) );

						if(targeted == TARGET_LEGS)
							sprintf( new_counter[0].word, "FOOTSHOT^%i&", GetAccuracy(current_guy, stored_target) );
					}
					if(has_mortar_equipped == true)     
					{
						sta2_out_of_range = false;

						new_counter[0].alpha = 1.0f; 
						new_counter[12].alpha = 1.0f;
						
						sprintf( new_counter[12].word, "@", 50); 

						if(stored_target == -1)
							sprintf( new_counter[0].word, "SELECT^TARGET");
						else
							sprintf( new_counter[0].word, "CLICK TO^BOMB!"); 
					}

					if(pack_id >= 0 && pack_id < STA2_PACKS_LIMIT)
					if(has_grenade_equipped == true)  
					{
						sta2_out_of_range = false;

						new_counter[0].alpha = 1.0f;  
						new_counter[12].alpha = 1.0f;

						sprintf( new_counter[12].word, "@", 50); 

						sprintf( new_counter[0].word, "CLICK TO^THROW"); 

						distance = 0.0f;  
					 
						mid_x = sprite[current_guy].w+sprite[current_guy].box_width/2; 
						mid_y = sprite[current_guy].z+sprite[current_guy].box_height/2; 

						tar_x = mouseX;   
						tar_y = mouseY;  

						distance = Node_Distance(mid_x, mid_y, tar_x, tar_y);
						   
						if(distance >= 0.4f)   
						{ 
							new_counter[0].id = 7;
							sprintf( new_counter[12].word, "@", 50); 
							sprintf( new_counter[0].word, "OUT OF^RANGE");
							sta2_out_of_range = true;
						}
						 
						if(sta2_pack[pack_id].extra_charge <= 0)
						{
							new_counter[0].alpha = 0.0f; 
							new_counter[12].alpha = 0.0f; 
						} 

					} 
						 
					// For left-sided messages, get longest line...
					if( new_counter[0].x >= sta2_left_of_screen) 
					{ 
						slongest_line = GetLongestLine(new_counter[0].word); 
							   
						new_counter[12].x = testX - 0.03f;   
						new_counter[0].x = new_counter[12].x - (slongest_line*0.0245f);  

					} 
					 
				}
				
				if(sta2_menu == true) 
				{
					new_counter[0].alpha = 0.0f;
					new_counter[12].alpha = 0.0f;
					new_counter[2].alpha = 0.0f;
				}
				 
				 
			} // current_guy != -1
            
			target_all = -1;
            stored_target = -1;

            hud_corner=true;   
       
            if( ply_id != -1)                
            {
                unit_selected = ply_id;                  
                guy_selected = true;
            }  
                      
            if(game_mode == WALK )                                 
            {         
            
            // Reset ply_pickup_target
            if(mouseleft == true)  
                ply_pickup_target = -1; 
                                  
            // Dump an object if held...     
            if( (hud_corner == true || mouseright == true ) && mouse_grabbed == true 
            && ( mouseleft == true || mouseright == true || DX_SHOOT == true || DX_RELOAD == true) && !(mouse_inv == INV_LETTERS && mouse_inv_value == 31) )     
            {     
                       
			  if(DX_SHOOT == true) 
				DX_SHOOT=false;

			  if(DX_RELOAD == true)
				DX_RELOAD=false;

              test_player = -1; 
              
              if(ply_id != -1 && player_type == p_server) 
              {
                  test_player = ply_id; 
                  testX = sprite[ply_id].w+sprite[ply_id].box_width/2; 
                  testY = sprite[ply_id].z+sprite[ply_id].box_height/2;
              }           
           
               
              if(test_player != -1)                            
              {     
               
                             
                if(near_sell == false || mouse_inv == INV_GOLD)
                if(New_FX(testX, testY, testX, testY, 13, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 3, PKU, 1.0, mouse_inv_value, mouse_inv, FX_STATIC, -1, 2, mouse_inv_value1, mouse_inv_value2, mouse_inv_value3)==true)
                {  
                    if(ply_id != -1)              
                    if(reloading == true)
                    {
                                 
                        ShotIdle(ply_id);      
                                                 
                        sprite[ply_id].anim_state = WAIT;  
                        sprite[ply_id].update = true;                      
                        sprite[ply_id].fire_target = -1;
                                                              
                        reloading = false;
                    }     
                    
                    if(mouse_inv != INV_NONE) 
                        PickUp_Sfx(mouse_inv, mouse_inv_value);    

                        GUN_SPECIAL=0;
                        GUN_SPECIAL2=0;

                    if(mouse_inv == INV_KNIFE_E)
                        current_special = -1;  
    
                    if(mouse_inv == INV_HELMET_E)
                        current_helmet = -1;  
 
                    if(mouse_inv == INV_MEDAL_E)
                        current_medal = -1;  

                    if(mouse_inv == INV_TRAP_E)
                        current_trap = -1;     
                                               
                    if(mouse_inv == INV_BOOT_E)
                        current_boot = -1;  
                                                                                               
                    mouse_inv = INV_NONE;           
                    mouse_inv_value  = 0;
                    mouse_inv_value1 = 0;  
              
                    mouse_grabbed = false;                              
                }
              }         
                             
              Calculate_Inventory();
              Calculate_Bullets();
              Calculate_Stats(); 

			  if(mouseright == true)
	              mouseright = false;

			  if(mouseleft == true)
	              mouseleft = false;  

              mouseheld = false;                                     
                          
            }  
            
            INV_PISTOL_ADD   = 0;      
            INV_RIFLE_ADD    = 0; 
            INV_SHOTGUN_ADD  = 0;
            INV_MACHINE_ADD  = 0;
            INV_HEALTH_ADD   = 0;
			INV_GRENADE_ADD  = 0;
            
            on_vehicle = -1;
            pkp_msg_target = -1;     
              
            if( unit_selected != -1)                  
            for(int i=0;i<new_no_sprites;i++) 
            {         
                             
                k = var5[i];           
               
                // Disables white flash...                     
                if(game_mode == WALK)
				if( k >= 0)
                if(k < TOTAL_NO_SPRITES)
                if(sprite[k].type == UNT)
                { 
                        
                    midX = sprite[k].w+sprite[k].box_width/2; 
                    midY = sprite[k].z+sprite[k].box_height/2;  
             
                    temp_row_x = (int)((midX + map_startX)*10);      
                    temp_row_y = (int)((midY + map_startY)*10); 
                    
            		if( (temp_row_y*MAP_HEIGHT)+temp_row_x >= 0)            
	                    sprite[k].tile_row = (temp_row_y*MAP_HEIGHT)+temp_row_x;
                }
                
                // Disables white flash...                      
                if(game_mode == WALK)
				if( k >= 0)
                if(k < TOTAL_NO_SPRITES) 
                if(sprite[k].flash_target == true 
                && (int)TimerGetTime() > sprite[k].flash_timer)   
                {      
                    sprite[k].flash_target = false;
                    sprite[k].flash_timer  = 0;
                }      
                  
                // Flash guys dead body...     
                if(game_mode == WALK)      
				if( k >= 0)           
                if(k < TOTAL_NO_SPRITES) 
                if(sprite[k].type == UNT || sprite[k].type == BAG || sprite[k].type == DOR)
                if(sprite[k].death_flash == true)
                if(sprite[k].flash_target == false)
                if((int)TimerGetTime() > sprite[k].dflash_timer)  
                {   
                   if(sprite[k].alpha > 0.0f)     
                       sprite[k].alpha = 0.0f;    
                   else
                       sprite[k].alpha = 1.0f;  
                          
                   sprite[k].dflash_timer = (int)TimerGetTime() + 50;
                   
				   sprite[k].flash_no_count++;       
				   
				   if(sprite[k].flash_no_count >= 12)
				       sprite[k].death_flash = false;       
				           
                }  
                
				if( k >= 0)
                if(k < TOTAL_NO_SPRITES)
                if(sprite[k].type == UNT)
                if(sprite[k].death_flash == false)     
                    sprite[k].alpha = 1.0f;
 

				// Start FX's...

                // Flash particles...      
                if(game_mode == WALK)   
				if( k-TOTAL_NO_SPRITES >= 0)              
                if(k >= TOTAL_NO_SPRITES) 
				if(Fx[k-TOTAL_NO_SPRITES].turn_off == false)
				if(k-TOTAL_NO_SPRITES >= 0 && (k-TOTAL_NO_SPRITES) < TOTAL_NO_FX_SPRITES) 
                if(Fx[k-TOTAL_NO_SPRITES].sector == FX_FRAG) 
                if((int)TimerGetTime() > Fx[k-TOTAL_NO_SPRITES].dflash_timer)  
                {   
                   if(Fx[k-TOTAL_NO_SPRITES].alpha > 0.0f)     
                       Fx[k-TOTAL_NO_SPRITES].alpha = 0.0f;    
                   else
                       Fx[k-TOTAL_NO_SPRITES].alpha = 1.0f; 
                          
                   Fx[k-TOTAL_NO_SPRITES].dflash_timer = (int)TimerGetTime() + 50;
				           
                }  
               
                // Disables white flash...                      
                if(game_mode == WALK)  
				if( k-TOTAL_NO_SPRITES >= 0)
                if(k >= TOTAL_NO_SPRITES) 
				if(Fx[k-TOTAL_NO_SPRITES].turn_off == false)
				if(k-TOTAL_NO_SPRITES >= 0 && (k-TOTAL_NO_SPRITES) < TOTAL_NO_FX_SPRITES)
				{
	                if(Fx[k-TOTAL_NO_SPRITES].flash_target == true 
	                && (int)TimerGetTime() > Fx[k-TOTAL_NO_SPRITES].flash_timer)   
	                {      
	                    Fx[k-TOTAL_NO_SPRITES].flash_target = false;
	                    Fx[k-TOTAL_NO_SPRITES].flash_timer  = 0;
               	    } 

				}      
                
                if(game_mode == WALK)
				if(ply_dead == false && on_hud_buttons==false)   
                if(k >= TOTAL_NO_SPRITES) 
                if(k-TOTAL_NO_SPRITES >= 0 && (k-TOTAL_NO_SPRITES) < TOTAL_NO_FX_SPRITES)
                if(Fx[k-TOTAL_NO_SPRITES].mouseover == false)
                if(Fx[k-TOTAL_NO_SPRITES].turn_off == false)
                if(Fx[k-TOTAL_NO_SPRITES].type == PKU || (Fx[k-TOTAL_NO_SPRITES].item_type == INV_MINE && !CONTROLLER) )
                {                  

                //    Fx[k-TOTAL_NO_SPRITES].flash_target = false;
                                                                  
                    if(Fx[k-TOTAL_NO_SPRITES].item_type == INV_PISTOL)
                      INV_PISTOL_ADD += Fx[k-TOTAL_NO_SPRITES].value2;

                    if(Fx[k-TOTAL_NO_SPRITES].item_type == INV_GRENADE)
                      INV_GRENADE_ADD += Fx[k-TOTAL_NO_SPRITES].value2;
                                                                       
                    if(Fx[k-TOTAL_NO_SPRITES].item_type == INV_HGUN_AMMO)
                      INV_PISTOL_ADD += Fx[k-TOTAL_NO_SPRITES].value;
                 
                    if(Fx[k-TOTAL_NO_SPRITES].item_type == INV_AMMO)
                      INV_RIFLE_ADD += Fx[k-TOTAL_NO_SPRITES].value;
                      
                    if(Fx[k-TOTAL_NO_SPRITES].item_type == INV_SHELLS)
                      INV_SHOTGUN_ADD += Fx[k-TOTAL_NO_SPRITES].value;
                      
                    if(Fx[k-TOTAL_NO_SPRITES].item_type == INV_BULLETS)
                      INV_MACHINE_ADD += Fx[k-TOTAL_NO_SPRITES].value;
                                            
                    if(Fx[k-TOTAL_NO_SPRITES].item_type == INV_AMPUOLE)
                      INV_HEALTH_ADD += Fx[k-TOTAL_NO_SPRITES].value;

                    if(Fx[k-TOTAL_NO_SPRITES].item_type == INV_HEALTH)
                      INV_HEALTH_ADD += Fx[k-TOTAL_NO_SPRITES].value;

                    if(Fx[k-TOTAL_NO_SPRITES].item_type == INV_APPLE)
                      INV_HEALTH_ADD += Fx[k-TOTAL_NO_SPRITES].value; 

                    if(Fx[k-TOTAL_NO_SPRITES].item_type == INV_BREAD)
                      INV_HEALTH_ADD += Fx[k-TOTAL_NO_SPRITES].value; 
                                                                  
                    if(Fx[k-TOTAL_NO_SPRITES].item_type == INV_FISH)
                      INV_HEALTH_ADD += Fx[k-TOTAL_NO_SPRITES].value; 

                  fx_offset = Calculate_Offset(false); 
                  
                  midX = Fx[k-TOTAL_NO_SPRITES].width/4; 
                  midY = Fx[k-TOTAL_NO_SPRITES].height/4;
                  
                  widthX  = (Fx[k-TOTAL_NO_SPRITES].x + midX) - (fx_offset);          
                  heightY = (Fx[k-TOTAL_NO_SPRITES].y + midY) - (fx_offset);  
                                   
                  widthX1  = (Fx[k-TOTAL_NO_SPRITES].x + Fx[k-TOTAL_NO_SPRITES].width  - midX) + (fx_offset);    
                  heightY1 = (Fx[k-TOTAL_NO_SPRITES].y + Fx[k-TOTAL_NO_SPRITES].height - midY) + (fx_offset); 
                                        
                  if(on_selected_man != BAD_MAN && on_selected_man != KICK_OBJ)
                  if(ply_id != -1)
                  if(reloading == false)  
				  if(switching_to_weapon == -1)                                     
                  if(( mouseX < widthX1 )                 
                  &&( mouseX > widthX)                                          
                  &&( mouseY < heightY1 )  
                  &&( mouseY > heightY))              
                  {                 

                        on_pickup = true; 
   
                         
                        midX = sprite[ply_id].w+sprite[ply_id].box_width/2; 
                        midY = sprite[ply_id].z+sprite[ply_id].box_height/2;
                        
                        temp_row_x = (int)((midX + map_startX)*10);      
                        temp_row_y = (int)((midY + map_startY)*10);  
     
                        temp_index = (temp_row_y*MAP_HEIGHT)+temp_row_x;  
                            
                        if(mouseheld == false)    
						{ 
                            Fx[k-TOTAL_NO_SPRITES].flash_target = true;  
                            Fx[k-TOTAL_NO_SPRITES].flash_timer = (int)TimerGetTime()+12;
						}
                         
                        pkp_msg_target = k-TOTAL_NO_SPRITES;
                        
                        if(mouseheld == false && reloading == false)
                            Hud_Check();        
                                         
                        // Am I trying to pick it up? 
                        
                        if(mouseleft == true && mouseheld == false)                     
                        {         
                                  
                            if(flash_on >= 0)                     
                            {                 
                                if(flash_on < TOTAL_NO_SPRITES)              
                                   sprite[flash_on].alpha = 1.0f; 
                                else
								{
									if(flash_on-TOTAL_NO_SPRITES >= 0)
                                        Fx[flash_on-TOTAL_NO_SPRITES].alpha = 1.0f; 
								} 
                            } 
                                                                  
                            // Flash the PKU
                            flash_on = k;     

                            target_flash_timer = 0;
                            target_flash_mtimer = (int)TimerGetTime() + FLASH_OBJECT_TIME;                             
                            
                                                 
                            ply_pickup_target = k-TOTAL_NO_SPRITES;  
                             
                            if(ply_id != -1 && ply_pickup_target >= 0)
                            if(Pickup_Check(ply_id, ply_pickup_target, STAND_AND_COLLECT)==false)
							{
							    FX_TOOFAR = true;
							}

                           
                        }                       
                        
                  }          
                                            
                }   
                
                if(k < TOTAL_NO_SPRITES) 
				if(k >= 0)
				if(ply_dead == false && on_hud_buttons==false) 
                if( sprite[k].type == TRI && sprite[k].rank == 1) 
                if(sprite[k].onCreate != -1)
                if(sprite[k].moving == false)
                if( main_mission[sprite[k].linked_sprite] != UNBEATEN
                || sprite[k].linked_sprite == MISSION_NONE 
                || sprite[k].linked_sprite == MISSION_T_COMPLETE
                || sprite[k].linked_sprite == MISSION_T_START)
                if(mouseleft == true)                 
                {
                 
                  widthX = sprite[k].w;          
                  heightY = sprite[k].z;  
                                   
                  widthX1 = sprite[k].w + sprite[k].box_width;    
                  heightY1 = sprite[k].z + sprite[k].box_height; 
                                                      
                  if(( mouseX < widthX1 )        
                  &&( mouseX > widthX)                                         
                  &&( mouseY < heightY1 )                     
                  &&( mouseY > heightY) )      
                  {                       
                    tall_trigger = k;      
                  } 
                    
                }

				if(CONTROLLER)
                if(k < TOTAL_NO_SPRITES) 
				if(k >= 0) 
				if(ply_dead == false) 
                if( sprite[k].type == TRI)  
				if(sprite[k].moving == false)
				if(sprite[k].sector != LVL_CLOSED)
                if(sprite[k].grab_switch == true)
                {
                 
                  widthX = sprite[k].x;          
                  heightY = sprite[k].y;  
                                   
                  widthX1 = sprite[k].x + sprite[k].width;    
                  heightY1 = sprite[k].y + sprite[k].height; 
                                                      
                  if(( mouseX < widthX1 )        
                  &&( mouseX > widthX)                                         
                  &&( mouseY < heightY1 )                     
                  &&( mouseY > heightY) )      
                  {                       
						on_a_trigger = true;
                  }
                    
                } 
                                       
                if(on_selected_man != BAD_MAN) // Let bad_man override                                                 
                if(k < TOTAL_NO_SPRITES) 
				if(k >= 0)
				if(ply_dead == false && on_hud_buttons==false) 
        //        if((reloading == false && switching_to_weapon == -1) || CONTROLLER) // && mouseheld == false 
				if(sprite[k].alpha != 0.0f)
                if( sprite[k].type == DOR || (sprite[k].type == BAG && sprite[k].moving == false)// 
                || (sprite[k].type == OBJ && sprite[k].sector_action == OBJ_SCARE || sprite[k].sector_action == OBJ_RESCUE || sprite[k].sector_action == OBJ_SCARECROW ) 
                )
                if(sprite[k].score > 0)  
                if(sprite[k].priority != 3) 
                if(sprite[k].grab_switch == true)                  
                if(sprite[k].turn_off == false)     
                {          
                                    
                  fx_offset = Calculate_Offset(false); 
                        
                  widthX = sprite[k].w - (fx_offset);          
                  heightY = sprite[k].z - (fx_offset);  
                                   
                  widthX1 = sprite[k].w + sprite[k].box_width + (fx_offset);    
                  heightY1 = sprite[k].z + sprite[k].box_height + (fx_offset); 
                   
                  if( sprite[k].type == BAG)
                  if(sprite[k].sector != UNIT_SEAGULL
                  && sprite[k].sector != UNIT_SEAGULL2
                  && sprite[k].sector != UNIT_TUNNEL)   
                  {
                      widthX = sprite[k].w - (fx_offset);          
                      heightY = sprite[k].z - (fx_offset);  
                                   
                      widthX1 = sprite[k].w + sprite[k].box_width + (fx_offset);    
                      heightY1 = sprite[k].z + (sprite[k].box_height*4) + (fx_offset);   

                  } 
                    
                  if( sprite[k].type == BAG) 
                  if(sprite[k].sector == UNIT_BOSS)    
                  {
                      widthX = sprite[k].w - (fx_offset);          
                      heightY = sprite[k].z - (fx_offset);  
                                   
                      widthX1 = sprite[k].w + sprite[k].box_width + (fx_offset);    
                      heightY1 = sprite[k].z + (sprite[k].box_height*1.5f) + (fx_offset);   

                  } 
                   
                  if( sprite[k].type == BAG) 
                  if(sprite[k].sector == UNIT_ARMOUR_TANK)    
                  {
                      widthX = sprite[k].w;           
                      heightY = sprite[k].z;  
                                   
                      widthX1 = sprite[k].w + sprite[k].box_width;    
                      heightY1 = sprite[k].z + sprite[k].box_height;   

                  } 
                   
                  if( sprite[k].type == BAG)  
                  if(sprite[k].sector == UNIT_ARMOUR_TURRET && sprite[k].rank != 0) // Mauser's small tanks   
                  { 
                      widthX = sprite[k].w;           
                      heightY = sprite[k].z;  
                                   
                      widthX1 = sprite[k].w + sprite[k].box_width;    
                      heightY1 = sprite[k].z + sprite[k].box_height;   

                  } 
                                    
                  if( sprite[k].type == DOR)
                  if( sprite[k].sector_action == TYPE_BARREL)
                  {
                      widthX = sprite[k].w - (fx_offset);          
                      heightY = sprite[k].z - (fx_offset);  
                                   
                      widthX1 = sprite[k].w + sprite[k].box_width + (fx_offset);    
                      heightY1 = sprite[k].z + (sprite[k].box_height*3) + (fx_offset);   
                  }
                   
                  if( sprite[k].type == DOR)
                  if( sprite[k].sector_action == TYPE_SINGLE_DOOR)
                  {
 
                      fx_offset = sprite[k].box_width;
                                        
                      widthX = sprite[k].w - (fx_offset);          
                      heightY = sprite[k].z - (fx_offset);   
                                   
                      widthX1 = sprite[k].w + sprite[k].box_width + (fx_offset);    
                      heightY1 = sprite[k].z + (sprite[k].box_height*5) + (fx_offset);   
                  }
                                    
                  if( sprite[k].type == DOR)
                  if( sprite[k].sector_action == TYPE_DOUBLE 
                  || sprite[k].sector_action == TYPE_DOUBLE_BACK)
                  {
                      widthX = sprite[k].x + (fx_offset);          
                      heightY = sprite[k].y + sprite[k].box_height;  
                                   
                      widthX1 = sprite[k].x + sprite[k].width - (fx_offset);    
                      heightY1 = sprite[k].y + (sprite[k].height - sprite[k].box_height);   
                  }
 				   
                  if(( mouseX < widthX1 + mouse_DX_Offset )                                  
                  &&( mouseX > widthX - mouse_DX_Offset)                                              
                  &&( mouseY < heightY1 + mouse_DX_Offset )                                                           
                  &&( mouseY > heightY -mouse_DX_Offset )) 
				  if(sprite[k].score > 0)
					DX_ON_TARGET = true;

                  if(( mouseX < widthX1 )        
                  &&( mouseX > widthX)                                         
                  &&( mouseY < heightY1 )                     
                  &&( mouseY > heightY) )      
                  {     
                         
                        on_pickup = false;

                        if(sprite[k].type != BAG)
                        {              
                            on_selected_man = KICK_OBJ; 
                            stored_target = k;  
							target_all = k;
                            targeted = TARGET_TORSO;  
                        }   
						 
						if(mouseleft == true)
						{
							SPRITE_NOWEAPON=true;
						}

                  }  
                                      
                }  
                
                if(on_selected_man != BAD_MAN) // Let bad_man override 
				if(ply_dead == false && on_hud_buttons==false)  
           //     if( (reloading == false && switching_to_weapon == -1) || CONTROLLER)                               
                if(k < TOTAL_NO_SPRITES) 
				if(k >= 0)
                if( sprite[k].type == LAD)
                if( sprite[k].grab_switch == true)                  
                if(sprite[k].turn_off == false) 
				if(sprite[k].moving == false) 
                { 
  
                  widthX = sprite[k].x; 
                  heightY = sprite[k].y;                  
                  widthX1 = sprite[k].w + sprite[k].box_width;
                  heightY1 = sprite[k].z + sprite[k].box_height;                      
                                    
                  if(( mouseX < widthX1 )        
                  &&( mouseX > widthX)                                         
                  &&( mouseY < heightY1 )                 
                  &&( mouseY > heightY))    
                  {                  
                        on_selected_man = LADDER; 

						if(CONTROLLER) 
							on_a_trigger = true;

                        stored_target = k;  
						target_all = k;
                  }                                        
                                        
                }    
				 
                if(!CONTROLLER)            
                if(on_selected_man != BAD_MAN) // Let bad_man override    
				if(ply_dead == false && on_hud_buttons==false)                                                                            
                if(k < TOTAL_NO_SPRITES && k >= 0)   
				if(sprite[k].alpha != 0.0f)  
                if( sprite[k].type == OBJ)   
             //   if( (reloading == false && switching_to_weapon == -1 && mouseheld == false) || CONTROLLER)                  
                if(sprite[k].mouseover == false)
                if(sprite[k].sector_action != OBJ_NONE 
				&& sprite[k].sector_action != -1
                && sprite[k].sector_action != OBJ_SHOP 
				&& sprite[k].sector_action != OBJ_OBSTACLE
                && sprite[k].sector_action != OBJ_LIGHT
                && sprite[k].sector_action != OBJ_NOCOL  
                && (sprite[k].sector_action != OBJ_SEAGULL && sprite[k].linked_sprite != LINKED_DOG)
                && (sprite[k].sector_action != OBJ_SEAGULL2 && sprite[k].linked_sprite != LINKED_DOG)
                && sprite[k].sector_action != OBJ_VAN_SHADOW
                && sprite[k].sector_action != OBJ_SCARE
                )    
                if( sprite[k].score > 0)                       
                if(sprite[k].turn_off == false) 
                {            
                                                                       
                  fx_offset = Calculate_Offset(false);
                         
                  widthX  = sprite[k].w - (fx_offset);     
                  heightY = sprite[k].z - (fx_offset);          
             
                  widthX1  = sprite[k].w + sprite[k].box_width + (fx_offset);
                  heightY1 = sprite[k].z + (sprite[k].box_height*4) + (fx_offset); 
                                       
                  if( in_open_world == false)
                  if( sprite[k].sector_action == OBJ_LIGHT1)
                  {
                      widthX = sprite[k].w - (fx_offset);          
                      heightY = sprite[k].z - (fx_offset);  
                                   
                      widthX1  = sprite[k].w + sprite[k].box_width + (fx_offset);
                      heightY1 = sprite[k].z + (sprite[k].box_height*2) + (fx_offset);  
                      
                      heightY += (sprite[k].box_height*4); 
                      heightY1 += (sprite[k].box_height*4); 
                      
                  }
                                       
                  if( in_open_world == false)
                  if( sprite[k].sector_action == OBJ_SWITCH)
                  {
                      widthX = sprite[k].w - (fx_offset);          
                      heightY = sprite[k].z - (fx_offset);  
                                   
                      widthX1  = sprite[k].w + sprite[k].box_width + (fx_offset);
                      heightY1 = sprite[k].z + (sprite[k].box_height*2) + (fx_offset);  
                      
                      heightY += (sprite[k].box_height*4); 
                      heightY1 += (sprite[k].box_height*4); 
                      
                  }
                                                             
                  if(( mouseX < widthX1 )           
                  &&( mouseX > widthX)                                             
                  &&( mouseY < heightY1 )                  
                  &&( mouseY > heightY))      
                  {                  
                        on_selected_man = TALK_MAN; 

                        stored_target = k;  
						target_all = k;
                        on_pickup = true;
						    
						if(ply_id != -1 && mouseleft == true)
						{
							midX = sprite[ply_id].w+sprite[ply_id].box_width/2;
							midY = sprite[ply_id].z+sprite[ply_id].box_height/2;     
                 
							tarX = sprite[k].w + sprite[k].box_width/2;
							tarY = sprite[k].z + sprite[k].box_height/2; 
    
							closest_point = (float)talk_rng; 
        
							if(sprite[k].sector_action == OBJ_INFO  
							|| sprite[k].sector_action == OBJ_DANCER 
							|| sprite[k].sector_action == OBJ_DANCER1)
								closest_point = (float)widetalk_rng;

							dis_to_point = Node_Distance(midX, midY, tarX, tarY);    

							if(ply_id != -1)
							if( dis_to_point >= closest_point)
							{
								TALKMAN_TOOFAR = true;
							}
						}

                  }          
                                            
                }                
                                  
                if(k < TOTAL_NO_SPRITES && k >= 0)     
				if(ply_dead == false && on_hud_buttons==false) 
            //    if( (reloading == false && switching_to_weapon == -1) || CONTROLLER)                            
                if(sprite[k].type == UNT && sprite[k].mouseover == false)
                if(!(sprite[k].sector == UNIT_DUCK && sprite[k].status == IDLE))
				if(sprite[k].sector != UNIT_DECOY || !CONTROLLER) 
                if(sprite[k].sector != UNIT_BIRD) 
                if(sprite[k].status != MAN_DOWN)      
                if(sprite[k].status != MAN_DOWN1)                            
                if(sprite[k].status != MAN_DOWN2)
                if(sprite[k].status != DEATH_READY)
                if(sprite[k].status != GRAVESTONE)
                if(sprite[k].onDeath_action != TANK_TOP)                
                if(sprite[k].turn_off == false)     
                {            
                                                                       
                  fx_offset = Calculate_Offset(false);     
                       
                  widthX  = sprite[k].w - (fx_offset);          
                  heightY = sprite[k].z - (fx_offset);  
                                   
                  widthX1  = sprite[k].w + sprite[k].box_width + (fx_offset);    
                  heightY1 = sprite[k].z + (sprite[k].box_height*4) + (fx_offset); 


				  if(sta2_environment_type == AREA_GRASSLANDS)
				  if(sprite[k].depth != 0.0)
					  heightY1 = sprite[k].z + (sprite[k].box_height*2) + (fx_offset);

            /*      if(sprite[k].sector == UNIT_MONKEY)
                  {  
                      widthX = sprite[k].w - (fx_offset);          
                      heightY = sprite[k].z - (fx_offset);  
                                   
                      widthX1 = sprite[k].w + sprite[k].box_width + (fx_offset);    
                      heightY1 = sprite[k].z + (sprite[k].box_height) + (fx_offset);   
                  }                  

                  if(sprite[k].sector == UNIT_DOG)
                  {  
                      widthX = sprite[k].w - (fx_offset);          
                      heightY = sprite[k].z - (fx_offset);  
                                   
                      widthX1 = sprite[k].w + sprite[k].box_width + (fx_offset);    
                      heightY1 = sprite[k].z + (sprite[k].box_height) + (fx_offset);   
                  }     */
				   
                  if(( mouseX < widthX1 + mouse_DX_Offset )                                 
                  &&( mouseX > widthX - mouse_DX_Offset)                                                 
                  &&( mouseY < heightY1 + mouse_DX_Offset )                                                           
                  &&( mouseY > heightY - mouse_DX_Offset ))  
				  if(player_type != sprite[k].linked_sprite)
				  if(sprite[k].score > 0)
					DX_ON_TARGET = true;

                  if(( mouseX < widthX1 )                                 
                  &&( mouseX > widthX)                                              
                  &&( mouseY < heightY1 )                                                             
                  &&( mouseY > heightY ))                      
                  {                
					    

				//	if(k != p1_id || FACEBARS == FACEBARS_OFF) 
					if(HEALTHBARS == HEALTHBARS_ON)
				        New_Healthbar(k, 1);
                    
					target_all = k;

                    if(player_type != sprite[k].linked_sprite)
                    {            

                        on_selected_man = BAD_MAN; 
                        
                        if(sprite[k].score > 0)       
                            on_pickup = false; 
                         
                        stored_target = k;       
                           
                        targeted = TARGET_LEGS;      

						if(sta2_environment_type == AREA_GRASSLANDS) 
						if(sprite[k].depth != 0.0)
	                        targeted = TARGET_TORSO;     
                        
                        if(mouseY > sprite[k].z + sprite[k].box_height)
                            targeted = TARGET_TORSO; 
                                                  
						if(sta2_environment_type == AREA_GRASSLANDS && sprite[k].depth != 0.0)
                        if(mouseY > sprite[k].z + (sprite[k].box_height*1.5)) 
						if( mouseX < widthX1 - (fx_offset/2) 
						&& mouseX > widthX + (fx_offset/2) )
                            targeted = TARGET_HEAD;   
                        else
                        {
						    on_selected_man = NO_MAN;
  
        					stored_target = -1; 	 
						}

						if(sta2_environment_type != AREA_GRASSLANDS || sprite[k].depth == 0.0)
                        if(mouseY > sprite[k].z + (sprite[k].box_height*3.5)) 
						if( mouseX < widthX1 - (fx_offset/2) 
						&& mouseX > widthX + (fx_offset/2) )
                            targeted = TARGET_HEAD;   
                        else
                        {
						    on_selected_man = NO_MAN;
  
        					stored_target = -1; 	
						}
                             
                        if(sprite[k].sector == UNIT_MONKEY)
                            targeted = TARGET_TORSO;     
                             
                        if(sprite[k].sector == UNIT_DOG) 
                            targeted = TARGET_TORSO;  
                                                            
                        if(has_machine_equipped == true && has_sight == false)
                            targeted = TARGET_TORSO;  
                                
                        if(has_shotgun_equipped == true)
                            targeted = TARGET_TORSO;
                                                                                                             
                    } // player_type != sprite[k].linked_sprit
					else
					{

						if(sprite[k].sector == UNIT_DECOY)
						if(ply_id != -1)
						{
						    on_selected_man = TALK_MAN;
	                        stored_target = k;    
	                        on_pickup = true;
 
             				mid_x = sprite[ply_id].w + sprite[ply_id].box_width/2;
       					    mid_y = sprite[ply_id].z + sprite[ply_id].box_height/2;
             
             				tar_x = sprite[k].w + sprite[k].box_width/2;  
             				tar_y = sprite[k].z + sprite[k].box_height/2;
 
             				if(mouseleft == true || DX_USECOLLECT == true)   
             				if(Node_Distance1(mid_x, mid_y, tar_x, tar_y) < (float)COLLECT_RANGE)
							{
								if(Calculate_Item(TRAP_TYPE_DECOY, INV_TRAP, -1, 0, 1, sprite[k].score))
			 					{

									DX_USECOLLECT = false;

                 					temp_row_x = (int)((tar_x + map_startX)*10);       
                 					temp_row_y = (int)((tar_y + map_startY)*10);   

           		 					if( (temp_row_y*MAP_HEIGHT)+temp_row_x > 0 && (temp_row_y*MAP_HEIGHT)+temp_row_x < MAP_TILES)
				 					if( map_col[(temp_row_y*MAP_HEIGHT)+temp_row_x] == 6)
	                 					map_col[(temp_row_y*MAP_HEIGHT)+temp_row_x] = 0; 
 
 			     					sprite[k].status = MAN_DOWN1;   
				 					sprite[k].all_timer = 0;  
				 					sprite[k].score = 0; 

			     					stored_target = -1;

									on_selected_man = NO_MAN;
									on_pickup = false;

				 					mgun_sfx = true;
				 					mouseleft = false;
			 					}
							}
							else 
							{ 
								if(ply_id != -1)
								{
									TALKMAN_TOOFAR = true;
								}
							}

						}
					} 
   
                      
                  } 
                                        
                }       
                                                                         
            }           
			  
               Run_Keyboard(f_rate1);      

			   hud[41].alpha = 0.0f; 

			   // Setup mouse arrow...
              Set_Sprite(1, 0, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Large White circle

			  if(sta2_turn == TURN_PLAYER)
			  if(game_mode == WALK)    
			  {
				  if(STA2_MODE == MODE_MOVING)
					  Set_Sprite(1, 0, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Hand
				  if(STA2_MODE == MODE_AIMING)
				  {   
					     
					  hud[41].x = hud[1].x - hud[41].width/6.0f; 
					  hud[41].y = hud[1].y + hud[41].width/5.5f; 

					  Set_Sprite(1, 1, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Large White circle
					  Set_Sprite(41, 3, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Large White circle

					  // Add directions to enemies...  
					  if(ply_id  -1) 
					  {
						  found_a_target = -1;
						  closest_point = 10000.0f;  

						  mid_x = mouseX;                                                      
						  mid_y = mouseY;  
						   
						  // Get nearest enemy....   
						  for(int i = 0;i < no_sprites;i++)
						  if(sprite[i].type == UNT)
						  if(sprite[i].linked_sprite != player_type) 
						  if(sprite[i].score > 0) 
						  {

							  tar_x = sprite[i].w + sprite[i].box_width/2;    
							  tar_y = sprite[i].z + sprite[i].box_height/2;    

							  dis_to_point = Node_Distance1(mid_x, mid_y, tar_x, tar_y); 

							  if(dis_to_point < closest_point) 
							  { 
								  closest_point = dis_to_point;
								  found_a_target = i;
							  }  

						  }  

						  if(found_a_target != -1) 
						  {   
							  hud[41].alpha = 1.0f;   

							  tar_x = sprite[found_a_target].w + sprite[found_a_target].box_width/2;    
							  tar_y = sprite[found_a_target].z + sprite[found_a_target].box_height/2;   

							  angle =  atan2(tar_y - mid_y,tar_x - mid_x); 

							  hud[41].anim = 2 + Convert_Angle_To_Dir(angle);
							  Set_Sprite(41, hud[41].anim, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Large White circle

							  dis_to_point = Node_Distance1(mid_x, mid_y, tar_x, tar_y); 

							  if(dis_to_point <= 0.2f)
								  hud[41].alpha = 0.0f;

						  }
						  

					  }


				  }
				  if(on_selected_man == BAD_MAN)
				  {
					  hud[41].alpha = 0.0f;
 					  Set_Sprite(1, 2, LOOP, ANIM_HUD, ANIM_NOT_WALKING); // Red dot
				  }

			  }

			  if((int)TimerGetTime() > ray_timer) 	 
				  ray_timer = (int)TimerGetTime() + 4;
                   
          
            if(game_mode != FRONT && mouse_stop == false && cutscene == false)                  
            {    
              ply_sniping = true;   
            }     
                                               
        }      

		}
         
        mouseleftcheck = false;  
        mousequickleft = false;     
        
     
} 

bool Get_Next_Tile(int k, float x2, float y2)
{
    
    bool success=true;  
    float x1=0.0f, y1=0.0f;
    float angle=0.0f, deltax=0.0f, deltay=0.0f;
    float mid_x=0.0f, mid_y =0.0f;
    float tar_x=0.0f, tar_y =0.0f;  
    float step=0, distance=0.0f; 
    int row_x=0, row_y=0;
    int free_tile_x=0, free_tile_y=0;
    int the_row=0;
    int free_tile=-1;
    int iterations=0;
    bool hit_collision=false;
    float x=0.0f, y=0.0f;
    int temp_row_x=0, temp_row_y=0;
    int index = 0;
	int stored_col = 0;
        
    x1 = sprite[k].w + sprite[k].box_width/2;
    y1 = sprite[k].z + sprite[k].box_height/2;
    
    x = x1;
    y = y1; 
     
    temp_row_x = (int)((x1 + map_startX)*10);        
    temp_row_y = (int)((y1 + map_startY)*10);  
     
    index = (temp_row_y*MAP_HEIGHT)+temp_row_x;          

	if(index < 0)
		index = 0;

	stored_col = map_col[index];

    map_col[index] = 0; 
        
    distance = Node_Distance1(x1, y1, x2, y2); 
     
    distance = (float)COL_CHAR_OFFSET; 
      
    // Shoot ray to x, y...get free tile, repeat.  
              
    angle = atan2(y2 - y1,x2 - x1);     
    
    deltax = cos(angle);    
    deltay = sin(angle);  
        
    deltax *= (float)LINE_OF_SIGHT;     
    deltay *= (float)LINE_OF_SIGHT;
        
    step = Node_Distance1(x1, y1, x1+deltax, y1+deltay);      
    
    if( step != 0)
        iterations = (int)(distance / step);
      
    if(iterations < 0)  
        iterations = 0;  
             
    for (int j = 0; j <= iterations; j++) 
    {
          
        x += deltax; // Which is the mid_x
        y += deltay; // Which is the mid_y      

        row_x = (int)((x + map_startX)*10);     
        row_y = (int)((y + map_startY)*10);    
    
        the_row = (row_y*MAP_HEIGHT)+row_x;     

		if(the_row < 0)
			the_row = 0;  

	        if( map_col[the_row] != 0 && map_col[the_row] != 9)   
	        {
	            success = false;                
	            break;
	        }
	        else
	        {
	            free_tile_x = row_x; 
	            free_tile_y = row_y;
    	        players_tile = the_row;
	        }
    
    } 

    map_col[index] = stored_col; 
    
    return(success);      
      
}
 
 
float Calculate_Offset(bool is_a_sprite)
{
    float offset=0.0f;  
                    
    if(is_a_sprite == false)
    {
                      
        offset = 0.05f;    
        
  /*      if(ply_id != -1)                                                                                        
        if(sprite[ply_id].factor < 1.0f)
            offset = 0.05f;
             
        if(ply_id != -1)             
        if(sprite[ply_id].factor < 0.75f)
            offset = 0.07f;  */
            
        mouse_enlarge = offset;   
            
    } 
    
    return(offset);     
}

void Run_Mouse_Limits(int f_rate)
{
    float testX=0.0f,testY=0.0f;  
    float midX=0.0f, midY=0.0f;
    float tarX=0.0f, tarY=0.0f; 
    float diffX=0.0f, diffY=0.0f;
    float deltax=0.0f, deltay=0.0f;
    bool go_aheadX=true;
    bool go_aheadY=true;
	bool run_scroll=false;

	if(STA2_MODE == MODE_MOVING)
	{

		tarX = mouseX;      
		tarY = mouseY; 
                  
		if(ply_id != -1) 
		{
			midX = sprite[ply_id].x + (sprite[ply_id].width/2);      
			midY = sprite[ply_id].y + (sprite[ply_id].height/2) - (sprite[ply_id].box_height); 
		}
                  
		diffX = (midX - tarX);  
		diffY = (midY - tarY);
               
		// ***************************************************************************************//   
		//                                                                                        //                                                                                         
		// Cursor moves in realtime, however the BG has a catch-up delay based on cosine...grrr.  //
		//                                                                                        //
		// ***************************************************************************************//   
                   
		diffX /= 40.0f; // was 60  
		diffY /= 30.0f; // was 50 
                      
		deltax = 0.0f;   
		deltay = 0.0f;   
                   
		camX_OFFSET = 0.0f; 
		camY_OFFSET = 0.0f;     
    
		for(int i=0;i<20;i++) 
		{  
                           
			deltax += diffX; 
			deltay += diffY;  
                        
			go_aheadX = true;   
			go_aheadY = true;   
                       
			testX = -( midX - deltax);   
			testY = -( midY - deltay); 
                           
			if( testX > ( map_startX-zoom_factor) )       
				go_aheadX = false;      
                           
			if( testX < -(MAP_WIDTH*0.05f) + zoom_factor)
				go_aheadX = false;       
                        
			// Offset for Hud at bottom of map                      
			if(testY > map_startY-((zoom_factor*sc_ratio)) ) // -((zoom_factor*sc_ratio)/4)  
				go_aheadY = false;
                           
			if( testY < -(MAP_HEIGHT*0.05f) + (zoom_factor*sc_ratio))
				go_aheadY = false;                     
                       
			if(go_aheadX == true) 
			{
				camX_OFFSET += diffX; // *(float)f_rate
			}   
                         
			if(go_aheadY == true)   
			{
				camY_OFFSET += diffY; // *(float)f_rate
			}  
                    
		}   
            
		if( camX_OFFSET >= 0.3f) // 0.3 
			camX_OFFSET = 0.3f;
                        
		if( camX_OFFSET <= -0.3f)  
			camX_OFFSET = -0.3f;
                   
		if( camY_OFFSET >= 0.35f) // 0.4
			camY_OFFSET = 0.35f;
                       
		if( camY_OFFSET <= -0.35f)
			camY_OFFSET = -0.35f;   

	} // STA2_MODE == MODE_MOVING
	    
	sta2_is_scrolling = false; 
	       
	if(screen_mode == SCREEN_169_WIDESCREEN)
	if( (mouseX > (-camX) + 0.6f) || (mouseX < (-camX) - 0.6f) || (mouseY > (-camY) + 0.3f) || (mouseY < (-camY) - 0.3f) ) 	
		run_scroll = true;

	if(screen_mode == SCREEN_1610_WIDESCREEN) 
	if( (mouseX > (-camX) + 0.5f) || (mouseX < (-camX) - 0.5f) || (mouseY > (-camY) + 0.3f) || (mouseY < (-camY) - 0.3f) ) 	
		run_scroll = true;

	if(STA2_MODE == MODE_AIMING || STA2_MODE == MODE_TARGET)
	if( run_scroll == true ) 
	{

		sta2_is_scrolling = true;

		sta2_globalY = -(camY) - mouseY; // -0.4 - 0.4
		 
		sta2_globalY /= -0.8f;           
		   
		if(sta2_globalY > 1.0f)   
			sta2_globalY = 1.0f;    
		   
		if(sta2_globalY < -1.0f)  
			sta2_globalY = -1.0f; 
			 
		camY -= (0.0022f*sta2_globalY)*(float)f_rate;
		mouseY += (0.0022f*sta2_globalY)*(float)f_rate;

		sta2_globalX = -(camX) - mouseX; // -0.7 - 0.7

		sta2_globalX /= -0.8f;         
		 
		if(sta2_globalX > 1.0f)     
			sta2_globalX = 1.0f;  
		 
		if(sta2_globalX < -1.0f)
			sta2_globalX = -1.0f;

		camX -= (0.0018f*sta2_globalX)*(float)f_rate;
		mouseX += (0.0018f*sta2_globalX)*(float)f_rate;

	} 
                   
    Get_Mouse_Row(); 

}


int GetAccuracy(int loop, int target)
{

    float x1=0.0f, y1=0.0f; 
    float x2=0.0f, y2=0.0f;       
    float angle=0.0f, deltax=0.0f, deltay=0.0f;       
    float mid_x=0.0f, mid_y =0.0f;
    float tar_x=0.0f, tar_y =0.0f;
    float step=0.0f, distance=0.0f;  
	float ftemp=0.0f, convert=0.0f;
	float range = 3.0f;
	int percent = 100;
	bool is_defending = true;
	int pack_id=-1;

	if(loop < 0)
		return(0);
	 
	if(target < 0) 
		return(0);

	if(loop != -1 && target != -1) 
	{ 

		if(loop == ply_id || loop == emy_id)
			is_defending = false;

		x1 = sprite[loop].w + sprite[loop].box_width/2;
		y1 = sprite[loop].z + sprite[loop].box_height/2;

		x2 = sprite[target].w + sprite[target].box_width/2;
		y2 = sprite[target].z + sprite[target].box_height/2;

		distance = Node_Distance1(x1, y1, x2, y2);  // 0.0 - 6.0 is width of map...
		 
		if(sprite[loop].linked_sprite != player_type || is_defending == true )  
		{
			range = 1.8f; 
			 
			if(sprite[loop].sector == UNIT_SNIPER) 
				range = 3.8f;   
		}
		else 
		{  
			if(sprite[loop].sector == UNIT_SNIPER) 
			{
				if(has_pistol_equipped == true)
					range = 3.5f;
				else
					range = 5.0f;
			}
			if(sprite[loop].sector == UNIT_GUNNER)
				range = 3.5f;
			if(sprite[loop].sector == UNIT_HEAVY)
				range = 1.75f; 
		}

		if(distance > range)
			distance = range;  

		convert = range / 1.57f;

		// Scout..
		ftemp = distance / convert;     

		distance = cos(ftemp); 

		percent = (int)( distance * 100.0f);
		  
		if(loop == ply_id)     
		{     

			if(has_shotgun_equipped == true || has_machine_equipped == true)
				targeted = TARGET_TORSO;

			if(targeted == TARGET_HEAD) 
			{
				if(sprite[loop].sector == UNIT_SNIPER)
					percent = (int)(percent - (percent/5));
				else
					percent = (int)(percent - (percent/5));
			}
			 
			if(targeted == TARGET_TORSO)  
				percent = (int)percent;  

			if(targeted == TARGET_LEGS)
				percent = (int)(percent - (percent/5));

			if(sprite[target].sector == UNIT_DOG)
				percent = (int)(percent - (percent/4));

		}
		else
			percent = (int)percent;

		if(percent <= 0)
			percent = 1;

	}

	if(sprite[target].sector == UNIT_DOG) 
	if(percent > 75)
		percent = 75; 

	if(sprite[loop].sector == UNIT_DOG) 
	if(percent > 75)
		percent = 75;

	// Accuracy buff...
	if(ply_id != -1) 
	if(sprite[loop].linked_sprite == player_type) 
	if(sprite[loop].value2 >= 0)
	{

		pack_id = sta2_squad[sprite[loop].value2].wp;

		if(pack_id > -1) 
		if(sta2_pack[pack_id].special_charge > 0)  
		{
			if(sta2_pack[pack_id].special == PACK_SPECIAL_SCOPE)
			{
				percent += 8; 

				if(percent >= 100)    
					percent = 99;   
			}

			if(sta2_pack[pack_id].special == PACK_SPECIAL_GODEYE)
				percent = 99;

			if(sta2_pack[pack_id].special == PACK_SPECIAL_DEATHBLOW)
			{
				percent /= 2;

				if(percent <= 0)
					percent = 1;
			}
		}

	}

	return(percent);

}