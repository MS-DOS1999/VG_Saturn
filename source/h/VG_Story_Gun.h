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

void VG_Help_Story_Gun(int scene, int index)
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
	 
	 
	// First fight against Siu at the prison...
	if(scene == 0)   
	{
		sprintf( new_counter[index].word, "WIN ONE ROUND USING^YOUR BASIC PUNCHES AND^KICKS TO WIN!^^PUNCHES^%c or %c^^KICKS^%c or %c", punch, punch2, kick, kick2); 
	}
	if(scene == 1) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT KONU USING^YOUR DASH ATTACKS. ONLY^THE DASH ATTACKS WILL^DAMAGE HIM!^^SLIDE ATTACK^%c,%c + %c^^CANNONBALL^%c,%c + %c", right, right, punch2, right, right, punch);
		else
			sprintf( new_counter[index].word, "DEFEAT KONU USING^YOUR DASH ATTACKS. ONLY^THE DASH ATTACKS WILL^DAMAGE HIM!^^SLIDE ATTACK^%c,%c,%c + %c^^CANNONBALL^%c,%c,%c + %c", down, downright, right, punch2, down, downright, right, punch);
	}
	if(scene == 2) 
	{
		sprintf( new_counter[index].word, "DEFEAT THE DETECTIVE^USING YOUR CLOTHESLINE.^ONLY THE CLOTHESLINE WILL^DAMAGE HIM!^^CLOTHESLINE^HOLD %c", kick2);
	}
	if(scene == 3) 
	{
		sprintf( new_counter[index].word, "DEFEAT THE COP SABU^USING YOUR COMBO ATTACK.^ONLY THE COMBO ATTACK WILL^DAMAGE HIM!^^COMBO^%c,%c,%c,%c", punch2, punch2, punch2, punch2);
	}
	if(scene == 4) 
	{
		sprintf( new_counter[index].word, "WIN ONE ROUND USING^YOUR BACKSTAB AND THROWS.^YOU CAN ONLY DAMAGE HIM^WHEN HE$S DIZZY^OR WITH THROWS^^BACKSTAB - THROW^PRESS %c", throw_key);
	}
	if(scene == 5) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE YAKUZA^USING ANY MEANS^NECESSARY!^^WHIPLASH^%c,%c + %c^^CANNONBALL^%c,%c + %c", left, left, kick2, right, right, punch);
		else
			sprintf( new_counter[index].word, "DEFEAT THE YAKUZA^USING ANY MEANS^NECESSARY!^^WHIPLASH^%c,%c,%c + %c^^CANNONBALL^%c,%c,%c + %c", down, downleft, left, kick2, down, downright, right, punch);
	}
	if(scene == 6) 
	{
		sprintf( new_counter[index].word, "YOU MUST WASTE SAPPORO!^DEFEAT HIM ON THE LAST^ROUND WHEN HE$S DIZZY^HE MUST BE DIZZY^TO WIN!^^DIZZY - THROW^PRESS %c", throw_key);
	}
	if(scene == 7)  
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT KONU WITH LOW^HEALTH.^^CLOTHESLINE^HOLD %c^^CANNONBALL^%c,%c + %c", kick2, right, right, punch);
		else
			sprintf( new_counter[index].word, "YOU$RE STILL WEAK FROM^THE LAST FIGHT. YOU MUST^DEFEAT KONU WITH LOW^HEALTH.^^CLOTHESLINE^HOLD %c^^CANNONBALL^%c,%c,%c + %c", kick2, down, downright, right, punch);
	}
	if(scene == 8) 
	{
		if(VG_P1_USING == VG_KEYBOARD)
			sprintf( new_counter[index].word, "DEFEAT THE CRIME BOSS^BEFORE TIME RUNS OUT!^IF THE TIMER RUNS OUT^YOU$LL LOSE THE FIGHT!^^SLIDE ATTACK^%c,%c + %c^^CANNONBALL^%c,%c + %c", right, right, punch2, right, right, punch);
		else
			sprintf( new_counter[index].word, "DEFEAT THE CRIME BOSS^BEFORE TIME RUNS OUT!^IF THE TIMER RUNS OUT^YOU$LL LOSE THE FIGHT!^^SLIDE ATTACK^%c,%c,%c + %c^^CANNONBALL^%c,%c,%c + %c", down, downright, right, punch2, down, downright, right, punch);
	}
