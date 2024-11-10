#include "DSString.h"

// Default constructor: creates an empty string
DSString::DSString() {
    data = new char[1];  // Allocate memory for null terminator
    data[0] = '\0';  // Null-terminate the string
    len = 0;  // Length is 0
}

// Constructor from a C-string
DSString::DSString(const char *str) {
    len = strlen(str);  // Set length
    data = new char[len + 1];  // Allocate memory
    data[len] = '\0';  // Null-terminate
    for (int i = 0; i < len; i++) {
        data[i] = str[i];  // Copy string data
    }
}

// Copy constructor: creates a copy of another DSString
DSString::DSString(const DSString &str) {
    len = str.len;
    data = new char[len + 1];  // Allocate memory
    data[len] = '\0';  // Null-terminate
    for (int i = 0; i < len; i++) {
        data[i] = str.data[i];  // Copy string data
    }
}

// Assignment operator: assigns one string to another
DSString & DSString::operator=(const DSString &str) {
    delete[] data;  // Free current memory
    len = str.len;
    data = new char[len + 1];  // Allocate new memory
    data[len] = '\0';  // Null-terminate
    for (int i = 0; i < len; i++) {
        data[i] = str.data[i];  // Copy string data
    }
    return *this;  // Return the current object
}

// Destructor: frees allocated memory
DSString::~DSString() {
    delete[] data;
}

// Returns the length of the string
size_t DSString::length() const {
    return len;
}

// Accesses individual characters
char & DSString::operator[](size_t i) {
    return data[i];
}

// Concatenates two strings and returns the result
DSString DSString::operator+(const DSString &str) const {
    char* newstr = new char[len + str.len + 1];  // Allocate memory
    newstr[len + str.len] = '\0';  // Null-terminate
    for (int i = 0; i < len; i++) {
        newstr[i] = data[i];  // Copy first string
    }
    for (int i = 0; i < str.len; i++) {
        newstr[len + i] = str.data[i];  // Copy second string
    }
    DSString final = newstr;  // Create final DSString
    delete[] newstr;  // Free temporary memory
    return final;
}

// Compares two strings for equality
bool DSString::operator==(const DSString &str) const {
    if (len != str.len) return false;  // Different lengths
    for (int i = 0; i < len; i++) {
        if (data[i] != str.data[i]) return false;  // Characters don't match
    }
    return true;  // Strings are equal
}

// Compares two strings lexicographically
bool DSString::operator<(const DSString &str) const {
    int i = 0;
    while (i < len && i < str.len) {
        if (data[i] < str.data[i]) return true;  // This string is smaller
        if (data[i] > str.data[i]) return false;  // This string is larger
        i++;
    }
    return len < str.len;  // Check for prefix case
}

// Returns a substring starting at 'start' with 'numChars' length
DSString DSString::substring(size_t start, size_t numChars) const {
    char* newstr = new char[numChars + 1];  // Allocate memory
    newstr[numChars] = '\0';  // Null-terminate
    for (int i = 0; i < numChars; i++) {
        newstr[i] = data[i + start];  // Copy substring
    }
    DSString final = newstr;  // Create final DSString
    delete[] newstr;  // Free temporary memory
    return final;
}

// Converts string to lowercase
DSString DSString::toLower() const {
    char* newstr = new char[len + 1];  // Allocate memory
    newstr[len] = '\0';  // Null-terminate
    for (int i = 0; i < len; i++) {
        newstr[i] = (data[i] >= 'A' && data[i] <= 'Z') ? data[i] + 32 : data[i];  // Convert to lowercase
    }
    DSString final = newstr;  // Create final DSString
    delete[] newstr;  // Free temporary memory
    return final;
}

// Returns the C-style string
const char * DSString::c_str() const {
    return data;
}

// Overloaded << operator to print DSString
std::ostream & operator<<(std::ostream &out, const DSString &str) {
    out << str.data;  // Output the string
    return out;
}
