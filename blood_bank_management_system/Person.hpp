#pragma once

#include <iostream>
#include <string>

class Person
{
protected:
    std::string name{};

public:
    Person() = default;
    Person(const std::string &other_name) : name(other_name) {}

    void set_name(const std::string &other_name)
    {
        name = other_name;
        return;
    }

    friend std::ostream &operator<<(std::ostream &, const Person &);
    friend std::istream &operator>>(std::istream &is, Person &);
};