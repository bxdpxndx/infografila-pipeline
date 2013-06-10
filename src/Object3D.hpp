#ifndef Object3D_hpp
#define Object3D_hpp

#include <fstream>
#include <vector>

#include "Polygon.hpp"
#include "Exception.hpp"
#include "Matrix.hpp"

// Object3Ds actually own Vertexs and Polygons. other classes just have
// pointers to here.
class Object3D {

private:
    std::vector<Polygon> _polygons;
    std::vector<Vertex3D> _vertexs;


public:
    
    friend class Render;
    Object3D() {};

    // Object3D uses factory methods.
    static Object3D * from_file(std::string filename) {
        std::ifstream fe(filename.c_str());
        if(!fe.is_open()) {
            throw FileNotFoundException(filename);
        }

        Object3D * obj = new Object3D;
        int nvertexs, npolys;
        fe >> nvertexs >> npolys;

        float x, y, z;
        for (int i = 0; i < nvertexs; i++) {
            fe >> x >> y >> z;
            // rotate the object on load
            Vertex3D v(x,z,y);
            obj->_vertexs.push_back(v);
        }

        int nsides;
        for (int i = 0; i < npolys; i++) {
            fe >> nsides;
            Polygon p(nsides);
            int vertex_id;
            for (int j = 0; j < nsides; j++) {
                fe >> vertex_id;
                // remember the vertexs in the file start indexing with 1
                p.add_vertex(&(obj->_vertexs[vertex_id-1]));
            }
            assert(p.is_valid());
            obj->_polygons.push_back(p);
        }
        std::cout << "Cargados " << nvertexs << " vértices y " << npolys << " polígonos." << std::endl;
        return obj;
    }

    void apply_matrix_transform(const Matrix & matrix) {
        for(std::vector<Vertex3D>::iterator it = _vertexs.begin(); it != _vertexs.end(); it++) {
            *it = matrix * (*it);
            
            it->project();
        }
    }

    void calculateAllNormals() {
        // reset vertex normals
        for(std::vector<Vertex3D>::iterator it = _vertexs.begin(); it != _vertexs.end(); it++) {
            it->_normal = Vector3D(0, 0, 0);
        }

        // calc poly normals and add them to vertex normals
        for (std::vector<Polygon>::iterator it = _polygons.begin(); it != _polygons.end(); it++) {
            it->NormalV();
            it->addNormalToVertexs();
        }
        
        // normalize vertex normals
        for(std::vector<Vertex3D>::iterator it = _vertexs.begin(); it != _vertexs.end(); it++) {
            it->_normal.normalize();
        }
    }

    friend std::ostream & operator<<(std::ostream & os, const Object3D &o);

};

std::ostream & operator<<(std::ostream & os, const Object3D &o) {
    os << "Object" << std::endl;
    for (std::vector<Polygon>::const_iterator it = o._polygons.begin(); it != o._polygons.end(); it++) {
        os << *it << std::endl;
    }
    return os;
}


#endif // Object3D_hpp

