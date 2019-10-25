// Banking Record System.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
using std::cout;
using std::cin;
using std::string;
using std::ostringstream;
using std::istringstream;
using std::vector;
using std::ios;
struct Account{
	std::string number;
	std::string first_name, last_name;
	string balance;
};
class BankingRecordSystem {
public:
	BankingRecordSystem() :filepath("data.txt") {}
	~BankingRecordSystem() {}

	//Time:2019/10/25
	//add banking record into the file
	//It asks for information such as account number, first name, 
	//last name and balance to be entered.
	void read_data() {
		try {
			//write file from memory to file 
			std::ofstream fout(filepath, ios::app|ios::binary);
			ostringstream formatline;
			if (!fout)
				throw std::runtime_error(FileOpenErrorMessage);
			else
			{
				Account t;
				cout << "Enter Accout Number: \n";
				cin >> t.number;
				cout << "Enter First Name: \n";
				cin >> t.first_name;
				cout << "Enter Last Name: \n";
				cin >> t.last_name;
				cout << "Enter Balance: \n";
				cin >> t.balance;
				//格式化数据,写入string流
				formatline << t.number << " " << t.first_name << " " << t.last_name<<" " << t.balance<<std::endl;
				//把string流中的数据写入文件
				fout << formatline.str();
			}
			fout.close();
		}
		
		//TODO  how to deal with error
		catch (std::runtime_error&e ) {
			cout << e.what();
		}
		
	}
	//show the record corresponding 
	//to a particular account number,
	//first name and last name.
	//Then display the current balance
	//of the account holder
	void show_data() {
		try {
			std::ifstream fin(filepath, ios::binary);
			
			if (fin.fail())
				throw std::runtime_error(FileOpenErrorMessage);
			else {
				Account t;
				string line;
				//循环条件是还能get到一行,不能使用!fin.eof()
				
				while (getline(fin, line))
				{
					istringstream iss(line);//用string流处理每一条的数据
					iss >> t.number >> t.first_name >> t.last_name >> t.balance;
					totalrecords.push_back(t);
				}
				cout << "There are " << totalrecords.size() << " record in the file\n";
				cout << "***Account List Data***\n\n";

				for (auto record : totalrecords) {
					cout << "Accout Number:";
					cout << record.number << "\n";
					cout << "First Name: ";
					cout << record.first_name << "\n";
					cout << "Last Name: ";
					cout << record.last_name << "\n";
					cout << "Balance: ";
					cout << record.balance << "\n\n";
				}
			}
		}
		catch (std::runtime_error& e) {
			cout << e.what();
		}
		
	}

	//TODO search result is only one.Need all.
	//eg:we have more than 1 number equal to 
	//101 but result is the first one

	//show the total records in the file
	//then user can search by record number
	//display Error Message if record not found
	void search_data() {
		show_data();
		cout << "Enter your searching record number: \n";
		string searchnumber;
		cin >> searchnumber;
		try {

			vector<Account>::iterator pos = std::find_if(totalrecords.begin(), totalrecords.end(), [&](const Account& x)
				{return x.number == searchnumber; });
			if (pos == totalrecords.end())
				throw std::runtime_error(ErrorRecordMessage);
			else
				cout << "Accout Number:";
				cout << pos->number << "\n";
				cout << "First Name: ";
				cout << pos->first_name << "\n";
				cout << "Last Name: ";
				cout << pos->last_name << "\n";
				cout << "Balance: ";
				cout << pos->balance << "\n\n";

		}
		catch (std::runtime_error& e)
		{
			cout << e.what();
		}
	}
	//t shows the total records in the file, and the user can edit 
	//the information by providing record number. 
	//if not found 
	//displays "Error in opening!Record Not Found!!"

	void edit_data() {
		show_data();
		cout << "Enter your searching record number: \n";
		string searchnumber;
		cin >> searchnumber;
		try {

			vector<Account>::iterator pos = std::find_if(totalrecords.begin(), totalrecords.end(), [&](const Account& x)
				{return x.number == searchnumber; });
			if (pos == totalrecords.end())
				throw std::runtime_error(ErrorRecordMessage);
			else
			{
				//else使用变量需要定义在块中
				auto index = pos - totalrecords.begin();

				Account t;
				cout << "Enter data to modify\n\n";
				cout << "Enter Accout Number: \n";
				cin >> t.number;
				cout << "Enter First Name: \n";
				cin >> t.first_name;
				cout << "Enter Last Name: \n";
				cin >> t.last_name;
				cout << "Enter Balance: \n";
				cin >> t.balance;
				
				//把修改的对象替换到vector中
				totalrecords.at(index) = t;
				std::ofstream of(filepath, ios::out | ios::binary);
				if (of) {
					for (auto i : totalrecords)
					{
						ostringstream oss;
						oss << i.number << " " << i.first_name << " " << i.last_name << " " << i.balance << std::endl;
						of << oss.str();
					}
					of.close();
				}
				else
					throw std::runtime_error(FileOpenErrorMessage);
				

			}
				
		}
		catch (std::runtime_error & e)
		{
			cout << e.what();
		}
	}
	//it shows all the records in the file, 
	//and the user can enter the 
	//record number to delete.
	void erase_data() {
		show_data();

		cout << "Enter your searching record number: \n";
		string searchnumber;
		cin >> searchnumber;
		try {

			vector<Account>::iterator pos = std::find_if(totalrecords.begin(), totalrecords.end(), [&](const Account& x)
				{return x.number == searchnumber; });
			if (pos == totalrecords.end())
				throw std::runtime_error(ErrorRecordMessage);
			else
			{
				totalrecords.erase(pos);
				std::ofstream of(filepath, ios::out | ios::binary);
				if (of) {
					for (auto i : totalrecords)
					{
						ostringstream oss;
						oss << i.number << " " << i.first_name << " " << i.last_name << " " << i.balance << std::endl;
						of << oss.str();
					}
					of.close();
				}
				else
					throw std::runtime_error(FileOpenErrorMessage);


			}

		}
		catch (std::runtime_error & e)
		{
			cout << e.what();
		}
	}

private:
	string filepath;
	vector<Account> totalrecords;
	const string ErrorRecordMessage = "Error! Record Not Found!!";
	const string FileOpenErrorMessage = "File Open Error！";
};

int main()
{
	cout << "***Account Information System***" << "\n"
		"Select one option below\n"
		"\t1-->Add Record to file\n"
		"\t2-->Show Record from file\n"
		"\t3-->Search Record from file\n"
		"\t4-->Update Record\n"
		"\t5-->Delete Record\n"
		"\t6-->Quit\n";

	BankingRecordSystem brs;
		unsigned op = 0;
		cin >> op;
		switch (op)
		{
		case 1:brs.read_data(); break;
		case 2:brs.show_data(); break;
		case 3:brs.search_data(); break;
		case 4:brs.edit_data(); break;
		case 5:brs.erase_data(); break;
		case 6:return 0;
		default:
			std::cerr << "error input,try agian!\n";
		}


}
