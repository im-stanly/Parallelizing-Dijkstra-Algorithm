#include <iostream>
#include <vector>
#include <thread>
#include <climits>
#include <sys/time.h>
using namespace std;

int NUM_THREAD;

void findMinDistance(vector<long long> &distance, vector<long long> &visited, vector<vector<long long>> &graph, long long &minDistance, long long &nextNode, int start, int end) {
    for (int i = start; i < end; ++i) {
        if (distance[i] < minDistance && !visited[i]) {
            minDistance = distance[i];
            nextNode = i;
        }
    }
}

void updateDistances(vector<long long> &distance, vector<long long> &visited, vector<vector<long long>> &graph, long long minDistance, long long nextNode, int start, int end) {
    for (int i = start; i < end; ++i) {
        if (!visited[i] && minDistance + graph[nextNode][i] < distance[i])
            distance[i] = minDistance + graph[nextNode][i];
    }
}

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

        vector<thread> threads;

        for (int t = 0; t < NUM_THREAD; ++t)
            threads.emplace_back(findMinDistance, ref(distance), ref(visited), ref(graph), ref(minDistance), ref(nextNode), t * graphSize / NUM_THREAD, (t + 1) * graphSize / NUM_THREAD);

        for (auto &t : threads)
            t.join();

        visited[nextNode] = 1;
        count++;

        threads.clear();

        for (int t = 0; t < NUM_THREAD; ++t)
            threads.emplace_back(updateDistances, ref(distance), ref(visited), ref(graph), minDistance, nextNode, t * graphSize / NUM_THREAD, (t + 1) * graphSize / NUM_THREAD);

        for (auto &t : threads)
            t.join();
    }

}

int main(int argc, char **argv) {
    NUM_THREAD = atoi(argv[1]);

    long long graphSize, vertexStart; 
    cin >> graphSize >> vertexStart;
    vector<vector<long long> > graph(graphSize, vector<long long>(graphSize));
    double time_start, time_end;
    struct timeval tv;
    struct timezone tz;
    
    // START TIME
    gettimeofday(&tv, &tz);
    time_start = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.00;

    for (long long i = 0; i < graphSize; i++) {
        for (long long j = 0; j < graphSize; j++)
            cin >> graph[i][j];
    }

    dijkstra(graph, vertexStart, graphSize);

    // END TIME
    gettimeofday(&tv, &tz);
    time_end = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.00;
    cout << time_end - time_start << "\n";

    return 0;
}
/*
    g++-13 -pthread dijkstraThread.cpp -o dijkstraThread
    ./dijkstraThread 4 < input.txt
*/