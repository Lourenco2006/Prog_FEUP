#include <iostream>
#include <cstdlib>
using namespace std;

/*
Game to match a number between 1 and 100

tip: use rand() to generate random numbers, remember that rand() generates numbers 
between 0 and RAND_MAX. To initialize rand, use srand (time(NULL));
*/


int main() {

    /*make the code here*/  

    srand(time(NULL));
  int n = 1+ rand() % 100;
  int g = 0; 
  int count = 0;

  cout << "Try to guess a number from 1 to 100\n";

  while(g != n)
  {
    count++;
    cout << "Guess the number: ";
    cin >> g;

    if(g == n)
        break;

    if(g < n)
        cout<<"The number you are looking for is greater\n";

    if(g > n)
        cout<<"The number you are looking for is smaller\n";
    
  }

  cout<< "Got it right in " << count << " attempts\n";


 

    return 0;
}  
