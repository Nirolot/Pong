#include "config.h"
#include "Ball.h"
#include "Paddle.h"

class CpuPaddle : public Paddle
{
public:
    void Update(float ball_y)
    {
        if(y < ball_y) {
            y += speed;
        }
        if(y > ball_y) {
            y -= speed;
        }

        LimitMovement();
    }
};

Ball ball;
Paddle p1;
CpuPaddle cpu;

GameState currentState = TITLE;


void UpdateTitle()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        currentState = PLAYING;
        ball.ResetBall();
        p1.score = 0;
        cpu.score = 0;
    }
}

void UpdatePlaying()
{

    ball.Update(cpu.score, p1.score);
    p1.Update();
    cpu.Update(ball.y);


    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{p1.x, p1.y, p1.width, p1.height}))
    {
        ball.speed_x *= -1;
    }
    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
    {
        ball.speed_x *= -1;
    }


    if (IsKeyPressed(KEY_P))
    {
        currentState = PAUSED;
    }

    if (p1.score >= 10 || cpu.score >= 10)
    {
        currentState = GAME_OVER;
    }
}

void UpdatePaused()
{
    if (IsKeyPressed(KEY_P))
    {
        currentState = PLAYING;
    }
    if (IsKeyPressed(KEY_M))
    {
        currentState = TITLE;
    }
}

void UpdateGameOver()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        currentState = TITLE;
    }
}


void DrawTitle()
{
    const char *title = "PONG";
    const char *subtitle = "Premi ENTER per giocare";

    int fontSize1 = 120;
    int fontSize2 = 50;

    int x1 = (screenWidth - MeasureText(title, fontSize1)) / 2;
    int y1 = screenHeight / 4;

    int x2 = (screenWidth - MeasureText(subtitle, fontSize2)) / 2;
    int y2 = screenHeight / 2;

    DrawText(title, x1, y1, fontSize1, WHITE);
    DrawText(subtitle, x2, y2, fontSize2, GRAY);
}

void DrawPlaying()
{

    DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);


    p1.Draw();
    cpu.Draw();
    ball.Draw();


    DrawText(TextFormat("%i", cpu.score), screenWidth / 4 - 20, 20, 80, WHITE);
    DrawText(TextFormat("%i", p1.score), 3 * screenWidth / 4 - 20, 20, 80, WHITE);
}

void DrawPaused()
{

    DrawPlaying();


    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));


    const char *text = "PAUSA";
    const char *controls = "P = Riprendi  |  M = Menu";
    int fontSize = 80;
    int fontSize2 = 30;
    int x = (screenWidth - MeasureText(text, fontSize)) / 2;
    int y = screenHeight / 2;
    int x2 = (screenWidth - MeasureText(controls, fontSize2)) / 2;

    DrawText(text, x, y, fontSize, WHITE);
    DrawText(controls, x2, y + 100, fontSize2, GRAY);
}

void DrawGameOver()
{
    DrawPlaying();

    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));

    const char *winner = (p1.score >= 10) ? "GIOCATORE VINCE!" : "CPU VINCE!";
    int fontSize = 60;
    int x = (screenWidth - MeasureText(winner, fontSize)) / 2;

    DrawText(winner, x, screenHeight / 2 - 50, fontSize, YELLOW);
    DrawText("Premi ENTER", x + 50, screenHeight / 2 + 50, 40, WHITE);
}

void SetUpGame()
{
    ball.radius = 10;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speed_x = 11;
    ball.speed_y = 11;

    p1.width = 25;
    p1.height = 120;
    p1.x = screenWidth - p1.width - 10;
    p1.y = screenHeight / 2 - p1.height / 2;
    p1.speed = 11;
    p1.score = 0;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screenHeight / 2 - cpu.height / 2;
    cpu.speed = 11;
    cpu.score = 0;
}