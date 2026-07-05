#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

//#include <windows.h>
#ifdef SWITCH
#include <egl/egl.h>
#include <glad/glad.h>
#endif
#include <string.h>    
#include "globals.h" 

#define MOUSE_CURSOR_ACTIVE  0   

extern void Set_Screen_Ratio();

extern bool LoadScene( int episode1, int scene1, bool delete_textures );
extern bool LoadCFG();

void ZoomDX(int type)		// Resize And Initialize The GL Window
{
	#if IS_USING_DIRECTX == 1  
	    
		if(RENDERER == RENDER_DIRECTX)            
	//	if(type == TYPE_MODE_NORM)            
		{    
			//printf("SCREEN MODE : %d maths : %f %f\n", screen_mode, org_zoom_scroll_display,sc_ratio);
			if (screen_mode == SCREEN_NORMAL) // 4:3
				D3DXMatrixOrthoLH(&matProjection, 1.10f + org_zoom_scroll_display, 0.8f + (org_zoom_scroll_display*sc_ratio), -(20.0f), 2.0f); // Only needs to be called once.

			if (screen_mode == SCREEN_1610_WIDESCREEN) // 8:5
				D3DXMatrixOrthoLH(&matProjection, 1.39f + org_zoom_scroll_display, 0.79f + (org_zoom_scroll_display*sc_ratio), -(20.0f), 2.0f); // Only needs to be called once.

			if (screen_mode == SCREEN_169_WIDESCREEN) // 16:9
				D3DXMatrixOrthoLH(&matProjection, 1.49f + org_zoom_scroll_display, 0.787f + (org_zoom_scroll_display*sc_ratio), -(20.0f), 2.0f); // Only needs to be called once.

			//D3DXMatrixIdentity(&matProjection);
			D3DXSetTransform(&D3DTS_PROJECTION, &matProjection);

		}   

		if(RENDERER == RENDER_DIRECTX)
		if(type == TYPE_MODE_TEXT_DEBUG)  
		{ 
			if (screen_mode == SCREEN_NORMAL) // 4:3
				D3DXMatrixOrthoLH(&matProjection, 2.0f, 2.0f, -100.0f, 100.0f); // Only needs to be called once.

			if (screen_mode == SCREEN_WIDESCREEN) // 5:3
				D3DXMatrixOrthoLH(&matProjection, 2.0f, 2.0f, -100.0f, 100.0f); // Only needs to be called once.

			if (screen_mode == SCREEN_1610_WIDESCREEN) // 8:5
				D3DXMatrixOrthoLH(&matProjection, 2.0f, 2.0f, -100.0f, 100.0f); // Only needs to be called once.

			if (screen_mode == SCREEN_169_WIDESCREEN) // 16:9
				D3DXMatrixOrthoLH(&matProjection, 2.0f, 2.0f, -100.0f, 100.0f); // Only needs to be called once.

			D3DXSetTransform(&D3DTS_PROJECTION, &matProjection);

		}  


	#endif       

}      

