#define _CRT_SECURE_NO_WARNINGS		//in order to use ctime without error.
#include "ContactsBook.h"
#include "Group.h"
#include<fstream>		//for file handling.

int ContactsBook::contactCounter = 0;

int ContactsBook::groupCounter = 0;

ContactsBook::ContactsBook() {}		//default constructor.

ContactsBook::ContactsBook(int size_of_list = 0) : size_of_contacts(size_of_list), contacts_count(0), groups_count(0) {		//parameterized constructor.
	contacts_list = new Contact[size_of_contacts];
	for (int i = 0; i < size_of_contacts; i++) {
		contacts_list[i] = Contact();
	}
}

ContactsBook::ContactsBook(const ContactsBook& other) {			//copy constructor.
	size_of_contacts = other.size_of_contacts;
	contacts_count = other.contacts_count;
	groups_count = other.groups_count;
	contacts_list = new Contact[size_of_contacts];
	for (int i = 0; i < contacts_count; i++) {
		Contact* copiedContact = other.contacts_list[i].copyContact();
		if (copiedContact != nullptr) {
			this->contacts_list[i] = *copiedContact;
			delete copiedContact;
		}
	}
}

ContactsBook& ContactsBook::operator=(const ContactsBook& other) {			//overloaded assignment operator.
	if (this != &other) {
		delete[] contacts_list;
		size_of_contacts = other.size_of_contacts;
		contacts_count = other.contacts_count;
		groups_count = other.groups_count;
		contacts_list = new Contact[size_of_contacts];
		for (int i = 0; i < contacts_count; i++) {
			Contact* copiedContact = other.contacts_list[i].copyContact();
			if (copiedContact != nullptr) {
				this->contacts_list[i] = *copiedContact;
				delete copiedContact;
			}
		}
	}
	return *this;
}

//count of contacts and groups.

int ContactsBook::totalContacts() const {
	return contacts_count;
}

int ContactsBook::totalGroups() const {
	return groups_count;
}

bool ContactsBook::full() const {
	if (size_of_contacts == contacts_count) {		//function to check if contacts_list is full.
		return true;
	}
	else return false;
}

void ContactsBook::resizeList() {
	int new_size = 2 * size_of_contacts;
	Contact* temp = new Contact[new_size];
	for (int i = 0; i < size_of_contacts; i++) {		//if contacts_list is full, it is resized.
		temp[i] = *contacts_list[i].copyContact();
		temp[i].setId(contacts_list[i].getId());
	}
	delete[] contacts_list;
	contacts_list = temp;
	size_of_contacts = new_size;
}

void ContactsBook::addContact(const Contact& c1) {
	system("cls");
	if (this->full() == true) {
		this->resizeList();											//add a contact to contacts_list.
	}
	contacts_list[contacts_count] = c1;
	contacts_list[contacts_count].setId(contactCounter + 1);
	contactCounter++;
	contacts_count++;
}

void ContactsBook::searchContact(string search) {								//advanced search that uses only one string.
	system("cls");
	addSearchToHistory(search);
	string first_name, last_name, mobile_number, email_address, full_address;
    bool found = false;
    for (int i = 0; i < contacts_count; i++) {
        first_name = contacts_list[i].getFirstName();
        last_name = contacts_list[i].getLastName();
        mobile_number = contacts_list[i].getMobileNumber();
        email_address = contacts_list[i].getEmailAddress();
        Address* address = contacts_list[i].getAddress();
        full_address = address->getHouse() + " " + address->getStreet() + " " + address->getCity() + " " + address->getCountry();
        if (searchCharacter(search, first_name) || searchCharacter(search, last_name) || searchCharacter(search, mobile_number) || searchCharacter(search, email_address)
			|| searchCharacter(search, full_address)) {
			cout << "\033[1;31m-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
            cout << "\tMatch Found!\t ||" << endl;
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m" << endl;
            contacts_list[i].printContact();
			if (i == contacts_count - 1) {
				cout << endl;
			}
            found = true;
        }
    }
    if (!found) {
		cout << "No Match Found! " << endl;
    }
}

