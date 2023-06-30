
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define fmt "%d";
typedef int Item;

typedef struct no {
    Item item;
    struct no *prox;
} *List;

List no(Item x, List p) {
    List n = (List)malloc(sizeof(struct no));
    n->item = x;
    n->prox = p;
    return n;
}

void printGraph(List Adj[], int size) {
    for (int i = 0; i < size; i++) {
        List curr = Adj[i];
        std::cout << "Vertex " << i << ": ";
        
        curr = Adj[i]->prox;

        if (curr == NULL) {
            std::cout << "No connections";
        } else {
            while (curr != NULL) {
                std::cout << " \u2192 " << curr->item;
                curr = curr->prox;
            }
        }
        std::cout << std::endl;
    }
}

void bfs(List Adj[], int size, int start)
{
    std::vector<bool> visited(size, false); // vetor para marcar os vértices visitados
    std::queue<int> queue;                   // fila para a busca em largura

    visited[start] = true; // marca o vértice inicial como visitado
    queue.push(start);     // insere o vértice inicial na fila

    while (!queue.empty())
    {
        int current = queue.front(); // obtém o vértice da frente da fila
        queue.pop();                 // remove o vértice da fila

        std::cout << current << " "; // imprime o vértice atual

        // percorre os vértices adjacentes ao vértice atual
        List curr = Adj[current]->prox;
        while (curr != NULL)
        {
            int neighbor = curr->item;
            if (!visited[neighbor])
            {
                visited[neighbor] = true; // marca o vértice adjacente como visitado
                queue.push(neighbor);     // insere o vértice adjacente na fila
            }
            curr = curr->prox;
        }
    }

    std::cout << std::endl;
}


int main (){

    List Adj[] = {
        no(0, no(1, no(2, no(3, NULL)))),
        no(1, no(0, no(3, NULL))),
        no(2, no(0, no(3, no(4, NULL)))),
        no(3, no(1, no(2, no(5, NULL)))),
        no(4, NULL),
        no(5, no(3, no(4, NULL)))
    };

    printGraph(Adj, 6);

    int size = sizeof(Adj) / sizeof(Adj[0]);
    int startVertex = 0;

    cout << endl ;

    cout << "BFS transverssão começando do vértice " << startVertex << ":\n";
    bfs(Adj, size, startVertex);

    return 0;
};







