#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MonteCarlo.h"
#include "Genealeatoire.h"
#include "Time.h"
#include "Simu.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <QtGui>
#include <QWidget>

using namespace std;


MainWindow::MainWindow(QWidget *parent) :

  QMainWindow(parent),
  ui(new Ui::MainWindow),  Expiry(0.2), Spot(55), Vol(0.2), Strike(50), r(0.09), NumberOfPaths(10000),
  lambda(3), TypeOption(0), m(0.00001), vega2(0.00004), secondes(1), StopMCType(0), prec(200)
{ 

  ui->setupUi(this);
  SetupPlotSimuB();
  SetupPlotSimuL();
  SetupPlotPayOffB();
  SetupPlotPayOffL();
  SetupPrices();


  QWidget::setUpdatesEnabled(true);
  // On initialise les axes des graphes à partir des données rentrées par l'utilisateur //




  PayOff* ttt;
     if (TypeOption==1)
     {
         ttt = new PayOffCall(Strike);
     }
     else
     {
         ttt = new PayOffPut(Strike);
     };


connect(ui->PB, SIGNAL(clicked()), this, SLOT(AddSimuB()));
connect(ui->PL, SIGNAL(clicked()), this, SLOT(AddSimuL()));


connect(ui->eVol, SIGNAL(returnPressed()), this, SLOT(edVol()));
connect(ui->OK, SIGNAL(clicked()), this, SLOT(update2()));

}

////////////////////////////////////// RECUPERATION DES DONNES DE L'UTILISATEUR ////////////////////////////

double  MainWindow::edSpot()
{
    QString montexte = ui->eSpot->text();
    return montexte.toDouble();;
}

double  MainWindow::edStrike()
{
    QString montexte = ui->eStrike->text();
    return montexte.toDouble();;
}

double  MainWindow::edExpiry()
{
    QString montexte = ui->eExpiry->text();
    return montexte.toDouble();;
}

double  MainWindow::edVol()
{
    QString montexte = ui->eVol->text();
    return montexte.toDouble();;
}

double  MainWindow::edm()
{
    QString montexte = ui->em->text();
    return montexte.toDouble();;
}

double  MainWindow::edr()
{
    QString montexte = ui->er->text();
    return montexte.toDouble();;
}

double  MainWindow::edlambda()
{
    QString montexte = ui->elambda->text();
    return montexte.toDouble();;
}

double  MainWindow::edvega2()
{
    QString montexte = ui->evega2->text();
    return montexte.toDouble();;
}

bool  MainWindow::edMCStop()
{
    bool oun = ui->eite->isChecked();
    return oun;
}

bool  MainWindow::edPOC()
{
    bool oun = ui->eCal->isChecked();
    return oun;
}

unsigned long  MainWindow::edNumberOfPaths()
{
    QString montexte = ui->eNumberOfPaths->text();
    return montexte.toLong();;
}

int  MainWindow::edt()
{
    QString montexte = ui->esecondes->text();
    return montexte.toInt();;
}

void  MainWindow::update2()
{
    // INITIALISATION DES VALEURS //

        double Spot(0);
        Spot=edSpot();
        double Strike(0);
        Strike=edStrike();
        double Expiry(0);
        Expiry=edExpiry();
        double Vol(0);
        Vol=edVol();
        double r(0);
        r=edr();
        double lambda(0);
        lambda=edlambda();
        double m(0);
        m=edm();
        double vega2(0);
        vega2=edvega2();
        int StopMCType(0);
        if (edMCStop()==false)
            StopMCType=1;
        int TypeOption(0);
        if (edPOC()==true)
            TypeOption=1;
        unsigned long NumberOfPaths(0);
        NumberOfPaths=edNumberOfPaths();
        int secondes(0);
        secondes=edt();

        /*(Spot>0,Strike>0,Expiry>0, Vol>0, r>0, lambda>0, edMCStop()==false, ui->et->isChecked()=false, edPOC()=false, ui->ePut->isChecked()=false)
*/

    {
    ui->Plot_PayOffB->clearGraphs();
    ui->Plot_PayOffL->clearGraphs();
    ui->Plot_SimuB->clearGraphs();
    ui->Plot_SimuL->clearGraphs();
    SetupPlotSimuB();
    SetupPlotSimuL();
    SetupPlotPayOffB();
    SetupPlotPayOffL();
    SetupPrices();
            }
}


