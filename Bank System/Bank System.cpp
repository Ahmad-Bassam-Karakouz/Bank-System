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

enum en_choice_client
{
	show_all_clients = 1,
	add_client = 2,
	delete_client = 3,
	update_client = 4,
	find_client = 5,
	transactions = 6,
	manage_users=7,
	log_out = 8
};

enum en_manage_users
{
	show_all_users=1,
	add_user=2,
	delete_user=3,
	update_user=4,
	find_user=5,
	main_menu=6
};


// ÊÌãíÚ ãÚáæãÇÊ ÇáÚãíá Öãä struct .
struct st_client_info
{
	string account_number;
	string pin_code;
	string client_name;
	string phone_number;
	double balance;
	bool for_delete_client = false;
};

// ÊÌãíÚ ãÚáæãÇÊ ÇáãÓÊÎÏã Öãä struct .
struct st_user_info
{
	string user_name;
	string password;
	int permisions;
	bool for_delete_user = false;
};

// ãä ÇÌá ãÚÑİÉ ÇáãÓÊÎÏã ÇáÍÇáí ááäÙÇã .
st_user_info current_user;

// ÊÚÑíİ ÇÓã Çáãáİ Úáì ãÓÊæì ÇáÈÑäÇãÌ .
string file_name_clients = "clients.txt";
string file_name_users = "users.txt";

// ÊÕÑíÍ Úä ÇáÏæÇá ãä ÇÌá ãÑæäÉ ÇáÚãá .
void show_main_menu();
void show_main_manage_users_screen();
void show_transactions_main_screen();
void clear_screen();
void login();
int  read_permissions();



// åĞå ÇáÏÇáÉ ÊÇÈÚÉ á show_all_clients_screen .
void print_client_data(const st_client_info& client_data)
{
	cout << "| " << left << setw(16) << client_data.account_number;
	cout << "| " << left << setw(12) << client_data.pin_code;
	cout << "| " << left << setw(28) << client_data.client_name;
	cout << "| " << left << setw(13) << client_data.phone_number;
	cout << "| " << left << setw(13) << to_string(client_data.balance);
}

// ØÈÇÚÉ ÈíÇäÇÊ ÇáÚãíá .
void print_client_card(const st_client_info& client)
{
	cout << "\n\n_______________________________________\n";
	cout << "\nAccount Number : " << client.account_number;
	cout << "\nPin Code : " << client.pin_code;
	cout << "\nClient Name : " << client.client_name;
	cout << "\nPhone Number : " << client.phone_number;
	cout << "\nBalance : " << client.balance;
	cout << "\n_______________________________________";
}

// ØÈÇÚÉ ÈíÇäÇÊ ÇáãÓÊÎÏã .
void print_user_card(const st_user_info& user)
{
	cout << "\n\n_______________________________________\n";
	cout << "\nUser Name : " << user.user_name;
	cout << "\nPassword  : " << user.password;
	cout << "\nPermisions : " << to_string(user.permisions);
	cout << "\n_______________________________________";
}

// åĞå ÇáÏÇáÉ ÊÇÈÚÉ á show_all_users_screen .
void print_user_data(const st_user_info& user_data)
{
	cout << "| " << left << setw(23) << user_data.user_name;
	cout << "| " << left << setw(23) << user_data.password;
	cout << "| " << left << setw(3) << user_data.permisions;
}

