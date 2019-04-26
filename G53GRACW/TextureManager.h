#ifndef ___TextureManager__
#define ___TextureManager__

#ifdef __APPLE__
#include <GLUT/glut.h>
#pragma pack(1)
#define WORD unsigned short
#define DWORD unsigned int
#define LONG int
typedef struct tagBITMAPFILEHEADER {
	WORD  bfType;
	DWORD bfSize;
	WORD  bfReserved1;
	WORD  bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;
typedef struct tagBITMAPINFOHEADER {
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} BITMAPINFOHEADER;
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

class TextureManager
{
public:
	TextureManager() {};
	~TextureManager();

	GLuint loadImage(const char* filename);

private:
	vector<GLuint> textures;
};

#endif
