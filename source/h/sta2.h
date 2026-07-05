#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64 
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#endif 

#define WW_NONE    0
#define WW_GAIN    1
#define WW_LOST    2
#define WW_TRADE   3
#define WW_SOLO    4

#define TEXT_NONE          0
#define TEXT_DAMAGE        1
#define TEXT_DAMAGE_ALL    2 
#define TEXT_GAIN_GOLD     3
#define TEXT_GAIN_FOOD     4
#define TEXT_LOST_GOLD     5
#define TEXT_LOST_FOOD     6
#define TEXT_HEALTH        7
#define TEXT_HEALTH_ALL    8

int ww_stored_amount1 = 0;
int ww_stored_amount2 = 0;

extern void STA2_RemoveSave();
extern int Get_Bet_Amount();

int Run_Trade();
bool Sta2LoadText( char *filename, char *word, int use_this_id, int type );
void WrapWord(char *word, unsigned int line_length, int type);
bool IsSquadAlive();
bool sta2GetName(char *filename, char *word);
bool sta2GetEmyNames(char *filename);
void HealAllTeam();
int SquadCount();
void Run_Ach();


int Run_Trade()
{ 
	int success = 1;   
	  
	if(sta2_trade.active == true)    
	{

		if(sta2_trade.cost_type == TRADE_GOLD)    
			sta2_gold -= sta2_trade.cost_amount; 

		if(sta2_trade.cost_type == TRADE_FOOD)
			sta2_food -= sta2_trade.cost_amount;  

		if(sta2_trade.gain_type == TRADE_GOLD) 
		{
			sta2_gold += sta2_trade.gain_amount; 
			sta2_gold_collected += sta2_trade.gain_amount; 
		}

		if(sta2_trade.gain_type == TRADE_FOOD)
			sta2_food += sta2_trade.gain_amount;

		if(sta2_trade.gain_type == TRADE_PACK)
		{
			// Add weapon pack for the hired unit....
			for(int k = 0;k < STA2_PACKS_LIMIT;k++)  
			{ 
				// Find an empty pack slot...  
				if(sta2_pack[k].type == STA2_VOID)  
				{
					if(sta2_co_type == STA2_CO_ADA)
					{
						sta2_pack[k].type = STA2_SCOUT;          
						sta2_pack[k].rank = sta2_trade.gain_amount;     
						sta2_pack[k].equipped = false; 
						sta2_pack[k].extra = PACK_EXTRA_NONE;      // PACK_EXTRA_MEDKIT
						sta2_pack[k].extra_charge = 0;
						sta2_pack[k].special = PACK_SPECIAL_NONE;  // PACK_EXTRA_MEDKIT
						sta2_pack[k].special_charge = 0;
						sprintf(sta2_pack[k].string, "SCOUT PACK");   
					}
					if(sta2_co_type == STA2_CO_MARIE)
					{
						sta2_pack[k].type = STA2_HEAVY;          
						sta2_pack[k].rank = sta2_trade.gain_amount;     
						sta2_pack[k].equipped = false; 
						sta2_pack[k].extra = PACK_EXTRA_NONE;      // PACK_EXTRA_MEDKIT
						sta2_pack[k].extra_charge = 0;
						sta2_pack[k].special = PACK_SPECIAL_NONE;  // PACK_EXTRA_MEDKIT
						sta2_pack[k].special_charge = 0;
						sprintf(sta2_pack[k].string, "HEAVY PACK");   
					}
					if(sta2_co_type == STA2_CO_ADELE)
					{
						sta2_pack[k].type = STA2_SNIPER;          
						sta2_pack[k].rank = sta2_trade.gain_amount;     
						sta2_pack[k].equipped = false; 
						sta2_pack[k].extra = PACK_EXTRA_NONE;      // PACK_EXTRA_MEDKIT
						sta2_pack[k].extra_charge = 0;
						sta2_pack[k].special = PACK_SPECIAL_NONE;  // PACK_EXTRA_MEDKIT
						sta2_pack[k].special_charge = 0;
						sprintf(sta2_pack[k].string, "SNIPER PACK");   
					}
					if(sta2_co_type == STA2_CO_BELLA)
					{
						sta2_pack[k].type = STA2_MORTAR;          
						sta2_pack[k].rank = sta2_trade.gain_amount;     
						sta2_pack[k].equipped = false; 
						sta2_pack[k].extra = PACK_EXTRA_NONE;      // PACK_EXTRA_MEDKIT
						sta2_pack[k].extra_charge = 0;
						sta2_pack[k].special = PACK_SPECIAL_NONE;  // PACK_EXTRA_MEDKIT
						sta2_pack[k].special_charge = 0;
						sprintf(sta2_pack[k].string, "MORTAR PACK");   
					}

					break;
				}
			}
		}

		if(sta2_gold < 0) 
			sta2_gold = 0; 
		if(sta2_food < 0)
			sta2_food = 0;

	}  

	sta2_trade.cost_type=TRADE_NONE;
	sta2_trade.gain_type=TRADE_NONE;

	sta2_trade.active = false;

	return(success);

} 
 
