#include "compresor.h"
#include <math.h>
#include <bitset>
#include <list>

/**************************************
 * 				AUXILIARES
 **************************************/

static int obtener_minimo(uint32_t* bloque, int tamanio){
	uint32_t minimo = bloque[0];
	for (int i = 0; i < tamanio; i++){
		if (minimo > bloque[i]){
			minimo = bloque[i];
		}
	}
	return minimo;
}

static int obtener_maximo(uint32_t* bloque, int tamanio){
	uint32_t maximo = 0;
	for (int i = 0; i < tamanio; i++){
		if (maximo < bloque[i]){
			maximo = bloque[i];
		}
	}
	return maximo;
}

static void restar_numero(int numero, uint32_t* bloque, int tamanio){
	for (int i = 0; i < tamanio; i++){
		bloque[i] -= numero;
	}
}

static int obtener_espacio_en_bits_minimo(uint32_t* bloque, int tamanio){
	int maximo = obtener_maximo(bloque, tamanio);
	int cantidadDeBits = 0;
	int mayorNumeroPosible = 0;
	while (mayorNumeroPosible < maximo){
		mayorNumeroPosible += pow(2, cantidadDeBits);
		++cantidadDeBits;
	}
	return cantidadDeBits;
}

static void agregar_minimo_a_comprimido(int minimo,
		std::list<std::bitset<8>> &comprimido){
	std::bitset<32> minimoBits(minimo);
	std::bitset<8> subMinimo;
	for (int i = 0; i < 32; ++i){
		if (i != 0 && (i)%8 == 0){
			comprimido.push_front(subMinimo);
			subMinimo.set(0);
		}
		subMinimo[i%8] = minimoBits[i];
	}
	comprimido.push_front(subMinimo);
}

static void reducir_numero(int numero, int espacio, int* reducido){
	for (int j = 0; j < espacio; ++j){
		reducido[espacio-1-j] = (numero % 2);
		numero = numero / 2;
	}
}

static void agregar_reducidos_a_la_lista(int tamanio,
		int espacio, std::list<std::bitset<8>> &comprimido,
		int *numeros){
	std::bitset<8> reducido;
	bool esElPrimero = true;
	for (int j = 0; j < tamanio * espacio; ++j){
		if (!esElPrimero && ((j % 8) == 0)){
			comprimido.push_back(reducido);
			reducido.reset();
		} else if (esElPrimero){
			esElPrimero = false;
		}
		reducido[7-(j%8)] = numeros[j];
	}
	comprimido.push_back(reducido);
}

static void reducir_a_n_bits(uint32_t* bloque, int tamanio,
		int espacio, std::list<std::bitset<8>> &comprimido){
	int *numeros = (int*) calloc(espacio, sizeof(int) * tamanio);
	for (int i = 0; i < tamanio; ++i){
		reducir_numero(bloque[i], espacio, &numeros[i*espacio]);
	}
	agregar_reducidos_a_la_lista(tamanio, espacio, comprimido,
								numeros);
	free(numeros);
}


/**************************************
 * 				PRIMITIVAS
 **************************************/

Compresor::Compresor() {
}

Compresor::~Compresor() {
}

void Compresor::comprimir(uint32_t* bloque, int tamanio,
		std::list<std::bitset<8>> &comprimido){
	int minimo = obtener_minimo(bloque, tamanio);
	agregar_minimo_a_comprimido(minimo, comprimido);
	restar_numero(minimo, bloque, tamanio);
	int espacio = obtener_espacio_en_bits_minimo(bloque, tamanio);
	comprimido.push_back(espacio);
	if (espacio != 0){
		reducir_a_n_bits(bloque, tamanio, espacio, comprimido);
	}
}
