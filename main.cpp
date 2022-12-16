#include <iostream>
#include <fstream> // reading and writing files
#include <string>
#include <cstdio> // to rename and remove files
#include <cstring>
using namespace std;
string role, username;
class Login
{
public:
    string password, un, pw, ro;
    Login() // Default constructor to intialize username and password
    {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
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
        cout << "Registration" << endl
             << endl;
        cout << "Enter your username: ";
        cin >> username;
    }
    void registration()
    {
        fstream f; // fstream is used to read and write into files
        f.open("file_names.txt");
        int flag = 0;
        while (f >> word)
        {
            if (word == username)
            {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            cout << "Enter your password: ";
            cin >> password;
            cout << "Enter if you are student or staff: ";
            cin >> role;
            // writes into the file and creates if file doesn't exist
            ofstream fl;
            fl.open("file_names.txt", ios_base::app);
            fl << username << endl;
            ofstream outfile;
            outfile.open(username + ".txt", ios_base::app); // to open file in append mode;
            outfile << username << endl;
            outfile << password << endl;
            outfile << role << endl;
            cout << "Registered Successfully" << endl;
        }
        else
        {
            cout << "Username already exist";
        }
        f.close();
    }
};
class Addbooks
{
public:
    string category,book_name, code;
    string count;
    Addbooks()// Default constructor
    {
        cout << "Enter the category the book belongs to: ";
        getline(cin >> ws, category);
        cout << "Enter the code of book: ";
        getline(cin >> ws, code);
        cout << "Enter the book name: ";
        getline(cin >> ws, book_name);
        cout << "Enter the number of books added:";
        getline(cin >> ws, count);
    }
    void add()
    {
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
            file << book_name << endl;
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
};
class Deletebooks
{
public:
    string category, code, count;
    Deletebooks()
    {
        cout << "delete a book" << endl;
        cout << "enter the category from which the book should be deleted  " << endl;
        cin >> category;
        cout << "enter the code of book to be deleted" << endl;
        cin >> code;
        cout << "enter the count of books to be deleted" << endl;
        cin >> count;
    }
    void deleted()
    {
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
                cout << "-------------------" << endl;
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
    char date[80];


    bool isLeap(int y)
{
	if (y%100 != 0 && y%4 == 0 || y %400 == 0)
		return true;

	return false;
}

int offsetDays(int d, int m, int y)
{
	int offset = d;

	switch (m - 1)
	{
	case 11:
		offset += 30;
	case 10:
		offset += 31;
	case 9:
		offset += 30;
	case 8:
		offset += 31;
	case 7:
		offset += 31;
	case 6:
		offset += 30;
	case 5:
		offset += 31;
	case 4:
		offset += 30;
	case 3:
		offset += 31;
	case 2:
		offset += 28;
	case 1:
		offset += 31;
	}

	if (isLeap(y) && m > 2)
		offset += 1;

	return offset;
}
void revoffsetDays(int offset, int y, int *d, int *m)
{
	int month[13] = { 0, 31, 28, 31, 30, 31, 30,
					31, 31, 30, 31, 30, 31 };

	if (isLeap(y))
		month[2] = 29;

	int i;
	for (i = 1; i <= 12; i++)
	{
		if (offset <= month[i])
			break;
		offset = offset - month[i];
	}

	*d = offset;
	*m = i;
}

    void getdata(int* d,int* m,int* y,int* x)
    {   
        int d1,m1,y1;
        int offset1 = offsetDays(d1, m1, y1);
	int remDays = isLeap(y1)?(366-offset1):(365-offset1);

	int y2, offset2;
	if (*x <= remDays)
	{
		y2 = y1;
		offset2 = offset1 + *x;
	}

	else
	{
		x -= remDays;
		y2 = y1 + 1;
		int y2days = isLeap(y2)?366:365;
		while (*x >= y2days)
		{
			x -= y2days;
			y2++;
			y2days = isLeap(y2)?366:365;
		}
		offset2 = *x;
	}

	int m2, d2;
	revoffsetDays(offset2, y2, &d2, &m2);

	cout<< d2 << "-" << m2 << "-" << y2;
    

    }

    void addays(char date[])
    {
        int x=20;
        int d=date[0]+date[1];
        int m=date[2]+date[3];
        int y=date[4]+date[5]+date[6]+date[7];
        // cout<<"hello \n";
        // cout<<d<<"-"<<m<<"-"<<y<<endl;
        // cout<<"sjbjkvbwbv;kwbv \n";
        getdata(&d,&m,&y,&x);

    }
    void borrow()
    {
        cout << "Subjects available : " << endl;
        cout << "-- -- -- -- -- -- -- -- -- -- -- -- -- --" << endl;
        ifstream ifs("all_books.txt");
        while (!ifs.eof())
        {
            getline(ifs, book);
            cout << "" << book << "\n";
        }
        cout << "\nEnter category of book you need : " << endl;
        cin >> category;
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
        // count--book
        cout << "-- -- -- -- -- -- -- -- -- -- -- -- -- --" << endl;
        cout << "\nEnter the book code carefully : " << endl;
        cin >> code;
        
        ifstream fr(category + ".txt");
        
        int t = 1;
        while (getline(fr, detail))
        {
            if (detail == code)
              { 
                // getline(fr,detail);
                break;
              }
        }
        //decreasing count
        //  fstream fi;
        // int se,flag;
        // fi.open(category + ".txt");
        // string b,count;
        // string temper;
        // int tx, position, size;
        // int ci = 0;
        // ofstream out;
        // out.open("tx.txt", ios_base::app);
        // while (getline(fi, b))
        // {
        //     // if entered code is already present in the category count will be increased
        //     if (flag == 1)
        //     {
        //         tx = stoi(b);
        //         tx += stoi(count);
        //         temper = to_string(tx);
        //         out << temper << endl;
        //         getline(fi, b);
        //         ci = 1;
        //         flag = 0;
        //     }
        //     // entering every line into a temporary file
        //     out << b << endl;
        //     if (b == code)
        //     {
        //         flag = 1;
        //     }
        // }
        // fi.close();
        // out.close();
      
        // char char_array[(category + ".txt").length()];
        // strcpy(char_array, (category + ".txt").c_str());
        // if (ci == 1)
        // {
        //     // renaming temp file with category
        //     remove(char_array);
        //     rename("temp.txt", char_array);
        // }

        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^ :) ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
        ofstream file;
        file.open(username + ".txt", ios_base::app);
        file << detail << endl;
        cout << "Enter todays Date in ddmmyy format : ";
        cin >> date;
        file << date << endl;
        cout<<"start : \n";
        addays(date);
        cout<<"\n end : \n";
        
        cout << "DUE FATE : 20 days from now" << endl;

        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ :) ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
    }
};
class Renewal
{
public:
    string read, code, dat, dut, temp;
    void renewbook()
    {
        cout << "Enter book code :" << endl;
        cin >> code;
        // todays dateinput
        ifstream ofs(username + ".txt");
        while (getline(ofs, read))
        {
            if (read == code)
            {
                getline(ofs, dat);
                break;
            }
        }
        // string to
        // check the date if greater than limit
    }
};
int main()
{
    int temp = 1;
    cout << "DASHBOARD" << endl;
    int choice;
    cout << "-- -- -- -- -- -- -- -- -- -- -- -- - " << endl;
    cout << "1. Register " << endl;
    cout << "2. Login " << endl;
    cout << "Enter your choice" << endl;
    cin >> choice;
    if (choice == 1)
    {
        Register r;
        r.registration();
    }
    else if (choice == 2)
    {
        Login l;
        if (l.checklogin())
        {
           // while (temp)
            //{   
                int stac,stuc;
                if (l.ro == "staff")
                {
                    cout << "1. Add Books" << endl;
                    cout << "2. Delete books" << endl;
                    cout << "3. Display books" << endl;
                    cout << "4. Back to Menu" << endl;
                    cout << "5. To exit " << endl;
                }
                else
                {
                    cout << "1. Take a book" << endl;
                    cout << "2. Return a book" << endl;
                    cout << "3. Renewal" << endl;
                    cout << "4. Display books" << endl;
                    cout << "5. Back to Menu" << endl;
                    cout << "6. To exit " << endl;
                }
                if (l.ro == "staff")
                    cin >> stac;
                else
                    cin >> stuc;
                if (stac == 1)
                {
                    char resp = 'y';
                    while (resp == 'y')
                    {
                        Addbooks a;
                        a.add();
                        cout << "If you want to add more book, enter 'y' else enter 'n'";
                        cin >> resp;
                    }
                }
                if (stuc == 1)
                {
                    Takebook t;
                    t.borrow();
                }
                if (stuc == 2)
                {
                    Renewal r;
                    r.renewbook();
                }
                if (stuc == 3)
                {
                }
                if (stac == 2)
                {
                    Deletebooks d;
                    d.deleted();
                }
                if (stac == 3 || stuc == 4)
                {
                    cout << "Here is the list of available books with their codes" << endl;
                    Display d;
                    d.dis();
                }
                if (stac == 4 || stuc == 5)
                {
                    main();
                }
                if (stac == 5 || stuc == 6)
                {
                    temp = 0;
                }
           // }
        }
        else
        {
            cout << "Invalid Login" << endl;
            main();
        }
    }
    else if (choice == 3)
    {
        temp = 0;
    }
}
