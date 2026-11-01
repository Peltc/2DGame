#include"spike.h"
#include"procu_spike.h"
#include"shader.h"
#include"box.h"
#include"matrix.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

/* notes info:
 * posy spikes should be go on -0.40f
*/
procu_spike* _ini_procu_spikes(){
    procu_spike* s_ps = malloc(sizeof(procu_spike));
    if(s_ps==NULL){
        return NULL;
    }
    s_ps->spikelimit = 100;
    for(int i=0;i<100;i++){
        s_ps->dupspike[i] = NULL;
    }
    return s_ps;
}
unsigned int randomintgen(){
    unsigned int _d = rand() % 10;
    return _d;
}
float randomX(int index,box* b){
    float resultofthemath = b->posx+randomintgen()+(index*1.0f);
    return resultofthemath;
}
void storespikes(procu_spike*s_ps,box*b){
    if(s_ps==NULL){
        printf("s_ps is missing!\n");
        return;
    }
    for(int i=0;i<s_ps->spikelimit;i+=1){
        s_ps->dupspike[i] = _ini_spike();
        if(s_ps->dupspike[i] == NULL){
            continue;
        }
        if(s_ps==NULL){
            printf("! failed to load or spawn janky spikes!\n");
            free(s_ps);
            return;
        }

        s_ps->dupspike[i]->posx = randomX(i,b);
        s_ps->dupspike[i]->posy = -0.400f;
        printf("spike posx: %f\n",s_ps->dupspike[i]->posx);
    }
}
void drawduppedspikes(procu_spike*s_ps,shader*s,matrix*m){
    for(int i=0;i<s_ps->spikelimit;i+=1){
        if(s_ps->dupspike[i] == NULL){
            continue;
        }
        if(s_ps==NULL||s==NULL||m==NULL){
            return;
        }
        glUniform4f(s->uColor,1.0,0.0,0.0,1.0);
        s_matrix(s,m,s_ps->dupspike[i]);
        s_draw(s_ps->dupspike[i]);
    }
}
void scorecounter(){


}






