#include "MathExtra.h"


// MathExtra::lorentzProfile()
//
// PURPOSE: 
//      Computes a simple Lorentzian profile given the centroid and the width.
//      Saves the dependent variable values into a vector y accessible as
//      public data member.
//
// INPUT:
//      predictions : vector containing the result
//      covariates : vector containing independent variable values
//      centroid : centroid of the Lorentzian profile (default = 0)
//      amplitude : maximum height of the Lorentzian profile (default = 1)
//      gamma : width of the Lorentzian profile (mode linewidth) (default = 1)
//
// OUTPUT:
//      void
//

void MathExtra::lorentzProfile(RefArrayXd predictions, const RefArrayXd covariates, double centroid, double amplitude, double gamma)
{
        predictions = (amplitude*amplitude)/((covariates-centroid)*(covariates-centroid) + (gamma/2.)*(gamma/2.));

} // END MathExtra::lorentzProfile()










// MathExtra::logGaussProfile()
//
// PURPOSE: 
//      Computes the logarithm of a Gaussian profile given the centroid, 
//      the standard deviation and the amplitude, for one given x-value
//
// INPUT:
//      covariate : independent variable
//      mu : mean value of the Gaussian profile (default = 0)
//      sigma : standard deviation of the Gaussian profile (default = 1)
//      amplitude : maximum amplitude of the Gaussian profile (default = 1)
//
// OUTPUT:
//      The natural logarithm of the Gaussian profile value of the independent variable.
//

double MathExtra::logGaussProfile(const double covariate, const double mu, const double sigma, const double amplitude)
{
    const double prefactor = log(amplitude) - 0.5 * log(2*MathExtra::PI) - log(sigma);

    return prefactor - 0.5 * (covariate - mu) * (covariate - mu) / (sigma * sigma);

} // END MathExtra::logGaussProfile() 








// MathExtra::logGaussProfile()
//
// PURPOSE: 
//      Computes the logarithm of a Gaussian profile given the centroid, 
//      the standard deviation and the amplitude for a set of values (overloaded)
//
// INPUT:
//      predictions : Eigen array containing the result
//      covariates : Eigen array containing independent variable values
//      mu : mean value of the Gaussian profile (default = 0)
//      sigma : standard deviation of the Gaussian profile (default = 1)
//      amplitude : maximum amplitude of the Gaussian profile (default = 1)
//
// OUTPUT:
//      void
//

void MathExtra::logGaussProfile(RefArrayXd predictions, const RefArrayXd covariates, const double mu, const double sigma, const double amplitude)
{
    const double prefactor = log(amplitude) - 0.5 * log(2*MathExtra::PI) - log(sigma);
    predictions = prefactor - 0.5 * (covariates - mu) * (covariates - mu) / (sigma * sigma);
    
} // END MathExra::logGaussProfile()









// MathExtra::logGaussLikelihood() 
//
// PURPOSE: 
//      Computes the log-Gaussian likelihood from a set of observations,
//      uncertainties, and theoretical predictions.
//
// INPUT:
//      observations : array containing the oberved values
//      predictions : array containing the corresponding predicted values of x
//      uncertainties : array containing the uncertanties on the observed values
//
// OUTPUT:
//      The resulting value of the log-Gaussian likelihood.
//

double MathExtra::logGaussLikelihood(const RefArrayXd observations, const RefArrayXd predictions, const RefArrayXd uncertainties)
{
    if ((observations.size() != predictions.size()) || (observations.size() != uncertainties.size()))
    {
        cout << "Array dimensions do not match. Quitting program." << endl;
        exit(1);
    }
    
    ArrayXd delta;
    ArrayXd lambda0;
    ArrayXd lambda;
    
    delta = ((observations - predictions)*(observations - predictions)) / (uncertainties*uncertainties);
    lambda0 = -1.*log(sqrt(2.*PI) * uncertainties);
    lambda = lambda0 -0.5*delta;
    
    return lambda.sum();

} // END MathExtra::logGaussLikelihood()








// MathExtra::product()
//
// PURPOSE: 
//      Computes the product of the elements contained in a vector of doubles of class vector.
//
// INPUT:
//      vec : vector of values to be multiplied
//
// OUTPUT:
//      The productoria of the vector elements.
//

inline double MathExtra::product(const vector<double> &vec)
{
    return accumulate(vec.begin(), vec.end(), 1.0, multiplies<double>());
} // END MathExtra::product()









// MathExtra::sum()
//
// PURPOSE: 
//      Computes the sum of the elements contained in a vector of doubles of vector class.
//
// INPUT:
//      vec : vector of values to be added.
//
// OUTPUT:
//      The summation of the vector elements.
//

inline double MathExtra::sum(const vector<double> &vec)
{
    return accumulate(vec.begin(), vec.end(), 0.0);
} // END MathExtra::sum()








// MathExtra::logExpSum()
//
// PURPOSE: 
//      Computes a logaritmic summation of exponentials in order to avoid overflow errors.
//
// INPUT: 
//      x : a first variable to be added
//      y : a second variable to be added
//
// OUTPUT: 
//        The logarithmic summation of the exponentials log(exp(x)+exp(y)).
//

double MathExtra::logExpSum(double x, double y)
{
    return (x >= y ? x+log(1.+exp(y-x)) : y + log(1.+exp(x-y)));
} // END MathExtra::logExpSum()

