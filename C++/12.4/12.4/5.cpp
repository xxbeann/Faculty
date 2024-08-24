#include<iostream>
#include<cstdlib>
using namespace std;

class random_list
{
private:
    int* m_array;
    int m_size;
    int m_used;
public:
    random_list();
    random_list(int size);
    ~random_list();

    void add(int data);
    void select();
    void print();
    void used();
};

random_list::random_list() : m_size(1), m_used(0)
{
    m_array = new int[m_size];
}

random_list::random_list(int size) : m_size(size), m_used(0)
{
    m_array = new int[m_size];
}

random_list::~random_list()
{
    delete[] m_array;
}

void random_list::add(int data)
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

void random_list::select()
{
    int n = rand() % this->m_used;
    cout << this->m_array[n];
}

void random_list::used()
{
    cout << this->m_used << endl;
}

void random_list::print()
{
    for (int i = 0; i < this->m_used; i++)
        printf("%d ", this->m_array[i]);
    printf("\n");
}

int main(void)
{
    random_list d1(4);
    d1.add(10);
    d1.add(20);
    d1.add(30);
    d1.add(40);
    d1.print();
    d1.used();
    d1.select();
    return 0;
}