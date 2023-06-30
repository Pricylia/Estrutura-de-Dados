
#include <iostream>
#include <stack>
#include <queue>

struct Node {
    int item;
    Node* next;
};

struct Stack {
    Node* top;
};

struct Graph {
    int V; // Numero de vertices
    Node** adjList; // Lista de adjacencia
};

Node* createNode(int item) {
    Node* newNode = new Node;
    newNode->item = item;
    newNode->next = NULL;
    return newNode;
}

Stack* createStack() {
    Stack* stack = new Stack;
    stack->top = NULL;
    return stack;
}

void push(Stack* stack, int item) {
    Node* newNode = createNode(item);

    if (stack->top == NULL) {
        stack->top = newNode;
    } else {
        newNode->next = stack->top;
        stack->top = newNode;
    }
}

int pop(Stack* stack) {
    if (stack->top == NULL)
        return -1;

    Node* temp = stack->top;
    int item = temp->item;

    stack->top = stack->top->next;

    delete temp;
    return item;
}

Graph* createGraph(int V) {
    Graph* graph = new Graph;
    graph->V = V;
    graph->adjList = new Node*[V];

    for (int i = 0; i < V; i++)
        graph->adjList[i] = NULL;

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void BFS(Graph* graph, int source, int destination) {
    bool* visited = new bool[graph->V];
    int* parent = new int[graph->V];

    for (int i = 0; i < graph->V; i++) {
        visited[i] = false;
        parent[i] = -1;
    }

    std::queue<int> queue;

    visited[source] = true;
    queue.push(source);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        Node* temp = graph->adjList[current];
        while (temp != NULL) {
            int adjVertex = temp->item;

            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                parent[adjVertex] = current;
                queue.push(adjVertex);
            }

            if (adjVertex == destination) {
                // Encontrou o destino
                int v = destination;
                std::cout << "Menor caminho (BFS): " << v;
                while (parent[v] != -1) {
                    std::cout << " <- " << parent[v];
                    v = parent[v];
                }
                std::cout << std::endl;
                break;
            }

            temp = temp->next;
        }
    }

    delete[] visited;
    delete[] parent;
}

void DFS(Graph* graph, int source, int destination) {
    bool* visited = new bool[graph->V];
    int* parent = new int[graph->V];

    for (int i = 0; i < graph->V; i++) {
        visited[i] = false;
        parent[i] = -1;
    }

    Stack* stack = createStack();

    visited[source] = true;
    push(stack, source);

    while (stack->top != NULL) {
        int current = pop(stack);

        Node* temp = graph->adjList[current];
        while (temp != NULL) {
            int adjVertex = temp->item;

            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                parent[adjVertex] = current;
                push(stack, adjVertex);
            }

            if (adjVertex == destination) {
                // Encontrou o destino
                int v = destination;
                std::cout << "Menor caminho (DFS): " << v;
                while (parent[v] != -1) {
                    std::cout << " <- " << parent[v];
                    v = parent[v];
                }
                std::cout << std::endl;
                break;
            }

            temp = temp->next;
        }
    }

    delete[] visited;
    delete[] parent;
    delete stack;
}

int main() {
    int V = 7; // N�mero de v�rtices
    Graph* graph = createGraph(V);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 6);

    int origem = 0;
    int destino = 6;

    BFS(graph, origem, destino);
    DFS(graph, origem, destino);

    return 0;
}
