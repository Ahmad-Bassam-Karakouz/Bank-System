#pragma once
#include<iostream>
#include<string>
#include"cls_string.h"
#include"cls_person.h"
#include<vector>
#include<fstream>
using namespace std;

class cls_bank_client: public cls_person
{
private:

	enum en_mode { empty_mode = 0,update_mode=1 ,add_new=2};

	en_mode _mode;
	string _account_number;
	string _pin_code;
	double _balance=0;
	bool _mark_for_delete = false;	
private:

	static cls_bank_client _convert_line_to_client_object(string line, string sep = "#//#")
	{
		vector<string>v;
		v = cls_string::split(line, sep);

		return cls_bank_client(en_mode::update_mode, v[0], v[1], v[2], v[3], v[4], v[5], stod(v[6]));

	}

	static cls_bank_client _get_empty_client_object()
	{
		return cls_bank_client(en_mode::empty_mode, "", "", "", "", "", "", 0);
	}
	
	static vector<cls_bank_client> _load_client_data_from_file()
	{
		vector<cls_bank_client>v;

		fstream my_file;
		my_file.open("clients.txt", ios::in);

		if (my_file.is_open())
		{
			string line;

			while (getline(my_file, line))
			{
				cls_bank_client client = _convert_line_to_client_object(line);				
				v.push_back(client);

			}
			my_file.close();
		}
		return v;
	}

	static string _convert_client_data_to_line(cls_bank_client client, string sep = "#//#")
	{
		string s = "";
		s += client.first_name + sep;
		s += client.last_name + sep;
		s += client.email + sep;
		s += client.phone + sep;
		s += client._account_number + sep;
		s +=client._pin_code + sep;
		s +=to_string(client._balance) + sep;
		return s;
	}
		
	static void _save_client_data_to_file(vector<cls_bank_client> v)
	{
		fstream my_file;
		my_file.open("clients.txt", ios::out);
		string data_line;
		if (my_file.is_open())
		{
			for (cls_bank_client c : v)
			{
				if (c._mark_for_delete == false)
				{
					data_line = _convert_client_data_to_line(c);
					my_file << data_line << endl;
				}				
			}
			my_file.close();
		}
		
	}

	void _update()
	{
		vector<cls_bank_client>v;
		v = _load_client_data_from_file();
		for (cls_bank_client& c : v)
		{
			if (c.account_number == _account_number)
			{
				c = *this;
				break;
			}
		}

		_save_client_data_to_file(v);
	}

	void _add_data_line_to_file(string client)
	{
		fstream my_file;
		my_file.open("clients.txt", ios::out | ios::app);
		if (my_file.is_open())
		{
			my_file << client << endl;
		}
		my_file.close();
	}

	void _add_new()
	{
		_add_data_line_to_file(_convert_client_data_to_line(*this));
	}

	
public:
	
	cls_bank_client(en_mode mode, string first_name, string last_name, string email, string phone,
		string account_number, string pin_code, float balance) :
		cls_person(first_name, last_name, email, phone)
	{
		_mode = mode;
		_account_number = account_number;
		_balance = balance;
		_pin_code = pin_code;
	}
	   	
	bool is_empty()
	{
		return(_mode == en_mode::empty_mode);
	}
	
	string get_account_number()
	{
		return _account_number;
	}

	__declspec(property(get = get_account_number))string account_number;

	float get_account_balance()
	{
		return _balance;
	}

private:

	void _set_account_balance(float balance)
	{
		_balance = balance;
	}

public:

	__declspec(property(get = get_account_balance))float balance;

	string get_pin_code()
	{
		return _pin_code;
	}

	void set_pin_code(string pin_code)
	{
		_pin_code = pin_code;
	}

	__declspec(property(get = get_pin_code, put = set_pin_code))string pin_code;

	string full_name()
	{
		return first_name +" " + last_name;
	}

		
public:

