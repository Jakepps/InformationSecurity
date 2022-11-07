﻿#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

void task_1(vector < vector <string> > RW_FROM_FILE_RZLT) // список объектов, не доступных для всех субъектов
{
	vector <int> answer = vector <int>();
	for (int j = 0; j < RW_FROM_FILE_RZLT[0].size(); j++) 
	{
		bool good = true;
		for (int i = 0; i < RW_FROM_FILE_RZLT.size(); i++)  
		{
			if (RW_FROM_FILE_RZLT[i][j] != "_")
				good = false;
		}
		if (good)
			answer.push_back(j + 1);
	}
	cout << "Список объектов, не доступных для всех субъектов" << endl;
	for (int d = 0; d < answer.size(); d++)
		cout << answer[d] << " ";
	cout << endl;
}

void task_2(vector < vector <string> > RW_FROM_FILE_RZLT) // список субъектов, не доступных для всех объектов
{
	vector <int> answer = vector <int>();
	for (int i = 0; i < RW_FROM_FILE_RZLT.size(); i++)  
	{
		bool good = true;
		for (int j = 0; j < RW_FROM_FILE_RZLT[0].size(); j++)  
		{
			if (RW_FROM_FILE_RZLT[i][j] != "_")
				good = false;
		}
		if (good)
			answer.push_back(i + 1);
	}
	cout << "Список субъектов, не доступных для всех объектов" << endl;
	for (int d = 0; d < answer.size(); d++)
		cout << answer[d] << " ";
	cout << endl;
}

void task_3(vector < vector <string> > RW_FROM_FILE_RZLT) // субъекты у которых есть полный доступ
{
	vector <int> answer = vector <int>();
	for (int i = 0; i < RW_FROM_FILE_RZLT.size(); i++)  
	{
		bool good = true;
		for (int j = 0; j < RW_FROM_FILE_RZLT[0].size(); j++)  
		{
			if (RW_FROM_FILE_RZLT[i][j] != "RW")
				good = false;
		}
		if (good)
			answer.push_back(i + 1);
	}
	cout << "Субъекты у которых есть полный доступ" << endl;
	for (int d = 0; d < answer.size(); d++)
		cout << answer[d] << " ";
	cout << endl;
}

void task_4(vector < vector <string> > RW_FROM_FILE_RZLT) // cписок субъектов C1 C2 .. C_i имеющих право записи в один объект O_j.
{
	vector <int> answer = vector <int>();
	for (int j = 0; j < RW_FROM_FILE_RZLT[0].size(); j++)  
	{
		bool good = true;
		for (int i = 0; i < RW_FROM_FILE_RZLT.size(); i++)   
		{
			if (RW_FROM_FILE_RZLT[i][j] != "RW" && RW_FROM_FILE_RZLT[i][j] != "W")
				good = false;
		}
		if (good)
			answer.push_back(j + 1);
	}
	cout << "Список субъектов C1 C2 .. C_i имеющих право записи в один объект O_j." << endl;
	for (int d = 0; d < answer.size(); d++)
		cout << answer[d] << " ";
	cout << endl;
}

void task_5(vector < vector <string> > RW_FROM_FILE_RZLT) // cписок субъектов, каждый из которых имеет полный доступ только к одному объекту
{
	vector <int> answer = vector <int>();
	for (int i = 0; i < RW_FROM_FILE_RZLT.size(); i++)  
	{
		int RW = 0, W = 0;
		for (int j = 0; j < RW_FROM_FILE_RZLT[0].size(); j++)  
		{
			if (RW_FROM_FILE_RZLT[i][j] == "RW")
				RW++;
			if (RW_FROM_FILE_RZLT[i][j] == "W")
				W++;
		}
		if (RW == 1 && W == 0)
			answer.push_back(i + 1);
	}
	cout << "Список субъектов, каждый из которых имеет полный доступ только к одному объекту" << endl;
	for (int d = 0; d < answer.size(); d++)
		cout << answer[d] << " ";
	cout << endl;
}

string RWOX_gen() // 
{
	string M[2] = { "R","W" };
	int w = 2;
	int i, j, n;
	string buff;
	n = pow(2, w);
	vector <string> RWOX;
	for (int i = 0; i < n; i++)
	{
		for (j = 0; j < w; j++)
			if (i & (1 << j))
				buff += M[j];
		RWOX.push_back(buff);
		buff = "";
	}
	int rander = rand() % 3 + 1; 
	int rander_empty_or_not = rand() % 2;
	string for_return;
	if (rander_empty_or_not == 1)
		for_return = RWOX[rander];
	else
		for_return = "_";
	return for_return;
}

vector < vector <string> > input()
{
	int n, m;
	vector <string> temp_N_M_A;
	string s;
	ifstream environ_file("access_matr.txt");
	while (getline(environ_file, s))
		temp_N_M_A.push_back(s);
	environ_file.close();

	n = stoi(temp_N_M_A[0]); //преобразование числовых строк в целые числа
	m = stoi(temp_N_M_A[1]);

	temp_N_M_A.erase(temp_N_M_A.begin(), temp_N_M_A.begin() + 2);
	vector < vector <string> > RW_FROM_FILE_RZLT = vector < vector <string> >();
	string input = "";
	regex re("[ ]");

	for (int i = 0; i < n; i++) // субъекты
	{
		RW_FROM_FILE_RZLT.push_back(vector<string>());
		input = temp_N_M_A[i];
		sregex_token_iterator first{ input.begin(), input.end(), re, -1 }, last;
		vector<string> tokens{ first, last };
		for (int j = 0; j < m; j++) // объекты
			RW_FROM_FILE_RZLT[i].push_back(tokens[j]);
	}
	return RW_FROM_FILE_RZLT;
}

void main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(0));
	int n; // число субъектов 
	int m; // число объектов 
	n = rand() % 100 + 1;
	m = rand() % 100 + 1;

	vector < vector <string> > RW(n, vector <string>(m));
	vector <int> LS(n); 
	vector <int> LO(m); 

	cout << "Генерация RW" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			RW[i][j] = RWOX_gen();

	ofstream out_file;
	out_file.open("access_matr.txt", fstream::in | fstream::out | fstream::trunc);
	if (out_file.is_open())
	{
		out_file << n << endl;
		out_file << m << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				out_file << RW[i][j] << " "; 
			}
			out_file << endl;
		}
	}
	out_file.close();

	task_1(input());
	task_2(input());
	task_3(input());
	task_4(input());
	task_5(input());
}