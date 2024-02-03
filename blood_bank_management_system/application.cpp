#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

const char nl = '\n';
void adding_donor();
void update_donor();
void donate();
void blood_packets();
void adding_hospital();
void request_blood();

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

std::ostream &
operator<<(std::ostream &, const std::map<size_t, std::string> &);

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

template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::map<T, U> &map)
{
    for (typename std::map<T, U>::const_iterator ii = map.begin(); ii != map.end(); ++ii)
    {
        os << ii->first << " ";
        for (auto item : ii->second)
            os << item << " ";
        os << nl;
    }
    return os;
}

template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::map<T, std::vector<U>> &map)
{
    for (typename std::map<T, std::vector<U>>::const_iterator ii = map.begin(); ii != map.end(); ++ii)
    {
        os << ii->first << " ";
        for (auto item : ii->second)
            os << item << " ";
        os << nl;
    }
    return os;
}

template <class T, class U>
std::istream &operator>>(std::istream &os, std::map<T, std::vector<U>> &map)
{
    std::string line{};
    while (getline(os, line))
    {
        std::istringstream is(line);

        std::string key{};
        is >> key;
        std::vector<U> v{};
        is >> v;
        map[key] = v;
    }
    return os;
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

    std::string get_string() const
    {
        return abo_group;
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

std::ostream &operator<<(std::ostream &os, const Hospital &object)
{
    os << object.contact;
    return os;
}

std::istream &operator>>(std::istream &os, Hospital &object)
{
    os >> object.contact;
    return os;
}

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

std::ostream &operator<<(std::ostream &os, const Hospitals &Hospitals)
{
    os << Hospitals.data;
    return os;
}

std::istream &operator>>(std::istream &is, Hospitals &Hospitals)
{
    is >> Hospitals.data;
    return is;
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
                else if (myMenu(choice) == "Display available blood packets")
                    blood_packets();
                else if (myMenu(choice) == "Add hospital")
                    adding_hospital();
                else if (myMenu(choice) == "Request blood")
                    request_blood();
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

        while (true)
        {
            size_t input{};
            std::string blank{};
            size_t max_items = total_donors_db.size();
            std::cout << "The list of donors is " << nl;
            std::cout << "*****************************" << nl;
            std::cout << total_donors_db << nl;
            std::cout << "*****************************" << nl;
            std::cout << "Give a number (press 0 to quit), limit: " << max_items << " >> ";
            std::cin >> input;

            std::getline(std::cin, blank);

            if (input >= 1 && input <= max_items)
            {
                Donor donor = total_donors_db[input - 1];
                std::cout << "this donor :" << nl;
                std::cout << donor << nl;
                std::cout << "will donate to the blood bank" << nl;

                std::string input{};
                while (true)
                {
                    std::string blank{};
                    std::cout << "Proceed ? Y/N >> ";
                    std::cin >> input;

                    if (input == "Y" || input == "N")
                    {
                        std::cout << "thanks you choose " << input << nl;
                        break;
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

                if (input == "Y")
                {
                    std::cout << "Donor: " << nl << donor << nl << " gave the blood" << nl;
                    std::getline(std::cin, blank);

                    if (donor.get_fit())
                    {
                        std::cout << donor << " in good shape - then we donate" << nl;
                        const std::string file_name = "blood_stock";
                        BloodStock the_blood_stock{};
                        std::ifstream input_file{};

                        input_file.open(file_name);

                        if (input_file.is_open())
                        {
                            input_file >> the_blood_stock;
                            the_blood_stock.update();
                            std::cout << "reconstruction:" << nl;
                        }

                        else
                        {
                            std::cout << "could not open the file" << nl;
                            std::cout << "The bank is empty: " << nl;
                        }
                        input_file.close();

                        std::cout << the_blood_stock << nl;

                        int input{};

                        while (true)
                        {
                            std::string blank{};
                            std::cout << "Give time to expiry up to 12 (months) >> ";
                            std::cin >> input;

                            if (input >= 1 && input <= 12)
                            {
                                std::cout << "thanks press a key to continue" << nl;
                                std::getline(std::cin, blank);
                                break;
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

                        the_blood_stock.add_expiry_donor(donor.get_abo().get_string(), input);

                        std::ofstream output_file{};

                        output_file.open(file_name, std::ofstream::trunc);

                        if (output_file.is_open())
                        {
                            output_file << the_blood_stock << nl;
                            output_file.close();
                            std::cout << "**************************" << nl;
                            std::cout << "Added into " << file_name << " database" << nl;
                            std::cout << "**************************" << nl;
                        }

                        else
                        {
                            std::cout << "could not open the file" << nl;
                            std::abort();
                        }
                    }

                    else
                    {
                        std::cout << donor << " can not donate" << nl;
                        std::cout << "press a key to continue" << nl;
                        std::getline(std::cin, blank);
                        std::system("clear");
                    }
                }

                else
                {
                    std::cout << "Ok we quit this" << nl;
                    std::getline(std::cin, blank);
                    break;
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
    }
    else
    {
        std::cout << "could not read the file" << nl;
        std::abort();
    }

    return;
}

void blood_packets()
{

    const std::string file_name = "blood_stock";
    BloodStock the_blood_stock{};
    std::ifstream input_file{};

    input_file.open(file_name);

    if (input_file.is_open())
    {
        input_file >> the_blood_stock;
        std::cout << "reconstruction:" << nl;
        the_blood_stock.update();
        the_blood_stock.display_summary();
    }

    else
    {
        std::cout << "could not open the file" << nl;
        std::cout << "The bank is empty - we need donors!" << nl;
    }
    input_file.close();

    return;
}

void adding_hospital()
{
    const std::string file_name = "hospitals_db";

    Hospital hospital{};

    std::string input{};

    std::cout << "Enter contact for the hospital" << nl;
    getline(std::cin, input);

    hospital.set_contact(input);

    std::ofstream output_file{};

    output_file.open(file_name, std::ios_base::app);

    if (output_file.is_open())
    {
        output_file << hospital << nl;
        output_file.close();
        std::cout << "**************************" << nl;
        std::cout << hospital << nl;
        std::cout << "Added into " << file_name << " database" << nl;
        std::cout << "**************************" << nl;
    }

    else
    {
        std::cout << "could not open the file" << nl;
        std::abort();
    }
}

void request_blood()
{
    Hospitals total_hospitals_db{};
    const std::string file_name = "hospitals_db";

    std::ifstream input_file{};

    input_file.open(file_name);

    if (input_file.is_open())
    {
        input_file >> total_hospitals_db;
        input_file.close();

        while (true)
        {
            size_t input{};
            size_t max_items = total_hospitals_db.size();
            std::cout << "The list of hospitals is " << nl;
            std::cout << "*****************************" << nl;
            std::cout << total_hospitals_db << nl;
            std::cout << "*****************************" << nl;
            std::cout << "Give a number (press 0 to quit), limit: " << max_items << " >> ";
            std::cin >> input;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), nl);

            if (input >= 1 && input <= max_items)
            {
                Hospital hospital = total_hospitals_db[input - 1];
                std::cout << "this hospital :" << nl;
                std::cout << hospital << nl;
                std::cout << "is asking for blood" << nl;

                const std::string file_name = "blood_stock";
                BloodStock the_blood_stock{};
                std::ifstream input_file{};

                input_file.open(file_name);

                if (input_file.is_open())
                {
                    input_file >> the_blood_stock;
                    the_blood_stock.update();
                    std::cout << "reconstruction:" << nl;
                    std::cout << the_blood_stock << nl;
                }

                else
                {
                    std::cout << "could not open the file" << nl;
                    std::cout << "The bank is empty: " << nl;
                    std::cout << "We can not donate anything - sorry " << nl;
                    break;
                }

                input_file.close();

                while (true)
                {
                    std::string input_abo{};
                    Checker check_blood({"AB+", "AB-", "O+", "O-", "A+", "A-", "B+", "B-"});
                    std::cout << "Which abo do you need ? " << nl;
                    std::getline(std::cin, input_abo);

                    if (check_blood(input_abo))
                    {
                        std::cout << "You choose " << input_abo << nl;
                        the_blood_stock.donate_abo(input_abo);

                        hospital.pay(input_abo);

                        std::cout << "Thanks ... " << nl;
                        std::cout << "Updating database" << nl;

                        std::ofstream output_file{};

                        output_file.open(file_name, std::ofstream::trunc);

                        if (output_file.is_open())
                        {
                            output_file << the_blood_stock << nl;
                            output_file.close();
                            std::cout << "**************************" << nl;
                            std::cout << "Database updated" << nl;
                            std::cout << "**************************" << nl;
                        }

                        else
                        {
                            std::cout << "could not open the file" << nl;
                            std::abort();
                        }

                        break;
                    }

                    else
                    {
                        std::cout << "sorry wrong input" << nl;
                    }
                    std::cout << "press a key to continue" << nl;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), nl);
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), nl);
            std::system("clear");
        }
    }

    else
    {
        std::cout << "could not read the file" << nl;
        std::abort();
    }
    return;
}

int main()
{
    Menu menu(choices);
    Menu menu_donor(choices_donor);

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

std::ostream &operator<<(std::ostream &os, const std::map<size_t, std::string> &map)
{
    for (typename std::map<size_t, std::string>::const_iterator ii = map.begin(); ii != map.end(); ++ii)
    {
        os << ii->first << " " << ii->second << nl;
    }

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

std::istream &operator>>(std::istream &os, BloodStock &object)
{
    os >> object.blood_stock;
    return os;
}
