#ifndef SIMU_H
#define SIMU_H

#include <iostream>
#include <vector>
#include "MonteCarlo.h"
#include <QVector>


QVector<double> Simul(MonteCarlo& MonTest, int prec);
QVector<double> gPayO(MonteCarlo& MonTest, PayOff& PO, int prec, double Strike, double Expiry);
QVector<double> gPayOT(MonteCarlo& pMC, PayOff& PO, int prec, double Strike);

#endif // SIMU_H
