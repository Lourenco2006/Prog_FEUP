#include <iostream>
#include "MediaMovel.hpp"
using namespace std;

MediaMovel::MediaMovel(double n_elem) : n_elementos(n_elem) {}

// Alínea a)
void MediaMovel::update(double valor)
{
  
  valores.push_back(valor);
  if(valores.size() > n_elementos ){
    valores.pop_front();
  }
  return;
}

// Alínea b)
double MediaMovel::getMediaMovel() const
{
  list<double>::const_iterator curr_valor;
  double soma = 0.0;

  for(curr_valor = valores.begin(); curr_valor != valores.end(); curr_valor++ )
  {
    soma += *curr_valor;
  }

  return (soma/n_elementos);
}
