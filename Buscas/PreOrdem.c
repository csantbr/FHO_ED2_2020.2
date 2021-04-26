typedef struct _no {
	int dado;
	struct _no *pai;
	struct _no *esq;
	struct _no *dir;
} NO;

void preOrdem (NO *tree) {
	if(tree != NULL) {
		printf("%d ", tree->dado);
		preOrdem(tree->esq);
		preOrdem(tree->dir);
	}
}