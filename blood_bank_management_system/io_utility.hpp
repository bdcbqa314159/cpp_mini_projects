#pragma once
#include <iostream>
#include <map>
#include <sstream>
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

template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::map<T, U> &map)
{
    for (typename std::map<T, U>::const_iterator ii = map.begin(); ii != map.end(); ++ii)
    {
        os << ii->first << " ";
        for (auto item : ii->second)
            os << item << " ";
        os << nl;
    }
    return os;
}

template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::map<T, std::vector<U>> &map)
{
    for (typename std::map<T, std::vector<U>>::const_iterator ii = map.begin(); ii != map.end(); ++ii)
    {
        os << ii->first << " ";
        for (auto item : ii->second)
            os << item << " ";
        os << nl;
    }
    return os;
}

template <class T, class U>
std::istream &operator>>(std::istream &os, std::map<T, std::vector<U>> &map)
{
    std::string line{};
    while (getline(os, line))
    {
        std::istringstream is(line);

        std::string key{};
        is >> key;
        std::vector<U> v{};
        is >> v;
        map[key] = v;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::map<std::string, std::string> &map);