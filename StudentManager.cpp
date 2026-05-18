#include "StudentManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// ─────────────────────────────────────────────
// Constructor
// ─────────────────────────────────────────────
StudentManager::StudentManager(string fileName) {
    dataFileName   = fileName;
    nextStudentId  = 1;
}

// ─────────────────────────────────────────────
// File I/O: Load
// ─────────────────────────────────────────────
bool StudentManager::loadFromFile() {
    ifstream inputFile(dataFileName);

    if (!inputFile.is_open()) {
        cout << "Creating new database file: " << dataFileName << endl;
        return true; // First-run: no file yet, that's okay
    }

    string line;
    int maxId = 0;

    while (getline(inputFile, line)) {
        // Skip blank lines and comment lines
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        int    id, year, activeInt;
        string name, course;
        double gpa;
        char   delimiter;

        // Format: ID,Name,Course,GPA,Active,Year
        if (ss >> id >> delimiter &&
            getline(ss, name,   ',') &&
            getline(ss, course, ',') &&
            ss >> gpa >> delimiter >> activeInt >> delimiter >> year)
        {
            students.push_back(Student(id, name, course, gpa,
                                       (activeInt == 1), year));
            maxId = max(maxId, id);
        }
    }

    inputFile.close();
    nextStudentId = maxId + 1;
    return true;
}

// ─────────────────────────────────────────────
// File I/O: Save
// ─────────────────────────────────────────────
bool StudentManager::saveToFile() {
    ofstream outputFile(dataFileName);

    if (!outputFile.is_open()) return false;

    outputFile << "# Student Database\n";
    outputFile << "# Format: ID,Name,Course,GPA,Active,Year\n";

    for (const Student& s : students) {
        outputFile << s.getStudentId()    << ","
                   << s.getFullName()     << ","
                   << s.getCourse()       << ","
                   << fixed << setprecision(2) << s.getGPA() << ","
                   << (s.getIsActive() ? 1 : 0) << ","
                   << s.getEnrollmentYear() << "\n";
    }

    outputFile.close();
    return true;
}

// ─────────────────────────────────────────────
// Private Helper: Find index by ID
// ─────────────────────────────────────────────
int StudentManager::findStudentById(int id) const {
    for (int i = 0; i < (int)students.size(); i++) {
        if (students[i].getStudentId() == id) return i;
    }
    return -1;
}

// ─────────────────────────────────────────────
// CRUD: Add
// ─────────────────────────────────────────────
bool StudentManager::addStudent(string name, string course,
                                double gpa, bool active, int year) {
    if (name.empty() || course.empty())  return false;
    if (gpa < 0.0   || gpa > 4.0)       return false;

    students.push_back(Student(nextStudentId, name, course, gpa, active, year));
    nextStudentId++;
    return true;
}

// ─────────────────────────────────────────────
// CRUD: Read single student
// ─────────────────────────────────────────────
bool StudentManager::getStudent(int id, Student& student) const {
    int index = findStudentById(id);
    if (index == -1) return false;
    student = students[index];
    return true;
}

// ─────────────────────────────────────────────
// CRUD: Update
// ─────────────────────────────────────────────
bool StudentManager::updateStudent(int id, string name, string course,
                                   double gpa, bool active) {
    int index = findStudentById(id);
    if (index == -1) return false;
    if (name.empty() || course.empty()) return false;
    if (gpa < 0.0   || gpa > 4.0)      return false;

    students[index].setFullName(name);
    students[index].setCourse(course);
    students[index].setGPA(gpa);
    students[index].setIsActive(active);
    return true;
}

// ─────────────────────────────────────────────
// CRUD: Delete
// ─────────────────────────────────────────────
bool StudentManager::deleteStudent(int id) {
    int index = findStudentById(id);
    if (index == -1) return false;
    students.erase(students.begin() + index);
    return true;
}

// ─────────────────────────────────────────────
// [CHANGED] Search: By Unique ID only
//
// Replaces the old searchByName() and searchByCourse().
// Uses the existing getStudent() to fill the result;
// returns false immediately if the ID is not found.
// ─────────────────────────────────────────────
bool StudentManager::searchById(int id, Student& student) const {
    return getStudent(id, student);
}

// ─────────────────────────────────────────────
// Filtered Views
// ─────────────────────────────────────────────
vector<Student> StudentManager::getAllStudents() const {
    return students;
}

vector<Student> StudentManager::getActiveStudents() const {
    vector<Student> results;
    for (const Student& s : students) {
        if (s.getIsActive()) results.push_back(s);
    }
    return results;
}

vector<Student> StudentManager::getScholarshipEligible() const {
    vector<Student> results;
    for (const Student& s : students) {
        if (s.isScholarshipEligible()) results.push_back(s);
    }
    return results;
}

// ─────────────────────────────────────────────
// Reporting
// ─────────────────────────────────────────────
int StudentManager::getTotalStudents() const {
    return (int)students.size();
}

double StudentManager::calculateAverageGPA() const {
    if (students.empty()) return 0.0;
    double sum = 0.0;
    for (const Student& s : students) sum += s.getGPA();
    return sum / students.size();
}

string StudentManager::generateReport() const {
    stringstream report;
    report << "\n========== STUDENT MANAGER SYSTEM - REPORT ==========\n"
           << "Total Students:        " << getTotalStudents()             << "\n"
           << "Active Students:       " << getActiveStudents().size()     << "\n"
           << "Scholarship Eligible:  " << getScholarshipEligible().size()<< "\n"
           << "Average GPA:           " << fixed << setprecision(2)
                                        << calculateAverageGPA()          << "\n"
           << "======================================================\n";
    return report.str();
}