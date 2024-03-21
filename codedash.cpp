#include <iostream>
#include <string>
using namespace std;

#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name, course;
    int age;
    double grade;
    double budget;
    Student* next = nullptr;
    Student* prev = nullptr;
};

struct Product {
    string name;
    double price;
    int quantity;
    Product* next = nullptr;
};

struct Canteen {
    Product* head = nullptr;
    Product* tail = nullptr;
};

struct Purchase {
    string productName;
    string studentName;
    int quantity;
    Purchase* next = nullptr;
};

struct PurchaseHistory {
    Purchase* head = nullptr;
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
void AddProduct(Canteen&);
void ViewProducts(const Canteen&);
void PurchaseProduct(StudentList&, const Canteen&, PurchaseHistory&);
void ViewPurchaseHistory(const PurchaseHistory&);
void RemoveProduct(Canteen&);
double CalculateTotalRevenue(const PurchaseHistory&, const Canteen&);
bool Continue(int&);

int main() {
    int option = 0;
    StudentList studentList;
    Canteen canteen;
    PurchaseHistory purchaseHistory;

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
        else if (option == 6) {
            system("cls");
            AddProduct(canteen);
        }
        else if (option == 7) {
            system("cls");
            ViewProducts(canteen);
        }
        else if (option == 8) {
            if (studentList.head != nullptr) {
                system("cls");
                PurchaseProduct(studentList, canteen, purchaseHistory);
            }
            else {
                system("cls");
                cout << "No students to make purchases for!\n";
                system("pause");
                system("cls");
            }
        }
        else if (option == 9) {
            system("cls");
            if (purchaseHistory.head != nullptr) {
                ViewPurchaseHistory(purchaseHistory);
            }
            else {
                cout << "No Purchase Transactions Yet\n";
            }
            system("pause");
            system("cls");
        }
        else if (option == 10) {
            system("cls");
            RemoveProduct(canteen);
        }
        else if (option == 11) {
            system("cls");
            cout << "Total Revenue: Php " << CalculateTotalRevenue(purchaseHistory, canteen) << endl;
            system("pause");
            system("cls");
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
        << "\n5. Delete Student History"
        << "\n6. Add Canteen Product"
        << "\n7. View Canteen Products"
        << "\n8. Purchase Product"
        << "\n9. View Purchase History"
        << "\n10. Remove one Product"
        << "\n11. Calculate Total Revenue"
        << "\n0. Exit"
        << "\nInput choice: ";
    cin >> option;
}

void GetInfo(StudentList& studentList) {
    const int MAX_STUDENTS = 100;
    int studentSize;
    Student* newStudent = nullptr;
    do {
        cout << "How many Students would you like to add: ";
        cin >> studentSize;
    } while (studentSize <= 0 || studentSize >= MAX_STUDENTS);

    for (int i = 0; i < studentSize; i++) {
        newStudent = new Student;
        cout << "Student " << i + 1 << ": " << "\n";
        cout << "Name: "; cin >> newStudent->name;
        cout << "Age: "; cin >> newStudent->age;
        cout << "Course: "; cin >> newStudent->course;
        cout << "Grade: "; cin >> newStudent->grade;
        cout << "Budget: "; cin >> newStudent->budget;
        newStudent->next = nullptr;
        newStudent->prev = nullptr;
        if (studentList.head == nullptr) {
            studentList.head = newStudent;
            studentList.tail = newStudent;
        }
        else {
            studentList.tail->next = newStudent;
            newStudent->prev = studentList.tail;
            studentList.tail = newStudent;
        }
        cout << "\n";
    }
}

void StudentLists(const StudentList& studentList) {
    Student* current = studentList.head;
    int studentNumber = 1;
    while (current != nullptr) {
        cout << "\nStudent " << studentNumber << ": ";
        cout << "\nName: " << current->name
            << "\nAge: " << current->age
            << "\nCourse: " << current->course
            << "\nGrade: " << current->grade
            << "\nBudget: " << current->budget;
        cout << "\n";
        current = current->next;
        studentNumber++;
    }
}

void DeleteStudent(StudentList& studentList) {
    Student* current = studentList.head;
    string name;
    cout << "Enter the name of the student to delete: ";
    cin >> name;

    while (current != nullptr) {
        if (current->name == name) {
            if (current->prev != nullptr)
                current->prev->next = current->next;
            else
                studentList.head = current->next;
            if (current->next != nullptr)
                current->next->prev = current->prev;
            else
                studentList.tail = current->prev;
            delete  current;
            cout << "\nStudent record for " << name << " deleted successfully.\n";
            return;
        }
        current = current->next;
    }
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

void AddProduct(Canteen& canteen) {
    Product* newProduct = new Product;
    cout << "Enter Product Name: ";
    cin >> newProduct->name;
    cout << "Enter Product Price: ";
    cin >> newProduct->price;
    cout << "Enter Product Quantity: ";
    cin >> newProduct->quantity;
    if (canteen.head == nullptr) {
        canteen.head = newProduct;
        canteen.tail = newProduct;
    }
    else {
        canteen.tail->next = newProduct;
        canteen.tail = newProduct;
    }
    cout << "Product added successfully!\n";
}

void ViewProducts(const Canteen& canteen) {
    Product* current = canteen.head;
    int productNumber = 1;
    if (canteen.head == nullptr) {
        cout << "No products available in the canteen.\n";
        return;
    }

    while (current != nullptr) {
        cout << "\nProduct " << productNumber << ": ";
        cout << "\nName: " << current->name
            << "\nPrice: " << current->price
            << "\nQuantity: " << current->quantity;
        cout << "\n";
        current = current->next;
        productNumber++;
    }
}

void PurchaseProduct(StudentList& studentList, const Canteen& canteen, PurchaseHistory& purchaseHistory) {
    Purchase* newPurchase = new Purchase;
    Product* currentProduct = canteen.head;
    Student* currentStudent = studentList.head;
    string studentName, productName;
    int quantity;
    cout << "Enter student name: ";
    cin >> studentName;
    cout << "Enter product name: ";
    cin >> productName;
    cout << "Enter quantity: ";
    cin >> quantity;

    while (currentStudent != nullptr) {
        if (currentStudent->name == studentName) {
            while (currentProduct != nullptr) {
                if (currentProduct->name == productName) {
                    if (currentProduct->quantity >= quantity) {
                        double totalPrice = currentProduct->price * quantity;
                        if (currentStudent->budget >= totalPrice) {
                            newPurchase->studentName = studentName;
                            newPurchase->productName = productName;
                            newPurchase->next = purchaseHistory.head;
                            purchaseHistory.head = newPurchase;

                            currentProduct->quantity -= quantity;
                            currentStudent->budget -= totalPrice;
                            cout << "Purchase Successful!\n";
                            return;
                        }
                        else {
                            cout << "Sorry, " << studentName << " does not have enough budget.\n";
                            return;
                        }
                    }
                    else {
                        cout << "Sorry, " << productName << " does not have enough quantity.\n";
                        return;
                    }
                }
                currentProduct = currentProduct->next;
            }
            cout << "Product " << productName << " not found in the canteen.\n";
            return;
        }
        currentStudent = currentStudent->next;
    }
    cout << "Student " << studentName << " not found.\n";
}

void ViewPurchaseHistory(const PurchaseHistory& purchaseHistory) {
    Purchase* current = purchaseHistory.head;
    if (purchaseHistory.head == nullptr) {
        cout << "No Purchase Transactions Yet\n";
        return;
    }

    while (current != nullptr) {
        cout << "Student Name: " << current->studentName << " purchased " << current->productName << endl;
        current = current->next;
    }
}

void RemoveProduct(Canteen& canteen) {
    string productName;
    Product* current = canteen.head;
    Product* prev = nullptr;
    cout << "Enter the name of the product to remove: ";
    cin >> productName;

    if (canteen.head == nullptr) {
        cout << "No products available in the canteen.\n";
        return;
    }

    while (current != nullptr) {
        if (current->name == productName) {
            if (prev == nullptr) {

                canteen.head = current->next;
                if (canteen.head == nullptr) {
                    canteen.tail = nullptr;
                }
            }
            else {
                prev->next = current->next;
                if (prev->next == nullptr) {
                    canteen.tail = prev;
                }
            }
            delete current;
            cout << "Product " << productName << " removed successfully!\n";
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "Product " << productName << " not found in the canteen.\n";
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
    cout << "\nDo you want to Continue?"
        << "\n1. Add another Student"
        << "\n2. View Student List"
        << "\n3. Calculate All Students Average Grade"
        << "\n4. Delete One Student"
        << "\n5. Delete Student History"
        << "\n6. Add Canteen Product"
        << "\n7. View Canteen Products"
        << "\n8. Purchase Product"
        << "\n9. View Purchase History"
        << "\n10. Remove one Product"
        << "\n11. Calculate Total Revenue"
        << "\n0. Exit"
        << "\nInput choice: ";
    cin >> option;

    if (option >= 0 && option <= 11) {
        return true;
    }
    return false;
}

double CalculateTotalRevenue(const PurchaseHistory& purchaseHistory, const Canteen& canteen) {
    double totalRevenue = 0.0;
    Purchase* currentPurchase = purchaseHistory.head;
    Product* currentProduct = canteen.head;

    while (currentPurchase != nullptr) {
        while (currentProduct != nullptr) {
            if (currentProduct->name == currentPurchase->productName) {
                totalRevenue += currentProduct->price * currentPurchase->quantity;
                break;
            }
            currentProduct = currentProduct->next;
        }
        currentPurchase = currentPurchase->next;
    }

    return totalRevenue;
}
