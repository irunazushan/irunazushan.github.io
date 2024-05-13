#ifndef DEPOSIT_VIEW_H
#define DEPOSIT_VIEW_H

#include <QStandardItemModel>
#include <QWidget>

#include "../controller/deposit_controller.h"

namespace Ui {
class DepositView;
}

class DepositView : public QWidget {
  Q_OBJECT

 public:
  explicit DepositView(QWidget *parent = nullptr);
  ~DepositView();

 private slots:
  void on_getDepositButton_clicked();

 private:
  Ui::DepositView *ui;
  QStandardItemModel *model;
  s21::DepositCalculatorController *deposit_;
};

#endif  // DEPOSIT_VIEW_H
