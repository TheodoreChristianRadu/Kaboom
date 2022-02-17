#include "Texture.h"
#include "stb_image.h"
#include <glut.h>

Texture::Texture(string path)
{
	this->path = path;
	all.push_back(this);
}

void Texture::Load()
{
	int width, height, channels;
	unsigned char * data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	transparent = channels == 4;
	int mode = transparent ? GL_RGBA : GL_RGB;
    
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(data);
}

void Texture::Setup()
{
	for (Texture * texture : all)
		texture->Load();
}

void Texture::Apply()
{
	glColor3f(1,1,1);
	if (transparent)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id);
}
