#ifndef __VG_GLOBAL_H__
#define __VG_GLOBAL_H__ 

#ifdef SWITCH
//#include <gl\gl.h>			// Header File For The OpenGL32 Library
#endif
#include "texture.h"               

// Verdict Guilty.... 

#define VG_CAT_IDLE   0
#define VG_CAT_LEFT   1
#define VG_CAT_RIGHT  2
#define VG_CAT_IDLE2  3

#define VG_BOTTOM_TEXT_OFFSET 0.11f;
#define VG_BOTTOM_OPTIONS_OFFSET -0.322f;

int VG_cat_AI = 0;
int VG_cat_AI_timer = 0;

int VG_1_Vs_wins = 0;
int VG_2_Vs_wins = 0;
int VG_Vs_draws = 0;

bool vg_continued_arcade = false;

int VG_1_Temp_perfects = 0;
int VG_2_Temp_perfects = 0;

int VG_1_Temp_arrests = 0;
int VG_2_Temp_arrests = 0;

int VG_1_CREDITS = 4;
int VG_2_CREDITS = 4;

int VG_1_BULLETS = 0;
int VG_2_BULLETS = 0;

int vg_next_scene    = -1; 
int vg_next_episode = -1;

int VG_flash_win_player = 0;
int VG_flash_win_timer = 0;
int VG_flash_win_timer_total = 0;

int VG_page_no = 0;

float VG_HIT_X = 0.0f;
float VG_HIT_Y = 0.0f;

float VG_SWEAT_X = 0.0f;
float VG_SWEAT_Y = 0.0f;
float VG_ANGLE_OF_ATTACK;

int VG_1_SELECT_ROWX = 0;
int VG_1_SELECT_ROWY = 0;

int VG_1_SELECTED = 0;

int VG_2_SELECT_ROWX = 0;
int VG_2_SELECT_ROWY = 0;

int VG_2_SELECTED = 0;

bool VG_PLAYER1_SELECTED = false;
bool VG_PLAYER2_SELECTED = false;

#define WIND_STOPPED   0
#define WIND_FAST      1
#define WIND_SLOW      2

int VG_1_HANDCUFFED_TIMER = 0;
int VG_2_HANDCUFFED_TIMER = 0;

int VG_1_ACID_TIMER = 0;
int VG_2_ACID_TIMER = 0;

int VG_1_DIZZY_TIMER = 0;
int VG_2_DIZZY_TIMER = 0;

int VG_1_STICKY_TIMER = 0;
int VG_2_STICKY_TIMER = 0;

int VG_WIND_BLOWING = WIND_STOPPED;
int VG_WIND_TIMER = 0;

bool VG_PLAYER1_WON = false;

int VG_1_vibrate_time = 0;
int VG_2_vibrate_time = 0;

float VG_PLAYERS_STARTY = -0.3440f;  

bool VG_PLAYER_1_PAUSED = false;

bool VG_IS_VERSUS_SCREEN = true;

int VG_insert_flash_timer = 0;
bool VG_insert_flash = false;

#define CS_NONE      0
#define CS_DANGER1   1
#define CS_DANGER2   2
#define CS_VICTORY   3
#define CS_ENDING    4
#define CS_BOSSIDLE  5
#define CS_IDLE      6

int VG_CS_SONG = CS_DANGER1;

bool VG_1_DX_UP = false;
bool VG_1_DX_DOWN = false;
bool VG_1_DX_LEFT = false;
bool VG_1_DX_RIGHT = false;
bool VG_1_SOFT_DX_LEFT = false;
bool VG_1_SOFT_DX_RIGHT = false;

bool VG_1_DX_A = false;
bool VG_1_DX_B = false;
bool VG_1_DX_X = false;
bool VG_1_DX_Y = false;

bool VG_1_DX_LS = false;
bool VG_1_DX_RS = false;

bool VG_1_DX_LT = false;
bool VG_1_DX_RT = false;

bool VG_1_DX_START = false;
bool VG_1_DX_BACK  = false;

bool VG_2_DX_UP = false;
bool VG_2_DX_DOWN = false;
bool VG_2_DX_LEFT = false;
bool VG_2_DX_RIGHT = false;
bool VG_2_SOFT_DX_LEFT = false;
bool VG_2_SOFT_DX_RIGHT = false;

bool VG_2_DX_A = false;
bool VG_2_DX_B = false;
bool VG_2_DX_X = false;
bool VG_2_DX_Y = false;

bool VG_2_DX_LS = false;
bool VG_2_DX_RS = false;

bool VG_2_DX_LT = false;
bool VG_2_DX_RT = false;

bool VG_2_DX_START = false;
bool VG_2_DX_BACK  = false;


bool VG_1_ARM_LENGTH = false;
bool VG_2_ARM_LENGTH = false;

int VG_SHEET_ANIM = 0;

bool VG_displaying_win = false;

bool VG_HUD_ESC = false;

bool VG_1_HUDDOWN = false;
bool VG_1_HUDUP = false;
bool VG_1_HUDLEFT = false;
bool VG_1_HUDRIGHT = false;

bool VG_2_HUDDOWN = false;
bool VG_2_HUDUP = false;
bool VG_2_HUDLEFT = false;
bool VG_2_HUDRIGHT = false;

bool VG_1_HUD_GO   = false;
bool VG_1_HUD_BACK = false;

bool VG_2_HUD_GO   = false;
bool VG_2_HUD_BACK = false;

