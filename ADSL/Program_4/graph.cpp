/*
There are flight paths between cities. If there is a flight between city
A and city B then there is an edge between the cities. The cost of the
edge can be the time that flight takes to reach city B from A, or the
amount of fuel used for the journey. Represent this as a graph. The
node can be represented by airport name or name of the city. Use
adjacency list representation of the graph. (Operation to be
performed adding and deleting edge, adding and deleting vertices,
calculated in-degree and out-degree for directed graph. Use any
traversal to traverse graph)
*/

#include <iostream>
#define MAX 10
using namespace std;

class node
{
    string cityname;
    int weight;
    node *next;

public:
    node(string, int);
    friend class graph;
};

node::node(string a, int x)
{
    cityname = a;
    weight = x;
    next = NULL;
}

class graph
{
    int numofvertices;
    string city[MAX];
    node *head[MAX];

public:
    //Constructor
    graph();

    //Main Functions
    void create();
    void addEdge();
    void deleteEdge();
    void addVertex();
    void deleteVertex();
    void calculatIndegree(string);
    void calculatOutdegree(string);
    void showGraph();
    void mainmenu();

    //Utility Functions
    int returnIndex(string);
};

graph::graph()
{
    cout << "\n\nEnter the number of cities to be represented on the network\n";
    cin >> numofvertices;
    if (numofvertices > MAX)
        cout << "Only " << MAX << " cities allowed\n";
    for (int i = 0; i < numofvertices; i++)
    {
        head[i] = NULL;
        city[i] = " ";
    }
    cout << "\n\nGraph initialised\n";
}

void graph::create()
{
    int x, cost;
    cout << "\n\nEnter the names of " << numofvertices << " cities\n";
    for (int i = 0; i < numofvertices; i++)
    {
        cin >> city[i];
    }
    cout << "\n\nThe " << numofvertices << " cities are:\n";
    for (int i = 0; i < numofvertices; i++)
    {
        cout << i + 1 << " -> " << city[i] << "\n";
    }
}

void graph::addEdge()
{
    string src, dest;
    int sourceIndex = 0, destinationIndex = 0, cost;

    showGraph();

_back:
    cout << "Source City : ";
    cin >> src;
    sourceIndex = returnIndex(src);

    cout << "Destination City : ";
    cin >> dest;
    destinationIndex = returnIndex(dest);

    if ((src.compare(dest) == 0) || (sourceIndex == -1) || (destinationIndex == -1))
    {
        cout << "Can't be same or Doesn't exist\n";
        goto _back;
    }

    cout << "Cost from " << src << " to " << dest << ": ";
    cin >> cost;

    if (head[sourceIndex])
    {
        node *temp = head[sourceIndex];
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new node(dest, cost);
    }
    else
    {
        head[sourceIndex] = new node(dest, cost);
    }

    showGraph();
}

void graph::deleteEdge()
{
    string src, dest;
    int sourceIndex = 0, destinationIndex = 0, cost;

    showGraph();

_back:
    cout << "Source City : ";
    cin >> src;
    sourceIndex = returnIndex(src);

    cout << "Destination City : ";
    cin >> dest;
    destinationIndex = returnIndex(dest);

    if ((src.compare(dest) == 0) || (sourceIndex == -1) || (destinationIndex == -1))
    {
        cout << "Can't be same or Doesn't exist\n";
        goto _back;
    }

    node *temp = head[sourceIndex];
    if (!temp)
    {
        cout << "No flights from " << src << "\n";
        return;
    }

    if ((head[sourceIndex]->cityname).compare(dest) == 0) //if first node is to be deleted
    {
        head[sourceIndex] = head[sourceIndex]->next;
    }
    else
    {
        node *temp2 = temp->next;
        while (temp->next)
        {
            if ((temp2->cityname).compare(dest) == 0)
            {
                temp->next = temp2->next;
                break;
            }
            temp = temp->next;
            temp2 = temp2->next;
        }
    }
    showGraph();
}

void graph::addVertex()
{
    string name;
    if (numofvertices < MAX)
    {
        cout << "Enter the city to add : ";
        cin >> name;
        city[numofvertices] = name;
        numofvertices++;
        head[numofvertices - 1] = NULL;
        cout << "\n\nNow, the cities in the network are: \n";
        for (int i = 0; i < numofvertices; i++)
            cout << i + 1 << " -> " << city[i] << "\n";
    }
    else
        cout << "\n\nCan't add. Already has " << MAX << " cities";
}

