#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

bool matcher(char* guess, string ans, int correct) {
	int count = 0;
	string str(guess);
	cout << "Matching " << str << " " << ans << endl;
	for (int i = 0; i < ans.size(); i++)
		if (guess[i] == ans[i])
			count++;
	cout << "Matches " << count << " out of " << correct << endl;
	if (count == correct)
	{
		cout << "SUCCESS" << endl;
		return true;
	}
	else return false;

}

bool nextComb(char* a, int n, int m)
{
	int j = m - 1;
	while (j >= 0 && a[j] == 'f') j--;
	if (j < 0) return false;
	if (a[j] == 'f')
		j--;
	a[j] = 'f';
	if (j == m - 1) return true;
	for (int k = j + 1; k < m; k++)
		a[k] = 't';
	return true;
}

int main()
{
	int n, m;
	char* b;
	n = 2, m = 10;
	b = new char[m + 1];
	for (int i = 0; i < m; i++)
		b[i] = 't';
	b[m] = '\0';
	setlocale(LC_ALL, "rus");
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	string buff;
	if (fin.is_open()) {
		getline(fin, buff);
		int N = stoi(buff);
		map<string, int> mp;
		while (getline(fin, buff)) {
			int num = buff[10] - '0';
			string anss = buff.substr(0, 10);
			mp[anss] = num;
		}
		vector<string> possible;
		bool isPossible = true;
		map <string, int> ::iterator it = mp.begin();
		do {
			for (int i = 0; it != mp.end(); it++, i++) {
				if (!matcher(b, it->first, it->second)) {
					isPossible = false;
					break;
				}
			}
			if (isPossible) {
				cout << "FOUND ONE" << endl;
				possible.push_back(b);
			}
			isPossible = true;
			it = mp.begin();
		} while (nextComb(b, n, m));
		cout << "ANSWER:" << endl;
		if (possible.size() == 1)
			fout << "ONE SOLUTION" << endl;
		else fout << "POSSIBLE SOLUTIONS" << endl;
		for (int i = 0; i < possible.size(); i++) {
			fout << possible[i] << endl;
			cout << possible[i] << endl;
		}
	}
	fin.close();
	return 0;
}