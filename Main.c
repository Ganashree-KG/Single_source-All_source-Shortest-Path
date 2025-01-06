#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
 
#define INF 999
#define FILENAME "graph_data.csv"  // File path for the CSV file
 
typedef struct {
    int *weight;
} Edge;
 
// Global variables for dimensions and nodes
int DIMENSION;
int N;
 
// Function to calculate the magnitude of a vector
double magnitude(int weight[], int dimension) {
    double sum = 0.0;
    for (int i = 0; i < dimension; i++) {
        sum += weight[i];
    }
    return sum;
}
 
// Single Source Shortest Path (Bellman-Ford Algorithm)
void bellmanFord(Edge **graph, int src) {
    double dist[N];
    for (int i = 0; i < N; i++) {
        dist[i] = (i == src) ? 0 : INF;
    }
 
    // Relax all edges N-1 times
    for (int i = 0; i < N - 1; i++) {
        for (int u = 0; u < N; u++) {
            for (int v = 0; v < N; v++) {
                if (graph[u][v].weight[0] != INF) {
                    double weight_uv = magnitude(graph[u][v].weight, DIMENSION);
                    if (dist[u] != INF && dist[u] + weight_uv < dist[v]) {
                        dist[v] = dist[u] + weight_uv;
                    }
                }
            }
        }
    }
 
    // Check for negative-weight cycles
    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            if (graph[u][v].weight[0] != INF) {
                double weight_uv = magnitude(graph[u][v].weight, DIMENSION);
                if (dist[u] != INF && dist[u] + weight_uv < dist[v]) {
                    printf("Graph contains a negative-weight cycle reachable from vertex %d.\n", src);
                    return;
                }
            }
        }
    }
 
    // Print the shortest distances if no negative-weight cycle is detected
    printf("Single Source Shortest Path from Vertex %d:\n", src);
    for (int i = 0; i < N; i++) {
        if (dist[i] == INF)
            printf("Vertex %d: Distance = INF\n", i);
        else
            printf("Vertex %d: Distance = %.2f\n", i, dist[i]);
    }
}

// All Pairs Shortest Path (Floyd-Warshall Algorithm with Negative Cycle Detection)
void floydWarshall(Edge **graph) {
    double dist[N][N];
 
    // Initialize distances
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (graph[i][j].weight[0] == INF) {  // No edge between nodes
                dist[i][j] = INF;
            } else {
                dist[i][j] = magnitude(graph[i][j].weight, DIMENSION);
            }
        }
    }
 
    // Floyd-Warshall algorithm
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
 
    // Check for negative cycles
    for (int i = 0; i < N; i++) {
        if (dist[i][i] < 0) {
            printf("Graph contains a negative-weight cycle.\n");
            return;
        }
    }
 
    // Print the shortest distances if no negative cycle is detected
    printf("\nAll Pairs Shortest Path:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (dist[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%.2f ", dist[i][j]);
            }
        }
        printf("\n");
    }
}

// Function to read graph data from a CSV file
void readGraphFromCSV(Edge ***graph) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        perror("Unable to open file");
        exit(1);
    }
 
    // Read N and DIMENSION from the first line
    if (fscanf(file, "%d,%d", &N, &DIMENSION) != 2) {
        perror("Invalid format in file header");
        exit(1);
    }
 
    // Dynamically allocate memory for the graph
    *graph = (Edge **)malloc(N * sizeof(Edge *));
    for (int i = 0; i < N; i++) {
        (*graph)[i] = (Edge *)malloc(N * sizeof(Edge));
        for (int j = 0; j < N; j++) {
            (*graph)[i][j].weight = (int *)malloc(DIMENSION * sizeof(int));
            for (int k = 0; k < DIMENSION; k++) {
                (*graph)[i][j].weight[k] = INF;  // Initialize to INF
            }
        }
    }
 
    // Read edges from the file
    int u, v;
    while (fscanf(file, "%d,%d", &u, &v) == 2) {
        for (int i = 0; i < DIMENSION; i++) {
            if (fscanf(file, ",%d", &(*graph)[u][v].weight[i]) != 1) {
                (*graph)[u][v].weight[i] = INF;  // Set to INF if no valid weight is provided
            }
        }
    }
 
    fclose(file);
}
int main() {
    // Same main function as before
    Edge **graph;
    readGraphFromCSV(&graph);
 
    int src;
    printf("Enter the source vertex for Bellman-Ford algorithm (0 to %d): ", N - 1);
    scanf("%d", &src);
    if (src < 0 || src >= N) {
        printf("Invalid source vertex.\n");
        return 1;
    }
    bellmanFord(graph, src);
    floydWarshall(graph);
 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            free(graph[i][j].weight);
        }
        free(graph[i]);
    }
    free(graph);
 
    return 0;
}