void incluir(GRAPH *g, int vertice1, int vertice2, int peso, int ehdigrafo) {
	if(ehdigrafo) {
		g->arcs[vertice1][vertice2].adj = vertice2;
		g->arcs[vertice1][vertice2].weight = peso;
	} else {
        g->arcs[vertice1][vertice2].adj = vertice2;
		g->arcs[vertice1][vertice2].weight = peso;
		g->arcs[vertice2][vertice1].adj = vertice1;
		g->arcs[vertice2][vertice1].weight = peso;
	}
}