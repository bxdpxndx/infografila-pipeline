#ifndef Matrix_hpp
#define Matrix_hpp

#include <iostream>
#include <vector>
#include <cmath>
#include "Vector3D.hpp"


class Matrix {

private:
    float mat[16];

public:

    float getElement(unsigned int x, unsigned int y) const {
        return mat[ y * 4 + x ];
    }

    void setElement(float f, unsigned int x, unsigned int y) {
        mat[ y * 4 + x ] = f;
    }

    Matrix() {
        for(int i=0; i < 16; i++) {
            mat[i] = 0;
        }
    }

    static Matrix screenTransform(float width, float height) {
        Matrix m = identity();

        m.setElement((width-1)/2.0, 0, 0);
        m.setElement((height-1)/2.0, 1, 1);
        m.setElement(width/2.0, 0, 3);
        m.setElement(height/2.0, 1, 3);

        return m;
    }
    static Matrix identity() {
        Matrix m;
        for(int i=0; i < 4; i++) {
            m.setElement(1, i, i);
        }
        return m;
    }

    void setTranslation(float Tx, float Ty, float Tz) {
        setElement(Tx, 0, 3);
        setElement(Ty, 1, 3);
        setElement(Tz, 2, 3);
    }

    void setScaling(float Sx, float Sy, float Sz) {
        setElement(Sx, 0, 0);
        setElement(Sy, 1, 1);
        setElement(Sz, 2, 2);
    }

    Matrix operator*(const Matrix &m) const {
        Matrix resultat;
        float element;
        for(int i=0; i<4; ++i) {
            for(int j=0; j<4; ++j) {
                element = 0;
                for(int k=0; k<4; ++k) {
                    element += this->getElement(i,k) * m.getElement(k,j);
                }
                resultat.setElement(element,i,j);
            }
        }
        return resultat;
    }

    // així permetem fer servir tant Vector3D com Vertex3D

    template <class T>
    T operator*(const T &v) const {
        T resultat;
        float element;
        for(int i=0; i<4; ++i) {
            element = 0;
            for(int j=0; j<4; ++j) {
                element += this->getElement(i,j) * v.get(j);
            }
            resultat.set(element,i);
        }
        return resultat;
    }

    friend std::ostream & operator<<(std::ostream & os, const Matrix & m);
};

std::ostream & operator<<(std::ostream & os, const Matrix & m) {
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            std::cout << m.getElement(i,j) << " ";
        }
        std::cout << std::endl;
    }
    return os;
}
#endif //Matrix_


