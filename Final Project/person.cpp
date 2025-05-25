#include "person.h"
#include "misc.h"
#include <iostream>
#include <utility>
#include <cctype>   
#include <ctime>    
using namespace std;

// three helper functions 
static std::string lower(std::string s)     // THe function lower the string
{
    for (char& c : s) c = std::tolower(static_cast<unsigned char>(c));
    return s;
}

static string first3(const string& phone)   // get the area code 
{
    string digits;
    for (char c : phone) if (isdigit(c)) digits += c;
    return digits.size() >= 3 ? digits.substr(0, 3) : "";
}

static int compute_age(const Date& b)   // compute the age from now
{
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    int yrs = (t->tm_year + 1900) - b.get_year();
    if ((t->tm_mon + 1) <  b.get_month() ||
        ((t->tm_mon + 1) == b.get_month() && t->tm_mday < b.get_day()))
        --yrs;
    return yrs;
}

Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){
    delete birthdate;
    delete email;
    delete phone;
    // TODO: complete the method!
}

Person::Person(string f_name, string l_name, string birthdate, string email, string phone){
    // TODO: Complete this method!
    // phone and email strings are in full version
    string type;
    this->f_name = f_name;
    this->l_name = l_name;
    this->birthdate = new Date(birthdate);
    for(int i = 0; i < email.length(); i++){
        if(email[i] == ')'){
            type = email.substr(1, i-1);
            email = email.substr(i+2);
            break;
        }
    }
    this->email = new Email(type, email);
    for(int i = 0; i < phone.length(); i++){
        if(phone[i] == ')'){
            type = phone.substr(1, i-1);
            phone = phone.substr(i+2);
            break;
        }
    }
    this->phone = new Phone(type, phone);
}

// create a new person constructor for wise search and phase 3 
Person::Person(const std::string& f,
    const std::string& l,
    const std::string& bdate,
    const std::string& emailLine,
    const std::string& phoneLine,
    const std::string& collegeLine,
    const std::string& majorLine,
    const std::string& zipLine)
{
// name and bod
f_name = f;
l_name = l;
birthdate = new Date(bdate);

// email address 
size_t p = emailLine.find(')');
string typ = emailLine.substr(1,p-1);
string addr= emailLine.substr(p+2);
email = new Email(typ, addr);
email_service = typ;

// parse the phone and area code 
p = phoneLine.find(')');
typ = phoneLine.substr(1,p-1);
std::string num = phoneLine.substr(p+2);          
phone = new Phone(typ, num);
area_code = first3(phone->get_contact());    

// get the student and zipcode information
college = collegeLine.substr(collegeLine.find(')')+2);
major   = majorLine.substr(majorLine.find(')')  +2);
zip_code= zipLine;

// get the age of the person
age = compute_age(*birthdate);
}


Person::Person(string filename){
    set_person(filename);
}


