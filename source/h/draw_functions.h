
#ifdef SWITCH
//#include <gl\gl.h>
#elif XB1
//#include "GameSaveManager.h"
extern std::vector< SDL_Vertex > VTXsdl;
extern std::vector< int > IDXsdl;
#endif
#include "globals.h"


extern void Set_Values(float x, float y, float R, float G, float B, float A, float u, float v);
#ifdef DREAMCAST
extern void Set_ValuesCustom(float x, float y, float R, float G, float B, float A, float u, float v);
extern float Get_Texture_Coord(int id, int fx_id, int frame, bool is_a_sprite, unsigned int &customID);
#else
extern float Get_Texture_Coord(int id, int fx_id, int frame, bool is_a_sprite);
#endif
extern void Draw_Font(int i); 
extern int Convert_Angle_To_Dir(float my_angle); 
extern void Animation_System(int loop, bool bullet_check, bool interrupt, bool pain_anim, bool fire);
extern void Animate(int loop, int type);

void Draw_Sprite(int f_rate);
void Draw_Hud_Sprites();
void Draw_Lines();
 
int sta2_line_timer = 0; 
int sta2_line_count = 0;

#if IS_USING_DIRECTX == 1  

/*#ifdef PS4
CUSTOMVERTEX Set_Vert(float x,  float y, float z, unsigned int color, float u,  float v)
#elif XB1
CUSTOMVERTEX Set_Vert(float x, float y, float z, DWORD color, float u, float v)
#endif
{
    CUSTOMVERTEX temp; 

    temp.x = x;
    temp.y = y; 
	temp.z = z;
#ifdef PS4
    temp.color = color;
#elif XB1
	temp.color = color;
#endif
    temp.u = u; 
    temp.v = v;           
    
    return(temp);
    
}*/

void Draw_BGDX(int temp1, int temp2, bool alpha_pass, bool is_debug)
{
   
     
}
#endif

void Draw_Lines()
{ 

}

void Draw_Sprite(int f_rate)
{ 
     
    float cx1=0.0f, cy1=0.0f;
    float cx2=0.0f, cy2=0.0f;
    float cx3=0.0f, cy3=0.0f;      
    float var2=0.0f;     
    float diff_Y=0.0f;    
    float vR = fade, vG = fade, vB = fade;
    float spritelight=0.0f;
    float temp_light=0.0f;
    float midX=0.0f;
    float midY=0.0f;
    int temp_row_x=0;
    int temp_row_y=0;     
    bool go_ahead = false;
    int light_index=0;
    int the_direction=0;
	int fog_r=0;
	int fog_g=0;
	int fog_b=0;
	bool is_a_sprite=false;  
	bool is_a_fx=false;
	bool flash_render=true;
	float fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f};  
	bool render_A=false;
	bool rotate_A=false;
	bool first_third=false; 
	float temp_distance=0.0f;

    for ( int i=0;i< new_no_sprites;i++)   
	if(i >= 0 && i < TOTAL_NO_SPRITES)
    {     

             is_a_sprite=false;
			 is_a_fx=false; 

             if(var3[i] < TOTAL_NO_SPRITES && var3[i] >= 0)     
             {
	 			// Run bump this code..
				if(sprite[var3[i]].bump_this == true)  
				{
					if((int)TimerGetTime() > sprite[var3[i]].bump_this_timer)
						sprite[var3[i]].bump_this = false; 
				}

                 display = sprite[var3[i]]; 
				 is_a_sprite = true;
                 go_ahead = true; 
             }
             else       
             {  
                 if(var3[i]-TOTAL_NO_SPRITES < TOTAL_NO_FX_SPRITES)
                 if(var3[i]-TOTAL_NO_SPRITES >= 0 )
                 {
                                 
	 				// Run bump this code..
					if(Fx[var3[i]-TOTAL_NO_SPRITES].bump_this == true)  
					{
						if((int)TimerGetTime() > Fx[var3[i]-TOTAL_NO_SPRITES].bump_this_timer)
							Fx[var3[i]-TOTAL_NO_SPRITES].bump_this = false; 
					}

                     display = Fx[var3[i]-TOTAL_NO_SPRITES];
					 is_a_fx=true;
                     go_ahead = true;  
                 } 
                 
             }
			  
			 if(VG_INVERT)
			 if(i >= 0 && i < TOTAL_NO_SPRITES)
			 if((var3[i] != 2 && var3[i] != 3 && (var3[i] != VG_1_LEGS || VG_1_LEGS == 0) && (var3[i] != VG_2_LEGS || VG_2_LEGS == 0) ) 
		     && is_a_fx == false)
				 go_ahead = false;
         
         if(go_ahead == true)
         {

         if( is_a_sprite == true || mode || is_a_fx == true || game_mode == FRONT)
         if( display.alpha != 0.0f || mode)    
         if( display.mouseover == false || mode)
         if( display.turn_off == false || mode)    
         { 
			  
             // Selected sprite in Debug Mode is brighter    
             if(mode)       
             {
				 if(i >= 0 && i < TOTAL_NO_SPRITES)
				 if(selection == var3[i])     
				 {
					 vR = 1.0f, vG = 1.0f, vB = 1.0f;
				 } 
				 else 
				 {
					 vR = 0.6f, vG = 0.6f, vB = 0.6f;  
				 }
             } 

             if(!mode)
                 vR = fade, vG = fade, vB = fade;

	         if(quit_active == true)
             {
                 vR -= 0.5f;
                 vG -= 0.5f;
                 vB -= 0.5f; 
             } 

			 // Draw offsets for punch/kicks etc...  
			 if(i >= 0 && i < TOTAL_NO_SPRITES)
			 if(episode == 5)  
			 {
				 if(var3[i] == 2)
					 display.x += VG_1_OFFSET;
				 if(var3[i] == 3)
					 display.x += VG_2_OFFSET;
			 }

			// Make sparkle effects visible in dark...
			if(!mode)
			if(i >= 0 && i < TOTAL_NO_SPRITES)
			if(var3[i] >= TOTAL_NO_SPRITES)
			if(display.flash_target == true)
			{ 
                 vR = 1.0f;
                 vG = 1.0f;
                 vB = 1.0f;			
			}
      
			 if(game_paused == true) 
			 { 
                 vR -= (float)PAUSED_LIGHT_LEVEL;
                 vG -= (float)PAUSED_LIGHT_LEVEL;

				 if(vR < 0.0f)
					vR = 0.0f;
				 if(vG < 0.0f)
					vG = 0.0f;
				 if(vB < 0.0f)
					vB = 0.0f;
			 }
				              
            if(display.bump_this == true) 
            { 
				// Bumping the BG sprite...
				display.height+=0.030f; 
				display.width+=0.030f; 
				display.x-=0.015f; 
				display.y-=0.015f; 
            }   

			// Shake sprite...
			if(episode == 5) 
			if(i >= 0 && i < TOTAL_NO_SPRITES)
			if( (var3[i] == 2 && VG_SHAKE_1 == true) || (var3[i] == 3 && VG_SHAKE_2 == true))
			if(VG_SHAKE_LEFT == true)
				display.x -= 0.004f;
			else
				display.x += 0.004f; 

			// Flicker for BG's... 
		/*	if(episode == 5 || (episode == 6 && scene == 0))
			if(var3[i] == 0)  
			{ 
				if(VG_FLICKER == true)  
				{ 
					display.x -= (0.00005f); // 0.00005f
				} 
				else
				{
					display.x += (0.00005f); // 0.00005f
				//	display.alpha = 0.5f;
				}

				VG_FLICKER ^= 1;
			}*/

	        
            // Animated Texture      
			if( display.id >= 0 && display.id < 200)
            if ( texture_fx[display.id] == 2 || texture_fx[display.id] == 3 || texture_fx[display.id] == 4)
            {
#ifdef DREAMCAST
            unsigned int customID = 0;
			if(RENDERER == RENDER_OPENGL) 
				Get_Texture_Coord(display.id, display.fx_id, display.frame, true, customID);
#else
			if(RENDERER == RENDER_OPENGL) 
				Get_Texture_Coord(display.id, display.fx_id, display.frame, true);
#endif

            cx1 = display.x;    
            cx2 = display.y; 
            cx3 = display.width; 
            cy3 = display.height;   

			flash_render = false; 
			render_A = false; 

			if(VG_DEFLECT_FLASH_ACTIVE == true)
			if(display.deflect == true)
			{
				fog_r = 0; // 64
				fog_g = 0; // 244 
				fog_b = 0; // 244 		
				flash_render = true; 
			}

			if(RENDERER == RENDER_DIRECTX || RENDERER == RENDER_OPENGL)
            if(display.flash_target == true)
			{
				flash_render = true;

				if(episode == 5) 
				{
					fog_r = 180; // 180   
					fog_g = 255; // 255
					fog_b = 199; // 199
				}
				else
				{
					fog_r = 255; // 180   
					fog_g = 255; // 255
					fog_b = 255; // 199
				}

			} 
			  
			if(VG_INVERT) 
			{
				flash_render = true;  
				fog_r = 0;
				fog_g = 0;    
				fog_b = 0;
			}
#if defined SWITCH || defined DREAMCAST      
			if(RENDERER == RENDER_OPENGL)
			{
				glPushMatrix(); 
				glTranslatef(cx1 + (cx3/2),cx2 + (cy3/2),0.0f); // This pretty much just means you load in your quad's center.
				glScalef( cx3, cy3, 0.0f);   // You load your object's X and Y dimensions in here.
			}
#endif

			rotate_A=false; 

			// Rotate angle...
#if defined SWITCH || defined DREAMCAST
            if(RENDERER == RENDER_OPENGL)
            {
#ifdef DREAMCAST
            	if(display.angle != 0.0)
            	{
#endif
            		glRotatef( display.angle, 0.0f, 0.0f, display.angle );
#ifdef DREAMCAST
            	}
#endif
                
            }
#endif

            Set_Values(-1, -1, vR, vG, vB, display.alpha, -1, -1);     
			
			if(RENDERER == RENDER_OPENGL)  
			if(flash_render == true)  
			{ 
				fogColor[0] = (float)fog_r/255; 
				fogColor[1] = (float)fog_g/255;
				fogColor[2] = (float)fog_b/255;
#if defined SWITCH || defined DREAMCAST
				////printf("FOG !!!!!!!\n");
#ifndef DREAMCAST
				glFogfv(GL_FOG_COLOR, fogColor);
				glEnable(GL_FOG);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
#endif

			}
#if defined SWITCH || defined DREAMCAST
			if(RENDERER == RENDER_OPENGL)
				glColor4fv(&Gcolor[0]);     
            
            //printf("1 SPRITE TEXTURE BINDING = %d\n", texID[(display.id)]);
#ifdef DREAMCAST
			unsigned int tempID_ju = 0;

			if(customID != 0)
			{
				tempID_ju = customID;
			}
			else
			{
				tempID_ju = texID[(display.id)];
			}

			if(RENDERER == RENDER_OPENGL)
			if( display.id >= 0 )
				glBindTexture(GL_TEXTURE_2D, tempID_ju);
#else
			if(RENDERER == RENDER_OPENGL)
			if( display.id >= 0 )
				glBindTexture(GL_TEXTURE_2D, texID[(display.id)]);
#endif  		

			if(RENDERER == RENDER_OPENGL)    
				glBegin(GL_QUADS);  
#endif
				  
                if(display.type == FE_FLIP || (display.sector == FX_FLIP && is_a_fx == true) ) 
                {    
 					 			
					#if IS_USING_DIRECTX == 1   
					if(RENDERER == RENDER_DIRECTX) 
						if(display.alpha != 0.0)                      
						{   
#ifdef XB1
							Set_Vertex_Buffer(var3[i], (int)(Gcolor[0] * 255), (int)(Gcolor[1] * 255), (int)(Gcolor[2] * 255), display.alpha, true, true);

							//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

							D3DXMatrixTranslation(&matTranslate, cx1 + (cx3 / 2), cx2 + (cy3 / 2), 0.0f);
							D3DXMatrixScaling(&matScale, cx3, cy3, 1.0f);

							D3DXMatrixRotationZ(&matRotationZ, display.angle*0.017453f);
							D3DXMATRIX matViewFinishedTemp;
							D3DXMATRIX matViewFinishedTemp2;
							D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matRotationZ);
							D3DXMatrixMultiply(&matViewFinishedTemp2, &matViewFinishedTemp, &matScale);
							D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp2, &matTranslate);
							//matViewFinished = (matIdentity * matRotationZ * matScale * matTranslate );

							if (display.id >= 0 && display.id < 100)
							{
								currentSetTexture = texture[display.id].tex;
								//currentSetSampler = texture[display.id].sampler;
							}
							//d3ddev->SetTexture(0, texture[display.id]); 

							// set the fog on      
							//if(flash_render == true)  
							//	d3ddev->SetRenderState(D3DRS_FOGENABLE, TRUE); 

							// Set the fog color  

							//NEED TO IMPLEMENT FOG---------
							ARGB_COLOR color_add;
							if (flash_render == true)
							{
								color_add.r = fog_r;
								color_add.g = fog_g;
								color_add.b = fog_b;
								color_add.a = 0;
							}
							else
							{
								color_add.r = 0;
								color_add.g = 0;
								color_add.b = 0;
								color_add.a = 0;
							}
							//////printf("FOG ACTIVATED ! %d %d %d\n", fog_r, fog_g, fog_b);
							//if(flash_render == true)
							//	d3ddev->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, fog_r, fog_g, fog_b) );
							//NEED TO IMPLEMENT FOG---------

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

								//////printf("HUD QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
							}

							VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[2].x, global_t_vert[2].y }, SDL_Color{ global_t_vert[2].color.r, global_t_vert[2].color.g, global_t_vert[2].color.b, global_t_vert[2].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
								SDL_FPoint{ global_t_vert[2].u, 1.0f - global_t_vert[2].v } });
							VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[3].x, global_t_vert[3].y }, SDL_Color{ global_t_vert[3].color.r, global_t_vert[3].color.g, global_t_vert[3].color.b, global_t_vert[3].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
								SDL_FPoint{ global_t_vert[3].u, 1.0f - global_t_vert[3].v } });
							VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[0].x, global_t_vert[0].y }, SDL_Color{ global_t_vert[0].color.r, global_t_vert[0].color.g, global_t_vert[0].color.b, global_t_vert[0].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
								SDL_FPoint{ global_t_vert[0].u, 1.0f - global_t_vert[0].v } });
							VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[1].x, global_t_vert[1].y }, SDL_Color{ global_t_vert[1].color.r, global_t_vert[1].color.g, global_t_vert[1].color.b, global_t_vert[1].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
								SDL_FPoint{ global_t_vert[1].u, 1.0f - global_t_vert[1].v } });


							SDL_RenderGeometry(pRenderer, currentSetTexture, VTXsdl.data(), VTXsdl.size(), IDXsdl.data(), IDXsdl.size());

							VTXsdl.clear();
							currentSetTexture = NULL;
