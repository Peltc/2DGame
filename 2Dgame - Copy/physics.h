#pragma once
#include"box.h"
#include"delta.h"
#include"platform.h"
#include"chunk.h"
#include"procu_spike.h"
void objectgravity(box*b,delta*d);
void collision(box*b,chunk*c);
void collisionHit(box* b,procu_spike* s_ps);








