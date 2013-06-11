#ifndef PhongShader_hpp
#define PhongShader_hpp

#include <vector>

#include "Polygon.hpp"
#include "image.hpp"
#include "Line.hpp"
#include "Vertex3D.hpp"
#include "Vector3D.hpp"

#include "Shader.hpp"
#include "Poly_borders.hpp"
#include "Utils.hpp"

class PhongShader : public Shader {

public:
    void draw_polygon(Image & im, const Polygon & p, const Vector3D & light) const {

        int lowest = p.get_lowest_point();

        // get the edges.
        Poly_borders borders(p);

        for (unsigned i = 0; i < borders.size(); i++) { // foreach scanline
            for (unsigned j = 0; j < borders[i].size()/2; j++) { // foreach pair in scanline
                border_point start = borders[i][j];
                border_point end = borders[i][j+1];
                for(int k = start.x; k < end.x; k++) { // foreach pixel in the painted region
                    if(im.isInBounds(k, i+ lowest)) {

                        // get its normal and its color
                        float interp = reverse_interpolate(start.x, end.x, k);
                        float depth = interpolate(start.z, end.z, interp);
                        Vector3D normal = interpolate(start.normal, end.normal, interp);

                        float ambient = 0.2;
                        float diffuse = 0.8 * normal.dot_product(light);

                        float intensity = ambient + diffuse;
                        Color color(intensity);
                        im.setPixelWithDepthTest(color, k , i + lowest, depth - 10.0);
                    }
                }

            }
        }
    }
};

#endif
