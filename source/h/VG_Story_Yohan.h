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

void VG_Help_Story_Yohan(int scene, int index)
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
	 
	 
	// First fight against Sung-Ki at the apartment...
	if(scene == 0)    
	{
		sprintf( new_counter[index].word, "WIN ONE ROUND USING^YOUR BASIC PUNCHES AND^KICKS TO WIN!^^PUNCHES^%c or %c^^KICKS^%c or %c", punch, punch2, kick, kick2); 
	}
	if(scene == 1) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE DETECTIVE USING^YOUR VIAL ATTACKS.^ONLY THE VIALS WILL^DAMAGE HIM!^^ACID VIAL^%c,%c + %c^^ACID LOW^%c,%c + %c", right, right, punch2, right, right, punch);
		else
			sprintf( new_counter[index].word, "DEFEAT THE DETECTIVE USING^YOUR VIAL ATTACKS.^ONLY THE VIALS WILL^DAMAGE HIM!^^ACID VIAL^%c,%c,%c + %c^^ACID LOW^%c,%c,%c + %c", down, downright, right, punch2, down, downright, right, punch);
	}
	if(scene == 2)  
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE TRAFFIC COP^USING YOUR BOMB DROP.^ONLY THE BOMB DROP WILL^DAMAGE HER!^^BOMB DROP^%c,%c + %c", left, left, kick2);
		else
			sprintf( new_counter[index].word, "DEFEAT THE TRAFFIC COP^USING YOUR BOMB DROP.^ONLY THE BOMB DROP WILL^DAMAGE HER!^^BOMB DROP^%c,%c,%c + %c", down, downleft, left, kick2);
	}
	if(scene == 3) 
	{
		sprintf( new_counter[index].word, "WIN ONE ROUND USING^YOUR STICKY BOMB AND THROWS.^ONLY THE STICKY BOMB OR^THROW WILL DAMAGE HIM!^^STICKY BOMB - THROW^PRESS %c", throw_key);
	}
	if(scene == 4) 
	{
		sprintf( new_counter[index].word, "DEFEAT THE COP^USING YOUR COMBO ATTACK.^ONLY THE COMBO ATTACK WILL^DAMAGE HIM!^^COMBO^%c,%c,%c", punch, punch, punch2);
	}
	if(scene == 5) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT YOUR FRIEND USING^ANY MEANS NECESSARY!^^SLIDE^%c,%c + %c^^ACID LOW^%c,%c + %c", right, right, kick, right, right, punch);
		else
			sprintf( new_counter[index].word, "DEFEAT YOUR FRIEND USING^ANY MEANS NECESSARY!^^SLIDE^%c,%c,%c + %c^^ACID LOW^%c,%c,%c + %c", down, downright, right, kick, down, downright, right, punch);
	}
	if(scene == 6) 
	{
		sprintf( new_counter[index].word, "YOU MUST SURVIVE UNTIL THE^TIMER RUNS OUT!^BE CAREFUL AS YOUR ATTACKS^WILL HAVE NO EFFECT!");
	}
	if(scene == 7)  
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE CRIME BOSS BEFORE^TIME RUNS OUT!^IF THE TIMER RUNS OUT^YOU$LL LOSE THE FIGHT!^^SLIDE^%c,%c + %c^^ACID LOW^%c,%c + %c", right, right, kick, right, right, punch);
		else
			sprintf( new_counter[index].word, "DEFEAT THE CRIME BOSS BEFORE^TIME RUNS OUT!^IF THE TIMER RUNS OUT^YOU$LL LOSE THE FIGHT!^^SLIDE^%c,%c,%c + %c^^ACID LOW^%c,%c,%c + %c", down, downright, right, kick, down, downright, right, punch);
	}
	if(scene == 8) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT SUNG-KI WITH LOW^HEALTH.^^BOMB DROP^%c,%c + %c^^ACID LOW^%c,%c + %c", left, left, kick2, right, right, punch);
		else
			sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT SUNG-KI WITH LOW^HEALTH.^^BOMB DROP^%c,%c,%c + %c^^ACID LOW^%c,%c,%c + %c", down, downleft, left, kick2, down, downright, right, punch);
	}
/*	if(scene == 9)  
	{
		sprintf( new_counter[index].word, 
	}*/



}

