#pragma once

#include <QObject>

class SquareMC : public QObject
{
    Q_OBJECT

public:
    explicit SquareMC(QObject *parent = nullptr);

    double exactArea() const;
};
