#include "include/raylib.h"
#include "head.cpp"
#include "score.cpp"
#include <cstdio>
#include <cmath>
const int screenWidth = 640;
const int screenHeight = 640;

Vector2 startPointLine;
Vector2 endPointLine;

void DetectClicks(Head &h, float &timeSlow)
{
    if (IsMouseButtonPressed(0))
    {
        startPointLine = GetMousePosition();
        h.setVelocity(h.getVelocity(0) / 5);
        printf("NEW : %f - NoSlow: %f ", h.getVelocity(0), h.getVelocity(1));
    }
    else if (IsMouseButtonDown(0))
    {
        endPointLine = GetMousePosition();
        DrawLineEx(startPointLine, endPointLine, 10, {212, 12, 45, 255});

        if (timeSlow > 0)
        {
            h.setVelocity(h.getVelocity(0));
            timeSlow -= GetFrameTime();
            //printf("%f ", timeSlow);
        }
        else
        {
            h.setVelocity(h.getVelocity(1));
        }
    }

    //Quan deixem anar el boto enviara el VectorUnitari del angle:
    if (IsMouseButtonReleased(0))
    {
        Vector2 vecUnitari;
        float distancia;

        float dirX = startPointLine.x - endPointLine.x;
        float dirY = startPointLine.y - endPointLine.y;
        distancia = abs(sqrt(dirX * dirX + dirY * dirY));
        if (distancia > 5)
        {
            vecUnitari.x = dirX / distancia;
            vecUnitari.y = dirY / distancia;
            h.setDirAndDist(vecUnitari, distancia / 100);
            timeSlow = 2;
        }
    }
}

int scoreTotal = 0;

void showScore()
{

    DrawText(TextFormat("%i", scoreTotal), 20, 10, 70, DARKGRAY);
}

Score ListScores[5];
int indexScores = 0;

void renderScores()
{
    for (int i = 0; i < indexScores; i++)
    {
        DrawRectangleRec(ListScores[i].getRectScore(), YELLOW);
    }
}

void addScores(Score &t_score)
{
    ListScores[indexScores] = t_score;
    indexScores++;
}

void deleteScores(int index)
{
    scoreTotal += ListScores[index].getScore();
    for (int i = index; i < indexScores - 1; i++)
    {
        ListScores[i] = ListScores[i + 1];
    }
    indexScores--;

    printf("%f", indexScores);
}

void checkCollisionRecs(Head &h)
{
    int i = 0;
    bool trobat = false;
    while (i < indexScores && !trobat)
    {
        if (CheckCollisionRecs(h.getRectangle(), ListScores[i].getRectScore()))
        {
            printf("Checking collision... TROBAT %i", i);
            deleteScores(i);
            trobat = true;
            break;
        }
        i++;
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
    float timeSlow = 2;

    //SCORE DE PROBA
    Vector2 posScore;
    posScore.x = 50;
    posScore.y = 50;
    Score r = Score(posScore, 5, 10);
    addScores(r);

    // Main game loop
    while (!WindowShouldClose())
    {

        //Calculs
        h.ActualizePosition(screenWidth, screenHeight);
        showScore();

        renderScores();
        checkCollisionRecs(h);
        //DrawRectangleRec(r.getRectScore(), YELLOW);

        // Update
        DetectClicks(h, timeSlow);
        DrawRectangleRec(h.getRectangle(), BLUE);
        BeginDrawing();
        ClearBackground({0, 1, 21, 255});

        EndDrawing();
    }
    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
