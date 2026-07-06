
#ifdef SWITCH
#include <egl/egl.h>
#include "glad/glad.h"
#endif
#include "globals.h" 
#ifdef SATURN
#include "saturn_profile.h"
#endif

#ifdef XB1
#include <vector>
extern SDL_Renderer* pRenderer;
extern std::vector< SDL_Vertex > VTXsdl;
extern std::vector< int > IDXsdl;
#endif
               
// External routines
extern int GetFont(float &x, float &y, char letter, float &s_width, int set, int modeset, bool password, int game_mode);
extern int GetNewFont(float &x, float &y, char letter, float &s_width, int set, int modeset, bool password, int game_mode);
extern float Node_Distance1(float x1, float y1, float x2, float y2);
#if defined SWITCH || defined DREAMCAST 
extern GLvoid Zoom(float fzoom);
#endif
extern void ZoomDX(int type); 

#if IS_USING_DIRECTX == 1  
void Draw_BGDX(int temp1, int temp2, bool alpha_pass, bool is_debug);
void DrawDXBox(float x, float y, float width, float height);
#endif 

#ifdef DREAMCAST
extern float Get_Texture_Coord(int id, int fx_id, int frame, bool is_a_sprite, unsigned int &customID);
#else
extern float Get_Texture_Coord(int id, int fx_id, int frame, bool is_a_sprite);
#endif
extern void Z_Buffer(bool is_a_sprite);
extern void Set_Values(float x, float y, float R, float G, float B, float A, float u, float v);
extern void Draw_Sprite(int f_rate);
extern void Draw_Hud_Sprites();
extern void Draw_Lines();

void DrawLine( float x, float y, float width, float height, float colour, float line_width);
void DrawNodeLine( float x, float y, float x1, float y1, float colour, float width);
void DrawBox( float x, float y, float x1, float y1);
void DrawPoint( float x, float y, float size);
void View_Cone(bool is_a_sprite);
void Debug_Display(); 

void Draw_Hud(int index);
void Draw_Font(int i); 
void Draw_New_Font(int i); 
void DrawTileBox();
float GetCamDistance();

#ifdef SWITCH

int		 IRenderModuleInit(void);
int		 IRenderStart(void);
int		 IRenderState(int state);
int		 IRenderClear(unsigned int flags, unsigned int c);
void	 PGuiCameraNative(void);
int		 IRenderSwap(void);
int		 IRenderEnd(void);

#endif
    
#if IS_USING_DIRECTX == 1  
void Set_Vertex_Buffer(int loop, int r, int g, int b, float alpha, bool is_a_sprite, bool flipped); 
#endif
    
// ******************************************************************************//
//                                                                               //
//                                 DRAW SCENE                                    //
//                                                                               //
// ******************************************************************************//
  
int DrawGLScene(bool render_all, int f_rate)									// Here's Where We Do All The Drawing
{ 
#ifdef SATURN
	vg_saturn_profile_draw_scene_begin();
#endif
	//printf("ENTER DRAW GL\n");
#ifdef SWITCH
	IRenderStart();
	IRenderClear(1 | 2, 0xff000000);
	IRenderState(1);

	PGuiCameraNative();
#elif PS4
	//printf("BEGIN SCENE\n");
	_Application.getGraphics()->beginScene(_Application.getGraphics()->getNextRenderTarget(), _Application.getGraphics()->getDepthStencilSurface());

	//if (mode)
		//_Application.getGraphics()->clearRenderTarget(_Application.ClearScreenColor(0, 0, 0, 50));
	//else
		//_Application.getGraphics()->clearRenderTarget(_Application.ClearScreenColor(0, 0, 0, 0));
	//d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 50), 1.0f, 0);

	if (VG_INVERT)
		_Application.getGraphics()->clearRenderTarget(_Application.ClearScreenColor(0, 255, 0, 90));
	else if (mode)
		_Application.getGraphics()->clearRenderTarget(_Application.ClearScreenColor(0, 0, 0, 50));
	else
		_Application.getGraphics()->clearRenderTarget(_Application.ClearScreenColor(0, 0, 0, 0));

	//d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 0, 90), 1.0f, 0);

	_Application.getGraphics()->setDepthWriteEnable(true);
	_Application.getGraphics()->setDepthFunc(sce::SampleUtil::Graphics::kDepthFuncAlways);
#elif XB1
	//global_sample->m_deviceResources->Prepare();
	
	if (VG_INVERT)
	{
		SDL_SetRenderDrawColor(pRenderer, 255, 0, 90, 255);
		SDL_RenderClear(pRenderer);
	}
	else if (mode)
	{
		SDL_SetRenderDrawColor(pRenderer, 0, 0, 50, 255);
		SDL_RenderClear(pRenderer);
	}
	else
	{
		SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
		SDL_RenderClear(pRenderer);
	}
#endif
    float cx1=0.0, cy1=0.0;
    float cx2=0.0, cy2=0.0;
    float cx3=0.0, cy3=0.0;
     
    float diff_Y=0.0;
     
    // Font
    float testX = 0.0f, testY = 0.0f;
    float testX1 =0.0f, testY1 = 0.0f;
    float is_slim_lttr =0.0f, slim_width=0.0f;
    float addX = 0.0f, addY = 0.0f, Yamount=0.0f; 
    float test_angle=0.0;
     
    float vR = fade, vG = fade, vB = fade;
    float spritelight=0.0;
        
    int letters = 0; 
    int temp=0;
    int temp1=0; 
    int temp2=0;
    int temp3=0;
    int row_x=0;
    int row_y=0;
    int minus_plus=0;
    int display_selection=0;
    float ftemp=0.0f;
    int temp_row_x =0; 
    int temp_row_y =0;
    int cull_sizeX=0;
    int cull_sizeY=0;
    int hud_cull=0;
	int index=0;
    
    int player_sprite=0;    
    
    bool scroll_text = false;
    bool p_test=false;
    bool on_paper=false;
    bool dont_draw=false;

	float original_camX = 0.0f;
	float original_camY = 0.0f;

	if(fade >= 1.0f)
		fade = 1.0f;

	if(fade <= 0.0f)
		fade = 0.0f;

    // Sort out the sprite order here...
      
    // ******************************************************************************//
    //                                Viewcone                                       //
    // ******************************************************************************//
	
	// Setup the camera...	

	#if IS_USING_DIRECTX == 1  
	if (RENDERER == RENDER_DIRECTX)
	{


		if (episode == 5)
			org_zoom_scroll_display = org_zoom_scroll_amount;

		ZoomDX(TYPE_MODE_NORM);

#ifdef XB1
		D3DXVECTOR3 a = { -camX, -camY, -1.0f };
		D3DXVECTOR3 b = { -camX, -camY, 0.0f };
		D3DXVECTOR3 c = { 0.0f, 1.0f, 0.0f }; // rotation

		D3DXVECTOR3 d = { 0.0f, 0.0f, -1.0f };
		D3DXVECTOR3 e = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 f = { 0.0f, 1.0f, 0.0f };

		// Set the camera in the world...   
		D3DXMatrixLookAtLH(&matCamView,
			&a,    // the camera position  
			&b,    // the look-at position  
			&c);    // the up direction  

					// Set the camera in the world...   
		D3DXMatrixLookAtLH(&matViewReset,
			&d,    // the camera position     
			&e,    // the look-at position  
			&f);    // the up direction   

		D3DXMatrixIdentity(&matIdentity);


		//d3ddev->BeginScene();

		// select which vertex format we are using
		//d3ddev->SetFVF(CUSTOMFVF);

#elif PS4
		D3DXVECTOR3 a = { -camX, -camY, -1.0f };
		D3DXVECTOR3 b = { -camX, -camY, 0.0f };
		D3DXVECTOR3 c = { 0.0f, 1.0f, 0.0f }; // rotation

		D3DXVECTOR3 d = { 0.0f, 0.0f, -1.0f };
		D3DXVECTOR3 e = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 f = { 0.0f, 1.0f, 0.0f };

		// Set the camera in the world...   
		D3DXMatrixLookAtLH(&matCamView,
			&a,    // the camera position  
			&b,    // the look-at position  
			&c);    // the up direction  

// Set the camera in the world...   
		D3DXMatrixLookAtLH(&matViewReset,
			&d,    // the camera position     
			&e,    // the look-at position  
			&f);    // the up direction   

		D3DXMatrixIdentity(&matIdentity);

		
		//d3ddev->BeginScene();

		// select which vertex format we are using
		//d3ddev->SetFVF(CUSTOMFVF);
#endif


	}
	#endif  

    memset(var5, 0, sizeof(var5) );   
    new_no_sprites=0; 

    View_Cone(true);  // For sprites...
        
    if(!mode)   // game_mode == WALK && 
        View_Cone(false); // For Fx...
            
    rendering = new_no_sprites;
#ifdef SATURN
    vg_saturn_profile_set_render_counts((uint32_t)no_sprites +
                                        (mode ? 0U : (uint32_t)no_fx),
                                        (uint32_t)new_no_sprites);
#endif
#if defined SWITCH || defined DREAMCAST
	if(RENDERER == RENDER_OPENGL) 
	{

		if(mode) 
    		glClearColor(0.0f, 0.0f, 0.5f, 0.0f);				// Blue Background
		else 
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);               // Black Background

		if(mode || fade == 0.0f)
			glClear(GL_COLOR_BUFFER_BIT );	// Clear Screen And Depth Buffer

		if(VG_INVERT)
		{
			glClearColor(1.0f, 0.0f, 0.5f, 0.0f);               // Black Background
			glClear(GL_COLOR_BUFFER_BIT );	// Clear Screen And Depth Buffer
		}
     
		glLoadIdentity();									// Reset The Current Modelview Matrix
		 
		if(episode == 5)
		    org_zoom_scroll_display = org_zoom_scroll_amount;
		//printf("Enter Zoom\n");
		Zoom( zoom_factor);
		//printf("End Zoom\n");

	} 

          
	if(RENDERER == RENDER_OPENGL)
	{
	    glTranslatef(camX, camY, 0.0f); 
	} 
#endif
	
	#if IS_USING_DIRECTX == 1   
	if (RENDERER == RENDER_DIRECTX)
		D3DXSetTransform(&D3DTS_VIEW, &matCamView);
	#endif
         
    // ******************************************************************************//
    //                              Scene sprites                                    //
    // ******************************************************************************//
    
    if((int)TimerGetTime() > view_cone_timer || (Z_BUFFER_ALWAYS == 1 && render_sequence == 0) || mode )   
	{
        Z_Buffer(true); 
	}     
          
     
    if(render_sequence == 0 || render_all == true)   // render_sequence == 1
    {      
	    Draw_Sprite(f_rate);    
    }       
    
    
    // ******************************************************************************//
    //                                Draw Points                                    //
    // ******************************************************************************//
#if defined SWITCH || defined DREAMCAST
	if(RENDERER == RENDER_OPENGL) 
    if(mode && mode == POINT_MODE)     
    for(int i=0;i < no_points;i++) 
	if(i >= 0 && i < TOTAL_NO_POINTS)
    { 
             
        if(i==pt_selection)
	        glColor4f(1.0f,1.0f,1.0f,1.0f);
	    else
	        glColor4f(0.6f,0.6f,0.6f,0.6f);  
                  
        DrawPoint( points[i].x, points[i].y, 10.0f);
        
    }

	// Display hit points...
	if(RENDERER == RENDER_OPENGL)  
    if(TEST_POINTS == 1)    
    for(int i=0;i < no_points;i++) 
	if(i >= 0 && i < TOTAL_NO_POINTS)
	if(points[i].active == 1)
    { 
               
        glColor4f(1.0f,1.0f,1.0f,1.0f);  
                  
        DrawPoint( points[i].x, points[i].y, 10.0f);

		if(i == 0 || i == 1)
            DrawNodeLine( points[i].x, points[i].y, points[i+2].x, points[i+2].y, 0.5f, 1.0f);
    }
#endif
    
    // ******************************************************************************//
    //                                Draw Nodes                                     //
    // ******************************************************************************//
#if defined SWITCH || defined DREAMCAST
	if(RENDERER == RENDER_OPENGL) 
    if(mode && mode != POINT_MODE)  
	if(nde_selection >= 0 && nde_selection < TOTAL_NO_NODES)
    for(int i=0;i < no_nodes;i++)
    {
             
        if(i==nde_selection)
	        glColor4f(1.0f,1.0f,1.0f,1.0f);
	    else
	        glColor4f(0.6f,0.6f,0.6f,0.6f);

        if(i == nodes[nde_selection].c1)
            glColor4f(0.0f,0.6f,0.0f,0.6f);
        if(i == nodes[nde_selection].c2)
            glColor4f(0.0f,0.6f,0.0f,0.6f);
        if(i == nodes[nde_selection].c3)
            glColor4f(0.0f,0.6f,0.0f,0.6f);
        if(i == nodes[nde_selection].c4)
            glColor4f(0.0f,0.6f,0.0f,0.6f);
                    
        DrawPoint( nodes[i].x, nodes[i].y, 10.0f);       
                     
    }  

        
    // Reset the camera so Text isn't affected

    if(RENDERER == RENDER_OPENGL) 
	{
	    glLoadIdentity();
    
	    Zoom(TYPE_MODE_HUD);   // zoom_factor     
    
		glTranslatef(0.0f, 0.0f, 0.0f); 
	}
