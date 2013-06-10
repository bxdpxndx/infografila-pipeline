#ifndef Poly_borders_hpp
#define Poly_borders_hpp

#include "Polygon.hpp"
#include "Utils.hpp"

class border_point {
    public:
        int x; // pixel position
        border_point operator+(const border_point & other) {
            border_point retval;
            retval.x = x + other.x;
            return retval;
        }

        border_point operator*(float value) {
            border_point retval;
            retval.x = x * value;
            return retval;
        }
        bool operator<(const border_point & other) const{
            return x < other.x;
        }
};

class Poly_borders {
    private:
        std::vector<std::vector<int> > _borders;

    public: 
        Poly_borders(const Polygon & p) {
            
            int lowest = p.get_lowest_point();
            int highest = p.get_highest_point();
            int delta = highest-lowest;

            // build the borders structure
            _borders.resize(delta+1, std::vector<int>());

            for (Polygon::LineIterator it = p.lines_begin(); it != p.lines_end(); it++) {
                for (int i = (int) ((*it).start->y) + 1; i <= ((int) ((*it).end->y)); i++) {
                    int current;
                    float interp = reverse_interpolate(((int)(*it).start->y), ((int) (*it).end->y - 1),  i);
                    current = interpolate((*it).start->x, (*it).end->x, interp);
                    std::cout << "border point " << current << " " << i + lowest << std::endl;
                    _borders[i - lowest].push_back(current);
                }
            }
            for (unsigned i = 0; i < _borders.size(); i++) {
                std::sort(_borders[i].begin(), _borders[i].end());
            }

        }

        std::vector<int> operator[](unsigned i) {
            return _borders[i];
        }
        unsigned size() {
            return _borders.size();
        }
};



#endif
