#pragma once
#include<iostream>
#include<iomanip>
#include"cls_screen.h"
#include"cls_user.h"
#include"cls_input_validate.h"
#include"cls_util.h"
using namespace std;

class cls_update_user_screen:protected cls_screen
{

private:

	static int _read_permissions()
	{
		int per = 0;
		char answer = 'n';
		cout << "\nDo you want to dive full access? y/n?";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			return -1;
		}
		cout << "\nDo you want to give access to:\n";

		cout << "\nShow Client List? y/n?";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			per += cls_user::en_permissions::p_list_client;
		}

		cout << "\nAdd new client ? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			per += cls_user::en_permissions::p_add_new_client;
		}

		cout << "\nUpdate client ? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			per += cls_user::en_permissions::p_update_client;
		}

		cout << "\nDelete client ? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			per += cls_user::en_permissions::p_delete_client;
		}

		cout << "\nFind client ? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			per += cls_user::en_permissions::p_find_client;
		}

		cout << "\nTransactions ? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			per += cls_user::en_permissions::p_transactions;
		}

		cout << "\nManage Users ? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			per += cls_user::en_permissions::p_manage_user;
		}

		return per;
	}

	static void _read_user_info(cls_user& user)
	{
		cout << "\nEnter First Name:";
		user.first_name = cls_input_validate::read_string();
		cout << "\nEnter Last Name:";
		user.last_name = cls_input_validate::read_string();
		cout << "\nEnter Phone:";
		user.phone = cls_input_validate::read_string();
		cout << "\nEnter Email:";
		user.email = cls_input_validate::read_string();
		cout << "\nEnter Password:";
		user.password = cls_input_validate::read_string();
		cout << "\nEnter Permissions:";
		user.permissions = _read_permissions();
	}

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

	static void update_user()
	{
		string main = "\t      Update User";
		string sub =  "\t      ...........";
		_draw_screen_header(main, sub, cls_util::tabs(2));

		string user_name = "";
		cout << "\nEnter User Name Please :";
		cin >> user_name;
		while (!cls_user::_is_user_exist(user_name))
		{
			cout << "\nUser is not found try again please:";
			cin >> user_name;
		}
		cls_user user = cls_user::find(user_name);
		_print_user(user);

		char answer = 'n';
		cout << "\nAre you sure do you want to update user informtions? y/n?";
		cin >> answer;
		cout << "\n\n";
		if (answer == 'y' || answer == 'Y')
		{
			_read_user_info(user);
			char an = 'n';
			cout << "\nAre you sure do you want to update user informtions? y/n?";
			cin >> an;
			if (an == 'y' || an == 'Y')
			{
				cls_user::en_save_result result;
				result = user.save();
				switch (result)
				{
				case cls_user::save_succeeded:
					cout << "\nUser update Successfully :-)\n";
					break;
				case cls_user::empty_object:
					cout << "\nError User was not saved because it's empty";
					break;
			
				}
			}
		}
	}

};

