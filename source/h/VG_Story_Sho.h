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

void VG_Help_Story_Sho(int scene, int index)
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
	 
	 
	// First fight against Sapporo at the alleyway...
	if(scene == 0)   
	{
		sprintf( new_counter[index].word, "WIN ONE ROUND USING^YOUR BASIC PUNCHES AND^KICKS TO WIN!^^PUNCHES^%c or %c^^KICKS^%c or %c", punch, punch2, kick, kick2); 
	}
	if(scene == 1) 
	{
		sprintf( new_counter[index].word, "DEFEAT SUNG-KI USING^YOUR PIGEON ATTACK.^ONLY YOUR PIGEON ATTACK^WILL DAMAGE HIM!^^PIGEON^HOLD %c", kick2);
	}
	if(scene == 2) 
	{
		sprintf( new_counter[index].word, "WIN ONE ROUND USING^YOUR HANDCUFFS AND THROWS.^YOU CAN ONLY DAMAGE HIM^WHEN HE$S HANDCUFFED^OR WITH THROWS^^HANDCUFF - THROW^PRESS %c", throw_key);
	}
	if(scene == 3) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE COP USING^THE PISTOL. ONLY THE PISTOL^WILL DAMAGE HER!^^PISTOL^%c,%c + %c^^PISTOL LOW^%c,%c + %c", left, right, punch2, left, right, punch);
		else
			sprintf( new_counter[index].word, "DEFEAT THE COP USING^THE PISTOL. ONLY THE PISTOL^WILL DAMAGE HER!^^PISTOL^%c,%c,%c + %c^^PISTOL LOW^%c,%c,%c + %c", down, downleft, left, punch2, down, downleft, left, punch);
	}
	if(scene == 4) 
	{
		sprintf( new_counter[index].word, "DEFEAT THE ROBBER^USING YOUR COMBO ATTACK.^ONLY THE COMBO ATTACK WILL^DAMAGE HIM!^^COMBO^%c,%c,%c,%c", kick2, kick2, kick2, kick2);
	}
	if(scene == 5)  
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE YAKUZA^USING ANY MEANS^NECESSARY!^^TRIP^%c,%c + %c^^PISTOL^%c,%c + %c", right, right, kick, left, right, punch2);
		else
			sprintf( new_counter[index].word, "DEFEAT THE YAKUZA^USING ANY MEANS^NECESSARY!^^TRIP^%c,%c,%c + %c^^PISTOL^%c,%c,%c + %c", down, downright, right, kick, down, downleft, left, punch2);
	}
	if(scene == 6) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "STOP THE PRISONER QUICK^BEFORE TIME RUNS OUT!^IF THE TIMER RUNS OUT^YOU$LL LOSE THE FIGHT!^^PIGEON^HOLD %c^^PISTOL^%c,%c + %c^", kick2, left, right, punch2);
		else
			sprintf( new_counter[index].word, "STOP THE PRISONER QUICK^BEFORE TIME RUNS OUT!^IF THE TIMER RUNS OUT^YOU$LL LOSE THE FIGHT!^^PIGEON^HOLD %c^^PISTOL^%c,%c,%c + %c^", kick2, down, downleft, left, punch2);
	}
	if(scene == 7)  
	{
		sprintf( new_counter[index].word, "YOU MUST ARREST THE SUSPECT!^DEFEAT HIM ON THE LAST^ROUND WHEN HE$S HANDCUFFED^HE MUST BE HANDCUFFED^TO WIN!^^HANDCUFF - THROW^PRESS %c", throw_key);
	}
	if(scene == 8) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT SANG WITH LOW^HEALTH.^^PIGEON^HOLD %c^^PISTOL^%c,%c + %c^", kick2, left, right, punch2);
		else
			sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT SANG WITH LOW^HEALTH.^^PIGEON^HOLD %c^^PISTOL^%c,%c,%c + %c^", kick2, down, downleft, left, punch2);
	}
/*	if(scene == 9)  
	{
		sprintf( new_counter[index].word, " ", kick, punch);
	}*/


}

