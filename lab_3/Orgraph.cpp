#include <iostream>
#include <vector>
#include<set>
#include <unordered_map>

using namespace std;

const int INF = 1e10;

class Graph {
private:
    unordered_map<char, vector<pair<char, int>>> graph;

public:
    void AddTop(char top) {
        if (graph.find(top) == graph.end()) {
            graph[top] = vector<pair<char, int>>();
        }
        else {
            cout << "Такая вершина уже существует!" << endl;
        }
    }

    void AddEdge(char from, char to, int weight) {
        if (graph.find(from) != graph.end() && graph.find(to) != graph.end()) {
            graph[from].push_back(make_pair(to, weight));
        }
        else {
            cout << "Одной(или двух вершин) из указанных не существует" << endl;
        }
    }

    void Dijkstra(char source) {
        unordered_map<char, int> distance;
        set<pair<int, char>> s;

        for (auto p : graph) {
            char vertex = p.first;
            distance[vertex] = INF;
        }

        distance[source] = 0;
        s.insert({ 0, source });

        while (!s.empty()) {
            char current_vertex = s.begin()->second;
            s.erase(s.begin());

            for (auto& edge : graph[current_vertex]) {
                char neighbor = edge.first;
                int weight = edge.second;

                if (distance[current_vertex] + weight < distance[neighbor]) {
                    s.erase({ distance[neighbor], neighbor });
                    distance[neighbor] = distance[current_vertex] + weight;
                    s.insert({ distance[neighbor], neighbor });
                }
            }
        }

        cout << "Кратчайшие пути к вершинам от вершины " << source << ":" << endl;
        for (auto& p : distance) {
            cout << "Вершина " << p.first << ": ";
            if (p.second == INF) {
                cout << "INF" << endl;
            }
            else {
                cout << p.second << endl;
            }
        }
    }

};

int main() {
    setlocale(LC_ALL, "rus");
    Graph graph;

    graph.AddTop('A');
    graph.AddTop('B');
    graph.AddTop('C');
    graph.AddTop('D');
    graph.AddTop('E');
    graph.AddTop('F');
    graph.AddTop('G');
    graph.AddTop('H');
    graph.AddTop('I');

    graph.AddEdge('A', 'B', 7);
    graph.AddEdge('A', 'C', 10);
    
    graph.AddEdge('B', 'A', 7);
    graph.AddEdge('B', 'G', 27);
    graph.AddEdge('B', 'F', 9);
    
    graph.AddEdge('C', 'A', 10);
    graph.AddEdge('C', 'F', 8);
    graph.AddEdge('C', 'E', 31);

    graph.AddEdge('D', 'E', 32);
    graph.AddEdge('D', 'H', 17);
    graph.AddEdge('D', 'I', 21);

    graph.AddEdge('E', 'C', 31);
    graph.AddEdge('E', 'D', 32);

    graph.AddEdge('F', 'H', 11);
    graph.AddEdge('F', 'C', 8);
    graph.AddEdge('F', 'B', 9);

    graph.AddEdge('G', 'B', 27);
    graph.AddEdge('G', 'I', 15);

    graph.AddEdge('H', 'F', 11);
    graph.AddEdge('H', 'D', 17);
    graph.AddEdge('H', 'I', 15);

    graph.AddEdge('I', 'H', 15);
    graph.AddEdge('I', 'G', 15);
    graph.AddEdge('I', 'D', 21);

    
    char vert;
    cout << "От какой вершины ищем кратчайшие пути? ";
    cin >> vert;
    graph.Dijkstra(vert);

    return 0;
}
