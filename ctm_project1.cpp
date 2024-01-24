#include <iostream>
#include <string>
#include <iomanip>
#include <climits>
#include <limits>
#include <fstream>
using namespace std;

class ctm {
	public:
	float scale = 0.01;
	int curr;
	float c;
	string t;
	void intro(){
	cout << "Select the exchange currency:\n";
	cout << "1. Yen\n" << "2. Rupee\n" << "3. Pound Sterling\n" << "4. Euro\n" << "5. CAD\n";
	cout << "Enter the exchange currency number (1-5): ";

		while (! (cin >> curr) ){
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid entry: Please enter a number between 1-5: ";
		}

		while (curr == 0 || curr != 0) {
		if (curr >= 1 && curr <= 5){
			if (curr == 1) {
				c = 6.77;
				t = "Yen";
				}
			else if (curr == 2){
				c = 80.01;
				t = "Rupees";
				}
			else if (curr == 3){
				c = 0.83;
				t = "Pounds";
				}
			else if (curr == 4){
				c = 0.98;
				t = "Euros";
				}
			else if (curr == 5){
				c = 1.29;
				t = "CAD";
				}
			break;
		}
		else {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry, please enter a number between 1-5: ";
			cin >> curr;
		}
		}
		}
		};

	class conv: public ctm {
			public:
			float convRate;
				void scanconv(){
					convRate = c;
					}
			};
	class amount: public conv {
			public:
			float scale = 0.01;
			float amnt, convCurr, convFee, totamnt;
			void calc(){
			cout << "Enter the amount needed in exchange currency: (in " << t << ") ";
			while (! (cin >> amnt) ){
			cout << "Invalid entry: (Please enter a number) Enter the amount needed in exchange currency: (in " << t << ") ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
				}
					convCurr = amnt / convRate;
					convFee = convCurr * 0.05;
					totamnt = convCurr + convFee;
	cout << "Current conversion rate -- " << fixed << setprecision(2) << convRate << " " << t << endl;
	cout << "Converted currency -- $ " << fixed << setprecision(2) << convCurr << endl;
	cout << "Conversion Fees (5%) -- $ " << fixed << setprecision(2) << convFee << endl;
	cout << "Total Amount Due -- $ " << fixed << setprecision(2) << totamnt << endl;
		}
		};
	class payment: public amount {
		public:
		char payopt, receipt;
		string z;
		void pmeth() {
			cout << "Enter 'c' for credit or 'd' for debit: ";
			while(! (cin >> payopt) ){
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry, please enter 'c' for credit or 'd' for debit: ";
			}

			while (payopt == 'c' || payopt != 'c') {
			if (payopt == 'c') {
				z = "credit";
				break;
				}
			else if (payopt == 'd'){
				z = "debit";
				break;
				}
			else {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Invalid entry, please enter 'c' for credit or 'd' for debit: ";
				cin >> payopt;
				}
			}
			}
		};
	class rcpt: public payment {
		public:
		string p, e, n, eml, CardNum, ExpDate, CvvCode;
		fstream rct;
		bool correct(string &CardNum){
			if (CardNum.length() != 16)
				return false;
			for (auto x: CardNum){
				if(x > '9' || x < '0')
				return false;
				}
				return true;
			}
		bool correct2(string &ExpDate){
			if (ExpDate.length() != 8)
				return false;
			for (auto x: ExpDate){
				if(x > '9' || x < '0')
				return false;
				}
				return true;
			}
		bool correct3(string &CvvCode){
			if (CvvCode.length() != 3)
				return false;
			for (auto x: CvvCode){
				if(x > '9' || x < '0')
				return false;
				}
				return true;
			}
		bool correcteml(string eml){
			for (size_t i = 0; i < eml.size(); i++){
				if (((int)(eml[i]) < 65 || (int)(eml[i]) > 90) && ((int)(eml[i]) < 97 || (int)(eml[i]) > 122)){
					return false;
					}
			}return true;
			}

		void rctype () {
		cout << "Enter " << z << " card details:\n";
		cout << "Card Number (16 Digit): ";
		while (1){
			cin >> CardNum;
			if(correct(CardNum)) break;
			else {
				cout << "Invalid entry, Enter a 16 digit card number: ";
				}
			}
		cout << "Expire Date (MMDDYYYY): ";
		while (1){
			cin >> ExpDate;
			if(correct2(ExpDate)) break;
			else {
				cout << "Invalid entry, Enter the date in MMDDYYYY format: ";
				}
			}
		cout << "CVV Code (###): ";
		while (1){
			cin >> CvvCode;
			if(correct3(CvvCode)) break;
			else {
				cout << "Invalid entry, Enter the 3 digit code (###): ";
				}
			}
		cout << "Processing Transaction ...\n";
		cout << "Transaction Complete!\n";
		rct.open("receipt.txt", ios::out);
		rct << "	Receipt Details\n" << "Currency Converted- $ " << convCurr << endl << "Conversion Fees- $ " << convFee << endl << "Total Amount Paid- $ " << totamnt << endl << "Thank you for your buisness!" << endl;
		rct.close();
		cout << "Enter 'p' to print receipt or 'e' to email or 'n' for no receipt: ";
		while (! (cin >> receipt) ){
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry, please enter 'p' to print receipt or 'e' to email or 'n' for no receipt: ";
			}

		while (receipt == 'p' || receipt != 'p') {
		if (receipt == 'p') {
			string line;
			rct.open("receipt.txt", ios::in);
			while (getline (rct, line)){
				cout << line << '\n';
				}
			rct.close();
			break;
			}
		else if (receipt == 'e'){
			cout << "Enter your email: ";
			while (1){
			cin >> eml;
			if(correcteml(eml)) break;
			else {
				cout << "Invalid entry, please enter your email: ";
				}
			}
			cout << "Email Sent.\nThank you for your buisness!";
			break;
			}
		else if (receipt == 'n'){
			cout << "Thank you for your buisness!";
			break;
			}
		else{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry, please enter 'p' to print receipt or 'e' to email or 'n' for no receipt: ";
			cin >> receipt;
			}
				}
			}
		};

int main(){

rcpt obj;
obj.ctm::intro();
obj.conv::scanconv();
obj.amount::calc();
obj.payment::pmeth();
obj.rctype();

	return 0;
	}
