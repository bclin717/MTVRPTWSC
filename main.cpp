#include "Param.h"

static vector<Customer> dCustomers;
static vector<Customer> sCustomers;

static vector<Customer> L1;
static vector<Customer> L2;

static vector<Chromosome> *chromosomes = new vector<Chromosome>;
static Chromosome solution;

static vector<Car> cars;
static vector<Route> routes;

extern std::vector<std::vector<float>> costMatrix = vector<vector<float>>(0); // travel cost matrix.txt
extern std::vector<std::vector<float>> timeMatrix = vector<vector<float>>(0); // travel time matrix.txt

static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
static mt19937 generator{seed};
static uniform_real_distribution<float> unif(0.0, 1.0);

void algorithm2() {
    //Roulette Wheel Selection
    //Calculate probabilities of all Chromosome
    static double total = 0;
    static int i;
    for (i = 0; i < NumberOfChromosome; i++)
        total += chromosomes->at(i).getFitnessValue();

    chromosomes->at(0).setWheelProbability(0);

    for (i = 1; i < NumberOfChromosome; i++)
        chromosomes->at(i).setWheelProbability(
                (chromosomes->at(i).getFitnessValue() / total) + chromosomes->at(i).getWheelProbability());

    //Select
    double p;
    static Chromosome *parent = new Chromosome[2];
    parent[0] = Chromosome();
    parent[1] = Chromosome();

    static Chromosome *child = new Chromosome[2];
    child[0] = Chromosome();
    child[1] = Chromosome();

    for (int i = 0; i < 2; i++) {
        parent[i].setNOD(NumberOfDeterministicCustomers);
        child[i].setNOD(NumberOfDeterministicCustomers);
    }

    int id[2] = {-1, -1};
    for (i = 0; i < 2; i++) {
        p = unif(generator);
        for (int i2 = 0; i2 < NumberOfChromosome; i2++) {
            if (p > chromosomes->at(static_cast<unsigned int>(i2)).getWheelProbability()) {
                parent[i] = Chromosome(chromosomes->at(static_cast<unsigned int>(i2)), true,
                                       NumberOfDeterministicCustomers);
                id[i] = i2;
                break;
            }
        }

        if (parent[i].getCustomers().size() <= 1) {
            parent[i] = Chromosome(chromosomes->at(static_cast<unsigned int>(0)), true,
                                   NumberOfDeterministicCustomers);
            id[i] = 0;
        }
    }

    assert(parent[0].getCustomers().size() == parent[1].getCustomers().size());

    static int size = parent[0].getCustomers().size();
    uniform_real_distribution<float> unif_int(1, size - 1);
    static int cutBegin = 0, cutEnd = -1;
    cutEnd = (int) unif_int(generator);

    for (i = 0; i < 2; i++) {
        for (int i2 = cutBegin; i2 < cutEnd; i2++) {
            child[i].getCustomers().emplace_back(parent[i].getCustomers().at(i2));
        }
    }

    for (i = cutEnd; i < parent[0].getCustomers().size(); i++) {
        if (!child[1].isExists(parent[0].getCustomers().at(i).getID()))
            child[1].getCustomers().emplace_back(parent[0].getCustomers().at(i));
    }

    for (i = cutEnd; i < parent[1].getCustomers().size(); i++) {
        if (!child[0].isExists(parent[1].getCustomers().at(i).getID()))
            child[0].getCustomers().emplace_back(parent[1].getCustomers().at(i));
    }

    for (i = 0; i < 2; i++) {
        child[i].calculateFitnessValue();
        chromosomes->emplace_back(child[i]);
    }

    sort(chromosomes->begin(), chromosomes->end(), Chromosome::cmp);

    for (int i = 0; i < 2; i++)
        chromosomes->pop_back();
}

