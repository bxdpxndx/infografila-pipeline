#ifndef Camera_hpp
#define Camera_hpp

#include <vector>

class Camera {

public: 

	union {
        struct {
            float x, y, z, w;
        };
        float coords[4];
    };
	
	union {
        struct {
            float atx, aty, atz, atw;
        };
        float lookat[4];
    };

	vector<float> CameraDirection(4);
	vector<float> CameraUp(4);
	vector<float> CameraRight(4);
		
	Camera() : x(0), y(0), z(0), w(1) {};

	Camera(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in), w(1) {};

	CameraLookAt(float x_in, float y_in, float z_in) {
		atx = x_in;
		aty = y_in;
		atz = z_in;
		atw = 1;
	}

	//we set the vector 'Direction' using Direction = lookat - coords
	void setDirectionCamera() {
		CameraDirection = {atx-x,aty-y,atz-z,0};
	}

	//we set the vector 'Up' using Up = V - V*N/( normVector(V - V*N) )
	void setVectorUpCamera() {
		vector<float> other(4) = {0,1,0,0};
		vector<float> aux(4);
		aux = other - (other*CameraDirection);
		CameraUp = aux / normVector(aux);
	}

	//we set the vector 'Left' using Left = Direction x Up   )
	void setVectorRight() {
		CameraLeft = crossProduct(CameraDirection, CameraUp);
	}

    float getPositionCamera(int i) const {
        return coords[i];
    }

    void setPositionCamera(float value, int i) {
        coords[i] = value;
    }

	float getElementVectorUp(int i) {
		return CameraUp(i);
	}

	float getElementVectorLeft(int i) {
		return CameraLeft(i);
	}
	
	float getElementVectorDirection(int i) {
		return CameraDirection(i);
	}

};

std::ostream & operator<<(std::ostream &os, const Camera & c)
{
    os << "(" << c.x << ", " << c.y << ", " << c.z << ")";
    return os;
}
};

#endif //  Camera_hpp
