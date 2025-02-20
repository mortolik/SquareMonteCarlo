#include "SquareMC.hpp"

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_FORWARD_DECLARE_CLASS(QLabel);
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

    SquareMC* squareMC;
    QLabel *exactAreaLabel;
    QLabel *mcAreaLabel;
    QLabel *m_mcErrorLabel;
    QPushButton *calcButton;
    QVBoxLayout *mainLayout;
    QWidget *centralWidget;

    void createChart();
    void createUI();
};
