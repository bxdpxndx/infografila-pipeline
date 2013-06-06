#ifndef Camera_hpp
#define Camera_hpp

#include <vector>

#include "Vertex3D.hpp"
#include "Vector3D.hpp"
#include "Matrix.hpp"

class Camera {

    Vertex3D _position;
	
    Vertex3D _lookAt;

	Vector3D _cameraDirection;
	Vector3D _cameraUp;
	Vector3D _cameraRight;


	//we set the vector 'Direction' using Direction = lookat - coords
	void setDirection() {
		_cameraDirection = _lookAt - _position;
        _cameraDirection.normalize();
	}

	//we set the vector 'Up' using Up = V - V*N/( normVector(V - V*N) )
	void setVectorUp() {
		_cameraUp = Vector3D(0, 1, 0);
        float scale = _cameraUp.dot_product(_cameraDirection);
        Vector3D projection = _cameraDirection * scale;
        _cameraUp = _cameraUp - projection;
        _cameraUp.normalize();     
	}

	//we set the vector 'Left' using Left = Direction x Up   )
    void setVectorRight() {
        _cameraRight = _cameraDirection.vectorial_product(_cameraUp);
        _cameraRight.normalize();
    }

public: 

    Camera() {};
	Camera(float x, float y, float z) : _position(x, y, z) {};
    Camera(Vertex3D v) : _position(v) {};

    Camera & position(float x, float y, float z) { 
        _position = Vertex3D(x,y,z); 
        return *this;
    }

    Camera & position(Vertex3D v) {
        _position = v;
        return *this;
    }

	Camera & lookAt(float x, float y, float z) {
        _lookAt = Vertex3D(x,y,z);
        return *this;
    }

    Camera & lookAt(Vertex3D v) {
        _lookAt = v; 
        return *this;
    }
    
    Camera & calcVectors() {
        setDirection();
        setVectorUp();
        setVectorRight();
        return *this;
    }

    Matrix getCameraTransform() const{
        Matrix rotation = Matrix::identity();
        for(int i = 0; i < 3; i++) {
            rotation.setElement(_cameraRight.get(i), 0, i);
            rotation.setElement(_cameraUp.get(i), 1, i);
            rotation.setElement(_cameraDirection.get(i), 2, i);
        }

        Matrix translation = Matrix::identity();
        for (int i = 0; i < 3; i++) {
            translation.setElement(-_position.get(i), i, 3);
        }
        return rotation * translation;
    }

    friend std::ostream & operator<<(std::ostream &os, const Camera & c);
    
};

std::ostream & operator<<(std::ostream &os, const Camera & c)
{
    os << "Camera at " << c._position << " that looks to " << c._lookAt << std::endl;
    os << "transform is: " << std::endl;
    os << c.getCameraTransform() << std::endl;
    return os;
}


#endif //  Camera_hpp