#endif

	// Reset the camera so Text isn't affected
	#if IS_USING_DIRECTX == 1
    if(RENDERER == RENDER_DIRECTX) 
	{
		D3DXMatrixIdentity (&matIdentity);

		D3DXSetTransform(&D3DTS_VIEW, &matViewReset);

		ZoomDX(TYPE_MODE_NORM);
		 
	} 
	#endif
                
    // ******************************************************************************//
    //                              HUD sprites                                      //
    // ******************************************************************************//

	if( (int)TimerGetTime() > view_cone_timer || (Z_BUFFER_ALWAYS == 1 && render_sequence == 0)) 
	{         
        Z_Buffer(false);   
	}
             
    vR = fade, vG = fade, vB = fade;

    if(render_sequence == 0 || render_all == true)    //  // render_sequence == 1 
    {   

		org_zoom_scroll_display = 0.0f;
#if defined SWITCH || defined DREAMCAST
        if(RENDERER == RENDER_OPENGL)  
			Zoom(TYPE_MODE_HUD); // 102  
#endif
        if(RENDERER == RENDER_DIRECTX)
			ZoomDX(TYPE_MODE_HUD); // 102  

        Draw_Hud_Sprites();
         
    }         
     
    Debug_Display();   
         
    vR = fade, vG = fade, vB = fade; 
                      
    // ******************************************************************************//
    //                              Font sprites                                     //
    // ******************************************************************************//

    if(RENDERER == RENDER_DIRECTX)
		ZoomDX(TYPE_MODE_NORM); // 102  

    if(render_sequence == 0 || render_all == true) //  render_sequence == 1
    if(quit_active == false) 
	if(mode)
    for(int i=0;i<TOTAL_TEXT;i++)
	{
		Draw_Font(i);   
	}

    if(render_sequence == 0 || render_all == true) //  render_sequence == 1
    if(quit_active == false) 
    if(!mode)
    for(int i=0;i<TOTAL_TEXT;i++)
	{
		Draw_New_Font(i);  
	}        


    // ******************************************************************************//
    //                               Mouse Pointer                                   //
    // ******************************************************************************//

#if defined SWITCH || defined DREAMCAST
    // Draw a box around mouse tile  
	if(RENDERER == RENDER_OPENGL)
    if(mode == TILE_MODE)          
    {  
         Zoom(102); 
    } 
	 
    if(RENDERER == RENDER_OPENGL)          
		Zoom(zoom_factor);
#endif
	if(RENDERER == RENDER_DIRECTX)   
		ZoomDX(TYPE_MODE_NORM);

	Draw_Hud(1);  // Arrow     
#if defined SWITCH || defined DREAMCAST
    // Debug screen outline  
	if(RENDERER == RENDER_OPENGL)
    if(mode)
    {
       Zoom(zoom_factor);     
       DrawLine( -zoom_factor, -zoom_factor*sc_ratio, (zoom_factor*2), ((zoom_factor*sc_ratio)*2), 0.7f, 4.0f);
    }    
#endif
	 
    // Debug screen outline  
	#if IS_USING_DIRECTX == 1 
	if(RENDERER == RENDER_DIRECTX) 
    if(mode)
    {
		if (RENDERER == RENDER_DIRECTX)
			D3DXSetTransform(&D3DTS_VIEW, &matCamView);

		#if IS_USING_DIRECTX == 1 
			DrawDXBox(-1.0f, -1.0f*sc_ratio, 2.0f, 2.0f*sc_ratio);
		#endif

    }     
	#endif
         
    if( (int)TimerGetTime() > view_cone_timer )   
    {          
         view_cone_timer = (int)TimerGetTime() + 10; // was 25 was 50
    } 
     
    render_sequence++;    
    
    if(render_sequence >= 1)   // render_sequence >= 2
    {
        double_main_code = 1; 
        render_sequence = 0;
#ifdef SWITCH
        if(RENDERER == RENDER_OPENGL)
			glFlush();										// Flush The GL Rendering Pipeline
#endif
         
    } 
#ifdef SWITCH
	IRenderEnd();
	IRenderSwap();
#elif PS4
	_Application.getGraphics()->endScene();

	_Application.render();
	//printf("END SCENE\n");
#elif XB1
	SDL_RenderPresent(pRenderer);
#elif DREAMCAST
	glKosSwapBuffers();
#endif

#ifdef SATURN
	vg_saturn_profile_draw_scene_end();
#endif
	return true;										// Everything Went OK
}

#if defined SWITCH || defined DREAMCAST
void DrawBox( float x, float y, float x1, float y1)
{
    
 	glLineWidth(4.0);
	glDisable(GL_TEXTURE_2D);
	
    // draw the line
	glBegin(GL_LINES);
      
        Set_Values(x, y, -1, -1, -1, -1, -1, -1);        
	    glVertex2fv(&Gvector[0]);
        Set_Values(x1, y1, -1, -1, -1, -1, -1, -1); 	    
	    glVertex2fv(&Gvector[0]);
                	    
	glEnd();
	  
	glEnable(GL_TEXTURE_2D);         
     
}


void DrawPoint( float x, float y, float size)
{
#ifndef DREAMCAST 
 	glPointSize(size);
#endif
	glDisable(GL_TEXTURE_2D);
	
    // draw the line
	glBegin(GL_POINTS);
 
	    glVertex2f(x, y);
                	    
	glEnd();
	  
	glEnable(GL_TEXTURE_2D);       
     
}

void DrawLine( float x, float y, float width, float height, float colour, float line_width)
{
     
    width += x;
    height += y;
     
 	glLineWidth(line_width);
	glDisable(GL_TEXTURE_2D);
	
	if(fade == 0.0) 
	    colour = 0.0; 
	
    // draw the line
	glBegin(GL_LINES);
	    
	    glColor3f(colour,colour,colour);
	    
	    glVertex3f(x, y, 0.0);
	    glVertex3f(x, height, 0.0);
	    
   	    glVertex3f(x, height, 0.0);
	    glVertex3f(width, height, 0.0);
	    
   	    glVertex3f(width, height, 0.0);
	    glVertex3f(width, y, 0.0);
	    
   	    glVertex3f(width, y, 0.0);
	    glVertex3f(x, y, 0.0);
                	    
	glEnd();
	  
	glEnable(GL_TEXTURE_2D);    
         
}    

void DrawNodeLine( float x, float y, float x1, float y1, float colour, float width)
{
      
 	glLineWidth(width);
	glDisable(GL_TEXTURE_2D); 

    // draw the line
	glBegin(GL_LINES);
	    
	    glColor3f(colour,colour,colour);
	    
	    glVertex3f(x, y, 0.0f);
	    glVertex3f(x1, y1, 0.0f);
                	    
	glEnd();
	  
	glEnable(GL_TEXTURE_2D);   
 
} 
#endif

void View_Cone(bool is_a_sprite)
{

     bool keep_in=false; 
     float x1=0.0f, y1=0.0f;
     float x2=0.0f, y2=0.0f;  
     float x3=0.0f, y3=0.0f; 
     float x4=0.0f, y4=0.0f;       
     float cx1=0.0f, cy1=0.0f;
     float cx2=0.0f, cy2=0.0f;
     float off_set = 0.1f; 
     int index=0; 
   
     if(is_a_sprite == true) 
     { 
         index=no_sprites;
     }              
          
     if(is_a_sprite == false)  
     { 
         index = no_fx;   
     }    
      
	 if(game_mode == FRONT)  
		 off_set = 0.2f;

     cx1 = -camX - (zoom_factor); // Mid-Point X
     cx2 = -camX + (zoom_factor); // Half the width
     cy1 = -camY - ((zoom_factor*sc_ratio)); // Mid-Point Y                         
     cy2 = -camY + ((zoom_factor*sc_ratio)); // Half the height 
     
     cx1 -= off_set; 
     cx2 += off_set;
     cy1 -= off_set;
     cy2 += off_set;
#if defined(SATURN)
     cx1 -= 0.25f;
     cx2 += 0.25f;
     cy1 -= 0.25f;
     cy2 += 0.25f;
#endif
         
     for(int loop=0;loop<index;loop++)  
     {
          
         keep_in = false; 
         
         if(is_a_sprite == true)
		 if(loop >= 0 && loop < TOTAL_NO_SPRITES )
         {
             x1 = (sprite[loop].x);
             x2 = (sprite[loop].x + sprite[loop].width);
             y1 = (sprite[loop].y);
             y2 = (sprite[loop].y + sprite[loop].height);
             x3 = (sprite[loop].x + (sprite[loop].width/2));
             y3 = (sprite[loop].y + (sprite[loop].height/2));
                              
         }                                      
         
         if(is_a_sprite == false)
		 if(loop >= 0 && loop < TOTAL_NO_FX_SPRITES )
         {
                       
             
             x1 = (Fx[loop].x); 
             x2 = (Fx[loop].x + Fx[loop].width);
             y1 = (Fx[loop].y);
             y2 = (Fx[loop].y + Fx[loop].height);
             x3 = (Fx[loop].x + (Fx[loop].width/2));
             y3 = (Fx[loop].y + (Fx[loop].height/2));
             
             if(Fx[loop].angle < 0)         
                 Fx[loop].angle += 360; 
                      
         } 
                  
         if((x2 >= cx1) && (x1 <= cx2) &&
            (y2 >= cy1) && (y1 <= cy2))
         {
             keep_in = true;
         } 
         
         if(keep_in == false)                               
         if(( x1 < cx2 )
         &&( x1 > cx1 )                        
         &&( y1 < cy2 )
         &&( y1 > cy1))
         {
             keep_in = true;    
         }
         
         if(keep_in == false)                              
         if(( x2 < cx2 )
         &&( x2 > cx1 )                        
         &&( y1 < cy2 )
         &&( y1 > cy1))
         {
             keep_in = true;    
         }                                             

         if(keep_in == false)                              
         if(( x2 < cx2 )
         &&( x2 > cx1 )                        
         &&( y2 < cy2 )
         &&( y2 > cy1))
         {
             keep_in = true;    
         }         

         if(keep_in == false)                              
         if(( x2 < cx2 )
         &&( x2 > cx1 )                        
         &&( y3 < cy2 )
         &&( y3 > cy1))
         {
             keep_in = true;    
         }         

         if(keep_in == false)                              
         if(( x1 < cx2 )
         &&( x1 > cx1 )                        
         &&( y3 < cy2 )
         &&( y3 > cy1))
         {
             keep_in = true;    
         }     

         if(keep_in == false)                           
         if(( x3 < cx2 )
         &&( x3 > cx1 )                        
         &&( y1 < cy2 )
         &&( y1 > cy1))
         {
             keep_in = true;    
         }         

         if(keep_in == false)                              
         if(( x3 < cx2 )
         &&( x3 > cx1 )                        
         &&( y2 < cy2 )
         &&( y2 > cy1))
         { 
             keep_in = true;      
         }  

		 // Non-Saturn builds historically kept every renderable in view.
#if !defined(SATURN)
		 keep_in = true;
#endif
#if defined(SATURN)
         if(is_a_sprite == true && loop >= 0 && loop < TOTAL_NO_SPRITES &&
            sprite[loop].priority >= 6)
             keep_in = true;
         if(is_a_sprite == false && loop >= 0 && loop < TOTAL_NO_FX_SPRITES &&
            Fx[loop].priority >= 6)
             keep_in = true;
#endif
                                     
         if(keep_in == true)       
         {  
                    
			 if(loop >= 0 && loop < TOTAL_NO_SPRITES )
             if(is_a_sprite == true && sprite[loop].turn_off == false)          
             {
                 if(new_no_sprites < TOTAL_NO_SPRITES)   
                     var5[new_no_sprites] = loop;  
                       
                 if(new_no_sprites < TOTAL_NO_SPRITES)
                     new_no_sprites++;  
                         
             }
			 if(loop >= 0 && loop < TOTAL_NO_FX_SPRITES )
             if(is_a_sprite == false && Fx[loop].turn_off == false)     
             { 
                   
                 if(new_no_sprites < TOTAL_NO_SPRITES)       
                     var5[new_no_sprites] = loop + TOTAL_NO_SPRITES;
                 
                 if(new_no_sprites < TOTAL_NO_SPRITES)                 
                     new_no_sprites++;     
   
             }
                        
                    
         }
         
     } 
     
}

