#pragma once
#include<iostream>
#include"cls_bank_client.h"
#include"cls_input_validate.h"
#include"cls_screen.h"
#include"cls_person.h"
#include"cls_util.h"
class cls_delet_client_screen:private cls_screen
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

	static void delete_client()
{
		if (!check_access_rights(cls_user::en_permissions::p_delete_client))
		{
			return;
		}


		string main = "\tDelete Client Screen";
		string sub  = "\t...................."; 
	_draw_screen_header(main,sub,(cls_util::tabs(2)));
	string account_number = " ";
	cout << "\nPlease Enter Account number : ";
	account_number = cls_input_validate::read_string();
	while (!cls_bank_client::_is_client_exist(account_number))
	{
		cout << "\nAccount number is not found, choose another one: ";
		account_number = cls_input_validate::read_string();
	}
	cls_bank_client client = cls_bank_client::find(account_number);
	_print_client(client);
	cout << "\nAre you sure you want to delete this client y/n ? ";
	char answer = 'n';
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		if (client.delete_client())
		{
			cout << "\nclient Deleted Successfully :-)\n";
			_print_client(client);
		}
		else
		{
			cout << "\nError client was not Deleted\n";
		}	
	}

}

};

