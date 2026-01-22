#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

struct StudentInfo {
    char studentID[20];
    char surname[30];
    char firstname[30];
    char civilStatus[15];
    char birthdate[15];
    char sex;
};

vector<StudentInfo*> students;


void saveData() {
    ofstream mydata("sample.txt");

    for (auto stu: students) {
        mydata << stu->studentID;
        mydata << stu->surname;
        mydata << stu->firstname;
        mydata << stu->birthdate;
        mydata << stu->sex;
    }

    mydata.close();
}

void loadData() {
    char stuid[20], surn[30], fn[30], bd[15], s;

    ifstream mydata("sample.txt");
    for (auto stu: students) {
        StudentInfo* student = new StudentInfo;
        mydata >> student->studentID;
        mydata >> student->surname;
        mydata >> student->firstname;
        mydata >> student->birthdate;
        mydata >> student->sex;
        students.push_back(student);
    }
}

void addData() {
    StudentInfo* student = new StudentInfo;
    cout << "ADD Record\n";
    cout << "Student ID: "; cin >> student->studentID;
    cout << "Surname : "; cin >> student->surname;
    cout << "Firstname: "; cin >> student->firstname;
    cout << "Birthdate: "; cin >> student->birthdate;
    cout << "Sex: "; cin >> student->sex;

    students.push_back(student);
}

void editData(int i) {
    students.at(i);

    cout << "Student ID: " << students.at(i)->studentID << " : "; cin >> students.at(i)->studentID;
    cout << "Surname: " << students.at(i)->surname << " : "; cin >> students.at(i)->surname;
    cout << "Firstname: " << students.at(i)->firstname << " : "; cin >> students.at(i)->firstname;
    cout << "BirthDate: " << students.at(i)->birthdate << " : "; cin >> students.at(i)->birthdate;
    cout << "Sex: " << students.at(i)->sex << " : "; cin >> students.at(i)->sex;

}

int main() {

    char choice;
    int rec = 0;

    do {
        int count = 1;

        cout << left
     << setw(5)  << "Rec"
     << setw(15) << "Student ID"
     << setw(15) << "Surname"
     << setw(15) << "Firstname"
     << setw(15) << "BirthDate"
     << setw(5)  << "Sex"
     << endl;

        cout << string(70, '-') << endl;
        for (auto stu: students) {
            cout << left
         << setw(5)  << count++
         << setw(15) << stu->studentID
         << setw(15) << stu->surname
         << setw(15) << stu->firstname
         << setw(15) << stu->birthdate
         << setw(5)  << stu->sex
         << endl;
        }
        

        cout << "[A]dd [E]dit [D]elete [S]ort [F]ilter sa[V]e e[X]it\n";
        while (true) {
            cout << "Enter: "; cin >> choice;
            
            if (!choice == 'A' || !choice == 'E' || !choice == 'D' || !choice == 'S' || !choice == 'F' || !choice == 'V' || !choice == 'X') {
                cout << "Invalid choice pls try again.\n";
            }
            break;
        }

        switch (choice) {
            case 'A':
                addData();
                break;
            case 'E':
                if (choice == 'E') {
                    cout << "Choose record number: ";
                    cin >> rec;
                    editData(rec);
                }
                break;
            case 'D':
                break;
            case 'S':
                break;
            case 'F':
                break;
            case 'V':
                break;
            case 'X':
                break;
        }
    } while (choice != 'X');

    return 0;
}