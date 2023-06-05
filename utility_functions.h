/**
 * @file utility_functions.h
 * Implementation of an utility functions for the project. 
 *
 * @author Ravi Patel 
 */

#pragma once 

#include <iostream>
#include <cmath>
#include<limits>

namespace cs225_fp { 
const double EPSILON = std::numeric_limits<double>::epsilon();
const double DBL_MAX{std::numeric_limits<double>::max()};
bool float_equal(double a, double b);
double haversine(double lat1, double lon1, double lat2, double lon2);
}