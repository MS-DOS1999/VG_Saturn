#ifndef __GLOBAL_H__
#define __GLOBAL_H__ 

#ifdef SWITCH
//#include <egl/egl.h>
#include "glad/glad.h"
#endif
#include "texture.h"

      
#define RENDER_RATE  1            // Rate lock for rendering the screen   // ORIGNIAL == 1
#define MAIN_RATE    1            // Rate lock for the main game cycle    // ORIGINAL == 4
#define AI_RATE      5            // Rate lock for AI cycle               // ORIGINAL == 1  
#define KEY_RATE     1            // Rate lock for Keyhandler             // ORIGINAL == 1
#define ANIMATE_RATE 12           // Rate lock for Keyhandler             // ORIGINAL == 20
#define SWAP_RATE    4            // Rate at which it buffers             // ORIGINAL == 10
#define STEAM_RATE   2            // Rate at which it buffers             // ORIGINAL == 10

#define Z_BUFFER_ALWAYS  1


//LPSTR global_lpCmdLine; 

// *****DIRECTX****** //     

//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------

#define SAFE_INT2BOOL(iVar, bVar)  { if(iVar != 0){bVar=true;}else{bVar=false;} }
#define SAFE_BOOL2INT(bVar, iVar)  { if(bVar == false){iVar=0;}else{iVar=1;} }

#define SAFE_DELETE_ARRAY(p)  { if(p) { delete [] p;     (p)=NULL; } }
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

#define TYPE_MODE_NORM       0
#define TYPE_MODE_TEXT       1 
#define TYPE_MODE_HUD        2
#define TYPE_MODE_TEXT_DEBUG 3

#define TOTAL_NUM_TEXTURES  100     

#if IS_USING_DIRECTX == 1    

#define SAMPLE_BUFFER_SIZE 8  // arbitrary number of buffer elements

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)  

// texture declarations
#ifdef PS4
void platform_unlock_achievement(int id);

typedef struct DEBUG_TEX_PS4
{
	sce::SampleUtil::Graphics::Texture* tex;
	char name[256];
};
unsigned int counter_STOCK;
DEBUG_TEX_PS4 texture_STOCK[500];
DEBUG_TEX_PS4 texture[TOTAL_NUM_TEXTURES];
sce::SampleUtil::Graphics::Texture* currentSetTexture;


struct TexturedVertex
{
	sce::Vectormath::Simd::Aos::Vector2 position;
	sce::Vectormath::Simd::Aos::Vector2 texcoord;
};
sce::SampleUtil::Graphics::IndexBuffer  *i_buffer;
sce::SampleUtil::Graphics::VertexBuffer *v_buffer;
TexturedVertex *vertexData;
uint16_t *indexData;

sce::Vectormath::Simd::Aos::Vector4 colorMAIN;
sce::Vectormath::Simd::Aos::Vector4 addMAIN;
#elif XB1
#include "SDL.h"
typedef struct DEBUG_TEX_XB1
{
    SDL_Texture* tex;
    char name[256];
};
void platform_unlock_achievement(int id);
unsigned int counter_STOCK;
DEBUG_TEX_XB1 texture_STOCK[500];
DEBUG_TEX_XB1 texture[TOTAL_NUM_TEXTURES];
SDL_Texture* currentSetTexture;
#endif
int tile_counter = 0;  
int size_of_tiles=0;
int tiles_no_verts=0;
int tiles_no_faces=0;
int tiles_no_indices=0;

int tile_counter1 = 0;  
int size_of_tiles1=0;
int tiles_no_verts1=0;
int tiles_no_faces1=0;
int tiles_no_indices1=0;
#ifdef XB1
typedef struct
{
	unsigned char a;
	unsigned char r;
	unsigned char g;
	unsigned char b;
}ARGB_COLOR;
#endif

struct CUSTOMVERTEX  
{ 
float x, y, z; // Position in 3d space
#ifdef XB1
ARGB_COLOR color;   // Color
#elif PS4
unsigned int color;
#endif
float u, v;    // Texture coordinates 
};
   

#ifdef XB1
CUSTOMVERTEX global_t_vert[4];

D3DXMATRIX matViewReset;    // the view transform matrix    
D3DXMATRIX matView;    // the view transform matrix
D3DXMATRIX matCamView;    // the view transform matrix
D3DXMATRIX matOrtho;
D3DXMATRIX matIdentity;
D3DXMATRIX matProjection;    // the projection transform matrix
D3DXMATRIX matScale;    // the projection transform matrix
D3DXMATRIX matTranslate;    // the projection transform matrix
D3DXMATRIX matViewFinished;
D3DXMATRIX matWorldFinished;
D3DXMATRIX matRotationZ;
D3DXMATRIX matRotationY;
D3DXMATRIX matRotationX;

#elif PS4

CUSTOMVERTEX global_t_vert[4];

D3DXMATRIX matViewReset;    // the view transform matrix    
D3DXMATRIX matView;    // the view transform matrix
D3DXMATRIX matCamView;    // the view transform matrix
D3DXMATRIX matOrtho;
D3DXMATRIX matIdentity;
D3DXMATRIX matProjection;    // the projection transform matrix
D3DXMATRIX matScale;    // the projection transform matrix
D3DXMATRIX matTranslate;    // the projection transform matrix
D3DXMATRIX matViewFinished;
D3DXMATRIX matWorldFinished;
D3DXMATRIX matRotationZ;
D3DXMATRIX matRotationY;
D3DXMATRIX matRotationX;
#endif