char VG_P1_UP_KEY_DSY;
char VG_P1_DOWN_KEY_DSY;
char VG_P1_LEFT_KEY_DSY;
char VG_P1_RIGHT_KEY_DSY;

char VG_P1_PUNCH1_KEY_DSY;
char VG_P1_PUNCH2_KEY_DSY;
char VG_P1_KICK1_KEY_DSY;
char VG_P1_KICK2_KEY_DSY;

char VG_P2_UP_KEY_DSY;
char VG_P2_DOWN_KEY_DSY;
char VG_P2_LEFT_KEY_DSY;
char VG_P2_RIGHT_KEY_DSY;

char VG_P2_PUNCH1_KEY_DSY;
char VG_P2_PUNCH2_KEY_DSY;
char VG_P2_KICK1_KEY_DSY;
char VG_P2_KICK2_KEY_DSY;

char VG_P1_BLOCK_KEY_DSY;
char VG_P1_THROW_KEY_DSY;
char VG_P2_BLOCK_KEY_DSY;
char VG_P2_THROW_KEY_DSY;
 
int VG_P1_UP_KEY;
int VG_P1_DOWN_KEY; 
int VG_P1_LEFT_KEY;
int VG_P1_RIGHT_KEY;

int VG_P1_PUNCH1_KEY;
int VG_P1_PUNCH2_KEY;
int VG_P1_KICK1_KEY;
int VG_P1_KICK2_KEY;

int VG_P1_THROW_KEY;
int VG_P1_BLOCK_KEY;

int VG_P2_UP_KEY;
int VG_P2_DOWN_KEY; 
int VG_P2_LEFT_KEY;
int VG_P2_RIGHT_KEY;

int VG_P2_PUNCH1_KEY;
int VG_P2_PUNCH2_KEY;
int VG_P2_KICK1_KEY;
int VG_P2_KICK2_KEY;

int VG_P2_THROW_KEY;
int VG_P2_BLOCK_KEY;

bool VG_P2_AI_UP_KEY = false;
bool VG_P2_AI_DOWN_KEY = false; 
bool VG_P2_AI_LEFT_KEY = false;
bool VG_P2_AI_RIGHT_KEY = false;

bool VG_P2_AI_PUNCH1_KEY = false;
bool VG_P2_AI_PUNCH2_KEY = false;
bool VG_P2_AI_KICK1_KEY = false;
bool VG_P2_AI_KICK2_KEY = false;

bool VG_P2_AI_THROW_KEY = false;
bool VG_P2_AI_BLOCK_KEY = false;

bool VG_1_display_hit = false;
bool VG_2_display_hit = false;

bool VG_define_P1_keys = false;

#define VG_VS_HIGH_HEALTH 2000

int VG_VS_TIME   = 0;
int VG_VS_HEALTH = 0;
int VG_VS_BG     = 0;

int VG_INTRO_DOG1 = 0;
int VG_INTRO_DOG2 = 0;

int VG_1_display_hit_timer = 0;
int VG_2_display_hit_timer = 0;

int VG_1_hits = 0;
int VG_2_hits = 0;

int VG_1_hits_timer = 0;
int VG_2_hits_timer = 0;

int VG_Flicker_HUD_Button_timer = 0;

int VG_1_WINS = 0;
int VG_2_WINS = 0;

int VG_SELECTED = 0;

int VG_ROUND = 1;

#define VG_BLOCK_NONE  0 
#define VG_BLOCK_MID   1 
#define VG_BLOCK_LOW   2 

float VG_1_BOXHEIGHT = 0.0f;
float VG_2_BOXHEIGHT = 0.0f; 

bool VG_Display_moves=false;

int VG_health_move_timer = 0;

#define STARTING_HEALTH  1000

int VG_1_HEALTH = STARTING_HEALTH;
int VG_2_HEALTH = STARTING_HEALTH; 
 
int VG_1_TOTALHEALTH = STARTING_HEALTH;
int VG_2_TOTALHEALTH = STARTING_HEALTH; 

float VG_1_NEWHEALTH = 1500.0f; 
float VG_2_NEWHEALTH = 1500.0f; 
 
float screen_limit = 1.1f;
float VG_BG_LAYER_STARTX = 0.0f;


bool VG_FLICKER = false;

float VG_SCREEN_EDGE = 0.75f; // 0.65f

bool VG_DONT_MOVE_CAMERA = false;

int VG_1_HANDCUFFED = 0;
int VG_2_HANDCUFFED = 0;

int VG_SHAKE_timer=0;
bool VG_SHAKE_LEFT = false; 


float VG_SCREEN_X = 0.0f;
float VG_LAYER1_X = 0.0f;  
float VG_START_Y = 0.0f;
float VG_JUMP_HEIGHT = 0.4f;
float VG_VIAL_HEIGHT = 0.36f;
float VG_VIAL_LOW_HEIGHT = 0.12f;
float VG_GRENADE_HEIGHT = 0.09f;
float VG_KNIFE_HEIGHT = 0.26f;
         
int VG_RESET_key_timer=0;            


int VG_1_cur = 0;
int VG_2_cur = 0;

int VG_rnd = 0;

#define VG_NORMAL   0
#define VG_VERSUS   1

int VG_DEFEATED_GUYS[15]; 
int vg_defeat_count = 0;

int VG_BATTLE_ROUND = 1;

int VG_AI_SPECIALS_TIMER = 0;
 
int VG_NEXT_FIGHTER = 0;
int vg_mode = VG_NORMAL;
bool vg_selected_character = false;

int vg_train_timer=0;
float train_startX=0.0f, train_start1X = 0.0f;

