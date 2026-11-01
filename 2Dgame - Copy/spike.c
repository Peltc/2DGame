#include<glad/gl.h>
#include<stdlib.h>
#include"spike.h"
#include"matrix.h"
#include<stdio.h>
spike* _ini_spike(){
    spike* s = malloc(sizeof(spike));
    if(s==NULL){
        printf("spike memory missing!\n");
        return NULL;
            }   
    s->posx = 9000000.0f;
    s->posy = 9000000.0f;
    s->sx = 0.05f;
    s->sy = 0.1f;
    s->r = 1.0f;
    float vertex[9] = 
    {
        s->r-s->r,s->r,s->r-s->r,
        -s->r,-s->r,s->r-s->r,
        s->r,-s->r,s->r-s->r
    };
    glGenBuffers(1,&s->VBO);
    glBindBuffer(GL_ARRAY_BUFFER,s->VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    return s;
}
void s_draw(spike*s){
    glBindBuffer(GL_ARRAY_BUFFER,s->VBO);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glDrawArrays(GL_TRIANGLES,0,3);
}
void s_matrix(shader*shaderS,matrix*m,spike*s){
    matrix*T = translation(s->posx,s->posy);
    matrix*R = rotation(0.0f);
    matrix*S = scale(s->sx,s->sy);
    matrix*RS = multiply(R,S);
    matrix*s_multiply = multiply(T,RS);
    glUniformMatrix3fv(shaderS->uModel,1,GL_TRUE,s_multiply->matt);
    free(T);free(R);free(S);free(RS);free(s_multiply);
} 
