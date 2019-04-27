#include "Sound.hpp"

Sound::Sound()
{
	device = alcOpenDevice(NULL); //open sound card
	if (device == NULL)
	{
		cout << "cannot open sound card" << endl;
	}

	soundContext = alcCreateContext(device, NULL);

	if (soundContext == NULL)
	{
		cout << "cannot open context" << endl;
	}

	alcMakeContextCurrent(soundContext);
}

Sound::~Sound()
{
	for (unsigned int i = 0; i < datas.size(); i++)
	{
		alDeleteSources(1, (unsigned int*)&datas[i].soundID);
		if (datas[i].bufferID != -1)
		{
			alDeleteBuffers(1, (unsigned int*)&datas[i].bufferID);
			delete[] datas[i].soundBuffer;
		}
	}
	alcDestroyContext(soundContext);
	alcCloseDevice(device);
}

bool Sound::isBigEndian()
{
	int a = 1;
	return !((char*)&a)[0];
}

int Sound::convertToInt(char* buffer, int length)
{
	int a = 0;
	if (!isBigEndian())
		for (int i = 0; i < length; i++)
			((char*)&a)[i] = buffer[i];
	else
		for (int i = 0; i < length; i++)
			((char*)&a)[3 - i] = buffer[i];
	return a;
}

char* Sound::loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size)
{
	char buffer[4];
	ifstream in(fn, ios::binary);
	in.read(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 4); //WAV
	in.read(buffer, 4);	//fmt
	in.read(buffer, 4); //16 bit
	in.read(buffer, 2); //1
	in.read(buffer, 2);
	chan = convertToInt(buffer, 2);
	in.read(buffer, 4);
	samplerate = convertToInt(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	bps = convertToInt(buffer, 2);
	in.read(buffer, 4);
	in.read(buffer, 4);
	size = convertToInt(buffer, 4);

	char* soundData = new char[size];
	in.read(soundData, size);
	return soundData;
}

unsigned int Sound::loadSound(const char* filename)
{
	bool found = false;
	unsigned int sourceID, bufferID;
	char* soundData = NULL;
	for (unsigned int i = 0; i < datas.size(); i++)
	{
		if (datas[i].name == filename && datas[i].bufferID != -1)
		{
			bufferID = datas[i].bufferID;
			found = true;
			break;
		}
	}
	if (!found)
	{
		int channel, sampleRate, bps, size;
		soundData = loadWAV(filename, channel, sampleRate, bps, size);
		unsigned int format;
		alGenBuffers(1, &bufferID);

		if (channel == 1)
		{
			if (bps == 8)
			{
				format = AL_FORMAT_MONO8;
			}
			else
			{
				format = AL_FORMAT_MONO16;
			}
		}
		else
		{
			if (bps == 8)
			{
				format = AL_FORMAT_STEREO8;
			}
			else
			{
				format = AL_FORMAT_STEREO16;
			}

		}

		alBufferData(bufferID, format, soundData, size, sampleRate);
	}
	alGenSources(1, &sourceID);
	alSourcei(sourceID, AL_BUFFER, bufferID);
	alSourcef(sourceID, AL_REFERENCE_DISTANCE, 1.0f);
	datas.push_back(data(sourceID, (!found ? bufferID : -1), soundData, filename));
	return sourceID;
}

void Sound::removeSound(unsigned int id)
{
}

void Sound::playSound(unsigned int id)
{
	alSourcePlay(id);
}
void Sound::playSound(unsigned int id, vec3& position)
{
	alSource3f(id, AL_POSITION, position.x, position.y, position.z);
	alSourcePlay(id);
}
void Sound::stopSound(unsigned int id)
{
	alSourceStop(id);
}
void Sound::createListener(glm::vec3& pos, glm::vec3& camLookAt)
{
	alListener3f(AL_POSITION, pos.x, pos.y, -pos.z);
	float orinet[6] = { camLookAt.x,camLookAt.y,camLookAt.z,0,1,0 };
	alListenerfv(AL_ORIENTATION, orinet);
}