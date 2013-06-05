#include <iostream> // std::cout
#include <fstream> // std::ifstream
#include <vector>

#include <cassert>
#include "World.hpp"
#include "Render.hpp"
#include "Object3D.hpp"



int main(int argc, char *argv[])
{
    if( argc != 3 ) {
        std::cerr << "Missing arguments: Usage " << argv[0] << " <object file> <output filename>" << std::endl;
        return 0;
    }

    int width = 480;
    int height = 320;

    World w;

    Object3D * obj = Object3D::from_file(argv[1]);
    w.add_object(obj);

// TODO: Implementar Light y Camera :3
    Light light;
    Camera camera;

    w.set_light(light);
    w.set_camera(camera);

    Render r(width,height);
    r.draw(w);

    r.saveTGA(argv[2]);

}
