#include "mainwindow.h"

#include <cmath>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtCharts/QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), chartView(new QtCharts::QChartView(this))
{
    createChart();
    createUI();

    setCentralWidget(centralWidget);
    setMinimumSize(800, 800);
}

MainWindow::~MainWindow() {}

void MainWindow::createChart()
{
    QtCharts::QChart *chart = new QtCharts::QChart();
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();

    int points = 200;
    double step = 2 * M_PI / points;

    for (double phi = -M_PI; phi <= M_PI; phi += step)
    {
        double r = fabs(phi); // r = |phi|
        double x = r * cos(phi);
        double y = r * sin(phi);
        series->append(x, y);
    }

    chart->addSeries(series);
    chart->setTitle("График кривой r = |φ|");

    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis();
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisX->setRange(-M_PI, M_PI);
    axisY->setRange(-M_PI, M_PI);

    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);

    chartView->setChart(chart);
}

void MainWindow::createUI()
{
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    exactAreaLabel = new QLabel(QString("Точная площадь: %1").arg(squareMC.exactArea()), this);
    mcAreaLabel = new QLabel("Приближенная площадь: ---", this);
    calcButton = new QPushButton("Запустить Монте-Карло", this);

    connect(calcButton, &QPushButton::clicked, this, &MainWindow::calculateMonteCarlo);

    mainLayout->addWidget(chartView);
    mainLayout->addWidget(exactAreaLabel);
    mainLayout->addWidget(mcAreaLabel);
    mainLayout->addWidget(calcButton);

    centralWidget->setLayout(mainLayout);
}

void MainWindow::calculateMonteCarlo()
{
    int n = 100000;
    double mcArea = squareMC.monteCarloArea(n);
    mcAreaLabel->setText(QString("Приближенная площадь (%1 точек): %2").arg(n).arg(mcArea));
}
