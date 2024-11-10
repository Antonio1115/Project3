
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


public:

    DSString();
 //constructor that takes an inputted char and declares our own string
    DSString(const char *);

    // Rule of three: copy constructor, copy assignment, and destructor (to delete the allocated memory)
 
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
    bool operator<(const DSString &) const; //this makes them alphabetically organized

   DSString substring(size_t start, size_t numChars) const;

    DSString toLower() const; //makes them lowercase

    const char *c_str() const; //returning data

    friend std::ostream &operator<<(std::ostream &, const DSString &);  

};

#endif