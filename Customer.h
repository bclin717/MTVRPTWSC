//
// Created by kevin on 2018/8/13.
//

#ifndef MTVRPTWSC_CUSTOMER_H
#define MTVRPTWSC_CUSTOMER_H


#include "TimeWindow.h"

class Customer {
private:
    int x;
    int y;
    int demandQuantity;
    int serviceTime;
    TimeWindow timeWindow;
};


#endif //MTVRPTWSC_CUSTOMER_H
