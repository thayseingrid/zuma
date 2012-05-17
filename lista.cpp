#include "lista.h"
using namespace Lista;

	template <class T>
	lista<T>::lista() {
		cab = new cel<T> ();
		tam = 0;
		cab->prox = cab;
		cab->ant = cab;

	}
	
	template <class T>
	void lista<T>::inserir_frente(const T& d) {
		cel<T>* novo;
		novo = new cel<T> ();
   
		novo->conteudo = d;
		novo->prox = cab->prox;
		novo->ant = cab;
		cab->prox = novo;
		novo->prox->ant = novo;

		tam += 1;
	}
	
	template <class T>
	void lista<T>::inserir_atras(const T& d) {
		cel<T>* novo;
		novo = new cel<T> ();

		novo->conteudo = d;
		novo->prox = cab;
		novo->ant = cab->ant;
		cab->ant->prox = novo;
		cab->ant = novo;
		tam += 1;
	}
	
	template <class T>
	void lista<T>::insere(int pos, const T& d) {
			if (eh_vazia()) {
					inserir_frente(d);
			}
			else if(!eh_vazia() && pos == tam) {
					inserir_atras(d);
			}
			else if (!eh_vazia()) {
				   
					cel<T>* novo;
					cel<T>* ptr1;
					cel<T>* ptr2;
					ptr1 = cab;
					ptr2 = cab->prox;
					novo = new cel<T> ();
					int cont = 0;

					novo->conteudo = d;
					while (ptr2 != cab) {
							if(cont == pos) {
									novo->prox = ptr2;
									novo->ant = ptr1;
									ptr1->prox = novo;
									ptr2->ant = novo;
							}
				   
							cont += 1;     
							ptr1 = ptr1->prox;
							ptr2 = ptr2->prox;
					}
					tam += 1;
			}                      
   
	}

	template <class T>
	void lista<T>::remove_frente() {
		cel<T>* tmp;
		tmp = cab->prox;

		if (eh_vazia() == false) {
			cab->prox = tmp->prox;
			tmp->prox->ant = cab;
			delete tmp;
		}
	}

	template <class T>
	void lista<T>::remove_atras() {
		cel<T>* tmp;
		tmp = cab->ant;

		if (eh_vazia() == false) {
		   cab->ant = tmp->ant;
		   tmp->ant->prox = cab;
		   delete tmp;
		}
	}

	template <class T>
	void lista<T>::remover(int pos) {
			cel<T>* tmp;
			int cont = 0;
			tmp = cab->prox;
			if(!eh_vazia()) {
					while(tmp != cab && pos != cont) {
							tmp = tmp->prox;
							cont += 1;
					}
					if(pos == cont) {
							tmp->ant->prox = tmp->prox;
							tmp->prox->ant = tmp->ant;
							delete tmp;
							tam -= 1;
					}
			}
	}

	template <class T>
	bool lista<T>::eh_vazia() {
		if (cab->prox == cab && cab->ant == cab)
			return true;
		else
			return false;
	}

	template <class T>
	void lista<T>::print() {
		cel<T>* ptr;
		ptr = cab->prox;
		while (ptr != cab) {
			cout << ptr->conteudo;
			cout << " ";
			ptr = ptr->prox;
		}

		cout << endl;
	}

	template <class T>
	void lista<T>::setData(int i, T& d) {
		cel<T>* tmp = cab->prox;

		while (i != 0) {
			tmp = tmp->prox;
			i = i - 1;
		}

		tmp->conteudo = d;
	}

	template <class T>
	T& lista<T>::getData(int pos) {
		cel<T>* tmp;
		tmp = cab->prox;
		while (pos != 0) {
			tmp = tmp->prox;
			--pos;
		}
		return tmp->conteudo;
	}      

	template <class T>
	lista<T>::~lista() {
		while (!eh_vazia()) {
			remove_frente();
		}
		delete cab;
	}

	template <class T>
	int lista<T>::getTamanho() {
			return tam;
	}

