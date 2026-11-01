#include<glad/gl.h>
#include"shader.h"
#include<stdlib.h>
#include<stdio.h>
char loginfo[512];
int success;
shader* _ini_shader(){
    shader* s = malloc(sizeof(shader));
    const char*fmShader=
        "#version 120\n"
        "uniform vec4 uColor;\n"
        "void main(){\n"
        "   gl_FragColor=uColor;\n"
        "}\n";
    const char*vtshader=
        "#version 120\n"
        "attribute vec3 aMainPos;\n"
        "uniform mat3 uMatrix;\n"
        "uniform mat3 uModel;\n"
        "void main(){\n"
        "   vec3 pos=uMatrix*uModel*vec3(aMainPos.xy,1.0);\n"
        "   gl_Position=vec4(pos.xy,0.0,1.0);\n"
        "}\n";
    s->_fmSource=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s->_fmSource,1,&fmShader,0);
    glCompileShader(s->_fmSource);
    s->_vtSource=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s->_vtSource,1,&vtshader,0);
    glCompileShader(s->_vtSource);
    s->program=glCreateProgram();
    // error checker here
    //i forgot the syntax and keywords but the patter n and what do i need to do is really i know is that okay?
    _fragErrorChecker(s);
    _vertexErrorChecker(s);
    glBindAttribLocation(s->program,0,"aMainPos");
    glAttachShader(s->program,s->_fmSource);
    glAttachShader(s->program,s->_vtSource);
    glLinkProgram(s->program);
    s->uColor=glGetUniformLocation(s->program,"uColor");
    s->uMatrix=glGetUniformLocation(s->program,"uMatrix");
    s->uModel=glGetUniformLocation(s->program,"uModel");
    return s;
}
void useprogram(shader*s){
    glUseProgram(s->program);        
}
void _fragErrorChecker(shader*s){   
    glGetShaderiv(s->_fmSource,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(s->_fmSource,512,NULL,loginfo);
        printf("Error Fragment shader: %s\n",loginfo);
    }
}
void _vertexErrorChecker(shader*s){
    glGetShaderiv(s->_vtSource,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(s->_vtSource,512,NULL,loginfo);
        printf("Error Vertex shader: %s\n",loginfo);
    }
}



