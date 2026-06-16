#pragma once

#include <fstream>
#include <string>
#include <stdexcept>
#include "graph.h"

graph parse(std::string fname) {
    graph g;
    std::ifstream ifs(fname);
    if (ifs.is_open()) {
        while (!ifs.eof()) {
            int v1, v2;
            double w;
            std::string edge_type;
            
            ifs >> edge_type;
            
            // serve se c'è un \n di troppo nel file
            if (ifs.fail()) {
                break;
            }

            ifs >> w;
            ifs >> v1;
            ifs >> v2;

            if (edge_type[0] == 'V' && v1 < v2)
                w = -w;//sistema il segno per i generatori, che sono negativi se v1 < v2 e positivi altrimenti

            g.add_edge(edge(v1, v2, w, (edge_type[0] == 'R' ? 1 : 0))); //determina se è un generatore o una resistenza 
        }
        ifs.close();
    }
    else 
        throw std::invalid_argument("nome file non valido");
    g.update_maps();
    return g;
}

