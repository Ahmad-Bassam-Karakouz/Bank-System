#pragma once
#include<iostream>
#include"cls_screen.h"
#include"cls_user.h"
#include"cls_util.h"
using namespace std;

class cls_find_user_screen:protected cls_screen
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

	static void find_user()
	{
		string main = "\t   Find User";
		string sub  = "\t   .........";
		_draw_screen_header(main, sub, cls_util::tabs(2));

		string user_name = "";
		cout << "\nEnter User Name Please :";
		cin >> user_name;
		while (!cls_user::_is_user_exist(user_name))
		{
			cout << "\nUser is not found enter another user name:";
			cin >> user_name;
		}
		cls_user user = cls_user::find(user_name);
		_print_user(user);

	}

};

