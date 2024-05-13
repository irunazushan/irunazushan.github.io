#ifndef CALCULATOR_VIEW_H
#define CALCULATOR_VIEW_H

#include <QKeyEvent>
#include <QMainWindow>

#include "../controller/calculator_controller.h"
#include "credit_view.h"
#include "deposit_view.h"

namespace Ui {
class CalculatorView;
}

class CalculatorView : public QMainWindow {
  Q_OBJECT

 public:
  explicit CalculatorView(QWidget *parent = nullptr);
  ~CalculatorView();

 private slots:
  void InitButtons();
  void addToken();
  void getResult();
  void getGraph();
  void cleanInput();
  void keyPressEvent(QKeyEvent *event);
  void onPushButtonPiClicked();
  void drawGraph(std::string &inputString);
  void openDepositView();
  void openCreditView();

 private:
  Ui::CalculatorView *ui;
  s21::CalculatorController *calc_;
  double X_, step_;
  QVector<double> x_, y_;
};

#endif  // CALCULATOR_VIEW_H