#elif PS4
							Set_Vertex_Buffer(var3[i], (int)(Gcolor[0]*255), (int)(Gcolor[1]*255), (int)(Gcolor[2]*255), display.alpha, true, true);  

							//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

							D3DXMatrixTranslation(&matTranslate, cx1 + (cx3/2),cx2 + (cy3/2), 0.0f);
							D3DXMatrixScaling(&matScale, cx3, cy3, 1.0f); 

							D3DXMatrixRotationZ(&matRotationZ, display.angle*0.017453f);
							D3DXMATRIX matViewFinishedTemp;
							D3DXMATRIX matViewFinishedTemp2;
							D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matRotationZ);
							D3DXMatrixMultiply(&matViewFinishedTemp2, &matViewFinishedTemp, &matScale);
							D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp2, &matTranslate);
							//matViewFinished = (matIdentity * matRotationZ * matScale * matTranslate );

							if( display.id >= 0 && display.id < 100)
								currentSetTexture = texture[display.id].tex;
							    //d3ddev->SetTexture(0, texture[display.id]); 

							// set the fog on      
							//if(flash_render == true)  
							//	d3ddev->SetRenderState(D3DRS_FOGENABLE, TRUE); 

							// Set the fog color  

							//NEED TO IMPLEMENT FOG---------
							if (flash_render == true)
								addMAIN = sce::Vectormath::Simd::Aos::Vector4(((float)fog_r) / 255.0f, ((float)fog_g) / 255.0f, ((float)fog_b) / 255.0f, 0.0);
							else
								addMAIN = sce::Vectormath::Simd::Aos::Vector4(0, 0, 0, 0);
								//////printf("FOG ACTIVATED ! %d %d %d\n", fog_r, fog_g, fog_b);
							//if(flash_render == true)
							//	d3ddev->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, fog_r, fog_g, fog_b) );
							//NEED TO IMPLEMENT FOG---------

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

								//////printf("SPRITE QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
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
								////printf("DETAIL %d -> %f %f uv : %f %f\n", vtx_count, global_t_vert[vtx_count].x, global_t_vert[vtx_count].y, global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
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
								1.0, VerticesStock, i_buffer, 6, colorMAIN, addMAIN, currentSetTexture, 1);

							//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

							//if(flash_render == true)
							//	d3ddev->SetRenderState(D3DRS_FOGENABLE, false);
							sce::SampleUtil::destroy(i_buffer);
							sce::SampleUtil::destroy(v_buffer);

							//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

							//if(flash_render == true)
							//	d3ddev->SetRenderState(D3DRS_FOGENABLE, false);

#endif
        
						}
					#endif

					if( display.fx_id >= 0 && display.fx_id < 75) 
                    if( a_texture[display.fx_id].column == 0 )
                    { 
#if defined SWITCH
						if(RENDERER == RENDER_OPENGL)
						{

							Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[0]);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        
							Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, global_u, display.v[1]);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        	
							Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, global_u, display.v[2]);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        	
							Set_Values(-0.5f, 0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[3]);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);

						}
