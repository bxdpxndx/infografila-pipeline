#include <iostream> // std::cout
#include <fstream> // std::ifstream
#include <vector>
typedef std::vector <float> coordenadas;

int main()
{
	
	std::ifstream fe("data.dat", std::ifstream::in);//fe => "fichero entrada" abrir fichero para lectura
	
	//estrucura de lectura
	// nº vertices espacio nº poligonos (primera linea)
	//coordenadas a espacio b espacio c (segunda en adelante) 
	int vertices;
	int polignos;
	float a, b, c; //a b c son las coordenadas
	
	coordenadas xyz; //vector de coordenadas xyz
	
        if( !fe )
        { std::cout << "-!- error -!-" << std::endl; } 

	fe >> vertices >> polignos;
	
	std::cout << "vertices polignos" << std::endl;	
	std::cout << vertices << "        " << polignos<< std::endl;
	std::cout << "coodenada" << std::endl;

	std::cout << "a b c" << std::endl;

	while( !fe.eof() ) {
		fe >> a >> b >>c;
		std::cout << a <<" "<< b << " " << c << std::endl;	
		xyz.push_back(a);
		xyz.push_back(b);
		xyz.push_back(c);
	}

	std::cout << "comprobación vector de coordenadas" << std::endl;
	int aux=0; //solo sirve para mostrar linias de 3, solo decorativo
	for (std::vector<float>::iterator it=xyz.begin() ; it!=xyz.end() ; ++it) {
		std::cout << *it<<" ";
		if (aux<2) aux++;
		else{
			aux=0; 
			std::cout<< std::endl;
			}	
	}
	fe.close(); //cerrar fichero 
}
