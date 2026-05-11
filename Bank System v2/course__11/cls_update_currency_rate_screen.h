#pragma once
#include"cls_screen.h"
#include"cls_currency.h"
#include"cls_input_validate.h"

class cls_update_currency_rate_screen:protected cls_screen
{

	static void _update_rate_by_code()
	{

		string code;
		cout << "\n\t\tPlease Enter Currency code :";
		code = cls_input_validate::read_string();
		while (!cls_currency::is_currency_exist_by_code(code))
		{
			cout << "\n\t\tCurrency is not found try again :";
			code = cls_input_validate::read_string();
		} 
		cout << "\n\t\tCurrency is found (_: \n";
		cls_currency currency = currency.find_by_code(code);
		currency.print(currency);
		char answer;
		cout << "\n\t\tAre you sure you want to update the rate of this currency y/n ?";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			double new_rate;
			cout << "\n\n\t\tEnter New Rate :";
			new_rate = cls_input_validate::read_number<double>();
			currency.rate = new_rate;
			currency.update();
			currency.print(currency);
		}

	}

	

public:

	static void update_currency_code()
	{
		string main = "\tUpdate Currency Screen";
		string sub =  "\t......................";

		_draw_screen_header(main, sub, cls_util::tabs(2));

		_update_rate_by_code();

	}

};

