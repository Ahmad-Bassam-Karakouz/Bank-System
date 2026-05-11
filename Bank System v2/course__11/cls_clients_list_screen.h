#pragma once
#include<iostream>
#include<iomanip>
#include"cls_bank_client.h"
#include"cls_screen.h"

class cls_clients_list_screen:protected cls_screen
{
private:

	static void _print_client_record_line(cls_bank_client client)

{
	
	cout << "| " << setw(15) << left << client.account_number;
	cout << "| " << setw(23) << left << client.full_name();
	cout << "| " << setw(12) << left << client.phone;
	cout << "| " << setw(30) << left << client.email;
	cout << "| " << setw(10) << left << client.pin_code;
	cout << "| " << setw(12) << left << client.balance;

}

public:

	static  void clients_list()
{

		if (!check_access_rights(cls_user::en_permissions::p_list_client))
		{
			return;
		}

	vector<cls_bank_client> v_clients = cls_bank_client::get_clients_lists();

	string main, sub;
	main = "\t\t\t\t clients list screen";
	 sub = "\t\t\t\t    ("+ to_string(v_clients.size()) +") Client(s)" ;
	
	cls_screen::_draw_screen_header(main, sub,cls_util::tabs(5));
	cout << "\n------------------------------------------------------";
	cout << "-------------------------------------------------------------\n";
	
	cout << "| " << left << setw(15) << "Account number ";
	cout << "| " << left << setw(23) << "Client Name ";
	cout << "| " << left << setw(12) << "Phone ";
	cout << "| " << left << setw(30) << "Email ";
	cout << "| " << left << setw(10) << "Pin code ";
	cout << "| " << left << setw(12) << "Balance ";
	cout << "\n-----------------------------------------------------";
	cout << "--------------------------------------------------------------\n";

	if (v_clients.size() == 0)
	{
		cout << "\t\t\t\t No Clients Available in the System !";
	}
	else
	{
		for (cls_bank_client c : v_clients)
		{
			_print_client_record_line(c);
			cout << endl;
		}

	}
	cout << "-----------------------------------------------------";
	cout << "--------------------------------------------------------------\n";
}

};

