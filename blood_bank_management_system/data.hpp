#pragma once

#include <vector>
#include <string>
#include <map>

const char nl = '\n';

const std::vector<std::string> choices = {
    "Add donor",
    "Update donor",
    "Add hospital",
    "Donate",
    "Request blood",
    "Display available blood packets",
    "Exit",
};

const std::map<std::string, int> prices = {

    {"O+", 64},
    {"O-", 94},
    {"A+", 63},
    {"A-", 93},
    {"B+", 91},
    {"B-", 99},
    {"AB+", 97},
    {"AB-", 99}

};