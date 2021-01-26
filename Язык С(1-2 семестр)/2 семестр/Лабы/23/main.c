#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>


typedef struct Node Node;


struct Node {
    double value;
    Node* leftChild;
    Node* rightChild;
};


Node* makeNode(double val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = val;
    node->leftChild = node->rightChild = NULL;
    return node;
}


void insert(Node* current, Node* val) {
    if (val->value < current->value) {
        if (current->leftChild == NULL) {
            current->leftChild = val;
            return;
        }
        insert(current->leftChild, val);
    } else {
        if (current->rightChild == NULL) {
            current->rightChild = val;
            return;
        }
        insert(current->rightChild, val);
    }
}


void print(Node* current, int d) {
    if (current->rightChild != NULL) {
        print(current->rightChild, d + 1);
    }
    printf("%*s%lf\n", 4 * d, " ", current->value);
    if (current->leftChild != NULL) {
        print(current->leftChild, d + 1);
    }
}


void destroy(Node* leaf) {
  if (leaf != NULL) {
      destroy(leaf->leftChild);
      destroy(leaf->rightChild);
      free(leaf);
  }
}


Node* deleteNode(Node* root, double val) {
    if (root == NULL)
        return root;
    
    if (root->value > val) {
        root->leftChild = deleteNode(root->leftChild, val);
        return root;
    }
    if (root->value < val) {
        root->rightChild = deleteNode(root->rightChild, val);
        return root;
    }
    
    if (root->leftChild == NULL) {
        Node* temp = root->rightChild;
        free(root);
        return temp;
    }
    if (root->rightChild == NULL) {
        Node* temp = root->leftChild;
        free(root);
        return temp;
    }
  
    Node* tmpParent = root;
    Node* tmp = root->rightChild;
    while (tmp->leftChild != NULL) {
        tmpParent = tmp;
        tmp = tmp->leftChild;
    }
    if (tmpParent != root)
        tmpParent->leftChild = tmp->rightChild;
    else
        tmpParent->rightChild = tmp->rightChild;

    root->value = tmp->value;
    free(tmp);
    return root;
    
}


int depth(Node* tree) {
    int val = 0;
    if (tree != NULL) {
        int lDepth = depth(tree->leftChild);
        int rDepth = depth(tree->rightChild);
        val =  lDepth + 1 > rDepth + 1 ? lDepth + 1 : rDepth + 1;
    }
    return val;
}


int main() {
    Node* root = NULL;
    int comm;
    printf("Commands:\n\t1. Insert\n\t2. Delete\n\t3. Print\n\t4. Depth\n\t5. Break\n");
    do {
        printf("Enter command: ");
        if (scanf("%i", &comm) != 1)
            getchar();
        double val;
        switch (comm) {
            case 1:
                printf("Enter num: ");
                scanf("%lf", &val);
                if (root == NULL) {
                    root = makeNode(val);
                } else {
                    insert(root, makeNode(val));
                }
                break;
            case 2:
                printf("Enter num: ");
                scanf("%lf", &val);
                root = deleteNode(root, val);
                break;
            case 3:
                if (root != NULL) {
                    printf("\nTree:\n");
                    print(root, 0);
                    printf("\n");
                } else {
                    printf("Empty tree!\n");
                }
                break;
            case 4:
                printf("Depth: %d\n", depth(root));
                break;
            default:
                break;
        }
    } while (comm != 5);
    destroy(root);
    return 0;
}
