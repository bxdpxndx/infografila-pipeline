#ifndef Matrix_hpp
#define Matrix_hpp

#include <iostream>
#include <vector>
#include <cmath>
#include "Vector3D.hpp"



template <typename T>

class Matrix {

private:
	float mat[16];

public:
	
	float getElement(unsigned int x, unsigned int y) const {
        	return mat[ y * 4 + x ];
    	}

        void setElement(const float& f, unsigned int x, unsigned int y) {
        	mat[ y * 4 + x ] = f;
    	}

	Matrix() {
		for(int i=0; i < 16; i++){
			mat[i] = 0; 	
		}
	}

	Matrix MatrixId() {
		for(int i=0; i < 4: i++){
			setElement(1, i, i);
		}
		return *this;
	}

	Matrix MatrixTrans(const float& Tx, const float& Ty, const float& Tz) {
		setElement(-Tx, 3, 0);
		setElement(-Ty, 3, 1);
		setElement(-Tz, 3, 2);
        return *this;
	}

    Matrix MatrixScale(const float& Sx, const float& Ty, const float& Tz) {
		setElement(Sx, 0, 0);
		setElement(Sy, 1, 1);
		setElement(Sz, 2, 2);        
    }



	Matrix operator*(Matrix &m) {
		Matrix resultat;
		float element;		
		for(int i=0; i<4; ++i){
			for(int j=0; j<4; ++j){
				element = 0;
				for(int k=0; k<4; ++k){
					element += this->getElement(i,k) * m.getElement(k,j);
				}
				res.setElement(element,i,j);
			}
		}
		return resultat;
	}

    // així permetem fer servir tant Point3D, com Vector3D i Vertex3D
    
    template <class T>
	T operator*(T &v) {
		T resultat;
		float element;		
		for(int i=0; i<4; ++i){
			element = 0;
			for(int j=0; j<4; ++j){
				element += this->getElement(i,j) * v.getElement(j);
			}
			resultat.setElement(element,i);
		}
		return resultat;
	}

	MatrixRotX(){}

	MatrixRotY(){}
	
	MatrixRotZ(){}

	



/*
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


