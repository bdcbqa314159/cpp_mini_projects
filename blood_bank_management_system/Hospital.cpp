#include "Hospital.hpp"
#include "io_utility.hpp"

std::ostream &operator<<(std::ostream &os, const Hospital &object)
{
    os << object.contact;
    return os;
}

std::istream &operator>>(std::istream &os, Hospital &object)
{
    os >> object.contact;
    return os;
}