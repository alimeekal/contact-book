#include "Contact.h"

Contact::Contact() {
	first_name = "";
	last_name = "";			//default constructor.
	mobile_number = "";
	email_address = "";
	address = nullptr;
	views_count = 0;
}

Contact::Contact(string first_name, string last_name, string mobile_number, string email_address, Address* address) {
	setFirstName(first_name);
	setLastName(last_name);
	setMobileNumber(mobile_number);			//parameterized constructor.
	setEmailAddress(email_address);
	setAddress(address);
}

Contact::Contact(const Contact& other) {
	id = other.id;
	views_count = other.views_count;
	first_name = other.first_name;
	last_name = other.last_name;
	mobile_number = other.mobile_number;			//copy constructor.
	email_address = other.email_address;
	if (other.address != nullptr) {
		address = new Address(*(other.address));
	}
	else {
		address = nullptr;
	}
}

Contact& Contact::operator=(const Contact& other) {
	if (this != &other) {
		id = other.id;
		views_count = other.views_count;
		first_name = other.first_name;
		last_name = other.last_name;
		mobile_number = other.mobile_number;			//overloaded assignment operator.
		email_address = other.email_address;
		delete address;
		if (other.address != nullptr) {
			address = new Address(*(other.address));
		}
		else {
			address = nullptr;
		}
	}
	return *this;
}

//setters.

void Contact::setId(int contact_id) {
	id = contact_id;
}

void Contact::setViewCount(int count) {
	views_count = count;
}

void Contact::setFirstName(const string& f1) {
	if (f1 != "") {
		first_name = f1;
	}
}

void Contact::setLastName(const string& l1) {
	if (l1 != "") {
		last_name = l1;
	}
}

void Contact::setMobileNumber(const string& m1) {
	if (m1 != "" && m1.length() == 11) {
		mobile_number = m1;
	}
	else mobile_number = "INVALID!";
}

void Contact::setEmailAddress(const string& e1) {
	if (e1 != "") {
		email_address = e1;
	}
}

void Contact::setAddress(Address* a1) {
	if (address != nullptr) {
		delete address;
	}
	if (a1 != nullptr) {
		address = new Address(a1->getHouse(), a1->getStreet(), a1->getCity(), a1->getCountry());
	}
	else {
		address = nullptr;
	}
}

void Contact::incrementViews() {
	views_count++;
}

//getters.

int Contact::getId() const {
	return id;
}

int Contact::getViewCount() const {
	return views_count;
}

string Contact::getFirstName() const {
	return first_name;
}

string Contact::getLastName() const {
	return last_name;
}

string Contact::getMobileNumber() const {
	return mobile_number;
}

string Contact::getEmailAddress() const {
	return email_address;
}

Address* Contact::getAddress() const {
	return address;
}

bool Contact::equals(const Contact& c1) const {			//function to check equal contacts.
	if (c1.first_name == this->first_name && c1.last_name == this->last_name && c1.mobile_number == this->mobile_number && c1.email_address == this->email_address
		&& c1.address->equals(*address) == true) {
		return true;
	}
	else return false;
}

Contact* Contact::copyContact() const {
	Address* address_copy = nullptr;
	if (address != nullptr) {
		address_copy = new Address(address->copyAddress());			//copy contact.
	}
	return new Contact(first_name, last_name, mobile_number, email_address, address_copy);
}

void Contact::printContact() const {
	cout << "ID: " << id << endl;
	cout << "Name: " << first_name << " " << last_name << endl;
	cout << "Mobile Number: " << mobile_number << endl;
	cout << "Email Address: " << email_address << endl;				//print contact.
	cout << "House: " << address->getHouse() << endl;
	cout << "Street: " << address->getStreet() << endl;
	cout << "City: " << address->getCity() << endl;
	cout << "Country: " << address->getCountry() << endl;
}

istream& operator>>(istream& i, Contact& c1) {
	string first_name, last_name, mobile_number, email_address;
	Address address;

	cout << "Enter First Name: ";
	getline(i, first_name);
	cout << "Enter Last Name: ";
	getline(i, last_name);						//overloaded cin operator.
	cout << "Enter Mobile Number: ";
	getline(i, mobile_number);
	cout << "Enter Email Address: ";
	getline(i, email_address);
	cin >> address;

	c1.setFirstName(first_name);
	c1.setLastName(last_name);
	c1.setMobileNumber(mobile_number);
	c1.setEmailAddress(email_address);
	c1.setAddress(&address);

	return i;
}

Contact::~Contact() {
	if (address != nullptr) {
		delete address;				//destructor with memory deletion.
		address = nullptr;
	}
}