#include <iostream>
#include "grafo.h"

void ejemplo_1() {
    grafo<string, int, int> g;
    g.add_vertex({"A", 10});
    g.add_vertex({"E", 20});
    g.add_vertex({"I", 30});
    g.add_vertex({"O", 40});
    g.add_vertex({"U", 50});

    g.add_edge("A", "E", 10);
    g.add_edge("E", "I", 7);
    g.add_edge("E", "O", 8);
    g.add_edge("I", "O", 2);
    g.add_edge("I", "U", 5);

    g.bfs("A", [](auto key) {
        cout << key << " ";
    });
    cout << endl;
    g.dfs("A", [](auto key) {
        cout << key << " ";
    });
    cout << endl;
}

void ejemplo_2() {
    grafo<string, int, int> g;
    g.add_vertex({"A", 1});
    g.add_vertex({"B", 2});
    g.add_vertex({"C", 3});
    g.add_vertex({"D", 4});
    g.add_vertex({"E", 5});
    g.add_vertex({"F", 6});
    g.add_vertex({"G", 7});
    g.add_vertex({"H", 8});

    g.add_edge("A", "B", 6);
    g.add_edge("A", "F", 3);
    g.add_edge("A", "G", 6);
    g.add_edge("A", "C", 10);
    g.add_edge("B", "F", 2);
    g.add_edge("F", "G", 1);
    g.add_edge("G", "C", 1);
    g.add_edge("G", "D", 5);
    g.add_edge("G", "H", 9);
    g.add_edge("C", "D", 7);
    g.add_edge("D", "H", 4);
    g.add_edge("D", "E", 3);
    g.add_edge("E", "H", 4);

    g.prim("E", [](auto k1, auto k2, auto w) {
       cout << k1 << " " << k2 << " " << w << endl;
    });


}

int main() {
    ejemplo_2();
    return 0;
}
