#include <iostream>
#include <vector>
#include <fstream> 
 #include <algorithm>
#include <sstream>



using namespace std;

int print_vec_componentes(vector<string> vec_comp)
{
    int size=vec_comp.size();
   
   for ( int i=0; i<size; i++ )
    {
        cout << vec_comp[i]<< endl;
    } 

    return 0;

}

int print_vec_custos(vector<float> vec_custos)
{
    int size=vec_custos.size();
   
   for ( int i=0; i<size; i++ )
    {
        cout << vec_custos[i]<< endl;
    } 

    return 0;

}

/*
 *Lê um ficheiro texto em que o parametro de entrada f é o nome do ficheiro
 * coloca informação referente aos nomes das peças num vetor.
**/

vector<string> cria_vet_componentes(string f)
{
    ifstream fin(f);

    if(!fin.is_open())
    return {"Erro de leitura."};
    
    string d;
    string v;
    vector<string> c;

    while(getline(fin,d))
    {

         while (!d.empty() && (d.back() == ' ' || d.back() == '\r' || d.back() == '\n'))
        d.pop_back();

        getline(fin,v);

        c.push_back(d);
    }
        
    fin.close();
        
    return c;

}

/**
 * Lê um ficheiro texto em que o parametro de entrada f é o nome do ficheiro
 * coloca informação referente aos respectivos valores das peças noutro vetor.
**/

vector<float> cria_vet_custos(string f)
{
    ifstream fin(f);

    if(!fin.is_open())
    return {0.00};
    
    string d;
    string v;
    float val;
    vector<float> c;

    while(getline(fin,d))
    {
        getline(fin,v);

        stringstream ss(v);
        
        ss >> val;

        c.push_back(val);
    }
        
    fin.close();
        
    return c;
   
}

/**
 * Apresenta no ecran o preço da peça str_componente.
 * Retorna 0 se conseguiu ou -1 se não conseguiu.
**/

int custo_componente(string str_componente, vector<string> vec_componentes, vector<float> vec_custos){
    
    bool veri = false;
    for(size_t i = 0; i < vec_componentes.size(); i++)
    {
        //cout << "A comparar: [" << vec_componentes[i] << "] com [" << str_componente << "]" << endl;

        
        if(vec_componentes[i] == str_componente)
        {
            cout<<vec_custos[i];
            veri = true;
            break;
        }
        
    }
    if(veri==true) return 0;
    else return -1;
}
/**Test code. Do not change**/

int main() {

    vector<string> vec_compon;
    vector<float> vec_custos;
    int result;
   
    vec_compon = cria_vet_componentes("auto_price_table.txt");
    print_vec_componentes(vec_compon);
    vec_custos = cria_vet_custos("auto_price_table.txt");
    print_vec_custos(vec_custos);
    result = custo_componente("Jante", vec_compon, vec_custos);
    cout << "Return de Jante é: " << result << endl;
    result = custo_componente("Retrovisor", vec_compon, vec_custos);
    cout << "Return de Retrovisor é: " << result << endl;
    result = custo_componente("Roda", vec_compon, vec_custos);
    cout << "Return de Roda é: " << result << endl;
    result = custo_componente("Vidro traseiro", vec_compon, vec_custos);
    cout << "Return de Vidro traseiro é: " << result << endl; 
    
    return 0;
}