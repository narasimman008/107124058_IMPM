#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Student {
    string regNo;
    string name;
    string cse1001;
    string cse1002;
    string proctorId;
};

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream infile("Example.txt");
    Student s;

    while (infile >> s.regNo >> s.name >> s.cse1001 >> s.cse1002 >> s.proctorId) {
        students.push_back(s);
    }

    return students;
}

void saveStudents(const vector<Student>& students) {
    ofstream outfile("Example.txt");
    for (const auto& s : students) {
        outfile << s.regNo << "\t"
                << s.name << "\t"
                << s.cse1001 << "\t"
                << s.cse1002 << "\t"
                << s.proctorId << endl;
    }
}

void addStudents(vector<Student>& students) {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Student s;
        cout << "Enter registration number: ";
        cin >> s.regNo;

        cout << "Enter name: ";
        cin.ignore();
        getline(cin, s.name);

        s.cse1001 = "00";
        s.cse1002 = "00";

        cout << "Enter proctor ID: ";
        cin >> s.proctorId;

        students.push_back(s);
    }

    saveStudents(students);
}

void studentLogin(const vector<Student>& students) {
    string reg;
    cout << "Enter your registration number: ";
    cin >> reg;

    for (const auto& s : students) {
        if (s.regNo == reg) {
            cout << "\nRegistration Number: " << s.regNo << endl;
            cout << "Name: " << s.name << endl;
            cout << "CSE1001 Mark: " << s.cse1001 << endl;
            cout << "CSE1002 Mark: " << s.cse1002 << endl;
            cout << "Proctor ID: " << s.proctorId << endl;
            return;
        }
    }

    cout << "No such registration number found!" << endl;
}

void facultyLogin(vector<Student>& students) {
    string subcode;
    cout << "Enter your subject code: ";
    cin >> subcode;

    int option;
    cout << "\n1. Add marks\n2. View marks\nEnter option: ";
    cin >> option;

    if (option == 1) {
        for (auto& s : students) {
            cout << "Enter mark for " << s.regNo << " : ";
            string mark;
            cin >> mark;

            if (subcode == "CSE1001") s.cse1001 = mark;
            else if (subcode == "CSE1002") s.cse1002 = mark;
            else {
                cout << "Invalid subject code!" << endl;
                return;
            }
        }
        saveStudents(students);
    }

    else if (option == 2) {
        cout << "Registration Number - Marks\n\n";
        for (const auto& s : students) {
            if (subcode == "CSE1001")
                cout << s.regNo << " - " << s.cse1001 << endl;
            else if (subcode == "CSE1002")
                cout << s.regNo << " - " << s.cse1002 << endl;
            else {
                cout << "Invalid subject code!" << endl;
                return;
            }
        }
    }
}

void proctorLogin(const vector<Student>& students) {
    string procId;
    cout << "Enter your proctor ID: ";
    cin >> procId;

    bool found = false;

    for (const auto& s : students) {
        if (s.proctorId == procId) {
            cout << "\nRegistration Number: " << s.regNo << endl;
            cout << "Name: " << s.name << endl;
            cout << "CSE1001 Mark: " << s.cse1001 << endl;
            cout << "CSE1002 Mark: " << s.cse1002 << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No such proctor ID found!" << endl;
    }
}

void adminView(const vector<Student>& students) {
    string password;
    cout << "Enter admin password: ";
    cin >> password;

    if (password == "admin") {
        cout << "\nReg No\tName\tCSE1001\tCSE1002\tProctor ID\n";
        for (const auto& s : students) {
            cout << s.regNo << "\t"
                 << s.name << "\t"
                 << s.cse1001 << "\t"
                 << s.cse1002 << "\t"
                 << s.proctorId << endl;
        }
    } else {
        cout << "Incorrect password!" << endl;
    }
}

int main() {
    vector<Student> students = loadStudents();
    int option = 0;

    while (option != 6) {
        cout << "\nAvailable operations:\n";
        cout << "1. Add New Students\n";
        cout << "2. Student Login\n";
        cout << "3. Faculty Login\n";
        cout << "4. Proctor Login\n";
        cout << "5. Admin View\n";
        cout << "6. Exit\n";
        cout << "Enter option: ";
        cin >> option;

        switch (option) {
            case 1: addStudents(students); break;
            case 2: studentLogin(students); break;
            case 3: facultyLogin(students); break;
            case 4: proctorLogin(students); break;
            case 5: adminView(students); break;
            case 6: cout << "Exiting program...\n"; break;
            default: cout << "Invalid option!\n";
        }
    }

    return 0;
}

