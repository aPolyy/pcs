#pragma once

#include <vector>
#include <Eigen/Dense>
#include <Eigen/SVD>

Eigen::VectorXd cg(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, const Eigen::VectorXd& x0, const int maxit, const double tol, int& it, double& rel_err) {
    Eigen::VectorXd x;
    Eigen::VectorXd r, r0;
    Eigen::VectorXd p;
    double alpha, beta;

    x = x0;
    r = b - A * x0;
    p = r;
    r0 = r;

    // il testo dice che il for può essere sostituito con questo
    // while (r.norm() > tol * r0.norm()) { 

    for (it = 0; it < maxit; it++) {
        alpha = (p.dot(r))/(p.dot(A * p));
        x = x + alpha * p;
        r = b - A * x;
        beta = (p.dot(A * r)) / (p.dot(A * p));
        p = r - beta * p;

        if (r.norm() < tol * r0.norm())
            break;

    }

    rel_err = r.norm() / r0.norm(); 
    return x;
}