#include <iostream>
#include <vector>

using namespace std;


int insert_several(vector<int>& v, int n){
    // questão 1 a)
    if(n<0)
    return -1;

    for(int i = 0;i<=n;i++)
    {
            v.push_back(i * 2);

    }
 
    return 0;
}


int insert_pos(vector<int>& v, int pos, int value){
    //questão 1 b)

    

    return 0;
}

// Utility function to print the vector
void print_vec(vector<int>& v){
    cout << "Vector elements: " << endl;
    for (auto i = v.begin(); i != v.end(); ++i)
        cout << *i << " ";
    cout << endl; 
}



int main(){
    

    vector<int> numbers;
    cout << "Return Value: " << insert_several(numbers,10) << endl;
    print_vec(numbers);

    int pos = 3;
    int value = 4;
    cout << "Return Value: " << insert_pos(numbers, pos, value)<< endl;
    print_vec(numbers);


}