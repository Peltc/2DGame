#include<glad/gl.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"box.h"
#include"shader.h"
#include"matrix.h"
#include"delta.h"
#define FINALBOXSIZE 1.0
#define FINALSPEED 0.03
#define JUMPVELO 2.0
box* _ini_box(){
    box*b=malloc(sizeof(box));
    b->r=FINALBOXSIZE;
    b->speed=FINALSPEED;
    //changeable Values size
    b->vx=0.0f;
    b->vy=0.0f;
    b->sx=0.05f;
    b->sy=0.05f;
    b->posx=0.0f;
    b->posy=0.0f;
    b->onground=false;
    float vertex[18]=
    {
        b->r,b->r,b->r-b->r,
        -b->r,-b->r,b->r-b->r,
        b->r,-b->r,b->r-b->r,
        b->r,b->r,b->r-b->r,
        -b->r,b->r,b->r-b->r,
        -b->r,-b->r,b->r-b->r,
    };
    glGenBuffers(1,&b->vbo);
    glBindBuffer(GL_ARRAY_BUFFER,b->vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    return b;
}
void b_draw(box*b){
    glBindBuffer(GL_ARRAY_BUFFER,b->vbo);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glDrawArrays(GL_TRIANGLES,0,6);
}
void b_ownmatrix(box*b,shader* s,matrix* m){
    matrix*T=translation(b->posx,b->posy);
    matrix*R=rotation(0.0f);
    matrix*S=scale(b->sx,b->sy);
    matrix*RS=multiply(R,S);
    matrix*TRSresult=multiply(T,RS);
    glUniformMatrix3fv(s->uModel,1,GL_TRUE,TRSresult->matt);
    free(T);
    free(R);
    free(S);
    free(RS);
    free(TRSresult);
}
void _moveauto(box*b,delta*d){
    //printf("posx: %f\n",b->posx);
    //printf("posy: %f\n",b->posy);
    b->vx += 0.00000000002 * d->maindelta;
    //printf("box speed/vx: %f\n",b->vx);
    b->vx+=b->speed*d->maindelta;
    /*if(b->vx>=0.5f){
        b->vx=0.5f; this is optional!
    }*/
    b->posx+=b->vx*d->maindelta;
}
void jumpplayer(box*b){
    b->vy = JUMPVELO;
    
}
