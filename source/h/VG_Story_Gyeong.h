#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64  
#define WIN32_LEAN_AND_MEAN    
#include <windows.h>
#endif     

#define VG_EMOTION_NONE        0 
#define VG_EMOTION_ANGRY       1
#define VG_EMOTION_SAD         2
#define VG_EMOTION_DERP        3
#define VG_EMOTION_MOTIVATED   4
#define VG_EMOTION_HAPPY       5
#define VG_EMOTION_PAIN        6
#define VG_EMOTION_PAIN_DERP   7

extern void VG_WrapWord(char *word, unsigned int line_length, int type);

void VG_Help_Story_Gyeong(int scene, int index)
{
	int rnd = 0;
	char punch;
	char punch2;
	char kick;
	char kick2;
	char up;
	char down;
	char left;
	char right;
	char downleft;
	char downright;
	char throw_key;

	down = '§';
	up = '¦';

	downleft = '¯';
	downright = '²';

	if(VG_P1_USING == VG_KEYBOARD)
	{
		up = VG_P1_UP_KEY_DSY;
		down = VG_P1_DOWN_KEY_DSY;
	//	left = VG_P1_LEFT_KEY_DSY;
	//	right = VG_P1_RIGHT_KEY_DSY;
		left = '¢';
		right = '¤';
		punch  = VG_P1_PUNCH1_KEY_DSY;
		punch2 = VG_P1_PUNCH2_KEY_DSY;
		kick   = VG_P1_KICK1_KEY_DSY;
		kick2  = VG_P1_KICK2_KEY_DSY;
		throw_key = VG_P1_THROW_KEY_DSY;
	}
	if(VG_P1_USING == VG_CONTROLLER)  
	{
		left = '¢';
		right = '¤';
		punch  = 'ù'; // ÷ - A
		punch2 = 'ú'; // ø - B
		kick   = '÷'; // ù - X 
		kick2  = 'ø'; // ú - Y
		throw_key = '»';
	} 
	 
	 
	// First fight against Toyun at alleyway...
	if(scene == 0)  
	{
		sprintf( new_counter[index].word, "WIN ONE ROUND USING^YOUR BASIC PUNCHES AND^KICKS TO WIN!^^PUNCHES^%c or %c^^KICKS^%c or %c", punch, punch2, kick, kick2); 
	}
	if(scene == 1) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE DOJO MASTER^USING YOUR PISTOL. ONLY^THE PISTOL WILL DAMAGE HIM!^^PISTOL^%c,%c + %c^^PISTOL LOW^%c,%c + %c", left, right, punch2, left, right, punch);
		else
			sprintf( new_counter[index].word, "DEFEAT THE DOJO MASTER^USING YOUR PISTOL. ONLY^THE PISTOL WILL DAMAGE HIM!^^PISTOL^%c,%c,%c + %c^^PISTOL LOW^%c,%c,%c + %c", down, downleft, left, punch2, down, downleft, left, punch);
	}
	if(scene == 2) 
	{
		sprintf( new_counter[index].word, "DEFEAT THE CRIMINAL USING^YOUR TORPEDO PUNCH!. ONLY^THE TORPEDO PUNCH WILL^DAMAGE HIM!^^TORPEDO PUNCH^%c,%c + %c^^TORPEDO PUNCH^%c,%c + %c", right, right, kick, right, right, kick2);
	}
	if(scene == 3)  
	{
		sprintf( new_counter[index].word, "DEFEAT THE TRAFFIC COP^USING YOUR COMBO ATTACK.^ONLY THE COMBO ATTACK WILL^DAMAGE HER!^^COMBO^%c,%c,%c", punch, punch, punch2);
	}
	if(scene == 4) 
	{
		sprintf( new_counter[index].word, "YOU MUST SURVIVE UNTIL THE^TIMER RUNS OUT!^BE CAREFUL AS YOUR ATTACKS^WILL HAVE NO EFFECT!"); 
	}
	if(scene == 5) 
	{
		sprintf( new_counter[index].word, "WIN ONE ROUND USING^YOUR HANDCUFFS AND THROWS.^YOU CAN ONLY DAMAGE HIM^WHEN HE$S HANDCUFFED^OR WITH THROWS^^HANDCUFF - THROW^PRESS %c", throw_key);
	}
	if(scene == 6) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "YOU MUST DEFEAT TOYUN^USE WHATEVER MEANS^NECCESSARY!^^UPPERCUT^%c,%c + %c^^TORPEDO^%c,%c + %c", left, left, kick2, right, right, kick);
		else
			sprintf( new_counter[index].word, "YOU MUST DEFEAT TOYUN^USE WHATEVER MEANS^NECCESSARY!^^UPPERCUT^%c,%c,%c + %c^^TORPEDO^%c,%c + %c", down, downleft, left, kick2, right, right, kick);
	}
	if(scene == 7)  
	{
		sprintf( new_counter[index].word, "YOU MUST ARREST THE KILLER!^DEFEAT HIM ON THE LAST^ROUND WHEN HE$S HANDCUFFED^HE MUST BE HANDCUFFED^TO WIN!^^HANDCUFF - THROW^PRESS %c", throw_key);
	}
	if(scene == 8) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "YOU MUST DEFEAT MIA^USE WHATEVER MEANS^NECCESSARY!^^PISTOL^%c,%c + %c^^TORPEDO^%c,%c + %c", left, right, punch2, right, right, kick);
		else
			sprintf( new_counter[index].word, "YOU MUST DEFEAT MIA^USE WHATEVER MEANS^NECCESSARY!^^PISTOL^%c,%c,%c + %c^^TORPEDO^%c,%c + %c", down, downleft, left, punch2, right, right, kick);
	}
	if(scene == 9)  
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT SANG WITH LOW^HEALTH.^^PISTOL^%c,%c + %c^^TORPEDO^%c,%c + %c", left, right, punch2, right, right, kick);
		else
			sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT SANG WITH LOW^HEALTH.^^PISTOL^%c,%c,%c + %c^^TORPEDO^%c,%c + %c", down, downleft, left, punch2, right, right, kick);
	}

}

