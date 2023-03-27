//	CAR PARKING MANAGEMENT SYSTEM	 //
#include <iostream>
#include <iomanip>
#include <windows.h>									// to put the program to sleep/wait/delay 
#include <ctime>										// to show current time and date
#include <string>
#include "../Project1/Header.h"
using namespace std;
int today_parked = 0;                                   // to show the num of parked cars in a day 

void write(string file_name, Vehicle obj) {
	ofstream fout(file_name, ios::binary | ios::app);
	fout.write((char*)&obj, sizeof(obj));
	fout.close();
}
void read(string file_name) {
	Vehicle obj;
	ifstream fin(file_name, ios::binary | ios::app);
	//fin.seekg(0, ios::end);
	//int endposition = fin.tellg();
	//int n = endposition / sizeof(obj);

	while (fin.read((char*)&obj, sizeof(obj)))
		obj.display();
	fin.close();
	//cout << "There are a total of " << n << " Vehical info in the file.\n";
}

void read_day(string file_name) {
	Vehicle obj;
	ifstream fin(file_name, ios::binary | ios::app);
	int position = (today_parked) * sizeof(obj);
	fin.seekg(-position, ios::end);

	while (fin.read((char*)&obj, sizeof(obj)))
	{

		obj.display();
	}

	fin.close();
}

void update(string file_name, string id, string updated_cnic) {
	Vehicle obj;
	fstream f(file_name, ios::out | ios::in | ios::binary);
	while (f.read((char*)&obj, sizeof(obj))) {
		if (obj.get_vehicle_id() == id) {
			obj.set_vehicle_owner(updated_cnic.c_str());
			int a = f.tellg();
			int s = sizeof(Vehicle);
			f.seekp(a - s, ios::beg);
			f.write((char*)&obj, sizeof(obj));
			break;
		}
	}
	f.close();
}



