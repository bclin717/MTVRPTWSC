//
// Created by kevin on 2018/8/13.
//

#ifndef MTVRPTWSC_PARAM_H
#define MTVRPTWSC_PARAM_H

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

#include "Route.h"
#include "Customer.h"
#include "TimeWindow.h"
#include "Car.h"
#include "Scenario.h"
#include "Link.h"
#include "Chromosome.h"

using namespace std;

static const int CurrentBestValue = 9999999;
static const float PriorityThresholdValue = 0.5;
static vector<Scenario> scenarios;

static const int SpeedKmHr = 40;
static const float SpeedKmMin = 1.5;

static const int NumberOfVehicle = 15;
static const int CapacityOfVehicle = 4;
static const float PenalizationFactor = 0.5;
static const int serviceTime = 10;

static const int NumberOfDeterministicCustomers = 16;
static const int NumberOfStochasticCustomers = 16;

static const int NumberOfChromosome = 10;

static const unsigned int NumberOfGeneration = 500;

const float distanceMatrix[NumberOfDeterministicCustomers][NumberOfDeterministicCustomers] = {
        {0.00,13.96,7.06,7.92,10.94,14.37,13.30,6.99,11.87,19.36,11.13,15.04,10.79,13.86,20.95,17.88},
        {13.96,0.00,9.93,5.78,11.13,12.72,0.77,7.01,5.06,7.39,3.41,1.09,8.74,2.64,7.16,3.92},
        {7.06,9.93,0.00,12.06,4.14,7.57,9.16,4.60,10.68,13.26,8.64,10.95,3.77,11.14,15.87,13.39},
        {17.92,5.78,12.06,0.00,11.13,11.05,5.90,11.16,10.84,1.63,8.99,5.35,9.10,8.21,4.53,4.45},
        {10.94,11.13,4.14,11.13,0.00,3.45,10.41,8.08,13.43,11.92,11.06,11.95,2.39,13.06,15.51,13.77},
        {14.37,12.72,7.57,11.05,3.45,0.00,12.10,11.17,15.91,11.37,13.44,13.33,4.77,15.01,15.58,14.56},
        {13.30,0.77,9.16,5.90,10.41,12.10,0.00,6.32,5.06,7.53,3.09,1.83,8.02,3.02,7.72,4.58},
        {6.99,7.01,4.60,11.16,8.08,11.17,6.32,0.00,6.23,12.69,4.58,8.10,6.45,7.32,13.96,10.91},
        {11.87,5.06,10.68,10.84,13.43,15.91,5.06,6.23,0.00,12.45,2.49,5.65,11.27,2.95,11.51,8.12},
        {19.36,7.39,13.26,1.63,11.92,11.37,7.53,12.69,12.45,0.00,10.62,6.91,10.07,9.78,4.62,5.59},
        {11.13,3.41,8.64,8.99,11.06,13.44,3.09,4.58,2.49,10.62,0.00,4.33,8.84,2.76,10.50,7.16},
        {15.04,1.09,10.95,5.35,11.95,13.33,1.83,8.10,5.65,6.91,4.33,0.00,9.56,2.87,6.17,2.87},
        {10.79,8.74,3.77,9.10,2.39,4.77,8.02,6.45,11.27,10.07,8.84,9.56,0.00,10.71,13.34,11.44},
        {13.86,2.64,11.14,8.21,13.06,15.01,3.02,7.32,2.95,9.78,2.76,2.87,10.71,0.00,8.56,5.18},
        {20.95,7.16,15.87,4.53,15.51,15.58,7.72,13.96,11.51,4.62,10.50,6.17,13.34,8.56,0.00,3.39},
        {17.88,3.92,13.39,4.45,13.77,14.56,4.58,10.91,8.12,5.59,7.16,2.87,11.44,5.18,3.39,0.00}
};


#endif //MTVRPTWSC_PARAM_H
