#ifndef Vertex3D_hpp
#define Vertex3D_hpp

#include <cassert>

#include "Vector3D.hpp"

class Vertex3D {

public:
    union {
        struct {
            float x, y, z, w;
        };
        float coords[4];
    };

    Vertex3D(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in), w(1) {};
    Vertex3D() : x(0), y(0), z(0), w(1) {};

    float get(int i) const {
        return coords[i];
    }

    void set(float value, int i) {
        coords[i] = value;
    }

    Vector3D operator-(const Vertex3D & other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    void project() {
        assert( w > 0 );
        x /= w;
        y /= w;
        z /= w;
        w = 1;
    }
};

std::ostream & operator<<(std::ostream &os, const Vertex3D & v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

#endif // Vertex3D_hpp
