#include <iostream>
#include <fstream>              // reading and writing files
#include <string>               //to perform string operations
#include <ctime>                //to get current  date and time
#include <cstdio>               // to rename and remove files
#include <cstring>              //to work with strings
#include "duedate_printter.cpp" //file to get de date

using namespace std;
string role, username;
char str[11];

class Login
{
public:
    string password, un, pw, ro;
    Login() // Default constructor to intialize username and password
    {
        cout << "-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-..-.-.-.-.-\n";
        cout << "\tEnter Username: ";
        cin >> username;
        cout << "\tEnter password: ";
        cin >> password;

        cout << "-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-..-.-.-.-.-\n";
    }
    bool checklogin() // checks if the login details are valid
    {
        // ifstream is used to read a file
        ifstream read(username + ".txt");
        // checking the first three lines of username's file
        getline(read, un); // username
        getline(read, pw); // password
        getline(read, ro); // role
        role = ro;
        if (un == username && pw == password)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
class Register
{
public:
    string word, username, password, role;
    Register() // Default constructor to intialize username and password
    {
        cout << "-----------------------------------------------------------------------\n";
        cout << "\tRegistration" << endl;
        cout << "\tEnter your username: " << endl;
        cin >> username;
        
    }
    void registration()
    {
        fstream f; // fstream is used to read and write into files
        f.open("file_names.txt");
        int flag = 0;
        while (f >> word) // to check if username already existing
        {
            if (word == username)
            {
                flag = 1;
            }
        }
        if (flag == 0)//if username not exist next process will follow
        {
            
            cout << "\tEnter your password: ";
            cin >> password;
            cout << "\tEnter if you are student or staff: ";
            cin >> role;
            cout << "---------------------------------------------------------------------\n";
            // writes into the file and creates if file doesn't exist
            ofstream fl;
            fl.open("file_names.txt", ios_base::app);
            fl << username << endl;
            ofstream outfile;
            outfile.open(username + ".txt", ios_base::app); // to open file in append mode;
            outfile << username << endl;
            outfile << password << endl;
            outfile << role << endl;
            cout << "\tRegistered Successfully" << endl;
            system("cls");
        }
        else
        {
            cout << "\tUsername already exist" << endl//else try other username
                 << endl;
        }
        f.close();
    }
};
class Returnbook;//forward declaration  as we are accessing in this class
class Addbooks
{
public:
    string category, book_name, code;
    int flag = 0;
    string count;
    void get_add(int t) // Default constructor
    {
        flag = t;
        cout << "...................................................\n";
        cout << "\tEnter the category the book belongs to: ";
        getline(cin >> ws, category);
        cout << "\tEnter the code of book: ";
        getline(cin >> ws, code);
        cout << "\tEnter the book name: ";
        getline(cin >> ws, book_name);
        cout << "\tEnter the number of books added:";
        getline(cin >> ws, count);
        cout << "...................................................\n";
    }
    friend void add(Addbooks &, Returnbook &);
};
class Returnbook
{
public:
    string category, code;
    int flag = 0;
    void get_return(int t)
    {
        flag = t;

        cout << "\t------------------------Your books-------------------------" << endl;
        cout << "\tCategory               Code             Due-Date" << endl;
        string detail;
        ifstream fp;
        fp.open(username + ".txt", ios::app);
        int c = 0;
        while (getline(fp, detail))//this while loop will read the category code and 
        {                          //due date and print on screen
            if (c == 5)
            {
                getline(fp, detail);
            }
            if (c >= 3)
            {
                cout << "\t" << detail << "          ";
                if (c == 5)
                    cout << endl;
            }
            if (c == 6)
            {
                c = 3;
            }
            c++;
        }
        cout << "\t\nenter the category of the book" << endl;
        cin >> category;
        cout << "\t\nenter the code of book you want to return " << endl;
        cin >> code;
        

        int f = 0;

        while (f == 0)//to check if wrong code entered
        {
            int choice;
            string word;
            ifstream out;
            out.open(username + ".txt");

            while (getline(out, word))
            {
                if (word == code)
                {
                    f = 1;
                    break;
                }
            }
            if (f == 0)
            {
                cout << "Wrong code  " << endl;
                cout << "1. Enter other code " << endl;
                cout << "Enter the code again carefully!!!" << endl;
                cin >> code;
            }
        }

        fp.close();
        string today;
        string detail1, detail2, dx;

        ifstream fx;
        fx.open(username + ".txt");

        while (getline(fx, dx))
        {
            if (dx == code)
            {
                getline(fx, detail1);
                getline(fx, detail2);
            }
        }
        fx.close();
        cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-` \n";

        string choice;
        int ex;
        int tm;
        cout << "------------------------------------------------------------------------------\n";
        cout << "\tDue date of the book : " << detail2 << endl;
        cout << "\tEnter '1' if not returning on time if not press any key. " << endl;
        cin >> choice;
        if (choice == "1")
        {
            cout << "\tYou have to the fine as you had not returned time:" << endl;
            cout << "\tEnter how many days you exceeded : " << endl;
            cin >> ex;

            cout << "\tPlease pay a fine of $0.5 perday " << endl
                 << endl;

            cout << "\tYou need to pay $" << ((0.5) * ex) << " rupees." << endl;
            // sorcecode dont toch
            cout << "\tIf you are paying online through UPI,press '1'" << endl;

            string x;
            cin >> tm;
            if (tm == 1)
            {
                cout << "$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $\n";
                cout << "\tYour transaction has been initiated :" << endl;
                cout << "\t\tEnter your mobile number : " << endl;
                cin >> x;

                cout << "\t\t Payment detail will be sent to you Pay the fine amount from your mobile application: " << endl
                     << endl;
                cout << "\t\tPayment Done Thank you:):)" << endl;
                cout << "$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $\n";
            }
        }
        
        else
            cout << "\tThank you" << endl;

        cout << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*- \n";
    }
    void del_inuser() // detlete book in user file
    {
        fstream fi;
        string detail;

        fi.open(username + ".txt");
        ofstream out;
        out.open("temp.txt", ios::app);
        while (getline(fi, detail))
        {
            if (detail == category)
            {
                getline(fi, detail);
                getline(fi, detail);
                getline(fi, detail);
                getline(fi, detail);
            }
            out << detail << endl;
        }
        out.close();
        fi.close();
        char char_array[(username + ".txt").length()];
        strcpy(char_array, (username + ".txt").c_str());
        remove(char_array);
        rename("temp.txt", char_array);
    }

    friend void add(Addbooks &, Returnbook &);
};
// function to add book to database after receiving from student
void add(Addbooks &a, Returnbook &r)
{
    string category, code, count;
    if (a.flag > r.flag)
    {
        category = a.category;
        code = a.code;
        count = a.count;
    }
    else
    {
        category = r.category;
        code = r.code;
        count = "1";
    }
    fstream f;
    f.open("all_books.txt");
    string word;
    int c = 0, flag = 0;
    while (f >> word)
    {
        if (word == category)
        {
            c = 1;
        }
    }
    if (c == 0)
    {
        // entering category name into  all_books.txt
        ofstream outfile;
        outfile.open("all_books.txt", ios_base::app);
        outfile << category << endl;
        outfile.close();
    }
    fstream fi;
    int se;
    fi.open(category + ".txt");
    string b;
    string temper;
    int temp, position, size;
    int ci = 0;
    ofstream out;
    out.open("temp.txt", ios_base::app);
    while (getline(fi, b))
    {
        // if entered code is already present in the category count will be increased
        if (flag == 1)
        {
            temp = stoi(b);
            temp += stoi(count);
            temper = to_string(temp);
            out << temper << endl;
            getline(fi, b);
            ci = 1;
            flag = 0;
        }
        // entering every line into a temporary file
        out << b << endl;
        if (b == code)
        {
            flag = 1;
        }
    }
    fi.close();
    out.close();
    if (ci == 0)
    {
        // entering code and book name into the respective category
        ofstream file;
        file.open(category + ".txt", ios_base::app);
        file << code << endl;
        file << count << endl;
        file << a.book_name << endl;
        file.close();
        remove("temp.txt");
    }
    // converting category name into character array to use remove and rename functions
    char char_array[(category + ".txt").length()];
    strcpy(char_array, (category + ".txt").c_str());
    if (ci == 1)
    {
        // renaming temp file with category
        remove(char_array);
        rename("temp.txt", char_array);
    }
}
// add ends

class Takebook; // forward declaration of class
class Deletebooks
{
public:
    string category, code, count;
    int flag = 0;
    void get_delete(int t)
    {
        string detail, book;
        flag = t;
        // xchj

        cout << "Subjects available : " << endl;
        cout << "-- -- -- -- -- -- -- -- -- -- -- -- -- --" << endl;
        ifstream ifs("all_books.txt");
        while (!ifs.eof())
        {
            getline(ifs, book);
            cout << "" << book << "\n";
        }

        int flag = 0, choice;
        cout << "\nEnter category of book you need : " << endl;
        cin >> category;
        while (flag == 0)
        {
            ifstream out;
            out.open("all_books.txt");
            string word;
            while (getline(out, word))
            {
                if (word == category)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                cout << "Entered category is not available " << endl;
                cout << "1. Enter any other category" << endl;
                cout << "2. Don't want to borrow book" << endl;
                cin >> choice;
                if (choice == 2)
                {
                    return;
                }
                if (choice == 1)
                {
                    cout << "Enter the name of category" << endl;
                    cin >> category;
                }
            }
        }
        ifstream f(category + ".txt");
        int temp = 1;
        while (getline(f, detail))
        {
            if (temp > 3)
                temp = 1;
            cout << detail << "    ";
            temp += 1;
            if (temp > 3)
                cout << endl;
        }
        cout << "||-------------------------------||-----------------------------------||\n";
        cout << "\tDelete a book" << endl;
        // cout << "\tenter the category from which the book should be deleted  " << endl;
        // cin >> category;
        cout << "\tenter the code of book to be deleted" << endl;
        cin >> code;
        cout << "\tenter the count of books to be deleted" << endl;
        cin >> count;
        cout << "\n";
        cout << "||-------------------------------||-----------------------------------||\n";
    }
    friend void deleted(Deletebooks &, Takebook &);
};

class Display
{
public:
    void dis()
    {
        fstream f;
        string word;
        string detail;
        f.open("all_books.txt", ios::in);
        if (f.is_open())
        {
            while (getline(f, word))
            {
                fstream file;
                file.open(word + ".txt", ios::in);
                int temp = 1;
                cout << "---------------------------------------" << endl;
                cout << "Category: " << word << endl;
                cout << "Codes   Count   Books" << endl;
                while (getline(file, detail))
                {
                    if (temp > 3)
                        temp = 1;
                    cout << detail << "    ";
                    temp += 1;
                    if (temp > 3)
                        cout << endl;
                }
            }
        }
    }
};
// borrowing and renewal

class Takebook
{
public:
    string book, category, detail, code;
    int flag = 1;
    char date[80];
    void borrow(int t)
    {
        flag = t;
        cout << "Subjects available : " << endl;
        cout << "-- -- -- -- -- -- -- -- -- -- -- -- -- --" << endl;
        cout<<"Categories : "<<endl;
        ifstream ifs("all_books.txt");
        while (!ifs.eof())
        {
            getline(ifs, book);
            cout << "" << book << "\n";
        }

        int flag = 0, choice;
        cout << "\nEnter category of book you need : " << endl;
        cin >> category;
        cout<<"Code          Quantity        Book name "<<endl<<endl;
        while (flag == 0)
        {
            ifstream out;
            out.open("all_books.txt");
            string word;
            while (getline(out, word))
            {
                if (word == category)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                cout << "Entered category is not available " << endl;
                cout << "1. Enter any other category" << endl;
                cout << "2. Don't want to borrow book" << endl;
                cin >> choice;
                if (choice == 2)
                {
                    return;
                }
                if (choice == 1)
                {
                    cout << "Enter the name of category" << endl;
                    cin >> category;
                }
            }
        }
        ifstream f(category + ".txt");
        int temp = 1;
        while (getline(f, detail))
        {
            if (temp > 3)
                temp = 1;
            cout << detail << "           ";
            temp += 1;
            if (temp > 3)
                cout << endl;
        }
        cout << "-- -- -- -- -- -- -- -- -- -- -- -- -- --" << endl;
        cout << "\nEnter the book code carefully : " << endl;
        cin >> code;
    }
    friend void deleted(Deletebooks &, Takebook &);
    void datechange()
    {
        cout << "--------------------------------------------\n"
             << endl;
        ofstream file;
        file.open(username + ".txt", ios_base::app);
        file << category << endl;
        file << code << endl;

        dates(); // gets the todays time
        strcpy(str, buffer);
        strcpy(temp, buffer);

        int d1[3];
        int i = 0;

        char *token = strtok(str, "-"); // spliting the string of date

        while (token != NULL)
        {
            d1[i] = stoi(token); // converting the string to int
            token = strtok(NULL, "-");
            i++;
        }
        file << d1[0] << "-" << d1[1] << "-" << d1[2] << endl; // sending the todays date into file
        int x = 20;

        string h = addDays(d1[0], d1[1], d1[2], x);
        file << h << endl; // sendng due date into file
        cout << endl;
    }
};

// take book class end

void deleted(Deletebooks &d, Takebook &t) // to decrease count of book in library database
{
    string count, category, code;
    if (d.flag > t.flag)
    {
        count = d.count;
        category = d.category;
        code = d.code;
    }
    else
    {
        count = "1";
        category = t.category;
        code = t.code;
    }
    fstream file;
    file.open(category + ".txt");
    string word;
    int c = 3;
    char char_array[(category + ".txt").length()];
    strcpy(char_array, (category + ".txt").c_str());
    int temper;
    string temp;
    if (file.is_open())
    {
        ofstream f;
        f.open("temp.txt", ios::app);

        while (getline(file, word))
        {
            if (word == code)
            {
                temp = word;
                c = 0;
            }
            if (c == 1)
            {

                if (stoi(word) < stoi(count))
                {
                    f.close();
                    remove("temp.txt");
                    break;
                }
                else if (stoi(word) > stoi(count))
                {
                    // temp = stoi(word);
                    f << temp << endl;
                    temper = stoi(word) - stoi(count);
                    f << to_string(temper) << endl;
                    c = 2;
                }
            }
            if (c >= 3)
            {
                f << word << endl;
            }
            c = c + 1;
        }
    }
    file.close();
    remove(char_array);
    rename("temp.txt", char_array);
}

class Display_stu
{
public:
    void get()
    {
        ifstream fp;
        fp.open("file_names.txt");
        string detail;
        cout << "List of students" << endl;
        while (getline(fp, detail))
        {
            cout << detail << endl;
        }
        fp.close();
        int choice;
        cout << "1. To display all records" << endl;
        cout << "2. To display a student's record" << endl;
        cin >> choice;
        ifstream out;
        out.open("file_names.txt");
        string word;
        if (choice == 1)
        {
            cout << "Details of all the students" << endl;
            while (getline(out, detail))
            {
                cout << "------------------------------" << endl;
                cout << "Username: " << detail << endl;
                cout << "Category  Code  Due-Date" << endl;
                ifstream fi;
                fi.open(detail + ".txt");
                int counte = 1, c = 0;
                while (getline(fi, word))
                {
                    if (counte > 3)
                    {
                        cout << word << "  ";
                        c++;
                    }
                    if (c == 4)
                    {
                        cout << endl;
                        c = 0;
                    }
                    counte++;
                }
            }
        }
        if (choice == 2)
        {
            int c = 0;
            cout << "\tenter the student's username to visit their profile" << endl;
            cin >> username;
            ifstream fi;
            fi.open(username + ".txt");
            cout << "--------------------------------" << endl;
            cout << "Username: " << username << endl;
            cout << "Details of the books taken by the student" << endl;
            cout << "Category     Code    Due-Date      Borrow Date" << endl
                 << endl;
            while (getline(fi, detail))
            {
                c++;
                if (detail == username)
                {
                    getline(fi, detail); // getting through each line
                    getline(fi, detail);
                    getline(fi, detail);
                }
                cout << detail << "     ";
                if (c == 3)
                {
                    cout << endl;
                    c = 0;
                }
            }
        }
    }
};
class MyProfile
{
public:
    void display()
    {
        ifstream fp;
        fp.open(username + ".txt");
        string detail;
        cout << "------------------------------------" << endl;
        cout << "Username: " << username << endl;
        cout << "\tCategory               Code             Borrow Date              Due-Date" << endl
             << endl;
        int counte = 1, c = 0;
        while (getline(fp, detail)) // Getting through each line of file
        {
            if (counte > 3)
            {
                cout << "\t" << detail << "          ";
                c++;
            }
            if (c == 4)
            {
                cout << endl;
                c = 0;
            }
            counte++;
        }
    }
};
//Renewal
class Renewal
{
public:
    void displayuser()
    {
        cout << "\t------------------------Your books-------------------------" << endl;
        cout << "\tCategory               Code             Due-Date" << endl;
        string detail;
        ifstream fp;
        fp.open(username + ".txt", ios::app);
        int c = 0;
        while (getline(fp, detail)) // this while loop will read the category code and
        {                           // due date and print on screen
            if (c == 5)
            {
                getline(fp, detail);
            }
            if (c >= 3)
            {
                cout << "\t" << detail << "          ";
                if (c == 5)
                    cout << endl;
            }
            if (c == 6)
            {
                c = 3;
            }
            c++;
        }
        cout << endl;
        fp.close();
    }
    void renew()
    {
        string code;
        cout << "Enter the code of book you want to renew" << endl;
        cin >> code;
        ifstream fi;
        fi.open(username + ".txt");
        string detail, temper;
        ofstream out;
        out.open("temp.txt", ios::app);
        while (getline(fi, detail))
        {
            if (detail == code)
            {
                out << detail << endl;
                getline(fi, detail);
                out << detail << endl;
                getline(fi, detail);
                int n = detail.length(), i = 0, d[3];
                char char_a[n + 1];
                strcpy(char_a, detail.c_str());
                char *token = strtok(char_a, "-");
                while (token != NULL)
                {
                    d[i] = stoi(token);
                    token = strtok(NULL, "-");
                    i++;
                }
                if (d[1] == 12)
                {
                    d[1] = 1;
                }
                else
                {
                    d[1] += 1;
                }
                temper = to_string(d[0]) + "-" + to_string(d[1]) + "-" + to_string(d[2]);
                out << temper << endl;
                getline(fi, detail);
                cout << "Due date is extended by a month" << endl;
                cout << "Updated due-date: " << temper << endl;
            }
            out << detail << endl;
        }
        out.close();
        fi.close();
        char char_array[(username + ".txt").length()];
        strcpy(char_array, (username + ".txt").c_str());
        remove(char_array);
        rename("temp.txt", char_array);
    }
};

int main()
{   cout<<"\n\n===============================================  SRM CENTRAL LIBRARY  ================================================================\n\n";
    int temp = 1;
    cout << "DASHBOARD" << endl;
    string choice;
    cout << "-- -- -- -- -- -- -- -- -- -- -- -- - " << endl
         << endl;
    cout << "\t1. Register " << endl;
    cout << "\t2. Login " << endl;
    cout << "\tEnter your choice" << endl;
    
    cin >> choice;
    if (choice == "1")
    {
        Register r;
        r.registration();
    }
    else if (choice == "2")
    {
        Login l;
        if (l.checklogin())
        {
            while (temp)
            {
                string stac, stuc;
                if (l.ro == "staff")
                {
                    cout << "1. Add Books" << endl;
                    cout << "2. Delete books" << endl;
                    cout << "3. Display books" << endl;
                    cout << "4. Display student records" << endl;
                    cout << "5. Back to Menu" << endl;
                    cout << "6. To exit " << endl;
                }
                else
                {
                    cout << "1. Take a book" << endl;
                    cout << "2. Return a book" << endl;
                    cout << "3. Renewal" << endl;
                    cout << "4. Display books" << endl;
                    cout << "5. My Profile" << endl;
                    cout << "6. Back to Menu" << endl;
                    cout << "7. To exit " << endl;
                }
                if (l.ro == "staff")
                    cin >> stac;

                else
                    cin >> stuc;

                if (stac == "1")
                {
                    char resp = 'y';
                    while (resp == 'y')
                    {
                        Addbooks a;
                        Returnbook r;
                        a.get_add(1);
                        add(a, r);
                        cout << "Enter 'y' if you want to add more books and 'n' if you want to stop" << endl;
                        cin >> resp;
                    }
                }
                if (stuc == "1")
                {
                    Takebook t;
                    Deletebooks d;
                    t.borrow(1);
                    deleted(d, t);
                    t.datechange();
                }
                if (stuc == "2")
                {
                    Returnbook r;
                    Addbooks a;
                    r.get_return(1);
                    add(a, r);
                    r.del_inuser();
                }
                if (stuc == "3")
                {   Renewal e;
                    e.displayuser();
                    e.renew();

    
                }
                if (stac == "2")
                {
                    Deletebooks d;
                    Takebook t;
                    d.get_delete(2);
                    deleted(d, t);
                }
                if (stac == "3" || stuc == "4")
                {
                    cout << "Here is the list of available books with their codes" << endl;
                    Display d;
                    d.dis();
                }
                if (stac == "4")
                {
                    Display_stu d;
                    d.get();
                }
                if (stuc == "5")
                {
                    MyProfile m;
                    m.display();
                }
                if (stac == "5" || stuc == "6")
                {
                    main();
                }
                if (stac == "6" || stuc == "7")
                {
                    temp = 0;
                }
            }
        }

        else
        {
            cout << "Invalid Login" << endl;
            main(); // Returning to main function
        }
    }
    else if (choice == "3")
    {
        temp = 0;
    }
    main();
}
