//Nome: Caio Santoro 	RA:105891
//Nome: Guilherme Viola RA:88206
//Nome: Leandro Silva 	RA:88617

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------ */
typedef struct _no {
    char sigla[3];
    int total_pt;   
    char nome[15];
    int qtd_vit;
    int qtd_emp;
    int qtd_der;
    int qtd_gm;
    int qtd_gs;
    struct _no *pai;
    struct _no *esq;
    struct _no *dir;
} Time;

/* ********************************************* */
/* *******       ROTINAS AUXILIARES      *******
/* ********************************************* */

/* ------------------------------------------------ */
void inicializar (Time **tree) {

    *tree = NULL;

} /* fim de inicializar */

/* ------------------------------------------------ */
int estaVazia (Time *tree) {
    
    if (tree == NULL)
    	return 1;

    return 0;

} /* fim de estaVazia */

/* ******************************************** */
/* *******  ROTINAS DE BUSCA NA ÁRVORE  *******
/* ******************************************** */

/* -------------------------------------------------------------------- */
Time* achaMaior (Time* arvore) {

    Time* atual = arvore;

    if (!estaVazia(arvore))
        while (atual->dir != NULL)
            atual = atual->dir;

    return atual;

} /* fim de achaMaior */

/* ------------------------------------------------ */
void preOrdem (Time *tree) {

    if (tree != NULL) {
        printf("%s ", tree->sigla);
        preOrdem(tree->esq);
        preOrdem(tree->dir);
    }

} /* fim de preOrdem */

/* ------------------------------------------------ */
int esvaziaArvore (Time **tree) {

    if (!estaVazia(*tree)) {
        esvaziaArvore(&(*tree)->esq);
        esvaziaArvore(&(*tree)->dir);
        free(*tree);
    }
    
    *tree = NULL;
    return 1;
} /* fim de esvaziaArvore */

void exibirDados(Time *tree) {
	if (estaVazia(tree))
		return;
		
	/* Declaração de Variaveis */
    Time *maior_one = tree;
   	maior_one = (Time*) malloc(sizeof(Time));
	maior_one->total_pt = -1;
	
    Time *maior_two = tree;
    maior_two = (Time*) malloc(sizeof(Time));
	maior_two->total_pt = -1;
	
	/* Declaração de Variaveis auxiliares*/
    Time *aux = tree;
	Time *atd = tree;
	Time *ate = tree;
	
	while ((atd != NULL) && (ate != NULL)) {
		if (atd->total_pt > maior_one->total_pt) {
			maior_one = atd;
		}
		atd = atd->dir;

		if (ate->total_pt > maior_two->total_pt) {
			maior_two = ate;
		}
		ate = ate->esq;
	}

	if (maior_one > maior_two) {
		aux = maior_one;
	} else {
		aux = maior_two;
	}

	printf("Maior valor: %s\n", aux->sigla);
}

/* ------------------------------------------------ */
void emOrdem (Time *tree) {

    if (!estaVazia(tree)) {
        emOrdem(tree->esq);
        printf("%s %d\n", tree->sigla, tree->qtd_vit);
        emOrdem(tree->dir);
    }

} /* fim de emOrdem */

/* ********************************************** */
/* ******* ROTINAS PARA INSERÇÃO DE UM NÓ *******
/* ********************************************** */
void inserir (Time **tree, char sigla[], char nome[]) {
    Time* aux;
    Time* papai;

    /* alocar novo noh na memoria */
    Time *novo = (Time*) malloc(sizeof(Time));
    strcpy(novo->sigla, sigla);
	strcpy(novo->nome, nome);
	novo->qtd_der = 0;
	novo->qtd_vit = 0;
	novo->qtd_emp = 0;
	novo->qtd_gm = 0;
	novo->qtd_gs = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    
    /* se a arvore estiver vazia */
    if (estaVazia(*tree)) {
        *tree = novo;
        return;
    }
    
    /* caso contrario */
    aux = *tree;
    while (aux != NULL) {

        papai = aux;

        if (strcmp(sigla, aux->sigla) < 0)
            aux = aux->esq;

        else if (strcmp(sigla, aux->sigla) > 0)
            aux = aux->dir;

        else {
            printf("Nao eh possivel inserir o noh\n");
            return;
        }
    
    } /* fim do while (aux != NULL) */
    
    if (strcmp(sigla, papai->sigla) < 0)
        papai->esq = novo;
    else
        papai->dir = novo;

    novo->pai = papai;

} /* fim de inserir */

