#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64 
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#endif 

extern void Refresh_Window();
extern bool New_FX(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int i_value, int i_type, int state, int linked_sprite, int tex_id, int i_value1, int i_value2, int i_value3);

bool Run_Casino(int f_rate);

int display_players_cards=0;
int display_dealers_cards=0;

int player_card_index = 3;
int dealers_card_index = 10;

int sta2_player_aces = 0;
int sta2_dealer_aces = 0;

int sta2_player_value = 0;
int sta2_dealer_value = 0;

int increment = 0;

#define CARD_PLAYER_TURN  0
#define CARD_DEALER_TURN  1

bool card_turn = CARD_PLAYER_TURN;

int sta2_bet = 5;
int sta2_current_bet = sta2_bet;

int cards_dealt = 0;

int Card_Time=0;   
int Card_Time1=0;

int Get_Bet_Amount()
{
	int value=0;

	if(sta2_sector == 1 || sta2_sector == 2)
		value = 5;

	if(sta2_sector == 3 || sta2_sector == 4)
		value = 10;

	if(sta2_sector == 5 || sta2_sector == 6)
		value = 15;

	if(sta2_sector == 7 || sta2_sector == 8)
		value = 20;

	value = 5;

	return(value);

}

int Get_Card_Value(int value)
{

    int success = value; 
	int low_value = 0;
	int high_value = 0;

	if(value == CARD_PLAYER_TURN) 
	{
		low_value = sta2_player_value;
		high_value = sta2_player_value;
	}

	if(value == CARD_DEALER_TURN) 
	{
		low_value = sta2_dealer_value;
		high_value = sta2_dealer_value;
	}

	// Has no aces... 
	if(value == CARD_DEALER_TURN)
	if(sta2_dealer_aces > 0) 
	{
		low_value += sta2_dealer_aces;
		high_value += 10 + (sta2_dealer_aces);
	}

	// Has no aces... 
	if(value == CARD_PLAYER_TURN)
	if(sta2_player_aces > 0) 
	{
		low_value += sta2_player_aces; 
		high_value += 10 + (sta2_player_aces);
	}

	if(high_value >= 22)   
		high_value = 0;

	if(high_value == 0) 
		success = low_value;
	else 
		success = high_value;

    return(success);
    
}

int Calculate_Cards(int value, int value2, bool check_total)
{

    int total_cards=0;
    bool single_card = false;
    
    if( check_total == true && num_players_cards == 1)
        single_card = true;
        
    if( check_total == false && num_dealers_cards == 1) 
        single_card = true;
                        
    if(value2 >= 2)
    {    
        total_cards = value2*1;
    }
    else 
    { 
        if(value > 11)
            total_cards = value2*1;
        else
            total_cards = value2*11;
        
    }
     
    if(value == 10 && value2 == 1 && single_card == true)
        total_cards = 101; // Blackjack
    else
        total_cards += value;
     
    return(total_cards);    
      
}

