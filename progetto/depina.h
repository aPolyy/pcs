#pragma once

#include <vector>
#include "graph.h"
#include "graph_utils.h"


std::vector<bool> vxor(const std::vector<bool>& v1, const std::vector<bool>&  v2) {
    if (v1.size() != v2.size()) 
        throw std::invalid_argument("Dimensioni non valide.");

    std::vector<bool> v(v1.size());
    for (long unsigned int i = 0; i < v2.size(); i++)
        v[i] = v1[i] ^ v2[i];
    return v;
}

int vprod(const std::vector<bool>& v1, const std::vector<bool>&  v2) {
    int res = 0;
    for (long unsigned int i = 0; i < v1.size(); i++)
        res ^= (v1[i] && v2[i]);
    return res;
}

// NB. La funzione assume che i nodi del grafo siano indicizzati sequenzialmente e 1-indexed
// cioè 1, 2, ..., V dove V = |nodes|
graph lift(const graph& g, const std::vector<bool>& S_i) {
    //restituisce il grafo liftato g_lift del grafo g rispetto al vettore S_i
    const int V = g.all_nodes().size();
    graph g_lift;
    int id = 0;
    int v1, v2;
    for (auto& e : g.all_edges()) {
        v1 = e.from();
        v2 = e.to();
        if (S_i[id] == true) {
            //aggiunge archi incrociati (v+, u-) e (v-, u+) 
            g_lift.add_edge(edge(v1, v2 + V));
            g_lift.add_edge(edge(v1 + V, v2));
        }
        else {
            //aggiunge archi paralleli (v+, u+) e (v-, u-)
            g_lift.add_edge(edge(v1, v2));
            g_lift.add_edge(edge(v1 + V, v2 + V));
        }
        id++;
    }
    return g_lift;
}

std::vector<bool> find_minimal_cycle(const graph& g, const std::vector<bool>& S_i) {
    //trova il ciclo minimo del grafo g con prodotto scalare 1 rispetto al vettore S_i
    const int V = g.all_nodes().size();
    const int E = g.all_edges().size();
    std::vector<bool> C_best(E), C_mu(E);
    graph g_lift = lift(g, S_i); //grafo liftato
    int szbest = E + 1;
    int sz;
    for (int source = 1; source <= V; source++) {
        sz = 0;
        std::fill(C_mu.begin(), C_mu.end(), false);

        auto pred = dijkstra(g_lift, source);//mappa dei predecessori del grafo liftato
        int node = source + V;
        
        // se il nodo non è raggiungibile faccio un'altra iterazione
        if (pred[node] == 0)
            continue; 
        
        while (node != source) {
            edge e((node <= V ? node : node - V), (pred[node] <= V ? pred[node] : pred[node] - V));//proeitto su G
            int id = g.edge_number(e);
            if (C_mu[id] == false) 
                sz++;
            else 
                sz--;
            C_mu[id] = !C_mu[id];
            node = pred[node];
        }
        if (sz < szbest) {
            szbest = sz;
            C_best = C_mu;
        }
    }
    return C_best;
}

std::vector<std::vector<bool>> coalbero_to_depina(const graph& g) {
    //restitusice i vettori Si per Depina
    auto albero = recursiveDFS(g, 1);
    auto coalbero = g - albero;
    std::vector<std::vector<bool>> S;
    for (const auto& e : coalbero.all_edges()) {
        std::vector<bool> S_i(g.all_edges().size(), false);//tutti 0
        int id = g.edge_number(e);
        S_i[id] = true;
        S.push_back(S_i);
    }
    return S;
}

std::vector<int> vbool_to_cycle(const std::vector<bool>& vbool, const graph& g) {
    //restituisce il ciclo del grafo g corrispondente al vettore vbool
    std::vector<int> ciclo;
    int start_node = -1;
    for (const auto& e : g.all_edges()) {
        if (vbool[g.edge_number(e)]) {//non appena trovato il primo arco del ciclo, lo uso per trovare il nodo di partenza  
            start_node = e.from(); 
            break;
        }
    }
    
    if (start_node == -1) {
        std::cout<< "ciclo vuoto\n";
        return ciclo;
    }

    int u = start_node;
    int prev = -1; 
    
    int next_node = -1;
    while (next_node != start_node) {
        ciclo.push_back(u);
        next_node = -1;
        
        for (int v : g.neighbours(u)) {
            if (v == prev) 
                continue; //saltiamo il nodo precedente per evitare di tornare indietro
            auto it = g.all_edges().find(edge(u, v));// prendo l'arco (u, v) se esiste
                int id = g.edge_number(*it);//find restituisce un iteratore, quindi devo dereferenziare per ottenere l'arco
                if (vbool[id]) { 
                    next_node = v;
                    break;
            }
        }
        
        if (next_node == -1) {
            std::cerr << "Ciclo non valido" << std::endl;
            break; 
        }
        
        prev = u;
        u = next_node;
    }
    ciclo.push_back(start_node); //aggiungo il nodo di partenza alla fine per chiudere il ciclo
    return ciclo;
}

std::vector<std::vector<int>> depina(const graph& g) {
    //restitusice i cicli minimi del grafo g usando l'algoritmo di Depina
    std::vector<std::vector<bool>> C_vbool;
    std::vector<std::vector<int>> C; 
    
    auto S = coalbero_to_depina(g);
    int k = size(S);

    for (int i = 0; i < k ; i++) {
        auto vbool = find_minimal_cycle(g, S[i]);//trova il ciclo minimo del grafo g con prodotto scalare 1 rispetto al vettore S[i]
        C_vbool.push_back(vbool);
        C.push_back(vbool_to_cycle(vbool, g));
        
        for (int j = i + 1; j < k; j++) {//per ogni ciclo trovato, aggiorna i vettori S[j] con xor se il prodotto scalare è 1
            if (vprod(C_vbool[i], S[j]) == 1) {
                S[j] = vxor(S[j], S[i]);
            }
        }
    }
    
    return C;
}



