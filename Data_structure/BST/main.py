class Node: #검색 알고리즘에 필요한 기본클래스
    def __init__(self, val):
        self.val = val
        self.leftChild = None
        self.rightChild = None

class BST:
    def __init__(self): #Create
        self.root = None

    def __add__(self, a):
        c = BST()
        c = self.union(a)

        return c

    def setRoot(self, val):
        self.root = Node(val)

    def add(self, val): #Add
        if (self.root is None):
            self.setRoot(val)
        else:
            self.insertNode(self.root, val)

    def insertNode(self, currentNode, val):
        if (val < currentNode.val):
            if (currentNode.leftChild != None):
                self.insertNode(currentNode.leftChild, val)
            else:
                currentNode.leftChild = Node(val)
        elif (val > currentNode.val):
            if (currentNode.rightChild != None):
                self.insertNode(currentNode.rightChild, val)
            else:
                currentNode.rightChild = Node(val)
        else:
            pass

    def search(self, val): #Search
        return self.findNode(self.root, val)

    def findNode(self, currentNode, val):
        if (currentNode is None):
            return False
        elif (val == currentNode.val):
            return True
        elif (val < currentNode.val):
            return self.findNode(currentNode.leftChild, val)
        else:
            return self.findNode(currentNode.rightChild, val)

    def delete(self, key): #Delete
        self.root, deleted = self._delete_value(self.root, key)
        return deleted

    def _delete_value(self, node, key):
        if node is None:
            return node, False

        deleted = False
        if key == node.val:
            deleted = True
            if node.leftChild and node.rightChild:
                # replace the node to the leftmost of node.right
                parent, child = node, node.rightChild
                while child.leftChild is not None:
                    parent, child = child, child.leftChild
                child.leftChild = node.leftChild
                if parent != node:
                    parent.leftChild = child.rightChild
                    child.rightChild = node.rightChild
                node = child
            elif node.leftChild or node.rightChild:
                node = node.leftChild or node.rightChild
            else:
                node = None
        elif key < node.val:
            node.leftChild, deleted = self._delete_value(node.leftChild, key)
        else:
            node.rightChild, deleted = self._delete_value(node.rightChild, key)
        return node, deleted

    def union(self, a): #Union
        c = BST()
        list = a.traverse()
        list1 = self.traverse()
        for i in range(len(list1)):
            c.add(list1[i])
        for i in range(len(list)-1):
            if (self.search(list[i]) == True):
                pass
            elif (self.search(list[i]) == False):
                c.add(list[i])

        return c

    def intersection(self, a): #Intersection
        c = BST()
        list1 = self.traverse()
        list2 = a.traverse()
        result = []
        if len(list1) >= len(list2):
            tmp1 = list1
            tmp2 = list2
        else:
            tmp1 = list2
            tmp2 = list1
        for i in tmp1:
            if i in tmp2:
                result.append(i)
            else: pass
        for i in range(len(result)):
            c.add(result[i])

        return c

    def traverse(self): #중위순회
        return self.traverseNode(self.root)

    def traverseNode(self, currentNode):
        result = []
        if (currentNode.leftChild is not None):
            result.extend(self.traverseNode(currentNode.leftChild))
        if (currentNode is not None):
            result.extend([currentNode.val])
        if (currentNode.rightChild is not None):
            result.extend(self.traverseNode(currentNode.rightChild))
        return result
'''
a = BST() #Create

a.add(2) #Add
a.add(-6)
a.add(14)
a.add(3)
a.add(-1)
a.add(2)
a.add(5)

print(a.traverse()) #Delete
a.delete(-6)
print(a.traverse())
a.delete(5)
print(a.traverse())
a.delete(5)
print(a.delete(5))
'''

a = BST() #Create
b = BST()

a.add(2) #Add
a.add(-6)
a.add(14)
a.add(3)
a.add(-1)
a.add(2)
a.add(5)

b.add(14)
b.add(-3)
b.add(-5)
b.add(9)
b.add(5)
b.add(9)

c = a.union(b) #Union
d = a.intersection(b) #Intersection
e = a + b

print(a.search(-6)) #Search
print(a.search(17))
print(b.search(14))
print(b.search(10))

print(a.traverse()) #Set_A
print(b.traverse()) #Set_B
print(c.traverse()) #Union
print(d.traverse()) #Intersection
print(e.traverse()) #Operator overloading

