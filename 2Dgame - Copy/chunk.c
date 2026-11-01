#include"chunk.h"
#include"platform.h"
#include"matrix.h"
#include"shader.h"
#include"box.h"
#include<stdio.h>
#include<stdlib.h>
chunk* _ini_chunk(){
    chunk* c = malloc(sizeof(chunk));
    if(c==NULL){
        return NULL;
    }
    c->spawnchunk = false;
    c->spawnedchunkcountlimit = 3;
    c->chunkcount = 3;
    c->chunkcounter = 0;
    c->p = calloc(c->chunkcount,sizeof(platform*));
    if(c->p==NULL){
        free(c);
        return NULL;
    }
    return c;
}
//the math here for positioning
double chunkx(int i){
    return 1.0f + (i*10000000000000000000.0f);
}
void generatechunk(box*b,chunk*c,matrix*m,shader*s){
    if(c->spawnchunk){
        for(int i=0;i<c->chunkcount;i++){
            c->p[i] = ini_platform();
            if(c->p[i]==NULL){
                return;
            }
            c->p[i]->posx = chunkx(i);
            c->p[i]->posy = -1.0f;
            c->p[i]->sx = (double)10000000000000000000.0f;
            c->p[i]->sy = 0.5f;
            c->chunkcounter+=1;
            //printf("platform x: %f\n",c->p[i]->posx);
        }
        c->spawnchunk = false;
    }
    if(c->chunkcounter>c->spawnedchunkcountlimit){
        c->spawnchunk = false;
    }
    if(c->chunkcounter<c->spawnedchunkcountlimit){
        c->spawnchunk = true;
    }

    if(c->p[0] != NULL &&
       c->p[1] != NULL &&
       c->p[2] != NULL){
        _draw_chunk(c,m,s);
    }
}
void _draw_chunk(chunk* c,matrix* m, shader* s){
    for(int draw=0;draw<c->chunkcount;draw++){
        glUniform4f(s->uColor,0.0f,1.0f,0.0f,1.0f);
        p_matrix(m,s,c->p[draw]);
        p_draw(s,m,c->p[draw]);
    }
}
