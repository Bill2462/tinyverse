#ifndef COMMON_TYPES_HPP_INCLUDED
#define COMMON_TYPES_HPP_INCLUDED

#include <eigen3/Eigen/Dense>

// Real number used through the simulation.
typedef float Real;

// Matrix for storing a sequence of 3D vectors.
typedef Eigen::Matrix<Real, Eigen::Dynamic, 3, Eigen::RowMajor> Vectors3D;

// Vector of numbers.
typedef Eigen::Matrix<Real, Eigen::Dynamic, 1> Vector;


#endif
