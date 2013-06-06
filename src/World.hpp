#ifndef World_hpp
#define World_hpp

#include "Object3D.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class World {

    std::vector <Object3D *> _objects;

    Light _lights;
    Camera _camera;
public:
    ~World() {
        for (auto it = _objects.begin(); it != _objects.end(); it++) {
            delete (*it);
        }
    }

    void add_object(Object3D * obj) {
        _objects.push_back(obj);
    }

    void set_light(Light l) {
        _lights = l;
    }

    void set_camera(Camera c) {
        _camera = c;
    }

    void apply_camera_transform() {
        transform(_camera.getCameraTransform());
    }

    void transform(const Matrix & matrix) {
        for (auto it = _objects.begin(); it != _objects.end(); it++) {
            (*it)->apply_matrix_transform(matrix);
        }
    }

    // expose the objects
    std::vector<Object3D *>::const_iterator objects_begin() {
        return _objects.begin();
    }

    std::vector<Object3D *>::const_iterator objects_end() {
        return _objects.end();
    }
};

#endif // World_hpp
