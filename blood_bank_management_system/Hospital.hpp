#pragma once
#include <iostream>

#include "data.hpp"

class Hospital
{
private:
    std::string contact{};

public:
    void set_contact(const std::string &other_contact)
    {
        contact = other_contact;
        return;
    }

    void pay(const std::string &abo)
    {
        int price = prices.at(abo);
        std::cout << "The price is " << price << nl;
        return;
    }

    friend std::ostream &operator<<(std::ostream &, const Hospital &);
    friend std::istream &operator>>(std::istream &, Hospital &);
};