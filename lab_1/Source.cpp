#include<iostream>

using namespace std;

int Moves = 0;

void hanoi(int N, int StartPosition, int EndPosition, int HelpPosition)
{
	if (N <= 0 || EndPosition <= 0)
	{
		cout << "������������ ������� ���������" << endl;
		return;
	}
	if (N == 1)
	{
		cout << "����������� ���� 1 �" << StartPosition << " ��" << EndPosition << " ���������" << endl;
		Moves++;
		return;
	}
	hanoi(N - 1, StartPosition, HelpPosition, EndPosition);
	cout << "����������� ���� " << N << " � " << StartPosition << " �� " << EndPosition << " ���������" <<  endl;
	Moves++;
	hanoi(N - 1, HelpPosition, EndPosition, StartPosition);

}

int main()
{
	setlocale(LC_ALL, "Rus");
	int N;
	cout << "������� ���������� ������ N = ";
	cin >> N;

	int k;
	cout << "������� ���������� �������� k = ";
	cin >> k;


	hanoi(N, 1, k, k - 1);

	if (Moves != 0)
	{
		cout << "�������� �������� �� " << Moves << " ��������" << endl;
	}





}