	static cls_bank_client find(string account_number)
	{
		//vector<cls_bank_client> v;

		fstream my_file;
		my_file.open("clients.txt", ios::in);
		if (my_file.is_open())
		{
			string line;
			while ((getline(my_file,line)))
			{
				cls_bank_client client = _convert_line_to_client_object(line);
				if (client.account_number == account_number)
				{
					my_file.close();
					//v.push_back(client);							
					return client;
				}			
			}
			my_file.close();
		}

		return _get_empty_client_object();
	}

	static cls_bank_client find(string account_number,string pin_code)
	{
		//vector<cls_bank_client> v;

		fstream my_file;
		my_file.open("clients.txt", ios::in);
		if (my_file.is_open())
		{
			string line;
			while ((getline(my_file, line)))
			{
				cls_bank_client client = _convert_line_to_client_object(line);
				if (client.get_account_number() == account_number && 
					client.get_pin_code()==pin_code)
				{
					my_file.close();
					return client;
				}				
				//v.push_back(client);
			}
			my_file.close();
		}

		return _get_empty_client_object();
	}

	static bool _is_client_exist(string account_number)
	{
		cls_bank_client client = cls_bank_client::find(account_number);

		return(!client.is_empty());
	}

	enum en_save_result { save_succeeded = 1, empty_object=0,account_number_exists=2};
	
	en_save_result save()
	{
		switch (_mode)
		{
		case cls_bank_client::empty_mode:
			return en_save_result::empty_object;
			break;
		case cls_bank_client::update_mode:
			_update();
			return en_save_result::save_succeeded;
			break;
		case cls_bank_client::add_new:
			if (cls_bank_client::_is_client_exist(_account_number))
			{
				return en_save_result::account_number_exists;
			}
			else
			{
				_add_new();

				_mode = en_mode::add_new;

				return en_save_result::save_succeeded;

				
			}
	
		}
	}

	static cls_bank_client get_add_new_client_project(string account_number)
	{
		return  cls_bank_client (en_mode::add_new, "", "", "", "", account_number, "", 0);
	}
	
	bool delete_client()
	{
		vector<cls_bank_client> v;
		v = _load_client_data_from_file();
		for (cls_bank_client& c : v)
		{
			if (c.account_number == _account_number)
			{
				c._mark_for_delete = true;
				break;			
			}
			
		}
		_save_client_data_to_file(v);

		*this = _get_empty_client_object();
		return true;
	}

	static vector<cls_bank_client> get_clients_lists()
	{
		return _load_client_data_from_file();
	}

	static double get_total_balance(vector<cls_bank_client> v_clients)
	{
		double total_balance = 0;
		for (cls_bank_client client : v_clients)
		{
			total_balance += client._balance;
		}
		return total_balance;
	}
	
	 string _convert_transfer_info_to_line( cls_bank_client client_to, float amount, string sep = "#//#")
	{
		string transfer_info = "";
		transfer_info += cls_date::get_date_and_time_string() + sep;
		transfer_info += account_number + sep;
		transfer_info += client_to.account_number + sep;
		transfer_info += to_string(amount) + sep;
		transfer_info += to_string(balance) + sep;
		transfer_info += to_string(client_to.balance) + sep;
		transfer_info += current_user.user_name;
		return transfer_info;
	}

	 void _add_transfer_info_to_file(string transfer_info)
	{

		fstream my_file;

		my_file.open("transfer_log.txt", ios::out | ios::app);
		if (my_file.is_open())
		{
			my_file << transfer_info << endl;
		}
		my_file.close();
	}

	 void _save_transfer_proccess(cls_bank_client client_to, float amount)
	{
		_add_transfer_info_to_file(_convert_transfer_info_to_line(client_to, amount));

	}
	 
	void deposit(double amount)
	{
		_balance += amount;
		_update();
	}

	bool withdraw(double amount)
	{
		if (amount > _balance)
		{
			return false;
		}
		else
		{
			_balance -= amount;
			save();
			return true;
		}
		
	}

	bool transfer(int amount, cls_bank_client& client_to)
	{
		if (amount > balance)
		{
			return false;
		}
		withdraw(amount);
		client_to.deposit(amount);
		_save_transfer_proccess(client_to, amount);
		return true;
	}

};



