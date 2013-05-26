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
    Matrix transform_matrix;

    void draw_horizontal_line(Line & l) {

        Color white(1,1,1);
        // we only draw left to right.
        if(l.start.x > l.end.x) {
            l.flip();
        }
        int deltax = l.end.x - l.start.x;
        int deltay = l.end.y - l.start.y;

        float slope = (float) deltay/(float) deltax;

        for (float i = 0; i < deltax; i++) {
            _image.setPixel(white, i + l.start.x, l.start.y + (i*slope));
        }
    }

    void draw_vertical_line(Line & l) {
        Color white(1,1,1);
        // we only draw downwards.
        if(l.start.y > l.end.y) {
            l.flip();
        }
        int deltax = l.end.x - l.start.x;
        int deltay = l.end.y - l.start.y;

        float slope = (float) deltax/(float) deltay;

        for (int i = 0; i < deltay; i++) {
            _image.setPixel(white, l.start.x + (i*slope), l.start.y + i);
        }
    }

public:
    Render(int width, int height) : _width(width), _height(height), _image(width, height) {
        transform_matrix.setTranslation(width/2.0, height/2.0, 0);
        transform_matrix.setScaling(width/2.0, height/2.0, 1);
    };

    void draw_line(Line l) {

        l.transform(transform_matrix);

        if(l.is_vertical()) {
            draw_vertical_line(l);
        } else {
            draw_horizontal_line(l);
        }
    }

    void saveTGA(const char *filename) {
        _image.saveTGA(filename);
    }
};

