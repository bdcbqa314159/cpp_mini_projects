#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>

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

const std::vector<std::string> choices_donor = {
    "Update name",
    "Update contact",
    "Update fitness status",
    "Exit",
};

std::ostream &operator<<(std::ostream &, const std::map<size_t, std::string> &);

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << *ii << " ";
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

void donors_database()
{

    std::cout << "Playing with donors" << nl;
    return;
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
    // ABO(const ABO &other) : abo_group(other.abo_group) {}

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

    friend std::ostream &operator<<(std::ostream &, const Donors &);
    friend std::istream &operator>>(std::istream &is, Donors &);
};

void example_for_data_bin()
{

    Person me = {"Bernardo"};
    Person you = {"Alexia"};
    Person her = {"Delphine"};
    std::cout << me << nl;

    std::vector<Person> all = {me, you, her};

    std::vector<Donor> all_1 = {me, you, her};

    for (auto &person : all_1)
    {
        person.set_contact("someone");
        person.set_fit(true);
        person.set_abo({"O+"});
    }

    // for (auto person : all_1)
    //     std::cout << person << nl;

    std::string filename = "test_person";
    std::ofstream output_file{};

    output_file.open(filename);

    if (output_file.is_open())
    {
        for (auto person : all_1)
            output_file << person << nl;
        output_file.close();
    }

    else
    {
        std::cout << "could not open the file" << nl;
        std::abort();
    }

    Donor other{};

    std::ifstream input_file{};

    std::vector<Donor> test{};

    input_file.open(filename);

    if (input_file.is_open())
    {
        while (input_file >> other)
        {
            test.push_back(other);
        }
        input_file.close();
        std::cout << "end of file: " << nl;
        for (auto person : test)
            std::cout << person << nl;
    }

    else
    {
        std::cout << "could not read the file" << nl;
        std::abort();
    }
}

void example_for_data_donors()
{

    Person me = {"Bernardo"};
    Person you = {"Alexia"};
    Person her = {"Delphine"};

    std::vector<Donor> all_1 = {me, you, her};

    for (auto &person : all_1)
    {
        person.set_contact("someone");
        person.set_fit(true);
        person.set_abo({"O+"});
    }

    std::cout << all_1 << nl;

    std::string filename = "test_person";
    std::ofstream output_file{};

    output_file.open(filename);

    if (output_file.is_open())
    {
        output_file << all_1;
        output_file.close();
    }

    else
    {
        std::cout << "could not open the file" << nl;
        std::abort();
    }

    Donors other{};

    std::ifstream input_file{};

    // std::vector<Donor> test{};

    input_file.open(filename);

    if (input_file.is_open())
    {
        input_file >> other;
        input_file.close();
        std::cout << "end of file: " << nl;
        std::cout << other << nl;
    }

    else
    {
        std::cout << "could not read the file" << nl;
        std::abort();
    }
}

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
                break;
            }

            else
            {
                std::cout << "you choose " << choice << nl;
                std::cout << myMenu(choice) << std::endl;
                // listener on myMenu
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
}

int main()
{
    Menu menu(choices);
    Menu menu_donor(choices_donor);
    Checker check_blood({"AB+", "AB-", "O+", "O-", "A+", "A-", "B+", "B-"});

    menu_interface(menu);

    // example_for_data_bin();
    // example_for_data_donors();

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