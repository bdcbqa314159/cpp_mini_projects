#include "Donor.hpp"

std::ostream &operator<<(std::ostream &os, const Donor &donor)
{
    os << donor.name << " " << donor.contact << " " << donor.fit << " " << donor.abo;
    return os;
}

std::istream &operator>>(std::istream &is, Donor &donor)
{
    is >> donor.name >> donor.contact >> donor.fit >> donor.abo;
    return is;
}