// Destructeur de notre fenêtre.
MainWindow::~MainWindow()
{
  delete ui;
}




////////////////////////////////// GRAPHE 1 : GRAPHE SIMU BROWNIEN //////////////////////////////////////

void MainWindow::SetupPlotSimuB()
{
    // INITIALISATION DES VALEURS //

        double Spot(0);
        Spot=edSpot();
        double Strike(0);
        Strike=edStrike();
        double Expiry(0);
        Expiry=edExpiry();
        double Vol(0);
        Vol=edVol();
        double r(0);
        r=edr();
        double lambda(0);
        lambda=edlambda();
        double m(0);
        m=edm();
        double vega2(0);
        vega2=edvega2();
        int StopMCType(0);
        if (edMCStop()==false)
            StopMCType=1;
        int TypeOption(0);
        if (edPOC()==true)
            TypeOption=1;
        unsigned long NumberOfPaths(0);
        NumberOfPaths=edNumberOfPaths();
        int secondes(0);
        secondes=edt();

    MonteCarloB pSimuB(Strike, Expiry, Spot, Vol, r);
// Setup des caractéristiques du graphe //

   ui->Plot_PayOffB->legend->setVisible(true);
   ui->Plot_SimuB->xAxis->setRange(0, Expiry, Qt::AlignLeft);
   ui->Plot_SimuB->yAxis->setRange(Spot, 5*Vol*Spot*sqrt(Expiry), Qt::AlignCenter);
   ui->Plot_SimuB->xAxis->setLabel("Temps (en années)");
   ui->Plot_SimuB->yAxis->setLabel("Cours");
   ui->Plot_SimuB->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                   QCP::iSelectLegend | QCP::iSelectPlottables);
  ui->Plot_SimuB->addGraph();
  ui->Plot_SimuB->graph()->setPen(QPen(Qt::blue));
  ui->Plot_SimuB->graph()->setBrush(QBrush(QColor(0, 0, 255, 20)));

// Vecteurs du graphe //

  QVector<double> x(prec);
  QVector<double> y=Simul(pSimuB, prec);
  int precm = prec-1;
  for (int i=0; i<prec; ++i)
  {
      x[i] = (i*Expiry)/precm;
  }

// Graphes //

  ui->Plot_SimuB->graph(0)->setData(x, y);
  ui->Plot_SimuB->axisRect()->setupFullAxesBox(true);
  ui->Plot_SimuB->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  ui->Plot_SimuB->replot();

}


////////////////////////////////// GRAPHE 2 : GRAPHE SIMU LEVY //////////////////////////////////////

void MainWindow::SetupPlotSimuL()
{
    // INITIALISATION DES VALEURS //

        double Spot(0);
        Spot=edSpot();
        double Strike(0);
        Strike=edStrike();
        double Expiry(0);
        Expiry=edExpiry();
        double Vol(0);
        Vol=edVol();
        double r(0);
        r=edr();
        double lambda(0);
        lambda=edlambda();
        double m(0);
        m=edm();
        double vega2(0);
        vega2=edvega2();
        int StopMCType(0);
        if (edMCStop()==false)
            StopMCType=1;
        int TypeOption(0);
        if (edPOC()==true)
            TypeOption=1;
        unsigned long NumberOfPaths(0);
        NumberOfPaths=edNumberOfPaths();
        int secondes(0);
        secondes=edt();


    MonteCarloL pSimuL(Strike, Expiry, Spot, Vol, r, lambda, m, vega2);
// Setup des caractéristiques du graphe //

 ui->Plot_SimuL->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                 QCP::iSelectLegend | QCP::iSelectPlottables);
 ui->Plot_SimuL->xAxis->setRange(0, Expiry, Qt::AlignLeft);
 ui->Plot_SimuL->yAxis->setRange(Spot, 5*Vol*Spot*sqrt(Expiry), Qt::AlignCenter);
 ui->Plot_SimuL->xAxis->setLabel("Temps (en années)");
 ui->Plot_SimuL->yAxis->setLabel("Cours");
 ui->Plot_SimuL->addGraph();
   ui->Plot_SimuL->graph()->setPen(QPen(Qt::red));
   ui->Plot_SimuL->graph()->setBrush(QBrush(QColor(120, 120, 20, 20)));

