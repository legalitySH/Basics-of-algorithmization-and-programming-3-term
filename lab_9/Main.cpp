#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<random>
#include<chrono>
#include <Windows.h>
#include <numeric>

using namespace std;


class Graph {
public:

	unordered_map<int, vector<pair<int, int>>> graph;
	vector<vector<int>> S;

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

	void PrintGraph() {
		for (auto& vertex : graph) {
			cout << "Вершина " << vertex.first << ": ";
			for (auto& edge : vertex.second) {
				cout << "(" << edge.first << ", " << edge.second << ") ";
			}
			cout << endl;
		}
	}
};


class GeneticAlgorithm {

public:

	Graph graph;
	int populationSize;
	int offspringCount;
	int evolutionCount;
	vector<int> bestRoute;
	int bestDistance = INT_MAX;
	int mutationPrecentage;

	GeneticAlgorithm(int populationSize, int offspringCount, int evolutionCount, int mutationPrecentage) {
		this->populationSize = populationSize;
		this->offspringCount = offspringCount;
		this->evolutionCount = evolutionCount;
		this->bestDistance = INT_MAX;
		this->mutationPrecentage = mutationPrecentage;
	}

	int CalculateDistance(const vector<int>& route) {
		int distance = 0;
		for (int i = 0; i < route.size() - 1; ++i) {
			int start = route[i];
			int end = route[i + 1];

			if (graph.S[start][end] == -1) {
				distance += 1000000; 
			}
			else {
				distance += graph.S[start][end];
			}
		}
		int lastCity = route.back();
		int firstCity = route.front();
		if (graph.S[lastCity][firstCity] == -1) {
			distance += 1000000; 
		}
		else {
			distance += graph.S[lastCity][firstCity];
		}

		return distance;
	}

	vector<vector<int>> InitializePopulation(int cityCount) {
		vector<vector<int>> population(populationSize, vector<int>(cityCount, 0));
		for (int i = 0; i < populationSize; ++i) {
			vector<int> route(cityCount);
			iota(route.begin(), route.end(), 0); 
			random_shuffle(route.begin() + 1, route.end()); 
			for (int j = 1; j < cityCount; ++j) {
				int currentCity = route[j];
				int previousCity = route[j - 1];
				while (graph.S[previousCity][currentCity] == -1) {
					random_shuffle(route.begin() + 1, route.end());
					currentCity = route[j];
					previousCity = route[j - 1];
				}
			}

			population[i] = route;
		}
		return population;
	}

	void SelectBestRoute(const vector<vector<int>>& population) {
		for (const auto& route : population) {
			int distance = CalculateDistance(route);
			if (distance < bestDistance) {
				bestDistance = distance;
				bestRoute = route;
			}
		}
	}

