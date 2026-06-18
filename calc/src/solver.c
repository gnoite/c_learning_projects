#include "solver.h"
#include "lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define TREESTACKSIZE 5

double runOp(OpType op, double a, double b) {
  switch (op) {
  case PLUS:
    return a + b;
  case MINUS:
    return a - b;
  case MUL:
    return a * b;
  case DIV:
    return a / b;
  case EXP:
    return 0;
  }
}

OpType get_opType(char c) {
  switch (c) {
  case '+':
    return PLUS;
  case '-':
    return MINUS;
  case '*':
    return MUL;
  case '/':
    return DIV;
  case '^':
    return EXP;
  default:
    return -1;
  }
}

double parseVal();
double parseExponential();
double parseGeometric();
double parseArithmetic();

int lastElement;
Token *token;

Token* advance() {
  static int currentElem = 0;
  if(currentElem == lastElement) {
    return NULL;
  }
  currentElem++;
  return token++;
}

double solve(TokenList *tokenlist) {
  if(tokenlist->size == 0) {
    return 0;
  }
  lastElement = tokenlist->size - 1;
  Token *tokens = tokenlist->data;
  return parseArithmetic();
}


double parseArithmetic() {
  double left = parseGeometric();

  while (token->ch == '+' || token->ch == '-') {
    
  }  
}

double parseGeometric() {
  double left = parseExponential();

  while(token->ch == '*' || token->ch == '/') {
    
  }
}

double parseExponential() {
  double left = parseVal();

  while (token->ch == '^') {
    advance();
    left += parseVal();
  } 
}

// 2 * 2 * 4 / 3


double parseVal(Token *token) {
  double value = strtod(token->str, NULL);
  advance();
  return value;
}
