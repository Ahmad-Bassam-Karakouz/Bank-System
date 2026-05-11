#pragma once
#include<iostream>
#include"cls_person.h"
#include"cls_screen.h"
#include"cls_user.h"
#include"cls_input_validate.h"
#include"cls_util.h"
using namespace std;

class cls_delete_user_screen: protected cls_screen
{
private:

	static void _print_user(cls_user user)
	{
		cout << "\n       user card";
		cout << "\n-----------------------------";
		cout << "\nuser name    :" << user.user_name;
		cout << "\nfull nmae    :" << user.full_name();
		cout << "\nEmail        :" << user.email;
		cout << "\nphone        :" << user.phone;
		cout << "\nPassword     :" << user.password;
		cout << "\npermissions  :" << user.permissions;
		cout << "\n-----------------------------\n";

	}


public:

	static void delete_user()
	{
		string min = "\t    Delete User";
		string sub = "\t    ...........";
		_draw_screen_header(min, sub,(cls_util::tabs(2)));

		string user_name = "";
		cout << "\nPlease Enter UserName :";
		cin >> user_name;
		while (!cls_user::_is_user_exist(user_name))
		{
			cout << "\nThis user is not found tray again please:";
			cin >> user_name;
		}
		cls_user user = cls_user::find(user_name);
		_print_user(user);

		char answer = 'n';
		cout << "Are you sure you want to delete this user? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			if (user.delete_client())
			{
				cout << "\nUser Deleted Successfully :-)\n";
				_print_user(user);
			}
			else
			{
				cout << "\nError User Was not Deleted\n";
			}
		}
	}

};

