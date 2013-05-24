#ifndef Vertex_hpp
#define Vertex_hpp

#include "Polygon.hpp"

class Vertex {

public:
    int id;
    const union {
        struct { float x; float y; float z; };
        float coords[3];
    };

    Vertex(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in), id(0) {};

private: 

    std::vector<Polygon*> _polygons;
    
    friend std::ostream & operator<<(std::ostream &os, const Vertex & v)
    {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

};

#endif //Vertex_hpp
