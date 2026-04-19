#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

// ÊÚÑíİ ÇÓã Çáãáİ Úáì ãÓÊæì ÇáÈÑäÇãÌ .
string file_name = "clients.txt";

// ÊÕÑíÍ Úä ÇáÏæÇá ãä ÇÌá ãÑæäÉ ÇáÚãá .
void add_new_client();
void delete_client();
void update_client_info();
void find_client();
void run_project();

// ÚÑÖ ŞÇÆãÉ ÇáÎÏãÇÊ .
void show_main_screen()
{
	cout << "=======================================================";
	cout << "\n";
	cout << "\t\t\t";
	cout << "Main Screen";
	cout << "\n";
	cout << "=======================================================";
	cout << "\n";
	cout << "[1] Show All Clients.";
	cout << "\n";
	cout << "[2] Add New Client.";
	cout << "\n";
	cout << "[3] Delet Client.";
	cout << "\n";
	cout << "[4] Update Client.";
	cout << "\n";
	cout << "[5] Find Client.";
	cout << "\n";
	cout << "[6] Exit.";
	cout << "\n";
	cout << "=======================================================";

}

 
enum en_choice
{
	show = 1,
	add=2,
	delet=3,
	update=4,
	find_=5,
	exit_=6
};

// ÊÌãíÚ ãÚáæãÇÊ ÇáÚãíá Öãä struct .
struct st_client_info
{
	string account_number;
	string pin_code;
	string client_name;
	string phone_number;
	float balance;
	bool for_delete = false;
};

// ŞÑÇÁÉ äæÚ ÇáÚãáíÉ ÇáÊí íÑíÏåÇ ÇáãÓÊÎÏã .
en_choice read_choice(string message)
{
	short operation_type;
	cout << message;
	cin >> operation_type;
	return (en_choice)operation_type;
}

// ŞÑÇÁÉ ÇáÈíÇäÇÊ ãä Çáãáİ æÊÍãíáåã Úáì vector . 
vector<string> read_file()
{
	vector<string>file;
	fstream f;
	f.open(file_name, ios::in);

	if (f.is_open())
	{
		string line;
		while (getline(f,line))
		{
			file.push_back(line);
		}
		f.close();
	}	
	return file;
}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÊÍæíá ÇáäÕ Çáì ßáãÇÊ .
vector<string> split(string line,string delim="#//#")
{
	vector<string> v;
	short pos = 0;
	string word;
	while ((pos=line.find(delim)) != std::string::npos)
	{
		word = line.substr(0, pos);

		if(word != "")
		{ 
			v.push_back(word);
		}
		line.erase(0, pos + delim.length());
	}
	if (line != "")
	{
		v.push_back(line);
	}

	return v;
}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÊÍæíá ÇáäÕ Çáì ÈíÇäÇÊ .
st_client_info convert_line_to_data(vector <string> v)
{
	st_client_info client_info;
	client_info.account_number = v[0];
	client_info.pin_code = v[1];
	client_info.client_name = v[2];
	client_info.phone_number = v[3];
	client_info.balance = stof(v[4]);

	return client_info;
}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÊÍæíá ÇáÈíÇäÇÊ äÕ .
string convert_data_to_line(st_client_info client_info,string delim="#//#")
{
	string line;
	line = client_info.account_number + delim;
	line += client_info.pin_code + delim;
	line += client_info.client_name + delim;
	line += client_info.phone_number + delim;
	line += to_string(client_info.balance) + delim;
	return line;
}

// ÇáÍÕæÇá Úáì ÌãíÚ ÇáÈíÇäÇÊ ÇáãæÌæÏÉ Úáì Çáãáİ .
vector<st_client_info> get_all_clients_data()
{
	vector<st_client_info>clients_data;

	vector<string> file_data = read_file();	

	for (const string& line : file_data)
	{
		clients_data.push_back(convert_line_to_data(split(line)));
	}

	return clients_data;
}

// ØÈÇÚÉ ÈíÇäÇÊ ÇáÚãíá .
void print_client_data(const st_client_info& client_info)
{
	cout << "| " << left << setw(16) << client_info.account_number;
	cout << "| " << left << setw(12) << client_info.pin_code;
	cout << "| " << left << setw(28) << client_info.client_name;
	cout << "| " << left << setw(13) << client_info.phone_number;
	cout << "| " << left << setw(13) << to_string(client_info.balance);
}

// ØÈÇÚÉ ÈíÇäÇÊ ÌãíÚ ÇáÚãáÇÁ  .
void show_all_clients_screen()
{
	vector<st_client_info> clients_data = get_all_clients_data();	

	cout << "\t\t\t\t";
	cout << "Clients List (" << clients_data.size() << ") " << "Client(s).";
	cout << "\n";
	cout << "______________________________________________________________________________________________";
	cout << "\n\n";
	cout << left << setw(18) << "| Account Number";
	cout << left << setw(14) << "| Pin Code";
	cout << left << setw(30) << "| Client Name";
	cout << left << setw(15) << "| Phone";
	cout << left << setw(15) << "| Balance";
	cout << "\n";
	cout << "______________________________________________________________________________________________";
	cout << "\n\n";

	
 
	for (const st_client_info& client_info : clients_data)
	{
		print_client_data(client_info);
		cout << endl;
	}
	
	cout << "______________________________________________________________________________________________";

}

