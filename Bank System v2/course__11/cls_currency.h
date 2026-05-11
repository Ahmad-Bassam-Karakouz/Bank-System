#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"cls_string.h"
using namespace std;

class cls_currency
{

private:

	enum en_mode{empty_mode=0,update_mode=1};

	en_mode _mode;
	string _country;
	string _currency_code;
	string _currency_name;
	float _rate = 0;

public:

	cls_currency(en_mode mode,string country, string currency_code, string currency_name, float rate)
	{
		_mode = mode;
		_country = country;
		_currency_code = currency_code;
		_currency_name = currency_name;
		_rate = rate;
	}
	
	string country()
	{
		return _country;
	}

	string currency_code()
	{
		return _currency_code;
	}

	string currency_name()
	{
		return _currency_name;
	}
	
	float get_rate()
	{
		return _rate;
	}

	void set_rate(float rate)
	{
		_rate = rate;
		update();
	}
	   
	__declspec(property(get = get_rate, put = set_rate))float rate;
	

private:
	
	static cls_currency _convert_currency_line_to_object(string line, string sep = "#//#")
	{
		vector<string>v = cls_string::split(line, sep);

		return cls_currency(en_mode::update_mode, v[0], v[1], v[2], stof(v[3]));
	}

	static vector<cls_currency> _load_currencys_data_from_file()
	{
		vector<cls_currency> v_currencys;

		fstream my_file;

		my_file.open("Currencies.txt", ios::in);
		if (my_file.is_open())
		{
			string line;

			while (getline(my_file, line))
			{
				cls_currency c = _convert_currency_line_to_object(line);

				v_currencys.push_back(c);

			}
			my_file.close();
		}

		return v_currencys;
	}

	string _convert_currency_data_to_line(cls_currency currency, string sep = "#//#")
	{
		string c;
		c += currency._country + sep;
		c += currency._currency_code + sep;
		c += currency._currency_name + sep;
		c += to_string(currency._rate) + sep;
		return c;
	}

	void _save_currencys_data_to_file(vector<cls_currency> v_currencys)
	{

		fstream my_file;
		string line;

		my_file.open("Currencies.txt", ios::out);
		if (my_file.is_open())
		{
			for (cls_currency c : v_currencys)
			{
				line = _convert_currency_data_to_line(c);
				my_file << line << endl;
			}
			my_file.close();
		}
	}
	
	static cls_currency _get_empty_object()
	{
		return cls_currency(en_mode::empty_mode, "", "", "", 0);
	}
	   

public:

	bool is_empyt()
	{
		return _mode == en_mode::empty_mode;
	}

	static cls_currency find_by_code(string currency_code)
	{
		currency_code = cls_string::upper_all_letters(currency_code);

		vector <cls_currency> v_currencys = _load_currencys_data_from_file();

		for (cls_currency c : v_currencys)
		{
			if (cls_string::upper_all_letters(c.currency_code()) == currency_code)
			{
				return c;
			}
		}

		return _get_empty_object();

	}

	static cls_currency find_by_name(string currency_name)
	{
		currency_name = cls_string::upper_all_letters(currency_name);

		vector <cls_currency> v_currency = _load_currencys_data_from_file();

		for (cls_currency& c : v_currency)
		{


			if (cls_string::upper_all_letters(c.country()) == currency_name)
			{
				return c;
			}
		}

		return _get_empty_object();


	}

	static bool is_currency_exist_by_code(string currency_code)
	{
		cls_currency c = cls_currency::find_by_code(currency_code);
		return(!c.is_empyt());
	}

	static bool is_currency_exist_by_name(string currency_name)
	{
		cls_currency c = cls_currency::find_by_name(currency_name);
		return(!c.is_empyt());
	}

	static void print(cls_currency currency)
	{

		cout << "\n\t\tCurrency Card:\n";
		cout << "\t\t----------------------------";
		cout << "\n\t\tCountry    :" << currency.country() ;
		cout << "\n\t\tCode       :" << currency.currency_code() ;
		cout << "\n\t\tName       :" << currency.currency_name();
		cout << "\n\t\tRate(1$)   :" << currency.rate ;
		cout << "\n\t\t---------------------------\n";
	}

	static vector<cls_currency> get_list_currencies()
	{
		return _load_currencys_data_from_file();
	}

	void update()
	{
		vector<cls_currency> v_currencys = _load_currencys_data_from_file();

		for (cls_currency& c : v_currencys)
		{
			if (c.currency_code() == currency_code())
			{
				c = *this;
				break;
			}

		}

		_save_currencys_data_to_file(v_currencys);
	}

	float currency_convert(float amount, cls_currency currency2)
	{
		return ((amount / rate ) * currency2.rate);
	}

};

