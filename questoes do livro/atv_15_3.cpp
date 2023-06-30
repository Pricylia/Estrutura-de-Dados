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
    struct no* prox;
} * List;

List no(Item x, List p) {
    List n = (List)malloc(sizeof(struct no));
    n->item = x;
    n->prox = p;
    return n;
}

void bfs(List Adj[], int size, int start, int dest, vector<vector<int>>& paths) {
    queue<vector<int>> queue;
    vector<int> initial_path;
    initial_path.push_back(start);
    queue.push(initial_path);

    while (!queue.empty()) {
        vector<int> current_path = queue.front();
        queue.pop();

        int current_vertex = current_path.back();

        if (current_vertex == dest) {
            paths.push_back(current_path);
        } else {
            List curr = Adj[current_vertex]->prox;
            while (curr != NULL) {
                int next_vertex = curr->item;
                bool already_visited = false;
                for (int i = 0; i < current_path.size(); i++) {
                    if (current_path[i] == next_vertex) {
                        already_visited = true;
                        break;
                    }
                }
                if (!already_visited) {
                    vector<int> new_path = current_path;
                    new_path.push_back(next_vertex);
                    queue.push(new_path);
                }
                curr = curr->prox;
            }
        }
    }
}

int main() {
    List Adj[] = {
        no(0, no(1, no(2, no(3, NULL)))),
        no(1, no(0, no(3, NULL))),
        no(2, no(0, no(3, no(4, NULL)))),
        no(3, no(1, no(2, no(5, NULL)))),
        no(4, NULL),
        no(5, no(3, no(4, NULL)))
    };

    int size = sizeof(Adj) / sizeof(Adj[0]);
    int startVertex = 0;
    int destVertex = 5;

    cout << "BFS transversão começando do vértice " << startVertex << " até o vértice " << destVertex << ":\n";

    vector<vector<int>> paths;
    bfs(Adj, size, startVertex, destVertex, paths);

    int count = 1;
    for (const auto& path : paths) {
        cout << "Caminho " << count++ << ": ";
        for (const auto& vertex : path) {
            cout << vertex << " ";
        }
        cout << endl;
    }

    return 0;
}