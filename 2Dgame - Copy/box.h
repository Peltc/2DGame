#pragma once
#include<glad/gl.h>
#include"shader.h"
#include"matrix.h"
#include"delta.h"
#include<stdbool.h>
typedef struct{
    float speed;
    GLuint vbo,vao;
    float r;
    float sx;
    float sy;
    float vx;
    float vy;
    float posx;
    float posy;
    bool onground;
}box;
box* _ini_box();
void b_draw(box*b);
void b_ownmatrix(box*b,shader*s,matrix*m);
void _moveauto(box*b,delta*d);
void jumpplayer(box*b);