// Vecteurs du graphe //

   QVector<double> x(prec);
   QVector<double> y=Simul(pSimuL, prec);
   int precm = prec-1;
   for (int i=0; i<prec; ++i)
   {
   x[i] = (i*Expiry)/precm;
   }

// Graphes //

   ui->Plot_SimuL->graph(0)->setData(x, y);
   ui->Plot_SimuL->axisRect()->setupFullAxesBox(true);
   ui->Plot_SimuL->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
   ui->Plot_SimuL->replot();

}

////////////////////////////////// GRAPHE 3 : PAYOFF BROWNIEN //////////////////////////////////////

void MainWindow::SetupPlotPayOffB()
{
    // INITIALISATION DES VALEURS //

        double Spot(0);
        Spot=edSpot();
        double Strike(0);
        Strike=edStrike();
        double Expiry(0);
        Expiry=edExpiry();
        double Vol(0);
        Vol=edVol();
        double r(0);
        r=edr();
        double lambda(0);
        lambda=edlambda();
        double m(0);
        m=edm();
        double vega2(0);
        vega2=edvega2();
        int StopMCType(0);
        if (edMCStop()==false)
            StopMCType=1;
        int TypeOption(0);
        if (edPOC()==true)
            TypeOption=1;
        unsigned long NumberOfPaths(0);
        NumberOfPaths=edNumberOfPaths();
        int secondes(0);
        secondes=edt();

    MonteCarloB pSimuB(Strike, Expiry, Spot, Vol, r);

PayOff* PO;
       if (TypeOption==1)
       {
           PO = new PayOffCall(Strike);
       }
       else
       {
           PO = new PayOffPut(Strike);
       };


// Setup des caractéristiques du graphe //
       ui->Plot_PayOffB->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                       QCP::iSelectLegend | QCP::iSelectPlottables);
   ui->Plot_PayOffB->addGraph();
   ui->Plot_PayOffB->graph()->setPen(QPen(Qt::blue));
   ui->Plot_PayOffB->graph()->setBrush(QBrush(QColor(0, 0, 255, 20)));
   ui->Plot_PayOffB->addGraph();
   QFont legendFont = font();
   legendFont.setPointSize(10);
   ui->Plot_PayOffB->legend->setFont(legendFont);
   ui->Plot_PayOffB->legend->setSelectedFont(legendFont);
   ui->Plot_PayOffB->legend->setSelectableParts(QCPLegend::spItems);
   ui->Plot_PayOffB->xAxis->setRange(0, 2*Spot, Qt::AlignLeft);
   ui->Plot_PayOffB->yAxis->setRange(0, Spot, Qt::AlignLeft);
   ui->Plot_PayOffB->xAxis->setLabel("Spot Price");
   ui->Plot_PayOffB->yAxis->setLabel("Prix de l'option");
   QPen graphPen;
   graphPen.setColor(QColor(51, 204, 0));
   graphPen.setWidthF(2);
   ui->Plot_PayOffB->graph()->setPen(graphPen);

// Vecteurs du graphe //

   QVector<double> x(prec);
   QVector<double> y=gPayO(pSimuB,*PO, prec, Strike, Expiry);
   QVector<double> z=gPayOT(pSimuB,*PO, prec, Strike);
   int precm=prec-1;
   for (int i=0; i<prec; ++i)
    {
     x[i] = (i*Spot*2)/precm;
    }

// Graphes //

   ui->Plot_PayOffB->graph(0)->setData(x, y);
   ui->Plot_PayOffB->graph(0)->setName("Prix aujourd'hui");
   ui->Plot_PayOffB->graph(1)->setData(x, z);
   ui->Plot_PayOffB->graph(1)->setName("Prix à la maturité");
   ui->Plot_PayOffB->axisRect()->setupFullAxesBox(true);
   ui->Plot_PayOffB->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
   ui->Plot_PayOffB->replot();
}


////////////////////////////////// GRAPHE 4 : PAYOFF LEVY //////////////////////////////////////

