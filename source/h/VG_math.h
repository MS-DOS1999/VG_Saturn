#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "globals.h"   

#if defined WIN32 || defined WIN64  
#define WIN32_LEAN_AND_MEAN      
#include <windows.h>
#endif      

extern void VG_Reset_all_anims();

float Node_Distance1(float x1, float y1, float x2, float y2)
{ 
        
      float length=0.0f;   
      float x_value=0.0;
      float y_value=0.0;
       
      if( x1 > x2)
          x_value = x1 - x2; 
      else
          x_value = x2 - x1;
      
      if( y1 > y2) 
          y_value = y1 - y2;
      else
          y_value = y2 - y1;           

      length = sqrt( (x_value * x_value) + (y_value * y_value) );
       
      return length;
           
}


int Convert_Angle_To_Dir(float my_angle)
{
    int i_my_angle=0;
   
    if(my_angle >= -1.875f && my_angle <= -1.125f) // DOWN
    {    
        i_my_angle = DOWN;       
    }
    if(my_angle <= 1.875f && my_angle >= 1.125f) // UP
    {
        i_my_angle = UP;     
    }        
    if(my_angle >= 2.625f || my_angle <= -2.625f) // RIGHT
    {   
        i_my_angle = LEFT;     
    }
    if(my_angle <= 0.375f && my_angle >= -0.375f) // LEFT 
    {  
        i_my_angle = RIGHT;      
    }  
    if(my_angle >= -2.625f && my_angle <= -1.875f) 
    {
        i_my_angle = DOWN_LEFT;     
    }
    if(my_angle >= -1.125f && my_angle <= -0.375f)  // DOWN LEFT/RIGHT
    {
        i_my_angle = DOWN_RIGHT;     
    }
    if(my_angle >= 1.875f && my_angle <= 2.625f)
    {
        i_my_angle = UP_LEFT;                            
    }
    if(my_angle <= 1.125f && my_angle >= 0.375f) // UP LEFT/RIGHT
    {      
        i_my_angle = UP_RIGHT;                            
    }
                                                                                           
    return(i_my_angle);     
}


bool Change_Texture(sString sfilename, int loop)
{
#ifdef SWITCH
  	bool Status=false;
    GLuint type = GL_RGBA;
    Texture ply_tex;
    int the_tex_id=0; 

	#if IS_USING_DIRECTX == 1
	if(RENDERER == RENDER_DIRECTX)
	if(loop >= 0 && loop < 100)
	{
		HRESULT texture_err; 
		Texture stexture;

		SAFE_RELEASE(texture[loop]);   
            
        strcat(sfilename.string,".tga"); 

		sLoadCompressedTGADX(&stexture, sfilename.string);

		// Create empty IDirect3DTexture9*
		texture_err = d3ddev->CreateTexture(stexture.width, stexture.height, 1, 0, 
							   D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture[loop], 0);

		D3DLOCKED_RECT rect;  

		texture[loop]->LockRect( 0, &rect, 0, D3DLOCK_DISCARD );
		unsigned char* dest = static_cast<unsigned char*>(rect.pBits);
		memcpy(dest, &stexture.imageData[0], stexture.imageSize);
		texture[loop]->UnlockRect(0); 

		if(stexture.imageData) 
		{
			free(stexture.imageData);
		}

       if(texture_err == D3DERR_INVALIDCALL)
	       MessageBox(NULL,"Error loadinf DirectX texture : D3DERR_INVALIDCALL","ERROR",MB_OK|MB_ICONEXCLAMATION);

       if(texture_err == D3DERR_NOTAVAILABLE)
	       MessageBox(NULL,"Error loadinf DirectX texture : D3DERR_NOTAVAILABLE","ERROR",MB_OK|MB_ICONEXCLAMATION);
	   
       if(texture_err == D3DERR_OUTOFVIDEOMEMORY)
	       MessageBox(NULL,"Error loadinf DirectX texture : D3DERR_OUTOFVIDEOMEMORY","ERROR",MB_OK|MB_ICONEXCLAMATION);
	   
       if(texture_err == D3DXERR_INVALIDDATA)
	       MessageBox(NULL,"Error loadinf DirectX texture : D3DXERR_INVALIDDATA","ERROR",MB_OK|MB_ICONEXCLAMATION);
	   
       if(texture_err == E_OUTOFMEMORY)
	       MessageBox(NULL,"Error loadinf DirectX texture : E_OUTOFMEMORY","ERROR",MB_OK|MB_ICONEXCLAMATION);


	}
	#endif

	if(RENDERER == RENDER_OPENGL)
	if(loop >= 0 && loop < 200)
	{

        for(int i=0;i<g_fx_id;i++)
		if(i < 75)
        {
            if(a_texture[i].id == loop)
                the_tex_id=i;
        }
		 
		if(texID[loop])
			glDeleteTextures(1, &texID[loop]);
        
        if( texture_fx[loop] == 2 || texture_fx[loop] == 3 || texture_fx[loop] == 4)
            animation_fx[loop] = LoadAnim( sfilename, loop, the_tex_id);
        else
            animation_fx[loop] = -1; 
                             
        if( texture_fx[loop] == 1 || texture_fx[loop] == 3 || texture_fx[loop] == 4 || texture_fx[loop] == 5)
        {
        
            strcat(sfilename.string,".tga");  
            
		    if(!(sLoadTGA(&ply_tex, sfilename.string)) )
                return 0;

        }
		else
		{
            strcat(sfilename.string,".tga");
		    if(!(LoadTGA(&ply_tex, sfilename.string)) )
                return 0;

        }
    
	    glGenTextures(1, &ply_tex.texID); 		

        texID[loop] = ply_tex.texID;
            	
        glBindTexture(GL_TEXTURE_2D, ply_tex.texID); 
                
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                        			
        if(ply_tex.bpp==24)
		    type = GL_RGB;
        else
		    type = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, type, ply_tex.width, ply_tex.height, 0, type, GL_UNSIGNED_BYTE, ply_tex.imageData);
        
        if (ply_tex.imageData)
			free(ply_tex.imageData);
			
	} // loop >= 0

      return(Status); 
