#include <iostream>
#include<string>
using namespace std;

const int MAX = 100;

class Node {

    string key;
    int value;
    Node* next;

public:
    Node()
    {
        key = "";
        value = 0;
        next = NULL;
    }

    Node(string key, int value)
    {
        this->key = key;
        this->value = value;
        next = NULL;
    }

    void print()
    {
        cout << "Key's Name: " << key
            << "\nVal: " << value << endl;
    }
    friend class SymbolTable;
};

class SymbolTable {
    Node* head[MAX];

public:
    SymbolTable()
    {
        for (int i = 0; i < MAX; i++)
            head[i] = NULL;
    }

    int hashf(string id); // hash function
    bool add(string id, int val);
    int find(string id);
    bool deleteRecord(string id);

    int& operator[](string id);

};

int SymbolTable::hashf(string id)
{
    int asciiSum = 0;

    for (int i = 0; i < id.length(); i++) {
        asciiSum = asciiSum + id[i];
    }

    return (asciiSum % 100);
}

// Function to insert an identifier
bool SymbolTable::add(string id, int val)
{
    int index = hashf(id);
    Node* p = new Node(id, val);

    if (head[index] == NULL) 
    {
        head[index] = p;
        //cout << "\n" << id << " inserted";

        return true;
    }

    else {
        Node* start = head[index];
        while (start->next != NULL)
            start = start->next;

        start->next = p;
        //cout << "\n" << id << " inserted";

        return true;
    }

    return false;
}

// Function to find an identifier
int SymbolTable::find(string id)
{
    int index = hashf(id);
    Node* start = head[index];

    if (start == NULL)
        return -1;

    while (start != NULL) 
    {

        if (start->key == id) 
        {
            //start->print();
            return start->value;
        }

        start = start->next;
    }
    
    return -1; // not found
}

// Function to delete an identifier
bool SymbolTable::deleteRecord(string id)
{
    int index = hashf(id);
    Node* tmp = head[index];
    Node* par = head[index];

    // no identifier is present at that index
    if (tmp == NULL) {
        return false;
    }
    // only one identifier is present
    if (tmp->key == id && tmp->next == NULL) {
        tmp->next = NULL;
        delete tmp;
        return true;
    }

    while (tmp->key != id && tmp->next != NULL) {
        par = tmp;
        tmp = tmp->next;
    }
    if (tmp->key == id && tmp->next != NULL) {
        par->next = tmp->next;
        tmp->next = NULL;
        delete tmp;
        return true;
    }

    // delete at the end
    else {
        par->next = NULL;
        tmp->next = NULL;
        delete tmp;
        return true;
    }
    return false;
}

//operator overloading
int& SymbolTable::operator[](string id)
{
    int a;
    a = this->find(id);
    return a;
}

int main()
{
    SymbolTable table;
    
    table.add("doll", 7);  // 추가연산
    table.add("house", 4);
    table.add("mouse", 2);
    table.add("lolipop", 10);

    cout << table["doll"] << endl; //value 값 출력
    cout << table["ball"] << endl; // 존재하지 않는 key _ false
    cout << table["mouse"] << endl;

    table.deleteRecord("mouse"); // 삭제연산
    table.deleteRecord("lolipop");

    cout << table["mouse"] << endl; //c++ shell에서는 잘돌아가는데 왜 여기선 안돌아가노

    return 0;
}