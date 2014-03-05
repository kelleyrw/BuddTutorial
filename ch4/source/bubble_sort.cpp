// Example of BubbleSort

#include <iostream>

template <typename T>
void Swap(T& lhs, T& rhs)
{
    const T temp(lhs);
    lhs = rhs;
    rhs = temp;
}

template <typename T>
void PrintArray(T v[], const unsigned int n)
{
    for (unsigned int i = 0; i != n; ++i)
    {
        std::cout << ' ' << v[i];
    }
    std::cout << '\n';
}

// echange the values in the vector v so that 
// they appear in ascending order
template <typename T>
void BubbleSort(T v[], const unsigned int n)
{
#ifndef NDEBUG
    std::cout << "v before ="; PrintArray(v, n);
#endif // NDEBUG
    // find the largest remaining value and place into v[i]
    for (unsigned int i = n-1; i > 0; i--)
    {
#ifndef NDEBUG
        std::cout << "\nv for beginning for i = " << i << " ="; PrintArray(v, n);
#endif // NDEBUG
        // move the largest value to the top
        for (unsigned j = 0; j < i; j++)
        {
#ifndef NDEBUG
            std::cout << "v before for i, j = " << i << ", " << j << " ="; PrintArray(v, n);
            std::cout << "comparing " << v[j] << " with " << v[j+1] << "\n";
#endif // NDEBUG
            // if out of order, then swap
            if (v[j] > v[j+1])
            {
#ifndef NDEBUG
            std::cout << "swapping " << v[j] << " with " << v[j+1] << "\n";
#endif // NDEBUG
                Swap(v[j], v[j+1]);
            }
#ifndef NDEBUG
            else
            {
                std::cout << "no swap\n";
            }
#endif // NDEBUG
#ifndef NDEBUG
            std::cout << "v after for i, j = " << i << ", " << j << " ="; PrintArray(v, n);
#endif // NDEBUG
        }
#ifndef NDEBUG
        std::cout << "v for end for i = " << i << " ="; PrintArray(v, n);
#endif // NDEBUG
    }
#ifndef NDEBUG
    std::cout << "v after ="; PrintArray(v, n);
#endif // NDEBUG
}

int main()
{
    // data
    int values[] = {32,71,12,45,26,80,53,33}; 
    const unsigned int n = sizeof(values)/sizeof(values[0]);
    std::cout << "value before ="; PrintArray(values, n);

    BubbleSort(values, n);
    std::cout << "value after  ="; PrintArray(values, n);
    return 0;
}
