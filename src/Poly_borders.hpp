#ifndef Poly_borders_hpp
#define Poly_borders_hpp

#include "Polygon.hpp"
#include "Utils.hpp"
#include "Vector3D.hpp"

class border_point {
public:
    int x; // pixel position
    float z; // depth
    Vector3D normal;
    bool operator<(const border_point & other) const {
        return x < other.x;
    }
};

class Poly_borders {
private:
    std::vector<std::vector<border_point> > _borders;

public:
    Poly_borders(const Polygon & p) {

        int lowest = p.get_lowest_point();
        int highest = p.get_highest_point();
        int delta = highest-lowest;

        // build the borders structure
        _borders.resize(delta+1, std::vector<border_point>());

        for (Polygon::LineIterator it = p.lines_begin(); it != p.lines_end(); it++) {
            for (int i = (int) ((*it).start->y) + 1; i <= ((int) ((*it).end->y)); i++) {
                float interp = reverse_interpolate((*it).start->y, (*it).end->y, i);
                border_point current;
                current.x = interpolate((*it).start->x, (*it).end->x, interp );
                current.z = interpolate((*it).start->z, (*it).end->z, interp );
                current.normal = interpolate((*it).start->_normal, (*it).end->_normal, interp );
                _borders[i - lowest].push_back(current);
            }
        }
        for (unsigned i = 0; i < _borders.size(); i++) {
            std::sort(_borders[i].begin(), _borders[i].end());
        }

    }

    std::vector<border_point> operator[](unsigned i) {
        return _borders[i];
    }
    unsigned size() {
        return _borders.size();
    }
};



#endif
