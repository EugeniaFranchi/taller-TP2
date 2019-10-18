#ifndef COLABLOQUEANTE_H_
#define COLABLOQUEANTE_H_
#include <queue>
#include <list>
#include <bitset>
#include <mutex>
#include <condition_variable>

class ColaBloqueante {
private:
	std::queue<std::list<std::bitset<8>>> cola;
	std::mutex m;
	std::condition_variable condVarEstaVacia;
	std::condition_variable condVarEstaLlena;
	bool terminado;
	size_t tamanio;

public:
	explicit ColaBloqueante(size_t tamanio);
	virtual ~ColaBloqueante();

	void push(std::list<std::bitset<8>> &lista);
	int pop(std::list<std::bitset<8>> &elemento);
	void cerrar();
	void pushUnsafe(std::unique_lock<std::mutex> &lock,
			std::list<std::bitset<8>> &lista);
	bool esta_vacia();
	bool esta_cerrada();
};

#endif
