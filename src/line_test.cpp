#include <iostream> // std::cout
#include <vector>

#include <assert.h>

#include "Vertex3D.hpp"
#include "Line.hpp"
#include "image.hpp"
#include "Render.hpp"


int main(void) {

    Render render(480,320); // funciona como Image más o menos,
    // pero se le puedne añadir lineas y cosas.
    for(float i = -1; i < 1; i+=0.1) {
        Vertex3D start(i, 1, 0);
        Vertex3D end(-1, i, 0);
        Line l(start, end);
        render.draw_line(l);
    }
    render.saveTGA("line_test.tga");

    return 0;
}

