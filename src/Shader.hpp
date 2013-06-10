#ifndef Shader_hpp
#define Shader_hpp

#include "image.hpp"
#include "Polygon.hpp"
#include "Vector3D.hpp"

class Shader {
public:
    virtual ~Shader() {};
    virtual void draw_polygon( Image & im, const Polygon & p, const Vector3D & light) const = 0;
};

#endif
