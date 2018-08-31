//
// Created by kevin on 2018/8/16.
//

#include "Scenario.h"

std::vector<int> Scenario::getStochasticCustomerIDs() {
    return _stochasticCustomerIDs;
}

float Scenario::getProbabilityOfOccurrence() {
    return _probabilityOfOccurrence;
}

void Scenario::setProbabilityOfOccurrence(float p) {
    _probabilityOfOccurrence = p;
}