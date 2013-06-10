#include <iostream> // std::cout
#include <fstream> // std::ifstream
#include <vector>
#include <sstream>

#include <cassert>
#include "World.hpp"
#include "Render.hpp"
#include "Object3D.hpp"



int main(int argc, char *argv[])
{
    int width = 512;
    int height = 512;
    std::string input_file;
    std::string output_file;
    std::string cam_file;

    if( argc == 4 || argc == 6) {
        input_file = argv[1];
        cam_file = argv[2];
        output_file = argv[3];
    }

    else {
        std::cerr << "Missing arguments: Usage " << argv[0] << " <object file> <camera file > <output filename> [width height]" << std::endl;
        return 0;
    }

    if (argc == 6) {
        std::stringstream(argv[4]) >> width;
        std::stringstream(argv[5]) >> height;
    }


    World w;

    Object3D * obj = Object3D::from_file(input_file);
    w.add_object(obj);

// TODO: Implementar Light y Camera :3
    Vector3D light = Vector3D(-1, -1, -1).normalize();
    Camera camera = Camera::from_file(cam_file);

    w.set_light(light);
    w.set_camera(camera);

    Render r(width,height);
    r.setWorld(&w);
    r.draw();

    r.saveTGA(output_file);

}