#if defined SWITCH || defined DREAMCAST
GLvoid Zoom(float fzoom)		// Resize And Initialize The GL Window
{
	
	//NN_LOG("EnterZoom");
	//if(RENDERER == RENDER_OPENGL)   
	{
		
	//	glViewport(0,0,sc_width,sc_height);						// Reset The Current Viewport
		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix

		

		if(mode)  
		{
			if(fzoom == 101) 
				glOrtho(-(1.0), 1.0, -(1.0), 1.0, -(1.0), 1.0); // Draw debug txt             
			if(fzoom == 102) 
				glOrtho(-(1.0), 1.0, -(0.75), 0.75, -(1.0), 1.0); // Draw Hud at 4:3
			if(fzoom != 101 && fzoom != 102)                  
				glOrtho(-(fzoom), fzoom, -(fzoom*sc_ratio), fzoom*sc_ratio, -(fzoom), fzoom);
			
		}
		else      
		{          
			if (screen_mode == SCREEN_NORMAL) // 4:3
			if(ZOOMING_CAMERA == 0)
				fzoom = 0.53f; // 0.53f + org_zoom_scroll_display
			else
				fzoom = 0.53f + org_zoom_scroll_display; // 0.53f + org_zoom_scroll_display

			if(screen_mode == SCREEN_169_WIDESCREEN)
				fzoom = 0.7f + org_zoom_scroll_display; // 0.7f - 0.6f
			if(screen_mode == SCREEN_1610_WIDESCREEN)
				fzoom = 0.636f + org_zoom_scroll_display; // 0.636f - 0.536f

			glOrtho(-(fzoom), fzoom, -(fzoom*sc_ratio), fzoom*sc_ratio, -(fzoom), fzoom);
			
		}

		
        
		//printf("EnterGLMODELVIEWMATRIX\n");
		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		//printf("ExitGLMODELVIEWMATRIX\n");
		glLoadIdentity();									// Reset The Modelview Matrix
		//printf("exitIdentity\n");
		
	}

	

}      


GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	} 
 
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
 	//printf("OrthoStartup %f %f\n", zoom_factor, zoom_factor*sc_ratio);
    glOrtho(-(zoom_factor), zoom_factor, -(zoom_factor*sc_ratio), zoom_factor*sc_ratio, -(zoom_factor), zoom_factor);             
           
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
    
}

  
int InitGL()				 						// All Setup For OpenGL Goes Here
{    
	    
	glFogi(GL_FOG_MODE, GL_LINEAR   );            // Fog Mode
	glFogf(GL_FOG_DENSITY, 1.0f);              // How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_FASTEST );            // Fog Hint Value
	glFogf(GL_FOG_START, -1.0f);            // Fog Start Depth  
	glFogf(GL_FOG_END, 0.0f);               // Fog End Depth 

 	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
    
    // GL_FLAT 
	glShadeModel(GL_FLAT); // GL_SMOOTH							    // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Black Background
    
    glEnable(GL_BLEND);  
#ifdef DREAMCAST    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending (disable alpha testing)
#else
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
#endif
    
    //glPushAttrib( GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT );

    glDisable( GL_LIGHTING );
    //glDisable( GL_DITHER );
    glDisable( GL_DEPTH_TEST );
    
	return true;										// Initialization Went OK
} 
void KillGLWindow()								// Properly Kill The Window
{

	/*if(fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}*/
	 
    /*if(RENDERER == RENDER_OPENGL)      
    {

		for(int i=0;i<numsubmtls;i++) 
			glDeleteTextures(1, &texID[i]);
            
		SAFE_DELETE_ARRAY(texID);

    }

	#if IS_USING_DIRECTX == 1  
		if(RENDERER == RENDER_DIRECTX)
			cleanD3D();
	#endif*/

	/*if(RENDERER == RENDER_OPENGL)
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if(RENDERER == RENDER_OPENGL)
	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	} 

	if(RENDERER == RENDER_OPENGL)
	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	} */
	 
	/*#if IS_USING_DIRECTX == 1 
	if(RENDERER == RENDER_DIRECTX)
	if (!UnregisterClass("DirectX",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
	#endif*/
	
}
/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
int CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
#if defined SWITCH || defined DREAMCAST
	GLuint		PixelFormat;

	long window_posX = 0;
	long window_posY = 0;

	if (fullscreen == false)
	{
		window_posX = (long)saved_window_posX;
		window_posY = (long)saved_window_posY;
	}

	fullscreen = fullscreenflag;

	ReSizeGLScene(width, height);

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		return false;								// Return FALSE
	}

	

	working_fullscreen = fullscreen;
	working_sc_width = width;
	working_sc_height = height;
	working_sc_bits = bits;

	if (changed_video == false && changed_renderer == false)
	{
		episode = 10;
		scene = 0;
	}

	LoadScene(episode, scene, false);

	sc_width = working_sc_width;
	sc_height = working_sc_height;

	Set_Screen_Ratio();
	fade = 1.0f;
	render_sequence = 0;
	//printf("EnterDrawGLCreate\n");
	DrawGLScene(true, 1);
	//printf("ExitDrawGLCreate\n");

	return(1);