#endif  

bool CONTROLLER = true;
bool CONTROLLER_ENABLED = false;
 
#define DELAY_ANALOG_TIME 400  
#define ROTATE_A  1

#define BOX_SMALL   0
#define BOX_WIDE    1 
#define ROW_MIDDLE  3

#if INCLDUE_360_CONTROLLER == 1

#if defined(SWITCH) || defined(PS4) || defined(DREAMCAST)

typedef struct XINPUT_GAMEPAD {
	int				wButtons;
	int				bLeftTrigger;
	int				bRightTrigger;
	int				sThumbLX;
	int				sThumbLY;
	int				sThumbRX;
	int				sThumbRY;
} XINPUT_GAMEPAD;

typedef struct XINPUT_STATE {
	int				dwPacketNumber;
	XINPUT_GAMEPAD	Gamepad;
} XINPUT_STATE;

typedef struct XINPUT_VIBRATION {
	int				wLeftMotorSpeed;
	int				wRightMotorSpeed;
} XINPUT_VIBRATION;

#elif XB1
typedef struct XINPUT_GAMEPAD_CUSTOM {
	int				wButtons;
	int				bLeftTrigger;
	int				bRightTrigger;
	int				sThumbLX;
	int				sThumbLY;
	int				sThumbRX;
	int				sThumbRY;
} XINPUT_GAMEPAD_CUSTOM;

typedef struct XINPUT_STATE_CUSTOM {
	int				dwPacketNumber;
	XINPUT_GAMEPAD_CUSTOM	Gamepad;
} XINPUT_STATE_CUSTOM;

typedef struct XINPUT_VIBRATION_CUSTOM {
	int				wLeftMotorSpeed;
	int				wRightMotorSpeed;
} XINPUT_VIBRATION_CUSTOM;
#endif

#define XINPUT_GAMEPAD_DPAD_UP          0x0001
#define XINPUT_GAMEPAD_DPAD_DOWN        0x0002
#define XINPUT_GAMEPAD_DPAD_LEFT        0x0004
#define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
#define XINPUT_GAMEPAD_START            0x0010
#define XINPUT_GAMEPAD_BACK             0x0020
#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040
#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
#define XINPUT_GAMEPAD_A                0x1000
#define XINPUT_GAMEPAD_B                0x2000
#define XINPUT_GAMEPAD_X                0x4000
#define XINPUT_GAMEPAD_Y                0x8000

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30

#endif

#ifdef XB1
int DXPacketNumber;
#elif SWITCH
int DXPacketNumber;
#elif PS4
int DXPacketNumber;
#elif DREAMCAST
int DXPacketNumber;
#endif

#if defined(SWITCH) || defined(PS4) || defined DREAMCAST
XINPUT_STATE state;

XINPUT_VIBRATION DX_vibration;

XINPUT_VIBRATION DX_1_vibration;
XINPUT_VIBRATION DX_2_vibration;
#elif XB1
XINPUT_STATE_CUSTOM state;

XINPUT_VIBRATION_CUSTOM DX_vibration;

XINPUT_VIBRATION_CUSTOM DX_1_vibration;
XINPUT_VIBRATION_CUSTOM DX_2_vibration;
#endif

int vibrate_time = 0;

int DX_LEFTTHUMB_THRES = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
int DX_CURRENT_TITLE_BUTTON[10];
int DX_TITLE_BUTTONS_COUNT[10];
int DXTSI[10][32];
float DX_TITLE_BUTTONS_X[10][32];
float DX_TITLE_BUTTONS_Y[10][32];
int DX_TITLE_BUTTONS_ID[10][32];
int DX_ROW = ROW_MIDDLE;
float DX_mouseX = 0.0f, DX_mouseY = 0.0f;

int DX_DELAY_ANALOG = 0;


#define VIBRATE_LEFT(speed, time)  { if(VIBRATE_FUNCTION){DX_vibration.wLeftMotorSpeed = speed; vibrate_time = (int)TimerGetTime() + time;} }
#define VIBRATE_RIGHT(speed, time)  { if(VIBRATE_FUNCTION){DX_vibration.wRightMotorSpeed  = speed; vibrate_time = (int)TimerGetTime() + time;} }
#define MAKE_BUTTON(row, loop, id)  { if(row >= 0 && row < 10 && loop >= 0 && loop < TOTAL_NO_SPRITES){DXTSI[row][DX_TITLE_BUTTONS_COUNT[row]]=loop;DX_TITLE_BUTTONS_ID[row][DX_TITLE_BUTTONS_COUNT[row]] = id;DX_TITLE_BUTTONS_X[row][DX_TITLE_BUTTONS_COUNT[row]] = sprite[loop].w+sprite[loop].box_width/2; DX_TITLE_BUTTONS_Y[row][DX_TITLE_BUTTONS_COUNT[row]] = sprite[loop].z+sprite[loop].box_height/2;if(DX_TITLE_BUTTONS_COUNT[row]<31)DX_TITLE_BUTTONS_COUNT[row]++;} }



