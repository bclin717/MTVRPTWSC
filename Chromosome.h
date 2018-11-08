//
// Created by kevin on 2018/9/1.
//

#include "Param.h"

class Chromosome {
public:
    Chromosome(std::vector<Customer> &c, int nod);

    Chromosome(Chromosome c, bool b, int nod);
    Chromosome();

    static bool cmp(const Chromosome &c1, const Chromosome &c2);


    std::vector<Customer> getIDs();

    float calculateFitnessValue();

    float getFitnessValue();

    void setWheelProbability(double p);
    double getWheelProbability();

    std::vector<Customer>& getCustomers();

    void setNOD(int nod);

    bool isExists(int cID);

private:
    std::vector<Customer> _customers;
    float _fitnewssValue;
    float penalty(float TW, float lowerbound);

    int NumberOfDeterministicCustomers;

    double _wheelProbability;
};
