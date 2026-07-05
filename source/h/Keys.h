
#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>
#include "texture.h"											// Header File Containing Our Texture Structure ( NEW )
#include "globals.h"
#include "audiere.h"  

#define VK_OEM_PERIOD     0xBE   // '.' any country 
     
using namespace audiere;    

extern void KillGLWindow();
extern int CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag);
extern int CreateDXWindow(char* title, int width, int height, int bits, bool fullscreenflag);
extern bool LoadScene(int episode1, int scene1, bool delete_textures);
extern bool DumpScene(char *filename); 
extern bool Dump_BG( char *filename ); 
extern bool Dump_COL( char *filename  );
extern bool Spawn_A_Guy(int number_of_dudes, int best_point, bool buddy, int trap, int sprite_point, int goto_point);
extern void Spawn_Pickup(int index, int type);
extern void Help_Limits();
extern void Level_Up(int loop);
extern void Bit_Shift( int the_value1, int bit_to_shift, int bit_value);
extern int Get_Bit_Shift( int the_value1, int bit_to_shift);  
extern void Calculate_Inventory();
extern void Calculate_Health(int amount, bool share, int index, bool regen);
extern void Calculate_Lifebar();
extern void Calculate_Bullets(); 
extern float Get_Weapon_Stats(int the_value, int type);
extern bool DumpTemp( char *filename );
extern bool LoadTemp( char *filename );
extern void Draw_Light(bool render_all);
extern void Special_Attack(int type);
extern void Create_Frag_Effect(float x1, float y1);
extern void Create_Gibs_Effect(int index, bool bones, int type);
extern void Create_Explosion(int guy_shot);
extern void Set_Timer(unsigned long time);
extern void Start_Game();  
extern void Init_Player();  
extern void Mission_Accomplished(bool active);
extern int New_Sprite(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int sideways, int upways, int state, int linked_sprite, int tex_id, int a_global, float angle, int p_type, int goto_point);
extern bool Has_This_Item(int type, int value);
extern void New_Healthbar(int index, int quick_display);
extern void Rank_Timer(int index, int status);
extern void Create_Star_Effect(float x1, float y1, float size, int tex_id);
extern void Run_Mouse_Limits(int f_rate);
extern bool sLoadCompressedTGADX(Texture * texture, char * filename);
extern bool SaveCFG();

extern void TimerInit(void);
extern float TimerGetTime();   
extern void Time_conversion();
extern void Set_Sprite(int id, int anim, int state, int hud_or_sprite, bool reset);
extern void DisplayText(int time,  int temp_text_id, int temp_txt_cur, bool overwrite, int text_type );
extern int Test_Collision(object collision, float x_inc, float y_inc, bool bullet, int no_test, bool quick_test);
extern void Set_Door_Open_Close(int no, int open_close);
extern void Barrel_Explode(int no, bool death);
extern void Add_Health(int value, bool bounce, int no_test, bool explosion);
extern void Add_Ammo(int value, bool bounce);
extern bool New_FX(float x, float y, float w, float z, int anim, int anim_state, float box_width, float box_height, float width, float height, int priority, int type, float alpha, int i_value, int i_type, int state, int linked_sprite, int tex_id, int i_value1, int i_value2, int i_value3);
extern float Sprite_Distance(object collision1, object collision2);
extern void Camera_Shake(int type);
extern void Hud_Face(int type);
extern bool Flip_bool(bool flip);
extern bool DumpNodes( char *filename );        
extern void Text_end();
extern bool SaveLevel( sString sfilename ); 
extern bool LoadLevel( sString sfilename, bool startup  );
extern void Alert_Buddies(int loop, float range);
extern int LoadAnim( sString sfilename, int texture_id, int the_tex_id );
extern bool LoadTGA(Texture *, char *);
extern bool sLoadTGA(Texture *, char *);
extern void Use_Potion(bool load);
extern void Calculate_Exp(int index, int experience);
extern void Calculate_Stats();
extern void Medal_Awarded(int type);
extern void Remove_Item(int item_type, int item_value, int item_value1, bool remove_all);
extern void Set_Camera(int f_rate, bool startup);
extern void Do_Player_Accel(int f_rate);
extern void Run_Legs();
extern void Run_Hats();
extern void Check_Crouch(int loop, bool loading);
extern void DamageNumber( int loop, int damage, int is_blue ); 
extern void sta2_Proc_Level();

bool DumpPoints( char *filename );
extern GLvoid Zoom(float fzoom);  
void Quit_Code(bool quit_active);
bool Test_Password();
void Carry_code();
void Gravity(int f_rate1);
void Calculate_Edges(int testme, int solid);
void Generate_Map(int index, int base_tile);
void Generate_Bush(int i, int j, int base_tile, int dir);
void Remove_Bush(int row_x, int row_y);
void Check_For_Grenade();
void Grab_Data_For_Map();

// Local Routines

bool Change_Texture(sString sfilename, int loop);

