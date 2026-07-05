#ifndef __TGA_H__
#define __TGA_H__

//#include <windows.h>									// Standard windows header
#include <stdio.h>										// Standard I/O header
#ifdef SWITCH
//#include <egl/egl.h>
//#include "glad/glad.h"										// Header for OpenGL32 library
#endif
#include "texture.h"

#ifdef SWITCH
typedef struct
{
	GLubyte Header[12];									// TGA File Header
} TGAHeader;


typedef struct
{
	GLubyte		header[6];								// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;								// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;									// Temporary Variable
	GLuint		type;	
	GLuint		Height;									//Height of Image
	GLuint		Width;									//Width ofImage
	GLuint		Bpp;									// Bits Per Pixel
} TGA;
#elif defined(PS4) || defined(XB1) || defined DREAMCAST
typedef struct
{
	unsigned char Header[12];									// TGA File Header
} TGAHeader;


typedef struct
{
	unsigned char		header[6];								// First 6 Useful Bytes From The Header
	unsigned int		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	unsigned int		imageSize;								// Used To Store The Image Size When Setting Aside Ram
	unsigned int		temp;									// Temporary Variable
	unsigned int		type;
	unsigned int		Height;									//Height of Image
	unsigned int		Width;									//Width ofImage
	unsigned int		Bpp;									// Bits Per Pixel
} TGA;
#endif


TGAHeader tgaheader;									// TGA header
TGA tga;												// TGA image data


#ifdef SWITCH
GLubyte uTGAcompare[12] = {0,0,2, 0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
GLubyte cTGAcompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};	// Compressed TGA Header
#elif defined(PS4) || defined(XB1) || defined DREAMCAST
unsigned char uTGAcompare[12] = { 0,0,2, 0,0,0,0,0,0,0,0,0 };	// Uncompressed TGA Header
unsigned char cTGAcompare[12] = { 0,0,10,0,0,0,0,0,0,0,0,0 };	// Compressed TGA Header
#endif


#endif






