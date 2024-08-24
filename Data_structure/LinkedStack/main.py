class Node:
    def __init__(self,elem,link=None):
        self.data = elem
        self.link = link

class LinkedStack:
    def __init__(self):
        self.top = None

    def isEmpty(self):
        return self.top == None

    def clear(self):
        self.top = None

    def push(self, item):
        n = Node(item,self.top)
        self.top = n

    def pop(self):
        if not self.isEmpty():
            n = self.top
            self.top = n.link
            return n.data