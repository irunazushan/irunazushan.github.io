#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "math.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_openB, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_closeB, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(add_token()));
  connect(ui->pushButton_clean, SIGNAL(clicked()), this, SLOT(clean_input()));
  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(get_result()));

  ui->graph_screen->xAxis->setRange(-10, 10);
  ui->graph_screen->yAxis->setRange(-10, 10);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::add_token() {
  QPushButton *button = (QPushButton *)sender();
  ui->result_screen->insert(button->text());
  if (button->text().length() >= 2 && button->text() != "mod")
    ui->result_screen->insert("(");
}

void MainWindow::clean_input() { ui->result_screen->clear(); }

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
    get_result();
  } else if (event->key() == Qt::Key_Escape) {
    clean_input();
  } else {
    QMainWindow::keyPressEvent(event);
  }
}

void MainWindow::draw_graph(stack **rpnStack) {
  int noError = OK;
  double resultDbl = 0;
  double x0 = ui->x0->text().toDouble();
  double x1 = ui->x1->text().toDouble();
  double y0 = ui->y0->text().toDouble();
  double y1 = ui->y1->text().toDouble();
  if (x0 < x1 && y0 < y1) {
    ui->graph_screen->xAxis->setRange(x0, x1);
    ui->graph_screen->yAxis->setRange(y0, y1);
    step = 0.0005 * (x1 - x0);
    for (X = x0; X <= x1; X += step) {
      noError = calculation(rpnStack, &resultDbl, X);
      if (noError == OK) {
        x.push_back(X);
        y.push_back(resultDbl);
      }
    }
    ui->graph_screen->addGraph();
    ui->graph_screen->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->graph_screen->graph(0)->setPen(QColor(222, 130, 40, 255));
    ui->graph_screen->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graph_screen->graph(0)->addData(x, y);
    ui->graph_screen->replot();
  } else {
    ui->result_screen->setText("INCORRECT_RANGES");
  }
}

void MainWindow::get_result() {
  QString input_expression = ui->result_screen->text();
  ui->result_screen->clear();
  stack *rawStack = NULL;
  stack *rpnStack = NULL;
  QByteArray byteArray = input_expression.toLocal8Bit();
  char *inputString = new char[byteArray.size() + 1];
  memcpy(inputString, byteArray.data(), byteArray.size());
  inputString[byteArray.size()] = '\0';
  int errorStatus = run_validation(inputString);

  if (errorStatus == OK) {
    expression_to_stack(inputString, &rawStack);
    rpn_stack(&rawStack, &rpnStack);
    QString resultStr = 0;
    double resultDbl = 0;
    x.clear();
    y.clear();
    ui->graph_screen->clearGraphs();
    if (strchr(inputString, 'x') != NULL) {
      errorStatus =
          calculation(&rpnStack, &resultDbl, ui->xArg->text().toDouble());
      if (errorStatus == OK) {
        ui->result_screen->setText(QString::number(resultDbl, 'g', 10));
        draw_graph(&rpnStack);
      }
    } else {
      errorStatus = calculation(&rpnStack, &resultDbl, 0);
      resultStr = QString::number(resultDbl, 'g', 10);
      ui->result_screen->setText(resultStr);
    }
  }
  delete[] inputString;

  if (errorStatus) {
    char *errorMessage = get_error(errorStatus);
    ui->result_screen->setText(errorMessage);
    free(errorMessage);
  }
}

void MainWindow::on_pushButton_pi_clicked() {
  ui->result_screen->insert(QString::number(M_PI, 'g', 10));
}

void MainWindow::on_getCreditButton_clicked() {
  creditData crData = {
      ui->creditSum->text().toDouble(), ui->creditMonth->text().toInt(),
      ui->creditRate->text().toDouble(), ui->diff->isChecked() ? 1 : 0};
  double monthPayment = 0.0, overPayment = 0.0, totalPayment = 0.0;
  int months = 0;
  int rows = (crData.isDiff) ? crData.month : 1;
  model = new QStandardItemModel(rows, 2, this);
  ui->creditTable->setModel(model);
  ui->creditTable->verticalHeader()->setVisible(false);
  model->setHeaderData(0, Qt::Horizontal, "Month");
  model->setHeaderData(1, Qt::Horizontal, "Summ");
  QModelIndex index;
  for (int i = 0; (months < crData.month); i++) {
    credit_calculator(crData, &monthPayment, &overPayment, &totalPayment,
                      &months);
    index = model->index(i, 0);
    model->setData(index, i + 1);
    index = model->index(i, 1);
    model->setData(index, QString::number(monthPayment, 'd', 2));
    if (months == crData.month) {
      ui->overPay->setText(QString::number(overPayment, 'd', 2));
      ui->totalPay->setText(QString::number(totalPayment, 'd', 2));
    }
  }
}

void MainWindow::on_getDepositButton_clicked() {
  depositData depData = {ui->depositSum->text().toDouble(),
                         ui->fullPeriod->text().toInt(),
                         ui->percentageRate->text().toDouble(),
                         ui->taxRate->text().toDouble(),
                         ui->keyRate->text().toDouble(),
                         ui->capitalization->checkState() ? 1 : 0};
  Report report = {0, 0, 0, 0, depData.depositSum};
  int rows = ceil((double)depData.fullPeriod / 12.0);
  model = new QStandardItemModel(rows, 5, this);
  ui->depositTable->setModel(model);
  ui->depositTable->verticalHeader()->setVisible(false);
  model->setHeaderData(0, Qt::Horizontal, "Year");
  model->setHeaderData(1, Qt::Horizontal, "Accrued cash");
  model->setHeaderData(2, Qt::Horizontal, "Tax");
  model->setHeaderData(3, Qt::Horizontal, "Cash flow");
  model->setHeaderData(4, Qt::Horizontal, "Balance");
  QModelIndex index;
  for (int i = 0; report.period < depData.fullPeriod; i++) {
    deposit_calculator(depData, &report);
    index = model->index(i, 0);
    model->setData(index,
                   QString::number((double)report.period / (12), 'd', 1));
    index = model->index(i, 1);
    model->setData(index, QString::number(report.accruedCash, 'd', 2));
    index = model->index(i, 2);
    model->setData(index, QString::number(report.tax, 'd', 2));
    index = model->index(i, 3);
    model->setData(index, QString::number(report.cashFlow, 'd', 2));
    index = model->index(i, 4);
    model->setData(index, QString::number(report.balance, 'd', 2));
  }
}
