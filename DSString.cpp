#include "DSString.h"
#include <iostream>
#include <vector>

using namespace std; 

// This is the default constructor
DSString::DSString() : data(nullptr), len(0) {}

// The constructor from C-string
DSString::DSString(const char* str) {
    if (str) {
        len = 0;
        // calculating the length of the C-string
        while (str[len] != '\0') {
            ++len;
        }
        data = new char[len + 1];
        // copying the characters from the C-string
        for (size_t i = 0; i < len; ++i) {
            data[i] = str[i];
        }
        data[len] = '\0'; 
    } else {
        data = nullptr;
        len = 0;
    }
}

// The copy constructor
DSString::DSString(const DSString& other) : len(other.len) {
    data = new char[len + 1];
    // copying the characters from the other string
    for (size_t i = 0; i < len; ++i) {
        data[i] = other.data[i];
    }
    data[len] = '\0';
}

// The copy assignment operator
DSString& DSString::operator=(const DSString& other) {
    if (this != &other) {
        delete[] data; // Freeing existing memory
        len = other.len;
        // Allocating new memory for the copied string
        data = new char[len + 1];
        // Copying each character from the other string
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
        throw out_of_range("Index out of range");
    }
    return data[index];
}

// The concatenation operator
DSString DSString::operator+(const DSString& other) const {
    DSString newString;
    newString.len = len + other.len;
    newString.data = new char[newString.len + 1];

    // copy the current string
    for (size_t i = 0; i < len; ++i) {
        newString.data[i] = data[i];
    }
    // Now append the other string
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
    //comparing each character in the strings
    for (size_t i = 0; i < len; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

// This is the less-than operator used for comparison
bool DSString::operator<(const DSString& other) const {
    size_t minLength = (len < other.len) ? len : other.len;
    // Comparing characters up to the length of the shorter string
    for (size_t i = 0; i < minLength; ++i) {
        if (data[i] < other.data[i]) {
            return true;
        } else if (data[i] > other.data[i]) {
            return false;
        }
    }
    return len < other.len; // If all fo the characters are equal then the shorter string would be the one considered less
}

// The substring method
DSString DSString::substring(size_t start, size_t numChars) const {
    //checking for the out of bounds range
    if (start >= len || start + numChars > len) {
        throw out_of_range("Invalid substring range");
    }
    //creating new DSS string to hold the substring
    DSString sub;
    sub.len = numChars;
    // allocating memory for the substring
    sub.data = new char[numChars + 1];
    // Manually copying characters from the original string to the new substring
    for (size_t i = 0; i < numChars; ++i) {
        sub.data[i] = data[start + i];
    }
    sub.data[numChars] = '\0'; 
    return sub;
}

// Stream insertion operator implementation
ostream& operator<<(ostream& out, const DSString& str) {
    out << str.c_str();
    return out;
}

// This c_str function returns a pointer to the null-terminated C-string
const char* DSString::c_str() const {
    return data;
}

// Tokenize the string into words based on the delimiter
vector<DSString> DSString::tokenize(const char delimiter) const {
    vector<DSString> tokens;
    size_t start = 0; // Starting at the index of a new token

    for (size_t i = 0; i < len; ++i) {
        if (data[i] == delimiter) {
            // If a delimiter is found and the token length is > 0, this creates a substring
            if (i > start) {
                tokens.push_back(this->substring(start, i - start));
            }
            // now we move the starting index to the character after the delimiter
            start = i + 1;
        }
    }

    // adds the last token if there are remaining characters after the last delimiter
    if (start < len) {
        tokens.push_back(this->substring(start, len - start));
    }

    return tokens;
}

void DSString::getline(istream& is, char delimiter) {
    // clear any previous data
    delete[] data;

    // Initialize variables to track size and capacity
    size_t size = 0;
    size_t capacity = 1000;  // this is my starting capacity
    data = new char[capacity];

    char ch;
    // now we read characters from the input stream until the delimiter is encountered
    while (is.get(ch) && ch != delimiter) {
        // If the buffer is full, increase its capacity
        if (size + 1 >= capacity) {
            capacity *= 2;  // Double the capacity
            char* newData = new char[capacity];
            // Copy the old data to the new buffer
            for (size_t i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        // this adds the charactert to the data array
        data[size++] = ch;
    }
    data[size] = '\0';
    len = size;
}
