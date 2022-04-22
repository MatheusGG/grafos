int* dijkstraAlterado(VERTICE* g, int s, int tipo) {
    int* d = (int*) malloc(sizeof(int) * NUM_VERTICES);
    int u;
    int p[NUM_VERTICES];
    BOOL aberto[NUM_VERTICES];
    inicializaD(g, d, p, s);

    int i;
    for(i = 0; i < NUM_VERTICES; i++) 
        aberto[i] = true;

    while(existeAberto(g, aberto)) {
        u = menorDist(g, aberto, d);
        aberto[u] = false;
        NO* ad = g[u].inicio;
        while(ad) {
            relaxa(g, d, p, u, ad->v);
            ad = ad->prox;
        }
    }

    int vertComMenorCusto = -1;
    for(i = 0; i < NUM_VERTICES; i++)
        if(g[i].tipo == tipo && d[i] < vertComMenorCusto)
            vertComMenorCusto = i;
        
    int* listaComCaminhoVertMenorCusto = (int*) malloc(sizeof(int)*NUM_VERTICES);
    for(i = 0; i < NUM_VERTICES; i++) {
        if(p[vertComMenorCusto] != -1) {
            listaComCaminhoVertMenorCusto[i] = vertComMenorCusto;
            vertComMenorCusto = p[vertComMenorCusto];
        } else {
            listaComCaminhoVertMenorCusto[i] = - 1;
        }
    } 
    /* CAMINHO DE V4 até V0*/
    
    /*
    int t = 4;
    printf("v%d", t);
    while(p[t] != -1){
        printf(" -> v%d", p[t]);
        t = p[t];
    }
    printf("\n"); 
 */

    return d;
}