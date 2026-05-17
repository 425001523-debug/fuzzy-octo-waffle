#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>

using namespace std;

class Task {
private:
    int taskId;
    string title;
    string subject;
    string deadline;
    int priorityLevel;
    bool completed;

public:
    Task();
    Task(int id, string t, string sub, string due, int priority, bool status);

    void setTaskId(int id);
    int getTaskId();

    void setTitle(string t);
    string getTitle();

    void setSubject(string sub);
    string getSubject();

    void setDeadline(string due);
    string getDeadline();

    void setPriorityLevel(int priority);
    int getPriorityLevel();

    void setCompleted(bool status);
    bool isCompleted();

    double calculateProductivityScore();
};

#endif
#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>

using namespace std;

class Task {
private:
    int taskId;
    string title;
    string subject;
    string deadline;
    int priorityLevel;
    bool completed;

public:
    Task();
    Task(int id, string t, string sub, string due, int priority, bool status);

    void setTaskId(int id);
    int getTaskId();

    void setTitle(string t);
    string getTitle();

    void setSubject(string sub);
    string getSubject();

    void setDeadline(string due);
    string getDeadline();

    void setPriorityLevel(int priority);
    int getPriorityLevel();

    void setCompleted(bool status);
    bool isCompleted();

    double calculateProductivityScore();
};

#endif