#ifndef GLOBAL_H
#define GLOBAL_H

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include "globals.h"

#define LIMIT_ANIMS 10
#define LIMIT_FRAMES 100

// ANIMATION DEFINE'S

#define WAIT 0
#define PLAY 1
#define LOOP 2

struct animation_texture
{
      float width, height;
      int frames;
      int no_of_anims;
      int id;
      int anims[LIMIT_ANIMS][LIMIT_FRAMES]; // Space for five anims
      int delay[LIMIT_FRAMES];// Space for 100 frames 
      int anim_frames[LIMIT_FRAMES];
      int cur;    
      bool rythm;  
};

struct object
{
    float x,y;
    float width, height;
    float w,z;
    float box_width, box_height;
    float u[4],v[4];
    int id;          // Texture id
    int cur;         // Current frame
    int fx_id;       // Which a_texture to use
    int frame;       // Used in DrawScene
    int anim;        // Which anim to play
    float cur_time;  // Animation delay
    int anim_state;  // Wait, Play or Loop
    bool mouseover;  // Is mouse over
    int score;       // This sprites total score
    bool grab_switch; // Grabbing variable
};

struct font
{
    float x,y;
    float width, height;
    int id;
    char word[256];
};

struct sString
{
 
    char string[255];      
       
};
 
bool mouseright, mouseleft, mousemiddle;
int no_sprites=0;
int hud_no_sprites=0;
int texture_fx[50];
int animation_fx[50];
int selection=0;

int sc_width=1024;
int sc_height=768;
  
#define STANDARD 0
#define PLACEMENT 1
#define TEXTURE 2
#define COLLISION 3
 
// SCENE VARIABLES 
 
int numsubmtls = 0;									// Status Indicator
int scene = 0;
int scene_score=0;
int mode = 0;
int var=0; // generic variable
int cur_keyframe = 0;
int no_of_keyframes=5; // Number of keyframes in current scene
int target_frame=0;// next key_frame to animate to

// Fades
int fade_in=0;
int fade_out=0;

char string[256];

sString temp_string;

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
bool    debug_text=FALSE;
bool    dump_debug;
bool    shift_key;
bool    animating=FALSE;

bool    next_scene=FALSE;

// Grabbing Variables
bool mouse_grabbed=FALSE;

POINT mouse_point, grabbed_point;
float x_amount, y_amount;

#define RESET 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

int interface_X = RESET;
int interface_Y = RESET;

float rythm_delay = 1.0f;

#define DANGER_LOW 0
#define DANGER_MED 1
#define DANGER_HIGH 2
int danger_switch = DANGER_HIGH;

// GAME MODES

#define NORM 0
#define GAME 1
#define CINE 2

int  game_mode = NORM; // 0 = NONE, 1 = GAME, 2 = CINE
int  game_time = 0, game_score = 0;
int  game_timer=0;


// TOOL-BOX

#define GRAB 0
#define PINCH 1

int tool_cur=GRAB;


int hundred=0, ten=0, one=0;

GLfloat	xrot;				// X Rotation
GLfloat	yrot;				// Y Rotation

float precision = 0.015f;
float fade = 0.0f;
 
float zoom_factor=1.0;

FILE* fp2; // Error.log
FILE* fpd; // Debug.log

#define MAX_FX_ID 20
animation_texture a_texture[MAX_FX_ID]; // Space for ten animated textures
int g_fx_id=0;

object sprite[10];
object key_frames[5][10];
object display;

// Temporary
object hand;
object hud[10];
    
#define TOTAL_TEXT 20    
font text[TOTAL_TEXT];
    
font counter[5];

font display_font;

GLuint* texID;

#endif