#endif
#if defined DREAMCAST
						if(RENDERER == RENDER_OPENGL)
						{
							if(customID != 0)
							{
								Set_ValuesCustom(-0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[0]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        
								Set_ValuesCustom( 0.5f, -0.5f, -1, -1, -1, -1, global_u, display.v[1]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        	
								Set_ValuesCustom( 0.5f,  0.5f, -1, -1, -1, -1, global_u, display.v[2]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        	
								Set_ValuesCustom(-0.5f, 0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[3]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
							}
							else
							{
								Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[0]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        
								Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, global_u, display.v[1]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        	
								Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, global_u, display.v[2]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        	
								Set_Values(-0.5f, 0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[3]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
							}
						}
#endif

                   } 
                    else
                    {
#if defined SWITCH
						if(RENDERER == RENDER_OPENGL)
						{

							Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, global_v1);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
                        
							Set_Values(0.5f, -0.5f, -1, -1, -1, -1, global_u, global_v1);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                    
							Set_Values(0.5f, 0.5f, -1, -1, -1, -1, global_u, global_v);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                    
							Set_Values(-0.5f, 0.5f, -1, -1, -1, -1, global_u + global_u1, global_v);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);

						}
#endif
#if defined DREAMCAST
						if(RENDERER == RENDER_OPENGL)
						{
							if(customID != 0)
							{
								Set_ValuesCustom(-0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, global_v1);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                        
								Set_ValuesCustom(0.5f, -0.5f, -1, -1, -1, -1, global_u, global_v1);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
		                    
								Set_ValuesCustom(0.5f, 0.5f, -1, -1, -1, -1, global_u, global_v);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
		                    
								Set_ValuesCustom(-0.5f, 0.5f, -1, -1, -1, -1, global_u + global_u1, global_v);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
							}
							else
							{
								Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, global_v1);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                        
								Set_Values(0.5f, -0.5f, -1, -1, -1, -1, global_u, global_v1);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
		                    
								Set_Values(0.5f, 0.5f, -1, -1, -1, -1, global_u, global_v);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
		                    
								Set_Values(-0.5f, 0.5f, -1, -1, -1, -1, global_u + global_u1, global_v);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
							}

						}
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
							Set_Vertex_Buffer(var3[i], (int)(Gcolor[0] * 255), (int)(Gcolor[1] * 255), (int)(Gcolor[2] * 255), display.alpha, true, false);

							// select the vertex buffer to display
							//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

							D3DXMatrixTranslation(&matTranslate, cx1 + (cx3 / 2), cx2 + (cy3 / 2), 0.0f);
							D3DXMatrixScaling(&matScale, cx3, cy3, 1.0f);

							D3DXMatrixRotationZ(&matRotationZ, display.angle*0.017453f);
							D3DXMATRIX matViewFinishedTemp;
							D3DXMATRIX matViewFinishedTemp2;
							D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matRotationZ);
							D3DXMatrixMultiply(&matViewFinishedTemp2, &matViewFinishedTemp, &matScale);
							D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp2, &matTranslate);
							//matViewFinished = (matIdentity * matRotationZ * matScale * matTranslate );

							if (display.id >= 0 && display.id < 100)
							{
								currentSetTexture = texture[display.id].tex;
								//currentSetSampler = texture[display.id].sampler;
							}


							// set the fog on      
							//if(flash_render == true)  
							//	d3ddev->SetRenderState(D3DRS_FOGENABLE, TRUE); 

							// Set the fog color 
							//NEED TO IMPLEMENT FOG---------
							ARGB_COLOR color_add;
							if (flash_render == true)
							{
								color_add.r = fog_r;
								color_add.g = fog_g;
								color_add.b = fog_b;
								color_add.a = 0;
							}
							else
							{
								color_add.r = 0;
								color_add.g = 0;
								color_add.b = 0;
								color_add.a = 0;
							}
							//if(flash_render == true)
							//	d3ddev->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, fog_r, fog_g, fog_b) );
							//NEED TO IMPLEMENT FOG---------

							D3DXSetTransform(&D3DTS_WORLD, &matViewFinished);

							D3DXMATRIX globalMTX;
							D3DXMatrixMultiply(&matViewFinishedTemp, &D3DTS_PROJECTION, &D3DTS_VIEW);
							D3DXMatrixMultiply(&globalMTX, &matViewFinishedTemp, &D3DTS_WORLD);

							for (int vtx_count = 0; vtx_count < 4; vtx_count++)
							{
								/*D3DVECTOR temp;
								D3DVECTOR res;
								temp.x = global_t_vert[vtx_count].x;
								temp.y = global_t_vert[vtx_count].y;
								temp.z = global_t_vert[vtx_count].z;

								D3DXVec3Transform(&res, &temp, &globalMTX);

								global_t_vert[vtx_count].x = (res.x + 1) / 2;
								global_t_vert[vtx_count].y = ((res.y + 1) / 2);
								global_t_vert[vtx_count].z = res.z;*/

								D3DXVECTOR3 temp;
								temp.x = global_t_vert[vtx_count].x;
								temp.y = global_t_vert[vtx_count].y;
								temp.z = global_t_vert[vtx_count].z;
								D3DXVECTOR3 res;
								D3DXVec3Project(&res, &temp, &D3DTS_PROJECTION, &D3DTS_VIEW, &D3DTS_WORLD);

								global_t_vert[vtx_count].x = res.x * 1920.0f;
								global_t_vert[vtx_count].y = res.y * 1080.0f;
								global_t_vert[vtx_count].z = res.z;

								//////printf("HUD QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
							}

							VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[2].x, global_t_vert[2].y }, SDL_Color{ global_t_vert[2].color.r, global_t_vert[2].color.g, global_t_vert[2].color.b, global_t_vert[2].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
								SDL_FPoint{ global_t_vert[2].u, 1.0f - global_t_vert[2].v } });
							VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[3].x, global_t_vert[3].y }, SDL_Color{ global_t_vert[3].color.r, global_t_vert[3].color.g, global_t_vert[3].color.b, global_t_vert[3].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
								SDL_FPoint{ global_t_vert[3].u, 1.0f - global_t_vert[3].v } });
							VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[0].x, global_t_vert[0].y }, SDL_Color{ global_t_vert[0].color.r, global_t_vert[0].color.g, global_t_vert[0].color.b, global_t_vert[0].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
								SDL_FPoint{ global_t_vert[0].u, 1.0f - global_t_vert[0].v } });
							VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[1].x, global_t_vert[1].y }, SDL_Color{ global_t_vert[1].color.r, global_t_vert[1].color.g, global_t_vert[1].color.b, global_t_vert[1].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
								SDL_FPoint{ global_t_vert[1].u, 1.0f - global_t_vert[1].v } });


							SDL_RenderGeometry(pRenderer, currentSetTexture, VTXsdl.data(), VTXsdl.size(), IDXsdl.data(), IDXsdl.size());

							VTXsdl.clear();
							currentSetTexture = NULL;
