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

    Vector3D(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in), w(0) {};
    Vector3D() : x(0), y(0), z(0), w(0) {};

    float get(int i) const{
        return coords[i];
    }

    void set(float value, int i) {
        coords[i] = value;
    }

    float length() const {
        return sqrt(this->dot_product(*this));
    }

    Vector3D operator* (float f) const {
        return Vector3D(x * f, y * f, z * f);
    }

    float dot_product(const Vector3D & other) const {
        return (x * other.x) + (y * other.y) + (z * other.z);
    }

    Vector3D operator-(const Vector3D & other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D vectorial_product(const Vector3D & other) const {
        return Vector3D(y * other.z - z * other.y,
                        z * other.x - x * other.z,
                        x * other.y - y * other.x
                        );
    }

    void normalize() {
        float l = length();
        x /= l;
        y /= l;
        z /= l;
    }
};

std::ostream & operator<<(std::ostream &os, const Vector3D & v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

#endif // Vector3D_hpp

