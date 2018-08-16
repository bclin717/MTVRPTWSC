//
// Created by kevin on 2018/8/13.
//

#include "Param.h"

Route::Route() {}

Route::Route(const Route &r) {
    _customerIDs = r._customerIDs;
    _time = r._time;
    _overhead = r._overhead;
}

vector<int> Route::getCustomerIDs() { return _customerIDs; }

vector<int> Route::getTime() { return _time; }

int Route::getOverhead() { return _overhead; }

void Route::setOverhead(int overhead) { _overhead = overhead; }