bool DX_MENU_CHANGED = false;

float DX_LX = 0.0f; 
float DX_LY = 0.0f;
float DX_SOFT_LX = 0.0f; 
float DX_SOFT_LY = 0.0f;
float DX_WALK_LX = 0.0f; 
float DX_L_MAGNITUDE = 0.0f;

float DX_RX = 0.0f;
float DX_RY = 0.0f;
float DX_R_MAGNITUDE = 0.0f;

#define BUTTON_DEFAULT  0
#define BUTTON_PRESS    1
#define BUTTON_HELD     2
#define BUTTON_RESET    3

int DX_KEY_A = BUTTON_DEFAULT; 
int DX_KEY_B = BUTTON_DEFAULT; 
int DX_KEY_X = BUTTON_DEFAULT; 
int DX_KEY_Y = BUTTON_DEFAULT; 

int DX_KEY_UP    = BUTTON_DEFAULT; 
int DX_KEY_DOWN  = BUTTON_DEFAULT; 
int DX_KEY_LEFT  = BUTTON_DEFAULT; 
int DX_KEY_RIGHT = BUTTON_DEFAULT; 

int DX_KEY_LTRIG = BUTTON_DEFAULT; 
int DX_KEY_RTRIG = BUTTON_DEFAULT; 
int DX_KEY_LSHLD = BUTTON_DEFAULT;  
int DX_KEY_RSHLD = BUTTON_DEFAULT; 

int DX_KEY_LTHUMB = BUTTON_DEFAULT;  
int DX_KEY_RTHUMB = BUTTON_DEFAULT;  

int DX_KEY_START = BUTTON_DEFAULT; 
int DX_KEY_BACK  = BUTTON_DEFAULT; 

int DX_LTHUMB_UP   = BUTTON_DEFAULT;  
int DX_LTHUMB_DOWN = BUTTON_DEFAULT;

int DX_LTHUMB_LEFT   = BUTTON_DEFAULT;  
int DX_LTHUMB_RIGHT  = BUTTON_DEFAULT;

bool DX_GRENADE_KEY = false;
bool DX_TRAP_KEY    = false;

bool DX_WEAPON1 = false;
bool DX_WEAPON2 = false;
bool DX_WEAPON3 = false;
bool DX_WEAPON4 = false;
 
bool DX_KNIFE = false;

bool DX_BACK = false;

bool DX_MAP = false;

bool DX_BACK_BUTTON = false;

bool DX_UP   = false;
bool DX_DOWN = false;
bool DX_LEFT   = false;
bool DX_RIGHT = false; 

bool DX_LEFTSHLDR   = false;
bool DX_RIGHTSHLDR  = false; 

bool DX_SHOOT = false;
bool DX_RELOAD = false;

bool DX_USECOLLECT = false; 

bool DX_INV_LEFTCLICK  = false;
bool DX_INV_RIGHTCLICK = false;
    
bool DX_PAUSED = false;

bool DX_INV_ACTIVE = false;
bool DX_MAP_ACTIVE = false;

int DXsprite_overlay=-1;
int DXTalk_Man=-1;
int DXPick_Up=-1;
bool DXJustCollected=false;

int CHANGE_SONG_SPEED = 0;

int DX_CURRENT_MESSAGE_BUTTON=0;

int DX_TITLE_BUTTON_DELAY=0; 

bool DX_ON_TARGET = false;

float DXmouseX=0.0f;
float DXmouseY=0.0f;

float DXTarMouseX=0.0f;
float DXTarMouseY=0.0f;

float DXAccel=0.0f;

int VG_CHARACTER_LOCKS[12];
 
 

// ****************** //   
#ifndef DREAMCAST
#define SCREEN_WIDTH  1280    
#define SCREEN_HEIGHT 720
#else
#define SCREEN_WIDTH  640    
#define SCREEN_HEIGHT 480
#endif
#define SCREEN_BITS   32  
  
float ZOOM_AMOUNT = 1.0;  
#define ASPECT_RATIO 0.75 

bool KEY_SPACE     = false;


bool space_is_held=false; 


float render_bg=0.0f; 
int render_sequence=0;   

#ifndef DREAMCAST
int MAX_horizontal = 1280;  
int MAX_vertical   = 720; 
#else
int MAX_horizontal = 640;  
int MAX_vertical   = 480; 
#endif

#define SCREEN_NORMAL            0   
#define SCREEN_WIDESCREEN        1 
#define SCREEN_1610_WIDESCREEN   2 
#define SCREEN_169_WIDESCREEN    3 

#ifndef DREAMCAST
int screen_mode = SCREEN_169_WIDESCREEN;  
#else
int screen_mode = SCREEN_NORMAL;  
#endif      

int sc_render_rate = RENDER_RATE;

int saved_window_posX = 0; 
int saved_window_posY = 0;

int fade_timer = 0;

int double_main_code = 0;

int new_renderer=0;
int new_sc_width=SCREEN_WIDTH;
int new_sc_height=SCREEN_HEIGHT;
bool sc_blur = false;

int title_sequence = 0;
int start_sequence = 0;
int start_sequence1 = 0;

int title_timer = 0;     

float temp_music_volume = 0.0;
float temp_sfx_volume   = 0.0;

