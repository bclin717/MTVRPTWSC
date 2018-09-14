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

    //Roulette Wheel Selection
    //Calculate probabilities of all Chromosome
    double total = 0;
    for (int i = 0; i < NumberOfChromosome; i++)
        total += chromosomes.at(i).getFitnessValue();
    chromosomes.at(0).setWheelProbability(chromosomes.at(0).getFitnessValue() / total);
    for (int i = 1; i < NumberOfChromosome; i++)
        chromosomes.at(i).setWheelProbability(
                (chromosomes.at(i).getFitnessValue() / total) + chromosomes.at(i - 1).getWheelProbability());

    //Select
//    Chromosome parent[2], child[2] = {Chromosome(), Chromosome()};
//    int id[2] = {-1, -1};
//    while (id[0] == id[1]) {
//        for (int i = 0; i < 2; i++) {
//            double p = static_cast<float>((double) rand() / (RAND_MAX + 1.0));
//            for (int i2 = 0; i2 < NumberOfChromosome - 1; i2++) {
//                if (p > chromosomes.at(i2).getWheelProbability() && p < chromosomes.at(i2 + 1).getWheelProbability()) {
//                    parent[i] = chromosomes.at(i2);
//                    id[i] = i2;
//                    break;
//                }
//            }
//        }
//    }
//    int size = static_cast<int>(parent[0].getCustomers().size());
//    int cutBegin = -1, cutEnd = -1;
//    do {
//        cutBegin = static_cast<int>(static_cast<float>( rand() % size));
//        cutEnd = static_cast<int>(static_cast<float>( rand() % size));
//    } while(cutBegin == cutEnd);

//    for(int i = 0; i < cutBegin; i++) {
//        child[0].getCustomers().emplace_back(Customer(parent[1].getCustomers().at(i)));
//        child[1].getCustomers().emplace_back(Customer(parent[0].getCustomers().at(i)));
//    }
//
//    for(int i = cutBegin; i < cutEnd + 1; i++) {
//        child[0].getCustomers().emplace_back(Customer(parent[0].getCustomers().at(i)));
//        child[1].getCustomers().emplace_back(Customer(parent[1].getCustomers().at(i)));
//    }

//    for(int i = cutEnd + 1; i < size; i++) {
//        child[0].getCustomers().emplace_back(Customer(parent[1].getCustomers().at(i)));
//        child[1].getCustomers().emplace_back(Customer(parent[0].getCustomers().at(i)));
//    }




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
    for (int i = 0; i < NumberOfDeterministicCustomers; i++)
        dCustomers.emplace_back(i);
    for (int i = NumberOfDeterministicCustomers;
         i < NumberOfStochasticCustomers + NumberOfDeterministicCustomers - 1; i++)
        sCustomers.emplace_back(i);

    // Generating probability of stochastic customers randomly
    srand(static_cast<unsigned int>(time(nullptr)));
    float p;
    for (int i = 0; i < NumberOfStochasticCustomers - 1; i++) {
        p = static_cast<float>((float) rand() / (RAND_MAX + 1.0));
        sCustomers.at(i).setProbability(p);
    }

    // Classify high probability stochastic customers and low probability stochastic customers

    // Put deterministic customers into L1
    for (int i = 0; i < NumberOfDeterministicCustomers; i++) {
        L1.emplace_back(dCustomers.at(i));
    }

    // Classified by probability
    for (int i = 0; i < NumberOfStochasticCustomers - 1; i++) {
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