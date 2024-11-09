#include "DSString.h"
#include <iostream>
#include <cstring> 

// This is the default constructor
DSString::DSString() : data(nullptr), len(0) {}

// The constructor from C-string
DSString::DSString(const char* str) {
    if (str) {
        len = 0;
        while (str[len] != '\0') {
            ++len;
        }
        data = new char[len + 1];
        for (size_t i = 0; i < len; ++i) {
            data[i] = str[i];
        }
        data[len] = '\0'; // Null-terminate the string
    } else {
        data = nullptr;
        len = 0;
    }
}

// The copy constructor
DSString::DSString(const DSString& other) : len(other.len) {
    data = new char[len + 1];
    for (size_t i = 0; i < len; ++i) {
        data[i] = other.data[i];
    }
    data[len] = '\0';
}

// The copy assignment operator
DSString& DSString::operator=(const DSString& other) {
    if (this != &other) {
        delete[] data; // Free existing memory

        len = other.len;
        data = new char[len + 1];
        for (size_t i = 0; i < len; ++i) {
            data[i] = other.data[i];
        }
        data[len] = '\0';
    }
    return *this;
}

// Destructor
DSString::~DSString() {
    delete[] data;
}

// Get length of the string
size_t DSString::length() const {
    return len;
}

// This is the operator for accessing characters
char& DSString::operator[](size_t index) {
    if (index >= len) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// The concatenation operator
DSString DSString::operator+(const DSString& other) const {
    DSString newString;
    newString.len = len + other.len;
    newString.data = new char[newString.len + 1];

    for (size_t i = 0; i < len; ++i) {
        newString.data[i] = data[i];
    }
    for (size_t i = 0; i < other.len; ++i) {
        newString.data[len + i] = other.data[i];
    }
    newString.data[newString.len] = '\0';
    return newString;
}

// Equality operator
bool DSString::operator==(const DSString& other) const {
    if (len != other.len) {
        return false;
    }
    for (size_t i = 0; i < len; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

// This is a less-than operator for comparison
bool DSString::operator<(const DSString& other) const {
    size_t minLength = (len < other.len) ? len : other.len;
    for (size_t i = 0; i < minLength; ++i) {
        if (data[i] < other.data[i]) {
            return true;
        } else if (data[i] > other.data[i]) {
            return false;
        }
    }
    return len < other.len;
}

// The substring method
DSString DSString::substring(size_t start, size_t numChars) const {
    if (start >= len || start + numChars > len) {
        throw std::out_of_range("Invalid substring range");
    }
    DSString sub;
    sub.len = numChars;
    sub.data = new char[numChars + 1];
    for (size_t i = 0; i < numChars; ++i) {
        sub.data[i] = data[start + i];
    }
    sub.data[numChars] = '\0';
    return sub;
}
