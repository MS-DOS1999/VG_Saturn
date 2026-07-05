#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h" 
#include "VG_globals.h"  
 
#if defined WIN32 || defined WIN64 
#define WIN32_LEAN_AND_MEAN   
#include <windows.h>  
#endif     

/*extern bool LoadKeys();
extern bool SaveKeys();  

void VG_Put_Temps_Into_Keys();
void VG_Put_Keys_Into_Temps();
void VG_Put_Keys_Into_Temps();

void VG_Get_Keys() 
{

	VG_P1_UP_KEY=VK_UP;
	VG_P1_DOWN_KEY=VK_DOWN;
	VG_P1_LEFT_KEY=VK_LEFT; 
	VG_P1_RIGHT_KEY=VK_RIGHT;   

	VG_P1_PUNCH1_KEY='A'; 
	VG_P1_PUNCH2_KEY='S'; 
	VG_P1_KICK1_KEY='Z';
	VG_P1_KICK2_KEY='X'; 
	VG_P1_BLOCK_KEY='D';
	VG_P1_THROW_KEY='C'; 
	  
	VG_P2_UP_KEY='I';
	VG_P2_DOWN_KEY='K'; 
	VG_P2_LEFT_KEY='J'; 
	VG_P2_RIGHT_KEY='L'; 

	VG_P2_PUNCH1_KEY='R';
	VG_P2_PUNCH2_KEY='T';
	VG_P2_KICK1_KEY='F';
	VG_P2_KICK2_KEY='G';
	VG_P2_BLOCK_KEY='Y';
	VG_P2_THROW_KEY='H'; 
	 
	if(LoadKeys() == false)
	{
		VG_P1_UP_KEY=VK_UP;
		VG_P1_DOWN_KEY=VK_DOWN; 
		VG_P1_LEFT_KEY=VK_LEFT; 
		VG_P1_RIGHT_KEY=VK_RIGHT;   

		VG_P1_PUNCH1_KEY='A'; 
		VG_P1_PUNCH2_KEY='S'; 
		VG_P1_KICK1_KEY='Z';
		VG_P1_KICK2_KEY='X'; 
		VG_P1_BLOCK_KEY='D';
		VG_P1_THROW_KEY='C'; 
	  
		VG_P2_UP_KEY='I';
		VG_P2_DOWN_KEY='K';  
		VG_P2_LEFT_KEY='J'; 
		VG_P2_RIGHT_KEY='L'; 

		VG_P2_PUNCH1_KEY='R';
		VG_P2_PUNCH2_KEY='T';
		VG_P2_KICK1_KEY='F';
		VG_P2_KICK2_KEY='G';
		VG_P2_BLOCK_KEY='Y';
		VG_P2_THROW_KEY='H'; 
		 
		VG_Put_Keys_Into_Temps();
		VG_Put_Temps_Into_Keys();
	}

}

void VG_Put_Temps_Into_Keys()
{
	int kick_key = 0;
	int test_key = 0;
	int stored_key;
	char display_key;

	for(int i=0; i< 20; i++)
	{

		stored_key = 127;

		if(i == 0)
			test_key = tVG_P1_UP_KEY;
		if(i == 1)
			test_key = tVG_P1_DOWN_KEY;
		if(i == 2)
			test_key = tVG_P1_LEFT_KEY;
		if(i == 3)
			test_key = tVG_P1_RIGHT_KEY;

		if(i == 4)
			test_key = tVG_P1_PUNCH1_KEY;
		if(i == 5)
			test_key = tVG_P1_PUNCH2_KEY;
		if(i == 6)
			test_key = tVG_P1_KICK1_KEY;
		if(i == 7)
			test_key = tVG_P1_KICK2_KEY;

		if(i == 8)
			test_key = tVG_P2_UP_KEY;
		if(i == 9)
			test_key = tVG_P2_DOWN_KEY;
		if(i == 10)
			test_key = tVG_P2_LEFT_KEY;
		if(i == 11)
			test_key = tVG_P2_RIGHT_KEY;

		if(i == 12)
			test_key = tVG_P2_PUNCH1_KEY;
		if(i == 13)
			test_key = tVG_P2_PUNCH2_KEY;
		if(i == 14)
			test_key = tVG_P2_KICK1_KEY;
		if(i == 15)
			test_key = tVG_P2_KICK2_KEY;

		if(i == 16)
			test_key = tVG_P1_BLOCK_KEY;
		if(i == 17)
			test_key = tVG_P1_THROW_KEY;
		if(i == 18)
			test_key = tVG_P2_BLOCK_KEY;
		if(i == 19)
			test_key = tVG_P2_THROW_KEY;

		if(test_key == VG_KEY_A)
			stored_key = 'A';
		if(test_key == VG_KEY_B)
			stored_key = 'B';
		if(test_key == VG_KEY_C)
			stored_key = 'C';
		if(test_key == VG_KEY_D)
			stored_key = 'D';
		if(test_key == VG_KEY_E)
			stored_key = 'E'; 
		if(test_key == VG_KEY_F)
			stored_key = 'F';
		if(test_key == VG_KEY_G)
			stored_key = 'G';

		if(test_key == VG_KEY_H)
			stored_key = 'H';
		if(test_key == VG_KEY_I) 
			stored_key = 'I';
		if(test_key == VG_KEY_J)
			stored_key = 'J';
		if(test_key == VG_KEY_K)
			stored_key = 'K';
		if(test_key == VG_KEY_L)
			stored_key = 'L';
		if(test_key == VG_KEY_M)
			stored_key = 'M';
		if(test_key == VG_KEY_N)
			stored_key = 'N';

		if(test_key == VG_KEY_O)
			stored_key = 'O';
		if(test_key == VG_KEY_P)
			stored_key = 'P';
		if(test_key == VG_KEY_Q)
			stored_key = 'Q';
		if(test_key == VG_KEY_R)
			stored_key = 'R';
		if(test_key == VG_KEY_S)
			stored_key = 'S';
		if(test_key == VG_KEY_T)
			stored_key = 'T';
		if(test_key == VG_KEY_U)
			stored_key = 'U';

		if(test_key == VG_KEY_V)
			stored_key = 'V';
		if(test_key == VG_KEY_W)
			stored_key = 'W';
		if(test_key == VG_KEY_X)
			stored_key = 'X';
		if(test_key == VG_KEY_Y)
			stored_key = 'Y';
		if(test_key == VG_KEY_Z)
			stored_key = 'Z';

		if(test_key == VG_KEY_0)
			stored_key = '0';
		if(test_key == VG_KEY_1)
			stored_key = '1';
		if(test_key == VG_KEY_2)
			stored_key = '2';
		if(test_key == VG_KEY_3)
			stored_key = '3';
		if(test_key == VG_KEY_4)
			stored_key = '4';
		if(test_key == VG_KEY_5)
			stored_key = '5';
		if(test_key == VG_KEY_6)
			stored_key = '6';
		if(test_key == VG_KEY_7)
			stored_key = '7';
		if(test_key == VG_KEY_8)
			stored_key = '8';
		if(test_key == VG_KEY_9)
			stored_key = '9';

		if(test_key == VG_KEY_BLANK)
			stored_key = '?';

		display_key = stored_key;

		if(test_key == VG_KEY_UP) 
		{
			stored_key = VK_UP; 
			display_key = 'ª';
		}
		if(test_key == VG_KEY_DOWN)
		{
			stored_key = VK_DOWN;
			display_key = '«';
		}
		if(test_key == VG_KEY_LEFT)
		{
			stored_key = VK_LEFT;
			display_key = '¨';
		}
		if(test_key == VG_KEY_RIGHT)
		{
			stored_key = VK_RIGHT;
			display_key = '©';
		}
		 
		if(test_key == VG_KEY_SPACE)
		{
			stored_key = VK_SPACE;
			display_key = '#';
		}
		 
		if(test_key == VG_KEY_COMMA)
		{
			stored_key = VK_OEM_COMMA;
			display_key = ',';
		}
		 
		if(test_key == VG_KEY_DOT)
		{
			stored_key = VK_OEM_PERIOD;
			display_key = '.';
		}
		 
		if(test_key == VG_KEY_DIVIDE)
		{
			stored_key = VK_OEM_2;
			display_key = '/';
		}
		 
		if(test_key == VG_KEY_ENDLINE)
		{
			stored_key = VK_OEM_1;
			display_key = ':';
		}
		 
		if(test_key == VG_KEY_FORWARDSLASH)
		{
			stored_key = VK_OEM_5;
			display_key = 'Ø';
		}
		 
		if(test_key == VG_KEY_DASH)
		{
			stored_key = VK_OEM_3;
			display_key = '$';
		}
		 
		if(test_key == VG_KEY_HASH)
		{
			stored_key = VK_OEM_7;
			display_key = '±';
		}
		 
		if(test_key == VG_KEY_LBRACKET)
		{
			stored_key = VK_OEM_4;
			display_key = '(';
		}
		 
		if(test_key == VG_KEY_RBRACKET)
		{
			stored_key = VK_OEM_6;
			display_key = ')';
		}

		if(i == 0 && stored_key != 127)
		{

			VG_P1_UP_KEY = stored_key;
			VG_P1_UP_KEY_DSY = display_key;

		}
		if(i == 1 && stored_key != 127)
		{
			VG_P1_DOWN_KEY = stored_key;
			VG_P1_DOWN_KEY_DSY = display_key;
		}
		if(i == 2 && stored_key != 127)
		{
			VG_P1_LEFT_KEY = stored_key;
			VG_P1_LEFT_KEY_DSY = display_key;
		}
		if(i == 3 && stored_key != 127)
		{
			VG_P1_RIGHT_KEY = stored_key;
			VG_P1_RIGHT_KEY_DSY = display_key;
		}

		if(i == 4 && stored_key != 127)
		{
			VG_P1_PUNCH1_KEY = stored_key;
			VG_P1_PUNCH1_KEY_DSY = display_key;
		}
		if(i == 5 && stored_key != 127)
		{
			VG_P1_PUNCH2_KEY = stored_key;
			VG_P1_PUNCH2_KEY_DSY = display_key;
		}
		if(i == 6 && stored_key != 127)
		{
			VG_P1_KICK1_KEY = stored_key;
			VG_P1_KICK1_KEY_DSY = display_key;
		}
		if(i == 7 && stored_key != 127)
		{
			VG_P1_KICK2_KEY = stored_key;
			VG_P1_KICK2_KEY_DSY = display_key;
		}

		if(i == 8 && stored_key != 127)
		{
			VG_P2_UP_KEY = stored_key;
			VG_P2_UP_KEY_DSY = display_key;
		}
		if(i == 9 && stored_key != 127)
		{
			VG_P2_DOWN_KEY = stored_key;
			VG_P2_DOWN_KEY_DSY = display_key;
		}
		if(i == 10 && stored_key != 127)
		{
			VG_P2_LEFT_KEY = stored_key;
			VG_P2_LEFT_KEY_DSY = display_key;
		}
		if(i == 11 && stored_key != 127)
		{
			VG_P2_RIGHT_KEY = stored_key;
			VG_P2_RIGHT_KEY_DSY = display_key;
		}

		if(i == 12 && stored_key != 127) 
		{
			VG_P2_PUNCH1_KEY = stored_key;
			VG_P2_PUNCH1_KEY_DSY = display_key;
		}
		if(i == 13 && stored_key != 127)
		{
			VG_P2_PUNCH2_KEY = stored_key;
			VG_P2_PUNCH2_KEY_DSY = display_key;
		}
		if(i == 14 && stored_key != 127)
		{
			VG_P2_KICK1_KEY = stored_key;
			VG_P2_KICK1_KEY_DSY = display_key;
		}
		if(i == 15 && stored_key != 127)
		{
			VG_P2_KICK2_KEY = stored_key;
			VG_P2_KICK2_KEY_DSY = display_key;
		}

		if(i == 16 && stored_key != 127) 
		{
			VG_P1_BLOCK_KEY = stored_key;
			VG_P1_BLOCK_KEY_DSY = display_key;
		}
		if(i == 17 && stored_key != 127)
		{
			VG_P1_THROW_KEY = stored_key;
			VG_P1_THROW_KEY_DSY = display_key;
		}
		if(i == 18 && stored_key != 127)
		{
			VG_P2_BLOCK_KEY = stored_key;
			VG_P2_BLOCK_KEY_DSY = display_key;
		}
		if(i == 19 && stored_key != 127)
		{
			VG_P2_THROW_KEY = stored_key;
			VG_P2_THROW_KEY_DSY = display_key;
		}

	}


}



void VG_Put_Keys_Into_Temps()
{
	int kick_key = 0;
	int test_key;
	int stored_key;

	for(int i=0; i< 20; i++)
	{

		stored_key = 0;

		if(i == 0)
			test_key = VG_P1_UP_KEY;
		if(i == 1) 
			test_key = VG_P1_DOWN_KEY;
		if(i == 2)
			test_key = VG_P1_LEFT_KEY;
		if(i == 3)
			test_key = VG_P1_RIGHT_KEY;

		if(i == 4)
			test_key = VG_P1_PUNCH1_KEY;
		if(i == 5)
			test_key = VG_P1_PUNCH2_KEY;
		if(i == 6)
			test_key = VG_P1_KICK1_KEY;
		if(i == 7)
			test_key = VG_P1_KICK2_KEY;

		if(i == 8)
			test_key = VG_P2_UP_KEY;
		if(i == 9)
			test_key = VG_P2_DOWN_KEY;
		if(i == 10)
			test_key = VG_P2_LEFT_KEY;
		if(i == 11)
			test_key = VG_P2_RIGHT_KEY;

		if(i == 12)
			test_key = VG_P2_PUNCH1_KEY;
		if(i == 13)
			test_key = VG_P2_PUNCH2_KEY;
		if(i == 14)
			test_key = VG_P2_KICK1_KEY;
		if(i == 15)
			test_key = VG_P2_KICK2_KEY;

		if(i == 16)
			test_key = VG_P1_BLOCK_KEY;
		if(i == 17)
			test_key = VG_P1_THROW_KEY;
		if(i == 18)
			test_key = VG_P2_BLOCK_KEY;
		if(i == 19)
			test_key = VG_P2_THROW_KEY;

		if(test_key == 'A')
			stored_key = VG_KEY_A;
		if(test_key == 'B')
			stored_key = VG_KEY_B;
		if(test_key == 'C')
			stored_key = VG_KEY_C;
		if(test_key == 'D')
			stored_key = VG_KEY_D;
		if(test_key == 'E')
			stored_key = VG_KEY_E;
		if(test_key == 'F')
			stored_key = VG_KEY_F;
		if(test_key == 'G')
			stored_key = VG_KEY_G;

		if(test_key == 'H')
			stored_key = VG_KEY_H;
		if(test_key == 'I')
			stored_key = VG_KEY_I;
		if(test_key == 'J')
			stored_key = VG_KEY_J;
		if(test_key == 'K')
			stored_key = VG_KEY_K;
		if(test_key == 'L')
			stored_key = VG_KEY_L;
		if(test_key == 'M')
			stored_key = VG_KEY_M;
		if(test_key == 'N')
			stored_key = VG_KEY_N;

		if(test_key == 'O')
			stored_key = VG_KEY_O;
		if(test_key == 'P')
			stored_key = VG_KEY_P;
		if(test_key == 'Q')
			stored_key = VG_KEY_Q;
		if(test_key == 'R')
			stored_key = VG_KEY_R;
		if(test_key == 'S')
			stored_key = VG_KEY_S;
		if(test_key == 'T')
			stored_key = VG_KEY_T;
		if(test_key == 'U')
			stored_key = VG_KEY_U;

		if(test_key == 'V')
			stored_key = VG_KEY_V;
		if(test_key == 'W')
			stored_key = VG_KEY_W;
		if(test_key == 'X')
			stored_key = VG_KEY_X;
		if(test_key == 'Y')
			stored_key = VG_KEY_Y;
		if(test_key == 'Z')
			stored_key = VG_KEY_Z;

		if(test_key == '0')
			stored_key = VG_KEY_0;
		if(test_key == '1')
			stored_key = VG_KEY_1;
		if(test_key == '2')
			stored_key = VG_KEY_2;
		if(test_key == '3')
			stored_key = VG_KEY_3;
		if(test_key == '4')
			stored_key = VG_KEY_4;
		if(test_key == '5')
			stored_key = VG_KEY_5;
		if(test_key == '6')
			stored_key = VG_KEY_6;
		if(test_key == '7')
			stored_key = VG_KEY_7;
		if(test_key == '8')
			stored_key = VG_KEY_8;
		if(test_key == '9')
			stored_key = VG_KEY_9;

		if(test_key == '?')
			stored_key = VG_KEY_BLANK;

		if(test_key == VK_SPACE)
			stored_key = VG_KEY_SPACE;

		if(test_key == VK_UP)
			stored_key = VG_KEY_UP;
		if(test_key == VK_DOWN)
			stored_key = VG_KEY_DOWN;
		if(test_key == VK_LEFT)
			stored_key = VG_KEY_LEFT;
		if(test_key == VK_RIGHT)
			stored_key = VG_KEY_RIGHT;

		if(test_key == VK_OEM_COMMA)
			stored_key = VG_KEY_COMMA;
		if(test_key == VK_OEM_PERIOD)
			stored_key = VG_KEY_DOT;
		if(test_key == VK_OEM_2)
			stored_key = VG_KEY_DIVIDE;
		if(test_key == VK_OEM_1)
			stored_key = VG_KEY_ENDLINE;
		if(test_key == VK_OEM_5)
			stored_key = VG_KEY_FORWARDSLASH;
		if(test_key == VK_OEM_3)
			stored_key = VG_KEY_DASH;
		if(test_key == VK_OEM_7)
			stored_key = VG_KEY_HASH;
		if(test_key == VK_OEM_4)
			stored_key = VG_KEY_LBRACKET;
		if(test_key == VK_OEM_6)
			stored_key = VG_KEY_RBRACKET;

		if(i == 0)
			tVG_P1_UP_KEY = stored_key;
		if(i == 1)
			tVG_P1_DOWN_KEY = stored_key;
		if(i == 2)
			tVG_P1_LEFT_KEY = stored_key;
		if(i == 3)
			tVG_P1_RIGHT_KEY = stored_key;

		if(i == 4)
			tVG_P1_PUNCH1_KEY = stored_key;
		if(i == 5)
			tVG_P1_PUNCH2_KEY = stored_key;
		if(i == 6)
			tVG_P1_KICK1_KEY = stored_key;
		if(i == 7)
			tVG_P1_KICK2_KEY = stored_key;

		if(i == 8)
			tVG_P2_UP_KEY = stored_key;
		if(i == 9)
			tVG_P2_DOWN_KEY = stored_key;
		if(i == 10)
			tVG_P2_LEFT_KEY = stored_key;
		if(i == 11)
			tVG_P2_RIGHT_KEY = stored_key;

		if(i == 12)
			tVG_P2_PUNCH1_KEY = stored_key;
		if(i == 13)
			tVG_P2_PUNCH2_KEY = stored_key;
		if(i == 14)
			tVG_P2_KICK1_KEY = stored_key;
		if(i == 15)
			tVG_P2_KICK2_KEY = stored_key;

		if(i == 16)
			tVG_P1_BLOCK_KEY = stored_key;
		if(i == 17)
			tVG_P1_THROW_KEY = stored_key;
		if(i == 18)
			tVG_P2_BLOCK_KEY = stored_key;
		if(i == 19)
			tVG_P2_THROW_KEY = stored_key;

	}	 

}

bool VG_Scan_for_Input()
{
	bool success = false;

     if (keys['A'])						// Is F1 Being Pressed?
     {
        keys['A']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_A;
		success = true;
     }    
     if (keys['B'])						// Is F1 Being Pressed?
     {
        keys['B']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_B;
		success = true;
     }    
     if (keys['C'])						// Is F1 Being Pressed?
     {
        keys['C']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_C;
		success = true;
     }    
     if (keys['D'])						// Is F1 Being Pressed?
     {
        keys['D']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_D;
		success = true;
     }    
     if (keys['E'])						// Is F1 Being Pressed?
     {
        keys['E']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_E;
		success = true;
     }    
     if (keys['F'])						// Is F1 Being Pressed?
     {
        keys['F']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_F;
		success = true;
     }    
     if (keys['G'])						// Is F1 Being Pressed?
     {
        keys['G']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_G;
		success = true;
     }    
     if (keys['H'])						// Is F1 Being Pressed?
     {
        keys['H']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_H;
		success = true;
     }    
     if (keys['I'])						// Is F1 Being Pressed?
     {
        keys['I']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_I;
		success = true;
     }    
     if (keys['J'])						// Is F1 Being Pressed?
     {
        keys['J']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_J;
		success = true;
     }    
     if (keys['K'])						// Is F1 Being Pressed?
     {
        keys['K']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_K;
		success = true;
     }    
     if (keys['L'])						// Is F1 Being Pressed?
     {
        keys['L']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_L;
		success = true;
     }    
     if (keys['M'])						// Is F1 Being Pressed?
     {
        keys['M']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_M;
		success = true;
     }    
     if (keys['N'])						// Is F1 Being Pressed?
     {
        keys['N']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_N;
		success = true;
     }    
     if (keys['O'])						// Is F1 Being Pressed?
     {
        keys['O']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_O;
		success = true;
     }    
     if (keys['P'])						// Is F1 Being Pressed?
     {
        keys['P']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_P;
		success = true;
     }    
     if (keys['Q'])						// Is F1 Being Pressed?
     {
        keys['Q']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_Q;
		success = true;
     }    
     if (keys['R'])						// Is F1 Being Pressed?
     {
        keys['R']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_R;
		success = true;
     }    
     if (keys['S'])						// Is F1 Being Pressed?
     {
        keys['S']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_S;
		success = true;
     }    
     if (keys['T'])						// Is F1 Being Pressed?
     {
        keys['T']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_T;
		success = true;
     }    
     if (keys['U'])						// Is F1 Being Pressed?
     {
        keys['U']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_U;
		success = true;
     }    
     if(keys['V'])						// Is F1 Being Pressed?
     {
        keys['V']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_V;
		success = true;
     }    
     if( keys['W'])						// Is F1 Being Pressed?
     {
        keys['W']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_W;
		success = true;
     }    
     if( keys['X'])						// Is F1 Being Pressed?
     {
        keys['X']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_X;
		success = true;
     }    
     if( keys['Y'])						// Is F1 Being Pressed?
     {
        keys['Y']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_Y;
		success = true;
     }    
     if( keys['Z'])						// Is F1 Being Pressed?
     {
        keys['Z']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_Z;
		success = true;
     }    
     if( keys['0'])						// Is F1 Being Pressed?
     {
        keys['0']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_0;
		success = true;
     }    
     if( keys['1'])						// Is F1 Being Pressed?
     {
        keys['1']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_1;
		success = true;
     }    
     if( keys['2'])						// Is F1 Being Pressed?
     {
        keys['2']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_2;
		success = true;
     }    
     if (keys['3'])						// Is F1 Being Pressed?
     {
        keys['3']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_3;
		success = true;
     }    
     if (keys['4'])						// Is F1 Being Pressed?
     {
        keys['4']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_4;
		success = true;
     }  
     if (keys['5'])						// Is F1 Being Pressed?
     {
        keys['5']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_5;
		success = true;
     }    
     if (keys['6'])						// Is F1 Being Pressed?
     {
        keys['6']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_6;
		success = true;
     }    
     if (keys['7'])						// Is F1 Being Pressed?
     {
        keys['7']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_7;
		success = true;
     }    
     if (keys['8'])						// Is F1 Being Pressed?
     {
        keys['8']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_8;
		success = true;
     }    
     if (keys['9'])						// Is F1 Being Pressed?
     {
        keys['9']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_9;
		success = true;
     }   

     if (keys['9'])						// Is F1 Being Pressed?
     {
        keys['9']=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_9;
		success = true;
     }  

     if (keys[VK_SPACE])						// Is F1 Being Pressed?
     {
        keys[VK_SPACE]=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_SPACE;
		success = true;
     }    
     if (keys[VK_UP])						// Is F1 Being Pressed?
     {
        keys[VK_UP]=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_UP;
		success = true;
     } 
     if (keys[VK_DOWN])						// Is F1 Being Pressed?
     {
        keys[VK_DOWN]=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_DOWN;
		success = true;
     } 
     if (keys[VK_LEFT])						// Is F1 Being Pressed?
     {
        keys[VK_LEFT]=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_LEFT;
		success = true;
     }    
     if (keys[VK_RIGHT])						// Is F1 Being Pressed?
     {
        keys[VK_RIGHT]=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_RIGHT;
		success = true;
     } 
     if (keys[VK_OEM_COMMA])						// Is F1 Being Pressed?
     {
        keys[VK_OEM_COMMA]=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_COMMA;
		success = true;
     } 
     if (keys[VK_OEM_PERIOD])						// Is F1 Being Pressed?
     {
        keys[VK_OEM_PERIOD]=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_DOT;
		success = true;
     } 
     if (keys[VK_OEM_2])						// Is F1 Being Pressed?
     {
        keys[VK_OEM_2]=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_DIVIDE;
		success = true;
     } 
     if (keys[VK_OEM_1])						// Is F1 Being Pressed?
     {
        keys[VK_OEM_1]=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_ENDLINE;
		success = true;
     } 
     if (keys[VK_OEM_5])						// Is F1 Being Pressed?
     {
        keys[VK_OEM_5]=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_FORWARDSLASH;
		success = true;
     } 
     if (keys[VK_OEM_3])						// Is F1 Being Pressed?
     {
        keys[VK_OEM_3]=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_DASH;
		success = true;
     } 
     if (keys[VK_OEM_7])						// Is F1 Being Pressed?
     {
        keys[VK_OEM_7]=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_HASH;
		success = true;
     } 
     if (keys[VK_OEM_4])						// Is F1 Being Pressed?
     {
        keys[VK_OEM_4]=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_LBRACKET;
		success = true;
     } 
     if (keys[VK_OEM_6])						// Is F1 Being Pressed?
     {
        keys[VK_OEM_6]=FALSE;					// If So Make Key FALSE
		VG_global_temp_key = VG_KEY_RBRACKET;
		success = true;
     } 

	return(success);
}

bool VG_Check_Key_Available(int player)
{
	bool success=true;

	// Player 1 can overwrite player 2 keys...
	if(player == 1)
	{
		if(VG_global_temp_key == tVG_P2_UP_KEY)
			tVG_P2_UP_KEY = VG_KEY_BLANK;
		if(VG_global_temp_key == tVG_P2_DOWN_KEY)
			tVG_P2_DOWN_KEY = VG_KEY_BLANK;
		if(VG_global_temp_key == tVG_P2_LEFT_KEY)
			tVG_P2_LEFT_KEY = VG_KEY_BLANK;
		if(VG_global_temp_key == tVG_P2_RIGHT_KEY)
			tVG_P2_RIGHT_KEY = VG_KEY_BLANK;

		if(VG_global_temp_key == tVG_P2_PUNCH1_KEY)
			tVG_P2_PUNCH1_KEY = VG_KEY_BLANK;
		if(VG_global_temp_key == tVG_P2_PUNCH2_KEY)
			tVG_P2_PUNCH2_KEY = VG_KEY_BLANK;
		if(VG_global_temp_key == tVG_P2_KICK1_KEY)
			tVG_P2_KICK1_KEY = VG_KEY_BLANK;
		if(VG_global_temp_key == tVG_P2_KICK2_KEY)
			tVG_P2_KICK2_KEY = VG_KEY_BLANK;

		if(VG_global_temp_key == tVG_P2_BLOCK_KEY)
			tVG_P2_BLOCK_KEY = VG_KEY_BLANK;
		if(VG_global_temp_key == tVG_P2_THROW_KEY)
			tVG_P2_THROW_KEY = VG_KEY_BLANK;

	}

	if(VG_global_temp_key == tVG_P1_UP_KEY)
		success = false;
	if(VG_global_temp_key == tVG_P1_DOWN_KEY)
		success = false;
	if(VG_global_temp_key == tVG_P1_LEFT_KEY)
		success = false;
	if(VG_global_temp_key == tVG_P1_RIGHT_KEY)
		success = false;

	if(VG_global_temp_key == tVG_P1_PUNCH1_KEY)
		success = false;
	if(VG_global_temp_key == tVG_P1_PUNCH2_KEY)
		success = false;
	if(VG_global_temp_key == tVG_P1_KICK1_KEY)
		success = false;
	if(VG_global_temp_key == tVG_P1_KICK2_KEY)
		success = false;

	if(VG_global_temp_key == tVG_P1_BLOCK_KEY)
		success = false;
	if(VG_global_temp_key == tVG_P1_THROW_KEY)
		success = false;

	if(VG_global_temp_key == tVG_P2_UP_KEY)
		success = false;
	if(VG_global_temp_key == tVG_P2_DOWN_KEY)
		success = false;
	if(VG_global_temp_key == tVG_P2_LEFT_KEY) 
		success = false;
	if(VG_global_temp_key == tVG_P2_RIGHT_KEY)
		success = false;

	if(VG_global_temp_key == tVG_P2_PUNCH1_KEY)
		success = false;
	if(VG_global_temp_key == tVG_P2_PUNCH2_KEY)
		success = false;
	if(VG_global_temp_key == tVG_P2_KICK1_KEY)
		success = false;
	if(VG_global_temp_key == tVG_P2_KICK2_KEY)
		success = false;

	if(VG_global_temp_key == tVG_P2_BLOCK_KEY)
		success = false;
	if(VG_global_temp_key == tVG_P2_THROW_KEY)
		success = false;


	return(success);
}*/