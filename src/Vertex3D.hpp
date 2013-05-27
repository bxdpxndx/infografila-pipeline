#ifndef Vertex3D_hpp
#define Vertex3D_hpp
#include "Point3D.hpp"

class Vertex3D : public Point3D {

public:
    Vertex3D(float x_in, float y_in, float z_in) : Point3D(x_in, y_in, z_in) {};
    Vertex3D() : Point3D() {};


};


#endif // Vertex3D_hpp
