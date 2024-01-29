#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>

const char nl = '\n';
void adding_donor();
void update_donor();
void donate();

const std::vector<std::string> choices = {
    "Add donor",
    "Update donor",
    "Add hospital",
    "Donate",
    "Request blood",
    "Display available blood packets",
    "Exit",
};

const std::vector<std::string> choices_donor = {
    "Update name",
    "Update contact",
    "Update fitness status",
    "Exit",
};

std::ostream &operator<<(std::ostream &, const std::map<size_t, std::string> &);

std::ostream &operator<<(std::ostream &, const std::map<std::string, std::vector<int>> &);

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << *ii << nl;
    }

    return os;
}

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

    friend std::ostream &operator<<(std::ostream &, const ABO &);
    friend std::istream &operator>>(std::istream &, ABO &);

private:
    std::string abo_group{};
};

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

struct DataMenu
{
    std::map<std::string, std::string> data{};
    std::map<std::string, std::string> operator()(const std::vector<std::string> &);
};

class Menu
{
private:
    std::map<std::string, std::string> data{};
    Checker myChecker{};

public:
    Menu() = default;
    Menu(const std::vector<std::string> &choice_data) : data(DataMenu()(choice_data))
    {
        std::set<std::string> myset{};
        for (size_t i = 1; i <= choice_data.size(); ++i)
            myset.insert(std::to_string(i));
        myChecker.set_data(myset);
    }

    bool check(const std::string &input)
    {
        return myChecker(input);
    }

    std::string operator()(const std::string &input)
    {
        return data[input];
    }

    friend std::ostream &operator<<(std::ostream &, const Menu &);
};

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

    friend std::ostream &operator<<(std::ostream &, const BloodStock &);
};

void menu_interface(Menu &myMenu)
{
    std::string choice{}, blank{};
    std::cout << myMenu << nl;

    while (true)
    {
        std::cout << "Please enter a valid choice  >> ";
        std::getline(std::cin, choice);

        if (myMenu.check(choice))
        {
            if (myMenu(choice) == "Exit")
            {
                std::cout << "Many thanks and bye" << nl;
                std::cout << "press a key to quit" << nl;
                std::getline(std::cin, blank);

                break;
            }

            else
            {
                std::cout << "you choose " << choice << nl;
                std::cout << myMenu(choice) << std::endl;
                if (myMenu(choice) == "Add donor")
                    adding_donor();
                else if (myMenu(choice) == "Update donor")
                    update_donor();
                else if (myMenu(choice) == "Donate")
                    donate();
            }
        }
        else
        {
            std::cout << "Sorry the input is invalid" << nl;
        }
        std::cout << "press a key to continue" << nl;
        std::getline(std::cin, blank);
        std::system("clear");
        std::cout << myMenu << nl;
    }
    std::system("clear");
    return;
}

void adding_name(Donor &donor)
{
    std::string input{};

    std::cout << "Give name >> ";
    std::getline(std::cin, input);
    donor.set_name(input);
    return;
}

void adding_contact(Donor &donor)
{

    std::string input{};
    std::cout << "Give contact >> ";
    std::getline(std::cin, input);
    donor.set_contact(input);
    return;
}

void adding_fitness(Donor &donor)
{
    std::string input{}, blank{};

    while (true)
    {
        std::cout << "Give fit - 0 or 1 >> ";
        std::getline(std::cin, input);

        if (input == "0")
        {
            donor.set_fit(false);
            break;
        }

        else if (input == "1")
        {
            donor.set_fit(true);
            break;
        }

        else
        {
            std::cout << "Sorry the input is invalid" << nl;
        }
        std::cout << "press a key to continue" << nl;
        std::getline(std::cin, blank);
        std::system("clear");
    }
    return;
}

void adding_abo(Donor &donor)
{
    std::string input{}, blank{};

    Checker check_blood({"AB+", "AB-", "O+", "O-", "A+", "A-", "B+", "B-"});
    while (true)
    {
        std::cout << "Give blood group >> ";
        std::getline(std::cin, input);

        if (check_blood(input))
        {
            donor.set_abo(input);
            break;
        }

        else
        {
            std::cout << "Sorry the input is invalid" << nl;
        }
        std::cout << "press a key to continue" << nl;
        std::getline(std::cin, blank);
        std::system("clear");
    }

    return;
}

Donor building_donor()
{

    Donor output{};

    adding_name(output);
    adding_contact(output);
    adding_fitness(output);
    adding_abo(output);

    return output;
}

void adding_donor()
{

    const std::string file_name = "donors_db";

    Donor current_donor = building_donor();

    std::ofstream output_file{};

    output_file.open(file_name, std::ios_base::app);

    if (output_file.is_open())
    {
        output_file << current_donor << nl;
        output_file.close();
        std::cout << "**************************" << nl;
        std::cout << current_donor << nl;
        std::cout << "Added into " << file_name << " database" << nl;
        std::cout << "**************************" << nl;
    }

    else
    {
        std::cout << "could not open the file" << nl;
        std::abort();
    }

    return;
}

