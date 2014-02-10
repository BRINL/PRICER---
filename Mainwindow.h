#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "../../qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
  void SetupPlotSimuB();
  void SetupPlotSimuL();
  void SetupPlotPayOffB();
  void SetupPlotPayOffL();
  void SetupPrices();
  void graphClicked(QCPAbstractPlottable *plottable);
public slots:
  void AddSimuL();
  void AddSimuB();
  double edStrike();
  double edSpot();
  double edExpiry();
  double edVol();
  double edr();
  double edlambda();
  double edm();
  double edvega2();
  bool edMCStop();
  bool edPOC();
  unsigned long  edNumberOfPaths();
  int edt();

  void update2();



private:
  Ui::MainWindow *ui;
  double Expiry;
  double Spot;
  double Vol;
  double Strike;
  double r;
  unsigned long NumberOfPaths;
  double lambda;
  int TypeOption;
  double m;
  double vega2;
  int secondes;
  int StopMCType;
  int prec;
  int i;
};

#endif // MAINWINDOW_H
