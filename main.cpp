#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>
#include "StudentManager.h"

using namespace std;

// ─────────────────────────────────────────────
// Forward Declarations
// ─────────────────────────────────────────────
void displayMainMenu();
void displayViewMenu();
void handleAddStudent(StudentManager& manager);
void handleViewStudents(StudentManager& manager);
void handleSearchStudent(StudentManager& manager);   // [CHANGED] ID-only search
void handleUpdateStudent(StudentManager& manager);
void handleDeleteStudent(StudentManager& manager);
void displayReport(StudentManager& manager);
bool validateInput(double& value, double minVal = 0.0, double maxVal = 4.0);
bool validateIntInput(int& value);
void pauseScreen();

// ─────────────────────────────────────────────
// Entry Point
// ─────────────────────────────────────────────
int main() {
    StudentManager manager("students.txt");

    if (!manager.loadFromFile()) {
        cerr << "Error loading student database!" << endl;
        return 1;
    }

    cout << "\n=====================================" << endl;
    cout << "   STUDENT MANAGER SYSTEM v1.0"         << endl;
    cout << "=====================================" << endl;

    int  choice;
    bool running = true;

    while (running) {
        displayMainMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Please enter a number between 1 and 7." << endl;
            pauseScreen();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: handleViewStudents(manager);  break;
            case 2: handleAddStudent(manager);    break;
            case 3: handleSearchStudent(manager); break;
            case 4: handleUpdateStudent(manager); break;
            case 5: handleDeleteStudent(manager); break;
            case 6: displayReport(manager);       break;
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

// ─────────────────────────────────────────────
// Menu Displays
// ─────────────────────────────────────────────
void displayMainMenu() {
    cout << "\n========== MAIN MENU ==========" << endl;
    cout << "1. View All Students"              << endl;
    cout << "2. Add New Student"                << endl;
    cout << "3. Search Student"                 << endl;
    cout << "4. Update Student"                 << endl;
    cout << "5. Delete Student"                 << endl;
    cout << "6. View Report"                    << endl;
    cout << "7. Save and Exit"                  << endl;
    cout << "==============================="   << endl;
    cout << "Enter your choice: ";
}

void displayViewMenu() {
    cout << "\n========== VIEW OPTIONS ==========" << endl;
    cout << "1. View All Students"                << endl;
    cout << "2. View Active Students Only"        << endl;
    cout << "3. View Scholarship Eligible Students" << endl;
    cout << "4. Back to Main Menu"                << endl;
    cout << "=================================="  << endl;
    cout << "Enter your choice: ";
}

// ─────────────────────────────────────────────
// Handler: Add Student
// ─────────────────────────────────────────────
void handleAddStudent(StudentManager& manager) {
    cout << "\n========== ADD NEW STUDENT ==========" << endl;

    string name, course;
    double gpa;
    int    year, activeChoice;
    bool   active;

    cout << "Enter student name: ";
    getline(cin, name);
    if (name.empty()) {
        cout << "Error: Name cannot be empty!" << endl;
        pauseScreen();
        return;
    }

    cout << "Enter course name: ";
    getline(cin, course);
    if (course.empty()) {
        cout << "Error: Course cannot be empty!" << endl;
        pauseScreen();
        return;
    }

    cout << "Enter GPA (0.0 - 4.0): ";
    if (!validateInput(gpa, 0.0, 4.0)) { pauseScreen(); return; }

    cout << "Enter enrollment year: ";
    if (!validateIntInput(year)) { pauseScreen(); return; }

    cout << "Is student active? (1 = Yes, 0 = No): ";
    if (!validateIntInput(activeChoice) || (activeChoice != 0 && activeChoice != 1)) {
        cout << "Error: Please enter 1 (Yes) or 0 (No)." << endl;
        pauseScreen();
        return;
    }
    active = (activeChoice == 1);

    if (manager.addStudent(name, course, gpa, active, year)) {
        cout << "\nStudent added successfully!" << endl;
    } else {
        cout << "\nError: Could not add student. Please check your input." << endl;
    }
    pauseScreen();
}

// ─────────────────────────────────────────────
// Handler: View Students
// ─────────────────────────────────────────────
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

        if      (choice == 1) { displayList = manager.getAllStudents();          break; }
        else if (choice == 2) { displayList = manager.getActiveStudents();       break; }
        else if (choice == 3) { displayList = manager.getScholarshipEligible();  break; }
        else if (choice == 4) { return; }
        else { cout << "Invalid choice! Please try again." << endl; }
    }

    if (displayList.empty()) {
        cout << "\nNo students found." << endl;
    } else {
        cout << "\n========== STUDENT LIST ==========" << endl;
        for (const Student& s : displayList) {
            cout << s.toString() << endl;
        }
        cout << "==================================" << endl;
        cout << "Total: " << displayList.size() << " student(s)" << endl;
    }
    pauseScreen();
}

