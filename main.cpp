#include "Param.h"

vector<Customer> dCustomers;
vector<Customer> sCustomers;

vector<Customer> L1;
vector<Customer> L2;


void algorithm1() {

}

Route algorithm2() {
    // TODO algorithm2
    return Route();
}

Route algorithm3() {
    while (L2.size() != 0) {
        Customer c = Customer(L2.at(0));
        L2.erase(L2.begin());

        // TODO algorithm3
        /*algorithm3
            ...
            ...
            ...
        */
    }
    return Route();
}

void algorithm4() {

}



int main() {

    // Genrating customers
    for (int i = 0; i < NumberOfDeterministicCustomers + 1; i++)
        dCustomers.push_back(Customer(i));
    for (int i = NumberOfDeterministicCustomers + 1;
         i < NumberOfStochasticCustomers + NumberOfDeterministicCustomers + 2; i++)
        sCustomers.push_back(Customer(i));

    // Generating probability of stochastic customers randomly
    srand(time(NULL));
    float p;
    for (int i = 0; i < NumberOfStochasticCustomers; i++) {
        p = (float) rand() / (RAND_MAX + 1.0);
        sCustomers.at(i).setProbability(p);
    }

    // Classify high probability stochastic customers and low probability stochastic customers

    // Put deterministic customers into L1
    for (int i = 0; i < NumberOfDeterministicCustomers + 1; i++) {
        L1.push_back(Customer(dCustomers.at(i)));
    }

    // Classified by probability
    for (int i = 0; i < NumberOfStochasticCustomers; i++) {
        if (sCustomers.at(i).getProbability() >= PriorityThresholdValue)
            L1.push_back(Customer(sCustomers.at(i)));
        else
            L2.push_back(Customer(sCustomers.at(i)));
    }

    // Sorting
    sort(L2.begin(), L2.end(), Customer::cmp);

    Route S = algorithm2();

    Route S2 = algorithm3();

    return 0;
}