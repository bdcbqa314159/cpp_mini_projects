#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

#include "Hospitals.hpp"
#include "Donors.hpp"
#include "BloodStock.hpp"
#include "Menu.hpp"

void adding_donor();
void update_donor();
void donate();
void blood_packets();
void adding_hospital();
void request_blood();

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

    menu_interface(menu);

    return 0;
}
