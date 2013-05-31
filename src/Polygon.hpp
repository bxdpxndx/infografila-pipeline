#ifndef Polygon_hpp
#define Polygon_hpp

#include <vector>
#include <ostream>

#include "Vertex3D.hpp"
#include "Vector3D.hpp"
#include "Line.hpp"

class Vertex;

class Polygon {

private:

    const unsigned _nvertexs;
    std::vector<Vertex3D*> _vertexs;
    Vector3D normal;


public:

    class LineIterator {
    private:
        Polygon *_poly;
        int _pointer;
    public:
        LineIterator(Polygon * poly, int start) : _poly(poly), _pointer(start) {};

        Line operator*() const {
            return Line(_poly->_vertexs[_pointer], _poly->_vertexs[(1 + _pointer) % _poly->_nvertexs]);
        }

        LineIterator & operator++() {
            ++_pointer;
            return *this;
        }

        LineIterator operator++(int) {
            LineIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const LineIterator & other) const {
            return _poly == other._poly && _pointer == other._pointer;
        }

        bool operator!=(const LineIterator & other) const {
            return ! (*this == other);
        }
    };

    Polygon(int nv) : _nvertexs(nv) {
        _vertexs.reserve(nv);
    }

    void add_vertex(Vertex3D *v) {
        _vertexs.push_back(v);
    }

    bool is_valid() const {
        return _nvertexs == _vertexs.size();
    }

    int nvertexs() const {
        return _nvertexs;
    };

    LineIterator lines_begin() {
        return LineIterator(this, 0);
    }

    LineIterator lines_end() {
        return LineIterator(this, _nvertexs);
    }

    friend std::ostream & operator<<(std::ostream &os, const Polygon & poly);

};

std::ostream & operator<<(std::ostream & os, const Polygon& poly) {
    os << "Polígono de " << poly._nvertexs << " lados:" << std::endl;
    for(unsigned i=0; i < poly._vertexs.size(); ++i) {
        os << "  " << poly._vertexs[i] << std::endl;
    }
    return os;
}



#endif //Polygon_hpp