// ─────────────────────────────────────────────
// Handler: Search Student
//
// [CHANGED] Removed the old submenu that offered searching
// by Name or Course. The new flow asks for a Student ID
// directly, calls searchById(), and displays the result
// or a "Student not found." message.
//
// Why: Student IDs are unique, so a single exact lookup
// is faster and unambiguous. The old searchByName and
// searchByCourse methods have been removed from
// StudentManager entirely since nothing else uses them.
// ─────────────────────────────────────────────
void handleSearchStudent(StudentManager& manager) {
    cout << "\n========== SEARCH STUDENT ==========" << endl;

    int studentId;
    cout << "Enter Student ID: ";
    if (!validateIntInput(studentId)) {
        pauseScreen();
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Student result;
    if (manager.searchById(studentId, result)) {
        cout << "\n========== STUDENT FOUND ==========" << endl;
        cout << result.toString()                       << endl;
        cout << "===================================" << endl;
    } else {
        cout << "\nStudent not found." << endl;
    }

    pauseScreen();
}

// ─────────────────────────────────────────────
// Handler: Update Student
// ─────────────────────────────────────────────
void handleUpdateStudent(StudentManager& manager) {
    cout << "\n========== UPDATE STUDENT ==========" << endl;

    int studentId;
    cout << "Enter student ID to update: ";
    if (!validateIntInput(studentId)) { pauseScreen(); return; }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
    int    activeChoice;
    bool   active;

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
    if (!validateInput(gpa, 0.0, 4.0)) { pauseScreen(); return; }

    cout << "Is student active? (1 = Yes, 0 = No): ";
    if (!validateIntInput(activeChoice) || (activeChoice != 0 && activeChoice != 1)) {
        cout << "Error: Please enter 1 (Yes) or 0 (No)." << endl;
        pauseScreen();
        return;
    }
    active = (activeChoice == 1);

    if (manager.updateStudent(studentId, name, course, gpa, active)) {
        cout << "\nStudent updated successfully!" << endl;
    } else {
        cout << "\nError: Could not update student." << endl;
    }
    pauseScreen();
}

// ─────────────────────────────────────────────
// Handler: Delete Student
// ─────────────────────────────────────────────
void handleDeleteStudent(StudentManager& manager) {
    cout << "\n========== DELETE STUDENT ==========" << endl;

    int studentId;
    cout << "Enter student ID to delete: ";
    if (!validateIntInput(studentId)) { pauseScreen(); return; }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
    cin  >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (tolower(confirm) == 'y') {
        if (manager.deleteStudent(studentId)) {
            cout << "Student deleted successfully!" << endl;
        } else {
            cout << "Error: Could not delete student." << endl;
        }
    } else {
        cout << "Delete operation cancelled." << endl;
    }
    pauseScreen();
}

// ─────────────────────────────────────────────
// Report Display
// ─────────────────────────────────────────────
void displayReport(StudentManager& manager) {
    cout << manager.generateReport();
    pauseScreen();
}

// ─────────────────────────────────────────────
// Input Validation Helpers
// ─────────────────────────────────────────────
bool validateInput(double& value, double minVal, double maxVal) {
    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Invalid input. Please enter a valid number." << endl;
        return false;
    }
    if (value < minVal || value > maxVal) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Value must be between " << minVal << " and " << maxVal << "." << endl;
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