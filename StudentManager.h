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
 * Handles loading, saving, searching, and CRUD operations for a collection of students.
 */
class StudentManager {
private:
    vector<Student> students;
    string dataFileName;
    int nextStudentId;

    /**
     * @brief Finds a student by ID.
     * @param id The student ID to search for.
     * @return Index of the student in the vector, or -1 if not found.
     */
    int findStudentById(int id) const;

public:
    StudentManager(string fileName = "students.txt");

    bool loadFromFile();
    bool saveToFile();

    bool addStudent(string name, string course, double gpa, bool active, int year);
    bool getStudent(int id, Student& student) const;
    vector<Student> getAllStudents() const;
    bool updateStudent(int id, string name, string course, double gpa, bool active);
    bool deleteStudent(int id);

    vector<Student> searchByName(string searchTerm) const;
    vector<Student> searchByCourse(string course) const;
    vector<Student> getActiveStudents() const;
    vector<Student> getScholarshipEligible() const;

    int getTotalStudents() const;
    double calculateAverageGPA() const;
    string generateReport() const;
};

#endif // STUDENT_MANAGER_H
