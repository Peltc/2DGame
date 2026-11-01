#pragma once
#include<glad/gl.h>
typedef struct{
    GLuint program;
    GLint _fmSource;
    GLint  _vtSource;
    GLuint uMatrix,uModel,uColor;
}shader;
shader*_ini_shader();
void useprogram(shader*s);
void _fragErrorChecker(shader*s);
void _vertexErrorChecker(shader*s);


