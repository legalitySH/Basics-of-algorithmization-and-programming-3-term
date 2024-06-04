#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph {
private:
    vector<vector<int>> adjacencyMatrix;
    int vertices;

public:
    Graph(const vector<vector<int>>& AdjMatrix) {
        adjacencyMatrix = AdjMatrix;
        vertices = AdjMatrix.size();
    }

    void printGraph() {
        cout << "Матрица смежности:" << endl;
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    vector<int> dfs(int start, int end) {
        vector<bool> visited(vertices, false);
        vector<int> path;
        stack<int> stack;

        stack.push(start);

        while (!stack.empty()) {
            int current = stack.top();
            stack.pop();

            if (!visited[current]) {
                visited[current] = true;
                path.push_back(current);

                if (current == end) {
                    return path; 
                }

                for (int neighbor = 0; neighbor < vertices; ++neighbor) {
                    if (adjacencyMatrix[current][neighbor] && !visited[neighbor]) {
                        stack.push(neighbor);
                    }
                }
            }
        }

        return vector<int>();
    }

    vector<int> bfs(int start, int end) {
        vector<bool> visited(vertices, false);
        vector<int> path;
        queue<int> queue;

        queue.push(start);

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();

            if (!visited[current]) {
                visited[current] = true;
                path.push_back(current);

                if (current == end) {
                    return path; 
                }

                for (int neighbor = 0; neighbor < vertices; ++neighbor) {
                    if (adjacencyMatrix[current][neighbor] && !visited[neighbor]) {
                        queue.push(neighbor);
                    }
                }
            }
        }


        return vector<int>();
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    vector<vector<int>> adjacencyMatrix = {
        {0, 0, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };

    Graph graph(adjacencyMatrix);

    int startVertex = 0;
    int endVertex = 1;

    vector<int> dfsPath = graph.dfs(startVertex, endVertex);
    if (!dfsPath.empty()) {
        cout << "DFS путь: ";
        for (int vertex : dfsPath) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else {
        cout << "Путь не найден!" << endl;
    }

    vector<int> bfsPath = graph.bfs(startVertex, endVertex);
    if (!bfsPath.empty()) {
        cout << "BFS путь: ";
        for (int vertex : bfsPath) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else {
        cout << "Путь не найден!" << endl;
    }

    return 0;
}