// ÊäÙíİ ÇáÔÇÔÉ .
void clear_screen()
{
	system("cls");
}

// ÇáĞåÇÈ Çáì ÇáŞÇÆãÉ ÇáÑÆíÓíÉ .
void go_to_main_menue()
{
	cout << "\n\nPress any key to go back to main menue...";
	cin.ignore();
	cin.get();
	clear_screen();
	//run_project();
}

// ÊäİíĞ ÇÎÊíÇÑ ÇáãÓÊÎÏã .
void implementing_use_selection(en_choice operation)
{
	switch (operation)
	{
	case show:
		clear_screen();
		show_all_clients_screen();
		go_to_main_menue();
		break;
	case add:
		add_new_client();
		go_to_main_menue();
		break;
	case delet:
		delete_client();
		go_to_main_menue();
		break;
	case update:
		update_client_info();
		go_to_main_menue();
		break;
	case find_:
		find_client();
		go_to_main_menue();
		break;
	case exit_:
		exit(0);
		break;
	default:
		exit(0);
		break;
	}
}


// ŞÑÇÁÉ ÑŞã ÍÓÇÈ ÇáãÓÊÎÏã
string read_account_number()
{
	string account_number;
	cout << "\nEnter account number please : ";
	cin >> account_number;
	return account_number;
}

// ÏÇáÉ ÎÇÕÉ ãä ÇáÊÔííß Úáì ÑŞã ÇáÍÓÇÈ ãä ÇÌá ÚÏã ÇáÊÖÇÑÈ ÚäÏ ÇáÇÖÇİÉ .
bool check_account_number_for_add(string account_number)
{
	vector<st_client_info>clients_info = get_all_clients_data();	
	for (const st_client_info& client_info : clients_info)
	{
		if (client_info.account_number == account_number)
		{
			return true;
		}		
	}
	return false;
}

// ŞÑÇÁÉ ÈíÇäÇÊ ÇáÚãíá ÇáÌÏíÏ .
st_client_info read_new_client_data(string account_number)
{
	st_client_info client_info;

	client_info.account_number = account_number;

	cout << "\nEnter Pin Code please: ";
	cin >> client_info.pin_code;	

	cout << "\nEnter Name please: ";
	cin.ignore();
	getline(cin, client_info.client_name);

	cout << "\nEnter Phone Number please: ";
	cin >> client_info.phone_number;

	cout << "\nEnter Balance please: ";
	cin >> client_info.balance;

	return client_info;
}

// ÇÖáİÉ ÈíÇäÇÊ ÇáÚãíá ÇáÌÏíÏ Çáì Çáãáİ .
void add_client_to_file(const st_client_info& client_info)
{
	fstream file;
	file.open(file_name, ios::out | ios::app);

	if (file.is_open())
	{				
		file << convert_data_to_line(client_info) << endl;
	}
	file.close();	
}

// ØÈÇÚÉ äæÚ ÇáÚãáíÉ ÇáÍÇáíÉ .
void print_head_screen(string operation)
{

	cout << "=======================================================";
	cout << "\n";
	cout << "\t\t\t";
	cout << operation;
	cout << "\n";
	cout << "=======================================================";

}


// ÇáÊÇßÏ ŞÈá ÊäİíĞ ÇáÚãáíÉ .
bool sure_the_process(string message)
{
	char answer;
	cout << message;
	cin >> answer;
	return (answer == 'y' || answer == 'Y');
}

// ÇáÓÄÇá ãä ÇÌá ÇáãÊÇÈÚÉ İí äİÓ ÇáÚãáíÉ æÚÏã ÇáÎÑæÌ ãäåÇ .
char follow_up(string message)
{
	char answer;
	cout << message;
	cin >> answer;
	return answer ;
}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÇÖÇİÉ Úãíá ÌÏíÏ .
void add_new_client()
{
	char follow = 'n';

	do
	{
		clear_screen();
		print_head_screen("Add Client");

		string account_number = read_account_number();
		

		while (check_account_number_for_add(account_number))
		{
			cout << "\nError...the account number (" << account_number << ") exists, enter another account number: ";
			cin >> account_number;
			
		}

		st_client_info client_info = read_new_client_data(account_number);
				

		if (sure_the_process("\nAre you sure from add new client [Y/N] ? "))
		{
			add_client_to_file(client_info);
			follow = follow_up("\nClient added successfully, do you want to add more clients [Y/N]? ");
		}

	} while (follow=='y' || follow=='Y');
}

// ÇáÍÕæá Úáì ÈíÇäÇÊ Úãíá ãä ÎáÇá ÑŞã ÇáÍÓÇÈ .
bool find_client_by_account(string account_number,st_client_info& client_info_)
{
	vector<st_client_info> clients_info = get_all_clients_data();	
	for (const st_client_info& client_info : clients_info)
	{
		if (client_info.account_number == account_number)
		{
			client_info_ = client_info;
			return true;
		}
	}
	return false;
}


