#include <iostream>
#include <vector>
#include <climits>
#include <sys/time.h>
using namespace std;

void dijkstra(vector<vector<long long> > &graph, long long vertexStart, long long graphSize) {
    vector<long long> distance(graphSize, 0);
    vector<long long> visited(graphSize, 0);
    long long i, j, count, nextNode, minDistance;

    for (i = 0; i < graphSize; i++) {
        distance[i] = graph[vertexStart][i];
        visited[i] = 0;
    }

    visited[vertexStart] = 1;
    count = 1;

    while (count < graphSize) {
        minDistance = INT_MAX;

        for (i = 0; i < graphSize; i++) {
            if (distance[i] < minDistance && !visited[i]) {
                minDistance = distance[i];
                nextNode = i;
            }
        }

        visited[nextNode] = 1;
        count++;

        for (i = 0; i < graphSize; i++) {
            if (!visited[i] && minDistance + graph[nextNode][i] < distance[i]) {
                distance[i] = minDistance + graph[nextNode][i];
            }
        }
    }

}

int main() {
    long long graphSize, vertexStart; 
    cin >> graphSize >> vertexStart;
    vector<vector<long long> > weight(graphSize, vector<long long>(graphSize, 0));
    long long i, j;

    // START TIME
    double time_start, time_end;
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    time_start = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.00;

    for (i = 0; i < graphSize; i++) {
        for (j = 0; j < graphSize; j++)
            cin >> weight[i][j];
    }

    dijkstra(weight, vertexStart, graphSize);

    // END TIME
    gettimeofday(&tv, &tz);
    time_end = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.00;
    cout << time_end - time_start << "\n";

    return 0;
}

/*
    g++ dijkstra.cpp -o dijkstraNormal
    ./dijkstraNormal < input.txt
*/