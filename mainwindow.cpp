#include "mainwindow.h"
#include <QtCharts/QValueAxis>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), chartView(new QtCharts::QChartView(this))
{
    createChart();
    setCentralWidget(chartView);
}

MainWindow::~MainWindow() {}

void MainWindow::createChart()
{
    QtCharts::QChart *chart = new QtCharts::QChart();
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();

    int points = 200; // Больше точек для гладкости
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
