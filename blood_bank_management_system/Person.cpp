#include "Person.hpp"

std::ostream &operator<<(std::ostream &os, const Person &person)
{
    os << person.name;
    return os;
}

std::istream &operator>>(std::istream &is, Person &person)
{
    is >> person.name;
    return is;
}