#include <iostream>
#include "grafo.h"

int main() {
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

    return 0;
}
