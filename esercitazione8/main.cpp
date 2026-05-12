#include <iostream>
#include <set>
#include <list>
#include <optional>
#include "graph.h"

int main() {
    
    std::set<int> g1_starting_nodes = {1, 2, 3, 4, 5};
    std::list<unidirected_edge<int>> g1_starting_edges;
    int from[] = {1, 1, 4, 5};
    int to[]   = {2, 3, 1, 3};
    for (int i = 0; i < sizeof(from)/sizeof(int); i++) 
        g1_starting_edges.push_back(unidirected_edge<int>(from[i], to[i]));

    unidirected_graph<int> g1(g1_starting_nodes, g1_starting_edges); 

    std::cout << "Nodi in g1: ";
    for (int n : g1.all_nodes()) 
        std::cout << n << " ";
    std::cout << "\n";
    
    std::cout << "Archi in g1: ";
    for (unidirected_edge<int> e : g1.all_edges()) 
        std::cout << e << " ";
    std::cout << "\n";
    
    std::cout << "Vicini del nodo 1: ";
    for (int neighb : g1.neighbours(1)) 
        std::cout << neighb << " ";
    std::cout << "\n";

    std::optional<int> edge_id;
    edge_id = g1.edge_number({1, 2});
    if (edge_id) 
        std::cout << "Id dell'arco (1, 2) : " << *edge_id;
    else 
        std::cout << "L'arco (1, 2) non esiste nel grafo";
    std::cout << "\n";

    edge_id = g1.edge_number({1, 100});
    if (edge_id) 
        std::cout << "Id dell'arco (1, 100) : " << *edge_id;
    else 
        std::cout << "L'arco (1, 100) non esiste nel grafo";
    std::cout << "\n";

    std::optional<unidirected_edge<int>> edge_at_id;
    edge_at_id = g1.edge_at(1);
    if (edge_at_id)
        std::cout << "Arco con id 1: " << *edge_at_id;
    else 
        std::cout << "Non esiste un arco con id 1 nel grafo";
    std::cout << "\n";

    edge_at_id = g1.edge_at(100);
    if (edge_at_id)
        std::cout << "Arco con id 100: " << *edge_at_id;
    else 
        std::cout << "Non esiste un arco con id 100 nel grafo";
    std::cout << "\n";

    unidirected_graph<int> g2; 
    g2.add_edge(unidirected_edge<int>(1, 2));
    g2.add_edge(unidirected_edge<int>(2, 3));

    std::cout << "Nodi in g2: ";
    for (int n : g2.all_nodes()) 
        std::cout << n << " ";
    std::cout << "\n";

    std::cout << "Archi in g2: ";
    for (unidirected_edge<int> e : g2.all_edges()) 
        std::cout << e << " ";
    std::cout << "\n";

    unidirected_graph<int> diff = g1 - g2; // NB. questo usa anche l'operatore di copia
    
    std::cout << "Archi nel grafo differenza (g1 - g2): ";
    for (unidirected_edge<int> e : diff.all_edges()) 
        std::cout << e << " ";
    std::cout << "\n";

    std::cout << "Vicini del nodo 1 dopo la differenza: ";
    for (int neighb : diff.neighbours(1)) 
        std::cout << neighb << " ";
    std::cout << "\n";

    return 0;
}