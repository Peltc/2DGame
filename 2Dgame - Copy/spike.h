#pragma once
#include<glad/gl.h>
#include"matrix.h"
#include"shader.h"
typedef struct{
    GLuint VBO;
    float r;
    float sx;
    float sy;
    float posx;
    float posy;
}spike;
spike* _ini_spike();
void s_draw(spike*s);
void s_matrix(shader*shaderS,matrix*m,spike*s);

