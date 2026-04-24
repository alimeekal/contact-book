#pragma once

#ifndef BASIC_LIB
#define BASIC_LIB
#include <iostream>     //basic libraries.
#include <string>
using namespace std;
#endif

template <typename T>       //template class.
class List {
private:
    T* arr;
    int count;      //members.
    int size;

public:
    List();         //headers.

    void addItem(T);
    void removeItem(T);

    int getSize() const;
    T* getArray() const;

    ~List();
   
    List(const List<T>&);
    List<T>& operator=(const List<T>&);
};