int Key_Handler(bool keys[256], object *display, int f_rate)
{  
    
    scroll_window=0.0;
    int g_index=0;
    int safe_g_index=0;
    int rnd=0;
    int rnd1=0;
    bool a_switch=false;
    int found_the_gun=-1;
    float mid_x=0.0, mid_y=0.0;
    float tar_x=0.0, tar_y=0.0;
	float cam_x=0.0, cam_y=0.0;
	float angle=0.0; 
	float deltax=0.0, deltay=0.0;
    int test_col=0;
	int created_a_window=0;
	bool is_a_gallery=false;
	int pack_id=0;
    
     if(f_rate <= 0)
         f_rate = 1;    

	// Code that needs running very fast...
	if(SPEED_INCREASE == 1) 
	{ 

         // Camera moving code  
         if(!mode && game_mode == WALK) 
		 if(game_paused == false)  
		 if(disable_scrolling == false)  	     
         {  

		//	if((int)TimerGetTime() > camera_startup_timer)  
				Run_Mouse_Limits( f_rate );

 		 	Set_Camera( f_rate, false );   

         }  	

         // Camera moving code 
         if(f_rate < 100)  
		 if(!mode && game_mode == WALK) 
		 if(game_paused == false)
         if(cam_moving == true) 
         { 
        /*     if(cam_speed == 0)
                 temp_speed = 0.0002f*(float)f_rate; 
             if(cam_speed == 1)
                 temp_speed = 0.0003f*(float)f_rate;
             if(cam_speed == 2)
                 temp_speed = 0.0005f*(float)f_rate;
             
             cam_x = -(camX);
             cam_y = -(camY);
             
			 if(next_cam >= 0)              
	             angle = atan2(cam_y - points[next_cam].y, cam_x - points[next_cam].x);
             
             deltax = cos(angle);
             deltay = sin(angle);
    
             deltax *= temp_speed; 
             deltay *= temp_speed; 
 
             camY += deltay;  
             camX += deltax; 
                                        
          	 if( camX > ( map_startX-zoom_factor) )        
             	camX = map_startX-zoom_factor;    
 
             if( camX < -(MAP_WIDTH*0.05f) + zoom_factor) 
                camX = -(MAP_WIDTH*0.05f) + zoom_factor;     
                    
          	 if( camY > map_startY - ( zoom_factor*sc_ratio ) ) // /1.2
                camY = map_startY - ( zoom_factor*sc_ratio );  // /1.2

          	 if( camY < -(MAP_HEIGHT*0.05f) + ( zoom_factor*sc_ratio ) ) 
                camY = -(MAP_HEIGHT*0.05f) + ( zoom_factor*sc_ratio );   

			 if(next_cam >= 0)
             if( (cam_x < points[next_cam].x+0.05f)
             &&( cam_x > points[next_cam].x-0.05f)                        
             &&( cam_y < points[next_cam].y+0.05f)
             &&( cam_y > points[next_cam].y-0.05f) )
             {   
                 cam_moving=false;  
             } 
                  */      
			  
         }    

         if(lock_player == false)  
		 if(game_paused == false)
         if(ply_id != -1) 
         if(!mode && game_mode == WALK)  
         { 
	     
			 if(ply_dead == false) 
             if(sprite[ply_id].status == MOVE_OUT || sprite[ply_id].status == OPEN_FIRE 
			 || sprite[ply_id].status == OPEN_CUT || sprite[ply_id].status == AIMING
			 || sprite[ply_id].status == OPEN_THROW)
             {
                 Do_Player_Accel(((int)TimerGetTime()-Key_Start)); 
             }

		} 

	}
    
    if(DEMO_MODE == 0)
    if( keys[VK_CONTROL] && keys['C'] )
    {
        
        keys['C']=false;
        
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		if(selection >= 0)
        {
                
        sprite_copy.x = sprite[selection].x;
        sprite_copy.y = sprite[selection].y;
        sprite_copy.width = sprite[selection].width;
        sprite_copy.height = sprite[selection].height;
                
        sprite_copy.w = sprite[selection].w;
        sprite_copy.z = sprite[selection].z;
        sprite_copy.box_width = sprite[selection].box_width;
        sprite_copy.box_height = sprite[selection].box_height;
                
        for(int j=0;j<4;j++)
        {
            sprite_copy.u[j] = sprite[selection].u[j];
            sprite_copy.v[j] = sprite[selection].v[j];
        }    
        sprite_copy.id = sprite[selection].id;
        sprite_copy.score = sprite[selection].score;
        sprite_copy.cur = sprite[selection].cur;
        sprite_copy.alpha = sprite[selection].alpha;
        sprite_copy.type = sprite[selection].type;
        sprite_copy.priority = sprite[selection].priority;
        sprite_copy.linked_sprite = sprite[selection].linked_sprite;
                
        sprite_copy.anim = sprite[selection].anim;
        sprite_copy.anim_state = sprite[selection].anim_state;
        sprite_copy.grab_switch = sprite[selection].grab_switch;
        sprite_copy.mouseover = sprite[selection].mouseover;
        sprite_copy.sector = sprite[selection].sector;
        sprite_copy.sector_action = sprite[selection].sector_action;
        sprite_copy.onCreate = sprite[selection].onCreate;
        sprite_copy.onCreate_action = sprite[selection].onCreate_action;
        sprite_copy.rank = sprite[selection].rank;
        sprite_copy.onDeath_action = sprite[selection].onDeath_action;                
        sprite_copy.light = sprite[selection].light; 
        
        tink_sfx=true;
        
        }
        
    }
    
    if(DEMO_MODE == 0) 
    if( keys[VK_CONTROL] && keys['V'] )
    {
        
        keys['V']=false;
        keys[VK_CONTROL]=false;
        
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
        { 
            no_sprites++;
            original_no_sprites++; 
            
            sprite[no_sprites - 1].x = -(camX + sprite_copy.width/2);
            sprite[no_sprites - 1].y = -(camY + sprite_copy.height/2);
            sprite[no_sprites - 1].width = sprite_copy.width;
            sprite[no_sprites - 1].height = sprite_copy.height;
                
            sprite[no_sprites - 1].w = sprite_copy.w - (sprite_copy.x - sprite[no_sprites - 1].x);
            sprite[no_sprites - 1].z = sprite_copy.z - (sprite_copy.y - sprite[no_sprites - 1].y);
            sprite[no_sprites - 1].box_width = sprite_copy.box_width;
            sprite[no_sprites - 1].box_height = sprite_copy.box_height;
                
            for(int j=0;j<4;j++)
            {
                sprite[no_sprites - 1].u[j] = sprite_copy.u[j];
                sprite[no_sprites - 1].v[j] = sprite_copy.v[j];
            }    
            
            sprite[no_sprites - 1].id = sprite_copy.id;
            sprite[no_sprites - 1].score = sprite_copy.score;
            sprite[no_sprites - 1].cur = sprite_copy.cur; 
            sprite[no_sprites - 1].alpha = sprite_copy.alpha;
            sprite[no_sprites - 1].type = sprite_copy.type;
            sprite[no_sprites - 1].priority = sprite_copy.priority;
            sprite[no_sprites - 1].linked_sprite = sprite_copy.linked_sprite;
                
            sprite[no_sprites - 1].anim = sprite_copy.anim;
            sprite[no_sprites - 1].anim_state = sprite_copy.anim_state;
            sprite[no_sprites - 1].grab_switch = sprite_copy.grab_switch;
            sprite[no_sprites - 1].mouseover = sprite_copy.mouseover;
            sprite[no_sprites - 1].sector = sprite_copy.sector;
            sprite[no_sprites - 1].sector_action = sprite_copy.sector_action;
            sprite[no_sprites - 1].onCreate = sprite_copy.onCreate;
            sprite[no_sprites - 1].onCreate_action = sprite_copy.onCreate_action;
            sprite[no_sprites - 1].rank = sprite_copy.rank;
            sprite[no_sprites - 1].onDeath_action = sprite_copy.onDeath_action;                
            sprite[no_sprites - 1].light = sprite_copy.light; 
            
            sprite[no_sprites - 1].turn_off = sprite_copy.turn_off;
                   
            if( texture_fx[sprite[no_sprites - 1].id] == 2 || texture_fx[sprite[no_sprites - 1].id] == 3 || texture_fx[sprite[no_sprites - 1].id] == 4)
               sprite[no_sprites - 1].fx_id = animation_fx[sprite[no_sprites - 1].id];
                                                   	         
            selection = (no_sprites-1);
            
            switch_n_sfx=true;
            
        }         
        
    }
    
    if(DEMO_MODE == 0)
	if(game_paused == false)
    if( keys[VK_CONTROL] && keys['N'] )
    {
        keys['N']=false;
               
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		if(selection >= 0)          
        {
	       display[selection].global_flag--;
        }  
            
    } 
    
    if(DEMO_MODE == 0)    
    if(game_paused == false)
    if( keys[VK_CONTROL] && keys['L'] )
    {
        keys['L']=false;  
  
        scene= 0;      
        episode++;
        if(episode>4)
            episode = 0;  
                  
        LoadScene( episode, scene, TRUE );

    }    
    if(DEMO_MODE == 0)    
    if(game_paused == false)
    if( keys[VK_CONTROL] && keys['J'] )
    {
         keys['J']=false; 
                        
         if(!(scene)==0)
            scene --;
            
         current_spawn = 0; 
                                     
         LoadScene( episode, scene, TRUE );
        
         if(game_mode != WALK && mode && game_mode != WORLD)
         {
            camX = 0.0f;
            camY = 0.0f;
            zoom_factor = 1.2f;
         }
        
         selection = 0;   

    }
    
    if(DEMO_MODE == 0)    
    if(game_paused == false)
    if( keys[VK_CONTROL] && keys['K'] )
    { 
         keys['K']=false;

         scene++;
            
         current_spawn = 0;
                
         if(ply_carry != -1)
            last_carried = sprite[ply_carry].linked_sprite;
         else
            last_carried = RESET;

         LoadScene( episode, scene, TRUE );
                 
         if(game_mode != WALK && mode && game_mode != WORLD)
         {
            camX = 0.0f;
            camY = 0.0f;
            zoom_factor = 1.2f;
         }
        
         selection = 0;  
        
    }  
    
    if(DEMO_MODE == 0)   
    if(game_paused == false)
    if( keys[VK_CONTROL] && keys['M'] )
    {
        keys['M']=false;
                
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		if(selection >= 0)          
        {
	       display[selection].global_flag++;
        }  
         
        if(DEMO_MODE == 0)       
        if(!mode && game_mode == WALK)
        { 
             Calculate_Item(100000, INV_GOLD, -1, 0, -1, -1);  
                                                               
            cash_sfx = true;
            
        }
            
    }  
        
    if(DEMO_MODE == 0)    
    if( keys[VK_CONTROL] && keys['S'] )
    {
        keys['S']=false;
        
        if(music_loop)
            music_loop--;
            
    }    
    
    if(DEMO_MODE == 0)    
    if( keys[VK_CONTROL] && keys['D'] )
    {
        keys['D']=false;
        
        music_loop++;
            
    }    
    
    if(DEMO_MODE == 0)    
    if( keys[VK_CONTROL] && keys['Z'] )
    {
        keys['Z']=false;
        
        if(g_type)
            g_type--;
            
    }    
    
    if(DEMO_MODE == 0)    
	if(game_paused == false)
    if( keys[VK_CONTROL] && keys['X'] )
    {
        keys['X']=false;

        g_type++;
            
    } 
    
    if(DEMO_MODE == 0)    
	if(game_paused == false)           
    if( keys[VK_DELETE])
    {
        
        keys[VK_DELETE]=FALSE;
        
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		if(selection >= 0)
        {   
                              
            for(int loop=selection;loop<no_sprites;loop++)
            {
                sprite[loop].x = sprite[loop+1].x;
                sprite[loop].y = sprite[loop+1].y;
                sprite[loop].width = sprite[loop+1].width;
                sprite[loop].height = sprite[loop+1].height;
                
                sprite[loop].w = sprite[loop+1].w;
                sprite[loop].z = sprite[loop+1].z;
                sprite[loop].box_width = sprite[loop+1].box_width;
                sprite[loop].box_height = sprite[loop+1].box_height;
                
                for(int j=0;j<4;j++)
                {
                    sprite[loop].u[j] = sprite[loop+1].u[j];
                    sprite[loop].v[j] = sprite[loop+1].v[j];
                }    
                sprite[loop].id = sprite[loop+1].id;
                sprite[loop].score = sprite[loop+1].score;
                sprite[loop].cur = sprite[loop+1].cur;
                sprite[loop].alpha = sprite[loop+1].alpha;
                sprite[loop].type = sprite[loop+1].type;
                sprite[loop].priority = sprite[loop+1].priority;
                sprite[loop].linked_sprite = sprite[loop+1].linked_sprite;
                
                sprite[loop].anim = sprite[loop+1].anim;
                sprite[loop].anim_state = sprite[loop+1].anim_state;
                sprite[loop].grab_switch = sprite[loop+1].grab_switch;
                sprite[loop].mouseover = sprite[loop+1].mouseover;
                sprite[loop].sector = sprite[loop+1].sector;
                sprite[loop].sector_action = sprite[loop+1].sector_action;
                sprite[loop].onCreate = sprite[loop+1].onCreate;
                sprite[loop].onCreate_action = sprite[loop+1].onCreate_action;
                sprite[loop].rank = sprite[loop+1].rank;
                sprite[loop].onDeath_action = sprite[loop+1].onDeath_action;                
                sprite[loop].light = sprite[loop+1].light;                
                sprite[loop].global_flag = sprite[loop+1].global_flag;
                   
                if( texture_fx[sprite[loop].id] == 2 || texture_fx[sprite[loop].id] == 3 || texture_fx[sprite[loop].id] == 4)
                   sprite[loop].fx_id = animation_fx[sprite[loop].id];
                     
                                
            }  

                           
            if(no_sprites>0)
                no_sprites--;
                
            if(!(selection == 0)) 
            selection--; 
            
       }     
        
       if(mode && mode == POINT_MODE)
       {
		   if(pt_selection >= 0) 
           for(int loop=pt_selection;loop<no_points;loop++)
           { 
              points[loop].x = points[loop+1].x;
              points[loop].y = points[loop+1].y; 
              
              points[loop].score = points[loop+1].score;  
              points[loop].active = points[loop+1].active;
              points[loop].speed  = points[loop+1].speed;  
              points[loop].c1 = points[loop+1].c1;
              points[loop].c2 = points[loop+1].c2; 
              points[loop].c3 = points[loop+1].c3;
              points[loop].c4 = points[loop+1].c4; 
                                                  
           }
           if(no_points>0)
               no_points--;
                
           if(!(pt_selection == 0)) 
               pt_selection--; 
       } 
       
       if(mode && mode == NODES)
       {
		      
       }        
    } 
     
    shift_key = false;

 
	if(game_paused == false)      
    if( keys[VK_SHIFT]) 
    {  
        shift_key = true;    
    }
     
    if( keys[VK_SHIFT])
        precision = 0.045f;

	if( keys[VK_CONTROL])
        precision = 0.015f;

	if( keys[VK_SHIFT] && keys[VK_CONTROL])
        precision = 0.0005f;

	
	capital_key = 0;

    capital_key = GetKeyState(VK_CAPITAL);
    
    if(episode == 0 && scene == 13)
    {
        shift_key = false;
        capital_key = 1;
    }
    
    if(DEMO_MODE == 0) 
	if(game_paused == false)  
    if (keys[VK_PAUSE])
    {
        keys[VK_PAUSE]=FALSE;
                                
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		if(selection >= 0)
        {
            display[selection].light -= 0.1f;        
        }
    }   
    
//    if(DEMO_MODE == 0)    
	if(game_paused == false)  
    if (keys[VK_BACK])
    {
        keys[VK_BACK]=FALSE;
        
/*        if(!mode && game_mode == WALK )
        {
             sprintf( string, "scene/episode%i/scene%i.tmp", episode, scene);                  
             LoadTemp( string );  

        } */
                                
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		if(selection >= 0)
        {
            display[selection].light += 0.1f;                  
        }
         
        if(text_selected==true && !mode)
		if(cur_letter >= 0)
        {
                               
           lvl_text[cur_letter]='\0';  
                                        
           if(cur_letter!=0) 
               cur_letter--;
               
           lvl_text[cur_letter]='\0';  
                    
           backspace_sfx = true;
           
        }  
        
        if( mode == TILE_MODE )
        {
		/*	if(paint_mode == false) 
            for(int i=0;i<MAP_TILES;i++)
                tiles[i] = 0;   */
 
			if(paint_mode == true)
                no_col_changes = 0;
       
            cash_sfx = true; 
			
        }
                
    } 

	if(game_paused == false)     
    if(DEMO_MODE == 0)      
	if (keys[VK_NEXT])
	{
             
       if(mode==PLACEMENT)
	   if(selection >= 0)	
       {
           display[selection].width -= precision;
           display[selection].box_width -= precision;
       }
       if(mode==TEXTURE)
	   if(selection >= 0)
       {
           display[selection].u[0] -= precision;
           display[selection].u[3] -= precision;
           display[selection].u[1] += precision;
           display[selection].u[2] += precision;  
       }  
       if(mode==COLLISION)
	   if(selection >= 0)
           display[selection].box_width -= precision;
    }  

	if(game_paused == false)     
    if(DEMO_MODE == 0)  
	if (keys[VK_END])
	{
           
       if(mode==PLACEMENT)
	   if(selection >= 0)
       {
           display[selection].width += precision;
           display[selection].box_width +=precision;
       } 
       if(mode==TEXTURE)
	   if(selection >= 0)
       {
           display[selection].u[0] += precision;
           display[selection].u[3] += precision;
           display[selection].u[1] -= precision;
           display[selection].u[2] -= precision;           
       }                 
       if(mode==COLLISION)
	   if(selection >= 0)
           display[selection].box_width +=precision;
    }

	if(game_paused == false)     
    if(DEMO_MODE == 0)
	if (keys[VK_PRIOR])
	{
            
       if(mode==PLACEMENT)
	   if(selection >= 0)
       {
           display[selection].height -= precision;
           display[selection].box_height -= precision;
       }
       if(mode==TEXTURE)
	   if(selection >= 0)
       {
           display[selection].v[0] += precision;
           display[selection].v[1] += precision;
           display[selection].v[3] -= precision;
           display[selection].v[2] -= precision;           
       }   
       if(mode==COLLISION)
	   if(selection >= 0)
           display[selection].box_height -= precision;
    }  

	if(game_paused == false)     
    if(DEMO_MODE == 0)
	if (keys[VK_HOME])
	{
           
       if(mode==PLACEMENT)               
	   if(selection >= 0)
       {
           display[selection].height += precision; 
           display[selection].box_height += precision;
       } 
       if(mode==TEXTURE)
	   if(selection >= 0)
       {
           display[selection].v[0] -= precision;
           display[selection].v[1] -= precision;
           display[selection].v[3] += precision;
           display[selection].v[2] += precision;           
       }               
       if(mode==COLLISION)
	   if(selection >= 0)
           display[selection].box_height += precision;  

                          
    }  
    
    // VK_UP  
	if(game_paused == false) 
    if(DEMO_MODE == 0 && mode)   
	if (keys[VK_UP] && !keys[VK_DOWN] )
	{ 
       
       if(keys[VK_CONTROL] || keys[VK_SHIFT])    
       {
           if(mode==PLACEMENT)          
		   if(selection >= 0)
           {
    	       display[selection].y += precision;
    	       display[selection].z += precision;
           }    
           if(mode==TEXTURE)
		   if(selection >= 0)
           {
               display[selection].v[0] -= precision;
               display[selection].v[1] -= precision;
               display[selection].v[3] -= precision;
               display[selection].v[2] -= precision;
           }
           if(mode==COLLISION)
		   if(selection >= 0)
               display[selection].z += precision;
                      
           if(mode==POINT_MODE)          
		   if(pt_selection >= 0)
    	       points[pt_selection].y += precision;

       }
	   else   
       {  
          camY -= (float)SCROLL_SPEED*(float)f_rate;                     
          mouseY += (float)SCROLL_SPEED*(float)f_rate;           
       }   
	}
    
    // VK_DOWN
	if(game_paused == false)  
    if(DEMO_MODE == 0 && mode)
	if (keys[VK_DOWN] && !keys[VK_UP])
	{
       if(keys[VK_CONTROL] || keys[VK_SHIFT]) 
       {              
           if(mode==PLACEMENT)
		   if(selection >= 0)
           {               
    	       display[selection].y -= precision;
    	       display[selection].z -= precision;
           }
           if(mode==TEXTURE)
		   if(selection >= 0)
           {
               display[selection].v[0] += precision;
               display[selection].v[1] += precision;
               display[selection].v[3] += precision;
               display[selection].v[2] += precision;
           }
           if(mode==COLLISION)
		   if(selection >= 0)
               display[selection].z -= precision;
               
           if(mode==POINT_MODE)
		   if(pt_selection >= 0)
    	       points[pt_selection].y -= precision;

       }
       else
       {
            camY += (float)SCROLL_SPEED*(float)f_rate;        
            mouseY -= (float)SCROLL_SPEED*(float)f_rate; 
       }    
	}
	
	// VK_RIGHT
	if(game_paused == false) 
    if(DEMO_MODE == 0 && mode)	
	if (keys[VK_RIGHT] && !keys[VK_LEFT])
	{
       if(keys[VK_CONTROL] || keys[VK_SHIFT])  
       {               
           if(mode==PLACEMENT)                
		   if(selection >= 0)
           {
    	       display[selection].x += precision;
    	       display[selection].w += precision;
           }
           if(mode==TEXTURE)
		   if(selection >= 0)
           {
               display[selection].u[0] -= precision;
               display[selection].u[1] -= precision;
               display[selection].u[3] -= precision;
               display[selection].u[2] -= precision;
                
           }
           if(mode==COLLISION)
		   if(selection >= 0)
               display[selection].w += precision;
     
           if(mode==POINT_MODE)                
		   if(pt_selection >= 0)
    	       points[pt_selection].x += precision;

       }
       else
       {
            camX -= (float)SCROLL_SPEED*(float)f_rate;                   
            mouseX += (float)SCROLL_SPEED*(float)f_rate;      
       }  	       
	}
	
	// VK_LEFT
	if(game_paused == false) 
    if(DEMO_MODE == 0 && mode)	
	if (keys[VK_LEFT] && !keys[VK_RIGHT])
	{
       if(keys[VK_CONTROL] || keys[VK_SHIFT])  
       {               
           if(mode==PLACEMENT)                
		   if(selection >= 0)
           {
    	       display[selection].x -= precision;
    	       display[selection].w -= precision;
           }
           if(mode==TEXTURE)
		   if(selection >= 0)
           {
               display[selection].u[0] += precision;
               display[selection].u[1] += precision;
               display[selection].u[3] += precision;
               display[selection].u[2] += precision;
           }
           if(mode==COLLISION)
		   if(selection >= 0)
               display[selection].w -= precision;
               
           if(mode==POINT_MODE)                 
		   if(pt_selection >= 0)
    	       points[pt_selection].x -= precision;

       }
       else
       {
            camX += (float)SCROLL_SPEED*(float)f_rate;                                                            
            mouseX -= (float)SCROLL_SPEED*(float)f_rate;                 
       }              
	} 

	if(game_paused == false)             
    if(keys['S']) 
    {   
		
		if( mode || text_selected == true)
            keys['S']=false;
        
		if(game_mode == FRONT)        
        if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
        {
                                          
           if(shift_key == true)  
               lvl_text[cur_letter]='S';
           else
               lvl_text[cur_letter]='s';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='S';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='s';
                          
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
        } 
                                               
    }   

	if(game_paused == false)      
    if(!mode) // game_mode == WALK && 
    {
		if( keys['S'] || keys[VK_DOWN] ) // Zoom function
	    {
	        KEY_BACKWARD = true;
	    } 
	    if( !keys['S'] && !keys[VK_DOWN] )
	    {
	        KEY_BACKWARD = false;

	        keys['S']=false; 

			keys[VK_DOWN]=false;

	    }
    }    
    
    if(game_paused == false) 
	if (keys[VK_SPACE]) 
	{

		sta2_space_pressed = true;

        KEY_SPACE = false;    
        
        if(space_is_held == false)
            KEY_SPACE = true; 
	    
		sta2_1_pressed = false;
		sta2_2_pressed = false;
		sta2_3_pressed = false;
		sta2_4_pressed = false;
		sta2_5_pressed = false;
		sta2_6_pressed = false;
		sta2_7_pressed = false;
		sta2_8_pressed = false;
		sta2_9_pressed = false;
		sta2_0_pressed = false;
	   
	    if(sta2_turn == TURN_PLAYER) 
		if(!mode && game_mode == WALK) 
		if(ply_id != -1)
		if(STA2_MODE == MODE_AIMING || STA2_MODE == MODE_TARGET || sprite[ply_id].return_fire == true)
		{

			keys[VK_SPACE] = false;

			sta2_space_pressed = true;

		}


	if(game_paused == false)        
 //   if(keys[VK_CONTROL])    
    if(DEMO_MODE == 0) 
    {  

		arcade_kill_count=0;

		arcade_score=0; 

		arcade_time=0;

		arcade_bonus_timer=0;

		arcade_bonus = 0;

       game_paused = false;          

       keys[VK_SPACE]=FALSE; 
                     
       mouseX = -camX;
       mouseY = -camY; 
	    
       mouse_stop = true;  
          
       if ( mode == STANDARD )
       {
           mode = PLACEMENT;
           zoom_factor = ZOOM_AMOUNT;
           
           if( ( game_mode == WALK || game_mode == WORLD) )
           {
               mode = CAMERA; 
               text[3].x = -0.35f;     
               sprintf( text[3].word, "Camera mode");       
           }
            
       }    
       else
       {
           mode = STANDARD;
           zoom_factor = ZOOM_AMOUNT;
       }
      
       if( mode == PLACEMENT )
       {
           text[3].x = -0.35f;     
           sprintf( text[3].word, "Placement mode");
       }
       
       current_spawn = 0;
             
       LoadScene( episode, scene, TRUE );
                  
       cur_keyframe = 0;
          
       Zoom(zoom_factor);     
       
       animating = FALSE;           
         
       if(!mode)
       { 
		   sprintf( temp_string.string, "Data/verdict/font");                

           Change_Texture(temp_string, 0);  
       }
       else
       {
		   sprintf( temp_string.string, "Data/hud/font");                
           Change_Texture(temp_string, 0);  
       }
       
       } // demo_mode == 0
       
       if(!keys[VK_CONTROL])
       if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
       {
                        
           keys[VK_SPACE]=FALSE;
                                         
           lvl_text[cur_letter]='_';
           
           if(cur_letter < input_cap)
               cur_letter++;
               
           tink_sfx = true;
               
        }        
    } 
    else
    {
       KEY_SPACE = false;
       keys[VK_SPACE]=FALSE;
       space_is_held=false; 
    }
    
	if(game_paused == false)
    if (keys[VK_TAB])
	{
                     
       keys[VK_TAB]=FALSE;					// If So Make Key FALSE

	   if((int)TimerGetTime() > sta2_key_delay_timer) 
	       sta2_tab_pressed = true;
        
       if(!mode && game_mode == WALK)
       {

       /*    if(map_stat == true)
           {     
               map_stat = false;      
           }
           else
           { 
               map_stat = true;
           }
	 
		if(map_stat == true)
		    Set_Sprite(3, 2, LOOP, ANIM_HUD, ANIM_NOT_WALKING);
		else
			Set_Sprite(3, 0, LOOP, ANIM_HUD, ANIM_NOT_WALKING);*/
                
       }

       if(DEMO_MODE == 0)
       if(mode)
       {    
           switch (mode)
           {  
               hud[47].alpha = 0.0;  
               case PLACEMENT:
           
                   mode = TEXTURE;       
                   text[3].x = -0.28f;
                   sprintf( text[3].word, "Texture mode");
                   hud[1].alpha = 1.0;
               break;          
               case TEXTURE:
                                
                   mode = COLLISION;  
                   text[3].x = -0.35f;     
                   sprintf( text[3].word, "Collision mode");
                   hud[1].alpha = 1.0;
               break;  
               case COLLISION:
               
                   mode = POINT_MODE;
                   text[3].x = -0.25f;    
                   sprintf( text[3].word, "Points mode");
                   hud[1].alpha = 1.0;     
               break;                 
               case POINT_MODE:  
                
                   mode = TILE_MODE;
                   text[3].x = -0.25f;    
				   if(paint_mode == true) 
	                   sprintf( text[3].word, "Tiling mode-(COL)");
				   else
	                   sprintf( text[3].word, "Tiling mode"); 
                   hud[1].alpha = 0.0;  
                   hud[47].alpha = 1.0;   
               break;  
               case TILE_MODE: 
                 
                   mode = PLACEMENT;
                   text[3].x = -0.25f;     
                   sprintf( text[3].word, "Placement mode");
                   hud[1].alpha = 1.0;     
               break;                  
                          
           }
       }          
    }   
     
	if (keys[VK_RETURN]) 
	{
                      
         keys[VK_RETURN]=FALSE;					// If So Make Key FALSE      
		 
          
         if(!mode) 
         { 

			 if(next_scene == false && fade == 1.0) 
			 if(game_mode == WALK || Level_Scene == LVL_GALLERY) 
			 {
				game_paused ^= 1;

				if(CONTROLLER)
				{ 
					DX_GRENADE_KEY = false;
					DX_TRAP_KEY    = false;

					DX_WEAPON1 = false;
					DX_WEAPON2 = false;
					DX_WEAPON3 = false;
					DX_WEAPON4 = false;

					DX_KNIFE = false;

					DX_BACK = false;

					DX_UP   = false;
					DX_DOWN = false;

					DX_SHOOT = false;
					DX_RELOAD = false;

					DX_PAUSED=false;
				}

				if(game_paused == false)   
				{

					pause_music=true;

					timer_addition += TimerGetTime() - pause_timer_start; 

					AI_Time = (int)TimerGetTime();
					Animate_Time = (int)TimerGetTime();  //8
					Swap_Time = (int)TimerGetTime() + SWAP_RATE;
					Steam_Time = (int)TimerGetTime() + STEAM_RATE;

					Key_Start = (int)TimerGetTime();
					Main_Start = (int)TimerGetTime();
					Code_Start = (int)TimerGetTime();
					Code_Time = (int)TimerGetTime();
					Main_Time = (int)TimerGetTime();

					Main_cycle = (int)TimerGetTime();
					Draw_cycle = (int)TimerGetTime(); 
					Ai_cycle = (int)TimerGetTime();
					Swap_cycle = (int)TimerGetTime();
					Key_Time = (int)TimerGetTime(); 
					Real_Time = (int)TimerGetTime();
					time_diff = (int)TimerGetTime(); 

					view_cone_timer = (int)TimerGetTime(); 
					render_bg = TimerGetTime();

					double_main_code = 0;
					render_sequence=0;

				} 
				else 
				{ 

				   pause_music=true;

	               pause_timer_start = TimerGetTime();


					AI_Time = (int)TimerGetTime();
					Animate_Time = (int)TimerGetTime();  //8
					Swap_Time = (int)TimerGetTime() + SWAP_RATE;
					Steam_Time = (int)TimerGetTime() + STEAM_RATE;

					Key_Start = (int)TimerGetTime();
					Main_Start = (int)TimerGetTime();
					Code_Start = (int)TimerGetTime();
					Code_Time = (int)TimerGetTime();
					Main_Time = (int)TimerGetTime();

					Main_cycle = (int)TimerGetTime();
					Draw_cycle = (int)TimerGetTime();
					Ai_cycle = (int)TimerGetTime();
					Swap_cycle = (int)TimerGetTime();
					Key_Time = (int)TimerGetTime(); 
					Real_Time = (int)TimerGetTime();
					time_diff = (int)TimerGetTime(); 

					view_cone_timer = (int)TimerGetTime(); 
					render_bg = TimerGetTime();

					double_main_code = 0;
					render_sequence=0;

				   if(Level_Scene != LVL_GALLERY) 
				   {
					  hud[55].id = 6;
					  hud[55].fx_id = animation_fx[hud[55].id];
					  hud[55].cur=0;
					  hud[55].cur_time=0;
					  Set_Sprite(55, 24, LOOP, ANIM_SPRITE, ANIM_WALKING); // Stunned
				   }
				   if(Level_Scene == LVL_GALLERY) 
				   {
					  hud[55].id = 8;
					  hud[55].fx_id = animation_fx[hud[55].id];
					  hud[55].cur=0;
					  hud[55].cur_time=0;
					  Set_Sprite(55, 24, LOOP, ANIM_SPRITE, ANIM_WALKING); // Stunned
				   }
				}
			//	 cash_sfx = true;  
             } 

         } 

         if(DEMO_MODE == 0)                
         if( mode )      
         if (dump_debug==FALSE) 
         { 

           memset(temp_global_objects, GLOBAL_UNBEATEN, sizeof(temp_global_objects) );
                     
           sprintf( string, "scene/episode%i/scene%i.tmp", episode, scene);
                                    
           remove(string); 
                                       
           sprintf( string, "scene/episode%i/scene%i.dat", episode, scene);
          
           DumpScene( string );
                                       
           sprintf( string, "scene/episode%i/scene%i.pt", episode, scene);
          
           DumpPoints( string );
           
           sprintf( string, "scene/episode%i/scene%i.nde", episode, scene);
           
           DumpNodes( string );   
           
           sprintf( string, "scene/episode%i/scene%i.bg", episode, scene);
           
           Dump_BG( string );    
           
           sprintf( string, "scene/episode%i/scene%i.col", episode, scene);
           
		//   if(game_mode == WALK) 
	    //       Dump_COL( string );     
                                                       
           dump_debug=TRUE; 
           
           cash_sfx = true; 
                                   
        }  

     }        
     else
	 { 
		if(DEMO_MODE == 0)
		if (dump_debug) 
			dump_debug=FALSE;
	 }

	 if(game_paused == false)				
	 if(DEMO_MODE == 0)
     if (keys[VK_F1])						// Is F1 Being Pressed?
     {
        if(!mode)
        {
                           
        keys[VK_F1]=FALSE;					// If So Make Key FALSE
		
		KillGLWindow();						// Kill Our Current Window

		fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode

		#if IS_USING_DIRECTX == 1 
		if(RENDERER == RENDER_DIRECTX)
		{

			if (!CreateDXWindow("Verdict Guilty™", sc_width, sc_height, sc_bits, fullscreen))
			{		 
				created_a_window = 0; 
			}  
			else  
				created_a_window = 1;

		}
		#endif 

		if(RENDERER == RENDER_OPENGL)
		{
			// Recreate Our OpenGL Window 
			created_a_window = CreateGLWindow("Verdict Guilty™", sc_width, sc_height, sc_bits, fullscreen);
		}
						
		if( created_a_window == 0) // Couldn't create...                       
		{	   
			if(RENDERER == RENDER_OPENGL) 
				MessageBox (HWND_DESKTOP, "Couldn't create openGL_window", "Error", MB_OK | MB_ICONEXCLAMATION);
			else
				MessageBox (HWND_DESKTOP, "Couldn't create directX_window", "Error", MB_OK | MB_ICONEXCLAMATION);

			return(0);				  		// Quit If Window Was Not Created           
		}        
		if( created_a_window == 1) // Created window...                         
		{	        
			SaveCFG();            
		}  

        }  
     }  

	 if(game_paused == false)				
	 //if(DEMO_MODE == 0) 
     if(keys[VK_F2] && !keys[VK_CONTROL])						// Is F2 Being Pressed?
     {
        if(!mode) 
        {
                           
            keys[VK_F2]=FALSE;					// If So Make Key FALSE

		/*	click_sfx=true;
			  
			CONTROLLER ^= 1; 
			 
			if(!CONTROLLER)
			if(DXsprite_overlay != -1) 
			{
				sprite[DXsprite_overlay].alpha = 0.0f;
				if(game_mode == WALK)
					sprite[DXsprite_overlay+1].alpha = 0.0f;
			}

			if(game_mode == FRONT) 
			{
				is_a_gallery=false;

				if(Level_Scene == LVL_GALLERY)
					is_a_gallery=true;

				if(CONTROLLER) 
				{ 
					if(is_a_gallery == false)
						hud[1].alpha = 0.0f; // Arrow
					else
						hud[1].alpha = 1.0f; // Arrow
				}
				else 
				{  
					if(next_scene == false)
					if(!(episode == 0 && scene == 0))
					if(!(episode == 10 && scene == 0))
						hud[1].alpha = 1.0f; // Arrow
				}

			} 

			if(!CONTROLLER) 
				DX_INV_ACTIVE=false;

			if(CONTROLLER_ENABLED == false)
				CONTROLLER = false;
		 */

        } 
     } 
     
	 if(game_paused == false)
     if (keys['J'])						// Is F1 Being Pressed?
     {
		if(mode || text_selected == true)
	        keys['J']=FALSE;					// If So Make Key FALSE
     
       if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
       {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='J';
           else
               lvl_text[cur_letter]='j';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='J';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='j';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
        } 
                
     } 

	 if(game_paused == false)
     if (keys[VK_OEM_PERIOD] || keys['.'])						// Is F1 Being Pressed?
     {
        keys[VK_OEM_PERIOD]=FALSE;					// If So Make Key FALSE
        keys['.']=FALSE;					// If So Make Key FALSE
                
       if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
       {
 
           lvl_text[cur_letter]='.';
                                 
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
        } 
                
     } 
     
          
	 if(game_paused == false)
     if (keys['K'])						// Is F1 Being Pressed?
     {
		if(mode || text_selected == true)
            keys['K']=FALSE;					// If So Make Key FALSE
              
       if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
       {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='K';
           else
               lvl_text[cur_letter]='k';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='K';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='k';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
                
        }  
         
     } 
     
	 if(game_paused == false) 
 //    if(game_mode != WALK || mode)   
     if( keys['Q']) // Zoom function
     {

        if(mode || game_mode != WALK) 
        	keys['Q']=FALSE;
        
	//	if(DEMO_MODE == 0 ) 
		if(keys[VK_CONTROL])
		{
			keys[VK_CONTROL] = false;

             end_sfx=NO_ANIM;          
             quitting = true;
             quit_timer = (int)TimerGetTime() + 100; 
    		 if(current_file != -1 && game_mode == WALK && episode != 0)
		     {   
		        sprintf( temp_string.string, "data/save/fragfile%i", current_file);
		        SaveLevel( temp_string);  
		     }  	

			switch_n_sfx = true;   

		} 

		if(game_mode != WALK || mode)
        if(text_selected== false)
		if(mode)
        if(DEMO_MODE == 0 )         
        if(password_mode==PASSWORD_RESET)
        {         
             zoom_factor +=0.1f;
             Zoom(zoom_factor);
        }  
                
       if(game_mode != WALK || mode)         
       if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
       {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='Q';
           else
               lvl_text[cur_letter]='q';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='Q';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='q';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
        } 

     }   

	 if(game_paused == false)
     if( keys['W']) // Zoom function
     {
        
		if(mode || text_selected == true) 
            keys['W']=FALSE;
        
		 
		 if(DEMO_MODE == 0)
		 if(keys[VK_CONTROL])
		 {
			keys[VK_CONTROL] = false;

            episode = 0;
			scene = 1;
			next_scene = true;
			switch_n_sfx = true;   

		 } 

		 if(mode)	
         if(text_selected== false)
         if(DEMO_MODE == 0 )         
         if(password_mode==PASSWORD_RESET)
         {         
             zoom_factor -=0.1f;
             Zoom(zoom_factor);
         }    

       if( game_mode == FRONT)        
       if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
       {
           if(shift_key == true)
               lvl_text[cur_letter]='W';
           else
               lvl_text[cur_letter]='w';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='W';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='w';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
        } 
                  
     } 

	 if(game_paused == false)      
     if(!mode)   // game_mode == WALK && 
     {
	     if( keys['W'] || keys[VK_UP]) // || keys[VK_UP] 
	     {
             KEY_FORWARD = true;
	     } 
	     if( !keys['W'] && !keys[VK_UP] ) // && !keys[VK_UP] 
	     {
	         KEY_FORWARD = false; 

	         keys['W'] = false; 
			 keys[VK_UP] = false;

	     }
	 }

	 if(game_paused == false)
     if( keys['1'] || DX_WEAPON1 == true)
     { 
         
         keys['1'] = FALSE;   
		 DX_WEAPON1 = false;

		 if((int)TimerGetTime() > sta2_key_delay_timer)
		 {
			sta2_space_pressed = false; 
			sta2_esc_pressed = false;
			sta2_tab_pressed = false;
			sta2_1_pressed = true;
			sta2_2_pressed = false;
			sta2_3_pressed = false;
			sta2_4_pressed = false;
			sta2_5_pressed = false;
			sta2_6_pressed = false;
			sta2_7_pressed = false;
			sta2_8_pressed = false;
			sta2_9_pressed = false; 
			sta2_0_pressed = false; 
		 }

         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         { 

           lvl_text[cur_letter]='1'; 

           if(cur_letter < input_cap) 
               cur_letter++; 
               
           type_sfx = true;
               
         }     
                  
         if(DEMO_MODE == 0) 
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {
			 // 16x16 
			 if(keys[VK_CONTROL] && keys[VK_SHIFT])   
			 { 
				 display[selection].width  = 0.05f; 
				 display[selection].w  = display[selection].x;
				 display[selection].box_width  = 0.05f;
			 }   
			 // 32x32 
			 if(keys[VK_CONTROL] && !keys[VK_SHIFT])  
			 {
				 display[selection].width  = 0.1f; 
				 display[selection].w  = display[selection].x;
				 display[selection].box_width  = 0.1f;
			 }      
			 // 512x 
			 if(keys[VK_SHIFT] && !keys[VK_CONTROL])  
			 {
				 display[selection].width  = 1.6f; 
				 display[selection].w  = display[selection].x;
				 display[selection].box_width  = 1.6f;
			 }      

			 if(!keys[VK_CONTROL] && !keys[VK_SHIFT])
                 fade_in -= 1;   
         }    
          
         if(DEMO_MODE == 0)
         if(!mode && game_mode == WALK)
         if(order_mode==ORDER_TYPING)
         {
             if(order_list[0] == -1)
                 pw_no_sfx=true;
             else
             {
                 order_mode=ORDER_CHECKING;
                 ordered = 0;
             }
         }
         
         if(mode && mode == TILE_MODE)
             mouse_brush = 100;

     }

	 if(game_paused == false)
     if( keys['2'] || DX_WEAPON2 == true)
     {
         DX_WEAPON2 = false;
         keys['2'] = FALSE;

		 if((int)TimerGetTime() > sta2_key_delay_timer)
		 {
			sta2_space_pressed = false; 
			sta2_esc_pressed = false;
			sta2_tab_pressed = false;
			sta2_1_pressed = false;
			sta2_2_pressed = true;
			sta2_3_pressed = false;
			sta2_4_pressed = false;
			sta2_5_pressed = false;
			sta2_6_pressed = false;
			sta2_7_pressed = false;
			sta2_8_pressed = false;
			sta2_9_pressed = false; 
			sta2_0_pressed = false; 
		 }

		 if(game_mode == FRONT)      
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         { 

           lvl_text[cur_letter]='2';

           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         } 
                  
         if(DEMO_MODE == 0)         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {
			 // 64x64
			 if(keys[VK_CONTROL]) 
			 {
				 display[selection].width  = 0.2f;
				 display[selection].w  = display[selection].x;
				 display[selection].box_width  = 0.2f;
			 }
			 // 1024 
			 if(keys[VK_SHIFT])  
			 {
				 display[selection].width  = 3.2f; 
				 display[selection].w  = display[selection].x;
				 display[selection].box_width  = 3.2f;
			 }      
			 if(!keys[VK_CONTROL] && !keys[VK_SHIFT]) 
                 fade_in += 1;  
         }     

     
         if(DEMO_MODE == 0)               
         if(mode && mode == TILE_MODE)
             mouse_brush = 200;
                      
     }

	 if(game_paused == false)
     if( keys['3'] || DX_WEAPON3 == true) 
     {
         DX_WEAPON3 = false;  
         keys['3'] = FALSE;

		 if((int)TimerGetTime() > sta2_key_delay_timer)
		 {
			sta2_space_pressed = false; 
			sta2_esc_pressed = false;
			sta2_tab_pressed = false;
			sta2_1_pressed = false;
			sta2_2_pressed = false;
			sta2_3_pressed = true;
			sta2_4_pressed = false;
			sta2_5_pressed = false;
			sta2_6_pressed = false;
			sta2_7_pressed = false;
			sta2_8_pressed = false;
			sta2_9_pressed = false; 
			sta2_0_pressed = false; 
		 }

         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         { 

           lvl_text[cur_letter]='3';

           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         } 

         if(DEMO_MODE == 0)         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {
			  
			 // 128       
			 if(keys[VK_CONTROL]) 
			 {
				 display[selection].width  = 0.4f;
			//	 display[selection].height = 0.4f;
				 display[selection].w  = display[selection].x;
			//	 display[selection].z  = display[selection].y;
				 display[selection].box_width  = 0.4f;
			//	 display[selection].box_height = 0.4f;
			 }
			 // 2056 
			 if(keys[VK_SHIFT])  
			 {
				 display[selection].width  = 6.4f; 
				 display[selection].w  = display[selection].x;
				 display[selection].box_width  = 6.4f;
			 }   
			 if(!keys[VK_CONTROL] && !keys[VK_SHIFT]) 
                 fade_out -= 1; 
         }      
     
         if(DEMO_MODE == 0)       
         if(mode && mode == TILE_MODE)
             mouse_brush = 300;                  
     }

	 if(game_paused == false)
     if( keys['4'] || DX_WEAPON4 == true)
     { 
         DX_WEAPON4 = false;   
         keys['4'] = FALSE;

		 if((int)TimerGetTime() > sta2_key_delay_timer) 
		 {
			sta2_space_pressed = false; 
			sta2_esc_pressed = false;
			sta2_tab_pressed = false;
			sta2_1_pressed = false;
			sta2_2_pressed = false;
			sta2_3_pressed = false;
			sta2_4_pressed = true;
			sta2_5_pressed = false;
			sta2_6_pressed = false;
			sta2_7_pressed = false;
			sta2_8_pressed = false;
			sta2_9_pressed = false; 
			sta2_0_pressed = false; 
		 }

         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         { 

           lvl_text[cur_letter]='4';

           if(cur_letter < input_cap)      
               cur_letter++;
               
           type_sfx = true;
                
         }   

         if(DEMO_MODE == 0)         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {

			 // 256
			 if(keys[VK_CONTROL]) 
			 {
				 display[selection].width  = 0.8f;
			//	 display[selection].height = 0.8f;
				 display[selection].w  = display[selection].x;
			//	 display[selection].z  = display[selection].y;
				 display[selection].box_width  = 0.8f;
			//	 display[selection].box_height = 0.8f;
			 }
			 else
                 fade_out += 1; 
         }   
     
         if(DEMO_MODE == 0)           
         if(mode && mode == TILE_MODE)
             mouse_brush = 400;                            
     }   

	 if(game_paused == false)    
     if ( keys['.'])
     { 
         keys['.'] =FALSE;
         
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(keys[VK_SHIFT])
               lvl_text[cur_letter]='>';
           else
               lvl_text[cur_letter]='.';
           
           if(cur_letter < input_cap)
               cur_letter++;
               
           tink_sfx = true;
               
         } 
             
                              
     }  
          

	 if(game_paused == false)
     if ( keys['M'])
     {
         keys['M'] =FALSE;
         
        if(text_selected== false)
        if(DEMO_MODE == 0 )         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {
                 
         game_mode ++; 
         
         if(game_mode > 5)
             game_mode =0;
         
         }  
         
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='M';
           else
               lvl_text[cur_letter]='m';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='M';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='m';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         } 
         
         if(mode && mode == TILE_MODE)
             mouse_brush = 500;               
                              
     }  

	 if(game_paused == false)
     if (keys['5'])
     { 
                    
         keys['5'] = FALSE;
 
		 if((int)TimerGetTime() > sta2_key_delay_timer) 
		 {
			sta2_space_pressed = false; 
			sta2_esc_pressed = false;
			sta2_tab_pressed = false;
			sta2_1_pressed = false;
			sta2_2_pressed = false;
			sta2_3_pressed = false;
			sta2_4_pressed = false;
			sta2_5_pressed = true;
			sta2_6_pressed = false;
			sta2_7_pressed = false;
			sta2_8_pressed = false;
			sta2_9_pressed = false; 
			sta2_0_pressed = false; 
		 }

         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         { 

           lvl_text[cur_letter]='5';

           if(cur_letter < input_cap) 
               cur_letter++;
               
           type_sfx = true;
               
         }   

         if(DEMO_MODE == 0)         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {

			 // 16x16  
			 if(keys[VK_CONTROL] && keys[VK_SHIFT]) 
			 { 
				 display[selection].height = 0.05f;
				 display[selection].z  = display[selection].y;
				 display[selection].box_height = 0.05f;
			 }
			  
			 // 32x32 
			 if(keys[VK_CONTROL] && !keys[VK_SHIFT]) 
			 {
				 display[selection].height = 0.1f;
				 display[selection].z  = display[selection].y;
				 display[selection].box_height = 0.1f;
			 }
			 // 512x 
			 if(keys[VK_SHIFT] && !keys[VK_CONTROL])  
			 {
				 display[selection].height  = 1.6f; 
				 display[selection].z  = display[selection].y;
				 display[selection].box_height  = 1.6f; 
			 }      
			 if(!keys[VK_CONTROL] && !keys[VK_SHIFT])
			 {
				 if(game_time > 0)
					game_time--; 
			 }

         }    
            
         if(DEMO_MODE == 0)               
         if(mode && mode == TILE_MODE)
             mouse_brush = 500;  
                                                         
     }    

	 if(game_paused == false)              
     if (keys['6'])
     {
                   
         keys['6'] = FALSE;
 
		 if((int)TimerGetTime() > sta2_key_delay_timer) 
		 {
			sta2_space_pressed = false; 
			sta2_esc_pressed = false;
			sta2_tab_pressed = false;
			sta2_1_pressed = false;
			sta2_2_pressed = false;
			sta2_3_pressed = false;
			sta2_4_pressed = false;
			sta2_5_pressed = false;
			sta2_6_pressed = true;
			sta2_7_pressed = false;
			sta2_8_pressed = false;
			sta2_9_pressed = false; 
			sta2_0_pressed = false; 
		 }

         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         { 

           lvl_text[cur_letter]='6';

           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }  

         if(DEMO_MODE == 0)         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {

			 //64x64 
			 if(keys[VK_CONTROL]) 
			 {
			//	 display[selection].width  = 0.2f;
				 display[selection].height = 0.2f;;
			//	 display[selection].w  = display[selection].x;
				 display[selection].z  = display[selection].y;
			//	 display[selection].box_width  = 0.2f;
				 display[selection].box_height = 0.2f;
			 }
			 // 1024x 
			 if(keys[VK_SHIFT])  
			 {
				 display[selection].height  = 3.2f; 
				 display[selection].z  = display[selection].y;
				 display[selection].box_height  = 3.2f; 
			 }    
			 if(!keys[VK_CONTROL] && !keys[VK_SHIFT]) 
			 {
				 if(game_time > 0)
					game_time++; 
			 }

         }   

         if(DEMO_MODE == 0)    
         if(!mode && game_mode == WALK)
         if(order_mode==ORDER_TYPING)
         {
             if(order_list[5] == -1)
                 pw_no_sfx=true;
             else
             {
                 order_mode=ORDER_CHECKING;
                 ordered = 5;
             }
         }   
                             
     }     

	 if(game_paused == false)      
     if (keys['7'])
     {
                   
         keys['7'] = FALSE;
 
		 if((int)TimerGetTime() > sta2_key_delay_timer) 
		 {
			sta2_space_pressed = false; 
			sta2_esc_pressed = false;
			sta2_tab_pressed = false;
			sta2_1_pressed = false;
			sta2_2_pressed = false;
			sta2_3_pressed = false;
			sta2_4_pressed = false;
			sta2_5_pressed = false;
			sta2_6_pressed = false;
			sta2_7_pressed = true;
			sta2_8_pressed = false;
			sta2_9_pressed = false; 
			sta2_0_pressed = false; 
		 }

         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         { 

           lvl_text[cur_letter]='7';

           if(cur_letter < input_cap)
               cur_letter++;
                
           type_sfx = true;
                   
         } 
    
         if(DEMO_MODE == 0)         
         if(mode && mode != NODES && mode != TILE_MODE)
         {

			 // 128x128  
			 if(keys[VK_CONTROL]) 
			 {
			//	 display[selection].width  = 0.4f;
				 display[selection].height = 0.4f;
			//	 display[selection].w  = display[selection].x;
				 display[selection].z  = display[selection].y;
			//	 display[selection].box_width  = 0.4f;
				 display[selection].box_height = 0.4f;
			 }
			 else 
			 {
				 if(DEMO_MODE == 0)        
				 if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
				 if(selection >= 0)
					 display[selection].score--;
             
				 if(DEMO_MODE == 0)         
				 if(mode == POINT_MODE)
				 if(selection >= 0)
					 points[pt_selection].score--; 
			 }

         }   
               
         
     }    

	 if(game_paused == false)      
     if (keys['8'])
     {
                   
         keys['8'] = FALSE; 
 
		 if((int)TimerGetTime() > sta2_key_delay_timer) 
	 		 sta2_8_pressed = true;

         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         { 

           lvl_text[cur_letter]='8';

           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }  
		   
         if(DEMO_MODE == 0)         
         if(mode && mode != NODES && mode != TILE_MODE)
         {
			   
			 // 256x256
			 if(keys[VK_CONTROL])  
			 {
			//	 display[selection].width  = 0.8f;
				 display[selection].height = 0.8f;
			//	 display[selection].w  = display[selection].x;
				 display[selection].z  = display[selection].y;
			//	 display[selection].box_width  = 0.8f;
				 display[selection].box_height = 0.8f;
			 }
			 else 
			 {
				 if(DEMO_MODE == 0)        
				 if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
				 if(selection >= 0)
					 display[selection].score++;
             
				 if(DEMO_MODE == 0)         
				 if(mode == POINT_MODE)
				 if(selection >= 0)
					 points[pt_selection].score++; 
			 }

         }   
                               
     } 

	 if(game_paused == false)          
     if (keys['9'])
     {
                   
         keys['9'] = FALSE;
 
		 if((int)TimerGetTime() > sta2_key_delay_timer) 
	 		 sta2_9_pressed = true;

         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         { 

           lvl_text[cur_letter]='9';

           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true; 
               
         } 
         
         if(DEMO_MODE == 0)
		 if(!keys[VK_CONTROL]) 
         if(mode) 
         {
             if(mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
			 if(selection >= 0)
             if(display[selection].anim_state)
                 display[selection].anim_state--;
                 
             if( mode == POINT_MODE)
			 if(pt_selection >= 0)
             if(points[pt_selection].anim_state)
                 points[pt_selection].anim_state--;
             
                              
         }     
         if(DEMO_MODE == 0)       
         if(!mode && ( game_mode == FRONT))  
         { 

		 } 
         if(DEMO_MODE == 0)       
         if(!mode) //  && ( game_mode == WALK || game_mode == WORLD)
         {   
    
            if(keys[VK_CONTROL])        
		    {        
				    
			//	sta2_Proc_Level();

			//	sta2_route_create_pins = true;
			//	sta2_scroll_route_map = true;
						 
		/*		sta2_has_adele = 0;
				sta2_has_marie = 0;  
				sta2_has_bella = 0;  

				sta2_ada_exp = 0;  
				sta2_marie_exp = 0;          
				sta2_adele_exp = 0; 
				sta2_bella_exp = 0;

				sta2_has_beaten_normal_game = false;
				sta2_has_beaten_training_game = false;*/

			/*	for(int i =0;i<100;i++)            
					sta2_globals[i] = GLOBALS_RESET;     
					                              
				sta2_tokens = 3000; */  

			//	sta2_co_type = STA2_CO_BELLA; 
				   
			//	sta2_bella_exp = 20000;     
				  
				sta2_has_adele = 1;
				sta2_has_marie = 1;   
				sta2_has_bella = 1;       

				sta2_ada_exp = 16000;  
				sta2_marie_exp = 16000;          
				sta2_adele_exp = 16000; 
				sta2_bella_exp = 16000;     

			/*	scene = 27;                   
				episode = 1;        
				 
				next_scene = true;*/
			
			//	sta2_has_beaten_training_game = true;
				      
		        stolen_sfx = true;          
		    }  
			else          
			{         
				  
				for(int i =0;i<100;i++)            
					sta2_globals[i] = GLOBALS_RESET;
				    
				#if IS_FULL_STEAM == 1   
				 
        		if(STEAM_ACTIVE == true)    
				{
					SteamUserStats()->ResetAllStats(true);
				//	SteamFriends()->ActivateGameOverlayToStore( STA_ID, k_EOverlayToStoreFlag_None );
				}
				 
				#endif

				cash_sfx = true;    


			}

         }
             
     }    

	 if(game_paused == false)     
     if (keys['0'])
     { 
                        
         keys['0'] = FALSE;
 
		 if((int)TimerGetTime() > sta2_key_delay_timer) 
	 		 sta2_0_pressed = true;

         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         { 

           lvl_text[cur_letter]='0';

           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         } 
         
         if(DEMO_MODE == 0)         
         if(mode)
         {
                 
             if( mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
			 if(selection >= 0)
             {
                 
             if(display[selection].type != CUT && display[selection].type != BUT && display[selection].type != ALM)
             if(display[selection].anim_state < LOOP)
                 display[selection].anim_state++;
                 
             if(display[selection].type == CUT || display[selection].type == BUT || display[selection].type == ALM)
                 display[selection].anim_state++;
                 
             }
             if( mode == POINT_MODE)
			 if(pt_selection >= 0)
             if(points[pt_selection].anim_state < ONCE)
                 points[pt_selection].anim_state++; 
 
                      
             if(mode && mode == TILE_MODE) 
                 mouse_brush = 0;                 
         }  

     } 

	 if(game_paused == false)
     if (keys['D'])						// Is F1 Being Pressed?
     { 
	   	if(mode || text_selected == true)								
            keys['D']=FALSE;					// If So Make Key FALSE

        if(text_selected== false)
        if(DEMO_MODE == 0 )    
		if(selection >= 0)  
            if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
                display[selection].rank++;
         
		 if(game_mode == FRONT)       
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='D';
           else
               lvl_text[cur_letter]='d';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='D';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='d';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }      
        
     }

     if(game_paused == false) 
     if(!mode) // game_mode == WALK && 
     {
	     if( keys['D'] || keys[VK_RIGHT]) // Zoom function
	     {
             KEY_RIGHTWARD = true;

	     }   
	     if( !keys['D'] && !keys[VK_RIGHT]) 
	     {
	         KEY_RIGHTWARD = false;  


			 keys['D']=false;

	         keys[VK_RIGHT]=false;
	     } 
	 }  

     if(game_paused == false)
     if (keys['A'])						// Is F1 Being Pressed?
     { 
	   	 if(mode || text_selected == true)								
            keys['A']=FALSE;					// If So Make Key FALSE

         if(text_selected== false)
         if(DEMO_MODE == 0 )      
		 if(selection >= 0)
            if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
                display[selection].rank--;
    	 
		 if(game_mode == FRONT)		
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='A';
           else
               lvl_text[cur_letter]='a';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='A';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='a';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true; 
               
         } 
       
     }     

	 if(game_paused == false)      
     if(!mode) // game_mode == WALK && 
     {
	     if( keys['A'] || keys[VK_LEFT]) // Zoom function
	     {
             KEY_LEFTWARD = true;

	     } 
	     if( !keys['A'] && !keys[VK_LEFT])
	     {
	         KEY_LEFTWARD = false;


			 keys['A']=false; 

			 keys[VK_LEFT] = false;

	     }
	 }              

	 if(game_paused == false)     
     if (keys['H'])						// Is F1 Being Pressed?
     { 
        keys['H']=FALSE;					// If So Make Key FALSE
        
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='H';
           else
               lvl_text[cur_letter]='h';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='H';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='h';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }     
         
         if(!mode && game_mode == WALK)
         { 
                  
             if(ply_id != -1)
             if(sprite[ply_id].score > 0)
             {
                 if(Has_This_Item(INV_AMPUOLE, -1) == true)
                 {
                      Remove_Item(INV_AMPUOLE, -1, -1, false);
                                              
                      Calculate_Health(AMOUNT_AMPUOLE, true, ply_id, false); 
                      
                      Calculate_Lifebar();        
                     
                      Calculate_Inventory();      
    
                      medikit_sfx = true;  
                                                       
                 }
                 else if(Has_This_Item(INV_HEALTH, -1) == true)
                 {
                      Remove_Item(INV_HEALTH, -1, -1, false);
                                              
                      Calculate_Health(AMOUNT_HEALTH, true, ply_id, false);
                      
                      Calculate_Lifebar();        
                     
                      Calculate_Inventory();      
    
                      medikit_sfx = true; 
                                                       
                 }
                 else
                     Display_Message(ply_id, MSG_NOHEALTH); 
             
             }
             
                  
         }
         
          
              
    }  
    

	 if(game_paused == false)          
     if (keys['O'])
     {
         if(mode || game_mode != WALK)          
	         keys['O'] = FALSE;

        if(text_selected== false)
        if(DEMO_MODE == 0 )       
		if(selection >= 0) 
            if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
            if(display[selection].onCreate > -2)
                display[selection].onCreate--;
                
        if(text_selected== false)
        if(DEMO_MODE == 0 )   
		if(pt_selection >= 0)
         if( mode == POINT_MODE)
         {
             keys['Q']=FALSE;
             points[pt_selection].c4--;
         }
         
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='O';
           else
               lvl_text[cur_letter]='o';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='O';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='o';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }                        
                   
     }
     

	 if(game_paused == false) 	           
     if(keys['P'])
     { 
         keys['P']=false; 
        
  //      if(!mode)
  //          gallery_sfx = true;
         
        if(text_selected== false)
        if(DEMO_MODE == 0 )      
		if(selection >= 0)                
         if( mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
         {

             display[selection].onCreate++;
            
         }  
         
        if(text_selected== false)
        if(DEMO_MODE == 0 )   
         if( mode == POINT_MODE)
         {
             keys['Q']=FALSE;
             points[pt_selection].c4++;
         } 

         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='P';
           else
               lvl_text[cur_letter]='p';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='P';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='p';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }    
         
                               
     }  
      

	 if(game_paused == false)
     if (keys['T'] || (DX_BACK_BUTTON && text_selected==false))						// Is F1 Being Pressed?
     { 
		  
        keys['T']=FALSE;					// If So Make Key FALSE

		if(next_scene == false)
        if(text_selected== false) 
	    if(!mode && game_mode == WALK)  
		if(in_dungeon != true && dm_game == DM_NONE && global_objects[66] == GLOBAL_BEATEN && Level != LVL_HIGHWAY)
	    {

			DX_BACK_BUTTON=false;           

			#if INCLDUE_360_CONTROLLER == 1

			if(CONTROLLER) 
			{ 

				saved_mouseX = mouseX; 
				saved_mouseY = mouseY;
			 
				saved_DXmouseX = DXmouseX;
				saved_DXmouseY = DXmouseY;

				saved_DXTarMouseX = DXTarMouseX;
				saved_DXTarMouseY = DXTarMouseY;

			}

			#endif

		    stats_scene   = scene;
            stats_episode = episode;
                                                                  
            episode = 1; 
            scene   = 1;
             
            next_scene = true;
		}

        if(text_selected== false)
        if(DEMO_MODE == 0 )    
		if(selection >= 0)     
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
             if(display[selection].onCreate_action>0)
                 display[selection].onCreate_action--;
                 
        if(text_selected== false)
        if(DEMO_MODE == 0 )       
		if(pt_selection >= 0)          
         if( mode == POINT_MODE)
         {
             points[pt_selection].c2--;
         }     
         
        if(text_selected== false)
        if(DEMO_MODE == 0 )         
         if( mode == TILE_MODE)
         {
             if(tileset_selected == 0)
                 tileset_selected = 1;
             else
                 tileset_selected = 0;
         }    
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='T';
           else
               lvl_text[cur_letter]='t';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='T';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='t';
                                         
           if(cur_letter < input_cap)     
               cur_letter++;
               
           type_sfx = true; 
                 
         }   

        
     }  

	 if(game_paused == false)     
     if (keys['Y'])						// Is F1 Being Pressed?
     {
        keys['Y']=FALSE;					// If So Make Key FALSE
                 
        if(text_selected== false)
        if(DEMO_MODE == 0 )     
		if(selection >= 0)    
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
             display[selection].onCreate_action++;
             
         if( mode == POINT_MODE)
		 if(pt_selection >= 0)
         {
             points[pt_selection].c2++;
         }               
          
         
         if(!mode)
             has_water = true;
         
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='Y';
           else
               lvl_text[cur_letter]='y';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='Y';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='y';
                                         
            if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
                    
         }     
             
         if(DEMO_MODE == 0)  
         if(text_selected == false)     
         if(!mode)           
         {           
              
         }    
                 
     } 
     

	 if(game_paused == false)
     if (keys['U'])						// Is F1 Being Pressed?
     {
		if(mode || game_mode != WALK)
            keys['U']=FALSE;					// If So Make Key FALSE
        
        if(text_selected== false)
        if(DEMO_MODE == 0 )         
		if(selection >= 0)
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
             if(display[selection].onDeath_action>-1)
                 display[selection].onDeath_action--;
         if( mode == POINT_MODE)
		 if(pt_selection >= 0)
         {
             points[pt_selection].c3--;
         }                   
 
        if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
        {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='U';
           else
               lvl_text[cur_letter]='u';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='U';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='u';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
        }             
        
     }  
     

	 if(game_paused == false)
     if (keys['I'])						// Is F1 Being Pressed?
     {

		if(mode || text_selected == true)
	        keys['I']=FALSE;					// If So Make Key FALSE
        
        if(text_selected== false)
        if(DEMO_MODE == 0 )    
		if(selection >= 0)     
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
             display[selection].onDeath_action++;
             
         if( mode == POINT_MODE)
		 if(pt_selection >= 0)
         {
             points[pt_selection].c3++;
         }          
              
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='I';
           else
               lvl_text[cur_letter]='i';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='I';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='i';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }             
             
     }  
     
      // ANIM.STATE       
     if(DEMO_MODE == 0)
	 if(mode)
     if(!keys[VK_CONTROL] && keys[VK_F2])
     {
                   
         keys[VK_F2] = FALSE; 

         if(mode)
         {
             if( mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
			 if(selection >= 0)
             if(display[selection].anim)
                 display[selection].anim--;
                 
             if(mode == POINT_MODE)
			 if(pt_selection >= 0)
                 points[pt_selection].anim--;
              
         } 
     
     }   

	 if(game_paused == false)     
     if(DEMO_MODE == 0) 
     if (keys[VK_F3])
     {
                   
         keys[VK_F3] = FALSE;
      
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		 if(selection >= 0)
         {
             if(display[selection].type != CUT && display[selection].type != BUT && display[selection].type != ALM)
             if(display[selection].anim < a_texture[display[selection].fx_id].no_of_anims-1)
             display[selection].anim++;
             
             if(display[selection].type == CUT || display[selection].type == BUT || display[selection].type == ALM)
                 display[selection].anim++;
             
         }
             
         if(mode == POINT_MODE)
		 if(pt_selection >= 0)
             points[pt_selection].anim++;
       
     }

	 if(game_paused == false)     
     if(DEMO_MODE == 0) 
     if( keys[VK_F5])
     {
         
         keys[VK_F5]=FALSE;
         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		 if(selection >= 0)
             display[selection].alpha -= 0.05f;
                     
     } 

	 if(game_paused == false)     
     if(DEMO_MODE == 0)
     if( keys[VK_F6])
     {
         
         keys[VK_F6]=FALSE;
         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		 if(selection >= 0)		
             display[selection].alpha += 0.05f;
                     
     }   

	 if(game_paused == false)     
     if(DEMO_MODE == 0)
     if( keys[VK_F7])
     {
         
         keys[VK_F7]=FALSE;
         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		 if(selection >= 0)
             display[selection].linked_sprite--;
                     
     }

	 if(game_paused == false)     
     if(DEMO_MODE == 0) 
     if( keys[VK_F8]) 
     {
         
         keys[VK_F8]=FALSE;
         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		 if(selection >= 0)
             display[selection].linked_sprite++;
                      
     }    

	 if(game_paused == false)     
     if(DEMO_MODE == 0) 
     if(keys[VK_CONTROL] && keys[VK_F2])
     { 
         keys[VK_F2]=FALSE;
         
         if(debug_active == true)
         {
             debug_active = false;                   
         }
         else
         {
             debug_active = true;
         }
         
     }    
      

	 if(game_paused == false)         
     if( keys['E'])
     {
		 if(mode || game_mode != WALK)	
	         keys['E']=FALSE;
         
        if(text_selected== false)
        if(DEMO_MODE == 0 )         
		 if(selection >= 0)
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
             display[selection].priority--;
                 
         if( mode == POINT_MODE)
		 if(pt_selection >= 0)
         {
             points[pt_selection].c1--;
         }             
                
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true) 
               lvl_text[cur_letter]='E';
           else
               lvl_text[cur_letter]='e';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='E';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='e';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }         

     }   
     

	 if(game_paused == false)        
     if( keys['R'])
     {
         keys['R']=FALSE;
        if(text_selected== false)
        if(DEMO_MODE == 0 )    
		 if(selection >= 0)     
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
             display[selection].priority++;
                          
         if( mode == POINT_MODE)
		 if(pt_selection >= 0)
         {
             points[pt_selection].c1++; 
         }     
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='R';
           else
               lvl_text[cur_letter]='r';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='R';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='r';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }    
		  

     }    
     
     // Change Sprite type

	 if(game_paused == false)
     if (keys['V'])						// Is F1 Being Pressed?
     {
        keys['V']=FALSE;					// If So Make Key FALSE
        
        if(text_selected== false)
        if(DEMO_MODE == 0 )        
        if(mode  && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)        
        if(game_mode == WALK || game_mode == FRONT || game_mode == WORLD)
        {
            
        DisplayText( 3000, 0, 0, TXT_OVERWRITE_ON, TRI_RESET );
        
        if(( game_mode == WALK || game_mode == WORLD))
		if(selection >= 0)  
            display[selection].type++;
        
        if(game_mode == FRONT)
        if(mode)
		if(selection >= 0)  
            display[selection].type++;            
            
        }
                   
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='V';
           else
               lvl_text[cur_letter]='v';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='V';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='v';
                                         
            if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }            

     } 
     

	 if(game_paused == false)
     if (keys['C'])						// Is F1 Being Pressed?
     {
        keys['C']=FALSE;					// If So Make Key FALSE
        
        if(text_selected== false)
        if(DEMO_MODE == 0 )        
        if(mode  && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
        if(game_mode == WALK || game_mode == FRONT || game_mode == WORLD)
        {
                
        DisplayText(3000,1,0,TXT_OVERWRITE_ON, TRI_RESET);

		if(selection >= 0)  
        if(mode && display[selection].type > 0)
            display[selection].type--; 
            
        }

        if(text_selected== false)		
        if(DEMO_MODE == 0 )   		
		if(mode == TILE_MODE)
		{
	       	if(paint_mode == false) 
			{
				paint_mode = true; 
			}
			else
			{
				paint_mode = false;
			}
 
        }
         
        if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='C';
           else
               lvl_text[cur_letter]='c';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='C';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='c';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }      
            
     }    
     
     // Change Object's Collision On/Off
     

	 if(game_paused == false)
     if (keys['F'])						// Is F1 Being Pressed?
     {
        keys['F']=FALSE;					// If So Make Key FALSE
        
        if(text_selected== false)
        if(DEMO_MODE == 0 )        
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		if(selection >= 0)  
        {
            if(display[selection].grab_switch == false)
                display[selection].grab_switch = true;
            else
                display[selection].grab_switch = false;
        }  
                
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='F';
           else
               lvl_text[cur_letter]='f';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='F';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='f';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         } 
                                    
     }
     
     // Change Object's Collision On/Off

	 if(game_paused == false)
     if (keys['G'])						// Is F1 Being Pressed?
     {
        keys['G']=FALSE;					// If So Make Key FALSE
        
		if(game_mode == WALK && !mode)
		if(ply_id != -1) 
		if(sprite[ply_id].on_ladder == false)
		{ 
			sprite[ply_id].status = STUNNED;
			stolen_sfx = true;
			sprite[ply_id].anim_state = WAIT;
			sprite[ply_id].update = true;
		    sprite[ply_id].moving = false; // Hack?
		    Rank_Timer(ply_id, STUNNED); 
		}
        
        if(text_selected== false)
        if(DEMO_MODE == 0 )        
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
	    if(selection >= 0)  
            if(display[selection].mouseover == false)
                display[selection].mouseover = true;
            else
                display[selection].mouseover = false;
                
        if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='G';
           else
               lvl_text[cur_letter]='g';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='G';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='g';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }         
          
        if(mode == TILE_MODE)
        {  
            // Reset Map 
            for(int y=0;y<MAP_HEIGHT;y++) 
                for(int x=0;x<MAP_WIDTH;x++)
                if(tiles[(y*MAP_HEIGHT)+x] != 0 
                && tiles[(y*MAP_HEIGHT)+x] != 16 
                && tiles[(y*MAP_HEIGHT)+x] != 32
                && tiles[(y*MAP_HEIGHT)+x] != 48  
                && tiles[(y*MAP_HEIGHT)+x] != 64  
                && tiles[(y*MAP_HEIGHT)+x] != 80 
                && tiles[(y*MAP_HEIGHT)+x] < 96 )   
                { 
                                    
                    a_switch = false;
                                    
                    if(tiles[(y*MAP_HEIGHT)+x] == 61 ||tiles[(y*MAP_HEIGHT)+x] == 62 || tiles[(y*MAP_HEIGHT)+x] == 63)
                    {
                        tiles[(y*MAP_HEIGHT)+x] = 48;
                        a_switch=true; 
                    }
                    if(tiles[(y*MAP_HEIGHT)+x] == 77 ||tiles[(y*MAP_HEIGHT)+x] == 78 || tiles[(y*MAP_HEIGHT)+x] == 79)
                    {
                        tiles[(y*MAP_HEIGHT)+x] = 64;
                        a_switch=true;
                    }    
                    if(tiles[(y*MAP_HEIGHT)+x] == 29 ||tiles[(y*MAP_HEIGHT)+x] == 30 || tiles[(y*MAP_HEIGHT)+x] == 31)
                    {
                        tiles[(y*MAP_HEIGHT)+x] = 16;
                        a_switch=true;
                    }      
                    if(a_switch == false)    
                        tiles[(y*MAP_HEIGHT)+x] = 0; 
                        
                } 
            
            for(int y=0;y<MAP_HEIGHT;y++)
                for(int x=0;x<MAP_WIDTH;x++)
                    Generate_Map((y*MAP_HEIGHT)+x, 16);
            for(int y=0;y<MAP_HEIGHT;y++) 
                for(int x=0;x<MAP_WIDTH;x++) 
                    Generate_Map((y*MAP_HEIGHT)+x, 32); 
            for(int y=0;y<MAP_HEIGHT;y++)
                for(int x=0;x<MAP_WIDTH;x++)
                    Generate_Map((y*MAP_HEIGHT)+x, 48); 
            for(int y=0;y<MAP_HEIGHT;y++) 
                for(int x=0;x<MAP_WIDTH;x++) 
                    Generate_Map((y*MAP_HEIGHT)+x, 64);
            for(int y=0;y<MAP_HEIGHT;y++)
                for(int x=0;x<MAP_WIDTH;x++)  
                    Generate_Map((y*MAP_HEIGHT)+x, 80); 
                     
            // Calculate the BG collision
            for(int i=0;i<MAP_TILES;i++)
            { 
                                  
              // Variation Blocks
              if(tiles[i] == 48 || tiles[i] == 61 || tiles[i] == 62 || tiles[i] == 63 ) 
              { 
                  tiles[i] = 48;        
              }    
                            
              if(tiles[i] == 16 ) 
              { 
                          
                rnd = rand()%200; 
                 
                if(rnd < 10)    
                {
                    tiles[i] = 29;       
                }   
                                                                  
              }   
                                                
              // Variation Blocks
              if(tiles[i] < 16) 
              { 
                          
                rnd = rand()%200;  
                
                if(rnd < 10)   
                {
                    rnd1 = rand()%5;
                    rnd1 += 5;
                    tiles[i] = rnd1;       
                }
                if(rnd == 10)          
                {
                    rnd1 = rand()%3;
                    rnd1 += 10;     
                    tiles[i] = rnd1;       
                }
                if(rnd > 10)  
                {
                    rnd1 = rand()%5;
                    tiles[i] = rnd1;
                }   
                                 
              }   
                                            
              if(tiles[i]>=48 && tiles[i]<64)
                map_col[i] = true;
              else 
                map_col[i] = false;  
                
            } 
        }
                                    
     }
          
     // Change Object's Collision On/Off

	 if(game_paused == false)
     if (keys['L'])						// Is F1 Being Pressed?
     {

		if(mode || text_selected == true)
            keys['L']=FALSE;					// If So Make Key FALSE

         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='L';
           else
               lvl_text[cur_letter]='l';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='L';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='l';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }   
     }
      

	 if(game_paused == false)
     if (keys['B'])						// Is F1 Being Pressed?
     {
        keys['B']=FALSE;					// If So Make Key FALSE
        
		if(DEBUG_MODE == 0 && DEMO_MODE == 0)
		if(game_mode == WALK && !mode) 
		{
		/*	if(has_buddy == BUDDY_ALIVE)
				has_buddy = BUDDY_WAIT;
			else
				has_buddy = BUDDY_ALIVE;

			if(ply_id != -1)
				Display_Message(ply_id, MSG_BUDDYONOFF);*/

			if(ply_hat_id != -1) 
			if(sprite[ply_hat_id].mouseover == false) 
			{ 
				sprite[ply_hat_id].alpha = 0.0;
				sprite[ply_hat_id].turn_off = true;
				sprite[ply_hat_id].mouseover = true;
			}
			else
			{
				sprite[ply_hat_id].alpha = 1.0;
				sprite[ply_hat_id].turn_off = false;
				sprite[ply_hat_id].mouseover = false;
				cash_up_sfx = true;
			}


		}

        if(text_selected== false)
        if(DEMO_MODE == 0 )        
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		if(selection != 0)
            display[selection].sector--;
            
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='B';
           else
               lvl_text[cur_letter]='b';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='B';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='b';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }    
     } 

	 if(game_paused == false)     
     if (keys['N'])						// Is F1 Being Pressed?
     {
        keys['N']=FALSE;					// If So Make Key FALSE
        
        if(text_selected== false)
        if(DEMO_MODE == 0 )        
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		if(selection >= 0)
            display[selection].sector++;
 
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='N';
           else
               lvl_text[cur_letter]='n';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='N';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='n';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         }         
    
     }  
     

	 if(game_paused == false)     
     if(keys['Z'])		 				// Is F1 Being Pressed?
     { 

        if(mode || text_selected == true)                
			keys['Z'] = false;
         
        if(text_selected== false)
        if(DEMO_MODE == 0 )        
        if(!mode && game_mode == WALK)
        {
            hours=8;     
            minutes=0; 
            wakeup_timer=0;
			keys['Z'] = false;
        }
        
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		if(selection >= 0)
        {
            keys['Z']=FALSE;					// If So Make Key FALSE
            display[selection].sector_action--;
        }   
        
        if(mode && mode == TILE_MODE)
        {
            keys['Z']=FALSE;    
            
            mouse_paste=false;
            
            if(mouse_copy == true)
                mouse_copy = false;
            else
                mouse_copy = true;        
        } 
        
         if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                         
           if(shift_key == true)
               lvl_text[cur_letter]='Z';
           else
               lvl_text[cur_letter]='z';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='Z';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='z';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
               
         } 
        
     } 
             
     // If no health restart scene
 /*    if(!mode && ( game_mode == WALK || game_mode == WORLD) )
     if( (int)TimerGetTime() > death_counter && death_ready == true ) 
     { 
            
         death_ready = false; 
                             
         next_scene = true;
         
         scene = 0;
             
     } */ 
        

	 if(game_paused == false)
     if(keys['X'])						// Is F1 Being Pressed?
     {
        keys['X']=FALSE;					// If So Make Key FALSE

        if(text_selected== false) 
        if(DEMO_MODE == 0 )           
        if(!mode && game_mode == WALK)
        { 
            hours=24;  
            minutes=0;
            wakeup_timer=0;
			keys['X']=FALSE;
        }
                
        if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
		if(selection >= 0)
            display[selection].sector_action++;
            
        if(mode == TILE_MODE) 
        {
            mouse_brush_size++;
            
            if(mouse_brush_size > 3)
                mouse_brush_size = 0;
                
        }
        if(text_selected == true && !mode && cur_letter < input_cap && cur_letter >= 0)
         {
                                           
           if(shift_key == true)
               lvl_text[cur_letter]='X';
           else
               lvl_text[cur_letter]='x';
           
           if(capital_key > 0)
               lvl_text[cur_letter]='X';
           
           if(capital_key > 0 && shift_key == true)
               lvl_text[cur_letter]='x';
                                         
           if(cur_letter < input_cap)
               cur_letter++;
               
           type_sfx = true;
                
         } 
     } 

	 if(game_paused == false)        
     if(DEMO_MODE == 0)
     if(keys[VK_F4])
     { 
                        
         keys[VK_F4]=false; 
         
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
             scene_shake++;                
     }

	 if(game_paused == false)      
     if(DEMO_MODE == 0)
     if(keys[VK_F11])
     {
                        
         keys[VK_F11]=false;
                                 
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
             scene_shake--;  
          
         if(!mode)
         {
                  
             if(fps_counter == false)
             {
                 fps_counter=true; 
             }
             else
                 fps_counter=false;
          
         }    
                                   
     }

	 if(game_paused == false)
     if(keys[VK_CONTROL] && keys[VK_F11])
     {
                        
         keys[VK_F11]=false;
                                 
         if(mode && mode != POINT_MODE && mode != NODES && mode != TILE_MODE)
             scene_shake--;  
          
         if(!mode)
         {
                  
             if(fps_counter == false)
             {
                 fps_counter=true; 
             }
             else
                 fps_counter=false;
          
         }    
                                   
     }           
     
	 if(game_paused == false) 
     if(keys[VK_ESCAPE]) 
     {
                          
		keys[VK_ESCAPE] = false;  

		sta2_esc_pressed = true;
		
		if(game_mode == WALK && !mode)
		{

			if(QUICK_PLAY == 1) 
			if(sta2_turn == TURN_COMPUTER)
			{
				sta2_enemy_mode = MOVE_END;
				sta2_timer = 0;
			}

			if(next_scene == false)
			{

				DX_BACK_BUTTON=false;     

				#if INCLDUE_360_CONTROLLER == 1
				     
				if(CONTROLLER) 
				{ 

					saved_mouseX = mouseX; 
					saved_mouseY = mouseY;
			 
					saved_DXmouseX = DXmouseX;
					saved_DXmouseY = DXmouseY;

					saved_DXTarMouseX = DXTarMouseX;
					saved_DXTarMouseY = DXTarMouseY;

				} 
				 
				#endif   
				 
				sta2_7_pressed = true;

			}
		}


     }                      
                         		
	 return true;   
}

