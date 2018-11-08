//
// Created by kevin on 2018/8/13.
//

#ifndef MTVRPTWSC_PARAM_H
#define MTVRPTWSC_PARAM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <unistd.h>
#include <thread>
#include <assert.h>
#include <chrono>

#include "Route.h"
#include "Customer.h"
#include "TimeWindow.h"
#include "Car.h"
#include "Scenario.h"
#include "Chromosome.h"

using namespace std;

static const int NumberOfVehicle = 15;
static const int NumberOfVehicle2 = 3;
static const int CapacityOfVehicle = 3;
static const float PenalizationFactor = 100;
static const int serviceTime = 8;

static int NumberOfDeterministicCustomers = 0;
static int NumberOfStochasticCustomers = 0;

static const int NumberOfChromosome = 20;

static const unsigned int NumberOfGeneration = 50;

extern std::vector<int> Lbound; // ai.txt
extern std::vector<int> Ubound; // bi.txt
extern std::vector<int> Lbound2; // ai2.txt
extern std::vector<int> Ubound2; // bi2.txt
extern std::vector<std::vector<int>> distanceMatrix; // distance matrix.txt
extern std::vector<std::vector<float>> costMatrix; // travel cost matrix.txt
extern std::vector<std::vector<float>> timeMatrix; // travel time matrix.txt
extern std::vector<Scenario> scenarios; // travel time matrix.txt

#endif //MTVRPTWSC_PARAM_H
