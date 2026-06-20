#pragma once
typedef enum { NONE, NUMBER, OPERATOR, SEP_OPEN, SEP_CLOSE } TokenType;

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

char* tktype_toString(TokenType);

TokenList new_tokenList();
void free_tokenList(TokenList *tokenlist);

void get_tokens(char *string, TokenList* tokenList);
