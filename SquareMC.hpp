#pragma once

#include <QObject>

struct MonteCarloResult
{
    double area;
    QVector<QPointF> points;
};
class SquareMC : public QObject
{
    Q_OBJECT

public:
    explicit SquareMC(QObject *parent = nullptr);

    double exactArea() const;
    MonteCarloResult monteCarloArea(int n) const;
    double evaluateAccuracy(int n) const;
};
