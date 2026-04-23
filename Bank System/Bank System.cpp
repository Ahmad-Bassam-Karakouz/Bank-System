#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;


enum en_transaction_type
{
	deposit = 1,
	withdraw = 2,
	total_balances = 3,
	main_menue = 4
};

enum en_choice
{
	show = 1,
	add_client = 2,
	delete_client = 3,
	update_client = 4,
	find_client = 5,
	transactions = 6,
	exit_from_project = 7
};

// ÊÌãíÚ ãÚáæãÇÊ ÇáÚãíá Öãä struct .

struct st_client_info
{
	string account_number;
	string pin_code;
	string client_name;
	string phone_number;
	double balance;
	bool for_delete = false;
};

// ÊÚÑíİ ÇÓã Çáãáİ Úáì ãÓÊæì ÇáÈÑäÇãÌ .

string file_name = "clients.txt";


// ÊÕÑíÍ Úä ÇáÏæÇá ãä ÇÌá ãÑæäÉ ÇáÚãá .

void show_main_menu();
void show_add_new_client_screen();
void show_delete_client_screen();
void show_update_client_screen();
void show_find_client_screen();

void show_transactions_main_screen();
void show_withdraw_screen();
void show_deposit_screen();
void show_all_clients_screen();

void go_to_main_menu();
void clear_screen();


void handle_choice(en_choice);
en_choice read_choice(string);
void handle_transactions(en_transaction_type);
en_transaction_type read_transaction_type(string);


// åĞå ÇáÏÇáÉ ÊÇÈÚÉ á show_all_clients_screen .

void print_client_data(const st_client_info& client_data)
{
	cout << "| " << left << setw(16) << client_data.account_number;
	cout << "| " << left << setw(12) << client_data.pin_code;
	cout << "| " << left << setw(28) << client_data.client_name;
	cout << "| " << left << setw(13) << client_data.phone_number;
	cout << "| " << left << setw(13) << to_string(client_data.balance);
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
		while (getline(f, line))
		{
			file.push_back(line);
		}
		f.close();
	}
	return file;
}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÊÍæíá ÇáäÕ Çáì ßáãÇÊ .

