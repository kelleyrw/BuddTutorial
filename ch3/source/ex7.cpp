#include <iostream>
#include <stdexcept>

using namespace std;

void PrintDigitAsHex(const int n)
{
    // check inputs
    if (n < 0)
    {
        throw std::runtime_error("[PrintDigitAsHex] Error: input must be > 0");
    }

    char result = '\0';
    switch (n)
    {
        case 0 : result = '0'; break;
        case 1 : result = '1'; break;
        case 2 : result = '2'; break;
        case 3 : result = '3'; break;
        case 4 : result = '4'; break;
        case 5 : result = '5'; break;
        case 6 : result = '6'; break;
        case 7 : result = '7'; break;
        case 8 : result = '8'; break;
        case 9 : result = '9'; break;
        case 10: result = 'A'; break;
        case 11: result = 'B'; break;
        case 12: result = 'C'; break;
        case 13: result = 'C'; break;
        case 14: result = 'D'; break;
        case 15: result = 'F'; break;
        default: 
            PrintDigitAsHex(n / 16);
            PrintDigitAsHex(n % 16);
    }
    std::cout << result;
}

void PrintTest(const int n)
{
    try
    {
        cout << n << " = ";
        PrintDigitAsHex(n);
        cout << endl;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << " -- ingoring..." << std::endl;
        return;
    }
}

int main()
{
    using namespace std;

    PrintTest(0);
    PrintTest(7);
    PrintTest(11);
    PrintTest(16);
    PrintTest(17);
    PrintTest(27);
    PrintTest(6666666);
    PrintTest(-12);
    return 0;
}
