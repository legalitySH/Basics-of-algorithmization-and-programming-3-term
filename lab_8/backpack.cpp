#include<iostream>
#include<vector>
#include<string>
#include<Windows.h>

using namespace std;


struct Product
{
	string name;
	int weight;
	int cost;

	Product(string name, int weight, int cost)
	{
		this->name = name;
		this->weight = weight;
		this->cost = cost;
	}

	friend ostream& operator << (ostream& os, const Product& Product)
	{
		return os << "Название продукта: " << Product.name << ", вес: " << Product.weight << ", цена: " << Product.cost;
	}
};

void PrintKnapsack(int capacity, const vector<Product> products);

void menu();



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введите вместимость рюкзака = ";
	int N;
	cin >> N;

	vector<Product> products;

	int choice = 0;

	while (choice != 3)
	{
		menu();
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cin.ignore();
			string name;
			int weight;
			float cost;
			cout << "Введите название товара = ";
			getline(cin, name);
			cout << "Введите вес товара = ";
			cin >> weight;
			cout << "Введите стоимость товара = ";
			cin >> cost;

			Product newProduct(name, weight, cost);

			products.push_back(newProduct);

			break;
		}

		case 2 :
		{
			for (auto &product : products)
			{
				cout << product << endl;
			}
			break;
		}
		default:
			break;
		}
	}

	PrintKnapsack(N, products);



	

}

void PrintKnapsack(int capacity, const vector<Product> products)
{
	int productCount = products.size();

	vector<vector<int>> D(productCount + 1, vector<int>(capacity + 1, 0));

	for (int i = 1; i <= productCount ; i++)
	{
		for (int w = 0; w <=capacity ; ++w)
		{
			if (products[i - 1].weight > w) D[i][w] = D[i - 1][w];
			else D[i][w] = max(D[i - 1][w], D[i - 1][w - products[i - 1].weight] + products[i - 1].cost);
		}
	}

	int i = productCount;
	int w = capacity;

	vector<Product> selectedProducts;

	while (i > 0 && w > 0) {
		if (D[i][w] != D[i - 1][w]) {
			selectedProducts.push_back(products[i - 1]);
			w -= products[i - 1].weight;
			i--;
		}
		else {
			i--;
		}
	}

	for (auto item : selectedProducts)
	{
		cout << item << endl;
	}
	

}


void menu()
{
	cout << "1 - Добавить товар" << endl;
	cout << "2 - Посмотреть товары" << endl;
	cout << "3 - Закончить добавлять товары" << endl;
}


