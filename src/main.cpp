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
	int poligonos;
	float a, b, c, d, e; //a b c son las coordenadas
	
	coordenadas xyz; //vector de vertices xyz
	coordenadas pols; //vector de coordenadas xyz

        if( !fe ) { std::cout << "-!- error -!-" << std::endl; } 

	fe >> vertices >> poligonos;
	
	std::cout << "vertices polignos" << std::endl;	
	std::cout << vertices << "        " << poligonos<< std::endl;
	std::cout << "coodenada" << std::endl;
	std::cout << "fichero original " << std::endl;

int bux=vertices, cux=poligonos;

	while( !fe.eof() ) 
	{
		if (bux>0){		
			fe >> a >> b >>c;
			xyz.push_back(a);
			xyz.push_back(b);
			xyz.push_back(c);
			bux--;
		}
		if (cux>0 && bux ==0 ){//si bux=vertices es 0 ya ha acabado de leer los vertices.	
		//fe >> a >> b >>c>>d;
		fe>>a;
	
			if ( a == 4)
			{
				fe >> b >> c >> d >> e;
				pols.push_back(a);
				pols.push_back(b);
				pols.push_back(c);
				pols.push_back(d);
				pols.push_back(e);
				std::cout<<a<<b<<c<<d<<e<<std::endl;
			}
			if (a == 3)	
			{
				fe >> b >> c >> d;
				pols.push_back(a);
				pols.push_back(b);
				pols.push_back(c);
				pols.push_back(d);				std::cout<<a<<b<<c<<d<<std::endl;
			}
		}
	}

	std::cout << "comprobación vector de vertices" << std::endl;

	int aux=0; //solo sirve para mostrar linias de 3, solo decorativo

	for (std::vector<float>::iterator it=xyz.begin() ; it!=xyz.end() ; ++it) {
		std::cout << *it<<" ";
		if (aux<2) aux++;
		else{
			aux=0; 
			std::cout<< std::endl;
			}	
	}
	std::cout << "comprobación vector de poligonos" << std::endl;

	aux=0;
	for (std::vector<float>::iterator it=pols.begin() ; it!=pols.end() ; ++it) {
		std::cout << *it<<" ";
		if (aux==0){ aux=*it+1; }
		if(aux>0) { aux--; }
		if (aux==0){ aux==0;	std::cout << std::endl; }	
			
	}
	fe.close(); //cerrar fichero 
}