void graph::deleteVertex() //segmentation fault
{
    string name;
_back:
    cout << "City you want to delete from the network: ";
    cin >> name;

    int src = returnIndex(name);

    if (src == -1)
    {
        cout << "City doesn't exist in network or Network empty\n";
        return;
    }

    //Deleting this city from the city array(array of strings)
    if (src == numofvertices - 1)
    {
        numofvertices--;
    }
    else
    {
        for (int i = src; i < numofvertices; i++)
            city[i] = city[i + 1];
        for (int i = src; i < numofvertices; i++)
            head[i] = head[i + 1];
        numofvertices--;
    }

    if (numofvertices)
    {
        cout << "\nCities in network now are: \n ";

        for (int i = 0; i < numofvertices; i++)
        {
            cout << city[i] << " ";
        }
    }
    else
        cout << "No cities in network\n";

    //Deleting Edges from all cities to this city
    for (int i = 0; i < numofvertices;)
    {
        if (head[i])
        {
            node *temp = head[i];
            if ((head[i]->cityname).compare(name) == 0) //if first node is to be deleted
            {
                head[i] = head[i]->next;
            }
            else
            {
                node *temp2 = head[i]->next;
                while (temp)
                {
                    if ((temp2->cityname).compare(name) == 0)
                    {
                        temp->next = temp2->next;
                        goto outer; //dont use break...it breaks outer loop also
                    }
                    temp = temp->next;
                    temp2 = temp2->next;
                }
            }
        }
    outer:
        i++;
    }
    showGraph();
}

void graph::calculatIndegree(string name)
{
    showGraph();

    int destinationIndex = returnIndex(name);
    if (destinationIndex == -1)
    {
        cout << "Such a city doesn't exist\n";
        return;
    }
    int count = 0;

    for (int i = 0; i < numofvertices; i++)
    {
        node *temp = head[i];
        if (head[i])
        {
            while (temp)
            {
                if ((temp->cityname).compare(name) == 0)
                    count++;
                temp = temp->next;
            }
        }
    }
    cout << "Flights landing in " << name << " is/are " << count;
}

void graph::calculatOutdegree(string name)
{
    showGraph();
    int count = 0;

    int sourceIndex = returnIndex(name);

    if (sourceIndex == -1)
    {
        cout << "Such a city doesn't exist\n";
        return;
    }

    node *temp = head[sourceIndex];
    while (temp)
    {
        temp = temp->next;
        count++;
    }
    cout << "Flights taking off from " << name << " is/are " << count;
}

void graph::showGraph()
{
    if (numofvertices)
    {
        cout << "\n\nThe network is:\n";
        for (int i = 0; i < numofvertices; i++)
        {
            cout << city[i] << " -> ";
            if (head[i])
            {
                node *temp = head[i];
                while (temp)
                {
                    cout << temp->cityname << "(" << temp->weight << ")";
                    if (temp->next)
                        cout << ", ";
                    temp = temp->next;
                }
            }
            cout << "\n";
        }
    }
    else
        cout << "Empty Network\n";
}

void graph::mainmenu()
{
    cout << "1. Enter the details of the network\n";
    cout << "2. Add a city to the network\n";
    cout << "3. Delete a city from the network\n";
    cout << "4. Add a flight from a city\n";
    cout << "5. Delete a flight from a city\n";
    cout << "6. Get number of flights landing in each city\n";
    cout << "7. Get number of flight taking off from each city\n";
    cout << "8. Show the current network\n";
}

int graph::returnIndex(string s)
{
    for (int i = 0; i < numofvertices; i++)
        if (city[i].compare(s) == 0)
            return i;
    return -1;
}

int main()
{
    string name;
    graph g;
_mainmenu:
    g.mainmenu();
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        g.create();
        break;
    case 2:
        g.addVertex();
        break;
    case 3:
        g.deleteVertex();
        break;
    case 4:
        g.addEdge();
        break;
    case 5:
        g.deleteEdge();
        break;
    case 6:
        cout << "Enter the name of the city: ";
        cin >> name;
        g.calculatIndegree(name);
        break;
    case 7:
        cout << "Enter the name of the city: ";
        cin >> name;
        g.calculatOutdegree(name);
        break;
    case 8:
        g.showGraph();
        break;
    }
    cout << "\n\n";
    cout<<"\nDo you want to continue (y/n) : ";
    char yn;    cin>>yn;
    if(yn=='y')
    goto _mainmenu;
    return 0;
}