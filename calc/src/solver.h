#pragma once
#include "lexer.h"
#include <stdbool.h>

typedef enum {
  PLUS,
  MINUS,
  MUL,
  DIV,
  EXP 
} OpType;

typedef struct Node Node;

struct Node {
  Node *parent;
  union {
    Node *node;
    double val;
  } left;
  union {
    Node *node;
    double val;
  } right;
  OpType operation;
  bool isLeftNode;
  bool isRightNode;
};

double runOp(OpType, double, double);

Node *parse_tokens(TokenList*);