bool VG_change_pitch = false;
bool VG_changed_pitch = false;
float VG_pitch = 1.0f;

int VG_played_title = -1;

int VG_1_hits_total = 0;
int VG_2_hits_total = 0;

int VG_TRAINER_HEALTH = 1000;

bool VG_BEAT_THE_GAME = false;

int VG_SUBBOSS = 0;

#define VG_GYEONG   0                 
#define VG_SIU      1                          
#define VG_MINSO    2      
#define VG_REESE    3                
#define VG_YOHAN    4                     
#define VG_JAE      5              
#define VG_GUN      6 
#define VG_HYUK     7  
#define VG_SHO      8
#define VG_TIA      9
#define VG_SAIZO    10
#define VG_KENNEDY  11
#define VG_SANG     12
#define VG_TRAINER  13


#define VG_TOYUN    14
#define VG_DAESU    15
#define VG_MIA      16
#define VG_BOB      17
#define VG_KONU     18
#define VG_SUNGKI   19
#define VG_SAPPORO  20
#define VG_YEJUN    21


#define VG_SHRINE   14


bool VG_CAR[3];
 
bool VG_TRAINING = false;

int VG_BACKGROUND = VG_JAE;    

int VG_1_CHARACTER = VG_JAE;
int VG_2_CHARACTER = VG_JAE;

char VG_1_NAME[1024];
char VG_2_NAME[1024];

#define VG_SOUND_NONE  0
#define VG_SOUND_CHOP  1
 
#define VG_KEYBOARD    0
#define VG_CONTROLLER  1 

#define COMBO_TIME 750 

int VG_P1_USING = VG_KEYBOARD;
int VG_P2_USING = VG_KEYBOARD;


bool VK_KEY_AI_SPECIAL1 = false;
bool VK_KEY_AI_COMBO = false;
bool VG_SKIP_INTRO = false;

#define VG_STRIKE_DELAY 1000

int VG_1_STRIKE_TIMER = 0;
int VG_2_STRIKE_TIMER = 0;

bool VG_play_pause_menu = false;

int VG_1_trail_timer = 0;
int VG_2_trail_timer = 0;

int VG_pause_button_timer=0;

int VG_DOG1_trail_timer = 0;
int VG_DOG2_trail_timer = 0;
 
bool VG_1_BLOCKING = false;
bool VG_2_BLOCKING = false;

#define VG_RESET   0
#define VG_PRESSED 1 
#define VG_HELD    2      
      
#define VG_HELD_SUPER_LENGTH 475    
#define VG_HELD_LENGTH 250         
#define VG_HELD_DIRECTIONS_LENGTH 350       
#define VG_RELEASE_LENGTH 12    
#define VG_WAIT_FOR_KEYS_LENGTH  85  
#define VG_WAIT_FOR_ACTION_LENGTH  15  
#define VG_COMBINE_LENGTH 100  
#define VG_COMBINE_LENGTH_THROW 200
#define VG_COMBINE_LONG_LENGTH 150 
#define VG_COMBINE_FAST_LENGTH 100 
#define VG_COMBINE_COMBO_LENGTH 1500
#define VG_COMBINE_COMBO_TOTALLENGTH 2000
#define VG_DASH_LENGTH 500

#define VG_SPECIAL_WAIT_LENGTH 400  
#define VG_SPECIAL_FIRST_LENGTH 100
#define VG_SPECIAL_LONG_LENGTH 3000  
#define VG_SPECIAL_BOTH_LENGTH 175


#define VG_LEFT_FONT  0
#define VG_RIGHT_FONT 1
#define VG_UP_FONT    2
#define VG_DOWN_FONT  3
#define VG_PUNCH_FONT 4
#define VG_KICK_FONT  5
#define VG_LEFT_FONT_H  6
#define VG_RIGHT_FONT_H 7
#define VG_UP_FONT_H    8
#define VG_DOWN_FONT_H  9
#define VG_PUNCH_FONT_H 10
#define VG_KICK_FONT_H  11

#define VG_KICK_AND_PUNCH_FONT   12

#define VG_LEFT_AND_PUNCH_FONT   13
#define VG_RIGHT_AND_PUNCH_FONT  14
#define VG_LEFT_AND_KICK_FONT    15
#define VG_RIGHT_AND_KICK_FONT   16

#define VG_DOWN_AND_KICK_FONT    17
#define VG_UP_AND_KICK_FONT      18
#define VG_DOWN_AND_PUNCH_FONT   19
#define VG_UP_AND_PUNCH_FONT     20

#define VG_DOWNLEFT_FONT   21
#define VG_DOWNRIGHT_FONT  22
#define VG_UPLEFT_FONT     23
#define VG_UPRIGHT_FONT    24

#define VG_DOWNLEFT_AND_KICK_FONT    25  
#define VG_DOWNRIGHT_AND_KICK_FONT   26
#define VG_DOWNLEFT_AND_PUNCH_FONT   27
#define VG_DOWNRIGHT_AND_PUNCH_FONT  28

#define VG_LEFT_AND_PUNCH_AND_KICK_FONT    29
#define VG_RIGHT_AND_PUNCH_AND_KICK_FONT   30

#define VG_UPLEFT_AND_KICK_FONT    32   
#define VG_UPRIGHT_AND_KICK_FONT   33
#define VG_UPLEFT_AND_PUNCH_FONT   34
#define VG_UPRIGHT_AND_PUNCH_FONT  35