void Debug_Display()
{
     
if(mode)
    {

	if(selection < 0)
	    selection = 0;
	if(nde_selection < 0)
	    nde_selection = 0;
	if(pt_selection < 0)
	    pt_selection = 0; 
 
    sprintf( text[0].word, "Scene : %i-%i-%i", episode, scene, g_type);
    
    if(g_type == G_NON)
        sprintf( text[0].word, "Scene : %i-%i-NON", episode, scene, g_type);
    if(g_type == G_ACT)
        sprintf( text[0].word, "Scene : %i-%i-ACT", episode, scene, g_type);
    if(g_type == G_FGT)
        sprintf( text[0].word, "Scene : %i-%i-FGT", episode, scene, g_type);
    if(g_type == G_WLK)
        sprintf( text[0].word, "Scene : %i-%i-WLK", episode, scene, g_type);
    if(g_type == G_BLK)
        sprintf( text[0].word, "Scene : %i-%i-BLK", episode, scene, g_type);
    if(g_type == G_SHT)
        sprintf( text[0].word, "Scene : %i-%i-SHT", episode, scene, g_type);
    if(g_type == G_SGN)
        sprintf( text[0].word, "Scene : %i-%i-SGN", episode, scene, g_type);
    if(g_type == G_STS)
        sprintf( text[0].word, "Scene : %i-%i-STS", episode, scene, g_type);
    if(g_type == G_ZIN)
        sprintf( text[0].word, "Scene : %i-%i-ZIN", episode, scene, g_type);
    if(g_type == G_ZOT)
        sprintf( text[0].word, "Scene : %i-%i-ZOT", episode, scene, g_type);
    if(g_type == G_SLI)
        sprintf( text[0].word, "Scene : %i-%i-SLI", episode, scene, g_type);        
    if(g_type == G_FLL)
        sprintf( text[0].word, "Scene : %i-%i-FLL", episode, scene, g_type);  
    if(g_type == G_FLY) 
        sprintf( text[0].word, "Scene : %i-%i-FLY", episode, scene, g_type);  
    if(g_type == G_OLD)
        sprintf( text[0].word, "Scene : %i-%i-OLD", episode, scene, g_type);   
                
    sprintf( text[1].word, "Timer-Shake : %i-%i-???", game_time, scene_shake);
                                                                              
    if(music_loop == SND_NON)     
        sprintf( text[1].word, "Timer-Shake : %i-%i-NON", game_time, scene_shake); 
    if(music_loop == SND_END)
        sprintf( text[1].word, "Timer-Shake : %i-%i-END", game_time, scene_shake);
    if(music_loop == SND_JET)
        sprintf( text[1].word, "Timer-Shake : %i-%i-JET", game_time, scene_shake); 
    if(music_loop == SND_WAR)
        sprintf( text[1].word, "Timer-Shake : %i-%i-BOOT", game_time, scene_shake); 
    if(music_loop == SND_LND)
        sprintf( text[1].word, "Timer-Shake : %i-%i-FRONT", game_time, scene_shake);
    if(music_loop == SND_CRD)
        sprintf( text[1].word, "Timer-Shake : %i-%i-BEACH", game_time, scene_shake);
    if(music_loop == SND_ARMY)
        sprintf( text[1].word, "Timer-Shake : %i-%i-BOSS", game_time, scene_shake);
    if(music_loop == SND_FIGHT)
        sprintf( text[1].word, "Timer-Shake : %i-%i-CAMP", game_time, scene_shake);
    if(music_loop == SND_SAD) 
        sprintf( text[1].word, "Timer-Shake : %i-%i-SAD", game_time, scene_shake);        
    if(music_loop == SND_DGNB) 
        sprintf( text[1].word, "Timer-Shake : %i-%i-DGNB", game_time, scene_shake); 
    if(music_loop == SND_FINAL)
        sprintf( text[1].word, "Timer-Shake : %i-%i-FINAL", game_time, scene_shake); 
    if(music_loop == SND_DANGERS)
        sprintf( text[1].word, "Timer-Shake : %i-%i-DANGERS", game_time, scene_shake); 
    if(music_loop == SND_INTRO)
        sprintf( text[1].word, "Timer-Shake : %i-%i-INTRO", game_time, scene_shake);        
    if(music_loop == SND_FANFARE)
        sprintf( text[1].word, "Timer-Shake : %i-%i-FANFARE", game_time, scene_shake); 
    if(music_loop == SND_URGENCY) 
        sprintf( text[1].word, "Timer-Shake : %i-%i-URGENCY", game_time, scene_shake);
    if(music_loop == SND_MINI)
        sprintf( text[1].word, "Timer-Shake : %i-%i-GROOVE", game_time, scene_shake);          
    if(music_loop == SND_FANFARE2)
        sprintf( text[1].word, "Timer-Shake : %i-%i-FANFARE2", game_time, scene_shake);
    if(music_loop == SND_DEATH)
        sprintf( text[1].word, "Timer-Shake : %i-%i-DEATH", game_time, scene_shake); 
    if(music_loop == SND_SIEGE)
        sprintf( text[1].word, "Timer-Shake : %i-%i-SIEGE", game_time, scene_shake);
    if(music_loop == SND_THEATRE)
        sprintf( text[1].word, "Timer-Shake : %i-%i-THEATRE", game_time, scene_shake);
    if(music_loop == SND_CREDITS)
        sprintf( text[1].word, "Timer-Shake : %i-%i-CREDITS", game_time, scene_shake); 

                                                                                           
    if ( mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
        sprintf( text[2].word, "Sprite[%i].Id : %i", selection, sprite[selection].id);
    if( mode == POINT_MODE)
        sprintf( text[2].word, "Point[%i]", pt_selection);
    if( mode == NODES) 
        sprintf( text[2].word, "Node[%i]", nde_selection);

    if( mode == PLACEMENT)    
        sprintf( text[3].word, "Placement Mode");
 
    if( mode == TEXTURE)    
        sprintf( text[3].word, "Texture Mode");

    if( mode == COLLISION)    
        sprintf( text[3].word, "Collision Mode"); 

    if( mode == CAMERA)    
        sprintf( text[3].word, "Camera Mode");
 
    if( mode == NODES)    
        sprintf( text[3].word, "Nodes Mode");

    if( mode == TILE_MODE)     
        sprintf( text[3].word, "Tiling mode"); 
                                
    sprintf( text[4].word, "Editing...");  

    if( game_mode == NORM)    
        sprintf( text[6].word, "Game Mode : norm");
 
    if( game_mode == GAME)    
        sprintf( text[6].word, "Game Mode : game");
 
    if( game_mode == CINE)    
        sprintf( text[6].word, "Game Mode : cine");

    if( game_mode == WALK)    
        sprintf( text[6].word, "Game Mode : walk");

    if( game_mode == FRONT)    
        sprintf( text[6].word, "Game Mode : front");

    if( game_mode == WORLD)    
        sprintf( text[6].word, "Game Mode : world");
                                                        
    sprintf( text[7].word, "Fading : [%i][%i][%.1f]", fade_in, fade_out, sprite[selection].alpha );
    
    if( mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
        sprintf( text[8].word, "score : %i", sprite[selection].score);

    if( mode == NODES)
        sprintf( text[8].word, "Direction : %i", nodes[nde_selection].score);
   
        

        
    if( mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
        sprintf( text[9].word, "Anims [%i][%i]", sprite[selection].anim_state, sprite[selection].anim); 
    if( mode != POINT_MODE && mode != NODES && sprite[selection].type == CUT && mode != TILE_MODE)
        sprintf( text[9].word, "Level [%i][%i]", sprite[selection].anim_state, sprite[selection].anim); 
            
    if( mode == POINT_MODE)
        sprintf( text[9].word, "Anims [%i][%i]", points[pt_selection].anim_state, points[pt_selection].anim); 
        
    if( mode == NODES) 
        sprintf( text[9].word, "Anims [%i][%i]", nodes[nde_selection].anim_state, nodes[nde_selection].anim); 
    
    sprintf( text[10].word, "Linked : [%i]", sprite[selection].linked_sprite);
       
    if(game_mode == WALK)       
    {

    if( sprite[selection].type == LVL) 
    {
        sprintf( text[10].word, "Scene : [%i]", sprite[selection].linked_sprite); 
    } 
    
    if( sprite[selection].type == DOR) 
    {
        sprintf( text[10].word, "Global : [%i]", sprite[selection].linked_sprite); 
    }     

    }
    
    if(game_mode == FRONT)
    {
        if( sprite[selection].type == FE_MOVE) 
            sprintf( text[10].word, "Speed : [%i]", sprite[selection].linked_sprite);                                               
    }
        
    sprintf( text[11].word, "Priority : [%i]", sprite[selection].priority);
    
    sprintf( text[13].word, "C-BOX : %i", sprite[selection].grab_switch); 
 
    sprintf( text[14].word, "Mouse_over : %i", sprite[selection].mouseover); 
         
    sprintf( text[15].word, "Sector : %i", sprite[selection].sector);
         
    if(game_mode == FRONT) 
    { 
        sprintf( text[15].word, "Episode : %i", sprite[selection].sector);     

		if(sprite[selection].type >= FE_TYPE1 && sprite[selection].type <= FE_TYPE8)
			sprintf( text[15].word, "TargetA : %i", sprite[selection].sector);     

    }
         
    sprintf( text[16].word, "AI Type : %i", sprite[selection].sector_action); 
      
    sprintf( text[17].word, "??? : %i", sprite[selection].rank);
                 
    sprintf( text[19].word, "onCreate : %i", sprite[selection].onCreate ); 

    sprintf( text[20].word, "Type : [%i]", sprite[selection].onCreate_action);        
 
                
    sprintf( text[21].word, "Light : %.1f", sprite[selection].light); 

    
    sprintf( text[22].word, "Global : %i", sprite[selection].global_flag); 
    
    if( mode == POINT_MODE )    
    {
        sprintf( text[10].word, "Type : %i", points[pt_selection].c1);
      
       sprintf( text[12].word, "??? : %i", points[pt_selection].c3); 

        sprintf( text[13].word, "??? : %i", points[pt_selection].c4);
		  
        sprintf( text[14].word, "");
        sprintf( text[15].word, "");        
        sprintf( text[16].word, "");    
        sprintf( text[17].word, "");
        sprintf( text[18].word, "");
        sprintf( text[19].word, "");        
        sprintf( text[20].word, "");    
        sprintf( text[21].word, ""); 
        sprintf( text[22].word, "");         
    }     
    if( mode == NODES)
    {
        
        sprintf( text[10].word, "c1 : %i", nodes[nde_selection].c1);    
        sprintf( text[11].word, "c2 : %i", nodes[nde_selection].c2);
        sprintf( text[12].word, "c3 : %i", nodes[nde_selection].c3);
        sprintf( text[13].word, "c4 : %i", nodes[nde_selection].c4);          
        sprintf( text[14].word, "");
        sprintf( text[15].word, "");         
        sprintf( text[16].word, "");    
        sprintf( text[17].word, "");
        sprintf( text[18].word, "");
        sprintf( text[19].word, "");        
        sprintf( text[20].word, "");    
        sprintf( text[21].word, "");   
        sprintf( text[22].word, "");       
    } 
  
    }                   
 

     
}

void Draw_Hud(int index)
{
     
    float avR = fade, avG = fade, avB = fade;     
    float atestX = 0.0f, atestY = 0.0f;
    float atestX1 =0.0f, atestY1 = 0.0f;
    int atemp=0;
    int atemp1=0; 
    int atemp2=0;
    int atemp3=0;
    float off_set = 0.0f;
                
    avR = fade, avG = fade, avB = fade;
       
	if(index >= 0 && index < TOTAL_NO_HUD)
    if(game_mode != NORM && (game_mode == WALK || game_mode == WORLD || game_mode == CINE || game_mode == FRONT)) // Draw the hand of god
    if(hud[index].alpha != 0.0 || mode)
    {   
#ifdef SATURN
            VG_SATURN_PROFILE_COUNT_HUD_SPRITE();
#endif
                       
            display = hud[index];    
                           
            // Animated Texture
			if( display.id >= 0 && display.id < 200)
			if( display.fx_id >= 0 && display.fx_id < 75)
            if ( texture_fx[display.id] == 2 || texture_fx[display.id] == 3 )
            { 

                atemp = 0;
                atemp1 = 0;

                if(a_texture[display.fx_id].column == 0)
                    a_texture[display.fx_id].column = 1;
                
                // Calculate X-texture co-ords                
                atemp = display.frame;

				if(a_texture[display.fx_id].column > 0)
	                atemp1 = a_texture[display.fx_id].frames/a_texture[display.fx_id].column; // 16
                
				if(atemp1 > 0)
					atemp = (atemp % atemp1); // no / 16
                                
                if(atemp1 != 0)
                	atestX1 = 1.0f / atemp1; // 0.0025 etc

                atestX = atestX1 * atemp; 

                // Calculate Y-texture co-ords
                atemp = display.frame;

				if(a_texture[display.fx_id].column > 0)
                	atemp1 = a_texture[display.fx_id].frames/a_texture[display.fx_id].column; // 16
                
                if(atemp1 != 0)
                	atemp = atemp / atemp1;  // Gets row number 0 - column 
                
                atemp++;

                if( a_texture[display.fx_id].column == 1)
                {
                    atestY = 1.0f;
                    atestY1 = 0.0f;
                }                  
                
                if( a_texture[display.fx_id].column == 2)
                switch(atemp)
                {
                    case 1:        
                        atestY = 1.0f;
                        atestY1 = 0.5f;
                    break;
                    case 2:        
                        atestY = 0.5f;
                        atestY1 = 0.0f;
                    break;
                }      
                if( a_texture[display.fx_id].column == 4 )
                switch(atemp)
                {
                            
                    case 1:        
                        atestY = 1.0f;
                        atestY1 = 0.75f;
                    break;
                    case 2:        
                        atestY = 0.75f;
                        atestY1 = 0.5f;
                    break;
                    case 3:        
                        atestY = 0.5f;
                        atestY1 = 0.25f;
                    break;
                    case 4:        
                        atestY = 0.25f;
                        atestY1 = 0.0f;
                    break;
                    
                } 
                if( a_texture[display.fx_id].column == 8 )
                switch(atemp) 
                {
                    case 1:        
                        atestY = 0.9999f;
                        atestY1 = 0.875f;
                    break; 
                    case 2:        
                        atestY = 0.8749f;
                        atestY1 = 0.750f;
                    break;
                    case 3:        
                        atestY = 0.7499f;
                        atestY1 = 0.625f;
                    break;
                    case 4:        
                        atestY = 0.6249f;
                        atestY1 = 0.500f;
                    break;
                    case 5:        
                        atestY = 0.4999f;
                        atestY1 = 0.375f;
                    break;
                    case 6:        
                        atestY = 0.3749f;
                        atestY1 = 0.250f;
                    break;
                    case 7:        
                        atestY = 0.2499f;
                        atestY1 = 0.125f;
                    break;                     
                    case 8:        
                        atestY = 0.1249f;
                        atestY1 = 0.000f;
                    break;                    
                }      

			#if IS_USING_DIRECTX == 1  
			    if(RENDERER == RENDER_DIRECTX)
				if(display.alpha != 0.0)                      
				{ 
#ifdef XB1
					Set_Vertex_Buffer(index, (int)(avR * 255), (int)(avG * 255), (int)(avB * 255), display.alpha, false, false);

					// select the vertex buffer to display
					//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

					D3DXMatrixTranslation(&matTranslate, display.x + (display.width / 2), display.y + (display.height / 2), 0.0f);
					D3DXMatrixScaling(&matScale, display.width, display.height, 1.0f);
					D3DXMATRIX matViewFinishedTemp;
					D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matScale);
					D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp, &matTranslate);
					//matViewFinished = (matIdentity * matScale * matTranslate);

					// set the texture    
					if (display.id >= 0 && display.id < 100)
					{
						currentSetTexture = texture[display.id].tex;
						//currentSetSampler = texture[display.id].sampler;
					}
					//d3ddev->SetTexture(0, texture[display.id]);  

					D3DXSetTransform(&D3DTS_WORLD, &matViewFinished);

					D3DXMATRIX globalMTX;
					D3DXMatrixMultiply(&matViewFinishedTemp, &D3DTS_PROJECTION, &D3DTS_VIEW);
					D3DXMatrixMultiply(&globalMTX, &matViewFinishedTemp, &D3DTS_WORLD);

					for (int vtx_count = 0; vtx_count < 4; vtx_count++)
					{
						D3DXVECTOR3 temp;
						temp.x = global_t_vert[vtx_count].x;
						temp.y = global_t_vert[vtx_count].y;
						temp.z = global_t_vert[vtx_count].z;
						D3DXVECTOR3 res;
						D3DXVec3Project(&res, &temp, &D3DTS_PROJECTION, &D3DTS_VIEW, &D3DTS_WORLD);

						global_t_vert[vtx_count].x = res.x*1920.0f;
						global_t_vert[vtx_count].y = res.y*1080.0f;
						global_t_vert[vtx_count].z = res.z;

						//printf("HUD QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
					}
					
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[2].x, global_t_vert[2].y }, SDL_Color{ global_t_vert[2].color.r, global_t_vert[2].color.g, global_t_vert[2].color.b, global_t_vert[2].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ global_t_vert[2].u, 1.0f - global_t_vert[2].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[3].x, global_t_vert[3].y }, SDL_Color{ global_t_vert[3].color.r, global_t_vert[3].color.g, global_t_vert[3].color.b, global_t_vert[3].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ global_t_vert[3].u, 1.0f - global_t_vert[3].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[0].x, global_t_vert[0].y }, SDL_Color{ global_t_vert[0].color.r, global_t_vert[0].color.g, global_t_vert[0].color.b, global_t_vert[0].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ global_t_vert[0].u, 1.0f - global_t_vert[0].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[1].x, global_t_vert[1].y }, SDL_Color{ global_t_vert[1].color.r, global_t_vert[1].color.g, global_t_vert[1].color.b, global_t_vert[1].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ global_t_vert[1].u, 1.0f - global_t_vert[1].v } });
					

					SDL_RenderGeometry(pRenderer, currentSetTexture, VTXsdl.data(), VTXsdl.size(), IDXsdl.data(), IDXsdl.size());
					VTXsdl.clear();
#elif PS4
					Set_Vertex_Buffer(index, (int)(avR*255), (int)(avG*255), (int)(avB*255), display.alpha, false, false);   
         
					// select the vertex buffer to display
					//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
       
					D3DXMatrixTranslation(&matTranslate, display.x + (display.width/2),display.y + (display.height/2), 0.0f);
					D3DXMatrixScaling(&matScale, display.width, display.height, 1.0f); 
					D3DXMATRIX matViewFinishedTemp;
					D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matScale);
					D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp, &matTranslate);
					//matViewFinished = (matIdentity * matScale * matTranslate);
         
					// set the texture    
					if(display.id >= 0 && display.id < 100)
						currentSetTexture = texture[display.id].tex;
						//d3ddev->SetTexture(0, texture[display.id]);  
                
					D3DXSetTransform (&D3DTS_WORLD, &matViewFinished );

					D3DXMATRIX globalMTX;
					D3DXMatrixMultiply(&matViewFinishedTemp, &D3DTS_PROJECTION, &D3DTS_VIEW);
					D3DXMatrixMultiply(&globalMTX, &matViewFinishedTemp, &D3DTS_WORLD);

					for (int vtx_count = 0; vtx_count < 4; vtx_count++)
					{
						D3DXVECTOR3 temp;
						temp.x = global_t_vert[vtx_count].x;
						temp.y = global_t_vert[vtx_count].y;
						temp.z = global_t_vert[vtx_count].z;
						D3DXVECTOR3 res;
						D3DXVec3Project(&res, &temp, &D3DTS_PROJECTION, &D3DTS_VIEW, &D3DTS_WORLD);

						global_t_vert[vtx_count].x = res.x;
						global_t_vert[vtx_count].y = res.y;
						global_t_vert[vtx_count].z = res.z;

					    //printf("HUD QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
					}
        
					//NEED TO DRAW PS4
					_Application.getGraphics()->createIndexBuffer(&i_buffer, (sizeof(uint16_t) * 6));
					_Application.getGraphics()->createVertexBuffer(&v_buffer, (sizeof(TexturedVertex) * 4));

					indexData = (uint16_t*)i_buffer->beginWrite();
					vertexData = (TexturedVertex*)v_buffer->beginWrite();

					/*for (int vtx_count = 0; vtx_count < 4; vtx_count++)
					{
						vertexData[vtx_count].position = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[vtx_count].x, global_t_vert[vtx_count].y);
						vertexData[vtx_count].texcoord = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
						printf("DETAIL %d -> %f %f uv : %f %f\n", vtx_count, global_t_vert[vtx_count].x, global_t_vert[vtx_count].y, global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
					}*/

					vertexData[0].position = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[2].x, global_t_vert[2].y);
					vertexData[1].position = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[3].x, global_t_vert[3].y);
					vertexData[2].position = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[0].x, global_t_vert[0].y);
					vertexData[3].position = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[1].x, global_t_vert[1].y);

					vertexData[0].texcoord = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[2].u, 1.0f - global_t_vert[2].v);
					vertexData[1].texcoord = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[3].u, 1.0f - global_t_vert[3].v);
					vertexData[2].texcoord = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[0].u, 1.0f - global_t_vert[0].v);
					vertexData[3].texcoord = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[1].u, 1.0f - global_t_vert[1].v);

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
						1.0, VerticesStock, i_buffer, 6, colorMAIN, sce::Vectormath::Simd::Aos::Vector4(0, 0, 0, 0), currentSetTexture, 1);

					//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

					//if(flash_render == true)
					//	d3ddev->SetRenderState(D3DRS_FOGENABLE, false);
					sce::SampleUtil::destroy(i_buffer);
					sce::SampleUtil::destroy(v_buffer);
					//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

