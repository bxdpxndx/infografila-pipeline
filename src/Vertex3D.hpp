#ifndef Vertex3D_hpp
#define Vertex3D_hpp
#include "Point3D.hpp"

class Vertex3D : public Point3D {
	
    public:
        Vertex3D(float x_in, float y_in, float z_in) : Point3D(x_in, y_in, z_in) {}
           
		float Getx(){
				 Point3D *p;
				 return p->Getx();
				 }
				 
		float Gety(){
				 Point3D *p;
				 return p->Gety();
				 }
				 
		float Getz(){
				 Point3D *p;
				 return p->Getz();
				 }
};

#endif // Vertex3D_hpp
