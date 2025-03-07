#include "SquareMC.hpp"

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QScatterSeries>

QT_FORWARD_DECLARE_CLASS(QLabel);
QT_FORWARD_DECLARE_CLASS(QLineEdit);
QT_FORWARD_DECLARE_CLASS(QVBoxLayout);
QT_FORWARD_DECLARE_CLASS(QPushButton);

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void calculateMonteCarlo();

private:
    QtCharts::QChartView *chartView;
    QtCharts::QScatterSeries *mcPointsSeries;

    int m_countPoints;

    SquareMC* m_squareMC;

    QLabel* m_exactAreaLabel;
    QLabel* m_mcAreaLabel;
    QLabel* m_mcErrorLabel;

    QPushButton* m_calcButton;
    QLineEdit* m_countPointsLineEdit;
    QVBoxLayout* m_mainLayout;
    QWidget* m_centralWidget;

    void createChart();
    void createUI();
};
