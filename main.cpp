#include "Param.h"

vector<Customer> dCustomers;
vector<Customer> sCustomers;

vector<Customer> L1;
vector<Customer> L2;

void algorithm1() {

}

void adsplit() {

}

Route algorithm2() {
    vector<Chromosome> chromosomes;
    for(int i = 0; i < NumberOfChromosome; i++)
        chromosomes.emplace_back(Chromosome(L1));

    for(int i = 0; i < NumberOfChromosome; i++) {
        chromosomes.at(i).getIDs();
    }


    //TODO algorithm2

    return Route();
}

Route algorithm3() {
    while (!L2.empty()) {
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
        dCustomers.emplace_back(i);
    for (int i = NumberOfDeterministicCustomers + 1;
         i < NumberOfStochasticCustomers + NumberOfDeterministicCustomers + 2; i++)
        sCustomers.emplace_back(i);

    // Generating probability of stochastic customers randomly
    srand(static_cast<unsigned int>(time(nullptr)));
    float p;
    for (int i = 0; i < NumberOfStochasticCustomers; i++) {
        p = static_cast<float>((float) rand() / (RAND_MAX + 1.0));
        sCustomers.at(i).setProbability(p);
    }

    // Classify high probability stochastic customers and low probability stochastic customers

    // Put deterministic customers into L1
    for (int i = 0; i < NumberOfDeterministicCustomers + 1; i++) {
        L1.emplace_back(dCustomers.at(i));
    }

    // Classified by probability
    for (int i = 0; i < NumberOfStochasticCustomers; i++) {
        if (sCustomers.at(i).getProbability() >= PriorityThresholdValue)
            L1.emplace_back(sCustomers.at(i));
        else
            L2.emplace_back(sCustomers.at(i));
    }

    // Sorting
    sort(L2.begin(), L2.end(), Customer::cmp);

    // Use Hybrid Generation Algorithm to generate a route.
    Route S = algorithm2();


    Route S2 = algorithm3();

    return 0;
}