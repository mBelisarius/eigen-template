#include "information.h"
#include <Eigen/Dense>
#include <iostream>

int main()
{
    std::cout << "Code version: " << eig_tmpl::getVersion()
              << std::endl << std::endl;

    Eigen::Matrix3d A;
    A << 2, -1, 0, -1, 2, -1, 0, -1, 2;

    Eigen::Vector3d b;
    b << 0, 0, 4;

    Eigen::LLT<Eigen::Matrix3d> llt;

    std::cout << "Here is the matrix A:\n" << A
              << std::endl << std::endl;
    std::cout << "Here is the right hand side b:\n" << b
              << std::endl << std::endl;

    std::cout << "Computing LLT decomposition..." << std::endl;
    llt.compute(A);

    std::cout << "Solving the system..." << std::endl;
    auto sol = llt.solve(b);
    std::cout << "The solution is:\n" << sol << std::endl;

    return 0;
}
 