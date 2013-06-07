#ifndef Object3D_hpp
#define Object3D_hpp

#include <fstream>
#include <vector>

#include "Polygon.hpp"


// Object3Ds actually own Vertexs and Polygons. other classes just have
// pointers to here.
class Object3D {

private:
    std::vector<Polygon> _polygons;
    std::vector<Vertex3D> _vertexs;

	void calculateAllNormals() {
		for( std::vector<Polygon>::iterator it = _polygons.begin(); it != _polygons.end(); it++) {
			it->NormalV();
			it->addNormalToVertexs();
		}
	}

public:
    Object3D() {};

    // Object3D uses factory methods.
    static Object3D * from_file(std::string filename) {
        Object3D * obj = new Object3D;
        std::ifstream fe(filename.c_str());
        if(!fe.is_open()) {
            std::cout << "-!- error abriendo el fichero " << filename << std::endl;
        }
        int nvertexs, npolys;
        fe >> nvertexs >> npolys;

        float x, y, z;
        for (int i = 0; i < nvertexs; i++) {
            fe >> x >> y >> z;
            Vertex3D v(x,y,z);
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
		obj->calculateAllNormals();
        std::cout << "Cargados " << nvertexs << " vértices y " << npolys << " polígonos." << std::endl;
        return obj;
    }

    void apply_matrix_transform(const Matrix & matrix) {
        std::cout << matrix << std::endl;
        for( std::vector<Vertex3D>::iterator it = _vertexs.begin(); it != _vertexs.end(); it++) {
            *it = matrix * (*it);
            it->project();
        }
    }

    // expose the polygons
    typename std::vector<Polygon>::const_iterator polys_begin() const {
        return _polygons.begin();
    }

    typename std::vector<Polygon>::const_iterator polys_end() const {
        return _polygons.end();
    }
    
};

#endif // Object3D_hpp
