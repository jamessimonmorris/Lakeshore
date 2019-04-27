#include "TextureManager.h"

TextureManager::~TextureManager() {
	int n = textures.size();
	if (n > 0)
		glDeleteTextures(n, &textures[0]);
}

GLuint TextureManager::loadImage(const char* filename) {
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	GLuint texObject;
	unsigned char *pixelBuffer;

	FILE *bitmapFile;

#ifdef _MSC_VER
	errno_t err = fopen_s(&bitmapFile, filename, "rb");
	if (err != 0) return NULL;
#else
	bitmapFile = fopen(filename, "rb");
#endif

	if (bitmapFile == NULL) return NULL;

	fread(&fileHeader, 14, 1, bitmapFile);

	if (fileHeader.bfType != 0x4D42) return NULL;

	fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, bitmapFile);

	if (infoHeader.biBitCount < 24)	return NULL;

	fseek(bitmapFile, fileHeader.bfOffBits, SEEK_SET);

	pixelBuffer = new unsigned char[infoHeader.biWidth * infoHeader.biHeight * (infoHeader.biBitCount / 8)];
	fread(pixelBuffer, sizeof(unsigned char), infoHeader.biWidth * infoHeader.biHeight * (infoHeader.biBitCount / 8), bitmapFile);

	fclose(bitmapFile);

	if (infoHeader.biBitCount == 32)
	{
		unsigned char c;
		for (int i = 0; i < infoHeader.biWidth * infoHeader.biHeight; i++)
		{
			c = pixelBuffer[i * 4];
			pixelBuffer[i * 4] = pixelBuffer[i * 4 + 3];
			pixelBuffer[i * 4 + 3] = c;
			c = pixelBuffer[i * 4 + 1];
			pixelBuffer[i * 4 + 1] = pixelBuffer[i * 4 + 2];
			pixelBuffer[i * 4 + 2] = c;
		}
	}

	// Enable texturing
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	// Generate a texture buffer
	glGenTextures(1, &texObject);

	// Bin to buffer
	glBindTexture(GL_TEXTURE_2D, texObject);

	// Set texture parameters with mipmapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// Upload texture data - disable mipmapping for specific textures
	string fileNameStr = filename;
	string subStr = "Textures/skybox";
	if (fileNameStr == "Textures/bark.bmp" || fileNameStr == "Textures/rotorfabric.bmp" || !strncmp(fileNameStr.c_str(), subStr.c_str(), subStr.size()))
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, infoHeader.biBitCount == 32 ? GL_RGBA : GL_RGB, infoHeader.biWidth, infoHeader.biHeight, 0, infoHeader.biBitCount == 32 ? GL_RGBA : GL_BGR_EXT, GL_UNSIGNED_BYTE, pixelBuffer);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, infoHeader.biWidth, infoHeader.biHeight, infoHeader.biBitCount == 32 ? GL_RGBA : GL_BGR_EXT, GL_UNSIGNED_BYTE, pixelBuffer);
	}

	// insert texture into texture list
	textures.push_back(texObject);

	// Delete old copy of pixel data
	delete[] pixelBuffer;

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	return texObject;
}
