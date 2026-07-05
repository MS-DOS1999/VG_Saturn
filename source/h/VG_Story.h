#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64  
#define WIN32_LEAN_AND_MEAN    
#include <windows.h>
#endif    

extern void VG_Init_Story_Minso(int index, int condition, int scene);
extern void VG_Init_Story_Gyeong(int index, int condition, int scene);
extern void VG_Init_Story_Hyuk(int index, int condition, int scene);
extern void VG_Init_Story_Jae(int index, int condition, int scene);

extern void VG_Init_Story_Reese(int index, int condition, int scene);
extern void VG_Init_Story_Siu(int index, int condition, int scene);
extern void VG_Init_Story_Gun(int index, int condition, int scene);
extern void VG_Init_Story_Yohan(int index, int condition, int scene);

extern void VG_Init_Story_Sho(int index, int condition, int scene);
extern void VG_Init_Story_Tia(int index, int condition, int scene);
extern void VG_Init_Story_Saizo(int index, int condition, int scene);
extern void VG_Init_Story_Sang(int index, int condition, int scene);

extern void VG_Init_Story_Kennedy(int index, int condition, int scene);


int VG_Scene_char=0;
int VG_Scene_emotion=0;

int vg_scene_sequence = 0;

int VG_button_pause_timer = 0; 

