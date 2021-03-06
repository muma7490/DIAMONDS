#include "PolynomialModel.h"


// PolynomialModel::PolynomialModel()
//
// PURPOSE: 
//      Constructor. Initializes model computation.
//
// INPUT:
//      covariates:             one-dimensional array containing the values
//                              of the independent variable.
//      Ndegrees:                 an integer containing the degree of the polynomial to fit.
//                              A polynomial of the type y = a*x + b has degree = 1.
//

PolynomialModel::PolynomialModel(const RefArrayXd covariates, int Ndegrees)
: Model(covariates),
  Ndegrees(Ndegrees)
{
}










// PolynomialModel::PolynomialModel()
//
// PURPOSE: 
//      Destructor.
//

PolynomialModel::~PolynomialModel()
{

}










// PolynomialModel::getNdegrees()
//
// PURPOSE: 
//      Get the protected data member Ndegrees.
//
// OUTPUT:
//      An integer containing the degree of the polynomial.
//

int PolynomialModel::getNdegrees()
{
    return Ndegrees;
}









// PolynomialModel::predict()
//
// PURPOSE:
//      Builds the predictions from a quadratic model of the type f = offset + a*x + b*x^2 + c*x^3 + ...
//      where offset, a, b, c, ... are the free parameters and x the covariates.
//      The free parameters related to the covariates have to be sorted in increasing degree order.
//
// INPUT:
//      predictions:        one-dimensional array to contain the predictions
//                          from the model
//      modelParameters:    one-dimensional array where each element
//                          contains the value of a free parameter of the model
//
// OUTPUT:
//      void
//

void PolynomialModel::predict(RefArrayXd predictions, RefArrayXd const modelParameters)
{
    // Compute predictions with a loop over the different degrees of the polynomial

    for (int degree = 0; degree < Ndegrees; ++degree)
    {
        predictions += covariates.pow(degree + 1)*modelParameters(degree);
    }

    predictions += modelParameters(Ndegrees);
}

    




