#ifndef Vertex_hpp
#define Vertex_hpp

class Vertex {

public:
    const union {
        struct { float x; float y; float z; };
        float v[3];
    };

    Vertex(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in) {};

};

#endif //Vertex_hpp
