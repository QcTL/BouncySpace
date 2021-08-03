#include "include/raylib.h"
#include <cstdio>

class Score
{
public:
    Score();
    Score(Vector2 t_posScore, int t_size, int t_score);
    int getScore();
    void countScore();
    Rectangle getRectScore();

private:
    int score;
    float size;
    Rectangle recScore;
    Vector2 posScore;
};

Score::Score() {}

Score::Score(Vector2 t_posScore, int t_size, int t_score)
{
    posScore = t_posScore;
    size = t_size;
    score = t_score;
    recScore = {posScore.x, posScore.y, size, size};
}

Rectangle Score::getRectScore()
{
    return recScore;
}

int Score::getScore()
{
    return score;
}