void Quit_Code(bool quit_active) 
{
   
    if(current_file != -1 && game_mode == WALK && episode != 0)
    {   
        sprintf( temp_string.string, "data/save/fragfile%i", current_file);
        SaveLevel( temp_string);  
    }
                
    stats_scene   = scene;
    stats_episode = episode;
    
    episode = 1; 
    scene   = 53;
    
    next_scene = true;  
    
    activate_bicycle = false;
     
} 
 
void Calculate_Edges(int testme, int solid)
{ 
    int g_index=0; 
    int safe_g_index=0;        
    bool g_direct[8];    
   
   memset(g_direct, false, sizeof(g_direct) );
   
   if(testme >= 0)
   {	

   if(tiles[testme]!= solid && testme >=0 && testme < MAP_TILES)     
   {     
	   if(testme+1 >= 0)
       if(tiles[testme+1] == solid) // LEFT 
           g_direct[7] = true;
	   if(testme-1 >= 0)	
       if(tiles[testme-1] == solid) // RIGHT
           g_direct[3] = true;
	   if(testme+MAP_WIDTH >= 0)
       if(tiles[testme+MAP_WIDTH] == solid) // UP
           g_direct[5] = true;
	   if(testme-MAP_WIDTH >= 0)	
       if(tiles[testme-MAP_WIDTH] == solid) // DOWN
           g_direct[1] = true;   
	   if(testme+(MAP_WIDTH+1) >= 0)
       if(tiles[testme+(MAP_WIDTH+1)] == solid) // UP-LEFT
           g_direct[6] = true; 
	   if(testme+(MAP_WIDTH-1) >= 0)
       if(tiles[testme+(MAP_WIDTH-1)] == solid) // UP-RIGHT
           g_direct[4] = true;
	   if(testme-(MAP_WIDTH+1) >= 0)
       if(tiles[testme-(MAP_WIDTH+1)] == solid) // DOWN-LEFT
           g_direct[0] = true;
	   if(testme-(MAP_WIDTH-1) >= 0)
       if(tiles[testme-(MAP_WIDTH-1)] == solid) // DOWN-RIGHT
           g_direct[2] = true;     
    
       if(g_direct[7] == true) // LEFT  
           tiles[testme]=solid+1; 
       if(g_direct[3] == true) // RIGHT
           tiles[testme]=solid+2;   
       if(g_direct[5] == true) // UP
           tiles[testme]=solid+4;
       if(g_direct[1] == true) // DOWN
           tiles[testme]=solid+3; 
                        
       if(g_direct[7] == true && g_direct[5] == true) // UP-LEFT
           tiles[testme]=solid+12;                                                   
       if(g_direct[3] == true && g_direct[5] == true) // UP-RIGHT
           tiles[testme]=solid+11;                                                   
       if(g_direct[7] == true && g_direct[1] == true) // DOWN-LEFT
           tiles[testme]=solid+9;                              
       if(g_direct[3] == true && g_direct[1] == true) // DOWN-RIGHT
           tiles[testme]=solid+10;     

       if(g_direct[6] == true && g_direct[5] == false && g_direct[7] == false) // UP-LEFT Corner
           tiles[testme]=solid+7;  
       if(g_direct[4] == true && g_direct[5] == false && g_direct[3] == false) // UP-RIGHT Corner
           tiles[testme]=solid+8;  
                         
       if(g_direct[0] == true && g_direct[1] == false && g_direct[3] == false) // DOWN-LEFT Corner
           tiles[testme]=solid+6;    
       if(g_direct[2] == true && g_direct[1] == false && g_direct[7] == false) // DOWN-RIGHT Corner
           tiles[testme]=solid+5;    
                                                 
    }   // Safety check     

	} // testme >= 0 
     
     
}

