#ifndef COMMON_TYPES_HPP_INCLUDED
#define COMMON_TYPES_HPP_INCLUDED

#include <eigen3/Eigen/Dense>

// Matrix for storing a sequence of 3D vectors.
typedef Eigen::Matrix<float, Eigen::Dynamic, 3, Eigen::RowMajor> Vectors3D;
typedef Eigen::Matrix<float, Eigen::Dynamic, 1> Vector;

// Real number used through the simulation.
typedef float Real;

#endif
