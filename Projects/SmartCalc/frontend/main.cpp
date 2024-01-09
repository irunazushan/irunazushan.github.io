#include <QApplication>
#include <locale>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  setlocale(LC_NUMERIC, "C");
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("SmartCalc (@convictw)");
  w.setStyleSheet("background-color:  rgb(114, 138, 182);");
  QSize size = w.size();
  int width = size.width();
  int height = size.height();
  w.setFixedSize(width, height);
  w.show();
  return a.exec();
}
