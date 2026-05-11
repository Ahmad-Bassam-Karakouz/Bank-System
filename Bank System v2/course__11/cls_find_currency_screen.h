#pragma once
#include"cls_screen.h"
#include"cls_currency.h"
#include"cls_input_validate.h"

class cls_find_currency_screen:protected cls_screen
{
	 enum en_choose{e_code=1,e_name=2};

	static void _find_by_code()
	{
		
		string answer;
		cout << "\n\t\tPlease Enter Currency code :";
		answer = cls_input_validate::read_string();
		if (cls_currency::is_currency_exist_by_code(answer))
		{
			cout << "\n\t\tCurrency is found (_: \n";
			cls_currency currency = currency.find_by_code(answer);
			currency.print(currency);
		}
		else
		{
			cout << "\n\t\tCurrensy is not found )_: \n";
		}

	}

	static void _find_by_name()
	{

		string answer;
		cout << "\n\t\tPlease Enter Country Name :";
		answer = cls_input_validate::read_string();
		if (cls_currency::is_currency_exist_by_name(answer))
		{
			cout << "\n\t\tCountry is found (_: \n";
			cls_currency currency = currency.find_by_name(answer);
			currency.print(currency);
		}
		else
		{
			cout << "\n\t\tCountry is not found )_: \n";
		}

	}

	static short _read_choose()
	{
		short answer;
		cout << "\n\t\tFind By : [1] Code or [2] Counry ?";
		answer = cls_input_validate::read_number_between<short>(1,2);
		return answer;
	}

	static void _perform_find_process(en_choose choose)
	{
		switch (choose)
		{
		case cls_find_currency_screen::e_code:
			_find_by_code();
			break;

		case cls_find_currency_screen::e_name:
			_find_by_name();
			break;


		}
	}


public:

	static void find_currency()
	{
		string main = "\tFind Currency Screen";
		string sub =  "\t...................";

		_draw_screen_header(main, sub, cls_util::tabs(2));

		_perform_find_process(en_choose(_read_choose()));

	}

};

