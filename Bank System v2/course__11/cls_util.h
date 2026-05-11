#pragma once
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include"cls_date.h"
#include"cls_string.h"
#include<iomanip>
using namespace std;



class cls_util
{
public:

	static void srand_()
	{
		srand((unsigned)time(NULL));
	}

	static int random_number(int from, int to)
	{
		int random = rand() % (to - from + 1) + from;
		return random;
	}

	enum en_char_type{small_letter=1,capital_letter=2,mix_char=4,digit=3,special_char=5};

	static char generate_char(en_char_type char_type)
	{
		if (char_type == mix_char)
		{
			char_type = (en_char_type)random_number(1, 3);
		}
		switch (char_type)
		{
		case cls_util::small_letter:
			return char(random_number(97, 122));
			break;
		case cls_util::capital_letter:
			return char(random_number(65, 90));
			break;			
		case cls_util::digit:
			return char(random_number(48, 57));
			break;
		case cls_util::special_char:
			return char(random_number(33, 47));
			break;
		default:
			return char(random_number(65, 90));
			break;
		}
	}
	
	static string generate_word(en_char_type char_type, short length)
	{
		string word;
		for (int i = 0; i < length; i++)
		{
			word = word + generate_char(char_type);
		}
		return word;
	}

	static string generate_key(en_char_type char_type)
	{
		string key;
		for (int i = 0; i < 4; i++)
		{
			key = key +" "+ generate_word(char_type, 4);
		}
		key = cls_string::trim(key);

		return key;
	}

	static void generate_keys(en_char_type char_type, short length)
	{
		string key;
		for (int i = 1; i <= length; i++)
		{
			key = generate_key(char_type);
			cout << setw(2) << i ;
			cout <<  ": " << key << endl;
				 			
		}
	}

   static  void swap(int& a, int& b)
	{
		int c = 0;
		c = a;
		a = b;
		b = c;

	}

	static void swap(char& a, char& b)
	{
		char c;
		c = a;
		a = b;
		b = c;
	}

	static void swap(double& a, double& b)
	{
		double c = 0;
		c = a;
		a = b;
		b = c;

	}

	static void swap(string& a, string& b)
	{
		string c ;
		c = a;
		a = b;
		b = c;

	}

	static void swap(cls_date& date1, cls_date& date2)
	{
		cls_date::swap_date(date1, date2);
	}

	static void fill_array_with_random_numbers(int array[100], int length, int from, int to)
	{
		for (int i = 0; i < length; i++)
		{
			array[i] = random_number(from, to);
		}
	}

	static void fill_array_with_random_words(string array[100], int length, en_char_type char_type, short length_word)
	{
		for (int i = 0; i < length; i++)
		{
			array[i] = generate_word(char_type, length_word);
		}
	}

	static void fill_array_with_random_keys(string array[100], int key_length, en_char_type char_type)
	{
		for (int i = 0; i < key_length; i++)
		{
			array[i]=generate_key(char_type);
		}
	}

	static void shuffle_array(int array[100], int length)
	{
		

		for (int i = 0; i < length - 1; i++)
		{
			swap(array[random_number(1, length) - 1], array[random_number(1, length) - 1]);
		}
	}

	static void shuffle_array(string array[100], int length)
	{
		for (int i = 0; i < length; i++)
		{
			swap(array[random_number(1, length) - 1], array[random_number(1, length) - 1]);
		}
	}

	static string tabs(short number)
	{
		string t = " ";
		for (int i = 0; i < number; i++)
		{
			t = t + "\t";			
		}
		
		return t;
	}

	static string encryption_text(string text, short enc)
	{
		for (int i = 0; i < text.length(); i++)
		{
			text[i] = char((int)text[i] + enc);

		}
		return text;
	}

	static string decryption_text(string text, short enc)
	{
		for (int i = 0; i < text.length(); i++)
		{
			text[i] = char((int)text[i] - enc);

		}
		return text;
	}

	static string convert_number_to_txt(int number)
	{
		if (number == 0)
		{
			return " ";
		}
		if (number >= 1 && number <= 19)
		{
			string array[] = { " ","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven","Twelve",
							   "Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
			return array[number] + " ";
		}
		if (number >= 20 && number <= 99)
		{
			string array[] = { " "," ","Twenty","Thirty","Fourty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return array[number / 10] + " " + convert_number_to_txt(number % 10) + " ";
		}
		if (number >= 100 && number <= 199)
		{
			return "One Hundred and " + convert_number_to_txt(number % 100);
		}
		if (number >= 200 && number <= 999)
		{
			return convert_number_to_txt(number / 100) + "Hundred and " + convert_number_to_txt(number % 100);
		}
		if (number >= 1000 && number <= 1999)
		{
			return "One Thousand and " + convert_number_to_txt(number % 1000);
		}
		if (number >= 2000 && number <= 999999)
		{
			return convert_number_to_txt(number / 1000) + "Thousand and " + convert_number_to_txt(number % 1000);
		}
		if (number >= 1000000 && number <= 1999999)
		{
			return "One million and " + convert_number_to_txt(number % 1000000);
		}
		if (number >= 2000000 && number <= 999999999)
		{
			return convert_number_to_txt(number / 1000000) + "Million and " + convert_number_to_txt(number % 1000000);
		}
		if (number >= 1000000000 && number <= 1999999999)
		{
			return "One Billion and " + convert_number_to_txt(number % 1000000000);
		}
		else
		{
			return convert_number_to_txt(number / 1000000000) + "Billions and " + convert_number_to_txt(number % 1000000000);
		}
	}


};

