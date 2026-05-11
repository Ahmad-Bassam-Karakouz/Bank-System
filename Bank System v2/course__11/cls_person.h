#pragma once
#include<iostream>
using namespace std;

class cls_person
{
private:
	string _first_name;
	string _last_name;
	string _email;
	string _phone;

public:

	cls_person(string first_name, string last_name, string email, string phone)
	{
		_first_name = first_name;
		_last_name = last_name;
		_email = email;
		_phone = phone;
	}

public:

	void set_first_name(string first_name)
	{
		_first_name = first_name;
	}

	string get_first_name()
	{
		return _first_name;
	}
	
	void set_last_name(string last_name)
	{
		_last_name = last_name;
	}

	string get_last_name()
	{
		return _last_name;
	}
	
	void set_email(string email)
	{
		_email = email;
	}

	string get_email()
	{
		return _email;
	}
	
	void set_phone(string phone)
	{
		_phone = phone;
	}

	string get_phone()
	{
		return _phone;
	}

public:

	__declspec(property(get = get_first_name, put = set_first_name)) string first_name;
	__declspec(property(get = get_last_name, put = set_last_name)) string last_name;
	__declspec(property(get = get_email, put = set_email)) string email;
	__declspec(property(get = get_phone, put = set_phone)) string phone;



};

