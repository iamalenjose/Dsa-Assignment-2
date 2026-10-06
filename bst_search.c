#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

/* Create a new node */
struct Node* createNode(int data)
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

/* Insert a node into BST */
struct Node* insert(struct Node *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }

    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }

    return root;
}

/* Inorder Traversal */
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

/* Preorder Traversal */
void preorder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

/* Postorder Traversal */
void postorder(struct Node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

/* BST Search */
int bstSearch(struct Node *root, int key, int *comparisons)
{
    while (root != NULL)
    {
        (*comparisons)++;

        if (key == root->data)
        {
            return 1;
        }
        else if (key < root->data)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    return 0;
}

/* Linear Search */
int linearSearch(int arr[], int n, int key, int *comparisons)
{
    int i;

    for (i = 0; i < n; i++)
    {
        (*comparisons)++;

        if (arr[i] == key)
        {
            return 1;
        }
    }

    return 0;
}

/* Calculate height of BST */
int height(struct Node *root)
{
    int leftHeight;
    int rightHeight;

    if (root == NULL)
    {
        return -1;
    }

    leftHeight = height(root->left);
    rightHeight = height(root->right);

    if (leftHeight > rightHeight)
    {
        return leftHeight + 1;
    }
    else
    {
        return rightHeight + 1;
    }
}

/* Display search result */
void searchResult(struct Node *root, int arr[], int n, int key)
{
    int bstComparisons = 0;
    int linearComparisons = 0;

    int bstResult;
    int linearResult;

    bstResult = bstSearch(root, key, &bstComparisons);
    linearResult = linearSearch(arr, n, key, &linearComparisons);

    printf("\n----------------------------------------\n");
    printf("Search Key: %d\n", key);
    printf("----------------------------------------\n");

    if (bstResult)
    {
        printf("BST Search    : Found\n");
    }
    else
    {
        printf("BST Search    : Not Found\n");
    }

    printf("BST Comparisons: %d\n", bstComparisons);

    if (linearResult)
    {
        printf("Linear Search : Found\n");
    }
    else
    {
        printf("Linear Search : Not Found\n");
    }

    printf("Linear Comparisons: %d\n", linearComparisons);
}

/* Free memory */
void freeTree(struct Node *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

/* Main function */
int main()
{
    int arr[] = {45, 20, 60, 10, 30, 50, 70, 25, 55};

    int n = sizeof(arr) / sizeof(arr[0]);

    int searchKeys[] = {25, 55, 90};

    int rootHeight;

    struct Node *root = NULL;

    int i;

    /* Build BST */
    for (i = 0; i < n; i++)
    {
        root = insert(root, arr[i]);
    }

    /* Display title */
    printf("========================================\n");
    printf("   BINARY SEARCH TREE ANALYSIS\n");
    printf("========================================\n");

    /* Display input */
    printf("\nISBN Keys:\n");

    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    /* Display traversals */
    printf("\n========================================\n");
    printf("TREE TRAVERSALS\n");
    printf("========================================\n");

    printf("\nInorder Traversal:\n");
    inorder(root);

    printf("\n\nPreorder Traversal:\n");
    preorder(root);

    printf("\n\nPostorder Traversal:\n");
    postorder(root);

    /* Display height */
    rootHeight = height(root);

    printf("\n\n========================================\n");
    printf("TREE INFORMATION\n");
    printf("========================================\n");

    printf("\nNumber of Nodes: %d\n", n);
    printf("Tree Height: %d edges\n", rootHeight);
    printf("Number of Levels: %d\n", rootHeight + 1);

    /* Search operations */
    printf("\n========================================\n");
    printf("SEARCH COMPARISON\n");
    printf("========================================\n");

    for (i = 0; i < 3; i++)
    {
        searchResult(root, arr, n, searchKeys[i]);
    }

    /* Final comparison table */
    printf("\n========================================\n");
    printf("COMPARISON TABLE\n");
    printf("========================================\n");

    printf("\nKey\tBST\tLinear\n");
    printf("-----------------------------\n");

    for (i = 0; i < 3; i++)
    {
        int bstComparisons = 0;
        int linearComparisons = 0;

        bstSearch(root, searchKeys[i], &bstComparisons);
        linearSearch(arr, n, searchKeys[i], &linearComparisons);

        printf("%d\t%d\t%d\n",
               searchKeys[i],
               bstComparisons,
               linearComparisons);
    }

    printf("\n========================================\n");
    printf("COMPLEXITY ANALYSIS\n");
    printf("========================================\n");

    printf("\nBST Search:\n");
    printf("Best Case    : O(1)\n");
    printf("Average Case : O(log n)\n");
    printf("Worst Case   : O(n)\n");
    printf("Space        : O(n)\n");

    printf("\nLinear Search:\n");
    printf("Best Case    : O(1)\n");
    printf("Average Case : O(n)\n");
    printf("Worst Case   : O(n)\n");
    printf("Space        : O(1)\n");

    printf("\n========================================\n");
    printf("CONCLUSION\n");
    printf("========================================\n");

    printf("\nFor the given dataset, BST Search is preferable\n");
    printf("because it requires fewer comparisons than Linear Search.\n");
    printf("A reasonably balanced BST provides efficient searching\n");
    printf("with an average complexity of O(log n).\n");

    /* Free allocated memory */
    freeTree(root);

    return 0;
}