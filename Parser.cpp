#include <charconv>
#include <iostream>

#include "Parser.h"

using Op = Lexer::Token::Op;

std::ostream &Parser::error(Lexer::Token const &t) {
  static std::ostream null{nullptr};
  if (panicMode)
    return null;

  panicMode = true;
  errors++;
  return std::cerr << lex.getFile() << ":" << t.line << ": Error: ";
}

void Parser::advance() {
  previous = peek;
  while (1) {
    peek = lex.scanToken();
    if (peek.op != Op::ERROR)
      break;
    error(peek) << peek.value << "\n";
  }
}

void Parser::consume(Op op) {
  if (peek.op != op)
    error(peek) << "Need " << op << " found " << peek.op << "\n";
  advance();
}

std::unique_ptr<Expr> Parser::number() {
  if (match(Op::NUMBER)) {
    auto s = previous.value;
    double d = 0.;
    auto err = std::from_chars(s.data(), s.data() + s.size(), d);
    if (err.ec != std::errc{})
      error(previous) << "Overflow\n";
    return std::make_unique<Expr>(Tensor{d});
  }
  error(peek) << "Need expression\n";
  return std::make_unique<Expr>(Dead{});
}

std::unique_ptr<Expr> Parser::monad() {
  if (match(Op::NEGATIVE)) {
    auto expr = monad();
    return std::make_unique<Expr>(Monad{Monad::Op::NEGATIVE, std::move(expr)});
  }
  return number();
}

std::unique_ptr<Expr> Parser::expr() {
  auto expr = monad();
  while (match(Op::PLUS)) {
    auto rhs = monad();
    expr = std::make_unique<Expr>(
        BinOp{BinOp::Op::ADD, std::move(expr), std::move(rhs)});
  }
  return expr;
}

std::vector<std::unique_ptr<Expr>> Parser::parse() {
  advance();

  std::vector<std::unique_ptr<Expr>> exprs;
  do {
    panicMode = false;
    exprs.emplace_back(expr());
  } while (match(Op::SEMICOLON));
  return exprs;
}