void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!

    string temp;
    string type;

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    getline(cin,f_name);

    cout << "Last Name: ";
    getline(cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    getline(cin,temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    // code here
    getline(cin, type);
    
    cout << "Email address: ";
    // code here
    getline(cin, temp);
    email = new Email(type, temp);

    cout << "Type of phone number: ";
    // code here
    getline(cin, type);
    cout << "Phone number: ";
    // code here
    // code here
    getline(cin, temp);
    phone = new Phone(type, temp);
}


void Person::set_person(string filename){
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
    // TODO: Complete this method!
    ifstream infile(filename);
    if (!infile.is_open()){
        cerr << "Error opening file!" << endl;
        return;
    }
    string type, fileline;
    getline(infile, fileline);
    f_name = fileline;
    getline(infile, fileline);
    l_name = fileline;
    getline(infile, fileline);
    birthdate = new Date(fileline);
    getline(infile,fileline);
    string myphone, mymail;
    for(int i = 0; i < fileline.length(); i++){
        if(fileline[i] == ')'){
            type = fileline.substr(1, i-1);
            myphone = fileline.substr(i+2);
            break;
        }
    }
    phone = new Phone(type, myphone);
    getline(infile, fileline);
    for(int i = 0; i < fileline.length(); i++){
        if(fileline[i] == ')'){
            type = fileline.substr(1, i-1);
            mymail = fileline.substr(i+2);
            break;
        }
    }
    email = new Email(type, mymail);
    cout << "College: ";
    getline(cin, college);
    cout << "Field of Study (Major): ";
    getline(cin, major);
    cout << "ZIP code: ";
    getline(cin, zip_code);

    area_code = first3(phone->get_contact("raw"));
    age       = compute_age(*birthdate);
    email_service = email->get_type();        // add a tiny getter in Email
}
   


bool Person::operator==(const Person& rhs){
    // TODO: Complete this method!
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)
    return (f_name == rhs.f_name && l_name == rhs.l_name && birthdate->get_month() == rhs.birthdate->get_month() && birthdate->get_day() == rhs.birthdate->get_day() && birthdate->get_year() == rhs.birthdate->get_year());
}

bool Person::operator!=(const Person& rhs){ 
    // TODO: Complete this method!
    return !(*this == rhs);
}


void Person::print_person(){
    // Already implemented for you! Do not change!
    cout << l_name <<", " << f_name << endl;
    birthdate->print_date("Month D, YYYY");
    cout << "Phone ";
    phone->print();
    cout << "Email ";
    email->print();
    for (int i = 0; i<myfriends.size(); i++){
        cout << codeName(myfriends[i]->f_name, myfriends[i]->l_name) << " (" << myfriends[i]->f_name << " " << myfriends[i]->l_name << ")" << endl;
    }
    cout << "College "   << college   << std::endl;
    cout << "Major "     << major     << std::endl;
    cout << "ZIP "       << zip_code  << std::endl;
    cout << "Age "       << age       << std::endl;
    cout << "Area Code " << area_code << std::endl;

}

void Person::makeFriend(Person* newfriend){
    for (int i =0; i<myfriends.size(); i++){
        if (newfriend==myfriends[i] || newfriend == nullptr){
            return;
        }
    }
    myfriends.push_back(newfriend);
}

void Person::print_friends (){
    vector<pair<string,Person*>> person_and_code;
    for (int i =0 ;i < myfriends.size(); i++){
        string individual_code = codeName (myfriends[i]->f_name, myfriends[i]->l_name);
        person_and_code.push_back({individual_code, myfriends[i]});
    }

    if (person_and_code.size()>1){ //only sort if there is more than one friend
        for (int i = 0; i < person_and_code.size()-1; i++){ //selection sort
            int current_min = i;
            for (int j = i+1; j<person_and_code.size(); j++){ 
                if (person_and_code[current_min].first.substr(0,2) > person_and_code[j].first.substr(0,2)){
                    current_min = j;
                }
            }
            pair<string,Person*> temp = person_and_code[current_min];
            person_and_code[current_min] = person_and_code[i];
            person_and_code[i] = temp;
        }

    }

    cout << f_name << ", " << l_name << endl;
    cout << "--------------------------------" << endl;

    for (int i =0; i<person_and_code.size(); i++){
        cout << person_and_code[i].second->f_name << ", " << person_and_code[i].second->l_name << endl;
    }
}

// for the wise function, to compare the user input field
std::string Person::getField(const std::string& field) const
{
    std::string f = lower(field);          // lower() already in this file

    if      (f == "first")   return f_name;
    else if (f == "last")    return l_name;
    else if (f == "college") return college;
    else if (f == "major")   return major;
    else if (f == "zip")     return zip_code;
    else if (f == "area")    return area_code;
    else if (f == "email")   return email->get_contact();
    else if (f == "phone")   return phone->get_contact();
    else if (f == "dob")     return birthdate->get_date();   
    return "";
}

