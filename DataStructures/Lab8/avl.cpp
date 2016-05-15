#include <stdio.h>
#include <stdlib.h>
#include <cctype>
#include<iostream>
#include<sstream>
#include<fstream>
#include<algorithm>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// An AVL tree node
struct Node
{
    string key;
    Node *left;
    Node *right;
    int height;
    int count;
};
 
// A utility function to get maximum of two integers
int max(int a, int b);
 
// A utility function to get height of the tree
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
Node* newNode(string key)
{
    Node* node = new Node;
    node->key    = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    node->count  = 1;
    return(node);
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
Node* insert(Node* node, string key)
{
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return(newNode(key));
        
    int comp = key.compare(node->key);
 
    if (comp < 0)
        node->left  = insert(node->left, key);
    else if(comp > 0)
        node->right = insert(node->right, key);
    else {
    	node->count++;
    	return node;
    }
 
    /* 2. Update height of this ancestor node */
    node->height = max(height(node->left), height(node->right)) + 1;
 
    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
void biggest(Node* node, int (&arr) [10], string (&a) [10])
{
    if(node->left) {
        biggest(node->left, arr, a);
    }

    if(node->right) {
        biggest(node->right, arr, a);
    }

    for(int i = 0; i < 10; i++) {
        if(node->count > arr[i]) {
            for (int j = 9; j > i; j--) {
                arr[j] = arr[j - 1];
                a[j] = a[j - 1];
            }

            arr[i] = node->count;
            a[i] = node->key;
            break;
        }
    }
}
 
struct alphabet_only: std::ctype<char> 
{
        alphabet_only(): std::ctype<char>(get_table()) {}

        static std::ctype_base::mask const* get_table()
        {
            static std::vector<std::ctype_base::mask> 
                rc(std::ctype<char>::table_size,std::ctype_base::space);

            std::fill(&rc['A'], &rc['['], std::ctype_base::upper);
            std::fill(&rc['a'], &rc['{'], std::ctype_base::lower);
            return &rc[0];
        }
};

int main(void)
{
    std::ifstream file;
    file.open ("big.txt");
    file.imbue(std::locale(std::locale(), new alphabet_only()));
    Node *root = NULL;
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
 
    std::string word;
    while (file >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        root = insert(root, word);
    }
    
    int biggestArr[10] = {-1};
    string biggestArrs[10];

    biggest(root, biggestArr, biggestArrs);
    
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    for(int i = 0; i < 10; i ++){
        cout << biggestArrs[i] << " - " << biggestArr[i] << endl;
    }
    
    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();

    cout << duration;
}
