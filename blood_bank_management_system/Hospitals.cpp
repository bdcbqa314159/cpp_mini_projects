#include "Hospitals.hpp"
#include "io_utility.hpp"

std::ostream &operator<<(std::ostream &os, const Hospitals &Hospitals)
{
    os << Hospitals.data;
    return os;
}

std::istream &operator>>(std::istream &is, Hospitals &Hospitals)
{
    is >> Hospitals.data;
    return is;
}