void VG_Init_Story_Gyeong(int index, int condition, int scene)
{

	VG_Scene_char = 0;

	// First fight against MIA at training dojo...
	if(scene == 0)
	{
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)   
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHAT ARE YOU DOING HERE GYEONG? "); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "THOUGHT YOU COULD USE A HAND OLD BUDDY!"); 
			}
			if(index == 2)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE OFF THE CASE. YOU SHOULDN$T BE HERE"); 
			} 
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "CAN$T I SEE AN OLD FRIEND?"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "WE$RE ALL SORRY ABOUT WHAT HAPPENED TO CHIA"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "DON$T MAKE THIS ANY WORSE GYEONG"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "IT HAS TO GET WORSE BEFORE IT GETS BETTER"); 
			}
			if(index == 7)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "DAMMIT GYEONG...."); 
			}
			if(index == 8)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_WON)
		{

			if(index == 0)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "Y-YOU$RE CRAZY..."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "WHAT DO WE HAVE HERE?"); 
			}
			if(index == 2)
			{   
				VG_Scene_char = 3;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "DON$T MIND IF I BORROW THIS DO YOU. OLD PAL "); 
				VG_handcuffs_sfx = true;  
			} 
			if(index == 3) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "I$M GOING TO HAVE TO REPORT THIS GYEONG"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "EVERY COP IN THE CITY WILL BE AFTER YOU"); 
			}
			if(index == 5)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "THAT$S WHAT I THOUGHT"); 
			} 
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "SEND MY LOVE TO THE CHIEF"); 
			} 
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}
			 
		} 
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "I$M TAKING YOU IN GYEONG, SORRY");
		}

	} 

	// Second fight against Trainer at dojo...
	if(scene == 1)
	{
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "THE DOJO$S CLOSING NOW DETECTIVE"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$M HERE TO ASK YOU SOME QUESTIONS.. "); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "WHAT PART OF CLOSED DIDN$T YOU UNDERSTAND?"); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "CUT THE CRAP OLD MAN I KNOW WHO YOU ARE!"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I DON$T KNOW WHAT YOU$RE TALKING ABOUT"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I HEARD YOU WERE TOUGH LET$S FIND OUT!"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_WON)
		{
			if(index == 0)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "W-WHAT DO YOU WANT TO KNOW..."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I WANT THE PUNK BEHIND THE MALL ATTACKS "); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "AND HOW SHOULD I KNOW THAT!"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I$M A DETECTIVE I KNOW ALL ABOUT YOU.."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "Y-YOU$LL NEED HYUK THEN HE KNOWS YOUR GUY.."); 
			}
			if(index == 5) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "HE$S DOING A BANK JOB THAT$S ALL I CAN SAY"); 
			}
			if(index == 6) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "DON$T SUPPOSE YOU HAVE ANY SOJU ON YOU?"); 
			}
			if(index == 7) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "N-NO I DON$T..."); 
			}
			if(index == 8)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "BEAT IT PUNK!");
		}

	}
	
	// Third fight against Hyuk on the highway...
	if(scene == 2)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "SO YOU MUST BE HYUK THEN PUNK?"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HUH? I$M ALITTLE BUSY HERE COP, EXCUSE ME!"); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "SORRY TO INTERRUPT YOUR SHOOT-OUT.."); 
			}
			if(index == 3)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU GOT A DEATHWISH OR SOMETHING BUDDY?"); 
			}
			if(index == 4) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I WAS TOLD YOU KNOW THE MAD BOMBER.."); 
			}
			if(index == 5)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "SO WHAT IF I DO. LIKE I$D TELL YOU!"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "MAYBE I CAN PERSUADE YOU THEN..."); 
			}
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_WON)
		{
			if(index == 0)   
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "A-ALRIGHT I-I$M PERSUADED"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHO$S THE MAD BOMBER?"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "THEY CALL HIM YOHAN..HE$S REAL TROUBLE"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "HE$S PART OF SOME CULT LEAD BY SUNG-KI."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHERE?"); 
			} 
			if(index == 5)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "T-THE OLD PLAZA. YOU DIDN$T HEAR IT FROM ME"); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I$LL SEND HIM YOUR REGARDS..."); 
			} 
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "WHAT A LOUSY DRUNK... GET LOST COP!");
		}

	}
	
	// Fourth fight against Minso at traffic jam...
	if(scene == 3)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{ 
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "WHAT A PILE-UP! WHO$S RUNNING THIS SHOW?"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HEY YOU CAN$T PARK THERE MISTER!"); 
			}
			if(index == 2)  
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "B-BUT I-I$M NOT PARKED!"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "NICE TRY BUDDY! YOU$RE GOING TO PAY THE TICKET"); 
			}
			if(index == 4)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I$M A DETECTIVE LADY. NOW MOVE THESE CARS!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THEN YOU SHOULD BE SETTING AN EXAMPLE!"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "(I DON$T HAVE TIME FOR THIS!)"); 
			}
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_WON)
		{
			if(index == 0) 
			{ 
				VG_Scene_char = 10; 
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "HEY! YOU GET BACK HERE MISTER!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 10;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "AND PAY YOUR PARKING TICKET!"); 
			} 
			if(index == 2)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "TIME TO PAY YOUR TICKET MISTER!");
		}

	}

	// Fifth fight against Yohan at the apartment...
	if(scene == 4)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "M-MASTER? YOU$RE HERE!"); 
			}
			if(index == 1) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "...WHO ARE YOU?..."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "SURPRISE!"); 
			}
			if(index == 3)  
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "CHIA SENT ME...I$M HERE TO KILL YOU"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "HAHAHA..."); 
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "DID I MISS THE JOKE?"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$LL NEVER LEAVE HERE ALIVE..."); 
			}
			if(index == 7)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$M COMING CHIA, WAIT FOR ME JUST ALITTLE LONGER"); 
			}
			if(index == 8)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_WON)
		{
			if(index == 0)
			{ 
				VG_Scene_char = 11; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "DAMMIT! HE GOT AWAY..."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 11;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "THERE MUST BE SOME CLUES IN THIS DUMP.."); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 3;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "HERE!...A NIGHTCLUB? ANOTHER BOMB ATTACK!"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 11;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I WON$T FAIL NEXT TIME CHIA..."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "TIME FOR YOU TO DIE NOW...");
		}

	}


	// Sixth fight against Dae-su at the subway...
	if(scene == 5)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "TIME FOR ALITTLE SHORTCUT!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "HOLD IT RIGHT THERE!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "WHY ME? I ONLY WANT TO KILL YOHAN"); 
			}
			if(index == 3)   
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "DROP YOUR WEAPON SON!"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$VE GOT THE WRONG MAN, OLD TIMER!"); 
			}
			if(index == 5)   
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "JUST COME QUIETLY! WE DON$T WANT TROUBLE"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_WON)
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "NOW LOOK WHAT YOU MADE ME DO!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "Y-YOU LITTLE PUNK..."); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "EVERY COP IN THE CITY IS AFTER YOU!"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "TAKING THE SUBWAY WASN$T SUCH A HOT IDEA."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$LL CUT THROUGH THE PARK..."); 
			}
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOUR UNDER ARREST SON!");
		}

	}


	// Seventh fight against Toyun at the park...
	if(scene == 6) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "JUST A NICE STROLL IN THE PARK!"); 
			}
			if(index == 1) 
			{    
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "GYEONG!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "GOD DAMMIT!"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU$RE TOTALLY SURROUNDED, GIVE UP!"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "YOU JUST WON$T QUIT WILL YOU!"); 
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$M DOING THIS FOR YOUR OWN SAKE GYEONG"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_WON)
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "I FOUND CHIA$S KILLER TOYUN! I FOUND HIM"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU HAVE TO TRUST ME ON THIS ONE.."); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "..."); 
			} 
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "A-ALRIGHT I$LL BUY YOU SOME TIME..."); 
			} 
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "JUST DON$T MESS THIS UP GYEONG"); 
			} 
			if(index == 5)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU KNOW ME TOYUN! ..THANKS OLD FRIEND.."); 
			} 
			if(index == 6)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "I$M SORRY IT CAME TO THIS OLD FRIEND");
		}

	}

	// Eighth fight against Yohan at the nightclub...
	if(scene == 7) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "D-DID I MAKE IT IN TIME?"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "THERE YOU ARE! JUST THE MAN...HAHA"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "THERE$S NO ESCAPE THIS TIME PUNK"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "YOU$LL BE THE SUSPECT WHEN THIS PLACE BLOWS!"); 
			}
			if(index == 4) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "IT ENDS HERE!..CHIA WAIT FOR ME.."); 
			}
  		    if(index == 5)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "HAHAHA..."); 
			}
			if(index == 6)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_WON)
		{
			if(index == 0)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "P-PLEASE DON$T KILL ME HE MADE ME DO IT"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "M-MR SANG...HE TOLD ME TO DO IT"); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THE GUY RUNNING FOR PRESIDENT?"); 
			} 
			if(index == 3) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "(I DON$T THINK HE$S LYING)"); 
			} 
			if(index == 4)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "I NEVER WANTED ANY OF THIS..."); 
			} 
			if(index == 5) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I$LL LET TOYUN DEAL WITH YOU PUNK!"); 
			} 
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "TIME TO CAST MY VOTE..."); 
			} 
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU$LL NEVER ARREST ME!");
		}

	}


	// Ninth fight against Mia at the courtroom...
	if(scene == 8) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "SANG! YOU COWARD! SHOW YOURSELF"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I DON$T THINK YOU HAVE AN APPOINTMENT"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "STAY OUT OF THIS LADY..."); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THERE$S A WARRANT OUT FOR YOUR ARREST"); 
			}
			if(index == 4)  
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "THE ONLY ARREST IS GOING TO BE SANGS"); 
			} 
			if(index == 5)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I CAN$T LET YOU DO THAT..."); 
			}
			if(index == 6) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHY ARE YOU PROTECTING THAT MONSTER?"); 
			}
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_WON)
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "OUT OF MY WAY LADY! YOU$VE HAD ENOUGH"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "KYUNG! PLEASE BE SAFE..."); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "IT$S JUST YOU AND ME NOW SANG!"); 
			}
			if(index == 3) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "CHIA WON$T REST UNTIL I DEFEAT YOU.."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU$RE UNDER ARREST!");
		}

	}

	// Tenth fight against Sang at the courtroom...
	if(scene == 9) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)  
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "SO THE SNAKE SHOWS ITSELF!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU$LL GO TO JAIL FOR YEARS FOR THIS!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "IS THAT SO? TOO BAD WE HAVE A WITNESS"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY; 
				sprintf( new_counter[1].word, "LINKING YOU TO THE MALL ATTACKS..IT$S OVER"); 
			}
			if(index == 4)  
			{    
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "YOU$RE LYING... YOU$RE JUST A DRUNK"); 
			}
			if(index == 5)   
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "WE HAVE YOHAN IN CUSTODY..."); 
			}
			if(index == 6)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I WARNED SUNG-KI ABOUT THAT LITTLE PUNK"); 
			}
			if(index == 7) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "IF I$M GOING DOWN YOU$RE COMING WITH ME!"); 
			}
			if(index == 8)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		} 
		if(condition == VG_STORY_SCENE_WON)
		{
			if(index == 0)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "Y-YEARS OF P-PLANNING R-RUINED..."); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU CAN REST NOW CHIA I LOVE YOU..."); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "CHIA? WAS YOUR GIRL? THAT$S TOO BAD.."); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHAT WOULD YOU KNOW ABOUT LOSS YOU MONSTER!"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "I LOST MY DAUGHTER.. IN A MUGGING.."); 
			}
			if(index == 5)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "THE POLICE NEVER FOUND THE KILLER..I VOWED.."); 
			}
			if(index == 6) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "TO CHANGE THE SYSTEM.. SOMEWHERE I FAILED.."); 
			}
			if(index == 7)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WE CAN ALL MAKE AMENDS, EVEN YOU SANG"); 
			}
			if(index == 8) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "I$M TOO OLD TO CHANGE, BUT YOU CAN.."); 
			}
			if(index == 9)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "..."); 
			}
			if(index == 10)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "ARREST THIS MAN!");
		}

	}

	// Final ending...
	if(scene == 10) 
	{  
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "WE TOOK IN SANG! HE$S CRYING LIKE A BABY!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I GUESS I OWE YOU ONE TOYUN..."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "YOU SAVED THE CITY!"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE; 
				sprintf( new_counter[1].word, "I CAN$T BELIEVE IT$S FINALLY OVER.."); 
			}
			if(index == 4)  
			{    
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "COMON I$LL BUY YOU A DRINK!"); 
			}
			if(index == 5)   
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I QUIT..I THINK I$LL PAY CHIA A VISIT"); 
			}
			if(index == 6)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I UNDERSTAND GYEONG.. WE$RE HERE FOR YOU"); 
			}
			if(index == 7)   
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I KNOW THAT BUDDY AND THANKS..."); 
			}
			if(index == 8)   
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "(THE END) THANKS FOR PLAYING!");
			}
			if(index == 9) 
			{
				VG_Scene_char = 102; // Cause ending quit...
			}

		}
		if(condition == VG_STORY_SCENE_LAST) 
		{
			VG_Scene_char = 1;
			VG_Scene_emotion = VG_EMOTION_HAPPY;
			sprintf( new_counter[1].word, "THROUGH THE DARKNESS WE MUST STRUGGLE ON"); 
		}
	} 

	// Arcade ending...
	if(scene == 101) 
	{  
		if(VG_SURVIVAL == false)
		if(condition == VG_STORY_SCENE_LAST)  
		{
			// Required so scoreboards go straight to title screen...
			VG_BEAT_THE_GAME = true;

			if(index == 0) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY; 

				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "WITH CHIA$S DEATH AVENGED..."); 
				else
					sprintf( new_counter[1].word, "WITH THE CHIEFS MURDER RESOLVED..."); 
			}
			if(index == 1) 
			{  
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_HAPPY;

				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "GYEONG CAN FINALLY REST.. FOR NOW!"); 
				else
					sprintf( new_counter[1].word, "TOYUN CAN TAKE THAT VACATION!"); 
			}
			if(index == 2)   
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "(THE END) THANKS FOR PLAYING!"); 
			}
			if(index == 3) 
				VG_Scene_char = 102; // Cause ending quit...

			if(VG_GAME_MODE == VG_ARCADE_MODE)
			if(VG_ARCADE_TYPE == VG_ARCADE_STANDARD && VG_DUELLISTS_UNLOCKED == 0)
			{
				if(index == 3)   
				{  
					VG_Scene_char = 8; // Sets the bg frame...
					VG_Scene_emotion = VG_EMOTION_HAPPY;
					sprintf( new_counter[1].word, "(DUELLING MODE! UNLOCKED!)"); 
					vg_pause_sfx = true;  
				}
				if(index == 4) 
				{
					if(VG_CHARACTER_LOCKS[VG_GYEONG] == 1)
						VG_Scene_char = 102; // Cause ending quit...
					else
					{  
						VG_CHARACTER_LOCKS[VG_GYEONG] = 1;
						VG_Scene_char = 9; // Sets the bg frame...
						VG_Scene_emotion = VG_EMOTION_HAPPY;
						sprintf( new_counter[1].word, "(TOYUN IS NOW PLAYABLE!)"); 
						vg_pause_sfx = true;  
					}
				}
				if(index == 5) 
					VG_Scene_char = 102; // Cause ending quit...
			}
			if(VG_GAME_MODE == VG_ARCADE_MODE) 
			if(VG_ARCADE_TYPE == VG_ARCADE_STANDARD && VG_DUELLISTS_UNLOCKED == 1)
			{
				if(index == 3)   
				{  
					if(VG_CHARACTER_LOCKS[VG_GYEONG] == 1)
						VG_Scene_char = 102; // Cause ending quit...
					else
					{  
						VG_CHARACTER_LOCKS[VG_GYEONG] = 1;
						VG_Scene_char = 9; // Sets the bg frame...
						VG_Scene_emotion = VG_EMOTION_HAPPY;
						sprintf( new_counter[1].word, "(TOYUN IS NOW PLAYABLE!)"); 
						vg_pause_sfx = true;  
					}
				}
				if(index == 4) 
					VG_Scene_char = 102; // Cause ending quit...

			}



			if(VG_GAME_MODE == VG_ARCADE_MODE)
			if(VG_ARCADE_TYPE == VG_ARCADE_DUELLING && VG_TURBO_UNLOCKED == 0)
			{
				if(index == 3)   
				{  
					VG_Scene_char = 8; // Sets the bg frame...
					VG_Scene_emotion = VG_EMOTION_HAPPY;
					sprintf( new_counter[1].word, "(TURBO MODE! UNLOCKED!)"); 
					vg_pause_sfx = true;  
				}
				if(index == 4) 
					VG_Scene_char = 102; // Cause ending quit...
			}
			if(VG_GAME_MODE == VG_ARCADE_MODE)
			if(VG_ARCADE_TYPE == VG_ARCADE_TURBO && VG_MASTER_UNLOCKED == 0)
			{
				if(index == 3)   
				{  
					VG_Scene_char = 8; // Sets the bg frame...
					VG_Scene_emotion = VG_EMOTION_HAPPY;
					sprintf( new_counter[1].word, "(MASTER MODE! UNLOCKED!)"); 
					vg_pause_sfx = true;  
				}
				if(index == 4) 
					VG_Scene_char = 102; // Cause ending quit...
			}



		}
		if(VG_SURVIVAL == true)
		if(condition == VG_STORY_SCENE_LAST) 
		{
			if(index == 0) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "ROUND CLEARED!");
			}
			if(index == 1) 
			{
				VG_Scene_char = 102; // Cause ending quit...
			}
		}
	}

	if(condition == VG_STORY_SCENE_LOST) 
	{
		if(VG_ROUND_CONDITIONS == CONDITION_MUST_ARREST)
			sprintf( new_counter[1].word, "(HMMM! I NEED TO ARREST THEM!)");
		if(VG_ROUND_CONDITIONS == CONDITION_MUST_WASTE)
			sprintf( new_counter[1].word, "(HMMM! I NEED TO WASTE THEM!)");
		if(VG_ROUND_CONDITIONS == CONDITION_TIMED || VG_ROUND_CONDITIONS == CONDITION_TIMED_BASIC)
			sprintf( new_counter[1].word, "(I W-WASN$T FAST ENOUGH!)");
	}

	if(VG_Scene_char != 101 && VG_Scene_char != 102)
		VG_WrapWord(new_counter[1].word, 25, -1);

}

