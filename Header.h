#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

char* current_time() {
#pragma warning(suppress : 4996)
	time_t now = time(0);				// current date/time based on current system
#pragma warning(suppress : 4996)
	char* dt = ctime(&now);				// convert now to string form

	return dt;
}

void login() {
	int count = 0;
	string name, password, name_enter, password_enter;



	ifstream input("data.txt");
	while (count == 0) {
		cout << "\n1. Login ID: ";
		cin >> name;
		cout << "2. Password: ";
		cin >> password;
		if (name == "admin" && password == "123")
			count = 1;
	}
	input.close();
	if (count == 1) {
		cout << "\nLogin successful!\n";
		return;
	}
	else {
		cout << "\nLogin Error! Please try again\n";
		login();
	}
}
//void admin() {
//	string reg_name, reg_password, r, u;
//
//	cout << "Enter username: ";
//	cin >> reg_name;
//	cout << "Enter password: ";
//	cin >> reg_password;
//	
//	ofstream reg("data.txt", ios::app);
//	reg << reg_name << " " << reg_password;
//
//	cout << "Registration successful!";
//	return;
//}
int num_days() {
	int d;

	srand(time(NULL));
	d = 1 + rand() % 299;

	cout << "\nOur data shows that you've been parking with us for " << d << " days :D" << endl;
	return d;
}





class Vehicle {
private:
	char vehicle_id[35]; char time_clock[35];
	char vehicle_brand[35]; char vehicle_cnic[35];
	//char time[24];

public:


	void get_owner_info() {
		string temp;

		cout << "Enter vehicle id: (E-XXX) ";
		cin >> temp;
		strcpy(vehicle_id, temp.c_str());

		cout << "Enter vehicle brand: ";
		cin >> temp;
		strcpy(vehicle_brand, temp.c_str());

		cout << "Enter vehicle owner cnic: ";
		cin >> temp;
		strcpy(vehicle_cnic, temp.c_str());


	}
	void set_vehicle_id(string v_id) {
		strcpy(vehicle_id, v_id.c_str());
	}
	char* get_vehicle_id() { return vehicle_id; }

	void set_vehicle_brand(string v_brand) {
		strcpy(vehicle_brand, v_brand.c_str());
	}
	char* get_vehicle_brand() { return vehicle_brand; }

	void set_vehicle_owner(string v_cnic) {
		strcpy(vehicle_cnic, v_cnic.c_str());
	}
	char* get_vehicle_owner() { return vehicle_cnic; }

	void set_time_clock(char time1[24]) {
		for (int i = 0; i < 24; i++)
		{
			time_clock[i] = time1[i];
		}
	}
	char* get_time_clock() { return time_clock; }

	bool operator ==(char* a) {
		if (vehicle_id == a)
			return true;
		else
			return false;
	}
	void const display() {
		cout << "\n\nOwner cnic: " << vehicle_cnic;
		cout << "\nVehicle brand: " << vehicle_brand;
		cout << "\nVehicle number: " << vehicle_id;
		cout << "\nEntering Time: " << time_clock;
	}
};

class Parking_place {
private:
	char parking_place_id[35];
	int status = 0;				//0 -> empty
	Vehicle v;

public:
	void set_parking_place_id(string id) {
		strcpy(parking_place_id, id.c_str());
	}
	string get_parking_place_id() { return parking_place_id; }

	void set_status(int s) {
		status = s;
	}
	int get_status() { return status; }

	int update_status() {
		if (status == 0)
			return 0;
		else if (status == 1)
			return 1;

		return status;
	}
	void operator=(Vehicle v1) {
		strcpy(parking_place_id, v1.get_vehicle_id());
	}
	bool operator==(Vehicle v1) {
		if (parking_place_id == v1.get_vehicle_id())
			return (parking_place_id == v1.get_vehicle_id());
		else
			return false;
	}
};

class Parking {
private:
	Parking_place p[14];
public:
	int cars_parked = 0;
	int cars_left = 0;

