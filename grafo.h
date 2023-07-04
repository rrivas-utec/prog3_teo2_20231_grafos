//
// Created by rrivas on 3/07/2023.
//

#ifndef PROG3_TEO2_20231_GRAFOS_GRAFO_H
#define PROG3_TEO2_20231_GRAFOS_GRAFO_H

#include <utility>
#include <unordered_map>
#include <vector>
#include <forward_list>
using namespace std;

template<typename KeyType, typename ValueType, typename WeightType>
class grafo {
    using VertexType = size_t;
    using AdjacentType = pair<VertexType, WeightType>;
    // Lista de Vertices
    unordered_map<KeyType, pair<VertexType, ValueType>> vertices;
    // Vertices Adyacentes
    vector<forward_list<AdjacentType>> adjacents;
public:
    grafo() = default;

    bool add_vertex(pair<KeyType, ValueType> node) {
        // Buscar el vertex
        if (vertices.find(node.first) == end(vertices)) {
            vertices[node.first] = size(vertices);
            adjacents.emplace_back();
            return true;
        }
        return false;
    }
    void add_edge(KeyType key_vertex1, KeyType key_vertex2, WeightType weight) {
        auto vx1 = vertices[key_vertex1].first;
        auto vx2 = vertices[key_vertex2].first;
        adjacents[vx1].push_front(vx2, weight);
        adjacents[vx2].push_front(vx1, weight);
    }
};

#endif //PROG3_TEO2_20231_GRAFOS_GRAFO_H
