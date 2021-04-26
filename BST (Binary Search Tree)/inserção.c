void inserir(NO *tree, int valorInserir) {
    NO *aux;
    NO *papai;
    NO *novo;
	
	//alocar memoria
	novo = (NO*) malloc(sizeof(NO));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL; 
	novo->pai = NULL;
	
	//se a arvore estiver vazia
	if (estaVazia(*tree)) {
		*tree = novo;
		return;
	}
	
	// se a arvore não estiver vazia
	aux = *tree;
    	
	while(aux != NULL) {
        papai = aux;
        		
        if (valor < aux->dado) { 
        	aux = aux->esq;	
        } else if (valor > aux->dado) {
        	aux = aux->dir;
        } else {
        	printf("N�o eh possivel incluir esse valor");
        	return;
        }
    }

    if (valor < papai->dado) {
       papai->esq = novo;
    } else {
    	papai->dir = novo;
    	novo->pai = papai;
    }
}
