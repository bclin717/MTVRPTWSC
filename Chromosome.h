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

    void pushCustomers(Customer c);
    void setCustomerTo(Customer c, int position);

    void setNOD(int nod);

    void initialCustomers(int n);

    bool isExists(int cID);

private:
    bool ifInRoute(int num, std::vector<int> ids);
    std::vector<Customer> _customers;
    std::vector<int> _ids;
    float _fitnewssValue;
    float penalty(float TW, float lowerbound);

    int NumberOfDeterministicCustomers;

    double _wheelProbability;
};
