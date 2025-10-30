#include "config.h"
#include "Ball.h"
#include "Paddle.h"

class CpuPaddle : public Paddle
{
public:
    void Update(int ball_y)
    {
        if (y + height / 2 > ball_y)
        {
            y -= speed;
        }
        else if (y + height / 2 <= ball_y)
        {
            y += speed;
        }

        LimitMovement();
    }
};

Ball ball;
Paddle player;
CpuPaddle cpu;
Paddle player2;

int main()
{
    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);

    ball.radius = 10;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speed_x = 11;
    ball.speed_y = 11;

    player.width = 25;
    player.height = 120;
    player.x = screenWidth - player.width - 10;
    player.y = screenHeight / 2 - player.height / 2;
    player.speed = 10;
    player.score = 0;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screenHeight / 2 - cpu.height / 2;
    cpu.speed = 10;
    cpu.score = 0;

    player2 = cpu;

    bool Title = true;

    while (!WindowShouldClose())
    {
        if (Title)
        {
            char *testo = "Pong";
            int fontSize = 120;
            int larghezzaTesto = MeasureText(testo, fontSize);

            int posX = (screenWidth / 2) - (larghezzaTesto / 2);
            int posY = screenHeight / 4;

            BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(screenWidth / 3, screenHeight / 2 + 40, 100, 50, WHITE);
            DrawRectangle(screenWidth / (4.0 / 3.0) - 200, screenHeight / 2 + 40, 100, 50, WHITE);
            DrawText(testo, posX, posY, fontSize, WHITE);
            DrawText("P v P", screenWidth / 3, screenHeight / 2 + 40, 30, BLACK);
            EndDrawing();

            if (IsKeyDown(KEY_ENTER))
            {
                Title = false;
            }
        }

        else
        {
            ball.Update(cpu.score, player.score);
            player.Update();
            cpu.Update(ball.y);

            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
            {
                ball.speed_x *= -1;
            }
            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
            {
                ball.speed_x *= -1;
            }

            BeginDrawing();
            ClearBackground(BLACK);
            DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
            player.Draw();
            cpu.Draw();
            ball.Draw();

            DrawText(TextFormat("%i", cpu.score), screenWidth / 4 - 20, 20, 80, WHITE);
            DrawText(TextFormat("%i", player.score), screenWidth / 4 * 3 - 20, 20, 80, WHITE);
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}