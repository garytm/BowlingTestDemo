#include "Viewport.hpp"
using namespace std;
//Setting the window width and height within the constructor
Viewport::Viewport(){
	screenWidth = 600.0f;
	screenHeight = 900.0f;
}
//Removing the glContext, closing the window and exiting the aplication is handled in the destructor
Viewport::~Viewport(){
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(newWindow);
	SDL_Quit();
}
//Setting up the game window is handled here,
//creating the window, checking for errors, ensuring backface culling is enabled
void Viewport::setupViewport() {
	CreateWindow();
	CheckForErrors();
	//Enabling depth comparisons and updating the depth buffer.
	glEnable(GL_DEPTH_TEST);
	//Enables the culling of polygons dependent on their windings in the window
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
//Getters for the window width and height
float Viewport::getScreenWidth() { return screenWidth; }
float Viewport::getScreenHeight() { return screenHeight; }
//Throws an error to the console and quits the application
void Viewport::throwError(string errorString){
	cout << errorString << endl;
	cout << "Press any  key to quit.";
	int in;
	cin >> in;
	SDL_Quit();
}
//A method to switch buffers, allows double-buffering. Speeding up processing
void Viewport::switchBuffer(){
	SDL_GL_SwapWindow(newWindow);
}
//Clears the window. Also clears the color and depth buffers
void Viewport::clearViewport(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//Creates the window by inistialising everything in SDL, applying colours
//and giving the window a name
void Viewport::CreateWindow()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	newWindow = SDL_CreateWindow("Gary Mulhall GP2 Coursework", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenWidth, (int)screenHeight, SDL_WINDOW_OPENGL);
}
//Checking for errors when loading the window
void Viewport::CheckForErrors()
{
	if (newWindow == nullptr) {
		throwError("Window creation failed!");
	}
	glContext = SDL_GL_CreateContext(newWindow);
	if (glContext == nullptr) {
		throwError("SDL_GL context failed to create");
	}
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		throwError("GLEW failed to initialise");
	}
}
