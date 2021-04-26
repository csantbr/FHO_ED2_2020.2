#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1

/* ********************************************* */
/* ******* DEFINI��O DA ESTRUTURA DO N�  ******* */
/* ********************************************* */
/* ------------------------------------------------ */
typedef struct _no {
    char sigla[4];  // chave
    char nome[15];
    int pontos;
    int vitorias;
    int empates;
    int derrotas;
    int golsMarc;
    int golsSofr;
    struct _no *pai;
    struct _no *esq;
    struct _no *dir;
} NO;

/* ********************************************* */
/* *******       ROTINAS AUXILIARES      *******
/* ********************************************* */

/* ------------------------------------------------ */
void inicializar (NO **tree) {

    *tree = NULL;

} /* fim de inicializar */


/* ------------------------------------------------ */
int estaVazia (NO *tree) {
    
    if (tree == NULL)
        return 1;

    return 0;

} /* fim de estaVazia */


/* ******************************************** */
/* *******  ROTINAS DE BUSCA NA �RVORE  *******
/* ******************************************** */

/* -------------------------------------------------------------------- */
NO* achaMaior (NO* arvore) {

    NO* atual = arvore;

    if (!estaVazia(arvore))
        while (atual->dir != NULL)
            atual = atual->dir;

    return atual;

} /* fim de achaMaior */

/* ------------------------------------------------ */
NO* pesquisar (NO *tree, char *sigla) {

    NO *aux = tree;

    while (aux != NULL) {
        
        if (strcmp(sigla, aux->sigla) == 0)
            break;
        
        else if (strcmp(sigla, aux->sigla) < 0)
            aux = aux->esq;
        
        else
            aux = aux->dir;

    } 

    return aux;

} /* fim de pesquisar */

int ehBST (NO *tree) {
	if (!estaVazia(tree)) {
		ehBST(tree->esq);
		ehBST(tree->dir);
		if((tree->esq->chave < tree->chave) && < tree->dir->chave) {
			return 0;
		} else {
			return 1;
		}
	}
}

/* ------------------------------------------------ */
int esvaziaArvore (NO **tree) {

    if (!estaVazia(*tree)) {
        esvaziaArvore(&(*tree)->esq);
        esvaziaArvore(&(*tree)->dir);
        free(*tree);
    }
    
    *tree = NULL;
    return 1;
} /* fim de esvaziaArvore */

/* ------------------------------------------------ */
void exibirMaiorPontuacao(NO *tree) {
	if (estaVazia(tree))
		return;
		
	/* Declara��o de Variaveis */
    NO *maior_one = tree;
   	maior_one = (NO*) malloc(sizeof(NO));
	maior_one->pontos = -1;
	
    NO *maior_two = tree;
    maior_two = (NO*) malloc(sizeof(NO));
	maior_two->pontos = -1;
	
	/* Declara��o de Variaveis auxiliares*/
    NO *aux = tree;
	NO *atd = tree;
	NO *ate = tree;
	
	while ((atd != NULL) && (ate != NULL)) {
		if (atd->pontos > maior_one->pontos) {
			maior_one = atd;
		}
		atd = atd->dir;

		if (ate->pontos > maior_two->pontos) {
			maior_two = ate;
		}
		ate = ate->esq;
	}

	if (maior_one > maior_two) {
		aux = maior_one;
	} else {
		aux = maior_two;
	}
	
	printf("--------- Time com maior quantidade de pontos ---------\n\n");
	printf("Sigla do Time: %s | Quantidade de Pontos: %d | Quantidade de Vitorias: %d | Quantidade de Derrotas: %d |\n Quantidade de Empates: %d | Gols marcados: %d | Gols sofridos: %d\n", aux->sigla, aux->pontos, aux->vitorias, aux->derrotas, aux->empates, aux->golsMarc, aux->golsSofr);
}
/* ------------------------------------------------ */
void emOrdemSigla (NO *arvore) {

    if (!estaVazia(arvore)) {
        emOrdemSigla(arvore->esq);
        printf("%s ", arvore->sigla);
        emOrdemSigla(arvore->dir);
    }

} /* fim de emOrdem */

void emOrdemGeral (NO *arvore) {

    if (!estaVazia(arvore)) {
        emOrdemGeral(arvore->esq);
        
        printf("%s %s\n", arvore->sigla, arvore->nome );
        printf("Pontos: %d\n", arvore->pontos);
        printf("Vitorias: %d, Empates: %d, Derrotas: %d\n", arvore->vitorias, arvore->empates, arvore->derrotas);
        printf("Gols marcados: %d, Gols sofridos: %d\n\n", arvore->golsMarc, arvore->golsSofr);
        
        emOrdemGeral(arvore->dir);
    }

} /* fim de emOrdem */

