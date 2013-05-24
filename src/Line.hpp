#ifndef Line_hpp
#define Line_hpp
#include "Vertex3D.hpp"

class Line {

private:
    Vertex3D _start, _end;

public:

    Vertex3D start() { return _start; };
    Vertex3D end() { return _end; };

    void flip() {
        std::swap(_start, _end);
    }

    void draw(Image & image) {
        // TODO hehehe
    }
};



#endif // Line_hpp
