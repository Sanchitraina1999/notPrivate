// * @Description:  Create inorder threaded binary tree and perform inorder, preorder traversal.


#include <iostream>
using namespace std;

class node
{
    int data;
    bool leftThread, rightThread;
    node *left, *right;

public:
    node()
    {
        data = 0;
        leftThread = rightThread = false; //false if links.....true if threads
        left = right = NULL;
    }
    friend class tbt;
};

class tbt
{
    node *root;

public:
    tbt()
    {
        root = NULL;
        cout << "\nEmpty tree created\n\n";
    }
    void mainmenu();
    void create();
    void inorderTraversal(node *root);
    void preorderTraversal(node *root);
    node *returnroot();
};

void tbt::mainmenu()
{
    cout << "\n1. Create Tree";
    cout << "\n2. Inorder Traversal";
    cout << "\n3. Preorder Traversal";
}

void tbt::create()
{
_addMore:
    node *ntba = new node(); //ntba for node to be added
    cout << "\nEnter the data to be added to TBT : ";
    cin >> ntba->data;
    if (!root)
    {
        root = ntba;
    }
    else
    {
        node *temp = root;
        bool done = false;
        do
        {
            cout << "Do you want to insert " << ntba->data << " to left or to right of " << temp->data << " ?: [l]/[r]";
            char ch;
            cin >> ch;
            if (ch == 'l')
            {
                if (temp->left == NULL || temp->leftThread == true)
                {
                    ntba->left = temp->left;
                    ntba->right = temp;
                    ntba->rightThread = true;
                    if (temp->leftThread)
                    {
                        temp->leftThread = false;
                        ntba->leftThread = true;
                    }
                    temp->left = ntba;
                    done = true;
                }
                else
                    temp = temp->left;
            }
            else
            {
                if (temp->right == NULL || temp->rightThread == true)
                {
                    ntba->right = temp->right;
                    ntba->left = temp;
                    ntba->leftThread = true;
                    if (temp->rightThread)
                    {
                        temp->rightThread = false;
                        ntba->rightThread = true;
                    }
                    temp->right = ntba;
                    done = true;
                }
                else
                    temp = temp->right;
            }
        } while (!done);
    }
    cout << "\nDo you want to add more nodes to the tree: (y/n) ";
    char yn;
    cin >> yn;
    if (yn == 'y')
        goto _addMore;
}

void tbt::inorderTraversal(node *root)
{
    if (!root)
    {
        cout << "Tree is empty\n";
        return;
    }
    if (root->left == NULL && root->right == NULL)
    {
        cout << root->data << "\t";
        return;
    }
    while (root->left != NULL)
        root = root->left;
    while (root->right != NULL)
    {
        cout << root->data << "\t";
        if (root->rightThread)
        {
            root = root->right;
            if (root->right == NULL) //last node condition
                cout << root->data << "\t";
        }
        else
        {
            root = root->right;
            if (root->right == NULL) //last node condition
                cout << root->data << "\t";
            while (root->leftThread == false) //jbb b root->leftThread true hojayega(last left node condition) ..while breaks
                root = root->left;
        }
    }
}

void tbt::preorderTraversal(node *root)
{
    if (root == NULL)
    {
        cout << "Tree is Empty" << endl;
        return;
    }
    cout << root->data << "\t";
    while (root->left != NULL)
    {
        root = root->left;
        cout << root->data << "\t";
    }
    while (root->right != NULL)
    {
        if (root->rightThread)
        {
            root = root->right;
        }
        else
        {
            root = root->right;
            while (root->leftThread == false)
            {
                cout << root->data << "\t";
                root = root->left;
            }
            cout << root->data << "\t";
        }
    }
}

node *tbt::returnroot()
{
    return root;
}

int main()
{
    tbt t;
up:
    t.mainmenu();
    int choice;
    char continu = 'y';

    cin >> choice;
    switch (choice)
    {
    case 1:
        t.create();
        break;
    case 2:
        cout << "Inorder Traversal: ";
        t.inorderTraversal(t.returnroot());
        break;
    case 3:
        cout << "Preorder Traversal: ";
        t.preorderTraversal(t.returnroot());
        break;
    }
    cout << "\nDo you to continue (y/n) : ";
    cin >> continu;
    if (continu == 'y')
        goto up;
    return 0;
}