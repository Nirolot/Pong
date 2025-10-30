#include "Paddle.h"

void Paddle::LimitMovement()
{
    if (y <= 0)
    {
        y = 0;
    }
    else if (y + height >= GetScreenHeight())
    {
        y = GetScreenHeight() - height;
    }
}

void Paddle::Draw()
{
    DrawRectangle(x, y, width, height, WHITE);
}

void Paddle::Update()
{
    if (IsKeyDown(KEY_UP))
    {
        y -= speed;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        y += speed;
    }

    LimitMovement();
}