#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <chrono>

// BST
using namespace std;
using namespace std::chrono;

struct Element
{
    string key;
    int value;
};

struct Node
{
    Element elem;
    Node *parent;
    Node *left;
    Node *right;
};

Node *createNode(Element elem,Node * PAR=NULL)
{
    Node *newEl = new Node;
    newEl->elem.key=elem.key;
    newEl->elem.value = 1;
    newEl->left = NULL;
    newEl->right = NULL;
    newEl->parent=PAR;
    return newEl;
}

// Binary search tree
struct BST
{
    Node *root;
};

void init(BST & tree)
{
    tree.root=NULL;
}

bool insertElem(Node *NODE, Element elem)
{
    int comp = elem.key.compare(NODE->elem.key);

    if(comp > 0) {
        if(NODE->right)
            return insertElem(NODE->right,elem);
        
        NODE->right = createNode(elem,NODE->right);
        NODE->right->parent=NODE;
        
        return true;
    } else if(comp < 0) {
        if(NODE->left)
            return insertElem(NODE->left,elem);
        
        NODE->left = createNode(elem,NODE->left);
        NODE->left->parent=NODE;
       
        return true;
    }

    // Key equal. Just increase count
    NODE->elem.value++;

    return false;
}

bool insertElem(BST & tree, Element elem)
{
    if(tree.root)
        return insertElem(tree.root,elem);

    tree.root=createNode(elem);
    return true;
}
//INORDER
void showInorder(Node * NODE)
{
    if(NODE->left)
        showInorder(NODE->left);
    cout<<NODE->elem.key<<'('<<NODE->elem.value<<"),"<<endl;
    if(NODE->right)
        showInorder(NODE->right);
}

void showInorder(BST & tree)
{
    if(tree.root==NULL)
    {
        cout<<endl;
        return;
    }
    showInorder(tree.root);
    cout<<endl;
}

void biggest(Node *node, int (&arr) [10], string (&a) [10])
{
    if(node->left) {
        biggest(node->left, arr, a);
    }

    if(node->right) {
        biggest(node->right, arr, a);
    }

    for(int i = 0; i < 10; i++) {
        if(node->elem.value > arr[i]) {
            for (int j = 9; j > i; j--) {
                arr[j] = arr[j - 1];
                a[j] = a[j - 1];
            }

            arr[i] = node->elem.value;
            a[i] = node->elem.key;
            break;
        }
    }
}

//CLEAR
void clear(Node *NODE)
{
    if(NODE->left)
        clear(NODE->left);
    if(NODE->right)
        clear(NODE->right);
    delete NODE;
}

void clear(BST & tree)
{
    if(tree.root)
        clear(tree.root);
    tree.root=NULL;
}

void showBool(bool val)
{
    if(val)
        cout << "true" << endl;
    else
        cout << "false" << endl;
}

bool isCommand(const string command,const char *mnemonic)
{
    return command==mnemonic;
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

int main()
{
    ifstream file;
    file.open ("big.txt");
    file.imbue(std::locale(std::locale(), new alphabet_only()));
    BST tree;
    
    init(tree);
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    std::string word;
    while (file >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        Element elem;
        elem.key = word;
        elem.value = 1;

        insertElem(tree, elem);
    }

    int biggestArr[10] = {-1};
    string biggestArrs[10];

    biggest(tree.root, biggestArr, biggestArrs);
    
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    for(int i = 0; i < 10; i ++){
        cout << biggestArrs[i] << " - " << biggestArr[i] << endl;
    }
    
    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();

    cout << duration;

    clear(tree);

    return 0;
}
