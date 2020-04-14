#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdlib>

using namespace std;
class Department
{
    char name[10], add[10];
    int div, roll;

public:
    void getdata();
    void showdata();
    char *getname() { return name; }
    int getroll() { return roll; }

    void update(char *nm, char *addr, int divi)
    {
        strcpy(name, nm);
        strcpy(add, addr);
        div = divi;
    }
};

void Department ::getdata()
{
    cout << "\nEnter Name : ";
    cin >> name;
    cout << "\nEnter Roll Number : ";
    cin >> roll;
    cout << "\nEnter Division : ";
    cin >> div;
    cout << "\nEnter City : ";
    cin >> add;
}

void Department ::showdata()
{
    cout << "\n\nName-: " << name;
    cout << "\nRoll Number-: " << roll;
    cout << "\nDivision-:" << div;
    cout << "\nCity-: " << add << "\n";
}

int main()
{
    Department rec;
    fstream file;
    file.open("data.dat", ios::ate | ios::in | ios::out | ios::binary);
    char ch, nm[10], addr[10];
    int choice, found = 0;
    int roll, div;
    while (true)
    {
        cout << "\n*****Department Students*****\n";
        cout << "1) Add New Record\n";
        cout << "2) Display All Records\n";
        cout << "3) Search by Person Name\n";
        cout << "4) Search by Roll No.\n";
        cout << "5) Update Information\n";
        cout << "6) Exit\n";
        cout << "Choose your choice : ";
        cin >> choice;
        int cnt = 0;

        switch (choice)
        {
        case 1: //New Record
            rec.getdata();
            cin.get(ch);
            file.write((char *)&rec, sizeof(rec));
            break;

        case 2: //Display All Records
            file.seekg(0, ios::beg);
            cout << "\n\n================Records in Department===================\n";
            while (file)
            {
                file.read((char *)&rec, sizeof(rec));
                if (!file.eof())
                {
                    cout << "\n---------------------------------------------------";
                    rec.showdata();
                    cout << "\n---------------------------------------------------";
                }
            }
            file.clear();
            break;

        case 3: //Search when person name is known.
            cout << "\n\nEnter Name : ";
            cin >> nm;
            file.seekg(0, ios::beg);
            found = 0;
            while (file.read((char *)&rec, sizeof(rec)))
            {
                if (strcmp(nm, rec.getname()) == 0)
                {
                    found = 1;
                    rec.showdata();
                }
            }
            file.clear();
            if (found == 0)
                cout << "\n\n---Record Not found---\n";
            // getch();
            break;

        case 4: //Search name on basis of roll no.
            cout << "\n\nEnter Roll No : ";
            cin >> roll;
            file.seekg(0, ios::beg);
            found = 0;
            while (file.read((char *)&rec, sizeof(rec)))
            {
                if (roll == rec.getroll())
                {
                    found = 1;
                    rec.showdata();
                }
            }
            file.clear();
            if (found == 0)
                cout << "\n\n---Record Not found---\n";
            // getch();
            break;

        case 5: //Update Information.
            cout << "\n\nEnter Roll No : ";
            cin >> roll;
            file.seekg(0, ios::beg);
            found = 0;

            while (file.read((char *)&rec, sizeof(rec)))
            {
                cnt++;
                if (rec.getroll() == roll)
                {
                    found = 1;
                    break;
                }
            }
            file.clear();
            if (found == 0)
                cout << "\n\n---Record Not found---\n";
            else
            {
                int location = (cnt - 1) * sizeof(rec);
                cin.get(ch);
                if (file.eof())
                    file.clear();

                cout << "Enter Updated name : ";
                cin >> nm;
                cout << "\nEnter Updated Division-: ";
                cin >> div;
                cout << "\nEnter Updated Address-: ";
                cin >> addr;
                file.seekp(location);

                rec.update(nm, addr, div);

                file.write((char *)&rec, sizeof(rec));
                file.flush();
            }
            break;
        case 6:
            exit(1);
            break;
        }
    }

    file.close();
}