bool ContactsBook::searchCharacter(string search, string attribute) const {			//character level match.
    int j = 0;
    for (int i = 0; i < attribute.length(); i++) {
        if (attribute[i] == search[j]) {
            j++;
            if (j == search.length()) {
                return true;
            }
        }
    }
    return false;
}

void ContactsBook::printContacts() const {			//print contacts unsorted.
	system("cls");
	if (contacts_count != 0) {
		for (int i = 0; i < contacts_count; i++) {
			cout << "ID: " << contacts_list[i].getId() << endl;
			cout << "[" << contacts_list[i].getFirstName() << "] [" << contacts_list[i].getLastName() << "] [" << contacts_list[i].getMobileNumber() << "] [" << contacts_list[i].getEmailAddress() << "]" << endl;
			contacts_list[i].getAddress()->printAddress();
			cout << endl;
		}
	}
	else {
		cout << "Contacts List is Empty!" << endl;
	}
}

void ContactsBook::sortContactsList(Contact* contacts_list, string choice) const {		//sort contacts.
	for (int i = 0; i < size_of_contacts - 1; i++) {
		for (int j = 0; j < size_of_contacts - i - 1; j++) {
			if ((choice == "first_name" && contacts_list[j].getFirstName() > contacts_list[j + 1].getFirstName() && contacts_list[j + 1].getFirstName() != "") ||
				(choice == "last_name" && contacts_list[j].getLastName() > contacts_list[j + 1].getLastName() && contacts_list[j + 1].getLastName() != "")) {
				swap(contacts_list[j], contacts_list[j + 1]);
			}
		}
	}
}

void ContactsBook::printContactsSorted(string choice) {
	system("cls");
	Contact* copy = this->copyArray();
	sortContactsList(copy, choice);
	if (choice == "first_name" || choice == "last_name") {			//print contacts after sorting.
		for (int i = 0; i < contacts_count; i++) {
			cout << "ID: " << copy[i].getId() << endl;
			cout << "[" << copy[i].getFirstName() << "] [" << copy[i].getLastName() << "] [" << copy[i].getMobileNumber() << "] [" << copy[i].getEmailAddress() << "]" << endl;
			copy[i].getAddress()->printAddress();
			if (i != contacts_count - 1) {
				cout << endl;
			}
		}
	}
	else {
		cout << "Invalid Searching Method!" << endl;
	}
	delete[] copy;
}

void ContactsBook::mergeDuplicates() {				//merge duplicate contacts.
	int count = 0;
	for (int i = 0; i < contacts_count; i++) {
		int duplicates = 0;
		for (int j = i + 1; j < contacts_count; j++) {
			if (contacts_list[i].equals(contacts_list[j])) {
				for (int k = j; k < contacts_count - 1; k++) {
					contacts_list[k] = contacts_list[k + 1];
				}
				contacts_list[contacts_count - 1] = Contact();
				contacts_count--;
				count++;
				duplicates++;
				j--;
			}
		}
		if (duplicates == 1) {
			int remove = contacts_list[i].getId();
			for (int k = 0; k < groups_count; k++) {
				if (groups.getArray()[k].hasContact(remove)) {
					groups.getArray()[k].removeContact(remove);
				}
			}
		}
	}
	cout << "Merged Contacts: " << count << endl;
	if (count > 0) {
		cout << "Duplicates Merged Successfully." << endl;
	}
	else {
		cout << "No Duplicates Found!" << endl;
	}
}

