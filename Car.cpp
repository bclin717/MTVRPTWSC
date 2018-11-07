//
// Created by kevin on 2018/8/16.
//

#include "Param.h"

Car::Car(std::vector<std::vector<float>> t, std::vector<int> l, std::vector<int> u, std::vector<int> l2,
         std::vector<int> u2) {
    setTimeMatrix(t);
    setLbound(l);
    setLbound2(l2);
    setUbound2(u2);
    setUbound(u);
    NumberOfDeterministicCustomers = Lbound.size() + 1;
    route.clear();
    startTime = 0;
}
void Car::addNode(int node) {
    route.emplace_back(node);
}

void Car::clearRoute() {
    route.clear();
    times.clear();
}

void Car::run() {

    for(int i = 1; i < route.size(); i++) {
        int nowPoint = route[i] >= NumberOfDeterministicCustomers ? route[i]-NumberOfDeterministicCustomers+1 : route[i];
        int prePoint = route[i-1] >= NumberOfDeterministicCustomers ? route[i-1]-NumberOfDeterministicCustomers+1 : route[i-1];

        startTime += timeMatrix[prePoint][nowPoint];

        if(route[i] >= NumberOfDeterministicCustomers) {
            int temp = route[i] - NumberOfDeterministicCustomers + 1;
            if(startTime < Lbound2[temp-1]) {
                startTime = Lbound2[temp-1];
            }
        } else {
            int temp = route[i];
            if(startTime < Lbound[temp-1]) {
                startTime = Lbound[temp-1];
            }
        }
        startTime += serviceTime;
        times.emplace_back(startTime);
    }
}

void Car::print() {
    for(int i = 0; i < route.size() - 1; i++) {
        cout << route[i] << " (" << times[i] << ") ";
    }
    cout << route[route.size()-1];
    cout << endl;
}

void Car::setTimeMatrix(std::vector<std::vector<float>> t) {
    timeMatrix = t;
}

void Car::setLbound(std::vector<int> l) {
    Lbound = l;
}

void Car::setLbound2(std::vector<int> l2) {
    Lbound2 = l2;
}

void Car::setUbound(std::vector<int> u) {
    Ubound = u;
}

void Car::setUbound2(std::vector<int> u2) {
    Ubound2 = u2;
}

void Car::setRoute(Route r) {
    for(int i = 0; i < r._customerIDs.size(); i++) {
        route.emplace_back(r._customerIDs[i]);
    }
}