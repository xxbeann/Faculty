#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Red-black tree node structure
typedef struct RBNode {
    long value;
    struct RBNode *left, *right, *parent;
    int color; // 0 for Black, 1 for Red
} RBNode;

// Tree root
RBNode *root = NULL;

// Function prototypes
RBNode *createNode(long value);
void leftRotate(RBNode **root, RBNode *x);
void rightRotate(RBNode **root, RBNode *y);
void rbInsertFixup(RBNode **root, RBNode *z);
void rbInsert(RBNode **root, long value);
RBNode *treeMaximum(RBNode *node);
RBNode *treePredecessor(RBNode *node);
void inorderTraversal(RBNode *node);

// Create a new Red-black tree node
RBNode *createNode(long value) {
    RBNode *node = (RBNode *)malloc(sizeof(RBNode));
    node->value = value;
    node->left = node->right = node->parent = NULL;
    node->color = 1; // New node is Red
    return node;
}

// Left rotate a subtree
void leftRotate(RBNode **root, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Right rotate a subtree
void rightRotate(RBNode **root, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right)
        x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Fixup function for RB tree after insertion
void rbInsertFixup(RBNode **root, RBNode *z) {
    while (z->parent && z->parent->color == 1) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right;
            if (y && y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rightRotate(root, z->parent->parent);
            }
        } else {
            RBNode *y = z->parent->parent->left;
            if (y && y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = 0;
}

// Insert a new value into the RB tree
void rbInsert(RBNode **root, long value) {
    RBNode *z = createNode(value);
    RBNode *y = NULL;
    RBNode *x = *root;

    while (x) {
        y = x;
        if (z->value < x->value)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (!y)
        *root = z;
    else if (z->value < y->value)
        y->left = z;
    else
        y->right = z;

    rbInsertFixup(root, z);
}

// Find the maximum value in a subtree
RBNode *treeMaximum(RBNode *node) {
    while (node->right)
        node = node->right;
    return node;
}

RBNode *treePredecessor(RBNode *node) {
    if (node->left) {
        // If the left subtree exists, find the maximum in the left subtree
        RBNode *current = node->left;
        while (current->right) {
            current = current->right;
        }
        return current;
    } else {
        // If no left subtree, go up the tree until we find a smaller ancestor
        RBNode *current = node;
        RBNode *parent = node->parent;
        while (parent && current == parent->left) {
            current = parent;
            parent = parent->parent;
        }
        return parent;
    }
}


// Inorder traversal of the RB tree
void inorderTraversal(RBNode *node) {
    if (node) {
        inorderTraversal(node->left);
        printf("%ld ", node->value);
        inorderTraversal(node->right);
    }
}

int main() {
    int n;
    printf("Enter n (>= 100000): ");
    scanf("%d", &n);

    int k = (int)(0.0025 * n); // Calculate k as 0.25% of n
    printf("Calculated k = %d\n", k);

    srand(time(NULL));
    long *data = malloc(n * sizeof(long));

    // 데이터 생성 & tree 삽입
    for (int i = 0; i < n; i++) {
        data[i] = rand() % 2147483647;
        rbInsert(&root, data[i]);
    }

    // k개의 최대값 탐색 시간 측정
    clock_t start_kmax = clock();
    printf("Top %d values: ", k);

    RBNode *node = treeMaximum(root);
    for (int i = 0; i < k; i++) {
        if (node) {
            printf("%ld ", node->value);
            node = treePredecessor(node);
        }
    }
    printf("\n");

    clock_t end_kmax = clock();
    double kmax_time = ((double)(end_kmax - start_kmax)) / CLOCKS_PER_SEC;

    // 결과 출력
    printf("K-Max Time: %f seconds\n", kmax_time);

    free(data);
    return 0;
}

