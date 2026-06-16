#pragma once

#include<vector>
#include<queue>
#include<set>
#include<map>
#include<utility>
#include<optional>
#include "graph.h"

// nb. per come è scritto assume che non ci siano nodi isolati nel grafo
 
class lifo {
    private:
    std::vector<int> s;
    int sz;

    public:

    lifo() {
        sz = 0;
    }

    int get() {
        sz--;
        int x = s.back();
        s.pop_back();
        return x;
    }

    void put(int x) {
        s.push_back(x);
        sz++;
        return;
    }

    bool empty() const {
        return sz == 0;
    }
};

class fifo {
    private:
    std::queue<int> s;
    int sz;

    public:
    fifo() {
        sz = 0;
    }

    int get() {
        sz--;
        int x = s.front();
        s.pop();
        return x;
    }

    void put(int x) {
        s.push(x);
        sz++;
        return;
    }

    bool empty() const {
        return sz == 0;
    }

};


void recursion(const graph& g_in, int curr, graph& g_out, std::set<int>& visited) {
    for (auto& node: g_in.neighbours(curr)) {
        if (!visited.contains(node)) {
            g_out.add_edge(edge(curr, node));
            visited.insert(node);
            recursion(g_in, node, g_out, visited);
        }
    }
    return;
}

graph recursiveDFS(const graph& g_in, int source) {
    //restituisce un albero DFS del grafo g_in, partendo da source
    graph g_out;
    std::set<int> visited;
    visited.insert(source);
    recursion(g_in, source, g_out, visited);
    return g_out;
}
 

std::map<int, int> dijkstra(const graph& g_in, int source) {
    //restituisce la mappa dei predecessori del grafo g_in, 
    //partendo da source, secondo l'algoritmo di Dijkstra
    graph g_out;
    std::map<int, int> pred; 
    std::map<int, int> dist;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    const int infty = g_in.all_nodes().size() + 1;//oltre la distanza massima
    
    for (auto& node: g_in.all_nodes())
        dist[node] = infty;
    dist[source] = 0;
    pred[source] = source;

    int curr;
    pq.push(std::pair<int, int>(0, source));
    while (!pq.empty()) {    
        curr = pq.top().second;
        pq.pop();

        for (auto& node : g_in.neighbours(curr)) {
            if (dist[curr] + 1 < dist[node]) {
                dist[node] = dist[curr] + 1;
                pred[node] = curr;
                pq.push(std::pair<int, int>(dist[node], node));
            }
        }
    }

    return pred;
}
    