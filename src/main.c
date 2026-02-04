#include "raylib.h"

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    InitWindow(1920,1080,"Neurovia");

    while (!WindowShouldClose()) {
        ClearBackground(BLACK);
        BeginDrawing();
        DrawFPS(10,10);
        EndDrawing();
    }

    CloseWindow();          // Close window and OpenGL context

    return 0;
}