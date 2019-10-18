#include "manejadorDeEntrada.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

ManejadorDeEntrada::ManejadorDeEntrada(std::mutex &mutex, std::istream &infile)
			: m(mutex), entrada(infile){
}

ManejadorDeEntrada::~ManejadorDeEntrada() {
}

int ManejadorDeEntrada::leer(int posicion, char* bloque,
		int tamanio){
	this->m.lock();
	if (!this->entrada.good()){
		this->entrada.clear();
	}
	this->entrada.seekg(posicion, this->entrada.beg);
	this->entrada.read(bloque, tamanio);
	int leidos = (this->entrada.gcount()) / 4;
	this->m.unlock();
	return leidos;
}
