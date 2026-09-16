#include <cctype>
#include <iostream>
#include <ostream>
#include <string>
#include "notas.h"

// fiz com pressa. codigo bem feio

int main() {
  std::cout << "Comandos:\n\tq: sair\n\tx: retorna a nota maxima\n\tn: retorna a nota minima\n\tm: retorna a media das notas\n\ti: insere uma nota\n\tp: remove uma nota" << std::endl;

  Notas notas;
    
  while(true) {
    std::cout << "Comando: ";
    std::string input;
    std::getline(std::cin, input);
    
    switch (std::tolower((*(char*)input.data()))) {
      case 'q':
        {
          return 0;
        }
      case 'x':
        std::cout << std::to_string(notas.maior()) << std::endl;
        break;
      case 'n':
        std::cout << std::to_string(notas.menor()) << std::endl;
        break;
      case 'm':
        std::cout << std::to_string(notas.calc_media()) << std::endl;
        break;
      case 'i': {
        double nota = std::stod(input.substr(1));

        switch (notas.inserir(nota)) {
          case Resultado::NotaInvalida:
            std::cout << "Valor de nota invalido." << std::endl;
            break;
          case Resultado::TamanhoExcedido:
            std::cout << "Lista cheia." << std::endl;
            break;
          case Resultado::Sucesso:
            std::cout << std::endl;
            break;
        }
        break;
      }
      case 'p': {
          double valor = notas.pop();
          std::cout << "Removido: " << std::to_string(valor) << std::endl;
          break;
        }
    }
    
  }
  
  return 0;
}