#endif
        
				}
			#endif

			if(RENDERER == RENDER_OPENGL)
			{
#if defined SWITCH || defined DREAMCAST
            glPushMatrix();     
            
            glTranslatef(display.x + (display.width/2),display.y + (display.height/2),0.0f); // This pretty much just means you load in your quad's center.
            glScalef( display.width, display.height, 0.0f);   // You load your object's X and Y dimensions in here.
            
            Set_Values(-1, -1, avR, avG, avB, display.alpha, -1, -1);     
                       
            glColor4fv(&Gcolor[0]); 
            	        
			if(display.id >= 0 && display.id < 100)
				glBindTexture(GL_TEXTURE_2D, texID[(display.id)]);     		

	        glBegin(GL_QUADS);
   
					if(display.fx_id >= 0 && display.fx_id < 75)
                    if( a_texture[display.fx_id].column == 0 )
                    {
 
                        Set_Values(-0.5, -0.5, -1, -1, -1, -1, atestX, display.v[0]);
                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        
                        Set_Values( 0.5, -0.5, -1, -1, -1, -1, atestX + atestX1, display.v[1]);
	                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        		
                        Set_Values( 0.5,  0.5, -1, -1, -1, -1, atestX + atestX1, display.v[2]);
	                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        	
                        Set_Values(-0.5,  0.5, -1, -1, -1, -1, atestX, display.v[3]);
                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);

                    }
                    else
                    {
                        Set_Values(-0.5, -0.5, -1, -1, -1, -1, atestX, atestY1);
                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        	
                        Set_Values( 0.5, -0.5, -1, -1, -1, -1, atestX + atestX1, atestY1);
	                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                    
                        Set_Values( 0.5,  0.5, -1, -1, -1, -1, atestX + atestX1, atestY);
	                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        	
                        Set_Values(-0.5,  0.5, -1, -1, -1, -1, atestX, atestY);
                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        
                    }

            glEnd();
           
            glPopMatrix();
#endif
			}
                            
            }
            else
            {      

			#if IS_USING_DIRECTX == 1  
			    if(RENDERER == RENDER_DIRECTX)
				if(display.alpha != 0.0)                      
				{ 
#ifdef XB1
					Set_Vertex_Buffer(index, (int)(avR * 255), (int)(avG * 255), (int)(avB * 255), display.alpha, false, false);

					// select the vertex buffer to display
					//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

					D3DXMatrixTranslation(&matTranslate, display.x + (display.width / 2), display.y + (display.height / 2), 0.0f);
					D3DXMatrixScaling(&matScale, display.width, display.height, 1.0f);

					D3DXMATRIX matViewFinishedTemp;
					D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matScale);
					D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp, &matTranslate);
					//matViewFinished = (matIdentity * matScale * matTranslate);

					// set the texture    
					if (display.id >= 0 && display.id < 100)
					{
						currentSetTexture = texture[display.id].tex;
						//currentSetSampler = texture[display.id].sampler;
					}
					//d3ddev->SetTexture(0, texture[display.id]);  


					D3DXSetTransform(&D3DTS_WORLD, &matViewFinished);

					D3DXMATRIX globalMTX;
					D3DXMatrixMultiply(&matViewFinishedTemp, &D3DTS_PROJECTION, &D3DTS_VIEW);
					D3DXMatrixMultiply(&globalMTX, &matViewFinishedTemp, &D3DTS_WORLD);

					for (int vtx_count = 0; vtx_count < 4; vtx_count++)
					{
						D3DXVECTOR3 temp;
						temp.x = global_t_vert[vtx_count].x;
						temp.y = global_t_vert[vtx_count].y;
						temp.z = global_t_vert[vtx_count].z;
						D3DXVECTOR3 res;
						D3DXVec3Project(&res, &temp, &D3DTS_PROJECTION, &D3DTS_VIEW, &D3DTS_WORLD);

						global_t_vert[vtx_count].x = res.x * 1920.0f;
						global_t_vert[vtx_count].y = res.y * 1080.0f;
						global_t_vert[vtx_count].z = res.z;

						//printf("HUD QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
					}

					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[2].x, global_t_vert[2].y }, SDL_Color{ global_t_vert[2].color.r, global_t_vert[2].color.g, global_t_vert[2].color.b, global_t_vert[2].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ global_t_vert[2].u, 1.0f - global_t_vert[2].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[3].x, global_t_vert[3].y }, SDL_Color{ global_t_vert[3].color.r, global_t_vert[3].color.g, global_t_vert[3].color.b, global_t_vert[3].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ global_t_vert[3].u, 1.0f - global_t_vert[3].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[0].x, global_t_vert[0].y }, SDL_Color{ global_t_vert[0].color.r, global_t_vert[0].color.g, global_t_vert[0].color.b, global_t_vert[0].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ global_t_vert[0].u, 1.0f - global_t_vert[0].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[1].x, global_t_vert[1].y }, SDL_Color{ global_t_vert[1].color.r, global_t_vert[1].color.g, global_t_vert[1].color.b, global_t_vert[1].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ global_t_vert[1].u, 1.0f - global_t_vert[1].v } });


					SDL_RenderGeometry(pRenderer, currentSetTexture, VTXsdl.data(), VTXsdl.size(), IDXsdl.data(), IDXsdl.size());

					VTXsdl.clear();
