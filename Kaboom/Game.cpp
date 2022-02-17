#include "Game.h"
#include "Texture.h"
#include "Audio.h"
#include <fstream>
#include <glut.h>

using namespace Game;

Texture ocean("Textures/Ocean.png");
Texture boat("Textures/Boat.png");
Texture shadow("Textures/Shadow.png");
Texture target("Textures/Target.png");
Texture cross("Textures/Cross.png");
Texture damage("Textures/Damage.png");
Texture won("Textures/Kaboom.png");
Texture lost("Textures/Sploosh.png");

Audio music("Sounds/Sea.wav", true);
Audio sploosh("Sounds/Sploosh.wav");
Audio kaboom("Sounds/Kaboom.wav");
Audio boom("Sounds/Boom.wav");

ifstream rules("Rules.cfg");

void Game::Initialize()
{
    Audio::Setup();
    Texture::Setup();

	rules >> size.x;
	rules >> size.y;
    set = false;

    music.Play();
	LoadBoat();
}

void Game::LoadBoat()
{
    int length;
    if (rules >> length)
        controlled = new Object(length);
    else
        controlled = nullptr;
}

void Game::Validate(unsigned char key, int x, int y)
{
    if (key == ' ' && !Over(true) && !Over(false))
    {
        if (!set)
        {
            players.push_back(controlled);
            LoadBoat();
            if (controlled == nullptr)
            {
                controlled = new Object(1);
                for (Object* player : players)
                    computers.push_back(new Object(player));
                set = true;
            }
        }
        else
        {
            if (controlled->Damage(computers))
                kaboom.Play();
            else
            {
                if (!controlled->Collide(misses))
                    misses.push_back(new Object(*controlled));
                sploosh.Play();
            }

            Object* shot = new Object(1, true);
            enemyShots.push_back(shot);
            if (shot->Damage(players))
                boom.Play();
        }
        glutPostRedisplay();
    }
}

void Game::Move(int key, int x, int y)
{
    if (!Over(true) && !Over(false))
    {
        switch (key)
        {
        case GLUT_KEY_UP:
            controlled->Move(Vector(0, 1)); glutPostRedisplay(); break;
        case GLUT_KEY_DOWN:
            controlled->Move(Vector(0, -1)); glutPostRedisplay(); break;
        case GLUT_KEY_LEFT:
            controlled->Move(Vector(-1, 0)); glutPostRedisplay(); break;
        case GLUT_KEY_RIGHT:
            controlled->Move(Vector(1, 0)); glutPostRedisplay(); break;
        }
    }
}

bool Game::Over(bool player)
{
    for (Object * boat : (player ? players : computers))
        if (!boat->Destroyed())
            return false;
    return set;
}

void Game::Reshape(int width, int height)
{
    glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0, size.x, 0, size.y);
}

void Game::Render()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

    ocean.Apply();
    glBegin(GL_QUADS);
        glTexCoord2f(0,1); glVertex2f(0,0);
        glTexCoord2f(1,1); glVertex2f(size.x,0);
        glTexCoord2f(1,0); glVertex2f(size.x,size.y);
        glTexCoord2f(0,0); glVertex2f(0,size.y);
    glEnd();
    
    glColor3f(0,0,0);
    glLineWidth(0.1);
    glBegin(GL_LINES);
    for (int x = 1; x < size.x; x++)
    {
        glVertex2f(x, 0);
        glVertex2f(x, size.x);
    }
    for (int y = 1; y < size.y; y++)
    {
        glVertex2f(0, y);
        glVertex2f(size.y, y);
    }
    glEnd();
    
    for (Object * player : players)
    {
        player->Render(shadow);
        player->RenderDamage(damage);
    }
    for (Object * computer : computers)
    {
        if (computer->Destroyed())
            computer->Render(boat);
        computer->RenderDamage(damage);
    }
    for (Object* miss : misses)
        miss->Render(cross);
    controlled->Render(set ? target : boat);


    if (Over(true))
    {
        sploosh.Play();
        lost.Apply();
        glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex2f(0, 0);
            glTexCoord2f(1, 1); glVertex2f(size.x, 0);
            glTexCoord2f(1, 0); glVertex2f(size.x, size.y);
            glTexCoord2f(0, 0); glVertex2f(0, size.y);
        glEnd();
    }
    if (Over(false))
    {
        won.Apply();
        glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex2f(0, 0);
            glTexCoord2f(1, 1); glVertex2f(size.x, 0);
            glTexCoord2f(1, 0); glVertex2f(size.x, size.y);
            glTexCoord2f(0, 0); glVertex2f(0, size.y);
        glEnd();
    }
    
    glFlush();
}
