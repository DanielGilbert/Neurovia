#include "raylib.h"
#include "raymath.h"
#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include "raylib-aseprite.h"

#define TILE_HEIGHT 8
#define TILE_WIDTH 8

const int screenHeight = 1080;
const int screenWidth = 1920;

void GameStartup();
void GameUpdate();
void GameRender();
void GameShutdown();

#define MAX_SPRITES 2
typedef enum {
    HUMAN = 0,
    GROUND = 1
} aseprite_asset;

Aseprite sprites[MAX_SPRITES];

#define WORLD_WIDTH 20
#define WORLD_HEIGHT 20

typedef struct {
    int x;
    int y;
} sTile;

sTile world[WORLD_WIDTH][WORLD_HEIGHT];

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    GameStartup();

    while (!WindowShouldClose()) {
        
        GameUpdate();
        ClearBackground(BLACK);
        BeginDrawing();
        DrawFPS(10,10);
        DrawText("This is a test!", 10, 30, 22, PINK);
        DrawAseprite(sprites[HUMAN], 1, 100, 100, WHITE);
        DrawAseprite(sprites[GROUND], 1, 140, 100, WHITE);
        GameRender();
        EndDrawing();
    }

    GameShutdown();

    CloseWindow();          // Close window and OpenGL context

    return 0;
}

void GameStartup() {
    InitAudioDevice();
    InitWindow(screenWidth, screenHeight, "Neurovia");

    sprites[HUMAN] = LoadAseprite("resources/human.ase");
    sprites[GROUND] = LoadAseprite("resources/ground-floor.ase");

    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int y = 0; y < WORLD_HEIGHT; y++) {
            world[x][y] = (sTile){
            .x = x,
            .y = y
            };
        }
    }
}

void GameUpdate() {

}

void GameRender() {
    sTile tile;

    for (int i = 0; i < WORLD_WIDTH; i++) {
        for (int j = 0; j < WORLD_HEIGHT; j++) {
            tile = world[i][j];
            DrawAseprite(sprites[GROUND], 1, tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, RAYWHITE);
        }
    }
}

void GameShutdown() {
    for (int i = 0; i < MAX_SPRITES; i++) {
        UnloadAseprite(sprites[i]);
    }
    CloseAudioDevice();

}