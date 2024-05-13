#include "deposit_view.h"

#include "ui_deposit_view.h"

DepositView::DepositView(QWidget *parent)
    : QWidget(parent), ui(new Ui::DepositView) {
  ui->setupUi(this);
  setWindowTitle("Deposit calculator");
  setFixedSize(width(), height());
}

DepositView::~DepositView() { delete ui; }

void DepositView::on_getDepositButton_clicked() {
  int fullPeriod = ui->fullPeriod->text().toInt();
  s21::DepositCalculatorModel depModel(
      {ui->depositSum->text().toDouble(), fullPeriod,
       ui->percentageRate->text().toDouble(), ui->taxRate->text().toDouble(),
       ui->keyRate->text().toDouble(),
       ui->capitalization->checkState() ? 1 : 0});
  deposit_ = new s21::DepositCalculatorController(&depModel);
  int rows = ceil((double)fullPeriod / 12.0);
  model = new QStandardItemModel(rows, 5, this);
  ui->depositTable->setModel(model);
  ui->depositTable->verticalHeader()->setVisible(false);
  model->setHeaderData(0, Qt::Horizontal, "Year");
  model->setHeaderData(1, Qt::Horizontal, "Accrued cash");
  model->setHeaderData(2, Qt::Horizontal, "Tax");
  model->setHeaderData(3, Qt::Horizontal, "Cash flow");
  model->setHeaderData(4, Qt::Horizontal, "Balance");
  QModelIndex index;
  for (int i = 0; deposit_->isEndOfIteration(); i++) {
    deposit_->runNextIteration();
    auto report = deposit_->getIterationReport();
    index = model->index(i, 0);
    model->setData(index, QString::number(report[4] / (12), 'd', 1));
    index = model->index(i, 1);
    model->setData(index, QString::number(report[3], 'd', 2));
    index = model->index(i, 2);
    model->setData(index, QString::number(report[1], 'd', 2));
    index = model->index(i, 3);
    model->setData(index, QString::number(report[2], 'd', 2));
    index = model->index(i, 4);
    model->setData(index, QString::number(report[0], 'd', 2));
  }
}
