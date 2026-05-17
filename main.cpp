#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>
#include "StudentManager.h"

using namespace std;

// Function prototypes
void displayMainMenu();
void displayViewMenu();
void handleAddStudent(StudentManager& manager);
void handleViewStudents(StudentManager& manager);
void handleSearchStudent(StudentManager& manager);
void handleUpdateStudent(StudentManager& manager);
void handleDeleteStudent(StudentManager& manager);
void displayReport(StudentManager& manager);
bool validateInput(double& value, double minVal = 0.0, double maxVal = 4.0);
bool validateIntInput(int& value);
void pauseScreen();

int main() {
    StudentManager manager("students.txt");
    
    // Load existing data from file
    if (!manager.loadFromFile()) {
        cerr << "Error loading student database!" << endl;
        return 1;
    }

    cout << "\n=====================================" << endl;
    cout << "   STUDENT MANAGER SYSTEM v1.0" << endl;
    cout << "=====================================" << endl;

    int choice;
    bool running = true;

    while (running) {
        displayMainMenu();
        
        // Input validation for menu choice
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Please enter a number between 1 and 7." << endl;
            pauseScreen();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                handleViewStudents(manager);
                break;
            case 2:
                handleAddStudent(manager);
                break;
            case 3:
                handleSearchStudent(manager);
                break;
            case 4:
                handleUpdateStudent(manager);
                break;
            case 5:
                handleDeleteStudent(manager);
                break;
            case 6:
                displayReport(manager);
                break;
            case 7:
                if (manager.saveToFile()) {
                    cout << "\nData saved successfully!" << endl;
                    cout << "Exiting Student Manager System. Goodbye!" << endl;
                    running = false;
                } else {
                    cout << "\nError saving data!" << endl;
                }
                break;
            default:
                cout << "\nInvalid choice! Please select an option between 1 and 7." << endl;
                pauseScreen();
        }
    }

    return 0;
}

void displayMainMenu() {
    cout << "\n========== MAIN MENU ==========" << endl;
    cout << "1. View All Students" << endl;
    cout << "2. Add New Student" << endl;
    cout << "3. Search Student" << endl;
    cout << "4. Update Student" << endl;
    cout << "5. Delete Student" << endl;
    cout << "6. View Report" << endl;
    cout << "7. Save and Exit" << endl;
    cout << "==============================" << endl;
    cout << "Enter your choice: ";
}

void displayViewMenu() {
    cout << "\n========== VIEW OPTIONS ==========" << endl;
    cout << "1. View All Students" << endl;
    cout << "2. View Active Students Only" << endl;
    cout << "3. View Scholarship Eligible Students" << endl;
    cout << "4. Back to Main Menu" << endl;
    cout << "==================================" << endl;
    cout << "Enter your choice: ";
}

void handleAddStudent(StudentManager& manager) {
    cout << "\n========== ADD NEW STUDENT ==========" << endl;
    
    string name, course;
    double gpa;
    int year;
    bool active;
    int activeChoice;

    // Get student name
    cout << "Enter student name: ";
    getline(cin, name);
    if (name.empty()) {
        cout << "Error: Name cannot be empty!" << endl;
        pauseScreen();
        return;
    }

    // Get course
    cout << "Enter course name: ";
    getline(cin, course);
    if (course.empty()) {
        cout << "Error: Course cannot be empty!" << endl;
        pauseScreen();
        return;
    }

    // Get GPA with validation
    cout << "Enter GPA (0.0 - 4.0): ";
    if (!validateInput(gpa, 0.0, 4.0)) {
        pauseScreen();
        return;
    }

    // Get enrollment year
    cout << "Enter enrollment year: ";
    if (!validateIntInput(year)) {
        pauseScreen();
        return;
    }

    // Get active status
    cout << "Is student active? (1 = Yes, 0 = No): ";
    if (!validateIntInput(activeChoice) || (activeChoice != 0 && activeChoice != 1)) {
        cout << "Error: Invalid input. Please enter 1 or 0." << endl;
        pauseScreen();
        return;
    }
    active = (activeChoice == 1);

    if (manager.addStudent(name, course, gpa, active, year)) {
        cout << "\nStudent added successfully!" << endl;
    } else {
        cout << "\nError adding student. Please check your input." << endl;
    }
    pauseScreen();
}

void handleViewStudents(StudentManager& manager) {
    int choice;
    vector<Student> displayList;

    while (true) {
        displayViewMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input!" << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            displayList = manager.getAllStudents();
            break;
        } else if (choice == 2) {
            displayList = manager.getActiveStudents();
            break;
        } else if (choice == 3) {
            displayList = manager.getScholarshipEligible();
            break;
        } else if (choice == 4) {
            return;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }

    if (displayList.empty()) {
        cout << "\nNo students found." << endl;
    } else {
        cout << "\n========== STUDENT LIST ==========" << endl;
        for (const Student& student : displayList) {
            cout << student.toString() << endl;
        }
        cout << "================================" << endl;
        cout << "Total: " << displayList.size() << " student(s)" << endl;
    }
    pauseScreen();
}

