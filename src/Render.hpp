#include <assert.h>
#include "image.hpp"
#include "Line.hpp"
#include "Matrix.hpp"

class Render {
// Takes points in 3d screen space and draws them to an image.
// 3d screen space is: x and y in the range -1, 1.
// (-1, -1) is the top left point.
// z in the range 0, 1. 0 is nearest.

// TODO (I think this order is good):

// Better line-drawing algorithm.
// drawing polygons (wireframe).
// drawing polygons(filled).
// shading.
// z-buffer rendering.

private:
    int _width, _height; // in pixels
    Image _image;
    Matrix _transform_matrix;

public:
    Render(int width, int height) : _width(width), _height(height), _image(width, height) {
        _transform_matrix.setTranslation(width/2.0, height/2.0, 0);
        _transform_matrix.setScaling(width/2.0, height/2.0, 1);
    };

    void draw_line(Line &l) {
        l.transform(_transform_matrix);
        int x0 = l.start.x;
        int y0 = l.start.y;
        int x1 = l.end.x;
        int y1 = l.end.y;
        int dx = abs(x1-x0);
        int sx = x0<x1 ? 1 : -1;
        int dy = abs(y1-y0);
        int sy = y0<y1 ? 1 : -1; 
        int err = (dx>dy ? dx : -dy)/2, e2;

        Color white(1,1,1);
        for(;;){
            _image.setPixel(white, x0, y0);
            if (x0==x1 && y0==y1) break;
            e2 = err;
            if (e2 >-dx) { err -= dy; x0 += sx; }
            if (e2 < dy) { err += dx; y0 += sy; }
        }
    }

    void saveTGA(const char *filename) {
        _image.saveTGA(filename);
    }
};