void Generate_Map(int g_index, int base_tile)
{ 
     
    int safe_g_index=0; 
    bool g_direct[8];
        
    memset(g_direct, false, sizeof(g_direct) );
                    
    safe_g_index = g_index;   
	if(g_index >= 0) 
    if(safe_g_index > 0 && safe_g_index < MAP_TILES)
    if(tiles[g_index]==0) // Only if it's a ground tile
    {  
        if(tiles[safe_g_index+1] == base_tile) // LEFT 
           g_direct[7] = true; 
        if(tiles[safe_g_index-1] == base_tile) // RIGHT
           g_direct[3] = true;
        if(tiles[safe_g_index+MAP_WIDTH] == base_tile) // UP
           g_direct[5] = true;
        if(tiles[safe_g_index-MAP_WIDTH] == base_tile) // DOWN
           g_direct[1] = true;   
        if(tiles[g_index+(MAP_WIDTH+1)] == base_tile) // UP-LEFT
           g_direct[6] = true;
        if(tiles[g_index+(MAP_WIDTH-1)] == base_tile) // UP-RIGHT
           g_direct[4] = true;
        if(tiles[g_index-(MAP_WIDTH+1)] == base_tile) // DOWN-LEFT
           g_direct[0] = true;
        if(tiles[g_index-(MAP_WIDTH-1)] == base_tile) // DOWN-RIGHT
           g_direct[2] = true;      
                        
        if(g_direct[7] == true) // LEFT  
           tiles[g_index]=1+base_tile; 
        if(g_direct[3] == true) // RIGHT 
           tiles[g_index]=2+base_tile;   
        if(g_direct[5] == true) // UP
           tiles[g_index]=4+base_tile;
        if(g_direct[1] == true) // DOWN
           tiles[g_index]=3+base_tile; 
                        
        if(g_direct[7] == true && g_direct[5] == true) // UP-LEFT
           tiles[g_index]=12+base_tile;                                                   
        if(g_direct[3] == true && g_direct[5] == true) // UP-RIGHT
           tiles[g_index]=11+base_tile;                                                   
        if(g_direct[7] == true && g_direct[1] == true) // DOWN-LEFT
           tiles[g_index]=9+base_tile;                              
        if(g_direct[3] == true && g_direct[1] == true) // DOWN-RIGHT
           tiles[g_index]=10+base_tile;    

        if(g_direct[6] == true && g_direct[5] == false && g_direct[7] == false) // UP-LEFT Corner
           tiles[g_index]=7+base_tile;  
        if(g_direct[4] == true && g_direct[5] == false && g_direct[3] == false) // UP-RIGHT Corner
           tiles[g_index]=8+base_tile; 
                         
        if(g_direct[0] == true && g_direct[1] == false && g_direct[3] == false) // DOWN-LEFT Corner
           tiles[g_index]=6+base_tile;    
        if(g_direct[2] == true && g_direct[1] == false && g_direct[7] == false) // DOWN-RIGHT Corner
           tiles[g_index]=5+base_tile;    
    }                                                           
     
}

