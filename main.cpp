#include <stdio.h>
#include <stdlib.h>
#include "manejadorDeHilos.h"

int main(int argc, char* argv[]) {
	ManejadorDeHilos manejador;
	manejador.comprimir(atoi(argv[1]), atoi(argv[2]),
			atoi(argv[3]), argv[4], argv[5]);
}
