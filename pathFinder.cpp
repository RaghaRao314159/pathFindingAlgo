
#include <iostream>
using namespace std;
 
// Number of vertices in the graph
#define numVert 18
#define srcParent -1
#define MAX_DIST INT16_MAX

// ------- HELPER FUNCTIONS -------
// returns vertex (not yet completed) that is the shortest distance from source 
int minDistance(int distance[], bool completedSet[]);

// initialises adjacency matrix
void initialise(int graph[numVert][numVert]);

// returns optimum path from source to destination.
void returnPath(int parent[], int j, int bestPath[], int *index);

// ------- PRINTING FUNCTIONS -------
// replace with Serial.write()

// prints optimum path from source to destination.
void printPath(int bestPath[]);
 
// prints minimum distance from source to every vertex
void printDistance(int distance[]);

// ------- PRIMARY FUNCTIONS -------
// Implements dijkstra algorithm (to be improved if need be)
void dijkstra(int graph[numVert][numVert], int source, int destination, int bestPath[numVert], int distance[numVert]);

// main

int main()
{
    int graph[numVert][numVert];
    initialise(graph);

    // declare best path 
    int bestPath[numVert];

    // distance[i] will hold the shortest distance from source to i
    int distance[numVert]; 

    // fill bestPath with the best path
    dijkstra(graph, 17, 5, bestPath, distance);

    // for printing best path
    printPath(bestPath);
    printDistance(distance);
    
 
    return 0;
}

void printPath(int bestPath[])
{
    // for printing best path
    cout << endl;
    cout << "Optimum path: ";
    for (int i = 0; i < numVert; i++) {
        if (bestPath[i] != -1) {
            cout << bestPath[i] << ' ';
        } 
    }
    cout << endl;
}

void returnPath(int parent[], int j, int bestPath[], int *index)
{
    // Base Case : If j is source
    if (parent[j] == srcParent){
        bestPath[*index] = j;
        return;
    }
    // recurse if j is not parent
    returnPath(parent, parent[j], bestPath, index);
    (*index)++;
    bestPath[*index] = j;
    return;
}

int minDistance(int distance[], bool completedSet[])
{
    // Initialize min value to be infinite
    int min = MAX_DIST;
    int min_index;
 
    for (int vert = 0; vert < numVert; vert++)
        if (completedSet[vert] == false && distance[vert] <= min) {
            min = distance[vert];
            min_index = vert;
        }
    // return vertex with min distance (vertices are represented by indices)
    return min_index;
}

void printDistance(int distance[])
{
    cout << endl;
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < numVert; i++) {
        cout << i << " \t\t\t\t" << distance[i] << endl;
    }
}

void dijkstra(int graph[numVert][numVert], int source, int destination, int bestPath[numVert], int distance[numVert]) {
 
    bool completedSet[numVert]; // completedSet[i] will be true if vertex i's distance to 
    // source can no longer be decreased.
 
    // Initialize all distances as INFINITE and completedSet[] as false
    for (int i = 0; i < numVert; i++)
        distance[i] = MAX_DIST, completedSet[i] = false;
 
    // Distance of source vertex from itself is always 0
    distance[source] = 0;

    // initialise best path 
    for (int i = 0; i < numVert; i++) {
            bestPath[i] = -1;
        }
    // initialise parent set
    int parent[numVert];
    for (int i = 0; i < numVert; i++) {
        parent[i] = srcParent;
    }
 
    // Find shortest path for all vertices
    for (int count = 0; count < numVert - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // source in the first iteration.
        int u = minDistance(distance, completedSet);
 
        // Mark the picked vertex as processed
        completedSet[u] = true;
 
        // Update distance value of the adjacent vertices of the
        // picked vertex.
        for (int vert = 0; vert < numVert; vert++)
 
            // Update distance[numVert] only if is not in completedSet,
            // there is an edge from u to numVert, and total
            // weight of path from source to  numVert through u is
            // smaller than current value of distance[numVert]
            if (!completedSet[vert] && graph[u][vert] && distance[u] != INT_MAX && distance[u] + graph[u][vert] < distance[vert]) {
                    // set parent of u to be previous spt vertex
                    parent[vert] = u;
                    distance[vert] = distance[u] + graph[u][vert];
                }
    }
 
    // print the constructed distance array

    // return best path as an array
    int index = 0;
    returnPath(parent, destination, bestPath, &index);
}
 
void initialise(int graph[numVert][numVert]) {
    for (int i = 0; i < numVert; i++) {
        for (int j = 0; j < numVert; j++) {
            graph[i][j] = 0;
        }
    }
    graph[0][3] = 46; graph[3][0] = 46;
    graph[1][2] = 71; graph[2][1] = 71; 
    graph[1][5] = 46; graph[5][1] = 46;
    graph[1][8] = 85; graph[8][1] = 85;
    graph[2][3] = 33; graph[3][2] = 33;
    graph[2][7] = 34; graph[7][2] = 34;
    graph[3][4] = 104; graph[4][3] = 104;
    graph[4][6] = 46; graph[6][4] = 46;
    graph[4][11] = 85; graph[11][4] = 85;
    graph[8][9] = 102; graph[9][8] = 102;
    graph[8][15] = 76 + 103; graph[15][8] = 76 + 103; // bend
    graph[9][10] = 35; graph[10][9] = 35;
    graph[9][13] = 37; graph[13][9] = 37;
    graph[10][11] = 72; graph[11][10] = 72;
    graph[10][12] = 30; graph[12][10] = 30;
    graph[11][16] = 76 + 63; graph[16][11] = 76 + 63;// bend
    graph[13][14] = 45; graph[14][13] = 45;
    graph[13][15] = 39; graph[15][13] = 39;
    graph[15][16] = 42; graph[16][15] = 42;
    graph[16][17] = 38; graph[17][16] = 38;
} 