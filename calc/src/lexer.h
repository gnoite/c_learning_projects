#pragma once
typedef enum { NUMBER, OPERATOR, SEP_OPEN, SEP_CLOSE } TokenType;

typedef struct {
  TokenType type;
  union {
    char *str;
    char ch;
  };
} Token;

typedef struct {
  Token* data;
  unsigned int capacity;
  unsigned int size;
} TokenList;


void free_tokenList(TokenList *tokenlist);

TokenList new_tokenList();


void get_tokens(char *string, TokenList* tokenList);
