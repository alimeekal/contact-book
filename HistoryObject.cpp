#include "HistoryObject.h"

HistoryObject::HistoryObject() {}       //default constructor.

HistoryObject::HistoryObject(string search) : search(search), timestamp(time(0)) {}     //parameterized constructor.

//getters.

string HistoryObject::getSearch() const {
    return search;
}

time_t HistoryObject::getTimestamp() const {
    return timestamp;
}