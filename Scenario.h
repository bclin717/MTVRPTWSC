//
// Created by kevin on 2018/8/16.
//

#ifndef MTVRPTWSC_SCENARIO_H
#define MTVRPTWSC_SCENARIO_H

#include <vector>

class Scenario {
public:
    std::vector<int> getStochasticCustomerIDs();

    float getProbabilityOfOccurrence();

    void setProbabilityOfOccurrence(float p);

private:
    std::vector<int> _stochasticCustomerIDs;
    float _probabilityOfOccurrence;
};

#endif //MTVRPTWSC_SCENARIO_H