void Generate_Bush(int y, int x, int base_tile, int dir)
{ 
     
    int safe_g_index=0; 
    bool g_direct[8];
    int cut_tile = 192;
        
    memset(g_direct, false, sizeof(g_direct) );
                    
    safe_g_index = (y*MAP_HEIGHT)+x;     
    
    // Only tiles above....for now  
	if(safe_g_index >= 0)    
    if(safe_g_index < MAP_TILES)
    if(tiles[safe_g_index] >= base_tile && tiles[safe_g_index] < base_tile + 16 || tiles[safe_g_index] >= 192 && tiles[safe_g_index] < 208 )
    {
        if(dir == UP) 
        {    
                            
        if(tiles[safe_g_index] == base_tile || tiles[safe_g_index] == base_tile+13
        || tiles[safe_g_index] == base_tile+14 || tiles[safe_g_index] == base_tile+15)
            tiles[safe_g_index] = cut_tile;   

        if(tiles[safe_g_index] == base_tile + 1)
            tiles[safe_g_index] = cut_tile + 1;
                
        if(tiles[safe_g_index] == base_tile + 2) 
            tiles[safe_g_index] = cut_tile + 2; 
                
        if(tiles[safe_g_index] == base_tile + 9) 
            tiles[safe_g_index] = cut_tile + 9;              
            
        if(tiles[safe_g_index] == base_tile + 10)  
            tiles[safe_g_index] = cut_tile + 10;
            
        if(tiles[safe_g_index] == base_tile + 11) 
            tiles[safe_g_index] = cut_tile + 11; 
            
        if(tiles[safe_g_index] == base_tile + 12) 
            tiles[safe_g_index] = cut_tile + 12;
        
        if(tiles[safe_g_index] == base_tile + 5)
        { 
            tiles[safe_g_index] = cut_tile + 5;
            map_col[safe_g_index] = 0;            
        }    
        if(tiles[safe_g_index] == base_tile + 6)  
        {
            tiles[safe_g_index] = cut_tile + 6;
            map_col[safe_g_index] = 0; 
        }  
        if(tiles[safe_g_index] == base_tile + 3)  
        {
            tiles[safe_g_index] = (cut_tile-16) + 3;
            map_col[safe_g_index] = 0;  
        }  
        
        // Cut tiles that are above the cut point
        if(tiles[safe_g_index] == cut_tile + 15)   
        {
            tiles[safe_g_index] = cut_tile-16;
            map_col[safe_g_index] = 0;   
        } 
        if(tiles[safe_g_index] == cut_tile + 13)   
        {
            tiles[safe_g_index] = (cut_tile-16)+1;
            map_col[safe_g_index] = 0;   
        } 
        if(tiles[safe_g_index] == cut_tile + 14)   
        {
            tiles[safe_g_index] = (cut_tile-16)+2;
            map_col[safe_g_index] = 0;    
        }         
        if(tiles[safe_g_index] == cut_tile + 7)   
        {
            tiles[safe_g_index] = (cut_tile-16)+9;
            map_col[safe_g_index] = 0;   
        } 
        if(tiles[safe_g_index] == cut_tile + 8)   
        {
            tiles[safe_g_index] = (cut_tile-16)+10;
            map_col[safe_g_index] = 0;   
        }                 
        
                        
        }
        
        
        if(dir == DOWN)
        {                   
          if(tiles[safe_g_index] == base_tile || tiles[safe_g_index] == base_tile+13
          || tiles[safe_g_index] == base_tile+14 || tiles[safe_g_index] == base_tile+15)
              tiles[safe_g_index] = cut_tile+15; 

          if(tiles[safe_g_index] == base_tile + 1)
            tiles[safe_g_index] = cut_tile + 13;
            
          if(tiles[safe_g_index] == base_tile + 2) 
            tiles[safe_g_index] = cut_tile + 14;
          
          if(tiles[safe_g_index] == base_tile + 9)   
            tiles[safe_g_index] = cut_tile+7; 

          if(tiles[safe_g_index] == base_tile + 10)   
            tiles[safe_g_index] = cut_tile+8;
                       
          if(tiles[safe_g_index] == base_tile + 4)   
          {
            tiles[safe_g_index] = (cut_tile-16)+4;
            map_col[safe_g_index] = 0;   
          } 
          if(tiles[safe_g_index] == base_tile + 7)   
          {
            tiles[safe_g_index] = (cut_tile-16)+7;
            map_col[safe_g_index] = 0;   
          } 
          if(tiles[safe_g_index] == base_tile + 8)   
          {
            tiles[safe_g_index] = (cut_tile-16)+8;
            map_col[safe_g_index] = 0;   
          }  
          if(tiles[safe_g_index] == base_tile + 11)   
          {
            tiles[safe_g_index] = (cut_tile-16)+11;
            map_col[safe_g_index] = 0;   
          } 
                              
          if(tiles[safe_g_index] == base_tile + 12)   
          {
            tiles[safe_g_index] = (cut_tile-16)+12;
            map_col[safe_g_index] = 0;   
          } 
                                                    
          // Cut tiles that are below the cut point
          if(tiles[safe_g_index] == cut_tile)   
          {
            tiles[safe_g_index] = cut_tile-16;
            map_col[safe_g_index] = 0;   
          } 
          // Cut tiles that are below the cut point
          if(tiles[safe_g_index] == cut_tile+1)   
          {
            tiles[safe_g_index] = (cut_tile-16)+1;
            map_col[safe_g_index] = 0;    
          } 
          // Cut tiles that are below the cut point
          if(tiles[safe_g_index] == cut_tile+2)   
          {
            tiles[safe_g_index] = (cut_tile-16)+2;
            map_col[safe_g_index] = 0;   
          } 
          // Cut tiles that are below the cut point
          if(tiles[safe_g_index] == cut_tile+9)   
          {
            tiles[safe_g_index] = (cut_tile-16)+1;
            map_col[safe_g_index] = 0;    
          } 
          // Cut tiles that are below the cut point
          if(tiles[safe_g_index] == cut_tile+10)   
          {
            tiles[safe_g_index] = (cut_tile-16)+2;
            map_col[safe_g_index] = 0;   
          } 
          
          // Remove any remaining peices
          safe_g_index -= MAP_WIDTH;
          
          if(safe_g_index > 0)
          {
            if(tiles[safe_g_index] == base_tile + 7 && map_col[safe_g_index+MAP_WIDTH] == 0)   
            {
              tiles[safe_g_index] = (cut_tile-16)+7;
              map_col[safe_g_index] = 0;   
            }  
            if(tiles[safe_g_index] == base_tile + 8 && map_col[safe_g_index+MAP_WIDTH] == 0)   
            {
              tiles[safe_g_index] = (cut_tile-16)+8;
              map_col[safe_g_index] = 0;   
            }  
          }          
          
                                                                                 
        }  
                                    
    }               
     
}

