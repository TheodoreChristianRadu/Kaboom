#pragma once
#include <string>
#include <list>

using namespace std;

struct Texture
{
    unsigned int id;
    string path;
    bool transparent;
    inline static list<Texture*> all;
    
	Texture(string path);

    void Load();
    static void Setup();

    void Apply();
};
