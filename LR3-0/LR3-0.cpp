#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	string temp = "";
	ifstream inf;
	inf.open("input.txt");
	if (inf.is_open())
		while (getline(inf, temp)) {}
	inf.close();

	vector <char> res;
	for (int i = 0; i < temp.size(); i++)
		res.push_back(temp[i]);


	bool status = 1;
	while (status == 1)
	{
		status = 0;
		for (int i = 0; i < res.size() - 1; i++)
			if (res[i] == res[i + 1])
			{
				status = 1;
				res.erase(res.begin() + i + 1);
				res.erase(res.begin() + i);
			}
	}
	ofstream outf;
	outf.open("output.txt");
	if (outf.is_open())
		for (int i = 0; i < res.size(); i++)
		{
			//cout << res[i];
			outf << res[i];
		}
	outf.close();
}