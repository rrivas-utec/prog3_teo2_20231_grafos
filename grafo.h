//
// Created by rrivas on 3/07/2023.
//

#ifndef PROG3_TEO2_20231_GRAFOS_GRAFO_H
#define PROG3_TEO2_20231_GRAFOS_GRAFO_H

#include <utility>
#include <unordered_map>
#include <vector>
#include <forward_list>
#include <queue>
#include <stack>
#include <unordered_set>
#include <algorithm>
using namespace std;

template<typename KeyType, typename ValueType, typename WeightType>
class grafo {
    using VertexType = size_t;
    using AdjacentType = pair<VertexType, WeightType>;
    using ItemType = pair<VertexType, ValueType>;
    using EdgeType = tuple<VertexType, VertexType, WeightType>;
    // Lista de Vertices
    unordered_map<KeyType, ItemType> vertices;
    // Vertices Adyacentes
    vector<forward_list<AdjacentType>> adjacent_vertices;
    KeyType get_key(VertexType vertex) {
        auto it = find_if(begin(vertices), end(vertices), [vertex](const auto& item){
           return item.second.first == vertex;
        });
        if (it == end(vertices))
            throw runtime_error("key no encontrada");
        return it->first;
    }
public:
    grafo() = default;

    bool add_vertex(pair<KeyType, ValueType> node) {
        // Buscar el vertex
        if (vertices.find(node.first) == end(vertices)) {
            const auto [key, value] = node;
            vertices.try_emplace(key, pair{size(adjacent_vertices), value});
            adjacent_vertices.emplace_back();
            return true;
        }
        return false;
    }
    void add_edge(KeyType key_vertex1, KeyType key_vertex2, WeightType weight) {
        auto vx1 = vertices[key_vertex1].first;
        auto vx2 = vertices[key_vertex2].first;
        adjacent_vertices[vx1].emplace_front(vx2, weight);
        adjacent_vertices[vx2].emplace_front(vx1, weight);
    }

    template<typename UnaryFunction>
    void bfs (KeyType key, UnaryFunction fun) {
        queue<VertexType> q;
        unordered_set<VertexType> visited;
        auto is_visited= [&visited](VertexType vertex) {
            return visited.find(vertex) != end(visited);
        };
        // Paso #1
        auto fv = vertices[key].first;
        q.push(fv);
        visited.insert(fv);
        // Paso #2
        while(!q.empty()) {
            // Paso #3
            auto vx = q.front();
            fun(get_key(vx));
            // Paso #4
            q.pop();
            // Paso #5
            for (auto [va, w]: adjacent_vertices[vx]) {
                if (!is_visited(va)) {
                    q.push(va);
                    visited.insert(va);
                }
            }
        }
    }
    template<typename UnaryFunction>
    void dfs (KeyType key, UnaryFunction fun) {
        stack<VertexType> s;
        unordered_set<VertexType> visited;
        // Paso #1
        auto fv = vertices[key].first;
        s.push(fv);
        visited.insert(fv);
        // Paso #2
        while(!s.empty()) {
            // Paso #3
            auto vx_top = s.top();
            // Paso # 4.0 Buscar el primer adjacente no visitado
            const auto& adj = adjacent_vertices[vx_top];
            auto it = find_if(begin(adj), end(adj), [&visited](auto item) {
               return visited.find(item.first) == end(visited);
            });
            // Paso #4
            if (it != end(adj)) {
                s.push(it->first);
                visited.insert(it->first);
            }
            // Paso #5
            else {
                fun(get_key(vx_top));
                s.pop();
            }
        }
    }

    template<typename UnaryFunction>
    void prim(KeyType key, UnaryFunction fun) {
        auto edge_compare = [](auto e1, auto e2) {
            return get<2>(e1) > get<2>(e2);
        };
        priority_queue<EdgeType, vector<EdgeType>, decltype(edge_compare)> pq;
        unordered_set<VertexType> visited;
        auto is_visited= [&visited](VertexType vertex) {
            return visited.find(vertex) != end(visited);
        };
        // Agregar al pq las arista adyacentes al vertex de key
        auto fvx = vertices[key].first;
        for (auto [fva, fw]: adjacent_vertices[fvx]) {
            pq.push({fvx, fva, fw});
        }
        visited.insert(fvx);
        // Bucle principal
        while (!pq.empty()) {
            auto [vx, va, w] = pq.top();
            pq.pop();
            if (!is_visited(va)) {
                fun(get_key(vx), get_key(va), w);
                visited.insert(va);
                for(auto [vaa, waa]: adjacent_vertices[va]) {
                    pq.push({va, vaa, waa});
                }
            }
        }
    }
};

#endif //PROG3_TEO2_20231_GRAFOS_GRAFO_H
