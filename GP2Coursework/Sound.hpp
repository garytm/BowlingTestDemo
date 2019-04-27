#pragma once
#include <glm\glm.hpp>
#include <AL\al.h>
#include <AL\alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <SDL\SDL.h>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

class Sound
{
	struct data {
		int soundID, bufferID;
		char* soundBuffer;
		string name;
		data(unsigned int sI, unsigned int bI, char* b, const char* n)
		{
			this->soundID = sI;
			this->bufferID = bI;
			this->soundBuffer = b;
			this->name = n;
		}
	};

	struct Vector3
	{
		float x, y, z;
	};
	vector<data> datas;
	ALCcontext* soundContext;
	ALCdevice* device;
	bool isBigEndian();
	int convertToInt(char* buffer, int length);
	char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size);

public:
	Sound();
	~Sound();
	unsigned int loadSound(const char* filename);
	void removeSound(unsigned int id);
	void playSound(unsigned int id);
	void playSound(unsigned int id, vec3& position);
	void stopSound(unsigned int id);
	void createListener(vec3& pos, vec3& camLookAt);

private:

};

