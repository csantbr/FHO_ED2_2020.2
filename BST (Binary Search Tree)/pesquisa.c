/*Função de Pesquisar */
NO* pesquisar(NO *tree, int valor) {
	NO *aux = tree;

	while (aux != NULL) {
		if (valor == aux->dado) {
			break;
		} else if (valor < aux->dado) {
			aux = aux->esq;
		} else {
			aux = aux->dir;
		}
	}

	return aux;
}