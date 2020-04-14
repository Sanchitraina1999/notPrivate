#include <iostream>
using namespace std;

class node
{
    int data;
    node *left;
    node *right;

public:
    node()
    {
        data = 0;
        left = NULL;
        right = NULL;
    }
    friend class Tree;
    friend class Stack;
    friend void isequal(node *temp1, node *temp2);
};

class Stack
{
    node *(a[20]);
    int top;

public:
    Stack()
    {
        top = -1;
        for (int i = 0; i < 20; i++)
            a[i] = NULL;
    }
    void push(node *);
    void pop();
    node *Top();
    bool empty();
};

void Stack::push(node *temp)
{
    top++;
    a[top] = temp;
}

void Stack::pop()
{
    if (this->empty())
    {
        cout << "The Tree is empty cannot perform pop operation." << endl;
        return;
    }
    top--;
}

node *Stack::Top()
{
    if (this->empty())
    {
        cout << "The Tree is Empty." << endl;
        return NULL;
    }
    return a[top];
}

bool Stack ::empty()
{
    if (top == -1)
        return 1;
    else
        return 0;
}

class Tree
{
    node *root;

public:
    Tree()
    {
        root = NULL;
    }
    void create();
    node *insert(node *, int);
    void Delete();
    node *Del_node(node *);
    void inorder();
    void inorder(node *);
    void postorder();
    void postorder(node *);
    void preorder();
    void preorder(node *);
    void operator=(Tree);
    void display();
    void display_internal(node *);
    void display_external(node *);
    friend class Stack;
    void it_preorder();
    void it_inorder();
    void it_postorder();
    void mirror();
    void mirror(node *);
    friend bool equate(Tree, Tree);
    friend void isequal(node *, node *);
    void copy(node *temp1, node *temp2);
};

void Tree::create()
{
    int num, n = 0;
    cout << "Enter the number of nodes in the tree :: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Data :: ";
        cin >> num;
        root = insert(root, num);
        cout << "Data Inserted." << endl;
    }
}

node *Tree ::insert(node *temp, int num)
{
    if (temp == NULL)
    {
        node *newnode = new node;
        newnode->data = num;
        return newnode;
    }
    char c;
    cout << "Do you want to insert node left or right(l/r)";
    cin >> c;
    if (c == 'l')
        temp->left = insert(temp->left, num);
    else if (c == 'r')
        temp->right = insert(temp->right, num);
    else
        cout << "Wrong Choice" << endl;
    return temp;
}

void Tree::Delete()
{
    if (root == NULL)
    {
        cout << "The Tree is empty." << endl;
        return;
    }
    root = Del_node(root);
}

node *Tree::Del_node(node *temp)
{
    if (temp->left == NULL && temp->right == NULL)
    {
        delete temp;
        return NULL;
    }
    if (temp->left != NULL)
        temp->left = Del_node(temp->left);
    if (temp->right != NULL)
        temp->right = Del_node(temp->right);
    delete temp;
    return NULL;
}

void Tree::inorder()
{
    if (root == NULL)
    {
        cout << "The Tree is Empty." << endl;
        return;
    }
    cout << "The Inorder traversal of Tree :: " << endl;
    inorder(root);
}

void Tree ::inorder(node *temp)
{
    if (temp == NULL)
        return;
    inorder(temp->left);
    cout << temp->data << " ";
    inorder(temp->right);
    return;
}

void Tree::postorder()
{
    if (root == NULL)
    {
        cout << "The Tree is Empty." << endl;
        return;
    }
    cout << "The Postorder Traversal of Tree :: " << endl;
    postorder(root);
}

void Tree::postorder(node *temp)
{
    if (temp == NULL)
        return;
    postorder(temp->left);
    postorder(temp->right);
    cout << temp->data << " ";
    return;
}

void Tree::preorder()
{
    if (root == NULL)
    {
        cout << "The Tree is Empty." << endl;
        return;
    }
    cout << "The Preorder Traversal of the Tree :: " << endl;
    preorder(root);
}

void Tree::preorder(node *temp)
{
    if (temp == NULL)
        return;
    cout << temp->data << " ";
    preorder(temp->left);
    preorder(temp->right);
    return;
}

void Tree::operator=(Tree t1)
{
    root = t1.root;
    copy(root, t1.root);
}

