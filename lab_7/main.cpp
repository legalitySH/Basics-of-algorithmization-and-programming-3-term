#include<iostream>
#include<vector>


using namespace std;


int main()
{
	setlocale(LC_ALL, "rus");
	vector<int> sequence;
	cout << "Последовательность:" << endl;
	for (int i = 0; i < 20; i++)
	{
		sequence.push_back(rand() % 10);
		cout << sequence[i] << " ";
	}
	cout << endl;

}