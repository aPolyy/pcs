#pragma once

#include <vector>
#include "graph.h"
#include "graph_utils.h"


std::vector<int> cammino_albero(graph& g, int partenza, int arrivo){
    lifo pila;
    pila.put(partenza);
    bool arrivato = false;
    const int V = g.all_nodes().size();
    std::vector<int> genitore(V + 1);
   
    while ( !arrivato){
        int nodo = pila.get();
        auto vicini = g.neighbours(nodo);
        for (auto& vicino:vicini){
            if (vicino == arrivo){
                genitore[arrivo] = nodo;
                arrivato = true;
            }
            if (vicino != genitore[nodo]){  //per non tornare indietro
                genitore[vicino] = nodo;
                pila.put(vicino);  //non controllo se già c'è perchè per la struttura di albero non può succedere
            }
        }
        
    }
    std::vector<int> percorso;
    int primo = genitore[arrivo];
    //undirected_edge edge(primo, secondo);
    percorso.push_back(arrivo);
    while (primo != partenza){
        percorso.push_back(primo);
        primo = genitore[primo];
        //undirected_edge edge(primo, secondo);
        

    }
    percorso.push_back(partenza);
    return percorso;
}

std::vector<std::vector<int>> cammini_dfs(graph& G){
    std::vector<std::vector<int>> cammini;
    lifo pila;
    auto A = recursiveDFS(G,1);
    auto C = G-A;

    for (auto& edge:C.all_edges()){
        int a = edge.from();
        int b = edge.to();
        auto cammino = cammino_albero(A, a, b);
        cammino.push_back(b);
        cammini.push_back(cammino);
    }
    return cammini;
}

// Questa versione implementa lo stesso metodo, con un approccio diverso
// Invece di fare DFS ad ogni step, salvo in anticipo le profondità e i parent 
// per sapere quando fermarmi nella risalita


void dfsLCA(const graph& T, std::vector<int>& parent, std::vector<int>& depth) {
    // uso una dfs per tabulare la profondità di ogni nodo dalla radice
    // il path fra due nodi in un albero deve incontrarsi alla stessa profondità
    // quindi posso risalire e so quando fermarmi

    lifo s;
    s.put(1);
    parent[1] = -1;
    depth[1] = 0;

    while (!s.empty()) {
        int u = s.get();
        for (int v : T.neighbours(u)) {
            if (v != parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                s.put(v);
            }
        }
    }
    return;
}

std::vector<int> findCycle(int a, int b, const std::vector<int>& parent, const std::vector<int>& depth) {
    int curr_a = a, curr_b = b;

    // uso questi al posto di un while per non dover ricalcolare ogni volta la condizione d'arresto
    int delta_a = depth[a] - depth[b];
    int delta_b = depth[b] - depth[a];
    for (int j = 0; j < delta_a; j++)
        curr_a = parent[curr_a];
    for (int j = 0; j < delta_b; j++)
        curr_b = parent[curr_b];
    while (curr_a != curr_b) {
        curr_a = parent[curr_a];
        curr_b = parent[curr_b];
    }
    int lca = curr_a;
    int len = (depth[a] - depth[lca]) + (depth[b] - depth[lca]) + 2; // il +2 è per aggiungere LCA e poter poi chiudere il ciclo
    std::vector<int> cycle(len); 
    cycle[0] = a;
    int j = 1;
    curr_a = a;
    curr_b = b;
    while (curr_a != lca) {
        curr_a = parent[curr_a];
        cycle[j] = curr_a;
        j++;
    }
    j = len - 2;
    while (curr_b != lca) {
        cycle[j] = curr_b;
        curr_b = parent[curr_b];
        j--;
    }
    cycle[len-1] = a;
    return cycle;
}

std::vector<std::vector<int>> findCycles(graph& G){
    std::vector<std::vector<int>> cycles;
    auto T = recursiveDFS(G,1);
    auto C = G-T;
    const int V = T.all_nodes().size();
    std::vector<int> parent(V + 1, -1);
    std::vector<int> depth(V + 1, 0);
    dfsLCA(T, parent, depth);

    for (const auto& edge:C.all_edges()){
        int a = edge.from();
        int b = edge.to();
        cycles.push_back(findCycle(a, b, parent, depth));
    }
    return cycles;
}