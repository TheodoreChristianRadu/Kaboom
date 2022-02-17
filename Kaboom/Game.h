#pragma once
#include "Vector.h"
#include "Object.h"
#include <list>

using namespace std;

namespace Game
{
	inline Vector size;
	inline list<Object*> players, computers;
    inline Object * controlled;
    inline list<Object*> misses, enemyShots;
    inline bool set;

	void Initialize();
    void LoadBoat();
    void Validate(unsigned char key, int x, int y);
    void Move(int key, int x, int y);
    bool Over(bool player);
    void Reshape(int width, int height);
	void Render();
};
