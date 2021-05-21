
#pragma once

#include <algorithm>
#include <exception>
#include <fstream>
#include <memory>
#include <set>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace day18 {

// helper type for the visitor
template <class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

enum class Op {
  add,
  mul,
  leftParenthesis,
  rightParenthesis,
  termination
};

using Elem = std::variant<Op, int>;

struct Solver {
  std::vector<Elem> stack = {Op::termination};

  void push(Elem elem) {
    std::visit(overloaded{
        [&](Op t) {
          if (t == Op::rightParenthesis) {
            int value = result();
            pop<Op>();
            stack.push_back(value);
          } else {
            stack.push_back(t);
          }
        },
        [&](int t) {
          // we can't have to number next to each other without operator between them
          switch (get<Op>(stack.back())) {
          case Op::add:
            pop<Op>(); // remove operator
            t += pop<int>();
            break;
          case Op::mul:
            pop<Op>(); // remove operator
            t *= pop<int>();
            break;
          case Op::leftParenthesis:
            // do nothing
            break;
          }
          stack.push_back(t);
        },
    },
    elem);
  }

  int result() {
    return pop<int>();
  }

  template <typename T>
  T pop() {
    Elem t = stack.back();
    stack.pop_back();
    return std::get<T>(t);
  }

  static Elem parse(char c) {
    switch (c) {
    case '+':
      return Op::add;
    case '*':
      return Op::mul;
    case '(':
      return Op::leftParenthesis;
    case ')':
      return Op::rightParenthesis;
    case ' ':
      throw std::runtime_error("should be filter before");
    default:
      const std::string s(1, c);
      return std::stoi(s);
    }
  }
};

size_t part1(const std::tuple<long, long> &results) {
  return std::get<0>(results);
}

size_t part2(const std::tuple<long, long> &results) {
  return std::get<1>(results);
}

std::tuple<long, long> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }
  std::string line;
  long part1 = 0;
  long part2 = 0;
  while (getline(infile, line)) {
    Solver solver;
    for (char c : line) {
      if (c == ' ')
        continue;
      solver.push(solver.parse(c));
    }
    part1 += solver.result();
  }

  return {part1, part2};
}

} // namespace day18