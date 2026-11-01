#pragma once
#include"box.h"
#include"spike.h"
#include"matrix.h"
#define ALLSPIKES 100
typedef struct{
    //adding 100 array stuff here so i can store spikes and track them
    int spikelimit;    
    
    spike* dupspike[ALLSPIKES];
} procu_spike;
void storespikes(procu_spike*s_ps,box*b);
procu_spike* _ini_procu_spikes();
void drawduppedspikes(procu_spike*s_ps,shader*s,matrix*m);
float randomX(int index,box* b);
unsigned int randomintgen();
void scorecounter();





