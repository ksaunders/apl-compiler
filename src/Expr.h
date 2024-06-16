#pragma once

#include <memory>
#include <variant>
#include <vector>

class Tensor {
public:
  explicit Tensor(double value) : dimensions{0}, values{value} {}

  inline int rank() const { return dimensions.size(); }

private:
  std::vector<int> dimensions;
  std::vector<double> values;
};

struct Monad;
struct BinOp;
struct Dead {};
using Expr = std::variant<Tensor, Monad, BinOp, Dead>;

struct Monad {
  enum class Op { NEGATIVE };

  Op op;
  std::unique_ptr<Expr> expr;
};

struct BinOp {
  enum class Op { ADD };

  Op op;
  std::unique_ptr<Expr> lhs;
  std::unique_ptr<Expr> rhs;
};
