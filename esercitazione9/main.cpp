#include <iostream>
#include "graph.h"
#include "graph_utils.h"

void print_graph(unidirected_graph<int> graph) {
    for (auto& edge: graph.all_edges())
        std::cout<< edge.from() << " -- " << edge.to() << ";\n";
    std::cout<<"\n";
    return;
}

int main () {
    unidirected_graph<int> g;
	
    g.add_edge(unidirected_edge<int>(1,2)); 
    g.add_edge(unidirected_edge<int>(1,3)); 
    g.add_edge(unidirected_edge<int>(1,4)); 
    g.add_edge(unidirected_edge<int>(1,6)); 
    g.add_edge(unidirected_edge<int>(2,4)); 
    g.add_edge(unidirected_edge<int>(2,5)); 
    g.add_edge(unidirected_edge<int>(2,7));
    g.add_edge(unidirected_edge<int>(3,6)); 
    g.add_edge(unidirected_edge<int>(4,6)); 
    g.add_edge(unidirected_edge<int>(4,7));
    g.add_edge(unidirected_edge<int>(5,7));
    g.add_edge(unidirected_edge<int>(6,7));
    g.add_edge(unidirected_edge<int>(6,8));
    g.add_edge(unidirected_edge<int>(7,9)); 
    g.add_edge(unidirected_edge<int>(8,9));
    
    print_graph(g);

    lifo<int> s;
    unidirected_graph<int> g_dfs = graph_visit(g, 1, s);
    print_graph(g_dfs);

    fifo<int> q;
    unidirected_graph<int> g_bfs = graph_visit(g, 1, q);
    print_graph(g_bfs);

    unidirected_graph<int> g_dfs_rec = recursiveDFS(g, 1);
    print_graph(g_dfs_rec);

    unidirected_graph<int> g_dijkstra = dijkstra(g, 1);
    print_graph(g_dijkstra);

}
