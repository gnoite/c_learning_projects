#include "notas.h"

double Notas::calc_media() {
  double total = 0;
  for(double* v = this->notas; v < this->notas + this->tamanho; v++) {
    total += *v;
  }
  return total / this->tamanho;
}

double Notas::menor() {
  double menor = 100;
  for(double* v = this->notas; v < this->notas + this->tamanho; v++) {
    if (*v < menor) {
      menor = *v;
    } 
  }

  return menor;
}

double Notas::maior() {
  double maior = 0;
  for(double* v = this->notas; v < this->notas + this->tamanho; v++) {
    
    if (*v > maior) {
      maior = *v;
    }
  }

  return maior;
}

Resultado Notas::inserir(double nota) {
  if(this->tamanho >= MAXIMO) {
    return Resultado::TamanhoExcedido;
  }
  if(nota < 0 || nota > 100) {
    return Resultado::NotaInvalida;
  }
  this->notas[this->tamanho] = nota;
  this->tamanho++;

  return Resultado::Sucesso;
}

// creio que seja safe por nao haver outra forma de tamanho subir sem mudar os valores.
double Notas::pop() {
  if(this->tamanho == 0) {
    return 0;
  }
  this->tamanho--;

  return this->notas[this->tamanho];
}
