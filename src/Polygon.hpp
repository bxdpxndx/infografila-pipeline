#ifndef Polygon_hpp
#define Polyhon_hpp
#include <vector>
#include <ostream>

class Polygon {

private:
    
    const int _nvertexs;
    std::vector<Vertex*> _vertexs;

public:
    Polygon(int nv) : _nvertexs(nv) {};

    void add_vertex(Vertex * v) {
        _vertexs.push_back(v);
    }

    bool is_valid() {
        return _nvertexs == _vertexs.size();
    }

    int nvertexs() const { return _nvertexs; };

    friend std::ostream & operator<<(std::ostream &os, const Polygon & p)
    {
        os << p.nvertexs() << "-sided polygon";
        return os;
    }
};

#endif //Polygon_hpp
