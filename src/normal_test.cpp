#include <iostream> // std::cout
#include <fstream> // std::ifstream
#include <vector>
#include <sstream>

#include <cassert>
#include "Vertex3D.hpp"
#include "Polygon.hpp"


int main(int argc, char *argv[])
{
    Polygon p(3);
    Vertex3D v1(0, 0, 0);
    Vertex3D v2(1, 0, 0);
    Vertex3D v3(0, 1, 0);
    p.add_vertex(&v1);
    p.add_vertex(&v2);
    p.add_vertex(&v3);
    p.NormalV();
    std::cout << p << std::endl;

}
