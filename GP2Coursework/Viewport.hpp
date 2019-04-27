#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;
//Header file for everything related to displaying the program to the monitor(s)
class Viewport
{
public:
	Viewport();
	~Viewport();
	void setupViewport();
	void CreateWindow();
	void CheckForErrors();
	void switchBuffer();
	void clearViewport(float r, float g, float b, float a);
	float getScreenWidth();
	float getScreenHeight();

private:
	//An error should be thrown if there is a problem with drawing to the screen
	void throwError(string writeError);
	//Creating the context that will be associated with the window
	SDL_GLContext glContext;
	SDL_Window* newWindow;
	float screenWidth;
	float screenHeight;
};