void ContactsBook::loadFromFile(string file_name) {		//load from file.
	system("cls");
	int contacts_count;
	string first_name, last_name, mobile_number, email_address, house, street, city, country;
	ifstream input_file(file_name);
	if (!input_file.is_open() || file_name == "contacts_output.txt") {
		cout << "Invalid File Name!" << endl;
		return;
	}
	input_file >> contacts_count;
	if (contacts_count > size_of_contacts) {
		resizeList();
	}
	for (int i = 0; i < contacts_count; i++) {
		input_file >> first_name >> last_name >> mobile_number >> email_address >> house >> street >> city >> country;
		Address address(house, street, city, country);
		Contact contact(first_name, last_name, mobile_number, email_address, &address);
		this->addContact(contact);
	}
	cout << "Loaded from File '" << file_name << "' Successfully." << endl;
	input_file.close();
}

void ContactsBook::saveToFile(string file_name) {		//save to file. saves contacts, groups & search_history.
	if (file_name == "contacts_output.txt" || file_name == "groups_output.txt" || file_name == "search_history.txt" || file_name == "frequently_searched.txt") {
		ofstream output_file(file_name);
		if (file_name == "contacts_output.txt") {
			output_file << "Contacts Count: " << contacts_count << endl;
			output_file << endl;
			for (int i = 0; i < contacts_count; i++) {
				output_file << contacts_list[i].getFirstName() << " " << contacts_list[i].getLastName() << ", " << contacts_list[i].getMobileNumber() << ", " <<
					contacts_list[i].getEmailAddress() << endl;
				output_file << contacts_list[i].getAddress()->getHouse() << ", " << contacts_list[i].getAddress()->getStreet() << ", " <<
					contacts_list[i].getAddress()->getCity() << ", " << contacts_list[i].getAddress()->getCountry() << endl;
				output_file << endl;
			}
		}
		if (file_name == "groups_output.txt") {
			for (int i = 0; i < groups_count; i++) {
				output_file << "ID: " << groups.getArray()[i].getId() << endl;
				output_file << "Name: " << groups.getArray()[i].getName() << endl;
				output_file << endl;
				for (int j = 0; j < groups.getArray()[i].getContactIds().getSize(); j++) {
					for (int k = 0; k < contacts_count; k++) {
						if (groups.getArray()[i].getContactIds().getArray()[j] == contacts_list[k].getId()) {
							output_file << contacts_list[k].getFirstName() << " " << contacts_list[k].getLastName() << ", " << contacts_list[k].getMobileNumber() << ", " <<
								contacts_list[k].getEmailAddress() << endl;
							output_file << contacts_list[k].getAddress()->getHouse() << ", " << contacts_list[k].getAddress()->getStreet() << ", " <<
								contacts_list[k].getAddress()->getCity() << ", " << contacts_list[k].getAddress()->getCountry() << endl;
							output_file << endl;
						}
					}
				}
			}
		}
		if (file_name == "search_history.txt") {
			for (int i = 0; i < history.getSize(); i++) {
				time_t t = history.getArray()[i].getTimestamp();
				string time = ctime(&t);
				output_file << "'" << history.getArray()[i].getSearch() << "' on " << time;
			}
		}
		if (file_name == "frequently_searched.txt") {
			Contact* top5 = copyArray();
			for (int i = 0; i < contacts_count - 1; i++) {
				for (int j = 0; j < contacts_count - i - 1; j++) {
					if (top5[j].getViewCount() < top5[j + 1].getViewCount()) {
						swap(top5[j], top5[j + 1]);
					}
				}
			}
			int size;
			if (contacts_count < 5) {
				size = contacts_count;
			}
			else {
				size = 5;
			}
			for (int i = 0; i < size; i++) {
				if (top5[i].getViewCount() != 0) {
					output_file << "ID: " << top5[i].getId() << endl;
					output_file << "View Count: " << top5[i].getViewCount() << endl;
					output_file << contacts_list[i].getFirstName() << " " << contacts_list[i].getLastName() << ", " << contacts_list[i].getMobileNumber() << ", " <<
						contacts_list[i].getEmailAddress() << endl;
					output_file << contacts_list[i].getAddress()->getHouse() << ", " << contacts_list[i].getAddress()->getStreet() << ", " <<
						contacts_list[i].getAddress()->getCity() << ", " << contacts_list[i].getAddress()->getCountry() << endl;
					output_file << endl;
				}
			}
			delete[] top5;
		}
		cout << "Saved to File '" << file_name << "' Successfully." << endl;
		output_file.close();
	}
	else {
		system("cls");
		cout << "Invalid File Name!" << endl;
	}
}

