#ifndef Vector3D_hpp
#define Vector3D_hpp
#include "Point3D.hpp"

class Vector3D : public Point3D {

public:
    Vector3D(float x_in, float y_in, float z_in) : Point3D(x_in, y_in, z_in) {};
    Vector3D() : Point3D() {};
};

#endif // Vector3D_hpp

