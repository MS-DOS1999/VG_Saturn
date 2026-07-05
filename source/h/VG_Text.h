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

void VG_WrapWord(char *word, unsigned int line_length, int type)
{
	int next_start = 0;  
	int length = 0; 
	char new_string[1024];  
	int current_position=0;     
	int temp=0;     
	int target=0;  
	int amount=0;
	int first_guy=0;       
	int second_guy=0;     
	int rnd = 0;    
	 
	if(word[0] == ' ')
		return; 

	sprintf( new_string, "%s", word);

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



void VG_Text(int character, int other_character, int final_text)
{
	int rnd=0;

	if(character == VG_GYEONG) 
	{
		rnd = rand()%12;

		if(rnd == 0)
			sprintf( new_counter[1].word, "YOU$RE NOT THE ONE WHO MURDERED CHIA");  
		if(rnd == 1)
			sprintf( new_counter[1].word, "DID YOU KILL MY WIFE AND DAUGHTER?"); 
		if(rnd == 2)
			sprintf( new_counter[1].word, "I WILL FIND MY WIFES KILLER.."); 
		if(rnd == 3)
			sprintf( new_counter[1].word, "I THINK I WENT TOO FAR THIS TIME"); 
		if(rnd == 4)
			sprintf( new_counter[1].word, "DAMN! I$M LOW ON SOJU.."); 
		if(rnd == 5)
			sprintf( new_counter[1].word, "I WAS A TOP DETECTIVE ONCE"); 
		if(rnd == 6)
			sprintf( new_counter[1].word, "CHIA! I WILL AVENGE YOU!"); 
		if(rnd == 7)
			sprintf( new_counter[1].word, "DON$T SUPPOSE YOU HAVE A LIGHT?"); 
		if(rnd == 8)
			sprintf( new_counter[1].word, "QUIT FIGHTING... YOU$LL LIVE LONGER"); 
		if(rnd == 9)
			sprintf( new_counter[1].word, "SORRY...YOU NEVER STOOD A CHANCE"); 
		if(rnd == 10)
			sprintf( new_counter[1].word, "IT$S NOTHING PERSONAL.."); 
		if(rnd == 11)
			sprintf( new_counter[1].word, "I MUST CONTINUE THE HUNT"); 

		if(VG_IS_AN_ALTER_P1 == true)
		{ 
			rnd = rand()%9; 

			if(rnd == 0)
			    sprintf( new_counter[1].word, "I WILL FIND THE CHIEFS KILLER!");
			if(rnd == 1)
			    sprintf( new_counter[1].word, "HOW CAN I FIGHT THIS CORRUPTION!?!");
			if(rnd == 2)
			    sprintf( new_counter[1].word, "WE$RE NOT ALL CORRUPT COPS, YOU KNOW!");
			if(rnd == 3)
			    sprintf( new_counter[1].word, "HOW CAN I DO THIS WITHOUT MY PARTNER...");
			if(rnd == 4)
			    sprintf( new_counter[1].word, "DAMN YOU GYEONG, FOR LEAVING US...");
			if(rnd == 5)
			    sprintf( new_counter[1].word, "THE CORRUPTION ENDS HERE!");
			if(rnd == 6)
			    sprintf( new_counter[1].word, "YOU FOUGHT WELL, BUT I$M A DETECTIVE...");
			if(rnd == 7)
			    sprintf( new_counter[1].word, "THE ACADEMY TRAINED US WELL.. TRY HARDER PUNK!");
			if(rnd == 8)
			    sprintf( new_counter[1].word, "I WILL FIND YOUR KILLER CHIEF!");

		}

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "I KNOW WHO YOU ARE SABU!");

		// Character is fighting against himself...
		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE)
		{
			if(VG_IS_AN_ALTER_P1 == false)
			{
				if(VG_PLAYER1_WON == false) // GYEONG LOSES...
					sprintf( new_counter[1].word, "YOU$RE OFF THE CASE GYEONG...");
				if(VG_PLAYER1_WON == true)  // GYEONG WINS...
					sprintf( new_counter[1].word, "STAY OUT OF THIS TOYUN");
			}
			if(VG_IS_AN_ALTER_P1 == true)
			{
				if(VG_PLAYER1_WON == false) // TOYUN LOSES...
					sprintf( new_counter[1].word, "YOU$RE OFF THE CASE TOYUN...");
				if(VG_PLAYER1_WON == true)  // TOYUN WINS...
					sprintf( new_counter[1].word, "STAY OUT OF THIS GYEONG");
			}
		} 



	} 
	if(character == VG_SIU) 
	{
		rnd = rand()%12;

		if(rnd == 0)
			sprintf( new_counter[1].word, "STOP BREAKING THE LAW"); 
		if(rnd == 1)
			sprintf( new_counter[1].word, "I TOLD YOU CRIME DOESN$T PAY!"); 
		if(rnd == 2)
			sprintf( new_counter[1].word, "YOUR SKILLS COULD USE IMPROVEMENT"); 
		if(rnd == 3)
			sprintf( new_counter[1].word, "YOU$RE NOT GOING ANYWHERE.."); 
		if(rnd == 4)
			sprintf( new_counter[1].word, "STAY OUT OF TROUBLE IN FUTURE"); 
		if(rnd == 5)
			sprintf( new_counter[1].word, "DON$T LET ME SEE YOU AGAIN"); 
		if(rnd == 6)
			sprintf( new_counter[1].word, "SO? WHO$S NEXT?"); 
		if(rnd == 7)
			sprintf( new_counter[1].word, "THE LAW ALWAYS WINS!"); 
		if(rnd == 8)
			sprintf( new_counter[1].word, "SHOW SOME RESPECT FOR AN OFFICER!"); 
		if(rnd == 9)
			sprintf( new_counter[1].word, "YOU JUST FELT THE FIST OF THE LAW"); 
		if(rnd == 10)
			sprintf( new_counter[1].word, "PLEASE CONSIDER OTHERS IN FUTURE"); 
		if(rnd == 11)
			sprintf( new_counter[1].word, "PROTECTING THE PEACE!"); 

		if(VG_IS_AN_ALTER_P1 == true)
		{ 
			rnd = rand()%9; 

			if(rnd == 0)
			    sprintf( new_counter[1].word, "GOOD WORK PIGEON ALLY!");
			if(rnd == 1)
			    sprintf( new_counter[1].word, "NATURE IS A POWERFUL ALLY!");
			if(rnd == 2)
			    sprintf( new_counter[1].word, "YOUR TECHNIQUE IS FAR TOO SLOPPY...");
			if(rnd == 3)
			    sprintf( new_counter[1].word, "I FORGET WHAT I WAS DOING.. OLD AGE HAHA!");
			if(rnd == 4)
			    sprintf( new_counter[1].word, "I WAS QUITE THE LADY$S MAN IN MY YOUTH!");
			if(rnd == 5)
			    sprintf( new_counter[1].word, "THIS SURE BEATS COLLECTING TICKETS!");
			if(rnd == 6)
			    sprintf( new_counter[1].word, "YOU MUST BEND, LIKE THE WIND!");
			if(rnd == 7)
			    sprintf( new_counter[1].word, "TIME TO FEED MY PIGEON ALLY!");
			if(rnd == 8)
			    sprintf( new_counter[1].word, "I HOPE THE TRAINS ARE ON TIME TODAY...");

		} 

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "I$M GLAD YOU GUYS ARE ON OUR SIDE");

		// Character is fighting against himself...
		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE)
		{
			if(VG_IS_AN_ALTER_P1 == false)
			{
				if(VG_PLAYER1_WON == false) // SIU LOSES...
					sprintf( new_counter[1].word, "THAT$S FOR WORRYING YOUR MOTHER");
				if(VG_PLAYER1_WON == true)  // SIU WINS...
					sprintf( new_counter[1].word, "SORRY DAD, THIS IS SOMETHING I MUST DO");
			}
			if(VG_IS_AN_ALTER_P1 == true)
			{
				if(VG_PLAYER1_WON == false) // DAE-SU LOSES...
					sprintf( new_counter[1].word, "SORRY DAD, THIS IS SOMETHING I MUST DO");
				if(VG_PLAYER1_WON == true)  // DAE-SU WINS...
					sprintf( new_counter[1].word, "THAT$S FOR WORRYING YOUR MOTHER");
			}
		}
	}
	if(character == VG_MINSO)
	{ 
		rnd = rand()%12;

		if(rnd == 0)
			sprintf( new_counter[1].word, "NEXT TIME PAY YOUR TICKET PLEASE!");  
		if(rnd == 1)
			sprintf( new_counter[1].word, "HMMM...I FORGOT TO FEED CHARLIE ");  
		if(rnd == 2)
			sprintf( new_counter[1].word, "I FORGET WHAT I WAS DOING AGAIN? ");  
		if(rnd == 3)
			sprintf( new_counter[1].word, "NOW WHAT WOULD YOUR MOTHER THINK!");  
		if(rnd == 4)
			sprintf( new_counter[1].word, "THINK TWICE WHEN BREAKING OUR LAWS");  
		if(rnd == 5)
			sprintf( new_counter[1].word, "I HOPE I DIDN$T HURT YOU?");   
		if(rnd == 6)
			sprintf( new_counter[1].word, "SAY HI TO CHIYU AT THE HOSPITAL!");  
		if(rnd == 7)
			sprintf( new_counter[1].word, "CHARLIE IT$S DINNER TIME! WHERE IS HE?"); 
		if(rnd == 8)
			sprintf( new_counter[1].word, "I ENJOYED OUR WORKOUT!");  
		if(rnd == 9)
			sprintf( new_counter[1].word, "YOU SHOULD TAKE BETTER CARE!");   
		if(rnd == 10)
			sprintf( new_counter[1].word, "HMMM...I REALLY FANCY KIMCHI TONIGHT");  
		if(rnd == 11)
			sprintf( new_counter[1].word, "CHARLIE! I THINK I LOST MY POLICE DOG!?!");  
		 
		if(VG_IS_AN_ALTER_P1 == true) 
		{ 
			rnd = rand()%12; 
			 
			if(rnd == 0)
			    sprintf( new_counter[1].word, "I WILL PROTECT YOU KYUNG!");
			if(rnd == 1)
			    sprintf( new_counter[1].word, "YOU SHOULD KNOW WHEN YOU$RE BEATEN...");
			if(rnd == 2)
			    sprintf( new_counter[1].word, "DID MY BEAUTY DAZZLE YOU?");
			if(rnd == 3)
			    sprintf( new_counter[1].word, "I WASN$T TOP OF MY CLASS FOR NOTHING!");
			if(rnd == 4)
			    sprintf( new_counter[1].word, "I WONDER WHAT THAT AIRHEAD MINSO IS DOING...");
			if(rnd == 5)
			    sprintf( new_counter[1].word, "FIX YOUR FACE.. IT WAS BAD ENOUGH BEFORE..");
			if(rnd == 6)
			    sprintf( new_counter[1].word, "YOU WERE NO CHALLENGE AT ALL!");
			if(rnd == 7)
			    sprintf( new_counter[1].word, "DON$T TAKE THIS PERSONALLY");
			if(rnd == 8)
			    sprintf( new_counter[1].word, "DON$T WASTE MY TIME, LOSER...");
			if(rnd == 9)
			    sprintf( new_counter[1].word, "DON$T MESS WITH A TRAFFIC COP!");
			if(rnd == 10)
			    sprintf( new_counter[1].word, "I$M TOO PRETTY TO WASTE TIME ON YOU!");
			if(rnd == 11)
			    sprintf( new_counter[1].word, "I HOPE KYUNG IS SAFE...");

		}

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "THANKS GRAMPS! IT$S BEEN AWHILE!");

		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE)
		{
			if(VG_IS_AN_ALTER_P1 == false)
			{
				if(VG_PLAYER1_WON == false) // MIA WINS...
					sprintf( new_counter[1].word, "HAVE YOU BEEN SLACKING OFF AGAIN MINSO?");
				if(VG_PLAYER1_WON == true)  // MIA LOSES...
					sprintf( new_counter[1].word, "SEE YOU BACK AT THE PRECINCT MIA!");
			}
			if(VG_IS_AN_ALTER_P1 == true)
			{
				if(VG_PLAYER1_WON == false) // MIA WINS...
					sprintf( new_counter[1].word, "SEE YOU BACK AT THE PRECINCT MIA!");
				if(VG_PLAYER1_WON == true)  // MIA LOSES...
					sprintf( new_counter[1].word, "HAVE YOU BEEN SLACKING OFF AGAIN MINSO?");
			}

		}
	}
	if(character == VG_REESE)
	{
		rnd = rand()%12;

		if(rnd == 0)
			sprintf( new_counter[1].word, "YOU SAW A WEATHER BALLOON..");  
		if(rnd == 1)
			sprintf( new_counter[1].word, "NO, ALIENS DON$T EXIST..");
		if(rnd == 2)
			sprintf( new_counter[1].word, "YOU NEVER SAW ME...");
		if(rnd == 3)
			sprintf( new_counter[1].word, "THIS COUNTRY IS TOO HOT!");
		if(rnd == 4)
			sprintf( new_counter[1].word, "YOU TRIPPED AND FELL..");
		if(rnd == 5)
			sprintf( new_counter[1].word, "YOU DIDN$T SEE ME...");
		if(rnd == 6)
			sprintf( new_counter[1].word, "WHAT YOU SAW WAS.. SWAMP GAS..");
		if(rnd == 7)
			sprintf( new_counter[1].word, "YOU$VE SEEN TOO MUCH...");
		if(rnd == 8)
			sprintf( new_counter[1].word, "REPEAT AFTER ME... WEATHER BALLOON..");
		if(rnd == 9)
			sprintf( new_counter[1].word, "DON$T TRY TO FOLLOW ME...");
		if(rnd == 10)
			sprintf( new_counter[1].word, "IF YOU SEE ANYTHING CALL US..");
		if(rnd == 11)
			sprintf( new_counter[1].word, "THERE$S NOT MUCH TIME..");

		if(VG_IS_AN_ALTER_P1 == true) 
		{ 
			rnd = rand()%9;  

			if(rnd == 0)
			    sprintf( new_counter[1].word, "BOB... IS .. THIRSTY...");
			if(rnd == 1)
			    sprintf( new_counter[1].word, "LITTLE ONE! IS THAT YOU?");
			if(rnd == 2)
			    sprintf( new_counter[1].word, "BOB DOESN$T.. LIKE YOU..");
			if(rnd == 3)
			    sprintf( new_counter[1].word, "NO HUMAN CAN DEFEAT BOB!");
			if(rnd == 4)
			    sprintf( new_counter[1].word, "BOB SAYS YOU NEED MEDICAL ATTENTION..");
			if(rnd == 5)
			    sprintf( new_counter[1].word, "BOB CANNOT BE DEFEATED!");
			if(rnd == 6)
			    sprintf( new_counter[1].word, "I-I SEE IT! T-THE MOTHERSHIP!");
			if(rnd == 7)
			    sprintf( new_counter[1].word, "BOB IS ONE WITH US NOW!");
			if(rnd == 8)
			    sprintf( new_counter[1].word, "JOIN US! JOIN BOB AND I!");

		}

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "FOR AN OLD MAN YOU MOVE FAST");

		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE)
		{
			if(VG_IS_AN_ALTER_P1 == false)
			{
				if(VG_PLAYER1_WON == false) // BOB WINS...
					sprintf( new_counter[1].word, "YOU CAN$T HANDLE THIS..");
				if(VG_PLAYER1_WON == true)  // BOB LOSES...
					sprintf( new_counter[1].word, "STAY OUT OF MY WAY BOB!");
			}
			if(VG_IS_AN_ALTER_P1 == true)
			{
				if(VG_PLAYER1_WON == false) // BOB WINS...
					sprintf( new_counter[1].word, "STAY OUT OF MY WAY BOB!");
				if(VG_PLAYER1_WON == true)  // BOB LOSES...
					sprintf( new_counter[1].word, "YOU CAN$T HANDLE THIS..");
			}


		}
	} 
	if(character == VG_YOHAN)
	{
		rnd = rand()%12;

		if(rnd == 0)
			sprintf( new_counter[1].word, "I$VE ONLY JUST BEGUN... ");  
		if(rnd == 1)
			sprintf( new_counter[1].word, "LET THE TERROR COMMENCE!");  
		if(rnd == 2)
			sprintf( new_counter[1].word, "YOU LOOK MUCH PRETTIER NOW..."); 
		if(rnd == 3)
			sprintf( new_counter[1].word, "LET THE ACID BURN!"); 
		if(rnd == 4)
			sprintf( new_counter[1].word, "WHY SO SAD?"); 
		if(rnd == 5)
			sprintf( new_counter[1].word, "HEHEHE...."); 
		if(rnd == 6)
			sprintf( new_counter[1].word, "HE WON$T LET ME STOP.."); 
		if(rnd == 7)
			sprintf( new_counter[1].word, "DID I BREAK YOUR FACE? MY APPOLOGY"); 
		if(rnd == 8)
			sprintf( new_counter[1].word, "I LIVE TO OBEY HIS COMMAND.."); 
		if(rnd == 9)
			sprintf( new_counter[1].word, "MY LORDS VISION WILL BE REALITY SOON!"); 
		if(rnd == 10)
			sprintf( new_counter[1].word, "I ONLY WANTED TO BLOW SOMETHING UP.."); 
		if(rnd == 11)
			sprintf( new_counter[1].word, "ORDER THROUGH CHAOS!"); 

		if(VG_IS_AN_ALTER_P1 == true)
		{ 
			rnd = rand()%9;  

			if(rnd == 0)
			    sprintf( new_counter[1].word, "LET THE ACID BURN!");
			if(rnd == 1)
			    sprintf( new_counter[1].word, "ORDER THROUGH CHAOS!");
			if(rnd == 2)
			    sprintf( new_counter[1].word, "JOIN OUR RELIGION! REPENT!");
			if(rnd == 3)
			    sprintf( new_counter[1].word, "REPENT! SINNER!");
			if(rnd == 4)
			    sprintf( new_counter[1].word, "MY VISION WILL BE REALITY SOON!");
			if(rnd == 5)
			    sprintf( new_counter[1].word, "LET THE TERROR COMMENCE!");
			if(rnd == 6)
			    sprintf( new_counter[1].word, "YOU FOUGHT WELL, BUT MY FAITH IS STRONG!");
			if(rnd == 7)
			    sprintf( new_counter[1].word, "YOU COULD NOT DEFEAT MY FAITH!");
			if(rnd == 8)
			    sprintf( new_counter[1].word, "MY RELIGION IS THE BEST OF ALL!");

		}
		 
		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "YOU$RE THE BEST? THE COPS ARE DONE..");

		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE)
		{
			if(VG_IS_AN_ALTER_P1 == false)
			{
				if(VG_PLAYER1_WON == false) // SUNG-KI WINS...
					sprintf( new_counter[1].word, "YOU MUST BE PUNISHED..");
				if(VG_PLAYER1_WON == true)  // SUNG-KI LOSES...
					sprintf( new_counter[1].word, "I LIVE TO OBEY YOU MASTER!");
			}
			if(VG_IS_AN_ALTER_P1 == true)
			{
				if(VG_PLAYER1_WON == false) // SUNG-KI WINS...
					sprintf( new_counter[1].word, "I LIVE TO OBEY YOU MASTER!");
				if(VG_PLAYER1_WON == true)  // SUNG-KI LOSES...
					sprintf( new_counter[1].word, "YOU MUST BE PUNISHED..");
			}

		}
	}
	if(character == VG_JAE)  
	{ 
		rnd = rand()%12;

		if(rnd == 0)
			sprintf( new_counter[1].word, "MY DANCE MOVES ARE TOO HOT FOR YOU!");  
		if(rnd == 1)
			sprintf( new_counter[1].word, "KING OF THE DANCE FLOOR");  
		if(rnd == 2)
			sprintf( new_counter[1].word, "I$M YOUNGER THAN I LOOK REALLY..");
		if(rnd == 3)
			sprintf( new_counter[1].word, "MY SPIN DASH CAN$T BE BEATEN..");  
		if(rnd == 4)
			sprintf( new_counter[1].word, "YOU NEED TO GET WITH THE GROOVE");  
		if(rnd == 5)
			sprintf( new_counter[1].word, "I$M NOT SO BAD ONCE YOU KNOW ME");
		if(rnd == 6)
			sprintf( new_counter[1].word, "NO, NO, YOUR RHYTHM IS ALL OFF!");  
		if(rnd == 7)
			sprintf( new_counter[1].word, "GET ME SOMEONE WHO CAN DANCE..");  
		if(rnd == 8)
			sprintf( new_counter[1].word, "MOVES LIKE THOSE? JUST EMBARRASING..");  
		if(rnd == 9)
			sprintf( new_counter[1].word, "EVEN YOUR SENSE OF FASHION IS OFF...");  
		if(rnd == 10)
			sprintf( new_counter[1].word, "I$M AMAZED YOU$RE STILL STANDING...");  
		if(rnd == 11)
			sprintf( new_counter[1].word, "WAS IT GOOD FOR YOU TOO?");   

		if(VG_IS_AN_ALTER_P1 == true)  
		{ 
			rnd = rand()%9; 

			if(rnd == 0)
			    sprintf( new_counter[1].word, "THAT$S WHAT YOU GET FOR STANDING UP TO US!");
			if(rnd == 1)
			    sprintf( new_counter[1].word, "YOU REALLY THOUGHT YOU COULD BEAT THE CLAN?");
			if(rnd == 2)
			    sprintf( new_counter[1].word, "CLASS IS OVER.. PUNK");
			if(rnd == 3)
			    sprintf( new_counter[1].word, "YOU$RE A FOOL TO STAND UP TO US!");
			if(rnd == 4)
			    sprintf( new_counter[1].word, "THE CLAN FORGIVES NO-ONE!");
			if(rnd == 5)
			    sprintf( new_counter[1].word, "I$LL BE PAYING A VISIT TO YOUR FAMILY NEXT!");
			if(rnd == 6)
			    sprintf( new_counter[1].word, "I HOPE YOU HAVE LIFE INSURANCE..");
			if(rnd == 7)
			    sprintf( new_counter[1].word, "WE OWN THIS CITY!");
			if(rnd == 8)
			    sprintf( new_counter[1].word, "TAKE THIS IDIOT TO THE LOCKER BOYS!");

		}

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "GIVE IT UP! WE RUN THIS CITY NOW!");

		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE) 
		{
			if(VG_IS_AN_ALTER_P1 == false)
			{
				if(VG_PLAYER1_WON == false) // SAPPORO WINS...
					sprintf( new_counter[1].word, "YOUR DASH IS NO MATCH FOR MINE!");
				if(VG_PLAYER1_WON == true)  // SAPPORO LOSES...
					sprintf( new_counter[1].word, "FOR THE CLAN...");
			}
			if(VG_IS_AN_ALTER_P1 == true)
			{
				if(VG_PLAYER1_WON == false) // SAPPORO WINS...
					sprintf( new_counter[1].word, "FOR THE CLAN...");
				if(VG_PLAYER1_WON == true)  // SAPPORO LOSES...
					sprintf( new_counter[1].word, "YOUR DASH IS NO MATCH FOR MINE!");
			}

		}
	}  
	if(character == VG_GUN)
	{
		rnd = rand()%12;

		if(rnd == 0)
			sprintf( new_counter[1].word, "YOU$LL NEVER CATCH ME..");  
		if(rnd == 1)
			sprintf( new_counter[1].word, "TURN MYSELF IN? FORGET IT!");  
		if(rnd == 2)
			sprintf( new_counter[1].word, "YOU HAVE NO IDEA...");  
		if(rnd == 3)
			sprintf( new_counter[1].word, "GOTTA KEEP MOVING...");  
		if(rnd == 4)
			sprintf( new_counter[1].word, "YOU$RE NOT THE ONE WHO SET ME UP!");
		if(rnd == 5)
			sprintf( new_counter[1].word, "YOU DON$T KNOW WHO SET ME UP EITHER?");
		if(rnd == 6)
			sprintf( new_counter[1].word, "WHEN I FIND THE GUY THAT SET ME UP..");
		if(rnd == 7)
			sprintf( new_counter[1].word, "I WON$T LET YOU DOWN BOYS");
		if(rnd == 8)
			sprintf( new_counter[1].word, "I$M A HARDENED CRIMINAL YOU KNOW");
		if(rnd == 9)
			sprintf( new_counter[1].word, "I GOTTA LOSE THESE CHAINS");
		if(rnd == 10)
			sprintf( new_counter[1].word, "YOU SERIOUSLY THOUGHT YOU COULD STOP ME?");  
		if(rnd == 11)
			sprintf( new_counter[1].word, "I$D KILL YOU NOW, BUT I$M KINDA BUSY");  
	
		if(VG_IS_AN_ALTER_P1 == true) 
		{ 
			rnd = rand()%9; 

			if(rnd == 0)
			    sprintf( new_counter[1].word, "I$M NOT GOING BACK TO PRISON!");
			if(rnd == 1)
			    sprintf( new_counter[1].word, "YOU CAN REALLY TAKE A BEATING CAN$T YOU!");
			if(rnd == 2)
			    sprintf( new_counter[1].word, "TRY BLOCKING NEXT TIME, FOOL");
			if(rnd == 3)
			    sprintf( new_counter[1].word, "TIME TO MAKE MY ESCAPE!");
			if(rnd == 4)
			    sprintf( new_counter[1].word, "JUST ONE MORE LITTLE JOB TO DO!");
			if(rnd == 5)
			    sprintf( new_counter[1].word, "YOU FIGHT LIKE AN OLD LADY...");
			if(rnd == 6)
			    sprintf( new_counter[1].word, "WHAT A LET DOWN.. TRY HARDER!");
			if(rnd == 7)
			    sprintf( new_counter[1].word, "YOU WOULDN$T LAST A SECOND INSIDE...");
			if(rnd == 8)
			    sprintf( new_counter[1].word, "TRY HITTING ME NEXT TIME, FOOL..");

		}

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "YOU COPS ARE ALL THE SAME...PATHETIC..");


		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE) 
		{
			if(VG_IS_AN_ALTER_P1 == false)
			{
				if(VG_PLAYER1_WON == false) // KONU WINS...
					sprintf( new_counter[1].word, "THE BOSS WANTS YOUR HEAD GUN");
				if(VG_PLAYER1_WON == true)  // KONU LOSES...
					sprintf( new_counter[1].word, "YOU CAN TELL THE BOSS HE$S NEXT..");
			}
			if(VG_IS_AN_ALTER_P1 == true)
			{
				if(VG_PLAYER1_WON == false) // KONU WINS...
					sprintf( new_counter[1].word, "YOU CAN TELL THE BOSS HE$S NEXT..");
				if(VG_PLAYER1_WON == true)  // KONU LOSES...
					sprintf( new_counter[1].word, "THE BOSS WANTS YOUR HEAD GUN");
			}
			

		}
	}
	if(character == VG_KENNEDY)
	{
		rnd = rand()%12;

		if(rnd == 0)
			sprintf( new_counter[1].word, "YOU$LL NEVER CATCH ME..");  
		if(rnd == 1)
			sprintf( new_counter[1].word, "TURN MYSELF IN? FORGET IT!");  
		if(rnd == 2)
			sprintf( new_counter[1].word, "YOU HAVE NO IDEA...");  
		if(rnd == 3)
			sprintf( new_counter[1].word, "GOTTA KEEP MOVING...");  
		if(rnd == 4)
			sprintf( new_counter[1].word, "YOU$RE NOT THE ONE WHO SET ME UP!");
		if(rnd == 5)
			sprintf( new_counter[1].word, "YOU DON$T KNOW WHO SET ME UP EITHER?");
		if(rnd == 6)
			sprintf( new_counter[1].word, "WHEN I FIND THE GUY THAT SET ME UP..");
		if(rnd == 7)
			sprintf( new_counter[1].word, "I WON$T LET YOU DOWN BOYS");
		if(rnd == 8)
			sprintf( new_counter[1].word, "I$M A HARDENED CRIMINAL YOU KNOW");
		if(rnd == 9)
			sprintf( new_counter[1].word, "I GOTTA LOSE THESE CHAINS");
		if(rnd == 10)
			sprintf( new_counter[1].word, "YOU SERIOUSLY THOUGHT YOU COULD STOP ME?");  
		if(rnd == 11)
			sprintf( new_counter[1].word, "I$D KILL YOU NOW, BUT I$M KINDA BUSY");  
	
		if(VG_IS_AN_ALTER_P1 == true) 
		{ 
			rnd = rand()%9; 

			if(rnd == 0)
			    sprintf( new_counter[1].word, "I$M NOT GOING BACK TO PRISON!");
			if(rnd == 1)
			    sprintf( new_counter[1].word, "YOU CAN REALLY TAKE A BEATING CAN$T YOU!");
			if(rnd == 2)
			    sprintf( new_counter[1].word, "TRY BLOCKING NEXT TIME, FOOL");
			if(rnd == 3)
			    sprintf( new_counter[1].word, "TIME TO MAKE MY ESCAPE!");
			if(rnd == 4)
			    sprintf( new_counter[1].word, "JUST ONE MORE LITTLE JOB TO DO!");
			if(rnd == 5)
			    sprintf( new_counter[1].word, "YOU FIGHT LIKE AN OLD LADY...");
			if(rnd == 6)
			    sprintf( new_counter[1].word, "WHAT A LET DOWN.. TRY HARDER!");
			if(rnd == 7)
			    sprintf( new_counter[1].word, "YOU WOULDN$T LAST A SECOND INSIDE...");
			if(rnd == 8)
			    sprintf( new_counter[1].word, "TRY HITTING ME NEXT TIME, FOOL..");

		}

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "YOU COPS ARE ALL THE SAME...PATHETIC..");


		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE) 
		{
			if(VG_IS_AN_ALTER_P1 == false)
			{
				if(VG_PLAYER1_WON == false) // KONU WINS...
					sprintf( new_counter[1].word, "THE BOSS WANTS YOUR HEAD GUN");
				if(VG_PLAYER1_WON == true)  // KONU LOSES...
					sprintf( new_counter[1].word, "YOU CAN TELL THE BOSS HE$S NEXT..");
			}
			if(VG_IS_AN_ALTER_P1 == true)
			{
				if(VG_PLAYER1_WON == false) // KONU WINS...
					sprintf( new_counter[1].word, "YOU CAN TELL THE BOSS HE$S NEXT..");
				if(VG_PLAYER1_WON == true)  // KONU LOSES...
					sprintf( new_counter[1].word, "THE BOSS WANTS YOUR HEAD GUN");
			}
			

		}
	}
	if(character == VG_HYUK)
	{
		rnd = rand()%12;

		if(rnd == 0)
			sprintf( new_counter[1].word, "NO, I$M NOT GIVING THAT MONEY BACK.."); 
		if(rnd == 1)
			sprintf( new_counter[1].word, "TIME FOR A VISIT TO THE BANK...HEHE"); 
		if(rnd == 2)
			sprintf( new_counter[1].word, "THAT MONEY BELONGS TO ME!"); 
		if(rnd == 3)
			sprintf( new_counter[1].word, "NEXT TIME BRING A REAL GUN!"); 
		if(rnd == 4)
			sprintf( new_counter[1].word, "YOU$RE LUCKY I$M IN A HURRY..."); 
		if(rnd == 5)
			sprintf( new_counter[1].word, "IT$S JUST NOT YOUR DAY IS IT?"); 
		if(rnd == 6)
			sprintf( new_counter[1].word, "TIME TO MAKE A WITHDRAWAL..."); 
		if(rnd == 7)
			sprintf( new_counter[1].word, "WHO SAYS CRIME DOESN$T PAY?"); 
		if(rnd == 8)
			sprintf( new_counter[1].word, "IT$S NOT ENOUGH I NEED MORE MONEY!"); 
		if(rnd == 9)
			sprintf( new_counter[1].word, "A FEW MORE JOBS AND I CAN RETIRE"); 
		if(rnd == 10)
			sprintf( new_counter[1].word, "HUH? YOU$RE STILL ALIVE?"); 
		if(rnd == 11)
			sprintf( new_counter[1].word, "GOT ANY CASH? I MIGHT LET YOU GO"); 

		if(VG_IS_AN_ALTER_P1 == true)
		{ 
			rnd = rand()%9; 

			if(rnd == 0)
			    sprintf( new_counter[1].word, "NOW GIVE ME ALL YOUR MONEY!");
			if(rnd == 1)
			    sprintf( new_counter[1].word, "HAND OVER YOUR CASH.. RIGHT NOW!");
			if(rnd == 2)
			    sprintf( new_counter[1].word, "YOU$RE A MESS... WHAT A JOKE...");
			if(rnd == 3)
			    sprintf( new_counter[1].word, "TIME TO MAKE MY GETAWAY!");
			if(rnd == 4)
			    sprintf( new_counter[1].word, "HEY! YOU GOT BLOOD ON MY SHIRT!");
			if(rnd == 5)
			    sprintf( new_counter[1].word, "YOU$VE HAD ENOUGH LOSER...");
			if(rnd == 6)
			    sprintf( new_counter[1].word, "YOU SHOULD THANK ME.. FOR MY LESSON..");
			if(rnd == 7)
			    sprintf( new_counter[1].word, "LOSERS LIKE YOU SHOULDN$T FIGHT!");
			if(rnd == 8)
			    sprintf( new_counter[1].word, "TIME TO GIVE ME ALL YOUR MONEY!");

		}

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "GIVE ME SOME WON AND YOU CAN LIVE");
		 
		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE) 
		{
			if(VG_IS_AN_ALTER_P1 == false)
			{
				if(VG_PLAYER1_WON == false) // YE-JUN WINS...
					sprintf( new_counter[1].word, "HAHA THE GANG IS MINE NOW...");
				if(VG_PLAYER1_WON == true)  // YE-JUN LOSES...
					sprintf( new_counter[1].word, "I$M STILL IN CHARGE AROUND HERE..");
			}
			if(VG_IS_AN_ALTER_P1 == true)
			{
				if(VG_PLAYER1_WON == false) // YE-JUN WINS...
					sprintf( new_counter[1].word, "I$M STILL IN CHARGE AROUND HERE..");
				if(VG_PLAYER1_WON == true)  // YE-JUN LOSES...
					sprintf( new_counter[1].word, "HAHA THE GANG IS MINE NOW...");
			}

		}
	}
	if(character == VG_SANG)
	{
		rnd = rand()%12;

		if(rnd == 0)
			sprintf( new_counter[1].word, "THIS CITY IS MINE..."); 
		if(rnd == 1)
			sprintf( new_counter[1].word, "YOU CAN$T STOP ME BECOMING PRESIDENT!"); 
		if(rnd == 2)
			sprintf( new_counter[1].word, "WITH MY CURSED HENCHMEN I CANNOT LOSE!"); 
		if(rnd == 3)
			sprintf( new_counter[1].word, "I$M MUCH MORE THAN A POLITICIAN, FOOL."); 
		if(rnd == 4)
			sprintf( new_counter[1].word, "THE POLICE WORK FOR ME NOW!"); 
		if(rnd == 5)
			sprintf( new_counter[1].word, "I WILL BECOME PRESIDENT!"); 
		if(rnd == 6)
			sprintf( new_counter[1].word, "SO SORRY. DID THAT HURT?"); 
		if(rnd == 7)
			sprintf( new_counter[1].word, "YOU SHOULD HAVE JOINED ME..INSTEAD DIE!"); 
		if(rnd == 8)
			sprintf( new_counter[1].word, "WITH THE CURSED STONE I$M UNSTOPPABLE!"); 
		if(rnd == 9)
			sprintf( new_counter[1].word, "REMEMBER TO VOTE FOR SANG.. HA HA"); 
		if(rnd == 10)
			sprintf( new_counter[1].word, "THE VOTES ARE IN, YOU$RE FINISHED.."); 
		if(rnd == 11)
			sprintf( new_counter[1].word, "I HOPE YOUR FAMILY ARE SAFE...HA HA.."); 

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "WHAT AN OLD FOOL...");
	}
	if(character == VG_TRAINER) 
	{
		if(other_character == VG_GYEONG)
		    sprintf( new_counter[1].word, "FOR A DETECTIVE YOU$RE PRETTY WEAK...");  
		if(other_character == VG_SIU)
		    sprintf( new_counter[1].word, "YOU$LL NEVER MAKE AN OFFICER!");  
		if(other_character == VG_MINSO)
		    sprintf( new_counter[1].word, "BAH! TRAFFIC COPS SHOULDN$T FIGHT..");  
		if(other_character == VG_REESE)
		    sprintf( new_counter[1].word, "GO BACK TO YOUR HOMELAND STRANGER.");  
		if(other_character == VG_YOHAN)
		    sprintf( new_counter[1].word, "STAY OUT OF TROUBLE KID...");  
		if(other_character == VG_JAE)
		    sprintf( new_counter[1].word, "YOU YAKUZA ARE ALL THE SAME...");  
		if(other_character == VG_GUN)
		    sprintf( new_counter[1].word, "BEAT IT BEFORE I ARREST YOU.");  
		if(other_character == VG_HYUK)
		    sprintf( new_counter[1].word, "DON$T I KNOW YOU PUNK?"); 
	} 
	if (character == VG_SHO)
	{
		rnd = rand() % 12;

		if (rnd == 0)
			sprintf(new_counter[1].word, "YOU CAN$T HANDLE MY FIRE");
		if (rnd == 1)
			sprintf(new_counter[1].word, "I M-MUST PROTECT S-SANG...");
		if (rnd == 2)
			sprintf(new_counter[1].word, "M-MUST F-FIGHT...");
		if (rnd == 3)
			sprintf(new_counter[1].word, "M-MUST FIGHT THE C-CURSE... ARGH!");
		if (rnd == 4)
			sprintf(new_counter[1].word, "FIRE BEATS WATER AND YOU!");
		if (rnd == 5)
			sprintf(new_counter[1].word, "MY FLAMEKICK WINS EVERYTIME.");
		if (rnd == 6)
			sprintf(new_counter[1].word, "M-MUST R-REACH MR.SANG..");
		if (rnd == 7)
			sprintf(new_counter[1].word, "YOU$VE BEEN BURNED MY FRIEND.");
		if (rnd == 8)
			sprintf(new_counter[1].word, "M-MY HEAD IT HURTS...ARGHH..");
		if (rnd == 9)
			sprintf(new_counter[1].word, "Y-YES MR.SANG. I WILL OBEY!");
		if (rnd == 10)
			sprintf(new_counter[1].word, "H-HE CALLS ME...M-MUST FIGHT IT!");
		if (rnd == 11)
			sprintf(new_counter[1].word, "NOTHING CAN STOP MY FIRE!");

		if (VG_TRAINING == true)
			sprintf(new_counter[1].word, "WHO$S IN CHARGE HERE?");

	}
	if (character == VG_TIA)
	{
		rnd = rand() % 12;

		if (rnd == 0)
			sprintf(new_counter[1].word, "GOODBYE, I WON$T FORGET YOU");
		if (rnd == 1)
			sprintf(new_counter[1].word, "I FEEL HIM C-CALLING. I M-MUST GO NOW.");
		if (rnd == 2)
			sprintf(new_counter[1].word, "YOU WILL NOT HURT MR.SANG!");
		if (rnd == 3)
			sprintf(new_counter[1].word, "I F-FEEL DIZZY. WHAT IS HAPPENING?");
		if (rnd == 4)
			sprintf(new_counter[1].word, "I M-MUST P-PROTECT MR.SANG...");
		if (rnd == 5)
			sprintf(new_counter[1].word, "I WILL FIND MY BROTHER!");
		if (rnd == 6)
			sprintf(new_counter[1].word, "BROTHER! WHERE ARE YOU?");
		if (rnd == 7)
			sprintf(new_counter[1].word, "I WILL NOT BE DEFEATED BY YOU!");
		if (rnd == 8)
			sprintf(new_counter[1].word, "I$M SORRY. I HAVE TO PROTECT HIM..");
		if (rnd == 9)
			sprintf(new_counter[1].word, "Y-YES MR.SANG. I WILL OBEY..");
		if (rnd == 10)
			sprintf(new_counter[1].word, "THE CURSE! I M-MUST FIGHT IT...");
		if (rnd == 11)
			sprintf(new_counter[1].word, "YOU FOUGHT WELL. BUT I AM STRONGER.");

		if (VG_TRAINING == true)
			sprintf(new_counter[1].word, "I HAVE TO WIN, FOR MY BROTHER");
	}
	if (character == VG_SAIZO)
	{
		rnd = rand() % 12;

		if (rnd == 0)
			sprintf(new_counter[1].word, "OUR CLAN CANNOT BE DEFEATED.");
		if (rnd == 1)
			sprintf(new_counter[1].word, "YOU GOT NO PERSISTENCE!");
		if (rnd == 2)
			sprintf(new_counter[1].word, "...");
		if (rnd == 3)
			sprintf(new_counter[1].word, "NINJA$S ASSEMBLE!");
		if (rnd == 4)
			sprintf(new_counter[1].word, "EAGLE COME!");
		if (rnd == 5)
			sprintf(new_counter[1].word, "MY SPIRITUAL POWERS ARE TO STRONG FOR YOU.");
		if (rnd == 6)
			sprintf(new_counter[1].word, "YOU ARE LUCKY I AM IN A HURRY.");
		if (rnd == 7)
			sprintf(new_counter[1].word, "I WILL PROTECT OUR CLIENT.");
		if (rnd == 8)
			sprintf(new_counter[1].word, "YOU CANNOT DEFEAT THE CLAN.");
		if (rnd == 9)
			sprintf(new_counter[1].word, "YOU ALMOST PUT UP A FIGHT.");
		if (rnd == 10)
			sprintf(new_counter[1].word, "..W-WHAT IS T-THIS FEELING!?!");
		if (rnd == 11)
			sprintf(new_counter[1].word, "YES MR.SANG. WE WILL OBEY.");

		if (VG_TRAINING == true)
			sprintf(new_counter[1].word, "WHO$S IN CHARGE HERE?");
	}
	if(character == VG_KENNEDY) 
	{
		rnd = rand() % 12;

		if (rnd == 0)
			sprintf(new_counter[1].word, "WHERE$S MY MICROPHONE!");
		if (rnd == 1)
			sprintf(new_counter[1].word, "KEN ANNNDEERRSSOON!");
		if (rnd == 2)
			sprintf(new_counter[1].word, "YOU JUST MET A LEGEND..");
		if (rnd == 3)
			sprintf(new_counter[1].word, "WEREN$T YOU LUCKY I CAME TO TOWN.");
		if (rnd == 4)
			sprintf(new_counter[1].word, "MY FOOT HURTS FROM KICKING YOUR FACE.");
		if (rnd == 5)
			sprintf(new_counter[1].word, "THANKS FOR THE WARM-UP.");
		if (rnd == 6)
			sprintf(new_counter[1].word, "YOU ARE LUCKY I AM IN A HURRY.");
		if (rnd == 7)
			sprintf(new_counter[1].word, "NOBODY REMEMBERS SECOND PLACE.");
		if (rnd == 8)
			sprintf(new_counter[1].word, "I$VE GOT A TOURNAMENT TO WIN.");
		if (rnd == 9)
			sprintf(new_counter[1].word, "KEN! REMEMBER THE NAME.");
		if (rnd == 10)
			sprintf(new_counter[1].word, "DID YOU STEAL MY MICROPHONE?");
		if (rnd == 11)
			sprintf(new_counter[1].word, "WHICH WAY IS THE TOURNAMENT?");

		if (VG_TRAINING == true)
			sprintf(new_counter[1].word, "YOU SHOULD BE TEACHING WRESTLING..");
	} 

	if(final_text == 1) 
		sprintf( new_counter[1].word, "WHAT!?! THE ENDINGS ARE COMING SOON! ");
	
	VG_WrapWord(new_counter[1].word, 25, -1);

	if(VG_GAME_MODE == VG_STORY_MODE)
	{
		if(VG_1_CHARACTER == VG_MINSO)
			VG_Init_Story_Minso(0, VG_STORY_SCENE_LOST, VG_CURRENT_STORY_SCENE);
		if(VG_1_CHARACTER == VG_GYEONG)
			VG_Init_Story_Gyeong(0, VG_STORY_SCENE_LOST, VG_CURRENT_STORY_SCENE);
		if(VG_1_CHARACTER == VG_HYUK)
			VG_Init_Story_Hyuk(0, VG_STORY_SCENE_LOST, VG_CURRENT_STORY_SCENE);
		if(VG_1_CHARACTER == VG_JAE)
			VG_Init_Story_Jae(0, VG_STORY_SCENE_LOST, VG_CURRENT_STORY_SCENE);

		if(VG_1_CHARACTER == VG_REESE)
			VG_Init_Story_Reese(0, VG_STORY_SCENE_LOST, VG_CURRENT_STORY_SCENE);
		if(VG_1_CHARACTER == VG_SIU)
			VG_Init_Story_Siu(0, VG_STORY_SCENE_LOST, VG_CURRENT_STORY_SCENE);
		if(VG_1_CHARACTER == VG_YOHAN)
			VG_Init_Story_Yohan(0, VG_STORY_SCENE_LOST, VG_CURRENT_STORY_SCENE);
		if(VG_1_CHARACTER == VG_GUN)
			VG_Init_Story_Gun(0, VG_STORY_SCENE_LOST, VG_CURRENT_STORY_SCENE);
	}

}