#define VG_HIT_IN_FACE_FONT 36
#define VG_HIT_IN_BODY_FONT 37
#define VG_HIT_IN_CLOSE_FONT 38

#define VG_PUNCH_SHORT_FONT 39
#define VG_KICK_SHORT_FONT  40

#define VG_PUNCH_MEDIUM_FONT 41
#define VG_KICK_MEDIUM_FONT  42

#define VG_PUNCH_LONG_FONT 43
#define VG_KICK_LONG_FONT  44

#define VG_PUNCH2_FONT 45
#define VG_KICK2_FONT  46
#define VG_PUNCH2_FONT_H 47
#define VG_KICK2_FONT_H  48

#define VG_KNOCKDOWN_FONT  49
#define VG_KNOCKSLIDE_FONT 50

#define VG_JUMPING_PUNCH_FONT 51
#define VG_JUMPING_KICK_FONT  52

#define VG_BLOCK_FONT      53
#define VG_BLOCKDOWN_FONT  54

#define VG_LOW_PUNCH_FONT  55
#define VG_LOW_KICK_FONT   56
#define VG_LOW_KICK2_FONT  57

#define VG_LOW_PUNCH_SHORT_FONT 58
#define VG_LOW_KICK_SHORT_FONT  59

#define VG_SPECIAL1_FONT  60
#define VG_SPECIAL2_FONT  61
#define VG_SPECIAL3_FONT  62
#define VG_SPECIAL4_FONT  63
#define VG_SPECIAL5_FONT  64
#define VG_SPECIAL6_FONT  65

#define VG_AI_SPECIAL1_FONT  66
#define VG_AI_SPECIAL2_FONT  67
#define VG_AI_SPECIAL3_FONT  68
#define VG_AI_SPECIAL4_FONT  69
#define VG_AI_SPECIAL5_FONT  70
#define VG_AI_SPECIAL6_FONT  71

#define VG_BULLET_MID  72
#define VG_BULLET_LOW  73

#define VG_RELOAD_FONT  74

#define VG_JUMPING_PUNCH_SHORT_FONT 75
#define VG_JUMPING_KICK_SHORT_FONT  76

#define VG_KICK_KNEE_FONT  78
#define VG_UPPERCUT_FONT   79

#define VG_LOW_PUNCH2_FONT  80

#define VG_DOG_ATTACK 81

#define VG_VIAL_MID  82
#define VG_VIAL_LOW  83

#define VG_GRENADE  84
 
#define VG_EXPLOSION  85

#define VG_FORCEFIELD  86

#define VG_COMBO1      87
#define VG_COMBO2      88

#define VG_SECOND_STRIKE  89
#define VG_THIRD_STRIKE   90

#define VG_KICK_POWER_FONT  91 

#define VG_BLOCKSTAND_FONT  92
#define VG_BLOCKSTANDDOWN_FONT   93

#define VG_BREAKDANCE_FONT   94

#define VG_KNIFE  95

#define VG_THROW_FONT  96

#define VG_STICKY_BOMB     97
#define VG_STICKY_GRENADE  98

#define VG_PIGEON_ATTACK   99

#define VG_AI_COMBO_FONT   100

#define VG_PANTY_SHOT  101

#define VG_STICKY_SUICIDE  102

#define VG_LANDED_FONT  103
#define VG_GETUP_FONT   104

#define VG_PUNCH_CLOSE_FONT 105
#define VG_KICK_CLOSE_FONT  106

#define VG_BULLET_ORB  107

#define VG_EXPLOSIONSAIZO  108

bool VG_MOVES_VS = false;


int VG_1_THROW_TIMER = 0;
int VG_2_THROW_TIMER = 0;

bool VG_1_THROWING = false;
bool VG_2_THROWING = false;

int VG_1_THROWING_SEQUENCE = 0;
int VG_2_THROWING_SEQUENCE = 0;

bool VG_1_HAS_THROW = false;
bool VG_2_HAS_THROW = false;


// Damage values...
#define VG_KNEE_DAMAGE 60 
#define VG_PUNCH_DAMAGE 80
#define VG_STRECTCH_ARMS_DAMAGE 120  
#define VG_SPECIAL1_DAMAGE 240  
#define VG_PISTOL1_DAMAGE 150
#define VG_UPPERCUT_DAMAGE 160 
#define VG_DOG_DAMAGE 100
#define VG_VIAL_DAMAGE 180 
#define VG_GRENADE_DAMAGE 240 
#define VG_ELECTRIC_DAMAGE 380
#define VG_MGUN_DAMAGE 75 
#define VG_POWER_DAMAGE 160
#define VG_DANCE_DAMAGE 220
#define VG_MAGNUM_DAMAGE 200
#define VG_KNIFE_DAMAGE 200
#define VG_COP_THROW_DAMAGE 140
#define VG_CRIME_THROW_DAMAGE 220 
#define VG_WEAK_THROW_DAMAGE 120
#define VG_STICKYBOMB_DAMAGE 400
#define VG_STICKYSUICIDE_DAMAGE 750
#define VG_PUNCH_CLOSE_DAMAGE 60
#define VG_KICK_CLOSE_DAMAGE 80
#define VG_PANTYSHOT_DAMAGE 220 
#define VG_ORB_DAMAGE 175
#define VG_FIREBALL_DAMAGE 120
#define VG_EXPLOSIONSAIZO_DAMAGE 100
#define VG_KUNAI_DAMAGE 120
#define VG_KENNEDY_THROW_DAMAGE 300

