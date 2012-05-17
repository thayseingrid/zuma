#ifndef CEL_H
#define CEL_H

#include "cel.h"


namespace Lista {

template <class T>
	class cel {
		public:
			T conteudo;
			cel* prox;
			cel* ant;
	};
}

#include "cel.cpp"
	
#endif
