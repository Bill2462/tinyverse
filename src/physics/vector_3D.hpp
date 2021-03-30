#ifndef VECTOR_3D_HPP_INCLUDED
#define VECTOR_3D_HPP_INCLUDED

#include <math.h>

template<typename T>
struct Vector3D
{
    T x;
    T y;
    T z;
    
    T norm2() const
    {
        return sqrt(x*x + y*y + z*z);
    }
};

#endif
