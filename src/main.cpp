#include <iostream> // std::cout
#include <fstream> // std::ifstream
#include <vector>

#include <assert.h>
#include "Vertex3D.hpp"
#include "Polygon.hpp"
#include "Object.hpp"

int main(void)
{
	
	std::ifstream fe("info_data.dat");//fe => "fichero entrada" abrir fichero para lectura
	
	//estrucura de lectura
	// nº vertices espacio nº poligonos (primera linea)
	//coordenadas a espacio b espacio c (segunda en adelante) 
	
    if(!fe.is_open()) { 
        std::cout << "-!- error abriendo el fichero -!-" << std::endl; 
        return 1;
    } 

	int nvertices;
	int npoligonos;
	fe >> nvertices >> npoligonos;

    std::vector<Vertex3D*> vertexs;

    float x, y, z;
	for (int i = 0; i < nvertices; i++) {
        fe >> x >> y >> z;
        vertexs.push_back(new Vertex3D(x,y,z));
	}
	std::cout << "Cargados " << nvertices << " vértices." << std::endl;

    Object object;
    int nsides;
	for (int i = 0; i < npoligonos; i++) {
        fe >> nsides;
        Polygon *p = new Polygon(nsides);
        int vertex_id;
        for (int j = 0; j < nsides; j++) {
            fe >> vertex_id;
            p->add_vertex(vertexs[vertex_id+1]);
        }
        assert(p->is_valid());
        object.addPolygon(p);
	}
    std::cout << "Cargados " << npoligonos << " polígonos" << std::endl;

    for(auto it = vertexs.begin(); it != vertexs.end(); it++) {
        delete *it;
    }
	fe.close(); //cerrar fichero 
}
