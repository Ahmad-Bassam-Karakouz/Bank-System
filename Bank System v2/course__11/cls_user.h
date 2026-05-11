#pragma once
#include<iostream>
#include<string>
#include"cls_string.h"
#include"cls_person.h"
#include<vector>
#include<fstream>
#include"cls_date.h"
#include"cls_util.h"
using namespace std;

class cls_user: public cls_person 
{
private:

	enum en_mode { empty_mode = 0, update_mode = 1, add_new = 2 };

	en_mode _mode;
	string _user_name;
	string _password;
	int _permissions = 0;
	bool _mark_for_delete = false;

private:

	static cls_user _convert_line_to_user_object(string line, string sep = "#//#")
	{
		vector<string>v;
		v = cls_string::split(line, sep);

		return cls_user(en_mode::update_mode, v[0], v[1], v[2], v[3], v[4],cls_util::decryption_text(v[5],2), stoi(v[6]));

	}
	
	static cls_user _get_empty_user_object()
	{
		return cls_user(en_mode::empty_mode, "", "", "", "", "", "", -1);
	}

	static vector<cls_user> _load_user_data_from_file()
	{
		vector<cls_user>v;

		fstream my_file;
		my_file.open("users.txt", ios::in);

		if (my_file.is_open())
		{
			string line;

			while (getline(my_file, line))
			{
				cls_user user = _convert_line_to_user_object(line);
				v.push_back(user);

			}
			my_file.close();
		}
		return v;
	}

	static string _convert_user_data_to_line(cls_user user, string sep = "#//#")
	{
		string s = "";
		s += user.first_name + sep;
		s += user.last_name + sep;
		s += user.email + sep;
		s += user.phone + sep;
		s += user.user_name + sep;
		s +=cls_util::encryption_text(user.password,2) + sep;
		s += to_string(user.permissions) + sep;


		return s;
	}
	
	static string _convert_current_user_data_to_line(cls_user user, string sep = "#//#")
	{
		string s = "";
		s = cls_date::get_date_and_time_string() + sep;
		s = s + user.user_name + sep;
		s = s +cls_util::encryption_text(user.password,2) + sep;
		s = s + to_string(user.permissions) + sep;


		return s;
	}

	static void _save_user_data_to_file(vector<cls_user> v)
	{
		fstream my_file;
		my_file.open("users.txt", ios::out);
		string data_line;
		if (my_file.is_open())
		{
			for (cls_user c : v)
			{
				if (c._mark_for_delete == false)
				{
					data_line = _convert_user_data_to_line(c);
					my_file << data_line << endl;
				}
			}
			my_file.close();
		}

	}

	void _update()
	{
		vector<cls_user>v;
		v = _load_user_data_from_file();
		for (cls_user& c : v)
		{
			if (c.user_name == user_name)
			{
				c = *this;
				break;
			}
		}

		_save_user_data_to_file(v);
	}

	void _add_data_line_to_file(string user)
	{
		fstream my_file;
		my_file.open("users.txt", ios::out | ios::app);
		if (my_file.is_open())
		{
			my_file << user << endl;
		}
		my_file.close();
	}

	void _add_data_for_current_user_to_file(string user)
	{
		fstream my_file;
		my_file.open("login_register.txt", ios::out | ios::app);
		if (my_file.is_open())
		{
			my_file << user << endl;
		}
		my_file.close();
	}
	
	void _add_new()
	{
		_add_data_line_to_file(_convert_user_data_to_line(*this));
	}
		
public:

	enum en_permissions {
		p_all = -1, p_list_client = 1, p_add_new_client = 2, p_delete_client = 4,
		p_update_client = 8, p_find_client = 16, p_transactions = 32, p_manage_user = 64, p_login_register=128
	};

	struct st_login_register_info
	{
		string time;
		string user_name;
		string password;
		int permissions = 0;
	};
	
	static st_login_register_info _convert_login_register_to_record(string line, string sep = "#//#")
	{
		st_login_register_info login_register_record;
		vector<string> login_register_line = cls_string::split(line, sep);
		login_register_record.time = login_register_line[0];
		login_register_record.user_name = login_register_line[1];
		login_register_record.password = login_register_line[2];
		login_register_record.permissions = stoi(login_register_line[3]);

		return login_register_record;

	}

	struct st_transfer_log_info
	{
		string time;
		string s_acct;
		string d_acct;
		float  amount;
		float s_balance;
		float d_balance;
		string user_name;
	};

	static st_transfer_log_info _convert_transfer_log_info_to_record(string line, string sep = "#//#")
	{
		vector<string> v = cls_string::split(line, sep);
		st_transfer_log_info transfer_log_info;
		transfer_log_info.time = v[0];
		transfer_log_info.s_acct = v[1];
		transfer_log_info.d_acct = v[2];
		transfer_log_info.amount = stof(v[3]);
		transfer_log_info.s_balance = stof(v[4]);
		transfer_log_info.d_balance = stof(v[5]);
		transfer_log_info.user_name = v[6];

		return transfer_log_info;

	
	}


public:

	cls_user(en_mode mode, string first_name, string last_name, string email, string phone,
		string user_name, string password, int permissions) :
		cls_person(first_name, last_name, email, phone)
	{
		_mode = mode;
		_user_name = user_name;
		_password = password;
		_permissions = permissions;
	}
	
	bool is_empty()
	{
		return(_mode == en_mode::empty_mode);
	}

	string get_user_name()
	{
		return _user_name;
	}

	__declspec(property(get = get_user_name))string user_name;

	string get_password()
	{
		return _password;
	}

	void set_password(string password)
	{
		_password = password;
	}

	__declspec(property(get = get_password, put = set_password))string password;

	int get_permissions()
	{
		return _permissions;
	}

	void set_permissions(int permissions)
	{
		_permissions = permissions;
	}

	__declspec(property(get = get_permissions, put = set_permissions))int permissions;

	string full_name()
	{
		return first_name + " " + last_name;
	}
	
public:
		
	static cls_user find(string user_name)
	{
		//vector<cls_bank_client> v;

		fstream my_file;
		my_file.open("users.txt", ios::in);
		if (my_file.is_open())
		{
			string line;
			while ((getline(my_file, line)))
			{
				cls_user user = _convert_line_to_user_object(line);
				if (user.user_name == user_name)
				{
					my_file.close();
					//v.push_back(client);
					return user;
				}
			}
			my_file.close();
		}

		return _get_empty_user_object();
	}

	static cls_user find(string user_name, string password)
	{
		vector<cls_user> v;

		fstream my_file;
		my_file.open("users.txt", ios::in);
		if (my_file.is_open())
		{
			string line;
			while ((getline(my_file, line)))
			{
				cls_user user = _convert_line_to_user_object(line);
				if (user.user_name == user_name && user.password == password)
				{
					my_file.close();
					return user;
				}
				v.push_back(user);
			}
			my_file.close();
		}

		return _get_empty_user_object();
	}

	static bool _is_user_exist(string user_name)
	{
		cls_user user = cls_user::find(user_name);

		return(!user.is_empty());
	}

	enum en_save_result { save_succeeded = 1, empty_object = 0, user_name_exists = 2 };

	en_save_result save()
	{
		switch (_mode)
		{
		case cls_user::empty_mode:
			return en_save_result::empty_object;
			break;
		case cls_user::update_mode:
			_update();
			return en_save_result::save_succeeded;
			break;
		case cls_user::add_new:
			if (cls_user::_is_user_exist(user_name))
			{
				return en_save_result::user_name_exists;
			}
			else
			{
				_add_new();

				_mode = en_mode::add_new;

				return en_save_result::save_succeeded;


			}

		}
	}

	static cls_user get_add_new_user_object(string user_name)
	{
		return  cls_user(en_mode::add_new, "", "", "", "", user_name, "", -1);
	}

	bool delete_client()
	{
		vector<cls_user> v;
		v = _load_user_data_from_file();
		for (cls_user& c : v)
		{
			if (c.user_name ==_user_name)
			{
				c._mark_for_delete = true;
				break;
			}

		}
		_save_user_data_to_file(v);

		*this = _get_empty_user_object();
		return true;
	}

	static vector<cls_user> get_users_list()
	{
		return _load_user_data_from_file();
	}
	
	 bool check_access_permission(en_permissions permission)
	{		

		if ((this->_permissions & permission) == permission)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	 void save_login_process()
	 {

		 _add_data_for_current_user_to_file(_convert_current_user_data_to_line(*this));
	 }
	 	
	 static vector <st_login_register_info> get_login_register()
	 {
		 vector<st_login_register_info> v;

		 fstream my_file;
		 my_file.open("login_register.txt", ios::in);
		 if (my_file.is_open())
		 {
			 string line;

			 st_login_register_info login_register;

			 while (getline(my_file,line))
			 {
				 login_register = _convert_login_register_to_record(line);
				 v.push_back(login_register);

			 }
			 my_file.close();
		 }
		 return v;
	} 	
	 
	 static vector<st_transfer_log_info> get_transfer_log_register()
	 {
		 vector<st_transfer_log_info> transfer_log_register;

		 fstream my_file;

		 my_file.open("transfer_log.txt", ios::in);
		 if (my_file.is_open())
		 {
			 string line;

			 st_transfer_log_info transfer_log_info;

			 while (getline(my_file,line))
			 {
				 transfer_log_info = _convert_transfer_log_info_to_record(line);

				 transfer_log_register.push_back(transfer_log_info);

			 }
			 my_file.close();
		 }

		 return transfer_log_register;			 

	 }

};

