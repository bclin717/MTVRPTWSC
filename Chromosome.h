//
// Created by kevin on 2018/9/1.
//

#include "Param.h"

class Chromosome {
public:
    Chromosome(std::vector<Customer>& c);

    void ClarkeAndWright();

    std::vector<Customer> getIDs();

    void calculateFitnessValue();



private:
    bool ifInRoute(int num, std::vector<int> ids);
    std::vector<Customer> _customers;
    std::vector<int> _ids;
    float _fitnewssValue;

};
