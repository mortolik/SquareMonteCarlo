#include "SquareMC.hpp"
#include "qpoint.h"
#include <cmath>
#include <QRandomGenerator>

SquareMC::SquareMC(QObject *parent) : QObject(parent) {}

double SquareMC::exactArea() const
{
    return (M_PI * M_PI * M_PI) / 3.0;
}

MonteCarloResult SquareMC::monteCarloArea(int n) const
{
    MonteCarloResult result;
    result.area = 0.0;

    if (n <= 0)
        return result;

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

        result.points.append(QPointF(x, y)); // Добавляем точку в результат
    }

    // Площадь квадрата [-π, π] x [-π, π]
    double rectArea = 4 * M_PI * M_PI;
    result.area = rectArea * static_cast<double>(countInside) / n;

    return result;
}

double SquareMC::evaluateAccuracy(int n) const
{
    if (n <= 0)
        return 0.0;

    return std::fabs(exactArea() - monteCarloArea(n).area);
}
