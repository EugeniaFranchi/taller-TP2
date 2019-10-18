#ifndef COMPRESOR_H_
#define COMPRESOR_H_
#include <list>
#include <bitset>

class Compresor {
public:
	Compresor();
	virtual ~Compresor();

	void comprimir(uint32_t* bloque, int tamanio,
			std::list<std::bitset<8>> &comprimido);
};

#endif