float fade_in_volume  = 0.0;
float fade_out_volume = 0.0;
float fade_increment  = 0.0;

int VG_1_JAE_DEFLECT_TIMER = 0;
int VG_2_JAE_DEFLECT_TIMER = 0;


bool music_fade = false; 

bool stop_music = false;

float global_u=0.0, global_u1=0.0;
float global_v=0.0, global_v1=0.0;

#define LIMIT_ANIMS 256      
#define LIMIT_FRAMES 256 
#define LIMIT_TEXTS 30
#define LIMIT_TEXT_FRAMES 30 
#define NODE_LIMIT 200  

// ANIMATION DEFINE'S 

#define WAIT     0
#define PLAY     1
#define LOOP     2
#define NO_ANIM  3
#define ONCE     4
#define FADE_IN  5
#define FADE_OUT 6
#define RESET_MUSIC 7

// Front-End Define's

#define NEW_GAME 0
#define OPTIONS  1
#define QUIT_GAME 2

// Front-End Define's

#define FE_NON     0
#define FE_NEW     1
#define FE_OPT     2
#define FE_SECRET  3
#define FE_END     4
#define FE_LOAD    5
#define FE_SCROLL  6
#define FE_FILE    7
#define FE_BACK1   8
#define FE_SINGLE  9
#define FE_MULTI   10
#define FE_MOVE    11
#define FE_DELETE  13
#define FE_OPTIONS 14
#define FE_GFX     15 
#define FE_START   16
#define FE_ACCEPT  17
#define FE_DECLINE 18
#define FE_RIFLE   19
#define FE_SHOTGUN   20
#define FE_MGUN    21
#define FE_TEXT    22
#define FE_CREATE  23
#define FE_FILE_CREATE 24
#define FE_FILE_DELETE 25
#define FE_BACK    26
#define FE_DUCK    27
#define FE_BULLETHOLE  28
#define FE_LOGO    29
#define FE_MUSIC   30
#define FE_SFX     31
#define FE_OPTION_CREATE 32
#define FE_CARD    33
#define FE_HIT     34
#define FE_STICK   35
#define FE_INCREASE 36
#define FE_DECREASE 37
#define FE_CREDITS  38
#define FE_TARGET   39 
#define FE_SHOOTABLE 40
#define FE_VERSION  41 
#define FE_FLIP     42
#define FE_SKIP     43
#define FE_MKEYBOARD 44
#define FE_MONLY     45
#define FE_VERSION1  47
#define FE_EASY      48
#define FE_NORMAL    49
#define FE_HARD      50
#define FE_GREENLIGHT  51
#define FE_KICKSTARTER 52
#define FE_HOST      53
#define FE_JOIN      54
#define FE_LAUNCH    55
#define FE_LAUNCH_GAME 57
#define FE_MAP       58
#define FE_TIME      59 
#define FE_KILLS     60   
#define FE_NET_P1    61 
#define FE_NET_P2    62 
#define FE_NET_P3    63
#define FE_NET_P4    64
#define FE_RADAR     65
#define FE_WEAPONS   66
#define FE_MKEYBOARD1 67
#define FE_DOUBLE     68
#define FE_TREBLE     69

#define FE_TYPE1      70
#define FE_TYPE2      71
#define FE_TYPE3      72
#define FE_TYPE4      73
#define FE_TYPE5      74
#define FE_TYPE6      75
#define FE_TYPE7      76
#define FE_TYPE8      77
#define FE_TYPE9      78


// Looping Music

#define SND_NON      0
#define SND_END      1 
#define SND_JET      2
#define SND_WAR      3
#define SND_LND      4 
#define SND_CRD      5
#define SND_ARMY     6 
#define SND_FIGHT    7
#define SND_SAD      8
#define SND_DGNB     9
#define SND_FINAL    10
#define SND_DANGERS  11
#define SND_INTRO    12
#define SND_FANFARE  13
#define SND_URGENCY  14
#define SND_MINI     15
#define SND_FANFARE2 16
#define SND_DEATH    17
#define SND_SIEGE    18 
#define SND_THEATRE  19 
#define SND_DANGER   20
#define SND_CREDITS  21
#define SND_SHO      22
#define SND_SAIZO    23
#define SND_TIA      24

int current_song = 0;
int old_song = 0;
int old_music_loop = 0;
bool continue_song = false; 

bool half_volume=false;

#define SONG_NONE     0
#define SONG_END      1 
#define SONG_JET      2
#define SONG_WAR      3
#define SONG_LND      4
#define SONG_CRD      5
#define SONG_ARMY     6
#define SONG_FIGHT    7
#define SONG_SAD      8
#define SONG_DGNB     9 
#define SONG_FINAL    10
#define SONG_DANGERS  11
#define SONG_INTRO    12
#define SONG_FANFARE  13
#define SONG_URGENCY  14 
#define SONG_MINI     15
#define SONG_FANFARE2 16
#define SONG_DEATH    17
#define SONG_SIEGE    18
#define SONG_THEATRE  19 
#define SONG_DANGER   20
#define SONG_CREDITS  21 
#define SONG_SHO      22
#define SONG_SAIZO    23
#define SONG_TIA      24

