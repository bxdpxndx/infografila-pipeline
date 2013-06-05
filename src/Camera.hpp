#ifndef Camera_hpp
#define Camera_hpp

#include <vector>

class Camera {

public: 

	
	Vertex3D *_centerCamera;
	Vertex3D *_lookAt;

	Vector3D _cameraDirection;
	Vector3D _cameraUp;
	Vector3D _cameraLeft;
		
	Camera() {
		_centerCamera = new Vertex3D();
	};
	
	Camera(float x_in, float y_in, float z_in) {
		_centerCamera = new Vertex3D(x_in, y_in, z_in);
	};

	CameraLookAt(float x_in, float y_in, float z_in) {
		_lookAt = new Vertex3D(x_in, y_in, z_in);
	}

	//we set the vector 'Direction' using Direction = lookAt - centerCamera
	void setDirectionCamera() {
		_cameraDirection = _lookAt - _centerCamera;
	}

	//we set the vector 'Up' using Up = V - V*N/( normVector(V - V*N) )
	void setVectorUpCamera() {
		Vector3D other(0,1,0,0);
		Vector3D aux();
		aux = other - (other*_cameraDirection);
		_cameraUp = aux / normVector(aux);
	}

	//we set the vector 'Left' using Left = Direction x Up   )
	void setVectorRight() {
		_cameraLeft = crossProduct(_cameraDirection, _cameraUp);
	}

    float getPositionCamera(int i) const {
        return _centerCamera.get(i);
    }

    void setPositionCamera(float value, int i) {
        _centerCamera.set(value, i);
    }

	float getElementVectorUp(int i) {
		return _cameraUp.get(i);
	}

	float getElementVectorLeft(int i) {
		return _cameraLeft.get(i);
	}
	
	float getElementVectorDirection(int i) {
		return _cameraDirection.get(i);
	}

};

std::ostream & operator<<(std::ostream &os, const Camera & c)
{
    os << "(" << c.x << ", " << c.y << ", " << c.z << ")";
    return os;
}
};

#endif //  Camera_hpp
