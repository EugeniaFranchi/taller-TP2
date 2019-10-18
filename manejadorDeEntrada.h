#ifndef MANEJADORDEENTRADA_H_
#define MANEJADORDEENTRADA_H_
#include <iostream>
#include <mutex>

class ManejadorDeEntrada {
private:
	std::mutex &m;
	std::istream &entrada;
public:
	ManejadorDeEntrada(std::mutex &mutex, std::istream &infile);
	virtual ~ManejadorDeEntrada();
	int leer(int posicion, char* bloque, int tamanio);
};

#endif
