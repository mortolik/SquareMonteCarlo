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

    // Новые границы для x и y
    double xMin = -3.14, xMax = 1.6;
    double yMin = -2.2, yMax = 2.2;

    for (int i = 0; i < n; ++i)
    {
        // Генерация x в диапазоне [-1.6, 1.6]
        double x = (randGen->generateDouble() * (xMax - xMin) + xMin);

        // Генерация y в диапазоне [-2.2, 2.2]
        double y = (randGen->generateDouble() * (yMax - yMin) + yMin);

        double rPoint = std::sqrt(x * x + y * y);
        double phi = std::atan2(y, x);

        double rCurve = std::fabs(phi);

        if (rPoint <= rCurve)
            ++countInside;

        result.points.append(QPointF(x, y)); // Добавляем точку в результат
    }

    // Площадь нового прямоугольника
    double rectArea = (xMax - xMin) * (yMax - yMin);
    result.area = rectArea * static_cast<double>(countInside) / n;

    return result;
}

double SquareMC::evaluateAccuracy(int n) const
{
    if (n <= 0)
        return 0.0;

    return std::fabs(exactArea() - monteCarloArea(n).area);
}

double SquareMC::evaluateAverageAccuracy(int n, int iterations) const
{
    if (n <= 0 || iterations <= 0)
        return 0.0;

    double totalError = 0.0;

    for (int i = 0; i < iterations; ++i)
    {
        double mcArea = monteCarloArea(n).area;
        double error = std::fabs(exactArea() - mcArea);
        totalError += error;
    }

    return totalError / iterations;
}
