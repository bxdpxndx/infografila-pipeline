#ifndef FlatShader_hpp
#define FlatShader_hpp

#include <vector>

#include "Polygon.hpp"
#include "image.hpp"
#include "Line.hpp"
#include "Vertex3D.hpp"
#include "Vector3D.hpp"

#include "Shader.hpp"
#include "Poly_borders.hpp"
#include "Utils.hpp"

class FlatShader : public Shader{
    Image _image;
public:
    void draw_polygon( Image & im, const Polygon & p, const Vector3D & light) const {
        // build the borders structure
        Poly_borders borders(p);

        float shade = light.dot_product(p.getNormal());
		float Ir = 0.6*0.3 + 0.7*0.7*shade;
		float Ig = 0.6*0.6 + 0.7*0.5*shade;
		float Ib = 0.6*0.4 + 0.7*0.6*shade;
        Color color(Ir, Ig, Ib);

        // fill.
        int lowest = p.get_lowest_point();

        for (unsigned i = 0; i < borders.size(); i++) {
            for (unsigned j = 0; j < borders[i].size()/2; j++) {
                for(int k = borders[i][j]; k < borders[i][j+1]; k++) {
                    //float interior_point_value = reverse_interpolate( borders[i][j].x, borders[i][j+1].x, k);
                    //float depth = interpolate(borders[i][j].z, borders[i][j+1].z, interior_point_value);
                    // do something with the normal here
                    if(im.isInBounds(k, i + lowest)) {
                        im.setPixel(color, k , i + lowest);
                    }
                }
            }
        } 
    }
};

#endif
