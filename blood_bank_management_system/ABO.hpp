#pragma once

#include <iostream>

class ABO
{
public:
    ABO() = default;
    ABO(const std::string &group) : abo_group(group) {}
    ABO(const std::string &&group) : abo_group(group) {}

    ABO &operator=(const ABO &other)
    {
        if (this != &other)
            abo_group = other.abo_group;

        return *this;
    }

    std::string get_string() const
    {
        return abo_group;
    }

    friend std::ostream &operator<<(std::ostream &, const ABO &);
    friend std::istream &operator>>(std::istream &, ABO &);

private:
    std::string abo_group{};
};