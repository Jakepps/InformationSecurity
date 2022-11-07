#include <iostream>
#include <vector>
#include <set>
#include <string.h>
#include <string>

using namespace std;

vector<set<int>> firms; //тупа фирмы
vector<set<int>> conflicts; //набор фирм
vector<vector<pair<int, string>>> accessSubHist;// история запросов для субъектов - список из последовательностей запросов каждого субъекта; запрос - индекс объекта + тип запроса
vector<vector<pair<int, string>>> accessObjHist;// история запросов для объектов - список из последовательностей запросов каждого объекта; запрос - индекс субъекта + тип запроса

bool contains(set<int>& s, int elt) 
{
    return (find(s.begin(), s.end(), elt) != s.end());
}

vector<string> split(string line)
{
    vector<string> result = vector<string>();

    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ' ') {
            result.push_back(line.substr(0, i));
            vector<string> tail = split(line.substr(i + 1, line.size() - i - 1));
            result.insert(result.end(), tail.begin(), tail.end());
            break;
        }
    }

    if (result.size() == 0) 
    {
        result.insert(result.begin(), line);
    }

    return result;
}

int getFirm(int forObject) 
{
    for (int i = 0; i < firms.size(); i++) 
    {
        if (contains(firms[i], forObject))
        {
            return i;
        }
    }
    return -1;
}

int getInterestGroup(int forObject) 
{
    int firm = getFirm(forObject);

    for (int i = 0; i < conflicts.size(); i++)
    {
        if (contains(conflicts[i], firm)) 
        {
            return i;
        }
    }

    return -1;
};

void printFirmObjects(int firmIndex)
{
    for (set<int>::iterator i = firms[firmIndex].begin(); i != firms[firmIndex].end(); i++) 
    {
        cout << *i << ", ";
        i++;
    }
    cout << endl;
}

void printReportForSubject(int subjectIndex) 
{
    for (int i = 0; i < accessSubHist[subjectIndex].size(); i++)
    {
        cout << "access " << accessSubHist[subjectIndex][i].second << " with object " << accessSubHist[subjectIndex][i].first << " in firm " << getFirm(accessSubHist[subjectIndex][i].first);
    }
}

void printReportForObject(int objectIndex)
{
    for (int i = 0; i < accessObjHist[objectIndex].size(); i++) 
    {
        cout << "access " << accessObjHist[objectIndex][i].second << " with object " << accessObjHist[objectIndex][i].first << " in firm " << getFirm(accessObjHist[objectIndex][i].first);
    }
}

bool canRead(int subjectIndex, int objectIndex)
{
    int interestGroup = getInterestGroup(objectIndex);
    int objectFirm = getFirm(objectIndex);

    set<int> accessGroups = set<int>();
    set<int> firmGroups = set<int>();

    for (int i = 0; i < accessSubHist[subjectIndex].size(); i++)
    {
        accessGroups.insert(getInterestGroup(accessSubHist[subjectIndex][i].first));
        firmGroups.insert(getFirm(accessSubHist[subjectIndex][i].first));
    }

    return !contains(accessGroups, interestGroup) || contains(firmGroups, objectFirm);
}

bool canWrite(int subjectIndex, int objectIndex)
{
    int objectFirm = getFirm(objectIndex);
    int objectInterest = getInterestGroup(objectIndex);
    bool isReadFromAnoutherFirm = false;

    set<int> readedFirms = set<int>();

    for (int i = 0; i < accessSubHist[subjectIndex].size(); i++) 
    {
        if (accessSubHist[subjectIndex][i].second == "r" &&
            getFirm(accessSubHist[subjectIndex][i].first) != objectFirm &&
            getInterestGroup(accessSubHist[subjectIndex][i].first) == objectInterest)
        {
            isReadFromAnoutherFirm = true;
            break;
        }
    }

    return canRead(subjectIndex, objectIndex) && !isReadFromAnoutherFirm;
}

void read(int subjectIndex, int objectIndex)
{
    if (canRead(subjectIndex, objectIndex)) 
    {
        accessSubHist[subjectIndex].push_back(pair<int, string>(objectIndex, "r"));
        accessObjHist[objectIndex].push_back(pair<int, string>(subjectIndex, "r"));
        cout << "accepted" << endl;
    }
    else 
    {
        cout << "refused" << endl;
    }
}

void write(int subjectIndex, int objectIndex) 
{
    if (canWrite(subjectIndex, objectIndex)) 
    {
        accessSubHist[subjectIndex].push_back(pair<int, string>(objectIndex, "w"));
        accessObjHist[objectIndex].push_back(pair<int, string>(subjectIndex, "w"));
        cout << "accepted" << endl;
    }
    else 
    {
        cout << "refused" << endl;
    }
}

void setUpChinaWall(int objCount, int subjCount, int firmCount, int interCount) 
{
    firms = vector<set<int>>(firmCount, set<int>());
    conflicts = vector<set<int>>(interCount, set<int>());

    accessSubHist = vector<vector<pair<int, string>>>(subjCount);
    accessObjHist = vector<vector<pair<int, string>>>(objCount);
}

void startActions(string command) 
{
    vector<string> words = split(command);

    if (words[0] == "start")
    {
        accessSubHist = vector<vector<pair<int, string>>>(accessSubHist.size());
        accessObjHist = vector<vector<pair<int, string>>>(accessObjHist.size());
    }
    else if (words[0] == "read")
    {
        int subjectIndex = stoi(words[1]);
        int objectIndex = stoi(words[2]);
        read(subjectIndex, objectIndex);
    }
    else if (words[0] == "write")
    {
        int subjectIndex = stoi(words[1]);
        int objectIndex = stoi(words[2]);
        write(subjectIndex, objectIndex);
    }
    else if (words[0] == "report_subject") 
    {
        int subjectIndex = stoi(words[1]);
        printReportForSubject(subjectIndex);
    }
    else if (words[0] == "report_object") 
    {
        int objectIndex = stoi(words[1]);
        printReportForObject(objectIndex);
    }
    else if (words[0] == "brief_case") 
    {
        int firmIndex = stoi(words[1]);
        printFirmObjects(firmIndex);
    }
    else
    {
        cout << "invalid command" << endl;
    }

    cout << endl;
}

int main() {
    //0 - 0 
    //1 - 1, 2, 3
    //2 - 4, 5 
    // 
    //0 - 0, 1
    //1 - 2

    setUpChinaWall(6, 1, 3, 2);
    firms[0].insert(0);
    firms[1].insert(1);
    firms[1].insert(2);
    firms[1].insert(3);
    firms[2].insert(4);
    firms[2].insert(5);

    conflicts[0].insert(0);
    conflicts[0].insert(1);
    conflicts[1].insert(2);

    while (true) 
    {
        string s;
        cin >> s;
        int i, j;
        cin >> i >> j;
        if (s == "read")
        {
            startActions("read " + to_string(i) + ' ' + to_string(j));
        }
        else 
        {
            startActions("write " + to_string(i) + ' ' + to_string(j));
        }
    }

    return 0;
}