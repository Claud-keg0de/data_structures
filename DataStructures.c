#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return root;
}

void createBST(Node** root, int arr[], int size) {
    *root = NULL;
    for (int i = 0; i < size; i++) {
        *root = insertNode(*root, arr[i]);
    }
}

int getHeight(Node* root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int getLevel(Node* root, int data, int level) {
    if (root == NULL) {
        return -1;
    }

    if (root->data == data) {
        return level;
    }

    int leftLevel = getLevel(root->left, data, level + 1);
    if (leftLevel != -1) {
        return leftLevel;
    }

    int rightLevel = getLevel(root->right, data, level + 1);
    return rightLevel;
}

Node* minValueNode(Node* root) {
    Node* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node* deleteNode(Node* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int main() {
    Node* root = NULL;
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int size = sizeof(arr) / sizeof(arr[0]);

    // i) Create the BST
    createBST(&root, arr, size);

    // ii) Delete a node from the BST
    int dataToDelete = 25;
    root = deleteNode(root, dataToDelete);

    // iii) Print the height of the BST
    int height = getHeight(root);
    printf("Height of the BST: %d\n", height);

    // iv) Print the level and height of any node in the BST
    int nodeData = 40;
    int level = getLevel(root, nodeData, 1);
    if (level != -1) {
        printf("Node %d is at level %d\n", nodeData, level);
        printf("Height of node %d: %d\n", nodeData, getHeight(root) - level + 1);
    } else {
        printf("Node %d not found in the BST\n", nodeData);
    }

    return 0;
}