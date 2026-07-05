/*	

if(character == VG_GYEONG) 
	{
		if(rnd == 0)
			sprintf( new_counter[1].word, "YOU$RE NOT THE ONE WHO MURDERED MY FAMILY... ");  
		if(rnd == 1)
			sprintf( new_counter[1].word, "DID YOU KILL MY WIFE AND DAUGHTER?...NO... "); 
		if(rnd == 2)
			sprintf( new_counter[1].word, "I MUST CONTINUE THE SEARCH FOR MY FAMILIES KILLER"); 
		if(rnd == 3)
			sprintf( new_counter[1].word, "I THINK I MIGHT HAVE GONE TOO FAR THIS TIME..."); 
		if(rnd == 4)
			sprintf( new_counter[1].word, "DAMN! I$M LOW ON SOJU.. COULD YOU LOAN ME SOME WON?"); 
		if(rnd == 5)
			sprintf( new_counter[1].word, "I USED TO BE A TOP DETECTIVE ONCE"); 
		if(rnd == 6)
			sprintf( new_counter[1].word, "CHIA! I WILL AVENGE YOU!"); 
		if(rnd == 7)
			sprintf( new_counter[1].word, "DON$T SUPPOSE YOU GOT A LIGHT?"); 
		if(rnd == 8)
			sprintf( new_counter[1].word, "YOU SHOULD QUIT FIGHTING YOU$LL LIVE LONGER"); 
		if(rnd == 9)
			sprintf( new_counter[1].word, "SORRY...BUT YOU NEVER STOOD A CHANCE"); 
		if(rnd == 10)
			sprintf( new_counter[1].word, "IT$S NOTHING PERSONAL..DON$T LOOK AT ME THAT WAY"); 
		if(rnd == 11)
			sprintf( new_counter[1].word, "I MUST CONTINUE THE HUNT"); 

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "GOOD TO SEE THERE$S SOME GOOD COPS LEFT!");

		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE)
		{
			if(VG_PLAYER1_WON == false) // TOYUN WINS...
				sprintf( new_counter[1].word, "YOU$RE OFF THE CASE GYEONG YOU$VE GONE TOO FAR...");
			if(VG_PLAYER1_WON == true)  // TOYUN LOSES...
				sprintf( new_counter[1].word, "I TOLD YOU TO STAY OUT OF THIS TOYUN...");
		}
	}
	if(character == VG_SIU)
	{
		if(rnd == 0)
			sprintf( new_counter[1].word, "WHEN YOU STOP BREAKING THE LAW I$LL STOP..."); 
		if(rnd == 1)
			sprintf( new_counter[1].word, "I TOLD YOU CRIME DOESN$T PAY!"); 
		if(rnd == 2)
			sprintf( new_counter[1].word, "YOUR FIGHTING SKILLS COULD USE IMPROVEMENT"); 
		if(rnd == 3)
			sprintf( new_counter[1].word, "YOU WON$T BE GOING ANYWHERE FOR AWHILE..."); 
		if(rnd == 4)
			sprintf( new_counter[1].word, "TRY TO STAY OUT OF TROUBLE IN FUTURE"); 
		if(rnd == 5)
			sprintf( new_counter[1].word, "IF I SEE YOU AGAIN I WON$T GO SO EASY"); 
		if(rnd == 6)
			sprintf( new_counter[1].word, "SO? WHO$S NEXT?"); 
		if(rnd == 7)
			sprintf( new_counter[1].word, "THE LAW ALWAYS WINS!"); 
		if(rnd == 8)
			sprintf( new_counter[1].word, "SHOW SOME RESPECT TO AN OFFICER!"); 
		if(rnd == 9)
			sprintf( new_counter[1].word, "YOU JUST FELT THE FIST OF THE LAW"); 
		if(rnd == 10)
			sprintf( new_counter[1].word, "PLEASE CONSIDER OTHERS IN FUTURE"); 
		if(rnd == 11)
			sprintf( new_counter[1].word, "PROTECTING THE PEACE MISSION ACCOMPLISHED"); 

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "I$M GLAD YOU GUYS ARE ON OUR SIDE");

		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE)
		{
			if(VG_PLAYER1_WON == false) // DAE-SU WINS...
				sprintf( new_counter[1].word, "THAT$S FOR WORRYING YOUR MOTHER SIU...");
			if(VG_PLAYER1_WON == true)  // DAE-SU LOSES...
				sprintf( new_counter[1].word, "SORRY DAD BUT THIS IS SOMETHING I HAVE TO DO");
		}
	}
	if(character == VG_MINSO)
	{ 
		if(rnd == 0)
			sprintf( new_counter[1].word, "NEXT TIME PAY YOUR PARKING TICKET PLEASE! ");  
		if(rnd == 1)
			sprintf( new_counter[1].word, "HMMM...I FORGOT TO FEED CHARLIE ");  
		if(rnd == 2)
			sprintf( new_counter[1].word, "I FORGET WHAT I WAS DOING AGAIN? ");  
		if(rnd == 3)
			sprintf( new_counter[1].word, "NOW WHAT WOULD YOUR MOTHER THINK!");  
		if(rnd == 4)
			sprintf( new_counter[1].word, "THINK TWICE NEXT TIME WHEN BREAKING OUR LAWS");  
		if(rnd == 5)
			sprintf( new_counter[1].word, "I HOPE I DIDN$T HURT YOU TOO BADLY?");   
		if(rnd == 6)
			sprintf( new_counter[1].word, "SAY HI TO CHIYU AT THE HOSPITAL FOR ME!");  
		if(rnd == 7)
			sprintf( new_counter[1].word, "CHARLIE IT$S DINNER TIME! WHERE IS THAT DOG?"); 
		if(rnd == 8)
			sprintf( new_counter[1].word, "I ENJOYED OUR WORKOUT! BUT YOU DON$T LOOK SO GOOD");  
		if(rnd == 9)
			sprintf( new_counter[1].word, "YOU SHOULD REALLY TAKE BETTER CARE OF YOURSELF! REALLY!");   
		if(rnd == 10)
			sprintf( new_counter[1].word, "HMMM...I REALLY FANCY KIMCHI TONIGHT, I CAN$T WAIT!");  
		if(rnd == 11)
			sprintf( new_counter[1].word, "CHARLIE! CHARLIE! SORRY I THINK I LOST MY POLICE DOG!?!");  

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "THANKS GRAMPS! IT$S SURE BEEN AWHILE! HEHE..");

		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE)
		{
			if(VG_PLAYER1_WON == false) // MIA WINS...
				sprintf( new_counter[1].word, "YOU$LL NEVER BE AS GOOD AS ME MINSO.");
			if(VG_PLAYER1_WON == true)  // MIA LOSES...
				sprintf( new_counter[1].word, "SEE YOU BACK AT THE PRECINCT MIA!");
		}
	}
	if(character == VG_REESE)
	{
		if(rnd == 0)
			sprintf( new_counter[1].word, "WHAT YOU SAW WAS.. A WEATHER BALLOON...");  
		if(rnd == 1)
			sprintf( new_counter[1].word, "THERE$S NO SUCH THING AS ALIENS...");
		if(rnd == 2)
			sprintf( new_counter[1].word, "YOU NEVER SAW ME...");
		if(rnd == 3)
			sprintf( new_counter[1].word, "THIS COUNTRY IS TOO HOT!");
		if(rnd == 4)
			sprintf( new_counter[1].word, "YOU TRIPPED AND FELL. THAT$S WHAT HAPPENED...");
		if(rnd == 5)
			sprintf( new_counter[1].word, "YOU DIDN$T SEE ME...");
		if(rnd == 6)
			sprintf( new_counter[1].word, "WHAT YOU SAW WAS... SWAMP GAS...");
		if(rnd == 7)
			sprintf( new_counter[1].word, "YOU$VE SEEN TOO MUCH...");
		if(rnd == 8)
			sprintf( new_counter[1].word, "REPEAT AFTER ME... WEATHER BALLOON...");
		if(rnd == 9)
			sprintf( new_counter[1].word, "DON$T TRY TO FOLLOW ME...");
		if(rnd == 10)
			sprintf( new_counter[1].word, "IF YOU SEE ANYTHING $ODD$ CALL US...");
		if(rnd == 11)
			sprintf( new_counter[1].word, "THERE$S NOT MUCH TIME..");

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "FOR AN OLD MAN YOU MOVE PRETTY WELL...");

		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE)
		{
			if(VG_PLAYER1_WON == false) // BOB WINS...
				sprintf( new_counter[1].word, "I TOLD THE BOSS YOU COULDN$T HANDLE THIS.");
			if(VG_PLAYER1_WON == true)  // BOB LOSES...
				sprintf( new_counter[1].word, "STAY OUT OF MY WAY BOB THIS IS MY CASE NOW.");
		}
	} 
	if(character == VG_YOHAN)
	{
		if(rnd == 0)
			sprintf( new_counter[1].word, "I$VE ONLY JUST BEGUN... ");  
		if(rnd == 1)
			sprintf( new_counter[1].word, "LET THE TERROR COMMENCE! ");  
		if(rnd == 2)
			sprintf( new_counter[1].word, "SEE! YOU LOOK MUCH PRETTIER NOW..."); 
		if(rnd == 3)
			sprintf( new_counter[1].word, "ACID DOES WONDERFUL THINGS FOR THE COMPLEXION"); 
		if(rnd == 4)
			sprintf( new_counter[1].word, "WHY SO SAD? "); 
		if(rnd == 5)
			sprintf( new_counter[1].word, "HEHEHE.... "); 
		if(rnd == 6)
			sprintf( new_counter[1].word, "HE WON$T LET ME STOP HE WANTS MORE..."); 
		if(rnd == 7)
			sprintf( new_counter[1].word, "DID I BREAK YOUR FACE? MY APPOLOGY.."); 
		if(rnd == 8)
			sprintf( new_counter[1].word, "I ONLY LIVE TO OBEY HIS COMMAND..."); 
		if(rnd == 9)
			sprintf( new_counter[1].word, "MY LORDS VISION WILL BE MADE REALITY SOON!"); 
		if(rnd == 10)
			sprintf( new_counter[1].word, "I ONLY WANTED TO BLOW SOMETHING UP..."); 
		if(rnd == 11)
			sprintf( new_counter[1].word, "ORDER THROUGH CHAOS! "); 
		 
		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "YOU$RE THE BEST? THE COPS ARE FINISHED...");

		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE)
		{
			if(VG_PLAYER1_WON == false) // SUNG-KI WINS...
				sprintf( new_counter[1].word, "YOU$VE FAILED US. YOU MUST BE PUNISHED...");
			if(VG_PLAYER1_WON == true)  // SUNG-KI LOSES...
				sprintf( new_counter[1].word, "I TOLD YOU I COULD DO THIS MASTER!");
		}
	}
	if(character == VG_JAE)  
	{ 
		if(rnd == 0)
			sprintf( new_counter[1].word, "MY DANCE MOVES ARE JUST TOO HOT FOR YOU...");  
		if(rnd == 1)
			sprintf( new_counter[1].word, "KING OF THE DANCE FLOOR");  
		if(rnd == 2)
			sprintf( new_counter[1].word, "I$M YOUNGER THAN I LOOK REALLY...");
		if(rnd == 3)
			sprintf( new_counter[1].word, "MY SPIN DASH CAN$T BE BEATEN...");  
		if(rnd == 4)
			sprintf( new_counter[1].word, "YOU NEED TO GET WITH THE GROOVE");  
		if(rnd == 5)
			sprintf( new_counter[1].word, "I$M NOT SO BAD ONCE YOU GET TO KNOW ME");
		if(rnd == 6)
			sprintf( new_counter[1].word, "NO, NO, YOUR RHYTHM IS ALL OFF!");  
		if(rnd == 7)
			sprintf( new_counter[1].word, "GET ME SOMEONE WHO CAN DANCE NEXT TIME...");  
		if(rnd == 8)
			sprintf( new_counter[1].word, "WITH MOVES LIKE THOSE? JUST EMBARRASING..");  
		if(rnd == 9)
			sprintf( new_counter[1].word, "EVEN YOUR SENSE OF FASHION IS OFF...");  
		if(rnd == 10)
			sprintf( new_counter[1].word, "I$M AMAZED YOUR STILL STANDING...");  
		if(rnd == 11)
			sprintf( new_counter[1].word, "WAS IT GOOD FOR YOU TOO?");   

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "GIVE IT UP OLD MAN WE RUN THIS CITY NOW!");

		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE) 
		{
			if(VG_PLAYER1_WON == false) // SAPPORO WINS...
				sprintf( new_counter[1].word, "YOUR DASH IS NO MATCH FOR MINE!");
			if(VG_PLAYER1_WON == true)  // SAPPORO LOSES...
				sprintf( new_counter[1].word, "GO BACK TO YOUR WIFE SAPPORO YOU$RE NO MATCH");
		}
	}  
	if(character == VG_GUN)
	{
		if(rnd == 0)
			sprintf( new_counter[1].word, "YOU$LL HAVE TO TRY HARDER TO CATCH ME...");  
		if(rnd == 1)
			sprintf( new_counter[1].word, "TURN MYSELF IN? FORGET IT!");  
		if(rnd == 2)
			sprintf( new_counter[1].word, "YOU HAVE NO IDEA...");  
		if(rnd == 3)
			sprintf( new_counter[1].word, "GOTTA KEEP MOVING...");  
		if(rnd == 4)
			sprintf( new_counter[1].word, "YOU$RE NOT THE ONE WHO SET ME UP!");
		if(rnd == 5)
			sprintf( new_counter[1].word, "SO YOU DON$T KNOW WHO SET ME UP EITHER?");
		if(rnd == 6)
			sprintf( new_counter[1].word, "I WON$T REST UNTIL I FIND WHO SET ME UP!");
		if(rnd == 7)
			sprintf( new_counter[1].word, "I WON$T LET YOU DOWN BOYS");
		if(rnd == 8)
			sprintf( new_counter[1].word, "I$M A HARDENED CRIMINAL WHAT DID YOU EXPECT?");
		if(rnd == 9)
			sprintf( new_counter[1].word, "I GOTTA LOSE THESE CHAINS");
		if(rnd == 10)
			sprintf( new_counter[1].word, "YOU SERIOUSLY THOUGHT YOU COULD STOP ME HUH?");  
		if(rnd == 11)
			sprintf( new_counter[1].word, "I$D KILL YOU NOW, BUT I$M KINDA BUSY");  

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "YOU COPS ARE ALL THE SAME...PATHETIC..");

		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE) 
		{
			if(VG_PLAYER1_WON == false) // KONU WINS...
				sprintf( new_counter[1].word, "THE BOSS WANTS YOUR HEAD GUN. YOU$RE THROUGH...");
			if(VG_PLAYER1_WON == true)  // KONU LOSES...
				sprintf( new_counter[1].word, "YOU CAN TELL THE BOSS HE$S NEXT...");
		}
	}
	if(character == VG_HYUK)
	{
		if(rnd == 0)
			sprintf( new_counter[1].word, "NO, I$M NOT GIVING THAT MONEY BACK..."); 
		if(rnd == 1)
			sprintf( new_counter[1].word, "TIME FOR A VISIT TO THE BANK...HEHE"); 
		if(rnd == 2)
			sprintf( new_counter[1].word, "WHAT MONEY?"); 
		if(rnd == 3)
			sprintf( new_counter[1].word, "NEXT TIME BRING A REAL WEAPON TO THE FIGHT"); 
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
			sprintf( new_counter[1].word, "JUST A FEW MORE JOBS AND I CAN RETIRE"); 
		if(rnd == 10)
			sprintf( new_counter[1].word, "HUH? YOU$RE STILL ALIVE?"); 
		if(rnd == 11)
			sprintf( new_counter[1].word, "GOT ANY CASH? AND I MIGHT LET YOU GO"); 

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "GIVE ME SOME WON AND I$LL LET YOU LIVE!");
		 
		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_GAME_MODE != VG_VERSUS_MODE) 
		{
			if(VG_PLAYER1_WON == false) // YE-JUN WINS...
				sprintf( new_counter[1].word, "HAHA THE GANG IS MINE NOW...");
			if(VG_PLAYER1_WON == true)  // YE-JUN LOSES...
				sprintf( new_counter[1].word, "I$M STILL IN CHARGE AROUND HERE...");
		}
	}
	if(character == VG_SANG)
	{
		if(rnd == 0)
			sprintf( new_counter[1].word, "THIS CITY IS MINE..."); 
		if(rnd == 1)
			sprintf( new_counter[1].word, "YOU CAN$T STOP ME BECOMING PRESIDENT!"); 
		if(rnd == 2)
			sprintf( new_counter[1].word, "THIS CITY IS MINE..."); 
		if(rnd == 3)
			sprintf( new_counter[1].word, "YOU CAN$T STOP ME BECOMING PRESIDENT!"); 
		if(rnd == 4)
			sprintf( new_counter[1].word, "THIS CITY IS MINE..."); 
		if(rnd == 5)
			sprintf( new_counter[1].word, "YOU CAN$T STOP ME BECOMING PRESIDENT!"); 
		if(rnd == 6)
			sprintf( new_counter[1].word, "THIS CITY IS MINE..."); 
		if(rnd == 7)
			sprintf( new_counter[1].word, "YOU CAN$T STOP ME BECOMING PRESIDENT!"); 
		if(rnd == 8)
			sprintf( new_counter[1].word, "THIS CITY IS MINE..."); 
		if(rnd == 9)
			sprintf( new_counter[1].word, "YOU CAN$T STOP ME BECOMING PRESIDENT!"); 
		if(rnd == 10)
			sprintf( new_counter[1].word, "THIS CITY IS MINE..."); 
		if(rnd == 11)
			sprintf( new_counter[1].word, "YOU CAN$T STOP ME BECOMING PRESIDENT!"); 

		if(VG_TRAINING == true)
			sprintf( new_counter[1].word, "WHAT AN OLD FOOL...");
	}
	if(character == VG_TRAINER) 
	{
		if(other_character == VG_GYEONG)
		    sprintf( new_counter[1].word, "FOR A DETECTIVE YOU$RE PRETTY WEAK...");  
		if(other_character == VG_SIU)
		    sprintf( new_counter[1].word, "YOU$LL NEVER MAKE AN OFFICER WITH THOSE MOVES!");  
		if(other_character == VG_MINSO)
		    sprintf( new_counter[1].word, "BAH! TRAFFIC COPS SHOULDN$T FIGHT..");  
		if(other_character == VG_REESE)
		    sprintf( new_counter[1].word, "YOU SHOULD GO BACK TO YOUR HOMELAND STRANGER.");  
		if(other_character == VG_YOHAN)
		    sprintf( new_counter[1].word, "STAY OUT OF TROUBLE KID...");  
		if(other_character == VG_JAE)
		    sprintf( new_counter[1].word, "YOU YAKUZA ARE ALL THE SAME...");  
		if(other_character == VG_GUN)
		    sprintf( new_counter[1].word, "YOU BETTER BEAT IT BEFORE I ARREST YOU.");  
		if(other_character == VG_HYUK)
		    sprintf( new_counter[1].word, "DON$T I KNOW YOU PUNK?"); 
	} 

	if(final_text == 1) 
		sprintf( new_counter[1].word, "WHAT!?! THE ENDINGS ARE COMING SOON! ");

	*/