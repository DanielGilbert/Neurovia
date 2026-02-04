#include "raylib.h"
#include "raymath.h"

const int screenHeight = 1080;
const int screenWidth = 1920;

void GameStartup();
void GameUpdate();
void GameRender();
void GameShutdown();

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    GameStartup();

    InitWindow(screenWidth, screenHeight, "Neurovia");

    while (!WindowShouldClose()) {
        
        GameUpdate();
        ClearBackground(BLACK);
        BeginDrawing();
        DrawFPS(10,10);
        DrawText("This is a test!", 10, 30, 22, PINK);
        GameRender();
        EndDrawing();
    }

    GameShutdown();

    CloseWindow();          // Close window and OpenGL context

    return 0;
}

void GameStartup() {
    InitAudioDevice();
}

void GameUpdate() {

}

void GameRender() {

}

void GameShutdown() {
    CloseAudioDevice();
}