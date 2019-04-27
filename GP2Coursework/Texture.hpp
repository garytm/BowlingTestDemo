#pragma once
#include <string>
#include <GL\glew.h>
using namespace std;
//Header file holding all information for textures used within the game
class Texture{
public:
	Texture();
	~Texture();
	//Allows multiple textures to be bound
	void BindTexture(unsigned int value);
	void initTexture(const string& nameOfFile);
	void ApplyTextures(int width, int height, unsigned char * imageParameters);

protected:
private:
	GLuint processTextures;
};

