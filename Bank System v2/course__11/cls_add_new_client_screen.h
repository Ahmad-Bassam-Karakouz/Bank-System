#pragma once
#include<iostream>
#include"cls_bank_client.h"
#include"cls_screen.h"
#include"cls_input_validate.h"
#include"cls_util.h"
class cls_add_new_client_screen:protected cls_screen
{
private:

	static void _print_client(cls_bank_client client)
	{
		cout << "\n       client card";
		cout << "\n-----------------------------";
		cout << "\nfirst name   :" << client.first_name;
		cout << "\nlast name    :" << client.last_name;
		cout << "\nfull nmae    :" << client.full_name();
		cout << "\nEmail        :" << client.email;
		cout << "\nphone        :" << client.phone;
		cout << "\nAcc. number  :" << client.account_number;
		cout << "\nPassword     :" << client.pin_code;
		cout << "\nBalance      :" << client.balance;
		cout << "\n-----------------------------";

	}		
	
	static void read_client_info(cls_bank_client& client)
	{
		cout << "\nEnter first name:";
		client.first_name = cls_input_validate::read_string();
		cout << "\nEnter last name:";
		client.last_name = cls_input_validate::read_string();
		cout << "\nEnter Email:";
		client.email = cls_input_validate::read_string();
		cout << "\nEnter phone:";
		client.phone = cls_input_validate::read_string();
		cout << "\nEnter pin code:";
		client.pin_code = cls_input_validate::read_string();		
		//cout << "\nEnter Account balance:";
		//client.balance = cls_input_validate::read_number<double>();
	
	}

public:
	
	static void add_new_client()
{
		if (!check_access_rights(cls_user::en_permissions::p_add_new_client))
		{
			return;
		}

		string main ="\t    Add New Client";
		string sub = "\t    ..............";
		cls_screen::_draw_screen_header(main,sub,(cls_util::tabs(2)));
	string account_number = " ";
	cout << "\nplease enter account number : ";
	account_number = cls_input_validate::read_string();
	while (cls_bank_client::_is_client_exist(account_number))
	{
		cout << "\nAccount number is already used choose another one :";
		account_number = cls_input_validate::read_string();

	}
	cls_bank_client new_client = cls_bank_client::get_add_new_client_project(account_number);

	read_client_info(new_client);

	cls_bank_client::en_save_result save_result;

	save_result = new_client.save();

	switch (save_result)
	{
	case cls_bank_client::save_succeeded:
		cout << "\nAccount Addeded Successfuly :-)\n";
		_print_client(new_client);
		break;
	case cls_bank_client::empty_object:
		cout << "\nErroe account was not saved because it's Empty";
		break;
	case cls_bank_client::account_number_exists:
		cout << "\nThis account number is used ,choose another one";
		break;

	}
}

};