// ŞÑÇÁÉ ÇáÈíÇäÇÊ ÇáÚãáÇÁ ãä Çáãáİ æÊÍãíáåã Úáì vector .
vector<string> read_file_clients()
{
	vector<string>file;
	fstream f;
	f.open(file_name_clients, ios::in);

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

// ŞÑÇÁÉ ÇáÈíÇäÇÊ ÇáãÓÊÎÏãíä ãä Çáãáİ æÊÍãíáåã Úáì vector . 
vector<string> read_file_users()
{
	vector<string>file;
	fstream f;
	f.open(file_name_users, ios::in);

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
st_client_info convert_line_to_data_for_client(string line)
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

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÊÍæíá ÇáäÕ Çáì ÈíÇäÇÊ .
st_user_info convert_line_to_data_for_user(string line)
{
	vector<string> v = split(line);

	st_user_info user_info;
	user_info.user_name = v[0];
	user_info.password = v[1];
	user_info.permisions = stoi(v[2]);

	return user_info;
}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÊÍæíá ÇáÈíÇäÇÊ äÕ ãä ÇÌá ÇáÚãíá .
string convert_data_to_line_for_client(st_client_info client_info, string delim = "#//#")
{
	string line;
	line = client_info.account_number + delim;
	line += client_info.pin_code + delim;
	line += client_info.client_name + delim;
	line += client_info.phone_number + delim;
	line += to_string(client_info.balance) ;
	return line;
}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÊÍæíá ÇáÈíÇäÇÊ äÕ ãä ÇÌá ÇáãÓÊÎÏã .
string convert_data_to_line_for_user(st_user_info user_info, string delim = "#//#")
{
	string line;
	line = user_info.user_name + delim;
	line += user_info.password + delim;
	line += to_string(user_info.permisions);
	
	return line;
}

// ÇáÍÕæÇá Úáì ÌãíÚ ÈíÇäÇÊ ÇáÚãáÇÁ ÇáãæÌæÏÉ Úáì Çáãáİ .
vector<st_client_info> get_all_clients_data()
{
	vector<st_client_info>clients_data;

	vector<string> file_data = read_file_clients();

	for (const string& line : file_data)
	{
		clients_data.push_back(convert_line_to_data_for_client(line));
	}

	return clients_data;
}

// ÇáÍÕæÇá Úáì ÌãíÚ ÈíÇäÇÊ ÇáãÓÊÎÏãíä ÇáãæÌæÏÉ Úáì Çáãáİ .
vector<st_user_info> get_all_users_data()
{
	vector<st_user_info>users_info;

	vector<string> file_data = read_file_users();

	for (const string& line : file_data)
	{
		users_info.push_back(convert_line_to_data_for_user(line));
	}

	return users_info;
}

// ŞÑÇÁÉ ÑŞã ÍÓÇÈ ÇáãÓÊÎÏã .
string read_account_number()
{
	string account_number;
	cout << "\nEnter account number please : ";
	cin >> account_number;
	return account_number;
}

// ŞÑÇÁÉ ÇÓã ÇáãÓÊÎÏã .
string read_user_name(string message)
{
	string user_name;
	cout << message;
	cin >> user_name;
	return user_name;
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

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÇáÊÔííß Úáì ÇÓã ÇáãÓÊÎÏã ÇáÌÏíÏ ÇĞÇ ßÇä ãßÑÑ  ãä ÇÌá ÚÏã ÇáÊÖÇÑÈ .
bool check_user_name(const vector<st_user_info>& v_users,string user_name,st_user_info& current_user)
{
	
	for (const st_user_info& user : v_users)
	{
		if (user.user_name == user_name)
		{
			current_user = user;
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
	getline(cin >> ws, client_info.pin_code);

	cout << "\nEnter Name please: ";	
	getline(cin >> ws, client_info.client_name);

	cout << "\nEnter Phone Number please: ";
	getline(cin >> ws, client_info.phone_number);

	cout << "\nEnter Balance please: ";
	cin >>  client_info.balance;

	return client_info;
}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ŞÑÇÁÉ ãÚáæãÇÊ ÇáãÓÊÎÏã ÇáÌÏíÏ .
st_user_info read_new_user_data(string user_name)
{
	st_user_info user_info;

	user_info.user_name = user_name;

	cout << "\nEnter password : ";
	getline(cin >> ws, user_info.password);

	user_info.permisions = read_permissions();

	return user_info;

}

// ÇÖáİÉ ÈíÇäÇÊ ÇáÚãíá ÇáÌÏíÏ Çáì Çáãáİ .
void add_client_to_file(const st_client_info& client_info)
{
	fstream file;
	file.open(file_name_clients, ios::out | ios::app);

	if (file.is_open())
	{
		file << convert_data_to_line_for_client(client_info) << endl;
	}
	file.close();
}

// ÇÖáİÉ ÈíÇäÇÊ ÇáãÓÊÎÏã ÇáÌÏíÏ Çáì Çáãáİ .
void add_user_to_file(const st_user_info& user_info)
{
	fstream file;
	file.open(file_name_users, ios::out | ios::app);

	if (file.is_open())
	{
		file << convert_data_to_line_for_user(user_info) << endl;
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
char ask_user_or_client_continue(string message)
{
	char answer;
	cout << message;
	cin >> answer;
	return answer;
}

// ÊÛííÑ ÍÇáÉ ãÊÛííÑ ÇáÍĞİ ãä ÇÌá ÍĞİ ÇáÚãíá ÇáãØáæÈ .
void mark_of_delete_for_client(string account_number, vector<st_client_info>& clients_info)
{
	for (st_client_info& client_info : clients_info)
	{
		if (client_info.account_number == account_number)
		{
			client_info.for_delete_client = true;
			break;
		}
	}
}

// ÊÛííÑ ÍÇáÉ ãÊÛííÑ ÇáÍĞİ ãä ÇÌá ÍĞİ ÇáÚãíá ÇáãØáæÈ .
void mark_of_delete_for_user(string user_name, vector<st_user_info>& v_users)
{
	for (st_user_info& user : v_users)
	{
		if (user.user_name == user_name)
		{
			user.for_delete_user = true;
			break;
		}
	}
}

// ÍĞİ ÇáÚãíá ãä Çáãáİ .
void save_new_file_for_client(const vector<st_client_info>& clients_info)
{
	fstream file;
	file.open(file_name_clients, ios::out);

	if (file.is_open())
	{
		for (short i = 0; i < clients_info.size(); i++)
		{
			if (clients_info[i].for_delete_client == false)
			{
				file << convert_data_to_line_for_client(clients_info[i]) << endl;
			}

		}
	}

	file.close();
}

// ÍĞİ ÇáãÓÊÎÏã ãä Çáãáİ .
void save_new_file_for_user(const vector<st_user_info>& v_users)
{
	fstream file;
	file.open(file_name_users, ios::out);

	if (file.is_open())
	{
		for (short i = 0; i < v_users.size(); i++)
		{
			if (v_users[i].for_delete_user == false)
			{
				file << convert_data_to_line_for_user(v_users[i]) << endl;
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
void update_data_for_client(vector<st_client_info>& clients_info, const st_client_info& new_client)
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

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ÊÍÏíË ÈíÇäÇÊ ÇáãÓÊÎÏã .
void update_data_for_user(vector<st_user_info>& v_users, const st_user_info& new_user)
{

	for (st_user_info& user : v_users)
	{
		if (user.user_name == new_user.user_name)
		{
			user = new_user;
			break;
		}
	}


}

// ÊØÈíŞ ÇáÊÍÏíË Úáì Çáãáİ .
void update_file_for_client(const vector<st_client_info>& clients_info)
{
	fstream file;

	file.open(file_name_clients, ios::out);

	if (file.is_open())
	{
		for (const st_client_info& client_info : clients_info)
		{
			file << convert_data_to_line_for_client(client_info) << endl;
		}
	}

	file.close();
}

// ÊØÈíŞ ÇáÊÍÏíË Úáì Çáãáİ .
void update_file_for_user(const vector<st_user_info>& v_users)
{
	fstream file;

	file.open(file_name_users, ios::out);

	if (file.is_open())
	{
		for (const st_user_info& user_info : v_users)
		{
			file << convert_data_to_line_for_user(user_info) << endl;
		}
	}

	file.close();
}

// show_add_new_client_screen åĞå ÇáÏÇáÉ ãÓÊÎÏãÉ İí .
bool is_account_number_exists(string account_number)
{
	vector<string>v_clients;
	fstream file;
	file.open(file_name_clients, ios::in);

	if (file.is_open())
	{
		st_client_info client;
		string line;
		while (getline(file, line))
		{
			client = convert_line_to_data_for_client(line);
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

bool check_permissions(int permission_number, int user_permissions)
{
	if (user_permissions == -1)
		return true;

	return (user_permissions & permission_number) != 0;
}


// CRUD.


// ÇáÑÌæÚ Çáì ÇáŞÇÆãÉ ÇáÑÆíÓíÉ .
void go_to_main_menu()
{
	cout << "\n\nPress any key to go back to main menue...";
	cin.ignore();
	cin.get();	
	show_main_menu();
}

// ÔÇÔÉ ÇáÈÍË Úä Úãíá .
void show_find_client_screen()
{
	char continue_ = 'n';

	do
	{
		clear_screen();

		print_head_screen("Find Client");

		if (!check_permissions(32, current_user.permisions))
		{
			cout << "\n\nSorry you dont have can access to this screen .\n\n";
			return;
		}

		continue_ = 'n';
			

		vector<st_client_info> v_clients = get_all_clients_data();

		st_client_info client;


		string account_number = read_account_number();

		if (check_account_number(account_number,v_clients,client))
		{
					
			print_client_card(client);
			continue_ = ask_user_or_client_continue("\n\ndo you want to find  more clients [Y/N]? ");
		}
		else
		{
			cout << "Client with account number ( " << account_number << " ) is not found !! ";
		}

	} while (continue_ == 'y' || continue_ == 'Y');

}

// ÔÇÔÉ  ÊÍÏíË ÈíÇäÇÊ Úããíá .
void show_update_client_screen()
{
	char continue_ = 'n';

	do
	{		
		clear_screen();

		print_head_screen("Update Client");

		if (!check_permissions(16, current_user.permisions))
		{
			cout << "\n\nSorry you dont have can access to this screen .\n\n";
			return;
		}

		continue_ = 'n';
			

		vector<st_client_info> v_clients = get_all_clients_data();

		st_client_info client;

		string account_number = read_account_number();

		while (!check_account_number(account_number, v_clients, client))
		{
			cout << "Client with account number ( " << account_number << " ) is not found !! ";
			account_number = read_account_number();
		}

		print_client_card(client);

		if (sure_the_process("\nAre you sure from update this client info [Y/N] ? "))
		{
			client = read_new_client_data(account_number);

			update_data_for_client(v_clients, client);

			update_file_for_client(v_clients);			

			continue_ = ask_user_or_client_continue("\nClient updated successfully, do you want to update more more clients [Y/N]? ");
		}

	} while (continue_ == 'y' || continue_ == 'Y');

}

// ÔÇÔÉ ÍĞİ Úãíá   .
void show_delete_client_screen()
{
	char continue_ = 'n';

	do
	{
		clear_screen();

		print_head_screen("Delete Client");

		if (!check_permissions(8, current_user.permisions))
		{
			cout << "\n\nSorry you dont have can access to this screen .\n\n";
			return;
		}

		continue_ = 'n';

		
		vector<st_client_info>v_clients = get_all_clients_data();

		st_client_info client;

		string account_number = read_account_number();

		while (!check_account_number(account_number, v_clients, client))
		{
			cout << "Client with  account number  ( " << account_number << " ) is not found !! ";
			account_number = read_account_number();
		}

		print_client_card(client);
		

		if (sure_the_process("\nAre you sure from delete this client [Y/N] ? "))
		{

			mark_of_delete_for_client(account_number, v_clients);
			save_new_file_for_client(v_clients);
			continue_ = ask_user_or_client_continue("\nClient deleted successfully, do you want to delete more more clients [Y/N]? ");
		}


	} while (continue_ == 'y' || continue_ == 'Y');

}

// ÔÇÔÉ ÇÖÇİÉ Úãíá ÌÏíÏ .
void show_add_new_client_screen()
{
	char continue_ = 'n';

	do
	{
		clear_screen();

		print_head_screen("Add Client");

		if (!check_permissions(4, current_user.permisions))
		{
			cout << "\n\nSorry you dont have can access to this screen .\n\n";
			return;
		}

		continue_ = 'n';

		
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
			continue_ = ask_user_or_client_continue("\nClient added successfully, do you want to add more clients [Y/N]? ");
		}

	} while (continue_ == 'y' || continue_ == 'Y');
}

//  ÔÇÔÉ ØÈÇÚÉ ÈíÇäÇÊ ÌãíÚ ÇáÚãáÇÁ  .
void show_all_clients_screen()
{
	clear_screen();

	if (!check_permissions(2, current_user.permisions))
	{
		cout << "\nSorry you dont have can access to this screen .\n\n";
		return;
	}


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

// ÊäİíĞ ÇÎÊíÇÑ ÇáÚãíá .
void handle_choice_client(en_choice_client choice)
{
	switch (choice)
	{
	case show_all_clients:

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
		go_to_main_menu();
		break;
	case manage_users:
		show_main_manage_users_screen();
		go_to_main_menu();
		break;
	case  log_out:
		login();
		break;
	default:
		exit(0);
		break;
	}
}

// ŞÑÇÁÉ äæÚ ÇáÚãáíÉ ÇáÊí íÑíÏåÇ ÇáÚãíá .
en_choice_client read_choice_from_client(string message)
{
	short operation_type;
	cout << message;
	cin >> operation_type;
	return (en_choice_client)operation_type;
}

// ÊäÙíİ ÇáÔÇÔÉ .
void clear_screen()
{
	system("cls");
}

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
	cout << "[7] Manage Users.";
	cout << "\n";
	cout << "[8] Log out.";
	cout << "\n";
	cout << "=======================================================";
	handle_choice_client(read_choice_from_client("\nChoose want do you want to do[1 to 8] ?"));
}



// TRANSACTIONS .



// ÇáÑÌæÚ Çáì ŞÇÆãÉ ÇáÚãáíÇÊ .
void go_to_transaction_menu()
{
	cout << "\n\nPress any key to go back to transactions menue...";
	cin.ignore();
	cin.get();
	show_transactions_main_screen();
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



	for (st_client_info& client : v_clients)
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

// ÔÇÔÉ ÚÑÖ ÚãáíÉ ÇáÓÍÈ .
void show_withdraw_screen()
{


	print_head_screen("Withdraw Screen");

	vector<st_client_info> v_clients = get_all_clients_data();
	st_client_info client;

	string account_number = read_account_number();

	while (!check_account_number(account_number, v_clients, client))
	{
		cout << "\nClient with account number ( " << account_number << " ) is not found !! ";
		account_number = read_account_number();
	}

	print_client_card(client);


	double amount = read_amount("\nWhat is the amunt Withdraw (please enter a positive number) ? ");

	if (check_withdraw_process(client, amount))
	{
		if (sure_the_process("\nAre you sure from this process [Y/N] ? "))
		{

			double new_amount = update_balance(v_clients, account_number, amount * -1);
			update_file_for_client(v_clients);
			cout << "\n\nThe Withdraw process was successful...Your current balance is " << new_amount << " .\n";
		}
	}
	else
	{
		cout << "\nYou cannot perform the withdrawal process because your balance is : " << client.balance << " .\n";
	}

}

// ÔÇÔÉ ÚÑÖ ÚãáíÉ ÇáÇíÏÇÚ .
void show_deposit_screen()
{


	print_head_screen("Deposit Screen");

	vector<st_client_info> v_clients = get_all_clients_data();

	st_client_info client;

	string account_number = read_account_number();

	while (!check_account_number(account_number, v_clients, client))
	{
		cout << "Client with account number ( " << account_number << " ) is not found !! ";
		account_number = read_account_number();
	}

	print_client_card(client);


	double amount = read_amount("\nWhat is the amunt deposited ? ");
	if (sure_the_process("\nAre you sure from this process [Y/N] ? "))
	{


		double new_amount = update_balance(v_clients, account_number, amount);
		update_file_for_client(v_clients);
		cout << "\n\nThe deposit process was successful...Your current balance is " << new_amount << " .\n";
	}

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
		show_total_balances_screen();
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

// ŞÑÇÁÉ äæÚ ÇáÚãáíÉ ÇáÊí íÑíÏåÇ ÇáÚãíá ÇáÎÇÕÉ ÈÇá transactions .
en_transaction_type read_transaction_type(string message)
{
	short transaction_type;
	cout << message;
	cin >> transaction_type;
	return (en_transaction_type)transaction_type;
}

// ÇáÔÇÔÉ ÇáÑÆíÓíÉ ÇáÎÇÕÉ ÈÇáÚãáíÇÊ .
void show_transactions_main_screen()
{

	clear_screen();


	if (!check_permissions(64, current_user.permisions))
	{
		cout << "\n\nSorry you dont have can access to this screen .\n\n";
		return;
	}

	print_head_screen("Transactions Menue");
	cout << "\n[1] Deposit.";
	cout << "\n[2] Withdraw.";
	cout << "\n[3] Total Balances.";
	cout << "\n[4] Main Menue.";
	cout << "\n=======================================================";
	handle_transactions(read_transaction_type("\nChoose what do you want to do [1 to 4] ? "));
}



// LOGIN SCREEN



// ÏÇáÉ ãä ÇÌá ÇáÊÔííß Úáì ÇáãÓÊÎÏã ÇĞÇ ßÇä ãæÌæÏ Çã áÇ .
bool check_user_info(st_user_info& user)
{
	vector<st_user_info>users_info = get_all_users_data();

	for (const st_user_info& user_info : users_info)
	{
		if (user_info.user_name == user.user_name && user_info.password == user.password)
		{
			user = user_info;
			return true;
		}
	}

	return false;
}

// ŞÑÇÁÉ ÇÓã æßáãÉ ÓÑ ÇáãÓÊÎÏã .
st_user_info read_user_info()
{
	st_user_info user_info;

	cout << "\nPlease enter user name : ";
	getline(cin >> ws, user_info.user_name);

	cout << "\nPlease enter password : ";
	getline(cin >> ws, user_info.password);

	return user_info;
}

// ØÈÇÚÉ ÔÇÔÉ ÊÓÌíá ÇáÏÎæá .
void print_login_screen()
{
	cout << "\n================================\n";
	cout << "\tLogin Screen";
	cout << "\n================================\n";
}

// ÇáÏÇáÉ ÇáäåÇÆíÉ ÇáÊí ÊÔÛá ÇáÈÑäÇãÌ .
void login()
{
	clear_screen();
	print_login_screen();
	st_user_info user_info = read_user_info();

	while (!check_user_info(user_info))
	{
		clear_screen();
		print_login_screen();
		cout << "\nInvlaid user name / password !\n";
		user_info = read_user_info();
	}
	current_user = user_info;
	show_main_menu();
}



// MANAGE USERS .


// ÇáÑÌæÚ Çáì ÔÇÔÉ ÇÏÇÑÉ ÇáãÓÊÎÏãíä .
void go_to_main_manage_users_screen()
{
	cout << "\n\nPress any key to go back to manager users menue...";
	cin.ignore();
	cin.get();

	clear_screen();
	show_main_manage_users_screen();
}

// ÔÇÔÉ ÇáÈÍË Úä ãÓÊÎÏã .
void show_find_user_screen()
{
	char continue_ = 'n';

	do
	{
		continue_ = 'n';

		clear_screen();

		print_head_screen("Find User");

		vector<st_user_info> v_user = get_all_users_data();

		st_user_info user;


		string user_name = read_user_name("\nEnter user name : ");

		if (check_user_name(v_user, user_name, user))
		{

			print_user_card(user);
			continue_ = ask_user_or_client_continue("\n\ndo you want to find  more users [Y/N]? ");
		}
		else
		{
			cout << "User with  user name ( " << user_name << " ) is not found !! ";
		}

	} while (continue_ == 'y' || continue_ == 'Y');

}

// ÔÇÔÉ  ÊÍÏíË ÈíÇäÇÊ ÇáãÓÊÎÏã .
void show_update_user_screen()
{
	char continue_ = 'n';

	do
	{
		continue_ = 'n';

		clear_screen();

		print_head_screen("Update User");

		vector<st_user_info> v_users = get_all_users_data();

		st_user_info user;

		string user_name = read_user_name("\nEnter user name : ");

		while (!check_user_name(v_users, user_name, user))
		{
			cout << "User with  User name ( " << user_name << " ) is not found !! ";
			user_name = read_user_name("\nEnter user name : ");
		}

		print_user_card(user);

		if (sure_the_process("\nAre you sure from update this User info [Y/N] ? "))
		{
			user = read_new_user_data(user_name);

			update_data_for_user(v_users, user);

			update_file_for_user(v_users);

			continue_ = ask_user_or_client_continue("\nUser updated successfully, do you want to update more more Users [Y/N]? ");
		}

	} while (continue_ == 'y' || continue_ == 'Y');

}

// ÔÇÔÉ ÍĞİ ãÓÊÎÏã   .
void show_delete_user_screen()
{
	char continue_ = 'n';

	do
	{
		clear_screen();

		continue_ = 'n';

		print_head_screen("Delete User");

		vector<st_user_info>v_users = get_all_users_data();

		st_user_info user;

		string user_name = read_user_name("\nEnter user name : ");

		while (!check_user_name(v_users, user_name, user))
		{
			cout << "User with  User name  ( " << user_name << " ) is not found !! ";
			user_name = read_user_name("\nEnter user name : ");
		}

		print_user_card(user);


		if (sure_the_process("\nAre you sure from delete this user [Y/N] ? "))
		{

			mark_of_delete_for_user(user_name, v_users);
			save_new_file_for_user(v_users);
			continue_ = ask_user_or_client_continue("\nUser deleted successfully, do you want to delete more more Users [Y/N]? ");
		}


	} while (continue_ == 'y' || continue_ == 'Y');

}

// ÏÇáÉ ÎÇÕÉ ãä ÇÌá ŞÑÇÁÉ ÇáÕáÇÍíÇÊ .
int read_permissions()
{
	char answer;

	cout << "\nDo you want to gave full access  [Y/N] ? ";
	cin >> answer;
	if (tolower(answer) == 'y')
	{
		return -1;
	}

	int permissions = 0;
	cout << "\nDo you want to gave  access to :\n\n";


	cout << "\nShow clients list [Y/N] ? ";
	cin >> answer;
	if (tolower(answer) == 'y')
	{
		permissions +=2;
	}

	cout << "\nAdd new client [Y/N] ? ";
	cin >> answer;
	if (tolower(answer) == 'y')
	{
		permissions += 4;
	}

	cout << "\nDelete client [Y/N] ? ";
	cin >> answer;
	if (tolower(answer) == 'y')
	{
		permissions += 8;
	}

	cout << "\nUpdate client [Y/N] ? ";
	cin >> answer;
	if (tolower(answer) == 'y')
	{
		permissions += 16;
	}

	cout << "\nFind client [Y/N] ? ";
	cin >> answer;
	if (tolower(answer) == 'y')
	{
		permissions += 32;
	}

	cout << "\nTreansactions [Y/N] ? ";
	cin >> answer;
	if (tolower(answer) == 'y')
	{
		permissions += 64;
	}

	cout << "\nManage Users [Y/N] ? ";
	cin >> answer;
	if (tolower(answer) == 'y')
	{
		permissions += 128;
	}

	return permissions;

}

// ÔÇÔÉ ÇÖÇİÉ ãÓÊÎÏã ÌÏíÏ .
void show_add_new_user_screen()
{
	char continue_ = 'n';

	do
	{

		clear_screen();

		continue_ = 'n';

		print_head_screen("Add User");

		vector<st_user_info> v_users = get_all_users_data();
		st_user_info new_user;
		string user_name = read_user_name("\nEnter user name : ");

		while (check_user_name(v_users,user_name, new_user))
		{
			cout << "\nError...the  user name (" << user_name << ") exists, enter another user name: ";
			cin >> user_name;

		}

		new_user = read_new_user_data(user_name);


		if (sure_the_process("\nAre you sure from add new user [Y/N] ? "))
		{
			add_user_to_file(new_user);

			continue_ = ask_user_or_client_continue("\nuser added successfully, do you want to add more user [Y/N]? ");
		}

	} while (tolower(continue_) == 'y');
}

//  ÔÇÔÉ ØÈÇÚÉ ÈíÇäÇÊ ÌãíÚ ÇáãÓÊÎÏãíä  .
void show_all_users_screen()
{
	clear_screen();

	vector<st_user_info> v_user = get_all_users_data();

	cout << "\t\t";
	cout << " Users List (" << v_user.size() << ") " << "Users(s).";
	cout << "\n";
	cout << "______________________________________________________________________";
	cout << "\n\n";	
	cout << left << setw(25) << "| User Name";
	cout << left << setw(25) << "| Password";
	cout << left << setw(5)  << "| Permisions";
	cout << "\n";
	cout << "______________________________________________________________________";
	cout << "\n\n";



	for (const st_user_info& user : v_user)
	{
		print_user_data(user);
		cout << endl;
	}

	cout << "______________________________________________________________________";

}

// ÊäİíĞ ÇÎÊíÇÑ ÇáãÓÊÎÏã .
void handle_choice_user(en_manage_users choice)
{
	switch (choice)
	{
	case show_all_users:
		show_all_users_screen();
		go_to_main_manage_users_screen();
		break;
	case add_user:
		show_add_new_user_screen();
		go_to_main_manage_users_screen();
		break;
	case delete_user:
		show_delete_user_screen();
		go_to_main_manage_users_screen();
		break;
	case update_user:
		show_update_user_screen();
		go_to_main_manage_users_screen();
		break;
	case find_user:
		show_find_user_screen();
		go_to_main_manage_users_screen();
		break;
	case main_menu:
		show_main_menu();
		break;
	default:
		exit(0);
		break;
	}
}

// ŞÑÇÁÉ äæÚ ÇáÚãáíÉ ÇáÊí íÑíÏåÇ ÇáãÓÊÎÏã .
en_manage_users read_choice_from_user(string message)
{
	short choice = 0;
	cout << message;
	cin >> choice;
	return (en_manage_users)choice;
}

// ÔÇÔÉ ÚÑÖ ŞÇÆãÉ ÇÏÇÑÉ ÇáãÓÊÎÏãíä .
void show_main_manage_users_screen()
{
	clear_screen();
	cout << "=======================================================";
	cout << "\n";
	cout << "\t\t";
	cout << "Main Manage Users Screen";
	cout << "\n";
	cout << "=======================================================";
	cout << "\n";
	cout << "[1] Show All Users.";
	cout << "\n";
	cout << "[2] Add New User.";
	cout << "\n";
	cout << "[3] Delet User.";
	cout << "\n";
	cout << "[4] Update User.";
	cout << "\n";
	cout << "[5] Find User.";
	cout << "\n";
	cout << "[6] Main Minu.";
	cout << "\n";
	cout << "=======================================================";
	handle_choice_user(read_choice_from_user("\nChoose want do you want to do[1 to 6] ?"));
}



int main()
{

	login();
	
}