#elif PS4
							Set_Vertex_Buffer(var3[i],  (int)(Gcolor[0]*255), (int)(Gcolor[1]*255), (int)(Gcolor[2]*255), display.alpha, true, false);  

							// select the vertex buffer to display
							//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

							D3DXMatrixTranslation(&matTranslate, cx1 + (cx3/2),cx2 + (cy3/2), 0.0f);
							D3DXMatrixScaling(&matScale, cx3, cy3, 1.0f); 

							D3DXMatrixRotationZ(&matRotationZ, display.angle*0.017453f);
							D3DXMATRIX matViewFinishedTemp;
							D3DXMATRIX matViewFinishedTemp2;
							D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matRotationZ);
							D3DXMatrixMultiply(&matViewFinishedTemp2, &matViewFinishedTemp, &matScale);
							D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp2, &matTranslate);
							//matViewFinished = (matIdentity * matRotationZ * matScale * matTranslate );

							if (display.id >= 0 && display.id < 100)
							{
								currentSetTexture = texture[display.id].tex;
								//d3ddev->SetTexture(0, texture[display.id]); 
								//////printf("SET TEXTURE %s\n", texture[display.id].name);
							}
								

							// set the fog on      
							//if(flash_render == true)  
							//	d3ddev->SetRenderState(D3DRS_FOGENABLE, TRUE); 

							// Set the fog color 
							//NEED TO IMPLEMENT FOG---------
							if (flash_render == true)
								addMAIN = sce::Vectormath::Simd::Aos::Vector4(((float)fog_r) / 255.0f, ((float)fog_g) / 255.0f, ((float)fog_b) / 255.0f, 0.0);
							else
								addMAIN = sce::Vectormath::Simd::Aos::Vector4(0, 0, 0, 0);
							//if(flash_render == true)
							//	d3ddev->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, fog_r, fog_g, fog_b) );
							//NEED TO IMPLEMENT FOG---------

							D3DXSetTransform (&D3DTS_WORLD, &matViewFinished );

							D3DXMATRIX globalMTX;
							D3DXMatrixMultiply(&matViewFinishedTemp, &D3DTS_PROJECTION, &D3DTS_VIEW);
							D3DXMatrixMultiply(&globalMTX, &matViewFinishedTemp, &D3DTS_WORLD);

							for (int vtx_count = 0; vtx_count < 4; vtx_count++)
							{
								/*D3DVECTOR temp;
								D3DVECTOR res;
								temp.x = global_t_vert[vtx_count].x;
								temp.y = global_t_vert[vtx_count].y;
								temp.z = global_t_vert[vtx_count].z;

								D3DXVec3Transform(&res, &temp, &globalMTX);

								global_t_vert[vtx_count].x = (res.x + 1) / 2;
								global_t_vert[vtx_count].y = ((res.y + 1) / 2);
								global_t_vert[vtx_count].z = res.z;*/

								D3DXVECTOR3 temp;
								temp.x = global_t_vert[vtx_count].x;
								temp.y = global_t_vert[vtx_count].y;
								temp.z = global_t_vert[vtx_count].z;
								D3DXVECTOR3 res;
								D3DXVec3Project(&res, &temp, &D3DTS_PROJECTION, &D3DTS_VIEW, &D3DTS_WORLD);

								global_t_vert[vtx_count].x = res.x;
								global_t_vert[vtx_count].y = res.y;
								global_t_vert[vtx_count].z = res.z;



								//////printf("SPRITE 2 QUAD %d -> %f %f%s", vtx_count, global_t_vert[vtx_count].x, global_t_vert[vtx_count].y, vtx_count == 3 ? " \n" : "  ");
							}

							//////printf("%.4f %.4f ------------------ %.4f %.4f\n", global_t_vert[2].u, global_t_vert[0].v, global_t_vert[3].u, global_t_vert[1].v);
							//////printf("%.4f %.4f ------------------ %.4f %.4f\n", global_t_vert[0].u, global_t_vert[2].v, global_t_vert[1].u, global_t_vert[3].v);

							//NEED TO DRAW PS4
							_Application.getGraphics()->createIndexBuffer(&i_buffer, (sizeof(uint16_t) * 6));
							_Application.getGraphics()->createVertexBuffer(&v_buffer, (sizeof(TexturedVertex) * 4));

							indexData = (uint16_t*)i_buffer->beginWrite();
							vertexData = (TexturedVertex*)v_buffer->beginWrite();

							/*for (int vtx_count = 0; vtx_count < 4; vtx_count++)
							{
								vertexData[vtx_count].position = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[vtx_count].x, global_t_vert[vtx_count].y);
								vertexData[vtx_count].texcoord = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
								////printf("DETAIL %d -> %f %f uv : %f %f\n", vtx_count, global_t_vert[vtx_count].x, global_t_vert[vtx_count].y, global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
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
								1.0, VerticesStock, i_buffer, 6, colorMAIN, addMAIN, currentSetTexture, 1);

							//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

							//if(flash_render == true)
							//	d3ddev->SetRenderState(D3DRS_FOGENABLE, false);
							sce::SampleUtil::destroy(i_buffer);
							sce::SampleUtil::destroy(v_buffer);

#endif
        
						}
					#endif

					if( display.fx_id >= 0 && display.fx_id < 75) 
                    if( a_texture[display.fx_id].column == 0 )
                    {
#if defined SWITCH
						if(RENDERER == RENDER_OPENGL)
						{


							Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u, display.v[0]);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
                        
							Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[1]);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        		
							Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[2]);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        	
							Set_Values(-0.5f,  0.5f, -1, -1, -1, -1, global_u, display.v[3]);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);

						}
#endif
#if defined DREAMCAST
						if(RENDERER == RENDER_OPENGL)
						{
							if(customID != 0)
							{
								Set_ValuesCustom(-0.5f, -0.5f, -1, -1, -1, -1, global_u, display.v[0]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                        
								Set_ValuesCustom( 0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[1]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        		
								Set_ValuesCustom( 0.5f,  0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[2]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        	
								Set_ValuesCustom(-0.5f,  0.5f, -1, -1, -1, -1, global_u, display.v[3]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
							}
							else
							{
								Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u, display.v[0]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                        
								Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[1]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        		
								Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[2]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        	
								Set_Values(-0.5f,  0.5f, -1, -1, -1, -1, global_u, display.v[3]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
							}
							
						}
#endif
 
                    }
                    else
                    {
#if defined SWITCH
						if(RENDERER == RENDER_OPENGL)
						{

							Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u, global_v1);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
                        
							Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, global_v1);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
                        	
							Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, global_u + global_u1, global_v);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        	
							Set_Values(-0.5f,  0.5f, -1, -1, -1, -1, global_u, global_v);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);

						}
#endif
#if defined DREAMCAST
						if(RENDERER == RENDER_OPENGL)
						{
							if(customID != 0)
							{
								Set_ValuesCustom(-0.5f, -0.5f, -1, -1, -1, -1, global_u, global_v1);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                        
								Set_ValuesCustom( 0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, global_v1);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                        	
								Set_ValuesCustom( 0.5f,  0.5f, -1, -1, -1, -1, global_u + global_u1, global_v);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        	
								Set_ValuesCustom(-0.5f,  0.5f, -1, -1, -1, -1, global_u, global_v);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
							}
							else
							{
								Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u, global_v1);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                        
								Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, global_v1);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                        	
								Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, global_u + global_u1, global_v);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        	
								Set_Values(-0.5f,  0.5f, -1, -1, -1, -1, global_u, global_v);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
							}

						}
#endif

                    }
                }
#if defined SWITCH || defined DREAMCAST
			if(RENDERER == RENDER_OPENGL)
				glEnd();     

            if(RENDERER == RENDER_OPENGL)
				glPopMatrix();
 
			if(flash_render == true)   
			{
				glDisable(GL_FOG);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
#endif

            }  
            else
            { 
#if defined SWITCH || defined DREAMCAST
            if(RENDERER == RENDER_OPENGL) 
			{
				glPushMatrix();  
              	//printf("Center %f %f\n", display.x + (display.width/2),display.y + (display.height/2));
				glTranslatef(display.x + (display.width/2),display.y + (display.height/2),0.0f); // This pretty much just means you load in your quad's center.
				glScalef( display.width, display.height, 0.0f);   // You load your object's X and Y dimensions in here.
				//printf("Scale %f %f\n", display.width, display.height);

			}

			if(RENDERER == RENDER_OPENGL)
			{
#ifdef DREAMCAST
            	if(display.angle != 0.0)
            	{
#endif
            		glRotatef( display.angle, 0.0f, 0.0f, display.angle );
#ifdef DREAMCAST
            	}
#endif
			}
#endif

            Set_Values(-1, -1, vR, vG, vB, display.alpha, -1, -1);
#if defined SWITCH || defined DREAMCAST
            if(RENDERER == RENDER_OPENGL)                          
				glColor4fv(&Gcolor[0]); 

			//printf("COLORS %f %f %f %f\n", Gcolor[0], Gcolor[1], Gcolor[2], Gcolor[3]);
	        //printf("2 SPRITE TEXTURE BINDING = %d\n", texID[(display.id)]);

			if(RENDERER == RENDER_OPENGL)
			if( display.id >= 0 )
				glBindTexture(GL_TEXTURE_2D, texID[(display.id)]);		
#endif

			#if IS_USING_DIRECTX == 1   			
            if(RENDERER == RENDER_DIRECTX) 
				if(display.alpha != 0.0)                      
				{ 
#ifdef XB1
					Set_Vertex_Buffer(var3[i], (int)(vR * 255), (int)(vG * 255), (int)(vB * 255), display.alpha, true, false);

					// select the vertex buffer to display
					//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

					D3DXMatrixTranslation(&matTranslate, display.x + (display.width / 2), display.y + (display.height / 2), 0.0f);
					D3DXMatrixScaling(&matScale, display.width, display.height, 1.0f);

					D3DXMatrixRotationZ(&matRotationZ, display.angle*0.017453f);
					D3DXMATRIX matViewFinishedTemp;
					D3DXMATRIX matViewFinishedTemp2;
					D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matRotationZ);
					D3DXMatrixMultiply(&matViewFinishedTemp2, &matViewFinishedTemp, &matScale);
					D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp2, &matTranslate);
					//matViewFinished = (matIdentity * matRotationZ * matScale * matTranslate );
					//bool transfoTitle = false;
					// set the texture    
					if (display.id >= 0 && display.id < 100)
					{
						
						/*if (strstr(texture[display.id].name, "title/bg_title.png") != NULL)
						{
							transfoTitle = true;
						}*/
						currentSetTexture = texture[display.id].tex;
						
						//currentSetSampler = texture[display.id].sampler;
					}
					//d3ddev->SetTexture(0, texture[display.id]);  

					D3DXSetTransform(&D3DTS_WORLD, &matViewFinished);

					//D3DXMATRIX globalMTX;
					//D3DXMatrixMultiply(&matViewFinishedTemp, &D3DTS_PROJECTION, &D3DTS_VIEW);
					//D3DXMatrixMultiply(&globalMTX, &matViewFinishedTemp, &D3DTS_WORLD);

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

						//////printf("HUD QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
					}
					
					/*if (transfoTitle == true)
					{
						global_t_vert[0].x = 0.0f;
						global_t_vert[0].y = 1080.0f;
						global_t_vert[1].x = 1920.0f;
						global_t_vert[1].y = 1080.0f;
						global_t_vert[2].x = 0.0f;
						global_t_vert[2].y = 0.0f;
						global_t_vert[3].x = 1920.0f;
						global_t_vert[3].y = 0.0f;
					}*/
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
					currentSetTexture = NULL;
