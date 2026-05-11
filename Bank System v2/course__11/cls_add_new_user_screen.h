#pragma once
#include<iostream>
#include<iomanip>
#include"cls_user.h"
#include"cls_input_validate.h"
#include"cls_screen.h"

using namespace std;

class cls_add_new_user_screen : protected cls_screen
{
private:

	static int _read_permissions()
	{
		int per = 0;
		char answer= 'n';
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

		cout << "\nLogin Register ? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			per += cls_user::en_permissions::p_login_register;
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

	static void add_new_user()
	{
		string main = "\t   Add New User";
		string sub =  "\t   ............";
		cls_screen::_draw_screen_header(main, sub, (cls_util::tabs(2)));
		string user_name = " ";
		cout << "\nplease enter user name : ";
		user_name = cls_input_validate::read_string();
		while (cls_user::_is_user_exist(user_name))
		{
			cout << "\nUser Name is already used choose another one :";
			user_name = cls_input_validate::read_string();

		}
		cls_user new_user = cls_user::get_add_new_user_object(user_name);

		_read_user_info(new_user);

		cls_user::en_save_result save_result;

		save_result = new_user.save();

		switch (save_result)
		{
		case cls_bank_client::save_succeeded:
			cout << "\nAccount Addeded Successfuly :-)\n";
			_print_user(new_user);
			break;
		case cls_bank_client::empty_object:
			cout << "\nErroe user name was not saved because it's Empty";
			break;
		case cls_bank_client::account_number_exists:
			cout << "\nThis user name is used ,choose another one";
			break;

		}
	}



};

