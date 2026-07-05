#ifndef __LOAD_H__
#define __LOAD_H__

//#include <windows.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <string.h>
#ifdef SWITCH
//#include <gl\gl.h>
#elif XB1
#include "stb_image.h"
extern SDL_Renderer* pRenderer;
//extern Sample* global_sample;
#endif
#include "texture.h"											// Header File Containing Our Texture Structure ( NEW )
#include "globals.h"
void VG_Reset_all_anims();

#ifdef DREAMCAST

#include "gl_dc.h"
#include "glu_dc.h"
#include "glkos_dc.h"
#include "glext_dc.h"

#include <vector>
#ifndef SATURN
#include <sstream>
#endif

float log2f(float x) {
    // Define constants for the log2 calculation
    float log2_e = 1.442695041; // 1 / ln(2)
    float ln_x = 0.0;

    // Handle special cases: negative or zero input
    if (x <= 0) {
        printf("Error: log2f function only accepts positive inputs.\n");
        return 0.0; // Return 0 for simplicity, you might want to handle this differently
    }

    // Calculate ln(x) using a suitable method (e.g., Taylor series, CORDIC, etc.)
    // Here, let's just use the natural logarithm from the math library for simplicity
    ln_x = logf(x);

    // Calculate log2(x) = ln(x) / ln(2)
    return ln_x * log2_e;
}



struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
    GLenum internalFormat;
    GLboolean mipmapped;
    unsigned int dataSize;
};

typedef struct Image Image;

#ifdef SATURN
static void SaturnTextureFallback(Image *image)
{
    const unsigned long width = 16;
    const unsigned long height = 16;
    image->sizeX = width;
    image->sizeY = height;
    image->data = NULL;
    image->internalFormat = GL_SATURN_4BPP_CLUT16;
    image->mipmapped = GL_FALSE;
    image->dataSize = 0;
}

static void SaturnTexturePath(const char *filename, char *out, size_t out_size)
{
    size_t i = 0;
    for (; (filename[i] != '\0') && (i + 1 < out_size); i++) {
        char c = filename[i];
        if ((c >= 'A') && (c <= 'Z')) {
            c = (char)(c - 'A' + 'a');
        }
        out[i] = c;
    }
    out[i] = '\0';

    char *ext = strrchr(out, '.');
    if ((ext != NULL) && ((size_t)(ext - out) + 5 < out_size)) {
        strcpy(ext, ".sat");
    }
}

static int SaturnImageLoad(char *filename, Image *image)
{
    char saturn_path[256];
    SaturnTexturePath(filename, saturn_path, sizeof(saturn_path));
    glSaturnSetTextureSourcePath(saturn_path);

    FILE *file = fopen(saturn_path, "rb");
    if (file == NULL) {
        printf("Saturn texture missing, fallback: %s\n", saturn_path);
        SaturnTextureFallback(image);
        return 1;
    }

    struct {
        char magic[4];
        unsigned short width;
        unsigned short height;
        unsigned int data_size;
    } header;

    if (fread(&header, sizeof(header), 1, file) != 1 ||
        memcmp(header.magic, "VG4P", 4) != 0 ||
        header.width == 0 || header.height == 0 ||
        header.data_size == 0) {
        fclose(file);
        printf("Invalid Saturn texture, fallback: %s\n", saturn_path);
        SaturnTextureFallback(image);
        return 1;
    }

    fclose(file);
    image->sizeX = header.width;
    image->sizeY = header.height;
    image->data = NULL;
    image->internalFormat = GL_SATURN_4BPP_CLUT16;
    image->mipmapped = GL_FALSE;
    image->dataSize = 32 + header.data_size;
    return 1;
}
#endif


int ImageLoad(char *filename, Image *image) {
#ifdef SATURN
    return SaturnImageLoad(filename, image);
#else
    FILE* file = NULL;

    // make sure the file is there.
    if ((file = fopen(filename, "rb")) == NULL)
    {
        printf("File Not Found : %s\n",filename);
        return 0;
    }

    struct {
        char	id[4];	// 'DTEX'
        GLushort	width;
        GLushort	height;
        GLuint		type;
        GLuint		size;
    } header;

    fread(&header, sizeof(header), 1, file);

    GLboolean twiddled = (header.type & (1 << 26)) < 1;
    GLboolean compressed = (header.type & (1 << 30)) > 0;
    GLboolean mipmapped = (header.type & (1 << 31)) > 0;
    GLboolean strided = (header.type & (1 << 25)) > 0;
    GLuint format = (header.type >> 27) & 0b111;

    image->data = (char *) malloc (header.size);
    image->sizeX = header.width;
    image->sizeY = header.height;
    image->dataSize = header.size;

    GLuint expected = 2 * header.width * header.height;
    GLuint ratio = (GLuint) (((GLfloat) expected) / ((GLfloat) header.size));

    fread(image->data, image->dataSize, 1, file);
    fclose(file);

    if(compressed) {
        if(twiddled) {
            switch(format) {
                case 0: {
                    if(mipmapped) {
                        image->internalFormat = GL_COMPRESSED_ARGB_1555_VQ_MIPMAP_TWID_KOS;
                    } else {
                        image->internalFormat = GL_COMPRESSED_ARGB_1555_VQ_TWID_KOS;
                    }
                } break;
                case 1: {
                    if(mipmapped) {
                        image->internalFormat = GL_COMPRESSED_RGB_565_VQ_MIPMAP_TWID_KOS;
                    } else {
                        image->internalFormat = GL_COMPRESSED_RGB_565_VQ_TWID_KOS;
                    }
                } break;
                case 2: {
                    if(mipmapped) {
                        image->internalFormat = GL_COMPRESSED_ARGB_4444_VQ_MIPMAP_TWID_KOS;
                    } else {
                        image->internalFormat = GL_COMPRESSED_ARGB_4444_VQ_TWID_KOS;
                    }
                }
                break;
                default:
                    fprintf(stderr, "Invalid texture format");
                    return 0;
            }
        } else {
            switch(format) {
                case 0: {
                    if(mipmapped) {
                        image->internalFormat = GL_COMPRESSED_ARGB_1555_VQ_MIPMAP_KOS;
                    } else {
                        image->internalFormat = GL_COMPRESSED_ARGB_1555_VQ_KOS;
                    }
                } break;
                case 1: {
                    if(mipmapped) {
                        image->internalFormat = GL_COMPRESSED_RGB_565_VQ_MIPMAP_KOS;
                    } else {
                        image->internalFormat = GL_COMPRESSED_RGB_565_VQ_KOS;
                    }
                } break;
                case 2: {
                    if(mipmapped) {
                        image->internalFormat = GL_COMPRESSED_ARGB_4444_VQ_MIPMAP_KOS;
                    } else {
                        image->internalFormat = GL_COMPRESSED_ARGB_4444_VQ_KOS;
                    }
                }
                break;
                default:
                    fprintf(stderr, "Invalid texture format");
                    return 0;
            }
        }
    } else {
        printf("Not a compressed texture");
        return 0;
    }

    // we're done.
    return 1;
#endif
}

