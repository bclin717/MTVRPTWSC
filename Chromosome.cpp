//
// Created by kevin on 2018/9/1.
//

#include <stdlib.h>
#include "Param.h"

Chromosome::Chromosome() {
    _wheelProbability = 1;
    _fitnewssValue = 0;
}

bool Chromosome::cmp(const Chromosome &c1, const Chromosome &c2) {
    return c1._fitnewssValue < c2._fitnewssValue;
}

Chromosome::Chromosome(Chromosome c, bool b, int nod) {
    vector<Customer> vc = c.getCustomers();
    _fitnewssValue = c.getFitnessValue();
    _wheelProbability = c.getWheelProbability();
    _customers.assign(vc.begin(), vc.end());
    this->NumberOfDeterministicCustomers = nod;
}

Chromosome::Chromosome(std::vector<Customer> &c, int nod) {
    _fitnewssValue = 0;
    _wheelProbability = 0;
    _customers.assign(c.begin(), c.end());

    for(unsigned int i = 1; i < _customers.size(); i++) {
        int j = static_cast<int>((rand() % (_customers.size() - 1)) + 1);
        Customer temp = _customers.at(i);
        _customers.at(i) = _customers.at(j);
        _customers.at(j) = temp;
    }

    _customers.at(0) = 0;
    this->NumberOfDeterministicCustomers = nod;
    _fitnewssValue = calculateFitnessValue();
}

void Chromosome::initialCustomers(int n) {
    for(int i = 0; i < n; i++) {
        _customers.emplace_back(Customer());
    }
}

bool Chromosome::ifInRoute(int num, vector<int> ids) {
    for (int id : ids) if(num == id) return true;
    return false;
}

float Chromosome::penalty(float TW, float lowerbound) {
    return (TW - lowerbound) / PenalizationFactor;
}

float Chromosome::calculateFitnessValue() {
    Car car[NumberOfVehicle];
    float COST = 0;
    float TW = 0;
    int LOAD = 0;
    int carCount = 0;
    int nowCustomer, preCustomer;
    car[carCount].route.push_back(0);

    for(unsigned int i = 1; i < _customers.size(); i++) {
        LOAD += _customers.at(i).getDemandQuantity();

        if (_customers.at(i).getID() >= NumberOfDeterministicCustomers) nowCustomer = _customers.at(i).getID() -
                                                                                      NumberOfDeterministicCustomers +
                                                                                      1;
        else nowCustomer = _customers.at(i).getID();

        if (_customers.at(i - 1).getID() >= NumberOfDeterministicCustomers) preCustomer = _customers.at(i - 1).getID() -
                                                                                          NumberOfDeterministicCustomers +
                                                                                          1;
        else preCustomer = _customers.at(i-1).getID();

        if(LOAD > CapacityOfVehicle) {
            COST += costMatrix[nowCustomer][0];
            car[++carCount].route.emplace_back(0);
            i--;
            LOAD = 0;
            continue;
        } else {
            TW = COST > _customers.at(i).getTimeWindow().getLowerBound() ? COST : _customers.at(i).getTimeWindow().getLowerBound();
            COST += costMatrix[preCustomer][nowCustomer] + _customers.at(i).getServiceTime();
            if (TW > _customers.at(i).getTimeWindow().getUpperBound())
                COST += penalty(TW, _customers.at(i).getTimeWindow().getUpperBound());
        }
    }
    _fitnewssValue = COST;
    return COST;
}


vector<Customer> Chromosome::getIDs() {
    for (auto &_customer : _customers)
        std::cout << _customer.getID() << " ";
    cout << "Fitness Value : " << _fitnewssValue << endl;
    return _customers;
}

float Chromosome::getFitnessValue() {
    return _fitnewssValue;
}

double Chromosome::getWheelProbability() {
    return _wheelProbability;
}

void Chromosome::setWheelProbability(double p) {
    _wheelProbability = p;
}

void Chromosome::setNOD(int nod) {
    this->NumberOfDeterministicCustomers = nod;
}

std::vector<Customer>& Chromosome::getCustomers() {
    return _customers;
}

void Chromosome::setCustomerTo(Customer c, int position) {
    _customers.at(static_cast<unsigned long>(position)) = Customer(c);
}

void Chromosome::pushCustomers(Customer c) {
    _customers.emplace_back(c);
}

bool Chromosome::isExists(int cID) {
    for (auto &_customer : _customers)
        if(_customer.getID() == cID) return true;
    return false;
}