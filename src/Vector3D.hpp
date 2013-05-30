#ifndef Vector3D_hpp
#define Vector3D_hpp

class Vector3D {

public:

    union {
        struct {
            float x, y, z, w;
        };
        float coords[4];
    };
    
    Vector3D(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in), w(1) {};
    Vector3D() : x(0), y(0), z(0), w(0) {};

    float get(int i) {
        return coords[i];
    }

    void set(float value, int i) {
        coords[i] = value;
    }
};

std::ostream & operator<<(std::ostream &os, const Vector3D & v)
    {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

#endif // Vector3D_hpp

