typedef struct _no {
	int dado;
	struct _no *pai;
	struct _no *esq;
	struct _no *dir;
} NO;

void posOrdem (NO *tree) {
	if (tree != NULL) {
		if(tree->esq != NULL) {
			posOrdem(tree->esq);
		} else {
			printf("%d ", tree->dado);
		}
		
		if(tree->dir != NULL) {
			posOrdem(tree->dir);
		} else {
			printf("%d ", tree->dado);
		}
	}
}