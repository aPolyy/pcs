#pragma once

#include <vector>
#include <Eigen/Dense>
#include <Eigen/SVD>

// todo list
// 1) capire se la tolleranza è assoluta o relativa
// 2) dare in output anche le iterazioni fatte e la tolleranza raggiunta
// 3) capire se va templatizzato o se questa cosa va messa in header o meno etc
// 4) prendere in input iterazioni massime e tolleranza e impostarne di standard se non vengono date
Eigen::VectorXd cg(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, const Eigen::VectorXd& x0, const int maxit, const double tol, int& it, double& rel_err) {
    std::vector<Eigen::VectorXd> x;
    std::vector<Eigen::VectorXd> r;
    std::vector<Eigen::VectorXd> p;
    std::vector<double> alpha;
    std::vector<double> beta;

    x.push_back(x0);
    r.push_back(b - A * x0);
    p.push_back(r[0]);

    for (it = 0; it < maxit; it++) {
        alpha.push_back((p[it].dot(r[it]))/(p[it].dot(A * r[it])));
        x.push_back(x[it] + alpha[it] * p[it]);
        r.push_back(b - A * x[it+1]);
        beta.push_back( (p[it].dot(A * r[it+1])) / (p[it].dot(A * p[it])));
        p.push_back(r[it+1] - beta[it] * p[it]);

        if (r[it+1].norm() < tol)
            break;
    }

    rel_err = 0.0; // todo
    return x.back();
}