#include <iostream> // std::cout
#include <fstream> // std::ifstream
#include <vector>
#include <assert.h>
#include "Vertex.hpp"
#include "Polygon.hpp"

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
	
	std::cout << "vertices poligonos" << std::endl;	
	std::cout << nvertices << "        " << npoligonos<< std::endl;
	std::cout << "coodenada" << std::endl;


    std::vector<Vertex*> vertexs;
    float x, y, z;
	for (int i = 0; i < nvertices; i++) {
        fe >> x >> y >> z;
        vertexs.push_back(new Vertex(x,y,z));
	}

    std::vector<Polygon*> polygons;
    int nsides;
	for (int i = 0; i < npoligonos; i++) {
        fe >> nsides;
        Polygon *p = new Polygon(nsides);
        int vertex_id;
        for (int j = 0; j < nsides; j++) {
            fe >> vertex_id;
            p->add_vertex(vertexs[vertex_id]);
        }
        assert(p->is_valid());
        polygons.push_back(p);
	}

	std::cout << "vector de polígonos: " << polygons.size() << " polígonos." << std::endl;
	for (std::vector<Polygon*>::iterator it = polygons.begin(); it!=polygons.end(); ++it) {
		std::cout << **it << std::endl;
	}
	fe.close(); //cerrar fichero 
}
