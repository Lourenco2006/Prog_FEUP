#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;


class Car{
 // questão 2 a)

};


Car::Car(string brand, string model, float price){
    // questão 2 b)
}

string Car::getbrand() const{
     // questão 2 c)
}

string Car::getmodel() const{
     // questão 2 c)
}


float Car::getPrice() const;{
    // questão 2 c)
}

vector<string> Car::getColors() const{
  // // questão 2 c)
}


void Car::setPrice(float euros) {
   // questão 2 d)
}
void Car::addcolors(string color){
    // questão 2 e)
}



void print_vector( vector<string> vec, string sep=" ")
{
    for(auto elem : vec)
    {
        cout<<elem<< sep;
    }
    cout << endl;
  
}

int main()
{
   
    string brand= "Fiat";
    string model= "500"; 
    float price = 20540; 
    Car c1(brand, model,price);

    cout << "O atributo brand é " << c1.getBrand() << endl; 
    cout << "O atributo model é " << c1.getModel() << endl;
    cout << "O atributo price é " << c1.getPrice() << endl;
    cout << "O tamanho do atributo colors é " << c1.getColors().size() << endl;

   c1.setPrice(25900);
    cout << "O atributo price é " << c1.getPrice() << endl;

    c1.addColors("Preto"); 
    cout << "Os elementos do atributo colors são:";
    print_vector(c1.getColors());  





}