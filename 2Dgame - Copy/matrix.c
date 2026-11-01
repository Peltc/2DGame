#include<glad/gl.h>
#include<stdlib.h>
#include<stdio.h>
#include"matrix.h"
#include"my_math.h"
//matrix.c
//here is my matrix math for 2D and i have no idea why i want to implement this on 2D :(((( its worth it to learn!!!
matrix*identity(){
    matrix*m=malloc(sizeof(matrix));   
    m->matt[0]=1.0f;m->matt[1]=0.0f;m->matt[2]=0.0f;
    m->matt[3]=0.0f;m->matt[4]=1.0f;m->matt[5]=0.0f;
    m->matt[6]=0.0f;m->matt[7]=0.0f;m->matt[8]=1.0f;
    return m;
}
matrix*translation(float x,float y){
    matrix*m=identity();
    m->matt[2]=x;
    m->matt[5]=y;
    return m;
}
matrix*rotation(float angle){
    matrix*m=identity();
    m->matt[0]=my_cos(angle),m->matt[1]=-my_sin(angle);
    m->matt[3]=my_sin(angle),m->matt[4]=my_cos(angle);
    return m;
}
matrix*scale(float sx,float sy){
    matrix*m=identity();
    m->matt[0]=sx;
    m->matt[4]=sy;
    return m;
}
matrix*multiply(matrix*A,matrix*B){
    matrix*m=identity();
    for(int row=0;row<3;row++){
        for(int col=0;col<3;col++){
            m->matt[row*3+col]=
                A->matt[row*3+0] * B->matt[0*3+col] +
                A->matt[row*3+1] * B->matt[1*3+col] +
                A->matt[row*3+2] * B->matt[2*3+col];
        }
    }
    return m;
}








