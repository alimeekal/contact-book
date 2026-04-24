#pragma once
#include "Address.h"

#ifndef BASIC_LIB
#define BASIC_LIB
#include <iostream>			//basic libraries.
#include <string>
using namespace std;
#endif

class Contact {
private:
	int id;
	int views_count;
	string first_name;
	string last_name;			//members.
	string mobile_number;
	string email_address;
	Address* address;
public:
	friend istream& operator>>(istream&, Contact&);			//headers.
	bool equals(const Contact&) const;
	Contact* copyContact() const;

	void setId(int);
	void setViewCount(int);
	void setFirstName(const string&);
	void setLastName(const string&);
	void setMobileNumber(const string&);
	void setEmailAddress(const string&);
	void setAddress(Address*);
	void incrementViews();

	int getId() const;
	int getViewCount() const;
	string getFirstName() const;
	string getLastName() const;
	string getMobileNumber() const;
	string getEmailAddress() const;
	Address* getAddress() const;

	void printContact() const;

	Contact();
	Contact(string first_name, string last_name, string mobile_number, string email_address, Address* address);

	Contact(const Contact&);
	Contact& operator=(const Contact&);

	~Contact();
};