#pragma once

#include <iostream>
#include <set>
#include <map>
#include <optional> // restituisco nullopt quando l'id/edge cercato non esiste
#include <iterator> // per std::next e std::distance

class edge {
    private:
        int v1, v2;
        double w;
        int r;
    public:
    
    edge() {} // mi serve per far funzionare map[] = edge
    
    edge(int a, int b, double weight, int res) {
        if (a < b) {
            v1 = a;
            v2 = b;
        }
        else {
            v1 = b;
            v2 = a;
        }
        w = weight;
        r = res;
    }  
    
    edge(int a, int b) {
        if (a < b) {
            v1 = a;
            v2 = b;
        }
        else {
            v1 = b;
            v2 = a;
        }
        w = 1.0;
        r = 0;
    } 

    int from() const {
        return v1;
    }

    int to() const {
        return v2;
    }

    double weight() const {
        return w;
    }

    int is_r() const {
        return r;
    }

    bool operator<(const edge& e) const {
        if (v1 < e.from())
            return true;
        if (v1 > e.from())
            return false;
        return v2 < e.to();
    }

    bool operator==(const edge& e) const {
        return (v1 == e.from() && v2 == e.to());
    }

};

std::ostream& 
operator<<(std::ostream& os, const edge& e) {
    os << "(" << e.from() << ", " << e.to() << ")"; // todo? stampare il peso
    return os;
} 

class graph {
    private:
    std::set<int> nodes;
    std::set<edge> edges; 
    std::map<int, std::set<int>> neighb;
    std::map<edge, int> res_to_resId;// mappa da resistenza a id (0-indexed) per costruire R e B
    std::map<edge, int> edge_to_number;
    std::map<int, edge> number_to_edge;

    public:
    graph(const std::set<int>& input_nodes, const std::set<edge>& input_edges) {
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

    graph() {}

    graph(const graph& other_graph) {
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

    std::set<int> neighbours(int node) const {
        if (nodes.contains(node))
            return neighb.at(node);
        return std::set<int>();
    }

    void add_edge(const edge& e) {
        nodes.insert(e.from());
        nodes.insert(e.to());

        if (edges.contains(e)) {
            std::cout << "Edge already present\n";
            return;
        }

        edges.insert(e);
        neighb[e.from()].insert(e.to());
        neighb[e.to()].insert(e.from());

        return;
    }

    void add_edge(int v1, int v2) {
        nodes.insert(v1);
        nodes.insert(v2);

        edge e(v1, v2);
        edges.insert(e);
        neighb[e.from()].insert(e.to());
        neighb[e.to()].insert(e.from());

        return;
    }

    // reference costante per non copiare il set
    const std::set<edge>& all_edges() const {
        return edges;
    }
    
    // reference costante per non copiare il set
    const std::set<int>& all_nodes() const {
        return nodes;
    }

    
    // uso id 0-indexed
    // uso std::distance e std::next per fare arithmetic degli iteratori su std::set::iterator (complessità lineare sul numero di archi)

    int edge_number(const edge& e) const {
        return edge_to_number.at(e);
    }
    edge edge_at(int input_id) const {
        return number_to_edge.at(input_id);
    }  

    int count_res() const {
        int count = 0;
        for (const auto& e : edges) {
            if (e.is_r() == 1)
                count++;
        }
        return count;
    }

    void update_maps() {   
        res_to_resId.clear();
        number_to_edge.clear();
        edge_to_number.clear();

        int k = 0;
        int n = 0;
        for (auto& e : edges) {
            number_to_edge[n] = e;
            edge_to_number[e] = n;
            n++; 
            if (e.is_r() == 1) {
                // ordina le id delle resistenze in base all'ordine degli archi in edges
                res_to_resId[e] = k;
                k++;
            }
        }
        return;
    }

    int find_resId(edge e) {
        return res_to_resId[e];
    }

    graph operator-(const graph& other_graph) const {
        std::set<edge> diff_edges;
        for (const auto& e : edges) { 
            if (!other_graph.all_edges().contains(e)) 
                diff_edges.insert(e);
        }
        return graph(nodes, diff_edges);
    }
};

