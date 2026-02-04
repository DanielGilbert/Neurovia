#include "raylib.h"
#include "raymath.h"
#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include "raylib-aseprite.h"

#define TILE_HEIGHT 16
#define TILE_WIDTH 16

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

Camera2D camera = { 0 };

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    GameStartup();

    while (!WindowShouldClose()) {
        
        GameUpdate();
        ClearBackground(BLACK);
        BeginDrawing();
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

    camera.target = (Vector2){ 0,0 };
    camera.offset = (Vector2){ (float)screenWidth / 2, (float)screenHeight / 2};
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;
}

void GameUpdate() {
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        const float zoomIncrement = 0.125f;
        camera.zoom += (wheel * zoomIncrement);
        if (camera.zoom < 3.0f) camera.zoom = 3.0f;
        if (camera.zoom > 8.0f) camera.zoom = 8.0f;
    }

    camera.target = (Vector2){0,0};
}

void GameRender() {
    BeginMode2D(camera);

    sTile tile;

    for (int i = 0; i < WORLD_WIDTH; i++) {
        for (int j = 0; j < WORLD_HEIGHT; j++) {
            tile = world[i][j];
            DrawAseprite(sprites[GROUND], 1, tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, RAYWHITE);
        }
    }
    DrawAseprite(sprites[HUMAN], 1, 8 * TILE_WIDTH, 12 * TILE_HEIGHT, SKYBLUE);

    EndMode2D();

    DrawRectangle(5,5,330,120,Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(5,5,330,120,BLUE);

    DrawFPS(15,50);
    DrawText(TextFormat("Camera Target: (%06.2f, %06.2f)", camera.target.x, camera.target.y), 15, 10, 14, YELLOW);
    DrawText(TextFormat("Camera Zoom: %06.2f", camera.zoom), 15, 30, 14, YELLOW);
}

void GameShutdown() {
    for (int i = 0; i < MAX_SPRITES; i++) {
        UnloadAseprite(sprites[i]);
    }
    CloseAudioDevice();

}