int main() {

	int days, op, money_ret;
	string ch, v_type, cnic_up, num_plate;								//ch ~ choice that user will select
	Vehicle v;
	Parking p;
	e_payment e;
	membership m1;
	vehicle_type v1;
	string cars_id;


user:
	op = 0;
	cout << endl << setw(62) << "---------Welcome to Metropolitan Car Parking---------" << setw(55) << current_time();
	cout << setw(55) << "Please select from the options below: " << endl;
	cout << setw(59) << "(1) Admin         (2) User         (3) Talk to us" << endl;
	cout << endl;
	cin >> op;
	int case1 = 0;

	Sleep(1000);
	system("CLS");

	if (op == 1) {												//for admin
		cout << "Enter your login details: " << endl;
		login();

		Sleep(1000);
		system("CLS");

	choose:
		op = 0;
		admin a;
		cout << "Which of the following operation do you want to perform? "
			"\n1. View record "
			"\n2. View available parking"
			"\n3. End system\n\n";
		cin >> op;

		switch (op) {
		case 1:
		{

			system("CLS");
			cout << "\n\nWhat do you want to see?\n"
				"1. Read complete file.\n"
				"2. Read the data of cars parked today.\n";
			cin >> case1;
			switch (case1)
			{
			case 1:
				read("V_data.dat");
				Sleep(15000);
				system("CLS");
				goto user;
				break;

			case 2:
				read_day("V_data.dat");
				Sleep(15000);
				system("CLS");
				goto user;
				break;

			default:
				cout << "Wrong number entered!" << endl;
				goto choose;
			}
			break;
		}
		case 2:
			cout << "\n** CHECKING WHICH SLOTS ARE NOW RESERVED **\n";
			p.Check_all_reserved();
			Sleep(4000);
			system("CLS");
			break;
		case 3:
			system("CLS");
			break;
		default:
			cout << "Wrong number entered!" << endl;
		}
		goto user;
	}

	else if (op == 2) {								//for user

		cout << "\nEnter what you are here for "
			"\n1. Park car."
			"\n2. Leave car."
			"\n3. Search car.\n\n\n";
		int val = 0;
		cin >> val;

		Sleep(2000);
		system("CLS");

		cout << endl;

		if (val == 1)
		{
			v.get_owner_info();
			v1.set_vehicle_type();
			v_type = v1.get_vehicle_type();
			v.set_time_clock(current_time());


			write("V_data.dat", v);
			today_parked += 1;

			Sleep(3000);
			system("CLS");
			cout << endl;

			p.Check_all_available();
			p.Park_vehicle(v);


			Sleep(7000);
			system("CLS");

			cout << "\n** CHECKING WHICH SLOTS ARE NOW RESERVED **\n";
			p.Check_all_reserved();


			cout << "\nDo you want to search your car? (Y/N): ";
			char choose;
			cin >> choose;
			if (choose == 'y' || choose == 'Y')
			{
				cout << "\nEnter the number plate of the car you want to search: (E-XXX) ";
				cin >> num_plate;
				p.find_vehicle(num_plate);
			}

			Sleep(3000);
			system("CLS");
			goto leave;
		}

		else if (val == 2)
		{
		leave:
			cout << "\nDo you want to leave the parking? ";
			cin >> ch;
			cout << p.getcars_parked() + p.getcars_left() << endl;      //prints the map of parking place

			if (ch == "y" || ch == "Y" || ch == "YES" || ch == "yes" || ch == "Yes")
			{
				cout << "\nEnter your car's id: (E-XXX) ";
				cin >> cars_id;

				Sleep(2000);
				system("CLS");

				if (v.get_vehicle_id() == cars_id)
				{
					if (ch == "y" || ch == "Y" || ch == "YES" || ch == "yes" || ch == "Yes") {


						payment p1;
						p1.setting_money(v_type);
						money_ret = p1.display_cost();

						cout << "\nDo you want the money to be deducted from your e-wallet? ";
						cin >> ch;								//e-wallet functionality

						if (ch == "y" || ch == "Y" || ch == "YES" || ch == "yes" || ch == "Yes")
							e.e_pay(money_ret);
						else
							e.c_pay(money_ret);



						p.Leave_parking(v);

						cout << p.getcars_parked() + p.getcars_left() << endl;       //prints the map of parking place

						Sleep(4000);
						system("CLS");

						cout << "\n** CHECKING WHICH SLOTS ARE EMPTY **\n";
						p.Check_all_available();
						cout << p.getcars_parked() + p.getcars_left() << endl;       //prints the map of parking place

						cout << endl;

						goto user;
					}

				}
				else {
					if (ch == "y" || ch == "Y" || ch == "YES" || ch == "yes" || ch == "Yes") {


						payment p1;
						p1.setting_money(v_type);
						money_ret = p1.display_cost();

						cout << "\nDo you want the money to be deducted from your e-wallet? ";
						cin >> ch;								//e-wallet functionality

						if (ch == "y" || ch == "Y" || ch == "YES" || ch == "yes" || ch == "Yes")
							e.e_pay(money_ret);
						else
							e.c_pay(money_ret);



						p.Leave_parking(v);

						cout << p.getcars_parked() + p.getcars_left() << endl;       //prints the map of parking place

						Sleep(4000);
						system("CLS");

						cout << "\n** CHECKING WHICH SLOTS ARE EMPTY **\n";
						p.Check_all_available();
						cout << p.getcars_parked() + p.getcars_left() << endl;       //prints the map of parking place

						cout << endl;

						goto user;
					}

					goto user;
				}
				goto user;
				Sleep(1000);
				system("CLS");
				goto user;

			}
			else {
				Sleep(1000);
				system("CLS");
				goto user;
			}

			Sleep(5000);
			goto user;

		}
		else if (val == 3)
		{
			cout << "\nDo you want to search your car? (Y/N): ";
			char choose;
			cin >> choose;
			if (choose == 'y' || choose == 'Y')
			{
				cout << "\nEnter the number plate of the car you want to search: (E-XXX) ";
				cin >> num_plate;
				p.find_vehicle(num_plate);
			}

			Sleep(3000);
			system("CLS");
		}
		else
			goto user;

	}
	else if (op == 3) {
		chatbot cb;
		cb.talk();

		Sleep(5000);
		system("CLS");

		goto user;
	}
	else
		goto user;

}