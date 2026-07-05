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

void VG_Help_Story_Jae(int scene, int index)
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
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE FOREIGNER USING^YOUR BREAKDANCE MOVE.^ONLY THE BREAKDANCE WILL^DAMAGE HIM!^^BREAKDANCE^%c,%c + %c", right, left, kick);
		else
			sprintf( new_counter[index].word, "DEFEAT THE FOREIGNER USING^YOUR BREAKDANCE MOVE.^ONLY THE BREAKDANCE WILL^DAMAGE HIM!^^BREAKDANCE^%c,%c,%c + %c", down, downleft, left, kick);
	}
	if(scene == 2) 
	{
		sprintf( new_counter[index].word, "DEFEAT THE SUBWAY COP^USING YOUR UZI.^ONLY THE UZI WILL^DAMAGE HIM!^^UZI^HOLD %c", punch);
	}
	if(scene == 3) 
	{
		sprintf( new_counter[index].word, "DEFEAT THE NEW COP^USING YOUR COMBO ATTACK.^ONLY THE COMBO ATTACK WILL^DAMAGE HIM!^^COMBO^%c,%c,%c", punch, punch, kick);
	}
	if(scene == 4) 
	{
		sprintf( new_counter[index].word, "WIN ONE ROUND USING^YOUR BACKSTAB AND THROWS.^YOU CAN ONLY DAMAGE HER^WHEN SHE$S DIZZY^OR WITH THROWS^^BACKSTAB - THROW^PRESS %c", throw_key);
	}
	if(scene == 5) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "YOU MUST DEFEAT THE COP!^USE ANY MEANS^NECESSARY!^^MAD DASH^%c,%c + %c^^UZI^HOLD %c", left, right, kick2, punch);
		else
			sprintf( new_counter[index].word, "YOU MUST DEFEAT THE COP!^USE ANY MEANS^NECESSARY!^^MAD DASH^%c,%c,%c + %c^^UZI^HOLD %c", down, downright, right, kick2, punch);
	}
	if(scene == 6) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT THE ROBBER WITH^LOW HEALTH.^^BREAKDANCE^%c,%c + %c^^UZI^HOLD %c", right, left, kick, punch);
		else
			sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT THE ROBBER WITH^LOW HEALTH.^^BREAKDANCE^%c,%c,%c + %c^^UZI^HOLD %c", down, downleft, left, kick, punch);
	}
	if(scene == 7)  
	{
		sprintf( new_counter[index].word, "YOU MUST SURVIVE UNTIL THE^TIMER RUNS OUT!^BE CAREFUL AS YOUR ATTACKS^WILL HAVE NO EFFECT!^^BULLET DEFLECT^%c,%c or %c,%c", left, left, right, right);
	}
	if(scene == 8)  
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT SANG BEFORE^TIME RUNS OUT!^IF THE TIMER RUNS OUT^YOU$LL LOSE THE FIGHT!^^BREAKDANCE^%c,%c + %c^^UZI^HOLD %c", right, left, kick, punch);
		else
			sprintf( new_counter[index].word, "DEFEAT SANG BEFORE^TIME RUNS OUT!^IF THE TIMER RUNS OUT^YOU$LL LOSE THE FIGHT!^^BREAKDANCE^%c,%c,%c + %c^^UZI^HOLD %c", down, downleft, left, kick, punch);
	}
	if(scene == 9)  
	{
		sprintf( new_counter[index].word, "YOU MUST WASTE SAPPORO!^DEFEAT HIM ON THE LAST^ROUND WHEN HE$S DIZZY^HE MUST BE DIZZY^TO WIN!^^DIZZY - THROW^PRESS %c", throw_key);
	}
}

