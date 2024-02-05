#pragma once

#include <vector>
#include "Hospital.hpp"

class Hospitals
{
private:
    std::vector<Hospital> data{};

public:
    Hospitals() = default;
    Hospitals(const std::vector<Hospital> &other_data) : data(other_data) {}

    void add(const Hospital &hospital)
    {
        data.push_back(hospital);
        return;
    }

    Hospital &operator[](size_t index) { return data.at(index); }
    Hospital operator[](size_t index) const { return data.at(index); }

    size_t size() { return data.size(); }

    friend std::ostream &operator<<(std::ostream &, const Hospitals &);
    friend std::istream &operator>>(std::istream &is, Hospitals &);
};