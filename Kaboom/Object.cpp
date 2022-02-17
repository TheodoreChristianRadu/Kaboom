#include "Object.h"
#include "Game.h"
#include <cstdlib>
#include <glut.h>

Object::Object(int length, bool ignorePlayers)
{
    do
    {
        bool flipped = rand() % 2;
        size = Vector(flipped ? 0 : (length - 1), flipped ? (length - 1) : 0);
        Vector max = Game::size - size;
        position = Vector(rand() % max.x, rand() % max.y);
    }
    while (!ignorePlayers * Collide(Game::players) || Collide(Game::computers) || Collide(Game::enemyShots));
}

Object::Object(Object * other)
{
    int length = !other->size + 1;
    *this = Object(length);
}

bool Object::Collide(Object & other)
{
    Vector gap = other.position - position;
    if (size % other.size == 0)
        return (!gap <= !size && !-gap <= !other.size && size % gap == 0 && other.size % gap == 0);
    else
        return (!gap <= !size && !-gap <= !other.size && size * gap >= 0 && other.size * gap <= 0);
}

bool Object::Collide(list<Object*> boats)
{
    for (Object * boat : boats)
        if (Collide(*boat))
            return true;
    return false;
}

bool Object::OffLimits()
{
    Vector end = position + size;
    return position.x < 0 || position.y < 0 || end.x >= Game::size.x || end.y >= Game::size.y;
}

void Object::Move(Vector move)
{
	position += move;
    if (OffLimits())
        Move(-move);
    else if (Collide(Game::players))
        Move(move);
}

bool Object::Damage(Object & boat)
{
    bool hit = Collide(boat);
    if (hit && !Collide(boat.damage))
        boat.damage.push_back(new Object(*this));
    return hit;
}

bool Object::Damage(list<Object*> boats)
{
    for (Object * boat : boats)
        if (Damage(*boat))
            return true;
    return false;
}

bool Object::Destroyed()
{
    return (damage.size() == !size + 1);
}

void Object::Render(Texture & texture)
{
    Vector end = position + size;
    bool flipped = size.y;
    texture.Apply();
    glBegin(GL_QUADS);
        glTexCoord2f(0,1); glVertex2f(position.x, position.y);
        glTexCoord2f(!flipped, !flipped); glVertex2f(end.x + 1, position.y);
        glTexCoord2f(1,0); glVertex2f(end.x + 1, end.y + 1);
        glTexCoord2f(flipped, flipped); glVertex2f(position.x, end.y + 1);
    glEnd();
}

void Object::RenderDamage(Texture & texture)
{
    for (Object * piece : damage)
        piece->Render(texture);
}
