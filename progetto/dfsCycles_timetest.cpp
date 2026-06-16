#include <iostream>
#include <chrono>
#include <vector>
#include "parse.h"
#include "graph.h" 
#include "cammini_dfs.h" 


// Funzione per confrontare le performance dei due algoritmi
void cyclesTimetest(graph& G) {
    std::cout << "--- Avvio Benchmark Cicli ---" << std::endl;
    // std::cout << "Nodi: " << G.all_nodes().size() << " | Archi totali: " << G.all_edges().size() << std::endl;

    // 1. Test metodo standard (DFS per ogni arco in C)
    auto start_dfs = std::chrono::high_resolution_clock::now();
    auto cycles_dfs = cammini_dfs(G);
    auto end_dfs = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> time_dfs = end_dfs - start_dfs;

    // 2. Test metodo ottimizzato (LCA con depth/parent precostruiti)
    auto start_lca = std::chrono::high_resolution_clock::now();
    auto cycles_lca = findCycles(G);
    auto end_lca = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> time_lca = end_lca - start_lca;

    // Output dei risultati
    std::cout << "Metodo 1 (DFS iterativa) : " << time_dfs.count() << " ms\n";
    std::cout << "Metodo 2 (LCA precalcolato): " << time_lca.count() << " ms\n";

    // Sanity check: assicuriamoci che trovino lo stesso numero di cicli fondamentali
    // In un grafo connesso con V nodi ed E archi, i cicli fondamentali devono essere E - V + 1
    if (cycles_dfs.size() != cycles_lca.size()) {
        std::cerr << "[ATTENZIONE] Discrepanza nei risultati: "
                  << "Il metodo DFS ha trovato " << cycles_dfs.size() << " cicli, "
                  << "mentre il metodo LCA ne ha trovati " << cycles_lca.size() << ".\n";
    } else {
        std::cout << "Check superato: Entrambi i metodi hanno trovato " << cycles_dfs.size() << " cicli fondamentali.\n";
    }
    std::cout << "-----------------------------\n";
}


int main() {
    graph G1 = parse("test10^2.txt");
    cyclesTimetest(G1);

    graph G2 = parse("test10^3.txt");
    cyclesTimetest(G2);

    graph G3 = parse("test2x10^3.txt");
    cyclesTimetest(G3);

    graph G4 = parse("test5x10^3.txt");
    cyclesTimetest(G4);

    graph G5 = parse("test10^4.txt");
    cyclesTimetest(G5);
    return 0;
}