#define VG_STORY_SPECIAL1_DAMAGE 340   
#define VG_STORY_THROW_DAMAGE 300
#define VG_STORY_PISTOL_DAMAGE 340
#define VG_STORY_MGUN_DAMAGE 125
#define VG_STORY_UZI_DAMAGE  175  
#define VG_STORY_DANCE_DAMAGE 550
#define VG_STORY_ELECTRIC_DAMAGE 550
#define VG_STORY_CLOTHESLINE_DAMAGE 340
#define VG_STORY_PIGEON_DAMAGE 340
#define VG_STORY_PISTOL_SIU_DAMAGE 240
#define VG_STORY_VIAL_DAMAGE 240
#define VG_STORY_MINE_DAMAGE 550
#define VG_STORY_STICKYBOMB_DAMAGE 900
#define VG_SANG_MGUN_DAMAGE 80
#define VG_STORY_COMBO_DAMAGE 350
#define VG_STORY_COMBOX_DAMAGE 400
#define VG_STORY_COMBO_SIU_DAMAGE 125
#define VG_STORY_COMBO_REESE_DAMAGE 150
#define VG_STORY_COMBO_YOHAN_DAMAGE 250
#define VG_STORY_GRENADE_DAMAGE 420



bool VG_1_DEFEATED_BY_BOMB = false;
bool VG_2_DEFEATED_BY_BOMB = false;

bool VG_SHAKE_CAMERA = false;
int VG_SHAKE_UP = 0;
int VG_SHAKE_CAMERA_LENGTH = 0;
int VG_shake_timer = 0;
int VG_shake_length_timer = 0;
float VG_shake_strength = 0.0f;


bool VG_1_WAS_ARRESTED = false;
bool VG_2_WAS_ARRESTED = false;


int VG_KOED_CHARACTER=0;

int VG_start_timer = 0;

int VG_map_last_point = 0;
int VG_map_next_point = 0;

bool VG_SHAKE_1 = false;
bool VG_SHAKE_2 = false;

bool VG_1_CORNERED = false;
bool VG_2_CORNERED = false;


bool VG_1_DOG_ACTIVE = false;
bool VG_2_DOG_ACTIVE = false;

bool VG_finished_round = false;

bool VG_1_DEFEATED = false;
bool VG_2_DEFEATED = false;

int VG_1_JUMPBOX = 0;
int VG_2_JUMPBOX = 0;

float VG_SPEED = 0.0f;

bool TEST_POINTS = false;

bool VG_AI_active = false;
int VG_Current_AI = 0;
int VG_AI_timer = 0;
int VG_Current_AI_MOVE = 0;
int VG_AI_MOVE_timer = 0;
int VG_AI_AVOID_timer = 0;

float VG_1_OFFSET = 0.0f;
float VG_2_OFFSET = 0.0f;
bool VG_update_OFFSET = false;

bool VG_SLOWMO = false;
float VG_slowmof = 1.0f;
int VG_slowmo_timer = 0;

bool VG_1_MOVE_ACTIVE = false;
bool VG_2_MOVE_ACTIVE = false;

#define AI_LOW   0
#define AI_MID   1
#define AI_HI    2

int VG_AI_DIFFICULTY = AI_LOW;

int VG_1st = 0;
int VG_2nd = 0;
int VG_3rd = 0;
int VG_4th = 0;
int VG_5th = 0;
 
int VG_1_current_timestamp=0;
bool VG_1_update_dump=false;

int VG_2_current_timestamp=0; 
bool VG_2_update_dump=false;

#define MOVES_LIMIT 750

int VG_1_Firststrike_timestamp = 0;
int VG_2_Firststrike_timestamp = 0;

bool VG_1_Firststrike = false;
bool VG_2_Firststrike = false;

int VG_1_perfects[10];
int VG_2_perfects[10];

int VG_1_arrests[10];
int VG_2_arrests[10];

int VG_arcade_sequence = 0;

int VG_1_perfect_count = 0;
int VG_2_perfect_count = 0;

int VG_1_arrests_count = 0;
int VG_2_arrests_count = 0;

int VG_1_TOTAL_MINS = 0;
int VG_1_TOTAL_SECS = 0;

int VG_1_TOTAL_perfects = 0;
int VG_2_TOTAL_perfects = 0;

int VG_FINAL_SCORE = 101;

int VG_1_TOTAL_arrests = 0;
int VG_2_TOTAL_arrests = 0;

int VG_1_WaitForKeys = 0;
int VG_2_WaitForKeys = 0;

int VG_1_MovesList_timer=0;
int VG_1_MovesList[MOVES_LIMIT];  
int VG_1_MovesList_timestamp[MOVES_LIMIT];
int VG_1_MovesList_count=0;

int VG_2_MovesList_timer=0;
int VG_2_MovesList[MOVES_LIMIT];  
int VG_2_MovesList_timestamp[MOVES_LIMIT];
int VG_2_MovesList_count=0;

int VG_1_Moves[MOVES_LIMIT];  
int VG_1_Moves_timestamp[MOVES_LIMIT];
int VG_1_Moves_count=0;
int VG_1_Moves_timer=0;

int VG_2_Moves[MOVES_LIMIT];
int VG_2_Moves_timestamp[MOVES_LIMIT];
int VG_2_Moves_count=0;
int VG_2_Moves_timer=0;


bool VG_1_LEFT_pressed  = false; 
bool VG_1_RIGHT_pressed = false; 
bool VG_1_UP_pressed = false; 
bool VG_1_DOWN_pressed = false; 

