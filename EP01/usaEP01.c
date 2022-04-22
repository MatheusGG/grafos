#include "EP01.c"

#define LITORAL 0
#define FESTIVAL 1
#define CONSTRUCOES 2
#define MONTANHAS 3
#define CACHOEIRA 4

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
    criarAresta(grafo, 1, 2, 4, numVertices);
    criarAresta(grafo, 2, 0, 12, numVertices);
    criarAresta(grafo, 2, 4, 40, numVertices);
    criarAresta(grafo, 3, 1, 3, numVertices);
    criarAresta(grafo, 4, 3, 8, numVertices);
    /* Define qual o TIPO de atracao de cada vertice */
    setAtracao(grafo, 0, LITORAL, numVertices);
    setAtracao(grafo, 1, FESTIVAL, numVertices);
    setAtracao(grafo, 2, CONSTRUCOES, numVertices);
    setAtracao(grafo, 3, MONTANHAS, numVertices);
    setAtracao(grafo, 4, MONTANHAS, numVertices);

    imprimeGrafo(grafo, numVertices);

    int vertInicial = 0, tipo = CACHOEIRA;
    /* Encontra o menor caminho do vertice inicial a ao vertice com a atracao buscada*/
    NO* lista = EncontrarCaminho(grafo, numVertices, vertInicial, tipo);
    if(!lista) printf("Nao existe caminho indo do V%d ate o tipo %d", vertInicial, tipo);
    imprimeListaLigada(lista);
    

	// crie um grafo de teste aqui
	// chame a funcao implementada e armazena a lista em uma variavel NO*
	// verifique se a lista retornada está correta
}

