#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
	string name;
	int price;
public:
	Product (); //������
	Product(string n, int p); // ������
	~Product(); //�Ҹ���
	string getname(); //������
	void setname(string n); //������
	int getprice(); //������
	void setprice(int p); //������
	int getPrice();
	void print(); // ������ ���ݰ� �̸� ���
};

Product::Product() :name(""), price(0) {}
Product::Product(string n, int p)
{
	name = n;
	price = p;
}
Product::~Product() {}
string Product::getname()
{
	return name;
}
void Product::setname(string n)
{
	name = n;
}
int Product::getprice()
{
	return price;
}
void Product::setprice(int p)
{
	price = p;
}
int Product::getPrice()
{
	return this->getprice();
}
void Product::print()
{
	cout << "�̸�: "<< this->getname() <<", ����: " << this->getprice() << endl;
}

class DiscountProduct : public Product {
private:
	int discount;
public:
	DiscountProduct(string n = "", int p = 0, int d = 0); // ������_�Ű������� ���� ��_�ܺο��� ���� ���ϰ� �ȿ���
	//DiscountProduct(string n = "", int p = 0, int d = 0) : Product(n, p), discount(d) {} // ������_�ѹ���
	~DiscountProduct(); //�Ҹ���
	int getdiscount(); // ������
	void setdiscount(int d); // ������
	int getPrice();
	void print();
};
DiscountProduct::DiscountProduct(string n, int p , int d):Product(n,p), discount(d){} //������_�Ű������� ���� ��
DiscountProduct::~DiscountProduct() {}
int DiscountProduct::getdiscount()
{
	return discount;
}
void DiscountProduct::setdiscount(int d)
{
	discount = d;
}
int DiscountProduct::getPrice()
{
	int tmp = this->getprice();
	tmp -= tmp * this->discount / 100;
	return tmp;
}
void DiscountProduct::print()
{
	cout << "�̸�: " << this->getname() << ", ����: " << this->getPrice() << endl;
}

int main(void)
{
	Product* p1 = new Product("toothbrush", 3000);
	Product* p2 = new DiscountProduct("toothbrush", 3000, 15);
	cout << p1->getPrice() << endl;
	cout << p2->getPrice() << endl;
	//�θ� Ŭ������ getPrice()�� ��ȯ�ȴ�.

	return 0;
}