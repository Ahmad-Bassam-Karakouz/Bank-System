#pragma once
#include"cls_screen.h"
#include"cls_util.h"
#include<iomanip>
#include<iostream>
#include<string>
#include<string.h>
using namespace std;

class cls_transfer_log_screen:protected cls_screen
{
private:

	static void _print_transfer_record(cls_user::st_transfer_log_info  transfer_log_info)
	{
		cout << "\t| " << left << setw(23) <<  transfer_log_info.time;
		cout << " | " << left << setw(8) <<  transfer_log_info.s_acct;
		cout << " | " << left << setw(8) <<  transfer_log_info.d_acct;
		cout << " | " << left << setw(8) <<  transfer_log_info.amount;
		cout << " | " << left << setw(10) <<  transfer_log_info.s_balance;
		cout << " | " << left << setw(10) <<  transfer_log_info.d_balance;
		cout << " | " << left << setw(8) <<  transfer_log_info.user_name;

	}


public:

	static void show_transfer_log_register()
	{

		vector<cls_user::st_transfer_log_info> v;

		v = cls_user::get_transfer_log_register();

		string main = "\t\t\t Transfer Log List Screen";
		string sub  = "\t\t\t    (" + to_string(v.size()) + ") Record(s)" ;

		_draw_screen_header(main, sub, cls_util::tabs(4));


		cout << "\n \t__________________________________________________";
		cout << "____________________________________________________\n\n";
		cout << "\t| " << left << setw(23) << "     Date/Time";
		cout << " | " << left << setw(8) << " s.Acct";
		cout << " | " << left << setw(8) << " d.Acct";
		cout << " | " << left << setw(8) << " Amount";
		cout << " | " << left << setw(10) << " s.Balance";
		cout << " | " << left << setw(10) << " d.Balance";
		cout << " | " << left << setw(8) <<  " User";
		cout << "\n \t__________________________________________________";
		cout << "____________________________________________________\n\n";
		for (cls_user::st_transfer_log_info c : v)
		{
			_print_transfer_record(c);
			cout << endl;
		}

		cout << " \t__________________________________________________";
		cout << "____________________________________________________\n";
		
	}

};

