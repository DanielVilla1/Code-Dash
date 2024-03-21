#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name, course;
    int age;
    double grade;
    Student* next = nullptr;
    Student* prev = nullptr;
};

struct StudentList {
    Student* head = nullptr;
    Student* tail = nullptr;
};

void MainMenu(int&);
void GetInfo(StudentList&);
void StudentLists(const StudentList&);
double CalculateStudentGrade(const StudentList&);
void DeleteStudent(StudentList&);
void DeleteHistory(StudentList&);
bool Continue(int&);

int main() {
    int option = 0;
    StudentList studentList;
    MainMenu(option);


    do {
        if (option == 1) {
            system("cls");
            GetInfo(studentList);
        }
        else if (option == 2) {
            if (studentList.head != nullptr) {
                system("pause");
                system("cls");
                StudentLists(studentList);
            }
            else {
                system("cls");
                cout << "No lists Yet!\n";
                system("pause");
                system("cls");
            }
        }
        else if (option == 3) {
            if (studentList.head != nullptr) {
                system("cls");
                cout << "All Students Average Grade: " << CalculateStudentGrade(studentList) << "\n";
                system("pause");
                system("cls");
            }
            else {
                system("cls");
                cout << "No students to calculate average!\n";
                system("pause");
                system("cls");
            }
        }
        else if (option == 4) {
            if (studentList.head != nullptr) {
                system("cls");
                DeleteStudent(studentList);
            }
            else {
                system("cls");
                cout << "No students to delete!\n";
                system("pause");
                system("cls");
            }
        }
        else if (option == 5) {
            if (studentList.head != nullptr) {
                system("cls");
                DeleteHistory(studentList);
            }
            else {
                system("cls");
                cout << "No students to delete!\n";
                system("pause");
                system("cls");
            }
        }
        else if (option == 0) {
            system("cls");
            cout << "Thank you!";
            exit(0);
        }

    } while (Continue(option));

    Student* current = studentList.head;
    while (current != nullptr) {
        Student* next = current->next;
        delete current;
        current = next;
    }

    return 0;
}

void MainMenu(int& option) {
    cout << "================================="
        << "\n        School Record"
        << "\n================================="
        << "\n1. Add Student"
        << "\n2. Lists of Students"
        << "\n3. Calculate All Students Average Grade"
        << "\n4. Delete One Student"
        << "\n5. Delete History"
        << "\n0. Exit"
        << "\nInput choice: ";
    cin >> option;
}

void GetInfo(StudentList& studentList) {
    const int MAX_STUDENTS = 100;
    int studentSize;
    Student* current = studentList.head;
    do {
        cout << "How many Students would you like to add: ";
        cin >> studentSize;
    } while (studentSize <= 0 || studentSize >= MAX_STUDENTS);

    for (int i = 0; i < studentSize; i++) {
        cout << "Student " << i + 1 << ": " << "\n";
        Student* newStudent = new Student;
        cout << "Name: "; cin >> newStudent->name;
        cout << "Age: "; cin >> newStudent->age;
        cout << "Course: "; cin >> newStudent->course;
        cout << "Grade: "; cin >> newStudent->grade;
        if (studentList.head == nullptr) {
            studentList.head = newStudent;
            studentList.tail = newStudent;
        }
        else {
            studentList.tail->next = newStudent;
            studentList.tail = newStudent;
        }
        cout << "\n";
    }
}
void StudentLists(const StudentList& studentList) {
    int studentNumber = 1;
    Student* current = studentList.head;
    while (current != nullptr) {
        cout << "\nStudent " << studentNumber << ": ";
        cout << "\nName: " << current->name
            << "\nAge: " << current->age
            << "\nCourse: " << current->course
            << "\nGrade: " << current->grade;
        cout << "\n";
        current = current->next;
        studentNumber++;
    }
}

void DeleteStudent(StudentList& studentList) {
    string name;
    cout << "Enter the name of the student to delete: ";
    cin >> name;

    Student* prev = nullptr;
    Student* current = studentList.head;
    while (current != nullptr) {
        if (current->name == name) {
            if (prev != nullptr)
                prev->next = current->next;
            else
                studentList.head = current->next;
            if (current == studentList.tail)
                studentList.tail = prev;
            delete current;
            cout << "\nStudent record for " << name << " deleted successfully.\n";
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "\nStudent with name " << name << " not found.\n";
}


void DeleteHistory(StudentList& studentList) {
    Student* current = studentList.head;
    while (current != nullptr) {
        Student* next = current->next;
        delete current;
        current = next;
    }
    studentList.head = nullptr;
    studentList.tail = nullptr;
    cout << "\nAll student records deleted successfully.\n";
}

double CalculateStudentGrade(const StudentList& studentList) {
    double sum = 0;
    int count = 0;
    Student* current = studentList.head;
    while (current != nullptr) {
        sum += current->grade;
        count++;
        current = current->next;
    }
    if (count > 0)
        return sum / count;
    else
        return 0;
}

bool Continue(int& option) {
    int choice;
    cout << "\nDo you want to Continue?"
        << "\n1. Add another Student"
        << "\n2. View Lists"
        << "\n3. Calculate All Students Average Grade"
        << "\n4. Delete One Student"
        << "\n5. Delete History"
        << "\n0. Exit"
        << "\nInput choice: ";
    cin >> choice;

    if (choice >= 0 && choice <= 5) {
        option = choice;
        return true;
    }
    return false;
}