void algorithm3() {
    int minPos, minFitV;
    bool flag = false;
    solution.setNOD(NumberOfDeterministicCustomers);
    while (!L2.empty()) {
        Customer c = Customer(L2.at(0));
        L2.erase(L2.begin());
        minPos = 1;
        minFitV = 9999999;
        flag = false;
        for (int i = 1; i < solution.getCustomers().size(); i++) {
            if (flag) {
                solution.getCustomers().insert(solution.getCustomers().begin() + i, Customer(c));
                solution.calculateFitnessValue();
                if (solution.getFitnessValue() <= minFitV) {
                    minFitV = static_cast<int>(solution.getFitnessValue());
                    minPos = i;
                }
                solution.getCustomers().erase(solution.getCustomers().begin() + i);
            }
            if (solution.getCustomers().at(i).getID() == c.getID() - NumberOfDeterministicCustomers + 1) {
                flag = true;
                i++;
            }
        }

        solution.getCustomers().insert(solution.getCustomers().begin() + minPos, c);
    }
//    chromosome.getCustomers().emplace_back(chromosome.getCustomers().at(1));
    solution.getCustomers().erase(solution.getCustomers().begin() + 1);
    solution.calculateFitnessValue();
}

void readFiles() {
    float finput;
    int input;
    char c;

    //Read ai.txt
    FILE *ai;
    if ((ai = fopen("ai.txt", "r")) == nullptr) {
        cout << "ai.txt does not exist!!" << endl;
        exit(1);
    }

    while (fscanf(ai, "%d%c", &input, &c) != EOF)
        Lbound.emplace_back(input);
    fclose(ai);

    //Read bi.txt
    FILE *bi;
    if ((bi = fopen("bi.txt", "r")) == nullptr) {
        cout << "bi.txt does not exist!!" << endl;
        exit(1);
    }

    while (fscanf(bi, "%d%c", &input, &c) != EOF)
        Ubound.emplace_back(input);
    fclose(bi);

    //Read ai2.txt
    FILE *ai2;
    if ((ai2 = fopen("ai2.txt", "r")) == nullptr) {
        cout << "ai2.txt does not exist!!" << endl;
        exit(1);
    }

    while (fscanf(ai2, "%d%c", &input, &c) != EOF)
        Lbound2.emplace_back(input);
    fclose(ai2);

    //Read bi2.txt
    FILE *bi2;
    if ((bi2 = fopen("bi2.txt", "r")) == nullptr) {
        cout << "bi2.txt does not exist!!" << endl;
        exit(1);
    }

    while (fscanf(bi2, "%d%c", &input, &c) != EOF)
        Ubound2.emplace_back(input);
    fclose(bi2);


    //Read travel cost matrix.txt
    FILE *tcm;
    if ((tcm = fopen("travel cost matrix.txt", "r")) == nullptr) {
        cout << "travel cost matrix.txt does not exist!!" << endl;
        exit(1);
    }
    costMatrix.emplace_back(vector<float>());
    for (int i = 0; fscanf(tcm, "%f%c", &finput, &c) != EOF;) {
        if (c == '\n') {
            costMatrix.at(i).emplace_back(finput);
            costMatrix.emplace_back(vector<float>());
            i++;
            continue;
        }
        costMatrix.at(i).emplace_back(finput);
    }
    fclose(tcm);


    //Read travel time matrix.txt
    FILE *ttm;
    if ((ttm = fopen("travel time matrix.txt", "r")) == nullptr) {
        cout << "travel time matrix.txt does not exist!!" << endl;
        exit(1);
    }
    timeMatrix.emplace_back(vector<float>());
    for (int i = 0; fscanf(ttm, "%f%c", &finput, &c) != EOF;) {
        if (c == '\n') {
            timeMatrix.at(i).emplace_back(finput);
            timeMatrix.emplace_back(vector<float>());
            i++;
            continue;
        }
        timeMatrix.at(i).emplace_back(finput);
    }
    fclose(ttm);

    //Read scenario.txt
    FILE *scenario;
    if ((scenario = fopen("scenario.txt", "r")) == nullptr) {
        cout << "scenario.txt does not exist!!" << endl;
        exit(1);
    }

    while (fscanf(scenario, "%d%c", &input, &c) != EOF) {
        Scenario s;
        s.ids.emplace_back(input);
        while (c != '\n') {
            fscanf(scenario, "%d%c", &input, &c) != EOF;
            s.ids.emplace_back(input);
        }
        fscanf(scenario, "%f%c", &finput, &c);
        s.setProbabilityOfOccurrence(finput);
        scenarios.emplace_back(s);
    }

}

