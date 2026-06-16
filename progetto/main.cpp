#include <iostream> 
#include <vector>
#include "parse.h"
#include "depina.h"
#include "graph.h"
#include "graph_utils.h"
#include "cammini_dfs.h"
#include "eigen_utils.h"
#include <Eigen/Dense>  


int main(){

    graph grafo = parse("testrotto.txt");
    
    // se vogliamo cammini dfs cicli non minimi
    std::vector<std::vector<int>> C = cammini_dfs(grafo);

    // se vogliamo dfs con lca
    //std::vector<std::vector<int>> C = findCycles(grafo);

    // se vogliamo depina cicli minimi
    //std::vector<std::vector<int>> C = depina(grafo);


    auto B = build_B(grafo, C);
    auto R = build_R(grafo);
    auto v = build_v(grafo, C);
/*
    std::cout<< "B: \n" << B <<'\n';
    std::cout<< "R: \n" << R <<'\n';
    std::cout<< "v: \n" << v <<'\n';
*/
    auto A = B.transpose() * R * B;
    auto x0 = Eigen::VectorXd::Zero(v.size());
    unsigned int iterations_used;
    auto I = conj_grad(A, v, x0, 1e-6, 1000, iterations_used);
    //std::cout << "Solution I:\n" << I << "\n";
    auto res = R * B * I;
    std::cout << "Tensioni:\n" << res << "\n";

}