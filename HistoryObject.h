#pragma once

#ifndef BASIC_LIB
#define BASIC_LIB
#include <iostream>     //basic libraries.
#include <string>
using namespace std;
#endif
#include <ctime>        //ctime for obtaining current date & time.

class HistoryObject {
private:
    string search;      //members.
    time_t timestamp;
public:
    HistoryObject();        //headers.
    HistoryObject(string);

    string getSearch() const;
    time_t getTimestamp() const;
};