#include <iostream>
#include <string>

using namespace std;

int main() {
    

    // code
    string s;
    char c,r;
    cout << "Enter a string: ";
    cin >> s;

    cout << "Enter the character to be replaced: ";
    cin >> c;

    cout << "Enter new character: ";
    cin >> r;

    int l = s.length();

    for(int i = 0; i < l; i++)
    {
        if(s[i] == c)
            s[i] = r;
    }

    cout << "Modified string: " << s <<"\n";
    return 0;
}