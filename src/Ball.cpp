#include "Ball.h"

void Ball::Draw()
{
    DrawCircle(x, y, radius, WHITE);
}

void Ball::Update(int &score_p1, int &score_p2)
{
    if (isResetting)
    {
        resetTimer -= GetFrameTime();
        if (resetTimer <= 0.0f)
        {
            isResetting = false;
            ResetBall();
        }
        return;
    }

    x += speed_x;
    y += speed_y;

    if (y + radius >= GetScreenHeight() || y - radius <= 0)
    {
        speed_y *= -1;
    }

    if (x + radius >= GetScreenWidth())
    {
        score_p1++;
        StartResetDelay(1.5f);
    }

    if (x - radius <= 0)
    {
        score_p2++;
        StartResetDelay(1.5f);
    }
}

void Ball::StartResetDelay(float seconds)
{
    resetTimer = seconds;
    isResetting = true;
}

void Ball::ResetBall()
{
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    int speed_choices[2] = {-1, 1};
    speed_x = 11 * speed_choices[GetRandomValue(0, 1)];
    speed_y = 11 * speed_choices[GetRandomValue(0, 1)];
}
