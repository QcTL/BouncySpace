#include "include/raylib.h"
#include "head.cpp"
#include <cstdio>
#include <cmath>
const int screenWidth = 640;
const int screenHeight = 640;

Vector2 startPointLine;
Vector2 endPointLine;

void DisplayLinePointing(Head &h)
{
    if (IsMouseButtonPressed(0))
    {
        startPointLine = GetMousePosition();
    }
    else if (IsMouseButtonDown(0))
    {
        endPointLine = GetMousePosition();
        DrawLineEx(startPointLine, endPointLine, 10, {212, 12, 45, 255});
    }

    //Quan deixem anar el boto enviara el VectorUnitari del angle:
    if (IsMouseButtonReleased(0))
    {
        Vector2 vecUnitari;
        float distancia;

        float dirX = startPointLine.x - endPointLine.x;
        float dirY = startPointLine.y - endPointLine.y;
        distancia = abs(sqrt(dirX * dirX + dirY * dirY));
        vecUnitari.x = dirX / distancia;
        vecUnitari.y = dirY / distancia;
        h.setDirAndDist(vecUnitari, distancia / 100);
        //printf("ENVIADOOO %f", distancia);
    }
}

int main(void)
{

    InitWindow(screenWidth, screenHeight, "Bouncy Space");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    Vector2 startPos;
    startPos.x = screenWidth / 2;
    startPos.y = screenHeight / 2;
    Head h = Head(startPos);
    // Main game loop
    while (!WindowShouldClose())
    {

        //Calculs
        h.ActualizePosition();

        // Update
        DisplayLinePointing(h);
        DrawRectangleV(h.getPosHead(), h.getSizeHead(), GREEN);
        BeginDrawing();
        ClearBackground({0, 1, 21, 255});

        EndDrawing();
    }
    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
