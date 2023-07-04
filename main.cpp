#include <iostream>
#include "grafo.h"

int main() {
    grafo<string, int, int> g;
    g.add_vertex({"A", 30});
    g.add_vertex({"B", 40});
    g.add_vertex({"C", 50});

    g.add_edge("A", "B", 2);
    g.add_edge("C", "B", 2);


    return 0;
}
