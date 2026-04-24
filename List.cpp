#include "List.h"

template <typename T>
List<T>::List() : count(0), size(1) {
    arr = new T[size];                  //default constructor.
}

template <typename T>
void List<T>::addItem(T item) {
    if (count == size) {
        size = size * 2;
        T* newArr = new T[size];
        for (int i = 0; i < count; i++) {       //addItem function.
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
    arr[count] = item;
    count++;
}

template <typename T>
void List<T>::removeItem(T item) {
    int index = -1;
    for (int i = 0; i < count; i++) {       //removeItem function.
        if (arr[i] == item) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        for (int i = index; i < count - 1; i++) {
            arr[i] = arr[i + 1];
        }
        arr[count - 1] = T();
        count--;
    }
}

//getters.

template <typename T>
int List<T>::getSize() const {
    return count;
}

template <typename T>
T* List<T>::getArray() const {
    return arr;
}

template <typename T>
List<T>::List(const List<T>& other) : count(other.count), size(other.size) {        //copy constructor.
    arr = new T[size];
    for (int i = 0; i < count; i++) {
        arr[i] = other.arr[i];
    }
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {         //overloaded assignment operator.
    if (this != &other) {
        delete[] arr;
        count = other.count;
        size = other.size;
        arr = new T[size];
        for (int i = 0; i < count; i++) {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

template <typename T>
List<T>::~List() {          //destructor with memory deletion.
    delete[] arr;
}