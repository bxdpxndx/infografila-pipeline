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

    int nvertexs() const { return _nvertexs; };

    friend std::ostream & operator<<(std::ostream &os, const Polygon & p)
    {
        os << p.nvertexs() << "-sided polygon" << std::endl;
        return os;
    }
/*
    //==============================================================
    //un triangulo tiene tres vertices. v1 v2 v3
    //p es el vector de v1v2 y q v1v3
    
    void vectorPQ(){
		float x,y,z;
		std::cout<<"Tamaño"<<_vertexs.size()<<std::endl;
		for(std::vector<Vertex3D*>::iterator it = _vertexs.begin(); it != _vertexs.end(); ++it) { 
				 (*it)->getxyz(x,y,z);
				 std::cout<< x << " " << y <<" "<< z  <<std::endl;
			}
		}
    //==============================================================
*/
};

#endif //Polygon_hpp
