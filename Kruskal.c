#include <stdio.h>
#include <stdlib.h>

#define NUM_V 10
#define NUM_E 15

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int numV, numE;
    struct Edge* edge;
};

struct Subset {
    int parent;
    int rank;
};

struct Graph* createGraph(int numV, int numE) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numV = numV;
    graph->numE = numE;
    graph->edge = (struct Edge*)malloc(numE * sizeof(struct Edge));
    return graph;
}

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int myComp(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight - b1->weight;
}

void KruskalMST(struct Graph* graph) {
    int numV = graph->numV;
    struct Edge result[numV];
    int e = 0;
    int i = 0;

    qsort(graph->edge, graph->numE, sizeof(graph->edge[0]), myComp);

    struct Subset* subsets = (struct Subset*)malloc(numV * sizeof(struct Subset));

    for (int v = 0; v < numV; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    printf("Kruskal MST Algorithm\n");

    while (e < numV - 1 && i < graph->numE) {
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
            printf("Edge (%d,%d) Select %d\n", next_edge.src, next_edge.dest, e);
        }
    }
}

int main() {
    int numV = 10; 
    int numE = 15; 
    struct Graph* graph = createGraph(numV, numE);

    graph->edge[0].src = 2;
    graph->edge[0].dest = 5;
    graph->edge[0].weight = 1;

    graph->edge[1].src = 3;
    graph->edge[1].dest = 4;
    graph->edge[1].weight = 2;

    graph->edge[2].src = 1;
    graph->edge[2].dest = 2;
    graph->edge[2].weight = 3;

    graph->edge[3].src = 2;
    graph->edge[3].dest = 4;
    graph->edge[3].weight = 4;

    graph->edge[4].src = 3;
    graph->edge[4].dest = 8;
    graph->edge[4].weight = 5;

    graph->edge[5].src = 3;
    graph->edge[5].dest = 7;
    graph->edge[5].weight = 6;

    graph->edge[6].src = 2;
    graph->edge[6].dest = 6;
    graph->edge[6].weight = 7;

    graph->edge[7].src = 9;
    graph->edge[7].dest = 10;
    graph->edge[7].weight = 10;

    graph->edge[8].src = 8;
    graph->edge[8].dest = 10;
    graph->edge[8].weight = 15;

    KruskalMST(graph);

    return 0;
}
