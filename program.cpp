#include "program.h"
#include <cstdio>

program::program() {
	fstream fin;
  vector<string>::iterator it;
  fin.open("database.csv", ios::in);
  int count = 0;

 	cout << "\nCard number (6 digits): ";
  cin >> cardNumber;
  while(!fin.eof()){
    row.clear();
    getline(fin, line);
    stringstream t(line);
    while(getline(t, word, ',')) {
      row.push_back(word);
    }
    if(row[2] == to_string(cardNumber)) {
      string pin;
      it = row.begin();
      pin = *(it+3);
      if (pin[0] >= 64 | pin[1] >= 64 | pin[2] >= 64 | pin[3] >= 64) {
        cout << endl << "Your account is not active." << endl;
        activate(cardNumber);
      }
      else {
        cout << "Pin code (4 digits): "; cin >> pinCode;
      }
    }
  }
  fin.close();

	fin.open("database.csv", ios::in);
  while (!fin.eof()) {
	  
	  row.clear();
	  getline(fin, line);
	  stringstream s(line);
	  
	  while (getline(s, word, ',')) {
	    row.push_back(word);
	    }
	  if (row[2]==to_string(cardNumber) && row[3]==to_string(pinCode)) {
	
	    count = 1;
	    user = new User(cardNumber, pinCode);
			user->setBankID(stoi(row[0]));
			user->setName(row[1]);
			user->setCardNum(stoi(row[2]));
			user->setPinCode(stoi(row[3]));
			user->setBalance(stoi(row[4]));
			user->setTransaction(stoi(row[5]));
	    display();
	    break;
	      }
	  }
	    if (count == 0) {
	      cout << "\nThe card number or PIN code is incorrect. Please, try again.\n";
			  program();
		    }
		fin.close(); 
}
void program::withdraw() {
	fstream fin, fout;
	
	fin.open("database.csv", ios::in); 
	fout.open("DATA2.csv", ios::out);

	int count = 0;
	vector<string> row;
	string line, word;
	int withdrawn;
	
  cout << endl << "Current balance: " << to_string(user->getBalance()) + " KZT" << endl;
	cout << endl << "Enter amount to withdraw: "; cin >> withdrawn;
	if(withdrawn <= user->getBalance()){
    while(!fin.eof()) {
      row.clear();
      
      getline(fin, line);
      stringstream s(line);
      
      while(getline(s, word, ',')) {
        row.push_back(word);
      }
      if (row[2]==to_string(cardNumber) && row[3]==to_string(pinCode)) {
        count = 1;
        stringstream convert;
        stringstream convert2;
        convert << stoi(row[4])	- withdrawn;
        row[4] = convert.str();
        convert2 << 0 - withdrawn;
        row[5] = convert2.str();
        user->setBalance(stoi(row[4]));
        user->setTransaction(stoi(row[5]));

        if(!fin.eof()) { // placing vector data into new csv
          for (int i=0; i<row.size()-1; i++) 
            fout << row[i] << ",";
          fout << row[row.size()-1] << endl;
        }
      }
      else {
        if(!fin.eof()) {
          for (int i=0; i<row.size()-1; i++)
            fout << row[i] << ",";
          fout << row[row.size()-1] << endl;
        }
      }
      if(fin.eof())
        break;
    }
    if (count==0)
      cout << "record is not found" << endl;
    fin.close();
    fout.close();
    
    remove("database.csv");
    rename("DATA2.csv", "database.csv");
    
    cout << "Cash withdrawn successfully!" << endl;
    cout << "Remaining balance: " << to_string(user->getBalance()) + " KZT" << endl << endl;
    
    returnMenu(); 
  }
  else {
    cout << "You don't have enough balance" << endl;
    cout << "Enter less amount" << endl;
    withdraw();
  }
}
void program::deposit() {
	fstream fin, fout;
	
	fin.open("database.csv", ios::in); 
	fout.open("DATA2.csv", ios::out);

	int count = 0;
	vector<string> row;
	string line, word;
	int depo;
	
  cout << endl << "Current balance: " << to_string(user->getBalance()) + " KZT" << endl;
	cout << endl << "Enter amount to deposit: "; cin >> depo;
    while(!fin.eof()) {
      row.clear();
      
      getline(fin, line);
      stringstream s(line);
      
      while(getline(s, word, ',')) {
        row.push_back(word);
      }
      if (row[2]==to_string(cardNumber) && row[3]==to_string(pinCode)) {
        count = 1;
        stringstream convert;
        stringstream convert2;
        convert << stoi(row[4])	+ depo;
        row[4] = convert.str();
        convert2 << depo;
        row[5] = convert2.str();
        user->setBalance(stoi(row[4]));
        user->setTransaction(stoi(row[5]));

        if(!fin.eof()) {
          for (int i=0; i<row.size()-1; i++)
            fout << row[i] << ",";
          fout << row[row.size()-1] << endl;
        }
      }
      else {
        if(!fin.eof()) {
          for (int i=0; i<row.size()-1; i++)
            fout << row[i] << ",";
          fout << row[row.size()-1] << endl;
        }
      }
      if(fin.eof())
        break;
    }

    if (count==0)
      cout << "record is not found" << endl;
    fin.close();
    fout.close();
    
    remove("database.csv");
    rename("DATA2.csv", "database.csv");

  
    cout << "Cash deposited successfully!" << endl;
    cout << "Remaining balance: " << to_string(user->getBalance()) + " KZT" << endl << endl;
    
    returnMenu(); 
}
void program::modify() {
	int card;
  fstream fin, fout;
	
	fin.open("database.csv", ios::in); 
	fout.open("DATA2.csv", ios::out);

	int count = 0;
	vector<string> row;
	string line, word;
	int new_pin;
	cout << "Enter the card number of the account: ";
  cin >> card;

  while(!fin.eof()) {
      row.clear();
      
      getline(fin, line);
      stringstream s(line);
      
      while(getline(s, word, ',')) {
        row.push_back(word);
      }
      if (row[2]==to_string(card)) {
        count = 1;
        vector<string>::iterator it;
        string pin;
        it = row.begin();
        pin = *(it+3);
        if (pin[0] >= 64 | pin[1] >= 64 | pin[2] >= 64 | pin[3] >= 64) {
        cout << endl << "This account is not active." << endl;
        activate(card);
        }
        else {
          stringstream convert;
          cout << "This account is already activated." << endl;
          cout << "Enter your new PIN code: "; cin >> new_pin;
          convert << new_pin;
          row[3] = convert.str();
          user->setPinCode(stoi(row[3]));
        }
        if(!fin.eof()) {
          for (int i=0; i<row.size()-1; i++)
            fout << row[i] << ",";
          fout << row[row.size()-1] << endl;
        }
      }
      else {
        if(!fin.eof()) {
          for (int i=0; i<row.size()-1; i++)
            fout << row[i] << ",";
          fout << row[row.size()-1] << endl;
        }
      }
      if(fin.eof())
        break;
    }
    if (count==0)
      cout << "record is not found" << endl;
    fin.close();
    fout.close();
    
    remove("database.csv");
    rename("DATA2.csv", "database.csv");
    if (count==1)
      cout << "PIN code has been changed successfully!" << endl;
    returnMenu(); 
}
void program::show() {
	cout << "Card owner: " << user->getName() << endl;
	cout << "Card number: " << user->getCardNum() << endl;
	cout << "Current balance in KZT: " << user->getBalance() << endl;
	cout << "Current balance in USD: " << user->getBalance()/450 << endl;
	cout << "Last transaction: " << user->getTransaction() << endl << endl;
	returnMenu();
}
void program::transfer() {
  fstream fin;
  string answer;
  string option;
  int count = 0;
  int beneficiary; // card number of receiver
  int transfer; // amount to be send
  fin.open("database.csv", ios::in);

  cout << "**Commision for fund transfers over 20,000 KZT is 500 KZT" << endl << "**Commision for fund transfers to other banks is 200 KZT" << endl;
  cout << endl << "Beneficiary's card number: "; cin >> beneficiary;
  cout << "Transfer amount (in KZT): "; cin >> transfer;

  while (!fin.eof()) {
	  row.clear();
	  getline(fin, line);
	  stringstream s(line);

	  while (getline(s, word, ',')) {
	
	    row.push_back(word);
	    }
	  if (row[2]==to_string(beneficiary)) {
	    count = 1;
      vector<string>::iterator it;
      string pin;
      it = row.begin();
      pin = *(it+3);
      if (pin[0] >= 64 | pin[1] >= 64 | pin[2] >= 64 | pin[3] >= 64) {
        cout << endl << "This account is not active." << endl;
        activate(beneficiary);
      }  
      else {
        ben_acc = new User(beneficiary);
        ben_acc->setBankID(stoi(row[0]));
        ben_acc->setName(row[1]);
        ben_acc->setCardNum(stoi(row[2]));
        ben_acc->setPinCode(stoi(row[3]));
        ben_acc->setBalance(stoi(row[4]));
        ben_acc->setTransaction(stoi(row[5]));
        break;
      }
	  }
	}
	    if (count == 0) {
	      cout << "The card number or PIN code is incorrect. Please, try again.\n";
			  returnMenu();
		    }
		fin.close();

  cout << endl << "Beneficiary's name: " << ben_acc->getName() << endl;
  cout << "Conform transfer? (Y/N):"; cin >> answer;
  while (answer != "y" | answer != "Y" | answer != "n" | answer != "N") {
		if (answer == "y" | answer == "Y") {
      transfer_sender(transfer);
			transfer_beneficiary(beneficiary, transfer);
      cout << endl << "Transfer successful!" << endl << endl;
      returnMenu();
    }
    else if(answer == "n" | answer == "N") {
      cout << endl << "Transfer canceled!" << endl << endl;
      returnMenu();
    }
		else
			cout << "Invalid input, please enter correct option.";
		}
}
void program::transfer_sender(int cash){
  int count = 0;
  fstream fin, fout;
  fin.open("database.csv", ios::in);
  fout.open("DATA3.csv", ios::out);

  while(!fin.eof()) {
      row.clear();
      getline(fin, line);
      stringstream s(line);
      while(getline(s, word, ',')) {
        row.push_back(word);
      }
      if (row[2]==to_string(cardNumber) && row[3]==to_string(pinCode)) {
        count = 1;
        stringstream s1;
        stringstream s2;
        if (cash <= user->getBalance()) {
          if (cash > 20000) {
            if(ben_acc->getBankID() == user->getBankID()) {
              s1 << stoi(row[4]) - (cash + 500);
              row[4] = s1.str();
              s2 << 0 - cash;
              row[5] = s2.str();
              user->setBalance(stoi(row[4]));
              user->setTransaction(stoi(row[5]));
            }
            else if(ben_acc->getBankID() != user->getBankID()) {
              s1 << stoi(row[4]) - cash - 700;
              row[4] = s1.str();
              s2 << 0 - cash;
              row[5] = s2.str();
              user->setBalance(stoi(row[4]));
              user->setTransaction(stoi(row[5]));
            }
          }
          else if(cash <= 20000) {
            if(ben_acc->getBankID() == user->getBankID()) {
              s1 << stoi(row[4]) - cash;
              row[4] = s1.str();
              s2 << 0 - cash;
              row[5] = s2.str();
              user->setBalance(stoi(row[4]));
              user->setTransaction(stoi(row[5]));
            }
            else if(ben_acc->getBankID() != user->getBankID()) {
              s1 << stoi(row[4]) - cash - 200;
              row[4] = s1.str();
              s2 << 0 - cash;
              row[5] = s2.str();
              user->setBalance(stoi(row[4]));
              user->setTransaction(stoi(row[5]));
            }
          }
        }
        else {
          cout << "Transfer fund exceeds your current balance";
          transfer();
        }
        if(!fin.eof()) {
          for (int i=0; i<row.size()-1; i++)
            fout << row[i] << ",";
          fout << row[row.size()-1] << endl;
        }
      }
      else {
        if(!fin.eof()) {
          for (int i=0; i<row.size()-1; i++)
            fout << row[i] << ",";
          fout << row[row.size()-1] << endl;
        }
      }
      if(fin.eof())
        break;
    }
  if (count==0)
    cout << "record is not found" << endl;
  fin.close();
  fout.close();
    
  remove("database.csv");
  rename("DATA3.csv", "database.csv");
}
void program::transfer_beneficiary(int card, int cash) {
  vector<string> r;
  vector<string>::iterator it;
  string l, w;
  int count = 0;
  fstream fin, fout;
  fin.open("database.csv", ios::in);
  fout.open("DATA2.csv", ios::out);
  string answer;
  string option; // yes / no

  while(!fin.eof()) {
        r.clear();
        getline(fin, l);
        stringstream s(l);
        while(getline(s, w, ',')) {
          r.push_back(w);
        }
        if (r[2]==to_string(card)) {
          count = 1;
          stringstream t1;
          stringstream t2;
          t1 << stoi(r[4]) + cash;
          r[4] = t1.str();
          t2 << cash;
          r[5] = t2.str();
          ben_acc->setBalance(stoi(r[4]));
          ben_acc->setTransaction(stoi(r[5]));
          
          if(!fin.eof()) {
            for (int i=0; i<r.size()-1; i++)
              fout << r[i] << ",";
            fout << r[r.size()-1] << endl;
          }
        }
        else {
          if(!fin.eof()) {
            for (int i=0; i<r.size()-1; i++)
              fout << r[i] << ",";
            fout << r[r.size()-1] << endl;
          }
        }
        if(fin.eof())
          break;
      }
  if (count==0)
    cout << "record is not found" << endl;
  fin.close();
  fout.close();
    
  remove("database.csv");
  rename("DATA2.csv", "database.csv");
}
void program::display() {
  int choice;
		
	while(true) {
		cout << "\nSelect one of the following options:" << endl;
		cout << endl;
    cout << "1. Withdraw Cash		        2. Deposit Cash" << endl;
		cout << "3. Modify PIN Code 		        4. Show Balance" << endl;
		cout << "5. Transfer Between Accounts	6. End Session" << endl;
		cout << "\nEnter option number: ";
		cin >> choice;
		cout << endl;
		switch(choice) {
			case 1:	withdraw();
				break;
			case 2:	deposit();
				break;
			case 3:	modify();
				break;
			case 4:	show();
				break;  
      case 5:	transfer();
				break;
			case 6:
				exit(0);
			default:
				cout << "Invalid input, please try again";
			}
		}
  cout << "Thank you for using our Bank";
}
void program::returnMenu() {
  string answer;
  cout << "Would you like to return to the main menu? [Y/N]: ";
	cin >> answer;
	while (answer != "y" | answer != "Y" | answer != "n" | answer != "N") {
		if (answer == "y" | answer == "Y")
			display();
		else if(answer == "n" | answer == "N") {
      cout << "Thank you for using our bank!";
      exit(0);
    }
		else
			cout << "Invalid input, please enter correct option." << endl << endl;
      returnMenu();
		}	  
}
void program::activate(int number) {
  fstream fin, fout;
	int count = 0;	
	fin.open("database.csv", ios::in); 
	fout.open("DATA2.csv", ios::out);

  while(!fin.eof()) {
      row.clear();
      
      getline(fin, line);
      stringstream s(line);
      
      while(getline(s, word, ',')) {
        row.push_back(word);
      }
      if (row[2]==to_string(number)) {
        count = 1;
        cout << endl << "Enter new PIN code to activate this account: ";
        cin >> pinCode;
        row[3] = to_string(pinCode);
        user = new User(cardNumber, pinCode);
        user->setPinCode(stoi(row[3]));
        user->setName(row[1]);
        user->setBalance(stoi(row[4]));
        user->setTransaction(stoi(row[5]));
        user->setBankID(stoi(row[0]));

        if(!fin.eof()) {
          for (int i=0; i<row.size()-1; i++)
            fout << row[i] << ",";
          fout << row[row.size()-1] << endl;
        }
      }
      else {
        if(!fin.eof()) {
          for (int i=0; i<row.size()-1; i++)
            fout << row[i] << ",";
          fout << row[row.size()-1] << endl;
        }
      }
      if(fin.eof())
        break;
    }
    if (count==0)
      cout << "record is not found" << endl;
    fin.close();
    fout.close();
    
    remove("database.csv");
    rename("DATA2.csv", "database.csv");

    cout << "Your account has been activated successfully!" << endl;
    returnMenu(); 
}