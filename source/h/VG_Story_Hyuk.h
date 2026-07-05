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

void VG_Help_Story_Hyuk(int scene, int index)
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
	 

	// First fight against Ye-Jun at highway...
	if(scene == 0)   
	{
		sprintf( new_counter[index].word, "WIN ONE ROUND USING^YOUR BASIC PUNCHES AND^KICKS TO WIN!^^PUNCHES^%c or %c^^KICKS^%c or %c", punch, punch2, kick, kick2); 
	}
	if(scene == 1) 
	{
		sprintf( new_counter[index].word, "DEFEAT THE PRISONER^USING YOUR COMBO ATTACK.^ONLY THE COMBO ATTACK WILL^DAMAGE HIM!^^COMBO^%c,%c,%c", kick, kick, kick2);
	}
	if(scene == 2) 
	{
		sprintf( new_counter[index].word, "YOU MUST SURVIVE UNTIL THE^TIMER RUNS OUT!^BE CAREFUL AS YOUR ATTACKS^WILL HAVE NO EFFECT!");
	}
	if(scene == 3) 
	{
		sprintf( new_counter[index].word, "DEFEAT THE SUBWAY COP^USING YOUR MACHINEGUN.^ONLY THE MACHINEGUN WILL^DAMAGE HIM!^^ASSAULT RIFLE^HOLD %c^^RIFLE LOW^HOLD %c", punch2, punch);
	}
	if(scene == 4) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE FOREIGNER^USING WHATEVER MEANS^NECCESSARY!^^RIFLE BUTT^%c,%c + %c^^RIFLE LOW^HOLD %c", right, right, kick, punch);
		else
			sprintf( new_counter[index].word, "DEFEAT THE FOREIGNER^USING WHATEVER MEANS^NECCESSARY!^^RIFLE BUTT^%c,%c,%c + %c^^RIFLE LOW^HOLD %c", down, downright, right, kick, punch);
	}
	if(scene == 5) 
	{
		sprintf( new_counter[index].word, "DEFEAT YE-JUN BEFORE TIME^RUNS OUT!^IF THE TIMER RUNS OUT^YOU$LL LOSE THE FIGHT!^^ASSAULT RIFLE^HOLD %c^^RIFLE LOW^HOLD %c", punch2, punch);
	}
	if(scene == 6) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT YOHAN USING^THE NEW GRENADES AND THROWS.^YOU CAN ONLY DAMAGE HIM^WITH THE GRENADES^OR WITH THROWS^^GRENADE^%c,%c + %c^STICKY GRENADE^PRESS %c", left, right, kick2, throw_key);
		else
			sprintf( new_counter[index].word, "DEFEAT YOHAN USING^THE NEW GRENADES AND THROWS.^YOU CAN ONLY DAMAGE HIM^WITH THE GRENADES^OR WITH THROWS^^GRENADE^%c,%c,%c + %c^STICKY GRENADE^PRESS %c", down, downleft, left, kick2, throw_key);
	}
	if(scene == 7)  
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE YAKUZA^USING WHATEVER MEANS^NECCESSARY!^^ASSAULT RIFLE^HOLD %c^^GRENADE^%c,%c + %c", punch2, left, right, kick2);
		else
			sprintf( new_counter[index].word, "DEFEAT THE YAKUZA^USING WHATEVER MEANS^NECCESSARY!^^ASSAULT RIFLE^HOLD %c^^GRENADE^%c,%c,%c + %c", punch2, down, downleft, left, kick2);
	}
	if(scene == 8) 
	{
		sprintf( new_counter[index].word, "DEFEAT THE YAKUZA BEFORE^TIME RUNS OUT!^IF THE TIMER RUNS OUT^YOU$LL LOSE THE FIGHT!^^ASSAULT RIFLE^HOLD %c^^RIFLE LOW^HOLD %c", punch2, punch);
	}
	if(scene == 9)  
	{
		sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT SANG WITH LOW^HEALTH.^^ASSAULT RIFLE^HOLD %c^^STICKY GRENADE^PRESS %c", punch2, throw_key);
	}
}

