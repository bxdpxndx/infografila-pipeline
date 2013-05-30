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

    Matrix MatrixId() {
        for(int i=0; i < 4; i++) {
            setElement(1, i, i);
        }
        return *this;
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


    Matrix operator*(Matrix &m) {
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
    T operator*(T &v) {
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

    friend std::ostream & operator<<(std::ostream & os, const Matrix & m) {
        for (int i = 0; i < 4; i ++) {
            for (int j = 0; j < 4; j ++) {
                std::cout << m.getElement(i,j) << " ";
            }
            std::cout << std::endl;
        }
        return os;
    }
};
#endif //Matrix_


