#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
	string name;
	int price;
public:
	Product (); //생성자
	Product(string n, int p); // 생성자
	~Product(); //소멸자
	string getname(); //접근자
	void setname(string n); //설정자
	int getprice(); //접근자
	void setprice(int p); //설정자
	int getPrice();
	void print(); // 물건의 가격과 이름 출력
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
	cout << "이름: "<< this->getname() <<", 가격: " << this->getprice() << endl;
}

class DiscountProduct : public Product {
private:
	int discount;
public:
	DiscountProduct(string n = "", int p = 0, int d = 0); // 생성자_매개변수가 없을 때_외부에서 정의 안하고 안에서
	//DiscountProduct(string n = "", int p = 0, int d = 0) : Product(n, p), discount(d) {} // 생성자_한번에
	~DiscountProduct(); //소멸자
	int getdiscount(); // 접근자
	void setdiscount(int d); // 설정자
	int getPrice();
	void print();
};
DiscountProduct::DiscountProduct(string n, int p , int d):Product(n,p), discount(d){} //생성자_매개변수가 있을 때
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
	cout << "이름: " << this->getname() << ", 가격: " << this->getPrice() << endl;
}

int main(void)
{
	Product* p1 = new Product("toothbrush", 3000);
	Product* p2 = new DiscountProduct("toothbrush", 3000, 15);
	cout << p1->getPrice() << endl;
	cout << p2->getPrice() << endl;
	//부모 클래스의 getPrice()가 반환된다.

	return 0;
}