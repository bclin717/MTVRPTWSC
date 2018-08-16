//
// Created by kevin on 2018/8/13.
//

#include "Param.h"

int Customer::getID() { return _id; }

void Customer::setID(int id) { _id = id; }

int Customer::getDemandQuantity() { return _demandQuantity; }

void Customer::setDemandQuantity(int dq) { _demandQuantity = dq; }

int Customer::getServiceTime() { return _serviceTime; }

void Customer::setServiceTime(int st) { _serviceTime = st; }

int Customer::getT() { return _t; }

void Customer::setT(int t) { _t = t; }

float Customer::getProbability() { return _probability; }

void Customer::setProbability(float p) { _probability = p; }

TimeWindow Customer::getTimeWindow() { return _timeWindow; }