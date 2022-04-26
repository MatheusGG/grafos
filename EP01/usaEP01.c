#include "EP01.c"

#define LITORAL 0
#define FESTIVAL 1
#define CONSTRUCOES 2
#define MONTANHAS 3
#define CACHOEIRA 4

/*---------- FUNCOES IMPLEMENTADAS ----------*/
// ALUNOS E GRUPO 
void imprimeNumUSPeGrupo(int nroUSP1, int nroUSP2, int grupo);
// GRAFO 
VERTICE* criarGrafo(int v);
NO* criarAdj(int v, int custo);
BOOL criarAresta(VERTICE* gr, int vi, int vf, int custo, int V);
BOOL setAtracao(VERTICE* gr, int vAlterado, int tipo, int numVertices);
void imprimeGrafo(VERTICE* gr, int V);
// LISTA LIGADA
void imprimeListaLigada(NO* lista);
//RESULTADO
void buscaImprimeMenorCaminho(VERTICE* g, int V, int v1, int t);

//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
// mas nao entregue o codido de main() nem inclua nada
// abaixo deste ponto
//---------------------------------------------------------
int main()
{
	if (nroUSP1()==0) printf("\n\nNro USP do primeiro integrante nao informado!!!\n\n");
	if (grupo()==0) printf("\n\nNro do grupo nao informado!!!\n\n");
    imprimeNumUSPeGrupo(nroUSP1(), nroUSP2(), grupo());

    int numVertices = 5;
    /* Cria o grafo com os vertices tipo -1 prox = NULL*/
    VERTICE* grafo = criarGrafo(numVertices);
    int i;
    
    /* Cria as arestas da lista do vertice inicial ao final e seu custo */
    criarAresta(grafo, 0, 1, 2, numVertices);
    criarAresta(grafo, 0, 0, 2, numVertices);
    criarAresta(grafo, 1, 2, 2, numVertices);
    criarAresta(grafo, 2, 0, 2, numVertices);
    criarAresta(grafo, 2, 3, 2, numVertices);
    criarAresta(grafo, 2, 4, 2, numVertices);
    criarAresta(grafo, 3, 1, 2, numVertices);
    criarAresta(grafo, 4, 3, 2, numVertices);
    /* Define qual o TIPO de atracao de cada vertice */
    setAtracao(grafo, 0, LITORAL, numVertices);
    setAtracao(grafo, 1, FESTIVAL, numVertices);
    setAtracao(grafo, 2, CONSTRUCOES, numVertices);
    setAtracao(grafo, 3, MONTANHAS, numVertices);
    setAtracao(grafo, 4, MONTANHAS, numVertices);

    imprimeGrafo(grafo, numVertices);

    /* LITORAL 0 | FESTIVAL 1 | CONSTRUCOES 2 | MONTANHAS 3 | CACHOEIRA 4 */
    int vertInicial = 0, tipo = CACHOEIRA;
    /* Encontra o menor caminho do vertice inicial a ao vertice com a atracao buscada*/
    buscaImprimeMenorCaminho(grafo, numVertices, vertInicial, tipo);
    tipo = MONTANHAS;
    buscaImprimeMenorCaminho(grafo, numVertices, vertInicial, tipo);

    
    

	// crie um grafo de teste aqui
	// chame a funcao implementada e armazena a lista em uma variavel NO*
	// verifique se a lista retornada está correta
}


void imprimeNumUSPeGrupo(int nroUSP1, int nroUSP2, int grupo){
    printf("|==============INTEGRANTES E GRUPO==============|\n");
    printf("\tNroUSP1: %d", nroUSP1);
    printf("\tGrupo: %d\n", grupo);
    printf("\tNroUSP2: %d\n", nroUSP2);
}


/* ---------------------CRIACAO DO GRAFO------------------------- */
VERTICE* criarGrafo(int v) {
    VERTICE* grafo = (VERTICE*) malloc(sizeof(VERTICE)*v);
    int i;
    for(i = 0; i < v; i++){
        grafo[i].inicio = NULL;
        grafo[i].tipo = -1;
    }
    return grafo;
}

NO* criarAdj(int v, int custo) {
    NO* temp = (NO*) malloc(sizeof(NO));
    temp->custo = custo;
    temp->v = v;
    temp->prox = NULL;
    return temp;
}

BOOL criarAresta(VERTICE* gr, int vi, int vf, int custo, int V) {
    if(!gr) return false;
    if((vi < 0) || (vi >= V)) return false;
    if((vf < 0) || (vf >= V)) return false;
    NO* novo = criarAdj(vf, custo);
    novo->prox = gr[vi].inicio;
    gr[vi].inicio = novo;
    return true;
}

BOOL setAtracao(VERTICE* gr, int vAlterado, int tipo, int numVertices) {
    if(!gr) return false;
    if((vAlterado < 0) || (vAlterado >= numVertices)) return false;
    gr[vAlterado].tipo = tipo;
    return true;
}

/* -----------------------LISTA LIGADA--------------------------- */
void imprimeGrafo(VERTICE* gr, int V) {
    if(!gr) return;
    printf("|=====================GRAFO=====================|\n");
    int i;
    for(i = 0; i < V; i++) {
        printf("\tv%d(%d): ", i, gr[i].tipo);
        NO* ad = gr[i].inicio;
        while(ad) {
            printf("v%d(%d) ", ad->v, ad->custo);
            ad = ad->prox;
        }
        printf("\n");
    }
    printf("|===============================================|\n");
}


void imprimeListaLigada(NO* lista) {
    if(!lista) return;
    printf("|=================LISTA LIGADA==================|\n\t");
    while(lista) {
        printf("v%d ", lista->v);
        if(lista->prox) printf("-> ");
        lista = lista->prox;
    }
}

/* ---------------------IMPRIME RESULTADOs------------------------- */
void buscaImprimeMenorCaminho(VERTICE* g, int V, int v1, int t) {
    if(!g) {
        printf("\nGrafo Invalido!\n");
        return;
    }
    NO* lista = EncontrarCaminho(g, V, v1, t);

    if(!lista){ 
        printf("Nao existe caminho indo do v%d ate o tipo %d\n", V, t);
        return;
    }
    printf("O menor caminho indo de V%d ate o tipo %d e:\n", V, t);
    imprimeListaLigada(lista);
}


/*--------------------SAIDA------------------*/
/*
|==============INTEGRANTES E GRUPO==============|
        NroUSP1: 12454  Grupo: 7
        NroUSP2: 1212
|=====================GRAFO=====================|
        v0(0): v0(2) v1(2) 
        v1(1): v2(2) 
        v2(2): v4(2) v3(2) v0(2) 
        v3(3): v1(2) 
        v4(3): v3(2) 
|===============================================|
Nao existe caminho indo do v5 ate o tipo 4
O menor caminho indo de V5 ate o tipo 3 e:
|=================LISTA LIGADA==================|
        v0 -> v1 -> v2 -> v3
*/
