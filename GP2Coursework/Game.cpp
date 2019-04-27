#include "Game.hpp"
#include "Camera.hpp"
#include <iostream>
#include <string>
using namespace glm;
Transform transform;

Vertex vertices[] =
{
	Vertex(vec3(-1, -1, -1), vec2(1, 0), vec3(0, 0, -1)),
	Vertex(vec3(-1, 1, -1), vec2(0, 0), vec3(0, 0, -1)),
	Vertex(vec3(1, 1, -1), vec2(0, 1), vec3(0, 0, -1)),
	Vertex(vec3(1, -1, -1), vec2(1, 1), vec3(0, 0, -1)),

	Vertex(vec3(-1, -1, 1), vec2(1, 0), vec3(0, 0, 1)),
	Vertex(vec3(-1, 1, 1), vec2(0, 0), vec3(0, 0, 1)),
	Vertex(vec3(1, 1, 1), vec2(0, 1), vec3(0, 0, 1)),
	Vertex(vec3(1, -1, 1), vec2(1, 1), vec3(0, 0, 1)),

	Vertex(vec3(-1, -1, -1), vec2(0, 1), vec3(0, -1, 0)),
	Vertex(vec3(-1, -1, 1), vec2(1, 1), vec3(0, -1, 0)),
	Vertex(vec3(1, -1, 1), vec2(1, 0), vec3(0, -1, 0)),
	Vertex(vec3(1, -1, -1), vec2(0, 0), vec3(0, -1, 0)),

	Vertex(vec3(-1, 1, -1), vec2(0, 1), vec3(0, 1, 0)),
	Vertex(vec3(-1, 1, 1), vec2(1, 1), vec3(0, 1, 0)),
	Vertex(vec3(1, 1, 1), vec2(1, 0), vec3(0, 1, 0)),
	Vertex(vec3(1, 1, -1), vec2(0, 0), vec3(0, 1, 0)),

	Vertex(vec3(-1, -1, -1), vec2(1, 1), vec3(-1, 0, 0)),
	Vertex(vec3(-1, -1, 1), vec2(1, 0), vec3(-1, 0, 0)),
	Vertex(vec3(-1, 1, 1), vec2(0, 0), vec3(-1, 0, 0)),
	Vertex(vec3(-1, 1, -1), vec2(0, 1), vec3(-1, 0, 0)),

	Vertex(vec3(1, -1, -1), vec2(1, 1), vec3(1, 0, 0)),
	Vertex(vec3(1, -1, 1), vec2(1, 0), vec3(1, 0, 0)),
	Vertex(vec3(1, 1, 1), vec2(0, 0), vec3(1, 0, 0)),
	Vertex(vec3(1, 1, -1), vec2(0, 1), vec3(1, 0, 0)),
};

unsigned int indices[] = { 0, 1, 2,
0, 2, 3,

6, 5, 4,
7, 6, 4,

10, 9, 8,
11, 10, 8,

12, 13, 14,
12, 14, 15,

16, 17, 18,
16, 18, 19,

22, 21, 20,
23, 22, 20
};

Game::Game() : Ball1(input){
	//Seting the default game state to PLAY when the game is running
	_gameState = GameState::PLAY;
	Sound* soundDevice();
}

Game::~Game(){
}

void Game::run(){
	setupSystems();
	gameLoop();
}

void Game::setupSystems(){
	_gameViewport.setupViewport();
	Lane.loadModel("..\\Content\\BowlingLane.obj");
	Ball1.loadModel("..\\Content\\Ball.obj");
	Pin1.loadModel("..\\Content\\Pin.obj");
	Pin2.loadModel("..\\Content\\Pin.obj");
	Pin3.loadModel("..\\Content\\Pin.obj");
	Pin4.loadModel("..\\Content\\Pin.obj");
	Pin5.loadModel("..\\Content\\Pin.obj");
	Pin6.loadModel("..\\Content\\Pin.obj");
	Pin7.loadModel("..\\Content\\Pin.obj");
	Pin8.loadModel("..\\Content\\Pin.obj");
	Pin9.loadModel("..\\Content\\Pin.obj");
	Pin10.loadModel("..\\Content\\Pin.obj");

	//Test.loadModel("..\\Content\\Pin.obj");
	laneTex.initTexture("..\\Content\\LaneTex.jpg");
	ballTex.initTexture("..\\Content\\BallTex.jpeg");
	pinTex.initTexture("..\\Content\\PinTex.jpg");
	pinTex2.initTexture("..\\Content\\PinTex2.jpg");
	shader.initShader("..\\Content\\shader");
	counter = 0.5f;

	//SOUND
	Whoosh = soundDevice.loadSound("..\\Content\\Whoosh.wav");
	backGroundMusic = soundDevice.loadSound("..\\Content\\BGMusic.wav");
}

