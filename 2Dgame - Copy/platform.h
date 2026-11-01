#pragma once
#include<glad/gl.h>
#include"shader.h"
#include"matrix.h"
#include"platform.h"
typedef struct{
    GLuint VBO,vao;
    float r;
    float sy;
    float sx;
    float posx;
    float posy;
}platform;
platform*ini_platform();
void p_draw(shader*s,matrix*m,platform*p);
void p_matrix(matrix*m,shader*s,platform*p);


