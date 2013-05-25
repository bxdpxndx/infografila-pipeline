#ifndef Point3D_hpp
#define Point3D_hpp


class Point3D {

private:

    float x, y, z;
    
public:

    Point3D(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in) {};
    
    friend std::ostream & operator<<(std::ostream &os, const Point3D & v)
    {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
    
	float Getx(){return x; std::cout<< x << " " << std::endl;}
	float Gety(){return y; std::cout<< y << " " << std::endl;}
	float Getz(){return z; std::cout<< z << " " << std::endl;}

};

#endif // Point3D_hpp

