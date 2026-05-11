#pragma once
#include<iostream>
#include"cls_screen.h"
#include"cls_util.h"
#include"cls_input_validate.h"
#include"cls_main_screen.h"
#include"cls_bank_client.h"
#include"cls_transfer_screen.h"
#include"cls_transfer_log_screen.h"
using namespace std;


class cls_transactions_screen:protected cls_screen
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
	
	static void _print_client_record_balance_liene(cls_bank_client client)
	{
		cout << "| " << setw(15) << left << client.account_number;
		cout << "| " << setw(40) << left << client.full_name();
		cout << "| " << setw(12) << left << client.balance;

	}

	static void _print_total_balance()
	{
		vector<cls_bank_client> v_clients = cls_bank_client::get_clients_lists();

		cout << "\n \t\t\tClients Lists (" << v_clients.size() << ") client(s).";
		cout << "\n-----------------------------------------";
		cout << "-------------------------------------------\n";
		cout << "| " << left << setw(15) << "Account number ";
		cout << "| " << left << setw(40) << "Client Name ";
		cout << "| " << left << setw(12) << "Balance ";
		cout << "\n-----------------------------------------";
		cout << "-------------------------------------------\n";

		if (v_clients.size() == 0)
		{
			cout << "\t\t\t\t No Clients Available in the System !";
		}
		else
		{
			for (cls_bank_client c : v_clients)
			{
				_print_client_record_balance_liene(c);
				cout << endl;
			}

		}
		cout << "-------------------------------------------";
		cout << "-----------------------------------------\n";

		double total_balance = cls_bank_client::get_total_balance(v_clients);
		cout << "\nTotal Balances  =  " << total_balance ;
		string total_balance_txt = cls_util::convert_number_to_txt(total_balance);
		cout << " ( " << total_balance_txt <<").\n";



	}
		
	enum en_transactions{e_deposit=1,e_withdraw=2,e_total_balance=3,e_treansfer,e_transfer_log=5,e_main_menue=6};

	static void _show_deposit_screen()
	{
		string main="\t   Deposit Screen";
		string sub ="\t   ..............";
		_draw_screen_header(main, sub,cls_util::tabs(2));
		string account_number = "";
		cout << "\nplease enter client Account number : ";
		account_number = cls_input_validate::read_string();

		while (!cls_bank_client::_is_client_exist(account_number))
		{
			cout << "\nAccount number is not found, choose another one :";
			account_number = cls_input_validate::read_string();

		}
		cls_bank_client client = cls_bank_client::find(account_number);
		_print_client(client);
		double amount = 0;
		cout << "\nPlease enter deposit amount ? ";
		amount = cls_input_validate::read_number<double>();
		cout << "\nAre you sure you want to perform this transaction [y/n] ? ";		 
		char answer = 'n';
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			client.deposit(amount);
			cout << "\nAmount Deposit successfully \n";
			cout << "\nNew Balance is " << client.balance << " \n";
		}
		else
		{
			cout << "\nOperation was cancelled\n";
		}
	}

	static void _show_withdraw_screen()
	{
		string main = "\t   Withdraw Screen";
		string sub =  "\t   ...............";
		_draw_screen_header(main, sub,cls_util::tabs(2));
		string account_number = "";
		cout << "\nplease enter client Account number : ";
		account_number = cls_input_validate::read_string();

		while (!cls_bank_client::_is_client_exist(account_number))
		{
			cout << "\nAccount number is not found, choose another one :";
			account_number = cls_input_validate::read_string();

		}
		cls_bank_client client = cls_bank_client::find(account_number);
		_print_client(client);
		double amount = 0;
		cout << "\nPlease enter withdraw amount ? ";
		amount = cls_input_validate::read_number<double>();
		cout << "\nAre you sure you want to perform this transaction [y/n] ? ";
		char answer = 'n';
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			if (client.withdraw(amount))
			{
				cout << "\nAmount withdraw successfully \n";
				cout << "\nNew Balance is " << client.balance << " \n";
			}
			else
			{
				cout << "\nCannot withdraw, Insuffecient Balance!\n";
				cout << "\nAmount to withdraw is :" << amount;
				cout << "\nAmount current is :" << client.balance << endl;
			}
			
		}
		else
		{
			cout << "\nOperation was cancelled\n";
		}
	}

	static void _show_total_balance_screen()
	{
		_print_total_balance();
	}
	
	static void _show_transfer_screen()
	{
		//cout << "\nTransfer screen will be here.\n\n";
		cls_transfer_screen::show_transfer_screen();
	}

	static void _show_transfer_log_screen()

	{
		//cout <<"\n\t\tTransfer log screen will be here\n\n";
		cls_transfer_log_screen::show_transfer_log_register();
	}

	static void _go_to_back_transactions_menue()
	{
		
		//cout << "\n\n\t\tPress any key to go back to main menu...";		
		//system("pause>0");
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
		show_transactions_menue();
	}

	static short _read_choose()
	{
		short c = 0;
		cout << "\n\t\tChoose want do you want to do [1 to 6]?";
		c = cls_input_validate::read_number_between<short>(1, 6);
		return c;
	}

	static void  _perform_main_menue_option(en_transactions choose)
	{
		switch (choose)
		{
		case cls_transactions_screen::e_deposit:
			system("cls");
			_show_deposit_screen();
			_go_to_back_transactions_menue();
			break;
		case cls_transactions_screen::e_withdraw:
			system("cls");
			_show_withdraw_screen();
			_go_to_back_transactions_menue();
			break;
		case cls_transactions_screen::e_total_balance:
			system("cls");
			_show_total_balance_screen();
			_go_to_back_transactions_menue();
			break;
		case cls_transactions_screen::e_treansfer:
			system("cls");
			_show_transfer_screen();
			_go_to_back_transactions_menue();
			break;
		case cls_transactions_screen::e_transfer_log:
			system("cls");
			_show_transfer_log_screen();
			_go_to_back_transactions_menue();
			break;
		case cls_transactions_screen::e_main_menue:			
			break;
				
		}
	}

public:

	static void show_transactions_menue()
	{
		if (!check_access_rights(cls_user::en_permissions::p_transactions))
		{
			return;
		}


		system("cls");
		string main = "\tTransactions Menue";
		string sub =  "\t...................";
		cls_screen::_draw_screen_header(main,sub,cls_util::tabs(2));
		cout << "\n\t\t=======================================\n";
		cout << "\t\t[1] Deposit.\n";
		cout << "\t\t[2] Withdraw.\n";
		cout << "\t\t[3] Total Balances.\n";
		cout << "\t\t[4] Transfer.\n";
		cout << "\t\t[5] Transfer Log.\n";
		cout << "\t\t[6] Main Menue.\n";
		cout << "\t\t=======================================\n";
		_perform_main_menue_option(en_transactions(_read_choose()));

	}

};

