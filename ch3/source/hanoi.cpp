#include <iostream>

using namespace std;

void Hanoi(int n, char a, char b, char c)
{
    // base case:
    if (n==1)
    {
        // move the smallest disk directly
        cout << "move disk from tower " << a << " to " << b << endl;
    }
    // recursive case:
    else
    {
        // first move all but the last disk to c
        Hanoi(n-1, a, c, b);

        // then move one disk from a to b
        cout << "move disk from tower " << a << " to " << b << endl;

        // then move all disks from c back to b
        Hanoi(n-1, c, b, a);
    }

    return;
}


int main()
{
    Hanoi(/*ndisks=*/3, 'A', 'B', 'C');
    return 0; 
}
