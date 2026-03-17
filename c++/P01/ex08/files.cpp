#include <iostream>
#include <fstream> 
#include <string>

using namespace std;


/**
 *  reads and prints the file f
 *  param: string f is the name of the file
 *  return: -1 if error, 0 if everything ok 
 */
int print_file(string f){
    ifstream fin(f);

    if(!fin)
    {
        return -1;
    }

    string line;
    int i = 1;
    while(getline(fin, line))
    {
        cout << i << ": " << line << endl;
        i++;
    }
    return 0;
}

/**
 *  counts and prints the number of chars in file f
 *  param: string f is the name of the file
 *  return: -1 if error, 0 if everything ok 
 */
int count_characters(string f) {
    
    ifstream fin(f);

    if(!fin)
    {
        return -1;
    }

    int count = 0;
    string line;
    while(getline(fin, line))
    {
        count+=line.length();
        
    }
    cout<<"The total number of characters is "<<count<<"\n";

    return 0;
}


/**Test code. Do not change**/

int main() {
	print_file("grocery_list.txt");
    count_characters("grocery_list.txt");
    return 0;
}

