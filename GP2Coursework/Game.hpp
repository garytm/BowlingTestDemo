#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Viewport.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Ball.hpp"
#include "Pin.hpp"
#include "Model.hpp"
#include "Sound.hpp"

enum class GameState { PLAY, EXIT };
class Game{
public:
	Game();
	~Game();

	void run();

private:
	void setupSystems();
	void handleInputs();
	void gameLoop();
	void gameDraw();
	void playAudio(unsigned int Source, vec3 position);
	bool CollisionCheck(vec3 ballPosition, float ballRadius, vec3 pinPosition, float pinRadius);
	Viewport _gameViewport;
	GameState _gameState;
	Input input;
	Ball Ball1;
	Pin Pin1;
	Pin Pin2;
	Pin Pin3;
	Pin Pin4;
	Pin Pin5;
	Pin Pin6;
	Pin Pin7;
	Pin Pin8;
	Pin Pin9;
	Pin Pin10;
	Model Lane;
	Model Test;

	Sound soundDevice;

	MoveableCamera newCamera;
	Texture newTexture;
	Texture laneTex;
	Texture ballTex;
	Texture pinTex;
	Texture pinTex2;
	Shader shader;

	unsigned int Whoosh;
	unsigned int backGroundMusic;
	float counter;
};
