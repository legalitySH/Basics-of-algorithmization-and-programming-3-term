#include<iostream>

using namespace std;

int Moves = 0;

void hanoi(int N, int StartPosition, int EndPosition, int HelpPosition)
{
	if (N <= 0 || EndPosition <= 0)
	{
		cout << "Некорректные входные параметры" << endl;
		return;
	}
	if (N == 1)
	{
		cout << "Переместить диск 1 с" << StartPosition << " на" << EndPosition << " стержнень" << endl;
		Moves++;
		return;
	}
	hanoi(N - 1, StartPosition, HelpPosition, EndPosition);
	cout << "Переместить диск " << N << " с " << StartPosition << " на " << EndPosition << " стержнень" <<  endl;
	Moves++;
	hanoi(N - 1, HelpPosition, EndPosition, StartPosition);

}

int main()
{
	setlocale(LC_ALL, "Rus");
	int N;
	cout << "Введите количество дисков N = ";
	cin >> N;

	int k;
	cout << "Введите количество стержней k = ";
	cin >> k;


	hanoi(N, 1, k, k - 1);

	if (Moves != 0)
	{
		cout << "Алгоритм выполнен за " << Moves << " действий" << endl;
	}





}