void GetPage(int sta2_event)       
{                    
	int rnd=0;      

	if(sta2_event == PAGE_INTRO)                   
	{      
		page[0].no_of_pages = 1;      
	    
		page[0].type = PAGE_INTRO;      
		page[0].option1 = OPTION_CONTINUE;       
		page[0].option2 = OPTION_NONE;      
		page[0].option3 = OPTION_NONE;          
		page[0].option4 = OPTION_NONE;        
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/intro/intro.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

	}  

	if(sta2_event == PAGE_NEW_SECTOR)                   
	{      
		page[0].no_of_pages = 1;    
	   
		page[0].type = PAGE_NEW_SECTOR;      
		page[0].option1 = OPTION_CONTINUE;      
		page[0].option2 = OPTION_NONE;      
		page[0].option3 = OPTION_NONE;          
		page[0].option4 = OPTION_NONE;      
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/sector/sector.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

	}  

	if(sta2_event == PAGE_SECTOR_GO)                   
	{       
		page[0].no_of_pages = 1;     
	   
		page[0].type = PAGE_SECTOR_GO;      
		page[0].option1 = OPTION_SECTOR;     
		page[0].option2 = OPTION_NONE;    
		page[0].option3 = OPTION_NONE;          
		page[0].option4 = OPTION_NONE;       
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/boss/sector.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

		if(sta2_playing_tutorial == true)
		{
			page[0].no_of_pages = 1;    
	   
			page[0].type = PAGE_BOSS;      
			page[0].option1 = OPTION_TUTORIAL;     
			page[0].option2 = OPTION_NONE;      
			page[0].option3 = OPTION_NONE;          
			page[0].option4 = OPTION_NONE;      
			page[0].choice = CHOICE_NONE;  

			Sta2LoadText("data/text/boss/tutorial.txt", page[0].word_text, -1, WW_NONE);  

			sprintf( page[0].word_option1, "1 : Continue."); 

	
			#if IS_FULL_STEAM == 1

			if(STEAM_ACTIVE == true)  
			if(IS_FULL_GAME == true)
			if (g_SteamAchievements)
			{
				g_SteamAchievements->SetAchievement("STA2_MEDAL_3"); // Beat tutorial mode...
				if(sta2_globals[GLOBAL_STA2_MEDAL_3] == GLOBALS_RESET)
				{
					sta2_globals[GLOBAL_STA2_MEDAL_3] = GLOBALS_ACTIVE;
					firework_sfx = true;

				} 
			}

			#endif

			sta2_globals[GLOBAL_STA2_MEDAL_3] = GLOBALS_ACTIVE;

		}
		if(sta2_sector == 8)  
		{

			page[0].no_of_pages = 1;    
	    
			page[0].type = PAGE_ENDGAME;      
			page[0].option1 = OPTION_ENDGAME;    
			page[0].option2 = OPTION_NONE;    
			page[0].option3 = OPTION_NONE;          
			page[0].option4 = OPTION_NONE;      
			page[0].choice = CHOICE_NONE;  

			Sta2LoadText("data/text/boss/endgame.txt", page[0].word_text, -1, WW_NONE);  

			sprintf( page[0].word_option1, "1 : Continue."); 
		}

	}   

	if(sta2_event == PAGE_BOSS)                    
	{       
		page[0].no_of_pages = 1;      
	   
		page[0].type = PAGE_BOSS;      
		page[0].option1 = OPTION_BOSS;    
		page[0].option2 = OPTION_CONTINUE;    
		page[0].option3 = OPTION_NONE;          
		page[0].option4 = OPTION_NONE;      
		page[0].choice = CHOICE_NONE;  

		if(sta2_sector == 8)  
			Sta2LoadText("data/text/boss/boss_final.txt", page[0].word_text, -1, WW_NONE);  
		else
			Sta2LoadText("data/text/boss/boss.txt", page[0].word_text, -1, WW_NONE);  
		
		sprintf( page[0].word_option1, "1 : Continue.");
		sprintf( page[0].word_option2, "2 : Go back.");

	}   

	if(sta2_event == PAGE_STARVE)                    
	{      
		page[0].no_of_pages = 1;    
	    
		page[0].type = PAGE_STARVE;     
		page[0].option1 = OPTION_DEFEAT;    
		page[0].option2 = OPTION_NONE;    
		page[0].option3 = OPTION_NONE;          
		page[0].option4 = OPTION_NONE;      
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/starve/starve.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

	}   

	if(sta2_event == PAGE_DEFEAT)                   
	{      
		page[0].no_of_pages = 1;    
	    
		page[0].type = PAGE_DEFEAT;     
		page[0].option1 = OPTION_DEFEAT;    
		page[0].option2 = OPTION_NONE;    
		page[0].option3 = OPTION_NONE;          
		page[0].option4 = OPTION_NONE;      
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/defeat/defeat.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

	}   

	if(sta2_event == PAGE_GENERAL)                   
	{      

		sta2_is_general_fight = true;

		page[0].no_of_pages = 1;    
	     
		page[0].type = PAGE_GENERAL;      
		page[0].option1 = OPTION_SQUAD;     
		page[0].option2 = OPTION_AVOID_GENERAL;    
		page[0].option3 = OPTION_NONE;           
		page[0].option4 = OPTION_NONE;      
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/defeat/general.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue."); 
		sprintf( page[0].word_option2, "2 : Try to escape.");

	}   

	if(sta2_event == PAGE_VICTORY)                  
	{      
		page[0].no_of_pages = 1;    
	   
		page[0].type = PAGE_VICTORY;     
		page[0].option1 = OPTION_VICTORY;    
		page[0].option2 = OPTION_NONE;    
		page[0].option3 = OPTION_NONE;          
		page[0].option4 = OPTION_NONE;     
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/victory/victory.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Results.");

	}   

	if(sta2_event == PAGE_HUNT_RESULT)                  
	{      
		page[0].no_of_pages = 1;    
	   
		page[0].type = PAGE_HUNT_RESULT;      
		page[0].option1 = OPTION_CONTINUE;    
		page[0].option2 = OPTION_NONE;     
		page[0].option3 = OPTION_NONE;          
		page[0].option4 = OPTION_NONE;     
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/hunt/huntR.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

	}  

	if(sta2_event == PAGE_GAMBLE_RESULT)                  
	{      
		page[0].no_of_pages = 1;    
	   
		page[0].type = PAGE_GAMBLE_RESULT;      
		page[0].option1 = OPTION_CONTINUE;    
		page[0].option2 = OPTION_NONE;      
		page[0].option3 = OPTION_NONE;           
		page[0].option4 = OPTION_NONE;     
		page[0].choice = CHOICE_NONE;   

		Sta2LoadText("data/text/gamble/gambleR.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

		if(sta2_picked_up_gold >= 200)
		{
			#if IS_FULL_STEAM == 1

			if(STEAM_ACTIVE == true) 
			if(IS_FULL_GAME == true)
			if (g_SteamAchievements)
			{
				g_SteamAchievements->SetAchievement("STA2_MEDAL_8"); // Win 200Gold on blackjack...
				if(sta2_globals[GLOBAL_STA2_MEDAL_8] == GLOBALS_RESET)
				{
					sta2_globals[GLOBAL_STA2_MEDAL_8] = GLOBALS_ACTIVE;
					firework_sfx = true;

				}
			}

			#endif
		}

	}  


	if(sta2_event == PAGE_VICTORY_RESULT)                  
	{      
		page[0].no_of_pages = 1;    
	   
		page[0].type = PAGE_VICTORY_RESULT;      
		page[0].option1 = OPTION_CONTINUE;    
		page[0].option2 = OPTION_NONE;    
		page[0].option3 = OPTION_NONE;          
		page[0].option4 = OPTION_NONE;     
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/victory/victoryR.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

		if(sta2_got_speed_bonus == true || sta2_got_epic_bonus == true)
			page[0].option1 = OPTION_SPEED; 
		else
		{
			if(sta2_is_epic_battle == true)
				page[0].option1 = OPTION_SECTOR_GO;
			if(sta2_got_double_bonus == true || sta2_got_triple_bonus == true)
				page[0].option1 = OPTION_BONUS;
		}

		if(sta2_is_epic_battle == true)
		if(sta2_only_defend == true)
		{
			#if IS_FULL_STEAM == 1 

			if(STEAM_ACTIVE == true)  
			if(IS_FULL_GAME == true)
			if (g_SteamAchievements)
			{
				g_SteamAchievements->SetAchievement("STA2_MEDAL_9"); // Win a battle only using defend...
				if(sta2_globals[GLOBAL_STA2_MEDAL_9] == GLOBALS_RESET)
				{
					sta2_globals[GLOBAL_STA2_MEDAL_9] = GLOBALS_ACTIVE;
					firework_sfx = true;

				}
			}

			#endif
		}

		if(sta2_is_epic_battle == true)
		if(sta2_only_grenade == true) 
		{
			#if IS_FULL_STEAM == 1 

			if(STEAM_ACTIVE == true)  
			if(IS_FULL_GAME == true)
			if (g_SteamAchievements)
			{
				g_SteamAchievements->SetAchievement("STA2_MEDAL_10"); // Win a battle with just grenades...
				if(sta2_globals[GLOBAL_STA2_MEDAL_10] == GLOBALS_RESET)
				{
					sta2_globals[GLOBAL_STA2_MEDAL_10] = GLOBALS_ACTIVE;
					firework_sfx = true;

				}
			}

			#endif
		}

		if(sta2_is_epic_battle == true)
		if(sta2_only_pistol == true)
		{
			#if IS_FULL_STEAM == 1 

			if(STEAM_ACTIVE == true)  
			if(IS_FULL_GAME == true)
			if (g_SteamAchievements)
			{
				g_SteamAchievements->SetAchievement("STA2_MEDAL_11"); // Win a battle with only the pistol...
				if(sta2_globals[GLOBAL_STA2_MEDAL_11] == GLOBALS_RESET)
				{
					sta2_globals[GLOBAL_STA2_MEDAL_11] = GLOBALS_ACTIVE;
					firework_sfx = true;

				}
			}

			#endif
		}

	}   

	if(sta2_event == PAGE_SPEED_RESULT)                  
	{      
		page[0].no_of_pages = 1;    
	   
		page[0].type = PAGE_SPEED_RESULT;      
		page[0].option1 = OPTION_CONTINUE;     
		page[0].option2 = OPTION_NONE;    
		page[0].option3 = OPTION_NONE;          
		page[0].option4 = OPTION_NONE;     
		page[0].choice = CHOICE_NONE;  

		if(sta2_got_epic_bonus == true)
			Sta2LoadText("data/text/victory/victoryE.txt", page[0].word_text, -1, WW_NONE);  
		else
			Sta2LoadText("data/text/victory/victoryS.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

		if(sta2_is_epic_battle == true)
			page[0].option1 = OPTION_SECTOR_GO;
		if(sta2_got_double_bonus == true || sta2_got_triple_bonus == true)
			page[0].option1 = OPTION_BONUS;
	}    
	if(sta2_event == PAGE_BONUS_RESULT)                  
	{      
		page[0].no_of_pages = 1;    
	   
		page[0].type = PAGE_BONUS_RESULT;      
		page[0].option1 = OPTION_CONTINUE;      
		page[0].option2 = OPTION_NONE;    
		page[0].option3 = OPTION_NONE;          
		page[0].option4 = OPTION_NONE;     
		page[0].choice = CHOICE_NONE;  

		if(sta2_got_double_bonus == true)
			Sta2LoadText("data/text/victory/victoryD.txt", page[0].word_text, -1, WW_NONE);  
		if(sta2_got_triple_bonus == true)
			Sta2LoadText("data/text/victory/victoryT.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

		if(sta2_is_epic_battle == true)
			page[0].option1 = OPTION_SECTOR_GO;
	}   

	if(sta2_event == PAGE_QUEST)                  
	{      
		page[0].no_of_pages = 1;    
	  
		page[0].type = PAGE_QUEST;     
		page[0].option1 = OPTION_CONTINUE;    
		page[0].option2 = OPTION_CONTINUE;    
		page[0].option3 = OPTION_NONE;          
		page[0].option4 = OPTION_NONE;     
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/quest/quest.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Accept.");
		sprintf( page[0].word_option2, "2 : Decline.");

	}   

	if(sta2_event == PAGE_GAMBLE)                 
	{      
		page[0].no_of_pages = 1;   
	   
		page[0].type = PAGE_GAMBLE;     
		page[0].option1 = OPTION_GAMBLE_READY;    
		page[0].option2 = OPTION_CONTINUE;   
		page[0].option3 = OPTION_NONE;          
		page[0].option4 = OPTION_NONE;     
		page[0].choice = CHOICE_NONE;   

		Sta2LoadText("data/text/gamble/gamble.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Go gambling!");
		sprintf( page[0].word_option2, "2 : Leave the area.");

		//Not enough food or gold for the trade... 
		if(sta2_gold < Get_Bet_Amount())  
		{ 
			page[0].option1 = OPTION_CONTINUE;
			page[0].option2 = OPTION_NONE;
			new_counter[3].greyed = true; // Greyed out...
			sprintf( page[0].word_option1, "1 : Not enough to gamble.");
		}
		else 
		{
			sprintf( page[0].word_option1, "1 : Go gambling!");
			sprintf( page[0].word_option2, "2 : Leave the area.");
		}		 
	}   

	if(sta2_event == PAGE_GAMBLE_READY)                 
	{      
		page[0].no_of_pages = 1;   
	  
		page[0].type = PAGE_GAMBLE_READY;     
		page[0].option1 = OPTION_GAMBLE;    
		page[0].option2 = OPTION_NONE;   
		page[0].option3 = OPTION_NONE;          
		page[0].option4 = OPTION_NONE;     
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/gamble/gambleG.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Okay!");
	//	sprintf( page[0].word_option2, "2 : Leave the area.");
		 
	}   

	if(sta2_event == PAGE_STORE)                 
	{       
		page[0].no_of_pages = 1;   
	  
		page[0].type = PAGE_STORE;     
		page[0].option1 = OPTION_STORE;    
		page[0].option2 = OPTION_CONTINUE;   
		page[0].option3 = OPTION_NONE;         
		page[0].option4 = OPTION_NONE;     
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/store/store.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Go shopping!");
		sprintf( page[0].word_option2, "2 : Leave the area.");

	}   
		 
	if(sta2_event == PAGE_HUNT)                 
	{      
		page[0].no_of_pages = 1;   
	  
		page[0].type = PAGE_HUNT;     
		page[0].option1 = OPTION_HUNT;    
		page[0].option2 = OPTION_CONTINUE;   
		page[0].option3 = OPTION_NONE;         
		page[0].option4 = OPTION_NONE;     
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/hunt/hunt.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Go hunt!"); 
		sprintf( page[0].word_option2, "2 : Leave the area.");

	}  

	if(sta2_event == PAGE_TRADE)                
	{       
		page[0].no_of_pages = 1;   
	  
		page[0].type = PAGE_TRADE;      
		page[0].option1 = OPTION_TRADE;         
		page[0].option2 = OPTION_CONTINUE;  
		page[0].option3 = OPTION_NONE;         
		page[0].option4 = OPTION_NONE;     
		page[0].choice = CHOICE_NONE;   

		Sta2LoadText("data/text/trade/trade.txt", page[0].word_text, -1, WW_TRADE);  

		sprintf( page[0].word_option1, "1 : Accept.");
		sprintf( page[0].word_option2, "2 : Decline.");

		//Not enough food or gold for the trade...
		if(sta2_trade.active == false)  
		{ 
			page[0].option1 = OPTION_CONTINUE;
			page[0].option2 = OPTION_NONE;
			new_counter[3].greyed = true; // Greyed out...
			sprintf( page[0].word_option1, "1 : Not enough to trade.");
		}
		else
		{
			sprintf( page[0].word_option1, "1 : Accept.");
			sprintf( page[0].word_option2, "2 : Decline.");
		}

	}   
		      
	if(sta2_event == PAGE_TRADE_RESULT)            
	{ 
		page[0].no_of_pages = 1;  
	      
		page[0].type = PAGE_CHANCE_RESULT;      
		page[0].option1 = OPTION_CONTINUE; 
		page[0].option2 = OPTION_NONE;  
		page[0].option3 = OPTION_NONE;      
		page[0].option4 = OPTION_NONE;    
		page[0].choice = CHOICE_NONE;  

		Run_Trade(); 

		Sta2LoadText("data/text/trade/tradeR.txt", page[0].word_text, sta2_global_use_id, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

	} 

	if(sta2_event == PAGE_BRIBE)                 
	{  
		page[0].no_of_pages = 1;    
	  
		page[0].type = PAGE_BRIBE;        
		page[0].option1 = OPTION_SQUAD;     
		page[0].option2 = OPTION_BRIBE;  
		page[0].option3 = OPTION_NONE;         
		page[0].option4 = OPTION_NONE;     
		page[0].choice = CHOICE_NONE;  

		if(sta2_environment_type == AREA_CITY)
			Sta2LoadText("data/text/bribe/bribeC.txt", page[0].word_text, -1, WW_NONE);  
		else
			Sta2LoadText("data/text/bribe/bribe.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Fight them!");
		sprintf( page[0].word_option2, "2 : Pay them to pass.");

		//Not enough food or gold for the trade...
		if(sta2_trade.active == false)      
		{ 
			page[0].option2 = OPTION_SQUAD; 
			new_counter[4].greyed = true; // Greyed out...
		}
		 
	}  
	 
	if(sta2_event == PAGE_BRIBE_RESULT)               
	{  
		page[0].no_of_pages = 1;     
	  
		page[0].type = PAGE_BRIBE_RESULT;     
		page[0].option1 = OPTION_CONTINUE;    
		page[0].option2 = OPTION_NONE;   
		page[0].option3 = OPTION_NONE;        
		page[0].option4 = OPTION_NONE;     
		page[0].choice = CHOICE_NONE;  

		Run_Trade();

		Sta2LoadText("data/text/bribe/bribeR.txt", page[0].word_text, sta2_global_use_id, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

	}

	if(sta2_event == PAGE_CHANCE)          
	{
		page[0].no_of_pages = 1;  
	   
		page[0].type = PAGE_CHANCE;    
		page[0].option1 = OPTION_INVESTIGATE; 
		page[0].option2 = OPTION_CONTINUE;  
		page[0].option3 = OPTION_NONE;      
		page[0].option4 = OPTION_NONE;   
		page[0].choice = CHOICE_NONE;  

		if(sta2_environment_type == AREA_GRASSLANDS)
			Sta2LoadText("data/text/chance/chance_grass.txt", page[0].word_text, -1, WW_NONE);  
		if(sta2_environment_type == AREA_FOREST)
			Sta2LoadText("data/text/chance/chance_forest.txt", page[0].word_text, -1, WW_NONE);  
		if(sta2_environment_type == AREA_SWAMP)
			Sta2LoadText("data/text/chance/chance_swamp.txt", page[0].word_text, -1, WW_NONE);  
		if(sta2_environment_type == AREA_FARM)
			Sta2LoadText("data/text/chance/chance_farm.txt", page[0].word_text, -1, WW_NONE);  
		if(sta2_environment_type == AREA_SNOW)
			Sta2LoadText("data/text/chance/chance_snow.txt", page[0].word_text, -1, WW_NONE);  
		if(sta2_environment_type == AREA_DESERT)
			Sta2LoadText("data/text/chance/chance_desert.txt", page[0].word_text, -1, WW_NONE); 
		if(sta2_environment_type == AREA_MOUNTAIN)
			Sta2LoadText("data/text/chance/chance_snow.txt", page[0].word_text, -1, WW_NONE);  
		if(sta2_environment_type == AREA_BEACH)
			Sta2LoadText("data/text/chance/chance_desert.txt", page[0].word_text, -1, WW_NONE);  
		if(sta2_environment_type == AREA_CITY)
			Sta2LoadText("data/text/chance/chance_city.txt", page[0].word_text, -1, WW_NONE);  
		if(sta2_environment_type == AREA_TRENCH)
			Sta2LoadText("data/text/chance/chance_trench.txt", page[0].word_text, -1, WW_NONE);  
		if(sta2_environment_type == AREA_CASTLE)
			Sta2LoadText("data/text/chance/chance_forest.txt", page[0].word_text, -1, WW_NONE);

		if(SquadCount() >= 1)
			sprintf( page[0].word_option1, "1 : Send a unit to investigate.");
		else
		{
			sprintf( page[0].word_option1, "1 : No units left to investigate.");
			page[0].option1 = OPTION_CONTINUE;
			new_counter[3].greyed = true;
		}
		sprintf( page[0].word_option2, "2 : Leave the area.");
	}  
		      
	if(sta2_event == PAGE_CHANCE_RESULT)         
	{
		page[0].no_of_pages = 1;  
	    
		page[0].type = PAGE_CHANCE_RESULT;     
		page[0].option1 = OPTION_CONTINUE;
		page[0].option2 = OPTION_NONE;
		page[0].option3 = OPTION_NONE;       
		page[0].option4 = OPTION_NONE;    
		page[0].choice = CHOICE_NONE;  

		if(rand()%2 == 0)
		{
			if(sta2_environment_type == AREA_GRASSLANDS)
				Sta2LoadText("data/text/chance/chanceG_grass.txt", page[0].word_text, sta2_global_use_id, WW_GAIN); 
			if(sta2_environment_type == AREA_FOREST)
				Sta2LoadText("data/text/chance/chanceG_forest.txt", page[0].word_text, sta2_global_use_id, WW_GAIN); 
			if(sta2_environment_type == AREA_SWAMP)
				Sta2LoadText("data/text/chance/chanceG_swamp.txt", page[0].word_text, sta2_global_use_id, WW_GAIN); 
			if(sta2_environment_type == AREA_FARM)
				Sta2LoadText("data/text/chance/chanceG_farm.txt", page[0].word_text, sta2_global_use_id, WW_GAIN); 
			if(sta2_environment_type == AREA_SNOW)
				Sta2LoadText("data/text/chance/chanceG_snow.txt", page[0].word_text, sta2_global_use_id, WW_GAIN); 
			if(sta2_environment_type == AREA_DESERT)
				Sta2LoadText("data/text/chance/chanceG_desert.txt", page[0].word_text, sta2_global_use_id, WW_GAIN); 
			if(sta2_environment_type == AREA_MOUNTAIN)
				Sta2LoadText("data/text/chance/chanceG_snow.txt", page[0].word_text, sta2_global_use_id, WW_GAIN); 
			if(sta2_environment_type == AREA_BEACH)
				Sta2LoadText("data/text/chance/chanceG_desert.txt", page[0].word_text, sta2_global_use_id, WW_GAIN); 
			if(sta2_environment_type == AREA_CITY)
				Sta2LoadText("data/text/chance/chanceG_city.txt", page[0].word_text, sta2_global_use_id, WW_GAIN); 
			if(sta2_environment_type == AREA_TRENCH)
				Sta2LoadText("data/text/chance/chanceG_trench.txt", page[0].word_text, sta2_global_use_id, WW_GAIN); 
			if(sta2_environment_type == AREA_CASTLE)
				Sta2LoadText("data/text/chance/chanceG_forest.txt", page[0].word_text, sta2_global_use_id, WW_GAIN); 
		}
		else
		{ 
			if(sta2_environment_type == AREA_GRASSLANDS)
				Sta2LoadText("data/text/chance/chanceB_grass.txt", page[0].word_text, sta2_global_use_id, WW_LOST); 
			if(sta2_environment_type == AREA_FOREST)
				Sta2LoadText("data/text/chance/chanceB_forest.txt", page[0].word_text, sta2_global_use_id, WW_LOST); 
			if(sta2_environment_type == AREA_SWAMP)
				Sta2LoadText("data/text/chance/chanceB_swamp.txt", page[0].word_text, sta2_global_use_id, WW_LOST); 
			if(sta2_environment_type == AREA_FARM)
				Sta2LoadText("data/text/chance/chanceB_farm.txt", page[0].word_text, sta2_global_use_id, WW_LOST); 
			if(sta2_environment_type == AREA_SNOW)
				Sta2LoadText("data/text/chance/chanceB_snow.txt", page[0].word_text, sta2_global_use_id, WW_LOST); 
			if(sta2_environment_type == AREA_DESERT)
				Sta2LoadText("data/text/chance/chanceB_desert.txt", page[0].word_text, sta2_global_use_id, WW_LOST); 
			if(sta2_environment_type == AREA_MOUNTAIN)
				Sta2LoadText("data/text/chance/chanceB_snow.txt", page[0].word_text, sta2_global_use_id, WW_LOST); 
			if(sta2_environment_type == AREA_BEACH)
				Sta2LoadText("data/text/chance/chanceB_desert.txt", page[0].word_text, sta2_global_use_id, WW_LOST); 
			if(sta2_environment_type == AREA_CITY)
				Sta2LoadText("data/text/chance/chanceB_city.txt", page[0].word_text, sta2_global_use_id, WW_LOST); 
			if(sta2_environment_type == AREA_TRENCH)
				Sta2LoadText("data/text/chance/chanceB_trench.txt", page[0].word_text, sta2_global_use_id, WW_LOST); 
			if(sta2_environment_type == AREA_CASTLE)
				Sta2LoadText("data/text/chance/chanceB_forest.txt", page[0].word_text, sta2_global_use_id, WW_LOST); 
		}

		sprintf( page[0].word_option1, "1 : Continue.");

	} 

 	if(sta2_event == PAGE_BEAT_TUTORIAL)               
	{ 

		cheer_sfx = true;

		page[0].no_of_pages = 1;  
	  
		page[0].type = PAGE_BEAT_TUTORIAL;    
		page[0].option1 = OPTION_TITLE;    
		page[0].option2 = OPTION_NONE;  
		page[0].option3 = OPTION_NONE;       
		page[0].option4 = OPTION_NONE;    
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/intro/tutorial.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

		// Setup initial layouts...
//		sta2_layouts[LAYOUT_ADA][0] = LAYOUT_OPEN;
//		sta2_layouts[LAYOUT_ADA][1] = LAYOUT_OPEN;
//		sta2_layouts[LAYOUT_ADA][2] = LAYOUT_OPEN;

//		sta2_layouts[LAYOUT_MARIE][0] = LAYOUT_OPEN; 

	}  

 	if(sta2_event == PAGE_BEAT_TRAINING)               
	{ 

		cheer_sfx = true;

		page[0].no_of_pages = 1;  
	  
		page[0].type = PAGE_BEAT_TRAINING;    
		page[0].option1 = OPTION_ENDGAME;    
		page[0].option2 = OPTION_NONE;  
		page[0].option3 = OPTION_NONE;       
		page[0].option4 = OPTION_NONE;    
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/intro/training.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

	}  

	if(sta2_event == PAGE_BATTLE)                
	{ 
		page[0].no_of_pages = 1;  
	  
		page[0].type = PAGE_BATTLE;    
		page[0].option1 = OPTION_SQUAD;    
		page[0].option2 = OPTION_AVOID;  
		page[0].option3 = OPTION_NONE;       
		page[0].option4 = OPTION_NONE;    
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/battle/battle.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Fight them!");

		if(sta2_playing_tutorial == false)
			sprintf( page[0].word_option2, "2 : Sneak around them.");
		else
			page[0].option2 = OPTION_NONE;

	}  

	if(sta2_event == PAGE_BATTLE_AVOID_GOOD)                   
	{
		page[0].no_of_pages = 1;           
	   
		page[0].type = PAGE_BATTLE_AVOID_GOOD;        
		page[0].option1 = OPTION_CONTINUE;  
		page[0].option2 = OPTION_NONE; 
		page[0].option3 = OPTION_NONE;      
		page[0].option4 = OPTION_NONE;    
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/battle/battle_avoidG.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Continue.");

	} 

	if(sta2_event == PAGE_BATTLE_AVOID_FAIL)                   
	{
		page[0].no_of_pages = 1;           
	   
		page[0].type = PAGE_BATTLE_AVOID_FAIL;         
		page[0].option1 = OPTION_SQUAD;   
		page[0].option2 = OPTION_NONE; 
		page[0].option3 = OPTION_NONE;      
		page[0].option4 = OPTION_NONE;    
		page[0].choice = CHOICE_NONE;  

		Sta2LoadText("data/text/battle/battle_avoidB.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Fight them!");

	}
	     
	if(sta2_event == PAGE_EMPTY)           
	{
		page[0].no_of_pages = 1;  
	  
		page[0].type = PAGE_EMPTY;     
		page[0].option1 = OPTION_CONTINUE;
		page[0].option2 = OPTION_NONE;
		page[0].option3 = OPTION_NONE;      
		page[0].option4 = OPTION_NONE;   
		page[0].choice = CHOICE_NONE; 

		if(SquadCount() >= 1)
		{
			if(sta2_environment_type == AREA_GRASSLANDS)
				Sta2LoadText("data/text/empty/empty_grass.txt", page[0].word_text, -1, WW_NONE);  
			if(sta2_environment_type == AREA_FOREST)
				Sta2LoadText("data/text/empty/empty_forest.txt", page[0].word_text, -1, WW_NONE);  
			if(sta2_environment_type == AREA_SWAMP)
				Sta2LoadText("data/text/empty/empty_swamp.txt", page[0].word_text, -1, WW_NONE);  
			if(sta2_environment_type == AREA_FARM)
				Sta2LoadText("data/text/empty/empty_farm.txt", page[0].word_text, -1, WW_NONE);  
			if(sta2_environment_type == AREA_SNOW)
				Sta2LoadText("data/text/empty/empty_snow.txt", page[0].word_text, -1, WW_NONE);  
			if(sta2_environment_type == AREA_DESERT)
				Sta2LoadText("data/text/empty/empty_desert.txt", page[0].word_text, -1, WW_NONE); 
			if(sta2_environment_type == AREA_MOUNTAIN)
				Sta2LoadText("data/text/empty/empty_snow.txt", page[0].word_text, -1, WW_NONE);  
			if(sta2_environment_type == AREA_BEACH)
				Sta2LoadText("data/text/empty/empty_desert.txt", page[0].word_text, -1, WW_NONE);  
			if(sta2_environment_type == AREA_CITY)
				Sta2LoadText("data/text/empty/empty_city.txt", page[0].word_text, -1, WW_NONE);  
			if(sta2_environment_type == AREA_TRENCH)
				Sta2LoadText("data/text/empty/empty_trench.txt", page[0].word_text, -1, WW_NONE);  
			if(sta2_environment_type == AREA_CASTLE)
				Sta2LoadText("data/text/empty/empty_forest.txt", page[0].word_text, -1, WW_NONE);

		}
		else
			Sta2LoadText("data/text/empty/empty_solo.txt", page[0].word_text, -1, WW_SOLO);  


		sprintf( page[0].word_option1, "1 : Leave the area.");

	} 
	 
	if(sta2_event == PAGE_WIZARD)           
	{
		page[0].no_of_pages = 1; 
	 
		page[0].type = PAGE_WIZARD;    
		page[0].option1 = OPTION_WIZARD; 
		page[0].option2 = OPTION_CONTINUE;  
		page[0].option3 = OPTION_NONE;       
		page[0].option4 = OPTION_NONE;  
		page[0].choice = CHOICE_NONE; 

		sta2_toll = 1+rand()%18 + (sta2_sector*2); 

		Sta2LoadText("data/text/wizard/wizard.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Try healing the squad for %iG.", sta2_toll);
		sprintf( page[0].word_option2, "2 : Leave the madman alone.");

		//Not enough food or gold for the trade...
		if(sta2_gold < sta2_toll)        
		{ 
			new_counter[3].greyed = true; // Greyed out...// Option2  
		}
	}

	if(sta2_event == PAGE_WIZARD_RESULT)          
	{ 
		page[0].no_of_pages = 1;   
	   
		page[0].type = PAGE_WIZARD_RESULT;      
		page[0].option1 = OPTION_CONTINUE; 
		page[0].option2 = OPTION_NONE; 
		page[0].option3 = OPTION_NONE;    
		page[0].option4 = OPTION_NONE;   
		page[0].choice = CHOICE_NONE;  

		sta2_gold-=sta2_toll;  

		if(rand()%2 == 0)
		{
			Sta2LoadText("data/text/wizard/wizardG.txt", page[0].word_text, -1, WW_GAIN);  
			HealAllTeam();
		}
		else
			Sta2LoadText("data/text/wizard/wizardB.txt", page[0].word_text, -1, WW_LOST);  

		sprintf( page[0].word_option1, "1 : Continue."); 

	} 

	if(sta2_event == PAGE_OBSTACLE_RIVER)           
	{
		page[0].no_of_pages = 1; 
	 
		page[0].type = PAGE_OBSTACLE_RIVER;    
		page[0].option1 = OPTION_SWIM; 
		page[0].option2 = OPTION_FERRY;  
		page[0].option3 = OPTION_NONE;      
		page[0].option4 = OPTION_NONE;   
		page[0].choice = CHOICE_NONE; 

		sta2_toll = 1+rand()%18 + (sta2_sector*2); 

		Sta2LoadText("data/text/river/river.txt", page[0].word_text, -1, WW_NONE);  

		sprintf( page[0].word_option1, "1 : Try swimming across.");
		sprintf( page[0].word_option2, "2 : Take the ferry for %iG.", sta2_toll);

		//Not enough food or gold for the trade...
		if(sta2_gold < sta2_toll)        
		{ 
			new_counter[4].greyed = true; // Greyed out...// Option2  
		}
	}

	if(sta2_event == PAGE_OBSTACLE_SWIM)         
	{ 
		page[0].no_of_pages = 1;   
	   
		page[0].type = PAGE_OBSTACLE_SWIM;      
		page[0].option1 = OPTION_CONTINUE; 
		page[0].option2 = OPTION_NONE; 
		page[0].option3 = OPTION_NONE;    
		page[0].option4 = OPTION_NONE;   
		page[0].choice = CHOICE_NONE;  

		if(rand()%2 == 0)
			Sta2LoadText("data/text/river/river_swimG.txt", page[0].word_text, -1, WW_GAIN);  
		else
			Sta2LoadText("data/text/river/river_swimB.txt", page[0].word_text, -1, WW_LOST);  

		sprintf( page[0].word_option1, "1 : Continue."); 

	}       

	if(sta2_event == PAGE_OBSTACLE_FERRY)          
	{ 
		page[0].no_of_pages = 1;   
	  
		page[0].type = PAGE_OBSTACLE_SWIM;    
		page[0].option1 = OPTION_CONTINUE; 
		page[0].option2 = OPTION_NONE; 
		page[0].option3 = OPTION_NONE;    
		page[0].option4 = OPTION_NONE;   
		page[0].choice = CHOICE_NONE; 

		sta2_gold-=sta2_toll;  

	//	if(rand()%4 == 0) 
	//		Sta2LoadText("data/text/river/river_ferryB.txt", page[0].word_text, -1, WW_LOST);
	//	else
			Sta2LoadText("data/text/river/river_ferryG.txt", page[0].word_text, -1, WW_GAIN);   

		sprintf( page[0].word_option1, "1 : Continue.");

	}
	 


}

void OptionHandler(int page_no, int option)  
{

	int option_id = 0; 
	 
	if(page_no > 0)
		return;

	// Grab what the option is...
	if(option == 1) 
		option_id = page[page_no].option1;
	if(option == 2)
		option_id = page[page_no].option2;
	if(option == 3)
		option_id = page[page_no].option3;
	if(option == 4) 
		option_id = page[page_no].option4;

	// Run the option... 
	if(option_id == OPTION_CONTINUE)
	{

		// If all units dead game over...
		if(IsSquadAlive()==false)  
		{
			if(sta2_team_starved == true)
			{
				sta2_next_event = EVENT_STARVE;
			//	GetPage(PAGE_STARVE);
				sta2_team_starved = false;  
			}
			else 
			{
				sta2_next_event = EVENT_DEFEAT;
			//	GetPage(PAGE_DEFEAT); 
			}

			episode = 1;        
			scene = 2; 

			next_scene = true;  
		}  
		else 
		{  

			if(page[page_no].type == PAGE_NEW_SECTOR)
				sta2_scroll_route_map = true;

			sta2_fade_out_sequence = 1;

			if(sta2_is_a_trader_event == true)
			{
				sta2_trader_sequence = 2;
			}
			else 
			{
				episode = 1;       
				scene = 28;     
				next_scene = true; 
			}

		}
	}
	if(option_id == OPTION_SQUAD)  
	{
		episode = 1;        
		scene = 5;     

		sta2_battle_ready = true;

		next_scene = true; 
	}
	if(option_id == OPTION_HUNT)
	{
		episode = 3;       
		scene = 0;     
		next_scene = true;   
	}
	if(option_id == OPTION_STORE) 
	{
		episode = 1;       
		scene = 6;     
		next_scene = true; 
	}
	if(option_id == OPTION_GAMBLE)
	{
		sta2_hands_dealt=0;
		episode = 1;      
		scene = 26;     
		next_scene = true; 
	}
	if(option_id == OPTION_FIGHT) 
	{
		episode = 2;     
		scene = 0;  

		sta2_loaded_level = false;  
		next_scene = true;
		   
	} 
	if(option_id == OPTION_BOSS)   
	{
		if(sta2_sector == 8)
			sta2_final_boss = true;

		episode = 1;         
		scene = 5;     

		sta2_is_epic_battle = true;
		sta2_battle_ready = true;

		next_scene = true; 
	}
	if(option_id == OPTION_SECTOR) 
	{
		episode = 1;    
		scene = 3;    
		next_scene = true; 
	} 
	if(option_id == OPTION_DEFEAT)  
	{
		episode = 1;     
		scene = 29;    

		STA2_RemoveSave();

		next_scene = true;
	} 
	// Beaten tutorial..
	if(option_id == OPTION_TITLE)  
	{
		sta2_finished_tutorial = true;
		episode = 0;    
		scene = 1;    
		next_scene = true;
	} 
	// Beat game, final boss not ready yet..
	if(option_id == OPTION_ENDGAME)   
	{ 
		episode = 1;
		scene = 29;

//		episode = 0;    
//		scene = 1;    
		next_scene = true;
	} 

	if(sta2_gold >= sta2_toll)
	if(option_id == OPTION_WIZARD)   
		GetPage(PAGE_WIZARD_RESULT); 

	if(option_id == OPTION_SWIM)  
		GetPage(PAGE_OBSTACLE_SWIM); 

	if(sta2_gold >= sta2_toll)
	if(option_id == OPTION_FERRY)
		GetPage(PAGE_OBSTACLE_FERRY); 

	if(option_id == OPTION_INVESTIGATE) 
		GetPage(PAGE_CHANCE_RESULT);
	 
	if(option_id == OPTION_TRADE)
		GetPage(PAGE_TRADE_RESULT);     

	if(option_id == OPTION_BRIBE)
		GetPage(PAGE_BRIBE_RESULT);

	if(option_id == OPTION_VICTORY) 
		GetPage(PAGE_VICTORY_RESULT);  

	if(option_id == OPTION_SPEED)
		GetPage(PAGE_SPEED_RESULT);

	if(option_id == OPTION_BONUS)
		GetPage(PAGE_BONUS_RESULT);

	if(option_id == OPTION_SECTOR_GO)
	{
		if(sta2_sector != 8)
			GetPage(PAGE_SECTOR_GO); 
		else
		{
			scene = 30;
			episode = 1;

			STA2_RemoveSave();

			next_scene = true;
		}

	}

	if(option_id == OPTION_TUTORIAL)  
		GetPage(PAGE_BEAT_TUTORIAL);   

	if(option_id == OPTION_TRAINING)  
		GetPage(PAGE_BEAT_TRAINING); 

	if(option_id == OPTION_GAMBLE_READY)  
		GetPage(PAGE_GAMBLE_READY); 

	if(option_id == OPTION_AVOID) 
	if(rand()%4 == 0) 
		GetPage(PAGE_BATTLE_AVOID_GOOD); 
	else
		GetPage(PAGE_BATTLE_AVOID_FAIL); 

	if(option_id == OPTION_AVOID_GENERAL) 
	if(rand()%2 == 0) 
		GetPage(PAGE_BATTLE_AVOID_GOOD); 
	else
		GetPage(PAGE_BATTLE_AVOID_FAIL); 
	

}

bool Sta2LoadText( char *filename, char *word, int use_this_id, int type )
{
    bool success=false; 
	int no_lines=0;  
	int rnd=0;
	char dummy_string[1024]; 
	 
    FILE *fp;      
	        
    errno_t err;  
	  
	err  = fopen_s( &fp, filename, "r");           

	if(use_this_id != -1) 
		sta2_global_use_id = use_this_id;

    if (err==NULL)                                                             
    {     
		    
        fscanf(fp,"%i", &no_lines);        
            
        for( int i=0;i<no_lines+1;i++)         
        {  
			if(i!=0)
				fgets(sta2_string[i-1].string, sizeof(dummy_string), fp);
			else
				fgets(dummy_string, sizeof(dummy_string), fp);
        }       
                                  
        fclose(fp);          
		 
        success=true;                     
            
    }      
	else 
		MessageBox(NULL,"Couldn't load X .txt","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);

	if(no_lines > 0)
	{
		if(use_this_id == -1) 
		{
			rnd = rand()%no_lines; 
			sta2_global_use_id = rnd;
			sprintf( word, "%s", sta2_string[rnd].string);
		} 
		else
		{
			if(use_this_id < no_lines)
				sprintf( word, "%s", sta2_string[use_this_id].string);
			else
				sprintf( word, "Error : Something went wrong...");
		} 

		WrapWord(word, 40, type);
	}

    return(success); 
	  
}

bool sta2GetName(char *filename, char *word)
{
    bool success=false;  
	int no_lines=0;  
	int rnd=0;
	char dummy_string[1024];  
	 
    FILE *fp;      
	        
    errno_t err;  
	  
	err  = fopen_s( &fp, filename, "r");  

    if (err==NULL)                                                             
    {      
		    
        fscanf(fp,"%i", &no_lines);         
            
        for( int i=0;i<no_lines+1;i++)          
        {  
			if(i < 128)
			if(i!=0)
			{
//				fgets(sta2_string[i-1].string, sizeof(dummy_string), fp);
				fscanf(fp,"%s", &sta2_string[i-1].string);			
			}
			else
				fgets(dummy_string, sizeof(dummy_string), fp);
        }       

        fclose(fp);          
		 
        success=true;                     
            
    }      
	else 
		MessageBox(NULL,"Couldn't load X .txt","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);

	if(no_lines > 0)  
	{
		rnd = rand()%no_lines; 
		sta2_global_use_id = rnd;
		sprintf( word, "%s", sta2_string[rnd].string);
	}

    return(success); 
}

bool sta2GetEmyNames(char *filename)
{
    bool success=false;    
	int no_lines=0;  
	int rnd=0;
	char dummy_string[1024];  
	 
    FILE *fp;      
	        
    errno_t err;  
	  
	err  = fopen_s( &fp, filename, "r");  

    if (err==NULL)                                                              
    {      
		    
        fscanf(fp,"%i", &no_lines);          
            
        for( int i=0;i<no_lines+1;i++)           
        {   
			if(i < 128) 
			if(i!=0)
			{
				fscanf(fp,"%s", &sta2_emy_names[i-1].string);			
			}
			else
				fgets(dummy_string, sizeof(dummy_string), fp);

        }        

        fclose(fp);          
		 
        success=true;                     
            
    }      
	else 
		MessageBox(NULL,"Couldn't load X .txt","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);

	if(no_lines > 0)  
		sta2_no_enemy_names = no_lines;

    return(success); 
}

int GetLongestLine(char *word) 
{ 
	int longest_line=0;
	int current_line=0; 
	int length=0; 
	     
	length = strlen(word);     
	    
	if(length > 0 && length < 1024)
    for(int i = 0; i < length;i++)              
	{ 
		current_line++; 
		 
		if(word[i] == '^')                   
		{    
			if(current_line > longest_line)
				longest_line = current_line;

			current_line=0;
		}

	}

	return(longest_line);
}

void WrapWord(char *word, unsigned int line_length, int type)
{
	int next_start = 0;  
	int length = 0; 
	char new_string[1024];  
	char name_string[1024];
	int current_position=0;     
	int temp=0;     
	int target=0;  
	int amount=0;
	int text_type=TEXT_NONE;          
	int first_guy=0;       
	int second_guy=0;     
	int rnd = 0;    
	int ww_unit_list[50]; 
	int ww_unit_list_count=0;   
	bool trade_failed = false;
	int gain_gold=0;
	int gain_food=0; 
	int gain_pack=0;  
	int wp_cost=0;
	int selected=-1;  
	 
	if(word[0] == ' ')
		return; 

	if(type == WW_GAIN) // type == WW_LOST, Pick weakest/strongest units.
	{ 
		if(type == WW_GAIN)    
			selected = 10000;  
		if(type == WW_LOST)   
			selected = 0;
		      
		// Get first unit...  
		for(int i = 0; i < sta2_squad_count;i++) 
		if(i!=0 || SquadCount() == 0 && i < 50)   
		{
			if(type == WW_GAIN)
			if(sta2_squad[i].health < selected)
			{
				first_guy = i;
				selected = sta2_squad[i].health;
			}
			if(type == WW_LOST)
			if(sta2_squad[i].health > selected)
			{
				first_guy = i;
				selected = sta2_squad[i].health;
			}
		}   
	}

	if(type == WW_NONE || type == WW_LOST || type == WW_SOLO)
	{ 
		  
		// Get first unit... 
		for(int i = 0; i < sta2_squad_count;i++) 
		if(i!=0 || SquadCount() == 0)
		{
			ww_unit_list[ww_unit_list_count] = i;
			ww_unit_list_count++;
		}    
	   
		if(ww_unit_list_count > 0)  
		{ 
			if(type != WW_SOLO)
				rnd = rand()%ww_unit_list_count;    
			else
				rnd = 0;

			if(rnd >= 0 && rnd < 50)
				first_guy = ww_unit_list[rnd];  

			// Get second unit... 
			for(int i = rnd;i < ww_unit_list_count;i++)
				ww_unit_list[i] = ww_unit_list[i+1];

			ww_unit_list_count--; 
			 
			if(ww_unit_list_count > 0)
				rnd = rand()%ww_unit_list_count; 

			if(rnd >= 0 && rnd < 50)
				second_guy = ww_unit_list[rnd];  
		}
	}  
    
	length = strlen(word);    

	if(length > 0 && length < 1024) 
    for(int i = 0; i < length;i++)              
	{ 
		if((current_position+i) < 1024)
			new_string[current_position+i] = word[i];  
		  
		if(word[i] == '*')                     
		{       
			 
			if(word[i+1] == '1')             
			{   

				if(word[i+2] == 'T') // This squad member took damage...
					target = first_guy; 

				if(first_guy >= 0 && first_guy < 50)
					temp = strlen(sta2_squad[first_guy].string);
		//		temp--;
				 
				if(temp > 0 && temp < 1024) 
				for(int j=0;j<temp;j++) 
				if((current_position+i+j) < 1024)
					new_string[current_position+i+j] = sta2_squad[first_guy].string[j];

				current_position += temp-3; 
				i+=2;
			}  
			if(word[i+1] == '2')          
			{   
				 
				if(word[i+2] == 'T') // This squad member took damage...
					target = second_guy;

				if(second_guy >= 0 && second_guy < 50)
					temp = strlen(sta2_squad[second_guy].string);
		//		temp--;

				if(temp > 0 && temp < 1024)
				for(int j=0;j<temp;j++) 
				if((current_position+i+j) < 1024)
					new_string[current_position+i+j] = sta2_squad[second_guy].string[j];

				current_position += temp-3; 
				i+=2;
			}  

			// Make a trade... 
			if(word[i+1] == 'Q' || word[i+1] == 'W' || word[i+1] == 'E' || word[i+1] == 'A')
			{

				sta2_trade.active = true;  

				if(word[i+2] == '1') // This squad member took damage...
					amount = 10;
				if(word[i+2] == '2') // This squad member took damage...
					amount = 15;
				if(word[i+2] == '3') // This squad member took damage...
					amount = 25;  

				if(word[i+1] == 'W' || word[i+1] == 'A') // Food is more...
					amount *= 4;   

				if(word[i+1] == 'Q') // Give gold  
				{ 
					sta2_trade.cost_type = TRADE_GOLD;
					sta2_trade.cost_amount = amount;
					if(sta2_trade.cost_amount > sta2_gold)
						trade_failed = true;
				}
				if(word[i+1] == 'W') // Give food       
				{
					sta2_trade.cost_type = TRADE_FOOD;
					sta2_trade.cost_amount = amount;
					if(sta2_trade.cost_amount > sta2_food)
						trade_failed = true; 
				}     
				if(word[i+1] == 'E') // Gain gold
				{
					sta2_trade.gain_type = TRADE_GOLD;
					sta2_trade.gain_amount = amount;
				} 
				if(word[i+1] == 'A') // Gain food
				{
					sta2_trade.gain_type = TRADE_FOOD;
					sta2_trade.gain_amount = amount; 
				}

				sprintf( name_string, "%i", amount);  

				temp = strlen(name_string); 

				if(temp > 0 && temp < 1024)
				for(int j=0;j<temp;j++)  
				if((current_position+i+j) < 1024)
					new_string[current_position+i+j] = name_string[j];

				current_position += temp-3; 
				i+=2;
			}    
			 
			if(word[i+1] == 'G' || word[i+1] == 'F')  
			{         

				if(word[i+2] == '1') // This squad member took damage...
					amount = 10+rand()%10; 
				if(word[i+2] == '2') // This squad member took damage...
					amount = 15+rand()%10;
				if(word[i+2] == '3') // This squad member took damage...
					amount = 25+rand()%10;         
				   
				if(word[i+1] == 'G')  
				if(sta2_picked_up_gold != 0)
					amount += sta2_picked_up_gold;
				 
				if(word[i+1] == 'F')
				if(sta2_picked_up_food != 0)
					amount += sta2_picked_up_food;

				if(word[i+1] == 'G')     
					gain_gold = amount;     
				if(word[i+1] == 'F')    
				{
					gain_food = amount*2;
					amount *= 2;
				}

				sprintf( name_string, "%i", amount); 

				temp = strlen(name_string); 

				if(temp > 0 && temp < 1024)
				for(int j=0;j<temp;j++)  
				if((current_position+i+j) < 1024)
					new_string[(current_position+i+j)] = name_string[j];

				current_position += temp-3; 
				i+=2; 
			} 
			 
			if(word[i+1] == 'B')  // Battle gold...
			{         
				 
				amount = (10+(sta2_sector*3)) + rand()%10; 
 
				if(sta2_picked_up_gold != 0)
					amount += sta2_picked_up_gold;

				if(word[i+1] == 'B')    
					gain_gold = amount;      

				sprintf( name_string, "%i", amount); 

				temp = strlen(name_string); 

				if(temp > 0 && temp < 1024)
				for(int j=0;j<temp;j++)  
				if((current_position+i+j) < 1024)
					new_string[current_position+i+j] = name_string[j];

				current_position += temp-3; 
				i+=2; 
			}
			 
			if(word[i+1] == 'C')  // Casino gold...
			{         
				if(sta2_picked_up_gold < 0)
					sta2_picked_up_gold = 0;

				amount = sta2_picked_up_gold;
  
				gain_gold = amount;      

				sprintf( name_string, "%i", amount); 

				temp = strlen(name_string); 

				if(temp > 0 && temp < 1024)
				for(int j=0;j<temp;j++)  
				if((current_position+i+j) < 1024)
					new_string[current_position+i+j] = name_string[j];

				current_position += temp-3; 
				i+=2; 
			}
			 
			if(word[i+1] == 'V')  // Hunt food...
			{         
				 
				amount = sta2_picked_up_food;

				if(word[i+1] == 'V')    
					gain_food = amount;      

				sprintf( name_string, "%i", amount); 

				temp = strlen(name_string); 

				if(temp > 0 && temp < 1024)
				for(int j=0;j<temp;j++)  
				if((current_position+i+j) < 1024)
					new_string[current_position+i+j] = name_string[j];

				current_position += temp-3; 
				i+=2; 
			}
			  
			if(word[i+1] == 'L')  // Weapon Pack level...
			{         

				sprintf( name_string, "%i", sta2_sector+1); 

				temp = strlen(name_string);  

				if(temp > 0 && temp < 1024)
				for(int j=0;j<temp;j++) 
				if((current_position+i+j) < 1024)
					new_string[current_position+i+j] = name_string[j];

				current_position += temp-3; 
				i+=2; 
			}
			  
			if(word[i+1] == 'I')  // Weapon Pack type...
			{         

				if(sta2_co_type == STA2_CO_ADA)
					sprintf( name_string, "Scout"); 
				if(sta2_co_type == STA2_CO_MARIE)
					sprintf( name_string, "Heavy"); 
				if(sta2_co_type == STA2_CO_ADELE)
					sprintf( name_string, "Sniper"); 
				if(sta2_co_type == STA2_CO_BELLA)
					sprintf( name_string, "Mortar"); 

				temp = strlen(name_string);   

				if(temp > 0 && temp < 1024)
				for(int j=0;j<temp;j++) 
				if((current_position+i+j) < 1024)
					new_string[current_position+i+j] = name_string[j];

				current_position += temp-3; 
				i+=2; 
			}
			 
			if(word[i+1] == 'P')  // Weapon Pack trade...
			{       
				sta2_trade.active = true;  
				 
				amount = (10+rand()%16) + ((sta2_sector+1)*15);   

				sta2_trade.cost_type = TRADE_GOLD;
				sta2_trade.cost_amount = amount;
				if(sta2_trade.cost_amount > sta2_gold)
					trade_failed = true; 

				sta2_trade.gain_type = TRADE_PACK;  
				sta2_trade.gain_amount = sta2_sector+1;

				sprintf( name_string, "%i", amount); 

				temp = strlen(name_string); 

				if(temp > 0 && temp < 1024)
				for(int j=0;j<temp;j++)  
				if((current_position+i+j) < 1024)
					new_string[current_position+i+j] = name_string[j];

				current_position += temp-3; 
				i+=2; 
			}

			if(word[i+1] == 'X' || word[i+1] == 'T' || word[i+1] == 'R' || word[i+1] == 'H' )             
			{   
				if(word[i+1] == 'X') 
					text_type = TEXT_DAMAGE;       
				if(word[i+1] == 'T') 
					text_type = TEXT_DAMAGE_ALL;    
				if(word[i+1] == 'R') 
					text_type = TEXT_HEALTH;   
				if(word[i+1] == 'H')  
					text_type = TEXT_HEALTH_ALL;

				if(word[i+2] == '1') // This squad member took damage...
				{
					amount = (sta2_sector * 5) + rand()%5; 
				}  
				if(word[i+2] == '2') // This squad member took damage...
				{
					amount = (sta2_sector * 10) + rand()%5; 
				} 
				if(word[i+2] == '3') // This squad member took damage...
				{
					amount = (sta2_sector * 20) + rand()%5; 
				} 

				sprintf( name_string, "%i", amount); 

				temp = strlen(name_string);

				if(temp > 0 && temp < 1024)
				for(int j=0;j<temp;j++)  
				if((current_position+i+j) < 1024)
					new_string[current_position+i+j] = name_string[j];

				current_position += temp-3; 
				i+=2; 
			} 
		
		}     

		if(i == length-1) 
		if((current_position+i) < 1024)
			new_string[current_position+i] = '\0';  
		  
	}        

	if(trade_failed == true)
		sta2_trade.active = false;

	// Run damage gain code... 
	if(target != -1)        
	{    
		 
		if(gain_gold > 0)  
		{
			sta2_gold += gain_gold; 
			sta2_gold_collected += gain_gold;
		}

		if(gain_food > 0)
			sta2_food += gain_food; 

		if(text_type == TEXT_DAMAGE && amount > 0 && target < 50) 
			sta2_squad[target].health -= amount;

		if(text_type == TEXT_DAMAGE_ALL && amount > 0)
		for(int i=0;i<sta2_squad_count;i++)  
			sta2_squad[i].health -= amount; 
		 
		if(text_type == TEXT_HEALTH && amount > 0 && target < 50)
			sta2_squad[target].health += amount;

		if(text_type == TEXT_HEALTH_ALL && amount > 0)
		for(int i=0;i<sta2_squad_count;i++) 
		if(sta2_squad[i].health > 1)
			sta2_squad[i].health += amount;

		for(int i=0;i<sta2_squad_count;i++) 
		if(sta2_squad[i].health != 0) 
		if(sta2_squad[i].health < 1) 
			sta2_squad[i].health = 1; 
		 
		for(int i=0;i<sta2_squad_count;i++)
		if(sta2_squad[i].health > (TotalSquadScore(i)) ) 
			sta2_squad[i].health = (TotalSquadScore(i));

	}

	      
    if(strlen(new_string) >= line_length)  
    for(int i = line_length; i > 0;i--)  
	if(i >= 0 && i < 1024)     
	if(new_string[i] == ' ')
    {
        new_string[i] = '^';   
		next_start = i;
        break; 
    } 
    if(strlen(new_string) >= (next_start+line_length) )
    for(int i = next_start+line_length; i > 0;i--)
	if(i >= 0 && i < 1024)
    if(new_string[i] == ' ') 
    {
        new_string[i] = '^'; 
		next_start = i;
        break;   
    }  
    if(strlen(new_string) >= (next_start+line_length) )
    for(int i = next_start+line_length; i > 0;i--)
	if(i >= 0 && i < 1024)
    if(new_string[i] == ' ')
    {
        new_string[i] = '^'; 
		next_start = i;
        break;   
    }  
    if(strlen(new_string) >= (next_start+line_length) )
	for(int i = next_start+line_length; i > 0;i--)
	if(i >= 0 && i < 1024)
    if(new_string[i] == ' ')
    {
        new_string[i] = '^';
		next_start = i; 
        break;  
    }  

	sprintf( word, "%s", new_string);


}
 

bool IsSquadAlive()
{
	bool success=true;

	sta2_squad_alive_count = 0;

	for(int i = 0;i < sta2_squad_count; i++)   
	{
		sta2_squad_current_health += sta2_squad[i].health; 
		if(sta2_squad[i].health > 1)
			sta2_squad_alive_count++;
	}

	if(sta2_squad_alive_count == 0)
		success = false;

	return(success);

}

int SquadCount()
{
	int count=0;
	 
	for(int i = 0;i < sta2_squad_count; i++)   
	{
		if(sta2_squad[i].type != STA2_VOID)
		if(sta2_squad[i].type != STA2_CO)
		if(sta2_squad[i].health > 1)
			count++;
	} 

	return(count);

}

void HealAllTeam() 
{

	healup_sfx = true;

	for(int i=0;i<sta2_squad_count;i++)
		sta2_squad[i].health = (TotalSquadScore(i));
	
}

void Run_Ach()
{
	#if IS_FULL_STEAM == 1 

	if(STEAM_ACTIVE == true)   
	if(IS_FULL_GAME == true)
	if (g_SteamAchievements)
	{
		if(sta2_globals[GLOBAL_STA2_MEDAL_0] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_0"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_1] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_1"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_2] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_2"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_3] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_3"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_4] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_4"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_5] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_5"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_6] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_6"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_7] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_7"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_8] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_8"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_9] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_9"); // Perform a triple kill...

		if(sta2_globals[GLOBAL_STA2_MEDAL_10] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_10"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_11] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_11"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_12] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_12"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_13] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_13"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_14] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_14"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_15] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_15"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_16] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_16"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_17] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_17"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_18] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_18"); // Perform a triple kill...
		if(sta2_globals[GLOBAL_STA2_MEDAL_19] == GLOBALS_ACTIVE)
			g_SteamAchievements->SetAchievement("STA2_MEDAL_19"); // Perform a triple kill...

	}

	#endif





}