void handleSearchStudent(StudentManager& manager) {
    cout << "\n========== SEARCH STUDENT ==========" << endl;
    cout << "1. Search by Name" << endl;
    cout << "2. Search by Course" << endl;
    cout << "====================================" << endl;
    cout << "Enter your choice: ";
    
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!" << endl;
        pauseScreen();
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Student> results;

    if (choice == 1) {
        string searchTerm;
        cout << "Enter student name (or part of name): ";
        getline(cin, searchTerm);
        results = manager.searchByName(searchTerm);
    } else if (choice == 2) {
        string course;
        cout << "Enter course name: ";
        getline(cin, course);
        results = manager.searchByCourse(course);
    } else {
        cout << "Invalid choice!" << endl;
        pauseScreen();
        return;
    }

    if (results.empty()) {
        cout << "\nNo students found matching your criteria." << endl;
    } else {
        cout << "\n========== SEARCH RESULTS ==========" << endl;
        for (const Student& student : results) {
            cout << student.toString() << endl;
        }
        cout << "===================================" << endl;
        cout << "Total: " << results.size() << " student(s)" << endl;
    }
    pauseScreen();
}

void handleUpdateStudent(StudentManager& manager) {
    cout << "\n========== UPDATE STUDENT ==========" << endl;
    
    int studentId;
    cout << "Enter student ID to update: ";
    if (!validateIntInput(studentId)) {
        pauseScreen();
        return;
    }

    Student student;
    if (!manager.getStudent(studentId, student)) {
        cout << "Student with ID " << studentId << " not found!" << endl;
        pauseScreen();
        return;
    }

    cout << "\nCurrent information:" << endl;
    cout << student.toString() << endl;

    string name, course;
    double gpa;
    bool active;
    int activeChoice;

    cout << "\nEnter new name: ";
    getline(cin, name);
    if (name.empty()) {
        cout << "Error: Name cannot be empty!" << endl;
        pauseScreen();
        return;
    }

    cout << "Enter new course: ";
    getline(cin, course);
    if (course.empty()) {
        cout << "Error: Course cannot be empty!" << endl;
        pauseScreen();
        return;
    }

    cout << "Enter new GPA (0.0 - 4.0): ";
    if (!validateInput(gpa, 0.0, 4.0)) {
        pauseScreen();
        return;
    }

    cout << "Is student active? (1 = Yes, 0 = No): ";
    if (!validateIntInput(activeChoice) || (activeChoice != 0 && activeChoice != 1)) {
        cout << "Error: Invalid input." << endl;
        pauseScreen();
        return;
    }
    active = (activeChoice == 1);

    if (manager.updateStudent(studentId, name, course, gpa, active)) {
        cout << "\nStudent updated successfully!" << endl;
    } else {
        cout << "\nError updating student!" << endl;
    }
    pauseScreen();
}

void handleDeleteStudent(StudentManager& manager) {
    cout << "\n========== DELETE STUDENT ==========" << endl;
    
    int studentId;
    cout << "Enter student ID to delete: ";
    if (!validateIntInput(studentId)) {
        pauseScreen();
        return;
    }

    Student student;
    if (!manager.getStudent(studentId, student)) {
        cout << "Student with ID " << studentId << " not found!" << endl;
        pauseScreen();
        return;
    }

    cout << "\nStudent to be deleted:" << endl;
    cout << student.toString() << endl;

    char confirm;
    cout << "\nAre you sure you want to delete this student? (y/n): ";
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (tolower(confirm) == 'y') {
        if (manager.deleteStudent(studentId)) {
            cout << "Student deleted successfully!" << endl;
        } else {
            cout << "Error deleting student!" << endl;
        }
    } else {
        cout << "Delete operation cancelled." << endl;
    }
    pauseScreen();
}

void displayReport(StudentManager& manager) {
    cout << manager.generateReport();
    pauseScreen();
}

bool validateInput(double& value, double minVal, double maxVal) {
    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Invalid input. Please enter a valid number." << endl;
        return false;
    }

    if (value < minVal || value > maxVal) {
        cout << "Error: Value must be between " << minVal << " and " << maxVal << endl;
        return false;
    }

    return true;
}

bool validateIntInput(int& value) {
    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Invalid input. Please enter a valid integer." << endl;
        return false;
    }

    return true;
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
