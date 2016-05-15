#include<iostream>
#include <string>
#include <sstream>

// BST

using namespace std;


struct Element
{
    int key;
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
    newEl->elem.value=elem.value;
    newEl->left=NULL;
    newEl->right=NULL;
    newEl->parent=PAR;//SOMETHING IS BROKEN HERE AND IDK WHY
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
    if(elem.key > NODE->elem.key)
    {
        if(NODE->right)
            return insertElem(NODE->right,elem);
        NODE->right=createNode(elem,NODE->right);
        NODE->right->parent=NODE;
        return true;
    }
    if(elem.key < NODE->elem.key)
    {
        if(NODE->left)
            return insertElem(NODE->left,elem);
        NODE->left=createNode(elem,NODE->left);
        NODE->left->parent=NODE;
        return true;
    }
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
    cout<<NODE->elem.key<<'('<<NODE->elem.value<<"),";
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
//PREORDER
void showPreorder(Node * NODE)
{
    if(NODE==NULL)
        return;
    cout<<NODE->elem.key<<'('<<NODE->elem.value<<"),";
    showPreorder(NODE->left);
    showPreorder(NODE->right);
}

void showPreorder(BST & tree)
{
    if(tree.root==NULL)
    {
        cout<<endl;
        return;
    }
    showPreorder(tree.root);
    cout<<endl;
}
//POSTORDER
void showPostorder(Node * NODE)
{
    if(NODE->left)
        showPostorder(NODE->left);
    if(NODE->right)
        showPostorder(NODE->right);
    cout<<NODE->elem.key<<'('<<NODE->elem.value<<"),";
}
void showPostorder(BST & tree)
{
    if(tree.root==NULL)
    {
        cout<<endl;
        return;
    }
    showPostorder(tree.root);
    cout<<endl;
}
//FIND KEY
Node *findNode(Node *node,int key)
{
    if(node->elem.key==key)
        return node;
    if(key>node->elem.key)
        if(node->right)
            return findNode(node->right,key);
    if(node->left)
        return findNode(node->left,key);

    return NULL;
}


bool findKey(BST & tree,int key, Element &elem)
{
    if(tree.root)
    {
        Node *found=findNode(tree.root,key);
        if(found!=NULL)
        {
            elem=found->elem;
            return true;
        }
    }
    return false;
}

Node *minimalNode(Node *node)
{
    while(node->left!=NULL)
        node=node->left;
    return node;
}

Node *succesor(Node *node)
{
    if(node->right!=NULL)
        return minimalNode(node->right);
    int key = node->elem.key;
    do
    {
        node=node->parent;
    }
    while(node->elem.key<key);
    return node;
}
bool isRoot(Node *node)
{
    if(node->parent==NULL)
        return true;
    return false;
}
bool removeKey(BST & tree, int key, Element &elem)
{
    if(tree.root==NULL)
        return false;
    Node *todel=findNode(tree.root,key);
    if(todel==NULL)
        return false;
    //NO CHILDREN
    if(todel->left==NULL && todel->right==NULL)
    {
        if(!isRoot(todel))
        {
            if(todel->parent->left==todel)
                todel->parent->left=NULL;
            else
                todel->parent->right=NULL;
        }
        else
            tree.root=NULL;
        elem=todel->elem;
        delete todel;
        return true;
    }
    // TWO CHILDREN
    if(todel->left && todel->right)
    {
        elem=todel->elem;
        Node *succ=succesor(todel);
        Element toSwap;
        removeKey(tree,succ->elem.key,toSwap);
        todel->elem=toSwap;
        return true;
    }
    //ONE CHILD
    if(todel->left || todel->right)
    {
        if(isRoot(todel))
        {
            tree.root = (todel->left ? todel->left : todel->right);
            tree.root->parent=NULL;
        }
        else
        {
            if(todel->parent->right==todel)
            {
                todel->parent->right=(todel->right?todel->right:todel->left);
                todel->parent->right->parent=todel->parent;
            }
            else
            {
                todel->parent->left=(todel->right?todel->right:todel->left);
                todel->parent->left->parent=todel->parent;
            }
        }
        elem=todel->elem;
        delete todel;
        return true;
    }
    return false;
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
//NUMBER OF NODES
void numberOfNodes(Node *NODE,int & number)
{
    if(NODE->left)
        numberOfNodes(NODE->left,number);
    if(NODE->right)
        numberOfNodes(NODE->right,number);
    number++;
}

int numberOfNodes(BST & tree)
{
    if(tree.root==NULL)
        return 0;
    int number=0;
    numberOfNodes(tree.root,number);
    return number;
}
//HEIGHT
int height(Node *node)
{
    if(node==NULL)
        return 0;
    return max(height(node->left),height(node->right))+1;
}

int height(BST & tree)
{
    if(tree.root==NULL)
        return 0;
    return height(tree.root);
}

int functionA(BST & tree)
{
    return -1;
}

int functionB(BST & tree, int key)
{
    return -1;
}

bool functionC(BST & tree, int key, Element &elem)
{
    return false;
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

int main()
{
    string line;
    string command;
    BST *tree=NULL;
    int currentT=0;
    int value;
    cout << "START" << endl;
    while(true)
    {
        getline(cin,line);
        std::stringstream stream(line);
        stream >> command;
        if(line=="" || command[0]=='#')
        {
            // ignore empty line and comment
            continue;
        }

        // copy line on output with exclamation mark
        cout << "!" << line << endl;;

        // change to uppercase
        command[0]=toupper(command[0]);
        command[1]=toupper(command[1]);

        // zero-argument command
        if(isCommand(command,"HA"))
        {
            cout << "END OF EXECUTION" << endl;
            break;
        }

        if(isCommand(command,"SI"))
        {
            showInorder(tree[currentT]);
            continue;
        }

        if(isCommand(command,"SP"))
        {
            showPreorder(tree[currentT]);
            continue;
        }

        if(isCommand(command,"SQ"))
        {
            showPostorder(tree[currentT]);
            continue;
        }

        if(isCommand(command,"CL"))
        {
            clear(tree[currentT]);
            continue;
        }

        if(isCommand(command,"IN"))
        {
            init(tree[currentT]);
            continue;
        }

        if(isCommand(command,"NN"))
        {
            cout << numberOfNodes(tree[currentT]) << endl;
            continue;
        }

        if(isCommand(command,"HE"))
        {
            cout << height(tree[currentT]) << endl;
            continue;
        }

        if(isCommand(command,"FA"))
        {
            cout << functionA(tree[currentT]) << endl;
            continue;
        }

        // read next argument, one int value
        stream >> value;


        if(isCommand(command,"IE"))
        {
            int variable2;
            stream >> variable2;
            Element elem;
            elem.key=value;
            elem.value=variable2;
            showBool(insertElem(tree[currentT],elem));
            continue;
        }

        if(isCommand(command,"FK"))
        {
            Element elem;
            bool ret=findKey(tree[currentT], value, elem);
            if(ret)
                cout << elem.key << '(' << elem.value << ')' << endl;
            else
                cout << "false" << endl;
            continue;
        }

        if(isCommand(command,"RK"))
        {
            Element elem;
            bool ret=removeKey(tree[currentT], value, elem);
            if(ret)
                cout << elem.key << '(' << elem.value << ')' << endl;
            else
                cout << "false" << endl;
            continue;
        }


        if(isCommand(command,"CH"))
        {
            currentT=value;
            continue;
        }

        if(isCommand(command,"GO"))
        {
            tree=new BST[value];
            continue;
        }

        if(isCommand(command,"FB"))
        {
            cout << functionB(tree[currentT],value) << endl;
            continue;
        }

        if(isCommand(command,"FC"))
        {
            Element elem;
            bool ret=functionC(tree[currentT], value, elem);
            if(ret)
                cout << elem.key << '(' << elem.value << ')' << endl;
            else
                cout << "false" << endl;
            continue;
        }

        cout << "wrong argument in test: " << command << endl;

    }
    return 0;
}
