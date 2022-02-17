#pragma once
#include "Vector.h"
#include "Texture.h"
#include <list>

using namespace std;

struct Object
{
    Vector position, size;
    list<Object*> damage;

	Object(int length, bool ignorePlayers = false);
    Object(Object*);
    
    bool Collide(Object & other);
    bool Collide(list<Object*> boats);
    bool OffLimits();
	void Move(Vector move);
	bool Damage(Object & boat);
    bool Damage(list<Object*> boat);
    bool Destroyed();

	void Render(Texture&);
    void RenderDamage(Texture&);
};
