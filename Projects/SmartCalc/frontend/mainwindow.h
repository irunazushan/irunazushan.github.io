#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QStandardItemModel>

extern "C" {
#include "../backend/s21_smart_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void add_token();
  void get_result();
  void clean_input();
  void keyPressEvent(QKeyEvent *event);
  void on_pushButton_pi_clicked();
  void draw_graph(stack **rpnStack);
  void on_getCreditButton_clicked();

  void on_getDepositButton_clicked();

 private:
  Ui::MainWindow *ui;
  QStandardItemModel *model;
  double X, step;
  QVector<double> x, y;
};
#endif  // MAINWINDOW_H
