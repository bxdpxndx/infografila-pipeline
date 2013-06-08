#ifndef World_hpp
#define World_hpp

#include "Object3D.hpp"
#include "Camera.hpp"

class World {

    std::vector <Object3D *> _objects;

    Vector3D _light;
    Camera _camera;
public:

    friend class Render;
    ~World() {
        for (std::vector<Object3D *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
            delete (*it);
        }
    }

    void add_object(Object3D * obj) {
        _objects.push_back(obj);
    }

    void set_light(Vector3D l) {
        _light = l;
    }

    void set_camera(Camera c) {
        _camera = c;
    }

    void transform(const Matrix & matrix) {
        std::cout << matrix << std::endl;
        for (std::vector<Object3D *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
            (*it)->apply_matrix_transform(matrix);
        }
    }

    void calculateAllNormals() {
        for (std::vector<Object3D *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
            (*it)->calculateAllNormals();
        }
    }

    Vector3D getCameraDirection() const {
        return _camera.getDirection();
    }
};

#endif // World_hpp