void VG_Init_Story_Hyuk(int index, int condition, int scene)
{

	VG_Scene_char = 0;

	// First fight against Ye-jun at the highway...
	if(scene == 0)
	{
		if(condition == VG_STORY_SCENE_SETUP) 
		{

			if(index == 0)
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THIS IS A TOTAL MESS YOU$VE GOT US INTO! "); 
			}
			if(index == 1) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU SAID YOU COULD DRIVE THAT THING! "); 
			}
			if(index == 2)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "WE$VE DECIDED YOU$RE OUT HYUK... "); 
			}
			if(index == 3)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THE MONEY GOES WITH ME..."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHY YOU TWO-TIMING.."); 
			}
			if(index == 5)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "IT$S NOTHING PERSONAL.. HAHA!"); 
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
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "DAMMIT! HE GOT AWAY..."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 11;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "AND WITH MY MONEY..."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 11;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "(YOU$RE UNDER ARREST PUNK! HANDS UP!) "); 
			} 
			if(index == 3) 
			{  
				VG_Scene_char = 11;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "THIS ISN$T GOOD..."); 
			}
			if(index == 4)
			{  
				VG_Scene_char = 11;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "(YOU$LL BE IN PRISON FOR ALONG TIME KID!) "); 
			} 
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}
			 
		} 
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "THE MONEY AND GANG ARE MINE NOW!");
		}

	} 

	// Second fight against Gun in prison...
	if(scene == 1)
	{
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHO LET THE NEW BOY OUT?"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU THINK I$M GONNA ROT IN HERE! "); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "THIS IS MY PRISON BREAK KID..."); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "TOO BAD OLD MAN I$M COMING WITH YOU GUYS!"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "TIME WE TEACHED THIS BRAT A LESSON BOYS"); 
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
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "SEE YOU ON THE OUTSIDE OLD TIMER!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "YOU$VE SURE GOT GUTS BOY... "); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "HAH! WELL GOOD LUCK KID.."); 
			}
			if(index == 3) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "YOU$RE NOT SUCH A BAD GUY AFTER ALL"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I$M COMING FOR YOU YE-JUN, JUST WAIT!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "HAH! YOU$RE STAYING HERE KID..");
		}

	}
	
	// Third fight against Sabu at the dojo...
	if(scene == 2)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I TOLD YOU NOT TO COME HERE HYUK!"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I NEED SOME HARDWARE WHAT$S IN STOCK?"); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU STILL OWE ME MONEY HYUK!"); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I$LL HAVE THE CASH SOON, I SWEAR"); 
			}
			if(index == 4) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "YOU BETTER LEAVE BEFORE SOMEONE SEES..."); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "NOT UNTIL I GET SOME NEW HARDWARE!"); 
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
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "ALRIGHT! ANYTHING TO GET YOU OUT OF HERE..."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "SO WHERE$S THE MERCHANDISE?"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "JUST CAME IN YESTERDAY..."); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 2;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "THIS$LL DO NICELY.."); 
				VG_handcuffs_sfx = true;
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "YOU DIDN$T GET IT FROM ME.."); 
			} 
			if(index == 5)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "DON$T WORRY SABU. I$M GOING...THANKS!"); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "DAMN PUNK KIDS!"); 
			} 
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU NEED TO LEAVE HYUK...");
		}

	}
	
	// Fourth fight against Siu at subway...
	if(scene == 3)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{ 
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "NOW WHERE THE HELL DID YE-JUN GET TO?"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "HOLD IT RIGHT THERE!"); 
			}
			if(index == 2)   
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE ONE OF THE ESCAPED PRISONERS!"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "AH GOOD! I CAN TRY OUT MY NEW TOY"); 
			}
			if(index == 4)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "ARE YOU LISTENING BUDDY!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "NOW HOW DOES THIS THING WORK AGAIN?"); 
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
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "NEXT TIME BRING A REAL GUN TO THE FIGHT"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "YOU WON$T GET AWAY WITH THIS!"); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "AH! THE CLUB! THAT$S WHERE YE-JUN$S HIDING!"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "PROBABLY..."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I$LL TEACH HIM TO STEAL MY MONEY..."); 
			}
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU$RE GOING BACK TO PRISON...");
		}

	}

	// Fifth fight against Bob at the park...
	if(scene == 4)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "ALMOST THERE! I CAN SMELL MY MONEY.."); 
			}
			if(index == 1)  
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "HELLO MA$AM!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "(DAMN FOREIGNERS...)"); 
			}
			if(index == 3)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU..SEY STRANGE PING NEARBY?"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "(CAN$T EVEN SPEAK OUR LANGUAGE...)"); 
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE STARTING TO PISS ME OFF BUDDY!"); 
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
				sprintf( new_counter[1].word, "(SEND IN BACK-UP THESE LOCALS ARE CRAZY)"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YEAH WELCOME TO NEO SEOUL BUDDY..."); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "NOW WHERE WAS I? OH YEAH..."); 
			}
			if(index == 3) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I$M COMING FOR YOU YE-JUN..."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "WE WERE NOT HERE, YES?");
		}

	}


	// Sixth fight against Ye-Jun at the nightclub...
	if(scene == 5)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "HYUK! OLD BUDDY THERE YOU ARE!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "LEMME BUY YOU A D-DRINK!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHERE$S THE MONEY!"); 
			}
			if(index == 3)   
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "COMON! WHAT$S A FEW WON BETWEEN FRIENDS?"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "YOU$VE GOT SOME NERVE YE-JUN..."); 
			}
			if(index == 5)   
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "HEY! DON$T GET MAD.."); 
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
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "NOW WHERE$S THE LOOT!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "I L-LOST IT... AT THE C-CASINO.."); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "HAHA...Y-YOU$RE JOKING RIGHT?"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "THE GAME WAS RIGGED I SWEAR! DAMN YAKUZA.."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "Y-YOU LOST ALL OF IT?"); 
			}
			if(index == 5)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "THEY SWINDLED US OUT OF IT. I SWEAR!"); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THOSE PUNKS DON$T SCARE ME. I NEED THAT MONEY!"); 
			}
			if(index == 7)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "TIME TO PAY AN OLD FRIEND A VISIT..."); 
			}
			if(index == 8)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "HERE$S SOME CHANGE.. NOW BEAT IT HYUK!");
		}

	}


	// Seventh fight against Yohan at the apartment...
	if(scene == 6) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "HYUK! IT$S BEEN AWHILE..."); 
			}
			if(index == 1) 
			{    
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I NEED A FAVOUR OLD FRIEND"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I NEED SOME EXTRA HARDWARE, WHAT YOU GOT?"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "IS THAT SO! I HAVE JUST THE THING"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 2;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I CALL THEM STICKY GRENADES...MY LATEST"); 
				VG_handcuffs_sfx = true;
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "THIS SHOULD TEACH THOSE YAKUZA SCUM!"); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "WHY DON$T WE TRY THEM OUT?..HEHE"); 
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
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "YOU$VE OUTDONE YOURSELF YOHAN.."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "THEY$LL GET THE JOB DONE..."); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HA! TIME TO GET MY MONEY BACK..."); 
			} 
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "HEHE SURE!..DON$T BE A STRANGER"); 
			} 
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU HAVEN$T MASTERED THEM YET! TRY AGAIN!");
		}

	}

	// Eighth fight against Jae at traffic jam...
	if(scene == 7) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "JUST THE YAKUZA SCUM I WAS LOOKING FOR..."); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "..."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I NEED TO TALK TO YOUR BOSS"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I DON$T KNOW WHAT YOU$RE TALKING ABOUT"); 
			}
			if(index == 4) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HE$S GOT SOME MONEY OF MINE..."); 
			}
  		    if(index == 5)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "YOU$LL HAVE TO ASK ME FIRST!"); 
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
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "SO WHERE IS HE?"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "THE BOSS IS IN A MEETING..."); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHERE?"); 
			} 
			if(index == 3) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "D-DOWNTOWN...THE B-BACK ALLEYS..."); 
			} 
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "SEE THAT WASN$T SO HARD WAS IT!"); 
			} 
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "DO YOU REALLY WANT TO MESS WITH US?");
		}

	}


	// Ninth fight against Sapporo at the alleyway...
	if(scene == 8) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHO$S THIS LOSER? YOU WITH THE COPS?"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU SCREWED MY BUDDY OUT OF MY MONEY"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "OH YEAH?"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU$RE GOING TO GIVE IT BACK!"); 
			}
			if(index == 4)  
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "WHO DO YOU THINK YOU ARE PUNK?"); 
			} 
			if(index == 5)  
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "WHY DON$T I SHOW YOU..."); 
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
				sprintf( new_counter[1].word, "I D-DON$T HAVE YOUR MONEY..."); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THEN WHO DOES?"); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "MR S-SANG..HE RUNS THE SHOW AROUND HERE"); 
			}
			if(index == 3) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THAT PUNK POLITICIAN?"); 
			}
			if(index == 4) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "HE$LL BE HERE SOON ASK HIM YOURSELF..."); 
			}
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU DON$T MESS WITH US!");
		}

	}

	// Tenth fight against Sang at the courtroom...
	if(scene == 9) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)  
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "SO YOU$RE BEHIND THAT LITTLE BANK JOB?"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU OWE ME SOME MONEY OLD MAN..."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "NO! YOU OWE ME A CUT. I RUN THIS TOWN"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY; 
				sprintf( new_counter[1].word, "LIKE HELL! I NEED THAT MONEY!"); 
			}
			if(index == 4)  
			{    
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "IT$S RIGHT HERE IN MY BRIEFCASE..."); 
			}
			if(index == 5)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "LET ME GET IT FOR YOU!"); 
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
				sprintf( new_counter[1].word, "HERE T-TAKE YOUR DAMN MONEY..."); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "ALRIGHT! IT$S ALL HERE!"); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "WE$LL HUNT YOU DOWN FOR THIS BOY..."); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "CATCH ME IF YOU CAN OLD TIMER..."); 
			}
			if(index == 4)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "Y-YOU LITTLE P-PUNK!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "LEARN THE HARD WAY BOY...");
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
				sprintf( new_counter[1].word, "HERE$S WHAT I OWE YOU SABU.."); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "HUH! I NEVER THOUGHT YOU$D ACTUALLY PAY"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I CAN SETTLE HER MEDICAL BILLS NOW!"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD; 
				sprintf( new_counter[1].word, "SHES SUFFERED FOR LONG ENOUGH... "); 
			}
			if(index == 4)  
			{    
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "YOUR MOTHER$S A GOOD WOMAN HYUK"); 
			}
			if(index == 5)   
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I KNOW...SHE$LL GET BETTER NOW!"); 
			}
			if(index == 6)  
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "SEE YOU ROUND YOU OLD CROOK!"); 
			}
			if(index == 7)   
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "(THE BOY TURNED OUT ALRIGHT AFTER ALL)"); 
			}
			if(index == 8)   
			{ 
				VG_Scene_char = 1;
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
			VG_Scene_char = 2;
			VG_Scene_emotion = VG_EMOTION_HAPPY;
			sprintf( new_counter[1].word, "NOT EVERYTHING IS WHAT IT SEEMS..."); 
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
				VG_Scene_char = 7;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "WITH SANG$S HIDDEN FUNDS..."); 
				else
					sprintf( new_counter[1].word, "WITH SANG$S HIDDEN FUNDS..."); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 7; 
				VG_Scene_emotion = VG_EMOTION_HAPPY;

				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "HYUK RETIRES A VERY RICH MAN!"); 
				else
					sprintf( new_counter[1].word, "YE-JUN RETIRES A VERY RICH MAN!"); 
			}
			if(index == 2)   
			{  
				VG_Scene_char = 7;
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
					if(VG_CHARACTER_LOCKS[VG_HYUK] == 1)
						VG_Scene_char = 102; // Cause ending quit...
					else
					{  
						VG_CHARACTER_LOCKS[VG_HYUK] = 1;
						VG_Scene_char = 9; // Sets the bg frame...
						VG_Scene_emotion = VG_EMOTION_HAPPY;
						sprintf( new_counter[1].word, "(YE-JUN IS NOW PLAYABLE!)"); 
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
					if(VG_CHARACTER_LOCKS[VG_HYUK] == 1)
						VG_Scene_char = 102; // Cause ending quit...
					else
					{  
						VG_CHARACTER_LOCKS[VG_HYUK] = 1;
						VG_Scene_char = 9; // Sets the bg frame...
						VG_Scene_emotion = VG_EMOTION_HAPPY;
						sprintf( new_counter[1].word, "(YE-JUN IS NOW PLAYABLE!)"); 
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
				VG_Scene_char = 7;
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
			sprintf( new_counter[1].word, "(DAMN! I NEED TO ARREST THEM!)");
		if(VG_ROUND_CONDITIONS == CONDITION_MUST_WASTE)
			sprintf( new_counter[1].word, "(DAMN! I NEED TO WASTE THEM!)");
		if(VG_ROUND_CONDITIONS == CONDITION_TIMED || VG_ROUND_CONDITIONS == CONDITION_TIMED_BASIC)
			sprintf( new_counter[1].word, "(DAMN! I WASN$T FAST ENOUGH!)");
	}

	if(VG_Scene_char != 101 && VG_Scene_char != 102)
		VG_WrapWord(new_counter[1].word, 25, -1);


}

