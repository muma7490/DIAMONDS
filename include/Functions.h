// Class for implementing some extra functions useful 
// computations of models and likelihoods.
// Created by Enrico Corsaro @ IvS - 22 January 2013
// e-mail: enrico.corsaro@ster.kuleuven.be
// Header file "Functions.h"
// Implementation contained in "Functions.cpp"


#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>
#include <cassert>
#include <numeric>
#include <functional>
#include <random>
#include <ctime>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>
#include "EuclideanMetric.h"

#define SWAP(a,b) {double copy; copy = a, a = b, b = copy;}


using namespace std;
using namespace Eigen;
typedef Eigen::Ref<Eigen::ArrayXd> RefArrayXd;
typedef Eigen::Ref<Eigen::ArrayXXd> RefArrayXXd;

namespace Functions
{

    const double PI = 4.0 * atan(1.0);


    // Profile functions
    
    void lorentzProfile(RefArrayXd predictions, const RefArrayXd covariates, const double centroid = 0.0, const double amplitude = 1.0, const double gamma = 1.0);
    double logGaussProfile(const double covariate, const double mu = 0.0, const double sigma = 1.0, const double amplitude = 1.0);
    void logGaussProfile(RefArrayXd y, const RefArrayXd x, const double mu = 0.0, const double sigma = 1.0, const double amplitude = 1.0);
    
    
    // Likelihood functions
    
    double logGaussLikelihood(const RefArrayXd observations, const RefArrayXd predictions, const RefArrayXd uncertainties);
    
    
    // Matrix algebra functions

    void clusterCovariance(const RefArrayXXd clusterSample, RefArrayXXd covarianceMatrix, RefArrayXd centerCoordinates);
    void covarianceDecomposition(const RefArrayXXd covarianceMatrix, RefArrayXd covarianceEigenvalues, RefArrayXXd covarianceEigenvectors);
    

    // Array algebra functions
    
    inline double product(const vector<double> &vec);
    inline double sum(const vector<double> &vec);
    double logExpSum(double x, double y);
    void sortElements(RefArrayXd array1, RefArrayXd array2);


    // Sampling Distributions

    void hyperSphericalDistribution(RefArrayXXd sampleDistribution, const int Ndimensions, const int Npoints = 1, const double radius = 1);
    void BoxMullerDistribution(RefArrayXXd sampleDistribution, const int Npoints);


} // END namespace Functions
#endif