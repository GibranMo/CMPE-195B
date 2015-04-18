//
//  EventHandler.h
//  Soccer Simulation
//
//  Created by Carlos Toledo on 2/10/15.
//  Copyright (c) 2015 Carlos Toledo. All rights reserved.
//

#ifndef __Soccer_Simulation__EventHandler__
#define __Soccer_Simulation__EventHandler__

enum Event_Type{
    ET_BALL_TOPBOTTOM_COLLISION,
    
};

struct Event{
    Event_Type et;
    //    ActorData* actor1;
    //    ActorData* actor2;
};

void initEventQueue(void);

void queueEvent(Event* ev);

void updateEventQueue(void);

#endif /* defined(__Soccer_Simulation__EventHandler__) */

