#include <iostream>
#include <fstream>
#include <queue>
#include <limits>

using namespace std;

const int MAX_VERTICES = 100;  // Максимальна кількість вершин у графі
const int INF = numeric_limits<int>::max();

void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices, int source, int destination) {
    int distances[MAX_VERTICES];
    int parents[MAX_VERTICES];

    for (int i = 0; i < numVertices; i++) {
        distances[i] = INF;
        parents[i] = -1;
    }

    distances[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(distances[source], source));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < numVertices; v++) {
            if (graph[u][v] != 0) {
                int newDistance = distances[u] + graph[u][v];
                if (newDistance < distances[v]) {
                    distances[v] = newDistance;
                    parents[v] = u;
                    pq.push(make_pair(distances[v], v));
                }
            }
        }
    }

    if (distances[destination] == INF) {
        cout << "No path found between the source and destination." << endl;
    }
    else {
        cout << "Shortest distance: " << distances[destination] << endl;

        // Відновлення найкоротшого шляху
        cout << "Shortest path: ";
        int currentVertex = destination;
        cout << currentVertex;
        while (currentVertex != source) {
            currentVertex = parents[currentVertex];
            cout << " <- " << currentVertex;
        }
        cout << endl;
    }
}

void dijkstra2(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices, int source) {
    int distances[MAX_VERTICES];
    int parents[MAX_VERTICES];

    for (int i = 0; i < numVertices; i++) {
        distances[i] = INF;
        parents[i] = -1;
    }

    distances[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(distances[source], source));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < numVertices; v++) {
            if (graph[u][v] != 0) {
                int newDistance = distances[u] + graph[u][v];
                if (newDistance < distances[v]) {
                    distances[v] = newDistance;
                    parents[v] = u;
                    pq.push(make_pair(distances[v], v));
                }
            }
        }
    }

    // Виведення списку вершин з відповідними значеннями найкоротших відстаней
    cout << "Vertex\t\tDistance" << endl;
    for (int i = 1; i < numVertices; i++) {
        cout << i << "\t\t" << distances[i] << endl;
    }
}

int main() {
    ifstream inputFile("t.txt");
    if (!inputFile) {
        cout << "Failed to open the input file." << endl;
        return 0;
    }

    int numVertices, numEdges;
    inputFile >> numVertices >> numEdges;

    int graph[MAX_VERTICES][MAX_VERTICES] = {};

    for (int i = 0; i < numEdges; i++) {
        int u, v, weight;
        inputFile >> u >> v >> weight;
        graph[u][v] = weight;
        graph[v][u] = weight;  // Якщо граф ненапрямлений
    }
    int source, destination;
    cout << "Enter the source vertex: ";
    cin >> source;
    cout << "Enter the destination vertex: ";
    cin >> destination;

    dijkstra(graph, numVertices, source, destination);

    cout << "Enter the source vertex: ";
    cin >> source;

    dijkstra2(graph, numVertices, source);
    return 0;
}

