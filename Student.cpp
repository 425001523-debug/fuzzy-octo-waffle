#include "Student.h"
#include <sstream>
#include <iomanip>

// Default Constructor
Student::Student() {
    studentId = 425001523;
    fullName = "James Vincent Sadili";
    course = "BSIT";
    gpa = 0.0;
    isActive = true;
    enrollmentYear = 2026;
}

// Parameterized Constructor
Student::Student(int id, string name, string course, double gpa, bool active, int year) {
    studentId = id;
    fullName = name;
    this->course = course;
    this->gpa = gpa;
    isActive = active;
    enrollmentYear = year;
}

// Getter Methods
int Student::getStudentId() const { 
    return studentId; 
}

string Student::getFullName() const { 
    return fullName; 
}

string Student::getCourse() const { 
    return course; 
}

double Student::getGPA() const { 
    return gpa; 
}

bool Student::getIsActive() const { 
    return isActive; 
}

int Student::getEnrollmentYear() const { 
    return enrollmentYear; 
}

// Setter Methods
void Student::setStudentId(int id) { 
    studentId = id; 
}

void Student::setFullName(string name) { 
    fullName = name; 
}

void Student::setCourse(string course) { 
    this->course = course; 
}

void Student::setGPA(double gpa) { 
    this->gpa = gpa; 
}

void Student::setIsActive(bool active) { 
    isActive = active; 
}

void Student::setEnrollmentYear(int year) { 
    enrollmentYear = year; 
}

// Business Logic: Calculate Performance Score
double Student::calculatePerformanceScore() const {
    // Performance score based on GPA (0-100 scale)
    // Assuming GPA is on 0-4.0 scale
    return (gpa / 4.0) * 100;
}

// Business Logic: Check Scholarship Eligibility
bool Student::isScholarshipEligible() const {
    // Eligible if GPA >= 3.5 and student is active
    return (gpa >= 3.5 && isActive);
}

// Return formatted string representation
string Student::toString() const {
    stringstream ss;
    ss << "ID: " << studentId 
       << " | Name: " << fullName 
       << " | Course: " << course 
       << " | GPA: " << fixed << setprecision(2) << gpa 
       << " | Status: " << (isActive ? "Active" : "Inactive") 
       << " | Year: " << enrollmentYear;
    return ss.str();
}