	bool Park_vehicle(Vehicle v) {
		int m;
		for (int i = 0; i < 14; i++) {
			if (p[i].update_status() == 0) {
				p[i] = v;
				p[i].set_status(1);
				cars_parked += 1;
				m = p[i].update_status();

				return true;

			}
		}
		return true;
	}
	void Leave_parking(Vehicle v) {
		int d = 0, m;
		for (int i = 0; i < 14; i++) {
			if (p[i].get_parking_place_id() == v.get_vehicle_id()) {
				cout << "\nThe parked car at slot #" << i + 1 << " has left the parking.";
				p[i].set_status(0);
				p[i].set_parking_place_id("EMPTY");
				cars_parked -= 1;
				cars_left += 1;
				d = i + 1;
			}
		}
		m = p[d].update_status();
		if (m == 0)
			cout << " Parking is available at slot #" << d << endl;
		else if (m == 1)
			cout << "Parking isn't avaible at slot #" << d << " as its been occupied :(" << endl;
	}
	void Leave_parking(string v) {
		int d, m;
		for (int i = 0; i < 14; i++) {
			if (p[i].get_parking_place_id() == v) {
				cout << "\nThe parked car at slot #" << i + 1 << " has left the parking.";
				p[i].set_status(0);
				p[i].set_parking_place_id("EMPTY");
				cars_parked -= 1;
				cars_left += 1;
				d = i + 1;
			}
		}
		m = p[d].update_status();
		if (m == 0)
			cout << " Parking is available at slot #" << d << endl;
		else if (m == 1)
			cout << "\nParking isn't available at slot #" << d << " as its been occupied :(" << endl;
	}
	void Check_all_available() {
		for (int i = 0; i < 14; i++) {
			if (p[i].update_status() == 0)
				cout << "Parking is available at slot #" << i + 1 << endl;

		}
	}
	void Check_all_reserved() {
		for (int i = 0; i < 14; i++) {
			if (p[i].update_status() == 1)
				cout << "Parking isn't available at slot #" << i + 1 << " as its been occupied :(" << endl;

		}
	}
	int find_vehicle(string num) {
		int a = 0;
		for (int i = 0; i < 14; i++) {
			if (p[i].get_parking_place_id() == num) {
				cout << "\nYOUR CAR IS PRESENT AT SLOT# " << i + 1 << " :')";
				return i + 1;
			}
			else
				a = 1;
		}
		if (a == 1) {
			cout << "\nYou've entered the wrong car number :/";
			cout << "\nPlease enter your car number again: ";
			cin >> num;
			find_vehicle(num);
		}
	}
	bool check_vehical(string num)
	{
		for (int i = 0; i < 14; i++) {
			if (p[i].get_parking_place_id() == num) {

				return true;
			}
		}
		if (1) {
			cout << "\nYou've entered the wrong car number :/";
		}
		return false;
	}
	int getcars_parked()
	{
		return cars_parked;
	}
	int getcars_left()
	{
		return cars_left;
	}
	Parking_place* getparking_place()
	{
		return p;
	}
};



class membership {
protected:
	int number_of_days, ep;
public:
	membership() {
		number_of_days = 0;

		srand(time(NULL));
		ep = 500 + rand() % 1000;
	}
	virtual ~membership() {}

	int get_num_days() { return number_of_days; }
	void set_num_days(int days) { number_of_days = days; }
};





class vehicle_type {
protected:
	char type_v[35];
public:
	vehicle_type() {}
	~vehicle_type() {}

	void set_vehicle_type() {
		cout << "Enter type of your vehicle (bike, car, jeep): ";
		cin >> type_v;
	}
	void set_vt(string v) { strcpy(type_v, v.c_str()); }
	char* get_vehicle_type() { return type_v; }
};

class payment {
protected:
	int money = 0, total_money = 0;
	float discount, count = 0;

public:
	payment() {
		count = 1;			//to help distinguish if we have to apply discount or not
	}
	payment(float disc) {
		count = 1;
	}
	virtual ~payment() {}

