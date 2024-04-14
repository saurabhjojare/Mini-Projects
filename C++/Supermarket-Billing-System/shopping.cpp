#include "shopping.h"
#include <iostream> // Include necessary headers
#include <string>

using namespace std; // Add this line to use the std namespace

void shopping::menu() {
    m:
    int choice;
    string email;
    string password;

    cout << "\nSupermarket Main Menu\n";
    cout << "1) Administrator \n";
    cout << "2) Buyer         \n";
    cout << "3) Exit          \n";
    cout << "Please Select: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "\nPlease Login\n";
        cout << "Enter Email: ";
        cin >> email;
        cout << "Password: ";
        cin >> password;

        if (email == "dan@gmail.com" && password == "dan@123")
        {
            administrator();
        }
        else
        {
            cout << "\nInvalid email/password\n";
        }
        break;

    case 2:
        buyer();
        break;

    case 3:
        exit(0);

    default:
        cout << "Please Select From The Given Options";
    }

    goto m;
}

void shopping::administrator() {
    m:
    int choice;
    cout << "\nAdministrator Menu\n";
    cout << "1) Add Product\n";
    cout << "2) Modify Product\n";
    cout << "3) Delete Product\n";
    cout << "4) Main Menu\n";
	
    cout << "\nEnter Your Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        add();
        break;

    case 2:
        edit();
        break;

    case 3:
        rem();
        break;

    case 4:
        menu();
        break;
        
    default:
        cout << "Invalid Choice";
    }

    goto m;
}

void shopping::buyer() {
    m:
    int choice;
    cout << "\nBuyer Menu\n";
    cout << "1) Buy product\n";
    cout << "2) Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        receipt();
        break;

    case 2:
        menu();
        break;

    default:
        cout << "Invalid Choice";
    }

    goto m;
}

void shopping::add() {
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\nAdd Product\n";
    cout << "Product Code: ";
    cin >> pcode;

    cout << "Product Name: ";
    cin >> pname;
    cout << "Product Price: ";
    cin >> price;
    cout << "Product Discount: ";
    cin >> dis;

    data.open("database.txt", ios::in);

    if (!data)
    {
        data.open("database.txt", ios::app | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
        cout << "Record Inserted\n";
    }
    else
    {
        data >> c >> n >> p >> d;
        while (!data.eof())
        {
            if (c == pcode)
            {
                cout << "Product code already exists. Record not inserted.\n";
                data.close();
                return; 
            }
            data >> c >> n >> p >> d;
        }
        data.close();

        data.open("database.txt", ios::app | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
        cout << "Record Inserted\n";
    }
}

void shopping::edit() {
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\nModify Record\n";
    cout << "Product Code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "File Doesn't Exist\n";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pkey == pcode)
            {
                cout << "New Code: ";
                cin >> c;
                cout << "New Name: ";
                cin >> pname;  
                cout << "New Price: ";
                cin >> p;
                cout << "New Discount: ";
                cin >> d;
                data1 << " " << c << " " << pname << " " << p << " " << d << "\n"; 
                cout << "Record Edited\n";
                token++;
            }
            else
            {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "Record not found\n";
        }
    }
}

void shopping::rem() {
    fstream data, data1;
    int pkey;
    int token = 0;
    cout << "\nDelete Product\n";
    cout << "Product Code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "File Doesn't Exist\n";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pcode == pkey)
            {
                cout << "Product Deleted Successfully\n";
                token++;
            }
            else
            {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "Record Not Found\n";
        }
    }
}

void shopping::list() {
     fstream data;
    data.open("database.txt", ios::in);
    cout << "\nProduct No\tName\t\tPrice\n";
    data >> pcode >> pname >> price >> dis;
    while (!data.eof())
    {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shopping::receipt() {
    fstream data;
    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount = 0;
    float total = 0;

    cout << "\nPlace the order\n";

    do
    {
    m:
        list();  

        cout << "\nEnter Product Code: ";
        cin >> arrc[c];
        cout << "Quantity: ";
        cin >> arrq[c];

        for (int i = 0; i < c; i++)
        {
            if (arrc[c] == arrc[i])
            {
                cout << "\nDuplicate Product Code.\n";
                goto m;
            }
        }
        c++;
        cout << "\nDo You Want To Buy Another Product?\ny or n: ";
        cin >> choice;

    } while (choice == 'y');

    cout << "\nReceipt\n";
    cout << "Product No\tProduct Name\tQuantity\tPrice\t\tDiscount\n";

    for (int i = 0; i < c; i++)
    {
        data.open("database.txt", ios::in);
        data >> pcode >> pname >> price >> dis;

        while (!data.eof())
        {
            if (pcode == arrc[i])
            {
                amount = price * arrq[i];
                float productDiscount = amount * dis / 100;
                total += (amount - productDiscount);

                cout << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t\t" << productDiscount << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
    }
    cout << "\nTotal Amount: " << total << "\n";
}

