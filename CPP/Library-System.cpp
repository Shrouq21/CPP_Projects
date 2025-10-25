#include<vector>
#include<algorithm>
#include<iostream>
//#define _CRT_SECURE_NO_WARNINGS   if you will use scanf to avoid warnings but in c++14 you cant use scanf
#include<stdio.h>
#include<string>
#include<sstream>
#include<map>
//#include<bits/stdc++.h>
//string status = "";
using namespace std;

struct book
{
	string name;
	int id, quantity;

};
struct user
{
	string name;
	int id;
	vector<string>borrowd_books;
	vector<string>returned_books;

};
vector<book>list_books;
vector<user>list_users;
void add_user(string name, int id)
{
	bool chk = 0;
	for (auto& i : list_users)
	{
		if (i.name == name)
		{
			cout << "You are already existed\n";
			chk = 1;
			break;
		}
	}
	if (!chk)list_users.push_back({ name,id });
}
vector<string>who_borrow(string book)
{
	vector<string>names;
	for (auto& i : list_users)
	{
		for (auto& k : i.borrowd_books) {
			if (book == k)
			{
				names.push_back(i.name);
			}
		}
	}
	return names;
}
void borrow_book(string name, int id,string book)
{
	bool chk_book = 0;
	for (auto& i : list_users)
	{
		if (i.name == name && i.id == id)
		{
			for (auto& k : list_books)
			{
				if (k.name == book)
				{
					chk_book = 1;
					if (k.quantity > 0)
					{
						i.borrowd_books.push_back(book);
						k.quantity--;
					}
					else
						cout << "There is no rest of copies\n";
				}
			}
			if (!chk_book)
			{
				cout << "There is no book with this name\n";
			}
		}
	}
}
void returned_book(string name, int id, string book)
{
	bool chk_user = 0;
	bool chk_book = 0;
	for (auto& i : list_users)
	{
		if (i.name == name && i.id == id)
		{
			chk_user = 1;
			for (auto& k : list_books)
			{
				if (k.name == book)
				{
					chk_book = 1;
					k.quantity++;
				}
			}
			if (!chk_book)
			{
				cout << "Please check your data\n";
			}
		}
	}
}
void add_book(string name,int id,int quantity)
{
	/*books[name].id = id;
	books[name].quantity += quantity;
	books[name].name = name;*/
	bool chk = 0;
	for (auto &i : list_books)
	{
		if (i.name == name)
		{
			i.id = id;
			i.quantity += quantity;
			chk = 1;
		}
	}
	if (!chk)
	{
		list_books.push_back({ name,id,quantity });
	}
}
vector<string>searching_book(/*const map<string, book>& b,*/const string& prefix)
{vector<string>result;
	for (auto& pair : list_books)
	{
		string name = pair.name;
		if (name.find(prefix) == 0)
		{
			result.push_back(name);
		}
		
	}
	return result;
}
bool sorting_id(book b1, book b2)
{
	if(b1.id!=b2.id)
	return  b1.id < b2.id;
	return b2.name < b1.name;
}
bool sorting_names(book b1, book b2)
{
	if (b1.name != b2.name)
		return b1.name < b2.name;
	return b2.name<b1.name;

}
void run(){
	int choice; 
	while (true)
	{
		cout << "Library Menu;\n"
			<< "1) add_book\n"
			<< "2) search_books_by_prefix\n"
			<< "3) print_who_borrowed_book_by_name\n"
			<< "4) print_library_by_id\n"
			<< "5) print_library_by_name\n"
			<< "6) add_user\n"
			<< "7) user_borrow_book\n"
			<< "8) user_return_book\n"
			<< "9) print_users\n"
			<< "10)print_books\n"
			<< "11) Exit\n";
		cout <<"Enter your menu choice [1-10]:";
		cin >> choice;
		if (choice == 1)
		{
			string name;
			int id, quantity;
			cout << "Please enter:\n"
				<< "name: ";
			cin >> name;
			cout << "Id: ";
			cin >> id;
			cout << "Quantity: ";
			cin >> quantity;

			add_book(name, id, quantity);
		}
		else if (choice == 2)
		{
			string prefix; cin >> prefix;
			vector<string>match;
			match = searching_book(prefix);
			if (match.empty())
			{
				cout << "Nothing\n";
			}
			else
			{
				for (auto& i : match)
				{
					cout << i << "\n";
				}
			}
		}
		else if (choice == 3)
		{
			cout << "Book_Name: ";
			string book; cin >> book;
			vector<string>who = who_borrow(book);
			for (auto& i : who)
			{
				cout << i << endl;
			}
		}
		else if (choice == 4)
		{
			sort(list_books.begin(), list_books.end(), sorting_id);
			cout << "Books based on Id\n";
			for (auto& x : list_books)
			{
				cout << x.name << "\n";
			}
		}
		else if (choice == 5)
		{
			sort(list_books.begin(), list_books.end(), sorting_names);
			cout << "Books based on Names: ";
			for (auto& x : list_books)
			{
				cout << x.name << "\n";
			}
		}
		else if (choice == 6)
		{
			cout << "Enter the Name and Id\n";
			string name; int id; cin >> name >> id;
			add_user(name, id);
		}
		else if (choice == 7)
		{
			cout << "Enter the Name and Id\n";
			string name, book; int id;
			cin >> name >> id;
			bool chk_user = 0;
			for (auto& i : list_users)
			{
				if (i.name == name && i.id == id)
				{
					cout << "Ok, Enter the name of the book you want borrow:";
					cin >> book;
					chk_user = 1;
					break;
				}
			}
			if (chk_user)
				borrow_book(name, id, book);
			else
				cout << "Sorry, You didn't regiseter yet\n";
		}
		else if (choice == 8)
		{
			cout << "Enter the Name and Id\n";
			string name, book; int id;
			cin >> name >> id;
			bool chk_user = 0;
			for (auto& i : list_users)
			{
				if (i.name == name && i.id == id)
				{
					cout << "Ok, Enter the name of the book you want return";
					cin >> book;
					chk_user = 1;
					break;
				}
			}
			if (chk_user)
				borrow_book(name, id, book);
			else
				cout << "Check your Name and Id\n";
		}
		else if (choice == 9)
		{
			if (!list_users.empty())
			{
				cout << "User Info: \n";
				for (auto& i : list_users)
				{
					cout << "Name: " << i.name << " Id:" << i.id << "\n";
				}
			}
			else
				cout << "There is no users\n";
		}
		else if (choice == 10)
		{
			if (!list_books.empty())
			{
				cout << "User Info: \n";
				for (auto& i : list_books)
				{
					cout << "Name:" << i.name << " Id: " << i.id << " Quantity: " << i.quantity << "\n";
				}
			}
			else
				cout << "There is no books\n";
		}
		else if(choice==11)
			break;
		else
			cout << "Try Again\n";
	}
}
int main()
{
	run();
}