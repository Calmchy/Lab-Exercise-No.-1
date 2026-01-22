#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cstring>
#include <limits>

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
        mydata << stu->studentID << "\n";
        mydata << stu->surname << "\n";
        mydata << stu->firstname << "\n";
        mydata << stu->birthdate << "\n";
        mydata << stu->sex << "\n";
    }

    mydata.close();
}

void loadData() {
    ifstream mydata("sample.txt");

    while (true) {
        StudentInfo* student = new StudentInfo;

        mydata.getline(student->studentID, 20);
        if (mydata.fail()) { delete student; break; }

        mydata.getline(student->surname, 30);
        mydata.getline(student->firstname, 30);
        mydata.getline(student->birthdate, 15);
        mydata >> student->sex;
        mydata.ignore();

        students.push_back(student);
    }

    mydata.close();
}

void addData() {
    StudentInfo* student = new StudentInfo;

    const int labelW = 12;

    cout << "\nADD Record\n";
    cout << left;

    cout << setw(labelW) << "Student ID" << ": "; cin >> student->studentID;
    cout << setw(labelW) << "Surname" << ": "; cin >> student->surname;
    cout << setw(labelW) << "Firstname" << ": "; cin >> student->firstname;
    cout << setw(labelW) << "Birthdate" << ": "; cin >> student->birthdate;
    cout << setw(labelW) << "Sex" << ": "; cin >> student->sex;

    students.push_back(student);
}

void editData(int i) {
    i -= 1;

    if (i < 0 || i >= static_cast<int>(students.size())) {
        cout << "Invalid record number\n";
        return;
    }

    const int labelW = 12;
    const int valueW = 20;

    char temp[50];

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << left;

    cout << setw(labelW) << "Student ID" << ": " << setw(valueW) << students.at(i)->studentID << " -> ";
    cin.getline(temp, 20);
    if (strlen(temp) > 0) { strcpy(students.at(i)->studentID, temp); }

    cout << setw(labelW) << "Surname" << ": " << setw(valueW) << students.at(i)->surname << " -> ";
    cin.getline(temp, 30);
    if (strlen(temp) > 0) { strcpy(students.at(i)->surname, temp); }

    cout << setw(labelW) << "Firstname" << ": " << setw(valueW) << students.at(i)->firstname << " -> ";
    cin.getline(temp, 30);
    if (strlen(temp) > 0) { strcpy(students.at(i)->firstname, temp); }

    cout << setw(labelW) << "BirthDate" << ": " << setw(valueW) << students.at(i)->birthdate << " -> ";
    cin.getline(temp, 15);
    if (strlen(temp) > 0) { strcpy(students.at(i)->birthdate, temp); }

    cout << setw(labelW) << "Sex" << ": " << setw(valueW) << students.at(i)->sex << " -> ";
    cin.getline(temp, 2);
    if (strlen(temp) > 0) { students.at(i)->sex = temp[0]; }
}

void deleteData() {

}

int main() {
    char choice;
    int rec = 0;

    loadData();

    do {
        int count = 1;

        cout << left << setw(5)  << "Rec" << setw(15) << "Student ID" << setw(15) << "Surname" << setw(15) << "Firstname" << setw(15) << "BirthDate" << setw(5)  << "Sex" << endl;

        cout << string(70, '-') << endl;
        for (auto stu: students) {
            cout << left << setw(5)  << count++ << setw(15) << stu->studentID << setw(15) << stu->surname << setw(15) << stu->firstname << setw(15) << stu->birthdate << setw(5)  << stu->sex << endl;
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
                cout << "Choose record number: ";
                cin >> rec;
                editData(rec);
                break;
            case 'D':
                deleteData();
                if (choice)
                break;
            case 'S':
                break;
            case 'F':
                break;
            case 'V':
                saveData();
                break;
            case 'X':
                break;
        }
    } while (choice != 'X');

    return 0;
}