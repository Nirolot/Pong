#include "config.h"
#include "Ball.h"
#include "Paddle.h"

class CpuPaddle : public Paddle
{
public:
    void Update()
    {
        if (IsKeyDown(KEY_W))
        {
            y -= speed;
        }
        else if (IsKeyDown(KEY_S))
        {
            y += speed;
        }

        LimitMovement();
    }
};

Ball ball;
Paddle p1;
CpuPaddle cpu;
CpuPaddle p2;

int main()
{
    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);

    ball.radius = 10;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speed_x = 11;
    ball.speed_y = 11;

    p1.width = 25;
    p1.height = 120;
    p1.x = screenWidth - p1.width - 10;
    p1.y = screenHeight / 2 - p1.height / 2;
    p1.speed = 10;
    p1.score = 0;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screenHeight / 2 - cpu.height / 2;
    cpu.speed = 10;
    cpu.score = 0;

    p2 = cpu;

    bool Title = true;

    while (!WindowShouldClose())
    {
        if (Title)
        {
            char *testo = "Pong";
            char *testo2 = "Press enter to play";
            int fontSize = 120;
            int fontSize2 = 50;
            int larghezzaTesto = MeasureText(testo, fontSize);
            int larghezzaTesto2 = MeasureText(testo2, fontSize2);

            int posX = (screenWidth / 2) - (larghezzaTesto / 2);
            int posY = screenHeight / 4;
            int posX2 = (screenWidth / 2) - (larghezzaTesto2 / 2);
            int posY2 = screenHeight / 2 + fontSize2 * 2;

            BeginDrawing();
            ClearBackground(BLACK);
            // DrawRectangle(screenWidth / 3, screenHeight / 2 + 40, 100, 50, WHITE);
            // DrawRectangle(screenWidth / (4.0 / 3.0) - 200, screenHeight / 2 + 40, 100, 50, WHITE);
            DrawText(testo, posX, posY, fontSize, WHITE);
            DrawText(testo2, posX2, posY2, fontSize2, WHITE);
            // DrawText("P v P", screenWidth / 3, screenHeight / 2 + 40, 30, BLACK);
            EndDrawing();

            if (IsKeyDown(KEY_ENTER))
            {
                Title = false;
            }
        }

        else
        {
            ball.Update(p2.score, p1.score);
            p1.Update();
            p2.Update();

            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{p1.x, p1.y, p1.width, p1.height}))
            {
                ball.speed_x *= -1;
            }
            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{p2.x, p2.y, p2.width, p2.height}))
            {
                ball.speed_x *= -1;
            }

            BeginDrawing();
            ClearBackground(BLACK);
            DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
            p1.Draw();
            p2.Draw();
            ball.Draw();

            DrawText(TextFormat("%i", p2.score), screenWidth / 4 - 20, 20, 80, WHITE);
            DrawText(TextFormat("%i", p1.score), screenWidth / 4 * 3 - 20, 20, 80, WHITE);
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}