#include "SquareMC.hpp"
#include <cmath>

SquareMC::SquareMC(QObject *parent) : QObject(parent) {}

double SquareMC::exactArea() const
{
    return M_PI * M_PI;
}
