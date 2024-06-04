#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

const int INF = 1e10;

class Graph {
private:
    unordered_map<int, vector<pair<int, int>>> graph;
    vector<vector<int>> S;

public:


    void AddTop(int top) {
        if (graph.find(top) == graph.end()) {
            graph[top] = vector<pair<int, int>>();
        }
        else {
            cout << "Такая вершина уже существует!" << endl;
        }
    }

    void AddEdge(int from, int to, int weight) {
        if (graph.find(from) != graph.end() && graph.find(to) != graph.end()) {
            graph[from].push_back(make_pair(to, weight));
        }
        else {
            cout << "Одной(или двух вершин) из указанных не существует" << endl;
        }
    }

    void FloydWarshall() {
        unordered_map<int, vector<pair<int, int>>> originalGraph = graph;
        const int SIZE = graph.size();

        vector<vector<int>> D(SIZE, vector<int>(SIZE, INF));
        S.resize(SIZE, vector<int>(SIZE, -1));

        // Инициализация D и S
        for (int i = 0; i < SIZE; ++i) {
            D[i][i] = 0;
            for (auto edge : graph[i + 1]) {
                int v = edge.first;
                int weight = edge.second;
                D[i][v - 1] = weight;
                S[i][v - 1] = v-1; 
            }
        }

        for (int m = 0; m < SIZE; ++m) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    if (i != j && i != m && j != m && D[i][m] + D[m][j] < D[i][j]) {
                        D[i][j] = D[i][m] + D[m][j];
                        S[i][j] = S[i][m]; 
                    }
                }
            }
        }

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (S[i][j] != -1) {
                    int k = S[i][j];
                    while (k != j) {
                        S[i][j] = S[i][k];
                        k = S[k][j];
                    }
                }
            }
        }

        cout << "D = " << endl;
        for (int i = 0; i < SIZE; ++i) {
            cout << '\t';
            for (int j = 0; j < SIZE; ++j) {
                if (D[i][j] == INF) {
                    cout << "0 ";
                }
                else {
                    cout << D[i][j] << " ";
                }
            }
            cout << endl;
        }

        cout << "S = " << endl;
        for (int i = 0; i < SIZE; ++i) {
            cout << "\t";
            for (int j = 0; j < SIZE; ++j) {
                cout << S[i][j]+1 << " ";
            }
            cout << endl;
        }

        graph = originalGraph;
    }
};

int main() {
    Graph graph;

    graph.AddTop(1);
    graph.AddTop(2);
    graph.AddTop(3);
    graph.AddTop(4);
    graph.AddTop(5);
    graph.AddTop(6);


    graph.AddEdge(1, 2, 28);
    graph.AddEdge(1, 3, 21);
    graph.AddEdge(1, 5, 12);
    graph.AddEdge(1, 4, 59);
    graph.AddEdge(1, 6, 27);

    graph.AddEdge(2, 1, 7);
    graph.AddEdge(2, 3, 24);
    graph.AddEdge(2, 6, 9);
    graph.AddEdge(2, 5, 21);

    graph.AddEdge(3, 1, 9);
    graph.AddEdge(3, 2, 32);
    graph.AddEdge(3, 5, 11);
    graph.AddEdge(3, 4, 13);

    graph.AddEdge(4, 1, 8);
    graph.AddEdge(4, 3, 5);
    graph.AddEdge(4, 5, 16);

    graph.AddEdge(5, 1, 14);
    graph.AddEdge(5, 2, 13);
    graph.AddEdge(5, 3, 15);
    graph.AddEdge(5, 4, 10);
    graph.AddEdge(5, 6, 22);

    graph.AddEdge(6, 1, 15);
    graph.AddEdge(6, 2, 18);
    graph.AddEdge(6, 5, 6);

    graph.FloydWarshall();
    return 0;
}
