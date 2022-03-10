#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <raylib.h>

#include "raycast.h"
#include "config.h"

Hit RayCast(sRay ray, Wall wall) {
    float x1 = wall.p1.x;
    float y1 = wall.p1.y;
    float x2 = wall.p2.x;
    float y2 = wall.p2.y;

    float x3 = ray.pos.x;
    float y3 = ray.pos.y;
    float x4 = x3 + cosf(ray.angle);
    float y4 = y3 + sinf(ray.angle);

    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    Hit hit = {false, {0, 0}};

    if(d != 0) {
        float u = ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2))/d;
        float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4))/d;

        if(t >= 0 && t <= 1 && u >= 0) {
            hit.hit = true;

            hit.pos.x = x1 + t * (x2 - x1);
            hit.pos.y = y1 + t * (y2 - y1);
        }
    }

    return hit;
}

void MovePlayer(Player* player, Direction dir, float amount) {
    switch (dir) {
    case FOREWARD:
        player->pos.x += cosf(player->angle) * amount;
        player->pos.y += sinf(player->angle) * amount;
        break;
        
    case BACKWARD:
        player->pos.x += cosf(player->angle + M_PI) * amount;
        player->pos.y += sinf(player->angle + M_PI) * amount;
        break;

    case LEFT:
        player->pos.x += cosf(player->angle - M_PI_2) * amount;
        player->pos.y += sinf(player->angle - M_PI_2) * amount;
        break;

    case RIGHT:
        player->pos.x += cosf(player->angle + M_PI_2) * amount;
        player->pos.y += sinf(player->angle + M_PI_2) * amount;
        break;
    
    default:
        break;
    }
}

void RotatePlayer(Player* player, float angle) {
    player->angle += angle;
}

void RenderView(Player player, World world) {
    sRay ray = {player.angle - player.FOVh/2, {player.pos.x, player.pos.y}};
    for(int column = 0; column < W; column++) {

        float dist = INFINITY;

        for(int wall = 0; wall < world.wallCount; wall++) {
            Hit hit = RayCast(ray, world.walls[wall]);

            if(hit.hit) {
                float dx = player.pos.x - hit.pos.x;
                float dy = player.pos.y - hit.pos.y;

                float d = sqrtf(dx*dx + dy*dy);

                if(d < dist) {
                    dist = d;
                }
            }
        }

        if(dist != INFINITY) {
            float brightness = 1.0f/(dist*dist);
            float height = (H  * (1 / tanf(player.FOVv)) / dist) / 2;
            
            DrawLine(column, H/2 + height, column, H/2 - height, ColorAlpha(WHITE, brightness));
        }

        ray.angle += player.FOVh/W;
    }
}

World ReadMapFile(char *filename) {
    FILE *map = fopen(filename, "r");

    char line[160] = {0};

    World m;

    int wallIdx = 0;

    bool firstLine = true;
    while(fgets(line, 160, map)) {
        int idx = 0;
        for(char* tok = strtok(line, ","); tok != NULL; tok = strtok(NULL, ",")) {
            if(!firstLine) {
                switch (idx) {
                case 0:
                    m.walls[wallIdx].p1.x = atof(tok);
                    break;

                case 1:
                    m.walls[wallIdx].p1.y = atof(tok);
                    break;

                case 2:
                    m.walls[wallIdx].p2.x = atof(tok);
                    break;

                case 3:
                    m.walls[wallIdx].p2.y = atof(tok);
                    break;
                
                default:
                    break;
                }
            } else {
                switch(idx) {
                case 0:
                    m.walls = malloc(sizeof(Wall) * atoi(line));
                    m.wallCount = atoi(tok);
                    break;
                    
                case 1:
                    m.spawn.x = atof(tok);
                    break;

                case 2:
                    m.spawn.y = atof(tok);
                    break;
                }
            }

            idx++;
        }

        firstLine = false;
        wallIdx++;
    }

    fclose(map);

    return m;
}