int VG_1_UP_timer = 0;
int VG_1_UP = 0;
int VG_1_DOWN_timer = 0;
int VG_1_DOWN = 0;
int VG_1_LEFT_timer = 0;
int VG_1_LEFT = 0;
int VG_1_RIGHT_timer = 0;
int VG_1_RIGHT = 0;

int VG_1_PUNCH_release = 0;
int VG_1_PUNCH_timer = 0;
int VG_1_PUNCH = 0;
int VG_1_PUNCH2_release = 0;
int VG_1_PUNCH2_timer = 0;
int VG_1_PUNCH2 = 0;

int VG_1_KICK_release = 0;
int VG_1_KICK_timer = 0;
int VG_1_KICK = 0;
int VG_1_KICK2_release = 0;
int VG_1_KICK2_timer = 0;
int VG_1_KICK2 = 0;

int VG_1_BLOCK_release = 0;
int VG_1_BLOCK_timer = 0;
int VG_1_BLOCK = 0;

int VG_1_THROW_release = 0;
int VG_1_THROW_timer = 0;
int VG_1_THROW = 0;
int VG_1_THROW_COOLDOWN = 0;

bool VG_2_LEFT_pressed  = false; 
bool VG_2_RIGHT_pressed = false; 
bool VG_2_UP_pressed = false; 
bool VG_2_DOWN_pressed = false;

bool VG_HIRES_BACKGROUNDS = false;


#define VG_ARCADE_MODE   0
#define VG_VERSUS_MODE   1
#define VG_STORY_MODE    2
#define VG_TRAINING_MODE 3

#define CONDITION_NONE          0
#define CONDITION_NO_SPECIALS   1
#define CONDITION_TIMED         2
#define CONDITION_SPECIAL1_ONLY 3
#define CONDITION_SPECIAL2_ONLY 4
#define CONDITION_MUST_WASTE    5
#define CONDITION_MUST_ARREST   6
#define CONDITION_THROWS_ONLY   7
#define CONDITION_SURVIVE       8
#define CONDITION_BASIC_ONLY    9
#define CONDITION_BASIC_BOTH    10
#define CONDITION_TIMED_BASIC   11
#define CONDITION_LOW_HEALTH    12
#define CONDITION_ENDING        13
#define CONDITION_GRENADES_ONLY    14
#define CONDITION_BREAKDANCE_ONLY  15
#define CONDITION_MID_HEALTH       16
#define CONDITION_ELECTRIC_ONLY    17
#define CONDITION_CLOTHESLINE_ONLY 18
#define CONDITION_PIGEON_ONLY   19
#define CONDITION_PISTOL_ONLY   20
#define CONDITION_MINE_ONLY     21
#define CONDITION_COMBO_ONLY    22


#define VG_STORY_SCENE_SETUP   0
#define VG_STORY_SCENE_WON     1
#define VG_STORY_SCENE_LOST    2
#define VG_STORY_SCENE_LAST    3

bool VG_STORY_PAUSE = false;

int VG_STORY_SETUP = VG_STORY_SCENE_SETUP;

#define EQUIPMENT_BASIC        0
#define EQUIPMENT_ALL          1
#define EQUIPMENT_JUST_SP1     2
#define EQUIPMENT_JUST_SP2     3
#define EQUIPMENT_JUST_COMBO   4

int VG_1_EQUIPMENT = EQUIPMENT_ALL;
int VG_2_EQUIPMENT = EQUIPMENT_ALL;

float VG_RESIZE_X = 0.0f;
float VG_RESIZE_Y = 0.0f; 

int VG_ZOOM_VS = 0;


int VG_story_song[20];
int VG_story_song_victory[20];
int VG_story_characters[20];
int VG_story_background[20];
int VG_story_conditions[20];
bool VG_is_an_alter_story[20];
int VG_story_ai_level[20];
int VG_1_equipment[20];
int VG_2_equipment[20];
bool VG_has_third_special[20];
int VG_story_count=0;
int VG_story_totalcount = 0;

int VG_BACK_SELECTED = 0;
bool VG_BACK_TO_SELECTION = false;

bool VG_IS_AN_ALTER = false;

bool VG_IS_AN_ALTER_P1 = false;
bool VG_IS_AN_ALTER_P2 = false;

int VG_CURRENT_STORY_SCENE = 0;

int VG_ROUND_CONDITIONS = CONDITION_NONE;

bool VG_AI_DOG_ONSCREEN = false;

int VG_AI_LEVEL = 1;

bool VG_SURVIVAL = false;

int VG_SURVIVAL_ROUND = 1;

int VG_SURVIVAL_WINS = 0;

int VG_1_SURVIVAL_HEALTH = 2000;

int VG_flash_survive_timer = 0;
int VG_flash_survive_local_timer = 0;
bool VG_flash_survive = false;


int VG_GAME_MODE = 0;

int flash_helptext_timer = 0;
int flash1_helptext_timer = 0;

int VG_2_UP_timer = 0;
int VG_2_UP = false;
int VG_2_DOWN_timer = 0;
int VG_2_DOWN = false;
int VG_2_LEFT_timer = 0;
int VG_2_LEFT = false;
int VG_2_RIGHT_timer = 0;
int VG_2_RIGHT = false;

int VG_2_PUNCH_release = 0;
int VG_2_PUNCH_timer = 0;
int VG_2_PUNCH = false;
int VG_2_PUNCH2_release = 0;
int VG_2_PUNCH2_timer = 0;
int VG_2_PUNCH2 = false;

