#include "Shader.hpp"
#include <iostream>
#include <fstream>
using namespace std;
Shader::Shader()
{

}

Shader::~Shader()
{
	for (unsigned int i = 0; i < SHADERS_AMT; i++)
	{
		glDetachShader(newProgram, shaders[i]);
		glDeleteShader(shaders[i]);
	}
	glDeleteProgram(newProgram);
}
//Creating a program and loading shaders from file
void Shader::initShader(const string& nameOfFile)
{
	newProgram = glCreateProgram();
	shaders[0] = ShaderCreation(ShaderLoad("..\\Content\\shader.vert"), GL_VERTEX_SHADER);
	shaders[1] = ShaderCreation(ShaderLoad("..\\Content\\shader.frag"), GL_FRAGMENT_SHADER);
	//Attaching shaders to programs based on how many shaders are available
	for (unsigned int i = 0; i < SHADERS_AMT; i++)
	{
		glAttachShader(newProgram, shaders[i]);
	}
	glBindAttribLocation(newProgram, 0, "position");
	glBindAttribLocation(newProgram, 1, "texCoord");
	//Linking the program to the created newProgram from the shaders list
	glLinkProgram(newProgram);
	ShaderErr(newProgram, GL_LINK_STATUS, true, "Error: Shader newProgram linking failed");
	//Checking the validity of the newProgram
	glValidateProgram(newProgram); 
	ShaderErr(newProgram, GL_VALIDATE_STATUS, true, "Error: Shader newProgram not valid");

	uniforms[TRANSFORM_U] = glGetUniformLocation(newProgram, "transform");
}

void Shader::ShaderBinding()
{
	glUseProgram(newProgram);
}

void Shader::Update(const Transform& transform, const MoveableCamera& camera)
{
	mat4 mvp = camera.getVP() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}

GLuint Shader::ShaderCreation(const string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type);
	//Throws an error as no shader is available
	if (shader == 0) 
		cerr << "Error type creation failed " << type << endl;

	const GLchar* startString[1]; 
	startString[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, startString, lengths); 
	glCompileShader(shader); 

	ShaderErr(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); 

	return shader;
}

string Shader::ShaderLoad(const string& nameOfFile)
{
	ifstream exisitingFile;
	exisitingFile.open((nameOfFile).c_str());

	string output;
	string line;

	if (exisitingFile.is_open())
	{
		while (exisitingFile.good())
		{
			getline(exisitingFile, line);
			output.append(line + "\n");
		}
	}
	else
	{
		cerr << "Shader could not be laoded: " << nameOfFile << endl;
	}

	return output;
}

void Shader::ShaderErr(GLuint shader, GLuint flag, bool isnewProgram, const string& writeError)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isnewProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isnewProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		cerr << writeError << ": '" << error << "'" << endl;
	}
}

