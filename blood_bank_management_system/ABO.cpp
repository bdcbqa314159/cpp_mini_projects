#include "ABO.hpp"

std::ostream &operator<<(std::ostream &os, const ABO &group)
{
    os << group.abo_group;
    return os;
}

std::istream &operator>>(std::istream &is, ABO &group)
{
    is >> group.abo_group;
    return is;
}