#include <iostream>
using namespace std;
class Node
{
private:
    int data;
    Node *next;

public:
    Node *start, *head, *temp, *start1, *start2;

    void create(int data) 
    {                    
        if (start == NULL)
        {
            start = new Node;
            start->data = data;
            start->next = NULL;
            head = start;
        }
        else
        {
            head->next = new Node;
            head = head->next;
            head->data = data;
            head->next = NULL;
        }
    }

    void insert(Node *tempstart, int data) //Inserting at end
    {
        head = tempstart;
        while (head->next != NULL)
        {
            head = head->next; 
        }
        head->next = new Node;
        head = head->next;
        head->data = data;
        head->next = NULL;
    }
    void print(Node *tempstart) //Print from start till head!=NULL
    {
        cout << "\nThe set is :\n";
        head = tempstart;
        cout << "{ ";
        while (head != NULL)
        {
            cout << head->data << " ";
            head = head->next;
        }
        cout << "}";
        cout << "\n\n***** *** *****\n";
    }

    bool search(Node *tempstart, int data) //Simple linear search
    {
        head = tempstart;
        while (head != NULL)
        {
            if (head->data == data)
            {
                return true;
            }
            head = head->next;
        }
            return false;
    }

    int remove(Node *tempstart, int data) //removes single element
    {
        head = tempstart;

        if (head->data == data) //if first node is equal
        {
            temp = head;
            head = head->next;
            start = head;
            delete (temp);
            return 1;
        }
        while (head->next != NULL)
        {
            if ((head->next->data) == data)
            {
                temp = head->next;
                head->next = head->next->next;
                delete (temp);
                return 1;   //deleted
            }
            else
                head = head->next;
        }
        return 0;   //not deleted
    }

    void intersection(Node *tempstart1, Node *tempstart2)
    {
        head = tempstart1;
        cout << "\nThe intersection of the two sets is : \n";
        while (head != NULL)
        {
            temp = tempstart2;
            while (temp != NULL)
            {
                if (head->data == temp->data)
                    cout << head->data << " ";
                temp = temp->next;
            }
            head = head->next;
        }
    }

    void unionset(Node *tempstart1, Node *tempstart2)
    {
        head = tempstart1;
        temp = tempstart2;
        cout << "\nThe union of the two sets is : \n";
        while (temp != NULL || head != NULL)
        {
            if (head == NULL) //if first set is null then only display temp
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
            else if (temp == NULL) //if second set is null then only display head
            {
                cout << head->data << " ";
                head = head->next;
            }
            else if (head->data == temp->data) //if it is equal then display any one (union has only one occurence)
            {
                cout << head->data << " ";
                head = head->next;
            }
            else if (head->data > temp->data) //if first set element is greater, then display second set element
            {                                 //Basically display the lower one of the two sets
                cout << temp->data << " ";
                temp = temp->next;
            }
            else if (head->data < temp->data) //if second set element is greater, then display first set element
            {                                 //Basically display the lower one of the two sets
                cout << head->data << " ";
                head = head->next;
            }
        }
    }
};

int main()
{
    Node n;
    int data, i, limit, choice, flag;
    n.start = NULL;
    n.start1 = NULL;
    n.start2 = NULL;
    cout << "\n***** *** *****\n";
    cout << "\nEnter number of elements in the set : ";
    cin >> limit;
    cout << "\nEnter elements sequencially only,\n";
    for (i = 0; i < limit; i++)
    {
        cout << "Enter data : ";
        cin >> data;
        n.create(data); 
    }
    n.start1 = n.start;
    n.start = NULL;    
    n.print(n.start1);
    cout << "\nEnter number of elements in the second set : ";
    cin >> limit;
    cout << "\nEnter elements sequencially only,\n";
    for (i = 0; i < limit; i++)
    {
        cout << "Enter data : ";
        cin >> data;
        n.create(data); 
    }
    n.start2 = n.start; 
    n.print(n.start2);
    cout << "\n***** *** *****\n";
    do
    {
        cout << "\n1.Insert Elements\n2.Search\n3.Delete Element\n4.Intersection\n5.Union\n6.Exit\nEnter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\nEnter data you want to insert :";
            cin >> data;
            n.insert(n.start1, data);
            limit++;
            cout << "\n***** *** *****\n";
            cout << "\nThe element is added";
            n.print(n.start1);
            break;
        case 2:
            cout << "Enter the data to be searched : ";
            cin >> data;
            if (n.search(n.start1, data))
                cout << "Element is present";
            else
                cout << "Element is not present";
            break;
        case 3:
            cout << "Enter the element to be deleted : ";
            cin >> data;
            flag = n.remove(n.start1, data); 
            if (flag == 1)
            {
                cout << "Element deleted successfully";
                limit--;
            }
            else
                cout << "Element not deleted successfully";
            cout << "\n***** *** *****\n";
            break;
        case 4:
            n.intersection(n.start1, n.start2);
            cout << "\n***** *** *****\n";
            break;
        case 5:
            n.unionset(n.start1, n.start2);
            cout << "\n***** *** *****\n";
            break;
        case 6:
            cout << "\nExiting...\n";
            break;
        default:
            cout << "\nWrong choice entered...Try Again";
            break;
        }
    } while (choice != 6);
}