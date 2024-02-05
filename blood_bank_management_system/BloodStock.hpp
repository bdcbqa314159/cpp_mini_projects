#pragma once
#include <iostream>
#include <map>
#include <set>

#include "Checker.hpp"
#include "data.hpp"

class BloodStock
{
private:
    std::map<std::string, std::vector<int>> blood_stock{};

public:
    BloodStock()
    {
        std::set<std::string> types = {
            "AB+",
            "AB-",
            "O+",
            "O-",
            "A+",
            "A-",
            "B+",
            "B-"};

        for (auto type : types)
        {
            blood_stock.insert(std::pair<std::string, std::vector<int>>(type, {}));
        }
    }

    bool check(const std::string &input)
    {
        Checker check_blood({"AB+", "AB-", "O+", "O-", "A+", "A-", "B+", "B-"});
        return check_blood(input);
    }

    void add_expiry_donor(const std::string &abo, int expiry)
    {
        if (check(abo))
            blood_stock[abo].push_back(expiry);

        return;
    }

    void display_summary()
    {
        for (auto it = blood_stock.begin(); it != blood_stock.end(); it++)
        {
            std::cout << it->first << " : " << it->second.size() << " packets." << nl;
        }
        return;
    }

    bool donate_abo(const std::string &abo)
    {
        if (check(abo))
        {
            if (blood_stock[abo].size() > 0)
            {
                std::sort(blood_stock.at(abo).begin(), blood_stock.at(abo).end(), std::greater<int>());
                std::cout << "This expiration has been donated: " << blood_stock.at(abo).back() << nl;
                blood_stock.at(abo).pop_back();
                return true;
            }

            else
            {
                std::cout << "Sorry we don't have this " << abo << " in our bank" << nl;
                return false;
            }
        }

        return false;
    }

    void update()
    {
        blood_stock.erase("");
        return;
    }

    friend std::ostream &operator<<(std::ostream &, const BloodStock &);
    friend std::istream &operator>>(std::istream &, BloodStock &);
};