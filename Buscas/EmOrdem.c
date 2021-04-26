typedef struct _no {
	int dado;
	struct _no *pai;
	struct _no *esq;
	struct _no *dir;
} NO;

void emOrdem (NO *tree) {
	if(tree != NULL) {
		if(tree->esq != NULL) {
			emOrdem(tree->esq);
		} else {
			printf("%d ", tree->dado);
		}
		
		printf("%d ", tree->dado);
		
		if(tree->dir != NULL) {
			emOrdem(tree->dir);
		} else {
			printf("%d ", tree->dado);
		}
	}
}