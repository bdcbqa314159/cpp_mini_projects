#pragma once
#include <iostream>
#include <map>
#include "data.hpp"

template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v)
{
    T element{};
    while (is >> element)
    {
        v.push_back(element);
    }

    return is;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << *ii << nl;
    }

    return os;
}

std::ostream &operator<<(std::ostream &os, const std::map<std::string, std::string> &map);