#elif PS4
					Set_Vertex_Buffer(index, (int)(avR*255), (int)(avG*255), (int)(avB*255), display.alpha, false, false);   
         
					// select the vertex buffer to display
					//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
       
					D3DXMatrixTranslation(&matTranslate, display.x + (display.width/2),display.y + (display.height/2), 0.0f);
					D3DXMatrixScaling(&matScale, display.width, display.height, 1.0f); 

					D3DXMATRIX matViewFinishedTemp;
					D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matScale);
					D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp, &matTranslate);
					//matViewFinished = (matIdentity * matScale * matTranslate);
         
					// set the texture    
					if(display.id >= 0 && display.id < 100)
						currentSetTexture = texture[display.id].tex;
						//d3ddev->SetTexture(0, texture[display.id]);  
						
                
					D3DXSetTransform (&D3DTS_WORLD, &matViewFinished );

					D3DXMATRIX globalMTX;
					D3DXMatrixMultiply(&matViewFinishedTemp, &D3DTS_PROJECTION, &D3DTS_VIEW);
					D3DXMatrixMultiply(&globalMTX, &matViewFinishedTemp, &D3DTS_WORLD);

					for (int vtx_count = 0; vtx_count < 4; vtx_count++)
					{
						D3DXVECTOR3 temp;
						temp.x = global_t_vert[vtx_count].x;
						temp.y = global_t_vert[vtx_count].y;
						temp.z = global_t_vert[vtx_count].z;
						D3DXVECTOR3 res;
						D3DXVec3Project(&res, &temp, &D3DTS_PROJECTION, &D3DTS_VIEW, &D3DTS_WORLD);

						global_t_vert[vtx_count].x = res.x;
						global_t_vert[vtx_count].y = res.y;
						global_t_vert[vtx_count].z = res.z;

						//printf("HUD 2 QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
					}
        
					//NEED TO DRAW PS4
					_Application.getGraphics()->createIndexBuffer(&i_buffer, (sizeof(uint16_t) * 6));
					_Application.getGraphics()->createVertexBuffer(&v_buffer, (sizeof(TexturedVertex) * 4));

					indexData = (uint16_t*)i_buffer->beginWrite();
					vertexData = (TexturedVertex*)v_buffer->beginWrite();

					/*for (int vtx_count = 0; vtx_count < 4; vtx_count++)
					{
						vertexData[vtx_count].position = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[vtx_count].x, global_t_vert[vtx_count].y);
						vertexData[vtx_count].texcoord = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
						printf("DETAIL %d -> %f %f uv : %f %f\n", vtx_count, global_t_vert[vtx_count].x, global_t_vert[vtx_count].y, global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
					}*/

					vertexData[0].position = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[2].x, global_t_vert[2].y);
					vertexData[1].position = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[3].x, global_t_vert[3].y);
					vertexData[2].position = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[0].x, global_t_vert[0].y);
					vertexData[3].position = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[1].x, global_t_vert[1].y);

					vertexData[0].texcoord = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[2].u, 1.0f - global_t_vert[2].v);
					vertexData[1].texcoord = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[3].u, 1.0f - global_t_vert[3].v);
					vertexData[2].texcoord = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[0].u, 1.0f - global_t_vert[0].v);
					vertexData[3].texcoord = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[1].u, 1.0f - global_t_vert[1].v);

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
						1.0, VerticesStock, i_buffer, 6, colorMAIN, sce::Vectormath::Simd::Aos::Vector4(0, 0, 0, 0), currentSetTexture, 1);

					//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

					//if(flash_render == true)
					//	d3ddev->SetRenderState(D3DRS_FOGENABLE, false);
					sce::SampleUtil::destroy(i_buffer);
					sce::SampleUtil::destroy(v_buffer);
					//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

#endif
        
				}
			#endif

			if(RENDERER == RENDER_OPENGL)
			{      
#if defined SWITCH || defined DREAMCAST
            glPushMatrix();    
           
            glTranslatef(display.x + (display.width/2),display.y + (display.height/2),0.0f); // This pretty much just means you load in your quad's center.
            glScalef( display.width, display.height, 0.0f);   // You load your object's X and Y dimensions in here.
  
        //    glColor4f(avR,avG,avB,display.alpha);    
      
			if(display.id >= 0 && display.id < 100)
			{
                Set_Values(-1, -1, avR, avG, avB, display.alpha, -1, -1);     
                glColor4fv(&Gcolor[0]);                 
  	            glBindTexture(GL_TEXTURE_2D, texID[(display.id)]);     		
			}

                        
            // Turn special blend on  
			if(display.id >= 0 && display.id < 200)
            if(texture_fx[display.id] == 5)
            {
                glBlendFunc(src_one, src_two);			// Enable Alpha Blending (disable alpha testing)
            }
 		
	        glBegin(GL_QUADS); 
	        
                Set_Values(-0.5, -0.5, -1, -1, -1, -1, display.u[0], display.v[0]);
                glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
                
                Set_Values( 0.5, -0.5, -1, -1, -1, -1, display.u[1], display.v[1]);
	            glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                	
	            Set_Values( 0.5,  0.5, -1, -1, -1, -1, display.u[2], display.v[2]);
	            glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                	
	            Set_Values(-0.5,  0.5, -1, -1, -1, -1, display.u[3], display.v[3]);
                glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                
            glEnd();
           
            glPopMatrix();
            	                    
            // Turn normal blend back on  
			if(display.id >= 0 && display.id < 200)
            if(texture_fx[display.id] == 5)
            {
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending (disable alpha testing)
            }
#endif
			} // if(RENDERER == RENDER_OPENGL)

            }

    }        
    
       
}

void Draw_New_Font(int i)
{

    // Font 
	void* pVoid;    // a void pointer 
    float testX = 0.0f, testY = 0.0f;
    float testX1 =0.0f, testY1 = 0.0f;
    float is_slim_lttr =0.0f, slim_width=0.0f;
    float addX = 0.0f, addY = 0.0f, Yamount=0.0f;     
     
    float vR = fade, vG = fade, vB = fade;
    
    bool scroll_text = false;
    bool p_test=false;
    bool on_paper=false;
    bool dont_draw=false;
    int letters = 0;     
    int temp=0;
	int the_letter=0;

	if(i < 0 || i >= TOTAL_TEXT) 
		return;

	display_font = new_counter[i]; 
	 
	if(display_font.word[0] == '\0' || display_font.alpha <= 0.0f)
		return;

	display_font.width = 0.05f;
	display_font.height = 0.05f;

    letters = strlen(display_font.word);
	 
	if(letters >= 1024)   
		return;

	scroll_text = false; 

	if(display_font.scroll_this == true)
	{

		if(scroll_txt_active == true)  
			scroll_text = true;
        
		if( scroll_text == true )  
			letters = scroll_index+1; 
	}

	if(letters < 1024)
    for(int loop=0;loop<letters;loop++)
    if(display_font.word[loop] != -1)
    { 
		  
		if(display_font.right == false)  
			the_letter = loop;   
		else 
		{
			the_letter = loop - (letters-1);
			the_letter *= -1;
		}

        // Newline  
		if(the_letter >= 0 && the_letter < 1024)
        if(display_font.word[the_letter] == '^')  
        {
			addX = -0.026f; 
			  
			if(display_font.type == 0)
				addY -= display_font.height - 0.005f;
			if(display_font.type == 1)  
				addY -= display_font.height - 0.01f; 
			if(display_font.type == 2) 
				addY -= display_font.height + 0.02f;  
        } 
		    
		slim_width = 0.026f; 

		if(the_letter >= 0 && the_letter < 1024)
        if(scroll_text == true && loop == scroll_index )
            GetNewFont(testX, testY, 'Ë', slim_width, i, on_paper, false, game_mode);
        else    
			GetNewFont(testX, testY, display_font.word[the_letter], slim_width, i, on_paper, false, game_mode);
     
        is_slim_lttr = 0.0625f;
		 
        testX *= 0.0625f; 
		 
        testY1 = 0.0625f;   
		   
		testY *= 0.0625f; 

        if(display_font.alpha != 0.0f) 
        {
#ifdef SATURN
            VG_SATURN_PROFILE_COUNT_FONT_GLYPH();
#endif
			#if IS_USING_DIRECTX == 1  
			    if(RENDERER == RENDER_DIRECTX) 
				{ 
#ifdef XB1
					//SAFE_RELEASE(v_buffer);  
					//sce::SampleUtil::destroy(v_buffer);

					// create a vertex buffer interface called v_buffer
					/*d3ddev->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
					0,
					CUSTOMFVF,
					D3DPOOL_MANAGED,
					&v_buffer,
					NULL);*/
					//_Application.getGraphics()->createVertexBuffer(&v_buffer, (sizeof(TexturedVertex) * 4));
					ARGB_COLOR temp_col = { 255, (unsigned char)(vR * 255), (unsigned char)(vG * 255), (unsigned char)(vB * 255) };
					CUSTOMVERTEX t_vert[] =
					{

						// square 1      
						{ -0.5,  0.5,  0.0, temp_col, testX, testY + testY1, },
						{ 0.5,  0.5,  0.0, temp_col, testX + is_slim_lttr, testY + testY1, },
						{ -0.5, -0.5,  0.0, temp_col, testX, testY, },
						{ 0.5, -0.5,  0.0, temp_col, testX + is_slim_lttr, testY, },

					};

					// lock v_buffer and load the vertices into it
					/*v_buffer->Lock(0, 0, (void**)&pVoid, 0);
					memcpy(pVoid, t_vert, sizeof(t_vert));
					v_buffer->Unlock();*/

					//colorMAIN = sce::Vectormath::Simd::Aos::Vector4(vR, vG, vB, 1.0f);
					//vertexData = (TexturedVertex*)v_buffer->beginWrite();
					//for (int i = 0; i < 4; i++)
					//{
					//	vertexData[i].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].x, t_vert[i].y);
					//	vertexData[i].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].u, t_vert[i].v);
					//}

					//memcpy(pVoid, t_vert, sizeof(t_vert));
					//v_buffer->endWrite();


					// select the vertex buffer to display
					//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

					D3DXMatrixTranslation(&matTranslate, (display_font.x + addX), (display_font.y + addY), 0.0f);
					D3DXMatrixScaling(&matScale, display_font.width, display_font.height, 1.0f);

					D3DXMATRIX matViewFinishedTemp;
					D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matScale);
					D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp, &matTranslate);
					//matViewFinished = (matIdentity * matScale * matTranslate);

					// set the texture    
					if (display_font.id >= 0 && display_font.id < 100)
					{
						currentSetTexture = texture[display_font.id].tex;
						//currentSetSampler = texture[display_font.id].sampler;
					}
					//d3ddev->SetTexture(0, texture[display_font.id]);  

					D3DXSetTransform(&D3DTS_WORLD, &matViewFinished);

					D3DXMATRIX globalMTX;
					D3DXMatrixMultiply(&matViewFinishedTemp, &D3DTS_PROJECTION, &D3DTS_VIEW);
					D3DXMatrixMultiply(&globalMTX, &matViewFinishedTemp, &D3DTS_WORLD);

					for (int vtx_count = 0; vtx_count < 4; vtx_count++)
					{
						D3DXVECTOR3 temp;
						temp.x = t_vert[vtx_count].x;
						temp.y = t_vert[vtx_count].y;
						temp.z = t_vert[vtx_count].z;
						D3DXVECTOR3 res;
						D3DXVec3Project(&res, &temp, &D3DTS_PROJECTION, &D3DTS_VIEW, &D3DTS_WORLD);

						t_vert[vtx_count].x = res.x * 1920.0f;
						t_vert[vtx_count].y = res.y * 1080.0f;
						t_vert[vtx_count].z = res.z;

						//printf("HUD QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
					}

					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{t_vert[2].x, t_vert[2].y }, SDL_Color{ t_vert[2].color.r, t_vert[2].color.g, t_vert[2].color.b, t_vert[2].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ t_vert[2].u, 1.0f - t_vert[2].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{t_vert[3].x, t_vert[3].y }, SDL_Color{ t_vert[3].color.r, t_vert[3].color.g, t_vert[3].color.b, t_vert[3].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ t_vert[3].u, 1.0f - t_vert[3].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{t_vert[0].x, t_vert[0].y }, SDL_Color{ t_vert[0].color.r, t_vert[0].color.g, t_vert[0].color.b, t_vert[0].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ t_vert[0].u, 1.0f - t_vert[0].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{t_vert[1].x, t_vert[1].y }, SDL_Color{ t_vert[1].color.r, t_vert[1].color.g, t_vert[1].color.b, t_vert[1].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ t_vert[1].u, 1.0f - t_vert[1].v } });


					SDL_RenderGeometry(pRenderer, currentSetTexture, VTXsdl.data(), VTXsdl.size(), IDXsdl.data(), IDXsdl.size());

					VTXsdl.clear();
#elif PS4
         
					//SAFE_RELEASE(v_buffer);  
					//sce::SampleUtil::destroy(v_buffer);
   
					// create a vertex buffer interface called v_buffer
					/*d3ddev->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
											   0,
											   CUSTOMFVF,
											   D3DPOOL_MANAGED,
											   &v_buffer,
											   NULL);*/
					//_Application.getGraphics()->createVertexBuffer(&v_buffer, (sizeof(TexturedVertex) * 4));
					 
					CUSTOMVERTEX t_vert[] =        
					{          

					  // square 1      
					  { -0.5,  0.5,  0.0, _Application.ARGBColorToUINT(255, (int)(vR*255), (int)(vG*255), (int)(vB*255)), testX, testY + testY1, },
					  {  0.5,  0.5,  0.0, _Application.ARGBColorToUINT(255, (int)(vR*255), (int)(vG*255), (int)(vB*255)), testX + is_slim_lttr, testY + testY1, },
					  { -0.5, -0.5,  0.0, _Application.ARGBColorToUINT(255, (int)(vR*255), (int)(vG*255), (int)(vB*255)), testX, testY, },
					  {  0.5, -0.5,  0.0, _Application.ARGBColorToUINT(255, (int)(vR*255), (int)(vG*255), (int)(vB*255)), testX + is_slim_lttr, testY, },

					};      

					// lock v_buffer and load the vertices into it
					/*v_buffer->Lock(0, 0, (void**)&pVoid, 0);
					memcpy(pVoid, t_vert, sizeof(t_vert));
					v_buffer->Unlock();*/   

					colorMAIN = sce::Vectormath::Simd::Aos::Vector4(vR, vG, vB, 1.0f);
					//vertexData = (TexturedVertex*)v_buffer->beginWrite();
					//for (int i = 0; i < 4; i++)
					//{
					//	vertexData[i].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].x, t_vert[i].y);
					//	vertexData[i].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].u, t_vert[i].v);
					//}

					//memcpy(pVoid, t_vert, sizeof(t_vert));
					//v_buffer->endWrite();

         
					// select the vertex buffer to display
					//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
       
					D3DXMatrixTranslation(&matTranslate, (display_font.x + addX), (display_font.y + addY), 0.0f);
					D3DXMatrixScaling(&matScale, display_font.width, display_font.height, 1.0f);

					D3DXMATRIX matViewFinishedTemp;
					D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matScale);
					D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp, &matTranslate);
					//matViewFinished = (matIdentity * matScale * matTranslate);
         
					// set the texture    
					if (display_font.id >= 0 && display_font.id < 100)
						currentSetTexture = texture[display_font.id].tex;
						//d3ddev->SetTexture(0, texture[display_font.id]);  
                
					D3DXSetTransform(&D3DTS_WORLD, &matViewFinished );

					D3DXMATRIX globalMTX;
					D3DXMatrixMultiply(&matViewFinishedTemp, &D3DTS_PROJECTION, &D3DTS_VIEW);
					D3DXMatrixMultiply(&globalMTX, &matViewFinishedTemp, &D3DTS_WORLD);

					for (int vtx_count = 0; vtx_count < 4; vtx_count++)
					{
						D3DXVECTOR3 temp;
						temp.x = t_vert[vtx_count].x;
						temp.y = t_vert[vtx_count].y;
						temp.z = t_vert[vtx_count].z;
						D3DXVECTOR3 res;
						D3DXVec3Project(&res, &temp, &D3DTS_PROJECTION, &D3DTS_VIEW, &D3DTS_WORLD);

						t_vert[vtx_count].x = res.x;
						t_vert[vtx_count].y = res.y;
						t_vert[vtx_count].z = res.z;

						//printf("QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count==3?" \n" : "  ");
					}
					
					

					//NEED TO DRAW PS4
					_Application.getGraphics()->createIndexBuffer(&i_buffer, (sizeof(uint16_t) * 6));
					_Application.getGraphics()->createVertexBuffer(&v_buffer, (sizeof(TexturedVertex) * 4));

					indexData = (uint16_t*)i_buffer->beginWrite();
					vertexData = (TexturedVertex*)v_buffer->beginWrite();

					/*for (int vtx_count = 0; vtx_count < 4; vtx_count++)
					{
						vertexData[vtx_count].position = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[vtx_count].x, global_t_vert[vtx_count].y);
						vertexData[vtx_count].texcoord = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
						printf("DETAIL %d -> %f %f uv : %f %f\n", vtx_count, global_t_vert[vtx_count].x, global_t_vert[vtx_count].y, global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
					}*/

					vertexData[0].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[2].x, t_vert[2].y);
					vertexData[1].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[3].x, t_vert[3].y);
					vertexData[2].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[0].x, t_vert[0].y);
					vertexData[3].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[1].x, t_vert[1].y);

					vertexData[0].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[2].u, 1.0f - t_vert[2].v);
					vertexData[1].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[3].u, 1.0f - t_vert[3].v);
					vertexData[2].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[0].u, 1.0f - t_vert[0].v);
					vertexData[3].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[1].u, 1.0f - t_vert[1].v);

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
						1.0, VerticesStock, i_buffer, 6, colorMAIN, sce::Vectormath::Simd::Aos::Vector4(0, 0, 0, 0), currentSetTexture, 1);

					//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

					//if(flash_render == true)
					//	d3ddev->SetRenderState(D3DRS_FOGENABLE, false);
					sce::SampleUtil::destroy(i_buffer);
					sce::SampleUtil::destroy(v_buffer);
					//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

