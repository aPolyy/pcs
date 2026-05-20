#pragma once

#include<vector>
#include<queue>
#include<set>
#include<map>
#include<utility>
#include<optional>
#include "graph.h"

// nb. per come è scritto assume che non ci siano nodi isolati nel grafo

template<typename T> 
class lifo {
    private:
    std::vector<T> s;
    int sz;

    public:

    lifo() {
        sz = 0;
    }

    std::optional<T> get() {
        if (sz > 0) {
            sz--;
            T x = s.back();
            s.pop_back();
            return x;
        }
        return std::nullopt;
    }

    void put(T x) {
        s.push_back(x);
        sz++;
        return;
    }

    bool empty() const {
        return sz == 0;
    }
};

template<typename T>
class fifo {
    private:
    std::queue<T> s;
    int sz;

    public:
    fifo() {
        sz = 0;
    }

    std::optional<T> get() {
        if (sz > 0) {
            sz--;
            T x = s.front();
            s.pop();
            return x;
        }
        return std::nullopt;
    }

    void put(T x) {
        s.push(x);
        sz++;
        return;
    }

    bool empty() const {
        return sz == 0;
    }

};

template<typename T, typename Container>
unidirected_graph<T> graph_visit(const unidirected_graph<T>& g_in, const T& source, Container& container) {
    unidirected_graph<T> g_out;
    std::set<T> visited;
    visited.insert(source);
    container.put(source);

    T curr;
    while(!container.empty()) {
        curr = container.get().value(); // è un optional, ma il check non serve perchè c'è gia sopra il check su .empty()
        for (auto& node: g_in.neighbours(curr)) {
            if (!visited.contains(node)) {
                container.put(node);
                visited.insert(node);
                g_out.add_edge(unidirected_edge<T>(curr, node));
            }
        }
    }
    return g_out;
}

template<typename T>
void recursion(const unidirected_graph<T>& g_in, const T& curr, unidirected_graph<T>& g_out, std::set<T>& visited) {
    for (auto& node: g_in.neighbours(curr)) {
        if (!visited.contains(node)) {
            g_out.add_edge(unidirected_edge<T>(curr, node));
            visited.insert(node);
            recursion(g_in, node, g_out, visited);
        }
    }
    return;
}

template<typename T>
unidirected_graph<T> recursiveDFS(const unidirected_graph<T>& g_in, const T& source) {
    unidirected_graph<T> g_out;
    std::set<T> visited;
    visited.insert(source);
    recursion(g_in, source, g_out, visited);
    return g_out;
}

template<typename T> 
unidirected_graph<T> dijkstra(const unidirected_graph<T>& g_in, const T& source) {
    unidirected_graph<T> g_out;
    std::map<T, T> pred; // questa non la sto usando, era nello pseudocodice della teoria
    std::map<T, int> dist;
    std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, std::greater<std::pair<int, T>>> pq;
    const int infty = g_in.all_nodes().size() + 1;
    
    for (auto& node: g_in.all_nodes())
        dist[node] = infty;
    dist[source] = 0;
    pred[source] = source;

    T curr;
    pq.push(std::pair<int, T>(0, source));
    while (!pq.empty()) {    
        curr = pq.top().second;
        pq.pop();

        for (auto& node : g_in.neighbours(curr)) {
            if (dist[curr] + 1 < dist[node]) {
                dist[node] = dist[curr] + 1;
                pred[node] = curr;
                pq.push(std::pair<int, T>(dist[node], node));
            }
        }
    }

    // in genere dovrei returnare le distanze, qui sto restituendo il grafo per stamparlo come richiesto
    for (auto& node : g_in.all_nodes()) {
        if (node != source) 
            g_out.add_edge(unidirected_edge<T>(pred[node], node));
    }

    return g_out;
}