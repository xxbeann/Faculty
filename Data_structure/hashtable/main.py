class DoubleHash:
    def __init__(self, size):
        self.M = size
        self.a = [None] * size  # key 저장하는 리스트
        self.d = [None] * size  # data 저장하는 리스트

    def h_hash(self, key):
        return key % self.M

    def d_hash2(self, key):
        return  7 - (key % 7)

    def put(self, key, item):
        h_index = self.h_hash(key)
        j = 0

        count = 0
        while True:
            index = (h_index + j * self.d_hash2(key)) % self.M

            if self.a[index] == None:
                self.a[index] = key
                self.d[index] = item
                return

            if self.a[index] == key:
                self.d[index] = item
            j += 1

            count += 1
            if count == self.M * 10:
                return

    def get(self, key):
        h_index = self.h_hash(key)
        j = 0

        count = 0

        while True:
            index = (h_index + j * self.d_hash2(key)) % self.M

            if self.a[index] == key:
                return

            j += 1

            count += 1
            if count == self.M * 10:
                return

    def print_table(self):  # 해시테이블 출력

        print('\n')
        for i in range(self.M):
            print(f'{i}', " ", end="")
        print('\n')

        for i in range(self.M):
            print(f'{self.a[i]}', " ", end="")
        print('\n')

a = DoubleHash(11)

a.put(1, 44)
a.put(2, 13)
a.put(3, 88)
a.put(4, 23)
a.put(5, 94)
a.put(6, 11)
a.put(7, 39)
a.put(8, 20)
a.put(9, 16)
a.put(10,5)

a.print_table()