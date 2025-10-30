#pragma once

#include "config.h"

class Ball
{
public:
    float x, y;
    int speed_x, speed_y, radius;

    void Draw();
    void Update(int&, int&);
    void ResetBall();
    void StartResetDelay(float);

private:
    float resetTimer = 0.0f;
    bool isResetting = false;
};