#pragma once

#include <iostream>
#include <raylib.h>

const int screenWidth = 1280;
const int screenHeight = 800;

enum GameState {
    TITLE,
    PLAYING,
    PAUSED,
    GAME_OVER
};

extern GameState currentState;

void UpdateTitle();
void UpdatePlaying();
void UpdatePaused();
void UpdateGameOver();

void DrawTitle();
void DrawPlaying();
void DrawPaused();
void DrawGameOver();

void SetUpGame();