#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include"delta.h"
delta*ini_delta(){
    delta*d=malloc(sizeof(delta));
    if(d==NULL){
        printf("delta null!\n");
        return NULL;
    }
    d->frame = 0;
    d->framecounter = 0;
    d->lasttime=clock();
    return d;
}
void FrameRatePerSecond(delta* d){
    d->framecounter+=d->maindelta;
    d->frame++;
    if(d->framecounter>=1.0f){
        printf("FPS: %d\n",d->frame);
        d->frame = 0;
        d->framecounter = 0;
    }
}
void deltatime(delta*d){
    clock_t starttime=clock();
    float dt=(float)(starttime-d->lasttime)/CLOCKS_PER_SEC;
    d->maindelta=dt;
    d->lasttime=starttime;
    //printf("delta: %f\n",d->maindelta);
    
}   