#endif
        
				}
			#endif
#if defined SWITCH || defined DREAMCAST
			if(RENDERER == RENDER_OPENGL)                      
			{

				glPushMatrix();      
            
				glTranslatef( display_font.x + addX, display_font.y + addY, 0.0f ); // This pretty much just means you load in your quad's center.
				glScalef( display_font.width, display_font.height, 0.0f);   // You load your object's X and Y dimensions in here.
            
				Set_Values(-1, -1, vR, vG, vB, display_font.alpha, -1, -1);     
                       
				glColor4fv(&Gcolor[0]);  
         
				if(display_font.id >= 0 && display_font.id < 100)
					glBindTexture(GL_TEXTURE_2D, texID[(display_font.id)]);     		

				glBegin(GL_QUADS);
	        
					Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, testX, testY);           
					glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
                
					Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, testX + is_slim_lttr, testY);
					glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	            
					Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, testX + is_slim_lttr, testY + testY1);
					glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	            
					Set_Values(-0.5f,  0.5f, -1, -1, -1, -1, testX, testY + testY1);
					glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                
				glEnd();  

				glPopMatrix();       

			}  
#endif
            
			if(display_font.type == 1)
			{
				if(display_font.right == false)
					addX += 0.023f;         
				else
					addX -= 0.023f;         
			}
			else
			{
				if(display_font.right == false)
					addX += 0.02825f;        
				else
					addX -= 0.02825f;        
			}

		}


	} // End of loop

}

void Draw_Font(int i)
{

    // Font 
	void* pVoid;    // a void pointer 
    float testX = 0.0f, testY = 0.0f;
    float testX1 =0.0f, testY1 = 0.0f;
    float is_slim_lttr =0.0f, slim_width=0.0f;
    float addX = 0.0f, addY = 0.0f, Yamount=0.0f;     
     
    float vR = fade, vG = fade, vB = fade;
    
    bool scroll_text = false;
    bool p_test=false;
    bool on_paper=false;
    bool dont_draw=false;
    int letters = 0;     
    int temp=0;
	 
	if( i >= 0 && i < TOTAL_TEXT)   
	{      
		 
      
    if(quit_active == false)  
    if((game_mode == GAME) || (game_mode == WALK) || (game_mode == FRONT) || (game_mode == WORLD) ) 
    { 
      
    if(mode)  
        display_font = text[i];
    else
        if(game_mode == GAME || game_mode == WALK || (game_mode == FRONT) || (game_mode == WORLD))
            display_font = counter[i];
        
    if(display_font.word[0] == '\0' || (display_font.alpha <= 0.0f && !mode))
        return;

    addX = 0.0f;
    Yamount = 0.0f;
    
    if(g_type != G_STS)   
        addY = 0.0f;  
    else
        addY = display_font.height;
    
    if( mode )
    {  
        vR = 1.0f;  
        vG = 1.0f; 
        vB = 1.0f;
    } 

    scroll_text = false; 
    
    letters = strlen(display_font.word);
    
	if(letters >= 1024)
		return; 

    if(scroll_txt_active == true)  
        scroll_text = true;
        
    if( scroll_text == true )  
        letters = scroll_index+1; 

    temp = 0;  

    for(int loop=0;loop<letters;loop++)
	if(loop >= 0 && loop < 1024)
    if(display_font.word[loop] != -1)
    { 
 
        p_test = false; 

        // Newline  
		if(loop >= 0 && loop < 1024)
        if(display_font.word[loop] == '^') 
        {
            addX = 0.00f - (display_font.width*2.15f);
            
            slim_width = 0.0f;  
            
              if(game_mode != FRONT) 
              {   
				
				if( (i == 1 || i == 2) && !mode)
	                addY -= display_font.height + 0.057f;
				else
	                addY -= display_font.height + 0.03f;
              }
              else 
              {
                   
                if(i == 1 || i == 0 || i == 11 || i == 13 || ( i == 2 && episode == 1 && (scene == 26 || scene == 52) ) )
                { 
                  if(episode == 1 && (scene == 26 || scene == 52) )
                      addY -= display_font.height + 0.08f;
                  else   
                      addY -= display_font.height + 0.05f;
                }
                else                 
                  addY -= display_font.height + 0.03f;
                
                if(i == 13) // File select screen
                    addY -= 0.02f; 
                
              } 
                 
        }  
        
        if( display_font.word[loop] == '%')
        {
            addX = 0.00f; 
            addY = display_font.height - 0.16f;
        }  
         
        // Brown numbers for stats... 
        if(i == 1 || i == 2 || i == 3 || i == 11)  
            on_paper = true;
        else
            on_paper = false;
         
        if(game_mode == FRONT) 
            on_paper = false;   
      
        if(scroll_text == true && loop == scroll_index )
            GetFont(testX, testY, '@', slim_width, i, on_paper, p_test, game_mode);
        else             
            GetFont(testX, testY, display_font.word[loop], slim_width, i, on_paper, p_test, game_mode);
        
        if(temp == 1 && loop == 0)
            GetFont(testX, testY, '_', slim_width, i, on_paper, p_test, game_mode);

        is_slim_lttr = 0.0625f;

        testX *= 0.0625f;

        testY1 = 0.0625f;   

		testY *= 0.0625f; 

        if(mode || i == 6) // 6 == Debug text 
		{
#if defined SWITCH || defined DREAMCAST
			if(RENDERER == RENDER_OPENGL)
				Zoom(101);// 101  
#endif
			if(RENDERER == RENDER_DIRECTX) 
				ZoomDX(TYPE_MODE_TEXT_DEBUG);// 101   
		}
        
        if(display_font.alpha != 0.0f)
        {
#ifdef SATURN
            VG_SATURN_PROFILE_COUNT_FONT_GLYPH();
#endif

			#if IS_USING_DIRECTX == 1  
			    if(RENDERER == RENDER_DIRECTX) 
				{ 
#ifdef XB1
					//sce::SampleUtil::destroy(v_buffer);

					// create a vertex buffer interface called v_buffer
					/*d3ddev->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
					0,
					CUSTOMFVF,
					D3DPOOL_MANAGED,
					&v_buffer,
					NULL);
					*/
					//_Application.getGraphics()->createVertexBuffer(&v_buffer, (sizeof(TexturedVertex) * 4));
					ARGB_COLOR temp_col = { 255, (unsigned char)(vR * 255), (unsigned char)(vG * 255), (unsigned char)(vB * 255) };
					CUSTOMVERTEX t_vert[] =
					{

						// square 1      
						{ -0.5,  0.5,  0.0, temp_col, testX, testY + testY1, },
						{ 0.5,  0.5,  0.0, temp_col, testX + is_slim_lttr, testY + testY1, },
						{ -0.5, -0.5,  0.0,temp_col, testX, testY, },
						{ 0.5, -0.5,  0.0, temp_col, testX + is_slim_lttr, testY, },

					};

					//colorMAIN = sce::Vectormath::Simd::Aos::Vector4(vR, vG, vB, 1.0f);

					// lock v_buffer and load the vertices into it
					/*v_buffer->Lock(0, 0, (void**)&pVoid, 0);
					memcpy(pVoid, t_vert, sizeof(t_vert));
					v_buffer->Unlock();*/


					// select the vertex buffer to display
					//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

					D3DXMatrixTranslation(&matTranslate, (display_font.x + addX) + (-(display_font.width)) + (display_font.width / 2), (display_font.y + addY) + (-(display_font.height)) + (display_font.height), 0.0f);
					D3DXMatrixScaling(&matScale, display_font.width * 2, display_font.height * 2, 1.0f);

					D3DXMATRIX matViewFinishedTemp;
					D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matScale);
					D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp, &matTranslate);
					//matViewFinished = (matIdentity * matScale * matTranslate);

					// set the texture    
					if (display_font.id >= 0 && display_font.id < 100)
					{
						currentSetTexture = texture[display_font.id].tex;
						//currentSetSampler = texture[display_font.id].sampler;
					}
					//d3ddev->SetTexture(0, texture[display_font.id]);  

					D3DXSetTransform(&D3DTS_WORLD, &matViewFinished);

					D3DXMATRIX globalMTX;
					D3DXMatrixMultiply(&matViewFinishedTemp, &D3DTS_PROJECTION, &D3DTS_VIEW);
					D3DXMatrixMultiply(&globalMTX, &matViewFinishedTemp, &D3DTS_WORLD);

					for (int vtx_count = 0; vtx_count < 4; vtx_count++)
					{
						D3DXVECTOR3 temp;
						temp.x = t_vert[vtx_count].x;
						temp.y = t_vert[vtx_count].y;
						temp.z = t_vert[vtx_count].z;
						D3DXVECTOR3 res;
						D3DXVec3Project(&res, &temp, &D3DTS_PROJECTION, &D3DTS_VIEW, &D3DTS_WORLD);

						t_vert[vtx_count].x = res.x * 1920.0f;
						t_vert[vtx_count].y = res.y * 1080.0f;
						t_vert[vtx_count].z = res.z;

						//printf("HUD QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
					}

					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{t_vert[2].x, t_vert[2].y }, SDL_Color{ t_vert[2].color.r, t_vert[2].color.g, t_vert[2].color.b, t_vert[2].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ t_vert[2].u, 1.0f - t_vert[2].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{t_vert[3].x, t_vert[3].y }, SDL_Color{ t_vert[3].color.r, t_vert[3].color.g, t_vert[3].color.b, t_vert[3].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ t_vert[3].u, 1.0f - t_vert[3].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{t_vert[0].x, t_vert[0].y }, SDL_Color{ t_vert[0].color.r, t_vert[0].color.g, t_vert[0].color.b, t_vert[0].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ t_vert[0].u, 1.0f - t_vert[0].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{t_vert[1].x, t_vert[1].y }, SDL_Color{ t_vert[1].color.r, t_vert[1].color.g, t_vert[1].color.b, t_vert[1].color.a }, SDL_Color{ 0, 0, 0, 0 },
						SDL_FPoint{ t_vert[1].u, 1.0f - t_vert[1].v } });


					SDL_RenderGeometry(pRenderer, currentSetTexture, VTXsdl.data(), VTXsdl.size(), IDXsdl.data(), IDXsdl.size());

					VTXsdl.clear();
#elif PS4
					//sce::SampleUtil::destroy(v_buffer);
   
					// create a vertex buffer interface called v_buffer
					/*d3ddev->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
											   0,
											   CUSTOMFVF,
											   D3DPOOL_MANAGED,
											   &v_buffer,
											   NULL);
					*/
					//_Application.getGraphics()->createVertexBuffer(&v_buffer, (sizeof(TexturedVertex) * 4));
					CUSTOMVERTEX t_vert[] =        
					{          

					  // square 1      
					  { -0.5,  0.5,  0.0, _Application.ARGBColorToUINT(255, (int)(vR*255), (int)(vG*255), (int)(vB*255)), testX, testY + testY1, },
					  {  0.5,  0.5,  0.0, _Application.ARGBColorToUINT(255, (int)(vR*255), (int)(vG*255), (int)(vB*255)), testX + is_slim_lttr, testY + testY1, },
					  { -0.5, -0.5,  0.0, _Application.ARGBColorToUINT(255, (int)(vR*255), (int)(vG*255), (int)(vB*255)), testX, testY, },
					  {  0.5, -0.5,  0.0, _Application.ARGBColorToUINT(255, (int)(vR*255), (int)(vG*255), (int)(vB*255)), testX + is_slim_lttr, testY, },

					};      

					colorMAIN = sce::Vectormath::Simd::Aos::Vector4(vR, vG, vB, 1.0f);

					// lock v_buffer and load the vertices into it
					/*v_buffer->Lock(0, 0, (void**)&pVoid, 0);
					memcpy(pVoid, t_vert, sizeof(t_vert));
					v_buffer->Unlock();*/  

         
					// select the vertex buffer to display
					//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
       
					D3DXMatrixTranslation(&matTranslate, (display_font.x + addX) + (-(display_font.width)) + (display_font.width/2),(display_font.y + addY) + (-(display_font.height)) + (display_font.height), 0.0f);
					D3DXMatrixScaling(&matScale, display_font.width*2, display_font.height*2, 1.0f); 

					D3DXMATRIX matViewFinishedTemp;
					D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matScale);
					D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp, &matTranslate);
					//matViewFinished = (matIdentity * matScale * matTranslate);
         
					// set the texture    
					if(display_font.id >= 0 && display_font.id < 100)
						currentSetTexture = texture[display_font.id].tex;
						//d3ddev->SetTexture(0, texture[display_font.id]);  
                
					D3DXSetTransform(&D3DTS_WORLD, &matViewFinished );

					D3DXMATRIX globalMTX;
					D3DXMatrixMultiply(&matViewFinishedTemp, &D3DTS_PROJECTION, &D3DTS_VIEW);
					D3DXMatrixMultiply(&globalMTX, &matViewFinishedTemp, &D3DTS_WORLD);

					for (int vtx_count = 0; vtx_count < 4; vtx_count++)
					{
						D3DXVECTOR3 temp;
						temp.x = t_vert[vtx_count].x;
						temp.y = t_vert[vtx_count].y;
						temp.z = t_vert[vtx_count].z;
						D3DXVECTOR3 res;
						D3DXVec3Project(&res, &temp, &D3DTS_PROJECTION, &D3DTS_VIEW, &D3DTS_WORLD);

						t_vert[vtx_count].x = res.x;
						t_vert[vtx_count].y = res.y;
						t_vert[vtx_count].z = res.z;

						//printf("QUAD FONT %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
					}
        
					//NEED TO DRAW PS4
					_Application.getGraphics()->createIndexBuffer(&i_buffer, (sizeof(uint16_t) * 6));
					_Application.getGraphics()->createVertexBuffer(&v_buffer, (sizeof(TexturedVertex) * 4));

					indexData = (uint16_t*)i_buffer->beginWrite();
					vertexData = (TexturedVertex*)v_buffer->beginWrite();

					/*for (int vtx_count = 0; vtx_count < 4; vtx_count++)
					{
						vertexData[vtx_count].position = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[vtx_count].x, global_t_vert[vtx_count].y);
						vertexData[vtx_count].texcoord = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
						printf("DETAIL %d -> %f %f uv : %f %f\n", vtx_count, global_t_vert[vtx_count].x, global_t_vert[vtx_count].y, global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
					}*/

					vertexData[0].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[2].x, t_vert[2].y);
					vertexData[1].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[3].x, t_vert[3].y);
					vertexData[2].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[0].x, t_vert[0].y);
					vertexData[3].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[1].x, t_vert[1].y);

					vertexData[0].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[2].u, 1.0f - t_vert[2].v);
					vertexData[1].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[3].u, 1.0f - t_vert[3].v);
					vertexData[2].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[0].u, 1.0f - t_vert[0].v);
					vertexData[3].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[1].u, 1.0f - t_vert[1].v);

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
						1.0, VerticesStock, i_buffer, 6, colorMAIN, sce::Vectormath::Simd::Aos::Vector4(0, 0, 0, 0), currentSetTexture, 1);

					//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

					//if(flash_render == true)
					//	d3ddev->SetRenderState(D3DRS_FOGENABLE, false);
					sce::SampleUtil::destroy(i_buffer);
					sce::SampleUtil::destroy(v_buffer);
					//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

