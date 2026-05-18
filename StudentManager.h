#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "Student.h"
#include <vector>
#include <string>

using namespace std;

/**
 * @class StudentManager
 * @brief Manages student records and file persistence operations.
 *
 * Handles loading, saving, searching, and CRUD operations
 * for a collection of Student objects.
 */
class StudentManager {
private:
    vector<Student> students;
    string dataFileName;
    int nextStudentId;

    /**
     * @brief Finds the vector index of a student by their unique ID.
     * @param id The student ID to locate.
     * @return Index in the vector, or -1 if not found.
     */
    int findStudentById(int id) const;

public:
    StudentManager(string fileName = "students.txt");

    // File I/O
    bool loadFromFile();
    bool saveToFile();

    // CRUD Operations
    bool addStudent(string name, string course, double gpa, bool active, int year);
    bool getStudent(int id, Student& student) const;
    bool updateStudent(int id, string name, string course, double gpa, bool active);
    bool deleteStudent(int id);

    // [CHANGED] Replaced searchByName/searchByCourse with a single ID-based search.
    // Returns true and fills `student` if found; returns false if not found.
    bool searchById(int id, Student& student) const;

    // Filtered Views
    vector<Student> getAllStudents() const;
    vector<Student> getActiveStudents() const;
    vector<Student> getScholarshipEligible() const;

    // Reporting
    int getTotalStudents() const;
    double calculateAverageGPA() const;
    string generateReport() const;
};

#endif // STUDENT_MANAGER_H