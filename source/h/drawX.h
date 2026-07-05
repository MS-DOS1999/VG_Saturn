
#ifdef SWITCH
//#include <gl\gl.h>
#endif
#include "globals.h"
 
void Z_Buffer(bool is_a_sprite);
void Set_Values(float x, float y, float R, float G, float B, float A, float u, float v);
#ifdef DREAMCAST
void Set_ValuesCustom(float x, float y, float R, float G, float B, float A, float u, float v);
float Get_Texture_Coord(int id, int fx_id, int frame, bool is_a_sprite, unsigned int &customID);
#else
float Get_Texture_Coord(int id, int fx_id, int frame, bool is_a_sprite);
#endif

unsigned int customTiles = 0;
bool useCustomTile = false;


void Set_Values(float x, float y, float R, float G, float B, float A, float u, float v)
{
     
    Gvector[0] = x; 

    Gvector[1] = y;
    
    if(R != -1)
      Gcolor[0] = R;
    if(G != -1)
      Gcolor[1] = G;
    if(B != -1)
      Gcolor[2] = B;
    if(A != -1)
      Gcolor[3] = A;
    

    Gtex[0] = u;
#ifdef DREAMCAST
    Gtex[1] = 1.0f - v;
#elif SWITCH
    Gtex[1] = v;
#endif
   
}
#ifdef DREAMCAST
bool lastGetCoordIs256 = false;
bool xSetupCustom = false;
bool ySetupCustom = false;
void Set_ValuesCustom(float x, float y, float R, float G, float B, float A, float u, float v)
{
     
    Gvector[0] = x; 

    Gvector[1] = y;
    
    if(R != -1)
      Gcolor[0] = R;
    if(G != -1)
      Gcolor[1] = G;
    if(B != -1)
      Gcolor[2] = B;
    if(A != -1)
      Gcolor[3] = A;
    

    Gtex[0] = u;
    Gtex[1] = v;
    if(xSetupCustom == false)
    {
        Gtex[0] *= 2.0f;
    }
    else
    {
        Gtex[0] -= 0.5f;
        Gtex[0] *= 2.0f;
    }

    if(lastGetCoordIs256 == false)
    {
        if(ySetupCustom == false)
        {
            Gtex[1] *= 2.0f;
        }
        else
        {
            Gtex[1] -= 0.5f;
            Gtex[1] *= 2.0f;
        }
    }
    
    

    Gtex[1] = 1.0f - Gtex[1];

}
#endif

