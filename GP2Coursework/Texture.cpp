#include "Texture.hpp"
#include "stb_image.h"
#include <cassert>
#include <iostream>
using namespace std;
Texture::Texture()
{
}

Texture::~Texture(){
	glDeleteTextures(1, &processTextures);
}
//Setting the amount of textures which can be bound (32)
void Texture::BindTexture(unsigned int unit){
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit); 
	glBindTexture(GL_TEXTURE_2D, processTextures);
}
//Loading textures from file, throwing an error message if this is not possible
void Texture::initTexture(const string& nameOfFile) {
	int width, height, componentAmt;
	unsigned char* imageParameters = stbi_load((nameOfFile).c_str(), &width, &height, &componentAmt, 4);

	if (imageParameters == NULL)
	{
		cerr << "texture load failed" << nameOfFile << endl;
	}
	ApplyTextures(width, height, imageParameters);
}
//A method which hold all the information required to apply textures
//to models and allows for easy reuse
void Texture::ApplyTextures(int width, int height, unsigned char * imageParameters) {
	glGenTextures(1, &processTextures);
	glBindTexture(GL_TEXTURE_2D, processTextures);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageParameters);

	stbi_image_free(imageParameters);
}