void Remove_Bush(int row_x, int row_y)
{
    int row=0;  
    bool in_range=false;   
    
    row = (row_y*MAP_HEIGHT)+row_x; 
               
               // Run a bush check first 
			   if(row >= 0)                                   
               if((tiles[row] >= 48 && tiles[row] < 64) || (tiles[row] >= 192 && tiles[row] < 208) )
               {      
                 
                 if(tiles[row] >= 48 && tiles[row] < 64)   
  	                 tiles[row] += 128;          
  	                 
                 if(tiles[row] >= 192 && tiles[row] < 208)
                 {   
                      
                     in_range = false;    
                     
                     if(tiles[row] == 192 + 7)
                     {   
                         tiles[row] = (192-16)+9;
                         in_range = true;
                     }
                     if(tiles[row] == 192 + 8)   
                     {
                         tiles[row] = (192-16)+10;
                         in_range = true;
                         
                     }
                     
                     if(in_range == false)                         
    	                 tiles[row] -= 16;                      
    	                 
   	                 in_range = false;       
   	                 
                 }   
                  
	             map_col[row] = 0;                                                               
                 
	             Generate_Bush( row_y+1, row_x, 48, UP);
	             Generate_Bush( row_y-1, row_x, 48, DOWN);
                     
               }  
               
}

