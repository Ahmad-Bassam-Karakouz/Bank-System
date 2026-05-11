#pragma once
#include"cls_screen.h"
#include"cls_currency.h"
#include"cls_util.h"
#include<iomanip>


class cls_currencies_list_screen:protected cls_screen
{


private:

	static void _print_currency_record_line(cls_currency currency)
	{
		cout << "\t";
		cout << setw(30) << left << "| " + currency.country();
		cout << setw(10) << left << "| " + currency.currency_code();
		cout << setw(42) << left << "| " + currency.currency_name();
		cout << setw(12) << left << "| " + to_string(currency.rate);

	}

public:

	static void currencies_list()
	{

		vector<cls_currency> v_currencies = cls_currency::get_list_currencies();
		string main = "\t\t\t\tCurrencies List Screen";
		string sub = "\t\t\t\t   (" + to_string(v_currencies.size()) + ") " + "Currency.";

		_draw_screen_header(main, sub, cls_util::tabs(5));

		cout << "\n\t_______________________________________________";
		cout << "___________________________________________________";
		cout << "\n\n\t";
		cout << setw(30) << left <<  "| Currency";
		cout << setw(10) << left <<  "| Code";
		cout << setw(42) << left <<  "| Name";
		cout << setw(12) << left <<  "| Rate/(1$)";
		cout << "\n\t_______________________________________________";
		cout << "___________________________________________________\n";

		if(v_currencies.size()==0)
		{
			cout << "\n\n\t\t\tNot Currencies Available in System!\n";
		}
		else
		{
			for (cls_currency c : v_currencies)
			{
				_print_currency_record_line(c);
				cout << endl;
			}
		}
	

		cout << "\t_______________________________________________";
		cout << "___________________________________________________\n";


	}

};

