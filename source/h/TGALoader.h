/********************************************************************************
/Name:		TGA.cpp																*
/Header:	tga.h																*
/Purpose:	Load Compressed and Uncompressed TGA files							*
/Functions:	LoadTGA(Texture * texture, char * filename)							*
/			LoadCompressedTGA(Texture * texture, char * filename, FILE * fTGA)	*
/			LoadUncompressedTGA(Texture * texture, char * filename, FILE * fTGA)*	
/*******************************************************************************/
#include "tga.h"
#include <stdlib.h>  
#include <math.h> 

FILE* fpm; 

/********************************************************************************
/name :		LoadTGA(Texture * texture, char * filename)							*
/function:  Open and test the file to make sure it is a valid TGA file			*	
/parems:	texture, pointer to a Texture structure								*
/			filename, string pointing to file to open							*
/********************************************************************************/


#ifndef DREAMCAST

#if defined(SWITCH)
bool LoadCompressedTGA(Texture *, char *, FILE *, bool is_map);		// Load a Compressed file
bool sLoadCompressedTGA(Texture * texture, char * filename, FILE * fTGA);		// Load COMPRESSED TGAs
#endif
bool sLoadCompressedTGADX(Texture * texture, char * filename);		// Load COMPRESSED TGAs

#if defined(SWITCH)
bool LoadTGA(Texture * texture, char * filename)				// Load a TGA file
{
	FILE * fTGA;												// File pointer to texture file
    errno_t err;

#ifdef SWITCH
	if (strstr(filename, "rom:") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "rom:/%s", filename);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fTGA = fopen(tempfilename, "rb");
		//printf("TGALOADER NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#endif
		for (int i = 0; filename[i]; i++) {
			filename[i] = tolower(filename[i]);
		}
		fTGA = fopen(filename, "rb");
		//printf("TGALOADER NO CONVERSION : %s\n", filename);
#ifdef SWITCH
	}
