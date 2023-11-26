#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>
#include <climits>
#include <omp.h>
using namespace std;

void dijkstra(vector<vector<long long> > &graph, long long vertexStart, long long graphSize) {
    vector<long long> visited(graphSize, 0);
    vector<long long> distance(graphSize, 0);
    long long md, mv;
    long long nth;

    for (long long i = 0; i < graphSize; i++) {
        visited[i] = 0;
        distance[i] = graph[vertexStart][i];
    }

    visited[vertexStart] = 1;

    #pragma omp parallel shared(visited, md, distance, mv, nth, graph)
    {
        long long my_id = omp_get_thread_num();
        nth = omp_get_num_threads();
        long long my_first = (my_id * graphSize) / nth;
        long long my_last = ((my_id + 1) * graphSize) / nth - 1;

        for (long long my_step = 1; my_step < graphSize; my_step++) {
            #pragma omp single
            {
                md = INT_MAX;
                mv = -1;
            }

            long long my_md = INT_MAX;
            long long my_mv = -1;

            for (long long k = my_first; k <= my_last; k++) {
                if (!visited[k] && distance[k] < my_md) {
                    my_md = distance[k];
                    my_mv = k;
                }
            }

            #pragma omp critical
            {
                if (my_md < md) {
                    md = my_md;
                    mv = my_mv;
                }
            }

            #pragma omp barrier
            #pragma omp single
            {
                if (mv != -1) {
                    visited[mv] = 1;
                }
            }
            #pragma omp barrier

            if (mv != -1) {
                for (long long j = my_first; j <= my_last; j++) {
                    if (!visited[j] && graph[mv][j] < INT_MAX &&
                        distance[mv] + graph[mv][j] < distance[j]) {
                        distance[j] = distance[mv] + graph[mv][j];
                    }
                }
            }

            #pragma omp barrier
        }
    }

}

int main(int argc, char **argv) {
    int threads = atoi(argv[1]);
    omp_set_num_threads(threads);

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
    g++-13 -fopenmp dijkstraOMP.cpp -o dijkstraOMP
    ./dijkstraOMP 4 < input.txt
*/