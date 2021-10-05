//----------------------------------------------
// CS 215- 004 - Project 2
//----------------------------------------------
// Author: Blair Hall
// Date: February 28, 2018
// Description: Write a program that  implement an Automatic Teller Machine (ATM) for a small bank. 
// I received assistance from Thomas Barber
//----------------------------------------------
#include <iostream> 
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const int SHUT_DOWN = -2;
const int NOT_FOUND = -1;
bool startup(string acctArr[], int pinArr[], double balArr[],  int & acctNum);
void printAccts(string acctArr[], int pinArr[], double balArr[],  int & acctNum);
int readAccts(string acctArr[], int pinArr[], double balArr[]);
void printLogo();
int custLogin(string acctArr[], int pinArr[], double balArr[], int & acctNum);
char askAction();
void addTransaction(double wdAmt, double balArr[], string transNumArr[], double transAmtArr[], int & transNum, string acctArr[], int & custIndex);
void doDeposit(double balArr[], string transNumArr[], double transAmtArr[], int & transNum, string acctArr[], int & custIndex);
bool processCust(string acctArr[], int pinArr[], double balArr[], string transNumArr[], double transAmtArr[], int & transNum, int & acctNum);
void writeTrans(string transNumArr[], double transAmtArr[], int & transNum);
void printTrans(string transNumArr[], double transAmtArr[], int & transNum);
void shutdown(string acctArr[], int pinArr[], double balArr[], string transNumArr[], double transAmtArr[], int & transNum, int & acctNum );
void doWithdrawal(double balArr[], string transNumArr[], double transAmtArr[], int & transNum, string acctArr[], int & custIndex);

int main() {
	cout << fixed << setprecision(2);
	int transNum = 0, acctNum = 0;
	string acctArr[100];
	int pinArr[100];
	double balArr[100];
	string transNumArr[5];
	double transAmtArr[5];
	//startup(acctArr, pinArr, balArr, acctNum);
	
	if (startup(acctArr, pinArr, balArr, acctNum) == true) {
		shutdown(acctArr, pinArr, balArr, transNumArr, transAmtArr, transNum, acctNum);
	}
	else {
		
		while(!processCust(acctArr, pinArr, balArr, transNumArr, transAmtArr, transNum, acctNum));

	}
	shutdown(acctArr, pinArr, balArr, transNumArr, transAmtArr, transNum, acctNum );
	system("pause");
	return 0;
}
bool startup(string acctArr[], int pinArr[], double balArr[], int & acctNum) {
	printLogo();
	acctNum = readAccts(acctArr, pinArr, balArr);
	if (acctNum == -1) {
		cout << "Error reading accounts" << endl;
		cout << endl;
		return true;
		cout << "ATM STARTUP..." << endl;
		/*cout << "Current Accounts: Number = 4" << endl;
		cout << "ACCOUNT       PIN   BALANCE  " << endl;
		cout << "------------  ----  ---------" << endl; */


	}


	printAccts(acctArr, pinArr, balArr,  acctNum);
	//cout << "Shut down complete." << endl;
	//system("pause")
	return false;



}

void printAccts(string acctArr[], int pinArr[], double balArr[],  int & acctNum) {
	//int numAccts = 100;
	//int Accts = readAccts(acctArr, pinArr, balArr);

	cout << "Current Accounts: Number = " << acctNum << endl;

	cout << "ACCOUNT       PIN   BALANCE  " << endl;
	cout << "------------  ----  ---------" << endl;
	int i = 0;
	for (i = 0; i < acctNum; i++) {
		cout << setw(12) << left << acctArr[i]<< setw(6) << right << pinArr[i] << "  $ "<< setw(7) << right << balArr[i] << endl;
	}
}
int readAccts(string acctArr[], int pinArr[], double balArr[]) {
	ifstream fin;
	fin.open("accounts.txt", ios::in);
	if (!fin.is_open()) {
		cout << "File failed to open\n";
		return -1;
	}
	int num;
	string acctName;
	int pinNum;
	double bal;
	fin >> num;
	if (num <= 100) {
		for (int i = 0; i < num; i++) {
			fin >> acctName >> pinNum >> bal;
			acctArr[i] = acctName;
			pinArr[i] = pinNum;
			balArr[i] = bal;

		}	//cout << acct << " " << pin << " " << bal;
	}
	//if (num >= 100) {
	//return
	//}
	fin.close();
	return num;
	//getline(fin, wholeLine);
}
void printLogo() {
	cout << "+-------------------------------------------------+" << endl;
	cout << "|               WILDCAT BANKING ATM               |" << endl;
	cout << "|                   by Blair Hall                 |" << endl;
	cout << "+-------------------------------------------------+" << endl;

}

