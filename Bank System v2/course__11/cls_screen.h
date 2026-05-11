#pragma once
#include<iostream>
#include"cls_bank_client.h"
#include"cls_user.h"
#include"Global.h"
#include"cls_date.h"

class cls_screen
{
protected:

	static  void _draw_screen_header(string title,string sub_title = " ", string tips =" ")
	{
		cout << tips << "_______________________________________\n\n";
		cout << "\t\t" << title;		
		if (sub_title != " ")
		{
			cout << "\n\t\t" << sub_title;
		}
		cout <<"\n" << tips << "_______________________________________\n\n";
		cout << tips << "User:"<< current_user.user_name<< "\n";
		cout << tips << "Date:" << cls_date::date_to_string(cls_date());
		cout << "\n\n";
		
	}
	
	static bool check_access_rights(cls_user::en_permissions permission)
	{
		if (!(current_user.check_access_permission(permission)))
		{
			cout << "\t\t\------------------------------------------------";
			cout << "\n\n\t\t      Access Denied! Contact Your Admin";
			cout << "\n\n\t\t------------------------------------------------";
			return false;
		}
		else
		{
			return true;
		}		
		
	}
	   
};

