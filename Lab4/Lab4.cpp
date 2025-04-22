#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}
    virtual ~Person() {}

    virtual void displayInfo(ostream& out) 
    const = 0; 
    virtual void introduce(ostream& out) 
    const = 0; 

    void displayPersonInfo() const {
        cout << "Person: " << name << ", Age: " << age << endl;
    }

    string get_name() const { 
        return name; }
    int get_age() const { 
        return age; }
};

 
class Student : public Person {
    int studentID;
    double gpa;

public:
    Student(string n, int a, int id, double g) : Person(n, a), studentID(id), gpa(g) {}

    void displayInfo(ostream& out) const override { 
        out << "Student: " << name << ", Age: " << age
            << ", ID: " << studentID << ", GPA: " << gpa << endl;
    }

    void introduce(ostream& out) const override { 
        out << "I am a student. My name is " << name << "." << endl;
    }

    void displayStudentInfo() const { 
        displayPersonInfo(); 
        cout << "Student ID: " << studentID << ", GPA: " << gpa << endl;
    }
};

class StudentPrivate : private Person {
    int studentID;

public:
    StudentPrivate(string n, int a, int id) : Person(n, a), studentID(id) {}

    void displayStudentInfo() const { 
        displayPersonInfo();
        cout << "Student ID: " << studentID << endl;
    }
};

class Teacher : public Person {
    string subject;
    int experience;

public:
    Teacher(string n, int a, string s, int exp) : Person(n, a), subject(s), experience(exp) {}

    void displayInfo(ostream& out) const override { 
        out << "Teacher: " << name << ", Age: " << age
            << ", Subject: " << subject << ", Experience: " << experience << " years" << endl;
    }

    void introduce(ostream& out) const override { 
        out << "I am a teacher. My name is " << name << "." << endl;
    }
};

void processInputFile(const string& filename) {
    ifstream inputFile(filename); 

    int n;
    inputFile >> n;
    vector<Person*> persons;  
    vector<Student*> studentsPublic; 

    for (int i = 0; i < n; ++i) {
        string type, name;
        int age;
        inputFile >> type >> name >> age;

        if (type == "Student") {
            int id;
            double gpa;
            inputFile >> id >> gpa;
            Student* student = new Student(name, age, id, gpa);
            persons.push_back(student);
            studentsPublic.push_back(student);
        } else if (type == "Teacher") {
            string subject;
            int experience;
            inputFile >> subject >> experience;
            persons.push_back(new Teacher(name, age, subject, experience)); 
        }
    }
    inputFile.close();


    ofstream outputQ1("output_Q1.txt");
    for (int i = 0; i < studentsPublic.size(); i++) {
        outputQ1 << "Public Inheritance: Person: " << studentsPublic[i]->get_name()
                 << ", Age: " << studentsPublic[i]->get_age() << endl;
    }
    outputQ1.close();

    ofstream outputQ2("output_Q2.txt");
    for (int i = 0; i < persons.size(); i++) {
        persons[i]->displayInfo(outputQ2);
    }
    outputQ2.close();

    ofstream outputQ3("output_Q3.txt");
    for (int i = 0; i < persons.size(); i++) {
        persons[i]->introduce(outputQ3);
    }
    outputQ3.close();

    for (int i = 0; i < persons.size(); i++) {
        delete persons[i]; 
    }
}

int main() {
    processInputFile("input.txt");

    return 0;
}