#else
	return true;
#endif
   
}

void VG_SlowMO(int duration, float strength)
{

	VG_slowmo_timer = (int)TimerGetTime() + duration;
	VG_slowmof = strength;        
	VG_SLOWMO = true; 

	VG_Reset_all_anims();
	
}


void VG_Restrain_sprite(int index, int j)
{
	float inc_x = 0.0f;

	if(index < 0 || index >= TOTAL_NO_SPRITES)
		return;

	inc_x = sprite[index].w - sprite[index].x;  

	if(j == 0)  
		VG_1_CORNERED = false;    
	else 
		VG_2_CORNERED = false;    

	if((sprite[index].w - sprite[index].box_width/2.0f) <= (sprite[1].x + 0.075f))
	{
		sprite[index].w = (sprite[1].x + 0.075f) + (sprite[index].box_width/2.0f);
		sprite[index].x = sprite[index].w - inc_x;
	}
	if((sprite[index].w + (sprite[index].box_width*1.5f)) >= (sprite[1].x - 0.075f) + sprite[1].width)
	{
		sprite[index].w = ((sprite[1].x - 0.075f) + sprite[1].width) - (sprite[index].box_width*1.5f);
		sprite[index].x = sprite[index].w - inc_x;
	}
	 
	if((sprite[index].w - sprite[index].box_width/2.0f) <= (sprite[1].x + 0.080f))
	{
	//	if(sprite[index].movement == RIGHT)   
		if(j == 0) 
			VG_1_CORNERED = true;  
		else 
			VG_2_CORNERED = true;
	}

	if((sprite[index].w + (sprite[index].box_width*1.5f)) >= (sprite[1].x - 0.080f) + sprite[1].width)
	{
	//	if(sprite[index].movement == LEFT)
		if(j == 0)
			VG_1_CORNERED = true;
		else
			VG_2_CORNERED = true;
	}

}


