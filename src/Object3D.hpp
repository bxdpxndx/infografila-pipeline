#ifndef Object3D_hpp
#define Object3D_hpp

#include <fstream>
#include <vector>

#include "Polygon.hpp"


// Object3Ds actually own Vertexs and Polygons. other classes just have
// pointers to here.
class Object3D {

private:
    std::vector<Polygon *> _polygons;
    std::vector<Vertex3D *> _vertexs;

public:
    Object3D() {};

    ~Object3D() {
        for(auto it = _polygons.begin(); it != _polygons.end(); it++) {
            delete (*it);
        }
        for(auto it = _vertexs.begin(); it != _vertexs.end(); it++) {
            delete (*it);
        }
    }

    void add_polygon (Polygon * p) {
        _polygons.push_back(p);
    }

    void add_vertex (Vertex3D * v) {
        _vertexs.push_back(v);
    }

    // Object3D uses factory methods.
    static Object3D * from_file(std::string filename) {
        Object3D * obj = new Object3D;
        std::ifstream fe(filename);
        if(!fe.is_open()) {
            std::cout << "-!- error abriendo el fichero " << filename << std::endl;
        }
        int nvertexs, npolys;
        fe >> nvertexs >> npolys;

        float x, y, z;
        for (int i = 0; i < nvertexs; i++) {
            fe >> x >> y >> z;
            obj->add_vertex(new Vertex3D(x,y,z));
        }

        int nsides;
        for (int i = 0; i < npolys; i++) {
            fe >> nsides;
            Polygon *p = new Polygon(nsides);
            int vertex_id;
            for (int j = 0; j < nsides; j++) {
                fe >> vertex_id;
                // remember the vertexs in the file start indexing with 1
                p->add_vertex(obj->_vertexs[vertex_id+1]);
            }
            assert(p->is_valid());
            obj->add_polygon(p);
        }

        return obj;
    }

    void apply_matrix_transform(const Matrix & matrix) {
        for( auto it = _vertexs.begin(); it != _vertexs.end(); it++) {
            **it = matrix * (**it);
        }
    }

    // expose the polygons
    typename std::vector<Polygon *>::const_iterator polys_begin() const {
        return _polygons.begin();
    }

    typename std::vector<Polygon *>::const_iterator polys_end() const {
        return _polygons.end();
    }
};

#endif // Object3D_hpp