void VG_Init_Story_Sho(int index, int condition, int scene)
{

	VG_Scene_char = 0;

	// First fight against Dae-su at the dojo...
	if(scene == 0)
	{
		if(condition == VG_STORY_SCENE_SETUP) 
		{

			if(index == 0)
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "YOU$RE RIGHT ON TIME SON.. "); 
			}
			if(index == 1) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "EVERY FRIDAY FATHER.. "); 
			}
			if(index == 2)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "ALTHOUGH I DON$T KNOW WHAT USE THIS IS. "); 
			}
			if(index == 3)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HAND COMBAT BUILDS DISCLIPLINE SON!"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "SURE DAD! BUT WHAT IF THE ENEMY HAS A GUN!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "HAH! WE$LL GET TO THAT..."); 
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
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "YOU$VE REALLY IMPROVED!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I-IS IT TRUE ABOUT THE CORRUPTION DAD?"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "THAT$S THE FIRST TIME YOU$VE ASKED THAT SON "); 
			} 
			if(index == 3) 
			{  
				VG_Scene_char = 4;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I WANT YOU TO HAVE MY PIGEON.."); 
				VG_handcuffs_sfx = true;
			}
			if(index == 4)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "W-WHAT USE IS A PIGEON IN A FIGHT... "); 
			} 
			if(index == 5) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "NEVER FORGET THE POWER OF NATURE SIU!"); 
			}
			if(index == 6)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I-I WON$T FATHER.. "); 
			} 
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}
			 
		} 
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU MUST FOCUS HARDER SIU!");
		}

	} 

	// Second fight against Sung-Ki at the subway...
	if(scene == 1)
	{
		if(condition == VG_STORY_SCENE_SETUP)  
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "IT$S GOOD TO BE BACK TO WORK!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "(HUH? A SUBWAY COP..) "); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "CAN I HELP YOU SIR?"); 
			}
			if(index == 3) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I-I$M FINE...REALLY."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "SAY WHAT$S IN THE BAG MISTER?"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "(DAMMIT IT! HE KNOWS..)"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HEY! I$M TALKING TO YOU!"); 
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
				sprintf( new_counter[1].word, "THIS BAG IS FULL OF EXPLOSIVES!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "Y-YOU$LL GET NOTHING FROM ME COP.. "); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU$RE UNDER ARREST.."); 
			}
			if(index == 3)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "AND I$LL BE OUT IN NO TIME! HAHA!"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "(T-THERE REALLY IS CORRUPTION THEN..)"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "(I MUST GET TO THE BOTTOM OF THIS!)"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "STAY OUT OF OUR WAY POLICEMAN...");
		}

	}
	
	// Third fight against Gyeong at the alleyway...
	if(scene == 2)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "MAY I HELP YOU?"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "THIS IS WHERE THE CHIEF WAS MURDERED?"); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHAT OF IT KID?"); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "A-ARE YOU CORRUPT TO?"); 
			}
			if(index == 4) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THAT$S DANGEROUS TALKING..."); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "TELL ME WHAT YOU KNOW!"); 
			}
			if(index == 6) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "QUIT BOSSING ME AROUND IT$S ANNOYING!"); 
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
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "I WAS JUST LIKE YOU WHEN I WAS YOUNGER.."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "I THOUGHT I COULD CHANGE THE SYSTEM TOO."); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHAT STOPPED YOU?"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "LIFE KID..."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I$M NOT GIVING UP! SOMEONE HAS TO FIX IT!"); 
			}
			if(index == 5)
			{ 
				VG_Scene_char = 5;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "YOU KNOW HOW TO USE ONE OF THESE?"); 
				VG_handcuffs_sfx = true;
			} 
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "O-OF COURSE..."); 
			} 
			if(index == 7)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "YOU$LL NEED IT KID. WATCH YOUR ASS OUT THERE!"); 
			} 
			if(index == 8)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "I$LL DO WHAT I CAN ON MY END..."); 
			} 
			if(index == 9)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU$RE IN TOO DEEP KID..");
		}

	}
	
	// Fourth fight against Mia at traffic jam...
	if(scene == 3)
	{ 
		if(condition == VG_STORY_SCENE_SETUP)  
		{ 
			if(index == 0)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I$M BUSY HERE WHAT DO YOU WANT?"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "W-WELL I$M LOOKING FOR SOMETHING.."); 
			}
			if(index == 2)   
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I DON$T HAVE ALL DAY OFFICER"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I HEARD THERE WAS ISSUES IN THE POLICE.."); 
			}
			if(index == 4)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "...W-WHAT DO YOU MEAN?..."); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "SO YOU DO KNOW SOMETHING!"); 
			}
			if(index == 6)   
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU CAN$T PROVE ANYTHING BRAT!"); 
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
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "W-WHAT DO YOU WANT FROM ME?"); 
			}
			if(index == 1) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHAT$S GOING ON WITH THE POLICE FORCE?"); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "M-MOST OF US SOLD OUT I HAD.."); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "SOLD OUT! TO WHO!"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "L-LOOK FOR THE YAKUZA CLAN..."); 
			}
			if(index == 5)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HOW CAN YOU CALL YOURSELF AN OFFICER!"); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "..."); 
			}
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "DO YOU HAVE A DEATHWISH OFFICER?");
		}

	}

	// Fifth fight against Hyuk at the highway...
	if(scene == 4)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "A SHOOT OUT? THEY COULD USE MY HELP!"); 
			}
			if(index == 1)  
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "MORE DAMN COPS..."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "PUT YOUR HANDS UP!"); 
			} 
			if(index == 3)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$LL NEVER TAKE ME ALIVE PIG!"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "(I BETTER TAKE THIS GUY DOWN QUICK!)"); 
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
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "O-OK! I SURRENDER.."); 
			}
			if(index == 1)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$LL LET THE OTHER POLICE DEAL WITH YOU!"); 
			} 
			if(index == 2)  
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "NOW I NEED TO FIND THESE YAKUZA GUYS.."); 
			}
			if(index == 3) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "I T-THINK I$M LOST THOUGH..."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "ONE MORE COP BITES THE DUST BOYS!");
		}

	}

	// Sixth fight against Jae at the nightclub...
	if(scene == 5)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "WOW! I NEVER KNEW THIS PLACE EXISTED"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THERE$S NO COPS ALLOWED IN HERE!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I$M AN OFFICER OF THE LAW..."); 
			}
			if(index == 3)   
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "DIDN$T YOU GET THE MEMO BUDDY?"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$M GOING TO ASK YOU SOME QUESTIONS"); 
			}
			if(index == 5)   
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "IS THAT SO COP? YOU$RE MAKING ME LAUGH"); 
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
				sprintf( new_counter[1].word, "W-WHAT DO YOU WANT O-OFFICER?"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHO$S BEHIND THE POLICE CORRUPTION?"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "I CAN$T TELL YOU. BUT I KNOW A GUY.."); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "WHAT GUY?"); 
			}
			if(index == 4) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "THEY$RE BREAKING OUT OF JAIL TONIGHT.."); 
			}
			if(index == 5)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I$M FINALLY GETTING SOMEWHERE!"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU CAN$T ARREST ME COP!");
		}

	}


	// Seventh fight against Konu at the prison...
	if(scene == 6) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "THE YAKUZA GUY SURE WASN$T KIDDING!"); 
			}
			if(index == 1) 
			{    
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "ARE YOU OUR INSIDE HELP?"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "NO! SORRY TO DISAPPOINT YOU.."); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "ANOTHER COP TO PLAY WITH BOYS!"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "LET ME ESCORT YOU BACK TO YOUR CELL!"); 
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE DEAD MEAT KID..."); 
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
				sprintf( new_counter[1].word, "W-WHAT ARE YOU DOING HERE ANYWAY?"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "TELL ME WHO$S BEHIND THE POLICE CORRUPTION!"); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "H-HE$S AT THE OLD PLAZA ASK HIM YOURSELF"); 
			} 
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "(DAMN! I$M GOING TO HAVE TO GO IN ALONE)"); 
			} 
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$M ALMOST THERE! FATHER."); 
			} 
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "LOCK HIM UP BOYS!");
		}

	}

	// Eighth fight against Sabu at the apartment...
	if(scene == 7) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "S-SIU AM I GLAD TO SEE YOU KID!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "SABU? WHAT ARE YOU DOING HERE?"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "THE BIG BOSS WILL BE ARRIVING SOON..."); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I$VE GOT YOUR BACK SABU!"); 
			}
			if(index == 4) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHICH MEANS YOU$VE SEEN TOO MUCH KID.."); 
			}
  		    if(index == 5)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "S-SABU! W-WHY?"); 
			}
			if(index == 6) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I ALWAYS LIKED YOU AND YOUR DAD...BUT.."); 
			}
			if(index == 7) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "DEAD MEN CAN$T TALK NOW CAN THEY?"); 
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
				sprintf( new_counter[1].word, "L-LOOKS LIKE YOU WIN KID.."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;  
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE A PART OF ALL THIS.."); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "MY DOJO WASN$T DOING SO WELL..."); 
			} 
			if(index == 3) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "I HAD TO MAKE THE CASH SOMEHOW..."); 
			} 
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "BY SELLING INFORMATION?"); 
			} 
			if(index == 5) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "A-AND WORSE KID..."); 
			} 
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU BETRAYED US ALL SABU..."); 
			} 
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU$LL NEVER ARREST ME KID!");
		}

	}


	// Ninth fight against Sang at the apartment...
	if(scene == 8)  
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "WHAT DO WE HAVE HERE? FRIEND OF YOURS SABU?"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "SO YOU$RE THE CREEP BEHIND THE CORRUPTION!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I GUESS YOU CAUGHT ME RED HANDED OFFICER!"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE UNDER ARREST!"); 
			}
			if(index == 4)  
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HOW ABOUT I DON$T COME QUIETLY!"); 
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
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "I-I$LL GIVE YOU ANYTHING YOU W-WANT!"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "M-MONEY POWER!"); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I$M HAPPY WITH MY CURRENT JOB, BUT THANKS"); 
			}
			if(index == 3) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "YOU LITTLE PUNK!"); 
			}
			if(index == 4) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$LL BE GOING AWAY FOR A LONG TIME"); 
			}
			if(index == 5) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "THE POLICE FORCE IS SAFE AGAIN!"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "SAY GOODNIGHT PUNK!");
		}

	}

	// Tenth fight against Sapporo at the alleyway...
