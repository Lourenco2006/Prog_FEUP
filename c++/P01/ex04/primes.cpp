#include <iostream>
using namespace std;

int main() {
    
    int n;
    // Asks user for an integer
    cout << "Enter an integer: ";
    // Stores the integer
    cin >> n;
    // calculates whether it is prime or not
    for(int i = 2; i < n; i++)
    {
        if(n % i == 0)
        {
            cout << "The number is not prime \n";
            return 0;
        }
    }
   //  Print result.
    cout << "The number is prime \n";
    return 0;
}