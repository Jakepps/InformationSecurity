#include <iostream>
#include <vector>

using namespace std;


bool CheckSystem(vector<vector<bool>> a, vector<int> ls, vector<int> lo)
{
	// w = true r = false
	for (int i = 0; i < ls.size(); i++)
	{
		for (int j = 0; j < lo.size(); j++)
		{
			if (!((ls[i] > lo[j] && a[i][j]) || (ls[i] <= lo[j] && !(a[i][j]))))
			{
				return false;
			}
		}
	}
	return true;
}

bool GetLsLo(const vector<vector<bool>>& a, vector<int>& ls, vector<int>& lo)
{
	ls.clear();
	lo.clear();

	for (int i = 0; i < a.size(); i++)
	{
		int count_s = 1;

		for (int j = 0; j < a[i].size(); j++)
		{
			if (a[i][j])
			{
				count_s++;
			}
		}

		ls.push_back(count_s);
	}

	for (int i = 0; i < a[0].size(); i++)
	{
		int min = 1;

		for (int j = 0; j < a.size(); j++)
		{
			if (!(a[j][i]) && ls[j] > min)
			{
				min = ls[j];
			}
		}
		lo.push_back(min);
	}

	return CheckSystem(a, ls, lo);
}

void CreateSystem(vector<vector<bool>>& a, vector<int>& ls, vector<int>& lo)
{

	for (int i = 0; i < ls.size(); i++)
	{
		ls[i] = rand() % 10;
	}
	for (int i = 0; i < lo.size(); i++)
	{
		lo[i] = rand() % 10;
	}

	for (int i = 0; i < ls.size(); i++)
	{
		for (int j = 0; j < lo.size(); j++)
		{
			if (ls[i] > lo[j])
			{
				a[i][j] = true;
			}
			else
			{
				a[i][j] = false;
			}
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Rus");
	vector<vector<bool>> matrixA;
	int n, m;
	cout << "Ввидите n и m:" << endl;
	cin >> n >> m;
	matrixA.resize(n);
	for (int i = 0; i < n; i++)
	{
		matrixA[i].resize(m);
	}
	vector<int> ls;
	ls.resize(n);
	vector<int> lo;
	lo.resize(m);
	CreateSystem(matrixA, ls, lo);
	cout << "Ls:" << endl;
	for (int i = 0; i < ls.size(); i++)
	{
		cout << ls[i] << " ";
	}

	cout << endl;

	cout << "Lo:" << endl;
	for (int i = 0; i < lo.size(); i++)
	{
		cout << lo[i] << " ";
	}
	cout << endl;

	cout << "Вывод полномочий субъектов системы:" << endl;
	for (int i = 0; i < ls.size(); i++)
	{
		for (int j = 0; j < lo.size(); j++)
		{
			if (matrixA[i][j])
			{
				cout << "W";
			}
			else
			{
				cout << "R";
			}
		}
		cout << endl;
	}

	if (CheckSystem(matrixA, ls, lo))
	{
		cout << "Система защищенна" << endl;
	}
	else
	{
		cout << "Система не защищенна" << endl;
	}

	if (GetLsLo(matrixA, ls, lo))
	{
		cout << "Безопассная система существует: " << endl;

		for (int i = 0; i < ls.size(); i++)
		{
			cout << ls[i] << " ";
		}

		cout << endl;

		for (int i = 0; i < lo.size(); i++)
		{	
				cout << lo[i] << " ";
		}
	}
}
