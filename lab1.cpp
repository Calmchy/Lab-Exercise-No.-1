#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cstring>
#include <limits>

using namespace std;

struct StudentInfo {
    string studentID;
    string surname;
    string firstname;
    string birthdate;
    char sex;
};

vector<StudentInfo*> students;

void saveData() {
    ofstream file("sample.txt");
    for (auto s : students) {
        file << s->studentID << "|"
             << s->surname << "|"
             << s->firstname << "|"
             << s->birthdate << "|"
             << s->sex << "\n";
    }
    file.close();
}

void loadData() {
    ifstream file("sample.txt");
    string line;

    while (getline(file, line)) {
        StudentInfo* s = new StudentInfo;
        stringstream ss(line);

        getline(ss, s->studentID, '|');
        getline(ss, s->surname, '|');
        getline(ss, s->firstname, '|');
        getline(ss, s->birthdate, '|');
        ss >> s->sex;

        students.push_back(s);
    }
    file.close();
}

void buffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string validationInput(string text, int sLimit) {
    string input;

    while (true) {
        cout << setw(12) << text << ": ";
        getline(cin, input);

        if (input.empty()) {
            cout << "Input cannot be empty. Try again.\n";
        }
        else if (input.length() > sLimit) {
            cout << text << " is limited to " << sLimit << " characters. Try again.\n";
        }
        else {
            return input;
        }
    }
}

char validationInput2(string text) {
    char input;

    while (true) {
        cout << setw(12) << text << ": ";
        cin >> input;
        input = toupper(input);

        if (input == 'M' || input == 'F') {
            buffer();
            return input;
        }

        cout << "Only accept M or F! Please try again.\n";
        buffer();
    }
}

void addData() {
    StudentInfo* student = new StudentInfo;

    const int labelW = 12;

    cout << "\nADD Record\n";
    cout << left;

    student->studentID = validationInput("Student ID", 10);
    student->surname = validationInput("Surname", 20);
    student->firstname = validationInput("Firstname", 20);
    student->birthdate = validationInput("Birthdate", 8);
    student->sex = validationInput2("Sex");

    students.push_back(student);
}

string validationInput3(string text, int sLimit, string old) {
    string newInput;

    while (true) {
        cout << setw(12) << text << ": ";
        getline(cin, newInput);

        if (newInput.length() > sLimit) {
            cout << text << " is limited to " << sLimit << " characters. Try again.\n";
        }
        else if (!newInput.empty()) {
            return newInput;
        }
        else {
            return old;
        }
    }
}

char validationInput4(string text, char old) {
    string newInput;
    while (true) {
        cout << setw(12) << text << ": ";
        getline(cin, newInput);

        if (newInput.empty()) {
            return old;
        }
        else if (toupper(newInput[0]) == 'M' || toupper(newInput[0]) == 'F') {
            return toupper(newInput[0]);
        }
        cout << "Only accept M or F! Please try again.\n";
    }
}

void editData() {
    int rec;
    cout << "Choose record number: ";
    cin >> rec;
    rec--;

    if (rec < 0 || rec >= static_cast<int>(students.size())) {
        cout << "Invalid record number\n";
        return;
    }

    buffer();

    string input;

    cout << "\n(Press ENTER to keep current value)\n\n";

    students[rec]->studentID = validationInput3("Student ID", 10, students[rec]->studentID);
    students[rec]->surname = validationInput3("Surname", 20, students[rec]->surname);
    students[rec]->firstname = validationInput3("Firstname", 20, students[rec]->firstname);
    students[rec]->birthdate = validationInput3("Birthdate", 8, students[rec]->birthdate);
    students[rec]->sex = validationInput4("Sex", students[rec]->sex);
}


void deleteData() {
    int rec;
    cout << "Enter record number to delete: ";
    cin >> rec;
    rec -= 1;

    if (rec < 0 || rec >= static_cast<int>(students.size())) {
        cout << "Invalid record\n";
        return;
    }

    delete students[rec];
    students.erase(students.begin() + rec);
}

void sortData() {
    if (students.empty()) {
        cout << "No records to sort.\n";
        return;
    }

    char choice;
    cout << "\nSort by Surname\n";

    while (true) {
        cout << "[A]scending | [D]escending: ";
        cin >> choice;
        buffer();

        choice = toupper(choice);

        if (choice != 'A' && choice != 'D') {
            cout << "Only accept A or D! Please try again.\n";
        }
        else {
            break;
        }
    }

    sort(students.begin(), students.end(),
        [choice](StudentInfo* a, StudentInfo* b) {
            if (choice == 'A')
                return a->surname < b->surname;
            else
                return a->surname > b->surname;
        });

    cout << "Records sorted successfully.\n";
}

void filterData() {
    char choice;
    cout << "\nFilter by Sex\n";

    while (true) {
        cout << "[M]ale | [F]emale | [A]ll: ";
        cin >> choice;

        choice = toupper(choice);

        if (choice != 'M' && choice != 'F' && choice != 'A') {
            cout << "Only accept M, F or A! Please try again.\n";
        }
        else {
            break;
        }
    }

    int count = 1;

    cout << left << setw(5)  << "Rec" << setw(15) << "Student ID" << setw(15) << "Surname" << setw(15) << "Firstname" << setw(15) << "BirthDate" << setw(5)  << "Sex" << endl;

    cout << string(70, '-') << endl;

    for (auto s : students) {
        if (choice == 'A' || s->sex == choice) {
            cout << left << setw(5)  << count++ << setw(15) << s->studentID << setw(15) << s->surname << setw(15) << s->firstname << setw(15) << s->birthdate << setw(5)  << s->sex << endl;
        }
    }
}

int main() {
    char choice;
    int rec = 0;

    loadData();

    do {
        int count = 1;
        cout << "Active File : [sample.txt]\n\n";
        cout << string(70, '-') << "\n";
        cout << left << setw(5)  << "\nRec" << setw(15) << "Student ID" << setw(15) << "Surname" << setw(15) << "Firstname" << setw(15) << "BirthDate" << setw(5)  << "Sex" << "\n\n";

        cout << string(70, '-') << "\n\n";
        for (auto stu: students) {
            cout << left << setw(5)  << count++ << setw(15) << stu->studentID << setw(15) << stu->surname << setw(15) << stu->firstname << setw(15) << stu->birthdate << setw(5)  << stu->sex << endl;
        }
        

        cout << "[A]dd [E]dit [D]elete [S]ort [F]ilter sa[V]e e[X]it\n";
        while (true) {
            cout << "Enter: "; cin >> choice; buffer();

            choice = toupper(choice);
            
            if (choice != 'A' && choice != 'E' && choice != 'D' && choice != 'S' && choice != 'F' && choice != 'V' && choice != 'X') {
                cout << "Invalid choice pls try again.\n";
                continue;
            }
            break;
        }

        switch (choice) {
            case 'A':
                addData();
                break;
            case 'E':
                editData();
                break;
            case 'D':
                deleteData();
                if (choice)
                break;
            case 'S':
                sortData();
                break;
            case 'F':
                filterData();
                break;
            case 'V':
                saveData();
                break;
            case 'X':
                break;
        }
    } while (choice != 'X');

    for (auto stu : students) {
        delete stu;
    }
    students.clear();

    return 0;
}