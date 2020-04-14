#include <iostream>
#include <string>
using namespace std;

class node
{
    string key, meaning;
    node *lchild, *rchild;

public:
    node()
    {
        lchild = NULL;
        rchild = NULL;
    }
    friend class bst;
    string retkey()
    {
        return key;
    }
};

class bst
{
    node *root;

public:
    node *getdata(string);
    node *insert(node *, string);
    void inorder(node *);
    void inorderev(node *);
    void update(string);
    void del(node *, string);
    node *copy(node *);

    node *retroot()
    {
        return root;
    }

    void assignroot(node *temp)
    {
        root = temp;
    }
    bst()
    {
        root = NULL;
    }
};

node *bst::copy(node *t)
{
    if (t == NULL)
        return NULL;
    else
    {
        node *mr = new node();
        mr->key = t->key;
        mr->meaning = t->meaning;
        mr->lchild = copy(t->lchild);
        mr->rchild = copy(t->rchild);
        return mr;
    }
}

void bst::del(node *T, string fkey)
{
    if (T == NULL)
        cout << "\n Empty Tree!";
    else
    {
        node *temp = root;
        node *p;
        while (temp->key != fkey && temp != NULL)
        {
            p = temp;
            if (temp->key < fkey)
                temp = temp->rchild;

            else if (temp->key > fkey)
                temp = temp->lchild;
        }
        if (temp == NULL)
        {
            cout << "\n Not found";
            return;
        }

        if (temp->rchild == NULL && temp->lchild == NULL)
        {
            if (temp == root)
            {
                root = NULL;
                delete temp;
                cout << "\nDeleted Successfully";
                return;
            }
            if (p->rchild == temp)
                p->rchild = NULL;
            else
                p->lchild = NULL;
            cout << "\nDeleted Successfully";
            delete temp;
        }
        else if (temp->rchild == NULL && temp->lchild != NULL)
        {
            if (temp == root)
            {
                root = temp->lchild;
                delete temp;
            }
            else
            {
                if (p->rchild == temp)
                    p->rchild = temp->lchild;
                else
                    p->lchild = temp->lchild;
                cout << "\nDeleted Successfully";
                delete temp;
            }
        }
        else if (temp->lchild == NULL && temp->rchild != NULL)
        {
            if (temp == root)
            {
                root = temp->rchild;
                cout << "\nDeleted Successfully";
                delete temp;
            }
            else
            {
                if (p->rchild == temp)
                    p->rchild = temp->rchild;
                else
                    p->lchild = temp->rchild;
                cout << "\nDeleted Successfully";
                delete temp;
            }
        }
        else
        {
            node *pre = temp->lchild;
            node *prep = temp->lchild;

            while (pre->rchild != NULL)
            {
                prep = pre;
                pre = pre->rchild;
            }
            temp->key = pre->key;
            temp->meaning = pre->meaning;
            if (pre->lchild != NULL)
                prep->rchild = pre->lchild;
            else
                prep->rchild = NULL;
            cout << "\nDeleted Successfully";
            delete pre;
        }
    }
}

void bst::update(string fkey)
{
    node *T = root;
    while (T != NULL)
    {
        if (T->key < fkey)
            T = T->rchild;
        else if (T->key > fkey)
            T = T->lchild;
        else if (T->key == fkey)
        {
            cout << "Enter new meaning: ";
            getline(cin, T->meaning);
            cout << "\nUpated Successfully";
            return;
        }
    }
    if (T == NULL)
        cout << "\nEntered Node does not exists";
}

node *bst::getdata(string fkey)
{
    node *newnode = new node();
    newnode->key = fkey;
    cout << "\n Enter meaning: ";
    getline(cin, newnode->meaning);
    return newnode;
}

node *bst::insert(node *T, string fkey)
{
    if (T == NULL)
    {
        return getdata(fkey);
    }
    else if (T->key < fkey)
    {
        T->rchild = insert(T->rchild, fkey);
    }
    else if (T->key > fkey)
    {
        T->lchild = insert(T->lchild, fkey);
    }
    else
    {
        cout << "\nDuplicate entries not allowed.";
    }

    return T;
}

void bst::inorder(node *T)
{
    if (T == NULL)
    {
        if (root == NULL)
            cout << "\nEmpty Tree";
        return;
    }
    if (T != NULL)
    {
        inorder(T->lchild);
        cout << T->key << "\t" << T->meaning << "\n";
        inorder(T->rchild);
    }
}

void bst::inorderev(node *T)
{
    if (T == NULL)
    {
        if (root == NULL)
            cout << "\nEmpty Tree";
        return;
    }
    if (T != NULL)
    {
        inorderev(T->rchild);
        cout << T->key << "\t" << T->meaning << "\n";
        inorderev(T->lchild);
    }
}

int main()
{
    string s;
    bst b1, b2;
    int dec;
    char dec1;
    do
    {
        cout<< "\n MENU \n1.INSERT WORD \n2.PRINT DICTIONARY(ascending) \n3.PRINT DICTIONARY(descending) \n4.UPDATE \n5.DELETE \n6.COPY: ";
        cin >> dec;

        switch (dec)
        {
        case 1:
            do
            {
                cin.ignore();
                if (b1.retroot() == NULL)
                {
                    cout << "\n Enter Word: ";
                    getline(cin, s);
                    b1.assignroot(b1.insert(b1.retroot(), s));
                }
                else
                {
                    cout << "\n Enter Word: ";
                    getline(cin, s);
                    b1.insert(b1.retroot(), s);
                }

                cout << "\n Do you want to continue inserting words ?(y/n)";
                cin >> dec1;
            } while (dec1 == 'y' || dec1 == 'Y');

            break;

        case 2:
            b1.inorder(b1.retroot());
            break;

        case 3:
            b1.inorderev(b1.retroot());
            break;
        case 4:
            if (b1.retroot() == NULL)
                cout << "\nEmpty Tree";
            else
            {

                cout << "\n Enter word to be updated: ";
                cin.ignore();
                getline(cin, s);
                b1.update(s);
            }
            break;
        case 5:
            if (b1.retroot() == NULL)
                cout << "\nEmpty Tree";
            else
            {
                cout << "\n Enter word to be deleted: ";
                cin.ignore();
                getline(cin, s);
                b1.del(b1.retroot(), s);
            }
            break;
        case 6:
            node *root1 = b1.copy(b1.retroot());
            cout << "\n\nCOPIED TREE SUCCESSFULLY\n";
            b2.assignroot(root1);
            cout<<"Displaying copied Dictionary:\n";
            b2.inorder(b2.retroot());
            break;
        }
        cout << "\nDo you want to continue?(y\\n)";
        cin >> dec1;
    } while (dec1 == 'y' || dec1 == 'Y');

    return 0;
}