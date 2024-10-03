#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iterator>
using namespace std;

class Person {
public:
    int age;
    string name;

    void serialize(ofstream& ofs) {
        ofs.write((const char*)&age, sizeof(age)); // write age
        size_t nameLength = name.size(); // get the length of the string
        ofs.write((const char*)&nameLength, sizeof(nameLength)); // write length of name
        ofs.write(name.c_str(), nameLength); // write name itself
    }

    void deserialize(ifstream& ifs) {
        ifs.read((char*)&age, sizeof(age)); // read age
        size_t nameLength;
        ifs.read((char*)&nameLength, sizeof(nameLength)); // read length of name
        name.resize(nameLength); // resize the string
        ifs.read(&name[0], nameLength); // read name itself
    }

    friend ostream& operator<<(ostream& os, const Person& p) {
        os << "Name: " << p.name << "  Age: " << p.age;
        return os;
    }
};

class VirtualOperation {
public:
    VirtualOperation() {}
    virtual void operation() = 0; // Pure virtual function
    virtual ~VirtualOperation() {} // Virtual destructor for cleanup
    static vector<Person*> v; // Declaration of static member
};

// Definition of static member outside the class
vector<Person*> VirtualOperation::v;

class AddOperation : public VirtualOperation {
public:
    void operation() override { // Override the base class function
        Person* p = new Person;
        cout << "Please enter his/her age: ";
        cin >> p->age;
        cout << "Please enter his/her name: ";
        cin >> p->name;
        v.push_back(p); // Add the new Person object to the static vector
    }
};
class DelOperation :public VirtualOperation
{
public:
    void operation()override {
        cout << "please enter his/her name" << endl;
        string enter_name;
        cin >> enter_name;
        int flag = 0;
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i]->name == enter_name)
            {
                v.erase(v.begin()+i);
                cout << "remove successfully" << endl;
                flag = 1;
            }
        }
        if (flag == 0)
        {
            cout << "no this one" << endl;
        }
    }
};
class ShowOperation : public VirtualOperation {
public:
    void operation() override { // Override the base class function
        for (Person* it : v) {
            cout << (*it) << endl; // Print each Person in the vector
        }
    }
};
class ExitOperation :public VirtualOperation
{
public:
    void operation() override {
        cout << "Exit successfully" << endl;

    }
};
void menu() {
    cout << "*********0.exit***********" << endl;
    cout << "*********1.add************" << endl;
    cout << "*********2.del************" << endl;
    cout << "*********3.display*********" << endl; // Changed to 'display' for clarity
}

int main() {
    int input = 0;
    vector<VirtualOperation*> operations; // To hold operations
    operations.push_back(new ExitOperation());
    operations.push_back(new AddOperation);
    operations.push_back(new DelOperation);
    operations.push_back(new ShowOperation);
    ifstream ifs("E:\\gitcode\\3.cpp\\14review\\14review\\file1.txt", ios::in || ios::binary);
    if (ifs.is_open())
    {
        size_t lenatb;
        ifs.read((char*)&lenatb, sizeof(size_t));
        for (int i = 0; i < lenatb; i++)
        {
            Person* p = new Person;
            p->deserialize(ifs);
            VirtualOperation::v.push_back(p);
        }
        ifs.close();
    }
    do {
        menu();
        cout << "Please enter an option: ";
        cin >> input;
        if (input <= 3 && input >= 0)
        {
            operations[input]->operation();
        }
        else
        {
            cout << "please enter a valid one" << endl;
        }
    } while (input != 0);

    // Clean up dynamically allocated objects
    for (VirtualOperation* op : operations) {
        delete op;
    }
    ofstream ofs("E:\\gitcode\\3.cpp\\14review\\14review\\file1.txt", ios::out | ios::binary);
    size_t lenate = VirtualOperation::v.size();
    ofs.write((const char*)&lenate, sizeof(size_t));
    for (Person* it : VirtualOperation::v)
    {
        it->serialize(ofs);
        delete it;
    }
    ofs.close();
    return 0;
} 