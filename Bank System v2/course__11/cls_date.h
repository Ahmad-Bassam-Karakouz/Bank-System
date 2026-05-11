#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include<ctime>
#include <vector>
#include<string>
#include"cls_string.h"
using namespace std;

class cls_date
{
private:

	short _day=0 ;
	short _month=0;
	short _year=0;
	
public:
	
	cls_date()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_day = now->tm_mday ;
		_month = now->tm_mon+1;
		_year = now->tm_year+1900;
	}

	cls_date(string date)
	{
		vector <string> v;
		v = cls_string::split(date, "/");
		_day = stoi(v[0]);
		_month = stoi(v[1]);
		_year = stoi(v[2]);
	}

	cls_date(short day, short month, short year)
	{
		_day = day;
		_month = month;
		_year = year;


	}
	
	void set_day(short day)
	{
		_day = day;
	}

	short get_day()
	{
		return _day;
	}

	__declspec(property(get = get_day, put = set_day)) short day;

	void set_month(short month)
	{
		_month = month;
	}

	short get_month()
	{
		return _month;
	}

	__declspec(property(get = get_month, put = set_month)) short month;

	void set_year(short year)
	{
		_year = year;
	}

	short get_year()
	{
		return _year;
	}

	__declspec(property(get = get_year, put = set_year)) short year;

	void _print_client()
	{
		cout << date_to_string() << endl;
	}
	

	//1-date to string.

	static string date_to_string(cls_date date)
	{
		return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year) + " \n";
	}

	string date_to_string()
	{
		return  date_to_string(*this);
	}

	//2-is leap year.

	static bool is_leap_year(short year)
	{
		return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
	}

	bool is_leap_year()
	{
		return is_leap_year(_year);
	}

	//3-days of month.

	static short days_of_month(short month, short year)
	{
		if (month < 1 || month>12)
		{
			return 0;
		}
		short array_for_days_of_month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

		return ((month == 2) ? is_leap_year(year) ? 29 : 28 : array_for_days_of_month[month]);
	}

	short days_of_month()
	{
		return  days_of_month(_month, _year);
	}

	//4-order current day.

	static short order_current_day(short day,short month,short year)
	{
		short a = ((14 - month) / 12);
		short y =year - a;
		short m = month + (12 * a) - 2;
		short d = (day + year + (year / 4) - (year / 100) + (year / 400) + ((31 * m) / 12)) % 7;
		return d;
	}
	
	static short order_current_day(cls_date date)
	{
		short a = ((14 - date._month) / 12);
		short y = date._year - a;
		short m = date._month + (12 * a) - 2;
		short d = (date._day + date._year + (date._year / 4) - (date._year / 100) + (date._year / 400) + ((31 * m) / 12)) % 7;
		return d;
	}

	short order_current_day()
	{
		return order_current_day(*this);
	}

	//5- name current day.

	static string name_current_day(short day_order)
	{
		string array_day_name[] = { "sunday", "monday" ,"tuesday" , "wednesday" ,"thursday" , "friday" ,"saturday" };
		return array_day_name[day_order];
	}

	string name_current_day()
	{
		return  name_current_day(order_current_day(_year, _month, _day));
	}

	//6-name month.

	static  string name_month(int month)
	{
		string  array_of_month_name[13] = { "","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		return array_of_month_name[month];
	}

	string name_month()
	{
		return   name_month(_month);
	}

	//7-days of week.

	static string name_days_of_week()
	{
		return ("  Sun  Mon  Tue  Wed  Thu  Fri  Sat  \n");
	}
	   	 
	//8-print calendar of month. 

	static void print_calendar_of_month(int month, int year)
	{
		cout << "  \n\n  _______________" << name_month(month) << "_______________\n\n";
		cout << name_days_of_week() << "\n";

		int i;
		for (i = 0; i < order_current_day(year, month, 1); i++)
		{
			printf("     ");
		}
		for (short ii = 1; ii <= days_of_month(month, year); ii++)
		{
			printf("%5d", ii);
			if (++i == 7)
			{
				i = 0;
				cout << "\n";
			}
		}
		cout << "\n  _________________________________\n";

	}
	
	void print_calendar_of_month()
	{
		print_calendar_of_month(_month, _year);
	}

	//9-print calendar of year.

	static void print_calendar_of_year(int year)
	{
		cout << "\n\n___________________________________\n\n";
		cout << "          Calendar - " << year << "\n\n";
		cout << "___________________________________\n\n";

		for (short i = 1; i <= 12; i++)
		{
			print_calendar_of_month(i, year);
		}

	}

	void print_calendar_of_year()
	{
		print_calendar_of_year(_year);
	}
	
	//10-total days from the deginnig of year.

	static int total_days_from_the_deginning_of_year(cls_date date)
	{
		int i = date._month - 1;
		int counter = date._day;
		for (i; i >= 1; i--)
		{
			counter += days_of_month(i, date._year);
		}
		return counter;
	}

	int total_days_from_the_deginning_of_year()
	{
		return  total_days_from_the_deginning_of_year(*this);
	}

	//11-is equal date2.

	static bool is_equal_date(cls_date date1, cls_date date2)
	{
		return (date1._year == date2._year && date1._month == date2._month && date1._day == date2._day) ?
			true : false;
	}

	bool is_equal_date(cls_date date2)
	{
		return  is_equal_date(*this, date2);
	}

	//12-is last day in month.

	static bool is_last_day_in_month(cls_date date)
	{
		return (days_of_month(date._month, date._year) == date._day) ? true : false;
	}

	bool is_last_day_in_month()
	{
		return  is_last_day_in_month(*this);
	}

	//13-is last month in year.

	static bool is_last_month_in_year(cls_date date)
	{
		return (date._month == 12) ? true : false;
	}

	bool is_last_month_in_year()
	{
		return  is_last_month_in_year(*this);
	}
	
	//14-adding 1 day to date.

	static cls_date adding_1_day_to_date(cls_date& date)
	{
		if (is_last_day_in_month(date))
		{
			if (is_last_month_in_year(date))
			{
				date._day = 1;
				date._month = 1;
				date._year++;
			}
			else
			{
				date._day = 1;
				date._month++;
			}

		}
		else
		{
			date._day++;
		}
		return date;

	}

	cls_date adding_1_day_to_date()
	{
		return adding_1_day_to_date(*this);
	}
	
	//15-difference between dates.

	static short get_difference_in_days_between_dates(cls_date date1, cls_date date2, bool include = false)
	{
		short days = 0;
		while (is_date1_before_date2(date1, date2))
		{
			days++;
			adding_1_day_to_date(date1);
		}
		return (include) ? ++days : days;
	}

	short get_difference_in_days_between_dates(cls_date date2)
	{
		return  get_difference_in_days_between_dates(*this, date2);
	}

	//16-get current date.

	static cls_date get_current_date_()
	{
		
		time_t t = time(0);
		tm* now = localtime(&t);

		short day, month, year;

		year = now->tm_year + 1900;
		month = now->tm_mon + 1;
		day = now->tm_mday;
		return cls_date(day,month,year);
	}
	
	//17-is valid date.

	static bool is_valid_date(cls_date date)
	{

		if (1 > date._day > 32)
			return false;
		if (0 >= date._month > 12)
			return false;
		if (0 >= date._year)
			return false;
		if (date._month == 2)
		{
			if (is_leap_year(date._year))
			{
				if (date._day > 29)
					return false;
			}
			else
			{
				if (date._day > 28)
					return false;
			}
		}


		if (date._day > days_of_month(date._month, date._year))
			return false;


		return true;

	}

	bool is_valid_date()
	{
		return   is_valid_date(*this);
	}
	
	//18-difference between current date and entered date.

	static short difference_between_current_date_and_entered_date(cls_date date1, bool include = false)
	{
		cls_date date2 = get_current_date_();
		short days = 0;
		while (is_date1_before_date2(date1, date2))
		{
			days++;
			adding_1_day_to_date(date1);
		}
		return (include) ? ++days : days;
	}

	short difference_between_current_date_and_entered_date()
	{
		return  difference_between_current_date_and_entered_date(*this);
	}

	//19-date after x days.
		
	static	cls_date date_after_x_days(cls_date &date, short days)
	{

		for (short i = 1; i <= days; i++)
		{
			date = adding_1_day_to_date(date);
		}
		return date;
	}

	void date_after_x_days(short days)
	{
	
		  date_after_x_days(*this, days);
	}

	//20-date after x weeks.
	
private:

	static cls_date date_after_1_week_(cls_date date)
	{
		for (short i = 1; i <= 7; i++)
		{
			date = adding_1_day_to_date(date);
		}
		return date;
	}
public:

	 cls_date date_after_x_weeks(cls_date &date, short weeks)
	{
		for (short i = 1; i <= weeks; i++)
		{
			date = date_after_1_week_(date);
		}
		return date;
	}

	 void date_after_x_weeks(short weeks)
	{
		  date_after_x_weeks(*this, weeks);
	}

	//21-date after x month.

private:

	static cls_date date_after_1_month(cls_date date)
	{
		short days = date._day;
		if (date._month == 12)
		{
			date._month = 1;
			date._year++;
		}
		else
		{
			date._month++;
		}
		if (date._month != 2)
		{
			short days_of_month_ = days_of_month(date._month, date._year);
			if (days_of_month_ < days)
			{
				date._day = days_of_month_;
			}
		}
		return date;
	}

public:

	static cls_date date_after_x_month(cls_date &date, short months)
	{
		for (short i = 1; i <= months; i++)
		{
			date = date_after_1_month(date);
		}
		return date;
	}

	void date_after_x_month(short days)
	{
		  date_after_x_month(*this, days);
	}

	//22-date after x year.

private:

	static cls_date date_after_1_year(cls_date date)
	{

		for (short i = 1; i <= 12; i++)
		{
			date = date_after_1_month(date);
		}

		return date;
	}

public:

	static cls_date date_after_x_year(cls_date &date, int years)
	{
		int days = date._day;
		for (int i = 1; i <= years; i++)
		{
			date = date_after_1_year(date);
		}

		return date;
	}

	void date_after_x_year(int years)
	{
		  date_after_x_year(*this, years);
	}
	
	//23-is first day in month.
		
	static	bool is_first_day_in_month(cls_date date)
	{
		return (date._day == 1) ? true : false;
	}

	bool is_first_day_in_month()
	{
		return  is_first_day_in_month(*this);
	}

	//24-is first month in year.

	static bool is_first_month_in_year(cls_date date)
	{
		return (date._month == 1) ? true : false;
	}

	bool is_first_month_in_year()
	{
		return  is_first_month_in_year(*this);
	}

	//25-date before x days.

private:

	static cls_date date_before_day(cls_date date)
	{

		if (is_first_day_in_month(date))
		{
			if (is_first_month_in_year(date))
			{
				date._day = 31;
				date._month = 12;
				date._year--;
			}
			else
			{
				date._month = date._month--;
				date._day = days_of_month(date._month, date._year);

			}

		}
		else
		{
			date._day--;
		}

		return date;

	}

public:

	cls_date date_before_x_day(cls_date &date, short days)
	{
		for (short i = days; i >= 1; i--)
		{
			date = date_before_day(date);
		}
		return date;
	}
	
	void date_before_x_day(short days)
	{
		date_before_x_day(*this, days);
	}

	//26-date before x weeks.

private:

	static cls_date date_before_1_week(cls_date date)
	{
		for (short i = 7; i >= 1; i--)
		{
			date = date_before_day(date);
		}
		return date;
	}

public:

	static cls_date date_befor_x_weeks(cls_date &date, short weeks)
	{
		for (short i = weeks; i >= 1; i--)
		{
			date = date_before_1_week(date);
		}
		return date;
	}

	void date_befor_x_weeks(short weeks)
	{
		  date_befor_x_weeks(*this, weeks);
	}

	//27-date before x month.

private:

	static cls_date date_before_1_month(cls_date date)
	{

		if (date._month == 1)
		{
			date._month = 12;
			date._year--;
		}
		else
		{
			date._month--;
		}
		short days_of_month_ = days_of_month(date._month, date._year);
		if (days_of_month_ < date._day)
		{
			date._day = days_of_month_;
		}

		return date;
	}

public:

	static cls_date date_before_x_month(cls_date &date, short months)
	{
		for (short i = months; i >= 1; i--)
		{
			date = date_before_1_month(date);
		}
		return date;
	}

	void date_before_x_month(short months)
	{
		  date_before_x_month(*this, months);
	}

	//28-date before x year.

private:

	static cls_date date_before_1_year(cls_date date)
	{

		for (short i = 12; i >= 1; i--)
		{
			date = date_before_1_month(date);
		}


		return date;
	}

public:

	static cls_date date_before_x_year(cls_date &date, short years)
	{
		short days = date._day;
		for (short i = years; i >= 1; i--)
		{
			date = date_before_1_year(date);
		}

		return date;
	}

	void date_before_x_year(short years)
	{
		   date_before_x_year(*this, years);
	}

	//29-is end week.

	static bool is_end_week(cls_date date)
	{
		return(order_current_day(date) == 6);
	}

	bool is_end_week()
	{
		return  is_end_week(*this);
	}

	//30-is week end.

	static bool is_week_end(cls_date date)
	{
		short day_end = order_current_day(date);
		return(day_end == 5 || day_end == 6);
	}

	bool is_week_end()
	{
		return  is_week_end(*this);
	}

	//31-is business day.

	static bool is_business_day(cls_date date)
	{
		if (!is_week_end(date))
		{
			return true;
		}
		return false;
	}

	bool is_business_day()
	{
		return  is_business_day(*this);
	}

	//32-days until end of week.

	static short days_until_end_of_week(cls_date date)
	{
		return 6 - (order_current_day(date));
	}

	short days_until_end_of_week()
	{
		return  days_until_end_of_week(*this);
	}
	
	//33-days until of month.

	static short days_until_end_of_month(cls_date date)
	{
		return days_of_month(date._month, date._year) - date._day;
	}

	short days_until_end_of_month()
	{
		return  days_until_end_of_month(*this);
	}

	//34-days until of year.
		
	static short days_until_end_of_year(cls_date date)
	{
		if (is_leap_year(date._year))
		{
			return 366 - total_days_from_the_deginning_of_year(date);
		}
		else
		{
			return 365 - total_days_from_the_deginning_of_year(date);
		}
	}

	short days_until_end_of_year()
	{
		return  days_until_end_of_year(*this);
	}
	
	//35-actucal vacation days.

	static short actucal_vacation_days(cls_date date1, cls_date date2)
	{
		short actucal_vacation_days = 0;

		while (is_date1_before_date2(date1, date2))
		{
			if (!is_week_end(date1))
			{
				actucal_vacation_days++;
			}
			date1 = adding_1_day_to_date(date1);
		}



		return actucal_vacation_days;
	}

	short actucal_vacation_days(cls_date date2)
	{
		return  actucal_vacation_days(*this, date2);
	}

	//36-actucal business days.

	static short actucal_business_days(cls_date date1, cls_date date2)
	{
		short actucal_business_days = 0;

		while (is_date1_before_date2(date1, date2))
		{
			if (!is_week_end(date1))
			{
				actucal_business_days++;
			}
			date1 = adding_1_day_to_date(date1);
		}

		return actucal_business_days;
	}

	short actucal_business_days(cls_date date2)
	{
		return  actucal_business_days(*this, date2);
	}
	   
	//37-date vacation end.

	static cls_date date_vacation_end(cls_date date, short vacation_days)
	{
		short counter_days = 0;

		for (short i = 1; i <= vacation_days + counter_days; i++)
		{
			if (is_week_end(date))
			{
				counter_days++;
			}
			date = adding_1_day_to_date(date);
		}
		while (is_week_end(date))
		{
			date = adding_1_day_to_date(date);
		}

		return date;
	}

	cls_date date_vacation_end(short vacation_days)
	{
		return  date_vacation_end(*this, vacation_days);
	}

	//38-is date after date2.

	static bool is_date1_after_date2(cls_date date1, cls_date date2)
	{
		return (date1._year > date2._year) ? true : (date1._month > date2._month) ? true : (date1._day > date2._day) ?
			true : false;
	}

	bool is_date1_after_date2(cls_date date2)
	{
		return  is_date1_after_date2(*this, date2);
	}

	//39-check date return string.
	
	static string check_2date_return_string(cls_date date1, cls_date date2)
	{
		if (is_date1_after_date2(date1, date2))
		{
			return"date1 is after date2";
		}
		if (is_date1_before_date2(date1, date2))
		{
			return "date1 is before date2";
		}
		return"date1 equal date2";
	}

	string check_this_date_with_other_date_return_string(cls_date date2)
	{
		return  check_2date_return_string(*this, date2);
	}
	
	//40-number of seconds in year.

	static int seconds_of_year(short year)
	{
		return minutes_of_year(year) * 60;
	}

	int seconds_of_year()
	{
		return  seconds_of_year(year);
	}
	
	//41-number of minutes in year.

	static int minutes_of_year(short year)
	{
		return hour_of_year(year) * 60;
	}

	int minutes_of_year()
	{
		return  minutes_of_year(year);
	}
	
	//42-number of hours in year.

	static short hour_of_year(short year)
	{
		return days_of_year(year) * 24;
	}

	short hour_of_year()
	{
		return  hour_of_year(year);
	}
	
	//43-number of days in year.

	static short days_of_year(short year)
	{
		return is_leap_year(year) ? 366 : 365;
	}

	short days_of_year()
	{
		return  days_of_year(year);
	}

	//44-is date1 before date2.

	static bool is_date1_before_date2(cls_date date1, cls_date date2)
	{
		return (date1.year < date2.year) ? true : (date1.month < date2.month) ? true
			: (date1.day < date2.day) ? true : false;
	}

	bool is_date1_before_date2( cls_date date2)
	{
		return   is_date1_before_date2(*this, date2);
	}

	//45-swap date.

	static void swap_date(cls_date& date1, cls_date& date2)
	{
		cls_date date;
		date = date1;
		date1 = date2;
		date2 = date;
	}

	void swap_date(cls_date& date2)
	{
		swap_date(*this, date2);
	}

	//46-get date and time (string).

	static string get_date_and_time_string()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short sec,min,hour,day, month, year;

		year = now->tm_year + 1900;
		month = now->tm_mon + 1;
		day = now->tm_mday;
		hour = now->tm_hour;
		min = now->tm_min;
		sec = now->tm_sec;		
		string time = to_string(year) + "_" + to_string(month) + "_" + to_string(day)+"   "+
			          to_string(hour) + ":" + to_string(min) + ":" + to_string(sec);
		return time;
			       
	}


};


