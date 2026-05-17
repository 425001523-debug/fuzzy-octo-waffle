#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

/**
 * @class Student
 * @brief Represents a student record with ID, name, course, GPA, and status.
 * 
 * This class encapsulates student data and provides getter/setter methods
 * for secure access to private member variables.
 */
class Student {
private:
    int studentId;
    string fullName;
    string course;
    double gpa;
    bool isActive;
    int enrollmentYear;

public:
    // Constructors
    Student();
    Student(int id, string name, string course, double gpa, bool active, int year);

    // Getter Methods
    int getStudentId() const;
    string getFullName() const;
    string getCourse() const;
    double getGPA() const;
    bool getIsActive() const;
    int getEnrollmentYear() const;

    // Setter Methods
    void setStudentId(int id);
    void setFullName(string name);
    void setCourse(string course);
    void setGPA(double gpa);
    void setIsActive(bool active);
    void setEnrollmentYear(int year);

    // Business Logic Methods
    /**
     * @brief Calculates academic performance score based on GPA.
     * @return Performance score (0-100).
     */
    double calculatePerformanceScore() const;

    /**
     * @brief Determines scholarship eligibility based on GPA and status.
     * @return true if student is eligible, false otherwise.
     */
    bool isScholarshipEligible() const;

    /**
     * @brief Returns formatted string representation of the student.
     * @return Formatted student data as string.
     */
    string toString() const;
};

#endif
