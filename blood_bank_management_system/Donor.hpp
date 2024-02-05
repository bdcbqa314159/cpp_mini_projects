#pragma once

#include "Person.hpp"
#include "ABO.hpp"

class Donor : public Person
{
private:
    std::string contact{};
    bool fit{};
    ABO abo{};

public:
    Donor() = default;
    Donor(const Person &other) : Person(other), contact{}, fit{}, abo{} {}

    void set_contact(const std::string &other_contact)
    {
        contact = other_contact;
        return;
    }

    void set_fit(const bool &other_fit)
    {
        fit = other_fit;
        return;
    }

    ABO get_abo() const
    {
        return abo;
    }

    void set_abo(const ABO &other_abo)
    {
        abo = other_abo;
        return;
    }

    bool get_fit()
    {
        return fit;
    }

    friend std::ostream &operator<<(std::ostream &, const Donor &);
    friend std::istream &operator>>(std::istream &is, Donor &);
};
