#pragma once
#include"cls_screen.h"
#include"cls_string.h"
#include"cls_bank_client.h"
#include"cls_util.h"
#include"cls_input_validate.h"
#include"cls_date.h"
#include<iomanip>

class cls_transfer_screen:cls_screen

{
private:

	static void _print_client(cls_bank_client client)
	{
		cout << "\n       client card";
		cout << "\n-----------------------------";
		//cout << "\nfirst name   :" << client.first_name;
		//cout << "\nlast name    :" << client.last_name;
		cout << "\nfull nmae    :" << client.full_name();
		//cout << "\nEmail        :" << client.email;
		//cout << "\nphone        :" << client.phone;
		cout << "\nAcc. number  :" << client.account_number;
		//cout << "\nPassword     :" << client.pin_code;
		cout << "\nBalance      :" << client.balance;
		cout << "\n-----------------------------";

	}

	static string _read_account_number(string message)
	{
		cout << "\n\n" << message;
		string account_number = cls_input_validate::read_string();
		while (!cls_bank_client::_is_client_exist(account_number))
		{
			cout << "\n\nAccount Number is not found !! please enter anohter number:";
			 account_number = cls_input_validate::read_string();
		}
		return account_number;
	}

	static float _read_amount(cls_bank_client client)
	{
		cout << "\n\nEnter Treansfer Amount?";
		float amount = cls_input_validate::read_number<float>("\nEnter Wrong !!\a Enter again");
		while (amount > client.balance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Ammount:";
			amount = cls_input_validate::read_number<float>("\nEnter Wrong !!\a Enter again");
		}
		return amount;
	}
	
public:

	static void show_transfer_screen()
	{
		string main = "\t  Transfer Screen";
		string sub = "\t  ...............";
		_draw_screen_header(main, sub, cls_util::tabs(2));

		cls_bank_client client_from = cls_bank_client::find(_read_account_number("Please Enter Account Number to Transfer From : "));
		_print_client(client_from);
		cls_bank_client client_to = cls_bank_client::find(_read_account_number("Please Enter Account Number to Transfer to : "));
		_print_client(client_to);

		float amount = _read_amount(client_from);

		cout << "\nAre you sure you want to perform this operation? y/n?";
		char answer = 'n';
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			if (client_from.transfer(amount, client_to))
			{
				
				cout << "\nTransfer done successfully\n";
			}
			else
			{
				cout << "\nTransfer Faild \n";
			}
		}
		_print_client(client_from);
		cout << endl;
		_print_client(client_to);
	}
		
};

