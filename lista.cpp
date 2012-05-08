#include <iostream>

using namespace std;

template <class T>
class cel {
    public:
        T conteudo;
        cel* prox;
        cel* ant;
};

template <class T>
class lista {
    private:
        cel<T>* cab;
        int tam;

    public:
        lista() {
            cab = new cel<T> ();
            tam = 0;
            cab->prox = cab;
            cab->ant = cab;
        }

        void inserir_frente(const T& d) {
            cel<T>* novo;
            novo = new cel<T> ();
        
            novo->conteudo = d;
            novo->prox = cab->prox;
            novo->ant = cab;
            cab->prox = novo;
            novo->prox->ant = novo;

            tam += 1;
        } 

        void inserir_atras(const T& d) {
            cel<T>* novo;
            novo = new cel<T> ();

            novo->conteudo = d;
            novo->prox = cab;
            novo->ant = cab->ant;
            cab->ant->prox = novo;
            cab->ant = novo;
            tam += 1;
        }

        void remove_frente() {
            cel<T>* tmp;
            tmp = cab->prox;

            if (eh_vazia() == false) {
                cab->prox = tmp->prox;                
                tmp->prox->ant = cab;
                delete tmp; 
            }
        }

        void remove_atras() {
            cel<T>* tmp;
            tmp = cab->ant;

            if (eh_vazia() == false) {
               cab->ant = tmp->ant;
               tmp->ant->prox = cab;
               delete tmp; 
            }
        }
        
        void remove(int pos) {
           cel<T>* ptr1;
           cel<T>* ptr2;
           ptr1 = cab;
           ptr2 = cab->prox;
        
           if (!eh_vazia()) {
              while (ptr2 != cab) {
                 if (pos == cab) {
                    ptr2->ant->prox = ptr2->prox;
                    ptr2->prox->ant = ptr2->ant;
                 }
                 ptr1 = ptr1->prox;
                 ptr2 = ptr2->prox;
              }
              delete ptr2;
              tam -= 1;
           }
        }
        
        void insere (int pos, T d) {
           cel<T>* ptr1;
           cel<T>* ptr2;
           cel<T>* novo;
           ptr1 = cab;
           ptr2 = cab->prox;
           novo = new cel<T>;
           int cont = 0;
        
           while (ptr2 != cab) {
              if (cont == pos) {
                 novo->conteudo = d;
                 novo->prox = ptr2;
                 novo->ant = ptr1;
                 ptr1->prox = novo;
                 ptr2->ant = novo;
              }
              ++cont; 
           }
           ptr1 = ptr1->prox;
           ptr2 = ptr2->prox;
           tam += 1;
        }
                    
        bool eh_vazia() {
            if (cab->prox == cab && cab->ant == cab) 
                return true;
            else
                return false;
        }

        int achar(const T& d) {
            int cont = -1;
            cel<T>* tmp;
            tmp = cab->prox;

            while (tmp != cab) {
                cont += 1;
                if (tmp->conteudo == d) {
                    return cont; 
                }        
                tmp = tmp->prox;
            }
            return cont;
        }

        void print() {
            cel<T>* ptr;
            ptr = cab->prox;

            while (ptr != cab) {
                cout << ptr->conteudo;
                cout << " ";
                ptr = ptr->prox;
            }

            cout << endl;
        }

        ~lista() {
            while (!eh_vazia()) {
                remove_frente();
            }
            delete cab;
        }
};


int main() {
    int num = 1;
    lista<int> Lista;
    
    while (num != 0) {
        cin >> num;
        Lista.inserir_atras(num);
    }
    
    cout << "posicao: " << Lista.achar(0) << endl;
    Lista.print();
    return 0;
}