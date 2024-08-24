#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

template <typename T>
class random_list
{
private:
    T* m_array;
    int m_size;
    int m_used;
public:
    random_list();
    random_list(int size);
    ~random_list();

    void add(T data);
    void select();
    void print();
    void used();
};
template <typename T>
random_list<T>::random_list() : m_size(1), m_used(0)
{
    m_array = new T[m_size];
}
template <typename T>
random_list<T>::random_list(int size) : m_size(size), m_used(0)
{
    m_array = new int[m_size];
}
template <typename T>
random_list<T>::~random_list()
{
    delete[] m_array;
}
template <typename T>
void random_list<T>::add(T data)
{
    if (this->m_used < this->m_size)
    {
        this->m_array[this->m_used] = data;
    }
    //메모리가 있으면
    else
    {
        T* temp = new T[m_size];
        for (int i = 0; i < this->m_used; i++)
            temp[i] = this->m_array[i];

        delete[] this->m_array;
        this->m_size *= 2;
        this->m_array = new T[m_size];

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
template <typename T>
void random_list<T>::select()
{
    srand((size_t)time(NULL));
    int n = rand() % this->m_used;
    cout << this->m_array[n] << endl;
}
template <typename T>
void random_list<T>::used()
{
    cout << this->m_used << endl;
}
template <typename T>
void random_list<T>::print()
{
    for (int i = 0; i < this->m_used; i++)
        cout << this->m_array[i] << " ";
    cout << '\n';
    
}

int main(void)
{
    random_list<int> d1;
    d1.add(10);
    d1.add(20);
    d1.add(30);
    d1.add(40);
    d1.print();
    d1.used();
    d1.select();
    cout << endl;

    random_list<double> d2;
    d2.add(1.7);
    d2.add(3.9);
    d2.add(4.3);
    d2.add(42.9);
    d2.print();
    d2.used();
    d2.select();
    cout << endl;

    random_list<char> d3;
    d3.add('a');
    d3.add('b');
    d3.add('c');
    d3.add('d');
    d3.print();
    d3.used();
    d3.select();

    return 0;
}