void VG_Init_Story(int character)      
{  
	VG_story_count = 0;  
	VG_story_totalcount = 0;   

	memset( VG_story_song, 0, sizeof(VG_story_song));
	memset( VG_story_song_victory, 0, sizeof(VG_story_song_victory));
	memset( VG_story_characters, 0, sizeof(VG_story_characters));
	memset( VG_story_background, 0, sizeof(VG_story_background));
	memset( VG_story_conditions, 0, sizeof(VG_story_conditions));
	memset( VG_1_equipment, 0, sizeof(VG_1_equipment)); 
	memset( VG_2_equipment, 0, sizeof(VG_2_equipment));
	memset( VG_story_ai_level, 0, sizeof(VG_story_ai_level)); 
	memset( VG_is_an_alter_story, 0, sizeof(VG_is_an_alter_story));

	VG_CURRENT_STORY_SCENE = 0;

	for(int i=0;i<20;i++)
		VG_has_third_special[i] = true;

	if(character == VG_YOHAN)
	{ 
		 
		VG_story_count = 0; 

		// 1...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_DANGER1;
		VG_story_characters[VG_story_count] = VG_YOHAN;
		VG_story_background[VG_story_count] = VG_YOHAN;
		VG_story_conditions[VG_story_count] = CONDITION_BASIC_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 1;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++; 

		// 2...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_GYEONG;
		VG_story_background[VG_story_count] = VG_GYEONG;
		VG_story_conditions[VG_story_count] = CONDITION_SPECIAL2_ONLY; 
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 2;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;
		 
		// 3...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_MINSO;
		VG_story_background[VG_story_count] = VG_MINSO;
		VG_story_conditions[VG_story_count] = CONDITION_MINE_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 2;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		//4...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_DANGER1;
		VG_story_characters[VG_story_count] = VG_HYUK;
		VG_story_background[VG_story_count] = VG_HYUK;
		VG_story_conditions[VG_story_count] = CONDITION_THROWS_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 2;
		VG_is_an_alter_story[VG_story_count] = true; 
		VG_story_count++; 

		// 5...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_DANGER1;
		VG_story_characters[VG_story_count] = VG_SIU;
		VG_story_background[VG_story_count] = VG_SIU;
		VG_story_conditions[VG_story_count] = CONDITION_COMBO_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 2;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++; 

		// 6...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_HYUK;
		VG_story_background[VG_story_count] = VG_REESE;
		VG_story_conditions[VG_story_count] = CONDITION_NONE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 4;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 7...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_YOHAN;
		VG_story_background[VG_story_count] = VG_JAE;
		VG_story_conditions[VG_story_count] = CONDITION_SURVIVE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]   = 3;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 8...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SANG;
		VG_story_background[VG_story_count] = VG_YOHAN;
		VG_story_conditions[VG_story_count] = CONDITION_TIMED;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 6;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 10...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_YOHAN;
		VG_story_background[VG_story_count] = VG_YOHAN;
		VG_story_conditions[VG_story_count] = CONDITION_LOW_HEALTH;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 8;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 11...CONDITION_ENDING
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_HYUK;
		VG_story_background[VG_story_count] = VG_REESE;
		VG_story_conditions[VG_story_count] = CONDITION_ENDING;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		VG_story_totalcount = VG_story_count;

	}

	if(character == VG_SIU)
	{ 
		 
		VG_story_count = 0; 

		// 1...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SIU;
		VG_story_background[VG_story_count] = VG_TRAINER;
		VG_story_conditions[VG_story_count] = CONDITION_BASIC_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 1;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 2...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_YOHAN;
		VG_story_background[VG_story_count] = VG_SIU;
		VG_story_conditions[VG_story_count] = CONDITION_PIGEON_ONLY; 
		VG_1_equipment[VG_story_count]      = EQUIPMENT_JUST_SP1;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 1;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 3...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_GYEONG;
		VG_story_background[VG_story_count] = VG_GYEONG;
		VG_story_conditions[VG_story_count] = CONDITION_THROWS_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_JUST_SP1;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 4;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++; 

		//4...
		VG_story_song[VG_story_count] = CS_IDLE; 
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_MINSO;
		VG_story_background[VG_story_count] = VG_MINSO;
		VG_story_conditions[VG_story_count] = CONDITION_PISTOL_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 3;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++; 

		// 5...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_HYUK;
		VG_story_background[VG_story_count] = VG_HYUK;
		VG_story_conditions[VG_story_count] = CONDITION_COMBO_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 4;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++; 

		// 6...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_JAE;
		VG_story_background[VG_story_count] = VG_JAE;
		VG_story_conditions[VG_story_count] = CONDITION_NONE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 5;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 7...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_GUN;
		VG_story_background[VG_story_count] = VG_GUN;
		VG_story_conditions[VG_story_count] = CONDITION_TIMED;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]   = 5;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 8...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_TRAINER;
		VG_story_background[VG_story_count] = VG_YOHAN;
		VG_story_conditions[VG_story_count] = CONDITION_MUST_ARREST;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 10...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SANG;
		VG_story_background[VG_story_count] = VG_YOHAN;
		VG_story_conditions[VG_story_count] = CONDITION_LOW_HEALTH;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 11...CONDITION_ENDING
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SIU;
		VG_story_background[VG_story_count] = VG_TRAINER;
		VG_story_conditions[VG_story_count] = CONDITION_ENDING;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		VG_story_totalcount = VG_story_count;

	}

	if(character == VG_GUN)
	{
		 
		VG_story_count = 0; 

		// 1...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SIU;
		VG_story_background[VG_story_count] = VG_GUN;
		VG_story_conditions[VG_story_count] = CONDITION_BASIC_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 1;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 2...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_GUN;
		VG_story_background[VG_story_count] = VG_MINSO;
		VG_story_conditions[VG_story_count] = CONDITION_SPECIAL1_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_JUST_SP1;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 1;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 3...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_GYEONG;
		VG_story_background[VG_story_count] = VG_GYEONG;
		VG_story_conditions[VG_story_count] = CONDITION_CLOTHESLINE_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 4;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		//4...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_TRAINER;
		VG_story_background[VG_story_count] = VG_TRAINER;
		VG_story_conditions[VG_story_count] = CONDITION_COMBO_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 3;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++; 

		// 5...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_REESE;
		VG_story_background[VG_story_count] = VG_REESE;
		VG_story_conditions[VG_story_count] = CONDITION_THROWS_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 3;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 6...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_JAE;
		VG_story_background[VG_story_count] = VG_JAE;
		VG_story_conditions[VG_story_count] = CONDITION_NONE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 4;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 7...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_JAE;
		VG_story_background[VG_story_count] = VG_JAE;
		VG_story_conditions[VG_story_count] = CONDITION_MUST_WASTE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]   = 5;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 8...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_DANGER2;
		VG_story_characters[VG_story_count] = VG_GUN;
		VG_story_background[VG_story_count] = VG_SIU;
		VG_story_conditions[VG_story_count] = CONDITION_MID_HEALTH;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 10...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SANG;
		VG_story_background[VG_story_count] = VG_SANG;
		VG_story_conditions[VG_story_count] = CONDITION_TIMED;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 5;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 11...CONDITION_ENDING
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_IDLE;
		VG_story_characters[VG_story_count] = VG_GUN;
		VG_story_background[VG_story_count] = VG_SIU;
		VG_story_conditions[VG_story_count] = CONDITION_ENDING;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		VG_story_totalcount = VG_story_count;

	}
	 	 	 
	if(character == VG_REESE)
	{
		 
		VG_story_count = 0; 

		// 1...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_MINSO;
		VG_story_background[VG_story_count] = VG_MINSO;
		VG_story_conditions[VG_story_count] = CONDITION_BASIC_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 1;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 2...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_HYUK;
		VG_story_background[VG_story_count] = VG_HYUK;
		VG_story_conditions[VG_story_count] = CONDITION_SPECIAL1_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_JUST_SP1;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 1;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 3...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_REESE;
		VG_story_background[VG_story_count] = VG_REESE;
		VG_story_conditions[VG_story_count] = CONDITION_ELECTRIC_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 4;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		//4...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_JAE;
		VG_story_background[VG_story_count] = VG_GYEONG;
		VG_story_conditions[VG_story_count] = CONDITION_THROWS_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 3;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 5...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_YOHAN;
		VG_story_background[VG_story_count] = VG_JAE;
		VG_story_conditions[VG_story_count] = CONDITION_COMBO_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 4;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;
		 
		// 6...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SIU;
		VG_story_background[VG_story_count] = VG_SIU;
		VG_story_conditions[VG_story_count] = CONDITION_NONE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 4;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 7...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_YOHAN;
		VG_story_background[VG_story_count] = VG_YOHAN;
		VG_story_conditions[VG_story_count] = CONDITION_LOW_HEALTH;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]   = 5;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 8...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_TRAINER;
		VG_story_background[VG_story_count] = VG_TRAINER;
		VG_story_conditions[VG_story_count] = CONDITION_TIMED;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 5;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 9...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_DANGER1;
		VG_story_characters[VG_story_count] = VG_REESE;
		VG_story_background[VG_story_count] = VG_REESE;
		VG_story_conditions[VG_story_count] = CONDITION_SURVIVE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 6;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 10... 
		VG_story_song[VG_story_count] = CS_DANGER2; 
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SANG;
		VG_story_background[VG_story_count] = VG_SANG;
		VG_story_conditions[VG_story_count] = CONDITION_MUST_ARREST; 
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 11...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_REESE;
		VG_story_background[VG_story_count] = VG_REESE;
		VG_story_conditions[VG_story_count] = CONDITION_ENDING;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		VG_story_totalcount = VG_story_count;

	}
	 	 	 
	if(character == VG_JAE)
	{
		 
		VG_story_count = 0; 

		// 1...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_JAE;
		VG_story_background[VG_story_count] = VG_GYEONG;
		VG_story_conditions[VG_story_count] = CONDITION_BASIC_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 1;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 2...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_REESE;
		VG_story_background[VG_story_count] = VG_REESE;
		VG_story_conditions[VG_story_count] = CONDITION_BREAKDANCE_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 1;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 3...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SIU;
		VG_story_background[VG_story_count] = VG_SIU;
		VG_story_conditions[VG_story_count] = CONDITION_SPECIAL2_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 2;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		//4...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SIU;
		VG_story_background[VG_story_count] = VG_SIU;
		VG_story_conditions[VG_story_count] = CONDITION_COMBO_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 2;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 5...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_MINSO;
		VG_story_background[VG_story_count] = VG_MINSO;
		VG_story_conditions[VG_story_count] = CONDITION_THROWS_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 2;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 6...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_MINSO;
		VG_story_background[VG_story_count] = VG_TRAINER;
		VG_story_conditions[VG_story_count] = CONDITION_NONE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 4;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 7...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_HYUK;
		VG_story_background[VG_story_count] = VG_HYUK;
		VG_story_conditions[VG_story_count] = CONDITION_MID_HEALTH;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]   = 5;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 8...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_JAE;
		VG_story_background[VG_story_count] = VG_JAE;
		VG_story_conditions[VG_story_count] = CONDITION_SURVIVE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 6;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 9...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_IDLE;
		VG_story_characters[VG_story_count] = VG_SANG;
		VG_story_background[VG_story_count] = VG_SANG;
		VG_story_conditions[VG_story_count] = CONDITION_TIMED;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 6;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 10...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_JAE;
		VG_story_background[VG_story_count] = VG_GYEONG;
		VG_story_conditions[VG_story_count] = CONDITION_MUST_WASTE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 6;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 11...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_IDLE;
		VG_story_characters[VG_story_count] = VG_JAE;
		VG_story_background[VG_story_count] = VG_JAE;
		VG_story_conditions[VG_story_count] = CONDITION_ENDING;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		VG_story_totalcount = VG_story_count;

	}
	 	 	 
	if(character == VG_HYUK)
	{
		 
		VG_story_count = 0; 

		// 1...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_HYUK;
		VG_story_background[VG_story_count] = VG_HYUK;
		VG_story_conditions[VG_story_count] = CONDITION_BASIC_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 1;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_has_third_special[VG_story_count] = false;
		VG_story_count++;

		// 2...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_GUN;
		VG_story_background[VG_story_count] = VG_GUN;
		VG_story_conditions[VG_story_count] = CONDITION_COMBO_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_JUST_COMBO;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 1;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_has_third_special[VG_story_count] = false;
		VG_story_count++;

		// 3...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_TRAINER; 
		VG_story_background[VG_story_count] = VG_TRAINER;
		VG_story_conditions[VG_story_count] = CONDITION_SURVIVE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_JUST_COMBO;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 2;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_has_third_special[VG_story_count] = false;
		VG_story_count++;

		//4...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SIU;
		VG_story_background[VG_story_count] = VG_SIU;
		VG_story_conditions[VG_story_count] = CONDITION_SPECIAL2_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_JUST_SP2;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 4;
		VG_story_count++;

		// 5...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_REESE;
		VG_story_background[VG_story_count] = VG_REESE;
		VG_story_conditions[VG_story_count] = CONDITION_NONE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_JUST_SP2;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 4;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 6...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_HYUK;
		VG_story_background[VG_story_count] = VG_JAE;
		VG_story_conditions[VG_story_count] = CONDITION_TIMED;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_JUST_SP2;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 5;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 7...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_YOHAN;
		VG_story_background[VG_story_count] = VG_YOHAN;
		VG_story_conditions[VG_story_count] = CONDITION_GRENADES_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 6;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 8...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_JAE;
		VG_story_background[VG_story_count] = VG_MINSO;
		VG_story_conditions[VG_story_count] = CONDITION_NONE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 9...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_JAE;
		VG_story_background[VG_story_count] = VG_GYEONG;
		VG_story_conditions[VG_story_count] = CONDITION_TIMED;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;
		 
		// 10...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SANG;
		VG_story_background[VG_story_count] = VG_GYEONG;
		VG_story_conditions[VG_story_count] = CONDITION_MID_HEALTH;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 11...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_IDLE;
		VG_story_characters[VG_story_count] = VG_TRAINER;
		VG_story_background[VG_story_count] = VG_TRAINER;
		VG_story_conditions[VG_story_count] = CONDITION_ENDING;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		VG_story_totalcount = VG_story_count;

	}
	 	 
	if(character == VG_GYEONG)
	{
		  
		VG_story_count = 0;  
		  
		// 1...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_GYEONG;
		VG_story_background[VG_story_count] = VG_GYEONG;
		VG_story_conditions[VG_story_count] = CONDITION_BASIC_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 1;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 2...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_TRAINER;
		VG_story_background[VG_story_count] = VG_TRAINER;
		VG_story_conditions[VG_story_count] = CONDITION_SPECIAL2_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_JUST_SP2;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 2;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 3...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_HYUK;
		VG_story_background[VG_story_count] = VG_HYUK;
		VG_story_conditions[VG_story_count] = CONDITION_SPECIAL1_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 2;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		//4... 
		VG_story_song[VG_story_count] = CS_IDLE; 
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_MINSO;
		VG_story_background[VG_story_count] = VG_MINSO;
		VG_story_conditions[VG_story_count] = CONDITION_COMBO_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 2;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 5...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_DANGER2;
		VG_story_characters[VG_story_count] = VG_YOHAN;
		VG_story_background[VG_story_count] = VG_YOHAN;
		VG_story_conditions[VG_story_count] = CONDITION_SURVIVE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 5;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 6...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SIU;
		VG_story_background[VG_story_count] = VG_SIU;
		VG_story_conditions[VG_story_count] = CONDITION_THROWS_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 4;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 7...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_GYEONG;
		VG_story_background[VG_story_count] = VG_REESE;
		VG_story_conditions[VG_story_count] = CONDITION_NONE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 6;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 8...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_YOHAN;
		VG_story_background[VG_story_count] = VG_JAE;
		VG_story_conditions[VG_story_count] = CONDITION_MUST_ARREST;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 9...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_MINSO;
		VG_story_background[VG_story_count] = VG_SANG;
		VG_story_conditions[VG_story_count] = CONDITION_NONE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 10...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_IDLE; 
		VG_story_characters[VG_story_count] = VG_SANG;
		VG_story_background[VG_story_count] = VG_SANG;
		VG_story_conditions[VG_story_count] = CONDITION_LOW_HEALTH;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 11...
		VG_story_song[VG_story_count] = CS_VICTORY;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_GYEONG;
		VG_story_background[VG_story_count] = VG_JAE;
		VG_story_conditions[VG_story_count] = CONDITION_ENDING;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		VG_story_totalcount = VG_story_count;

	}
	 
	if(character == VG_MINSO)
	{

		VG_story_count = 0;

		// 1...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_MINSO;
		VG_story_background[VG_story_count] = VG_TRAINER;
		VG_story_conditions[VG_story_count] = CONDITION_BASIC_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_BASIC;
		VG_story_ai_level[VG_story_count]      = 1;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 2...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_YOHAN;
		VG_story_background[VG_story_count] = VG_MINSO;
		VG_story_conditions[VG_story_count] = CONDITION_COMBO_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_JUST_COMBO;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 2;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 3...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_REESE;
		VG_story_background[VG_story_count] = VG_REESE;
		VG_story_conditions[VG_story_count] = CONDITION_SPECIAL1_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_JUST_SP1;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 2;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 4...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_HYUK;
		VG_story_background[VG_story_count] = VG_HYUK;
		VG_story_conditions[VG_story_count] = CONDITION_THROWS_ONLY;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_JUST_SP1;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 3;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		//5...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_GYEONG;
		VG_story_background[VG_story_count] = VG_GYEONG;
		VG_story_conditions[VG_story_count] = CONDITION_NONE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 4;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 6...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_JAE;
		VG_story_background[VG_story_count] = VG_JAE;
		VG_story_conditions[VG_story_count] = CONDITION_MUST_ARREST;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 5;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;
		 
		// 7...
		VG_story_song[VG_story_count] = CS_IDLE;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SIU;
		VG_story_background[VG_story_count] = VG_SIU;
		VG_story_conditions[VG_story_count] = CONDITION_SURVIVE;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 6;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 8...
		VG_story_song[VG_story_count] = CS_DANGER1;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_GUN;
		VG_story_background[VG_story_count] = VG_GUN;
		VG_story_conditions[VG_story_count] = CONDITION_TIMED;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 6;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 9...
		VG_story_song[VG_story_count] = CS_BOSSIDLE;
		VG_story_song_victory[VG_story_count] = CS_BOSSIDLE;
		VG_story_characters[VG_story_count] = VG_MINSO;
		VG_story_background[VG_story_count] = VG_GUN;
		VG_story_conditions[VG_story_count] = CONDITION_LOW_HEALTH;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		// 10...
		VG_story_song[VG_story_count] = CS_DANGER2;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_SANG;
		VG_story_background[VG_story_count] = VG_YOHAN;
		VG_story_conditions[VG_story_count] = CONDITION_MUST_ARREST;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 6;
		VG_is_an_alter_story[VG_story_count] = false;
		VG_story_count++;

		// 11...
		VG_story_song[VG_story_count] = CS_VICTORY;
		VG_story_song_victory[VG_story_count] = CS_VICTORY;
		VG_story_characters[VG_story_count] = VG_MINSO;
		VG_story_background[VG_story_count] = VG_MINSO;
		VG_story_conditions[VG_story_count] = CONDITION_ENDING;
		VG_1_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_2_equipment[VG_story_count]      = EQUIPMENT_ALL;
		VG_story_ai_level[VG_story_count]      = 7;
		VG_is_an_alter_story[VG_story_count] = true;
		VG_story_count++;

		VG_story_totalcount = VG_story_count;

	}

}


