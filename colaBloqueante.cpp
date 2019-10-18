#include "colaBloqueante.h"
#include <stdlib.h>
#include <queue>
#include <list>

ColaBloqueante::ColaBloqueante(size_t tamanio):
		terminado(false), tamanio(tamanio){
}

ColaBloqueante::~ColaBloqueante() {
}

void ColaBloqueante::push(std::list<std::bitset<8>> &lista){
	std::unique_lock<std::mutex> lock(this->m);
	this->pushUnsafe(lock, lista);
}

void ColaBloqueante::pushUnsafe(std::unique_lock<std::mutex> &lock,
		std::list<std::bitset<8>> &lista){
	while (this->tamanio == this->cola.size()){
		this->condVarEstaLlena.wait(lock);
	}
	this->cola.push(lista);
    this->condVarEstaVacia.notify_all();
}

int ColaBloqueante::pop(std::list<std::bitset<8>> &elemento){
	std::unique_lock<std::mutex> lock(this->m);
	while (this->cola.size() == 0 && !this->esta_cerrada()) {
		this->condVarEstaVacia.wait(lock);
	}
	elemento = this->cola.front();
	if (elemento.empty()){
		return 1;
	}
	this->cola.pop();
    this->condVarEstaLlena.notify_all();
	return 0;
}

void ColaBloqueante::cerrar(){
	std::unique_lock<std::mutex> lock(this->m);
	std::list<std::bitset<8>> listaVacia;
	this->pushUnsafe(lock, listaVacia);
	this->terminado = true;
}

bool ColaBloqueante::esta_vacia(){
	return this->cola.empty();
}

bool ColaBloqueante::esta_cerrada(){
	return this->terminado;
}
