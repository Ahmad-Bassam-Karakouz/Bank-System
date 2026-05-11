#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include"cls_screen.h"
#include"cls_user.h"
#include"cls_util.h"

using namespace std;

class cls_list_users_screen : protected cls_screen
{
private:

	static void _print_user_record_line(cls_user user)
	{
		cout << "| " << setw(12) << left << user.user_name;
		cout << "| " << setw(25) << left << user.full_name();
		cout << "| " << setw(12) << left << user.phone;
		cout << "| " << setw(30) << left << user.email;
		cout << "| " << setw(10) << left << user.password;
		cout << "| " << setw(12) << left << user.permissions;

	}

public:

	static void show_users_list()
	{
		vector <cls_user> v_users = cls_user::get_users_list();
		string min = "\t\t\t\t   User List Screen";
		string sub = "\t\t\t\t     (" + to_string(v_users.size())+ ")"+" user(s)";
		_draw_screen_header(min, sub, (cls_util::tabs(5)));
		cout << "\n----------------------------------------------------------";
		cout << "-------------------------------------------------------\n";
		cout << "| " << setw(12) << left << "User Name";
		cout << "| " << setw(25) << left << "Full Name";
		cout << "| " << setw(12) << left << "Phone";
		cout << "| " << setw(30) << left << "Email";
		cout << "| " << setw(10) << left << "Password";
		cout << "| " << setw(12) << left << "Permissions";

		cout << "\n----------------------------------------------------------";
		cout << "-------------------------------------------------------\n";

	
		for (cls_user v : v_users)
		{
			_print_user_record_line(v);
			cout << endl;
		}

		cout << "----------------------------------------------------------";
		cout << "-------------------------------------------------------\n";
	}

};

