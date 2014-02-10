#include "MonteCarlo.h"

#include "MonteCarlo.h"
#include "PayOff.h"
#include "Genealeatoire.h"
#include <cstdlib>
#include <cmath>

using namespace std;



////////////////////////////////// GRAPHE 3 : PAYOFF BROWNIEN //////////////////////////////////////
// Propose deux types différents d'arrêts de la MC : nombre d'itérations, temps de calcul //



// Constructeur mère

MonteCarlo::MonteCarlo() {};

// Accesseurs Spot, Expiry, r //

double MonteCarlo::getSpot() const
{
    return 0;
}
double MonteCarlo::getExpiry() const
{
    return 0;
}

double MonteCarlo::getr() const
{
    return 0;
}

// Méthode virtuelle pure ??? (vérifier la dénomination)//

double MonteCarlo::Simu(double Spot, double Expiry) const
{
    return 0;
}

////////////////////////////////// METHODE 1 POUR ARRETER MC  //////////////////////////////////////
//  le nombre de pas entré par l'utilisateur //


double MonteCarlo::PrixA(unsigned long NumberOfPaths, PayOff& thePayOff, MonteCarlo& Simu, double Spot)
{
    double runningSum(0);
    unsigned long i(0);
    while (i<NumberOfPaths)
 {
     i+=1;
     runningSum+=thePayOff(Simu(Spot));
 }
    double mean = (runningSum/i)*exp(-Simu.getExpiry()*Simu.getr());
    return mean;
 }

////////////////////////////////// METHODE 1 POUR ARRETER MC  //////////////////////////////////////
//  le temps de calcul (en secondes) chosi par l'utilisateur //


double MonteCarlo::PrixT(int secondes, PayOff& thePayOff, MonteCarlo& Simu, double Spot)
{
    time_t tbegin,tend;
    unsigned long k=0;
    double texec=0.;
    double runningSum(0);
    tbegin=time(NULL);              // Date du debut

    while (texec<secondes)
    {
        tend=time(NULL);                // Date de fin
        k+=1;
        runningSum+=thePayOff(Simu(Spot));
        texec=difftime(tend,tbegin);    // tend-tbegin (resultat en secondes)
    }
    double mean = (runningSum/k)*exp(-Simu.getExpiry()*Simu.getr());
    return mean;
}


////////////////////////////////// MC POUR LES GRAPHES  //////////////////////////////////////

double MonteCarlo::PrixAc(unsigned long NumberOfPaths, PayOff& thePayOff, MonteCarlo& Simu, double Spot, double Expiry, double r)
{
    double runningSum(0);
    for(int i=1;i<NumberOfPaths;i++)
    {
        runningSum+=thePayOff(Simu.Simu(Spot,Expiry));
    }
    double mean = runningSum/NumberOfPaths;
    double resultat=mean*exp(-(Expiry*r));
    return resultat;
}



////////////////////////////////// CLASSE FILLE 1 : BROWNIEN  //////////////////////////////////////
// Classe pour simuler le cours dans le cas du modèle Black-Scholes-Merton //


MonteCarloB ::MonteCarloB(double Strike, double Expiry, double Spot, double Vol, double r) :  m_Strike(Strike), m_Expiry(Expiry), m_Spot(Spot), m_Vol(Vol), m_r(r), variance(m_Vol*m_Vol*m_Expiry), Rootvariance(sqrt(variance)), demivar(-0.5*variance), m_movedSpot(m_Spot*exp(m_r*m_Expiry+demivar)), thisSpotB(1)
{
}

MonteCarloB::~MonteCarloB()
{
}


double MonteCarloB::operator()(double Spot) const
{
    double SpotTB(1);
    double thisGaussian = gNormale();
    SpotTB=m_movedSpot*exp(Rootvariance*thisGaussian);
    return SpotTB;
}


// Une version avec choix Spot et Expiry pour tracer les graphes, plus long car les calculs sont répétés dans chaque boucle de la MC //

double MonteCarloB::Simu(double Spot, double Expiry) const
{
    double varianceSB(m_Vol*m_Vol*Expiry);
    double RootvarianceSB(sqrt(varianceSB));
    double demivarSB(-0.5*varianceSB);
    double movedSpot(Spot*exp(m_r*Expiry+demivarSB));
    double thisGaussian = gNormale();
    double SimuBr = movedSpot*exp(RootvarianceSB*thisGaussian);
    return SimuBr;
}

// Accesseurs Spot, Expiry, r //

double MonteCarloB::getSpot() const
{
    return m_Spot;
}

double MonteCarloB::getExpiry() const
{
    return m_Expiry;
}

double MonteCarloB::getr() const
{
    return m_r;
}


////////////////////////////////// CLASSE FILLE 2 : LEVY  //////////////////////////////////////
// Classe pour simuler le cours dans le cas du modèle de Levy //

MonteCarloL ::MonteCarloL(double Strike, double Expiry, double Spot, double Vol, double r, double lambda, double m, double vega2) :  m_Strike(Strike), m_Expiry(Expiry), m_Spot(Spot), m_Vol(Vol), m_r(r), m_lambda(lambda), m_m(m), m_vega2(vega2), variance(m_Vol*m_Vol*m_Expiry), Rootvariance(sqrt(variance)), m_movedSpot(m_Spot*exp(m_r*m_Expiry+demivar)), demivar(-0.5*variance), thisSpotL(1)
{
}

double MonteCarloL::operator()(double Spot) const
{
    double T(1);
    double thisGaussian = gNormale();
    int N=gPoisson(m_lambda);
        if (N>0)
            for (int i=0; i<N+1; i++)
                T=T*(gLogNormale(m_m, m_vega2));
           double  SpotTL=m_movedSpot*exp(Rootvariance*thisGaussian)*T;
    return SpotTL;
}

// Une version avec choix Spot et Expiry pour tracer les graphes, plus long car les calculs sont répétés dans chaque boucle de la MC //

double MonteCarloL::Simu(double Spot, double Expiry) const
{
    double T(1);
    double varianceSL(m_Vol*m_Vol*Expiry);
    double RootvarianceSL(sqrt(varianceSL));
    double demivarSL(-0.5*varianceSL);
    double movedSpot(Spot*exp(m_r*Expiry+demivarSL));
    double thisGaussian = gNormale();
    int N=gPoisson(m_lambda);
    if (N>0)
        for (int i=0; i<N+1; i++)
            T=T*(gLogNormale(m_m, m_vega2));
    double SimuLr=movedSpot*exp(RootvarianceSL*thisGaussian)*T;
    return SimuLr;
}

// Accesseurs Spot, Expiry, r //

double MonteCarloL::getSpot() const
{
    return m_Spot;
}

double MonteCarloL::getExpiry() const
{
    return m_Expiry;
}

double MonteCarloL::getr() const
{
    return m_r;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