vector<string> split(string line, string delim = "#//#")
{
	vector<string> v;
	short pos = 0;
	string word;
	while ((pos = line.find(delim)) != std::string::npos)
	{
		word = line.substr(0, pos);

		if (word != "")
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

st_client_info convert_line_to_data(string line)
{
	vector<string> v = split(line);

	st_client_info client_info;
	client_info.account_number = v[0];
	client_info.pin_code = v[1];
	client_info.client_name = v[2];
	client_info.phone_number = v[3];
	client_info.balance = stof(v[4]);

	return client_info;
}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÊÍæíá ÇáÈíÇäÇÊ äÕ .

string convert_data_to_line(st_client_info client_info, string delim = "#//#")
{
	string line;
	line = client_info.account_number + delim;
	line += client_info.pin_code + delim;
	line += client_info.client_name + delim;
	line += client_info.phone_number + delim;
	line += to_string(client_info.balance) ;
	return line;
}

// ÇáÍÕæÇá Úáì ÌãíÚ ÇáÈíÇäÇÊ ÇáãæÌæÏÉ Úáì Çáãáİ .
vector<st_client_info> get_all_clients_data()
{
	vector<st_client_info>clients_data;

	vector<string> file_data = read_file();

	for (const string& line : file_data)
	{
		clients_data.push_back(convert_line_to_data(line));
	}

	return clients_data;
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

bool check_account_number(string account_number,vector<st_client_info>& v_clients,st_client_info& client)
{
	for (const st_client_info& client_info : v_clients)
	{
		if (client_info.account_number == account_number)
		{
			client = client_info;
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
	return answer;
}

// ÊÛííÑ ÍÇáÉ ãÊÛííÑ ÇáÍĞİ ãä ÇÌá ÍĞİ ÇáÚãíá ÇáãØáæÈ .

void mark_of_delete(string account_number, vector<st_client_info>& clients_info)
{
	for (st_client_info& client_info : clients_info)
	{
		if (client_info.account_number == account_number)
		{
			client_info.for_delete = true;
			break;
		}
	}
}

// ØÈÇÚÉ ÈíÇäÇÊ ÇáÚãíá .

void print_client_info(const st_client_info& client_info)
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

void save_new_file(const vector<st_client_info>& clients_info)
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

// ŞÑÇÁÉ ÇáãÈáÛ .

double read_amount(string message)
{
	double amount = 0;
	do
	{
		cout << message;
		cin >> amount;

	} while (amount <= 0);


	return amount;
}

// ÊØÈíŞ ÇáÚãáíÉ Úáì Çáãáİ ÇáÇÓÇÓí (ÈÔßá ÑÓãí) ÓæÇÁ ÓÍÈ Çæ ÇíÏÇÚ . 

double update_balance(vector<st_client_info>& clients_info, string account_number, double amount)
{
	for (st_client_info& client_info : clients_info)
	{
		if (client_info.account_number == account_number)
		{
			client_info.balance += amount;
			return client_info.balance;
		}
	}
	return 0;
}

// ÇáÊÍŞŞ ãä ÚãáíÉ ÇáÓÍÈ ŞÈá ÇáÊäİíĞ .

bool check_withdraw_process(const st_client_info& client, double amount)
{
	return (client.balance >= amount);

}

//  åĞå ÇáÏÇáÉ ÊÇÈÚÉ áá total balances .

void print_client_info_for_balance( st_client_info& client)
{

	cout << "| " << left << setw(28) << client.client_name;
	cout << "| " << left << setw(16) << client.account_number;
	cout << "| " << left << setw(13) << to_string(client.balance);
}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÊÍÏíË ÈíÇäÇÊ Úãíá .

void update_data(vector<st_client_info>& clients_info, const st_client_info& new_client)
{

	for (st_client_info& client : clients_info)
	{
		if (client.account_number == new_client.account_number)
		{
			client = new_client;
			break;
		}
	}


}

// ÊØÈíŞ ÇáÊÍÏíË Úáì Çáãáİ .

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

// show_add_new_client_screen åĞå ÇáÏÇáÉ ãÓÊÎÏãÉ İí .

bool is_account_number_exists(string account_number)
{
	vector<string>v_clients;
	fstream file;
	file.open(file_name, ios::in);

	if (file.is_open())
	{
		st_client_info client;
		string line;
		while (getline(file, line))
		{
			client = convert_line_to_data(line);
			if (client.account_number == account_number)
			{
				file.close();
				return true;
			}
		}		
	}
	file.close();
	return false;
}


// CRUD.

// ÚÑÖ ŞÇÆãÉ ÇáÎÏãÇÊ .

void show_main_menu()
{
	clear_screen();
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
	cout << "[6] Transactions.";
	cout << "\n";
	cout << "[7] Exit.";
	cout << "\n";
	cout << "=======================================================";
	handle_choice(read_choice("\nChoose want do you want to do[1 to 7] ?"));
}

// ŞÑÇÁÉ äæÚ ÇáÚãáíÉ ÇáÊí íÑíÏåÇ ÇáãÓÊÎÏã .

en_choice read_choice(string message)
{
	short operation_type;
	cout << message;
	cin >> operation_type;
	return (en_choice)operation_type;
}

// ÊäÙíİ ÇáÔÇÔÉ .

void clear_screen()
{
	system("cls");
}

// ÇáÑÌæÚ Çáì ÇáŞÇÆãÉ ÇáÑÆíÓíÉ .

void go_to_main_menu()
{
	cout << "\n\nPress any key to go back to main menue...";
	cin.ignore();
	cin.get();	
	show_main_menu();
}

// ÊäİíĞ ÇÎÊíÇÑ ÇáãÓÊÎÏã .

void handle_choice(en_choice choice)
{
	switch (choice)
	{
	case show:		

		show_all_clients_screen();
		go_to_main_menu();
		break;
	case add_client:		
		show_add_new_client_screen();
		go_to_main_menu();
		break;
	case delete_client:		
		show_delete_client_screen();
		go_to_main_menu();
		break;
	case update_client:		
		show_update_client_screen();
		go_to_main_menu();
		break;
	case find_client:		
		show_find_client_screen();
		go_to_main_menu();
		break;
	case transactions:		
		show_transactions_main_screen();
		break;
	case exit_from_project:
		exit(0);
		break;
	default:
		exit(0);
		break;
	}
}

//  ÔÇÔÉ ØÈÇÚÉ ÈíÇäÇÊ ÌãíÚ ÇáÚãáÇÁ  .

void show_all_clients_screen()
{
	clear_screen();

	vector<st_client_info> v_clients = get_all_clients_data();

	cout << "\t\t\t\t";
	cout << "Clients List (" << v_clients.size() << ") " << "Client(s).";
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



	for (const st_client_info& client : v_clients)
	{
		print_client_data(client);
		cout << endl;
	}

	cout << "______________________________________________________________________________________________";

}

// ÔÇÔÉ ÇÖÇİÉ Úãíá ÌÏíÏ .

void show_add_new_client_screen()
{
	char follow = 'n';

	do
	{
		clear_screen();
		
		print_head_screen("Add Client");
		string account_number = read_account_number();

		while (is_account_number_exists(account_number))
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

	} while (follow == 'y' || follow == 'Y');
}

// ÔÇÔÉ ÍĞİ Úãíá   .

void show_delete_client_screen()
{
	char follow = 'n';

	do
	{		
		clear_screen();

		print_head_screen("Delete Client");

		vector<st_client_info>v_clients = get_all_clients_data();

		st_client_info client;

		string account_number = read_account_number();

		while (!check_account_number(account_number,v_clients,client))
		{
			cout << "Client with account number ( " << account_number << " ) is not found !! ";
			account_number = read_account_number();
		}
				
		print_client_info(client);

		if (sure_the_process("\nAre you sure from delete this client [Y/N] ? "))
		{
			
			mark_of_delete(account_number, v_clients);
			save_new_file(v_clients);
			follow = follow_up("\nClient deleted successfully, do you want to delete more more clients [Y/N]? ");
		}


	} while (follow == 'y' || follow == 'Y');

}

// ÔÇÔÉ  ÊÍÏíË ÈíÇäÇÊ Úããíá .

void show_update_client_screen()
{
	char follow = 'n';

	do
	{
		follow = 'n';

		clear_screen();

		print_head_screen("Update Client");

		vector<st_client_info> v_clients = get_all_clients_data();

		st_client_info client;

		string account_number = read_account_number();

		while (!check_account_number(account_number,v_clients,client))
		{
			cout << "Client with account number ( " << account_number << " ) is not found !! ";
			 account_number = read_account_number();
		}
				
		print_client_info(client);

		if (sure_the_process("\nAre you sure from update this client info [Y/N] ? "))
		{
			client = read_new_client_data(account_number);
			
			update_data(v_clients, client);

			update_file(v_clients);

			follow = follow_up("\nClient updated successfully, do you want to update more more clients [Y/N]? ");
		}

	} while (follow == 'y' || follow == 'Y');

}

// ÔÇÔÉ ÇáÈÍË Úä Úãíá .

void show_find_client_screen()
{
	char follow = 'n';

	do
	{
		follow = 'n';
		
		clear_screen();

		print_head_screen("Find Client");

		vector<st_client_info> v_clients = get_all_clients_data();

		st_client_info client;


		string account_number = read_account_number();

		if (check_account_number(account_number,v_clients,client))
		{
					
			print_client_info(client);
			follow = follow_up("\n\ndo you want to find  more clients [Y/N]? ");
		}
		else
		{
			cout << "Client with account number ( " << account_number << " ) is not found !! ";
		}

	} while (follow == 'y' || follow == 'Y');

}

// TRANSACTIONS .

// ÇáÔÇÔÉ ÇáÑÆíÓíÉ ÇáÎÇÕÉ ÈÇáÚãáíÇÊ .

void show_transactions_main_screen()
{
	clear_screen();
	print_head_screen("Transactions Menue");
	cout << "\n[1] Deposit.";
	cout << "\n[2] Withdraw.";
	cout << "\n[3] Total Balances.";
	cout << "\n[4] Main Menue.";
	cout << "\n=======================================================";
	handle_transactions(read_transaction_type("\nChoose what do you want to do [1 to 4] ? "));
}

// ŞÑÇÁÉ äæÚ ÇáÚãáíÉ ÇáÊí íÑíÏåÇ ÇáãÓÊÎÏã ÇáÎÇÕÉ ÈÇá transactions .

en_transaction_type read_transaction_type(string message)
{
	short transaction_type;
	cout << message;
	cin >> transaction_type;
	return (en_transaction_type)transaction_type;
}

// ÇáÑÌæÚ Çáì ŞÇÆãÉ ÇáÚãáíÇÊ .

void go_to_transaction_menu()
{
	cout << "\n\nPress any key to go back to transactions menue...";
	cin.ignore();
	cin.get();	
	show_transactions_main_screen();
}

// ÊäİíĞ äæÚ ÇáÚãáíÉ  .

void handle_transactions(en_transaction_type transaction_type)

{
	switch (transaction_type)
	{
	case deposit:
		clear_screen();
		show_deposit_screen();
		go_to_transaction_menu();
		break;
	case withdraw:	
		clear_screen();
		show_withdraw_screen();
		go_to_transaction_menu();
		break;
	case total_balances:
		clear_screen();
		show_all_clients_screen();
		go_to_transaction_menu();
		break;
	case main_menue:	
		show_main_menu();
		break;
	default:
		exit(0);
		break;
	}
}

// ÔÇÔÉ ÚÑÖ ÚãáíÉ ÇáÇíÏÇÚ .

void show_deposit_screen()
{
	

	print_head_screen("Deposit Screen");

	vector<st_client_info> v_clients = get_all_clients_data();

	st_client_info client;

	string account_number = read_account_number();

	while (!check_account_number(account_number,v_clients, client))
	{
		cout << "Client with account number ( " << account_number << " ) is not found !! ";
		account_number = read_account_number();
	}	
	
	print_client_info(client);

	double amount = read_amount("\nWhat is the amunt deposited ? ");
	if (sure_the_process("\nAre you sure from this process [Y/N] ? "))
	{

		
		double new_amount = update_balance(v_clients,account_number, amount);
		update_file(v_clients);
		cout << "\n\nThe deposit process was successful...Your current balance is " << new_amount << " .\n";
	}	

}

// ÔÇÔÉ ÚÑÖ ÚãáíÉ ÇáÓÍÈ .

void show_withdraw_screen()
{
	

	print_head_screen("Withdraw Screen");

	vector<st_client_info> v_clients = get_all_clients_data();
	st_client_info client;

	string account_number = read_account_number();

	while (!check_account_number(account_number,v_clients,client))
	{
		cout << "\nClient with account number ( " << account_number << " ) is not found !! ";
		account_number = read_account_number();
	}
		
	print_client_info(client);

	double amount = read_amount("\nWhat is the amunt Withdraw (please enter a positive number) ? ");

	if (check_withdraw_process(client, amount))
	{
		if (sure_the_process("\nAre you sure from this process [Y/N] ? "))
		{

			double new_amount = update_balance(v_clients, account_number, amount * -1);
			update_file(v_clients);
			cout << "\n\nThe Withdraw process was successful...Your current balance is " << new_amount << " .\n";
		}
	}
	else
	{
		cout << "\nYou cannot perform the withdrawal process because your balance is : " << client.balance << " .\n";
	}

}

// ÔÇÔÉÚÑÖ Çá Total balances .

void show_total_balances_screen()
{
	

	vector<st_client_info> v_clients = get_all_clients_data();
	float total_balances = 0;
	cout << "\n";
	cout << "\t\t\t";
	cout << "Balances List (" << v_clients.size() << ") " << "Client(s).";
	cout << "\n";
	cout << "______________________________________________________________________________";
	cout << "\n\n";
	cout << left << setw(30) << "| Client Name";
	cout << left << setw(18) << "| Account Number";
	cout << left << setw(15) << "| Balance";
	cout << "\n";
	cout << "______________________________________________________________________________";
	cout << "\n\n";



	for ( st_client_info& client : v_clients)
	{
		total_balances += client.balance;
		print_client_info_for_balance(client);
		cout << endl;
	}

	cout << "______________________________________________________________________________";
	cout << "\n\n";
	cout << "\t\t\t\t\t\t";
	cout << "Total Balances : " << total_balances << " .\n";

}



int main()
{


	show_main_menu();
}

