#ifndef TEXTURE_H
#define TEXTURE_H

#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <gl/GL.h>

struct TGA_Header
{
	GLubyte ID_Lenght;
	GLubyte ColorMapType;
	GLubyte ImageType;
	GLubyte ColorMapSpecification[5];

	GLshort xOrigin;
	GLshort yOrigin;
	GLshort ImageWidth;
	GLshort ImageHeight;

	GLshort PixelDepth;

};

class Texture
{
	// Functions
public:
	Texture(std::string filename, std::string name);
	~Texture();

	// Variables
public:
	unsigned char* imageData;
	unsigned int bpp;
	unsigned int width;
	unsigned int height;
	unsigned int texID;

	std::string name;

	static std::vector<Texture*> textures;


private:
	bool loadTGA(std::string filename);
	bool createTexture(
		unsigned char* imageData,
		unsigned int width,
		unsigned int height,
		unsigned int type);
};


#endif // !TEXTURE_H
