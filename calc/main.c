#include "src/oplogic.h"
#include <stdbool.h>
#include <stdio.h>
#include <threads.h>

#include "src/lexer.h"

#define is_digit(x) (x >= 48 && x <= 57)

char *handle_args(int argc, char *argv[]) {
  if (argc <= 1) {
    return NULL;
  } else if (argc > 2) {
    // read file
  }
  return argv[1];
}


int main(int argc, char *argv[]) {
  char *to_compute = handle_args(argc, argv);

  TokenList tokenlist = new_tokenList();
  if (tokenlist.size == -1) {
    puts("Failed to allocate tokenList memory.");
    return 1;
  }

  get_tokens(to_compute, &tokenlist);
    
  

  free_tokenList(&tokenlist);

  return 0;
}
