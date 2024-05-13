#include "calculator_view.h"

#include "ui_calculator_view.h"

CalculatorView::CalculatorView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CalculatorView) {
  ui->setupUi(this);
  setWindowTitle("SmartCalcV2 (@convictw)");
  setFixedSize(width(), height());
  InitButtons();
  ui->graph_screen->xAxis->setRange(-10, 10);
  ui->graph_screen->yAxis->setRange(-10, 10);
}

CalculatorView::~CalculatorView() { delete ui; }

void CalculatorView::addToken() {
  QPushButton *button = (QPushButton *)sender();
  ui->result_screen->insert(button->text());
  if (button->text().length() >= 2 && button->text() != "mod")
    ui->result_screen->insert("(");
}

void CalculatorView::cleanInput() { ui->result_screen->clear(); }

void CalculatorView::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
    getResult();
  } else if (event->key() == Qt::Key_Escape) {
    cleanInput();
  } else {
    QMainWindow::keyPressEvent(event);
  }
}

void CalculatorView::getGraph() {
  QString input_expression = ui->result_screen->text();
  QByteArray byteArray = input_expression.toLocal8Bit();
  std::string inputString = byteArray.data();
  s21::CalculatorModel calcModel;
  calc_ = new s21::CalculatorController(&calcModel);
  drawGraph(inputString);
}

void CalculatorView::drawGraph(std::string &inputString) {
  x_.clear();
  y_.clear();
  ui->graph_screen->clearGraphs();
  double x0 = ui->x0->value(), x1 = ui->x1->value(), y0 = ui->y0->value(),
         y1 = ui->y1->value();
  if (x0 < x1 && y0 < y1) {
    ui->graph_screen->xAxis->setRange(x0, x1);
    ui->graph_screen->yAxis->setRange(y0, y1);
    step_ = 0.0005 * (x1 - x0);
    for (X_ = x0; X_ <= x1; X_ += step_) {
      if (!calc_->startCalculator(inputString, X_)) {
        x_.push_back(X_);
        y_.push_back(calc_->getResult());
      }
    }
    ui->graph_screen->addGraph();
    ui->graph_screen->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->graph_screen->graph(0)->setPen(QColor(23, 30, 126, 255));
    ui->graph_screen->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graph_screen->graph(0)->addData(x_, y_);
    ui->graph_screen->setInteraction(QCP::iRangeZoom, true);
    ui->graph_screen->setInteraction(QCP::iRangeDrag, true);
    ui->graph_screen->replot();
  } else {
    ui->result_screen->setText("INCORRECT_RANGES");
  }
}

void CalculatorView::getResult() {
  QString input_expression = ui->result_screen->text();
  ui->result_screen->clear();
  QByteArray byteArray = input_expression.toLocal8Bit();
  std::string inputString = byteArray.data();
  s21::CalculatorModel calcModel;
  calc_ = new s21::CalculatorController(&calcModel);
  QString resultStr = 0;
  int errorStatus = 0;
  if (inputString.find('x') != std::string::npos) {
    errorStatus =
        calc_->startCalculator(inputString, ui->xArg->text().toDouble());
  } else {
    errorStatus = calc_->startCalculator(inputString);
  }
  if (errorStatus == s21::kOk) {
    resultStr = QString::number(calc_->getResult(), 'g', 10);
    ui->result_screen->setText(resultStr);
  } else {
    std::string msg = calc_->getErrorMessage();
    QString str = QString::fromUtf8(msg.c_str());
    ui->result_screen->setText(str);
  }
}

void CalculatorView::onPushButtonPiClicked() {
  ui->result_screen->insert(QString::number(M_PI, 'g', 10));
}

void CalculatorView::openCreditView() {
  CreditView *creditWindow = new CreditView();
  creditWindow->show();
}

void CalculatorView::openDepositView() {
  DepositView *depositWindow = new DepositView();
  depositWindow->show();
}

void CalculatorView::InitButtons() {
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_openB, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_closeB, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(addToken()));
  connect(ui->pushButton_clean, SIGNAL(clicked()), this, SLOT(cleanInput()));
  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(getResult()));
  connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(getGraph()));
  connect(ui->pushButtonCredit, SIGNAL(clicked()), this,
          SLOT(openCreditView()));
  connect(ui->pushButtonDeposit, SIGNAL(clicked()), this,
          SLOT(openDepositView()));
}