void init() {
    NumberOfDeterministicCustomers = Lbound.size() + 1;
    NumberOfStochasticCustomers = NumberOfDeterministicCustomers;

    L1.reserve(NumberOfDeterministicCustomers);
    L2.reserve(NumberOfDeterministicCustomers);

    costMatrix.reserve(NumberOfDeterministicCustomers + 2);
    timeMatrix.reserve(NumberOfDeterministicCustomers + 2);

    for (int i = 0; i < NumberOfDeterministicCustomers + 2; i++) {
        costMatrix[i].reserve(NumberOfDeterministicCustomers + 2);
        timeMatrix[i].reserve(NumberOfDeterministicCustomers + 2);
    }

    // Generating customers
    dCustomers.emplace_back(0, 0, 720);
    for (int i = 0; i < NumberOfDeterministicCustomers; i++) {
        dCustomers.emplace_back(i + 1, Lbound[i], Ubound[i]);
    }

    for (int i = NumberOfDeterministicCustomers;
         i < NumberOfStochasticCustomers + NumberOfDeterministicCustomers - 1; i++) {
        sCustomers.emplace_back(i, Lbound2[i - NumberOfDeterministicCustomers],
                                Ubound2[i - NumberOfDeterministicCustomers]);
    }

    // Generating probability of stochastic customers randomly
    float p;
    for (int i = 0; i < NumberOfStochasticCustomers - 1; i++) {
        p = unif(generator);
        sCustomers.at(i).setProbability(p);
    }

    // Classify high probability stochastic customers and low probability stochastic customers

    // Put deterministic customers into L1
    for (int i = 0; i < NumberOfDeterministicCustomers; i++) {
        L1.emplace_back(dCustomers.at(i));
    }

    // Classified by probability
    for (int i = 0; i < NumberOfStochasticCustomers - 1; i++) {
        L2.emplace_back(sCustomers.at(i));
    }

    // Sorting
    sort(L2.begin(), L2.end(), Customer::cmp);
}

void runCars() {
    for(int i = 0; i < NumberOfVehicle2; i++) {
        cars.emplace_back(Car(timeMatrix, Lbound, Ubound, Lbound2, Ubound2));
    }
    int nowCar = 0;

    routes.emplace_back(Route());
    routes[0].addNode(0);
    for(int i = 1; i < solution.getCustomers().size(); i++) {
        routes[routes.size() - 1].addNode(solution.getCustomers()[i].getID());
        if(solution.getCustomers()[i].getID() == 0) {
            routes.emplace_back(Route());
            routes[routes.size() - 1].addNode(0);
        }
    }
    routes.pop_back();

    for (auto &route : routes) {
        for (int j = 0; j <= cars.size(); j++) {
            if (j == cars.size()) {
                int min = 99999, minCar = 0;
                for (int k = 0; k < cars.size(); k++) {
                    if (min > cars[k].startTime) {
                        min = cars[k].startTime;
                        minCar = k;
                    }
                }

                cars[minCar].setRoute(route);
                cars[minCar].run();
                cout << "Car " << minCar + 1 << " : ";
                cars[minCar].print();
                cars[minCar].clearRoute();
                break;
            }

            int ltime;
            if (route._customerIDs[1] >= NumberOfDeterministicCustomers) {
                ltime = Lbound2[route._customerIDs[1] - NumberOfDeterministicCustomers];
            } else {
                ltime = Lbound[route._customerIDs[1] - 1];
            }

            if (cars[j].startTime < ltime) {
                cars[j].setRoute(route);
                cars[j].run();
                cout << "Car " << j + 1 << " : ";
                cars[j].print();
                cars[j].clearRoute();
                break;
            }
        }
    }


}