#ifdef DREAMCAST
float Get_Texture_Coord(int id, int fx_id, int frame, bool is_a_sprite, unsigned int &customID)
#else
float Get_Texture_Coord(int id, int fx_id, int frame, bool is_a_sprite)
#endif
{
	//printf("TEXCOORD id: %d fx_id: %d frame: %d\n", id, fx_id, frame);
    float testX = 0.0f, testY = 0.0f; 
    float testX1 =0.0f, testY1 = 0.0f;
    int temp=0;
    int temp1=0; 
    int temp2=0;
    int temp3=0;    
      
            // Animated Texture
			if( id >= 0 && id < 200)
			if(fx_id >= 0 && fx_id < 75)
            if( texture_fx[id] == 2 || texture_fx[id] == 3 || texture_fx[id] == 4)
            {
                
                     
                if(a_texture[fx_id].column == 0)  
                    a_texture[fx_id].column = 1;
                 
                // Calculate X-texture co-ords                      
                temp = frame; // 3  
				 
				if( a_texture[fx_id].column > 0)
                    temp1 = a_texture[fx_id].frames / a_texture[fx_id].column; // 16 / 2 == 8

				if(temp1 > 0)
					temp = (frame % temp1); // 3 % 8 == 3
                
                if(temp1 > 0)
                   testX1 = 1.0f / temp1; // 1.0 / 8 == 0.125

				testX = testX1 * temp; // Increment multiplied by frame row

                //printf("frames %d column %d testX %f\n", a_texture[fx_id].frames, a_texture[fx_id].column, testX);

             //   testX  -= 0.01f;              
             //   testX1 -= 0.1f; 
				      
				// testX is 0.0 needs to be 0.5 
				// testx1 is 0.5 needs to be 1.0
                
                // Calculate Y-texture co-ords
                temp = frame;

                if( a_texture[fx_id].column > 0)
					temp1 = a_texture[fx_id].frames/a_texture[fx_id].column; // 16
                
                if(temp1 != 0)
					temp = temp / temp1;  // Gets row number 0 - column 
				 
#if IS_USING_DIRECTX == 1   
				if(RENDERER == RENDER_DIRECTX)
				{

                if( a_texture[fx_id].column == 1)
                {
                    testY = 0.9999f;
                    testY1 = 0.00f;
                }                     
                
                if( a_texture[fx_id].column == 2)
                switch(temp)
                {
                    case 0:        
                        testY = 0.9999f;
                        testY1 = 0.50f; 
                    break;
                    case 1:        
                        testY = 0.4999f;
                        testY1 = 0.00f;
                    break;
                }      
                if( a_texture[fx_id].column == 4 )
                switch(temp)
                { 
                            
                    case 0:        
                        testY = 0.9999f;
                        testY1 = 0.75f;
                    break;
                    case 1:        
                        testY = 0.7499f;
                        testY1 = 0.50f;
                    break;
                    case 2:        
                        testY = 0.4999f;
                        testY1 = 0.25f;
                    break;
                    case 3:        
                        testY = 0.2499f;
                        testY1 = 0.00f;
                    break;
                    
                } 
                if( a_texture[fx_id].column == 8 )
                switch(temp) 
                {
                    case 0:        
                        testY = 0.9999f;
                        testY1 = 0.875f;
                    break; 
                    case 1:        
                        testY = 0.8749f;
                        testY1 = 0.750f;
                    break;
                    case 2:        
                        testY = 0.7499f;
                        testY1 = 0.625f;
                    break;
                    case 3:        
                        testY = 0.6249f;
                        testY1 = 0.500f;
                    break; 
                    case 4:        
                        testY = 0.4999f;
                        testY1 = 0.375f;
                    break;
                    case 5:        
                        testY = 0.3749f;
                        testY1 = 0.250f;
                    break;
                    case 6:        
                        testY = 0.2499f;
                        testY1 = 0.125f;
                    break;                     
                    case 7:        
                        testY = 0.1249f;
                        testY1 = 0.000f;
                    break;                     
                }       
                if( a_texture[fx_id].column == 16 )
                switch(temp) 
                { // 0.0625
                    case 0:        
                        testY = 0.9999f;
                        testY1 = 0.9375f;
                    break; 
                    case 1:        
                        testY = 0.9375f;
                        testY1 = 0.8750f;
                    break;
                    case 2:        
                        testY = 0.8750f;
                        testY1 = 0.8125f;
                    break;
                    case 3:        
                        testY = 0.8125f;
                        testY1 = 0.7500f;
                    break; 
                    case 4:        
                        testY = 0.7500f;
                        testY1 = 0.6875f;
                    break;
                    case 5:        
                        testY = 0.6875f;
                        testY1 = 0.6250f;
                    break;
                    case 6:        
                        testY = 0.6250f;
                        testY1 = 0.5625f;
                    break;                     
                    case 7:        
                        testY = 0.5625f;
                        testY1 = 0.5000f;
                    break;    
                    case 8:        
                        testY = 0.5000f;
                        testY1 = 0.4375f;
                    break; 
                    case 9:        
                        testY = 0.4375f;
                        testY1 = 0.3750f;
                    break;
                    case 10:        
                        testY = 0.3750f;
                        testY1 = 0.3125f;
                    break;
                    case 11:        
                        testY = 0.3125f;
                        testY1 = 0.2500f;
                    break; 
                    case 12:        
                        testY = 0.2500f;
                        testY1 = 0.1875f;
                    break;
                    case 13:        
                        testY = 0.1875f;
                        testY1 = 0.1250f;
                    break; 
                    case 14:         
                        testY = 0.1250f;
                        testY1 = 0.0625f;
                    break;                      
                    case 15:         
                        testY = 0.0625f;
                        testY1 = 0.000f;
                    break;                  
                }    
				}    
#endif 
				

				if(RENDERER == RENDER_OPENGL)
				{

                if( a_texture[fx_id].column == 1)
                {
                    testY = 0.9999f;
                    testY1 = 0.00f;
                }                  
                
                if( a_texture[fx_id].column == 2)
                switch(temp)
                {
                    case 0:        
                        testY = 0.9999f;
                        testY1 = 0.50f;
                    break;
                    case 1:        
                        testY = 0.4999f;
                        testY1 = 0.00f;
                    break;
                }      
                if( a_texture[fx_id].column == 4 )
                switch(temp)
                { 
                            
                    case 0:        
                        testY = 0.9999f;
                        testY1 = 0.75f;
                    break;
                    case 1:        
                        testY = 0.7499f;
                        testY1 = 0.50f;
                    break;
                    case 2:        
                        testY = 0.4999f;
                        testY1 = 0.25f;
                    break;
                    case 3:        
                        testY = 0.2499f;
                        testY1 = 0.00f;
                    break;
                    
                } 
                if( a_texture[fx_id].column == 8 )
                switch(temp) 
                {
                    case 0:        
                        testY = 0.9999f;
                        testY1 = 0.875f;
                    break; 
                    case 1:        
                        testY = 0.8749f;
                        testY1 = 0.750f;
                    break;
                    case 2:        
                        testY = 0.7499f;
                        testY1 = 0.625f;
                    break;
                    case 3:        
                        testY = 0.6249f;
                        testY1 = 0.500f;
                    break; 
                    case 4:        
                        testY = 0.4999f;
                        testY1 = 0.375f;
                    break;
                    case 5:        
                        testY = 0.3749f;
                        testY1 = 0.250f;
                    break;
                    case 6:        
                        testY = 0.2499f;
                        testY1 = 0.125f;
                    break;                     
                    case 7:        
                        testY = 0.1249f;
                        testY1 = 0.000f;
                    break;                     
                }       
                if( a_texture[fx_id].column == 16 )
                switch(temp) 
                { // 0.0625
                    case 0:        
                        testY = 0.9999f;
                        testY1 = 0.9375f;
                    break; 
                    case 1:        
                        testY = 0.9375f;
                        testY1 = 0.8750f;
                    break;
                    case 2:        
                        testY = 0.8750f;
                        testY1 = 0.8125f;
                    break;
                    case 3:        
                        testY = 0.8125f;
                        testY1 = 0.7500f;
                    break; 
                    case 4:        
                        testY = 0.7500f;
                        testY1 = 0.6875f;
                    break;
                    case 5:        
                        testY = 0.6875f;
                        testY1 = 0.6250f;
                    break;
                    case 6:        
                        testY = 0.6250f;
                        testY1 = 0.5625f;
                    break;                     
                    case 7:        
                        testY = 0.5625f;
                        testY1 = 0.5000f;
                    break;    
                    case 8:        
                        testY = 0.5000f;
                        testY1 = 0.4375f;
                    break; 
                    case 9:        
                        testY = 0.4375f;
                        testY1 = 0.3750f;
                    break;
                    case 10:        
                        testY = 0.3750f;
                        testY1 = 0.3125f;
                    break;
                    case 11:        
                        testY = 0.3125f;
                        testY1 = 0.2500f;
                    break; 
                    case 12:        
                        testY = 0.2500f;
                        testY1 = 0.1875f;
                    break;
                    case 13:        
                        testY = 0.1875f;
                        testY1 = 0.1250f;
                    break; 
                    case 14:         
                        testY = 0.1250f;
                        testY1 = 0.0625f;
                    break;                      
                    case 15:        
                        testY = 0.0625f;
                        testY1 = 0.000f;
                    break;                  
                }     
				}

          
    }

#ifdef DREAMCAST
    if(texID[id] >= 666666 && texID[id] < 777777)
    {
        lastGetCoordIs256 = true;
        int baseID_cus = 0;
        for (size_t lol = 0; lol < tex2048x256.size(); ++lol)
        {
            if(tex2048x256[lol].baseID == texID[id])
                baseID_cus = lol;
        }

        if(testX < 0.5)
        {
            xSetupCustom = false;
            customID = tex2048x256[baseID_cus].topLeft;
        }
        else if(testX >= 0.5)
        {
            xSetupCustom = true;
            customID = tex2048x256[baseID_cus].topRight;
        }
    }
    else if(texID[id] >= 777777)
    {
        lastGetCoordIs256 = false;
        int baseID_cus = 0;
        for (size_t lol = 0; lol < tex2048x2048.size(); ++lol)
        {
            if(tex2048x2048[lol].baseID == texID[id])
                baseID_cus = lol;
        }

        if(testX < 0.5 && testY < 0.5)
        {
            xSetupCustom = false;
            ySetupCustom = false;
            customID = tex2048x2048[baseID_cus].bottomLeft;
        }
        else if(testX >= 0.5 && testY < 0.5)
        {
            xSetupCustom = true;
            ySetupCustom = false;
            customID = tex2048x2048[baseID_cus].bottomRight;
        }
        else if(testX < 0.5 && testY >= 0.5)
        {
            xSetupCustom = false;
            ySetupCustom = true;
            customID = tex2048x2048[baseID_cus].topLeft;
        }
        else if(testX >= 0.5 && testY >= 0.5)
        {
            xSetupCustom = true;
            ySetupCustom = true;
            customID = tex2048x2048[baseID_cus].topRight;
        }
    }
#endif
    
    global_u = testX;
    global_u1 = testX1;
      
    global_v  = testY; 
    global_v1 = testY1;  

    //printf("Global_u %f Global_u1 %f Global_v %f Global_v1 %f\n", global_u, global_u1, global_v, global_v1);

	return 0;
      
}


