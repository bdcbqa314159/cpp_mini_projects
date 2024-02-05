#pragma once

#include "Donor.hpp"

class Donors
{
private:
    std::vector<Donor> data{};

public:
    Donors() = default;
    Donors(const std::vector<Donor> &other_data) : data(other_data) {}

    void add(const Donor &donor)
    {
        data.push_back(donor);
        return;
    }

    Donor &operator[](size_t index) { return data.at(index); }
    Donor operator[](size_t index) const { return data.at(index); }

    size_t size() { return data.size(); }

    friend std::ostream &operator<<(std::ostream &, const Donors &);
    friend std::istream &operator>>(std::istream &is, Donors &);
};