void calScenarioValue() {
    //remove 0 from solution
    for (int i = 1; i < solution.getCustomers().size() - 1; i++)
        if (solution.getCustomers()[i].getID() == 0)
            solution.getCustomers().erase(solution.getCustomers().begin() + i);

    float total = 0;
    Chromosome temp;
    for (auto &scenario : scenarios) {
        temp = Chromosome(solution, true, NumberOfDeterministicCustomers);
        for (int j = 0; j < temp.getCustomers().size(); j++) {
            bool flag = false;
            if (temp.getCustomers()[j].getID() >= NumberOfDeterministicCustomers) {
                for (int id : scenario.ids) {
                    if (temp.getCustomers()[j].getID() != (id + NumberOfDeterministicCustomers - 1)) {
                        flag = false;
                        continue;
                    } else {
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    temp.getCustomers().erase(temp.getCustomers().begin() + j);
                    j--;

                }
            }
        }

        for (int i = 1; i < temp.getCustomers().size(); i++) {
            int pre = temp.getCustomers()[i - 1].getID();
            int next = temp.getCustomers()[i].getID();

            if (pre >= NumberOfDeterministicCustomers) pre = pre - NumberOfDeterministicCustomers + 1;
            if (next >= NumberOfDeterministicCustomers) next = next - NumberOfDeterministicCustomers + 1;
            if (pre == next) {
                temp.getCustomers().erase(temp.getCustomers().begin() + i);
                i--;
            }
        }

        temp.calculateFitnessValue();
        total += temp.getFitnessValue() * scenario.getProbabilityOfOccurrence();

        for (auto &j : temp.getCustomers()) {
            cout << j.getID() << " ";
        }
        cout << endl;

    }

    cout << "Total : " << total << endl;
}

int main() {
    readFiles();
    init();

    //Release Memory
    dCustomers.clear();
    dCustomers.shrink_to_fit();
    sCustomers.clear();
    sCustomers.shrink_to_fit();
    chromosomes->clear();
    chromosomes->shrink_to_fit();

    for (int i = 0; i < NumberOfChromosome; i++) {
        chromosomes->emplace_back(Chromosome(L1, NumberOfDeterministicCustomers));
    }
    L1.clear();
    L1.shrink_to_fit();

    cout << "Algorithm2 Starts" << endl;
    // Use Hybrid Generation Algorithm to generate a route.
    sleep(0.1);
    for (int i = 0; i < NumberOfGeneration; i++) {
        algorithm2();
    }
    cout << "Algorithm2 Ends" << endl;

    // Best route (only dCustomer)
    solution = Chromosome(chromosomes->at(0));
    delete (chromosomes);

    // Check if there's an error occurs
    sleep(0.1);
    for (int i = 1; i < solution.getCustomers().size(); i++) {
        if (solution.getCustomers().at(i).getID() == 0)
            solution.getCustomers().erase(solution.getCustomers().begin() + i);
    }

    cout << "Algorithm3 Starts" << endl;
    algorithm3();
    cout << "Algorithm3 Ends" << endl;

    cout << "al3 finished" << endl;
    sleep(0.1);
    solution.getCustomers().emplace_back(0);
    for (int i = 1; i < solution.getCustomers().size(); i++) {
        if (i % (CapacityOfVehicle + 1) == 0) {
            solution.getCustomers().insert(solution.getCustomers().begin() + i, 0);
        }
    }

    solution.getIDs();
    cout << "runCars Starts" << endl;
    runCars();
    cout << "runCars Ends" << endl;


    calScenarioValue();

    return 0;
}