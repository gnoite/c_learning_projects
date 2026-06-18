#include <stdio.h>
#include "src/solver.h"
#include "src/lexer.h"


int main(int argc, char *argv[]) {
  if(argc < 2) {
    puts("Not enough args.");
    return 1;
  }
  char *to_compute = argv[1];

  TokenList tokenlist = new_tokenList();
  if (tokenlist.size == -1) {
    puts("Failed to allocate tokenList memory.");
    return 1;
  }

  get_tokens(to_compute, &tokenlist);
    
  printf("Result: %f\n", solve(&tokenlist));

  free_tokenList(&tokenlist);

  return 0;
}
