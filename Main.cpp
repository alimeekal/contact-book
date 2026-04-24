#include "ContactsBook.h"

int main()
{
    int choice = 0;
    ContactsBook* contactsbook = nullptr;
    while (choice != 17) {
        system("cls");
        cout << "\033[1;31m-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
        cout << "       Contacts Book\t ||\n    23F-0574 Ali Meekal\t ||\n   23F-0535 Rayyan Asim\t ||\n";
        cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m" << endl;
        cout << "(1). Create Contacts List      \033[1;31m||\033[0m\n(2). Add New Contact\t       \033[1;31m||\033[0m\n(3). Merge Duplicates\t       \033[1;31m||\033[0m\n(4). Store to File\t       \033[1;31m||\033[0m\n"
            "(5). Load from File\t       \033[1;31m||\033[0m\n(6). Print Contacts Sorted     \033[1;31m||\033[0m\n(7). Print Contacts\t       \033[1;31m||\033[0m\n(8). Search Contacts\t       \033[1;31m||\033[0m\n"
            "(9). Display Count of Contacts \033[1;31m||\033[0m\n(10). Create a Group\t       \033[1;31m||\033[0m\n(11). Add a Contact to Group   \033[1;31m||\033[0m\n(12). Print Groups\t       \033[1;31m||\033[0m\n"
            "(13). View a Contact's Groups  \033[1;31m||\033[0m\n(14). Delete a Group\t       \033[1;31m||\033[0m\n(15). View Search History      \033[1;31m||\033[0m\n(16). View Top 5\t       \033[1;31m||\033[0m\n(17). Exit\t\t       \033[1;31m||\n";
        cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m" << endl;
        cout << "Choice: ";
        cin >> choice; cin.ignore();
        switch (choice) {
        case(1): {
            system("cls");
            if (contactsbook == nullptr) {
                int size;
                cout << "Enter Size of Contacts List: ";
                cin >> size; cin.ignore();
                if (size > 0) {
                    contactsbook = new ContactsBook(size);
                    contactsbook->loadFromFile("contacts_input.txt");
                    cout << "Contacts List Created Successfully." << endl;
                }
                else {
                    system("cls");
                    cout << "Invalid Size!" << endl;
                }
            }
            else {
                cout << "Contacts List already exists." << endl;
            }
            break;
        }
        case(2): {
            system("cls");
            if (contactsbook != nullptr) {
                Contact contact;
                cin >> contact;
                contactsbook->addContact(contact);
                contactsbook->saveToFile("contacts_output.txt");
                cout << "Contact Added Successfully." << endl;
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }
            break;
        }
        case(3): {
            system("cls");
            if (contactsbook != nullptr) {
                contactsbook->mergeDuplicates();
                contactsbook->saveToFile("contacts_output.txt");
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }
            break;
        }
        case(4): {
            system("cls");
            string file_name;
            if (contactsbook != nullptr) {
                cout << "Enter Filename to Store Contacts: ";
                getline(cin, file_name);
                system("cls");
                contactsbook->saveToFile(file_name);
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }
            break;
        }
        case(5): {
            system("cls");
            string file_name;
            if (contactsbook != nullptr) {
                cout << "Enter Filename to Load Contacts: ";
                cin >> file_name; cin.ignore();
                contactsbook->loadFromFile(file_name);
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }
            break;
        }
        case(6): {
            system("cls");
            string sortChoice;
            if (contactsbook != nullptr) {
                if (contactsbook->totalContacts() != 0) {
                    cout << "Sort by 'first_name' or 'last_name': ";
                    getline(cin, sortChoice);
                    contactsbook->printContactsSorted(sortChoice);
                }
                else {
                    cout << "Contacts List is Empty!" << endl;
                }
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }     
            break;
        }
        case(7): {
            system("cls");
            if (contactsbook != nullptr) {
                contactsbook->printContacts();
                if (contactsbook->totalContacts() > 0) {
                    int id, manage;
                    cout << "Enter Contact ID: ";
                    cin >> id; cin.ignore();
                    bool valid = contactsbook->viewContact(id);
                    if (valid) {
                        cout << "\033[1;31m-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
                        cout << "\tManagement\t ||" << endl;
                        cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m" << endl;
                        cout << "(1). Update Contact\t \033[1;31m||\033[0m\n(2). Delete Contact\t \033[1;31m||\033[0m\n(3). Exit\t\t \033[1;31m||\n";
                        cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m" << endl;
                        cout << "Choice: ";
                        cin >> manage; cin.ignore();
                        switch (manage) {
                        case(1): {
                            system("cls");
                            int choice; bool updated = false;
                            cout << "\033[1;31m-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
                            cout << "      Update Contact\t ||" << endl;
                            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m" << endl;
                            cout << "(1). First Name\t\t \033[1;31m||\033[0m\n(2). Last Name\t\t \033[1;31m||\033[0m\n(3). Mobile Number\t \033[1;31m||\033[0m\n(4). Email Address\t \033[1;31m||\033[0m\n(5). House\t\t \033[1;31m||\033[0m\n(6). Street\t\t \033[1;31m||\033[0m\n(7). City\t\t \033[1;31m||\033[0m\n(8). Country\t\t \033[1;31m||\n";
                            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m" << endl;
                            cout << "Choice: ";
                            cin >> choice; cin.ignore();
                            updated = contactsbook->updateContact(id, choice);
                            if (updated) {
                                system("cls");
                                contactsbook->saveToFile("contacts_output.txt");
                                cout << "Contact Updated Successfully." << endl;
                            }
                            break;
                        }
                        case(2): {
                            system("cls");
                            contactsbook->deleteContact(id);
                            contactsbook->saveToFile("contacts_output.txt");
                            cout << "Contact Deleted Successfully." << endl;
                            break;
                        }
                        case(3): {
                            system("cls");
                            cout << "Exiting..." << endl;
                            break;
                        }
                        default:
                            system("cls");
                            cout << "Invalid Choice! Try Again." << endl;
                            break;
                        }
                    }
                    else {
                        cout << "Invalid Contact ID!" << endl;
                    }
                }
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }
            break;
        }
        case(8): {
            system("cls");
            string search;
            if (contactsbook != nullptr) {
                cout << "Enter Search Query: ";
                getline(cin, search);
                contactsbook->searchContact(search);
                contactsbook->saveToFile("search_history.txt");
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }
            break;
        }
        case(9): {
            system("cls");
            if (contactsbook != nullptr) {
                cout << "Total Contacts: " << contactsbook->totalContacts() << endl;
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }
            break;
        }
        case(10): {
            system("cls");
            string group_name;
            if (contactsbook != nullptr) {
                cout << "Enter Group Name: ";
                getline(cin, group_name);
                contactsbook->createGroup(group_name);
                contactsbook->saveToFile("groups_output.txt");
                cout << "Group Created Successfully." << endl;
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }
            break;
        }
        case(11): {
            system("cls");
            int group_id, contact_id;
            bool valid = false;
            if (contactsbook != nullptr) {
                valid = contactsbook->displayGroups();
                if (valid) {
                    cout << endl;
                    cout << "Enter Group ID: ";
                    cin >> group_id; cin.ignore();
                    valid = contactsbook->isValidGroup(group_id);
                    if (valid) {
                        if (contactsbook->totalContacts() > 0) {
                        contactsbook->printContacts(); cout << endl;
                            cout << "Enter Contact ID: ";
                            cin >> contact_id; cin.ignore();
                            valid = contactsbook->isValidContact(contact_id);
                            if (valid) {
                                system("cls");
                                contactsbook->saveToFile("groups_output.txt");
                                contactsbook->addContactToGroup(contact_id, group_id);
                            }
                            else {
                                system("cls");
                                cout << "Invalid Contact ID!" << endl;
                            }
                        }
                        else {
                            system("cls");
                            cout << "Contacts List is Empty!" << endl;
                        }
                    }
                    else {
                        system("cls");
                        cout << "Invalid Group ID!" << endl;
                    }
                }
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }
            break;
        }
        case(12): {
            system("cls");
            int group_id, contact_id, choice;
            bool valid = false;
            if (contactsbook != nullptr) {
                valid = contactsbook->displayGroups();
                if (valid) {
                    cout << endl;
                    cout << "Enter Group ID: ";
                    cin >> group_id; cin.ignore();
                    valid = contactsbook->isValidGroup(group_id);
                    if (valid) {
                        valid = contactsbook->displayGroupContacts(group_id);
                        if (valid) {
                            cout << "\033[1;31m-=-=-=-=-=-=-=-=-=-=-=-\033[0m" << endl;
                            cout << "(1). Remove Contact  \033[1;31m||\033[0m\n(2). Exit\t     \033[1;31m||\n";
                            cout << "-=-=-=-=-=-=-=-=-=-=-=-\033[0m" << endl;
                            cout << "Choice: ";
                            cin >> choice; cin.ignore();
                            switch (choice) {
                            case(1): {
                                system("cls");
                                contactsbook->displayGroupContacts(group_id); cout << endl;
                                cout << "Enter Contact ID: ";
                                cin >> contact_id; cin.ignore();
                                valid = contactsbook->removeContactFromGroup(group_id, contact_id);
                                if (valid) {
                                    contactsbook->saveToFile("groups_output.txt");
                                    cout << "Contact Removed Successfully." << endl;
                                }
                                else {
                                    cout << "Invalid Contact ID!" << endl;
                                }
                                break;
                            }
                            case(2): {
                                system("cls");
                                cout << "Exiting..." << endl;
                                break;
                            }
                            default:
                                system("cls");
                                cout << "Invalid Choice! Try Again." << endl;
                                break;
                            }
                        }
                    }
                    else {
                        system("cls");
                        cout << "Invalid Group ID!" << endl;
                    }
                }
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }
            break;
        }
        case(13): {
            system("cls");
            int contact_id;
            bool valid = false;
            if (contactsbook != nullptr) {
                if (contactsbook->totalContacts() > 0) {
                    contactsbook->printContacts(); cout << endl;
                    cout << "Enter Contact ID: ";
                    cin >> contact_id; cin.ignore();
                    valid = contactsbook->isValidContact(contact_id);
                    if (valid) {
                        contactsbook->viewContactGroups(contact_id);
                    }
                    else {
                        system("cls");
                        cout << "Invalid Contact ID!" << endl;
                    }
                }
                else {
                    system("cls");
                    cout << "Contacts List is Empty!" << endl;
                }
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }
            break;
        }
        case(14): {
            system("cls");
            int group_id;
            bool valid = false;
            if (contactsbook != nullptr) {
                valid = contactsbook->displayGroups();
                if (valid) {
                    cout << endl;
                    cout << "Enter Group ID: ";
                    cin >> group_id; cin.ignore();
                    valid = contactsbook->deleteGroup(group_id);
                    if (valid) {
                        contactsbook->saveToFile("groups_output.txt");
                        cout << "Group Deleted Successfully." << endl;
                    }
                    else {
                        cout << "Invalid Group ID!" << endl;
                    }
                }
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }
            break;
        }
        case(15): {
            system("cls");
            if (contactsbook != nullptr) {
                contactsbook->viewSearchHistory();
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }
            break;
        }
        case(16): {
            system("cls");
            bool valid = false;
            if (contactsbook != nullptr) {
                valid = contactsbook->viewTop5();
                if (valid) {
                    contactsbook->saveToFile("frequently_searched.txt");
                }
            }
            else {
                cout << "Create a Contacts List First." << endl;
            }
            break;
        }
        case(17): {
            system("cls");
            if (contactsbook != nullptr) {
                contactsbook->saveToFile("contacts_output.txt");
                contactsbook->saveToFile("groups_output.txt");
                contactsbook->saveToFile("search_history.txt");
                contactsbook->saveToFile("frequently_searched.txt");
                delete contactsbook;
                contactsbook = nullptr;
            }
            cout << "Exiting..." << endl;
            break;
        }
        default:
            system("cls");
            cout << "Invalid Choice! Try Again." << endl;
            break;
        }
        system("pause");
    }
    return 0;
}