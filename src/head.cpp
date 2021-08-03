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
    Rectangle recHead;

public:
    Head(Vector2 startPos);
    Vector2 getPosHead();
    Vector2 getSizeHead();
    Rectangle getRectangle();
    void setDirAndDist(Vector2 nDir, float nDist);
    void setVelocity(float t_velocity);
    float getVelocity(int i);
    void ActualizePosition(int screenWidth, int screenHeight);
};

Head::Head(Vector2 startPos)
{
    posHead = startPos;
    Vector2 size;
    size.x = 20;
    size.y = 20;
    sizeHead = size;
    velocity = 0;
    maxVelocity = 10;
    recHead = {posHead.x, posHead.y, sizeHead.x, sizeHead.y};
}

Vector2 Head::getPosHead()
{
    return posHead;
}

Vector2 Head::getSizeHead()
{
    return sizeHead;
}

Rectangle Head::getRectangle()
{
    return recHead;
}

void Head::setVelocity(float t_velocity)
{
    velocityNoSlow = velocity;
    velocity = t_velocity;
}

float Head::getVelocity(int i)
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

void Head::ActualizePosition(int screenWidth, int screenHeight)
{
    Vector2 newPos;
    //Casos on s'ha de canviar la direccio per el xoc amb algun objecte
    if (posHead.y < 0 || posHead.y > screenHeight)
    {
        direction.y = direction.y * -1;
        velocity = velocity * 0.75;
        if (posHead.y < 0)
        {
            posHead.y = 0;
        }
        else
        {
            posHead.y = screenHeight;
        }
        printf("Xocat contra amunt");
    }
    if (posHead.x < 0 || posHead.x > screenWidth)
    {
        direction.x = direction.x * -1;
        velocity = velocity * 0.75;
        printf("Xocat contra amunt");
        if (posHead.x < 0)
        {
            posHead.x = 0;
        }
        else
        {
            posHead.x = screenWidth;
        }
    }

    newPos.x = posHead.x + direction.x * velocity;
    newPos.y = posHead.y + direction.y * velocity;

    posHead = newPos;
    recHead = {posHead.x, posHead.y, 20, 20};
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