void VG_Init_Story_Yohan(int index, int condition, int scene)
{

	VG_Scene_char = 0;

	// First fight against Sung-Ki at the apartment...
	if(scene == 0)
	{
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			 
			if(index == 0)
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "THE TIME HAS COME MY BOY. THE DAY IS HERE! "); 
			}
			if(index == 1) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I LIVE TO SERVE YOU MASTER! "); 
			}
			if(index == 2)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "TONIGHT BEGINS THE NIGHT OF TERROR! "); 
			}
			if(index == 3)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "ARE YOU READY FOR YOUR TEST YOHAN?"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I WILL NOT FAIL YOU MASTER..."); 
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
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "YOU HAVE PASSED THE TEST..."); 
			}
			if(index == 1) 
			{ 
				VG_Scene_char = 6;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "TAKE YOUR TOOLS AND SET FORTH!"); 
				VG_handcuffs_sfx = true;
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "WE WILL WAKE THE PEOPLE FROM THEIR SLUMBER! "); 
			} 
			if(index == 3) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WITH THE SOUNDS OF EXPLOSIONS!"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}
			 
		} 
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU ARE NOT WORTHY! TRY AGAIN!!");
		}

	} 

	// Second fight against Gyeong at the alleyway...
	if(scene == 1)
	{
		if(condition == VG_STORY_SCENE_SETUP)  
		{
			if(index == 0)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "THIS IS A CRIME SCENE NO CIVILIANS ALLOWED!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "YOU$LL DO NICELY! "); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "DIDN$T YOU HEAR ME BUDDY!"); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "TIME TO TEST OUT THESE ACID VIALS! HEHE!"); 
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
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "W-WHAT ARE YOU TRYING TO ACHIEVE!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "TONIGHT BEGINS THE REIGN OF CHAOS!"); 
			}
			if(index == 2) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "D-DAMN! YOU$RE ONE OF THE BOMBERS..."); 
			}
			if(index == 3)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "I W-WILL AVENGE YOU CHIA!..."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE IN NO STATE TO DO ANYTHING...HEHE!"); 
			}
			if(index == 5)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "D-DAMMIT!"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "THIS AREA IS OFF LIMITS TO CIVILIANS!");
		}

	}
	
	// Third fight against Minso at traffic jam...
	if(scene == 2)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "SO MANY CARS TO DESTROY HEHE!"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "ARE YOU TALKING TO YOURSELF MISTER?"); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "(DAMN A TRAFFIC COP...)"); 
			}
			if(index == 3)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHAT$S IN THAT BAG YOU$RE CARRYING?"); 
			}
			if(index == 4) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "COME OVER HERE AND I$LL SHOW YOU!"); 
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
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "W-WHO ARE YOU!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "JUST SIT BACK AND ENJOY THE SHOW! HEHE!"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THE NIGHT HAS JUST BEGUN!"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "(HMMPH! WHAT A CREEP!)"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU$RE UNDER ARREST FOR CARRYING EXPLOSIVES!");
		}

	}
	
	// Fourth fight against Ye_Jun at highway...
	if(scene == 3)
	{ 
		if(condition == VG_STORY_SCENE_SETUP)   
		{ 
			if(index == 0) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I KNOW YOU, YOU$RE HYUK$S FRIEND?"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHERE IS HE?"); 
			}
			if(index == 2)   
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "WE HAD ALITTLE FALLING OUT. I$M LEADER NOW!"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "HAH! YOU$RE NOTHING TO ME ..."); 
			}
			if(index == 4)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WATCH YOUR MOUTH YOU LITTLE PUNK!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "ANY ENEMY OF HYUK$S IS MY ENEMY TOO..."); 
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
				sprintf( new_counter[1].word, "T-TAKE THE MONEY..IT$S YOURS..."); 
			}
			if(index == 1) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I DON$T WANT YOUR STINKING MONEY.."); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "W-WHAT DO YOU W-WANT?"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "TOO SEE THIS CITY BURN WHAT ELSE?"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "(THIS KID IS TOTALLY NUTS!)"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "I WARNED YOU KID... GIVE IT UP!");
		}

	}

	// Fifth fight against Siu at the subway...
	if(scene == 4)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "LOT$S OF TRAINS TO BLOW UP!"); 
			}
			if(index == 1)  
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "THIS PLATFORM IS CLOSED"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "IT WILL BE WHEN I$M FINISHED WITH IT..."); 
			}
			if(index == 3)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "ARE YOU OKAY? SIR?"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I$VE NEVER FELT BETTER..."); 
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THEN YOU NEED TO MOVE TO THE OTHER PLATFORM"); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "NO...I$M NOT DOING THAT"); 
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
				sprintf( new_counter[1].word, "W-WHAT$S WRONG WITH THIS GUY?"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THE NIGHT OF CHAOS CONTINUES!"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHERE SHALL WE STRIKE NEXT MASTER..."); 
			}
			if(index == 3) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "(SOMEONE HAS TO STOP THIS GUY...)"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU$RE COMING WITH ME!");
		}

	}

	// Sixth fight against Hyuk at the park...
	if(scene == 5)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "THERE YOU ARE HYUK..."); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOHAN, IT$S BEEN AWHILE YOU LOOK DIFFERENT.."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THE NIGHT OF TERROR IS UPON US BROTHER!"); 
			}
			if(index == 3)   
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I HEARD YOU BECAME PART OF THAT WEIRD CULT.."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "IT$S NOT A CULT!"); 
			}
			if(index == 5)   
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "I$M WORRIED ABOUT YOU THAT CULT$S A FRAUD.."); 
			}
			if(index == 6)   
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I HEARD THE LEADER WORKS FOR SOME CRIME BOSS"); 
			}
			if(index == 7)   
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "H-HOW DARE Y-YOU INSULT THE GREAT LEADER!"); 
			}
			if(index == 8)   
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "C-CALM DOWN BUDDY! I-IT$S THE TRUTH I SWEAR!"); 
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
				sprintf( new_counter[1].word, "I-I$M JUST LOOKING OUT FOR YOU YOHAN..."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WE DON$T NEED YOUR HELP!"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "WE$VE KNOWN EACHOTHER SINCE KIDS"); 
			}
			if(index == 3) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "I$M NOT LYING TO YOU YOHAN!"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I$LL ASK MY MASTER THEN! HE KNOWS ALL!"); 
			}
			if(index == 5) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "T-THANKS! Y-YOHAN.."); 
			}
			if(index == 6)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "WHY ARE WE FIGHTING YOHAN!");
		}

	}


	// Seventh fight against Sung-Ki at the nightclub...
	if(scene == 6) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "WHAT ARE YOU DOING HERE?"); 
			}
			if(index == 1) 
			{    
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU$RE SUPPOSED TO BE CREATING MAYHEM!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I$M SORRY MASTER IT$S.."); 
			}  
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "GET BACK OUT THERE! HOW DARE YOU DEFY ME!"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "B-BUT M-MASTER..I.."); 
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I DON$T HAVE TIME FOR YOUR CHILDISH GAMES!"); 
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
				VG_Scene_char = 11; 
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "M-MASTER COME BACK PLEASE!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 11;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHAT IF HYUK WAS RIGHT?"); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 11;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I MUST GO BACK TO THE APARTMENT..."); 
			} 
			if(index == 3)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "NOW GET BACK OUT THERE!");
		}

	}

	// Eighth fight against Sang at the apartment...
	if(scene == 7) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "AH! YOU MUST BE THE TALENTED YOHAN!"); 
			}
			if(index == 1)  
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHO ARE YOU?"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "JUST AN OLD FRIEND OF YOUR MASTERS..."); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "SO YOU$RE THE CRIME BOSS HYUK TALKED ABOUT..."); 
			}
			if(index == 4) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "BE CAREFUL WHAT YOU SAY BOY!"); 
			}
  		    if(index == 5)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "SO THE CULT IS A FRAUD!"); 
			}
			if(index == 6) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "IT SEEMS YOU NEED TO KNOW YOUR PLACE!"); 
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
				sprintf( new_counter[1].word, "M-MASTER WHERE ARE YOU?"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "W-WHAT ARE YOU PLANNING ON D-DOING?"); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I-I$M SO CONFUSED..."); 
			} 
			if(index == 3) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "MASTER!?!"); 
			} 
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "BE CAREFUL WHAT YOU SAY IN FUTURE BOY...");
		}

	}


	// Ninth fight against Sung-Ki at the apartment...
	if(scene == 8)  
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU LITTLE BRAT HOW DARE YOU ATTACK MR.SANG!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHAT$S GOING ON HERE MASTER? "); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "O-OUR P-PLAN TO WAKE UP THE PEOPLE!"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU REALLY BELIEVED THAT RUBBISH..."); 
			}
			if(index == 4)  
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THIS IS ABOUT MONEY AND POWER!"); 
			} 
			if(index == 5)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I-I$LL NEVER FORGIVE YOU!"); 
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
				sprintf( new_counter[1].word, "I$M THROUGH WITH YOUR CULT SUNG-KI!"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "I-I WAS ONLY JOKING YOHAN B-BELIEVE ME..."); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "WE MUST WAKE UP THE PEOPLE!"); 
			}
			if(index == 3) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU AND YOUR BOSS ARE FINISHED..."); 
			}
			if(index == 4) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "I NEVER REALLY WANTED TO JOIN THE CULT.."); 
			}
			if(index == 5) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "O-OF COURSE YOU DID!"); 
			}
			if(index == 6) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "I JUST WANTED TO BELONG..."); 
			}
			if(index == 7) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "WHAT HAPPENED TO ME?"); 
			}
			if(index == 8)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "IT$S TIME YOU DIED FOR THE GREATER CAUSE!");
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
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "A-ARE YOU STILL MAD AT ME?"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "NO...I FEEL..BETTER NOW...THANKS HYUK"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "GOOD $CAUSE I WAS LOOKING FOR A REMATCH!"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY; 
				sprintf( new_counter[1].word, "HAHA! ANYTIME! "); 
			}
			if(index == 4)  
			{    
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "YOU KNOW I$M LOOKING FOR A NEW GANG MEMBER?"); 
			}
			if(index == 5)    
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "THANKS, BUT I NEED TO DO SOME SOUL SEARCHING"); 
			}
			if(index == 6)  
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I DON$T KNOW WHO I AM ANYMORE..."); 
			}
			if(index == 7)   
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "BUT TODAY$S A GOOD DAY TO START!"); 
			}
			if(index == 8)   
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "(THE END) THANKS FOR PLAYING!"); 
			}
			if(index == 9)  
			{
				VG_Scene_char = 102; // Cause ending quit...
			} 

		}  
		if(condition == VG_STORY_SCENE_LAST) 
		{
			VG_Scene_char = 7;
			VG_Scene_emotion = VG_EMOTION_HAPPY;
			sprintf( new_counter[1].word, "WHAT HAPPENS WHEN WE FORGET WHO WE ARE?"); 
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
				VG_Scene_char = 4;
				VG_Scene_emotion = VG_EMOTION_HAPPY;

				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "WITH SANG DEFEATED THE CULT TAKES CONTROL.."); 
				else
					sprintf( new_counter[1].word, "WITH SANG DEFEATED THE CAPITAL FALLS.."); 
			}
			if(index == 1) 
			{  
				VG_Scene_char = 4; 
				VG_Scene_emotion = VG_EMOTION_HAPPY;

				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "YOHAN CONTINUES THE REIGN OF CHAOS!"); 
				else
					sprintf( new_counter[1].word, "THE COUNTRY IS CONSUMED BY CIVIL WAR!"); 

			}
			if(index == 2)   
			{  
				VG_Scene_char = 4;
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
					if(VG_CHARACTER_LOCKS[VG_YOHAN] == 1)
						VG_Scene_char = 102; // Cause ending quit...
					else
					{  
						VG_CHARACTER_LOCKS[VG_YOHAN] = 1;
						VG_Scene_char = 9; // Sets the bg frame...
						VG_Scene_emotion = VG_EMOTION_HAPPY;
						sprintf( new_counter[1].word, "(SUNG-KI IS NOW PLAYABLE!)"); 
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
					if(VG_CHARACTER_LOCKS[VG_YOHAN] == 1)
						VG_Scene_char = 102; // Cause ending quit...
					else
					{  
						VG_CHARACTER_LOCKS[VG_YOHAN] = 1;
						VG_Scene_char = 9; // Sets the bg frame...
						VG_Scene_emotion = VG_EMOTION_HAPPY;
						sprintf( new_counter[1].word, "(SUNG-KI IS NOW PLAYABLE!)"); 
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
				VG_Scene_char = 4;
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
			sprintf( new_counter[1].word, "(SEEMS I NEED TO ARREST THEM!)");
		if(VG_ROUND_CONDITIONS == CONDITION_MUST_WASTE)
			sprintf( new_counter[1].word, "(SEEMS I NEED TO WASTE THEM!)");
		if(VG_ROUND_CONDITIONS == CONDITION_TIMED || VG_ROUND_CONDITIONS == CONDITION_TIMED_BASIC)
			sprintf( new_counter[1].word, "(SEEMS I WASN$T FAST ENOUGH!)");
	}

	if(VG_Scene_char != 101 && VG_Scene_char != 102)
		VG_WrapWord(new_counter[1].word, 25, -1);


}

