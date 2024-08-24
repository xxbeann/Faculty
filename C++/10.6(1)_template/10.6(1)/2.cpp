#include<algorithm>
#include <iostream>
#include <math.h>
#include <stack>
#include <string>
using namespace std;

template <typename T>
struct Node {

    T data;
    Node* left;
    Node* right;

public:

    void inorder(Node* r)
    {
        if (r == NULL) {
            return;
        }
        inorder(r->left);
        cout << r->data << " ";
        inorder(r->right);
    }

    int containsNode(Node* r, T d)
    {
        if (r == NULL) {
            return 0;
        }
        int x = r->data == d ? 1 : 0;
        return x | containsNode(r->left, d) | containsNode(r->right, d);
    }

    Node* minValueNode(Node* r)
    {
        Node* current = r;
        while (current && current->left != NULL)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* r, T d)
    {
        if (r == NULL)
            return r;

        if (d < r->data)
        {
            r->left = deleteNode(r->left, d);
        }
        else if (d > r->data)
        {
            r->right = deleteNode(r->right, d);
        }
        else
        {
            if (r->left == NULL && r->right == NULL)
                return NULL;
            else if (r->left == NULL)
            {
                Node* temp = r->right;
                free(r);
                return temp;
            }
            else if (r->right == NULL)
            {
                Node* temp = r->left;
                free(r);
                return temp;
            }

            Node* temp = minValueNode(r->right);
            r->data = temp->data;
            r->right = deleteNode(r->right, temp->data);
        }
        return r;
    }

    Node* insert(Node* r, T d)
    {
        if (r == NULL) {
            Node<T>* tmp = new Node<T>;
            tmp->data = d;
            tmp->left = tmp->right = NULL;
            return tmp;
        }

        if (d < r->data) {
            r->left = insert(r->left, d);
            return r;
        }

        else if (d > r->data) {
            r->right = insert(r->right, d);
            return r;
        }
        else
            return r;
    }
};

template <typename T>
class Set {

    Node<T>* root;
    int size;

public:

    Set()
    {
        root = NULL;
        size = 0;
    }

    Set(const Set& s)
    {
        root = s.root;
        size = s.size;
    }

    void add(const T data)
    {
        if (!root->containsNode(root, data)) 
        {
            root = root->insert(root, data);
            size++;
        }
    }

    void deletion(const T data)
    {
        if (root->containsNode(root, data))
        {
            root = root->deleteNode(root, data);
        }
    }

    Set unionSet(Set& s)
    {
        Set<T> res;

        if (root == NULL)
            return res;

        if (s.root == NULL)
            return *this;

        stack<Node<T>*> nodeStack;
        nodeStack.push(root);

        while (!nodeStack.empty()) {
            Node<T>* node;
            node = nodeStack.top();
            nodeStack.pop();

            res.add(node->data);

            if (node->right)
                nodeStack.push(node->right);
            if (node->left)
                nodeStack.push(node->left);
        }

        stack<Node<T>*> nodeStack1;
        nodeStack1.push(s.root);

        while (!nodeStack1.empty()) {
            Node<T>* node;
            node = nodeStack1.top();
            nodeStack1.pop();

            res.add(node->data);

            if (node->right)
                nodeStack1.push(node->right);
            if (node->left)
                nodeStack1.push(node->left);
        }

        return res;
    }

    Set intersectionSet(Set& s)
    {
        Set<T> res;
        stack<Node<T>*> nodeStack;
        nodeStack.push(root);

        while (!nodeStack.empty()) {
            Node<T>* node;
            node = nodeStack.top();
            nodeStack.pop();
            if (s.contains(node->data)) {
                res.add(node->data);
            }
            if (node->right)
                nodeStack.push(node->right);
            if (node->left)
                nodeStack.push(node->left);
        }
        return res;
    }

    bool contains(T data)
    {
        return root->containsNode(root, data) ? true : false;
    }

    void displaySet()
    {
        cout << "{ ";
        root->inorder(root);
        cout << "}" << endl;
    }

    int getSize()
    {
        return size;
    }

    bool operator+(T data)
    {
        this->add(data);
        return true;
    }

    Set operator|(Set& s)
    {
        return this->unionSet(s);  
    }

    Set operator&(Set& s)
    {
        return this->intersectionSet(s);
    }

    bool operator-(T data)
    {
        this->deletion(data);
        return true;
    }
    
    bool operator==(Set& s)
    {
        if (s.getSize() != size) {
            return false;
        }
        stack<Node<T>*> nodeStack;
        nodeStack.push(this->root);

        while (!nodeStack.empty()) {
            Node<T>* node;
            node = nodeStack.top();
            nodeStack.pop();
            if (!s.contains(node->data)) {
                return false;
            }
            if (node->right)
                nodeStack.push(node->right);
            if (node->left)
                nodeStack.push(node->left);
        }
        return true;

    }

};

int main(void)
{   
    Set<int> A; // 집합 A 생성
    A.add(1);
    A.add(2);
    A.add(3); 
    A.add(3); //중복 포함 X
    A + 4; // + operator overloading
    A.displaySet();

    Set<int> B; // 집합 B 생성
    B.add(3);
    B.add(4);
    B.add(5);

    Set<int> C = A | B; // | operator overloading : union set
    C.displaySet();

    Set<int> D = A & B; // & operator overloading : intersection set
    D.displaySet();

    Set<int> E;
    E.add(3);
    E.add(4);

    cout << (E == D) << endl; // == operator overloading : isSame -> true

    E - 3; // - operator overloading : deletion
    E.displaySet();
  
	return 0;
}