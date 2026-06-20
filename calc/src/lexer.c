#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define is_digit(x) (x >= 48 && x <= 57)

TokenList new_tokenList();
int push_token(TokenList *, Token);
TokenType get_tokenType(char c);

void get_tokens(char *string, TokenList *tokenList) {
  char *numStart = NULL;
  unsigned short int numLen = 0;
  char *c = string;

  do {
    TokenType currentType = get_tokenType(*c);

    if (currentType == NUMBER) {
      if (numStart == NULL) {
        numStart = c;
      }
      numLen++;
      continue;
    }

    if (numStart != NULL) {
      char *newStr = malloc(sizeof(char) * numLen + 1);
      
      if (newStr == NULL) {
        puts("Failed to allocate str memory for number");
        return;
      }
      
      memcpy(newStr, numStart, sizeof(char) * numLen);
      newStr[numLen] = '\0';
      
      Token token = {NUMBER, .str = newStr};

      if (push_token(tokenList, token))
        puts("Failed to push token");
      numLen = 0, numStart = NULL;
    }

    if (currentType != -1) {
      Token token = {currentType, .ch = *c};

      if (push_token(tokenList, token))
        puts("Failed to push token");
    }

  } while (*(c++) != '\0');
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

int push_token(TokenList *list, Token token) {
  if (list->size == list->capacity) {
    list->capacity *= 2;
    Token *newalloc = realloc(list->data, sizeof(Token) * list->capacity);
    if (newalloc == NULL)
      return 1;
    list->data = newalloc;
  }
  list->data[list->size] = token;
  list->size++;
  return 0;
}

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

void free_tokenList(TokenList *tokenlist) {
  for (size_t i = 0; i < tokenlist->size; i++) {
    Token token = tokenlist->data[i];
    if (token.type == NUMBER) {
      free(token.str);
    }
  }
  free(tokenlist->data);
}

char* tktype_toString(TokenType type) {
  switch (type) {
    case NUMBER: return "NUMBER";
    case OPERATOR: return "OPERATOR";
    case SEP_OPEN: return "OPEN_PARENTHESIS";
    case SEP_CLOSE: return "CLOSED_PARENTHESIS";
    case NONE: return "NONE";
  }
}
