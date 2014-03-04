// -------------------------- //
// examples from 4.2.2
// -------------------------- //

#include <stdexcept>

// example of O(n)
double Minimum(const double values[], const unsigned int n)
{
    // make sure there is a least one element
    if (n < 1)
    {
        throw std::domain_error("[Minimum] must be of size one or more");
    }

    double result = values[0];
    for (unsigned int i = 0; i < n; i++)
    {
        if (values[i] < result) {result = values[i];}
    }
    return result;
}

// example of O(sqrt(n))
bool IsPrime(const unsigned int n)
{
    for (unsigned int i = 2; i*i <=n; i++)
    {
        // if divisible by i, not prime
        if (0 == n%i) {return false;}
    }
    // if here, then no factors found == prime
    return true;
}

// example of O(n^3)
// Square matrix multiplication: C = A*B
template <const unsigned int N>
void SquareMatrixProduct(const double a[N][N], const double b[N][N], double c[N][N])
{
    for (unsigned int i = 0; i != N; i++)
    {
        for (unsigned int j = 0; j != N; j++)
        {
            c[i][j] = 0.0;
            for (unsigned int k = 0; k != N; k++)
            {
                c[i][j] += a[i][k] * a[k][j];
            }
        }
    }
    return;
}

#include <iostream>
#include <iomanip>

template <const unsigned int N>
void PrintSquareMatrix(const double a[N][N])
{
    using std::cout;
    for (unsigned int row = 0; row != N; row++)
    {
        for (unsigned int col = 0; col != N; col++)
        {
            cout << std::setw(5) << a[row][col];
            if (col == (N-1)) {cout << " ";}
        }
        if (row != (N-1)) {cout << "\n";}
    }
    std::cout << "\n";
}


int main()
{
    double test_values[] = {3,7,2,5,6,4,9};
    const std::size_t n  = sizeof(test_values)/sizeof(test_values[0]);

    // Minimum example
    std::cout << "example 1\n";
    std::cout << "min value = " << Minimum(test_values, n) << std::endl;

    // IsPrime example
    std::cout << "\nexample 2\n";
    for (std::size_t i = 0; i != n; i++)
    {
        const double v = test_values[i];
        std::cout << test_values[i] << " is Prime? --> " << IsPrime(v) << std::endl;
    }

    // matrix multiply example 
    std::cout << "\nexample 3\n";
    const double a[5][5] = 
    { 
        {0  , 1  , 2  , 3  , 4 }, 
        {5  , 6  , 7  , 8  , 9 }, 
        {10 , 11 , 12 , 13 , 14}, 
        {15 , 16 , 17 , 18 , 19}, 
        {20 , 21 , 22 , 23 , 24}, 
    };
    std::cout << "a = \n";
    PrintSquareMatrix(a);

    const double b[5][5] = 
    { 
        {10 , 11 , 12 , 13 , 14}, 
        {15 , 16 , 17 , 18 , 19}, 
        {20 , 21 , 22 , 23 , 24}, 
        {25 , 26 , 27 , 28 , 29}, 
        {30 , 31 , 32 , 33 , 34}, 
    };
    std::cout << "b = \n";
    PrintSquareMatrix(b);

    double c[5][5];
    SquareMatrixProduct(a, b, c);
    std::cout << "c = \n";
    PrintSquareMatrix(c);

    return 0;
}
