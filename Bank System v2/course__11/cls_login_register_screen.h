#pragma once
#include"cls_screen.h"
#include<iomanip>

class cls_login_register_screen:protected cls_screen
{
private:

	static void _print_login_register_record_line(cls_user::st_login_register_info login)
	{
		cout << "\t| " << setw(22) << left << login.time;
		cout << "\t| " << setw(20) << left << login.user_name;
		cout << "\t| " << setw(20) << left << login.password;
		cout << "\t| " << setw(10) << left << login.permissions;

	}

public:

	static void show_login_register_screen()
	{

		if (!check_access_rights(cls_user::en_permissions::p_login_register))
		{
			return;
		}


		vector<cls_user::st_login_register_info> v = cls_user::get_login_register();

		string main = "\t\t\tLogin Register List Screen";
		string sub = "\t\t\t\t  (" + to_string(v.size()) + ")";

		_draw_screen_header(main, sub,cls_util::tabs(4));

		cout << "\t-------------------------------------------------";
		cout << "-------------------------------------------------\n";
		cout << "\t| " << left << setw(22) << "Date/Time";
		cout << "\t| " << left << setw(20) << "User Name";
		cout << "\t| " << left << setw(20) << "Password";
		cout << "\t| " << left << setw(10) << "Permissions";
		cout << "\n\t------------------------------------------------";
		cout << "--------------------------------------------------\n";

		if (v.size() == 0)
		{
			cout << "\n\t\t\t\tNo Logins Available in the System \n";
		}

		for (cls_user::st_login_register_info c : v)
		{
			_print_login_register_record_line(c);
			cout << endl;
		}
		cout << "\t-------------------------------------------------";
		cout << "-------------------------------------------------\n";

	}

};

