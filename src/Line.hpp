#ifndef Line_hpp
#define Line_hpp

#include <iostream>

#include "Vertex3D.hpp"
#include "Matrix.hpp"


class Line {
// Sólo un par de Vértices.

public:
    Vertex3D start, end;

    Line(Vertex3D st, Vertex3D en) : start(st), end(en) {};

    void flip() {
        std::swap(start, end);
    }

    void transform(Matrix m) {
        start = m * start;
        end = m * end;
    }

    bool is_vertical() {
        return abs(end.x - start.x) < abs(end.y - start.y);
    }

    friend std::ostream & operator<<(std::ostream & os, const Line & l) {
        os << l.start << " - " << l.end;
        return os;
    }
};



#endif // Line_hpp