//HDC	 		hDC=NULL;		// Private GDI Device Context
//HGLRC		hRC=NULL;		// Permanent Rendering Context
//HWND		hWnd=NULL;		// Holds Our Window Handle
//HINSTANCE	hInstance;		// Holds The Instance Of The Application
  
//LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
 
struct animation_texture  
{ 
      float width, height;
#ifndef DREAMCAST
      int frames;
      int column;
      int no_of_anims;   
      int id;
      int anims[LIMIT_ANIMS][LIMIT_FRAMES]; // Space for five anims
      int delay[LIMIT_FRAMES];// Space for 100 frames 
      int anim_frames[LIMIT_FRAMES];
      int cur;    
      int rythm;  
#else
      short frames;
      short column;
      short no_of_anims;   
      short id;
      short** anims;
      short* delay;
      short* anim_frames;
      short cur;    
      short rythm;
      char loaded;
#endif  
};



struct object   
{
    float x,y;  // X/Y position of the rendered sprite
    float width, height; // Height/width of the rendered sprite
    float w,z; // used for collision box
    float box_width, box_height; // used for collision box
    float u[4], v[4];  // U-V co-ordinates
    int id;          // Texture id
    int cur;         // Current frame
    int fx_id;       // Which a_texture to use
    int frame;       // Used in DrawScene
    int anim;        // Which anim to play
    int cur_time;  // Animation delay
    int anim_state;  // Wait, Play or Loop
    bool mouseover;  // Is mouse over
    int score;       // This sprites total score
    bool grab_switch; // Grabbing variable
    float alpha;
    float light; 
    int linked_sprite; 
    bool moving; 
    int priority;
    int type;
    float angle;
    int fire_target;    
    int emy_shoot;
    bool emy_shooting; 
    int sector;  
    int sector_action;
    bool flash_target; 
    bool jumping;
    int heal_timer; // throwing_grenade
    int onCreate;
    int onCreate_action;
    int rank;
    int onDeath_action; 
    bool hit_opponent; 
    int reached_node;  
    int node_list[NODE_LIMIT];
    int node_count;
    int node_counter;  
    float kills;
    bool selected; 
    int status; 
    int all_timer;   
    int col_timer;
    int ai_timer;
    bool update; 
    int bomb_timer; 
    int global_flag; 
    int flash_timer;
    int dflash_timer;     
    bool death_flash;
    float mov_x, mov_y; 
    float shell_x, shell_y;
    float trans_x, trans_w;
    float end_x, end_y;
    float depth; 
    bool hit_by_bullet; 
    bool target_hole;
    int  special;
    bool turn_off;
    bool on_mud; 
    int movement;
    int base_anim;
    bool building;
    char flash_no_count;     
    bool mercy;
    int thrown_effect;
    char death_by_mud;
    float tar_angle;
    bool turning;
    bool bagging;
    int group_id; 
    int reload_timer;
    bool file_full;
    float factor;
    int grenaded; 
    int spotted_timer;
    bool spotted;
    int item_type; 
    int value;
    int value1;
    int value2; 
	int value3;  // Used for storing healthbar id
    float spin; 
    float distance; 
    float angle2;
    int action_timer;
    int tile_row; 
    int sparkle_timer;   
    bool splatted;  
    bool on_ladder;
    bool on_screen; 
   	int ai_brain;
    int ai_brain_timer;   
    bool return_fire;
	int idle_type;    
	int name;
	bool camo;
	int direction;
	int ducking;
	int duck_timer;
	int hit_direction;
	bool pain;
	bool knockdown;
	float knockdown_Y;
	float new_Z;
	int block_type;
	bool invulnerable;
	bool electrocute;
	bool handcuffed;
	bool walking_backwards;
	bool dizzy;
	bool sticky;
	bool is_a_pigeon;
	bool deflect;
	int cur_start_time;
	int cur_dest_time;
	bool was_knocked_down;
	float last_slowmo;
    bool bump_this;
	int  bump_this_timer;
	bool acid;
	bool strafe;
	bool spin_strafe;


};

struct a_point
{
    float x,y;
    int anim_state;
    int anim;
    int score;
    int active; // Grabbing variable
    float speed;
    int c1;
    int c2;
    int c3;
    int c4;
};

struct a_node
{
    float x,y;
    bool connect[8];
    float connect_dis[8];

};


struct font 
{
    float x,y;
	float w,z;
    float width, height;
    float box_width, box_height;
	float scroll;
    int id;
    char word[1024]; 
    float alpha;
    int length;
	bool greyed;
	bool right;
	bool scroll_this;
	int type;
}; 

struct sString 
{
 
    char string[256];      
       
};

struct sSFX
{
       
    float x;
    float y;
       
};

float Gvector[2] = { 0.0f, 0.0f };
float Gcolor[4]  = { 0.0f, 0.0f, 0.0f, 0.0f };
float Gtex[2]  = { 0.0f, 0.0f }; 

#define IDLE_NONE 0

#define NUMBER_OF_SUBMATERIALS 200

VG_LOW_RAM_BSS sString material[NUMBER_OF_SUBMATERIALS];

#define NO_PARAMS_PROG 25 

int no_of_params=0;
sString params_prog[NO_PARAMS_PROG]; 
 
bool create_option = false;