#endif
	/*GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
    long window_posX=0;
    long window_posY=0;   
         
//    LoadCFG();

    if(fullscreen==false)
    {
        window_posX = (long)saved_window_posX; 
        window_posY = (long)saved_window_posY;
    }
     
    WindowRect.left=(long)0;			// Set Left Value To 0
    WindowRect.right=(long)width;		// Set Right Value To Requested Width
  
    WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height
    
	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window. // CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= 0;			                        // Load The Default Icon // LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor			= LoadCursor(NULL, IDC_CROSS);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{ 
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	 
	if (fullscreen)												// Attempt Fullscreen Mode?
	{ 
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				    // Selected Screen Width   - width
		dmScreenSettings.dmPelsHeight	= height;				    // Selected Screen Height  - height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{

			MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Switching to Windowed Mode.","Super Trench Attack!",MB_OK|MB_ICONEXCLAMATION);
			fullscreen=FALSE;

		}
	} 
     
	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(MOUSE_CURSOR_ACTIVE);										// Hide Mouse Pointer
	}
	else
	{
		dwStyle=WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;							// Windows Style
		ShowCursor(MOUSE_CURSOR_ACTIVE);										// Hide Mouse Pointer
	}

	AdjustWindowRect(&WindowRect, dwStyle, FALSE);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindow(	"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								window_posX, window_posY,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width // WindowRect.right-WindowRect.left
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height // WindowRect.bottom-WindowRect.top
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	} 
      
	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,				 				// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  // Was 16 
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}
 
	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
//	SetCapture(hWnd);                               // NEW 	
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen
	 
	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}
	
  	if(DEMO_MODE==0)
        fprintf(fp2,"CREATED WINDOW\n");
	    
 //   sprintf( temp_string.string, "scene/episode%i/scene%i", episode, scene);

    working_fullscreen = fullscreen; 
	working_sc_width = width;
	working_sc_height = height;      
	working_sc_bits = bits;

	if(changed_video == false && changed_renderer == false)
	{
        episode = 10; 
        scene   = 0; 
	} 

	RENDERER = RENDER_OPENGL;

    LoadScene(episode, scene, false); 

	sc_width = working_sc_width;
	sc_height = working_sc_height;

	Set_Screen_Ratio();                 
    fade = 1.0f;     
    render_sequence = 0;  
	DrawGLScene(true, 1);                   
    SwapBuffers(hDC);

	return(1);									// Success*/
}
#endif
   
#if IS_USING_DIRECTX == 1   

int CreateDXWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
#if 0
    long window_posX=0; 
    long window_posY=0;   
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
    WNDCLASS wc;   

    ZeroMemory(&wc, sizeof(WNDCLASS));

    WindowRect.left=(long)0;			// Set Left Value To 0
    WindowRect.right=(long)width;		// Set Right Value To Requested Width
  
    WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height
    
	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag
	 
	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW;	            // Redraw On Size, And Own DC For Window. // CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= 0;			                        // Load The Default Icon // LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor			= LoadCursor(NULL, IDC_CROSS);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "DirectX";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{ 
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	} 
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{

			MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Switching to Windowed Mode.","Super Trench Attack!",MB_OK|MB_ICONEXCLAMATION);
			fullscreen=FALSE;

		}
	} 
     
	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(MOUSE_CURSOR_ACTIVE);										// Hide Mouse Pointer
	}
	else
	{
		dwStyle  = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;							// Windows Style
		ShowCursor(MOUSE_CURSOR_ACTIVE);										// Hide Mouse Pointer
	}
	 
	AdjustWindowRect(&WindowRect, dwStyle, FALSE);		// Adjust Window To True Requested Size
  
	if (!(hWnd=CreateWindow(	"DirectX",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								window_posX, window_posY,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width // WindowRect.right-WindowRect.left
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height // WindowRect.bottom-WindowRect.top
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}  


	ShowWindow(hWnd, SW_SHOW); 

	d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface
	
    D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information
 
    ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
    d3dpp.Windowed = true;    // program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
    d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
//    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferWidth = width;    // width   
    d3dpp.BackBufferHeight = height;   // height 
    d3dpp.EnableAutoDepthStencil = false; 

    // create a device class using this information and information from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING, // D3DCREATE_MIXED_VERTEXPROCESSING
                      &d3dpp, 
                      &d3ddev);       
    
    d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting
    d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);    // turn off the 3D lighting
    d3ddev->SetRenderState(D3DRS_ZENABLE, false);    // turn off the z-buffer   

    // keep the alpha blending in
    d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);    // turn on the color blending

    d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);    // set source factor
    d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);    // set dest factor

 //   d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);    // set the operation
	d3ddev->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	 
	if(sc_blur == true) 
	{
		d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );    // set the operation 
		d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );    // set the operation 
	}
	else
	{
		d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT  );    // set the operation 
		d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT  );    // set the operation 
	}

    working_fullscreen = fullscreen;   
	working_sc_width = width;
	working_sc_height = height;  
	working_sc_bits = bits;
#endif

	if(changed_video == false && changed_renderer == false)
	{
        episode = 10;  
        scene   = 0; 
	}

	RENDERER = RENDER_DIRECTX; 

    LoadScene(episode, scene, false); 

	sc_width = working_sc_width;
	sc_height = working_sc_height; 
	 
	Set_Screen_Ratio();                 
    fade = 1.0f;    
    render_sequence = 0;
#ifndef XB1
	DrawGLScene(true, 1);
#endif
//    SwapBuffers(hDC);

	return(1);									// Success*/

} 

// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{ 
#if 0
    SAFE_RELEASE(v_buffer);    // close and release the vertex buffer 

	SAFE_RELEASE(i_buffer);

    SAFE_RELEASE(v_buffer1);    // close and release the vertex buffer 

	SAFE_RELEASE(i_buffer1);

	for(int i=0;i<numsubmtls;i++)  
	if(i < 100)
		SAFE_RELEASE(texture[i]); 

	SAFE_RELEASE(d3ddev);
	SAFE_RELEASE(d3d);
#endif

}  
   
#endif 

void Refresh_Window(int new_renderer)
{
	int created_a_window=0;
#ifdef SWITCH
	KillGLWindow();	 	  				// Kill Our Current Window
#endif
	RENDERER = new_renderer;

	/*if(RENDERER == RENDER_OPENGL)   
	{ 
		// Recreate Our OpenGL Window 
		created_a_window = CreateGLWindow("Verdict Guilty™", new_sc_width, new_sc_height, sc_bits, fullscreen);
	}

	if(RENDERER == RENDER_DIRECTX)   
	{ 
		// Recreate Our OpenGL Window 
		created_a_window = CreateDXWindow("Verdict Guilty™", new_sc_width, new_sc_height, sc_bits, fullscreen);
	}

	if(created_a_window == 0) // Couldn't create...                       
	{	  
		if(new_renderer == RENDER_OPENGL)
			MessageBox (HWND_DESKTOP, "Couldn't create openGL_window", "Error", MB_OK | MB_ICONEXCLAMATION);
		else
			MessageBox (HWND_DESKTOP, "Couldn't create directX_window", "Error", MB_OK | MB_ICONEXCLAMATION);

		return;				  		// Quit If Window Was Not Created           
	}       
	if( created_a_window == 1) // Created window...                         
	{	        
		sc_width = new_sc_width;                   
		sc_height = new_sc_height;       
        SaveCFG();           
	}  
                                                   
    changed_renderer = false;
    changed_video = false; */

}