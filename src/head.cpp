#include "include/raylib.h"
#include <cstdio>

class Head
{
private:
    Vector2 posHead;
    Vector2 sizeHead;
    Vector2 direction;
    float velocity;
    float velocityNoSlow;
    float maxVelocity;
    int bounces;
    Rectangle recHead;

public:
    Head(Vector2 startPos);
    Vector2 getPosHead() const;
    Vector2 getSizeHead() const;
    Rectangle getRectangle() const;
    void setDirAndDist(Vector2 nDir, float nDist);
    void resetBounces();
    int getBounces() const;
    void setVelocity(float t_velocity);
    float getVelocity(int i) const;
    void ActualizePosition(int screenWidth, int screenHeight);
};

Head::Head(Vector2 startPos)
{
    bounces = 0;
    posHead = startPos;
    Vector2 size;
    size.x = 20;
    size.y = 20;
    sizeHead = size;
    velocity = 0;
    maxVelocity = 10;
    recHead = {posHead.x, posHead.y, sizeHead.x, sizeHead.y};
}

Vector2 Head::getPosHead() const
{
    return posHead;
}

Vector2 Head::getSizeHead() const
{
    return sizeHead;
}

Rectangle Head::getRectangle() const
{
    return recHead;
}

void Head::setVelocity(float t_velocity)
{
    velocityNoSlow = velocity;
    velocity = t_velocity;
}

float Head::getVelocity(int i) const
{
    float velReturn;
    if (i == 0)
    {
        velReturn = velocity;
    }
    else
    {
        velReturn = velocityNoSlow;
    }
    return velReturn;
}

void reduceVelocity(int t_bounces, float &velocity)
{
    if (t_bounces == 0)
    {
        velocity = velocity * 0.6;
    }
    else
    {
        velocity = velocity * 0.2;
    }
}

void Head::ActualizePosition(int screenWidth, int screenHeight)
{
    Vector2 newPos;
    //Change direction of the head to bounce the walls
    if (posHead.y < 0 || posHead.y > screenHeight)
    {
        direction.y = direction.y * -1;
        reduceVelocity(bounces, velocity);
        if (posHead.y < 0)
        {
            posHead.y = 0;
        }
        else
        {
            posHead.y = screenHeight;
        }
        bounces++;
    }
    if (posHead.x < 0 || posHead.x > screenWidth)
    {
        direction.x = direction.x * -1;
        reduceVelocity(bounces, velocity);
        if (posHead.x < 0)
        {
            posHead.x = 0;
        }
        else
        {
            posHead.x = screenWidth;
        }
        bounces++;
    }

    newPos.x = posHead.x + direction.x * velocity;
    newPos.y = posHead.y + direction.y * velocity;

    posHead = newPos;
    recHead = {posHead.x, posHead.y, 20, 20};
}
void Head::resetBounces()
{
    bounces = 0;
}

int Head::getBounces() const
{
    return bounces;
}

void Head::setDirAndDist(Vector2 nDir, float nDist)
{

    direction = nDir;

    if (nDist < maxVelocity)
    {
        velocity = nDist;
    }
    else
    {
        velocity = maxVelocity;
    }
}