bool mouseright, mouseleft, mousemiddle, mouseheld;
int  mousewheel;
int no_sprites=0;
int no_fx=0;
int new_no_sprites=0;
int no_points=0;
int no_nodes=0;
int no_rows=0;
int no_columns=0;
int original_no_sprites=0;
int hud_no_sprites=0;

int texture_fx[200]; 
int animation_fx[200];

int selection=0;
int pt_selection=0;
int nde_selection=0;

int music_loop=SND_NON;


int AI_Time=0;
int Animate_Time=0;
int Real_Time=0;
int Net_Time=0; 
int Net_Read_Time=0; 
int Code_Time=0; 
int Key_Time=0;
int Steam_Time=0;
int Swap_Time=0;
int Stop_Time=0;
int Main_Time=0;
int Code_Start=0;   
int Key_Start=0;  
int Main_Start=0;
int Ai_cycle=0;
int Draw_cycle=0;
int Main_cycle=0;
int Peek_cycle=0;
int Swap_cycle=0;
int Total_cycle=0;
int Total_Start=0;
int Draw_Start=0;
bool quitting=false;
int quit_timer=0;
int music_reset=false;


float music_volume = 0.4f;
float sfx_volume   = 0.3f; 

bool update_title = false;

int mouse_held_state = 0;


int view_cone_timer = 0;



     
#define PAUSED_LIGHT_LEVEL 0.4

// Pause game stuff

int pause_timer=0;
float pause_timer_start=0.0f;
float timer_addition=0.0f;
bool game_paused = false;
bool pause_music=false;
int time_diff=0;  

// Global temps  
float ftemp=0.0;
int itemp=0;

int flash_timer=0;


int rendering=0;
int scene_shake = 0;



bool changed_video = false;
bool changed_renderer = false;

#define VK_BACK			1
#define VK_CAPITAL		2
#define VK_CONTROL		3
#define VK_DELETE		4
#define VK_UP			5
#define VK_DOWN			6
#define VK_LEFT			7
#define VK_RIGHT		8
#define VK_HOME			9
#define VK_END			10
#define VK_F1			11
#define VK_F2			12
#define VK_F3			13
#define VK_F4			14
#define VK_F5			15
#define VK_F6			16
#define VK_F7			17
#define VK_F8			18
#define VK_F9			19
#define VK_F10			20
#define VK_F11			21
#define VK_F12			22
#define VK_RETURN		23
#define VK_SHIFT		24
#define VK_TAB			25
#define VK_SPACE		26
#define VK_ESCAPE		27
#define VK_NEXT			28
#define VK_PRIOR		29
#define VK_PAUSE		30



     
int sc_width  = SCREEN_WIDTH;
int sc_height = SCREEN_HEIGHT;
int working_sc_width  = SCREEN_WIDTH;
int working_sc_height = SCREEN_HEIGHT;
int working_sc_bits   = SCREEN_BITS;
int sc_bits   = SCREEN_BITS;
float sc_ratio  = ASPECT_RATIO;
bool working_fullscreen=true;	// Fullscreen Flag Set To Fullscreen Mode By Default
      
float camX = 0.0f;
float camY = 0.0f; 

float old_camX = 0.0f;
float old_camY = 0.0f;

float new_camX = 0.0f;
float new_camY = 0.0f;

float camDistance=0.0;

float camX_OFFSET=0.0f, camY_OFFSET=0.0f;





    
float real_mouseX=0.0;
float real_mouseY=0.0;

float hud_mouseX=0.0;
float hud_mouseY=0.0;

int mouseheld_timer=0;
bool mouseleftcheck = false;
bool mousequickleft = false;



float hud27width   = 0.0;
float hud27height  = 0.0;
float hud1width    = 0.0;
float hud1height   = 0.0;


// defines for object.type

#define NON 0 // No collision
#define COL 1 // Collision
#define PLY 2 // Player
#define OBJ 3 // Object
#define DOR 4 // Door
#define BOD 5 // Body
#define SFE 6 // A Safe zone
#define TRI 7 // Trigger
#define BAR 8 // Barrel
#define SWI 9 // Switch
#define PKU 10 // Pick-Up
#define LAD 11 // Ladder
#define BIN 12 // Searchable - Bin
#define RCM 13 // Buddy
#define LVL 14 // End Level
#define GFX 15 // An effect
#define ZAP 16 // Stairs
#define LFT 17 // Lift
#define NDR 18 // New Door
#define GPU 19 // GFX pick-up
#define ALM 20 // Alarm trigger
#define CUT 21 // Cutscene
#define WIN 22 // Mine
#define QUE 23 // Question Mark
#define FLY 24 // Fly Machine
#define WTR 25 // Water
#define SAV 26 // Help Text
#define TEL 27 // Teleport
#define MOV 28 // Teleport
#define SCR 29 // Scroll texture
#define JBK 30 // Jump onto block
#define PNO 31 // No player walk_thru
#define RCK 32 // Breakable boulder
#define PSE 33 // No player walk_thru but can see graphic
#define OVR 34 // Overlay
#define BUD 35 // Buddy 
#define FLM 36 // Flame
#define STA 37 // Stairs
#define RKT 38 // Rocket 
#define MNE 39 // Mine
#define HLP 40 // Help Text
#define DWN 41 // Door that moves down
#define JMP 42 // Jump point
#define BAG 43 // Punching bag
#define BOX 44 // Box
#define BUT 45 // Button 
#define UNT 46 // Unit
#define SEL 47 // Unit
  
