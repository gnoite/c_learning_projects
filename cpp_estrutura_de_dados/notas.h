constexpr int MAXIMO = 100;

enum class Resultado{
  Sucesso,
  TamanhoExcedido,
  NotaInvalida
};

class Notas {
  private:
    int tamanho = 0;
    double notas[50]{}; // era melhor ter nomeado de "dados"
  public:
    double pop();
    Resultado inserir(double nota);
    double calc_media();
    double maior();
    double menor();
};
