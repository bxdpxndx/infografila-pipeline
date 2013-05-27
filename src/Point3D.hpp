#ifndef Point3D_hpp
#define Point3D_hpp


class Point3D {

public:
    union { 
        struct {float x, y, z, w; };
        float coords[4];
    }
        
;

    Point3D(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in), w(1) {};
    Point3D() : x(0), y(0), z(0), w(0) {};
    
    friend std::ostream & operator<<(std::ostream &os, const Point3D & v)
    {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
    
    float get(int i) {
        return coords[i];
    }

    void set(float value, int i) {
        coords[i] = value;
    }
    
    void mostrar(){
			std::cout << "(" << x << ", " << y << ", " << z << ")";
	}

};

#endif // Point3D_hpp

