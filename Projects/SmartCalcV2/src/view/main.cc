#include <QApplication>

#include "calculator_view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  CalculatorView window;

  window.show();
  return a.exec();
}
