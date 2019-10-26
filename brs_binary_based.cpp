// Banking Record System.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<fstream>
#include<cstdlib> //rename remove
using std::cout;
using std::cin;
using std::endl;
using std::ostringstream;
using std::istringstream;
using std::ifstream;
using std::ofstream;
using std::ios;

//非POD不能二进制写入文件
struct Account{
	char number[20];
	char first_name[20], last_name[20];
	char balance[20];
};
class BankingRecordSystem {
public:
	BankingRecordSystem() {}
	~BankingRecordSystem() {}

	void read_data() {
		cout << "Enter Accout Number: \n";
		cin >> t.number;
		cout << "Enter First Name: \n";
		cin >> t.first_name;
		cout << "Enter Last Name: \n";
		cin >> t.last_name;
		cout << "Enter Balance: \n";
		cin >> t.balance;
	}
	void show_data() {
		cout << "Accout Number:";
		cout << t.number << "\n";
		cout << "First Name: ";
		cout << t.first_name << "\n";
		cout << "Last Name: ";
		cout << t.last_name << "\n";
		cout << "Balance: ";
		cout << t.balance << "\n";
		cout << "-------------------------------" << endl;
	}
	void write_rec() {
		ofstream fout(filepath,ios::app|ios::binary);
		read_data();
		fout.write(reinterpret_cast<char*>(&t), sizeof(t));
		show_data();
	}
	void read_rec() {
		ifstream fin(filepath, ios::binary);
		if (!fin)
		{
			cout << FileOpenErrorMessage;

			return;
		}
		cout << "\n****Data from file****" << endl;

		while (fin.read((char*)(&t), sizeof(t))) {
			show_data();
		}
		fin.close();
	}
	void search_rec() {	
		ifstream fin(filepath, ios::binary);
		if (!fin) {
			cout << FileOpenErrorMessage;
			return;
		}
		fin.seekg(0, ios::end);
		int count = fin.tellg() / sizeof(t);
		cout << "\n There are " << count << " record in the file";
		cout << "\n Enter Record Number to Search: ";
		int n;
		cin >> n;
		fin.seekg((n - 1) * sizeof(t));
		fin.read(reinterpret_cast<char*>(&t), sizeof(t));
		show_data();
		fin.close();
		}
	void edit_rec() {
		std::fstream fs;
		fs.open(filepath, ios::in|ios::binary);
		if(!fs)
		{
			cout << FileOpenErrorMessage;
			return;
		}
		fs.seekg(0, ios::end);
		int count = fs.tellg() / sizeof(t);
		cout << "\n There are " << count << " record in the file";
		cout << "\n Enter Record Number to Edit: ";
		int n;
		cin >> n;
		fs.seekg((n - 1) * sizeof(t));
		fs.read(reinterpret_cast<char*>(&t), sizeof(t));
		cout << "Record " << n << " has following data" << endl;
		show_data();
		fs.close();

		fs.open(filepath, ios::in|ios::out | ios::binary);
		fs.seekp((n - 1) * sizeof(t));
		cout << "\nEnter data to Modify " << endl;
		read_data();
		fs.write(reinterpret_cast<char*>(&t), sizeof(t));
		fs.close();

	}

	//read data one by one
	//and write to a temp file 
	//then rename that file
	void erase_data() {
		ifstream fin;
		ofstream fout;
		fin.open(filepath,ios::binary);
		const char* tempfilename = "tempfile.txt";
		fout.open(tempfilename, ios::binary);
		if (!fin&&!fout)
		{
			cout << FileOpenErrorMessage;
			return;
		}
		fin.seekg(0, ios::end);
		int count = fin.tellg() / sizeof(t);
		cout << "\n There are " << count << " record in the file";
		cout << "\n Enter Record Number to Delete: ";
		int n;
		cin >> n;

		fin.seekg(0, ios::beg);
		for (int i = 0; i < count; ++i) {
			fin.read(reinterpret_cast<char*>(&t), sizeof(t));
			//pass the deleted data
			if (i == n - 1)
				continue;
			fout.write(reinterpret_cast<char*>(&t), sizeof(t));
		}
		fin.close();
		fout.close();
		remove(filepath);
		rename(tempfilename,filepath);

	}
private:
	Account t;
	const char* filepath = "data.txt";
	const char* ErrorRecordMessage = "Error! Record Not Found!!";
	const char* FileOpenErrorMessage = "File Open Error！";
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
		case 1:brs.write_rec(); break;
		case 2:brs.read_rec(); break;
		case 3:brs.search_rec(); break;
		case 4:brs.edit_rec(); break;
		case 5:brs.erase_data(); break;
		case 6:return 0;
		default:
			std::cerr << "error input,try agian!\n";
		}


}