void MainWindow::SetupPlotPayOffL()
{
    // INITIALISATION DES VALEURS //

        double Spot(0);
        Spot=edSpot();
        double Strike(0);
        Strike=edStrike();
        double Expiry(0);
        Expiry=edExpiry();
        double Vol(0);
        Vol=edVol();
        double r(0);
        r=edr();
        double lambda(0);
        lambda=edlambda();
        double m(0);
        m=edm();
        double vega2(0);
        vega2=edvega2();
        int StopMCType(0);
        if (edMCStop()==false)
            StopMCType=1;
        int TypeOption(0);
        if (edPOC()==true)
            TypeOption=1;
        unsigned long NumberOfPaths(0);
        NumberOfPaths=edNumberOfPaths();
        int secondes(0);
        secondes=edt();

    MonteCarloL pSimuL(Strike, Expiry, Spot, Vol, r, lambda, m, vega2);
    PayOff* PO;
           if (TypeOption==1)
           {
               PO = new PayOffCall(Strike);
           }
           else
           {
               PO = new PayOffPut(Strike);
           };


    // Setup des caractéristiques du graphe //

           ui->Plot_PayOffL->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                           QCP::iSelectLegend | QCP::iSelectPlottables);

           ui->Plot_PayOffL->legend->setVisible(true);
           QFont legendFont = font();
           legendFont.setPointSize(10);
           ui->Plot_PayOffL->legend->setFont(legendFont);
           ui->Plot_PayOffL->legend->setSelectedFont(legendFont);
           ui->Plot_PayOffL->legend->setSelectableParts(QCPLegend::spItems);
           ui->Plot_PayOffL->xAxis->setRange(0, 2*Spot, Qt::AlignLeft);
           ui->Plot_PayOffL->yAxis->setRange(0, Spot, Qt::AlignLeft);
           ui->Plot_PayOffL->xAxis->setLabel("Spot Price");
           ui->Plot_PayOffL->yAxis->setLabel("Prix de l'option");
           ui->Plot_PayOffL->addGraph();
       ui->Plot_PayOffL->graph()->setPen(QPen(Qt::red));
       ui->Plot_PayOffL->graph()->setBrush(QBrush(QColor(120, 120, 20, 20)));
       ui->Plot_PayOffL->addGraph();
       QPen graphPen;
       graphPen.setColor(QColor(51, 204, 0));
       graphPen.setWidthF(2);
       ui->Plot_PayOffL->graph()->setPen(graphPen);

    // Vecteurs du graphe //

       QVector<double> x(prec);
       QVector<double> y=gPayO(pSimuL,*PO, prec, Strike, Expiry);
       QVector<double> z=gPayOT(pSimuL,*PO, prec, Strike);
       int precm=prec-1;
       for (int i=0; i<prec; ++i)
        {
         x[i] = (i*Spot*2)/precm;
        }

    // Graphes //

       ui->Plot_PayOffL->graph(0)->setData(x, y);
       ui->Plot_PayOffL->graph(0)->setName("Prix aujourd'hui");
       ui->Plot_PayOffL->graph(1)->setData(x, z);
       ui->Plot_PayOffL->graph(1)->setName("Prix à la maturité");
       ui->Plot_PayOffL->axisRect()->setupFullAxesBox(true);
       ui->Plot_PayOffL->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
       ui->Plot_PayOffL->replot();
}

void MainWindow::SetupPrices()
{
    // INITIALISATION DES VALEURS //

        double Spot(0);
        Spot=edSpot();
        double Strike(0);
        Strike=edStrike();
        double Expiry(0);
        Expiry=edExpiry();
        double Vol(0);
        Vol=edVol();
        double r(0);
        r=edr();
        double lambda(0);
        lambda=edlambda();
        double m(0);
        m=edm();
        double vega2(0);
        vega2=edvega2();
        int StopMCType(0);
        if (edMCStop()==false)
            StopMCType=1;
        int TypeOption(0);
        if (edPOC()==true)
            TypeOption=1;
        unsigned long NumberOfPaths(0);
        NumberOfPaths=edNumberOfPaths();
        int secondes(0);
        secondes=edt();

MonteCarloB pSimuB(Strike, Expiry, Spot, Vol, r);
MonteCarloL pSimuL(Strike, Expiry, Spot, Vol, r, lambda, m, vega2);


    PayOff* PO;
           if (TypeOption==1)
           {
               PO = new PayOffCall(Strike);
           }
           else
           {
               PO = new PayOffPut(Strike);
           };

    double PrixB;
if (StopMCType==1)
    PrixB= pSimuB.PrixT(secondes, *PO, pSimuB, Spot);
else
    PrixB=pSimuB.PrixA(NumberOfPaths, *PO, pSimuB, Spot);

double PrixL;
if (StopMCType==1)
    PrixL= pSimuL.PrixT(secondes, *PO, pSimuL, Spot);
else
    PrixL=pSimuL.PrixA(NumberOfPaths, *PO, pSimuL, Spot);

ui->RB->setNum(PrixB);
ui->RL->setNum(PrixL);
ui->lSpot->setNum(Spot);
ui->lExpiry->setNum(Expiry);
ui->lStrike->setNum(Strike);
ui->lsigma2->setNum(Vol);
ui->llambda->setNum(lambda);
ui->lm->setNum(m);
ui->tr->setNum(r);
ui->lvega2->setNum(vega2);
ui->lOptionType->setText("Européenne");
if (TypeOption==1)
ui->lCoP->setText("Call");
else ui->lCoP->setText("Put");

QString s = QString::number(NumberOfPaths);

if (StopMCType==0)
{
    ui->SMC->setText("Nombre d'itérations");
ui->lNumberOfPaths->setText(s);
ui->lsecondes->setText("-");
}
else
{
    ui->SMC->setText("Temps de calcul");
    ui->lsecondes->setNum(secondes);
    ui->lNumberOfPaths->setText("-");
}
}

