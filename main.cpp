#include <bits/stdc++.h>
using namespace std;
void add_user(void);
void user_login(void);
void change_pass(string);
void admin_login(void);
void modify_details(void);
void delete_details(void);
void display_all(void);
void display_one(void);
class Sepoy
{
private:
    string sepoy_id; //only for sepoys and hence not inheritable
    string post;
    string name;
    string DOB;
    string password; //for storing password
    // private:                   //not inheritable information
    //     string sepoy_section_id;
    //     string sepoy_company_id;
    //     string sepoy_platoon_id;

public:
    // Sepoy() : DOB("noname"), sepoy_id("noname"), name("noname"), password("noname"), post("noname") {}
    void getter(void)
    {
        cout << "Enter Name of Sepoy: ";
        cin >> name;
        cout << endl;
        cout << "Enter DOB: ";
        cin >> DOB;
        cout << endl;
        cout << "Enter Id: ";
        cin >> sepoy_id;
        cout << endl;
        cout << "Enter your Post(General-Duty/Officer): ";
        cin >> post;
        cout << endl;
        cout << "Enter the Password: ";
        cin >> password;
        cout << endl;
    }
    void change_password(string pass)
    {
        this->password = pass;
    }
    void Display(void)
    {
        cout << "Name: " << name << endl;
        cout << "Post: " << post << endl;
        cout << "DOB: " << DOB << endl;
    }
    string getsepoy_id(void)
    {
        return sepoy_id;
    }
    string get_password(void)
    {
        return password;
    }
    string get_post(void)
    {
        return post;
    }
};
int main()
{
    string logout;
    do
    {
        int choice;
        logout = "NO";
        cout << "1. Add User: " << endl;
        cout << "2. User Login" << endl;
        cout << "3. Admin Login" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            add_user();
            break;
        case 2:
            user_login();
            break;
        case 3:
            admin_login();
            break;
        default:
            cout << "\nEnter correct choice and try again...";
            break;
        }
        cout << "Want to logout(NO/YES): ";
        cin >> logout;
    } while (logout == "NO");
    return 0;
}
void add_user(void)
{
    Sepoy obj;
    ofstream oFile;
    oFile.open("sepoy.dat", ios::binary | ios::app);
    obj.getter();
    oFile.write((char*)(&obj), sizeof(Sepoy));
    oFile.close();
    cout << "\n\nSepoy record Has Been Created ";
    cin.ignore();
    cin.get();
}
void user_login(void)
{
    string id;
    string pass; //Password
    cout << "Enter the Sepoy Id: ";
    cin >> id;
    cout << endl;
    cout << "Enter the password: ";
    cin >> pass;
    cout << endl;
    bool found = false;
    Sepoy obj;
    ifstream inFile;
    inFile.open("sepoy.dat", ios::binary | ios::in);
    if (!inFile.is_open())
    {
        cout << "File could not be opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    inFile.seekg(0, ios::beg);
    while (inFile.read((char*)(&obj), sizeof(Sepoy)))
    {
        if (obj.getsepoy_id() == id && pass == obj.get_password() && obj.get_post() != "Officer")
        {
            string choice;
            found = true;
            obj.Display();
            cout << "\nDo you want to change password(YES/NO): ";
            cin >> choice;
            if (choice == "YES" || choice == "yes")
            {
                change_pass(id);
            }
            break;
        }
    }
    if (!found)
    {
        cout << "\nRecord Not Found!!";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}
void change_pass(string id)
{
    bool found = false;
    Sepoy obj;
    fstream fl;
    fl.open("sepoy.dat", ios::binary | ios::in | ios::out);
    if (!fl.is_open())
    {
        cout << "File could not be opened. Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    fl.seekg(0, ios::beg);
    while (!fl.eof() && found == false)
    {
        fl.read((char*)(&obj), sizeof(Sepoy));
        if (obj.getsepoy_id() == id)
        {
            string new_password;
            cout << "\nEnter new Password:";
            cin >> new_password;
            obj.change_password(new_password);
            int pos = (-1) * static_cast<int>(sizeof(obj));
            fl.seekp(pos, ios::cur);
            fl.write((char*)(&obj), sizeof(Sepoy));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    fl.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
    cin.ignore();
    cin.get();
}
void admin_login(void)
{
    string id;
    string password;
    cout << "Enter the Id: ";
    cin >> id;
    cout << endl;
    cout << "Enter password: ";
    cin >> password;
    bool found = false;
    Sepoy obj;
    ifstream inFile;
    inFile.open("sepoy.dat", ios::binary | ios::in);
    if (!inFile.is_open())
    {
        cout << "File could not be opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    inFile.seekg(0, ios::beg);
    while (inFile.read((char*)(&obj), sizeof(Sepoy)))
    {
        if (obj.getsepoy_id() == id && password == obj.get_password() && obj.get_post()=="Officer")
        {
            int choice;
            found = true;
            obj.Display();
            cout << "\n\tMENU";
            cout << "1. Change Password: " << endl;
            cout << "2. Add User: " << endl;
            cout << "3. Modify Details of User: " << endl;
            cout << "4. Delete User: " << endl;
            cout << "5. Display all Users: " << endl;
            cout << "6. Display specific user: " << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                change_pass(id);
                break;
            case 2:
                add_user();
                break;
            case 3:
                modify_details();
                break;
            case 4:
                delete_details();
                break;
            case 5:
                display_all();
                break;
            case 6:
                display_one();
                break;
            default:
                cout << "Enter correct choice and try again" << endl;
                break;
            }
            break;
        }
    }
    if (!found)
    {
        cout << "\nRecord Not Found!!";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}
void modify_details(void)
{
    string id;
    cout << "Enter the Id of User: ";
    cin >> id;
    cout << endl;
    bool found = false;
    Sepoy obj;
    fstream fl;
    fl.open("sepoy.dat", ios::binary | ios::in | ios::out);
    if (!fl.is_open())
    {
        cout << "File could not be opened. Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    fl.seekg(0, ios::beg);
    while (!fl.eof() && found == false)
    {
        fl.read((char*)(&obj), sizeof(Sepoy));
        if (obj.getsepoy_id() == id)
        {
            obj.getter(); //There is some updation required like officer does not have access to change password of user.
            int pos = (-1) * static_cast<int>(sizeof(obj));
            fl.seekp(pos, ios::cur);
            fl.write((char*)(&obj), sizeof(Sepoy));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    fl.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
    cin.ignore();
    cin.get();
}
void delete_details(void)
{
    Sepoy obj;
    ifstream iFile;
    iFile.open("sepoy.dat", ios::binary | ios::in);
    if (!iFile.is_open())
    {
        cout << "File could not be opened... Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("temp.dat", ios::binary | ios::out);
    iFile.seekg(0, ios::beg);
    oFile.seekp(0, ios::beg);
    string id;
    cout << "Enter the Id: ";
    cin >> id;
    while (iFile.read((char*)(&obj), sizeof(Sepoy)))
    {
        if (obj.getsepoy_id() != id)
        {
            oFile.write((char*)(&obj), sizeof(Sepoy));
        }
    }
    oFile.close();
    iFile.close();
    remove("sepoy.dat");
    rename("temp.dat", "sepoy.dat");
    cout << "\n\n\tRecord Deleted ..";
    cin.ignore();
    cin.get();
}
void display_all(void)
{
    Sepoy obj;
    ifstream inFile;
    inFile.open("sepoy.dat", ios::binary | ios::in);
    if (!inFile.is_open())
    {
        cout << "File could not be opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    inFile.seekg(0, ios::beg);
    cout << "\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
    while (inFile.read((char*)(&obj), sizeof(Sepoy)))
    {
        obj.Display();
        cout << endl;
    }
    inFile.close();
    cin.ignore();
    cin.get();
}
void display_one(void)
{
    string id;
    cout << "Enter the Id: ";
    cin >> id;
    cout << endl;
    Sepoy obj;
    ifstream iFile;
    iFile.open("sepoy.dat", ios::binary | ios::in);
    if (!iFile.is_open())
    {
        cout << "File could not be opened... Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while (iFile.read((char*)(&obj), sizeof(Sepoy)))
    {
        if (obj.getsepoy_id() == id)
        {
            obj.Display();
            flag = true;
            break;
        }
    }
    iFile.close();
    if (flag == false)
        cout << "\n\nrecord does not exist";
    cin.ignore();
    cin.get();
}
