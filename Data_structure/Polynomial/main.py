class Polynomial:

    def __init__(self,a = []): #생성
        self.a = a
        self.coef = []
        if len(self.a) != 0:
            self.max_degree = len(self.a) -1
            for i in range(0, len(self.a), 1):
                k = self.a[i]
                self.coef.append(k)
        else:
            self.max_degree = int(input("다항식의 최고차항을 입력하세요: "))
            for i in range(self.max_degree, -1, -1):
                a = int(input("x^ %d 의 계수 : " % (i)))
                self.coef.append(a)
            self.coef.reverse()

    def add(self, a): #덧셈
        z = []
        if self.max_degree > a.degree():
            for i in range(0, a.degree() + 1, 1):
                k = self.coef[i] + a.coef[i]
                z.append(k)
            for i in range(a.degree() + 1, self.max_degree +1, 1):
                l = self.coef[i]
                z.append(l)

        return z

    def inverse(self): #덧셈역수
        for i in range(0,self.max_degree +1,1):
            self.coef[i] = - self.coef[i]
        return self.coef

    def degree(self): #차수
        a = self.max_degree
        return a

    def display(self, a=''): #출력
        print(a, end='')
        for i in range(self.max_degree, 0, -1):
            print("%d X^%d +" %(self.coef[i], i), end='')
        print("%d" %(self.coef[0]))

    def evaluate(self, a): #수식연산
        val = 0
        for i in range(0, self.max_degree + 1, 1):
            val += pow(a, i) * self.coef[i]
        return val

a = Polynomial()
b = Polynomial()
c = a.add(b)
d = Polynomial(c)
a.display("A(x) = ")
b.display("B(x) = ")
d.display("C(x) = ")
print("C(2) = ", d.evaluate(2))