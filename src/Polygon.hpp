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
    Vector3D normal;


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
			 P.x= (_vertexs[1]->x) - (_vertexs[0]->x);
			 P.y= (_vertexs[1]->y) - (_vertexs[0]->y);
			 P.x= (_vertexs[1]->z) - (_vertexs[0]->z);
			 Q.x= (_vertexs[2]->x) - (_vertexs[0]->x);
			 Q.y= (_vertexs[2]->y) - (_vertexs[0]->y);
			 Q.x= (_vertexs[2]->z) - (_vertexs[0]->z);
		
			//Vector normal a los vectores P y Q
			normal.x = (P.y * Q.z) - (P.z*Q.y);
			normal.y = (P.z * Q.x) - (P.x*Q.z);
			normal.z = (P.x * Q.y) - (P.y*Q.x);
			
			//Mmodulo de la normal.
			float Modulo = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
			
			//Notmlaizar.
			normal.x /= Modulo;
			normal.y /= Modulo;
			normal.z /= Modulo;
			
		}

};

std::ostream & operator<<(std::ostream & os, const Polygon& poly) {
    os << "Polígono de " << poly._nvertexs << " lados:" << std::endl;
    for(unsigned i=0; i < poly._vertexs.size(); ++i) {
        os << "  " << poly._vertexs[i] << std::endl;
    }
    return os;
}



#endif //Polygon_hpp
