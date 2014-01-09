//
// Compile with: clang++ -o demoRosenbrockFunction demoRosenbrockFunction.cpp -L../build/ -I ../include/ -l multinest -stdlib=libc++ -std=c++11
// 

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Functions.h"
#include "File.h"
#include "MultiEllipsoidSampler.h"
#include "KmeansClusterer.h"
#include "EuclideanMetric.h"
#include "Prior.h"
#include "UniformPrior.h"
#include "NormalPrior.h"
#include "Results.h"
#include "Ellipsoid.h"
#include "ZeroModel.h"
#include "FerozReducer.h"
#include "PowerlawReducer.h"
#include "demoRosenbrockFunction.h"


int main(int argc, char *argv[])
{
    unsigned long Nrows;
    int Ncols;
    ArrayXXd data;
  
    // Creating dummy arrays for the covariates and the observations.
    // They're not used because we compute our Likelihood directly. 

    ArrayXd covariates;
    ArrayXd observations;


    // -------------------------------------------------------------------
    // ----- First step. Set up the models for the inference problem ----- 
    // ------------------------------------------------------------------- 

    // Set up a dummy model. This won't be used because we're computing
    // the Likelihood directly, but the Likelihood nevertheless expects a model in 
    // its constructor.
    
    ZeroModel model(covariates);


    // -------------------------------------------------------
    // ----- Second step. Set up all prior distributions -----
    // -------------------------------------------------------

    int Ndimensions = 2;        // Number of free parameters (dimensions) of the problem
    vector<Prior*> ptrPriors(1);
    ArrayXd parametersMinima(Ndimensions);
    ArrayXd parametersMaxima(Ndimensions);
    parametersMinima <<  -3.0, -2.0;
    parametersMaxima << 4.0, 10.0;
    UniformPrior uniformPrior(parametersMinima, parametersMaxima);
    ptrPriors[0] = &uniformPrior;   


    // -----------------------------------------------------------------
    // ----- Third step. Set up the likelihood function to be used -----
    // -----------------------------------------------------------------

    RosenbrockLikelihood likelihood(observations, model);
    

    // -------------------------------------------------------------------------------
    // ----- Fourth step. Set up the K-means clusterer using an Euclidean metric -----
    // -------------------------------------------------------------------------------

    EuclideanMetric myMetric;
    int minNclusters = 3;
    int maxNclusters = 6;
    int Ntrials = 10;
    double relTolerance = 0.01;

    KmeansClusterer kmeans(myMetric, minNclusters, maxNclusters, Ntrials, relTolerance); 


    // ---------------------------------------------------------------------
    // ----- Sixth step. Configure and start nested sampling inference -----
    // ---------------------------------------------------------------------
    
    bool printOnTheScreen = true;                   // Print results on the screen
    int initialNobjects = 1000;                      // Initial number of active points evolving within the nested sampling process.
    int minNobjects = 400;                          // Minimum number of active points allowed in the nesting process.
    int maxNdrawAttempts = 50000;                    // Maximum number of attempts when trying to draw a new sampling point.
    int NinitialIterationsWithoutClustering = 200;  // The first N iterations, we assume that there is only 1 cluster.
    int NiterationsWithSameClustering = 20;         // Clustering is only happening every X iterations.
    double initialEnlargementFraction = 2.0;        // Fraction by which each axis in an ellipsoid has to be enlarged.
                                                    // It can be a number >= 0, where 0 means no enlargement.
    double shrinkingRate = 0.4;                     // Exponent for remaining prior mass in ellipsoid enlargement fraction.
                                                    // It is a number between 0 and 1. The smaller the slower the shrinkage
                                                    // of the ellipsoids.
    double terminationFactor = 0.05;                // Termination factor for nesting loop.


    // Start the computation

    MultiEllipsoidSampler nestedSampler(printOnTheScreen, ptrPriors, likelihood, myMetric, kmeans, 
                                        initialNobjects, minNobjects, initialEnlargementFraction, shrinkingRate);
    
    double tolerance = 1.e2;
    double exponent = 0.4;
    //FerozReducer livePointsReducer(nestedSampler, tolerance);
    PowerlawReducer livePointsReducer(nestedSampler, tolerance, exponent, terminationFactor);

    string outputPathPrefix = "demoRosenbrockFunction_";
    nestedSampler.run(livePointsReducer, NinitialIterationsWithoutClustering, NiterationsWithSameClustering, 
    maxNdrawAttempts, terminationFactor, outputPathPrefix);


    // -------------------------------------------------------
    // ----- Last step. Save the results in output files -----
    // -------------------------------------------------------

    Results results(nestedSampler);
    results.writeParametersToFile("Parameter");
    results.writeLogLikelihoodToFile("LikelihoodDistribution.txt");
    results.writeEvidenceInformationToFile("EvidenceInformation.txt");
    results.writePosteriorProbabilityToFile("PosteriorDistribution.txt");

    double credibleLevel = 68.3;
    bool writeMarginalDistributionToFile = true;
    results.writeParametersSummaryToFile("ParameterSummary.txt", credibleLevel, writeMarginalDistributionToFile);

 
    // That's it!

    return EXIT_SUCCESS;
}