// ÊÛííÑ ÍÇáÉ ãÊÛííÑ ÇáÍĞİ ãä ÇÌá ÍĞİ ÇáÚãíá ÇáãØáæÈ .
void convert_for_delete(vector<st_client_info>& clients_info,string account_number)
{	
	for ( st_client_info& client_info : clients_info)
	{
		if (client_info.account_number == account_number)
		{
			client_info.for_delete = true;
			break;
		}
	}
}

// ØÈÇÚÉ ÈíÇäÇÊ ÇáÚãíá .
void print_client_info(st_client_info client_info)
{
	cout << "\n\n_______________________________________\n";
	cout << "\nAccount Number : " << client_info.account_number;
	cout << "\nPin Code : " << client_info.pin_code;
	cout << "\nClient Name : " << client_info.client_name;
	cout << "\nPhone Number : " << client_info.phone_number;
	cout << "\nBalance : " << client_info.balance;
	cout << "\n_______________________________________";
}

// ÍĞİ ÇáÚãíá ãä Çáãáİ .
void delete_client_from_file(const vector<st_client_info>& clients_info)
{
	fstream file;
	file.open(file_name, ios::out);

	if (file.is_open())
	{
		for (short i = 0; i < clients_info.size(); i++)
		{
			if (clients_info[i].for_delete == false)
			{
				file << convert_data_to_line(clients_info[i]) << endl;
			}
			
		}
	}

	file.close();
}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÍĞİ Úãíá .
void delete_client()
{
	char follow = 'n';

	do
	{
		clear_screen();

		print_head_screen("Delete Client");

		string account_number = read_account_number();

		st_client_info client_info;

		if (find_client_by_account(account_number, client_info))
		{
			print_client_info(client_info);
			if (sure_the_process("\nAre you sure from delete this client [Y/N] ? "))
			{
				vector<st_client_info> clients_info = get_all_clients_data();
				convert_for_delete(clients_info, account_number);
				delete_client_from_file(clients_info);
				follow=follow_up("\nClient deleted successfully, do you want to delete more more clients [Y/N]? ");
			}
		}
		else
		{
			cout << "Client with account number ( " << account_number << " ) is not found !! ";
		}

	} while (follow=='y' || follow=='Y');
		
}


// ÊÔÛíá ÇáÈÑäÇãÌ ....ÇáÏÇáÉ ÇáäåÇÆíÉ .
void run_project()
{
	
	show_main_screen();	
	en_choice choice = read_choice("\nChoose want do you want to do [1 to 6] ? ");
	implementing_use_selection(choice);

}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÊÍÏíË ÈíÇäÇÊ Úãíá .
vector<st_client_info> update_data(const st_client_info& new_client)
{
	vector<st_client_info> clients_info = get_all_clients_data();

	for (st_client_info& client : clients_info)
	{
		if (client.account_number == new_client.account_number)
		{
			client = new_client;
			break;
		}
	}

	return clients_info;
}


// ÊÍÏíË ÈíÇäÇÊ Çáãáİ .
void update_file(const vector<st_client_info>& clients_info)
{
	fstream file;

	file.open(file_name, ios::out);

	if (file.is_open())
	{
		for (const st_client_info& client_info : clients_info)
		{
			file << convert_data_to_line(client_info) << endl;			
		}
	}

	file.close();
}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÊÍÏíË ÈíÇäÇÊ Úããíá .
void update_client_info()
{
	char follow = 'n';

	do
	{
		follow = 'n';

		clear_screen();

		print_head_screen("Update Client");

		string account_number = read_account_number();

		st_client_info client_info;

		if (find_client_by_account(account_number, client_info))
		{
			print_client_info(client_info);
			if (sure_the_process("\nAre you sure from update this client info [Y/N] ? "))
			{
				client_info=read_new_client_data(account_number);
				vector<st_client_info> clients_info =update_data(client_info);
				update_file(clients_info);
				follow = follow_up("\nClient updated successfully, do you want to update more more clients [Y/N]? ");
			}
		}
		else
		{
			cout << "Client with account number ( " << account_number << " ) is not found !! ";
		}

	} while (follow == 'y' || follow == 'Y');


}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÇíÌÇÏ ÈíÇäÇÊ Úãíá Úä ØÑíŞ ÑŞã ÇáÍÓÇÈ .
void find_client()
{
	char follow = 'n';

	do
	{
		follow = 'n';

		clear_screen();

		print_head_screen("Find Client");

		string account_number = read_account_number();

		st_client_info client_info;

		if (find_client_by_account(account_number, client_info))
		{
			print_client_info(client_info);

			follow = follow_up("\n\ndo you want to find  more clients [Y/N]? ");
		
		}
		else
		{
			cout << "Client with account number ( " << account_number << " ) is not found !! ";
		}

	} while (follow == 'y' || follow == 'Y');


}

int main()
{
	while (true)
	{
		run_project();
	}

	
}

