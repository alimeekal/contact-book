#include "Group.h"

Group::Group() {}       //default constructor.

Group::Group(string name) : name(name) {}       //parameterized constructor.

//setter.

void Group::setId(int id) {
    unique_id = id;
}

//getters.

int Group::getId() const {
    return unique_id;
}

string Group::getName() const {
    return name;
}

List<int>& Group::getContactIds() {
    return contact_ids;
}

void Group::addContact(int contact_id) {        //addContact function.
    contact_ids.addItem(contact_id);
}

void Group::removeContact(int contact_id) {     //removeContact function.
    contact_ids.removeItem(contact_id);
}

bool Group::hasContact(int contact_id) const {              //function to check if a group has a certain contact_id.
    for (int i = 0; i < contact_ids.getSize(); i++) {
        if (contact_ids.getArray()[i] == contact_id) {
            return true;
        }
    }
    return false;
}

bool Group::operator==(const Group& other) const {      //overloaded equality operator.
    return this->name == other.name;
}