void Tree::copy(node *temp1, node *temp2)
{
    if (temp2 == NULL)
    {
        temp1 = NULL;
    }
    else
    {
        temp1 = new node;
        temp1->data = temp2->data;
        copy(temp1->left, temp2->left);
        copy(temp1->right, temp2->right);
    }
}

void Tree::display()
{
    if (root == NULL)
    {
        cout << "The Tree is empty." << endl;
        return;
    }
    cout << "Internal nodes of the Tree ::" << endl;
    display_internal(root);
    cout << endl;
    cout << endl;
    cout << "External nodes of the Tree ::" << endl;
    display_external(root);
    cout << endl;
}

void Tree::display_internal(node *temp)
{
    if (temp == NULL)
        return;
    display_internal(temp->left);
    if (temp->left != NULL || temp->right != NULL)
        cout << temp->data << " ";
    display_internal(temp->right);
    return;
}

void Tree::display_external(node *temp)
{
    if (temp == NULL)
        return;
    display_external(temp->left);
    if (temp->left == NULL && temp->right == NULL)
        cout << temp->data << " ";
    display_external(temp->right);
    return;
}

void Tree ::it_preorder()
{
    if (root == NULL)
    {
        cout << "The Tree is Empty." << endl;
        return;
    }
    cout << "The Preorder Traversal of Tree using Iteration :: " << endl;
    Stack s;
    node *temp = root;
    temp = root;

    do
    {
        if (temp != NULL)
        {
            cout << temp->data << " ";
            s.push(temp);
            temp = temp->left;
        }
        else
        {
            temp = s.Top();
            s.pop();
            temp = temp->right;
        }
    } while (!s.empty() || temp != NULL);
}

void Tree ::it_inorder()
{
    if (root == NULL)
    {
        cout << "The Tree is Empty." << endl;
        return;
    }
    cout << "The Inorder Traversal using Iterative Method :: " << endl;
    Stack s;
    node *temp = root;
    do
    {
        if (temp != NULL)
        {
            s.push(temp);
            temp = temp->left;
        }
        else
        {
            temp = s.Top();
            s.pop();
            cout << temp->data << " ";
            temp = temp->right;
        }
    } while (temp != NULL || !s.empty());
}

void Tree::it_postorder()
{
    if (this->root == NULL)
    {
        cout << "The Tree is Empty." << endl;
        return;
    }
    Stack s;
    node *temp = root;
    node *prev = NULL;
    cout << "The Postorder traversal of the tree using Iteration :: " << endl;
    do
    {
        if (temp != NULL)
        {
            s.push(temp);
            temp = temp->left;
        }
        else
        {
            temp = s.Top();
            s.pop();
            if (temp->right != NULL)
            {
                if (prev != temp->right)
                {
                    s.push(temp);
                    temp = temp->right;
                }
                else
                {
                    cout << temp->data << " ";
                    prev = temp;
                    temp = NULL;
                }
            }

            else
            {
                cout << temp->data << " ";
                prev = temp;
                temp = NULL;
            }
        }
    } while (!s.empty() || temp != NULL);
    cout << endl;
}

void Tree ::mirror()
{
    if (root == NULL)
    {
        cout << "The Tree is Empty." << endl;
    }
    mirror(root);
}

void swap(node *&a, node *&b)
{
    node *temp;
    temp = a;
    a = b;
    b = temp;
}

void Tree ::mirror(node *temp)
{
    if (temp == NULL)
        return;
    mirror(temp->left);
    mirror(temp->right);
    swap(temp->left, temp->right);
}

int temp_flag = 0;

bool equate(Tree t1, Tree t2)
{
    temp_flag = 1;
    isequal(t1.root, t2.root);
    if (temp_flag == 1)
        return 1;
    else
        return 0;
}

void isequal(node *temp1, node *temp2)
{
    if ((temp1 == NULL && temp2 == NULL) || temp_flag == 0)
        return;
    else if (temp1 == NULL && temp2 != NULL)
    {
        temp_flag = 0;
        return;
    }
    else if (temp1 != NULL && temp2 == NULL)
    {
        temp_flag = 0;
        return;
    }
    else if (temp1->data != temp2->data)
    {
        temp_flag = 0;
        return;
    }
    isequal(temp1->left, temp2->left);
    isequal(temp1->right, temp2->right);
}

