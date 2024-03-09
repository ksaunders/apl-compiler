#pragma once

#include <ostream>

#include "Expr.h"
#include "Lexer.h"

class Parser {
public:
  Parser(Lexer &&lex) : lex{std::move(lex)} {}

  std::vector<std::unique_ptr<Expr>> parse();

  inline bool hadError() const { return errors != 0; }

private:
  std::ostream &error(Lexer::Token const &t);

  inline bool eof() { return peek.op == Lexer::Token::Op::Op_EOF; }

  inline bool match(Lexer::Token::Op op) {
    if (peek.op == op) {
      advance();
      return true;
    }
    return false;
  }

  void consume(Lexer::Token::Op op);

  void advance();

  std::unique_ptr<Expr> number();

  std::unique_ptr<Expr> monad();

  std::unique_ptr<Expr> expr();

  Lexer::Token peek, previous;
  Lexer lex;
  bool panicMode;
  int errors = 0;
};
