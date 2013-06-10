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

class FlatShader : public Shader {

public:
    void draw_polygon(Image & im, const Polygon & p, const Vector3D & light) const {

        Poly_borders borders(p);
        float value = 0.2 + p.getNormal().dot_product(light);
        Color color(value);

        int lowest = p.get_lowest_point();
        // get the edges.
        // sort the edges and fill.
        for (unsigned i = 0; i < borders.size(); i++) { // foreach scanline
            for (unsigned j = 0; j < borders[i].size()/2; j++) { // foreach pair in scanline
                border_point start = borders[i][j];
                border_point end = borders[i][j+1];
                for(int k = start.x; k < end.x; k++) { // foreach pixel in the painted region
                    if(im.isInBounds(k, i+ lowest)) {
                        float interp = reverse_interpolate(start.x, end.x, k);
                        float depth = interpolate(start.z, end.z, interp);
                        im.setPixelWithDepthTest(color, k , i + lowest, depth - 2.0);
                    }
                }

            }
        }
    }
};

#endif