int New_Sprite(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int sideways, int upways, int state, int linked_sprite, int tex_id, int a_global, float angle, int p_type, int goto_point)
{ 
  
    int end_id=-1;   
    int loop=0;
    bool new_sprite=true; 
    bool go_ahead=true;
    int temp_row_x=0;
    int temp_row_y=0;  
    int temp_index=0;
    float mid_x=0.0f, mid_y=0.0f;
	int rnd=0;
    
	// Re-use dead sprites...
/*	for(int i = 0; i< no_sprites;i++)
	if(sprite[i].turn_off == true) 
	{
		sprite[i].turn_off = false;
		end_id = i;
		new_sprite = false;
		break;
	}*/

    if(go_ahead==true)    
	if(new_sprite == true)
	if(no_sprites < (TOTAL_NO_SPRITES-2))
    if(end_id == -1) 
    { 

        end_id = no_sprites;
        no_sprites++; 
		
    }
   
    if(go_ahead==true)    
    if(end_id >= 0 && end_id < TOTAL_NO_SPRITES)    
    {          
                       
		sprite[end_id].turn_off = false;

        sprite[end_id].id = tex_id; 
                                                                
        sprite[end_id].x = x;      
        sprite[end_id].y = y; 
        
        sprite[end_id].w = w; 
        sprite[end_id].z = z;   
          
        sprite[end_id].width = width;
        sprite[end_id].height = height;       
                        
        sprite[end_id].box_width = box_width;
        sprite[end_id].box_height = box_height;
         
        if(anim_state != NO_ANIM)   
		if(sprite[end_id].id >= 0 && sprite[end_id].id < 512)
        {
            sprite[end_id].fx_id = animation_fx[sprite[end_id].id];
	
            sprite[end_id].anim = anim; 
            sprite[end_id].cur = 0;     
                         
            sprite[end_id].anim_state = anim_state;
#ifndef DREAMCAST
			if(sprite[end_id].anim >= 0 && sprite[end_id].anim < 512)
			if(sprite[end_id].cur >= 0 && sprite[end_id].cur < 512)
	            sprite[end_id].frame = a_texture[sprite[end_id].fx_id].anims[sprite[end_id].anim][sprite[end_id].cur];
#else
	        if(sprite[end_id].anim >= 0 && sprite[end_id].anim < 512)
			if(sprite[end_id].cur >= 0 && sprite[end_id].cur < 512)
	            sprite[end_id].frame = a_texture_get_anims_secondlayer(sprite[end_id].fx_id, sprite[end_id].anim, sprite[end_id].cur);
#endif
            
            sprite[end_id].base_anim = sprite[end_id].anim;
                    
            Set_Sprite(end_id, anim, anim_state, ANIM_SPRITE, ANIM_WALKING);
            
        }    
           
        sprite[end_id].alpha = alpha;  

        sprite[end_id].priority = priority;
            
        sprite[end_id].type = type;      

		sprite[end_id].sector = state;
        
        sprite[end_id].mouseover = false;

		sprite[end_id].invulnerable = false;  
        
        sprite[end_id].score = 0;   
        
        sprite[end_id].all_timer = 0; 

		sprite[end_id].action_timer = 0;

        sprite[end_id].linked_sprite = linked_sprite;
        
        sprite[end_id].angle = angle; 
		
        sprite[end_id].grab_switch = true; 
		 
		sprite[end_id].on_mud = false;   

		sprite[end_id].status = 0; 

		sprite[end_id].onCreate = 0;

		sprite[end_id].onCreate_action = -1;  

		sprite[end_id].emy_shoot = 0;

		sprite[end_id].sticky = false;

		if(sideways != -1)
			sprite[end_id].direction = sideways;

    }  
     
	if(new_sprite == true)
    if(end_id == -1) 
    { 
		if(no_sprites > 0)
			no_sprites--; 
    }
	 
    return(end_id); 
}


void VG_Particles(float x, float y, float angle, int priority, int anim) 
{ 
	 

	// Note that box_width is used to take angle...

	New_FX(x, y, x, y, anim, PLAY, angle, 0.007f, 0.007f, 0.007f, 1, GFX, 1.0f, 0, -1, FX_VG_SWEAT, -1, 12, 0, 0, -1); 
	New_FX(x, y, x, y, anim, PLAY, angle-0.1f, 0.008f, 0.008f, 0.008f, 1, GFX, 1.0f, 0, -1, FX_VG_SWEAT2, -1, 12, 0, 0, -1); 
	New_FX(x, y, x, y, anim, PLAY, angle+0.1f, 0.006f, 0.006f, 0.006f, 1, GFX, 1.0f, 0, -1, FX_VG_SWEAT, -1, 12, 0, 0, -1); 

	New_FX(x, y, x, y, anim, PLAY, angle+0.25f, 0.007f, 0.007f, 0.007f, 3, GFX, 1.0f, 0, -1, FX_VG_SWEAT2, -1, 12, 0, 0, -1); 
	New_FX(x, y, x, y, anim, PLAY, angle+0.27f, 0.008f, 0.008f, 0.008f, 3, GFX, 1.0f, 0, -1, FX_VG_SWEAT, -1, 12, 0, 0, -1); 
	New_FX(x, y, x, y, anim, PLAY, angle-0.15f, 0.006f, 0.006f, 0.006f, 3, GFX, 1.0f, 0, -1, FX_VG_SWEAT2, -1, 12, 0, 0, -1); 


}


void VG_Resize_Sprite(int index) 
{

	if(!(VG_RESIZE_X == 0.0f || VG_RESIZE_Y == 0.0f))
	{
		sprite[index].width += sprite[index].width * VG_RESIZE_X; 
		sprite[index].height += sprite[index].height * VG_RESIZE_Y; 

		sprite[index].box_width += sprite[index].box_width * VG_RESIZE_X; 
		sprite[index].box_height += sprite[index].box_height * VG_RESIZE_Y; 
				
		sprite[index].x -= (sprite[index].width * VG_RESIZE_X)/2; 
		sprite[index].w -= (sprite[index].box_width * VG_RESIZE_X)/2;  
	}



}