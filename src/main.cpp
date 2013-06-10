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

    if( argc == 3 || argc == 5) {
        input_file = argv[1];
        output_file = argv[2];
    }

    else {
        std::cerr << "Missing arguments: Usage " << argv[0] << " <object file> <output filename> [width height]" << std::endl;
        return 0;
    }

    if (argc == 5) {
        std::stringstream(argv[3]) >> width;
        std::stringstream(argv[4]) >> height;
    }


    World w;

    Object3D * obj = Object3D::from_file(argv[1]);
    w.add_object(obj);

// TODO: Implementar Light y Camera :3
    Vector3D light = Vector3D(0, -1, 0).normalize();
    Camera camera;

    camera.position(2, -1, -1).lookAt(0.5,0.5,0.5).calcVectors();
    camera.setNearPlane(2);
    camera.setFarPlane(20);
    camera.setCameraAperture(1);

    w.set_light(light);
    w.set_camera(camera);

    Render r(width,height);
    r.setWorld(&w);
    r.draw();

    r.saveTGA(argv[2]);

}
