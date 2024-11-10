
#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>
#include <cstring>

class DSString
{

private:
 //a pointer that points to a character array with a '\0' terminator
    char *data;
 //length of the string
    size_t len;
    // Note: we keep the terminator only so we can return a c-string version in function c_str().

public:

    DSString();
 //constructor that takes an inputted char and declares our own string
    DSString(const char *);

    // Rule of three: copy constructor, copy assignment, and destructor (to delete the allocated memory)
 //shallow copy is default while deep copy copies entire
    DSString(const DSString &);         //constructor
    DSString &operator=(const DSString &);  //copy assignment
    ~DSString();      //destructor

    //returns length of the string
    size_t length() const;

    //returns a reference to character at index
    char &operator[](size_t);


   //combining the two strings, one being from the argument
    DSString operator+(const DSString &) const;


    bool operator==(const DSString &) const; //making the two strings equal and passing the equaled value
    bool operator<(const DSString &) const; //alphabetical organized



 //first parameter, the start index of the string you want to remove from main string (substring)
 //and second is the length of the substring returned
   DSString substring(size_t start, size_t numChars) const;

    DSString toLower() const; //lowercase


    const char *c_str() const; //returning data ex. string is a array of char AKA c-string


 //friends passes through the ostream and string and lets us use the cout operator now
    friend std::ostream &operator<<(std::ostream &, const DSString &);  //cout a string or outputting to a file

};

#endif