#pragma once
#include"cls_user.h"
#include"Global.h"
#include<iomanip>
#include<iostream>
#include"cls_main_screen.h"
#include"cls_input_validate.h"
using namespace std;

class cls_login_screen:protected cls_screen
{

private:

	static bool _login()
	{
		bool login_faild = false;

		string user_name, password;
				
		static short counter = 3;

		do
		{
						
			if (login_faild)
			{
				cout << "\nInvlaid User Name / Password !!\n";
				counter--;
				cout << "You have " << counter << " Trial(s) to login.\n";
			}
			if (counter == 0)
			{
				cout << "You are Locked after 3 failed trail(s).\n";
				return false;
			}

			cout << "\n\t\tEnter User Name :";
			user_name= cls_input_validate::read_string();			
			cout << "\n\t\tEnter password :";
			password = cls_input_validate::read_string();

			current_user = cls_user::find(user_name, password);

			login_faild = current_user.is_empty();


		} while (login_faild);
		

		current_user.save_login_process();

		cls_main_screen::show_main_menu();
		

	}

public:

	static bool show_login_screen()
	{
		string main = "\t   Login Screen";
		string  sub = "\t   ............";
		_draw_screen_header(main, sub, cls_util::tabs(2));

		return _login();

	}


};