int main()
{
    Tree t1, t2, t3, t4, t5;
    int choice = 1;
    char ch = 'y';
    while (choice != 11)
    {
        cout << "1. Create the Tree." << endl;
        cout << "2. Delete the Tree." << endl;
        cout << "3. Inorder Traversal." << endl;
        cout << "4. Preorder Traversal." << endl;
        cout << "5. Postorder Traversal." << endl;
        cout << "6. Iterative Preorder." << endl;
        cout << "7. Iterative Inorder." << endl;
        cout << "8. Iterative Postorder." << endl;
        cout << "9. Display Internal and External Nodes." << endl;
        cout << "10. Mirror image of Tree." << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your Choice :: ";
        cin >> choice;
        if (choice < 1 || choice > 11)
        {
            cout << "You have entered a wrong choice." << endl;
            cout << "Re enter your choice." << endl;
            choice = 1;
            continue;
        }
        cout << endl;
        switch (choice)
        {
        case 1:
            t1.create();
            cout << "\nTree Created." << endl;
            break;

        case 2:
            t1.Delete();
            cout << "Tree Deleted." << endl;
            break;

        case 3:
            t1.inorder();
            break;

        case 4:
            t1.preorder();
            break;

        case 5:
            t1.postorder();
            break;

        case 6:
            t1.it_preorder();
            break;

        case 7:
            t1.it_inorder();
            break;

        case 8:
            t1.it_postorder();
            break;

        case 9:
            t1.display();
            break;

        case 10:
            t1.mirror();
            cout << "The Tree is Mirrored." << endl;
            break;

        case 11:
            cout << "Loop Exit." << endl;
            break;

        default:
            cout << "You have enter a wrong choice." << endl;
            cout << "Please Reenter your choice." << endl;
            break;
        }
        cout << endl;
        ch = 'y';
        cout << "\nDo You want to continue(y/n)." << endl;
        cin >> ch;
        if (ch == 'N' || ch == 'n')
            choice = 10;
        cout << endl;
    }

    t3 = t1;
    cout << "Tree Copied." << endl;
    cout << "The Copied Tree is :: " << endl;
    t3.inorder();
    cout << endl;
    cout << endl;

    cout << "Enter the Details of second Tree." << endl
         << endl;
    choice = 1;
    while (choice != 11)
    {
        cout << "1. Create the Tree." << endl;
        cout << "2. Delete the Tree." << endl;
        cout << "3. Inorder Traversal." << endl;
        cout << "4. Preorder Traversal." << endl;
        cout << "5. Postorder Traversal." << endl;
        cout << "6. Iterative Preorder." << endl;
        cout << "7. Iterative Inorder." << endl;
        cout << "8. Iterative Postorder." << endl;
        cout << "9. Display Internal and External Nodes." << endl;
        cout << "10. Mirror Image of the Tree." << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your Choice :: ";
        cin >> choice;
        if (choice < 1 || choice > 10)
        {
            cout << "You have entered a wrong choice." << endl;
            cout << "Re enter your choice." << endl;
            choice = 1;
            continue;
        }
        cout << endl;
        switch (choice)
        {
        case 1:
            t2.create();
            cout << "\nTree Created." << endl;
            break;

        case 2:
            t2.Delete();
            cout << "Tree Deleted." << endl;
            break;

        case 3:
            t2.inorder();
            break;

        case 4:
            t2.preorder();
            break;

        case 5:
            t2.postorder();
            break;

        case 6:
            t2.it_preorder();
            break;

        case 7:
            t2.it_inorder();
            break;

        case 8:
            t2.it_postorder();
            break;

        case 9:
            t2.display();
            break;

        case 10:
            t2.mirror();
            cout << "The Tree is Mirrored." << endl;
            break;

        case 11:
            cout << "Loop Exit." << endl;
            break;

        default:
            cout << "You have enter a wrong choice." << endl;
            cout << "Please Reenter your choice." << endl;
            break;
        }
        cout << endl;
        ch = 'y';
        cout << "\nDo You want to continue(y/n)." << endl;
        cin >> ch;
        if (ch == 'N' || ch == 'n')
            choice = 10;
        cout << endl;
    }

    cout << endl;
    if (equate(t1, t2))
        cout << "Both the Trees are Equal." << endl;
    else
        cout << "Trees are not Equal." << endl;
    return 0;
}