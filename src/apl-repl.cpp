#include <readline/readline.h>

#include "Lexer.h"
#include "Parser.h"

static std::string_view file = "<unknown>";

int main() {
  while (1) {
    char *p = readline("apl-repl> ");
    if (p == nullptr)
      return 0;
    Lexer lex{file, p};
    Parser parser{std::move(lex)};
    parser.parse();
  }

  return 0;
}
