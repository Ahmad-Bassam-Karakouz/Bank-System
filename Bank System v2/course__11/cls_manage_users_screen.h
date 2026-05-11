#pragma once
#include<iostream>
#include <iomanip>
#include"cls_screen.h"
#include"cls_input_validate.h"
#include"cls_util.h"
#include"cls_list_users_screen.h"
#include"cls_add_new_user_screen.h"
#include"cls_update_user_screen.h"
#include"cls_find_user_screen.h"
#include"cls_delete_user_screen.h"
using namespace std;

class cls_manage_users_screen: protected cls_screen 
{
private:

	enum en_manage_users{e_list_users=1,e_add_new=2,e_delet=3,e_update=4,e_find=5,e_main_menue=6};

	static short _read_user_option()
	{
		short c = 0;
		cout << "\n\t\tplease enter your option  >> from [1] to [6] ? ";
		c = cls_input_validate::read_number_between<short>(1, 6);
		return c;
	}

	static void _go_to_manage_users_menue()
	{
		//cout << "go to back to manage users menue will be here...\n";
		//cout << "\n\n\t\tPress any key to go back to manage users menu...";
		//system("pause>0");
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
		show_manage_users_menue();
	}

	static void _show_list_users_screen()
	{
		//cout << "list users screen will be here...\n";
		cls_list_users_screen::show_users_list();
	}

	static void _show_add_new_user_screen()
	{
		//cout << "add new user will be here...\n";
		cls_add_new_user_screen::add_new_user();
	}

	static void _show_delete_user_screen()
	{
		//cout << "delete user will be here...\n";
		cls_delete_user_screen::delete_user();
	
	}

	static void _show_update_user_screen()
	{
		//cout << "update user will be here...\n";
		cls_update_user_screen::update_user();
	}

	static void _show_find_user_screen()
	{
		//cout << "find user will be here...\n";
		cls_find_user_screen::find_user();
	}

	static void _perform_manage_users_menue_option(en_manage_users option)
	{
		switch (option)
		{
		case cls_manage_users_screen::e_list_users:
			system("cls");
			_show_list_users_screen();
			_go_to_manage_users_menue();
			break;
		case cls_manage_users_screen::e_add_new:
			system("cls");
			_show_add_new_user_screen();
			_go_to_manage_users_menue();
			break;
		case cls_manage_users_screen::e_delet:
			system("cls");
			_show_delete_user_screen();
			_go_to_manage_users_menue();
			break;
		case cls_manage_users_screen::e_update:
			system("cls");
			_show_update_user_screen();
			_go_to_manage_users_menue();
			break;
		case cls_manage_users_screen::e_find:
			system("cls");
			_show_find_user_screen();
			_go_to_manage_users_menue();
			break;
		case cls_manage_users_screen::e_main_menue:
			
			break;
		
		}
	}


public:

	static void show_manage_users_menue()
	{
		if (!check_access_rights(cls_user::en_permissions::p_manage_user))
		{
			return;
		}

		system("cls");
		string main = "\t Manage Users Screen";
		string sub =  "\t ...................";
		_draw_screen_header(main, sub,cls_util::tabs(2));

		cout << "\n\t\t=======================================\n";
		cout << "\t\t\t Manage Users Menue\n";
		cout << "\t\t=======================================\n";
		cout << "\t\t[1] List Users.\n";
		cout << "\t\t[2] Add New User.\n";
		cout << "\t\t[3] Delete User.\n";
		cout << "\t\t[4] Update User.\n";
		cout << "\t\t[5] Find User.\n";
		cout << "\t\t[6] Main Menue.\n";
		cout << "\t\t=======================================\n";
		_perform_manage_users_menue_option(en_manage_users(_read_user_option()));
	}

};

