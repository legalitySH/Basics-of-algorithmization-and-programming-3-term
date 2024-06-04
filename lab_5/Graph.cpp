#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
private:

	using GraphContainer = unordered_map<int, vector<pair<int, int>>>;
	GraphContainer graph;
	int size = 0;
	int m = 0;
	int n = 0;

	struct DisjointSets
	{
		int* parent, * rnk;
		int n;

		DisjointSets(int n)
		{
			this->n = n;
			parent = new int[n + 1];
			rnk = new int[n + 1];

			for (int i = 0; i <= n; i++)
			{
				rnk[i] = 0;
				parent[i] = i;
			}
		}


		int find(int u)
		{
			if (u != parent[u])
				parent[u] = find(parent[u]);
			return parent[u];
		}

		void merge(int x, int y)
		{
			x = find(x), y = find(y);

			if (rnk[x] > rnk[y])
				parent[y] = x;
			else
				parent[x] = y;

			if (rnk[x] == rnk[y])
				rnk[y]++;
		}
	};

	struct Edge
	{
		int start;
		int end;
		int weight;

		Edge(int start, int end , int weight)
		{
			this->start = start;
			this->end = end;
			this->weight = weight;
		}
	};

	vector<Edge> edjes;

public:
	Graph(int size) {
		this->size = size;
	}

	void AddTop(int vert) {
		if (graph.find(vert - 1) == graph.end()) {
			n++;
			graph[vert - 1].push_back(make_pair(int(), -1));
		}
	}

	bool AddEdje(int startTop, int endTop, int weight) {
		if (graph.find(startTop) == graph.end()) {
			AddTop(startTop);
		}
		else if (graph.find(endTop) == graph.end()) {
			AddTop(endTop);
		}
		else if (weight < 0) {
			return false;
		}
		m++;
		graph[startTop - 1].push_back(make_pair(endTop - 1, weight));
		graph[endTop - 1].push_back(make_pair(startTop - 1, weight));
		edjes.push_back({ startTop-1,endTop-1,weight });
		return true;
	}

	void Prima() {
		vector<vector<int>> adjMatrix(size, vector<int>(size, 0));

		for (auto vertice : graph) {
			for (auto connected_vertice : vertice.second) {
				if (vertice.first >= 0 && vertice.first < size && connected_vertice.first >= 0 && connected_vertice.first < size && connected_vertice.second != -1) {
					adjMatrix[vertice.first][connected_vertice.first] = connected_vertice.second;
				}
			}
		}

		for (int i = 0; i < adjMatrix.size(); i++)
		{
			for (int k = 0; k < adjMatrix.size(); k++)
			{
				cout << adjMatrix[i][k] << " ";
			}
			cout << endl;
		}

		vector<int> selectedVertices(size, 0);

		vector<pair<int, int>> edges;

		selectedVertices[0] = 1;
		int minSpanningTreeWeight = 0;

		while (edges.size() < size - 1) {
			int minWeight = INT_MAX;
			int u = -1;
			int v = -1;

			for (int i = 0; i < size; i++) {
				if (selectedVertices[i]) {
					for (int j = 0; j < size; j++) {
						if (!selectedVertices[j] && adjMatrix[i][j]) {
							if (adjMatrix[i][j] < minWeight) {
								minWeight = adjMatrix[i][j];
								u = i;
								v = j;
							}
						}
					}
				}
			}

			if (u != -1 && v != -1) {
				edges.push_back(make_pair(u, v));
				selectedVertices[v] = 1;
				minSpanningTreeWeight += adjMatrix[u][v];
			}
		}

		for (int i = 0; i < edges.size(); i++) {
			cout << i + 1 << ". " << "Вершина: " << edges[i].first + 1 << " - " << edges[i].second + 1 << " Вес: " << adjMatrix[edges[i].first][edges[i].second] << endl;
		}

		cout << "Вес минимального остовного дерева: " << minSpanningTreeWeight << endl;
	}


	void Kruskal() {
		sort(edjes.begin(), edjes.end(), [](const Edge& a, const Edge& b) {
			return a.weight < b.weight;
			});

		DisjointSets ds(size);
		vector<Edge> kruskalEdges;
		int kruskalWeight = 0;
		int edgeNumber = 1;  

		for (auto edge : edjes) {
			int startTop = edge.start;
			int endTop = edge.end;
			int weight = edge.weight;

			int startSet = ds.find(startTop);
			int endSet = ds.find(endTop);

			if (startSet != endSet) {
				kruskalEdges.push_back(edge);
				kruskalWeight += weight;
				ds.merge(startSet, endSet);
				cout << edgeNumber << ". " << "Вершина: " << startTop+1 << " - " << endTop+1 << " Вес: " << weight << endl;
				edgeNumber++;
			}
		}

		cout << "Общий вес минимального остовного дерева: " << kruskalWeight << endl;
	}





	void PrintInfo() {
		cout << "Количество вершин: " << n << endl;
		cout << "Количество рёбер: " << m << endl;
		cout << "Цикломатическое число: " << m - n + 1 << endl;
	}
};

int main() {
	setlocale(LC_ALL, "rus");

	Graph graph(8);

	graph.AddTop(1);
	graph.AddTop(2);
	graph.AddTop(3);
	graph.AddTop(4);
	graph.AddTop(5);
	graph.AddTop(6);
	graph.AddTop(7);
	graph.AddTop(8);
	graph.AddEdje(1, 2, 2);
	graph.AddEdje(1, 5, 2);
	graph.AddEdje(1, 4, 8);
	graph.AddEdje(2, 4, 10);
	graph.AddEdje(2, 3, 3);
	graph.AddEdje(2, 5, 5);
	graph.AddEdje(3, 8, 7);
	graph.AddEdje(3, 5, 12);
	graph.AddEdje(4, 7, 11);
	graph.AddEdje(4, 6, 3);
	graph.AddEdje(4, 5, 14);
	graph.AddEdje(5, 7, 4);
	graph.AddEdje(5, 8, 8);
	graph.AddEdje(5, 6, 11);
	graph.AddEdje(6, 7, 6);
	graph.AddEdje(7, 8, 9);

	graph.PrintInfo();

	cout << "Алгоритм Прима: " << endl;
	graph.Prima();

	cout << "Алгоритм Краскала: " << endl;
	graph.Kruskal();
}
