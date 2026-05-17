#include "StudentManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Constructor
StudentManager::StudentManager(string fileName) {
    dataFileName = fileName;
    nextStudentId = 1;
}

// Load data from file
bool StudentManager::loadFromFile() {
    ifstream inputFile(dataFileName);
    
    if (!inputFile.is_open()) {
        cout << "Creating new database file: " << dataFileName << endl;
        return true; // First run scenario
    }

    string line;
    int maxId = 0;
    
    while (getline(inputFile, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        int id;
        string name, course;
        double gpa;
        bool active;
        int year;
        char delimiter;

        // Parse: ID,Name,Course,GPA,Active,Year
        if (ss >> id >> delimiter >> 
            ws && getline(ss, name, ',') &&
            ss >> ws && getline(ss, course, ',') &&
            ss >> gpa >> delimiter >> active >> delimiter >> year) {
            
            students.push_back(Student(id, name, course, gpa, active, year));
            maxId = max(maxId, id);
        }
    }

    inputFile.close();
    nextStudentId = maxId + 1;
    return true;
}

// Find student by ID (helper function)
int StudentManager::findStudentById(int id) const {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getStudentId() == id) {
            return i;
        }
    }
    return -1;
}

// Add a new student
bool StudentManager::addStudent(string name, string course, double gpa, bool active, int year) {
    // Validation
    if (name.empty() || course.empty()) {
        return false;
    }
    if (gpa < 0 || gpa > 4.0) {
        return false;
    }

    Student newStudent(nextStudentId, name, course, gpa, active, year);
    students.push_back(newStudent);
    nextStudentId++;
    return true;
}

// Get a student by ID
bool StudentManager::getStudent(int id, Student& student) const {
    int index = findStudentById(id);
    if (index != -1) {
        student = students[index];
        return true;
    }
    return false;
}

// Get all students
vector<Student> StudentManager::getAllStudents() const {
    return students;
}

// Update a student
bool StudentManager::updateStudent(int id, string name, string course, double gpa, bool active) {
    int index = findStudentById(id);
    if (index == -1) {
        return false;
    }

    // Validation
    if (name.empty() || course.empty()) {
        return false;
    }
    if (gpa < 0 || gpa > 4.0) {
        return false;
    }

    students[index].setFullName(name);
    students[index].setCourse(course);
    students[index].setGPA(gpa);
    students[index].setIsActive(active);
    return true;
}

// Delete a student
bool StudentManager::deleteStudent(int id) {
    int index = findStudentById(id);
    if (index == -1) {
        return false;
    }

    students.erase(students.begin() + index);
    return true;
}

// Search by name
vector<Student> StudentManager::searchByName(string searchTerm) const {
    vector<Student> results;
    for (const Student& student : students) {
        string fullName = student.getFullName();
        // Convert to lowercase for case-insensitive search
        transform(fullName.begin(), fullName.end(), fullName.begin(), ::tolower);
        transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);
        
        if (fullName.find(searchTerm) != string::npos) {
            results.push_back(student);
        }
    }
    return results;
}

// Search by course
vector<Student> StudentManager::searchByCourse(string course) const {
    vector<Student> results;
    for (const Student& student : students) {
        if (student.getCourse() == course) {
            results.push_back(student);
        }
    }
    return results;
}

// Get active students
vector<Student> StudentManager::getActiveStudents() const {
    vector<Student> results;
    for (const Student& student : students) {
        if (student.getIsActive()) {
            results.push_back(student);
        }
    }
    return results;
}

// Get scholarship eligible students
vector<Student> StudentManager::getScholarshipEligible() const {
    vector<Student> results;
    for (const Student& student : students) {
        if (student.isScholarshipEligible()) {
            results.push_back(student);
        }
    }
    return results;
}

// Save to file
bool StudentManager::saveToFile() {
    ofstream outputFile(dataFileName);
    
    if (!outputFile.is_open()) {
        return false;
    }

    // Write header
    outputFile << "# Student Database" << endl;
    outputFile << "# Format: ID,Name,Course,GPA,Active,Year" << endl;

    // Write each student
    for (const Student& student : students) {
        outputFile << student.getStudentId() << ","
                   << student.getFullName() << ","
                   << student.getCourse() << ","
                   << fixed << setprecision(2) << student.getGPA() << ","
                   << (student.getIsActive() ? 1 : 0) << ","
                   << student.getEnrollmentYear() << endl;
    }

    outputFile.close();
    return true;
}

// Get total students
int StudentManager::getTotalStudents() const {
    return students.size();
}

// Calculate average GPA
double StudentManager::calculateAverageGPA() const {
    if (students.empty()) {
        return 0.0;
    }

    double sum = 0.0;
    for (const Student& student : students) {
        sum += student.getGPA();
    }
    return sum / students.size();
}

// Generate report
string StudentManager::generateReport() const {
    stringstream report;
    report << "\n========== STUDENT MANAGER SYSTEM - REPORT ==========" << endl;
    report << "Total Students: " << getTotalStudents() << endl;
    report << "Active Students: " << getActiveStudents().size() << endl;
    report << "Scholarship Eligible: " << getScholarshipEligible().size() << endl;
    report << "Average GPA: " << fixed << setprecision(2) << calculateAverageGPA() << endl;
    report << "====================================================\n" << endl;
    return report.str();
}
