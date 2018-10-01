//
// Created by kevin on 2018/8/13.
//

#include "Param.h"

Customer::Customer() {
    initialParams();
}

Customer::Customer(int id) {
    initialParams();
    _id = id;
}

Customer::Customer(int id, int up, int lp) {
    initialParams();
    _id = id;
    _timeWindow.setLowerBound(lp);
    _timeWindow.setUpperBound(up);
}

Customer::Customer(const Customer &_c) {
    _id = _c._id;
    _demandQuantity = _c._demandQuantity;
    _serviceTime = _c._serviceTime;
    _probability = _c._probability;
    _timeWindow = _c._timeWindow;
}

void Customer::initialParams() {
    _id = -1;
    _demandQuantity = 1;
    _probability = 1;
    _serviceTime = serviceTime;
    _x = 0;
    _y = 0;
    _t = -1;
    _timeWindow = TimeWindow();
}

bool Customer::cmp(const Customer &c1, const Customer &c2) {
    return c1._probability > c2._probability;
}

int Customer::getID() {
    return _id;
}

void Customer::setID(int id) {
    _id = id;
}

int Customer::getDemandQuantity() {
    return _demandQuantity;
}

void Customer::setDemandQuantity(int dq) {
    _demandQuantity = dq;
}

int Customer::getServiceTime() {
    return _serviceTime;
}

void Customer::setServiceTime(int st) {
    _serviceTime = st;
}

int Customer::getT() {
    return _t;
}

void Customer::setT(int t) {
    _t = t;
}

float Customer::getProbability() {
    return _probability;
}

void Customer::setProbability(float p) {
    _probability = p;
}

TimeWindow Customer::getTimeWindow() {
    return TimeWindow(_timeWindow);
}

void Customer::setTimeWindow(TimeWindow tw) {
    _timeWindow = TimeWindow(tw);
}

