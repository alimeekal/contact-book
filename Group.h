#pragma once
#include "List.cpp"

#ifndef BASIC_LIB
#define BASIC_LIB
#include <iostream>         //basic libraries.
#include <string>
using namespace std;
#endif

class Group {
private:
    int unique_id;          //members.
    string name;
    List<int> contact_ids;
public:
    Group();            //headers.
    Group(string);

    int getId() const;
    string getName() const;

    void setId(int);

    void addContact(int);
    void removeContact(int);
    bool hasContact(int) const;

    bool operator==(const Group& other) const;
    List<int>& getContactIds();
};