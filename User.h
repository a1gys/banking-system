#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class User {
private:
	int cardNumber, bankID; 
  int signed long long transaction; 
  int signed long long balance;
	int mutable pinCode;
	string name;
public:
  User(int number);
  User(int number, int code); // constructor
  //setters
  void setBankID(int number);
  void setName(string name);
  void setCardNum(int number);
  void setPinCode(int code);
  void setBalance(int number);
  void setTransaction(int number);
  //getters
  int getBankID();
  string getName();
  int getCardNum();
  int getPinCode();
  int getBalance();
  int getTransaction();
};

#endif