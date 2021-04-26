/*Função de Busca */
NO* buscaMenor(NO **tree) {
	if ((*tree)->esq != NULL) {
		return buscaMenor(&(*tree)->esq);
	} else {
		NO *aux = *tree;
		if ((*tree)->dir != NULL) {
			(*tree) = (*tree)->dir;
		} else {
			(*tree) = NULL;
		}
		
		return aux;
	}
}

/*Função de Remoção */
int remover(NO **tree, int valor) {
	if (*tree == NULL)
		return;

	if (valor<(*tree)->dado) {
		remover(&(*tree)->esq, valor);
	} else if (valor > (*tree)->dado) {
		remover(&(*tree)->dir, valor);
	} else {
		NO *aux = *tree;
		if (((*tree)->esq == NULL) && ((*tree)->dir == NULL)) { // Se for folha
			removeSimples(*tree, *aux);
		} else { // Se tiver filho a direita
			if ((*tree)->esq == NULL) {
				(*tree) = (*tree)->dir;
				free(aux);
				aux = NULL;
			} else {
				aux = buscaMenor(&(*tree)->dir);
				aux->esq = (*tree)->esq;
				aux->dir = (*tree)->dir;
				free(tree);
				(*tree) = aux;
				aux = NULL;
			}
		}
	}
	
	return 1;
}

int removeSimples(NO **tree, NO **aux) {
	free(aux);
	*tree = NULL;
}