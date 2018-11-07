//
// Created by kevin on 2018/8/13.
//

#include "Param.h"

Route::Route() {}

Route::Route(const Route &r) {
    _customerIDs = r._customerIDs;
    _time = r._time;
}

vector<int> Route::getCustomerIDs() {
    return _customerIDs;
}

vector<int> Route::getTime() {
    return _time;
}

int Route::getID() {
    return _id;
}

void Route::setID(int id) {
    _id = id;
}

void Route::addNode(int n) {
    _customerIDs.emplace_back(n);
}
