#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include "cg.h"

double condA(const Eigen::MatrixXd& A) {
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
    Eigen::VectorXd singularValuesA = svd.singularValues();
    return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}

int main() {
    const double tol = 1.0e-15;
    unsigned int n = 10;

    Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);

    if (abs(B.determinant()) < tol)
    return -1;

    Eigen::MatrixXd A = B.transpose() * B;
    Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);

    Eigen::VectorXd b = A * x_ex;

    const unsigned int maxit = 100;
    const double res_tol = 1.0e-12;

    std::cout.precision(5);
    std::cout<< std::scientific<< "Matrix Cond: "<< condA(A)<< std::endl;

    int it;
    double rel_err;
    Eigen::VectorXd x = cg(A, b, Eigen::VectorXd::Zero(n), maxit, res_tol, it, rel_err);
    auto res = A * x - b;


    std::cout.precision(4);
    std::cout<< "it"<< "/"<< "maxit: ";
    std::cout<< std::scientific<< it << "/"<< maxit << std::endl;

    std::cout<< std::scientific<< "res norm: ";
    std::cout<< std::scientific<< res.norm() << std::endl;

    std::cout<< "rel_err: ";
    std::cout<< std::scientific<< rel_err << std::endl;

    std::cout<<"sol: ";
    std::cout<< std::scientific<< x << std::endl;


    return 0;
}
