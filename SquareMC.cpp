#include "SquareMC.hpp"
#include <cmath>
#include <QRandomGenerator>

SquareMC::SquareMC(QObject *parent) : QObject(parent) {}

double SquareMC::exactArea() const
{
    return (M_PI * M_PI * M_PI) / 3.0;
}

double SquareMC::monteCarloArea(int n) const
{
    if (n <= 0)
        return 0.0;

    int countInside = 0;
    QRandomGenerator *randGen = QRandomGenerator::global();

    for (int i = 0; i < n; ++i)
    {
        double x = (randGen->generateDouble() * 2.0 - 1.0) * M_PI; // x  [-π, π]
        double y = (randGen->generateDouble() * 2.0 - 1.0) * M_PI; // y  [-π, π]

        double rPoint = std::sqrt(x * x + y * y);
        double phi = std::atan2(y, x);

        double rCurve = std::fabs(phi);

        if (rPoint <= rCurve)
            ++countInside;
    }

    // Площадь квадрата [-π, π] x [-π, π]
    double rectArea = 4 * M_PI * M_PI;
    return rectArea * static_cast<double>(countInside) / n;
}

double SquareMC::evaluateAccuracy(int n) const
{
    if (n <= 0)
        return 0.0;

    //double absError = std::fabs(exactArea() - monteCarloArea(n));
    //return (absError / exactArea()) * 100.0; // Относительная ошибка

    return std::fabs(exactArea() - monteCarloArea(n));
}
