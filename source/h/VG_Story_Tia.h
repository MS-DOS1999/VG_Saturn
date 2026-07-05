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

void VG_Help_Story_Tia(int scene, int index)
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
	char upleft;
	char upright;
	char throw_key;

	down = '§';
	up = '¦';

	downleft = '¯';
	downright = '²';

	upleft = '³';
	upright = '¹';

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
	 
	// First fight against MIA at training dojo...
	if(scene == 0)  
	{
		sprintf( new_counter[index].word, "WIN ONE ROUND USING^YOUR BASIC PUNCHES AND^KICKS TO WIN!^^PUNCHES^%c or %c^^KICKS^%c or %c", punch, punch2, kick, kick2);
	}
	if(scene == 1) 
	{
		sprintf( new_counter[index].word, "DEFEAT THE SUSPICIOUS MAN^USING YOUR COMBO ATTACK.^ONLY THE COMBO ATTACK WILL^DAMAGE HIM!^^COMBO^%c,%c,%c", punch, punch, kick);
	}
	if(scene == 2) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE FOREIGNER USING^THE TAZER. ONLY THE TAZER^WILL DAMAGE HIM!^^TAZER HIGH^%c,%c + %c^^TAZER LOW^%c,%c + %c", right, right, punch2, right, right, punch);
		else
			sprintf( new_counter[index].word, "DEFEAT THE FOREIGNER USING^THE TAZER. ONLY THE TAZER^WILL DAMAGE HIM!^^TAZER HIGH^%c,%c,%c + %c^^TAZER LOW^%c,%c,%c + %c", down, downright, right, punch2, down, downright, right, punch);
	}
	if(scene == 3) 
	{
		sprintf( new_counter[index].word, "WIN ONE ROUND USING^YOUR HANDCUFFS AND THROWS.^YOU CAN ONLY DAMAGE HIM^WHEN HE$S HANDCUFFED^OR WITH THROWS^^HANDCUFF - THROW^PRESS %c", throw_key);
	}
	if(scene == 4) 
	{
		sprintf( new_counter[index].word, "USE YOUR POLICE DOG^CHARLIE TO HELP DEFEAT^THE SUSPECT!^^CHARLIE^HOLD %c", punch);
	}
	if(scene == 5) 
	{
		sprintf( new_counter[index].word, "YOU MUST ARREST THE SUSPECT!^DEFEAT HIM ON THE LAST^ROUND WHEN HE$S HANDCUFFED^HE MUST BE HANDCUFFED^TO WIN!^^HANDCUFF - THROW^PRESS %c", throw_key);
	}
	if(scene == 6) 
	{
		sprintf( new_counter[index].word, "YOU MUST SURVIVE UNTIL THE^TIMER RUNS OUT!^BE CAREFUL AS YOUR ATTACKS^WILL HAVE NO EFFECT!"); 
	}
	if(scene == 7)  
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "STOP THE PRISONER QUICK^BEFORE TIME RUNS OUT!^IF THE TIMER RUNS OUT^YOU$LL LOSE THE FIGHT!^^PANTY SHOT^%c + HOLD %c^^CHARLIE^HOLD %c^", upright, kick2, punch);
		else
			sprintf( new_counter[index].word, "STOP THE PRISONER QUICK^BEFORE TIME RUNS OUT!^IF THE TIMER RUNS OUT^YOU$LL LOSE THE FIGHT!^^PANTY SHOT^%c + HOLD %c^^CHARLIE^HOLD %c^", upright, kick2, punch);
	}
	if(scene == 8) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT MIA WITH LOW^HEALTH.^^TAZER HIGH^%c,%c + %c^^CHARLIE^HOLD %c^", right, right, punch2, punch);
		else
			sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT MIA WITH LOW^HEALTH.^^TAZER HIGH^%c,%c,%c + %c^^CHARLIE^HOLD %c^", down, downright, right, punch2, punch);
	}
	if(scene == 9) 
	{
		sprintf( new_counter[index].word, "YOU MUST ARREST THE SUSPECT!^DEFEAT HIM ON THE LAST^ROUND WHEN HE$S HANDCUFFED^HE MUST BE HANDCUFFED^TO WIN!^^HANDCUFF - THROW^PRESS %c", throw_key);
	}
}

