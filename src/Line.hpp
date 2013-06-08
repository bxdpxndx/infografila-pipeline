#ifndef Line_hpp
#define Line_hpp

#include <iostream>

#include "Vertex3D.hpp"

class Line {
// Sólo un par de Vértices.

public:
    Vertex3D *start, *end;

    Line(Vertex3D *st, Vertex3D *en) : start(st), end(en) {};

    float getStepness() {
        return (end->x - start->x) / (end->y - start->y);
    }

    friend std::ostream & operator<<(std::ostream & os, const Line & l) {
        os << *(l.start) << " - " << *(l.end);
        return os;
    }
};

#endif // Line_hpp

