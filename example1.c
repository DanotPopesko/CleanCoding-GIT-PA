#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int vertexCount;
    int *visited;
    struct Node **AdjList;
} GRAPH;

typedef struct Stack {
    int top;
    int capacity;
    int *array;
} STACK;

NODE *create_node(int value) {
    NODE *newNode = malloc(sizeof(NODE));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void add_edge(GRAPH *graph, int from, int to) {
    NODE *newNode = create_node(to);
    newNode->next = graph->AdjList[from];
    graph->AdjList[from] = newNode;

    newNode = create_node(from);
    newNode->next = graph->AdjList[to];
    graph->AdjList[to] = newNode;
}

GRAPH *create_graph(int totalVertices) {
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->vertexCount = totalVertices;
    graph->AdjList = malloc(totalVertices * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * totalVertices);

    for (int i = 0; i < totalVertices; i++) {
        graph->AdjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

STACK *create_stack(int maxCapacity) {
    STACK *stack = malloc(sizeof(STACK));
    stack->array = malloc(maxCapacity * sizeof(int));
    stack->top = -1;
    stack->capacity = maxCapacity;

    return stack;
}

void push(int value, STACK *stack) {
    if (stack->top + 1 < stack->capacity) {
        stack->top++;
        stack->array[stack->top] = value;
    }
}

void DFS(GRAPH *graph, STACK *stack, int currentVertex) {
    NODE *neighborList = graph->AdjList[currentVertex];
    NODE *iterator = neighborList;

    graph->visited[currentVertex] = 1;
    push(currentVertex, stack);

    while (iterator != NULL) {
        int adjacentVertex = iterator->data;
        if (graph->visited[adjacentVertex] == 0)
            DFS(graph, stack, adjacentVertex);
        iterator = iterator->next;
    }
}

void insert_edges(GRAPH *graph, int totalEdges, int totalVertices) {
    int source, destination;
    printf("Adauga %d muchii (de la 0 la %d)\n", totalEdges, totalVertices - 1);
    for (int i = 0; i < totalEdges; i++) {
        scanf("%d%d", &source, &destination);
        add_edge(graph, source, destination);
    }
}

void wipe(GRAPH *graph, int totalVertices) {
    for (int i = 0; i < totalVertices; i++) {
        graph->visited[i] = 0;
    }
}

void CanReachPath(GRAPH *graph, int totalVertices, STACK *stack) {
    int startVertex, endVertex;
    printf("Introduceti nodul de start: ");
    scanf("%d", &startVertex);
    printf("Introduceti nodul final: ");
    scanf("%d", &endVertex);

    stack->top = -1;
    for (int i = 0; i < totalVertices; i++)
        graph->visited[i] = 0;

    DFS(graph, stack, startVertex);

    if (graph->visited[endVertex])
        printf("Exista drum intre %d si %d", startVertex, endVertex);
    else
        printf("Nu exista drum intre %d si %d", startVertex, endVertex);
}

int main() {
    int totalVertices;
    int totalEdges;

    printf("Cate noduri are graful?\n");
    scanf("%d", &totalVertices);

    printf("Cate muchii are graful?\n");
    scanf("%d", &totalEdges);

    GRAPH *graph = create_graph(totalVertices);
    STACK *stack = create_stack(2 * totalVertices);

    insert_edges(graph, totalEdges, totalVertices);
    CanReachPath(graph, totalVertices, stack);

    return 0;
}
