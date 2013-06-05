#ifndef Camera_hpp
#define Camera_hpp

#include <vector>

class Camera {

    Vertex3D _position;
	
    Vertex3D _lookAt;

	Vector3D _cameraDirection;
	Vector3D _cameraUp;
	Vector3D _cameraRight;


	//we set the vector 'Direction' using Direction = lookat - coords
	void setDirection() {
		_cameraDirection = _lookAt - _position;
	}

	//we set the vector 'Up' using Up = V - V*N/( normVector(V - V*N) )
	void setVectorUp() {
        assert(_cameraDirection.x != 0);
        assert(_cameraDirection.z != 0);
		Vector3D _cameraUp(0, 1, 0);
        _cameraUp = _cameraUp - _cameraDirection * (_cameraUp.dot_product(_cameraDirection));
	}

	//we set the vector 'Left' using Left = Direction x Up   )
    void setVectorRight() {
        _cameraRight = _cameraDirection.vectorial_product(_cameraUp);
    }

public: 

    Camera() {};
	Camera(float x, float y, float z) : _position(x, y, z) {};
    Camera(Vertex3D v) : _position(v) {};

    Camera & position(float x, float y, float z) { 
        _lookAt = Vertex3D(x,y,z); 
        return *this;
    }

    Camera & position(Vertex3D v) {
        _lookAt = v;
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
    
    void calcVectors() {
        setDirection();
        setVectorUp();
        setVectorRight();
    }

    friend std::ostream & operator<<(std::ostream &os, const Camera & c);
    
};

std::ostream & operator<<(std::ostream &os, const Camera & c)
{
    os << "Camera at " << c._position << " that looks to " << c._lookAt << std::endl;
    return os;
}


#endif //  Camera_hpp

