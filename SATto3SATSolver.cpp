#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <cassert>
#include <cstdint>

namespace {
  typedef std::uint64_t Var;
  typedef std::int64_t Lit;
  typedef std::uint64_t ClauseCount;
  typedef std::vector<Lit> Clause;

  std::ostream& operator <<(std::ostream& out, const Clause& C) {
    for (const Lit x : C) out << x << " ";
    return out << "\n";
  }
}

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) return 1;
    const auto first = line[0];
    if (first == 'c') continue;
    if (first == 'p') break;
    return 1;
  }
  if (not std::cin) return 2;
  assert(line[0] = 'p');
  std::stringstream pline{line};
  std::string token;
  pline >> token;
  if (token != "p") return 3;
  pline >> token;
  if (token != "cnf") return 4;
  const Var n = [&pline]{Var t; pline >> t; return t;}();
  if (not pline) return 5;
  const ClauseCount c = [&pline]{ClauseCount t; pline >> t; return t;}();
  if (not pline) return 6;
  std::cout << "p cnf " << n << " " << c << "\n";
  Var aux = n+1;
  ClauseCount count_clauses = 0;
  while (count_clauses < c) {
    Clause C;
    {Lit x;
     while (std::cin >> x, x) C.push_back(x);
     if (not std::cin) return 7;
     if (x != 0) return 8;
    }
    if (C.empty()) return 9;
    ++count_clauses;
    // assert(C is valid);
    while (C.size() > 3) {
      const Lit x = C.back();
      C.resize(C.size()-1);
      const Lit y = C.back();
      C.resize(C.size()-1);
      const Var v = aux;
      std::cout << Clause{x,y,-Lit(v)};
      C.push_back(v);
    }
    std::cout << C;
  }
}
