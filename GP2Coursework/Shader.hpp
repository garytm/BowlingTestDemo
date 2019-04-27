#pragma once
#include <string>
#include <GL\glew.h>
#include "Transform.hpp"
#include "Camera.hpp"
using namespace std;
//Header file holding all information for shaders used within the game
class Shader
{
public:
	Shader();
	~Shader();
	//initShader is used in Shader.cpp to load the shaders from a file using the file path and name
	void initShader(const string& nameOfFile);
	//Ensuring the GPU is using the these shaders
	void ShaderBinding();
	void Update(const Transform& transform, const MoveableCamera& camera);
	GLuint Shader::ShaderCreation(const string& text, unsigned int type);
	string Shader::ShaderLoad(const string& nameOfFile);

	void Shader::ShaderErr(GLuint shader, GLuint flag, bool isnewProgram, const string& writeError);


protected:
private:
	static const unsigned int SHADERS_AMT = 2;

	enum{
		TRANSFORM_U,
		UNIFORMS_AMT
	};

	GLuint newProgram; 
	GLuint shaders[SHADERS_AMT];
	GLuint uniforms[UNIFORMS_AMT];
};