#elif PS4
					Set_Vertex_Buffer(var3[i],  (int)(vR*255), (int)(vG*255), (int)(vB*255), display.alpha, true, false);  
         
					// select the vertex buffer to display
					//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
       
					D3DXMatrixTranslation(&matTranslate, display.x + (display.width/2), display.y + (display.height/2), 0.0f);
					D3DXMatrixScaling(&matScale, display.width, display.height, 1.0f); 

					D3DXMatrixRotationZ(&matRotationZ, display.angle*0.017453f);
					D3DXMATRIX matViewFinishedTemp;
					D3DXMATRIX matViewFinishedTemp2;
					D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matRotationZ);
					D3DXMatrixMultiply(&matViewFinishedTemp2, &matViewFinishedTemp, &matScale);
					D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp2, &matTranslate);
					//matViewFinished = (matIdentity * matRotationZ * matScale * matTranslate );
         
					// set the texture    
					if (display.id >= 0 && display.id < 100)
					{
						//////printf("SET TEXTURE %s\n", texture[display.id].name);
						currentSetTexture = texture[display.id].tex;
					}
						//d3ddev->SetTexture(0, texture[display.id]);  
                
					D3DXSetTransform (&D3DTS_WORLD, &matViewFinished );
        
					//D3DXMATRIX globalMTX;
					//D3DXMatrixMultiply(&matViewFinishedTemp, &D3DTS_PROJECTION, &D3DTS_VIEW);
					//D3DXMatrixMultiply(&globalMTX, &matViewFinishedTemp, &D3DTS_WORLD);

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

						//////printf("SPRITE 3 QUAD %d ->%f %f%s ", vtx_count, global_t_vert[u].v, global_t_vert[u].v, vtx_count == 3 ? " \n" : "  ");
					}

					//////printf("%.4f %.4f ------------------ %.4f %.4f\n", global_t_vert[2].u, global_t_vert[0].v, global_t_vert[3].u, global_t_vert[1].v);
					//////printf("%.4f %.4f ------------------ %.4f %.4f\n", global_t_vert[0].u, global_t_vert[2].v, global_t_vert[1].u, global_t_vert[3].v);

					//NEED TO DRAW PS4
					_Application.getGraphics()->createIndexBuffer(&i_buffer, (sizeof(uint16_t) * 6));
					_Application.getGraphics()->createVertexBuffer(&v_buffer, (sizeof(TexturedVertex) * 4));

					indexData = (uint16_t*)i_buffer->beginWrite();
					vertexData = (TexturedVertex*)v_buffer->beginWrite();

					/*for (int vtx_count = 0; vtx_count < 4; vtx_count++)
					{
						vertexData[vtx_count].position = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[vtx_count].x, global_t_vert[vtx_count].y);
						vertexData[vtx_count].texcoord = sce::Vectormath::Simd::Aos::Vector2(global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
						////printf("DETAIL %d -> %f %f uv : %f %f\n", vtx_count, global_t_vert[vtx_count].x, global_t_vert[vtx_count].y, global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
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
#if defined SWITCH || defined DREAMCAST
    		if(RENDERER == RENDER_OPENGL)
			{
	        glBegin(GL_QUADS);
	        	
                Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, display.u[0], display.v[0]);
                glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                //printf("vec %f %f uv %f %f\n", Gvector[0], Gvector[1], Gtex[0], Gtex[1]);	
                
                Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, display.u[1], display.v[1]);
	            glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	            //printf("vec %f %f uv %f %f\n", Gvector[0], Gvector[1],Gtex[0], Gtex[1]);	
	            
                Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, display.u[2], display.v[2]);
	            glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	            //printf("vec %f %f uv %f %f\n", Gvector[0], Gvector[1],Gtex[0], Gtex[1]);	
	            
                Set_Values(-0.5f,  0.5f, -1, -1, -1, -1, display.u[3], display.v[3]);
                glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                //printf("vec %f %f uv %f %f\n", Gvector[0], Gvector[1],Gtex[0], Gtex[1]);

            glEnd();     
	                  
            glPopMatrix(); 

			}  
#endif
               
            }   
#if defined SWITCH || defined DREAMCAST
           if(RENDERER == RENDER_OPENGL)            
           if( (mode==COLLISION && selection == var3[i]) || debug_active == true )
	            DrawLine( display.w, display.z, display.box_width, display.box_height, 0.5f, 1.0f);
#endif
	       
       }      
       
       
       } // go_ahead == true
       
    } // End of for loop   
  
     
}

void Draw_Hud_Sprites()
{

    float cx1=0.0f, cy1=0.0f;
    float cx2=0.0f, cy2=0.0f;
    float cx3=0.0f, cy3=0.0f;      
    float diff_Y=0.0f;    
    float vR = fade, vG = fade, vB = fade;
    float spritelight=0.0f;
    float temp_light=0.0f;
    float midX=0.0f;
    float midY=0.0f;
    int temp_row_x=0;
    int temp_row_y=0;     
    bool go_ahead = false;
    int light_index=0;
    int the_direction=0;
	int fog_r=0;
	int fog_g=0;
	int fog_b=0;
	bool is_a_sprite=false;  
	bool is_a_fx=false;
	bool flash_render=true;
	float fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f};  
	bool render_A=false;
	bool rotate_A=false;
	bool first_third=false; 
	float temp_distance=0.0f;    
        
        
        for ( int i=0;i < hud_no_sprites;i++)
		if(i >= 0 && i < 75)
		if(var4[i] >= 0 && var4[i] < TOTAL_NO_HUD)
        if(var4[i] != 1) // Don't draw the mouse pointer or message box
        if(hud[var4[i]].alpha != 0.0f || mode)
        { 
			// Run bump this code..
            if(hud[var4[i]].bump_this == true)  
            {
				if((int)TimerGetTime() > hud[var4[i]].bump_this_timer)
					hud[var4[i]].bump_this = false; 
			}
                                 
             display = hud[var4[i]];  
                         
             vR = fade, vG = fade, vB = fade;

            if(display.bump_this == true)  
            {
                display.height+=0.0100f; 
                display.width+=0.0100f;  
                display.x-=0.0050f; 
                display.y-=0.0050f;  
            }  

			 if(game_paused == true && var4[i] != 55)
			 { 
                 vR -= (float)PAUSED_LIGHT_LEVEL;
                 vG -= (float)PAUSED_LIGHT_LEVEL;
                 vB -= (float)PAUSED_LIGHT_LEVEL;

				 if(vR < 0.0f)
					vR = 0.0f;
				 if(vG < 0.0f)
					vG = 0.0f;
				 if(vB < 0.0f)
					vB = 0.0f;
			 }

  			flash_render = false;
			render_A = false;

			if(RENDERER == RENDER_DIRECTX || RENDERER == RENDER_OPENGL)
            if(display.flash_target == true)
			{
				flash_render = true;
				fog_r = 255;
				fog_g = 255;  
				fog_b = 255;
			} 

            // Animated Texture
			if( display.id >= 0 && display.id < 200)
			if(display.frame >= 0 && display.fx_id >= 0)
            if ( texture_fx[display.id] == 2 || texture_fx[display.id] == 3 )
            {  

#ifdef DREAMCAST
            unsigned int customID = 0;
			if(RENDERER == RENDER_OPENGL) 
				Get_Texture_Coord(display.id, display.fx_id, display.frame, true, customID);
#else
			if(RENDERER == RENDER_OPENGL) 
				Get_Texture_Coord(display.id, display.fx_id, display.frame, true);
#endif
       
            cx1 = display.x;    
            cx2 = display.y; 
            cx3 = display.width; 
            cy3 = display.height;  
#if defined SWITCH || defined DREAMCAST
			if(RENDERER == RENDER_OPENGL)  
			{
				glPushMatrix();     
           
				glTranslatef(display.x + (display.width/2),display.y + (display.height/2),0.0f); // This pretty much just means you load in your quad's center.
				glScalef( display.width, display.height, 0.0f);   // You load your object's X and Y dimensions in here.
			}
#endif

			Set_Values(-1, -1, vR, vG, vB, display.alpha, -1, -1); 
	
#if defined SWITCH || defined DREAMCAST
			if(RENDERER == RENDER_OPENGL)   
			if(display.flash_target == true)  
			{ 
				fogColor[0] = (float)fog_r/255; 
				fogColor[1] = (float)fog_g/255;
				fogColor[2] = (float)fog_b/255;
				glFogfv(GL_FOG_COLOR, fogColor);
				glEnable(GL_FOG);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			}
#endif

			#if IS_USING_DIRECTX == 1  
					  
			    if(display.type == FE_FLIP) 
                {  
					if(RENDERER == RENDER_DIRECTX)
					if(display.alpha != 0.0)                      
					{ 
#ifdef XB1
						Set_Vertex_Buffer(var4[i], (int)(Gcolor[0] * 255), (int)(Gcolor[1] * 255), (int)(Gcolor[2] * 255), display.alpha, false, true);

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

						// set the fog on      
						//if(flash_render == true)  
						//d3ddev->SetRenderState(D3DRS_FOGENABLE, TRUE); 

						// Set the fog color  
						//NEED TO IMPLEMENT FOG---------
						ARGB_COLOR color_add;
						if (flash_render == true)
						{
							color_add.r = fog_r;
							color_add.g = fog_g;
							color_add.b = fog_b;
							color_add.a = 0;
						}
						else
						{
							color_add.r = 0;
							color_add.g = 0;
							color_add.b = 0;
							color_add.a = 0;
						}
						//d3ddev->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, fog_r, fog_g, fog_b) );
						//NEED TO IMPLEMENT FOG---------

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

							//////printf("HUD QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
						}

						VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[2].x, global_t_vert[2].y }, SDL_Color{ global_t_vert[2].color.r, global_t_vert[2].color.g, global_t_vert[2].color.b, global_t_vert[2].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
							SDL_FPoint{ global_t_vert[2].u, 1.0f - global_t_vert[2].v } });
						VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[3].x, global_t_vert[3].y }, SDL_Color{ global_t_vert[3].color.r, global_t_vert[3].color.g, global_t_vert[3].color.b, global_t_vert[3].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
							SDL_FPoint{ global_t_vert[3].u, 1.0f - global_t_vert[3].v } });
						VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[0].x, global_t_vert[0].y }, SDL_Color{ global_t_vert[0].color.r, global_t_vert[0].color.g, global_t_vert[0].color.b, global_t_vert[0].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
							SDL_FPoint{ global_t_vert[0].u, 1.0f - global_t_vert[0].v } });
						VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[1].x, global_t_vert[1].y }, SDL_Color{ global_t_vert[1].color.r, global_t_vert[1].color.g, global_t_vert[1].color.b, global_t_vert[1].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
							SDL_FPoint{ global_t_vert[1].u, 1.0f - global_t_vert[1].v } });


						SDL_RenderGeometry(pRenderer, currentSetTexture, VTXsdl.data(), VTXsdl.size(), IDXsdl.data(), IDXsdl.size());

						VTXsdl.clear();
						currentSetTexture = NULL;
#elif PS4
						Set_Vertex_Buffer(var4[i], (int)(Gcolor[0]*255), (int)(Gcolor[1]*255), (int)(Gcolor[2]*255), display.alpha, false, true);   
         
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

						// set the fog on      
						//if(flash_render == true)  
							//d3ddev->SetRenderState(D3DRS_FOGENABLE, TRUE); 

						// Set the fog color  
						//NEED TO IMPLEMENT FOG---------
						if (flash_render == true)
							addMAIN = sce::Vectormath::Simd::Aos::Vector4(((float)fog_r) / 255.0f, ((float)fog_g) / 255.0f, ((float)fog_b) / 255.0f, 0.0);
						else
							addMAIN = sce::Vectormath::Simd::Aos::Vector4(0, 0, 0, 0);
							//d3ddev->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, fog_r, fog_g, fog_b) );
						//NEED TO IMPLEMENT FOG---------

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

							//////printf("QUAD SPE %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
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
							////printf("DETAIL %d -> %f %f uv : %f %f\n", vtx_count, global_t_vert[vtx_count].x, global_t_vert[vtx_count].y, global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
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
							1.0, VerticesStock, i_buffer, 6, colorMAIN, addMAIN, currentSetTexture, 1);

						//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

						//if(flash_render == true)
						//	d3ddev->SetRenderState(D3DRS_FOGENABLE, false);
						sce::SampleUtil::destroy(i_buffer);
						sce::SampleUtil::destroy(v_buffer);

						//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

						//if(flash_render == true)
							//d3ddev->SetRenderState(D3DRS_FOGENABLE, false); 

#endif
        
					}
				}
				else
				{
					if(RENDERER == RENDER_DIRECTX)
					if(display.alpha != 0.0)                      
					{ 
#ifdef XB1
						Set_Vertex_Buffer(var4[i], (int)(Gcolor[0] * 255), (int)(Gcolor[1] * 255), (int)(Gcolor[2] * 255), display.alpha, false, false);

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

						// set the fog on      
						//if(flash_render == true)  
						//d3ddev->SetRenderState(D3DRS_FOGENABLE, TRUE); 

						// Set the fog color  
						//NEED TO IMPLEMENT FOG---------
						ARGB_COLOR color_add;
						if (flash_render == true)
						{
							color_add.r = fog_r;
							color_add.g = fog_g;
							color_add.b = fog_b;
							color_add.a = 0;
						}
						else
						{
							color_add.r = 0;
							color_add.g = 0;
							color_add.b = 0;
							color_add.a = 0;
						}
						//if(flash_render == true)
						//d3ddev->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, fog_r, fog_g, fog_b) );
						//NEED TO IMPLEMENT FOG---------

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

							//////printf("HUD QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
						}

						VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[2].x, global_t_vert[2].y }, SDL_Color{ global_t_vert[2].color.r, global_t_vert[2].color.g, global_t_vert[2].color.b, global_t_vert[2].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
							SDL_FPoint{ global_t_vert[2].u, 1.0f - global_t_vert[2].v } });
						VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[3].x, global_t_vert[3].y }, SDL_Color{ global_t_vert[3].color.r, global_t_vert[3].color.g, global_t_vert[3].color.b, global_t_vert[3].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
							SDL_FPoint{ global_t_vert[3].u, 1.0f - global_t_vert[3].v } });
						VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[0].x, global_t_vert[0].y }, SDL_Color{ global_t_vert[0].color.r, global_t_vert[0].color.g, global_t_vert[0].color.b, global_t_vert[0].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
							SDL_FPoint{ global_t_vert[0].u, 1.0f - global_t_vert[0].v } });
						VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[1].x, global_t_vert[1].y }, SDL_Color{ global_t_vert[1].color.r, global_t_vert[1].color.g, global_t_vert[1].color.b, global_t_vert[1].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
							SDL_FPoint{ global_t_vert[1].u, 1.0f - global_t_vert[1].v } });


						SDL_RenderGeometry(pRenderer, currentSetTexture, VTXsdl.data(), VTXsdl.size(), IDXsdl.data(), IDXsdl.size());

						VTXsdl.clear();
						currentSetTexture = NULL;
#elif PS4

						Set_Vertex_Buffer(var4[i], (int)(Gcolor[0]*255), (int)(Gcolor[1]*255), (int)(Gcolor[2]*255), display.alpha, false, false);   
         
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

						// set the fog on      
						//if(flash_render == true)  
							//d3ddev->SetRenderState(D3DRS_FOGENABLE, TRUE); 

						// Set the fog color  
						//NEED TO IMPLEMENT FOG---------
						if (flash_render == true)
							addMAIN = sce::Vectormath::Simd::Aos::Vector4(((float)fog_r) / 255.0f, ((float)fog_g) / 255.0f, ((float)fog_b) / 255.0f, 0.0);
						else
							addMAIN = sce::Vectormath::Simd::Aos::Vector4(0, 0, 0, 0);
						//if(flash_render == true)
							//d3ddev->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, fog_r, fog_g, fog_b) );
						//NEED TO IMPLEMENT FOG---------

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

							//////printf("QUAD SPE 2 %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
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
							////printf("DETAIL %d -> %f %f uv : %f %f\n", vtx_count, global_t_vert[vtx_count].x, global_t_vert[vtx_count].y, global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
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
							1.0, VerticesStock, i_buffer, 6, colorMAIN, addMAIN, currentSetTexture, 1);

						//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

						//if(flash_render == true)
						//	d3ddev->SetRenderState(D3DRS_FOGENABLE, false);
						sce::SampleUtil::destroy(i_buffer);
						sce::SampleUtil::destroy(v_buffer);

						//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

						//if(flash_render == true)
							//d3ddev->SetRenderState(D3DRS_FOGENABLE, false); 

#endif
        
					}
				}

			#endif 

            if(RENDERER == RENDER_OPENGL) 
			{
#if defined SWITCH || defined DREAMCAST
            glColor4fv(&Gcolor[0]); 
            ////printf("3 SPRITE TEXTURE BINDING = %d\n", texID[(display.id)]);
#ifdef DREAMCAST
			unsigned int tempID_ju = 0;

			if(customID != 0)
			{
				tempID_ju = customID;
			}
			else
			{
				tempID_ju = texID[(display.id)];
			}

			if(display.id >= 0 && display.id < 100)
				glBindTexture(GL_TEXTURE_2D, tempID_ju);
#else
			if(display.id >= 0 && display.id < 100)
				glBindTexture(GL_TEXTURE_2D, texID[(display.id)]);
#endif  		  		

	        glBegin(GL_QUADS); 
#endif
   
			    if(display.type == FE_FLIP) 
                {  
					if( display.fx_id >= 0 ) 
                    if( a_texture[display.fx_id].column == 0 )
                    { 
						if(RENDERER == RENDER_OPENGL)
						{
#if defined SWITCH
							Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[0]);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        
							Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, global_u, display.v[1]);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        	
							Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, global_u, display.v[2]);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        	
							Set_Values(-0.5f, 0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[3]);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
#endif
#if defined DREAMCAST
							if(customID != 0)
							{
								Set_ValuesCustom(-0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[0]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        
								Set_ValuesCustom( 0.5f, -0.5f, -1, -1, -1, -1, global_u, display.v[1]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        	
								Set_ValuesCustom( 0.5f,  0.5f, -1, -1, -1, -1, global_u, display.v[2]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        	
								Set_ValuesCustom(-0.5f, 0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[3]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
							}
							else
							{
								Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[0]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        
								Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, global_u, display.v[1]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        	
								Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, global_u, display.v[2]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        	
								Set_Values(-0.5f, 0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[3]);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
							}
#endif
						}

                   } 
                    else
                    {
						if(RENDERER == RENDER_OPENGL)
						{
#if defined SWITCH
							Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, global_v1);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
                        
							Set_Values(0.5f, -0.5f, -1, -1, -1, -1, global_u, global_v1);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                    
							Set_Values(0.5f, 0.5f, -1, -1, -1, -1, global_u, global_v);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                    
							Set_Values(-0.5f, 0.5f, -1, -1, -1, -1, global_u + global_u1, global_v);
							glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
#endif
#if defined DREAMCAST
							if(customID != 0)
							{
								Set_ValuesCustom(-0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, global_v1);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                        
								Set_ValuesCustom(0.5f, -0.5f, -1, -1, -1, -1, global_u, global_v1);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
		                    
								Set_ValuesCustom(0.5f, 0.5f, -1, -1, -1, -1, global_u, global_v);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
		                    
								Set_ValuesCustom(-0.5f, 0.5f, -1, -1, -1, -1, global_u + global_u1, global_v);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
							}
							else
							{
								Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, global_v1);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                        
								Set_Values(0.5f, -0.5f, -1, -1, -1, -1, global_u, global_v1);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
		                    
								Set_Values(0.5f, 0.5f, -1, -1, -1, -1, global_u, global_v);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
		                    
								Set_Values(-0.5f, 0.5f, -1, -1, -1, -1, global_u + global_u1, global_v);
								glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
							}
#endif
						}
                    } 
				}
				else
				{
                    if( a_texture[display.fx_id].column == 0 )
                    {
#if defined SWITCH
                        Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u, display.v[0]);
                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
                        
                        Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[1]);
	                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                    
                        Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[2]);
	                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        	
                        Set_Values(-0.5f,  0.5f, -1, -1, -1, -1, global_u, display.v[3]);
                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
#endif
#if defined DREAMCAST
                        if(customID != 0)
                        {
                        	Set_ValuesCustom(-0.5f, -0.5f, -1, -1, -1, -1, global_u, display.v[0]);
	                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                        
	                        Set_ValuesCustom( 0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[1]);
		                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
		                    
	                        Set_ValuesCustom( 0.5f,  0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[2]);
		                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        	
	                        Set_ValuesCustom(-0.5f,  0.5f, -1, -1, -1, -1, global_u, display.v[3]);
	                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        }
                        else
                        {
                        	Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u, display.v[0]);
	                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                        
	                        Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[1]);
		                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
		                    
	                        Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, global_u + global_u1, display.v[2]);
		                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                        	
	                        Set_Values(-0.5f,  0.5f, -1, -1, -1, -1, global_u, display.v[3]);
	                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        }
                        
#endif
                        
                    }
                    else
                    {
#if defined SWITCH
                        Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u, global_v1);
                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
                        
                        Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, global_v1);
	                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                    
                        Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, global_u + global_u1, global_v);
	                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
	                    
                        Set_Values(-0.5f,  0.5f, -1, -1, -1, -1, global_u, global_v);
                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
#endif
#if defined DREAMCAST
                        if(customID != 0)
                        {
                        	Set_ValuesCustom(-0.5f, -0.5f, -1, -1, -1, -1, global_u, global_v1);
	                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                        
	                        Set_ValuesCustom( 0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, global_v1);
		                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
		                    
	                        Set_ValuesCustom( 0.5f,  0.5f, -1, -1, -1, -1, global_u + global_u1, global_v);
		                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
		                    
	                        Set_ValuesCustom(-0.5f,  0.5f, -1, -1, -1, -1, global_u, global_v);
	                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        }
                        else
                        {
                        	Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, global_u, global_v1);
	                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	                        
	                        Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, global_u + global_u1, global_v1);
		                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
		                    
	                        Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, global_u + global_u1, global_v);
		                    glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
		                    
	                        Set_Values(-0.5f,  0.5f, -1, -1, -1, -1, global_u, global_v);
	                        glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                        }
                        
#endif
                    }
				}
#if defined SWITCH || defined DREAMCAST
            glEnd();  
           
            glPopMatrix();
 
			if(flash_render == true)   
			{
				glDisable(GL_FOG);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
#endif

			} // if(RENDERER == RENDER_OPENGL)
                             
            }
            else
            {              
   
            // Turn special blend on  
			if(RENDERER == RENDER_OPENGL)
			if( display.id >= 0 )
            if(texture_fx[display.id] == 5)
            {
#if defined SWITCH || defined DREAMCAST
                glBlendFunc(src_one, src_two);			// Enable Alpha Blending (disable alpha testing)
#endif
            }  

	        
            if(i==0 && game_mode == FRONT) // Draws hand in porno mode
            {

			#if IS_USING_DIRECTX == 1  
			    if(RENDERER == RENDER_DIRECTX)
				if(display.alpha != 0.0)                       
				{ 
#ifdef XB1
					Set_Vertex_Buffer(var4[i], (int)(Gcolor[0] * 255), (int)(Gcolor[1] * 255), (int)(Gcolor[2] * 255), display.alpha, false, false);

					// select the vertex buffer to display
					//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

					D3DXMatrixTranslation(&matTranslate, display.x + (display.width / 2), display.y + (display.height / 2), 0.0f);
					D3DXMatrixScaling(&matScale, display.width, display.height, 1.0f);
					D3DXMATRIX matViewFinishedTemp;
					if (var4[i] == 56)
					{
						D3DXMatrixRotationZ(&matRotationZ, display.angle*0.017453f);

						D3DXMATRIX matViewFinishedTemp2;
						D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matRotationZ);
						D3DXMatrixMultiply(&matViewFinishedTemp2, &matViewFinishedTemp, &matScale);
						D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp2, &matTranslate);
						//matViewFinished = (matIdentity * matRotationZ * matScale * matTranslate );
					}
					else
					{

						D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matScale);
						D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp, &matTranslate);
						//matViewFinished = (matIdentity * matScale * matTranslate);
					}


					// set the texture    
					if (display.id >= 0 && display.id < 100)
					{
						currentSetTexture = texture[display.id].tex;
						//currentSetSampler = texture[display.id].sampler;
					}
					//d3ddev->SetTexture(0, texture[display.id]);  

					// set the fog on      
					//if(flash_render == true)  
					//d3ddev->SetRenderState(D3DRS_FOGENABLE, TRUE); 

					// Set the fog color  
					//NEED TO IMPLEMENT FOG---------
					ARGB_COLOR color_add;
					if (flash_render == true)
					{
						color_add.r = fog_r;
						color_add.g = fog_g;
						color_add.b = fog_b;
						color_add.a = 0;
					}
					else
					{
						color_add.r = 0;
						color_add.g = 0;
						color_add.b = 0;
						color_add.a = 0;
					}
					//if(flash_render == true)
					//d3ddev->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, fog_r, fog_g, fog_b) );
					//NEED TO IMPLEMENT FOG---------

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

						//////printf("HUD QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
					}

					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[2].x, global_t_vert[2].y }, SDL_Color{ global_t_vert[2].color.r, global_t_vert[2].color.g, global_t_vert[2].color.b, global_t_vert[2].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
						SDL_FPoint{ global_t_vert[2].u, 1.0f - global_t_vert[2].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[3].x, global_t_vert[3].y }, SDL_Color{ global_t_vert[3].color.r, global_t_vert[3].color.g, global_t_vert[3].color.b, global_t_vert[3].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
						SDL_FPoint{ global_t_vert[3].u, 1.0f - global_t_vert[3].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[0].x, global_t_vert[0].y }, SDL_Color{ global_t_vert[0].color.r, global_t_vert[0].color.g, global_t_vert[0].color.b, global_t_vert[0].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
						SDL_FPoint{ global_t_vert[0].u, 1.0f - global_t_vert[0].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[1].x, global_t_vert[1].y }, SDL_Color{ global_t_vert[1].color.r, global_t_vert[1].color.g, global_t_vert[1].color.b, global_t_vert[1].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
						SDL_FPoint{ global_t_vert[1].u, 1.0f - global_t_vert[1].v } });


					SDL_RenderGeometry(pRenderer, currentSetTexture, VTXsdl.data(), VTXsdl.size(), IDXsdl.data(), IDXsdl.size());

					VTXsdl.clear();
					currentSetTexture = NULL;
#elif PS4
					Set_Vertex_Buffer(var4[i], (int)(Gcolor[0]*255), (int)(Gcolor[1]*255), (int)(Gcolor[2]*255), display.alpha, false, false);  
         
					// select the vertex buffer to display
					//d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
       
					D3DXMatrixTranslation(&matTranslate, display.x + (display.width/2),display.y + (display.height/2), 0.0f);
					D3DXMatrixScaling(&matScale, display.width, display.height, 1.0f); 
					D3DXMATRIX matViewFinishedTemp;
					if(var4[i] == 56) 
					{
						D3DXMatrixRotationZ(&matRotationZ, display.angle*0.017453f);
						
						D3DXMATRIX matViewFinishedTemp2;
						D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matRotationZ);
						D3DXMatrixMultiply(&matViewFinishedTemp2, &matViewFinishedTemp, &matScale);
						D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp2, &matTranslate);
						//matViewFinished = (matIdentity * matRotationZ * matScale * matTranslate );
					} 
					else
					{
						
						D3DXMatrixMultiply(&matViewFinishedTemp, &matIdentity, &matScale);
						D3DXMatrixMultiply(&matViewFinished, &matViewFinishedTemp, &matTranslate);
						//matViewFinished = (matIdentity * matScale * matTranslate);
					}
						
         
					// set the texture    
					if(display.id >= 0 && display.id < 100)
						currentSetTexture = texture[display.id].tex;
						//d3ddev->SetTexture(0, texture[display.id]);  

						// set the fog on      
						//if(flash_render == true)  
							//d3ddev->SetRenderState(D3DRS_FOGENABLE, TRUE); 

						// Set the fog color  
						//NEED TO IMPLEMENT FOG---------
						if (flash_render == true)
							addMAIN = sce::Vectormath::Simd::Aos::Vector4(((float)fog_r) / 255.0f, ((float)fog_g) / 255.0f, ((float)fog_b) / 255.0f, 0.0);
						else
							addMAIN = sce::Vectormath::Simd::Aos::Vector4(0, 0, 0, 0);
						//if(flash_render == true)
							//d3ddev->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, fog_r, fog_g, fog_b) );
						//NEED TO IMPLEMENT FOG---------

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

							//////printf("QUAD SPE 3 %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
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
							////printf("DETAIL %d -> %f %f uv : %f %f\n", vtx_count, global_t_vert[vtx_count].x, global_t_vert[vtx_count].y, global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
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
							1.0, VerticesStock, i_buffer, 6, colorMAIN, addMAIN, currentSetTexture, 1);

						//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

						//if(flash_render == true)
						//	d3ddev->SetRenderState(D3DRS_FOGENABLE, false);
						sce::SampleUtil::destroy(i_buffer);
						sce::SampleUtil::destroy(v_buffer);
						//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

						//if(flash_render == true)
							//d3ddev->SetRenderState(D3DRS_FOGENABLE, false); 

#endif
        
				}
			#endif

             if(RENDERER == RENDER_OPENGL)                      
			 {
#if defined SWITCH || defined DREAMCAST
             glPushMatrix();    
           
             glTranslatef( display.x - display.width, (display.y - display.height),0.0f); // This pretty much just means you load in your quad's center.
             glScalef( display.width*2, display.height*2, 0.0f);   // You load your object's X and Y dimensions in here.
             
             Set_Values(-1, -1, vR, vG, vB, display.alpha, -1, -1);     
                       
             glColor4fv(&Gcolor[0]); 
             ////printf("4 SPRITE TEXTURE BINDING = %d\n", texID[(display.id)]);  

			if(display.id >= 0 && display.id < 100)
				glBindTexture(GL_TEXTURE_2D, texID[(display.id)]);
		      
		
	         glBegin(GL_QUADS);
                         
                Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, display.u[0], display.v[0]);                             
                glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);		
                
                Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, display.u[1], display.v[1]);                             
	            glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	            
                Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, display.u[2], display.v[2]);                             
	            glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
	            
                Set_Values(-0.5f,  0.5f, -1, -1, -1, -1, display.u[3], display.v[3]);                             
                glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);

             glEnd();
            
             glPopMatrix(); 
#endif

			 } // if(RENDERER == RENDER_OPENGL)
                             
             }
             else
             {       

			#if IS_USING_DIRECTX == 1  
			    if(RENDERER == RENDER_DIRECTX) 
				if(display.alpha != 0.0)                      
				{ 
#ifdef XB1
					Set_Vertex_Buffer(var4[i], (int)(Gcolor[0] * 255), (int)(Gcolor[1] * 255), (int)(Gcolor[2] * 255), display.alpha, false, false);

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

					// set the fog on      
					//if(flash_render == true)  
					//d3ddev->SetRenderState(D3DRS_FOGENABLE, TRUE); 

					// Set the fog color  
					//NEED TO IMPLEMENT FOG---------
					ARGB_COLOR color_add;
					if (flash_render == true)
					{
						color_add.r = fog_r;
						color_add.g = fog_g;
						color_add.b = fog_b;
						color_add.a = 0;
					}
					else
					{
						color_add.r = 0;
						color_add.g = 0;
						color_add.b = 0;
						color_add.a = 0;
					}
					//if(flash_render == true)
					//d3ddev->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, fog_r, fog_g, fog_b) );
					//NEED TO IMPLEMENT FOG---------

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

						//////printf("HUD QUAD %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
					}

					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[2].x, global_t_vert[2].y }, SDL_Color{ global_t_vert[2].color.r, global_t_vert[2].color.g, global_t_vert[2].color.b, global_t_vert[2].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
						SDL_FPoint{ global_t_vert[2].u, 1.0f - global_t_vert[2].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[3].x, global_t_vert[3].y }, SDL_Color{ global_t_vert[3].color.r, global_t_vert[3].color.g, global_t_vert[3].color.b, global_t_vert[3].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
						SDL_FPoint{ global_t_vert[3].u, 1.0f - global_t_vert[3].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[0].x, global_t_vert[0].y }, SDL_Color{ global_t_vert[0].color.r, global_t_vert[0].color.g, global_t_vert[0].color.b, global_t_vert[0].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
						SDL_FPoint{ global_t_vert[0].u, 1.0f - global_t_vert[0].v } });
					VTXsdl.push_back(SDL_Vertex{ SDL_FPoint{global_t_vert[1].x, global_t_vert[1].y }, SDL_Color{ global_t_vert[1].color.r, global_t_vert[1].color.g, global_t_vert[1].color.b, global_t_vert[1].color.a }, SDL_Color{ color_add.r, color_add.g, color_add.b, color_add.a },
						SDL_FPoint{ global_t_vert[1].u, 1.0f - global_t_vert[1].v } });



					SDL_RenderGeometry(pRenderer, currentSetTexture, VTXsdl.data(), VTXsdl.size(), IDXsdl.data(), IDXsdl.size());

					VTXsdl.clear();
					currentSetTexture = NULL;
#elif PS4
					Set_Vertex_Buffer(var4[i], (int)(Gcolor[0]*255), (int)(Gcolor[1]*255), (int)(Gcolor[2]*255), display.alpha, false, false);  
         
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

					// set the fog on      
					//if(flash_render == true)  
						//d3ddev->SetRenderState(D3DRS_FOGENABLE, TRUE); 

					// Set the fog color  
					//NEED TO IMPLEMENT FOG---------
					if (flash_render == true)
						addMAIN = sce::Vectormath::Simd::Aos::Vector4(((float)fog_r) / 255.0f, ((float)fog_g) / 255.0f, ((float)fog_b) / 255.0f, 0.0);
					else
						addMAIN = sce::Vectormath::Simd::Aos::Vector4(0, 0, 0, 0);
					//if(flash_render == true)
						//d3ddev->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, fog_r, fog_g, fog_b) );
					//NEED TO IMPLEMENT FOG---------

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

						//////printf("QUAD SPE 4 %d -> %f %f%s", vtx_count, res.x, res.y, vtx_count == 3 ? " \n" : "  ");
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
						////printf("DETAIL %d -> %f %f uv : %f %f\n", vtx_count, global_t_vert[vtx_count].x, global_t_vert[vtx_count].y, global_t_vert[vtx_count].u, global_t_vert[vtx_count].v);
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
						1.0, VerticesStock, i_buffer, 6, colorMAIN, addMAIN, currentSetTexture, 1);

					//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

					//if(flash_render == true)
					//	d3ddev->SetRenderState(D3DRS_FOGENABLE, false);
					sce::SampleUtil::destroy(i_buffer);
					sce::SampleUtil::destroy(v_buffer);
					//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // Draws a basic Quad...

					//if(flash_render == true)
						//d3ddev->SetRenderState(D3DRS_FOGENABLE, false);

#endif
        
				}
			#endif

             if(RENDERER == RENDER_OPENGL)   
			 {
#if defined SWITCH || defined DREAMCAST
				glPushMatrix();       
           
				glTranslatef(display.x + (display.width/2),display.y + (display.height/2),0.0f); // This pretty much just means you load in your quad's center.
				glScalef( display.width, display.height, 0.0f);   // You load your object's X and Y dimensions in here.
             
				Set_Values(-1, -1, vR, vG, vB, display.alpha, -1, -1);     
                       
				glColor4fv(&Gcolor[0]); 
				////printf("5 SPRITE TEXTURE BINDING = %d\n", texID[(display.id)]);

				if(display.id >= 0 && display.id < 100)
					glBindTexture(GL_TEXTURE_2D, texID[(display.id)]);		      		

				glBegin(GL_QUADS);
	        
					Set_Values(-0.5f, -0.5f, -1, -1, -1, -1, display.u[0], display.v[0]);                                       
					glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);	
                
					Set_Values( 0.5f, -0.5f, -1, -1, -1, -1, display.u[1], display.v[1]);                                       
					glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                	
					Set_Values( 0.5f,  0.5f, -1, -1, -1, -1, display.u[2], display.v[2]);                                       
					glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
                	
					Set_Values(-0.5f,  0.5f, -1, -1, -1, -1, display.u[3], display.v[3]);                                       
					glTexCoord2fv(&Gtex[0]);glVertex2fv(&Gvector[0]);
 
				glEnd(); 
           
				glPopMatrix(); 
#endif
			 } // if(RENDERER == RENDER_OPENGL)
                                                
            }

            
            }
    
                    
         }  // if(hud[var4[i]].alpha != 0.0f || mode)   
     
     
     
     
}