/* *********************************************** */
/* ******* ROTINAS PARA INSER��O DE UM TIME *******
/* *********************************************** */
void inserirTime (NO **arvore, char *sigla, char *nome) {

    NO* aux;
    NO* papai;

    /* alocar novo noh na memoria */
    NO *novo = (NO*) malloc(sizeof(NO));
    strcpy(novo->sigla, sigla);      
    strcpy(novo->nome, nome);
    novo->pontos=0;
    novo->vitorias=0;
    novo->empates=0;
    novo->derrotas=0;
    novo->golsMarc=0;
    novo->golsSofr=0;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    
    /* se a arvore estiver vazia */
    if (estaVazia(*arvore)) {
        *arvore = novo;
        return;
    }
    
    /* caso contrario */
    aux = *arvore;
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


/* ******************************************************** */
/* ******* ROTINA PARA ATUALIZAD DADOS DAS PARTIDAS ******* */
/* ******************************************************** */
void atualizarPartida(NO *arvore, char *siglaMan, int golsMan, char *siglaVis, int golsVis){
	
	NO *aux;
	int pontosMan = 0, pontosVis = 0;
	int vitMan=0, vitVis = 0;
    int empMan = 0, empVis = 0;
	int derMan = 0, derVis = 0;

	if (golsMan > golsVis){
		pontosMan = 3; 
		vitMan = 1;
	    derVis = 1;
	}
	else if (golsMan < golsVis){
		pontosVis = 3; 
		vitVis = 1;
	    derMan = 1;
	}
	else {
		pontosMan = 1; 
		pontosVis = 1; 
	    empMan = 1;
		empVis = 1;
	}
			
	aux = pesquisar (arvore, siglaMan);
	if (aux != NULL){
		aux->pontos += pontosMan;
		aux->vitorias += vitMan;
    	aux->empates  += empMan;
		aux->derrotas += derMan;
		aux->golsMarc += golsMan;
		aux->golsSofr += golsVis;
	}
					
	aux = pesquisar (arvore, siglaVis);
	if (aux != NULL){
		aux->pontos += pontosVis;
		aux->vitorias += vitVis;
    	aux->empates  += empVis;
		aux->derrotas += derVis;
		aux->golsMarc += golsVis;
		aux->golsSofr += golsMan;
	}
}  /* fim da rotina de atualizacao dos dados de uma partida */

/* ********************************************* */
/* ******* ROTINAS PARA REMO��O DE UM N� *******
/* ********************************************* */

int remover(NO **arvore, char *sigla) {

    NO* atual;
    NO* maior;
    int valor;

    if (estaVazia(*arvore))
        return 1;

    atual = pesquisar(*arvore, sigla);

    /* noh nao encontrado! */
    if (atual == NULL)
        return 0;

    /* ================================================================ */
    /* CASO 1: NOH A SER REMOVIDO EH NOH FOLHA                          */
    /* ================================================================ */
    if ((atual->esq == NULL) && (atual->dir == NULL)) {

        /* noh a ser removido eh noh raiz */
        if (atual->pai == NULL) {
            inicializar(arvore);
            free(atual);
            return 1;
        }
       
        /* noh a ser removido nao eh o noh raiz */
        if (strcmp(sigla, atual->pai->sigla) < 0)
            atual->pai->esq = NULL;
        else
            atual->pai->dir = NULL;

        free(atual);
        return 1;

    } /* fim do CASO 1 */


    /* ================================================================ */
    /* CASO 2: NOH A SER REMOVIDO TEM APENAS UM FILHO                   */
    /* ================================================================ */
    if (((atual->esq != NULL) && (atual->dir == NULL)) ||
        ((atual->esq == NULL) && (atual->dir != NULL))) {

        /* caso o noh 'atual' for o noh raiz */
        if (atual->pai == NULL) {

            /* se filho do noh atual for o filho da esquerda */
            if (atual->esq != NULL)
                *arvore = atual->esq;

            /* se filho do noh atual for o filho da direita */
            else
                *arvore = atual->dir;
        }

        /* caso o noh 'atual' nao for o noh raiz */
        else {

            /* caso do noh 'atual' ser o filho da esquerda */
            if (atual == atual->pai->esq) {
                
                /* caso do filho do noh 'atual' ser o filho da esquerda */
                if (atual->esq != NULL) {
                    atual->pai->esq = atual->esq;
                    atual->esq->pai = atual->pai;
                }

                /* caso do filho do noh 'atual' ser o filho da direita */
                else {
                    atual->pai->esq = atual->dir;
                    atual->dir->pai = atual->pai;
                }

            } /* fim do if (atual == filho da esquerda) */


            /* caso noh 'atual ser o filho da direita */
            else if (atual == atual->pai->dir) {

                /* caso do filho do noh 'atual' ser o filho da esquerda */
                if (atual->esq != NULL) {
                    atual->pai->dir = atual->esq;
                    atual->esq->pai = atual->pai;
                }

                /* caso do filho do noh 'atual' ser o filho da direita */
                else {
                    atual->pai->dir = atual->dir;
                    atual->dir->pai = atual->pai;
                }

            } /* fim do else (atual == filho da direita) */

        } /* fim do else (atual != raiz) */

        free(atual);
        return 1;

    } /* fim do CASO 2 */

    /* ================================================================ */
    /* CASO 3: NOH A SER REMOVIDO TEM AMBOS OS FILHOS                   */
    /* ================================================================ */
    if ((atual->esq != NULL) && (atual->dir != NULL)) {

        /* acha o noh de maior valor da sub-arvore da esquerda */
        maior = achaMaior(atual->esq);
        
        /* guarda valor do noh encontrado */
        strcpy(sigla, maior->sigla);

        /* remove o noh econtrado */
        remover(arvore, maior->sigla);

        /* substitui 'atual' pelo noh encontrado */
        strcpy(atual->sigla, sigla);

    } /* fim do CASO 3 */

}

/* ------------------------------------------------ */
int main () {
    NO *arvore;
    NO *aux;
    FILE *arq;
	int ret, i, op;

    char siglaMan[4], siglaVis[4];
    char nomeMan[15], nomeVis[15];
    char resp[1];
    char versus;
    int pontosMan, pontosVis;
    int vitMan, vitVis;
    int empMan, empVis;
    int derMan, derVis;
    int golsMan, golsVis;	
    
    inicializar(&arvore);

	while(TRUE){
		printf("Menu\n");
		printf("1 - Montar a BST\n");
		printf("2 - Carregar dados das partidas\n");
		printf("3 - Exibir os times em ordem de sigla\n");
		printf("4 - Exibir todos os dados dos times\n");
		printf("5 - Buscar uma equipe pela sigla\n");
		printf("6 - Excluir uma equipe\n");
		printf("7 - Esvaziar  arvore\n");
		printf("8 - Identificar e exibir dados da equipe que tem maior quantidade de pontos\n");
		printf("0 - Sair\n");
	
		printf("\nEscolha uma opcao: ");
		scanf("%d", &op);

		switch (op) {
		
		case 1:
			arq = fopen("A05Times.txt", "r");	
			if (arq == NULL)  {
		       printf("Problemas na abertura do arquivo times.txt\n");
		 	   exit(0);	   
			}
				
			while (fscanf(arq, "%s %[^\n]s", siglaMan, nomeMan) == 2) {
			    inserirTime(&arvore, siglaMan, nomeMan);
			}
						
			fclose(arq); // fecha arquivo A05Times.txt
				
			break;
				
		case 2: 
			printf("Carregando dados das partidas\n");
			arq = fopen("A05partidas.txt", "r");
			if (arq == NULL)  {
       			printf("Problemas na abertura do arquivo partidas.txt\n");
 	   			exit(0);
			}
	
			while(fscanf(arq, "%s %d %c %d %s", siglaMan, &golsMan, &versus, &golsVis, siglaVis ) == 5)
				atualizarPartida(arvore, siglaMan, golsMan, siglaVis, golsVis);
				
			fclose(arq); // fecha arquivo A05Partidas.txt
			
			break;
	
		case 3: 
			printf("\nSiglas em ordem alfabetica\n");
		    emOrdemSigla(arvore);
		    printf("\n\n");
			break;
			
		case 4: 
			printf("\nDados das equipes\n");
		    emOrdemGeral(arvore);
		    printf("\n\n");
			break;
			
		case 5:
			printf("Sigla da equipe: ");
			scanf("%s", siglaMan);
			aux = pesquisar(arvore, siglaMan);
			if (aux != NULL){
		        printf("%s %s\n", aux->sigla, aux->nome);
        		printf("Pontos: %d\n", aux->pontos);
		        printf("Vitorias: %d, Empates: %d, Derrotas: %d\n", aux->vitorias, aux->empates, aux->derrotas);
        		printf("Gols marcados: %d, Gols sofridos: %d\n\n", aux->golsMarc, aux->golsSofr);
			}
			else {
				printf("Time nao encontrado!!!!\n");
			}
					
			break;
			
		case 6: 
			printf("Sigla da equipe a ser excluida: ");
			scanf("%s", siglaMan);

			remover(&arvore, siglaMan);		

			break;
			
		case 7: 
	        esvaziaArvore(&arvore);
	        
			break;
			
		case 8: 
	        exibirMaiorPontuacao(arvore);
	        
			break;
			
		case 0: 
			exit (1);
			
		default:
			printf("Opcao invalida\n"); 
		
		} /* fim do switch */
		
	} /* fim do while */
	
    return 0;

} /* fim do main */
