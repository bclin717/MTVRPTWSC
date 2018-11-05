//
// Created by kevin on 2018/8/16.
//

#ifndef MTVRPTWSC_CAR_H
#define MTVRPTWSC_CAR_H


#include "Param.h"

class Car {
public:
    Car(std::vector<std::vector<float>> t, std::vector<int> l, std::vector<int> u, std::vector<int> l2, std::vector<int> u2);
    std::vector<int> route;
    std::vector<int> times;
    int startTime;
    void addNode(int node);
    void clearRoute();
    void run();
    void print();
    void setRoute(Route r);

    void setTimeMatrix(std::vector<std::vector<float>> t);
    void setLbound(std::vector<int> l);
    void setUbound(std::vector<int> u);
    void setLbound2(std::vector<int> l2);
    void setUbound2(std::vector<int> u2);

    std::vector<std::vector<float>> timeMatrix;
    std::vector<int> Lbound;
    std::vector<int> Ubound;
    std::vector<int> Lbound2;
    std::vector<int> Ubound2;
};


#endif //MTVRPTWSC_CAR_H
