#pragma once
#include <set>

class Checker
{
private:
    std::set<std::string> data{};

public:
    Checker() = default;
    Checker(const std::set<std::string> &other_data) : data(other_data) {}

    void set_data(const std::set<std::string> &other_data)
    {
        data = other_data;
        return;
    }

    bool operator()(const std::string &input) const
    {
        return data.find(input) != data.end();
    }
};
