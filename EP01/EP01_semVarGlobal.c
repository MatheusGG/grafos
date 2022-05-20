/* Alguns algoritmos como fila e dijkstra foram adoptados do professor Norton e Digiampietri, univesp */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <limits.h>

typedef int BOOL;

// nos das listas de adjacencias
// usados no grafo, e para uso tambem na lista de resposta
typedef struct adj {
	int v;
    int custo;
	struct adj* prox;
} NO;

// vertices
typedef struct {
    int tipo;
	NO* inicio;
} VERTICE;

/*---------- FUNCOES IMPLEMENTADAS ----------*/
// ALUNOS E GRUPO 
int grupo();
int nroUSP1();
int nroUSP2();
// DIJKSTRA
void  inicializaD(VERTICE* g, int* d, int* p, int s, int V);
void relaxa(VERTICE *g, int* d, int* p, int u, int v);
int* dijkstraAlterado(VERTICE* g, int s, int tipo, int V);
BOOL existeAberto(VERTICE* g, int* aberto, int V);
int menorDist(VERTICE* g, int* aberto, int* d, int V);
// LISTA LIGADA
NO* criarNo(int v, int custo);
NO* buscaSeq(NO* lista, NO** ant);
BOOL inserirElementoLista(NO* inicio, int vertice);
// FUNCAO DO EP
// funcao principal (assinatura exigida por alguns compiladores)
NO* EncontrarCaminho(VERTICE* g, int V, int v1, int t);

// ######### ESCREVA O NRO DO SEU GRUPO AQUI CONFORME CADASTRADO EM
// https://docs.google.com/spreadsheets/d/1_wy0Uko3vX8GE07G1WP4X6X6-yRdu6eCpLdmmRvU7EM/edit?usp=sharing

int grupo() {
    return 7;
}

// ######### ESCREVA O NROUSP AQUI
int nroUSP1() {
    return 9023030;
}

int nroUSP2() {
    return 12692367;
}

/* -------------------------------DIJKSTRA-------------------------------------- */
int* dijkstraAlterado(VERTICE* g, int s, int tipo, int V) {
    int* d = (int*) malloc(sizeof(int) * V); // Armazena as distancias do vertice inial aos demais
    int u;
    int p[V]; //armazena qual o vertice anterior de cada vertice, partindo do vertice inicial
    BOOL aberto[V]; // guarda quais vertices tem um caminho possivel/aberto ainda
    inicializaD(g, d, p, s, V); //

    int i;
    for(i = 0; i < V; i++) // define todos os caminhos como abertos
        aberto[i] = 1;

    // enquando existir caminho abertos, ele registra a menor distancia entre o vertice inicial e os demais vertices
    while(existeAberto(g, aberto, V)) {
        u = menorDist(g, aberto, d, V);
        aberto[u] = 0;
        NO* ad = g[u].inicio;
        while(ad) {
            relaxa(g, d, p, u, ad->v);
            ad = ad->prox;
        }
    }


    int menorCusto = INT_MAX/2;
    int vertComMenorCusto = -1;
    /* verifica o vertice com menor custo */
    for(i = 0; i < V; i++){
        if(g[i].tipo == tipo && d[i] < menorCusto) {
            vertComMenorCusto = i;
            menorCusto = d[i];
        }
    }
    /* cria uma lista com os vertices de menor caminho do inicial ate o tipo buscado */
    int* listaComCaminhoVertMenorCusto = (int*) malloc(sizeof(int)*V);
    for(i = 0; i < V; i++) {
        if(p[vertComMenorCusto] != -1) {
            listaComCaminhoVertMenorCusto[i] = vertComMenorCusto;
            vertComMenorCusto = p[vertComMenorCusto];
        } else {
            listaComCaminhoVertMenorCusto[i] = - 1;
        }
    } 

    return listaComCaminhoVertMenorCusto;
}

/*
* Inicializa os arrays colocando a distancia dos outros vertice ao inicial como o maior valor possivel 
* define -1 como anterior para todos os vertices  
*/
void inicializaD(VERTICE* g, int* d, int* p, int s, int V) {
    int v;
    for(v = 0; v < V; v++) {
        d[v] = (int) INT_MAX/2;
        p[v] = -1;
    }
    d[s] = 0;
}

void relaxa(VERTICE *g, int* d, int* p, int u, int v) {
    NO* ad = g[u].inicio;
    while(ad && ad->v != v){
       ad = ad->prox;
    }
    if(ad) {
        if(d[v] > d[u] + ad->custo) {
            d[v] = d[u] + ad->custo;
            p[v] = u;
        }
    }
}

BOOL existeAberto(VERTICE* g, int* aberto, int V) {
    int i;
    for(i = 0; i< V; i++) {
        if(aberto[i]) return 1;
    }
    return 0;
}

/* verifica a menor distancia entre os vertices, partindo do vertice inicial */ 
int menorDist(VERTICE* g, int* aberto, int* d, int V){
    int i;
    for(i = 0; i < V; i++) 
        if(aberto[i]) break;
    if(i == V) return -1;
    int menor = i;
    for(i = menor+1; i < V; i++) 
        if(aberto[i] && (d[menor] > d[i]))
            menor = i;
    return menor;
}

/* -------------------------------DIJKSTRA-------------------------------------- */

/* -----------------LISTA LIGADA CONTENDO OS NOS--------------------- */
NO* criarNo(int v, int custo) {
    NO* temp = (NO*) malloc(sizeof(NO));
    temp->custo = custo;
    temp->v = v;
    temp->prox = NULL;
    return temp;
}

NO* buscaSeq(NO* lista, NO** ant){
    *ant = NULL;
    NO* atual = lista;
    while(atual != NULL) {
        *ant = atual;
        atual = atual->prox;
    }
    if(atual != NULL) return atual;
    return NULL;
}

BOOL inserirElementoLista(NO* inicio, int vertice) {
    NO* ant;
    NO* i = buscaSeq(inicio, &ant);
    if (i != NULL) return 0;
    i = (NO*) malloc(sizeof(NO));
    i->v = vertice;
    if(ant == NULL) {
        i->prox = inicio;
        inicio = i;
    } else {
        i->prox = ant->prox;
        ant->prox = i;
    }
    return 1;
}

/* -----------------LISTA LIGADA CONTENDO OS NOS--------------------- */

/* ---------------------- FUNCAO DO EP ---------------------- */
//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO* EncontrarCaminho(VERTICE* g, int V, int v1, int t)
{
	if(!g) return NULL;
    if(v1 < 0 || v1 > V) return NULL;
    int i, temTipo = 0;
    /* verifica se existe o tipo procurado em um dos vertices */ 
    for(i = 0; i < V; i++) {
        if(g[i].tipo == t) {
            temTipo = 1;
            break;
        }
    }
    if(!temTipo) return NULL;

    /* Obtem um array com os vertices do vertice inicial ate o vertice final que possui a atracao e tem o menor caminho */
    int* caminhoAnterior = dijkstraAlterado(g, v1, t, V);
    /* verfica o tamanho da lista */
    i=0;
    while(caminhoAnterior[i] != -1) i++;

    /* cria uma lista partindo do inicio e inserindo todos os nos ate o vertice final */
    i--;
    NO* inicio = criarNo(v1, 0);
    while(i >= 0) {
        inserirElementoLista(inicio, caminhoAnterior[i]);
        i--;
    }     

   return inicio;
}
/* ---------------------- FUNCAO DO EP ---------------------- */

