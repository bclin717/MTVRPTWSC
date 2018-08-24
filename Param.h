//
// Created by kevin on 2018/8/13.
//

#ifndef MTVRPTWSC_PARAM_H
#define MTVRPTWSC_PARAM_H

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

#include "Route.h"
#include "Customer.h"
#include "TimeWindow.h"
#include "Car.h"
#include "Scenario.h"

using namespace std;

static const int CurrentBestValue = 9999999;
static const float PriorityThresholdValue = 0.5;
static vector<Scenario> scenarios;

static const int NumberOfDeterministicCustomers = 15;
static const int NumberOfStochasticCustomers = 15;

const int distanceMatrix[NumberOfDeterministicCustomers][NumberOfDeterministicCustomers] = {

};

#endif //MTVRPTWSC_PARAM_H
