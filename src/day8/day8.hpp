
#pragma once

#include <fstream>
#include <numeric>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace day8 {

int part1(const std::vector<std::pair<std::string, int>> &program) {
  int accumulator = 0;
  std::set<int> visitedIndex;
  for (int i = 0; i < program.size(); ++i) {
    if (visitedIndex.count(i)) {
      return accumulator;
    }
    visitedIndex.insert(i);
    if (program[i].first == "nop") {
    } else if (program[i].first == "jmp") {
      i += program[i].second - 1; // to compensate the ++i of the loop
    } else if (program[i].first == "acc") {
      accumulator += program[i].second;
    }
  }
  return 0;
}

std::optional<int> executeMutatedProgram(const std::vector<std::pair<std::string, int>> &program, std::set<int> &changedInstruction) {
  int accumulator = 0;
  bool haveChangedInstruction = false;
  std::vector<std::pair<std::string, int>> programMutable = program;

  std::set<int> visitedIndex;
  for (int i = 0; i < programMutable.size(); ++i) {
    if (i < 0) {
      return {};
    }
    if (i > programMutable.size()+1) {
      return {};
    }
    // Mutate instruction
    if (!haveChangedInstruction && !changedInstruction.count(i)) {
      if (programMutable[i].first == "nop") {
        programMutable[i].first = "jmp";
        haveChangedInstruction = true;
        changedInstruction.insert(i);
      } else if (programMutable[i].first == "jmp") {
        programMutable[i].first = "nop";
        haveChangedInstruction = true;
        changedInstruction.insert(i);
      }
    }
    if (visitedIndex.count(i)) {
      return {};
    }
    visitedIndex.insert(i);
    if (programMutable[i].first == "nop") {
    } else if (programMutable[i].first == "jmp") {
      i += programMutable[i].second - 1; // to compensate the ++i of the loop
    } else if (programMutable[i].first == "acc") {
      accumulator += programMutable[i].second;
    }
  }
  return accumulator;
}

int part2(const std::vector<std::pair<std::string, int>> &program) {
  std::optional<int> accumulator;
  std::set<int> changedInstruction;

  while (!accumulator) {
    accumulator = executeMutatedProgram(program, changedInstruction);
  }

  return accumulator.value();
}

std::vector<std::pair<std::string, int>> parseInputFile(std::string filename) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    throw std::runtime_error("File Not Found : " + filename);
  }

  std::string line;

  std::vector<std::pair<std::string, int>> program;

  while (getline(infile, line)) {
    std::string instruction(line.data(), line.data() + 3);
    int value = std::stoi(line.data() + 3);
    program.push_back({instruction, value});
  }

  return program;
}

} // namespace day8