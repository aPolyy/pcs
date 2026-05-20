#pragma once

#include <iostream>
#include <set>
#include <map>
#include <optional> // restituisco nullopt quando l'id/edge cercato non esiste
#include <iterator> // per std::next e std::distance

template<typename T>
class unidirected_edge {
    private:
    T v1, v2;
    
    public:
    
    unidirected_edge() {} // mi serve per far funzionare map[] = edge
    
    unidirected_edge(T a, T b) {
        if (a < b) {
            v1 = a;
            v2 = b;
        }
        else {
            v1 = b;
            v2 = a;
        }
    }   

    T from() const {
        return v1;
    }

    T to() const {
        return v2;
    }

    bool operator<(const unidirected_edge<T>& e) const {
        if (v1 < e.from())
            return true;
        if (v1 > e.from())
            return false;
        return v2 < e.to();
    }

    bool operator==(const unidirected_edge<T>& e) const {
        return (v1 == e.from() && v2 == e.to());
    }

};


template<typename T>
std::ostream& 
operator<<(std::ostream& os, const unidirected_edge<T>& e) {
    os << "(" << e.from() << ", " << e.to() << ")";
    return os;
} 

template<typename T>
class unidirected_graph {
    private:
    std::set<T> nodes;
    std::set<unidirected_edge<T>> edges; 
    std::map<T, std::set<T>> neighb;

    // qui l'id è la posizione che ha l'arco secondo l'ordinamento del grafo
    // quindi il set mi permette di ottenere edge_to_id e id_to_edge senza altre strutture

    // la map di neighb mi serve per recuperare rapidamente i vicini di un nodo

    public:
    unidirected_graph(const std::set<T>& input_nodes, const std::set<unidirected_edge<T>>& input_edges) {
        for (const auto& node : input_nodes) 
            nodes.insert(node);

        for (const auto& e : input_edges) { 
            nodes.insert(e.from());
            nodes.insert(e.to());
            edges.insert(e);    
            neighb[e.from()].insert(e.to());
            neighb[e.to()].insert(e.from());
        }
    }

    unidirected_graph() {}

    unidirected_graph(const unidirected_graph<T>& other_graph) {
        for (const auto& node : other_graph.all_nodes())
            nodes.insert(node);

        for (const auto& e : other_graph.all_edges()) { 
            nodes.insert(e.from());
            nodes.insert(e.to());
            edges.insert(e);    
            neighb[e.from()].insert(e.to());
            neighb[e.to()].insert(e.from());
        }
    }

    // non metto reference perchè poi segfaulta con return std::set<T>();
    // potrei provare a farlo con optional
    std::set<T> neighbours(const T& node) const {
        if (neighb.contains(node))
            return neighb.at(node);
        return std::set<T>();
    }

    void add_edge(const unidirected_edge<T>& e) {
        nodes.insert(e.from());
        nodes.insert(e.to());

        // per ora lo lascio per far vedere che non è stato modificato il grafo
        // potrei anche fare gli insert e basta
        if (edges.contains(e)) {
            std::cout << "Edge already present\n";
            return;
        }

        edges.insert(e);
        neighb[e.from()].insert(e.to());
        neighb[e.to()].insert(e.from());

        return;
    }

    // reference costante per non copiare il set
    const std::set<unidirected_edge<T>>& all_edges() const {
        return edges;
    }
    
    // reference costante per non copiare il set
    const std::set<T>& all_nodes() const {
        return nodes;
    }

    
    // uso id 0-indexed
    // uso std::distance e std::next per fare arithmetic agli iteratori si std::set::iterator (complessità lineare sul numero di archi)

    std::optional<int> edge_number(const unidirected_edge<T>& e) const {
        auto it = edges.find(e);
        if (it != edges.end())
            return std::distance(edges.begin(), it); 
        return std::nullopt; 
    }

    std::optional<unidirected_edge<T>> edge_at(int input_id) const {
        if (input_id < 0) {
            std::cout << "id non valido\n";
            return std::nullopt;
        }
        if (edges.size() > input_id)
            return *std::next(edges.begin(), input_id);
        return std::nullopt;    
    }

    unidirected_graph<T> operator-(const unidirected_graph<T>& other_graph) const {
        std::set<unidirected_edge<T>> diff_edges;
        for (const auto& e : edges) { 
            if (!other_graph.all_edges().contains(e)) 
                diff_edges.insert(e);
        }
        return unidirected_graph<T>(nodes, diff_edges);
    }
};


