#include <iostream>
#include <string>
#include <bitset>
using namespace std;

unsigned int grayencode(unsigned int g)
{
    return g ^ (g >> 1);
}
void toBinary(unsigned int n)
{
    if (n / 2 != 0) 
    {
        toBinary(n / 2);
    }
    cout << n % 2;
}
int main()
{
    int n = 4;
    //cin >> n;
    for (int i = 0; i <= n; i++)
    {   
        int g1 = grayencode(i);
        toBinary(g1);
    }
    //cout << endl<< grayencode(n) << endl;
}