void Z_Buffer(bool is_a_sprite)
{
    
    int temp=0;
    int temp1=0; 
    int temp2 =0;
    float var2=0;
	float original_Y=0.0f;
    
    if(is_a_sprite == false)
    {
        memset(var4, 0, sizeof(var4) );
        memset(hud_list, 0, sizeof(hud_list) );    
    }

    if(is_a_sprite == true)    
    { 
                   
    memset(var3, 0, sizeof(var3) );               
    memset(sprite_list, 0, sizeof(sprite_list) ); 
                        
    for( int i=0;i<new_no_sprites;i++)
	if(i >= 0 && i < TOTAL_NO_SPRITES)
    {  
        if(var5[i] < TOTAL_NO_SPRITES)  
        { 
			if(var5[i] >= 0 && var5[i] < 1000)
				sprite_list[i] = sprite[var5[i]].priority; // in no order just adds the priority
        } 
        else 
        {     
			if( var5[i]-TOTAL_NO_SPRITES >= 0 && var5[i]-TOTAL_NO_SPRITES < TOTAL_NO_FX_SPRITES) 
				sprite_list[i] = Fx[var5[i]-TOTAL_NO_SPRITES].priority; // in no order just adds the priority
        }    
             
    }   
        
    // Set-up display order using calculated priority list
    for(int i=0;i<new_no_sprites;i++)
	if(i >= 0 && i < 1000)
        if(sprite_list[i] == 6)
        { 
			if(i >= 0 && i < TOTAL_NO_SPRITES)
			if(temp >= 0 && temp < TOTAL_NO_SPRITES)
			{
				var3[temp] = var5[i];
				sprite_list[i] = -1;
			}
            temp++;
        }
           
    // Set-up display order using calculated priority list
    for(int i=0;i<new_no_sprites;i++)
	if(i >= 0 && i < 1000)
        if(sprite_list[i] == 5)  
        {
			if(i >= 0 && i < TOTAL_NO_SPRITES)
			if(temp >= 0 && temp < TOTAL_NO_SPRITES)
			{
				var3[temp] = var5[i];
				sprite_list[i] = -1;
			}
            temp++;
        } 
   
    // Set-up display order using calculated priority list
    for(int i=0;i<new_no_sprites;i++)
	if(i >= 0 && i < 1000)
        if(sprite_list[i] == 4)
        {
			if(i >= 0 && i < TOTAL_NO_SPRITES)
			if(temp >= 0 && temp < TOTAL_NO_SPRITES)
			{
				var3[temp] = var5[i];
				sprite_list[i] = -1;
			}
            temp++;
        } 
 
    // Set-up display order using calculated priority list
    for(int i=0;i<new_no_sprites;i++)
	if(i >= 0 && i < 1000)
        if(sprite_list[i] == 3)
        {
			if(i >= 0 && i < TOTAL_NO_SPRITES)
			if(temp >= 0 && temp < TOTAL_NO_SPRITES)
			{
				var3[temp] = var5[i];
				sprite_list[i] = -1;
			}
            temp++;
        } 
     
    // Set-up display order using calculated priority list
    for(int i=0;i<new_no_sprites;i++)
	if(i >= 0 && i < TOTAL_NO_SPRITES)
    {
        var2 = -1000;
        temp1 = -1; 
        temp2 = -1;
            
        for(int loop=0;loop<new_no_sprites;loop++)
		if(loop >= 0 && loop < 1000)
        if(sprite_list[loop] == 2)  
        {

		  if(loop >= 0 && loop < TOTAL_NO_SPRITES)
          if(var5[loop] >= 0 && var5[loop] < TOTAL_NO_SPRITES)                   
          if(var2 < sprite[var5[loop]].y )
          {
            var2 = sprite[var5[loop]].y;    

            temp1 = var5[loop]; 
            temp2 = loop;       
          } 
		  if(loop >= 0 && loop < TOTAL_NO_SPRITES)
          if(var5[loop] >= TOTAL_NO_SPRITES) 
		  {	 
			  if(var5[loop]-TOTAL_NO_SPRITES >= 0 && var5[loop]-TOTAL_NO_SPRITES < TOTAL_NO_FX_SPRITES)
	          if(var2 < Fx[var5[loop]-TOTAL_NO_SPRITES].y) 
   	          {
   	   		      var2 = Fx[var5[loop]-TOTAL_NO_SPRITES].y;  

   	        	  temp1 = var5[loop];  
	              temp2 = loop;
			  }  

		  }    
        
        }
        
        if(temp >= 0 && temp < TOTAL_NO_SPRITES && temp1 >= 0)
		if(temp2 >= 0 && temp2 < 1000)
        {
            var3[temp] = temp1; 
            sprite_list[temp2] = -1;
            temp++;         
        }
        
    }  
    // Set-up display order using calculated priority list
    for(int i=0;i<new_no_sprites;i++)
	if(i >= 0 && i < 1000)
        if(sprite_list[i] == 1 && temp >= 0)
        {
			if(i >= 0 && i < TOTAL_NO_SPRITES)
			if(temp >= 0 && temp < TOTAL_NO_SPRITES)
			{
				var3[temp] = var5[i];
				sprite_list[i] = -1;
			}
            temp++;       
        }
    
    // Set-up display order using calculated priority list
    for(int i=0;i<new_no_sprites;i++)
	if(i >= 0 && i < 1000)
        if(sprite_list[i] == 0 && temp >= 0)
        {
			if(i >= 0 && i < TOTAL_NO_SPRITES)
			if(temp >= 0 && temp < TOTAL_NO_SPRITES)
			{
				var3[temp] = var5[i];
				sprite_list[i] = -1;
			}
            temp++;
        }
   
    } 
    
    if(is_a_sprite == false)
    {
                   
    temp=0;  
    
    for(int i=0;i<hud_no_sprites;i++)
	if(i >= 0 && i < TOTAL_NO_HUD)
        hud_list[i] = hud[i].priority; // in no order just adds the priority
 
    // Set-up display order using calculated priority list
    for(int i=0;i<hud_no_sprites;i++)
	if(i >= 0 && i < 75)
        if(hud_list[i] == 5)
        {
			if(temp >= 0 && temp < 75)
				var4[temp] = i;
            hud_list[i] = -1;
            temp++;
        }
    // Set-up display order using calculated priority list
    for(int i=0;i<hud_no_sprites;i++)
	if(i >= 0 && i < 75)
        if(hud_list[i] == 4)
        {
			if(temp >= 0 && temp < 75)
				var4[temp] = i;
            hud_list[i] = -1;
            temp++;
        }
    // Set-up display order using calculated priority list
    for(int i=0;i<hud_no_sprites;i++)
	if(i >= 0 && i < 75)
        if(hud_list[i] == 3)
        {
			if(temp >= 0 && temp < 75)
				var4[temp] = i;
            hud_list[i] = -1;
            temp++;
        }
    // Set-up display order using calculated priority list
    for(int i=0;i<hud_no_sprites;i++)
	if(i >= 0 && i < 75)
        if(hud_list[i] == 2)
        {
			if(temp >= 0 && temp < 75)
				var4[temp] = i;
            hud_list[i] = -1;
            temp++;
        }  
    // Set-up display order using calculated priority list
    for(int i=0;i<hud_no_sprites;i++)
	if(i >= 0 && i < 75)
        if(hud_list[i] == 1) 
        {
			if(temp >= 0 && temp < 75)
				var4[temp] = i;
            hud_list[i] = -1;
            temp++;
        }                                   
    // Set-up display order using calculated priority list
    for(int i=0;i<hud_no_sprites;i++)
	if(i >= 0 && i < 75)
        if(hud_list[i] == 0)
        {
			if(temp >= 0 && temp < 75)
				var4[temp] = i;
            hud_list[i] = -1;
            temp++; 
        }
              
    }    
    
}
 
