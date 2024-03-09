#include <iostream>

#include "Lexer.h"

static std::string_view file = "<unknown>";
static std::string_view source = "¯2 + 3";

int main() {
  Lexer lex{file, source};
  while (1) {
    auto t = lex.scanToken();
    if (t.op == Lexer::Token::Op::Op_EOF)
      return 0;
    std::cerr << static_cast<int>(t.op) << "\n";
  }
  return 0;
}
