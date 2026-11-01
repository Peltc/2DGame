#pragma once 
#include"platform.h"
#include"shader.h"
#include"matrix.h"
#include"box.h"
#include<stdbool.h>
typedef struct{
    int spawnedchunkcountlimit;
    int chunkcounter;
    int chunkcount;
    platform** p;
    bool spawnchunk;
}chunk;
chunk* _ini_chunk();
void _draw_chunk(chunk* c,matrix* m, shader* s);
void generatechunk(box*b,chunk*c,matrix*m,shader*s);
double chunkx(int i);


