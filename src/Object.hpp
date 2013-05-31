#ifndef Object_hpp
#define Object_hpp

#include <vector>

#include "Polygon.hpp"


class Object {

private:
    std::vector<Polygon*> _polygons;

public:
    void addPolygon (Polygon * p) {
        _polygons.push_back(p);
    }

    ~Object() {
        for(std::vector<Polygon*>::iterator it = _polygons.begin(); it != _polygons.end(); it++) {
            delete *it;
        }
    }


    void recorrer() const {
        std::cout<<" _polygons[j] "<<std::endl;
        for(unsigned j=0; j<_polygons.size(); ++j) {
            std::cout<< *_polygons[j] <<std::endl;
        }
    }
};

#endif // Object_hpp
