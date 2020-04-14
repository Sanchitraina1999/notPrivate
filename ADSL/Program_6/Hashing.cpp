#include <iostream>
using namespace std;

class node
{
    string key, meaning;

public:
    friend class HashTable;
};

class HashTable
{
    node *HT;
    int n;

public:
    HashTable(int d)
    {
        n = d;
        HT = new node[n];
        for (int i = 0; i < n; i++)
            HT[i].key = "#";
    }
    void create();
    void withoutinsert(node); //linear probing without replacement
    void withinsert(node);    //linear probing with replacement
    void find();
    void del();
};

void HashTable::del()
{
    string k;
    cout << "\nEnter key of element to be deleted: ";
    cin >> k;

    int l = k.length() % n;

    if (HT[l].key == k)
    {
        HT[l].key = "#";
        HT[l].meaning = "";
        cout << "\nDELETED SUCCESSFULLY";
    }
    else
    {
        int i;
        for (i = (l + 1) % n; i != l && HT[i].key != k; i = (i + 1) % n)
            ;
        if (i == l)
            cout << "\nENTRY DOES NOT EXISTS";
        else
        {
            HT[i].key = "#";
            HT[i].meaning = "";
            cout << "\nDELETED SUCCESSFULLY";
        }
    }
}

void HashTable::find()
{
    string k;

    cout << "\nEnter key of element to be found: ";
    cin >> k;

    int l = k.length() % n;

    if (HT[l].key == k)
        cout << "\nFOUND!\n"
             << HT[l].key << " - " << HT[l].meaning;
    else
    {
        int i;
        for (i = (l + 1) % n; i != l && HT[i].key != k; i = (i + 1) % n)
            ;
        if (i == l)
            cout << "\nNOT FOUND!";
        else
            cout << "\nFOUND!\n"
                 << HT[i].key << " - " << HT[i].meaning;
    }
}

void HashTable::withoutinsert(node nn)
{
    int l = nn.key.length() % n;

    int i;
    for (i = l; HT[i].key != "#"; i = (i + 1) % n)
        ;
    HT[i] = nn;

    for (int i = 0; i < n; i++)
        cout << HT[i].key << "\n";
}
void HashTable::withinsert(node nn)
{
    int l = nn.key.length() % n;

    if (HT[l].key == "#")
    {
        HT[l] = nn;
    }
    else
    {
        if (HT[l].key.length() % n == l)
        {
            int i;
            for (i = (l + 1) % n; HT[i].key != "#"; i = (i + 1) % n)
                ;
            HT[i] = nn;
        }
        else
        {
            node temp;
            temp = HT[l];
            HT[l] = nn;
            int i;
            for (i = (l + 1) % n; HT[i].key != "#"; i = (i + 1) % n)
                ;
            HT[i] = temp;
        }
    }
    for (int i = 0; i < n; i++)
        cout << HT[i].key << "\n";
}

void HashTable::create()
{
    string k, m;
    int ch;

    cout << "\nEnter type of Linear Probing: \n1. Without Replacement\n2. With Replacement: ";
    cin >> ch;
    while (ch != 1 && ch != 2)
    {
        cout << "\nInvalid!";

        cout << "\nEnter type of Linear Probing: \n1. Without Replacement\n2. With Replacement: " ;
        cin >> ch;
    }

    for (int i = 0; i < n; i++)
    {
        node nn;
        cout << "\n"
             << i + 1 << " Entry";
        cout << "\nEnter key: ";
        cin >> nn.key;
        cout << "Enter meaning: ";
        cin >> nn.meaning;

        if (ch == 1)
            withoutinsert(nn);
        if (ch == 2)
            withinsert(nn);
    }
}

int main()
{
    int n;
    cout << "\nEnter number of dictionary entries: ";
    cin >> n;
    HashTable obj(n);
    obj.create();
    do
    {
        cout << "\nSELECT OPTION\n1. Retrieve\n2. Delete\n3. Exit : ";
        cin >> n;
        if (n == 1)
            obj.find();
        if (n == 2)
            obj.del();
    } while (n != 3);
    return 0;
}