#endif
        
				}
			#endif
#if defined SWITCH || defined DREAMCAST
			if(RENDERER == RENDER_OPENGL)                      
			{

				glPushMatrix();      
            
					glTranslatef((display_font.x + addX) + (-(display_font.width)) + (display_font.width/2),(display_font.y + addY) + (-(display_font.height)) + (display_font.height),0.0f); // This pretty much just means you load in your quad's center.
					glScalef( display_font.width*2, display_font.height*2, 0.0f);   // You load your object's X and Y dimensions in here.
            
					Set_Values(-1, -1, vR, vG, vB, display_font.alpha, -1, -1);     
                       
					glColor4fv(&Gcolor[0]); 
         
					if(display_font.id >= 0 && display_font.id < 100)
						glBindTexture(GL_TEXTURE_2D, texID[(display_font.id)]);     		

					glBegin(GL_QUADS);
	        
						Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, testX, testY);           
						glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
                
						Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, testX + is_slim_lttr, testY);
						glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	            
						Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, testX + is_slim_lttr, testY + testY1);
						glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	            
						Set_Values(-0.5f,  0.5f, -1, -1, -1, -1, testX, testY + testY1);
						glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                
					glEnd();  

				glPopMatrix();

			} 
#endif
        
        }

#if defined SWITCH || defined DREAMCAST
        if(RENDERER == RENDER_OPENGL)
        if(mode || i == 6)
            Zoom(zoom_factor);
#endif

        if(RENDERER == RENDER_DIRECTX)
        if(mode || i == 6)
            ZoomDX(TYPE_MODE_TEXT); 

        slim_width *= display_font.width;
        
        addX += slim_width;      
         
        // Fix Can symbol...
        if(display_font.word[loop] != 'é'
        && display_font.word[loop] != 'è'
        && display_font.word[loop] != 'ô'
        && display_font.word[loop] != 'î'
        && display_font.word[loop] != '/'
        && display_font.word[loop] != 'ù'
        && display_font.word[loop] != '¿'
        && display_font.word[loop] != 'Í'
        && display_font.word[loop] != 'ó'
        && display_font.word[loop] != 'á'
        && display_font.word[loop] != 'É'
        && display_font.word[loop] != 'Ú'
        && display_font.word[loop] != 'Ó'
        && display_font.word[loop] != 'º'
        && display_font.word[loop] != 'Ñ'
        && display_font.word[loop] != 'È' 
        && display_font.word[loop] != 'Ö' 
        && display_font.word[loop] != '$'
        && display_font.word[loop] != 'Ž'    
        && display_font.word[loop] != 'Ý' 
        && display_font.word[loop] != 'Þ'    
		&& display_font.word[loop] != '×' 
		&& display_font.word[loop] != '~' 
		&& display_font.word[loop] != '¢' 
		&& display_font.word[loop] != 'ª' 	
		&& display_font.word[loop] != '¸'  
		&& display_font.word[loop] != '³' 	
		&& display_font.word[loop] != 'Õ'  
		&& display_font.word[loop] != '¬' 
		&& display_font.word[loop] != '«'  
		&& display_font.word[loop] != 'Ï' 
        )
            addX += 0.005f;

	        
    }   
      
    } 


	} // i >= 0
       
}

void DrawTileBox()
{
 
}

#if IS_USING_DIRECTX == 1 
void Set_Vertex_TILE_Buffer(int row_x, int row_y) 
{  
	//UNUSED

#if 0
    VOID* pVoid;    // a void pointer  
    HRESULT err;
        
    float x_inc = (1.0f/16);
    float y_inc = (1.0f/32);
    float u=0.0f, u1=0.0f;
    float v=0.0f, v1=0.0f;

    SAFE_RELEASE(v_buffer);              
         
    SAFE_RELEASE(i_buffer); 
    
    
    u = x_inc*row_x; 
    u1 = u + x_inc; 
    
    v = y_inc*row_y;     
    v1 = v + y_inc;
     
    v  = v; 
    v1 = v1;
    
    // create a vertex buffer interface called v_buffer
    err = d3ddev->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &v_buffer,
                               NULL);
 	   
	if(err == D3DERR_INVALIDCALL)
		MessageBox(NULL,"Error CreateVertexBuffer : D3DERR_INVALIDCALL","ERROR",MB_OK|MB_ICONEXCLAMATION);

	if(err == D3DERR_OUTOFVIDEOMEMORY)
		MessageBox(NULL,"Error CreateVertexBuffer : D3DERR_OUTOFVIDEOMEMORY","ERROR",MB_OK|MB_ICONEXCLAMATION);
	   
	if(err == E_OUTOFMEMORY)
		MessageBox(NULL,"Error CreateVertexBuffer : E_OUTOFMEMORY","ERROR",MB_OK|MB_ICONEXCLAMATION);

        CUSTOMVERTEX t_vert[] =           
        {       
          // square 1      
          { -0.5,  0.5,  0.0, D3DCOLOR_XRGB(255, 255, 255), (u), v1, },
          {  0.5,  0.5,  0.0, D3DCOLOR_XRGB(255, 255, 255), (u1), v1, },
          { -0.5, -0.5,  0.0, D3DCOLOR_XRGB(255, 255, 255), (u), v, },
          {  0.5, -0.5,  0.0, D3DCOLOR_XRGB(255, 255, 255), (u1), v, },                
        };  

        // lock v_buffer and load the vertices into it
        v_buffer->Lock(0, 0, (void**)&pVoid, 0);
        memcpy(pVoid, t_vert, sizeof(t_vert));
        v_buffer->Unlock();     
     
        // create a index buffer interface called i_buffer
        d3ddev->CreateIndexBuffer(6*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &i_buffer,
                              NULL);
        
        // create the indices using an int array
        short indices[] =
        {
        0, 1, 2,    // fuselage
        2, 1, 3,
        }; 
         
       // lock i_buffer and load the indices into it
       i_buffer->Lock(0, 0, (void**)&pVoid, 0);
       memcpy(pVoid, indices, sizeof(indices));
       i_buffer->Unlock();  
       
       tile_counter++;              
        
#endif     
}

#endif

