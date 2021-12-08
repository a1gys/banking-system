#include "User.h"

User::User(int number) {
  this->cardNumber=number;
}
User::User(int number, int code) {
	this->cardNumber=number;
	this->pinCode=code; 
}
void User::setBankID(int number) {
  this->bankID=number;
}
void User::setName(string name) {
  this->name=name;
}
void User::setCardNum(int number) {
  this->cardNumber=number;
}
void User::setPinCode(int code) {
  this->pinCode=code;
}
void User::setBalance(int number) {
  this->balance=number;
}
void User::setTransaction(int number) {
  this->transaction=number;
}
int User::getBankID(){
  return this->bankID;
}
string User::getName() {
  return this->name;
}
int User::getCardNum() {
  return this->cardNumber;
}
int User::getPinCode() {
  return this->pinCode;
}
int User::getBalance() {
  return this->balance;
}
int User::getTransaction() {
  return this->transaction;
}