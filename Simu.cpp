#include "Simu.h"
#include "MonteCarlo.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <QVector>

using namespace std;

////////////////////////////////// SIMU DE COURS //////////////////////////////////////

QVector<double> Simul(MonteCarlo& pSimu, int prec)
{
QVector<double> Simulr(prec);
double rec(pSimu.getSpot());
double pas=(pSimu.getExpiry()/prec);
double tempspas=(pas);
for (int j=0;j<prec;++j)
{
    tempspas+=pas;
    rec=pSimu.Simu(rec,pas);
    Simulr[j]=rec;
}
    return Simulr;
}

////////////////////////////////// SIMU POUR DIFFERENTS SPOT //////////////////////////////////////


QVector<double> gPayO(MonteCarlo& pMC, PayOff& PO, int prec, double Strike, double Expiry)
{
    QVector<double> gPayOr(prec);
    double POt;
    double pas=(2*Strike)/prec;
    double axe(0);
    for (int j=0;j<prec;j++)
    {
        axe+=pas;
        POt=pMC.PrixAc(10000,PO,pMC,axe,Expiry, 0.09);
        gPayOr[j]=POt;
    }
    return gPayOr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

QVector<double> gPayOT(MonteCarlo& pMC, PayOff& PO, int prec, double Strike)
{
     double POT;
     QVector<double> gPayOr(prec);
     double pas=(2*Strike)/prec;
     double axe(0);
     for (int j=0;j<prec;j++)
     {
         axe+=pas;
         POT=PO(axe);
         gPayOr[j]=POT;
     }
     return gPayOr;
}
