#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <iostream>
#include "PayOff.h"
#include <ctime>
#include <cmath>

/*
CLASSE MERE : MONTECARLO
Les différentes méthodes de cette classe sont les différentes méthodes d'arrêt du MonteCarlo
*/

class MonteCarlo
{
    public :
    MonteCarlo();
    virtual double operator()(double Spot) const=0;
    virtual double PrixA(unsigned long NumberOfPaths, PayOff& thePayOff, MonteCarlo& Simu, double Spot);
    virtual double PrixT(int secondes, PayOff& thePayOff, MonteCarlo& Simu, double Spot);
    virtual double PrixAc(unsigned long NumberOfPaths, PayOff& thePayOff, MonteCarlo& Simu, double Spot, double Expiry, double r);
    virtual double getSpot() const;
    virtual double getExpiry() const;
    virtual double getr() const;
    virtual double Simu(double Spot, double Expiry) const;
    protected :
};


/*
 CLASSE MERE : MONTECARLO
Permet de simuler le cours avec la méthode B&S
 */

class MonteCarloB : public MonteCarlo
{
    public :
            MonteCarloB(double Strike, double Expiry, double Spot, double Vol, double r);
            virtual double operator()(double Spot) const;
            virtual double Simu(double Spot, double Expiry) const;
            virtual double getSpot() const ;
            virtual double getExpiry() const ;
            virtual double getr() const ;
    ~MonteCarloB();

    protected :
    double m_Strike;
    double m_Expiry;
    double m_Spot;
    double m_Vol;
    double m_r;
    int m_TypeOption;
    double variance ;
    double Rootvariance;
    double demivar;
    double m_movedSpot;
    double thisSpotB;

};

/*
 CLASSE MERE : MONTECARLO
 Permet de simuler le cours avec la méthode Levy
 */


class MonteCarloL : public MonteCarlo
{
    public :
    MonteCarloL(double Strike, double Expiry, double Spot, double Vol, double r, double lambda, double m, double vega2);
    virtual double operator()(double Spot) const;
    virtual double Simu(double Spot, double Expiry) const;
    virtual double getSpot() const ;
    virtual double getExpiry() const ;
    virtual double getr() const ;
    protected :

    double m_Strike;
    double m_Expiry;
    double m_Spot;
    double m_Vol;
    double m_r;
    int m_TypeOption;
    double m_lambda;
    double m_m;
    double m_vega2;
    double variance ;
    double Rootvariance;
    double demivar;
    double m_movedSpot;
    double thisSpotL;
};


#endif // MONTECARLO_H
