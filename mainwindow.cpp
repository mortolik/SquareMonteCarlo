#include "mainwindow.h"

#include <cmath>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtCharts/QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), chartView(new QtCharts::QChartView(this))
{
    createChart();
    createUI();

    setCentralWidget(m_centralWidget);
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
    m_centralWidget = new QWidget(this);
    m_mainLayout = new QVBoxLayout(m_centralWidget);

    QLabel* pointsLable = new QLabel("Количество точек:", this);
    m_countPointsLineEdit = new QLineEdit("10000");
    QHBoxLayout *pointsLAyout = new QHBoxLayout();
    pointsLAyout->addWidget(pointsLable);
    pointsLAyout->addWidget(m_countPointsLineEdit);

    m_exactAreaLabel = new QLabel(QString("Точная площадь: %1").arg(m_squareMC->exactArea()), this);
    m_mcAreaLabel = new QLabel("Приближенная площадь: ---", this);
    m_mcErrorLabel = new QLabel("Точность метода: ---", this);
    m_calcButton = new QPushButton("Запустить Монте-Карло", this);

    connect(m_calcButton, &QPushButton::clicked, this, &MainWindow::calculateMonteCarlo);

    m_mainLayout->addWidget(chartView);
    m_mainLayout->addLayout(pointsLAyout);
    m_mainLayout->addWidget(m_exactAreaLabel);
    m_mainLayout->addWidget(m_mcAreaLabel);
    m_mainLayout->addWidget(m_mcErrorLabel);
    m_mainLayout->addWidget(m_calcButton);

    m_centralWidget->setLayout(m_mainLayout);
}

void MainWindow::calculateMonteCarlo()
{

    m_countPoints = m_countPointsLineEdit->text().toInt();
    double mcArea = m_squareMC->monteCarloArea(m_countPoints);
    m_mcAreaLabel->setText(QString("Приближенная площадь (%1 точек): %2").arg(m_countPoints).arg(mcArea));
    double error = m_squareMC->evaluateAccuracy(m_countPoints);
    m_mcErrorLabel->setText(QString("Точность метода %1").arg(error));
}
