#ifndef Polygon_hpp
#define Polygon_hpp

#include <vector>
#include <ostream>

#include "Vertex3D.hpp"
#include "Vector3D.hpp"

class Vertex;

class Polygon {

private:

    const unsigned _nvertexs;
    std::vector<Vertex3D*> _vertexs;
    Vector3D normal;

public:

    Polygon(int nv) : _nvertexs(nv) {};

    void add_vertex(Vertex3D *v) {
        _vertexs.push_back(v);
    }

    bool is_valid() {
        return _nvertexs == _vertexs.size();
    }

    int nvertexs() const {
        return _nvertexs;
    };

    friend std::ostream & operator<<(std::ostream &os, const Polygon & p)
    {
        os << p.nvertexs() << "-sided polygon" << std::endl;
        return os;
    }

    void recorrer() {
        for(unsigned i=0; i < _vertexs.size(); ++i) {
            std::cout << _vertexs[i];
        }
        std::cout<<std::endl;
    }
};

#endif //Polygon_hpp
