#include <iostream>
#include "graph.h"
#include <list>



int main() {

  std::list<Graph> graph_list;
  int counter = 0;

  for (uint32_t b_i = 0; b_i < 32767; ++b_i) {
    std::vector<bool> X(15, 0);
    for (int i = 0; i < 15; ++i)
      X[i] = (b_i & 1 << i) >> i;

    bool isBernaul = true;

    if (X[0] + !X[1] + X[5] + X[6] != 2
      || X[1] + !X[2] + X[7] + X[8] != 2
      || X[2] + !X[3] + X[9] + X[10] != 2
      || X[3] + !X[4] + X[11] + X[12] != 2
      || X[4] + !X[0] + X[13] + X[14] != 2)
      isBernaul = false;


    if (isBernaul == true) {
      for (auto c : X)
        std::cout << c << " ";
      std::cout << "\n";
      graph_list.push_back(Graph(X));
      counter++;
    }
  }

  Permutation rotate72({
    5, 1, 2, 3, 4, // f-b points
    14, 15, 6, 7, 8, 9, 10, 11, 12, 13
    });

  Permutation rotate144 = rotate72 * rotate72;
  Permutation rotate216 = rotate144 * rotate72;
  Permutation rotate288 = rotate216 * rotate72;



  for (auto it = graph_list.begin(); it != graph_list.end(); ++it) {
    std::vector<Graph> rotate = { *it * rotate72, *it * rotate144, *it * rotate216, *it * rotate288 };
    auto inner_it = it;
    inner_it++;
    for (; inner_it != graph_list.end(); ++inner_it) {
      for (auto c : rotate)
        if (c == *inner_it) {
          inner_it = graph_list.erase(inner_it);
          --inner_it;
          break;
        }
    }
  }

  std::cout << "All graphs count: " << counter << "\n";
  std::cout << "Non-isomorphic graphs count: " << graph_list.size() << "\n";
  for (auto c : graph_list)
    std::cout << c << "\n";
  return 0;
}
