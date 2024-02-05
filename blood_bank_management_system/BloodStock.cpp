#include "BloodStock.hpp"
#include "io_utility.hpp"

std::ostream &operator<<(std::ostream &os, const BloodStock &object)
{
    os << object.blood_stock;
    return os;
}

std::istream &operator>>(std::istream &os, BloodStock &object)
{
    os >> object.blood_stock;
    return os;
}