void VG_Init_Story_Jae(int index, int condition, int scene)
{

	VG_Scene_char = 0;

	// First fight against Sapporo at the alleyway...
	if(scene == 0)
	{
		if(condition == VG_STORY_SCENE_SETUP) 
		{

			if(index == 0)
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "GOOD YOU MADE IT! "); 
			}
			if(index == 1) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHAT$S THE WORD BOSS? "); 
			}
			if(index == 2)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "WE$VE GOT A LITTLE JOB FOR YOU... "); 
			}
			if(index == 3)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "LET$S SEE IF YOU HAVE WHAT IT TAKES"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I WON$T LET THE CLAN DOWN BOSS"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "HAH! WE$LL SEE..."); 
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
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "ALRIGHT! ENOUGH..."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "THAT$S WHY WE$RE NUMBER ONE BOSS!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "HERE$S THE LIST OF TARGETS... "); 
			} 
			if(index == 3) 
			{  
				VG_Scene_char = 4;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "AND SOME FIREPOWER.. DON$T LET ME DOWN"); 
				VG_handcuffs_sfx = true;
			}
			if(index == 4)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I SERVE THE CLAN BOSS. IT$LL BE DONE "); 
			} 
			if(index == 5) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "FINE COME SEE ME WHEN YOU$RE FINISHED"); 
			}
			if(index == 6)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "(I CAN FINALLY PROVE MYSELF TO THE CLAN!) "); 
			} 
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}
			 
		} 
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU$RE A DISGRACE TO THE CLAN...");
		}

	} 

	// Second fight against Reese at the park...
	if(scene == 1)
	{
		if(condition == VG_STORY_SCENE_SETUP)  
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "(FIRST TARGET IS A DUDE CALLED SIU...)"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "THIS IS A RESTRICTED AREA.. "); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "(WHO$S THIS BOZO?)"); 
			}
			if(index == 3)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THIS PARK IS CLOSED..."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "DO YOU HAVE ANY IDEA WHO YOU$RE MESSING WITH?"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$M GOING TO ASK YOU TO MOVE AROUND"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "NO-ONE TELLS US WHAT TO DO BUDDY"); 
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
				sprintf( new_counter[1].word, "LOOKS LIKE MY TARGET IS AT THE SUBWAY"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "Y-YOU SAW NOTHING H-HERE... "); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "YOU STILL ALIVE?"); 
			}
			if(index == 3)  
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THIS IS OUR TURF BUDDY, BEAT IT..."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "TIME TO TAKE OUT TARGET NUMBER ONE"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "THIS AREA IS RESTRICTED...");
		}

	}
	
	// Third fight against Siu at the subway...
	if(scene == 2)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "MAY I HELP YOU?"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "SO YOU MUST BE SIU?"); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YEAH THAT$S ME. WHAT OF IT?"); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU$VE BEEN POKING AROUND OUR AFFAIRS"); 
			}
			if(index == 4) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "IT$S NOT NICE TO BE SO NOSEY!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I HAVE NO IDEA WHAT YOU$RE TALKING ABOUT"); 
			}
			if(index == 6) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU SHOULDN$T THREATEN AN OFFICER!"); 
			}
			if(index == 7)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "DAMMIT KID.."); 
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
				sprintf( new_counter[1].word, "W-WHO ARE YOU?"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "LOOK KID..JUST TAKE A BRIBE..."); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "..."); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "NOW YOU$RE MAKING ME ANGRY KID!"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "NEXT TIME DON$T THREATEN AN OFFICER!");
		}

	}
	
	// Fourth fight against Dae-Su at subway...
	if(scene == 3)
	{ 
		if(condition == VG_STORY_SCENE_SETUP)  
		{ 
			if(index == 0)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "SON! SON! ARE YOU ALRIGHT?"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I WARNED YOU PUNKS TO BACK OFF!"); 
			}
			if(index == 2)   
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "LOOK POPS THIS DOESN$T CONCERN YOU..."); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "TELL YOUR DAMN CLAN WE$LL GET YOU!"); 
			}
			if(index == 4)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "(HOW DID THIS MESS ESCULATE SO FAST?)"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE LEAVING ME NO CHOICE HERE POPS..."); 
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
				sprintf( new_counter[1].word, "I-IS THIS WHAT YOU REALLY WANT?"); 
			}
			if(index == 1) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I-IT$S NOT PERSONAL ..I MEAN.."); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "JUST KEEP OUT OF OUR WAY"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "..."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "(I MUST PROTECT OUR CLAN...)"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "I$LL SEE YOU IN COURT PUNK!");
		}

	}

	// Fifth fight against Minso at the Traffic Jam...
	if(scene == 4)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "(NEXT ON THE LIST HMMM...)"); 
			}
			if(index == 1)  
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "COULD YOU MOVE YOUR VAN PLEASE!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "SAY DO YOU KNOW A COP CALLED MIA?"); 
			}
			if(index == 3)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I SURE DO...I MEAN, WHO WANTS TO KNOW?"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I$M AN OLD FRIEND OF HERS YOU SEE"); 
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHO DID YOU SAY YOU WERE?"); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "(THIS ISN$T WORKING..)"); 
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
				sprintf( new_counter[1].word, "I-I$LL NEVER TELL YOU MIA$S AT THE DOJO.."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "OOPS..."); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "THANKS LADY THAT$S ALL I NEEDED..."); 
			}
			if(index == 3) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "TIME TO VISIT THIS MIA CHICK.."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "NEXT TIME MOVE YOUR VAN PLEASE!");
		}

	}

	// Sixth fight against Mia at the dojo...
	if(scene == 5)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I KNOW WHY YOU$RE HERE.."); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "TELL SANG I WON$T DO IT.."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "LOOK LADY I DON$T WANT THIS EITHER.."); 
			}
			if(index == 3)   
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "BESIDES I$M HERE FOR YOUR KID.."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "LEAVE KYUNG OUT OF THIS..P-PLEASE!"); 
			}
			if(index == 5)   
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "T-THAT$S MY ORDERS.."); 
			}
			if(index == 6)   
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "JUST DO WANT THEY WANT AND IT$LL BE OVER"); 
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
				sprintf( new_counter[1].word, "YOU$RE COMING WITH ME KID.."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 3;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "LEAVE MY MOM ALONE!"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "NO HARM WILL COME TO HIM. I PROMISE"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "...I$LL DO IT.. JUST DON$T HURT KYUNG!"); 
			}
			if(index == 4) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "COME ON KID! WE$RE GOING ON A TRIP"); 
			}
			if(index == 5)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "(IS THIS REALLY BEST FOR THE CLAN?)"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "THERE$S YOUR ANSWER!");
		}

	}


	// Seventh fight against hyuk on the highway...
	if(scene == 6) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "DAMN! A SHOOT-OUT..."); 
			}
			if(index == 1) 
			{    
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "STAY HERE KID! I$LL DEAL WITH THIS.."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I CAN PROTECT MYSELF MISTER"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "HAH! SURE YOU CAN SQUIRT! STAY BY THE VAN"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "A-ARE YOU REALLY GOING TO PROTECT ME?"); 
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "OF COURSE KID! I PROMISED DIDN$T I?"); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
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
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "THAT WAS AMAZING MISTER!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I TOLD YOU I$D PROTECT YOU SQUIRT"); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "C-CAN YOU TEACH ME THOSE MOVES.."); 
			} 
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "SURE!..I MEAN.. LISTEN KID.."); 
			} 
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "..FORGET IT.."); 
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
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "KEEP OUT OF MY WAY, YAKUZA SCUM!");
		}

	}

	// Eighth fight against Sapporo at the nightclub...
	if(scene == 7) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I BROUGHT THE KID AS YOU WANTED BOSS"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "GOOD YOU$VE DONE WELL JAE..."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I JUST DON$T KNOW ABOUT ALL THIS"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "IS THIS REALLY BEST FOR THE CLAN? BROTHER?"); 
			}
			if(index == 4) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I TOLD YOU NEVER TO CALL ME THAT!"); 
			}
  		    if(index == 5)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I KNOW FATHER LEFT YOU THE CLAN.."); 
			}
			if(index == 6) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "IT SEEMS YOU NEED TO KNOW YOUR PLACE!"); 
			}
			if(index == 7) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "LITTLE BROTHER..."); 
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
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "ANY MORE QUESTIONS LITTLE BROTHER?"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "JUST LOOK AFTER THE KID, I PROMISED"); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THAT DEPENDS, I HAVE ONE LAST TARGET FOR YOU.."); 
			} 
			if(index == 3) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "YOU$RE GOING TO DEAL WITH SANG...."); 
			} 
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "BUT HE$S..."); 
			} 
			if(index == 5) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "DON$T FAIL ME... FOR THE KIDS SAKE"); 
			} 
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I WON$T FAIL THE CLAN BOSS"); 
			} 
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "I$LL DEAL WITH YOU LATER LITTLE BROTHER..");
		}

	}


	// Ninth fight against Sang at the courtroom...
	if(scene == 8)  
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I TOLD YOU PUNKS NOT TO COME HERE!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "SAPPORO WANTS YOU OUT SANG...."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "SO HE SENDS HIS LITTLE BROTHER. HAHA!"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WE$RE TAKING BACK THIS TOWN!"); 
			}
			if(index == 4)  
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I OWN THIS TOWN BOY!"); 
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
				sprintf( new_counter[1].word, "W-WELL DONE BOY.. A SUCKER TO THE END"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHAT ARE YOU TALKING ABOUT SANG?"); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "SAPPORO TOOK THE CLAN FROM YOU..."); 
			}
			if(index == 3) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "WHEN HE KILLED YOUR FATHER...HAHA!"); 
			}
			if(index == 4) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "Y-YOUR LYING SANG!"); 
			}
			if(index == 5) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "A-ASK HIM YOURSELF BOY..."); 
			}
			if(index == 6) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "I-IT CAN$T BE TRUE!"); 
			}
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "TELL YOUR BOSS HE$S FINISHED...");
		}

	}

	// Tenth fight against Sapporo at the alleyway...
	if(scene == 9) 
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
				sprintf( new_counter[1].word, "SO YOU$RE STILL HERE SQUIRT?"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "YOU KEPT YOUR PROMISE!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "YOU CAN GO HOME NOW KID.."); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_SAD; 
				sprintf( new_counter[1].word, "WILL YOU TEACH ME THOSE MOVES? "); 
			}
			if(index == 4)  
			{    
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "SURE IF YOUR MOM DOESN$T KICK MY ASS!"); 
			}
			if(index == 5)    
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I$LL BE WAITING MISTER! I BETTER GO!"); 
			}
			if(index == 6)  
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "(IT$S TIME OUR CLAN WENT LEGIT..)"); 
			}
			if(index == 7)   
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "(AND THANKS KID...)"); 
			}
			if(index == 8)   
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "(THE END) THANKS FOR PLAYING!"); 
			}
			if(index == 9) 
			{
				VG_Scene_char = 102; // Cause ending quit...
			} 

		}  
		if(condition == VG_STORY_SCENE_LAST) 
		{
			VG_Scene_char = 3;
			VG_Scene_emotion = VG_EMOTION_HAPPY;
			sprintf( new_counter[1].word, "EVEN THE WORST SITUATION CAN BE OVERCOME"); 
		}
	}

	if(condition == VG_STORY_SCENE_LOST) 
	{
		if(VG_ROUND_CONDITIONS == CONDITION_MUST_ARREST)
			sprintf( new_counter[1].word, "(DAMN! I NEED TO ARREST THEM!)");
		if(VG_ROUND_CONDITIONS == CONDITION_MUST_WASTE)
			sprintf( new_counter[1].word, "(DAMN! I NEED TO WASTE THEM!)");
		if(VG_ROUND_CONDITIONS == CONDITION_TIMED || VG_ROUND_CONDITIONS == CONDITION_TIMED_BASIC)
			sprintf( new_counter[1].word, "(DAMN! I WASN$T FAST ENOUGH!)");
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
				VG_Scene_char = 5;
				VG_Scene_emotion = VG_EMOTION_HAPPY;

				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "WITH THE CITY NOW SAVED..."); 
				else
					sprintf( new_counter[1].word, "WITH SANG DEFEATED THE CLAN TAKES CONTROL!"); 
			}
			if(index == 1) 
			{  
				VG_Scene_char = 5; 
				VG_Scene_emotion = VG_EMOTION_HAPPY;

				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "JAE GOES ON TO BECOME DANCING KING!"); 
				else
					sprintf( new_counter[1].word, "NOT EVEN THE POLICE CAN STOP HIM NOW"); 

			}
			if(index == 2)   
			{  
				VG_Scene_char = 5;
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
					if(VG_CHARACTER_LOCKS[VG_JAE] == 1)
						VG_Scene_char = 102; // Cause ending quit...
					else
					{  
						VG_CHARACTER_LOCKS[VG_JAE] = 1;
						VG_Scene_char = 9; // Sets the bg frame...
						VG_Scene_emotion = VG_EMOTION_HAPPY;
						sprintf( new_counter[1].word, "(SAPPORO IS NOW PLAYABLE!)"); 
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
					if(VG_CHARACTER_LOCKS[VG_JAE] == 1)
						VG_Scene_char = 102; // Cause ending quit...
					else
					{  
						VG_CHARACTER_LOCKS[VG_JAE] = 1;
						VG_Scene_char = 9; // Sets the bg frame...
						VG_Scene_emotion = VG_EMOTION_HAPPY;
						sprintf( new_counter[1].word, "(SAPPORO IS NOW PLAYABLE!)"); 
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
				VG_Scene_char = 5;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "ROUND CLEARED!");
			}
			if(index == 1) 
			{
				VG_Scene_char = 102; // Cause ending quit...
			}
		}
	}

	if(VG_Scene_char != 101 && VG_Scene_char != 102)
		VG_WrapWord(new_counter[1].word, 25, -1);

}

