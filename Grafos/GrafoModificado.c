/* ************************************************** */
/* *** este programa implementa um grafo simples, *** */
/* **        nao valorado e nao direcionado           */
/* ************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* ********************************************* */
/* *** estrutura da lista e tamanho do grafo *** */
/* ********************************************* */

#define N 5

#define TRUE 1
#define FALSE 0

typedef struct _vertice {
	char id;
	int peso;
	int status;
} Vertice;

typedef struct _no {
	int id;
	struct _no *proximo;
} NoLista;

/* ********************************************* */
/* ***          funcoes auxiliares           *** */
/* ********************************************* */

/* Exibe o grafo ------------------------------------------------- */
void imprimeGrafo(Vertice g[N][N]){
	int lin, col;
	printf("MATRIZ DE ADJACENCIA DO GRAFO\n");
	
	for(lin=0; lin<N; lin++){
		for(col=0; col<N; col++){
			printf("%d ", g[lin][col].peso);
		}
		printf("\n");
	}
} /* fim da funcao imprimeGrafo */
	

/* inicializa a lista ------------------------------------------------- */
void inicializaLista (NoLista **lista) {
	
    *lista = NULL;
    
} /* fim de inicializaLista */

void zeraGrafo(Vertice grafo[N][N]) {
	int lin, col;
	for(lin=0; lin<N; lin++){
		for(col=0; col<N; col++){
			grafo[lin][col].peso = 0;
		}
	}
}

/* verifica se a lista esta vazia ------------------------------------- */
int estaVazia (NoLista *lista) {

    return (lista == NULL);

} /* fim de estaVazia */

/* adiciona um elemento no final da lista ----------------------------- */
void insereFinal (NoLista **lista, int id) {

    NoLista *atual = *lista;
    NoLista *novo;
    
    novo = (NoLista*) malloc (sizeof(NoLista));
    novo->id = id;

    if (estaVazia(*lista)) {
        *lista = novo;
        novo->proximo = NULL;
        return;
    }

    while (atual->proximo != NULL)
        atual = atual->proximo;

    atual->proximo = novo;
    novo->proximo = NULL;

} /* fim de insereFinal */

/* remove o elemento do inicio da lista ------------------------------- */
int removeInicio (NoLista **lista) {

    NoLista *atual = *lista;
    int id;

    if (estaVazia(*lista))
        return -1;

    *lista = atual->proximo;
    id = atual->id;
    free(atual);
    return id;

} /* fim de removeInicio */

int convert(char letter) {
	int i;
	char letras[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	for(i = 0; i < 26; i++) {
		if(letras[i] == letter) {
			return i;
		}
	}
	return -1;
}

int deconvert(int letter) {
	int i;
	char letras[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	for(i = 0; i < 26; i++) {
		if(i == letter) {
			return letras[i];
		}
	}
	return -1;
}


void buscaP(Vertice g[N][N], char v, int p1){
	int w;
	
	/* faz status de v = 'visitado'  */
	g[convert(v)][p1].status = 1;
	printf("%c ", deconvert(v));
	
	for(w=0; w<N; w++){
		if((g[convert(v)][w].status==1) || (g[convert(v)][w].status==0)) {

			/* faz uma chamada recurvisa */
			buscaP(g, w, p1++);
		}
		
	} /* fim do for */
	
} /* fim da funcao recursiva buscaP */

/* funcao busca em profundidade */
void buscaEmProfundidade(Vertice g[N][N], char x, int p){
	
	/* faz todos os vertices term status = 'nao visitados' */
	int lin, col;
	for(lin = 0; lin < N; lin++){
		for(col = 0; col < N; col++) {
			g[lin][col].status = 0;
		}
	}

	printf("Busca em profundidade: ");
	
	/* inicia a funcao recursiva */
	buscaP(g, x, p);
	
	printf("\n");
	
} /* fim da buscaEmProfundidade */

void insereGrafo(Vertice grafo[N][N], char origem, char dest, int peso, int opcao, int opcao2) {
	if(dest == ' ') {
		int i = sizeof(grafo);
		for(i = 0; i < N; i++) {
			grafo[convert(origem)][i].peso = 0;
		}
	}
	
	if(origem == dest) {
		if(peso != 0){
			grafo[convert(origem)][convert(dest)].id = origem;
			grafo[convert(origem)][convert(dest)].peso = peso;
		} else {
			grafo[convert(origem)][convert(dest)].id = origem;
			grafo[convert(origem)][convert(dest)].peso = 1;
		}
	}
	
	if(opcao && opcao2) { /* valorado e direcional */
		grafo[convert(origem)][convert(dest)].id = origem;
		grafo[convert(origem)][convert(dest)].peso = peso;
	} else if(!opcao && !opcao2) { /* nao valorado e nao direcional */
		grafo[convert(origem)][convert(dest)].id = origem;
		grafo[convert(origem)][convert(dest)].peso = 1;
		grafo[convert(dest)][convert(origem)].id = dest;
		grafo[convert(dest)][convert(origem)].peso = 1;
	} else if(opcao && !opcao2) { /* valorado e nao direcional */
		grafo[convert(origem)][convert(dest)].id = origem;
		grafo[convert(origem)][convert(dest)].peso = peso;
		grafo[convert(dest)][convert(origem)].id = dest;
		grafo[convert(dest)][convert(origem)].peso = peso;
	} else if(!opcao && opcao2) { /* nao valorado e direcional */
		grafo[convert(origem)][convert(dest)].id = origem;
		grafo[convert(origem)][convert(dest)].peso = 1;
	}
}

int main(){
    // Aula09 2A - FAZER N = 10
    int p = -1;
	Vertice grafo[N][N];
	
	zeraGrafo(grafo);
	insereGrafo(grafo, 'A', 'B', 10, FALSE, TRUE);
	insereGrafo(grafo, 'A', 'D', 5, FALSE, TRUE); 
	insereGrafo(grafo, 'A', 'C', 5, FALSE, TRUE); 
	insereGrafo(grafo, 'B', 'D', 5, FALSE, TRUE);  
	insereGrafo(grafo, 'C', 'D', 5, FALSE, TRUE);  
	insereGrafo(grafo, 'D', 'C', 5, FALSE, TRUE);

	//printf("%d\n", grafo[0][1].peso);       
	//printf("%d\n", grafo[1][0].peso);  

    // Aula09 2B - FAZER N = 8
    
	//ABDC
	imprimeGrafo(grafo);
	
	//buscaEmLargura(grafo, 2);	
	
	buscaEmProfundidade(grafo, 'A', p);

	
	return 0;
}