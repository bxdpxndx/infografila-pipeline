#ifndef PhongShader_hpp
#define PhongShader_hpp

#include <vector>

#include "Polygon.hpp"
#include "image.hpp"
#include "Line.hpp"
#include "Vertex3D.hpp"

#include "Shader.hpp"

class PhongShader : public Shader {

public:
    void draw_polygon( Image & im, const Polygon & p, const Vector3D & light) const {
    }
};

#endif