#define STANDARD   0
#define PLACEMENT  1
#define TEXTURE    2 
#define COLLISION  3 
#define CAMERA     4 
#define POINT_MODE 5
#define NODES      6
#define TILE_MODE  7

// FX states
#define FX_STATIC   0
#define FX_BULLET   1
#define FX_BULLET1  2
#define FX_FLOOR    3
#define FX_TELEPORT 4
#define FX_ROCKET   5
#define FX_PICKUP   6
#define FX_FLAMEOLD 7
#define FX_MINE     8
#define FX_EXPLODE  9
#define FX_CLOUD   10
#define FX_DUST    11
#define FX_EXCLAM  12
#define FX_HUH     13
#define FX_DOLLAR  14
#define FX_TIME    15
#define FX_LASER   16
#define FX_QBUB    17 // Question Mark
#define FX_POINTER 18 // Mouse Pointer
#define FX_SELECT  19
#define FX_RANK    20
#define FX_MUD     21
#define FX_SHADOW  22
#define FX_CHIP    23 
#define FX_SHELL   24
#define FX_BULLET_SHADOW  25 
#define FX_BLOOD   26
#define FX_GRENADE 27
#define FX_GRENADE_SHADOW 28
#define FX_FALLING_BOMB   29
#define FX_FRAG    30
#define FX_FRAG_SHADOW    31
#define FX_FIRE    32
#define FX_STAR    33
#define FX_ARTILLERY 34
#define FX_DECAL   35
#define FX_FIRE1   36
#define FX_GAS     37
#define FX_BARREL  38
#define FX_HEADSHOT 39
#define FX_SPLAT    40
#define FX_HEALTHBAR 41
#define FX_HEALTHBOX 42
#define FX_SPARKLE   43
#define FX_MUZZLE    44
#define FX_EXPLOSION 45
#define FX_STUNNED   46
#define FX_SCORE     47
#define FX_SCORE_SLOW     48
#define FX_HUNT_BULLET    49
#define FX_ALERT    50
#define FX_PUNCH_POINT  51
#define FX_VG_BULLET 52
#define FX_VG_BULLET_LOW 53
#define FX_VG_VIAL   54
#define FX_VG_VIAL_LOW   55
#define FX_VG_GRENADE   56
#define FX_VG_EXPLOSION   57
#define FX_ARM  58
#define FX_VG_CASING  59
#define FX_FLAME   60
#define FX_LEAF    61
#define FX_LEAF1   62
#define FX_RUBBISH    63
#define FX_RUBBISH1   64
#define FX_FLIP       65
#define FX_VG_KNIFE   66
#define FX_VG_BOMB    67
#define FX_VG_ATTACH  68
#define FX_VG_STICKYB  69
#define FX_VG_STICKYG  70
#define FX_VG_EXPLOSIONG 71
#define FX_VG_EXPLOSIONB 72
#define FX_VG_ATTACH_HANDCUFFS  73
#define FX_VG_TRAIL  74
#define FX_VG_TRAIL_SPRITE  75
#define FX_VG_MONEY  76

#define FX_VG_STICKYS  77
#define FX_VG_EXPLOSIONS 78

#define FX_VG_RAINDROP  79

#define FX_VG_ATTACH_ACID  80

#define FX_VG_SWEAT  81

#define FX_VG_ORB 82

#define FX_VG_FIREBALL 83

#define FX_VG_BOMBSAIZO 84
#define FX_VG_EXPLOSIONSAIZO 85

#define FX_VG_KUNAI 86

#define FX_VG_SWEAT2  87


#define LINE_OF_SIGHT  0.01

// SCENE VARIABLES 

bool done=false;
int numsubmtls = 0;									// Status Indicator
int scene = 0;
int episode = 0;
int old_scene=0;
int old_mode=0;




int mode = 0;
int var=0; // generic variable

int no_of_keyframes = 0;


float mouseX=0.0, mouseY=0.0;


bool quit_active=false;

#define G_NON   0
#define G_ACT   1
#define G_FGT   2
#define G_WLK   3
#define G_BLK   4
#define G_SHT   5
#define G_SGN   6
#define G_STS   7
#define G_ZIN   8
#define G_ZOT   9
#define G_SLI   10 // Sliding outside the sky-scraper
#define G_FLL   11 // Free falling mode
#define G_FLY   12 // Start as a fly
#define G_OLD   13 // Start as oldman

int g_type = G_NON;



// Player Animation System 
#define ANIM_NOT_WALKING 0
#define ANIM_WALKING     1

#define ANIM_SPRITE 0 
#define ANIM_HUD    1
#define ANIM_FX     2

#define INTERRUPT_OFF 0
#define INTERRUPT_ON  1

#define BULLET_CHECK_OFF 0
#define BULLET_CHECK_ON  1

#define PAIN_ANIM_OFF 0
#define PAIN_ANIM_ON  1

#define FIRE_OFF 0
#define FIRE_ON  1


// Fades
int fade_in=0; 
int fade_out=0;
int c_fade_in=0;
int c_fade_out=0;

float cos_fade=0.0;
float cos_scroll=0.0;

char string[256];

sString temp_string;


bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=true;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=true;	// Fullscreen Flag Set To Fullscreen Mode By Default
bool    debug_text=false;
bool    dump_debug;
bool    shift_key;
bool    animating=true;
bool    animate_sprites=true;
bool    next_scene=false;


bool    debug_active=false; 
 
#define RESET      0
#define UP         1
#define DOWN       2
#define LEFT       3
#define RIGHT      4
#define UP_RIGHT   5
#define UP_LEFT    6
#define DOWN_RIGHT 7
#define DOWN_LEFT  8
#define NO_MOVE    9
#define UP_SIDE    10
#define DOWN_SIDE  11


int start_timer=0;
int start_timer1=0;

int RES_Width[30];
int RES_Height[30];

bool RES_Available[30];

int VG_1_LEGS = 0;
int VG_2_LEGS = 0;


float desktop_ratio = 0.0f;


// GAME MODES

#define NORM  0
#define GAME  1
#define CINE  2
#define WALK  3
#define FRONT 4
#define WORLD 5
#define FIGHT 6

 
int  game_mode = NORM; // 0 = NONE, 1 = GAME, 2 = CINE
int  game_time = 0, game_score = 0;
int  game_timer=0;

#if defined SWITCH || defined DREAMCAST
GLenum src_one=GL_ONE_MINUS_DST_ALPHA;
GLenum src_two=GL_SRC_COLOR;
#endif



// Onscreen TEXT
int  text_timer=0;
bool text_active=false;

int scroll_txt_timer=0;
int scroll_index=0;
int scroll_length=0;
bool scroll_txt_active=false;

float precision = 0.015f;
float fade = 0.0f;
 
float zoom_factor=ZOOM_AMOUNT;
float org_zoom_factor=ZOOM_AMOUNT;

float org_zoom_scroll_amount=0.0f;

float org_zoom_scroll_display=0.0f;

#define SCROLL_SPEED 0.004


 
int flash_target=0;

FILE* fp2; // Error.log  
FILE* fp3; // Error.log 
FILE* fpd; // Debug.log     

#define MAX_FX_ID 75 
animation_texture a_texture[MAX_FX_ID]; // Space for fifty animated textures

short a_texture_get_anims_secondlayer(int id, int first, int second)
{
	if(a_texture[id].loaded == 0)
		return 0;

	if(first >= a_texture[id].no_of_anims)
		return 0;

	if(second >= a_texture[id].anim_frames[first])
		return 0;
	
	return a_texture[id].anims[first][second];
}

short a_texture_get_delay(int id, int delay)
{
	if(a_texture[id].loaded == 0)
		return 0;

	if(delay >= a_texture[id].frames)
		return 0;

	return a_texture[id].delay[delay];
}

short a_texture_get_animsframes(int id, int anims_frames)
{
	if(a_texture[id].loaded == 0)
		return 0;

	if(anims_frames >= a_texture[id].no_of_anims)
		return 0;

	return a_texture[id].anim_frames[anims_frames];
}

int g_fx_id=0;
int total_fx=0;     

#define TOTAL_NO_SPRITES    400        
#define TOTAL_NO_FX_SPRITES 350 
#define TOTAL_NO_POINTS     400 
#define TOTAL_NO_NODES      100  
//#define TOTAL_NO_FX         50 
#define TOTAL_NO_HUD        75 
#define TOTAL_PKU           30    

int sprite_list[1000];   
int var3[TOTAL_NO_SPRITES];
int var5[TOTAL_NO_SPRITES];  

int hours=0;
int minutes=0;
int seconds=0;


object *sprite;
 
object *Fx;

a_point points[TOTAL_NO_POINTS]; 
a_point nodes[TOTAL_NO_NODES];
      

object display; 
object sprite_copy; 

object *hud;



//object hud[TOTAL_NO_HUD];
int var4[TOTAL_NO_HUD];
int hud_list[TOTAL_NO_HUD];
    
#define TOTAL_TEXT 300     
VG_LOW_RAM_BSS font text[TOTAL_TEXT]; 
    
VG_LOW_RAM_BSS font counter[TOTAL_TEXT];

VG_LOW_RAM_BSS font new_counter[TOTAL_TEXT];

font display_font;
#if defined SWITCH || defined DREAMCAST
GLuint* texID=NULL;
#endif
 

float gallery_volume = 0.0f;
int music_timer = 0;


int end_sfx  =WAIT;
int jet_sfx  =WAIT; 
int war_sfx  =WAIT; 
int lnd_sfx  =WAIT; 
int crd_sfx  =WAIT;
int army_sfx =WAIT;   
int fight_sfx=WAIT;
int sad_sfx  =WAIT;
int dgnb_sfx  =WAIT; 
int final_sfx  =WAIT;
int dangers_sfx  =WAIT;
int intro_sfx  = WAIT;
int mini_sfx   = WAIT;
int urgency_sfx  = WAIT;
int fanfare_sfx  = WAIT;
int fanfare2_sfx  = WAIT;
int deathscreen_sfx  = WAIT;
int siege_sfx  = WAIT;
int theatre_sfx  = WAIT;
int credits_sfx  = WAIT;  
int sho_sfx  =WAIT;
int saizo_sfx  =WAIT;
int tia_sfx  =WAIT;


  
#endif