/*	if(scene == 9)  
	{
		sprintf( new_counter[index].word, "YOU MUST WASTE SAPPORO!^DEFEAT HIM ON THE LAST^ROUND WHEN HE$S DIZZY^HE MUST BE DIZZY^TO WIN!^^DIZZY - THROW^%c + %c", punch, punch2);
	}*/
}

void VG_Init_Story_Gun(int index, int condition, int scene)
{

	VG_Scene_char = 0;

	// First fight against Sapporo at the alleyway...
	if(scene == 0)
	{
		if(condition == VG_STORY_SCENE_SETUP) 
		{

			if(index == 0)
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "WE MADE IT THIS FAR BOYS! "); 
			}
			if(index == 1) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "THAT$S FAR ENOUGH COP KILLER.. "); 
			}
			if(index == 2)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "HAH! I NEVER KILLED ANY COP.. "); 
			}
			if(index == 3)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THE JUDGE SAID OTHERWISE GET BACK TO YOUR CELLS!"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "NOT UNTIL I FIND WHO SET ME UP!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "TAKE $EM DOWN BOYS!"); 
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
				sprintf( new_counter[1].word, "DAMN THE PRISONERS ARE ESCAPING..."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "TIME TO PROVE MY INNOCENCE!"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "Y-YOU WON$T GET FAR... "); 
			} 
			if(index == 3) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "ALL I HAVE TO DO IS FIND WHO SET ME UP!"); 
			}
			if(index == 4) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "ENJOY YOUR STAY..COP"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}
			 
		} 
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU$LL BE IN SOLITARY FOR A MONTH!");
		}

	} 

	// Second fight against Konu at the traffic jam...
	if(scene == 1)
	{
		if(condition == VG_STORY_SCENE_SETUP)  
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "ALRIGHT! WE$RE OUT.."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "TIME TO FIND THE PUNK WHO SET US UP! "); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WE$RE NOT COMING WITH YOU GUN..."); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THIS IS MY PRISON BREAK KONU!"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WE WANT NO PART OF YOUR VENDETTA..."); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "SO YOU PLAN TO TAKE OVER?"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_NONE;
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
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "GO YOUR OWN WAY THEN..SEE IF I CARE"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "W-WE$RE NOT GOING BACK TO PRISON GUN "); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I DON$T NEED COWARDS LIKE YOU ANYWAY!"); 
			}
			if(index == 3)  
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "(DAMN I DIDN$T EXPECT THIS....)"); 
			}
			if(index == 4)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "WE$RE NOT FOLLOWING YOU ANYMORE GUN!");
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
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "H-HOW DID YOU GET OUT..."); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "SO THIS IS WHERE HE WAS MURDERED?"); 
			}
			if(index == 2)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU SHOULD KNOW PUNK YOU KILLED HIM!"); 
			}
			if(index == 3)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "DO YOU THINK I$D COME HERE IF I DID?"); 
			}
			if(index == 4) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I HAD MY SUSPICIONS BUT YOU$RE WANTED!"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "SO YOU BELIEVE ME THEN!"); 
			}
			if(index == 6) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "I DON$T KNOW WHAT TO BELIEVE ANYMORE.."); 
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
				sprintf( new_counter[1].word, "I NEVER KILLED YOUR POLICE CHIEF!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "MAYBE...JUST.. MAYBE.."); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHAT DO YOU KNOW?"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "THE COP SABU, I THINK HE$S IMPLEMENTED.."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "YEAH I$VE HEARD OF HIM ONE CROOKED COP.."); 
			}
			if(index == 5)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "JUST TRY TO KEEP OUT OF TROUBLE.."); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I OWE YOU ONE DETECTIVE..."); 
			}
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "I CAN$T LET YOU ESCAPE!");
		}

	}
	
	// Fourth fight against Sabu at the dojo...
	if(scene == 3)
	{ 
		if(condition == VG_STORY_SCENE_SETUP)  
		{ 
			if(index == 0)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I DON$T WANT ANY TROUBLE SON... "); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I$M NOT HERE FOR THAT"); 
			}
			if(index == 2)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOUR CLOTHES SAY OTHERWISE.."); 
			}
			if(index == 3)   
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$M OUT FOR A LITTLE VISIT.."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$M RUNNING A LEGIT SHOW HERE"); 
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU WON$T MIND IF I ASK SOME QUESTIONS THEN?"); 
			}
			if(index == 6)
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I$M NOT HELPING AN ESCAPED CONVICT.."); 
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
				sprintf( new_counter[1].word, "I$M SICK OF YOU PUNKS BEATING ME UP!"); 
			}
			if(index == 1) 
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "DO YOU REMEMBER THE OLD POLICE CHIEF?"); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "O-OF COURSE..HE WAS AN OLD FRIEND"); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "SOMEONE STITCHED ME UP FOR HIS MURDER!"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "ALL I KNOW IS THE CLAN WAS INVOLVED.."); 
			}
			if(index == 5)
			{ 
				VG_Scene_char = 1; 
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "I WARNED THE CHIEF HE WAS IN TROUBLE"); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "TIME TO SEE OUR YAKUZA FRIENDS..."); 
			}
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU$RE UNDER ARREST PUNK!");
		}

	}

	// Fifth fight against Reese at the park...
	if(scene == 4)
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "WHERE$S A YAKUZA WHEN YOU NEED ONE!"); 
			}
			if(index == 1)  
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "HAVE YOU SEEN ANYTHING STRANGE RECENTLY?"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "WHAT ARE YOU BOYS UP TO HERE?"); 
			}
			if(index == 3)  
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "WE$RE GOVERNMENT A-AGENTS..."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "LIKE HELL YOU ARE.."); 
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YOU SAW NOTHING.."); 
			}
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HEY GET BACK HERE!"); 
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
				sprintf( new_counter[1].word, "I R-REALLY HATE THIS CITY..."); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "WELCOME TO OUR COUNTRY NOW WHERE WAS I?"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "IF I WAS YAKUZA SCUM WHERE WOULD I BE?"); 
			}
			if(index == 3) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "T-THE NIGHTCLUB?"); 
			}
			if(index == 4) 
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "YOU$RE RIGHT BALDY! THANKS.."); 
			}
			if(index == 5) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "A-ANYTIME..."); 
			}
			if(index == 6)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "YOU SAW NOTHING HERE..");
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
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "TELL YOUR BOSS I$M HERE TO SEE HIM"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHAT$S WITH THE GET UP? THIS ISN$T FANCY DRESS"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I BROKE OUT OF JAIL THIS MORNING"); 
			}
			if(index == 3)   
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "YEAH SURE..I$M BUSY HERE..."); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "LET ME GET YOUR ATTENTION THEN"); 
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
				sprintf( new_counter[1].word, "YOU$RE IN A WORLD OF TROUBLE PAL"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "GOOD BRING IT ON!"); 
			} 
			if(index == 2) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "LET ME GET THE BOSS FOR YOU.."); 
			}
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "FINE, JUST HURRY IT UP."); 
			}
			if(index == 4) 
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "(WHO THE HELL IS THIS GUY?)"); 
			}
			if(index == 5)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "ESCORT THIS GUY TO THE DOOR!");
		}

	}


	// Seventh fight against Sapporo at the nightclub...
	if(scene == 6) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHERE$S THE IDIOT TEARING UP MY NIGHTCLUB!"); 
			}
			if(index == 1) 
			{     
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "YOU SURE TOOK YOUR SWEET TIME BOSS MAN"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHAT DO YOU WANT OLD TIMER?"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I HEARD YOU KNOW ABOUT THE POLICE CHIEF MURDER"); 
			}
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "WHAT$S IT TO YOU? YOU$RE NO COP LOVER"); 
			}
			if(index == 5)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "I DON$T NEED TO TELL YOU SQUAT"); 
			}
			if(index == 6)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "GOOD! WE$LL DO THIS THE HARD WAY THEN..."); 
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
				sprintf( new_counter[1].word, "A-ALRIGHT YOU WIN!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "WHO KILLED THE CHIEF?"); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "I-I DON$T KNOW WHO BUT SANG ORDERED IT.."); 
			} 
			if(index == 3)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "THAT SLEAZY POLITICIAN?"); 
			} 
			if(index == 4)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "T-THE SAME, COULD YOU EXIT MY CLUB NOW.."); 
			} 
			if(index == 5)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "AND TRY NOT TO BREAK ANYTHING ELSE.."); 
			} 
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$M COMING FOR YOU MR.SANG!"); 
			} 
			if(index == 7)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "GET THIS LOSER OUT OF HERE!");
		}

	}

	// Eighth fight against Konu at the subway...
	if(scene == 7) 
	{ 
		if(condition == VG_STORY_SCENE_SETUP) 
		{
			if(index == 0)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "KONU! YOU CAME BACK TO HELP!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "MR SAPPORO SENT ME..."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "HOW LONG HAVE YOU BEEN WITH THE YAKUZA?"); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "LONG ENOUGH GUN. YOU NEVER WERE TOO BRIGHT."); 
			}
			if(index == 4) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHATEVER..LET ME THROUGH!"); 
			}
  		    if(index == 5)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED;
				sprintf( new_counter[1].word, "YOU JUST DON$T GET IT DO YOU?"); 
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
				sprintf( new_counter[1].word, "HOW COME I CAN NEVER BEAT YOU!"); 
			}
			if(index == 1)
			{ 
				VG_Scene_char = 0; 
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "THAT$S WHY I$M THE BOSS AROUND HERE"); 
			} 
			if(index == 2)
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "EVEN THOUGH IT WAS ME WHO SET YOU UP!"); 
			} 
			if(index == 3) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "HAHA! I KILLED THE POLICE CHIEF!"); 
			} 
			if(index == 4)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_DERP;
				sprintf( new_counter[1].word, "...THAT CAN$T BE TRUE.."); 
			} 
			if(index == 5) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "IT WAS A PLEASURE TO PUT YOU BEHIND BARS"); 
			} 
			if(index == 6)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I ALWAYS KNEW YOU WERE A RAT KONU..."); 
			} 
			if(index == 7)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I THOUGHT I COULD CHANGE YOU. I WAS WRONG."); 
			} 
			if(index == 8) 
			{ 
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "..."); 
			} 
			if(index == 9)
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "I$LL DEAL WITH YOU LATER!"); 
			} 
			if(index == 10)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "IT$S BACK TO PRISON FOR YOU GUN....");
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
				sprintf( new_counter[1].word, "WHAT$S AN ESCAPED CONVICT DOING HERE?"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "YOU$RE THE ONE THAT PUT ME BEHIND BARS.."); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "I$M JUST A SIMPLE POLITICIAN.."); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "OH YEAH! WHAT$S IN THE BRIEFCASE...SANG"); 
			}
			if(index == 4)  
			{   
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "HERE I$LL SHOW YOU!"); 
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
				sprintf( new_counter[1].word, "I-I CAN GIVE YOU ANYTHING YOU WANT!"); 
			}
			if(index == 1)
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "WHY DID YOU KILL THE POLICE CHIEF?"); 
			}
			if(index == 2) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "WE WENT TO LAW SCHOOL TOGETHER.."); 
			}
			if(index == 3) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "I GUESS HE DIDN$T APPROVE OF MY PLANS.."); 
			}
			if(index == 4) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_SAD;
				sprintf( new_counter[1].word, "SO YOU HAD YOUR BEST FRIEND KILLED.."); 
			}
			if(index == 5) 
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "H-HE LEFT ME NO CHOICE..THE FOOL.."); 
			}
			if(index == 6) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$LL SEE YOU ON THE INSIDE SANG..."); 
			}
			if(index == 7) 
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_ANGRY;
				sprintf( new_counter[1].word, "PRISON IS MY TURF YOU$LL ENJOY IT! HAHA!"); 
			}
			if(index == 8)
			{
				VG_Scene_char = 101; // Cause quit...
			}

		}
		if(condition == VG_STORY_SCENE_LOST) 
		{
			sprintf( new_counter[1].word, "SOMEONE ARREST THIS MAN!");
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
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "Y-YOU REALLY TOOK OUT S-SANG!"); 
			}
			if(index == 1) 
			{   
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "HE$LL BE GOING WITH US, BACK TO JAIL"); 
			}
			if(index == 2)
			{  
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN;
				sprintf( new_counter[1].word, "W-WHY YOU$RE CRAZY.."); 
			} 
			if(index == 3)  
			{ 
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_MOTIVATED; 
				sprintf( new_counter[1].word, "WITH YOU I CAN CLEAR MY NAME "); 
			}
			if(index == 4)  
			{    
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I$LL BE OUT IN NO TIME!"); 
			}
			if(index == 5)    
			{
				VG_Scene_char = 1;
				VG_Scene_emotion = VG_EMOTION_PAIN_DERP;
				sprintf( new_counter[1].word, "W-WHAT ABOUT ME? YOUR OLD FRIEND..."); 
			}
			if(index == 6)  
			{
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_NONE;
				sprintf( new_counter[1].word, "I FORGIVE YOU KONU..."); 
			}
			if(index == 7)   
			{  
				VG_Scene_char = 0;
				VG_Scene_emotion = VG_EMOTION_HAPPY;
				sprintf( new_counter[1].word, "EVERYONE DESERVES A SECOND CHANCE. EVEN YOU"); 
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
			VG_Scene_char = 5;
			VG_Scene_emotion = VG_EMOTION_HAPPY;
			sprintf( new_counter[1].word, "THE CYCLE IS BROKEN WITH FORGIVENESS..."); 
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
				VG_Scene_char = 6;
				VG_Scene_emotion = VG_EMOTION_HAPPY;  

				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "GUN MUST SERVE HIS REMAINING SENTENCE..."); 
				else
					sprintf( new_counter[1].word, "WITH SANG DEFEATED KONU LIVES OUT HIS DREAM"); 
			}
			if(index == 1) 
			{  
				VG_Scene_char = 6;  
				VG_Scene_emotion = VG_EMOTION_HAPPY;

				if(VG_IS_AN_ALTER_P1 == false)
					sprintf( new_counter[1].word, "BUT HE HAS SOME NEW PERKS ATLEAST!"); 
				else
					sprintf( new_counter[1].word, "TO BE A SALARYMAN!"); 
			}
			if(index == 2)   
			{  
				VG_Scene_char = 6;
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
					if(VG_CHARACTER_LOCKS[VG_GUN] == 1)
						VG_Scene_char = 102; // Cause ending quit...
					else
					{  
						VG_CHARACTER_LOCKS[VG_GUN] = 1;
						VG_Scene_char = 9; // Sets the bg frame...
						VG_Scene_emotion = VG_EMOTION_HAPPY;
						sprintf( new_counter[1].word, "(KONU IS NOW PLAYABLE!)"); 
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
					if(VG_CHARACTER_LOCKS[VG_GUN] == 1)
						VG_Scene_char = 102; // Cause ending quit...
					else
					{  
						VG_CHARACTER_LOCKS[VG_GUN] = 1;
						VG_Scene_char = 9; // Sets the bg frame...
						VG_Scene_emotion = VG_EMOTION_HAPPY;
						sprintf( new_counter[1].word, "(KONU IS NOW PLAYABLE!)"); 
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
				VG_Scene_char = 6;
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
			sprintf( new_counter[1].word, "(GRRR! I WASN$T FAST ENOUGH!)");
	}

	if(VG_Scene_char != 101 && VG_Scene_char != 102)
		VG_WrapWord(new_counter[1].word, 25, -1);


}

