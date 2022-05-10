#include <iostream>
#include <string>
using namespace std;

void menu();
void account(int option);
string AccountType[] = {"", "Account1", "Account2"};
string response;

//PIN number, Account1 account balance, Account2 account balance
int AccountDetails[] = {1234, 500, 10000 };

bool validatePin(int pin) {
	if (pin == AccountDetails[0]) {
		return true;
	} else {
		return false;
	}
}

bool proceed(string response) {
	if(response =="y" || response == "Y"){
		return true;
	} else if(response == "n" || response == "N"){
		string exit;
		cout << "\n-- Thank you. --";
		cin >> exit;
		return false;
	}
}

class AccountSettings {
	private:
		int type;		//account type
		int balance;	//account balance
	public:
		AccountSettings(int type) {
			//type 1 = Account1, type 2 = Account2
			this->type = type;
			this->balance = AccountDetails[this->type];
		}
		int getWithdraw() {
			int withdrawAmount;
			cout << "Please enter the amount to withdraw.\n" << endl;
			cin >> withdrawAmount;
			//get account type
			if(withdrawAmount <= this->balance){
				int AccountBalance = this->balance -= withdrawAmount;
				cout << "Your request to withdraw $"<< withdrawAmount << " has been completed.\n";
				//update the balance
				AccountDetails[this->type] = AccountBalance;
				getBalance();
			} else {
				cout << "Insufficient balance." << endl;
				getBalance();
			}
			return 0;
		}

		int getDeposit() {
			int depositAmount;
			cout << "Please enter an amount to deposit.\n" << endl;
			cin >> depositAmount;
			int AccountBalance = this->balance += depositAmount;
			// update the account balance
			AccountDetails[this->type] = AccountBalance;
			cout << "\t$" << depositAmount << " has been deposited into your account.\n";
			getBalance();
			return 0;
		}

		int getBalance() {
			string confirmBalance;
			//get the account type, and return balance
			cout << "Would you like to check your "<< AccountType[this->type] << " account balance? (Y/N)\n" << endl;
			cin >> confirmBalance;
			if(confirmBalance=="Y" || confirmBalance=="y"){
				cout <<"\n"<< AccountType[this->type] <<" account balance : $" << this->balance << endl;
			} 
			cout << "\nWould you like to continue? (Y/N) \n";
			cin >> response;
			if (proceed(response)) {
				account(this->type); // return to account menu
			}
			return 0;
		}
};

void account(int option) {
		//account option = 1 (Account1), account option = 2 (Account2)
		cout << "\n-- " <<AccountType[option]<< " --\n\t1. Check balance"<<"\n\t2. Withdraw"<<"\n\t3. Deposit"<<"\n\t4. Return to Main Menu" << endl;
		//Pass the account type
		AccountSettings Account(option); 
		int selectMenu;
		cin >> selectMenu;
		switch(selectMenu){
			case 1:
				cout << Account.getBalance();
				break;
			case 2: 
				cout << Account.getWithdraw();
				break;
			case 3: 
				cout << Account.getDeposit();
				break;
			case 4:
				menu(); //return to main menu
				break;
			default:
				cout << "Would you like to continue? (Y/N)\n";
				cin >> response;
				proceed(response);
				if (proceed(response)) {
					menu(); // return to main menu
				} 
				break;
		}
}

void menu() {
	int option;
	cout << "\n-- Main Menu --" <<endl;
	cout << "\tPlease select your Account" << endl;
	cout << "\t1. Account1 \n\t2. Account2 \n\t3. Exit" << endl;
	cin >> option;
	switch(option){
		case 1: account(option); // Account1
			break;
		case 2: account(option); // Account2
			break;
		default:
			cout << "Would you like to continue? (Y/N)\n";
			cin >> response;
			proceed(response);
			if (proceed(response)) {
				menu();
			} 
			break;
	}
}

// Begin MAIN
int main() {
	int pin;
	cout << "Please enter your PIN number to access your account." << endl;
	do {
		cin >> pin;
		if(validatePin(pin)) {
			menu(); //continue to main menu
		} else {
			cout << "Invalid PIN. Please enter a valid PIN." << endl; 
		}
	} while (!validatePin(pin));
	return 0;
}