Contact* ContactsBook::copyArray() const {
	Contact* temp = new Contact[size_of_contacts];
	for (int i = 0; i < size_of_contacts; i++) {		//copies contacts_list.
		temp[i] = *contacts_list[i].copyContact();
		temp[i].setId(contacts_list[i].getId());
		temp[i].setViewCount(contacts_list[i].getViewCount());
	}
	return temp;
}

bool ContactsBook::viewContact(int id) {		//view a specific contact.
	system("cls");
	for (int i = 0; i < contacts_count; i++) {
		if (contacts_list[i].getId() == id) {
			contacts_list[i].incrementViews();
			contacts_list[i].printContact();
			return true;
		}
	}
	return false;
}

bool ContactsBook::updateContact(int id, int choice) {		//update a contact's attribute.
	switch (choice) {
	case(1): {
		system("cls");
		string first_name;
		cout << "Enter New First Name: ";
		getline(cin, first_name);
		for (int i = 0; i < contacts_count; i++) {
			if (contacts_list[i].getId() == id) {
				contacts_list[i].setFirstName(first_name);
				return true;
			}
		}
		break;
	}
	case(2): {
		system("cls");
		string last_name;
		cout << "Enter New Last Name: ";
		getline(cin, last_name);
		for (int i = 0; i < contacts_count; i++) {
			if (contacts_list[i].getId() == id) {
				contacts_list[i].setLastName(last_name);
				return true;
			}
		}
		break;
	}
	case(3): {
		system("cls");
		string mobile_number;
		cout << "Enter New Mobile Number: ";
		getline(cin, mobile_number);
		for (int i = 0; i < contacts_count; i++) {
			if (contacts_list[i].getId() == id) {
				contacts_list[i].setMobileNumber(mobile_number);
				return true;
			}
		}
		break;
	}
	case(4): {
		system("cls");
		string email_address;
		cout << "Enter New Email Address: ";
		getline(cin, email_address);
		for (int i = 0; i < contacts_count; i++) {
			if (contacts_list[i].getId() == id) {
				contacts_list[i].setEmailAddress(email_address);
				return true;
			}
		}
		break;
	}
	case(5): {
		system("cls");
		string house;
		cout << "Enter New House: ";
		getline(cin, house);
		for (int i = 0; i < contacts_count; i++) {
			if (contacts_list[i].getId() == id) {
				contacts_list[i].getAddress()->setHouse(house);
				return true;
			}
		}
		break;
	}
	case(6): {
		system("cls");
		string street;
		cout << "Enter New Street: ";
		getline(cin, street);
		for (int i = 0; i < contacts_count; i++) {
			if (contacts_list[i].getId() == id) {
				contacts_list[i].getAddress()->setStreet(street);
				return true;
			}
		}
		break;
	}
	case(7): {
		system("cls");
		string city;
		cout << "Enter New City: ";
		getline(cin, city);
		for (int i = 0; i < contacts_count; i++) {
			if (contacts_list[i].getId() == id) {
				contacts_list[i].getAddress()->setCity(city);
				return true;
			}
		}
		break;
	}
	case(8): {
		system("cls");
		string country;
		cout << "Enter New Country: ";
		getline(cin, country);
		for (int i = 0; i < contacts_count; i++) {
			if (contacts_list[i].getId() == id) {
				contacts_list[i].getAddress()->setCountry(country);
				return true;
			}
		}
		break;
	}
	default:
		system("cls");
		cout << "Invalid Choice! Try Again." << endl;
		return false;
		break;
	}
}

