#include <iostream> // std::cout
#include <vector>

#include <cassert>
#include <cstdlib>
#include <ctime>

#include "Vertex3D.hpp"
#include "Line.hpp"
#include "Polygon.hpp"
#include "image.hpp"
#include "Render.hpp"
#include "Matrix.hpp"


int main(void) {

    int width = 1024;
    int height = 1024;
    int nvertexs = 10;
    
    srand(time(0));

    Render render(width, height); // funciona como Image más o menos,
    // pero se le pueden añadir lineas y cosas.

    const Matrix & transform = render.getTransformMatrix();

    std::vector<Vertex3D*> vertexs;


    // ATENCIÓN: ESTA PARTE ES MUY MUY MUY MUY MUY FEA. NO COJAIS
    // INSPIRACIÓN AQUÍ.
    Polygon p(nvertexs);
    for(int i = 0; i < nvertexs; i++) {
        float k = i / (float) nvertexs;
        float random = 2*((float) rand() / (float) RAND_MAX) - 1;

        Vertex3D * vertex = new Vertex3D(k, random, 0);
        *vertex = transform * (*vertex);
        vertexs.push_back(vertex);
        p.add_vertex(vertex);
    }

    // ESTA ES LA DEMO CON LA QUE OS DEBERÍAIS QUEDAR.
    for (Polygon::LineIterator it = p.lines_begin(); it != p.lines_end(); it++) {
        std::cout << "line " << *it << std::endl;
        render.draw_line(*it);
    }
    render.saveTGA("poly_test.tga");

    return 0;
}

