#pragma once
#include "Contact.h"
#include "Group.h"
#include "HistoryObject.h"

#ifndef BASIC_LIB
#define BASIC_LIB
#include <iostream>			//basic libraries.
#include <string>
#include<iomanip>
using namespace std;
#endif

class ContactsBook {
private:		//members.
	List<Group> groups;				//groups List to manage groups.
	List<HistoryObject> history;	//history List to manage history.
	Contact* contacts_list;			//contacts_list to manage contacts.
	int size_of_contacts;
	int contacts_count;
	int groups_count;
	static int contactCounter;
	static int groupCounter;
public:
	ContactsBook();			//headers.
	ContactsBook(int);

	bool full() const;
	void resizeList();

	void addContact(const Contact&);
	int totalContacts() const;
	int totalGroups() const;

	Contact* copyArray() const;

	void searchContact(string);
	bool searchCharacter(string, string) const;

	void sortContactsList(Contact*, string) const;

	void printContacts() const;
	void printContactsSorted(string);
	void mergeDuplicates();

	bool viewContact(int);
	bool updateContact(int, int);
	void deleteContact(int);

	void loadFromFile(string);
	void saveToFile(string);

	void createGroup(string);
	void addContactToGroup(int, int);
	bool removeContactFromGroup(int, int);
	void viewContactGroups(int) const;
	bool deleteGroup(int);
	bool displayGroups() const;
	bool displayGroupContacts(int) const;

	void addSearchToHistory(string);
	void viewSearchHistory() const;
	bool viewTop5() const;

	ContactsBook(const ContactsBook&);
	ContactsBook& operator=(const ContactsBook&);

	bool isValidContact(int);
	bool isValidGroup(int);

	~ContactsBook();
};