/*	if(scene == 9) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)  
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I KNEW I$D FIND YOU HERE..."); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "YOU DID IT BROTHER! THIS CITY IS OURS!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU NEVER TOLD ME WHAT HAPPENED TO FATHER"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY; 
				sprintf( new_counter[1].word, "WHAT ARE YOU GETTING AT JAE?"); 
			}
			if(index == 4)  
			{    
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU KILLED HIM DIDN$T YOU..."); 
			}
			if(index == 5)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "T-THAT$S RIDICULOUS.."); 
			}
			if(index == 6)  
			{    
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "SO SANG WAS RIGHT H-HOW COULD YOU!"); 
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
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "T-TOGETHER WE CAN RULE THIS CITY.."); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "IT$S OVER BROTHER THE CLAN IS MINE NOW"); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "Y-YOU CAN$T RUN IT WITHOUT ME!"); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "LEAVE THIS CITY AND NEVER COME BACK..."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "Y-YOU LITTLE P-PUNK!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "THING$S ARE GOING TO CHANGE AROUND HERE"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "WE WON$T BE NEEDING YOU ANYMORE BROTHER..");
		}

	}*/

	// Final ending...
	if(scene == 9) 
	{  
		if(condition == VG_STORY_SCENE_SETUP)   
		{
			if(index == 0)  
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY; 
				sprintf( new_counter[1].word, "SON WHERE HAVE YOU BEEN!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY; 
				sprintf( new_counter[1].word, "SORRY I$M LATE DAD!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY; 
				sprintf( new_counter[1].word, "HMMM! I SEE SABU IS STILL MISSING.."); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;  
				sprintf( new_counter[1].word, "I DON$T THINK WE$LL SEE HIM FOR AWHILE.."); 
			}
			if(index == 4)  
			{    
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY; 
				sprintf( new_counter[1].word, "ALRIGHT LET$S BEGIN THE TRAINING!"); 
			}
			if(index == 5)    
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY; 
				sprintf( new_counter[1].word, "SURE THING DAD!"); 
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
			VG_Scene_char = 6;
			VG_Scene_emotion = VG_EMOTION_HAPPY; 
			sprintf( new_counter[1].word, "SOME TRADITIONS ARE WORTH SAVING..."); 
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
				VG_Scene_char = 10;
				VG_Scene_emotion = VG_EMOTION_HAPPY;

				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "WITH SANG DEFEATED THE CURSE IS LIFTED.."); 
				else
					sprintf( new_counter[1].word, "WITH SANG DEFEATED THE CURSE IS LIFTED.."); 
			}
			if(index == 1) 
			{  
				VG_Scene_char = 10; 
				VG_Scene_emotion = VG_EMOTION_HAPPY;

				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "SHO CAN FINALLY RETURN TO HIS HOMELAND!"); 
				else
					sprintf( new_counter[1].word, "SHO CAN FINALLY RETURN TO HIS HOMELAND!"); 
			}
			if(index == 2)   
			{  
				VG_Scene_char = 10;
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
				VG_Scene_char = 1;
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
			sprintf( new_counter[1].word, "(OH NO! I NEED TO ARREST THEM!)");
		if(VG_ROUND_CONDITIONS == CONDITION_MUST_WASTE)
			sprintf( new_counter[1].word, "(OH NO! I NEED TO WASTE THEM!)");
		if(VG_ROUND_CONDITIONS == CONDITION_TIMED || VG_ROUND_CONDITIONS == CONDITION_TIMED_BASIC)
			sprintf( new_counter[1].word, "(OH NO! I WASN$T FAST ENOUGH!)");
	}


	if(VG_Scene_char != 101 && VG_Scene_char != 102)
		VG_WrapWord(new_counter[1].word, 25, -1);


}

