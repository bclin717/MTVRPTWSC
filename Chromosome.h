//
// Created by kevin on 2018/9/1.
//

#include "Param.h"

class Chromosome {
public:
    Chromosome(std::vector<Customer>& c);

    Chromosome(Chromosome c, bool b);
    Chromosome();


    void ClarkeAndWright();

    std::vector<Customer> getIDs();

    float calculateFitnessValue();

    float getFitnessValue();

    void setWheelProbability(double p);

    double getWheelProbability();

    std::vector<Customer> getCustomers();


private:
    bool ifInRoute(int num, std::vector<int> ids);
    std::vector<Customer> _customers;
    std::vector<int> _ids;
    float _fitnewssValue;
    float penalty(float TW, float lowerbound);

    double _wheelProbability;
};
