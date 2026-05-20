#pragma once

#include <vector>
#include <Eigen/Dense>
#include <Eigen/SVD>

// codice preso dall'esempio dato a lezione
double condA(const Eigen::MatrixXd& A)
{
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
  Eigen::VectorXd singularValuesA = svd.singularValues();
  return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}

// todo list
// 1) capire se la tolleranza è assoluta o relativa
// 2) dare in output anche le iterazioni fatte e la tolleranza raggiunta
// 3) capire se va templatizzato o se questa cosa va messa in header o meno etc
// 4) prendere in input iterazioni massime e tolleranza e impostarne di standard se non vengono date
Eigen::VectorXd cg(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, const Eigen::VectorXd& x0, const int maxit, const double tol) {
    std::vector<Eigen::VectorXd> x;
    std::vector<Eigen::VectorXd> r;
    std::vector<Eigen::VectorXd> p;
    std::vector<double> alpha;
    std::vector<double> beta;

    x.push_back(x0);
    r.push_back(b - A * x0);
    p.push_back(r[0]);

    for (int k = 0; k < maxit; k++) {
        alpha[k] = (p[k].dot(r[k]))/(p[k].dot(A * r[k]));
        x.push_back(x[k] + alpha[k] * p[k]);
        r.push_back(b - A * x[k+1]);
        beta.push_back( (p[k].dot(A * r[k+1])) / (p[k].dot(A * p[k])));
        p.push_back(r[k+1] - beta[k] * p[k]);

        if (r[k+1].norm() < tol)
            break;
    }

    return x.back();
}