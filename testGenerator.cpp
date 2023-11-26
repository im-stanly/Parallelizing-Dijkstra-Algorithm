#include <iostream>
#include <climits>
#include <string>
using namespace std;

int main(int argc, char **argv){
    int graphSize, vertexStart;
    int tmp1 = atoi(argv[1]), tmp2 = atoi(argv[2]);
    
    srand((unsigned) time(NULL));
    graphSize = tmp1 + (rand() % (tmp2 - tmp1));
    vertexStart = rand() % graphSize;
    cout << graphSize << ' ' << vertexStart << '\n';

    for (int i = 0; i < graphSize; i++){
        for (int j = 0; j < graphSize; j++){
            tmp1 = 1 + rand() % 2500;
            if(tmp1 > 2000)
                tmp1 = INT_MAX;
            cout << tmp1 << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}

/*
    g++-13 testGenerator.cpp -o testGenerator
    ./testGenerator 100 1000 > input.txt
*/