void VG_Moveslist(int counter, int character, int index, int player)
{
	char string_value[1024];
	int rnd = 0;
	char punch;
	char punch2;
	char kick;
	char kick2;
	char left;
	char right;
	char down;
	char up;
	char downleft;
	char downright;
	char upleft;
	char upright;
	char throw_key;
	int VG_PLAYER_USING = VG_KEYBOARD;
	bool is_alter = false;

	down = '§';
	up = '¦';

	downleft = '¯';
	downright = '²';

	upleft = '³';
	upright = '¹';

	if(player == 1)
	{
		VG_PLAYER_USING = VG_P1_USING;

		if(VG_PLAYER_USING == VG_KEYBOARD)
		{
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
		if(VG_PLAYER_USING == VG_CONTROLLER)
		{
			left = '¢';
			right = '¤';
			punch  = 'ù'; // ÷ - A
			punch2 = 'ú'; // ø - B
			kick   = '÷'; // ù - X 
			kick2  = 'ø'; // ú - Y
			throw_key = '»';
		}

		if(VG_IS_AN_ALTER_P1 == true)
			is_alter = true;

	} 
	if(player == 2)
	{ 
		VG_PLAYER_USING = VG_P2_USING;

		if(VG_PLAYER_USING == VG_KEYBOARD)
		{
		//	left = VG_P2_LEFT_KEY_DSY;
		//	right = VG_P2_RIGHT_KEY_DSY;
			left = '¢';
			right = '¤';
			punch  = VG_P2_PUNCH1_KEY_DSY;
			punch2 = VG_P2_PUNCH2_KEY_DSY;
			kick   = VG_P2_KICK1_KEY_DSY;
			kick2  = VG_P2_KICK2_KEY_DSY;
			throw_key = VG_P2_THROW_KEY_DSY;
		}
		if(VG_PLAYER_USING == VG_CONTROLLER)
		{
			left = '¢';
			right = '¤';
			punch  = 'ù'; // ÷ - A
			punch2 = 'ú'; // ø - B
			kick   = '÷'; // ù - X 
			kick2  = 'ø'; // ú - Y
			throw_key = '»';
		} 

		if(VG_IS_AN_ALTER == true)
			is_alter = true;
	}
	// £  ¥  À  Á
	// Z  X  C  V

	// Reset the string...
	sprintf( new_counter[counter].word, " ");

	if(VG_GAME_MODE == VG_STORY_MODE)
	{
		if(index == 0) 
		{
			sprintf( new_counter[counter].word, "PUNCHES^%c or %c", punch, punch2); // £
		}
		if(index == 1) 
		{
			sprintf( new_counter[counter].word, "KICKS^%c or %c", kick, kick2); // £
		}
		if(index == 2) 
		{
			sprintf( new_counter[counter].word, "HOLD BACK^TO BLOCK", punch, punch2); // £
		}


	}
	if(VG_GAME_MODE != VG_STORY_MODE)
	{

	if(character == VG_GYEONG)    
	{
		if(index == -1) 
			rnd = rand()%6; 
		else 
			rnd = index;   
		 
		if(rnd == 0)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "TORPEDO^%c,%c + %c", right, right, kick); // £
		else
			sprintf( new_counter[counter].word, "TORPEDO^%c,%c + %c", right, right, kick); // £

		if(rnd == 1)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "PISTOL^%c,%c + %c", left, right, punch2); // £
		else
			sprintf( new_counter[counter].word, "PISTOL^%c,%c,%c + %c", down, downleft, left, punch2); // £

		if(rnd == 2)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "PISTOL LOW^%c,%c + %c", left, right, punch); // ¥
		else
			sprintf( new_counter[counter].word, "PISTOL LOW^%c,%c,%c + %c", down, downleft, left, punch); // £

		if(rnd == 3)
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c", punch, punch, punch2); // À

		if(rnd == 4)
		if(VG_MOVES_VS == false)
			sprintf( new_counter[counter].word, "HANDCUFFS^PRESS %c", throw_key); // À
		else
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c", punch, punch, punch2); // À

		if(rnd == 5)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "UPPERCUT^%c,%c + %c", left, left, kick2); // kick
		else
			sprintf( new_counter[counter].word, "UPPERCUT^%c,%c,%c + %c", down, downleft, left, kick2); // kick

		if(VG_MOVES_VS == true)
		{ 
			sprintf(string_value,"^HANDCUFFS^PRESS %c", throw_key);
			strcat(new_counter[counter].word, string_value);
		}

	} 
	if(character == VG_SIU)  
	{  
		if(index == -1)  
			rnd = rand()%6; 
		else 
			rnd = index;   

		if(rnd == 0)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "PISTOL^%c,%c + %c", left, right, punch2); // £
		else
			sprintf( new_counter[counter].word, "PISTOL^%c,%c,%c + %c", down, downleft, left, punch2); // £

		if(rnd == 1)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "PISTOL LOW^%c,%c + %c", left, right, punch); // ¥
		else
			sprintf( new_counter[counter].word, "PISTOL LOW^%c,%c,%c + %c", down, downleft, left, punch); // £
		 
		if(rnd == 2)
			sprintf( new_counter[counter].word, "PIGEON^HOLD %c", kick2); // kick
		if(rnd == 3)
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c,%c", kick2, kick2, kick2, kick2); // À

		if(rnd == 4)
		if(VG_MOVES_VS == false)
			sprintf( new_counter[counter].word, "HANDCUFFS^PRESS %c", throw_key); // À
		else
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c,%c", kick2, kick2, kick2, kick2); // À

		if(rnd == 5)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "TRIP^%c,%c + %c", right, right, kick); // kick
		else
			sprintf( new_counter[counter].word, "TRIP^%c,%c,%c + %c", down, downright, right, kick); // kick

		if(VG_MOVES_VS == true)
		{ 
			sprintf(string_value,"^HANDCUFFS^PRESS %c", throw_key);
			strcat(new_counter[counter].word, string_value);
		}
	}
	if(character == VG_MINSO)  
	{   
		if(index == -1) 
			rnd = rand()%6;  
		else  
			rnd = index; 
		 
		if(rnd == 0)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "TAZER HIGH^%c,%c + %c", right, right, punch2); // punch
		else
			sprintf( new_counter[counter].word, "TAZER HIGH^%c,%c,%c + %c", down, downright, right, punch2); // punch

		if(rnd == 1)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "TAZER LOW^%c,%c + %c", right, right, punch); // kick
		else
			sprintf( new_counter[counter].word, "TAZER LOW^%c,%c,%c + %c", down, downright, right, punch); // kick

		if(rnd == 2)
		{
			if(is_alter == false)
				sprintf( new_counter[counter].word, "CHARLIE^HOLD %c", punch); // kick
			else
				sprintf( new_counter[counter].word, "MAX^HOLD %c", punch); // kick
		}
		if(rnd == 3)
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c", punch, punch, kick); // punch, punch, kick 

		if(rnd == 4)
		if(VG_MOVES_VS == false)
			sprintf( new_counter[counter].word, "HANDCUFFS^PRESS %c", throw_key); // À
		else
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c", punch, punch, kick); // punch, punch, kick 

		if(rnd == 5) 
		if(VG_PLAYER_USING == VG_KEYBOARD)  
			sprintf( new_counter[counter].word, "PANTY SHOT^%c + HOLD %c", upright, kick2); // kick
		else
			sprintf( new_counter[counter].word, "PANTY SHOT^%c + HOLD %c", upright, kick2); // kick

		if(VG_MOVES_VS == true)
		{ 
			sprintf(string_value,"^HANDCUFFS^PRESS %c", throw_key);
			strcat(new_counter[counter].word, string_value);
		}

	}
	if(character == VG_REESE)  
	{
		if(index == -1)
			rnd = rand()%7;
		else
			rnd = index;

		if(rnd == 0)
		if(VG_PLAYER_USING == VG_KEYBOARD) 
			sprintf( new_counter[counter].word, "STRETCH^%c,%c + %c", right, right, punch2); // punch
		else
			sprintf( new_counter[counter].word, "STRETCH^%c,%c,%c + %c", down, downright, right, punch2); // punch

		if(rnd == 1)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "STRETCH LOW^%c,%c + %c", right, right, punch); // punch2
		else
			sprintf( new_counter[counter].word, "STRETCH LOW^%c,%c,%c + %c", down, downright, right, punch); // punch

		if(rnd == 2)
			sprintf( new_counter[counter].word, "ELECTRIC^HOLD %c", kick); // kick
		if(rnd == 3)
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c", kick2, kick2, punch2); // kick2, kick2,punch

		if(rnd == 4)
		if(VG_MOVES_VS == false)
			sprintf( new_counter[counter].word, "HANDCUFFS^PRESS %c", throw_key); // À
		else
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c", kick2, kick2, punch2); // kick2, kick2,punch

		if(rnd == 5)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "POWER ORB^%c,%c + %c", left, right, punch2); // £
		else
			sprintf( new_counter[counter].word, "POWER ORB^%c,%c,%c + %c", down, downleft, left, punch2); // £

		if(rnd == 6)
			sprintf( new_counter[counter].word, "DEFLECT^HOLD %c", kick2); // kick

		if(VG_MOVES_VS == true)
		{ 
			sprintf(string_value,"^HANDCUFFS^PRESS %c", throw_key);
			strcat(new_counter[counter].word, string_value);
		}

	}
	if(character == VG_YOHAN) 
	{ 
		if(index == -1) 
			rnd = rand()%7;
		else
			rnd = index;

		if(rnd == 0)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "ACID VIAL^%c,%c + %c", right, right, punch2); // punch
		else
			sprintf( new_counter[counter].word, "ACID VIAL^%c,%c,%c + %c", down, downright, right, punch2); // punch

		if(rnd == 1)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "ACID LOW^%c,%c + %c", right, right, punch); // punch2
		else
			sprintf( new_counter[counter].word, "ACID LOW^%c,%c,%c + %c", down, downright, right, punch); // punch

		if(rnd == 2)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "BOMB DROP^%c,%c + %c", left, left, kick2); // punch, punch, punch2
		else
			sprintf( new_counter[counter].word, "BOMB DROP^%c,%c,%c + %c", down, downleft, left, kick2); // punch

		if(rnd == 3)
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c", punch, punch, punch2); // punch, punch, punch2

		if(rnd == 4)
		if(VG_MOVES_VS == false)
			sprintf( new_counter[counter].word, "THROW^PRESS %c", throw_key); // À
		else
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c", punch, punch, punch2); // punch, punch, punch2

		if(rnd == 5)
			sprintf( new_counter[counter].word, "SUICIDE^HOLD %c", punch2); // kick

		if(rnd == 6)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "SLIDE^%c,%c + %c", right, right, kick); // kick
		else
			sprintf( new_counter[counter].word, "SLIDE^%c,%c,%c + %c", down, downright, right, kick); // kick

		if(VG_MOVES_VS == true)
		{ 
			sprintf(string_value,"^THROW^PRESS %c", throw_key);
			strcat(new_counter[counter].word, string_value);
		}

	}
	if(character == VG_JAE)   
	{ 
		if(index == -1) 
			rnd = rand()%6;  
		else
			rnd = index;
		if(rnd == 0)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "DEFLECT^%c,%c or %c,%c", left, left, right, right); 
		else
			sprintf( new_counter[counter].word, "DEFLECT^%c,%c, or %c,%c,", left, left, right, right); 

		if(rnd == 1)
			sprintf( new_counter[counter].word, "MACHINEGUN^HOLD %c", punch); // punch 

		if(rnd == 2)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "BREAKDANCE^%c,%c + %c", right, left, kick); // punch 
		else
			sprintf( new_counter[counter].word, "BREAKDANCE^%c,%c,%c + %c", down, downleft, left, kick); // punch
		if(rnd == 3)
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c", punch, punch, kick); // punch, punch, kick

		if(rnd == 4)
		if(VG_MOVES_VS == false)
			sprintf( new_counter[counter].word, "THROW^PRESS %c", throw_key); // À
		else
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c", punch, punch, kick); // punch, punch, kick

		if(rnd == 5) 
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "MAD DASH^%c,%c + %c", left, right, kick2); // kick
		else
			sprintf( new_counter[counter].word, "MAD DASH^%c,%c,%c + %c", down, downright, right, kick2); // kick

		if(VG_MOVES_VS == true)
		{ 
			sprintf(string_value,"^THROW^PRESS %c", throw_key);
			strcat(new_counter[counter].word, string_value);
		}
	}
	if(character == VG_GUN) 
	{ 
		if(index == -1) 
			rnd = rand()%6;  
		else 
			rnd = index;
		if(rnd == 0)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "SLIDE^%c,%c + %c", right, right, punch2); // punch 
		else
			sprintf( new_counter[counter].word, "SLIDE^%c,%c,%c + %c", down, downright, right, punch2); // punch

		if(rnd == 1)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "CANNONBALL^%c,%c + %c", right, right, punch); // kick
		else
			sprintf( new_counter[counter].word, "CANNONBALL^%c,%c,%c + %c", down, downright, right, punch); // punch

		if(rnd == 2)
			sprintf( new_counter[counter].word, "CLOTHESLINE^HOLD %c", kick2); // kick		if(rnd == 3)
		if(rnd == 3)
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c,%c", punch2, punch2, punch2, punch2); // punch2, punch2, punch2, punch2

		if(rnd == 4)
		if(VG_MOVES_VS == false)
			sprintf( new_counter[counter].word, "THROW^PRESS %c", throw_key); // À
		else
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c,%c", punch2, punch2, punch2, punch2); // punch2, punch2, punch2, punch2

		if(rnd == 5)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "WHIPLASH^%c,%c + %c", left, left, kick2); // kick
		else
			sprintf( new_counter[counter].word, "WHIPLASH^%c,%c,%c + %c", down, downleft, left, kick2); // kick

		if(VG_MOVES_VS == true)
		{ 
			sprintf(string_value,"^THROW^PRESS %c", throw_key);
			strcat(new_counter[counter].word, string_value);
		}

	}
	if(character == VG_HYUK)
	{   
		if(index == -1)
			rnd = rand()%6;  
		else  
			rnd = index; 
		if(rnd == 0)
			sprintf( new_counter[counter].word, "RIFLE^HOLD %c", punch2); // punch
		if(rnd == 1)
			sprintf( new_counter[counter].word, "RIFLE LOW^HOLD %c", punch); // punch2
		if(rnd == 2)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "GRENADE^%c,%c + %c", left, right, kick2); // kick
		else
			sprintf( new_counter[counter].word, "GRENADE^%c,%c,%c + %c", down, downleft, left, kick2); // punch

		if(rnd == 3)
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c", kick, kick, kick2); // kick, kick, kick2

		if(rnd == 4)
		if(VG_MOVES_VS == false)
			sprintf( new_counter[counter].word, "THROW^PRESS %c", throw_key); // À
		else
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c", kick, kick, kick2); // kick, kick, kick2

		if(rnd == 5)  
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "RIFLE BUTT^%c,%c + %c", right, right, kick); // kick
		else
			sprintf( new_counter[counter].word, "RIFLE BUTT^%c,%c,%c + %c", down, downright, right, kick); // kick

		if(VG_MOVES_VS == true)
		{ 
			sprintf(string_value,"^THROW^PRESS %c", throw_key);
			strcat(new_counter[counter].word, string_value);
		}
	}

	if (character == VG_SHO)
	{
		if (index == -1)
			rnd = rand() % 6;
		else
			rnd = index;

		if (rnd == 0)
			if (VG_PLAYER_USING == VG_KEYBOARD)
				sprintf(new_counter[counter].word, "SLIDE^%c,%c + %c", right, right, kick); // £
			else
				sprintf(new_counter[counter].word, "SLIDE^%c,%c,%c + %c", down, downright, right, kick); // kick

		if (rnd == 1)
			if (VG_PLAYER_USING == VG_KEYBOARD)
				sprintf(new_counter[counter].word, "FLAMEKICK^%c,%c + %c", left, left, kick); // ¥
			else
				sprintf(new_counter[counter].word, "FLAMEKICK^%c,%c,%c + %c", down, downleft, left, kick); // kick

		if (rnd == 2)
		if (VG_PLAYER_USING == VG_KEYBOARD)
			sprintf(new_counter[counter].word, "FIREBALL^%c,%c + %c", right, right, punch2); // ¥
		else
			sprintf(new_counter[counter].word, "FIREBALL^%c,%c,%c + %c", down, downright, right, punch2); // kick

		if (rnd == 3)
			sprintf(new_counter[counter].word, "COMBO1^%c,%c,%c", punch, punch, punch2); // À

		if (rnd == 4)
			if (VG_MOVES_VS == false)
				sprintf(new_counter[counter].word, "HANDCUFFS^PRESS %c", throw_key); // À
			else
				sprintf(new_counter[counter].word, "COMBO1^%c,%c,%c", punch, punch, punch2); // À

		if (rnd == 5)
		if (VG_PLAYER_USING == VG_KEYBOARD)
			sprintf(new_counter[counter].word, "FIREBALL^%c,%c + %c", right, right, punch2); // ¥
		else
			sprintf(new_counter[counter].word, "FIREBALL^%c,%c,%c + %c", down, downright, right, punch2); // kick

		if (VG_MOVES_VS == true)
		{
			sprintf(string_value, "^HANDCUFFS^PRESS %c", throw_key);
			strcat(new_counter[counter].word, string_value);
		}
	}
	if (character == VG_TIA)
	{
		if (index == -1)
			rnd = rand() % 6;
		else
			rnd = index;

		if (rnd == 0)
			if (VG_PLAYER_USING == VG_KEYBOARD)
				sprintf(new_counter[counter].word, "SLIDE^%c,%c + %c", left, left, kick); // punch
			else
				sprintf(new_counter[counter].word, "SLIDE^%c,%c,%c + %c", down, downleft, left, kick); // kick

		if (rnd == 1)
			if (VG_PLAYER_USING == VG_KEYBOARD)
				sprintf(new_counter[counter].word, "UPPERCUT^%c,%c + %c", left, left, punch2); // kick
			else
				sprintf(new_counter[counter].word, "UPPERCUT^%c,%c,%c + %c", down, downleft, left, punch2); // kick
		 
		if (rnd == 2)
		{
			if (is_alter == false)
				sprintf(new_counter[counter].word, "FIREBALL^%c,%c + %c", left, right, punch2); // ¥
			else
				sprintf(new_counter[counter].word, "FIREBALL^%c,%c,%c + %c", down, downright, right, punch2); // kick
		}
		if (rnd == 3)
			sprintf(new_counter[counter].word, "COMBO1^%c,%c,%c", punch, punch, kick); // punch, punch, kick 

		if (rnd == 4)
			if (VG_MOVES_VS == false)
				sprintf(new_counter[counter].word, "HANDCUFFS^PRESS %c", throw_key); // À
			else
				sprintf(new_counter[counter].word, "COMBO1^%c,%c,%c", punch, punch, kick); // punch, punch, kick 

		if (rnd == 5)
			if (VG_PLAYER_USING == VG_KEYBOARD)
				sprintf(new_counter[counter].word, "FIREBALL^%c,%c + %c", left, right, punch2); // ¥
			else
				sprintf(new_counter[counter].word, "FIREBALL^%c,%c,%c + %c", down, downright, right, punch2); // kick

		if (VG_MOVES_VS == true)
		{
			sprintf(string_value, "^HANDCUFFS^PRESS %c", throw_key);
			strcat(new_counter[counter].word, string_value);
		}


	}

	if (character == VG_SAIZO)
	{
		if (index == -1)
			rnd = rand() % 6;
		else
			rnd = index;

		if (rnd == 0)
			if (VG_PLAYER_USING == VG_KEYBOARD)
				sprintf( new_counter[counter].word, "EAGLE^HOLD %c", punch2); // kick
			else
				sprintf( new_counter[counter].word, "EAGLE^HOLD %c", punch2); // kick

		if (rnd == 1)
		if (VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "BOMB^%c,%c + %c", left, right, kick2); // kick
		else
			sprintf( new_counter[counter].word, "BOMB^%c,%c,%c + %c", down, downleft, left, kick2); // punch

		if (rnd == 2)
		if (VG_PLAYER_USING == VG_KEYBOARD)
			sprintf(new_counter[counter].word, "KUNAI^%c,%c + %c", left, right, punch2); // ¥
		else
			sprintf(new_counter[counter].word, "KUNAI^%c,%c,%c + %c", down, downright, right, punch2); // kick

		if (rnd == 3)
			sprintf(new_counter[counter].word, "COMBO1^%c,%c,%c", punch, punch, punch2); // À

		if (rnd == 4)
			if (VG_MOVES_VS == false)
				sprintf(new_counter[counter].word, "HANDCUFFS^PRESS %c", throw_key); // À
			else
				sprintf(new_counter[counter].word, "COMBO1^%c,%c,%c", punch, punch, punch2); // À

		/*if (rnd == 5)
		if (VG_PLAYER_USING == VG_KEYBOARD)
			sprintf(new_counter[counter].word, "KUNAI^%c,%c + %c", left, right, punch2); // ¥
		else
			sprintf(new_counter[counter].word, "KUNAI^%c,%c,%c + %c", down, downright, right, punch2); // kick*/

		if (VG_MOVES_VS == true)
		{
			sprintf(string_value, "^HANDCUFFS^PRESS %c", throw_key);
			strcat(new_counter[counter].word, string_value);
		}
	}

	if(character == VG_SANG)  
	{  
		if(index == -1)  
			rnd = rand()%6; 
		else 
			rnd = index;   

		if(rnd == 0)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "FLAME^%c,%c + %c", left, right, kick); // £
		else
			sprintf( new_counter[counter].word, "FLAME^%c,%c + %c", left, right, kick); // £

		if(rnd == 1)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "MACHINEGUN^HOLD %c", punch); // punch 
		else
			sprintf( new_counter[counter].word, "MACHINEGUN^HOLD %c", punch); // punch 
		 
		if(rnd == 2)
			sprintf( new_counter[counter].word, "MACHINEGUN2^HOLD %c", punch2); // punch 
		if(rnd == 3)
			sprintf( new_counter[counter].word, "MACHINEGUN2^HOLD %c", punch2); // punch 

		if(rnd == 4)
		if(VG_MOVES_VS == false)
			sprintf( new_counter[counter].word, "HANDCUFFS^PRESS %c", throw_key); // À
		else
			sprintf( new_counter[counter].word, "HANDCUFFS^PRESS %c", throw_key); // À

		if(rnd == 5)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "FLAME^%c,%c + %c", left, right, kick); // £
		else
			sprintf( new_counter[counter].word, "FLAME^%c,%c + %c", left, right, kick); // £

		if(VG_MOVES_VS == true)
		{ 
			sprintf(string_value,"^HANDCUFFS^PRESS %c", throw_key);
			strcat(new_counter[counter].word, string_value);
		}
	}
	if(character == VG_KENNEDY) 
	{ 
		if(index == -1) 
			rnd = rand()%6;  
		else 
			rnd = index;
		if(rnd == 0)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "FLAMEKICK^%c,%c + %c", right, right, punch2); // punch 
		else
			sprintf( new_counter[counter].word, "FLAMEKICK^%c,%c,%c + %c", down, downright, right, punch2); // punch

		if(rnd == 1)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "SLIDE^%c,%c + %c", right, right, punch); // kick
		else
			sprintf( new_counter[counter].word, "SLIDE^%c,%c,%c + %c", down, downright, right, punch); // punch

		if(rnd == 2)
			sprintf( new_counter[counter].word, "LARIAT^HOLD %c", kick2); // kick		if(rnd == 3)
		if(rnd == 3)
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c,%c", punch2, punch2, punch2, punch2); // punch2, punch2, punch2, punch2

		if(rnd == 4)
		if(VG_MOVES_VS == false)
			sprintf( new_counter[counter].word, "THROW^PRESS %c", throw_key); // À
		else
			sprintf( new_counter[counter].word, "COMBO1^%c,%c,%c,%c", punch2, punch2, punch2, punch2); // punch2, punch2, punch2, punch2

		if(rnd == 5)
		if(VG_PLAYER_USING == VG_KEYBOARD)
			sprintf( new_counter[counter].word, "X-SLASH^%c,%c + %c", left, left, kick2); // kick
		else
			sprintf( new_counter[counter].word, "X-SLASH^%c,%c,%c + %c", down, downleft, left, kick2); // kick

		if(VG_MOVES_VS == true)
		{ 
			sprintf(string_value,"^THROW^PRESS %c", throw_key);
			strcat(new_counter[counter].word, string_value);
		}

	}

	// End of moves list




	}

}