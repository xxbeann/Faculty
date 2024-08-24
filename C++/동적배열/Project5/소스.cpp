#include<iostream>
using namespace std;

class dynamicArray
{
private:
    int* m_array;
    int m_size;
    int m_used;
public:
    dynamicArray();
    dynamicArray(int size);
    ~dynamicArray();

    void popBack();
    void pushBack(int data);
    void print();
};

dynamicArray::dynamicArray() : m_size(1), m_used(0)
{
    m_array = new int[m_size];
}

dynamicArray::dynamicArray(int size) : m_size(size), m_used(0)
{
    m_array = new int[m_size];
}

dynamicArray::~dynamicArray()
{
    delete[] m_array;
}

void dynamicArray::pushBack(int data)
{
    if (this->m_used < this->m_size)
    {
        this->m_array[this->m_used] = data;
    }
    //메모리가 있으면
    else
    {
        int* temp = new int[m_size];
        for (int i = 0; i < this->m_used; i++)
            temp[i] = this->m_array[i];

        delete[] this->m_array;
        this->m_size *= 2;
        this->m_array = new int[m_size];

        //this->m_array = temp;
        for (int i = 0; i < this->m_used; i++)
        {
            this->m_array[i] = temp[i];
        }
        delete[] temp;
        this->m_array[this->m_used] = data;
    }

    this->m_used++;
    //메모리가 없으면(더이상 넣을 공간이 없으면 확장)
}

void dynamicArray::popBack()
{
    if (m_used == 0) return;

    m_used--;
    int* temp = new int[m_used];

    for (int i = 0; i < m_used; i++)
        temp[i] = m_array[i];

    delete[] m_array;
    m_array = new int[m_size];

    for (int i = 0; i < m_used; i++)
        temp[i] = m_array[i];

    delete[] temp;
    return;
}

void dynamicArray::print()
{
    for (int i = 0; i < this->m_used; i++)
        printf("%d ", this->m_array[i]);
    printf("\n");
}

int main(void)
{

    return 0; 
}