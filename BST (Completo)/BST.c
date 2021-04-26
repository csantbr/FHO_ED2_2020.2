#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct _no {
    int dado;
    struct _no *pai;
    struct _no *esq;
    struct _no *dir;
} NO;

void inicializar (NO **tree) {
    *tree = NULL;
}

int estaVazia (NO *tree) { 
    if (tree == NULL) {
        return 1;
    }
    
    return 0;
}

NO* achaMaior (NO* arvore) {
    NO* atual = arvore;

    if (!estaVazia(arvore)) {
		while (atual->dir != NULL) {
            atual = atual->dir;
        }
	}
 
    return atual;
}

NO* pesquisar (NO* tree, int valor) {
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

void preOrdem (NO *tree) {
    if (tree != NULL) {
        printf("%d ", tree->dado);
        preOrdem(tree->esq);
        preOrdem(tree->dir);
    }
}

void posOrdem (NO *tree) {
    if (!estaVazia(tree)) {
        posOrdem(tree->esq);
        posOrdem(tree->dir);
        printf("%d ", tree->dado);
    }
}

void emOrdem (NO *tree) {
    if (!estaVazia(tree)) {
        emOrdem(tree->esq);
        printf("%d ", tree->dado);
        emOrdem(tree->dir);
    }
}

void inserir (NO **tree, int valor) {
    NO* aux;
    NO* papai;

    NO *novo = (NO*) malloc(sizeof(NO));
    novo->dado = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    
    if (estaVazia(*tree)) {
        *tree = novo;
        return;
    }
    
    aux = *tree;
    while (aux != NULL) {
        papai = aux;

        if (valor < aux->dado) {
            aux = aux->esq;
        } else if (valor > aux->dado) {
            aux = aux->dir;
        } else {
            printf("Nao eh possivel inserir o noh\n");
            return;
        }
    }
    
    if (valor < papai->dado) {
		papai->esq = novo;
    } else {
        papai->dir = novo;
    }
    
    novo->pai = papai;
}

int remover(NO **arvore, int dado) {
    NO* atual;
    NO* maior;
    int valor;

    if (estaVazia(*arvore)) {
        return 1;
    }
    
    atual = pesquisar(*arvore, dado);

    if (atual == NULL) {
		return 0;	
	}  

    if ((atual->esq == NULL) && (atual->dir == NULL)) {
        if (atual->pai == NULL) {
            inicializar(arvore);
            free(atual);
            return 1;
        }
       
        if (dado < atual->pai->dado) {
		    atual->pai->esq = NULL;	
		} else {
            atual->pai->dir = NULL;
        }
        
        free(atual);
        return 1;
    }

    if (((atual->esq != NULL) && (atual->dir == NULL)) || ((atual->esq == NULL) && (atual->dir != NULL))) {
        if (atual->pai == NULL) {
            if (atual->esq != NULL) {
                *arvore = atual->esq;

            } else {
				*arvore = atual->dir;
			}
        } else {
            if (atual == atual->pai->esq) {
                if (atual->esq != NULL) {
                    atual->pai->esq = atual->esq;
                    atual->esq->pai = atual->pai;
                } else {
                    atual->pai->esq = atual->dir;
                    atual->dir->pai = atual->pai;
                }
            } else if (atual == atual->pai->dir) {
                if (atual->esq != NULL) {
                    atual->pai->dir = atual->esq;
                    atual->esq->pai = atual->pai;
                } else {
                    atual->pai->dir = atual->dir;
                    atual->dir->pai = atual->pai;
                }
            }
        }

        free(atual);
        return 1;
    }

    if ((atual->esq != NULL) && (atual->dir != NULL)) {
        maior = achaMaior(atual->esq);
        valor = maior->dado;
        remover(arvore, maior->dado);
        atual->dado = valor;
    }
}

void noRaiz(NO *tree) {
	printf("Nó raiz: %d\n", tree->dado);
}

void noRamo(NO *tree) {
	if (!estaVazia(tree)) {
        noRamo(tree->esq);
        noRamo(tree->dir);
        if (((tree->esq != NULL) || (tree->dir != NULL)) && (tree->pai != NULL)) {
		 	printf("Nó Ramo: %d\n", tree->dado);
		}
    }
}

void noFolha(NO *tree) {
	if (!estaVazia(tree)) {
        noFolha(tree->esq);
        noFolha(tree->dir);
    	if ((tree->esq == NULL) && (tree->dir == NULL)) {
		 	printf("Nó Folha: %d\n", tree->dado);
		}
    }
}

int altura(NO *tree) {
    if ((estaVazia(tree)) || (tree->esq == NULL && tree->dir == NULL)) {
   		return 0;
    } else {
   		if(altura(tree->esq) > altura(tree->dir)) {
            return 1 + altura(tree->esq);
        } else {
            return 1 + altura(tree->dir);
        }
    }
}

int alturaNo(NO *tree, int valor) {
    return altura(pesquisar(tree, valor));
}

int profundidade(NO *tree){
	if (!estaVazia(tree)) {
		return 0;
	}
	
	return -1;
}

int profundidadeNo(NO *tree, int valor){
	NO *aux = tree;
	int prof = 0;
	
    while (aux != NULL) {	
        if (valor == aux->dado) {
            break;
        } else if (valor < aux->dado) {
			aux = aux->esq;
        	prof++;	
		} else {
			aux = aux->dir;
        	prof++;
		}
    }

    return prof;
}

int calculaNivel(NO *tree, int valor, int nivel) { 
    if (estaVazia(tree)) {
	    return 0;	
	}
 
    if (tree->dado == valor) {
		return nivel; 	
	}
        
    int ret = calculaNivel(tree->esq, valor, nivel+1); 
    
    if (ret != 0) {
		return ret;
	}   
    ret = calculaNivel(tree->dir, valor, nivel+1); 
    
    return ret; 
}

int nivel(NO *tree, int valor) { 
    return calculaNivel(tree, valor, 1); 
}

int grau(NO *tree, int valor){
	return alturaNo(tree, valor);
}

void buscaAncestrais(NO *tree, int valor) {
   	NO *aux = tree;
	
    while (aux != NULL) {	
        if (valor == aux->dado) {
            break;
        } else if (valor < aux->dado) {
  			printf("%d ", aux->dado);
			aux = aux->esq;	
		} else {
			printf("%d ", aux->dado);
			aux = aux->dir;
		}
    }
    
    printf("\n");
}

void descendentes(NO *tree, int valor) {
    if (!estaVazia(tree)) {
        descendentes(tree->esq,valor);
        if(tree->dado != valor){
			printf("%d ", tree->dado);
		}
        descendentes(tree->dir,valor);
    }
}

void buscaDescendentes(NO *tree, int valor){
	descendentes(pesquisar(tree, valor), valor);
}

void desenhar(NO *tree, NO *aux){
	int i;
    if (!estaVazia(tree)) {
  		for(i = 1; i < calculaNivel(aux, tree->dado, 1); i++){
			printf("    ");
		}
		
        printf("%d\n", tree->dado);
        
        desenhar(tree->esq, aux);
        desenhar(tree->dir, aux);
    }
}

int main () {
	setlocale(LC_ALL, "portuguese");
    NO *arvore;
    NO *aux;
	int ret, valor;
	
    inicializar(&arvore);

	/* ----------------- */
	/* LEIA O README.txt */
	/* ----------------- */
	
    printf("Insira os valores para a arvore: \n");
	while(scanf("%d", &valor) != 0 && valor != 0) {		
		inserir(&arvore, valor);
	}
	
	printf("\n");
   
    printf("Apresentado o nó raiz: \n");
	noRaiz(arvore);
	printf("\n");
	
	printf("Apresentado os nós ramos: \n");
	noRamo(arvore);
	printf("\n");
	
	printf("Apresentado os nós folhas: \n");
	noFolha(arvore);
	printf("\n");
	
	printf("Altura: %d\n", altura(arvore));
	printf("\n");
	
	printf("Altura do nó: %d\n", alturaNo(arvore, 55));
	printf("\n");
	
	printf("Profundidade da arvore: %d\n", profundidade(arvore));
	printf("\n");
	
	printf("Profundidade do nó: %d\n", profundidadeNo(arvore, 55));
	printf("\n");
	
	printf("Nivel do nó: %d\n", nivel(arvore, 55));
	printf("\n");
	
	printf("Grau do nó: %d\n", grau(arvore, 40));
	printf("\n");
	
	printf("Ancestrais do nó: \n");
	buscaAncestrais(arvore, 52);
	printf("\n");
	
	printf("Descendentes do nó: \n");
	buscaDescendentes(arvore, 78);
	printf("\n");
	
	printf("Desenho da arvore:\n");
	desenhar(arvore, arvore);
	printf("\n");
	
    printf("Impressão em Ordem\n\n");
    
    printf(" EM: ");
    emOrdem(arvore);
    printf("\n\n");
    
    printf(" PRE: ");
    preOrdem(arvore);
    printf("\n\n");
    
    printf(" POS: ");
    posOrdem(arvore);
    printf("\n\n");

    return 0;
}