int VG_2_KICK_release = 0;
int VG_2_KICK_timer = 0;
int VG_2_KICK = false;
int VG_2_KICK2_release = 0;
int VG_2_KICK2_timer = 0;
int VG_2_KICK2 = false;

int VG_2_BLOCK_release = 0;
int VG_2_BLOCK_timer = 0;
int VG_2_BLOCK = 0;

int VG_2_THROW_release = 0;
int VG_2_THROW_timer = 0;
int VG_2_THROW = 0;
int VG_2_THROW_COOLDOWN = 0;

bool VG_ESC_pressed = false;
bool VG_1_pressed = false;
bool VG_2_pressed = false;
bool VG_3_pressed = false;

int VG_TIME = 99;


// ******************************************************************************//
//                               SOUND EFFECTS                                   //
// ******************************************************************************//

int VG_yell_sfx = -1;

bool vg_judge_sfx = false;

int VG_victory_sfx = -1;

int VG_1_special1_sfx = 0;
int VG_2_special1_sfx = 0;

int VG_1_chop_sfx = 0;
int VG_2_chop_sfx = 0;

int VG_reloadsfx = 0;
int VG_reloadedsfx = 0; 

int VG_1_Pistolsfx = 0;           
int VG_2_Pistolsfx = 0;   
int VG_1_Mgunsfx = 0;         
int VG_2_Mgunsfx = 0;  
int VG_1_Vialsfx = 0;         
int VG_2_Vialsfx = 0; 
int VG_1_Grenadesfx = 0;         
int VG_2_Grenadesfx = 0; 
int VG_1_Knifesfx = 0;         
int VG_2_Knifesfx = 0; 
int VG_1_Pfpsfx = 0;         
int VG_2_Pfpsfx = 0; 

bool stop_vg_amb_prison_sfx = false;
bool stop_vg_amb_traffic_sfx = false;
bool stop_vg_amb_subway_sfx = false;
bool stop_vg_amb_van_sfx = false;
bool stop_vg_amb_duel_sfx = false;

bool VG_knockslide_sfx = false;

bool VG_titlevoice_sfx = false;

bool vg_pause_sfx = false;

bool vg_explode_sfx = false;

bool vg_title_move_sfx=false;

bool vg_titlemove_sfx=false;

bool vg_vacuum_sfx=false;


bool vg_fight_sfx = false;

bool vg_titleselect_sfx = false;

bool vg_hitsound_sfx  = false;

bool vg_shock_sfx=false; 
bool VG_handcuffs_sfx = false;
bool vg_amb_prison_sfx = false;
bool vg_amb_traffic_sfx = false;
bool vg_amb_van_sfx = false;
bool vg_amb_duel_sfx = false;

bool vg_amb_car1_sfx = false;
bool vg_amb_car2_sfx = false;

bool vg_siren_sfx=false;
bool vg_shout_sfx=false;

bool vg_win_sfx=false;

bool VG_verdict_sfx = false;
bool VG_guilty_sfx = false;

bool VG_pow_sfx = false;

bool vg_stamp_sfx = false;

bool vg_splat_sfx = false;

bool vg_tink_sfx = false;

bool vg_glass_sfx = false;

bool vg_dogattack_sfx = false;

bool vg_ric_sfx = false;

bool vg_round_sfx=false;

bool vg_gameover_sfx = false;

bool VG_KO_sfx = false;
bool vg_lose_sfx = false;
bool VG_power_sfx = false;
bool VG_arrested_sfx = false;
bool VG_wasted_sfx = false;

bool vg_perfect_sfx = false;
bool vg_ko_smash_sfx   = false;
bool vg_amb_subway_sfx = false;
bool vg_blocked_sfx=false;
bool vg_knockdown_sfx=false;
bool VG_title_sfx = false;
bool VG_destiny_sfx = false;

bool VG_alright_sfx = false;
bool VG_nice_sfx = false;
bool VG_okay_sfx = false;
bool VG_good_sfx = false;
bool VG_great_sfx = false;
bool VG_excellent_sfx = false;

bool VG_land_sfx = false;


// ******************************************************************************//
//                               VG VIRTUAL KEYS                                 //
// ******************************************************************************//

int VG_global_temp_key = 0;

int tVG_P1_UP_KEY = 0;
int tVG_P1_DOWN_KEY = 0;
int tVG_P1_LEFT_KEY = 0;
int tVG_P1_RIGHT_KEY = 0;

int tVG_P1_PUNCH1_KEY = 0;
int tVG_P1_PUNCH2_KEY = 0;
int tVG_P1_KICK1_KEY = 0;
int tVG_P1_KICK2_KEY = 0;

int tVG_P2_UP_KEY = 0;
int tVG_P2_DOWN_KEY = 0;
int tVG_P2_LEFT_KEY = 0;
int tVG_P2_RIGHT_KEY = 0;

int tVG_P2_PUNCH1_KEY = 0;
int tVG_P2_PUNCH2_KEY = 0;
int tVG_P2_KICK1_KEY = 0;
int tVG_P2_KICK2_KEY = 0;

int tVG_P1_BLOCK_KEY = 0;
int tVG_P1_THROW_KEY = 0;
int tVG_P2_BLOCK_KEY = 0;
int tVG_P2_THROW_KEY = 0;

#define VG_KEY_A    0
#define VG_KEY_B    1
#define VG_KEY_C    2
#define VG_KEY_D    3
#define VG_KEY_E    4
#define VG_KEY_F    5
#define VG_KEY_G    6

#define VG_KEY_H    7
#define VG_KEY_I    8
#define VG_KEY_J    9
#define VG_KEY_K    10
#define VG_KEY_L    11
#define VG_KEY_M    12
#define VG_KEY_N    13

