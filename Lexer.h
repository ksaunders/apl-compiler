#pragma once

#include <ostream>
#include <string_view>

using Rune = int;

class Lexer {
public:
  struct Token {
    enum class Op {
      SEMICOLON,
      NEGATIVE,
      PLUS,
      NUMBER,

      ERROR,
      Op_EOF
    };

    Op op;
    std::string_view value;
    int line;
  };

  Lexer(std::string_view file, std::string_view source)
      : file{file}, source{source} {}

  Token scanToken();

  std::string_view getFile() const { return file; }

private:
  Rune advance();

  static inline bool isspace(Rune r) {
    return r == ' ' || r == '\r' || r == '\t';
  }

  static inline bool isdigit(Rune r) { return r >= '0' && r <= '9'; }

  inline bool eof() { return cursor >= source.size(); }

  inline Token makeToken(Token::Op op, std::string_view value = "") {
    return Token{op, value, line};
  }

  std::string_view file, source;
  int cursor = 0;
  int line = 1;
};

std::ostream &operator<<(std::ostream &os, Lexer::Token::Op op);
