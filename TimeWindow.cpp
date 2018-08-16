//
// Created by kevin on 2018/8/13.
//

#include "Param.h"

int TimeWindow::getLowerBound() { return _lowerBound; }

void TimeWindow::setLowerBound(int lb) { _lowerBound = lb; }

int TimeWindow::getUpperBound() { return _upperBound; }

void TimeWindow::setUpperBound(int ub) { _upperBound = ub; }