void update_donor()
{
    Donors total_donors_db{};
    const std::string file_name = "donors_db";

    std::ifstream input_file{};

    input_file.open(file_name);

    if (input_file.is_open())
    {
        input_file >> total_donors_db;
        input_file.close();

        std::cout << "the list of donors is " << nl;
        std::cout << total_donors_db << nl;

        while (true)
        {
            size_t input{};
            std::string blank{};
            std::cout << "Give a number >> ";
            std::cin >> input;
            size_t max_items = total_donors_db.size();
            std::getline(std::cin, blank);
            if (input >= 1 && input <= max_items)
            {
                Donor to_change = total_donors_db[input - 1];
                std::cout << "this donor :" << nl;
                std::cout << to_change << nl;
                std::cout << "will be changed" << nl;

                Donor current_donor = building_donor();
                total_donors_db[input - 1] = current_donor;
                std::cout << nl << nl;
                std::cout << "After modification" << nl << total_donors_db << nl;

                std::ofstream output_file{};
                output_file.open(file_name);

                if (output_file.is_open())
                {
                    output_file << total_donors_db;
                    output_file.close();
                    break;
                }

                else
                {
                    std::cout << "could not read the file" << nl;
                    std::abort();
                }
            }
            else
            {
                std::cout << "Sorry the input is invalid" << nl;
            }
            std::cout << "press a key to continue" << nl;
            std::getline(std::cin, blank);
            std::system("clear");
        }
        return;
    }

    else
    {
        std::cout << "could not read the file" << nl;
        std::abort();
    }
}

void donate()
{
    Donors total_donors_db{};
    const std::string file_name = "donors_db";

    std::ifstream input_file{};

    input_file.open(file_name);

    if (input_file.is_open())
    {
        input_file >> total_donors_db;
        input_file.close();

        std::cout << "the list of donors is " << nl;
        std::cout << total_donors_db << nl;

        while (true)
        {
            size_t input{};
            std::string blank{};
            std::cout << "Give a number (press 0 to quit)>> ";
            std::cin >> input;
            size_t max_items = total_donors_db.size();
            std::getline(std::cin, blank);
            if (input >= 1 && input <= max_items)
            {
                Donor donor = total_donors_db[input - 1];
                std::cout << "this donor :" << nl;
                std::cout << donor << nl;
                std::cout << "will donate to the blood bank" << nl;

                while (true)
                {
                    std::string input{};
                    std::string blank{};
                    std::cout << "Proceed ? Y/N >> ";
                    std::cin >> input;

                    if (input == "Y" || input == "N")
                    {
                        if (input == "Y")
                        {
                            std::cout << "Donor: " << nl << donor << nl << " gave the blood" << nl;
                            std::getline(std::cin, blank);

                            if (donor.get_fit())
                            {
                                std::cout << donor << " in good shape" << nl;
                            }

                            else
                            {
                                std::cout << donor << " can not donate" << nl;
                                std::getline(std::cin, blank);
                                break;
                            }
                        }
                        else
                        {
                            std::cout << "Ok we quit this" << nl;
                            std::getline(std::cin, blank);
                            break;
                        }
                    }

                    else
                    {
                        std::cout << "Sorry the input is invalid" << nl;
                        std::getline(std::cin, blank);
                    }
                    std::cout << "press a key to continue" << nl;
                    std::getline(std::cin, blank);
                    std::system("clear");
                }
            }

            else if (input == 0)
            {
                std::cout << "Ah ok - we quit" << nl;
                break;
            }

            else
            {
                std::cout << "Sorry the input is invalid" << nl;
            }
            std::cout << "press a key to continue" << nl;
            std::getline(std::cin, blank);
            std::system("clear");
        }
        return;
    }

    else
    {
        std::cout << "could not read the file" << nl;
        std::abort();
    }
}

int main()
{
    Menu menu(choices);
    Menu menu_donor(choices_donor);
    // Checker check_blood({"AB+", "AB-", "O+", "O-", "A+", "A-", "B+", "B-"});

    menu_interface(menu);

    return 0;
}

std::ostream &operator<<(std::ostream &os, const Person &person)
{
    os << person.name;
    return os;
}

std::istream &operator>>(std::istream &is, Person &person)
{
    is >> person.name;
    return is;
}

std::ostream &operator<<(std::ostream &os, const Donor &donor)
{
    os << donor.name << " " << donor.contact << " " << donor.fit << " " << donor.abo;
    return os;
}

std::istream &operator>>(std::istream &is, Donor &donor)
{
    is >> donor.name >> donor.contact >> donor.fit >> donor.abo;
    return is;
}

std::ostream &operator<<(std::ostream &os, const ABO &group)
{
    os << group.abo_group;
    return os;
}

std::istream &operator>>(std::istream &is, ABO &group)
{
    is >> group.abo_group;
    return is;
}

std::ostream &operator<<(std::ostream &os, const std::map<std::string, std::string> &map)
{
    for (auto it = map.begin(); it != map.end(); it++)
        os << it->first << " " << it->second << nl;
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::map<std::string, std::vector<int>> &map)
{
    for (auto it = map.begin(); it != map.end(); it++)
        os << it->first << " " << it->second << nl;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Menu &menu)
{
    os << menu.data;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Donors &donors)
{
    os << donors.data;
    return os;
}

std::istream &operator>>(std::istream &is, Donors &donors)
{
    is >> donors.data;
    return is;
}

std::map<std::string, std::string> DataMenu::operator()(const std::vector<std::string> &choices)
{

    std::map<std::string, std::string> map{};
    for (size_t i = 0; i < choices.size(); i++)
        map.insert(std::make_pair(std::to_string(i + 1), choices.at(i)));

    return map;
}

std::ostream &operator<<(std::ostream &os, const BloodStock &object)
{
    os << object.blood_stock;
    return os;
}