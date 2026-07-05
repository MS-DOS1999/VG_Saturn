// Super trench attack-STEAM.cpp : Defines the entry point for the application.             
#include "stdafx.h"      
#include "Super trench attack-STEAM.h"
#include "interface.h"




#ifdef SWITCH

#include <nn/oe.h>

extern bool NEED_TO_SAVE_AND_EXIT;
#elif PS4
#include <sampleutil.h>
#include <vectormath.h>
#include <vector>
#include <string>
#include <scebase_common.h>
#include <mutex>
#include <user_service.h>
#include <system_service.h>
#include <np.h>
#include <libsysmodule.h>

#include "d3dmath.h"

#elif XB1
#include "d3dmath_custom.h"
#endif



//#include <EGLLayer.h>
                                                                                                                          
#define WIN32_LEAN_AND_MEAN                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
#define WIN32_EXTRA_LEAN                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
#define DEBUG_MODE  1  // 0 == ON   // 1 == OFF                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
#define DEMO_MODE   1  // 0 == ON   // 1 == OFF                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
                                                                                                                                                                                                                                                                                                                                                                                                                                
#define QUICK_LOAD  0  // 1 == ON   // 0 == OFF                                                                                                                                                                                                                                                                                                                                                 
#define QUICK_QUIT  0  // 1 == ON   // 0 == OFF                                                                                                                                                                                                                                                                                                             
                                                                                                                                                                                           
#define QUICK_PLAY  0                                        
                   
#define TEST_SANG     0    
#define TEST_ALTERS   0   
#define VG_CORNER_SLIDEBACK 1     

#define VG_STEAM_DEMO  0  
  
#define FRAME_RATE_DELAY 0 
  
#define TURN_OFF_INGAME_HELP       0  
#define DISPLAY_1_MOVES_DURING_VS  1  
                     
#define PLAYER_INVULNERABLE  0                                                                                                                                  
#define DISABLE_ALL_ENEMIES  0                                                               
                                                 
#define TESTING_PROC_ROUTE 0        

#define SHAKE_CAM_WHEN_HIT  1     
     
#define NO_SPECIALS  0   
                   
#define NEW_CAMERA_TEST  0                                                                       
                        
#define INFINITE_RUN     0      
 
#define WALK_BUG_TEST    0 
                            
#define DISPLAY_MESSAGES 0                                                         
                      
#define IS_FULL_GAME   1                                                                                                       
#ifdef SWITCH
#define IS_FULL_STEAM     0   // Includes steam files...
#elif defined (PS4) || defined (XB1)
#define IS_FULL_STEAM     1   // Includes steam files...
#endif


#if defined(PS4) || defined(XB1)
#define IS_USING_DIRECTX  1   // Includes directX code...
#endif

#ifdef SWITCH
#define IS_USING_DIRECTX  0   // Includes directX code...
#endif
 
#define RENDER_DEFAULT    0        
#define RENDER_OPENGL     1                    
#define RENDER_DIRECTX    2        
 
#define UNITS_CAN_MOVE_MORE_THAN_ONCE 1        
  
#define INCLDUE_360_CONTROLLER 1 

#define REPLACE_SANG_WITH_KENNEDY 1

#define ZOOMING_CAMERA 0

//#define BREAKER_CHARACTER_BUILD



      


#if defined(PS4) || defined(XB1)
int RENDERER = RENDER_DIRECTX;     // RENDER_OPENGL   /   RENDER_DIRECTX
#endif

#ifdef SWITCH
int RENDERER = RENDER_OPENGL;     // RENDER_OPENGL   /   RENDER_DIRECTX
#endif
      
//#include <windows.h>
#ifdef SWITCH
//#include <egl/egl.h>
//#include "glad/glad.h"
#endif
#include <string.h>                                                                                                      
#include <stdio.h>			// Header File For Standard Input/Output         
#include <stdlib.h>                                                                                                                                                        
//#include <wtypes.h>                                                                                                                                                                                                                                
#include <iostream>          
#include <cstdio>
                   
#if IS_USING_DIRECTX == 1                                                 
        
#if defined(XB1)
	// DirectX Header Files                
	//#include <d3d9.h>        
	//#include <d3dx9.h>  
	//#include <D3dx9math.h>
    //#include <Xinput.h>
#endif
  
#endif    
         
#if INCLDUE_360_CONTROLLER == 1                          
                          
	// DirectX Header Files
#ifdef XB1
    //#include <Xinput.h> 
#endif
    #include "dxinput.h"
	extern void Run_Joypad();    
	extern bool Check_Controller(); 

#endif       
	           
//#include "audiere.h"                                                                                                                                                                                                                                                                                                            
//using namespace audiere;  
//AudioDevicePtr device;

    
#include "globals.h"  
#include "VG_globals.h"  
                 
bool STEAM_ACTIVE = false; 
 
#if IS_FULL_STEAM == 1                       
         
	/*#include "steam_api.h"        
	#include "steam_gameserver.h"                  
	#include "isteamuserstats.h"
    #include "steam_stuff.h"*/    
     

#endif          
       
#if IS_USING_DIRECTX == 1                               
   
	/*  Make the class name into a global variable  */
	char szClassName[ ] = "WindowsApp";
	extern void cleanD3D(void);    // closes Direct3D and releases memory 

#endif  

#include "TGALoader.h"           
#include "timer.h"                                                                                                                                                                                                                                                                                                                                  
#include "texture.h"                                                                                                                                                                                                                                                                                                                                                                                                                                        
#include "load.h"                                                                                                                                                                                                                                             
#include "draw.h"                                                                               
#include "drawX.h"                                                                                    
#include "draw_functions.h"                                                                                                                                                                                                                                                                                                                                    
#include "win_code.h"                                                                                                                                                                                                                                                                                                                                                                                               
#include "Animate.h"        
#include "enum_display.h" 
                 
#include "VG_scripts.h"               
#include "VG_keys.h"    
#include "VG_keys_editor.h"  
#include "VG_Moves.h"                     
#include "VG_specials.h"     
#include "VG_specialsCONT.h"   
#include "VG_Text.h"        
#include "VG_AI.h"                    
#include "VG_Pause.h"            
#include "VG_Throws.h"              
#include "VG_Story.h"     
#include "VG_math.h"  
#include "VG_frontend.h"  
#include "VG_rebinds.h" 
	             
#include "VG_Story_Gyeong.h"      
#include "VG_Story_Siu.h"    
#include "VG_Story_Minso.h"       
#include "VG_Story_Reese.h"   
#include "VG_Story_Yohan.h" 
#include "VG_Story_Jae.h"  
#include "VG_Story_Gun.h"    
#include "VG_Story_Hyuk.h" 
#include "VG_Story_Sho.h"    
#include "VG_Story_Tia.h"
#include "VG_Story_Saizo.h"  
#include "VG_Story_Sang.h"  
#include "VG_Story_Kennedy.h"  

#include "VG_GYEONG.h"           
#include "VG_SIU.h"    
#include "VG_MINSO.h"         
#include "VG_REESE.h"   
#include "VG_YOHAN.h"   
#include "VG_JAE.h"  
#include "VG_GUN.h"   
#include "VG_HYUK.h"  
#include "VG_SANG.h"  
#include "VG_TRAINER.h"  
#include "VG_SHO.h" 
#include "VG_TIA.h"  
#include "VG_SAIZO.h" 
#include "VG_KENNEDY.h" 


#define V3f glVertex3f                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
bool LoadTGA(Texture *, char  *);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
bool sLoadTGA(Texture *, char *);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                   
// External routines                                                    
extern int GetFont(float &x, float &y, char letter, float &s_width);   
extern int Key_Handler(bool keys[256], object *display, int f_rate); 
extern int VG_Key_Handler(bool keys[256], object *display, int f_rate); 
extern void TimerInit(void);                                                                                                                                                                                                                    
#ifdef SWITCH
extern float TimerGetTime();
#elif defined PS4 || defined XB1
extern double TimerGetTime();
#endif                                                                                                                          
extern void Set_Timer(unsigned long time);                                                                                                                                                             
extern void Run_Verdict(int f_rate); 
extern bool LoadCFG();                                                                        
extern bool SaveCFG();    
extern bool LoadKeys();  
extern bool SaveKeys();  
  
// From load.h                                                              
extern int LoadAnim( sString sfilename, int texture_id );                                     
extern bool LoadText(sString sfilename); 
extern bool LoadHud( char *filename ); 
extern bool LoadScene(int episode1, int scene1, bool delete_textures); 
extern bool DumpScene( char *filename ); 
extern bool LoadTextures(sString sfilename, bool delete_textures); 
extern int DrawGLScene(bool render_all, int f_rate);	           
extern void KillGLWindow();                  
extern int CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag);
#ifdef SWITCH
extern GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
#endif
extern int InitGL();
#ifdef SWITCH
extern GLvoid Zoom(float fzoom);
#endif
extern void DrawLine( float x, float y, float width, float height, float colour); 
extern void DrawBox( float x, float y, float x1, float y1);
extern void Animation_System(int loop, bool bullet_check, bool interrupt, bool pain_anim, bool fire); 
extern void Animate(int loop, int type);                
extern void Set_Sprite(int id, int anim, int state, int hud_or_sprite, bool reset);
                                                                          
extern float GetCamDistance();       

extern void VG_Slow_Mo();
extern void VG_Pause();
extern bool Run_Frontend(int f_rate);


void VG_Get_Keys();
                                                
                                                 
void DrawLine( float x, float y, float width, float height, float colour); 
void DrawBox( float x, float y, float x1, float y1);

bool Remove_FX(int id, bool test);   
bool New_FX(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int i_value, int i_type, int state, int linked_sprite, int tex_id, int i_value1, int i_value2, int i_value3);
void Get_Sound(float x, float y);                   
void UpdateMouseCursor();      
void GetDesktopResolution(int& horizontal, int& vertical);
bool Reset_FX(int id, bool test);     
void Run_Fx(int f_rate); 
//void GetParameters(LPSTR lpCmdLine);
                   
bool STREAM_MUSIC = true;                            
                     
int warning_timer = 0;    


 
 
//RECT r;              
        
          
//AudioDevicePtr device(OpenDevice()); // This is now done further up! 
     
     
/*LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
		 					LPARAM	lParam)			// Additional Message Information
{   
       
    float tar_x = 0.0, tar_y = 0.0;                
    float new_width=0.0, new_height=0.0; 
      
	switch (uMsg)									// Check For Windows Messages
	{              
            
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}      
			else  
			{
				active=FALSE;						// Program Is No Longer Active
			}
 
			return 0;								// Return To The Message Loop
		}  
		              
		// Mouse handling      
		     
	    case WM_LBUTTONDOWN:		// left mouse button
	    {   
			if(!CONTROLLER)
			{

            if( mode )                  
            {              
            
                if(mode == POINT_MODE)                 
                {
                 if(!(pt_selection ==0)) 
                    pt_selection--;   
                 else     
                    pt_selection = no_points-1;                    
                } 
                if(mode == NODES) 
                {
                 if(!(nde_selection ==0))  
                    nde_selection--;
                 else  
                    nde_selection = no_nodes-1;                      
                }                    
                                    
            }                        
             
            UpdateMouseCursor();   
            
			if(game_paused == false)
            if(next_scene == false)     
                mouseleft = TRUE;     
            
			}

		    break;                       
        } 
        	     	
	    case WM_RBUTTONDOWN:		// left mouse button
	    {     
			if(!CONTROLLER)
			{

            if( mode )         
            {           
               
                if(mode == POINT_MODE)
                {      
                  if((pt_selection < (no_points-1)))
                      pt_selection++;
                  else 
                      pt_selection=0;                                              
                }                   
                if(mode == NODES)                                  
                {   
                  if((nde_selection < (no_nodes-1)))
                      nde_selection++;    
                  else     
                      nde_selection=0;                                     
                }                               
                                                 
            }                                                                                                   

			if(game_paused == false) 
			{

            mouseright = TRUE;                                        

			}

			} // !CONTROLLER
                                
		    break;                                  
        }           
        
	    case WM_LBUTTONUP:			// left button release
	    {
			if(!CONTROLLER) 
			{                
				     
			 if(game_paused == false)                      
             if(mouseleft == true)  
  	             mouseleftcheck = true;    
                        
	         mouseleft = FALSE;               
             
			 if(game_paused == false)
                 UpdateMouseCursor();              

			}

		    break;  

        } 
        case WM_RBUTTONUP:			// right button release
		{

			if(!CONTROLLER)
				mouseright = FALSE;

		     break;      
		}  
	    case WM_MBUTTONDOWN:			// left button release
	    {  
			 if(game_paused == false)
	             mousemiddle = TRUE;                     
		     break;                    
        }        
        case WM_MBUTTONUP:			// right button release
                
			 if(game_paused == false)
             if( mode )                
             {      
                 if(mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
				 if(no_sprites >= 0 && no_sprites < TOTAL_NO_SPRITES)
                 { 
                     no_sprites++;       
                     original_no_sprites++;                                        
        
                     sprite[no_sprites - 1].x = -(camX + 0.2f);
                     sprite[no_sprites - 1].y = -(camY + 0.45f);
                     sprite[no_sprites - 1].width = 0.4f;
                     sprite[no_sprites - 1].height = 0.9f;
                               
                     sprite[no_sprites - 1].w = -(camX + 0.2f);
                     sprite[no_sprites - 1].z = -(camY + 0.45f);
                     sprite[no_sprites - 1].box_width = 0.4f;
                     sprite[no_sprites - 1].box_height = 0.9f;
                     
                     sprite[no_sprites - 1].u[0] = 0.0f;    
	                 sprite[no_sprites - 1].v[0] = 0.0f;
	                 sprite[no_sprites - 1].u[1] = 1.0f; 
	                 sprite[no_sprites - 1].v[1] = 0.0f;       
	                 sprite[no_sprites - 1].u[2] = 1.0f;           
	                 sprite[no_sprites - 1].v[2] = 1.0f;         
	                 sprite[no_sprites - 1].u[3] = 0.0f;
	                 sprite[no_sprites - 1].v[3] = 1.0f;
	                    
                     sprite[no_sprites - 1].id = 0;
                     sprite[no_sprites - 1].anim_state = 0;
                     sprite[no_sprites - 1].anim = 0; 
                     sprite[no_sprites - 1].linked_sprite = -1;
                     sprite[no_sprites - 1].score = 0;          
                     sprite[no_sprites - 1].alpha = 1.0f;
                     sprite[no_sprites - 1].grab_switch = false;
                     sprite[no_sprites - 1].mouseover = false;
                     sprite[no_sprites - 1].sector = -1;
                     sprite[no_sprites - 1].sector_action = -1;
                     sprite[no_sprites - 1].onCreate = 0;
                     sprite[no_sprites - 1].type = 0;
                     sprite[no_sprites - 1].onCreate_action = 0;
                     sprite[no_sprites - 1].rank = 0;
                     sprite[no_sprites - 1].onDeath_action = 0; 
                     sprite[no_sprites - 1].light = 1.0f; 

	                 if( texture_fx[sprite[no_sprites - 1].id] == 2 || texture_fx[sprite[no_sprites - 1].id] == 3 || texture_fx[sprite[no_sprites - 1].id] == 4)
	                     sprite[no_sprites - 1].fx_id = animation_fx[sprite[no_sprites - 1].id];
                                                      	         
	                 selection = (no_sprites-1); 
                                 
                 }                      
                 if(mode == POINT_MODE)                                   
                 {   
                     no_points++;    
                     points[no_points - 1].x = -(camX);
                     points[no_points - 1].y = -(camY);
                     points[no_points - 1].score = -1;
                     points[no_points - 1].c1 = -1;
                     points[no_points - 1].c2 = -1;
                     points[no_points - 1].c3 = -1;
                     points[no_points - 1].c4 = -1;
                     
                     
                     pt_selection = (no_points-1);
                      
                 }
                 if(mode == NODES)                       
                 {           
                     no_nodes++;    
                     nodes[no_nodes - 1].x = -(camX);
                     nodes[no_nodes - 1].y = -(camY);
                     nodes[no_nodes - 1].score = -1;
                     nodes[no_nodes - 1].c1 = -1;
                     nodes[no_nodes - 1].c2 = -1;
                     nodes[no_nodes - 1].c3 = -1;
                     nodes[no_nodes - 1].c4 = -1;
                     
                     
                     nde_selection = (no_nodes-1);
                          
                 }                 
                   
                  
             }         
             	               
             mousemiddle = FALSE;      
                                        
        break;                                               
               	         
		case WM_MOUSEMOVE:			// mouse movement 
            
			if(CONTROLLER == false) //  || game_mode != WALK 
			{
				 
            mouseX = ((float)LOWORD(lParam));         
            mouseY = ((float)HIWORD(lParam));             
			 
            if(sc_width/2 != 0)      
                mouseX /= (sc_width/2);                        
                                         
            mouseX -= 1.0f;         
            mouseX *= zoom_factor; //     zoom_factor                                          
                 
            if(sc_height/2 != 0)                        
                mouseY /= (sc_height/2);          
                       
            mouseY -= 1.0f;                   
            mouseY *= (zoom_factor*sc_ratio);  // 
                
            mouseY = -(mouseY);   
                              
            real_mouseX = mouseX;                
            real_mouseY = mouseY;    
                                 
            UpdateMouseCursor();      
                       
            new_width  = hud27width  * 1.3f; 
            new_height = hud27height * 1.3f;           
            
            hud[27].width  = new_width;                                      
            hud[27].height = new_height;            

            hud[27].x = mouseX - (new_width/2);        
            hud[27].y = mouseY - (new_height/2);                 
            hud[27].w = mouseX - (new_width/2);   
            hud[27].z = mouseY - (new_height/2);              
            
            hud[28].x = hud[27].x + new_width;       
            hud[28].y = hud[27].y;      
            hud[28].width  = new_width;          
            hud[28].height = new_height;
                            
            hud_mouseX = mouseX;        
            hud_mouseY = mouseY;
                                                                        
            mouseX += -camX;                
            mouseY += -camY;    
            
            hud_mouseX += -camX;
            hud_mouseY += -camY;


			}        

		break;            
		                   
        case WM_MOUSEWHEEL:         
			 
            if ((short)HIWORD(wParam) > 0)        
            {     
               
               if(mode != TILE_MODE && selection >= 0)
               if( mode && (( sprite[selection].id < numsubmtls )) )
               {
                   sprite[selection].id++;
                   
	               if( texture_fx[sprite[selection].id] == 2 || texture_fx[sprite[selection].id] == 3 || texture_fx[sprite[selection].id] == 4)
	                 sprite[selection].fx_id = animation_fx[sprite[selection].id];
                   
      
               }                   

               mousewheel = UP;      
                                     
            }                        
            if ((short)HIWORD(wParam) < 0)               
            {   
                if(mode != TILE_MODE && selection >= 0)
                if( mode && (( sprite[selection].id > 0 )) )                           
                {
                    sprite[selection].id--;
                   
	               if( texture_fx[sprite[selection].id] == 2 || texture_fx[sprite[selection].id] == 3 || texture_fx[sprite[selection].id] == 4)
	                 sprite[selection].fx_id = animation_fx[sprite[selection].id];
                       
                } 
                    
               mousewheel = DOWN;                                
                
            }          
                                
        break;          
              
		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}        
                       
		case WM_CLOSE:			 					// Did We Receive A Close Message?
		{          
		//	PostQuitMessage(0);						// Send A Quit Message
                    
            quitting = true;
            quit_timer = (int)TimerGetTime() + 100; 
            
			return 0;								//  Back
		}          
         
 		case WM_KEYDOWN:	 						// Is A Key Being Held Down?
		{
			keys[wParam] = true;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}                          
  
		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = false;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}
  
		case WM_SIZE:								// Resize The OpenGL Window
		{
			if(RENDERER == RENDER_OPENGL)			
				ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
	    //	Set_Screen_Ratio();
			return 0;	 							// Jump Back
		}   
	    case WM_MOVE:			// left button release 
	    {  
             
	         saved_window_posX = (int)(short) LOWORD(lParam);   // horizontal position 
             saved_window_posY = (int)(short) HIWORD(lParam);   // vertical position 
              
        //     SaveCFG(); 
                                      
		     break;                  
        }           
        		            
        default:             
        break;                                         
                                        
	    }                
		     
	// Pass All Unhandled Messages To DefWindowProc 
	return DefWindowProc(hWnd,uMsg,wParam,lParam); 
}  */

#ifdef XB1

#include <string>
void UnlockAchievement(std::string id);

void platform_unlock_achievement(int id)
{
	UnlockAchievement(std::to_string(id+1));
}

#endif

#ifdef XB1
bool CANSAVE_XB1 = false;
#endif

#if defined (PS4) || defined (SWITCH)

#ifdef SWITCH
#include "SwStartup.h"
#include "IControl.h"

NN_OS_ALIGNAS_THREAD_STACK char g_MessageThreadStack[0x4000];

bool CANSAVE_SWITCH = false;

static void HandleMessageAutoLoop(void *arg) NN_NOEXCEPT

{
	NN_UNUSED(arg);

	for (;;) {
		auto message = nn::oe::PopNotificationMessage();
		switch (message) {
		case nn::oe::MessageFocusStateChanged:
			// Notifies when there has been a change to the program's focus state.
			// Does not notify based on the nn::oe::SetFocusHandlingMode() specification.
		{
			auto state = nn::oe::GetCurrentFocusState();
			switch (state) {
			case nn::oe::FocusState_InFocus:
				// In-focus state.
				break;
			case nn::oe::FocusState_OutOfFocus:
				// Out-of-focus state.
				break;
			case nn::oe::FocusState_Background:
				// BG focus state.
				break;
			}
		}
		break;

		case nn::oe::MessageResume:
			// Notifies when the application resumes from a suspended state.
			// Does not notify based on the nn::oe::SetResumeNotificationEnabled() specification.
			break;

		case nn::oe::MessageOperationModeChanged:
			// Notifies when the operation mode has changed between handheld mode and TV mode.
			// You can get the current operation mode using the nn::oe::GetOperationMode() function.
			// Does not notify based on the nn::oe::SetOperationModeChangedNotificationEnabled() specification.
			break;

		case nn::oe::MessagePerformanceModeChanged:
			// Notifies when the performance mode has changed between Normal mode and Boost mode.
			// You can get the current performance mode using the nn::oe::GetPerformanceMode() function.
			// Does not notify based on the nn::oe::SetPerformanceModeChangedNotificationEnabled() specification.
			break;

		case nn::oe::MessageExitRequest:
			// Notification to the program of an request to exit.
			// This notification is only sent if nn::oe::EnterExitRequestHandlingSection()
			// was called beforehand. The processes prior to existing are quickly performed, and
			// the application finally exits on the call to nn::oe::LeaveExitRequestHandlingSection().
			if (CANSAVE_SWITCH)
				NEED_TO_SAVE_AND_EXIT = true;
			else
				nn::oe::LeaveExitRequestHandlingSection();
			break;

		default:
			// Unknown messages will be ignored.
			NN_LOG("Unhandled message = 0x%08x\n", message);
			break;
		}
	}

	return;
}


extern "C" void nnMain()			// Window Show State
#elif PS4

static SceNpTrophyContext trophy_context;
static SceNpTrophyGameDetails trophy_game_details;
static ScePthread trophy_thread;
static std::condition_variable trophy_cond;
static std::mutex trophy_mutex;
static std::vector<int> trophy_unlock;

static void * trophy_thread_func(void * arg)
{
	SceNpTrophyHandle handle;
	sceNpTrophyCreateHandle(&handle);
	sceNpTrophyRegisterContext(trophy_context, handle, 0);

	sceNpTrophyGetGameInfo(trophy_context, handle, &trophy_game_details, NULL);

	printf("TrophyCount : %d\n", trophy_game_details.numTrophies);

	sceNpTrophyDestroyHandle(handle);

	while (true) {
		int trophy_id;
		{
			std::unique_lock<std::mutex> lock(trophy_mutex);

			if (trophy_unlock.empty())
				trophy_cond.wait(lock);

			if (trophy_unlock.empty())
				continue;

			trophy_id = trophy_unlock.back();
			trophy_unlock.pop_back();
		}

		sceNpTrophyCreateHandle(&handle);
		SceNpTrophyId id;
		printf("Unlock Trophy: %d\n", trophy_id);
		sceNpTrophyUnlockTrophy(trophy_context, handle, trophy_id, &id);
		sceNpTrophyDestroyHandle(handle);
	}
	return NULL;
}

void platform_unlock_achievement(int id)
{
	int trophy_id = id;
	printf("Unlock trophy add: %d\n", trophy_id);
	trophy_mutex.lock();
	trophy_unlock.push_back(trophy_id);
	trophy_cond.notify_all();
	trophy_mutex.unlock();
}


int main()
#endif
{

#ifdef SWITCH
	

	INIT_SWITCH();

	NN_LOG("INIT GL");

	IRenderModuleInit();
	IControlModuleInit();

	NN_LOG("INIT RENDER");

	gladLoadGLLoader(GLADloadproc(eglGetProcAddress));

	INIT_SOLOUD();
#elif PS4
	_Application.initialize();

	sceSysmoduleLoadModule(SCE_SYSMODULE_NP_TROPHY);
	int service_label = 0;
	sceNpTrophyCreateContext(&trophy_context, _Application._MainUserID, service_label, 0);
	{
		ScePthreadAttr attr;
		scePthreadAttrInit(&attr);
		scePthreadAttrSetstacksize(&attr, 128 * 1024);
		scePthreadCreate(&trophy_thread, &attr, trophy_thread_func, NULL,
			"TrophyThread");
		scePthreadAttrDestroy(&attr);
	}

	INIT_D3D_MTX();
	SET_CLIP_MATRIX();
	SET_MVS_MATRIX();

	for (int xyz = 0; xyz < TOTAL_NUM_TEXTURES; xyz++)
	{

		texture[xyz].tex = NULL;
		strcpy(texture[xyz].name, "NULL");
	}

	for (int xyz = 0; xyz < 500; xyz++)
	{
		texture_STOCK[xyz].tex = NULL;
		strcpy(texture_STOCK[xyz].name, "NULL");
	}

	counter_STOCK = 0;

	_Application.setSaveParam("Verdict Guilty", "Verdict Guilty Save", "Verdict Guilty save folder for options and unlocked contents.", "/app0/data/save_data.png", 10 * 1024);
	
	sceSystemServiceHideSplashScreen();
	
#endif

	int loop_timer=0;
    bool test=false;        
    int fps=0;           
    int FPS=0;
    int FrameTime=0; 
    int FrameTimer=0;  
    int frame_rate=0;
    int f_rate1=0;
    float jump_timing=0; 
    float testX=0.0f,testY=0.0f;      
    float testX1=0.0f, testY1=0.0f;
    float widthX=0.0f, heightY = 0.0f;
    float widthX1=0.0f, heightY1 = 0.0f;
    float midX=0.0f, midY=0.0f;    
    float distance = 0.0f; 
    int rnd=0;      
    int multi_select=0; 
    int dig_select=0;
    int plane_select=0;   
    int wood_select=0;     
    int work_select=0;               
    int food_select=0;        
    int carry_select=0;       
    int slash_select=0;    
    int cp_select=0;         
    int bk_select=0;       
    int cm_select=0;    
    int unit_sp_selected=-1;
    bool move_the_guy=false;    
    int the_worker=0;
    int dig_man=0;     
    int rank_man=0;
    int special_type = 0;     
    int k=0, l=0;   
    bool return_cargo=false;      
    bool building_selected=false; 
    int old_direction = 0;  
    int new_direction = 0;
    int test_player=0;                          
    int brush_id=0;                          
    int temp_index=0;                   
    int temp_row_x=0;                    
    int temp_row_y=0;          
    int row_x1=0;                
    int row_y1=0;          
    int sell_gold=0;                                     
    int m_check=-1;                                    
    bool knifing=false;                                   
    bool has_ammo=false;                                           
	int hud_weapon_addition =0; 
	float temp_speed=0.0f;    
	int col_index=-1;  
	int created_a_window=0;     
	int temp_horizontal = 0; 
	int temp_vertical = 0;


	//AudioDevicePtr device(OpenDevice("directsound")); 

	int device = 0;
//	if (!device) 
//	{
//		MessageBox(NULL, "Initialization of Audio Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
//	}

	memset(VG_CHARACTER_LOCKS, 0, sizeof(VG_CHARACTER_LOCKS));

	GetDisplaySettings(); //enumdisplaysettings

	//global_lpCmdLine = lpCmdLine;

//	MAX_horizontal = GetSystemMetrics(SM_CXSCREEN);
//	MAX_vertical   = GetSystemMetrics(SM_CYSCREEN);

	GetDesktopResolution(temp_horizontal, temp_vertical);
	 
	MAX_horizontal = temp_horizontal;    
	MAX_vertical = temp_vertical;
	      
	if(temp_horizontal < 1280)   
	{ 
		MAX_horizontal = 1280;
		MAX_vertical = 720;
	}

	if(temp_vertical < 720)  
	{
		MAX_horizontal = 1280;
		MAX_vertical = 720;
	}

	//if(DEMO_MODE == 0)                                               
    //{                                   
	  // Error.log            
      //remove("Server_error.log");    
      //fp2 = fopen("Server_error.log", "w");     
    //}     
	 
	time_diff=0;                          
	           
    sprite = new object[TOTAL_NO_SPRITES];          
    hud    = new object[TOTAL_NO_HUD]; 
    Fx     = new object[TOTAL_NO_FX_SPRITES];      
    
	memset(sprite, 0, sizeof(object)*TOTAL_NO_SPRITES );
    memset(hud, 0, sizeof(object)*TOTAL_NO_HUD );    
    memset(Fx, 0, sizeof(object)*TOTAL_NO_FX_SPRITES ); 
       
    memset(a_texture, 0, sizeof(animation_texture)*MAX_FX_ID );
                                
    fullscreen = true;                                               
		
#ifdef SWITCH
	STEAM_ACTIVE = false;
#elif defined PS4 || defined XB1
	STEAM_ACTIVE = true;
#endif
	#if IS_FULL_STEAM == 1
		//STEAM_ACTIVE = SteamAPI_Init(); 
	#endif

    LoadCFG();  
	   
    TimerInit();

#ifdef SWITCH

	Texture stexture_pixelsplash;

	LoadTGA(&stexture_pixelsplash, "Data/verdict/pixelheart.tga");

	glGenTextures(1, &stexture_pixelsplash.texID);

	glBindTexture(GL_TEXTURE_2D, stexture_pixelsplash.texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int type;
	if (stexture_pixelsplash.bpp == 24)
		type = GL_RGB;
	else
		type = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, type, stexture_pixelsplash.width, stexture_pixelsplash.height, 0, type, GL_UNSIGNED_BYTE, stexture_pixelsplash.imageData);

	if (stexture_pixelsplash.imageData)
	{
		free(stexture_pixelsplash.imageData);
	}

	int time_splash = CTimerGet();

	//TEST
	int timePassedSplash = 0;
	while (timePassedSplash < 2)
	{

		IRenderStart();
		IRenderClear(1 | 2, 0xff000000);
		IRenderState(1);

		
		glBindTexture(GL_TEXTURE_2D, stexture_pixelsplash.texID);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);   // setup a 10x10x2 viewing world
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);

		/* create a square on the XY
		   note that OpenGL origin is at the lower left
		   but texture origin is at upper left
		   => it has to be mirrored
		   (gasman knows why i have to mirror X as well) */
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2d(0, 0); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2d(0, 1); glVertex3f(0.0, 1.0, 0.0);
		glTexCoord2d(1, 1); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2d(1, 0); glVertex3f(1.0, 0.0, 0.0);
		glEnd();

		IRenderEnd();
		IRenderSwap();

		

		timePassedSplash = CTimerDifference(time_splash, CTimerGet());
		nn::TimeSpan time;
		nn::os::SleepThread(time.FromMilliSeconds(1000));
		//printf("timePassed = %d\n", timePassedSplash);
	}

#elif PS4
	Texture stexture_pixelsplash;

	int retval = _Application._GraphicsLoader->createTextureFromFile(&stexture_pixelsplash.texID, "/app0/data/verdict/pixelheart.png");
	if (retval == SCE_OK)
	{
		stexture_pixelsplash.texID->setAddrMode(sce::SampleUtil::Graphics::kTextureAddrModeClamp, sce::SampleUtil::Graphics::kTextureAddrModeClamp);
		stexture_pixelsplash.texID->setFilter(sce::SampleUtil::Graphics::kTextureFilterPoint, sce::SampleUtil::Graphics::kTextureFilterPoint, sce::SampleUtil::Graphics::kTextureMipFilterDisabled);
	}

	struct timespec time_splash;
	CTimerGet(&time_splash);

	//TEST
	int timePassedSplash = 0;
	while (timePassedSplash < 3000)
	{

		_Application.update();

		_Application.getGraphics()->beginScene(_Application.getGraphics()->getNextRenderTarget(), _Application.getGraphics()->getDepthStencilSurface());
		_Application.getGraphics()->clearRenderTarget(_Application.ClearScreenColor(0, 0, 0, 0));

		_Application.getGraphics()->setDepthWriteEnable(true);
		_Application.getGraphics()->setDepthFunc(sce::SampleUtil::Graphics::kDepthFuncAlways);

		_Application.getGraphics()->createIndexBuffer(&i_buffer, (sizeof(uint16_t) * 6));
		_Application.getGraphics()->createVertexBuffer(&v_buffer, (sizeof(TexturedVertex) * 4));

		indexData = (uint16_t*)i_buffer->beginWrite();
		vertexData = (TexturedVertex*)v_buffer->beginWrite();


		vertexData[0].position = sce::Vectormath::Simd::Aos::Vector2(0.0, 0.0);
		vertexData[1].position = sce::Vectormath::Simd::Aos::Vector2(1.0, 0.0);
		vertexData[2].position = sce::Vectormath::Simd::Aos::Vector2(0.0, 1.0);
		vertexData[3].position = sce::Vectormath::Simd::Aos::Vector2(1.0, 1.0);

		vertexData[0].texcoord = sce::Vectormath::Simd::Aos::Vector2(0.0, 0.0);
		vertexData[1].texcoord = sce::Vectormath::Simd::Aos::Vector2(1.0, 0.0);
		vertexData[2].texcoord = sce::Vectormath::Simd::Aos::Vector2(0.0, 1.0);
		vertexData[3].texcoord = sce::Vectormath::Simd::Aos::Vector2(1.0, 1.0);

		indexData[0] = 0;

		indexData[1] = 2;

		indexData[2] = 1;

		indexData[3] = 1;

		indexData[4] = 2;

		indexData[5] = 3;


		v_buffer->endWrite();
		i_buffer->endWrite();

		sce::SampleUtil::Graphics::VertexBuffer* VerticesStock[] = { v_buffer };
		_Application._SpriteRenderer->drawTextureVertex(_Application.getGraphics(), sce::Vectormath::Simd::Aos::Vector2(0, 0), sce::Vectormath::Simd::Aos::Vector2(1, 1),
			1.0, VerticesStock, i_buffer, 6, sce::Vectormath::Simd::Aos::Vector4(1.0, 1.0, 1.0, 1.0), sce::Vectormath::Simd::Aos::Vector4(0, 0, 0, 0), stexture_pixelsplash.texID, 1);

		sce::SampleUtil::destroy(i_buffer);
		sce::SampleUtil::destroy(v_buffer);

		_Application.getGraphics()->endScene();

		_Application.render();

		struct timespec t1;
		CTimerGet(&t1);
		timePassedSplash = CTimerDifference(time_splash, t1);
	}
#endif
	
	                       
	if(RENDERER == RENDER_OPENGL)                                                     
	{            
#ifdef SWITCH
		// Create Our OpenGL Window     
		if(!CreateGLWindow("Verdict Guilty™", sc_width, sc_height, sc_bits, fullscreen))
		{		 
			//MessageBox (HWND_DESKTOP, "Couldn't create gl_window", "Error", MB_OK | MB_ICONEXCLAMATION);
			//return 0;						 			// Quit If Window Was Not Created
		}                                                             
		else                     
		{           
			Set_Screen_Ratio();                     
			fade = 1.0f;    
			render_sequence = 0;             
			DrawGLScene(true, 1);

			//if(RENDERER == RENDER_OPENGL)
				//SwapBuffers(hDC);


			/*if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
			{  
				 TranslateMessage(&msg);				// Translate The Message    
				 DispatchMessage(&msg);					// Dispatch The Message             
			} */
			Set_Sprite(2, 0, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // BETA Logo          
			Animate(-1, -1);               
		}
#endif

	}

	#if IS_USING_DIRECTX == 1 
	 
	if(RENDERER == RENDER_DIRECTX) 
	{ 

	// Create Our DirectX Window
	if (!CreateDXWindow("Verdict Guilty™", sc_width, sc_height, sc_bits, fullscreen))
	{		 
        //MessageBox (HWND_DESKTOP, "Couldn't create directX_window", "Error", MB_OK | MB_ICONEXCLAMATION);
		return 0;						 			// Quit If Window Was Not Created
	}                                                       
    else          
    {           
		Set_Screen_Ratio();               
        fade = 1.0f;    
        render_sequence = 0;             
        DrawGLScene(true, 1);  

		/*if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{  
             TranslateMessage(&msg);				// Translate The Message    
             DispatchMessage(&msg);				// Dispatch The Message             
		}*/ 
        Set_Sprite(2, 0, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // BETA Logo          
        Animate(-1, -1);               
    }
	  
	} 
	   
    #endif               

    LoadCFG();         

	SoundEffectPtr vg_arrested_snd(OpenSoundEffect(device, "Data/SFX/VG_ARRESTED.wav", SINGLE)); // VG_GYEONG
	SoundEffectPtr vg_wasted_snd(OpenSoundEffect(device, "Data/SFX/VG_WASTED.wav", SINGLE)); // VG_GYEONG

	SoundEffectPtr vg_power1_snd(OpenSoundEffect(device, "Data/SFX/VG_POWER1.wav", SINGLE)); // VG_GYEONG
	SoundEffectPtr vg_power2_snd(OpenSoundEffect(device, "Data/SFX/VG_POWER2.wav", SINGLE)); // VG_SIU
 	SoundEffectPtr vg_power3_snd(OpenSoundEffect(device, "Data/SFX/VG_POWER3.wav", SINGLE)); // VG_MINSO
	SoundEffectPtr vg_power4_snd(OpenSoundEffect(device, "Data/SFX/VG_POWER4.wav", SINGLE)); // VG_REESE

	SoundEffectPtr vg_ko_1_snd(OpenSoundEffect(device, "Data/SFX/VG_KO_GYEONG.wav", SINGLE)); // VG_GYEONG
	SoundEffectPtr vg_ko_2_snd(OpenSoundEffect(device, "Data/SFX/VG_KO_SIU.wav", SINGLE)); // VG_SIU
 	SoundEffectPtr vg_ko_3_snd(OpenSoundEffect(device, "Data/SFX/VG_KO_MINSO.wav", SINGLE)); // VG_MINSO
	SoundEffectPtr vg_ko_4_snd(OpenSoundEffect(device, "Data/SFX/VG_KO_REESE.wav", SINGLE)); // VG_REESE
	SoundEffectPtr vg_ko_5_snd(OpenSoundEffect(device, "Data/SFX/VG_KO_YOHAN.wav", SINGLE)); // VG_YOHAN
	SoundEffectPtr vg_ko_6_snd(OpenSoundEffect(device, "Data/SFX/VG_KO_JAE.wav", SINGLE)); // VG_JAE
	SoundEffectPtr vg_ko_7_snd(OpenSoundEffect(device, "Data/SFX/VG_KO_GUN.wav", SINGLE)); // VG_GUN
	SoundEffectPtr vg_ko_8_snd(OpenSoundEffect(device, "Data/SFX/VG_KO_HYUK.wav", SINGLE)); // VG_HYUK
	SoundEffectPtr vg_ko_9_snd(OpenSoundEffect(device, "Data/SFX/VG_KO_SANG.wav", SINGLE)); // VG_SANG
	SoundEffectPtr vg_ko_10_snd(OpenSoundEffect(device, "Data/SFX/VG_KO_TRAINER.wav", SINGLE)); // VG_SANG
	SoundEffectPtr vg_ko_11_snd(OpenSoundEffect(device, "Data/SFX/VG_KO_SIU.wav", SINGLE)); // VG_SHO
	SoundEffectPtr vg_ko_12_snd(OpenSoundEffect(device, "Data/SFX/VG_KO_MINSO.wav", SINGLE)); // VG_TIA
	SoundEffectPtr vg_ko_13_snd(OpenSoundEffect(device, "Data/SFX/VG_KO_GYEONG.wav", SINGLE)); // VG_SAIZO
	SoundEffectPtr vg_ko_14_snd(OpenSoundEffect(device, "Data/SFX/VG_KO_GUN.wav", SINGLE)); // VG_KENNEDY

    SoundEffectPtr vg_shout_snd(OpenSoundEffect(device, "Data/SFX/VG_SHOUT.wav", SINGLE)); 
    SoundEffectPtr vg_siren_snd(OpenSoundEffect(device, "Data/SFX/VG_SIREN.wav", SINGLE));  

    SoundEffectPtr vg_title_move(OpenSoundEffect(device, "Data/SFX/TS_CHARMOVE.wav", SINGLE)); 
    SoundEffectPtr vg_title_select(OpenSoundEffect(device, "Data/SFX/TS_CHARSELECT.wav", SINGLE));    
              
    SoundEffectPtr vg_perfect_snd(OpenSoundEffect(device, "Data/SFX/VG_perfect.wav", SINGLE));
    SoundEffectPtr vg_amb_car1_snd(OpenSoundEffect(device, "Data/SFX/VG_AMB_CAR1.ogg", MULTIPLE));
    SoundEffectPtr vg_amb_car2_snd(OpenSoundEffect(device, "Data/SFX/VG_AMB_CAR2.ogg", MULTIPLE));  
    
    SoundEffectPtr vg_ko_snd(OpenSoundEffect(device, "Data/SFX/VG_hit_KO1.wav", SINGLE)); // Dieing sound
    SoundEffectPtr vg_ko1_snd(OpenSoundEffect(device, "Data/SFX/VG_hit_KO2.wav", SINGLE)); // Dieing sound
    SoundEffectPtr vg_ko2_snd(OpenSoundEffect(device, "Data/SFX/VG_hit_KO3.wav", SINGLE)); // Dieing sound
    SoundEffectPtr vg_ko3_snd(OpenSoundEffect(device, "Data/SFX/VG_hit_KO4.wav", SINGLE)); // Dieing sound

    SoundEffectPtr vg_fight_snd(OpenSoundEffect(device, "Data/SFX/VG_FIGHT.wav", SINGLE));   // Fight voice
                    
    SoundEffectPtr vg_blocked_snd(OpenSoundEffect(device, "Data/SFX/VG_BLOCKED.wav", SINGLE));   // Punching sound 
    SoundEffectPtr vg_knockdown_snd(OpenSoundEffect(device, "Data/SFX/VG_KNOCKSLIDE.wav", SINGLE));   // Punching sound 

	SoundEffectPtr vg_stamp_snd(OpenSoundEffect(device, "Data/SFX/VG_STAMP.wav", SINGLE));   // Punching sound 

    SoundEffectPtr vg_round1_snd(OpenSoundEffect(device, "Data/SFX/VG_rnd1.wav", SINGLE));  
    SoundEffectPtr vg_round2_snd(OpenSoundEffect(device, "Data/SFX/VG_rnd2.wav", SINGLE));
    SoundEffectPtr vg_round3_snd(OpenSoundEffect(device, "Data/SFX/VG_rnd3.wav", SINGLE));
    SoundEffectPtr vg_round4_snd(OpenSoundEffect(device, "Data/SFX/VG_rnd4.wav", SINGLE)); 
    SoundEffectPtr vg_round5_snd(OpenSoundEffect(device, "Data/SFX/VG_rnd5.wav", SINGLE)); 
    SoundEffectPtr vg_round6_snd(OpenSoundEffect(device, "Data/SFX/VG_rnd6.wav", SINGLE));
 	       
	SoundEffectPtr VG_title_snd(OpenSoundEffect(device, "Data/SFX/VG_TITLE.wav", SINGLE)); 
	SoundEffectPtr VG_verdict_snd(OpenSoundEffect(device, "Data/SFX/VG_VERDICT.wav", SINGLE)); 
	SoundEffectPtr VG_guilty_snd(OpenSoundEffect(device, "Data/SFX/VG_GUILTY.wav", SINGLE)); 
	SoundEffectPtr VG_destiny_snd(OpenSoundEffect(device, "Data/SFX/VG_DESTINY.wav", SINGLE)); 
	SoundEffectPtr VG_pow_snd(OpenSoundEffect(device, "Data/SFX/VG_POW.wav", SINGLE));

	SoundEffectPtr VG_titlevoice_snd(OpenSoundEffect(device, "Data/SFX/VG_TITLEVOICE.wav", SINGLE));

	SoundEffectPtr VG_alright_snd(OpenSoundEffect(device, "Data/SFX/VG_ALRIGHT.wav", SINGLE)); 
	SoundEffectPtr VG_nice_snd(OpenSoundEffect(device, "Data/SFX/VG_NICE.wav", SINGLE)); 
	SoundEffectPtr VG_okay_snd(OpenSoundEffect(device, "Data/SFX/VG_OKAY.wav", SINGLE)); 
	SoundEffectPtr VG_good_snd(OpenSoundEffect(device, "Data/SFX/VG_GOOD.wav", SINGLE));
	SoundEffectPtr VG_great_snd(OpenSoundEffect(device, "Data/SFX/VG_GREAT.wav", SINGLE)); 
	SoundEffectPtr VG_excellent_snd(OpenSoundEffect(device, "Data/SFX/VG_EXCELLENT.wav", SINGLE)); 

	SoundEffectPtr gyeong_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_GYEONG.wav", SINGLE));   
	SoundEffectPtr siu_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_SIU.wav", SINGLE)); 
	SoundEffectPtr hyuk_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_HYUK.wav", SINGLE)); 
	SoundEffectPtr gun_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_GUN.wav", SINGLE));
	SoundEffectPtr jae_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_JAE.wav", SINGLE));
	SoundEffectPtr minso_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_MINSO.wav", SINGLE));
	SoundEffectPtr reese_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_REESE.wav", SINGLE)); 
	SoundEffectPtr yohan_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_YOHAN.wav", SINGLE));
	SoundEffectPtr sang_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_SANG.wav", SINGLE));
	SoundEffectPtr trainer_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_TRAINER.wav", SINGLE));

	SoundEffectPtr gyeong2_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_GYEONG.wav", SINGLE));   
	SoundEffectPtr siu2_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_SIU.wav", SINGLE)); 
	SoundEffectPtr hyuk2_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_HYUK.wav", SINGLE)); 
	SoundEffectPtr gun2_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_GUN.wav", SINGLE));
	SoundEffectPtr jae2_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_JAE.wav", SINGLE));
	SoundEffectPtr minso2_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_MINSO.wav", SINGLE));
	SoundEffectPtr reese2_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_REESE.wav", SINGLE)); 
	SoundEffectPtr yohan2_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_YOHAN.wav", SINGLE));
	SoundEffectPtr sang2_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_SANG.wav", SINGLE));
	SoundEffectPtr trainer2_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_TRAINER.wav", SINGLE));
	   
	SoundEffectPtr WIN_gyeong_snd(OpenSoundEffect(device, "Data/SFX/VG_WIN_GYEONG.wav", SINGLE));   
	SoundEffectPtr WIN_siu_snd(OpenSoundEffect(device, "Data/SFX/VG_WIN_SIU.wav", SINGLE)); 
	SoundEffectPtr WIN_hyuk_snd(OpenSoundEffect(device, "Data/SFX/VG_WIN_HYUK.wav", SINGLE));
	SoundEffectPtr WIN_gun_snd(OpenSoundEffect(device, "Data/SFX/VG_WIN_GUN.wav", SINGLE)); 
	SoundEffectPtr WIN_jae_snd(OpenSoundEffect(device, "Data/SFX/VG_WIN_JAE.wav", SINGLE));
	SoundEffectPtr WIN_minso_snd(OpenSoundEffect(device, "Data/SFX/VG_WIN_MINSO.wav", SINGLE));
	SoundEffectPtr WIN_reese_snd(OpenSoundEffect(device, "Data/SFX/VG_WIN_REESE.wav", SINGLE));
	SoundEffectPtr WIN_yohan_snd(OpenSoundEffect(device, "Data/SFX/VG_WIN_YOHAN.wav", SINGLE));
	SoundEffectPtr WIN_sang_snd(OpenSoundEffect(device, "Data/SFX/VG_WIN_SANG.wav", SINGLE));
	SoundEffectPtr WIN_trainer_snd(OpenSoundEffect(device, "Data/SFX/VG_WIN_TRAINER.wav", SINGLE));

	SoundEffectPtr YELL_gyeong_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_GYEONG.wav", SINGLE));   
	SoundEffectPtr YELL_siu_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_SIU.wav", SINGLE)); 
	SoundEffectPtr YELL_hyuk_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_HYUK.wav", SINGLE)); 
	SoundEffectPtr YELL_gun_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_GUN.wav", SINGLE)); 
	SoundEffectPtr YELL_jae_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_JAE.wav", SINGLE));
	SoundEffectPtr YELL_minso_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_MINSO.wav", SINGLE)); 
	SoundEffectPtr YELL_reese_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_REESE.wav", SINGLE)); 
	SoundEffectPtr YELL_yohan_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_YOHAN.wav", SINGLE));
	SoundEffectPtr YELL_sang_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_SANG.wav", SINGLE));
	SoundEffectPtr YELL_trainer_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_TRAINER.wav", SINGLE));

	SoundEffectPtr YELL_judge_snd(OpenSoundEffect(device, "Data/SFX/VG_YELL_JUDGE.wav", SINGLE));

    SoundEffectPtr vg_gameover_snd(OpenSoundEffect(device, "Data/SFX/VG_GAME_OVER.wav", SINGLE)); // Special voice
                                        
    SoundEffectPtr vg_titleselect_snd(OpenSoundEffect(device, "Data/SFX/TS_TITLESELECT.wav", SINGLE));
                                                
    SoundEffectPtr vg_titlemove_snd(OpenSoundEffect(device, "Data/SFX/TS_TITLEMOVE.wav", SINGLE)); //vg_titlemove
    
    SoundEffectPtr vg_break_snd(OpenSoundEffect(device, "Data/SFX/VG_BREAK.wav", MULTIPLE));
    SoundEffectPtr vg_knife_snd(OpenSoundEffect(device, "Data/SFX/VG_KNIFE.wav", MULTIPLE));

	SoundEffectPtr vg_vacuum_snd(OpenSoundEffect(device, "Data/SFX/VG_VACUUM.wav", MULTIPLE));

    SoundEffectPtr vg_orb_snd(OpenSoundEffect(device, "Data/SFX/VG_VACUUM.wav", MULTIPLE));
    SoundEffectPtr vg_orb2_snd(OpenSoundEffect(device, "Data/SFX/VG_VACUUM.wav", MULTIPLE));                            
                                          
    SoundEffectPtr vg_pistol1_snd(OpenSoundEffect(device, "Data/SFX/VG_PISTOL.wav", SINGLE));          
    SoundEffectPtr vg_pistol2_snd(OpenSoundEffect(device, "Data/SFX/VG_PISTOL.wav", SINGLE)); 
 
    SoundEffectPtr vg_shotgun1_snd(OpenSoundEffect(device, "Data/SFX/VG_SHOTGUN.wav", SINGLE));
    SoundEffectPtr vg_shotgun2_snd(OpenSoundEffect(device, "Data/SFX/VG_SHOTGUN.wav", SINGLE));

    SoundEffectPtr vg_ric1_snd(OpenSoundEffect(device, "Data/SFX/VG_RIC1.wav", SINGLE));       
    SoundEffectPtr vg_ric2_snd(OpenSoundEffect(device, "Data/SFX/VG_RIC2.wav", SINGLE));    
    SoundEffectPtr vg_ric3_snd(OpenSoundEffect(device, "Data/SFX/VG_RIC3.wav", SINGLE));               
       
                                                     
    SoundEffectPtr vg_shock_snd(OpenSoundEffect(device, "Data/SFX/VG_SHOCK.wav", SINGLE));  


    SoundEffectPtr vg_reload_snd(OpenSoundEffect(device, "Data/SFX/VG_RELOAD.wav", SINGLE)); 
    SoundEffectPtr vg_reloaded_snd(OpenSoundEffect(device, "Data/SFX/VG_RELOADED.wav", SINGLE)); 
 
    SoundEffectPtr vg_mgun_snd(OpenSoundEffect(device, "Data/SFX/VG_MGUN.wav", MULTIPLE));    
               
    SoundEffectPtr vg_glass1_snd(OpenSoundEffect(device, "Data/SFX/VG_GLASS1.wav", MULTIPLE));
    SoundEffectPtr vg_glass2_snd(OpenSoundEffect(device, "Data/SFX/VG_GLASS2.wav", MULTIPLE));
    SoundEffectPtr vg_glass3_snd(OpenSoundEffect(device, "Data/SFX/VG_GLASS3.wav", MULTIPLE));
    SoundEffectPtr vg_glass4_snd(OpenSoundEffect(device, "Data/SFX/VG_GLASS4.wav", MULTIPLE));

                 
    SoundEffectPtr vg_dogattack_snd(OpenSoundEffect(device, "Data/SFX/VG_DOGATTACK.wav", MULTIPLE));

    SoundEffectPtr vg_verdict_snd(OpenSoundEffect(device, "Data/SFX/VG_VERDICT.wav", SINGLE));

    SoundEffectPtr vg_knockslide_snd(OpenSoundEffect(device, "Data/SFX/VG_knockslide_fx.wav", SINGLE)); // VG_KNOCKSLIDE.wav

	SoundEffectPtr VG_land_snd(OpenSoundEffect(device, "Data/SFX/VG_land_fx.wav", MULTIPLE));

          	                          
    SoundEffectPtr vg_tink_snd(OpenSoundEffect(device, "Data/SFX/VG_TINK.wav", MULTIPLE));
      	    
    SoundEffectPtr vg_chop_snd(OpenSoundEffect(device, "Data/SFX/VG_whoosh1.wav", MULTIPLE));
	SoundEffectPtr vg_chop1_snd(OpenSoundEffect(device, "Data/SFX/VG_whoosh2.wav", MULTIPLE));
	SoundEffectPtr vg_chop2_snd(OpenSoundEffect(device, "Data/SFX/VG_whoosh3.wav", MULTIPLE));
	SoundEffectPtr vg_chop3_snd(OpenSoundEffect(device, "Data/SFX/VG_whoosh4.wav", MULTIPLE));
       	                   
    SoundEffectPtr vg_splat_snd(OpenSoundEffect(device, "Data/SFX/VG_SPLAT.wav", MULTIPLE));

    SoundEffectPtr vg_explode_snd(OpenSoundEffect(device, "Data/SFX/VG_EXPLODE.wav", MULTIPLE));

    SoundEffectPtr vg_hitsound_snd(OpenSoundEffect(device, "Data/SFX/VG_hit_soft1.wav", SINGLE));    
    SoundEffectPtr vg_hitsound1_snd(OpenSoundEffect(device, "Data/SFX/VG_hit_soft2.wav", SINGLE));
    SoundEffectPtr vg_hitsound2_snd(OpenSoundEffect(device, "Data/SFX/VG_hit_soft3.wav", SINGLE));
    SoundEffectPtr vg_hitsound3_snd(OpenSoundEffect(device, "Data/SFX/VG_hit_soft4.wav", SINGLE));     
    SoundEffectPtr vg_hitsound4_snd(OpenSoundEffect(device, "Data/SFX/VG_hit_hard1.wav", SINGLE));
    SoundEffectPtr vg_hitsound5_snd(OpenSoundEffect(device, "Data/SFX/VG_hit_hard2.wav", SINGLE));
    SoundEffectPtr vg_hitsound6_snd(OpenSoundEffect(device, "Data/SFX/VG_hit_hard3.wav", SINGLE));
    SoundEffectPtr vg_hitsound7_snd(OpenSoundEffect(device, "Data/SFX/VG_hit_hard4.wav", SINGLE));


    SoundEffectPtr vg_win_snd(OpenSoundEffect(device, "Data/SFX/VG_WIN.wav", SINGLE));
                    
    SoundEffectPtr vg_lose_snd(OpenSoundEffect(device, "Data/SFX/VG_LOSE.wav", SINGLE));
                  

        render_sequence = 0;                                         
        DrawGLScene(true, 1);  
		//if(RENDERER == RENDER_OPENGL)        
			//SwapBuffers(hDC);

		/*if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{  
            TranslateMessage(&msg);				// Translate The Message    
             DispatchMessage(&msg);				// Dispatch The Message             
		} */
        Set_Sprite(2, 1, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // BETA Logo          
        Animate(-1, -1);  
                      

        render_sequence = 0;              
        DrawGLScene(true, 1);  
		      
		//if(RENDERER == RENDER_OPENGL)             
			//SwapBuffers(hDC);                         
		  
		/*if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{  
            TranslateMessage(&msg);				// Translate The Message     
             DispatchMessage(&msg);				// Dispatch The Message             
		}   */
		  
        Set_Sprite(2, 2, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // BETA Logo          
        Animate(-1, -1);                                                                                      
                                                                                                                  	                                                                                       
		OutputStreamPtr emy1_snd(OpenSound(device, "Data/SFX/BG_ALLEYWAY.ogg", STREAM_MUSIC));        // Title screen 
		OutputStreamPtr emy2_snd(OpenSound(device, "Data/SFX/BG_TRAIN.ogg", STREAM_MUSIC));        // Title screen 
		OutputStreamPtr emy3_snd(OpenSound(device, "Data/SFX/BG_TRAFFIC.ogg", STREAM_MUSIC));        // Title screen 
		OutputStreamPtr emy4_snd(OpenSound(device, "Data/SFX/BG_PARK.ogg", STREAM_MUSIC));        // Title screen 
		OutputStreamPtr emy5_snd(OpenSound(device, "Data/SFX/BG_BIKESHOP.ogg", STREAM_MUSIC));        // Title screen 
		OutputStreamPtr emy6_snd(OpenSound(device, "Data/SFX/BG_NIGHTCLUB.ogg", STREAM_MUSIC));        // Title screen
		OutputStreamPtr emy7_snd(OpenSound(device, "Data/SFX/BG_PRISON.ogg", STREAM_MUSIC));        // Title screen 
		OutputStreamPtr emy8_snd(OpenSound(device, "Data/SFX/BG_HIGHWAY.ogg", STREAM_MUSIC));        // Title screen 
		OutputStreamPtr emy9_snd(OpenSound(device, "Data/SFX/BG_COURT.ogg", STREAM_MUSIC));        // Title screen 
		OutputStreamPtr emy10_snd(OpenSound(device, "Data/SFX/BG_DOJO.ogg", STREAM_MUSIC));        // Title screen 
		OutputStreamPtr emy11_snd(OpenSound(device, "Data/SFX/BG_AIRPORT.ogg", STREAM_MUSIC));  
		OutputStreamPtr emy12_snd(OpenSound(device, "Data/SFX/BG_ROOFTOPS.ogg", STREAM_MUSIC));  
		OutputStreamPtr emy13_snd(OpenSound(device, "Data/SFX/BG_CAFE.ogg", STREAM_MUSIC));  
		OutputStreamPtr emy14_snd(OpenSound(device, "Data/SFX/BG_RING.ogg", STREAM_MUSIC)); 

		OutputStreamPtr jet1_snd(OpenSound(device, "Data/SFX/VG_VS.ogg", STREAM_MUSIC));      // Old Radio system 
		OutputStreamPtr jet2_snd(OpenSound(device, "Data/SFX/VG_GAMEOVER.ogg", STREAM_MUSIC));      // Old Radio system 
		OutputStreamPtr jet3_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));      // Old Radio system 
		OutputStreamPtr jet4_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));      // Old Radio system 

		OutputStreamPtr siege1_snd(OpenSound(device, "Data/SFX/CS_DANGER1.ogg", STREAM_MUSIC));      // Old Radio system  
        OutputStreamPtr siege2_snd(OpenSound(device, "Data/SFX/CS_DANGER2.ogg", STREAM_MUSIC));      // Old Radio system
        OutputStreamPtr siege3_snd(OpenSound(device, "Data/SFX/CS_VICTORY.ogg", STREAM_MUSIC));      // Old Radio system
        OutputStreamPtr siege4_snd(OpenSound(device, "Data/SFX/CS_ENDING.ogg", STREAM_MUSIC));      // Old Radio system
        OutputStreamPtr siege5_snd(OpenSound(device, "Data/SFX/CS_BOSSIDLE.ogg", STREAM_MUSIC));      // Old Radio system
        OutputStreamPtr siege6_snd(OpenSound(device, "Data/SFX/CS_IDLE.ogg", STREAM_MUSIC));      // Old Radio system

        render_sequence = 0;                                                     
        DrawGLScene(true, 1);                                  
		                              
		//if(RENDERER == RENDER_OPENGL)         
			//SwapBuffers(hDC); 
		  
		/*if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{  
            TranslateMessage(&msg);				// Translate The Message    
             DispatchMessage(&msg);				// Dispatch The Message             
		} */
        Set_Sprite(2, 3, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // BETA Logo          
        Animate(-1, -1);             
                              
    OutputStreamPtr map_grass_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));        // Credits screen
    OutputStreamPtr map_swamp_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));        // Credits screen
    OutputStreamPtr map_forest_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));        // Credits screen
    OutputStreamPtr map_farm_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));        // Credits screen
    OutputStreamPtr map_snow_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));        // Credits screen
    OutputStreamPtr map_desert_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));        // Credits screen
	OutputStreamPtr map_trench_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));        // Credits screen

    OutputStreamPtr lnd_snd(OpenSound(device, "Data/SFX/CS_ENDING.ogg", STREAM_MUSIC));       // File select screen
    OutputStreamPtr theatre_snd(OpenSound(device, "Data/SFX/CS_INTRO.ogg", STREAM_MUSIC));      // Old Radio system     
    OutputStreamPtr credits1_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));      // Old Radio system 
    OutputStreamPtr credits2_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));      // Old Radio system 
    OutputStreamPtr credits3_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));      // Old Radio system 

        render_sequence = 0;                     
        DrawGLScene(true, 1);                       
		              
		//if(RENDERER == RENDER_OPENGL)                     
			//SwapBuffers(hDC);

		/*if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{  
            TranslateMessage(&msg);				// Translate The Message    
             DispatchMessage(&msg);				// Dispatch The Message             
		} */
        Set_Sprite(2, 4, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // BETA Logo           
        Animate(-1, -1);        
           
    OutputStreamPtr crd_snd(OpenSound(device, "Data/SFX/VG_SELECT.ogg", STREAM_MUSIC));
            
    OutputStreamPtr army_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));  
                        
        render_sequence = 0;                                 
        DrawGLScene(true, 1);    
		       
		//if(RENDERER == RENDER_OPENGL)                               
			//SwapBuffers(hDC);                  

		/*if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{  
            TranslateMessage(&msg);				// Translate The Message    
             DispatchMessage(&msg);				// Dispatch The Message             
		} */

        Set_Sprite(2, 5, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // BETA Logo           
        Animate(-1, -1);              
         
    OutputStreamPtr fight_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));
            
    OutputStreamPtr sad_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));    
            
    OutputStreamPtr intro_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC)); 
            
    OutputStreamPtr mini_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC)); 
            
    OutputStreamPtr deathscreen_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC)); 
                        
    OutputStreamPtr urgency_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC)); 
                
    OutputStreamPtr fanfare_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC)); 
                
    OutputStreamPtr fanfare2_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC)); 
                          
        render_sequence = 0;                                                                                             
        DrawGLScene(true, 1);            
		            
		//if(RENDERER == RENDER_OPENGL)                      
			//SwapBuffers(hDC); 
		 
		/*if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{  
            TranslateMessage(&msg);				// Translate The Message    
             DispatchMessage(&msg);				// Dispatch The Message             
		} */
        Set_Sprite(2, 6, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // BETA Logo          
        Animate(-1, -1);      
           
    OutputStreamPtr dgnb_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));  
            
    OutputStreamPtr final_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));  
            
    OutputStreamPtr dangers_snd(OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC));  
                      
        render_sequence = 0;           
        DrawGLScene(true, 1);  

		//if(RENDERER == RENDER_OPENGL)
			//SwapBuffers(hDC);

		/*if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{  
            TranslateMessage(&msg);				// Translate The Message    
             DispatchMessage(&msg);				// Dispatch The Message             
		}  */
        Set_Sprite(2, 7, ONCE, ANIM_SPRITE, ANIM_NOT_WALKING); // BETA Logo          
        Animate(-1, -1);                    
    
    OutputStreamPtr vg_amb_prison_snd(OpenSound(device, "Data/SFX/VG_AMB_PRISON.ogg", STREAM_MUSIC)); 
            
    OutputStreamPtr vg_amb_traffic_snd(OpenSound(device, "Data/SFX/VG_AMB_TRAFFIC.ogg", STREAM_MUSIC)); 

	OutputStreamPtr vg_amb_subway_snd(OpenSound(device, "Data/SFX/VG_AMB_SUBWAY.ogg", STREAM_MUSIC)); 

    OutputStreamPtr vg_amb_van_snd(OpenSound(device, "Data/SFX/VG_VAN.ogg", STREAM_MUSIC));

    OutputStreamPtr vg_amb_duel_snd(OpenSound(device, "Data/SFX/VG_AMB_DUEL.ogg", STREAM_MUSIC));

    vg_perfect_snd->setVolume(sfx_volume);      
    vg_amb_car1_snd->setVolume(sfx_volume);             
    vg_amb_car2_snd->setVolume(sfx_volume);   
         
    vg_ko_snd->setVolume(sfx_volume);       
    vg_ko1_snd->setVolume(sfx_volume); 
	vg_ko2_snd->setVolume(sfx_volume); 
    vg_ko3_snd->setVolume(sfx_volume); 
              
                            
    vg_amb_subway_snd->setVolume(sfx_volume);     
    vg_fight_snd->setVolume(sfx_volume);

    VG_title_snd->setVolume(sfx_volume);   
	    
    gyeong_snd->setVolume(sfx_volume);
    siu_snd->setVolume(sfx_volume);
    minso_snd->setVolume(sfx_volume);    
    reese_snd->setVolume(sfx_volume);       
    yohan_snd->setVolume(sfx_volume);
    jae_snd->setVolume(sfx_volume);
    gun_snd->setVolume(sfx_volume);
    hyuk_snd->setVolume(sfx_volume); 
    sang_snd->setVolume(sfx_volume);
    trainer_snd->setVolume(sfx_volume);
	    
    gyeong2_snd->setVolume(sfx_volume);
    siu2_snd->setVolume(sfx_volume);
    minso2_snd->setVolume(sfx_volume);    
    reese2_snd->setVolume(sfx_volume);       
    yohan2_snd->setVolume(sfx_volume);
    jae2_snd->setVolume(sfx_volume);
    gun2_snd->setVolume(sfx_volume);
    hyuk2_snd->setVolume(sfx_volume); 
    sang2_snd->setVolume(sfx_volume);
    trainer2_snd->setVolume(sfx_volume);

    WIN_gyeong_snd->setVolume(sfx_volume);
    WIN_siu_snd->setVolume(sfx_volume);
    WIN_minso_snd->setVolume(sfx_volume);
    WIN_reese_snd->setVolume(sfx_volume);
    WIN_yohan_snd->setVolume(sfx_volume);
    WIN_jae_snd->setVolume(sfx_volume);
    WIN_gun_snd->setVolume(sfx_volume);
    WIN_hyuk_snd->setVolume(sfx_volume);
    WIN_sang_snd->setVolume(sfx_volume);
    WIN_trainer_snd->setVolume(sfx_volume);

    YELL_gyeong_snd->setVolume(sfx_volume);
    YELL_siu_snd->setVolume(sfx_volume);
    YELL_minso_snd->setVolume(sfx_volume);
    YELL_reese_snd->setVolume(sfx_volume);
    YELL_yohan_snd->setVolume(sfx_volume);
    YELL_jae_snd->setVolume(sfx_volume);
    YELL_gun_snd->setVolume(sfx_volume);
    YELL_hyuk_snd->setVolume(sfx_volume);
    YELL_sang_snd->setVolume(sfx_volume);
    YELL_trainer_snd->setVolume(sfx_volume);

    YELL_judge_snd->setVolume(sfx_volume);

    vg_blocked_snd->setVolume(sfx_volume);   

    vg_knockdown_snd->setVolume(sfx_volume);  

    vg_stamp_snd->setVolume(sfx_volume);   
    
    vg_titlemove_snd->setVolume(sfx_volume);



	vg_arrested_snd->setVolume(sfx_volume);
	vg_wasted_snd->setVolume(sfx_volume);

    vg_power1_snd->setVolume(sfx_volume);
    vg_power2_snd->setVolume(sfx_volume);
    vg_power3_snd->setVolume(sfx_volume);
    vg_power4_snd->setVolume(sfx_volume);

    vg_ko_1_snd->setVolume(sfx_volume);
    vg_ko_2_snd->setVolume(sfx_volume);
    vg_ko_3_snd->setVolume(sfx_volume);
    vg_ko_4_snd->setVolume(sfx_volume);
    vg_ko_5_snd->setVolume(sfx_volume);
    vg_ko_6_snd->setVolume(sfx_volume);
    vg_ko_7_snd->setVolume(sfx_volume);
    vg_ko_8_snd->setVolume(sfx_volume);
    vg_ko_9_snd->setVolume(sfx_volume);
    vg_ko_10_snd->setVolume(sfx_volume);
    vg_ko_11_snd->setVolume(sfx_volume);
    vg_ko_12_snd->setVolume(sfx_volume);
    vg_ko_13_snd->setVolume(sfx_volume);
    vg_ko_14_snd->setVolume(sfx_volume);

    vg_shout_snd->setVolume(sfx_volume);
    vg_siren_snd->setVolume(sfx_volume);

    vg_title_move->setVolume(sfx_volume);
    vg_title_select->setVolume(sfx_volume);
        
    vg_round1_snd->setVolume(sfx_volume);
    vg_round2_snd->setVolume(sfx_volume);  
    vg_round3_snd->setVolume(sfx_volume);  
    vg_round4_snd->setVolume(sfx_volume);  
    vg_round5_snd->setVolume(sfx_volume);  
    vg_round6_snd->setVolume(sfx_volume);  
    
    vg_gameover_snd->setVolume(sfx_volume);

            
    vg_titleselect_snd->setVolume(sfx_volume);
           
 
	vg_knife_snd->setVolume(sfx_volume);
	vg_break_snd->setVolume(sfx_volume);

	vg_vacuum_snd->setVolume(sfx_volume);

	vg_orb_snd->setVolume(sfx_volume);
	vg_orb2_snd->setVolume(sfx_volume);

    vg_pistol1_snd->setVolume(sfx_volume);    
    vg_pistol2_snd->setVolume(sfx_volume);    

        
    vg_ric1_snd->setVolume(sfx_volume);
    vg_ric2_snd->setVolume(sfx_volume);
    vg_ric3_snd->setVolume(sfx_volume);

            
    vg_shock_snd->setVolume(sfx_volume);
                                    

    vg_reload_snd->setVolume(sfx_volume);
    vg_reloaded_snd->setVolume(sfx_volume);

    
    vg_mgun_snd->setVolume(sfx_volume);

         
    vg_glass1_snd->setVolume(sfx_volume);     
    vg_glass2_snd->setVolume(sfx_volume);  
    vg_glass3_snd->setVolume(sfx_volume);  
    vg_glass4_snd->setVolume(sfx_volume);  
   
	vg_dogattack_snd->setVolume(sfx_volume);


    VG_land_snd->setVolume(sfx_volume);

        
    vg_shotgun1_snd->setVolume(sfx_volume); 
    vg_shotgun2_snd->setVolume(sfx_volume); 
              
    vg_tink_snd->setVolume(sfx_volume);   
    
    vg_chop_snd->setVolume(sfx_volume);        
    vg_chop1_snd->setVolume(sfx_volume); 
    vg_chop2_snd->setVolume(sfx_volume); 
    vg_chop3_snd->setVolume(sfx_volume); 
    
    vg_hitsound_snd->setVolume(sfx_volume);  
    vg_hitsound1_snd->setVolume(sfx_volume);  
    vg_hitsound2_snd->setVolume(sfx_volume);  
    vg_hitsound3_snd->setVolume(sfx_volume);   
    vg_hitsound4_snd->setVolume(sfx_volume);  
    vg_hitsound5_snd->setVolume(sfx_volume);  
    vg_hitsound6_snd->setVolume(sfx_volume);  
    vg_hitsound7_snd->setVolume(sfx_volume);  
         
    vg_splat_snd->setVolume(sfx_volume);  
	  
	vg_explode_snd->setVolume(sfx_volume);  
        
    vg_win_snd->setVolume(sfx_volume);   

    vg_lose_snd->setVolume(sfx_volume);         

    vg_verdict_snd->setVolume(sfx_volume); 
    vg_knockslide_snd->setVolume(sfx_volume); 

    emy1_snd->setVolume(music_volume);                 
    emy1_snd->setRepeat(true);  
    emy2_snd->setVolume(music_volume);                 
    emy2_snd->setRepeat(true);  
    emy3_snd->setVolume(music_volume);                 
    emy3_snd->setRepeat(true);  
    emy4_snd->setVolume(music_volume);                 
    emy4_snd->setRepeat(true);  
    emy5_snd->setVolume(music_volume);                 
    emy5_snd->setRepeat(true);  
    emy6_snd->setVolume(music_volume);                 
    emy6_snd->setRepeat(true);  
    emy7_snd->setVolume(music_volume);                 
    emy7_snd->setRepeat(true);  
    emy8_snd->setVolume(music_volume);                 
    emy8_snd->setRepeat(true);  
    emy9_snd->setVolume(music_volume);                 
    emy9_snd->setRepeat(true);  
    emy10_snd->setVolume(music_volume);                 
	emy10_snd->setRepeat(true);
    emy11_snd->setVolume(music_volume);                 
    emy11_snd->setRepeat(true);  
    emy12_snd->setVolume(music_volume);                 
    emy12_snd->setRepeat(true);  
    emy13_snd->setVolume(music_volume);                 
    emy13_snd->setRepeat(true);  
    emy14_snd->setVolume(music_volume);                 
    emy14_snd->setRepeat(true);  


    jet1_snd->setVolume(music_volume);    
    jet1_snd->setRepeat(true); 
    jet2_snd->setVolume(music_volume);    
    jet2_snd->setRepeat(true);
    jet3_snd->setVolume(music_volume);    
    jet3_snd->setRepeat(true);
    jet4_snd->setVolume(music_volume);    
    jet4_snd->setRepeat(true);

    siege1_snd->setVolume(music_volume);    
    siege1_snd->setRepeat(true); 
    siege2_snd->setVolume(music_volume);    
    siege2_snd->setRepeat(true); 
    siege3_snd->setVolume(music_volume);    
    siege3_snd->setRepeat(true); 
    siege4_snd->setVolume(music_volume);    
    siege4_snd->setRepeat(false); 
    siege5_snd->setVolume(music_volume);    
    siege5_snd->setRepeat(true); 
    siege6_snd->setVolume(music_volume);    
    siege6_snd->setRepeat(true); 
        
    theatre_snd->setVolume(music_volume);   
    theatre_snd->setRepeat(false);      
        
    credits1_snd->setVolume(music_volume);   
    credits1_snd->setRepeat(false);  
    credits2_snd->setVolume(music_volume);   
    credits2_snd->setRepeat(false);  
    credits3_snd->setVolume(music_volume);   
    credits3_snd->setRepeat(false);  

    map_grass_snd->setVolume(music_volume);       
    map_grass_snd->setRepeat(true);  
    map_swamp_snd->setVolume(music_volume);       
    map_swamp_snd->setRepeat(true);  
    map_forest_snd->setVolume(music_volume);        
    map_forest_snd->setRepeat(true);  
    map_farm_snd->setVolume(music_volume);             
    map_farm_snd->setRepeat(true);        
    map_snow_snd->setVolume(music_volume);              
    map_snow_snd->setRepeat(true);             
    map_desert_snd->setVolume(music_volume);                   
    map_desert_snd->setRepeat(true);        
    map_trench_snd->setVolume(music_volume);         
    map_trench_snd->setRepeat(true);    
         
    lnd_snd->setVolume(music_volume);        
    lnd_snd->setRepeat(false);                   
             
    crd_snd->setVolume(music_volume);      
    crd_snd->setRepeat(true);               
         
    army_snd->setVolume(music_volume);  
    army_snd->setRepeat(true);     
      
    fight_snd->setVolume(music_volume);          
    fight_snd->setRepeat(true);           
        
    sad_snd->setVolume(music_volume);   
    sad_snd->setRepeat(true); 
        
    intro_snd->setVolume(music_volume);   
    intro_snd->setRepeat(true); 
        
    mini_snd->setVolume(music_volume);   
    mini_snd->setRepeat(true); 
        
    deathscreen_snd->setVolume(music_volume);   
    deathscreen_snd->setRepeat(true); 
                
    urgency_snd->setVolume(music_volume);   
    urgency_snd->setRepeat(true); 
            
    fanfare_snd->setVolume(music_volume);   
    fanfare_snd->setRepeat(false); 
            
    fanfare2_snd->setVolume(music_volume);   
    fanfare2_snd->setRepeat(false); 
        
    dgnb_snd->setVolume(music_volume);   
    dgnb_snd->setRepeat(true); 
        
    final_snd->setVolume(music_volume);       
    final_snd->setRepeat(true); 
        
    dangers_snd->setVolume(music_volume);   
    dangers_snd->setRepeat(true); 
                              
    vg_amb_prison_snd->setVolume(sfx_volume);                                 
    vg_amb_prison_snd->setRepeat(true);       
	 
    vg_amb_traffic_snd->setVolume(sfx_volume);                                 
    vg_amb_traffic_snd->setRepeat(true);       
               
    vg_amb_van_snd->setVolume(sfx_volume);                                  
    vg_amb_van_snd->setRepeat(true);   
               
    vg_amb_duel_snd->setVolume(sfx_volume);                                  
    vg_amb_duel_snd->setRepeat(true);   

	// Create the SteamAchievements object if Steam was successfully initialized
	#if IS_FULL_STEAM == 1  
	           
		/*if(STEAM_ACTIVE == true)                        
		{  

			g_SteamLeaderboards_finalscore = new CSteamLeaderboards(); 
			g_SteamLeaderboards_finalscore->FindLeaderboard("Arcade score");

			g_SteamLeaderboards_survivalscore = new CSteamLeaderboards(); 
			g_SteamLeaderboards_survivalscore->FindLeaderboard("Survival score");

			g_SteamLeaderboards_duellingscore = new CSteamLeaderboards(); 
			g_SteamLeaderboards_duellingscore->FindLeaderboard("Duelling score");

			g_SteamLeaderboards_turboscore = new CSteamLeaderboards(); 
			g_SteamLeaderboards_turboscore->FindLeaderboard("Turbo score");

			g_SteamLeaderboards_masterscore = new CSteamLeaderboards(); 
			g_SteamLeaderboards_masterscore->FindLeaderboard("Master score");

			g_SteamAchievements = new CSteamAchievements(g_Achievements, 13); 

		}  */

	#endif      
                
    if( DEMO_MODE == 0)     
	/*if(RENDERER == RENDER_OPENGL)
    {                                                        
        fprintf(fp2,"GL_RENDERED : %s\n", (char *)glGetString(GL_RENDERER) );
        fprintf(fp2,"GL_VENDOR : %s\n", (char *)glGetString(GL_VENDOR) );
        fprintf(fp2,"GL_VERSION : %s\n", (char *)glGetString(GL_VERSION) );
        fprintf(fp2,"GL_EXTENSIONS : %s\n", (char *)glGetString(GL_EXTENSIONS) );
    }*/
             
/*    warning_timer = (int)TimerGetTime() + 2500;
    
    if( DEMO_MODE == 1)           
    while(warning_timer > (int)TimerGetTime() )
    {
                
    }*/                            
             
    scene = 0;                             
         
    AI_Time = (int)TimerGetTime();           
    Swap_Time = (int)TimerGetTime();          
    Net_Time = (int)TimerGetTime();                  
    Net_Read_Time = (int)TimerGetTime();                
    Code_Time = (int)TimerGetTime();                
    Key_Time = (int)TimerGetTime();           
    Main_Time = (int)TimerGetTime();             
    FrameTime = (int)TimerGetTime();      
    FrameTimer = (int)TimerGetTime()+ 1000;
    Real_Time = (int)TimerGetTime() + 100;       
  
	//VG_Get_Keys();

    srand((int)TimerGetTime());   

	VG_P1_USING = VG_KEYBOARD;
	VG_P2_USING = VG_KEYBOARD;

	#if INCLDUE_360_CONTROLLER == 1                        
                 
		if(Check_Controller() == true)
			VG_P1_USING = VG_CONTROLLER;
		else
			VG_P1_USING = VG_KEYBOARD;

		if (Check_Controller() == true)
			VG_P2_USING = VG_CONTROLLER;
		else
			VG_P2_USING = VG_KEYBOARD;

	#endif


#ifdef SWITCH
	CANSAVE_SWITCH = true;

	nn::os::ThreadType messageThread;
	nn::os::CreateThread(&messageThread, HandleMessageAutoLoop, NULL, g_MessageThreadStack, sizeof(g_MessageThreadStack), nn::os::HighestThreadPriority);
	NN_ASSERT(result.IsSuccess(), "Cannot create message handling thread.");
	nn::os::StartThread(&messageThread);
	nn::oe::EnterExitRequestHandlingSection();
#endif
	

		


//    MAX_horizontal = 10000; 
//	MAX_vertical   = 10000;

#ifdef SWITCH

		while (IControlConnected(CDEV_PAD_0) == ICTRL_NONE && IControlConnected(CDEV_PAD_1) == ICTRL_NONE)
		{
			//printf("While before loop\n");
			IControlSetup(1,1);
			IControlUpdate();
		}
#endif
        
	while(!done)    	 		 						// Loop That Runs While done=FALSE
	{                  
        
		/*if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{        
                                                                  
                Peek_cycle = (int)TimerGetTime();
                                   
			    if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			    {
				    done=TRUE;							// If So done=TRUE
			    } 
			    else	        								// If Not, Deal With Window Messages
			    {
				    TranslateMessage(&msg);				// Translate The Message    
				    DispatchMessage(&msg);				// Dispatch The Message             
			    }              
			     
			    Peek_cycle = (int)TimerGetTime() - Peek_cycle;
			      
                if(fullscreen == true)              
                { 
                    GetWindowRect( hWnd, &r);  
                    ClipCursor( &r );  	
                }	 
                	                    
		}*/
#ifdef SWITCH
		if (NEED_TO_SAVE_AND_EXIT)
		{
			SaveCFG();
			nn::oe::LeaveExitRequestHandlingSection();
		}
		
		IControlUpdate();
#endif
#ifdef PS4

		_Application.update();
		
#endif
        if(1) // If There Are No Messages                
 	    {                                                                                                                                                                                                                                                                                                                                                                              
                         
                  Total_cycle = (int)TimerGetTime() - Total_Start; 
                  Total_Start = (int)TimerGetTime();
                                             
                  frame_rate++;     
                                                                    
                  // RealTime      
                  if((int)TimerGetTime() > Real_Time)                 
                  {           
                                       
                      time_diff = (int)TimerGetTime() - Real_Time; 
                      
                      time_diff /= 100;                                                        
                                                                                                                                                              
                      if(hours >= 24)                                                                                                                                                                                                                                                                     
                      {                                                                                                                                                                                                                                                      
                          hours = 0;                                                                                                                                                                                                                                                                                                                       
                      }           
                                                                                                                           
                      Real_Time = (int)TimerGetTime() + 100;                       
                                                                                                                                                       
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
                  }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
                  if((int)TimerGetTime() > FrameTimer)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
                  {                                            
                                                                                           
                            
                      FrameTimer = (int)TimerGetTime()+100;             
                                                        
                      frame_rate=0;                  
                                                                                                                                                                                                                                        
                  }                              
				     
				  if(game_paused == false)                                
                  if((int)TimerGetTime() > Steam_Time)  
                  {                                    
					                                 
					  #if IS_FULL_STEAM == 1                      
					           
					  //if(STEAM_ACTIVE == TRUE)  
						//SteamAPI_RunCallbacks(); // STEAM
					        
					  #endif                           
                                        
                      Steam_Time = (int)TimerGetTime() + STEAM_RATE;  // 400  
                                  
                  }                                  
				        
				  if(game_paused == false)                            
                  if((int)TimerGetTime() > Animate_Time)  
                  {                         
				      Animate(-1, -1);      
                                   
                      Animate_Time = (int)TimerGetTime() + ANIMATE_RATE;  //8  
                                  
                  }                  
				  			                                                                          
              //    if(fade != 0.0f)                             
                  if(double_main_code == 0)                                                                            
                  if((int)TimerGetTime() > AI_Time)                 
                  {               
                           
                      Draw_cycle = (int)TimerGetTime();  
                      	
                      DrawGLScene(false, (int)TimerGetTime()-Draw_Start);                                       
   			          
                      Draw_cycle = (int)TimerGetTime() - Draw_cycle;
                               
					  Draw_Start = (int)TimerGetTime(); 
                      AI_Time = (int)TimerGetTime() + RENDER_RATE;  //1  
                              
                  }                                                         
                                                                 
              //    if(fade != 0.0f)                          
                  if(double_main_code == 1)                                                                              
                  if((int)TimerGetTime() > Swap_Time)                
                  {               
                            
                      Swap_cycle = (int)TimerGetTime(); 

					  //if(RENDERER == RENDER_OPENGL)
   						//SwapBuffers(hDC); 					// Swap Buffers (Double Buffering)
                         
                      Swap_cycle = (int)TimerGetTime() - Swap_cycle;
                                
                      Swap_Time = (int)TimerGetTime() + SWAP_RATE;  //8  

                      double_main_code = 0;    

				//	  VG_FLICKER ^= 1;
                                                                                                                               
                  }                                                                                  
                        
				  /*if(FRAME_RATE_DELAY == 1)  
				      Sleep(10);  // For testing purposes...
				  if(FRAME_RATE_DELAY == 2)
				      Sleep(50);  // For testing purposes...*/
                  if((int)TimerGetTime() > Key_Time)
                  {                                
					    
			//		  if(CONTROLLER_ENABLED == false)  
			//			  CONTROLLER=false;  
					   
					  #if INCLDUE_360_CONTROLLER == 1 
					  if(!mode)                
 					  { 
  						  Run_Joypad();
						  
					  }       
					  else 
						  CONTROLLER = false;               
					             
					  #endif       
                      
					  if(!(episode == 0 && scene == 15))
					  if(!mode) 
					  {
				          VG_Key_Handler(keys, sprite, (int)TimerGetTime()-Key_Start );
					  }
					  else
						  Key_Handler(keys, sprite, (int)TimerGetTime()-Key_Start );
					
					  if(game_paused == false)
					      Run_Fx((int)TimerGetTime()-Key_Start);  

                      Key_Start = (int)TimerGetTime();       
                      Key_Time = (int)TimerGetTime()+KEY_RATE; //8  
					           
                                                                                      
                  }                                                                                                                                                                                                
        
                    
       if(mouseleft == true)           
       {                                        
                    
           if(mouse_held_state==0)         
           {
               mouse_held_state = 1;
               mouseheld_timer = (int)TimerGetTime() + 600;  
           }

           if((int)TimerGetTime() > mouseheld_timer && mouse_held_state == 1)
           { 
               mouseheld = true;
           }     
                                   
       }          
       else                   
       {                
           mouseheld = false;  
              
           mouse_held_state = 0;         
       }              
                                                                                
       UpdateMouseCursor();    

	   // *****************************//
	   //      Paused game code...     //
	   // *****************************//
                            
	   if(vg_pause_sfx == true)                 
	   {   
		   vg_pause_sfx = false;     
		   vg_title_select->setVolume(sfx_volume);              
		   vg_title_select->play();        
	   }  

	   VG_Pause();
	   
	   if(pause_music == true) 
	   {

		   if(game_paused == true)      
		   {

				emy1_snd->setVolume(0.0f); 
				emy2_snd->setVolume(0.0f); 
				emy3_snd->setVolume(0.0f); 
				emy4_snd->setVolume(0.0f); 
				emy5_snd->setVolume(0.0f); 
				emy6_snd->setVolume(0.0f); 
				emy7_snd->setVolume(0.0f); 
				emy8_snd->setVolume(0.0f); 
				emy9_snd->setVolume(0.0f); 
				emy10_snd->setVolume(0.0f); 
				emy11_snd->setVolume(0.0f); 
				emy12_snd->setVolume(0.0f); 
				emy13_snd->setVolume(0.0f); 
				emy14_snd->setVolume(0.0f);

				jet1_snd->setVolume(0.0f);  
				jet2_snd->setVolume(0.0f);  
				jet3_snd->setVolume(0.0f);  
				jet4_snd->setVolume(0.0f);  

				siege1_snd->setVolume(0.0f);   
				siege2_snd->setVolume(0.0f);
				siege3_snd->setVolume(0.0f);   
				siege4_snd->setVolume(0.0f);
				siege5_snd->setVolume(0.0f);   
				siege6_snd->setVolume(0.0f); 

				theatre_snd->setVolume(0.0f);   
				credits1_snd->setVolume(0.0f);  
				credits2_snd->setVolume(0.0f); 
				credits3_snd->setVolume(0.0f); 

				map_grass_snd->setVolume(0.0f);       
				map_swamp_snd->setVolume(0.0f);       
				map_forest_snd->setVolume(0.0f);       
				map_farm_snd->setVolume(0.0f);       
				map_snow_snd->setVolume(0.0f);       
				map_desert_snd->setVolume(0.0f);       
				map_trench_snd->setVolume(0.0f); 

				lnd_snd->setVolume(0.0f);     
				crd_snd->setVolume(0.0f);      
				army_snd->setVolume(0.0f);  
				fight_snd->setVolume(0.0f);          
				sad_snd->setVolume(0.0f);        
				intro_snd->setVolume(0.0f);              
				mini_snd->setVolume(0.0f);   
				deathscreen_snd->setVolume(0.0f);         
				urgency_snd->setVolume(0.0f);   
				fanfare_snd->setVolume(0.0f);   
				fanfare2_snd->setVolume(0.0f);    
				dgnb_snd->setVolume(0.0f);   
				final_snd->setVolume(0.0f);   
				dangers_snd->setVolume(0.0f);  

				vg_amb_prison_snd->setVolume(0.0f);
				vg_amb_traffic_snd->setVolume(0.0f);        
				vg_amb_van_snd->setVolume(0.0f);
				vg_amb_duel_snd->setVolume(0.0f);

		   }     
		   else 
		   { 

				emy1_snd->setVolume(music_volume);  
				emy2_snd->setVolume(music_volume); 
				emy3_snd->setVolume(music_volume);
				emy4_snd->setVolume(music_volume);
				emy5_snd->setVolume(music_volume);
				emy6_snd->setVolume(music_volume);
				emy7_snd->setVolume(music_volume);
				emy8_snd->setVolume(music_volume);
				emy9_snd->setVolume(music_volume);
				emy10_snd->setVolume(music_volume);
				emy11_snd->setVolume(music_volume);
				emy12_snd->setVolume(music_volume);
				emy13_snd->setVolume(music_volume);
				emy14_snd->setVolume(music_volume);

				jet1_snd->setVolume(music_volume);    
				jet2_snd->setVolume(music_volume);    
				jet3_snd->setVolume(music_volume);    
				jet4_snd->setVolume(music_volume);     

				siege1_snd->setVolume(music_volume);  
				siege2_snd->setVolume(music_volume); 
				siege3_snd->setVolume(music_volume);  
				siege4_snd->setVolume(music_volume); 
				siege5_snd->setVolume(music_volume);  
				siege6_snd->setVolume(music_volume); 

				theatre_snd->setVolume(music_volume);   
				credits1_snd->setVolume(music_volume);  
				credits2_snd->setVolume(music_volume);
				credits3_snd->setVolume(music_volume);

				map_grass_snd->setVolume(music_volume); 
				map_swamp_snd->setVolume(music_volume); 
				map_forest_snd->setVolume(music_volume); 
				map_farm_snd->setVolume(music_volume); 
				map_snow_snd->setVolume(music_volume); 
				map_desert_snd->setVolume(music_volume); 
				map_trench_snd->setVolume(music_volume); 

				lnd_snd->setVolume(music_volume);     
				crd_snd->setVolume(music_volume);      
				army_snd->setVolume(music_volume);  
				fight_snd->setVolume(music_volume);          
				sad_snd->setVolume(music_volume);   
				intro_snd->setVolume(music_volume);   
				mini_snd->setVolume(music_volume);   
				deathscreen_snd->setVolume(music_volume);   
				urgency_snd->setVolume(music_volume);   
				fanfare_snd->setVolume(music_volume);   
				fanfare2_snd->setVolume(music_volume);   
				dgnb_snd->setVolume(music_volume);   
				final_snd->setVolume(music_volume);   
				dangers_snd->setVolume(music_volume);  

				vg_amb_prison_snd->setVolume(sfx_volume);
				vg_amb_traffic_snd->setVolume(sfx_volume);        
				vg_amb_van_snd->setVolume(sfx_volume);
				vg_amb_duel_snd->setVolume(sfx_volume);

		   }

           pause_music=false;     
	   }     
	            
       // Main Code                             
                                                                 
       Main_cycle = (int)TimerGetTime();                                            
                         
       if(!mode)           
       {                               
                   
		   Set_Screen_Ratio();              
	  
           if(!mode)
               zoom_factor = (org_zoom_factor-0.6f) + org_zoom_scroll_amount; // 1.3 - 0.6 = 0.7 for 16:9
           else
               zoom_factor = org_zoom_factor + org_zoom_scroll_amount;    

       } 
               
       srand((int)TimerGetTime()); 
   
	   //Sleep(20);        

//       if(double_main_code == 0)                
       if((int)TimerGetTime() > Main_Time)                    
       if(game_paused == false)                          
       {                                                   
                                            
       f_rate1 = (int)TimerGetTime()-Main_Start;                                   
                    
	   if(f_rate1 <= 0)                                                    
	       f_rate1 = 1;         
	                     
	   if(f_rate1 > 100)         
		   f_rate1 = 100;                
	      
	   if(!mode)
	   {
		   if(episode == 0 || episode == 1)       
			   Run_Frontend((int)TimerGetTime()-Main_Start); 

		   Run_Verdict((int)TimerGetTime()-Main_Start);  
		   Run_Story((int)TimerGetTime()-Main_Start);   
	   }

	   if(episode == 1)
	   if((int)TimerGetTime() > VG_insert_flash_timer)
	   {

			sprintf( new_counter[299].word, "INSERT COIN"); 
			 
			if(VG_insert_flash == false)
			{
				new_counter[299].alpha = 1.0f;   
				VG_insert_flash = true;
			}
			else
			{
				new_counter[299].alpha = 0.0f;    
				VG_insert_flash = false;
			}

			VG_insert_flash_timer = (int)TimerGetTime() + 500;
			  
			new_counter[299].type = 1;  // Small Font...
			new_counter[299].right = false;

			new_counter[299].id = 3;

			new_counter[299].x = -0.08f;                    
			new_counter[299].y = VG_BOTTOM_OPTIONS_OFFSET;           

			new_counter[299].w = new_counter[299].x - 0.026f;   
			new_counter[299].z = new_counter[299].y - 0.015f;

			new_counter[299].box_width = strlen(new_counter[299].word)   *  0.026f;
			new_counter[299].box_height = new_counter[299].height - 0.015f;

	   } 

       Main_Start = (int)TimerGetTime();                                                                 
       Main_Time = (int)TimerGetTime() + MAIN_RATE;    
         
       if((int)TimerGetTime() > quit_timer && quitting == true)
       {
                                  
           done = true;             
                   
           quitting=false;                                                        
                
       }                 

      
        // ******************************************************************************//
        //                              Animation System                                 //                     
        // ******************************************************************************//

		// Game Logic   
		if(c_fade_in != 0 && next_scene == false)                 
        if(fade < 1.0)                               
        {  
            fade += 1.0f - cos(cos_fade);    

			if(fade > 1.0f)
				fade = 1.0f;

            cos_fade += ( (((float)c_fade_in / 50000) * (float)f_rate1) );
             
            if(cos_fade > 1.5f ) 
                cos_fade = 1.5f;       
        }
        else  
        {     
            fade=1.0f;  
            cos_fade = 0.0f;   
            c_fade_in = 0;        
        }    

		if(fade_in == 0 && next_scene == false)
		if((int)TimerGetTime() < fade_timer)
		{
		    fade = 0.0f;
        }      
        else     
        {
            if(fade == 0.0f) 
                fade = 1.0f;     
        }           


        // ******************************************************************************//
        //                              Fade System                                      //                     
        // ******************************************************************************//
                                
        // Load next scene if no fade out required
        if(next_scene == true)                         
        {                       
           
            if(c_fade_out == 0)              
            {         
                                      
               fade = 0.0f;                            
                        
			   if(vg_next_episode != -1) 
			   {
				   episode = vg_next_episode;   
				   scene = vg_next_scene;

				   vg_next_episode = -1; 
				   vg_next_scene  = -1;
			   }    

               LoadScene( episode, scene, true );
                    
               animating = true;   
                      
               next_scene = false;  
                         
            }              
            else                        
            {        
                if(fade > 0.0f)        
                {  

                    fade -= 1.0f - cos(cos_fade);   
                    
                    cos_fade += ( (((float)c_fade_out / 50000) * (float)f_rate1) );
             
                    if( cos_fade > 1.5f ) 
                        cos_fade = 1.5f;   

					// Was 0.0f...
					if(fade < 0.0f)  // 0.001f
					{
						fade = 0.0f; // 0.001f
						c_fade_out = 0;
					}
                
                }
                else                          
                {
                    fade = 0.0f;  
                    c_fade_out = 0;    
                }                          
            }      

        }        
                        
        // If paused don't execute                              
        if( quit_active == false)     
        {             
 

        // ******************************************************************************//
        //                                Debug-Selection                                //                     
        // ******************************************************************************//
                                                                    
        if(mode && mode != POINT_MODE && mode != NODES  && mode != TILE_MODE && next_scene == false)
        {              
            if(mouseleft == true)           
            for(int i=0;i<original_no_sprites;i++)
            { 
                var = var3[i];          
                    
				if(var >= 0 && var < TOTAL_NO_SPRITES)                            
                if(( mouseX < (sprite[var].x + sprite[var].width) )
                &&( mouseX > sprite[var].x)                        
                &&( mouseY < (sprite[var].y + sprite[var].height) )
                &&( mouseY > sprite[var].y))
                {
                    if(selection != var)
                        fps = var;
                }               
            }        
              
            selection = fps;       
            mouseleft = false;       
                          
        }                                   
                                                   
        // ******************************************************************************//
        //                                Text-Functions                                 //                     
        // ******************************************************************************//

        if( scroll_txt_active == true && (int)TimerGetTime() > scroll_txt_timer )
        {
               
            if(scroll_index < scroll_length )
            {       
                scroll_index++;  
                if(scroll_length > 1)  
                    vg_tink_sfx = true; 
                     
            }              
                    
            if(scroll_index >= scroll_length)
            {  
                            
                scroll_txt_active = false;
                
                text_timer = ((int)TimerGetTime() + 2000);
                 
                if(g_type != G_STS)
                    text_active = true;  
         
            } 
                
            scroll_txt_timer = ((int)TimerGetTime() + 40);
                 
        }    

     //   if(DEBUG_MODE == 1 )  
       if((game_mode == WALK || game_mode == FRONT || game_mode == WORLD || game_mode == CINE) )
       {   
                           
 //      if(DEBUG_MODE == 1 )                                   
 //      {                              
       
	   if(!CONTROLLER)
       if(music_volume <= 0.05f) 
           music_volume = 0.0f;

	   if(CONTROLLER) 
       if(music_volume <= 0.0f) 
           music_volume = 0.0f;
       
       if(music_volume >= 1.0f)
           music_volume = 1.0f;
            
       if(music_volume != 0.0f) 
       {      

	/*	if(CHANGE_SONG_SPEED == 1)  
		{ 

			if(VG_BACKGROUND == VG_GYEONG)
			{
				emy1_snd->stop();    
				emy1f_snd->play();
				CHANGE_SONG_SPEED = 2;
			}

		}*/
       
       temp_music_volume = music_volume;     
       temp_sfx_volume   = sfx_volume;    
                         
       // Set the volume for the musicbox at base camp
//       if(!mode)  
       if(music_fade == true)
       if((int)TimerGetTime() > music_timer)          
       {    
                     
           music_timer = (int)TimerGetTime() + 50; 
           
           fade_increment = music_volume / 28.0f;  
           
           if(fade_increment <= 0.0f)
               fade_increment = 0.0f;
           
           fade_out_volume -= fade_increment;  
           fade_in_volume  += fade_increment;
           
           if(fade_out_volume <= 0.0f)     
           { 
               fade_out_volume = 0.0f;     
               fade_in_volume = music_volume;      
               music_fade = false;
           } 
           
           if(fade_out_volume > 1.0f)  
               fade_out_volume = 1.0f;
                           
           if(fade_in_volume < 0.0f) 
               fade_in_volume = 0.0f;    
           
           if(fade_in_volume > 1.0f)  
               fade_in_volume = 1.0f;
                                     
           if(fade_in_volume >= music_volume)
           {
               fade_out_volume = 0.0f;
               fade_in_volume = music_volume;
               music_fade = false;
           }   
           
           if(crd_sfx == FADE_IN)     
           {
               crd_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  crd_sfx = LOOP;               
           }                   
           if(crd_sfx == FADE_OUT)          
           { 
                     
              crd_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f)
                  crd_sfx = NO_ANIM;      
                             
           }   
                
           if(end_sfx == FADE_IN) 
           {

			   if(VG_BACKGROUND == VG_GYEONG)
				  emy1_snd->setVolume(fade_in_volume);
			   if(VG_BACKGROUND == VG_SIU)
				  emy2_snd->setVolume(fade_in_volume);
			   if(VG_BACKGROUND == VG_MINSO)
				  emy3_snd->setVolume(fade_in_volume);
			   if(VG_BACKGROUND == VG_REESE)
				  emy4_snd->setVolume(fade_in_volume);
			   if(VG_BACKGROUND == VG_YOHAN)
				  emy5_snd->setVolume(fade_in_volume);
			   if(VG_BACKGROUND == VG_JAE)
				  emy6_snd->setVolume(fade_in_volume);
			   if(VG_BACKGROUND == VG_GUN)
				  emy7_snd->setVolume(fade_in_volume);
			   if(VG_BACKGROUND == VG_HYUK)
				  emy8_snd->setVolume(fade_in_volume);
			   if(VG_BACKGROUND == VG_SANG)
				  emy9_snd->setVolume(fade_in_volume);
			   if(VG_BACKGROUND == VG_TRAINER)
				  emy10_snd->setVolume(fade_in_volume);
			   if(VG_BACKGROUND == VG_SHO)
				  emy11_snd->setVolume(fade_in_volume);
			   if(VG_BACKGROUND == VG_SAIZO)
				  emy12_snd->setVolume(fade_in_volume);
			   if(VG_BACKGROUND == VG_TIA)
				  emy13_snd->setVolume(fade_in_volume);
			   if(VG_BACKGROUND == VG_KENNEDY)
				  emy14_snd->setVolume(fade_in_volume);

				if(fade_in_volume == music_volume)
					end_sfx = LOOP;                
           }                   
           if(end_sfx == FADE_OUT) 
           {
			  if(VG_BACKGROUND == VG_GYEONG)
			      emy1_snd->setVolume(fade_out_volume);  
			  if(VG_BACKGROUND == VG_SIU)
				  emy2_snd->setVolume(fade_out_volume);  
			  if(VG_BACKGROUND == VG_MINSO)
				  emy3_snd->setVolume(fade_out_volume);  
			  if(VG_BACKGROUND == VG_REESE)
				  emy4_snd->setVolume(fade_out_volume);  
			  if(VG_BACKGROUND == VG_YOHAN)
				  emy5_snd->setVolume(fade_out_volume);  
			  if(VG_BACKGROUND == VG_JAE)
				  emy6_snd->setVolume(fade_out_volume);   
			  if(VG_BACKGROUND == VG_GUN)
				  emy7_snd->setVolume(fade_out_volume);  
			  if(VG_BACKGROUND == VG_HYUK)
				  emy8_snd->setVolume(fade_out_volume); 
			  if(VG_BACKGROUND == VG_SANG)
				  emy9_snd->setVolume(fade_out_volume);  
			  if(VG_BACKGROUND == VG_TRAINER)
				  emy10_snd->setVolume(fade_out_volume); 
			  if(VG_BACKGROUND == VG_SHO)
				  emy11_snd->setVolume(fade_out_volume); 
			  if(VG_BACKGROUND == VG_SAIZO)
				  emy12_snd->setVolume(fade_out_volume); 
			  if(VG_BACKGROUND == VG_TIA)
				  emy13_snd->setVolume(fade_out_volume); 
			  if(VG_BACKGROUND == VG_KENNEDY)
				  emy14_snd->setVolume(fade_out_volume); 

              if(fade_out_volume == 0.0f)  
                  end_sfx = NO_ANIM; 
           }         
             
           if(war_sfx == FADE_IN)         
           {

               if(fade_in_volume == music_volume)
                  war_sfx = LOOP;               
           }                   
           if(war_sfx == FADE_OUT)
           {

              if(fade_out_volume == 0.0f)
                  war_sfx = NO_ANIM;               
           }      
                      
           if(lnd_sfx == FADE_IN)
           {
               lnd_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  lnd_sfx = LOOP;               
           }                   
           if(lnd_sfx == FADE_OUT) 
           {
              lnd_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f) 
                  lnd_sfx = NO_ANIM;    
           }
                      
           if(army_sfx == FADE_IN)
           {
               army_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  army_sfx = LOOP;               
           }                   
           if(army_sfx == FADE_OUT)
           {
              army_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f)
                  army_sfx = NO_ANIM;               
           }      
                      
           if(fight_sfx == FADE_IN)               
           {
               fight_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  fight_sfx = LOOP;               
           }                   
           if(fight_sfx == FADE_OUT)      
           {
              fight_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f)
                  fight_sfx = NO_ANIM;               
           }
                                  
           if(jet_sfx == FADE_IN) 
           { 
                    
			   if(VG_IS_VERSUS_SCREEN == true)
				  jet1_snd->setVolume(fade_in_volume);
			   if(VG_IS_VERSUS_SCREEN == false)
				  jet2_snd->setVolume(fade_in_volume);

               if(fade_in_volume == music_volume)
                  jet_sfx = LOOP;               
           }                         
           if(jet_sfx == FADE_OUT)
           {
                    
			   if(VG_IS_VERSUS_SCREEN == true)
				  jet1_snd->setVolume(fade_out_volume);
			   if(VG_IS_VERSUS_SCREEN == false)
				  jet2_snd->setVolume(fade_out_volume);

              if(fade_out_volume == 0.0f)
                  jet_sfx = NO_ANIM;               
           }    
                      
           if(siege_sfx == FADE_IN)  
           {
			   if(VG_CS_SONG == CS_DANGER1)
				   siege1_snd->setVolume(fade_in_volume);
			   if(VG_CS_SONG == CS_DANGER2)
				   siege2_snd->setVolume(fade_in_volume);
			   if(VG_CS_SONG == CS_VICTORY)
				   siege3_snd->setVolume(fade_in_volume);
			   if(VG_CS_SONG == CS_ENDING)
				   siege4_snd->setVolume(fade_in_volume);
			   if(VG_CS_SONG == CS_BOSSIDLE)
				   siege5_snd->setVolume(fade_in_volume);
			   if(VG_CS_SONG == CS_IDLE)
				   siege6_snd->setVolume(fade_in_volume);

               if(fade_in_volume == music_volume)
                  siege_sfx = LOOP;               
           }                         
           if(siege_sfx == FADE_OUT) 
           {
			   if(VG_CS_SONG == CS_DANGER1)
				   siege1_snd->setVolume(fade_out_volume);
			   if(VG_CS_SONG == CS_DANGER2)
				   siege2_snd->setVolume(fade_out_volume);
			   if(VG_CS_SONG == CS_VICTORY)
				   siege3_snd->setVolume(fade_out_volume);
			   if(VG_CS_SONG == CS_ENDING)
				   siege4_snd->setVolume(fade_out_volume);
			   if(VG_CS_SONG == CS_BOSSIDLE)
				   siege5_snd->setVolume(fade_out_volume);
			   if(VG_CS_SONG == CS_IDLE)
				   siege6_snd->setVolume(fade_out_volume);

              if(fade_out_volume < 0.0f)
                  siege_sfx = NO_ANIM;               
           }    
                      
           if(theatre_sfx == FADE_IN)
           {
               theatre_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  theatre_sfx = LOOP;               
           }                         
           if(theatre_sfx == FADE_OUT)
           {
              theatre_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f)
                  theatre_sfx = NO_ANIM;               
           }    
                      
           if(credits_sfx == FADE_IN)
           {
             
           }                         
           if(credits_sfx == FADE_OUT)
           {

              if(fade_out_volume == 0.0f)
                  credits_sfx = NO_ANIM;               
           }                                 
                      
           if(sad_sfx == FADE_IN)   
           {
               sad_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  sad_sfx = LOOP;               
           }                 
           if(sad_sfx == FADE_OUT)
           {
              sad_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f)
                  sad_sfx = NO_ANIM;               
           }      
                      
           if(intro_sfx == FADE_IN)
           {
               intro_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  intro_sfx = LOOP;               
           }                 
           if(intro_sfx == FADE_OUT)
           {
              intro_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f)
                  intro_sfx = NO_ANIM;               
           }   
                      
           if(mini_sfx == FADE_IN)
           {
               mini_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  mini_sfx = LOOP;               
           }                 
           if(mini_sfx == FADE_OUT)
           {
              mini_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f)
                  mini_sfx = NO_ANIM;               
           }  
           
           if(deathscreen_sfx == FADE_IN)
           {
               deathscreen_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  deathscreen_sfx = LOOP;               
           }                 
           if(deathscreen_sfx == FADE_OUT)
           {
              deathscreen_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f)
                  deathscreen_sfx = NO_ANIM;               
           } 
                                            
           if(urgency_sfx == FADE_IN)
           {
               urgency_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  urgency_sfx = LOOP;               
           }                 
           if(urgency_sfx == FADE_OUT)
           {
              urgency_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f)
                  urgency_sfx = NO_ANIM;               
           } 
                                 
           if(fanfare_sfx == FADE_IN)
           {
               fanfare_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  fanfare_sfx = LOOP;               
           }                 
           if(fanfare_sfx == FADE_OUT)
           {
              fanfare_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f)
                  fanfare_sfx = NO_ANIM;               
           }  
                                 
           if(fanfare2_sfx == FADE_IN)
           {
               fanfare2_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  fanfare2_sfx = LOOP;               
           }                 
           if(fanfare2_sfx == FADE_OUT)
           {
              fanfare2_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f)
                  fanfare2_sfx = NO_ANIM;               
           }  
                                                       
           if(dgnb_sfx == FADE_IN)
           {
               dgnb_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  dgnb_sfx = LOOP;               
           }                 
           if(dgnb_sfx == FADE_OUT)
           {
              dgnb_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f)
                  dgnb_sfx = NO_ANIM;               
           }  
                      
           if(final_sfx == FADE_IN)
           {
               final_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  final_sfx = LOOP;               
           }                 
           if(final_sfx == FADE_OUT)
           {
              final_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f)
                  final_sfx = NO_ANIM;               
           }  
                      
           if(dangers_sfx == FADE_IN)
           {
               dangers_snd->setVolume(fade_in_volume);
               if(fade_in_volume == music_volume)
                  dangers_sfx = LOOP;               
           }                 
           if(dangers_sfx == FADE_OUT)
           {
              dangers_snd->setVolume(fade_out_volume);  
              if(fade_out_volume == 0.0f)
                  dangers_sfx = NO_ANIM;               
           }              
                                                                                                                      
       }  // if(music_fade == true)       
             
       if(crd_sfx == NO_ANIM) 
       {    
           crd_snd->stop();
           crd_snd->reset(); 
           crd_sfx = WAIT; 
       }         
       if(crd_sfx == PLAY || crd_sfx == FADE_IN)              
       {
		   if(crd_snd->isPlaying() == false)
               crd_snd->play();
            
           if(crd_sfx == PLAY)      
           {      
               crd_sfx = LOOP;      
                
               if(half_volume == false)
                   crd_snd->setVolume(music_volume);
               else
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   crd_snd->setVolume(music_volume/2);
               } 
           }              
       }      
       
       if(end_sfx == NO_ANIM)        
       {                                        
           emy1_snd->stop();            
           emy1_snd->reset();
           emy2_snd->stop();            
           emy2_snd->reset();
           emy3_snd->stop();             
           emy3_snd->reset();
           emy4_snd->stop();            
           emy4_snd->reset();
           emy5_snd->stop();             
           emy5_snd->reset();
           emy6_snd->stop();            
           emy6_snd->reset();
           emy7_snd->stop();            
           emy7_snd->reset();
           emy8_snd->stop();            
           emy8_snd->reset();
           emy9_snd->stop();            
           emy9_snd->reset();
           emy10_snd->stop();            
           emy10_snd->reset();
           emy11_snd->stop();            
           emy11_snd->reset();
           emy12_snd->stop();            
           emy12_snd->reset();
           emy13_snd->stop();            
           emy13_snd->reset();
           emy14_snd->stop();            
           emy14_snd->reset();

           end_sfx=WAIT;              
       }                    
       if(end_sfx == PLAY || end_sfx == FADE_IN || end_sfx == ONCE)              
       {
		   if(VG_BACKGROUND == VG_GYEONG)
		   if(emy1_snd->isPlaying() == false)
			   emy1_snd->play();   
		   if(VG_BACKGROUND == VG_SIU)
		   if(emy2_snd->isPlaying() == false)
			   emy2_snd->play();  
		   if(VG_BACKGROUND == VG_MINSO)
		   if(emy3_snd->isPlaying() == false)
			   emy3_snd->play();  
		   if(VG_BACKGROUND == VG_REESE)
		   if(emy4_snd->isPlaying() == false)
			   emy4_snd->play();  
		   if(VG_BACKGROUND == VG_YOHAN)
		   if(emy5_snd->isPlaying() == false)
			   emy5_snd->play();  
		   if(VG_BACKGROUND == VG_JAE)
		   if(emy6_snd->isPlaying() == false)
			   emy6_snd->play();  
		   if(VG_BACKGROUND == VG_GUN)
		   if(emy7_snd->isPlaying() == false)
			   emy7_snd->play(); 
		   if(VG_BACKGROUND == VG_HYUK)
		   if(emy8_snd->isPlaying() == false)
			   emy8_snd->play(); 
		   if(VG_BACKGROUND == VG_SANG)
		   if(emy9_snd->isPlaying() == false)
			   emy9_snd->play(); 
		   if(VG_BACKGROUND == VG_TRAINER)
		   if(emy10_snd->isPlaying() == false)
			   emy10_snd->play(); 
		   if(VG_BACKGROUND == VG_SHO)
		   if(emy11_snd->isPlaying() == false)
			   emy11_snd->play(); 
		   if(VG_BACKGROUND == VG_SAIZO)
		   if(emy12_snd->isPlaying() == false)
			   emy12_snd->play(); 
		   if(VG_BACKGROUND == VG_TIA)
		   if(emy13_snd->isPlaying() == false)
			   emy13_snd->play(); 
		   if(VG_BACKGROUND == VG_KENNEDY)
		   if(emy14_snd->isPlaying() == false)
			   emy14_snd->play(); 

           if(end_sfx == PLAY)      
           {      
               end_sfx = LOOP;      

               if(half_volume == false)
			   {
                   emy1_snd->setVolume(music_volume);
                   emy2_snd->setVolume(music_volume);
                   emy3_snd->setVolume(music_volume);
                   emy4_snd->setVolume(music_volume);
                   emy5_snd->setVolume(music_volume);
                   emy6_snd->setVolume(music_volume);
                   emy7_snd->setVolume(music_volume);
				   emy8_snd->setVolume(music_volume);
				   emy9_snd->setVolume(music_volume);
				   emy10_snd->setVolume(music_volume);
				   emy11_snd->setVolume(music_volume);
				   emy12_snd->setVolume(music_volume);
				   emy13_snd->setVolume(music_volume);
				   emy14_snd->setVolume(music_volume);
			   }
               else
               {
                   temp_music_volume = music_volume/2; 
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   emy1_snd->setVolume(music_volume/2);
				   emy2_snd->setVolume(music_volume/2);
				   emy3_snd->setVolume(music_volume/2);
				   emy4_snd->setVolume(music_volume/2);
				   emy5_snd->setVolume(music_volume/2);
				   emy6_snd->setVolume(music_volume/2);
				   emy7_snd->setVolume(music_volume/2);
				   emy8_snd->setVolume(music_volume/2);
				   emy9_snd->setVolume(music_volume/2);
				   emy10_snd->setVolume(music_volume/2);
				   emy11_snd->setVolume(music_volume/2);
				   emy12_snd->setVolume(music_volume/2);
				   emy13_snd->setVolume(music_volume/2);
				   emy14_snd->setVolume(music_volume/2);
               }  
           }   
       
       }
       if(war_sfx == NO_ANIM)
       {


           war_sfx=WAIT;                
       }           
       if(war_sfx == PLAY || war_sfx == FADE_IN) 
       {

           
           if(war_sfx == PLAY)     
           {      
               war_sfx = LOOP;        
                 
               if(half_volume == false)
			   {

			   }
               else 
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;


               }
               
           }      
       } 
       if(lnd_sfx == NO_ANIM)
       {      
           lnd_snd->stop();
           lnd_snd->reset();
           lnd_sfx=WAIT;
       }      
       if(lnd_sfx == PLAY || lnd_sfx == FADE_IN)         
       {
		   if(lnd_snd->isPlaying() == false)
               lnd_snd->play();
           
           if(lnd_sfx == PLAY)      
           {      
               lnd_sfx = LOOP;      
                
               if(half_volume == false)
                   lnd_snd->setVolume(music_volume);
               else
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   lnd_snd->setVolume(music_volume/2);
               }
                
           }   
       }                   
       if(army_sfx == NO_ANIM)               
       {
           army_snd->stop();          
           army_snd->reset();           
           army_sfx = WAIT;      
       }       
       if(army_sfx == PLAY || army_sfx == FADE_IN)
       {
		   if(army_snd->isPlaying() == false)
               army_snd->play();   

           if(army_sfx == PLAY)      
           {      
               army_sfx = LOOP;      
                
               if(half_volume == false)
                   army_snd->setVolume(music_volume);
               else
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   army_snd->setVolume(music_volume/2);
               } 
           }       
       }        
       if(fight_sfx == NO_ANIM)
       {    
           fight_snd->stop();           
       //    fight_snd->reset(); 
           fight_sfx = WAIT;
       }  
       if(fight_sfx == RESET_MUSIC)
       {    
           fight_snd->stop();           
           fight_snd->reset();
           fight_sfx = WAIT;
       }              
       if(fight_sfx == PLAY || fight_sfx == FADE_IN)
       {  
		   if(fight_snd->isPlaying() == false)
               fight_snd->play();             

           if(fight_sfx == PLAY)     
           {      
               fight_sfx = LOOP;     
                
               if(half_volume == false)
                   fight_snd->setVolume(music_volume);
               else
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   fight_snd->setVolume(music_volume/2);
               }
               
           }
       }   
       if(jet_sfx == NO_ANIM)
       {
           jet1_snd->stop();            
           jet1_snd->reset();
           jet2_snd->stop();            
           jet2_snd->reset();
           jet3_snd->stop();             
           jet3_snd->reset();
           jet4_snd->stop();            
           jet4_snd->reset();

           jet_sfx = WAIT;
       }               
       if(jet_sfx == PLAY || jet_sfx == FADE_IN)
       { 
		   if(VG_IS_VERSUS_SCREEN == true)
		   if(jet1_snd->isPlaying() == false)
			   jet1_snd->play();       
		   if(VG_IS_VERSUS_SCREEN == false)
		   if(jet2_snd->isPlaying() == false)
			   jet2_snd->play();  

           if(jet_sfx == PLAY)      
           {      
               jet_sfx = LOOP;       
                
               if(half_volume == false)
			   {
                   jet1_snd->setVolume(music_volume);
                   jet2_snd->setVolume(music_volume);
                   jet3_snd->setVolume(music_volume);
                   jet4_snd->setVolume(music_volume);
			   }
               else
               {
                   temp_music_volume = music_volume/2; 
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   jet1_snd->setVolume(music_volume/2);
				   jet2_snd->setVolume(music_volume/2);
				   jet3_snd->setVolume(music_volume/2);
				   jet4_snd->setVolume(music_volume/2);
               }   
           }            
       }  

       if(siege_sfx == NO_ANIM)
       {
           siege1_snd->stop();  
           siege1_snd->reset();
           siege2_snd->stop();  
           siege2_snd->reset();
           siege3_snd->stop();  
           siege3_snd->reset();
           siege4_snd->stop();  
           siege4_snd->reset();
           siege5_snd->stop();  
           siege5_snd->reset();
           siege6_snd->stop();  
           siege6_snd->reset();

           siege_sfx = WAIT;
       }               
       if(siege_sfx == PLAY || siege_sfx == FADE_IN) 
       { 

		   if(VG_CS_SONG == CS_DANGER1)
		   if(siege1_snd->isPlaying() == false)
			   siege1_snd->play();
		   if(VG_CS_SONG == CS_DANGER2)
		   if(siege2_snd->isPlaying() == false)
			   siege2_snd->play();
		   if(VG_CS_SONG == CS_VICTORY)
		   if(siege3_snd->isPlaying() == false)
			   siege3_snd->play();
		   if(VG_CS_SONG == CS_ENDING)
		   if(siege4_snd->isPlaying() == false)
			   siege4_snd->play();
		   if(VG_CS_SONG == CS_BOSSIDLE)
		   if(siege5_snd->isPlaying() == false)
			   siege5_snd->play();
		   if(VG_CS_SONG == CS_IDLE)
		   if(siege6_snd->isPlaying() == false)
			   siege6_snd->play();
           
           if(siege_sfx == PLAY)       
           {                
               siege_sfx = LOOP;                
                
               if(half_volume == false)
			   {
                   siege1_snd->setVolume(music_volume);
                   siege2_snd->setVolume(music_volume);
                   siege3_snd->setVolume(music_volume);
                   siege4_snd->setVolume(music_volume);
                   siege5_snd->setVolume(music_volume);
                   siege6_snd->setVolume(music_volume);
			   }
               else
               {    
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   siege1_snd->setVolume(music_volume/2);
				   siege2_snd->setVolume(music_volume/2);
                   siege3_snd->setVolume(music_volume/2);
				   siege4_snd->setVolume(music_volume/2); 
                   siege5_snd->setVolume(music_volume/2);
				   siege6_snd->setVolume(music_volume/2);
               } 
                     
           }     

       }        
       if(theatre_sfx == NO_ANIM)    
       {
           theatre_snd->stop();    
           theatre_snd->reset(); 
           theatre_sfx = WAIT;
       }               
       if(theatre_sfx == PLAY || theatre_sfx == FADE_IN)
       {  
		   if(theatre_snd->isPlaying() == false)
               theatre_snd->play();
           
           if(theatre_sfx == PLAY)       
           {                
               theatre_sfx = LOOP;                     
                
               if(half_volume == false)
                   theatre_snd->setVolume(music_volume);
               else
               {    
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   theatre_snd->setVolume(music_volume/2);
               }
                
           }   
       }      
       if(credits_sfx == NO_ANIM) 
       {
           credits1_snd->stop();  
           credits1_snd->reset(); 
           credits2_snd->stop();  
           credits2_snd->reset(); 
           credits3_snd->stop();  
           credits3_snd->reset(); 

           credits_sfx = WAIT;
       }               
       if(credits_sfx == PLAY || credits_sfx == FADE_IN)
       {  
           
           if(credits_sfx == PLAY)             
           {                 
               credits_sfx = LOOP;                
                       
               if(half_volume == false)
			   {
                   credits1_snd->setVolume(music_volume);
				   credits2_snd->setVolume(music_volume);
				   credits3_snd->setVolume(music_volume);
			   }
               else
               {    
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)

                       temp_music_volume = 0.0f;
                       
                   credits1_snd->setVolume(music_volume/2);
				   credits2_snd->setVolume(music_volume/2);
				   credits3_snd->setVolume(music_volume/2);
               }
                
           }  
       }              
       if(sad_sfx == NO_ANIM)
       {
           sad_snd->stop();
       //    sad_snd->reset();     
           sad_sfx = WAIT;
       }     
       if(sad_sfx == RESET_MUSIC)
       {    
           sad_snd->stop();           
           sad_snd->reset();
           sad_sfx = WAIT;
       }                   
       if(sad_sfx == PLAY || sad_sfx == FADE_IN)
       { 
		   if(sad_snd->isPlaying() == false)
               sad_snd->play();              

           if(sad_sfx == PLAY)     
           {      
               sad_sfx = LOOP;     
                
               if(half_volume == false)
                   sad_snd->setVolume(music_volume);
               else
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   sad_snd->setVolume(music_volume/2);
               }
               
           } 
       }
       if(intro_sfx == NO_ANIM)                                
       {   
           intro_snd->stop();        
           intro_snd->reset();   
           intro_sfx = WAIT;    
       }               
       if(intro_sfx == PLAY || intro_sfx == FADE_IN)
       {       
		   if(intro_snd->isPlaying() == false)
               intro_snd->play();     
                
           if(intro_sfx == PLAY)      
           {            
               intro_sfx = LOOP;     
                
               intro_snd->setVolume(music_volume);
               
/*               if(game_mode == WALK)
                   intro_snd->setVolume(music_volume);
               else
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   intro_snd->setVolume(music_volume/2);
               }*/
                
           }       
       } 
       if(mini_sfx == NO_ANIM)                                 
       {   
           mini_snd->stop();    
       //    mini_snd->reset();   
           mini_sfx = WAIT;
       }  
       if(mini_sfx == RESET_MUSIC)     
       {    
           mini_snd->stop();           
           mini_snd->reset();
           mini_sfx = WAIT;      
       } 
                             
       if(mini_sfx == PLAY || mini_sfx == FADE_IN)
       {       

		   if(mini_snd->isPlaying() == false)
               mini_snd->play();              

           if(mini_sfx == PLAY)      
           {      
               mini_sfx = LOOP;     
                
               if(half_volume == false)
                   mini_snd->setVolume(music_volume);
               else
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   mini_snd->setVolume(music_volume/2);
               }
               
           } 
                          
       }         
       if(urgency_sfx == NO_ANIM)                                
       {
           urgency_snd->stop();   
       //    urgency_snd->reset();   
           urgency_sfx = WAIT; 
       }               
       if(urgency_sfx == PLAY || urgency_sfx == FADE_IN)
       {       
		   if(urgency_snd->isPlaying() == false)
               urgency_snd->play();
           
           if(urgency_sfx == PLAY)      
           {      
               urgency_sfx = LOOP;      
                
               if(half_volume == false)
                   urgency_snd->setVolume(music_volume);
               else
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   urgency_snd->setVolume(music_volume/2);
               }
                
           }       
       }          
       if(fanfare_sfx == NO_ANIM)                                
       {
           fanfare_snd->stop();   
           fanfare_snd->reset();         
           fanfare_sfx = WAIT;
       }               
       if(fanfare_sfx == PLAY || fanfare_sfx == FADE_IN)
       { 
		   if(fanfare_snd->isPlaying() == false)
               fanfare_snd->play();
           
           if(fanfare_sfx == PLAY)      
           {      
               fanfare_sfx = LOOP;      
                
               if(half_volume == false)
                   fanfare_snd->setVolume(music_volume);
               else
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   fanfare_snd->setVolume(music_volume/2);
               }
                
           }  
       }             
       if(fanfare2_sfx == NO_ANIM)                                
       {
           fanfare2_snd->stop();   
           fanfare2_snd->reset();   
           fanfare2_sfx = WAIT;
       }               
       if(fanfare2_sfx == PLAY || fanfare2_sfx == FADE_IN)
       { 
		   if(fanfare2_snd->isPlaying() == false)
               fanfare2_snd->play();
           
           if(fanfare2_sfx == PLAY)      
           {      
               fanfare2_sfx = LOOP;      
                
               if(half_volume == false)
                   fanfare2_snd->setVolume(music_volume);
               else
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   fanfare2_snd->setVolume(music_volume/2);
               }
                
           }  
       }   
       if(deathscreen_sfx == NO_ANIM)                                
       {
           deathscreen_snd->stop();   
           deathscreen_snd->reset();         
           deathscreen_sfx = WAIT;
       }               
       if(deathscreen_sfx == PLAY || deathscreen_sfx == FADE_IN)
       { 
		   if(deathscreen_snd->isPlaying() == false)
               deathscreen_snd->play();
           
           if(deathscreen_sfx == PLAY)      
           {      
               deathscreen_sfx = LOOP;      
                
               if(half_volume == false)
                   deathscreen_snd->setVolume(music_volume);
               else
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   deathscreen_snd->setVolume(music_volume/2);
               }   
                
           }    
       }               

       if(dgnb_sfx == NO_ANIM)
       {
           dgnb_snd->stop();
           dgnb_snd->reset();  
           dgnb_sfx = WAIT;
       }               
       if(dgnb_sfx == PLAY || dgnb_sfx == FADE_IN)
       { 
		   if(dgnb_snd->isPlaying() == false)
               dgnb_snd->play();
           
           if(dgnb_sfx == PLAY)      
           {      
               dgnb_sfx = LOOP;      
                
               if(half_volume == false)
                   dgnb_snd->setVolume(music_volume);
               else
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   dgnb_snd->setVolume(music_volume/2);
               }
                
           }  
       }    
       if(final_sfx == NO_ANIM)
       {
           final_snd->stop(); 
           final_snd->reset(); 
           final_sfx = WAIT;
       }               
       if(final_sfx == PLAY || final_sfx == FADE_IN)
       { 
		   if(final_snd->isPlaying() == false)
               final_snd->play();
           
           if(final_sfx == PLAY)      
           {      
               final_sfx = LOOP;      
                
               if(half_volume == false)
                   final_snd->setVolume(music_volume);
               else
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   final_snd->setVolume(music_volume/2);
               }
                
           }  
       }         
       if(dangers_sfx == NO_ANIM)
       {
           dangers_snd->stop();
           dangers_snd->reset();  
           dangers_sfx = WAIT;
       }      
               
       if(dangers_sfx == PLAY || dangers_sfx == FADE_IN)
       { 
		   if(dangers_snd->isPlaying() == false)
               dangers_snd->play(); 
           
           if(dangers_sfx == PLAY)      
           {      
               dangers_sfx = LOOP;      
                
               if(half_volume == false)
                   dangers_snd->setVolume(music_volume);
               else
               {
                   temp_music_volume = music_volume/2;
                   
                   if(temp_music_volume < 0.0f)
                       temp_music_volume = 0.0f;
                       
                   dangers_snd->setVolume(music_volume/2);
               } 
                
           }         
       }        

        
       } // music_volume != 0.0

	    
	   //       
	   // SFX start.......     
	   //      
  

       if(vg_round_sfx == true)                  
       {     
           vg_round_sfx = false;  
            
		   vg_round1_snd->setVolume(sfx_volume);
		   vg_round2_snd->setVolume(sfx_volume);
		   vg_round3_snd->setVolume(sfx_volume);
		   vg_round4_snd->setVolume(sfx_volume);
		   vg_round5_snd->setVolume(sfx_volume);
		   vg_round6_snd->setVolume(sfx_volume);

           if(VG_ROUND == 1)         
               vg_round1_snd->play(); 
           if(VG_ROUND == 2)         
               vg_round2_snd->play(); 
           if(VG_ROUND == 3)         
               vg_round3_snd->play(); 
           if(VG_ROUND == 4)         
               vg_round4_snd->play(); 
           if(VG_ROUND == 5)         
               vg_round5_snd->play(); 
           if(VG_ROUND == 6)         
               vg_round6_snd->play(); 

                
       }  

       if(VG_yell_sfx != -1)                                                                               
       {         

			if(VG_yell_sfx == VG_GYEONG) 
			{
				YELL_gyeong_snd->setVolume(sfx_volume); 
				YELL_gyeong_snd->play();
			}
			if(VG_yell_sfx == VG_SIU)
			{
				YELL_siu_snd->setVolume(sfx_volume); 
				YELL_siu_snd->play();
			}
			if(VG_yell_sfx == VG_MINSO)
			{
				YELL_minso_snd->setVolume(sfx_volume);
				YELL_minso_snd->play();
			}
			if(VG_yell_sfx == VG_REESE)
			{
				YELL_reese_snd->setVolume(sfx_volume);
				YELL_reese_snd->play(); 
			}
			if(VG_yell_sfx == VG_YOHAN)
			{
				YELL_yohan_snd->setVolume(sfx_volume); 
				YELL_yohan_snd->play(); 
			}
			if(VG_yell_sfx == VG_JAE)   
			{
				YELL_jae_snd->setVolume(sfx_volume); 
				YELL_jae_snd->play(); 
			}
			if(VG_yell_sfx == VG_GUN)
			{
				YELL_gun_snd->setVolume(sfx_volume); 
				YELL_gun_snd->play();   
			}
			if(VG_yell_sfx == VG_HYUK) 
			{
				YELL_hyuk_snd->setVolume(sfx_volume);
				YELL_hyuk_snd->play();    
			}
			if(VG_yell_sfx == VG_SANG) 
			{
				YELL_sang_snd->setVolume(sfx_volume);
				YELL_sang_snd->play();   
			}
			if(VG_yell_sfx == VG_TRAINER)
			{
				YELL_trainer_snd->setVolume(sfx_volume);
				YELL_trainer_snd->play();
			}
			if(VG_yell_sfx == VG_KENNEDY)
			{
				YELL_gun_snd->setVolume(sfx_volume); 
				YELL_gun_snd->play();   
			}

		   VG_yell_sfx = -1;

	   }

       if(VG_victory_sfx != -1)                                                                              
       {          
		   WIN_gyeong_snd->setVolume(sfx_volume);   
		   WIN_siu_snd->setVolume(sfx_volume); 
		   WIN_minso_snd->setVolume(sfx_volume);      
		   WIN_reese_snd->setVolume(sfx_volume);    
		   WIN_yohan_snd->setVolume(sfx_volume); 
		   WIN_jae_snd->setVolume(sfx_volume); 
		   WIN_gun_snd->setVolume(sfx_volume);    
		   WIN_hyuk_snd->setVolume(sfx_volume);  
		   WIN_sang_snd->setVolume(sfx_volume);
		   WIN_trainer_snd->setVolume(sfx_volume);         

			if(VG_victory_sfx == VG_GYEONG)   
				WIN_gyeong_snd->play();
			if(VG_victory_sfx == VG_SIU)
				WIN_siu_snd->play();
			if(VG_victory_sfx == VG_MINSO)
				WIN_minso_snd->play();
			if(VG_victory_sfx == VG_REESE)
				WIN_reese_snd->play(); 
			if(VG_victory_sfx == VG_YOHAN)
				WIN_yohan_snd->play(); 
			if(VG_victory_sfx == VG_JAE)   
				WIN_jae_snd->play(); 
			if(VG_victory_sfx == VG_GUN)
				WIN_gun_snd->play();   
			if(VG_victory_sfx == VG_HYUK) 
				WIN_hyuk_snd->play();    
			if(VG_victory_sfx == VG_SANG) 
				WIN_sang_snd->play();   
			if(VG_victory_sfx == VG_TRAINER)
				WIN_trainer_snd->play();
			if(VG_victory_sfx == VG_KENNEDY)
				WIN_gun_snd->play();  

		   VG_victory_sfx = -1; 

	   }
       if(VG_1_special1_sfx != 0)                                                                             
       {       
		    
		   if(sfx_volume > 0.0f)
		   if(VG_1_special1_sfx == 1) // Stop the sound...
		   { 
			   // Was stop...removed for bug crash...
		   }
		   else
		   {

			   if(VG_1_CHARACTER == VG_GYEONG)
			   {
				    gyeong_snd->setVolume(sfx_volume);
					gyeong_snd->play();
			   }
			   if(VG_1_CHARACTER == VG_SIU)
			   {
				    siu_snd->setVolume(sfx_volume); 
					siu_snd->play();
			   }
			   if(VG_1_CHARACTER == VG_MINSO)
			   {
				    minso_snd->setVolume(sfx_volume); 
					minso_snd->play();
			   }
			   if(VG_1_CHARACTER == VG_REESE)
			   {
				    reese_snd->setVolume(sfx_volume); 
					reese_snd->play();
			   }
			   if(VG_1_CHARACTER == VG_YOHAN)
			   {
				    yohan_snd->setVolume(sfx_volume); 
					yohan_snd->play();
			   }
			   if(VG_1_CHARACTER == VG_JAE)
			   {
				    jae_snd->setVolume(sfx_volume); 
					jae_snd->play();
			   }
			   if(VG_1_CHARACTER == VG_GUN) 
			   {
				    gun_snd->setVolume(sfx_volume); 
					gun_snd->play();
			   }
			   if(VG_1_CHARACTER == VG_HYUK)
			   {
				    hyuk_snd->setVolume(sfx_volume); 
					hyuk_snd->play();
			   }
			   if(VG_1_CHARACTER == VG_SANG)
			   {
				    sang_snd->setVolume(sfx_volume); 
					sang_snd->play();
			   }
			   if(VG_1_CHARACTER == VG_TRAINER)
			   {    
				    trainer_snd->setVolume(sfx_volume); 
					trainer_snd->play();
			   }
			   if (VG_1_CHARACTER == VG_SHO)
			   {
				   siu_snd->setVolume(sfx_volume);
				   siu_snd->play();
			   }
			   if (VG_1_CHARACTER == VG_SAIZO)
			   {
				   hyuk_snd->setVolume(sfx_volume);
				   hyuk_snd->play();
			   }
			   if (VG_1_CHARACTER == VG_TIA)
			   {
				   minso_snd->setVolume(sfx_volume);
				   minso_snd->play();
			   }
			   if(VG_1_CHARACTER == VG_KENNEDY) 
			   {
				    gun_snd->setVolume(sfx_volume); 
					gun_snd->play();
			   }


		   } // else

           VG_1_special1_sfx = 0;   
           
       }   

       if(VG_2_special1_sfx != 0)                                                                             
       {         
		    
		   if(sfx_volume > 0.0f)
		   if(VG_2_special1_sfx == 1) // Stop the sound...
		   {
			   // Was stop...removed for bug crash...
		   }  
		   else
		   {  
			   if(VG_2_CHARACTER == VG_GYEONG) 
			   {
				    gyeong2_snd->setVolume(sfx_volume);
					gyeong2_snd->play();
			   }
			   if(VG_2_CHARACTER == VG_SIU)
			   {
				    siu2_snd->setVolume(sfx_volume); 
					siu2_snd->play();
			   }
			   if(VG_2_CHARACTER == VG_MINSO)
			   {
				    minso2_snd->setVolume(sfx_volume); 
					minso2_snd->play();
			   }
			   if(VG_2_CHARACTER == VG_REESE)
			   {
				    reese2_snd->setVolume(sfx_volume); 
					reese2_snd->play();
			   }
			   if(VG_2_CHARACTER == VG_YOHAN)
			   {
				    yohan_snd->setVolume(sfx_volume); 
					yohan_snd->play();
			   }
			   if(VG_2_CHARACTER == VG_JAE)
			   {
				    jae2_snd->setVolume(sfx_volume); 
					jae2_snd->play();
			   }
			   if(VG_2_CHARACTER == VG_GUN)
			   {
				    gun2_snd->setVolume(sfx_volume); 
					gun2_snd->play();
			   }
			   if(VG_2_CHARACTER == VG_HYUK)
			   {
				    hyuk2_snd->setVolume(sfx_volume); 
					hyuk2_snd->play();
			   }
			   if(VG_2_CHARACTER == VG_SANG)
			   {
				    sang2_snd->setVolume(sfx_volume); 
					sang2_snd->play();
			   }
			   if(VG_2_CHARACTER == VG_TRAINER)
			   {
				    trainer2_snd->setVolume(sfx_volume); 
					trainer2_snd->play();
			   }
			   if(VG_2_CHARACTER == VG_KENNEDY)
			   {
				    gun2_snd->setVolume(sfx_volume); 
					gun2_snd->play();
			   }
			    
		   } // else

           VG_2_special1_sfx = 0;   
           
       }                                                              
         
       if(vg_titleselect_sfx == true)                   
       {      
           vg_titleselect_sfx = false;     
           vg_titleselect_snd->setVolume(sfx_volume);     
                    
           vg_titleselect_snd->play();  
            
       } 
       if(vg_gameover_sfx == true)                  
       {     
           vg_gameover_sfx = false;   
           vg_gameover_snd->setVolume(sfx_volume); 
           vg_gameover_snd->play();
       }     
       if(VG_title_sfx == true)                  
       {      
           VG_title_sfx = false;   
           VG_title_snd->setVolume(sfx_volume); 
           VG_title_snd->play();
       }      
       if(VG_verdict_sfx == true)                  
       {      
           VG_verdict_sfx = false;   
           VG_verdict_snd->setVolume(sfx_volume); 
           VG_verdict_snd->play();
       }  
       if(VG_knockslide_sfx == true)                  
       {     
           VG_knockslide_sfx = false;   
           vg_knockslide_snd->setVolume(sfx_volume); 
           vg_knockslide_snd->play();
       }      
       if(VG_guilty_sfx == true)                   
       {     
           VG_guilty_sfx = false;   
           VG_guilty_snd->setVolume(sfx_volume); 
           VG_guilty_snd->play();    
       }         
       if(VG_titlevoice_sfx == true)                   
       {     
           VG_titlevoice_sfx = false;   
           VG_titlevoice_snd->setVolume(sfx_volume); 
           VG_titlevoice_snd->play();    
       }      
       if(VG_pow_sfx == true)                   
       {     
           VG_pow_sfx = false;   
           VG_pow_snd->setVolume(sfx_volume); 
           VG_pow_snd->play();    
       }    
       if(VG_destiny_sfx == true)                             
       {            
           VG_destiny_sfx = false;             
           VG_destiny_snd->setVolume(sfx_volume); 
           VG_destiny_snd->play();
       }  
       if(VG_alright_sfx == true)                       
       {     
           VG_alright_sfx = false;   
           VG_alright_snd->setVolume(sfx_volume); 
           VG_alright_snd->play();
       }   
       if(VG_nice_sfx == true)                       
       {      
           VG_nice_sfx = false;   
           VG_nice_snd->setVolume(sfx_volume); 
           VG_nice_snd->play();
       }   
       if(VG_okay_sfx == true)                       
       {     
           VG_okay_sfx = false;   
           VG_okay_snd->setVolume(sfx_volume); 
           VG_okay_snd->play();
       }   
	     
       if(vg_judge_sfx == true)                  
       {     
           vg_judge_sfx = false;  
		   YELL_judge_snd->setVolume(sfx_volume);
		   YELL_judge_snd->play();
       }  

       if(VG_good_sfx == true)                  
       {     
           VG_good_sfx = false;   
           VG_good_snd->setVolume(sfx_volume); 
           VG_good_snd->play();
       }   
       if(VG_great_sfx == true)                  
       {     
           VG_great_sfx = false;   
           VG_great_snd->setVolume(sfx_volume); 
           VG_great_snd->play();
       }   
       if(VG_excellent_sfx == true)                  
       {     
           VG_excellent_sfx = false;   
           VG_excellent_snd->setVolume(sfx_volume); 
           VG_excellent_snd->play();
       }   
                         
       if(VG_reloadsfx == 1)     
       { 
           VG_reloadsfx = 2;  
           vg_reload_snd->setVolume(sfx_volume);              
           vg_reload_snd->play();            
       }                   
                  
       if(VG_reloadedsfx == 1)
       { 
           VG_reloadedsfx = 2;  
           vg_reloaded_snd->setVolume(sfx_volume);               
           vg_reloaded_snd->play();       
       }   
                  
       if(VG_handcuffs_sfx == true)
       { 
           VG_handcuffs_sfx = false;  
           vg_reloaded_snd->setVolume(sfx_volume);               
           vg_reloaded_snd->play();       
       }    

       if(vg_perfect_sfx == true)
       {
           vg_perfect_sfx = false;  
           vg_perfect_snd->setVolume(sfx_volume);             
           vg_perfect_snd->play();        
       }            

       if(VG_arrested_sfx == true)                     
       {     
           VG_arrested_sfx = false;
		   vg_arrested_snd->setVolume(sfx_volume);            
		   vg_arrested_snd->play();  
	   }
       if(VG_wasted_sfx == true)                     
       {     
           VG_wasted_sfx = false;
		   vg_wasted_snd->setVolume(sfx_volume);            
		   vg_wasted_snd->play();  
	   }

       if(VG_power_sfx == true)                     
       {     
           VG_power_sfx = false;

		   rnd = rand()%4;
		    
		   if(rnd == 0)  
		   {     
			   vg_power1_snd->setVolume(sfx_volume);            
			   vg_power1_snd->play();       
		   } 
		   if(rnd == 1) 
		   {
			   vg_power2_snd->setVolume(sfx_volume);            
			   vg_power2_snd->play();       
		   }
		   if(rnd == 2) 
		   {
			   vg_power3_snd->setVolume(sfx_volume);            
			   vg_power3_snd->play();       
		   }
		   if(rnd == 3) 
		   {
			   vg_power4_snd->setVolume(sfx_volume);            
			   vg_power4_snd->play();       
		   }
	   } 

       if(VG_KO_sfx == true)                     
       {      
           VG_KO_sfx = false;        
		          
		   if(VG_KOED_CHARACTER == VG_GYEONG)  
		   {     
			   vg_ko_1_snd->setVolume(sfx_volume);            
			   vg_ko_1_snd->play();       
		   } 
		   if(VG_KOED_CHARACTER == VG_SIU)
		   {
			   vg_ko_2_snd->setVolume(sfx_volume);            
			   vg_ko_2_snd->play();       
		   }
		   if(VG_KOED_CHARACTER == VG_MINSO)
		   {
			   vg_ko_3_snd->setVolume(sfx_volume);            
			   vg_ko_3_snd->play();       
		   }
		   if(VG_KOED_CHARACTER == VG_REESE)
		   {
			   vg_ko_4_snd->setVolume(sfx_volume);            
			   vg_ko_4_snd->play();       
		   }
		   if(VG_KOED_CHARACTER == VG_YOHAN)
		   {
			   vg_ko_5_snd->setVolume(sfx_volume);            
			   vg_ko_5_snd->play();       
		   }
		   if(VG_KOED_CHARACTER == VG_JAE)
		   {
			   vg_ko_6_snd->setVolume(sfx_volume);            
			   vg_ko_6_snd->play();       
		   }
		   if(VG_KOED_CHARACTER == VG_GUN)
		   {
			   vg_ko_7_snd->setVolume(sfx_volume);            
			   vg_ko_7_snd->play();       
		   }
		   if(VG_KOED_CHARACTER == VG_HYUK)
		   {
			   vg_ko_8_snd->setVolume(sfx_volume);            
			   vg_ko_8_snd->play();       
		   }
		   if(VG_KOED_CHARACTER == VG_SANG)
		   {
			   vg_ko_9_snd->setVolume(sfx_volume);            
			   vg_ko_9_snd->play();       
		   }
		   if(VG_KOED_CHARACTER == VG_TRAINER)
		   {
			   vg_ko_10_snd->setVolume(sfx_volume);            
			   vg_ko_10_snd->play();       
		   }
		   if(VG_KOED_CHARACTER == VG_SHO)
		   {
			   vg_ko_11_snd->setVolume(sfx_volume);            
			   vg_ko_11_snd->play();       
		   }
		   if(VG_KOED_CHARACTER == VG_TIA)
		   {
			   vg_ko_12_snd->setVolume(sfx_volume);            
			   vg_ko_12_snd->play();       
		   }
		   if(VG_KOED_CHARACTER == VG_SAIZO)
		   {
			   vg_ko_13_snd->setVolume(sfx_volume);            
			   vg_ko_13_snd->play();       
		   }
		   if(VG_KOED_CHARACTER == VG_KENNEDY)
		   {
			   vg_ko_14_snd->setVolume(sfx_volume);            
			   vg_ko_14_snd->play();       
		   }

       }

       if(vg_ko_smash_sfx == true)                     
       {     
           vg_ko_smash_sfx = false;        
			
		   VG_rnd = rand()%4;    
		          
		   if(VG_rnd == 0)  
		   {     
			   vg_ko_snd->setVolume(sfx_volume);            
			   vg_ko_snd->play();       
		   } 
		   if(VG_rnd == 1)
		   {
			   vg_ko1_snd->setVolume(sfx_volume);            
			   vg_ko1_snd->play();       
		   }
		   if(VG_rnd == 2)
		   { 
			   vg_ko2_snd->setVolume(sfx_volume);             
			   vg_ko2_snd->play();       
		   }
		   if(VG_rnd == 3)
		   { 
			   vg_ko3_snd->setVolume(sfx_volume);            
			   vg_ko3_snd->play();       
		   }

       }
                          
                              
       if(vg_fight_sfx == true)  
       {
           vg_fight_sfx = false;         
           vg_fight_snd->setVolume(sfx_volume);                   
           vg_fight_snd->play();        
       }     
     
       if(vg_amb_car1_sfx == true)    
       {   
           vg_amb_car1_sfx = false;  

           vg_amb_car1_snd->setVolume(sfx_volume);
         
           vg_amb_car1_snd->play();                  
       }       
             
       if(vg_amb_car2_sfx == true)
       {
           vg_amb_car2_sfx = false;  

           vg_amb_car2_snd->setVolume(sfx_volume);
         
           vg_amb_car2_snd->play();  
       
                               
       }
       
       if(vg_blocked_sfx == true)
       {
           vg_blocked_sfx = false;  
           vg_blocked_snd->setVolume(sfx_volume);            
           vg_blocked_snd->play();       
       }
       
       if(vg_knockdown_sfx == true)
       {
           vg_knockdown_sfx = false;  
           vg_knockdown_snd->setVolume(sfx_volume);            
           vg_knockdown_snd->play();       
       }

	   if(vg_shout_sfx == true)
       {      
           vg_shout_sfx = false;         
           vg_shout_snd->setVolume(sfx_volume);                              
           vg_shout_snd->play();             
       }   
       if(vg_siren_sfx == true)
       {      
           vg_siren_sfx = false;         
           vg_siren_snd->setVolume(sfx_volume);                              
           vg_siren_snd->play();             
       }   

       if(vg_titlemove_sfx == true)  
       {
           vg_titlemove_sfx = false;
           vg_titlemove_snd->setVolume(sfx_volume);               
           vg_titlemove_snd->play();        
       }    

       if(vg_vacuum_sfx == true)  
       {
           vg_vacuum_sfx = false;
           vg_vacuum_snd->setVolume(sfx_volume);               
           vg_vacuum_snd->play();        
       }      


                                           
       if(vg_title_move_sfx == true)
       {      
           vg_title_move_sfx = false;         
           vg_title_move->setVolume(sfx_volume);                              
           vg_title_move->play();             
       }        
 
                 
       if(VG_1_Mgunsfx != 0)           
       {
           vg_mgun_snd->setVolume(sfx_volume);
           if(VG_1_Mgunsfx == 1)
			   vg_mgun_snd->play();

		   VG_1_Mgunsfx = 2;

        
       }                     
  
       if(VG_2_Mgunsfx != 0)      
       {               
           vg_mgun_snd->setVolume(sfx_volume);
           if(VG_2_Mgunsfx == 1) 
			   vg_mgun_snd->play();

		   VG_2_Mgunsfx = 2;

              
       }	 
       if(VG_1_Vialsfx != 0)            
       {
           vg_knife_snd->setVolume(sfx_volume);
           if(VG_1_Vialsfx == 1) 
			   vg_knife_snd->play();
		      
		   VG_1_Vialsfx = 2; 
  
       }                          
   
       if(VG_2_Vialsfx != 0)       
       {               
           vg_knife_snd->setVolume(sfx_volume);
           if(VG_2_Vialsfx == 1)
			   vg_knife_snd->play();

		   VG_2_Vialsfx = 2;
          
       }	
       if(VG_1_Pfpsfx != 0)            
       {
           vg_knife_snd->setVolume(sfx_volume);
           if(VG_1_Pfpsfx == 1) 
			   vg_knife_snd->play();
		      
		   VG_1_Pfpsfx = 2; 
  
       }                          
  
       if(VG_2_Pfpsfx != 0)      
       {               
           VG_land_snd->setVolume(sfx_volume);
           if(VG_2_Pfpsfx == 1)
			   VG_land_snd->play();

		   VG_2_Pfpsfx = 2;
          
       }	
       if(VG_1_Knifesfx != 0)           
       {
           VG_land_snd->setVolume(sfx_volume);
           if(VG_1_Knifesfx == 1)
			   VG_land_snd->play();

		   VG_1_Knifesfx = 2;

        
       }                     
  
       if(VG_2_Knifesfx != 0)      
       {               
           vg_knife_snd->setVolume(sfx_volume);
           if(VG_2_Knifesfx == 1)
			   vg_knife_snd->play();

		   VG_2_Knifesfx = 2;

             
       }	
       if(VG_1_Grenadesfx != 0)           
       {
           vg_knife_snd->setVolume(sfx_volume);
           if(VG_1_Grenadesfx == 1)
			   vg_knife_snd->play();

		   VG_1_Grenadesfx = 2;

        
       }                     
   
       if(VG_2_Grenadesfx != 0)      
       {               
           vg_knife_snd->setVolume(sfx_volume);

           if(VG_2_Grenadesfx == 1) 
			   vg_knife_snd->play();  

		   VG_2_Grenadesfx = 2;

             
       }	
       if(VG_1_Pistolsfx != 0)           
       {
           vg_pistol1_snd->setVolume(sfx_volume); 
		   vg_shotgun1_snd->setVolume(sfx_volume);
		   vg_orb_snd->setVolume(sfx_volume);

		   if(VG_1_Pistolsfx == 1)
		   {
			   if(VG_1_CHARACTER == VG_REESE || VG_1_CHARACTER == VG_SHO || VG_1_CHARACTER == VG_TIA || VG_1_CHARACTER == VG_SAIZO)
			   {
				   vg_orb_snd->play();    
			   }
			   else
			   {
				   if(VG_1_CHARACTER != VG_TRAINER)
					   vg_pistol1_snd->play();
				   else
					   vg_shotgun1_snd->play();    
			   }
		   }
		    
		   VG_1_Pistolsfx = 2; 
         
       }                     
   
       if(VG_2_Pistolsfx != 0)       
       {           

           vg_pistol2_snd->setVolume(sfx_volume);
		   vg_shotgun2_snd->setVolume(sfx_volume);
		   vg_orb2_snd->setVolume(sfx_volume);

           if(VG_2_Pistolsfx == 1)
		   {
			   if(VG_2_CHARACTER == VG_REESE || VG_2_CHARACTER == VG_SHO || VG_2_CHARACTER == VG_TIA || VG_2_CHARACTER == VG_SAIZO)
			   {
				   vg_orb2_snd->play();    
			   }
			   else
			   {
				   if(VG_2_CHARACTER != VG_TRAINER)
					   vg_pistol2_snd->play();
				   else
					   vg_shotgun2_snd->play();
			   }
		   }

		   VG_2_Pistolsfx = 2;
             
       }	 

       if(vg_lose_sfx == true ) 
       {     
           vg_lose_sfx = false;     
           vg_lose_snd->setVolume(sfx_volume);               
           vg_lose_snd->play();       
              
       }    
                    
       if(vg_tink_sfx == true)
       {
           vg_tink_sfx = false;
           vg_tink_snd->setVolume(sfx_volume);                                 
           vg_tink_snd->play();       
                   
       }                   
               
       if(vg_ric_sfx == true)
       { 
           vg_ric_sfx = false;                                

           vg_ric1_snd->setVolume(sfx_volume);                
           vg_ric2_snd->setVolume(sfx_volume);                
           vg_ric3_snd->setVolume(sfx_volume);                
			
		   VG_rnd = rand()%3;    

		   if(VG_rnd == 0)
	           vg_ric1_snd->play();                                                                     
		   if(VG_rnd == 1)
	           vg_ric2_snd->play();                                                                     
		   if(VG_rnd == 2)
	           vg_ric3_snd->play();                                                                     

                                          
       }            
              
                            
       if(vg_shock_sfx == true)                     
       {     
           vg_shock_sfx = false;
           vg_shock_snd->setVolume(sfx_volume);     
           vg_shock_snd->play();                  
       }           
                   
       if(VG_1_chop_sfx == 1)  
       {   
	       vg_chop_snd->setVolume(sfx_volume);   
		   vg_chop1_snd->setVolume(sfx_volume);
		   vg_chop2_snd->setVolume(sfx_volume);
		   vg_chop3_snd->setVolume(sfx_volume);

           if(VG_1_chop_sfx == 1)
		   {
			   VG_rnd = rand()%4;

			   if(VG_rnd == 0)
				  vg_chop_snd->play();   
			   if(VG_rnd == 1)
			      vg_chop1_snd->play();   
			   if(VG_rnd == 2)
			      vg_chop2_snd->play();   
			   if(VG_rnd == 3)
			      vg_chop3_snd->play();   

		   }
               
           VG_1_chop_sfx = 2; 
                   
       }     
       if(VG_2_chop_sfx == 1) 
       {       
	       vg_chop_snd->setVolume(sfx_volume);   
		   vg_chop1_snd->setVolume(sfx_volume);
		   vg_chop2_snd->setVolume(sfx_volume);
		   vg_chop3_snd->setVolume(sfx_volume);

           if(VG_2_chop_sfx == 1)
		   {
			   VG_rnd = rand()%4;

			   if(VG_rnd == 0)
				  vg_chop_snd->play();   
			   if(VG_rnd == 1)
			      vg_chop1_snd->play();   
			   if(VG_rnd == 2)
			      vg_chop2_snd->play();   
			   if(VG_rnd == 3)
			      vg_chop3_snd->play();   
		   }
               
           VG_2_chop_sfx = 2;
                   
       }        
       if(vg_explode_sfx == true)      
       {  
           vg_explode_sfx = false;
           vg_explode_snd->setVolume(sfx_volume);                       
           vg_explode_snd->play();              
                 
       }                           
       if(vg_splat_sfx == true)      
       {  
           vg_splat_sfx = false;
           vg_splat_snd->setVolume(sfx_volume);                       
           vg_splat_snd->play();              
                 
       }                            
       if(vg_win_sfx == true) 
       {   
           vg_win_sfx = false; 
           vg_win_snd->setVolume(sfx_volume);         
           vg_win_snd->play();        
                           
       }         
            
       if(vg_glass_sfx == true)  
       {  
           vg_glass_sfx = false; 
 
	        vg_glass1_snd->setVolume(sfx_volume);  
	        vg_glass2_snd->setVolume(sfx_volume);   
	        vg_glass3_snd->setVolume(sfx_volume); 
	        vg_glass4_snd->setVolume(sfx_volume);

           VG_rnd = rand()%4;    
                                                                      
           if(VG_rnd == 0)                                                          
               vg_glass1_snd->play();                               
           if(VG_rnd == 1)       
               vg_glass2_snd->play();                            
           if(VG_rnd == 2)     
               vg_glass3_snd->play();  
           if(VG_rnd == 3)                
               vg_glass4_snd->play();                                    
              
       }        
                 
       if(vg_hitsound_sfx == true)  
       {  
           vg_hitsound_sfx = false; 
 
	        vg_hitsound_snd->setVolume(sfx_volume);
			vg_hitsound1_snd->setVolume(sfx_volume);  
	        vg_hitsound2_snd->setVolume(sfx_volume);   
	        vg_hitsound3_snd->setVolume(sfx_volume); 
	        vg_hitsound4_snd->setVolume(sfx_volume);
	        vg_hitsound5_snd->setVolume(sfx_volume);  
	        vg_hitsound6_snd->setVolume(sfx_volume);   
	        vg_hitsound7_snd->setVolume(sfx_volume); 

           VG_rnd = rand()%8;    
                                                                      
           if(VG_rnd == 0)                                                          
               vg_hitsound_snd->play();                               
           if(VG_rnd == 1)       
               vg_hitsound1_snd->play();                            
           if(VG_rnd == 2)     
               vg_hitsound2_snd->play();  
           if(VG_rnd == 3)                
               vg_hitsound3_snd->play(); 
           if(VG_rnd == 4)                                                          
               vg_hitsound4_snd->play();                               
           if(VG_rnd == 5)       
               vg_hitsound5_snd->play();                            
           if(VG_rnd == 6)     
               vg_hitsound6_snd->play();  
           if(VG_rnd == 7)                
               vg_hitsound7_snd->play();                                    
              
              
       }                
   

                       
       if(vg_dogattack_sfx == true)   
       { 
           vg_dogattack_sfx = false; 
           vg_dogattack_snd->setVolume(sfx_volume);   
           vg_dogattack_snd->play();       
                 
       }  


       if(vg_stamp_sfx == true) 
       { 
            
           vg_stamp_snd->setVolume(sfx_volume); 
                               
           vg_stamp_snd->play();
           
           vg_stamp_sfx = false; 
                       
       }         
      
       if(VG_land_sfx == true)
       { 
 
           VG_land_snd->setVolume(sfx_volume); 
                                    
           VG_land_snd->play();      
                                                                     
           VG_land_sfx = false;       
                                                 
       }                          
       
       if(vg_amb_prison_sfx == true)       
       {
//           untie_snd->reset();          
           vg_amb_prison_snd->setVolume(sfx_volume);                     
           vg_amb_prison_snd->play();  
            
           vg_amb_prison_sfx = false;     
                        
       }    
                   
       if(vg_amb_subway_sfx == true)
       {          
           vg_amb_subway_snd->reset();       
                    
           vg_amb_subway_snd->setVolume(sfx_volume);                                
           vg_amb_subway_snd->setRepeat(false);    
                                         
           vg_amb_subway_snd->play();        
           
           vg_amb_subway_sfx = false; 
                 
       }                                                    
         
       if(vg_amb_traffic_sfx == true)                    
       {         
           vg_amb_traffic_snd->reset();       
                    
           vg_amb_traffic_snd->setVolume(sfx_volume);                                
           vg_amb_traffic_snd->setRepeat(true);    
                                         
           vg_amb_traffic_snd->play();        
           
           vg_amb_traffic_sfx = false;     
                                       
       }  
     
       if(vg_amb_duel_sfx == true)                
       {
           vg_amb_duel_snd->reset();       
              
           vg_amb_duel_snd->setVolume(sfx_volume);                                
           vg_amb_duel_snd->setRepeat(true);    
                           
           vg_amb_duel_snd->play();  
           
           vg_amb_duel_sfx = false;       
                                       
       }    

       if(vg_amb_van_sfx == true)                
       {
           vg_amb_van_snd->reset();       
              
           vg_amb_van_snd->setVolume(sfx_volume);                                
           vg_amb_van_snd->setRepeat(true);    
                           
           vg_amb_van_snd->play();  
           
           vg_amb_van_sfx = false;       
                                       
       }                     
 
       if(stop_vg_amb_prison_sfx==true)      
       { 
                                  
		   if(vg_amb_prison_snd->isPlaying() == true)
               vg_amb_prison_snd->stop();                 

           vg_amb_prison_snd->reset();               
                               
           stop_vg_amb_prison_sfx=false;    
       } 
             
       if(stop_vg_amb_traffic_sfx==true)                             
       {        
           if(vg_amb_traffic_snd->isPlaying() == true)                    
               vg_amb_traffic_snd->stop();              

           vg_amb_traffic_snd->reset();           

           stop_vg_amb_traffic_sfx=false; 
       }  
             
       if(stop_vg_amb_subway_sfx==true)                                  
       {        
           if(vg_amb_subway_snd->isPlaying() == true)                    
               vg_amb_subway_snd->stop();              

           vg_amb_subway_snd->reset();           

           stop_vg_amb_subway_sfx=false; 
       }  

       if(stop_vg_amb_van_sfx==true)                      
       {  
           if(vg_amb_van_snd->isPlaying() == true)                    
               vg_amb_van_snd->stop();      

           vg_amb_van_snd->reset();           
                               
           stop_vg_amb_van_sfx=false;
       }           
 
       if(stop_vg_amb_duel_sfx==true)                      
       {  
           if(vg_amb_duel_snd->isPlaying() == true)                    
               vg_amb_duel_snd->stop();      

           vg_amb_duel_snd->reset();           
                               
           stop_vg_amb_duel_sfx=false;
       }         
       
       
    }  
                      
    mousewheel = RESET;                     
          
  }// Quit_timer == false     

    	               
  }       
                                        
  Main_cycle = (int)TimerGetTime() - Main_cycle;  
     
} // Peek_message       
          
                             
} // While not done        

    delete [] sprite; 
    delete [] Fx;     
    delete [] hud;    

    #if IS_FULL_STEAM == 1  
	  
	if(STEAM_ACTIVE == true)      
	{     

		/*SteamAPI_Shutdown();

	    if (g_SteamLeaderboards_finalscore) 
			delete g_SteamLeaderboards_finalscore;

	    if (g_SteamLeaderboards_survivalscore) 
			delete g_SteamLeaderboards_survivalscore; 

	    if (g_SteamLeaderboards_duellingscore) 
			delete g_SteamLeaderboards_duellingscore; 

	    if (g_SteamLeaderboards_turboscore) 
			delete g_SteamLeaderboards_turboscore; 

	    if (g_SteamLeaderboards_masterscore) 
			delete g_SteamLeaderboards_masterscore; 

		// Delete the SteamAchievements object
	    if (g_SteamAchievements)
		    delete g_SteamAchievements;*/
	} 
	              
	#endif 

    SaveCFG();     
	//SaveKeys();
            
    //if(DEMO_MODE == 0)       
	    //fclose(fp2); 
    
	// Shutdown
#ifdef SWITCH
	KillGLWindow();									// Kill The Window
#endif

	//return (msg.wParam);							// Exit The Program
	  
}

#elif XB1

int loop_timer = 0;
bool test = false;
int fps = 0;
int FPS = 0;
int FrameTime = 0;
int FrameTimer = 0;
int frame_rate = 0;
int f_rate1 = 0;
float jump_timing = 0;
float testX = 0.0f, testY = 0.0f;
float testX1 = 0.0f, testY1 = 0.0f;
float widthX = 0.0f, heightY = 0.0f;
float widthX1 = 0.0f, heightY1 = 0.0f;
float midX = 0.0f, midY = 0.0f;
float distance = 0.0f;
int rnd = 0;
int multi_select = 0;
int dig_select = 0;
int plane_select = 0;
int wood_select = 0;
int work_select = 0;
int food_select = 0;
int carry_select = 0;
int slash_select = 0;
int cp_select = 0;
int bk_select = 0;
int cm_select = 0;
int unit_sp_selected = -1;
bool move_the_guy = false;
int the_worker = 0;
int dig_man = 0;
int rank_man = 0;
int special_type = 0;
int k = 0, l = 0;
bool return_cargo = false;
bool building_selected = false;
int old_direction = 0;
int new_direction = 0;
int test_player = 0;
int brush_id = 0;
int temp_index = 0;
int temp_row_x = 0;
int temp_row_y = 0;
int row_x1 = 0;
int row_y1 = 0;
int sell_gold = 0;
int m_check = -1;
bool knifing = false;
bool has_ammo = false;
int hud_weapon_addition = 0;
float temp_speed = 0.0f;
int col_index = -1;
int created_a_window = 0;
int temp_horizontal = 0;
int temp_vertical = 0;

int device = 0;

SoundEffectPtr vg_arrested_snd;
SoundEffectPtr vg_wasted_snd;
SoundEffectPtr vg_power1_snd;
SoundEffectPtr vg_power2_snd;
SoundEffectPtr vg_power3_snd;
SoundEffectPtr vg_power4_snd;
SoundEffectPtr vg_ko_1_snd;
SoundEffectPtr vg_ko_2_snd;
SoundEffectPtr vg_ko_3_snd;
SoundEffectPtr vg_ko_4_snd;
SoundEffectPtr vg_ko_5_snd;
SoundEffectPtr vg_ko_6_snd;
SoundEffectPtr vg_ko_7_snd;
SoundEffectPtr vg_ko_8_snd;
SoundEffectPtr vg_ko_9_snd;
SoundEffectPtr vg_ko_10_snd;
SoundEffectPtr vg_ko_11_snd;
SoundEffectPtr vg_ko_12_snd;
SoundEffectPtr vg_ko_13_snd;
SoundEffectPtr vg_ko_14_snd;
SoundEffectPtr vg_shout_snd;
SoundEffectPtr vg_siren_snd;
SoundEffectPtr vg_title_move;
SoundEffectPtr vg_title_select;
SoundEffectPtr vg_perfect_snd;
SoundEffectPtr vg_amb_car1_snd;
SoundEffectPtr vg_amb_car2_snd;
SoundEffectPtr vg_ko_snd;
SoundEffectPtr vg_ko1_snd;
SoundEffectPtr vg_ko2_snd;
SoundEffectPtr vg_ko3_snd;
SoundEffectPtr vg_fight_snd;
SoundEffectPtr vg_blocked_snd;
SoundEffectPtr vg_knockdown_snd;
SoundEffectPtr vg_stamp_snd;
SoundEffectPtr vg_round1_snd;
SoundEffectPtr vg_round2_snd;
SoundEffectPtr vg_round3_snd;
SoundEffectPtr vg_round4_snd;
SoundEffectPtr vg_round5_snd;
SoundEffectPtr vg_round6_snd;
SoundEffectPtr VG_title_snd;
SoundEffectPtr VG_verdict_snd;
SoundEffectPtr VG_guilty_snd;
SoundEffectPtr VG_destiny_snd;
SoundEffectPtr VG_pow_snd;
SoundEffectPtr VG_titlevoice_snd;
SoundEffectPtr VG_alright_snd;
SoundEffectPtr VG_nice_snd;
SoundEffectPtr VG_okay_snd;
SoundEffectPtr VG_good_snd;
SoundEffectPtr VG_great_snd;
SoundEffectPtr VG_excellent_snd;
SoundEffectPtr gyeong_snd;
SoundEffectPtr siu_snd;
SoundEffectPtr hyuk_snd;
SoundEffectPtr gun_snd;
SoundEffectPtr jae_snd;
SoundEffectPtr minso_snd;
SoundEffectPtr reese_snd;
SoundEffectPtr yohan_snd;
SoundEffectPtr sang_snd;
SoundEffectPtr trainer_snd;
SoundEffectPtr gyeong2_snd;
SoundEffectPtr siu2_snd;
SoundEffectPtr hyuk2_snd;
SoundEffectPtr gun2_snd;
SoundEffectPtr jae2_snd;
SoundEffectPtr minso2_snd;
SoundEffectPtr reese2_snd;
SoundEffectPtr yohan2_snd;
SoundEffectPtr sang2_snd;
SoundEffectPtr trainer2_snd;
SoundEffectPtr WIN_gyeong_snd;
SoundEffectPtr WIN_siu_snd;
SoundEffectPtr WIN_hyuk_snd;
SoundEffectPtr WIN_gun_snd;
SoundEffectPtr WIN_jae_snd;
SoundEffectPtr WIN_minso_snd;
SoundEffectPtr WIN_reese_snd;
SoundEffectPtr WIN_yohan_snd;
SoundEffectPtr WIN_sang_snd;
SoundEffectPtr WIN_trainer_snd;
SoundEffectPtr YELL_gyeong_snd;
SoundEffectPtr YELL_siu_snd;
SoundEffectPtr YELL_hyuk_snd;
SoundEffectPtr YELL_gun_snd;
SoundEffectPtr YELL_jae_snd;
SoundEffectPtr YELL_minso_snd;
SoundEffectPtr YELL_reese_snd;
SoundEffectPtr YELL_yohan_snd;
SoundEffectPtr YELL_sang_snd;
SoundEffectPtr YELL_trainer_snd;
SoundEffectPtr YELL_judge_snd;
SoundEffectPtr vg_gameover_snd;
SoundEffectPtr vg_titleselect_snd;
SoundEffectPtr vg_titlemove_snd;
SoundEffectPtr vg_break_snd;
SoundEffectPtr vg_knife_snd;
SoundEffectPtr vg_vacuum_snd;
SoundEffectPtr vg_orb_snd;
SoundEffectPtr vg_orb2_snd;
SoundEffectPtr vg_pistol1_snd;
SoundEffectPtr vg_pistol2_snd;
SoundEffectPtr vg_shotgun1_snd;
SoundEffectPtr vg_shotgun2_snd;
SoundEffectPtr vg_ric1_snd;
SoundEffectPtr vg_ric2_snd;
SoundEffectPtr vg_ric3_snd;
SoundEffectPtr vg_shock_snd;
SoundEffectPtr vg_reload_snd;
SoundEffectPtr vg_reloaded_snd;
SoundEffectPtr vg_mgun_snd;
SoundEffectPtr vg_glass1_snd;
SoundEffectPtr vg_glass2_snd;
SoundEffectPtr vg_glass3_snd;
SoundEffectPtr vg_glass4_snd;
SoundEffectPtr vg_dogattack_snd;
SoundEffectPtr vg_verdict_snd;
SoundEffectPtr vg_knockslide_snd;
SoundEffectPtr VG_land_snd;
SoundEffectPtr vg_tink_snd;
SoundEffectPtr vg_chop_snd;
SoundEffectPtr vg_chop1_snd;
SoundEffectPtr vg_chop2_snd;
SoundEffectPtr vg_chop3_snd;
SoundEffectPtr vg_splat_snd;
SoundEffectPtr vg_explode_snd;
SoundEffectPtr vg_hitsound_snd;
SoundEffectPtr vg_hitsound1_snd;
SoundEffectPtr vg_hitsound2_snd;
SoundEffectPtr vg_hitsound3_snd;
SoundEffectPtr vg_hitsound4_snd;
SoundEffectPtr vg_hitsound5_snd;
SoundEffectPtr vg_hitsound6_snd;
SoundEffectPtr vg_hitsound7_snd;
SoundEffectPtr vg_win_snd;
SoundEffectPtr vg_lose_snd;
OutputStreamPtr emy1_snd;
OutputStreamPtr emy2_snd;
OutputStreamPtr emy3_snd;
OutputStreamPtr emy4_snd;
OutputStreamPtr emy5_snd;
OutputStreamPtr emy6_snd;
OutputStreamPtr emy7_snd;
OutputStreamPtr emy8_snd;
OutputStreamPtr emy9_snd;
OutputStreamPtr emy10_snd;
OutputStreamPtr emy11_snd;
OutputStreamPtr emy12_snd;
OutputStreamPtr emy13_snd;
OutputStreamPtr emy14_snd;
OutputStreamPtr jet1_snd;
OutputStreamPtr jet2_snd;
OutputStreamPtr jet3_snd;
OutputStreamPtr jet4_snd;
OutputStreamPtr siege1_snd;
OutputStreamPtr siege2_snd;
OutputStreamPtr siege3_snd;
OutputStreamPtr siege4_snd;
OutputStreamPtr siege5_snd;
OutputStreamPtr siege6_snd;
OutputStreamPtr map_grass_snd;
OutputStreamPtr map_swamp_snd;
OutputStreamPtr map_forest_snd;
OutputStreamPtr map_farm_snd;
OutputStreamPtr map_snow_snd;
OutputStreamPtr map_desert_snd;
OutputStreamPtr map_trench_snd;
OutputStreamPtr lnd_snd;
OutputStreamPtr theatre_snd;
OutputStreamPtr credits1_snd;
OutputStreamPtr credits2_snd;
OutputStreamPtr credits3_snd;
OutputStreamPtr crd_snd;
OutputStreamPtr army_snd;
OutputStreamPtr fight_snd;
OutputStreamPtr sad_snd;
OutputStreamPtr intro_snd;
OutputStreamPtr mini_snd;
OutputStreamPtr deathscreen_snd;
OutputStreamPtr urgency_snd;
OutputStreamPtr fanfare_snd;
OutputStreamPtr fanfare2_snd;
OutputStreamPtr dgnb_snd;
OutputStreamPtr final_snd;
OutputStreamPtr dangers_snd;
OutputStreamPtr vg_amb_prison_snd;
OutputStreamPtr vg_amb_traffic_snd;
OutputStreamPtr vg_amb_subway_snd;
OutputStreamPtr vg_amb_van_snd;
OutputStreamPtr vg_amb_duel_snd;

void GameInit()
{
	Init_XboxSound();

	INIT_D3D_MTX();

	SET_CLIP_MATRIX();

	SET_MVS_MATRIX();

	memset(VG_CHARACTER_LOCKS, 0, sizeof(VG_CHARACTER_LOCKS));

	GetDisplaySettings(); //enumdisplaysettings

						  //global_lpCmdLine = lpCmdLine;

						  //	MAX_horizontal = GetSystemMetrics(SM_CXSCREEN);
						  //	MAX_vertical   = GetSystemMetrics(SM_CYSCREEN);

	GetDesktopResolution(temp_horizontal, temp_vertical);

	MAX_horizontal = temp_horizontal;
	MAX_vertical = temp_vertical;

	if (temp_horizontal < 1280)
	{
		MAX_horizontal = 1280;
		MAX_vertical = 720;
	}

	if (temp_vertical < 720)
	{
		MAX_horizontal = 1280;
		MAX_vertical = 720;
	}

	//if(DEMO_MODE == 0)                                               
	//{                                   
	// Error.log            
	//remove("Server_error.log");    
	//fp2 = fopen("Server_error.log", "w");     
	//}     

	time_diff = 0;

	sprite = new object[TOTAL_NO_SPRITES];
	hud = new object[TOTAL_NO_HUD];
	Fx = new object[TOTAL_NO_FX_SPRITES];

	memset(sprite, 0, sizeof(object)*TOTAL_NO_SPRITES);
	memset(hud, 0, sizeof(object)*TOTAL_NO_HUD);
	memset(Fx, 0, sizeof(object)*TOTAL_NO_FX_SPRITES);

	memset(a_texture, 0, sizeof(animation_texture)*MAX_FX_ID);

	fullscreen = true;

	STEAM_ACTIVE = true;

	LoadCFG();

	TimerInit();

	CreateDXWindow(NULL, sc_width, sc_height, sc_bits, fullscreen);              

	LoadCFG();

	emy1_snd = OpenSound(device, "Data/SFX/BG_ALLEYWAY.ogg", STREAM_MUSIC);
	emy2_snd = OpenSound(device, "Data/SFX/BG_TRAIN.ogg", STREAM_MUSIC);
	emy3_snd = OpenSound(device, "Data/SFX/BG_TRAFFIC.ogg", STREAM_MUSIC);
	emy4_snd = OpenSound(device, "Data/SFX/BG_PARK.ogg", STREAM_MUSIC);
	emy5_snd = OpenSound(device, "Data/SFX/BG_BIKESHOP.ogg", STREAM_MUSIC);
	emy6_snd = OpenSound(device, "Data/SFX/BG_NIGHTCLUB.ogg", STREAM_MUSIC);
	emy7_snd = OpenSound(device, "Data/SFX/BG_PRISON.ogg", STREAM_MUSIC);
	emy8_snd = OpenSound(device, "Data/SFX/BG_HIGHWAY.ogg", STREAM_MUSIC);
	emy9_snd = OpenSound(device, "Data/SFX/BG_COURT.ogg", STREAM_MUSIC);
	emy10_snd = OpenSound(device, "Data/SFX/BG_DOJO.ogg", STREAM_MUSIC);
	emy11_snd = OpenSound(device, "Data/SFX/BG_AIRPORT.ogg", STREAM_MUSIC);
	emy12_snd = OpenSound(device, "Data/SFX/BG_ROOFTOPS.ogg", STREAM_MUSIC);
	emy13_snd = OpenSound(device, "Data/SFX/BG_CAFE.ogg", STREAM_MUSIC);
	emy14_snd = OpenSound(device, "Data/SFX/BG_RING.ogg", STREAM_MUSIC);
	jet1_snd = OpenSound(device, "Data/SFX/VG_VS.ogg", STREAM_MUSIC);
	jet2_snd = OpenSound(device, "Data/SFX/VG_GAMEOVER.ogg", STREAM_MUSIC);
	jet3_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	jet4_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	siege1_snd = OpenSound(device, "Data/SFX/CS_DANGER1.ogg", STREAM_MUSIC);
	siege2_snd = OpenSound(device, "Data/SFX/CS_DANGER2.ogg", STREAM_MUSIC);
	siege3_snd = OpenSound(device, "Data/SFX/CS_VICTORY.ogg", STREAM_MUSIC);
	siege4_snd = OpenSound(device, "Data/SFX/CS_ENDING.ogg", STREAM_MUSIC);
	siege5_snd = OpenSound(device, "Data/SFX/CS_BOSSIDLE.ogg", STREAM_MUSIC);
	siege6_snd = OpenSound(device, "Data/SFX/CS_IDLE.ogg", STREAM_MUSIC);
	map_grass_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	map_swamp_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	map_forest_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	map_farm_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	map_snow_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	map_desert_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	map_trench_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	lnd_snd = OpenSound(device, "Data/SFX/CS_ENDING.ogg", STREAM_MUSIC);
	theatre_snd = OpenSound(device, "Data/SFX/CS_INTRO.ogg", STREAM_MUSIC);
	credits1_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	credits2_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	credits3_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	crd_snd = OpenSound(device, "Data/SFX/VG_SELECT.ogg", STREAM_MUSIC);
	army_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	fight_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	sad_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	intro_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	mini_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	deathscreen_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	urgency_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	fanfare_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	fanfare2_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	dgnb_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	final_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	dangers_snd = OpenSound(device, "Data/SFX/BLANK.ogg", STREAM_MUSIC);
	vg_amb_prison_snd = OpenSound(device, "Data/SFX/VG_AMB_PRISON.ogg", STREAM_MUSIC);
	vg_amb_traffic_snd = OpenSound(device, "Data/SFX/VG_AMB_TRAFFIC.ogg", STREAM_MUSIC);
	vg_amb_subway_snd = OpenSound(device, "Data/SFX/VG_AMB_SUBWAY.ogg", STREAM_MUSIC);
	vg_amb_van_snd = OpenSound(device, "Data/SFX/VG_VAN.ogg", STREAM_MUSIC);
	vg_amb_duel_snd = OpenSound(device, "Data/SFX/VG_AMB_DUEL.ogg", STREAM_MUSIC);
	vg_arrested_snd = OpenSoundEffect(device, "Data/SFX/VG_ARRESTED.wav", SINGLE);
	vg_wasted_snd = OpenSoundEffect(device, "Data/SFX/VG_WASTED.wav", SINGLE);
	vg_power1_snd = OpenSoundEffect(device, "Data/SFX/VG_POWER1.wav", SINGLE);
	vg_power2_snd = OpenSoundEffect(device, "Data/SFX/VG_POWER2.wav", SINGLE);
	vg_power3_snd = OpenSoundEffect(device, "Data/SFX/VG_POWER3.wav", SINGLE);
	vg_power4_snd = OpenSoundEffect(device, "Data/SFX/VG_POWER4.wav", SINGLE);
	vg_ko_1_snd = OpenSoundEffect(device, "Data/SFX/VG_KO_GYEONG.wav", SINGLE);
	vg_ko_2_snd = OpenSoundEffect(device, "Data/SFX/VG_KO_SIU.wav", SINGLE);
	vg_ko_3_snd = OpenSoundEffect(device, "Data/SFX/VG_KO_MINSO.wav", SINGLE);
	vg_ko_4_snd = OpenSoundEffect(device, "Data/SFX/VG_KO_REESE.wav", SINGLE);
	vg_ko_5_snd = OpenSoundEffect(device, "Data/SFX/VG_KO_YOHAN.wav", SINGLE);
	vg_ko_6_snd = OpenSoundEffect(device, "Data/SFX/VG_KO_JAE.wav", SINGLE);
	vg_ko_7_snd = OpenSoundEffect(device, "Data/SFX/VG_KO_GUN.wav", SINGLE);
	vg_ko_8_snd = OpenSoundEffect(device, "Data/SFX/VG_KO_HYUK.wav", SINGLE);
	vg_ko_9_snd = OpenSoundEffect(device, "Data/SFX/VG_KO_SANG.wav", SINGLE);
	vg_ko_10_snd = OpenSoundEffect(device, "Data/SFX/VG_KO_TRAINER.wav", SINGLE);
	vg_ko_11_snd = OpenSoundEffect(device, "Data/SFX/VG_KO_SIU.wav", SINGLE);
	vg_ko_12_snd = OpenSoundEffect(device, "Data/SFX/VG_KO_MINSO.wav", SINGLE);
	vg_ko_13_snd = OpenSoundEffect(device, "Data/SFX/VG_KO_GYEONG.wav", SINGLE);
	vg_ko_14_snd = OpenSoundEffect(device, "Data/SFX/VG_KO_GUN.wav", SINGLE);
	vg_shout_snd = OpenSoundEffect(device, "Data/SFX/VG_SHOUT.wav", SINGLE);
	vg_siren_snd = OpenSoundEffect(device, "Data/SFX/VG_SIREN.wav", SINGLE);
	vg_title_move = OpenSoundEffect(device, "Data/SFX/TS_CHARMOVE.wav", SINGLE);
	vg_title_select = OpenSoundEffect(device, "Data/SFX/TS_CHARSELECT.wav", SINGLE);
	vg_perfect_snd = OpenSoundEffect(device, "Data/SFX/VG_perfect.wav", SINGLE);
	vg_amb_car1_snd = OpenSoundEffect(device, "Data/SFX/VG_AMB_CAR1.ogg", MULTIPLE);
	vg_amb_car2_snd = OpenSoundEffect(device, "Data/SFX/VG_AMB_CAR2.ogg", MULTIPLE);
	vg_ko_snd = OpenSoundEffect(device, "Data/SFX/VG_hit_KO1.wav", SINGLE);
	vg_ko1_snd = OpenSoundEffect(device, "Data/SFX/VG_hit_KO2.wav", SINGLE);
	vg_ko2_snd = OpenSoundEffect(device, "Data/SFX/VG_hit_KO3.wav", SINGLE);
	vg_ko3_snd = OpenSoundEffect(device, "Data/SFX/VG_hit_KO4.wav", SINGLE);
	vg_fight_snd = OpenSoundEffect(device, "Data/SFX/VG_FIGHT.wav", SINGLE);
	vg_blocked_snd = OpenSoundEffect(device, "Data/SFX/VG_BLOCKED.wav", SINGLE);
	vg_knockdown_snd = OpenSoundEffect(device, "Data/SFX/VG_KNOCKSLIDE.wav", SINGLE);
	vg_stamp_snd = OpenSoundEffect(device, "Data/SFX/VG_STAMP.wav", SINGLE);
	vg_round1_snd = OpenSoundEffect(device, "Data/SFX/VG_rnd1.wav", SINGLE);
	vg_round2_snd = OpenSoundEffect(device, "Data/SFX/VG_rnd2.wav", SINGLE);
	vg_round3_snd = OpenSoundEffect(device, "Data/SFX/VG_rnd3.wav", SINGLE);
	vg_round4_snd = OpenSoundEffect(device, "Data/SFX/VG_rnd4.wav", SINGLE);
	vg_round5_snd = OpenSoundEffect(device, "Data/SFX/VG_rnd5.wav", SINGLE);
	vg_round6_snd = OpenSoundEffect(device, "Data/SFX/VG_rnd6.wav", SINGLE);
	VG_title_snd = OpenSoundEffect(device, "Data/SFX/VG_TITLE.wav", SINGLE);
	VG_verdict_snd = OpenSoundEffect(device, "Data/SFX/VG_VERDICT.wav", SINGLE);
	VG_guilty_snd = OpenSoundEffect(device, "Data/SFX/VG_GUILTY.wav", SINGLE);
	VG_destiny_snd = OpenSoundEffect(device, "Data/SFX/VG_DESTINY.wav", SINGLE);
	VG_pow_snd = OpenSoundEffect(device, "Data/SFX/VG_POW.wav", SINGLE);
	VG_titlevoice_snd = OpenSoundEffect(device, "Data/SFX/VG_TITLEVOICE.wav", SINGLE);
	VG_alright_snd = OpenSoundEffect(device, "Data/SFX/VG_ALRIGHT.wav", SINGLE);
	VG_nice_snd = OpenSoundEffect(device, "Data/SFX/VG_NICE.wav", SINGLE);
	VG_okay_snd = OpenSoundEffect(device, "Data/SFX/VG_OKAY.wav", SINGLE);
	VG_good_snd = OpenSoundEffect(device, "Data/SFX/VG_GOOD.wav", SINGLE);
	VG_great_snd = OpenSoundEffect(device, "Data/SFX/VG_GREAT.wav", SINGLE);
	VG_excellent_snd = OpenSoundEffect(device, "Data/SFX/VG_EXCELLENT.wav", SINGLE);
	gyeong_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_GYEONG.wav", SINGLE);
	siu_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_SIU.wav", SINGLE);
	hyuk_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_HYUK.wav", SINGLE);
	gun_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_GUN.wav", SINGLE);
	jae_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_JAE.wav", SINGLE);
	minso_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_MINSO.wav", SINGLE);
	reese_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_REESE.wav", SINGLE);
	yohan_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_YOHAN.wav", SINGLE);
	sang_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_SANG.wav", SINGLE);
	trainer_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_TRAINER.wav", SINGLE);
	gyeong2_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_GYEONG.wav", SINGLE);
	siu2_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_SIU.wav", SINGLE);
	hyuk2_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_HYUK.wav", SINGLE);
	gun2_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_GUN.wav", SINGLE);
	jae2_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_JAE.wav", SINGLE);
	minso2_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_MINSO.wav", SINGLE);
	reese2_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_REESE.wav", SINGLE);
	yohan2_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_YOHAN.wav", SINGLE);
	sang2_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_SANG.wav", SINGLE);
	trainer2_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_TRAINER.wav", SINGLE);
	WIN_gyeong_snd = OpenSoundEffect(device, "Data/SFX/VG_WIN_GYEONG.wav", SINGLE);
	WIN_siu_snd = OpenSoundEffect(device, "Data/SFX/VG_WIN_SIU.wav", SINGLE);
	WIN_hyuk_snd = OpenSoundEffect(device, "Data/SFX/VG_WIN_HYUK.wav", SINGLE);
	WIN_gun_snd = OpenSoundEffect(device, "Data/SFX/VG_WIN_GUN.wav", SINGLE);
	WIN_jae_snd = OpenSoundEffect(device, "Data/SFX/VG_WIN_JAE.wav", SINGLE);
	WIN_minso_snd = OpenSoundEffect(device, "Data/SFX/VG_WIN_MINSO.wav", SINGLE);
	WIN_reese_snd = OpenSoundEffect(device, "Data/SFX/VG_WIN_REESE.wav", SINGLE);
	WIN_yohan_snd = OpenSoundEffect(device, "Data/SFX/VG_WIN_YOHAN.wav", SINGLE);
	WIN_sang_snd = OpenSoundEffect(device, "Data/SFX/VG_WIN_SANG.wav", SINGLE);
	WIN_trainer_snd = OpenSoundEffect(device, "Data/SFX/VG_WIN_TRAINER.wav", SINGLE);
	YELL_gyeong_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_GYEONG.wav", SINGLE);
	YELL_siu_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_SIU.wav", SINGLE);
	YELL_hyuk_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_HYUK.wav", SINGLE);
	YELL_gun_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_GUN.wav", SINGLE);
	YELL_jae_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_JAE.wav", SINGLE);
	YELL_minso_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_MINSO.wav", SINGLE);
	YELL_reese_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_REESE.wav", SINGLE);
	YELL_yohan_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_YOHAN.wav", SINGLE);
	YELL_sang_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_SANG.wav", SINGLE);
	YELL_trainer_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_TRAINER.wav", SINGLE);
	YELL_judge_snd = OpenSoundEffect(device, "Data/SFX/VG_YELL_JUDGE.wav", SINGLE);
	vg_gameover_snd = OpenSoundEffect(device, "Data/SFX/VG_GAME_OVER.wav", SINGLE);
	vg_titleselect_snd = OpenSoundEffect(device, "Data/SFX/TS_TITLESELECT.wav", SINGLE);
	vg_titlemove_snd = OpenSoundEffect(device, "Data/SFX/TS_TITLEMOVE.wav", SINGLE);
	vg_break_snd = OpenSoundEffect(device, "Data/SFX/VG_BREAK.wav", MULTIPLE);
	vg_knife_snd = OpenSoundEffect(device, "Data/SFX/VG_KNIFE.wav", MULTIPLE);
	vg_vacuum_snd = OpenSoundEffect(device, "Data/SFX/VG_VACUUM.wav", MULTIPLE);
	vg_orb_snd = OpenSoundEffect(device, "Data/SFX/VG_VACUUM.wav", MULTIPLE);
	vg_orb2_snd = OpenSoundEffect(device, "Data/SFX/VG_VACUUM.wav", MULTIPLE);
	vg_pistol1_snd = OpenSoundEffect(device, "Data/SFX/VG_PISTOL.wav", SINGLE);
	vg_pistol2_snd = OpenSoundEffect(device, "Data/SFX/VG_PISTOL.wav", SINGLE);
	vg_shotgun1_snd = OpenSoundEffect(device, "Data/SFX/VG_SHOTGUN.wav", SINGLE);
	vg_shotgun2_snd = OpenSoundEffect(device, "Data/SFX/VG_SHOTGUN.wav", SINGLE);
	vg_ric1_snd = OpenSoundEffect(device, "Data/SFX/VG_RIC1.wav", SINGLE);
	vg_ric2_snd = OpenSoundEffect(device, "Data/SFX/VG_RIC2.wav", SINGLE);
	vg_ric3_snd = OpenSoundEffect(device, "Data/SFX/VG_RIC3.wav", SINGLE);
	vg_shock_snd = OpenSoundEffect(device, "Data/SFX/VG_SHOCK.wav", SINGLE);
	vg_reload_snd = OpenSoundEffect(device, "Data/SFX/VG_RELOAD.wav", SINGLE);
	vg_reloaded_snd = OpenSoundEffect(device, "Data/SFX/VG_RELOADED.wav", SINGLE);
	vg_mgun_snd = OpenSoundEffect(device, "Data/SFX/VG_MGUN.wav", MULTIPLE);
	vg_glass1_snd = OpenSoundEffect(device, "Data/SFX/VG_GLASS1.wav", MULTIPLE);
	vg_glass2_snd = OpenSoundEffect(device, "Data/SFX/VG_GLASS2.wav", MULTIPLE);
	vg_glass3_snd = OpenSoundEffect(device, "Data/SFX/VG_GLASS3.wav", MULTIPLE);
	vg_glass4_snd = OpenSoundEffect(device, "Data/SFX/VG_GLASS4.wav", MULTIPLE);
	vg_dogattack_snd = OpenSoundEffect(device, "Data/SFX/VG_DOGATTACK.wav", MULTIPLE);
	vg_verdict_snd = OpenSoundEffect(device, "Data/SFX/VG_VERDICT.wav", SINGLE);
	vg_knockslide_snd = OpenSoundEffect(device, "Data/SFX/VG_knockslide_fx.wav", SINGLE);
	VG_land_snd = OpenSoundEffect(device, "Data/SFX/VG_land_fx.wav", MULTIPLE);
	vg_tink_snd = OpenSoundEffect(device, "Data/SFX/VG_TINK.wav", MULTIPLE);
	vg_chop_snd = OpenSoundEffect(device, "Data/SFX/VG_whoosh1.wav", MULTIPLE);
	vg_chop1_snd = OpenSoundEffect(device, "Data/SFX/VG_whoosh2.wav", MULTIPLE);
	vg_chop2_snd = OpenSoundEffect(device, "Data/SFX/VG_whoosh3.wav", MULTIPLE);
	vg_chop3_snd = OpenSoundEffect(device, "Data/SFX/VG_whoosh4.wav", MULTIPLE);
	vg_splat_snd = OpenSoundEffect(device, "Data/SFX/VG_SPLAT.wav", MULTIPLE);
	vg_explode_snd = OpenSoundEffect(device, "Data/SFX/VG_EXPLODE.wav", MULTIPLE);
	vg_hitsound_snd = OpenSoundEffect(device, "Data/SFX/VG_hit_soft1.wav", SINGLE);
	vg_hitsound1_snd = OpenSoundEffect(device, "Data/SFX/VG_hit_soft2.wav", SINGLE);
	vg_hitsound2_snd = OpenSoundEffect(device, "Data/SFX/VG_hit_soft3.wav", SINGLE);
	vg_hitsound3_snd = OpenSoundEffect(device, "Data/SFX/VG_hit_soft4.wav", SINGLE);
	vg_hitsound4_snd = OpenSoundEffect(device, "Data/SFX/VG_hit_hard1.wav", SINGLE);
	vg_hitsound5_snd = OpenSoundEffect(device, "Data/SFX/VG_hit_hard2.wav", SINGLE);
	vg_hitsound6_snd = OpenSoundEffect(device, "Data/SFX/VG_hit_hard3.wav", SINGLE);
	vg_hitsound7_snd = OpenSoundEffect(device, "Data/SFX/VG_hit_hard4.wav", SINGLE);
	vg_win_snd = OpenSoundEffect(device, "Data/SFX/VG_WIN.wav", SINGLE);
	vg_lose_snd = OpenSoundEffect(device, "Data/SFX/VG_LOSE.wav", SINGLE);

	vg_perfect_snd->setVolume(sfx_volume);
	vg_amb_car1_snd->setVolume(sfx_volume);
	vg_amb_car2_snd->setVolume(sfx_volume);

	vg_ko_snd->setVolume(sfx_volume);
	vg_ko1_snd->setVolume(sfx_volume);
	vg_ko2_snd->setVolume(sfx_volume);
	vg_ko3_snd->setVolume(sfx_volume);


	vg_amb_subway_snd->setVolume(sfx_volume);
	vg_fight_snd->setVolume(sfx_volume);

	VG_title_snd->setVolume(sfx_volume);

	gyeong_snd->setVolume(sfx_volume);
	siu_snd->setVolume(sfx_volume);
	minso_snd->setVolume(sfx_volume);
	reese_snd->setVolume(sfx_volume);
	yohan_snd->setVolume(sfx_volume);
	jae_snd->setVolume(sfx_volume);
	gun_snd->setVolume(sfx_volume);
	hyuk_snd->setVolume(sfx_volume);
	sang_snd->setVolume(sfx_volume);
	trainer_snd->setVolume(sfx_volume);

	gyeong2_snd->setVolume(sfx_volume);
	siu2_snd->setVolume(sfx_volume);
	minso2_snd->setVolume(sfx_volume);
	reese2_snd->setVolume(sfx_volume);
	yohan2_snd->setVolume(sfx_volume);
	jae2_snd->setVolume(sfx_volume);
	gun2_snd->setVolume(sfx_volume);
	hyuk2_snd->setVolume(sfx_volume);
	sang2_snd->setVolume(sfx_volume);
	trainer2_snd->setVolume(sfx_volume);

	WIN_gyeong_snd->setVolume(sfx_volume);
	WIN_siu_snd->setVolume(sfx_volume);
	WIN_minso_snd->setVolume(sfx_volume);
	WIN_reese_snd->setVolume(sfx_volume);
	WIN_yohan_snd->setVolume(sfx_volume);
	WIN_jae_snd->setVolume(sfx_volume);
	WIN_gun_snd->setVolume(sfx_volume);
	WIN_hyuk_snd->setVolume(sfx_volume);
	WIN_sang_snd->setVolume(sfx_volume);
	WIN_trainer_snd->setVolume(sfx_volume);

	YELL_gyeong_snd->setVolume(sfx_volume);
	YELL_siu_snd->setVolume(sfx_volume);
	YELL_minso_snd->setVolume(sfx_volume);
	YELL_reese_snd->setVolume(sfx_volume);
	YELL_yohan_snd->setVolume(sfx_volume);
	YELL_jae_snd->setVolume(sfx_volume);
	YELL_gun_snd->setVolume(sfx_volume);
	YELL_hyuk_snd->setVolume(sfx_volume);
	YELL_sang_snd->setVolume(sfx_volume);
	YELL_trainer_snd->setVolume(sfx_volume);

	YELL_judge_snd->setVolume(sfx_volume);

	vg_blocked_snd->setVolume(sfx_volume);

	vg_knockdown_snd->setVolume(sfx_volume);

	vg_stamp_snd->setVolume(sfx_volume);

	vg_titlemove_snd->setVolume(sfx_volume);



	vg_arrested_snd->setVolume(sfx_volume);
	vg_wasted_snd->setVolume(sfx_volume);

	vg_power1_snd->setVolume(sfx_volume);
	vg_power2_snd->setVolume(sfx_volume);
	vg_power3_snd->setVolume(sfx_volume);
	vg_power4_snd->setVolume(sfx_volume);

	vg_ko_1_snd->setVolume(sfx_volume);
	vg_ko_2_snd->setVolume(sfx_volume);
	vg_ko_3_snd->setVolume(sfx_volume);
	vg_ko_4_snd->setVolume(sfx_volume);
	vg_ko_5_snd->setVolume(sfx_volume);
	vg_ko_6_snd->setVolume(sfx_volume);
	vg_ko_7_snd->setVolume(sfx_volume);
	vg_ko_8_snd->setVolume(sfx_volume);
	vg_ko_9_snd->setVolume(sfx_volume);
	vg_ko_10_snd->setVolume(sfx_volume);
	vg_ko_11_snd->setVolume(sfx_volume);
	vg_ko_12_snd->setVolume(sfx_volume);
	vg_ko_13_snd->setVolume(sfx_volume);
	vg_ko_14_snd->setVolume(sfx_volume);

	vg_shout_snd->setVolume(sfx_volume);
	vg_siren_snd->setVolume(sfx_volume);

	vg_title_move->setVolume(sfx_volume);
	vg_title_select->setVolume(sfx_volume);

	vg_round1_snd->setVolume(sfx_volume);
	vg_round2_snd->setVolume(sfx_volume);
	vg_round3_snd->setVolume(sfx_volume);
	vg_round4_snd->setVolume(sfx_volume);
	vg_round5_snd->setVolume(sfx_volume);
	vg_round6_snd->setVolume(sfx_volume);

	vg_gameover_snd->setVolume(sfx_volume);


	vg_titleselect_snd->setVolume(sfx_volume);


	vg_knife_snd->setVolume(sfx_volume);
	vg_break_snd->setVolume(sfx_volume);

	vg_vacuum_snd->setVolume(sfx_volume);

	vg_orb_snd->setVolume(sfx_volume);
	vg_orb2_snd->setVolume(sfx_volume);

	vg_pistol1_snd->setVolume(sfx_volume);
	vg_pistol2_snd->setVolume(sfx_volume);


	vg_ric1_snd->setVolume(sfx_volume);
	vg_ric2_snd->setVolume(sfx_volume);
	vg_ric3_snd->setVolume(sfx_volume);


	vg_shock_snd->setVolume(sfx_volume);


	vg_reload_snd->setVolume(sfx_volume);
	vg_reloaded_snd->setVolume(sfx_volume);


	vg_mgun_snd->setVolume(sfx_volume);


	vg_glass1_snd->setVolume(sfx_volume);
	vg_glass2_snd->setVolume(sfx_volume);
	vg_glass3_snd->setVolume(sfx_volume);
	vg_glass4_snd->setVolume(sfx_volume);

	vg_dogattack_snd->setVolume(sfx_volume);


	VG_land_snd->setVolume(sfx_volume);


	vg_shotgun1_snd->setVolume(sfx_volume);
	vg_shotgun2_snd->setVolume(sfx_volume);

	vg_tink_snd->setVolume(sfx_volume);

	vg_chop_snd->setVolume(sfx_volume);
	vg_chop1_snd->setVolume(sfx_volume);
	vg_chop2_snd->setVolume(sfx_volume);
	vg_chop3_snd->setVolume(sfx_volume);

	vg_hitsound_snd->setVolume(sfx_volume);
	vg_hitsound1_snd->setVolume(sfx_volume);
	vg_hitsound2_snd->setVolume(sfx_volume);
	vg_hitsound3_snd->setVolume(sfx_volume);
	vg_hitsound4_snd->setVolume(sfx_volume);
	vg_hitsound5_snd->setVolume(sfx_volume);
	vg_hitsound6_snd->setVolume(sfx_volume);
	vg_hitsound7_snd->setVolume(sfx_volume);

	vg_splat_snd->setVolume(sfx_volume);

	vg_explode_snd->setVolume(sfx_volume);

	vg_win_snd->setVolume(sfx_volume);

	vg_lose_snd->setVolume(sfx_volume);

	vg_verdict_snd->setVolume(sfx_volume);
	vg_knockslide_snd->setVolume(sfx_volume);

	emy1_snd->setVolume(music_volume);
	emy1_snd->setRepeat(true);
	emy2_snd->setVolume(music_volume);
	emy2_snd->setRepeat(true);
	emy3_snd->setVolume(music_volume);
	emy3_snd->setRepeat(true);
	emy4_snd->setVolume(music_volume);
	emy4_snd->setRepeat(true);
	emy5_snd->setVolume(music_volume);
	emy5_snd->setRepeat(true);
	emy6_snd->setVolume(music_volume);
	emy6_snd->setRepeat(true);
	emy7_snd->setVolume(music_volume);
	emy7_snd->setRepeat(true);
	emy8_snd->setVolume(music_volume);
	emy8_snd->setRepeat(true);
	emy9_snd->setVolume(music_volume);
	emy9_snd->setRepeat(true);
	emy10_snd->setVolume(music_volume);
	emy10_snd->setRepeat(true);
	emy11_snd->setVolume(music_volume);
	emy11_snd->setRepeat(true);
	emy12_snd->setVolume(music_volume);
	emy12_snd->setRepeat(true);
	emy13_snd->setVolume(music_volume);
	emy13_snd->setRepeat(true);
	emy14_snd->setVolume(music_volume);
	emy14_snd->setRepeat(true);


	jet1_snd->setVolume(music_volume);
	jet1_snd->setRepeat(true);
	jet2_snd->setVolume(music_volume);
	jet2_snd->setRepeat(true);
	jet3_snd->setVolume(music_volume);
	jet3_snd->setRepeat(true);
	jet4_snd->setVolume(music_volume);
	jet4_snd->setRepeat(true);

	siege1_snd->setVolume(music_volume);
	siege1_snd->setRepeat(true);
	siege2_snd->setVolume(music_volume);
	siege2_snd->setRepeat(true);
	siege3_snd->setVolume(music_volume);
	siege3_snd->setRepeat(true);
	siege4_snd->setVolume(music_volume);
	siege4_snd->setRepeat(false);
	siege5_snd->setVolume(music_volume);
	siege5_snd->setRepeat(true);
	siege6_snd->setVolume(music_volume);
	siege6_snd->setRepeat(true);

	theatre_snd->setVolume(music_volume);
	theatre_snd->setRepeat(false);

	credits1_snd->setVolume(music_volume);
	credits1_snd->setRepeat(false);
	credits2_snd->setVolume(music_volume);
	credits2_snd->setRepeat(false);
	credits3_snd->setVolume(music_volume);
	credits3_snd->setRepeat(false);

	map_grass_snd->setVolume(music_volume);
	map_grass_snd->setRepeat(true);
	map_swamp_snd->setVolume(music_volume);
	map_swamp_snd->setRepeat(true);
	map_forest_snd->setVolume(music_volume);
	map_forest_snd->setRepeat(true);
	map_farm_snd->setVolume(music_volume);
	map_farm_snd->setRepeat(true);
	map_snow_snd->setVolume(music_volume);
	map_snow_snd->setRepeat(true);
	map_desert_snd->setVolume(music_volume);
	map_desert_snd->setRepeat(true);
	map_trench_snd->setVolume(music_volume);
	map_trench_snd->setRepeat(true);

	lnd_snd->setVolume(music_volume);
	lnd_snd->setRepeat(false);

	crd_snd->setVolume(music_volume);
	crd_snd->setRepeat(true);

	army_snd->setVolume(music_volume);
	army_snd->setRepeat(true);

	fight_snd->setVolume(music_volume);
	fight_snd->setRepeat(true);

	sad_snd->setVolume(music_volume);
	sad_snd->setRepeat(true);

	intro_snd->setVolume(music_volume);
	intro_snd->setRepeat(true);

	mini_snd->setVolume(music_volume);
	mini_snd->setRepeat(true);

	deathscreen_snd->setVolume(music_volume);
	deathscreen_snd->setRepeat(true);

	urgency_snd->setVolume(music_volume);
	urgency_snd->setRepeat(true);

	fanfare_snd->setVolume(music_volume);
	fanfare_snd->setRepeat(false);

	fanfare2_snd->setVolume(music_volume);
	fanfare2_snd->setRepeat(false);

	dgnb_snd->setVolume(music_volume);
	dgnb_snd->setRepeat(true);

	final_snd->setVolume(music_volume);
	final_snd->setRepeat(true);

	dangers_snd->setVolume(music_volume);
	dangers_snd->setRepeat(true);

	vg_amb_prison_snd->setVolume(sfx_volume);
	vg_amb_prison_snd->setRepeat(true);

	vg_amb_traffic_snd->setVolume(sfx_volume);
	vg_amb_traffic_snd->setRepeat(true);

	vg_amb_van_snd->setVolume(sfx_volume);
	vg_amb_van_snd->setRepeat(true);

	vg_amb_duel_snd->setVolume(sfx_volume);
	vg_amb_duel_snd->setRepeat(true);

		scene = 0;

	AI_Time = (int)TimerGetTime();
	Swap_Time = (int)TimerGetTime();
	Net_Time = (int)TimerGetTime();
	Net_Read_Time = (int)TimerGetTime();
	Code_Time = (int)TimerGetTime();
	Key_Time = (int)TimerGetTime();
	Main_Time = (int)TimerGetTime();
	FrameTime = (int)TimerGetTime();
	FrameTimer = (int)TimerGetTime() + 1000;
	Real_Time = (int)TimerGetTime() + 100;

	//VG_Get_Keys();

	srand((int)TimerGetTime());

	VG_P1_USING = VG_KEYBOARD;
	VG_P2_USING = VG_KEYBOARD;

#if INCLDUE_360_CONTROLLER == 1                        

	if (Check_Controller() == true)
		VG_P1_USING = VG_CONTROLLER;
	else
		VG_P1_USING = VG_KEYBOARD;

	if (Check_Controller() == true)
		VG_P2_USING = VG_CONTROLLER;
	else
		VG_P2_USING = VG_KEYBOARD;

#endif
}

void GameUpdate()
{
	
		if (1) // If There Are No Messages                
		{

			Total_cycle = (int)TimerGetTime() - Total_Start;
			Total_Start = (int)TimerGetTime();

			frame_rate++;

			// RealTime      
			if ((int)TimerGetTime() > Real_Time)
			{

				time_diff = (int)TimerGetTime() - Real_Time;

				time_diff /= 100;

				if (hours >= 24)
				{
					hours = 0;
				}

				Real_Time = (int)TimerGetTime() + 100;


			}

			if ((int)TimerGetTime() > FrameTimer)
			{


				FrameTimer = (int)TimerGetTime() + 100;

				frame_rate = 0;

			}

			if (game_paused == false)
				if ((int)TimerGetTime() > Steam_Time)
				{                         

					Steam_Time = (int)TimerGetTime() + STEAM_RATE;  // 400  

				}

			if (game_paused == false)
				if ((int)TimerGetTime() > Animate_Time)
				{
					Animate(-1, -1);

					Animate_Time = (int)TimerGetTime() + ANIMATE_RATE;  //8  

				}

			

			//    if(fade != 0.0f)                          
			if (double_main_code == 1)
				if ((int)TimerGetTime() > Swap_Time)
				{

					Swap_cycle = (int)TimerGetTime();

					//if(RENDERER == RENDER_OPENGL)
					//SwapBuffers(hDC); 					// Swap Buffers (Double Buffering)

					Swap_cycle = (int)TimerGetTime() - Swap_cycle;

					Swap_Time = (int)TimerGetTime() + SWAP_RATE;  //8  

					double_main_code = 0;

					//	  VG_FLICKER ^= 1;

				}

			/*if(FRAME_RATE_DELAY == 1)
			Sleep(10);  // For testing purposes...
			if(FRAME_RATE_DELAY == 2)
			Sleep(50);  // For testing purposes...*/

			if ((int)TimerGetTime() > Key_Time)
			{

				//		  if(CONTROLLER_ENABLED == false)  
				//			  CONTROLLER=false;  

#if INCLDUE_360_CONTROLLER == 1 
				if (!mode)
				{
					Run_Joypad();

				}
				else
					CONTROLLER = false;

#endif       

				if (!(episode == 0 && scene == 15))
					if (!mode)
					{
						VG_Key_Handler(keys, sprite, (int)TimerGetTime() - Key_Start);
					}
					else
						Key_Handler(keys, sprite, (int)TimerGetTime() - Key_Start);

				if (game_paused == false)
					Run_Fx((int)TimerGetTime() - Key_Start);

				Key_Start = (int)TimerGetTime();
				Key_Time = (int)TimerGetTime() + KEY_RATE; //8  


			}


			if (mouseleft == true)
			{

				if (mouse_held_state == 0)
				{
					mouse_held_state = 1;
					mouseheld_timer = (int)TimerGetTime() + 600;
				}

				if ((int)TimerGetTime() > mouseheld_timer && mouse_held_state == 1)
				{
					mouseheld = true;
				}

			}
			else
			{
				mouseheld = false;

				mouse_held_state = 0;
			}

			UpdateMouseCursor();

			// *****************************//
			//      Paused game code...     //
			// *****************************//

			if (vg_pause_sfx == true)
			{
				vg_pause_sfx = false;
				vg_title_select->setVolume(sfx_volume);
				vg_title_select->play();
			}

			VG_Pause();

			if (pause_music == true)
			{

				if (game_paused == true)
				{

					emy1_snd->setVolume(0.0f);
					emy2_snd->setVolume(0.0f);
					emy3_snd->setVolume(0.0f);
					emy4_snd->setVolume(0.0f);
					emy5_snd->setVolume(0.0f);
					emy6_snd->setVolume(0.0f);
					emy7_snd->setVolume(0.0f);
					emy8_snd->setVolume(0.0f);
					emy9_snd->setVolume(0.0f);
					emy10_snd->setVolume(0.0f);
					emy11_snd->setVolume(0.0f);
					emy12_snd->setVolume(0.0f);
					emy13_snd->setVolume(0.0f);
					emy14_snd->setVolume(0.0f);

					jet1_snd->setVolume(0.0f);
					jet2_snd->setVolume(0.0f);
					jet3_snd->setVolume(0.0f);
					jet4_snd->setVolume(0.0f);

					siege1_snd->setVolume(0.0f);
					siege2_snd->setVolume(0.0f);
					siege3_snd->setVolume(0.0f);
					siege4_snd->setVolume(0.0f);
					siege5_snd->setVolume(0.0f);
					siege6_snd->setVolume(0.0f);

					theatre_snd->setVolume(0.0f);
					credits1_snd->setVolume(0.0f);
					credits2_snd->setVolume(0.0f);
					credits3_snd->setVolume(0.0f);

					map_grass_snd->setVolume(0.0f);
					map_swamp_snd->setVolume(0.0f);
					map_forest_snd->setVolume(0.0f);
					map_farm_snd->setVolume(0.0f);
					map_snow_snd->setVolume(0.0f);
					map_desert_snd->setVolume(0.0f);
					map_trench_snd->setVolume(0.0f);

					lnd_snd->setVolume(0.0f);
					crd_snd->setVolume(0.0f);
					army_snd->setVolume(0.0f);
					fight_snd->setVolume(0.0f);
					sad_snd->setVolume(0.0f);
					intro_snd->setVolume(0.0f);
					mini_snd->setVolume(0.0f);
					deathscreen_snd->setVolume(0.0f);
					urgency_snd->setVolume(0.0f);
					fanfare_snd->setVolume(0.0f);
					fanfare2_snd->setVolume(0.0f);
					dgnb_snd->setVolume(0.0f);
					final_snd->setVolume(0.0f);
					dangers_snd->setVolume(0.0f);

					vg_amb_prison_snd->setVolume(0.0f);
					vg_amb_traffic_snd->setVolume(0.0f);
					vg_amb_van_snd->setVolume(0.0f);
					vg_amb_duel_snd->setVolume(0.0f);

				}
				else
				{

					emy1_snd->setVolume(music_volume);
					emy2_snd->setVolume(music_volume);
					emy3_snd->setVolume(music_volume);
					emy4_snd->setVolume(music_volume);
					emy5_snd->setVolume(music_volume);
					emy6_snd->setVolume(music_volume);
					emy7_snd->setVolume(music_volume);
					emy8_snd->setVolume(music_volume);
					emy9_snd->setVolume(music_volume);
					emy10_snd->setVolume(music_volume);
					emy11_snd->setVolume(music_volume);
					emy12_snd->setVolume(music_volume);
					emy13_snd->setVolume(music_volume);
					emy14_snd->setVolume(music_volume);

					jet1_snd->setVolume(music_volume);
					jet2_snd->setVolume(music_volume);
					jet3_snd->setVolume(music_volume);
					jet4_snd->setVolume(music_volume);

					siege1_snd->setVolume(music_volume);
					siege2_snd->setVolume(music_volume);
					siege3_snd->setVolume(music_volume);
					siege4_snd->setVolume(music_volume);
					siege5_snd->setVolume(music_volume);
					siege6_snd->setVolume(music_volume);

					theatre_snd->setVolume(music_volume);
					credits1_snd->setVolume(music_volume);
					credits2_snd->setVolume(music_volume);
					credits3_snd->setVolume(music_volume);

					map_grass_snd->setVolume(music_volume);
					map_swamp_snd->setVolume(music_volume);
					map_forest_snd->setVolume(music_volume);
					map_farm_snd->setVolume(music_volume);
					map_snow_snd->setVolume(music_volume);
					map_desert_snd->setVolume(music_volume);
					map_trench_snd->setVolume(music_volume);

					lnd_snd->setVolume(music_volume);
					crd_snd->setVolume(music_volume);
					army_snd->setVolume(music_volume);
					fight_snd->setVolume(music_volume);
					sad_snd->setVolume(music_volume);
					intro_snd->setVolume(music_volume);
					mini_snd->setVolume(music_volume);
					deathscreen_snd->setVolume(music_volume);
					urgency_snd->setVolume(music_volume);
					fanfare_snd->setVolume(music_volume);
					fanfare2_snd->setVolume(music_volume);
					dgnb_snd->setVolume(music_volume);
					final_snd->setVolume(music_volume);
					dangers_snd->setVolume(music_volume);

					vg_amb_prison_snd->setVolume(sfx_volume);
					vg_amb_traffic_snd->setVolume(sfx_volume);
					vg_amb_van_snd->setVolume(sfx_volume);
					vg_amb_duel_snd->setVolume(sfx_volume);

				}

				pause_music = false;
			}

			// Main Code                             

			Main_cycle = (int)TimerGetTime();

			if (!mode)
			{

				Set_Screen_Ratio();

				if (!mode)
					zoom_factor = (org_zoom_factor - 0.6f) + org_zoom_scroll_amount; // 1.3 - 0.6 = 0.7 for 16:9
				else
					zoom_factor = org_zoom_factor + org_zoom_scroll_amount;

			}

			srand((int)TimerGetTime());

			//Sleep(20);        

			//       if(double_main_code == 0)                
			if ((int)TimerGetTime() > Main_Time)
				if (game_paused == false)
				{

					f_rate1 = (int)TimerGetTime() - Main_Start;

					if (f_rate1 <= 0)
						f_rate1 = 1;

					if (f_rate1 > 100)
						f_rate1 = 100;

					if (!mode)
					{
						if (episode == 0 || episode == 1)
							Run_Frontend((int)TimerGetTime() - Main_Start);

						Run_Verdict((int)TimerGetTime() - Main_Start);
						Run_Story((int)TimerGetTime() - Main_Start);
					}

					if (episode == 1)
						if ((int)TimerGetTime() > VG_insert_flash_timer)
						{

							sprintf(new_counter[299].word, "INSERT COIN");

							if (VG_insert_flash == false)
							{
								new_counter[299].alpha = 1.0f;
								VG_insert_flash = true;
							}
							else
							{
								new_counter[299].alpha = 0.0f;
								VG_insert_flash = false;
							}

							VG_insert_flash_timer = (int)TimerGetTime() + 500;

							new_counter[299].type = 1;  // Small Font...
							new_counter[299].right = false;

							new_counter[299].id = 3;

							new_counter[299].x = -0.08f;
							new_counter[299].y = VG_BOTTOM_OPTIONS_OFFSET;

							new_counter[299].w = new_counter[299].x - 0.026f;
							new_counter[299].z = new_counter[299].y - 0.015f;

							new_counter[299].box_width = strlen(new_counter[299].word)   *  0.026f;
							new_counter[299].box_height = new_counter[299].height - 0.015f;

						}

					Main_Start = (int)TimerGetTime();
					Main_Time = (int)TimerGetTime() + MAIN_RATE;

					if ((int)TimerGetTime() > quit_timer && quitting == true)
					{

						done = true;

						quitting = false;

					}


					// ******************************************************************************//
					//                              Animation System                                 //                     
					// ******************************************************************************//

					// Game Logic   
					if (c_fade_in != 0 && next_scene == false)
						if (fade < 1.0)
						{
							fade += 1.0f - cos(cos_fade);

							if (fade > 1.0f)
								fade = 1.0f;

							cos_fade += ((((float)c_fade_in / 50000) * (float)f_rate1));

							if (cos_fade > 1.5f)
								cos_fade = 1.5f;
						}
						else
						{
							fade = 1.0f;
							cos_fade = 0.0f;
							c_fade_in = 0;
						}

					if (fade_in == 0 && next_scene == false)
						if ((int)TimerGetTime() < fade_timer)
						{
							fade = 0.0f;
						}
						else
						{
							if (fade == 0.0f)
								fade = 1.0f;
						}


					// ******************************************************************************//
					//                              Fade System                                      //                     
					// ******************************************************************************//

					// Load next scene if no fade out required
					if (next_scene == true)
					{

						if (c_fade_out == 0)
						{

							fade = 0.0f;

							if (vg_next_episode != -1)
							{
								episode = vg_next_episode;
								scene = vg_next_scene;

								vg_next_episode = -1;
								vg_next_scene = -1;
							}

							LoadScene(episode, scene, true);

							animating = true;

							next_scene = false;

						}
						else
						{
							if (fade > 0.0f)
							{

								fade -= 1.0f - cos(cos_fade);

								cos_fade += ((((float)c_fade_out / 50000) * (float)f_rate1));

								if (cos_fade > 1.5f)
									cos_fade = 1.5f;

								// Was 0.0f...
								if (fade < 0.0f)  // 0.001f
								{
									fade = 0.0f; // 0.001f
									c_fade_out = 0;
								}

							}
							else
							{
								fade = 0.0f;
								c_fade_out = 0;
							}
						}

					}

					// If paused don't execute                              
					if (quit_active == false)
					{


						// ******************************************************************************//
						//                                Debug-Selection                                //                     
						// ******************************************************************************//

						if (mode && mode != POINT_MODE && mode != NODES  && mode != TILE_MODE && next_scene == false)
						{
							if (mouseleft == true)
								for (int i = 0; i<original_no_sprites; i++)
								{
									var = var3[i];

									if (var >= 0 && var < TOTAL_NO_SPRITES)
										if ((mouseX < (sprite[var].x + sprite[var].width))
											&& (mouseX > sprite[var].x)
											&& (mouseY < (sprite[var].y + sprite[var].height))
											&& (mouseY > sprite[var].y))
										{
											if (selection != var)
												fps = var;
										}
								}

							selection = fps;
							mouseleft = false;

						}

						// ******************************************************************************//
						//                                Text-Functions                                 //                     
						// ******************************************************************************//

						if (scroll_txt_active == true && (int)TimerGetTime() > scroll_txt_timer)
						{

							if (scroll_index < scroll_length)
							{
								scroll_index++;
								if (scroll_length > 1)
									vg_tink_sfx = true;

							}

							if (scroll_index >= scroll_length)
							{

								scroll_txt_active = false;

								text_timer = ((int)TimerGetTime() + 2000);

								if (g_type != G_STS)
									text_active = true;

							}

							scroll_txt_timer = ((int)TimerGetTime() + 40);

						}

						//   if(DEBUG_MODE == 1 )  
						if ((game_mode == WALK || game_mode == FRONT || game_mode == WORLD || game_mode == CINE))
						{

							//      if(DEBUG_MODE == 1 )                                   
							//      {                              

							if (!CONTROLLER)
								if (music_volume <= 0.05f)
									music_volume = 0.0f;

							if (CONTROLLER)
								if (music_volume <= 0.0f)
									music_volume = 0.0f;

							if (music_volume >= 1.0f)
								music_volume = 1.0f;

							if (music_volume != 0.0f)
							{

								/*	if(CHANGE_SONG_SPEED == 1)
								{

								if(VG_BACKGROUND == VG_GYEONG)
								{
								emy1_snd->stop();
								emy1f_snd->play();
								CHANGE_SONG_SPEED = 2;
								}

								}*/

								temp_music_volume = music_volume;
								temp_sfx_volume = sfx_volume;

								// Set the volume for the musicbox at base camp
								//       if(!mode)  
								if (music_fade == true)
									if ((int)TimerGetTime() > music_timer)
									{

										music_timer = (int)TimerGetTime() + 50;

										fade_increment = music_volume / 28.0f;

										if (fade_increment <= 0.0f)
											fade_increment = 0.0f;

										fade_out_volume -= fade_increment;
										fade_in_volume += fade_increment;

										if (fade_out_volume <= 0.0f)
										{
											fade_out_volume = 0.0f;
											fade_in_volume = music_volume;
											music_fade = false;
										}

										if (fade_out_volume > 1.0f)
											fade_out_volume = 1.0f;

										if (fade_in_volume < 0.0f)
											fade_in_volume = 0.0f;

										if (fade_in_volume > 1.0f)
											fade_in_volume = 1.0f;

										if (fade_in_volume >= music_volume)
										{
											fade_out_volume = 0.0f;
											fade_in_volume = music_volume;
											music_fade = false;
										}

										if (crd_sfx == FADE_IN)
										{
											crd_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												crd_sfx = LOOP;
										}
										if (crd_sfx == FADE_OUT)
										{

											crd_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												crd_sfx = NO_ANIM;

										}

										if (end_sfx == FADE_IN)
										{

											if (VG_BACKGROUND == VG_GYEONG)
												emy1_snd->setVolume(fade_in_volume);
											if (VG_BACKGROUND == VG_SIU)
												emy2_snd->setVolume(fade_in_volume);
											if (VG_BACKGROUND == VG_MINSO)
												emy3_snd->setVolume(fade_in_volume);
											if (VG_BACKGROUND == VG_REESE)
												emy4_snd->setVolume(fade_in_volume);
											if (VG_BACKGROUND == VG_YOHAN)
												emy5_snd->setVolume(fade_in_volume);
											if (VG_BACKGROUND == VG_JAE)
												emy6_snd->setVolume(fade_in_volume);
											if (VG_BACKGROUND == VG_GUN)
												emy7_snd->setVolume(fade_in_volume);
											if (VG_BACKGROUND == VG_HYUK)
												emy8_snd->setVolume(fade_in_volume);
											if (VG_BACKGROUND == VG_SANG)
												emy9_snd->setVolume(fade_in_volume);
											if (VG_BACKGROUND == VG_TRAINER)
												emy10_snd->setVolume(fade_in_volume);
											if (VG_BACKGROUND == VG_SHO)
												emy11_snd->setVolume(fade_in_volume);
											if (VG_BACKGROUND == VG_SAIZO)
												emy12_snd->setVolume(fade_in_volume);
											if (VG_BACKGROUND == VG_TIA)
												emy13_snd->setVolume(fade_in_volume);
											if (VG_BACKGROUND == VG_KENNEDY)
												emy14_snd->setVolume(fade_in_volume);

											if (fade_in_volume == music_volume)
												end_sfx = LOOP;
										}
										if (end_sfx == FADE_OUT)
										{
											if (VG_BACKGROUND == VG_GYEONG)
												emy1_snd->setVolume(fade_out_volume);
											if (VG_BACKGROUND == VG_SIU)
												emy2_snd->setVolume(fade_out_volume);
											if (VG_BACKGROUND == VG_MINSO)
												emy3_snd->setVolume(fade_out_volume);
											if (VG_BACKGROUND == VG_REESE)
												emy4_snd->setVolume(fade_out_volume);
											if (VG_BACKGROUND == VG_YOHAN)
												emy5_snd->setVolume(fade_out_volume);
											if (VG_BACKGROUND == VG_JAE)
												emy6_snd->setVolume(fade_out_volume);
											if (VG_BACKGROUND == VG_GUN)
												emy7_snd->setVolume(fade_out_volume);
											if (VG_BACKGROUND == VG_HYUK)
												emy8_snd->setVolume(fade_out_volume);
											if (VG_BACKGROUND == VG_SANG)
												emy9_snd->setVolume(fade_out_volume);
											if (VG_BACKGROUND == VG_TRAINER)
												emy10_snd->setVolume(fade_out_volume);
											if (VG_BACKGROUND == VG_SHO)
												emy11_snd->setVolume(fade_out_volume);
											if (VG_BACKGROUND == VG_SAIZO)
												emy12_snd->setVolume(fade_out_volume);
											if (VG_BACKGROUND == VG_TIA)
												emy13_snd->setVolume(fade_out_volume);
											if (VG_BACKGROUND == VG_KENNEDY)
												emy14_snd->setVolume(fade_out_volume);

											if (fade_out_volume == 0.0f)
												end_sfx = NO_ANIM;
										}

										if (war_sfx == FADE_IN)
										{

											if (fade_in_volume == music_volume)
												war_sfx = LOOP;
										}
										if (war_sfx == FADE_OUT)
										{

											if (fade_out_volume == 0.0f)
												war_sfx = NO_ANIM;
										}

										if (lnd_sfx == FADE_IN)
										{
											lnd_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												lnd_sfx = LOOP;
										}
										if (lnd_sfx == FADE_OUT)
										{
											lnd_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												lnd_sfx = NO_ANIM;
										}

										if (army_sfx == FADE_IN)
										{
											army_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												army_sfx = LOOP;
										}
										if (army_sfx == FADE_OUT)
										{
											army_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												army_sfx = NO_ANIM;
										}

										if (fight_sfx == FADE_IN)
										{
											fight_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												fight_sfx = LOOP;
										}
										if (fight_sfx == FADE_OUT)
										{
											fight_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												fight_sfx = NO_ANIM;
										}

										if (jet_sfx == FADE_IN)
										{

											if (VG_IS_VERSUS_SCREEN == true)
												jet1_snd->setVolume(fade_in_volume);
											if (VG_IS_VERSUS_SCREEN == false)
												jet2_snd->setVolume(fade_in_volume);

											if (fade_in_volume == music_volume)
												jet_sfx = LOOP;
										}
										if (jet_sfx == FADE_OUT)
										{

											if (VG_IS_VERSUS_SCREEN == true)
												jet1_snd->setVolume(fade_out_volume);
											if (VG_IS_VERSUS_SCREEN == false)
												jet2_snd->setVolume(fade_out_volume);

											if (fade_out_volume == 0.0f)
												jet_sfx = NO_ANIM;
										}

										if (siege_sfx == FADE_IN)
										{
											if (VG_CS_SONG == CS_DANGER1)
												siege1_snd->setVolume(fade_in_volume);
											if (VG_CS_SONG == CS_DANGER2)
												siege2_snd->setVolume(fade_in_volume);
											if (VG_CS_SONG == CS_VICTORY)
												siege3_snd->setVolume(fade_in_volume);
											if (VG_CS_SONG == CS_ENDING)
												siege4_snd->setVolume(fade_in_volume);
											if (VG_CS_SONG == CS_BOSSIDLE)
												siege5_snd->setVolume(fade_in_volume);
											if (VG_CS_SONG == CS_IDLE)
												siege6_snd->setVolume(fade_in_volume);

											if (fade_in_volume == music_volume)
												siege_sfx = LOOP;
										}
										if (siege_sfx == FADE_OUT)
										{
											if (VG_CS_SONG == CS_DANGER1)
												siege1_snd->setVolume(fade_out_volume);
											if (VG_CS_SONG == CS_DANGER2)
												siege2_snd->setVolume(fade_out_volume);
											if (VG_CS_SONG == CS_VICTORY)
												siege3_snd->setVolume(fade_out_volume);
											if (VG_CS_SONG == CS_ENDING)
												siege4_snd->setVolume(fade_out_volume);
											if (VG_CS_SONG == CS_BOSSIDLE)
												siege5_snd->setVolume(fade_out_volume);
											if (VG_CS_SONG == CS_IDLE)
												siege6_snd->setVolume(fade_out_volume);

											if (fade_out_volume < 0.0f)
												siege_sfx = NO_ANIM;
										}

										if (theatre_sfx == FADE_IN)
										{
											theatre_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												theatre_sfx = LOOP;
										}
										if (theatre_sfx == FADE_OUT)
										{
											theatre_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												theatre_sfx = NO_ANIM;
										}

										if (credits_sfx == FADE_IN)
										{

										}
										if (credits_sfx == FADE_OUT)
										{

											if (fade_out_volume == 0.0f)
												credits_sfx = NO_ANIM;
										}

										if (sad_sfx == FADE_IN)
										{
											sad_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												sad_sfx = LOOP;
										}
										if (sad_sfx == FADE_OUT)
										{
											sad_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												sad_sfx = NO_ANIM;
										}

										if (intro_sfx == FADE_IN)
										{
											intro_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												intro_sfx = LOOP;
										}
										if (intro_sfx == FADE_OUT)
										{
											intro_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												intro_sfx = NO_ANIM;
										}

										if (mini_sfx == FADE_IN)
										{
											mini_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												mini_sfx = LOOP;
										}
										if (mini_sfx == FADE_OUT)
										{
											mini_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												mini_sfx = NO_ANIM;
										}

										if (deathscreen_sfx == FADE_IN)
										{
											deathscreen_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												deathscreen_sfx = LOOP;
										}
										if (deathscreen_sfx == FADE_OUT)
										{
											deathscreen_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												deathscreen_sfx = NO_ANIM;
										}

										if (urgency_sfx == FADE_IN)
										{
											urgency_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												urgency_sfx = LOOP;
										}
										if (urgency_sfx == FADE_OUT)
										{
											urgency_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												urgency_sfx = NO_ANIM;
										}

										if (fanfare_sfx == FADE_IN)
										{
											fanfare_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												fanfare_sfx = LOOP;
										}
										if (fanfare_sfx == FADE_OUT)
										{
											fanfare_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												fanfare_sfx = NO_ANIM;
										}

										if (fanfare2_sfx == FADE_IN)
										{
											fanfare2_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												fanfare2_sfx = LOOP;
										}
										if (fanfare2_sfx == FADE_OUT)
										{
											fanfare2_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												fanfare2_sfx = NO_ANIM;
										}

										if (dgnb_sfx == FADE_IN)
										{
											dgnb_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												dgnb_sfx = LOOP;
										}
										if (dgnb_sfx == FADE_OUT)
										{
											dgnb_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												dgnb_sfx = NO_ANIM;
										}

										if (final_sfx == FADE_IN)
										{
											final_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												final_sfx = LOOP;
										}
										if (final_sfx == FADE_OUT)
										{
											final_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												final_sfx = NO_ANIM;
										}

										if (dangers_sfx == FADE_IN)
										{
											dangers_snd->setVolume(fade_in_volume);
											if (fade_in_volume == music_volume)
												dangers_sfx = LOOP;
										}
										if (dangers_sfx == FADE_OUT)
										{
											dangers_snd->setVolume(fade_out_volume);
											if (fade_out_volume == 0.0f)
												dangers_sfx = NO_ANIM;
										}

									}  // if(music_fade == true)       

								if (crd_sfx == NO_ANIM)
								{
									crd_snd->stop();
									crd_snd->reset();
									crd_sfx = WAIT;
								}
								if (crd_sfx == PLAY || crd_sfx == FADE_IN)
								{
									if (crd_snd->isPlaying() == false)
										crd_snd->play();

									if (crd_sfx == PLAY)
									{
										crd_sfx = LOOP;

										if (half_volume == false)
											crd_snd->setVolume(music_volume);
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											crd_snd->setVolume(music_volume / 2);
										}
									}
								}

								if (end_sfx == NO_ANIM)
								{
									emy1_snd->stop();
									emy1_snd->reset();
									emy2_snd->stop();
									emy2_snd->reset();
									emy3_snd->stop();
									emy3_snd->reset();
									emy4_snd->stop();
									emy4_snd->reset();
									emy5_snd->stop();
									emy5_snd->reset();
									emy6_snd->stop();
									emy6_snd->reset();
									emy7_snd->stop();
									emy7_snd->reset();
									emy8_snd->stop();
									emy8_snd->reset();
									emy9_snd->stop();
									emy9_snd->reset();
									emy10_snd->stop();
									emy10_snd->reset();
									emy11_snd->stop();
									emy11_snd->reset();
									emy12_snd->stop();
									emy12_snd->reset();
									emy13_snd->stop();
									emy13_snd->reset();
									emy14_snd->stop();
									emy14_snd->reset();

									end_sfx = WAIT;
								}
								if (end_sfx == PLAY || end_sfx == FADE_IN || end_sfx == ONCE)
								{
									if (VG_BACKGROUND == VG_GYEONG)
										if (emy1_snd->isPlaying() == false)
											emy1_snd->play();
									if (VG_BACKGROUND == VG_SIU)
										if (emy2_snd->isPlaying() == false)
											emy2_snd->play();
									if (VG_BACKGROUND == VG_MINSO)
										if (emy3_snd->isPlaying() == false)
											emy3_snd->play();
									if (VG_BACKGROUND == VG_REESE)
										if (emy4_snd->isPlaying() == false)
											emy4_snd->play();
									if (VG_BACKGROUND == VG_YOHAN)
										if (emy5_snd->isPlaying() == false)
											emy5_snd->play();
									if (VG_BACKGROUND == VG_JAE)
										if (emy6_snd->isPlaying() == false)
											emy6_snd->play();
									if (VG_BACKGROUND == VG_GUN)
										if (emy7_snd->isPlaying() == false)
											emy7_snd->play();
									if (VG_BACKGROUND == VG_HYUK)
										if (emy8_snd->isPlaying() == false)
											emy8_snd->play();
									if (VG_BACKGROUND == VG_SANG)
										if (emy9_snd->isPlaying() == false)
											emy9_snd->play();
									if (VG_BACKGROUND == VG_TRAINER)
										if (emy10_snd->isPlaying() == false)
											emy10_snd->play();
									if (VG_BACKGROUND == VG_SHO)
										if (emy11_snd->isPlaying() == false)
											emy11_snd->play();
									if (VG_BACKGROUND == VG_SAIZO)
										if (emy12_snd->isPlaying() == false)
											emy12_snd->play();
									if (VG_BACKGROUND == VG_TIA)
										if (emy13_snd->isPlaying() == false)
											emy13_snd->play();
									if (VG_BACKGROUND == VG_KENNEDY)
										if (emy14_snd->isPlaying() == false)
											emy14_snd->play();

									if (end_sfx == PLAY)
									{
										end_sfx = LOOP;

										if (half_volume == false)
										{
											emy1_snd->setVolume(music_volume);
											emy2_snd->setVolume(music_volume);
											emy3_snd->setVolume(music_volume);
											emy4_snd->setVolume(music_volume);
											emy5_snd->setVolume(music_volume);
											emy6_snd->setVolume(music_volume);
											emy7_snd->setVolume(music_volume);
											emy8_snd->setVolume(music_volume);
											emy9_snd->setVolume(music_volume);
											emy10_snd->setVolume(music_volume);
											emy11_snd->setVolume(music_volume);
											emy12_snd->setVolume(music_volume);
											emy13_snd->setVolume(music_volume);
											emy14_snd->setVolume(music_volume);
										}
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											emy1_snd->setVolume(music_volume / 2);
											emy2_snd->setVolume(music_volume / 2);
											emy3_snd->setVolume(music_volume / 2);
											emy4_snd->setVolume(music_volume / 2);
											emy5_snd->setVolume(music_volume / 2);
											emy6_snd->setVolume(music_volume / 2);
											emy7_snd->setVolume(music_volume / 2);
											emy8_snd->setVolume(music_volume / 2);
											emy9_snd->setVolume(music_volume / 2);
											emy10_snd->setVolume(music_volume / 2);
											emy11_snd->setVolume(music_volume / 2);
											emy12_snd->setVolume(music_volume / 2);
											emy13_snd->setVolume(music_volume / 2);
											emy14_snd->setVolume(music_volume / 2);
										}
									}

								}
								if (war_sfx == NO_ANIM)
								{


									war_sfx = WAIT;
								}
								if (war_sfx == PLAY || war_sfx == FADE_IN)
								{


									if (war_sfx == PLAY)
									{
										war_sfx = LOOP;

										if (half_volume == false)
										{

										}
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;


										}

									}
								}
								if (lnd_sfx == NO_ANIM)
								{
									lnd_snd->stop();
									lnd_snd->reset();
									lnd_sfx = WAIT;
								}
								if (lnd_sfx == PLAY || lnd_sfx == FADE_IN)
								{
									if (lnd_snd->isPlaying() == false)
										lnd_snd->play();

									if (lnd_sfx == PLAY)
									{
										lnd_sfx = LOOP;

										if (half_volume == false)
											lnd_snd->setVolume(music_volume);
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											lnd_snd->setVolume(music_volume / 2);
										}

									}
								}
								if (army_sfx == NO_ANIM)
								{
									army_snd->stop();
									army_snd->reset();
									army_sfx = WAIT;
								}
								if (army_sfx == PLAY || army_sfx == FADE_IN)
								{
									if (army_snd->isPlaying() == false)
										army_snd->play();

									if (army_sfx == PLAY)
									{
										army_sfx = LOOP;

										if (half_volume == false)
											army_snd->setVolume(music_volume);
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											army_snd->setVolume(music_volume / 2);
										}
									}
								}
								if (fight_sfx == NO_ANIM)
								{
									fight_snd->stop();
									//    fight_snd->reset(); 
									fight_sfx = WAIT;
								}
								if (fight_sfx == RESET_MUSIC)
								{
									fight_snd->stop();
									fight_snd->reset();
									fight_sfx = WAIT;
								}
								if (fight_sfx == PLAY || fight_sfx == FADE_IN)
								{
									if (fight_snd->isPlaying() == false)
										fight_snd->play();

									if (fight_sfx == PLAY)
									{
										fight_sfx = LOOP;

										if (half_volume == false)
											fight_snd->setVolume(music_volume);
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											fight_snd->setVolume(music_volume / 2);
										}

									}
								}
								if (jet_sfx == NO_ANIM)
								{
									jet1_snd->stop();
									jet1_snd->reset();
									jet2_snd->stop();
									jet2_snd->reset();
									jet3_snd->stop();
									jet3_snd->reset();
									jet4_snd->stop();
									jet4_snd->reset();

									jet_sfx = WAIT;
								}
								if (jet_sfx == PLAY || jet_sfx == FADE_IN)
								{
									if (VG_IS_VERSUS_SCREEN == true)
										if (jet1_snd->isPlaying() == false)
											jet1_snd->play();
									if (VG_IS_VERSUS_SCREEN == false)
										if (jet2_snd->isPlaying() == false)
											jet2_snd->play();

									if (jet_sfx == PLAY)
									{
										jet_sfx = LOOP;

										if (half_volume == false)
										{
											jet1_snd->setVolume(music_volume);
											jet2_snd->setVolume(music_volume);
											jet3_snd->setVolume(music_volume);
											jet4_snd->setVolume(music_volume);
										}
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											jet1_snd->setVolume(music_volume / 2);
											jet2_snd->setVolume(music_volume / 2);
											jet3_snd->setVolume(music_volume / 2);
											jet4_snd->setVolume(music_volume / 2);
										}
									}
								}

								if (siege_sfx == NO_ANIM)
								{
									siege1_snd->stop();
									siege1_snd->reset();
									siege2_snd->stop();
									siege2_snd->reset();
									siege3_snd->stop();
									siege3_snd->reset();
									siege4_snd->stop();
									siege4_snd->reset();
									siege5_snd->stop();
									siege5_snd->reset();
									siege6_snd->stop();
									siege6_snd->reset();

									siege_sfx = WAIT;
								}
								if (siege_sfx == PLAY || siege_sfx == FADE_IN)
								{

									if (VG_CS_SONG == CS_DANGER1)
										if (siege1_snd->isPlaying() == false)
											siege1_snd->play();
									if (VG_CS_SONG == CS_DANGER2)
										if (siege2_snd->isPlaying() == false)
											siege2_snd->play();
									if (VG_CS_SONG == CS_VICTORY)
										if (siege3_snd->isPlaying() == false)
											siege3_snd->play();
									if (VG_CS_SONG == CS_ENDING)
										if (siege4_snd->isPlaying() == false)
											siege4_snd->play();
									if (VG_CS_SONG == CS_BOSSIDLE)
										if (siege5_snd->isPlaying() == false)
											siege5_snd->play();
									if (VG_CS_SONG == CS_IDLE)
										if (siege6_snd->isPlaying() == false)
											siege6_snd->play();

									if (siege_sfx == PLAY)
									{
										siege_sfx = LOOP;

										if (half_volume == false)
										{
											siege1_snd->setVolume(music_volume);
											siege2_snd->setVolume(music_volume);
											siege3_snd->setVolume(music_volume);
											siege4_snd->setVolume(music_volume);
											siege5_snd->setVolume(music_volume);
											siege6_snd->setVolume(music_volume);
										}
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											siege1_snd->setVolume(music_volume / 2);
											siege2_snd->setVolume(music_volume / 2);
											siege3_snd->setVolume(music_volume / 2);
											siege4_snd->setVolume(music_volume / 2);
											siege5_snd->setVolume(music_volume / 2);
											siege6_snd->setVolume(music_volume / 2);
										}

									}

								}
								if (theatre_sfx == NO_ANIM)
								{
									theatre_snd->stop();
									theatre_snd->reset();
									theatre_sfx = WAIT;
								}
								if (theatre_sfx == PLAY || theatre_sfx == FADE_IN)
								{
									if (theatre_snd->isPlaying() == false)
										theatre_snd->play();

									if (theatre_sfx == PLAY)
									{
										theatre_sfx = LOOP;

										if (half_volume == false)
											theatre_snd->setVolume(music_volume);
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											theatre_snd->setVolume(music_volume / 2);
										}

									}
								}
								if (credits_sfx == NO_ANIM)
								{
									credits1_snd->stop();
									credits1_snd->reset();
									credits2_snd->stop();
									credits2_snd->reset();
									credits3_snd->stop();
									credits3_snd->reset();

									credits_sfx = WAIT;
								}
								if (credits_sfx == PLAY || credits_sfx == FADE_IN)
								{

									if (credits_sfx == PLAY)
									{
										credits_sfx = LOOP;

										if (half_volume == false)
										{
											credits1_snd->setVolume(music_volume);
											credits2_snd->setVolume(music_volume);
											credits3_snd->setVolume(music_volume);
										}
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)

												temp_music_volume = 0.0f;

											credits1_snd->setVolume(music_volume / 2);
											credits2_snd->setVolume(music_volume / 2);
											credits3_snd->setVolume(music_volume / 2);
										}

									}
								}
								if (sad_sfx == NO_ANIM)
								{
									sad_snd->stop();
									//    sad_snd->reset();     
									sad_sfx = WAIT;
								}
								if (sad_sfx == RESET_MUSIC)
								{
									sad_snd->stop();
									sad_snd->reset();
									sad_sfx = WAIT;
								}
								if (sad_sfx == PLAY || sad_sfx == FADE_IN)
								{
									if (sad_snd->isPlaying() == false)
										sad_snd->play();

									if (sad_sfx == PLAY)
									{
										sad_sfx = LOOP;

										if (half_volume == false)
											sad_snd->setVolume(music_volume);
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											sad_snd->setVolume(music_volume / 2);
										}

									}
								}
								if (intro_sfx == NO_ANIM)
								{
									intro_snd->stop();
									intro_snd->reset();
									intro_sfx = WAIT;
								}
								if (intro_sfx == PLAY || intro_sfx == FADE_IN)
								{
									if (intro_snd->isPlaying() == false)
										intro_snd->play();

									if (intro_sfx == PLAY)
									{
										intro_sfx = LOOP;

										intro_snd->setVolume(music_volume);

										/*               if(game_mode == WALK)
										intro_snd->setVolume(music_volume);
										else
										{
										temp_music_volume = music_volume/2;

										if(temp_music_volume < 0.0f)
										temp_music_volume = 0.0f;

										intro_snd->setVolume(music_volume/2);
										}*/

									}
								}
								if (mini_sfx == NO_ANIM)
								{
									mini_snd->stop();
									//    mini_snd->reset();   
									mini_sfx = WAIT;
								}
								if (mini_sfx == RESET_MUSIC)
								{
									mini_snd->stop();
									mini_snd->reset();
									mini_sfx = WAIT;
								}

								if (mini_sfx == PLAY || mini_sfx == FADE_IN)
								{

									if (mini_snd->isPlaying() == false)
										mini_snd->play();

									if (mini_sfx == PLAY)
									{
										mini_sfx = LOOP;

										if (half_volume == false)
											mini_snd->setVolume(music_volume);
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											mini_snd->setVolume(music_volume / 2);
										}

									}

								}
								if (urgency_sfx == NO_ANIM)
								{
									urgency_snd->stop();
									//    urgency_snd->reset();   
									urgency_sfx = WAIT;
								}
								if (urgency_sfx == PLAY || urgency_sfx == FADE_IN)
								{
									if (urgency_snd->isPlaying() == false)
										urgency_snd->play();

									if (urgency_sfx == PLAY)
									{
										urgency_sfx = LOOP;

										if (half_volume == false)
											urgency_snd->setVolume(music_volume);
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											urgency_snd->setVolume(music_volume / 2);
										}

									}
								}
								if (fanfare_sfx == NO_ANIM)
								{
									fanfare_snd->stop();
									fanfare_snd->reset();
									fanfare_sfx = WAIT;
								}
								if (fanfare_sfx == PLAY || fanfare_sfx == FADE_IN)
								{
									if (fanfare_snd->isPlaying() == false)
										fanfare_snd->play();

									if (fanfare_sfx == PLAY)
									{
										fanfare_sfx = LOOP;

										if (half_volume == false)
											fanfare_snd->setVolume(music_volume);
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											fanfare_snd->setVolume(music_volume / 2);
										}

									}
								}
								if (fanfare2_sfx == NO_ANIM)
								{
									fanfare2_snd->stop();
									fanfare2_snd->reset();
									fanfare2_sfx = WAIT;
								}
								if (fanfare2_sfx == PLAY || fanfare2_sfx == FADE_IN)
								{
									if (fanfare2_snd->isPlaying() == false)
										fanfare2_snd->play();

									if (fanfare2_sfx == PLAY)
									{
										fanfare2_sfx = LOOP;

										if (half_volume == false)
											fanfare2_snd->setVolume(music_volume);
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											fanfare2_snd->setVolume(music_volume / 2);
										}

									}
								}
								if (deathscreen_sfx == NO_ANIM)
								{
									deathscreen_snd->stop();
									deathscreen_snd->reset();
									deathscreen_sfx = WAIT;
								}
								if (deathscreen_sfx == PLAY || deathscreen_sfx == FADE_IN)
								{
									if (deathscreen_snd->isPlaying() == false)
										deathscreen_snd->play();

									if (deathscreen_sfx == PLAY)
									{
										deathscreen_sfx = LOOP;

										if (half_volume == false)
											deathscreen_snd->setVolume(music_volume);
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											deathscreen_snd->setVolume(music_volume / 2);
										}

									}
								}

								if (dgnb_sfx == NO_ANIM)
								{
									dgnb_snd->stop();
									dgnb_snd->reset();
									dgnb_sfx = WAIT;
								}
								if (dgnb_sfx == PLAY || dgnb_sfx == FADE_IN)
								{
									if (dgnb_snd->isPlaying() == false)
										dgnb_snd->play();

									if (dgnb_sfx == PLAY)
									{
										dgnb_sfx = LOOP;

										if (half_volume == false)
											dgnb_snd->setVolume(music_volume);
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											dgnb_snd->setVolume(music_volume / 2);
										}

									}
								}
								if (final_sfx == NO_ANIM)
								{
									final_snd->stop();
									final_snd->reset();
									final_sfx = WAIT;
								}
								if (final_sfx == PLAY || final_sfx == FADE_IN)
								{
									if (final_snd->isPlaying() == false)
										final_snd->play();

									if (final_sfx == PLAY)
									{
										final_sfx = LOOP;

										if (half_volume == false)
											final_snd->setVolume(music_volume);
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											final_snd->setVolume(music_volume / 2);
										}

									}
								}
								if (dangers_sfx == NO_ANIM)
								{
									dangers_snd->stop();
									dangers_snd->reset();
									dangers_sfx = WAIT;
								}

								if (dangers_sfx == PLAY || dangers_sfx == FADE_IN)
								{
									if (dangers_snd->isPlaying() == false)
										dangers_snd->play();

									if (dangers_sfx == PLAY)
									{
										dangers_sfx = LOOP;

										if (half_volume == false)
											dangers_snd->setVolume(music_volume);
										else
										{
											temp_music_volume = music_volume / 2;

											if (temp_music_volume < 0.0f)
												temp_music_volume = 0.0f;

											dangers_snd->setVolume(music_volume / 2);
										}

									}
								}


							} // music_volume != 0.0


							  //       
							  // SFX start.......     
							  //      


							if (vg_round_sfx == true)
							{
								vg_round_sfx = false;

								vg_round1_snd->setVolume(sfx_volume);
								vg_round2_snd->setVolume(sfx_volume);
								vg_round3_snd->setVolume(sfx_volume);
								vg_round4_snd->setVolume(sfx_volume);
								vg_round5_snd->setVolume(sfx_volume);
								vg_round6_snd->setVolume(sfx_volume);

								if (VG_ROUND == 1)
									vg_round1_snd->play();
								if (VG_ROUND == 2)
									vg_round2_snd->play();
								if (VG_ROUND == 3)
									vg_round3_snd->play();
								if (VG_ROUND == 4)
									vg_round4_snd->play();
								if (VG_ROUND == 5)
									vg_round5_snd->play();
								if (VG_ROUND == 6)
									vg_round6_snd->play();


							}

							if (VG_yell_sfx != -1)
							{

								if (VG_yell_sfx == VG_GYEONG)
								{
									YELL_gyeong_snd->setVolume(sfx_volume);
									YELL_gyeong_snd->play();
								}
								if (VG_yell_sfx == VG_SIU)
								{
									YELL_siu_snd->setVolume(sfx_volume);
									YELL_siu_snd->play();
								}
								if (VG_yell_sfx == VG_MINSO)
								{
									YELL_minso_snd->setVolume(sfx_volume);
									YELL_minso_snd->play();
								}
								if (VG_yell_sfx == VG_REESE)
								{
									YELL_reese_snd->setVolume(sfx_volume);
									YELL_reese_snd->play();
								}
								if (VG_yell_sfx == VG_YOHAN)
								{
									YELL_yohan_snd->setVolume(sfx_volume);
									YELL_yohan_snd->play();
								}
								if (VG_yell_sfx == VG_JAE)
								{
									YELL_jae_snd->setVolume(sfx_volume);
									YELL_jae_snd->play();
								}
								if (VG_yell_sfx == VG_GUN)
								{
									YELL_gun_snd->setVolume(sfx_volume);
									YELL_gun_snd->play();
								}
								if (VG_yell_sfx == VG_HYUK)
								{
									YELL_hyuk_snd->setVolume(sfx_volume);
									YELL_hyuk_snd->play();
								}
								if (VG_yell_sfx == VG_SANG)
								{
									YELL_sang_snd->setVolume(sfx_volume);
									YELL_sang_snd->play();
								}
								if (VG_yell_sfx == VG_TRAINER)
								{
									YELL_trainer_snd->setVolume(sfx_volume);
									YELL_trainer_snd->play();
								}
								if (VG_yell_sfx == VG_KENNEDY)
								{
									YELL_gun_snd->setVolume(sfx_volume);
									YELL_gun_snd->play();
								}

								VG_yell_sfx = -1;

							}

							if (VG_victory_sfx != -1)
							{
								WIN_gyeong_snd->setVolume(sfx_volume);
								WIN_siu_snd->setVolume(sfx_volume);
								WIN_minso_snd->setVolume(sfx_volume);
								WIN_reese_snd->setVolume(sfx_volume);
								WIN_yohan_snd->setVolume(sfx_volume);
								WIN_jae_snd->setVolume(sfx_volume);
								WIN_gun_snd->setVolume(sfx_volume);
								WIN_hyuk_snd->setVolume(sfx_volume);
								WIN_sang_snd->setVolume(sfx_volume);
								WIN_trainer_snd->setVolume(sfx_volume);

								if (VG_victory_sfx == VG_GYEONG)
									WIN_gyeong_snd->play();
								if (VG_victory_sfx == VG_SIU)
									WIN_siu_snd->play();
								if (VG_victory_sfx == VG_MINSO)
									WIN_minso_snd->play();
								if (VG_victory_sfx == VG_REESE)
									WIN_reese_snd->play();
								if (VG_victory_sfx == VG_YOHAN)
									WIN_yohan_snd->play();
								if (VG_victory_sfx == VG_JAE)
									WIN_jae_snd->play();
								if (VG_victory_sfx == VG_GUN)
									WIN_gun_snd->play();
								if (VG_victory_sfx == VG_HYUK)
									WIN_hyuk_snd->play();
								if (VG_victory_sfx == VG_SANG)
									WIN_sang_snd->play();
								if (VG_victory_sfx == VG_TRAINER)
									WIN_trainer_snd->play();
								if (VG_victory_sfx == VG_KENNEDY)
									WIN_gun_snd->play();

								VG_victory_sfx = -1;

							}
							if (VG_1_special1_sfx != 0)
							{

								if (sfx_volume > 0.0f)
									if (VG_1_special1_sfx == 1) // Stop the sound...
									{
										// Was stop...removed for bug crash...
									}
									else
									{

										if (VG_1_CHARACTER == VG_GYEONG)
										{
											gyeong_snd->setVolume(sfx_volume);
											gyeong_snd->play();
										}
										if (VG_1_CHARACTER == VG_SIU)
										{
											siu_snd->setVolume(sfx_volume);
											siu_snd->play();
										}
										if (VG_1_CHARACTER == VG_MINSO)
										{
											minso_snd->setVolume(sfx_volume);
											minso_snd->play();
										}
										if (VG_1_CHARACTER == VG_REESE)
										{
											reese_snd->setVolume(sfx_volume);
											reese_snd->play();
										}
										if (VG_1_CHARACTER == VG_YOHAN)
										{
											yohan_snd->setVolume(sfx_volume);
											yohan_snd->play();
										}
										if (VG_1_CHARACTER == VG_JAE)
										{
											jae_snd->setVolume(sfx_volume);
											jae_snd->play();
										}
										if (VG_1_CHARACTER == VG_GUN)
										{
											gun_snd->setVolume(sfx_volume);
											gun_snd->play();
										}
										if (VG_1_CHARACTER == VG_HYUK)
										{
											hyuk_snd->setVolume(sfx_volume);
											hyuk_snd->play();
										}
										if (VG_1_CHARACTER == VG_SANG)
										{
											sang_snd->setVolume(sfx_volume);
											sang_snd->play();
										}
										if (VG_1_CHARACTER == VG_TRAINER)
										{
											trainer_snd->setVolume(sfx_volume);
											trainer_snd->play();
										}
										if (VG_1_CHARACTER == VG_SHO)
										{
											siu_snd->setVolume(sfx_volume);
											siu_snd->play();
										}
										if (VG_1_CHARACTER == VG_SAIZO)
										{
											hyuk_snd->setVolume(sfx_volume);
											hyuk_snd->play();
										}
										if (VG_1_CHARACTER == VG_TIA)
										{
											minso_snd->setVolume(sfx_volume);
											minso_snd->play();
										}
										if (VG_1_CHARACTER == VG_KENNEDY)
										{
											gun_snd->setVolume(sfx_volume);
											gun_snd->play();
										}


									} // else

								VG_1_special1_sfx = 0;

							}

							if (VG_2_special1_sfx != 0)
							{

								if (sfx_volume > 0.0f)
									if (VG_2_special1_sfx == 1) // Stop the sound...
									{
										// Was stop...removed for bug crash...
									}
									else
									{
										if (VG_2_CHARACTER == VG_GYEONG)
										{
											gyeong2_snd->setVolume(sfx_volume);
											gyeong2_snd->play();
										}
										if (VG_2_CHARACTER == VG_SIU)
										{
											siu2_snd->setVolume(sfx_volume);
											siu2_snd->play();
										}
										if (VG_2_CHARACTER == VG_MINSO)
										{
											minso2_snd->setVolume(sfx_volume);
											minso2_snd->play();
										}
										if (VG_2_CHARACTER == VG_REESE)
										{
											reese2_snd->setVolume(sfx_volume);
											reese2_snd->play();
										}
										if (VG_2_CHARACTER == VG_YOHAN)
										{
											yohan_snd->setVolume(sfx_volume);
											yohan_snd->play();
										}
										if (VG_2_CHARACTER == VG_JAE)
										{
											jae2_snd->setVolume(sfx_volume);
											jae2_snd->play();
										}
										if (VG_2_CHARACTER == VG_GUN)
										{
											gun2_snd->setVolume(sfx_volume);
											gun2_snd->play();
										}
										if (VG_2_CHARACTER == VG_HYUK)
										{
											hyuk2_snd->setVolume(sfx_volume);
											hyuk2_snd->play();
										}
										if (VG_2_CHARACTER == VG_SANG)
										{
											sang2_snd->setVolume(sfx_volume);
											sang2_snd->play();
										}
										if (VG_2_CHARACTER == VG_TRAINER)
										{
											trainer2_snd->setVolume(sfx_volume);
											trainer2_snd->play();
										}
										if (VG_2_CHARACTER == VG_KENNEDY)
										{
											gun2_snd->setVolume(sfx_volume);
											gun2_snd->play();
										}

									} // else

								VG_2_special1_sfx = 0;

							}

							if (vg_titleselect_sfx == true)
							{
								vg_titleselect_sfx = false;
								vg_titleselect_snd->setVolume(sfx_volume);

								vg_titleselect_snd->play();

							}
							if (vg_gameover_sfx == true)
							{
								vg_gameover_sfx = false;
								vg_gameover_snd->setVolume(sfx_volume);
								vg_gameover_snd->play();
							}
							if (VG_title_sfx == true)
							{
								VG_title_sfx = false;
								VG_title_snd->setVolume(sfx_volume);
								VG_title_snd->play();
							}
							if (VG_verdict_sfx == true)
							{
								VG_verdict_sfx = false;
								VG_verdict_snd->setVolume(sfx_volume);
								VG_verdict_snd->play();
							}
							if (VG_knockslide_sfx == true)
							{
								VG_knockslide_sfx = false;
								vg_knockslide_snd->setVolume(sfx_volume);
								vg_knockslide_snd->play();
							}
							if (VG_guilty_sfx == true)
							{
								VG_guilty_sfx = false;
								VG_guilty_snd->setVolume(sfx_volume);
								VG_guilty_snd->play();
							}
							if (VG_titlevoice_sfx == true)
							{
								VG_titlevoice_sfx = false;
								VG_titlevoice_snd->setVolume(sfx_volume);
								VG_titlevoice_snd->play();
							}
							if (VG_pow_sfx == true)
							{
								VG_pow_sfx = false;
								VG_pow_snd->setVolume(sfx_volume);
								VG_pow_snd->play();
							}
							if (VG_destiny_sfx == true)
							{
								VG_destiny_sfx = false;
								VG_destiny_snd->setVolume(sfx_volume);
								VG_destiny_snd->play();
							}
							if (VG_alright_sfx == true)
							{
								VG_alright_sfx = false;
								VG_alright_snd->setVolume(sfx_volume);
								VG_alright_snd->play();
							}
							if (VG_nice_sfx == true)
							{
								VG_nice_sfx = false;
								VG_nice_snd->setVolume(sfx_volume);
								VG_nice_snd->play();
							}
							if (VG_okay_sfx == true)
							{
								VG_okay_sfx = false;
								VG_okay_snd->setVolume(sfx_volume);
								VG_okay_snd->play();
							}

							if (vg_judge_sfx == true)
							{
								vg_judge_sfx = false;
								YELL_judge_snd->setVolume(sfx_volume);
								YELL_judge_snd->play();
							}

							if (VG_good_sfx == true)
							{
								VG_good_sfx = false;
								VG_good_snd->setVolume(sfx_volume);
								VG_good_snd->play();
							}
							if (VG_great_sfx == true)
							{
								VG_great_sfx = false;
								VG_great_snd->setVolume(sfx_volume);
								VG_great_snd->play();
							}
							if (VG_excellent_sfx == true)
							{
								VG_excellent_sfx = false;
								VG_excellent_snd->setVolume(sfx_volume);
								VG_excellent_snd->play();
							}

							if (VG_reloadsfx == 1)
							{
								VG_reloadsfx = 2;
								vg_reload_snd->setVolume(sfx_volume);
								vg_reload_snd->play();
							}

							if (VG_reloadedsfx == 1)
							{
								VG_reloadedsfx = 2;
								vg_reloaded_snd->setVolume(sfx_volume);
								vg_reloaded_snd->play();
							}

							if (VG_handcuffs_sfx == true)
							{
								VG_handcuffs_sfx = false;
								vg_reloaded_snd->setVolume(sfx_volume);
								vg_reloaded_snd->play();
							}

							if (vg_perfect_sfx == true)
							{
								vg_perfect_sfx = false;
								vg_perfect_snd->setVolume(sfx_volume);
								vg_perfect_snd->play();
							}

							if (VG_arrested_sfx == true)
							{
								VG_arrested_sfx = false;
								vg_arrested_snd->setVolume(sfx_volume);
								vg_arrested_snd->play();
							}
							if (VG_wasted_sfx == true)
							{
								VG_wasted_sfx = false;
								vg_wasted_snd->setVolume(sfx_volume);
								vg_wasted_snd->play();
							}

							if (VG_power_sfx == true)
							{
								VG_power_sfx = false;

								rnd = rand() % 4;

								if (rnd == 0)
								{
									vg_power1_snd->setVolume(sfx_volume);
									vg_power1_snd->play();
								}
								if (rnd == 1)
								{
									vg_power2_snd->setVolume(sfx_volume);
									vg_power2_snd->play();
								}
								if (rnd == 2)
								{
									vg_power3_snd->setVolume(sfx_volume);
									vg_power3_snd->play();
								}
								if (rnd == 3)
								{
									vg_power4_snd->setVolume(sfx_volume);
									vg_power4_snd->play();
								}
							}

							if (VG_KO_sfx == true)
							{
								VG_KO_sfx = false;

								if (VG_KOED_CHARACTER == VG_GYEONG)
								{
									vg_ko_1_snd->setVolume(sfx_volume);
									vg_ko_1_snd->play();
								}
								if (VG_KOED_CHARACTER == VG_SIU)
								{
									vg_ko_2_snd->setVolume(sfx_volume);
									vg_ko_2_snd->play();
								}
								if (VG_KOED_CHARACTER == VG_MINSO)
								{
									vg_ko_3_snd->setVolume(sfx_volume);
									vg_ko_3_snd->play();
								}
								if (VG_KOED_CHARACTER == VG_REESE)
								{
									vg_ko_4_snd->setVolume(sfx_volume);
									vg_ko_4_snd->play();
								}
								if (VG_KOED_CHARACTER == VG_YOHAN)
								{
									vg_ko_5_snd->setVolume(sfx_volume);
									vg_ko_5_snd->play();
								}
								if (VG_KOED_CHARACTER == VG_JAE)
								{
									vg_ko_6_snd->setVolume(sfx_volume);
									vg_ko_6_snd->play();
								}
								if (VG_KOED_CHARACTER == VG_GUN)
								{
									vg_ko_7_snd->setVolume(sfx_volume);
									vg_ko_7_snd->play();
								}
								if (VG_KOED_CHARACTER == VG_HYUK)
								{
									vg_ko_8_snd->setVolume(sfx_volume);
									vg_ko_8_snd->play();
								}
								if (VG_KOED_CHARACTER == VG_SANG)
								{
									vg_ko_9_snd->setVolume(sfx_volume);
									vg_ko_9_snd->play();
								}
								if (VG_KOED_CHARACTER == VG_TRAINER)
								{
									vg_ko_10_snd->setVolume(sfx_volume);
									vg_ko_10_snd->play();
								}
								if (VG_KOED_CHARACTER == VG_SHO)
								{
									vg_ko_11_snd->setVolume(sfx_volume);
									vg_ko_11_snd->play();
								}
								if (VG_KOED_CHARACTER == VG_TIA)
								{
									vg_ko_12_snd->setVolume(sfx_volume);
									vg_ko_12_snd->play();
								}
								if (VG_KOED_CHARACTER == VG_SAIZO)
								{
									vg_ko_13_snd->setVolume(sfx_volume);
									vg_ko_13_snd->play();
								}
								if (VG_KOED_CHARACTER == VG_KENNEDY)
								{
									vg_ko_14_snd->setVolume(sfx_volume);
									vg_ko_14_snd->play();
								}

							}

							if (vg_ko_smash_sfx == true)
							{
								vg_ko_smash_sfx = false;

								VG_rnd = rand() % 4;

								if (VG_rnd == 0)
								{
									vg_ko_snd->setVolume(sfx_volume);
									vg_ko_snd->play();
								}
								if (VG_rnd == 1)
								{
									vg_ko1_snd->setVolume(sfx_volume);
									vg_ko1_snd->play();
								}
								if (VG_rnd == 2)
								{
									vg_ko2_snd->setVolume(sfx_volume);
									vg_ko2_snd->play();
								}
								if (VG_rnd == 3)
								{
									vg_ko3_snd->setVolume(sfx_volume);
									vg_ko3_snd->play();
								}

							}


							if (vg_fight_sfx == true)
							{
								vg_fight_sfx = false;
								vg_fight_snd->setVolume(sfx_volume);
								vg_fight_snd->play();
							}

							if (vg_amb_car1_sfx == true)
							{
								vg_amb_car1_sfx = false;

								vg_amb_car1_snd->setVolume(sfx_volume);

								vg_amb_car1_snd->play();
							}

							if (vg_amb_car2_sfx == true)
							{
								vg_amb_car2_sfx = false;

								vg_amb_car2_snd->setVolume(sfx_volume);

								vg_amb_car2_snd->play();


							}

							if (vg_blocked_sfx == true)
							{
								vg_blocked_sfx = false;
								vg_blocked_snd->setVolume(sfx_volume);
								vg_blocked_snd->play();
							}

							if (vg_knockdown_sfx == true)
							{
								vg_knockdown_sfx = false;
								vg_knockdown_snd->setVolume(sfx_volume);
								vg_knockdown_snd->play();
							}

							if (vg_shout_sfx == true)
							{
								vg_shout_sfx = false;
								vg_shout_snd->setVolume(sfx_volume);
								vg_shout_snd->play();
							}
							if (vg_siren_sfx == true)
							{
								vg_siren_sfx = false;
								vg_siren_snd->setVolume(sfx_volume);
								vg_siren_snd->play();
							}

							if (vg_titlemove_sfx == true)
							{
								vg_titlemove_sfx = false;
								vg_titlemove_snd->setVolume(sfx_volume);
								vg_titlemove_snd->play();
							}

							if (vg_vacuum_sfx == true)
							{
								vg_vacuum_sfx = false;
								vg_vacuum_snd->setVolume(sfx_volume);
								vg_vacuum_snd->play();
							}



							if (vg_title_move_sfx == true)
							{
								vg_title_move_sfx = false;
								vg_title_move->setVolume(sfx_volume);
								vg_title_move->play();
							}


							if (VG_1_Mgunsfx != 0)
							{
								vg_mgun_snd->setVolume(sfx_volume);
								if (VG_1_Mgunsfx == 1)
									vg_mgun_snd->play();

								VG_1_Mgunsfx = 2;


							}

							if (VG_2_Mgunsfx != 0)
							{
								vg_mgun_snd->setVolume(sfx_volume);
								if (VG_2_Mgunsfx == 1)
									vg_mgun_snd->play();

								VG_2_Mgunsfx = 2;


							}
							if (VG_1_Vialsfx != 0)
							{
								vg_knife_snd->setVolume(sfx_volume);
								if (VG_1_Vialsfx == 1)
									vg_knife_snd->play();

								VG_1_Vialsfx = 2;

							}

							if (VG_2_Vialsfx != 0)
							{
								vg_knife_snd->setVolume(sfx_volume);
								if (VG_2_Vialsfx == 1)
									vg_knife_snd->play();

								VG_2_Vialsfx = 2;

							}
							if (VG_1_Pfpsfx != 0)
							{
								vg_knife_snd->setVolume(sfx_volume);
								if (VG_1_Pfpsfx == 1)
									vg_knife_snd->play();

								VG_1_Pfpsfx = 2;

							}

							if (VG_2_Pfpsfx != 0)
							{
								VG_land_snd->setVolume(sfx_volume);
								if (VG_2_Pfpsfx == 1)
									VG_land_snd->play();

								VG_2_Pfpsfx = 2;

							}
							if (VG_1_Knifesfx != 0)
							{
								VG_land_snd->setVolume(sfx_volume);
								if (VG_1_Knifesfx == 1)
									VG_land_snd->play();

								VG_1_Knifesfx = 2;


							}

							if (VG_2_Knifesfx != 0)
							{
								vg_knife_snd->setVolume(sfx_volume);
								if (VG_2_Knifesfx == 1)
									vg_knife_snd->play();

								VG_2_Knifesfx = 2;


							}
							if (VG_1_Grenadesfx != 0)
							{
								vg_knife_snd->setVolume(sfx_volume);
								if (VG_1_Grenadesfx == 1)
									vg_knife_snd->play();

								VG_1_Grenadesfx = 2;


							}

							if (VG_2_Grenadesfx != 0)
							{
								vg_knife_snd->setVolume(sfx_volume);

								if (VG_2_Grenadesfx == 1)
									vg_knife_snd->play();

								VG_2_Grenadesfx = 2;


							}
							if (VG_1_Pistolsfx != 0)
							{
								vg_pistol1_snd->setVolume(sfx_volume);
								vg_shotgun1_snd->setVolume(sfx_volume);
								vg_orb_snd->setVolume(sfx_volume);

								if (VG_1_Pistolsfx == 1)
								{
									if (VG_1_CHARACTER == VG_REESE || VG_1_CHARACTER == VG_SHO || VG_1_CHARACTER == VG_TIA || VG_1_CHARACTER == VG_SAIZO)
									{
										vg_orb_snd->play();
									}
									else
									{
										if (VG_1_CHARACTER != VG_TRAINER)
											vg_pistol1_snd->play();
										else
											vg_shotgun1_snd->play();
									}
								}

								VG_1_Pistolsfx = 2;

							}

							if (VG_2_Pistolsfx != 0)
							{

								vg_pistol2_snd->setVolume(sfx_volume);
								vg_shotgun2_snd->setVolume(sfx_volume);
								vg_orb2_snd->setVolume(sfx_volume);

								if (VG_2_Pistolsfx == 1)
								{
									if (VG_2_CHARACTER == VG_REESE || VG_2_CHARACTER == VG_SHO || VG_2_CHARACTER == VG_TIA || VG_2_CHARACTER == VG_SAIZO)
									{
										vg_orb2_snd->play();
									}
									else
									{
										if (VG_2_CHARACTER != VG_TRAINER)
											vg_pistol2_snd->play();
										else
											vg_shotgun2_snd->play();
									}
								}

								VG_2_Pistolsfx = 2;

							}

							if (vg_lose_sfx == true)
							{
								vg_lose_sfx = false;
								vg_lose_snd->setVolume(sfx_volume);
								vg_lose_snd->play();

							}

							if (vg_tink_sfx == true)
							{
								vg_tink_sfx = false;
								vg_tink_snd->setVolume(sfx_volume);
								vg_tink_snd->play();

							}

							if (vg_ric_sfx == true)
							{
								vg_ric_sfx = false;

								vg_ric1_snd->setVolume(sfx_volume);
								vg_ric2_snd->setVolume(sfx_volume);
								vg_ric3_snd->setVolume(sfx_volume);

								VG_rnd = rand() % 3;

								if (VG_rnd == 0)
									vg_ric1_snd->play();
								if (VG_rnd == 1)
									vg_ric2_snd->play();
								if (VG_rnd == 2)
									vg_ric3_snd->play();


							}


							if (vg_shock_sfx == true)
							{
								vg_shock_sfx = false;
								vg_shock_snd->setVolume(sfx_volume);
								vg_shock_snd->play();
							}

							if (VG_1_chop_sfx == 1)
							{
								vg_chop_snd->setVolume(sfx_volume);
								vg_chop1_snd->setVolume(sfx_volume);
								vg_chop2_snd->setVolume(sfx_volume);
								vg_chop3_snd->setVolume(sfx_volume);

								if (VG_1_chop_sfx == 1)
								{
									VG_rnd = rand() % 4;

									if (VG_rnd == 0)
										vg_chop_snd->play();
									if (VG_rnd == 1)
										vg_chop1_snd->play();
									if (VG_rnd == 2)
										vg_chop2_snd->play();
									if (VG_rnd == 3)
										vg_chop3_snd->play();

								}

								VG_1_chop_sfx = 2;

							}
							if (VG_2_chop_sfx == 1)
							{
								vg_chop_snd->setVolume(sfx_volume);
								vg_chop1_snd->setVolume(sfx_volume);
								vg_chop2_snd->setVolume(sfx_volume);
								vg_chop3_snd->setVolume(sfx_volume);

								if (VG_2_chop_sfx == 1)
								{
									VG_rnd = rand() % 4;

									if (VG_rnd == 0)
										vg_chop_snd->play();
									if (VG_rnd == 1)
										vg_chop1_snd->play();
									if (VG_rnd == 2)
										vg_chop2_snd->play();
									if (VG_rnd == 3)
										vg_chop3_snd->play();
								}

								VG_2_chop_sfx = 2;

							}
							if (vg_explode_sfx == true)
							{
								vg_explode_sfx = false;
								vg_explode_snd->setVolume(sfx_volume);
								vg_explode_snd->play();

							}
							if (vg_splat_sfx == true)
							{
								vg_splat_sfx = false;
								vg_splat_snd->setVolume(sfx_volume);
								vg_splat_snd->play();

							}
							if (vg_win_sfx == true)
							{
								vg_win_sfx = false;
								vg_win_snd->setVolume(sfx_volume);
								vg_win_snd->play();

							}

							if (vg_glass_sfx == true)
							{
								vg_glass_sfx = false;

								vg_glass1_snd->setVolume(sfx_volume);
								vg_glass2_snd->setVolume(sfx_volume);
								vg_glass3_snd->setVolume(sfx_volume);
								vg_glass4_snd->setVolume(sfx_volume);

								VG_rnd = rand() % 4;

								if (VG_rnd == 0)
									vg_glass1_snd->play();
								if (VG_rnd == 1)
									vg_glass2_snd->play();
								if (VG_rnd == 2)
									vg_glass3_snd->play();
								if (VG_rnd == 3)
									vg_glass4_snd->play();

							}

							if (vg_hitsound_sfx == true)
							{
								vg_hitsound_sfx = false;

								vg_hitsound_snd->setVolume(sfx_volume);
								vg_hitsound1_snd->setVolume(sfx_volume);
								vg_hitsound2_snd->setVolume(sfx_volume);
								vg_hitsound3_snd->setVolume(sfx_volume);
								vg_hitsound4_snd->setVolume(sfx_volume);
								vg_hitsound5_snd->setVolume(sfx_volume);
								vg_hitsound6_snd->setVolume(sfx_volume);
								vg_hitsound7_snd->setVolume(sfx_volume);

								VG_rnd = rand() % 8;

								if (VG_rnd == 0)
									vg_hitsound_snd->play();
								if (VG_rnd == 1)
									vg_hitsound1_snd->play();
								if (VG_rnd == 2)
									vg_hitsound2_snd->play();
								if (VG_rnd == 3)
									vg_hitsound3_snd->play();
								if (VG_rnd == 4)
									vg_hitsound4_snd->play();
								if (VG_rnd == 5)
									vg_hitsound5_snd->play();
								if (VG_rnd == 6)
									vg_hitsound6_snd->play();
								if (VG_rnd == 7)
									vg_hitsound7_snd->play();


							}



							if (vg_dogattack_sfx == true)
							{
								vg_dogattack_sfx = false;
								vg_dogattack_snd->setVolume(sfx_volume);
								vg_dogattack_snd->play();

							}


							if (vg_stamp_sfx == true)
							{

								vg_stamp_snd->setVolume(sfx_volume);

								vg_stamp_snd->play();

								vg_stamp_sfx = false;

							}

							if (VG_land_sfx == true)
							{

								VG_land_snd->setVolume(sfx_volume);

								VG_land_snd->play();

								VG_land_sfx = false;

							}

							if (vg_amb_prison_sfx == true)
							{
								//           untie_snd->reset();          
								vg_amb_prison_snd->setVolume(sfx_volume);
								vg_amb_prison_snd->play();

								vg_amb_prison_sfx = false;

							}

							if (vg_amb_subway_sfx == true)
							{
								vg_amb_subway_snd->reset();

								vg_amb_subway_snd->setVolume(sfx_volume);
								vg_amb_subway_snd->setRepeat(false);

								vg_amb_subway_snd->play();

								vg_amb_subway_sfx = false;

							}

							if (vg_amb_traffic_sfx == true)
							{
								vg_amb_traffic_snd->reset();

								vg_amb_traffic_snd->setVolume(sfx_volume);
								vg_amb_traffic_snd->setRepeat(true);

								vg_amb_traffic_snd->play();

								vg_amb_traffic_sfx = false;

							}

							if (vg_amb_duel_sfx == true)
							{
								vg_amb_duel_snd->reset();

								vg_amb_duel_snd->setVolume(sfx_volume);
								vg_amb_duel_snd->setRepeat(true);

								vg_amb_duel_snd->play();

								vg_amb_duel_sfx = false;

							}

							if (vg_amb_van_sfx == true)
							{
								vg_amb_van_snd->reset();

								vg_amb_van_snd->setVolume(sfx_volume);
								vg_amb_van_snd->setRepeat(true);

								vg_amb_van_snd->play();

								vg_amb_van_sfx = false;

							}

							if (stop_vg_amb_prison_sfx == true)
							{

								if (vg_amb_prison_snd->isPlaying() == true)
									vg_amb_prison_snd->stop();

								vg_amb_prison_snd->reset();

								stop_vg_amb_prison_sfx = false;
							}

							if (stop_vg_amb_traffic_sfx == true)
							{
								if (vg_amb_traffic_snd->isPlaying() == true)
									vg_amb_traffic_snd->stop();

								vg_amb_traffic_snd->reset();

								stop_vg_amb_traffic_sfx = false;
							}

							if (stop_vg_amb_subway_sfx == true)
							{
								if (vg_amb_subway_snd->isPlaying() == true)
									vg_amb_subway_snd->stop();

								vg_amb_subway_snd->reset();

								stop_vg_amb_subway_sfx = false;
							}

							if (stop_vg_amb_van_sfx == true)
							{
								if (vg_amb_van_snd->isPlaying() == true)
									vg_amb_van_snd->stop();

								vg_amb_van_snd->reset();

								stop_vg_amb_van_sfx = false;
							}

							if (stop_vg_amb_duel_sfx == true)
							{
								if (vg_amb_duel_snd->isPlaying() == true)
									vg_amb_duel_snd->stop();

								vg_amb_duel_snd->reset();

								stop_vg_amb_duel_sfx = false;
							}


						}

						mousewheel = RESET;

					}// Quit_timer == false     


				}

			Main_cycle = (int)TimerGetTime() - Main_cycle;

		} // Peek_message       
        
}

void GameRender()
{
	//    if(fade != 0.0f)                             
	if (double_main_code == 0)
		if ((int)TimerGetTime() > AI_Time)
		{

			Draw_cycle = (int)TimerGetTime();

			DrawGLScene(false, (int)TimerGetTime() - Draw_Start);

			Draw_cycle = (int)TimerGetTime() - Draw_cycle;

			Draw_Start = (int)TimerGetTime();
			AI_Time = (int)TimerGetTime() + RENDER_RATE;  //1  

		}
}

#endif
          
bool New_FX(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int i_value, int i_type, int state, int linked_sprite, int tex_id, int i_value1, int i_value2, int i_value3)
{   
    // sideways = item_value    
    // upways   = item_type                     
    
    int end_id=0;                        
    int temp_row_x=0;                            
    int temp_row_y=0;  
    int testX=0, testY=0;       
    int my_row_x=0, my_row_y=0;          
    int row_index=0;                 
    int test_row_x=0;                              
    int test_row_y=0;                                  
    int test_index=0;     
    bool my_row_available=false; 
    bool test_success=true;            
    bool no_item_here=false;          
    int direction = 0; 
    int rnd=0;   
    float x1 = 0.0f, y1 = 0.0f;            
	bool not_created=false;
                      
    if(no_fx >= 0 && no_fx < TOTAL_NO_FX_SPRITES) 
    {               

        end_id = no_fx;

		// Reset the new FX...
		Reset_FX(end_id, false);             
        
        if(linked_sprite >= 0 && linked_sprite < TOTAL_NO_SPRITES)      
            Fx[end_id].linked_sprite = linked_sprite;
           
        Fx[end_id].x = x;                
        Fx[end_id].y = y;           

        Fx[end_id].w = w;                   
        Fx[end_id].z = z;  
   
        Fx[end_id].width = width;
        Fx[end_id].height = height;  
        Fx[end_id].box_width = box_width;      
        Fx[end_id].box_height = box_height;  
      
        Fx[end_id].sector_action = -1;     
        Fx[end_id].sparkle_timer = -1;
     
        Fx[end_id].value     = i_value; // item_value 
        Fx[end_id].value1    = i_value1; 
        Fx[end_id].value2    = i_value2;
		Fx[end_id].value3    = i_value3;
		Fx[end_id].item_type = i_type; // item_type
                        
        Fx[end_id].id = tex_id;                      
                               
        if(anim_state != NO_ANIM)                      
        {      

			if( Fx[end_id].id >= 0 && Fx[end_id].id < 200)
	            Fx[end_id].fx_id = animation_fx[Fx[end_id].id];
                                                                                                
            Fx[end_id].anim = anim;   

			Fx[end_id].base_anim = anim;
                               
            Fx[end_id].cur = 0;                            
                                              
            Fx[end_id].anim_state = anim_state;      
            
			if( Fx[end_id].fx_id >= 0 && Fx[end_id].fx_id < 75)
			if( Fx[end_id].anim >= 0 && Fx[end_id].anim < 256)
			if( Fx[end_id].cur >= 0 && Fx[end_id].cur < 256)    
            	Fx[end_id].frame = a_texture[Fx[end_id].fx_id].anims[Fx[end_id].anim][Fx[end_id].cur];
                    
            Set_Sprite(end_id, anim, anim_state, ANIM_FX, ANIM_WALKING);
         
        }                                                          
                       
        Fx[end_id].turn_off = false;        
               
        Fx[end_id].alpha = alpha; 

        Fx[end_id].fire_target = -1;  

        Fx[end_id].priority = priority;
                               
        Fx[end_id].type = type;                     
        
        Fx[end_id].mouseover = false;   
        
        Fx[end_id].spin = 0.0f;         
             
        Fx[end_id].angle = 0.0f;           
                    
        Fx[end_id].angle2 = 0.0f;                                      
                                 
        Fx[end_id].distance = 0.0f;                                           
                   
        Fx[end_id].flash_target = false;            
                             
        Fx[end_id].sector = state;                               
              
        Fx[end_id].light = 1.0;   

		Fx[end_id].bomb_timer = 0;

		Fx[end_id].all_timer = 0;

		if(state == FX_VG_TRAIL)
		if(linked_sprite >= 0 && linked_sprite < TOTAL_NO_FX_SPRITES)
			Fx[end_id].angle = Fx[linked_sprite].angle;

		if(state == FX_VG_TRAIL_SPRITE)
		if(linked_sprite >= 0 && linked_sprite < TOTAL_NO_SPRITES)
			Fx[end_id].angle = sprite[linked_sprite].angle;

		if(state == FX_VG_CASING)
		{
			 rnd = rand()%314;	
             Fx[end_id].angle = (float)rnd;
			 Fx[end_id].bomb_timer = -1;
		}

		if(state == FX_VG_ORB)
			Fx[end_id].bomb_timer = (int)TimerGetTime() + 6000;

		if(state == FX_VG_FIREBALL)
			Fx[end_id].bomb_timer = (int)TimerGetTime() + 6000;

		if(state == FX_VG_KUNAI)
			Fx[end_id].bomb_timer = (int)TimerGetTime() + 6000;

		if(state == FX_VG_MONEY)
			 Fx[end_id].bomb_timer = -1;

		if(state == FX_VG_BULLET || state == FX_VG_BULLET_LOW || state == FX_VG_ORB || state == FX_VG_FIREBALL || state == FX_VG_KUNAI)
			Fx[end_id].grab_switch = false;

		if(state == FX_VG_VIAL || state == FX_VG_VIAL_LOW)
		{
			Fx[end_id].grab_switch = false;
			Fx[end_id].knockdown_Y = Fx[end_id].y;
			Fx[end_id].knockdown = false;
		}

		if(state == FX_VG_KNIFE)
		{
			Fx[end_id].grab_switch = false;
			Fx[end_id].knockdown_Y = Fx[end_id].y;
			Fx[end_id].knockdown = false;
		}

		if(state == FX_VG_STICKYB || state == FX_VG_STICKYG || state == FX_VG_STICKYS) 
		{
			Fx[end_id].bomb_timer = (int)TimerGetTime() + 1000;
			Set_Sprite(end_id, 24 + Fx[end_id].value1, LOOP, ANIM_FX, ANIM_NOT_WALKING);
		}
		 
		if(state == FX_VG_GRENADE) 
		{
			Fx[end_id].grab_switch = true;
			Fx[end_id].knockdown_Y = Fx[end_id].y;
			Fx[end_id].shell_x = Fx[end_id].x;
			Fx[end_id].knockdown = false;
			Fx[end_id].bomb_timer = -1; 
		} 
		 
		if(state == FX_VG_BOMBSAIZO) 
		{
			Fx[end_id].grab_switch = true;
			Fx[end_id].knockdown_Y = Fx[end_id].y;
			Fx[end_id].shell_x = Fx[end_id].x;
			Fx[end_id].knockdown = false;
			Fx[end_id].bomb_timer = -1; 
		} 

		if(state == FX_VG_BOMB) 
		{
			Fx[end_id].grab_switch = false;
			Fx[end_id].bomb_timer = (int)TimerGetTime() + 1000; 
		}

		if(state == FX_VG_EXPLOSION)
			Fx[end_id].grab_switch = false;

		if(state == FX_VG_EXPLOSIONSAIZO)
			Fx[end_id].grab_switch = false;

        if(not_created == false)          
	        no_fx++;        
                                                    
    }    
    
    return(test_success);
    
} 

void Get_Sound(float x, float y) 
{   
         
      float length=0.0f;
      float x_value=0.0f, y_value=0.0f;
      float x1=0.0f, y1=0.0f;
      
      x1 = -camX;
      y1 = -camY; 
        
      if( x > x1)
          x_value = x - x1;  
      else
          x_value = x1 - x;
      
      if( y > y1) 
          y_value = y - y1;
      else
          y_value = y1 - y;           
      
      x_value += y_value; 
           
      length = x_value / 2;  
          
     // Gets from Cam position
     
      
     
}     

void UpdateMouseCursor() 
{ 
    float new_width=0.0f, new_height=0.0f;

    new_width  = hud1width;
    new_height = hud1height;
                                                                            
    hud[1].x = real_mouseX - (new_width/2);  
    hud[1].y = real_mouseY - (new_height/2);    
    hud[1].w = real_mouseX - (new_width/2);  
    hud[1].z = real_mouseY - (new_height/2); 
            
    if(hud[1].anim == 0 || hud[1].anim == 1
    || hud[1].anim == 6 || hud[1].anim == 7
    ) 
    {
        hud[1].x += (new_width/6);  
        hud[1].y -= (new_height/6);                            
    }
            
    hud[1].width  = new_width;
    hud[1].height = new_height;
            
}
    
void Set_Screen_Ratio()                                                    
{                                    
                       
    ZOOM_AMOUNT = 1.0f;                                        
    org_zoom_factor = 1.0f;  


                     
	if(sc_width > 0.0f)
		sc_ratio = (float)sc_height / (float)sc_width;  
 
    if(sc_ratio == 0.75f)        
         screen_mode = SCREEN_NORMAL;                      
             
    if(sc_ratio == 0.625f)      
         screen_mode = SCREEN_1610_WIDESCREEN;   // 16:10  
               
	if(sc_ratio >= 0.5622f && sc_ratio <= 0.5625f)        
         screen_mode = SCREEN_169_WIDESCREEN;   
         
    if(sc_width == 400 && sc_height == 240) 
         screen_mode = SCREEN_WIDESCREEN;     
    if(sc_width == 800 && sc_height == 480) 
         screen_mode = SCREEN_WIDESCREEN;           
    if(sc_width == 1280 && sc_height == 768)  
         screen_mode = SCREEN_WIDESCREEN;        

	// Hack...
	screen_mode = SCREEN_NORMAL;
                                    
    if(screen_mode == SCREEN_NORMAL)                                   
    {                         
        ZOOM_AMOUNT = 1.0f;            
        org_zoom_factor = 1.0f;                 
    }
    if(screen_mode == SCREEN_WIDESCREEN)      
    {
        ZOOM_AMOUNT = 1.2f;      
        org_zoom_factor = 1.2f;
    } 
    if(screen_mode == SCREEN_1610_WIDESCREEN)     
    {
        ZOOM_AMOUNT = 1.25f;     
        org_zoom_factor = 1.25f;   
    }     
    if(screen_mode == SCREEN_169_WIDESCREEN)   
    {
        ZOOM_AMOUNT = 1.3f;  // 1.3f
        org_zoom_factor = 1.3f;   // 1.3f
    }         
 
    zoom_factor = org_zoom_factor;    
 
}
                
      
// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& horizontal, int& vertical)
{
                              
    //RECT desktop;                
    // Get a handle to the desktop window     
    //const HWND hDesktop = GetDesktopWindow();
    // Get the size of screen to the variable desktop
    //GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)
    //horizontal = desktop.right;  
    //vertical   = desktop.bottom;
     
}     

bool Remove_FX(int id, bool test)        
{
     
	bool success=false;            

    for(int j=id;j<no_fx;j++)
	if(j >= 0 && (j+1) < TOTAL_NO_FX_SPRITES)    
    {               
                                      
        Fx[j].width = Fx[j+1].width;
        Fx[j].height = Fx[j+1].height;
        Fx[j].box_width = Fx[j+1].box_width;
        Fx[j].box_height = Fx[j+1].box_height;                  
        Fx[j].x = Fx[j+1].x;
        Fx[j].y = Fx[j+1].y;  
        Fx[j].w = Fx[j+1].w;                
        Fx[j].z = Fx[j+1].z;  
        Fx[j].mov_x = Fx[j+1].mov_x;
        Fx[j].mov_y = Fx[j+1].mov_y; 
        Fx[j].end_x = Fx[j+1].end_x;
        Fx[j].end_y = Fx[j+1].end_y; 
        Fx[j].shell_x = Fx[j+1].shell_x;
        Fx[j].shell_y = Fx[j+1].shell_y; 
        Fx[j].anim = Fx[j+1].anim;  
		Fx[j].base_anim = Fx[j+1].base_anim; 
        Fx[j].cur = Fx[j+1].cur;
        Fx[j].cur_time = Fx[j+1].cur_time;        
        Fx[j].id = Fx[j+1].id;
        Fx[j].fx_id = Fx[j+1].fx_id;      
        Fx[j].alpha = Fx[j+1].alpha;                                                  
        Fx[j].frame = Fx[j+1].frame;
        Fx[j].type = Fx[j+1].type;         
        Fx[j].anim_state = Fx[j+1].anim_state;                         
        Fx[j].priority = Fx[j+1].priority;       
        Fx[j].mouseover = Fx[j+1].mouseover;                  
        Fx[j].grab_switch = Fx[j+1].grab_switch;               
        Fx[j].linked_sprite = Fx[j+1].linked_sprite;      
        Fx[j].angle = Fx[j+1].angle;   
        Fx[j].sector = Fx[j+1].sector;     
        Fx[j].light = Fx[j+1].light;
        Fx[j].sector_action = Fx[j+1].sector_action; 
        Fx[j].tile_row = Fx[j+1].tile_row;
        Fx[j].value = Fx[j+1].value; 
        Fx[j].value1 = Fx[j+1].value1;     
        Fx[j].value2 = Fx[j+1].value2; 
        Fx[j].value3 = Fx[j+1].value3;  
        Fx[j].item_type = Fx[j+1].item_type;
        Fx[j].spin = Fx[j+1].spin;   
        Fx[j].distance = Fx[j+1].distance;                                                                                  
        Fx[j].angle2 = Fx[j+1].angle2;   
        Fx[j].action_timer = Fx[j+1].action_timer;                    
        Fx[j].turn_off = Fx[j+1].turn_off; 
        Fx[j].flash_target = Fx[j+1].flash_target;                    
        Fx[j].flash_timer = Fx[j+1].flash_timer;
        Fx[j].sparkle_timer = Fx[j+1].sparkle_timer;     
		Fx[j].on_ladder = Fx[j+1].on_ladder;  
        Fx[j].knockdown = Fx[j+1].knockdown; 
        Fx[j].knockdown_Y = Fx[j+1].knockdown_Y;  
        Fx[j].bomb_timer = Fx[j+1].bomb_timer;
        Fx[j].fire_target = Fx[j+1].fire_target;  

        Fx[j].pain = Fx[j+1].pain;
        Fx[j].knockdown = Fx[j+1].knockdown; 
        Fx[j].knockdown_Y = Fx[j+1].knockdown_Y; 
        Fx[j].new_Z = Fx[j+1].new_Z;

        Fx[j].block_type = Fx[j+1].block_type;
        Fx[j].invulnerable = Fx[j+1].invulnerable;
        Fx[j].electrocute = Fx[j+1].electrocute;
        Fx[j].handcuffed = Fx[j+1].handcuffed;
        Fx[j].walking_backwards = Fx[j+1].walking_backwards;
		Fx[j].dizzy = Fx[j+1].dizzy;
		Fx[j].sticky = Fx[j+1].sticky; 

		Fx[j].is_a_pigeon = Fx[j+1].is_a_pigeon;
		Fx[j].deflect = Fx[j+1].deflect;


    }                  
 
	// Reset the new FX...   
	Reset_FX(no_fx, false);  
                       
    no_fx--;                    
	          
	          
	return(success); 

}     
 
bool Reset_FX(int id, bool test)        
{     
   
	bool success=false;  

	if(id >= 0 && id < TOTAL_NO_FX_SPRITES)
		memset(&Fx[id], 0, sizeof(object));   

	return(success);     
   
}
  

void Run_Fx(int f_rate1)       
{             
       
	float midX=0.0f, midY=0.0f;  
	float mid_x=0.0f, tar_x=0.0f;  
	float deltax=0.0f, deltay=0.0f;
	float distance=0.0f;  
	int temp_row_x = 0;              
    int temp_row_y = 0;
	int temp_index = 0;       
	float vial_height=0.0f;
	float temp_speed = 0.0f;
	int timer_passed = 0;
          
    if(f_rate1 <= 0)
        f_rate1 = 1;

    if(f_rate1 > 100)
        f_rate1 = 100;

	// Bullets for AI...
	VG_AI_DANGER_MID =  false; 
	VG_AI_DANGER_LOW = false;
	VG_AI_OWN_BOMB = false; 

    // ******************************************************************************//
    //                              Fade FX Sprites                                  //                     
    // ******************************************************************************//
                                
    for(int i=0;i<no_fx;i++)    
	if(i >= 0 && i < TOTAL_NO_FX_SPRITES)
	if(VG_slowmof > 0.0f)
    {        
		if(Fx[i].turn_off == false)                
        if(Fx[i].sector == FX_VG_STICKYB || Fx[i].sector == FX_VG_STICKYG || Fx[i].sector == FX_VG_STICKYS) 
		if(Fx[i].value3 >= 0 && Fx[i].value3 < TOTAL_NO_SPRITES) 
        {     
			Fx[i].x = sprite[Fx[i].value3].x + 0.15f;  
			Fx[i].y = sprite[Fx[i].value3].y + 0.35f;  
			 
			if((int)TimerGetTime() > Fx[i].bomb_timer) 
			{ 

				Fx[i].value1--; 
				Fx[i].bomb_timer = (int)TimerGetTime() + 1000; 

				if(VG_finished_round == true) 
					Fx[i].value1 = -1;

				// Blow up any bombs if player dead or finished round...
				if(Fx[i].value1 < 0)    
				{ 
					Fx[i].turn_off = true;  
					 
					if(VG_finished_round == true)
					if((Fx[i].value3 == 2 && VG_1_HEALTH == 0) || (Fx[i].value3 == 3 && VG_2_HEALTH == 0) )
					{
						vg_explode_sfx = true;     
						  
						midX = sprite[Fx[i].value3].x + 0.15f; 
						midY = sprite[Fx[i].value3].y + 0.05f;  

						// Frags...
						New_FX(midX, midY,  midX, midY, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 1); 
						New_FX(midX, midY,  midX, midY, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 2); 
						New_FX(midX, midY,  midX, midY, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 3); 
						New_FX(midX, midY,  midX, midY, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 4); 

						New_FX((midX+Fx[i].width/2)-0.1f, midY+0.01f,(midX+Fx[i].width/2)-0.1f, midY+0.01f, 0, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 2, GFX, 1.0f, 0, -1, FX_STATIC, -1, 28, 0, 0, -1); 

					}

					if(VG_finished_round == false)
					{
						vg_explode_sfx = true; 

						midX = sprite[Fx[i].value3].x + 0.15f; 
						midY = sprite[Fx[i].value3].y + 0.05f;  

						// Frags...
						New_FX(midX, midY,  midX, midY, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 1); 
						New_FX(midX, midY,  midX, midY, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 2); 
						New_FX(midX, midY,  midX, midY, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 3); 
						New_FX(midX, midY,  midX, midY, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 4); 

						// Explosion...
						if(Fx[i].sector == FX_VG_STICKYB)
							New_FX((midX+Fx[i].width/2)-0.1f, midY+0.01f,(midX+Fx[i].width/2)-0.1f, midY+0.01f, 0, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 2, GFX, 1.0f, 0, -1, FX_VG_EXPLOSIONB, -1, 28, 0, 0, -1); 
						if(Fx[i].sector == FX_VG_STICKYG)
							New_FX((midX+Fx[i].width/2)-0.1f, midY+0.01f,(midX+Fx[i].width/2)-0.1f, midY+0.01f, 0, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 2, GFX, 1.0f, 0, -1, FX_VG_EXPLOSIONG, -1, 28, 0, 0, -1); 
						if(Fx[i].sector == FX_VG_STICKYS)
							New_FX((midX+Fx[i].width/2)-0.1f, midY+0.01f,(midX+Fx[i].width/2)-0.1f, midY+0.01f, 0, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 2, GFX, 1.0f, 0, -1, FX_VG_EXPLOSIONS, -1, 28, 0, 0, -1); 
					}

					if(VG_finished_round == false)   
					{

						sprite[Fx[i].value3].sticky = false;

						if(Fx[i].value3 == 2) 
							VG_2_HAS_THROW = true;
						if(Fx[i].value3 == 3)
							VG_1_HAS_THROW = true;
						 
					} 

				}

				Set_Sprite(i, 24+Fx[i].value1, LOOP, ANIM_FX, ANIM_NOT_WALKING);
			}

		}   

		// Note that box_width is used to take angle...
		if(Fx[i].turn_off == false)               
        if(Fx[i].sector == FX_VG_SWEAT || Fx[i].sector == FX_VG_SWEAT2) 
        {     
			    
			deltax = cos(Fx[i].box_width); // *1.2f   
			deltay = sin(Fx[i].box_width); // *1.2f

			if(Fx[i].sector == FX_VG_SWEAT)
				temp_speed = ((0.00060f/VG_slowmof)*(float)f_rate1);
			if(Fx[i].sector == FX_VG_SWEAT2)
				temp_speed = ((0.00090f/VG_slowmof)*(float)f_rate1);


			deltax *= temp_speed;           
			deltay *= temp_speed;     
			 
			Fx[i].x += deltax; 
			Fx[i].y += deltay;

			temp_speed = ((0.00010f/VG_slowmof)*(float)f_rate1);

			Fx[i].y -= temp_speed;
                        
			if(Fx[i].turn_off == false)                
			if(Fx[i].anim_state == WAIT)                 
				Fx[i].turn_off = true;       

		}


		if(Fx[i].turn_off == false)               
        if(Fx[i].sector == FX_VG_ATTACH) 
		if(Fx[i].value3 >= 0 && Fx[i].value3 < TOTAL_NO_SPRITES) 
        {    
			Fx[i].x = sprite[Fx[i].value3].x + 0.1f;
			Fx[i].y = sprite[Fx[i].value3].y + 0.2f;

			if(sprite[Fx[i].value3].dizzy == false || VG_finished_round == true)
				Fx[i].turn_off = true;
		}
		 
		if(Fx[i].turn_off == false)               
        if(Fx[i].sector == FX_VG_ATTACH_ACID) 
		if(Fx[i].value3 >= 0 && Fx[i].value3 < TOTAL_NO_SPRITES) 
        {    
			Fx[i].x = sprite[Fx[i].value3].x + 0.1f;  
			Fx[i].y = sprite[Fx[i].value3].y + 0.2f;  
			 
			if(sprite[Fx[i].value3].acid == false || VG_finished_round == true)
				Fx[i].turn_off = true;
		}
		 
		if(Fx[i].turn_off == false)               
        if(Fx[i].sector == FX_VG_ATTACH_HANDCUFFS) 
		if(Fx[i].value3 >= 0 && Fx[i].value3 < TOTAL_NO_SPRITES) 
        {    
			Fx[i].x = sprite[Fx[i].value3].x + 0.1f; 
			Fx[i].y = sprite[Fx[i].value3].y + 0.3f;

			Fx[i].alpha = 1.0f;

			if(VG_ROUND_CONDITIONS == CONDITION_MUST_ARREST || VG_ROUND_CONDITIONS == CONDITION_MUST_WASTE 
			|| VG_ROUND_CONDITIONS == CONDITION_THROWS_ONLY)
			if(sprite[Fx[i].value3].handcuffed == true || sprite[Fx[i].value3].dizzy == true)
				Fx[i].alpha = 0.0f;

			if(VG_finished_round == true)
				Fx[i].turn_off = true;
		}

		if(Fx[i].turn_off == false)               
        if(Fx[i].sector == FX_LEAF || Fx[i].sector == FX_LEAF1)                   
        {         
			if(VG_WIND_BLOWING != WIND_STOPPED)
			{  
				Set_Sprite(i, Fx[i].base_anim+1, LOOP, ANIM_FX, ANIM_NOT_WALKING);

				if(Fx[i].sector == FX_LEAF)
					temp_speed = ((0.00040f/VG_slowmof)*(float)f_rate1); // 00400f
				if(Fx[i].sector == FX_LEAF1)
					temp_speed = ((0.00030f/VG_slowmof)*(float)f_rate1); // 00400f

				if(VG_WIND_BLOWING == WIND_SLOW) 
					temp_speed *= 0.6f;

				Fx[i].x -= temp_speed;
				Fx[i].w -= temp_speed;  
			}
			else
				Set_Sprite(i, Fx[i].base_anim, LOOP, ANIM_FX, ANIM_NOT_WALKING);

			if(Fx[i].x < sprite[1].x)
				Fx[i].x = sprite[1].x + sprite[1].width + Fx[i].width;

		}
	  
		if(Fx[i].turn_off == false)               
        if(Fx[i].sector == FX_VG_RAINDROP)  
        {    
			if(Fx[i].anim == 0) 
			{
				temp_speed = ((0.00015f/VG_slowmof)*(float)f_rate1); // 00400f
				Fx[i].x -= temp_speed;

				temp_speed = ((0.00090f/VG_slowmof)*(float)f_rate1); // 00400f
				Fx[i].y -= temp_speed;
			}  
			  
			if(Fx[i].anim == 0)
			{
				if(Fx[i].value3 == 0)
				if(Fx[i].y < sprite[1].y + 0.01f)
					Set_Sprite(i, Fx[i].base_anim + 1, PLAY, ANIM_FX, ANIM_NOT_WALKING);
				if(Fx[i].value3 == 1)
				if(Fx[i].y < sprite[1].y + 0.05f)
					Set_Sprite(i, Fx[i].base_anim + 1, PLAY, ANIM_FX, ANIM_NOT_WALKING);
				if(Fx[i].value3 == 2)
				if(Fx[i].y < sprite[1].y + 0.10f)
					Set_Sprite(i, Fx[i].base_anim + 1, PLAY, ANIM_FX, ANIM_NOT_WALKING);
				if(Fx[i].value3 == 3)
				if(Fx[i].y < sprite[1].y + 0.12f)
					Set_Sprite(i, Fx[i].base_anim + 1, PLAY, ANIM_FX, ANIM_NOT_WALKING);
				if(Fx[i].value3 == 4)
				if(Fx[i].y < sprite[1].y + 0.18f)
					Set_Sprite(i, Fx[i].base_anim + 1, PLAY, ANIM_FX, ANIM_NOT_WALKING);

			}
		}

		 

		if(Fx[i].turn_off == false)             
        if(Fx[i].sector == FX_RUBBISH || Fx[i].sector == FX_RUBBISH1) 
		if(VG_slowmof > 0.0f)
        {        
			if(sprite[10].x <= sprite[1].x + sprite[1].width/2)
			if((sprite[11].x+sprite[11].width) >= sprite[1].x) 
			{
				Set_Sprite(i, Fx[i].base_anim+1, LOOP, ANIM_FX, ANIM_NOT_WALKING);

				if(Fx[i].sector == FX_RUBBISH)
					temp_speed = ((0.00040f/VG_slowmof)*(float)f_rate1); // 00400f
				if(Fx[i].sector == FX_RUBBISH1)
					temp_speed = ((0.00030f/VG_slowmof)*(float)f_rate1); // 00400f


				Fx[i].x -= temp_speed;
				Fx[i].w -= temp_speed;  
			}
			else
				Set_Sprite(i, Fx[i].base_anim, LOOP, ANIM_FX, ANIM_NOT_WALKING);

			if(Fx[i].x < sprite[1].x)
				Fx[i].x = sprite[1].x + sprite[1].width + Fx[i].width;

		}

		if(Fx[i].turn_off == false)           
        if(Fx[i].sector == FX_VG_CASING || Fx[i].sector == FX_VG_MONEY)
		if(VG_slowmof > 0.0f)
        {                            
       
			if(Fx[i].value3 == -1 || Fx[i].value3 == 5 || Fx[i].value3 == 6 || Fx[i].value3 == 7)
	        if(Fx[i].value == RIGHT)  
	        {
				if(Fx[i].value3 == 5) 
    	            temp_speed = ((0.00030f/VG_slowmof)*(float)f_rate1); 
				if(Fx[i].value3 == 6)       
    	            temp_speed = ((0.00035f/VG_slowmof)*(float)f_rate1);
				if(Fx[i].value3 == 7)       
    	            temp_speed = ((0.00040f/VG_slowmof)*(float)f_rate1);

				if(Fx[i].value2 == 1) 
					temp_speed = temp_speed * 0.1f; 
				else
				{
					if(Fx[i].spin == 3.14f)
						temp_speed = temp_speed * 0.6f;
				}
				 
				Fx[i].x -= temp_speed; 
			}     
	        else                        
	        {   
				if(Fx[i].value3 == 5) 
    	            temp_speed = ((0.00030f/VG_slowmof)*(float)f_rate1); 
				if(Fx[i].value3 == 6)       
    	            temp_speed = ((0.00035f/VG_slowmof)*(float)f_rate1);
				if(Fx[i].value3 == 7)       
    	            temp_speed = ((0.00040f/VG_slowmof)*(float)f_rate1);

				if(Fx[i].value2 == 1)
					temp_speed = temp_speed * 0.1f;
				else
				{
					if(Fx[i].spin == 3.14f)
						temp_speed = temp_speed * 0.6f;
				}

				Fx[i].x += temp_speed;
			}
			 
			if(Fx[i].value3 == 1)
			{
				temp_speed = ((0.0004f/VG_slowmof)*(float)f_rate1);
				if(Fx[i].value2 == 1)
					temp_speed = temp_speed * 0.1f;
				Fx[i].x += temp_speed;
			}
			if(Fx[i].value3 == 2)
			{
				temp_speed = ((0.0005f/VG_slowmof)*(float)f_rate1);
				if(Fx[i].value2 == 1)
					temp_speed = temp_speed * 0.1f;
				Fx[i].x += temp_speed;
			}
			if(Fx[i].value3 == 3)
			{
				temp_speed = ((0.00045f/VG_slowmof)*(float)f_rate1);
				if(Fx[i].value2 == 1)
					temp_speed = temp_speed * 0.1f;
				Fx[i].x -= temp_speed;
			} 
			if(Fx[i].value3 == 4) 
			{
				temp_speed = ((0.00055f/VG_slowmof)*(float)f_rate1);
				if(Fx[i].value2 == 1)
					temp_speed = temp_speed * 0.1f;
	            Fx[i].x -= temp_speed;
			}             
			 
	        if(Fx[i].value3 == -1 || Fx[i].value3 == 5 || Fx[i].value3 == 6 || Fx[i].value3 == 7)
				Fx[i].y += cos(Fx[i].spin)*((0.0010f/VG_slowmof)*(float)f_rate1);
			else
				Fx[i].y += cos(Fx[i].spin)*((0.0006f/VG_slowmof)*(float)f_rate1);
	                      
			if(Fx[i].value3 == -1 || Fx[i].value3 == 5 || Fx[i].value3 == 6 || Fx[i].value3 == 7)
				Fx[i].spin += (0.025f/VG_slowmof)*(float)f_rate1; 

			if(Fx[i].value3 == 1) 
				Fx[i].spin += (0.015f/VG_slowmof)*(float)f_rate1;  
			if(Fx[i].value3 == 2)
				Fx[i].spin += (0.009f/VG_slowmof)*(float)f_rate1; 
			if(Fx[i].value3 == 3)
				Fx[i].spin += (0.012f/VG_slowmof)*(float)f_rate1; 
			if(Fx[i].value3 == 4)
				Fx[i].spin += (0.005f/VG_slowmof)*(float)f_rate1; 
	                              
	        if(Fx[i].spin > 3.14f)              
	            Fx[i].spin = 3.14f;    
	           
			if(Fx[i].sector == FX_VG_CASING)
			if(Fx[i].value2 == 1) 
				Fx[i].angle += (1.0f/VG_slowmof)*(float)f_rate1; 
			else
				Fx[i].angle += (2.0f/VG_slowmof)*(float)f_rate1; 

			if(Fx[i].y < sprite[Fx[i].linked_sprite].y - Fx[i].height/4 )
			{
				Fx[i].y = (sprite[Fx[i].linked_sprite].y - Fx[i].height/4 );
				Fx[i].value2 = 1;
				if(Fx[i].bomb_timer == -1)
					Fx[i].bomb_timer = (int)TimerGetTime() + 500;
			}

			if(Fx[i].bomb_timer != -1)
			if((int)TimerGetTime() > Fx[i].bomb_timer)
			{
	            Fx[i].alpha = 0.0f;			
				Fx[i].turn_off = true;   
			}
                                     
        } 		
	    if(Fx[i].sector == FX_VG_BOMB)           
		if(VG_slowmof > 0.0f)
        {        
			mid_x = Fx[i].x + Fx[i].width/2;   
			tar_x = sprite[3].x + sprite[3].width/2;  

			distance = Node_Distance1(mid_x, VG_START_Y, tar_x, VG_START_Y);

			if(distance < 0.2f) 
			{
				if(Fx[i].sector == FX_VG_BOMB)
					VG_AI_DANGER_LOW = true;

				if(Fx[i].sector == FX_VG_BOMB && Fx[i].value3 == 2)
				    VG_AI_OWN_BOMB = true; 
			}

			if(Fx[i].y > (sprite[5].y - Fx[i].height/5) )
			{
			    temp_speed = (0.00100f/VG_slowmof)*(float)f_rate1; 
				Fx[i].y -= temp_speed;   
				Fx[i].z -= temp_speed;
			}
			else
			{
				Fx[i].y = (sprite[5].y - Fx[i].height/5);
			}

			if(Fx[i].anim_state == NO_ANIM) 
			{
				Fx[i].turn_off = true;
				vg_explode_sfx = true; 
				// Frags...
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 1); 
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 2); 
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 3); 
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 4); 
				// Explosion...
				New_FX((Fx[i].x+Fx[i].width/2)-0.1f, Fx[i].y+0.01f,(Fx[i].x+Fx[i].width/2)-0.1f, Fx[i].y+0.01f, 0, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 2, GFX, 1.0f, 0, -1, FX_VG_EXPLOSION, -1, 28, 0, 0, -1); 
			}

		}

	    if(Fx[i].sector == FX_VG_GRENADE)         
        {   


			mid_x = Fx[i].x + Fx[i].width/2;   
			tar_x = sprite[3].x + sprite[3].width/2;  

			distance = Node_Distance1(mid_x, VG_START_Y, tar_x, VG_START_Y);

			if(distance < 0.2f) 
			{
				if(Fx[i].sector == FX_VG_GRENADE)
					VG_AI_DANGER_LOW = true;

				if(Fx[i].sector == FX_VG_GRENADE && Fx[i].value3 == 2)
				    VG_AI_OWN_BOMB = true; 
			}

			if(Fx[i].anim == 6) // RIGHT  
			if(Fx[i].grab_switch == true) 
			if(Fx[i].x > Fx[i].shell_x + 0.38f) 
			{ 
				Fx[i].bump_this = true; 
				Fx[i].bump_this_timer = (int)TimerGetTime() + 150; 
				Fx[i].grab_switch = false;
				Fx[i].bomb_timer = (int)TimerGetTime() + 500;  
			}
			if(Fx[i].anim == 7) // LEFT 
			if(Fx[i].grab_switch == true)
			if(Fx[i].x < Fx[i].shell_x - 0.38f)    
			{
				Fx[i].bump_this = true; 
				Fx[i].bump_this_timer = (int)TimerGetTime() + 150; 
				Fx[i].grab_switch = false; 
				Fx[i].bomb_timer = (int)TimerGetTime() + 500;
			}  
			    
			if(Fx[i].grab_switch == false)  
			if((int)TimerGetTime() > Fx[i].bomb_timer) 
			{
				Fx[i].turn_off = true;
				vg_explode_sfx = true; 
				// Frags...
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 1); 
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 2); 
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 3); 
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 4); 
				// Explosion...
				New_FX((Fx[i].x+Fx[i].width/2)-0.1f, Fx[i].y+0.01f,(Fx[i].x+Fx[i].width/2)-0.1f, Fx[i].y+0.01f, 0, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 2, GFX, 1.0f, 0, -1, FX_VG_EXPLOSION, -1, 28, 0, 0, -1); 
			}
 			 
			if(Fx[i].grab_switch == true)  
			if(VG_slowmof > 0.0f)
			{ 

				// Trails for vials...
				if(Fx[i].anim == 6 || Fx[i].anim == 7)
				if((int)TimerGetTime() > Fx[i].all_timer)
				{
					Fx[i].all_timer = (int)TimerGetTime() + 75;

					if(Fx[i].anim == 6) // RIGHT 
						New_FX(Fx[i].x, Fx[i].y, Fx[i].x, Fx[i].y, 42, PLAY, Fx[i].width,Fx[i].height, Fx[i].width,Fx[i].height, 3, GFX, 1.0f, 0, -1, FX_VG_TRAIL, i, Fx[i].id, 0, 0, i);
					else
						New_FX(Fx[i].x, Fx[i].y, Fx[i].x, Fx[i].y, 42, PLAY, Fx[i].width,Fx[i].height, Fx[i].width,Fx[i].height, 3, GFX, 1.0f, 0, -1, FX_VG_TRAIL, i, Fx[i].id, 0, 0, i);

				}

				if(Fx[i].anim == 6) // RIGHT        
				{ 
					if(Fx[i].y > sprite[5].y)
						temp_speed = ((0.00125f/VG_slowmof)*(float)f_rate1); // 00400f
					else
						temp_speed = ((0.00020f/VG_slowmof)*(float)f_rate1); // 00400f

					Fx[i].x += temp_speed; 
					Fx[i].w += temp_speed;  

					Fx[i].angle += ((1.5f/VG_slowmof)*(float)f_rate1);
				} 

				if(Fx[i].anim == 7) // LEFT
				{ 
					if(Fx[i].y > sprite[5].y)
						temp_speed = ((0.00125f/VG_slowmof)*(float)f_rate1);  // 00400f
					else
						temp_speed = ((0.00020f/VG_slowmof)*(float)f_rate1);  // 00400f

					Fx[i].x -= temp_speed;
					Fx[i].w -= temp_speed;  

					Fx[i].angle -= ((1.5f/VG_slowmof)*(float)f_rate1);
				}    

				vial_height = VG_GRENADE_HEIGHT;   

				temp_speed = (0.0020f/VG_slowmof)*(float)f_rate1;   
			  
				if(Fx[i].y > sprite[5].y + (vial_height*0.4f))  
					 temp_speed = (0.00150f/VG_slowmof)*(float)f_rate1; 

				if(Fx[i].y > sprite[5].y + (vial_height*0.6f))
					 temp_speed = (0.00100f/VG_slowmof)*(float)f_rate1; 

				if(Fx[i].y > sprite[5].y + (vial_height*0.75f))
					 temp_speed = (0.00050f/VG_slowmof)*(float)f_rate1; 

				if(Fx[i].y > sprite[5].y + (vial_height*0.9f)) 
					 temp_speed = (0.00025f/VG_slowmof)*(float)f_rate1; 

				if(Fx[i].y > sprite[5].y + vial_height)
					Fx[i].knockdown = true;     

				if(Fx[i].y > sprite[5].y)
				if(Fx[i].knockdown == true)
				{
					Fx[i].y -= temp_speed;  
					Fx[i].z -= temp_speed;
				}
				else
				{
					Fx[i].y += temp_speed;  
					Fx[i].z += temp_speed; 
				}

				// Vial hit the deck...
				if(Fx[i].y <= sprite[5].y)  
				{

					Fx[i].y = sprite[5].y;
					Fx[i].z = sprite[5].y;
				}

			}

			if(Fx[i].x >= sprite[1].x + sprite[1].width)
				Fx[i].turn_off = true;
			if((Fx[i].x + Fx[i].width) <= sprite[1].x)
				Fx[i].turn_off = true;
			 
        }      
	    if(Fx[i].sector == FX_VG_BOMBSAIZO)         
        {   


			mid_x = Fx[i].x + Fx[i].width/2;   
			tar_x = sprite[3].x + sprite[3].width/2;  

			distance = Node_Distance1(mid_x, VG_START_Y, tar_x, VG_START_Y);

			if(distance < 0.2f) 
			{
				if(Fx[i].sector == FX_VG_BOMBSAIZO)
					VG_AI_DANGER_LOW = true;

				if(Fx[i].sector == FX_VG_BOMBSAIZO && Fx[i].value3 == 2)
				    VG_AI_OWN_BOMB = true; 
			}

			if(Fx[i].anim == 55) // RIGHT  
			if(Fx[i].grab_switch == true) 
			if(Fx[i].x > Fx[i].shell_x + 0.20f) 
			{ 
				Fx[i].bump_this = true; 
				Fx[i].bump_this_timer = (int)TimerGetTime() + 150; 
				Fx[i].grab_switch = false;
				Fx[i].bomb_timer = 0;  
			}
			if(Fx[i].anim == 54) // LEFT 
			if(Fx[i].grab_switch == true)
			if(Fx[i].x < Fx[i].shell_x - 0.20f)    
			{
				Fx[i].bump_this = true; 
				Fx[i].bump_this_timer = (int)TimerGetTime() + 150; 
				Fx[i].grab_switch = false; 
				Fx[i].bomb_timer = 0;
			}  
			    
			if(Fx[i].grab_switch == false)  
			if((int)TimerGetTime() > Fx[i].bomb_timer) 
			{
				Fx[i].turn_off = true;
				vg_explode_sfx = true; 
				// Frags...
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 1); 
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 2); 
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 3); 
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 9, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 4); 
				// Explosion...
				New_FX((Fx[i].x+Fx[i].width/2)-0.1f, Fx[i].y+0.01f,(Fx[i].x+Fx[i].width/2)-0.1f, Fx[i].y+0.01f, 0, PLAY, 0.2f, 0.2f, 0.2f, 0.2f, 2, GFX, 1.0f, 0, -1, FX_VG_EXPLOSIONSAIZO, -1, 28, 0, 0, -1); 
			}
 			 
			if(Fx[i].grab_switch == true)  
			if(VG_slowmof > 0.0f)
			{ 

				// Trails for vials...
				if(Fx[i].anim == 54 || Fx[i].anim == 55)
				if((int)TimerGetTime() > Fx[i].all_timer)
				{
					Fx[i].all_timer = (int)TimerGetTime() + 75;

					if(Fx[i].anim == 55) // RIGHT 
						New_FX(Fx[i].x, Fx[i].y, Fx[i].x, Fx[i].y, 42, PLAY, Fx[i].width,Fx[i].height, Fx[i].width,Fx[i].height, 3, GFX, 1.0f, 0, -1, FX_VG_TRAIL, i, Fx[i].id, 0, 0, i);
					else
						New_FX(Fx[i].x, Fx[i].y, Fx[i].x, Fx[i].y, 42, PLAY, Fx[i].width,Fx[i].height, Fx[i].width,Fx[i].height, 3, GFX, 1.0f, 0, -1, FX_VG_TRAIL, i, Fx[i].id, 0, 0, i);

				}

				if(Fx[i].anim == 55) // RIGHT        
				{ 
					if(Fx[i].y > sprite[5].y)
						temp_speed = ((0.00125f/VG_slowmof)*(float)f_rate1); // 00400f
					else
						temp_speed = ((0.00020f/VG_slowmof)*(float)f_rate1); // 00400f

					Fx[i].x += temp_speed; 
					Fx[i].w += temp_speed;  

					Fx[i].angle += ((1.5f/VG_slowmof)*(float)f_rate1);
				} 

				if(Fx[i].anim == 54) // LEFT
				{ 
					if(Fx[i].y > sprite[5].y)
						temp_speed = ((0.00125f/VG_slowmof)*(float)f_rate1);  // 00400f
					else
						temp_speed = ((0.00020f/VG_slowmof)*(float)f_rate1);  // 00400f

					Fx[i].x -= temp_speed;
					Fx[i].w -= temp_speed;  

					Fx[i].angle -= ((1.5f/VG_slowmof)*(float)f_rate1);
				}    

				vial_height = VG_GRENADE_HEIGHT;   

				temp_speed = (0.0020f/VG_slowmof)*(float)f_rate1;   
			  
				if(Fx[i].y > sprite[5].y + (vial_height*0.4f))  
					 temp_speed = (0.00200f/VG_slowmof)*(float)f_rate1; 

				if(Fx[i].y > sprite[5].y + (vial_height*0.6f))
					 temp_speed = (0.00150f/VG_slowmof)*(float)f_rate1; 

				if(Fx[i].y > sprite[5].y + (vial_height*0.75f))
					 temp_speed = (0.00075f/VG_slowmof)*(float)f_rate1; 

				if(Fx[i].y > sprite[5].y + (vial_height*0.9f)) 
					 temp_speed = (0.00050f/VG_slowmof)*(float)f_rate1; 

				if(Fx[i].y > sprite[5].y + vial_height)
					Fx[i].knockdown = true;     

				if(Fx[i].y > sprite[5].y)
				if(Fx[i].knockdown == true)
				{
					Fx[i].y -= temp_speed;  
					Fx[i].z -= temp_speed;
				}
				else
				{
					Fx[i].y += temp_speed;  
					Fx[i].z += temp_speed; 
				}

				// Vial hit the deck...
				if(Fx[i].y <= sprite[5].y)  
				{

					Fx[i].y = sprite[5].y;
					Fx[i].z = sprite[5].y;
				}

			}

			if(Fx[i].x >= sprite[1].x + sprite[1].width)
				Fx[i].turn_off = true;
			if((Fx[i].x + Fx[i].width) <= sprite[1].x)
				Fx[i].turn_off = true;
			 
        }      
	    if(Fx[i].sector == FX_VG_KNIFE)  
		if(VG_slowmof > 0.0f)
        {           
			if(Fx[i].anim == 21) // RIGHT    
			{ 
				temp_speed = ((0.00150f/VG_slowmof)*(float)f_rate1); // 00400f
				Fx[i].x += temp_speed; 
				Fx[i].w += temp_speed;  

				Fx[i].angle += ((3.5f/VG_slowmof)*(float)f_rate1);
			}      
			if(Fx[i].anim == 22) // LEFT 
			{  
				temp_speed = ((0.00150f/VG_slowmof)*(float)f_rate1);  // 00400f
				Fx[i].x -= temp_speed;
				Fx[i].w -= temp_speed;  

				Fx[i].angle -= ((3.5f/VG_slowmof)*(float)f_rate1);
			}    
			 
			vial_height = VG_KNIFE_HEIGHT;   

	        temp_speed = (0.0020f/VG_slowmof)*(float)f_rate1;   
			  
			if(Fx[i].y > sprite[5].y + (vial_height*0.4f))  
			     temp_speed = (0.00150f/VG_slowmof)*(float)f_rate1; 

			if(Fx[i].y > sprite[5].y + (vial_height*0.6f))
			     temp_speed = (0.00100f/VG_slowmof)*(float)f_rate1; 

			if(Fx[i].y > sprite[5].y + (vial_height*0.75f))
			     temp_speed = (0.00050f/VG_slowmof)*(float)f_rate1; 

			if(Fx[i].y > sprite[5].y + (vial_height*0.9f)) 
			     temp_speed = (0.00025f/VG_slowmof)*(float)f_rate1; 

			if(Fx[i].y > sprite[5].y + vial_height)
			    Fx[i].knockdown = true;     

			if(Fx[i].knockdown == true) 
			{
				Fx[i].y -= temp_speed;   
				Fx[i].z -= temp_speed;
			}
			else
			{
				Fx[i].y += temp_speed;   
				Fx[i].z += temp_speed; 
			} 

			// Vial hit the deck...   
			if(Fx[i].y <= sprite[5].y) 
			{
			//	glass_sfx = true;
				 
				Fx[i].turn_off = true;
				Fx[i].grab_switch = true;
			}

			if(Fx[i].x >= sprite[1].x + sprite[1].width)
				Fx[i].turn_off = true; 
			if((Fx[i].x + Fx[i].width) <= sprite[1].x)
				Fx[i].turn_off = true;
			 
        }

	    if(Fx[i].sector == FX_VG_VIAL || Fx[i].sector == FX_VG_VIAL_LOW)       
		if(VG_slowmof > 0.0f)
        {           
			mid_x = Fx[i].x + Fx[i].width/2;   
			tar_x = sprite[3].x + sprite[3].width/2;   

			distance = Node_Distance1(mid_x, VG_START_Y, tar_x, VG_START_Y);

			if(distance < 0.2f) 
			{
				if(Fx[i].sector == FX_VG_VIAL)
					VG_AI_DANGER_MID = true;
				if(Fx[i].sector == FX_VG_VIAL_LOW)
					VG_AI_DANGER_LOW = true;
			}

			// Trails for vials...
			if((int)TimerGetTime() > Fx[i].all_timer)
			{
				Fx[i].all_timer = (int)TimerGetTime() + 75;

				if(Fx[i].anim == 4) // RIGHT 
					New_FX(Fx[i].x, Fx[i].y, Fx[i].x, Fx[i].y, 40, PLAY, Fx[i].width,Fx[i].height, Fx[i].width,Fx[i].height, 3, GFX, 1.0f, 0, -1, FX_VG_TRAIL, i, Fx[i].id, 0, 0, i);
				else
					New_FX(Fx[i].x, Fx[i].y, Fx[i].x, Fx[i].y, 41, PLAY, Fx[i].width,Fx[i].height, Fx[i].width,Fx[i].height, 3, GFX, 1.0f, 0, -1, FX_VG_TRAIL, i, Fx[i].id, 0, 0, i);

			}

			if(Fx[i].anim == 4) // RIGHT     
			{ 
				if(Fx[i].sector == FX_VG_VIAL)
					temp_speed = ((0.00075f/VG_slowmof)*(float)f_rate1); // 00400f
				else
					temp_speed = ((0.00150f/VG_slowmof)*(float)f_rate1); // 00400f

				Fx[i].x += temp_speed;
				Fx[i].w += temp_speed;   

				Fx[i].angle += ((1.5f/VG_slowmof)*(float)f_rate1);
			} 
			if(Fx[i].anim == 5) // LEFT
			{ 
				if(Fx[i].sector == FX_VG_VIAL)
					temp_speed = ((0.00075f/VG_slowmof)*(float)f_rate1); // 00400f
				else
					temp_speed = ((0.00150f/VG_slowmof)*(float)f_rate1); // 00400f

				Fx[i].x -= temp_speed;
				Fx[i].w -= temp_speed;  

				Fx[i].angle -= ((1.5f/VG_slowmof)*(float)f_rate1);
			}    
			 
			if(Fx[i].sector == FX_VG_VIAL)  
				vial_height = VG_VIAL_HEIGHT;   
			if(Fx[i].sector == FX_VG_VIAL_LOW)  
				vial_height = VG_VIAL_LOW_HEIGHT;

			if(Fx[i].sector == FX_VG_KNIFE)  
				vial_height = VG_VIAL_HEIGHT;   

	        temp_speed = (0.0020f/VG_slowmof)*(float)f_rate1;   
			  
			if(Fx[i].y > sprite[5].y + (vial_height*0.4f))  
			     temp_speed = (0.00150f/VG_slowmof)*(float)f_rate1; 

			if(Fx[i].y > sprite[5].y + (vial_height*0.6f))
			     temp_speed = (0.00100f/VG_slowmof)*(float)f_rate1; 

			if(Fx[i].y > sprite[5].y + (vial_height*0.75f))
			     temp_speed = (0.00050f/VG_slowmof)*(float)f_rate1; 

			if(Fx[i].y > sprite[5].y + (vial_height*0.9f)) 
			     temp_speed = (0.00025f/VG_slowmof)*(float)f_rate1; 

			if(Fx[i].y > sprite[5].y + vial_height)
			    Fx[i].knockdown = true;     

			if(Fx[i].knockdown == true) 
			{
				Fx[i].y -= temp_speed;   
				Fx[i].z -= temp_speed;
			}
			else
			{
				Fx[i].y += temp_speed;  
				Fx[i].z += temp_speed;  
			}

			// Vial hit the deck... 
			if(Fx[i].y <= sprite[5].y)
			{
				vg_glass_sfx = true;
						 
				// Shards...
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 10, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 1); 
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 11, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 2); 
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 10, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 3); 
				New_FX(Fx[i].x, Fx[i].y,  Fx[i].x, Fx[i].y, 11, LOOP, 0.1f, 0.1f, 0.1f, 0.1f, 1, GFX, 1.0f, 0, 5, FX_VG_CASING, 5, 12, 0, 0, 4); 

				Fx[i].turn_off = true;
				Fx[i].grab_switch = true;  
			}

			if(Fx[i].x >= sprite[1].x + sprite[1].width)
				Fx[i].turn_off = true;
			if((Fx[i].x + Fx[i].width) <= sprite[1].x) 
				Fx[i].turn_off = true;

        }  

		if(Fx[i].sector == FX_ARM)
		if(Fx[i].value3 >= 0 && Fx[i].value3 < TOTAL_NO_SPRITES)
		{
			Fx[i].deflect = sprite[Fx[i].value3].deflect;
		}

        if(Fx[i].sector == FX_VG_BULLET || Fx[i].sector == FX_VG_BULLET_LOW || Fx[i].sector == FX_VG_ORB || Fx[i].sector == FX_VG_FIREBALL || Fx[i].sector == FX_VG_KUNAI)   
		if(VG_slowmof > 0.0f)
        {           

			mid_x = Fx[i].x + Fx[i].width/2;   
			tar_x = sprite[3].x + sprite[3].width/2;  

			distance = Node_Distance1(mid_x, VG_START_Y, tar_x, VG_START_Y);

			if(distance < 0.4f) 
			{
				if(Fx[i].sector == FX_VG_BULLET) //  || Fx[i].sector == FX_VG_ORB
					VG_AI_DANGER_MID = true;
				if(Fx[i].sector == FX_VG_BULLET_LOW)
					VG_AI_DANGER_LOW = true;

			}
			if(distance < 0.3f)
			if(Fx[i].sector == FX_VG_ORB || Fx[i].sector == FX_VG_FIREBALL || Fx[i].sector == FX_VG_KUNAI) 
				VG_AI_DANGER_MID = true;

			if(Fx[i].sector != FX_VG_ORB && Fx[i].sector != FX_VG_FIREBALL && Fx[i].sector != FX_VG_KUNAI)
			if(Fx[i].anim == 2) // RIGHT    
			{ 
				if(Fx[i].sector == FX_VG_BULLET)
					temp_speed = ((0.00150f/VG_slowmof)*(float)f_rate1); // 00400f
				if(Fx[i].sector == FX_VG_BULLET_LOW)
					temp_speed = ((0.00100f/VG_slowmof)*(float)f_rate1); // 00400f

				Fx[i].x += temp_speed; 
				Fx[i].w += temp_speed;                                                                 
			}  
			if(Fx[i].sector != FX_VG_ORB && Fx[i].sector != FX_VG_FIREBALL && Fx[i].sector != FX_VG_KUNAI)
			if(Fx[i].anim == 3) // LEFT 
			{
				if(Fx[i].sector == FX_VG_BULLET)
					temp_speed = ((0.00150f/VG_slowmof)*(float)f_rate1); // 00400f
				if(Fx[i].sector == FX_VG_BULLET_LOW)
					temp_speed = ((0.00100f/VG_slowmof)*(float)f_rate1); // 00400f

				Fx[i].x -= temp_speed;
				Fx[i].w -= temp_speed;    
			}   
			if(Fx[i].sector == FX_VG_ORB)
			if(Fx[i].value3 == RIGHT) // RIGHT    
			{ 
				if(Fx[i].sector == FX_VG_ORB)
					temp_speed = ((0.00050f/VG_slowmof)*(float)f_rate1); // 00400f
				 
				Fx[i].x += temp_speed; 
				Fx[i].w += temp_speed;                                                                  
			}  
			if(Fx[i].sector == FX_VG_ORB)
			if(Fx[i].value3 == LEFT) // LEFT
			{
				if(Fx[i].sector == FX_VG_ORB)
					temp_speed = ((0.00050f/VG_slowmof)*(float)f_rate1); // 00400f

				Fx[i].x -= temp_speed;
				Fx[i].w -= temp_speed;    
			}   

			if(Fx[i].sector == FX_VG_FIREBALL)
			if(Fx[i].value3 == RIGHT) // RIGHT    
			{ 
				if(Fx[i].sector == FX_VG_FIREBALL)
					temp_speed = ((0.00075f/VG_slowmof)*(float)f_rate1); // 00400f
				 
				Fx[i].x += temp_speed; 
				Fx[i].w += temp_speed;                                                                  
			}  
			if(Fx[i].sector == FX_VG_FIREBALL)
			if(Fx[i].value3 == LEFT) // LEFT
			{
				if(Fx[i].sector == FX_VG_FIREBALL)
					temp_speed = ((0.00075f/VG_slowmof)*(float)f_rate1); // 00400f

				Fx[i].x -= temp_speed;
				Fx[i].w -= temp_speed;    
			}  

			if(Fx[i].sector == FX_VG_KUNAI)
			if(Fx[i].value3 == RIGHT) // RIGHT    
			{ 
				if(Fx[i].sector == FX_VG_KUNAI)
					temp_speed = ((0.00150f/VG_slowmof)*(float)f_rate1); // 00400f
				 
				Fx[i].x += temp_speed; 
				Fx[i].w += temp_speed;                                                                  
			}  
			if(Fx[i].sector == FX_VG_KUNAI)
			if(Fx[i].value3 == LEFT) // LEFT
			{
				if(Fx[i].sector == FX_VG_KUNAI)
					temp_speed = ((0.00150f/VG_slowmof)*(float)f_rate1); // 00400f

				Fx[i].x -= temp_speed;
				Fx[i].w -= temp_speed;    
			}  

			if(Fx[i].sector == FX_VG_ORB || Fx[i].sector == FX_VG_FIREBALL)
			{
				if(Fx[i].sector == FX_VG_ORB)
				if((int)TimerGetTime() > (Fx[i].bomb_timer - 2000) )
					Set_Sprite(i, 50, LOOP, ANIM_FX, ANIM_NOT_WALKING);

				if((int)TimerGetTime() > Fx[i].bomb_timer)
					Fx[i].turn_off = true;
			}
			 
			if(Fx[i].x >= sprite[1].x + sprite[1].width)
				Fx[i].turn_off = true;
			if((Fx[i].x + Fx[i].width) <= sprite[1].x)
				Fx[i].turn_off = true;

        }    

        if(Fx[i].sector == FX_PUNCH_POINT)     
		if(Fx[i].linked_sprite >= 0)   
        {      
			if(Fx[i].linked_sprite == 2)      
			{  
				Fx[i].x = points[0].x-0.025f;           
				Fx[i].y = points[0].y-0.025f;                                                                 
			} 
			if(Fx[i].linked_sprite == 3)        
			{
				Fx[i].x = points[1].x-0.025f;     
				Fx[i].y = points[1].y-0.025f;  
			}   
        }      
         
		if(Fx[i].sector != FX_VG_ATTACH_HANDCUFFS) 
		if(Fx[i].turn_off == false)   
        if(Fx[i].alpha <= 0.0f)                                               
            Fx[i].turn_off = true;                                   
                        
		if(Fx[i].turn_off == false)                
        if(Fx[i].anim_state == WAIT)                 
            Fx[i].turn_off = true;            

    }  

    for(int i=0;i<no_fx;i++)    
	{
        if(Fx[i].turn_off == true) 
        {   
            Remove_FX(i, false); 
		}
	}




}

/*void GetParameters(LPSTR lpCmdLine)
{
	int length=0; 
	int j=0;
	bool reading=false;       
	sString itemp_string;    
	                 
	// Grab the parameters here...  
	length=strlen(lpCmdLine);     

	memset( params_prog, 0, sizeof(sString)*NO_PARAMS_PROG );

	if(length > 0)   
	for(int i=0;i<length;i++)          
	{        
		if(lpCmdLine[i] != ' ')       
		{   

			if(j<16)
			if(no_of_params < 10)
				params_prog[no_of_params].string[j] = lpCmdLine[i];

			if(j<16) 
				j++;

			if(i==length-1) 
			if(no_of_params < 10)    
				no_of_params++;

			reading=true;
		}
		if(lpCmdLine[i] == ' ') 
		{ 
			j=0;  
			 
			if(reading == true) 
			if(no_of_params < 10)
			{
				no_of_params++;
			}

			reading=false;
		}   
		  
	} 
	  
	for(int i=0;i<no_of_params;i++)      
	{   

		if(strlen(params_prog[i].string) > 0) 
		{ 

			sprintf(itemp_string.string, "-windowed");
			if( strcmp( params_prog[i].string, itemp_string.string ) == 0)
				fullscreen=false;

			sprintf(itemp_string.string, "-fullscreen");
			if( strcmp( params_prog[i].string, itemp_string.string ) == 0)
				fullscreen=true;

			sprintf(itemp_string.string, "-opengl");
			if( strcmp( params_prog[i].string, itemp_string.string ) == 0)
				RENDERER=RENDER_OPENGL;

			sprintf(itemp_string.string, "-directx");
			if( strcmp( params_prog[i].string, itemp_string.string ) == 0)
				RENDERER=RENDER_DIRECTX;

		} 
		 
	}


}*/




