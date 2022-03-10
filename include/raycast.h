#ifndef RAYCAST_H
#define RAYCAST_H

#include <stdbool.h>

typedef struct XY {
    float x, y;
}XY;

typedef enum Direction {
    FOREWARD,
    BACKWARD,
    LEFT,
    RIGHT,
}Direction;

typedef struct Player {
    XY pos;
    float angle;
    float FOVh, FOVv;
}Player;

typedef struct sRay {
    float angle;
    XY pos;
}sRay;

typedef struct Hit {
    bool hit;
    XY pos;
}Hit;

typedef struct Wall {
    XY p1, p2;
}Wall;

typedef struct World {
    int wallCount;
    Wall *walls;
    XY spawn;
}World;

Hit RayCast(sRay ray, Wall wall);

void MovePlayer(Player* player, Direction dir, float amount);
void RotatePlayer(Player* player, float angle);

void RenderView(Player player, World world);

World ReadMapFile(char *filename);

#endif