	void Solve(Graph& g) {
		graph = g;
		int cityCount = g.graph.size();

		graph.S.resize(cityCount, vector<int>(cityCount, -1)); 

		for (const auto& vertex : g.graph) {
			int adjustedVertex = vertex.first - 1; 
			for (const auto& edge : vertex.second) {
				int adjustedEdge = edge.first - 1; 
				graph.S[adjustedVertex][adjustedEdge] = edge.second;
			}
		}

		cout << "Матрица расстояний: " << endl;
		for (int i = 0; i <graph.S.size(); i++)
		{
			for (int j = 0; j < graph.S[i].size(); j++) {
				cout << graph.S[i][j] << " ";
			}
			cout << endl;
		}


		vector<vector<int>> population = InitializePopulation(cityCount);
		SelectBestRoute(population);

		for (int generation = 0; generation < evolutionCount; ++generation) {
			vector<vector<int>> offspring;

			for (int i = 0; i < populationSize / 2; ++i) {
				int parent1Index = rand() % populationSize;
				int parent2Index = rand() % populationSize;

				vector<int> parent1 = population[parent1Index];
				vector<int> parent2 = population[parent2Index];

				int crossoverPoint = rand() % (cityCount - 1) + 1;

				vector<int> child1(cityCount);
				vector<int> child2(cityCount);

				copy(parent1.begin(), parent1.begin() + crossoverPoint, child1.begin());
				copy(parent2.begin(), parent2.begin() + crossoverPoint, child2.begin());

				int child1Index = crossoverPoint;
				int child2Index = crossoverPoint;

				for (int j = 0; j < cityCount; ++j) {
					if (find(child1.begin(), child1.end(), parent2[j]) == child1.end()) {
						child1[child1Index++] = parent2[j];
					}
					if (find(child2.begin(), child2.end(), parent1[j]) == child2.end()) {
						child2[child2Index++] = parent1[j];
					}
				}

				offspring.push_back(child1);
				offspring.push_back(child2);
			}

			for (auto& child : offspring) {
				if (rand() % 100 < mutationPrecentage) {
					int mutationPoint1 = rand() % (cityCount - 1) + 1;
					int mutationPoint2 = rand() % (cityCount - 1) + 1;
					swap(child[mutationPoint1], child[mutationPoint2]);
				}
			}

			population = offspring;

			SelectBestRoute(population);

			cout << "Популяция: " << generation + 1 << endl;
			cout << "Минимальный маршрут коммивояжера: ";
			for (int i = 0; i < bestRoute.size(); ++i) {
				cout << bestRoute[i]+1 << " ";
			}
			cout << bestRoute[0] + 1;
			cout << endl;
			if (bestDistance < 100000)
			{
				cout << "Длина маршрута: " << bestDistance << endl;
				cout << "-----------------------------" << endl;
			}
			else
			{
				cout << "Не существующий маршрут!" << endl;
				cout << "-----------------------------" << endl;
			}
		}
	}
};


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	srand(time(0));

	Graph graph;
	graph.AddTop(1);
	graph.AddTop(2);
	graph.AddTop(3);
	graph.AddTop(4);
	graph.AddTop(5);
	graph.AddTop(6);
	graph.AddTop(7);
	graph.AddTop(8);

	graph.AddEdge(1, 6, 17);
	graph.AddEdge(1, 2, 5);
	graph.AddEdge(1, 4, 16);
	graph.AddEdge(2, 1, 32);
	graph.AddEdge(2, 3, 8);
	graph.AddEdge(2,6, 19);
	graph.AddEdge(2,8,6);
	graph.AddEdge(3,2,4);
	graph.AddEdge(3,5,8);
	graph.AddEdge(3,6,1);
	graph.AddEdge(4,1,16);
	graph.AddEdge(4,7,11);
	graph.AddEdge(4, 8, 3);
	graph.AddEdge(5, 7, 4);
	graph.AddEdge(5, 8, 16);
	graph.AddEdge(5,3,12);
	graph.AddEdge(6,1,5);
	graph.AddEdge(6,3,22);
	graph.AddEdge(6,2,13);
	graph.AddEdge(7,4,33);
	graph.AddEdge(7,8,5);
	graph.AddEdge(7,5,22);
	graph.AddEdge(8,2,7);
	graph.AddEdge(8,4,21);
	graph.AddEdge(8,5,14);
	graph.AddEdge(8,7,6);







	graph.PrintGraph();

	int populationSize, offspringCount, evolutionCount, mutationPrecentage;
	cout << "Введите размер популяции: ";
	cin >> populationSize;
	cout << "Введите количество потомков при скрещивании: ";
	cin >> offspringCount;
	cout << "Введите количество эволюций: ";
	cin >> evolutionCount;
	cout << "Введите желаемый процент мутации(1-100%): ";
	cin >> mutationPrecentage;
	if (mutationPrecentage < 1 || mutationPrecentage > 100)
	{
		cout << "Ошибка ввода процента мутации";
		return 1;
	}

	GeneticAlgorithm geneticAlgorithm(populationSize, offspringCount, evolutionCount, mutationPrecentage);
	geneticAlgorithm.Solve(graph);

	return 0;
}


// Оптимальный маршрут : 1 2 8 4 7 5 3 6 1 (вес 83)