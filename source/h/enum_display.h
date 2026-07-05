
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

//#include <windows.h>
#ifdef SWITCH
#include <gl\gl.h>
#endif
#include <string.h>    
//#include <WinUser.h>
#include "globals.h" 

#define MOUSE_CURSOR_ACTIVE  0   

extern void Set_Screen_Ratio();
extern bool LoadScene( int episode1, int scene1, bool delete_textures );
extern bool LoadCFG();


void GetDisplaySettings()
{

   /*int index = 0;
   //DEVMODE dm;
   // initialize the DEVMODE structure
   ZeroMemory(&dm, sizeof(dm));  
   dm.dmSize = sizeof(dm); 

   memset(RES_Available, false, sizeof(RES_Available));

   while(0 != EnumDisplaySettings(NULL, index++, &dm))
   {
      // inspect the DEVMODE structure to obtain details
      // about the display settings such as
      //  - Orientation
      //  - Width and Height  
      //  - Frequency 
      //  - etc. 

	//   fprintf(fp2, "dm.dmPositionX %d\n", dm.dmPelsWidth); 
	//   fprintf(fp2, "dm.dmPositionX %d\n", dm.dmPelsHeight); 
	//  fprintf(fp2, "dm.dmBitsPerPel %d\n", dm.dmBitsPerPel);

	//   RES_Width[0]  = 1280; 
	//   RES_Height[0] = 720;	
	   if(dm.dmPelsWidth == 1280 && dm.dmPelsHeight == 720 && dm.dmBitsPerPel == 32)
		   RES_Available[0] = true;

	//	  RES_Width[1]  = 1366;
	//	  RES_Height[1] = 768;
	   if(dm.dmPelsWidth == 1366 && dm.dmPelsHeight == 768 && dm.dmBitsPerPel == 32)
		   RES_Available[1] = true;

	//	  RES_Width[2]  = 1600;
	//	  RES_Height[2] = 900;
	   if(dm.dmPelsWidth == 1600 && dm.dmPelsHeight == 900 && dm.dmBitsPerPel == 32)
		   RES_Available[2] = true;

	//	  RES_Width[3]  = 1920;
	//	  RES_Height[3] = 1080;
	   if(dm.dmPelsWidth == 1920 && dm.dmPelsHeight == 1080 && dm.dmBitsPerPel == 32)
		   RES_Available[3] = true;

	//	  RES_Width[4]  = 2048;
	//	  RES_Height[4] = 1152;  
	   if(dm.dmPelsWidth == 2048 && dm.dmPelsHeight == 1152 && dm.dmBitsPerPel == 32)
		   RES_Available[4] = true;

	//	  RES_Width[5]  = 2560;
	//	  RES_Height[5] = 1440;
	   if(dm.dmPelsWidth == 2560 && dm.dmPelsHeight == 1440 && dm.dmBitsPerPel == 32)
		   RES_Available[5] = true;
 
	//	  RES_Width[6]  = 3200;
	//	  RES_Height[6] = 1800;
	   if(dm.dmPelsWidth == 3200 && dm.dmPelsHeight == 1800 && dm.dmBitsPerPel == 32)
		   RES_Available[6] = true;

	//	  RES_Width[7]  = 3840;
	//	  RES_Height[7] = 2160;
	   if(dm.dmPelsWidth == 3840 && dm.dmPelsHeight == 2160 && dm.dmBitsPerPel == 32)
		   RES_Available[7] = true;

	//	  RES_Width[8]  = 4096;
	//	  RES_Height[8] = 2304;
	   if(dm.dmPelsWidth == 4096 && dm.dmPelsHeight == 2304 && dm.dmBitsPerPel == 32)
		   RES_Available[8] = true;

	//	  RES_Width[9]  = 1280;
	//	  RES_Height[9] = 800;	
	   if(dm.dmPelsWidth == 1280 && dm.dmPelsHeight == 800 && dm.dmBitsPerPel == 32)
		   RES_Available[9] = true;

	//	  RES_Width[10]  = 1440;
	//	  RES_Height[10] = 900;
	   if(dm.dmPelsWidth == 1440 && dm.dmPelsHeight == 900 && dm.dmBitsPerPel == 32)
		   RES_Available[10] = true;

	//	  RES_Width[11]  = 1680;
	//	  RES_Height[11] = 1050;
	   if(dm.dmPelsWidth == 1680 && dm.dmPelsHeight == 1050 && dm.dmBitsPerPel == 32)
		   RES_Available[11] = true;

	//	  RES_Width[12]  = 1920;
	//	  RES_Height[12] = 1200;
	   if(dm.dmPelsWidth == 1920 && dm.dmPelsHeight == 1200 && dm.dmBitsPerPel == 32)
		   RES_Available[12] = true;

	//	  RES_Width[13]  = 2048;
	//	  RES_Height[13] = 1280; 
	   if(dm.dmPelsWidth == 2048 && dm.dmPelsHeight == 1280 && dm.dmBitsPerPel == 32)
		   RES_Available[13] = true;

	//	  RES_Width[14]  = 2560; 
	//	  RES_Height[14] = 1600;
	   if(dm.dmPelsWidth == 2560 && dm.dmPelsHeight == 1600 && dm.dmBitsPerPel == 32)
		   RES_Available[14] = true;
 
	//	  RES_Width[15]  = 2880;
	//	  RES_Height[15] = 1800;
	   if(dm.dmPelsWidth == 2880 && dm.dmPelsHeight == 1800 && dm.dmBitsPerPel == 32)
		   RES_Available[15] = true;

	//	  RES_Width[16]  = 3840;
	//	  RES_Height[16] = 2400;
	   if(dm.dmPelsWidth == 3840 && dm.dmPelsHeight == 2400 && dm.dmBitsPerPel == 32)
		   RES_Available[16] = true;

	//	  RES_Width[17]  = 5120;
	//	  RES_Height[17] = 3200;
	   if(dm.dmPelsWidth == 5120 && dm.dmPelsHeight == 3200 && dm.dmBitsPerPel == 32)
		   RES_Available[17] = true;


   }*/




}