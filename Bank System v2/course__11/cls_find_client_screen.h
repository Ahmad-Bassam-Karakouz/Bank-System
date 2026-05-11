#pragma once
#include<iostream>
#include"cls_screen.h"
#include"cls_bank_client.h"
#include"cls_bank_client.h"
#include"cls_input_validate.h"
using namespace std;

class cls_find_client_screen:protected cls_screen
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

public:
	
	static void find_client()
	{
		if (!check_access_rights(cls_user::en_permissions::p_find_client))
		{
			return;
		}

		string main = "\t      Find Client";
		string sub =  "\t      ...........";
		_draw_screen_header(main, sub,(cls_util::tabs(2)));

		string account_number = "";
		cout << "\nplease enter client Account number : ";
		account_number = cls_input_validate::read_string();

		while (!cls_bank_client::_is_client_exist(account_number))
		{
			cout << "\nAccount number is not found, choose another one :";
			account_number = cls_input_validate::read_string();

		}
		cls_bank_client client = cls_bank_client::find(account_number);
		if (!client.is_empty())
		{
			cout << "\n Client found :-)\n";
		}
		else
		{
			cout << "\n Client is not fond :-(\n";
		}
		_print_client(client);

	}


};

