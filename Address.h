#pragma once
#include <iostream>		//basic libraries.
#include <string>
using namespace std;

class Address {
private:
	string house;
	string street;		//members.
	string city;
	string country;
public:
	friend istream& operator>>(istream&, Address&);		//headers.
	bool equals(const Address&) const;
	void printAddress() const;
	Address copyAddress() const;

	void setHouse(const string&);
	void setStreet(const string&);
	void setCity(const string&);
	void setCountry(const string&);

	string getHouse() const;
	string getStreet() const;
	string getCity() const;
	string getCountry() const;

	Address(string house, string street, string city, string country);
	Address();
	~Address();
};