#if IS_USING_DIRECTX == 1  
void Set_Vertex_Buffer(int loop, int r, int g, int b, float alpha, bool is_a_sprite, bool flipped) 
{  
#ifdef XB1
	object temp_display;
	float temp_u = 0.0f;
	float temp_u1 = 0.0f;
	float diff_Y = 0.0f;
	int a = (int)(alpha * 255);
	//HRESULT err;

	void* pVoid;    // a void pointer  

	if (is_a_sprite == true)
	{
		if (loop < TOTAL_NO_SPRITES && loop >= 0)
			temp_display = sprite[loop];
		else
		{
			if (loop - TOTAL_NO_SPRITES >= 0 && loop - TOTAL_NO_SPRITES < TOTAL_NO_FX_SPRITES)
				temp_display = Fx[loop - TOTAL_NO_SPRITES];
		}
	}
	else
	{
		if (loop >= 0 && loop < TOTAL_NO_HUD)
			temp_display = hud[loop];
	}

	//sce::SampleUtil::destroy(v_buffer);

	// create a vertex buffer interface called v_buffer
	//_Application.getGraphics()->createVertexBuffer(&v_buffer, (sizeof(TexturedVertex) * 4));
	/*err = d3ddev->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
	0,
	CUSTOMFVF,
	D3DPOOL_MANAGED,
	&v_buffer,
	NULL);*/

	/*if(err == D3DERR_INVALIDCALL)
	MessageBox(NULL,"Error CreateVertexBuffer : D3DERR_INVALIDCALL","ERROR",MB_OK|MB_ICONEXCLAMATION);

	if(err == D3DERR_OUTOFVIDEOMEMORY)
	MessageBox(NULL,"Error CreateVertexBuffer : D3DERR_OUTOFVIDEOMEMORY","ERROR",MB_OK|MB_ICONEXCLAMATION);

	if(err == E_OUTOFMEMORY)
	MessageBox(NULL,"Error CreateVertexBuffer : E_OUTOFMEMORY","ERROR",MB_OK|MB_ICONEXCLAMATION);*/

	// create the vertices using the CUSTOMVERTEX struct
	if (temp_display.id >= 0 && temp_display.id < 200)
		if (texture_fx[temp_display.id] == 2 || texture_fx[temp_display.id] == 3 || texture_fx[temp_display.id] == 4)
		{

			//    Get_Texture_Coord(loop, is_a_sprite); 
			Get_Texture_Coord(temp_display.id, temp_display.fx_id, temp_display.frame, true);

			if (flipped == false)
			{
				temp_u = global_u;
				temp_u1 = global_u + global_u1;
			}
			if (flipped == true)
			{
				temp_u = global_u + global_u1;
				temp_u1 = global_u;
			}
			if (is_a_sprite == true)
				if (temp_display.depth > 0.0f)
				{
					diff_Y = global_v - global_v1;
					diff_Y = diff_Y / (1.0f / temp_display.depth);
					global_v1 += diff_Y;
				}

			if (temp_display.fx_id >= 0 && temp_display.fx_id < 75)
				if (a_texture[temp_display.fx_id].column == 0)
				{
					ARGB_COLOR temp_col = { a,r,g,b };
					CUSTOMVERTEX t_vert[] =
					{
						// square 1      
						{ -0.5,  0.5,  0.0,temp_col, temp_u,  temp_display.v[1], },
						{ 0.5,  0.5,  0.0, temp_col, temp_u1, temp_display.v[0], },
						{ -0.5, -0.5,  0.0, temp_col, temp_u,  temp_display.v[2], },
						{ 0.5, -0.5,  0.0, temp_col, temp_u1, temp_display.v[3], },
					};

					// lock v_buffer and load the vertices into it
					//v_buffer->Lock(0, 0, (void**)&pVoid, 0);
					memcpy(&global_t_vert, &t_vert, sizeof(CUSTOMVERTEX) * 4);
					/*vertexData = (TexturedVertex*)v_buffer->beginWrite();
					for (int i = 0; i < 4; i++)
					{
					vertexData[i].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].x, t_vert[i].y);
					vertexData[i].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].u, t_vert[i].v);
					}

					//memcpy(pVoid, t_vert, sizeof(t_vert));
					v_buffer->endWrite();*/
					//v_buffer->Unlock();  

				}
				else
				{
					ARGB_COLOR temp_col = { a,r,g,b };
					CUSTOMVERTEX t_vert[] =
					{
						// square 1      
						{ -0.5,  0.5,  0.0, temp_col, temp_u,  global_v, },
						{ 0.5,  0.5,  0.0, temp_col, temp_u1, global_v, },
						{ -0.5, -0.5,  0.0, temp_col, temp_u,  global_v1, },
						{ 0.5, -0.5,  0.0, temp_col, temp_u1, global_v1, },
					};

					// lock v_buffer and load the vertices into it
					//v_buffer->Lock(0, 0, (void**)&pVoid, 0);
					//colorMAIN = sce::Vectormath::Simd::Aos::Vector4(((float)r) / 255.0f, ((float)g) / 255.0f, ((float)b) / 255.0f, ((float)a) / 255.0f);
					/*vertexData = (TexturedVertex*)v_buffer->beginWrite();
					for (int i = 0; i < 4; i++)
					{
					vertexData[i].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].x, t_vert[i].y);
					vertexData[i].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].u, t_vert[i].v);
					}

					//memcpy(pVoid, t_vert, sizeof(t_vert));
					v_buffer->endWrite();*/
					memcpy(&global_t_vert, &t_vert, sizeof(CUSTOMVERTEX) * 4);
					//v_buffer->Unlock();  


				}

		}
		else
		{
			ARGB_COLOR temp_col = { a,r,g,b };
			CUSTOMVERTEX t_vert[] =
			{
				// FIXED     
				{ -0.5f,  0.5f,  0.0, temp_col, temp_display.u[0], temp_display.v[2], },
				{ 0.5f,  0.5f,  0.0, temp_col, temp_display.u[1], temp_display.v[2], },
				{ -0.5f, -0.5f,  0.0, temp_col, temp_display.u[0], temp_display.v[0], },
				{ 0.5f, -0.5f,  0.0, temp_col, temp_display.u[1], temp_display.v[0], },
			};

			// lock v_buffer and load the vertices into it
			//v_buffer->Lock(0, 0, (void**)&pVoid, 0);
			//colorMAIN = sce::Vectormath::Simd::Aos::Vector4(((float)r) / 255.0f, ((float)g) / 255.0f, ((float)b) / 255.0f, ((float)a) / 255.0f);
			/*vertexData = (TexturedVertex*)v_buffer->beginWrite();
			for (int i = 0; i < 4; i++)
			{
			vertexData[i].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].x, t_vert[i].y);
			vertexData[i].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].u, t_vert[i].v);
			}

			//memcpy(pVoid, t_vert, sizeof(t_vert));
			v_buffer->endWrite();*/
			memcpy(&global_t_vert, &t_vert, sizeof(CUSTOMVERTEX) * 4);
			//v_buffer->Unlock();          

		}
#elif PS4
	object temp_display;
	float temp_u=0.0f;
	float temp_u1=0.0f;
	float diff_Y=0.0f;
	int a = (int)(alpha * 255);
	//HRESULT err;
         
    void* pVoid;    // a void pointer  
	
    if(is_a_sprite == true)
	{
		if(loop < TOTAL_NO_SPRITES && loop >= 0) 
			temp_display = sprite[loop];  
		else        
        {  
            if(loop-TOTAL_NO_SPRITES >= 0 && loop-TOTAL_NO_SPRITES < TOTAL_NO_FX_SPRITES)
                temp_display = Fx[loop-TOTAL_NO_SPRITES];
		}
	}
    else
	{
		if(loop >= 0 && loop < TOTAL_NO_HUD)
			temp_display = hud[loop];  
	}

	//sce::SampleUtil::destroy(v_buffer);
   
    // create a vertex buffer interface called v_buffer
	//_Application.getGraphics()->createVertexBuffer(&v_buffer, (sizeof(TexturedVertex) * 4));
    /*err = d3ddev->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &v_buffer,
                               NULL);*/
	   
	/*if(err == D3DERR_INVALIDCALL)
		MessageBox(NULL,"Error CreateVertexBuffer : D3DERR_INVALIDCALL","ERROR",MB_OK|MB_ICONEXCLAMATION);

	if(err == D3DERR_OUTOFVIDEOMEMORY)
		MessageBox(NULL,"Error CreateVertexBuffer : D3DERR_OUTOFVIDEOMEMORY","ERROR",MB_OK|MB_ICONEXCLAMATION);
	   
	if(err == E_OUTOFMEMORY)
		MessageBox(NULL,"Error CreateVertexBuffer : E_OUTOFMEMORY","ERROR",MB_OK|MB_ICONEXCLAMATION);*/
     
    // create the vertices using the CUSTOMVERTEX struct
	if(temp_display.id >= 0 && temp_display.id < 200)
    if ( texture_fx[temp_display.id] == 2 || texture_fx[temp_display.id] == 3 || texture_fx[temp_display.id] == 4)
    {     
         
  //    Get_Texture_Coord(loop, is_a_sprite); 
      Get_Texture_Coord(temp_display.id, temp_display.fx_id, temp_display.frame, true);

	if(flipped == false) 
	{
		temp_u = global_u;
		temp_u1 = global_u + global_u1;
	}
	if(flipped == true)  
	{
		temp_u = global_u + global_u1;
		temp_u1 = global_u;
	}
	if(is_a_sprite == true)
    if(temp_display.depth > 0.0f)        
    { 
        diff_Y = global_v - global_v1;
        diff_Y = diff_Y / (1.0f/temp_display.depth); 
        global_v1 += diff_Y;  
    }

	if(temp_display.fx_id >= 0 && temp_display.fx_id < 75)
      if( a_texture[temp_display.fx_id].column == 0 )
      {  
		    
        CUSTOMVERTEX t_vert[] =    
        {      
          // square 1      
          { -0.5,  0.5,  0.0, _Application.ARGBColorToUINT(a, r, g, b), temp_u,  temp_display.v[1], },
          {  0.5,  0.5,  0.0, _Application.ARGBColorToUINT(a, r, g, b), temp_u1, temp_display.v[0], },
          { -0.5, -0.5,  0.0, _Application.ARGBColorToUINT(a, r, g, b), temp_u,  temp_display.v[2], },
          {  0.5, -0.5,  0.0, _Application.ARGBColorToUINT(a, r, g, b), temp_u1, temp_display.v[3], },
        };   

        // lock v_buffer and load the vertices into it
        //v_buffer->Lock(0, 0, (void**)&pVoid, 0);
		colorMAIN = sce::Vectormath::Simd::Aos::Vector4(((float)r) / 255.0f, ((float)g) / 255.0f, ((float)b) / 255.0f, ((float)a) / 255.0f);
		memcpy(&global_t_vert, &t_vert, sizeof(CUSTOMVERTEX) * 4);
		/*vertexData = (TexturedVertex*)v_buffer->beginWrite();
		for (int i = 0; i < 4; i++)
		{
			vertexData[i].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].x, t_vert[i].y);
			vertexData[i].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].u, t_vert[i].v);
		}
			
        //memcpy(pVoid, t_vert, sizeof(t_vert));
		v_buffer->endWrite();*/
        //v_buffer->Unlock();  
               
      }
      else  
      {  

        CUSTOMVERTEX t_vert[] =          
        {      
          // square 1      
          { -0.5,  0.5,  0.0, _Application.ARGBColorToUINT(a, r, g, b), temp_u,  global_v, },
          {  0.5,  0.5,  0.0, _Application.ARGBColorToUINT(a, r, g, b), temp_u1, global_v, },
          { -0.5, -0.5,  0.0, _Application.ARGBColorToUINT(a, r, g, b), temp_u,  global_v1, },
          {  0.5, -0.5,  0.0, _Application.ARGBColorToUINT(a, r, g, b), temp_u1, global_v1, },
        };    

		// lock v_buffer and load the vertices into it
		//v_buffer->Lock(0, 0, (void**)&pVoid, 0);
		colorMAIN = sce::Vectormath::Simd::Aos::Vector4(((float)r) / 255.0f, ((float)g) / 255.0f, ((float)b) / 255.0f, ((float)a) / 255.0f);
		/*vertexData = (TexturedVertex*)v_buffer->beginWrite();
		for (int i = 0; i < 4; i++)
		{
			vertexData[i].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].x, t_vert[i].y);
			vertexData[i].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].u, t_vert[i].v);
		}

		//memcpy(pVoid, t_vert, sizeof(t_vert));
		v_buffer->endWrite();*/
		memcpy(&global_t_vert, &t_vert, sizeof(CUSTOMVERTEX) * 4);
		//v_buffer->Unlock();  
                             
          
      }        
             
    }  
    else     
    {     
              
      CUSTOMVERTEX t_vert[] =                  
      {            
        // FIXED     
        { -0.5f,  0.5f,  0.0, _Application.ARGBColorToUINT(a, r, g, b), temp_display.u[0], temp_display.v[2], },
        {  0.5f,  0.5f,  0.0, _Application.ARGBColorToUINT(a, r, g, b), temp_display.u[1], temp_display.v[2], },
        { -0.5f, -0.5f,  0.0, _Application.ARGBColorToUINT(a, r, g, b), temp_display.u[0], temp_display.v[0], },
        {  0.5f, -0.5f,  0.0, _Application.ARGBColorToUINT(a, r, g, b), temp_display.u[1], temp_display.v[0], },
      }; 

	  // lock v_buffer and load the vertices into it
	  //v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	  colorMAIN = sce::Vectormath::Simd::Aos::Vector4(((float)r) / 255.0f, ((float)g) / 255.0f, ((float)b) / 255.0f, ((float)a) / 255.0f);
	  /*vertexData = (TexturedVertex*)v_buffer->beginWrite();
	  for (int i = 0; i < 4; i++)
	  {
		  vertexData[i].position = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].x, t_vert[i].y);
		  vertexData[i].texcoord = sce::Vectormath::Simd::Aos::Vector2(t_vert[i].u, t_vert[i].v);
	  }

	  //memcpy(pVoid, t_vert, sizeof(t_vert));
	  v_buffer->endWrite();*/
	  memcpy(&global_t_vert, &t_vert, sizeof(CUSTOMVERTEX) * 4);
	  //v_buffer->Unlock();          
    
    }
#endif
     
}

void DrawDXBox(float x, float y, float width, float height) 
{     
 //UNUSED, FOR DEBUG
#if 0
	float screen_box_x, screen_box_y;
	float screen_box_width, screen_box_height;

	d3ddev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	screen_box_x = x;  
	screen_box_y = y;     

	screen_box_width = width;  
	screen_box_height = height;

	D3DXMatrixIdentity (&matIdentity);

	D3DXMatrixTranslation(&matTranslate, screen_box_x + (screen_box_width/2),screen_box_y + (screen_box_height/2), 0.0f);
	D3DXMatrixScaling(&matScale, screen_box_width, screen_box_height, 1.0f); 

	matViewFinished = (matIdentity * matScale * matTranslate);

	d3ddev->SetTexture(0, NULL);  

	d3ddev->SetTransform (D3DTS_WORLD, &matViewFinished );

	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

	d3ddev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

#endif
}   



#endif
