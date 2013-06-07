#ifndef Polygon_hpp
#define Polygon_hpp

#include <vector>
#include <ostream>
#include <math.h>
#include "Vertex3D.hpp"
#include "Vector3D.hpp"
#include "Line.hpp"

class Vertex;

class Polygon {

private:

    unsigned _nvertexs;
    std::vector<Vertex3D*> _vertexs;
    Vector3D _normal;


public:

    class LineIterator {
		private:
			const Polygon * const _poly;
			int _pointer;
		public:
			LineIterator(const Polygon * const poly, int start) : _poly(poly), _pointer(start) {};

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

    LineIterator lines_begin() const {
        return LineIterator(this, 0);
    }

    LineIterator lines_end() const {
        return LineIterator(this, _nvertexs);
    }

    friend std::ostream & operator<<(std::ostream &os, const Polygon & poly);
    
    void NormalV (){//Solo triangulos
			 
			 //Calculo vectores P y Q qye unen los 
			 //vertices V1V2V3 de un triangulo.
			 Vector3D P,Q;
			 P= *_vertexs[1] - *_vertexs[0];
			 Q= *_vertexs[2] - *_vertexs[0];

			//Vector normal a los vectores P y Q
			_normal=P.vectorial_product(Q);
	
			_normal.normalize();
			
	}

	void addNormalToVertexs() {
		for (std::vector<Vertex3D *>::iterator it = _vertexs.begin(); it != _vertexs.end(); it ++) {
			(*it)->addNormal(_normal);
		}
	}

};

std::ostream & operator<<(std::ostream & os, const Polygon& poly) {
    os << "Polígono de " << poly._nvertexs << " lados:" << std::endl;
    os << "Normal: " << poly._normal << std::endl;

    for(unsigned i=0; i < poly._vertexs.size(); ++i) {
        os << "  " << *(poly._vertexs[i]) << std::endl;
    }
    return os;
}



#endif //Polygon_hpp
