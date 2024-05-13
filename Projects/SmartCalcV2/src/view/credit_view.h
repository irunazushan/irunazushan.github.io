#ifndef CREDIT_VIEW_H
#define CREDIT_VIEW_H

#include <QStandardItemModel>
#include <QWidget>

#include "../controller/credit_controller.h"

namespace Ui {
class CreditView;
}

class CreditView : public QWidget {
  Q_OBJECT

 public:
  explicit CreditView(QWidget *parent = nullptr);
  ~CreditView();

 private slots:
  void on_getCreditButton_clicked();

 private:
  Ui::CreditView *ui;
  QStandardItemModel *model;
  s21::CreditCalculatorController *credit_;
};

#endif  // CREDIT_VIEW_H
