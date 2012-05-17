#ifndef LISTA_H
#define LISTA_H

#include "cel.h"
#include <iostream>
using namespace std;


namespace Lista{

template <class T>
	class lista {
		public:
			lista();
			void inserir_frente(const T& d);
			void inserir_atras(const T& d);
			void insere(int pos, const T& d);
			void remove_frente();
			void remove_atras();
			void remover(int pos);
			bool eh_vazia();
			void print();
			void setData(int i, T& d);
			T& getData(int pos);
			~lista();
			int getTamanho();
		private:
			cel<T>* cab;
			int tam;
	};
}

#include "lista.cpp"

#endif
