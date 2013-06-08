#ifndef Render_hpp
#define Render_hpp
#include <cassert>

#include "image.hpp"
#include "Line.hpp"
#include "Polygon.hpp"
#include "Object3D.hpp"
#include "World.hpp"
#include "Matrix.hpp"

class Render {
// Takes points in 3d screen space and draws them to an image.
// 3d screen space is: x and y in the range -1, 1.
// (-1, -1) is the top left point.
// z in the range 0, 1. 0 is nearest.

// TODO (I think this order is good):

// Better line-drawing algorithm. DONE
// drawing polygons (wireframe). DONE
// drawing polygons(filled).
// shading.
// z-buffer rendering.

private:
    int _width, _height; // in pixels
    Image _image;
    World *_world;
    // wireframe drawing functions
    void draw_line(const Line & l) {
        // sólo usado para dibujar wireframes. algoritmo de bresenham
        // http://en.wikipedia.org/wiki/Bresenham's_line_algorithm
        // tomado prestado de
        // http://rosettacode.org/wiki/Bitmap/Bresenham's_line_algorithm#C
        // sería necesario limpiar un poco el código.
        int x0 = l.start->x;
        int y0 = l.start->y;
        int x1 = l.end->x;
        int y1 = l.end->y;
        int dx = abs(x1-x0);
        int sx = x0<x1 ? 1 : -1;
        int dy = abs(y1-y0);
        int sy = y0<y1 ? 1 : -1;
        int err = (dx>dy ? dx : -dy)/2;
        int e2;

        Color white(1, 1, 1);
        for(;;) {
            //std::cout << "  setting pixel " << x0 << " " << y0 << std::endl;
            if ( x0 < 0 || x0 >= _width || y0 < 0 || y0 >= _height ) {
                ;
            }
            else {
                _image.setPixel(white, x0, y0);
            }
            if (x0==x1 && y0==y1) break;
            e2 = err;
            if (e2 >-dx) {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dy) {
                err += dx;
                y0 += sy;
            }
        }

    }
    void draw_polygon_wireframe(const Polygon & p) {
        for (Polygon::LineIterator it = p.lines_begin(); it != p.lines_end(); it++) {
            draw_line(*it);
        }
    }

    void draw_polygon(const Polygon & p) {
        int lowest = p.get_lowest_point();
        int highest = p.get_highest_point();
        int delta = highest-lowest;
        std::vector<std::vector<int> > borders(delta+1, std::vector<int>());
        Color color(1, 1, 1);
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
                    _image.setPixel(color, k , i + lowest);
                }
            }
        }  
    }

    void draw_object(const Object3D & o) {
        for (std::vector<Polygon>::const_iterator it = o._polygons.begin(); it != o._polygons.end(); it ++) {

            // Backface culling!
            if ( it->getNormal().dot_product(_world->getCameraDirection()) < 0) {
                draw_polygon(*it);
            }
        }
    }



public:
    Render(int width, int height) : _width(width), _height(height), _image(width, height) {
    };

    void draw () {
        // TODO : Juntar todas las matrices y multiplicar una sola vez.
        // será al menos 3 veces más rápido!
        _world->apply_camera_transform();
        _world->apply_projection_transform();
        _world->transform(Matrix::screenTransform(_width, _height));
        for (std::vector <Object3D *>::const_iterator it = _world->_objects.begin(); it != _world->_objects.end(); it++) {
            draw_object(**it);
        }
    }

    void setWorld(World * w) {
        _world = w;
    }

    void saveTGA(char * filename) {
        _image.saveTGA(filename);
    }
};

#endif // Render_hpp
