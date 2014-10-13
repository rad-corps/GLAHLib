#pragma once

#include <map>
#include <string>
#include <Windows.h>


class GLAHSound
{
public:	
	~GLAHSound(void);
	static GLAHSound* Instance();

	
	DWORD CreateSound(std::string path_, 
						bool loop_ = false, //true to loop
						bool play_ = false, //true to start playing immediately
						float vol_ = 0.2f, //0 to 1
						float pan = 0.0f //-1 (full left) to +1 (full right)
						);

	void Play(DWORD sound_);
	void Stop(DWORD sound_);
	void Pause(DWORD sound_);

	//set frequency sample rate in HZ
	void SetPitch(DWORD sound_, float freq_ = 44100.f);

	//vol_ 0 min, 1 max
	void SetVolume(DWORD sound_, float vol_ = 0.2f);
	
	//pan -1 LEFT, +1 RIGHT
	void SetPan(DWORD sound_, float pan_ = 0.0f);

private:
	GLAHSound(void);
	static GLAHSound* instance;

	//std::map<unsigned int, GLAHSoundInfo>
};

