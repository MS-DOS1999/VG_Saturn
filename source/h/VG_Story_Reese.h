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

void VG_Help_Story_Reese(int scene, int index)
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
	 
	 
	// First fight against minso at traffic jam...
	if(scene == 0)   
	{ 
		sprintf( new_counter[index].word, "WIN ONE ROUND USING^ONLY YOUR BASIC PUNCHES^AND KICKS TO WIN!^^PUNCHES^%c or %c^^KICKS^%c or %c", punch, punch2, kick, kick2); 
	}
	if(scene == 1)   
	{ 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE ROBBER USING^YOUR STRETCH ARMS MOVE.^ONLY YOUR STRETCH ARMS^WILL DAMAGE HIM!^^STRETCH ATTACK^%c,%c + %c^^STRETCH LOW^%c,%c + %c", right, right, punch2, right, right, punch);
		else
			sprintf( new_counter[index].word, "DEFEAT THE ROBBER USING^YOUR STRETCH ARMS MOVE.^ONLY YOUR STRETCH ARMS^WILL DAMAGE HIM!^^STRETCH ATTACK^%c,%c,%c + %c^^STRETCH LOW^%c,%c,%c + %c", down, downright, right, punch2, down, downright, right, punch);
	}
	if(scene == 2) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
		    sprintf( new_counter[index].word, "DEFEAT AGENT BOB^USING YOUR ELECTRIC ATACKS.^ONLY YOUR ELECTRIC ATTACKS^CAN EFFECT HIM!^^ELECTRIC^HOLD %c^^POWER ORB^%c,%c + %c", kick, left, right, punch2);
		else
		    sprintf( new_counter[index].word, "DEFEAT AGENT BOB^USING YOUR ELECTRIC ATACKS.^ONLY YOUR ELECTRIC ATTACKS^CAN EFFECT HIM!^^ELECTRIC^HOLD %c^^POWER ORB^%c,%c,%c + %c", kick, down, downleft, left, punch2);
	}
	if(scene == 3) 
	{
		sprintf( new_counter[index].word, "WIN ONE ROUND USING^YOUR HANDCUFFS AND THROWS.^YOU CAN ONLY DAMAGE HIM^WHEN HE$S HANDCUFFED^OR WITH THROWS^^HANDCUFF - THROW^PRESS %c", throw_key);
	}
	if(scene == 4) 
	{
		sprintf( new_counter[index].word, "DEFEAT THE SUSPICIOUS MAN^USING YOUR COMBO ATTACK.^ONLY THE COMBO ATTACK WILL^DAMAGE HIM!^^COMBO^%c,%c,%c", kick2, kick2, punch2);
	}
	if(scene == 5) 
	{ 
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE SUBWAY COP^USING ANY MEANS^NECESSARY!^^STRETCH LOW^%c,%c + %c^^ELECTRIC^HOLD %c", right, right, punch, kick);
		else
			sprintf( new_counter[index].word, "DEFEAT THE SUBWAY COP^USING ANY MEANS^NECESSARY!^^STRETCH LOW^%c,%c,%c + %c^^ELECTRIC^HOLD %c", down, downright, right, punch, kick);
	}
	if(scene == 6) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT THE MAN WITH^LOW HEALTH.^^STRETCH ATTACK^%c,%c + %c^^ELECTRIC^HOLD %c", right, right, punch2, kick);
		else
			sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT THE MAN WITH^LOW HEALTH.^^STRETCH ATTACK^%c,%c,%c + %c^^ELECTRIC^HOLD %c", down, downright, right, punch2, kick);
	}
	if(scene == 7)  
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE COP BEFORE^TIME RUNS OUT!^IF THE TIMER RUNS OUT^YOU$LL LOSE THE FIGHT!^^DEFLECT^HOLD %c^^ELECTRIC^HOLD %c", kick2, kick);
		else
			sprintf( new_counter[index].word, "DEFEAT THE COP BEFORE^TIME RUNS OUT!^IF THE TIMER RUNS OUT^YOU$LL LOSE THE FIGHT!^^DEFLECT^HOLD %c^^ELECTRIC^HOLD %c", kick2, kick);
	}
	if(scene == 8) 
	{
		sprintf( new_counter[index].word, "YOU MUST SURVIVE UNTIL THE^TIMER RUNS OUT!^BE CAREFUL AS YOUR ATTACKS^WILL HAVE NO EFFECT!");
	}
	if(scene == 9)  
	{
		sprintf( new_counter[index].word, "YOU MUST ARREST SANG!^DEFEAT HIM ON THE LAST^ROUND WHEN HE$S HANDCUFFED^HE MUST BE HANDCUFFED^TO WIN!^^HANDCUFF - THROW^PRESS %c", throw_key);
	}
}
 
