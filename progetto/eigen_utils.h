#include <iostream>
#include "graph.h"
#include <Eigen/Dense>

Eigen::MatrixXd build_R (const graph& g) {
    //crea la matrice R a partire dal grafo g, mettendo i pesi delle resistenze sulla diagonale
    const int p = g.count_res();//numero di resistenze
    Eigen::MatrixXd R(p, p);
    int k = 0;
    for (auto& e : g.all_edges()) {
        if (e.is_r() == 1) {
            R(k, k) = e.weight();
            k++;    
        }
    }
    return R;
}

Eigen::VectorXd build_v (const graph& g, const std::vector<std::vector<int>>& C) {
    //crea il vettore v a partire dal grafo g e dai cicli C
    const int sz = C.size();//numero di cicli
    Eigen::VectorXd v(sz);
    for (int i = 0; i < sz; i++) {
        for (long unsigned int j = 0; j < C[i].size() - 1; j++) {
            edge e = *g.all_edges().find(edge(C[i][j], C[i][j + 1]));//trovo l'arco e nel ciclo C[i] che va da C[i][j] a C[i][j+1] 
            if (e.is_r() == 0) {//se è un generatore
                int sign = (C[i][j] < C[i][j+1] ? 1 : -1);//segno positivo dal minore al maggiore
                v[i] += sign * e.weight();
            }
        }
    }
    return v;
}

Eigen::MatrixXd build_B(graph& g, std::vector<std::vector<int>>& C) {
    int E = g.count_res();
    int n_maglie = C.size();
    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(E, n_maglie);
    int j = 0;

    for (auto& Ci : C){
        for(long unsigned int i = 0; i < Ci.size() - 1; i++){
            edge e = *g.all_edges().find(edge(Ci[i], Ci[i+1]));//otiengo l'arco
            if(e.is_r() == 1){//se è una resistenza
                int sign = (Ci[i] < Ci[i+1] ? 1 : -1);//positivo dal minore al maggiore
                int edge_n = g.find_resId(e);//trovo l'id dell'arco e nell'insieme ordinato di sole resistenze
                B(edge_n,j) = sign;
           }
        }
        j++;
    }
    return B;
}

Eigen::VectorXd conj_grad(const Eigen::MatrixXd& A, 
                                  const Eigen::VectorXd& b, 
                                  const Eigen::VectorXd& x0, 
                                  double tol, 
                                  unsigned int it_max,
                                  unsigned int& iterations_used)
{
    Eigen::VectorXd x = x0;
    Eigen::VectorXd res = b - A * x;
    Eigen::VectorXd dir = res; // Nel primo passo, la direzione coincide con il residuo

    double res_norm_0 = res.norm();
    unsigned int it = 0;

    while (it < it_max &&
        res.norm() > tol * res_norm_0)
    {
    const double alpha_k = (dir.transpose() * res).value() / (dir.transpose() * A * dir).value();

    x = x + alpha_k * dir;
    res = b - A * x;

    const double beta_k = (dir.transpose() * A * res).value() / (dir.transpose() * A * dir).value();
    dir = res - beta_k * dir;

    it++;
    }
    iterations_used = it;
    return x;
}