////////////////////////////////// AJOUTER SIMULATIONS DE COURS //////////////////////////////////////

void MainWindow::AddSimuB()
{
    // INITIALISATION DES VALEURS //

        double Spot(0);
        Spot=edSpot();
        double Strike(0);
        Strike=edStrike();
        double Expiry(0);
        Expiry=edExpiry();
        double Vol(0);
        Vol=edVol();
        double r(0);
        r=edr();
        double lambda(0);
        lambda=edlambda();
        double m(0);
        m=edm();
        double vega2(0);
        vega2=edvega2();
        int StopMCType(0);
        if (edMCStop()==false)
            StopMCType=1;
        int TypeOption(0);
        if (edPOC()==true)
            TypeOption=1;
        unsigned long NumberOfPaths(0);
        NumberOfPaths=edNumberOfPaths();
        int secondes(0);
        secondes=edt();


    MonteCarloB pSimuB(Strike, Expiry, Spot, Vol, r);

    // Vecteurs du graphe //

      QVector<double> x(prec);
      QVector<double> y=Simul(pSimuB, prec);
      int precm = prec-1;
      for (int i=0; i<prec; ++i)
      {
          x[i] = (i*Expiry)/precm;
      }

      // Setup des caractéristiques du graphe //

      ui->Plot_SimuB->addGraph();
      ui->Plot_SimuB->graph()->setBrush(QBrush(QColor(0, 0, 255, 20)));

      ui->Plot_SimuB->graph()->setData(x, y);
      QPen graphPen;
      graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
      ui->Plot_SimuB->graph()->setPen(graphPen);
      ui->Plot_SimuB->replot();
}


void MainWindow::AddSimuL()
{
    // INITIALISATION DES VALEURS //

        double Spot(0);
        Spot=edSpot();
        double Strike(0);
        Strike=edStrike();
        double Expiry(0);
        Expiry=edExpiry();
        double Vol(0);
        Vol=edVol();
        double r(0);
        r=edr();
        double lambda(0);
        lambda=edlambda();
        double m(0);
        m=edm();
        double vega2(0);
        vega2=edvega2();
        int StopMCType(0);
        if (edMCStop()==false)
            StopMCType=1;
        int TypeOption(0);
        if (edPOC()==true)
            TypeOption=1;
        unsigned long NumberOfPaths(0);
        NumberOfPaths=edNumberOfPaths();
        int secondes(0);
        secondes=edt();


    // Objet Levy //

    MonteCarloL pSimuL(Strike, Expiry, Spot, Vol, r, lambda, m, vega2);

    // Vecteurs du graphe //

      QVector<double> x(prec);
      QVector<double> y=Simul(pSimuL, prec);
      int precm = prec-1;
      for (int i=0; i<prec; ++i)
      {
          x[i] = (i*Expiry)/precm;
      }

      // Setup des caractéristiques du graphe //

      ui->Plot_SimuL->addGraph();
      ui->Plot_SimuL->graph()->setBrush(QBrush(QColor(225, 102, 102, 40)));

      ui->Plot_SimuL->graph()->setData(x, y);
      QPen graphPen;
      graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
      ui->Plot_SimuL->graph()->setPen(graphPen);
      ui->Plot_SimuL->replot();
}