	void const setting_money(string vehicle_type) {
		if (vehicle_type == "Bike" || vehicle_type == "bike" || vehicle_type == "BIKE")
			money = 500;
		else if (vehicle_type == "Car" || vehicle_type == "car" || vehicle_type == "CAR")
			money = 1000;
		else if (vehicle_type == "Jeep" || vehicle_type == "jeep" || vehicle_type == "JEEP")
			money = 2500;
		else
			money = 5000;
	}
	int display_cost() {
		if (count == 1) {
			std::cout << "Total cost of parking is: " << money << std::endl;
			return money;
		}

	}
};

class e_payment : public membership {
private:
	int final_cost;
public:
	e_payment() {}
	~e_payment() {}

	void c_pay(int m) {
		cout << "\nEnter amount due: ";
		cin >> final_cost;

		if (final_cost == m)
			cout << "Transaction succesful!" << endl;
		else if (final_cost > m)
			cout << "An amount of " << final_cost - m << " has been entered in your e-wallet." << endl;
		else if (final_cost < m) {
			cout << "You have not entered the correct amount!" << endl;
			c_pay(m);
		}
	}
	void e_pay(int m) {
		final_cost = m - ep;
		if (final_cost == 0)
			cout << "Wohoo! Transaction successful!" << endl;
		else if (final_cost > 0) {
			cout << "\nCredits in your e-wallet (before transaction): " << ep << endl;
			cout << "You still have to pay a cost of: " << final_cost << endl;
			ep = 0;
			c_pay(final_cost);
		}
		else if (final_cost < 0) {
			cout << "\nCredits in your e-wallet (before transaction): " << ep << endl;
			cout << "Wohoo! Transaction successful!" << endl;
			cout << "You still have " << (-1 * final_cost) << " credits left in your e-wallet" << endl;
			ep = final_cost;
		}
	}
};


class chatbot {
private:
	string user_reply, phone_num;
public:
	chatbot() {}
	void talk() {
		cout << "\nHello there. How are you doing? \n";
		getline(cin, user_reply);

		cout << "";
		getline(cin, user_reply);

		cout << "\nAhh, I see! So what can I help you with? \n";
		getline(cin, user_reply);

		cout << "\nHmm... Can you describe it with a few more details? \n";
		getline(cin, user_reply);

		cout << "\nWell, I'll definitly let out supervisors know about this! "
			"Is there anything you'd like to say?\n";
		getline(cin, user_reply);

		cout << "\nOk! So I'll get back in touch with you soon "
			"and will give you daily updates about your message. "
			"How about you drop your phone number so we can contact you? \n";
		getline(cin, phone_num);

		cout << "\nThanks a lot for your time. Have a nice day, and remember to park smart ;)\n";
		return;
	}
};

class admin {
private:
	int op;
	char e[35];		// e -> edit_info
	Vehicle v;
	vehicle_type vt;
	Parking p;
public:
	void view_record() {
		cout << endl << "Vehicle owner cnic: " << v.get_vehicle_owner();
		cout << endl << "Vehicle number plate: " << v.get_vehicle_id();
		cout << endl << "Vehicle brand: " << v.get_vehicle_brand();
		cout << endl << "Vehicle type: " << vt.get_vehicle_type() << "\n\n";

		Sleep(3000);
		system("CLS");
	}
	void edit_record() {
		cout << "Do you want to edit "
			"\n1. Vehicle owner cnic"
			"\n2. Vehicle brand"
			"\n3. Vehicle type\n";
		cin >> op;
		if (op == 1) {
			cout << "Enter cnic: ";
			string temp;
			cin >> temp;
			strcpy_s(e, temp.c_str());
			v.set_vehicle_owner(e);

			cout << "\nUPDATED INFO: ";
			view_record();
		}
		else if (op == 2) {
			cout << "Enter brand: ";
			cin >> e;
			v.set_vehicle_brand(e);

			cout << "\nUPDATED INFO: ";
			view_record();
		}
		else if (op == 3) {
			cout << "Enter vehicle type: ";
			cin >> e;
			vt.set_vt(e);

			cout << "\nUPDATED INFO: ";
			view_record();
		}
		else
			edit_record();
	}
	void avail_parking() {
		p.Check_all_available();
		cout << "\n\n";
		//#draw_map1(p.getcars_parked(), p);       //prints the map of parking place
		Sleep(3000);
		system("CLS");
	}
};
