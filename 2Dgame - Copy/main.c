#include<glad/gl.h>
#include<windows.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"shader.h"
#include"box.h"
#include"matrix.h"
#include"my_math.h"
#include"platform.h"
#include"physics.h"
#include"delta.h"
#include"chunk.h"
#include"spike.h"
#include"procu_spike.h"
/*GLOBAL VARAIBLES*/
#define WIDTH 1000
#define HEIGHT 600
#define worldsx 1.0
#define worldsy 1.0
typedef BOOL (WINAPI* SwapIntervalProc)(int interval);
SwapIntervalProc swapinterval = NULL;
bool running = true;
bool jump = false;
MSG msg;
HGLRC glrc;
HDC hdc;
//This is the world matrix dont touch this or you will move the 2D world!!! >:(
void FinalMatrixStuff(shader*s,box*b){
    matrix*T=translation(-b->posx,-b->posy);
    matrix*R=rotation(0.0f);
    matrix*S=scale(worldsx,worldsy);
    matrix*RS=multiply(R,S);
    matrix*fresult=multiply(T,RS);
    glUniformMatrix3fv(s->uMatrix,1,GL_TRUE,fresult->matt);
    free(T);
    free(R);
    free(S);
    free(RS);
    free(fresult);
}
float reposx(){
    float getX=GetSystemMetrics(SM_CXSCREEN);
    float newX=(getX-WIDTH)/(float)2.0f;
    return newX;
}
float reposy(){
    float getY=GetSystemMetrics(SM_CYSCREEN);
    float newY=(getY-HEIGHT)/(float)2.0f;;
    return newY;
}
void fixglViewport(float w,float h){
    glViewport(0,0,w,h);
}
void _init_vsync(){
    swapinterval = (SwapIntervalProc)wglGetProcAddress("wglSwapIntervalEXT");
    if(swapinterval!=NULL){
        swapinterval(1);
    }
    else{
        printf("vsync not supported!\n");
    }
}
void _init_opengl(HWND hwnd){ /* this one generates or load openGL on my program */
    hdc=(GetDC(hwnd));
    PIXELFORMATDESCRIPTOR gll={0};
    gll.nSize=sizeof(PIXELFORMATDESCRIPTOR);
    gll.nVersion=1;
    gll.dwFlags=PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
    gll.iPixelType=PFD_TYPE_RGBA;
    gll.cColorBits=32;
    gll.cDepthBits=24;
    gll.cStencilBits=8;
    gll.iLayerType=PFD_MAIN_PLANE;
    int format=ChoosePixelFormat(hdc,&gll);
    SetPixelFormat(hdc,format,&gll);
    glrc=wglCreateContext(hdc);
    wglMakeCurrent(hdc,glrc);
    gladLoaderLoadGL();
}
LRESULT CALLBACK windowproc(HWND hwnd,UINT umsg,WPARAM wparam,LPARAM lparam){
    if(umsg==WM_SIZE){
        float newvX=LOWORD(lparam);
        float newvY=HIWORD(lparam);
        if(newvX > 0 && newvY > 0 && wglGetCurrentContext() != NULL){
            fixglViewport(newvX,newvY);
        }
    }
    if(umsg==WM_KEYDOWN){
        if(wparam==VK_SPACE){
            jump = true;
        }
        if(wparam==VK_ESCAPE){
            running = false;
            DestroyWindow(hwnd);
            exit(0);
        }
    }
    return DefWindowProc(hwnd,umsg,wparam,lparam);
}
void _triggerjumpresult(box*b){
    if(jump&&b->onground){
        jumpplayer(b);
        b->onground = false;
    } jump = false;
}
void _Initialize_window(){
    srand((unsigned int)time(NULL));
    WNDCLASS wc={0};
    wc.lpfnWndProc=windowproc;
    wc.lpszClassName="mygame";
    wc.hInstance=GetModuleHandleA(NULL);
    wc.hbrBackground=(HBRUSH)(BLACK_BRUSH);
    RegisterClass(&wc);
    HWND mainwindow=CreateWindowExA(0,"mygame","2Dgame",WS_OVERLAPPEDWINDOW,reposx(),reposy(),WIDTH,HEIGHT,NULL,NULL,GetModuleHandle(NULL),NULL);
    _init_opengl(mainwindow);
    _init_vsync();
    ShowWindow(mainwindow,SW_SHOW);
    shader*s=_ini_shader();
    box*b=_ini_box();
    platform*p=ini_platform();
    matrix*m=identity();
    delta*d=ini_delta();
    chunk*c=_ini_chunk();
    spike*s_spike=_ini_spike();
    procu_spike*s_ps=_ini_procu_spikes();
    useprogram(s);
    storespikes(s_ps,b);
    while(running){
        while(PeekMessageA(&msg,mainwindow,0,0,PM_REMOVE)){   
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        glClearColor(0.41f,0.59f,0.71f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        drawduppedspikes(s_ps,s,m);

        _triggerjumpresult(b);
        generatechunk(b,c,m,s);
        _moveauto(b,d);
        collision(b,c);
        deltatime(d);
        FinalMatrixStuff(s,b);
        glUniform4f(s->uColor,1.0f,0.0f,0.0f,1.0f);
        s_matrix(s,m,s_spike);
        s_draw(s_spike);
        p_matrix(m,s,p);
        glUniform4f(s->uColor,0.0f,1.0f,0.0f,1.0f);
        p_draw(s,m,p);
        b_ownmatrix(b,s,m);
        glUniform4f(s->uColor,1.0f,1.0f,1.0f,1.0f);
        b_draw(b);
        objectgravity(b,d);     
        FrameRatePerSecond(d);
        collisionHit(b,s_ps);
        SwapBuffers(hdc);
    }
}
int main(int args,char* argv[]){
    _Initialize_window();
    return 0;
}