void Quit_From_Multiplayer()  
{
 	 
	   if( ping_quit == true)               
       if((int)TimerGetTime() > quit_network_timer)
       {
                               
           quit_network_timer=0;  
		             
           ping_quit = false;                
           
     	   scene = 22; 
     	   episode = 0;

     	   next_scene = true; 
         
              
       }    	 
	 
}

void Check_For_Grenade()
{
    int found_the_gun = -1;			 	 			
      
      for(int j=0;j<16;j++)          
      if(player_inv[j] == INV_GRENADE_A)
          found_the_gun = j;
      
      if(found_the_gun != -1)  
      {        
         
    /*      switching_to_weapon=found_the_gun;
          
          next_weapon_timer = (int)TimerGetTime() + GUN_SWITCH_TIME;
          
          switched_weapon = false;*/

          current_special = found_the_gun;

      //    spark_sfx = true;
      
      } 
      else
      {
          if(ply_id != -1)
          Display_Message(ply_id, MSG_NOGRENADE);    
      }   	 
	 
}

void Grab_Data_For_Map() 
{
	float  mid_x=0.0f, mid_y=0.0f;
	int unit_count=0;
	int index=0;
	int unit_list[100]; 
	int map_list[100]; 

	no_of_map_pins=0;  

	emy_id = -1;

	sta2_cpu_map_unit = -1;

	sta2_enemy_count = 0;  
	sta2_player_count = 0; 

	sta2_has_officer = false;

	for(int i = 0;i < no_sprites;i++)    
	{  
		 
		if(sprite[i].type == UNT)          
		{   
			 
			 if(sprite[i].score > 0) 
			 if(sprite[i].linked_sprite != player_type)
			 {
			     sta2_enemy_count++;  
			 } 
			  
			 if(sprite[i].score > 1) 
			 if(sprite[i].linked_sprite == player_type)
			 {
			    sta2_player_count++;   
			 }

			// Select next unit for computer...
			if(sprite[i].score > 0) 
			if(sprite[i].linked_sprite != player_type) 
		//	if(sprite[i].unit_moved == false || UNITS_CAN_MOVE_MORE_THAN_ONCE == 1)
			{
				unit_list[unit_count] = i;
				map_list[unit_count] = no_of_map_pins;     
				unit_count++;  
			}         

			mid_x = (sprite[i].w + sprite[i].box_width/2)  + map_startX; 
			mid_y = (sprite[i].z + sprite[i].box_height/2) + map_startY;

			map_pins_x[no_of_map_pins] = mid_x / ((float)(MAP_WIDTH/10));  // 0.0f - 1.0f
			map_pins_y[no_of_map_pins] = mid_y / ((float)(MAP_HEIGHT/10));  // 0.0f - 1.0f

			map_pins_index[no_of_map_pins] = i;  

			map_pins_sector_type[no_of_map_pins] = sprite[i].sector;   

			map_pins_score[no_of_map_pins] = sprite[i].score;   
			map_pins_rank[no_of_map_pins] = sprite[i].rank;   

			map_pins_names[no_of_map_pins] = sprite[i].name;   
			  
			map_pins_angle[no_of_map_pins] = sprite[i].angle;

			map_pins_movement[no_of_map_pins] = sprite[i].movement; 

			if(sprite[i].linked_sprite != player_type)  
			{  
				map_pins_type[no_of_map_pins] = PIN_ENEMY;
			}
			 
			if(sprite[i].linked_sprite == player_type)        
			{ 

				if(sprite[i].value2 != -1) 
				{ 
					if(sprite[i].value2 != -1) 
						sta2_squad[sprite[i].value2].health = sprite[i].score;
					if(sprite[i].score > 1)
					{
						if(sta2_squad[sprite[i].value2].type == STA2_CO)
						{
							sta2_has_officer = true;
							sta2_officer_rank = sta2_squad[sprite[i].value2].rank;
						}
					}

				} 
				 
				map_pins_unit_moved[no_of_map_pins] = false; // Reset for enemies...
				map_pins_defend[no_of_map_pins] = false; // Reset for enemies...

				if(sprite[i].linked_sprite == player_type)
					map_pins_defend[no_of_map_pins] = sprite[i].return_fire;  
				 
			//	if(sprite[i].linked_sprite == player_type)
			//		map_pins_unit_moved[no_of_map_pins] = sprite[i].unit_moved;  

				if(sprite[i].value2 != -1)
					map_pins_roster[no_of_map_pins] = sprite[i].value2; 

				if(sprite[i].value3 == PIN_UNIT1)
				{
					map_pins_type[no_of_map_pins] = PIN_UNIT1;
					map_unit_id[PIN_UNIT1] = i; 
				}
				if(sprite[i].value3 == PIN_UNIT2)
				{
					map_pins_type[no_of_map_pins] = PIN_UNIT2;
					map_unit_id[PIN_UNIT2] = i; 
				}
				if(sprite[i].value3 == PIN_UNIT3)
				{
					map_pins_type[no_of_map_pins] = PIN_UNIT3;
					map_unit_id[PIN_UNIT3] = i; 
				}
				if(sprite[i].value3 == PIN_UNIT4) 
				{
					map_pins_type[no_of_map_pins] = PIN_UNIT4;
					map_unit_id[PIN_UNIT4] = i; 
				}
				if(sprite[i].value3 == PIN_UNIT5)  
				{
					map_pins_type[no_of_map_pins] = PIN_UNIT5;
					map_unit_id[PIN_UNIT5] = i; 
				}
			}

			no_of_map_pins++; 
			 
		}
	 

	}  

	// Set emy_id...
	if(sta2_enemy_moves > 0)
	if(sta2_pressed_map == false)
	if(sta2_turn == TURN_COMPUTER || sta2_player_moves <= 0 )
	if(unit_count != 0)
	{
		index = rand()%unit_count;
		emy_id = unit_list[index]; 
		sta2_cpu_map_unit = map_list[index];
	}



}