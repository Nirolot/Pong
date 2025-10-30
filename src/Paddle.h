#pragma once

#include "config.h"

class Paddle
{
protected:
    void LimitMovement();

public:
    float x, y, width, height;
    int speed;
    int score;

    void Draw();

    void Update();
};