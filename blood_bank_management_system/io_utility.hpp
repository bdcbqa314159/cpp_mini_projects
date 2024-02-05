#pragma once
#include <iostream>
#include <map>

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

std::ostream &operator<<(std::ostream &os, const std::map<std::string, std::string> &map);