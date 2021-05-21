
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

using Elem = std::variant<Op, int64_t>;

template <bool HavePrecedence>
struct Solver {
  std::vector<Elem> stack = {Op::termination};

  void push(Elem elem) {
    if (holds_alternative<Op>(elem) && get<Op>(elem) == Op::rightParenthesis) {
      elem = result();
      pop<Op>();
    }

    if (holds_alternative<int64_t>(elem) && holds_alternative<Op>(stack.back())) {
      int64_t value = std::get<int64_t>(elem);
      switch (get<Op>(stack.back())) {
      case Op::add:
        pop<Op>(); // remove operator
        value += pop<int64_t>();
        break;
      case Op::mul:
        if (!HavePrecedence) {
          pop<Op>(); // remove operator
          value *= pop<int64_t>();
        }
        break;
      case Op::leftParenthesis:
      case Op::rightParenthesis:
      case Op::termination:
        break;
      default:
        throw std::runtime_error("should not happen");
      }
      stack.push_back(value);
    } else {
      stack.push_back(elem);
    }
  }

  int64_t result() {
    if (HavePrecedence) {
      int64_t value = pop<int64_t>();
      while (std::get<Op>(stack.back()) == Op::mul) {
        pop<Op>();
        value *= pop<int64_t>();
      }
      return value;
    } else {
      return pop<int64_t>();
    }
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

size_t part1(const std::tuple<size_t, size_t> &results) {
  return std::get<0>(results);
}

size_t part2(const std::tuple<size_t, size_t> &results) {
  return std::get<1>(results);
}

std::tuple<size_t, size_t> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }
  std::string line;
  size_t part1 = 0;
  size_t part2 = 0;
  while (getline(infile, line)) {
    Solver<false> solverPart1;
    Solver<true> solverPart2;
    for (char c : line) {
      if (c == ' ')
        continue;
      solverPart1.push(solverPart1.parse(c));
      solverPart2.push(solverPart2.parse(c));
    }
    part1 += solverPart1.result();
    part2 += solverPart2.result();
  }

  return {part1, part2};
}

} // namespace day18