void VG_Init_Story_Reese(int index, int condition, int scene)
{

	VG_Scene_char = 0;

	// First fight against Minso at the traffic jam...
	if(scene == 0)
	{
		if(condition == VG_STORY_SCENE_SETUP) 
		{

			if(index == 0)
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "DAMN! THIS COUNTRY IS HOT... "); 
			}
			if(index == 1) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "AND THIS CITY IS TOO DAMN BIG.. "); 
			}
			if(index == 2)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "HELLO MISTER! ARE YOU HERE ON HOLIDAY?"); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "COULD YOU TELL ME WHERE THE CITY PARK IS?"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HUH! SO YOU CAN DEAL DRUGS!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHAT!... "); 
			}
			if(index == 6)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE COMING WITH ME MISTER!"); 
			}
			if(index == 7)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "WHAT THE HELL IS UP WITH THIS CITY? "); 
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
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "OKAY..SO MAYBE YOU$RE NOT A DRUG DEALER"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "THAT$S WHAT I TRIED TO TELL YOU!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WELL MOVE ALONG THERE$S NOTHING TO SEE HERE! "); 
			} 
			if(index == 3) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "(I CAN$T WAIT TO FINISH THIS MISSION)"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}
			 
		} 
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU$RE COMING DOWNTOWN MISTER DRUG DEALER..");
		}

	} 

	// Second fight against Ye-Jun at the highway...
	if(scene == 1)
	{
		if(condition == VG_STORY_SCENE_SETUP)  
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "A S-SHOOT-OUT IN BROAD DAYLIGHT..."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHY AM I NOT SURPRISED "); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WE$VE GOT COMPANY BOYS THE MILITARY IS HERE!"); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$VE GOT THE WRONG IDEA..."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "TAKE HIM DOWN WITH THE REST OF THE PIGS!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "THIS ISN$T MY DAY.."); 
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
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "DO YOU KNOW WHERE THE PARK IS?"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "S-SURE BIG GUY IT$S STRAIGHT ON... "); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "THANKS FOR YOUR CO-OPERATION.."); 
			}
			if(index == 3)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "N-NO P-PROBLEM..."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "(I HOPE THE TEAM IS SETUP ALREADY)"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "EVEN THE MILITARY CAN$T STOP US!");
		}

	}
	
	// Third fight against Bob at the park...
	if(scene == 2)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "WHAT ARE WE LOOKING AT AGENT BOB?"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "..."); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "WHAT$S THE STATUS? OF THE CRASH SITE.."); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "T-THEY COME... T-THEY ARE HERE.."); 
			}
			if(index == 4) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "JESUS BOB HAVE YOU BEEN DRINKING?"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I CAN HEAR THEM.. THEY SAY YOU ARE BAD"); 
			}
			if(index == 6) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "BOB YOU$RE STARTING TO SCARE ME.."); 
			}
			if(index == 7)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I MUST PROTECT THE LITTLE ONE!"); 
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
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "BOB! BOB! WHERE THE HELL IS HE GOING?"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 11;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "HE$S GOING TO BLOW OUR COVER.."); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 11;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "GET BACK HERE BOB!"); 
			}
			if(index == 3)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "THE LITTLE ONE IS MOST PLEASED!");
		}

	}
	
	// Fourth fight against Sapporo at alleyway...
	if(scene == 3)
	{ 
		if(condition == VG_STORY_SCENE_SETUP)  
		{ 
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "I$M SURE HE CAME THIS WAY.."); 
			}
			if(index == 1)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "H-HOW DID YOU FIND US COP?"); 
			}
			if(index == 2)   
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "DO I LOOK LIKE A COP"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "DAMN! THEY DISCOVERED OUR DEAL"); 
			}
			if(index == 4)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "YOU$LL NEVER ARREST ME!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "(HAS EVERYONE IN THIS CITY GONE CRAZY?)"); 
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
				sprintf( new_counter[1].word, "O-OK YOU WIN..."); 
			}
			if(index == 1) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "DID A MAN IN A SUIT PASS-BY HERE?"); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion =  VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "I-I SAW NOTHING...I SWEAR!"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "DAMMIT BOB! WHERE DID YOU GO?"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "THAT$LL TEACH YOU COP!");
		}

	}

	// Fifth fight against Yohan at the nightclub...
	if(scene == 4)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I BET HE CAME IN HERE THE DRUNK"); 
			}
			if(index == 1)  
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "OF ALL THE TIMES ..."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "W-WHO ARE YOU?"); 
			}
			if(index == 3)  
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "DID A MAN IN.."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "STAY BACK! OR I$LL BLOW THIS JOINT"); 
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "W-WHAT!?!"); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I$M WARNING YOU. I$LL DO IT!"); 
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
				sprintf( new_counter[1].word, "N-NO MY BOMBS ARE BROKEN.."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "IF BOB$S NOT HERE. WHERE THE HELL IS HE?"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "MY LORD WILL PUNISH YOU FOR THIS!"); 
			}
			if(index == 3) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I NEED TO KEEP LOOKING.."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "5..4..3..2.. KA-BOOM!");
		}

	}

	// Sixth fight against Dae-Su at the subway...
	if(scene == 5)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "ANOTHER ONE! YOU WON$T GET AWAY THIS TIME!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "WHAT HAPPENED HERE!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "I GUY IN A SUIT JUST LIKE YOU.."); 
			}
			if(index == 3)   
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "DAMN PUNKS HAVE NO RESPECT!"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "BOB! WHICH WAY DID HE GO?"); 
			}
			if(index == 5)   
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "NOT SO FAST! I WON$T LOSE AGAIN!"); 
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
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I THINK YOU SHOULD GO TO THE HOSPITAL"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "W-WHERE AM I?..."); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "W-WHAT PRETTY STARS!.."); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I$M GETTING CLOSER HE MUST BE NEARBY..."); 
			}
			if(index == 4) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$M COMING BOB.."); 
			}
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "WE$LL BE FLYING YOU BACK TO YOUR COUNTRY!");
		}

	}


	// Seventh fight against Sung-Ki At the apartment...
	if(scene == 6) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "W-WHAT THE HELL ARE YOU PEOPLE..."); 
			}
			if(index == 1) 
			{    
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "Y-YOU CAN$T BE HUMAN.."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "SO BOB WAS HERE AS WELL..."); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHAT ARE YOU UP TO BOB?"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "W-WHAT DO YOU WANT FROM US?"); 
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "LET ME ASK YOU SOME QUESTIONS"); 
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
				sprintf( new_counter[1].word, "A-ALRIGHT I G-GIVE UP!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "SO WHAT DID BOB TELL YOU?"); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "H-HE SAID THE LITTLE ONE HAD A PLAN..."); 
			} 
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "H-HE MENTIONED A DOJO.."); 
			} 
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "GOOD...FORGET I WAS EVER HERE.."); 
			} 
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "NO-ONE CAN DEFEAT THE GREAT SUNG-KI!");
		}

	}

	// Eighth fight against Sabu at the dojo...
	if(scene == 7) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "IF YOU WANT YOUR FRIEND HE JUST LEFT"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "WHAT WAS HE LOOKING FOR.."); 
			}
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "NOW HOW SHOULD I KNOW. HE$S CRAZY.."); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "AND YOU$RE ON PRIVATE PROPERTY.."); 
			}
			if(index == 4) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$D BE GLAD IF YOU$D CO-OPERATE.."); 
			}
  		    if(index == 5)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "YOU PUNKS THINK YOU OWN THIS PLACE!"); 
			}
			if(index == 6) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "LET ME TEACH YOU SOME MANNERS.."); 
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
				sprintf( new_counter[1].word, "SO WHAT DID MY FRIEND SAY?"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "HE SAID SOMETHING ABOUT A SHIP.."); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "HE WAS GOING BACK TO THE MOTHERSHIP.."); 
			} 
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I$VE GOT YOU NOW BOB!"); 
			} 
			if(index == 4) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "TIME TO END THIS..."); 
			} 
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "WELCOME TO OUR COUNTRY PUNK!");
		}

	}


	// Ninth fight against Bob at the park...
	if(scene == 8)  
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "WHAT THE HELLS GOING ON BOB?"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "THE LITTLE ONE SAID YOU WOULD COME..."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "LET$S GET YOU CHECKED OUT.."); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU HAVE MADE THE LITTLE ONE ANGRY!"); 
			}
			if(index == 4)  
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I DON$T WANT TO HURT YOU!"); 
			} 
			if(index == 5)
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
				sprintf( new_counter[1].word, "W-WHAT H-HAPPENED.. R-REESE?"); 
			}
			if(index == 1)   
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "THAT MUST BE SOME HANGOVER.."); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "THERE WAS A VOICE IN MY HEAD..."); 
			}
			if(index == 3) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "SURE THERE WAS. NOW LET$S FINISH THIS JOB"); 
			}
			if(index == 4) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I HEARD THE WORD ..SANG.."); 
			}
			if(index == 5) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WE HAVE TO CHECK IT OUT REESE.."); 
			}
			if(index == 6) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "ALRIGHT..ALRIGHT I$LL CHECK IT OUT.."); 
			}
			if(index == 7) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU$VE DONE ENOUGH. JUST STAY HERE..DON$T MOVE!"); 
			}
			if(index == 8)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "I M-MUST DESTROY...");
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
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "SO YOU MUST BE SANG?"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE THE PUNK WHO BEAT UP ALL MY MEN!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "TELL ME ABOUT THE CRASH AT THE PARK?"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY; 
				sprintf( new_counter[1].word, "YES! YES! BUT I$M TELLING YOU NOTHING!"); 
			}
			if(index == 4)  
			{    
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WE CAN DO THIS THE HARD WAY.."); 
			}
			if(index == 5)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I HAVE SOMETHING IN MY BRIEFCASE FOR YOU.."); 
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
				sprintf( new_counter[1].word, "HAHA! YOU H-HAVE NO IDEA..."); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "THE UFO CRASH AT THE PARK..."); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "W-WAS JUST A HOAX.. WE NEEDED TO SCARE.."); 
			}
			if(index == 3)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "OFF THE LOCAL COUNCIL.. .T-THAT$S ALL.."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "JUST ANOTHER DEAD END... I SHOULD HAVE KNOWN.."); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I$LL BE HAPPY TO LEAVE THIS CRAZY CITY ANYWAY"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "(HEHE! THIS IDIOT HAS NO IDEA...)"); 
			}
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "POLICE! ARREST THIS MAN!");
		}

	}

	// Final ending...
	if(scene == 10) 
	{  
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "PACK IT UP BOYS! WE$RE GOING HOME!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "NO LUCK ON THE SANG LEAD THEN?"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "IT$S ALL A HOAX.. A DIRTY SCHEME!"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE; 
				sprintf( new_counter[1].word, "WE$LL CAPTURE THE TARGET NEXT TIME FOR SURE! "); 
			}
			if(index == 4)  
			{    
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I REALLY THOUGHT WE HAD IT THIS TIME..."); 
			}
			if(index == 5)    
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "LET$S GO HOME!"); 
			}
			if(index == 6)   
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "(THE END) THANKS FOR PLAYING!"); 
			}
			if(index == 7) 
			{     
				VG_Scene_char = 102; // Cause ending quit...
			} 

		}  
		if(condition == VG_STORY_SCENE_LAST) 
		{
			VG_Scene_char = 4;
			VG_Scene_emotion = VG_EMOTION_HAPPY;
			sprintf( new_counter[1].word, "THE BEST PLACE TO HIDE IS IN PLAIN SIGHT.."); 
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
				VG_Scene_char = 3;
				VG_Scene_emotion = VG_EMOTION_HAPPY;

				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "SANG WASN$T AN ALIEN AFTER ALL.."); 
				else
					sprintf( new_counter[1].word, "HAVING DEFEATED SANG BOB LEAVES NEO SEOUL"); 
			}
			if(index == 1) 
			{  
				VG_Scene_char = 3; 
				VG_Scene_emotion = VG_EMOTION_HAPPY;

				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "BUT THE HUNT CONTINUES!"); 
				else
					sprintf( new_counter[1].word, "TO DESTROY THE AGENCY FROM WITHIN!"); 
			}
			if(index == 2)   
			{  
				VG_Scene_char = 3;
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
					if(VG_CHARACTER_LOCKS[VG_REESE] == 1)
						VG_Scene_char = 102; // Cause ending quit...
					else
					{  
						VG_CHARACTER_LOCKS[VG_REESE] = 1;
						VG_Scene_char = 9; // Sets the bg frame...
						VG_Scene_emotion = VG_EMOTION_HAPPY;
						sprintf( new_counter[1].word, "(BOB IS NOW PLAYABLE!)"); 
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
					if(VG_CHARACTER_LOCKS[VG_REESE] == 1)
						VG_Scene_char = 102; // Cause ending quit...
					else
					{  
						VG_CHARACTER_LOCKS[VG_REESE] = 1;
						VG_Scene_char = 9; // Sets the bg frame...
						VG_Scene_emotion = VG_EMOTION_HAPPY;
						sprintf( new_counter[1].word, "(BOB IS NOW PLAYABLE!)"); 
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
				VG_Scene_char = 3;
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
			sprintf( new_counter[1].word, "(OK, I NEED TO ARREST THEM!)");
		if(VG_ROUND_CONDITIONS == CONDITION_MUST_WASTE)
			sprintf( new_counter[1].word, "(OK, I NEED TO WASTE THEM!)");
		if(VG_ROUND_CONDITIONS == CONDITION_TIMED || VG_ROUND_CONDITIONS == CONDITION_TIMED_BASIC)
			sprintf( new_counter[1].word, "(SEEMS I WASN$T FAST ENOUGH!)");
	}

	if(VG_Scene_char != 101 && VG_Scene_char != 102)
		VG_WrapWord(new_counter[1].word, 25, -1);


}

