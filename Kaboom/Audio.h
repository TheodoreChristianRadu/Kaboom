#pragma once
#include "miniaudio.h"
#include <string>
#include <list>

using namespace std;

struct Audio
{
	string path;
	bool loop;
	ma_sound sound;
	inline static ma_engine engine;
	inline static list<Audio*> all;

	Audio(string path, bool loop = false);

	static void Setup();
	void Play();
};