#endif

	
	  
	if(err != NULL)											// If it didn't open....
	{
		//MessageBox(NULL, "Could not open texture file", "ERROR", MB_OK);	// Display an error message
		return false;														// Exit function
	}

	if(fread(&tgaheader, sizeof(TGAHeader), 1, fTGA) == 0)					// Attempt to read 12 byte header from file
	{
		//MessageBox(NULL, "Could not read file header", "ERROR", MB_OK);		// If it fails, display an error message 
		if(fTGA != NULL)													// Check to seeiffile is still open
		{
			fclose(fTGA);													// If it is, close it
		}
		return false;														// Exit function
	}

	if(memcmp(uTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)				// See if header matches the predefined header of 
	{																		// an Uncompressed TGA image
	//	LoadUncompressedTGA(texture, filename, fTGA);						// If so, jump to Uncompressed TGA loading code
	}
	else if(memcmp(cTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)		// See if header matches the predefined header of
	{																		// an RLE compressed TGA image
		LoadCompressedTGA(texture, filename, fTGA, false);							// If so, jump to Compressed TGA loading code
	}
	else																	// If header matches neither type
	{
		//MessageBox(NULL, "TGA file be type 2 or type 10 ", "Invalid Image", MB_OK);	// Display an error
		fclose(fTGA);
		return false;																// Exit function
	}
	return true;															// All went well, continue on
}

bool LoadCompressedTGA(Texture * texture, char * filename, FILE * fTGA, bool is_map)		// Load COMPRESSED TGAs
{ 
	int colour = 0;
	int current_rowX=0;
	int current_rowY=0;

	if(fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)					// Attempt to read header
	{
		//MessageBox(NULL, "Could not read info header", "ERROR", MB_OK);		// Display Error
		if(fTGA != NULL)													// If file is open
		{
			fclose(fTGA);													// Close it
		}
		return false;														// Return failed
	}

	texture->width  = tga.header[1] * 256 + tga.header[0];					// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = tga.header[3] * 256 + tga.header[2];					// Determine The TGA Height	(highbyte*256+lowbyte)
	texture->bpp	= tga.header[4];										// Determine Bits Per Pixel
	tga.Width		= texture->width;										// Copy width to local structure
	tga.Height		= texture->height;										// Copy width to local structure
	tga.Bpp			= texture->bpp;											// Copy width to local structure
	 
	if((texture->width <= 0) || (texture->height <= 0) || ((texture->bpp != 24) && (texture->bpp !=32)))	//Make sure all texture info is ok
	{
		//MessageBox(NULL, "Invalid texture information", "ERROR", MB_OK);	// If it isnt...Display error
		if(fTGA != NULL)													// Check if file is open
		{
			fclose(fTGA);													// Ifit is, close it
		}
		return false; 														// Return failed
	}  

	tga.bytesPerPixel	= (tga.Bpp / 8);									// Compute BYTES per pixel
	tga.imageSize		= (tga.bytesPerPixel * tga.Width * tga.Height);		// Compute amout of memory needed to store image
	texture->imageSize  = tga.imageSize;
	texture->imageData	= (GLubyte *)malloc(tga.imageSize);					// Allocate that much memory

	if(texture->imageData == NULL)											// If it wasnt allocated correctly..
	{
		//MessageBox(NULL, "Could not allocate memory for image", "ERROR", MB_OK);	// Display Error
		fclose(fTGA);														// Close file
		return false;														// Return failed
	}

	GLuint pixelcount	= tga.Height * tga.Width;							// Nuber of pixels in the image
	GLuint currentpixel	= 0;												// Current pixel being read
	GLuint currentbyte	= 0;												// Current byte 
	GLubyte * colorbuffer = (GLubyte *)malloc(tga.bytesPerPixel);			// Storage for 1 pixel

	do
	{
		GLubyte chunkheader = 0;											// Storage for "chunk" header

		if(fread(&chunkheader, sizeof(GLubyte), 1, fTGA) == 0)				// Read in the 1 byte header
		{
			//MessageBox(NULL, "Could not read RLE header", "ERROR", MB_OK);	// Display Error
			if(fTGA != NULL)												// If file is open
			{
				fclose(fTGA);												// Close file
			}
			if(texture->imageData != NULL)									// If there is stored image data
			{
				free(texture->imageData);									// Delete image data
			}
			return false;													// Return failed
		}

		if(chunkheader < 128)												// If the ehader is < 128, it means the that is the number of RAW color packets minus 1
		{																	// that follow the header
			chunkheader++;													// add 1 to get number of following color values
			for(short counter = 0; counter < chunkheader; counter++)		// Read RAW color values
			{
				if(fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel) // Try to read 1 pixel
				{
					//MessageBox(NULL, "Could not read image data", "ERROR", MB_OK);		// IF we cant, display an error

					if(fTGA != NULL)													// See if file is open
					{
						fclose(fTGA);													// If so, close file
					}

					if(colorbuffer != NULL)												// See if colorbuffer has data in it
					{
						free(colorbuffer);												// If so, delete it
					}

					if(texture->imageData != NULL)										// See if there is stored Image data
					{
						free(texture->imageData);										// If so, delete it too
					}

					return false;														// Return failed
				}
				
				if(	currentbyte >= 0)																	// write to memory
				texture->imageData[currentbyte		] = colorbuffer[2];				    // Flip R and B vcolor values around in the process 
				if(	currentbyte + 1 >= 0)																	// write to memory
				texture->imageData[currentbyte + 1	] = colorbuffer[1];
				if(	currentbyte + 2 >= 0)																	// write to memory
				texture->imageData[currentbyte + 2	] = colorbuffer[0];
                 
                if ( colorbuffer[0] == 255 && colorbuffer[1] == 0 && colorbuffer[2] == 255 )
                    texture->imageData[currentbyte		] = 15;  
                
				if(tga.bytesPerPixel == 8)												// if its a 32 bpp image
				{
					texture->imageData[currentbyte + 3] = colorbuffer[3];				// copy the 4th byte
				}

				currentbyte += tga.bytesPerPixel;										// Increase thecurrent byte by the number of bytes per pixel
				currentpixel++;															// Increase current pixel by 1

				current_rowX++;  

				if(	current_rowX >= 512) 
				{
					current_rowX=0;
					current_rowY++; 
				}

				if(currentpixel > pixelcount)											// Make sure we havent read too many pixels
				{
					//MessageBox(NULL, "Too many pixels read", "ERROR", MB_OK|MB_ICONEXCLAMATION);			// if there is too many... Display an error!

					if(fTGA != NULL)													// If there is a file open
					{
						fclose(fTGA);													// Close file
					}	

					if(colorbuffer != NULL)												// If there is data in colorbuffer
					{
						free(colorbuffer);												// Delete it
					}

					if(texture->imageData != NULL)										// If there is Image data
					{
						free(texture->imageData);										// delete it
					}

					return false;														// Return failed
				}
			}
		}
		else																			// chunkheader > 128 RLE data, next color reapeated chunkheader - 127 times
		{
			chunkheader -= 127;															// Subteact 127 to get rid of the ID bit
			if(fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel)		// Attempt to read following color values
			{	
				//MessageBox(NULL, "Could not read from file", "ERROR", MB_OK);			// If attempt fails.. Display error (again)

				if(fTGA != NULL)														// If thereis a file open
				{
					fclose(fTGA);														// Close it
				}

				if(colorbuffer != NULL)													// If there is data in the colorbuffer
				{
					free(colorbuffer);													// delete it
				}

				if(texture->imageData != NULL)											// If thereis image data
				{
					free(texture->imageData);											// delete it
				}

				return false;															// return failed
			}

			for(short counter = 0; counter < chunkheader; counter++)					// copy the color into the image data as many times as dictated 
			{		
				if(	currentbyte >= 0) 													// by the header
				texture->imageData[currentbyte		] = colorbuffer[2];					// switch R and B bytes areound while copying

				if(	currentbyte + 1 >= 0)													// by the header
				texture->imageData[currentbyte + 1	] = colorbuffer[1];

				if(	currentbyte + 2 >= 0)													// by the header
				texture->imageData[currentbyte + 2	] = colorbuffer[0];

				if(tga.bytesPerPixel == 4)
				if(	currentbyte + 3 >= 0)												// If TGA images is 32 bpp
				{
					texture->imageData[currentbyte + 3] = colorbuffer[3];				// Copy 4th byte
				}  

				currentbyte += tga.bytesPerPixel;										// Increase current byte by the number of bytes per pixel
				currentpixel++;															// Increase pixel count by 1

				current_rowX++;  

				if(	current_rowX >= 512) 
				{
					current_rowX=0;
					current_rowY++; 
				}

				if(currentpixel > pixelcount)											// Make sure we havent written too many pixels
				{
					//MessageBox(NULL, "Too many pixels read", "ERROR", MB_OK|MB_ICONEXCLAMATION);			// if there is too many... Display an error!

					if(fTGA != NULL)													// If there is a file open
					{
						fclose(fTGA);													// Close file
					}	

					if(colorbuffer != NULL)												// If there is data in colorbuffer
					{
						free(colorbuffer);												// Delete it
					}

					if(texture->imageData != NULL)										// If there is Image data
					{
						free(texture->imageData);										// delete it
					}

					return false;														// Return failed
				}
			}
		}
	}

	while(currentpixel < pixelcount);													// Loop while there are still pixels left
	fclose(fTGA);
    free(colorbuffer);																		// Close the file
	return true;																		// return success
}


bool sLoadTGA(Texture * texture, char * filename)				// Load a TGA file
{

	FILE * fTGA;												// File pointer to texture file
    errno_t err;

#ifdef SWITCH
	if (strstr(filename, "rom:") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "rom:/%s", filename);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fTGA = fopen(tempfilename, "rb");
		//printf("STGALOADER NO CONVERSION : %s\n", tempfilename);
	}
	else
	{
#endif
		for (int i = 0; filename[i]; i++) {
			filename[i] = tolower(filename[i]);
		}
		fTGA = fopen(filename, "rb");
		//printf("STGALOADER NO CONVERSION : %s\n", filename);
#ifdef SWITCH
	}
#endif

	if(fTGA == NULL)											// If it didn't open....
	{
		//MessageBox(NULL, "Could not open texture file", "ERROR", MB_OK);	// Display an error message
		return false;														// Exit function
	}

	if(fread(&tgaheader, sizeof(TGAHeader), 1, fTGA) == 0)					// Attempt to read 12 byte header from file
	{
		//MessageBox(NULL,"Could not read file header", "ERROR", MB_OK);		// If it fails, display an error message 
		if(fTGA != NULL)													// Check to seeiffile is still open
		{
			fclose(fTGA);													// If it is, close it
		}
		return false;														// Exit function
	}

	if(memcmp(uTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)				// See if header matches the predefined header of 
	{																		// an Uncompressed TGA image
	//	LoadUncompressedTGA(texture, filename, fTGA);						// If so, jump to Uncompressed TGA loading code
	}
	else if(memcmp(cTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)		// See if header matches the predefined header of
	{		
			sLoadCompressedTGA(texture, filename, fTGA);							// If so, jump to Compressed TGA loading code
	}
	else																	// If header matches neither type
	{
		//MessageBox(NULL, "TGA file be type 2 or type 10 ", "Invalid Image", MB_OK);	// Display an error
		fclose(fTGA);
		return false;																// Exit function
	}
	return true;															// All went well, continue on
}

bool sLoadCompressedTGA(Texture * texture, char * filename, FILE * fTGA)		// Load COMPRESSED TGAs
{ 
    
	if(fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)					// Attempt to read header
	{
		//MessageBox(NULL, "Could not read info header", "ERROR", MB_OK);		// Display Error
		if(fTGA != NULL)													// If file is open
		{
			fclose(fTGA);													// Close it
		}
		return false;														// Return failed
	}

	texture->width  = tga.header[1] * 256 + tga.header[0];					// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = tga.header[3] * 256 + tga.header[2];					// Determine The TGA Height	(highbyte*256+lowbyte)
	texture->bpp	= tga.header[4];										// Determine Bits Per Pixel
   
	tga.Width		= texture->width;										// Copy width to local structure
	tga.Height		= texture->height;										// Copy width to local structure
	tga.Bpp			= texture->bpp;											// Copy width to local structure

    
	tga.bytesPerPixel	= (tga.Bpp / 8);									// Compute BYTES per pixel
	tga.imageSize		= (4 * tga.Width * tga.Height);		// Compute amout of memory needed to store image
	texture->imageSize  = tga.imageSize;
	texture->imageData	= (GLubyte *)malloc(tga.imageSize);					// Allocate that much memory
      
    texture->bpp = 32; // Hack

	if(texture->imageData == NULL)											// If it wasnt allocated correctly..
	{
		//MessageBox(NULL, "Could not allocate memory for image", "ERROR", MB_OK);	// Display Error
		fclose(fTGA);														// Close file
		return false;														// Return failed
	}

	GLuint pixelcount	= tga.Height * tga.Width;							// Nuber of pixels in the image
	GLuint currentpixel	= 0;												// Current pixel being read
	GLuint currentbyte	= 0;												// Current byte 
	GLubyte * colorbuffer = (GLubyte *)malloc(4);			// Storage for 1 pixel

	do
	{
		GLubyte chunkheader = 0;											// Storage for "chunk" header

		if(fread(&chunkheader, sizeof(GLubyte), 1, fTGA) == 0)				// Read in the 1 byte header
		{
			//MessageBox(NULL, "Could not read RLE header", "ERROR", MB_OK);	// Display Error
			if(fTGA != NULL)												// If file is open
			{
				fclose(fTGA);												// Close file
			}
			if(texture->imageData != NULL)									// If there is stored image data
			{
				free(texture->imageData);									// Delete image data
			}
			return false;													// Return failed
		}

		if(chunkheader < 128)												// If the ehader is < 128, it means the that is the number of RAW color packets minus 1
		{																	// that follow the header
			chunkheader++;													// add 1 to get number of following color values
			for(short counter = 0; counter < chunkheader; counter++)		// Read RAW color values
			{
				if(fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel) // Try to read 1 pixel
				{
					//MessageBox(NULL, "Could not read image data", "ERROR", MB_OK);		// IF we cant, display an error

					if(fTGA != NULL)													// See if file is open
					{
						fclose(fTGA);													// If so, close file
					}

					if(colorbuffer != NULL)												// See if colorbuffer has data in it
					{
						free(colorbuffer);												// If so, delete it
					}

					if(texture->imageData != NULL)										// See if there is stored Image data
					{
						free(texture->imageData);										// If so, delete it too
					}

					return false;														// Return failed
				}
				if(	currentbyte >= 0)																		// write to memory
				texture->imageData[currentbyte		] = colorbuffer[2];				    // Flip R and B vcolor values around in the process 
				if(	currentbyte + 1 >= 0)																		// write to memory
				texture->imageData[currentbyte + 1	] = colorbuffer[1];
				if(	currentbyte + 2 >= 0)																		// write to memory
				texture->imageData[currentbyte + 2	] = colorbuffer[0];
                                                    
                if ( colorbuffer[0] == 255 && colorbuffer[1] == 0 && colorbuffer[2] == 255 )
                {
					if(	currentbyte >= 0)
                    	texture->imageData[currentbyte		] = 0;				    // Flip R and B vcolor values around in the process 
					if(	currentbyte+1 >= 0)
				    	texture->imageData[currentbyte + 1	] = 0;
					if(	currentbyte+2 >= 0)
				    	texture->imageData[currentbyte + 2	] = 0;     

                    texture->imageData[currentbyte + 3 ] = 0;  
                }   
                else
				{
					if(	currentbyte+3 >= 0)
                    	texture->imageData[currentbyte + 3  ] = 255; 
				}
                                         
                if ( colorbuffer[0] == 255 && colorbuffer[1] == 255 && colorbuffer[2] == 0 )
                {
				    if(	currentbyte >= 0)
                    texture->imageData[currentbyte		] = 0;				    // Flip R and B vcolor values around in the process 
				    if(	currentbyte+ 1 >= 0)
				    texture->imageData[currentbyte + 1	] = 0;
				    if(	currentbyte+ 2 >= 0)
				    texture->imageData[currentbyte + 2	] = 0;     
				    if(	currentbyte+ 3 >= 0)
                    texture->imageData[currentbyte + 3 ] = 80; 
                }
                                          
                if ( colorbuffer[0] == 0 && colorbuffer[1] == 255 && colorbuffer[2] == 255 )
                {
				    if(	currentbyte >= 0)
                    texture->imageData[currentbyte		] = 0;				    // Flip R and B vcolor values around in the process 
				    if(	currentbyte+ 1 >= 0)
				    texture->imageData[currentbyte + 1	] = 0;
				    if(	currentbyte+ 2 >= 0)
				    texture->imageData[currentbyte + 2	] = 0;     
				    if(	currentbyte+ 3 >= 0)
                    texture->imageData[currentbyte + 3 ] = 140; 
                } 
                                            
			    currentbyte += 4;
				currentpixel++;															// Increase current pixel by 1

				if(currentpixel > pixelcount)											// Make sure we havent read too many pixels
				{
					//MessageBox(NULL, "Too many pixels read", "ERROR", MB_OK|MB_ICONEXCLAMATION);			// if there is too many... Display an error!

					if(fTGA != NULL)													// If there is a file open
					{
						fclose(fTGA);													// Close file
					}	

					if(colorbuffer != NULL)												// If there is data in colorbuffer
					{
						free(colorbuffer);												// Delete it
					}

					if(texture->imageData != NULL)										// If there is Image data
					{
						free(texture->imageData);										// delete it
					}

					return false;														// Return failed
				}
			}
		}
		else																			// chunkheader > 128 RLE data, next color reapeated chunkheader - 127 times
		{
			chunkheader -= 127;															// Subteact 127 to get rid of the ID bit
			if(fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel)		// Attempt to read following color values
			{	
				//MessageBox(NULL, "Could not read from file", "ERROR", MB_OK);			// If attempt fails.. Display error (again)

				if(fTGA != NULL)														// If thereis a file open
				{
					fclose(fTGA);														// Close it
				}

				if(colorbuffer != NULL)													// If there is data in the colorbuffer
				{
					free(colorbuffer);													// delete it
				}

				if(texture->imageData != NULL)											// If thereis image data
				{
					free(texture->imageData);											// delete it
				}

				return false;															// return failed
			}

			for(short counter = 0; counter < chunkheader; counter++)					// copy the color into the image data as many times as dictated 
			{	
  																		// by the header
			    if(	currentbyte >= 0)
				texture->imageData[currentbyte		] = colorbuffer[2];	// b			// switch R and B bytes areound while copying
			    if(	currentbyte+ 1 >= 0)
				texture->imageData[currentbyte + 1	] = colorbuffer[1]; // g
			    if(	currentbyte+ 2 >= 0)
				texture->imageData[currentbyte + 2	] = colorbuffer[0]; // r
               
                if ( colorbuffer[0] == 255 && colorbuffer[1] == 0 && colorbuffer[2] == 255 )
                { 
				    if(	currentbyte >= 0)
                    texture->imageData[currentbyte		] = 0;				    // Flip R and B vcolor values around in the process 
				    if(	currentbyte+ 1 >= 0)
				    texture->imageData[currentbyte + 1	] = 0;
				    if(	currentbyte+ 2 >= 0)
				    texture->imageData[currentbyte + 2	] = 0;     

				    if(	currentbyte+ 3 >= 0)
                    texture->imageData[currentbyte + 3 ] = 0;  
                }    
                else
				{
				    if(	currentbyte+ 3 >= 0)
                    texture->imageData[currentbyte + 3 ] = 255; 
				}

                if ( colorbuffer[0] == 255 && colorbuffer[1] == 255 && colorbuffer[2] == 0 )
                {
				    if(	currentbyte >= 0)
                    texture->imageData[currentbyte		] = 0;				    // Flip R and B vcolor values around in the process 
				    if(	currentbyte+ 1 >= 0)
				    texture->imageData[currentbyte + 1	] = 0;
				    if(	currentbyte+ 2 >= 0)
				    texture->imageData[currentbyte + 2	] = 0;     
				    if(	currentbyte+ 3 >= 0)
                    texture->imageData[currentbyte + 3 ] = 80; 
                } 

                if ( colorbuffer[0] == 0 && colorbuffer[1] == 255 && colorbuffer[2] == 255 )
                {
				    if(	currentbyte >= 0)
                    texture->imageData[currentbyte		] = 0;				    // Flip R and B vcolor values around in the process 
				    if(	currentbyte+ 1 >= 0)
				    texture->imageData[currentbyte + 1	] = 0;
				    if(	currentbyte+ 2 >= 0)
				    texture->imageData[currentbyte + 2	] = 0;     
				    if(	currentbyte+ 3 >= 0)
                    texture->imageData[currentbyte + 3 ] = 140; 
                }
                                
			    currentbyte += 4;
				currentpixel++;															// Increase pixel count by 1

				if(currentpixel > pixelcount)											// Make sure we havent written too many pixels
				{
					//MessageBox(NULL, "Too many pixels read", "ERROR", MB_OK|MB_ICONEXCLAMATION);			// if there is too many... Display an error!

					if(fTGA != NULL)													// If there is a file open
					{
						fclose(fTGA);													// Close file
					}	

					if(colorbuffer != NULL)												// If there is data in colorbuffer
					{
						free(colorbuffer);												// Delete it
					}

					if(texture->imageData != NULL)										// If there is Image data
					{
						free(texture->imageData);										// delete it
					}

					return false;														// Return failed
				}
			}
		}
	}

	while(currentpixel < pixelcount);													// Loop while there are still pixels left
	
	free(colorbuffer);
	
	fclose(fTGA);																		// Close the file

	return true;																		// return success
}
#endif

bool sLoadTGADX(Texture * texture, char * filename)				// Load a TGA file
{

	FILE * fTGA;												// File pointer to texture file
    errno_t err;

	fTGA = fopen(filename, "rb");

	if(err != NULL)											// If it didn't open....
	{
		//MessageBox(NULL, "Could not open texture file", "ERROR", MB_OK);	// Display an error message
		return false;														// Exit function
	}

	if(fread(&tgaheader, sizeof(TGAHeader), 1, fTGA) == 0)					// Attempt to read 12 byte header from file
	{
		//MessageBox(NULL,"Could not read file header", "ERROR", MB_OK);		// If it fails, display an error message 
		if(fTGA != NULL)													// Check to seeiffile is still open
		{
			fclose(fTGA);													// If it is, close it
		}
		return false;														// Exit function
	}

	if(memcmp(uTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)				// See if header matches the predefined header of 
	{																		// an Uncompressed TGA image
	//	LoadUncompressedTGA(texture, filename, fTGA);						// If so, jump to Uncompressed TGA loading code
	}
	else if(memcmp(cTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)		// See if header matches the predefined header of
	{		
			sLoadCompressedTGADX(texture, filename);							// If so, jump to Compressed TGA loading code
	}
	else			 														// If header matches neither type
	{ 
		//MessageBox(NULL, "TGA file be type 2 or type 10 ", "Invalid Image", MB_OK);	// Display an error
		fclose(fTGA);
		return false;																// Exit function
	}
	return true;															// All went well, continue on
}

bool sLoadCompressedTGADX(Texture * texture, char * filename)		// Load COMPRESSED TGAs
{ 
	FILE * fTGA;
	errno_t err;
	
#ifdef SWITCH
	GLuint currentpixel	= 0;												// Current pixel being read
	GLuint currentbyte	= 0;
#elif PS4// Current byte
	texture->imageData = NULL;
	unsigned int currentpixel = 0;												// Current pixel being read
	unsigned int currentbyte = 0;
#elif XB1// Current byte
	texture->imageData = NULL;
	unsigned int currentpixel = 0;												// Current pixel being read
	unsigned int currentbyte = 0;
#endif

	int bit_size = 4;
#ifdef PS4
	if (strstr(filename, "/app0/") == NULL)
	{
		char tempfilename[200];
		sprintf(tempfilename, "/app0/%s", filename);
		for (int i = 0; tempfilename[i]; i++) {
			tempfilename[i] = tolower(tempfilename[i]);
		}
		fTGA = fopen(tempfilename, "rb");
		printf("TGALOADER NO CONVERSION : %s\n", tempfilename);
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
			fTGA = fopen(tempfilename, "rb");
			printf("TGALOADER NO CONVERSION : %s\n", tempfilename);
		}
		else
		{
#endif
		for (int i = 0; filename[i]; i++) {
			filename[i] = tolower(filename[i]);
		}
		fTGA = fopen(filename, "rb");
		printf("TGALOADER NO CONVERSION : %s\n", filename);
#if defined (PS4) || defined (XB1)
	}
#endif
	//fTGA  = fopen( filename, "rb");

	if(err != NULL)											// If it didn't open....
	{
		//MessageBox(NULL, "Could not open texture file", "ERROR", MB_OK);	// Display an error message
		return false;														// Exit function
	} 

	if(fread(&tgaheader, sizeof(TGAHeader), 1, fTGA) == 0)					// Attempt to read 12 byte header from file
	{
		//MessageBox(NULL,"Could not read file header", "ERROR", MB_OK);		// If it fails, display an error message 
		if(fTGA != NULL)													// Check to seeiffile is still open
		{
			fclose(fTGA);													// If it is, close it
		}
		return false;														// Exit function
	}

	if(fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)					// Attempt to read header
	{
		//MessageBox(NULL, "Could not read info header", "ERROR", MB_OK);		// Display Error
		if(fTGA != NULL)													// If file is open
		{
			fclose(fTGA);													// Close it
		}
		return false;														// Return failed
	}  
	 
	tga.Width		= tga.header[1] * 256 + tga.header[0];						 // Copy width to local structure
	tga.Height		= tga.header[3] * 256 + tga.header[2];						 // Copy width to local structure
	tga.Bpp			= tga.header[4];											 // Copy width to local structure
     
	tga.bytesPerPixel	= (tga.Bpp / 8); 									// Compute BYTES per pixel
	tga.imageSize		= (4 * tga.Width * tga.Height);					// Compute amout of memory needed to store image

	texture->imageSize  = tga.imageSize; 
#ifdef SWITCH
	texture->imageData	= (GLubyte *)malloc(tga.imageSize);					// Allocate that much memory
#elif PS4
	texture->imageData = (unsigned char *)malloc(tga.imageSize);
#elif XB1
	texture->imageData = (unsigned char *)malloc(tga.imageSize);
#endif
	texture->width  = tga.header[1] * 256 + tga.header[0];					// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = tga.header[3] * 256 + tga.header[2];					// Determine The TGA Height	(highbyte*256+lowbyte)
	texture->bpp	= tga.header[4];										// Determine Bits Per Pixel
      
    texture->bpp = 32; // Hack 

	if(texture->imageData == NULL)											// If it wasnt allocated correctly..
	{
		//MessageBox(NULL, "Could not allocate memory for image", "ERROR", MB_OK);	// Display Error
		fclose(fTGA);														// Close file
		return false;														// Return failed
	}
#ifdef SWITCH
	GLuint pixelcount	= tga.Height * tga.Width;							// Nuber of pixels in the image
	GLubyte * colorbuffer = (GLubyte *)malloc(4);			// Storage for 1 pixel
#elif PS4
	unsigned int pixelcount = tga.Height * tga.Width;							// Nuber of pixels in the image
	unsigned char * colorbuffer = (unsigned char *)malloc(4);			// Storage for 1 pixel
#elif XB1
	unsigned int pixelcount = tga.Height * tga.Width;							// Nuber of pixels in the image
	unsigned char * colorbuffer = (unsigned char *)malloc(4);			// Storage for 1 pixel
#endif

	do
	{
#ifdef SWITCH
		GLubyte chunkheader = 0;											// Storage for "chunk" header

		if(fread(&chunkheader, sizeof(GLubyte), 1, fTGA) == 0)				// Read in the 1 byte header
#elif PS4
		unsigned char chunkheader = 0;											// Storage for "chunk" header

		if (fread(&chunkheader, sizeof(unsigned char), 1, fTGA) == 0)				// Read in the 1 byte header
#elif XB1
		unsigned char chunkheader = 0;											// Storage for "chunk" header

		if (fread(&chunkheader, sizeof(unsigned char), 1, fTGA) == 0)				// Read in the 1 byte header
#endif
		{
			//MessageBox(NULL, "Could not read RLE header", "ERROR", MB_OK);	// Display Error
			if(fTGA != NULL)												// If file is open
			{
				fclose(fTGA);												// Close file
			}
			if(texture->imageData != NULL)									// If there is stored image data
			{
				free(texture->imageData);									// Delete image data
			}
			return false;													// Return failed
		}

		if(chunkheader < 128)												// If the ehader is < 128, it means the that is the number of RAW color packets minus 1
		{																	// that follow the header
			chunkheader++;													// add 1 to get number of following color values
			for(short counter = 0; counter < chunkheader; counter++)		// Read RAW color values
			{
				if(fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel) // Try to read 1 pixel
				{
					//MessageBox(NULL, "Could not read image data", "ERROR", MB_OK);		// IF we cant, display an error

					if(fTGA != NULL)													// See if file is open
					{
						fclose(fTGA);													// If so, close file
					}

					if(colorbuffer != NULL)												// See if colorbuffer has data in it
					{
						free(colorbuffer);												// If so, delete it
					}

					if(texture->imageData != NULL)										// See if there is stored Image data
					{
						free(texture->imageData);										// If so, delete it too
					}

					return false;														// Return failed
				} 

				      
				texture->imageData[currentbyte + 0	] = colorbuffer[0]; 	  
				texture->imageData[currentbyte + 1	] = colorbuffer[1];
				texture->imageData[currentbyte + 2	] = colorbuffer[2];
				texture->imageData[currentbyte + 3	] = 255;

                if ( colorbuffer[0] == 255 && colorbuffer[1] == 0 && colorbuffer[2] == 255 )
                {
					if(	currentbyte >= 0)
                    	texture->imageData[currentbyte		] = 0;				    // Flip R and B vcolor values around in the process 
					if(	currentbyte+1 >= 0)
				    	texture->imageData[currentbyte + 1	] = 0;
					if(	currentbyte+2 >= 0)
				    	texture->imageData[currentbyte + 2	] = 0;     

                    texture->imageData[currentbyte + 3 ] = 0;  
                }   
                else
				{
					if(	currentbyte+3 >= 0)
                    	texture->imageData[currentbyte + 3  ] = 255; 
				}
                                         
                if ( colorbuffer[0] == 255 && colorbuffer[1] == 255 && colorbuffer[2] == 0 )
                {
				    if(	currentbyte >= 0)
                    texture->imageData[currentbyte		] = 0;				    // Flip R and B vcolor values around in the process 
				    if(	currentbyte+ 1 >= 0)
				    texture->imageData[currentbyte + 1	] = 0;
				    if(	currentbyte+ 2 >= 0)
				    texture->imageData[currentbyte + 2	] = 0;     
				    if(	currentbyte+ 3 >= 0)
                    texture->imageData[currentbyte + 3 ] = 80; 
                }
                                          
                if ( colorbuffer[0] == 0 && colorbuffer[1] == 255 && colorbuffer[2] == 255 )
                {
				    if(	currentbyte >= 0)
                    texture->imageData[currentbyte		] = 0;				    // Flip R and B vcolor values around in the process 
				    if(	currentbyte+ 1 >= 0)
				    texture->imageData[currentbyte + 1	] = 0;
				    if(	currentbyte+ 2 >= 0)
				    texture->imageData[currentbyte + 2	] = 0;     
				    if(	currentbyte+ 3 >= 0)
                    texture->imageData[currentbyte + 3 ] = 140; 
                }    

                                            
			    currentbyte += 4;
				currentpixel++;															// Increase current pixel by 1

				if(currentpixel > pixelcount)											// Make sure we havent read too many pixels
				{
					//MessageBox(NULL, "Too many pixels read", "ERROR", MB_OK|MB_ICONEXCLAMATION);			// if there is too many... Display an error!

					if(fTGA != NULL)													// If there is a file open
					{
						fclose(fTGA);													// Close file
					}	

					if(colorbuffer != NULL)												// If there is data in colorbuffer
					{
						free(colorbuffer);												// Delete it
					}

					if(texture->imageData != NULL)										// If there is Image data
					{
						free(texture->imageData);										// delete it
					}

					return false;														// Return failed
				}
			}
		}
		else																			// chunkheader > 128 RLE data, next color reapeated chunkheader - 127 times
		{
			chunkheader -= 127;															// Subteact 127 to get rid of the ID bit
			if(fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel)		// Attempt to read following color values
			{	
				//MessageBox(NULL, "Could not read from file", "ERROR", MB_OK);			// If attempt fails.. Display error (again)

				if(fTGA != NULL)														// If thereis a file open
				{
					fclose(fTGA);														// Close it
				}

				if(colorbuffer != NULL)													// If there is data in the colorbuffer
				{
					free(colorbuffer);													// delete it
				}

				if(texture->imageData != NULL)											// If thereis image data
				{
					free(texture->imageData);											// delete it
				}

				return false;															// return failed
			} 

			for(short counter = 0; counter < chunkheader; counter++)					// copy the color into the image data as many times as dictated 
			{	

				texture->imageData[currentbyte		] = colorbuffer[0];	  
				texture->imageData[currentbyte + 1	] = colorbuffer[1]; 
				texture->imageData[currentbyte + 2	] = colorbuffer[2];
				texture->imageData[currentbyte + 3	] = 255;

                if ( colorbuffer[0] == 255 && colorbuffer[1] == 0 && colorbuffer[2] == 255 )
                { 
				    if(	currentbyte >= 0)
                    texture->imageData[currentbyte		] = 0;				    // Flip R and B vcolor values around in the process 
				    if(	currentbyte+ 1 >= 0)
				    texture->imageData[currentbyte + 1	] = 0;
				    if(	currentbyte+ 2 >= 0)
				    texture->imageData[currentbyte + 2	] = 0;     

				    if(	currentbyte+ 3 >= 0)
                    texture->imageData[currentbyte + 3 ] = 0;  
                }    
                else
				{
				    if(	currentbyte+ 3 >= 0)
                    texture->imageData[currentbyte + 3 ] = 255; 
				}

                if ( colorbuffer[0] == 255 && colorbuffer[1] == 255 && colorbuffer[2] == 0 )
                {
				    if(	currentbyte >= 0)
                    texture->imageData[currentbyte		] = 0;				    // Flip R and B vcolor values around in the process 
				    if(	currentbyte+ 1 >= 0)
				    texture->imageData[currentbyte + 1	] = 0;
				    if(	currentbyte+ 2 >= 0)
				    texture->imageData[currentbyte + 2	] = 0;     
				    if(	currentbyte+ 3 >= 0)
                    texture->imageData[currentbyte + 3 ] = 80; 
                } 

                if ( colorbuffer[0] == 0 && colorbuffer[1] == 255 && colorbuffer[2] == 255 )
                {
				    if(	currentbyte >= 0)
                    texture->imageData[currentbyte		] = 0;				    // Flip R and B vcolor values around in the process 
				    if(	currentbyte+ 1 >= 0)
				    texture->imageData[currentbyte + 1	] = 0;
				    if(	currentbyte+ 2 >= 0)
				    texture->imageData[currentbyte + 2	] = 0;     
				    if(	currentbyte+ 3 >= 0)
                    texture->imageData[currentbyte + 3 ] = 140;   
                }

			    currentbyte += 4; 
				currentpixel++;															// Increase pixel count by 1

				if(currentpixel > pixelcount)											// Make sure we havent written too many pixels
				{
					//MessageBox(NULL, "Too many pixels read", "ERROR", MB_OK|MB_ICONEXCLAMATION);			// if there is too many... Display an error!

					if(fTGA != NULL)													// If there is a file open
					{
						fclose(fTGA);													// Close file
					}	

					if(colorbuffer != NULL)												// If there is data in colorbuffer
					{
						free(colorbuffer);												// Delete it
					}

					if(texture->imageData != NULL)										// If there is Image data
					{
						free(texture->imageData);										// delete it
					}

					return false;														// Return failed
				}
			}
		}
	}

	while(currentpixel < pixelcount);													// Loop while there are still pixels left
	
	free(colorbuffer);
	
	fclose(fTGA);																		// Close the file

	return true;																		// return success
}

#endif
