#pragma once
#include<iostream>
#include<vector>
using namespace std;

class cls_string
{
private:

	string _value;

public:

	cls_string()
	{
		_value = "";
	}

	cls_string(string value)
	{
		_value = value;
	}

	void set_value(string value)
	{
		_value = value;
	}

	string get_value()
	{
		return _value;
	}
		
	__declspec (property(get = get_value, put = set_value)) string value;

	//1-length.

	static int length_(string s)
	{
		return s.length();
	}

	int length_()
	{
		return length_(_value);
	}
	
	//2-convert first letter from word  to upper.

	static string upper_first_letter_of_each_word(string s)
	{
		bool first = true;
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ' ' && first)
			{
				s[i] = toupper(s[i]);
			}
			first = (s[i] == ' ' ? true : false);
		}
		return s;
	}

	void upper_first_letter_of_each_word()
	{
		upper_first_letter_of_each_word(_value);
	}

	//3-convert first letter from word to lower.

	static string lower_first_letter_of_each_word(string s)
	{
		bool first = true;
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ' ' && first)
			{
				s[i] = tolower(s[i]);
			}
			first = (s[i] == ' ' ? true : false);
		}
		return s;
	}

	void lower_firslower_first_letter_of_each_wordt_letter()
	{
		 lower_first_letter_of_each_word(_value);
	}
		
	//4-convert all letters to uppers.

	static string upper_all_letters(string s)
	{

		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ' ')
			{
				s[i] = toupper(s[i]);
			}
		}
		return s;
	}

	void upper_all_letters()
	{
		   upper_all_letters(_value);
	}
		
	//5-convert all letters to lowers.

	static string lower_all_letters(string s)
	{

		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ' ')
			{
				s[i] = tolower(s[i]);
			}
		}
		return s;
	}

	void lower_all_letters()
	{
		 lower_all_letters(_value);
	}

	//6-convert all letter.

	static char invert_letter(char c)
	{
		return isupper(c) ? tolower(c) : toupper(c);
	}

	static string invert_all_letters(string s)
	{

		for (int i = 0; i < s.length(); i++)
		{
			s[i] = invert_letter(s[i]);
		}
		return s;
	}
	
	void invert_all_letters()
	{
		  invert_all_letters(_value);
	}
	
	//7-counter for letters of upper or lower or both.
			
	static short counter_letters_all_small_cap(string s, char what_counter ='a')
	{
		short counter = 0;

		if (what_counter == 'a')
		{
			for (int i = 0; i < s.length(); i++)
			{
				if (islower(s[i]) || isupper(s[i]))
				{
					counter++;
				}
			}			
		}
		
		for (int i = 0; i < s.length(); i++)
		{
			if (what_counter == 's' && islower(s[i]))
			{
				counter++;
			}
			else if (what_counter == 'c' && isupper(s[i]))
			{
				counter++;
			}
		}
		return counter;
	}

	short counter_letters_all_small_cap(char what_counter = 'a')
	{
		return  counter_letters_all_small_cap(_value, what_counter);
	}
	
	//8-letter repetition.

	static short letter_repetition(char c, string s,bool match_case=true)
	{
		short counter = 0;
		if (match_case)
		{
			for (int i = 0; i < s.length(); i++)
			{
				if (s[i] == c)
				{
					counter++;
				}
			}
		}
		else
		{
			for (int i = 0; i < s.length(); i++)
			{
				if (tolower(s[i]) == tolower(c))
				{
					counter++;
				}
			}
		}
		
		return counter;
	}

	short letter_repetition(char c,bool match_case=true)
	{
		return  letter_repetition(c,_value,match_case);
	}
	
	//9-counter string words.

	static int counter_words(string s)
	{
		int counter = 0;
		string delim = " ";
		int pos = 0;
		string word;
		while ((pos = s.find(delim)) != std::string::npos)
		{
			word = s.substr(0, pos);
			if (word != "")
			{
				counter++;
			}
			s.erase(0, pos + delim.length());
		}
		if (s != "")
		{
			counter++;
		}
		return counter;
	}

	short counter_words()
	{
		return  counter_words(_value);
	}

	//10-trim left string.
		
	static	string trim_left(string s)
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ' ')
			{
				return s.substr(i, s.length() - i);
			}
		}
		return s;
	}

	void trim_left()
	{
		trim_left(_value);
	}

	//11-trim right string.

	static  string trim_right(string s)
	{
		for (int i = (s.length() - 1); i >= 0; i--)
		{
			if (s[i] != ' ')
			{
				return s.substr(0, i + 1);
			}
		}
		return s;
	}

	void trim_right()
	{
		trim_right(_value);
	}

	//12-trim string.

	static  string trim(string s)
	{
		return (trim_left(trim_right(s)));
	}

	string trim()
	{
		return  trim(_value);
	}
			
	//13-split string.

	static vector <string> split(string s, string delim)
	{
		vector <string> v_string;
		int pos = 0;
		string word;
		while ((pos = s.find(delim)) != std::string::npos)
		{
			word = s.substr(0, pos);
			if (word != "")
			{
				v_string.push_back(word);
			}
			s.erase(0, pos + delim.length());
		}
		if (s != "")
		{
			v_string.push_back(s);
		}
		return v_string;
	}

	vector <string> split()
	{
		return  split(_value, " ");

	}

	//14-join string.

	static string join_string(vector <string> v_string, string delim)
	{
		string ss;
		for (string& s : v_string)
		{
			ss = ss + s + delim;
		}
		return ss.substr(0, ss.length() - delim.length());
	}
			
	static	string join_string(string s_string[], short length, string delim)
	{
		string s = "";
		for (short i = 0; i < length; i++)
		{
			s = s + s_string[i] + delim;
		}
		return s.substr(0, s.length() - delim.length());
	}

	//15-reverse string.

	static string reverse_string(string s)
	{
		vector<string> v_string;
		v_string = split(s, " ");
		string s1 = "";
		vector <string>::iterator iter = v_string.end();
		while (iter != v_string.begin())
		{
			iter--;
			s1 += *iter + " ";
		}
		s1 = s1.substr(0, s1.length() - 1);
		return s1;

	}

	void reverse_string()
	{
		  reverse_string(_value);
	}
	
	//16-replace.

	static string replace_string(string st, string word_orgenal, string word_new, bool math_case = true)
	{
		vector <string> v_string = split(st," ");
		for (string& s : v_string)
		{
			if (math_case)
			{
				if (s == word_orgenal)
				{
					s = word_new;
				}
			}
			else
			{
				if (lower_all_letters(s) == lower_all_letters(word_orgenal))
				{
					s = word_new;
				}
			}
		}
		return join_string(v_string, " ");
	}

	void replace_string(string word_orgenal, string word_new,bool math_case=true)
	{
		   replace_string(_value, word_orgenal, word_new);
	}
	
	//17-remove punctution.

	static string remove_punctuation(string s)
	{
		string s2;
		for (int i = 0; i < s.length(); i++)
		{
			if (!ispunct(s[i]))
			{
				s2 += s[i];
			}
		}
		return s2;
	}

	void remove_punctuation()
	{
		  remove_punctuation(_value);
	}

	//18- char is vowel.

	static bool is_vowel(char c)
	{
		if (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'o' || c == 'u' || c == 'U')
		{
			return true;
		}
		return false;
	}

	//19- counter chars vowels.

	static int counter_vowel_letters(string s)
	{
		int counter = 0;
		for (int i = 0; i < s.length(); i++)
		{
			if (is_vowel(s[i]))
			{
				counter++;
			}
		}
		return counter;
	}

	short counter_vowel_letters()
	{
		return  counter_vowel_letters(_value);
	}



};

