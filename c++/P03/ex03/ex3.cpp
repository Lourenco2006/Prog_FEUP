#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;


/**
 *  Imprime os elementos do vetor;
 */

int imprime_vetor(vector<int> vec){

    if (vec.empty()) {
        cout << "vector vazio"<< endl;
        return -1;
    }
    cout << "[ ";
    for (int v:vec)
    {
        cout << v << " ";
    }
    cout << "]"<<endl;
    return 0;
}

vector<int> encontrapadrao(vector<int> v, vector<int> vp)
{
   
}


int main()
{
    vector<int> v1{1,2,1,2,1,2,1};
    vector<int> vpadrao{1,2,1};
    vector<int> vresultado;

    vresultado=encontrapadrao(v1,vpadrao);
    cout << "V1=";
    imprime_vetor(v1);
    cout << "Vpadrao=";
    imprime_vetor(vpadrao);
    cout << "Vresultado=";
    imprime_vetor(vresultado);

    vector<int> v2{1,4,5,1,5,5,4,5,2,1};
    vector<int> vpadrao2{4,5};
    

    vresultado=encontrapadrao(v2,vpadrao2);
    cout << "V2=";
    imprime_vetor(v2);
    cout << "Vpadrao2=";
    imprime_vetor(vpadrao2);
    cout << "Vresultado=";
    imprime_vetor(vresultado);
}