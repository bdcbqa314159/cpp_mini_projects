#include <iostream>

int main()
{
    std::cout << "All numbers divisble by 3 within the interval [1,30]" << std::endl;

    unsigned int count = 0;

    for (int i = 1; i <= 30; i++)
    {
        if (i % 3 == 0)
        {
            std::cout << i << " is divisible by 3" << std::endl;
            count++;
        }
    }

    std::cout << "At the end we have " << count << " numbers divisible by 3" << std::endl;

    std::cout << "All numbers divisble by 11 within the interval [1,100]" << std::endl;

    count = 0;
    for (int i = 1; i <= 100; i++)
    {
        if (i % 11 == 0)
        {
            std::cout << i << " is divisible by 11" << std::endl;
            count++;
        }
    }

    std::cout << "At the end we have " << count << " numbers divisible by 11" << std::endl;

    std::cout << "And obviously we have " << 30 - count << " numbers not divisible by 3 within [1,30]" << std::endl;

    return 0;
}