bool Run_Casino(int f_rate) 
{  
	bool success=true;
	float testX=0.0f, testY=0.0f;  
	float midX=0.0f, midY=0.0f;
	float incY=0.0f;
	int rnd=0;
	int index=0; 
	int index1=0;
	int slongest_line=0;
	char string_value[1024]; 

    // ******************************************************************************//
    //                         1-26  (CASINO BLACKJACK)                              //
    // ******************************************************************************//
        
	if(episode == 1 && scene == 26)
	if(!mode) 
	if(next_scene == false)
	{

    if(title_sequence == 0)      
    { 

		sta2_bet =  Get_Bet_Amount();

		sta2_current_bet = sta2_bet;

		sta2_1_pressed = false;
		sta2_2_pressed = false;
		sta2_3_pressed = false;
		sta2_esc_pressed = false;

		sprite[17].alpha = 0.0f;

		sta2_player_value = 0;
		sta2_dealer_value = 0;	

		sta2_player_aces = 0;
		sta2_dealer_aces = 0;

		card_turn = CARD_PLAYER_TURN;

		cards_dealt = 0;

		player_card_index = 3;
		dealers_card_index = 10;

		sprintf( new_counter[0].word, "3 : QUIT");  

		new_counter[0].alpha = 1.0f;                 
		new_counter[0].id = 0;  

		if(screen_mode == SCREEN_1610_WIDESCREEN)
			new_counter[0].x = 0.43f;          
		else
			new_counter[0].x = 0.45f;   

		new_counter[0].y = -0.34f;  	      

		new_counter[0].w = new_counter[0].x - 0.026f;   
		new_counter[0].z = new_counter[0].y - 0.015f;

		new_counter[0].box_width = strlen(new_counter[0].word)   *  0.026f;
		new_counter[0].box_height = new_counter[0].height - 0.015f;	
	
		sprintf( new_counter[1].word, "1 : CARD");  

		new_counter[1].alpha = 1.0f;         
		new_counter[1].id = 0; 
		       
		new_counter[1].x = -0.60f;     
		new_counter[1].y = -0.34f;  	      

		new_counter[1].w = new_counter[1].x - 0.026f;   
		new_counter[1].z = new_counter[1].y - 0.015f;

		new_counter[1].box_width = strlen(new_counter[1].word)   *  0.026f;
		new_counter[1].box_height = new_counter[1].height - 0.015f;	

		sprintf( new_counter[2].word, "2 : STICK");  

		new_counter[2].alpha = 1.0f;        
		new_counter[2].id = 0;  
		       
		new_counter[2].x = -0.10f;     
		new_counter[2].y = -0.34f;  	      

		new_counter[2].w = new_counter[2].x - 0.026f;   
		new_counter[2].z = new_counter[2].y - 0.015f;

		new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
		new_counter[2].box_height = new_counter[2].height - 0.015f;	
		
		new_counter[3].id = 0; 
		             
		if(screen_mode == SCREEN_1610_WIDESCREEN) 
			new_counter[3].x = -0.60f;        
		else
			new_counter[3].x = -0.65f;       

		new_counter[3].y = 0.36f; 	  
		 
		new_counter[4].id = 0;   
		             
		if(screen_mode == SCREEN_1610_WIDESCREEN)
			new_counter[4].x = 0.38f;      
		else
			new_counter[4].x = 0.42f;      

		new_counter[4].y = 0.36f; 	  

		new_counter[6].alpha = 0.0f;              
		new_counter[6].id = 0;  
		     
		new_counter[6].x = 0.28f;     
		new_counter[6].y = 0.37f; 

		new_counter[15].alpha = 0.0f;              
		new_counter[15].id = 0;  

		new_counter[15].x = 0.52f;          
		new_counter[15].y = 0.37f;

		card_decision = DEAL_NONE;
		title_timer = (int)TimerGetTime()+Card_Time;

		// Player cards...
		for(int i = 3; i<10;i++)
			sprite[i].alpha = 0.0f;

		// Dealers cards... 
		for(int i = 10; i<17;i++)
			sprite[i].alpha = 0.0f;
		 
		title_sequence++;
	}

	new_counter[0].alpha = 0.0f;   
	new_counter[1].alpha = 0.0f;          
	new_counter[2].alpha = 0.0f;  
	new_counter[3].alpha = 0.0f;        
	new_counter[4].alpha = 0.0f; 

	sprintf( new_counter[3].word, "PLAYER HAS %i^DEALER HAS %i", Get_Card_Value(CARD_PLAYER_TURN), Get_Card_Value(CARD_DEALER_TURN)); 
	sprintf( new_counter[4].word, "");

	if(sta2_gold >= 1000)  
		sprintf( string_value, "GOLD: %i^", sta2_gold); 
	if(sta2_gold >= 100 && sta2_gold < 1000) 
		sprintf( string_value, "GOLD:  %i^", sta2_gold); 
	if(sta2_gold >= 10 && sta2_gold < 100)
		sprintf( string_value, "GOLD:   %i^", sta2_gold); 
	if(sta2_gold < 10)
		sprintf( string_value, "GOLD:    %i^", sta2_gold); 

	strcat(new_counter[4].word, string_value);

	if(sta2_bet >= 100)  
		sprintf( string_value, "BET :  %i^", sta2_bet);	 
	if(sta2_bet >= 10 && sta2_bet < 100)
		sprintf( string_value, "BET :   %i^", sta2_bet);
	if(sta2_bet < 10)
		sprintf( string_value, "BET :    %i^", sta2_bet);

	strcat(new_counter[4].word, string_value);


	if(card_decision == DEAL_NONE) 
	{      
		new_counter[0].alpha = 1.0f;          
		if(sta2_gold >= sta2_bet)      
			new_counter[1].alpha = 1.0f; 
		new_counter[2].alpha = 0.0f;
		new_counter[4].alpha = 1.0f;
		sprintf( new_counter[1].word, "1. DEAL");
		sprintf( new_counter[0].word, "3. QUIT");

		sprite[18].alpha = 1.0f; // Increase coins...
		sprite[19].alpha = 1.0f; // Decrease coins...

	}
	else
	{

		sprite[18].alpha = 0.0f; // Increase coins...
		sprite[19].alpha = 0.0f; // Decrease coins...
	}
	 
	if(card_decision == DEAL_WAIT) 
	{ 
		new_counter[0].alpha = 1.0f;  
		new_counter[1].alpha = 1.0f; 
		new_counter[2].alpha = 1.0f;
		new_counter[3].alpha = 0.0f;
		sprintf( new_counter[1].word, "1. CARD");
		sprintf( new_counter[2].word, "2. STICK");
	} 
	  
	if(card_decision == DEAL_WAIT_PLAYER) 
	{  
		if(sta2_gold >= (sta2_bet*2))
			new_counter[0].alpha = 1.0f;
		new_counter[1].alpha = 1.0f; 
		new_counter[2].alpha = 1.0f;
		new_counter[3].alpha = 1.0f;
		new_counter[4].alpha = 1.0f;
		sprintf( new_counter[1].word, "1. CARD");
		sprintf( new_counter[2].word, "2. STICK");
		sprintf( new_counter[0].word, "3. DOUBLE");
	} 
	   
	if(card_decision == DEAL_CARD_PLAYER || card_decision == DEAL_CARD_DEALER || card_decision == DEAL_RESULTS)
	{
		new_counter[3].alpha = 1.0f;
	}

	new_counter[7].alpha = 0.0f; 
	new_counter[8].alpha = 0.0f;

	// Coins...
	if(sprite[18].alpha == 1.0f)
	if(( mouseX < (sprite[18].w + sprite[18].box_width) )
	&&( mouseX > sprite[18].w)                            
	&&( mouseY < (sprite[18].z + sprite[18].box_height) )
	&&( mouseY > sprite[18].z))  
	{    
				    
		new_counter[7].alpha = 1.0f;                
					    
		new_counter[7].x = mouseX + 0.13f;                   
		new_counter[7].y = mouseY;  

		new_counter[8].alpha = 1.0f;               
					   
		new_counter[8].x = mouseX + 0.1f;                 
		new_counter[8].y = mouseY;  
		 
		sprintf( new_counter[8].word, "@"); 
    	sprintf( new_counter[7].word, "INCREASE BET^");	 

		// For left-sided messages, get longest line...
		if( new_counter[7].x >= sta2_left_of_screen) 
		{ 
			slongest_line = GetLongestLine(new_counter[7].word); 
							   
			new_counter[8].x = mouseX - 0.03f;   
			new_counter[7].x = new_counter[8].x - (slongest_line*0.0245f);  

		} 
		 
		if(mouseleft == true) 
		{
			if((sta2_bet + 5) <= sta2_gold)
			if((sta2_bet + 5) <= 100)
			{
				sta2_bet +=  5;
				sta2_current_bet = sta2_bet;
			}
			mouseleft = false;
		}
		 
	}

	if(sprite[19].alpha == 1.0f)
	if(( mouseX < (sprite[19].w + sprite[19].box_width) )
	&&( mouseX > sprite[19].w)                            
	&&( mouseY < (sprite[19].z + sprite[19].box_height) )
	&&( mouseY > sprite[19].z))  
	{    
				    
		new_counter[7].alpha = 1.0f;                
					     
		new_counter[7].x = mouseX + 0.13f;                   
		new_counter[7].y = mouseY;  

		new_counter[8].alpha = 1.0f;               
					   
		new_counter[8].x = mouseX + 0.1f;                 
		new_counter[8].y = mouseY;  

		sprintf( new_counter[8].word, "@"); 
    	sprintf( new_counter[7].word, "DECREASE BET^");	

		// For left-sided messages, get longest line...
		if( new_counter[7].x >= sta2_left_of_screen) 
		{ 
			slongest_line = GetLongestLine(new_counter[7].word); 
							   
			new_counter[8].x = mouseX - 0.03f;   
			new_counter[7].x = new_counter[8].x - (slongest_line*0.0245f);  

		} 

		if(mouseleft == true) 
		{
			if((sta2_bet - 5) >= 5)
			{
				sta2_bet -=  5;
				sta2_current_bet = sta2_bet;
			}
			mouseleft = false;
		}

	}

	 
    if(title_sequence == 1)        
    { 

		new_counter[0].id = 0; 
		new_counter[1].id = 0; 
		new_counter[2].id = 0; 
				 
		testX = hud_mouseX - (-camX);                                                    
		testY = hud_mouseY - (-camY);  

		if((int)TimerGetTime() > title_timer)
		if(card_decision == DEAL_CARDS_START) 
		{
			switch(card_turn)
			{
				case CARD_PLAYER_TURN: 

					sprite[player_card_index].alpha = 1.0f;

					sprite[player_card_index].sector_action = 1+(rand()%13);
					Set_Sprite(player_card_index, sprite[player_card_index].sector_action+((rand()%4)*16), LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Point Arrow

					if(sprite[player_card_index].sector_action == 1)
						sta2_player_aces++;
					else
					{
						if(sprite[player_card_index].sector_action >= 11 && sprite[player_card_index].sector_action <= 13)
							sta2_player_value += 10;
						else
							sta2_player_value += sprite[player_card_index].sector_action;
					}

					card_turn = CARD_DEALER_TURN;

					player_card_index++; 

				break; 
				 
				case CARD_DEALER_TURN: 

					sprite[dealers_card_index].alpha = 1.0f;

					sprite[dealers_card_index].sector_action = 1+(rand()%13);
					 
					if(cards_dealt >= 3)
						sprite[dealers_card_index].sector_action = 14; // Back of card...

					Set_Sprite(dealers_card_index, sprite[dealers_card_index].sector_action+((rand()%4)*16), LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Point Arrow

					if(cards_dealt < 3)
					if(sprite[dealers_card_index].sector_action == 1)
						sta2_dealer_aces++; 
					else
					{
						if(sprite[dealers_card_index].sector_action >= 11 && sprite[dealers_card_index].sector_action <= 13)
							sta2_dealer_value += 10;
						else
							sta2_dealer_value += sprite[dealers_card_index].sector_action;
					}

					card_turn = CARD_PLAYER_TURN;
					 
					if(cards_dealt < 3) 
						dealers_card_index++;  

				break;
			}  
			 
			chop_sfx = true;

			cards_dealt++;

			title_timer = (int)TimerGetTime()+2000;

			if(cards_dealt == 4)
			{
				card_decision = DEAL_WAIT_PLAYER;
				sta2_1_pressed = false;
				sta2_2_pressed = false;
				sta2_3_pressed = false;
				sta2_esc_pressed = false;
			}

		}

		if((int)TimerGetTime() > title_timer)
		if(card_decision == DEAL_CARD_PLAYER || card_decision == DEAL_CARD_PLAYER_DOUBLE)  
		{

			sprite[player_card_index].alpha = 1.0f;  

			sprite[player_card_index].sector_action = 1+(rand()%13);
			Set_Sprite(player_card_index, sprite[player_card_index].sector_action+((rand()%4)*16), LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Point Arrow

			if(sprite[player_card_index].sector_action == 1)
				sta2_player_aces++;
			else
			{
				if(sprite[player_card_index].sector_action >= 11 && sprite[player_card_index].sector_action <= 13)
					sta2_player_value += 10;
				else
					sta2_player_value += sprite[player_card_index].sector_action;
			}
			 
			chop_sfx = true; 
			  
			player_card_index++;   

			if(card_decision == DEAL_CARD_PLAYER)
				card_decision = DEAL_WAIT_PLAYER; 

			index = Get_Card_Value(CARD_PLAYER_TURN); 

			if(card_decision == DEAL_CARD_PLAYER_DOUBLE) 
			{
				card_decision = DEAL_CARD_DEALER;
				title_timer = (int)TimerGetTime()+2000;
			}

			if(index >= 22)
			{
				title_timer = (int)TimerGetTime()+1000;
				card_decision = DEAL_RESULTS;
			}
 

		}

		if((int)TimerGetTime() > title_timer)
		if(card_decision == DEAL_CARD_DEALER) 
		{ 
			 
			sprite[dealers_card_index].alpha = 1.0f;

			sprite[dealers_card_index].sector_action = 1+(rand()%13);
			Set_Sprite(dealers_card_index, sprite[dealers_card_index].sector_action, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Point Arrow

			if(sprite[dealers_card_index].sector_action == 1)
				sta2_dealer_aces++;
			else
			{
				if(sprite[dealers_card_index].sector_action >= 11 && sprite[dealers_card_index].sector_action <= 13)
					sta2_dealer_value += 10;
				else
					sta2_dealer_value += sprite[dealers_card_index].sector_action;
			} 

			chop_sfx = true;

			dealers_card_index++;  
			  
			card_decision = DEAL_CARD_DEALER;
			title_timer = (int)TimerGetTime()+2000;

			index = Get_Card_Value(CARD_DEALER_TURN);

			if(index >= 22) 
			{
				title_timer = (int)TimerGetTime()+1000;
				card_decision = DEAL_RESULTS;
			}

			if(index >= 17 && index <= 21)
			{
				title_timer = (int)TimerGetTime()+1000;
				card_decision = DEAL_RESULTS;
			}
			 
		} 

		if((int)TimerGetTime() > title_timer)
		if(card_decision == DEAL_RESULTS) 
		{ 
			sprite[17].alpha = 1.0f;

			index = Get_Card_Value(CARD_PLAYER_TURN);
			index1 = Get_Card_Value(CARD_DEALER_TURN);

			sta2_hands_dealt++;
			sta2_tableslam_count = 0;
			sprite[0].end_x = sprite[0].x;
			sprite[0].end_y = 0.0f;

			if(index >= 22) // Player went bust...
			{
				Set_Sprite(17, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // You lose!
				sta2_gold -= sta2_current_bet;

				sta2_picked_up_gold -= sta2_current_bet;

				title_timer = (int)TimerGetTime()+2000;
				card_decision = DEAL_ENDGAME;
			}
			else
			{

				title_timer = (int)TimerGetTime()+2000;
				card_decision = DEAL_ENDGAME;

				if(index1 >= 22) // Dealer went bust...
				{      
					Set_Sprite(17, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // You win!
					cash_sfx = true;   
				    cheer_sfx = true;
					sta2_gold += sta2_current_bet;
					sta2_gold_collected += sta2_current_bet;

					sta2_picked_up_gold += sta2_current_bet;

					title_timer = (int)TimerGetTime()+250;
					card_decision = DEAL_TABLESLAM;
					sta2_shake_timer = 0;

				} 
				else 
				{
					if(index == index1)
						Set_Sprite(17, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Draw game!
					if(index < index1)
					{
						Set_Sprite(17, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // You lose!
						sta2_gold -= sta2_current_bet;

						sta2_picked_up_gold -= sta2_current_bet;
					}
					if(index > index1)
					{
						Set_Sprite(17, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // You win!
						cash_sfx = true;   
						cheer_sfx = true;
						sta2_gold += sta2_current_bet;
						sta2_gold_collected += sta2_current_bet;

						sta2_picked_up_gold += sta2_current_bet;

						title_timer = (int)TimerGetTime()+250;
						card_decision = DEAL_TABLESLAM;
						sta2_shake_timer = 0;

					}
				}
			} 

			sta2_1_pressed = false;
			sta2_2_pressed = false;
			sta2_3_pressed = false;
			sta2_esc_pressed = false;
		}


		if(card_decision == DEAL_TABLESLAM) 
		{ 						
			if(sta2_tableslam_count == 1 || sta2_tableslam_count == 3 || sta2_tableslam_count == 5)
			if((int)TimerGetTime() > sta2_shake_timer )
			{
				sprite[0].end_y += 1.0f; 
				sprite[0].x += (cos(sprite[0].end_y)/400);
   
				if(sprite[0].end_y >= 3.14f) 
					sprite[0].end_y = -3.14f;

				sta2_shake_timer = (int)TimerGetTime() + 10;
              
			} 
			if(sta2_tableslam_count == 0 || sta2_tableslam_count == 2 || sta2_tableslam_count == 4 || sta2_tableslam_count == 6)
			{
				sprite[0].x = sprite[0].end_x;
			}
		}

		if((int)TimerGetTime() > title_timer)
		if(card_decision == DEAL_TABLESLAM) 
		{ 

			 sta2_1_pressed = false; 
			 sta2_2_pressed = false;
			 sta2_3_pressed = false;
			 sta2_esc_pressed = false;

			 sta2_tableslam_count++;

			 if(sta2_tableslam_count == 1)
			 {
				 Set_Sprite(2, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Draw game!
				 destroy_sfx = true;
				 title_timer = (int)TimerGetTime()+250;

				 for(int i = 0; i<no_sprites;i++)
				 if(sprite[i].type == FE_CARD) 
				 if(rand()%2 == 0)
					sprite[i].angle += 1.0f;
				 else
					sprite[i].angle -= 1.0f; 
			 }
			 if(sta2_tableslam_count == 2)
			 {
				 Set_Sprite(2, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Draw game!
				 title_timer = (int)TimerGetTime()+250;
			 }
			 if(sta2_tableslam_count == 3)
			 {
				 Set_Sprite(2, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Draw game!
				 destroy_sfx = true;

				 for(int i = 0; i<no_sprites;i++) 
				 if(sprite[i].type == FE_CARD)
				 if(rand()%2 == 0) 
					sprite[i].angle += 2.0f;  
				 else
					sprite[i].angle -= 2.0f;

				 title_timer = (int)TimerGetTime()+250;
			 }
			 if(sta2_tableslam_count == 4)      
			 {
				 Set_Sprite(2, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Draw game!
				 title_timer = (int)TimerGetTime()+250;
			 }
			 if(sta2_tableslam_count == 5)
			 {
				 Set_Sprite(2, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Draw game!
				 destroy_sfx = true;

				 for(int i = 0; i<no_sprites;i++)
				 if(sprite[i].type == FE_CARD)
				 if(rand()%2 == 0) 
					sprite[i].angle += 4.0f;
				 else
					sprite[i].angle -= 4.0f;

				 title_timer = (int)TimerGetTime()+250;
			 }
			 if(sta2_tableslam_count == 6)
			 {
				 Set_Sprite(2, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Draw game!
				 title_timer = (int)TimerGetTime()+250;
			 }

			 if(sta2_tableslam_count >= 7)
			 {
				 for(int i = 0; i<no_sprites;i++)
				 if(sprite[i].type == FE_CARD)
					sprite[i].angle = 0.0f;

				 title_sequence = 0; 

				 if(sta2_hands_dealt == 3)
				 {
					sta2_next_event = EVENT_GAMBLE_RESULT;

					if(sta2_picked_up_gold < 0)
						sta2_picked_up_gold = 0;

					episode = 1;  
					scene = 2;

					next_scene = true;
				 }
			 }
		} 

		if((int)TimerGetTime() > title_timer)
		if(card_decision == DEAL_ENDGAME) 
		{ 

			 sta2_1_pressed = false;
			 sta2_2_pressed = false;
			 sta2_3_pressed = false;
			 sta2_esc_pressed = false;

			 title_sequence = 0; 

			 if(sta2_hands_dealt == 3)
			 {
				sta2_next_event = EVENT_GAMBLE_RESULT;

				if(sta2_picked_up_gold < 0)
					sta2_picked_up_gold = 0;

				episode = 1;  
				scene = 2;

				next_scene = true;
			 }

		} 

		// 3 key..
		if(new_counter[0].alpha == 1.0f) 
		if(( testX < (new_counter[0].w + new_counter[0].box_width) )
		&&( testX > new_counter[0].w)                            
		&&( testY < (new_counter[0].z + new_counter[0].box_height) )
		&&( testY > new_counter[0].z) || sta2_3_pressed == true || sta2_esc_pressed == true)   
		{ 
			new_counter[0].id = 2;   

			if(mouseleft == true || DX_SHOOT == true || sta2_3_pressed == true || sta2_esc_pressed == true) 
			{  
						 
				mouseleft = false;       
				DX_SHOOT = false;  
				sta2_3_pressed = false;
				sta2_esc_pressed = false;

				if(card_decision == DEAL_WAIT_PLAYER)
				{
					sta2_current_bet = sta2_bet*2;
					card_decision = DEAL_CARD_PLAYER_DOUBLE;
					title_timer = (int)TimerGetTime()+500;
				}
				else
				{
					sta2_next_event = EVENT_GAMBLE_RESULT;

					if(sta2_picked_up_gold < 0)
						sta2_picked_up_gold = 0;

					episode = 1;  
					scene = 2;

					next_scene = true;
				}
						  
			} 
		}      

		// 1 key..
		if(new_counter[1].alpha == 1.0f)
		if(( testX < (new_counter[1].w + new_counter[1].box_width) )
		&&( testX > new_counter[1].w)                            
		&&( testY < (new_counter[1].z + new_counter[1].box_height) )
		&&( testY > new_counter[1].z) || sta2_1_pressed == true)   
		{ 
			new_counter[1].id = 2;    

			if(mouseleft == true || DX_SHOOT == true || sta2_1_pressed == true) 
			{  
						 
				mouseleft = false;        
				DX_SHOOT = false;  
				sta2_1_pressed = false;  

				if(card_decision == DEAL_NONE)
					card_decision = DEAL_CARDS_START; 
						   
				if(card_decision == DEAL_WAIT_PLAYER) 
				{
					card_decision = DEAL_CARD_PLAYER;
					title_timer = (int)TimerGetTime()+500;
				}
			}  
		}   

		// 2 key..
		if(new_counter[2].alpha == 1.0f)
		if(( testX < (new_counter[2].w + new_counter[2].box_width) )
		&&( testX > new_counter[2].w)                            
		&&( testY < (new_counter[2].z + new_counter[2].box_height) )
		&&( testY > new_counter[2].z) || sta2_2_pressed == true)   
		{ 
			new_counter[2].id = 2;   

			if(mouseleft == true || DX_SHOOT == true || sta2_2_pressed == true) 
			{  
						 
				mouseleft = false;       
				DX_SHOOT = false;  
				sta2_2_pressed = false; 
						   
				if(card_decision == DEAL_WAIT_PLAYER) 
				{
					card_decision = DEAL_CARD_DEALER;
					title_timer = (int)TimerGetTime()+2000;
				}
						  
			} 
		}  

	}

	} // episode == 1 && scene == 26

/*
       
    if(game_mode == FRONT || game_mode == WALK)
    if(next_scene == false)
    if(!mode)
    if(next_scene == false)    
    if(episode == 1 && scene == 26)
    {     


	   if(!mode && CONTROLLER)
	   if(next_scene == false) 
	   if(DX_BACK == true)
	   {

		   if(sprite[4].id == 7)
		   if(sprite[4].alpha == 1.0f)
		   {
			   scene = 3; 
			   episode = 1;
			   next_scene = true;
		   }

		   DX_BACK=false;
	   }

       if(title_sequence != 8 && title_sequence != 9) 
       {
                                                      
       counter[0].width = 0.02f;
       counter[0].height = 0.05f; 
     
       counter[1].width = 0.02f;
       counter[1].height = 0.05f;
     
       counter[3].width = 0.02f;
       counter[3].height = 0.05f;
                                                              
       counter[3].x = 0.70f;          
       counter[3].y =  -0.12f; 
       counter[3].width = 0.016f;
       counter[3].height = 0.048f;   
       counter[3].alpha = 1.0f;
       
       sprintf( counter[3].word, "GOLD^%i^BET^%i", player_inv_value[current_gold], bet_size);
                                                      
       counter[0].x = -0.90f;      
       counter[0].y =  -0.26f; 
       counter[0].width = 0.016f;
       counter[0].height = 0.048f; 
       counter[0].alpha = 1.0f;  
       
       display_players_cards = Calculate_Cards(players_cards, players_aces, true);
       
       if(display_players_cards != 0 && display_players_cards != 101)
           sprintf( counter[0].word, "PLAYER^%i", display_players_cards);
       if(display_players_cards == 0)    
           sprintf( counter[0].word, "PLAYER^EMPTY");
       if(display_players_cards == 101)    
           sprintf( counter[0].word, "PLAYER^NICE!");
       if(display_players_cards > 21 && display_players_cards != 101)    
           sprintf( counter[0].word, "PLAYER^BUST!"); 
                                                       
       counter[1].x = 0.70f;        
       counter[1].y =  0.66f; 
       counter[1].width = 0.016f;
       counter[1].height = 0.048f;
       counter[1].alpha = 1.0f;
              
       display_dealers_cards = Calculate_Cards(dealers_cards, dealers_aces, false);
       
       if(display_dealers_cards != 0 && display_dealers_cards != 101)         
           sprintf( counter[1].word, "DEALER^%i", display_dealers_cards);
       if(display_dealers_cards == 0)    
           sprintf( counter[1].word, "DEALER^EMPTY");
       if(display_dealers_cards == 101)    
           sprintf( counter[1].word, "DEALER^NICE!");
       if(display_dealers_cards > 21 && display_dealers_cards != 101)    
           sprintf( counter[1].word, "DEALER^BUST!");
           
       } 
                            
       for(int i=0;i<no_sprites;i++)  
       {  
         
         if(sprite[i].type == FE_CARD) 
         {
              Set_Sprite(i, sprite[i].sector_action, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); 
         } 
         
       }   
        
                  
       if(title_sequence == 0)     
       { 
		   #if INCLDUE_360_CONTROLLER == 1
			    
			   	MAKE_BUTTON(ROW_MIDDLE-1, 23, BOX_SMALL); 
				MAKE_BUTTON(ROW_MIDDLE-1, 24, BOX_SMALL); 

				MAKE_BUTTON(ROW_MIDDLE, 0, BOX_SMALL);  
				MAKE_BUTTON(ROW_MIDDLE+1, 4, BOX_SMALL);   

				MAKE_BUTTON(ROW_MIDDLE+2, 19, BOX_SMALL); 
				MAKE_BUTTON(ROW_MIDDLE+2, 20, BOX_SMALL);

		   #endif

		   quit_casino=true;

		   max_bet_size=100;    

	       max_bet_size=player_rank*150;   

		   if(player_rank >= 10)
		       max_bet_size = 10000;	
	
           old_bet = bet_size;
	
		   sprite[23].alpha = 0.0f; // Double
		   sprite[24].alpha = 0.0f; // Treble
              
           players_cards = 0; 
           dealers_cards = 0;  
           players_aces  = 0;
           dealers_aces  = 0;   
           num_players_cards=0;
           num_dealers_cards=0; 
           
           sprite[0].mouseover = false; // Hit
		   sprite[0].alpha = 1.0f; // Hit
           sprite[4].mouseover = false; // Stick 
           sprite[4].alpha = 1.0f; // Hit 

           sprite[19].mouseover = false; // Hit
		   sprite[19].alpha = 1.0f; // Hit 
           sprite[20].mouseover = false; // Stick 
		   sprite[20].alpha = 1.0f; // Hit 
                      
           sprite[0].id = 5;
           sprite[4].id = 7; 
    
           sprite[5].alpha = 0.0f; // Thumb

           Set_Sprite(3, 2, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Big Delete Arrow 
           
           for(int i=0;i<no_sprites;i++)  
           if(sprite[i].type == FE_CARD)             
               sprite[i].sector_action = 0;
            
           if(card_decision == DEAL_CARD) 
           {
               title_timer = (int)TimerGetTime()+Card_Time;
               title_sequence++;  
               card_decision = DEAL_NONE;
               sprite[0].mouseover = true; // Hit
			   sprite[0].alpha = 0.0f; // Hit
               sprite[4].mouseover = true; // Stick 
			   sprite[4].alpha = 0.0f; // Hit
           
               sprite[19].mouseover = true; // Hit
			   sprite[19].alpha = 0.0f; // Hit
               sprite[20].mouseover = true; // Stick                                     
			   sprite[20].alpha = 0.0f; // Hit
           }
           if(card_decision == DEAL_STAY)   
           {
               scene = 3;
               episode = 1;
               next_scene = true;
               card_decision = DEAL_NONE;
           } 
           
       }
       
       // DEAL FIRST CARD TO PLAYER
       if( (int)TimerGetTime() > title_timer)    
       if(title_sequence == 1)   
       {
                         
           sprite[5].alpha = 1.0f;
           Set_Sprite(3, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Big Delete Arrow 
             
           title_timer = (int)TimerGetTime()+Card_Time;
           
         for(int i=0;i<no_sprites;i++)  
         if(sprite[i].type == FE_CARD)             
         if(sprite[i].score == 0)
         {
           sprite[i].sector_action = 1+(rand()%13);
           players_cards += Get_Card_Value(sprite[i].sector_action, true);
         }  
           title_sequence++;       
             
       }
       
       // DEAL FIRST CARD TO DEALER
       if( (int)TimerGetTime() > title_timer)
       if(title_sequence == 2)   
       {
             
           title_timer = (int)TimerGetTime()+Card_Time;
           
         for(int i=0;i<no_sprites;i++)  
         if(sprite[i].type == FE_CARD)             
         if(sprite[i].score == 5)
         {
           sprite[i].sector_action = 1+(rand()%13);
           dealers_cards += Get_Card_Value(sprite[i].sector_action, false);
         }  
                   
           title_sequence++;  
             
       }
       
       // DEAL SECOND CARD TO PLAYER 
       if( (int)TimerGetTime() > title_timer)
       if(title_sequence == 3)   
       {
             
           title_timer = (int)TimerGetTime()+Card_Time;
           
         for(int i=0;i<no_sprites;i++)  
         if(sprite[i].type == FE_CARD)             
         if(sprite[i].score == 1)
         {
           sprite[i].sector_action = 1+(rand()%13);
           players_cards += Get_Card_Value(sprite[i].sector_action, true);
         }  
                    
           title_sequence++;  
              
       }
       
       if( (int)TimerGetTime() > title_timer)
       if(title_sequence == 4)    
       {
                     
           title_sequence++;  
             
       } 

       // DISPLAY HIT OR STICK OR DOUBLE
       if( (int)TimerGetTime() > title_timer) 
       if(title_sequence == 5)    
       {
                       
           sprite[0].mouseover = false; // Hit
		   sprite[0].alpha = 1.0f; // Hit
           sprite[4].mouseover = false; // Stick                   
		   sprite[4].alpha = 1.0f; // Hit
                       
           sprite[0].id = 6;
           sprite[4].id = 8;
 		   
		   if(current_gold >= 0)
		   if(bet_size*2 <= player_inv_value[current_gold])
		   {
               sprite[23].alpha = 1.0f; 
               sprite[24].alpha = 1.0f; 
		   }
                           
           title_sequence++; 

           current_card = 1;  
           
       }
       
       if( (int)TimerGetTime() > title_timer)
       if(title_sequence == 6)    
       {
 
           if(card_decision == DEAL_DOUBLE || card_decision == DEAL_TREBLE) 
           {
			   	
			   if(card_decision == DEAL_DOUBLE)
				  bet_size *= 2;      
			   if(card_decision == DEAL_TREBLE)
				  bet_size *= 3;      

			   current_card++;  
               
               card_decision = DEAL_NONE;

			   mouseleft = false;
	
               sprite[0].mouseover = true; // Hit
			   sprite[0].alpha = 0.0f; // Hit
               sprite[4].mouseover = true; // Stick   
			   sprite[4].alpha = 0.0f; // Hit

			   sprite[23].alpha = 0.0f;
               sprite[24].alpha = 0.0f;

               for(int i=0;i<no_sprites;i++)  
               if(sprite[i].type == FE_CARD)             
               if(sprite[i].score == current_card)
               {
                   sprite[i].sector_action = 1+(rand()%13);
                   players_cards += Get_Card_Value(sprite[i].sector_action, true);
               }   
               
               display_players_cards = Calculate_Cards(players_cards, players_aces, true); 

               if(display_players_cards > 21 && display_players_cards != 101)
               {
                   title_timer = (int)TimerGetTime() + Card_Time;
                   sprite[0].mouseover = true; // Hit
				   sprite[0].alpha = 0.0f; // Hit
                   sprite[4].mouseover = true; // Stick   
				   sprite[4].alpha = 0.0f; // Hit
                   current_card = 6;
               //    title_sequence++;                    
               } 
               if(current_card == 4 )
               {
                   sprite[0].mouseover = true; // Hit
				   sprite[0].alpha = 0.0f; // Hit
                   sprite[4].mouseover = true; // Stick   
				   sprite[4].alpha = 0.0f; // Hit
                   current_card = 6;
               //    title_sequence++;                            
               }

               card_decision = DEAL_NONE;

               current_card = 6;
			   title_sequence++;	
                   
           }
            
           if(card_decision == DEAL_STAY)
           {
               sprite[0].mouseover = true; // Hit
			   sprite[0].alpha = 0.0f; // Hit
               sprite[4].mouseover = true; // Stick 
			   sprite[4].alpha = 0.0f; // Hit

               title_sequence++;
               current_card = 6;               
               card_decision = DEAL_NONE;
           }
           
           if(card_decision == DEAL_CARD) 
           {
                    
               current_card++;  
               
               card_decision = DEAL_NONE;
                                           
               for(int i=0;i<no_sprites;i++)  
               if(sprite[i].type == FE_CARD)             
               if(sprite[i].score == current_card)
               {
                   sprite[i].sector_action = 1+(rand()%13);
                   players_cards += Get_Card_Value(sprite[i].sector_action, true);
               }   
               
               display_players_cards = Calculate_Cards(players_cards, players_aces, true);                
               
               if(display_players_cards > 21 && display_players_cards != 101)
               {
                   title_timer = (int)TimerGetTime() + Card_Time;
                   sprite[0].mouseover = true; // Hit
				   sprite[0].alpha = 0.0f; // Hit
                   sprite[4].mouseover = true; // Stick   
				   sprite[4].alpha = 0.0f; // Hit
                   current_card = 6;
                   title_sequence++;                    
               }
               if(current_card == 4 )
               {
                   sprite[0].mouseover = true; // Hit
				   sprite[0].alpha = 0.0f; // Hit
                   sprite[4].mouseover = true; // Stick   
				   sprite[4].alpha = 0.0f; // Hit
                   current_card = 6;
                   title_sequence++;                            
               }
                   
           }
      
       }
       
       // Dealers Turn...
       if( (int)TimerGetTime() > title_timer)
       if(title_sequence == 7)     
       { 

           sprite[23].alpha = 0.0f; 
           sprite[24].alpha = 0.0f;

           title_timer = (int)TimerGetTime() + Card_Time;  
            
           // Dealer's AI
           if( ((display_dealers_cards < display_players_cards) || (display_dealers_cards < 17)) 
           && display_dealers_cards != 101)
               card_decision = DEAL_CARD;  
           else
               card_decision = DEAL_STAY; 
            
           if(display_players_cards > 21 && display_players_cards != 101)
               card_decision = DEAL_STAY; 
               
           if(display_dealers_cards >= 17 && display_dealers_cards != 101)
               card_decision = DEAL_STAY;
                                        
           if(card_decision == DEAL_STAY)
           {
               sprite[0].mouseover = true; // Hit
			   sprite[0].alpha = 0.0f; // Hit
               sprite[4].mouseover = true; // Stick 
			   sprite[4].alpha = 0.0f; // Hit
               title_sequence++;
               card_decision = DEAL_NONE; 
           }
           
           if(card_decision == DEAL_CARD) 
           {
                   
               current_card++;  
                
               card_decision = DEAL_NONE;   
                                           
               for(int i=0;i<no_sprites;i++)  
               if(sprite[i].type == FE_CARD)             
               if(sprite[i].score == current_card)
               {
                   sprite[i].sector_action = 1+(rand()%13);
                   dealers_cards += Get_Card_Value(sprite[i].sector_action, false);
               }  
               
               if(current_card == 9)
               {
                   sprite[0].mouseover = true; // Hit
				   sprite[0].alpha = 0.0f; // Hit
                   sprite[4].mouseover = true; // Stick   
				   sprite[4].alpha = 0.0f; // Hit
                   title_sequence++;                            
               }
                   
           }
           
       } // title_sequence == 7           
                
       // Dealers Turn...
       if( (int)TimerGetTime() > title_timer)
       if(title_sequence == 8)  
       {
                         
           card_flash_timer = 0;
                         
           title_timer = (int)TimerGetTime() + Card_Time1;                  
           title_sequence++;               
       
           display_players_cards = Calculate_Cards(players_cards, players_aces, true);                         
           display_dealers_cards = Calculate_Cards(dealers_cards, dealers_aces, false);
           
           // Dealer's AI
           if( (display_dealers_cards < display_players_cards) && 
           display_dealers_cards != 101)
               win_game = CARD_WIN; 
           else
               win_game = CARD_LOSE;
               
           if( display_dealers_cards == display_players_cards && display_dealers_cards >= 17)
               win_game = CARD_PUSH;
           
           if(display_players_cards > 21 && display_players_cards != 101)
               win_game = CARD_LOSE;  
                            
           if(display_dealers_cards > 21 && display_dealers_cards != 101)
               win_game = CARD_WIN; 
                          
           if(win_game == CARD_WIN)  
           {
               sprintf( counter[0].word, "PLAYER^WINS!");               
               sprintf( counter[1].word, "DEALER^LOSES!");
               
               if(display_players_cards != 101)
			   {
				   if(current_gold >= 0)	
                   	   player_inv_value[current_gold] += bet_size;
				   casino_won += bet_size; 	 	
			   }	
               else
			   {	
				   if(current_gold >= 0) 
                       player_inv_value[current_gold] += (bet_size*15)/10;
				   casino_won += (bet_size*15)/10;
               } 
               
               Calculate_Gold();
                   
               Set_Sprite(3, 3, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Swearing
               
               // Remove cards
               for(int i=0;i<no_sprites;i++)  
               if(sprite[i].type == FE_CARD)             
                   sprite[i].sector_action = 0;
                                             
               cash_sfx = true;   
			   cheer_sfx = true;            
           }              
           if(win_game == CARD_LOSE)  
           {
               sprintf( counter[0].word, "PLAYER^LOSES");               
               sprintf( counter[1].word, "DEALER^WINS!");

               if(current_gold >= 0)
	               player_inv_value[current_gold] -= bet_size;

  		   //    casino_won -= bet_size;
               
               Calculate_Gold();  
               
               Set_Sprite(3, 4, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Crunch Cards
               
               // Remove cards
               for(int i=0;i<no_sprites;i++)  
               if(sprite[i].type == FE_CARD)             
                   sprite[i].sector_action = 0;

			   stolen_sfx=true;
                                  
           }              
           if(win_game == CARD_PUSH)
           {
               sprintf( counter[0].word, "PLAYER^PUSH!");               
               sprintf( counter[1].word, "DEALER^PUSH!");               
           }              
                   
           sprintf( counter[3].word, "GOLD^%i^BET^%i", player_inv_value[current_gold], bet_size);
              
       } // title_sequence == 8   
       
       // Flash win-lose... 
       if(title_sequence == 9)  
       {
           bet_size = old_bet;

           if((int)TimerGetTime() > card_flash_timer)
           { 
                                  
               card_flash_timer = (int)TimerGetTime() + 250;
                                  
               if(card_flash == true)
               {
                   sprintf( counter[0].word, "");
                   sprintf( counter[1].word, "");
                   card_flash = false;
               }
               else 
               {
                 card_flash = true;
                 if(win_game == CARD_WIN) 
                 {
                   sprintf( counter[0].word, "PLAYER^WINS!");               
                   sprintf( counter[1].word, "DEALER^LOSES!");
                 }                         
                 if(win_game == CARD_LOSE) 
                 { 
                   sprintf( counter[0].word, "PLAYER^LOSES");               
                   sprintf( counter[1].word, "DEALER^WINS!");                          
                 }              
                 if(win_game == CARD_PUSH)
                 {
                   sprintf( counter[0].word, "PLAYER^PUSH!");               
                   sprintf( counter[1].word, "DEALER^PUSH!");               
                 } 
                                     
               }
           }
                      
                         
       } 
       
          
       // Dealers Turn...
       if( (int)TimerGetTime() > title_timer)
       if(title_sequence == 9)  
       {
		   #if INCLDUE_360_CONTROLLER == 1
		       DX_ROW = ROW_MIDDLE;
			   DX_CURRENT_TITLE_BUTTON[DX_ROW] = 0;       
		   #endif

           title_sequence = 0;
                         
       }                   
       
                          
  }   

  */


	return(success);

} 
