#include "credit_view.h"

#include "ui_credit_view.h"

CreditView::CreditView(QWidget *parent)
    : QWidget(parent), ui(new Ui::CreditView) {
  ui->setupUi(this);
  setWindowTitle("Credit calculator");
  setFixedSize(width(), height());
}

CreditView::~CreditView() { delete ui; }

void CreditView::on_getCreditButton_clicked() {
  int isDiff = ui->diff->isChecked() ? 1 : 0;
  int month = ui->creditMonth->text().toInt();
  s21::CreditCalculatorModel creditModel(
      {ui->creditSum->text().toDouble(), month,
       ui->creditRate->text().toDouble(), isDiff});
  credit_ = new s21::CreditCalculatorController(&creditModel);
  int rows = (isDiff) ? month : 1;
  model = new QStandardItemModel(rows, 2, this);
  ui->creditTable->setModel(model);
  ui->creditTable->verticalHeader()->setVisible(false);
  model->setHeaderData(0, Qt::Horizontal, "Month");
  model->setHeaderData(1, Qt::Horizontal, "Sum");
  QModelIndex index;
  for (int i = 0; credit_->isEndOfIteration(); ++i) {
    credit_->runNextIteration();
    index = model->index(i, 0);
    model->setData(index, i + 1);
    index = model->index(i, 1);
    model->setData(index,
                   QString::number(credit_->getIterationReport()[0], 'd', 2));
    if (i + 1 == month || !isDiff) {
      ui->overPay->setText(
          QString::number(credit_->getIterationReport()[1], 'd', 2));
      ui->totalPay->setText(
          QString::number(credit_->getIterationReport()[2], 'd', 2));
    }
  }
}