/* Função para carregar times */
void carregarTimes(Time **tree) {
	int i, value;
	char sigla[3];
	char time[15];
	
	FILE *arq;
	if ((arq = fopen("A05Times.txt", "r")) == NULL) {
	   printf("Arquivo texto não encontrado!\n");
	   exit(0);
	}
	
	while (!feof(arq)) {
		fscanf(arq, "%s %[^\n]s", sigla, time);
		inserir(tree, sigla, time);
	}
	
	fclose(arq);
}

Time* pesquisar(Time **tree, char sigla[]) {

    Time *aux = (*tree);

    while (aux != NULL) {
        
        if (strcmp(sigla, aux->sigla) == 0)
            break;
        
        else if (strcmp(sigla, aux->sigla)<0)
            aux = aux->esq;
        
        else
            aux = aux->dir;

    }
	
    return aux;
  
}


/* ********************************************* */
/* ******* ROTINAS PARA REMO!O DE UM N?*******
/* ********************************************* */
/*Fun? de Busca */
Time* buscaMenor(Time **tree) {
	if ((*tree)->esq != NULL) {
		return buscaMenor(&(*tree)->esq);
	} else {
		Time *aux = *tree;
		if ((*tree)->dir != NULL) {
			(*tree) = (*tree)->dir;
		} else {
			(*tree) = NULL;
		}

		return aux;
	}
}

/*Fun? de Remo? */
int remover(Time **tree, char sigla[]) {
	if (*tree == NULL)
		return;

	if (strcmp(sigla,(*tree)->sigla)<0) {
		remover(&(*tree)->esq, sigla);
	} else if (strcmp(sigla,(*tree)->sigla)>0) {
		remover(&(*tree)->dir, sigla);
	} else {
		Time *aux = *tree;
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
				//free(tree);
				(*tree) = aux;
				aux = NULL;
			}
		}
	}
	return 1;
}

int removeSimples(Time **tree, Time **aux) {
	free(aux);
	*tree = NULL;
}

void carregarPartidas(Time **tree) {
	Time *aux;
    char sigla1[3];
    char sigla2[3];
    char c;
    int gol1, gol2;
    
    FILE *arq;
    
	if ((arq = fopen("A05Partidas.txt", "r")) == NULL) {
	   printf("Arquivo texto não encontrado!\n");
	   exit(0);
	}

	
	while (!feof(arq)) {
	
		fscanf(arq, "%s %d %c %d %s", sigla1, &gol1 , &c , &gol2, sigla2);
	

		if(gol1 > gol2) {
			
            aux = pesquisar(tree, sigla1);
            aux->total_pt+=3;
            aux->qtd_vit +=1;
            aux->qtd_gm += gol1;
            aux->qtd_gs += gol2;
            aux = pesquisar(tree,sigla2);
            aux->qtd_gm += gol2;
            aux->qtd_gs += gol1;
            aux->qtd_der +=1;
            
        } else if(gol2> gol1) {
        	
            aux = pesquisar(tree, sigla2);
            aux->total_pt+=3;
            aux->qtd_vit +=1;
            aux->qtd_gm += gol2;
            aux->qtd_gs += gol1;
            aux = pesquisar(tree,sigla1);
            aux->qtd_gm += gol1;
            aux->qtd_gs += gol2;
            aux->qtd_der +=1;
           
        } else {
            aux = pesquisar(tree, sigla1);
            aux->qtd_gm = gol1;
            aux->qtd_gs = gol2;
            aux->total_pt +=1;
            aux->qtd_emp +=1;
            aux = pesquisar(tree, sigla2);
            aux->qtd_gm = gol2;
            aux->qtd_gs = gol1;
            aux->total_pt +=1;
            aux->qtd_emp +=1;
            
            
        }
              
		
	}
	
	fclose(arq);
}

/* ------------------------------------------------ */
int main () {

    Time *arvore;
    Time *aux;
	int ret;
    inicializar(&arvore);

    carregarTimes(&arvore);
    carregarPartidas(&arvore);
	/*emOrdem(arvore);
	exibirDados(arvore);
	printf("\n");
	remover(&arvore,"FLA");
	
	//emOrdem(arvore);
	
	if(esvaziaArvore(&arvore)){
		printf("Arvore vazia");
	}

	printf("\n");
	emOrdem(arvore);*/
	
	
	exibirDados(arvore);
	
	system("pause");

    return 0;

} /* fim do main */
