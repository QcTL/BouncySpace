#include "include/raylib.h"
#include "head.cpp"
#include "score.cpp"
#include <cstdio>
#include <cmath>
const int screenWidth = 640;
const int screenHeight = 640;

Vector2 startPointLine;
Vector2 endPointLine;

bool gameDead = false;

int shots = 3;
void DetectClicks(Head &h, float &timeSlow)
{
    if (shots > 0)
    {
        if (IsMouseButtonPressed(0))
        {
            startPointLine = GetMousePosition();
            h.setVelocity(h.getVelocity(0) / 5);
        }
        else if (IsMouseButtonDown(0))
        {
            endPointLine = GetMousePosition();
            DrawLineEx(startPointLine, endPointLine, 10, {212, 12, 45, 255});

            if (timeSlow > 0)
            {
                h.setVelocity(h.getVelocity(0));
                timeSlow -= GetFrameTime();
            }
            else
            {
                h.setVelocity(h.getVelocity(1));
            }
        }

        //When released will send to VectorUnitarti the angle of rotation;
        if (IsMouseButtonReleased(0))
        {
            h.resetBounces();
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
                shots--;
            }
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

    shots = 3;
    //Create a newScore
    if (indexScores < 5)
    {
        for (int i = 0; i < GetRandomValue(1, 2); i++)
        {
            Vector2 posScore;
            posScore.x = GetRandomValue(0, screenWidth);
            posScore.y = GetRandomValue(0, screenHeight);
            Score r = Score(posScore, 5, 10);
            addScores(r);
        }
    }
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

Vector2 posS1, posS2, posS3;
Vector2 sizeS;
void setShotsLeft()
{
    posS1.x = 550;
    posS1.y = 600;

    posS2.x = 550;
    posS2.y = 570;

    posS3.x = 550;
    posS3.y = 540;

    sizeS.x = 100;
    sizeS.y = 25;
}

void renderShotsLeft()
{
    switch (shots)
    {
    case 3:
    {
        DrawRectangleV(posS1, sizeS, WHITE);
        DrawRectangleV(posS2, sizeS, WHITE);
        DrawRectangleV(posS3, sizeS, WHITE);
    }
    break;
    case 2:
    {
        DrawRectangleV(posS1, sizeS, WHITE);
        DrawRectangleV(posS2, sizeS, WHITE);
    }
    break;
    case 1:
    {
        DrawRectangleV(posS1, sizeS, WHITE);
    }
    break;
    default:
        break;
    }
}

void renderDeathScreen()
{
    DrawRectangle(0, 0, screenWidth, screenHeight, {0, 0, 0, 100});
    DrawText(TextFormat("GAME OVER"), 50, 50, 90, WHITE);
}
void isDeadState(const Head &h)
{
    if (shots == 0 && h.getBounces() > 1)
    {
        gameDead = true;
    }
}

int main(void)
{

    InitWindow(screenWidth, screenHeight, "Bouncy Space");

    SetTargetFPS(60);

    Vector2 startPos;
    startPos.x = screenWidth / 2;
    startPos.y = 200;
    Head h = Head(startPos);
    float timeSlow = 2;

    //INITIAL SCORE
    Vector2 posScore;
    posScore.x = screenWidth / 2;
    posScore.y = screenHeight / 2;
    Score r = Score(posScore, 5, 10);
    addScores(r);

    setShotsLeft();

    // Main game loop
    while (!WindowShouldClose())
    {

        h.ActualizePosition(screenWidth, screenHeight);
        showScore();
        renderScores();
        checkCollisionRecs(h);

        // Update
        DetectClicks(h, timeSlow);
        DrawRectangleRec(h.getRectangle(), BLUE);
        renderShotsLeft();
        isDeadState(h);
        if (gameDead)
        {
            renderDeathScreen();
        }
        BeginDrawing();
        ClearBackground({0, 1, 21, 255});

        EndDrawing();
    }
    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
