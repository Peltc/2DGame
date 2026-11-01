#include"box.h"
#include"delta.h"
#include"platform.h"
#include"chunk.h"
#include"procu_spike.h"
#include"my_math.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/*physics.c*/
#define GRAVITY -6.0 // g = -2.0
void objectgravity(box*b,delta*d){
    b->vy+=GRAVITY*d->maindelta;
    b->posy+=b->vy*d->maindelta;
}
void collision(box*b,chunk*c){
    //box edges
    for(int i=0;i<c->chunkcount;i++){
        if(c->p[i]==NULL){
            continue;
        }
        float b_top=b->posy+b->sy;
        float b_bottom=b->posy-b->sy;
        float b_right=b->posx+b->sx;
        float b_left=b->posx-b->sx;
        //platforms edges
        float p_top=c->p[i]->posy+c->p[i]->sy;
        float p_bottom=c->p[i]->posy-c->p[i]->sy;
        float p_right=c->p[i]->posx+c->p[i]->sx;
        float p_left=c->p[i]->posx-c->p[i]->sx;
        bool check1=(b_top >= p_bottom && b_bottom <= p_top && b_right >= p_left && b_left <= p_right);
        if(check1){
            b->posy = b->sy + p_top;
            b->onground = true;
        }
    }
}
void collisionHit(box* b,procu_spike* s_ps){
    for(int k=0;k<s_ps->spikelimit;k++){
        if(s_ps->dupspike[k] == NULL){
            continue;
        }
        float dx = b->posx - s_ps->dupspike[k]->posx;
        float dy = b->posy - s_ps->dupspike[k]->posy;
        float distance = (dx*dx+dy*dy);
        float radius = 0.10f;
        float despawnradius = 10.0f;
        if(distance <= radius * radius){
            printf("collision hit\n");
            exit(0);
        }
        
        if(distance > despawnradius * despawnradius){
            free(s_ps->dupspike[k]);
            s_ps->dupspike[k] = NULL;
        }
        if(s_ps->dupspike[k] == NULL){
            s_ps->dupspike[k] = _ini_spike();
            if(s_ps->dupspike[k] == NULL){
                continue;
            }
            s_ps->dupspike[k]->posx = b->posx + 2.0f;
            s_ps->dupspike[k]->posy = -0.400f;
        }

    }
}



















