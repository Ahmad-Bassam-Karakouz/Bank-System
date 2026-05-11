#pragma once
#include<iostream>
#include<iomanip>
#include"cls_input_validate.h"
#include"cls_screen.h"
#include"cls_clients_list_screen.h"
#include"cls_add_new_client_screen.h"
#include"cls_delete_client_screen.h"
#include"cls_update_client_screen.h"
#include"cls_find_client_screen.h"
#include"cls_transactions_screen.h"
#include"cls_manage_users_screen.h"
#include"cls_login_screen.h"
#include"Global.h"
#include"cls_login_register_screen.h"
#include<limits>
#include"cls_currency_exchange_screen.h"
using namespace std;


class cls_main_screen :protected cls_screen
{

private:

	enum en_main_screen{e_list=1,e_add_new=2,e_delete=3,e_update=4,e_find=5,
		                e_transactions=6,e_manage_user=7,e_login_register=8,e_currency_exchange=9,e_logout=10};
	
	static void _show_all_clients_screen()
	{
		cls_clients_list_screen::clients_list();	
			
	}

	static void _show_add_new_client_screen()
	{
		cls_add_new_client_screen::add_new_client();
	}

	static void _show_delete_client_screen()
	{
		cls_delet_client_screen::delete_client();
	}

	static void _show_update_client_screen()
	{
		cls_update_client_screen::update_client();
	}
	
	static void _show_find_client_screen()
	{
		cls_find_client_screen::find_client();
	}
	
	static void _show_transactions_screen()
	{
		cls_transactions_screen::show_transactions_menue();
	}

	static void _show_manage_users_screen()
	{
		cls_manage_users_screen::show_manage_users_menue();
	}

	static void _show_login_register_screen()
	{
		cls_login_register_screen::show_login_register_screen();
	}
	
	static void _show_currency_exchange_screen()
	{
		cls_currency_exchange_screen::_show_currency_exchange_menue();
	}

	static void _logout_screen()
	{
		//cout << "\nlogout will be here...\n";
		_logout();
	}
	
	static void _go_to_back_main_menue()
	{
		//cout << "\n\n\t\tPress any key to go back to main menu...";
		//system("pause>0");		
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
		show_main_menu();
	}

	static short _read_choose()
	{
		short c = 0;
		cout << "\n\t\tEnter your choose from >> [1] to [10] :";
		c = cls_input_validate::read_number_between(1, 10);
		return c;
	}

	static void _logout()
	{
		current_user = cls_user::find("", "");
	}

	static void _perform_main_menue_option(en_main_screen choose)
	{
		switch (choose)
		{
		case cls_main_screen::e_list:
			system("cls");
			_show_all_clients_screen();
			_go_to_back_main_menue();
			break;
		case cls_main_screen::e_add_new:
			system("cls");
			_show_add_new_client_screen();
			_go_to_back_main_menue();
			break;
		case cls_main_screen::e_delete:
			system("cls");
			_show_delete_client_screen();
			_go_to_back_main_menue();
			break;
		case cls_main_screen::e_update:
			system("cls");
			_show_update_client_screen();
			_go_to_back_main_menue();
			break;
		case cls_main_screen::e_find:
			system("cls");
			_show_find_client_screen();
			_go_to_back_main_menue();
			break;
		case cls_main_screen::e_transactions:
			system("cls");
			_show_transactions_screen();
			_go_to_back_main_menue();
			break;
		case cls_main_screen::e_manage_user:
			system("cls");
			_show_manage_users_screen();
			_go_to_back_main_menue();
			break;
		case cls_main_screen::e_login_register:
			system("cls");
			_show_login_register_screen();
			_go_to_back_main_menue();
			break;
		case cls_main_screen::e_currency_exchange:
			system("cls");
			_show_currency_exchange_screen();
			_go_to_back_main_menue();			
		case cls_main_screen::e_logout:
			system("cls");
			_logout_screen();				
			break;		
		}
	}
	
public:

	static void show_main_menu()
	{
		system("cls");
		string main = "\t     Main Screen";
		string sub =  "\t     ...........";
		cls_screen::_draw_screen_header(main,sub,cls_util::tabs(2));
		cout << "\t\t=======================================\n";
		cout << "\t\t[01] show client list.\n";
		cout << "\t\t[02] Add new client.\n";
		cout << "\t\t[03] Delete client.\n";
		cout << "\t\t[04] update client.\n";
		cout << "\t\t[05] Find client.\n";
		cout << "\t\t[06] Transactions.\n";
		cout << "\t\t[07] Manage Users.\n";
		cout << "\t\t[08] login Register.\n";		
		cout << "\t\t[09] Currency Exchange.\n";	
		cout << "\t\t[10] Logout.\n";
		cout << "\t\t=======================================";
		_perform_main_menue_option(en_main_screen(_read_choose()));
	}
	
};

