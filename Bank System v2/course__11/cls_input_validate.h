#pragma once
#include<iostream>
#include<string>
#include"cls_date.h"
#include"cls_string.h"
#include"cls_util.h"
using namespace std;

class cls_input_validate
{
public:

template  <typename T>  static T is_number_between(T number, T from, T to)
	{
		if (number >= from && number <= to)
		{
			return true;
		}
		return false;
	}

	static bool is_date_between(cls_date date, cls_date date1, cls_date date2)
	{
		cls_date min, max;
		if (cls_date::is_date1_before_date2(date1, date2))
		{
			min = date1;
			max = date2;
		}
		else
		{
			min = date2;
			max = date1;
		}
		if (cls_date::is_date1_before_date2(date, max)  || cls_date::is_equal_date(date,max)
			&& cls_date::is_date1_after_date2(date, min)|| cls_date::is_equal_date(date,min))
		{
			return true;
		}
		return false;

	}

template <typename T> static T read_number(string error = "Invalid nmuber, Enter again\n")
	{
		T number;
		while (!(cin>>number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << error;
		}
		return number;
	}

template <typename T> static T read_number_between(T from, T to, string error = "number is not within the range,Enter again\n")
	{
		T number = read_number<T>();
		while (! is_number_between<T>(number, from, to))
		{
			cout << error;
			number = read_number<T>();
		}
		return number;
	}

	static bool is_valid_date(cls_date date)
	{
		return cls_date::is_valid_date(date);
	}

	static string read_string()
	{
		string s = "";
		getline(cin >> ws, s);
		return s;
	}

	
};