#define VG_KEY_O    14
#define VG_KEY_P    15
#define VG_KEY_Q    16
#define VG_KEY_R    17
#define VG_KEY_S    18
#define VG_KEY_T    19
#define VG_KEY_U    20

#define VG_KEY_V    21
#define VG_KEY_W    22
#define VG_KEY_X    23
#define VG_KEY_Y    24
#define VG_KEY_Z    25

#define VG_KEY_UP    26
#define VG_KEY_DOWN  27
#define VG_KEY_LEFT  28
#define VG_KEY_RIGHT 29

#define VG_KEY_BLANK 30

#define VG_KEY_0     31
#define VG_KEY_1     32
#define VG_KEY_2     33
#define VG_KEY_3     34
#define VG_KEY_4     35
#define VG_KEY_5     36
#define VG_KEY_6     37
#define VG_KEY_7     38
#define VG_KEY_8     39
#define VG_KEY_9     40

#define VG_KEY_SPACE 41

#define VG_KEY_COMMA 42
#define VG_KEY_DOT   43
#define VG_KEY_DIVIDE   44
#define VG_KEY_ENDLINE  45

#define VG_KEY_FORWARDSLASH  46 

#define VG_KEY_DASH  47
#define VG_KEY_HASH  48
 
#define VG_KEY_LBRACKET  49  
#define VG_KEY_RBRACKET  50 
   
bool VG_VIRBATION_FUNCTION = true;

#define VG_KNOCKSLIDE_SPEED_HIGH  0.00036f 
#define VG_KNOCKSLIDE_SPEED_SLOW  0.00030f 

int VG_1_DX_A_timer = 0;  
int VG_2_DX_A_timer = 0;   
 
float VG_1_XAXIS = 0.0f;  
float VG_2_XAXIS = 0.0f;
 
#define VG_FLASH_HIT_LENGTH 50   

#define VG_GLOBAL_DUST_LENGTH 200
int VG_1_GLOBAL_DUST_TIMER = 0; 
int VG_2_GLOBAL_DUST_TIMER = 0; 


#define VG_INVERT_START_LENGTH 150  
#define VG_INVERT_LENGTH 250
#define VG_INVERT_TOTAL_LENGTH 250

bool VG_INVERT = false;
int VG_INVERT_TIMER = 0;
int VG_INVERT_TOTAL_TIMER = 0; 

#define BILLBOARD_WAIT_LENGTH 6000

#define BILL_WAITING   0
#define BILL_MOVING    1

#define BILL_LEFT   0
#define BILL_RIGHT  1


int BILLBOARD_DIRECTION = BILL_RIGHT;
int BILLBOARD_TIMER = 0;
int BILLBOARD_STATE = BILL_WAITING;

int BILLBOARD2_DIRECTION = BILL_RIGHT;
int BILLBOARD2_TIMER = 0;
int BILLBOARD2_STATE = BILL_WAITING;

bool VG_AI_BITE_MID = false;
bool VG_AI_BITE_LOW = false;

bool VG_AI_DANGER_MID = false; 
bool VG_AI_DANGER_LOW = false;

bool VG_AI_OWN_BOMB = false; 

int VG_DEFLECT_TIMER = 0;
int VG_DEFLECT_TOTAL_TIMER = 0;

bool VG_DEFLECT_FLASH_ACTIVE = false;

int VG_HUD_1_BACK_TIMER = 0;

#define VG_CLOSE_ATTACK_DISTANCE 0.16f

bool VG_has_no_explosive = false;

float VG_clock_offset = 0.0f;
float VG_clock2_offset = 0.0f;

float VG_suitcase_offset = 0.0f;

int VG_suitcase_timer = 0;
bool VG_suitcase_resetting = false;

int VG_SCROLL_INDEX = 0;

int VG_GROUND_INDEX = 1;

int GRID_LEFT_RIGHT = 0;
int GRID_UP_DOWN = 0;
int GRID_TIMER = 0;

#define VG_SHEET_SCROLL_SPEED 0.00025f
#define VG_TITLE_SCROLL_SPEED 0.00010f


#define VG_ARCADE_STANDARD    0
#define VG_ARCADE_DUELLING    1
#define VG_ARCADE_TURBO       2
#define VG_ARCADE_MASTER      3

int VG_ROUND_LIMIT = 2;

int VG_ARCADE_TYPE = VG_ARCADE_STANDARD;

int VG_DUELLISTS_UNLOCKED = 0; 
int VG_TURBO_UNLOCKED = 0; 
int VG_MASTER_UNLOCKED = 0; 

int VG_DISPLAY_SCORE_TYPE = VG_ARCADE_STANDARD;

int VG_SABU_JUDGE_INDEX = 0;

bool VG_JUDGE_DECISION = false;
int VG_JUDGE_DECISION_TIMER = 0; 

#define VG_RAIN_LENGTH 50

int VG_RAIN_TIMER = 0;

int VG_RAIN_SEGMENT = 0;

#define VG_JUDGE_IDLE    0 
#define VG_JUDGE_MOVING  1 
#define VG_JUDGE_FLAG    2

int VG_JUDGE_AI = VG_JUDGE_IDLE;
int VG_JUDGE_AI_TIMER = 0;

#define THROW_COOLDOWN_LENGTH 1150

int VG_CPU_THROWN_COUNT = 0;

//#define VG_KEY_LEFT  41
//#define VG_KEY_RIGHT 42

#endif