#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "solver.h"
#include "lexer.h"

double parseVal(); // Raw values or expressions enclosed in (); also responsible(mostly) for going forward in list
double parseExponential(); // Exponentiation
double parseGeometric(); // Multiplication
double parseArithmetic(); // Adding and subtraction

int size;
Token *token;

Token* advance() {
  static int currentElem = 0;
  if(currentElem == size) {
    return NULL;
  }
  currentElem++;
  return token++;
}

double solve(const TokenList *tokenlist) {
  if(tokenlist->size == 0) {
    return 0;
  }
  size = tokenlist->size - 1;
  Token *tokens = tokenlist->data;
  token = tokens;
  
  return parseArithmetic();
}

double parseArithmetic() {
  double value = parseGeometric();

  while (token->ch == '+' || token->ch == '-') {
    Token *last = advance();
    if(last->ch == '+') {
      value += parseGeometric();
    }else if(last->ch == '-') {
      value -= parseGeometric();
    }
  }

  return value;
}

double parseGeometric() {
  double value = parseExponential();

  while(token->ch == '*' || token->ch == '/') {
    Token *last = advance();
    if(last->ch == '*') {
      value *= parseExponential();
    } else if(last->ch == '/') {
      value /= parseExponential();
    }
  }
  return value;
}

double parseExponential() {
  double value = parseVal();

  while (token->ch == '^') {
    advance();
    value = pow(value, parseVal());
  }

  return value;
}

double parseVal() {
  double value;
  if(token->type == SEP_OPEN) {
    advance();
    value = parseArithmetic();
  }else {
    value = strtod(token->str, NULL);
  }
  Token *last = advance();
  
  while(token->type == SEP_OPEN) {
    advance();
    value *= parseArithmetic();
    advance();
  }
  return value;
}
