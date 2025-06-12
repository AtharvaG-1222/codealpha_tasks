#include <iostream>
using namespace std;

class product
{
    string name;
    int quant;

public:
    void put_data(string s, int q)
    {
        name = s;
        quant = q;
    }
    friend void display(product *p, int count);
    friend void add(product *p, int &count);
    friend product *remove(product *p, int &count, string pro);
    friend void modify(product *p, int count, string n, int qt);
};

void display(product *p, int count)
{
    cout << "Product Name\t\tQuantity" << endl;
    for (int i = 0; i < count; i++)
    {
        cout << "\t" << p[i].name << "\t\t" << p[i].quant << endl;
    }
}

void add(product *inv, int &count)
{
    string pro;
    int q, c;

    cin.ignore();
    cout << "Enter The Name Of Product: ";
    getline(cin, pro);
    for (int i = 0; i < count; i++)
    {
        if (inv[i].name == pro)
        {
            c = 1;
            break;
        }
    }
    if (c == 1)
    {
        count--;
        throw 2;
    }
    cout << "Enter the Quantity of Product: ";
    cin >> q;

    inv[count - 1].put_data(pro, q);
    cout << "Product Added Successfully!" << endl;
}

void modify(product *p, int count, string n, int qt)
{
    int i, c = 0;
    for (i = 0; i < count; i++)
    {
        if (p[i].name == n)
        {
            c = 1;
            break;
        }
    }
    if (c == 0)
    {
        throw 1;
    }
    cout << "1. Increase Quantity\n2. Decreasee Quantity\nEnter Choice: ";
    cin >> c;
    switch (c)
    {
    case 1:
        p[i].quant += qt;
        cout << "Quantity Increased Successfully by: " << qt << endl;
        break;
    case 2:
        if (p[i].quant >= qt)
        {
            p[i].quant -= qt;
            cout << "Quantity Decreased Successfully by: " << qt << endl;
        }
        else
        {
            throw 3;
        }
        break;
    default:
        cout << "Enter A Valid Choice!!" << endl;
    }
}
product *remove(product *p, int &count, string pro)
{
    int i, c, ch;
    for (i = 0; i < count; i++)
    {
        if (p[i].name == pro)
        {
            ch = 1;
            break;
        }
        else
        {
            ch = 0;
        }
    }
    count -= 1;
    if (ch == 1)
    {
        for (int j = i; j < count; j++)
        {
            p[j] = p[j + 1];
        }
        product *temp = new product[count];
        for (i = 0; i < count; i++)
        {
            temp[i] = p[i];
        }

        delete[] p;

        cout << "\"" << pro << "\"Removed Successfully!" << endl;

        return temp;
    }
    else
    {
        throw 4;
    }
}

int main()
{
    int i, count = 0, ch = 1, q;
    product *inv, *tem;
    string pro;
    inv = new product[count];
    do
    {
        cout << "1. Initialize Inventory\n2. Add Product\n3. Modify Product\n";
        cout << "4. Delete Product\n5. Display Inventory\nEnter Choice: " << endl;
        cin >> ch;
        switch (ch)
        {

        case 1:
            count = 0;
            cout << "Inventory Initialised Successfully With '0' Products" << endl;
            break;
        case 2:
            tem = new product[count + 1];
            for (i = 0; i < count; i++)
            {
                tem[i] = inv[i];
            }
            count += 1;
            delete[] inv;
            inv = new product[count];
            for (i = 0; i < count; i++)
            {
                inv[i] = tem[i];
            }
            try
            {
                add(inv, count);
            }
            catch (int n)
            {
                cout << "Product Already Exists" << endl;
            }
            delete[] tem;
            break;
        case 3:
            cin.ignore();
            cout << "Enter Product you need to modify: ";
            getline(cin, pro);
            cout << "Enter Quantity To Modify: ";
            cin >> q;
            try
            {
                modify(inv, count, pro, q);
            }
            catch (int n)
            {
                if (n == 1)
                {
                    cout << "Item Doesn't Exists!!" << endl;
                }
                if (n == 3)
                {
                    cout << "Specified Quantity Doesn't Exists!!" << endl;
                }
            }
            break;
        case 4:
            cin.ignore();
            cout << "Enter Product To Delete: " << endl;
            getline(cin, pro);
            try
            {
                inv = remove(inv, count, pro);
                // inv = tem;
                // delete[] tem;
            }
            catch (int n)
            {
                cout << "Item Not Found!!" << endl;
            }
            break;
        case 5:
            if (count == 0)
            {
                cout << "Inventory Is Already Empty!!" << endl;
                break;
            }
            else
            {
                display(inv, count);
            }
            break;
        default:
            cout << "Invalid Choice, Terminating Inventory Management System!!";
            ch = 0;
        }
    } while (ch != 0);

    return 0;
}