#include "include/raylib.h"
#include <cstdio>

class Head
{
private:
    Vector2 posHead;
    Vector2 sizeHead;
    Vector2 direction;
    float velocity;
    float maxVelocity;
    Rectangle recHead;

public:
    Head(Vector2 startPos);
    Vector2 getPosHead();
    Vector2 getSizeHead();
    void setDirAndDist(Vector2 nDir, float nDist);

    void ActualizePosition();
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
}

Vector2 Head::getPosHead()
{
    return posHead;
}

Vector2 Head::getSizeHead()
{
    return sizeHead;
}

void Head::ActualizePosition()
{

    Vector2 newPos;

    newPos.x = posHead.x + direction.x * velocity;
    newPos.y = posHead.y + direction.y * velocity;
    recHead = {newPos.x, newPos.y, sizeHead.x, sizeHead.y};
    posHead = newPos;
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