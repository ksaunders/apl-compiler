#include "Lexer.h"
#include "Parser.h"

static std::string_view file = "<unknown>";
static std::string_view source = "¯2 + 3";

int main() {
  Lexer lex{file, source};
  Parser parser{std::move(lex)};
  auto exprs = parser.parse();
  if (parser.hadError())
    return 1;
  return 0;
}
