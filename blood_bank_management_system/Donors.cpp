#include "Donors.hpp"
#include "io_utility.hpp"

std::ostream &operator<<(std::ostream &os, const Donors &donors)
{
    os << donors.data;
    return os;
}

std::istream &operator>>(std::istream &is, Donors &donors)
{
    is >> donors.data;
    return is;
}