void ContactsBook::deleteContact(int id) {			//delete contact.
	for (int i = 0; i < groups_count; i++) {
		if (groups.getArray()[i].hasContact(id)) {
			groups.getArray()[i].removeContact(id);
			break;
		}
	}
	for (int i = 0; i < contacts_count; i++) {
		if (contacts_list[i].getId() == id) {
			for (int j = i; j < contacts_count - 1; j++) {
				contacts_list[j] = contacts_list[j + 1];
			}
			contacts_list[contacts_count - 1] = Contact();
			contacts_count--;
		}
	}
}

/*-=-=-=-=-=(GROUPS)=-=-=-=-=-*/

void ContactsBook::createGroup(string name) {			//create a group.
	system("cls");
	groups.addItem(Group(name));
	groups.getArray()[groups_count].setId(groupCounter + 1);
	groupCounter++;
	groups_count++;
}

bool ContactsBook::displayGroups() const {			//display all groups.
	if (groups.getSize() != 0) {
		cout << "\033[1;31m-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "      Available Groups	 ||" << endl;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m" << endl;
		for (int i = 0; i < groups_count; i++) {
			cout << "ID: " << groups.getArray()[i].getId() << endl;
			cout << "Name: " << groups.getArray()[i].getName() << endl;
			if (i != groups_count - 1) {
				cout << endl;
			}
		}
		return true;
	}
	else {
		cout << "No Groups Available!" << endl;
		return false;
	}
}

void ContactsBook::addContactToGroup(int contact_id, int group_id) {		//add a contact to a group.
	bool duplicate = false;
	for (int i = 0; i < groups_count; i++) {
		if (groups.getArray()[i].getId() == group_id) {
			for (int j = 0; j < groups.getArray()[i].getContactIds().getSize(); j++) {
				if (contact_id == groups.getArray()[i].getContactIds().getArray()[j]) {
					duplicate = true;
					break;
				}
			}
		}
	}
	if (!duplicate) {
		for (int i = 0; i < groups_count; i++) {
			if (groups.getArray()[i].getId() == group_id) {
				groups.getArray()[i].addContact(contact_id);
				cout << "Contact Added Successfully." << endl;
				break;
			}
		}
	}
	else {
		cout << "Contact ID is already in Group." << endl;
	}
}

bool ContactsBook::displayGroupContacts(int group_id) const {		//display contacts of a group.
	system("cls");
	bool found = false;
	for (int i = 0; i < groups_count; i++) {
		for (int j = 0; j < groups.getArray()[i].getContactIds().getSize(); j++) {
			for (int k = 0; k < contacts_count; k++) {
				if (groups.getArray()[i].getContactIds().getArray()[j] == contacts_list[k].getId()) {
					found = true;
				}
			}
		}
	}
	if (found) {
		cout << "\033[1;31m-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "     Contacts in Group   ||" << endl;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m" << endl;
		for (int i = 0; i < groups_count; i++) {
			if (groups.getArray()[i].getId() == group_id) {
				for (int j = 0; j < groups.getArray()[i].getContactIds().getSize(); j++) {
					for (int k = 0; k < contacts_count; k++) {
						if (groups.getArray()[i].getContactIds().getArray()[j] == contacts_list[k].getId()) {
							contacts_list[k].printContact();
							cout << endl;
						}
					}
				}
			}
		}
		return found;
	}
	if (!found) {
		cout << "Group is empty!" << endl;
		return false;
	}
}

bool ContactsBook::removeContactFromGroup(int group_id, int contact_id) {		//remove a contact from a group.
	system("cls");
	bool found = false;
	for (int i = 0; i < groups_count; i++) {
		if (group_id == groups.getArray()[i].getId()) {
			for (int j = 0; j < groups.getArray()[i].getContactIds().getSize(); j++) {
				if (contact_id == groups.getArray()[i].getContactIds().getArray()[j]) {
					found = true;
				}
			}
		}
	}
	if (found) {
		for (int i = 0; i < groups_count; i++) {
			if (groups.getArray()[i].getId() == group_id) {
				groups.getArray()[i].removeContact(contact_id);
				return true;
			}
		}
	}
	return false;
}

