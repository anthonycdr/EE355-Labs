
#ifndef PERSON_H
#define PERSON_H

#include "date.h"
#include "contact.h"
#include "fstream"
#include <string>
#include <vector>

using namespace std;

class Person{
    friend class Network;

private:
    std::string f_name;
    std::string l_name;
    Date *birthdate;
    Email *email;
    Phone *phone;
    // the following to attributes are used in the linked list.
    Person* next;
    Person* prev;
    std::vector<Person*> myfriends;

    string college;        // “USC”
    string major;          // “Electrical Engineering”
    string zip_code;       // 5‑digit ZIP
    int    age   = 0;      // computed once at construction
    string area_code;      // first 3 digits of phone number
    string email_service;  // “Gmail”, “Yahoo”, “Official”

public: 
    Person();
    ~Person();
    Person(std::string filename);
    Person(std::string f_name, std::string l_name, std::string birthdate, std::string email, std::string phone);
    Person(const std::string& f,
        const std::string& l,
        const std::string& bdate,
        const std::string& emailLine,
        const std::string& phoneLine,
        const std::string& collegeLine,
        const std::string& majorLine,
        const std::string& zipLine);
	void print_person();
	void set_person();
	void set_person(std::string filename);
    bool operator==(const Person& rhs);
    bool operator!=(const Person& rhs);
    void makeFriend(Person* newfriend);
    void print_friends();
    int get_age()   const { return age; }
    string get_area()  const { return area_code; }
    string get_school()const { return college; }
    string get_major() const { return major; }
    string get_zip()   const { return zip_code; }
    string getField(const std::string& field) const;

};


#endif
