#include "solver.h"
#include "lexer.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXDEPTH 50
#define assert(condition, message, ...)                                        \
  if (!(condition)) {                                                          \
    printf((message), __VA_ARGS__);                                            \
    exit(1);                                                                   \
  }

double parseVal();         // Raw values or expressions enclosed in (); also leaves token ptr on a operator
                           // the ones below leave token pointing to a value(number or enclosed expression)
double parseExponential(); // Exponentiation
double parseGeometric();   // Multiplication
double parseArithmetic();  // Adding and subtraction

int tkListSize;
int currentElem = 0;
Token *token;
Token empty = {NONE, 0}; // could't think of a less hacky way

Token *advance() {
  if (currentElem == tkListSize) {
    token = &empty;
    return NULL;
  }
  currentElem++;
  return token++;
}

double solve(const TokenList *tokenlist) {
  if (tokenlist->size == 0) {
    return 0;
  }
  tkListSize = tokenlist->size - 1;
  token = tokenlist->data;

  return parseArithmetic();
}

double parseArithmetic() {
  double value = parseGeometric();

  while (token->ch == '+' || token->ch == '-') {
    Token *last = advance();
    if (last->ch == '+') {
      value += parseGeometric();
    } else if (last->ch == '-') {
      value -= parseGeometric();
    }
  }

  return value;
}

double parseGeometric() {
  double value = parseExponential();

  while (token->ch == '*' || token->ch == '/') {
    Token *last = advance();
    if (last->ch == '*') {
      value *= parseExponential();
    } else if (last->ch == '/') {
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

unsigned short int depth = 0;

double parseVal() {
  assert(token->type == NUMBER || token->type == SEP_OPEN,
         "Expected number or open parenthesis, got: %s. %dth element",
         tktype_toString(token->type), currentElem + 1);

  double value = 1;

  if (token->type == NUMBER) {
    value = strtod(token->str, NULL);
    advance();
  }
  while (token->type == SEP_OPEN) {
    depth++;

    if (depth > MAXDEPTH) {
      puts("Excessive expression nesting");
      exit(1);
    }

    advance();

    value *= parseArithmetic();

    assert(token->type == SEP_CLOSE, "Expected a closed parenthesis, got %s. %dth element", tktype_toString(token->type), currentElem + 1);

    advance();

    depth--;
  }
  return value;
}
