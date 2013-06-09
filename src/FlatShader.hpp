#ifndef FlatShader_hpp
#define FlatShader_hpp

#include <vector>

#include "Polygon.hpp"
#include "image.hpp"
#include "Line.hpp"
#include "Vertex3D.hpp"
#include "Vector3D.hpp"

#include "Shader.hpp"

class FlatShader : public Shader{
    Image _image;
public:
    void draw_polygon( Image & im, const Polygon & p, const Vector3D & light) const {
        int lowest = p.get_lowest_point();
        int highest = p.get_highest_point();
        int delta = highest-lowest;
        std::vector<std::vector<int> > borders(delta+1, std::vector<int>());

        float shade = light.dot_product(p.getNormal());
		float Ir = 0.6*0.3 + 0.7*0.7*shade;
		float Ig = 0.6*0.6 + 0.7*0.5*shade;
		float Ib = 0.6*0.4 + 0.7*0.6*shade;
        Color color(Ir, Ig, Ib);
        // get the edges.
        for (Polygon::LineIterator it = p.lines_begin(); it != p.lines_end(); it++) {
            float steepness = (*it).getStepness();
            for (int i = (int) ((*it).start->y) + 1; i <= ((int) ((*it).end->y)); i++) {
                borders[i - lowest].push_back( (*it).start->x + (steepness * (i - (*it).start->y) - 1));
            }
        }

        // sort the edges and fill.
        for (unsigned i = 0; i < borders.size(); i++) {
            std::sort(borders[i].begin(), borders[i].end());
            for (unsigned j = 0; j < borders[i].size()/2; j++) {
                for(int k = borders[i][j]; k < borders[i][j+1]; k++) {
                    if(im.isInBounds(k, i + lowest)) {
                        im.setPixel(color, k , i + lowest);
                    }
                }
            }
        } 
    }
};

#endif