void ContactsBook::viewContactGroups(int contact_id) const {			//view groups of a contact.
	system("cls");
	bool found = false;
	for (int i = 0; i < groups_count; i++) {
		if (groups.getArray()[i].hasContact(contact_id)) {
			found = true;
		}
	}
	if (found) {
		cout << "\033[1;31m-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "     Groups of Contact   ||" << endl;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m" << endl;
		for (int i = 0; i < groups_count; i++) {
			if (groups.getArray()[i].hasContact(contact_id)) {
				cout << "ID: " << groups.getArray()[i].getId() << endl;
				cout << "Name: " << groups.getArray()[i].getName() << endl;
				if (i != groups_count - 1) {
					cout << endl;
				}
			}
		}
	}
	else {
		cout << "Contact has No Groups!" << endl;
	}
}

bool ContactsBook::deleteGroup(int group_id) {			//delete a group.
	system("cls");
	if (group_id < 0) {
		return false;
	}
	for (int i = 0; i < groups_count; i++) {
		if (groups.getArray()[i].getId() == group_id) {
			groups.removeItem(groups.getArray()[i]);
			groups_count--;
			return true;
		}
	}
	return false;
}

/*-=-=-=-=-=(HISTORY)=-=-=-=-=-*/

void ContactsBook::addSearchToHistory(string search) {		//add a search query to history.
	history.addItem(HistoryObject(search));
}

void ContactsBook::viewSearchHistory() const {			//view search_history.
	if (history.getSize() != 0) {
		cout << "\033[1;31m-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "      Search History     ||" << endl;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m" << endl;
		int size = history.getSize();
		HistoryObject* sorted = new HistoryObject[size];
		for (int i = 0; i < size; i++) {
			sorted[i] = history.getArray()[i];
		}
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				if (sorted[j].getTimestamp() < sorted[j + 1].getTimestamp()) {
					HistoryObject temp = sorted[j];
					sorted[j] = sorted[j + 1];
					sorted[j + 1] = temp;
				}
			}
		}
		for (int i = 0; i < size; i++) {
			time_t t = sorted[i].getTimestamp();
			string time = ctime(&t);			//convert time into a string.
			cout << "'" << sorted[i].getSearch() << "' on " << time;
		}
		delete[] sorted;
	}
	else {
		cout << "No History Available!" << endl;
	}
}

bool ContactsBook::viewTop5() const {
	bool found = false;
	Contact* top5 = copyArray();
	for (int i = 0; i < contacts_count - 1; i++) {
		for (int j = 0; j < contacts_count - i - 1; j++) {
			if (top5[j].getViewCount() < top5[j + 1].getViewCount()) {
				swap(top5[j], top5[j + 1]);
			}
		}
	}
	int size;
	if (contacts_count < 5) {
		size = contacts_count;
	}
	else {
		size = 5;
	}
	for (int i = 0; i < size; i++) {
		if (top5[i].getViewCount() != 0) {
			cout << "Contact ID: " << top5[i].getId() << "    ||" << endl;
			cout << "View Count: " << top5[i].getViewCount() << "    ||" << endl;
			cout << "-=-=-=-=-=-=-=-=-=-" << endl;
			found = true;
		}
	}
	if (!found) {
		cout << "No Contacts Viewed!" << endl;
	}
	delete[] top5;
	return found;
}

bool ContactsBook::isValidContact(int contact_id) {
	for (int i = 0; i < contacts_count; i++) {
		if (contact_id == contacts_list[i].getId()) {
			return true;
		}
	}
	return false;
}

bool ContactsBook::isValidGroup(int group_id) {
	for (int i = 0; i < groups_count; i++) {
		if (group_id == groups.getArray()[i].getId()) {
			return true;
		}
	}
	return false;
}

ContactsBook::~ContactsBook() {			//destructor with memory deletion.
	delete[] contacts_list;
}