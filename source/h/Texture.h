#ifndef __TEXTURE_H__
#define __TEXTURE_H__

//#include <windows.h>									// Standard windows header
#include <stdio.h>										// Standard I/O header
#ifdef SWITCH
//#include <egl/egl.h>
#include "glad/glad.h"										// Header for OpenGL32 library


typedef	struct									
{
	GLubyte	* imageData;									// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel
	GLuint	imageSize;								// Used To Store The Image Size When Setting Aside Ram
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	GLuint	type;											// Image Type (GL_RGB, GL_RGBA)
} Texture;	
#elif PS4

typedef	struct
{
	unsigned char	* imageData;									// Image Data (Up To 32 Bits)
	unsigned int	bpp;											// Image Color Depth In Bits Per Pixel
	unsigned int	imageSize;								// Used To Store The Image Size When Setting Aside Ram
	unsigned int	width;											// Image Width
	unsigned int	height;											// Image Height
	sce::SampleUtil::Graphics::Texture*	texID;											// Texture ID Used To Select A Texture
	unsigned int	type;											// Image Type (GL_RGB, GL_RGBA)
} Texture;
#elif XB1
#include "SDL.h"
typedef	struct
{
	unsigned char	* imageData;									// Image Data (Up To 32 Bits)
	unsigned int	bpp;											// Image Color Depth In Bits Per Pixel
	unsigned int	imageSize;								// Used To Store The Image Size When Setting Aside Ram
	unsigned int	width;											// Image Width
	unsigned int	height;											// Image Height
	SDL_Texture* texID;											// Texture ID Used To Select A Texture
	unsigned int	type;											// Image Type (GL_RGB, GL_RGBA)
} Texture;

#elif DREAMCAST
typedef	struct
{
	unsigned char	* imageData;									// Image Data (Up To 32 Bits)
	unsigned int	bpp;											// Image Color Depth In Bits Per Pixel
	unsigned int	imageSize;								// Used To Store The Image Size When Setting Aside Ram
	unsigned int	width;											// Image Width
	unsigned int	height;											// Image Height
	int	texID;											// Texture ID Used To Select A Texture
	unsigned int	type;											// Image Type (GL_RGB, GL_RGBA)
} Texture;
#endif

#endif

