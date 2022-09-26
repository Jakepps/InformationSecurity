#include <iostream>
#include <string>
using namespace std;

string rle(string code)
{
	int count = 0;
	string encoded = "";
	for (int i = 0; i < code.length() - 1; i++) {
		count = 1;
		while (code[i] == code[i + 1]) {
			count++;
			i++;
		}
		if (count > 1)
			encoded += to_string(count) + code[i];
		else
			encoded += code[i];
	}
	if (code[code.length() - 1] != encoded[encoded.length() - 1])
		encoded += code[code.length() - 1];
	return encoded;
}

int main()
{
	cout << rle("AAAVVVCSSSLL");

}
