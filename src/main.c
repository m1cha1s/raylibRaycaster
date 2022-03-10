#include <stdio.h>
#include <math.h>

#include <raylib.h>

#include "raycast.h"
#include "config.h"

int main(void) {
    InitWindow(W, H, "raylibTest");
    SetTargetFPS(60);
    
    World world = ReadMapFile("C:/Users/schon/sync/projects/C/raylibTest/map.map");

    float px = world.spawn.x;
    float py = world.spawn.y;

    Player player = {{px, py}, M_PI, M_PI/2, M_PI/6};

    while(!WindowShouldClose()) {
        BeginDrawing();

        // Moving player
        if(IsKeyDown(KEY_W)) MovePlayer(&player, FOREWARD, WALKING_SPEED);
        if(IsKeyDown(KEY_S)) MovePlayer(&player, BACKWARD, WALKING_SPEED);
        if(IsKeyDown(KEY_A)) MovePlayer(&player, LEFT, WALKING_SPEED);
        if(IsKeyDown(KEY_D)) MovePlayer(&player, RIGHT, WALKING_SPEED);

        // Rotating player
        if(IsKeyDown(KEY_J)) RotatePlayer(&player, -ROTATION_SPEED);
        if(IsKeyDown(KEY_K)) RotatePlayer(&player, ROTATION_SPEED);

        ClearBackground(BLACK);
        RenderView(player, world);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}