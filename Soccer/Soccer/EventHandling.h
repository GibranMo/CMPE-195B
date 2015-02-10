#ifndef EventHandling_H

#define EventHandling_H

#include "Definitions.h"

void initEventQueue(void);

void queueEvent(Event* ev);

void updateEventQueue(void);


#endif