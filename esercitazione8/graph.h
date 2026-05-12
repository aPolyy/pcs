#include <iostream>
#include <set>
#include <map>
#include <list>
#include <optional> // restituisco nullopt quando l'id/edge cercato non esiste

template<typename T>
class unidirected_edge {
    private:
    T v1, v2;
    
    public:
    
    unidirected_edge() {} // mi serve per far funzionare map[int] = edge
    
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
std::ostream& operator<<(std::ostream& os, const unidirected_edge<T>& e) {
    os << "(" << e.from() << ", " << e.to() << ")";
    return os;
} 

template<typename T>
class unidirected_graph {
    private:
    std::set<T> nodes;
    std::list<unidirected_edge<T>> edges; 
    std::map<int, unidirected_edge<T>> id_to_edge;
    std::map<unidirected_edge<T>, int> edge_to_id;
    std::map<T, std::set<T>> neighb;
    int id;

    public:
    unidirected_graph (const std::set<T>& input_nodes, const std::list<unidirected_edge<T>>& input_edges) {
        id = 0;
        for (T node : input_nodes) 
            nodes.insert(node);

        for (unidirected_edge<T> e : input_edges) {
            if (!nodes.contains(e.from()))
                nodes.insert(e.from());
            if (!nodes.contains(e.to())) 
                nodes.insert(e.to());

            if (!edge_to_id.contains(e)) {
                edges.push_back(e);
                id_to_edge[id] = e;
                edge_to_id[e] = id;
                id++;
                
                neighb[e.from()].insert(e.to());
                neighb[e.to()].insert(e.from());
            }
            
        }
    }

    unidirected_graph () {
        id = 0;
    }

    unidirected_graph(const unidirected_graph<T>& other_graph) 
    : unidirected_graph(other_graph.all_nodes(), other_graph.all_edges()) {}

    std::set<T> neighbours (const T& node) const {
        if (neighb.contains(node))
            return neighb.at(node);
        return std::set<T>();
    }

    void add_edge(const unidirected_edge<T>& e) {

        if (!nodes.contains(e.from()))
            nodes.insert(e.from());
        if (!nodes.contains(e.to()))
            nodes.insert(e.to());

        if (edge_to_id.contains(e)) {
            std::cout << "Edge already present\n";
            return;
        }

        edges.push_back(e);
        id_to_edge[id] = e;
        edge_to_id[e] = id;
        id++;

        neighb[e.from()].insert(e.to());
        neighb[e.to()].insert(e.from());

        return;
    }

    std::list<unidirected_edge<T>> all_edges() const {
        return edges;
    }

    std::set<T> all_nodes() const {
        return nodes;
    }

    std::optional<int> edge_number(const unidirected_edge<T>& e) const {
        if (edge_to_id.contains(e))
            return edge_to_id.at(e);
        return std::nullopt; 
    }

    std::optional<unidirected_edge<T>> edge_at(int input_id) const {
        if (id_to_edge.contains(input_id))
            return id_to_edge.at(input_id);
        return std::nullopt;    
    }

    unidirected_graph<T> operator-(const unidirected_graph<T>& other_graph) const {
        std::list<unidirected_edge<T>> diff_edges;
        for (unidirected_edge<T> e : edges) {
            if (other_graph.edge_number(e) == std::nullopt)
                diff_edges.push_back(e);
        }
        return unidirected_graph<T>(nodes, diff_edges);
    }
};


