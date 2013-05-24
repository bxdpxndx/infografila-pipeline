#ifndef Point3D_hpp
#define Point3D_hpp


class Point3D {

public:

    float x, y, z;
    Point3D(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in) {};

private:
    
    friend std::ostream & operator<<(std::ostream &os, const Point3D & v)
    {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
};

#endif // Point3D_hpp

