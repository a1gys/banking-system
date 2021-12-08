#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "User.h"

class program {
private:
	int cardNumber, pinCode;
	User *user;
  User *ben_acc;
	vector<string> row;
	string line, word;
public:
  program(); // constructor
  // functions of bank
  void withdraw();
  void deposit();
  void modify();
  void show();
  void transfer();
  void transfer_sender(int cash);
  void transfer_beneficiary(int card, int cash);
  void display();
  void returnMenu();
  void activate(int number);
};

#endif