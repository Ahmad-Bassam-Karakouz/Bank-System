#pragma once
#include"cls_screen.h"
#include"cls_input_validate.h"
#include"cls_util.h"
#include"cls_currencies_list_screen.h"
#include"cls_find_currency_screen.h"
#include"cls_update_currency_rate_screen.h"
#include"cls_currency_calculator_screen.h"

class cls_currency_exchange_screen:protected cls_screen
{
private:

	enum  en_main_screen{e_list_currencioe=1,e_find_currency=2,e_update_rate=3,
	                   	e_currency_calculator=4,e_min_menue};


	static void _show_list_currencies_screen()
	{
		//cout << "\n\n List Currencies Screen Will Be Here ...\n\n ";
		cls_currencies_list_screen::currencies_list();
		_go_to_back_to_main_menue();

	}

	static void _show_find_currency_screen()
	{
		//cout << "\n\n Find Currency Screen Will Be Here ...\n\n";	
		cls_find_currency_screen::find_currency();
		_go_to_back_to_main_menue();
	}

	static void _show_update_rate_screen()
	{
		//cout << "\n\n Update Rate Scrren Will Be Here ...\n\n";
		cls_update_currency_rate_screen::update_currency_code();
		_go_to_back_to_main_menue();
	}

	static void _show_currency_calculator_screen()
	{
		//cout << "\n\n Currency Calculstor Screen Will Be Here ...\n\n";
		cls_currency_calculator_screen::courrency_calculator();
		_go_to_back_to_main_menue();
	}

	static void _go_to_back_to_main_menue()
	{		
		cout << "\n\n\t\tPress any key go to Currencies Menue...";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
		system("cls");
		_show_currency_exchange_menue();
	}

	static short _read_choose()
	{
		cout << "\n\t\tChoose want do you want to do ? [1 to 5]?";
		short choose = cls_input_validate::read_number_between(1, 5);
		return choose;
		
	}

	static void _perform_main_menue_option(en_main_screen choose)
	{
		switch (choose)
		{
		case cls_currency_exchange_screen::e_list_currencioe:
			system("cls");
			_show_list_currencies_screen();
			_go_to_back_to_main_menue();
			break;
		case cls_currency_exchange_screen::e_find_currency:
			system("cls");
			_show_find_currency_screen();
			_go_to_back_to_main_menue();
			break;
		case cls_currency_exchange_screen::e_update_rate:
			system("cls");
			_show_update_rate_screen();
			_go_to_back_to_main_menue();
			break;
		case cls_currency_exchange_screen::e_currency_calculator:
			system("cls");
			_show_currency_calculator_screen();
			_go_to_back_to_main_menue();
			break;
		case cls_currency_exchange_screen::e_min_menue:			
			break;

		}
	}

public:

	static void _show_currency_exchange_menue()
	{
		string main = "    Currency Exchange Main Screen";
		string sub  = "    .............................";
		_draw_screen_header(main, sub, cls_util::tabs(2));

		cout << "\t\t========================================\n";
		cout << "\t\t     Currency Exchange Menue";
		cout << "\n\t\t========================================\n";
		cout << "\t\t[1] List Currencies.\n";
		cout << "\t\t[2] Find Currency.\n";
		cout << "\t\t[3] Update Rate.\n";
		cout << "\t\t[4] Currency Calculator.\n";
		cout << "\t\t[5] Main Menue.\n";
		cout << "\t\t========================================\n";
		_perform_main_menue_option(en_main_screen(_read_choose()));
	}

};

