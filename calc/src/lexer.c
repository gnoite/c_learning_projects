#include "lexer.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define is_digit(x) (x >= 48 && x <= 57)

TokenType get_tokenType(char c) {
  if (is_digit(c))
    return NUMBER;
  switch (c) {
  case '(':
    return SEP_OPEN;
  case ')':
    return SEP_CLOSE;
  case '+':
  case '-':
  case '*':
  case '/':
  case '^':
    return OPERATOR;
  default:
    return -1;
  }
}

TokenList new_tokenList() {
  TokenList list;

  list.capacity = 8;
  list.data = malloc(sizeof(Token) * list.capacity);
  if (list.data == NULL) {
    list.size = -1;
    return list;
  }
  list.size = 0;

  return list;
}

void free_tokenList(TokenList *tokenlist) {
  for (size_t i = 0; i < tokenlist->size; i++) {
    Token token = tokenlist->data[i];
    if (token.type == NUMBER) {
      free(token.str);
    }
  }
  free(tokenlist->data);
}

int push_token(TokenList *list, Token token) {
  if (list->size == list->capacity) {
    list->capacity *= 2;
    Token *newalloc = realloc(list->data, sizeof(Token) * list->capacity);
    if (newalloc == NULL) return -1;
    list->data = newalloc;
  }
  list->data[list->size] = token;
  list->size++;
  return 0;
}

void get_tokens(char *string, TokenList *tokenList) {

  char *numFirst = NULL;
  unsigned short int numLen = 0;
  char *c = string;
  do {
    TokenType currentType = get_tokenType(*c);

    if (currentType == NUMBER) {
      if (numFirst == NULL) {
        numFirst = c;
      }
      numLen++;
    } else {
      if (numFirst != NULL) {
        char *newStr = malloc(sizeof(char) * numLen + 1);
        if (newStr == NULL) {
          printf("Failed to allocate str memory for number");
          return;
        }
        memcpy(newStr, numFirst, sizeof(char) * numLen);
        newStr[numLen] = '\0';
        Token token = {NUMBER, .str = newStr};
        if (push_token(tokenList, token)) {
          puts("Failed to push token");
        }
        numLen = 0, numFirst = NULL;
      }
      if (currentType != -1) {
        Token token = {currentType, .ch = *c};
        if (push_token(tokenList, token) == -1) {
          puts("Failed to push token");
        }
      }
    }
  } while (*(c++) != '\0');
}