void Run_Story(int f_rate)
{

	float X_align = 0.0f;
	float Y_align = 0.0f;
	float temp_speed = 0.0f;
                   
	if(f_rate <= 0)                                                
	    f_rate = 1;        

	if(f_rate >= 50)
		f_rate = 50; 

	// ******************************************************************************//
	//                            6-2  (CUTSCENE MODE)                               //
	// ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode) 
   if(next_scene == false) 
   if(episode == 6 && scene == 2)        
   {        
		 
		if(title_sequence == 0)  
		{ 

			if(VG_STORY_SETUP == VG_STORY_SCENE_WON)
				VG_CS_SONG = VG_story_song_victory[VG_CURRENT_STORY_SCENE];
			else
				VG_CS_SONG = VG_story_song[VG_CURRENT_STORY_SCENE];

			sprite[1].mov_x = sprite[1].x;
			sprite[2].mov_x = sprite[2].x; 

			sprite[1].x = sprite[0].x + sprite[0].width;
			sprite[2].x = sprite[0].x - sprite[2].width;

			vg_scene_sequence = 0;

			VG_Scene_char=0;
			VG_Scene_emotion=0;
			 
			if(VG_GAME_MODE == VG_ARCADE_MODE)
			{
				VG_CS_SONG = CS_VICTORY;

				if(VG_1_CHARACTER == VG_YOHAN)
					VG_CS_SONG = CS_DANGER2;

				VG_CURRENT_STORY_SCENE = 101;
				VG_STORY_SETUP = VG_STORY_SCENE_LAST; 

				if(VG_SURVIVAL == false)
				{
					VG_BATTLE_ROUND++;

					if(VG_BATTLE_ROUND > 9)
						VG_BATTLE_ROUND = 9;

				}

				#if IS_FULL_STEAM == 1 
				if(STEAM_ACTIVE == true)
				{
					// Upload current score...
					if(VG_STEAM_DEMO == 0)
					if(VG_SURVIVAL == true)
						VG_Upload_Score(1);
					else
						VG_Upload_Score(0);
				}
				#endif

				#if IS_FULL_STEAM == 1 
				if(VG_SURVIVAL == false)
				if(VG_STEAM_DEMO == 0)
				if(STEAM_ACTIVE == true)
				{
					platform_unlock_achievement(10);
				}
				#endif

			}

			if(VG_1_CHARACTER == VG_GYEONG)
				VG_Init_Story_Gyeong(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_MINSO)
				VG_Init_Story_Minso(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_HYUK)
				VG_Init_Story_Hyuk(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_JAE)
				VG_Init_Story_Jae(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);

			if(VG_1_CHARACTER == VG_REESE)
				VG_Init_Story_Reese(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_SIU)
				VG_Init_Story_Siu(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_YOHAN)
				VG_Init_Story_Yohan(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_GUN)
				VG_Init_Story_Gun(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_SHO)
				VG_Init_Story_Sho(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_TIA)
				VG_Init_Story_Tia(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_SAIZO)
				VG_Init_Story_Saizo(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_SANG)
				VG_Init_Story_Sang(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_KENNEDY)
				VG_Init_Story_Kennedy(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);

			new_counter[1].alpha = 1.0f;                 
			new_counter[1].id = 0;       
			new_counter[1].x = -0.32f;         
			new_counter[1].y = sprite[2].y - 0.04f;
			new_counter[1].type = 2;  // Large Font...  
			new_counter[1].right = false; 

			sprintf( new_counter[2].word, "^     %c: NEXT ESC: BACK^", VG_P1_PUNCH1_KEY_DSY); 
			  
			new_counter[2].alpha = 1.0f;                     
			new_counter[2].id = 3;        
				  
			new_counter[2].type = 1;  // Small Font...
			new_counter[2].right = false;

			new_counter[2].x = -0.28f;                     
			new_counter[2].y = -0.33f;          

			new_counter[2].w = new_counter[2].x - 0.026f;   
			new_counter[2].z = new_counter[2].y - 0.015f; 

			new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
			new_counter[2].box_height = new_counter[2].height - 0.015f;	

			sprite[2].alpha = 0.0f;

			 title_sequence++; 
		}   
		 
		if(title_sequence == 1)        
		{ 
			temp_speed = (0.00125f/VG_slowmof)*(float)f_rate;
			     
			sprite[1].x -= temp_speed;   
			sprite[2].x += temp_speed;     
			     
			if(sprite[1].x <= sprite[1].mov_x)   
			{      
				sprite[1].x = sprite[1].mov_x;
				sprite[2].x = sprite[2].mov_x;   

				title_sequence++;
			}
			 
		}
		 
		// Animate-setup sprites...

		if(VG_Scene_char == 101 || VG_Scene_char == 102) // Quit command...
			title_sequence = 3;

		if(VG_1_HUD_BACK == true)
		if(VG_STORY_SETUP != VG_STORY_SCENE_LAST) // Can't skip final scene...
		{
			if(VG_GAME_MODE == VG_STORY_MODE)
			{
				if(VG_CURRENT_STORY_SCENE == 10 && VG_1_CHARACTER == VG_GYEONG)
					VG_Scene_char = 102;
				if(VG_CURRENT_STORY_SCENE == 9 && VG_1_CHARACTER == VG_SIU)
					VG_Scene_char = 102;
				if(VG_CURRENT_STORY_SCENE == 10 && VG_1_CHARACTER == VG_MINSO)
					VG_Scene_char = 102;
				if(VG_CURRENT_STORY_SCENE == 10 && VG_1_CHARACTER == VG_REESE)
					VG_Scene_char = 102;

				if(VG_CURRENT_STORY_SCENE == 9 && VG_1_CHARACTER == VG_YOHAN)
					VG_Scene_char = 102;
				if(VG_CURRENT_STORY_SCENE == 10 && VG_1_CHARACTER == VG_JAE)
					VG_Scene_char = 102;
				if(VG_CURRENT_STORY_SCENE == 9 && VG_1_CHARACTER == VG_GUN)
					VG_Scene_char = 102;
				if(VG_CURRENT_STORY_SCENE == 10 && VG_1_CHARACTER == VG_HYUK)
					VG_Scene_char = 102;

			} 

			if(VG_SURVIVAL == false) 
			if(VG_GAME_MODE == VG_ARCADE_MODE) 
			if(VG_STORY_SETUP == VG_STORY_SCENE_LAST) 
				VG_Scene_char = 102;

			title_sequence = 3;
			VG_reset_input();
		}

		if(VG_GAME_MODE == VG_ARCADE_MODE) 
		{
			// Background picture...
			if(VG_Scene_char < 16)
			{
				sprite[1].alpha = 0.0f; // LEFT
				sprite[2].alpha = 0.0f; // RIGHT

				Set_Sprite(3, VG_Scene_char, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Background left...
			}
		}

		if(VG_GAME_MODE != VG_ARCADE_MODE)
		{
			// LEFT guy talking...
			if(VG_Scene_char == 0)  
			{
				// LEFT guy facing with emotion...
				Set_Sprite(1, VG_Scene_emotion, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				// RIGHT guy back facing...
				Set_Sprite(2, 15, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				Set_Sprite(3, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Background left...

				sprite[1].alpha = 1.0f;
				sprite[2].alpha = 1.0f;
			}
			// RIGHT guy talking...
			if(VG_Scene_char == 1)
			{
				// RIGHT guy facing with emotion...
				Set_Sprite(2, VG_Scene_emotion, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				// LEFT guy back facing...
				Set_Sprite(1, 15, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				Set_Sprite(3, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Background left...

				sprite[1].alpha = 1.0f;
				sprite[2].alpha = 1.0f; 
			}
			// Background picture...
			if(VG_Scene_char > 1 && VG_Scene_char < 8)
			{
				sprite[1].alpha = 0.0f; // LEFT
				sprite[2].alpha = 0.0f; // RIGHT

				Set_Sprite(3, VG_Scene_char, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Background left...
			}

			// Only RIGHT guy in scene...
			if(VG_Scene_char == 10) 
			{
				// RIGHT guy with emotion...
				Set_Sprite(2, 15, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);
				// Char one back facing...
				Set_Sprite(1, 15, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				Set_Sprite(3, 1, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Background left...

				sprite[1].alpha = 0.0f;  // LEFT
				sprite[2].alpha = 1.0f;  // RIGHT
			}
		  
			// Only left guy in scene...
			if(VG_Scene_char == 11) 
			{
				// Char two front facing with emotion...
				Set_Sprite(2, 15, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				Set_Sprite(1, 15, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING);

				Set_Sprite(3, 0, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Background left...

				sprite[1].alpha = 1.0f; // LEFT
				sprite[2].alpha = 0.0f; // RIGHT
			} 
		}   

		if(VG_P1_USING == VG_KEYBOARD)   
		{
			if(VG_STORY_SETUP != VG_STORY_SCENE_LAST)
				sprintf( new_counter[2].word, "^     %c: NEXT %c: SKIP^", VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY); 
			else
				sprintf( new_counter[2].word, "^       %c: CONTINUE^", VG_P1_KICK1_KEY_DSY, VG_P1_KICK2_KEY_DSY); 
		}
		else
		{
			if(VG_STORY_SETUP != VG_STORY_SCENE_LAST)
				sprintf( new_counter[2].word, "^     ÷: NEXT ø: SKIP^");
			else
				sprintf( new_counter[2].word, "^       ÷: CONTINUE^");
		}

		if(title_sequence == 2)  
		{ 
			 
			if((int)TimerGetTime() > VG_button_pause_timer)
			{
				if(VG_1_HUD_GO == true)
				{
					VG_button_pause_timer = (int)TimerGetTime() + 150;

					VG_reset_input(); 
					vg_scene_sequence++;

					if(VG_1_CHARACTER == VG_GYEONG)
						VG_Init_Story_Gyeong(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
					if(VG_1_CHARACTER == VG_MINSO)
						VG_Init_Story_Minso(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
					if(VG_1_CHARACTER == VG_HYUK)
						VG_Init_Story_Hyuk(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
					if(VG_1_CHARACTER == VG_JAE)
						VG_Init_Story_Jae(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);

					if(VG_1_CHARACTER == VG_REESE)
						VG_Init_Story_Reese(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
					if(VG_1_CHARACTER == VG_SIU)
						VG_Init_Story_Siu(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
					if(VG_1_CHARACTER == VG_YOHAN)
						VG_Init_Story_Yohan(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
					if(VG_1_CHARACTER == VG_GUN)
						VG_Init_Story_Gun(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);

					if(VG_1_CHARACTER == VG_SHO)
						VG_Init_Story_Sho(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
					if(VG_1_CHARACTER == VG_TIA)
						VG_Init_Story_Tia(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
					if(VG_1_CHARACTER == VG_SAIZO)
						VG_Init_Story_Saizo(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
					if(VG_1_CHARACTER == VG_SANG)
						VG_Init_Story_Sang(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);
					if(VG_1_CHARACTER == VG_KENNEDY)
						VG_Init_Story_Kennedy(vg_scene_sequence, VG_STORY_SETUP, VG_CURRENT_STORY_SCENE);

				}
			}
			else
				VG_reset_input();
			 
		} // title_sequence == 2

		if(title_sequence == 3)   
		{

			// Go to next scene...
			VG_reset_input();

			if(VG_STORY_SETUP == VG_STORY_SCENE_SETUP)
			{
				VG_IS_VERSUS_SCREEN = true;
				vg_next_episode = 6;    
				vg_next_scene    = 0;    
				next_scene = true; 
			}
			if(VG_STORY_SETUP == VG_STORY_SCENE_WON) 
			{
				// Important this makes it go to the next fight/scene...
				VG_CURRENT_STORY_SCENE++;
				 
				VG_IS_VERSUS_SCREEN = false;
				vg_next_episode = 6;    
				vg_next_scene    = 1;    
				next_scene = true;  
			}

			// Played the ending...
			if(VG_Scene_char == 102)
			{  
				if(VG_GAME_MODE == VG_ARCADE_MODE) 
				if(VG_ARCADE_TYPE == VG_ARCADE_STANDARD && VG_DUELLISTS_UNLOCKED == 0)
					VG_DUELLISTS_UNLOCKED = 1;

				if(VG_GAME_MODE == VG_ARCADE_MODE) 
				if(VG_ARCADE_TYPE == VG_ARCADE_DUELLING && VG_TURBO_UNLOCKED == 0)
					VG_TURBO_UNLOCKED = 1;

				if(VG_GAME_MODE == VG_ARCADE_MODE) 
				if(VG_ARCADE_TYPE == VG_ARCADE_TURBO && VG_MASTER_UNLOCKED == 0)
					VG_MASTER_UNLOCKED = 1;

				vg_next_episode = 6;    
				vg_next_scene    = 3;    
				next_scene = true; 
			}

			if(VG_GAME_MODE == VG_ARCADE_MODE)
			{
				vg_next_episode = 0;   
				vg_next_scene    = 11; // Score sheet
				
				if(VG_SURVIVAL == true)
				{
					vg_next_episode = 6;   
					vg_next_scene    = 1; // Map screen...

					VG_SURVIVAL_ROUND++;

					vg_defeat_count = 0;
				
					VG_map_last_point = (VG_1_CHARACTER+14);
					VG_map_next_point = 0;

					for(int i =0;i<15;i++) 
						VG_DEFEATED_GUYS[i] = -1;

					VG_BATTLE_ROUND = 1;
					VG_ROUND = 1;

				}

				next_scene = true; 
			}

			title_sequence++;

		} // title_sequence == 3

   }     


	// ******************************************************************************//
	//                            6-3  (LAST SCENE)                                  //
	// ******************************************************************************//

   // Title Screen Stuff... 
   if(!mode) 
   if(next_scene == false) 
   if(episode == 6 && scene == 3)        
   {        
		 
		if(title_sequence == 0)  
		{ 
		//	VG_CS_SONG = VG_story_song[VG_CURRENT_STORY_SCENE];
		//	VG_CS_SONG = CS_NONE;


			sprite[1].mov_x = sprite[1].x;
			sprite[2].mov_x = sprite[2].x; 

			sprite[1].x = sprite[0].x + sprite[0].width;
			sprite[2].x = sprite[0].x - sprite[2].width;

			vg_scene_sequence = 0;

			VG_Scene_char=0;
			VG_Scene_emotion=0;

			#if IS_FULL_STEAM == 1 
			if(STEAM_ACTIVE == true)
			if(VG_STEAM_DEMO == 0)
			if(VG_GAME_MODE == VG_STORY_MODE)
			{
				if(VG_1_CHARACTER == VG_GYEONG)
					platform_unlock_achievement(0); // Beat Gyeong story mode...
				if(VG_1_CHARACTER == VG_SIU)
					platform_unlock_achievement(1); // Beat Siu story mode..
				if(VG_1_CHARACTER == VG_MINSO)
					platform_unlock_achievement(2); // Beat Minso story mode..
				if(VG_1_CHARACTER == VG_REESE)
					platform_unlock_achievement(3); // Beat Reese story mode..

				if(VG_1_CHARACTER == VG_YOHAN)
					platform_unlock_achievement(4); // Beat Yohan story mode..
				if(VG_1_CHARACTER == VG_JAE)
					platform_unlock_achievement(5); // Beat Jae story mode..
				if(VG_1_CHARACTER == VG_GUN)
					platform_unlock_achievement(6); // Beat Gun story mode..
				if(VG_1_CHARACTER == VG_HYUK)
					platform_unlock_achievement(7); // Beat Hyuk story mode..
			}
			#endif

			if(VG_1_CHARACTER == VG_GYEONG)
				VG_Init_Story_Gyeong(vg_scene_sequence, VG_STORY_SCENE_LAST, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_MINSO)
				VG_Init_Story_Minso(vg_scene_sequence, VG_STORY_SCENE_LAST, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_HYUK)
				VG_Init_Story_Hyuk(vg_scene_sequence, VG_STORY_SCENE_LAST, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_JAE)
				VG_Init_Story_Jae(vg_scene_sequence, VG_STORY_SCENE_LAST, VG_CURRENT_STORY_SCENE);

			if(VG_1_CHARACTER == VG_REESE)
				VG_Init_Story_Reese(vg_scene_sequence, VG_STORY_SCENE_LAST, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_SIU)
				VG_Init_Story_Siu(vg_scene_sequence, VG_STORY_SCENE_LAST, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_YOHAN)
				VG_Init_Story_Yohan(vg_scene_sequence, VG_STORY_SCENE_LAST, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_GUN)
				VG_Init_Story_Gun(vg_scene_sequence, VG_STORY_SCENE_LAST, VG_CURRENT_STORY_SCENE);

			if(VG_1_CHARACTER == VG_SHO)
				VG_Init_Story_Sho(vg_scene_sequence, VG_STORY_SCENE_LAST, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_TIA)
				VG_Init_Story_Tia(vg_scene_sequence, VG_STORY_SCENE_LAST, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_SAIZO)
				VG_Init_Story_Saizo(vg_scene_sequence, VG_STORY_SCENE_LAST, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_SANG)
				VG_Init_Story_Sang(vg_scene_sequence, VG_STORY_SCENE_LAST, VG_CURRENT_STORY_SCENE);
			if(VG_1_CHARACTER == VG_KENNEDY)
				VG_Init_Story_Kennedy(vg_scene_sequence, VG_STORY_SCENE_LAST, VG_CURRENT_STORY_SCENE);			

			new_counter[1].alpha = 1.0f;                 
			new_counter[1].id = 0;       
			new_counter[1].x = -0.32f;         
			new_counter[1].y = sprite[2].y - 0.04f;
			new_counter[1].type = 2;  // Large Font...  
			new_counter[1].right = false; 

			sprintf( new_counter[2].word, "^     %c: NEXT %c: BACK^", VG_P1_PUNCH1_KEY_DSY, VG_P1_PUNCH2_KEY_DSY); 
			  
			new_counter[2].alpha = 0.0f;                     
			new_counter[2].id = 3;        
				  
			new_counter[2].type = 1;  // Small Font...
			new_counter[2].right = false;

			new_counter[2].x = -0.28f;                     
			new_counter[2].y = -0.33f;          

			new_counter[2].w = new_counter[2].x - 0.026f;   
			new_counter[2].z = new_counter[2].y - 0.015f; 

			new_counter[2].box_width = strlen(new_counter[2].word)   *  0.026f;
			new_counter[2].box_height = new_counter[2].height - 0.015f;	

			sprite[2].alpha = 0.0f;  

			 title_sequence++;   
		}    
		 
		if(title_sequence == 1)         
		{ 
			temp_speed = (0.00125f/VG_slowmof)*(float)f_rate;
			     
			sprite[1].x -= temp_speed;   
			sprite[2].x += temp_speed;     
			     
			if(sprite[1].x <= sprite[1].mov_x)   
			{      
				sprite[1].x = sprite[1].mov_x;
				sprite[2].x = sprite[2].mov_x;   

				title_timer = (int)TimerGetTime() + 6000;
				title_sequence++;
			}
			 
		}  

		Set_Sprite(3, VG_Scene_char, LOOP, ANIM_SPRITE, ANIM_NOT_WALKING); // Background left or right...

		// Animate-setup sprites...

		sprite[1].alpha = 0.0f;
		sprite[2].alpha = 0.0f;

		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[2].word, "^     %c: NEXT %c: BACK^", VG_P1_PUNCH1_KEY_DSY, VG_P1_PUNCH2_KEY_DSY);
		else
			sprintf( new_counter[2].word, "^     ÷: NEXT ø: BACK^");

		if(title_sequence == 2)  
		if((int)TimerGetTime() > title_timer)
		{

			vg_next_episode = 0;    
			vg_next_scene    = 1;   

			next_scene = true; 

			title_sequence++;

		} // title_sequence == 3

   }     






}