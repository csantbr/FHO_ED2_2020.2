/* ************************************************** */
/* *** este programa implementa um grafo simples, *** */
/* **        nao valorado e nao direcionado           */
/* ************************************************** */

#include <stdio.h>
#include <stdlib.h>

/* ********************************************* */
/* *** estrutura da lista e tamanho do grafo *** */
/* ********************************************* */

#define N 10

typedef struct _no {
	int id;
	struct _no *proximo;
} NoLista;

/* ********************************************* */
/* ***          funcoes auxiliares           *** */
/* ********************************************* */

/* Exibe o grafo ------------------------------------------------- */
void imprimeGrafo(int g[N][N]){
	int lin, col;
	printf("MATRIZ DE ADJACENCIA DO GRAFO\n");
	
	for(lin=0; lin<N; lin++){
		for(col=0; col<N; col++){
			printf("%d ", g[lin][col]);
		}
		printf("\n");
	}
} /* fim da funcao imprimeGrafo */

/* inicializa a lista ------------------------------------------------- */
void inicializaLista (NoLista **lista) {
    
    *lista = NULL;

} /* fim de inicializaLista */

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


/* ********************************************* */
/* ***          funcoes principais           *** */
/* ********************************************* */
void buscaEmLargura (int g[N][N], int x){
	
	NoLista *fila;
	int visitados[N];
	int v, w;
	int i;
	
	/* faz status nao visitado para todos os vertices de "g" */
	for (i=0; i<N; i++)
		visitados[i] = 0;
		
	/* faz status do vertice inicial = 'visitado' */
	visitados[x] = 1;
	printf("Busca em largura: %d ", x);
	
	/* incluir o vertice x na fila */
	inicializaLista(&fila);
	insereFinal(&fila, x);
	
	while (!estaVazia(fila)){
		/* remove o inicio da fila */
		v = removeInicio(&fila);
		
		/* para todo adjacente nao visitado de v .... */
		for(w=0; w<N; w++){
			if( (g[v][w]==1) && (visitados[w]==0) ) {
				
				/*faz status w como 'visitado' */
				visitados[w] = 1;
				printf("%d ", w);
				
				/* adiciona w na fila */
				insereFinal(&fila, w);
			} /* fim do if */
			
		} /* fim do for */
		
	} /* fim do while */
	
	printf("\n");
} /* fim da funcao buscaEmlargura */


void buscaP(int g[N][N], int visitados[N], int v){
	int w;
	
	/* faz status de v = 'visitado'  */
	visitados[v] = 1;
	printf("%d ", v);
	
	for(w=0; w<N; w++){
		if((g[v][w]==1) && (visitados[w]==0)) {

			/* faz uma chamada recurvisa */
			buscaP(g, visitados, w);
		}
		
	} /* fim do for */
	
} /* fim da funcao recursiva buscaP */



/* funcao busca em profundidade */
void buscaEmProfundidade(int g[N][N], int x){
	
	int visitados[N];
	int i;
	
	/* faz todos os vertices term status = 'nao visitados' */
	for (i=0; i<N; i++)
		visitados[i] = 0;
		
	printf("Busca em profundidade: ");
	
	/* inicia a funcao recursiva */
	buscaP(g, visitados, x);
	
	printf("\n");
	
} /* fim da buscaEmProfundidade */




int main(){
	
/*	int grafo[N][N] = { {0, 1, 1, 0, 0, 0},
	                    {1, 0, 1, 1, 0, 1},
	                    {1, 1, 0, 1, 1, 0},
	                    {0, 1, 1, 0, 1, 1},
	                    {0, 0, 1, 1, 0, 0},
	                    {0, 1, 0, 1, 0, 0} };
*/

    // Aula09 2A - FAZER N = 10
	int grafo[N][N] = { {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
	                    {1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
	                    {1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
	                    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
	                    {0, 1, 1, 0, 0, 1, 1, 0, 0, 0},
	                    {0, 0, 1, 1, 1, 0, 0, 1, 0, 0},
						{0, 1, 0, 0, 1, 0, 0, 1, 0, 1},
						{0, 0, 0, 0, 0, 1, 1, 0, 1, 0},
						{0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
						{0, 0, 0, 0, 0, 0, 1, 0, 1, 0} };


    // Aula09 2B - FAZER N = 8
/*	int grafo[N][N] = { {0, 1, 1, 1, 0, 0, 0, 0},
	                    {0, 0, 0, 0, 0, 0, 0, 0},
	                    {0, 1, 0, 0, 1, 0, 1, 0},
	                    {1, 0, 0, 0, 1, 0, 0, 0},
	                    {0, 0, 0, 0, 0, 0, 0, 1},
	                    {0, 1, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 1, 0, 1, 0, 1},
						{0, 0, 0, 0, 0, 0, 0, 0} };
*/

	imprimeGrafo(grafo);
	
	buscaEmLargura(grafo, 2);	
	
	buscaEmProfundidade(grafo, 2);
	
	return 0;
	
}