void Game::gameLoop(){
	while (_gameState != GameState::EXIT){
		handleInputs();
		gameDraw();
		CollisionCheck(Ball1.getBallSpherePosition(), Ball1.getBallSphereRadius(), Pin1.getPinSpherePosition(), Pin1.getPinSphereRadius());
		CollisionCheck(Ball1.getBallSpherePosition(), Ball1.getBallSphereRadius(), Pin2.getPinSpherePosition(), Pin2.getPinSphereRadius());
		CollisionCheck(Ball1.getBallSpherePosition(), Ball1.getBallSphereRadius(), Pin3.getPinSpherePosition(), Pin3.getPinSphereRadius());
		CollisionCheck(Ball1.getBallSpherePosition(), Ball1.getBallSphereRadius(), Pin4.getPinSpherePosition(), Pin4.getPinSphereRadius());
		CollisionCheck(Ball1.getBallSpherePosition(), Ball1.getBallSphereRadius(), Pin5.getPinSpherePosition(), Pin5.getPinSphereRadius());
		CollisionCheck(Ball1.getBallSpherePosition(), Ball1.getBallSphereRadius(), Pin6.getPinSpherePosition(), Pin6.getPinSphereRadius());
		CollisionCheck(Ball1.getBallSpherePosition(), Ball1.getBallSphereRadius(), Pin7.getPinSpherePosition(), Pin7.getPinSphereRadius());
		CollisionCheck(Ball1.getBallSpherePosition(), Ball1.getBallSphereRadius(), Pin8.getPinSpherePosition(), Pin8.getPinSphereRadius());
		CollisionCheck(Ball1.getBallSpherePosition(), Ball1.getBallSphereRadius(), Pin9.getPinSpherePosition(), Pin9.getPinSphereRadius());
		CollisionCheck(Ball1.getBallSpherePosition(), Ball1.getBallSphereRadius(), Pin10.getPinSpherePosition(), Pin10.getPinSphereRadius());
		newCamera.setupCamera(vec3(Ball1.transform.GetPosition().x,Ball1.transform.GetPosition().y + 1.0f,Ball1.transform.GetPosition().z - 3), 70.f, (float)_gameViewport.getScreenWidth() / _gameViewport.getScreenHeight(), 0.01f, 1000.0f);
		
		if (input.isDown(SDLK_RETURN))
		{
			newCamera.setupCamera(vec3(Ball1.transform.GetPosition().x, Ball1.transform.GetPosition().y + 1.0f, Ball1.transform.GetPosition().z - 1), 70.f, (float)_gameViewport.getScreenWidth() / _gameViewport.getScreenHeight(), 0.01f, 1000.0f);
		}

		if (input.isDown(SDLK_UP))
		{
			playAudio(Whoosh, newCamera.getPosition());
			newCamera.setupCamera(vec3(0, 5, 30), 70.f, (float)_gameViewport.getScreenWidth() / _gameViewport.getScreenHeight(), 0.01f, 1000.0f);
			newCamera.CameraPitch(0.5);
		}
		
		if (input.isDown(SDLK_RIGHT))
		{
			playAudio(Whoosh, newCamera.getPosition());
			newCamera.setupCamera(vec3(10, 0, 10), 70.f, (float)_gameViewport.getScreenWidth() / _gameViewport.getScreenHeight(), 0.01f, 1000.0f);
			newCamera.CameraForward(45);
			newCamera.RotateY(4);
		}
		if (input.isDown(SDLK_LEFT))
		{
			playAudio(Whoosh, newCamera.getPosition());
			newCamera.setupCamera(vec3(-10, 0, 10), 70.f, (float)_gameViewport.getScreenWidth() / _gameViewport.getScreenHeight(), 0.01f, 1000.0f);
			newCamera.CameraForward(45);
			newCamera.RotateY(-4);
		}
		if (input.wasDown(SDLK_a)) {
			newCamera.CameraForward(2);
			newCamera.CameraPitch(0.5);
			newCamera.CameraRight(0.5);
		}
		if (input.wasDown(SDLK_d)) {
			newCamera.CameraForward(2);
			newCamera.CameraPitch(0.5);
			newCamera.CameraRight(-0.5);
		}
		playAudio(backGroundMusic, vec3(0.0f, 0.0f, 0.0f));
	}
}

