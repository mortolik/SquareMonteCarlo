#include "SquareMC.hpp"
#include <cmath>
#include <QRandomGenerator>

SquareMC::SquareMC(QObject *parent) : QObject(parent) {}

double SquareMC::exactArea() const
{
    return M_PI * M_PI;
}

double SquareMC::monteCarloArea(int n) const
{
    if (n <= 0) return 0.0;

    int countInside = 0;
    QRandomGenerator *randGen = QRandomGenerator::global();

    for (int i = 0; i < n; ++i)
    {
        double x = randGen->generateDouble() * (2 * M_PI) - M_PI; // x ∈ [-π, π]
        double y = randGen->generateDouble() * M_PI;              // y ∈ [0, π]

        if (y <= fabs(x))
            ++countInside;
    }

    double rectArea = 2 * M_PI * M_PI;
    return rectArea * static_cast<double>(countInside) / n;
}
