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

    // així permetem fer servir tant Point3D, com Vector3D i Vertex3D

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
    /*

    	MatrixRotX(){}

    	MatrixRotY(){}

    	MatrixRotZ(){}





    	void setMatrix() {
    		std::cout << "Enter elements of the Matrix" << std::endl;
    		p = new T*[rows];
    		for(int i=0; i < rows; i++){
    			p[i] = new T[columns];
    			for(int j=0; j < columns; j++){
    				std::cin >> p[i][j];
    			}
    		}
    		std::cout << "Matrix completed" << std::endl;
    	}

    	void writeMatrix() {
    		std::cout << "Writting Matrix..." << std::endl;
    		for(int i=0; i < rows; i++){
    			for(int j=0; j < columns; j++){
    				std::cout <<  p[i][j] << " ";
    			}
    			std::cout << std::endl;
    		}
    		std::cout << "Matrix completed" << std::endl;
    	}


    	Matrix& operator=( const Matrix & matrix){
    		rows = matrix.rows;
    		columns = matrix.columns;
    		p = matrix.p;
    		return *this;
    	}



    	Matrix operator*(const T & num) {
    		Matrix res(this->rows);
    		for(int i=0; i<rows; ++i){
    			for(int j=0; j<columns; ++j){
    				res.p[i][j] = this->p[i][j]*num;
    			}
    		}
    		return res;
    	}

    };*/

};
#endif //Matrix_


