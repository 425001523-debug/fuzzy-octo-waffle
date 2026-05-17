Student Manager System

Project Title and SDG Goal
Student Manager System — A modular C++ application designed to provide efficient student record management and data persistence, supporting SDG 4: Quality Education by enabling effective administrative management of student information.

Project Description

Overview
The Student Manager System is a console-based application that demonstrates professional C++ development practices through:
- Multi-file architecture with separated header and implementation files
- Object-Oriented Programming (OOP) with encapsulation and proper class design
- CRUD Operations (Create, Read, Update, Delete) for student management
- File Handling for persistent data storage
- Input Validation and defensive programming techniques
- Advanced algorithms including search and filtering capabilities

Architecture Justification
The project uses a Two-Class Model:
1. Student Class: Represents a single student entity with data validation and business logic
2. StudentManager Class: Handles collection management, CRUD operations, and file I/O

This separation ensures:
- Modularity: Each class has a single responsibility
- Maintainability: Easy to modify or extend functionality
- Reusability: Student class can be used in other applications
- Testability: Components can be tested independently

Key Features
- Automated Data Initialization: Loads pre-existing records from `students.txt`
- Secure Record Management: Complete CRUD operations with validation
- Core Domain Logic: Calculates performance scores and scholarship eligibility
- Persistent State Storage: Saves all changes to external file
- Navigational Menu System: User-friendly interface with input validation

Technical Implementation

Class Structure

Student Class
```
Private Members:
  - int studentId
  - string fullName
  - string course
  - double gpa
  - bool isActive
  - int enrollmentYear

Public Methods:
  - Constructors (Default & Parameterized)
  - Getters & Setters (Encapsulation)
  - calculatePerformanceScore()
  - isScholarshipEligible()
  - toString()
```

StudentManager Class
```
Private Members:
  - vector<Student> students
  - string dataFileName
  - int nextStudentId
  - findStudentById(int id)

Public Methods:
  - loadFromFile()
  - addStudent(...) [CREATE]
  - getStudent(...) [READ]
  - updateStudent(...) [UPDATE]
  - deleteStudent(...) [DELETE]
  - searchByName(...)
  - searchByCourse(...)
  - getActiveStudents()
  - getScholarshipEligible()
  - saveToFile()
  - generateReport()
```

Input Validation
The system implements robust error handling:
- Type Mismatch Prevention: Validates numeric input before processing
- Range Validation: Ensures GPA is within 0.0-4.0
- Empty String Checks: Prevents null or empty data
- Confirmation Dialogs: Asks for confirmation before deletion
- Graceful Error Messages: Informs users of invalid operations

Business Logic
1. Performance Score Calculation: `(GPA / 4.0) × 100`
2. Scholarship Eligibility: GPA ≥ 3.5 AND Student is Active
3. Data Statistics: Average GPA, total students, active count

Installation & Usage

Prerequisites
- C++ 11 or higher
- G++ compiler (or equivalent)
- Text editor or IDE (VS Code, Code::Blocks, etc.)

Compilation
```bash
g++ -std=c++11 main.cpp Student.cpp StudentManager.cpp -o StudentManager
```

Execution
```bash
./StudentManager
```

Menu Options
1. View All Students - Display all or filtered student list
2. Add New Student - Create new student record
3. Search Student - Find by name or course
4. Update Student - Modify existing student information
5. Delete Student - Remove student record (with confirmation)
6. View Report - Display system statistics
7. Save and Exit - Persist data and close application

Data Persistence

File Format
```
ID,Name,Course,GPA,Active,Year
1,John Smith,BSIT,3.75,1,2024
...
```

File Operations
- Load: Automatically reads `students.txt` on startup
- Parse: Parses comma-separated values into Student objects
- Save: Updates file with all changes when exiting

Project Structure
```
student_manager_system/
├── main.cpp                 # Application entry point & menu system
├── Student.h               # Student class declaration
├── Student.cpp             # Student class implementation
├── StudentManager.h        # StudentManager class declaration
├── StudentManager.cpp      # StudentManager class implementation
├── students.txt            # Initial database 
└── README.md              # This file
```

Non-Functional Requirements Met

Robustness: Input validation with error messages  
Modularity: Separated .h and .cpp files  
Encapsulation: Private data with public accessors  Naming: PascalCase for classes, camelCase for variables  
Documentation: In-code comments for all methods  
Memory Efficiency: Appropriate data type selection  
Scope Management: Variables declared in narrowest scope  

Contributors

This is a student project developed as part of CC103 - Computer Programming coursework at National Teacher's College.

Primary Modules:
- Student Entity Management: All team members
- System Architecture: All team members
- File I/O & Persistence: All team members
- User Interface & Menu: All team members

Future Enhancements

- Database connectivity (MySQL/SQLite)
- GUI interface using Qt or wxWidgets
- Advanced filtering and reporting features
- Data import/export functionality
- Authentication and multi-user support

 Academic Integrity Notice

This project is original work created as part of the course curriculum. All external code is properly cited and attributed.



Last Updated: May 17, 2026  
Course: CC103 - Computer Programming   
Semester: 2nd Semester, 1st Year BSIT