void VG_Init_Story_Tia(int index, int condition, int scene)
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
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE LATE AS USUAL MINSO! REALLY... "); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I-I$M SORRY MIA... "); 
			}
			if(index == 2)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "ALRIGHT LET$S GET STARTED "); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "THIS SHOULD BE FUN HEY CHARLIE..CHARLIE?"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_WON)
		{

			if(index == 0)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "NOT TOO BAD MINSO..."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "WE DID IT! CHARLIE! "); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "YOU KNOW YOUR SHIFT STARTED TWO HOURS AGO?"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "OH NO! THE CHIEF IS GOING TO BE ANGRY"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}
			 
		} 
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "REALLY..YOU$RE NOT TRYING HARD ENOUGH MINSO!");
		}

	} 

	// Second fight against YOHAN at traffic jam...
	if(scene == 1)
	{
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "NOW HOW DID ALL THESE CARS PILE_UP!"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "CHARLIE?..OH NO! I-I$VE LOST MY POLICE DOG! "); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "(A TRAFFIC COP? HOW DID THEY FIND OUT!)"); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "HAVE YOU SEEN MY DOG MISTER?"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "GUESS I$LL HAVE TO BLOW YOU UP TOO!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHAT ARE YOU TALKING ABOUT?"); 
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
				sprintf( new_counter[1].word, "H-HOW DID YOU DEFEAT ME!?!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "ARE YOU STILL HERE?"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "..MY LORDS PLANS.. ..RUINED!.."); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "NOW WHERE DID CHARLIE RUN OFF TO?"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I KNOW HE LIKES THE PARK. THAT$S IT!"); 
			}
			if(index == 5) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "..S-SHE$S IGNORING ME.."); 
			}
			if(index == 6)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "5..4..3..2.. KA-BOOM!!");
		}

	}
	
	// Third fight against REESE at the park...
	if(scene == 2)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "CHARLIE! CHARLIE! HERE BOY!"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU SHOULDN$T BE HERE LITTLE LADY"); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "A FOREIGNER? DO YOU HAVE A PERMIT?"); 
			}
			if(index == 3)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "WELL ER...THIS AREAS RESTRICTED!"); 
			}
			if(index == 4) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "HMMM..WHAT$S THIS?"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 2;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "MY TAZER! I KNEW I LEFT IT SOMEWHERE!"); 
				VG_handcuffs_sfx = true;
			}
			if(index == 6)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "(THIS BROAD ISN$T LISTENING)"); 
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
				sprintf( new_counter[1].word, "E-ELECTRIC...P-PAIN.."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU SHOULD RESPECT OUR COUNTRIES LAWS"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "W-WE W-WILL... O-OFFICER.."); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "TIME I GOT GOING SEE YA!"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "M-MY HEAD HURTS..."); 
			}
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU DON$T KNOW WHAT YOU$RE UP AGAINST LADY");
		}

	}
	
	// Fourth fight against Hyuk at the park...
	if(scene == 3)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "A TRAFFIC JAM? ATLEAST THIS WASN$T MY FAULT!"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "STAY BACK PIGS OR I SHOOT THE GIRL!"); 
			}
			if(index == 2)  
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "ARE YOU TALKING TO ME?"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "YOU$LL MAKE A FINE HOSTAGE. COME HERE!"); 
			}
			if(index == 4)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I THINK YOU HAVE THE WRONG IDEA MISTER!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "SAY! DID A BIG DOG PASS THIS WAY?"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HUH? WHAT$S WITH THIS CHICK?"); 
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
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "NOW WHAT HAVE YOU DONE WITH CHARLIE!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "I-I DON$T KNOW ANY CHARLIE...HONEST!"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU BETTER NOT BE LYING.."); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "P-PLEASE DON$T HIT ME AGAIN..."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHAT$S THAT?..I THINK I HEARD A BARK!"); 
			}
			if(index == 5)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I$M COMING CHARLIE!"); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "I THINK I$LL STAY HERE. WHERE IT$S SAFE"); 
			}
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "I PREFER IT WHEN THEY RESIST..HAHA!");
		}

	}

	// Fifth fight against Gyeong at alleyway...
	if(scene == 4)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "(WHAT$S A TRAFFIC COP DOING HERE?)"); 
			}
			if(index == 1) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "CHARLIE! THERE YOU ARE!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 2;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WOOF! WOOF!"); 
				vg_dogattack_sfx = true;
			}
			if(index == 3)  
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HEY MISTER! WHAT ARE YOU DOING WITH MY DOG!"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "I-I NEVER TOUCHED YOUR DOG...WAIT!"); 
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE THE ONE THAT SHOULDN$T BE HERE!"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "ARE YOU DRUNK? I$M TAKING YOU IN BUDDY"); 
			}
			if(index == 7)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE STARTING TO PISS ME OFF LADY"); 
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
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "SO THERE ARE SOME GOOD COPS LEFT..."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I DON$T KNOW WHAT YOU MEAN MISTER!"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "THE COPS HAVE BEEN CORRUPTED..."); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "YOU REALLY DIDN$T KNOW?"); 
			}
			if(index == 4)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "REALLY?"); 
			}
			if(index == 5) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "THIS CITY IS TOTALLY FINISHED"); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "HMMM...JUST LEAVE THIS TO ME"); 
			}
			if(index == 7)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "COMON ON CHARLIE LET$S LOOK FOR CLUES!"); 
			}
			if(index == 8)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "DON$T MESS UP MY CRIME SCENE");
		}

	}


	// Sixth fight against Jae at nightclub...
	if(scene == 5)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "HMMM...YOU LOOK LIKE A CRIMINAL"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "BUZZ OFF COP I$M BUSY HERE..."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHY DON$T WE SAY HELLO CHARLIE"); 
			}
			if(index == 3)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "HEY KEEP THAT THING AWAY FROM ME!"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU KNOW COPS AREN$T ALLOWED IN HERE"); 
			}
			if(index == 5)   
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "IS THAT SO?"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "YOU MUST BE CRAZY OR STUPID..."); 
			}
			if(index == 7)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I DON$T THINK HE$S GOING TO LISTEN CHARLIE"); 
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
				sprintf( new_counter[1].word, "ALRIGHT! ALRIGHT! JUST CALL OFF THE DOG!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "TELL ME WHAT YOU KNOW MISTER"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "THERE$S A PRISON BREAK... TONIGHT"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "DO YOU THINK HE$S LYING CHARLIE?"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "I-I SWEAR..TONIGHT AT THE NEO SEOUL PRISON!"); 
			}
			if(index == 5) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "LET$S GO CHARLIE!"); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "(HAHA..SHE HAS NO IDEA WHAT$S IN STORE)"); 
			}
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "I$M OUTTA HERE COP SEE YA!");
		}

	}


	// Seventh fight against Siu at the subway...
	if(scene == 6) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "TAKING THE SUBWAY WILL BE MUCH QUICKER!"); 
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
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I$D LOVE TO TALK BUT I$M ON A CASE"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THE POLICE CHIEF WANTS YOU FOR QUESTIONING!"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "WE$RE ON THE SAME SIDE HERE!"); 
			}
			if(index == 5)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "..."); 
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
				VG_Scene_char = 10; 
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "DAMN SHE GOT AWAY..."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 10;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "JUST WHO WAS THAT GIRL?"); 
			} 
			if(index == 2)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU$RE COMING WITH ME!");
		}

	}

	// Eighth fight against Gun at the prison...
	if(scene == 7) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE ALL UNDER ARREST!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "LOOK WHAT WE HAVE HERE BOYS!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "THERE$S NO ESCAPE..."); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HAH! WE HAVE ALITTLE INSIDE HELP COMING"); 
			}
			if(index == 4) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "SO THERE IS CORRUPTION IN THE POLICE!"); 
			}
			if(index == 5)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "THEY$RE ALITTLE LATE SO LET$S HAVE SOME FUN!"); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "..."); 
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
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "NOW LET ME ESCORT YOU BACK TO YOUR CELL"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "IT$S NOT OVER YET COP..."); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "THERE YOU ARE! YOU SURE TOOK YOUR TIME.."); 
			} 
			if(index == 3)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "OUR POLICE FRIEND WILL DEAL WITH YOU!"); 
			} 
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "LOCK HER UP BOYS!");
		}

	}


	// Ninth fight against Mia at the prison...
	if(scene == 8) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "MIA! I$M SO GLAD!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "MINSO! WHAT$S GOING ON HERE?"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "WELL FIRST I SORT OF LOST CHARLIE AND.."); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE GOING TO HAVE TO STAND ASIDE!"); 
			}
			if(index == 4)  
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "B-BUT WHY M-MIA?"); 
			}
			if(index == 5)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "YOU DON$T KNOW ANYTHING MINSO"); 
			}
			if(index == 6) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I MUST RELEASE THESE PRISONERS..."); 
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
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "FORGIVE ME MINSO.. I HAD NO CHOICE!"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HOW COULD YOU MIA? WE$RE BEST FRIENDS"); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THEY TOOK MY LITTLE BOY A WEEK AGO.."); 
			}
			if(index == 3)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "I HAD TO FOLLOW THEIR ORDERS.."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "I$M SO SORRY MINSO..."); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "NO-ONE MAKES MY FRIEND CRY!"); 
			}
			if(index == 6) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHERE$S KYUNG BEING HELD?"); 
			}
			if(index == 7)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "H-HE$S AT THE OLD PLAZA PLEASE SAVE MY BOY!"); 
			}
			if(index == 8) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I WON$T LET YOU DOWN MIA, I PROMISE.."); 
			}
			if(index == 9)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "I$M SORRY MINSO...");
		}

	}

	// Tenth fight against Sang at the apartment...
	if(scene == 9) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "HOW DID YOU GET IN HERE?"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU HURT MIA AND NOW I$M GOING TO HURT YOU"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "AH YES! YOU$RE THE ONE WHO STOPPED YOHAN"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_ANGRY; 
				sprintf( new_counter[1].word, "SO MIA HAS FAILED ME? TOO BAD..."); 
			}
			if(index == 4)  
			{    
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "KYUNG! ARE YOU ALRIGHT?"); 
			}
			if(index == 5)  
			{    
				VG_Scene_char = 4;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "..HMMPH...HMMPH!.."); 
			}
			if(index == 6)   
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I$LL DEAL WITH THE BOY SOON..."); 
			}
			if(index == 7)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "AFTER I KILL YOU!"); 
			}
			if(index == 8) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "R-READY CHARLIE! WE HAVE TO DO THIS!"); 
			}
			if(index == 9)
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
				sprintf( new_counter[1].word, "W-WHAT IS IT YOU WANT? MONEY.."); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "ALL I WANT IS TO SEE YOU BEHIND BARS"); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "POWER? I CAN GIVE YOU EVERYTHING..."); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "IT$S DINNER TIME CHARLIE!"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "N-NO KEEP THAT MUTT AWAY!!!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "ARE YOU OKAY KYUNG?"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 5;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "I-I$M FINE MINSO!"); 
			}
			if(index == 7) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "LET$S SEE YOUR MOM! I FANCY KIMCHI TONIGHT!"); 
			}
			if(index == 8)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "D-DON$T LEAVE ME HERE!"); 
			}
			if(index == 9)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "HAHA! YOU$LL NEVER ARREST ME!");
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
				sprintf( new_counter[1].word, "KYUNG! YOU$RE OK!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 2;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "HEHE! HE$S A TOUGH KID LIKE HIS MOM!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "YOU$RE A REAL HERO MINSO! I$M SO PROUD OF YOU!"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP; 
				sprintf( new_counter[1].word, "IF YOU SAY SO MIA I$M JUST HUNGRY..."); 
			}
			if(index == 4)  
			{    
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "WHO FANCIES KIMCHI!"); 
			}
			if(index == 5)   
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "BUT WHERE$S CHARLIE?"); 
			}
			if(index == 6)  
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "CHARLIE! WHERE IS CHARLIE!"); 
			}
			if(index == 7) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "HAHA..WE$LL FIND HIM TOGETHER THIS TIME"); 
			}
			if(index == 8)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "OKAY!"); 
			}
			if(index == 9) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "(THE END) THANKS FOR PLAYING!"); 
			}
			if(index == 10)
			{
				VG_Scene_char = 102; // Cause ending quit...
			}

		}
		if(condition == VG_STORY_SCENE_LAST) 
		{
			VG_Scene_char = 0;
			VG_Scene_emotion = VG_EMOTION_HAPPY;
			sprintf( new_counter[1].word, "THE GOOD MUST ALWAYS REMAIN VIGILANT!"); 
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
				VG_Scene_char = 11;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "WITH SANG DEFEATED THE CURSE IS LIFTED.."); 
				else
					sprintf( new_counter[1].word, "WITH SANG DEFEATED THE CURSE IS LIFTED.."); 
			}
			if(index == 1) 
			{  
				VG_Scene_char = 11; 
				VG_Scene_emotion = VG_EMOTION_HAPPY;

				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "TIA CONTINUES HER SEARCH FOR HER BROTHER!"); 
				else
					sprintf( new_counter[1].word, "TIA CONTINUES HER SEARCH FOR HER BROTHER!"); 
			}
			if(index == 2)   
			{    
				VG_Scene_char = 11;
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
					VG_Scene_char = 102; // Cause ending quit...
				}
				if(index == 5) 
					VG_Scene_char = 102; // Cause ending quit...
				 
			}
			if(VG_GAME_MODE == VG_ARCADE_MODE)
			if(VG_ARCADE_TYPE == VG_ARCADE_STANDARD && VG_DUELLISTS_UNLOCKED == 1)
			{
				if(index == 3)   
				{  
					VG_Scene_char = 102; // Cause ending quit...
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
				VG_Scene_char = 2;
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
			sprintf( new_counter[1].word, "(OOPS! I NEED TO ARREST THEM!)");
		if(VG_ROUND_CONDITIONS == CONDITION_MUST_WASTE)
			sprintf( new_counter[1].word, "(OOPS! I NEED TO WASTE THEM!)");
		if(VG_ROUND_CONDITIONS == CONDITION_TIMED || VG_ROUND_CONDITIONS == CONDITION_TIMED_BASIC)
			sprintf( new_counter[1].word, "(OH NO! I WASN$T FAST ENOUGH!)");
	}

	if(VG_Scene_char != 101 && VG_Scene_char != 102)
		VG_WrapWord(new_counter[1].word, 25, -1);


}

