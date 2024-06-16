#include <iostream>

#include "Lexer.h"

using Token = Lexer::Token;
using Op = Token::Op;

Token Lexer::scanToken() {
  while (!eof()) {
    int begin = cursor;
    Rune r = advance();
    if (r == '\n') {
      auto eol = makeToken(Op::SEMICOLON);
      line++;
      return eol;
    }
    if (isspace(r)) {
      continue;
    }
    switch (r) {
    case ';':
      return makeToken(Op::SEMICOLON);
    case '+':
      return makeToken(Op::PLUS);
    case U'¯':
      return makeToken(Op::NEGATIVE);
    }
    if (isdigit(r)) {
      while (isdigit(r))
        r = advance();
      return makeToken(Op::NUMBER, source.substr(begin, cursor - begin));
    }
    return makeToken(Op::ERROR, "Unknown lexeme");
  }
  return makeToken(Op::Op_EOF);
}

Rune Lexer::advance() {
  if (eof())
    return 0;
  // UTF-8 decoder.
  Rune r = source[cursor++];
  int l = 0;
  if ((r & 0x80) == 0) {
    r &= 0x7f;
  } else if ((r & 0xe0) == 0xc0) {
    l = 1;
    r &= 0x1f;
  } else if ((r & 0xf0) == 0xe0) {
    l = 2;
    r &= 0x0f;
  } else if ((r & 0xf8) == 0xf0) {
    l = 3;
    r &= 0x07;
  } else {
    return -1;
  }
  while (l--) {
    if (eof())
      return -1;
    r = (r << 6) | (source[cursor++] & 0x3f);
  }
  return r;
}

std::ostream &operator<<(std::ostream &os, Op op) {
  switch (op) {
  case Op::SEMICOLON:
    os << ";";
    break;
  case Op::NEGATIVE:
    os << "¯";
    break;
  case Op::PLUS:
    os << "+";
    break;
  case Op::NUMBER:
    os << "NUMBER";
    break;
  case Op::ERROR:
    os << "ERROR";
    break;
  case Op::Op_EOF:
    os << "EOF";
    break;
  }
  return os;
}