bool processCust(string acctArr[], int pinArr[], double balArr[], string transNumArr[], double transAmtArr[], int & transNum, int & acctNum) {
	printLogo();
	int custIndex = custLogin(acctArr, pinArr, balArr, acctNum);
	if (custIndex == SHUT_DOWN) {
		return true;

	}
	else if (custIndex == NOT_FOUND) {
		cout << "Invalid account number/pin combination" << endl;
		

		return false;
	}
	else {
		char transCode = askAction();
		switch (transCode) {
		case 'W':
			doWithdrawal(balArr, transNumArr, transAmtArr, transNum, acctArr, custIndex);
			break;
		case 'D':
			doDeposit(balArr, transNumArr, transAmtArr, transNum, acctArr, custIndex);
			break;

		case 'B':
			cout << "Your current balance is: $ " << balArr[custIndex] << endl;

			break;

		}
		return false; 
	}
}
int custLogin(string acctArr[], int pinArr[], double balArr[], int & acctNum) {
	int userPin;
	string entAcct;
	int i=0;
	cout << "Enter account number: ";
	cin >> entAcct;
	cout << "Enter pin number:     ";
	cin >> userPin;

	// take ccount #
	if (entAcct == "10000" && userPin == 1000) {
		return SHUT_DOWN;
	}

	for (i = 0; i < acctNum; i++) {
		// check which index is the account # stored in
		if (entAcct.compare(acctArr[i]) == 0 && userPin == pinArr[i]){
			return i;}
	}
	return NOT_FOUND;


	// take im pin check if right
	//cout << "Enter pin number: ";
	//cin >> userPin;
	/*if (userPin == pinArr[i] && userAcct == acctArr[i]) {
	cout << "Invalid account number/pin combination.";
	printLogo();
	}*/

}

char askAction() {
	char transCode;
	cout << "W - Withdraw" << endl;
	cout << "D - Deposit" << endl;
	cout << "B - Get Current Balance" << endl;

	cout << "Enter transaction code: ";
	cin >> transCode;

	while (transCode != 'W' && transCode != 'D' && transCode != 'B') {
		cout << "Invalid option...please enter W, D, or B!" << endl;
		cout << "W - Withdraw" << endl;
		cout << "D - Deposit" << endl;
		cout << "B - Get Current Balance" << endl;

		cout << "Enter transaction code: ";
		cin >> transCode;

	}
	return transCode;
}
void addTransaction(double wdAmt, double balArr[], string transNumArr[], double transAmtArr[], int & transNum, string acctArr[], int & custIndex) {

	if (transNum >= 5) {
		cout << "Transaction cannot be done. Contact IT Support." << endl;

	}
	else {
		transNumArr[transNum] = acctArr[custIndex];
		transAmtArr[transNum] = wdAmt;
		balArr[custIndex] += wdAmt;
		cout << "Transaction complete." << endl;
		cout << "Your new balance is now: $" << balArr[custIndex] << endl;
		transNum++;
	}
}


void doWithdrawal(double balArr[], string transNumArr[], double transAmtArr[], int & transNum, string acctArr[], int & custIndex) {
	double wdAmt;
	cout << "Enter withdrawal amount: $ ";
	cin >> wdAmt;

	while (wdAmt < 0.00 || wdAmt > balArr[custIndex]) {
		if (wdAmt < 0.00) {
			cout << "Invalid amount! Enter a value 0.00 or greater" << endl;
			cout << "Enter withdrawal amount: $ ";
			cin >> wdAmt;
		}


		if (wdAmt > balArr[custIndex]) {
			cout << "Your account only has $ " << balArr[custIndex] << endl;
			cout << "Enter withdrawal amount: $ ";
			cin >> wdAmt;
		}
	}
	if (wdAmt == 0) {
		cout << "Transaction canceled." << endl;

	}
	else {
		addTransaction(-1 * wdAmt, balArr, transNumArr, transAmtArr, transNum, acctArr, custIndex);
	}

}
void doDeposit(double balArr[], string transNumArr[], double transAmtArr[], int & transNum, string acctArr[], int & custIndex) {
	;
	double dAmt;
	cout << "Enter deposit amount: $ ";
	cin >> dAmt;
	while (dAmt < 0.00) {
		cout << "Invalid amount! Enter a value 0.00 or greater" << endl;
		cin >> dAmt;
	}
	if (dAmt == 0) {
		cout << "Transaction canceled" << endl;

	}
	else {
		addTransaction(dAmt, balArr, transNumArr, transAmtArr, transNum, acctArr, custIndex);
	}
}

void printTrans(string transNumArr[], double transAmtArr[], int & transNum, int & acctNum) {
	cout << "Transactions: number = " << transNum << endl;
	cout << "ACCOUNT        AMOUNT" << endl;
	cout << "------------   ----------" << endl;
	for (int i = 0; i <transNum; i++) {
		cout << left << setw(12) << transNumArr[i] << "   $  " << right << setw(4) << transAmtArr[i] << endl;
		
		
	}
}
	void writeTrans(string transNumArr[], double transAmtArr[], int & transNum, int & acctNum) {
		ofstream fout;
		fout << fixed << setprecision(2);
		fout.open("transactions.txt", ios::out);
		if (!fout.is_open()) {
			cout << "Unable to open transaction output file." << endl;
		}
		else {
			//fout << "Transactions: number = " << transNum << endl;
			//cout << "ACCOUNT       AMOUNT" << endl;
			//cout << "------------  ----------" << endl;
			



			cout << "Transactions written to file." << endl;
			
		}
		}
void shutdown(string acctArr[], int pinArr[], double balArr[], string transNumArr[], double transAmtArr[], int & transNum, int & acctNum) 
{
	cout << "Shutting down ATM..." << endl;
	printTrans(transNumArr, transAmtArr, transNum, acctNum);
	writeTrans(transNumArr, transAmtArr, transNum, acctNum);
	printAccts( acctArr, pinArr, balArr, acctNum);
	cout << "Shut down complete." << endl;
}
