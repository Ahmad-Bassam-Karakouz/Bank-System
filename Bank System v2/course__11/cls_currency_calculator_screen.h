#pragma once
#include"cls_screen.h"
#include"cls_input_validate.h"
#include"cls_currency.h"
#include"cls_util.h"

class cls_currency_calculator_screen:protected cls_screen
{
private :

	static cls_currency _read_currency_code(string message)
	{
		string currency_code;
		cout << message;
		currency_code = cls_input_validate::read_string();
		while (!cls_currency::is_currency_exist_by_code(currency_code))
		{
			cout << "\n\n\t\tCurrency is not found ! you sure again :";
			currency_code = cls_input_validate::read_string();
		}
		cls_currency  currency = cls_currency::find_by_code(currency_code);
		
		return currency;
		
	}
	
	static float _read_amount()
	{
		float amount;
		cout << "\n\n\t\tWhat is it amount ?";
		amount = cls_input_validate::read_number<float>();
		return amount;
	}
	
public:

	static void courrency_calculator()
	{
		char answer = 'y';
		while (answer=='y' || answer=='Y')
		{
			system("cls");
			string main = "\tCurrency Calculator";
			string sub = "\t...................";

			_draw_screen_header(main, sub, cls_util::tabs(2));

			cls_currency currency_from = _read_currency_code("\n\n\t\tWat type of currency do you want to convert?");
			cls_currency currency_to = _read_currency_code("\n\n\t\tWat currency do you want to convert to?");
			int amount = _read_amount();
			float convert_result = currency_from.currency_convert(amount, currency_to);
			cout << "\n\n\t\t " << to_string(amount) << " " << currency_from.currency_code() << " = "
				<< to_string(convert_result) << " " << currency_to.currency_code() << " .";


			cout << "\n\n\t\tAre you want perform another calculator [y/n] ?";
			cin >> answer;
		}
		
				
	}

};

