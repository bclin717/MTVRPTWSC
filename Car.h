//
// Created by kevin on 2018/8/16.
//

#ifndef MTVRPTWSC_CAR_H
#define MTVRPTWSC_CAR_H


#include "Route.h"

class Car {
public:
    Route getRoute();

    void setRoute(Route r);

private:
    Route _route;
};


#endif //MTVRPTWSC_CAR_H