void Loading_Time_Draw()
{
	Image stexture_loading;

	char str_path_load[200];
	sprintf(str_path_load, "cd/data/Loading_%d.tex", (rand() % 3) + 1);

	if (!ImageLoad(str_path_load, &stexture_loading)) {
		printf("Can't Load Texture %s\n", str_path_load);
		return;
	}

	//printf("Load Texture %s\n", str_path_load);

	unsigned int texID_splash;

	glGenTextures(1, &texID_splash);

	glBindTexture(GL_TEXTURE_2D, texID_splash);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glCompressedTexImage2DARB(GL_TEXTURE_2D, 0, stexture_loading.internalFormat, stexture_loading.sizeX, stexture_loading.sizeY, 0, stexture_loading.dataSize, stexture_loading.data);

	free(stexture_loading.data);
	
		
	glBindTexture(GL_TEXTURE_2D, texID_splash);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);   // setup a 10x10x2 viewing world
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	
	glTexCoord2f(0.0, 1.0); glColor3f(1.0, 1.0, 1.0); glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0); glColor3f(1.0, 1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glColor3f(1.0, 1.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glColor3f(1.0, 1.0, 1.0); glVertex3f(1.0, 0.0, 0.0);
	glEnd();

	glKosSwapBuffers();

	glDeleteTextures(1, &texID_splash);
}


#endif
        
 
// List of routines
int LoadAnim( sString sfilename, int texture_id, int the_tex_id ); 
bool LoadHud( char *filename );
bool LoadNodes( char *filename ); 
bool LoadScene( int episode1, int scene1, bool delete_textures );
bool DumpScene( char *filename );
bool LoadTextures(sString sfilename, bool delete_textures);
bool LoadText(sString sfilename); 
bool LoadPoints( sString sfilename );
bool DumpPoints( char *filename );
bool DumpNodes( char *filename ); 

bool Load_BG(  sString sfilename); 
bool Load_COL(  char *filename); 
bool Dump_BG( sString sfilename );
bool Dump_COL( sString sfilename );

bool LoadCFG();
bool SaveCFG();  

bool LoadKeys();
bool SaveKeys(); 


#if IS_USING_DIRECTX == 1 

bool LoadDXTextures(sString sfilename, bool delete_textures);
bool sLoadCompressedTGADX(Texture * texture, char * filename);
bool sLoadTGADX(Texture * texture, char * filename);				// Load a TGA file

extern void ResetReticule();
extern void VG_Reset_all_anims();

#endif

// External Routines
                                 
extern bool LoadMAP(Texture * texture, char * filename);
extern bool LoadTGA(Texture *, char *);
extern bool sLoadTGA(Texture *, char *);
extern bool LoadDetail(Texture * texture, char * filename);
extern void TimerInit(void);
#ifdef SWITCH
extern float TimerGetTime();
#elif defined PS4 || defined XB1 || defined DREAMCAST
extern double TimerGetTime();
#endif
extern void Set_Sprite(int id, int anim, int state, int hud_or_sprite, bool reset);
extern void Animation_System(int loop, bool bullet_check, bool interrupt, bool pain_anim, bool fire);
extern void Animate(int loop, int type);
extern void Set_Timer(unsigned long time);
extern void GetDesktopResolution(int& horizontal, int& vertical);
extern void Run_Verdict(int f_rate);
extern void GetParameters(/*LPSTR lpCmdLine*/);
extern void Run_Story(int f_rate);
extern void VG_set_intro_dogs();
extern void VG_Put_Temps_Into_Keys();
extern void VG_Put_Keys_Into_Temps();

// ******************************************************************************//
//                                                                               //
//                                  LOAD KEYS                                    //
//                                                                               //
// ******************************************************************************// 
  
/*bool LoadKeys() 
{ 
    bool success=false;

	sprintf( temp_string.string, "Data/VG_KEYBINDS.cfg");

	FILE * fp;												// File pointer to texture file
    errno_t err;

	fp = fopen( temp_string.string, "r"); 

    if(err!=NULL)  
    {   
        success = false;
    }
    else    
    {      

		success = true;

		fscanf(fp,"%i", &tVG_P1_UP_KEY);   
		fscanf(fp,"%i", &tVG_P1_DOWN_KEY); 
		fscanf(fp,"%i", &tVG_P1_LEFT_KEY);
		fscanf(fp,"%i", &tVG_P1_RIGHT_KEY); 

		fscanf(fp,"%i", &tVG_P1_PUNCH1_KEY);
		fscanf(fp,"%i", &tVG_P1_PUNCH2_KEY); 
		fscanf(fp,"%i", &tVG_P1_KICK1_KEY);
		fscanf(fp,"%i", &tVG_P1_KICK2_KEY);

		fscanf(fp,"%i", &tVG_P2_UP_KEY);     
		fscanf(fp,"%i", &tVG_P2_DOWN_KEY);
		fscanf(fp,"%i", &tVG_P2_LEFT_KEY);
		fscanf(fp,"%i", &tVG_P2_RIGHT_KEY);

		fscanf(fp,"%i", &tVG_P2_PUNCH1_KEY);
		fscanf(fp,"%i", &tVG_P2_PUNCH2_KEY);
		fscanf(fp,"%i", &tVG_P2_KICK1_KEY);
		fscanf(fp,"%i", &tVG_P2_KICK2_KEY);

		fscanf(fp,"%i", &tVG_P1_BLOCK_KEY);
		fscanf(fp,"%i", &tVG_P1_THROW_KEY);
		fscanf(fp,"%i", &tVG_P2_BLOCK_KEY);
		fscanf(fp,"%i", &tVG_P2_THROW_KEY);

		if(success == false)  
		{
			//MessageBox(NULL, "Key file has been corrupted...", "ERROR", MB_OK);
		}

		if(tVG_P1_UP_KEY == VG_KEY_BLANK) 
			success = false;
		if(tVG_P1_DOWN_KEY == VG_KEY_BLANK)
			success = false;
		if(tVG_P1_LEFT_KEY == VG_KEY_BLANK)
			success = false;
		if(tVG_P1_RIGHT_KEY == VG_KEY_BLANK)
			success = false; 

		if(tVG_P1_PUNCH1_KEY == VG_KEY_BLANK)
			success = false;
		if(tVG_P1_PUNCH2_KEY == VG_KEY_BLANK)
			success = false;
		if(tVG_P1_KICK1_KEY == VG_KEY_BLANK)
			success = false; 
		if(tVG_P1_KICK2_KEY == VG_KEY_BLANK)
			success = false;

		if(tVG_P1_BLOCK_KEY == VG_KEY_BLANK)
			success = false; 
		if(tVG_P1_THROW_KEY == VG_KEY_BLANK)
			success = false;

		if(success == true)
			VG_Put_Temps_Into_Keys();

		fclose(fp); 
        
    } 

    return(success);     
    
}*/

// ******************************************************************************//
//                                                                               //
//                                  SAVE KEYS                                    //
//                                                                               //
// ******************************************************************************// 
  
/*bool SaveKeys() 
{ 
    bool success=false;

	sprintf( temp_string.string, "Data/VG_KEYBINDS.cfg");

	FILE * fp;												// File pointer to texture file
    errno_t err;

	fp = fopen(temp_string.string, "w+");
                
    if (err != NULL)
    {  
        success = false;
    }
    else      
    {        

		success = true;

		VG_Put_Keys_Into_Temps();

		fprintf(fp,"%i\n", tVG_P1_UP_KEY);   
		fprintf(fp,"%i\n", tVG_P1_DOWN_KEY); 
		fprintf(fp,"%i\n", tVG_P1_LEFT_KEY);
		fprintf(fp,"%i\n", tVG_P1_RIGHT_KEY);

		fprintf(fp,"%i\n", tVG_P1_PUNCH1_KEY);
		fprintf(fp,"%i\n", tVG_P1_PUNCH2_KEY); 
		fprintf(fp,"%i\n", tVG_P1_KICK1_KEY);
		fprintf(fp,"%i\n", tVG_P1_KICK2_KEY); 

		fprintf(fp,"%i\n", tVG_P2_UP_KEY);      
		fprintf(fp,"%i\n", tVG_P2_DOWN_KEY);
		fprintf(fp,"%i\n", tVG_P2_LEFT_KEY);
		fprintf(fp,"%i\n", tVG_P2_RIGHT_KEY);

		fprintf(fp,"%i\n", tVG_P2_PUNCH1_KEY);
		fprintf(fp,"%i\n", tVG_P2_PUNCH2_KEY);
		fprintf(fp,"%i\n", tVG_P2_KICK1_KEY);
		fprintf(fp,"%i\n", tVG_P2_KICK2_KEY);

		fprintf(fp,"%i\n", tVG_P1_BLOCK_KEY);
		fprintf(fp,"%i\n", tVG_P1_THROW_KEY);
		fprintf(fp,"%i\n", tVG_P2_BLOCK_KEY);
		fprintf(fp,"%i\n", tVG_P2_THROW_KEY);

		fclose(fp); 
        
    } 

    return(success);     
    
}*/

// ******************************************************************************//
//                                                                               //
//                                  LOAD CFG                                     //
//                                                                               //
// ******************************************************************************// 

#if defined PS4 || defined XB1 || defined DREAMCAST

float checksave_music_volume;
float checksave_sfx_volume;
int checksave_sc_width;
int checksave_sc_height;
int checksave_sc_bits;
float checksave_sc_ratio;
int checksave_sc_render_rate;
int checksave_temp_fullscreen;
int checksave_saved_window_posX;
int checksave_saved_window_posY;
int checksave_RENDERER;
int checksave_VG_VS_TIME;
int checksave_VG_VS_HEALTH;
int checksave_VG_VS_BG;
int checksave_VG_DUELLISTS_UNLOCKED;
int checksave_VG_TURBO_UNLOCKED;
int checksave_VG_MASTER_UNLOCKED;
int checksave_temp_lowres;

int checksave_VG_CHARACTER_LOCKS[12];

bool CheckCFG()
{
	//retrun false if no change, true otherwise

	if (checksave_music_volume != music_volume)
		return true;

	if (checksave_sfx_volume != sfx_volume)
		return true;

	if (checksave_sc_width != sc_width)
		return true;

	if (checksave_sc_height != sc_height)
		return true;

	if (checksave_sc_bits != sc_bits)
		return true;

	if (checksave_sc_ratio != sc_ratio)
		return true;

	if (checksave_sc_render_rate != sc_render_rate)
		return true;

	//if (checksave_temp_fullscreen != global_temp_fullscreen)
		//return true;

	if (checksave_saved_window_posX != saved_window_posX)
		return true;

	if (checksave_saved_window_posY != saved_window_posY)
		return true;

	if (checksave_RENDERER != RENDERER)
		return true;

	if (checksave_VG_VS_TIME != VG_VS_TIME)
		return true;

	if (checksave_VG_VS_HEALTH != VG_VS_HEALTH)
		return true;

	if (checksave_VG_VS_BG != VG_VS_BG)
		return true;

	if (checksave_VG_DUELLISTS_UNLOCKED != VG_DUELLISTS_UNLOCKED)
		return true;

	if (checksave_VG_TURBO_UNLOCKED != VG_TURBO_UNLOCKED)
		return true;

	if (checksave_VG_MASTER_UNLOCKED != VG_MASTER_UNLOCKED)
		return true;

	//if (checksave_temp_lowres != global_temp_lowres)
		//return true;

	for (int i = 0; i < 12; i++)
	{
		if (checksave_VG_CHARACTER_LOCKS[i] != VG_CHARACTER_LOCKS[i])
			return true;
	}

	return false;
}
#endif

#ifdef SWITCH
extern bool CANSAVE_SWITCH;
#elif XB1
#include <vector>

extern bool CANSAVE_XB1;

std::vector<uint8_t> XB1_LoadSave(std::string cont, std::string blob);
void XB1_WriteSave(std::string cont, std::string blob, std::vector<uint8_t> data);

std::size_t array_read(void* dest, std::size_t size, std::size_t count, std::uint8_t* src)
{
	std::size_t bytes_to_read = size * count;
	std::memcpy(dest, src, bytes_to_read);
	return count;
}
#elif DREAMCAST

size_t array_read(void* dest, size_t size, size_t count, uint8_t* src)
{
    size_t bytes_to_read = size * count;
    memcpy(dest, src, bytes_to_read);
    return count;
}

#define SCORE_FILE "vg.bin"
// array size is 512
static const unsigned char VERDICT_ICON[]  = {
  0x00, 0x00, 0x01, 0x01, 0x12, 0x22, 0x33, 0x33, 0x33, 0x22, 0x33, 0x33, 0x32, 0x23, 0x32, 0x20, 
  0x00, 0x00, 0x01, 0x01, 0x12, 0x22, 0x22, 0x22, 0x23, 0x22, 0x23, 0x22, 0x22, 0x00, 0x11, 0x14, 
  0x22, 0x02, 0x01, 0x11, 0x10, 0x00, 0x02, 0x22, 0x22, 0x20, 0x00, 0x11, 0x11, 0x11, 0x55, 0x46, 
  0x00, 0x00, 0x01, 0x10, 0x11, 0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x55, 0x55, 0x55, 0x57, 0x46, 
  0x20, 0x20, 0x01, 0x10, 0x11, 0x11, 0x11, 0x55, 0x55, 0x55, 0x55, 0x77, 0x77, 0x87, 0x77, 0x46, 
  0x00, 0x00, 0x01, 0x01, 0x11, 0x15, 0x55, 0x57, 0x75, 0x78, 0x88, 0x88, 0x88, 0x88, 0x84, 0x66, 
  0x11, 0x11, 0x11, 0x01, 0x11, 0x11, 0x11, 0x15, 0x75, 0x88, 0x85, 0x89, 0x99, 0x99, 0x94, 0x66, 
  0x55, 0x11, 0x11, 0x01, 0x15, 0x55, 0x55, 0x51, 0x55, 0x88, 0x55, 0x11, 0x11, 0x11, 0x14, 0x66, 
  0x77, 0x77, 0x51, 0x01, 0x11, 0x11, 0x55, 0x55, 0x55, 0x88, 0x11, 0x11, 0x11, 0x11, 0x46, 0x66, 
  0x88, 0x87, 0x51, 0x07, 0x77, 0x77, 0x77, 0x75, 0x58, 0x88, 0x51, 0xab, 0x11, 0x14, 0x66, 0x66, 
  0x88, 0x88, 0x51, 0x18, 0x88, 0x88, 0x88, 0x85, 0x88, 0x95, 0x71, 0xab, 0xb1, 0x14, 0x66, 0x66, 
  0x89, 0x98, 0x81, 0x19, 0x99, 0x99, 0x99, 0x98, 0x89, 0x95, 0x77, 0x71, 0x11, 0x14, 0x66, 0x66, 
  0x99, 0x99, 0x85, 0x19, 0x99, 0x99, 0x99, 0x99, 0x89, 0x95, 0x78, 0x88, 0x77, 0x74, 0x66, 0x66, 
  0x99, 0x99, 0x98, 0x59, 0x99, 0x99, 0x99, 0x99, 0x99, 0x95, 0x78, 0x99, 0x99, 0xc4, 0x66, 0x66, 
  0x99, 0x99, 0x98, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x95, 0x89, 0x99, 0x99, 0x46, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x91, 0x89, 0x99, 0x98, 0x46, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x95, 0x89, 0x99, 0x97, 0x46, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x91, 0x89, 0x99, 0x8c, 0x46, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x98, 0x99, 0x99, 0x91, 0x89, 0x99, 0x74, 0x66, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x88, 0x99, 0x99, 0x91, 0x89, 0x98, 0xc4, 0x66, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x99, 0x99, 0x98, 0x75, 0x71, 0x77, 0x71, 0x99, 0x98, 0xd6, 0x66, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x87, 0x97, 0x71, 0x19, 0x99, 0x9c, 0x46, 0x66, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x98, 0x89, 0x99, 0x9d, 0x66, 0x66, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0xc4, 0x66, 0x66, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0xd6, 0x66, 0x66, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x97, 0x46, 0x66, 0x66, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x97, 0x11, 0x11, 0x11, 0x77, 0x99, 0x99, 0x71, 0xd4, 0x66, 0x66, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x78, 0x99, 0x99, 0x99, 0x71, 0x79, 0x99, 0x1d, 0xe4, 0x66, 0x66, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x99, 0x98, 0x88, 0x88, 0x99, 0x99, 0x97, 0x1d, 0xed, 0x46, 0x66, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x71, 0xd1, 0xed, 0x46, 0x66, 0x66, 0x66, 
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x97, 0x1d, 0xd1, 0xde, 0xd4, 0x66, 0x66, 0x66, 
  0x89, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x71, 0xd1, 0xd1, 0x1e, 0xd4, 0x66, 0x66, 0x66
};

// array size is 32
static const unsigned char VERDICT_ICON_PAL[]  = {
  0x36, 0xf6, 0x03, 0xf2, 0x89, 0xfb, 0xab, 0xfc, 0x02, 0xf1, 0x18, 0xf8, 0x00, 0xf0, 0x39, 0xfa, 
  0x4b, 0xfb, 0xcd, 0xff, 0x4f, 0xf4, 0xaf, 0xfa, 0x27, 0xf8, 0x34, 0xf5, 0x48, 0xf9, 0x00, 0x00
};

extern bool continueWithoutSaving;

uint8 lastSaveMem[500];

int save_to_vmu(uint8* data, uint16 size) {
#ifdef SATURN
    (void)data;
    (void)size;
    return 0;
#else
    vmu_pkg_t pkg;
    int pkg_size, err;
    uint8 *pkg_out;
    FILE *fp;
    char savename[32];
    maple_device_t *vmu;
    int rv = 0, blocks_freed = 0;
    file_t f;

    /* Make sure there's a VMU in port A1. */
    if(!(vmu = maple_enum_dev(0, 1))) {
        return -100;
    }

    if(!vmu->valid || !(vmu->info.functions & MAPLE_FUNC_MEMCARD)) {
        return -100;
    }

    sprintf(savename, "/vmu/a1/%s", SCORE_FILE);

    
    strncpy(pkg.desc_long, "Verdict Guilty Save", 32);
    pkg.desc_long[31] = 0;
    

    strcpy(pkg.desc_short, "Verdict Guilty");
    strcpy(pkg.app_id, "Verdict Guilty");
    pkg.icon_cnt = 1;
    pkg.icon_anim_speed = 0;
    memcpy(pkg.icon_pal, VERDICT_ICON_PAL, 32);
    pkg.icon_data = VERDICT_ICON;
    pkg.eyecatch_type = VMUPKG_EC_NONE;
    pkg.data_len = size;
    pkg.data = data;

    vmu_pkg_build(&pkg, &pkg_out, &pkg_size);

    /* See if a file exists with that name, since we'll overwrite it. */
    f = fs_open(savename, O_RDONLY);
    if(f != FILEHND_INVALID) {
        blocks_freed = fs_total(f) >> 9;
        fs_close(f);
    }

    /* Make sure there's enough free space on the VMU. */
    if(vmufs_free_blocks(vmu) + blocks_freed < (pkg_size >> 9)) {
    	printf("Pas assez de mémoire libre dans le VMU");
        free(pkg_out);
        //free(comp);
        return -2;
    }

    if(memcmp(data, lastSaveMem, 500) == 0)
    {
    	free(pkg_out);
    	printf("Same_Save\n");
    	return 0;
    }

    if(!(fp = fopen(savename, "wb"))) {
        free(pkg_out);
        //free(comp);
        return -3;
    }

    if(fwrite(pkg_out, 1, pkg_size, fp) != (size_t)pkg_size)
        rv = -1;
    else
   		rv = 0;

    fclose(fp);

    memcpy(lastSaveMem, pkg_out, 500);

    free(pkg_out);


    //free(comp);

    return rv;
#endif
}



int read_from_vmu(uint8* data) {
#ifdef SATURN
    if (data != NULL) {
        memset(data, 0, 500);
    }
    return 0;
#else
    vmu_pkg_t pkg;
    uint8 *pkg_out;
    int pkg_size;
    FILE *fp;
    char savename[32];

    /* Try the newer filename first... */
    sprintf(savename, "/vmu/a1/%s", SCORE_FILE);

    if(!(fp = fopen(savename, "rb"))) {
        return -1;
    }

    fseek(fp, 0, SEEK_SET);
    fseek(fp, 0, SEEK_END);
    pkg_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    pkg_out = (uint8 *)malloc(pkg_size);
    
    fread(pkg_out, pkg_size, 1, fp);
    fclose(fp);

    vmu_pkg_parse(pkg_out, &pkg);

    printf("Begin MEMCPY\n");
    memcpy(data, pkg.data, pkg.data_len);
    printf("PKG DATA SIZE %d\n", pkg.data_len);
    memcpy(lastSaveMem, pkg.data, 500);

    printf("After MEMCPY\n");
    free(pkg_out);
    printf("After FREE\n");

    return 0;
#endif
}

#endif

bool LoadCFG() 
{ 
    bool success=false;
    float dimension=0.0f; 
	int temp_fullscreen=0;
	int temp_HAS_HARD_MODE=0;
	int temp_VIBRATE_FUNCTION=0;
	int temp_CONTROLLER_RIGID=0;
	int temp_CONTROLLER=0;
	int temp_VG_DUELLISTS_UNLOCKED = 0;
	int temp_dummy=0;
	int temp_blur=0;
	int temp_int=0;
	int temp_lowres=0;  
    int encode[25];   
    int encode_temp[25];  
	int dummy_int = 0;

    memset(encode, 0, sizeof(encode));
    memset(encode_temp, 0, sizeof(encode_temp));
	memset(VG_CHARACTER_LOCKS, 0, sizeof(VG_CHARACTER_LOCKS));
#ifdef SATURN
    music_volume = 0.0f;
    sfx_volume = 0.0f;
    sc_bits = 32;
    sc_render_rate = RENDER_RATE;
    sc_blur = false;
    fullscreen = false;
    saved_window_posX = 0;
    saved_window_posY = 0;
    sc_width = 640;
    sc_height = 480;
    new_sc_width = sc_width;
    new_sc_height = sc_height;
    RENDERER = RENDER_OPENGL;
    VG_VS_TIME = 0;
    VG_VS_HEALTH = 0;
    VG_VS_BG = 0;
    VG_DUELLISTS_UNLOCKED = 0;
    VG_TURBO_UNLOCKED = 0;
    VG_MASTER_UNLOCKED = 0;
    VG_HIRES_BACKGROUNDS = false;
    return false;
#endif
#ifdef SWITCH
	sprintf( temp_string.string, "save:/VG.cfg");
#elif defined PS4 || defined XB1 || defined DREAMCAST
	sprintf(temp_string.string, "VG.cfg");
#endif
	FILE * fp;												// File pointer to texture file
#ifndef DREAMCAST
    errno_t err;
#endif

#ifdef SWITCH
	fp = fopen(temp_string.string, "r");
#elif PS4
	fp = _Application.dataLoad_fopen(temp_string.string);
#elif XB1
	std::vector<uint8_t> dataVEC = XB1_LoadSave("Verdict_Guilty_Save", temp_string.string);

	uint8_t* dataPTR = dataVEC.data();
	std::size_t counterDataPTR = 0;
#elif DREAMCAST
	uint8_t* dataPTR = (uint8_t*)malloc(500);
	int saveFound = -1;
	if(continueWithoutSaving == true)
	{
		saveFound = -1;
	}
	else
	{
		saveFound = read_from_vmu(dataPTR);
	}
	
	if(saveFound != -1)
	{
		if(dataPTR[0] == 'n' && dataPTR[1] == 'o' && dataPTR[2] == '!' && dataPTR[3] == '\0')
		{
			saveFound = -1;
		}
	}
	int counterDataPTR = 0;
#endif

#if defined SWITCH || defined PS4
    if(fp==NULL)  
#elif DREAMCAST
    if(saveFound == -1)
#elif XB1
	if(dataVEC.size() == 0 || dataVEC.empty() == true)
#endif
    {   
#ifdef DREAMCAST
    	free(dataPTR);
    	music_volume = 0.8f; 
        sfx_volume   = 0.8f; 
#else
        music_volume = 0.5f; 
        sfx_volume   = 0.5f; 
#endif            
        sc_bits      = 32;     
            
  //      GetDesktopResolution(horizontal, vertical);

        sc_render_rate = RENDER_RATE;
        
        sc_blur = false; 
        
        fullscreen = true; 
        
        saved_window_posX = 0;
        saved_window_posY = 0; 
#ifndef DREAMCAST
        sc_width = 1280; // 1024 
        sc_height = 720; // 768    

        if(dimension == 0.75f)
        {
            sc_width = 1280; // 1024 
            sc_height = 720; // 768           
        } 
        
        if(dimension == 0.625f) // 16 : 10
        { 
            sc_width = 1280; // 1280
            sc_height = 800; // 800          
        } 
        
        if(dimension == 0.6f)
        {
            sc_width = 1280; // 1280
            sc_height = 720; // 768           
        } 
        
        if(dimension >= 0.5622f && dimension <= 0.5625f) // 16 : 9
        {
            sc_width = 1280; 
            sc_height = 720;            
        } 
#else
        sc_width = 640; // 1024 
        sc_height = 480; // 768    

        if(dimension == 0.75f)
        {
            sc_width = 640; // 1024 
        	sc_height = 480; // 768           
        } 
        
        if(dimension == 0.625f) // 16 : 10
        { 
            sc_width = 640; // 1024 
        	sc_height = 480; // 768            
        } 
        
        if(dimension == 0.6f)
        {
            sc_width = 640; // 1024 
        	sc_height = 480; // 768         
        } 
        
        if(dimension >= 0.5622f && dimension <= 0.5625f) // 16 : 9
        {
            sc_width = 640; // 1024 
        	sc_height = 480; // 768           
        } 
#endif
                             
        new_sc_width=sc_width;  
        new_sc_height=sc_height; 

        success = false;
        
    }
    else    
    {      

		success = true;
#ifdef SWITCH
		fscanf(fp,"%f", &music_volume);   
		fscanf(fp,"%f", &sfx_volume); 
		fscanf(fp,"%i", &sc_width);
		fscanf(fp,"%i", &sc_height); 
		fscanf(fp,"%i", &sc_bits);
		fscanf(fp,"%f", &sc_ratio); 
		fscanf(fp,"%i", &sc_render_rate);
		fscanf(fp,"%i", &temp_fullscreen);   // Bool
		fscanf(fp,"%i", &saved_window_posX);     
		fscanf(fp,"%i", &saved_window_posY);
		fscanf(fp,"%i", &RENDERER);
		fscanf(fp,"%i", &VG_VS_TIME);
		fscanf(fp,"%i", &VG_VS_HEALTH);
		fscanf(fp,"%i", &VG_VS_BG);
		fscanf(fp,"%i", &VG_DUELLISTS_UNLOCKED); 
		fscanf(fp,"%i", &VG_TURBO_UNLOCKED);
		fscanf(fp,"%i", &VG_MASTER_UNLOCKED);
		fscanf(fp,"%i", &temp_lowres);       // Bool

		for(int i =0 ;i< 12;i++)
		{
			fscanf(fp,"%i", &VG_CHARACTER_LOCKS[i]);
		}
#elif PS4
		fread(&music_volume, 1, sizeof(float), fp);
		fread(&sfx_volume, 1, sizeof(float), fp);
		fread(&sc_width, 1, sizeof(int), fp);
		fread(&sc_height, 1, sizeof(int), fp);
		fread(&sc_bits, 1, sizeof(int), fp);
		fread(&sc_ratio, 1, sizeof(float), fp);
		fread(&sc_render_rate, 1, sizeof(int), fp);
		fread(&temp_fullscreen, 1, sizeof(int), fp);   // Bool
		fread(&saved_window_posX, 1, sizeof(int), fp);
		fread(&saved_window_posY, 1, sizeof(int), fp);
		fread(&RENDERER, 1, sizeof(int), fp);
		fread(&VG_VS_TIME, 1, sizeof(int), fp);
		fread(&VG_VS_HEALTH, 1, sizeof(int), fp);
		fread(&VG_VS_BG, 1, sizeof(int), fp);
		fread(&VG_DUELLISTS_UNLOCKED, 1, sizeof(int), fp);
		fread(&VG_TURBO_UNLOCKED, 1, sizeof(int), fp);
		fread(&VG_MASTER_UNLOCKED, 1, sizeof(int), fp);
		fread(&temp_lowres, 1, sizeof(int), fp);       // Bool

		for (int i = 0; i < 12; i++)
		{
			fread(&VG_CHARACTER_LOCKS[i], 1, sizeof(int), fp);
		}

		checksave_music_volume = music_volume;
		checksave_sfx_volume = sfx_volume;
		checksave_sc_width = sc_width;
		checksave_sc_height = sc_height;
		checksave_sc_bits = sc_bits;
		checksave_sc_ratio = sc_ratio;
		checksave_sc_render_rate = sc_render_rate;
		checksave_saved_window_posX = saved_window_posX;
		checksave_saved_window_posY = saved_window_posY;
		checksave_RENDERER = RENDERER;
		checksave_VG_VS_TIME = VG_VS_TIME;
		checksave_VG_VS_HEALTH = VG_VS_HEALTH;
		checksave_VG_VS_BG = VG_VS_BG;
		checksave_VG_DUELLISTS_UNLOCKED = VG_DUELLISTS_UNLOCKED;
		checksave_VG_TURBO_UNLOCKED = VG_TURBO_UNLOCKED;
		checksave_VG_MASTER_UNLOCKED = VG_MASTER_UNLOCKED;

		for (int i = 0; i < 12; i++)
		{
			checksave_VG_CHARACTER_LOCKS[i] = VG_CHARACTER_LOCKS[i];
		}
#elif defined XB1 || defined DREAMCAST 
		array_read(&music_volume, 1, sizeof(float), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(float);
		array_read(&sfx_volume, 1, sizeof(float), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(float);
		array_read(&sc_width, 1, sizeof(int), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(int);
		array_read(&sc_height, 1, sizeof(int), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(int);
		array_read(&sc_bits, 1, sizeof(int), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(int);
		array_read(&sc_ratio, 1, sizeof(float), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(float);
		array_read(&sc_render_rate, 1, sizeof(int), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(int);
		array_read(&temp_fullscreen, 1, sizeof(int), &dataPTR[counterDataPTR]);   // Bool
		counterDataPTR += sizeof(int);
		array_read(&saved_window_posX, 1, sizeof(int), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(int);
		array_read(&saved_window_posY, 1, sizeof(int), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(int);
		array_read(&RENDERER, 1, sizeof(int), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(int);
		array_read(&VG_VS_TIME, 1, sizeof(int), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(int);
		array_read(&VG_VS_HEALTH, 1, sizeof(int), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(int);
		array_read(&VG_VS_BG, 1, sizeof(int), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(int);
		array_read(&VG_DUELLISTS_UNLOCKED, 1, sizeof(int), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(int);
		array_read(&VG_TURBO_UNLOCKED, 1, sizeof(int), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(int);
		array_read(&VG_MASTER_UNLOCKED, 1, sizeof(int), &dataPTR[counterDataPTR]);
		counterDataPTR += sizeof(int);
		array_read(&temp_lowres, 1, sizeof(int), &dataPTR[counterDataPTR]);       // Bool
		counterDataPTR += sizeof(int);

		for (int i = 0; i < 12; i++)
		{
			array_read(&VG_CHARACTER_LOCKS[i], 1, sizeof(int), &dataPTR[counterDataPTR]);
			counterDataPTR += sizeof(int);
		}

		checksave_music_volume = music_volume;
		checksave_sfx_volume = sfx_volume;
		checksave_sc_width = sc_width;
		checksave_sc_height = sc_height;
		checksave_sc_bits = sc_bits;
		checksave_sc_ratio = sc_ratio;
		checksave_sc_render_rate = sc_render_rate;
		checksave_saved_window_posX = saved_window_posX;
		checksave_saved_window_posY = saved_window_posY;
		checksave_RENDERER = RENDERER;
		checksave_VG_VS_TIME = VG_VS_TIME;
		checksave_VG_VS_HEALTH = VG_VS_HEALTH;
		checksave_VG_VS_BG = VG_VS_BG;
		checksave_VG_DUELLISTS_UNLOCKED = VG_DUELLISTS_UNLOCKED;
		checksave_VG_TURBO_UNLOCKED = VG_TURBO_UNLOCKED;
		checksave_VG_MASTER_UNLOCKED = VG_MASTER_UNLOCKED;

		for (int i = 0; i < 12; i++)
		{
			checksave_VG_CHARACTER_LOCKS[i] = VG_CHARACTER_LOCKS[i];
		}
#endif

		SAFE_INT2BOOL(temp_fullscreen, fullscreen); 
		SAFE_INT2BOOL(temp_lowres, VG_HIRES_BACKGROUNDS);	

		if(success == false)  
		{
			//MessageBox(NULL, "Cfg file has been corrupted...", "ERROR", MB_OK);
		}
	 
		if(VG_VS_TIME > 1 || VG_VS_TIME < 0)
			VG_VS_TIME = 0;
		if(VG_VS_HEALTH > 1 || VG_VS_HEALTH < 0)
			VG_VS_HEALTH = 0;
		if(VG_VS_BG > 1 || VG_VS_BG < 0)
			VG_VS_BG = 0;

		if(sfx_volume < 0.0f)  
			sfx_volume = 0.0f;  
		if(sfx_volume > 1.0f)  
			sfx_volume = 1.0f;
          
		if(music_volume < 0.0f)    
			music_volume = 0.0f; 
		if(music_volume > 1.0f) 
			music_volume = 1.0f;
    
		if(saved_window_posX < 0 || saved_window_posY < 0)  
		{ 
			saved_window_posX = 0;
			saved_window_posY = 0;
		}  
   
		new_sc_width=sc_width; 
		new_sc_height=sc_height;  

#ifdef SWITCH               
		fclose(fp);
#elif PS4
		_Application.dataLoad_fclose(fp);
#elif DREAMCAST
		free(dataPTR);
#endif
        
    } 

	fullscreen = false;

	sc_width = 640; // 1024 
	sc_height = 480; // 768    

	if(RENDERER < 0 || RENDERER > 2)
		RENDERER = RENDER_DIRECTX;

	//GetParameters(global_lpCmdLine);


    return(success);     
    
}
 // ******************************************************************************//
//                                                                               //
//                                  Save CFG                                     //
//                                                                               //
// ******************************************************************************// 



bool SaveCFG()
{
#ifdef SATURN
    return false;
#endif
#ifdef SWITCH
	if (CANSAVE_SWITCH == false)
	{
		return false;
	}
#elif XB1
	if (CANSAVE_XB1 == false)
	{
		return false;
	}
#elif DREAMCAST
	if(continueWithoutSaving == true)
	{
		return false;
	}
#endif
    bool success=false;
	int temp_fullscreen=0;
	int temp_HAS_HARD_MODE=0;
	int temp_VIBRATE_FUNCTION=0; 
	int temp_CONTROLLER_RIGID=0; 
	int temp_CONTROLLER=0; 
	int temp_lowres=0;
	int temp_blur=0;
	int temp_dummy=0; // Replaces keyboard layout
	int temp_int=0;
    int encode[25];  
    int encode_temp[25];  
	int dummy_int = 0;
	
    memset(encode, 0, sizeof(encode));
    memset(encode_temp, 0, sizeof(encode_temp));
#ifdef SWITCH
	sprintf( temp_string.string, "save:/VG.cfg");
#elif defined PS4 || defined XB1
	unsigned char byte_to_sav[500];
	unsigned int ptr_offset = 0;
	memset(byte_to_sav, 0, 500);

	sprintf(temp_string.string, "VG.cfg");
#elif defined DREAMCAST
	unsigned char* byte_to_sav = (unsigned char*)malloc(500);
	unsigned int ptr_offset = 0;
	memset(byte_to_sav, 0, 500);

	sprintf(temp_string.string, "VG.cfg");
#endif
       
//    remove(temp_string.string);  

	FILE * fp;
#ifndef DREAMCAST												// File pointer to texture file
    errno_t err;
#endif
#ifdef SWITCH
	fp = fopen(temp_string.string, "w");
  
    if (fp == NULL)
    {  
        success = false;
    }
    else      
    { 


		SAFE_BOOL2INT(fullscreen, temp_fullscreen); 
		SAFE_BOOL2INT(VG_HIRES_BACKGROUNDS, temp_lowres);
		 
        fprintf(fp,"%f\n", music_volume); 
        fprintf(fp,"%f\n", sfx_volume);  
        fprintf(fp,"%i\n", sc_width);   
        fprintf(fp,"%i\n", sc_height); 
        fprintf(fp,"%i\n", sc_bits);
        fprintf(fp,"%f\n", sc_ratio);
        fprintf(fp,"%i\n", sc_render_rate); 
        fprintf(fp,"%i\n", temp_fullscreen);        // bool 
        fprintf(fp,"%i\n", saved_window_posX);
        fprintf(fp,"%i\n", saved_window_posY); 
		fprintf(fp,"%i\n", RENDERER);
		fprintf(fp,"%i\n", VG_VS_TIME);  
		fprintf(fp,"%i\n", VG_VS_HEALTH);
		fprintf(fp,"%i\n", VG_VS_BG);
		fprintf(fp,"%i\n", VG_DUELLISTS_UNLOCKED);	  
		fprintf(fp,"%i\n", VG_TURBO_UNLOCKED);		
		fprintf(fp,"%i\n", VG_MASTER_UNLOCKED);		
        fprintf(fp,"%i\n", temp_lowres);            // bool

		for(int i =0 ;i< 12;i++)
		{
			if(VG_CHARACTER_LOCKS[i] < 0 || VG_CHARACTER_LOCKS[i] > 1)
				VG_CHARACTER_LOCKS[i]=0;

			fprintf(fp,"%i\n", VG_CHARACTER_LOCKS[i]);
		}

            
    fclose(fp);  

    }

	nn::fs::Commit("save");
#elif defined PS4 || defined XB1 || defined DREAMCAST
	SAFE_BOOL2INT(fullscreen, temp_fullscreen);
	SAFE_BOOL2INT(VG_HIRES_BACKGROUNDS, temp_lowres);

	
	ptr_offset = 0;

	//fread(&music_volume, 1, sizeof(float), fp);
	memcpy(byte_to_sav + ptr_offset, &music_volume, sizeof(float));
	ptr_offset += sizeof(float);

	//fread(&sfx_volume, 1, sizeof(float), fp);
	memcpy(byte_to_sav + ptr_offset, &sfx_volume, sizeof(float));
	ptr_offset += sizeof(float);

	//fread(&sc_width, 1, sizeof(int), fp);
	memcpy(byte_to_sav + ptr_offset, &sc_width, sizeof(int));
	ptr_offset += sizeof(int);

	//fread(&sc_height, 1, sizeof(int), fp);
	memcpy(byte_to_sav + ptr_offset, &sc_height, sizeof(int));
	ptr_offset += sizeof(int);

	//fread(&sc_bits, 1, sizeof(int), fp);
	memcpy(byte_to_sav + ptr_offset, &sc_bits, sizeof(int));
	ptr_offset += sizeof(int);

	//fread(&sc_ratio, 1, sizeof(float), fp);
	memcpy(byte_to_sav + ptr_offset, &sc_ratio, sizeof(float));
	ptr_offset += sizeof(float);

	//fread(&sc_render_rate, 1, sizeof(int), fp);
	memcpy(byte_to_sav + ptr_offset, &sc_render_rate, sizeof(int));
	ptr_offset += sizeof(int);

	//fread(&temp_fullscreen, 1, sizeof(int), fp);   // Bool
	memcpy(byte_to_sav + ptr_offset, &temp_fullscreen, sizeof(int));
	ptr_offset += sizeof(int);

	//fread(&saved_window_posX, 1, sizeof(int), fp);
	memcpy(byte_to_sav + ptr_offset, &saved_window_posX, sizeof(int));
	ptr_offset += sizeof(int);

	//fread(&saved_window_posY, 1, sizeof(int), fp);
	memcpy(byte_to_sav + ptr_offset, &saved_window_posY, sizeof(int));
	ptr_offset += sizeof(int);

	//fread(&RENDERER, 1, sizeof(int), fp);
	memcpy(byte_to_sav + ptr_offset, &RENDERER, sizeof(int));
	ptr_offset += sizeof(int);

	//fread(&VG_VS_TIME, 1, sizeof(int), fp);
	memcpy(byte_to_sav + ptr_offset, &VG_VS_TIME, sizeof(int));
	ptr_offset += sizeof(int);

	//fread(&VG_VS_HEALTH, 1, sizeof(int), fp);
	memcpy(byte_to_sav + ptr_offset, &VG_VS_HEALTH, sizeof(int));
	ptr_offset += sizeof(int);

	//fread(&VG_VS_BG, 1, sizeof(int), fp);
	memcpy(byte_to_sav + ptr_offset, &VG_VS_BG, sizeof(int));
	ptr_offset += sizeof(int);

	//fread(&VG_DUELLISTS_UNLOCKED, 1, sizeof(int), fp);
	memcpy(byte_to_sav + ptr_offset, &VG_DUELLISTS_UNLOCKED, sizeof(int));
	ptr_offset += sizeof(int);

	//fread(&VG_TURBO_UNLOCKED, 1, sizeof(int), fp);
	memcpy(byte_to_sav + ptr_offset, &VG_TURBO_UNLOCKED, sizeof(int));
	ptr_offset += sizeof(int);

	//fread(&VG_MASTER_UNLOCKED, 1, sizeof(int), fp);
	memcpy(byte_to_sav + ptr_offset, &VG_MASTER_UNLOCKED, sizeof(int));
	ptr_offset += sizeof(int);

	//fread(&temp_lowres, 1, sizeof(int), fp);       // Bool
	memcpy(byte_to_sav + ptr_offset, &temp_lowres, sizeof(int));
	ptr_offset += sizeof(int);

	for (int i = 0; i < 12; i++)
	{
		//fread(&VG_CHARACTER_LOCKS[i], 1, sizeof(int), fp);
		memcpy(byte_to_sav + ptr_offset, &VG_CHARACTER_LOCKS[i], sizeof(int));
		ptr_offset += sizeof(int);
	}

#ifdef PS4
	_Application.dataSave(temp_string.string, (void*)byte_to_sav, 500);
#elif XB1
	std::vector<uint8_t> dataVEC;
	for (int i = 0; i < 500; i++)
		dataVEC.push_back(byte_to_sav[i]);

	XB1_WriteSave("Verdict_Guilty_Save", temp_string.string, dataVEC);
#elif DREAMCAST
	save_to_vmu(byte_to_sav, 500);
	free(byte_to_sav);
#endif

	checksave_music_volume = music_volume;
	checksave_sfx_volume = sfx_volume;
	checksave_sc_width = sc_width;
	checksave_sc_height = sc_height;
	checksave_sc_bits = sc_bits;
	checksave_sc_ratio = sc_ratio;
	checksave_sc_render_rate = sc_render_rate;
	checksave_saved_window_posX = saved_window_posX;
	checksave_saved_window_posY = saved_window_posY;
	checksave_RENDERER = RENDERER;
	checksave_VG_VS_TIME = VG_VS_TIME;
	checksave_VG_VS_HEALTH = VG_VS_HEALTH;
	checksave_VG_VS_BG = VG_VS_BG;
	checksave_VG_DUELLISTS_UNLOCKED = VG_DUELLISTS_UNLOCKED;
	checksave_VG_TURBO_UNLOCKED = VG_TURBO_UNLOCKED;
	checksave_VG_MASTER_UNLOCKED = VG_MASTER_UNLOCKED;

	for (int i = 0; i < 12; i++)
	{
		checksave_VG_CHARACTER_LOCKS[i] = VG_CHARACTER_LOCKS[i];
	}
#endif
    
    return(success);    
    
}  

// ******************************************************************************//
//                                                                               //
//                          LOAD ANIMATED TEXTURE                                //
//                                                                               //
// ******************************************************************************//

int LoadAnim( sString sfilename, int texture_id, int the_tex_id )
{
  
    FILE *fp;
    int holder_fx_id=0;
  
    strcat(sfilename.string,".dat"); 
    
//    fp = fopen(sfilename.string, "r");
#ifndef DREAMCAST
    errno_t err;
#endif

#ifdef SWITCH
	if (strstr(sfilename.string, "rom:") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "rom:/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "r");
		printf("LoadAnim NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#elif PS4
	if (strstr(sfilename.string, "/app0/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "/app0/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "r");
		//printf("LoadAnim NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#elif XB1
	if (strstr(sfilename.string, "./Assets/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "./Assets/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "r");
		//printf("LoadAnim NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#elif DREAMCAST
	if (strstr(sfilename.string, "cd/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "cd/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "r");
		//printf("LoadAnim NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#endif
		for (int i = 0; sfilename.string[i]; i++) {
			sfilename.string[i] = tolower(sfilename.string[i]);
		}
		fp = fopen(sfilename.string, "r");
		//printf("LoadAnim NO CONVERSION : %s\n", sfilename.string);

	}

        
    if(the_tex_id==-1) 
    {      
		if(g_fx_id >= 0 && g_fx_id < 75)
	        a_texture[g_fx_id].id = texture_id; // Linked to this texture
        holder_fx_id=g_fx_id;
    }
    else 
    {
		if(the_tex_id >= 0 && the_tex_id < 75)
			a_texture[the_tex_id].id = texture_id; // Linked to this texture
        holder_fx_id=the_tex_id;        
    }
#ifdef SWITCH       
    if ((err==NULL) && holder_fx_id >= 0 && holder_fx_id < 75)
#elif PS4
	if ((fp != NULL) && holder_fx_id >= 0 && holder_fx_id < 75)
#elif XB1
	if ((fp != NULL) && holder_fx_id >= 0 && holder_fx_id < 75)
#elif DREAMCAST
	if ((fp != NULL) && holder_fx_id >= 0 && holder_fx_id < 75)
#endif
    {   


        fscanf(fp, "%f", &a_texture[holder_fx_id].width);                                                      
        fscanf(fp, "%f", &a_texture[holder_fx_id].height);
#ifdef DREAMCAST                                                      
        fscanf(fp, "%hd", &a_texture[holder_fx_id].column); 
        fscanf(fp, "%hd", &a_texture[holder_fx_id].frames);    
        fscanf(fp, "%hd", &a_texture[holder_fx_id].no_of_anims);
        fscanf(fp, "%hd", &a_texture[holder_fx_id].rythm);
        a_texture[holder_fx_id].loaded = 1;
#else
        fscanf(fp, "%i", &a_texture[holder_fx_id].column); 
        fscanf(fp, "%i", &a_texture[holder_fx_id].frames);    
        fscanf(fp, "%i", &a_texture[holder_fx_id].no_of_anims);
        fscanf(fp, "%i", &a_texture[holder_fx_id].rythm);
#endif
        //printf("w %f h %f c %d f %d\n", a_texture[holder_fx_id].width, a_texture[holder_fx_id].height, a_texture[holder_fx_id].column, a_texture[holder_fx_id].frames);

#ifdef DREAMCAST
        a_texture[holder_fx_id].anim_frames = (short*)malloc(sizeof(short) * a_texture[holder_fx_id].no_of_anims);

        for(int j=0;j<a_texture[holder_fx_id].no_of_anims;j++)
		if(j >= 0 && j < 256)
            fscanf(fp, "%hd", &a_texture[holder_fx_id].anim_frames[j] );
        
        a_texture[holder_fx_id].delay = (short*)malloc(sizeof(short) * a_texture[holder_fx_id].frames);

        for(int j=0;j<a_texture[holder_fx_id].frames;j++)
		if(j >= 0 && j < 256)
            fscanf(fp, "%hd", &a_texture[holder_fx_id].delay[j]);

        a_texture[holder_fx_id].anims = (short**)malloc(sizeof(short*) * a_texture[holder_fx_id].no_of_anims);

        //printf("-------- id %d num anim %d num frames %d\n", holder_fx_id, a_texture[holder_fx_id].no_of_anims, a_texture[holder_fx_id].frames);
        for(int j=0;j<a_texture[holder_fx_id].no_of_anims;j++)
        {
        	//printf("-- sub frames size %d\n", a_texture[holder_fx_id].anim_frames[j]);
        	a_texture[holder_fx_id].anims[j] = (short*)malloc(sizeof(short) * a_texture[holder_fx_id].anim_frames[j]);

        	for(int i=0;i<a_texture[holder_fx_id].anim_frames[j];i++)
			if(i >= 0 && i < 256)
			if(j >= 0 && j < 256)
            	fscanf(fp, "%hd", &a_texture[holder_fx_id].anims[j][i]);
    	}

#else

        for(int j=0;j<a_texture[holder_fx_id].no_of_anims;j++)
		if(j >= 0 && j < 256)
            fscanf(fp, "%i", &a_texture[holder_fx_id].anim_frames[j] );

        for(int j=0;j<a_texture[holder_fx_id].frames;j++)
		if(j >= 0 && j < 256)
            fscanf(fp, "%i", &a_texture[holder_fx_id].delay[j]);

        for(int j=0;j<a_texture[holder_fx_id].no_of_anims;j++)
        {
        	for(int i=0;i<a_texture[holder_fx_id].anim_frames[j];i++)
			if(i >= 0 && i < 256)
			if(j >= 0 && j < 256)
            	fscanf(fp, "%i", &a_texture[holder_fx_id].anims[j][i]);
    	}
#endif
       
        fclose(fp);   
                                  
    } 
    
    if(the_tex_id==-1)  
    {
    if(g_fx_id < MAX_FX_ID)
        g_fx_id++;
    
    return (g_fx_id-1);      
    }  
    else
        return(the_tex_id);
} 

#ifdef DREAMCAST
void DeleteAllAnim()
{
	for(int i = 0; i < 75; i++)
	{
		if(a_texture[i].anim_frames != NULL)
		{
			free(a_texture[i].anim_frames);
			a_texture[i].anim_frames = NULL;
		}
		if(a_texture[i].anim_frames != NULL)
		{
			free(a_texture[i].delay);
			a_texture[i].delay = NULL;
		}
		if(a_texture[i].anims != NULL)
		{
			for(int j=0;j<a_texture[i].no_of_anims;j++)
			{
				free(a_texture[i].anims[j]);
			}
			free(a_texture[i].anims);
			a_texture[i].anims = NULL;
		}

		a_texture[i].no_of_anims = 0;
		a_texture[i].column = 0;
		a_texture[i].frames = 0;
		a_texture[i].loaded = 0;
		a_texture[i].id = 0;
		a_texture[i].cur = 0;
		a_texture[i].rythm = 0;

	}

	
}
#endif
// ******************************************************************************//
//                                                                               //
//                                  Load Collision                               //
//                                                                               //
// ******************************************************************************// 

bool Load_COL(  sString sfilename )
{   
    bool success=true;         

    return(success);     
     
} 
   
// ******************************************************************************//
//                                                                               //
//                                  Dump Collision                               //
//                                                                               //
// ******************************************************************************// 

bool Dump_COL( char *filename )
{   
    bool success=true;        
 

    return(success);     
     
}  
   
    
// ******************************************************************************//
//                                                                               //
//                                  LOAD BACKGROUND                              //
//                                                                               //
// ******************************************************************************// 

bool Load_BG(  sString sfilename ) 
{   
    bool success=false;    

    return(success);
}  
  
// ******************************************************************************//
//                                                                               //
//                                  DUMP BACKGROUND                              //
//                                                                               //
// ******************************************************************************// 

bool Dump_BG( char *filename )
{  
    bool success=false;    

    return(success);
}       
// ******************************************************************************//
//                                                                               //
//                                 LOAD POINTS                                   //
//                                                                               //
// ******************************************************************************//

bool LoadPoints( sString sfilename )
{
    bool success=false; 
    FILE *fp;
   
    strcat(sfilename.string,".pt"); 
   
//    fp = fopen(sfilename.string, "r");
#ifndef DREAMCAST
    errno_t err;
#endif


#ifdef SWITCH
	if (strstr(sfilename.string, "rom:") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "rom:/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "r");
		printf("LoadAnim NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#elif PS4
	if (strstr(sfilename.string, "/app0/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "/app0/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "r");
		//printf("LoadPoints NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#elif DREAMCAST
	if (strstr(sfilename.string, "cd/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "cd/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "r");
		//printf("LoadPoints NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#elif XB1
	if (strstr(sfilename.string, "./Assets/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "./Assets/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "r");
		//printf("LoadPoints NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#endif
		for (int i = 0; sfilename.string[i]; i++) {
			sfilename.string[i] = tolower(sfilename.string[i]);
		}
		fp = fopen(sfilename.string, "r");
		//printf("LoadPoints NO CONVERSION : %s\n", sfilename.string);

	}

	//fp = fopen( sfilename.string, "r");

    //if (err!=NULL)
      // MessageBox(NULL,"Couldn't load scene.pnt","ERROR",MB_OK|MB_ICONEXCLAMATION);
#ifdef SWITCH
    if (err==NULL)
#elif PS4
	if(fp != NULL)
#elif XB1
	if (fp != NULL)
#elif DREAMCAST
	if (fp != NULL)
#endif
    {   
		          
	    memset( points, 0, sizeof(a_point)*TOTAL_NO_POINTS ); 

        fscanf(fp, "%i", &no_points);                                                      
        
        for( int i=0; i<no_points;i++)
		if(i >= 0 && i < TOTAL_NO_POINTS)
        {
	        fscanf(fp,"%f", &points[i].x);
	        fscanf(fp,"%f", &points[i].y);
	        fscanf(fp,"%i", &points[i].anim_state);
	        fscanf(fp,"%i", &points[i].anim);
	        fscanf(fp,"%i", &points[i].active);
	        fscanf(fp,"%f", &points[i].speed);
	        fscanf(fp,"%i", &points[i].score);
	        fscanf(fp,"%i", &points[i].c1);	        
	        fscanf(fp,"%i", &points[i].c2);	        
	        fscanf(fp,"%i", &points[i].c3);	        
	        fscanf(fp,"%i", &points[i].c4);	
            
            points[i].active = 0;        
        } 
        fclose(fp);
                      
    }      
    
    return(true);
  
} 
// ******************************************************************************//
//                                                                               //
//                                 DUMP POINTS                                   //
//                                                                               //
// ******************************************************************************//

bool DumpPoints( char *filename )
{
    FILE *fp;
            
    //remove(filename); 
    //fp = fopen (filename, "w");
#ifndef DREAMCAST	  
    errno_t err; 
#endif

	fp = fopen( filename, "w+");
    
    //if (err!=NULL)
        //MessageBox(NULL,"Couldn't dump sceneX.pnt","ERROR",MB_OK|MB_ICONEXCLAMATION);
#ifdef SWITCH
    if (err==NULL)
#elif PS4
	if(fp != NULL)
#elif XB1
	if (fp != NULL)
#elif DREAMCAST
	if (fp != NULL)
#endif
    {   
        fprintf(fp, "%i\n", no_points);                                                      
        
        for( int i=0; i<no_points;i++)
		if(i >= 0 && i < TOTAL_NO_POINTS)
        {
              
	        fprintf(fp,"%f\n", points[i].x);
	        fprintf(fp,"%f\n", points[i].y);
	        fprintf(fp,"%i\n", points[i].anim_state);
	        fprintf(fp,"%i\n", points[i].anim);
	        fprintf(fp,"%i\n", points[i].active);
	        fprintf(fp,"%f\n", points[i].speed);
	        fprintf(fp,"%i\n", points[i].score);
	        fprintf(fp,"%i\n", points[i].c1);	        
	        fprintf(fp,"%i\n", points[i].c2);	        
	        fprintf(fp,"%i\n", points[i].c3);	        
	        fprintf(fp,"%i\n", points[i].c4);	        
	        
        } 

        fclose(fp);
                      
    }      
 
    return(true);
  
}       
// ******************************************************************************//
//                                                                               //
//                                 LOAD NODES                                    //
//                                                                               //
// ******************************************************************************//

bool LoadNodes( sString sfilename )
{
    FILE *fp; 
   
    strcat(sfilename.string,".nde"); 
   
    // fp = fopen(sfilename.string, "r");
#ifndef DREAMCAST
    errno_t err; 
#endif

	//fp = fopen( sfilename.string, "r");

#ifdef SWITCH
	if (strstr(sfilename.string, "rom:") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "rom:/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "rb");
		printf("NODE NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#elif PS4
	if (strstr(sfilename.string, "/app0/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "/app0/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "rb");
		//printf("NODE : %s\n", tempfilename);
	}
	else
	{
#elif DREAMCAST
	if (strstr(sfilename.string, "cd/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "cd/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "rb");
		//printf("NODE : %s\n", tempfilename);
	}
	else
	{
#elif XB1
	if (strstr(sfilename.string, "./Assets/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "./Assets/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "rb");
		//printf("NODE : %s\n", tempfilename);
	}
	else
	{
#endif
		for (int i = 0; sfilename.string[i]; i++) {
			sfilename.string[i] = tolower(sfilename.string[i]);
		}
		fp = fopen(sfilename.string, "r");
		//printf("NODE NO CONVERSION : %s\n", sfilename.string);

	}


    //if (err!=NULL)
    //   MessageBox(NULL,"Couldn't load scene.nde","ERROR",MB_OK|MB_ICONEXCLAMATION);
#ifdef SWITCH        
    if (err==NULL)
#elif PS4
	if(fp != NULL)
#elif XB1
	if (fp != NULL)
#elif DREAMCAST
	if (fp != NULL)
#endif
    {   
		          
		memset( nodes, 0, sizeof(a_point)*TOTAL_NO_NODES );

        fscanf(fp, "%i", &no_nodes);

#if defined (PS4) || defined (XB1)
		if (no_nodes == 0)
		{
			fclose(fp);
			return true;
		}
#endif
        
        for( int i=0; i<no_nodes;i++) 
		if(i >= 0 && i < TOTAL_NO_NODES)
        {
	        fscanf(fp,"%f", &nodes[i].x);
	        fscanf(fp,"%f", &nodes[i].y);
	        fscanf(fp,"%i", &nodes[i].anim_state);
	        fscanf(fp,"%i", &nodes[i].anim);
	        fscanf(fp,"%i", &nodes[i].active);
	        fscanf(fp,"%f", &nodes[i].speed);
	        fscanf(fp,"%i", &nodes[i].score);
	        fscanf(fp,"%i", &nodes[i].c1);	        
	        fscanf(fp,"%i", &nodes[i].c2);	        
	        fscanf(fp,"%i", &nodes[i].c3);	        
	        fscanf(fp,"%i", &nodes[i].c4);	        
        } 

        fclose(fp);
                      
    }      
 
    return true;
  
}
       
// ******************************************************************************//
//                                                                               //
//                                 DUMP NODES                                    //
//                                                                               //
// ******************************************************************************//

bool DumpNodes( char *filename )
{
    FILE *fp; 
            
    //remove(filename); 
    //fp = fopen (filename, "w");
#ifndef DREAMCAST 		  
    errno_t err; 
#endif

	fp  = fopen( filename, "w+");
    
    //if (err!=NULL)
    //    MessageBox(NULL,"Couldn't dump sceneX.nde","ERROR",MB_OK|MB_ICONEXCLAMATION);
#ifdef SWITCH
    if (err==NULL)
#elif PS4
	if(fp != NULL)
#elif XB1
	if (fp != NULL)
#elif DREAMCAST
	if (fp != NULL)
#endif
    {   
        fprintf(fp, "%i\n", no_nodes);                                                      
        
        for( int i=0; i<no_nodes;i++)
		if(i >= 0 && i < TOTAL_NO_NODES)
        {
             
	        fprintf(fp,"%f\n", nodes[i].x);
	        fprintf(fp,"%f\n", nodes[i].y);
	        fprintf(fp,"%i\n", nodes[i].anim_state);
	        fprintf(fp,"%i\n", nodes[i].anim);
	        fprintf(fp,"%i\n", nodes[i].active);
	        fprintf(fp,"%f\n", nodes[i].speed);
	        fprintf(fp,"%i\n", nodes[i].score);
	        fprintf(fp,"%i\n", nodes[i].c1);	        
	        fprintf(fp,"%i\n", nodes[i].c2);	        
	        fprintf(fp,"%i\n", nodes[i].c3);	        
	        fprintf(fp,"%i\n", nodes[i].c4);	        
	        
        } 

        fclose(fp);
                      
    }      
 
    return(true);
  
}           
    
// ******************************************************************************//
//                                                                               //
//                                 LOAD HUD                                      //
//                                                                               //
// ******************************************************************************//

bool LoadHud( char *filename )
{
    FILE *fp;
    int hud_blank=0; // Not used at moment
	int temp_grab_switch=0;
	int temp_mouseover=0;

    //fp = fopen(filename, "r"); 
#ifndef DREAMCAST    		  
    errno_t err; 
#endif

#ifdef SWITCH
	if (strstr(filename, "rom:") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "rom:/%s", filename);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "rb");
		printf("NODE NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#elif PS4
	if (strstr(filename, "/app0/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "/app0/%s", filename);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "rb");
		//printf("HUD : %s\n", tempfilename);
	}
	else
	{
#elif DREAMCAST
	if (strstr(filename, "cd/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "cd/%s", filename);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "rb");
		//printf("HUD : %s\n", tempfilename);
	}
	else
	{
#elif XB1
	if (strstr(filename, "./Assets/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "./Assets/%s", filename);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "rb");
		//printf("HUD : %s\n", tempfilename);
	}
	else
	{
#endif
		for (int i = 0; filename[i]; i++) {
			filename[i] = tolower(filename[i]);
		}
		fp = fopen(filename, "r");
		//printf("HUD NO CONVERSION : %s\n", filename);

	}


	//fp  = fopen( filename, "r");
                
    //if (err!=NULL)
    //    MessageBox(NULL,"Couldn't load hud.dat","ERROR",MB_OK|MB_ICONEXCLAMATION);
#ifdef SWITCH    
    if (err==NULL)
#elif PS4
	if(fp != NULL)
#elif XB1
	if (fp != NULL)
#elif DREAMCAST
	if (fp != NULL)
#endif
    {   
        fscanf(fp, "%i", &hud_blank);                                                      
        fscanf(fp, "%i", &hud_no_sprites);
        fscanf(fp, "%i", &hud_blank);
        fscanf(fp, "%i", &hud_blank);
        fscanf(fp, "%i", &hud_blank);
        fscanf(fp, "%i", &hud_blank);
        fscanf(fp, "%i", &hud_blank);
        fscanf(fp, "%i", &hud_blank);
        fscanf(fp, "%i", &hud_blank);
                          
        for( int i=0; i<hud_no_sprites;i++)
		if(i >= 0 && i < TOTAL_NO_HUD)
        {
	        fscanf(fp,"%f", &hud[i].x);
	        fscanf(fp,"%f", &hud[i].y);
            
	        fscanf(fp,"%f", &hud[i].width);
	        fscanf(fp,"%f", &hud[i].height);
	        
	        fscanf(fp,"%f", &hud[i].w);
	        fscanf(fp,"%f", &hud[i].z);
            
	        fscanf(fp,"%f", &hud[i].box_width);
	        fscanf(fp,"%f", &hud[i].box_height);
             	        
	        for ( int j=0;j<4;j++)
	        {
	            fscanf(fp,"%f", &hud[i].u[j]);
	            fscanf(fp,"%f", &hud[i].v[j]);
            } 

	        fscanf(fp,"%i", &hud[i].id);

			if( hud[i].id >= 0 && hud[i].id < 200)
	        if( texture_fx[hud[i].id] == 2 || texture_fx[hud[i].id] == 3 || texture_fx[hud[i].id] == 4)
	           hud[i].fx_id = animation_fx[hud[i].id];
	           
	        fscanf(fp,"%i", &hud_blank);
            fscanf(fp,"%i", &hud[i].anim_state);
            fscanf(fp,"%i", &hud[i].anim); 
            fscanf(fp,"%f", &hud[i].alpha);
            fscanf(fp,"%i", &hud[i].linked_sprite); 
   	        fscanf(fp,"%i", &hud[i].priority);
	        fscanf(fp,"%i", &hud[i].type);
	        fscanf(fp,"%i", &temp_grab_switch); // Bool
	        fscanf(fp,"%i", &temp_mouseover);   // Bool 
	        fscanf(fp,"%i", &hud[i].sector);
	        fscanf(fp,"%i", &hud[i].sector_action);
	        fscanf(fp,"%i", &hud[i].onCreate);
	        fscanf(fp,"%i", &hud[i].onCreate_action);
	        fscanf(fp,"%i", &hud[i].rank);
	        fscanf(fp,"%i", &hud[i].onDeath_action);
	        fscanf(fp,"%f", &hud[i].light); 
		    fscanf(fp,"%i", &hud[i].global_flag); 

			SAFE_INT2BOOL(temp_grab_switch, hud[i].grab_switch);
			SAFE_INT2BOOL(temp_mouseover, hud[i].mouseover);
            
            if(hud[i].anim > LIMIT_ANIMS)
                hud[i].anim = 0;
            if(hud[i].anim < 0)
                hud[i].anim = 0;
            
            if(hud[i].cur > LIMIT_FRAMES)
                hud[i].cur = 0;
            if(hud[i].cur < 0) 
                hud[i].cur = 0; 
            
            if(hud[i].fx_id > MAX_FX_ID)
                hud[i].fx_id = 0;
            if(hud[i].fx_id < 0)
                hud[i].fx_id = 0;                
            
			hud[i].base_anim = hud[i].anim;
             	        
        }  

        fclose(fp);
                
    }   
    
   return(true);
  
} 

// ******************************************************************************//
//                                                                               //
//                                LOAD SCENE                                     //
//                                                                               //
// ******************************************************************************//

bool LoadScene( int episode1, int scene1, bool delete_textures )
{ 
#if defined PS4 || defined XB1 || (defined DREAMCAST && !defined SATURN)
	if (CheckCFG())
	{
		SaveCFG();
	}
#endif
#if defined DREAMCAST && !defined SATURN
	printf("Load Scene %d %d\n", episode1, scene1);
	if((episode1 == 0 && scene1 == 1) || (episode1 == 1 && scene1 == 4) || (episode1 == 1 && scene1 == 3) || (episode1 == 1 && scene1 == 2) || (episode1 == 1 && scene1 == 5)
		|| (episode1 == 1 && scene1 == 1) || (episode1 == 1 && scene1 == 0) || (episode1 == 0 && scene1 == 0) || (episode1 == 10 && scene1 == 0))
	{
		printf("no loading screen");
	}
	else
	{
		Loading_Time_Draw();

	}
#endif
    FILE *fp;
#ifndef DREAMCAST
	errno_t err; 
#endif
    bool temp=false;
    int rnd=0;
    int rnd1=0;
    // All for assigning bins a pku
    int index=0;
    int itemp=0;
    int draw_counter=0;
    int key_counter=0;
    int tied_counter=0; 
    int temp_p1_count=0;
    int temp_p2_count=0;
    float mid_x=0.0, mid_y=0.0;
    float the_difference=0.0;
    int row_x=0, row_y=0;
    int item_value  = 0; 
    int item_type   = 0; 
    int item_value1 = 0;    
    int count=0;     
	int free_spawn_point=-1;
    bool loaded_temp=false; 
    int col_type = 0;
    bool skip_this = false; 
    bool next_scene_stats=false;
	int furniture_count=0;       
	int temp_grab_switch=false;   
	int temp_mouseover=false;  
	int spawn_emy_number=0;  
	bool sta2_all_dogs=false;
	bool sta2_is_final_battle = false; 
	bool skip_textures = false;


	if(TEST_ALTERS == 1)
		VG_IS_AN_ALTER = true;

	if(VG_GAME_MODE != VG_STORY_MODE) 
	{
		if(VG_GAME_MODE != VG_VERSUS_MODE) 
		if(VG_1_CHARACTER == VG_2_CHARACTER && VG_IS_AN_ALTER_P1 == false)
			VG_IS_AN_ALTER = true;
		else
			VG_IS_AN_ALTER = false;

		if(VG_GAME_MODE == VG_VERSUS_MODE)
		if(VG_IS_AN_ALTER_P2 == true)
			VG_IS_AN_ALTER = true;
		else
			VG_IS_AN_ALTER = false;

	}

	// For displaying Versus screen moveslists...
	VG_MOVES_VS = false;

	// Turn/off all ambience sounds... 
	if(episode != 5)
	{ 
		stop_vg_amb_prison_sfx = true;
		stop_vg_amb_traffic_sfx = true;
		stop_vg_amb_subway_sfx = true;
		stop_vg_amb_duel_sfx = true;
	} 
	else
		VG_played_title = -1; // Reset title logo anim...

	CHANGE_SONG_SPEED = 0;

//	VG_change_pitch = true;
//	VG_changed_pitch = false;
//	VG_pitch = 1.0f;  

	scroll_txt_active = false;

	scroll_txt_timer = 0;

	VG_STORY_PAUSE = false;

	flash_helptext_timer = 0;
	flash1_helptext_timer = 0;

	VG_1_DEFEATED_BY_BOMB = false;
	VG_2_DEFEATED_BY_BOMB = false;
	
	VG_1_ACID_TIMER = 0;
	VG_2_ACID_TIMER = 0;

	VG_1_DIZZY_TIMER = 0;
	VG_2_DIZZY_TIMER = 0;

	vg_judge_sfx = false;

	flash_helptext_timer = 0;

	VG_arrested_sfx = false;
	VG_wasted_sfx = false;

	vg_vacuum_sfx=false;

	VG_arcade_sequence = 0;

	VG_SHAKE_CAMERA = false;
	VG_SHAKE_UP = 0;
	VG_shake_timer = 0;
	VG_shake_length_timer = 0;

	VG_1_HANDCUFFED_TIMER = 0;
	VG_2_HANDCUFFED_TIMER = 0;

	VG_1_HANDCUFFED = 0;
	VG_2_HANDCUFFED = 0;

	VG_handcuffs_sfx = false;

	VG_1_HAS_THROW = true;
	VG_2_HAS_THROW = true;

	VG_1_THROW_TIMER = 0;
	VG_2_THROW_TIMER = 0;

	VG_1_THROWING = false;
	VG_2_THROWING = false;

	VG_1_THROWING_SEQUENCE = 0;
	VG_2_THROWING_SEQUENCE = 0;

	VG_1_Knifesfx = 0;
	VG_2_Knifesfx = 0;

	VG_PLAYER_1_PAUSED = false;

	VG_pause_button_timer = 0;

	VG_power_sfx = false;

	VG_DOG1_trail_timer = 0;
	VG_DOG2_trail_timer = 0;

	VG_1_trail_timer = 0;
	VG_2_trail_timer = 0;

	VG_flash_win_timer_total = 0;
	VG_flash_win_player = 0;
	VG_flash_win_timer = 0;

	VG_WIND_BLOWING = WIND_STOPPED;
	VG_WIND_TIMER = 0;

	VG_1_STRIKE_TIMER = 0;
	VG_2_STRIKE_TIMER = 0;

	VG_page_no = 0;

	VG_played_title = -1; // temp...
	 
	// Turn off any sound effects playing...

	VG_knockslide_sfx = false;
	VG_pow_sfx = false;
	VG_titlevoice_sfx = false;

	vg_pause_sfx = false;
	vg_explode_sfx = false;
	vg_title_move_sfx=false;
	vg_titlemove_sfx=false;
	vg_fight_sfx = false;
	vg_titleselect_sfx = false;
	vg_hitsound_sfx  = false;
	vg_shock_sfx=false; 
	VG_handcuffs_sfx = false;
	vg_amb_prison_sfx = false;
	vg_amb_traffic_sfx = false;
	vg_amb_van_sfx = false;

	vg_amb_car1_sfx = false;
	vg_amb_car2_sfx = false;

	vg_siren_sfx=false;
	vg_shout_sfx=false;
	vg_win_sfx=false;
	VG_verdict_sfx = false;
	VG_guilty_sfx = false;
	vg_stamp_sfx = false;
	vg_splat_sfx = false;
	vg_tink_sfx = false;
	vg_glass_sfx = false;
	vg_dogattack_sfx = false;
	vg_ric_sfx = false;
	vg_round_sfx=false;
	vg_gameover_sfx = false;

	VG_KO_sfx = false;
	vg_lose_sfx = false;
	VG_power_sfx = false;
	VG_arrested_sfx = false;
	VG_wasted_sfx = false;

	vg_perfect_sfx = false;
	vg_ko_smash_sfx   = false;
	vg_amb_subway_sfx = false;
	vg_blocked_sfx=false;
	VG_title_sfx = false;
	VG_destiny_sfx = false;

	VG_alright_sfx = false;
	VG_nice_sfx = false;
	VG_okay_sfx = false;
	VG_good_sfx = false;
	VG_great_sfx = false;
	VG_excellent_sfx = false;


	VG_victory_sfx = -1;
	VG_yell_sfx = -1;

	VG_displaying_win = false;

	VG_1_hits = 0;
	VG_2_hits = 0;

	VG_1_hits_timer = 0;
	VG_2_hits_timer = 0;

	VG_1_display_hit = false;
	VG_2_display_hit = false;

	VG_1_display_hit_timer = 0;
	VG_2_display_hit_timer = 0;

	VG_start_timer = 0;

	VG_1_CORNERED = false;
	VG_2_CORNERED = false;

	VG_SHAKE_1 = false;
	VG_SHAKE_2 = false;

	VG_1_ARM_LENGTH = false;
	VG_2_ARM_LENGTH = false;

	VG_KO_sfx = false;

	VG_1_chop_sfx = 0;
	VG_2_chop_sfx = 0;

	VG_reloadsfx = 0;
	VG_reloadedsfx = 0;

	VG_1_cur = 0;
	VG_2_cur = 0;

	VG_1_Pistolsfx = 0;
	VG_2_Pistolsfx = 0;

	VG_1_Mgunsfx = 0;
	VG_2_Mgunsfx = 0;

	VG_1_Vialsfx = 0;
	VG_2_Vialsfx = 0;

	VG_1_Pfpsfx = 0;         
	VG_2_Pfpsfx = 0; 

	VG_1_Grenadesfx = 0;
	VG_2_Grenadesfx = 0;

	VG_P2_AI_PUNCH1_KEY = false; 
	VG_P2_AI_KICK1_KEY = false;     
	VG_P2_AI_KICK2_KEY = false;       
	VG_P2_AI_PUNCH2_KEY = false;   

	VG_P2_AI_THROW_KEY = false;
	VG_P2_AI_BLOCK_KEY = false;

	VK_KEY_AI_SPECIAL1 = false;

	VG_1_MOVE_ACTIVE = false;
	VG_2_MOVE_ACTIVE = false;

	VG_1_MovesList_count = 0;
	VG_2_MovesList_count = 0;

	VG_1_Moves_count = 0;
	VG_2_Moves_count = 0;

	VG_1_MovesList_timer = 0;
	VG_2_MovesList_timer = 0;

	VG_1_DEFEATED = false;
	VG_2_DEFEATED = false;

	VG_finished_round = false;

	VG_1_JUMPBOX = 0;
	VG_2_JUMPBOX = 0;

	VG_1_DX_UP = false;
	VG_1_DX_DOWN = false;
	VG_1_DX_LEFT = false;
	VG_1_DX_RIGHT = false;

	VG_1_DX_A = false;
	VG_1_DX_B = false;
	VG_1_DX_X = false;
	VG_1_DX_Y = false;

	VG_1_DX_LS = false;
	VG_1_DX_RS = false;

	VG_1_DX_START = false;
	VG_1_DX_BACK = false;

	VG_2_DX_UP = false;
	VG_2_DX_DOWN = false;
	VG_2_DX_LEFT = false;
	VG_2_DX_RIGHT = false;

	VG_2_DX_A = false;
	VG_2_DX_B = false;
	VG_2_DX_X = false;
	VG_2_DX_Y = false;
	 
	VG_2_DX_LS = false;
	VG_2_DX_RS = false;

	VG_2_DX_START = false;
	VG_2_DX_BACK = false;

	VG_ESC_pressed = false;
	VG_1_pressed = false;
	VG_2_pressed = false;
	VG_3_pressed = false;

	VG_Display_moves=false;

	VG_1_HEALTH = STARTING_HEALTH;
	VG_2_HEALTH = STARTING_HEALTH;

	screen_limit = 1.1f;
	VG_SCREEN_EDGE = 0.65f;

	VG_DONT_MOVE_CAMERA = false;

	VG_1_MOVE_ACTIVE = false;
	VG_2_MOVE_ACTIVE = false; 

	VG_SHAKE_timer=0;
	VG_SHAKE_LEFT = false;
	VG_land_sfx = false;

	VG_SLOWMO = false;
	VG_slowmof = 1.0f;
	VG_Reset_all_anims();
	VG_slowmo_timer = 0;

	VG_LAYER1_X = 0.0f;
	VG_START_Y = 0.0f;
	VG_JUMP_HEIGHT = 0.4f;

	VG_1_current_timestamp=0;
	VG_1_update_dump=false;

	VG_2_current_timestamp=0; 
	VG_2_update_dump=false;

	VG_RESET_key_timer=0;

	VG_1_current_timestamp = -1;
	VG_1_MovesList_timer = -1;

	VG_land_sfx = false;

	VG_1_HUDDOWN = false;
	VG_1_HUDUP = false;
	VG_1_HUDLEFT = false;
	VG_1_HUDRIGHT = false;

	VG_2_HUDDOWN = false;
	VG_2_HUDUP = false;
	VG_2_HUDLEFT = false;
	VG_2_HUDRIGHT = false;

	VG_1_HUD_GO   = false;
	VG_1_HUD_BACK = false;

	VG_2_HUD_GO   = false;
	VG_2_HUD_BACK = false;

	VG_1_LEFT_pressed  = false; 
	VG_1_RIGHT_pressed = false; 
	VG_1_UP_pressed = false; 
	VG_1_DOWN_pressed = false; 

	VG_2_LEFT_pressed  = false; 
	VG_2_RIGHT_pressed = false; 
	VG_2_UP_pressed = false; 
	VG_2_DOWN_pressed = false; 

	VG_HUD_ESC = false;

	VG_1_HUDDOWN = false;
	VG_1_HUDUP = false;
	VG_1_HUDLEFT = false;
	VG_1_HUDRIGHT = false;

	VG_2_HUDDOWN = false;
	VG_2_HUDUP = false;
	VG_2_HUDLEFT = false;
	VG_2_HUDRIGHT = false;

	VG_1_PUNCH = VG_RESET;
	VG_1_PUNCH2 = VG_RESET;
	VG_1_KICK = VG_RESET;
	VG_1_KICK2 = VG_RESET;

	VG_1_BLOCK = VG_RESET;
	VG_1_THROW = VG_RESET;

	VG_2_PUNCH = VG_RESET;
	VG_2_PUNCH2 = VG_RESET;
	VG_2_KICK = VG_RESET;
	VG_2_KICK2 = VG_RESET;

	VG_2_BLOCK = VG_RESET;
	VG_2_THROW = VG_RESET;

	keys['A'] = false;
	keys['S'] = false;
	keys['W'] = false;
	keys['D'] = false;
	keys['K'] = false;
	keys['L'] = false;
	keys['M'] = false;
	//keys[VK_OEM_COMMA] = false;

	keys[VK_UP] = false;
	keys[VK_LEFT] = false;
	keys[VK_RIGHT] = false;
	keys[VK_DOWN] = false;
	keys['Z'] = false;
	keys['X'] = false;
	keys['C'] = false;
	keys['V'] = false;

	VG_P2_AI_UP_KEY = false;
	VG_P2_AI_DOWN_KEY = false; 
	VG_P2_AI_LEFT_KEY = false;
	VG_P2_AI_RIGHT_KEY = false;

	VG_P2_AI_PUNCH1_KEY = false;
	VG_P2_AI_PUNCH2_KEY = false;
	VG_P2_AI_KICK1_KEY = false;
	VG_P2_AI_KICK2_KEY = false;

	memset(keys, false, sizeof(keys));

	VG_ESC_pressed = false;

    camX_OFFSET = 0.0; 
    camY_OFFSET = 0.0;



	game_paused=false;     

    sprintf( temp_string.string, "scene/episode%i/scene%i", episode1, scene1);

	if (!LoadTextures(temp_string, delete_textures))  	  						
	{
		//MessageBox(NULL,"Couldn't load GLTextures","ERROR",MB_OK|MB_ICONEXCLAMATION);                              
		return false;   
	}      	
    if (!LoadPoints(temp_string))
    {
        //MessageBox(NULL,"Couldn't load points","ERROR",MB_OK|MB_ICONEXCLAMATION);                              
        return false;
    } 
    if (!LoadNodes(temp_string))
    {
        //MessageBox(NULL,"Couldn't load nodes","ERROR",MB_OK|MB_ICONEXCLAMATION);                              
        return false;
    }    
    if (!LoadText(temp_string))  
    {  
        //MessageBox(NULL,"Couldn't load text file","ERROR",MB_OK|MB_ICONEXCLAMATION);                              
        return false;      
    }          
    if(episode1 == 2 || episode1 == 3 || episode1 == 4)   
    if (!Load_BG(temp_string))     
    {
        //MessageBox(NULL,"Couldn't load sceneX.bg","ERROR",MB_OK|MB_ICONEXCLAMATION);                              
        return false;                              
    }           

    no_fx=0;

    memset(Fx, 0, sizeof(object)*TOTAL_NO_FX_SPRITES ); 

	#if INCLDUE_360_CONTROLLER == 1 
#ifdef XB1
	ZeroMemory(&state, sizeof(XINPUT_STATE_CUSTOM));
	ZeroMemory(&DX_vibration, sizeof(XINPUT_VIBRATION_CUSTOM));
#endif // XB1

    

	#endif

    music_reset = false;

	fade_timer = 0; 
	render_bg  = 0;

    KEY_SPACE    = false;
	 
    new_renderer=RENDER_DEFAULT;

    selection=0;
    pt_selection=0;
    nde_selection=0;    

    quitting=false;

    title_sequence = 0; 
    title_timer = 0;

	start_timer = 0;
    start_sequence = 0;


    changed_video = false;
	changed_renderer = false;



    double_main_code = 0;


    mouseleft = false;
    mouseheld = false; 

    camX_OFFSET = 0.0f;
    camY_OFFSET = 0.0f;

	vg_tink_sfx = false;
	vg_splat_sfx = false;
	vg_lose_sfx = false;


	vg_knockdown_sfx=false;
    vg_blocked_sfx=false;
    vg_titlemove_sfx=false;
 	vg_round_sfx=false;

    vg_amb_car1_sfx = false; 
    vg_amb_car2_sfx = false;
    vg_amb_subway_sfx = false;
    vg_ko_smash_sfx = false;

    vg_fight_sfx = false; 

    text_active = false;


    vg_glass_sfx = false;

    vg_titleselect_sfx = false;

    vg_hitsound_sfx  = false;

    vg_stamp_sfx   = false; 

    vg_siren_sfx=false;

    temp_music_volume = 0.0; 
    temp_sfx_volume   = 0.0; 
    fade_increment    = 0.0;
    
    fade_out_volume   = music_volume;
    fade_in_volume    = 0.0; 
    
    music_fade = true;  
    
    stop_music = false;
    
    old_song = current_song; 
    
    old_music_loop = music_loop;
       
    end_sfx=NO_ANIM;
    jet_sfx=NO_ANIM;
    siege_sfx=NO_ANIM;
    theatre_sfx=NO_ANIM;
    credits_sfx=NO_ANIM;
    war_sfx=NO_ANIM;
    lnd_sfx=NO_ANIM;
    crd_sfx=NO_ANIM; 
    army_sfx=NO_ANIM; 
    fight_sfx=NO_ANIM;
    sad_sfx=NO_ANIM;
    intro_sfx=NO_ANIM;
    mini_sfx=NO_ANIM;    
    urgency_sfx=NO_ANIM;  
    dgnb_sfx = NO_ANIM;
    final_sfx = NO_ANIM;
    dangers_sfx = NO_ANIM; 
    fanfare_sfx = NO_ANIM;  
    fanfare2_sfx = NO_ANIM;
    deathscreen_sfx = NO_ANIM; 

	
	sprintf( temp_string.string, "scene/episode%i/scene%i.dat", episode1, scene1);

#ifdef SWITCH
	if (strstr(temp_string.string, "rom:") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "rom:/%s", temp_string.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "r");
		printf("LoadAnim NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#elif PS4
	if (strstr(temp_string.string, "/app0/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "/app0/%s", temp_string.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "r");
		//printf("LoadScene: %s\n", tempfilename);
	}
	else
	{
#elif DREAMCAST
	if (strstr(temp_string.string, "cd/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "cd/%s", temp_string.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "r");
		//printf("LoadScene: %s\n", tempfilename);
	}
	else
	{
#elif XB1
	if (strstr(temp_string.string, "./Assets/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "./Assets/%s", temp_string.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fp = fopen(tempfilename, "r");
		//printf("LoadScene: %s\n", tempfilename);
	}
	else
	{

#endif
		for (int i = 0; temp_string.string[i]; i++) {
			temp_string.string[i] = tolower(temp_string.string[i]);
		}
		fp = fopen(temp_string.string, "r");
		//printf("LoadScene NO CONVERSION : %s\n", temp_string.string);
	}

	//fp  = fopen( temp_string.string, "r");
	                
    //if (err!=NULL) 
    //   MessageBox(NULL,"Couldn't load sceneX.dat","ERROR",MB_OK|MB_ICONEXCLAMATION);
#ifdef SWITCH
    if(err==NULL)
#elif PS4
	if(fp != NULL)
#elif XB1
	if (fp != NULL)
#elif DREAMCAST
	if (fp != NULL)
#endif
    {   
		
        fscanf(fp, "%i", &game_mode);  

		game_mode = FRONT;

        fscanf(fp, "%i", &no_sprites);
        fscanf(fp, "%i", &no_of_keyframes);
        fscanf(fp, "%i", &game_time);
        fscanf(fp, "%i", &fade_in);
        fscanf(fp, "%i", &fade_out);
        fscanf(fp, "%i", &scene_shake);
        fscanf(fp, "%i", &music_loop);
        fscanf(fp, "%i", &g_type);

        for( int i=0; i < no_sprites;i++)
		if(i >= 0 && i < TOTAL_NO_SPRITES)
        {
	        fscanf(fp,"%f", &sprite[i].x);
	        fscanf(fp,"%f", &sprite[i].y);
	        fscanf(fp,"%f", &sprite[i].width);
	        fscanf(fp,"%f", &sprite[i].height);
	        
	        fscanf(fp,"%f", &sprite[i].w);
	        fscanf(fp,"%f", &sprite[i].z);
	        fscanf(fp,"%f", &sprite[i].box_width);
	        fscanf(fp,"%f", &sprite[i].box_height);
	        
	        for ( int j=0;j<4;j++)
	        {
	            fscanf(fp,"%f", &sprite[i].u[j]);
	            fscanf(fp,"%f", &sprite[i].v[j]);
            }

	        fscanf(fp,"%i", &sprite[i].id);

			if( sprite[i].id >= 0 && sprite[i].id < 200)
	        if( texture_fx[sprite[i].id] == 2 || texture_fx[sprite[i].id] == 3 || texture_fx[sprite[i].id] == 4 )
	           sprite[i].fx_id = animation_fx[sprite[i].id];
	           
	        fscanf(fp,"%i", &sprite[i].score);
	        fscanf(fp, "%i", &sprite[i].anim_state);
	        fscanf(fp,"%i", &sprite[i].anim);
	        fscanf(fp,"%f", &sprite[i].alpha);
	        fscanf(fp,"%i", &sprite[i].linked_sprite);
	        fscanf(fp,"%i", &sprite[i].priority);
	        fscanf(fp,"%i", &sprite[i].type);
	        fscanf(fp,"%i", &temp_grab_switch); // Bool
	        fscanf(fp,"%i", &temp_mouseover);   // Bool
	        fscanf(fp,"%i", &sprite[i].sector);
	        fscanf(fp,"%i", &sprite[i].sector_action); 
	        fscanf(fp,"%i", &sprite[i].onCreate);
	        fscanf(fp,"%i", &sprite[i].onCreate_action);
	        fscanf(fp,"%i", &sprite[i].rank);
	        fscanf(fp,"%i", &sprite[i].onDeath_action);
	        fscanf(fp,"%f", &sprite[i].light);		        
            fscanf(fp,"%i", &sprite[i].global_flag);

			SAFE_INT2BOOL(temp_grab_switch, sprite[i].grab_switch);
			SAFE_INT2BOOL(temp_mouseover, sprite[i].mouseover);
            
            sprite[i].base_anim = sprite[i].anim;
            sprite[i].deflect = false;
			sprite[i].cur_start_time = 0;
			sprite[i].cur_dest_time = 0;
			sprite[i].was_knocked_down = false;
			sprite[i].last_slowmo = 0.0f;
			sprite[i].bump_this = false;
			sprite[i].bump_this_timer = 0;

			sprite[i].handcuffed = false;
			sprite[i].dizzy = false;
			sprite[i].acid = false;
			sprite[i].strafe = false;
			sprite[i].spin_strafe = false;

        } 

        fclose(fp);      
    
    }       

	// ********************************************************* // 
	// Put code here after loading this scene                    //
	// ********************************************************* // 

    original_no_sprites = no_sprites;
         
    if(mode)
        mode = PLACEMENT;
        
    continue_song = false; 
      
    current_song = SONG_NONE; 
     
    half_volume=false; 

	if(!mode)
	if(episode == 6 && scene == 1)
	if(VG_AI_active == true && vg_selected_character == true)
    if(music_loop == SND_CRD) 
    {
		music_loop = SND_NON;
        current_song = SONG_NONE;
    }   
	
    if(music_loop == SND_END)
    {
        end_sfx=PLAY;
        current_song = SONG_END;
        
        if(old_song != current_song)          
            end_sfx=FADE_IN;
    }        
    if(music_loop == SND_JET)
    {
        jet_sfx=PLAY;
        current_song = SONG_JET;
        
        if(old_song != current_song)          
            jet_sfx=FADE_IN;        
    }    
    if(music_loop == SND_SIEGE)
    {
        siege_sfx=PLAY;
        current_song = SONG_SIEGE;
        
        if(old_song != current_song)          
            siege_sfx=FADE_IN;        
    }     
    if(music_loop == SND_THEATRE)
    {
        theatre_sfx=PLAY;
        current_song = SONG_THEATRE;
        
        if(old_song != current_song)          
            theatre_sfx=FADE_IN;        
    }  
    if(music_loop == SND_CREDITS)
    {
        credits_sfx=PLAY;
        current_song = SONG_CREDITS;
        
        if(old_song != current_song)          
            credits_sfx=FADE_IN;        
    }             
    if(music_loop == SND_WAR)
    {
        war_sfx=PLAY;
        current_song = SONG_WAR;
        
        if(old_song != current_song)           
            war_sfx=FADE_IN;        
    }        
    if(music_loop == SND_LND)  
    {
        lnd_sfx=PLAY;
        current_song = SONG_LND;
        
        if(old_song != current_song)          
            lnd_sfx=FADE_IN;         
    }        
    if(music_loop == SND_CRD)
    {
        crd_sfx=PLAY;
        current_song = SONG_CRD;
        
        if(old_song != current_song)          
            crd_sfx=FADE_IN;         
    }        
    if(music_loop == SND_ARMY)
    {
        army_sfx=PLAY; 
        current_song = SONG_ARMY;
        
        if(old_song != current_song)          
            army_sfx=FADE_IN;         
    }        
    if(music_loop == SND_FIGHT)
    {
        fight_sfx=PLAY;
        current_song = SONG_FIGHT;
        
        if(old_song != current_song)          
            fight_sfx=FADE_IN;         
    }        
    if(music_loop == SND_SAD)
    { 
        sad_sfx=PLAY;  
        current_song = SONG_SAD;
        
        if(old_song != current_song)          
            sad_sfx=FADE_IN;         
    }   
    if(music_loop == SND_INTRO) 
    { 
        intro_sfx=PLAY;   
        current_song = SONG_INTRO;
        
        if(old_song != current_song)          
            intro_sfx=FADE_IN;         
    }  
    if(music_loop == SND_MINI) 
    { 
        mini_sfx=PLAY;   
        current_song = SONG_MINI;
        
        if(old_song != current_song)          
            mini_sfx=FADE_IN;         
    }      
    if(music_loop == SND_URGENCY) 
    { 
        urgency_sfx=PLAY;   
        current_song = SONG_URGENCY;
        
        if(old_song != current_song)          
            urgency_sfx=FADE_IN;         
    }      
    if(music_loop == SND_FANFARE) 
    { 
        fanfare_sfx=PLAY;   
        current_song = SONG_FANFARE;
        
        if(old_song != current_song)          
            fanfare_sfx=FADE_IN;         
    } 
    if(music_loop == SND_FANFARE2) 
    { 
        fanfare2_sfx=PLAY;   
        current_song = SONG_FANFARE2;
        
        if(old_song != current_song)          
            fanfare2_sfx=FADE_IN;         
    } 
    if(music_loop == SND_DEATH) 
    { 
        deathscreen_sfx=PLAY;   
        current_song = SONG_DEATH;
        
        if(old_song != current_song)          
            deathscreen_sfx=FADE_IN;         
    }                         
    if(music_loop == SND_DGNB)
    { 
        dgnb_sfx=PLAY;  
        current_song = SONG_DGNB;
        
        if(old_song != current_song)          
            dgnb_sfx=FADE_IN;         
    }    
    if(music_loop == SND_FINAL)
    { 
        final_sfx=PLAY;  
        current_song = SONG_FINAL;
        
        if(old_song != current_song)          
            final_sfx=FADE_IN;         
    }    
    if(music_loop == SND_DANGERS)
    { 
        dangers_sfx=PLAY;  
        current_song = SONG_DANGERS;
        
        if(old_song != current_song)          
            dangers_sfx=FADE_IN;         
    }      
    
    // Do music fade outs
    
    if(old_song == SONG_END)
    if(old_song != current_song)
        end_sfx=FADE_OUT;     
    
    if(old_song == SONG_JET)
    if(old_song != current_song)
        jet_sfx=FADE_OUT;    
    
    if(old_song == SONG_SIEGE)
    if(old_song != current_song)
		siege_sfx=FADE_OUT;  
        
    if(old_song == SONG_THEATRE)
    if(old_song != current_song)
        theatre_sfx=FADE_OUT;   
        
    if(old_song == SONG_CREDITS)
    if(old_song != current_song)
        credits_sfx=FADE_OUT; 
                    
    if(old_song == SONG_WAR)
    if(old_song != current_song)
        war_sfx=FADE_OUT;    
    
    if(old_song == SONG_LND)
    if(old_song != current_song)
        lnd_sfx=FADE_OUT;    
    
    if(old_song == SONG_CRD)
    if(old_song != current_song)
        crd_sfx=FADE_OUT;    
    
    if(old_song == SONG_ARMY)
    if(old_song != current_song)
        army_sfx=FADE_OUT;    
     
    if(old_song == SONG_FIGHT)
    if(old_song != current_song)
        fight_sfx=FADE_OUT; 
    
    if(old_song == SONG_SAD)
    if(old_song != current_song)
        sad_sfx=FADE_OUT;                 
    
    if(old_song == SONG_INTRO)
    if(old_song != current_song)
        intro_sfx=FADE_OUT; 
    
    if(old_song == SONG_MINI)
    if(old_song != current_song)
        mini_sfx=FADE_OUT; 
            
    if(old_song == SONG_URGENCY)
    if(old_song != current_song)
        urgency_sfx=FADE_OUT;
            
    if(old_song == SONG_FANFARE)
    if(old_song != current_song)
        fanfare_sfx=FADE_OUT; 
            
    if(old_song == SONG_FANFARE2)
    if(old_song != current_song)
        fanfare2_sfx=FADE_OUT; 
            
    if(old_song == SONG_DEATH)
    if(old_song != current_song)
        deathscreen_sfx=FADE_OUT; 
                                    
    if(old_song == SONG_DGNB)
    if(old_song != current_song)
        dgnb_sfx=FADE_OUT;     
    
    if(old_song == SONG_FINAL)
    if(old_song != current_song) 
        final_sfx=FADE_OUT;     
    
    if(old_song == SONG_DANGERS)
    if(old_song != current_song)
        dangers_sfx=FADE_OUT;     
 
    if(game_mode == FRONT || game_mode == WALK)
    for(int i=0;i<no_sprites;i++)   
	if(i >= 0 && i < TOTAL_NO_SPRITES)
    {    
         
         sprite[i].turn_off = false; 
         sprite[i].flash_target = false; 
		 sprite[i].electrocute = false; 
		 sprite[i].moving = false;

         if(game_mode == FRONT)             
         if(sprite[i].type == FE_MUSIC && !mode) 
         { 
             sprite[i].width = sprite[i].box_width * music_volume;
         } 
         if(game_mode == FRONT)          
         if(sprite[i].type == FE_SFX && !mode) 
         { 
             sprite[i].width = sprite[i].box_width * sfx_volume;
         }      

	if(game_mode == FRONT)
	{
		sprite[i].depth = 0.0f;
		sprite[i].angle = 0.0f;
		sprite[i].distance = 0.0f;
	}

    if(game_mode == WALK && !mode)  
    {        
        sprite[i].name=-1;  
        sprite[i].cur=0;  
        sprite[i].file_full = false;
        sprite[i].flash_target = false;  
        sprite[i].flash_timer = 0;   
        sprite[i].dflash_timer = 0;  
        sprite[i].death_flash  = false;             
        sprite[i].moving = false;
        sprite[i].special = 0;
        sprite[i].fire_target = -1;
        sprite[i].emy_shooting = false;
        sprite[i].jumping = false;  
        sprite[i].all_timer=0;
        sprite[i].reached_node = -1;
        sprite[i].node_counter = 0;
        sprite[i].kills = 0;  
        sprite[i].turn_off = false; 
        sprite[i].node_counter=0;
        sprite[i].depth = 0.0f;  
        sprite[i].flash_no_count = 0;  
        sprite[i].movement = 0;
        sprite[i].on_mud = false; 
        sprite[i].building = false;  
        sprite[i].death_by_mud = 0;
        sprite[i].hit_opponent = false;   
        sprite[i].tar_angle = 0.0000; 
        sprite[i].turning = false; 
        sprite[i].bagging = false;
        sprite[i].splatted = false;
        sprite[i].on_ladder = false;
		sprite[i].value2 = -1;
        sprite[i].value3 = -1; 
        sprite[i].group_id = -1;
        sprite[i].reload_timer = 0; 
        sprite[i].hit_by_bullet = false;
        sprite[i].mercy = false; 
        sprite[i].kills = 0.0;
        sprite[i].base_anim = sprite[i].anim; 
        sprite[i].mov_x = sprite[i].x;
        sprite[i].mov_y = sprite[i].y;
        sprite[i].end_x = sprite[i].x;
        sprite[i].end_y = sprite[i].y;
        sprite[i].grenaded = 0;
        sprite[i].spotted_timer = 0;
        sprite[i].spotted = false;  
        sprite[i].col_timer = 0;
        sprite[i].light = 1.0;
        sprite[i].ai_brain = 0;
        sprite[i].ai_brain_timer = 0;
		sprite[i].thrown_effect = 0;
        sprite[i].return_fire = false; 
        sprite[i].idle_type = IDLE_NONE;  
		sprite[i].camo = false;

		sprite[i].direction = 0;
		sprite[i].ducking = 0;
		sprite[i].duck_timer = 0;
		sprite[i].hit_direction = 0;

		sprite[i].pain = false;
		sprite[i].knockdown = false;
		sprite[i].knockdown_Y = 0.0f;
		sprite[i].new_Z = 0.0f;
		sprite[i].block_type = 0;
		sprite[i].invulnerable = false;
		sprite[i].electrocute = false;
		sprite[i].handcuffed = false;
		sprite[i].walking_backwards = false;
		sprite[i].dizzy = false;
		sprite[i].sticky = false;

		sprite[i].is_a_pigeon = false;
		sprite[i].deflect = false;

 
        for(int j=0;j<NODE_LIMIT;j++)    
            sprite[i].node_list[j] = -1;
         
    }   // End of Walk check  
            
    Set_Sprite(i, sprite[i].anim, sprite[i].anim_state, ANIM_SPRITE, ANIM_WALKING); 

//	if(game_mode == WALK)
//		Animation_System(i, BULLET_CHECK_OFF, INTERRUPT_OFF, PAIN_ANIM_OFF, FIRE_OFF);
                
    } // End of for loop
        
    if(game_mode == GAME || game_mode == FRONT )
    {  
        LoadHud("scene/episode0/scene3.dat"); 
                         
        for(int i=0;i<hud_no_sprites;i++)
		if(i >= 0 && i < TOTAL_NO_HUD)
		{
#ifndef DREAMCAST
			if( hud[i].fx_id >= 0 && hud[i].fx_id < 75)
			if( hud[i].anim >= 0 && hud[i].anim < 256)
			if( hud[i].cur >= 0 && hud[i].cur < 256)
			   hud[i].frame = a_texture[hud[i].fx_id].anims[hud[i].anim][hud[i].cur];
#else
			if( hud[i].fx_id >= 0 && hud[i].fx_id < 75)
			if( hud[i].anim >= 0 && hud[i].anim < 256)
			if( hud[i].cur >= 0 && hud[i].cur < 256)
			   hud[i].frame = a_texture_get_anims_secondlayer(hud[i].fx_id, hud[i].anim, hud[i].cur);
#endif
			hud[i].flash_target = false;
		}
            
    } 

    if(game_mode == WORLD)
        LoadHud( "scene/episode0/scene3.dat" );
    if(game_mode == CINE)
    {
        LoadHud("scene/episode0/scene3.dat");        
        
        for(int i=0;i<TOTAL_NO_HUD;i++)
		if(i >= 0 && i < TOTAL_NO_HUD)
            hud[i].alpha = 0.0f;  
                                             
    } 
    if(game_mode == FRONT)
    {
        
        for(int i=0;i<TOTAL_NO_HUD;i++)
		if(i >= 0 && i < TOTAL_NO_HUD)
            hud[i].alpha = 0.0f;             
            
        hud[1].alpha = 1.0f;
            
    } 
                                    
    hud[1].x = mouseX - (hud[1].width/2);  
    hud[1].y = mouseY - (hud[1].height/2);    
    hud[1].w = mouseX - (hud[1].width/2);  
    hud[1].z = mouseY - (hud[1].height/2); 
                        
    if( (g_type == G_NON || g_type == G_STS) && game_mode == WALK)
    {
        hud[0].alpha = 0.0f;  
        hud[1].alpha = 1.0f;
        hud[2].alpha = 0.0f;
        hud[3].alpha = 0.0f;  
        hud[4].alpha = 0.0f;      
        hud[5].alpha = 0.0f; 
        hud[6].alpha = 0.0f;   
        hud[7].alpha = 0.0f; 
        hud[8].alpha = 0.0f;   
        hud[9].alpha = 0.0f;  
        hud[10].alpha = 0.0f;  
        hud[11].alpha = 0.0f;  
        hud[12].alpha = 0.0f;  
        hud[13].alpha = 0.0f;  
        hud[14].alpha = 0.0f;  
        hud[15].alpha = 0.0f;  
        hud[16].alpha = 0.0f;  
        hud[17].alpha = 0.0f;                                                          
        hud[18].alpha = 0.0f;  
        hud[19].alpha = 0.0f;                
        hud[20].alpha = 0.0f;                                                          
        hud[21].alpha = 0.0f;  
        hud[22].alpha = 0.0f;  
        hud[23].alpha = 0.0f;                                                          
        hud[24].alpha = 0.0f;  
        hud[25].alpha = 0.0f;
        hud[26].alpha = 0.0f;  
        hud[27].alpha = 0.0f;                                                          
        hud[28].alpha = 0.0f;  
        hud[29].alpha = 0.0f; 
        hud[30].alpha = 0.0f;
        hud[31].alpha = 0.0f;
        hud[32].alpha = 0.0f;
        hud[33].alpha = 0.0f;
        hud[34].alpha = 0.0f;
        hud[35].alpha = 0.0f;                  
        hud[36].alpha = 0.0f;
        hud[37].alpha = 0.0f;
        hud[38].alpha = 0.0f;
        hud[39].alpha = 0.0f;  
        hud[40].alpha = 0.0f; 
        hud[41].alpha = 0.0f;  
        hud[42].alpha = 0.0f;
        hud[43].alpha = 0.0f;                
        hud[44].alpha = 0.0f;  
        hud[45].alpha = 0.0f;  
        hud[46].alpha = 0.0f;  
        hud[47].alpha = 0.0f;  
        hud[48].alpha = 0.0f;  
        hud[49].alpha = 0.0f;  
        hud[50].alpha = 0.0f;
        hud[51].alpha = 0.0f;
        hud[52].alpha = 0.0f;
        hud[53].alpha = 0.0f;
        hud[54].alpha = 0.0f;
        hud[55].alpha = 0.0f;  
        hud[56].alpha = 0.0f;                      
        hud[57].alpha = 0.0f; 
        hud[58].alpha = 0.0f;
        hud[59].alpha = 0.0f;
        hud[60].alpha = 0.0f;
        hud[61].alpha = 0.0f;
        hud[62].alpha = 0.0f;
        hud[63].alpha = 0.0f;
        hud[64].alpha = 0.0f;
        hud[65].alpha = 0.0f;
        hud[66].alpha = 0.0f;
        hud[67].alpha = 0.0f;
        hud[68].alpha = 0.0f;


    }    
    if( (g_type == G_BLK || g_type == G_SLI || g_type == G_FLL || g_type == G_FLY || g_type == G_OLD) && game_mode == WALK)
    {
        hud[0].alpha = 0.0f; 
        hud[1].alpha = 0.0f;
        hud[2].alpha = 0.0f; 
        hud[3].alpha = 0.0f; 
        hud[4].alpha = 0.0f; // Face
        hud[5].alpha = 0.0f; // Health               
        hud[6].alpha = 0.0f;   
        hud[7].alpha = 0.0f; // Ammo1
        hud[8].alpha = 0.0f; // Ammo2
        hud[9].alpha = 0.0f; // Ammo3
        hud[10].alpha = 0.0f;// Ammo4
        hud[11].alpha = 0.0f;  
        hud[12].alpha = 0.0f;  
        hud[13].alpha = 0.0f;   
        hud[14].alpha = 0.0f;  
        hud[15].alpha = 0.0f;   
        hud[16].alpha = 0.0f;  
        hud[17].alpha = 0.0f;                                                          
        hud[18].alpha = 0.0f;   
        hud[19].alpha = 0.0f;                
        hud[20].alpha = 0.0f;                                                          
        hud[21].alpha = 0.0f;  
        hud[22].alpha = 0.0f;  
        hud[23].alpha = 0.0f;                                                           
        hud[24].alpha = 0.0f;  
        hud[25].alpha = 0.0f;  
        hud[26].alpha = 0.0f;  
        hud[27].alpha = 0.0f;                                                          
        hud[28].alpha = 0.0f;  
        hud[29].alpha = 0.0f;    
        hud[30].alpha = 0.0f;
        hud[31].alpha = 0.0f; 
        hud[32].alpha = 0.0f;
        hud[33].alpha = 0.0f;
        hud[34].alpha = 0.0f;
        hud[35].alpha = 0.0f;       
        hud[36].alpha = 0.0f;     
        hud[37].alpha = 0.0f;
        hud[38].alpha = 0.0f;
        hud[39].alpha = 0.0f; 
        hud[40].alpha = 0.0f; 
        hud[41].alpha = 0.0f; 
        hud[42].alpha = 0.0f;
        hud[43].alpha = 0.0f;
        hud[44].alpha = 0.0f;   
        hud[45].alpha = 0.0f;  
        hud[46].alpha = 0.0f;   
        hud[47].alpha = 0.0f;  
        hud[48].alpha = 0.0f;  
        hud[49].alpha = 0.0f;  
        hud[50].alpha = 0.0f;
        hud[51].alpha = 0.0f;
        hud[52].alpha = 0.0f;
        hud[53].alpha = 0.0f;
        hud[54].alpha = 0.0f;
        hud[55].alpha = 0.0f;            
        hud[56].alpha = 0.0f;                      
        hud[57].alpha = 0.0f;
		hud[58].alpha = 0.0f;  
        hud[59].alpha = 0.0f;	
        hud[60].alpha = 0.0f;
        hud[61].alpha = 0.0f;
        hud[62].alpha = 0.0f;
        hud[63].alpha = 0.0f;
        hud[64].alpha = 0.0f;  
        hud[65].alpha = 0.0f;
        hud[66].alpha = 0.0f;    
        hud[67].alpha = 0.0f;    
        hud[68].alpha = 0.0f;    
    }    
    
    hud1width  = hud[1].width;   
    hud1height = hud[1].height;      
                    
    if(mode)   
	if(game_mode == WALK )     
    {     
         
        for(int i=0;i<TOTAL_NO_HUD;i++)
		if(i >= 0 && i < TOTAL_NO_HUD)
        {
            hud[i].alpha = 0.0f;   

            Set_Sprite(i, hud[i].base_anim, hud[i].anim_state, ANIM_HUD, ANIM_WALKING);
            
        }    

        hud[1].alpha = 1.0f;                        
                      
    } 

	if(game_mode == WALK)
	for(int i=0;i<TOTAL_NO_HUD;i++)
	if(i >= 0 && i < TOTAL_NO_HUD)
		Set_Sprite(i, hud[i].base_anim, hud[i].anim_state, ANIM_HUD, ANIM_WALKING);

	// Load screen... 
	if(episode == 10 && scene == 0)
		hud[1].alpha = 0.0f;
#if defined SWITCH || defined DREAMCAST
	if(mode)  
	if(RENDERER == RENDER_OPENGL) 
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending (disable alpha testing)  
#endif                      
    if(!mode && game_mode != WALK && game_mode != WORLD)      
    {
        camX = 0.0f;     
        camY = 0.0f;   
    }    
            

    animating = true;


    // Set-up fading 
    if(!(fade_in==0) )
        fade=0.0f;
    else
        fade=1.0f; 
    
    if(fade_in<0)
    {
        c_fade_in=fade_in*-1;
    }
    else
        c_fade_in=fade_in;    
     
    if(fade_out<0)
    {
        c_fade_out=fade_out*-1;
    }
    else
        c_fade_out=fade_out;
     
    if(fade_in == 0)
    {
    
        fade_timer = (int)TimerGetTime() + 10;  
        
        fade=0.0f;  
    }    
    
    cos_fade = 0.0f;

	// Hack
    if(( game_mode == WALK || game_mode == WORLD || game_mode == FRONT))
    {
               
        if( game_mode == WALK && !mode )
        {                
      
            counter[0].x = -0.96f;  
            counter[0].y = -0.35f; 
            counter[0].alpha=1.0f; 
                         
            counter[0].width = 0.016f;
            counter[0].height = 0.048f;             
                  
            counter[1].x = -0.90f;  
            counter[1].y = -0.48f; 
            counter[1].alpha=0.0f;  
            
            counter[1].width = 0.010f;
            counter[1].height = 0.03f;
                 
            counter[2].x = -0.68f;  
            counter[2].y = -0.48f; 
            counter[2].alpha=0.0f;  
            
            counter[2].width = 0.010f;
            counter[2].height = 0.03f;
                 
            counter[4].x = -0.24f; 
            counter[4].y = 0.20f;
            counter[4].alpha=1.0f;  
            
            counter[4].width = 0.012f; 
            counter[4].height = 0.03f;
                 
            counter[5].x = -0.80f;
            counter[5].y = 0.70f;
            counter[5].alpha=1.0f;  
            
            counter[5].width = 0.012f;
            counter[5].height = 0.03f;  
                        
        }  
        else
        {
            counter[0].alpha=0.0f;    
            counter[1].alpha=0.0f;
            counter[2].alpha=0.0f;
            counter[4].alpha=0.0f;
            counter[5].alpha=0.0f; 
                 
            counter[5].x = -0.80f;
            counter[5].y = 0.70f;
            counter[5].alpha=1.0f;  
            
            counter[5].width = 0.012f;
            counter[5].height = 0.03f;  
                        
        //    ply_speed = PLY_WORLD_SPEED; 
        } 
    }    

	for(int i = 0;i < TOTAL_TEXT;i++)  
	{ 
		new_counter[i].width = 0.05f;
		new_counter[i].height = 0.05f;
		new_counter[i].id = 0;
		new_counter[i].greyed = false;
		new_counter[i].scroll_this = false;
	}
     
    sprintf(counter[8].word, "");

    next_scene = false;

	#if INCLDUE_360_CONTROLLER == 1
		Run_Joypad();
		//IControlUpdate();
	#endif

	// Reset all counters
	for(int i = 0; i < TOTAL_TEXT;i++)
	{
		new_counter[i].alpha = 0.0f; 
	}
 
	if(!mode) 
	{
		VG_INTRO_DOG1 = 0;
		VG_INTRO_DOG2 = 0;

		VG_set_intro_dogs();
		Run_Verdict(1);
		Run_Story(1);

		Animate(-1, -1); 
	}
	 
	render_sequence=0;  
	double_main_code=0;


    return(true);
   
}    
 
// ******************************************************************************//
//                                                                               //
//                                DUMP SCENE                                     //
//                                                                               //
// ******************************************************************************//

bool DumpScene( char *filename )
{
	int temp_grab_switch=0;
	int temp_mouseover=0;

          FILE *fp;
                
//          remove(filename); 
//          fp = fopen (filename, "w");
#ifndef DREAMCAST 
		  errno_t err;
#endif 

		  fp  = fopen( filename, "w+");

         // if (err!=NULL)
         //    MessageBox(NULL,"Couldn't dump sceneX.dat","ERROR",MB_OK|MB_ICONEXCLAMATION);
#ifdef SWITCH       
         if(err==NULL)
#elif PS4
		 if (fp!=NULL)
#elif XB1
		  if (fp != NULL)
#elif DREAMCAST
		  if (fp != NULL)
#endif
         { 
             
         fprintf(fp, "%i\n", game_mode);                                                        
         fprintf(fp, "%i\n", no_sprites);
         fprintf(fp, "%i\n", no_of_keyframes);
         fprintf(fp, "%i\n", game_time);
         fprintf(fp, "%i\n", fade_in);
         fprintf(fp, "%i\n", fade_out);
         fprintf(fp, "%i\n", scene_shake);
         fprintf(fp, "%i\n", music_loop);
         fprintf(fp, "%i\n", g_type);

         for( int i=0; i<no_sprites;i++) 
		 if(i >= 0 && i < TOTAL_NO_SPRITES)
         {
 
				SAFE_BOOL2INT(sprite[i].grab_switch, temp_grab_switch);
				SAFE_BOOL2INT(sprite[i].mouseover, temp_mouseover);

		        fprintf(fp,"%f\n", sprite[i].x);
		        fprintf(fp,"%f\n", sprite[i].y);
		        fprintf(fp,"%f\n", sprite[i].width);
		        fprintf(fp,"%f\n", sprite[i].height);
		        	        
	            fprintf(fp,"%f\n", sprite[i].w);
	            fprintf(fp,"%f\n", sprite[i].z);
	            fprintf(fp,"%f\n", sprite[i].box_width);
	            fprintf(fp,"%f\n", sprite[i].box_height);
	        
 	            for ( int j=0;j<4;j++)
	            {
	                fprintf(fp,"%f\n", sprite[i].u[j]);
	                fprintf(fp,"%f\n", sprite[i].v[j]);
                }
		        fprintf(fp,"%i\n", sprite[i].id);
		        fprintf(fp,"%i\n", sprite[i].score); 
		        fprintf(fp,"%i\n", sprite[i].anim_state);
		        fprintf(fp,"%i\n", sprite[i].anim);
		        fprintf(fp,"%f\n", sprite[i].alpha);
		        fprintf(fp,"%i\n", sprite[i].linked_sprite);
		        fprintf(fp,"%i\n", sprite[i].priority);
		        fprintf(fp,"%i\n", sprite[i].type); 
		        fprintf(fp,"%i\n", temp_grab_switch); // Bool
		        fprintf(fp,"%i\n", temp_mouseover);   // Bool
		        fprintf(fp,"%i\n", sprite[i].sector);
		        fprintf(fp,"%i\n", sprite[i].sector_action);
		        fprintf(fp,"%i\n", sprite[i].onCreate);
		        fprintf(fp,"%i\n", sprite[i].onCreate_action);
		        fprintf(fp,"%i\n", sprite[i].rank);
		        fprintf(fp,"%i\n", sprite[i].onDeath_action);
		        fprintf(fp,"%f\n", sprite[i].light);
		        fprintf(fp,"%i\n", sprite[i].global_flag);
                		         
          }
                                  
          fclose(fp);
          
          }
          
          sprintf( text[4].word, "Dumped scene%i...", scene);
       
    return(true);

} 
 
// ******************************************************************************//
//                                                                               //
//                              LOAD TEXTURES                                    //
//                                                                               //
// ******************************************************************************//
#ifdef DREAMCAST

unsigned int startID2048x256 = 666666;
unsigned int startID2048x2048 = 777777;
#define TEXNUMBER2048x256 45
#define TEXNUMBER2048x2048 52
const char *path2048x256[TEXNUMBER2048x256] = {
    "verdict/chars/judge.tex",
    "verdict/sheet/bob.tex",
    "verdict/sheet/bob1.tex",
    "verdict/sheet/daesu.tex",
    "verdict/sheet/daesu1.tex",
    "verdict/sheet/gun.tex",
    "verdict/sheet/gun1.tex",
    "verdict/sheet/gyeong.tex",
    "verdict/sheet/gyeong1.tex",
    "verdict/sheet/hyuk.tex",
    "verdict/sheet/hyuk1.tex",
    "verdict/sheet/jae.tex",
    "verdict/sheet/jae1.tex",
    "verdict/sheet/kennedy.tex",
    "verdict/sheet/kennedy1.tex",
    "verdict/sheet/konu.tex",
    "verdict/sheet/konu1.tex",
    "verdict/sheet/mia.tex",
    "verdict/sheet/mia1.tex",
    "verdict/sheet/minso.tex",
    "verdict/sheet/minso1.tex",
    "verdict/sheet/reese.tex",
    "verdict/sheet/reese1.tex",
    "verdict/sheet/saizo.tex",
    "verdict/sheet/saizo1.tex",
    "verdict/sheet/sang.tex",
    "verdict/sheet/sang1.tex",
    "verdict/sheet/sapporo.tex",
    "verdict/sheet/sapporo1.tex",
    "verdict/sheet/sho.tex",
    "verdict/sheet/sho1.tex",
    "verdict/sheet/siu.tex",
    "verdict/sheet/siu1.tex",
    "verdict/sheet/sungki.tex",
    "verdict/sheet/sungki1.tex",
    "verdict/sheet/tia.tex",
    "verdict/sheet/tia1.tex",
    "verdict/sheet/toyun.tex",
    "verdict/sheet/toyun1.tex",
    "verdict/sheet/trainer.tex",
    "verdict/sheet/trainer1.tex",
    "verdict/sheet/yejun.tex",
    "verdict/sheet/yejun1.tex",
    "verdict/sheet/yohan.tex",
    "verdict/sheet/yohan1.tex",
};

const char *path2048x2048[TEXNUMBER2048x2048] = {
    "verdict/chars/gun.tex",
    "verdict/chars/gyeong.tex",
    "verdict/chars/hyuk.tex",
    "verdict/chars/hyuk_non.tex",
    "verdict/chars/jae.tex",
    "verdict/chars/kennedy.tex",
    "verdict/chars/minso.tex",
    "verdict/chars/reese.tex",
    "verdict/chars/saizo.tex",
    "verdict/chars/sang.tex",
    "verdict/chars/sho.tex",
    "verdict/chars/siu.tex",
    "verdict/chars/test.tex",
    "verdict/chars/test1.tex",
    "verdict/chars/tia.tex",
    "verdict/chars/trainer.tex",
    "verdict/chars/yohan.tex",
    "verdict/chars/alters/bob.tex",
    "verdict/chars/alters/daesu.tex",
    "verdict/chars/alters/konu.tex",
    "verdict/chars/alters/mia.tex",
    "verdict/chars/alters/saizo.tex",
    "verdict/chars/alters/sang.tex",
    "verdict/chars/alters/sapporo.tex",
    "verdict/chars/alters/sungki.tex",
    "verdict/chars/alters/toyun.tex",
    "verdict/chars/alters/trainer.tex",
    "verdict/chars/alters/yejun.tex",
    "verdict/chars/colors/bob.tex",
    "verdict/chars/colors/daesu.tex",
    "verdict/chars/colors/gun.tex",
    "verdict/chars/colors/gyeong.tex",
    "verdict/chars/colors/hyuk.tex",
    "verdict/chars/colors/jae.tex",
    "verdict/chars/colors/kennedy.tex",
    "verdict/chars/colors/konu.tex",
    "verdict/chars/colors/mia.tex",
    "verdict/chars/colors/minso.tex",
    "verdict/chars/colors/reese.tex",
    "verdict/chars/colors/saizo.tex",
    "verdict/chars/colors/sang.tex",
    "verdict/chars/colors/sapporo.tex",
    "verdict/chars/colors/sho.tex",
    "verdict/chars/colors/siu.tex",
    "verdict/chars/colors/sungki.tex",
    "verdict/chars/colors/tia.tex",
    "verdict/chars/colors/toyun.tex",
    "verdict/chars/colors/trainer.tex",
    "verdict/chars/colors/yejun.tex",
    "verdict/chars/colors/yohan.tex",
    "verdict/sheet/test.tex",
    "verdict/sheet/test1.tex",
};

typedef struct 
{
	unsigned int baseID;
	unsigned int topLeft;
	unsigned int topRight;
	unsigned int bottomLeft;
	unsigned int bottomRight;
}CustomBigTex;
std::vector<CustomBigTex> tex2048x256;
std::vector<CustomBigTex> tex2048x2048;


#endif
      
bool LoadTextures(sString sfilename, bool delete_textures)								
{ 
       
	bool Status=false;              
	int rnd=0;
	sString itemp_string;
#if defined SWITCH || defined DREAMCAST
    GLuint type = GL_RGBA;
#endif

	#if IS_USING_DIRECTX == 1 
#ifdef XB1
	HRESULT texture_err;
#endif
    #endif 

	Texture stexture;

    FILE *fpt;
    
    g_fx_id=0; // Reset this or nasty things happen


    strcat(sfilename.string,".txd");
                      
    // fpt = fopen(sfilename.string, "r");
#ifndef DREAMCAST    		  
	errno_t err; 
#endif

#ifdef SWITCH
	if (strstr(sfilename.string, "rom:") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "rom:/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fpt = fopen(tempfilename, "r");
		printf("LoadAnim NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#elif PS4
	if (strstr(sfilename.string, "/app0/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "/app0/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fpt = fopen(tempfilename, "r");
		//printf("LoadTEXTURE NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#elif DREAMCAST
	if (strstr(sfilename.string, "cd/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "cd/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fpt = fopen(tempfilename, "r");
		//printf("LoadTEXTURE NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#elif XB1
	if (strstr(sfilename.string, "./Assets/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "./Assets/%s", sfilename.string);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fpt = fopen(tempfilename, "r");
		//printf("LoadTEXTURE NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#endif
		for (int i = 0; sfilename.string[i]; i++) {
			sfilename.string[i] = tolower(sfilename.string[i]);
		}
		fpt = fopen(sfilename.string, "r");
		//printf("LoadTEXTURE NO CONVERSION : %s\n", sfilename.string);

	}


	//fpt  = fopen( sfilename.string, "r");

        //if (err!=NULL)
           //MessageBox(NULL,"Couldn't load sceneX.txd","ERROR",MB_OK|MB_ICONEXCLAMATION);
#ifdef SWITCH
	if(err==NULL)
#elif defined PS4 || defined XB1 || defined DREAMCAST
	if(fpt != NULL)
#endif
	{


		#if IS_USING_DIRECTX == 1
#if defined (PS4) || defined (XB1)
		if (RENDERER == RENDER_DIRECTX)
			if (delete_textures == true)
			{
				for (int i = 0; i < numsubmtls; i++)
					if (i >= 0 && i < TOTAL_NUM_TEXTURES)
					{
						//if (strcmp(texture[i].name, "NULL") != 0)
						//{
							//printf("DELETE TEXTURE %s\n", texture[i].name);
							//sce::SampleUtil::destroy(&texture[i].tex);
							//strcpy(texture[i].name, "NULL");
							//texture[i].tex = NULL;
						//}
					}
			}
#endif
		#endif
#if defined SWITCH || defined DREAMCAST
		if(RENDERER == RENDER_OPENGL)     
		if( delete_textures == true ) 
		{ 
			 
			
#ifdef DREAMCAST
			for(int i=0;i<numsubmtls;i++) 
			{
				if(i >= 0 && i < TOTAL_NUM_TEXTURES)
				{
					if(texID[i] < 666666)
						glDeleteTextures(1, &texID[i]);	
				}
			}
			
            
			SAFE_DELETE_ARRAY(texID);
			DeleteAllAnim();
			for (size_t lol = 0; lol < tex2048x256.size(); ++lol) {
        		glDeleteTextures(1, &tex2048x256[lol].topLeft);
        		glDeleteTextures(1, &tex2048x256[lol].topRight);
    		}
    		for (size_t lol = 0; lol < tex2048x2048.size(); ++lol) {
        		glDeleteTextures(1, &tex2048x2048[lol].topLeft);
        		glDeleteTextures(1, &tex2048x2048[lol].topRight);
        		glDeleteTextures(1, &tex2048x2048[lol].bottomLeft);
        		glDeleteTextures(1, &tex2048x2048[lol].bottomRight);
    		}
			tex2048x256.clear();
    		
    		tex2048x2048.clear();
    		
    		startID2048x256 = 666666;
			startID2048x2048 = 777777;
			//printf("DELETE TEX AND ANIM");
#else
			for(int i=0;i<numsubmtls;i++) 
			if(i >= 0 && i < TOTAL_NUM_TEXTURES)
				glDeleteTextures(1, &texID[i]);
            
			SAFE_DELETE_ARRAY(texID);
#endif

		}
#endif

		fscanf( fpt, "%i", &numsubmtls); 
		//printf("NUMSUBMATERIALS %d\n", numsubmtls);
//      	sString material[numsubmtls]; 
      	
      	memset( material, 0, sizeof(sString)*NUMBER_OF_SUBMATERIALS );
#if defined SWITCH || defined DREAMCAST        
		if(RENDERER == RENDER_OPENGL) 
			texID = new GLuint[numsubmtls]; 
         
		if(RENDERER == RENDER_OPENGL) 
			memset( texID, 0, sizeof(texID) );
#endif

        memset( texture_fx, 0, sizeof(texture_fx) );               
             
        for ( int i=0;i<numsubmtls;i++)   
		if(i >= 0 && i < 200) 
        {                   
            fscanf( fpt, "%i", &texture_fx[i]);     
            fscanf( fpt, "%s", &material[i].string);  

			// HiRes backgrounds...
			if(VG_HIRES_BACKGROUNDS == true) 
			{ 

				// ALLEYWAY...
				sprintf(itemp_string.string, "Data/verdict/bgs/alleyway/bg1");

				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/alleyway/bg1H");

				sprintf(itemp_string.string, "Data/verdict/bgs/alleyway/fg");

				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/alleyway/fgH");

				sprintf(itemp_string.string, "Data/verdict/bgs/alleyway/bg_car");

				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/alleyway/bg_carH");

				// TRAIN...
				sprintf(itemp_string.string, "Data/verdict/bgs/train/bg1");

				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/train/bg1H");
				 
				// TRAFFIC...
				sprintf(itemp_string.string, "Data/verdict/bgs/traffic/bg1");
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/traffic/bg1H");

				sprintf(itemp_string.string, "Data/verdict/bgs/traffic/billboard");

				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/traffic/billboardH");

				sprintf(itemp_string.string, "Data/verdict/bgs/traffic/fg");

				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/traffic/fgH");

				// PARK...
				sprintf(itemp_string.string, "Data/verdict/bgs/park/bg1");
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/park/bg1H");

				sprintf(itemp_string.string, "Data/verdict/bgs/park/clouds");
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/park/cloudsH");

				// BIKESHOP...
				sprintf(itemp_string.string, "Data/verdict/bgs/bikeshop/bg1");
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/bikeshop/bg1H");

				sprintf(itemp_string.string, "Data/verdict/bgs/bikeshop/fg");
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/bikeshop/fgH");

				// NIGHTCLUB...
				sprintf(itemp_string.string, "Data/verdict/bgs/nightclub/bg1");
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/nightclub/bg1H");

				sprintf(itemp_string.string, "Data/verdict/bgs/nightclub/fg");
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/nightclub/fgH");

				sprintf(itemp_string.string, "Data/verdict/bgs/nightclub/screen");
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/nightclub/screenH");	

				// PRISON... 
				sprintf(itemp_string.string, "Data/verdict/bgs/prison/bg1"); 
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/prison/bg1H");

				sprintf(itemp_string.string, "Data/verdict/bgs/prison/fg");
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/prison/fgH");

				// HIGHWAY...
				sprintf(itemp_string.string, "Data/verdict/bgs/highway/bg1"); 
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/highway/bg1H");

				sprintf(itemp_string.string, "Data/verdict/bgs/highway/fg");
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/highway/fgH");

				// COURT... 
				sprintf(itemp_string.string, "Data/verdict/bgs/court/bg1"); 
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/court/bg1H");

				sprintf(itemp_string.string, "Data/verdict/bgs/court/fg"); 
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/court/fgH");

				// ROOFTOPS...
				sprintf(itemp_string.string, "Data/verdict/bgs/rooftops/bg1"); 
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/rooftops/bg1H");

				sprintf(itemp_string.string, "Data/verdict/bgs/rooftops/fg"); 
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/rooftops/fgH");

				// AIRPORT... 
				sprintf(itemp_string.string, "Data/verdict/bgs/airport/bg1"); 
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/airport/bg1H"); 

				sprintf(itemp_string.string, "Data/verdict/bgs/airport/fg"); 
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/airport/fgH");

				// CAFE... 
				sprintf(itemp_string.string, "Data/verdict/bgs/cafe/bg1"); 
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/cafe/bg1H");

				sprintf(itemp_string.string, "Data/verdict/bgs/cafe/fg"); 
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/cafe/fgH");

				// SHRINE...
				sprintf(itemp_string.string, "Data/verdict/bgs/shrine/bg1"); 
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/shrine/bg1H");

				sprintf(itemp_string.string, "Data/verdict/bgs/shrine/fg");
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/shrine/fgH");

				// DOJO... 
				sprintf(itemp_string.string, "Data/verdict/bgs/dojo/bg"); 
				  
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/dojo/bgH");

				sprintf(itemp_string.string, "Data/verdict/bgs/dojo/bg1"); 
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/dojo/bg1H");

				sprintf(itemp_string.string, "Data/verdict/bgs/dojo/fg");
				 
				if( strcmp( material[i].string, itemp_string.string ) == 0)
						sprintf(material[i].string, "Data/verdict/bgs/dojo/fgH");


			}



			// Title screen logo for Steam demo... 
			sprintf(itemp_string.string, "Data/verdict/front/VS_sign");

            if( strcmp( material[i].string, itemp_string.string ) == 0)
			{
				if(VG_GAME_MODE == VG_ARCADE_MODE && VG_ARCADE_TYPE == VG_ARCADE_DUELLING)
					sprintf(material[i].string, "Data/verdict/front/Duel_sign");
			} 

			// Title screen logo for Steam demo...
#ifdef BREAKER_CHARACTER_BUILD
				sprintf(itemp_string.string, "Data/verdict/title/logo");
#else
				sprintf(itemp_string.string, "Data/verdict/title/logo_old");
				if (strcmp(material[i].string, "Data/verdict/title/logo") == 0)
				{
					sprintf(material[i].string, "Data/verdict/title/logo_old");
				}
#endif

            if( strcmp( material[i].string, itemp_string.string ) == 0)
			{
				if(VG_STEAM_DEMO == 1)
					sprintf(material[i].string, "Data/verdict/title/logo_demo");
			} 

			// Versus Background... 
			sprintf(itemp_string.string, "Data/verdict/title/bg_vs1");

            if( strcmp( material[i].string, itemp_string.string ) == 0)
			{
				if(VG_GAME_MODE == VG_VERSUS_MODE)
					sprintf(material[i].string, "Data/verdict/title/bg_vs2");
			} 
			 
			// Versus Background... 
			sprintf(itemp_string.string, "Data/verdict/title/bg_anim");

            if( strcmp( material[i].string, itemp_string.string ) == 0)
			{
				if(episode == 6 && scene == 0) 
				if(VG_IS_VERSUS_SCREEN == true)
				{
					sprintf(material[i].string, "Data/verdict/title/bg_vs3");

					// VS SCREEN...
					if(VG_HIRES_BACKGROUNDS == true)
						sprintf(material[i].string, "Data/verdict/title/bg_vs3H");
				}
			}
			 
			// Dog1...
			sprintf(itemp_string.string, "Data/verdict/chars/dog_p1");

            if( strcmp( material[i].string, itemp_string.string ) == 0)
			{
				sprintf(material[i].string, "Data/verdict/chars/dog1"); // Charlie

				if(VG_1_CHARACTER != VG_TRAINER)
					sprintf(material[i].string, "Data/verdict/chars/dog1"); // Charlie
				if(VG_1_CHARACTER == VG_TRAINER)
					sprintf(material[i].string, "Data/verdict/chars/dog2"); // Max
				if(VG_1_CHARACTER == VG_SIU)
					sprintf(material[i].string, "Data/verdict/chars/pigeon1"); // White pigeon
				if(VG_1_CHARACTER == VG_SAIZO)
					sprintf(material[i].string, "Data/verdict/chars/eagle1"); // Eagle

				if(VG_1_CHARACTER == VG_MINSO && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/chars/dog2"); // Max
				if(VG_1_CHARACTER == VG_SIU && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/chars/pigeon2"); // Grey pigeon

			} 

			// Dog2... 
			sprintf(itemp_string.string, "Data/verdict/chars/dog_p2"); // Max

            if( strcmp( material[i].string, itemp_string.string ) == 0)
			{
				sprintf(material[i].string, "Data/verdict/chars/dog1"); // Max

				if(VG_2_CHARACTER == VG_TRAINER)
					sprintf(material[i].string, "Data/verdict/chars/dog2"); // Max

				if(VG_2_CHARACTER == VG_SIU)
					sprintf(material[i].string, "Data/verdict/chars/pigeon1"); // White pigeon
				if(VG_2_CHARACTER == VG_SIU && VG_IS_AN_ALTER == true)
					sprintf(material[i].string, "Data/verdict/chars/pigeon2"); // Grey pigeon

				if(VG_2_CHARACTER == VG_SAIZO)
					sprintf(material[i].string, "Data/verdict/chars/eagle1"); // Eagle

				if(VG_2_CHARACTER == VG_MINSO && VG_IS_AN_ALTER == true)
					sprintf(material[i].string, "Data/verdict/chars/dog2"); // Max

			}

			sprintf(itemp_string.string, "Data/verdict/sheet/test");

            if( strcmp( material[i].string, itemp_string.string ) == 0)
			{
				if(VG_1_CHARACTER == VG_GYEONG)
					sprintf(material[i].string, "Data/verdict/sheet/gyeong"); 
				if(VG_1_CHARACTER == VG_SIU)
					sprintf(material[i].string, "Data/verdict/sheet/siu"); 
				if(VG_1_CHARACTER == VG_MINSO)
					sprintf(material[i].string, "Data/verdict/sheet/minso"); 
				if(VG_1_CHARACTER == VG_REESE)
					sprintf(material[i].string, "Data/verdict/sheet/reese"); 
				if(VG_1_CHARACTER == VG_YOHAN)
					sprintf(material[i].string, "Data/verdict/sheet/yohan"); 
				if(VG_1_CHARACTER == VG_JAE)
					sprintf(material[i].string, "Data/verdict/sheet/jae"); 
				if(VG_1_CHARACTER == VG_GUN)
					sprintf(material[i].string, "Data/verdict/sheet/gun"); 
				if(VG_1_CHARACTER == VG_HYUK)
					sprintf(material[i].string, "Data/verdict/sheet/hyuk"); 
				if(VG_1_CHARACTER == VG_SANG)
					sprintf(material[i].string, "Data/verdict/sheet/sang"); 
				if(VG_1_CHARACTER == VG_TRAINER)
					sprintf(material[i].string, "Data/verdict/sheet/trainer"); 
				if (VG_1_CHARACTER == VG_SHO)
					sprintf(material[i].string, "Data/verdict/sheet/sho");
				if (VG_1_CHARACTER == VG_TIA)
					sprintf(material[i].string, "Data/verdict/sheet/tia");
				if (VG_1_CHARACTER == VG_SAIZO)
					sprintf(material[i].string, "Data/verdict/sheet/saizo");
				if(VG_1_CHARACTER == VG_KENNEDY)
					sprintf(material[i].string, "Data/verdict/sheet/kennedy"); 

				if(VG_1_CHARACTER == VG_GYEONG && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/toyun"); 
				if(VG_1_CHARACTER == VG_SIU && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/daesu"); 
				if(VG_1_CHARACTER == VG_MINSO && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/mia"); 
				if(VG_1_CHARACTER == VG_REESE && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/bob"); 
				if(VG_1_CHARACTER == VG_YOHAN && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/sungki"); 
				if(VG_1_CHARACTER == VG_JAE && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/sapporo"); 
				if(VG_1_CHARACTER == VG_GUN && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/konu"); 
				if(VG_1_CHARACTER == VG_HYUK && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/yejun"); 

			}

			sprintf(itemp_string.string, "Data/verdict/sheet/test1");

            if( strcmp( material[i].string, itemp_string.string ) == 0)
			{
				if(VG_1_CHARACTER == VG_GYEONG)      
					sprintf(material[i].string, "Data/verdict/sheet/gyeong1"); 
				if(VG_1_CHARACTER == VG_SIU)
					sprintf(material[i].string, "Data/verdict/sheet/siu1"); 
				if(VG_1_CHARACTER == VG_MINSO)
					sprintf(material[i].string, "Data/verdict/sheet/minso1"); 
				if(VG_1_CHARACTER == VG_REESE)
					sprintf(material[i].string, "Data/verdict/sheet/reese1"); 
				if(VG_1_CHARACTER == VG_YOHAN)
					sprintf(material[i].string, "Data/verdict/sheet/yohan1"); 
				if(VG_1_CHARACTER == VG_JAE)
					sprintf(material[i].string, "Data/verdict/sheet/jae1"); 
				if(VG_1_CHARACTER == VG_GUN)
					sprintf(material[i].string, "Data/verdict/sheet/gun1"); 
				if(VG_1_CHARACTER == VG_HYUK)
					sprintf(material[i].string, "Data/verdict/sheet/hyuk1"); 
				if(VG_1_CHARACTER == VG_SANG)
					sprintf(material[i].string, "Data/verdict/sheet/sang1"); 
				if(VG_1_CHARACTER == VG_TRAINER)
					sprintf(material[i].string, "Data/verdict/sheet/trainer1"); 
				if (VG_1_CHARACTER == VG_SHO)
					sprintf(material[i].string, "Data/verdict/sheet/sho1");
				if (VG_1_CHARACTER == VG_TIA)
					sprintf(material[i].string, "Data/verdict/sheet/tia1");
				if (VG_1_CHARACTER == VG_SAIZO)
					sprintf(material[i].string, "Data/verdict/sheet/saizo1");
				if(VG_1_CHARACTER == VG_KENNEDY)
					sprintf(material[i].string, "Data/verdict/sheet/kennedy1"); 

				if(VG_1_CHARACTER == VG_GYEONG && VG_IS_AN_ALTER_P1 == true)      
					sprintf(material[i].string, "Data/verdict/sheet/toyun1"); 
				if(VG_1_CHARACTER == VG_SIU && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/daesu1"); 
				if(VG_1_CHARACTER == VG_MINSO && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/mia1"); 
				if(VG_1_CHARACTER == VG_REESE && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/bob1"); 
				if(VG_1_CHARACTER == VG_YOHAN && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/sungki1"); 
				if(VG_1_CHARACTER == VG_JAE && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/sapporo1"); 
				if(VG_1_CHARACTER == VG_GUN && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/konu1"); 
				if(VG_1_CHARACTER == VG_HYUK && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/sheet/yejun1"); 
			}

			sprintf(itemp_string.string, "Data/verdict/chars/test");

            if( strcmp( material[i].string, itemp_string.string ) == 0)
			{
				if(VG_1_CHARACTER == VG_GYEONG)
					sprintf(material[i].string, "Data/verdict/chars/gyeong"); 
				if(VG_1_CHARACTER == VG_SIU)
					sprintf(material[i].string, "Data/verdict/chars/siu"); 
				if(VG_1_CHARACTER == VG_MINSO)
					sprintf(material[i].string, "Data/verdict/chars/minso"); 
				if(VG_1_CHARACTER == VG_REESE)
					sprintf(material[i].string, "Data/verdict/chars/reese"); 
				if(VG_1_CHARACTER == VG_YOHAN)
					sprintf(material[i].string, "Data/verdict/chars/yohan"); 
				if(VG_1_CHARACTER == VG_JAE)
					sprintf(material[i].string, "Data/verdict/chars/jae"); 
				if(VG_1_CHARACTER == VG_GUN)
					sprintf(material[i].string, "Data/verdict/chars/gun"); 
				if(VG_1_CHARACTER == VG_HYUK)
				{
					if(VG_GAME_MODE != VG_STORY_MODE)
						sprintf(material[i].string, "Data/verdict/chars/hyuk"); 
					else
					{
						if(VG_CURRENT_STORY_SCENE <= 2)
							sprintf(material[i].string, "Data/verdict/chars/hyuk_non"); 
						else
							sprintf(material[i].string, "Data/verdict/chars/hyuk"); 
					}
				} 
				if (VG_1_CHARACTER == VG_SHO)
					sprintf(material[i].string, "Data/verdict/chars/sho");
				if (VG_1_CHARACTER == VG_TIA)
					sprintf(material[i].string, "Data/verdict/chars/tia");
				if (VG_1_CHARACTER == VG_SAIZO)
					sprintf(material[i].string, "Data/verdict/chars/saizo");
				if (VG_1_CHARACTER == VG_KENNEDY)
					sprintf(material[i].string, "Data/verdict/chars/kennedy");

				if(VG_1_CHARACTER == VG_GYEONG && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/chars/alters/toyun"); 
				if(VG_1_CHARACTER == VG_SIU && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/chars/alters/daesu"); 
				if(VG_1_CHARACTER == VG_MINSO && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/chars/alters/mia"); 
				if(VG_1_CHARACTER == VG_REESE && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/chars/alters/bob"); 
				if(VG_1_CHARACTER == VG_YOHAN && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/chars/alters/sungki"); 
				if(VG_1_CHARACTER == VG_JAE && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/chars/alters/sapporo"); 
				if(VG_1_CHARACTER == VG_GUN && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/chars/alters/konu"); 
				if(VG_1_CHARACTER == VG_HYUK && VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/chars/alters/yejun"); 

				if(VG_1_CHARACTER == VG_SANG)
					sprintf(material[i].string, "Data/verdict/chars/sang"); 
				if(VG_1_CHARACTER == VG_TRAINER)
					sprintf(material[i].string, "Data/verdict/chars/trainer"); 
			} 

			sprintf(itemp_string.string, "Data/verdict/chars/test1"); 

			if (strcmp(material[i].string, itemp_string.string) == 0)
			{
				if (VG_2_CHARACTER == VG_GYEONG)
					sprintf(material[i].string, "Data/verdict/chars/gyeong");
				if (VG_2_CHARACTER == VG_SIU)
					sprintf(material[i].string, "Data/verdict/chars/siu");
				if (VG_2_CHARACTER == VG_MINSO)
					sprintf(material[i].string, "Data/verdict/chars/minso");
				if (VG_2_CHARACTER == VG_REESE)
					sprintf(material[i].string, "Data/verdict/chars/reese");
				if (VG_2_CHARACTER == VG_YOHAN)
					sprintf(material[i].string, "Data/verdict/chars/yohan");
				if (VG_2_CHARACTER == VG_JAE)
					sprintf(material[i].string, "Data/verdict/chars/jae");
				if (VG_2_CHARACTER == VG_GUN)
					sprintf(material[i].string, "Data/verdict/chars/gun");
				if (VG_2_CHARACTER == VG_HYUK)
					sprintf(material[i].string, "Data/verdict/chars/hyuk");
				if (VG_2_CHARACTER == VG_SANG)
					sprintf(material[i].string, "Data/verdict/chars/sang");
				if (VG_2_CHARACTER == VG_TRAINER)
					sprintf(material[i].string, "Data/verdict/chars/trainer");
				if (VG_2_CHARACTER == VG_SHO)
					sprintf(material[i].string, "Data/verdict/chars/sho");
				if (VG_2_CHARACTER == VG_TIA)
					sprintf(material[i].string, "Data/verdict/chars/tia");
				if (VG_2_CHARACTER == VG_SAIZO)
					sprintf(material[i].string, "Data/verdict/chars/saizo");
				if (VG_2_CHARACTER == VG_KENNEDY)
					sprintf(material[i].string, "Data/verdict/chars/kennedy");

				// Load in secondary costumes...
				if (VG_GAME_MODE == VG_ARCADE_MODE)
				if (VG_1_CHARACTER == VG_2_CHARACTER)
				{
					if (VG_2_CHARACTER == VG_SHO)
						sprintf(material[i].string, "Data/verdict/chars/colors/sho");
					if (VG_2_CHARACTER == VG_TIA)
						sprintf(material[i].string, "Data/verdict/chars/colors/tia");
					if (VG_2_CHARACTER == VG_SAIZO)
						sprintf(material[i].string, "Data/verdict/chars/colors/saizo");
					if (VG_2_CHARACTER == VG_SANG)
						sprintf(material[i].string, "Data/verdict/chars/colors/sang");
				}

				// Load in secondary costumes...
				if(VG_IS_AN_ALTER == true) 
				{ 

					if(VG_2_CHARACTER == VG_GYEONG) 
						sprintf(material[i].string, "Data/verdict/chars/alters/toyun"); 
					if(VG_2_CHARACTER == VG_SIU)
						sprintf(material[i].string, "Data/verdict/chars/alters/daesu"); 
					if(VG_2_CHARACTER == VG_MINSO)
						sprintf(material[i].string, "Data/verdict/chars/alters/mia"); 
					if(VG_2_CHARACTER == VG_REESE)
						sprintf(material[i].string, "Data/verdict/chars/alters/bob"); 
					if(VG_2_CHARACTER == VG_YOHAN)
						sprintf(material[i].string, "Data/verdict/chars/alters/sungki"); 
					if(VG_2_CHARACTER == VG_JAE) 
						sprintf(material[i].string, "Data/verdict/chars/alters/sapporo"); 
					if(VG_2_CHARACTER == VG_GUN) 
						sprintf(material[i].string, "Data/verdict/chars/alters/konu"); 
					if(VG_2_CHARACTER == VG_HYUK) 
						sprintf(material[i].string, "Data/verdict/chars/alters/yejun"); 

					if(VG_IS_AN_ALTER_P1 == true && VG_2_CHARACTER == VG_GYEONG && VG_1_CHARACTER == VG_GYEONG) 
						sprintf(material[i].string, "Data/verdict/chars/colors/toyun"); 
					if(VG_IS_AN_ALTER_P1 == true && VG_2_CHARACTER == VG_SIU && VG_1_CHARACTER == VG_SIU)
						sprintf(material[i].string, "Data/verdict/chars/colors/daesu"); 
					if(VG_IS_AN_ALTER_P1 == true && VG_2_CHARACTER == VG_MINSO && VG_1_CHARACTER == VG_MINSO)
						sprintf(material[i].string, "Data/verdict/chars/colors/mia"); 
					if(VG_IS_AN_ALTER_P1 == true && VG_2_CHARACTER == VG_REESE && VG_1_CHARACTER == VG_REESE)
						sprintf(material[i].string, "Data/verdict/chars/colors/bob"); 
					if(VG_IS_AN_ALTER_P1 == true && VG_2_CHARACTER == VG_YOHAN && VG_1_CHARACTER == VG_YOHAN)
						sprintf(material[i].string, "Data/verdict/chars/colors/sungki"); 
					if(VG_IS_AN_ALTER_P1 == true && VG_2_CHARACTER == VG_JAE && VG_1_CHARACTER == VG_JAE)
						sprintf(material[i].string, "Data/verdict/chars/colors/sapporo"); 
					if(VG_IS_AN_ALTER_P1 == true && VG_2_CHARACTER == VG_GUN && VG_1_CHARACTER == VG_GUN)
						sprintf(material[i].string, "Data/verdict/chars/colors/konu"); 
					if(VG_IS_AN_ALTER_P1 == true && VG_2_CHARACTER == VG_HYUK && VG_1_CHARACTER == VG_HYUK)
						sprintf(material[i].string, "Data/verdict/chars/colors/yejun"); 
				}  
				// Load in secondary costumes...
				if(VG_GAME_MODE == VG_VERSUS_MODE && TEST_ALTERS == 0) 
				if(VG_1_CHARACTER == VG_2_CHARACTER && VG_IS_AN_ALTER == false)
				{

					if(VG_2_CHARACTER == VG_GYEONG)
						sprintf(material[i].string, "Data/verdict/chars/colors/gyeong"); 
					if(VG_2_CHARACTER == VG_SIU)
						sprintf(material[i].string, "Data/verdict/chars/colors/siu"); 
					if(VG_2_CHARACTER == VG_MINSO)
						sprintf(material[i].string, "Data/verdict/chars/colors/minso"); 
					if(VG_2_CHARACTER == VG_REESE)
						sprintf(material[i].string, "Data/verdict/chars/colors/reese"); 
					if(VG_2_CHARACTER == VG_YOHAN)
						sprintf(material[i].string, "Data/verdict/chars/colors/yohan"); 
					if(VG_2_CHARACTER == VG_JAE)
						sprintf(material[i].string, "Data/verdict/chars/colors/jae"); 
					if(VG_2_CHARACTER == VG_GUN)
						sprintf(material[i].string, "Data/verdict/chars/colors/gun"); 
					if(VG_2_CHARACTER == VG_HYUK)
						sprintf(material[i].string, "Data/verdict/chars/colors/hyuk"); 
					if (VG_2_CHARACTER == VG_SHO)
						sprintf(material[i].string, "Data/verdict/chars/colors/sho");
					if (VG_2_CHARACTER == VG_TIA)
						sprintf(material[i].string, "Data/verdict/chars/colors/tia");
					if (VG_2_CHARACTER == VG_SAIZO)
						sprintf(material[i].string, "Data/verdict/chars/colors/saizo");
					if (VG_2_CHARACTER == VG_SANG)
						sprintf(material[i].string, "Data/verdict/chars/colors/sang");
					if (VG_2_CHARACTER == VG_KENNEDY)
						sprintf(material[i].string, "Data/verdict/chars/colors/kennedy");
				}  
				 
			}  

			sprintf(itemp_string.string, "Data/verdict/front/Select_faces");  

			if (REPLACE_SANG_WITH_KENNEDY == 1)
			{
				if (strcmp(material[i].string, itemp_string.string) == 0)
				{
					sprintf(material[i].string, "Data/verdict/front/Select_facesWVG");
				}
			}
            

			sprintf(itemp_string.string, "Data/verdict/front/VS_faces");  

			if(!(episode == 6 && scene == 1)) // Character select screen...
            if( strcmp( material[i].string, itemp_string.string ) == 0)   
			{
				sprintf(material[i].string, "Data/verdict/front/VS_faces");

				if(VG_IS_AN_ALTER_P1 == true)
					sprintf(material[i].string, "Data/verdict/front/VS_faces_alters");
			}

			sprintf(itemp_string.string, "Data/verdict/front/VS_faces1"); 

			if(!(episode == 6 && scene == 1)) // Character select screen...
            if( strcmp( material[i].string, itemp_string.string ) == 0)   
			{

				sprintf(material[i].string, "Data/verdict/front/VS_faces"); 

				if(VG_IS_AN_ALTER == true)
					sprintf(material[i].string, "Data/verdict/front/VS_faces_alters");

				if(VG_GAME_MODE == VG_VERSUS_MODE)
				if(VG_1_CHARACTER == VG_2_CHARACTER && VG_IS_AN_ALTER == false)
					sprintf(material[i].string, "Data/verdict/front/VS_faces1");

			}
 
		/*	sprintf(itemp_string.string, "Data/verdict/front/VS_faces1B"); 

			if(!(episode == 6 && scene == 1)) // Character select screen...
            if( strcmp( material[i].string, itemp_string.string ) == 0)   
			{

				sprintf(material[i].string, "Data/verdict/front/VS_faces1"); 

				if(VG_GAME_MODE == VG_VERSUS_MODE)
				if(VG_1_CHARACTER == VG_2_CHARACTER && VG_IS_AN_ALTER == false)
					sprintf(material[i].string, "Data/verdict/front/VS_faces1B");

				if(VG_GAME_MODE == VG_ARCADE_MODE)
				if(VG_1_CHARACTER == VG_2_CHARACTER)
			    if(VG_1_CHARACTER == VG_SANG || VG_1_CHARACTER == VG_SHO || VG_1_CHARACTER == VG_TIA || VG_1_CHARACTER == VG_SAIZO)
					sprintf(material[i].string, "Data/verdict/front/VS_faces1B");
			}*/

			sprintf(itemp_string.string, "Data/verdict/story/Faces_Gyeong"); 

            if( strcmp( material[i].string, itemp_string.string ) == 0)   
			{

				if(VG_1_CHARACTER == VG_GYEONG)
					sprintf(material[i].string, "Data/verdict/story/Faces_Gyeong"); 
				if(VG_1_CHARACTER == VG_SIU)
					sprintf(material[i].string, "Data/verdict/story/Faces_Siu"); 
				if(VG_1_CHARACTER == VG_MINSO)
					sprintf(material[i].string, "Data/verdict/story/Faces_Minso"); 
				if(VG_1_CHARACTER == VG_REESE)
					sprintf(material[i].string, "Data/verdict/story/Faces_Reese"); 
				if(VG_1_CHARACTER == VG_YOHAN)
					sprintf(material[i].string, "Data/verdict/story/Faces_Yohan"); 
				if(VG_1_CHARACTER == VG_JAE)
					sprintf(material[i].string, "Data/verdict/story/Faces_Jae"); 
				if(VG_1_CHARACTER == VG_GUN)
					sprintf(material[i].string, "Data/verdict/story/Faces_Gun"); 
				if(VG_1_CHARACTER == VG_HYUK)
					sprintf(material[i].string, "Data/verdict/story/Faces_Hyuk"); 
				if (VG_1_CHARACTER == VG_SHO)
					sprintf(material[i].string, "Data/verdict/story/Faces_Sho");
				if (VG_1_CHARACTER == VG_TIA)
					sprintf(material[i].string, "Data/verdict/story/Faces_Tia");
				if (VG_1_CHARACTER == VG_SAIZO)
					sprintf(material[i].string, "Data/verdict/story/Faces_Saizo");
				if (VG_1_CHARACTER == VG_KENNEDY)
					sprintf(material[i].string, "Data/verdict/story/Faces_Kennedy");
			}  
  
			sprintf(itemp_string.string, "Data/verdict/story/Faces_Toyun"); 

            if( strcmp( material[i].string, itemp_string.string ) == 0)   
			{

				if(VG_2_CHARACTER == VG_GYEONG)
					sprintf(material[i].string, "Data/verdict/story/Faces_Gyeong"); 
				if(VG_2_CHARACTER == VG_SIU)
					sprintf(material[i].string, "Data/verdict/story/Faces_Siu"); 
				if(VG_2_CHARACTER == VG_MINSO)
					sprintf(material[i].string, "Data/verdict/story/Faces_Minso"); 
				if(VG_2_CHARACTER == VG_REESE)
					sprintf(material[i].string, "Data/verdict/story/Faces_Reese"); 
				if(VG_2_CHARACTER == VG_YOHAN)
					sprintf(material[i].string, "Data/verdict/story/Faces_Yohan"); 
				if(VG_2_CHARACTER == VG_JAE)
					sprintf(material[i].string, "Data/verdict/story/Faces_Jae"); 
				if(VG_2_CHARACTER == VG_GUN)
					sprintf(material[i].string, "Data/verdict/story/Faces_Gun"); 
				if(VG_2_CHARACTER == VG_HYUK)
					sprintf(material[i].string, "Data/verdict/story/Faces_Hyuk"); 
				if (VG_2_CHARACTER == VG_SHO)
					sprintf(material[i].string, "Data/verdict/story/Faces_Sho");
				if (VG_2_CHARACTER == VG_TIA)
					sprintf(material[i].string, "Data/verdict/story/Faces_Tia");
				if (VG_2_CHARACTER == VG_SAIZO)
					sprintf(material[i].string, "Data/verdict/story/Faces_Saizo");
				if (VG_2_CHARACTER == VG_KENNEDY)
					sprintf(material[i].string, "Data/verdict/story/Faces_Kennedy");

				if(VG_2_CHARACTER == VG_SANG)
					sprintf(material[i].string, "Data/verdict/story/Faces_Sang"); 
				if(VG_2_CHARACTER == VG_TRAINER)
					sprintf(material[i].string, "Data/verdict/story/Faces_Trainer"); 

				if(VG_2_CHARACTER == VG_GYEONG && VG_IS_AN_ALTER == true)
					sprintf(material[i].string, "Data/verdict/story/Faces_Toyun"); 
				if(VG_2_CHARACTER == VG_SIU && VG_IS_AN_ALTER == true)
					sprintf(material[i].string, "Data/verdict/story/Faces_Daesu"); 
				if(VG_2_CHARACTER == VG_MINSO && VG_IS_AN_ALTER == true) 
					sprintf(material[i].string, "Data/verdict/story/Faces_Mia"); 
				if(VG_2_CHARACTER == VG_REESE && VG_IS_AN_ALTER == true)
					sprintf(material[i].string, "Data/verdict/story/Faces_Bob"); 
				if(VG_2_CHARACTER == VG_YOHAN && VG_IS_AN_ALTER == true) 
					sprintf(material[i].string, "Data/verdict/story/Faces_Sungki"); 
				if(VG_2_CHARACTER == VG_JAE && VG_IS_AN_ALTER == true)
					sprintf(material[i].string, "Data/verdict/story/Faces_Sapporo"); 
				if(VG_2_CHARACTER == VG_GUN && VG_IS_AN_ALTER == true)
					sprintf(material[i].string, "Data/verdict/story/Faces_Konu"); 
				if(VG_2_CHARACTER == VG_HYUK && VG_IS_AN_ALTER == true)
					sprintf(material[i].string, "Data/verdict/story/Faces_Yejun"); 

				// Kyung faces... 
				if(VG_1_CHARACTER == VG_JAE)
				if(VG_CURRENT_STORY_SCENE == 6 || VG_CURRENT_STORY_SCENE == 10)
					sprintf(material[i].string, "Data/verdict/story/Faces_kyung");
				 
			}   

			sprintf(itemp_string.string, "Data/verdict/story/bg/BG_ALLEYWAY"); 

            if( strcmp( material[i].string, itemp_string.string ) == 0)   
			{ 

				if(VG_BACKGROUND == VG_GYEONG)
					sprintf(material[i].string, "Data/verdict/story/bg/BG_ALLEYWAY"); 
				if(VG_BACKGROUND == VG_YOHAN)
					sprintf(material[i].string, "Data/verdict/story/bg/BG_BIKESHOP"); 
				if(VG_BACKGROUND == VG_SANG)
					sprintf(material[i].string, "Data/verdict/story/bg/BG_COURT"); 
				if(VG_BACKGROUND == VG_TRAINER)
					sprintf(material[i].string, "Data/verdict/story/bg/BG_DOJO"); 
				if(VG_BACKGROUND == VG_HYUK)
					sprintf(material[i].string, "Data/verdict/story/bg/BG_HIGHWAY"); 
				if(VG_BACKGROUND == VG_JAE)
					sprintf(material[i].string, "Data/verdict/story/bg/BG_NIGHTCLUB"); 
				if(VG_BACKGROUND == VG_REESE)
					sprintf(material[i].string, "Data/verdict/story/bg/BG_PARK"); 
				if(VG_BACKGROUND == VG_GUN)
					sprintf(material[i].string, "Data/verdict/story/bg/BG_PRISON"); 
				if(VG_BACKGROUND == VG_MINSO)
					sprintf(material[i].string, "Data/verdict/story/bg/BG_TRAFFIC"); 
				if(VG_BACKGROUND == VG_SIU)
					sprintf(material[i].string, "Data/verdict/story/bg/BG_TRAIN"); 
				if (VG_BACKGROUND == VG_SHO)
					sprintf(material[i].string, "Data/verdict/story/bg/BG_TRAIN");
				if (VG_BACKGROUND == VG_TIA)
					sprintf(material[i].string, "Data/verdict/story/bg/BG_TRAIN");
				if (VG_BACKGROUND == VG_SAIZO)
					sprintf(material[i].string, "Data/verdict/story/bg/BG_TRAIN");
				if (VG_BACKGROUND == VG_KENNEDY)
					sprintf(material[i].string, "Data/verdict/story/bg/BG_TRAIN");

				// Endings Background... 
				if(VG_GAME_MODE == VG_ARCADE_MODE)
				{
					sprintf(material[i].string, "Data/verdict/story/bg/BG_LAST_ARCADE");

					if(VG_IS_AN_ALTER_P1 == true)
						sprintf(material[i].string, "Data/verdict/story/bg/BG_LAST_ARCADE_ALTER");  
				}

			}  

        }  
 
    fclose(fpt); 

	} // is file open

    memset( animation_fx, 0, sizeof(animation_fx) );
    
	for( int loop=0;loop<numsubmtls;loop++)
	if(loop >= 0 && loop < 200)
    {
        if( texture_fx[loop] == 2 || texture_fx[loop] == 3 || texture_fx[loop] == 4)
            animation_fx[loop] = LoadAnim( material[loop], loop, -1);
        else
            animation_fx[loop] = -1;   
		
		#if IS_USING_DIRECTX == 1   

		if(RENDERER == RENDER_DIRECTX)    
		{	
#ifdef XB1
			char temp_string[256];
			strcpy(temp_string, material[loop].string);
			strcat(temp_string, ".png");
			char tempfilename[200];
			if (strstr(temp_string, "./Assets/") == NULL)
			{

				sprintf(tempfilename, "./Assets/%s", temp_string);
				for (int i = 0; tempfilename[i]; i++) {
					tempfilename[i] = tolower(tempfilename[i]);
				}
			}


			if (loop >= 0 && loop < 100)
			{
				//sLoadCompressedTGADX(&stexture, temp_string);
				bool loaded_in_stock = false;
				for (int stock_idx = 0; stock_idx < 500; stock_idx++)
				{
					//if(strcmp(texture_STOCK[stock_idx].name, "NULL") != 0)
					//printf("STOCK %d %s\n", stock_idx, texture_STOCK[stock_idx].name);

					if (strcmp(texture_STOCK[stock_idx].name, tempfilename) == 0)
					{
						texture[loop] = texture_STOCK[stock_idx];
						loaded_in_stock = true;
						//printf("TEX LOADED (STOCK) %s\n", tempfilename);
					}
				}

				if (loaded_in_stock == false)
				{
					//int retval = _Application._GraphicsLoader->createTextureFromFile(&texture[loop].tex, tempfilename);
					
					std::wstring wcpath(200, L'#');
					mbstowcs(&wcpath[0], tempfilename, 200);
					int width, height, n;
					unsigned char* data = stbi_load(tempfilename, &width, &height, &n, 4);
					texture[loop].tex = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);
					SDL_UpdateTexture(texture[loop].tex, NULL, data, width * 4);
					SDL_SetTextureBlendMode(texture[loop].tex, SDL_BLENDMODE_BLEND);
					SDL_SetTextureSamplerMode(texture[loop].tex, 0); // 0 = clamp 1 = mirror 2 = clampmirror
					//global_sample->LoadTexture(wcpath.c_str(), &texture[loop], w, h);
					//if (retval == SCE_OK)
					//{
					strcpy(texture[loop].name, tempfilename);
					//global_sample->SetSampler(&texture[loop], PERSONAL_WRAP_CLAMP);
					//printf("TEX LOADED %s\n", tempfilename);

					texture_STOCK[counter_STOCK] = texture[loop];

					counter_STOCK++;
					/*}
					else
					{
						strcpy(texture[loop].name, "NULL");
						//printf("TEX NOT LOADED %s\n", tempfilename);
					}*/
				}



				//_Application._GraphicsLoader->createTextureFromMemory(&texture[loop].tex, &stexture.imageData[0], stexture.imageSize);

			}

			/*if (stexture.imageData != NULL)
			{
			free(stexture.imageData);
			}*/
#elif PS4
			char temp_string[256];
			strcpy(temp_string, material[loop].string);
			strcat(temp_string, ".png");
			char tempfilename[200];
			if (strstr(temp_string, "/app0/") == NULL)
			{
				
				sprintf(tempfilename, "/app0/%s", temp_string);
				for (int i = 0; tempfilename[i]; i++) {
					tempfilename[i] = tolower(tempfilename[i]);
				}
			}


			if (loop >= 0 && loop < 100)
			{
				//sLoadCompressedTGADX(&stexture, temp_string);
				bool loaded_in_stock = false;
				for (int stock_idx = 0; stock_idx < 500; stock_idx++)
				{
					//if(strcmp(texture_STOCK[stock_idx].name, "NULL") != 0)
						//printf("STOCK %d %s\n", stock_idx, texture_STOCK[stock_idx].name);

					if (strcmp(texture_STOCK[stock_idx].name, tempfilename) == 0)
					{
						texture[loop] = texture_STOCK[stock_idx];
						loaded_in_stock = true;
						//printf("TEX LOADED (STOCK) %s\n", tempfilename);
					}
				}

				if (loaded_in_stock == false)
				{
					char new_path[200];
					strcpy(new_path, tempfilename);
					if (strstr(new_path, "font") != NULL)
					{
						if (_Application.isMainButtonCircle == true)
						{
							new_path[strlen(new_path) - 4] = '\0';
							strcat(new_path, "_jp.png");
						}
					}
					int retval = _Application._GraphicsLoader->createTextureFromFile(&texture[loop].tex, new_path);
					
					if (retval == SCE_OK)
					{
						strcpy(texture[loop].name, tempfilename);
						texture[loop].tex->setAddrMode(sce::SampleUtil::Graphics::kTextureAddrModeClamp, sce::SampleUtil::Graphics::kTextureAddrModeClamp);
						texture[loop].tex->setFilter(sce::SampleUtil::Graphics::kTextureFilterPoint, sce::SampleUtil::Graphics::kTextureFilterPoint, sce::SampleUtil::Graphics::kTextureMipFilterDisabled);
						//printf("TEX LOADED %s\n", tempfilename);

						texture_STOCK[counter_STOCK] = texture[loop];

						counter_STOCK++;
					}
					else
					{
						strcpy(texture[loop].name, "NULL");
						//printf("TEX NOT LOADED %s\n", tempfilename);
					}
				}
				
				

				//_Application._GraphicsLoader->createTextureFromMemory(&texture[loop].tex, &stexture.imageData[0], stexture.imageSize);
				
			}

			/*if (stexture.imageData != NULL)
			{
				free(stexture.imageData);
			}*/
#endif
		}

		#endif

#ifdef SWITCH
		if(RENDERER == RENDER_OPENGL)              
		{

			if( texture_fx[loop] == 1 || texture_fx[loop] == 3 || texture_fx[loop] == 4 || texture_fx[loop] == 5)
			{
				strcat(material[loop].string,".tga");
				if(!(sLoadTGA(&stexture, material[loop].string)) )
					return 0;

			}
			else
			{
				strcat(material[loop].string,".tga");
				if(!(LoadTGA(&stexture, material[loop].string)) )
					return 0;

			}  

			sc_blur = false;

			glGenTextures(1, &stexture.texID);		
 
			texID[loop] = stexture.texID;   
            	
			glBindTexture(GL_TEXTURE_2D, stexture.texID); 

			if(sc_blur == true)  
			{ 
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}
			if(sc_blur == false)
			{        
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}                			
        
			if(stexture.bpp==24)
				type = GL_RGB; 
			else
				type = GL_RGBA;  

			glTexImage2D(GL_TEXTURE_2D, 0, type, stexture.width, stexture.height, 0, type, GL_UNSIGNED_BYTE, stexture.imageData);

			if(stexture.imageData) 
			{
				free(stexture.imageData);
			}

		}
#endif

#ifdef DREAMCAST

		if(RENDERER == RENDER_OPENGL)              
		{
			
			//strcat(material[loop].string,".tex");
			char temp_string[256];
			strcpy(temp_string, material[loop].string);
			strcat(temp_string, ".tex");
			char tempfilename[200];
			if (strstr(temp_string, "cd/") == NULL)
			{
				
				sprintf(tempfilename, "cd/%s", temp_string);
				for (int i = 0; tempfilename[i]; i++) {
					tempfilename[i] = tolower(tempfilename[i]);
				}
			}

			int loadType = 0;

			for(int lol = 0; lol < TEXNUMBER2048x256; lol++)
			{
				if(strstr(tempfilename, path2048x256[lol]) != NULL)
				{
					loadType = 2;
				}	
			}

			for(int lol = 0; lol < TEXNUMBER2048x2048; lol++)
			{
				if(strstr(tempfilename, path2048x2048[lol]) != NULL)
				{
					loadType = 4;
				}	
			}
			

			if(loadType == 0)
			{
				Image image1;
				if (!ImageLoad(tempfilename, &image1)) {
					printf("Can't Load Texture %s\n", tempfilename);
	        		return 0;
	    		}

	    		//printf("Load Texture %s\n", tempfilename);

				sc_blur = false;

				unsigned int texID_img;

				glGenTextures(1, &texID_img);		
	 
				texID[loop] = texID_img;  
				//printf("TEX ID %d\n", texID_img);
	            	
				glBindTexture(GL_TEXTURE_2D, texID_img); 

				if(sc_blur == true)  
				{ 
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				}
				if(sc_blur == false)
				{        
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				}                			

				glCompressedTexImage2DARB(GL_TEXTURE_2D, 0, image1.internalFormat, image1.sizeX, image1.sizeY, 0, image1.dataSize, image1.data);

				free(image1.data);
			}
			else
			{
				CustomBigTex customTex;
				if(loadType == 2)
	 			{
	 				texID[loop] = startID2048x256;
	 				customTex.baseID = startID2048x256;
	 				startID2048x256++;
	 			}
	 			else if(loadType == 4)
	 			{
	 				texID[loop] = startID2048x2048;  
	 				customTex.baseID = startID2048x2048;
	 				startID2048x2048++;
	 			}
				for(int lol = 0; lol < loadType; lol++)
				{
					Image image1;
				    char strCTemp[500];
				    strcpy(strCTemp, tempfilename);
				    char *texPosition = strstr(strCTemp, ".tex");
				    if (texPosition != NULL) {
				        sprintf(texPosition, "_%d.tex", lol);
				    }
				    else
				    {
				    	printf("ERROR STR Can't Load Texture %s\n", strCTemp);
		        		return 0;
				    }
					if (!ImageLoad(strCTemp, &image1)) {
						printf("Can't Load Texture %s\n", strCTemp);
		        		return 0;
		    		}

		    		//printf("Load Texture %s\n", newString.c_str());

					sc_blur = false;

					unsigned int texID_img;

					glGenTextures(1, &texID_img);		

					if(lol == 0)
					{
						customTex.topLeft = texID_img;
					}
					else if(lol == 1)
					{
						customTex.topRight = texID_img;
					}
					else if(lol == 2)
					{
						customTex.bottomLeft = texID_img;
					}
					else if(lol == 3)
					{
						customTex.bottomRight = texID_img;
					}

					
					//printf("TEX ID %d\n", texID_img);
		            	
					glBindTexture(GL_TEXTURE_2D, texID_img); 

					if(sc_blur == true)  
					{ 
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					}
					if(sc_blur == false)
					{        
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					}                			

					glCompressedTexImage2DARB(GL_TEXTURE_2D, 0, image1.internalFormat, image1.sizeX, image1.sizeY, 0, image1.dataSize, image1.data);

					free(image1.data);
				}

				if(loadType == 2)
					tex2048x256.push_back(customTex);
				else if(loadType == 4)
					tex2048x2048.push_back(customTex);
				
			}
			


		}

#endif

	}
     
	Status = true; 
                                      
	return Status;										// Return The Status
	
}
             
// ******************************************************************************//
//                                                                               //
//                                 LOAD TEXT                                     //
//                                                                               //
// ******************************************************************************//
     
bool LoadText(sString sfilename)
{

    int num_of_text=0;
    int num_multi_texts=0;
	int dummy_int = 0;
        
    memset( text, 0, sizeof(text) );
    memset( counter, 0, sizeof(counter) );
            
    sprintf( text[5].word, "Keyframe[%i]", dummy_int);
    sprintf( text[6].word, "Game Mode : %i", game_mode);
    sprintf( text[7].word, "Fading : [%i] [%i]", fade_in, fade_out);

    for(int i=0;i<TOTAL_TEXT;i++)
        text[i].alpha=1.0f;
            	
    text[0].x = -0.95f;
    text[0].y = 0.88f;
    
    text[0].width = 0.02f;
    text[0].height = 0.05f;
    
    text[0].id = 0;
    text[0].alpha = 1.0f;
    
    text[1].x = -0.95f;
    text[1].y = 0.95f;
    
    text[1].width = 0.02f;
    text[1].height = 0.05f;
    
    text[1].id = 0;
    text[1].alpha = 1.0f;
    
    text[2].x = -0.95f;
    text[2].y = 0.81f;
      
    text[2].width = 0.02f;
    text[2].height = 0.05f;
     
    text[2].id = 0;
    text[2].alpha = 1.0f;
    
    text[3].x = -0.25f;
    text[3].y = -0.9f;
    
    text[3].width = 0.02f;
    text[3].height = 0.05f;
           
    text[3].id = 0;
    text[3].alpha = 1.0f;
    
 //   if(game_mode != WALK && game_mode != WORLD)
    sprintf( text[3].word, "Placement mode");
 //   else
 //       sprintf( text[3].word, "Camera mode");
     
    text[4].x = -0.95f;
    text[4].y = 0.74f;
     
    text[4].width = 0.02f;
    text[4].height = 0.05f;
     
    text[4].id = 0;
    text[4].alpha = 1.0f;
    
    sprintf( text[4].word, "Editing...");
      
    text[5].x = -0.28f;
    text[5].y = -0.82f;
    
    text[5].width = 0.02f;
    text[5].height = 0.05f;
     
    text[5].id = 0;
    text[5].alpha = 1.0f;
    
    sprintf( text[5].word, "Keyframe[%i]", 0);
     
    text[6].x = -0.95f;
    text[6].y = 0.60f;
     
    text[6].width = 0.02f;
    text[6].height = 0.05f;
     
    text[6].id = 0;
    text[6].alpha = 1.0f;
    
    sprintf( text[6].word, "Game Mode : %i", game_mode);
     
    text[7].x = -0.95f;
    text[7].y = 0.53f;
      
    text[7].width = 0.02f;
    text[7].height = 0.05f;
     
    text[7].id = 0;
    text[7].alpha = 1.0f;
    
    sprintf( text[7].word, "Fading : %i", fade_in);
     
    text[8].x = -0.95f;
    text[8].y = 0.43f;
     
    text[8].width = 0.02f;
    text[8].height = 0.05f;
     
    text[8].id = 0;
    text[8].alpha = 1.0f;
    
    sprintf( text[8].word, "score : %i", 0);    
     
    text[9].x = -0.95f;
    text[9].y = 0.33f;
     
    text[9].width = 0.02f;
    text[9].height = 0.05f;
     
    text[9].id = 0;
    text[9].alpha = 1.0f;
    
    sprintf( text[9].word, "Anims [%i][%i]", 0, 0);    
     
    text[10].x = -0.95f;
    text[10].y = 0.23f;
     
    text[10].width = 0.02f;
    text[10].height = 0.05f;
     
    text[10].id = 0;
    text[10].alpha = 1.0f;
    
    sprintf( text[10].word, "Linked : [%i]", 0);   
     
    text[11].x = -0.95f;
    text[11].y = 0.13f;
     
    text[11].width = 0.02f;
    text[11].height = 0.05f;
     
    text[11].id = 0;
    text[11].alpha = 1.0f;
    
    sprintf( text[11].word, "Priority : [%i]", 0);   
      
    text[12].x = -0.95f;
    text[12].y = 0.03f;
     
    text[12].width = 0.02f;
    text[12].height = 0.05f;
     
    text[12].id = 0;
    text[12].alpha = 1.0f;
    
    sprintf( text[12].word, "Type : NON");   
      
    text[13].x = -0.95f;
    text[13].y = -0.07f;
     
    text[13].width = 0.02f;
    text[13].height = 0.05f;
      
    text[13].id = 0;
    text[13].alpha = 1.0f;
    
    sprintf( text[13].word, "C-BOX : 0");   
      
    text[14].x = -0.95f;
    text[14].y = -0.17f;
     
    text[14].width = 0.02f;
    text[14].height = 0.05f;
     
    text[14].id = 0;
    text[14].alpha = 1.0f;
    
    sprintf( text[14].word, "Mouse_over : 0");   
      
    text[15].x = -0.95f;
    text[15].y = -0.27f;
     
    text[15].width = 0.02f;
    text[15].height = 0.05f;
     
    text[15].id = 0;
    text[15].alpha = 1.0f;
    
    sprintf( text[15].word, "Sector : 0"); 
      
    text[16].x = -0.95f;
    text[16].y = -0.37f;
     
    text[16].width = 0.02f;
    text[16].height = 0.05f;
     
    text[16].id = 0;
    text[16].alpha = 1.0f;
    
    sprintf( text[16].word, "Action : 0"); 
      
    text[17].x = -0.95f;
    text[17].y = -0.47f;
     
    text[17].width = 0.02f;
    text[17].height = 0.05f;
     
    text[17].id = 0;
    text[17].alpha = 1.0f;
    
    sprintf( text[17].word, "rank : 0"); 
      
    text[18].x = -0.95f;
    text[18].y = -0.57f;
      
    text[18].width = 0.02f;
    text[18].height = 0.05f;
     
    text[18].id = 0;
    text[18].alpha = 1.0f;
    
    sprintf( text[18].word, "Action : 0"); 
        
    text[19].x = -0.95f;
    text[19].y = -0.67f;
     
    text[19].width = 0.02f;
    text[19].height = 0.05f;
     
    text[19].id = 0;
    text[19].alpha = 1.0f;
    
    sprintf( text[19].word, "onCreate : 0"); 
        
    text[20].x = -0.95f;
    text[20].y = -0.77f;
     
    text[20].width = 0.02f;
    text[20].height = 0.05f;
     
    text[20].id = 0;
    text[20].alpha = 1.0f;
    
    sprintf( text[20].word, "Action : 0"); 
        
    text[21].x = -0.95f;
    text[21].y = -0.87f;
     
    text[21].width = 0.02f;
    text[21].height = 0.05f;
     
    text[21].id = 0;
    text[21].alpha = 1.0f;
    
    sprintf( text[21].word, "Light : 0"); 
        
    text[22].x = -0.95f;
    text[22].y = -0.97f;
     
    text[22].width = 0.02f;
    text[22].height = 0.05f;
     
    text[22].id = 0;
    text[22].alpha = 1.0f;
    
    sprintf( text[22].word, "Global : 0"); 
                                                               
    // Reserved for TIME && SCORE
      
    for(int i=0;i<TOTAL_TEXT;i++)
	{
        counter[i].alpha=1.0f;
		counter[i].id=0;
	}
             
    counter[0].x = -0.85f;
    counter[0].y = 0.75f;
     
    counter[0].width = 0.02f;
    counter[0].height = 0.05f;
     
    counter[0].id = 0;
    counter[0].alpha = 1.0f;
    
    if(game_mode == GAME)
        sprintf( counter[0].word, "0");  // TIME   
     
    counter[1].x = 0.70f;
    counter[1].y = 0.75f;
      
    counter[1].width = 0.02f;
    counter[1].height = 0.05f;
     
    counter[1].id = 0; 
    counter[1].alpha = 1.0f;
    
    if(game_mode == GAME)
        sprintf( counter[1].word, "0");  // SCORE 
    
    if(game_mode == GAME)
    { 
        counter[2].x = 0.0f;
        counter[2].y = -0.65f;
    }  
    else
    {
        counter[2].x = -0.70f;
        counter[2].y = 0.88f;    // 80    
    }
    
    counter[2].width = 0.02f;
    counter[2].height = 0.04f;
     
    counter[2].id = 0; 
    counter[2].alpha = 1.0f;
        
    sprintf( counter[2].word, "");     

    // MONEY 
    
    counter[3].x = -0.74f;
    counter[3].y = -0.83f; 
    
    counter[3].width = 0.035f;
    counter[3].height = 0.070f;
     
    counter[3].id = 0;  
    counter[3].alpha = 1.0f;
        
    sprintf( counter[3].word, ""); 

    // PASSWORD
         
    counter[4].x = -0.0f;
    counter[4].y = -0.00f;
      
    counter[4].width = 0.02f;
    counter[4].height = 0.06f;
      
    counter[4].id = 0;    
    counter[4].alpha = 1.0f;
        
    sprintf( counter[4].word, "");

    // POTION
          
    counter[5].x = 0.84f;
    counter[5].y = -0.87f; 
      
    counter[5].width = 0.02f; 
    counter[5].height = 0.04f;
      
    counter[5].id = 0; 
    counter[5].alpha = 1.0f;
        
    sprintf( counter[5].word, "");
 
    // DEBUG
      
    counter[6].x = -0.95f; //.6
    counter[6].y = 0.85f;
      
    counter[6].width = 0.02f;
    counter[6].height = 0.04f;
      
    counter[6].id = 0; 
    counter[6].alpha = 1.0f;
        
    sprintf( counter[6].word, "");
    
    // ORDER FORM
       
    counter[7].x = -0.50f;
    counter[7].y = 0.25f;
      
    counter[7].width = 0.03f; 
    counter[7].height = 0.06f;
      
    counter[7].id = 0; 
    counter[7].alpha = 0.0f;
        
    sprintf( counter[7].word, "");
    // ORDER FORM
       
    counter[8].x = -0.50f;
    counter[8].y = 0.10f;
      
    counter[8].width = 0.03f; 
    counter[8].height = 0.06f;
      
    counter[8].id = 0; 
    counter[8].alpha = 0.0f;
        
    sprintf( counter[8].word, "");
        
    // ORDER FORM
       
    counter[9].x = -0.50f;
    counter[9].y = -0.05f;
      
    counter[9].width = 0.03f; 
    counter[9].height = 0.06f;
      
    counter[9].id = 0; 
    counter[9].alpha = 0.0f;
        
    sprintf( counter[9].word, "");
    // ORDER FORM
       
    counter[10].x = -0.50f;
    counter[10].y = -0.20f;
      
    counter[10].width = 0.03f; 
    counter[10].height = 0.06f;
      
    counter[10].id = 0; 
    counter[10].alpha = 0.0f;
        
    sprintf( counter[10].word, "");
    // ORDER FORM
       
    counter[11].x = -0.50f;
    counter[11].y = -0.35f;
      
    counter[11].width = 0.03f; 
    counter[11].height = 0.06f;
      
    counter[11].id = 0; 
    counter[11].alpha = 0.0f;
        
    sprintf( counter[11].word, "");
    // ORDER FORM
       
    counter[12].x = -0.50f;
    counter[12].y = -0.50f;
      
    counter[12].width = 0.03f; 
    counter[12].height = 0.06f;
      
    counter[12].id = 0; 
    counter[12].alpha = 0.0f;
        
    sprintf( counter[12].word, "");
                                            
    // CINEMATIC TEXT if game_mode == CINE
       
    counter[13].x = -0.50f;
    counter[13].y = -0.50f;
      
    counter[13].width = 0.03f; 
    counter[13].height = 0.06f;
      
    counter[13].id = 0; 
    counter[13].alpha = 0.0f;
        
    sprintf( counter[13].word, "");
       
    counter[14].x = -0.50f;
    counter[14].y = -0.50f;
      
    counter[14].width = 0.03f; 
    counter[14].height = 0.06f;
      
    counter[14].id = 9; 
    counter[14].alpha = 0.0f;
        
    sprintf( counter[14].word, "");
       
    counter[15].x = -0.50f;
    counter[15].y = -0.50f;
       
    counter[15].width = 0.03f; 
    counter[15].height = 0.06f;
      
    counter[15].id = 9; 
    counter[15].alpha = 0.0f; 
        
    sprintf( counter[15].word, "");

    return(true);     
}




#endif
