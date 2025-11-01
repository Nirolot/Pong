#include "config.h"
#include "Ball.h"
#include "Paddle.h"

int main()
{
    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);

    SetUpGame();

    while (!WindowShouldClose())
    {
        switch (currentState)
        {
        case TITLE:
            UpdateTitle();
            break;
        case PLAYING:
            UpdatePlaying();
            break;
        case PAUSED:
            UpdatePaused();
            break;
        case GAME_OVER:
            UpdateGameOver();
            break;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        switch (currentState)
        {
        case TITLE:
            DrawTitle();
            break;
        case PLAYING:
            DrawPlaying();
            break;
        case PAUSED:
            DrawPaused();
            break;
        case GAME_OVER:
            DrawGameOver();
            break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}