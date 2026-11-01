//platform.c
#include<glad/gl.h>
#include"platform.h"
#include<stdlib.h>
#include"shader.h"
#include"matrix.h"
#define platformsx 1.0
#define platformsy 0.1
platform*ini_platform(){
    platform*p=malloc(sizeof(platform));
    p->r=1.0f;
    p->sx=platformsx;
    p->sy=platformsy;
    p->posx=0.0f;
    p->posy=90000.0f;
    float vertex[18]=
    {
        p->r,p->r,p->r-p->r,
        -p->r,-p->r,p->r-p->r,
        p->r,-p->r,p->r-p->r,

        p->r,p->r,p->r-p->r,
        -p->r,p->r,p->r-p->r,
        -p->r,-p->r,p->r-p->r,
    };
    glGenBuffers(1,&p->VBO);
    glBindBuffer(GL_ARRAY_BUFFER,p->VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    return p;
}
void p_draw(shader*s,matrix*m,platform*p){
    glBindBuffer(GL_ARRAY_BUFFER,p->VBO);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glDrawArrays(GL_TRIANGLES,0,6);
}
void p_matrix(matrix*m,shader*s,platform*p){
    matrix*T=translation(p->posx,p->posy);
    matrix*R=rotation(0.0f);
    matrix*S=scale(p->sx,p->sy);
    matrix*RS=multiply(R,S);
    matrix*TRSresult=multiply(T,RS);
    glUniformMatrix3fv(s->uModel,1,GL_TRUE,TRSresult->matt);
    free(T);free(S);free(R);free(RS);free(TRSresult);
}


