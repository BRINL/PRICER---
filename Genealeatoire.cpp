//  Genealeatoire.cpp


#include "Genealeatoire.h"
#include <cstdlib>
#include <cmath>
#include "math.h"
#include "time.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

////////////////////////////////// UNIFORME (0,1) //////////////////////////////////////

double uRand()
{
    return (rand()/static_cast<double>(RAND_MAX));
}

////////////////////////////////// LOI NORMALE (0,1)  //////////////////////////////////////
// Méthode employée ??? //

double gNormale()
{
    double result=0;
    for (unsigned long j=0; j < 12; j++)
        result += rand()/static_cast<double>(RAND_MAX);
    result -= 6.0;
    return result;
     }

////////////////////////////////// LOI LOGNORMALE (m, vega2)  //////////////////////////////////////

double gLogNormale(double m, double vega2)
{
    double normal=sqrt(vega2)*gNormale()+m;
    return exp(normal);
}

////////////////////////////////// LOI POISSON (lambda)  //////////////////////////////////////

// Méthode employée ??? //

int gPoisson(double lambda)
{
    double L=exp(-lambda);
    double p(1);
    int k(1);
    while (p>L)
    {
        p=p*uRand();
        k+=1;
    }
    return (k-1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