void Game::handleInputs() {
	vector<SDL_Event> eventList;
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		eventList.push_back(evnt);
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		}
	}
	input.EventHandler(eventList);
}
//Checking all collisions between models
	bool Game::CollisionCheck(vec3 ballPosition, float ballRadius, vec3 pinPosition, float pinRadius)
{
	float distanceBetween = sqrt((pinPosition.x - ballPosition.x)*(pinPosition.x - ballPosition.x)
	+ (pinPosition.y - ballPosition.y)*(pinPosition.y - ballPosition.y)
	+ (pinPosition.z - ballPosition.z)*(pinPosition.z - ballPosition.z));
	if (distanceBetween < (ballRadius + pinRadius))
	{
		Pin1.transform.SetPosition(vec3(-0.9, -0.5, 0.0));
		Pin1.transform.SetRotation(vec3(0, 0, 0));
		Pin1.transform.SetScale(vec3(0.2, 0.2, 0.2));
		Pin1.shader = &shader;
		shader.Update(transform, newCamera);
		pinTex.BindTexture(0);
		Pin1.draw(newCamera);
		soundDevice.createListener(newCamera.getPosition(), ballPosition);
		playAudio(Whoosh, ballPosition);
		return true;
	}
	else
	{
		return false;
	}
}

void Game::playAudio(unsigned int Source, vec3 position)
{
	ALint state;
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state)
	{
		soundDevice.playSound(Source, position);
	}
}
void Game::gameDraw(){
	_gameViewport.clearViewport(0.0f, 0.0f, 0.0f, 1.0f);

	float sinCounter = sinf(counter);
	float absSinCounter = abs(sinCounter);

	Ball1.transform.SetPosition(vec3(sinf(counter), -0.1, -5.0));
	Ball1.transform.SetRotation(vec3(10, 2, 0));
	Ball1.transform.SetScale(vec3(0.2, 0.2, 0.2));
	Ball1.shader = &shader;
	shader.Update(Ball1.transform, newCamera);
	Ball1.update();
	ballTex.BindTexture(0);
	Ball1.draw(newCamera);
	Ball1.updateBallSphere(Ball1.transform.GetPosition(), 0.65f);

	Pin1.transform.SetPosition(vec3(-0.9, -0.5, 50.0));
	Pin1.transform.SetRotation(vec3(0, 0, 0));
	Pin1.transform.SetScale(vec3(0.2, 0.2, 0.2));
	Pin1.shader = &shader;
	shader.Update(transform, newCamera);
	pinTex.BindTexture(0);
	Pin1.draw(newCamera);
	Pin1.updatePinSphere(Pin1.transform.GetPosition(), 0.65f);
	//Pin2
	Pin2.transform.SetPosition(vec3(-0.3, -0.5, 50.0));
	Pin2.transform.SetRotation(vec3(0, 0, 0));
	Pin2.transform.SetScale(vec3(0.2, 0.2, 0.2));
	Pin2.shader = &shader;
	shader.Update(transform, newCamera);
	pinTex2.BindTexture(0);
	Pin2.draw(newCamera);
	Pin2.updatePinSphere(Pin2.transform.GetPosition(), 0.65f);
	//Pin3
	Pin3.transform.SetPosition(vec3(0.3, -0.5, 50.0));
	Pin3.transform.SetRotation(vec3(0, 0, 0));
	Pin3.transform.SetScale(vec3(0.2, 0.2, 0.2));
	Pin3.shader = &shader;
	shader.Update(transform, newCamera);
	pinTex.BindTexture(0);
	Pin3.draw(newCamera);
	Pin3.updatePinSphere(Pin3.transform.GetPosition(), 0.65f);
	//Pin4
	Pin4.transform.SetPosition(vec3(0.9, -0.5, 50.0));
	Pin4.transform.SetRotation(vec3(0, 0, 0));
	Pin4.transform.SetScale(vec3(0.2, 0.2, 0.2));
	Pin4.shader = &shader;
	shader.Update(transform, newCamera);
	pinTex2.BindTexture(0);
	Pin4.draw(newCamera);
	Pin4.updatePinSphere(Pin4.transform.GetPosition(), 0.65f);
	//Pin5
	Pin5.transform.SetPosition(vec3(-0.6, -0.5, 47.0));
	Pin5.transform.SetRotation(vec3(0, 0, 0));
	Pin5.transform.SetScale(vec3(0.2, 0.2, 0.2));
	Pin5.shader = &shader;
	shader.Update(transform, newCamera);
	pinTex.BindTexture(0);
	Pin5.draw(newCamera);
	Pin5.updatePinSphere(Pin5.transform.GetPosition(), 0.65f);
	//Pin6
	Pin6.transform.SetPosition(vec3(0.0, -0.5, 47.0));
	Pin6.transform.SetRotation(vec3(0, 0, 0));
	Pin6.transform.SetScale(vec3(0.2, 0.2, 0.2));
	Pin6.shader = &shader;
	shader.Update(transform, newCamera);
	pinTex2.BindTexture(0);
	Pin6.draw(newCamera);
	Pin6.updatePinSphere(Pin6.transform.GetPosition(), 0.65f);
	//Pin7
	Pin7.transform.SetPosition(vec3(0.6, -0.5, 47.0));
	Pin7.transform.SetRotation(vec3(0, 0, 0));
	Pin7.transform.SetScale(vec3(0.2, 0.2, 0.2));
	Pin7.shader = &shader;
	shader.Update(transform, newCamera);
	pinTex.BindTexture(0);
	Pin7.draw(newCamera);
	Pin7.updatePinSphere(Pin7.transform.GetPosition(), 0.65f);
	//Pin8
	Pin8.transform.SetPosition(vec3(-0.3, -0.5, 44.0));
	Pin8.transform.SetRotation(vec3(0, 0, 0));
	Pin8.transform.SetScale(vec3(0.2, 0.2, 0.2));
	Pin8.shader = &shader;
	shader.Update(transform, newCamera);
	pinTex2.BindTexture(0);
	Pin8.draw(newCamera);
	Pin8.updatePinSphere(Pin8.transform.GetPosition(), 0.65f);
	//Pin9
	Pin9.transform.SetPosition(vec3(0.3, -0.5, 44.0));
	Pin9.transform.SetRotation(vec3(0, 0, 0));
	Pin9.transform.SetScale(vec3(0.2, 0.2, 0.2));
	Pin9.shader = &shader;
	shader.Update(transform, newCamera);
	pinTex.BindTexture(0);
	Pin9.draw(newCamera);
	Pin9.updatePinSphere(Pin9.transform.GetPosition(), 0.65f);
	//Pin10
	Pin10.transform.SetPosition(vec3(0.0, -0.5, 41.0));
	Pin10.transform.SetRotation(vec3(0, 0, 0));
	Pin10.transform.SetScale(vec3(0.2, 0.2, 0.2));
	Pin10.shader = &shader;
	shader.Update(transform, newCamera);
	pinTex2.BindTexture(0);
	Pin10.draw(newCamera);
	Pin10.updatePinSphere(Pin10.transform.GetPosition(), 0.65f);

	
	Lane.transform.SetPosition(vec3(0, -3.0, 10.0));
	Lane.transform.SetRotation(vec3(0, 0 ,0));
	Lane.transform.SetScale(vec3(0.05, 0.21, 0.8));
	Lane.shader = &shader;
	shader.Update(transform, newCamera);
	laneTex.BindTexture(0);
	Lane.draw(newCamera);

	/*Test.transform.SetPosition(vec3(sinf(counter), 0.0, 0.0));
	Test.transform.SetRotation(vec3(counter * 2, 0.0, counter * 2));
	Test.transform.SetScale(vec3(sinf(counter), sinf(counter), sinf(counter)));
	Test.shader = &shader;
	shader.Update(transform, newCamera);
	pinTex.BindTexture(0);
	Test.draw(newCamera);*/

	counter = counter + 0.01f;

	glEnd();
	_gameViewport.switchBuffer();
}