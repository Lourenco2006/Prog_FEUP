#include <iostream>

using namespace std;

void sumOfIntegers()
{
    int n;
    // Asks user for an integer
    cout << "Enter an integer: ";
    // Stores the integer
    cin >> n;
    // Calculate the sum of integers up to the value entered (including)
    int R = (n*(n+1))/2;
    //  Print result.
    cout << "Result: " << R << "\n";

}

/**Test code. Do not change**/

int main() {

   sumOfIntegers();

    return 0;
}  
